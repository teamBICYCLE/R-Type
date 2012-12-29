/*
 * -----------------------------------------------------------------------------
 * "THE BEER-WARE LICENSE" (Revision 42):
 * <duplom_t@epitech.eu> wrote this file. As long as you retain this notice you
 * can do whatever you want with this stuff. If we meet some day, and you think
 * this stuff is worth it, you can buy me a beer in return Thomas Duplomb
 * -----------------------------------------------------------------------------
 */

#ifndef _ADDR_H__
#define _ADDR_H__

#include "IAddr.hh"
#include <string>

#define _linux_LOL__
#ifdef _linux_LOL__
#include <sys/socket.h>
#include <netdb.h>
#elif WIN32

#endif

namespace network {
class Addr : public IAddr {
public:
    Addr();

    Addr(const std::string & ip, short port);

    virtual ~Addr();

    virtual void set(const std::string & ip, short port);

    virtual std::pair<std::string, short> get() const;

    virtual const void *raw() const;

    virtual void *raw();

    virtual int rawSize() const;

private:
    std::string _ip;
    short       _port;
    sockaddr    _raw;
};
}

#endif /* !_ADDR_H__ */
