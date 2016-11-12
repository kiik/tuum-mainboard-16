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

Timer updTmr;

MotorController* mot;
PID* pid;

unsigned long  heapSize()
{
  char   stackVariable;
  void   *heap;
  unsigned long result;
  heap  = malloc(4);
  result  = (unsigned long)(&stackVariable) - (unsigned long)heap;
  free(heap);
  return result;
}

void debug_print() {
  if(updTmr.read_ms() > 1000) {
    /*
    gLogger.printf("\nSpeed = %.2f deg/s. PWM: %.4f. pidv = %.2f, err = %.4f.\n", mot->getSpeed(), mot->getPWMValue(), mot->getPIDValue(), mot->getErr());
    gLogger.printf("PID: p=%.2f, i=%.2f, d=%.2f\n", pid->_p(), pid->_i(), pid->_d());
    */
    gLogger.printf("mem:%lu\n", heapSize());
    updTmr.reset();
  }
}

int main() {
  updTmr.start();
  usr::hw_init();

  gLogger.printf("Tuum-Mainboard-16_mbed v0.0.1\n");

  usr:UI::setup();
  gComm.setup();

  while(1) {
    gComm.process();

    gDrib.process();
    gCoil.process();
    usr::UI::process();
    //debug_print();
  }
}
