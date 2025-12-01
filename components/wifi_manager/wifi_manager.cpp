#include "wifi_manager.h"

#include "wifi_module.h"
#include "ap_module.h"
#include "storage_module.h"
#include "webserver_module.h"

#include <WiFi.h>
#include "esp_log.h"

static const char* TAG = "WIFI_MANAGER";

enum WifiState {
    WIFI_STATE_INIT,
    WIFI_STATE_TRY_CONNECT,
    WIFI_STATE_CONFIG_PORTAL,
    WIFI_STATE_CONNECTED
};

static WifiState state = WIFI_STATE_INIT;

// Variables globales
static String g_ssid = "";
static String g_pass = "";


// ------------------------------------------------------------------
// Callback llamado DESDE el webserver cuando el usuario presiona "Guardar"
// ------------------------------------------------------------------
void wifi_manager_restart_after_config(const String& ssid, const String& pass) {
    ESP_LOGI(TAG, "📡 Recibido SSID/PASS desde webserver. Guardando...");

    // Guardar
    storage_save_wifi(ssid, pass);

    g_ssid = ssid;
    g_pass = pass;

    // Apagar modo AP
    ap_stop();
    webserver_stop();

    // Cambiar de estado → intentar conectar en modo STA
    state = WIFI_STATE_TRY_CONNECT;
}


// ------------------------------------------------------------------
// Flujo principal
// ------------------------------------------------------------------
void wifi_manager_start() {
    ESP_LOGI(TAG, "🔧 WiFi Manager iniciando...");

    // 1) Inicializar NVS solo una vez
    if (!storage_init()) {
        ESP_LOGE(TAG, "❌ Error inicializando NVS");
        return;
    }

    // 2) Cargar credenciales
    bool ok = storage_load_wifi(g_ssid, g_pass);

    if (ok) {
        ESP_LOGI(TAG, "📡 Credenciales encontradas en NVS: SSID=%s", g_ssid.c_str());
        state = WIFI_STATE_TRY_CONNECT;
    } else {
        ESP_LOGW(TAG, "⚠ No hay credenciales -> modo configuración");
        state = WIFI_STATE_CONFIG_PORTAL;
    }

    // Registrar callback del webserver
    webserver_set_save_callback(wifi_manager_restart_after_config);
}


// ------------------------------------------------------------------
// Bucle de ejecución (se llama desde loop())
// ------------------------------------------------------------------
void wifi_manager_loop() {
    switch (state) {

        // ----------------------------------------------------------
        case WIFI_STATE_TRY_CONNECT: {
            ESP_LOGI(TAG, "🌐 Intentando conectar a: %s", g_ssid.c_str());

            WiFi.mode(WIFI_STA);
            
            if (wifi_connect(g_ssid.c_str(), g_pass.c_str())) {
                ESP_LOGI(TAG, "✅ Conectado! IP: %s", WiFi.localIP().toString().c_str());

                webserver_start();    // modo normal
                state = WIFI_STATE_CONNECTED;
            } else {
                ESP_LOGW(TAG, "⚠ Falló la conexión → modo configuración");
                state = WIFI_STATE_CONFIG_PORTAL;
            }
            break;
        }

        // ----------------------------------------------------------
        case WIFI_STATE_CONFIG_PORTAL: {
            ESP_LOGI(TAG, "📶 Iniciando modo AP + portal de configuración");

            ap_start("ESP32_Config");
            webserver_start_config();

            state = WIFI_STATE_CONNECTED;  // usar connected para ejecutar loop
            break;
        }

        // ----------------------------------------------------------
        case WIFI_STATE_CONNECTED: {
            webserver_loop();  // atender peticiones
            break;
        }

        default:
            break;
    }
}
