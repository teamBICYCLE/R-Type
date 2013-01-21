#include <iostream>
#include "gamestate/GameState.hh"
#include "GUnit.hh"

GUnit::GUnit(int id, const Vector2D& pos, const Vector2D& dir)
	: Unit(id, pos, dir)
  , sf::Drawable()
  , _circle(10.f)
{
  setId(_id);
  toto.addSourceFolder("resources/sprites");
  _anim.reset(toto["resources/sprites/vaisseau.bmp"]->generateAnimInfo());

}

GUnit::GUnit(void)
	: Unit()
  , sf::Drawable()
  , _circle(10.f)
{	
}

GUnit::~GUnit(void)
{

}

void GUnit::setId(const uint32_t id)
{
	_id = id;
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

void GUnit::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
	sf::Vector2f pos = static_cast<sf::Vector2f>(_pos);

	std::cout << "drawing " << _id << std::endl;
	if (_dir.y > 0)
		_anim->setAnimationName("top");
	else if (_dir.y < 0)
		_anim->setAnimationName("bot");
	else
		_anim->setAnimationName("mid");
	
	//_anim->getSprite();
	// _anim->startAnimation();
	
	pos.x *= GameState::WINDOW_WIDTH;
	pos.y *= GameState::WINDOW_HEIGHT;
	target.draw(_circle, sf::Transform().translate(pos));
}

Unit *GUnit::clone(void)
{
  	return (new GUnit(*this));
}
