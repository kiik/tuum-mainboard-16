
#include "rtx_Coil.hpp"

#define H 1
#define L 0

namespace rtx {

  Coil::Coil(coil_pin_t cpt):
    mCharge(cpt.CHARGE), mKick(cpt.KICK), mDone(cpt.DONE),
    m_charged(true), m_kicked(true),
    m_charge_mx_period(5000)
  {
    mKick = L;
    mCharge = L;
  }

  void Coil::startCharge() {
    coilTimeout.reset();
    m_charged = false;
  }

  void Coil::startKick() {
    m_kicked = false;
  }

  bool Coil::isDone() {
    return (mDone.read() == L);
  }

  void Coil::doCharge() {
    if(coilTimeout.read_ms() > m_charge_mx_period) {
      m_charged = true;
      mCharge = L;
      return;
    }

    if(!Coil::isDone()) {
      mCharge = H;
    } else {
      mCharge = L;
      m_charged = true;
    }
  }

  void Coil::doKick() {
    mKick = H;
    wait_ms(5);
    mKick = L;
    m_kicked = true;
  }

  void Coil::process() {
    if(!m_charged) {
      doCharge();
    } else {
      if(!m_kicked) {
        doKick();
      }
    }
  }

}
