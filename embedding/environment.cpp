#include "environment.h"

Environment::Environment()
{
  m_fb_speeds.assign(0);
  m_fb_distances.assign(0);
  for(int i=0; i<8; i++)
  {
    m_fb_proximities[i].fill(0);
  }
}

void Environment::setActions(const std::array<std::array<float, 2>, 8>& to_do)
{
  m_actions = to_do;
}

std::array<float, 2>& Environment::getActions(const int id)
{
  return m_actions[id];
}


void setState(std::array<std::array<std::array>> proximities, std::array<float> speeds, std::array<float> distances)
{
  //TODO: check lengths
  m_proximities = proximities;
  m_speeds = speeds;
  m_distances = distances;
}
