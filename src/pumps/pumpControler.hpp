#include "pins/pinsControler.hpp"

// Set LED_BUILTIN if it is not defined by Arduino framework
// #define LED_BUILTIN 2

#define PIN_BUTTON_GELB D11
#define PIN_BUTTON_BLAU D12
#define PIN_BUTTON_ROT D13
#define PIN_BUTTON_SCHWARZ D10

#define PIN_PUMP1_LEFT D2
#define PIN_PUMP1_RIGHT D3
#define PIN_PUMP2_LEFT D4
#define PIN_PUMP2_RIGHT D5
#define PIN_PUMP3_LEFT D6
#define PIN_PUMP3_RIGHT D7

int getPumpPin(int pump, bool left);

void incPumpPWM(int pump, int value);

void decPumpPWM(int pump, int value);

void setPump(int pump);

void togglePump(int pump);

void toggleDirection(int pump);