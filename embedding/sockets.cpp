#include "sockets.h"

void Sockets::start()
{
  // read environment variables
  port = std::atoi(std::getenv("RL_ARGOS_PORT"));
  width = std::atoi(std::getenv("RL_ARGOS_WIDTH"));
  height = std::atoi(std::getenv("RL_ARGOS_HEIGHT"));
}

void Sockets::send() {
  
}

void Sockets::receive() {
}

void Sockets::update() {
}

Sockets::~Sockets() {
}
