#include <iostream>
#include <system/log/Log.hh>
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
	std::string path = "player";
	if (_resourceId > 3)
		path = std::to_string(_resourceId);

	try {
		_anim.reset((*(m.get()))["resources/sprites/" + path + ".bmp"]->generateAnimInfo());
	} catch (const std::invalid_argument &e) {
		TBSystem::log::warn << e.what() << TBSystem::log::endl;
	}
}

void GUnit::setId(const uint32_t id)
{
	_id = id;
}

bool GUnit::playerAnimation(void) const
{
	bool valid = false;
	std::string path = std::to_string(_id);
	if (_dir.y > 0)
		valid = _anim->setAnimationName("bot" + path); // recuperer l'id
	else if (_dir.y < 0)
		valid = _anim->setAnimationName("top" + path);
	else
		valid = _anim->setAnimationName("mid" + path);
	return valid;
}

void GUnit::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
	(void)states;
	sf::Vector2f pos = static_cast<sf::Vector2f>(_pos);
	bool valid = false;

	_anim->setPlayAnimNumber(-1);
	if (isDead()) {
		valid = _anim->setAnimationName("die");
		_anim->setPlayAnimNumber(1);
	}
	else if (_resourceId < PLAYERS_ID)
		valid = GUnit::playerAnimation();
	else if (_resourceId == MISSILE_ID)
		valid = _anim->setAnimationName("mid");
	else
		valid = _anim->setAnimationName("mid");

	if (valid)
	{
		sf::Sprite sprite = _anim->getSprite();
		
		pos.x *= GameState::WINDOW_WIDTH;
		pos.y *= GameState::WINDOW_HEIGHT;

		//target.draw(_circle, sf::Transform().translate(pos));
		pos.x -= (sprite.getGlobalBounds().width / 2);
		pos.y -= (sprite.getGlobalBounds().height / 2);  
		target.draw(_anim->getSprite(), sf::Transform().translate(pos));
	}
}

Unit *GUnit::clone(void)
{
  	return (new GUnit(*this));
}

std::shared_ptr<Sprite::AnimationInfos> GUnit::getAnimInfo(void)
{
	return (_anim);
}