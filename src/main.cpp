/** @file main.cpp
 *  @brief Mainboard logic entry module.
 *
 *  @authors Meelik Kiik
 *  @date 7. October 2016
 *  @version 0.1
 */

#include "mbed.h"

#include "rtx_logger.hpp"
#include "rtx_MotorState.hpp"

#include "usr_pins.hpp"
#include "usr_ui.hpp"
#include "usr_Comm.hpp"

using namespace rtx;
using namespace usr;

usr::Comm gComm;

int main() {
  gLogger.printf("Tuum-Mainboard-16_mbed v0.0.1\n");

  gComm.setup();

  MotorState mMot1(MOT1);
  Timer tmr;
  tmr.start();
  tmr.reset();

  usr::UI::setup();

  while(1) {
    if(tmr.read_ms() > 1000) {
      int32_t dp = mMot1.deltaPos();
      float deg = mMot1.deltaPosDegrees();
      gLogger.printf("mMot1.dp = %i, .deg = %.2f\n", dp, deg);

      mMot1.resetDelta();
      tmr.reset();
    }

    gComm.process();
    usr::UI::process();
  }
}
