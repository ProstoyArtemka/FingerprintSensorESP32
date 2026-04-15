#ifndef SCENE_HANDLER_H
#define SCENE_HANDLER_H

#include <display/display.h>
#include <display/sprite.h>
#include <display/scene.h>

#include <display/impl/sensor_not_found.scene.h>
#include <display/impl/main_menu.scene.h>
#include <display/impl/empty.scene.h>
#include <display/impl/info.scene.h>
#include <display/impl/scan_finger.scene.h>

enum Scenes {
    EMPTY_SCENE, 
    MAIN_SCENE, 
    SENSOR_NOT_FOUND_SCENE,
    INFO_SCENE,
    SCAN_FINGER_SCENE
};

class SceneHandler {

    Display *display;
    Sprite *buffer;
    
    Scene *currentScene;
    Scenes currentSceneIndex;

    Scene *scenes[16];
    int sceneTransitions[16];

    bool sceneChanged = true;

    public:

        SceneHandler(Display *display, Sprite *buffer, Fingerprint *fingerprint);

        void tick();

        void changeScene(Scenes index, bool force);

        bool isScene(Scenes index);
        bool isScene(int count, ...);

        void setTransition(Scenes from, Scenes to);
        void transitionScene();

        void buttonRelease();

        ~SceneHandler();
};

#endif