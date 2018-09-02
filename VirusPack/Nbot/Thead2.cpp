#include "includes.h"

Thread_s	g_pThread[15];

HANDLE AddThread(void *szProcAddress, void *szArgs, int iPriority, char* szThreadName)
{
	DWORD dwThreadId;
	
	for (int i = 1; i < MAXTHREADS; i++) 
	{
		if (!g_pThread[i].szName)
		{
			// Start a thread, after placing a exception handler
			__try 
			{
				g_pThread[i].hThreadId = realloc(0, sizeof(HANDLE));
				g_pThread[i].hThreadId = CreateThread(NULL, 0, (unsigned long (__stdcall *)(void *))szProcAddress, (LPVOID)szArgs, 0, &dwThreadId);
				
				if(iPriority == 0)
					SetThreadPriority(g_pThread[i].hThreadId, THREAD_PRIORITY_IDLE);
				else 
					if(iPriority == 1)
						SetThreadPriority(g_pThread[i].hThreadId, THREAD_PRIORITY_LOWEST);
					else
						if(iPriority == 2)
							SetThreadPriority(g_pThread[i].hThreadId, THREAD_PRIORITY_BELOW_NORMAL);
						else
							if(iPriority == 4)
								SetThreadPriority(g_pThread[i].hThreadId, THREAD_PRIORITY_ABOVE_NORMAL);
							else
								if(iPriority == 5)
									SetThreadPriority(g_pThread[i].hThreadId, THREAD_PRIORITY_HIGHEST);
			}
			
			__except(1) 
			{ 
				// exception handler :D
			}
			
			if (!g_pThread[i].hThreadId) 
				return 0;
			
			g_pThread[i].szName			= szThreadName;
			g_pThread[i].nThreadId		= i;
			g_pThread[i].nThreadPriority	= iPriority;
			
			break;
		}
	}
	return g_pThread[i].hThreadId;
}

void DelThread(int iThreadId)
{
	if ((iThreadId > 1) && (iThreadId < MAXTHREADS)) 
	{
		// Disconect and clear the sockets
		closesocket(g_pThread[iThreadId].sServerSock);
		g_pThread[iThreadId].sServerSock		= 0;
		closesocket(g_pThread[iThreadId].sClientSock);
		g_pThread[iThreadId].sClientSock		= 0;
		
		// Memzero the thread name and priority
		g_pThread[iThreadId].szName			= NULL;
		g_pThread[iThreadId].nThreadPriority	= 0;
		
		// Clean the stack variables
		g_pThread[iThreadId].nThreadId		= 0;
		
		// Terminate and reset the thread
		HANDLE hThread						= g_pThread[iThreadId].hThreadId;
		g_pThread[iThreadId].hThreadId		= 0;
		TerminateThread(hThread,	0);
	}
}

int FindPid(char* szThreadName)
{
	int nCurrentThread = 0;
	
	for (int i = 1; i < MAXTHREADS; i++)
	{
		if (!g_pThread[i].szName)
			break;
		
		if (!_strcmpi(g_pThread[i].szName, szThreadName))
		{
			nCurrentThread = g_pThread[i].nThreadId;
			break;
		} 
	}
	return nCurrentThread;
}
