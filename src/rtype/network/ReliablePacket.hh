#ifndef   __RELIABLEPACKET_HH__
# define  __RELIABLEPACKET_HH__

# include <map>
# include <system/network/Udp.hh>
# include <system/network/Addr.hh>
# include "network/Packet.hh"

namespace communication {

class ReliablePacket
{
public:
  ReliablePacket(const std::vector<TBSystem::network::Addr>& addr,
                 const Packet& packet);
  ~ReliablePacket();

public:
  ReliablePacket(const ReliablePacket& other);
  ReliablePacket(ReliablePacket&& other);
  ReliablePacket& operator=(ReliablePacket other);
  friend void swap(ReliablePacket& lhs, ReliablePacket& rhs);

public:
  bool  checkAnswer(const TBSystem::network::Addr& clientAddr, const Packet& packet);
  void  tryAgain(TBSystem::network::sockets::Udp& socket);

public:
  bool  allSent(void) const;

private:
  //class to compare to Addr based on their ip, port and protocol.
  //Needed to store Addr as a key in the _clientsStatus map
  struct AddrComparer
  {
    bool  operator()(const TBSystem::network::Addr& addr1,
                     const TBSystem::network::Addr& addr2)
    {
      std::tuple<std::string, std::string, std::string> infos1 = addr1.get();
      std::tuple<std::string, std::string, std::string> infos2 = addr2.get();

      return infos1 < infos2;
    }
  };

  //std::map<TBSystem::network::Addr, bool, AddrComparer> _clientsStatus;
  std::vector<std::pair<TBSystem::network::Addr, bool>>   _clientsStatus;
  std::vector<Packet> _packets;
  Packet  _packet;
};

}

#endif /* !__RELIABLE_PACKET_HH__ */
