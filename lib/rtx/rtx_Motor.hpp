/** @file rtx_Motor.hpp
 *  @brief UT Motor controller.
 *
 *  @authors
 *  @date
 *  @version 0.1
 */

#ifndef RTX_MOTOR_H
#define RTX_MOTOR_H

#include "rtx_MotorState.hpp"

namespace rtx {

  class MotorController
  {
  public:
    MotorController(motor_pin_t);

    int setSpeed(float); // Angular momentum ( degrees / s )
    int setAbsSp(float); // Absolute speed ( cm / s )
    int setRelSp(int16_t); // Relative speed ( -255 ... 255 )

  private:
    MotorState mMotSt;

    float m_diameter;
  };

}

#endif //RTX_MOTOR_H
