#include "sockets.h"

using boost::asio::ip::tcp;

Sockets::Sockets(Environment* env):
  pServerSocket(NULL),
  pClientSocket(NULL)
{
  m_env = env;
}

void Sockets::start()
{
  // read environment variables
  port = std::atoi(std::getenv("ARGOS_PORT"));

  std::cerr << "port is " << port << std::endl;

  try
  {
    boost::asio::io_service io_service;
    std::cerr << "io_service created" << std::endl;
    boost::shared_ptr<tcp::acceptor> pServerSocket(new tcp::acceptor(io_service, tcp::endpoint(tcp::v4(), port)));
    std::cerr << "pServerSocket assigned" << std::endl;

    // wait 10s for client to connect
    for(int i=0; i<100; i++)
    {
      boost::shared_ptr<tcp::socket> pClientSocket(new tcp::socket(io_service));
      pServerSocket->accept(*pClientSocket);
      std::cerr << "pClientSocket assigned" << std::endl;
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
    state.push_back(boost::asio::buffer(m_env->getProximities()));
    state.push_back(boost::asio::buffer(m_env->getSpeeds()));
    state.push_back(boost::asio::buffer(m_env->getDistances()));
    // Send state info
    pClientSocket->send(state);
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

    pClientSocket->read_some(boost::asio::buffer(actions), error);

    m_env->setActions(actions);
  }
  catch (std::exception& e)
  {
    std::cerr << e.what() << std::endl;
  }
}

Sockets::~Sockets()
{
  pClientSocket->close();
  pServerSocket->close();
}
