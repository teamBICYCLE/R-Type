/*
 * -----------------------------------------------------------------------------
 * "THE BEER-WARE LICENSE" (Revision 42):
 * <duplom_t@epitech.eu> wrote this file. As long as you retain this notice you
 * can do whatever you want with this stuff. If we meet some day, and you think
 * this stuff is worth it, you can buy me a beer in return Thomas Duplomb
 * -----------------------------------------------------------------------------
 */

#ifndef _IADDR_H__
#define _IADDR_H__

#include <string>
#include <tuple>
#include <vector>
#include <memory>

namespace TBSystem {
namespace network {
enum SpecialIp {
      SI_ADDR_ANY = 0
    , SI_ADDR_BROADCAST
};

class IAddrInfo {
public:
    virtual ~IAddrInfo() {}

    virtual void* get() = 0;

    virtual int size() const = 0;
};

class IAddr {
public:
    virtual ~IAddr() {}

    virtual void set(SpecialIp ip, const std::string & port,
                     const std::string & proto) = 0;

    virtual void set(const std::string & ip, const std::string & port,
                     const std::string & proto) = 0;

    virtual std::tuple<std::string, std::string, std::string> get() const = 0;

    virtual std::vector<std::shared_ptr<IAddrInfo>> infos() const = 0;

    virtual bool    hasValidAddr() const = 0;

    virtual void    setValid(const void * addr) const = 0;

    virtual int    validSize() const = 0;

    virtual const void*   getValid() const = 0;

    virtual bool  operator==(const IAddr& other) const = 0;

};
}
}

#endif /* !_IADDR_H__ */
