/*
 * -----------------------------------------------------------------------------
 * "THE BEER-WARE LICENSE" (Revision 42):
 * <duplom_t@epitech.eu> wrote this file. As long as you retain this notice you
 * can do whatever you want with this stuff. If we meet some day, and you think
 * this stuff is worth it, you can buy me a beer in return Thomas Duplomb
 * -----------------------------------------------------------------------------
 */

#ifndef     _LOGGER_HH_
#define		_LOGGER_HH_
#include <string>
#include <sstream>
#include <ostream>

namespace TBSystem {
namespace log {
enum modifier {
    endl
};

class Logger {
public:
    enum {
          EMERGENCY = 0
        , ALERT
        , CRITIC
        , ERR
        , WARN
        , NOTICE
        , INFO
        , DEBUG
    };

    Logger(int level = 6);
    ~Logger();

    template <typename T>
    Logger &   operator<<(const T & s) {
        if (_newline) {
            _line << std::string("BONJOUR ! Ceci est un message de log: ");
            _newline = false;
        }
        _line << s;
        return *this;
    }

    Logger &   operator<<(const log::modifier & s);

    template <class charT, class traits>
    Logger &   operator<<(std::basic_ostream<charT,traits>& endl)
    {
        (void)endl;
    }

private:
    std::ostream &		_outstream() const;
	std::stringstream	_line;

private:
    int _level;
    bool _newline;
};
}
}
#endif // _LOGGER_HH_