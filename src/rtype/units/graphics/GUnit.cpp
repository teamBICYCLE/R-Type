#include <iostream>
#include "gamestate/GameState.hh"
#include "GUnit.hh"

GUnit::GUnit(int id, const Vector2D& pos, const Vector2D& dir)
	: Unit(id, pos, dir)
  	, sf::Drawable()
  	, _circle(10)
{
  setId(_id);
}

GUnit::GUnit(void)
	: Unit()
	, sf::Drawable()
	, _circle(10)
{
}

GUnit::~GUnit(void)
{

}

void GUnit::setAnimationManager(const AnimationM &m)
{
	// player
	std::string path = "player";
	if (_resourceId > 3)
		path = std::to_string(_resourceId);

	//std::cout << "----> img ---> " << "resources/sprites/" + path + ".bmp" << std::endl;
	_anim.reset((*(m.get()))["resources/sprites/" + path + ".bmp"]->generateAnimInfo());
	// throw ---^
	//_currentResourceId = _resourceId;
  	//_anim.reset((*(a.get()))["resources/sprites/vaisseau.bmp"]->generateAnimInfo());
}

void GUnit::setId(const uint32_t id)
{
	_id = id;
}

bool GUnit::playerAnimation(void) const
{
	bool valid = false;
	if (_dir.y > 0)
		valid = _anim->setAnimationName("bot"); // recuperer l'id
	else if (_dir.y < 0)
		valid = _anim->setAnimationName("top");
	else
		valid = _anim->setAnimationName("mid");	
	return valid;
}

void GUnit::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
	(void)states;
	sf::Vector2f pos = static_cast<sf::Vector2f>(_pos);
	bool valid = false;

	if (_resourceId < PLAYERS_ID)
		valid = GUnit::playerAnimation();
	if (_resourceId == MISSILE_ID)
		valid = _anim->setAnimationName("mid3");
	else
		valid = _anim->setAnimationName("mid");

	if (valid)
	{
		sf::Sprite sprite = _anim->getSprite();
		
		pos.x *= GameState::WINDOW_WIDTH;
		pos.y *= GameState::WINDOW_HEIGHT;

		//target.draw(_circle, sf::Transform().translate(pos));
		pos.x -= (sprite.getGlobalBounds().width / 2);
		pos.y -= (sprite.getGlobalBounds().height / 4);  
		target.draw(_anim->getSprite(), sf::Transform().translate(pos));
	}
}

Unit *GUnit::clone(void)
{
  	return (new GUnit(*this));
}
