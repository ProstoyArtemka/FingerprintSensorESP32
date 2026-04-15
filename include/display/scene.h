#ifndef SCENE_H
#define SCENE_H

#include <display/display.h>
#include <display/sprite.h>

class Scene {

    public:
        Display *display;
        Sprite *buffer;

        Scene(Display *display, Sprite *buffer);

        virtual void setup() = 0;
        virtual void draw() = 0;

        virtual bool buttonRelease() = 0;

};

#endif