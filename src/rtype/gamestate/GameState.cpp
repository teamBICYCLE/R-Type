/*
 * -----------------------------------------------------------------------------
 * "THE BEER-WARE LICENSE" (Revision 42):
 * <duplom_t@epitech.eu> wrote this file. As long as you retain this notice you
 * can do whatever you want with this stuff. If we meet some day, and you think
 * this stuff is worth it, you can buy me a beer in return. Thomas Duplomb
 * -----------------------------------------------------------------------------
 */

#include "GameState.hh"
#include "input/Data.hh"

const int GameState::WINDOW_WIDTH = 1200;
const int GameState::WINDOW_HEIGHT = 800;

GameState::GameState(const std::shared_ptr<UnitPool> &p)
  : PLAYER_SPEED(200.f), _pool(p)
{
}

GameState::~GameState()
{
}

void  GameState::update(const communication::Packet& packet)
{
  auto it = _updateMap.find(packet.getType());

  if (it != _updateMap.end()) it->second(packet);
}

void  GameState::update(const std::vector<communication::Packet>& v)
{
   for (auto& p : v)
   {
      this->update(p);
   }
}

Vector2D  GameState::convertToSpeed(const Vector2D& direction) const
{
  return direction / GameState::PLAYER_SPEED;
}
