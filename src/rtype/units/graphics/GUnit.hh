#ifndef		_G_UNIT_HH_
# define	_G_UNIT_HH_

# include <SFML/Graphics.hpp>
# include <memory>
# include "units/Unit.hh"
# include "sprites/AnimationInfos.hh"
# include "sprites/AnimationManager.hh"

# define PLAYERS_ID 4 
# define MISSILE_ID 5

typedef std::shared_ptr<Sprite::AnimationManager> AnimationM;

class GUnit : public virtual Unit, public sf::Drawable
{
public:
	GUnit(int id, const Vector2D& pos, const Vector2D& dir);
	GUnit(void);
	virtual ~GUnit(void);

public:
  virtual void    setId(const uint32_t id);
  void	setAnimationManager(const AnimationM &);
  Unit	  *clone(void);
 std::shared_ptr<Sprite::AnimationInfos> getAnimInfo(void);

public:
	virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const;
	bool playerAnimation(void) const;

private:
	void switchSprite(void);

private:
	sf::CircleShape _circle;
	std::shared_ptr<Sprite::AnimationInfos> _anim;
	unsigned int _currentResourceId;
};

#endif /*!_G_UNIT_HH_*/
