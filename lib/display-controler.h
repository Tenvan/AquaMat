#pragma once

#include "esphome.h"
#include <string>

using namespace esphome;
using namespace display;

namespace esphome {

  enum DisplayType {
    SMALL,
    MEDIUM,
    LARGE
  };

  class DisplayComponent {

  protected:
    DisplayBuffer *display;
    DisplayType displayType;

    display::Image *image;

    Font *fontLarge;
    Font *fontMedium;
    Font *fontSmall;
    Font *fontContent;
    Font *fontHeader;

    int headerColWidth;
    int colStart;
    int contentFontSize;
    int contentLineHeight;
    int contentLines;
    int displayHeight;
    int displayWidth;
    int headerLineHeight;
    int headerFontSize;

  public:
    DisplayComponent(DisplayBuffer *pDisplay,
                     Image *pImage,
                     Font *pFontSmall,
                     Font *pFontMedium,
                     Font *pFontLarge);

    void printLine(int line, const char *text);

    void printLinef(int line, const char *text, ...);

    void render_display_header();

    void render_WelcomeScreen();

    void render_NetworkScreen();

    void render_TimeScreen();

    void render_Pump1Screen();

    void render_Pump2Screen();

    void render_Pump3Screen();
  };

} // namespace esphome
