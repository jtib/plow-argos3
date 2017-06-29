#include "sockets.h"
#include <unistd.h>

using boost::asio::ip::tcp;

Sockets::Sockets(Environment &env):
  pServerSocket(NULL),
  pClientSocket(NULL)
{
  m_env = &env;
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
    
    pServerSocket = boost::shared_ptr<tcp::acceptor>(new tcp::acceptor(io_service, tcp::endpoint(tcp::v4(), port)));
    std::cerr << "pServerSocket assigned" << std::endl;
    
    pClientSocket = boost::shared_ptr<tcp::socket>(new tcp::socket(io_service));
    std::cerr << "pClientSocket assigned" << std::endl;
    pServerSocket->accept(*pClientSocket);
  }

  // handle any exceptions
  catch (std::exception& e)
  {
    std::cerr << e.what() << std::endl;
  }
}

void Sockets::send(std::string dataType)
{
  std::cerr << "sending" << std::endl;
  try
  {
    if(dataType == "frame")
    {
      // get frame
      std::vector<boost::asio::const_buffer> frame;
      int bc [2] = {m_env->getByteCount(), m_env->getByteCountPerLine()};
      frame.push_back(boost::asio::buffer(bc));
      frame.push_back(boost::asio::buffer(m_env->getFrame(), bc[0]));
      // send frame
      pClientSocket->send(frame);
    }
    else if(dataType == "numerical")
    {
      // get state
      std::vector<boost::asio::const_buffer> state;
      state.push_back(boost::asio::buffer(m_env->getProximities(), (m_env->getNbFb())*48*sizeof(float)));
      state.push_back(boost::asio::buffer(m_env->getSpeeds(), (m_env->getNbFb())*sizeof(float)));
      state.push_back(boost::asio::buffer(m_env->getDistances(), (m_env->getNbFb())*sizeof(float)));
      // Send state info
      pClientSocket->send(state);
    }
    else
    {
      std::vector<boost::asio::const_buffer> all;
      // get frame
      int bc [2] = {m_env->getByteCount(), m_env->getByteCountPerLine()};
      all.push_back(boost::asio::buffer(bc));
      all.push_back(boost::asio::buffer(m_env->getFrame(), bc[0]));
      // get state
      all.push_back(boost::asio::buffer(m_env->getProximities(), (m_env->getNbFb())*48*sizeof(float)));
      all.push_back(boost::asio::buffer(m_env->getSpeeds(), (m_env->getNbFb())*sizeof(float)));
      all.push_back(boost::asio::buffer(m_env->getDistances(), (m_env->getNbFb())*sizeof(float)));
      // Send state info
      pClientSocket->send(all);
    }
  }
  catch(std::exception& e)
  {
    std::cerr << e.what() << std::endl;
  }  
}

void Sockets::receive()
{
  std::cerr << "receiving" << std::endl;
  try
  {
    float * actions = m_env->getpActions();
    requestCount++;
    boost::system::error_code error;

    pClientSocket->read_some(boost::asio::buffer(actions, (m_env->getNbFb())*sizeof(float)), error);

    for(int i=0; i<m_env->getNbFb(); ++i)
      std::cout << actions[i] << std::endl;
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
