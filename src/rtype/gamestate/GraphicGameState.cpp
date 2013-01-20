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
#include "units/graphics/GPlayer.hh"

using namespace TBSystem;

GraphicGameState::GraphicGameState(const std::vector<std::shared_ptr<Player>>& v)
  : GameState(v)
  , BACKGROUND_SPEED(800.f)
  , _backgroundTexture(new sf::Texture)
  , _backgroundSprite1(new sf::Sprite)
  , _backgroundSprite2(new sf::Sprite)
  , _backgroundPos()
  , _backgroundDirection(-1.f, 0.f)
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
  target.draw(*_backgroundSprite1);
  target.draw(*_backgroundSprite2);
  for (auto& p : _players) {
    if (p->isDead() == false)
      target.draw(static_cast<GPlayer&>(*p));//only draw alive players
  }
}

// client
void  GraphicGameState::updateWithPosition(const communication::Packet& packet)
{
  const uint32_t id = packet.getId();

  //ROMAIN: ici tu traites les packets de type POSITION
  //(envoyes quand un monstre se deplace, donc)
  if (id < _players.size()) {
    _players[id]->unpack(packet.getSequence(), packet.getContent());
  }
  else
  {
    //UnitPool::getInstance()->get<>
    //_enemies.push_back()
  }
}

// client
void  GraphicGameState::updateWithDeath(const communication::Packet& packet)
{
  const uint32_t id = packet.getId();

  std::cout << "DEATH" << std::endl;
  if (id < _players.size()) {
    _players[id]->setDead(true);
  }
  //need to look for a monster/missile with this id and remove it
}

void  GraphicGameState::simulate(const Input::Data& input)
{
  const int playerId = input.getId();

  if (playerId >= 0 && playerId < _players.size()) {
    if (_players[playerId]->isDead() == false) {//only simulate if player is alive
      GameState::setPlayerDirection(playerId, input.getVector());
      GameState::moveOne(*_players[playerId]);
    }
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
