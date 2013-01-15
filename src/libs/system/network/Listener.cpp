/*
 * -----------------------------------------------------------------------------
 * "THE BEER-WARE LICENSE" (Revision 42):
 * <duplom_t@epitech.eu> wrote this file. As long as you retain this notice you
 * can do whatever you want with this stuff. If we meet some day, and you think
 * this stuff is worth it, you can buy me a beer in return. Thomas Duplomb
 * -----------------------------------------------------------------------------
 */

#include "Listener.hh"
#include <list>
#include <system/log/Log.hh>

using namespace TBSystem;

namespace TBSystem {
namespace network {

/**
 *  Listener::Socket
 *
 *  This is the underlying class used by Listener to handle a socket and its
 *  callbacks
 */
Listener::Socket::Socket(std::shared_ptr<sockets::ITcpSocket>& s,
                         readCallback readCallback)
  : _socket(s)
  , _readCallback(readCallback)
{
}

Listener::Socket::~Socket()
{
}

Listener::Socket::Socket(const Socket& other)
  : _socket(other._socket)
  , _readCallback(other._readCallback)
{
}

Listener::Socket::Socket(Socket&& other)
{
  swap(*this, other);
}

Listener::Socket& Listener::Socket::operator=(Socket other)
{
  swap(*this, other);
  return *this;
}

void  Listener::Socket::read(Listener& l)
{
  _readCallback(_socket, l);
}

void  Listener::Socket::disconnect()
{
  log::notice << "Disconnect callback call is not implemented" << log::endl;
}

/**
 * The Listener Class
 */
Listener::Listener()
{
}

Listener::~Listener()
{
}

void  Listener::addSocket(std::shared_ptr<sockets::ITcpSocket>& s,
                    readCallback readCallback)
{
  _sockets.emplace_back(s, readCallback);
}

void  Listener::execute()
{
  std::list<std::vector<Socket>::iterator> l;

  for (auto& s : _sockets) {
    if (FD_ISSET(s._socket->getUnderlyingSocket(), &_set)) {
        s.read(*this);
    }
  }
}
}
}
