#include <thread>
#include <chrono>
#include <system/log/Log.hh>
#include <system/network/Udp.hh>
#include <system/network/Addr.hh>
#include "units/Unit.hh"
#include "input/Data.hh"
#include "gamestate/ServerGameState.hh"
#include "network/NetworkHandler.hh"
#include "pool/SUnitPool.hh"

using namespace TBSystem;

static const std::chrono::milliseconds g_serverUpdateRate(16);
static const std::chrono::milliseconds g_serverPacketRate(16);

void  runServer(const std::vector<std::string>& clientsIps,
                const std::string& port)
{
  std::vector<network::Addr> clients;

  for (auto& addr : clientsIps) {
    clients.push_back(network::Addr(addr, "4244", "UDP"));
  }

  std::vector<Player*> players;
  std::shared_ptr<UnitPool> pool = std::shared_ptr<UnitPool>(new SUnitPool());
  for (int i = 0; i < 4; i++)
  {
    Player *player = pool->get<Player>();

    if (player == nullptr) {
      log::err << "Could not create the players" << log::endl;
      return;
    }
    player->setId(i);
    player->setPos(Vector2D(0.1f, 0.1f * (float)(i + 1)));
    player->setDir(Vector2D(0.f, 0.f));
    players.push_back(player);
  }

  // START OF THE REAL LOOP
  communication::NetworkHandler   nh(port);
  std::chrono::time_point<std::chrono::system_clock> currentTime = std::chrono::system_clock::now();
  std::chrono::time_point<std::chrono::system_clock> newTime;
  std::chrono::time_point<std::chrono::system_clock> lastSent;
  std::chrono::milliseconds accumulator;

  nh.setClients(clients);
  network::sockets::Udp s;
  ServerGameState g(pool, players);
  while (1)
  {
    newTime = std::chrono::system_clock::now();
    std::chrono::milliseconds frameTime = std::chrono::duration_cast<std::chrono::milliseconds>
                                          (newTime - currentTime);

    if (frameTime > g_serverUpdateRate)
      frameTime = g_serverUpdateRate;
    accumulator += frameTime;
    currentTime = newTime;
    while (accumulator >= g_serverUpdateRate)
    {
      // updates the player vectors from inputs
      g.update(nh.getIncomingPackets());
      g.updateWorld();
      g.moveAll();
      accumulator -= g_serverUpdateRate;
    }
    if (newTime - lastSent >= g_serverPacketRate)
    {
      nh.broadcast(g);
      lastSent = newTime;
    }
    if (accumulator < g_serverUpdateRate)//sleep to the next frame
      std::this_thread::sleep_for(g_serverUpdateRate - accumulator);
  }
}

int     main(int argc, char *argv[])
{
  std::vector<std::string>  clients;

  clients.push_back("10.23.99.201");
  clients.push_back("10.23.99.200");
  //clients.push_back("10.23.98.230");
  clients.push_back("192.168.1.32");
  clients.push_back("10.23.98.165");
  runServer(clients, "4242");
  return EXIT_SUCCESS;
}
