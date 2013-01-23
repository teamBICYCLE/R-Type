#include "Missile.hh"

Missile::Missile(int id, const Vector2D& pos, const Vector2D& dir)
  : Monster(id, pos, dir)
  , MISSILE_SPEED(100.f)
  //, _resourceId(5)
{
  setMissileMoveStyle();
  Unit::setResourceId(5);
}

Missile::Missile(void)
	: Monster()
  , MISSILE_SPEED(100.f)
  //, _resourceId(5)
{	
  setMissileMoveStyle();
  Unit::setResourceId(5);
}

Missile::~Missile(void)
{
}

Missile *Missile::clone(void)
{
	return (new Missile(*this));
}

void  Missile::setMissileMoveStyle(void)
{
  _movefct = [this](const Vector2D &pos) -> Vector2D {
    Vector2D v;

    (void)pos;
    v.x += (1.f / MISSILE_SPEED);
    //v.y += (1.f / MISSILE_SPEED);
    return v;
  };
}

bool  Missile::isOffScreen(const float screenWidth) const
{
  if (Monster::isOffScreen(screenWidth) == true ||
      _pos.x - (_hitboxRadius / screenWidth) >= 1.f)
    return true;
  return false;
}
