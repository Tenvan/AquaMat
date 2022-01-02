#include "Arduino.h"
#include <analogWrite.h>

#include "main.hpp"
#include "pumpControler.hpp"

#define PWM_MAX 500

enum Direction {
  LEFT,
  RIGHT
};

auto pumpPWM = new int[3]{0, 0, 0};
auto pumpActive = new bool[3]{false, false, false};
auto pumpDirection = new Direction[3]{RIGHT, RIGHT, RIGHT};

void incPumpPWM(int pump, int value) {
  pumpPWM[pump - 1] = min(pumpPWM[pump - 1] + value, PWM_MAX);
  printf("Pumpen Power erhöht: %d\n", pumpPWM[pump - 1]);
  setPump(pump);
}

void decPumpPWM(int pump, int value) {
  pumpPWM[pump - 1] = max(pumpPWM[pump - 1] - value, 0);
  printf("Pumpen Power gesenkt: %d\n", pumpPWM[pump - 1]);
  setPump(pump);
}

int getPumpPin(int pump, bool left) {
  switch (pump) {
    case 1:
      return left ? PIN_PUMP1_LEFT : PIN_PUMP1_RIGHT;

    case 2:
      return left ? PIN_PUMP2_LEFT : PIN_PUMP2_RIGHT;

    case 3:
      return left ? PIN_PUMP3_LEFT : PIN_PUMP3_RIGHT;
  }

  return 0;
}

void togglePump(int pump) {
  pumpActive[pump - 1] = !pumpActive[pump - 1];
  printf("Motor geschaltet: %s\n", pumpActive[pump - 1] ? "EIN" : "AUS");
  setPump(pump);
}

void toggleDirection(int pump) {
  pumpDirection[pump - 1] = pumpDirection[pump - 1] == LEFT ? RIGHT : LEFT;
  printf("Motor Drehrichtung geändert: %s\n", pumpDirection[pump - 1] == LEFT ? "LEFT" : "RIGHT");
  setPump(pump);
}

void setPump(int pump) {
  auto pinLeft = getPumpPin(pump, true);
  auto pinRight = getPumpPin(pump, false);

  if (pinLeft <= 0 || pinRight <= 0) {
    printf("Ungültige Pumpe (%d) oder Pin (L:%d R:%d)\n", pump, pinLeft, pinRight);
  }

  printf("Pumpe %d (Pin: %d): %s -> PWM: %d/%d\n",
         pump,
         pinLeft,
         pumpActive[pump - 1] ? "EIN" : "AUS",
         pumpPWM[pump - 1],
         PWM_MAX);

  analogWrite(pumpDirection[pump - 1] == LEFT ? pinRight : pinLeft, 0);
  delay(10);
  analogWrite(pumpDirection[pump - 1] == LEFT ? pinLeft : pinRight,
              pumpActive[pump - 1] ? pumpPWM[pump - 1] : 0,
              PWM_MAX);
  delay(10);
}
