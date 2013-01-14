/*
 * -----------------------------------------------------------------------------
 * "THE BEER-WARE LICENSE" (Revision 42):
 * <duplom_t@epitech.eu> wrote this file. As long as you retain this notice you
 * can do whatever you want with this stuff. If we meet some day, and you think
 * this stuff is worth it, you can buy me a beer in return. Thomas Duplomb
 * -----------------------------------------------------------------------------
 */

#ifndef _CLIENT_H__
#define _CLIENT_H__

#include <string>
#include <system/network/Tcp.hh>

namespace preroll {
class Client {
public:
  Client();
  ~Client();

private:
  unsigned int          _id;
  std::string           _ip;
  std::string           _login;
  TBSystem::network::sockets::Tcp _socket;
};
}

#endif /* !_CLIENT_H__ */
