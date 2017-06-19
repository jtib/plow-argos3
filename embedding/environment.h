#ifndef ENVIRONMENT_H
#define ENVIRONMENT_H

#include <stdio.h>
#include <iostream>
#include <string.h>
#include <stdlib.h>
#include <stdint.h>
#include <vector>
#include <argos3/plugins/robots/foot-bot/control_interface/ci_footbot_proximity_sensor.h>

#define STATE_SIZE 50
#define PROXIM_SIZE 48

class Environment
{
  int m_nbFb;

  float * p_state;

  //std::vector<argos::CCI_FootBotProximitySensor::TReadings> m_proximities;
  //std::vector<float> m_speeds;
  //std::vector<float> m_distances;
  
  float * p_actions;
  //std::vector<float> m_actions;

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
   * Get the size of the state
   */
  int getStateSize();

  /**
   * Get the size of the actions array
   */
  int getActionsSize();

  /**
   * Set the next actions to execute.
   */
  void setActions(float* to_do);

  /**
   * Get pointer to actions
   */
  float * getpActions();

  /**
   * Sends the footbot whose id it is the action it must do.
   * Called from the loop.
   */
  float getActions(const int id);

  /**
   * Convert TReadings into float array
   */
  void convertProximities(int fbId, argos::CCI_FootBotProximitySensor::TReadings& proximities);

  /**
   * Sets the state for one fb
   */
  void setState(int fb_id, float * proximities, float speed, float distance);

  ///**
  // * Get the proximities as one huge vector
  // */
  //float * getProximities();

  ///**
  // * Get the speeds
  // */
  // getSpeeds();

  ///**
  // * Get the distances
  // */
  //std::vector<float> getDistances();
  
  /**
   * Get the state
   */
  float * getState();

};

#endif
