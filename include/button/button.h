#ifndef BUTTON_H
#define BUTTON_H

#include <functional>

class Button {

    int pin;

    long lastButtonUnpressed = 0;

    bool buttonPressed = false;

    std::function<void()> buttonPressedForFuncs[10];
    bool alreadyPresssedFor[10];

    std::function<void()> releaseFunc;
    bool releaseFuncSet = false;

    public:
        Button(int pin);

        void tick();

        void buttonPressedFor(int seconds, std::function<void()> func);
        void onRelease(std::function<void()> func);
};

#endif