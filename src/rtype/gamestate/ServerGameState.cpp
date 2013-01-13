/*
 * -----------------------------------------------------------------------------
 * "THE BEER-WARE LICENSE" (Revision 42):
 * <duplom_t@epitech.eu> wrote this file. As long as you retain this notice you
 * can do whatever you want with this stuff. If we meet some day, and you think
 * this stuff is worth it, you can buy me a beer in return. Thomas Duplomb
 * -----------------------------------------------------------------------------
 */

#include "input/Data.hh"
#include "ServerGameState.hh"

ServerGameState::ServerGameState(const std::vector<std::shared_ptr<Unit>>& v)
  : GameState(v)
{
   using namespace std::placeholders;

   _updateMap[communication::Packet::Type::INPUT] =
      std::bind(&ServerGameState::updateWithInput, this, _1, _2);
}

ServerGameState::~ServerGameState()
{
}

void  ServerGameState::updateWithInput(uint32_t id, const uint8_t* content)
{
   if (id >= 0 && id <= _players.size()) {
      Input::Data d;

      d.unpack(content);
      _players[id]->setDirection(d.getVector() / 500);
   }
}
