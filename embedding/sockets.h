#ifndef SOCKETS_H
#define SOCKETS_H

#include <stdio.h>
#include <iostream>
#include <sys/socket.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <string.h>
#include <boost/asio.hpp>

using boost::asio::ip::tcp;

class Sockets {
  tcp::acceptor serverSocket;
  tcp::socket clientSocket;
  int requestCount;
  int port;
  //Environment --> CLoopWhatever? env;
  
  int t;

public:

  Sockets();

  void start();

  void send();

  void receive();

  void update();

  ~Sockets();  
};

#endif
