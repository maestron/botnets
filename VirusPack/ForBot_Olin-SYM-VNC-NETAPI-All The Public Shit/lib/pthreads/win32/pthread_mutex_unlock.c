/*
 * pthread_mutex_unlock.c
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

#include "pthread.h"
#include "implement.h"


int
pthread_mutex_unlock(pthread_mutex_t *mutex)
{
  int result = 0;
  pthread_mutex_t mx;

  if (mutex == NULL || *mutex == NULL)
    {
      return EINVAL;
    }

  mx = *mutex;

  /*
   * If the thread calling us holds the mutex then there is no
   * race condition. If another thread holds the
   * lock then we shouldn't be in here.
   */
  if (mx != PTHREAD_MUTEX_INITIALIZER)
    {
      if (mx->ownerThread == (pthread_t) PTW32_MUTEX_OWNER_ANONYMOUS
	  || pthread_equal(mx->ownerThread, pthread_self()))
	{
	  if( mx->kind != PTHREAD_MUTEX_RECURSIVE_NP
	      || 0 == --mx->recursive_count )
	    {
	      mx->ownerThread = NULL;
	      EnterCriticalSection( &mx->wait_cs );

	      if( InterlockedDecrement( &mx->lock_idx ) >= 0 )
		{
		  /* Someone is waiting on that mutex */
		  if (sem_post( &mx->wait_sema ) != 0)
		    {
		      result = errno;
		    }
		}

	      LeaveCriticalSection( &mx->wait_cs );
	    }
	}
      else
	{
	  result = EPERM;
	}
    }
  else
    {
      result = EINVAL;
    }

  return(result);
}
