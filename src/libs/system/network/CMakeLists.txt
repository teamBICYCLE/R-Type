################################################################################
# "THE BEER-WARE LICENSE" (Revision 42):
# <duplom_t@epitech.eu> wrote this file. As long as you retain this notice you
# can do whatever you want with this stuff. If we meet some day, and you think
# this stuff is worth it, you can buy me a beer in return Thomas Duplomb
################################################################################

list(APPEND ${PROJECT_NAME}_HEADERS
    ${CMAKE_CURRENT_LIST_DIR}/crossplateform_utils.h
    ${CMAKE_CURRENT_LIST_DIR}/Addr.hh
    ${CMAKE_CURRENT_LIST_DIR}/IAddr.hh  
    ${CMAKE_CURRENT_LIST_DIR}/ITcpSocket.hh  
    ${CMAKE_CURRENT_LIST_DIR}/IUdpSocket.hh  
    ${CMAKE_CURRENT_LIST_DIR}/Tcp.hh  
    ${CMAKE_CURRENT_LIST_DIR}/Udp.hh  
)
if(${UNIX})
list(APPEND ${PROJECT_NAME}_HEADERS
    ${CMAKE_CURRENT_LIST_DIR}/UnixTcp.hh  
   ${CMAKE_CURRENT_LIST_DIR}/UnixUdp.hh
)
elseif(${WIN32})
list(APPEND ${PROJECT_NAME}_HEADERS
    ${CMAKE_CURRENT_LIST_DIR}/WinTcp.hh
    ${CMAKE_CURRENT_LIST_DIR}/WinUdp.hh      
)
endif()

list(APPEND ${PROJECT_NAME}_SOURCES
    ${CMAKE_CURRENT_LIST_DIR}/Addr.cpp
)
if(${UNIX})
list(APPEND ${PROJECT_NAME}_SOURCES
    ${CMAKE_CURRENT_LIST_DIR}/UnixTcp.cpp
    ${CMAKE_CURRENT_LIST_DIR}/UnixUdp.cpp      
)
elseif(${WIN32})
list(APPEND ${PROJECT_NAME}_SOURCES
    ${CMAKE_CURRENT_LIST_DIR}/WinTcp.cpp
    ${CMAKE_CURRENT_LIST_DIR}/WinUdp.cpp      
)
endif()
