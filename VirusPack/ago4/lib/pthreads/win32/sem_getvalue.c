/*
 * -------------------------------------------------------------
 *
 * Module: sem_getvalue.c
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

#include "pthread.h"
#include "semaphore.h"
#include "implement.h"


int
sem_getvalue(sem_t * sem, int * sval)
     /*
      * ------------------------------------------------------
      * DOCPUBLIC
      *      This function stores the current count value of the
      *      semaphore.
      * RESULTS
      *
      * Return value
      *
      *       0 		 sval has been set.
      *      -1 		 failed, error in errno
      *
      *  in global errno
      *
      *      EINVAL		 'sem' is not a valid semaphore,
      *      ENOSYS		 this function is not supported,
      *
      *
      * PARAMETERS
      *
      *      sem		 pointer to an instance of sem_t
      *
      *      sval		 pointer to int.
      *
      * DESCRIPTION
      *      This function stores the current count value of the semaphore
      *      pointed to by sem in the int pointed to by sval.
      */
{
  int result = 0;
	long value;
 
  if ( sem == NULL || *sem == NULL || sval == NULL )
    {
      result = EINVAL;
    }
  else
    {
			register sem_t s = *sem;
			
#ifdef NEED_SEM

			EnterCriticalSection(&s->sem_lock_cs);
			value = s->value;
			LeaveCriticalSection(&s->sem_lock_cs);

#else

      /*
       * There appears to be NO atomic means of determining the
       * value of the semaphore. Using only ReleaseSemaphore()
       * with either a zero or oversized count parameter has been
       * suggested but this trick doesn't produce consistent results
       * across Windows versions (the technique uses values that are
       * knowingly illegal but hopes to extract the current value
       * anyway - the zero parameter appears to work for Win9x but
       * neither work reliably for WinNT).
       *
       * The intrusive method below will give false results
       * at times but it at least errs on the side of
       * caution. Competing threads might occasionally believe
       * the semaphore has a count of one less than it actually
       * would have and possibly block momentarily unecessarily,
       * but they will never see a higher semaphore value than
       * there should be.
       *
       *
       * Multiple threads calling sem_getvalue() at the same time
       * may not all return the same value (assuming no calls to
       * other semaphore routines). They will always return the
       * correct value or a lesser value. This problem could be fixed
       * with a global or a per-semaphore critical section here.
       *
       * An equally approximate but IMO slightly riskier approach
       * would be to keep a separate per-semaphore counter and
       * decrement/increment it inside of sem_wait() and sem_post()
       * etc using the Interlocked* functions.
       */
      if ( WaitForSingleObject( s->sem, 0 ) == WAIT_TIMEOUT )
				{
					/* Failed - must be zero */
					value = 0;
				}
      else
				{
					/* Decremented semaphore - release it and note the value */
					(void) ReleaseSemaphore( s->sem, 1L, &value);
					value++;
				}

#endif
    }


  if ( result != 0 )
    {
      errno = result;
      return -1;
    }

	*sval = value;
  return 0;

}   /* sem_getvalue */
