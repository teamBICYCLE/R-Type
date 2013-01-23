/*
 * -----------------------------------------------------------------------------
 * "THE BEER-WARE LICENSE" (Revision 42):
 * <duplom_t@epitech.eu> wrote this file. As long as you retain this notice you
 * can do whatever you want with this stuff. If we meet some day, and you think
 * this stuff is worth it, you can buy me a beer in return. Thomas Duplomb
 * -----------------------------------------------------------------------------
 */

#ifndef _NETWORKHANDLER_H__
#define _NETWORKHANDLER_H__

#include <vector>
#include <system/network/Udp.hh>
#include <system/network/Addr.hh>
#include "network/ReliablePacket.hh"
#include "gamestate/ServerGameState.hh"

namespace communication {

class NetworkHandler {
public:
   NetworkHandler(const std::string& port);
   ~NetworkHandler();

public:
   void   broadcast(const ServerGameState& g);
   void   sendEntity(Unit* entity);
   std::vector<communication::Packet> getIncomingPackets();

public:
   void setClients(const std::vector<TBSystem::network::Addr>& c);
   bool allReliablePacketsSent(void) const;
   void trySendAll(void);

private:
   void sendToAll(uint8_t *packet, int packetSize);
   void addReliablePacket(const uint8_t *packet, int packetSize);

private:
   TBSystem::network::sockets::Udp      _socket;
   std::vector<TBSystem::network::Addr> _outAddr;
   std::list<ReliablePacket>            _reliablePackets;
};

}

#endif /* !_NETWORKHANDLER_H__ */
