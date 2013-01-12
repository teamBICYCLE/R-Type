#ifndef		_G_UNIT_HH_
# define	_G_UNIT_HH_

#include <SFML/Graphics.hpp>
#include "units/Unit.hh"

class GUnit : public Unit, public sf::Drawable
{

public:
	GUnit(unsigned int id, const Vector2D& pos, const Vector2D& dir);
	~GUnit(void);

public:
	void draw(sf::RenderTarget &target, sf::RenderStates states) const;
	virtual const sf::Drawable *render(void) const = 0;
};

#endif /*!_G_UNIT_HH_*/
