/*
 * -----------------------------------------------------------------------------
 * "THE BEER-WARE LICENSE" (Revision 42):
 * <duplom_t@epitech.eu> wrote this file. As long as you retain this notice you
 * can do whatever you want with this stuff. If we meet some day, and you think
 * this stuff is worth it, you can buy me a beer in return Thomas Duplomb
 * -----------------------------------------------------------------------------
 */

#ifndef _ITCPSOCKET_H__
#define _ITCPSOCKET_H__

#include <memory>
#include "IAddr.hh"

namespace network {
    namespace sockets {
        class ITcpSocket {
            public:
                virtual ~ITcpSocket() {}

                virtual void listen(int queueLenght) = 0;

                virtual std::shared_ptr<ITcpSocket> accept(IAddr & pair) = 0;

                virtual void connect(const IAddr & pair) = 0;

                virtual void bind(const IAddr & addr) = 0;

                virtual int recv(char * packet, int maxPacketSize) = 0;

                virtual int send(const char * packet, int packetSize) = 0;
        };
    }
}

#endif /* !_ITCPSOCKET_H__ */
