#include <display/impl/add_finger.scene.h>

#include <Images.h>
#include <Font.h>
#include <Math.h>

AddFingerScene::AddFingerScene(Display *display, Sprite *buffer, Fingerprint *fingerprint) : Scene(display, buffer), addFingerSprite(buffer, Vector2i(addFingerWidth, addFingerHeight)), fingerprint(fingerprint) {

    addFingerSprite.initSprite(true);
    addFingerSprite.writeImage(addFinger);

    addFingerSprite.position = Vector2i(display->getSize().x / 2, addFingerSprite.size.y / 2 + 4);

}

void AddFingerScene::setup() {}

void AddFingerScene::drawText() {
    int centerX = display->getSize().x / 2;
    int posY = (display->getSize().y / 1.5);
    char str[40];

    if (removedFingerprints) {
        buffer->setTextColor(TFT_RED);

        buffer->drawString("Все отпечатки", centerX, posY);
        buffer->drawString("удалены", centerX, posY + 25);
        
        buffer->setTextColor(TFT_WHITE);

        return;
    }

    if (step == -3) {
        buffer->setTextColor(TFT_GREEN);
        
        buffer->drawString("Успех!", centerX, posY);
        buffer->drawString("Отпечаток сохранён", centerX, posY + 25);
        
        sprintf(str, "Под номером %d", this->fingerprint->getLastId() - 1);
        buffer->drawString(str, centerX, posY + 50);

        buffer->setTextColor(TFT_WHITE);

        return;
    }

    if (step == -2) {
        buffer->setTextColor(TFT_RED);

        buffer->drawString("Ошибка!", centerX, posY);
        buffer->drawString("Не удалось", centerX, posY + 25);
        buffer->drawString("сохранить", centerX, posY + 50);
        
        buffer->setTextColor(TFT_WHITE);

        return;
    }

    if (step == -1) {
        buffer->setTextColor(TFT_RED);

        buffer->drawString("Ошибка!", centerX, posY);
        buffer->drawString("Отпечатки не", centerX, posY + 25);
        buffer->drawString("совпали", centerX, posY + 50);

        buffer->setTextColor(TFT_WHITE);

        return;
    }

    if (step == 0) {
        buffer->drawString("Отсканируйте палец", centerX, posY);
        buffer->drawString("режим добавления", centerX, posY + 25);

        sprintf(str, "Номер отпечатка: %d", fingerprint->getLastId());
        buffer->drawString(str, centerX, posY + 50);

        return;
    }

    if (step == 1) {
        buffer->drawString("Уберите палец", centerX, posY);

        return;
    }

    if (step == 2) {
        buffer->drawString("Приложите тот", centerX, posY);
        buffer->drawString("же палец", centerX, posY + 25);

        return;
    }

}

void AddFingerScene::processSensor() {
 
    if (millis() - lastFingerprintCheck <= 500 + checKDelay) return;
    if (addedFingerprint) return;

    lastFingerprintCheck = millis();
    checKDelay = 0;
    if (step < 0) step = 0;

    FPMStatus status;

    if (step == 0) {
        status = fingerprint->getImage();
        if (status != FPMStatus::OK) return;

        status = fingerprint->image2Tz(1);
        if (status != FPMStatus::OK) return;

        step = 1;
        checKDelay += 1000;

        return;
    }

    if (step == 1) {
        status = fingerprint->getImage();
        if (status != FPMStatus::NOFINGER) return;

        step = 2;
        checKDelay += 1000;

        return;
    }

    if (step == 2) {
        status = fingerprint->getImage();
        if (status != FPMStatus::OK) return;

        fingerprint->saveToLittleFS("/currentFinger.raw");

        status = fingerprint->image2Tz(2);
        if (status != FPMStatus::OK) return;

        status = fingerprint->createModel();
        if (status != FPMStatus::OK) {
            step = -1;
            checKDelay += 2000;    
            
            return;
        }

        status = fingerprint->storeModel(fingerprint->getLastId(), 1);
        fingerprint->incrementLastId();

        if (status != FPMStatus::OK) {
            step = -2;
            checKDelay += 2000;
            
            return;
        }

        step = -3;
        checKDelay += 1000;
        addedFingerprint = true;

        return;
    }
    
}

void AddFingerScene::draw() {
    buffer->fillSprite(TFT_BLACK);

    addFingerSprite.pushTransformed(buffer, ST_WITHOUT_ROTATION | ST_WITHOUT_SCALING);

    drawText();
    processSensor();

    buffer->pushSprite(0, 0);
    display->display();

    display->display();
}

bool AddFingerScene::buttonRelease() { 
    step = 0;

    if (addedFingerprint) {
        addedFingerprint = false;

        return true;
    }

    if (removedFingerprints) {
        removedFingerprints = false;

        return true;
    }

    return false; 
}