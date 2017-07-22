PROJECT(crossroad_loop_footbot)
cmake_minimum_required(VERSION 3.5)

set(ARGOS_PREFIX ${ARGOS_PREFIX} CACHE INTERNAL "")
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${ARGOS_PREFIX}/share/argos3/cmake /usr/share/argos3/cmake /store/argos/argos3/src/cmake/)

# Location may vary
include(/usr/share/argos3/cmake/ARGoSCheckQTOpenGL.cmake)

find_package(Qt5OpenGL)

find_package(Lua52 REQUIRED)

include_directories(${CMAKE_SOURCE_DIR} ${ARGOS_INCLUDE_DIRS} ${LUA_INCLUDE_DIR})

link_directories(${ARGOS_LIBRARY_DIRS})

add_library(crossroad_loop_footbot MODULE
  crossroad_loop_footbot.h
  crossroad_loop_footbot.cpp)

# Locations may vary
target_link_libraries(crossroad_loop_footbot
  ${CMAKE_CURRENT_LIST_DIR}/../embedding/build/libenvironment.so
  ${CMAKE_CURRENT_LIST_DIR}/../embedding/build/libsockets.so
  /usr/lib/argos3/libargos3core_simulator.so
  /usr/lib/argos3/libargos3plugin_simulator_entities.so
  /usr/lib/argos3/libargos3plugin_simulator_footbot.so
  /usr/lib/argos3/libargos3plugin_simulator_qtopengl.so
  ${QT_LIBRARIES} ${GLUT_LIBRARY} ${OPENGL_LIBRARY})

qt5_use_modules(crossroad_loop_footbot Widgets OpenGL)
