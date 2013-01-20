/*
 * -----------------------------------------------------------------------------
 * "THE BEER-WARE LICENSE" (Revision 42):
 * <duplom_t@epitech.eu> wrote this file. As long as you retain this notice you
 * can do whatever you want with this stuff. If we meet some day, and you think
 * this stuff is worth it, you can buy me a beer in return. Thomas Duplomb
 * -----------------------------------------------------------------------------
 */

#ifndef _LOUNGE_H__
#define _LOUNGE_H__

#include <list>
#include <memory>
#include <system/network/ITcpSocket.hh>
#include <system/network/IUdpSocket.hh>
#include <system/network/Listener.hh>

class Client;
class Room;

class Lounge {
public:
  explicit Lounge(std::shared_ptr<TBSystem::network::sockets::ITcpSocket>&
                  serverSocket);
  ~Lounge();

public:
  int exec();

public:
  void broadcastInfos();

public:
  bool acceptClient(std::shared_ptr<
                    TBSystem::network::sockets::ITcpSocket
                    >& socket);
  void handleClientDisconnect(const Client& c);

public:
  bool sendRoomlist(std::shared_ptr<
                    TBSystem::network::sockets::ITcpSocket>& socket,
                    std::string params) const;
  bool sendRoomDetails(std::shared_ptr<
                       TBSystem::network::sockets::ITcpSocket>& socket,
                    std::string params) const;
  bool createRoom(std::shared_ptr<
                  TBSystem::network::sockets::ITcpSocket>& socket,
                  std::string params, int playerId);

public:
  bool movePlayerToRoom(int playerId, int roomId);
  bool removePlayerFromRoom(int playerId);
  bool removePlayerFromRoom(int playerId, int roomId);

public:
  void addClient(std::shared_ptr<Client>& c);
  const std::list<Client>& getClients() const;

private:
  TBSystem::network::Listener _listener;
  std::list<Client>         _clients;
  std::list<Room>           _rooms;
  std::shared_ptr<TBSystem::network::sockets::IUdpSocket> _bcSocket;
};

#endif /* !_LOUNGE_H__ */
