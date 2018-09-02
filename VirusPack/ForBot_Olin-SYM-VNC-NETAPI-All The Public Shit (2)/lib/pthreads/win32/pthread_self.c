/*
 * pthread_self.c
 *
 * Description:
 * This translation unit implements miscellaneous thread functions.
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


pthread_t
pthread_self (void)
     /*
      * ------------------------------------------------------
      * DOCPUBLIC
      *      This function returns a reference to the current running
      *      thread.
      *
      * PARAMETERS
      *      N/A
      *
      *
      * DESCRIPTION
      *      This function returns a reference to the current running
      *      thread.
      *
      * RESULTS
      * 	     pthread_t	     reference to the current thread
      *
      * ------------------------------------------------------
      */
{
  pthread_t self;

#ifdef _UWIN
	if(!ptw32_selfThreadKey)
		return(NULL);
#endif

  self = (pthread_t) pthread_getspecific (ptw32_selfThreadKey);

  if (self == NULL)
    {
      /*
       * Need to create an implicit 'self' for the currently
       * executing thread.
       */
      self = ptw32_new();

      if (self != NULL)
	{
	  /*
	   * This is a non-POSIX thread which has chosen to call
	   * a POSIX threads function for some reason. We assume that
	   * it isn't joinable, but we do assume that it's
	   * (deferred) cancelable.
	   */
	  self->implicit = 1;
	  self->detachState = PTHREAD_CREATE_DETACHED;
	  self->thread = GetCurrentThreadId ();

#ifdef NEED_DUPLICATEHANDLE
	  /*
	   * DuplicateHandle does not exist on WinCE.
	   *
	   * NOTE:
	   * GetCurrentThread only returns a pseudo-handle
	   * which is only valid in the current thread context.
	   * Therefore, you should not pass the handle to
	   * other threads for whatever purpose.
	   */
	  self->threadH = GetCurrentThread();
#else
	  if( !DuplicateHandle(
			       GetCurrentProcess(),
			       GetCurrentThread(),
			       GetCurrentProcess(),
			       &self->threadH,
			       0,
			       FALSE,
			       DUPLICATE_SAME_ACCESS ) )
	    {
	      /* Thread structs are never freed. */
	      ptw32_threadReusePush(self);
	      return (NULL);
	    }
#endif

          /*
           * No need to explicitly serialise access to sched_priority
           * because the new handle is not yet public.
           */
          self->sched_priority = GetThreadPriority(self->threadH);
	}

      pthread_setspecific (ptw32_selfThreadKey, self);
    }

  return (self);

}				/* pthread_self */
