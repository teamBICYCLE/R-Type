/*
 * -----------------------------------------------------------------------------
 * "THE BEER-WARE LICENSE" (Revision 42):
 * <duplom_t@epitech.eu> wrote this file. As long as you retain this notice you
 * can do whatever you want with this stuff. If we meet some day, and you think
 * this stuff is worth it, you can buy me a beer in return Thomas Duplomb
 * -----------------------------------------------------------------------------
 */
#ifndef _TCP_H__
#define _TCP_H__

#ifdef __gnu_linux__
# include "UnixTcp.hh"
# define Parent UnixTcp
#elif defined _WIN32
# include "WinTcp.hh"
# define Parent WinTcp
#endif

namespace TBSystem {
    namespace network {
        namespace sockets {
            class Tcp : public UnixTcp {
                public:
                    Tcp() : Parent() {}

                    explicit Tcp(int socketDescriptor)
                    : Parent(socketDescriptor)
                    {}

                    virtual ~Tcp() {}
            };

        }
    }
}

#endif /* !_TCP_H__ */
