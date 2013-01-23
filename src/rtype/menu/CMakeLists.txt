
################################################################################
# "THE BEER-WARE LICENSE" (Revision 42):
# <duplom_t@epitech.eu> wrote this file. As long as you retain this notice you
# can do whatever you want with this stuff. If we meet some day, and you think
# this stuff is worth it, you can buy me a beer in return. Thomas Duplomb
################################################################################

list(APPEND MENU_HEADERS
  ${CMAKE_CURRENT_LIST_DIR}/Button.hh
  ${CMAKE_CURRENT_LIST_DIR}/ListItem.hh
  ${CMAKE_CURRENT_LIST_DIR}/ListView.hh
  ${CMAKE_CURRENT_LIST_DIR}/View.hh
  ${CMAKE_CURRENT_LIST_DIR}/PreGame.hh
  ${CMAKE_CURRENT_LIST_DIR}/Room.hh
  ${CMAKE_CURRENT_LIST_DIR}/RoomListItem.hh
  ${CMAKE_CURRENT_LIST_DIR}/Room.hh
  ${CMAKE_CURRENT_LIST_DIR}/PlayerListItem.hh
  ${CMAKE_CURRENT_LIST_DIR}/Player.hh
 )

list(APPEND MENU_SOURCES
  ${CMAKE_CURRENT_LIST_DIR}/Button.cpp
  ${CMAKE_CURRENT_LIST_DIR}/ListItem.cpp
  ${CMAKE_CURRENT_LIST_DIR}/ListView.cpp
  ${CMAKE_CURRENT_LIST_DIR}/main.cpp
  ${CMAKE_CURRENT_LIST_DIR}/View.hh
  ${CMAKE_CURRENT_LIST_DIR}/ListView.cpp
  ${CMAKE_CURRENT_LIST_DIR}/main.cpp
  ${CMAKE_CURRENT_LIST_DIR}/View.cpp
  ${CMAKE_CURRENT_LIST_DIR}/PreGame.cpp
  ${CMAKE_CURRENT_LIST_DIR}/Room.cpp
  ${CMAKE_CURRENT_LIST_DIR}/RoomListItem.cpp
  ${CMAKE_CURRENT_LIST_DIR}/Room.cpp
  ${CMAKE_CURRENT_LIST_DIR}/PlayerListItem.cpp
  ${CMAKE_CURRENT_LIST_DIR}/Player.cpp
)

set(MENU ${MENU_HEADERS} ${MENU_SOURCES})
