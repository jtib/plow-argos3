#ifndef ENVIRONMENT_H
#define ENVIRONMENT_H

#include <stdio.h>
#include <iostream>
#include <string.h>
#include <stdlib.h>
#include <stdint.h>
#include <vector>
#include <argos3/plugins/robots/foot-bot/control_interface/ci_footbot_proximity_sensor.h>

class Environment
{
  int m_nbFb;

  std::vector<argos::CCI_FootBotProximitySensor::TReadings> m_proximities;
  std::vector<float> m_speeds;
  std::vector<float> m_distances;
  
  std::vector<float> m_actions;

  int t;

public:

  /**
   * The constructor.
   */
  Environment();

  /**
   * Get time
   */
  int getTime();

  /**
   * Increment time
   */
  void incTime();

  /**
   * Set the number of footbots
   */
  void setFbNumber(int nbFb);

  /**
   * Set the next actions to execute.
   */
  void setActions(const std::vector<float>& to_do);

  /**
   * Sends the footbot whose id it is the action it must do.
   * Called from the loop.
   */
  float getActions(const int id);

  /**
   * Sets the state for one fb
   */
  void setState(int fb_id, argos::CCI_FootBotProximitySensor::TReadings& proximities, float speed, float distance);

  /**
   * Get the proximities as one huge vector
   */
  std::vector<float> getProximities();

  /**
   * Get the speeds
   */
  std::vector<float> getSpeeds();

  /**
   * Get the distances
   */
  std::vector<float> getDistances();

};

#endif
