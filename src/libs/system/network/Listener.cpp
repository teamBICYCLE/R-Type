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
                         readCallback readCallback,
                         disconnectCallback disconnectCallback)
  : _socket(s)
  , _readCallback(readCallback)
  , _disconnectCallback(disconnectCallback)
{
}

Listener::Socket::~Socket()
{
}

Listener::Socket::Socket(const Socket& other)
  : _socket(other._socket)
  , _readCallback(other._readCallback)
  , _disconnectCallback(other._disconnectCallback)
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

bool Listener::Socket::operator==(const Socket& other) const
{
  return _socket->getUnderlyingSocket() == other._socket->getUnderlyingSocket();
}

bool  Listener::Socket::read()
{
  return _readCallback(_socket);
}

void  Listener::Socket::disconnect()
{
  _disconnectCallback();
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
                    readCallback readCallback,
                    disconnectCallback disconnectCallback)
{
  _sockets.emplace_back(s, readCallback, disconnectCallback);
}

void  Listener::execute()
{
  std::list<Socket*> l;

  for (auto& s : _sockets) {
    if (FD_ISSET(s._socket->getUnderlyingSocket(), &_set)) {
        if (!s.read()) {
          s.disconnect();
          l.push_back(&s);
        }
    }
  }
  for (auto& s : l) {
    _sockets.erase(std::find(_sockets.begin(), _sockets.end(), *s));
  }
}
}
}
