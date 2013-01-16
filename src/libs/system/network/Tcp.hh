/*
 * -----------------------------------------------------------------------------
 * "THE BEER-WARE LICENSE" (Revision 42):
 * <duplom_t@epitech.eu> wrote this file. As long as you retain this notice you
 * can do whatever you want with this stuff. If we meet some day, and you think
 * this stuff is worth it, you can buy me a beer in return Thomas Duplomb
 * -----------------------------------------------------------------------------
 */

#ifndef _TCP_H__
#define _TCP_H__

#include "ITcpSocket.hh"
#include "IAddr.hh"

namespace TBSystem {
namespace network {

class Listener;
namespace sockets {

class Tcp : public ITcpSocket {
public:

  Tcp();

  explicit Tcp(int socketDescriptor);

  virtual ~Tcp();

  virtual void listen(int queueLenght);

  virtual void bind(const IAddr & addr);

  virtual std::shared_ptr<ITcpSocket> accept(IAddr & pair);

  virtual void connect(const IAddr & pair);

  virtual int recv(char * packet, int maxPacketSize);

  virtual int send(const char * packet, int packetSize);

  virtual int getUnderlyingSocket() const;

  virtual bool hasPendingDatagram() const;

private:
  int _socket;
};
}
}
}

#endif /* !_TCP_H__ */
