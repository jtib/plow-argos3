#ifndef ENVIRONMENT_H
#define ENVIRONMENT_H

#include <stdio.h>
#include <iostream>
#include <string.h>
#include <stdlib.h>
#include <stdint.h>
#include <boost/array.hpp>
#include <vector>
#include <boost/multi_array.hpp>
#include <array>

// argos2 includes
#include <argos3/plugins/robots/foot-bot/control_interface/ci_footbot_proximity_sensor.h>

class Environment
{
  std::array<std::array<std::array<float, 2>, 24>, 8> m_proximities;
  std::array<float, 8> m_speeds;
  std::array<float, 8> m_distances;
  std::array<std::array<float, 2>, 8> m_actions;

public:

  /**
   * The constructor.
   */
  Environment();

  void setActions(const std::array<std::array<float, 2>, 8>& to_do);

  /**
   * Sends the footbot whose id it is the action it must do.
   * Called from the loop.
   */
  std::array<float, 2>& getActions(const int id);

  /**
   * Sets the state
   */
  void setState(std::array<std::array<std::array>> proximities, std::array<float> speeds, std::array<float> distances);

};

#endif
