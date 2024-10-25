//
// Created by hugo on 8-10-24.
//

#ifndef ARGOS3_SIMULATOR_CI_PIPUCK_INFRARED_TEMPERATURE_SENSOR_H
#define ARGOS3_SIMULATOR_CI_PIPUCK_INFRARED_TEMPERATURE_SENSOR_H

namespace argos {
    class CCI_PiPuckIRTemperatureSensor;
}

#include <argos3/core/control_interface/ci_sensor.h>
#include <argos3/core/utility/math/vector3.h>
#include <argos3/core/utility/math/quaternion.h>

#include <map>
#include <tuple>
#include <functional>

namespace argos {

    class CCI_PiPuckIRTemperatureSensor : public CCI_Sensor {

    public:

        using TConfiguration = std::tuple<const char*, CVector3, CQuaternion, Real>;

        struct SInterface {
            SInterface(const UInt8& un_label) :
                    Label(un_label),
                    Configuration(MAP_SENSOR_CONFIG.at(un_label)),
                    Temperature(0.0),
                    SomethingElse(0.0){}
            const UInt8& Label;
            const TConfiguration& Configuration;
            Real Temperature;
            Real SomethingElse;

        };

        virtual ~CCI_PiPuckIRTemperatureSensor() {}

        virtual void Visit(std::function<void(const SInterface&)>) = 0;


#ifdef ARGOS_WITH_LUA
        virtual void CreateLuaState(lua_State* pt_lua_state);

        virtual void ReadingsToLuaState(lua_State* pt_lua_state);
#endif
    protected:

        static const std::map<UInt8, TConfiguration> MAP_SENSOR_CONFIG;

    };

}

#endif //ARGOS3_SIMULATOR_CI_PIPUCK_INFRARED_TEMPERATURE_SENSOR_H
