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

#ifndef __CTHREAD_H__
#define __CTHREAD_H__

#include <list>
using namespace std;

class CMutex
{
public:
					 CMutex();							// Constructor
	virtual			~CMutex();							// Destructor

	void			 Lock();							// Lock the mutex
	void			 Unlock();							// Unlock the mutex
private:
#ifdef WIN32
	bool			 m_bLocked;							// Is the mutex locked ?
#else
#ifndef AGOBOT_PLUGIN_BUILD
	pthread_mutex_t	 m_mMutex;							// The mutex structure
#endif // AGOBOT_PLUGIN_BUILD
#endif // WIN32
};

class CThread
{
public:
					 CThread();							// Constructor
	virtual			~CThread();							// Destructor

	static void		 InitPThreads();					// Performs pthreads initialization, and creates cleanup thread
	static void		 CleanupPThreads();					// Performs pthreads cleanup, and destroys cleanup thread

	bool			 Start(	bool bDynamic=true, 
							bool bRestart=false,
							bool bRealtime=false);		// This starts the thread
	void			 Kill();							// This kills the thread
	int				 Join();							// Join the thread
	bool			 IsRunning() { return m_bRunning; }	// Is the thread running ?

	void			*m_pArgs;							// A pointer to the arguments
	bool			 m_bDynamic;						// Is this object allocated using new operator ?

	CMutex			 m_mRunning;						// Locked when thread is running
	char			*m_szType;							// The threads type
protected:
	static void		*RunWrapper(void *pThis);			// A static wrapper around the member function
	virtual void	*Run()=0;							// This has to be overridden to create your own thread

	int				 m_iPrioBackup;						// Backup value for the thread priority

#ifdef WIN32
	HANDLE			 m_hThread;							// The handle to the thread
	DWORD			 m_dwThreadId;						// The thread id
#else
#ifndef AGOBOT_PLUGIN_BUILD
	pthread_t		 m_tThread;							// The thread structure
	pthread_attr_t	 m_aAttr;							// The thread attributes				
#endif // AGOBOT_PLUGIN_BUILD
#endif // WIN32

	bool			 m_bRunning;						// Is the thread running ?
	bool			 m_bRestart;						// Restart this thread if it crashed ?
};

class CCleanupThread : public CThread
{
public:
					 CCleanupThread();					// Constructor

	void			*Run();								// Thread function

	void			 Schedule(CThread *pThread);		// Schedule the specified thread for cleanup
	void			 Cleanup();							// Do the cleanup
private:
	CMutex			 m_mLock;							// The thread lock
	list<CThread*>	 m_lQueue;							// The cleanup queue
};

#endif // __CTHREAD_H__
