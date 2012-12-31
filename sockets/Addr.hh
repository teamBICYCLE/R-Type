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
#include "crossplateform_utils.h"
#ifdef __gnu_linux__
# include <netdb.h>
#endif

namespace network {
using ::addrinfo;
class AddrInfo : public IAddrInfo {
public:
    AddrInfo(void * addrinfo);

    virtual ~AddrInfo();

    virtual void *get();

    virtual int size() const;

private:
    CROSSPLATEFORM(addrinfo, win) *_raw;
};

class Addr : public IAddr {
public:
    Addr();

    Addr(const std::string & ip, const std::string & port, const std::string & proto);

    Addr(SpecialIp ip, const std::string & port, const std::string & proto);

    virtual ~Addr();

    virtual void set(const std::string & ip, const std::string & port,
                     const std::string & proto);

    virtual void set(SpecialIp ip, const std::string & port,
                     const std::string & proto);

    virtual std::tuple<std::string, std::string, std::string> get() const;

    virtual std::vector<std::auto_ptr<IAddrInfo>> infos() const;

private:
    SpecialIp   _special;
    std::string _ip;
    std::string _port;
    std::string _proto;
    mutable addrinfo *_infosRes;
};
}

#endif /* !_ADDR_H__ */
