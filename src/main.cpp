/** @file main.cpp
 *  @brief Mainboard logic entry module.
 *
 *  @authors Meelik Kiik
 *  @date 7. October 2016
 *  @version 0.1
 */

#include "mbed.h"

#include "rtx_logger.hpp"
#include "rtx_protocol.hpp"
#include "rtx_llbus.hpp"
#include "rtx_MotorState.hpp"

#include "usr_pins.hpp"
#include "usr_ui.hpp"

using namespace rtx;
using namespace usr;


char* buf = NULL;
size_t blen = 0;

void handle_messages() {
  if(rtx::llb::read(buf, blen) >= 0) {
    if(!buf) return;

    int res;
    rtx::Protocol::Message msg;
    res = rtx::Protocol::parseCommand(buf, msg);
    if(res >= 0) {
      gLogger.printf("ACK\n");
    }

    delete(buf);
    buf = NULL;
    blen = 0;
  }
}


int main() {
  rtx::llb::setup();

  gLogger.printf("Tuum-Mainboard-16_mbed v0.0.1\n");

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

    handle_messages();

    usr::UI::process();
  }
}
