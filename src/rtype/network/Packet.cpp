#include <cstring>
#include <utility>
#include "Packet.hh"
#include <system/log/Log.hh>

using namespace TBSystem;

namespace communication {

Packet::Packet(Type type, uint32_t id, const uint8_t *content, size_t contentSize)
  : _dataSize(sizeof(_header) + contentSize)
{
  static uint32_t packetSequence = 1;

  _header.isReliable = false;
  _header.sequence = packetSequence;
  packetSequence++;
  _header.type = type;
  _header.id = id;
  std::memcpy(_data, &_header, sizeof(_header));
  std::memcpy(_data + sizeof(_header), content, contentSize);
}

//dataFromNetwork represents a network packet, with the type first and then the data
Packet::Packet(const uint8_t *dataFromNetwork, size_t size)
{
  _dataSize = size;
  std::memcpy(&_header, dataFromNetwork, sizeof(_header));
  std::memcpy(_data, dataFromNetwork, size);
}

Packet::~Packet()
{
}

Packet::Packet(const Packet& other)
  : _header(other._header)
  , _dataSize(other._dataSize)
{
  std::memcpy(_data, other._data, other._dataSize);
}

Packet::Packet(Packet&& other)
{
  swap(*this, other);
}

Packet&     Packet::operator=(Packet other)
{
  swap(*this, other);
  return *this;
}

void    swap(Packet& lhs, Packet& rhs)
{
  std::swap(lhs._header, rhs._header);
  std::swap(lhs._data, rhs._data);
  std::swap(lhs._dataSize, rhs._dataSize);
}

bool    Packet::isReliable(void) const
{
  return _header.isReliable;
}

uint32_t    Packet::getSequence(void) const
{
  return _header.sequence;
}

Packet::Type    Packet::getType(void) const
{
  return _header.type;
}

uint32_t    Packet::getId(void) const
{
  return _header.id;
}

const uint8_t *Packet::getContent(void) const
{
  return _data + sizeof(_header);
}

size_t  Packet::getContentSize(void) const
{
  return _dataSize - sizeof(_header);
}

const uint8_t *Packet::getData(void) const
{
  return _data;
}

size_t  Packet::getDataSize(void) const
{
  return _dataSize;
}

void  Packet::setType(communication::Packet::Type type)
{
  _header.type = type;
  rewriteHeader();
}

void  Packet::setReliable(bool b)
{
  _header.isReliable = b;
  rewriteHeader();
}

void  Packet::rewriteHeader(void)
{
  std::memcpy(_data, &_header, sizeof(_header));
}

}
