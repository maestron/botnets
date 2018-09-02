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

class CThread
{
public:
	CThread();								// Constructor
	virtual ~CThread();						// Destructor

	static void InitPThreads();				// Performs pthreads initialization
	static void CleanupPThreads();			// Performs pthreads cleanup

	bool Start();							// This starts the thread
	void *Join();							// This waits for the thread to exit
	void Kill();							// This kills the thread

	pthread_t GetThread();					// This returns the thread structure

	void		*m_pArgs;					// A pointer to the arguments
protected:
	static void *RunWrapper(void *pThis);	// A static wrapper around the member function
	virtual void *Run()=0;					// This has to be overridden to create your own thread

	pthread_t	 m_tThread;					// The thread structure
};

#endif // __CTHREAD_H__
