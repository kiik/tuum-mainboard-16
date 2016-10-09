/** @file usr_comm.cpp
 *  @brief Communication manager implementation.
 *
 *  @authors Meelik Kiik
 *  @date 8. October 2016
 *  @version 0.1
 */

#include <sstream>

#include "rtx_logger.hpp"
#include "usr_Comm.hpp"

namespace usr {

  Comm::cmd_map_t Comm::loadCommandMap() {
    Comm::cmd_map_t out;

    out["sp"] = ECMD_SetSpeed;
    out["mv"] = ECMD_Move;
    out["tr"] = ECMD_Turn;
    out["om"] = ECMD_Omni;

    out["pd"] = ECMD_SetPid;
    out["en"] = ECMD_SetEnc;

    return out;
  }

  Comm::ckw_map_t Comm::loadKeywordMap() {
    Comm::ckw_map_t out;

    out["deg"] = EKW_Degree;
    out["abs"] = EKW_Absolute;
    out["rel"] = EKW_Relative;

    out["dm"] = EKW_Diameter;
    out["rp"] = EKW_Report;

    return out;
  }

  const Comm::cmd_map_t Comm::cmdIdMap = Comm::loadCommandMap();
  const Comm::ckw_map_t Comm::cmdKwMap = Comm::loadKeywordMap();

  Comm::cmd_id_t Comm::getCommandId(const char* in) {
    cmd_map_t::const_iterator it;
    for(it = Comm::cmdIdMap.begin();it != Comm::cmdIdMap.end(); ++it) {
      if(it->first == in) {
        gLogger.printf("DBG:%s,%s,%i\n", in, it->first.c_str(), (it->first == in));
        return it->second;
      }
    }
    return ECMD_None;
  }

  Comm::cmd_kw_t Comm::getKeywordId(const char* in) {
    ckw_map_t::const_iterator it;
    for(it = Comm::cmdKwMap.begin();it != Comm::cmdKwMap.end(); ++it)
      if(it->first == in) return it->second;
    return EKW_None;
  }

  void msg_ack(const Message& msg) {
    std::stringstream buf;
    buf << "<1:ACK," << msg.id.c_str() << ',' << msg.argc << '>';
    gLogger.printf("%s\n", buf.str().c_str());
  }

  void msg_nocmd(const Message& msg) {
    std::stringstream buf;

    buf << "<1:UNK";
    for(size_t i = 0; i < msg.argc; i++)
      buf << ',' << msg.argv[i];
    buf << '>';

    gLogger.printf("%s\n", buf.str().c_str());
  }

  void msg_debug(const Message& msg) {
    std::stringstream buf;

    buf << "<1:ARG";
    for(size_t i = 0; i < msg.argc; i++)
      buf << ',' << msg.argv[i];
    buf << '>';

    gLogger.printf("%s\n", buf.str().c_str());
  }


  Comm::cmd_res_t Comm::callback(cmd_id_t cId, const Message& msg) {
    switch(cId)
    {
      case ECMD_SetSpeed:
        return onSetSpeed(msg);
      case ECMD_Move:
        return onMove(msg);
      case ECMD_Turn:
        return onTurn(msg);
      case ECMD_Omni:
        return onOmni(msg);
      case ECMD_SetPid:
        return onSetPid(msg);
      case ECMD_SetEnc:
        return onSetEnc(msg);
      default:
        return CRES_NoCmd;
    }
  }


  void Comm::onMessage(const Message& msg) {
    cmd_id_t cId = getCommandId(msg.argv[0]);
    cmd_res_t res = callback(cId, msg);

    switch(res) {
      case CRES_NoCmd:
        msg_nocmd(msg);
        break;
      case CRES_OK:
        msg_ack(msg);
        msg_debug(msg);
        break;
    }
  }

  Comm::cmd_res_t Comm::onSetSpeed(const Message& msg) {
    //TODO: Motor control

    std::stringstream buf;
    buf << "<1:TODO,onSetSpeed," << msg.id.c_str() << ',' << msg.argc << '>';
    gLogger.printf("%s\n", buf.str().c_str());

    return CRES_OK;
  }

  Comm::cmd_res_t Comm::onMove(const Message& msg) {
    //TODO: omni Move

    std::stringstream buf;
    buf << "<1:TODO,onMove," << msg.id.c_str() << ',' << msg.argc << '>';
    gLogger.printf("%s\n", buf.str().c_str());

    return CRES_OK;
  }

  Comm::cmd_res_t Comm::onTurn(const Message& msg) {
    //TODO: omni Turn

    std::stringstream buf;
    buf << "<1:TODO,onTurn," << msg.id.c_str() << ',' << msg.argc << '>';
    gLogger.printf("%s\n", buf.str().c_str());

    return CRES_OK;
  }

  Comm::cmd_res_t Comm::onOmni(const Message& msg) {
    //TODO: Omni drive

    std::stringstream buf;
    buf << "<1:TODO,onOmni," << msg.id.c_str() << ',' << msg.argc << '>';
    gLogger.printf("%s\n", buf.str().c_str());

    return CRES_OK;
  }

  Comm::cmd_res_t Comm::onSetPid(const Message& msg) {
    //TODO: Pid configuration
    std::stringstream buf;
    buf << "<1:TODO,onSetPid," << msg.id.c_str() << ',' << msg.argc << '>';
    gLogger.printf("%s\n", buf.str().c_str());

    return CRES_OK;
  }

  Comm::cmd_res_t Comm::onSetEnc(const Message& msg) {
    std::stringstream buf;
    buf << "<1:TODO,onSetEnc," << msg.id.c_str() << ',' << msg.argc << '>';
    gLogger.printf("%s\n", buf.str().c_str());

    if(msg.argv[0] == "dm") {
      //TODO: Set diameter
    } else if(msg.argv[0] == "rp") {
      //TODO: Encoder reporting
    }

    return CRES_OK;
  }

}
