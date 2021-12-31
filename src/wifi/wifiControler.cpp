#include "wifiControler.hpp"

const char *ssid = WIFI_SSID;
const char *pass = WIFI_PW;

void setup_wifi()
{
  delay(10);

  // We start by connecting to a WiFi network
  Serial.println();
  Serial.print("Verbindung zu ");
  Serial.println(ssid);

  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, pass);

  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.print("Verbindung zu..: ");
  Serial.println(ssid);
  Serial.print("IP Addresse....: ");
  Serial.println(WiFi.localIP());

  Serial.println("Wifi Setup fertig");
}
