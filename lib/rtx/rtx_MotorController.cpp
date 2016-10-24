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

  void MotorController::updateSpeed(double dt) {
    float deg = mMot.deltaDegree();
    mMot.resetDelta();
    m_speed = deg / dt;

    m_err = m_targetSpeed - m_speed;
  }

  void MotorController::run() {
    m_dt = mTmr.read_us();
    mTmr.reset();
    m_dt /= 1000.0 * 1000.0; // Convert to seconds.

    updateSpeed(m_dt);

    m_err = m_err / 1000.0; // Normalize
    m_pidv = mPID.run(m_err, m_dt);

    if(m_pidv < 0.0) mMot.setDirection(MotorState::DIR_CW);
    else if(m_pidv > 0.0) mMot.setDirection(MotorState::DIR_CCW);

    m_pwmv = (m_pidv < 0) ? m_pidv * -1 : m_pidv;

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
