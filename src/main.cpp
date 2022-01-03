#include <Arduino.h>
#include <stdexcept>

#include "main.hpp"
#include "logger.hpp"
#include "ssd1306/ssd1306Controler.hpp"
#include "ota/otaControler.hpp"
#include "mqtt/mqttControler.hpp"
#include "wifi/wifiControler.hpp"
#include "pins/pinsControler.hpp"
#include "ArduinoLog.h"

using std::runtime_error;

void setup() {
  setupLogger();

  /* Print chip information */
  esp_chip_info_t chip_info;
  esp_chip_info(&chip_info);

  Log.info("This is ESP32 chip with %d CPU cores, WiFi%s%s, ",
           chip_info.cores,
           (chip_info.features & CHIP_FEATURE_BT) ? "/BT" : "",
           (chip_info.features & CHIP_FEATURE_BLE) ? "/BLE" : "");

  Log.info("silicon revision %d, ", chip_info.revision);

  Log.infoln("%dMB %s flash", spi_flash_get_chip_size() / (1024 * 1024),
             (chip_info.features & CHIP_FEATURE_EMB_FLASH) ? "embedded" : "external");

  Log.infoln("AquaMAt Version %s wird geladen.", VERSION);

  // Init Screen Hardware
  screenPreSetup();

  // Init WIFI
  setup_wifi();

  // Init MQTT
  mqttSetup();

  // Init OTA
  setup_basic_ota();
  setup_elegant_ota();

  // Init Pins
  pinsSetup();

  // Init Screen Ticker
  screenPostSetup();

  Log.noticeln("Setup komplett.");
}

void loop() {
  otaLoop();

  pinsLoop();

  mqttLoop();

  asciiLoop();

  delay(10);
}
