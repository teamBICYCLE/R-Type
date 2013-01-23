/*
 * -----------------------------------------------------------------------------
 * "THE BEER-WARE LICENSE" (Revision 42):
 * <duplom_t@epitech.eu> wrote this file. As long as you retain this notice you
 * can do whatever you want with this stuff. If we meet some day, and you think
 * this stuff is worth it, you can buy me a beer in return. Thomas Duplomb
 * -----------------------------------------------------------------------------
 */

#ifndef _CLIENT_H__
#define _CLIENT_H__

#include <string>

class sf::RenderWindow;

void client(const std::string& ip, const std::string& port, int id,
            sf::RenderWindow& window);

#endif /* !_CLIENT_H__ */
