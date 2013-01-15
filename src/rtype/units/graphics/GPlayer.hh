#ifndef		_G_PLAYER_HH_
# define	_G_PLAYER_HH_

#include <SFML/Graphics.hpp>
#include "units/Player.hh"
#include "GUnit.hh"

class GPlayer : public GUnit, public Player
{
public:
	GPlayer(unsigned int id, const Vector2D& pos, const Vector2D& dir);
	~GPlayer(void);

public:
	const sf::Drawable *render(void) const;

private:
	sf::CircleShape _circle;
	
};

#endif	/*!_G_PLAYER_HH_*/
