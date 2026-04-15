#include <display/impl/empty.scene.h>

#include <Images.h>
#include <Font.h>
#include <Math.h>

EmptyScene::EmptyScene(Display *display, Sprite *buffer) : Scene(display, buffer) {}

void EmptyScene::setup() {
    display->fillScreen(TFT_BLACK);
    display->display();
}

void EmptyScene::draw() {}
bool EmptyScene::buttonRelease() { return false; }