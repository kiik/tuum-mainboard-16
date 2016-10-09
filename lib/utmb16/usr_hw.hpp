/** @file usr_hw.hpp
 *  @brief Hardware objects module.
 *
 *  @authors Meelik Kiik
 *  @date 9. October 2016
 *  @version 0.1
 */

#ifndef USR_HW_H
#define USR_HW_H

#include "rtx_MotorController.hpp"

#include "usr_pins.hpp"

using namespace rtx;

namespace usr {

  extern MotorController* gMotors[MOTOR_COUNT];

  void hw_init();
  void hw_process();

}

#endif
