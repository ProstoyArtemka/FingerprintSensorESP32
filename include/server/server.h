#ifndef WEBSERVER_LIB_H

#define WEBSERVER_LIB_H
#include <WiFi.h>
#include <WebServer.h>
#include <LittleFS.h>

class FingerprintServer {

    WebServer server;

    public:
        FingerprintServer(const char* name, const char* password, const int port);

        void handle();
};

#endif