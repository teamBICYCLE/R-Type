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

size_t  AUnit::pack(uint8_t *out, size_t outSize) const
{
    UnitPacket_u            packetContent;

    packetContent.id = _id;
    packetContent.x = _pos.x;
    packetContent.y = _pos.y;
    packetContent.dx = _dir.x;
    packetContent.dy = _dir.y;

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
    _pos.x = content->x;
    _pos.y = content->y;
    _dir.x = content->dx;
    _dir.y = content->dy;
}

std::ostream&   operator<<(std::ostream& stream, const AUnit& unit)
{
    stream << "Unit #" << unit._id << " position: " << unit._pos.x << "-" << unit._pos.y;
	return stream;
}
