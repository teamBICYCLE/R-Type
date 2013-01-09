/*
 * -----------------------------------------------------------------------------
 * "THE BEER-WARE LICENSE" (Revision 42):
 * <duplom_t@epitech.eu> wrote this file. As long as you retain this notice you
 * can do whatever you want with this stuff. If we meet some day, and you think
 * this stuff is worth it, you can buy me a beer in return Thomas Duplomb
 * -----------------------------------------------------------------------------
 */

#ifndef _INPUTMANAGER_H__
#define _INPUTMANAGER_H__

#include <vector>
#include "Data.hh"
#include "Config.hh"

namespace Input {
class Manager {
public:
    Manager();
    ~Manager();

    std::vector<Data> getInputs();

private:
    std::vector<Config> _configs;
};
}

#endif /* !_INPUTMANAGER_H__ */
