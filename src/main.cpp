#include <Arduino.h>
#include <analogWrite.h>
#include <iostream>

#include "main.hpp"
#include "ssd1306/ssd1306Controler.hpp"
#include "ota/otaControler.hpp"
#include "mqtt/mqttControler.hpp"
#include "wifi/wifiControler.hpp"
#include "pins/pinsControler.hpp"

using std::runtime_error;

void setup()
{
  Serial.begin(115200);

  /* Print chip information */
  esp_chip_info_t chip_info;
  esp_chip_info(&chip_info);
  
  printf("This is ESP32 chip with %d CPU cores, WiFi%s%s, ",
         chip_info.cores,
         (chip_info.features & CHIP_FEATURE_BT) ? "/BT" : "",
         (chip_info.features & CHIP_FEATURE_BLE) ? "/BLE" : "");

  printf("silicon revision %d, ", chip_info.revision);

  printf("%dMB %s flash\n", spi_flash_get_chip_size() / (1024 * 1024),
         (chip_info.features & CHIP_FEATURE_EMB_FLASH) ? "embedded" : "external");

  printf("\nAquaMAt Version %s wird geladen.\n", VERSION);

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

  printf("Setup komplett.");
}

void loop()
{
  pinsLoop();

  mqttLoop();

  // screenLoop();
  asciiLoop();

  delay(1);
}

void setPump(int pin, bool status)
{
  if (status)
  {
    digitalWrite(pin, HIGH);
    // for (int i = 0; i < 1000; i = i + 10)
    // {
    //   analogWrite(pin, i, 1000);
    //   Serial.printf("Pin: %d Power: %d\n", pin, i);
    //   delay(50);
    // }
  }
  else
  {
    digitalWrite(pin, LOW);
    // analogWrite(pin, 0);
  }
}
