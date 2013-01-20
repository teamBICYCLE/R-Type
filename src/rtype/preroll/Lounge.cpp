/*
 * -----------------------------------------------------------------------------
 * "THE BEER-WARE LICENSE" (Revision 42):
 * <duplom_t@epitech.eu> wrote this file. As long as you retain this notice you
 * can do whatever you want with this stuff. If we meet some day, and you think
 * this stuff is worth it, you can buy me a beer in return. Thomas Duplomb
 * -----------------------------------------------------------------------------
 */

#include "Lounge.hh"
#include <functional>
#include <system/log/Log.hh>
#include <system/network/Udp.hh>
#include "Client.hh"
#include "Room.hh"

using namespace TBSystem;

Lounge::Lounge(std::shared_ptr<network::sockets::ITcpSocket>& serverSocket)
  : _bcSocket(new network::sockets::Udp)
{
  using namespace std::placeholders;

  _listener.addSocket(
                      serverSocket,
                      std::bind(&Lounge::acceptClient, this, _1),
                      std::bind(std::plus<int>(), 0, 0)
                     );
}

Lounge::~Lounge()
{
}

int Lounge::exec()
{
  while (1) {
    _listener.waitEvent(std::chrono::seconds(1));
    _listener.execute();
    broadcastInfos();
    log::info << "client connected count = " << _clients.size() << log::endl;
  }
  return 0;
}

bool  Lounge::acceptClient(std::shared_ptr<
                    TBSystem::network::sockets::ITcpSocket
                    >& socket)
{
  using namespace std::placeholders;

  // accept client and store its addr
  network::Addr clientAddr;
  std::shared_ptr<network::sockets::ITcpSocket>
    clientSock(socket->accept(clientAddr));

  // add him to the _client container, and get a reference to the object
  _clients.emplace_back(clientSock, clientAddr);
  Client& client = _clients.back();

  // bind client socket action to client
  _listener.addSocket(clientSock, std::bind(&Client::handleRcv, &client,
                                            _1, std::ref(*this)),
                      std::bind(&Lounge::handleClientDisconnect, this,
                                std::cref(client)));
  client.welcome();
  return true;
}

void  Lounge::handleClientDisconnect(const Client& c)
{
  removePlayerFromRoom(c.getId());
  _clients.erase(std::find(_clients.begin(), _clients.end(), c));
  // pensay a enlevay de la room si nessessaire
}

bool Lounge::sendRoomlist(std::shared_ptr<
                          TBSystem::network::sockets::ITcpSocket>& socket,
                  std::string params) const
{
  std::string ret;

  ret  = "rep roomlist start\r\n";
  for (auto& r : _rooms) {
    ret += "rep roomlist room " + r.toString() + "\r\n";
  }
  ret += "rep roomlist end\r\n";
  socket->send(ret.c_str(), ret.size());
  return true;
}

bool Lounge::sendRoomDetails(std::shared_ptr<
                             TBSystem::network::sockets::ITcpSocket>& socket,
                             std::string params) const
{
  std::stringstream ss(params);
  std::string junk;
  int id = -1;

  // drop command
  ss >> junk;
  // get the room asked id
  ss >> id;
  log::debug << "les animations de thibault c'est de la merde = " << id << log::endl;
  auto room = std::find_if(_rooms.begin(), _rooms.end(),
                           [id](const Room& room) -> bool {
                           return id == room.getId();
                           });
  if (room != _rooms.end()) {
    std::string ret("rep room_details " + std::to_string(id) + " start\r\n");

    std::vector<std::string> vec = room->playersStateStrings();
    for (auto& p : vec) {
      ret += "rep room_details " + std::to_string(id) + " player " + p + "\r\n";
    }
    ret += "rep room_details " + std::to_string(id) + " end\r\n";
    socket->send(ret.c_str(), ret.size());
  }
  else {
    std::string error("err no such room\r\n");

    socket->send(error.c_str(), error.size());
  }
  return true;
}

bool Lounge::createRoom(std::shared_ptr<
                TBSystem::network::sockets::ITcpSocket>& socket,
                std::string params, int playerId)
{
  std::string err;
  bool hasErr = false;

  if (std::find_if(_clients.begin(), _clients.end(), [playerId](Client& p) {
                   return p.getId() == playerId;
                   })->isInRoom()) {
    err = "Your are already in a room\r\n";
    log::debug << "MAIS iH " << err << log::endl;
    hasErr = true;
  }
  if (_rooms.size() > 3) {
    err = "err to much room already exist, try later\r\n";
    log::debug << "MAIS aH " << err << log::endl;
    hasErr = true;
  }
  if (hasErr == true) {
    log::debug << "MAIS OH " << err << log::endl;
    socket->send(err.c_str(), err.size());
    return true;
  }
  log::debug << "hello" << log::endl;
  _rooms.emplace_back(4, *this);

  std::string rep("rep create OK " + std::to_string(_rooms.back().getId())
                  + "\r\n");
  movePlayerToRoom(playerId, _rooms.back().getId());
  socket->send(rep.c_str(), rep.size());
  _rooms.back().launchGame(*this);
  return true;
}

bool Lounge::movePlayerToRoom(int playerId, int roomId)
{
  auto playerIt = std::find_if(_clients.begin(), _clients.end(),
                               [playerId](const Client& c) -> bool {
                                return c.getId() == playerId;
                               });
  auto roomIt = std::find_if(_rooms.begin(), _rooms.end(),
                             [roomId](const Room& r) -> bool {
                             return r.getId() == roomId;
                             });

  if (playerIt == _clients.end() || roomIt == _rooms.end()
      || !roomIt->addPlayer(playerId)) {
    return false;
  }
  playerIt->setInRoom(true);
  return true;
}

bool Lounge::removePlayerFromRoom(int playerId)
{
  bool ret = false;
  std::vector<std::list<Room>::iterator> itVect;

  for (auto it = _rooms.begin(); it != _rooms.end(); ++it) {
    ret |= it->removePlayer(playerId);
    if (it->isEmpty()) itVect.push_back(it);
  }
  for (auto& it : itVect) _rooms.erase(it);
  return ret;
}

bool  Lounge::removePlayerFromRoom(int playerId, int roomId)
{
  auto playerIt = std::find_if(_clients.begin(), _clients.end(),
                               [playerId](const Client& c) -> bool {
                                return c.getId() == playerId;
                               });
  auto roomIt = std::find_if(_rooms.begin(), _rooms.end(),
                             [roomId](const Room& r) -> bool {
                             return r.getId() == roomId;
                             });

  if (playerIt == _clients.end() || roomIt == _rooms.end()) {
    return false;
  }
  if (roomIt->removePlayer(playerId)) {
    if (roomIt->isEmpty()) _rooms.erase(roomIt);
    return true;
  }
  return false;
}

const std::list<Client>&
Lounge::getClients() const
{
  return _clients;
}

void Lounge::broadcastInfos()
{
  std::string s("42");
  network::Addr addr("255.0.0.37", "42424", "UDP");

  log::debug << "TODO ! " << s << log::endl;
  log::debug << "wrote = " << _bcSocket->send((uint8_t*)s.c_str(),
                                              s.size(), addr) << log::endl;
}
