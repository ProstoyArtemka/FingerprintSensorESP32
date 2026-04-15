#ifndef FINGERPRINT_H
#define FINGERPRINT_H

#include <Arduino.h>
#include <Adafruit_Fingerprint.h>
#include <Preferences.h>

class Fingerprint : Adafruit_Fingerprint {
    bool enabled;

    Preferences prefs;

    public:
        Fingerprint(Preferences prefs);

        void init();

        void retry();
        bool isEnabled();

        int getCapacity();
        int getAmount();
        int getLastId();
        

};

#endif