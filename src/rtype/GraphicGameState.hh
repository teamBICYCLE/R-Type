/*
 * -----------------------------------------------------------------------------
 * "THE BEER-WARE LICENSE" (Revision 42):
 * <duplom_t@epitech.eu> wrote this file. As long as you retain this notice you
 * can do whatever you want with this stuff. If we meet some day, and you think
 * this stuff is worth it, you can buy me a beer in return. Thomas Duplomb
 * -----------------------------------------------------------------------------
 */

#ifndef _GRAPHICGAMESTATE_H__
#define _GRAPHICGAMESTATE_H__

#include <SFML/Graphics.hpp>
#include "GameState.hh"

class GraphicGameState : public GameState, public sf::Drawable {
public:
  GraphicGameState(const std::vector<std::shared_ptr<Unit>>& v);
  virtual ~GraphicGameState();

public:
  void draw(sf::RenderTarget &target, sf::RenderStates states) const;

public:
  void  updateWithPosition (uint32_t id, const uint8_t* content);
  void  updateWithDeath    (uint32_t id, const uint8_t* content);
};

#endif /* !_GRAPHICGAMESTATE_H__ */
