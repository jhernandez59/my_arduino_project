#pragma once

#include <Arduino.h>
#include <WiFi.h>

#define WIFI_SSID "SKYNET"
#define WIFI_PASS "79152302"

void wifi_init(const char* ssid, const char* password);
bool wifi_is_connected();
