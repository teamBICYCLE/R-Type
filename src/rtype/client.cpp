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
#include "sprites/AnimationManager.hh"
#include <memory>
#ifdef _WIN32
#include <stdlib.h>
#include <string.h>
#include <tchar.h>
#endif
#include "audio/Sound.hh"

using namespace std;
using namespace TBSystem;

Sound sounds;

//static const std::chrono::milliseconds g_frameDelta(1000 / 60);
//static const std::chrono::milliseconds g_maxFrameTime(25);
static const int  g_frameDelta(16);
static const int  g_maxFrameTime(25);
static const int  g_msToDisconnect(5000);

//#ifdef _WIN32
//int WINAPI WinMain(HINSTANCE hInstance,
                   //HINSTANCE hPrevInstance,
                   //LPSTR lpCmdLine,
                   //int nCmdShow)
//#elif defined __gnu_linux__
//int main(int argc, char* argv[])
//#endif

void client(const std::string& ip, const std::string& port, int id,
            sf::RenderWindow& window)
{
  std::cout << "connect on " << ip << ":" << port << std::endl;
  network::sockets::Udp s;
  network::Addr server(ip, port, "UDP");
  Input::Config cfg;
  cfg._top = sf::Keyboard::Up;
  cfg._bot = sf::Keyboard::Down;
  cfg._left = sf::Keyboard::Left;
  cfg._right = sf::Keyboard::Right;
  cfg._fire = sf::Keyboard::Space;

  std::shared_ptr<UnitPool> pool = std::shared_ptr<UnitPool>(new GUnitPool());
  std::shared_ptr<Sprite::AnimationManager> animationM = std::shared_ptr<Sprite::AnimationManager>(new Sprite::AnimationManager());
  animationM->addSourceFolder("resources/sprites");

  GPlayer *player = new GPlayer(id, Vector2D(0.1f, 0.1f), Vector2D(0.f, 0.f));
  player->setAnimationManager(animationM);
  GraphicGameState  g(pool, animationM, std::shared_ptr<GPlayer>(player));

  s.setBlocking(false);
  s.bind(network::Addr(network::SI_ADDR_ANY, "4244", "UDP"));

  sf::Clock clock;
  int lastServerUpdate = 0;
  int accumulator = 0;

  window.setFramerateLimit(300);
  while (window.isOpen() &&
         g.running() == true)
  {
    int frameTime = clock.getElapsedTime().asMilliseconds();
    if (frameTime > g_maxFrameTime)
      frameTime = g_maxFrameTime;
    accumulator += frameTime;
    lastServerUpdate += frameTime;

    clock.restart();

    if (lastServerUpdate >= g_msToDisconnect) {
      log::err << "Connection to server lost." << std::endl;
      break;
    }
    while (accumulator >= g_frameDelta)
    {
      uint8_t buf[256];

      Input::Data i = cfg.getInput();
      i.setId(id);
      g.simulate(i);
      int ret = i.pack(buf, sizeof(buf));

      s.send(buf, ret, server);
      std::vector<communication::Packet> packets;

      while (s.recv(buf, sizeof(buf), server) != -1) {
        communication::Packet p((uint8_t*)buf, sizeof(buf));

        lastServerUpdate = 0;
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
  }
}
