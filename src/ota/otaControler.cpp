#include <stdexcept>

#include <ArduinoOTA.h>
#include "ESPAsyncWebServer.h"
#include "AsyncElegantOTA.h"

using std::runtime_error;

#include "main.hpp"
#include "otaControler.hpp"

#define GREETING "Hallo! Ich bin dein AquaMat mit der Version: "

AsyncWebServer server(80);

void setup_elegant_ota() {
  delay(10);

  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request) {
      request->send(200, "text/plain", String(GREETING) + String(VERSION));
  });

  AsyncElegantOTA.begin(&server);
  server.begin();
  Serial.println("HTTP Server gestartet");

  Serial.println("Elegant OTA Setup fertig");
}

void setup_basic_ota() {
  printf("\n---> Basic OTA Setup startet\n");

  try {

    // Port defaults to 3232
    ArduinoOTA.setPort(3232);

    // Hostname defaults to esp3232-[MAC]
    ArduinoOTA.setHostname("AquaMat");

    // No authentication by default
    // ArduinoOTA.setPassword("admin");

    // Password can be set with it's md5 value as well
    // MD5(admin) = 21232f297a57a5a743894a0e4a801fc3
    // ArduinoOTA.setPasswordHash("21232f297a57a5a743894a0e4a801fc3");

    ArduinoOTA
        .onStart([]() {
            String type;
            if (ArduinoOTA.getCommand() == U_FLASH)
              type = "sketch";
            else // U_SPIFFS
              type = "filesystem";

            // NOTE: if updating SPIFFS this would be the place to unmount SPIFFS using SPIFFS.end()
            Serial.println("Start updating " + type);
        })
        .onEnd([]() { Serial.println("\nEnd"); })
        .onProgress([](unsigned int progress, unsigned int total) {
            Serial.printf("Progress: %u%%\n", (progress / (total / 100)));
        })
        .onError([](ota_error_t error) {
            Serial.printf("Error[%u]: ", error);
            if (error == OTA_AUTH_ERROR) Serial.println("Auth Failed");
            else if (error == OTA_BEGIN_ERROR) Serial.println("Begin Failed");
            else if (error == OTA_CONNECT_ERROR) Serial.println("Connect Failed");
            else if (error == OTA_RECEIVE_ERROR) Serial.println("Receive Failed");
            else if (error == OTA_END_ERROR) Serial.println("End Failed");
        });

    ArduinoOTA.begin();
  }
  catch (const runtime_error &e) {
    printf("Exception aufgetreten!\n%s", e.what());
  }

  printf("\n<--- Basic OTA Setup fertig\n");
}

void otaLoop() {
  ArduinoOTA.handle();
}