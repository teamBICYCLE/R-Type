/*
 * -----------------------------------------------------------------------------
 * "THE BEER-WARE LICENSE" (Revision 42):
 * <duplom_t@epitech.eu> wrote this file. As long as you retain this notice you
 * can do whatever you want with this stuff. If we meet some day, and you think
 * this stuff is worth it, you can buy me a beer in return. Thomas Duplomb
 * -----------------------------------------------------------------------------
 */

#include "Music.hh"

Music::Music()
{
  auto pair = std::make_pair("menu", std::shared_ptr<sf::Music>(new sf::Music));
  _musics.insert(pair);
  _musics["menu"]->openFromFile("./resources/audio/menu.ogg");
  _musics["menu"]->setLoop(true);

  pair = std::make_pair("game", std::shared_ptr<sf::Music>(new sf::Music));
  _musics.insert(pair);
  _musics["game"]->openFromFile("./resources/audio/game.ogg");
  _musics["game"]->setLoop(true);
}

Music::~Music()
{
}

void Music::play(const std::string& name)
{
  if (_lastPlayed) _lastPlayed->stop();
  _musics[name]->play();
  _lastPlayed = _musics[name];
}
