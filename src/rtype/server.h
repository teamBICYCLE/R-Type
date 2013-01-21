/*
 * -----------------------------------------------------------------------------
 * "THE BEER-WARE LICENSE" (Revision 42):
 * <duplom_t@epitech.eu> wrote this file. As long as you retain this notice you
 * can do whatever you want with this stuff. If we meet some day, and you think
 * this stuff is worth it, you can buy me a beer in return. Thomas Duplomb
 * -----------------------------------------------------------------------------
 */

#ifndef _SERVER_H__
#define _SERVER_H__

#include <vector>
#include <string>

void runServer(const std::vector<std::string>& clients,
               const std::string& port);

#endif /* !_SERVER_H__ */
