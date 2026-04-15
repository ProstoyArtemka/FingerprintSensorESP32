#ifndef SCAN_FINGER_SCENE_H
#define SCAN_FINGER_SCENE_H

#include <display/display.h>
#include <display/scene.h>
#include <Fingerprint.h>


class ScanFingerScene : public Scene {

    Fingerprint *fingerprint;

    Sprite scanFingerSprite;

    public:
        ScanFingerScene(Display *display, Sprite *buffer, Fingerprint *fingerprint);

        void setup() override;
        void draw() override;

        bool buttonRelease() override;

};

#endif