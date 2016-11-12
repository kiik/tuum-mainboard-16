#include "rtx_BallSensor.hpp"

#define H 1
#define L 0

namespace rtx {

  BallSensor::BallSensor(ballsensor_pin_t bl):
    mBallSensor(bl.BLS)
    {

    }

  void BallSensor::process() {

  }

  bool BallSensor::getBallSensor() {
    return (mBallSensor == L);
  }

}
