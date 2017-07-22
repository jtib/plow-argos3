PROJECT(embedding)
cmake_minimum_required(VERSION 3.5)

set(ARGOS_PREFIX ${ARGOS_PREFIX} CACHE INTERNAL "")
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${ARGOS_PREFIX}/share/argos3/cmake /usr/share/argos3/cmake /store/argos/argos3/src/cmake/)


set(Boost_USE_STATIC_LIBS OFF)
set(Boost_USE_MULTITHREADED ON)
set(Boost_USE_STATIC_RUNTIME OFF)

find_package(Boost COMPONENTS system REQUIRED)

# The location of this file may vary
include(/usr/share/argos3/cmake/ARGoSCheckQTOpenGL.cmake)

find_package(Lua52 REQUIRED)

include_directories(${CMAKE_SOURCE_DIR} ${ARGOS_INCLUDE_DIRS} ${LUA_INCLUDE_DIR} ${Boost_INCLUDE_DIRS})

link_directories(${ARGOS_LIBRARY_DIRS})

add_library(environment MODULE environment.h environment.cpp)
add_library(sockets MODULE sockets.h sockets.cpp)

# The location of these libraries may vary
target_link_libraries(environment
  /usr/lib/argos3/libargos3core_simulator.so
  /usr/lib/argos3/libargos3plugin_simulator_entities.so
  /usr/lib/argos3/libargos3plugin_simulator_footbot.so
  /usr/lib/argos3/libargos3plugin_simulator_qtopengl.so
  ${QT_LIBRARIES} ${GLUT_LIBRARY} ${OPENGL_LIBRARY} ${Boost_LIBRARIES})

target_link_libraries(sockets
  /usr/lib/argos3/libargos3core_simulator.so
  /usr/lib/argos3/libargos3plugin_simulator_entities.so
  /usr/lib/argos3/libargos3plugin_simulator_footbot.so
  /usr/lib/argos3/libargos3plugin_simulator_qtopengl.so
  ${QT_LIBRARIES} ${GLUT_LIBRARY} ${OPENGL_LIBRARY} ${Boost_LIBRARIES})
