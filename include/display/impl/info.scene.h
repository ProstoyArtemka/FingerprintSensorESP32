#ifndef INFO_SCENE_H
#define INFP_SCENE_H

#include <display/display.h>
#include <display/scene.h>

#include <Fingerprint.h>


class InfoScene : public Scene {

    Fingerprint *fingerprint;
    Sprite infoSprite;

    public:
        InfoScene(Display *display, Sprite *buffer, Fingerprint *fingerprint);

        void setup() override;
        void draw() override;

        bool buttonRelease() override;

};

#endif