PROJECT(footbot_controller)
cmake_minimum_required(VERSION 3.5)

include(./ARGoSCheckQTOpenGL.cmake)

add_library(crossroad_footbot_controller MODULE crossroad_footbot_controller.h crossroad_footbot_controller.cpp)
target_link_libraries(crossroad_footbot_controller
  /usr/local/lib/argos3/libargos3core_simulator.so
  /usr/local/lib/argos3/libargos3plugin_simulator_footbot.so
  /usr/local/lib/argos3/libargos3plugin_simulator_genericrobot.so
  ${QT_LIBRARIES} ${GLUT_LIBRARY} ${OPENGL_LIBRARY})

MESSAGE( STATUS "QT_LIBRARIES -> : " ${QT_LIBRARIES} )
MESSAGE( STATUS "GLUT_LIBRARY -> : " ${GLUT_LIBRARY} )
MESSAGE( STATUS "OPENGL_LIBRARY -> : " ${OPENGL_LIBRARY} )