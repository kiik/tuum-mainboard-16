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
#include "usr_motion.hpp"
#include <iostream>
#include <time.h>

#include "app.hpp"

using namespace rtx;
using namespace usr;

usr::Comm gComm;

#define H 1
#define L 0

Timer updTmr;

MotorController* mot;
PID* pid;

void debug_print() {
  if(updTmr.read_ms() > 1000) {
    gLogger.printf("\nSpeed = %.2f deg/s. PWM: %.4f. pidv = %.2f, err = %.4f.\n", mot->getSpeed(), mot->getPWMValue(), mot->getPIDValue(), mot->getErr());
    gLogger.printf("PID: p=%.2f, i=%.2f, d=%.2f\n", pid->_p(), pid->_i(), pid->_d());
    updTmr.reset();
  }
}

namespace app {

  PinName C_DONE = P1_29, C_CHARGE = P0_10, C_KICK = P0_11;

  DigitalOut CHARGE(C_CHARGE), KICK(C_KICK);
  DigitalIn DONE(C_DONE);

  bool charge_done = true, kick_done = true;
  Timer coilTimeout;

  size_t chargeMxPeriod = 5000;

  void charge() {
    coilTimeout.reset();
    charge_done = false;
  }

  void kick() {
    kick_done = false;
  }

  bool is_done() {
    return (DONE.read() == L);
  }

  void do_charge() {
    if(coilTimeout.read_ms() > chargeMxPeriod) {
      charge_done = true;
      CHARGE = L;
      return;
    }

    if(!is_done()) {
      CHARGE = H;
    } else {
      CHARGE = L;
      charge_done = true;
    }
  }

  void do_kick() {
    KICK = H;
    wait_ms(5);
    KICK = L;
    kick_done = true;
  }

  void init() {
    KICK = L;
    CHARGE = L;
  }

  void setup() {

  }

  void process() {
    if(!charge_done) {
      do_charge();
    } else {
      if(!kick_done) {
        do_kick();
      }
    }

    if(!is_done()) {
      usr::UI::mL1.write(1.0, 0.0, 0.0); // Not DONE = RED
    } else {
      usr::UI::mL1.write(0.0, 1.0, 0.0); // DONE = GREEN
    }
  }

}

int main() {
  usr::hw_init();
  app::init();

  gLogger.printf("Tuum-Mainboard-16_mbed v0.0.1\n");

  usr::UI::setup();

  gComm.setup();

  mot = usr::gMotors[0];

  //omniDrive(5,0,10);

  updTmr.start();

  app::setup();

  while(1) {
    app::process();
    debug_print();

    gComm.process();
    usr::UI::process();
  }
}
