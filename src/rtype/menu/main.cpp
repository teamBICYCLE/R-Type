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

void	playCallback()
{
  std::cout << "==PLAY==" << std::endl;
}

void	quitCallback()
{
  std::cout << "==QUIT==" << std::endl;
}

void	listCallback()
{
  std::cout << "==LISTITEM CLICKED==" << std::endl;
}

int	main(int argc, char *argv[])
{
  using namespace TBSystem;
  using namespace TBSystem::network;
  using namespace TBSystem::network::sockets;

  PreGame  pregame(argv[1], argv[2]);

  pregame.run();
  return EXIT_SUCCESS;
}
