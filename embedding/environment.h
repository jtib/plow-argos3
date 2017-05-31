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
  boost::array<float, 8> m_fb_speeds;
  boost::array<float, 8> m_fb_distances;
  std::array<std::array<float, 24>, 8> m_fb_proximities;
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
};

#endif
