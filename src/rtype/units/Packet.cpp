#include <cstring>
#include <utility>
#include "Packet.hh"

namespace network_packet {

Packet::Packet(Type type, uint8_t *content, size_t contentSize)
    : _type(type)
    , _dataSize(sizeof(_type) + contentSize)
{
    std::memcpy(_data, &type, sizeof(_type));
    std::memcpy(_data + sizeof(_type), content, contentSize);
}

//dataFromNetwork represents a network packet, with the type first and then the data
Packet::Packet(uint8_t *dataFromNetwork, size_t size)
{
    _dataSize = size;
    std::memcpy(&_type, dataFromNetwork, sizeof(_type));
    dataFromNetwork += sizeof(_type);
    size -= sizeof(_type);
    std::memcpy(_data, &_type, sizeof(_type));
    std::memcpy(_data + sizeof(_type), dataFromNetwork, size);
}

Packet::~Packet()
{
}

Packet::Packet(const Packet& other)
    : _type(other._type)
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
    std::swap(lhs._type, rhs._type);
    std::swap(lhs._data, rhs._data);
    std::swap(lhs._dataSize, rhs._dataSize);
}

Type    Packet::getType(void) const
{
    return _type;
}

const uint8_t *Packet::getContent(void) const
{
    return _data + sizeof(_type);
}

size_t  Packet::getContentSize(void) const
{
    return _dataSize - sizeof(_type);
}

const uint8_t *Packet::getData(void) const
{
    return _data;
}

size_t  Packet::getDataSize(void) const
{
    return _dataSize;
}

}
