#include "storage_module.h"
#include "esp_log.h"

static const char *TAG = "TEST_STORAGE";

extern "C" void test_storage_run() {
    ESP_LOGI(TAG, "===== Iniciando prueba de storage_module =====");

    String ssid = "MiRedTest";
    String pass = "Clave123";

    ESP_LOGI(TAG, "Guardando credenciales...");
    storage_save_wifi(ssid, pass);

    String ssid_read, pass_read;
    ESP_LOGI(TAG, "Leyendo credenciales...");
    bool ok = storage_load_wifi(ssid_read, pass_read);

    if (ok) {
        ESP_LOGI(TAG, "SSID leído: %s", ssid_read.c_str());
        ESP_LOGI(TAG, "PASS leído: %s", pass_read.c_str());
    } else {
        ESP_LOGE(TAG, "No se encontraron credenciales.");
    }

    ESP_LOGI(TAG, "Borrando credenciales...");
    storage_clear_wifi();

    ESP_LOGI(TAG, "Probando lectura después del borrado...");
    ok = storage_load_wifi(ssid_read, pass_read);
    if (!ok) {
        ESP_LOGI(TAG, "OK — No hay credenciales almacenadas (borrado exitoso)");
    } else {
        ESP_LOGE(TAG, "ERROR — Se encontraron credenciales después del borrado");
    }

    ESP_LOGI(TAG, "===== Prueba completada =====");
}

