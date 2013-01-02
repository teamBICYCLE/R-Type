// Default configuration
// log::info << "test" << log::endl;
// output : `[Mar 11 déc 2012 16:42:19 CET], duplom_t@macbookair: test`
// log::warn << "test" << log::endl;
// log::err << "test" << log::endl;
//
// log::emergency     (level 0)
// log::alert         (level 1)
// log::critic        (level 2)
// log::err           (level 3)
// log::warn          (level 4)
// log::notice        (level 5)
// log::info          (level 6)
// log::debug         (level 7) 

#include "Log.hh"
#include <iostream>

namespace TBSystem {
namespace log {
    Logger emergency(Logger::EMERGENCY);
    Logger alert(Logger::ALERT);
    Logger critic(Logger::CRITIC);
    Logger err(Logger::ERR);
    Logger warn(Logger::WARN);
    Logger notice(Logger::NOTICE);
    Logger info(Logger::INFO);
    Logger debug(Logger::DEBUG);
}
}

