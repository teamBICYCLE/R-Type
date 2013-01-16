/*
 * -----------------------------------------------------------------------------
 * "THE BEER-WARE LICENSE" (Revision 42):
 * <duplom_t@epitech.eu> wrote this file. As long as you retain this notice you
 * can do whatever you want with this stuff. If we meet some day, and you think
 * this stuff is worth it, you can buy me a beer in return. Thomas Duplomb
 * -----------------------------------------------------------------------------
 */

#ifndef _INETWORKSERIALIZABLE_H__
#define _INETWORKSERIALIZABLE_H__

class INetworkSerializable {
public:
  virtual ~INetworkSerializable() {}

  virtual std::string toString() const = 0;
};

#endif /* !_INETWORKSERIALIZABLE_H__ */
