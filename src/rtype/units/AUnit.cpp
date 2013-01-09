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

void    AUnit::move(void)
{
    _pos += _dir;
}

void    AUnit::setDirection(const Vector2D& dir)
{
    _dir = dir;
}

std::ostream&   operator<<(std::ostream& stream, const AUnit& unit)
{
    stream << "Unit #" << unit._id << " position: " << unit._pos.x << "-" << unit._pos.y;
	return stream;
}
