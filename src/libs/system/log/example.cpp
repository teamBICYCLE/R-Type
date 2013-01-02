
#include "Log.hh"
#include <iostream>

int main() {
    log::err << "hello" << " mon petit lapin" << 2 << log::endl;
    log::debug << "hello" << log::endl;
    return 0;
}
