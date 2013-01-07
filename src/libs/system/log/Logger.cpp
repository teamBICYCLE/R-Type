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
#ifdef _WIN32
# include <Windows.h>
#endif

namespace TBSystem {
namespace log {
Logger::Logger(int level)
: _level(level)
, _newline(true)
{}

Logger::~Logger() {}

Logger & Logger::operator<<(const log::modifier & s) {
	switch (s) {
	case log::endl:
		_line << std::endl;
        if (_file.good()) {
            _file << _line.str();
        } else {
            #ifdef __gnu_linux__
        		_outstream() << _line.str();
        		_outstream().flush();
            #elif defined _WIN32
        		OutputDebugString(_line.str().c_str());
            #endif
        }
		_newline = true;
		break;
	default:
		break;
	}
    return *this;
}

Logger& Logger::operator<<(std::ostream& (*endline)(std::ostream&))
    {
    	_line << endline;
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

bool    Logger::configure(const std::string &OutputFile) {
    bool success = false;
    _file.open(OutputFile);
    if (_file.good()) {
        success = true;
    }
    return (success);
}
}
}
