#include <display/impl/info.scene.h>

#include <Images.h>
#include <Font.h>
#include <Math.h>
#include <Fingerprint.h>

InfoScene::InfoScene(Display *display, Sprite *buffer, Fingerprint *fingerprint) : Scene(display, buffer), fingerprint(fingerprint), infoSprite(buffer, Vector2i(infoWidth, infoHeight)) {

    infoSprite.initSprite(true);
    infoSprite.writeImage(info);

}

void InfoScene::setup() { }

void InfoScene::draw() {

    buffer->fillSprite(TFT_BLACK);

    infoSprite.position = Vector2i(30);
    infoSprite.pushTransformed(buffer, ST_WITHOUT_ROTATION | ST_WITHOUT_SCALING);

    int centerX = (display->getSize().x / 2);

    buffer->drawString("Информация", centerX + 10, 30);



    char str[60];
    sprintf(str, "Вместимость: %d", fingerprint->getCapacity());
    buffer->drawString(str, centerX, 70);

    sprintf(str, "Кол-во занято: %d", fingerprint->getAmount());
    buffer->drawString(str, centerX, 90);

    buffer->drawString("Номер последнего", centerX, 110);
    sprintf(str, "отпечатка: %d", fingerprint->getLastId());
    buffer->drawString(str, centerX, 130);

    buffer->pushSprite(0, 0);

    display->display();

}

bool InfoScene::buttonRelease() { return false; }