#ifndef SEN_NOT_FOUND_H
#define SEN_NOT_FOUND_H

#include <display/display.h>
#include <display/scene.h>


class SensorNotFoundScene : public Scene {

    Sprite angrySprite;

    public:
        SensorNotFoundScene(Display *display, Sprite *buffer);

        void setup() override;
        void draw() override;
        
        bool buttonRelease() override;

};

#endif