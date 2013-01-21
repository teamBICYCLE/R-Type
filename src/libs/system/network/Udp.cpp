/*
 * -----------------------------------------------------------------------------
 * "THE BEER-WARE LICENSE" (Revision 42):
 * <duplom_t@epitech.eu> wrote this file. As long as you retain this notice you
 * can do whatever you want with this stuff. If we meet some day, and you think
 * this stuff is worth it, you can buy me a beer in return Thomas Duplomb
 * -----------------------------------------------------------------------------
 */

#include "Udp.hh"
#include <string.h>
#include <stdexcept>
#include <system/log/Log.hh>
#include "socketInit.hh"
#ifdef __gnu_linux__
#include <unistd.h>
#include <netinet/ip.h>
#include <sys/socket.h>
#include <fcntl.h>
#define recvfrom_size_param unsigned int
#elif defined _WIN32
#include <winsock2.h>
#define recvfrom_size_param int
#pragma comment( lib, "wsock32.lib" )
#pragma comment (lib, "Ws2_32.lib")
#endif

namespace TBSystem {
namespace network {
namespace sockets {
Udp::Udp()
{
  socketInit();
  errno = 0;
  _socket = socket(AF_INET, SOCK_DGRAM, 0);
  if (_socket == -1) throw std::runtime_error(strerror(errno));
}

Udp::~Udp() {
#ifdef __gnu_linux__
  close(_socket);
#elif defined _WIN32
  closesocket(_socket);
#endif
}

void Udp::bind(const IAddr & pair)
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

int Udp::send(const uint8_t * packet, int packetSize, const IAddr & pair)
{
  int ret;

  if (pair.hasValidAddr()) {
    ret = ::sendto(_socket, reinterpret_cast<const char *>(packet), packetSize, 0,
                   static_cast<const sockaddr *>(pair.getValid()),
                   pair.validSize());
  }
  else {
    for (auto& hint : pair.infos()) {
      if ((ret = ::sendto(_socket, reinterpret_cast<const char *>(packet), packetSize, 0,
                   static_cast<const sockaddr *>(hint->get()),
                   hint->size()))
          != -1) {
        pair.setValid(hint->get());
        break;
      }
    }
  }
  if (ret == -1) throw std::runtime_error(strerror(errno));
  return ret;
}

int Udp::recv(uint8_t * packet, int maxPacketSize, IAddr & pair)
{
  int ret;
  sockaddr_in buf;
  recvfrom_size_param len = sizeof(buf);

  memset(&buf, 0, sizeof(buf));
  errno = 0;
  ret = ::recvfrom(_socket, reinterpret_cast<char *>(packet), maxPacketSize, 0,
                   reinterpret_cast<sockaddr*>(&buf), &len);
  //if (errno != EWOULDBLOCK && ret == -1) throw std::runtime_error(strerror(errno));
  pair.setValid(static_cast<void *>(&buf));
  return ret;
}

void    Udp::setBlocking(bool v)
{
#ifdef __gnu_linux__

  int nonBlocking = !v;
  if ( fcntl( _socket, F_SETFL, O_NONBLOCK, nonBlocking ) == -1 )
  {
    log::err << "ERROR: " << strerror(errno) << log::endl;
  }

#elif defined _WIN32

  DWORD nonBlocking = !v;
  if ( ioctlsocket( _socket, FIONBIO, &nonBlocking ) != 0 )
  {
    log::err << "ERROR: " << WSAGetLastError() << log::endl;
  }

#endif
}
}
}
}
