#include "main.h"
#include "cthread.h"
#include "mainctrl.h"

CThread::CThread() {}

CThread::~CThread() {
	try {Kill();} catch(...) {
#ifdef DBGCONSOLE
		g_cMainCtrl.m_cConsDbg.Log(2, "CThread::~CThread(cthread.cpp): Kill() caused an exception.\n");
#endif // DBGCONSOLE
	}
}

void CThread::InitPThreads() {
#ifdef WIN32
	pthread_win32_process_attach_np();
	pthread_win32_thread_attach_np();
#else
#endif // WIN32
}

void CThread::CleanupPThreads() {
#ifdef WIN32
	pthread_win32_process_detach_np();
	pthread_win32_thread_detach_np();
#else
#endif // WIN32
}

bool CThread::Start() {
	try {
		if(!pthread_create(&m_tThread, NULL, &this->RunWrapper, this))
		{ m_bRunning=true; return true; } else { m_bRunning=false; return false; }
	} catch(...) {
#ifdef DBGCONSOLE
		g_cMainCtrl.m_cConsDbg.Log(2, "CThread::Start(cthread.cpp): pthread_create caused an exception.\n");
#endif // DBGCONSOLE
		m_bRunning=false; return false;
	}
}

void *CThread::Join() {
	try {
		if(m_bRunning) {
			void *pRetVal;
			pthread_join(m_tThread, &pRetVal);
			m_bRunning=false; return pRetVal;
		} else {
			return NULL;
		}
	} catch(...) {
#ifdef DBGCONSOLE
		g_cMainCtrl.m_cConsDbg.Log(2, "CThread::Join(cthread.cpp): pthread_join caused an exception.\n");
#endif // DBGCONSOLE
		return NULL;
	}
}

void CThread::Kill() {
	try {
		if(m_bRunning) {
			pthread_kill(m_tThread, SIGTERM);
			m_bRunning=false;
		}
	} catch(...) {
#ifdef DBGCONSOLE
		g_cMainCtrl.m_cConsDbg.Log(2, "CThread::Kill(cthread.cpp): pthread_kill caused an exception.\n");
#endif // DBGCONSOLE
	}
}

pthread_t CThread::GetThread() {
	return m_tThread;
}

void *CThread::RunWrapper(void *pArgs) {
	CThread *pThread=(CThread*)pArgs;
	try {
#ifdef _DEBUG
		_CrtCheckMemory();
#endif // _DEBUG

		pThread->Run();

#ifdef _DEBUG
		_CrtCheckMemory();
#endif // _DEBUG
	} catch(...) {
#ifdef DBGCONSOLE
		g_cMainCtrl.m_cConsDbg.Log(2, "CThread::RunWrapper(cthread.cpp): Thread caused an exception.\n");
#endif // DBGCONSOLE
		return NULL;
	}
	return NULL;
}

void CThread::Suspend() {
	try {
		if(m_bRunning) {
			sched_param param; int iPolicy;

			pthread_getschedparam(m_tThread, &iPolicy, &param);
			m_iPrioBackup=param.sched_priority;

			param.sched_priority=0;
			pthread_setschedparam(m_tThread, SCHED_FIFO, &param);
		}
	} catch(...) {
#ifdef DBGCONSOLE
		g_cMainCtrl.m_cConsDbg.Log(2, "CThread::Suspend(cthread.cpp): pthread_(get/set)schedparam caused an exception.\n");
#endif // DBGCONSOLE
	}
}

void CThread::Resume() {
	try {
		if(m_bRunning) {
			sched_param param; param.sched_priority=m_iPrioBackup;
			pthread_setschedparam(m_tThread, SCHED_FIFO, &param);
		}
	} catch(...) {
#ifdef DBGCONSOLE
		g_cMainCtrl.m_cConsDbg.Log(2, "CThread::Resume(cthread.cpp): pthread_setschedparam caused an exception.\n");
#endif // DBGCONSOLE
	}
}
