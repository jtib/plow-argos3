#include "environment.h"

Environment::Environment()
{
  m_footbot_ids.assign(0);
  m_fb_speeds.assign(0);
  m_fb_distances.assign(0);
  m_fb_proximities.assign(0);
}

void Environment::setActions(const float* to_do, const int len)
{
  m_actions.assign(to_do, to_do + len);
}

float Environment::sendActions(int id)
{
  return m_actions[id];
}

void Environment::getResults(float *state, uint8_t *frame)
{

}
