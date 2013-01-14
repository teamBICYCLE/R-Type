/*
 * -----------------------------------------------------------------------------
 * "THE BEER-WARE LICENSE" (Revision 42):
 * <duplom_t@epitech.eu> wrote this file. As long as you retain this notice you
 * can do whatever you want with this stuff. If we meet some day, and you think
 * this stuff is worth it, you can buy me a beer in return Thomas Duplomb
 * -----------------------------------------------------------------------------
 */

#include <iostream>
#include "Player.hh"

Player::Player(int id, const Vector2D& pos, const Vector2D& dir)
    : Unit(id, pos, dir)
{
}

Player::Player(void)
	: Unit()
{	
}

Player::~Player()
{
	std::cout << "Player delete " << this << std::endl;
}

Player *Player::clone(void)
{
	return (new Player(*this));
}