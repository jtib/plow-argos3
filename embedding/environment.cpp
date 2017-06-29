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

void Environment::setFrame(uchar* img, int count, int count_per_line)
{
  m_bytesCount = count;
  std::cerr << count << std::endl;
  m_bytesPerLine = count_per_line;
  std::cerr << count_per_line << std::endl;
  delete m_imgBits;
  m_imgBits = new uchar[count];
  std::copy(img, img + count, m_imgBits);
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

uchar * Environment::getFrame()
{
  return m_imgBits;
}

int Environment::getByteCount()
{
  return m_bytesCount;
}

int Environment::getByteCountPerLine()
{
  return m_bytesPerLine;
}
