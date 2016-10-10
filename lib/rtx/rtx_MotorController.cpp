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

  MotorController::MotorController(motor_pin_t mpt):
    mMot(mpt),
    m_speed(0), m_targetSpeed(0)
  {
    mTmr.start();
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
    m_speed = mMot.deltaDegree() / dt * (m_targetSpeed < 0 ? -1 : 1);
    mMot.resetDelta();

    m_err = abs(m_targetSpeed) - m_speed;
  }

  void MotorController::run() {
    double dt = mTmr.read_us() / (1000.0 * 1000.0);
    mTmr.reset();
    m_dt = dt;

    updateSpeed(dt);

    m_err = m_err / (360.0 * 2);
    m_pidv = mPID.run(m_err, dt);

    if(abs(m_err) > 0.01)
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
