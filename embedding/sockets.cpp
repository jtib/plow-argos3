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
    // get state
    std::vector<boost::asio::const_buffer> state;
    state.push_back(boost::asio::buffer(env.getProximities()));
    state.push_back(boost::asio::buffer(env.getSpeeds()));
    state.push_back(boost::asio::buffer(env.getDistances()));
    // Send state info
    clientSocket.send(state);
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
    std::array<float, 8> actions;
    requestCount++;
    boost::system::error_code error;

    clientSocket.read_some(boost::asio::buffer(actions), error);

    env.setActions(actions);
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

Sockets::~Sockets()
{
  clientSocket.close();
  serverSocket.close();
}
