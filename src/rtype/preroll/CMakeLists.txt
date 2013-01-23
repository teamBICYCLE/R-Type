################################################################################
# "THE BEER-WARE LICENSE" (Revision 42):
# <duplom_t@epitech.eu> wrote this file. As long as you retain this notice you
# can do whatever you want with this stuff. If we meet some day, and you think
# this stuff is worth it, you can buy me a beer in return. Thomas Duplomb
################################################################################


list(APPEND LOUNGE_HEADERS
  ${CMAKE_CURRENT_LIST_DIR}/INetworkSerializable.hh
  ${CMAKE_CURRENT_LIST_DIR}/Client.hh
  ${CMAKE_CURRENT_LIST_DIR}/Room.hh
  ${CMAKE_CURRENT_LIST_DIR}/Lounge.hh
)

list(APPEND LOUNGE_SOURCES
  ${CMAKE_CURRENT_LIST_DIR}/Client.cpp
  ${CMAKE_CURRENT_LIST_DIR}/Room.cpp
  ${CMAKE_CURRENT_LIST_DIR}/Lounge.cpp
  ${CMAKE_CURRENT_LIST_DIR}/server.cpp
)

set(LOUNGE ${LOUNGE_HEADERS} ${LOUNGE_SOURCES})
