/** @file usr_comm.hpp
 *  @brief Communication manager module.
 *
 *  @authors Meelik Kiik
 *  @date 8. October 2016
 *  @version 0.1
 */

#ifndef USR_COMM_H
#define USR_COMM_H

#include <string>
#include <map>

#include "rtx_Comm.hpp"

using namespace rtx;

namespace usr {

  //sp,<motId>,<{deg/abs/rel(default)}>,<value>
  //mv,<{deg/abs/rel(default)}>,<value>,<dir(degrees)>
  //tr,

  /*
  pd P, I, D
  en dm(set diameter), rp(report)
  */

  typedef Protocol::Message Message;

  class Comm : public rtx::Comm
  {
  public:

    // FIXME: Use scoped enum when c11 is available.
    enum cmd_id_t {
      ECMD_None,

      ECMD_SetSpeed,
      ECMD_Move,
      ECMD_Turn,
      ECMD_Omni,

      ECMD_SetPid,
      ECMD_SetEnc,

      // ECMD_CHARGE,
      // ECMD_KICK,

      ECMD_Dribble,
      ECMD_DrbWrite,

      ECMD_GetPitchAngle,
      ECMD_SetPitchAngle,

      ECMD_GetBallStatus,

      ECMD_SetDiagnostics,
      ECMD_GetDiagnostics,
      
      ECMD_SetMotorSpeed,
      ECMD_GetMotorSpeed,

      ECMD_GetMotorEncoders

      // ECMD_BallSensor,

      // ECMD_Switch,
      // ECMD_getSwitch
    };

    enum cmd_kw_t {
      EKW_None,

      EKW_Degree,
      EKW_Absolute,
      EKW_Relative,

      EKW_Diameter,
      EKW_Report,
    };

    enum cmd_res_t {
      CRES_None   = -10,
      CRES_ERR    = -3,
      CRES_NoCmd  = -2,
      CRES_OK     =  0,
      CRES_DONE   =  1,
    };

    typedef std::map<std::string, cmd_id_t> cmd_map_t;
    typedef std::map<std::string, cmd_kw_t> ckw_map_t;

    cmd_res_t callback(cmd_id_t, const Message&);

    void onMessage(const Message&);

    cmd_res_t onSetSpeed(const Message&);
    cmd_res_t onMove(const Message&);
    cmd_res_t onTurn(const Message&);
    cmd_res_t onOmni(const Message&);

    cmd_res_t onSetPid(const Message&);
    cmd_res_t onSetEnc(const Message&);

    // cmd_res_t onCharge(const Message&);
    // cmd_res_t onKick(const Message&);

    cmd_res_t onDribble(const Message&);
    cmd_res_t onDrbWrite(const Message&);

    cmd_res_t getPitchAngle(const Message&);
    cmd_res_t setPitchAngle(const Message&);

    cmd_res_t getBallStatus(const Message&);

    cmd_res_t getDiagnostics(const Message&);
    cmd_res_t setDiagnostics(const Message&);

    cmd_res_t setMotorSpeed(const Message&);
    cmd_res_t getMotorSpeed(const Message&);

    cmd_res_t getMotorEncoders(const Message&);

    // cmd_res_t onBallSensor(const Message&);
    // cmd_res_t onSwitch(const Message&);
    // cmd_res_t onGetSwitch(const Message&);

    static cmd_map_t loadCommandMap();
    static ckw_map_t loadKeywordMap();

    static const cmd_map_t cmdIdMap;
    static const ckw_map_t cmdKwMap;

    static cmd_id_t getCommandId(const char*);
    static cmd_kw_t getKeywordId(const char*);

  };

}

#endif
