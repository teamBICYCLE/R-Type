/*
 * -----------------------------------------------------------------------------
 * "THE BEER-WARE LICENSE" (Revision 42):
 * <duplom_t@epitech.eu> wrote this file. As long as you retain this notice you
 * can do whatever you want with this stuff. If we meet some day, and you think
 * this stuff is worth it, you can buy me a beer in return. Thomas Duplomb
 * -----------------------------------------------------------------------------
 */

#include <system/log/Log.hh>
#include "GraphicGameState.hh"
#include "pool/GUnitPool.hh"
#include "units/graphics/GPlayer.hh"

using namespace TBSystem;

GraphicGameState::GraphicGameState(const std::shared_ptr<UnitPool> &p,
                                   const std::shared_ptr<Sprite::AnimationManager> &a,
                                   std::shared_ptr<GPlayer> player)
  : GameState(p)
  , BACKGROUND_SPEED(800.f)
  , _backgroundTexture(new sf::Texture)
  , _backgroundSprite1(new sf::Sprite)
  , _backgroundSprite2(new sf::Sprite)
  , _backgroundPos()
  , _backgroundDirection(-1.f, 0.f)
  , _player(player)
  , _animationManager(a)
{
  using namespace std::placeholders;

   _updateMap[communication::Packet::Type::POSITION] =
      std::bind(&GraphicGameState::updateWithPosition, this, _1);
   _updateMap[communication::Packet::Type::DEATH] =
      std::bind(&GraphicGameState::updateWithDeath, this, _1);

  _backgroundTexture->loadFromFile("resources/background.jpg");
  _backgroundSprite1->setTexture(*_backgroundTexture);
  _backgroundSprite2->setTexture(*_backgroundTexture);
}

GraphicGameState::~GraphicGameState()
{
  delete _backgroundTexture;
  delete _backgroundSprite1;
  delete _backgroundSprite2;
}

void GraphicGameState::draw(sf::RenderTarget &target, sf::RenderStates states) const {
  (void)states;
  target.draw(*_backgroundSprite1);
  target.draw(*_backgroundSprite2);
  if (_player->isDead() == false)
    target.draw(static_cast<GUnit&>(*_player));//only draw alive players
  for (auto& entity : _others) {
      target.draw(*entity);
  }
}

// client
void  GraphicGameState::updateWithPosition(const communication::Packet& packet)
{
  const uint32_t id = packet.getId();

  if (id == _player->getId())
    _player->unpack(packet.getSequence(), packet.getContent());
  else
  {
    GUnit *entity = findEntityById(id);

    if (entity != nullptr)
      entity->unpack(packet.getSequence(), packet.getContent());
    else {
      GUnit *newEntity = _pool->get<GUnit>();

      if (newEntity != nullptr) {
        //std::cout << "Setting id of newEntity from " << newEntity->getId() << " to " << id << std::endl;
        newEntity->setId(id);
        newEntity->setResourceId(packet.getResourceId());
        newEntity->setAnimationManager(_animationManager);
        _others.push_back(newEntity);
        _others.back()->unpack(packet.getSequence(), packet.getContent());
      }
    }
  }
}

// client
void  GraphicGameState::updateWithDeath(const communication::Packet& packet)
{
  const uint32_t id = packet.getId();

  //std::cout << "DEATH" << std::endl;
  if (id == _player->getId())//if it's me..
    _player->setDead(true);
  else//search for an enemy/ally/bullet
  {
    GUnit *entity = findEntityById(id);

    //need someting like deleteLater, juste to animate the death
    if (entity != nullptr) {
      std::cout << "Entity with id=" << entity->getId() << " died" << std::endl;
      _others.remove(entity);
      _pool->release<GUnit>(entity);
    }
  }
}

void  GraphicGameState::simulate(const Input::Data& input)
{
  const uint32_t playerId = input.getId();

  if (playerId == _player->getId() &&
      _player->isDead() == false)//simulate only if player is alive
  {
    _player->setDir(GameState::convertToSpeed(input.getVector()));
    _player->move();
  }
}

void  GraphicGameState::animationUpdate(void)
{
  sf::Vector2f pos;

  _backgroundPos += (_backgroundDirection / GraphicGameState::BACKGROUND_SPEED);
  pos = static_cast<sf::Vector2f>(_backgroundPos);
	pos.x *= GameState::WINDOW_WIDTH;
	pos.y *= GameState::WINDOW_HEIGHT;
  _backgroundSprite1->setPosition(pos);
  pos.x += _backgroundTexture->getSize().x;
  if (pos.x <= 0)//if the x of the second background is less than zero...
    _backgroundPos.x = 0;//then we reset the position of the first background to loop again
  _backgroundSprite2->setPosition(pos);
}

GUnit *GraphicGameState::findEntityById(const uint32_t id)
{
  auto  entityIt = std::find_if(_others.begin(), _others.end(),
                                [&id](const GUnit* entity) -> bool {
                                return id == entity->getId();
                                });

  if (entityIt != _others.end())
    return *entityIt;
  return nullptr;
}
