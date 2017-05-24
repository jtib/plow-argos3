#include <stdio.h>
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
  
  int width;
  int height;
  int t;
  int state_dim;
  int action_dim;

public:

  void start();

  void send();

  void receive();

  void update();

  ~Sockets();  
};
