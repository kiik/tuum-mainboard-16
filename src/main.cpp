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
#include "usr_motion.hpp"

#include "usr_Comm.hpp"

#include "app.hpp"

//#define TUUM_ETH_EN

#ifdef TUUM_ETH_EN
#include "EthernetInterface.h"
#endif

#define IP         "192.168.1.250"
#define GATEWAY    "192.168.1.254"
#define MASK       "255.255.255.0"


using namespace rtx;
using namespace usr;

#ifndef TUUM_ETH_EN
usr::Comm gComm;
#endif

Timer updTmr;

MotorController* mot;
PID* pid;

extern "C" void mbed_mac_address(char *s) {
  char mac[6];
  mac[0] = 0x00;
  mac[1] = 0x02;
  mac[2] = 0xf7;
  mac[3] = 0xf0;
  mac[4] = 0x45;
  mac[5] = 0xbe;
  // Write your own mac address here
  memcpy(s, mac, 6);
}

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

void debug_prxint() {
  if(updTmr.read_ms() > 1000) {
   
    gLogger.printf("\nSpeed = %.2f deg/s. PWM: %.4f. pidv = %.2f, err = %.4f.\n", mot->getSpeed(), mot->getPWMValue(), mot->getPIDValue(), mot->getErr());
    gLogger.printf("PID: p=%.2f, i=%.2f, d=%.2f\n", pid->_p(), pid->_i(), pid->_d());
    //gLogger.printf("mem:%lu\n", heapSize());
    updTmr.reset();
  }
}

int main() {
#ifdef TUUM_ETH_EN
  EthernetInterface eth;

  eth.disconnect();

  int i = eth.set_network(IP,MASK,GATEWAY);

  i = eth.connect();
#endif

  updTmr.start();
  usr::hw_init();

  //net.connect();

  gLogger.printf("Tuum-Mainboard-16_mbed v0.0.1\n");

  usr::UI::setup();

#ifndef TUUM_ETH_EN
  gComm.setup();
#endif

  while(1) {
    if(updTmr.read_ms() > 2000) {
#ifdef TUUM_ETH_EN
      const char *ip = eth.get_ip_address();
      const char *mac = eth.get_mac_address();
      gLogger.printf("%s, %s\n", ip, mac);
#endif
      updTmr.reset();
    }

#ifndef TUUM_ETH_EN
    gComm.process();
#endif

    gDribbler.process();
    gPitcher.process();

    usr::UI::process();
  }

  //net.disconnect();
}
