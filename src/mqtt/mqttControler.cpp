#include <PubSubClient.h>

#include <WiFi.h>
#include <PubSubClient.h>

// *****************************************************
// MQTT Setup

WiFiClient espClient;
PubSubClient client(espClient);

long lastMsg = 0;
char msg[50];
int value = 0;

float temperature = 0;
float humidity = 0;

// Add your MQTT Broker IP address, example:
// const char* mqtt_server = "192.168.1.144";
const char *mqtt_server = "broker.emqx.io";
const int mqtt_port = 1883;
// const char *mqtt_server = "tenvan.free.mqttserver.eu";
// const int mqtt_port = 8883;

void callback(char *topic, byte *message, unsigned int length)
{
  Serial.print("Message arrived on topic: ");
  Serial.print(topic);
  Serial.print(". Message: ");

  String messageTemp;

  for (int i = 0; i < length; i++)
  {
    Serial.print((char)message[i]);
    messageTemp += (char)message[i];
  }
  Serial.println();

  // Feel free to add more if statements to control more GPIOs with MQTT

  // If a message is received on the topic esp32/output, you check if the message is either "on" or "off".
  // Changes the output state according to the message
  if (String(topic) == "AquaMat/Pump/1")
  {
    Serial.print("Pumpe 1 ");
    Serial.println(messageTemp);
  }
}

void reconnect()
{
  // Loop until we're reconnected
  while (!client.connected())
  {
    Serial.print("Attempting MQTT connection...");
    // Attempt to connect
    if (client.connect("AquaMat"))
    {
      Serial.println("connected");
      // Subscribe
      client.subscribe("AquaMat/Pumpe/#");
    }
    else
    {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      // Wait 5 seconds before retrying
      delay(5000);
    }
  }
}

void mqttSetup()
{
  // Init MQTT
  Serial.printf("MQTT Broker: %s\n", mqtt_server);
  Serial.printf("MQTT Port: %d\n", mqtt_port);

  client.setServer(mqtt_server, mqtt_port);
  client.setCallback(callback);

  Serial.println("MQTT done");
}

void mqttLoop()
{
  if (!client.connected())
  {
    reconnect();
  }

  client.loop();

  auto now = millis();

  if (now - lastMsg > 15000)
  {
    lastMsg = now;

    // Temperature in Celsius
    temperature = random(20, 30);

    // Convert the value to a char array
    char tempString[8];
    dtostrf(temperature, 1, 2, tempString);
    Serial.print("Temperature: ");
    Serial.println(tempString);
    client.publish("AquaMat/Temperatur", tempString);

    lastMsg = now;
  }
}
