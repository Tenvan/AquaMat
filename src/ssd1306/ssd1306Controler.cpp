#include <stdexcept>

#include "SSD1306Ascii.h"
#include "SSD1306AsciiWire.h"

#include <WiFi.h>

#include "main.hpp"
#include "ssd1306Controler.hpp"
#include "ssd1306Images.hpp"
#include "pins/pinsControler.hpp"
#include "ArduinoLog.h"

using std::runtime_error;

const DevType displayDevice = Adafruit128x32;

// const uint8_t* systemFont = Adafruit5x7;
const uint8_t *systemFont = fixed_bold10x15;

#define SCREEN_WIDTH displayDevice.lcdWidth   // OLED display width, in pixels
#define SCREEN_HEIGHT displayDevice.lcdHeight // OLED display height, in pixels

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

SSD1306AsciiWire displayLineTop;
SSD1306AsciiWire displayLineBottom;
SSD1306AsciiWire displayFull;

bool tickerActive = true;

uint32_t tickTime = 0;

// Ticker state. Maintains text pointer queue and current ticker state.
TickerState stateTickerTop;
TickerState stateTickerBottom;

String textTop;
String textBottom;

void asciiLoop() {
  if (tickerActive && tickTime <= millis()) {
    tickTime = millis() + 30;

    // Should check for error. rtn < 0 indicates error.
    auto rtnTop = displayLineTop.tickerTick(&stateTickerTop);
    auto rtnBottom = displayLineBottom.tickerTick(&stateTickerBottom);

    if (rtnTop <= RTN_CHECK) {
      if (!displayLineTop.tickerText(&stateTickerTop, textTop)) {
        Log.noticeln("Fehler im Ticker Top aufgetreten!");
      }
    }

    if (rtnBottom <= RTN_CHECK) {
      textBottom = "Pumpen: " + String(getPumpen()) + " * Temperatur: " + String(getTemperatur(), 1) + " Grad Celsius";

      if (!displayLineBottom.tickerText(&stateTickerBottom, textBottom)) {
        Log.noticeln("Fehler im Ticker Bottom aufgetreten!");
      }
    }
  }
}

void asciiPreSetup() {
  Wire.begin();
  Wire.setClock(400000L);

#if OLED_RESET >= 0
  displayLineTop.begin(&displayDevice, SCREEN_ADDRESS, OLED_RESET);
  displayLineBottom.begin(&displayDevice, SCREEN_ADDRESS, OLED_RESET);
  displayFull.begin(&displayDevice, SCREEN_ADDRESS, OLED_RESET);
#else
  displayLineTop.begin(&displayDevice, SCREEN_ADDRESS);
  displayLineBottom.begin(&displayDevice, SCREEN_ADDRESS);
  displayFull.begin(&displayDevice, SCREEN_ADDRESS);
#endif

  // Use Adafruit5x7, field at row 1, set2X, columns 0 through 128.
  displayLineTop.tickerInit(&stateTickerTop, systemFont, 0, false, POS1, SCREEN_WIDTH);
  displayLineBottom.tickerInit(&stateTickerBottom, systemFont, 2, false, POS1, SCREEN_WIDTH);
  displayFull.setFont(systemFont);

  displayLineTop.clear();
  displayLineBottom.clear();
  displayLineTop.println("OLED LINE 1");
  displayLineBottom.println("OLED LINE 2");
}

void asciiPostSetup() {
  /**
   * @brief Ticker Top Texte hier definieren, da diese statisch sind.
   *
   */
  textTop = "AquaMat " + String(VERSION) + " * (c) 2022 Ralf Stich * WLAN SSID: " + String(WiFi.SSID()) + " * IP: " +
            String(WiFi.localIP()) + " ";
  Log.noticeln("Top Ticker Text: %s", textTop.c_str());

  textBottom = "Pumpen: " + String(getPumpen()) + " * Temperatur: " + String(getTemperatur()) + " ";
  Log.noticeln("Bottom Ticker Text: %s", textBottom.c_str());
}

void stopTicker() {
  tickerActive = false;
  displayLineTop.clear();
  displayLineBottom.clear();
}

void startTicker() {
  displayLineTop.clear();
  displayLineBottom.clear();
  tickerActive = true;
}

void screenPreSetup() {
  Log.noticeln("---> Screen Pre Setup startet");
  try {
    asciiPreSetup();
  }
  catch (const runtime_error &e) {
    Log.noticeln("Exception aufgetreten!" CR "%s", e.what());
  }

  Log.noticeln("<--- Screen Pre Setup fertig");
}

void screenPostSetup() {
  Log.noticeln("---> Screen Post Setup startet");
  try {
    asciiPostSetup();
  }
  catch (const runtime_error &e) {
    Log.noticeln("Exception aufgetreten!" CR "%s", e.what());
  }

  Log.noticeln("<--- Screen Post Setup fertig");
}
