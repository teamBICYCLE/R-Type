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

int	main(int argc, char *argv[])
{
  try {
    PreGame  pregame(argv[1], argv[2]);

    pregame.run();
  }
  catch (std::exception& e) {
    std::cout << e.what() << std::endl;
  }
  return EXIT_SUCCESS;
}
