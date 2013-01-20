/*
 * -----------------------------------------------------------------------------
 * "THE BEER-WARE LICENSE" (Revision 42):
 * <duplom_t@epitech.eu> wrote this file. As long as you retain this notice you
 * can do whatever you want with this stuff. If we meet some day, and you think
 * this stuff is worth it, you can buy me a beer in return. Thomas Duplomb
 * -----------------------------------------------------------------------------
 */

#ifndef _LISTENER_H__
#define _LISTENER_H__

#include <chrono>
#include <list>
#include <algorithm>
#include "ITcpSocket.hh"

namespace TBSystem {
namespace network {
class Listener {
  typedef std::function<bool (std::shared_ptr<sockets::ITcpSocket>&)>
    readCallback;
  typedef std::function<void ()>
    disconnectCallback;

  class Socket {
  public:
    Socket(std::shared_ptr<sockets::ITcpSocket>& s, readCallback readCallback,
           disconnectCallback disconnectCallback);
    ~Socket();
    Socket(const Socket& other);
    Socket(Socket&& other);
    friend void swap(Socket& lhs, Socket& rhs)
    {
      std::swap(lhs._socket, rhs._socket);
      std::swap(lhs._readCallback, rhs._readCallback);
    }
    Socket& operator=(Socket other);

  public:
    bool operator==(const Socket& other) const;
  public:
    bool  read();

    void  disconnect();

    friend class Listener;

  private:
    std::shared_ptr<sockets::ITcpSocket> _socket;
    readCallback _readCallback;
    disconnectCallback _disconnectCallback;
  };

public:
  Listener();
  ~Listener();

  void  addSocket(std::shared_ptr<sockets::ITcpSocket>& s,
                    readCallback readCallback,
                    disconnectCallback disconnectCallback);
  void  removeSocket(std::shared_ptr<sockets::ITcpSocket>& s);
  template< class Rep, class Period >
  bool  waitEvent(std::chrono::duration<Rep, Period> waitDuration);
  void  execute();

private:
  std::list<Socket> _sockets;
  fd_set  _set;
};

/**
 * Implementation of Listener templated classes
 */
template< class Rep, class Period >
bool  Listener::waitEvent(std::chrono::duration<Rep, Period> waitDuration)
{
  int maxfd = -1;
  struct timeval tv;
  int retval;

  // set the timeval used by select with waitDuration value
  tv.tv_sec = std::chrono::duration_cast
    <std::chrono::seconds>(waitDuration).count();
  tv.tv_usec = std::chrono::duration_cast
    <std::chrono::microseconds>(waitDuration).count();
  // init set to watch every handled sockets
  FD_ZERO(&_set);
  for (auto& s : _sockets) {
    maxfd = std::max(s._socket->getUnderlyingSocket(), maxfd);
    FD_SET(s._socket->getUnderlyingSocket(), &_set);
  }

  retval = select(maxfd + 1, &_set, nullptr, nullptr, &tv);

  return retval > 0;
}

} // namepsace network
} // namepsace TBSstem

#endif /* !_LISTENER_H__ */
