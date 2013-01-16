#include <thread>
#include <chrono>
#include <system/log/Log.hh>
#include <system/network/Udp.hh>
#include <system/network/Addr.hh>
#include "units/Unit.hh"
#include "input/Data.hh"
#include "gamestate/ServerGameState.hh"
#include "network/NetworkHandler.hh"

using namespace TBSystem;

static const std::chrono::milliseconds g_serverUpdateRate(16);
static const std::chrono::milliseconds g_serverPacketRate(100);

void intTobinary(int num){
  if(num>0){
    intTobinary(num/2);
    printf("%d",num%2);
  }
}

int     main(int argc, char *argv[])
{
  // all those informations will be coming from game init
  std::vector<network::Addr> clients;
  clients.push_back(network::Addr("10.23.99.201", "4244", "UDP"));
  clients.push_back(network::Addr("10.23.99.200", "4244", "UDP"));
  clients.push_back(network::Addr("10.23.98.230", "4244", "UDP"));

  std::vector<std::shared_ptr<Player>> players;

  players.push_back(std::shared_ptr<Player>(new Player(0, Vector2D(0.1f, 0.1f), Vector2D(0.f, 0.f))));
  players.push_back(std::shared_ptr<Player>(new Player(1, Vector2D(0.1f, 0.2f), Vector2D(0.f, 0.f))));
  players.push_back(std::shared_ptr<Player>(new Player(2, Vector2D(0.1f, 0.3f), Vector2D(0.f, 0.f))));
  players.push_back(std::shared_ptr<Player>(new Player(3, Vector2D(0.1f, 0.4f), Vector2D(0.f, 0.f))));

  // START OF THE REAL LOOP
  communication::NetworkHandler   nh;
  std::chrono::time_point<std::chrono::system_clock> currentTime = std::chrono::system_clock::now();
  std::chrono::time_point<std::chrono::system_clock> newTime;
  std::chrono::time_point<std::chrono::system_clock> lastSent;
  std::chrono::milliseconds accumulator;

  nh.setClients(clients);
  network::sockets::Udp s;
  ServerGameState g(players);
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
      g.move();
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
