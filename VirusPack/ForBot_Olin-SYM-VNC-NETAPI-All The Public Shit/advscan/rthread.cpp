#include "rthread.h"
#include "defines.h"
#include "advscan.h"
#include "../sdcompat.h"
#include "../mainctrl.h"

void clearthread(int threadnum){
	THREAD * threads = g_cMainCtrl.m_cAdvScan.threads;
	threads[threadnum].tHandle = 0;
	threads[threadnum].id=0;
	threads[threadnum].parent=0;
	threads[threadnum].pid=0;
	threads[threadnum].sock=0;
	threads[threadnum].csock=0;
	threads[threadnum].name[0]='\0';
	threads[threadnum].nick[0]='\0';

	return;
}

BOOL killthread(int threadnum){
		THREAD * threads = g_cMainCtrl.m_cAdvScan.threads;

	BOOL threadkilled = FALSE;
				
	if ((threadnum>0) && (threadnum<MAXTHREADS)) {
		TerminateThread(threads[threadnum].tHandle, 0);
		if (threads[threadnum].tHandle != 0) 
			threadkilled = TRUE;

		threads[threadnum].tHandle = 0;
		threads[threadnum].id = 0;
		threads[threadnum].parent = 0;

		if(threads[threadnum].pid > 0)
			killProcess(threads[threadnum].pid);
		threads[threadnum].pid = 0; 
		
		threads[threadnum].name[0] = '\0';
		threads[threadnum].nick[0] = '\0';

		closesocket(threads[threadnum].sock);
		threads[threadnum].sock = 0;
		closesocket(threads[threadnum].csock);
		threads[threadnum].csock = 0;
	}

	return (threadkilled);
}


int killthreadid(int threadid, int threadnum){
	THREAD * threads = g_cMainCtrl.m_cAdvScan.threads;

	int numthreads=0;

	for (int i=0;i<MAXTHREADS;i++) {
		if (threads[i].id == threadid) {
			if (threadnum > 0) {
				if (threads[i].parent == threadnum || i == threadnum)
					if (killthread(i)) 
						numthreads++;
			} else {
				if (killthread(i)) 
					numthreads++;
			}
		}
	}

	return (numthreads);
}


int killProcess(int pid){
	int ret=1;

 	HANDLE pHandle;
	
	if ((pHandle = OpenProcess(PROCESS_ALL_ACCESS,FALSE,pid)) != NULL)
		if(!TerminateProcess(pHandle,0)) {
			ret=0;
			CloseHandle(pHandle);
		}

	return ret;
}

int findthreadid(int threadid){
	THREAD * threads = g_cMainCtrl.m_cAdvScan.threads;
	int numthreads=0;
	for (int i=0;i<MAXTHREADS;i++)if (threads[i].id == threadid)numthreads++;
	return (numthreads);
}

int findthreadnum(int threadid){
	THREAD * threads = g_cMainCtrl.m_cAdvScan.threads;
	int threadnum=0;
	for (int i=0;i<MAXTHREADS;i++)if (threads[i].id == threadid) {threadnum=i;break;}
	return (threadnum);
}

int raddthread(char *name, int id, SOCKET sock){
	THREAD * threads = g_cMainCtrl.m_cAdvScan.threads;
	int i;
	for (i = 0; i < MAXTHREADS; i++) {
		if (threads[i].name[0] == '\0') {
			strncpy(threads[i].name, name, sizeof(threads[i].name)-1);
			threads[i].id=id;
			threads[i].parent=0;
			threads[i].pid=0;
			threads[i].sock=sock;
			threads[i].nick[0]='\0';
			break;
		}
	}
	return i;
}
