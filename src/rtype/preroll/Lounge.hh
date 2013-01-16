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

#include <vector>
#include <memory>
#include <system/network/ITcpSocket.hh>
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

public:
  void addClient(std::shared_ptr<Client>& c);
  const std::vector<Client>& getClients();

private:
  TBSystem::network::Listener _listener;
  std::vector<Client>         _clients;
  std::vector<Room>           _rooms;
};

#endif /* !_LOUNGE_H__ */