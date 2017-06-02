/* Include the controller definition */
#include "crossroad_footbot_controller.h"
/* Function definitions for XML parsing */
#include <argos3/core/utility/configuration/argos_configuration.h>
/* 2D vector definition */
#include <argos3/core/utility/math/vector2.h>
#include <argos3/core/utility/logging/argos_log.h>
#include <string>
#include <argos3/core/utility/math/angles.h>
#include <QImage>

#include "../embedding/global.h"

/****************************************/
/****************************************/

CFootBotCrossroadController::CFootBotCrossroadController() :
   img_bits(NULL),
   m_pcWheels(NULL),
   m_pcProximity(NULL),
   m_cAlpha(10.0f),
   m_fDelta(0.5f),
   m_fWheelVelocity(2.5f),
   m_cGoStraightAngleRange(-ToRadians(m_cAlpha),
                           ToRadians(m_cAlpha)) {}

/****************************************/
/****************************************/

void CFootBotCrossroadController::Init(TConfigurationNode& t_node) {
   /*
    * Get sensor/actuator handles
    *
    * The passed string (ex. "differential_steering") corresponds to the
    * XML tag of the device whose handle we want to have. For a list of
    * allowed values, type at the command prompt:
    *
    * $ argos3 -q actuators
    *
    * to have a list of all the possible actuators, or
    *
    * $ argos3 -q sensors
    *
    * to have a list of all the possible sensors.
    *
    * NOTE: ARGoS creates and initializes actuators and sensors
    * internally, on the basis of the lists provided the configuration
    * file at the <controllers><footbot_diffusion><actuators> and
    * <controllers><footbot_diffusion><sensors> sections. If you forgot to
    * list a device in the XML and then you request it here, an error
    * occurs.
    */
   m_pcWheels    = GetActuator<CCI_DifferentialSteeringActuator>("differential_steering");
   m_pcProximity = GetSensor  <CCI_FootBotProximitySensor      >("footbot_proximity"    );
   /*
    * Parse the configuration file
    *
    * The user defines this part. Here, the algorithm accepts three
    * parameters and it's nice to put them in the config file so we don't
    * have to recompile if we want to try other settings.
    */
   GetNodeAttributeOrDefault(t_node, "alpha", m_cAlpha, m_cAlpha);
   m_cGoStraightAngleRange.Set(-ToRadians(m_cAlpha), ToRadians(m_cAlpha));
   GetNodeAttributeOrDefault(t_node, "delta", m_fDelta, m_fDelta);
   GetNodeAttributeOrDefault(t_node, "velocity", m_fWheelVelocity, m_fWheelVelocity);
   m_fb_id = fb_ids[m_strId];

   selected_robot = "fu0";
}

/****************************************/
/****************************************/

void CFootBotCrossroadController::ControlStep() {
  // get the action to execute
  std::array<float, 2> action = env.getActions(m_fb_id);
  // execute the action (brake, acceleration)
  float wheel_speed = action[1] - action[0];
  m_pcWheels->SetLinearVelocity(wheel_speed, wheel_speed);
  
//   //RLOG << "Position: " << m_positioningSensor->GetReading().Position << std::endl;
//   if(img_bits != NULL){
//	   RLOG << "Img bits: " << img_bits << std::endl;
//	   RLOG << "Bytes count: " << bytesCount << std::endl;
//	   RLOG << "Bytes per line: " << bytesPerLine << std::endl;
//   }
//
//	std::map<std::string, CVector3>::iterator it = positions_all.begin();
//	for(; it != positions_all.end(); ++it){
//		RLOG << it->first << ". Readings: " << it->second << std::endl;
//	}
//
//	// TODO:
//	// images

}

/****************************************/
/****************************************/

/*
 * This statement notifies ARGoS of the existence of the controller.
 * It binds the class passed as first argument to the string passed as
 * second argument.
 * The string is then usable in the configuration file to refer to this
 * controller.
 * When ARGoS reads that string in the configuration file, it knows which
 * controller class to instantiate.
 * See also the configuration files for an example of how this is used.
 */
REGISTER_CONTROLLER(CFootBotCrossroadController, "crossroad_footbot_controller")
