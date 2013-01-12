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

GameState::GameState(const std::vector<std::shared_ptr<Unit>>& v)
   : _players(v)
{
   using namespace std::placeholders;

   _updateMap[network_packet::Packet::Type::INPUT] =
      std::bind(&GameState::updateWithInput, this, _1, _2);
}

GameState::~GameState()
{
}

void  GameState::update(const network_packet::Packet& packet)
{
   auto it = _updateMap.find(packet.getType());

   if (it != _updateMap.end()) it->second(packet.getId(), packet.getContent());
}

void  GameState::update(const std::vector<network_packet::Packet>& v)
{
   for (auto& p : v)
   {
      this->update(p);
   }
}

// server
void  GameState::updateWithInput(uint32_t id, const uint8_t* content)
{
   if (id >= 0 && id <= _players.size()) {
      Input::Data d;

      d.unpack(content);
      _players[id]->setDirection(d.getVector() / 100);
   }
}

void  GameState::move()
{
   for (auto& p : _players) {
      p->move();
   }
}

const std::vector<std::shared_ptr<Unit>>& GameState::getPlayers() const
{
  return _players;
}
