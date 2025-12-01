#pragma once
#include <Arduino.h>

bool storage_init();
bool storage_save_wifi(const String& ssid, const String& pass);
bool storage_load_wifi(String& ssid, String& pass);
bool storage_clear_wifi();
