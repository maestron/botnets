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
//extern char msg[256];
extern SOCKET sock;
extern char zipname[];
extern char insidezip[];
extern char szRegname[];


#ifndef NO_SFCDISABLE
extern char sfc_dllname[];
#endif


extern char dir_title[];

extern char process_title[];
extern char irc_title[];
//extern char scan_title[];
//extern char ftp_title[];
//extern char mirc_title[];
//extern char file_title[];
extern char download_title[];
extern char update_title[];
//extern char logic_title[];
//extern char reg_title[];
//extern char pstore_title[];
//extern char netstatp_title[];
extern char tcp_title[];
//extern char udp_title[];
//extern char speedtest_title[];
//extern char sock4_title[];
//extern char redirect_title[];
//extern char warn_title[];
//extern char sniffer_title[];
extern char imspread_title[];
extern char timspread_title[];
extern char aimspread_title[];
extern char msnworm_title[];
extern char Message[];
extern char str_msn_msg[];
//char str_msn_spread[]	= "[msn]: Message & Zipfile sent to: %d contacts.";

extern HANDLE ih;

//extern char exip[MAX_IP];
//extern char inip[MAX_IP];
extern char host[MAX_HOSTNAME];

extern DWORD dwstarted;
extern DWORD dwconnected;

extern char main_title[];
extern char threads_title[];
extern char sec_title[];
extern char unsec_title[];

extern THREAD threads[MAX_THREADS];

//extern char installedt[128];

extern HANDLE xetum;

// The login command needs extern for protocol.cpp
extern const char get_auth1[];
extern const char get_auth2[];
