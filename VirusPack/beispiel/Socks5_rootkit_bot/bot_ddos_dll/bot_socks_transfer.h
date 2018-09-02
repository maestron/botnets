#define my_FD_ISSET(fd, set) api.p__WSAFDIsSet((SOCKET)(fd), (fd_set FAR *)(set))

DWORD WINAPI TransferLoop( LPVOID pParam )
{
	int dwLen ;
	char *pszBuf ;
	PSOCKS_THREAD_INFO psInfo = (PSOCKS_THREAD_INFO)pParam;
	SOCKET srv = psInfo->hServer;
	SOCKET sck = psInfo->hClient ;

	pszBuf = ALLOC(pGlobOpt->dwMaxLoopBufferLen);


	for ( ;; )
	{
		if ( ( dwLen = recv( srv, pszBuf,pGlobOpt->dwMaxLoopBufferLen,0 ) ) <= 0 ) break ;
		if ( send( sck, pszBuf, dwLen, 0 ) <= 0 ) break ;
	}

	if(pszBuf)
		FREE(pszBuf);
#ifdef _DEBUG_
	DbgPrint("--- Exit thread %08X\n",psInfo->dwClientThreadId);
#endif
	psInfo->hThread = 0;
	api.pExitThread(-1);
	return 0;
}

DWORD WINAPI SocksLoopBytes(LPVOID pParam)
{
	DWORD	dwExitCode = 0;
	DWORD	dwLen = 0;
	DWORD	dwRet = 0;
	DWORD	dwError = 0;

	fd_set	fd;
	PVOID	pMem;
	struct timeval timeout;
	PSOCKS_THREAD_INFO psInfo = (PSOCKS_THREAD_INFO)pParam;

	pMem = ALLOC(pGlobOpt->dwMaxLoopBufferLen);
	if(!pMem)
	{
		dwExitCode = -1;
		goto end;
	}

	timeout.tv_sec = 10;

	while( 1 )
	{
		FD_ZERO(&fd);
		FD_SET(psInfo->hClient, &fd);
		FD_SET(psInfo->hServer, &fd);

		if(api.pselect(0, &fd, NULL, NULL, &timeout) > 0)
		{
			api.pSleep(50);
			if(my_FD_ISSET(psInfo->hClient,&fd))
			{
				memset(pMem, 0, pGlobOpt->dwMaxLoopBufferLen);
#ifdef _DEBUG_
				dwLen = socks_RECV(psInfo->hClient,pMem,pGlobOpt->dwMaxLoopBufferLen,"socks data from client");
#else
				dwLen = socks_RECV(psInfo->hClient,pMem,pGlobOpt->dwMaxLoopBufferLen,"");
#endif
				if( dwLen == -1 )
				{
					dwError = api.pWSAGetLastError();
					if(dwError != WSAEWOULDBLOCK)
					{
						DbgPrint("Recv from client error %d\n",api.pWSAGetLastError());
						break;
					}
				}
				
				if( dwLen > 0)
				{
#ifdef _DEBUG_
					dwRet = socks_SEND(psInfo->hServer,pMem,dwLen,"socks data to server");
#else
					dwRet = socks_SEND(psInfo->hServer,pMem,dwLen,"");
#endif
					if(	dwRet != dwLen || dwRet == -1) 
					{
						DbgPrint("Send to  server error %d\n",api.pWSAGetLastError());
						break;
					}
				}
				dwRet = dwLen = 0;
			}
			api.pSleep(50);
			if(my_FD_ISSET(psInfo->hServer,&fd))
			{
				memset(pMem, 0, pGlobOpt->dwMaxLoopBufferLen);
#ifdef _DEBUG_
				dwLen = socks_RECV(psInfo->hServer,pMem,pGlobOpt->dwMaxLoopBufferLen,"socks data from client");
#else
				dwLen = socks_RECV(psInfo->hServer,pMem,pGlobOpt->dwMaxLoopBufferLen,"");
#endif
				if( dwLen == -1 )
				{
					DbgPrint("Recv server error %d\n",api.pWSAGetLastError());
					break;
				}

				if( dwLen > 0)
				{
#ifdef _DEBUG_
					dwRet = socks_SEND(psInfo->hClient,pMem,dwLen,"socks data to server");
#else
					dwRet = socks_SEND(psInfo->hClient,pMem,dwLen,"");
#endif
					if(	dwRet != dwLen || dwRet == -1) 
					{
						DbgPrint("Send to client error %d\n",api.pWSAGetLastError());
						break;
					}
				}
				dwRet = dwLen = 0;
			}
		}
	}

end:
	if(pMem)
		FREE(pMem);

	api.pExitThread(dwExitCode);
	return dwExitCode;
}

DWORD WINAPI SocksLoopThread(LPVOID pParam)
{
	DWORD dwRet = 0;
	DWORD dwLen = 0;
	DWORD dwError = 0;
	void *pszBuf = NULL;
	fd_set fd;
	struct timeval timeout;
	PSOCKS_THREAD_INFO psInfo = (PSOCKS_THREAD_INFO)pParam;

	timeout.tv_sec = 10;
	pszBuf = ALLOC(pGlobOpt->dwMaxLoopBufferLen);
	if(!pszBuf)
		goto end;

	while (TRUE) 
	{
		FD_ZERO(&fd);
		FD_SET(psInfo->hClient, &fd);
			
		if(api.pselect(0, &fd, NULL, NULL, &timeout) > 0)
		{
			if(my_FD_ISSET(psInfo->hClient, &fd))
			{
				memset(pszBuf, 0, pGlobOpt->dwMaxLoopBufferLen);
				dwLen = socks_RECV(psInfo->hClient,pszBuf,pGlobOpt->dwMaxLoopBufferLen,""/*socks data*/);
				if( dwLen == -1 )
					break;
				
				if( dwLen > 0)
				{
					dwRet = socks_SEND(psInfo->hServer,pszBuf,dwLen,""/*socks data*/);
					if(	dwRet != dwLen || dwRet == -1) 
						break;
				}
				dwRet = dwLen = 0;
			}
		}
		api.pSleep(70);
	}

end:
	if(pszBuf)
	{
		memset(pszBuf,0,pGlobOpt->dwMaxLoopBufferLen);
		FREE(pszBuf);
	} 
    shutdown(psInfo->hClient, SD_BOTH);
    api.pclosesocket(psInfo->hClient);

#ifdef _DEBUG_
	DbgPrint("--- Exit thread %08X\n",psInfo->dwClientThreadId);
#endif
	psInfo->hThread = 0;
	api.pExitThread(-1);
	return -1;
}