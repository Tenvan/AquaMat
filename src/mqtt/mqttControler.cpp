#include <stdexcept>

#include <ArduinoLog.h>

#include <WiFi.h>
#include <PubSubClient.h>

#include "pins/pinsControler.hpp"
#include "ssd1306/ssd1306Controler.hpp"
#include "pumps/pumpControler.hpp"

using std::runtime_error;

// *****************************************************
// MQTT Setup

WiFiClient espClient;
PubSubClient client(espClient);

long lastMsg = 0;
char msg[50];
int value = 0;

float temperature = 0;

// Add your MQTT Broker IP address, example:
// const char* mqtt_server = "192.168.1.144";
//const char *mqtt_server = "broker.emqx.io";
//const char *mqtt_server = "homeassistant.local";
const char *mqtt_server = "192.168.0.112";
const int mqtt_port = 1883;
// const char *mqtt_server = "tenvan.free.mqttserver.eu";
// const int mqtt_port = 8883;

void callback(const char *topic, byte *message, unsigned int length) {
  Log.noticeln("Message arrived on topic: %s", topic);

  String messageTemp;

  for (int i = 0; i < length; i++) {
    messageTemp += (char) message[i];
  }

  stopTicker();
  displayFull.clear();
  displayFull.println("MQTT Msg:");
  displayFull.println(topic);
  delay(1000);

  Log.noticeln("Message: %s", messageTemp.c_str());

  if (String(topic) == "AquaMat/Pump/Active") {
    Log.noticeln("Pumpe 1 %s", messageTemp.c_str());
    displayFull.printf("Pumpe 1 %s", messageTemp.c_str());
    togglePump(1);
  }

  delay(1000);
  startTicker();
}

void reconnect() {
  // Loop until we're reconnected
  while (!client.connected()) {
    stopTicker();

    displayFull.clear();
    displayFull.println("MQTT:");
    displayFull.println(mqtt_server);

    Log.noticeln("Attempting MQTT connection...");
    // Attempt to connect
    if (client.connect("AquaMat", "mqttuser", "Betty74#mqtt")) {
      Log.noticeln("connected");

      displayFull.clear();
      displayFull.println("CONNECT");
      delay(2000);

      // Subscribe
      client.subscribe("AquaMat/Pump/#");
    } else {
      Log.noticeln("failed, rc=%d", client.state());
      Log.noticeln(" try again in 5 seconds");
      delay(5000);
    }

    startTicker();
  }
}

void mqttSetup() {
  Log.traceln("---> MQTT Setup startet");
  try {
    // Init MQTT
    Log.noticeln("MQTT Broker: %s", mqtt_server);
    Log.noticeln("MQTT Port: %d", mqtt_port);

    client.setServer(mqtt_server, mqtt_port);
    client.setCallback(callback);
  }
  catch (const runtime_error &e) {
    Log.noticeln("Exception aufgetreten!" CR "%s", e.what());
  }

  Log.traceln("<--- MQTT Setup startet");
}

void mqttLoop() {
  if (!client.connected()) {
    reconnect();
  }

  client.loop();

  long now = millis();

  if (now - lastMsg > 15000) {
    lastMsg = now;

    // Temperature in Celsius
    temperature = getTemperatur();

    // Convert the value to a char array
    char tempString[8];
    dtostrf(temperature, 1, 2, tempString);
    Log.noticeln("Temperature: %s", tempString);
    client.publish("AquaMat/Temperatur", tempString);

    lastMsg = now;
  }
}
