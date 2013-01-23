/*
 * -----------------------------------------------------------------------------
 * "THE BEER-WARE LICENSE" (Revision 42):
 * <duplom_t@epitech.eu> wrote this file. As long as you retain this notice you
 * can do whatever you want with this stuff. If we meet some day, and you think
 * this stuff is worth it, you can buy me a beer in return. Thomas Duplomb
 * -----------------------------------------------------------------------------
 */

#ifndef   _GRAPHICGAMESTATE_H__
# define  _GRAPHICGAMESTATE_H__

# include <list>
# include <SFML/Graphics.hpp>
# include "input/Data.hh"
# include "GameState.hh"
# include "units/graphics/GPlayer.hh"

class GraphicGameState : public GameState, public sf::Drawable {
public:
  GraphicGameState(const std::shared_ptr<UnitPool> &, const std::shared_ptr<Sprite::AnimationManager> &, std::shared_ptr<GPlayer> player);
  virtual ~GraphicGameState();

private:
  GraphicGameState(const GraphicGameState& other);
  GraphicGameState& operator=(const GraphicGameState& other);

public:
  void draw(sf::RenderTarget &target, sf::RenderStates states) const;

public:
  void  updateWithPosition  (const communication::Packet& packet);
  void  updateWithDeath     (const communication::Packet& packet);
  void  endGame             (const communication::Packet& packet);
  void  clientDisconnected  (const communication::Packet& packet);
  void  simulate            (const Input::Data& input);
  void  animationUpdate     (void);

private:
  GUnit *findEntityById(const uint32_t id);

private:
  const float BACKGROUND_SPEED;

private:
  sf::Texture *_backgroundTexture;
  sf::Sprite  *_backgroundSprite1;
  sf::Sprite  *_backgroundSprite2;
  Vector2D    _backgroundPos;
  Vector2D    _backgroundDirection;
  std::shared_ptr<GPlayer>  _player;
  std::list<GUnit*>         _others;
  std::list<GUnit*>         _deadUnits;
  std::shared_ptr<Sprite::AnimationManager>  _animationManager;
};

#endif /* !_GRAPHICGAMESTATE_H__ */
