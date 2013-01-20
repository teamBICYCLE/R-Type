/*
 * -----------------------------------------------------------------------------
 * "THE BEER-WARE LICENSE" (Revision 42):
 * <duplom_t@epitech.eu> wrote this file. As long as you retain this notice you
 * can do whatever you want with this stuff. If we meet some day, and you think
 * this stuff is worth it, you can buy me a beer in return Thomas Duplomb
 * -----------------------------------------------------------------------------
 */

#ifndef _UDP_H__
#define _UDP_H__

#include <cstdint>
#include "IUdpSocket.hh"
#include "IAddr.hh"

namespace TBSystem {
namespace network {
    namespace sockets {
        class Udp : public IUdpSocket {
            public:
                Udp();

                virtual ~Udp();

                virtual void bind(const IAddr & pair);

                virtual int send(const uint8_t * packet, int packetSize,
                                 const IAddr & pair);

                virtual int recv(uint8_t * packet, int maxPacketSize,
                                 IAddr & pair);

            public:
                virtual void setBlocking(bool v);

            private:
                int _socket;
        };
    }
}
}

#endif /* !_UDP_H__ */
