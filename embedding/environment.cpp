#include "environment.h"

void Environment::setActions(const float to_do[])
{
  actions = to_do;
}

int Environment::sendAction(int fb_id)
{
  return actions[fb_id];
}

void Environment::getResults(float *state, uint8_t *frame)
{

}
