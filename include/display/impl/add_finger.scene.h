#ifndef ADD_FINGER_SCENE_H
#define ADD_FINGER_SCENE_H

#include <display/display.h>
#include <display/scene.h>
#include <Fingerprint.h>

class AddFingerScene : public Scene {

    Fingerprint *fingerprint;
    long lastFingerprintCheck = 0;;
    int checKDelay = 0;
    bool addedFingerprint = false;

    Sprite addFingerSprite;

    int step = 0;

    public:
        bool removedFingerprints = false;

        AddFingerScene(Display *display, Sprite *buffer, Fingerprint *fingerprint);

        void drawText();
        void processSensor();

        void setup() override;
        void draw() override;
        
        bool buttonRelease() override;

};

#endif