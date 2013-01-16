#ifndef		_ISHARED_MONSTER_HH_
# define	_ISHARED_MONSTER_HH_

# include   "utilities/Vector2D.hh"

class ISharedMonster
{

public:
	virtual ~ISharedMonster(void) {}
	virtual	const Vector2D &getDirection(const Vector2D &) const = 0;
	virtual void			fire(void) const = 0;
	virtual void			getFireRate(void) const = 0;
};

#endif /*!_ISHARED_MONSTER_HH_*/