#include "rtx_SwitchInterface.hpp"

namespace rtx {

  SwitchInterface::SwitchInterface(switches_pin_t in):
    mInput({in.SW0, in.SW1, in.SW2, in.SW3})
  {
    for(size_t i=0; i < 4; i++) {
      m_states[i] = mInput[i];
    }
  }

  void SwitchInterface::process() {

    for(size_t i=0; i < 4; i++) {
      if(mInput[i] != m_states[i]) {
        gLogger.printf("<1:sw,%i,%i>\n", i, mInput[i].read());
      }
    }

    for(size_t i=0; i < 4; i++) {
      m_states[i] = mInput[i];
    }

  }

  bool SwitchInterface::getSwitch(size_t ix) {
    return (mInput[ix].read() == 1);
  }

}
