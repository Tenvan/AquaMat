#pragma once

#include "esphome.h"
#include <string>

using namespace esphome;
using namespace display;

static int contentFontSize = 14;
static int headerFontSize = 12;
static int contentLines = 4;

static int colStart = 3;

namespace esphome {

  void render_display_header(DisplayBuffer *display, Font *font);

  void render_WelcomeScreen(DisplayBuffer *display, Font *font);

  void render_TimeScreen(DisplayBuffer *display, Font *font);

  void render_Pump1Screen(DisplayBuffer *display, Font *font);

  void render_Pump2Screen(DisplayBuffer *display, Font *font);

  void render_Pump3Screen(DisplayBuffer *display, Font *font);

} // namespace esphome
