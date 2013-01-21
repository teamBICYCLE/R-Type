#include "Missile.hh"

Missile::Missile(int id, const Vector2D& pos, const Vector2D& dir)
    : Monster(id, pos, dir)
{
}

Missile::Missile(void)
	: Monster()
{	
}

Missile::~Missile(void)
{

}

Missile *Missile::clone(void)
{
	return (new Missile(*this));
}
