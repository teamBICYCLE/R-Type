#include <iostream>
#include <string>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <system/threads/WinMutex.hh>
#include <system/log/Log.hh>
#include "RTypeConfig.h"
using namespace std;

#ifdef _WIN32
#include <windows.h>
#include <stdlib.h>
#include <string.h>
#include <tchar.h>
#endif

#ifdef _WIN32
int WINAPI WinMain(HINSTANCE hInstance,
                   HINSTANCE hPrevInstance,
                   LPSTR lpCmdLine,
                   int nCmdShow)
#elif defined UNIX
int main(int argc, char* argv[]) 
#endif
{
	sf::RenderWindow window(sf::VideoMode(800, 600), "RType v" 
		+ std::to_string(RTYPE_VERSION_MAJOR) + "." + std::to_string(RTYPE_VERSION_MINOR));
	sf::SoundBuffer buffer;
    sf::CircleShape shape(100.f);
    shape.setFillColor(sf::Color::Green);
	WinMutex mut;

	TBSystem::log::notice << "Test some stuff out" << TBSystem::log::endl;
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear();
        window.draw(shape);
        window.display();
    }
    return 0;
}