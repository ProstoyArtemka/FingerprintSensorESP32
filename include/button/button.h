#ifndef BUTTON_H
#define BUTTON_H

#include <functional>

class Button {

    int pin;

    long lastButtonUnpressed = 0;

    bool buttonPressed = false;

    std::function<void()> releaseFunc;
    bool releaseFuncSet = false;

    public:
        Button(int pin);

        void tick();

        void onRelease(std::function<void()> func);
};

#endif