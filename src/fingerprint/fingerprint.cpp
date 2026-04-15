#include <fingerprint/fingerprint.h>
#include <Arduino.h>
#include <Adafruit_Fingerprint.h>

Fingerprint::Fingerprint(Preferences prefs) : Adafruit_Fingerprint(&Serial2), prefs(prefs) {}

void Fingerprint::init() {
    Serial2.begin(57600, SERIAL_8N1, 17, 18);

    enabled = verifyPassword();

    prefs.begin("fingerprint");

    if (!prefs.isKey("lastId"))
        prefs.putInt("lastId", 0);
    
    prefs.end();
}

bool Fingerprint::isEnabled() {
    return enabled;
}

void Fingerprint::retry() {

    enabled = verifyPassword();

}

int Fingerprint::getCapacity() {
    return capacity;
}

int Fingerprint::getAmount() {
    return templateCount;
}

int Fingerprint::getLastId() {

    this->prefs.begin("fingerprint");
    
    int lastId = prefs.getInt("lastId");

    this->prefs.end();

    return lastId;

}