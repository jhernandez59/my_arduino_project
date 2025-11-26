#include "wifi_module.h"

void wifi_init(const char* ssid, const char* password) {

    Serial.println("🔌 Iniciando WiFi...");

    WiFi.mode(WIFI_STA);
    WiFi.begin(WIFI_SSID, WIFI_PASS);

    int intentos = 0;

    while (WiFi.status() != WL_CONNECTED && intentos < 20) {
        delay(500);
        Serial.print(".");
        intentos++;
    }

    Serial.println();

    if (WiFi.status() == WL_CONNECTED) {
        Serial.println("✅ WiFi conectado");
        Serial.print("IP: ");
        Serial.println(WiFi.localIP());
    } else {
        Serial.println("❌ No se pudo conectar al WiFi");
    }
}

bool wifi_is_connected() {
    return WiFi.status() == WL_CONNECTED;
}
