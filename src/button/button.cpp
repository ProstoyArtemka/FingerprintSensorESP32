#include <button/button.h>
#include <functional>

#include <Arduino.h>

Button::Button(int pin) : pin(pin) {

    pinMode(pin, INPUT_PULLUP);

}

void Button::tick() {

    bool buttonValue = digitalRead(pin) != HIGH;

    if (!buttonValue) {

        if (buttonPressed) {
            if (releaseFuncSet)
                releaseFunc();

            buttonPressed = false;
        }

        lastButtonUnpressed = millis();
    }

    if (buttonValue && millis() - lastButtonUnpressed >= 100) {
        buttonPressed = true;
    }
}

void Button::onRelease(std::function<void()> func) {

    releaseFunc = func;
    releaseFuncSet = true;

}