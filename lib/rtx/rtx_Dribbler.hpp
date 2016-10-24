#ifndef RTX_DRIB_H
#define RTX_DRIB_H

#include "rtx_llif.hpp"

namespace rtx {

  class Dribbler
  {
  public:
    Dribbler(drib_pin_t);

    void process();

    void setPower(float);

    void write(float);

  private:
    PwmOut mOut;
    float m_pwr;

    Timer mWarmupTmr;
    bool m_warmup;

  };

}

#endif
