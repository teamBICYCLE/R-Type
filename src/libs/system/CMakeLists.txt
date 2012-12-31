################################################################################
# "THE BEER-WARE LICENSE" (Revision 42):
# <duplom_t@epitech.eu> wrote this file. As long as you retain this notice you
# can do whatever you want with this stuff. If we meet some day, and you think
# this stuff is worth it, you can buy me a beer in return Thomas Duplomb
################################################################################

project(system)

if(UNIX)
list(APPEND ${PROJECT_NAME}_HEADERS
    dll/UnixDLoader.hh
)
elseif(WIN32)
list(APPEND ${PROJECT_NAME}_HEADERS
    dll/WinDLoader.hh
)
endif()

if(UNIX)
list(APPEND ${PROJECT_NAME}_SOURCES
    dll/UnixDLoader.cpp
)
elseif(WIN32)
list(APPEND ${PROJECT_NAME}_SOURCES
    dll/WinDLoader.cpp  
)
endif()

list(APPEND ${PROJECT_NAME}_HEADERS
    network/crossplateform_utils.h
    network/Addr.hh
    network/IAddr.hh  
    network/ITcpSocket.hh  
    network/IUdpSocket.hh  
    network/Tcp.hh  
    network/Udp.hh
)

list(APPEND ${PROJECT_NAME}_SOURCES
    network/Addr.cpp
    network/Tcp.cpp
    #network/Udp.cpp      
)

list(APPEND ${PROJECT_NAME}_HEADERS
    threads/IThread.hh
    threads/IMutex.hh
)
if(UNIX)
list(APPEND ${PROJECT_NAME}_HEADERS
    threads/UnixThread.hh
    threads/UnixMutex.hh
)
elseif(WIN32)
list(APPEND ${PROJECT_NAME}_HEADERS
    threads/WinThread.hh
    threads/WinMutex.hh
)
endif()

if(UNIX)
list(APPEND ${PROJECT_NAME}_SOURCES
    threads/UnixThread.cpp
    threads/UnixMutex.cpp
)
elseif(WIN32)
list(APPEND ${PROJECT_NAME}_SOURCES
    threads/WinThread.cpp      
    threads/WinMutex.cpp    
)
endif()

add_library(${PROJECT_NAME} SHARED
    ${${PROJECT_NAME}_HEADERS}
    ${${PROJECT_NAME}_SOURCES}
)

if(UNIX)
    target_link_libraries(${PROJECT_NAME} pthread)
endif(UNIX)
