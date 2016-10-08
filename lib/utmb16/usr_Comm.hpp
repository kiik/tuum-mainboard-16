/** @file usr_comm.hpp
 *  @brief Communication manager module.
 *
 *  @authors Meelik Kiik
 *  @date 8. October 2016
 *  @version 0.1
 */

#ifndef USR_COMM_H
#define USR_COMM_H

#include "rtx_Comm.hpp"

namespace usr {

  class Comm : public rtx::Comm
  {
  public:
    void onMessage(const rtx::Protocol::Message&);
  };

}

#endif
