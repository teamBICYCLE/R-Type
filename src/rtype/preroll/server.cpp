/*
 * -----------------------------------------------------------------------------
 * "THE BEER-WARE LICENSE" (Revision 42):
 * <duplom_t@epitech.eu> wrote this file. As long as you retain this notice you
 * can do whatever you want with this stuff. If we meet some day, and you think
 * this stuff is worth it, you can buy me a beer in return. Thomas Duplomb
 * -----------------------------------------------------------------------------
 */

#include <memory>
#include <system/network/Tcp.hh>
#include <system/network/Addr.hh>

using namespace TBSystem;

void  server(network::sockets::ITcpSocket & sock) {
  std::vector<std::shared_ptr<network::sockets::ITcpSocket>> clients;

  while (1) {
    network::Addr clientAddr;
    std::shared_ptr<network::sockets::ITcpSocket> client = sock.accept(clientAddr);

    client->send("hi\n", sizeof("hi\n"));
    clients.push_back(client);
  }
}

int main(int argc, const char *argv[])
{
  // creation socket / bdd
  network::sockets::Tcp mainSocket;
  network::Addr addr(network::SI_ADDR_ANY, "4242", "TCP");

  mainSocket.bind(addr);
  mainSocket.listen(10);
  server(mainSocket);
  // main loop
  // cleanup
  return 0;
}
