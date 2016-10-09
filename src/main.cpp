/** @file main.cpp
 *  @brief Mainboard logic entry module.
 *
 *  @authors Meelik Kiik
 *  @date 7. October 2016
 *  @version 0.1
 */

#include "mbed.h"

#include "rtx_logger.hpp"
#include "rtx_MotorController.hpp"

#include "usr_pins.hpp"
#include "usr_ui.hpp"
#include "usr_hw.hpp"
#include "usr_Comm.hpp"

using namespace rtx;
using namespace usr;

usr::Comm gComm;


Timer updTmr;

MotorController* mot;
PID* pid;

void debug_print() {
  if(updTmr.read_ms() > 1000) {
    gLogger.printf("\nSpeed = %.2f deg/s. PWM: %.4f. pidv = %.2f, err = %.4f\n", mot->getSpeed(), mot->getPWMValue(), mot->getPIDValue(), mot->getErr());
    gLogger.printf("PID: p=%.2f, i=%.2f, d=%.2f\n", pid->_p(), pid->_i(), pid->_d());
    updTmr.reset();
  }
}


int main() {
  gLogger.printf("Tuum-Mainboard-16_mbed v0.0.1\n");

  usr::hw_init();
  usr::UI::setup();

  gComm.setup();

  mot = usr::gMotors[1];
  pid = mot->getPID();

  updTmr.start();
  while(1) {
    debug_print();

    gComm.process();
    usr::UI::process();
  }
}
