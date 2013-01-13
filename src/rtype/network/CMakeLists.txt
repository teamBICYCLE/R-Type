################################################################################
# "THE BEER-WARE LICENSE" (Revision 42):
# <duplom_t@epitech.eu> wrote this file. As long as you retain this notice you
# can do whatever you want with this stuff. If we meet some day, and you think
# this stuff is worth it, you can buy me a beer in return Thomas Duplomb
################################################################################

list(APPEND COMMON_NETWORK_HEADERS
  ${CMAKE_CURRENT_LIST_DIR}/IPackable.hh
  ${CMAKE_CURRENT_LIST_DIR}/Packet.hh
)

list(APPEND COMMON_NETWORK_SOURCES
  ${CMAKE_CURRENT_LIST_DIR}/Packet.cpp
)

list(APPEND SERVER_NETWORK_HEADERS
  ${COMMON_NETWORK_HEADERS}
  ${CMAKE_CURRENT_LIST_DIR}/NetworkHandler.hh
)

list(APPEND SERVER_NETWORK_SOURCES
  ${COMMON_NETWORK_SOURCES}
  ${CMAKE_CURRENT_LIST_DIR}/NetworkHandler.cpp
)

set(CLIENT_NETWORK ${COMMON_NETWORK_HEADERS} ${COMMON_NETWORK_SOURCES})
set(SERVER_NETWORK ${SERVER_NETWORK_HEADERS} ${SERVER_NETWORK_SOURCES})
