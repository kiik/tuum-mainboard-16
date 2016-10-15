/** @file rtx_MotorController.cpp
 *  @brief Motor controller implementation.
 *
 *  @authors Meelik Kiik
 *  @date 9. October 2016
 *  @version 0.1
 */

#include <cmath>

#include "rtx_logger.hpp"
#include "rtx_MotorController.hpp"
#include "usr_hw.hpp"

namespace rtx {

  float ENC_FILTER = 0.0;

  MotorController::MotorController(motor_pin_t mpt):
    mMot(mpt),
    m_speed(0), m_targetSpeed(0)
  {
    mTmr.start();
    cross = false;
  }

  void MotorController::setSpeed(double v) {
    if(v < 0) mMot.setDirection(MotorState::DIR_CW);
    else if(v > 0) mMot.setDirection(MotorState::DIR_CCW);
    else mMot.setDirection(MotorState::DIR_STOP);

    m_targetSpeed = v;
  }

  double MotorController::getSpeed() { return m_speed; }

  double MotorController::getPIDValue() { return m_pidv; }
  double MotorController::getPWMValue() { return m_pwmv; }

  double MotorController::getErr() { return m_err; }
  double MotorController::getdT() { return m_dt; }

  double MotorController::getDBGVal() {
    return m_dbg;
  }

  void MotorController::updateSpeed(double dt) {
    m_dbg = m_dbg * ENC_FILTER + mMot.deltaDegree() * (1 - ENC_FILTER);
    m_speed = m_dbg / dt * (m_targetSpeed < 0 ? -1 : 1);
    mMot.resetDelta();

    m_err = abs(m_targetSpeed) - m_speed;
  }

  void MotorController::run() {
    double dt = mTmr.read_us() / (1000.0 * 1000.0);
    mTmr.reset();
    m_dt = dt;

    updateSpeed(dt);

    m_err = m_err / 1000.0;
    m_pidv = mPID.run(m_err, dt) / 10.0;

    if(m_pidv < 0) cross = true;
    else if(m_pidv > 0) {
      if(cross) {
        m_dbg += 1;
        cross = false;
      }
    }

    m_pwmv += m_pidv;

    if(m_pwmv > 1.0) m_pwmv = 1.0;
    else if(m_pwmv < -1.0) m_pwmv = -1.0;

    if(m_targetSpeed != 0)
      mMot.setPower(m_pwmv);
    else
      mMot.setPower(0.0);
  }

  MotorState* MotorController::getMotorState() { return &mMot; }
  PID* MotorController::getPID() { return &mPID; }

}
