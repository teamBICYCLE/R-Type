#include <iostream>
#include <string>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include <system/archiver/ResourcesArchiver.hh>

#ifdef _WIN32
#include <system/threads/WinMutex.hh>
#elif defined __gnu_linux__
#include <system/threads/UnixMutex.hh>
#endif
#include <system/log/Log.hh>
#include "RTypeConfig.h"
using namespace std;
using namespace TBSystem;

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
#elif defined __gnu_linux__
int main(int argc, char* argv[])
#endif
{
	sf::RenderWindow window(sf::VideoMode(800, 600), "RType v"
		+ std::to_string(RTYPE_VERSION_MAJOR) + "." + std::to_string(RTYPE_VERSION_MINOR));
	sf::SoundBuffer buffer;
    sf::CircleShape shape(100.f);
    shape.setFillColor(sf::Color::Green);
#ifdef _WIN32
	WinMutex mut;
#elif defined __gnu_linux__
	UnixMutex mut;
#endif

    ResourcesArchiver a("toto");
    a.add("test/av.jpg");
    a.add("test/lolo.jpg");

    a.pack();
    std::cout << "Eeeeeeeeee" << std::endl;
    ResourcesArchiver::unpack(std::string("toto.ar"), "res");

	log::notice << "Test some stuff out";
	log::notice << "other stuff" << std::endl;
	log::notice << "endtest" << log::endl;
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
