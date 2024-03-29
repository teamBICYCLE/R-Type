/*
 * -----------------------------------------------------------------------------
 * "THE BEER-WARE LICENSE" (Revision 42):
 * <duplom_t@epitech.eu> wrote this file. As long as you retain this notice you
 * can do whatever you want with this stuff. If we meet some day, and you think
 * this stuff is worth it, you can buy me a beer in return. Thomas Duplomb
 * -----------------------------------------------------------------------------
 */

#include <algorithm>
#include <system/log/Log.hh>
#include "NetworkHandler.hh"

using namespace TBSystem;

namespace communication {

NetworkHandler::NetworkHandler(const std::string& port)
{
  network::Addr pair(network::SI_ADDR_ANY, port, "UDP");

  _socket.setBlocking(false);
  _socket.bind(pair);
}

NetworkHandler::~NetworkHandler()
{
}

std::vector<communication::Packet> NetworkHandler::getIncomingPackets()
{
  network::Addr clt;
  std::vector<communication::Packet> inputs;
  uint8_t buf[256];
  int ret;

  while ((ret = _socket.recv(buf, sizeof(buf), clt))
         != -1) {
    communication::Packet p(buf, ret);

    //if (std::find(_outAddr.begin(), _outAddr.end(), clt) != _outAddr.end())
    //{
      if (p.getType() == communication::Packet::Type::INPUT)
        inputs.push_back(p);
      else if (p.getType() == communication::Packet::Type::ACK)
      {
        auto it = _reliablePackets.begin();
        while (it != _reliablePackets.end())//check all reliable packets..
        {
          it->checkAnswer(clt, p);//if the received packet is an answer to them..
          if (it->allSent() == true)//and every client received their packet..
            it = _reliablePackets.erase(it);//then discard it
          else
            ++it;
        }
      }
    //}
  }
  return inputs;
}

void NetworkHandler::sendToAll(uint8_t *packet, int packetSize)
{
  for (auto& addr : _outAddr) {
    //if (addr.isDisconnected() == false)
      _socket.send(packet, packetSize, addr);
  }
}

void NetworkHandler::addReliablePacket(const uint8_t *packet, int packetSize)
{
  Packet tmp(packet, packetSize);

  _reliablePackets.emplace_back(_outAddr, tmp);//unit is dead, send this to everyone
}

void  NetworkHandler::broadcast(const ServerGameState& g)
{
  if (g.running() == false) {
    Packet  endGamePacket(communication::Packet::Type::END_GAME, 0, 0,
                          nullptr, 0);

    endGamePacket.setReliable(true);
    addReliablePacket(endGamePacket.getData(), endGamePacket.getDataSize());
  }
  else {
    //send player update to other players
    for (auto& p : g.getPlayers()) {
      //if (p->isDisconnected() == true) {
      //  Packet  disconnectedPacket(communication::Packet::Type::CLIENT_DISCONNECTED,
      //                             p->getId(), p->getResourceId(), nullptr, 0);

      //  disconnectedPacket.setReliable(true);
      //  _outAddr[p->getId()].setDisconnected(true);
      //  std::cout << "Client #" << p->getId() << " is probably disconnected" << std::endl;
      //  addReliablePacket(disconnectedPacket.getData(), disconnectedPacket.getDataSize());
      //}
      //else {
      //  _outAddr[p->getId()].setDisconnected(false);
        sendEntity(p);
      //}
    }

    //send monsters update
    for (auto& monster : g.getEnemies()) {
      sendEntity(monster);
    }

    //send monster missiles update
    for (auto& monsterMissile : g.getMonsterMissiles()) {
      sendEntity(monsterMissile);
    }

    //_disconnected = b;
    //send player missiles update
    for (auto& playerMissile : g.getPlayerMissiles()) {
      sendEntity(playerMissile);
    }
  }

  trySendAll();
}

void  NetworkHandler::trySendAll(void)
{
  //retry sending every non-ack reliable packets
  for (auto& packet : _reliablePackets) {
    packet.tryAgain(_socket);
  }
}

void  NetworkHandler::sendEntity(Unit *entity)
{
  uint8_t  *buf = new uint8_t[communication::Packet::MAX_PACKET_SIZE];
  int       bufSize = communication::Packet::MAX_PACKET_SIZE;
  int       packetSize;

  if (entity->isDead() == false ||
      entity->wereOthersNotifiedOfDeath() == false)
  {
    packetSize = entity->pack(buf, bufSize);
    if (entity->isDead() == false) {
      //entity is not dead, send position
      sendToAll(buf, packetSize);
    }
    else {
      //entity is dead, notify others
      addReliablePacket(buf, packetSize);
      //others are planned to be notified, no need to handle the dead unit anymore
      entity->setOthersNotifiedOfDeath(true);
    }
  }
  delete [] buf;
}

void NetworkHandler::setClients(const std::vector<network::Addr>& c)
{
  _outAddr = c;
}

bool NetworkHandler::allReliablePacketsSent(void) const
{
  return (_reliablePackets.size() == 0);
}

}
