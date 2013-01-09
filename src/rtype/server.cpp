#include <thread>
#include <system/log/Log.hh>
#include <system/network/Udp.hh>
#include <system/network/Addr.hh>
#include "units/AUnit.hh"
#include "Input.hh"

using namespace TBSystem;

void intTobinary(int num){
    if(num>0){
        intTobinary(num/2);
        printf("%d",num%2);
    }
}

int     main(int argc, char *argv[])
{
    AUnit   player1(1, Vector2D(0.1f, 0.1f), Vector2D(0.01f, 0.f));
    AUnit   player2(2, Vector2D(0.1f, 0.2f), Vector2D(0.01f, 0.f));
    AUnit   player3(3, Vector2D(0.1f, 0.3f), Vector2D(0.01f, 0.f));
    AUnit   player4(4, Vector2D(0.1f, 0.4f), Vector2D(0.01f, 0.f));
    network::sockets::Udp s;
    network::Addr pair(network::SI_ADDR_ANY, "4242", "UDP");

    s.setBlocking(false);
    s.bind(pair);
    Input tmp;

    tmp.setId(2); tmp.setBot(true);
    log::notice << "id mal code " << sizeof(tmp) << log::endl;
    log::notice << tmp.getId() << log::endl;
    while (1)
    {
        log::notice << player1 << std::endl;
        log::notice << player2 << std::endl;
        log::notice << player3 << std::endl;
        log::notice << player4 << log::endl;

        // recupere les input
        int i;
        network::Addr clt;
        while (s.recv(reinterpret_cast<char*>(&i), sizeof(i), clt) != -1) {
            Input input(i);

            switch (input.getId()) {
                case 1:
                    player1.setDirection(input.getVector() / 10);
                    break;
                case 2:
                    player2.setDirection(input.getVector() / 10);
                    break;
                case 3:
                    player3.setDirection(input.getVector() / 10);
                    break;
                case 4:
                    player4.setDirection(input.getVector() / 10);
                    break;
                default:
                    break;
            }
        }
        player1.move();
        player2.move();
        player3.move();
        player4.move();

        std::chrono::seconds    duration(1);
        std::this_thread::sleep_for(duration);
    }
}
