/** @file rtx_SPWM.hpp
 *  @brief Software PWM class.
 *
 *  @authors Meelik Kiik
 *  @date 7. October 2016
 *  @version 0.1
 */

#ifndef RTX_SPWM_H
#define RTX_SPWM_H

#include "mbed.h"

namespace rtx {

  class SPWM
  {
  public:
      SPWM(PinName Pin);

      void enable();
      void disable();

      void write(float);

      SPWM& operator=(float value) {
        write(value);
        return *this;
      }

      void setPeriod(size_t T);

      DigitalOut* getDigitalOut() { return &mOut; }

  private:
      float  m_duty;
      size_t m_period;

      DigitalOut mOut;

      Ticker  mProcTicker;
      Timeout mPulseTmr;

      void pulseStart();
      void pulseEnd();
  };

}

#endif
