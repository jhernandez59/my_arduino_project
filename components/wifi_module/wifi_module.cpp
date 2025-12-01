#include "wifi_module.h"
#include <WiFi.h>

bool wifi_connect(const char* ssid, const char* pass) {
    WiFi.mode(WIFI_STA);     // <--- IMPORTANTE
    WiFi.disconnect(true);   // Limpia estados previos
    delay(100);

    WiFi.begin(ssid, pass);

    unsigned long start = millis();
    while (WiFi.status() != WL_CONNECTED && millis() - start < 8000) {
        delay(200);
    }

    return WiFi.status() == WL_CONNECTED;
}

bool wifi_is_connected() {
    return WiFi.status() == WL_CONNECTED;
}

void wifi_disconnect() {
    WiFi.disconnect(true);
    WiFi.mode(WIFI_OFF);   // <--- Para evitar errores de driver
}

