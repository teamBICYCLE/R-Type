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
#include <stdexcept>
#include "Lounge.hh"

using namespace TBSystem;

std::string resourcesPath;

int  server(std::shared_ptr<network::sockets::ITcpSocket> & sock) {
  Lounge lounge(sock);

  return lounge.exec();
}

int main(int argc, const char *argv[])
{
  if (argc < 2) {
    std::cerr << "Usage: ./server <resources_path>" << std::endl;
    return EXIT_FAILURE;
  }
  resourcesPath = argv[1];

  try {
    // creation socket
    std::shared_ptr<network::sockets::ITcpSocket> mainSocket(new network::sockets::Tcp);
    network::Addr addr(network::SI_ADDR_ANY, "4242", "TCP");

    mainSocket->bind(addr);
    mainSocket->listen(10);
    // main loop
    server(mainSocket);
  }
  catch (std::runtime_error &e) {
    std::cout << e.what() << std::endl;
  }
  catch (std::exception& e) {
    std::cout << e.what() << std::endl;
  }
  // cleanup
  return 0;
}
