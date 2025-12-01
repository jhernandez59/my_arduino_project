#include "ap_module.h"
#include <WiFi.h>
#include "esp_log.h"

static const char* TAG = "AP_MODULE";

void ap_start(const char* ssid_ap) {
    ESP_LOGI(TAG, "Iniciando Access Point: %s", ssid_ap);

    WiFi.mode(WIFI_AP);

    bool ok = WiFi.softAP(ssid_ap, "", 1, 0, 4);  
    //                    SSID, PASS, CH,  HIDDEN, MAX_CONN
    // Canal 1 → más estable
    // Red visible (0 = visible)
    // Máximo 4 clientes
    // Sin contraseña (modo configuración)

    if (!ok) {
        ESP_LOGE(TAG, "❌ Error iniciando AP");
        return;
    }

    delay(100);  // pequeña pausa para estabilidad

    IPAddress ip = WiFi.softAPIP();
    ESP_LOGI(TAG, "AP iniciado en IP: %s", ip.toString().c_str());
}

void ap_stop() {
    ESP_LOGI(TAG, "Deteniendo AP...");
    WiFi.softAPdisconnect(true); // desconecta y apaga AP
    WiFi.mode(WIFI_OFF);    // apaga WiFi completamente
}

String ap_get_ip() {
    return WiFi.softAPIP().toString();
}
