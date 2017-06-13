#ifndef SOCKETS_H
#define SOCKETS_H

#include <stdio.h>
#include <iostream>
#include <sys/socket.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <string.h>
#include "environment.h"
#include <boost/asio.hpp>
#include <boost/shared_ptr.hpp>

using boost::asio::ip::tcp;

class Sockets {
  int port;
  boost::shared_ptr<tcp::acceptor> pServerSocket;
  boost::shared_ptr<tcp::socket> pClientSocket;
  int requestCount;

  Environment* m_env;

public:

  Sockets(Environment &env);

  void start();

  void send();

  void receive();

  ~Sockets();  
};

#endif
