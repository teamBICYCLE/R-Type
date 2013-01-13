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
#include "GameState.hh"

class NetworkHandler {
public:
   NetworkHandler();
   ~NetworkHandler();

public:
   void  broadcast(const GameState& g);
   std::vector<network_packet::Packet> getIncomingPackets();

public:
   void setClients(const std::vector<TBSystem::network::Addr>& c);

private:
   TBSystem::network::sockets::Udp      _socket;
   std::vector<TBSystem::network::Addr> _outAddr;
};

#endif /* !_NETWORKHANDLER_H__ */
