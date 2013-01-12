/*
 * -----------------------------------------------------------------------------
 * "THE BEER-WARE LICENSE" (Revision 42):
 * <duplom_t@epitech.eu> wrote this file. As long as you retain this notice you
 * can do whatever you want with this stuff. If we meet some day, and you think
 * this stuff is worth it, you can buy me a beer in return. Thomas Duplomb
 * -----------------------------------------------------------------------------
 */

#include <system/log/Log.hh>
#include "GraphicGameState.hh"
#include "units/graphics/GUnit.hh"

using namespace TBSystem;

GraphicGameState::GraphicGameState(const std::vector<std::shared_ptr<Unit>>& v)
  : GameState(v)
{
  using namespace std::placeholders;

   _updateMap[network_packet::Packet::Type::POSITION] =
      std::bind(&GraphicGameState::updateWithPosition, this, _1, _2);
   _updateMap[network_packet::Packet::Type::DEATH] =
      std::bind(&GraphicGameState::updateWithDeath, this, _1, _2);
}

GraphicGameState::~GraphicGameState()
{
}

void GraphicGameState::draw(sf::RenderTarget &target, sf::RenderStates states) const {
  for (auto& p : _players) {
    target.draw(static_cast<GUnit&>(*p));
  }
}

// client
void  GraphicGameState::updateWithPosition(uint32_t id, const uint8_t* content)
{
   if (id >= 0 && id < _players.size()) {
      _players[id]->unpack(content);
   }
}

// client
void  GraphicGameState::updateWithDeath(uint32_t id, const uint8_t* content)
{
   //assert(false);
}


