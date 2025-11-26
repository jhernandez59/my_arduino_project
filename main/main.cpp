#include "Arduino.h"       // ⭐ Integración Arduino
#include "../components/wifi_module/wifi_module.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_log.h"

static const char *TAG = "ARDUINO_APP";

extern "C" void app_main(void);

/**
 * Tarea principal que maneja la lógica que antes estaba en setup() y loop().
 */
void main_app_task(void *pvParameters) {

    Serial.begin(115200);   // Inicializa puerto serial
    ESP_LOGI(TAG, "Iniciando lógica de la aplicación...");

    wifi_init("WIFI_SSID", "WIFI_PASS");

    while (true) {

        if (wifi_is_connected()) {
            Serial.println("📡 WiFi conectado");
        } else {
            Serial.println("🔄 WiFi desconectado, reintentando...");
             wifi_init("WIFI_SSID", "WIFI_PASS");
        }

        vTaskDelay(pdMS_TO_TICKS(2000));
    }
}

// 👉 Punto de entrada para ESP-IDF
extern "C" void app_main(void) {
    // 🔰 Inicializamos Arduino 
    // (necesario para usar las funciones de Arduino como Serial, digitalWrite, etc.)
    initArduino();

    // 🧵 Creamos la tarea principal que contiene toda la lógica
    xTaskCreatePinnedToCore(
        main_app_task,
        "main_app_task",
        4096,      // Tamaño de stack
        NULL,
        1,         // Prioridad
        NULL,
        0          // Núcleo (0)
    );

    
}
