################################################################################
# "THE BEER-WARE LICENSE" (Revision 42):
# <duplom_t@epitech.eu> wrote this file. As long as you retain this notice you
# can do whatever you want with this stuff. If we meet some day, and you think
# this stuff is worth it, you can buy me a beer in return. Thomas Duplomb
################################################################################

project(preroll)

include_directories(${PROJECT_SOURCE_DIR})

add_executable(preroll_server
  Client.cpp
  Client.hh
  Room.cpp
  Room.hh
  INetworkSerializable.hh
  Lounge.cpp
  Lounge.hh
  server.cpp
  ${UTILITIES}
  ${UNITS}
  ${SERVER_NETWORK}
  ${SERVER_GAMESTATE}
  ${SERVER_POOL}
  ../input/Data.hh
  ../input/Data.cpp
  ../server.cpp
)

target_link_libraries(preroll_server
  system
  csv-parser
)
