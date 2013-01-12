/*
 * -----------------------------------------------------------------------------
 * "THE BEER-WARE LICENSE" (Revision 42):
 * <duplom_t@epitech.eu> wrote this file. As long as you retain this notice you
 * can do whatever you want with this stuff. If we meet some day, and you think
 * this stuff is worth it, you can buy me a beer in return Thomas Duplomb
 * -----------------------------------------------------------------------------
 */

#ifndef _IUDPSOCKET_H__
#define _IUDPSOCKET_H__

#include "IAddr.hh"

namespace TBSystem {
namespace network {
    namespace sockets {
        class IUdpSocket {
            public:
                virtual ~IUdpSocket() {}

                virtual void bind(const IAddr & pair) = 0;

                virtual int send(const uint8_t * packet, int packetSize,
                                 const IAddr & pair) = 0;

                virtual int recv(uint8_t * packet, int maxPacketSize,
                                 IAddr & pair) = 0;

                virtual void setBlocking(bool v) = 0;
        };
    }
}
}

#endif /* !_IUDPSOCKET_H__ */
