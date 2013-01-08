#include "Input.hh"

Input::Input()
    : _packet(0)
{
}

Input::Input(int packet)
    : _packet(packet)
{
}

Input::~Input()
{
}

Input::Input(const Input& other)
    : _packet(other._packet)
{
}

Input::Input(Input&& other)
{
    swap(*this, other);
}

Input&  Input::operator=(Input other)
{
    swap(*this, other);
    return *this;
}

void    swap(Input& lhs, Input& rhs)
{
    std::swap(lhs._packet, rhs._packet);
}

int         Input::getId() const
{
    return _id;
}

Vector2D    Input::getVector() const
{
    Vector2D v;

    if (_top)   v.y -= 1;
    if (_bot)   v.y += 1;
    if (_left)  v.x -= 1;
    if (_right) v.x += 1;
    v.normalize();
    return v;
}

bool        Input::isFiring() const
{
    return _fire;
}

unsigned int     Input::getPacket(void) const
{
    return _packet;
}

void    Input::setId(int v)
{
    _id = v;
}

void    Input::setTop(bool v)
{
    _top = v;
}

void    Input::setBot(bool v)
{
    _bot = v;
}

void    Input::setLeft(bool v)
{
    _left = v;
}

void    Input::setRight(bool v)
{
    _right = v;
}

void    Input::setFire(bool v)
{
    _fire = v;
}
