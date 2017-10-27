
#include "rtx_logger.hpp"
#include "usr_hw.hpp"
#include "usr_motion.hpp"

namespace usr {

  typedef float mot_speed_t[MOTOR_COUNT];

  const float MOTOR_ANGLE = M_PI / 4.0;
  const float MOTOR_CMS_TO_DGS = 2*M_PI*WHEEL_RADIUS / 360; // cm/s to deg/s

  Ticker timeoutTick;

  void timeout();

  void set_speed(mot_speed_t vs) {
    timeoutTick.detach();
    for(int i=0; i < MOTOR_COUNT; i++) { gMotors[i]->setSpeed(vs[i]); }
    timeoutTick.attach_us(timeout, 1000 * 1000);
  }

  void omniDrive(float spd, float dir, float rot) {
    float v = spd / MOTOR_CMS_TO_DGS;
    float rot_v = rot * ROBOT_RADIUS / WHEEL_RADIUS;
    float rad = dir * M_PI/180;

    mot_speed_t vs;
    vs[0] = v * -sin(MOTOR_ANGLE - dir) + rot_v;
    vs[1] = v * -sin(MOTOR_ANGLE + dir) + rot_v;
    vs[2] = v * sin(MOTOR_ANGLE - dir) + rot_v;
    vs[3] = v * sin(MOTOR_ANGLE + dir) + rot_v;

    set_speed(vs);
  }

  void timeout() {
    omniDrive(0, 0, 0);
  }


}
