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

class IAddr {
public:
    virtual ~IAddr() {}

    virtual void set(const std::string & ip, short port) = 0;

    virtual std::pair<std::string, short> get() const = 0;

    virtual void *raw() = 0;

    virtual const void *raw() const = 0;

    virtual int rawSize() const = 0;
};

#endif /* !_IADDR_H__ */
