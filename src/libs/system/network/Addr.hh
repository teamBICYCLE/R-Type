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
#ifdef __gnu_linux__
# include <netdb.h>
#elif defined _WIN32
# include <WinSock2.h>
# include <ws2tcpip.h>
#endif

namespace TBSystem {
namespace network {
using ::addrinfo;
class AddrInfo : public IAddrInfo {
public:
    AddrInfo(void * addrinfo);

    virtual ~AddrInfo();

    virtual void *get();

    virtual int size() const;

private:
    addrinfo *  _raw;
};

class Addr : public IAddr {
public:
    Addr();

    Addr(const Addr& other);

    Addr(const std::string & ip, const std::string & port, const std::string & proto);

    Addr(SpecialIp ip, const std::string & port, const std::string & proto);

    virtual ~Addr();

    virtual void set(const std::string & ip, const std::string & port,
                     const std::string & proto);

    virtual void set(SpecialIp ip, const std::string & port,
                     const std::string & proto);

    virtual std::tuple<std::string, std::string, std::string> get() const;

    virtual std::vector<std::shared_ptr<IAddrInfo>> infos() const;

    virtual bool    hasValidAddr() const;

    virtual void    setValid(const void * addr) const;

    virtual int     validSize() const;

    virtual const void*   getValid() const;

    virtual bool  operator==(const IAddr& other) const;

    virtual std::string getIpString() const;

    bool  isDisconnected(void) const;
    void  setDisconnected(bool b);

private:
    SpecialIp   _special;
    std::string _ip;
    std::string _port;
    std::string _proto;

    mutable struct addrinfo*     _infosRes;
    mutable bool        _isValid;
    mutable struct sockaddr_in _valid;
    bool  _disconnected;
};
}
}

#endif /* !_ADDR_H__ */
