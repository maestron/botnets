#define ERROR_EXIT() \
{	\
	bRet = FALSE;\
	goto end;	\
}

#ifdef _DEBUG_

#define ALLOC(a) MemAlloc(__FILE__,__LINE__,a);
#define FREE(a) MemFree(__FILE__,__LINE__,a);
#define DbgBreak() __asm { int 3 };
#define DbgPrint DbgPrintEx
#define DbgMsg DbgMsgEx
#define DumpMemory DumpMemoryEx
#define RECV() socks_RECV();
#define SEND() socks_SEND();

#else

#define DbgBreak
#define DbgMsg
#define DbgPrint
#define DumpMemory
#define ALLOC(a) VirtualAllocEx(api.pGetCurrentProcess(),NULL,a,MEM_COMMIT|MEM_RESERVE,PAGE_EXECUTE_READWRITE);
#define FREE(a) VirtualFreeEx(api.pGetCurrentProcess (),a,0,0);

#endif

//--------------------------------------------------------------------------------------
//+ DEBUG
void *MemAlloc(char *file,int line,DWORD dwSize);
void MemFree(char *file,int line,PVOID pMem);
void DumpMemoryEx(PVOID Buffer,ULONG Size,char *info);
void DbgPrintEx(char *msg,...);
	
	BOOLEAN bAllocated = FALSE;
	HANDLE	hConsole = 0;
	void DbgMsgEx(char *file, int line, char *msg, ...)
	{
#ifdef _DEBUG_
		char buff[2024], obuff[1024]="\0";
		va_list mylist;
		DWORD dwWrited;
		DWORD dwLastError = 0;

		if(!bAllocated)
			AllocConsole();
		
		if(!hConsole)
			hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
		
		va_start(mylist, msg);
		wvsprintf(buff, msg, mylist);	
		va_end(mylist);

		wsprintf(obuff, "%s(%d) : %s\n", file, line, buff);

		OutputDebugString((PVOID)obuff);
		WriteConsole(hConsole,(const VOID *)obuff,(DWORD)strlen(obuff),&dwWrited,0);
		dwLastError = GetLastError();
#endif
	}

	void DbgPrintEx(char *msg,...)
	{
#ifdef _DEBUG_
		char buff[1024], obuff[1024]="\0";
		va_list mylist;
		DWORD dwWrited;

		if(!bAllocated)
			AllocConsole();
		
		if(!hConsole)
			hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
		
		va_start(mylist, msg);
		wvsprintf(buff, msg, mylist);	
		va_end(mylist);
		OutputDebugString(obuff);
		WriteConsole(hConsole,(const VOID *)buff,(DWORD)strlen(buff),&dwWrited,0);		
#endif
	}

	void DumpMemoryEx(void *mem, ULONG len,char *info)
	{
#ifdef _DEBUG_
		unsigned char str[20];
		unsigned char *m = mem;
		ULONG i,j;
		DWORD dwCurThread = GetCurrentThreadId();
		ULONG b;
		PCHAR p = mem;

		DbgPrint("\n+------------------------------------------------+\n");
		DbgPrint("|[%s] TID [0x%08X] \n",info,dwCurThread);

		if(len < 8)
		{
			for (b = 0; b < len; b++) {
				if (b % 16 == 0)
					DbgPrint("|");
				 DbgPrint("%02X ", (p[b]) & 0xFF);
			}
			DbgPrint("\n|[%s]",info);
			DbgPrint("\n+------------------------------------------------+\n");
		}	else	{
			for (j=0; j<len/8; j++)
			{
				memset (str,0,sizeof str);
				for (i=0; i<8; i++) 
				{
					if (m[i] > ' ' && m[i] < '~')
						str[i]=m[i];
					else
						str[i]='.';
				}

				DbgPrint ("0x%08X  %02X %02X %02X %02X %02X %02X %02X %02X  %c%c%c%c%c%c%c%c \n",m, m[0], m[1], m[2], m[3], m[4], m[5], m[6], m[7], str[0], str[1], str[2], str[3], str[4], str[5], str[6], str[7] );

				m+=8;
			}
			DbgPrint("|[%s]",info);
			DbgPrint("\n+------------------------------------------------+\n");
		}
#endif
	}

void MemFree(char *file,int line,PVOID pMem)
{
	__try {
		if(VirtualFreeEx(GetCurrentProcess(),pMem,0,0))
		{
	#ifdef _DEBUG_MEMORY_
			DbgMsg(file,line,"Free memory at 0x%08X",pMem);
			dwFree++;
	#endif
		}	else	{
	#ifdef _DEBUG_MEMORY_
			DbgMsg(file,line,"Error free memory at 0x%08X",pMem);
	#endif
		}
	}	__except(EXCEPTION_EXECUTE_HANDLER)
	{
		DbgMsgEx(__FILE__,__LINE__,"On free memory exception! Fix it\n");
	}
}

void *MemAlloc(char *file,int line,DWORD dwSize)
{
	PVOID pMem = VirtualAllocEx(GetCurrentProcess(),NULL,dwSize,MEM_COMMIT|MEM_RESERVE,PAGE_EXECUTE_READWRITE);
	if(pMem){
		rtl_memset(pMem,0,dwSize);
#ifdef _DEBUG_MEMORY_
		DbgMsg(file,line,"Allocated %d bytes in %08X",dwSize,pMem);
		dwAllocated++;
#endif
	}	else	{
#ifdef _DEBUG_MEMORY_
		DbgMsg(file,line,"Error allocate %d bytes",dwSize,pMem);
#endif
	}
	return pMem;
}
 

int socks_RECV(	SOCKET hSocket,PVOID pMem,DWORD dwSize,char *szInfo)
{
	DWORD dwRet = 0;
	dwRet = api.precv(hSocket, pMem, dwSize, 0);
/*#ifdef _DEBUG_SOCKET_
	if(	dwRet == 0 ||
		dwRet == WSAECONNRESET )
	{
		DbgMsg(__FILE__,__LINE__,"Recv error %08X",WSAGetLastError());
	}	else	{*/
	if( dwRet > 0  && dwRet <= dwSize)
		DumpMemory(pMem,dwRet,szInfo);
/*	}
#endif*/
	return dwRet;
}

int socks_SEND(	SOCKET hSocket,
				PVOID pMem,
				DWORD dwSize,
				char *szInfo)
{
	DWORD dwRet = 0;
#ifdef _DEBUG_SOCKET_
	if(dwSize > 0)
		DumpMemory(pMem,dwSize,szInfo);
#endif
	dwRet = api.psend(hSocket,pMem,dwSize,0);
#ifdef _DEBUG_SOCKET_
	if(dwRet == SOCKET_ERROR )
	{
		DbgMsg(__FILE__,__LINE__,"Send error %08X",api.pWSAGetLastError());
	}
#endif
	return dwRet;
}


int socks_CONNECT(SOCKET s,const struct sockaddr* name,int namelen)
{
	int nRet = 0;
	struct sockaddr_in *sinfo = name;

	/*DbgPrint("--- Connect to %d.%d.%d.%d:%d\n",
		sinfo->sin_addr.S_un.S_un_b.s_b1,
		sinfo->sin_addr.S_un.S_un_b.s_b2,sinfo->sin_addr.S_un.S_un_b.s_b3,		sinfo->sin_addr.S_un.S_un_b.s_b4,
		htons(sinfo->sin_port));*/
	api.pconnect(s,name,namelen);
	return nRet;
}