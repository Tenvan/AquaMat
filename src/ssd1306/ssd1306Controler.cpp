
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include "SSD1306Ascii.h"
#include "SSD1306AsciiWire.h"

#include <WiFi.h>

#include "main.hpp"
#include "ssd1306Controler.hpp"
#include "ssd1306Images.hpp"
#include "pins/pinsControler.hpp"

using std::runtime_error;

const DevType displayDevice = Adafruit128x32;

// const uint8_t* tickerFont = Adafruit5x7;
// const uint8_t* tickerFont = Arial_bold_14;
// const uint8_t* tickerFont = Callibri14;
const uint8_t* tickerFont = fixed_bold10x15;

#define SCREEN_WIDTH displayDevice.lcdWidth   // OLED display width, in pixels
#define SCREEN_HEIGHT displayDevice.lcdHeight // OLED display height, in pixels

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
// On an Arduino UNO:       A4(SDA), A5(SCL)
// On an Arduino MEGA 2560: 20(SDA), 21(SCL)
// On an Arduino LEONARDO:   2(SDA),  3(SCL), ...
#define OLED_RESET 4        // Reset pin # (or -1 if sharing Arduino reset pin)
#define SCREEN_ADDRESS 0x3C ///< See datasheet for Address; 0x3D for 128x64, 0x3C for 128x32

// Try values of zero or one for RTN_CHECK.
#define RTN_CHECK 1

SSD1306AsciiWire tickerTop;
SSD1306AsciiWire tickerBottom;

uint32_t tickTime = 0;

// Ticker state. Maintains text pointer queue and current ticker state.
TickerState stateTickerTop;
int lineTop = 0;
TickerState stateTickerBottom;
int lineBottom = 0;

#define TICKER1_LINES 4
#define TICKER2_LINES 2

String textTop;
String textBottom;

void asciiLoop()
{
  if (tickTime <= millis())
  {
    tickTime = millis() + 30;

    // Should check for error. rtn < 0 indicates error.
    auto rtnTop = tickerTop.tickerTick(&stateTickerTop);
    auto rtnBottom = tickerBottom.tickerTick(&stateTickerBottom);

    if (rtnTop <= RTN_CHECK)
    {
      if (!tickerTop.tickerText(&stateTickerTop, textTop))
      {
        printf("Fehler im Ticker Top aufgetreten!");
      }
    }

    if (rtnBottom <= RTN_CHECK)
    {
      textBottom = "Pumpen: " + String(getPumpen()) + " * Temperatur: " + String(getTemperatur(), 1) + " Grad Celsius";

      if (!tickerBottom.tickerText(&stateTickerBottom, textBottom))
      {
        printf("Fehler im Ticker Bottom aufgetreten!");
      }
    }
  }
}

void asciiPreSetup()
{
  Wire.begin();
  Wire.setClock(400000L);

#if OLED_RESET >= 0
  tickerTop.begin(&displayDevice, SCREEN_ADDRESS, OLED_RESET);
  tickerBottom.begin(&displayDevice, SCREEN_ADDRESS, OLED_RESET);
#else
  tickerTop.begin(&displayDevice, SCREEN_ADDRESS);
  tickerBottom.begin(&displayDevice, SCREEN_ADDRESS);
#endif

  // Use Adafruit5x7, field at row 1, set2X, columns 0 through 128.
  tickerTop.tickerInit(&stateTickerTop, tickerFont, 0, false, POS1, SCREEN_WIDTH);
  tickerBottom.tickerInit(&stateTickerBottom, tickerFont, 2, false, POS1, SCREEN_WIDTH);

  tickerTop.clear();
  tickerBottom.clear();

  printf("\nDisplay Diagnose:\n");
  printf("----> Display\n");
  printf("Screen Width %d Height: %d\n", SCREEN_WIDTH, SCREEN_HEIGHT);
  printf("Display Width %d Height: %d Size: %d ColOffset: %d\n", displayDevice.lcdWidth, displayDevice.lcdHeight, displayDevice.initSize, displayDevice.colOffset);
  printf("<---- Display\n");
  printf("----> Ticker Top\n");
  printf("DisplayRows %d FontRows: %d\n", tickerTop.displayRows(), tickerTop.fontRows());
  printf("<---- Ticker Top\n");
  printf("----> Ticker Bottom\n");
  printf("DisplayRows %d FontRows: %d\n", tickerBottom.displayRows(), tickerBottom.fontRows());
  printf("<---- Ticker Bottom\n");
}

void asciiPostSetup()
{
  /**
   * @brief Ticker Top Texte hier definieren, da diese statisch sind.
   *
   */
  textTop = "AquaMat " + String(VERSION) + " * (c) 2022 Ralf Stich * WLAN SSID: " + String(WiFi.SSID()) + " * IP: " + String(WiFi.localIP());
  printf("Top Ticker Text: %s\n", textTop.c_str());

  textBottom = "Pumpen: " + String(getPumpen()) + " * Temperatur: " + String(getTemperatur());
  printf("Bottom Ticker Text: %s\n", textBottom.c_str());
}

void screenPreSetup()
{
  printf("\n---> Screen Pre Setup startet\n");
  try
  {
    asciiPreSetup();
  }
  catch (const runtime_error &e)
  {
    printf("Exception aufgetreten!\n%s", e.what());
  }

  printf("\n<--- Screen Pre Setup fertig\n");
}

void screenPostSetup()
{
  printf("\n---> Screen Post Setup startet\n");
  try
  {
    asciiPostSetup();
  }
  catch (const runtime_error &e)
  {
    printf("Exception aufgetreten!\n%s", e.what());
  }

  printf("\n<--- Screen Post Setup fertig\n");
}
