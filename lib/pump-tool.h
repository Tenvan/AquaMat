#pragma once

#include "esphome.h"
#include <string>

using namespace esphome;
using namespace fan;

namespace esphome {

  class PumpTool {

  protected:
    FanState *pump;

  public:
    PumpTool(FanState *pump);

    void calibratePump();
  };

} // namespace esphome
