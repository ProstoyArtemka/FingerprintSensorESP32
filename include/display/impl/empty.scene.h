#ifndef EMPTY_SCENE_H
#define EMPTY_SCENE_H

#include <display/display.h>
#include <display/scene.h>


class EmptyScene : public Scene {

    public:
        EmptyScene(Display *display, Sprite *buffer);

        void setup() override;
        void draw() override;
        
        bool buttonRelease() override;

};

#endif