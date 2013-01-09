#ifdef _WIN32
#include <windows.h>
#include <stdlib.h>
#include <string.h>
#include <tchar.h>
#endif
#include <thread>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "units/graphics/GPlayer.hh"
#include <system/log/Log.hh>
#include <system/network/Udp.hh>
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
    cfg._top = sf::Keyboard::UP;
    cfg._bot = sf::Keyboard::DOWN;
    cfg._left = sf::Keyboard::LEFT;
    cfg._right = sf::Keyboard::RIGHT;
    cfg._fire = sf::Keyboard::SPACE;
    GPlayer   player1(1, Vector2D(0.1f, 0.1f), Vector2D(0.01f, 0.f));
    GPlayer   player2(2, Vector2D(0.1f, 0.2f), Vector2D(0.01f, 0.f));
    GPlayer   player3(3, Vector2D(0.1f, 0.3f), Vector2D(0.01f, 0.f));
    GPlayer   player4(4, Vector2D(0.1f, 0.4f), Vector2D(0.01f, 0.f));

    sf::RenderWindow window(sf::VideoMode(800, 800), "RForceType v"
        + std::to_string(RTYPE_VERSION_MAJOR)
        + "." + std::to_string(RTYPE_VERSION_MINOR));

    while (window.isOpen())
    {
        Input::Data i = cfg.getInput();

        i.setId(std::stoi(argv[3]));
        s.send(&i.getPacket(), sizeof(&i.getPacket()), server);

        char buf[256];
        while (s.recv()) {
            network_packet::Packet p(buf, sizeof(buf));

            UnitPacket_u u(p.getContent());
            switch (u.getId()) {
                case 1:
                    player1.update(u);
                    break;
                case 2:
                    player2.udpate(u);
                    break;
                case 3:
                    player3.update(u);
                    break;
                case 4:
                    player4.update(u);
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
        std::chrono::milliseconds duration(1000);
        std::this_thread::sleep_for(duration);
    }
    return 0;
}
