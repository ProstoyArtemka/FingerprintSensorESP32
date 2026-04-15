#include <display/scene_handler.h>

SceneHandler::SceneHandler(Display *display, Sprite *buffer, Fingerprint *fingerprint) : display(display), buffer(buffer) {

    for (int i = 0; i < 16; i++)
        sceneTransitions[i] = (Scenes) -1;

    scenes[EMPTY_SCENE] = new EmptyScene(display, buffer);
    scenes[MAIN_SCENE] = new MainMenuScene(display, buffer);
    scenes[SENSOR_NOT_FOUND_SCENE] = new SensorNotFoundScene(display, buffer);
    scenes[INFO_SCENE] = new InfoScene(display, buffer, fingerprint);
    scenes[SCAN_FINGER_SCENE] = new ScanFingerScene(display, buffer, fingerprint);

    changeScene(MAIN_SCENE, true);



    setTransition(EMPTY_SCENE, INFO_SCENE);
    setTransition(MAIN_SCENE, INFO_SCENE);

    setTransition(INFO_SCENE, SCAN_FINGER_SCENE);
    setTransition(SCAN_FINGER_SCENE, MAIN_SCENE);
}

SceneHandler::~SceneHandler() {
    
    for (int i = 0; i < 16; i++) {
        if (scenes[i] == nullptr) continue;

        delete scenes[i];
    }

}

void SceneHandler::tick() {

    if (sceneChanged) {
        currentScene->setup();

        sceneChanged = false;
    }

    currentScene->draw();
}

void SceneHandler::changeScene(Scenes index, bool force) {
    Scene *toChange = scenes[index];

    if (index == currentSceneIndex && !force) return;

    currentScene = toChange;
    currentSceneIndex = index;
    sceneChanged = true;

}

bool SceneHandler::isScene(Scenes index) {
    return currentSceneIndex == index;
}

bool SceneHandler::isScene(int count, ...){
    va_list args;
    va_start(args, count);

    for (int i = 0; i < count; i++) {
        int value = va_arg(args, int);

        if (currentSceneIndex == value) {
            va_end(args);
            
            return true;
        }
    }

    va_end(args);

    return false;
}

void SceneHandler::setTransition(Scenes from, Scenes to) {
    sceneTransitions[from] = to;
}

void SceneHandler::transitionScene() {
    int transition = sceneTransitions[currentSceneIndex];
    Serial.println(transition);

    if (transition == -1) return; 

    changeScene((Scenes) transition, false);
}

void SceneHandler::buttonRelease() {

    if (!currentScene->buttonRelease())
        transitionScene();

}