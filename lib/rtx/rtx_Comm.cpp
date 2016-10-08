/** @file rtx_comm.cpp
 *  @brief Communication manager implementation.
 *
 *  @authors Meelik Kiik
 *  @date 8. October 2016
 *  @version 0.1
 */

#include "rtx_logger.hpp"
#include "rtx_protocol.hpp"
#include "rtx_llbus.hpp"
#include "rtx_Comm.hpp"

namespace rtx {

  Comm::Comm():
    buf(NULL), blen(0)
  {

  }

  void Comm::setup() {
    rtx::llb::setup();
  }

  void Comm::process() {
    if(rtx::llb::read(buf, blen) >= 0) {
      if(buf) handleMessage(buf);

      delete(buf);
      buf = NULL;
      blen = 0;
    }
  }

  void Comm::handleMessage(char* data) {
    int res;

    rtx::Protocol::Message msg;
    res = rtx::Protocol::parseCommand(buf, msg);
    if(res < 0) return;

    onMessage(msg);

    msg.cleanup();
  }

}
