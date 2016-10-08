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

  Serial gBus(USBTX, USBRX);

  bool avail = false;

  char buffer[16];
  size_t char_seq = 0;

  void on_data() {
    while(gBus.readable()) buffer[char_seq++] = gBus.getc();

    if(buffer[char_seq - 1] == '\n') {
      avail = true;
      char_seq = 0;
    }
  }

  void setup() {
    gBus.attach(&on_data);
  }

  int read(char*& out, size_t& len) {
    if(!avail) return -1;

    len = char_seq + 1;
    out = new char[len];
    strncpy(out, buffer, len);

    return 0;
  }

  int write(char* in, size_t len) {
    gBus.printf(in);
    return 0;
  }

}}
