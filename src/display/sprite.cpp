#include <display/sprite.h>
#include <display/display.h>

#include <LovyanGFX.h>
#include <Math.h>

Sprite::Sprite() {};
Sprite::Sprite(LovyanGFX *parent, Vector2i size) : LGFX_Sprite(parent), size(size) {}


void Sprite::initSprite(bool centered) {
    this->createSprite(this->size.x, this->size.y);
    this->setSwapBytes(true);

    if (centered) 
        this->setPivot(this->size.x / 2, this->size.y / 2);
}

Vector2f Sprite::getScaledSize() {
    return Vector2f(this->size.x * this->scale.x, this->size.y * this->scale.y);
}

void Sprite::pushTransformed(LovyanGFX *dst) {
    Vector2f leftCornerPos = Vector2f(this->position.x, this->position.y);

    this->pushRotateZoom(dst, leftCornerPos.x, leftCornerPos.y, rotation, this->scale.x, this->scale.y);

}

void Sprite::pushTransformed(LovyanGFX *dst, int flags) {

    Vector2i pos = Vector2i(0 ,0);
    Vector2f scale = Vector2f(1, 1);
    float rotation = 0;

    if ((flags & (1 << 0)) == 0) { // WITH POSITION
        pos = this->position;
    }

    if ((flags & (1 << 1)) == 0) { // WITH ROTATION
        rotation = this->rotation;
    }

    if ((flags & (1 << 2)) == 0) { // WITH SCALE
        scale = this->scale;
    }

    this->pushRotateZoom(dst, pos.x, pos.y, rotation, scale.x, scale.y);

}

void Sprite::writeImage(const uint16_t *data) {
    pushImage(0, 0, this->size.x, this->size.y, data);
}