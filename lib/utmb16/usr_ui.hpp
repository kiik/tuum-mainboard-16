/** @file usr_ui.hpp
 *  @brief Mainboard user input & output interface.
 *
 *  @authors Meelik Kiik
 *  @date 7. October 2016
 *  @version 0.1
 */

#ifndef USR_UI_H
#define USR_UI_H

#include "mbed.h"
#include "usr_hw.hpp"
#include "rtx_RGBLed.hpp"

using namespace rtx;

namespace usr {

  // TODO: Code cleanup
  template<class OutClass>
  struct LedBreathe {
    float c;
    float p;

    int T;
    float B;
    Timer tmr;

    OutClass* out;
    Color mColor;

    LedBreathe(OutClass* _out):
      B(0.8), mColor(Color::White)
    {
      blink();
      out = _out;
      tmr.start();
      tmr.reset();
    }

    void tick() {
      p = p + c;
      if(p > 1.0) {
        c *= -1.0;
        p = 1.0;
      } else if(p < 0.0) {
        c *= -1.0;
        p = 0.0;
      }
    }

    void process() {
      if(tmr.read_ms() > T) {
        tick();
        *out = (mColor * p);
        tmr.reset();
      }
    }

    float getConstant() {
      return p;
    }

    void blink() {
      c = 2.0;
      T = 100;
      p = 1.0;
    }

    void breathe() {
      c = 0.005;
      T = 10;
      p = 1.0;
    }

    void flash() {
      c = 2.0;
      T = 50;
      p = 1.0;
    }

    void setColor(Color col) {
      mColor = col;
    }

  };

  class UI
  {
  public:

    static void setup();
    static void process();

    static RGBLed mL1;
  private:
    static RGBLed mL2;

    static LedBreathe<RGBLed> uiStatusPulse;
  };

}

#endif
