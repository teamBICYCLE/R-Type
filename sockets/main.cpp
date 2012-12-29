#include "Tcp.hh"
#include "Addr.hh"
#define TRUE 1
#define FALSE 0
#if FALSE == TRUE
// UDP Broadcast
int main()
{
    network::sockets::Udp s;
    network::Addr pair("255.0.0.37", 4242);

    while (1) s.send("bonjour\n", sizeof("bonjour\n"), pair);
    return 0;
}
#elif FALSE == TRUE
// UDP Recv
int main()
{
    network::sockets::Udp s;
    network::Addr broadChan(netork::addr::INADDR_ANY, 4242);
    char buf[127];

    s.bind(broadChan);
    while (1) {
        network::Addr pair;
        int len = s.recv(buf, sizeof(buf), pair);

        write(1, buf, len);
    }
    return 0;
}

#elif TRUE == TRUE
// TCP Client
int main()
{
    network::sockets::Tcp s;
    network::Addr pair("127.0.0.1", 4242);

    s.connect(pair); // ca bloque !
    s.send("salut\n", sizeof("salut\n"));
    return 0;
}

#elif FALSE == TRUE
// TCP Server
int main()
{
    network::sockets::Tcp s;
    network::sockets::Tcp s2;
    char buf[127];

    s.listen(5);
    s2 = s.accept();
    int len = s2.recv(buf, sizeof(buf));
    write(1, buf, len);
    return 0;
}
#endif
