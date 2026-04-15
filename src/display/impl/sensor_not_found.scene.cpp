#include <display/impl/sensor_not_found.scene.h>

#include <Images.h>
#include <Font.h>
#include <Math.h>

SensorNotFoundScene::SensorNotFoundScene(Display *display, Sprite *buffer) : Scene(display, buffer), angrySprite(Sprite(buffer, Vector2i(angryWidth, angryHeight))) {

    angrySprite.initSprite(true);

    angrySprite.writeImage(angry);
    angrySprite.position = Vector2i(display->getSize().x / 2, angrySprite.size.y / 2 + 15);

}

void SensorNotFoundScene::setup() {

    buffer->clear();

    buffer->drawString("Сенсор не найден...", display->getSize().x / 2, (display->getSize().y / 1.5) + 5);
    angrySprite.pushTransformed(buffer, ST_WITHOUT_ROTATION | ST_WITHOUT_SCALING);

    buffer->pushSprite(0, 0);
    display->display();
}

void SensorNotFoundScene::draw() {


}

bool SensorNotFoundScene::buttonRelease() { return false; }