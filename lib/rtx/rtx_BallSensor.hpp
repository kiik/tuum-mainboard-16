#include "rtx_llif.hpp"

namespace rtx {

  class BallSensor {
  public:
    BallSensor(ballsensor_pin_t);

    void process();

    bool getBallSensor();

  private:
    DigitalIn mBallSensor;

  };
}
