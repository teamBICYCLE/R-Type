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

# include <iostream>
# include "Unit.hh"

class Player : public Unit {

public:
    Player(int id, const Vector2D& pos, const Vector2D& dir);
    Player(void);
    virtual ~Player();

    void test(void) const
    {
    	std::cout << ":)" << std::endl;
    }

public:
	Player *clone(void);
};

#endif /* !_PLAYER_H__ */

