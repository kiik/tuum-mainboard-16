/** @file usr_pins.hpp
 *  @brief Mainboard pinout mapping.
 *
 *  @authors Meelik Kiik
 *  @date 7. October 2016
 *  @version 0.1
 */

#ifndef USR_PINS_H
#define USR_PINS_H

#include "rtx_llif.hpp"

using namespace rtx;

#define MOTOR_COUNT 4

namespace usr {

  static const rgb_pin_t RGB1 = {P4_28, P4_29, P2_8};
  static const rgb_pin_t RGB2 = {P0_28, P1_18, P0_27};

  static const motor_pin_t MOT0 = {P2_3, P0_21, P0_20, P0_19, P0_18, P0_22};
  static const motor_pin_t MOT1 = {P2_0, P0_7, P0_6, P0_5, P0_4, P0_8};
  static const motor_pin_t MOT2 = {P2_1, P0_24, P0_25, P0_26, P0_9, P0_23};
  static const motor_pin_t MOT3 = {P2_2, P0_15, P0_16, P2_7, P2_6, P0_17};

  static const motor_pin_t* MOTN[MOTOR_COUNT] = {&MOT0, &MOT1, &MOT2, &MOT3};

  // static const coil_pin_t COIL0 = {P0_10, P0_11, P1_29};
  static const dribbler_pin_t DRB0 = {P2_5}; // P2_5
  static const pitcher_pin_t PTH0 = {P1_30, P2_4};
  // static const ballsensor_pin_t BL0 = {P1_30};
  // static const switches_pin_t SW = {P1_24, P1_23, P1_22, P1_21};

}

#endif
