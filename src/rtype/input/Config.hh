/*
 * -----------------------------------------------------------------------------
 * "THE BEER-WARE LICENSE" (Revision 42):
 * <duplom_t@epitech.eu> wrote this file. As long as you retain this notice you
 * can do whatever you want with this stuff. If we meet some day, and you think
 * this stuff is worth it, you can buy me a beer in return Thomas Duplomb
 * -----------------------------------------------------------------------------
 */

#ifndef _INPUTCONFIG_H__
#define _INPUTCONFIG_H__

#include <SFML/Window/Keyboard.hpp>
#include "Data.hh"

namespace Input {
class Config {
public:
    Config();
    ~Config();

public:
    Config(const Config & other);
    Config(Config && other);
    Config &    operator=(Config other);
    friend void swap(Config & lhs, Config & rhs);

public:
    Data    getInput() const;

    unsigned int        _playerId;
    sf::Keyboard::Key   _top;
    sf::Keyboard::Key   _bot;
    sf::Keyboard::Key   _right;
    sf::Keyboard::Key   _left;
    sf::Keyboard::Key   _fire;
};
}

#endif /* !_INPUTCONFIG_H__ */
