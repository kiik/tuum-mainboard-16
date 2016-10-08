/** @file rtx_logger.hpp
 *  @brief Global logger service module.
 *
 *  @authors Meelik Kiik
 *  @date 8. October 2016
 *  @version 0.1
 */

#ifndef RTX_LOG_H
#define RTX_LOG_H

#include "mbed.h"

namespace rtx {

  class Logger
  {
  public:
    Logger();

    Serial* getHandle();

  };

  extern Logger logger;

}

#define gLogger (*(rtx::logger.getHandle()))

#endif
