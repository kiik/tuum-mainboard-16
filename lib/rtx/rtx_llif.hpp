/** @file rtx_llif.hpp
 *  @brief Low level interface data structures.
 *
 *  @authors Meelik Kiik
 *  @date 7. October 2016
 *  @version 0.1
 */

#ifndef RTX_LLIF_H
#define RTX_LLIF_H

#include "mbed.h"

namespace rtx {

  struct rgb_pin_t { PinName R, G, B; };
  struct motor_pin_t { PinName PWM, D1, D2, EA, EB, FLT; };
  struct coil_pin_t { PinName CHARGE, KICK, DONE; };
  struct dribbler_pin_t { PinName PWM; };
  struct ballsensor_pin_t { PinName BLS; };

}

#endif
