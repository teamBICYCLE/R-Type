/*
 * -----------------------------------------------------------------------------
 * "THE BEER-WARE LICENSE" (Revision 42):
 * <duplom_t@epitech.eu> wrote this file. As long as you retain this notice you
 * can do whatever you want with this stuff. If we meet some day, and you think
 * this stuff is worth it, you can buy me a beer in return Thomas Duplomb
 * -----------------------------------------------------------------------------
 */

#include <string>

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
            _outstream() << std::string("BONJOUR ! Ceci est un message de log: ");
            _newline = false;
        }
        _outstream() << s;
        return *this;
    }
    Logger &   operator<<(const log::modifier & s);

private:
    std::ostream & _outstream() const;

private:
    int _level;
    bool _newline;
};
}
