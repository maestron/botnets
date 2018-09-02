/* PRIME.C - primality-testing routines
 */

/* Copyright (C) RSA Laboratories, a division of RSA Data Security,
     Inc., created 1991. All rights reserved.
 */

#include "global.h"
#include "rsaref.h"
#include "r_random.h"
#include "nn.h"
#include "prime.h"

static unsigned int SMALL_PRIMES[] = { 3, 5, 7, 11 };
#define SMALL_PRIME_COUNT 4

static int ProbablePrime PROTO_LIST ((NN_DIGIT *, unsigned int));
static int SmallFactor PROTO_LIST ((NN_DIGIT *, unsigned int));
static int FermatTest PROTO_LIST ((NN_DIGIT *, unsigned int));

/* Generates a probable prime a between b and c such that a-1 is
   divisible by d.

   Lengths: a[digits], b[digits], c[digits], d[digits].
   Assumes b < c, digits < MAX_NN_DIGITS.
   
   Returns RE_NEED_RANDOM if randomStruct not seeded, RE_DATA if
   unsuccessful.
 */
int GeneratePrime (a, b, c, d, digits, randomStruct)
NN_DIGIT *a, *b, *c, *d;
unsigned int digits;
R_RANDOM_STRUCT *randomStruct;
{
  int status;
  unsigned char block[MAX_NN_DIGITS * NN_DIGIT_LEN];
  NN_DIGIT t[MAX_NN_DIGITS], u[MAX_NN_DIGITS];

  /* Generate random number between b and c.
   */
  if (status = R_GenerateBytes (block, digits * NN_DIGIT_LEN, randomStruct))
    return (status);
  NN_Decode (a, digits, block, digits * NN_DIGIT_LEN);
  NN_Sub (t, c, b, digits);
  NN_ASSIGN_DIGIT (u, 1, digits);
  NN_Add (t, t, u, digits);
  NN_Mod (a, a, digits, t, digits);
  NN_Add (a, a, b, digits);

  /* Adjust so that a-1 is divisible by d.
   */
  NN_Mod (t, a, digits, d, digits);
  NN_Sub (a, a, t, digits);
  NN_Add (a, a, u, digits);
  if (NN_Cmp (a, b, digits) < 0)
    NN_Add (a, a, d, digits);
  if (NN_Cmp (a, c, digits) > 0)
    NN_Sub (a, a, d, digits);

  /* Search to c in steps of d.
   */
  NN_Assign (t, c, digits);
  NN_Sub (t, t, d, digits);

  while (! ProbablePrime (a, digits)) {
    if (NN_Cmp (a, t, digits) > 0)
      return (RE_DATA);
    NN_Add (a, a, d, digits);
  }

  return (0);
}

/* Returns nonzero iff a is a probable prime.

   Lengths: a[aDigits].
   Assumes aDigits < MAX_NN_DIGITS.
 */
static int ProbablePrime (a, aDigits)
NN_DIGIT *a;
unsigned int aDigits;
{
  return (! SmallFactor (a, aDigits) && FermatTest (a, aDigits));
}

/* Returns nonzero iff a has a prime factor in SMALL_PRIMES.

   Lengths: a[aDigits].
   Assumes aDigits < MAX_NN_DIGITS.
 */
static int SmallFactor (a, aDigits)
NN_DIGIT *a;
unsigned int aDigits;
{
  int status;
  NN_DIGIT t[1];
  unsigned int i;
  
  status = 0;
  
  for (i = 0; i < SMALL_PRIME_COUNT; i++) {
    NN_ASSIGN_DIGIT (t, SMALL_PRIMES[i], 1);
    if ((aDigits == 1) && ! NN_Cmp (a, t, 1))
      break;
    NN_Mod (t, a, aDigits, t, 1);
    if (NN_Zero (t, 1)) {
      status = 1;
      break;
    }
  }
  
  /* Zeroize sensitive information.
   */
  i = 0;
  R_memset ((POINTER)t, 0, sizeof (t));

  return (status);
}

/* Returns nonzero iff a passes Fermat's test for witness 2.
   (All primes pass the test, and nearly all composites fail.)
     
   Lengths: a[aDigits].
   Assumes aDigits < MAX_NN_DIGITS.
 */
static int FermatTest (a, aDigits)
NN_DIGIT *a;
unsigned int aDigits;
{
  int status;
  NN_DIGIT t[MAX_NN_DIGITS], u[MAX_NN_DIGITS];
  
  NN_ASSIGN_DIGIT (t, 2, aDigits);
  NN_ModExp (u, t, a, aDigits, a, aDigits);
  
  status = NN_EQUAL (t, u, aDigits);
  
  /* Zeroize sensitive information.
   */
  R_memset ((POINTER)u, 0, sizeof (u));
  
  return (status);
}
