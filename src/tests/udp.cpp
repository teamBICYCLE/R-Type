#include <thread>
#include <system/network/Udp.hh>
#include <system/network/Addr.hh>
#include <system/log/Log.hh>
#include <string.h>

using namespace TBSystem;

int main(int argc, const char *argv[])
{
    network::Addr pair(network::ADDR_ANY, "4242", "UDP");
    network::sockets::Udp udp;
    char buf[1024];

    udp.bind(pair);
    while (1) {
        memset(buf, 0, sizeof(buf));
        if (udp.recv(buf, sizeof(buf), pair) > 0) {
            log::debug << buf << log::endl;
            return 0;
        }
        std::chrono::milliseconds duration( 100 );
        std::this_thread::sleep_for(duration);
    }
    return 0;
}
