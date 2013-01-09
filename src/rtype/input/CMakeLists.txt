################################################################################
# "THE BEER-WARE LICENSE" (Revision 42):
# <duplom_t@epitech.eu> wrote this file. As long as you retain this notice you
# can do whatever you want with this stuff. If we meet some day, and you think
# this stuff is worth it, you can buy me a beer in return Thomas Duplomb
################################################################################

set(NAMESPACE INPUT)

list(APPEND ${NAMESPACE}_HEADERS
    ${CMAKE_CURRENT_LIST_DIR}/Data.hh
    ${CMAKE_CURRENT_LIST_DIR}/Config.hh
    ${CMAKE_CURRENT_LIST_DIR}/Manager.hh
)

list(APPEND ${NAMESPACE}_SOURCES
    ${CMAKE_CURRENT_LIST_DIR}/Data.cpp
    ${CMAKE_CURRENT_LIST_DIR}/Config.cpp
    ${CMAKE_CURRENT_LIST_DIR}/Manager.cpp
)

set(${NAMESPACE} ${${NAMESPACE}_HEADERS} ${${NAMESPACE}_SOURCES})
