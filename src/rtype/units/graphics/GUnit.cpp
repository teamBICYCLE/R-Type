#include <iostream>
#include "gamestate/GameState.hh"
#include "GUnit.hh"

GUnit::GUnit(unsigned int id, const Vector2D& pos, const Vector2D& dir)
	: Unit(id, pos, dir)
  , sf::Drawable()
{
}

GUnit::~GUnit(void)
{

}

void GUnit::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
	sf::Vector2f pos = static_cast<sf::Vector2f>(_pos);

	//tmp
	pos.x *= GameState::WINDOW_WIDTH;
	pos.y *= GameState::WINDOW_HEIGHT;
	target.draw(*(render()), sf::Transform().translate(pos));
}
