
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Window/Keyboard.hpp>
#include "units/graphics/GPlayer.hh"
#include "input/Data.hh"
#include "input/Config.hh"
#include <libs/system/log/Log.hh>
#include <system/network/Udp.hh>
#include <system/network/Addr.hh>
#include "RTypeConfig.h"
#include "gamestate/GraphicGameState.hh"
#include "pool/GUnitPool.hh"
#include "units/Player.hh"
#include <memory>
#ifdef _WIN32
#include <stdlib.h>
#include <string.h>
#include <tchar.h>
#endif

using namespace std;
using namespace TBSystem;

//static const std::chrono::milliseconds g_frameDelta(1000 / 60);
//static const std::chrono::milliseconds g_maxFrameTime(25);
static const int  g_frameDelta(16);
static const int  g_maxFrameTime(25);

#ifdef _WIN32
int WINAPI WinMain(HINSTANCE hInstance,
                   HINSTANCE hPrevInstance,
                   LPSTR lpCmdLine,
                   int nCmdShow)
#elif defined __gnu_linux__
int main(int argc, char* argv[])
#endif
{
  network::sockets::Udp s;
  network::Addr server("10.23.98.230", "4242", "UDP");
  Input::Config cfg;
  cfg._top = sf::Keyboard::Up;
  cfg._bot = sf::Keyboard::Down;
  cfg._left = sf::Keyboard::Left;
  cfg._right = sf::Keyboard::Right;
  cfg._fire = sf::Keyboard::Space;

  sf::RenderWindow window(sf::VideoMode(GraphicGameState::WINDOW_WIDTH, GraphicGameState::WINDOW_HEIGHT),
                          "RForceType v"
                          + std::to_string(RTYPE_VERSION_MAJOR)
                          + "." + std::to_string(RTYPE_VERSION_MINOR));

  //GPlayer *player = GUnitPool::getInstance()->get<GPlayer>();
  //player->setId(std::stoi(argv[3]));
  //player->setPos(Vector2D(0.1f, 0.1f));
  //player->setDir(Vector2D(0.f, 0.f));
  GraphicGameState  g(std::shared_ptr<GPlayer>(new GPlayer(std::stoi("1"),
                                  Vector2D(0.1f, 0.1f), Vector2D(0.f, 0.f))));

  s.setBlocking(false);
  s.bind(network::Addr(network::SI_ADDR_ANY, "4244", "UDP"));

  sf::Clock clock;
  int lastFpsPrinted = 0;
  int accumulator = 0;
  int timeDraw = 0;
  window.setFramerateLimit(300);
  while (window.isOpen())
  {
    int frameTime = clock.getElapsedTime().asMilliseconds();
    if (frameTime > g_maxFrameTime)
      frameTime = g_maxFrameTime;
    accumulator += frameTime;
    lastFpsPrinted += frameTime;

    if (lastFpsPrinted >= 1000)
    {
      std::cout << timeDraw << "fps" << std::endl;
      timeDraw = 0;
      lastFpsPrinted -= 1000;
    }

    clock.restart();

    while (accumulator >= g_frameDelta)
    {
      uint8_t buf[256];

      Input::Data i = cfg.getInput();
      i.setId(std::stoi("1"));
      g.simulate(i);
      int ret = i.pack(buf, sizeof(buf));

      s.send(buf, ret, server);
      std::vector<communication::Packet> packets;

      while (s.recv(buf, sizeof(buf), server) != -1) {
        communication::Packet p((uint8_t*)buf, sizeof(buf));

        packets.push_back(p);
        if (p.isReliable() == true) {//if the packet needs an ack, we send it
          p.setType(communication::Packet::Type::ACK);
          s.send(p.getData(), p.getDataSize(), server);
        }
      }
      g.update(packets);
      accumulator -= g_frameDelta;
    }
    g.animationUpdate();

    sf::Event event;
    while (window.pollEvent(event))
    {
      if (event.type == sf::Event::Closed)
        window.close();
    }
    window.clear();
    window.draw(g);
    window.display();
    timeDraw++;
  }
  return EXIT_SUCCESS;
}
