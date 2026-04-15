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

Sprite buffer = Sprite(&display, display.getSize());

Button button = Button(40);
SceneHandler sceneHandler = SceneHandler(&display, &buffer, &fingerprint);


void buttonReleased() {
  sceneHandler.buttonRelease();
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

  display.display_init();
  buffer.initSprite(false);

  buffer.setTextDatum(middle_center);
  buffer.setTextSize(0.75);
  buffer.loadFont(Inter_28);

}

void sensor() {
  if (!sceneHandler.isScene(3, MAIN_SCENE, EMPTY_SCENE, SENSOR_NOT_FOUND_SCENE)) return;

  if (millis() - lastCheckedSensor >= 250 && (sceneHandler.isScene(2, MAIN_SCENE, EMPTY_SCENE))) {
    fingerprint.retry();

    lastCheckedSensor = millis();
  }

  if (!fingerprint.isEnabled()) {
    sceneHandler.changeScene(SENSOR_NOT_FOUND_SCENE, false);

    return;
  }

  if (fingerprint.isEnabled()) {
    sceneHandler.changeScene(MAIN_SCENE, false);

    return;
  }

}

void loop() {

  sensor();

  sceneHandler.tick();
  button.tick();

}
