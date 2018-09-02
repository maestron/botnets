/*
 * -------------------------------------------------------------
 *
 * Module: sem_trywait.c
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
sem_trywait (sem_t * sem)
     /*
      * ------------------------------------------------------
      * DOCPUBLIC
      *      This function tries to wait on a semaphore.
      *
      * PARAMETERS
      *      sem
      * 	     pointer to an instance of sem_t
      *
      * DESCRIPTION
      *      This function tries to wait on a semaphore. If the
      *      semaphore value is greater than zero, it decreases
      *      its value by one. If the semaphore value is zero, then
      *      this function returns immediately with the error EAGAIN
      *
      * RESULTS
      * 	     0		     successfully decreased semaphore,
      * 	     -1 	     failed, error in errno
      * ERRNO
      * 	     EAGAIN	     the semaphore was already locked,
      * 	     EINVAL	     'sem' is not a valid semaphore,
      * 	     ENOTSUP	     sem_trywait is not supported,
      * 	     EINTR	     the function was interrupted by a signal,
      * 	     EDEADLK	     a deadlock condition was detected.
      *
      * ------------------------------------------------------
      */
{
#ifdef NEED_SEM

  /*
   * not yet implemented!
   */
  errno = ENOTSUP;
  return -1;

#else /* NEED_SEM */

  int result = 0;

  if (sem == NULL || *sem == NULL)
    {
      result = EINVAL;
    }
  else if (WaitForSingleObject ((*sem)->sem, 0) == WAIT_TIMEOUT)
    {
      result = EAGAIN;
    }

  if (result != 0)
    {
      errno = result;
      return -1;
    }

  return 0;

#endif /* NEED_SEM */

}				/* sem_trywait */
