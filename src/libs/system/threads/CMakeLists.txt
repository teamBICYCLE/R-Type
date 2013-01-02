################################################################################
# "THE BEER-WARE LICENSE" (Revision 42):
# <duplom_t@epitech.eu> wrote this file. As long as you retain this notice you
# can do whatever you want with this stuff. If we meet some day, and you think
# this stuff is worth it, you can buy me a beer in return Thomas Duplomb
################################################################################

list(APPEND ${PROJECT_NAME}_HEADERS
    ${CMAKE_CURRENT_LIST_DIR}/IThread.hh
    ${CMAKE_CURRENT_LIST_DIR}/IMutex.hh
)
if(UNIX)
list(APPEND ${PROJECT_NAME}_HEADERS
    ${CMAKE_CURRENT_LIST_DIR}/UnixThread.hh
    ${CMAKE_CURRENT_LIST_DIR}/UnixMutex.hh
)
elseif(WIN32)
list(APPEND ${PROJECT_NAME}_HEADERS
    ${CMAKE_CURRENT_LIST_DIR}/WinMutex.hh
    ${CMAKE_CURRENT_LIST_DIR}/WinThread.hh
)
endif()

if(UNIX)
list(APPEND ${PROJECT_NAME}_SOURCES
    ${CMAKE_CURRENT_LIST_DIR}/UnixThread.cpp
    ${CMAKE_CURRENT_LIST_DIR}/UnixMutex.cpp
)
elseif(WIN32)
list(APPEND ${PROJECT_NAME}_SOURCES
    ${CMAKE_CURRENT_LIST_DIR}/WinThread.cpp      
    ${CMAKE_CURRENT_LIST_DIR}/WinMutex.cpp    
)
endif()
