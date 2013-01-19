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
# include "units/graphics/GUnit.hh"

class GraphicGameState : public GameState, public sf::Drawable {
public:
  GraphicGameState(const std::vector<std::shared_ptr<Player>>& v);
  virtual ~GraphicGameState();

private:
  GraphicGameState(const GraphicGameState& other);
  GraphicGameState& operator=(const GraphicGameState& other);

public:
  void draw(sf::RenderTarget &target, sf::RenderStates states) const;

public:
  void  updateWithPosition  (const communication::Packet& packet);
  void  updateWithDeath     (const communication::Packet& packet);
  void  simulate            (const Input::Data& input);
  void  animationUpdate     (void);

private:
  const float BACKGROUND_SPEED;

private:
  sf::Texture *_backgroundTexture;
  sf::Sprite  *_backgroundSprite1;
  sf::Sprite  *_backgroundSprite2;
  Vector2D    _backgroundPos;
  Vector2D    _backgroundDirection;
  std::list<GUnit*> _enemies;
};

#endif /* !_GRAPHICGAMESTATE_H__ */
