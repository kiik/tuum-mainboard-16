/** @file rtx_Motor.cpp
 *  @brief UT motor controller implementation.
 *
 *  @authors
 *  @date
 *  @version 0.1
 */

#include "rtx_Motor.hpp"

namespace rtx {

  MotorController::MotorController(motor_pin_t mpt):
    mMotSt(mpt),
    m_diameter(0)
  {

  }

  int MotorController::setSpeed(float angular) {
    return 0;
  }

  int MotorController::setAbsSp(float cms) {
    return 0;
  }

  int MotorController::setRelSp(int16_t sp) {
    return 0;
  }

}
