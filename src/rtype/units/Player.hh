/*
 * -----------------------------------------------------------------------------
 * "THE BEER-WARE LICENSE" (Revision 42):
 * <duplom_t@epitech.eu> wrote this file. As long as you retain this notice you
 * can do whatever you want with this stuff. If we meet some day, and you think
 * this stuff is worth it, you can buy me a beer in return Thomas Duplomb
 * -----------------------------------------------------------------------------
 */

#ifndef _PLAYER_H__
#define _PLAYER_H__

# include "Unit.hh"

class Player : public virtual Unit
{
public:
  Player(int id, const Vector2D& pos, const Vector2D& dir);
  Player(void);
  virtual ~Player();

public:
  bool  collideWith(const Player& other) const;
  virtual void  move(void);

public:
  Unit *clone(void);
};

#endif /* !_PLAYER_H__ */

