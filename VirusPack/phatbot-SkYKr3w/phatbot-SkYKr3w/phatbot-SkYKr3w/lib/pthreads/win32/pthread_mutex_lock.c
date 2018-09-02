/*
 * pthread_mutex_lock.c
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
#include "pthread.h"
#include "implement.h"


static INLINE int
ptw32_semwait (sem_t * sem)
     /*
      * ------------------------------------------------------
      * DESCRIPTION
      *      This function waits on a POSIX semaphore. If the
      *      semaphore value is greater than zero, it decreases
      *      its value by one. If the semaphore value is zero, then
      *      the calling thread (or process) is blocked until it can
      *      successfully decrease the value.
      *
      *      Unlike sem_wait(), this routine is non-cancelable.
      *
      * RESULTS
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

  DWORD status;

  if (sem == NULL)
    {
      result = EINVAL;
    }
  else
    {

#ifdef NEED_SEM

      status = WaitForSingleObject( (*sem)->event, INFINITE );

#else /* NEED_SEM */

      status = WaitForSingleObject( (*sem)->sem, INFINITE );

#endif

      if (status == WAIT_OBJECT_0)
	{

#ifdef NEED_SEM

	  ptw32_decrease_semaphore(sem);

#endif /* NEED_SEM */

	  return 0;
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

}				/* ptw32_semwait */


int
pthread_mutex_lock(pthread_mutex_t *mutex)
{
  int result = 0;
  pthread_mutex_t mx;


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

  if ( 0 == InterlockedIncrement( &mx->lock_idx ) )
    {
      mx->recursive_count = 1;
      mx->ownerThread = (mx->kind != PTHREAD_MUTEX_FAST_NP
			 ? pthread_self()
			 : (pthread_t) PTW32_MUTEX_OWNER_ANONYMOUS);
    }
  else
    {
      if ( mx->kind != PTHREAD_MUTEX_FAST_NP &&
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
	  if (ptw32_semwait( &mx->wait_sema ) == 0)
	    {
	      mx->recursive_count = 1;
	      mx->ownerThread = (mx->kind != PTHREAD_MUTEX_FAST_NP
				 ? pthread_self()
				 : (pthread_t) PTW32_MUTEX_OWNER_ANONYMOUS);
	    }
	  else
	    {
	      result = errno;
	    }
	}
    }

  return(result);
}
