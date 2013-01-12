/*
 * -----------------------------------------------------------------------------
 * "THE BEER-WARE LICENSE" (Revision 42):
 * <duplom_t@epitech.eu> wrote this file. As long as you retain this notice you
 * can do whatever you want with this stuff. If we meet some day, and you think
 * this stuff is worth it, you can buy me a beer in return. Thomas Duplomb
 * -----------------------------------------------------------------------------
 */

#ifndef _GAMESTATE_H__
#define _GAMESTATE_H__

#include <vector>
#include <map>
#include <functional>
#include <memory>
#include "units/Unit.hh"
#include "units/Packet.hh"

class GameState {
public:
  GameState(const std::vector<std::shared_ptr<Unit>>& v);
  virtual ~GameState();

  void  update(const network_packet::Packet & packet);
  void  update(const std::vector<network_packet::Packet>& v);

public:
  // server
  void  updateWithInput    (uint32_t id, const uint8_t* content);

public:
  void  move();

public:
  const std::vector<std::shared_ptr<Unit>>& getPlayers() const;

protected:
  typedef std::function<void (uint32_t, const uint8_t *)> UpdateFunction;
  std::vector<std::shared_ptr<Unit>>  _players;
  std::map<network_packet::Packet::Type, UpdateFunction> _updateMap;
};

#endif /* !_GAMESTATE_H__ */
