#ifndef CROSSROAD_FUNCTIONS_FB_H
#define CROSSROAD_FUNCTIONS_FB_H

#include <argos3/core/simulator/loop_functions.h>
#include <argos3/core/simulator/entity/floor_entity.h>
#include <argos3/plugins/robots/foot-bot/simulator/footbot_entity.h>
#include <argos3/plugins/simulator/visualizations/qt-opengl/qtopengl_render.h>
#include <argos3/plugins/simulator/visualizations/qt-opengl/qtopengl_camera.h>
#include <argos3/plugins/simulator/visualizations/qt-opengl/qtopengl_user_functions.h>
#include "/home/juliette/Documents/mila/plow-argos3/crossroad_footbot_controller/crossroad_footbot_controller.h"
//#include <QGLWidget>
#include <QElapsedTimer>
#include <argos3/plugins/robots/generic/control_interface/ci_differential_steering_actuator.h>
#include "../embedding/sockets.h"
#include "../embedding/environment.h"
#include <argos3/plugins/robots/foot-bot/control_interface/ci_footbot_proximity_sensor.h>
#include <argos3/core/utility/logging/argos_log.h>
#include <argos3/core/utility/configuration/argos_configuration.h>
#include <argos3/plugins/simulator/entities/box_entity.h>
#include <QImage>
#include <array>

#ifdef __APPLE__
#include <glu.h>
#else
#include <GL/glu.h>
#endif

using namespace argos;

class CCrossroadFunctionsFb : public CLoopFunctions {

public:

 CCrossroadFunctionsFb();
 virtual ~CCrossroadFunctionsFb() {}
 void Init(TConfigurationNode& t_node);
 void Update();
 virtual void PreStep();
 virtual void PostStep();

private:

  void ResetPosition();
  void SetPovCamera();

  CSimulator* m_Simulator;

  CQTOpenGLRender* m_Renderer;
  CQTOpenGLCamera* m_Camera;
  CQTOpenGLCamera::SSettings* m_CameraSettings;
  std::array<CFootBotEntity*, 8> m_pcEFootbots; 
  CFootBotEntity* m_SelectedEntity;
  CFootBotEntity* m_pcEFootBot;
  std::array<CFootBotCrossroadController*, 8> m_pcControllers;
  CFootBotCrossroadController* m_pcController;

  Environment m_env;
  Sockets m_soc;
};

#endif
