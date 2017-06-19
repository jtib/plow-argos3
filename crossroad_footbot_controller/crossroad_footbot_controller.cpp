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

   selected_robot = "fu0";
}

/****************************************/
/****************************************/

void CFootBotCrossroadController::setEnvironment(Environment* env)
{
  m_env = env;
}

float CFootBotCrossroadController::getInitialVelocity()
{
  return m_fWheelVelocity;
}

std::string CFootBotCrossroadController::getstrId()
{
  return m_strId;
}

void CFootBotCrossroadController::setFbId(int FbId)
{
  m_fb_id = FbId;
}

/****************************************/
/****************************************/

std::array<float, 48> CFootBotCrossroadController::ConvertTReadings(CCI_FootBotProximitySensor::TReadings& proximities)
{
  std::array<float, 48> proxima;
  for(int i = 0; i<24; i++)
  {
    proxima[2*i] = proximities[i].Value;
    proxima[2*i+1] = proximities[i].Angle.GetValue();
  }
  return proxima;
}

/*************************************/
/*************************************/

void CFootBotCrossroadController::ControlStep() {
  std::cerr << "entering control step" << std::endl;
  // get the action to execute
  float wheel_speed = m_env->getActions(m_fb_id);
  std::cerr << "Action [" << m_fb_id << "]: " << wheel_speed << std::endl;
  // execute the action (throttle)
  m_pcWheels->SetLinearVelocity(wheel_speed, wheel_speed);

  // set the new state for this footbot
  CCI_FootBotProximitySensor::TReadings proximities = m_pcProximity->GetReadings();
  std::array<float, 48> proxim_readings = this->ConvertTReadings(proximities);
  m_distance += wheel_speed;
  m_env->setState(m_fb_id, proxim_readings, wheel_speed, m_distance);
  
  
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
