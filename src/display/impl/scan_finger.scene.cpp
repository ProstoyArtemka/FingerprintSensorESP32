#include <display/impl/scan_finger.scene.h>

#include <Images.h>
#include <Font.h>
#include <Math.h>
#include <Fingerprint.h>

ScanFingerScene::ScanFingerScene(Display *display, Sprite *buffer, Fingerprint *fingerprint) : Scene(display, buffer), scanFingerSprite(buffer, Vector2i(scanFingerWidth, scanFingerHeight)), fingerprint(fingerprint) {

    scanFingerSprite.initSprite(true);

    scanFingerSprite.writeImage(scanFinger);
    scanFingerSprite.position = Vector2i(display->getSize().x / 2, scanFingerSprite.size.y / 2 + 4);

}

void ScanFingerScene::setup() {}

void ScanFingerScene::drawText( int fingerprintID) {

    int centerX = display->getSize().x / 2;
    int posY = (display->getSize().y / 1.5);

    if (fingerprintID == -1) {
        buffer->drawString("Отсканируйте палец", centerX, posY);
        buffer->drawString("режим определения", centerX, posY + 25);

        return;
    }

    if (fingerprintID == -2) {
        buffer->setColor(TFT_RED);

        buffer->drawString("Отпечаток не найден", centerX, posY);
        buffer->drawString("в памяти", centerX, posY + 25);

        buffer->setColor(TFT_WHITE);

        return;
    }

    buffer->setColor(TFT_BLUE);
    buffer->drawString("Отпечаток найден!", centerX, posY);
    buffer->setColor(TFT_WHITE);


    char str[40];
    sprintf(str, "номер: %d", fingerprintID);
    buffer->drawString(str, centerX, posY + 25);

}

void ScanFingerScene::draw() {

    buffer->fillSprite(TFT_BLACK);

    if (millis() - lastGotID >= 300 + scanDelay) {
        
        this->fingerprintID = this->fingerprint->scanFingerprint();

        lastGotID = millis();
        scanDelay = (this->fingerprintID == -1) ? 0 : 2000;
    }

    drawText(this->fingerprintID);

    scanFingerSprite.pushTransformed(buffer, ST_WITHOUT_ROTATION | ST_WITHOUT_SCALING);

    buffer->pushSprite(0, 0);
    display->display();

}

bool ScanFingerScene::buttonRelease() { return false; }