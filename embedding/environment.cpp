#include "environment.h"

Environment::Environment()
{
  m_speeds.fill(0);
  m_distances.fill(0);
  for(int i=0; i<8; i++)
  {
    for(int j=0; j<24; j++)
      m_proximities[i][j].fill(0);
  }
  //TODO: get initial random speed
  m_actions_executed = false;
  m_actions_updated = true;
}

void Environment::setActions(const std::array<float, 8>& to_do)
{
  m_actions = to_do;
}

float Environment::getActions(const int id)
{
  return m_actions[id];
}


void Environment::setState(int fb_id, std::array<std::array<float, 2>, 24> proximities, float speed, float distance)
{
  m_proximities[fb_id] = proximities;
  m_speeds[fb_id] = speed;
  m_distances[fb_id] = distance;
}

std::array<float, 384> Environment::getProximities()
{
  std::array<float, 384> proxima;
  for(int i=0; i<8; i++)
  {
    for(int j=0; j<24; j++)
    {
      int I = i*48 + j*2;
      proxima[I] = m_proximities[i][j][0];
      proxima[I+1] = m_proximities[i][j][1];
    }
  }
  return proxima;
}

std::array<float, 8> Environment::getSpeeds()
{
  return m_speeds;
}

std::array<float, 8> Environment::getDistances()
{
  return m_distances;
}
