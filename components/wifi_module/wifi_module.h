#pragma once
#include <Arduino.h>

bool wifi_connect(const char* ssid, const char* pass);
bool wifi_is_connected();
void wifi_disconnect();
