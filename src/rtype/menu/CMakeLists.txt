
################################################################################
# "THE BEER-WARE LICENSE" (Revision 42):
# <duplom_t@epitech.eu> wrote this file. As long as you retain this notice you
# can do whatever you want with this stuff. If we meet some day, and you think
# this stuff is worth it, you can buy me a beer in return. Thomas Duplomb
################################################################################

project(client)

include_directories(${PROJECT_SOURCE_DIR})

add_executable(preroll_client
  ${GUI_TYPE} # Prevent windows from spawning a terminal window
  Button.cpp
  Button.hh
  ListItem.cpp
  ListItem.hh
  ListView.cpp
  ListView.hh
  main.cpp
  View.cpp
  View.hh
  PreGame.cpp
  PreGame.hh
  Room.cpp
  Room.hh
  RoomListItem.cpp
  RoomListItem.hh
  Room.cpp
  Room.hh
  PlayerListItem.cpp
  PlayerListItem.hh
  Player.cpp
  Player.hh
  ${INPUT}
  ${UTILITIES}
  ${GUNITS}
  ${CLIENT_NETWORK}
  ${CLIENT_GAMESTATE}
  ${SPRITES}
  ${CLIENT_POOL}
  ../client.cpp
  )

target_link_libraries(preroll_client
  system
  csv-parser
  ${SFML_LIBRARIES}
  )
