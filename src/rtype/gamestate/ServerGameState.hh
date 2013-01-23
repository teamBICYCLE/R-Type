#ifndef		_SERVERGAMESTATE_H__
# define	_SERVERGAMESTATE_H__

# include "GameState.hh"
# include "PatternManager.hh"	

# define  BOSS_SPAWN 5000

class ServerGameState : public GameState {
public:
  ServerGameState(const std::shared_ptr<UnitPool> &, const std::vector<Player*>& v);
  virtual ~ServerGameState();

public:
  void  updateWithInput(const communication::Packet& packet);
  void	updateWorld(void);
  void  requireMonsters(void);
  void  requireBoss(void);
  void  moveOne(Player& p);
  void  moveAll(void);

public:
  template<typename UnitType>
  void  updateEntities(std::list<UnitType*>& entities,
                       std::function<bool(const Unit *unit)> collideFun,
                       std::function<void(Unit *unit)> fireFun);

private:
  void  setPlayerDirection(uint32_t id, const Vector2D& dir);

public:
  const std::vector<Player*>& getPlayers() const;
  const std::list<Monster*>&  getEnemies() const;
  const std::list<Missile*>&  getMonsterMissiles() const;
  const std::list<Missile*>&  getPlayerMissiles() const;

private:
	const PatternManager  _pm;
  std::vector<Player*>  _players;
	std::list<Monster*>	  _enemies;
	std::list<Missile*>	  _monsterMissiles;
	std::list<Missile*>	  _playerMissiles;
  std::chrono::time_point<std::chrono::system_clock> _lastIncrease;
  std::chrono::time_point<std::chrono::system_clock> _lastMonsterSpawn;
  const std::chrono::seconds  _levelIncreaseTick;
  std::chrono::milliseconds   _monsterSpawnRate;
  unsigned int _turn;
  bool _bossAppear;
};

#endif /* !_SERVERGAMESTATE_H__ */

