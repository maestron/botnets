/*

    Reptile - a modular IRC bot for Win32
    Based on the rxBot core by Racerx90

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
	MAIN_THREAD,
	LOG_THREAD,
	PROC_THREAD,
	SECURE_THREAD,
	ASECURE_THREAD,
	WINDOW_THREAD,
	UNIGNORE_THREAD,
	LIST_THREAD,
	BOUNCER_THREAD,
	NETSTAT_THREAD,
	RUPTIME_THREAD,
	DRIVE_THREAD,
	FTPTRANS_THREAD,
	SCAN_THREAD,
	FTPD_THREAD,
	SPEEDTEST_THREAD,
	DDOS_THREAD,
	IDENT_THREAD,
	RCMD_THREAD,
	DCC_THREAD,
	DCCCHAT_THREAD,
	DOWNLOAD_THREAD,
	SNIFFER_THREAD,
	PSTORE_THREAD,
	SOCK4_THREAD,
	REDIRECT_THREAD,
};

typedef struct THREAD 
{
   char name[IRCLINE];
   int id; 
   int parent;
   DWORD pid;
   HANDLE tHandle;
//   SOCKET sock;
   SOCKET csock;
//   char nick[MAX_NICKLEN];

} THREAD;

// default new thread structure
typedef struct NTHREAD {
	void *conn;
	char target[128];
	int  threadnum;
	
	char *data1;
	char *data2;
	char *data3;

	BOOL bdata1;
	BOOL bdata2;
	BOOL bdata3;

	int idata1;
	int idata2;

	SOCKET sock;
	SOCKET csock;

	BOOL verbose;
	BOOL silent;
	BOOL gotinfo;

} NTHREAD;

/*
typedef struct TLIST
{
	SOCKET sock;
	char chan[128];
	int threadnum;
	BOOL full;
	BOOL notice;
	BOOL silent;
	BOOL gotinfo;

} TLIST;
*/

int addthread(int id, char *name,...);
BOOL killthread(int threadnum);
int killthreadall(void);
int killthreadid(int threadid, int threadnum=0);
void clearthread(int threadnum);
DWORD WINAPI ListThread(LPVOID param);
//void listthreads(char *target, void* conn, BOOL verbose, BOOL full);
void stopthread(char *target, void* conn, BOOL silent, BOOL verbose, char *thread, int threadid, char *desc);
int findthreadid(int threadid);
int findthreadnum(int threadid);

/*DWORD WINAPI ListThread(LPVOID param);
void listthreads(SOCKET sock, char *chan, BOOL notice, BOOL full=FALSE);
int findthreadid(int threadid);
void stopthread(SOCKET sock, char *chan, BOOL notice, BOOL silent, char *name, char *desc, int threadid, char *thread);
*/