#ifndef FINGERPRINT_H
#define FINGERPRINT_H

#include <Arduino.h>
#include <Adafruit_Fingerprint.h>
#include <Preferences.h>

class Fingerprint : Adafruit_Fingerprint {
    bool enabled;
    int lastId = 0;

    Preferences &prefs;

    public:
        Fingerprint(Preferences &prefs);

        void init();

        void retry();
        bool isEnabled();

        int getCapacity();
        int getAmount();
        int getLastId();
        void incrementLastId();

        uint8_t getImage();
        uint8_t image2Tz(int slot);
        uint8_t fingerFastSearch();
        uint8_t createModel();
        uint8_t storeModel(int id);

        int getFingerprintID();
        int getConfidence();
        
        int scanFingerprint();
        void clearFingerprints();

};

#endif