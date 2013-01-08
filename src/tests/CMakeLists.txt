################################################################################
# "THE BEER-WARE LICENSE" (Revision 42):
# <duplom_t@epitech.eu> wrote this file. As long as you retain this notice you
# can do whatever you want with this stuff. If we meet some day, and you think
# this stuff is worth it, you can buy me a beer in return Thomas Duplomb
################################################################################

## example

add_executable(test-lol udp.cpp)
target_link_libraries(test-lol system ${SFML_LIBRARIES})

## your tests

add_executable(thread_test thread_test.cpp)
target_link_libraries(thread_test system)
