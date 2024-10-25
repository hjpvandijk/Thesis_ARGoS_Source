//
// Created by hugo on 8-10-24.
//

#ifndef PIPUCK_IR_TEMPERATURE_DEFAULT_SENSOR_H
#define PIPUCK_IR_TEMPERATURE_DEFAULT_SENSOR_H

namespace argos {
    class CPiPuckIRTemperatureDefaultSensor;
    class CControllableEntity;
    class CEmbodiedEntity;
    struct SAnchor;
}

#include <argos3/core/simulator/sensor.h>
#include <argos3/core/utility/math/vector3.h>
#include <argos3/core/utility/math/quaternion.h>
#include <argos3/plugins/robots/pi-puck/control_interface/ci_pipuck_ir_temperature_sensor.h>

namespace argos {

    class CPiPuckIRTemperatureDefaultSensor : public CSimulatedSensor,
                                             public CCI_PiPuckIRTemperatureSensor {

    public:

        struct SSimulatedInterface : SInterface {
            /* constructor */
            SSimulatedInterface(const UInt8& un_label,
                                const SAnchor& s_anchor) :
                    SInterface(un_label),
                    Anchor(s_anchor) {}
            /* members */
            const SAnchor& Anchor;
        };

        CPiPuckIRTemperatureDefaultSensor():
                m_bShowRays(false),
                m_pcControllableEntity(nullptr) {}

        virtual ~CPiPuckIRTemperatureDefaultSensor() {}

        virtual void SetRobot(CComposableEntity& c_entity);

        virtual void Init(TConfigurationNode& t_tree);

        virtual void Update();

        virtual void Reset();

        virtual void Visit(std::function<void(const SInterface&)>);

        double GetObjectTemperature(){
            return objectTemperature;
        }


    private:

        Real ConvertToMeters(Real f_raw) {
            static const Real fConversionFactor = Real(1.0);
            return (f_raw * fConversionFactor);
        }

        Real ConvertToLux(Real f_raw) {
            static const Real fConversionFactor = Real(1.0);
            return (f_raw * fConversionFactor);
        }

    private:

        bool m_bShowRays;
        CControllableEntity* m_pcControllableEntity;
        std::vector<SSimulatedInterface> m_vecSimulatedInterfaces;
        double ambientTemperature;
        double objectTemperature;

    };
}

#endif //ARGOS3_SIMULATOR_PIPUCK_IR_TEMPERATURE_SENSOR_H
