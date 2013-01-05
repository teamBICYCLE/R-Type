################################################################################
# "THE BEER-WARE LICENSE" (Revision 42):
# <duplom_t@epitech.eu> wrote this file. As long as you retain this notice you
# can do whatever you want with this stuff. If we meet some day, and you think
# this stuff is worth it, you can buy me a beer in return Thomas Duplomb
################################################################################

if(${UNIX})
list(APPEND ${PROJECT_NAME}_HEADERS
    ${CMAKE_CURRENT_LIST_DIR}/UnixDLoader.hh
)
elseif(${WIN32})
list(APPEND ${PROJECT_NAME}_HEADERS
    ${CMAKE_CURRENT_LIST_DIR}/WinDLoader.hh
)
endif()

if(${UNIX})
list(APPEND ${PROJECT_NAME}_SOURCES
    ${CMAKE_CURRENT_LIST_DIR}/UnixDLoader.cpp
)
elseif(${WIN32})
list(APPEND ${PROJECT_NAME}_SOURCES
    ${CMAKE_CURRENT_LIST_DIR}/WinDLoader.cpp  
)
endif()
