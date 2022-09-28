#include "esphome.h"
#include "display-controler.h"
#include <cstdio>

using namespace display;
using namespace time;
using namespace network;
using namespace homeassistant;
using namespace wifi;

namespace esphome {

  DisplayComponent::DisplayComponent(DisplayBuffer *pDisplay,
                                     Image *pImage,
                                     Font *pFontSmall,
                                     Font *pFontMedium,
                                     Font *pFontLarge) {
    display = pDisplay;
    image = pImage;
    fontSmall = pFontSmall;
    fontMedium = pFontMedium;
    fontLarge = pFontLarge;

    displayHeight = display->get_height();
    displayWidth = display->get_width();

    if (displayHeight <= 32) {
      displayType = SMALL;
      colStart = 0;
      contentLines = 2;
      contentFontSize = 12;
      headerLineHeight = 0;
      headerFontSize = 12;
      fontContent = fontSmall;
      fontHeader = fontSmall;
    } else if (displayHeight <= 64) {
      headerLineHeight = headerFontSize + 2;
      displayType = MEDIUM;
      colStart = 2;
      contentLines = 4;
      contentFontSize = 14;
      headerFontSize = 12;
      headerLineHeight = headerFontSize + 2;
      fontContent = fontMedium;
      fontHeader = fontSmall;
    } else {
      headerLineHeight = headerFontSize + 2;
      displayType = LARGE;
      colStart = 4;
      contentLines = 5;
      contentFontSize = 18;
      headerFontSize = 14;
      headerLineHeight = headerFontSize + 2;
      fontContent = fontLarge;
      fontHeader = fontMedium;
    }

    contentLineHeight = (displayHeight - headerLineHeight) / contentLines;
    headerColWidth = displayWidth / headerFontSize;
  }

  void DisplayComponent::render_display_header() {

    bool connected = is_connected();
    auto time = global_homeassistant_time->now();

    auto colPos = displayWidth - headerColWidth;

    switch (displayType) {
      case SMALL:
        display->print(colPos, 0, fontHeader, Color::WHITE, connected ? "*" : "O");
        break;

      case MEDIUM:
        display->filled_rectangle(0, 0, displayWidth, headerLineHeight + 2, Color::WHITE);
        display->rectangle(0, 0, displayWidth, displayHeight, Color::WHITE);

        if (global_homeassistant_time != nullptr) {
          display->strftime(colStart, 0, fontHeader, Color::BLACK, "%X", time);
        }

        display->print(colPos, 0, fontHeader, Color::BLACK, connected ? "*" : "O");
        break;

      case LARGE:
        display->filled_rectangle(0, 0, displayWidth, headerLineHeight + 2, Color::WHITE);
        display->rectangle(0, 0, displayWidth, displayHeight, Color::WHITE);

        if (global_homeassistant_time != nullptr) {
          display->strftime(colStart, 0, fontHeader, Color::BLACK, "%X", time);
        }

        display->print(colPos, 0, fontHeader, Color::BLACK, connected ? "*" : "O");
        break;
    }
  }

  void DisplayComponent::printLine(int line, const char *text) {
    display->print(colStart, headerLineHeight + contentLineHeight * line, fontContent, text);
  }

  void DisplayComponent::printLinef(int line, const char *text, ...) {
    char buffer[256];
    va_list args;
    va_start(args, text);
    int ret = vsnprintf(buffer, sizeof(buffer), text, args);
    if (ret > 0)
      this->printLine(line, buffer);
    va_end(args);
  }

  void DisplayComponent::render_WelcomeScreen() {
    display->image(5, headerLineHeight + 5, image);
  }

  void DisplayComponent::render_NetworkScreen() {
    auto ip = global_wifi_component->wifi_sta_ip().str();
    int8_t rssi = global_wifi_component->wifi_rssi();

    if (displayType != SMALL) {
      printLine(0, "Network:");
      printLine(1, App.get_name().c_str());
      printLine(2, ip.c_str());
      printLinef(3, "Signal: %d dB", rssi);
    } else {
      printLine(0, App.get_name().c_str());
      printLine(1, ip.c_str());
    }
  }

  void DisplayComponent::render_TimeScreen() {
    if (displayType != SMALL) {
      printLine(1, "Temperatur:");
      printLinef(2, "%s", "24.5°C");
    } else {
      printLine(0, "Temperatur:");
      printLinef(1, "%s", "24.5°C");
    }
  }

  void DisplayComponent::render_Pump1Screen() {
    if (displayType != SMALL) {
      printLine(0, "Pumpe 1:");
      printLinef(1, "%s", "NPK");
      printLine(2, "Nächste:");
      printLinef(3, "%d ml %02d:%02d", 30, 1, 5);
    } else {
      printLinef(0, "Pumpe 1: %s", "NPK");
      printLinef(1, "Nächste: %d ml %02d:%02d", 30, 1, 5);
    }
  }

  void DisplayComponent::render_Pump2Screen() {
    if (displayType != SMALL) {
      printLine(0, "Pumpe 2:");
      printLinef(1, "%s", "GH Boost");
      printLine(2, "Nächste:");
      printLinef(3, "%d ml %02d:%02d", 2, 22, 0);
    } else {
      printLinef(0, "Pumpe 1: %s", "GH Boost");
      printLinef(1, "Nächste: %d ml %02d:%02d", 30, 1, 5);
    }
  }

  void DisplayComponent::render_Pump3Screen() {
    printLine(0, "Pumpe 3:");
    printLinef(1, "%s", "Eisen");
    printLine(2, "Nächste:");
    printLinef(3, "%d ml %02d:%02d", 5, 48, 0);
    if (displayType != SMALL) {
    } else {
      printLinef(0, "Pumpe 1: %s", "Eisen");
      printLinef(1, "Nächste: %d ml %02d:%02d", 30, 1, 5);
    }
  }

}
