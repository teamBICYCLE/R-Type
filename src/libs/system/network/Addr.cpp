/*
 * -----------------------------------------------------------------------------
 * "THE BEER-WARE LICENSE" (Revision 42):
 * <duplom_t@epitech.eu> wrote this file. As long as you retain this notice you
 * can do whatever you want with this stuff. If we meet some day, and you think
 * this stuff is worth it, you can buy me a beer in return Thomas Duplomb
 * -----------------------------------------------------------------------------
 */

#include "Addr.hh"
#include <stdexcept>
#include <iostream>
#include <string.h>
#include <system/log/Log.hh>
#include "socketInit.hh"
#ifdef __gnu_linux__
# include <sys/types.h>
# include <sys/socket.h>
# include <netinet/ip.h>
# include <arpa/inet.h>
# include <netdb.h>
#elif _WIN32

#endif

namespace TBSystem {
namespace network {
/*
 * AddrInfo implementation
 */

AddrInfo::AddrInfo(void * addrinfo)
  : _raw(static_cast< struct addrinfo * >(addrinfo))
{
}

AddrInfo::~AddrInfo()
{}

void*   AddrInfo::get()
{
  return _raw->ai_addr;
}

int    AddrInfo::size() const
{
  return _raw->ai_addrlen;
}

/*
 * Addr implementation
 */
Addr::Addr()
  : _special(static_cast<SpecialIp>(-1))
  , _infosRes(nullptr)
  , _isValid(false)
  , _disconnected(false)
{
  socketInit();
}

Addr::~Addr() {
  //if (_infosRes) freeaddrinfo(_infosRes);
}

Addr::Addr(const Addr& other)
  : _special(other._special)
  , _ip(other._ip)
  , _port(other._port)
  , _proto(other._proto)
  , _infosRes(other._infosRes)
  , _isValid(other._isValid)
  , _disconnected(other._disconnected)
{
  memcpy(&_valid, &other._valid, sizeof(sockaddr_in));
}

Addr::Addr(const std::string & ip, const std::string & port,
           const std::string & proto)
  : _special(static_cast<SpecialIp>(-1))
  , _infosRes(nullptr)
  , _isValid(false)
  , _disconnected(false)
{
  set(ip, port, proto);
}

Addr::Addr(SpecialIp ip, const std::string & port,
           const std::string & proto)
  : _special(static_cast<SpecialIp>(-1))
  , _infosRes(nullptr)
  , _isValid(false)
  , _disconnected(false)
{
  set(ip, port, proto);
}


void Addr::set(SpecialIp ip, const std::string & port,
               const std::string & proto)
{
  _special = ip;
  _port = port;
  _proto = proto;
  _isValid = false;
}

void Addr::set(const std::string & ip, const std::string & port,
               const std::string & proto)
{
  _special = static_cast<SpecialIp>(-1);
  _ip = ip;
  _port = port;
  _proto = proto;
  _isValid = false;
}

std::tuple<std::string, std::string, std::string> Addr::get() const
{
  switch (_special) {
    case SI_ADDR_ANY:
      return std::make_tuple("ADDR_ANY", _port, _proto);
      break;
    case SI_ADDR_BROADCAST:
      return std::make_tuple("ADDR_BROADCAST", _port, _proto);
      break;
    default:
      return std::make_tuple(_ip, _port, _proto);
      break;
  }
}

std::vector<std::shared_ptr<IAddrInfo>> Addr::infos() const
{
  // Free _infosRes from previous call
  if (_infosRes) freeaddrinfo(_infosRes); _infosRes = nullptr;

  // Set the hint structure if ADDR_ANY is needed (suitable for bind)
  struct addrinfo hint;
  const char * node = _ip.c_str();

  memset(&hint, 0, sizeof(hint));
  if (_special == SI_ADDR_ANY) {
    hint.ai_flags = AI_PASSIVE;
    node = nullptr;
  }
  protoent *protoent = getprotobyname(_proto.c_str());

  if (!protoent) {
    throw std::runtime_error("`" + _proto + "` No such protocol");
  }
  hint.ai_protocol = protoent->p_proto;
  hint.ai_family = AF_UNSPEC;

  // Request addrinfo and prepare return vector
  std::vector<std::shared_ptr<IAddrInfo>> ret;
  int err;

  if ((err = getaddrinfo(node, _port.c_str(), &hint, &_infosRes))) {
    throw std::runtime_error(gai_strerror(err));
  }
  for (addrinfo *res = _infosRes; res != nullptr; res = res->ai_next) {
    ret.push_back(std::shared_ptr<IAddrInfo>(new AddrInfo(res)));
  }
  if (ret.size() < 1) throw std::runtime_error("Could not resolve Addr");
  return ret;
}

bool    Addr::hasValidAddr() const {
  return _isValid;
}

void    Addr::setValid(const void * addr) const {
  if (!_isValid)
    memcpy(static_cast<void*>(&_valid), addr, sizeof(_valid));
  _isValid = true;
}

int     Addr::validSize() const {
  return sizeof(sockaddr_in);
}

const void *  Addr::getValid() const {
  return &_valid;
}

bool  Addr::operator==(const IAddr& other) const
{
  return memcmp(&_valid, other.getValid(), sizeof(_valid)) == 0;
}

std::string Addr::getIpString() const
{
  if (!_isValid) throw std::runtime_error("unrecognized addr");
  return inet_ntoa(_valid.sin_addr);
}

bool  Addr::isDisconnected(void) const
{
  return _disconnected;
}

void  Addr::setDisconnected(bool b)
{
  _disconnected = b;
}

}
}
