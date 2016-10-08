/** @file usr_comm.cpp
 *  @brief Communication manager implementation.
 *
 *  @authors Meelik Kiik
 *  @date 8. October 2016
 *  @version 0.1
 */

#include <sstream>

#include "rtx_logger.hpp"
#include "usr_Comm.hpp"

namespace usr {

  void msg_ack(const rtx::Protocol::Message& msg) {
    std::stringstream buf;
    buf << "<1:ACK," << msg.id.c_str() << ',' << msg.argc << '>';
    gLogger.printf("%s\n", buf.str().c_str());
  }

  void msg_debug(const rtx::Protocol::Message& msg) {
    std::stringstream buf;

    buf << "<1:ARG";
    for(size_t i = 0; i < msg.argc; i++)
      buf << ',' << msg.argv[i];
    buf << '>';

    gLogger.printf("%s\n", buf.str().c_str());
  }

  void Comm::onMessage(const rtx::Protocol::Message& msg) {
    msg_ack(msg);
    msg_debug(msg);
  }

}
