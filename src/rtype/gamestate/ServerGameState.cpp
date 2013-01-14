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
      std::bind(&ServerGameState::updateWithInput, this, _1);
}

ServerGameState::~ServerGameState()
{
}

void  ServerGameState::updateWithInput(const communication::Packet& packet)
{
  const uint32_t  id = packet.getId();

  if (id >= 0 && id <= _players.size()) {
    Input::Data d;
    std::shared_ptr<Unit>& player = _players[id];

    d.unpack(packet.getSequence(), packet.getContent());
    if (player->getLastPacketSequence() < packet.getSequence())
    {
      player->setLastPacketSequence(packet.getSequence());
      GameState::setPlayerDirection(id, d.getVector());
    }
    else
      std::cout << "=======================================Dropped" << std::endl;
  }
}
