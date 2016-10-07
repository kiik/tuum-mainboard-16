/** @file usr_pins.hpp
 *  @brief Mainboard pinout mapping.
 *
 *  @authors
 *  @date 7. October 2016
 *  @version 0.1
 */

#ifndef USR_PINS_H
#define USR_PINS_H

#include "mbed.h"
#include "definitions.h"

namespace usr {

  static const PinName LED1_R = P4_28, LED1_G = P4_29, LED1_B = P2_8;

  /*
  PwmOut MOTOR0_PWM(P2_3);
  DigitalOut MOTOR0_DIR1(P0_21);
  DigitalOut MOTOR0_DIR2(P0_20);
  DigitalIn MOTOR0_FAULT(P0_22);
  InterruptIn MOTOR0_ENCA(P0_19);
  InterruptIn MOTOR0_ENCB(P0_18);
  */
  //Testing pins

}

#endif
