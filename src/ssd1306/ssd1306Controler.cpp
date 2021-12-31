
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <WiFi.h>

#include "main.hpp"
#include "ssd1306Controler.hpp"
#include "ssd1306Images.hpp"

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 32 // OLED display height, in pixels

#define LINE1 0 * SCREEN_HEIGHT / 4 // Zeile 1 bei kleinster Auflösung
#define LINE2 1 * SCREEN_HEIGHT / 4 // Zeile 2 bei kleinster Auflösung
#define LINE3 2 * SCREEN_HEIGHT / 4 // Zeile 3 bei kleinster Auflösung
#define LINE4 3 * SCREEN_HEIGHT / 4 // Zeile 4 bei kleinster Auflösung

#define POS1 0 * SCREEN_WIDTH / 4 // Spalte erstes Viertel bei kleinster Auflösung
#define POS2 1 * SCREEN_WIDTH / 4 // Spalte zweites Viertel bei kleinster Auflösung
#define POS3 2 * SCREEN_WIDTH / 4 // Spalte drittes Viertel bei kleinster Auflösung
#define POS4 3 * SCREEN_WIDTH / 4 // Spalte letztes Viertel bei kleinster Auflösung

// Declaration for an SSD1306 display connected to I2C (SDA, SCL pins)
// The pins for I2C are defined by the Wire-library.
// On an arduino UNO:       A4(SDA), A5(SCL)
// On an arduino MEGA 2560: 20(SDA), 21(SCL)
// On an arduino LEONARDO:   2(SDA),  3(SCL), ...
#define OLED_RESET 4        // Reset pin # (or -1 if sharing Arduino reset pin)
#define SCREEN_ADDRESS 0x3C ///< See datasheet for Address; 0x3D for 128x64, 0x3C for 128x32
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

void drawWelcomeScreen()
{
  display.clearDisplay();

  display.setTextSize(3);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(POS1, LINE1);
  display.println(F("AquaMat"));
  display.setTextSize(1);
  display.setCursor(POS2, LINE4);
  display.println(F("Version V1.0"));

  display.display();
}

void drawWifiStatusScreen()
{
  display.clearDisplay();

  display.setTextSize(2);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(POS1, LINE1);
  display.println(F("SSID:"));

  display.setTextSize(1);
  display.setCursor(POS1, LINE3);
  display.println(WiFi.SSID());
  display.display();
  delay(1000);

  display.clearDisplay();
  display.setTextSize(2);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(POS1, LINE1);
  display.println(F("IP:"));

  display.setTextSize(1);
  display.setCursor(POS1, LINE3);
  display.println(WiFi.localIP());
  display.display();
}

void drawStatusScreen()
{
  display.clearDisplay();

  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(POS1, LINE1);
  display.println(F("Temperatur:"));

  display.setTextSize(2);
  display.setCursor(POS2, LINE3);
  display.println("24.5 C");
  display.display();
  delay(1000);

  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(POS1, LINE1);
  display.println(F("Pumpen:"));

  display.setTextSize(4);
  display.setCursor(POS3, LINE1);
  display.println(1);
  display.display();
}

Adafruit_SSD1306 *getDisplay()
{
  return &display;
}

long lastScreen = 0;

bool painted1 = false;
bool painted2 = false;

void screenLoop()
{
  auto now = millis();

  // TODO Dispatcher optimlaer gestalten
  if (now - lastScreen > 3000 && !painted1)
  {
    drawWifiStatusScreen();
    lastScreen = now;
  }

  if (now - lastScreen > 3000 && !painted2)
  {
    drawStatusScreen();
    lastScreen = now;
    painted1 = false;
    painted2 = false;
  }
}

void screenSetup()
{
  // SSD1306_SWITCHCAPVCC = generate display voltage from 3.3V internally
  if (!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS))
  {
    Serial.println(F("SSD1306 Bindung fehlgeschlagen"));
  }

  // Show initial display buffer contents on the screen --
  // the library initializes this with an Adafruit splash screen.
  display.display();

  // Clear the buffer
  display.clearDisplay();

  // Draw a single pixel in white
  display.drawPixel(10, 10, SSD1306_WHITE);

  // Show the display buffer on the screen. You MUST call display() after
  // drawing commands to make them visible on screen!

  drawWelcomeScreen();
  
  Serial.println("Screen Setup fertig");
}
