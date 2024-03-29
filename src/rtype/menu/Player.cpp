#include "Player.hh"

namespace gooey {
Player::Player(const std::string& infos)
{
  std::stringstream ss(infos);

  ss >> _id;
}

Player::~Player()
{
}

int	Player::getId() const
{
  return _id;
}
}
