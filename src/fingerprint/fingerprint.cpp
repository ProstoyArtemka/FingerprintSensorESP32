#include <fingerprint/fingerprint.h>
#include <Arduino.h>
#include <Adafruit_Fingerprint.h>

Fingerprint::Fingerprint(Preferences &prefs) : Adafruit_Fingerprint(&Serial2), prefs(prefs) {}

void Fingerprint::init() {
    Serial2.begin(57600, SERIAL_8N1, 17, 18);

    enabled = verifyPassword();

    prefs.begin("fingerprint");

    if (!prefs.isKey("lastId"))
        prefs.putInt("lastId", 0);

    this->lastId = prefs.getInt("lastId");
    
    prefs.end();

    Adafruit_Fingerprint::deleteModel(5);
}

bool Fingerprint::isEnabled() {
    return enabled;
}

void Fingerprint::retry() {

    enabled = verifyPassword();

}

int Fingerprint::getCapacity() {
    return this->capacity;
}

int Fingerprint::getAmount() {
    Adafruit_Fingerprint::getTemplateCount();

    return this->templateCount;
}

int Fingerprint::getLastId() {
    return lastId;

}

void Fingerprint::incrementLastId() {

    this->lastId++;

    prefs.begin("fingerprint");
    prefs.putInt("lastId", lastId);
    prefs.end();
}


uint8_t Fingerprint::getImage() {
    return Adafruit_Fingerprint::getImage();
}

uint8_t Fingerprint::image2Tz(int slot) {
    return Adafruit_Fingerprint::image2Tz(slot);
}

uint8_t Fingerprint::fingerFastSearch() {
    return Adafruit_Fingerprint::fingerFastSearch();
}

uint8_t Fingerprint::createModel() {
    return Adafruit_Fingerprint::createModel();
}

uint8_t Fingerprint::storeModel(int id) {
    return Adafruit_Fingerprint::storeModel(id);
}

int Fingerprint::getConfidence() {
    return confidence;
}

int Fingerprint::getFingerprintID() {
    return fingerID;
}

int Fingerprint::scanFingerprint() {
    int status = getImage();
    if (status != FINGERPRINT_OK) return -1;

    status = image2Tz(1);
    if (status != FINGERPRINT_OK) return -1;

    status = fingerFastSearch();
    if (status != FINGERPRINT_OK) return -2;

    return getFingerprintID();
}

void Fingerprint::clearFingerprints() {
    
    this->emptyDatabase();
    this->lastId = 0;

    prefs.begin("fingerprint");
    prefs.putInt("lastId", lastId);
    prefs.end();
}