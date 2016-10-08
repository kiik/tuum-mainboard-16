/** @file rtx_comm.hpp
 *  @brief Communication manager module.
 *
 *  @authors Meelik Kiik
 *  @date 8. October 2016
 *  @version 0.1
 */

#ifndef RTX_COMM_H
#define RTX_COMM_H

#include "rtx_protocol.hpp"

namespace rtx {

  class Comm
  {
  public:
    Comm();

    void setup();
    void process();

    void handleMessage(char*);

    virtual void onMessage(const Protocol::Message&) {};

  private:
    char*  buf;
    size_t blen;
  };

}

#endif
