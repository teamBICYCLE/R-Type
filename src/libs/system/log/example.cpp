
#include "Log.hh"
#include <iostream>

using namespace TBSystem;

int main() {
    log::err << "hello" << " mon petit lapin" << std::endl << 2 << log::endl;
    log::debug << "hello" << log::endl;
    return 0;
}
