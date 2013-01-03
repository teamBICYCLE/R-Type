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

include_directories("${PROJECT_BINARY_DIR}")

list(APPEND ${PROJECT_NAME}_HEADERS
)

list(APPEND ${PROJECT_NAME}_SOURCES
    main.cpp
)

add_executable(${PROJECT_NAME} 
	${GUI_TYPE} # Prevent windows from spawning a terminal window
    ${${PROJECT_NAME}_HEADERS}
    ${${PROJECT_NAME}_SOURCES}
)

target_link_libraries(${PROJECT_NAME} 
    ${SFML_LIBRARIES}
    system
)
