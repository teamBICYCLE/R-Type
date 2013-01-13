/*
 * -----------------------------------------------------------------------------
 * "THE BEER-WARE LICENSE" (Revision 42):
 * <duplom_t@epitech.eu> wrote this file. As long as you retain this notice you
 * can do whatever you want with this stuff. If we meet some day, and you think
 * this stuff is worth it, you can buy me a beer in return. Thomas Duplomb
 * -----------------------------------------------------------------------------
 */

#include <system/log/Log.hh>
#include "NetworkHandler.hh"

using namespace TBSystem;

NetworkHandler::NetworkHandler()
{
  network::Addr pair(network::SI_ADDR_ANY, "4242", "UDP");

  _socket.setBlocking(false);
  _socket.bind(pair);
  _outAddr.push_back(network::Addr("127.0.0.1", "4244", "UDP"));
}

NetworkHandler::~NetworkHandler()
{
}

std::vector<network_packet::Packet> NetworkHandler::getIncomingPackets()
{
  network::Addr clt;
  std::vector<network_packet::Packet> inputs;
  uint8_t buf[256];
  int ret;

  while ((ret = _socket.recv(buf, sizeof(buf), clt))
         != -1) {
    network_packet::Packet p(buf, ret);

    // TODO: verifier que clt est dans la liste des clients
    inputs.push_back(p);
  }
  return inputs;
}

void  NetworkHandler::broadcast(const GameState& g)
{
      for (auto& p : g.getPlayers()) {
         uint8_t  buf[network_packet::Packet::MAX_PACKET_SIZE];
         int      packetSize;

         packetSize = p->pack(buf, sizeof(buf));
         for (auto& addr : _outAddr) {
            _socket.send(buf, packetSize, addr);
         }
   }
}

void NetworkHandler::setClients(const std::vector<network::Addr>& c)
{
  _outAddr = c;
}
