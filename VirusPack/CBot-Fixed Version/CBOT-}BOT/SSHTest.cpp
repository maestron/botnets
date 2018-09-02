#include "include.h"
#include "hell.h"

#ifndef SSH
int pvar = 23;
int tries;



int find_local_port() 
{
	for (tries = 20; tries > 0; tries--) 
	{
		SOCKET connecter = socket(AF_INET, SOCK_STREAM, 0);
		struct sockaddr_in connecter_addr;
		connecter_addr.sin_family = AF_INET;
		connecter_addr.sin_port = (unsigned)rand() % 512 + 512;
		connecter_addr.sin_addr.s_addr = htonl(INADDR_ANY);

		if (connecter == INVALID_SOCKET) 
		{
			return 0;
		}

		if (bind(connecter, (struct sockaddr FAR *)&connecter_addr, sizeof(connecter_addr)) != SOCKET_ERROR) 
		{
			closesocket(connecter);
			return connecter_addr.sin_port;
		} 
		else 
		if (WSAGetLastError() != WSAEADDRINUSE) 
		{
			closesocket(connecter);
			return 0;
		}
			closesocket(connecter);
	}
	return 0;
}

static int PASCAL FAR SSHconnect(SOCKET s, const struct sockaddr FAR *name, int namelen) 
{
	if (s == INVALID_SOCKET) 
	{
		struct sockaddr_in addr;
		addr.sin_family = AF_INET;
		addr.sin_port = htons(pvar);
		addr.sin_addr.s_addr = INADDR_ANY;
		memset(addr.sin_zero, 0, sizeof(addr.sin_zero));
		bind(s, (struct sockaddr FAR *)&addr, sizeof(addr));
	}
	return (s, name, namelen);
}
#endif