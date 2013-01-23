#include <iostream>
#include <algorithm>
#include "ReliablePacket.hh"

namespace communication {

ReliablePacket::ReliablePacket(const std::vector<TBSystem::network::Addr>& addr,
                               const Packet& packet)
  : _packet(packet)
{
  for (auto& a : addr) {
    _clientsStatus.emplace_back(std::make_pair(a, false));
  }
  //Would be nice to be able to compare Addr..
  //Four packets for now to keep track of the different addr based on sequence
  _packets.emplace_back(_packet);
  _packets.emplace_back(Packet(_packet.getType(), _packet.getId(), _packet.getResourceId(),
                              _packet.getData(), _packet.getDataSize()));
  _packets.emplace_back(Packet(_packet.getType(), _packet.getId(), _packet.getResourceId(),
                              _packet.getData(), _packet.getDataSize()));
  _packets.emplace_back(Packet(_packet.getType(), _packet.getId(), _packet.getResourceId(),
                              _packet.getData(), _packet.getDataSize()));
}

ReliablePacket::~ReliablePacket()
{
}

ReliablePacket::ReliablePacket(const ReliablePacket& other)
  : _clientsStatus(other._clientsStatus)
  , _packet(other._packet)
{
}

ReliablePacket::ReliablePacket(ReliablePacket&& other)
  : _packet(other._packet)
{
  swap(*this, other);
}

ReliablePacket& ReliablePacket::operator=(ReliablePacket other)
{
  swap(*this, other);
  return *this;
}

void  swap(ReliablePacket& lhs, ReliablePacket& rhs)
{
  std::swap(lhs._clientsStatus, rhs._clientsStatus);
  std::swap(lhs._packet, rhs._packet);
}

bool  ReliablePacket::checkAnswer(const TBSystem::network::Addr& clientAddr,
                                  const Packet& packet)
{
  auto clientIt = _clientsStatus.begin();
  auto packetIt = _packets.begin();
  while (clientIt != _clientsStatus.end() &&
         packetIt != _packets.end())
  {
    //if its a packet I know and its an answer..
    if (packet.getSequence() == packetIt->getSequence() &&
        packet.getType() == communication::Packet::Type::ACK)
    {
      //std::cout << "SAFE id=" << packet.getSequence() << std::endl;
      clientIt->second = true;//it arrived safely
      return true;
    }
    ++clientIt;
    ++packetIt;
  }
  return false;
}

void  ReliablePacket::tryAgain(TBSystem::network::sockets::Udp& socket)
{
  auto clientIt = _clientsStatus.begin();
  auto packetIt = _packets.begin();
  while (clientIt != _clientsStatus.end() &&
         packetIt != _packets.end())
  {
    if (clientIt->second == false)//if the user did not receive my packet
    {
      //std::cout << "Need to try again with this one :(" << std::endl;
      //send it again
      socket.send(packetIt->getData(), packetIt->getDataSize(), clientIt->first);
    }
    ++clientIt;
    ++packetIt;
  }
}

bool  ReliablePacket::allSent(void) const
{
  for (auto& client : _clientsStatus)
  {
    if (client.second == false)//at least one did not receive it
      return false;
  }
  //std::cout << "All sent!" << std::endl;
  return true;
}

}
