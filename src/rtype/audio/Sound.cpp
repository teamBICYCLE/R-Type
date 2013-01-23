/*
 * -----------------------------------------------------------------------------
 * "THE BEER-WARE LICENSE" (Revision 42):
 * <duplom_t@epitech.eu> wrote this file. As long as you retain this notice you
 * can do whatever you want with this stuff. If we meet some day, and you think
 * this stuff is worth it, you can buy me a beer in return. Thomas Duplomb
 * -----------------------------------------------------------------------------
 */

#include "Sound.hh"
#include <iostream>

Sound::Sound()
{
  _buffers["shoot"].loadFromFile("./resources/audio/samples/shoot.wav");
}

Sound::~Sound()
{
}

void Sound::play(const std::string& name)
{
  for (auto& p : _players) {
    if (p.getStatus() == sf::SoundSource::Stopped) {
      p.setBuffer(_buffers[name]);
      p.play();
      return ;
    }
  }
  _players.emplace_back();
  auto p = _players.back();
  p.setBuffer(_buffers[name]);
  p.play();
}
