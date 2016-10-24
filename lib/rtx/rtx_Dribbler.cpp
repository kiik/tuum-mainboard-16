#include "rtx_llif.hpp"
#include "rtx_Dribbler.hpp"

namespace rtx {

  const float DRB_MIN = 0.05;
  const float DRB_MAX = 0.1;
  const float DRB_SPAN = DRB_MAX - DRB_MIN;
  const size_t DRB_WARMUP = 0.065;

  const size_t DRB_WARMUP_T = 500;

  Dribbler::Dribbler(drib_pin_t dpt):
    mOut(dpt.PWM),
    m_pwr(0.0),
    m_warmup(false)
  {
    mWarmupTmr.start();
  }

  void Dribbler::process() {
    if(m_warmup) {
      if(mWarmupTmr.read_ms() > DRB_WARMUP_T) {
        m_warmup = false;
        mOut = DRB_SPAN * m_pwr;
      }
    }
  }

  void Dribbler::setPower(float pwr) {
    if(m_pwr == 0.0) {
      m_warmup = true;
      mWarmupTmr.reset();
      mOut = DRB_WARMUP;
    } else {
      mOut = DRB_SPAN * pwr;
    }

    m_pwr = pwr;
  }

  void Dribbler::write(float pwr) {
    mOut = DRB_SPAN * pwr;
  }

}
