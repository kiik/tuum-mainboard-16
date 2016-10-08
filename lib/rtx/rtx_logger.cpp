/** @file rtx_logger.cpp
 *  @brief Global logger service implementation.
 *
 *  @authors Meelik Kiik
 *  @date 8. October 2016
 *  @version 0.1
 */

#include "rtx_llbus.hpp"
#include "rtx_logger.hpp"

namespace rtx {

  Logger::Logger()
  {

  }

  Serial* Logger::getHandle() { return &llb::gBus; }

  Logger logger;

}
