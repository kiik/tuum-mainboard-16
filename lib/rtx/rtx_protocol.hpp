/** @file rtx_protocol.hpp
 *  @brief Low level protocol handler.
 *
 *  @authors Meelik Kiik
 *  @date 7. October 2016
 *  @version 0.1
 */

#ifndef RTX_PROTOCOL_H
#define RTX_PROTOCOL_H

#include <string>

namespace rtx {

  static const char* PACKET_BEGIN = "<";
  static const char* PACKET_END = ">";
  static const char* PACKET_ID_END = ":";
  static const char* PACKET_PDELIM = ",";
  static const int   PACKET_MAX_ARGC = 10;

  class Protocol
  {
  public:

    typedef std::string msg_id;

    struct Message {
      msg_id id;   // Receiver id
      msg_id sId; // Sender id

      size_t argc;
      char** argv;

      Message():
        id(""), sId(""),
        argc(0), argv(NULL)
      {

      }

      ~Message() {
        cleanup();
      }

      void cleanup() {
        if(argv) {
          for(size_t i=0; i < argc; i++) free(argv[i]);
          free(argv);
          argv = NULL;
          argc = 0;
        }
      }

    };

    enum EParseError {
      INV_PACKET = -1,
      INV_ID     = -2,
      INV_PARAM  = -3,
    };

    static int parseCommand(char*, Message&);

  private:
    static int validate(const std::string&);

    static int parseIds(const std::string&, Message&);
    static int parseArgs(const std::string&, Message&);
  };

}

#endif
