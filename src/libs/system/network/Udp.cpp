/*
 * -----------------------------------------------------------------------------
 * "THE BEER-WARE LICENSE" (Revision 42):
 * <duplom_t@epitech.eu> wrote this file. As long as you retain this notice you
 * can do whatever you want with this stuff. If we meet some day, and you think
 * this stuff is worth it, you can buy me a beer in return Thomas Duplomb
 * -----------------------------------------------------------------------------
 */

#include "Udp.hh"

namespace TBSystem {
namespace network {
    namespace sockets {
        Udp::Udp()
        {}

        Udp::~Udp() {}

        void Udp::bind(const IAddr & pair)
        {
            for (auto hint : addr.infos()) {
               if (::bind(_socket, static_cast<const sockaddr *>(hint->get()), hint->size())
                   != -1)
                   return;
            }
            throw std::runtime_error("No valid host for " + std::get<0>(addr.get()) + ":" + std::get<1>(addr.get()));
        }

        int Udp::send(const char * packet, int packetSize, const IAddr & pair)
        {
            int ret;

            //ret = ::sendto(_socket, packet, packetSize, 0);
            if (ret == -1) throw std::runtime_error(strerror(errno));
            return ret;
        }

        int Udp::recv(char * packet, int maxPacketSize, IAddr & pair)
        {
            int ret;

            errno = 0;
            //ret = ::recvfrom(_socket, packet, maxPacketSize, 0, addr, sizeof(addr));
            if (ret == -1) throw std::runtime_error(strerror(errno));
            return ret;
        }
    }
}
}
