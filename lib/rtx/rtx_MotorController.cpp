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
    mPID.setP(1.0);
    mPID.setI(0.0);
    mPID.setD(0.0);

    mTmr.start();
  }

  void MotorController::setSpeed(double v) {
    if(v < 0) mMot.updateDirection(MotorState::DIR_CCW);
    else if(v > 0) mMot.updateDirection(MotorState::DIR_CW);
    else mMot.updateDirection(MotorState::DIR_STOP);

    m_targetSpeed = v;
  }

  double MotorController::getSpeed() { return m_speed; }

  double MotorController::getPIDValue() { return m_pidv; }
  double MotorController::getPWMValue() { return m_pwmv; }

  double MotorController::getErr() { return m_err; }
  double MotorController::getdT() { return m_dt; }

  void MotorController::updateSpeed(double dt) {
    m_speed = mMot.deltaDegree() / dt;
    mMot.resetDelta();

    m_err = m_targetSpeed - m_speed;
  }

  void MotorController::run() {
    double dt = mTmr.read_us() / (1000.0 * 1000.0);
    mTmr.reset();
    m_dt = dt;

    updateSpeed(dt);

    m_err = m_err / (360.0 * 4);
    m_pidv = mPID.run(m_err, dt);

    if(abs(m_err) > 0.01)
      m_pwmv += m_pidv;

    if(m_pwmv < 0.0) m_pwmv = 0.01;
    else if(m_pwmv > 1.0) m_pwmv = 1.0;
    mMot.setPower(m_pwmv);
  }

  MotorState* MotorController::getMotorState() { return &mMot; }
  PID* MotorController::getPID() { return &mPID; }

}
