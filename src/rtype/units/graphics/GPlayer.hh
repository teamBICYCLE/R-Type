#ifndef		_G_PLAYER_HH_
# define	_G_PLAYER_HH_

#include <memory>
#include <SFML/Graphics.hpp>
#include "units/Player.hh"
#include "sprites/AnimationInfos.hh"
#include "sprites/AnimationManager.hh"
#include "GUnit.hh"

class GPlayer : public GUnit, public Player
{
public:
	GPlayer(unsigned int id, const Vector2D& pos, const Vector2D& dir);
	GPlayer();
	virtual ~GPlayer(void);

public:
	using Player::move;
	virtual const sf::Drawable *render(void) const;
	GPlayer *clone(void);

public:
	void setId(const uint32_t id);

private:
	sf::CircleShape _circle;
	std::shared_ptr<Sprite::AnimationInfos> _anim;
	Sprite::AnimationManager toto;
};

#endif	/*!_G_PLAYER_HH_*/
