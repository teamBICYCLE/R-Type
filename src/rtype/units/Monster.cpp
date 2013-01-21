#include "Monster.hh"

Monster::Monster(int id, const Vector2D& pos, const Vector2D& dir)
    : Unit(id, pos, dir)
{
}

Monster::Monster(void)
	: Unit()
{	
}

Monster::~Monster(void)
{

}

void Monster::setMoveStyle(const moveStyle &m)
{
	_movefct = m;
}

Monster *Monster::clone(void)
{
	return (new Monster(*this));
}

void	Monster::move(void)
{
	_dir = _movefct(_pos);
	//std::cout << _dir << std::endl;
	Unit::move();
}