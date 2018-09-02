#include "includes.h"
#include "externs.h"

struct threads thread[512];
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
