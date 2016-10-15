
#include "usr_hw.hpp"
#include "usr_motion.hpp"

namespace usr {

  typedef float mot_speed_t[MOTOR_COUNT];

  const float MOTOR_ANGLE = M_PI / 4.0;
  const float MOTOR_CMS_TO_DGS = 0.067597; // cm/s to deg/s

  void set_speed(mot_speed_t vs) {
    for(int i=0; i < MOTOR_COUNT; i++) { gMotors[i]->setSpeed(vs[i]); }
  }

  void omniDrive(float spd, float dir, float rot) {
    float v = spd / MOTOR_CMS_TO_DGS;
    float rot_v = rot * 3.243;
    float rad = dir * M_PI/180;

    mot_speed_t vs;
    vs[0] = v * -sin(rad + MOTOR_ANGLE) + rot_v;
    vs[1] = v * sin(rad - MOTOR_ANGLE) + rot_v;
    vs[2] = v * sin(rad + MOTOR_ANGLE) + rot_v;
    vs[3] = v * -sin(rad - MOTOR_ANGLE) + rot_v;

    set_speed(vs);
  }

}
