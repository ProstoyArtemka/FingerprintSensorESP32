#ifndef SPRITE_H
#define SPRITE_H

#include <Arduino.h>
#include <LovyanGFX.h>
#include <Math.h>
#include <display/display.h>

const int ST_WITHOUT_POSITION = 0b001;
const int ST_WITHOUT_ROTATION = 0b010;
const int ST_WITHOUT_SCALING  = 0b100;

class Sprite : public LGFX_Sprite {

    public:
        Vector2i size;

        Vector2i position = Vector2i(0, 0);
        Vector2f scale = Vector2f(1, 1);
        int rotation;

        LovyanGFX *parent;

        Sprite();
        Sprite(LovyanGFX *parent, Vector2i size);

        void initSprite(bool centered);

        void pushTransformed(LovyanGFX *dst);
        void pushTransformed(LovyanGFX *dst, int spriteTransformationFlags);

        void writeImage(const uint16_t *data);

        Vector2f getScaledSize();
};

#endif