/*
 * pthread_mutex_timedlock.c
 *
 * Description:
 * This translation unit implements mutual exclusion (mutex) primitives.
 *
 * --------------------------------------------------------------------------
 *
 *      Pthreads-win32 - POSIX Threads Library for Win32
 *      Copyright(C) 1998 John E. Bossom
 *      Copyright(C) 1999,2003 Pthreads-win32 contributors
 * 
 *      Contact Email: rpj@callisto.canberra.edu.au
 * 
 *      The current list of contributors is contained
 *      in the file CONTRIBUTORS included with the source
 *      code distribution. The list can also be seen at the
 *      following World Wide Web location:
 *      http://sources.redhat.com/pthreads-win32/contributors.html
 * 
 *      This library is free software; you can redistribute it and/or
 *      modify it under the terms of the GNU Lesser General Public
 *      License as published by the Free Software Foundation; either
 *      version 2 of the License, or (at your option) any later version.
 * 
 *      This library is distributed in the hope that it will be useful,
 *      but WITHOUT ANY WARRANTY; without even the implied warranty of
 *      MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 *      Lesser General Public License for more details.
 * 
 *      You should have received a copy of the GNU Lesser General Public
 *      License along with this library in the file COPYING.LIB;
 *      if not, write to the Free Software Foundation, Inc.,
 *      59 Temple Place - Suite 330, Boston, MA 02111-1307, USA
 */

#ifndef _UWIN
#   include <process.h>
#endif
#ifndef NEED_FTIME
#include <sys/timeb.h>
#endif
#include "pthread.h"
#include "implement.h"


static INLINE int
ptw32_timed_semwait (sem_t * sem, const struct timespec * abstime)
     /*
      * ------------------------------------------------------
      * DESCRIPTION
      *      This function waits on a POSIX semaphore. If the
      *      semaphore value is greater than zero, it decreases
      *      its value by one. If the semaphore value is zero, then
      *      the calling thread (or process) is blocked until it can
      *      successfully decrease the value or until abstime.
      *      If abstime has passed when this routine is called then
      *      it returns a result to indicate this.
      *
      *      If 'abstime' is a NULL pointer then this function will
      *      block until it can successfully decrease the value or
      *      until interrupted by a signal.
      *
      *      Unlike sem_timedwait(), this routine is not a cancelation point.
      *
      *      Unlike sem_timedwait(), this routine is non-cancelable.
      *
      * RESULTS
      * 	     2		     abstime has passed already
      * 	     1		     abstime timed out while waiting
      * 	     0		     successfully decreased semaphore,
      * 	     -1 	     failed, error in errno.
      * ERRNO
      * 	     EINVAL	     'sem' is not a valid semaphore,
      * 	     ENOSYS	     semaphores are not supported,
      * 	     EINTR	     the function was interrupted by a signal,
      * 	     EDEADLK	     a deadlock condition was detected.
      *
      * ------------------------------------------------------
      */
{
  int result = 0;

#ifdef NEED_FTIME

  struct timespec currSysTime;

#else /* NEED_FTIME */

  struct _timeb currSysTime;

#endif /* NEED_FTIME */

  const DWORD NANOSEC_PER_MILLISEC = 1000000;
  const DWORD MILLISEC_PER_SEC = 1000;
  DWORD milliseconds;
  DWORD status;

  if (sem == NULL)
    {
      result = EINVAL;
    }
  else
    {
      if (abstime == NULL)
	{
	  milliseconds = INFINITE;
	}
      else
	{
	  /* 
	   * Calculate timeout as milliseconds from current system time. 
	   */
					
	  /* get current system time */
					
#ifdef NEED_FTIME
					
	  {
	    FILETIME ft;
	    SYSTEMTIME st;
						
	    GetSystemTime(&st);
	    SystemTimeToFileTime(&st, &ft);
	    /*
	     * GetSystemTimeAsFileTime(&ft); would be faster,
	     * but it does not exist on WinCE
	     */
	    
	    ptw32_filetime_to_timespec(&ft, &currSysTime);
	  }
					
	  /*
	   * subtract current system time from abstime
	   */
	  milliseconds = (abstime->tv_sec - currSysTime.tv_sec) * MILLISEC_PER_SEC;
	  milliseconds += ((abstime->tv_nsec - currSysTime.tv_nsec)
			   + (NANOSEC_PER_MILLISEC/2)) / NANOSEC_PER_MILLISEC;

#else /* NEED_FTIME */
	  _ftime(&currSysTime);

	  /*
	   * subtract current system time from abstime
	   */
	  milliseconds = (abstime->tv_sec - currSysTime.time) * MILLISEC_PER_SEC;
	  milliseconds += ((abstime->tv_nsec + (NANOSEC_PER_MILLISEC/2)) / NANOSEC_PER_MILLISEC)
            - currSysTime.millitm;

#endif /* NEED_FTIME */

	  if (((int) milliseconds) < 0)
	    {
	      return 2;
	    }
	}

#ifdef NEED_SEM

      status = WaitForSingleObject( (*sem)->event, milliseconds );

#else /* NEED_SEM */
	    
      status = WaitForSingleObject( (*sem)->sem, milliseconds );

#endif

      if (status == WAIT_OBJECT_0)
	{

#ifdef NEED_SEM

	  ptw32_decrease_semaphore(sem);

#endif /* NEED_SEM */

	  return 0;
	}
      else if (status == WAIT_TIMEOUT)
	{
	  return 1;
	}
      else
	{
	  result = EINVAL;
	}
    }

  if (result != 0)
    {
      errno = result;
      return -1;
    }

  return 0;

}				/* ptw32_timed_semwait */


int
pthread_mutex_timedlock(pthread_mutex_t *mutex, const struct timespec *abstime)
{
  int result = 0;
  pthread_mutex_t mx;

#ifdef NEED_SEM
  errno = ENOTSUP;
  return -1;
#endif

  if (mutex == NULL || *mutex == NULL)
    {
      return EINVAL;
    }

  /*
   * We do a quick check to see if we need to do more work
   * to initialise a static mutex. We check
   * again inside the guarded section of ptw32_mutex_check_need_init()
   * to avoid race conditions.
   */
  if (*mutex == PTHREAD_MUTEX_INITIALIZER)
    {
      if ((result = ptw32_mutex_check_need_init(mutex)) != 0)
	{
	  return(result);
	}
    }

  mx = *mutex;

  if( 0 == InterlockedIncrement( &mx->lock_idx ) )
    {
      mx->recursive_count = 1;
      mx->ownerThread = (mx->kind != PTHREAD_MUTEX_FAST_NP
			 ? pthread_self()
			 : (pthread_t) PTW32_MUTEX_OWNER_ANONYMOUS);
    }
  else
    {
      if( mx->kind != PTHREAD_MUTEX_FAST_NP &&
	  pthread_equal( mx->ownerThread, pthread_self() ) )
	{
	  (void) InterlockedDecrement( &mx->lock_idx );

	  if( mx->kind == PTHREAD_MUTEX_RECURSIVE_NP )
	    {
	      mx->recursive_count++;
	    }
	  else
	    {
	      result = EDEADLK;
	    }
	}
      else
	{
	  if (abstime == NULL)
	    {
	      result = EINVAL;
	    }
	  else
	    {
	      switch (ptw32_timed_semwait( &mx->wait_sema, abstime ))
		{
		case 0: /* We got the mutex. */
		  {
		    mx->recursive_count = 1;
		    mx->ownerThread = (mx->kind != PTHREAD_MUTEX_FAST_NP
				       ? pthread_self()
				       : (pthread_t) PTW32_MUTEX_OWNER_ANONYMOUS);
		    break;
		  }
		case 1: /* Timedout, try a second grab. */
		  {
		    int busy;

		    EnterCriticalSection(&mx->wait_cs);
		    
		    /*
		     * If we timeout, it is up to us to adjust lock_idx to say
		     * we're no longer waiting. If the mutex was also unlocked
		     * while we were timing out, and we simply return ETIMEDOUT,
		     * then wait_sema would be left in a state that is not consistent
		     * with the state of lock_idx.
		     *
		     * We must check to see if wait_sema has just been posted
		     * but we can't just call sem_getvalue - we must compete for
		     * the semaphore using sem_trywait(), otherwise we would need
		     * additional critical sections elsewhere, which would make the
		     * logic too inefficient.
		     *
		     * If sem_trywait returns EAGAIN then either wait_sema
		     * was given directly to another waiting thread or
		     * another thread has called sem_*wait() before us and
		     * taken the lock. Then we MUST decrement lock_idx and return
		     * ETIMEDOUT.
		     *
		     * Otherwise we MUST return success (because we have effectively
		     * acquired the lock that would have been ours had we not
		     * timed out), and NOT decrement lock_idx.
		     *
		     * We can almost guarrantee that EAGAIN is the only
		     * possible error, so no need to test errno.
		     */
		    
		    if ( -1 == (busy = sem_trywait( &mx->wait_sema )) )
		      {
			(void) InterlockedDecrement( &mx->lock_idx );
			result = ETIMEDOUT;
		      }
		    
		    LeaveCriticalSection(&mx->wait_cs);

		    if ( ! busy )
		      {
			/*
			 * We have acquired the lock on second grab - keep it.
			 */
			mx->recursive_count = 1;
			mx->ownerThread = (mx->kind != PTHREAD_MUTEX_FAST_NP
					   ? pthread_self()
					   : (pthread_t) PTW32_MUTEX_OWNER_ANONYMOUS);
		      }
		    break;
		  }
		case 2: /* abstime passed before we started to wait. */
		  {
		    /*
		     * If we timeout, it is up to us to adjust lock_idx to say
		     * we're no longer waiting.
		     *
		     * The owner thread may still have posted wait_sema thinking
		     * we were waiting. I believe we must check but then NOT do any
		     * programmed work if we have acquired the mutex because
		     * we don't how long ago abstime was. We MUST just release it
		     * immediately.
		     */
		    EnterCriticalSection(&mx->wait_cs);
		    
		    result = ETIMEDOUT;

		    if ( -1 == sem_trywait( &mx->wait_sema ) )
		      {
			(void) InterlockedDecrement( &mx->lock_idx );
		      }
		    else
		      {
			if ( InterlockedDecrement( &mx->lock_idx ) >= 0 )
			  {
			    /* Someone else is waiting on that mutex */
			    if ( sem_post( &mx->wait_sema ) != 0 )
			      {
				result = errno;
			      }
			  }
		      }
		    
		    LeaveCriticalSection(&mx->wait_cs);
		    break;
		  }
		default:
		  {
		    result = errno;
		    break;
		  }
		}
	    }
	}
    }

  return(result);
}
