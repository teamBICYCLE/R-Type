################################################################################
# "THE BEER-WARE LICENSE" (Revision 42):
# <duplom_t@epitech.eu> wrote this file. As long as you retain this notice you
# can do whatever you want with this stuff. If we meet some day, and you think
# this stuff is worth it, you can buy me a beer in return Thomas Duplomb
################################################################################

list(APPEND COMMON_HEADERS
  ${CMAKE_CURRENT_LIST_DIR}/GameState.hh
)

list(APPEND COMMON_SOURCES
  ${CMAKE_CURRENT_LIST_DIR}/GameState.cpp
)

list(APPEND SERVER_HEADERS
  ${COMMON_HEADERS}
  ${CMAKE_CURRENT_LIST_DIR}/ServerGameState.hh
  ${CMAKE_CURRENT_LIST_DIR}/Pattern.hh
  ${CMAKE_CURRENT_LIST_DIR}/PatternManager.hh
)

list(APPEND SERVER_SOURCES
  ${COMMON_SOURCES}
  ${CMAKE_CURRENT_LIST_DIR}/ServerGameState.cpp
  ${CMAKE_CURRENT_LIST_DIR}/Pattern.cpp
  ${CMAKE_CURRENT_LIST_DIR}/PatternManager.cpp
)

list(APPEND CLIENT_HEADERS
  ${COMMON_HEADERS}
  ${CMAKE_CURRENT_LIST_DIR}/GraphicGameState.hh
)

list(APPEND CLIENT_SOURCES
  ${COMMON_SOURCES}
  ${CMAKE_CURRENT_LIST_DIR}/GraphicGameState.cpp
)

set(CLIENT_GAMESTATE ${CLIENT_HEADERS} ${CLIENT_SOURCES})
set(SERVER_GAMESTATE ${SERVER_HEADERS} ${SERVER_SOURCES})
