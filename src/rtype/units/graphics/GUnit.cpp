#include <iostream>
#include "gamestate/GameState.hh"
#include "GUnit.hh"

GUnit::GUnit(int id, const Vector2D& pos, const Vector2D& dir)
	: Unit(id, pos, dir)
  	, sf::Drawable()
{
	switch (_id) {
		case 0 :
			_circle.setFillColor(sf::Color::Green);
			break;
		case 1 :
			_circle.setFillColor(sf::Color::Red);
			break;
		case 2 :
			_circle.setFillColor(sf::Color::Blue);
			break;
		case 3 :
			_circle.setFillColor(sf::Color::Yellow);
			break;
	}
}

GUnit::GUnit(void)
	: Unit()
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
