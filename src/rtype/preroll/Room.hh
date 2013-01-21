/*
 * -----------------------------------------------------------------------------
 * "THE BEER-WARE LICENSE" (Revision 42):
 * <duplom_t@epitech.eu> wrote this file. As long as you retain this notice you
 * can do whatever you want with this stuff. If we meet some day, and you think
 * this stuff is worth it, you can buy me a beer in return. Thomas Duplomb
 * -----------------------------------------------------------------------------
 */

#ifndef _ROOM_H__
#define _ROOM_H__

#include <memory>
#include <vector>
#include <string>
#include <system/network/ITcpSocket.hh>
#include <system/threads/Thread.hh>
#include "INetworkSerializable.hh"
#include "Client.hh"

class Lounge;

class Room : public INetworkSerializable {
public:
  enum Status {
    WAITING,
    INGAME
  };
  explicit Room(int maxplayers, Lounge& lounge);
  ~Room();

  int     getId() const;
  virtual std::string toString() const;
  std::vector<std::string> playersStateStrings() const;
  bool    addPlayer(int c);
  bool    removePlayer(int c);
  bool    isEmpty() const;

  void    launchGame(const Lounge& lounge);

  bool    isIn(int playerId);

private:
  static int          _s_lastID;
  int                 _id;
  Status              _st;
  unsigned int           _maxplayers;
  std::vector<int>    _playersIds;
  Lounge&             _lounge;
  Thread              t;
};

#endif /* !_ROOM_H__ */
