/** @file rtx_llbus.hpp
 *  @brief Low-level communication bus interface.
 *
 *  @authors Meelik Kiik
 *  @date 8. October 2016
 *  @version 0.1
 */

#ifndef RTX_LLBUS_H
#define RTX_LLBUS_H

#include "mbed.h"

namespace rtx { namespace llb {

  extern Serial gBus;

  void setup();

  int read(char*&, size_t&);
  int write(char* size_t);

}}

#endif
