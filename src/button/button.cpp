#include <button/button.h>
#include <functional>

#include <Arduino.h>

Button::Button(int pin) : pin(pin) {

    pinMode(pin, INPUT_PULLUP);

    for (int i = 0; i < 10; i++) {
        alreadyPresssedFor[i] = false;
        buttonPressedForFuncs[i] = nullptr;
    }
}

void Button::tick() {

    bool buttonValue = digitalRead(pin) != HIGH;

    if (!buttonValue) {

        if (buttonPressed) {
            if (releaseFuncSet)
                releaseFunc();

            buttonPressed = false;

            for (int i = 0; i < 10; i++) alreadyPresssedFor[i] = false;
        }

        lastButtonUnpressed = millis();
    }

    if (buttonValue && millis() - lastButtonUnpressed >= 100) {
        buttonPressed = true;

        if (millis() - lastButtonUnpressed >= 1000) {
            int seconds = (millis() - lastButtonUnpressed) / 1000;

            if (alreadyPresssedFor[seconds - 1]) return;

            std::function<void()> f = buttonPressedForFuncs[seconds - 1];

            if (f) f();

            alreadyPresssedFor[seconds - 1] = true;
        }
    }
}

void Button::onRelease(std::function<void()> func) {

    releaseFunc = func;
    releaseFuncSet = true;

}

void Button::buttonPressedFor(int seconds, std::function<void()> func) {

    buttonPressedForFuncs[seconds - 1] = func;

}