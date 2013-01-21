/*
 * -----------------------------------------------------------------------------
 * "THE BEER-WARE LICENSE" (Revision 42):
 * <duplom_t@epitech.eu> wrote this file. As long as you retain this notice you
 * can do whatever you want with this stuff. If we meet some day, and you think
 * this stuff is worth it, you can buy me a beer in return Thomas Duplomb
 * -----------------------------------------------------------------------------
 */

#include <iostream>
#include "gamestate/GameState.hh"
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
}

bool  Player::collideWith(const Player& other) const
{
  float dist = _hitboxCenter.distanceSquared(other.getHitboxCenter());

  return dist <= (((_hitboxRadius + other.getHitboxRadius()) / GameState::WINDOW_WIDTH) *
                 ((_hitboxRadius + other.getHitboxRadius()) / GameState::WINDOW_WIDTH));
}

void  Player::move(void)
{
  const float scaledHitboxDiameter = (_hitboxRadius / GameState::WINDOW_WIDTH) * 2;

  Unit::move();
  if (_pos.x < 0) _pos.x = 0;
  if (_pos.x + scaledHitboxDiameter > 1) _pos.x = 1 - scaledHitboxDiameter;
  if (_pos.y < 0) _pos.y = 0;
  if (_pos.y + scaledHitboxDiameter > 1) _pos.y = 1 - scaledHitboxDiameter;
  //std::cout << "Player moved: " << _pos << std::endl;
  _hitboxCenter = _pos;
}

Unit *Player::clone(void)
{
	return (new Player(*this));
}
