#pragma once
#include <WiFi.h>
#include <Arduino.h>

using SaveCallback = void (*)(const String&, const String&);

void webserver_set_save_callback(SaveCallback cb);

void webserver_start_config();
void webserver_start();
void webserver_stop();
void webserver_loop();

