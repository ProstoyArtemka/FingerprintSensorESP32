#include <Arduino.h>

#include <Button.h>
#include <Images.h>
#include <Display.h>
#include <Fingerprint.h>
#include <Font.h>

#include <nvs_flash.h>

Preferences prefs;

Display display = Display();
Fingerprint fingerprint = Fingerprint(prefs);
long lastCheckedSensor = 0;
int lastSceneIndex = -1;

Sprite buffer = Sprite(&display, display.getSize());

Button button = Button(40);
SceneHandler sceneHandler = SceneHandler(&display, &buffer, &fingerprint);


void buttonReleased() {
  sceneHandler.buttonRelease();
}

void buttonPressedFor5Seconds() {
  if (!sceneHandler.isScene(ADD_FINGER_SCENE)) return;

  fingerprint.clearFingerprints();

  AddFingerScene* scene = static_cast<AddFingerScene*>(sceneHandler.currentScene);
  if (scene != nullptr) {
    scene->removedFingerprints = true;
  }
}

void setup() {

  Serial.begin(115200);

  // Умная инициализация NVS чтобы сохранять настроечки
  esp_err_t ret = nvs_flash_init();
  if (ret == ESP_ERR_NVS_NO_FREE_PAGES || ret == ESP_ERR_NVS_NEW_VERSION_FOUND) {

    ESP_ERROR_CHECK(nvs_flash_erase());
    ret = nvs_flash_init();
  }

  fingerprint.init();

  button.onRelease(buttonReleased);
  button.buttonPressedFor(5, buttonPressedFor5Seconds);

  display.display_init();
  buffer.initSprite(false);

  buffer.setTextDatum(middle_center);
  buffer.setTextSize(0.75);
  buffer.loadFont(Inter_28);

}

void checkSensorState() {

  if (millis() - lastCheckedSensor >= 500) {
    fingerprint.retry();

    lastCheckedSensor = millis();
  }

  if (fingerprint.isEnabled() && lastSceneIndex != -1) {

    sceneHandler.changeScene((Scenes) lastSceneIndex, false);
    lastSceneIndex = -1;
  }

  if (!fingerprint.isEnabled() && !sceneHandler.isScene(SENSOR_NOT_FOUND_SCENE)) {
    lastSceneIndex = sceneHandler.currentSceneIndex;

    sceneHandler.changeScene(SENSOR_NOT_FOUND_SCENE, false);
  }

}

void loop() {

  checkSensorState();

  sceneHandler.tick();
  button.tick();

}
