#ifdef _WIN32
#include <windows.h>
#include <stdlib.h>
#include <string.h>
#include <tchar.h>
#endif
#include <thread>
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
#include "GraphicGameState.hh"

using namespace std;
using namespace TBSystem;

#ifdef _WIN32
int WINAPI WinMain(HINSTANCE hInstance,
                   HINSTANCE hPrevInstance,
                   LPSTR lpCmdLine,
                   int nCmdShow)
#elif defined __gnu_linux__
int main(int argc, char* argv[])
#endif
{
    // tmp
    network::sockets::Udp s;
    network::Addr server(argv[1], argv[2], "UDP");
    Input::Config cfg;
    cfg._top = sf::Keyboard::Up;
    cfg._bot = sf::Keyboard::Down;
    cfg._left = sf::Keyboard::Left;
    cfg._right = sf::Keyboard::Right;
    cfg._fire = sf::Keyboard::Space;
    std::vector<std::shared_ptr<Unit>> players = {
      std::shared_ptr<Unit>(new GPlayer(0, Vector2D(0.1f, 0.1f), Vector2D(0.f, 0.f))),
      std::shared_ptr<Unit>(new GPlayer(1, Vector2D(0.1f, 0.2f), Vector2D(0.f, 0.f))),
      std::shared_ptr<Unit>(new GPlayer(2, Vector2D(0.1f, 0.3f), Vector2D(0.f, 0.f))),
      std::shared_ptr<Unit>(new GPlayer(3, Vector2D(0.1f, 0.4f), Vector2D(0.f, 0.f)))
    };
    GraphicGameState  g(players);

    sf::RenderWindow window(sf::VideoMode(800, 800), "RForceType v"
        + std::to_string(RTYPE_VERSION_MAJOR)
        + "." + std::to_string(RTYPE_VERSION_MINOR));

    s.setBlocking(false);
    s.bind(network::Addr(network::SI_ADDR_ANY, "4244", "UDP"));
    while (window.isOpen())
    {
        uint8_t buf[256];

        Input::Data i = cfg.getInput();
        i.setId(std::stoi(argv[3]));
        int ret = i.pack(buf, sizeof(buf));

        s.send(buf, ret, server);
        std::vector<network_packet::Packet> packets;

        while (s.recv(buf, sizeof(buf), server) != -1) {
            network_packet::Packet p((uint8_t*)buf, sizeof(buf));

            packets.push_back(p);
        }
        g.update(packets);
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }
        window.clear();
        window.draw(g);
        window.display();
        std::chrono::milliseconds duration(10);
        std::this_thread::sleep_for(duration);
    }
    return 0;
}
