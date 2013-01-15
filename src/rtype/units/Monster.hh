#ifndef		_MONSTER_HH_
# define	_MONSTER_HH_

# include "Unit.hh"

class Monster : public virtual Unit
{

public:
	Monster(int id, const Vector2D &, const Vector2D &);
	Monster(void);
	virtual ~Monster(void);

public:
	Monster *clone(void);
};

#endif /*!_MONSTER_HH_*/