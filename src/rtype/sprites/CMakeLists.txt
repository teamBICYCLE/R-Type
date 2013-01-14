################################################################################
# "THE BEER-WARE LICENSE" (Revision 42):
# <duplom_t@epitech.eu> wrote this file. As long as you retain this notice you
# can do whatever you want with this stuff. If we meet some day, and you think
# this stuff is worth it, you can buy me a beer in return Thomas Duplomb
################################################################################

list(APPEND SPRITES_HEADERS
  ${CMAKE_CURRENT_LIST_DIR}/Animation.hh
  ${CMAKE_CURRENT_LIST_DIR}/Board.hh
  ${CMAKE_CURRENT_LIST_DIR}/AnimationInfos.hh
)

list(APPEND SPRITES_SOURCES
  ${CMAKE_CURRENT_LIST_DIR}/Animation.cpp
  ${CMAKE_CURRENT_LIST_DIR}/Board.cpp
  ${CMAKE_CURRENT_LIST_DIR}/AnimationInfos.cpp
)

set(SPRITES ${SPRITES_HEADERS} ${SPRITES_SOURCES})
