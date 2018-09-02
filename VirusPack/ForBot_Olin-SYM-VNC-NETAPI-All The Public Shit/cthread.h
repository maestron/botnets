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

	void Suspend();							// This suspends the thread
	void Resume();							// This resumes the thread

	pthread_t GetThread();					// This returns the thread structure

	void		*m_pArgs;					// A pointer to the arguments


protected:
	static void *RunWrapper(void *pThis);	// A static wrapper around the member function
	virtual void *Run()=0;					// This has to be overridden to create your own thread

	int			 m_iPrioBackup;				// Backup value for the thread priority

	pthread_t	 m_tThread;					// The thread structure

	bool		 m_bRunning;				// Is the thread running?

};

#endif // __CTHREAD_H__
