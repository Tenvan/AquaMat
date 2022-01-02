#include <Arduino.h>
#include <stdexcept>

using std::runtime_error;

#include "main.hpp"
#include "pinsControler.hpp"
#include "pumps/pumpControler.hpp"

enum Buttons {
  GELB,
  BLAU,
  ROT,
  SCHWARZ
};

/**
 * @brief Gibt die Anzahl der konfigurierten Pumpen zurück
 *
 * @return int
 */
int getPumpen() {
  return 3;
}

long lastTemperaturRefresh;
double currentTemperatur;

double getTemperatur() {
  auto now = millis();

  if (now - lastTemperaturRefresh > 5000) {
    lastTemperaturRefresh = now;
    currentTemperatur = random(15, 34);
  }
  return currentTemperatur;
}

void pinsSetup() {
  printf("\n---> Pins Setup startet\n");

  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, HIGH);

  pinMode(PIN_PUMP1_LEFT, OUTPUT);
  pinMode(PIN_PUMP1_RIGHT, OUTPUT);
  pinMode(PIN_PUMP2_LEFT, OUTPUT);
  pinMode(PIN_PUMP2_RIGHT, OUTPUT);
  pinMode(PIN_PUMP3_LEFT, OUTPUT);
  pinMode(PIN_PUMP3_RIGHT, OUTPUT);
  pinMode(GPIO_NUM_39, OUTPUT);

  pinMode(PIN_BUTTON_GELB, INPUT_PULLUP);
  pinMode(PIN_BUTTON_BLAU, INPUT_PULLUP);
  pinMode(PIN_BUTTON_ROT, INPUT_PULLUP);
  pinMode(PIN_BUTTON_SCHWARZ, INPUT_PULLUP);

  Serial.println("Pin done");

  printf("\n<--- Pins Setup fertig\n");
}

String getButtonColor(Buttons button) {
  switch (button) {
    case GELB:
      return "GELB";
      break;
    case BLAU:
      return "BLAU";
      break;
    case ROT:
      return "ROT";
      break;
    case SCHWARZ:
      return "SCHWARZ";
      break;
  }

  return "KEINE";
}

int getButtonPin(Buttons button) {
  switch (button) {
    case GELB:
      return PIN_BUTTON_GELB;

    case BLAU:
      return PIN_BUTTON_BLAU;

    case ROT:
      return PIN_BUTTON_ROT;

    case SCHWARZ:
      return PIN_BUTTON_SCHWARZ;
  }

  return -1;
}

bool getButtonPressed(Buttons button) {
  auto buttonPin = getButtonPin(button);
  int pinValue = digitalRead(buttonPin);
  return pinValue != 1;
}

bool buttonPressed(Buttons button) {
  auto buttonPressed = getButtonPressed(button);

  if (buttonPressed) {
    while (getButtonPressed(button)) {
      delay(10);
    }
    printf("Button %s (%d) gedrückt\n", getButtonColor(button).c_str(), button);
    return true;
  }

  return false;
}

long lastPin = 0;

void pinsLoop() {
  long now = millis();

  if (now - lastPin > 100) {

    try {

      if (buttonPressed(GELB)) {
        togglePump(1);
        togglePump(2);
        togglePump(3);
      }

      if (buttonPressed(BLAU)) {
        incPumpPWM(1, 50);
        incPumpPWM(2, 50);
        incPumpPWM(3, 50);
      }

      if (buttonPressed(ROT)) {
        decPumpPWM(1, 50);
        decPumpPWM(2, 50);
        decPumpPWM(3, 50);
      }

      if (buttonPressed(SCHWARZ)) {
        toggleDirection(1);
        toggleDirection(2);
        toggleDirection(3);
      }
    }
    catch (const runtime_error &e) {
      printf("Exception aufgetreten!\n%s", e.what());
    }

    lastPin = now;
  }
}