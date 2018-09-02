/*
 * pthread_key_delete.c
 *
 * Description:
 * POSIX thread functions which implement thread-specific data (TSD).
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
pthread_key_delete (pthread_key_t key)
     /*
      * ------------------------------------------------------
      * DOCPUBLIC
      *      This function deletes a thread-specific data key. This
      *      does not change the value of the thread spcific data key
      *      for any thread and does not run the key's destructor
      *      in any thread so it should be used with caution.
      *
      * PARAMETERS
      *      key
      *              pointer to an instance of pthread_key_t
      *
      *
      * DESCRIPTION
      *      This function deletes a thread-specific data key. This
      *      does not change the value of the thread spcific data key
      *      for any thread and does not run the key's destructor
      *      in any thread so it should be used with caution.
      *
      * RESULTS
      *              0               successfully deleted the key,
      *              EINVAL          key is invalid,
      *
      * ------------------------------------------------------
      */
{
  int result = 0;

  if (key != NULL)
    {
      if (key->threads != NULL &&
          key->destructor != NULL &&
          pthread_mutex_lock (&(key->threadsLock)) == 0)
        {
          /*
           * Run through all Thread<-->Key associations
           * for this key.
           * If the pthread_t still exists (ie the assoc->thread
           * is not NULL) then leave the assoc for the thread to
           * destroy.
           * Notes:
           *      If assoc->thread is NULL, then the associated thread
           *      is no longer referencing this assoc.
           *      The association is only referenced
           *      by this key and must be released; otherwise
           *      the assoc will be destroyed when the thread is destroyed.
           */
          ThreadKeyAssoc *assoc;

          assoc = (ThreadKeyAssoc *) key->threads;

          while (assoc != NULL)
            {
              if (pthread_mutex_lock (&(assoc->lock)) == 0)
                {
                  ThreadKeyAssoc *next;

                  assoc->key = NULL;
                  next = assoc->nextThread;
                  assoc->nextThread = NULL;

                  pthread_mutex_unlock (&(assoc->lock));

                  ptw32_tkAssocDestroy (assoc);

                  assoc = next;
                }
            }
          pthread_mutex_unlock (&(key->threadsLock));
        }

      TlsFree (key->key);
      if (key->destructor != NULL)
        {
          pthread_mutex_destroy (&(key->threadsLock));
        }

#if defined( _DEBUG )
      memset ((char *) key, 0, sizeof (*key));
#endif
      free (key);
    }

  return (result);
}
