#include "sockets.h"

using boost::asio::ip::tcp;

void Sockets::start()
{
  // read environment variables
  port = std::atoi(std::getenv("ARGOS_PORT"));

  try
  {
    boost::asio::io_service io_service;
    tcp::acceptor serverSocket (io_service, tcp::endpoint(tcp::v4(), port));
    t = 0;

    // wait 10s for client to connect
    for(int i=0; i<100; i++)
    {
      tcp::socket clientSocket (io_service);
      serverSocket.accept(clientSocket);
    }
  }

  // handle any exceptions
  catch (std::exception& e)
  {
    std::cerr << e.what() << std::endl;
  }
}

void Sockets::send()
{
  try
  {
    // Frame
    std::vector<uint8_t> frame;
    // speed, distance from departure, proximity reading
    float state[24]; //TODO: replace with 24
    // TODO: get state info from environment
    
    // Send state info
    boost::system::error_code ignored_error;
    boost::asio::write(clientSocket, boost::asio::buffer(frame), ignored_error);
    boost::asio::write(clientSocket, boost::asio::buffer(state), ignored_error);
  }
  catch(std::exception& e)
  {
    std::cerr << e.what() << std::endl;
  }  
}

void Sockets::receive()
{
  try
  {
    float actions[8];
    requestCount++;
    boost::system::error_code error;

    clientSocket.read_some(boost::asio::buffer(actions), error);

    env.setActions(actions, 8);
  }
  catch (std::exception& e)
  {
    std::cerr << e.what() << std::endl;
  }
}

void Sockets::setEnvironment(Environment *env)
{
  this->env = *env;
}

void Sockets::update()
{
  try
  {
    receive();
    send();
    t++;
  }
  catch (std::exception& e)
  {
    std::cerr << e.what() << std::endl;
  }
}

Sockets::~Sockets()
{
  clientSocket.close();
  serverSocket.close();
}

int main()
{
  return 0;
}
