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

   _updateMap[communication::Packet::Type::POSITION] =
      std::bind(&GraphicGameState::updateWithPosition, this, _1);
   _updateMap[communication::Packet::Type::DEATH] =
      std::bind(&GraphicGameState::updateWithDeath, this, _1);
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
void  GraphicGameState::updateWithPosition(const communication::Packet& packet)
{
  const uint32_t id = packet.getId();

  if (id >= 0 && id < _players.size()) {
    _players[id]->unpack(packet.getSequence(), packet.getContent());
  }
}

// client
void  GraphicGameState::updateWithDeath(const communication::Packet& packet)
{
   //assert(false);
}

void  GraphicGameState::simulate(const Input::Data& input)
{
  const int playerId = input.getId();

  if (playerId >= 0 && playerId < _players.size()) {
    _players[playerId]->setDirection(input.getVector() / 200);
    _players[playerId]->move();
  }
}
