#include <display/impl/scan_finger.scene.h>

#include <Images.h>
#include <Font.h>
#include <Math.h>
#include <Fingerprint.h>

ScanFingerScene::ScanFingerScene(Display *display, Sprite *buffer, Fingerprint *fingerprint) : Scene(display, buffer), scanFingerSprite(buffer, Vector2i(scanFingerWidth, scanFingerHeight)) {

    scanFingerSprite.initSprite(true);

    scanFingerSprite.writeImage(scanFinger);
    scanFingerSprite.position = Vector2i(display->getSize().x / 2, scanFingerSprite.size.y / 2 + 4);

}

void ScanFingerScene::setup() {

    buffer->fillSprite(TFT_BLACK);

    int centerX = display->getSize().x / 2;
    int posY = (display->getSize().y / 1.5);

    buffer->drawString("Отсканируйте палец", centerX, posY + 21);
    buffer->drawString("Режим определения", centerX, posY + 46);

    scanFingerSprite.pushTransformed(buffer, ST_WITHOUT_ROTATION | ST_WITHOUT_SCALING);

    buffer->pushSprite(0, 0);
    display->display();
}

void ScanFingerScene::draw() {



}

bool ScanFingerScene::buttonRelease() { return false; }