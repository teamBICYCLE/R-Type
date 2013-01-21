/*
 * -----------------------------------------------------------------------------
 * "THE BEER-WARE LICENSE" (Revision 42):
 * <duplom_t@epitech.eu> wrote this file. As long as you retain this notice you
 * can do whatever you want with this stuff. If we meet some day, and you think
 * this stuff is worth it, you can buy me a beer in return. Thomas Duplomb
 * -----------------------------------------------------------------------------
 */

#include "Room.hh"
#include <system/log/Log.hh>
#include "Lounge.hh"
#include "server.h"

using namespace TBSystem;

int Room::_s_lastID = 1;

Room::Room(int maxplayers, Lounge& lounge)
  : _id(_s_lastID++)
  , _st(WAITING)
  , _maxplayers(maxplayers)
  , _lounge(lounge)
{
}

Room::~Room()
{
}

std::string Room::toString() const
{
  return std::to_string(_id) + " "
    + std::to_string(_playersIds.size()) + " "
    + std::to_string(_maxplayers);
}

int     Room::getId() const
{
  return _id;
}

std::vector<std::string> Room::playersStateStrings() const
{
  std::vector<std::string> ret;
  for (int p : _playersIds) {
    auto c = std::find_if(_lounge.getClients().begin(),
                          _lounge.getClients().end(),
                          [p](const Client& _c) -> bool {
                          return _c.getId() == p;
                          });

    ret.emplace_back(std::to_string(p) + " WAITING");
  }
  return ret;
}

bool    Room::addPlayer(int id)
{
  auto it = std::find(_playersIds.begin(), _playersIds.end(), id);

  if (_playersIds.size() + 1 < _maxplayers && it == _playersIds.end()) {
    _playersIds.push_back(id);
    return true;
  }
  else {
    return false;
  }
}

bool    Room::removePlayer(int id)
{
  auto it = std::find(_playersIds.begin(), _playersIds.end(), id);

  if (it != _playersIds.end()) {
    log::debug << "COULD WITH " << id << log::endl;
    _playersIds.erase(it);
    return true;
  }
  else {
    log::debug << "could not do the thing with " << id << log::endl;
    return false;
  }
}

bool  Room::isEmpty() const
{
  return _playersIds.size() == 0;
}

void* launchServer(void* players);

void Room::launchGame(const Lounge& lounge)
{
  std::vector<std::string> *playersAddr = new std::vector<std::string>;

  for (int id : _playersIds) {
    auto it =
      std::find_if(lounge.getClients().begin(), lounge.getClients().end(),
                   [id](const Client& c) {
                   return c.getId() == id;
                   });

    playersAddr->push_back(it->getAddr().getIpString());
  }
  log::debug << "start game LOL !" << log::endl;
  t.start(&launchServer, playersAddr);
}

void* launchServer(void* param) {
  std::vector<std::string> *players = (std::vector<std::string>*)param;

  runServer(*players, "4242");
  return nullptr;
}

bool  Room::isIn(int playerId) {
  return std::find(_playersIds.begin(), _playersIds.end(), playerId) !=
    _playersIds.end();
}
