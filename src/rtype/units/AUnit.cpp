#include <cstring>
#include <stdexcept>
#include "AUnit.hh"

AUnit::AUnit(int id, const Vector2D& pos, const Vector2D& dir)
    : _id(id)
    , _pos(pos)
    , _dir(dir)
{
}

AUnit::AUnit(const AUnit& other)
    : _id(other._id)
    , _pos(other._pos)
    , _dir(other._dir)
{
}

AUnit::~AUnit()
{
}

AUnit::AUnit(AUnit&& other)
{
    swap(*this, other);
}

AUnit&  AUnit::operator=(AUnit other)
{
    swap(*this, other);
    return *this;
}

void    swap(AUnit& lhs, AUnit& rhs)
{
    std::swap(lhs._id, rhs._id);
    std::swap(lhs._pos, rhs._pos);
    std::swap(lhs._dir, rhs._dir);
}

int     AUnit::getId(void) const
{
    return _id;
}

const Vector2D& AUnit::getPos(void) const
{
    return _pos;
}

const Vector2D& AUnit::getDir(void) const
{
    return _dir;
}

void    AUnit::move(void)
{
    _pos += _dir;
}

void    AUnit::setDirection(const Vector2D& dir)
{
    _dir = dir;
}

#define TO_SHORT(x) (x * ((uint16_t)-1))
#define FROM_SHORT(x) (x / (float)((uint16_t)-1))

size_t  AUnit::pack(uint8_t *out, size_t outSize) const
{
    UnitPacket_u            packetContent;

    packetContent.id = _id;
    packetContent.x = TO_SHORT(_pos.x);
    packetContent.y = TO_SHORT(_pos.y);
    packetContent.dx = TO_SHORT(_dir.x);
    packetContent.dy = TO_SHORT(_dir.y);

    network_packet::Packet packet(network_packet::Type::POSITION, packetContent.whole, sizeof(packetContent.whole));

    if (outSize < packet.getDataSize())
        throw std::overflow_error("Output is too small for the packet to fit");
    std::memcpy(out, packet.getData(), packet.getDataSize());
    return packet.getDataSize();
}

void    AUnit::update(network_packet::Packet packet)
{
    const UnitPacket_u *content = reinterpret_cast<const UnitPacket_u*>(packet.getContent());

    _id = content->id;
    _pos.x = FROM_SHORT(content->x);
    _pos.y = FROM_SHORT(content->y);
    _dir.x = FROM_SHORT(content->dx);
    _dir.y = FROM_SHORT(content->dy);
}

std::ostream&   operator<<(std::ostream& stream, const AUnit& unit)
{
    stream << "Unit #" << unit._id << " position: " << unit._pos.x << "-" << unit._pos.y;
	return stream;
}
