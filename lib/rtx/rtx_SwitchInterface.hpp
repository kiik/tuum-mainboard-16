#include "rtx_llif.hpp"
#include "rtx_logger.hpp"

namespace rtx {

  class SwitchInterface {
  public:
    SwitchInterface(switches_pin_t);

    void process();

    bool getSwitch(size_t);

  private:
    DigitalIn mInput[4];
    bool m_states[4];

  };
}
