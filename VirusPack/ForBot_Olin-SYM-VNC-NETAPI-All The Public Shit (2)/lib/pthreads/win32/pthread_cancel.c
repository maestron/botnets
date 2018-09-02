/*
 * pthread_cancel.c
 *
 * Description:
 * POSIX thread functions related to thread cancellation.
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


#if defined(_M_IX86) || defined(_X86_)
#define PTW32_PROGCTR(Context)  ((Context).Eip)
#endif

#if defined(_MIPS_)
#define PTW32_PROGCTR(Context)  ((Context).Fir)
#endif

#if defined(_ALPHA_)
#define PTW32_PROGCTR(Context)  ((Context).Fir)
#endif

#if defined(_PPC_)
#define PTW32_PROGCTR(Context)  ((Context).Iar)
#endif

#if !defined(PTW32_PROGCTR)
#error Module contains CPU-specific code; modify and recompile.
#endif

static INLINE void
ptw32_cancel_self(void)
{
  ptw32_throw(PTW32_EPS_CANCEL);

  /* Never reached */
}

int
pthread_cancel (pthread_t thread)
     /*
      * ------------------------------------------------------
      * DOCPUBLIC
      *      This function requests cancellation of 'thread'.
      *
      * PARAMETERS
      *      thread
      *              reference to an instance of pthread_t
      *
      *
      * DESCRIPTION
      *      This function requests cancellation of 'thread'.
      *      NOTE: cancellation is asynchronous; use pthread_join to
      *                wait for termination of 'thread' if necessary.
      *
      * RESULTS
      *              0               successfully requested cancellation,
      *              ESRCH           no thread found corresponding to 'thread',
      *              ENOMEM          implicit self thread create failed.
      * ------------------------------------------------------
      */
{
  int result;
  int cancel_self;
  pthread_t self;

  /* This is the proper way to test thread validity. */
  result = pthread_kill(thread, 0);
  if (0 != result)
    {
      return result;
    }

  if ((self = pthread_self()) == NULL)
    {
      return ENOMEM;
    };

  /*
   * FIXME!!
   *
   * Can a thread cancel itself?
   *
   * The standard doesn't
   * specify an error to be returned if the target
   * thread is itself.
   *
   * If it may, then we need to ensure that a thread can't
   * deadlock itself trying to cancel itself asyncronously
   * (pthread_cancel is required to be an async-cancel
   * safe function).
   */
  cancel_self = pthread_equal(thread, self);

  /*
   * Lock for async-cancel safety.
   */
  (void) pthread_mutex_lock(&thread->cancelLock);

  if (thread->cancelType == PTHREAD_CANCEL_ASYNCHRONOUS
      && thread->cancelState == PTHREAD_CANCEL_ENABLE
      && thread->state < PThreadStateCanceling )
    {
      if (cancel_self)
        {
          thread->state = PThreadStateCanceling;
          thread->cancelState = PTHREAD_CANCEL_DISABLE;

          (void) pthread_mutex_unlock(&thread->cancelLock);
          ptw32_throw(PTW32_EPS_CANCEL);

          /* Never reached */
        }
      else
        {
          HANDLE threadH = thread->threadH;

          SuspendThread(threadH);

          if (WaitForSingleObject(threadH, 0) == WAIT_TIMEOUT )
            {
              CONTEXT context;

              thread->state = PThreadStateCanceling;
              thread->cancelState = PTHREAD_CANCEL_DISABLE;
              context.ContextFlags = CONTEXT_CONTROL;
              GetThreadContext(threadH, &context);
              PTW32_PROGCTR(context) = (DWORD) ptw32_cancel_self;
              SetThreadContext(threadH, &context);
              (void) pthread_mutex_unlock(&thread->cancelLock);
              ResumeThread(threadH);
            }
        }
    }
  else
    {
      /*
       * Set for deferred cancellation.
       */
      if ( thread->state >= PThreadStateCanceling
           || !SetEvent (thread->cancelEvent))
        {
          result = ESRCH;
        }

      (void) pthread_mutex_unlock(&thread->cancelLock);
    }

  return (result);
}

