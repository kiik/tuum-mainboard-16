/** @file usr_comm.cpp
 *  @brief Communication manager implementation.
 *
 *  @authors Meelik Kiik
 *  @date 8. October 2016
 *  @version 0.1
 */

#include <sstream>
#include <cstdlib>

#include "rtx_logger.hpp"
#include "rtx_PID.hpp"
#include "rtx_MotorController.hpp"
#include "rtx_Coil.hpp"

#include "usr_hw.hpp"
#include "usr_Comm.hpp"
#include "usr_motion.hpp"

#include "app.hpp"

namespace usr {

  Comm::cmd_map_t Comm::loadCommandMap() {
    Comm::cmd_map_t out;

    out["sp"] = ECMD_SetSpeed;
    out["mv"] = ECMD_Move;
    out["tr"] = ECMD_Turn;
    out["om"] = ECMD_Omni;

    out["pd"] = ECMD_SetPid;
    out["en"] = ECMD_SetEnc;

    out["kick"] = ECMD_KICK;
    out["chrg"] = ECMD_CHARGE;

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
      if(it->first == in) {
        gLogger.printf("DBG:%s\n", it->first.c_str());
        return it->second;
      }
    return EKW_None;
  }

  void msg_ack(const Message& msg) {
    std::stringstream buf;
    buf << "<1:ACK," << msg.id.c_str() << ',' << msg.argc << '>';
    gLogger.printf("%s\n", buf.str().c_str());
  }

  void msg_err(const Message& msg) {
    std::stringstream buf;
    buf << "<1:ERR," << msg.id.c_str() << ',' << msg.argc << '>';
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
      case ECMD_CHARGE:
        return onCharge(msg);
      case ECMD_KICK:
        return onKick(msg);
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
      case CRES_None:
        break;
      case CRES_ERR:
        msg_err(msg);
        msg_debug(msg);
        break;
      case CRES_DONE:
        break;
    }
  }

  Comm::cmd_res_t Comm::onSetSpeed(const Message& msg) {
    size_t c = msg.argc;

    if(c == 4) {
      switch(getKeywordId(msg.argv[2]))
      {
        case EKW_Degree:
        {
          int id = atoi(msg.argv[1]);
          if((id < 0) || (id >= MOTOR_COUNT)) return CRES_ERR;
          int val = atoi(msg.argv[3]);

          if(val < -10000) val = 10000;
          else if(val > 10000) val = 10000;

          gMotors[id]->setSpeed(val);
          break;
        }
        case EKW_None:
        break;
      }
    } else if(c == 3) {
      if(strcmp("enf", msg.argv[1]) >= 0) rtx::ENC_FILTER = atof(msg.argv[2]);
    } else {
      return CRES_ERR;
    }

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
    if(msg.argc < 4) return CRES_ERR;

    usr::omniDrive(atof(msg.argv[1]), atof(msg.argv[2]), atof(msg.argv[3]));

    return CRES_OK;
  }

  Comm::cmd_res_t Comm::onSetPid(const Message& msg) {
    PID::pid_size_t P, I, D;
    cmd_res_t res = CRES_None;

    if(msg.argc == 4) {
      P = atof(msg.argv[1]);
      I = atof(msg.argv[2]);
      D = atof(msg.argv[3]);
    }
    else if(msg.argc == 2) {
      if(strcmp("rst", msg.argv[1]) == 0) {
        P = gP;
        I = gI;
        D = gD;
      } else {
        res = CRES_ERR;
      }
    } else {
      res = CRES_ERR;
    }

    if(res == CRES_ERR) return res;

    for(size_t ix = 0; ix < MOTOR_COUNT; ix++) {
      PID* ptr = gMotors[ix]->getPID();
      ptr->setPID(P, I, D);
    }

    return CRES_OK;
  }

  Comm::cmd_res_t Comm::onSetEnc(const Message& msg) {
    std::stringstream buf;
    buf << "<1:TODO,onSetEnc," << msg.id.c_str() << ',' << msg.argc << '>';
    gLogger.printf("%s\n", buf.str().c_str());

    if(std::string(msg.argv[0]) == "dm") {
      //TODO: Set diameter
    } else if(std::string(msg.argv[0]) == "rp") {
      //TODO: Encoder reporting
    }

    return CRES_OK;
  }

  Comm::cmd_res_t Comm::onCharge(const Message& msg) {
    gCoil.startCharge();
    return CRES_OK;
  }

  Comm::cmd_res_t Comm::onKick(const Message& msg) {
    gCoil.startKick();
    return CRES_OK;
  }

}
