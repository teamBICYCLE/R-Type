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
    GPlayer   player1(1, Vector2D(0.1f, 0.1f), Vector2D(0.01f, 0.f));
    // GPlayer   player2(2, Vector2D(0.1f, 0.2f), Vector2D(0.01f, 0.f));
    // GPlayer   player3(3, Vector2D(0.1f, 0.3f), Vector2D(0.01f, 0.f));
    // GPlayer   player4(4, Vector2D(0.1f, 0.4f), Vector2D(0.01f, 0.f));

    sf::RenderWindow window(sf::VideoMode(800, 600), "RForceType v"
        + std::to_string(RTYPE_VERSION_MAJOR)
        + "." + std::to_string(RTYPE_VERSION_MINOR));

    while (window.isOpen())
    {
        sf::Event event;
        log::debug << sf::Keyboard::isKeyPressed(sf::Keyboard::Left) << log::endl;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }
        window.clear();
        window.draw(player1);
        window.display();
        std::chrono::milliseconds duration(1000);
        std::this_thread::sleep_for(duration);
    }
    return 0;
}
