

#ifndef NO_NETINFO
#include "bt1.h"

//Get Connection Info (IP & Host)
void get_connection_info(SOCKET bsock, char *szBuffer)
{
	char szHost[LOWBUF];
	SOCKADDR sa;
	int sas;

#ifndef NO_DEBUG
		printf("[DEBUG] Getting connection ip and host, getconnectioninfo()...\n");
#endif

	if (gethostname(szHost, sizeof(szHost)) == SOCKET_ERROR) return;
		sas = sizeof(sa);
		memset(&sa, 0, sizeof(sa));
		getsockname(bsock, &sa, &sas);
		sprintf(szBuffer, "local IP address: %d.%d.%d.%d. connected from: %s", (BYTE)sa.sa_data[2], (BYTE)sa.sa_data[3], (BYTE)sa.sa_data[4], (BYTE)sa.sa_data[5], szHost);
}

//Get ConnectionType
void get_connection_type(char *szBuffer)
{
	char szName[LOWBUF];
	DWORD dwCon;

#ifndef NO_DEBUG
		printf("[DEBUG] Getting connection type, getconnectiontype()...\n");
#endif

		InternetGetConnectedStateEx(&dwCon, szName, sizeof(szName), 0);
    if (dwCon & INTERNET_CONNECTION_MODEM == INTERNET_CONNECTION_MODEM) sprintf(szBuffer, "connection type: dial-up (%s)", szName);
//	else if (dwCon & INTERNET_CONNECTION_LAN == INTERNET_CONNECTION_LAN) sprintf(szBuffer, "connection type: LAN (%s)", szName);
//	else if (dwCon & INTERNET_CONNECTION_PROXY == INTERNET_CONNECTION_PROXY) sprintf(szBuffer, "connection type: proxy (%s)", szName);
//	else sprintf(szBuffer, "connection type: unknown (%s)", szName);
	else sprintf(szBuffer, "connection type: LAN (%s)", szName);
	return;
}

//Get Net Info
void get_netinfo(SOCKET bsock, char *szBuffer)
{
	char szNetBuff[MEDBUF];

#ifndef NO_DEBUG
		printf("[DEBUG] Getting connection info, getnetinfo()...\n");
#endif

//Get Connection Type
		get_connection_type(szNetBuff);
		strcat(szBuffer, szNetBuff);
		strcat(szBuffer, ". ");
//Get Connection Info
		get_connection_info(bsock, szNetBuff);
		strcat(szBuffer, szNetBuff);
		return;
}
#endif