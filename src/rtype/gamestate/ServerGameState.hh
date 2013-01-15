/*
 * -----------------------------------------------------------------------------
 * "THE BEER-WARE LICENSE" (Revision 42):
 * <duplom_t@epitech.eu> wrote this file. As long as you retain this notice you
 * can do whatever you want with this stuff. If we meet some day, and you think
 * this stuff is worth it, you can buy me a beer in return. Thomas Duplomb
 * -----------------------------------------------------------------------------
 */

#ifndef _SERVERGAMESTATE_H__
#define _SERVERGAMESTATE_H__

#include "GameState.hh"

class ServerGameState : public GameState {
public:
  ServerGameState(const std::vector<std::shared_ptr<Player>>& v);
  virtual ~ServerGameState();

public:
  void  updateWithInput    (const communication::Packet& packet);
  void  requireMonsters(const Vector2D &left, const Vector2D &right);

private:
	const PatternManager _pm;
};

#endif /* !_SERVERGAMESTATE_H__ */

