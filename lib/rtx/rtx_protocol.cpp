/** @file rtx_protocol.cpp
 *  @brief Low level protocol handler implementation.
 *
 *  @authors Meelik Kiik
 *  @date 7. October 2016
 *  @version 0.1
 */

#include <algorithm>
#include <string.h>

#include "rtx_protocol.hpp"

namespace rtx {

  int Protocol::parseCommand(char* input, Message& out) {
    std::string in = std::string(input);

    int res = validate(in);
    if(res < 0) {
      //printf(":validate_input: Error %i!\n", res);
      return -1;
    }

    // Parse identificators
    res = parseIds(in, out);
    if(res < 0) {
      //printf(":parse_ids: Error %i!\n", res);
      return -2;
    }

    // Parse arguments
    res = parseArgs(in, out);
    if(res < 0) {
      //printf(":parse_args: Error %i!\n", res);
      return -3;
    }

    return 0;
  }

  int Protocol::validate(const std::string& in) {
    size_t os, os2;

    os = in.find(PACKET_BEGIN);
    if(os == std::string::npos) return INV_PACKET;

    os = in.find(PACKET_ID_END, os+2);
    if(os == std::string::npos) return INV_ID;

    os2 = in.find(PACKET_END, os+2);
    if(os2 == std::string::npos) return INV_PARAM;

    return 0;
  }

  int Protocol::parseIds(const std::string& in, Message& out) {
    int os1 = in.find(PACKET_BEGIN), os2 = in.find(PACKET_ID_END);
    int os3 = in.find(PACKET_PDELIM);

    if((os3 == std::string::npos) || (os3 > os2)) {
      out.id = in.substr(os1 + 1, os2 - os1 - 1);
    } else {
      out.id = in.substr(os1 + 1, os3 - os1 - 1);
      out.sId = in.substr(os3 + 1, os2 - os3 - 1);
    }

    return 0;
  }

  int Protocol::parseArgs(const std::string& in, Message& out) {
    int os1 = in.find(PACKET_ID_END), os2 = in.find(PACKET_END);

    out.argc = std::count(in.begin(), in.end(), *PACKET_PDELIM) + 1;
    if(out.sId != "") out.argc--;
    out.argv = new char*[out.argc];

    int n = 0;
    std::string buf;

    os1++;
    while(os2 != -1 && n < PACKET_MAX_ARGC) {
      os2 = in.find(PACKET_PDELIM, os1+1);

      buf = in.substr(os1, os2 != -1 ? (os2 - os1) : in.length() - os1 - 1);

      out.argv[n] = new char[buf.length() + 1];
      strncpy(out.argv[n], buf.c_str(), buf.length() + 1);

      n++;
      os1 = os2 + 1;
    }

    return 0;
  }

}
