
#include "esphome.h"
#include "pump-tool.h"

namespace esphome {

  PumpTool::PumpTool(Fan *pPump) {
    pump = pPump;
  }

  void PumpTool::calibratePump() {
    //    - logger.log: "Pumpe 1 Kalibrierung"
    ESP_LOGD("pump", "Pumpe 1 Kalibrierung");

    {
      //    - fan.turn_off: pump_1
      auto call = pump->turn_off();
      call.perform();
    }

    {

      //    - fan.turn_on:
      //      id: pump_1
      //      direction: FORWARD
      //      speed: 50
      auto call = pump->turn_on();
      call.set_direction(fan::FanDirection::FORWARD);
      call.set_speed(50);
      call.perform();
    }

    //    - text_sensor.template.publish:
    //      id: pump1_status
    //      state: "Kalibrierung"

    //    - delay: 10s
    delay(5000);

    {
      //    - fan.turn_off: pump_1
      auto call = pump->turn_off();
      call.perform();
    }

    //    - text_sensor.template.publish:
    //      id: pump1_status
    //      state: "aus"

    //    - logger.log: "Pumpe 1 Kalibrierung fertig"
    ESP_LOGD("pump", "Pumpe 1 Kalibrierung fertig");

  }
}
