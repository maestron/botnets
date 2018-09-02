#ifndef __RTHREAD__
#define __RTHREAD__

#include "../main.h"
#include "defines.h"
enum {
	DEAD_THREAD,
	TFTP_THREAD,
	HTTP_THREAD,
	SCAN_THREAD		// Port Scanner thread
};
typedef struct THREAD 
{
   char name[IRCLINE];
   int id; 
   int parent;
   DWORD pid;
   SOCKET sock;
   SOCKET csock;
   HANDLE tHandle;
   char nick[MAXNICKLEN];

} THREAD;

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
int killthreadid(int threadid, int threadnum);
BOOL killthread(int threadnum);
int killProcess(int pid);
int raddthread(char *name, int id, SOCKET sock);
int findthreadid(int threadid);
int findthreadnum(int threadid);
void clearthread(int threadnum);
#endif