#ifndef FINGERPRINT_H
#define FINGERPRINT_H

#include <Arduino.h>
#include <Preferences.h>
#include <FPM.h>
#include <LittleFS.h>

class Fingerprint : FPM {
    bool enabled;
    int lastId = 0;

    uint16_t fingerprintId;
    uint16_t confidence;
    uint16_t tempalteCount;

    Preferences &prefs;
    FPMSystemParams params;

    public:
        Fingerprint(Preferences &prefs);

        void init();

        void retry();
        bool isEnabled();

        int getCapacity();
        int getAmount();
        int getLastId();
        void incrementLastId();

        FPMStatus getImage();
        FPMStatus image2Tz(int slot);
        FPMStatus fingerFastSearch(int slot);
        FPMStatus createModel();
        FPMStatus storeModel(int id, int slot);
        FPMStatus saveToLittleFS(const char* filename);

        int getFingerprintID();
        int getConfidence();
        
        int scanFingerprint();
        void clearFingerprints();

};

#endif