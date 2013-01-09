/*
 * -----------------------------------------------------------------------------
 * "THE BEER-WARE LICENSE" (Revision 42):
 * <duplom_t@epitech.eu> wrote this file. As long as you retain this notice you
 * can do whatever you want with this stuff. If we meet some day, and you think
 * this stuff is worth it, you can buy me a beer in return Thomas Duplomb
 * -----------------------------------------------------------------------------
 */

#ifndef  _LOGGER_HH_
#define	 _LOGGER_HH_
#include <string>
#include <sstream>
#include <ostream>
#include <fstream>
#include <ctime>

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

    Logger(int level = INFO);
    ~Logger();

    bool       configure(const std::string &OutpuFile);

	void		outputHeader();

    template <typename T>
    Logger &   operator<<(const T & s) {
		outputHeader();
        _line << s;
        return *this;
    }

    Logger &   operator<<(const log::modifier & s);
    Logger &   operator<<(std::ostream& (*endline)(std::ostream&));

private:
    std::ostream &		_outstream() const;
	std::stringstream	_line;
    std::ofstream       _file;

private:
    int _level;
    bool _newline;
};
}
}
#endif // _LOGGER_HH_