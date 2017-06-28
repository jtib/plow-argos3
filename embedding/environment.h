#ifndef ENVIRONMENT_H
#define ENVIRONMENT_H

#include <stdio.h>
#include <iostream>
#include <string.h>
#include <stdlib.h>
#include <stdint.h>
#include <vector>
#include <array>

// argos includes
#include <argos3/plugins/robots/foot-bot/control_interface/ci_footbot_proximity_sensor.h>

using uchar = unsigned char;

class Environment
{
  int nbFb;

  float * m_speeds;
  float * m_distances;
  float * m_proximities;

  uchar * m_imgBits;
  int m_bytesCount;
  int m_bytesPerLine;
  
  float * m_actions;

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
  void setNbFb(int numFb);

  /**
   * Get the number of footbots
   */
  int getNbFb();

  /**
   * Set the next actions to execute.
   */
  void setActions(float * to_do);
  
  /**
   * Set actions with a vector
   */
  void setActions(std::vector<float> to_do);
  
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
   * Sets the state for one fb
   */
  void setState(int fb_id, std::array<float, 48> proximities, float speed, float distance);

  /**
   * Sets the frame
   */
  void setFrame(uchar* img, int count, int count_per_line);

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

  /**
   * Get the frame
   */
  uchar * getFrame();

  /**
   * Get the byte count
   */
  int getByteCount();

  /**
   * Get the byte count per line
   */
  int getByteCountPerLine();

};

#endif

