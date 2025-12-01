#pragma once
#include <Arduino.h>

void wifi_manager_start();
void wifi_manager_loop();

// llamado por el webserver cuando el usuario guarda ssid/pass
void wifi_manager_restart_after_config(const String& ssid, const String& pass);
