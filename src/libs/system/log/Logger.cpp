/*
 * -----------------------------------------------------------------------------
 * "THE BEER-WARE LICENSE" (Revision 42):
 * <duplom_t@epitech.eu> wrote this file. As long as you retain this notice you
 * can do whatever you want with this stuff. If we meet some day, and you think
 * this stuff is worth it, you can buy me a beer in return Thomas Duplomb
 * -----------------------------------------------------------------------------
 */

#include "Logger.hh"
#include <iostream>

namespace log {
Logger::Logger(int level)
: _level(level)
, _newline(true)
{
}

Logger::~Logger() {}

Logger & Logger::operator<<(const log::modifier & s) {
    _outstream() << std::endl;
    _newline = true;
    return *this;
}

std::ostream & Logger::_outstream() const {
   if (_level <= NOTICE) {
        return std::cout;
    }
    else if (_level <= DEBUG) {
        return std::cerr;
    }
    else {
        return std::cerr; // TODO: std::cnull
    }
}
}
