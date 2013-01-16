/*
 * -----------------------------------------------------------------------------
 * "THE BEER-WARE LICENSE" (Revision 42):
 * <duplom_t@epitech.eu> wrote this file. As long as you retain this notice you
 * can do whatever you want with this stuff. If we meet some day, and you think
 * this stuff is worth it, you can buy me a beer in return. Thomas Duplomb
 * -----------------------------------------------------------------------------
 */

#include <memory>
#include <functional>
#include <iostream>
#include <system/network/Tcp.hh>
#include <system/network/Addr.hh>
#include <system/network/Listener.hh>
#include "Lounge.hh"

using namespace TBSystem;

int  server(std::shared_ptr<network::sockets::ITcpSocket> & sock) {
  Lounge lounge(sock);

  return lounge.exec();
}

int main(int argc, const char *argv[])
{
  // creation socket
  std::shared_ptr<network::sockets::ITcpSocket> mainSocket(new network::sockets::Tcp);
  network::Addr addr(network::SI_ADDR_ANY, "4242", "TCP");

  mainSocket->bind(addr);
  mainSocket->listen(10);
  // main loop
  server(mainSocket);

  // cleanup
  return 0;
}
