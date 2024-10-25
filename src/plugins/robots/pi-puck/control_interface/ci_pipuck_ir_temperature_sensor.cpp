//
// Created by hugo on 8-10-24.
//

#include "ci_pipuck_ir_temperature_sensor.h"

#ifdef ARGOS_WITH_LUA
#include <argos3/core/wrappers/lua/lua_utility.h>
#endif

namespace argos {

    /****************************************/
    /****************************************/

#ifdef ARGOS_WITH_LUA
    void CCI_PiPuckIRTemperatureSensor::CreateLuaState(lua_State* pt_lua_state) {
        CLuaUtility::StartTable(pt_lua_state, "ir_temperature");
        Visit([pt_lua_state] (const SInterface& s_interface) {
            CLuaUtility::StartTable(pt_lua_state, s_interface.Label + 1);
            CLuaUtility::AddToTable(pt_lua_state, "temperature", s_interface.Temperature);
            CLuaUtility::AddToTable(pt_lua_state, "somethingElse", s_interface.SomethingElse);
            CLuaUtility::StartTable(pt_lua_state, "transform");
            CLuaUtility::AddToTable(pt_lua_state, "position", std::get<CVector3>(s_interface.Configuration));
            CLuaUtility::AddToTable(pt_lua_state, "orientation", std::get<CQuaternion>(s_interface.Configuration));
            CLuaUtility::AddToTable(pt_lua_state, "anchor", std::get<const char*>(s_interface.Configuration));
            CLuaUtility::EndTable(pt_lua_state);
            CLuaUtility::EndTable(pt_lua_state);
        });
        CLuaUtility::EndTable(pt_lua_state);
    }
#endif

    /****************************************/
    /****************************************/

#ifdef ARGOS_WITH_LUA
    void CCI_PiPuckIRTemperatureSensor::ReadingsToLuaState(lua_State* pt_lua_state) {
        lua_getfield(pt_lua_state, -1, "ir_temperature");
        Visit([pt_lua_state] (const SInterface& s_interface) {
            lua_pushnumber(pt_lua_state, s_interface.Label + 1);
            lua_gettable(pt_lua_state, -2);
            lua_pushstring(pt_lua_state, "temperature");
            lua_pushnumber(pt_lua_state, s_interface.Temperature);
            lua_settable(pt_lua_state, -3);
            lua_pushstring(pt_lua_state, "somethingElse");
            lua_pushnumber(pt_lua_state, s_interface.SomethingElse);
            lua_settable(pt_lua_state, -3);
            lua_pop(pt_lua_state, 1); // label
        });
        lua_pop(pt_lua_state, 1);
    }
#endif


    /****************************************/
    /****************************************/

const std::map<UInt8, CCI_PiPuckIRTemperatureSensor::TConfiguration > CCI_PiPuckIRTemperatureSensor::MAP_SENSOR_CONFIG = {
//    std::make_pair(0, std::make_tuple("origin", CVector3( 0.0,0.0000, 0.0333), CQuaternion( 0.5 * CRadians::PI, CVector3(0, 1.0,0)), 4)), //Forward
//    std::make_pair(1, std::make_tuple("origin", CVector3( 0.0, 0.0000, 0.0333), CQuaternion(CRadians::PI * 20.0 / 180.0, CVector3(0.0, 0.0, 1.0)) * CQuaternion(0.5 * CRadians::PI, CVector3(0.0, 1.0, 0.0)), 4)),  // 20° Left
//    std::make_pair(2, std::make_tuple("origin", CVector3( 0.0, 0.0000, 0.0333), CQuaternion(CRadians::PI * 40.0 / 180.0, CVector3(0.0, 0.0, 1.0)) * CQuaternion(0.5 * CRadians::PI, CVector3(0.0, 1.0, 0.0)), 4)),  // 40° Left
//    std::make_pair(3, std::make_tuple("origin", CVector3( 0.0, 0.0000, 0.0333), CQuaternion(-CRadians::PI * 20.0 / 180.0, CVector3(0.0, 0.0, 1.0)) * CQuaternion(0.5 * CRadians::PI, CVector3(0.0, 1.0, 0.0)), 4)),  // 20° Right
//    std::make_pair(4, std::make_tuple("origin", CVector3( 0.0, 0.0000, 0.0333), CQuaternion(-CRadians::PI * 40.0 / 180.0, CVector3(0.0, 0.0, 1.0)) * CQuaternion(0.5 * CRadians::PI, CVector3(0.0, 1.0, 0.0)), 4))   // 40° Right
        std::make_pair(0, std::make_tuple("origin", CVector3(0.0, 0.0, 0.0333), CQuaternion(CRadians::PI * -40.0 / 180.0, CVector3(0.0, 0.0, 1.0)) * CQuaternion(0.5 * CRadians::PI, CVector3(0.0, 1.0, 0.0)), 4)),  // -40° Right
        std::make_pair(1, std::make_tuple("origin", CVector3(0.0, 0.0, 0.0333), CQuaternion(CRadians::PI * -36.0 / 180.0, CVector3(0.0, 0.0, 1.0)) * CQuaternion(0.5 * CRadians::PI, CVector3(0.0, 1.0, 0.0)), 4)),  // -36° Right
        std::make_pair(2, std::make_tuple("origin", CVector3(0.0, 0.0, 0.0333), CQuaternion(CRadians::PI * -32.0 / 180.0, CVector3(0.0, 0.0, 1.0)) * CQuaternion(0.5 * CRadians::PI, CVector3(0.0, 1.0, 0.0)), 4)),  // -32° Right
        std::make_pair(3, std::make_tuple("origin", CVector3(0.0, 0.0, 0.0333), CQuaternion(CRadians::PI * -28.0 / 180.0, CVector3(0.0, 0.0, 1.0)) * CQuaternion(0.5 * CRadians::PI, CVector3(0.0, 1.0, 0.0)), 4)),  // -28° Right
        std::make_pair(4, std::make_tuple("origin", CVector3(0.0, 0.0, 0.0333), CQuaternion(CRadians::PI * -24.0 / 180.0, CVector3(0.0, 0.0, 1.0)) * CQuaternion(0.5 * CRadians::PI, CVector3(0.0, 1.0, 0.0)), 4)),  // -24° Right
        std::make_pair(5, std::make_tuple("origin", CVector3(0.0, 0.0, 0.0333), CQuaternion(CRadians::PI * -20.0 / 180.0, CVector3(0.0, 0.0, 1.0)) * CQuaternion(0.5 * CRadians::PI, CVector3(0.0, 1.0, 0.0)), 4)),  // -20° Right
        std::make_pair(6, std::make_tuple("origin", CVector3(0.0, 0.0, 0.0333), CQuaternion(CRadians::PI * -16.0 / 180.0, CVector3(0.0, 0.0, 1.0)) * CQuaternion(0.5 * CRadians::PI, CVector3(0.0, 1.0, 0.0)), 4)),  // -16° Right
        std::make_pair(7, std::make_tuple("origin", CVector3(0.0, 0.0, 0.0333), CQuaternion(CRadians::PI * -12.0 / 180.0, CVector3(0.0, 0.0, 1.0)) * CQuaternion(0.5 * CRadians::PI, CVector3(0.0, 1.0, 0.0)), 4)),  // -12° Right
        std::make_pair(8, std::make_tuple("origin", CVector3(0.0, 0.0, 0.0333), CQuaternion(CRadians::PI * -8.0 / 180.0, CVector3(0.0, 0.0, 1.0)) * CQuaternion(0.5 * CRadians::PI, CVector3(0.0, 1.0, 0.0)), 4)),   // -8° Right
        std::make_pair(9, std::make_tuple("origin", CVector3(0.0, 0.0, 0.0333), CQuaternion(CRadians::PI * -4.0 / 180.0, CVector3(0.0, 0.0, 1.0)) * CQuaternion(0.5 * CRadians::PI, CVector3(0.0, 1.0, 0.0)), 4)),   // -4° Right
        std::make_pair(10, std::make_tuple("origin", CVector3(0.0, 0.0, 0.0333), CQuaternion(CRadians(0), CVector3(0.0, 0.0, 1.0)) * CQuaternion(0.5 * CRadians::PI, CVector3(0.0, 1.0, 0.0)), 4)),                // 0° Forward
        std::make_pair(11, std::make_tuple("origin", CVector3(0.0, 0.0, 0.0333), CQuaternion(CRadians::PI * 4.0 / 180.0, CVector3(0.0, 0.0, 1.0)) * CQuaternion(0.5 * CRadians::PI, CVector3(0.0, 1.0, 0.0)), 4)),   // 4° Left
        std::make_pair(12, std::make_tuple("origin", CVector3(0.0, 0.0, 0.0333), CQuaternion(CRadians::PI * 8.0 / 180.0, CVector3(0.0, 0.0, 1.0)) * CQuaternion(0.5 * CRadians::PI, CVector3(0.0, 1.0, 0.0)), 4)),   // 8° Left
        std::make_pair(13, std::make_tuple("origin", CVector3(0.0, 0.0, 0.0333), CQuaternion(CRadians::PI * 12.0 / 180.0, CVector3(0.0, 0.0, 1.0)) * CQuaternion(0.5 * CRadians::PI, CVector3(0.0, 1.0, 0.0)), 4)),  // 12° Left
        std::make_pair(14, std::make_tuple("origin", CVector3(0.0, 0.0, 0.0333), CQuaternion(CRadians::PI * 16.0 / 180.0, CVector3(0.0, 0.0, 1.0)) * CQuaternion(0.5 * CRadians::PI, CVector3(0.0, 1.0, 0.0)), 4)),  // 16° Left
        std::make_pair(15, std::make_tuple("origin", CVector3(0.0, 0.0, 0.0333), CQuaternion(CRadians::PI * 20.0 / 180.0, CVector3(0.0, 0.0, 1.0)) * CQuaternion(0.5 * CRadians::PI, CVector3(0.0, 1.0, 0.0)), 4)),  // 20° Left
        std::make_pair(16, std::make_tuple("origin", CVector3(0.0, 0.0, 0.0333), CQuaternion(CRadians::PI * 24.0 / 180.0, CVector3(0.0, 0.0, 1.0)) * CQuaternion(0.5 * CRadians::PI, CVector3(0.0, 1.0, 0.0)), 4)),  // 24° Left
        std::make_pair(17, std::make_tuple("origin", CVector3(0.0, 0.0, 0.0333), CQuaternion(CRadians::PI * 28.0 / 180.0, CVector3(0.0, 0.0, 1.0)) * CQuaternion(0.5 * CRadians::PI, CVector3(0.0, 1.0, 0.0)), 4)),  // 28° Left
        std::make_pair(18, std::make_tuple("origin", CVector3(0.0, 0.0, 0.0333), CQuaternion(CRadians::PI * 32.0 / 180.0, CVector3(0.0, 0.0, 1.0)) * CQuaternion(0.5 * CRadians::PI, CVector3(0.0, 1.0, 0.0)), 4)),  // 32° Left
        std::make_pair(19, std::make_tuple("origin", CVector3(0.0, 0.0, 0.0333), CQuaternion(CRadians::PI * 36.0 / 180.0, CVector3(0.0, 0.0, 1.0)) * CQuaternion(0.5 * CRadians::PI, CVector3(0.0, 1.0, 0.0)), 4)),  // 36° Left
        std::make_pair(20, std::make_tuple("origin", CVector3(0.0, 0.0, 0.0333), CQuaternion(CRadians::PI * 40.0 / 180.0, CVector3(0.0, 0.0, 1.0)) * CQuaternion(0.5 * CRadians::PI, CVector3(0.0, 1.0, 0.0)), 4)),  // 40° Left


    };

    /****************************************/
    /****************************************/

}
