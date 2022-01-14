#include "esphome.h"
#include "display-controler.h"
#include "esphome/components/homeassistant/time/homeassistant_time.h"

/**
 *
 * Display Controler, sorgt für eine einheitliche Ausgabe auf allen verwendeten Displays.
 *
 */

using namespace display;
using namespace time;
using namespace network;
using namespace homeassistant;
using namespace wifi;

namespace esphome {

  /**
   * Rendert die Standard Kopfzeile
   *
   * @param display
   * @param font
   */
  void render_display_header(DisplayBuffer *display, Font *font) {

    // Die Höhe der Headerzeile
    int headerLineHeight = headerFontSize + 2;
    // Die Höhe der Inhaltszeilen
    int contentLineHeight = (display->get_height() - headerLineHeight) / contentLines;
    // Zeichenbreite bei Mono Font
    int colWidth = display->get_width() / contentFontSize;

    display->filled_rectangle(0, 0, display->get_width(), headerLineHeight + 2, Color::WHITE);
    display->rectangle(0, 0, display->get_width(), display->get_height(), Color::WHITE);

    if (global_homeassistant_time != nullptr) {
      auto time = global_homeassistant_time->now();
      display->strftime(colStart, 0, font, Color::BLACK, "%X", time);
    }

    bool connected = is_connected();
    display->print(display->get_width() - colWidth, 0, font, Color::BLACK, connected ? "*" : "O");
  }

  void render_WelcomeScreen(DisplayBuffer *display, Font *font) {

    // Die Höhe der Headerzeile
    int headerLineHeight = headerFontSize + 2;
    // Die Höhe der Inhaltszeilen
    int contentLineHeight = (display->get_height() - headerLineHeight) / contentLines;
    // Zeichenbreite bei Mono Font
    int colWidth = display->get_width() / contentFontSize;

    display->printf(colStart, headerLineHeight + contentLineHeight * 0, font, TextAlign::TOP_LEFT, "Network:");
    display->printf(colStart, headerLineHeight + contentLineHeight * 1, font, "%s", App.get_name().c_str());

    auto ip = global_wifi_component->wifi_sta_ip().str();
    display->printf(colStart, headerLineHeight + contentLineHeight * 2, font, "%s", ip.c_str());

    int8_t rssi = global_wifi_component->wifi_rssi();
    display->printf(colStart, headerLineHeight + contentLineHeight * 3, font, "Signal: %d dB", rssi);
  }

  void render_TimeScreen(DisplayBuffer *display, Font *font) {

    // Die Höhe der Headerzeile
    int headerLineHeight = headerFontSize + 2;
    // Die Höhe der Inhaltszeilen
    int contentLineHeight = (display->get_height() - headerLineHeight) / contentLines;
    // Zeichenbreite bei Mono Font
    int colWidth = display->get_width() / contentFontSize;

    display->print(colStart, headerLineHeight + contentLineHeight * 1, font, "Temperatur:");
    display->print(colStart, headerLineHeight + contentLineHeight * 2, font, " 24.5°C");
  }

  void render_Pump1Screen(DisplayBuffer *display, Font *font) {

    // Die Höhe der Headerzeile
    int headerLineHeight = headerFontSize + 2;
    // Die Höhe der Inhaltszeilen
    int contentLineHeight = (display->get_height() - headerLineHeight) / contentLines;
    // Zeichenbreite bei Mono Font
    int colWidth = display->get_width() / contentFontSize;

    display->printf(colStart, headerLineHeight + contentLineHeight * 0, font, "Pumpe 1:");
    display->printf(colStart, headerLineHeight + contentLineHeight * 1, font, "%s", "NPK");
    display->printf(colStart, headerLineHeight + contentLineHeight * 2, font, "Nächste Dosis:");
    display->printf(colStart, headerLineHeight + contentLineHeight * 3, font, "%03dml %02d:%02d", 30, 1, 5);
  }

  void render_Pump2Screen(DisplayBuffer *display, Font *font) {

    // Die Höhe der Headerzeile
    int headerLineHeight = headerFontSize + 2;
    // Die Höhe der Inhaltszeilen
    int contentLineHeight = (display->get_height() - headerLineHeight) / contentLines;
    // Zeichenbreite bei Mono Font
    int colWidth = display->get_width() / contentFontSize;

    display->printf(colStart, headerLineHeight + contentLineHeight * 0, font, "Pumpe 2:");
    display->printf(colStart, headerLineHeight + contentLineHeight * 1, font, "%s", "GH Boost");
    display->printf(colStart, headerLineHeight + contentLineHeight * 2, font, "Nächste Dosis:");
    display->printf(colStart, headerLineHeight + contentLineHeight * 3, font, "%03dml %02d:%02d", 2, 22, 0);
  }

  void render_Pump3Screen(DisplayBuffer *display, Font *font) {

    // Die Höhe der Headerzeile
    int headerLineHeight = headerFontSize + 2;
    // Die Höhe der Inhaltszeilen
    int contentLineHeight = (display->get_height() - headerLineHeight) / contentLines;
    // Zeichenbreite bei Mono Font
    int colWidth = display->get_width() / contentFontSize;

    display->printf(colStart, headerLineHeight + contentLineHeight * 0, font, "Pumpe 3:");
    display->printf(colStart, headerLineHeight + contentLineHeight * 1, font, "%s", "Eisen");
    display->printf(colStart, headerLineHeight + contentLineHeight * 2, font, "Nächste Dosis:");
    display->printf(colStart, headerLineHeight + contentLineHeight * 3, font, "%03dml %02d:%02d", 5, 48, 0);
  }
}
