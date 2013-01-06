/*
 * -----------------------------------------------------------------------------
 * "THE BEER-WARE LICENSE" (Revision 42):
 * <duplom_t@epitech.eu> wrote this file. As long as you retain this notice you
 * can do whatever you want with this stuff. If we meet some day, and you think
 * this stuff is worth it, you can buy me a beer in return Thomas Duplomb
 * -----------------------------------------------------------------------------
 */

#include "Tcp.hh"
#include <stdexcept>
#include "system/log/Log.hh"
#ifdef __gnu_linux__
#include <errno.h>
#include <unistd.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/ip.h>


// Test purpuse
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>


#elif _WIN32

#endif

namespace TBSystem {
namespace network {
    namespace sockets {
        Tcp::Tcp()
        {
            errno = 0;
            _socket = socket(AF_INET, SOCK_STREAM, 0);
            if (_socket == -1) throw std::runtime_error(strerror(errno));
        }

        Tcp::Tcp(int socketDescriptor)
        : _socket(socketDescriptor)
        {
        }

        Tcp::~Tcp()
        {
            close(_socket);
        }

        void Tcp::listen(int queueLenght)
        {
            errno = 0;
            if (::listen(_socket, queueLenght) != 0) {
                throw std::runtime_error(strerror(errno));
            }
        }

        void Tcp::bind(const IAddr & addr)
        {
            for (auto hint : addr.infos()) {
               if (::bind(_socket, static_cast<const sockaddr *>(hint->get()), hint->size())
                   != -1)
                   return;
            }
            throw std::runtime_error("No valid host for " + std::get<0>(addr.get()) + ":" + std::get<1>(addr.get()));
        }

        std::shared_ptr<ITcpSocket> Tcp::accept(IAddr & pair)
        {
            int fd;

            errno = 0;
            fd = ::accept(_socket, nullptr, nullptr);
            if (fd == -1) throw std::runtime_error(strerror(errno));
            return std::shared_ptr<ITcpSocket>(new Tcp(fd));
        }

        void Tcp::connect(const IAddr & pair)
        {
            for (auto hint : pair.infos()) {
                sockaddr_in * _hint = static_cast<sockaddr_in*>(hint->get());
                char addrstr[127];

                memset(addrstr, 0, sizeof(addrstr));
                inet_ntop(_hint->sin_family,
                          static_cast<const void*>(&_hint->sin_addr),
                          addrstr, sizeof(addrstr));
                log::info << "Trying to connect to "
                    << addrstr << ":" << ntohs(_hint->sin_port) << "... ";

                if (::connect(_socket, static_cast<const sockaddr *>(hint->get()), hint->size())
                    != -1) {
                    log::info << "SUCCESS" << log::endl;
                    return;
                }
                log::info << "FAIL" << log::endl;
            }
            throw std::runtime_error("No valid host found for " +
                                     std::get<0>(pair.get())
                                     + ":" + std::get<1>(pair.get()));
       }

        int Tcp::recv(char * packet, int maxPacketSize)
        {
            int ret;

            errno = 0;
            ret = ::recv(_socket, packet, maxPacketSize, 0);
            if (ret == -1) throw std::runtime_error(strerror(errno));
            return ret;
        }

        int Tcp::send(const char * packet, int packetSize)
        {
            int ret;

            ret = ::send(_socket, packet, packetSize, 0);
            if (ret == -1) throw std::runtime_error(strerror(errno));
            return ret;
        }
    }
}
}
