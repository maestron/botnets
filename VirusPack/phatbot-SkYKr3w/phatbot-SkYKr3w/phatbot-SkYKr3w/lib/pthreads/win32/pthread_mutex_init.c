/*
 * pthread_mutex_init.c
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
pthread_mutex_init(pthread_mutex_t *mutex, const pthread_mutexattr_t *attr)
{
  int result = 0;
  pthread_mutex_t mx;

  if (mutex == NULL)
    {
      return EINVAL;
    }

  if (attr != NULL
      && *attr != NULL
      && (*attr)->pshared == PTHREAD_PROCESS_SHARED
      )
    {
      /*
       * Creating mutex that can be shared between
       * processes.
       */
#if _POSIX_THREAD_PROCESS_SHARED

      /*
       * Not implemented yet.
       */

#error ERROR [__FILE__, line __LINE__]: Process shared mutexes are not supported yet.

#else

      return ENOSYS;

#endif /* _POSIX_THREAD_PROCESS_SHARED */

    }

  mx = (pthread_mutex_t) calloc(1, sizeof(*mx));

  if (mx == NULL)
    {
      result = ENOMEM;
    }
  else
    {
      mx->lock_idx = PTW32_MUTEX_LOCK_IDX_INIT;
      mx->recursive_count = 0;
      mx->kind = (attr == NULL || *attr == NULL
		  ? PTHREAD_MUTEX_DEFAULT
		  : (*attr)->kind);
      mx->ownerThread = NULL;

      if ( 0 != sem_init( &mx->wait_sema, 0, 0 ))
	{
	  result = EAGAIN;
	  free(mx);
	  mx = NULL;
	}
      else
	{
	  InitializeCriticalSection( &mx->wait_cs );
	}
    }

  *mutex = mx;

  return(result);
}
