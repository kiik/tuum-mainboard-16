/** @file rtx_RGBLed.cpp
 *  @brief RGB Led interface implementation.
 *
 *  @authors Meelik Kiik
 *  @date 7. October 2016
 *  @version 0.1
 */

#include "rtx_RGBLed.hpp"

namespace rtx {

  const Color Color::White(0.7,0.7,0.7);
  const Color Color::Black(0.0,0.0,0.0);

  const Color Color::Red(1.0,0.0,0.0);
  const Color Color::Green(0.0,1,0.0);
  const Color Color::Blue(0.0,0.0,1.0);

  const Color Color::Yellow(1.0,1,0.0);
  const Color Color::Cyan(0.2,1.0,1.0);

  RGBLed::RGBLed(rgb_pin_t rlt):
    pR(rlt.R), pG(rlt.G), pB(rlt.B)
  {
#ifndef RGB_PWM_DISABLED

#ifndef RGB_SPWM
    //pR.period(0.005);
#else
    float period = (1.0 / 500.0 * 1000.0 * 1000.0);
    pR.setPeriod(period);
    pG.setPeriod(period);
    pB.setPeriod(period);
#endif

#endif
  }

  void RGBLed::write(float r, float g, float b)
  {
#ifndef RGB_PWM_DISABLED
    pR = r;
    pG = g;
    pB = b;
#else
    pR = r > 0 ? 1 : 0;
    pG = g > 0 ? 1 : 0;
    pB = b > 0 ? 1 : 0;
#endif
  }

  void RGBLed::write(Color c)
  {
    write(c.r, c.g, c.b);
  }

}
