#include "Arduino.h"       // ⭐ Integración Arduino
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_log.h"

static const char *TAG = "ARDUINO_APP";

extern "C" void app_main(void);

// 👉 Prototipo del loop() como en Arduino
void loop(void);

// 👉 Tarea que ejecuta loop() continuamente
void arduino_loop_task(void *pvParameters) {
    ESP_LOGI(TAG, "Iniciando loop() de Arduino...");

    for (;;) {
        loop();
        vTaskDelay(pdMS_TO_TICKS(10));  // 🕒 Frecuencia del loop()
    }
}

// 👉 Setup como en Arduino
void setup() {
    Serial.begin(115200);   // 🖥️ Inicializa puerto serial
    pinMode(2, OUTPUT);     // 💡 LED en GPIO2
    Serial.println("🚀 Arduino iniciado dentro de ESP-IDF");
}

// 👉 Loop típico de Arduino
void loop() {
    digitalWrite(2, HIGH);       // 💡 LED ON
    Serial.println("LED ON");
    delay(500);

    digitalWrite(2, LOW);        // 🔦 LED OFF
    Serial.println("LED OFF");
    delay(500);
}

// 👉 Punto de entrada para ESP-IDF
extern "C" void app_main(void) {
    // 🔰 Inicializamos Arduino
    initArduino();

    // ⚙️ Ejecutamos el setup()
    setup();

    // 🧵 Creamos la tarea que manejará loop()
    xTaskCreatePinnedToCore(
        arduino_loop_task,
        "arduino_loop_task",
        4096,      // Tamaño de stack
        NULL,
        1,         // Prioridad
        NULL,
        1          // Núcleo
    );
}
