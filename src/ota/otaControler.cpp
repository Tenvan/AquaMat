#include <stdexcept>

#include <ArduinoOTA.h>
#include "ESPAsyncWebServer.h"
#include "AsyncElegantOTA.h"
#include "SSD1306Ascii.h"
#include "SSD1306AsciiWire.h"

using std::runtime_error;

#include "main.hpp"
#include "otaControler.hpp"
#include "ssd1306/ssd1306Controler.hpp"
#include "ArduinoLog.h"

#define GREETING "Hallo! Ich bin dein AquaMat mit der Version: "

AsyncWebServer server(80);

void setup_elegant_ota() {
  delay(10);

  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request) {
    request->send(200, "text/plain", String(GREETING) + String(VERSION));
  });

  AsyncElegantOTA.begin(&server);
  server.begin();
  Log.noticeln("HTTP Server gestartet");

  Log.noticeln("Elegant OTA Setup fertig");
}

void setup_basic_ota() {
  Log.traceln("---> Basic OTA Setup startet");

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
          Log.noticeln("Start updating %s", type.c_str());
          stopTicker();
          displayFull.clear();
          displayFull.println("OTA Update");
        })
        .onEnd([]() {
          Log.noticeln("End");
          displayFull.clear();
          displayFull.println("OTA Fertig");
          displayFull.println(":-)");
          delay(1000);
        })
        .onProgress([](unsigned int progress, unsigned int total) {
          Log.noticeln("Progress: %d %%", (progress / (total / 100)));
          displayFull.printf("==> %03u %%\n", (progress / (total / 100)));
        })
        .onError([](ota_error_t error) {
          Log.noticeln("Error[%u]: ", error);

          displayFull.clear();
          displayFull.println("OTA Fehler !");
          displayFull.println(error);
          if (error == OTA_AUTH_ERROR) Log.noticeln("Auth Failed");
          else if (error == OTA_BEGIN_ERROR) Log.noticeln("Begin Failed");
          else if (error == OTA_CONNECT_ERROR) Log.noticeln("Connect Failed");
          else if (error == OTA_RECEIVE_ERROR) Log.noticeln("Receive Failed");
          else if (error == OTA_END_ERROR) Log.noticeln("End Failed");
        });

    ArduinoOTA.begin();
  }
  catch (const runtime_error &e) {
    Log.noticeln("Exception aufgetreten!" CR "%s", e.what());
  }

  Log.traceln("<--- Basic OTA Setup fertig");
}

void otaLoop() {
  ArduinoOTA.handle();
}