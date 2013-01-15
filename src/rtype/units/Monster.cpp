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

Monster *Monster::clone(void)
{
	return (new Monster(*this));
}