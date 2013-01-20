
#ifdef _WIN32
#include <windows.h>
#include <stdlib.h>
#include <string.h>
#include <tchar.h>
#endif
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
  network::Addr server(argv[1], argv[2], "UDP");
  Input::Config cfg;
  cfg._top = sf::Keyboard::Up;
  cfg._bot = sf::Keyboard::Down;
  cfg._left = sf::Keyboard::Left;
  cfg._right = sf::Keyboard::Right;
  cfg._fire = sf::Keyboard::Space;
  std::vector<std::shared_ptr<Player>> players;
  GUnitPool *p = GUnitPool::getInstance();

  float pos = 0.1f;
  for (int i = 0; i != 4; i++)
  {
    GPlayer *player = p->get<GPlayer>();
    player->setId(i);
    player->setPos(Vector2D(pos, 0.1f));
    player->setDir(Vector2D(0.f, 0.f));
    players.push_back(std::shared_ptr<Player>(player));
    pos += 0.1f;
  }

  // players.push_back(std::shared_ptr<Player>(new GPlayer(0, Vector2D(0.1f, 0.1f), Vector2D(0.f, 0.f))));
  // players.push_back(std::shared_ptr<Player>(new GPlayer(1, Vector2D(0.1f, 0.2f), Vector2D(0.f, 0.f))));
  // players.push_back(std::shared_ptr<Player>(new GPlayer(2, Vector2D(0.1f, 0.3f), Vector2D(0.f, 0.f))));
  // players.push_back(std::shared_ptr<Player>(new GPlayer(3, Vector2D(0.1f, 0.4f), Vector2D(0.f, 0.f))));

  sf::RenderWindow window(sf::VideoMode(GameState::WINDOW_WIDTH, GameState::WINDOW_HEIGHT),
                          "RForceType v"
                          + std::to_string(RTYPE_VERSION_MAJOR)
                          + "." + std::to_string(RTYPE_VERSION_MINOR));
  GraphicGameState  g(players);

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
      i.setId(std::stoi(argv[3]));
      g.simulate(i);
      int ret = i.pack(buf, sizeof(buf));

      s.send(buf, ret, server);
      std::vector<communication::Packet> packets;

      while (s.recv(buf, sizeof(buf), server) != -1) {
        communication::Packet p((uint8_t*)buf, sizeof(buf));

        //ROMAIN: ici tu recuperes le packet le plus tot possible
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
