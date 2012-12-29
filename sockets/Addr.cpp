/*
 * -----------------------------------------------------------------------------
 * "THE BEER-WARE LICENSE" (Revision 42):
 * <duplom_t@epitech.eu> wrote this file. As long as you retain this notice you
 * can do whatever you want with this stuff. If we meet some day, and you think
 * this stuff is worth it, you can buy me a beer in return Thomas Duplomb
 * -----------------------------------------------------------------------------
 */

#include "Addr.hh"

namespace network {
    Addr::Addr()
    {}

    Addr::Addr(const std::string & ip, short port)
    {
        set(ip, port);
    }

    Addr::~Addr() {}

    void Addr::set(const std::string & ip, short port)
    {
        _ip = ip;
        _port = port;
    }

    std::pair<std::string, short> Addr::get() const
    {
        return std::make_pair(_ip, _port);
    }

    void *Addr::raw()
    {
        return Addr::raw();
    }

    const void* Addr::raw() const {
        return &_raw;
    }

    int Addr::rawSize() const
    {
        return sizeof(_raw);
    }
}
