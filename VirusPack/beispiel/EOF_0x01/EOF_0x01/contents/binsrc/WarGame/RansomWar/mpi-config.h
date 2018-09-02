/* Default configuration for MPI library */
/* $Id: mpi-config.h,v 1.8 2000/07/11 04:28:14 sting Exp sting $ */

#ifndef MPI_CONFIG_H_
#define MPI_CONFIG_H_

/*
  For boolean options, 
  0 = no
  1 = yes

  Other options are documented individually.

 */

#ifndef MP_IOFUNC
#define MP_IOFUNC     0  /* include mp_print() ?                */
#endif

#ifndef MP_MODARITH
#define MP_MODARITH   1  /* include modular arithmetic ?        */
#endif

#ifndef MP_NUMTH
#define MP_NUMTH      1  /* include number theoretic functions? */
#endif

#ifndef MP_LOGTAB
#define MP_LOGTAB     0  /* use table of logs instead of log()? */
#endif

#ifndef MP_MEMSET
#define MP_MEMSET     1  /* use memset() to zero buffers?       */
#endif

#ifndef MP_MEMCPY
#define MP_MEMCPY     1  /* use memcpy() to copy buffers?       */
#endif

#ifndef MP_CRYPTO
#define MP_CRYPTO     0  /* erase memory on free?               */
#endif

#ifndef MP_ARGCHK
/*
  0 = no parameter checks
  1 = runtime checks, continue execution and return an error to caller
  2 = assertions; dump core on parameter errors
 */
#define MP_ARGCHK     1  /* how to check input arguments        */
#endif

#ifndef MP_DEBUG
#define MP_DEBUG      0  /* print diagnostic output?            */
#endif

#ifndef MP_DEFPREC
#define MP_DEFPREC    128 /* default precision, in digits        */
#endif

#ifndef MP_MACRO
#define MP_MACRO      1  /* use macros for frequent calls?      */
#endif

#ifndef MP_SQUARE
#define MP_SQUARE     1  /* use separate squaring code?         */
#endif

#ifndef MP_PTAB_SIZE
/*
  When building mpprime.c, we build in a table of small prime
  values to use for primality testing.  The more you include,
  the more space they take up.  See primes.c for the possible
  values (currently 16, 32, 64, 128, 256, and 6542)
 */
#define MP_PTAB_SIZE  128  /* how many built-in primes?         */
#endif

#endif /* ifndef MPI_CONFIG_H_ */


/* crc==1814202000, version==3, Wed Mar 28 09:24:45 2001 */
