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
            _reliablePackets.erase(it);//then discard it
          ++it;
        }
      }
    //}
  }
  return inputs;
}

void  NetworkHandler::broadcast(const ServerGameState& g)
{
  for (auto& p : g.getPlayers()) {
    if (p->isDead() == false ||
        p->wereOthersNotifiedOfDeath() == false)
    {
      uint8_t  buf[communication::Packet::MAX_PACKET_SIZE];
      int      packetSize;

      packetSize = p->pack(buf, sizeof(buf));
      if (p->isDead() == false)
      {
        for (auto& addr : _outAddr) {//player is not dead so send its positions
          _socket.send(buf, packetSize, addr);
        }
      }
      else
      {
        Packet tmp(buf, packetSize);

        std::cout << "RELIABLE" << std::endl;
        _reliablePackets.emplace_back(_outAddr, tmp);//player is dead, send this to everyone
        p->setOthersNotifiedOfDeath(true);//others are planned to be notified,
                                          //no need to handle the dead player anymore
      }
    }
  }
  //SHIT -v
  for (auto& monster : g.getEnemies()) {
    uint8_t  buf[communication::Packet::MAX_PACKET_SIZE];
    int      packetSize;

    packetSize = monster->pack(buf, sizeof(buf));
    for (auto& addr : _outAddr) {//player is not dead so send its positions
      _socket.send(buf, packetSize, addr);
    }
  }
  for (auto& packet : _reliablePackets)
    packet.tryAgain(_socket);
}

void NetworkHandler::setClients(const std::vector<network::Addr>& c)
{
  _outAddr = c;
}

}
