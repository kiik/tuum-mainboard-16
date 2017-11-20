
#include "rtx_llif.hpp"
#include "rtx_Dribbler.hpp"
#include "rtx_logger.hpp"

namespace rtx {

	const float DRB_MAX = 0.1;
	const float DRB_MIN = 0.05;
	const float DRB_SPN = DRB_MAX - DRB_MIN;
	const float DRB_WARM = 0.058;
	const float DRB_WARM2 = 0.2;
	const size_t DRB_WARM_T = 100;

	Dribbler::Dribbler(dribbler_pin_t dpt):
	mOut(dpt.PWM), m_pwr(0.0),
	m_warmup(false)
	{
		mOut.period(1.0 / 50.0);
		write(DRB_MIN);
	}

	void Dribbler::process()
	{
		if(m_warmup)
		{
			gLogger.printf("[D::p]\n" );

			if(mWarmupTmr.read_ms() >= DRB_WARM_T)
			{
				mWarmupTmr.stop();

				float pwr = m_pwr;

				m_pwr = m_pwr + 0.1;

				setPower(pwr);
			}
		}
	}

	void Dribbler::setPower(float pwr){

		// gLogger.printf("[setPower]: warmup = %d, current = %.2f, new = %.2f\n", m_warmup, m_pwr, pwr );

		if(m_pwr == pwr) return;

		if(!m_warmup && (m_pwr == 0.0))
		{
			m_warmup = true;
			
			mWarmupTmr.reset();
			mWarmupTmr.start();

			write(DRB_WARM); // 0.058

			m_pwr = pwr;
			return;

		}
		else if(m_warmup)
		{
			m_warmup = false;
		}

		/**if(m_pwr < 0.2) {
		  m_warmup = true;
		  mWarmupTmr.reset();
		  mWarmupTmr.start();
		  write(DRB_WARM2);
		  m_pwr = pwr;
		  return;
		}*/
		mOut = DRB_MIN + DRB_SPN * pwr;

		m_pwr = pwr;
	}

	void Dribbler::write(float pwr){
		mOut = pwr;
	}

	void Dribbler::setSpeed( float pwm_value ){
		mOut = pwm_value;
	}

	float Dribbler::read(){
		return m_pwr;
	}
}
