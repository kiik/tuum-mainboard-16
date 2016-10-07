/** @file rtx_SPWM.cpp
 *  @brief Software PWM implementation.
 *
 *  @authors Meelik Kiik
 *  @date 7. October 2016
 *  @version 0.1
 */

#include "rtx_SPWM.hpp"

namespace rtx {

  // 50Hz
  const size_t SPWM_DEF_PERIOD = 1.0 / 50.0 * 1000 * 1000;

  SPWM::SPWM(PinName Pin):
    m_duty(0.5), m_period(SPWM_DEF_PERIOD),
    mOut(Pin)
  {
    mOut = 1;
    enable();
  }

  void SPWM::write(float value) {
    m_duty = value;
  }

  void SPWM::pulseStart() {
    float T = m_period * m_duty;

    if(T == 0) mOut = 1;
    else {
      mOut = 0;
      mPulseTmr.attach_us(this, &SPWM::pulseEnd, (size_t)T);
    }
  }

  void SPWM::pulseEnd() {
    mOut = 1;
  }

  void SPWM::enable() {
    disable();
    mProcTicker.attach_us(this, &SPWM::pulseStart, m_period);
  }

  void SPWM::disable() {
    mProcTicker.detach();
  }

  void SPWM::setPeriod(size_t T) {
    m_period = T;
  }

}
