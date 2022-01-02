#include <stdexcept>

#include "wifiControler.hpp"

using std::runtime_error;

const char *ssid = WIFI_SSID;
const char *pass = WIFI_PW;

void setup_wifi() {
  printf("\n---> Wifi Setup startet\n");

  try {
    // We start by connecting to a WiFi network
    Serial.println();
    Serial.print("Verbindung zu ");
    Serial.println(ssid);

    WiFi.mode(WIFI_STA);
    WiFi.begin(ssid, pass);

    while (WiFi.status() != WL_CONNECTED) {
      delay(500);
      Serial.print(".");
    }

    Serial.println("");
    Serial.print("Verbindung zu.: ");
    Serial.println(ssid);
    Serial.print("IP Adresse....: ");
    Serial.println(WiFi.localIP());
  }
  catch (const runtime_error &e) {
    printf("Exception aufgetreten!\n%s\n", e.what());
  }

  printf("\n<--- Wifi Setup fertig\n");
}
