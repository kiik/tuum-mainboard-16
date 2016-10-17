/** @file rtx_MotorController.hpp
 *  @brief Motor controller interface.
 *
 *  @authors Meelik Kiik
 *  @date 9. October 2016
 *  @version 0.1
 */

#ifndef RTX_MOTOR_CTL_H
#define RTX_MOTOR_CTL_H

#include "rtx_MotorState.hpp"
#include "rtx_PID.hpp"

namespace rtx {

  extern float ENC_FILTER;

  class MotorController
  {
  public:
    MotorController(motor_pin_t);

    void setSpeed(double);

    double getSpeed();
    double getdT();

    double getPIDValue();
    double getPWMValue();
    double getErr();

    double getDBGVal();

    void updateSpeed(double);
    void run();

    MotorState* getMotorState();
    PID* getPID();

  private:
    MotorState mMot;
    PID mPID;

    double m_speed, m_targetSpeed;
    double m_err, m_pidv, m_pwmv;
    double m_dt;

    bool cross;
    Timer mTmr;
  };

}

#endif //RTX_MOTOR_CTL_H
