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
  int nbFb;

  //std::array<float, 384> m_proximities;
  float * m_speeds;
  float * m_distances;
  float * m_proximities;
  
  //float * m_actions;
  std::array<float, 8> m_actions;
  bool m_actions_executed;
  bool m_actions_updated;

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
   * Set time
   */
  void setTime(int time);

  /**
   * Increment time
   */
  void incTime();

  /**
   * Set the number of footbots
   */
  void setNbFb(int numFb);

  /**
   * Get the number of footbots
   */
  int getNbFb();

  /**
   * Set the next actions to execute.
   */
  //void setActions(float * to_do);
  void setActions(std::array<float, 8>& to_do);

  /**
   * Sends the footbot whose id it is the action it must do.
   * Called from the loop.
   */
  float getActions(const int id);

  /**
   * Sets the state for one fb
   */
  void setState(int fb_id, std::array<float, 48> proximities, float speed, float distance);

  /**
   * Get the proximities as one huge array
   */
  float * getProximities();

  /**
   * Get the speeds
   */
  float * getSpeeds();

  /**
   * Get the distances
   */
  float * getDistances();

};

#endif
