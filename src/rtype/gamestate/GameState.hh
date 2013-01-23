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
#include "units/Player.hh"
#include "network/Packet.hh"
#include "pool/UnitPool.hh"

class GameState {
public:
  GameState(const std::shared_ptr<UnitPool> &p);
  virtual ~GameState();

  void  update(const communication::Packet& packet);
  void  update(const std::vector<communication::Packet>& v);
  bool    running(void) const;

protected:
  Vector2D  convertToSpeed(const Vector2D& direction) const;

public:
  static const int WINDOW_WIDTH;
  static const int WINDOW_HEIGHT;

protected:
  typedef std::function<void (const communication::Packet&)> UpdateFunction;
  std::map<communication::Packet::Type, UpdateFunction> _updateMap;
  const float PLAYER_SPEED;
  std::shared_ptr<UnitPool> _pool;
  bool  _running;
};

#endif /* !_GAMESTATE_H__ */
