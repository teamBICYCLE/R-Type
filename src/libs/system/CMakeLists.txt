################################################################################
# "THE BEER-WARE LICENSE" (Revision 42):
# <duplom_t@epitech.eu> wrote this file. As long as you retain this notice you
# can do whatever you want with this stuff. If we meet some day, and you think
# this stuff is worth it, you can buy me a beer in return Thomas Duplomb
################################################################################

project(system)

include(dll/CMakeLists.txt)
include(threads/CMakeLists.txt)
include(network/CMakeLists.txt)
include(log/CMakeLists.txt)
include(archiver/CMakeLists.txt)
include(exploredir/CMakeLists.txt)

add_library(${PROJECT_NAME}
    ${${PROJECT_NAME}_HEADERS}
    ${${PROJECT_NAME}_SOURCES}
)

if(UNIX)
    target_link_libraries(${PROJECT_NAME} pthread dl)
endif(UNIX)
