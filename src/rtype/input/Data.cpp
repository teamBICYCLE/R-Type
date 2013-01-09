#include "Data.hh"

namespace Input {
Data::Data()
    : _packet(0)
{
}

Data::Data(int packet)
    : _packet(packet)
{
}

Data::~Data()
{
}

Data::Data(const Data& other)
    : _packet(other._packet)
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
}
