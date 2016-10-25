#ifndef RTX_DRB_H
#define RTX_DRB_H

#include "rtx_llif.hpp"

namespace rtx {

  class Dribbler
  {
  public:
    Dribbler(dribbler_pin_t);

    void process();

    void setPower(float);
    void writePower(float);

    void write(float);

  private:
    PwmOut mOut;
    float m_pwr;

    Timer mWarmupTmr;
    bool m_warmup;
  };

}

#endif
