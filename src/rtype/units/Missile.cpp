#include "Missile.hh"

Missile::Missile(int id, const Vector2D& pos, const Vector2D& dir)
  : Monster(id, pos, dir)
  , MISSILE_SPEED(800.f)
{
  _movefct = [this](const Vector2D &pos) {
    Vector2D v;

    (void)pos;
    v.x += (_dir.x / MISSILE_SPEED);
    v.y += (_dir.y / MISSILE_SPEED);
    return v;
  };

}

Missile::Missile(void)
	: Monster()
  , MISSILE_SPEED(800.f)
{	
}

Missile::~Missile(void)
{
}

Missile *Missile::clone(void)
{
	return (new Missile(*this));
}
