#ifndef RTX_COIL_H
#define RTX_COIL_H

#include "rtx_llif.hpp"

namespace rtx {

  class Coil
  {
  public:
    Coil(coil_pin_t);

    void process();

    void startCharge();

    void startKick();
    void startKick(size_t T);

    bool isDone();

  private:
    void doCharge();
    void doKick();

    DigitalOut mCharge, mKick;
    DigitalIn mDone;

    Timer coilTimeout;

    bool m_charged, m_kicked;
    size_t m_charge_mx_period, m_kick_length;
  };

}

#endif
