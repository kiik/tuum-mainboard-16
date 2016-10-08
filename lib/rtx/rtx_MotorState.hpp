/** @file rtx_MotorState.hpp
 *  @brief Motor state structure.
 *
 *  @authors Meelik Kiik
 *  @date 8. October 2016
 *  @version 0.1
 */

#ifndef RTX_MOTST_H
#define RTX_MOTST_H

#include "mbed.h"

#include "rtx_llif.hpp"

namespace rtx {

  class MotorState
  {
  public:
    MotorState(motor_pin_t);

    void feedbackUpdate();

    void resetDelta();

    int32_t deltaPos();
    float deltaPosDegrees();

  private:
    PwmOut OUT;
    DigitalOut D1, D2;
    InterruptIn EA, EB;
    DigitalIn FLT;

    int32_t pos, lpos;
    uint8_t enc, lenc;

  };

}

#endif
