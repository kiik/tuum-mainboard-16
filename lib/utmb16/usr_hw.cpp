/** @file usr_hw.cpp
 *  @brief Hardware objects module.
 *
 *  @authors Meelik Kiik
 *  @date 9. October 2016
 *  @version 0.1
 */

#include "usr_pins.hpp"
#include "usr_hw.hpp"

using namespace rtx;

namespace usr {

  MotorController gM0(MOT0);
  MotorController gM1(MOT1);
  MotorController gM2(MOT2);
  MotorController gM3(MOT3);

  MotorController* gMotors[MOTOR_COUNT];

  Coil gCoil(COIL0);
  Dribbler gDribbler(DRB0);

  Dribbler gDrib(DRB0);

  Ticker hwProcTick;

  void hw_init() {
    gMotors[0] = &gM0;
    gMotors[1] = &gM1;
    gMotors[2] = &gM2;
    gMotors[3] = &gM3;

    size_t Hz100_us = 10 * 1000;
    hwProcTick.attach_us(hw_process, Hz100_us);
  }

  void hw_process() {
    for(size_t ix = 0; ix < MOTOR_COUNT; ix++)
      gMotors[ix]->run();
  }

}
