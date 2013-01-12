/*
 * -----------------------------------------------------------------------------
 * "THE BEER-WARE LICENSE" (Revision 42):
 * <duplom_t@epitech.eu> wrote this file. As long as you retain this notice you
 * can do whatever you want with this stuff. If we meet some day, and you think
 * this stuff is worth it, you can buy me a beer in return Thomas Duplomb
 * -----------------------------------------------------------------------------
 */

#include "socketInit.hh"
#include <stdlib.h>

static void    shutdownSocket(void) {
#ifdef _WIN32
	WSACleanup();
#endif
}

void    socketInit()
{
    static bool isInit = false;

    if (!isInit) {
#ifdef _WIN32
        WSADATA WsaData;
        WSAStartup( MAKEWORD(2,2), &WsaData );
#endif
        isInit = true;
        atexit(&shutdownSocket);
    }
}
