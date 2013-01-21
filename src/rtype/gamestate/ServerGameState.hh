#ifndef		_SERVERGAMESTATE_H__
# define	_SERVERGAMESTATE_H__

# include "GameState.hh"
# include "PatternManager.hh"	

class ServerGameState : public GameState {
public:
  ServerGameState(const std::shared_ptr<UnitPool> &, const std::vector<Player*>& v);
  virtual ~ServerGameState();

public:
  void  updateWithInput(const communication::Packet& packet);
  void	updateWorld(void);
  void  requireMonsters(const Vector2D &left = Vector2D(1.0f, 0.0f), const Vector2D &right = Vector2D(1.15f, 1.0f));
  void  moveOne(Player& p);
  void  moveAll(void);

private:
  void  setPlayerDirection(uint32_t id, const Vector2D& dir);

public:
  const std::vector<Player*>& getPlayers() const;
  const std::list<Unit*>&     getEnemies() const;

private:
	const PatternManager _pm;
  std::vector<Player*>  _players;
	std::list<Unit*>	 _enemies;
  std::chrono::time_point<std::chrono::system_clock> _lastIncrease;
  std::chrono::time_point<std::chrono::system_clock> _lastMonsterSpawn;
  const std::chrono::seconds  _levelIncreaseTick;
  std::chrono::milliseconds   _monsterSpawnRate;
};

#endif /* !_SERVERGAMESTATE_H__ */

