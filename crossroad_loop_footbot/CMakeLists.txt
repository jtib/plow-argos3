PROJECT(crossroad_loop_footbot)
cmake_minimum_required(VERSION 3.5)

set(ARGOS_PREFIX ${ARGOS_PREFIX} CACHE INTERNAL "")
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${ARGOS_PREFIX}/share/argos3/cmake /usr/share/argos3/cmake)

include(/usr/share/argos3/cmake/ARGoSCheckQTOpenGL.cmake)

find_package(Qt5OpenGL)

find_package(Lua52 REQUIRED)

include_directories(${CMAKE_SOURCE_DIR} ${ARGOS_INCLUDE_DIRS} ${LUA_INCLUDE_DIR})

link_directories(${ARGOS_LIBRARY_DIRS})

add_library(crossroad_loop_footbot MODULE
  crossroad_loop_footbot.h
  crossroad_loop_footbot.cpp)

target_link_libraries(crossroad_loop_footbot
  /home/juliette/Documents/mila/plow-argos3/embedding/libenvironment.so
  /home/juliette/Documents/mila/plow-argos3/embedding/libsockets.so
  /usr/lib/argos3/libargos3core_simulator.so
  /usr/lib/argos3/libargos3plugin_simulator_entities.so
  /usr/lib/argos3/libargos3plugin_simulator_footbot.so
  /usr/lib/argos3/libargos3plugin_simulator_qtopengl.so
  ${QT_LIBRARIES} ${GLUT_LIBRARY} ${OPENGL_LIBRARY})

qt5_use_modules(crossroad_loop_footbot Widgets OpenGL)

MESSAGE( STATUS "QT_LIBRARIES -> : " ${QT_LIBRARIES} )
MESSAGE( STATUS "GLUT_LIBRARY -> : " ${GLUT_LIBRARY} )
MESSAGE( STATUS "OPENGL_LIBRARY -> : " ${OPENGL_LIBRARY} )
