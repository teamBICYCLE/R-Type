/*
 * -----------------------------------------------------------------------------
 * "THE BEER-WARE LICENSE" (Revision 42):
 * <duplom_t@epitech.eu> wrote this file. As long as you retain this notice you
 * can do whatever you want with this stuff. If we meet some day, and you think
 * this stuff is worth it, you can buy me a beer in return Thomas Duplomb
 * -----------------------------------------------------------------------------
 */

#include "UnixUdp.hh"
#include <sys/socket.h>
#include <string.h>
#include <unistd.h>
#include <netinet/ip.h>
#include <stdexcept>

namespace TBSystem {
namespace network {
    namespace sockets {
        UnixUdp::UnixUdp()
        {
            errno = 0;
            _socket = socket(AF_INET, SOCK_DGRAM, 0);
            if (_socket == -1) throw std::runtime_error(strerror(errno));
        }

        UnixUdp::~UnixUdp() {
            close(_socket);
        }

        void UnixUdp::bind(const IAddr & pair)
        {
            for (auto hint : pair.infos()) {
               if (::bind(_socket, static_cast<const sockaddr *>(hint->get()),
                          hint->size())
                   != -1) {
                   pair.setValid(hint->get());
                   return;
               }
            }
            throw std::runtime_error("No valid host for "
                                     + std::get<0>(pair.get()) + ":"
                                     + std::get<1>(pair.get()));
        }

        int UnixUdp::send(const char * packet, int packetSize, const IAddr & pair)
        {
            int ret;

            if (pair.hasValidAddr()) {
                ret = ::sendto(_socket, packet, packetSize, 0,
                               static_cast<const sockaddr *>(pair.getValid()),
                               pair.validSize());
            }
            else {
                for (auto hint : pair.infos()) {
                    if (::sendto(_socket, packet, packetSize, 0,
                                 static_cast<const sockaddr *>(hint->get()),
                                 hint->size())
                        != -1) {
                        pair.setValid(hint->get());
                        break;
                    }
                }
            }
            if (ret == -1) throw std::runtime_error(strerror(errno));
            return ret;
        }

        int UnixUdp::recv(char * packet, int maxPacketSize, IAddr & pair)
        {
            int ret;
            sockaddr_in buf;
            unsigned int len = 0;

            memset(&buf, 0, sizeof(buf));
            errno = 0;
            ret = ::recvfrom(_socket, packet, maxPacketSize, 0,
                             reinterpret_cast<sockaddr*>(&buf), &len);
            pair.setValid(static_cast<void *>(&buf));
            if (ret == -1) throw std::runtime_error(strerror(errno));
            return ret;
        }
    }
}
}
