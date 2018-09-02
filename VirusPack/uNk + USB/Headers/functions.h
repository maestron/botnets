// kernel32.dll function variables
extern GCNA fGetComputerName;

// user32.dll function variables
extern IW fIsWindow;

// ws2_32.dll function variables
extern WSAS fWSAStartup;
extern WSASo fWSASocket;
extern WSAGLE fWSAGetLastError;
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
extern SSO fsetsockopt;
extern GSN fgetsockname;
extern GHN fgethostname;
extern GHBN fgethostbyname;
extern GPN fgetpeername;
extern CLSO fclosesocket;
extern SD fshutdown;
#ifndef NO_NETSTATP
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


// shell32.dll function variables
extern SE fShellExecute;
extern SHCN fSHChangeNotify;

extern PRFS fPathRemoveFileSpec;

// icmp.dll function variables
#ifndef NO_PINGUDP
extern ICF fIcmpCreateFile;
extern ISE fIcmpSendEcho;
extern ICH fIcmpCloseHandle;
#endif