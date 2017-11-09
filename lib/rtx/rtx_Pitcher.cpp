#include "rtx_Pitcher.hpp"
#include "rtx_logger.hpp"
#include "rtx_Dribbler.hpp"
#include "Servo.h"

#define H 1
#define L 0

#define min(x, y) x > y ? y : x

namespace rtx {

	/**
	 * Pitcher class
	 */
	Pitcher::Pitcher(pitcher_pin_t PTH, Dribbler* DRB):
		m_angleCtl(PTH.SRV),
		m_ballSensor(PTH.IR),

		m_dribbler(DRB)

		//m_ballSensorStatus(L)
	{
		m_clk.start();
		setAngle( m_min_pos );
	}

	void Pitcher::process() {
	  


	}

	

	int Pitcher::getBallStatus(){
		return m_ballSensor;
	}

	/**
	 * Set motor speed
	 * @method  Pitcher::setMotorSpeed
	 * @author  Marko Praakli
	 * @date    2017-11-09
	 */
	void Pitcher::setMotorSpeed( uint8_t percent ){

		percent = min( percent, m_max_percent );

		// Get PWM value
		float pwm_value = map(percent, m_min_percent, m_max_percent, m_min_motor_speed, m_max_motor_speed);

		// Log it
		gLogger.printf("[setMotorSpeed]: PWM = %.2f, P=%i\n", pwm_value, percent );

		// Set PWM value as angle
		m_dribbler->write( pwm_value );
	}

	/**
	 * Get motor speed
	 * @method  Pitcher::getMotorSpeed
	 * @author  Marko Praakli
	 * @date    2017-11-09
	 */
	int Pitcher::getMotorSpeed(){

		float pwm_value = m_dribbler->read();

		// Get valculated percent
		int percent = roundf( map(pwm_value, m_min_motor_speed, m_max_motor_speed, m_min_percent, m_max_percent) );

		// Log it
		gLogger.printf("[getMotorSpeed]: PWM = %.2f, P=%i\n", pwm_value, percent );

		return percent;
	}

	/**
	 * Get servo angle
	 * @method  Pitcher::getAngle
	 * @author  Marko Praakli
	 * @date    2017-11-09
	 */
	int Pitcher::getAngle(){

		// Get PWM value
		float pwm_value = m_angleCtl.read();

		// Get valculated percent
		int percent = roundf( map(pwm_value, m_min_pos, m_max_pos, m_min_percent, m_max_percent) );

		// Log it
		gLogger.printf("[getAngle]: PWM = %.2f, P=%i\n", pwm_value, percent );

		return percent;
	}

	/**
	 * Set servo angle
	 * @method  Pitcher::setAngle
	 * @author  Marko Praakli
	 * @date    2017-11-09
	 */
	void Pitcher::setAngle( uint8_t percent ){

		percent = min( percent, m_max_percent );

		// Get PWM value
		float pwm_value = map(percent, m_min_percent, m_max_percent, m_min_pos, m_max_pos);

		// Log it
		gLogger.printf("[setAngle]: PWM = %.2f, P=%i\n", pwm_value, percent );

		// Set PWM value as angle
		m_angleCtl.write( pwm_value );
	}

	/**
	 * Map function to calculate min max
	 * @method  Pitcher::map
	 * @author  Marko Praakli
	 * @date    2017-11-09
	 * @version [version]
	 */
	float Pitcher::map(float in, float inMin, float inMax, float outMin, float outMax) {
		return outMin + ((outMax - outMin) / (inMax - inMin)) * (in - inMin);
	}
}
