/*
 * -----------------------------------------------------------------------------
 * "THE BEER-WARE LICENSE" (Revision 42):
 * <duplom_t@epitech.eu> wrote this file. As long as you retain this notice you
 * can do whatever you want with this stuff. If we meet some day, and you think
 * this stuff is worth it, you can buy me a beer in return. Thomas Duplomb
 * -----------------------------------------------------------------------------
 */

#include "Client.hh"
#include <iostream>
#include <regex>
#include <system/log/Log.hh>
#include "Lounge.hh"

using namespace TBSystem::network;
using namespace TBSystem;

int Client::_s_lastID = 1;
std::map<std::string, Client::protocolHandler> create_map()
{
  using namespace std::placeholders;

  std::map<std::string,Client::protocolHandler> m;
  m["roomlist"] = std::bind(&Lounge::sendRoomlist, _2, _1, _3);
  m["room_details"] = std::bind(&Lounge::sendRoomDetails, _2, _1, _3);
  return m;
}

Client::Client(
               std::shared_ptr<sockets::ITcpSocket>& socket,
               Addr& addr
              )
  : _id(_s_lastID++)
  , _socket(socket)
  , _addr(addr)
  , _commandLine("")
{
  using namespace std::placeholders;
  _s_commands = create_map();
  _s_commands["create"] = std::bind(&Lounge::createRoom, _2, _1, _3, _id);
}

Client::~Client()
{
}

bool  Client::operator==(const Client& other) const
{
  return _id == other._id;
}

bool  Client::handleRcv(
                        std::shared_ptr<
                        TBSystem::network::sockets::ITcpSocket
                        >& socket,
                        Lounge& lounge
                       )
{
  std::regex  ask_regex("ask");
  char  buf[512];
  std::string::size_type pos;

  buf[socket->recv(buf, sizeof(buf))] = '\0';
  if (!buf[0]) return false;
  _commandLine += buf;

  while ((pos = _commandLine.find("\r\n")) != std::string::npos) {
    std::stringstream stream(_commandLine.substr(0, pos));
    std::string command;
    _commandLine = _commandLine.substr(pos + 2);

    stream >> command;
    std::cout << "client #" << _id << ": " << command << std::endl;

    auto it = _s_commands.find(command);
    if (it != _s_commands.end()) (it->second)(socket, lounge, stream.str());
    else {
      std::string error("err unknown command\r\n");

      socket->send(error.c_str(), error.size());
    }
  }
  return true;
}

void  Client::welcome()
{
  std::string welcomeString = "hi #" + std::to_string(_id) + "\r\n";
  _socket->send(welcomeString.c_str(), welcomeString.size());
}

int Client::getId() const
{
  return _id;
}
