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

CThread::CThread() {
}

CThread::~CThread() {
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
	if(!pthread_create(&m_tThread, NULL, &this->RunWrapper, this)) return true;
	return false;
}

void *CThread::Join() {
	void *pRetVal;
	pthread_join(m_tThread, &pRetVal);
	return pRetVal;
}

void CThread::Kill() {
	pthread_kill(m_tThread, SIGTERM);
}

pthread_t CThread::GetThread() {
	return m_tThread;
}

void *CThread::RunWrapper(void *pArgs) {
	CThread *pThread=(CThread*)pArgs;
	pThread->Run();
	return NULL;
}
