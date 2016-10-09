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
    enum dir_t {
      DIR_BLOCK = 0,
      DIR_STOP  = 1,
      DIR_CW    = 2,
      DIR_CCW   = 3,
    };

    MotorState(motor_pin_t);

    void setPower(float);
    void setDirection(dir_t);
    void updateDirection(dir_t);

    void feedbackUpdate();

    void resetDelta();
    int32_t deltaPos();
    float deltaDegree();

  private:
    PwmOut OUT;
    DigitalOut D1, D2;
    InterruptIn EA, EB;
    DigitalIn FLT;

    int32_t pos, lpos;
    uint8_t enc, lenc;
    uint8_t pol;
    dir_t ldir;

  };

}

#endif
