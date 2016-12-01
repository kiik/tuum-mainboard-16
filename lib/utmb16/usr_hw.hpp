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
#include "rtx_Dribbler.hpp"
#include "rtx_Coil.hpp"
#include "rtx_Dribbler.hpp"
#include "rtx_BallSensor.hpp"
#include "rtx_SwitchInterface.hpp"
#include "usr_pins.hpp"

using namespace rtx;

namespace usr {

  extern MotorController* gMotors[MOTOR_COUNT];

  extern Coil gCoil;
  extern Dribbler gDribbler;
  extern BallSensor gSensor;
  extern SwitchInterface gSwitch;

  void hw_init();
  void hw_process();

}

#endif
