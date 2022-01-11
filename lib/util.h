#pragma once

#include "esphome.h"
#include <string>

using namespace esphome;
using namespace display;

static int utilSystemFontSize = 12;
static int colStart = 1;

namespace esphome {

/// Display Header
  void render_display_header(DisplayBuffer *display, Font *font);

}  // namespace esphome
