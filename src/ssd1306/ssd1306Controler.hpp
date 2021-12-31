#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

void screenPreSetup();
void screenPostSetup();
void screenLoop();

void asciiPostSetup();
void asciiPreSetup();
void asciiLoop();

Adafruit_SSD1306 *getDisplay();