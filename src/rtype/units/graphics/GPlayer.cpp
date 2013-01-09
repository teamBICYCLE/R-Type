#include <iostream>
#include "GPlayer.hh"

GPlayer::GPlayer(unsigned int id, const Vector2D& pos, const Vector2D& dir)
	: GUnit(id, pos, dir), _circle(10.f)
{
	_circle.setFillColor(sf::Color::Green);
	_circle.setPosition(20, 20);
}

GPlayer::~GPlayer(void)
{

}

const sf::Drawable *GPlayer::render(void) const
{
	return &_circle;
}