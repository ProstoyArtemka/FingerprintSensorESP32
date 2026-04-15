#include <display/impl/main_menu.scene.h>

#include <Images.h>
#include <Font.h>
#include <Math.h>

MainMenuScene::MainMenuScene(Display *display, Sprite *buffer) : Scene(display, buffer), okSprite(Sprite(buffer, Vector2i(okWidth, okHeight))) {

    okSprite.initSprite(true);
    
    okSprite.writeImage(ok);
    okSprite.position = Vector2i(display->getSize().x / 2, okSprite.size.y / 2 + 15);

}

void MainMenuScene::setup() {

    buffer->fillSprite(TFT_BLACK);

    int centerX = display->getSize().x / 2;
    int posY = (display->getSize().y / 1.5);

    buffer->drawString("Сенсор найден!", centerX, posY + 5);
    buffer->drawString("Всё готово к работе", centerX, posY + 31);

    okSprite.pushTransformed(buffer, ST_WITHOUT_ROTATION | ST_WITHOUT_SCALING);

    buffer->pushSprite(0, 0);
    display->display();
}

void MainMenuScene::draw() {


}

bool MainMenuScene::buttonRelease() { return false; }