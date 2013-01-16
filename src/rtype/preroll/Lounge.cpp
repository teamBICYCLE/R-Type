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
#include "Client.hh"
#include "Room.hh"

using namespace TBSystem;

Lounge::Lounge(std::shared_ptr<network::sockets::ITcpSocket>& serverSocket)
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
  _clients.push_back(Client(clientSock, clientAddr));
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
  if (_rooms.size() > 3) {
    std::string err("err to much room already exist, try later\r\n");

    socket->send(err.c_str(), err.size());
    return true;
  }
  _rooms.emplace_back(4, *this);

  std::string rep("rep create OK " + std::to_string(_rooms.back().getId())
                  + "\r\n");

  movePlayerToRoom(playerId, _rooms.back().getId());
  socket->send(rep.c_str(), rep.size());
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
  if (playerIt == _clients.end()
      || roomIt == _rooms.end()
      || !roomIt->addPlayer(playerIt->getId())) return false;
}

const std::vector<Client>&
Lounge::getClients()
{
  return _clients;
}
