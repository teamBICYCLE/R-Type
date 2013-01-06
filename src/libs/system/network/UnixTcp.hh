/*
 * -----------------------------------------------------------------------------
 * "THE BEER-WARE LICENSE" (Revision 42):
 * <duplom_t@epitech.eu> wrote this file. As long as you retain this notice you
 * can do whatever you want with this stuff. If we meet some day, and you think
 * this stuff is worth it, you can buy me a beer in return Thomas Duplomb
 * -----------------------------------------------------------------------------
 */

#ifndef _UNIXTCP_H__
#define _UNIXTCP_H__

#include "ITcpSocket.hh"
#include "IAddr.hh"
# include <sys/socket.h>

namespace TBSystem {
namespace network {
    namespace sockets {
        class UnixTcp : public ITcpSocket {
            public:
                UnixTcp();

                explicit UnixTcp(int socketDescriptor);

                virtual ~UnixTcp();

                virtual void listen(int queueLenght);

                virtual void bind(const IAddr & addr);

                virtual std::shared_ptr<ITcpSocket> accept(IAddr & pair);

                virtual void connect(const IAddr & pair);

                virtual int recv(char * packet, int maxPacketSize);

                virtual int send(const char * packet, int packetSize);

            private:
                int _socket;
        };
    }
}
}

#endif /* !_UNIXTCP_H__ */
