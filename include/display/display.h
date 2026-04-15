#ifndef DISPLAY_H
#define DISPLAY_H

#include <Arduino.h>
#include <LovyanGFX.h>

class Display : public lgfx::LGFX_Device {
    lgfx::Panel_ST7789 _panel_instance;
    lgfx::Bus_SPI       _bus_instance;

    Vector2i size = Vector2i(240, 240);

    public:
        Display();

        void display_init();

        Vector2i getSize();
};

#endif