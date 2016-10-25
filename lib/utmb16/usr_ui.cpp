/** @file usr_ui.cpp
 *  @brief Mainboard user input & output interface implementation.
 *
 *  @authors Meelik Kiik
 *  @date 7. October 2016
 *  @version 0.1
 */

#include "usr_pins.hpp"
#include "usr_hw.hpp"
#include "usr_ui.hpp"

namespace usr {

  RGBLed UI::mL1(RGB1);
  RGBLed UI::mL2(RGB2);

  LedBreathe<RGBLed> UI::uiStatusPulse(&UI::mL2);

  enum EMainState {
    NONE = 0,
    INIT,
    COMM_INIT,
    COMM_WACK,
    COMM_READY,

    MAIN_STATE_N,
  };

  EMainState st = INIT;

  Timer tmr;

  void UI::setup() {
    uiStatusPulse.breathe();
    uiStatusPulse.setColor(Color::White);

    tmr.start();
    tmr.reset();
  }

  void UI::process() {
    uiStatusPulse.process();

    if(!gCoil.isDone())
      mL1.write(1.0, 0.0, 0.0);
    else
      mL1.write(0.0, 1.0, 0.0);

    switch(st) {
      case INIT:
        if(tmr.read_ms() >= 2500) {
          uiStatusPulse.setColor(Color::Green);
          uiStatusPulse.blink();
          st = COMM_INIT;
          tmr.reset();
        }
        break;
      case COMM_INIT:
        if(tmr.read_ms() >= 2000) {
          uiStatusPulse.flash();
          st = COMM_WACK;
          tmr.reset();
        }
        break;
      case COMM_WACK:
        if(tmr.read_ms() >= 1000) {
          uiStatusPulse.breathe();
          st = COMM_READY;
          tmr.reset();
        }
        break;
      case COMM_READY:
        if(tmr.read_ms() >= 3000) {
          uiStatusPulse.blink();
          uiStatusPulse.setColor(Color::Cyan);
          st = MAIN_STATE_N;
          tmr.reset();
        }
        break;
    }
  }

}
