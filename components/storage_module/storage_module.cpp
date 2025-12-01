#include "storage_module.h"
#include <Preferences.h>
#include <nvs_flash.h>

Preferences prefs;

// -----------------------
// Inicialización del NVS
// -----------------------
bool storage_init() {
    esp_err_t ret = nvs_flash_init();

    if (ret == ESP_ERR_NVS_NO_FREE_PAGES || ret == ESP_ERR_NVS_NEW_VERSION_FOUND) {
        // La partición NVS está corrupta → borrar y reiniciar
        nvs_flash_erase();
        ret = nvs_flash_init();
    }

    return ret == ESP_OK;
}

// -----------------------
// Guardar SSID / PASS
// -----------------------
bool storage_save_wifi(const String& ssid, const String& pass) {
    prefs.begin("wifi", false);
    prefs.putString("ssid", ssid);
    prefs.putString("pass", pass);
    prefs.end();
    return true;
}

// -----------------------
// Cargar SSID / PASS
// -----------------------
bool storage_load_wifi(String& ssid, String& pass) {
    prefs.begin("wifi", true);  // modo lectura
    ssid = prefs.getString("ssid", "");
    pass = prefs.getString("pass", "");
    prefs.end();
    return ssid.length() > 0;  // true si había datos
}

// -----------------------
// Borrar SSID / PASS
// -----------------------
bool storage_clear_wifi() {
    prefs.begin("wifi", false);
    prefs.clear();
    prefs.end();
    return true;
}

