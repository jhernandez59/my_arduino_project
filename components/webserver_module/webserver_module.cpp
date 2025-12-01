#include "webserver_module.h"
#include <WebServer.h>

static WebServer server(80);
static SaveCallback save_callback = nullptr;

// Registrar el callback
void webserver_set_save_callback(SaveCallback cb) {
    save_callback = cb;
}

// --------------------------------------------------------------------------
// Página principal — formulario
// --------------------------------------------------------------------------
void handle_root() {
    String html = R"(
        <html>
        <body>
        <h2>Configuración WiFi</h2>
        <form action="/save" method="POST">
            SSID: <input name="ssid"><br><br>
            PASS: <input name="pass" type="password"><br><br>
            <input type="submit" value="Guardar">
        </form>
        </body>
        </html>
    )";

    server.send(200, "text/html", html);
}

// --------------------------------------------------------------------------
// Guardar datos — llama al callback si existe
// --------------------------------------------------------------------------
void handle_save() {
    String ssid = server.arg("ssid");
    String pass = server.arg("pass");

    if (ssid.length() == 0) {
        server.send(400, "text/plain", "SSID no puede estar vacío");
        return;
    }

    server.send(200, "text/plain", "Guardado. Intentando conexión...");

    if (save_callback) {
        save_callback(ssid, pass);
    }
}

// --------------------------------------------------------------------------
void webserver_start_config() {
    server.on("/", handle_root);
    server.on("/save", handle_save);
    server.begin();
}

// --------------------------------------------------------------------------
// MODO NORMAL
// --------------------------------------------------------------------------
void handle_normal_root() {
    String html = "<h2>ESP32 funcionando en modo normal</h2>";
    html += "<p>IP local: " + WiFi.localIP().toString() + "</p>";
    server.send(200, "text/html", html);
}

void webserver_start() {
    server.on("/", handle_normal_root);
    server.begin();
}

// --------------------------------------------------------------------------
void webserver_stop() {
    server.stop();
}

// --------------------------------------------------------------------------
void webserver_loop() {
    server.handleClient();
}
