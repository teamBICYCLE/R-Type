/*
 * ----------------------------------------------------------------------------
 * "THE BEER-WARE LICENSE" (Revision 42):
 * <duplom_t@epitech.eu> wrote this file. As long as you retain this notice you
 * can do whatever you want with this stuff. If we meet some day, and you think
 * this stuff is worth it, you can buy me a beer in return Thomas Duplomb
 * ----------------------------------------------------------------------------
 */

#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <stdint.h>
#include <iostream>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <netdb.h>
#include <string.h>
#include <stdint.h>

#include <string.h>


static void udpError(const char *msg)
{
	perror(msg);
    exit(errno);
}

static void createClient(const char *ip, const char *port)
{
	int s = socket(AF_INET, SOCK_DGRAM, 0);
    struct sockaddr_in sin;

    if (!s)
    	udpError("socket error");

	struct hostent *hostinfo = NULL;
	struct sockaddr_in to;
	int tosize = sizeof to;

	hostinfo = gethostbyname(ip);
	if (hostinfo == NULL)
	{
	    std::cerr << "Unknown host " << ip << std::endl;
	    exit(EXIT_FAILURE);
	}

	to.sin_addr = *(struct in_addr *) hostinfo->h_addr;
	to.sin_port = htons(atoi(port));
	to.sin_family = AF_INET;

	while (1)
	{
        uint32_t packet = 66;
		if (sendto(s, &packet, sizeof(packet), 0, (struct sockaddr *)(&to), tosize) < 0)
			udpError("sendto error");
	}
}

int main(int argc, const char *argv[])
{
    createClient(argv[1], argv[2]);
    return 0;
}
