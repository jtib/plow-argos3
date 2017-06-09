PROJECT(footbot_controller)
cmake_minimum_required(VERSION 3.5)

set(ARGOS_PREFIX ${ARGOS_PREFIX} CACHE INTERNAL "")
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${ARGOS_PREFIX}/share/argos3/cmake /usr/share/argos3/cmake)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

include(./ARGoSCheckQTOpenGL.cmake)

find_package(Lua52 REQUIRED)

include_directories(${CMAKE_SOURCE_DIR} ${ARGOS_INCLUDE_DIRS} ${LUA_INCLUDE_DIR})

add_library(crossroad_footbot_controller MODULE crossroad_footbot_controller.h crossroad_footbot_controller.cpp)
target_link_libraries(crossroad_footbot_controller
  /usr/lib/argos3/libargos3core_simulator.so
  /usr/lib/argos3/libargos3plugin_simulator_footbot.so
  /usr/lib/argos3/libargos3plugin_simulator_genericrobot.so
  ${QT_LIBRARIES} ${GLUT_LIBRARY} ${OPENGL_LIBRARY})

MESSAGE( STATUS "QT_LIBRARIES -> : " ${QT_LIBRARIES} )
MESSAGE( STATUS "GLUT_LIBRARY -> : " ${GLUT_LIBRARY} )
MESSAGE( STATUS "OPENGL_LIBRARY -> : " ${OPENGL_LIBRARY} )
