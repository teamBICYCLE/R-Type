/*
 * -----------------------------------------------------------------------------
 * "THE BEER-WARE LICENSE" (Revision 42):
 * <duplom_t@epitech.eu> wrote this file. As long as you retain this notice you
 * can do whatever you want with this stuff. If we meet some day, and you think
 * this stuff is worth it, you can buy me a beer in return. Thomas Duplomb
 * -----------------------------------------------------------------------------
 */

Room::Room(const std::string& infos)
{
  std::stringstream ss(infos);

  ss >> _id;
  ss >> _players;
  ss >> _maxplayers;
}

Room::~Room()
{
}

int Room::getId()         const
{
  return _id;
}

int Room::getPlayers()    const
{
  return _players;
}

int Room::getMaxPlayers() const
{
  return _maxplayers;
}