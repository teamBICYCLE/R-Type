#include <iostream>
#include "GUnit.hh"

GUnit::GUnit(unsigned int id, const Vector2D& pos, const Vector2D& dir)
	: AUnit(id, pos, dir), sf::Drawable()
{
	std::cout << "New GUnit !" << std::endl;
}

GUnit::~GUnit(void)
{

}

void GUnit::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
	std::cout << "Draw !" << std::endl;
	target.draw(*(render()), states);
		
}