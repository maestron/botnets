
#include "Globals.h"
#ifndef __THREAD_H__
#define __THREAD_H__

// Add a new thread to the threading pool
HANDLE AddThread(void *szProcAddress, void *szArgs, int iPriority, char* szThreadName);
// Remove and clean a thread from the threading pool
void DelThread(int iThreadId);
// Find the given thread by name
int FindPid(char* szThreadName);
// List all running threads
void ListThreads();

// Thread creating structure
struct Thread_s
{
	char*		szName;				// Name of the thread we add
	HANDLE		hThreadId;			// Pointer to the threadid
	int			nThreadId;			// Number of the thread in the threading pool
	int			nThreadPriority;	// Priority of the given thread
	
	SOCKET		sServerSock;		// Server socket
	SOCKET		sClientSock;		// Client socket
};

// Thread functions
extern Thread_s pThread[15];

#endif // __THREAD_H__

