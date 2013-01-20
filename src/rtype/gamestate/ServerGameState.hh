#ifndef		_SERVERGAMESTATE_H__
# define	_SERVERGAMESTATE_H__

# include "GameState.hh"
# include "PatternManager.hh"	

class ServerGameState : public GameState {
public:
  ServerGameState(const std::vector<std::shared_ptr<Player>>& v);
  virtual ~ServerGameState();

public:
  void  updateWithInput(const communication::Packet& packet);
  void	updateWorld(void);
  void  requireMonsters(const Vector2D &left = Vector2D(1.0f, 0.0f), const Vector2D &right = Vector2D(1.15f, 1.0f));
  void  moveAll(void);

private:
	const PatternManager _pm;
	std::list<Unit*>	 _enemies;
};

#endif /* !_SERVERGAMESTATE_H__ */

