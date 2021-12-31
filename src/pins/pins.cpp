#include <Arduino.h>
#include "main.hpp"
#include "pins.hpp"

void pinsSetup()
{
    pinMode(LED_BUILTIN, OUTPUT);

    pinMode(PIN_PUMP1, OUTPUT);
    pinMode(PIN_PUMP2, OUTPUT);
    pinMode(PIN_PUMP3, OUTPUT);

    pinMode(PIN_BUTTON1, INPUT_PULLUP);
    pinMode(PIN_BUTTON2, INPUT_PULLUP);
    pinMode(PIN_BUTTON3, INPUT_PULLUP);

    Serial.println("Pin done");

    Serial.println("Pins Setup fertig.");
}

long lastPin = 0;

void pinsLoop()
{
    long now = millis();

    if (now - lastPin > 500)
    {
        auto button1 = digitalRead(PIN_BUTTON1);
        auto button2 = digitalRead(PIN_BUTTON2);
        auto button3 = digitalRead(PIN_BUTTON3);

        printf("Buttons -> Gelb: %d / Blau: %d / Rot %d\n", button1, button2, button3);

        digitalWrite(PIN_PUMP1, 1 - button1);
        digitalWrite(PIN_PUMP2, 1 - button2);
        digitalWrite(PIN_PUMP3, 1 - button3);

        lastPin = now;
    }
}
