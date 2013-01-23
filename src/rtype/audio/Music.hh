/*
 * -----------------------------------------------------------------------------
 * "THE BEER-WARE LICENSE" (Revision 42):
 * <duplom_t@epitech.eu> wrote this file. As long as you retain this notice you
 * can do whatever you want with this stuff. If we meet some day, and you think
 * this stuff is worth it, you can buy me a beer in return. Thomas Duplomb
 * -----------------------------------------------------------------------------
 */

#ifndef _MUSIC_H__
#define _MUSIC_H__

#include <map>
#include <string>
#include <memory>
#include <SFML/Audio.hpp>

class Music {
public:
  Music();
  ~Music();

  void play(const std::string& name);

private:
  std::map<std::string, std::shared_ptr<sf::Music>> _musics;
  std::shared_ptr<sf::Music> _lastPlayed;
};

#endif /* !_MUSIC_H__ */
