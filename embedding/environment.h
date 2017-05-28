#ifndef ENVIRONMENT_H
#define ENVIRONMENT_H

#include <stdio.h>
#include <iostream>
#include <string.h>
#include <stdlib.h>
#include <stdint.h>
#include <boost/array.hpp>
#include <vector>

class Environment
{
  boost::array<int, 8> m_footbot_ids;
  boost::array<float, 8> m_fb_speeds;
  boost::array<float, 8> m_fb_distances;
  boost::array<float, 8> m_fb_proximities; // TODO: check what a proximity reading looks like
  std::vector<float> m_actions;

public:

  /**
   * The constructor.
   */
  Environment();

  void setActions(const float* to_do, const int len);

  /**
   * Sends the footbot whose id it is the action it must do.
   * Called from the loop.
   */
  int sendAction(int fb_id);

  /**
   * Returns the results (state + maybe frame) after the action
   * is executed.
   * Called from the loop.
   */
  void getResults(float *state, uint8_t *frame);

};

#endif
