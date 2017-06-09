#ifndef ENVIRONMENT_H
#define ENVIRONMENT_H

#include <stdio.h>
#include <iostream>
#include <string.h>
#include <stdlib.h>
#include <stdint.h>
#include <vector>
#include <array>

// argos2 includes
#include <argos3/plugins/robots/foot-bot/control_interface/ci_footbot_proximity_sensor.h>

class Environment
{
  std::array<std::array<std::array<float, 2>, 24>, 8> m_proximities;
  std::array<float, 8> m_speeds;
  std::array<float, 8> m_distances;
  
  std::array<float, 8> m_actions;
  bool m_actions_executed;
  bool m_actions_updated;

public:

  /**
   * The constructor.
   */
  Environment();

  /**
   * Set the next actions to execute.
   */
  void setActions(const std::array<float, 8>& to_do);

  /**
   * Sends the footbot whose id it is the action it must do.
   * Called from the loop.
   */
  float getActions(const int id);

  /**
   * Sets the state for one fb
   */
  void setState(int fb_id, std::array<std::array<float, 2>, 24> proximities, float speed, float distance);

  /**
   * Get the proximities as one huge array
   */
  std::array<float, 384> getProximities();

  /**
   * Get the speeds
   */
  std::array<float, 8> getSpeeds();

  /**
   * Get the distances
   */
  std::array<float, 8> getDistances();

};

#endif
