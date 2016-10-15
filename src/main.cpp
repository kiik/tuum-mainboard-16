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

#include <iostream>
#include <time.h>

using namespace rtx;
using namespace usr;

usr::Comm gComm;


Timer updTmr;

MotorController* mot;
PID* pid;

void debug_print() {
  if(updTmr.read_ms() > 1000) {
    gLogger.printf("\nSpeed = %.2f deg/s. PWM: %.4f. pidv = %.2f, err = %.4f. dbg = %.2f\n", mot->getSpeed(), mot->getPWMValue(), mot->getPIDValue(), mot->getErr(), mot->getDBGVal());
    gLogger.printf("PID: p=%.2f, i=%.2f, d=%.2f\n", pid->_p(), pid->_i(), pid->_d());
    updTmr.reset();
  }
}

//Note to self: Järgnevad 2 funktsiooni tuleb ümber tõsta mujale. /delete later
void Moving(double v, double angle) {
  double rad = angle*M_PI/180;
  double spd1 = v * -sin(rad + M_PI / 4.0);
  double spd2 = v * sin(rad - M_PI / 4.0);
  double spd3 = v * sin(rad + M_PI / 4.0);
  double spd4 = v * -sin(rad - M_PI / 4.0);

  double speeds[4] = {spd1, spd2, spd3, spd4};
  for(int i=0; i < 4; i++) { gMotors[i]->setSpeed(speeds[i]); }
}

void Rotating(double v, double rot){
  double rad = rot*M_PI/180;
  for(int i=0; i < 4; i++) {
    if (sin(rad) < 0) { gMotors[i]->setSpeed(-v); }
      else { gMotors[i]->setSpeed(v); }
  }
  //Note to self: Ajatsükkel ei tööta /delete later
  double T=(rad/2*M_PI)/v;
  clock_t time = clock();
  while (T != 0) {
    if ((clock() - time)/CLOCKS_PER_SEC == 1) { T = T-1; }
  }
  for(int i=0; i < 4; i++) { gMotors[i]->setSpeed(0); }
}

int main() {
  gLogger.printf("Tuum-Mainboard-16_mbed v0.0.1\n");

  usr::hw_init();
  usr::UI::setup();

  gComm.setup();

  mot = usr::gMotors[1];
  pid = mot->getPID();

  Rotating(50, 10);

  updTmr.start();
  while(1) {
    debug_print();

    gComm.process();
    usr::UI::process();
  }
}
