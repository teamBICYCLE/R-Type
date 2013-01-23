#include "gamestate/GameState.hh"
#include "Monster.hh"

Monster::Monster(int id, const Vector2D& pos, const Vector2D& dir)
    : Unit(id, pos, dir), _boss(false)
{
}

Monster::Monster(void)
	: Unit(), _boss(false)
{	
}

Monster::~Monster(void)
{

}

void Monster::setMoveStyle(const moveStyle &m)
{
	_movefct = m;
}

bool Monster::isBoss(void)
{
	return _boss;
}

void Monster::setBoss(bool v)
{
	_boss = v;
}

Unit *Monster::clone(void)
{
	return (new Monster(*this));
}

void	Monster::move(void)
{
	const float scaledHitboxDiameter = (_hitboxRadius / GameState::WINDOW_WIDTH) * 2;
	_dir = _movefct(_pos);
	Unit::move();
	if (_pos.y < 0) _pos.y = 0;
	if (_pos.y + scaledHitboxDiameter > 1) _pos.y = 1 - scaledHitboxDiameter;
	_hitboxCenter = _pos;
}

bool  Monster::isOffScreen(const float screenWidth) const
{
  if (_pos.x + (_hitboxRadius / screenWidth) <= 0)
    return true;
  return false;
}
