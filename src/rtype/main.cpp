#include <iostream>
#include <SFML/Graphics.hpp>
#include <system/network/Addr.hh>
#include <system/network/Tcp.hh>
using namespace std;

int main(int argc, char* argv[]) {
    sf::RenderWindow window(sf::VideoMode(200, 200), "SFML works!");
    sf::CircleShape shape(100.f);
    shape.setFillColor(sf::Color::Green);
    network::Addr pair("localhost", "4242", "TCP");
    network::sockets::Tcp s;

    s.connect(pair);
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
