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

#define linux_LOL__
#ifdef linux_LOL__
#include <errno.h>
#include <unistd.h>
#include <string.h>
#include <sys/socket.h>
#elif WIN32_MDR__

#endif

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

        std::shared_ptr<ITcpSocket> Tcp::accept(IAddr & pair)
        {
            int fd;

            errno = 0;
            fd = ::accept(_socket, static_cast<sockaddr *>(pair.raw()), nullptr); // TODO: change nullptr to fill Addr
            if (fd == -1) throw std::runtime_error(strerror(errno));
            return std::shared_ptr<ITcpSocket>(new Tcp(fd));
        }

        void Tcp::connect(const IAddr & pair)
        {
            errno = 0;
            if (::connect(_socket, static_cast<const sockaddr *>(pair.raw()), 0) == -1) {
                throw std::runtime_error(strerror(errno));
            }
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
