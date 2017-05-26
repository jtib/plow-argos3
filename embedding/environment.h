#ifndef ENVIRONMENT_H
#define ENVIRONMENT_H

#include <stdio.h>
#include <iostream>
#include <string.h>
#include <stdlib.h>
#include <array>

class Environment
{
  int footbot_ids[8];
  float fb_speeds[8];
  float fb_distances[8];
  float fb_proximities[8]; // TODO: check what a proximity reading looks like
  std::array<float, 8> actions;

public:

  void setActions(const float to_do[]);

  /**
   * Sends the footbot whose id it is the action it must do.
   * Called from the controller.
   */
  int sendAction(int fb_id);

  /**
   * Returns the results (state + maybe frame) after the action
   * is executed.
   * Called from the controller.
   */
  void getResults();

};

#endif
