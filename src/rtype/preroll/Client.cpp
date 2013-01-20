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
  , _isInRoom(false)
{
  using namespace std::placeholders;
  _s_commands = create_map();
  _s_commands["create"] = std::bind(&Lounge::createRoom, _2, _1, _3, _id);
  _s_commands["join"] = [=](std::shared_ptr<TBSystem::network::sockets::ITcpSocket>& l_socket,
                            Lounge& l_lounge,
                            std::string l_params) -> bool {
    std::stringstream ss(l_params);
    std::string junk;
    int roomId;

    ss >> junk;
    ss >> roomId;
      std::string rep;
    if (!_isInRoom && l_lounge.movePlayerToRoom(_id, roomId)) {
      _isInRoom = true;
      rep = "rep join OK " + std::to_string(roomId) + "\r\n";
    }
    else {
      rep = "err could not join room\r\n";
    }
    l_socket->send(rep.c_str(), rep.size());
    return true;
  };
  _s_commands["leave"] = [=](std::shared_ptr<TBSystem::network::sockets::ITcpSocket>& l_socket,
                            Lounge& l_lounge,
                            std::string l_params) -> bool {

    std::stringstream ss(l_params);
    std::string junk;
    int roomId;

    ss >> junk;
    ss >> roomId;
    log::debug << "tu m'as entendu " << roomId << " " << _id << log::endl;
    std::string rep;
    if (l_lounge.removePlayerFromRoom(_id, roomId)) {
      _isInRoom = false;
      rep = "rep leave OK " + std::to_string(roomId) + "\r\n";
    }
    else {
      rep = "err your are not in this room\r\n";
    }
    l_socket->send(rep.c_str(), rep.size());
    return true;
  };
  _s_commands["start"] = std::bind(&Client::startGame, this,
                                   _1, _2, _3);
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

bool  Client::startGame(
                        std::shared_ptr<
                        TBSystem::network::sockets::ITcpSocket
                        >& socket,
                        Lounge& lounge,
                        std::string params
                       )
{
  std::stringstream ss(params);
  std::string trash;
  int roomId;

  ss >> trash;
  ss >> roomId;
  if (!lounge.tryStartRoom(_id, roomId)) {
    trash = "rep could not start game\r\n";

    socket->send(trash.c_str(), trash.size());
  }
  return true;
}

void  Client::welcome()
{
  std::string welcomeString = "hi " + std::to_string(_id) + "\r\n";
  _socket->send(welcomeString.c_str(), welcomeString.size());
}

int Client::getId() const
{
  return _id;
}

const TBSystem::network::Addr& Client::getAddr() const
{
  return _addr;
}

void Client::setInRoom(bool b)
{
  _isInRoom = b;
}
bool Client::isInRoom() const
{
  return _isInRoom;
}
