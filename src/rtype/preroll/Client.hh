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
#include <map>
#include <system/network/Addr.hh>
#include <system/network/ITcpSocket.hh>
#include <functional>

class Lounge;

class Client {
public:
  typedef std::function<bool (std::shared_ptr<
                              TBSystem::network::sockets::ITcpSocket>&,
                              Lounge& lounge,
                              std::string params)>
    protocolHandler;

public:
  Client(
         std::shared_ptr<TBSystem::network::sockets::ITcpSocket>& socket,
         TBSystem::network::Addr& addr
         );
  ~Client();

public:
  bool  operator==(const Client& other) const;

public:
  bool  handleRcv(
                  std::shared_ptr<TBSystem::network::sockets::ITcpSocket>& socket,
                  Lounge& lounge
                 );
  bool  handleAsk(
                  std::shared_ptr<TBSystem::network::sockets::ITcpSocket>& socket,
                  std::string buf,
                  Lounge& lounge
                 );

  void  welcome();
public:
  int getId() const;

private:
  static int            _s_lastID;
  std::map<std::string, protocolHandler> _s_commands;

  int                   _id;
  std::string           _ip;
  std::shared_ptr<TBSystem::network::sockets::ITcpSocket> _socket;
  TBSystem::network::Addr _addr;
  std::string             _commandLine;
};

#endif /* !_CLIENT_H__ */
