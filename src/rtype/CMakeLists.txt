################################################################################
# "THE BEER-WARE LICENSE" (Revision 42):
# <duplom_t@epitech.eu> wrote this file. As long as you retain this notice you
# can do whatever you want with this stuff. If we meet some day, and you think
# this stuff is worth it, you can buy me a beer in return Thomas Duplomb
################################################################################

project(r-type)

set (RTYPE_VERSION_MAJOR 0)
set (RTYPE_VERSION_MINOR 1)
configure_file (
  "${PROJECT_SOURCE_DIR}/RTypeConfig.h.in"
  "${PROJECT_BINARY_DIR}/RTypeConfig.h"
  )

include_directories(${PROJECT_SOURCE_DIR} ${PROJECT_BINARY_DIR})

include("units/CMakeLists.txt")
include("utilities/CMakeLists.txt")
include("input/CMakeLists.txt")

add_executable(client
    ${GUI_TYPE} # Prevent windows from spawning a terminal window
    ${INPUT}
    ${UTILITIES}
    ${GUNITS}
    GameState.hh
    GameState.cpp
    GraphicGameState.cpp
    GraphicGameState.hh
    client.cpp
)

add_executable(server
    ${UTILITIES}
    ${UNITS}
    input/Data.hh
    input/Data.cpp
    server.cpp
    NetworkHandler.hh
    NetworkHandler.cpp
    GameState.hh
    GameState.cpp
)

target_link_libraries(client
    ${SFML_LIBRARIES}
    system
)

target_link_libraries(server
    system
)

# temporary

add_subdirectory(preroll)
