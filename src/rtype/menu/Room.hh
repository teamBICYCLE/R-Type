/*
 * -----------------------------------------------------------------------------
 * "THE BEER-WARE LICENSE" (Revision 42):
 * <duplom_t@epitech.eu> wrote this file. As long as you retain this notice you
 * can do whatever you want with this stuff. If we meet some day, and you think
 * this stuff is worth it, you can buy me a beer in return. Thomas Duplomb
 * -----------------------------------------------------------------------------
 */

#ifndef _ROOM_H__
#define _ROOM_H__

# include <string>
# include <sstream>

class Room {
public:
  Room(const std::string& infos);
  ~Room();

  int getId()         const;
  int getPlayers()    const;
  int getMaxPlayers() const;

private:
  int _id;
  int _players;
  int _maxplayers;
};

#endif /* !_ROOM_H__ */
