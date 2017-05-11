PROJECT(charging_station)
cmake_minimum_required(VERSION 3.5)

 include(./ARGoSCheckQTOpenGL.cmake)

add_library(crossroad_loop_footbot MODULE
  crossroad_loop_footbot.h
  crossroad_loop_footbot.cpp)

target_link_libraries(crossroad_loop_footbot
  /usr/lib/argos3/libargos3core_simulator.so
  /usr/lib/argos3/libargos3plugin_simulator_entities.so
  /usr/lib/argos3/libargos3plugin_simulator_footbot.so
  /usr/lib/argos3/libargos3plugin_simulator_qtopengl.so
  ${QT_LIBRARIES} ${GLUT_LIBRARY} ${OPENGL_LIBRARY})

MESSAGE( STATUS "QT_LIBRARIES -> : " ${QT_LIBRARIES} )
MESSAGE( STATUS "GLUT_LIBRARY -> : " ${GLUT_LIBRARY} )
MESSAGE( STATUS "OPENGL_LIBRARY -> : " ${OPENGL_LIBRARY} )
