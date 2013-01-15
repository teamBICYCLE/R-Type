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

using namespace TBSystem;

void print(std::shared_ptr<network::sockets::ITcpSocket>& s, network::Listener& l)
{
  char buf[512];

  buf[s->recv(buf, sizeof(buf))] = '\0';
  std::cout << "client said: " << buf << std::endl;
}

void handleAccept(std::vector<std::shared_ptr<network::sockets::ITcpSocket>>& c,
                  std::shared_ptr<network::sockets::ITcpSocket>& s, network::Listener& l)
{
  using namespace std::placeholders;

  network::Addr clientAddr;
  std::shared_ptr<network::sockets::ITcpSocket> client = s->accept(clientAddr);

  l.addSocket(client, std::bind(&print, _1, _2));
  client->send("hi\n", sizeof("hi\n"));
  c.push_back(client);
}

void  server(std::shared_ptr<network::sockets::ITcpSocket> & sock) {
  using namespace network::sockets;
  using namespace std::placeholders;

  network::Listener l;
  std::vector<std::shared_ptr<ITcpSocket>> clients;

  l.addSocket(sock, std::bind(&handleAccept, clients, _1, _2));
  while (1) {
    if (l.waitEvent(std::chrono::seconds(5))) l.execute();

    for (auto& c : clients) {
      c->send("someone connected\n", sizeof("someone connected\n"));
    }
  }
}

int main(int argc, const char *argv[])
{
  // creation socket / bdd
  std::shared_ptr<network::sockets::ITcpSocket> mainSocket(new network::sockets::Tcp);
  network::Addr addr(network::SI_ADDR_ANY, "4242", "TCP");

  mainSocket->bind(addr);
  mainSocket->listen(10);
  server(mainSocket);
  // main loop
  // cleanup
  return 0;
}
