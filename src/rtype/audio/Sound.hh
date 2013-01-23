/*
 * -----------------------------------------------------------------------------
 * "THE BEER-WARE LICENSE" (Revision 42):
 * <duplom_t@epitech.eu> wrote this file. As long as you retain this notice you
 * can do whatever you want with this stuff. If we meet some day, and you think
 * this stuff is worth it, you can buy me a beer in return. Thomas Duplomb
 * -----------------------------------------------------------------------------
 */

#ifndef _SOUND_H__
#define _SOUND_H__

#include <map>
#include <string>
#include <list>
#include <SFML/Audio.hpp>

class Sound {
public:
  Sound();
  ~Sound();

  void play(const std::string& name);

private:
  std::map<std::string, sf::SoundBuffer> _buffers;
  std::list<sf::Sound>  _players;
};

#endif /* !_SOUND_H__ */
