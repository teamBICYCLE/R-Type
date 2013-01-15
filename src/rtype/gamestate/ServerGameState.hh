#ifndef		_SERVERGAMESTATE_H__
# define	_SERVERGAMESTATE_H__

# include "GameState.hh"
# include "PatternManager.hh"	

class ServerGameState : public GameState {
public:
  ServerGameState(const std::vector<std::shared_ptr<Player>>& v);
  virtual ~ServerGameState();

public:
  void  updateWithInput    (const communication::Packet& packet);
  void  requireMonsters(const Vector2D &left, const Vector2D &right);

private:
	// const PatternManager _pm;
};

#endif /* !_SERVERGAMESTATE_H__ */

