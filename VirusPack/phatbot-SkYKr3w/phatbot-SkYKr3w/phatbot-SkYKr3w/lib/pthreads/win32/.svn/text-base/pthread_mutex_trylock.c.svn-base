/*
 * pthread_mutex_trylock.c
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
pthread_mutex_trylock(pthread_mutex_t *mutex)
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
      result = ptw32_mutex_check_need_init(mutex);
    }

  mx = *mutex;

  if (result == 0)
    {
      if ( (PTW32_INTERLOCKED_LONG) PTW32_MUTEX_LOCK_IDX_INIT ==
	   ptw32_interlocked_compare_exchange((PTW32_INTERLOCKED_LPLONG) &mx->lock_idx,
					      (PTW32_INTERLOCKED_LONG) 0,
					      (PTW32_INTERLOCKED_LONG) PTW32_MUTEX_LOCK_IDX_INIT))
	{
	  mx->recursive_count = 1;
	  mx->ownerThread = (mx->kind != PTHREAD_MUTEX_FAST_NP
			     ? pthread_self()
			     : (pthread_t) PTW32_MUTEX_OWNER_ANONYMOUS);
	}
      else
	{
          if( mx->kind == PTHREAD_MUTEX_RECURSIVE_NP &&
              pthread_equal( mx->ownerThread, pthread_self() ) )
            {
              mx->recursive_count++;
            }
          else
            {
              result = EBUSY;
            }
	}
    }

  return(result);
}
