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

const float GameState::WINDOW_WIDTH = 800.f;
const float GameState::WINDOW_HEIGHT = 800.f;

GameState::GameState(const std::vector<std::shared_ptr<Player>>& v)
  : _lastPacketSequence(0) 
  , _players(v)
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

void  GameState::setPlayerDirection(int id, const Vector2D& dir)
{
  if (id >= 0 && id < _players.size()) {
    _players[id]->setDir(dir / GameState::PLAYER_SPEED);
  }
}

void  GameState::move()
{
   for (auto& p : _players) {
     Vector2D  savedPos = p->getPos();

     p->move();
     for (auto& other : _players)
     {
       if (other->getId() != p->getId() &&
           other->collideWith(*p) == true)
       {
         p->setPos(savedPos);
         std::cout << "COLLIDED" << std::endl;
         break;
       }
     }
   }
}

const std::vector<std::shared_ptr<Player>>& GameState::getPlayers() const
{
  return _players;
}
