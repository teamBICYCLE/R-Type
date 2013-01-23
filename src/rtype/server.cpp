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
  int   playerIdx = 0;
  float playerSpacing = GameState::WINDOW_HEIGHT / static_cast<float>(clientsIps.size());
  std::vector<network::Addr> clients;
  std::vector<Player*> players;
  std::shared_ptr<UnitPool> pool = std::shared_ptr<UnitPool>(new SUnitPool());

  for (auto& addr : clientsIps) {
    Player *player = pool->get<Player>();

    if (player == nullptr) {
      log::err << "Could not create the players" << log::endl;
      return;
    }
    player->setId(playerIdx);
    player->setPos(Vector2D(0.1f, (((playerSpacing * static_cast<float>(playerIdx + 1)) -
                                   (playerSpacing / 2.f))) / GameState::WINDOW_HEIGHT));
    player->setDir(Vector2D(0.f, 0.f));
    player->setFireFrequence(std::chrono::milliseconds(200));
    players.push_back(player);
    log::debug  << "add client with addr " << addr << log::endl;
    clients.push_back(network::Addr(addr, "4244", "UDP"));
    playerIdx++;
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
  while (g.running() == true)
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
  while (nh.allReliablePacketsSent() == false) {
    g.update(nh.getIncomingPackets());
    nh.trySendAll();
    //std::this_thread::sleep_for(g_serverUpdateRate - accumulator);
  }
}
