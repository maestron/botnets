/*
 * -------------------------------------------------------------
 *
 * Module: sem_destroy.c
 *
 * Purpose:
 *	Semaphores aren't actually part of the PThreads standard.
 *	They are defined by the POSIX Standard:
 *
 *		POSIX 1003.1b-1993	(POSIX.1b)
 *
 * -------------------------------------------------------------
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
#include "semaphore.h"
#include "implement.h"


int
sem_destroy (sem_t * sem)
     /*
      * ------------------------------------------------------
      * DOCPUBLIC
      *      This function destroys an unnamed semaphore.
      *
      * PARAMETERS
      *      sem
      * 	     pointer to an instance of sem_t
      *
      * DESCRIPTION
      *      This function destroys an unnamed semaphore.
      *
      * RESULTS
      * 	     0		     successfully destroyed semaphore,
      * 	     -1 	     failed, error in errno
      * ERRNO
      * 	     EINVAL	     'sem' is not a valid semaphore,
      * 	     ENOSYS	     semaphores are not supported,
      * 	     EBUSY	     threads (or processes) are currently
      * 				     blocked on 'sem'
      *
      * ------------------------------------------------------
      */
{
  int result = 0;
  sem_t s = NULL;

  if (sem == NULL || *sem == NULL)
    {
      result = EINVAL;
    }
  else
    {
      s = *sem;
      *sem = NULL;

#ifdef NEED_SEM

      if (! CloseHandle(s->event))
	{
	  *sem = s;
	  result = EINVAL;
	}
      else
	{
	  DeleteCriticalSection(&s->sem_lock_cs);
	}

#else /* NEED_SEM */

      if (! CloseHandle (s->sem))
	{
	  *sem = s;
	  result = EINVAL;
	}

#endif /* NEED_SEM */

    }

  if (result != 0)
    {
      errno = result;
      return -1;
    }

  free(s);

  return 0;

}				/* sem_destroy */
