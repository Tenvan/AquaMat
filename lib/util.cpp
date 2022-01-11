#include "esphome.h"
#include "util.h"
#include "esphome/components/homeassistant/time/homeassistant_time.h"

using namespace display;
using namespace time;
using namespace network;
using namespace homeassistant;

namespace esphome {
  void render_display_header(DisplayBuffer *display, Font *font) {

    static int displayLines = display->get_height() / utilSystemFontSize;
    static int lineHeight = display->get_height() / displayLines;
    static int colWidth = display->get_width() / utilSystemFontSize;

    display->filled_rectangle(0, 0, display->get_width(), lineHeight + 2, Color::WHITE);
    display->rectangle(0, 0, display->get_width(), display->get_height(), Color::WHITE);

    if (global_homeassistant_time != nullptr) {
      auto time = global_homeassistant_time->now();
      display->strftime(1, 0, font, Color::BLACK, "%X", time);
    }

    bool connected = is_connected();
    display->print(display->get_width() - colWidth, 0, font, Color::BLACK, connected ? "*" : "O");
  }
}
