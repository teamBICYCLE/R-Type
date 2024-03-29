#ifndef		_MISSILE_HH_
# define	_MISSILE_HH_

# include "units/Monster.hh"

class Missile : public Monster
{

public:
	Missile(int id, const Vector2D &, const Vector2D &);
	Missile(void);
	virtual ~Missile(void);

public:
	Unit *clone(void);
  virtual bool  isOffScreen(const float screenWidth) const;

public:
  void  setMissileMoveStyle(void);

private:
  const float MISSILE_SPEED;
};

#endif
