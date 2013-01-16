/*
 * -----------------------------------------------------------------------------
 * "THE BEER-WARE LICENSE" (Revision 42):
 * <duplom_t@epitech.eu> wrote this file. As long as you retain this notice you
 * can do whatever you want with this stuff. If we meet some day, and you think
 * this stuff is worth it, you can buy me a beer in return. Thomas Duplomb
 * -----------------------------------------------------------------------------
 */

#include "Room.hh"
#include "Lounge.hh"

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
  if (_playersIds.size() + 1 < _maxplayers) {
    _playersIds.push_back(id);
    return true;
  }
  else {
    return false;
  }
}
