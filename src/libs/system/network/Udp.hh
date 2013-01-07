/*
 * -----------------------------------------------------------------------------
 * "THE BEER-WARE LICENSE" (Revision 42):
 * <duplom_t@epitech.eu> wrote this file. As long as you retain this notice you
 * can do whatever you want with this stuff. If we meet some day, and you think
 * this stuff is worth it, you can buy me a beer in return Thomas Duplomb
 * -----------------------------------------------------------------------------
 */

#ifndef _UDP_H__
#define _UDP_H__
#ifdef __gnu_linux__
# include "UnixUdp.hh"
# define Parent UnixUdp
#elif defined _WIN32
# include "WinUdp.hh"
# define Parent WinUdp
#endif

namespace TBSystem {
    namespace network {
        namespace sockets {
            class Udp : public UnixUdp {
                public:
                    Udp() : Parent() {}
                    virtual ~Udp() {}
            };
        }
    }
}

#endif /* !_UDP_H__ */
