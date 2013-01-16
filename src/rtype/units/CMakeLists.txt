################################################################################
# "THE BEER-WARE LICENSE" (Revision 42):
# <duplom_t@epitech.eu> wrote this file. As long as you retain this notice you
# can do whatever you want with this stuff. If we meet some day, and you think
# this stuff is worth it, you can buy me a beer in return Thomas Duplomb
################################################################################

list(APPEND UNITS_HEADERS
    ${CMAKE_CURRENT_LIST_DIR}/Unit.hh
    ${CMAKE_CURRENT_LIST_DIR}/Player.hh
    ${CMAKE_CURRENT_LIST_DIR}/Monster.hh
)

list(APPEND UNITS_SOURCES
    ${CMAKE_CURRENT_LIST_DIR}/Unit.cpp
    ${CMAKE_CURRENT_LIST_DIR}/Player.cpp
    ${CMAKE_CURRENT_LIST_DIR}/Monster.cpp
)

set(UNITS ${UNITS_HEADERS} ${UNITS_SOURCES})

include("units/graphics/CMakeLists.txt")
include("units/shared/CMakeLists.txt")