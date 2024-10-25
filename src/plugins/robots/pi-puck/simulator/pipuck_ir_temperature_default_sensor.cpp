//
// Created by hugo on 8-10-24.
//


#include "pipuck_ir_temperature_default_sensor.h"
#include "plugins/simulator/entities/cylinder_entity.h"

#include <argos3/core/utility/logging/argos_log.h>
#include <argos3/core/simulator/entity/composable_entity.h>
#include <argos3/core/simulator/entity/controllable_entity.h>
#include <argos3/core/simulator/entity/embodied_entity.h>
#include <argos3/core/simulator/physics_engine/physics_model.h>

namespace argos {

    /****************************************/
    /****************************************/

    void CPiPuckIRTemperatureDefaultSensor::SetRobot(CComposableEntity& c_entity) {
        m_pcControllableEntity = &(c_entity.GetComponent<CControllableEntity>("controller"));
        /* allocate memory for the sensor interfaces */
        m_vecSimulatedInterfaces.reserve(MAP_SENSOR_CONFIG.size());
        /* get the anchors for the sensor interfaces from m_mapSensorConfig */
        for(const std::pair<const UInt8, TConfiguration>& t_config : MAP_SENSOR_CONFIG) {
            const char* pchAnchor = std::get<const char*>(t_config.second);
            SAnchor& sAnchor =
                    c_entity.GetComponent<CEmbodiedEntity>("body").GetAnchor(pchAnchor);
            m_vecSimulatedInterfaces.emplace_back(t_config.first, sAnchor);
        }
    }

    /****************************************/
    /****************************************/

    void CPiPuckIRTemperatureDefaultSensor::Init(TConfigurationNode& t_tree) {
        try {
            CCI_PiPuckIRTemperatureSensor::Init(t_tree);
            GetNodeAttributeOrDefault(t_tree, "show_rays", m_bShowRays, m_bShowRays);
            this->ambientTemperature = 20.0; //Ambient temperature of the environment
        }
        catch(CARGoSException& ex) {
            THROW_ARGOSEXCEPTION_NESTED("Initialization error in the Pi-Puck ir temperature sensor.", ex);
        }
    }

    /****************************************/
    /****************************************/

    void CPiPuckIRTemperatureDefaultSensor::Update() {
        /* buffers */
        CRay3 cSensorRay;
        CVector3 cRayStart, cRayEnd;
        SEmbodiedEntityIntersectionItem sIntersection;

        double averageTemperature = 0.0;
        /* go through the sensors */
        for(SSimulatedInterface& s_interface : m_vecSimulatedInterfaces) {
            cRayStart = std::get<CVector3>(s_interface.Configuration);
            cRayStart.Rotate(s_interface.Anchor.Orientation);
            cRayStart += s_interface.Anchor.Position;
            cRayEnd = CVector3::Z * std::get<Real>(s_interface.Configuration);
            cRayEnd.Rotate(std::get<CQuaternion>(s_interface.Configuration));
            cRayEnd.Rotate(s_interface.Anchor.Orientation);
            cRayEnd += cRayStart;
            cSensorRay.Set(cRayStart,cRayEnd);
            /* Get the closest intersection */
            if(GetClosestEmbodiedEntityIntersectedByRay(sIntersection, cSensorRay)) {
                auto intersectedEntity = sIntersection.IntersectedEntity;
                if (intersectedEntity->GetParent().GetTypeDescription() == "person" ) { //If entity is a person

                    CCylinderEntity* cCylinder = dynamic_cast<CCylinderEntity*>(&intersectedEntity->GetParent());
                    if (cCylinder != nullptr) {
                        /* There is an intersection */
                        if (m_bShowRays) {
//                        if (s_interface.Label == 0 || s_interface.Label == 20) {
//                            m_pcControllableEntity->AddCheckedRay(true, cSensorRay);
//                        }
                            m_pcControllableEntity->AddIntersectionPoint(cSensorRay, sIntersection.TOnRay);
                        }
                        //According to the optical specifications of the STH34PF80 datasheet:
                        int labelMinusTen = s_interface.Label - 10;
                        s_interface.Temperature = cCylinder->GetTemperature();
                    }
                } else {
                    s_interface.Temperature = this->ambientTemperature; //If no intersection with person, temperature is ambient temperature
                    if(m_bShowRays) {
//                        if (s_interface.Label == 0 || s_interface.Label == 20) {
//                            m_pcControllableEntity->AddCheckedRay(false, cSensorRay);
//                        }
                    }
                }
            }
            else {
                /* No intersection */
                s_interface.Temperature = this->ambientTemperature; //If no intersection, temperature is ambient temperature
                if(m_bShowRays) {
//                    if (s_interface.Label == 0 || s_interface.Label == 20) {
//                        m_pcControllableEntity->AddCheckedRay(false, cSensorRay);
//                    }
                }
            }
            averageTemperature += s_interface.Temperature;
        }
        objectTemperature = averageTemperature / m_vecSimulatedInterfaces.size();
    }

    /****************************************/
    /****************************************/

    void CPiPuckIRTemperatureDefaultSensor::Reset() {
        for(SSimulatedInterface& s_interface : m_vecSimulatedInterfaces) {
            s_interface.Temperature = ambientTemperature;
        }
    }

    /****************************************/
    /****************************************/

    void CPiPuckIRTemperatureDefaultSensor::Visit(std::function<void(const SInterface&)> fn_visitor) {
//        argos::LOG << "Visiting" << std::endl;
        for(const SSimulatedInterface& s_interface : m_vecSimulatedInterfaces) {
            fn_visitor(s_interface);
        }
    }


    /****************************************/
    /****************************************/

    REGISTER_SENSOR(CPiPuckIRTemperatureDefaultSensor,
                    "pipuck_ir_temperature", "default",
                    "Hugo van Dijk [hugojpvandijk@gmail.com]",
                    "1.0",
                    "The Pi-Puck infrared temperature sensor.",
                    "The documentation for this sensor is \a.",
                    "Usable"
    );

}

