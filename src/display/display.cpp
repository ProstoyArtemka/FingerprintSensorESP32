#include <display/display.h>

#define LGFX_USE_V1
#include <LovyanGFX.h>

Display::Display() {
    auto cfg = _bus_instance.config();

    cfg.spi_host   = SPI2_HOST;
    cfg.spi_mode   = 3;
    cfg.freq_write = 80000000;
    cfg.pin_sclk   = 12;
    cfg.pin_mosi   = 11;
    cfg.pin_dc     = 42;

    _bus_instance.config(cfg);
    _panel_instance.setBus(&_bus_instance);

    auto p_cfg = _panel_instance.config();

    p_cfg.pin_cs       = -1;
    p_cfg.pin_rst      = 41;
    p_cfg.panel_width  = 240;
    p_cfg.panel_height = 240;
    p_cfg.offset_x     = 0;
    p_cfg.offset_y = 82;
    p_cfg.invert       = true;
    _panel_instance.config(p_cfg);

    setPanel(&_panel_instance);
}

void Display::display_init() {
    this->init();

    this->setRotation(0); 

    this->startWrite();
    this->writeCommand(0x36); 
    this->writeData(0xC8); 
    this->endWrite();

    this->setAttribute(lgfx::attribute::utf8_switch, true);

    this->fillScreen(TFT_BLACK);
}

Vector2i Display::getSize() {
    return size;
}