#include <iostream>
#include <string>
#include <thread>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <system/log/Log.hh>
#include <system/network/Udp.hh>
#include <system/network/Addr.hh>
#include "RTypeConfig.h"
#ifdef _WIN32
#include <windows.h>
#include <stdlib.h>
#include <string.h>
#include <tchar.h>
#endif
#include <string.h>

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
    //network::Addr pair(network::ADDR_ANY, "4242", "UDP");
    //network::sockets::Udp udp;
    //char buf[1024];

    log::notice.configure("output.log");
	log::notice << "Test some stuff out";
	log::notice << "other stuff" << std::endl;
	log::notice << "end test" << log::endl;
    //udp.bind(pair);
    //while (1) {
        //memset(buf, 0, sizeof(buf));
        //if (udp.recv(buf, sizeof(buf), pair) > 0) {
            //log::debug << buf << log::endl;
            //return 0;
        //}
        //std::chrono::milliseconds duration( 100 );
        //std::this_thread::sleep_for(duration);
    //}
    //return 0;
    sf::RenderWindow window(sf::VideoMode(800, 600), "RType v"
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
        std::chrono::milliseconds duration( 100 );
        std::this_thread::sleep_for(duration);
    }
    return 0;
}
