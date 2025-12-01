#include <Arduino.h>
#include <nvs_flash.h>

#include "wifi_manager.h"

static const char* TAG = "MAIN";

void setup() {
    Serial.begin(115200);
    delay(500);

    Serial.println("\n==============================");
    Serial.println(" 🔧 Iniciando sistema principal");
    Serial.println("==============================\n");

    // -------------------------------------------------------
    // 1) Inicializar NVS
    // -------------------------------------------------------
    Serial.println("⚙ Inicializando NVS...");

    esp_err_t ret = nvs_flash_init();
    if (ret == ESP_ERR_NVS_NO_FREE_PAGES ||
        ret == ESP_ERR_NVS_NEW_VERSION_FOUND)
    {
        Serial.println("⚠ Se requiere borrar NVS, corrigiendo...");
        nvs_flash_erase();
        nvs_flash_init();
    }
    Serial.println("✔ NVS inicializado correctamente\n");

    // -------------------------------------------------------
    // 2) Iniciar WiFi Manager
    // -------------------------------------------------------
    wifi_manager_start();

    Serial.println("\n📡 WiFi Manager iniciado\n");
}

void loop() {
    wifi_manager_loop();
    delay(10);  // evita bloquear el sistema
}

// -----------------------------------------------------------
// 🔥 ESP-IDF requiere obligatoriamente esta función
// -----------------------------------------------------------
extern "C" void app_main() {
    initArduino();  // Inicializa el entorno Arduino dentro de ESP-IDF

    setup();

    while (true) {
        loop();
        vTaskDelay(1);  // cede tiempo al scheduler FreeRTOS
    }
}
