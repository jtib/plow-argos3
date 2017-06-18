#include "environment.h"

Environment::Environment()
{
  t = 0;
}

int Environment::getTime()
{
  return t;
}

void Environment::incTime()
{
  t++;
}

void Environment::setFbNumber(int nbFb)
{
  m_nbFb = nbFb;
  m_actions.assign(nbFb, 0.0);
  m_speeds.assign(nbFb, 0.0);
  m_distances.assign(nbFb, 0.0);
  argos::CCI_FootBotProximitySensor::TReadings proxim (24);
  m_proximities.assign(nbFb, proxim);
}

void Environment::setActions(const std::vector<float>& to_do)
{
  m_actions = to_do;
}

float Environment::getActions(const int id)
{
  return m_actions[id];
}

void Environment::setState(int fb_id, argos::CCI_FootBotProximitySensor::TReadings& proximities, float speed, float distance)
{
  m_proximities[fb_id] = proximities;
  m_speeds[fb_id] = speed;
  m_distances[fb_id] = distance;
}

std::vector<float> Environment::getProximities()
{
  std::vector<float> proxima;
  proxima.assign(2*24*m_nbFb, 0.0);
  for(int i=0; i<m_nbFb; i++)
  {
    for(int j=0; j<24; j++)
    {
      int I = i*48 + j*2;
      proxima[I] = m_proximities[i][j].Angle.GetValue();
      proxima[I+1] = m_proximities[i][j].Value;
    }
  }
  return proxima;
}

std::vector<float> Environment::getSpeeds()
{
  return m_speeds;
}

std::vector<float> Environment::getDistances()
{
  return m_distances;
}
