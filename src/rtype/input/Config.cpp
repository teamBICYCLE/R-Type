/*
 * -----------------------------------------------------------------------------
 * "THE BEER-WARE LICENSE" (Revision 42):
 * <duplom_t@epitech.eu> wrote this file. As long as you retain this notice you
 * can do whatever you want with this stuff. If we meet some day, and you think
 * this stuff is worth it, you can buy me a beer in return Thomas Duplomb
 * -----------------------------------------------------------------------------
 */

#include "Config.hh"

namespace Input {

Config::Config()
{
}

Config::~Config()
{
}

Config::Config(const Config & other)
  : _top(other._top)
  , _bot(other._bot)
  , _right(other._right)
  , _left(other._left)
  , _fire(other._fire)
{
}

Config::Config(Config && other)
{
  swap(*this, other);
}

Config &    Config::operator=(Config other)
{
  swap(*this, other);
  return *this;
}

void    swap(Config & lhs, Config & rhs)
{
  std::swap(lhs._top, rhs._top);
  std::swap(lhs._bot, rhs._bot);
  std::swap(lhs._right, rhs._right);
  std::swap(lhs._left, rhs._left);
  std::swap(lhs._fire, rhs._fire);
}

Data    Config::getInput() const
{
  Data    ret;

  ret.setTop(sf::Keyboard::isKeyPressed(_top));
  ret.setBot(sf::Keyboard::isKeyPressed(_bot));
  ret.setRight(sf::Keyboard::isKeyPressed(_right));
  ret.setLeft(sf::Keyboard::isKeyPressed(_left));
  ret.setFire(sf::Keyboard::isKeyPressed(_fire));
  ret.setId(_playerId);
  return ret;
}

}
