#ifndef     _LOG_HH_
#define		_LOG_HH_

#include <string>
#include "Logger.hh"

namespace TBSystem {
namespace log {
    extern Logger emergency;
    extern Logger alert;
    extern Logger critic;
    extern Logger err;
    extern Logger warn;
    extern Logger notice;
    extern Logger info;
    extern Logger debug;
}
}
#endif // _LOG_HH_