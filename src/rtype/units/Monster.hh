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
	virtual void    move(void);
	void 	setMoveStyle(const moveStyle &);
	bool 	isBoss(void);
	void    setBoss(bool v);
  	virtual bool  isOffScreen(const float screenWidth) const;

public:
	Unit *clone(void);

protected:
	moveStyle _movefct;
	bool      _boss;
};

#endif /*!_MONSTER_HH_*/
