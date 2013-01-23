#include "Button.hh"
#include "ListView.hh"
#include "ListItem.hh"
#include "View.hh"
#include <functional>
#include <SFML/Graphics.hpp>
#include <system/log/Log.hh>
#include <system/network/Listener.hh>
#include <system/network/Tcp.hh>
#include <system/network/Addr.hh>
#include <iostream>
#include "PreGame.hh"

std::string resourcesPath;

int	main(int argc, char *argv[])
{
  if (argc < 4) {
    std::cerr << "Usage: ./client <ip> <port> <resources_path>" << std::endl;
    return EXIT_FAILURE;
  }
  resourcesPath = argv[3];
  try {
    PreGame  pregame(argv[1], argv[2]);

    pregame.run();
  }
  catch (std::exception& e) {
    std::cout << e.what() << std::endl;
  }
  return EXIT_SUCCESS;
}
