/*
 * -------------------------------------------------------------
 *
 * Module: sem_init.c
 *
 * Purpose:
 *	Semaphores aren't actually part of PThreads.
 *	They are defined by the POSIX Standard:
 *
 *		POSIX 1003.1-2001
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

#ifndef _UWIN
#   include <process.h>
#endif

#include "pthread.h"
#include "semaphore.h"
#include "implement.h"

int
sem_init (sem_t * sem, int pshared, unsigned int value)
     /*
      * ------------------------------------------------------
      * DOCPUBLIC
      *      This function initializes a semaphore. The
      *      initial value of the semaphore is 'value'
      *
      * PARAMETERS
      *      sem
      * 	     pointer to an instance of sem_t
      *
      *      pshared
      * 	     if zero, this semaphore may only be shared between
      * 	     threads in the same process.
      * 	     if nonzero, the semaphore can be shared between
      * 	     processes
      *
      *      value
      * 	     initial value of the semaphore counter
      *
      * DESCRIPTION
      *      This function initializes a semaphore. The
      *      initial value of the semaphore is set to 'value'.
      *
      * RESULTS
      * 	     0		     successfully created semaphore,
      * 	     -1 	     failed, error in errno
      * ERRNO
      * 	     EINVAL	     'sem' is not a valid semaphore,
      * 	     ENOSPC	     a required resource has been exhausted,
      * 	     ENOSYS	     semaphores are not supported,
      * 	     EPERM	     the process lacks appropriate privilege
      *
      * ------------------------------------------------------
      */
{
  int result = 0;
  sem_t s = NULL;

  if (pshared != 0)
    {
      /*
       * Creating a semaphore that can be shared between
       * processes
       */
      result = EPERM;

    }
  else
    {

      s = (sem_t) calloc (1, sizeof (*s));

      if (NULL == s)
				{
					result = ENOMEM;
				}

#ifdef NEED_SEM

      else
				{
					s->value = value;
					s->event = CreateEvent (NULL,
						PTW32_FALSE,	/* manual reset */
						PTW32_FALSE,	/* initial state */
						NULL);

					if (0 == s->event)
						{
							result = ENOSPC;
						}
					else
						{
							if (value != 0)
								{
									SetEvent(s->event);
								}

							InitializeCriticalSection(&s->sem_lock_cs);
						}
				}

#else /* NEED_SEM */

      s->sem = CreateSemaphore (NULL,			     /* Always NULL */
				(long) value,		     /* Initial value */
				(long) _POSIX_SEM_VALUE_MAX, /* Maximum value */
				NULL);			     /* Name */
			
      if (0 == s->sem)
				{
					result = ENOSPC;
				}

#endif /* NEED_SEM */

    }

  if (result != 0)
    {
      errno = result;
      return -1;
    }

  *sem = s;

  return 0;

}				/* sem_init */
