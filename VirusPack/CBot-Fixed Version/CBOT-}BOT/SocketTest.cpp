#include "Include.h"
#include "Hell.h"


bool Bind(SOCKET sSock, const int iPort, bool bUDP) 
{
	SOCKADDR_IN siSockAddr;
	siSockAddr.sin_family		= AF_INET; 
	siSockAddr.sin_port			= htons(iPort); 
	siSockAddr.sin_addr.s_addr	= INADDR_ANY;
	
	BOOL bReUser = TRUE; 
	
	if (setsockopt(sSock, SOL_SOCKET, SO_REUSEADDR, (char *)&bReUser, sizeof(bReUser)))
		return false; 
	
	if(bind(sSock, (sockaddr*)&siSockAddr, sizeof(siSockAddr)) == SOCKET_ERROR)
		return false;
	
	if(!bUDP)
	{
		if (listen(sSock, 10) == SOCKET_ERROR)
			return false; 
	}
	
	return true;
}

char *ResolveHost(const char *szRemoteAddress)
{
	char szAddress[128];
	DWORD dwAddress;
	HOSTENT* lpHostent;
	
	if (!szRemoteAddress)
		strcpy(szAddress, "");
	else
		strcpy(szAddress, szRemoteAddress);
	
	if(lpHostent = gethostbyname(szAddress))
		return inet_ntoa(*(struct in_addr *) lpHostent->h_addr_list[0]);
	
	if((dwAddress = inet_addr(szAddress)) != INADDR_NONE)
	{
		if(lpHostent = gethostbyaddr((char *)&dwAddress, sizeof(struct in_addr), AF_INET))
			return lpHostent->h_name;
	}
	
	return NULL;
}

bool GetSocketAddress(SOCKET sSock, char* szOutput)
{
	LPHOSTENT lpHostent;
	SOCKADDR_IN siSockAddr;
	
	int iSockAddrLenght = sizeof(siSockAddr);
	
	if (getpeername(sSock, (LPSOCKADDR)&siSockAddr, &iSockAddrLenght))
		return false;
	
	if (!(lpHostent = gethostbyaddr((char *)&siSockAddr.sin_addr, sizeof(siSockAddr.sin_addr), PF_INET)))
		sprintf(szOutput, inet_ntoa(siSockAddr.sin_addr));
	else
		strcpy(szOutput, lpHostent->h_name);
	
	return true;
}