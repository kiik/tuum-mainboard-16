/** @file rtx_llbus.cpp
 *  @brief Low-level communication bus interface implementation.
 *
 *  @authors Meelik Kiik
 *  @date 8. October 2016
 *  @version 0.1
 */

#include <string.h>

#include "rtx_llbus.hpp"

namespace rtx { namespace llb {

  llbus_decl();

  packet_buf_t dataBuffer;

  void on_data() {
    while(gBus.readable()) dataBuffer.stream(gBus.getc());
  }

  void setup() {
    gBus.attach(&on_data);
  }

  int read(char*& out, size_t& len) {
    //__disable_irq();
    int res = dataBuffer.read(out, len);
    //__enable_irq();
    return res;
  }

  int write(char* in, size_t len) {
    gBus.printf(in);
    return 0;
  }

}}
