#include <thread>
#include <system/log/Log.hh>
#include <system/network/Udp.hh>
#include <system/network/Addr.hh>
#include "units/Unit.hh"
#include "input/Data.hh"
#include "gamestate/ServerGameState.hh"
#include "network/NetworkHandler.hh"

using namespace TBSystem;

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

  std::vector<std::shared_ptr<Unit>> players;

  players.push_back(std::shared_ptr<Unit>(new Unit(0, Vector2D(0.1f, 0.1f), Vector2D(0.f, 0.f))));
  players.push_back(std::shared_ptr<Unit>(new Unit(1, Vector2D(0.1f, 0.2f), Vector2D(0.f, 0.f))));
  players.push_back(std::shared_ptr<Unit>(new Unit(2, Vector2D(0.1f, 0.3f), Vector2D(0.f, 0.f))));
  players.push_back(std::shared_ptr<Unit>(new Unit(3, Vector2D(0.1f, 0.4f), Vector2D(0.f, 0.f))));

  // START OF THE REAL LOOP
  communication::NetworkHandler   nh;

  nh.setClients(clients);
  network::sockets::Udp s;
  ServerGameState g(players);
  while (1)
  {
    // updates the player vectors from inputs
    g.update(nh.getIncomingPackets());
    g.move();
    nh.broadcast(g);

    std::chrono::milliseconds    duration(10);
    std::this_thread::sleep_for(duration);
  }
}
