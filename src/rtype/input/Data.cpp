#include "Data.hh"
#include <stdexcept>
#include <cstring>
#include <system/log/Log.hh>

using namespace TBSystem;

namespace Input {

Data::Data()
    : _packet(0)
    , _id(0)
{
}

Data::Data(int packet)
    : _packet(packet)
    , _id(0)
{
}

Data::~Data()
{
}

Data::Data(const Data& other)
    : _packet(other._packet)
    , _id(other._id)
{
}

Data::Data(Data&& other)
{
    swap(*this, other);
}

Data&  Data::operator=(Data other)
{
    swap(*this, other);
    return *this;
}

void    swap(Data& lhs, Data& rhs)
{
    std::swap(lhs._packet, rhs._packet);
    std::swap(lhs._id, rhs._id);
}

int         Data::getId() const
{
    return _id;
}

Vector2D    Data::getVector() const
{
    Vector2D v;

    if (_top)   v.y -= 1;
    if (_bot)   v.y += 1;
    if (_left)  v.x -= 1;
    if (_right) v.x += 1;
    v.normalize();
    return v;
}

bool        Data::isFiring() const
{
    return _fire == 1;
}

unsigned int     Data::getPacket(void) const
{
    return _packet;
}

void    Data::setId(int v)
{
    _id = v;
}

void    Data::setTop(bool v)
{
    _top = v;
}

void    Data::setBot(bool v)
{
    _bot = v;
}

void    Data::setLeft(bool v)
{
    _left = v;
}

void    Data::setRight(bool v)
{
    _right = v;
}

void    Data::setFire(bool v)
{
    _fire = v;
}

size_t Data::pack(uint8_t *out, size_t outSize) const
{
  communication::Packet packet(communication::Packet::Type::INPUT, _id, 0,
                               reinterpret_cast<const uint8_t*>(&_packet),
                               sizeof(_packet));

   if (outSize < packet.getDataSize()) {
      throw std::overflow_error("Output is too small for the packet to fit");
   }
   std::memcpy(out, packet.getData(), packet.getDataSize());
   return packet.getDataSize();
}

void   Data::unpack(const uint32_t newPacketSequence, const uint8_t* content)
{
  _packet = *reinterpret_cast<const uint32_t*>(content);
  //log::debug << "left: " << _left << " right " << _right << log::endl;
}

}
