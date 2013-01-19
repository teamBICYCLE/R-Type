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
  void  requireMonsters(const Vector2D &left, const Vector2D &right);
  void  moveAll(void);

private:
	const PatternManager _pm;
	std::list<Unit*>	 _enemies;
};

#endif /* !_SERVERGAMESTATE_H__ */

