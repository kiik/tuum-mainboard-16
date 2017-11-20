/** @file rtx_MotorState.cpp
 *  @brief Motor state implementation.
 *
 *  @authors Meelik Kiik
 *  @date 8. October 2016
 *  @version 0.1
 */

#include "rtx_MotorState.hpp"

namespace rtx {

  MotorState::MotorState(motor_pin_t mpt):
    OUT(mpt.PWM),
    D1(mpt.D1), D2(mpt.D2),
    EA(mpt.EA), EB(mpt.EB), FLT(mpt.FLT),
    pos(0), lpos(0), enc(0), lenc(0),
    pol(0)
  {
    EA.mode(PullNone);
    EA.mode(PullNone);
    OUT.period(1.0 / 200.0); // 200Hz

    setDirection(DIR_STOP);
    setPower(0.0);

    EA.rise(this, &MotorState::feedbackUpdate);
    EA.fall(this, &MotorState::feedbackUpdate);
    EB.rise(this, &MotorState::feedbackUpdate);
    EB.fall(this, &MotorState::feedbackUpdate);

    EA.enable_irq();
    EB.enable_irq();
  }

  void MotorState::setPower(float p) {
    if(isLocked()) return;
    lock();
    OUT.write(p);
    lpw = p;
    unlock();
  }

  void MotorState::setDirection(dir_t d) {
    switch(d) {
      case DIR_CW:
        setPower(0.0);
        D1 = pol;
        D2 = !pol;
        setPower(lpw);
        break;
      case DIR_CCW:
        setPower(0.0);
        D1 = !pol;
        D2 = pol;
        setPower(lpw);
        break;
      case DIR_BLOCK:
        setPower(0.0);
        D1 = 1;
        D2 = 1;
        break;
      case DIR_STOP:
        setPower(0.0);
        break;
    }

    ldir = d;
  }

  void MotorState::updateDirection(dir_t d) {
    if(ldir == d) return;
    setDirection(d);
  }

  void MotorState::feedbackUpdate() {
    lenc = enc;
    enc = EA.read() | (EB.read() << 1);

    uint8_t dir = (lenc & 1) ^ ((enc & 2) >> 1);

    if (dir & 1) pos++;
    else pos--;
  }

  void MotorState::resetDelta() {
    lpos = pos;
  }

  int32_t MotorState::deltaPos() {
    int32_t dp = pos - lpos;
    return dp;
  }

  float MotorState::deltaDegree() {
    return deltaPos() / 1200.0 * 360;
  }

  void MotorState::lock() {
    locked = true;
  }

  void MotorState::unlock() {
    locked = false;
  }

  bool MotorState::isLocked() {
    return locked == true;
  }
  
  int MotorState::getPosition() {
    return pos / 1200.0 * 360;
  }
}
