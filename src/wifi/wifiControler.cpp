#include <stdexcept>

#include "wifiControler.hpp"
#include "ArduinoLog.h"
#include "ssd1306/ssd1306Controler.hpp"

using std::runtime_error;

const char *ssid = WIFI_SSID;
const char *pass = WIFI_PW;

void setup_wifi() {
  Log.traceln("---> Wifi Setup startet");

  try {
    // We start by connecting to a WiFi network
    displayFull.clear();
    displayFull.println("WLAN ...");
    displayFull.println(ssid);

    Log.info("Verbindung zu ");
    Log.infoln(ssid);

    WiFi.mode(WIFI_STA);
    WiFi.begin(ssid, pass);

    while (WiFi.status() != WL_CONNECTED) {
      delay(2000);
      Log.infoln(".");
    }

    displayFull.clear();
    displayFull.println("CONNECT");

    Log.infoln("");
    Log.noticeln("Verbindung hergestellt: %s", ssid);
    Log.noticeln("IP Adresse............: %s", WiFi.localIP().toString().c_str());

    delay(1000);
  }
  catch (const runtime_error &e) {
    Log.noticeln("Exception aufgetreten!" CR "%s", e.what());
  }

  Log.traceln("<--- Wifi Setup fertig");
}
