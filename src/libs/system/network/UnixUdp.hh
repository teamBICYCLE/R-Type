/*
 * -----------------------------------------------------------------------------
 * "THE BEER-WARE LICENSE" (Revision 42):
 * <duplom_t@epitech.eu> wrote this file. As long as you retain this notice you
 * can do whatever you want with this stuff. If we meet some day, and you think
 * this stuff is worth it, you can buy me a beer in return Thomas Duplomb
 * -----------------------------------------------------------------------------
 */

#ifndef _UNIXUDP_H__
#define _UNIXUDP_H__

#include "IUdpSocket.hh"
#include "IAddr.hh"

namespace TBSystem {
namespace network {
    namespace sockets {
        class UnixUdp : IUdpSocket {
            public:
                UnixUdp();

                virtual ~UnixUdp();

                virtual void bind(const IAddr & pair);

                virtual int send(const char * packet, int packetSize,
                                 const IAddr & pair);

                virtual int recv(char * packet, int maxPacketSize,
                                 IAddr & pair);
            private:
                int _socket;
        };
    }
}
}

#endif /* !_UNIXUDP_H__ */
