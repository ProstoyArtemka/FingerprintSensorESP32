#include <fingerprint/fingerprint.h>
#include <Arduino.h>

Fingerprint::Fingerprint(Preferences &prefs) : FPM(&Serial2), prefs(prefs) {}

void Fingerprint::init() {
    Serial2.setRxBufferSize(4096);
    Serial2.begin(57600, SERIAL_8N1, 17, 18);

    enabled = begin();
    if (!enabled) return;

    readParams(&params);


    prefs.begin("fingerprint");

    if (!prefs.isKey("lastId"))
        prefs.putInt("lastId", 0);

    this->lastId = prefs.getInt("lastId");
    
    prefs.end();
}

bool Fingerprint::isEnabled() {
    return enabled;
}

void Fingerprint::retry() {

    enabled = verifyPassword(0);

}

int Fingerprint::getCapacity() {
    return this->params.capacity;
}

int Fingerprint::getAmount() {
    this->getTemplateCount(&tempalteCount);

    return tempalteCount;
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


FPMStatus Fingerprint::getImage() {
    return FPM::getImage();
}

FPMStatus Fingerprint::image2Tz(int slot) {
    return FPM::image2Tz(slot);
}

FPMStatus Fingerprint::fingerFastSearch(int slot) {
    return FPM::searchDatabase(&fingerprintId, &confidence, slot);
}

FPMStatus Fingerprint::createModel() {
    return FPM::generateTemplate();
}

FPMStatus Fingerprint::storeModel(int id, int slot) {
    return FPM::storeTemplate(id, slot);
}

int Fingerprint::getConfidence() {
    return confidence;
}

int Fingerprint::getFingerprintID() {
    return fingerprintId;
}

int Fingerprint::scanFingerprint() {
    FPMStatus status = getImage();
    if (status != FPMStatus::OK) return -1;

    status = image2Tz(1);
    if (status != FPMStatus::OK) return -1;

    status = fingerFastSearch(1);
    if (status != FPMStatus::OK) return -2;

    return getFingerprintID();
}

void Fingerprint::clearFingerprints() {
    
    this->emptyDatabase();
    this->lastId = 0;

    prefs.begin("fingerprint");
    prefs.putInt("lastId", lastId);
    prefs.end();
}

// Usage after getImage
FPMStatus Fingerprint::saveToLittleFS(const char* filename) {

    while (Serial2.available()) Serial2.read();

    if (downloadImage() == FPMStatus::OK) {
        File file = LittleFS.open(filename, FILE_WRITE);
        if (!file) return FPMStatus::NOTFOUND;

        uint8_t packet[FPM_MAX_PACKET_LEN]; 
        uint16_t readLen;
        bool isComplete = false;

        while (!isComplete) {
            if (readDataPacket(packet, NULL, &readLen, &isComplete)) {
                file.write(packet, readLen);

                yield();
            }
        }

        file.close();

        return FPMStatus::OK;
    }

    return FPMStatus::NOTFOUND;
}