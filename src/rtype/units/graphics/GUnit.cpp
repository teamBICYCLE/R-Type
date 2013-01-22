#include <iostream>
#include "gamestate/GameState.hh"
#include "GUnit.hh"

GUnit::GUnit(int id, const Vector2D& pos, const Vector2D& dir)
	: Unit(id, pos, dir)
  , sf::Drawable()
{
  setId(_id);
}

GUnit::GUnit(void)
	: Unit() , sf::Drawable()
{
}

GUnit::~GUnit(void)
{

}

void GUnit::setAnimationManager(const AnimationM &a)
{
	// nom = _resourceId;
  	_anim.reset((*(a.get()))["resources/sprites/vaisseau.bmp"]->generateAnimInfo());
}

void GUnit::setId(const uint32_t id)
{
	_id = id;
}

void GUnit::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
	sf::Vector2f pos = static_cast<sf::Vector2f>(_pos);

	// THIBAULT
	
	if (_dir.y > 0)
		_anim->setAnimationName("top");
	else if (_dir.y < 0)
		_anim->setAnimationName("bot");
	else
		_anim->setAnimationName("mid");
	
	_anim->startAnimation();
	
	pos.x *= GameState::WINDOW_WIDTH;
	pos.y *= GameState::WINDOW_HEIGHT;
	target.draw(_anim->getSprite(), sf::Transform().translate(pos));
}

Unit *GUnit::clone(void)
{
  	return (new GUnit(*this));
}
