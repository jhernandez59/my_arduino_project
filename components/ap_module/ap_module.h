#pragma once
#include <Arduino.h>

void ap_start(const char* ssid_ap);
void ap_stop();
String ap_get_ip();

