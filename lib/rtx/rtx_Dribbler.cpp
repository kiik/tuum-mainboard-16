
#include "rtx_llif.hpp"
#include "rtx_Dribbler.hpp"
#include "rtx_logger.hpp"

namespace rtx {

	const float DRB_MAX = 0.1;
	const float DRB_MIN = 0.05;
	const float DRB_SPN = DRB_MAX - DRB_MIN;
	const float DRB_WARM = 0.058;
	const float DRB_WARM2 = 0.2;

	const size_t DRB_WARM_T = 1000;

	Dribbler::Dribbler(dribbler_pin_t dpt):
	mOut(dpt.PWM), m_pwr(0.0),
	m_warmup(false)
	{
	mOut.period(1.0 / 50.0);
	write(DRB_MIN);
	}

	void Dribbler::process() {
	if(m_warmup) {
	  if(mWarmupTmr.read_ms() >= DRB_WARM_T) {
		m_warmup = false;
		mWarmupTmr.stop();
	  }
	}
	}

	void Dribbler::setPower(float pwr) {

	// Set pitcher angle
	gLogger.printf("Dribbler power: %.2f\n", pwr);

	if(m_pwr == pwr) return;

	if(m_pwr == 0.0) {
		m_warmup = true;
		mWarmupTmr.reset();
		mWarmupTmr.start();
		write(DRB_WARM);
		m_pwr = pwr;
		return;
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

	void Dribbler::write(float pwr) {
		mOut = pwr;
	}

	float Dribbler::read(){
		return m_pwr;
	}
}
