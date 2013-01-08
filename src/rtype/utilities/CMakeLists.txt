################################################################################
# "THE BEER-WARE LICENSE" (Revision 42):
# <duplom_t@epitech.eu> wrote this file. As long as you retain this notice you
# can do whatever you want with this stuff. If we meet some day, and you think
# this stuff is worth it, you can buy me a beer in return Thomas Duplomb
################################################################################

list(APPEND UTILITIES_HEADERS
    ${CMAKE_CURRENT_LIST_DIR}/Vector2D.hh
)

list(APPEND UTILITIES_SOURCES
    ${CMAKE_CURRENT_LIST_DIR}/Vector2D.cpp
)

set(UTILITIES ${UTILITIES_HEADERS} ${UTILITIES_SOURCES})
