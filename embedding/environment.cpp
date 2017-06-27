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

void Environment::setNbFb(int numFb)
{
  nbFb = numFb;
  m_speeds = new float[nbFb];
  m_distances = new float[nbFb];
  m_proximities = new float[nbFb*48];
  m_actions = new float[nbFb];
}

int Environment::getNbFb()
{
  return nbFb;
}

void Environment::setActions(float * to_do)
{
  m_actions = to_do;
}

void Environment::setActions(std::vector<float> to_do)
{
  std::copy(to_do.begin(), to_do.end(), m_actions);
}

float * Environment::getpActions()
{
  return m_actions;
}

float Environment::getActions(const int id)
{
  return m_actions[id];
}

void Environment::setState(int fb_id, std::array<float, 48> proximities, float speed, float distance)
{
  memcpy(m_proximities + fb_id*48, proximities.data(), 48*sizeof(float));
  m_speeds[fb_id] = speed;
  m_distances[fb_id] = distance;
}

float * Environment::getProximities()
{
  return m_proximities;
}

float * Environment::getSpeeds()
{
  return m_speeds;
}

float * Environment::getDistances()
{
  return m_distances;
}
