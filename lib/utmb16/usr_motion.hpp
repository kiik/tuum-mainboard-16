

#ifndef USR_MOTION_H
#define USR_MOTION_H

#define WHEEL_RADIUS 3.875
#define ROBOT_RADIUS 12.6

namespace usr {

	typedef float mot_speed_t[MOTOR_COUNT];

   void set_speed(mot_speed_t vs);

  extern void omniDrive(float, float, float);
}

#endif
