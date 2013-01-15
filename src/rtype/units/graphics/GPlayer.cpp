#include <iostream>
#include "GPlayer.hh"

GPlayer::GPlayer(unsigned int id, const Vector2D& pos, const Vector2D& dir)
    : Unit(id, pos, dir)
    , GUnit(id, pos, dir)
    , Player(id, pos, dir)
    , _circle(10.f)
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

GPlayer::~GPlayer(void)
{

}

const sf::Drawable *GPlayer::render(void) const
{
	return &_circle;
}
