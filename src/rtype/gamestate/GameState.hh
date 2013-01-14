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
#include "network/Packet.hh"

class GameState {
public:
  GameState(const std::vector<std::shared_ptr<Unit>>& v);
  virtual ~GameState();

  void  update(const communication::Packet & packet);
  void  update(const std::vector<communication::Packet>& v);

public:
  void  move();

protected:
  void  setPlayerDirection(int id, const Vector2D& dir);

public:
  const std::vector<std::shared_ptr<Unit>>& getPlayers() const;

protected:
  const float PLAYER_SPEED = 200.f;
  typedef std::function<void (const communication::Packet&)> UpdateFunction;
  uint32_t  _lastPacketSequence;
  std::vector<std::shared_ptr<Unit>>  _players;
  std::map<communication::Packet::Type, UpdateFunction> _updateMap;
};

#endif /* !_GAMESTATE_H__ */
