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
#include "units/AUnit.hh"
#include "input/Data.hh"
#include "input/Config.hh"
#include <libs/system/log/Log.hh>
#include <system/network/Udp.hh>
#include <system/network/Addr.hh>
#include "RTypeConfig.h"

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

    GPlayer   player1(1, Vector2D(0.1f, 0.1f), Vector2D(0.01f, 0.f));
    GPlayer   player2(2, Vector2D(0.1f, 0.2f), Vector2D(0.01f, 0.f));
    GPlayer   player3(3, Vector2D(0.1f, 0.3f), Vector2D(0.01f, 0.f));
    GPlayer   player4(4, Vector2D(0.1f, 0.4f), Vector2D(0.01f, 0.f));

    sf::RenderWindow window(sf::VideoMode(800, 800), "RForceType v"
        + std::to_string(RTYPE_VERSION_MAJOR)
        + "." + std::to_string(RTYPE_VERSION_MINOR));

    s.setBlocking(false);
    s.bind(network::Addr(network::SI_ADDR_ANY, "4244", "UDP"));
    while (window.isOpen())
    {
        Input::Data i = cfg.getInput();
        i.setId(std::stoi(argv[3]));

        uint32_t data = i.getPacket();

        log::debug << "data value: " << data << log::endl;
        s.send(reinterpret_cast<const char*>(&data), sizeof(data), server);

        char buf[256];
        while (s.recv(buf, sizeof(buf), server) != -1) {
            network_packet::Packet p((uint8_t*)buf, sizeof(buf));
            const UnitPacket_u * content = reinterpret_cast<const UnitPacket_u*>(p.getContent());

            log::debug << "Player #" << content->id << "pos: " << content->x << ":" << content->y << log::endl;
            switch (content->id) {
                case 1:
                    player1.update(p);
                    break;
                case 2:
                    player2.update(p);
                    break;
                case 3:
                    player3.update(p);
                    break;
                case 4:
                    player4.update(p);
                    break;
                default:
                    break;
            }
        }
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }
        window.clear();
        window.draw(player1);
        window.draw(player2);
        window.draw(player3);
        window.draw(player4);
        window.display();
        std::chrono::milliseconds duration(10);
        std::this_thread::sleep_for(duration);
    }
    return 0;
}
