#include <argos3/core/utility/logging/argos_log.h>
#include <argos3/core/utility/configuration/argos_configuration.h>
#include <argos3/plugins/simulator/entities/box_entity.h>
#include <QImage>
#include "crossroad_loop_footbot.h"
#include <unistd.h>

static const Real POV_HEIGHT = 0.2f;

CCrossroadFunctionsFb::CCrossroadFunctionsFb() :
		m_pcController(NULL),
		m_pcEFootBot(NULL),
        m_env(),
        m_soc(m_env){}

/****************************************/
/****************************************/

void CCrossroadFunctionsFb::Init(TConfigurationNode& t_node) {
  std::cerr << "entering loop init" << std::endl;
  
  //get a map of the footbots
  CSpace::TMapPerType& fbMap = *(&GetSpace().GetEntitiesByType("foot-bot"));
  // number of footbots
  int nbFb = fbMap.size();
  m_env.setFbNumber(nbFb);
  // start the socket
  m_soc.start();
  std::cerr << "soc started" << std::endl;

  std::vector<CFootBotEntity*> m_pcEFootbots (nbFb);
  std::vector<CFootBotCrossroadController*> m_pcControllers (nbFb);
  std::string str;
  //for the initial velocities
  std::vector<float> init_velocities (nbFb, 0.0);
  
  int j;
  CSpace::TMapPerType::iterator it;

  for(it = fbMap.begin(), j = 0; it != fbMap.end(); ++it, ++j)
  {
    str = it->first;
    m_pcEFootbots[j] = dynamic_cast<CFootBotEntity*>(&GetSpace().GetEntity(str));
    m_pcControllers[j] = &dynamic_cast<CFootBotCrossroadController&>((m_pcEFootbots[j])->GetControllableEntity().GetController());
    m_pcControllers[j]->setEnvironment(&m_env);
    m_pcControllers[j]->setFbId(j);
    std::cerr << "Getting initial velocities" << std::endl;
    init_velocities[j] = m_pcControllers[j]->getInitialVelocity();
    std::cerr << "initial velocity: " << j << " " << str << " " << init_velocities[j] << std::endl;
  }
  
  // don't break existing code while it's not adapted
  m_pcEFootBot = dynamic_cast<CFootBotEntity*>(&GetSpace().GetEntity("fu0"));
  m_pcController = &dynamic_cast<CFootBotCrossroadController&>(m_pcEFootBot->GetControllableEntity().GetController());

  // set initial velocities in the environment
  std::cerr << "Setting initial velocities" << std::endl;
  m_env.setActions(init_velocities);

  std::cerr << "loop functions initialized" << std::endl;
}

/****************************************/
/****************************************/

void CCrossroadFunctionsFb::SetPovCamera()
{
    m_Renderer = dynamic_cast<CQTOpenGLRender*>(&GetSimulator().GetVisualization());
    m_Camera = &m_Renderer->GetMainWindow().GetOpenGLWidget().GetCamera();
    CQTOpenGLWidget *m_OpenGlWidget = &m_Renderer->GetMainWindow().GetOpenGLWidget();
    CQTOpenGLWidget::SFrameGrabData *frame = &m_OpenGlWidget->GetFrameGrabData();

    // http://doc.qt.io/qt-4.8/qimage.html#bits
    // save image
    /*
    m_OpenGlWidget->grabFrameBuffer().save("test.jpg", 0, frame->Quality);
    QImage img = m_OpenGlWidget->grabFrameBuffer();
    uchar* bits = img.bits();
    std::cout<< "Bits: " << sizeof(bits) << " byteCount: " << img.byteCount() << std::endl;
    */

    if(m_pcController != NULL){
    	m_pcController->img_bits = m_OpenGlWidget->grabFramebuffer().bits();
    	m_pcController->bytesCount = m_OpenGlWidget->grabFramebuffer().byteCount();
		m_pcController->bytesPerLine = m_OpenGlWidget->grabFramebuffer().bytesPerLine();
    }



    m_CameraSettings = &m_Camera->GetActiveSettings();
    m_SelectedEntity = dynamic_cast<CFootBotEntity*>(m_Renderer->GetMainWindow().GetOpenGLWidget().GetSelectedEntity());


    if(m_SelectedEntity != NULL){
        // get robot position and orientation
        CVector3 pos_vec = m_SelectedEntity->GetEmbodiedEntity().GetOriginAnchor().Position;
        CQuaternion orientation = m_SelectedEntity->GetEmbodiedEntity().GetOriginAnchor().Orientation;

        // get robot angle
        CRadians cZAngle, cYAngle, cXAngle;
        orientation.ToEulerAngles(cZAngle, cYAngle, cXAngle);

        // calculate camera direction vector
        double x = pos_vec.GetX() + cos(cZAngle.GetValue());
        double y = pos_vec.GetY() + sin(cZAngle.GetValue());
        // fixate X so you don't get tilt
        m_CameraSettings->Up.SetX(0);

        // set position and viewpoint target
        m_CameraSettings->Position.Set((double)(pos_vec.GetX()), (double)(pos_vec.GetY()), POV_HEIGHT);
        m_CameraSettings->Target.Set(x, y, POV_HEIGHT);
    }
}

/*************************************/
/*************************************/

void CCrossroadFunctionsFb::PreStep(){
  std::cerr << "entering prestep" << std::endl;
  usleep(10000000);
  if(m_env.getTime()!=0)
  {
    std::cerr << "trying to receive..." << std::endl;
    m_soc.receive();
  }
}

/*************************************/
/*************************************/

void CCrossroadFunctionsFb::PostStep(){
  std::cerr << "entering post-step" << std::endl;
  //ResetPosition();
  //SetPovCamera();

  //if(m_pcController != NULL){
  //  if(m_pcController->selected_robot != "none"){
  //    CFootBotEntity &cFootBot = dynamic_cast<CFootBotEntity&>(GetSpace().GetEntity(m_pcController->selected_robot));
  //    m_Renderer->GetMainWindow().GetOpenGLWidget().SelectEntity(cFootBot);
  //    //m_Renderer = dynamic_cast<CQTOpenGLRender*>(&GetSimulator().GetVisualization());
  //    //m_Renderer->GetMainWindow().GetOpenGLWidget().GetSelectedEntity();
  //  }
  //}

  m_env.incTime();
  m_soc.send();
  //CSpace::TMapPerType& boxes = GetSpace().GetEntitiesByType("box");
  //for(CSpace::TMapPerType::iterator it = boxes.begin(); it != boxes.end(); ++it) {
  //	CBoxEntity& box = *any_cast<CBoxEntity*>(it->second);
      //box.EnableLEDs(med);
  //}
}

/****************************************/
/****************************************/

void CCrossroadFunctionsFb::ResetPosition(){
  std::cerr << "resetting position" << std::endl;
	CSpace::TMapPerType& m_cFootbots = GetSpace().GetEntitiesByType("foot-bot");

	if(m_pcController != NULL){
		m_pcController->positions_all.clear();
	}

	for(CSpace::TMapPerType::iterator it = m_cFootbots.begin(); it != m_cFootbots.end(); ++it) {
		CFootBotEntity& cFootBot = *any_cast<CFootBotEntity*>(it->second);

		CQuaternion qOrientation = cFootBot.GetEmbodiedEntity().GetOriginAnchor().Orientation;
		CVector3 vPosition = cFootBot.GetEmbodiedEntity().GetOriginAnchor().Position;

		if(m_pcController != NULL){
	    	m_pcController->positions_all.insert(std::make_pair(cFootBot.GetId(), vPosition));
	    }

		// check up/down robots
		if(vPosition.GetX() >= 4.7 || vPosition.GetX() <= -4.7){ // map edge
			vPosition.SetX(vPosition.GetX() - (vPosition.GetX() * 2));
		}
		// check left/right robots
		if(vPosition.GetY()>= 4.7 || vPosition.GetY() <= -4.7){
			vPosition.SetY(vPosition.GetY() - (vPosition.GetY() * 2));
		}
		cFootBot.GetEmbodiedEntity().MoveTo(vPosition, qOrientation, false);
	}
}


REGISTER_LOOP_FUNCTIONS(CCrossroadFunctionsFb, "crossroad_loop_footbot")
