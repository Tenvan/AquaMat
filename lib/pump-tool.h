#pragma once

#include "esphome.h"
#include <string>

using namespace esphome;
using namespace fan;

namespace esphome {

  class PumpTool {

  protected:
    Fan *pump;

  public:
    PumpTool(Fan *pump);

    void calibratePump();
  };

} // namespace esphome
