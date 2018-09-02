#include "include.h"
#include "hell.h"


Thread_s	pThread[15];

HANDLE AddThread(void *szProcAddress, void *szArgs, int iPriority, char* szThreadName)
{
	DWORD dwThreadId;

	for (int i = 1; i < MAXTHREADS; i++) 
	{
		if (!pThread[i].szName)
		{
			// Start a thread, after placing a exception handler
			__try 
			{
				pThread[i].hThreadId = realloc(0, sizeof(HANDLE));
				pThread[i].hThreadId = CreateThread(NULL, 0, (unsigned long (__stdcall *)(void *))szProcAddress, (LPVOID)szArgs, 0, &dwThreadId);

				if(iPriority == 0)
					SetThreadPriority(pThread[i].hThreadId, THREAD_PRIORITY_IDLE);
				else 
					if(iPriority == 1)
						SetThreadPriority(pThread[i].hThreadId, THREAD_PRIORITY_LOWEST);
				else
					if(iPriority == 2)
						SetThreadPriority(pThread[i].hThreadId, THREAD_PRIORITY_BELOW_NORMAL);
				else
					if(iPriority == 4)
						SetThreadPriority(pThread[i].hThreadId, THREAD_PRIORITY_ABOVE_NORMAL);
				else
					if(iPriority == 5)
						SetThreadPriority(pThread[i].hThreadId, THREAD_PRIORITY_HIGHEST);
			}

			__except(1) 
			{ 
				// exception handler :D
			}

			if (!pThread[i].hThreadId) 
				return 0;

			pThread[i].szName			= szThreadName;
			pThread[i].nThreadId		= i;
			pThread[i].nThreadPriority	= iPriority;
			
			break;
		}
	}
	return pThread[i].hThreadId;
}

void DelThread(int iThreadId)
{
	if ((iThreadId > 1) && (iThreadId < MAXTHREADS)) 
	{
		// Disconect and clear the sockets
		closesocket(pThread[iThreadId].sServerSock);
		pThread[iThreadId].sServerSock		= 0;
		closesocket(pThread[iThreadId].sClientSock);
		pThread[iThreadId].sClientSock		= 0;

		// Memzero the thread name and priority
		pThread[iThreadId].szName			= NULL;
		pThread[iThreadId].nThreadPriority	= 0;

		// Clean the stack variables
		pThread[iThreadId].nThreadId		= 0;

		// Terminate and reset the thread
		HANDLE hThread						= pThread[iThreadId].hThreadId;
		pThread[iThreadId].hThreadId		= 0;
		TerminateThread(hThread,	0);
	}
}

int FindPid(char* szThreadName)
{
	int nCurrentThread = 0;

	for (int i = 1; i < MAXTHREADS; i++)
	{
		if (!pThread[i].szName)
			break;

		if (!_strcmpi(pThread[i].szName, szThreadName))
		{
			nCurrentThread = pThread[i].nThreadId;
			break;
		} 
	}
	return nCurrentThread;
}