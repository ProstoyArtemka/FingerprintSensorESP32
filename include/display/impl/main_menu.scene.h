#ifndef MAIN_MENU_H
#define MAIN_MENU_H

#include <display/display.h>
#include <display/scene.h>


class MainMenuScene : public Scene {

    Sprite okSprite;

    public:
        MainMenuScene(Display *display, Sprite *buffer);

        void setup() override;
        void draw() override;

        bool buttonRelease() override;

};

#endif