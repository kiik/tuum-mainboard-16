#include "rtx_llif.hpp"
#include "Servo.h"

namespace rtx {

	class Dribbler;

	class Pitcher {

		public:
			Pitcher(pitcher_pin_t, Dribbler*);

			// Process events
			void process();

			void setAngle(uint8_t);
			int getAngle();

			int getBallStatus();
			
			void setMotorSpeed(uint8_t);
			int getMotorSpeed();

			float map(float, float, float, float, float);

		private:
			Timer m_clk;
			Servo m_angleCtl;

			// Digital IN pins
			DigitalIn m_ballSensor;

			Dribbler *m_dribbler;

			static const float m_min_motor_speed = 0.0;
			static const float m_max_motor_speed = 1.0;

			static const float m_min_pos = 0.05;
			static const float m_max_pos = 0.60;

			static const int m_min_percent = 0;
			static const int m_max_percent = 99;
	};
}
