#include <server/server.h>
#include <server/pages.h>

#include <LittleFS.h>

FingerprintServer::FingerprintServer(const char* name, const char* password, const int port) : server(port) {

    WiFi.mode(WIFI_AP);
    WiFi.softAP(name, password);

    server.on("/", [this]() {

        this->server.send(200, "text/html", MAIN_PAGE);

    });

    server.on("/get-finger", [this]() {

        if (LittleFS.exists("/currentFinger.raw")) {
            File file = LittleFS.open("/currentFinger.raw", "r");

            this->server.streamFile(file, "application/octet-stream");
            file.close();

            return;
        }

        this->server.send(404, "text/plain", "Not found.");

    });

    server.begin();
}

void FingerprintServer::handle() {
    server.handleClient();
}