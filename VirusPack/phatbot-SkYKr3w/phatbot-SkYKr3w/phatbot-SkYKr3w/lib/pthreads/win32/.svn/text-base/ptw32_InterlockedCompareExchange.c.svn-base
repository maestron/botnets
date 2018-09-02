/*
 * ptw32_InterlockedCompareExchange.c
 *
 * Description:
 * This translation unit implements routines which are private to
 * the implementation and may be used throughout it.
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


/*
 * ptw32_InterlockedCompareExchange --
 *
 * Needed because W95 doesn't support InterlockedCompareExchange.
 * It is only used when running the dll on W95. Other versions of
 * Windows use the Win32 supported version, which may be running on
 * different processor types.
 *
 * This can't be inlined because we need to know it's address so that
 * we can call it through a pointer.
 */
PTW32_INTERLOCKED_LONG WINAPI
ptw32_InterlockedCompareExchange(PTW32_INTERLOCKED_LPLONG location,
				 PTW32_INTERLOCKED_LONG   value,
				 PTW32_INTERLOCKED_LONG   comparand)
{
  PTW32_INTERLOCKED_LONG result;

#if defined(_M_IX86) || defined(_X86_)

#if defined(_MSC_VER)

  _asm {
    PUSH	 ecx
    PUSH	 edx
    MOV 	 ecx,dword ptr [location]
    MOV 	 edx,dword ptr [value]
    MOV 	 eax,dword ptr [comparand]
    LOCK CMPXCHG dword ptr [ecx],edx	    ; if (EAX == [ECX]), 
					    ;	[ECX] = EDX
					    ; else
					    ;	EAX = [ECX]
    MOV 	 dword ptr [result], eax
    POP 	 edx
    POP 	 ecx
  }

#elif defined(__GNUC__)

  __asm__
    (
     "lock\n\t"
     "cmpxchgl	     %3,(%0)"	 /* if (EAX == [location]), */
				 /*   [location] = value    */
				 /* else		    */
				 /*   EAX = [location]		 */
     :"=r" (location), "=a" (result)
     :"0"  (location), "q" (value), "a" (comparand)
     : "memory" );

#endif

#else

  /*
   * If execution gets to here then we should be running on a Win95 system
   * but either running on something other than an X86 processor, or a
   * compiler other than MSVC or GCC. Pthreads-win32 doesn't support that
   * platform (yet).
   */

  result = 0;

#endif

  return result;
}
