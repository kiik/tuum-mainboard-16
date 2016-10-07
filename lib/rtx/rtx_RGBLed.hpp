/** @file rtx_RGBLed.hpp
 *  @brief RGB Led interface.
 *
 *  @authors Meelik Kiik
 *  @date 7. October 2016
 *  @version 0.1
 */

#ifndef RTX_RGBL_H
#define RTX_RGBL_H

#include "mbed.h"

//#define RGB_PWM_DISABLED
#define RGB_SPWM

#ifdef RGB_SPWM
#include "rtx_SPWM.hpp"
#endif

namespace rtx {

  class Color {
  public:
    float r;
    float g;
    float b;

    Color(float _r, float _g, float _b):
      r(_r), g(_g), b(_b)
    {

    }

    Color(const Color& c):
      r(c.r), g(c.g), b(c.b)
    {

    }

    Color operator*(const float& k)
    {
      return Color(r*k, g*k, b*k);
    }

    Color operator+(const float& k)
    {
      return Color(r + k, g + k, b + k);
    }

    Color operator+(const Color& x)
    {
      return Color(r + x.r , g + x.g, b + x.b);
    }

  public:
    static const Color White;
    static const Color Black;

    static const Color Red;
    static const Color Green;
    static const Color Blue;

    static const Color Yellow;
    static const Color Cyan;
  };


  class RGBLed
  {
  public:
    RGBLed(PinName, PinName, PinName);

    void write(float, float, float);
    void write(Color c);

    RGBLed operator=(Color c) {
      write(c);
      return *this;
    };

  private:
    #ifndef RGB_PWM_DISABLED

    #ifndef RGB_SPWM
    PwmOut pR;
    PwmOut pG;
    PwmOut pB;
    #else
    SPWM pR;
    SPWM pG;
    SPWM pB;
    #endif

    #else
    /*DigitalOut pR;
    DigitalOut pG;
    DigitalOut pB;*/
    #endif
  };

}

#endif
