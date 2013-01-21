#ifndef		_MONSTER_HH_
# define	_MONSTER_HH_

# include <functional>
# include "Unit.hh"

typedef std::function<const Vector2D (const Vector2D &)> moveStyle;

class Monster : public virtual Unit
{

public:
	Monster(int id, const Vector2D &, const Vector2D &);
	Monster(void);
	virtual ~Monster(void);

public:
	void    move(void);
	void 	setMoveStyle(const moveStyle &);

public:
	Monster *clone(void);

private:
	moveStyle _movefct;
};

#endif /*!_MONSTER_HH_*/