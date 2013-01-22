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
  PreGame  pregame(argv[1], argv[2]);

  pregame.run();
  return EXIT_SUCCESS;
}
