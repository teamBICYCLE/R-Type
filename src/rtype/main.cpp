#ifdef _WIN32
#include <windows.h>
#include <stdlib.h>
#include <string.h>
#include <tchar.h>
#endif
#include <thread>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

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
        window.display();
        std::chrono::milliseconds duration( 1000 );
        std::this_thread::sleep_for(duration);
    }
    return 0;
}
