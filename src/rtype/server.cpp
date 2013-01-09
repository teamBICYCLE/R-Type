#include <thread>
#include <system/log/Log.hh>
#include <system/network/Udp.hh>
#include <system/network/Addr.hh>
#include "units/AUnit.hh"
#include "input/Data.hh"

using namespace TBSystem;

void intTobinary(int num){
    if(num>0){
        intTobinary(num/2);
        printf("%d",num%2);
    }
}

int     main(int argc, char *argv[])
{
#ifdef _WIN32
	WSADATA WsaData;
	WSAStartup( MAKEWORD(2,2), &WsaData );
#endif
    AUnit   player1(1, Vector2D(0.1f, 0.1f), Vector2D(0.f, 0.f));
    network::Addr p1_s("127.0.0.1", "4244", "UDP");
    AUnit   player2(2, Vector2D(0.1f, 0.2f), Vector2D(0.f, 0.f));
    AUnit   player3(3, Vector2D(0.1f, 0.3f), Vector2D(0.f, 0.f));
    AUnit   player4(4, Vector2D(0.1f, 0.4f), Vector2D(0.f, 0.f));
    network::sockets::Udp s;
    network::Addr pair(network::SI_ADDR_ANY, "4242", "UDP");

    s.setBlocking(false);
    s.bind(pair);
    Input::Data tmp;

	tmp.setId(2); tmp.setBot(true);
    log::notice << "id mal code " << sizeof(tmp) << log::endl;
    log::notice << tmp.getPacket() << log::endl;
    while (1)
    {
        log::notice << std::endl << player1 << std::endl;
        log::notice << player2 << std::endl;
        log::notice << player3 << std::endl;
        log::notice << player4 << log::endl;

        // recupere les input
        int i;
        network::Addr clt;
        while (s.recv(reinterpret_cast<char*>(&i), sizeof(i), clt) != -1) {
            Input::Data input(i);

            switch (input.getId()) {
                case 1:
                    player1.setDirection(input.getVector() / 100);
                    break;
                case 2:
                    player2.setDirection(input.getVector() / 100);
                    break;
                case 3:
                    player3.setDirection(input.getVector() / 100);
                    break;
                case 4:
                    player4.setDirection(input.getVector() / 100);
                    break;
                default:
                    break;
            }
        }
        player1.move();
        char buf[256];
        int ret = player1.pack(reinterpret_cast<uint8_t*>(buf), sizeof(buf));
        log::debug << "ret = " << ret << log::endl;
        s.send(buf, ret, p1_s);
		player1.setDirection(Vector2D());
        player2.move();
		player2.setDirection(Vector2D());
        player3.move();
		player3.setDirection(Vector2D());
        player4.move();
		player4.setDirection(Vector2D());

        std::chrono::milliseconds    duration(10);
        std::this_thread::sleep_for(duration);
    }
#ifdef _WIN32
	WSACleanup();
#endif
}
