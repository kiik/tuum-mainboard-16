/** @file rtx_protocol.cpp
 *  @brief Low level protocol handler implementation.
 *
 *  @authors Meelik Kiik
 *  @date 7. October 2016
 *  @version 0.1
 */

#include <algorithm>
#include <string.h>

#include "rtx_logger.hpp"
#include "rtx_protocol.hpp"

namespace rtx {

  const char* PACKET_BEGIN = "<";
  const char* PACKET_END = ">";
  const char* PACKET_ID_END = ":";
  const char* PACKET_PDELIM = ",";
  const int   PACKET_MAX_ARGC = 10;

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

  int Protocol::validate(std::string& in) {
    size_t os, os1, os2;

    // <1:om,12345,12345,12345,12345>
    // <1:x>
    if(in.size() > 60) return INV_PACKET;
    if(in.size() < 5) return INV_PACKET;

    os = in.find(PACKET_BEGIN);  // <
    if(os == std::string::npos) return INV_PACKET;

    os1 = in.find(PACKET_ID_END, os+2); // :
    if(os1 == std::string::npos) return INV_ID;

    // <:
    if(os1 <= (os + 1)) return INV_ID;

    os2 = in.find(PACKET_END, os1+2); // >
    if(os2 == std::string::npos) return INV_PARAM;

    size_t begin = in.find(PACKET_BEGIN),
           end = in.find(PACKET_END, begin+2);
    in = in.substr(begin, end - begin + 1);

    return 0;
  }

  int Protocol::parseIds(const std::string& in, Message& out) {
    size_t os1 = in.find(PACKET_BEGIN), os2 = in.find(PACKET_ID_END);
    //size_t os3 = in.find(PACKET_PDELIM); // ,

    out.id = in.substr(os1 + 1, os2 - os1 - 1);

    /*
    if((os3 == std::string::npos) || (os3 > os2)) {
    } else {
      out.id = in.substr(os1 + 1, os3 - os1 - 1);
      out.sId = in.substr(os3 + 1, os2 - os3 - 1);
    }*/

    return 0;
  }

  int Protocol::parseArgs(const std::string& in, Message& out) {

    // <1:om>1:om,0,0,0>

    int os1 = in.find(PACKET_ID_END), os2, os3 = in.find(PACKET_END);

    out.argc = std::count(in.begin() + os1, in.end(), *PACKET_PDELIM) + 1;
    if(out.argc == 0) return -1;

    //if(out.sId != "") out.argc--;

    out.argv = new char*[out.argc];

    int n = 0;
    std::string buf;

    os1++;
    size_t len;
    while(os2 != -1 && n < PACKET_MAX_ARGC) {
      os2 = in.find(PACKET_PDELIM, os1);
      if(os2 > os3) os2 = os3;

      len = os2 != -1 ? (os2 - os1) : in.length() - os1 - 1;

      if(len > 0) {
        buf = in.substr(os1, len);
        out.argv[n] = new char[buf.length()];
        strcpy(out.argv[n], buf.c_str());
      } else {
        out.argv[n] = new char[1];
        out.argv[n][0] = 0;
      }

      n++;
      os1 = os2 + 1;
    }

    return 0;
  }

}
