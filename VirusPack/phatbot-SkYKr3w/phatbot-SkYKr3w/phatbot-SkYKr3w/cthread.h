

#ifndef __CTHREAD_H__
#define __CTHREAD_H__

#include <list>
using namespace std;

class CMutex
{
public:
					 CMutex();						// Constructor
	virtual			~CMutex();						// Destructor

	void			 Lock();						// Lock the mutex
	void			 Unlock();						// Unlock the mutex
private:
#ifndef AGOBOT_PLUGIN_BUILD
	pthread_mutex_t	 m_mMutex;						// The mutex structure
#endif // AGOBOT_PLUGIN_BUILD
};

class CThread
{
public:
					 CThread();						// Constructor
	virtual			~CThread();						// Destructor

	static void		 InitPThreads();				// Performs pthreads initialization, and creates cleanup thread
	static void		 CleanupPThreads();				// Performs pthreads cleanup, and destroys cleanup thread

	bool			 Start(	bool bDynamic=true, 
							bool bRestart=false,
							bool bRealtime=false);	// This starts the thread
	void			 Kill();						// This kills the thread
	int				 Join();						// Join the thread
	bool			 IsRunning() { return m_bRunning; }	// Is the thread running ?

	void			*m_pArgs;						// A pointer to the arguments
	bool			 m_bDynamic;					// Is this object allocated using new operator ?

	CMutex			 m_mRunning;					// Locked when thread is running
	char			*m_szType;						// The threads type
protected:
	static void		*RunWrapper(void *pThis);		// A static wrapper around the member function
	virtual void	*Run()=0;						// This has to be overridden to create your own thread

	int				 m_iPrioBackup;					// Backup value for the thread priority

#ifndef AGOBOT_PLUGIN_BUILD
	pthread_t		 m_tThread;						// The thread structure
	pthread_attr_t	 m_aAttr;						// The thread attributes				
#endif // AGOBOT_PLUGIN_BUILD

	bool			 m_bRunning;					// Is the thread running ?
	bool			 m_bRestart;					// Restart this thread if it crashed ?
};

class CCleanupThread : public CThread
{
public:
					 CCleanupThread();				// Constructor

	void			*Run();							// Thread function

	void			 Schedule(CThread *pThread);	// Schedule the specified thread for cleanup
	void			 Cleanup();						// Do the cleanup
private:
	CMutex			 m_mLock;						// The thread lock
	list<CThread*>	 m_lQueue;						// The cleanup queue
};

#endif // __CTHREAD_H__
