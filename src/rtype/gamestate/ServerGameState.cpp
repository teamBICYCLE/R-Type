/*
 * -----------------------------------------------------------------------------
 * "THE BEER-WARE LICENSE" (Revision 42):
 * <duplom_t@epitech.eu> wrote this file. As long as you retain this notice you
 * can do whatever you want with this stuff. If we meet some day, and you think
 * this stuff is worth it, you can buy me a beer in return. Thomas Duplomb
 * -----------------------------------------------------------------------------
 */

#include <list>
#include "input/Data.hh"
#include "units/Monster.hh"
#include "pool/SUnitPool.hh"
#include "ServerGameState.hh"

ServerGameState::ServerGameState(const std::shared_ptr<UnitPool> &p, const std::vector<Player*>& v)
  : GameState(p)
  , _pm()
  , _players(v)
  , _lastIncrease(std::chrono::system_clock::now())
  , _lastMonsterSpawn(std::chrono::system_clock::now())
  , _levelIncreaseTick(10)
  , _monsterSpawnRate(10000)
  , _turn(1)
  , _bossAppear(false)
{
   using namespace std::placeholders;

   _updateMap[communication::Packet::Type::INPUT] =
      std::bind(&ServerGameState::updateWithInput, this, _1);
}

ServerGameState::~ServerGameState()
{
}

void  ServerGameState::updateWithInput(const communication::Packet& packet)
{
  const uint32_t  id = packet.getId();

  if (id < _players.size()) {
    Input::Data d;
    Player *player = _players[id];

    if (player->isDead() == true)
      return;//if the player is dead, ignore his inputs
    d.unpack(packet.getSequence(), packet.getContent());
    if (player->getLastPacketSequence() < packet.getSequence())
    {
      player->setLastPacketSequence(packet.getSequence());
      setPlayerDirection(id, d.getVector());
      if (d.isFiring() == true) {
        Missile *newMissile = player->fire(_pool.get());
        if (newMissile != nullptr) {
          newMissile->setResourceId(5);
          _playerMissiles.push_back(newMissile);
        }
      }
    }
    else
    {
      std::cout << "==============================================Dropped. Last: " <<
      player->getLastPacketSequence() << ". New: " << packet.getSequence() << std::endl;
      player->setLastPacketSequence(0);//So that the client can reconnect and his packets be treated, and not dropped
    }
  }
}

template<typename UnitType>
void  ServerGameState::updateEntities(std::list<UnitType*>& entities,
                                      std::function<bool(const Unit *unit)> collideFun,
                                      std::function<void(Unit *unit)> fireFun)
{
  for (auto entityIt = entities.begin(); entityIt != entities.end(); ) {
    if ((*entityIt)->isDead() == true) {//if entity is dead..
      if ((*entityIt)->wereOthersNotifiedOfDeath() == true) {//..and client were notified
        UnitType *deadUnit = *entityIt;
        entityIt = entities.erase(entityIt);//..we remove it
        _pool->release<UnitType>(deadUnit);
      }
    }
    else {//entity alive
      (*entityIt)->move();
      fireFun(*entityIt); 
      if ((*entityIt)->isOffScreen(GameState::WINDOW_WIDTH) == true) {
        (*entityIt)->setDead(true);
      }
      if (collideFun(*entityIt) == true) {
        (*entityIt)->getHit();
      }
      ++entityIt;
    }
  }
}

void  ServerGameState::updateWorld(void)
{
  std::chrono::time_point<std::chrono::system_clock> now = std::chrono::system_clock::now();

  if (now - _lastIncrease >= _levelIncreaseTick) {
    _monsterSpawnRate = (_monsterSpawnRate * 9) / 10;//speed up by 10%
    _lastIncrease = now;
  }

  if (_bossAppear && _enemies.size() == 0)
  {
    _turn = 0;
    _bossAppear = false;
  }

  if (_turn == BOSS_SPAWN && !_bossAppear)
    requireBoss();
  else if (now - _lastMonsterSpawn >= _monsterSpawnRate && !_bossAppear) {
    if (_enemies.size() <= 60) {
      requireMonsters();
    }
    _lastMonsterSpawn = now;
  }

  std::function<bool(const Unit*)> monsterCollision = [this] (const Unit *monster) -> bool {
    for (auto& playerMissile : _playerMissiles) {
      //check monster against player missiles
      if (playerMissile->collideWith(*monster) == true) {
        playerMissile->getHit();
        return true;
      }
    }
    //bool  allDead = true;
    //for (auto& player : _players) {
    //  //check monster against players. Monsters do not die upon collision
    //  if (player->isDead() == false &&
    //      player->collideWith(*monster) == true) {
    //    player->getHit();
    //  }
    //  if (player->isDead() == false) {
    //    allDead = false;
    //  }
    //}
    //if (allDead == true) {
    //  _running = false;
    //}
    return false;
  };

  //std::function<bool(const Unit*)> monsterMissileCollision = [this] (const Unit *monsterMissile) -> bool {
  //  for (auto& player : _players) {
  //    //check monster missiles against players
  //    if (player->isDead() == false &&
  //        player->collideWith(*monsterMissile) == true) {
  //      player->getHit();
  //      return true;
  //    }
  //  }
  //  return false;
  //};

  std::function<void(Unit *)> noFire = [](Unit *u) -> void {
    (void)u;
  };

  std::function<bool(const Unit*)> noCollide = [] (const Unit*) -> bool {
    return false;
  };

  std::function<void(Unit *)> monsterFire = [this](Unit *u) -> void {
    Missile *m = u->fire(this->_pool.get());
    if (m)
    {
      //m->setDir(Vector2D(-1.f, 0));
      _monsterMissiles.push_back(m);
    }
  };

  updateEntities<Missile>(_monsterMissiles, noCollide, noFire);
  updateEntities<Missile>(_playerMissiles, noCollide, noFire);
  updateEntities<Monster>(_enemies, monsterCollision, monsterFire);
  ++_turn;
}

void ServerGameState::requireBoss(void)
{
    Monster *boss = _pool->get<Monster>();
    if (boss)
    {
      boss->setPos(Vector2D(1.1f, 0.40f));
      boss->setPv(35);
      boss->setResourceId(4);

      moveStyle move = [](const Vector2D &pos) {      
        Vector2D v; v.x = 0;
        if (pos.x >= 0.7f)
          v.x -= 1 / MONSTER_SPEED;
        return v;
      };

      boss->setMoveStyle(move);
      boss->setBoss(true);
      _bossAppear = true;
      _enemies.push_back(boss);
    }
}

void  ServerGameState::requireMonsters(void)
{
  std::list<Monster*> monsters = _pm.get(_pool);
  Vector2D left(1.0f, 0.1f);
  Vector2D right(1.2f, 0.5f);

  float randx = left.x + ((float)rand()) / ((float)RAND_MAX / (right.x - left.x));

  float randy = 0.f;
  int alive = std::count_if(_players.begin(), _players.end(),
                                [](const Player *p) -> bool {
                                  return !(p->isDead());
                                });

  if (alive == 0)
    randy = left.y + ((float)rand()) / ((float)RAND_MAX / (right.y - left.y));
  else
  {
    for (auto player : _players)
        if (!player->isDead())
          randy += player->getPos().y;

      randy /= alive;
      if (!monsters.empty())
      {
        float offset = ((monsters.back()->getPos().y / 2) * 0.05f);
        randy = (((randy - offset) < 0) ? (0) : (randy - offset));
      }
  }

  for (auto it : monsters)
  {
      Vector2D originalPos = it->getPos();
      float newX = randx + (originalPos.x * 0.03f); 
      float newY = randy + (originalPos.y * 0.05f);
      it->setPos(Vector2D(newX, newY));
  }
  _enemies.insert(_enemies.end(), monsters.begin(), monsters.end());
}

void  ServerGameState::moveOne(Player& p)
{
  p.move();
  for (auto& monster : _enemies) {
    if (p.isDead() == false &&
        p.collideWith(*monster) == true) {
      p.getHit();
    }
  }

  for (auto& monsterMissile : _monsterMissiles) {
    if (p.isDead() == false &&
        p.collideWith(*monsterMissile) == true) {
      p.getHit();
      monsterMissile->getHit();
    }
  }
}

void  ServerGameState::moveAll(void)
{
  bool  allDead = true;
  for (auto& p : _players) {
    if (p->isDead() == false) //only move alive player
      moveOne(*p);
    if (p->isDead() == false)
      allDead = false;
  }
  if (allDead == true) {
    _running = false;
  }
}

void  ServerGameState::setPlayerDirection(uint32_t id, const Vector2D& dir)
{
  if (id < _players.size()) {
    _players[id]->setDir(GameState::convertToSpeed(dir));
  }
}

const std::vector<Player*>& ServerGameState::getPlayers() const
{
  return _players;
}

const std::list<Monster*>&   ServerGameState::getEnemies() const
{
  return _enemies;
}

const std::list<Missile*>&  ServerGameState::getMonsterMissiles() const
{
  return _monsterMissiles;
}

const std::list<Missile*>&  ServerGameState::getPlayerMissiles() const
{
  return _playerMissiles;
}
