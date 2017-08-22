#ifndef CROSSROAD_FUNCTIONS_FB_H
#define CROSSROAD_FUNCTIONS_FB_H

#include <argos3/core/simulator/loop_functions.h>
#include <argos3/core/simulator/entity/floor_entity.h>
#include <argos3/plugins/robots/foot-bot/simulator/footbot_entity.h>
#include <argos3/plugins/simulator/visualizations/qt-opengl/qtopengl_render.h>
#include <argos3/plugins/simulator/visualizations/qt-opengl/qtopengl_camera.h>
#include <argos3/plugins/simulator/visualizations/qt-opengl/qtopengl_user_functions.h>
#include "../crossroad_footbot_controller/crossroad_footbot_controller.h"
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
#include <map>
#include <string>
#include <opencv2/imgproc/imgproc.hpp>

#ifdef __APPLE__
#include <glu.h>
#else
#include <GL/glu.h>
#endif

using namespace argos;

#define LINES 84
#define COLS 84

class CCrossroadFunctionsFb : public CLoopFunctions {

public:

 CCrossroadFunctionsFb();
 virtual ~CCrossroadFunctionsFb() {}
 void Init(TConfigurationNode& t_node);
 void Update();
 virtual void PreStep();
 virtual void PostStep();
 virtual bool IsExperimentFinished();

private:

  void ResetPosition();
  // Removes footbots that have reached a wall (including the road walls).
  void RemoveFootBotsAgainstWalls();
  void AddFootBots();
  void SetPovCamera();
  CQuaternion OrientationFromPosition(CVector3 pos);
  uchar * PreprocessFrame(uchar * frame, int bc, int bcl,
      int bc_after, int bcl_after);

  CSimulator* m_Simulator;

  CQTOpenGLRender* m_Renderer;
  CQTOpenGLCamera* m_Camera;
  CQTOpenGLCamera::SSettings* m_CameraSettings;
  CFootBotEntity* m_SelectedEntity;
  CFootBotEntity* m_pcEFootBot;
  CFootBotCrossroadController* m_pcController;
  std::string m_chosen;
  std::string dataExchanged;
  Environment m_env;
  Sockets m_soc;

  // Added attributes
  CQuaternion m_orient1;
  CQuaternion m_orient2;
  CQuaternion m_orient3;
  CQuaternion m_orient4;
};

#endif
