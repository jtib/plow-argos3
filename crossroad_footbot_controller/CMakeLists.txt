PROJECT(footbot_controller)
cmake_minimum_required(VERSION 3.5)

set(ARGOS_PREFIX ${ARGOS_PREFIX} CACHE INTERNAL "")
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${ARGOS_PREFIX}/share/argos3/cmake /usr/share/argos3/cmake /store/argos/argos3/src/cmake/)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(Boost_USE_STATIC_LIBS OFF)
set(Boost_USE_MULTITHREADED ON)
set(Boost_USE_STATIC_RUNTIME OFF)

# Location may vary
include(/usr/share/argos3/cmake/ARGoSCheckQTOpenGL.cmake)

find_package(Qt5OpenGL)

find_package(Boost COMPONENTS system REQUIRED)
find_package(Lua52 REQUIRED)

include_directories(${CMAKE_SOURCE_DIR} ${ARGOS_INCLUDE_DIRS} ${LUA_INCLUDE_DIR} ${BOOST_INCLUDE_DIRS})

# Locations may vary
add_library(crossroad_footbot_controller MODULE crossroad_footbot_controller.h crossroad_footbot_controller.cpp)

target_link_libraries(crossroad_footbot_controller
  /usr/local/lib/argos3/libargos3core_simulator.so
  /usr/local/lib/argos3/libargos3plugin_simulator_footbot.so
  /usr/local/lib/argos3/libargos3plugin_simulator_genericrobot.so
  ${QT_LIBRARIES} ${GLUT_LIBRARY} ${OPENGL_LIBRARY} ${Boost_LIBRARIES})

MESSAGE( STATUS "QT_LIBRARIES -> : " ${QT_LIBRARIES} )
MESSAGE( STATUS "GLUT_LIBRARY -> : " ${GLUT_LIBRARY} )
MESSAGE( STATUS "OPENGL_LIBRARY -> : " ${OPENGL_LIBRARY} )
