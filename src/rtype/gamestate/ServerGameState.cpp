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
#include "ServerGameState.hh"

ServerGameState::ServerGameState(const std::vector<std::shared_ptr<Player>>& v)
  : GameState()
  , _pm()
  , _players(v)
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

  if (id <= _players.size()) {
    Input::Data d;
    std::shared_ptr<Player>& player = _players[id];

    if (player->isDead() == true)
      return;//if the player is dead, ignore his inputs
    d.unpack(packet.getSequence(), packet.getContent());
    if (player->getLastPacketSequence() < packet.getSequence())
    {
      player->setLastPacketSequence(packet.getSequence());
      setPlayerDirection(id, d.getVector());
      if (d.isFiring() == true)
      {}
    }
    else
    {
      std::cout << "==============================================Dropped. Last: " <<
      player->getLastPacketSequence() << ". New: " << packet.getSequence() << std::endl;
      player->setLastPacketSequence(0);//So that the client can reconnect and his packets be treated, and not dropped
    }
  }
}

void  ServerGameState::updateWorld(void)
{
  //SHIT -v
  static bool first = true;

  if (first == true)
  {
    requireMonsters(Vector2D(0.1f, 0.1f), Vector2D(0.9f, 0.9f));
    first = false;
  }

  for (auto& e : _enemies) {
    (dynamic_cast<Monster *>(e))->move();
  }
}

void  ServerGameState::requireMonsters(const Vector2D &left, const Vector2D &right)
{
  //SHIT -v
  int id = 5;
  std::list<Unit *> monsters = _pm.get();

  float randx = left.x + ((float)rand()) / ((float)RAND_MAX / (right.x - left.x));
  float randy = left.y + ((float)rand()) / ((float)RAND_MAX / (right.y - left.y));

  // pour l'instant on verifie rien
  for (auto it : monsters)
  {
      Vector2D originalPos = it->getPos();
      float newX = randx + (originalPos.x * 0.03);
      float newY = randy + (originalPos.y * 0.05);
      it->setPos(Vector2D(newX, newY));
      //SHIT -v
      it->setId(id++);
      std::cout << it->getResourceId() << std::endl;
  }
  _enemies.insert(_enemies.end(), monsters.begin(), monsters.end());
}

void  ServerGameState::moveOne(Player& p)
{
  Vector2D  savedPos = p.getPos();

  p.move();
  for (auto& enemy : _enemies)
  {
    if (p.collideWith(*enemy) == true)
    {
      p.setDead(true);
      std::cout << "COLLIDED" << std::endl;
      break;
    }
  }
}

void  ServerGameState::moveAll(void)
{
   for (auto& p : _players) {
      if (p->isDead() == false) //only move alive player
        moveOne(*p);
   }
}

void  ServerGameState::setPlayerDirection(uint32_t id, const Vector2D& dir)
{
  if (id < _players.size()) {
    _players[id]->setDir(GameState::convertToSpeed(dir));
  }
}

const std::vector<std::shared_ptr<Player>>& ServerGameState::getPlayers() const
{
  return _players;
}

const std::list<Unit*>&   ServerGameState::getEnemies() const
{
  return _enemies;
}
