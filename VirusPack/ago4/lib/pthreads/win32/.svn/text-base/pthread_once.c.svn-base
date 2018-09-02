/*
 * pthread_once.c
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


int
pthread_once (
	       pthread_once_t * once_control,
	       void (*init_routine) (void)
)
	/*
	 * ------------------------------------------------------
	 * DOCPUBLIC
	 *	If any thread in a process  with  a  once_control  parameter
	 *	makes  a  call to pthread_once(), the first call will summon
	 *	the init_routine(), but  subsequent  calls  will  not. The
	 *	once_control  parameter  determines  whether  the associated
	 *	initialization routine has been called.  The  init_routine()
	 *	is complete upon return of pthread_once().
	 *	This function guarantees that one and only one thread
	 *	executes the initialization routine, init_routine when
	 *	access is controlled by the pthread_once_t control
	 *	key.
	 *
	 * PARAMETERS
	 *	once_control
	 *		pointer to an instance of pthread_once_t
	 *
	 *	init_routine
	 *		pointer to an initialization routine
	 *
	 *
	 * DESCRIPTION
	 *	See above.
	 *
	 * RESULTS
	 *		0		success,
	 *		EINVAL		once_control or init_routine is NULL
	 *
	 * ------------------------------------------------------
	 */
{
  int result;

  if (once_control == NULL || init_routine == NULL)
    {

      result = EINVAL;
      goto FAIL0;

    }
  else
    {
      result = 0;
    }

  if (!once_control->done)
    {
      if (InterlockedIncrement (&(once_control->started)) == 0)
	{
	  /*
	   * First thread to increment the started variable
	   */
	  (*init_routine) ();
	  once_control->done = PTW32_TRUE;

	}
      else
	{
	  /*
	   * Block until other thread finishes executing the onceRoutine
	   */
	  while (!(once_control->done))
	    {
	      /*
	       * The following gives up CPU cycles without pausing
	       * unnecessarily
	       */
	      Sleep (0);
	    }
	}
    }

  /*
   * Fall through Intentionally
   */

  /*
   * ------------
   * Failure Code
   * ------------
   */
FAIL0:
  return (result);

}				/* pthread_once */
