/* RSA.C - RSA routines for RSAREF
 */

/* Copyright (C) RSA Laboratories, a division of RSA Data Security,
     Inc., created 1991. All rights reserved.
 */

#include "global.h"
#include "rsaref.h"
#include "r_random.h"
#include "rsa.h"
#include "nn.h"

static int RSAPublicBlock PROTO_LIST 
  ((unsigned char *, unsigned int *, unsigned char *, unsigned int,
    R_RSA_PUBLIC_KEY *));
static int RSAPrivateBlock PROTO_LIST 
  ((unsigned char *, unsigned int *, unsigned char *, unsigned int,
    R_RSA_PRIVATE_KEY *));

/* RSA public-key encryption, according to PKCS #1.
 */
int RSAPublicEncrypt
  (output, outputLen, input, inputLen, publicKey, randomStruct)
unsigned char *output;                                      /* output block */
unsigned int *outputLen;                          /* length of output block */
unsigned char *input;                                        /* input block */
unsigned int inputLen;                             /* length of input block */
R_RSA_PUBLIC_KEY *publicKey;                              /* RSA public key */
R_RANDOM_STRUCT *randomStruct;                          /* random structure */
{
  int status;
  unsigned char byte, pkcsBlock[MAX_RSA_MODULUS_LEN];
  unsigned int i, modulusLen;
  
  modulusLen = (publicKey->bits + 7) / 8;
  if (inputLen + 11 > modulusLen)
    return (RE_LEN);
  
  pkcsBlock[0] = 0;
  /* block type 2 */
  pkcsBlock[1] = 2;

  for (i = 2; i < modulusLen - inputLen - 1; i++) {
    /* Find nonzero random byte.
     */
    do {
      R_GenerateBytes (&byte, 1, randomStruct);
    } while (byte == 0);
    pkcsBlock[i] = byte;
  }
  /* separator */
  pkcsBlock[i++] = 0;
  
  R_memcpy ((POINTER)&pkcsBlock[i], (POINTER)input, inputLen);
  
  status = RSAPublicBlock
    (output, outputLen, pkcsBlock, modulusLen, publicKey);
  
  /* Zeroize sensitive information.
   */
  byte = 0;
  R_memset ((POINTER)pkcsBlock, 0, sizeof (pkcsBlock));
  
  return (status);
}

/* RSA public-key decryption, according to PKCS #1.
 */
int RSAPublicDecrypt (output, outputLen, input, inputLen, publicKey)
unsigned char *output;                                      /* output block */
unsigned int *outputLen;                          /* length of output block */
unsigned char *input;                                        /* input block */
unsigned int inputLen;                             /* length of input block */
R_RSA_PUBLIC_KEY *publicKey;                              /* RSA public key */
{
  int status;
  unsigned char pkcsBlock[MAX_RSA_MODULUS_LEN];
  unsigned int i, modulusLen, pkcsBlockLen;
  
  modulusLen = (publicKey->bits + 7) / 8;
  if (inputLen > modulusLen)
    return (RE_LEN);
  
  if (status = RSAPublicBlock
      (pkcsBlock, &pkcsBlockLen, input, inputLen, publicKey))
    return (status);
  
  if (pkcsBlockLen != modulusLen)
    return (RE_LEN);
  
  /* Require block type 1.
   */
  if ((pkcsBlock[0] != 0) || (pkcsBlock[1] != 1))
   return (RE_DATA);

  for (i = 2; i < modulusLen-1; i++)
    if (pkcsBlock[i] != 0xff)
      break;
    
  /* separator */
  if (pkcsBlock[i++] != 0)
    return (RE_DATA);
  
  *outputLen = modulusLen - i;
  
  if (*outputLen + 11 > modulusLen)
    return (RE_DATA);

  R_memcpy ((POINTER)output, (POINTER)&pkcsBlock[i], *outputLen);
  
  /* Zeroize potentially sensitive information.
   */
  R_memset ((POINTER)pkcsBlock, 0, sizeof (pkcsBlock));
  
  return (0);
}

/* RSA private-key encryption, according to PKCS #1.
 */
int RSAPrivateEncrypt (output, outputLen, input, inputLen, privateKey)
unsigned char *output;                                      /* output block */
unsigned int *outputLen;                          /* length of output block */
unsigned char *input;                                        /* input block */
unsigned int inputLen;                             /* length of input block */
R_RSA_PRIVATE_KEY *privateKey;                           /* RSA private key */
{
  int status;
  unsigned char pkcsBlock[MAX_RSA_MODULUS_LEN];
  unsigned int i, modulusLen;
  
  modulusLen = (privateKey->bits + 7) / 8;
  if (inputLen + 11 > modulusLen)
    return (RE_LEN);
  
  pkcsBlock[0] = 0;
  /* block type 1 */
  pkcsBlock[1] = 1;

  for (i = 2; i < modulusLen - inputLen - 1; i++)
    pkcsBlock[i] = 0xff;

  /* separator */
  pkcsBlock[i++] = 0;
  
  R_memcpy ((POINTER)&pkcsBlock[i], (POINTER)input, inputLen);
  
  status = RSAPrivateBlock
    (output, outputLen, pkcsBlock, modulusLen, privateKey);

  /* Zeroize potentially sensitive information.
   */
  R_memset ((POINTER)pkcsBlock, 0, sizeof (pkcsBlock));

  return (status);
}

/* RSA private-key decryption, according to PKCS #1.
 */
int RSAPrivateDecrypt (output, outputLen, input, inputLen, privateKey)
unsigned char *output;                                      /* output block */
unsigned int *outputLen;                          /* length of output block */
unsigned char *input;                                        /* input block */
unsigned int inputLen;                             /* length of input block */
R_RSA_PRIVATE_KEY *privateKey;                           /* RSA private key */
{
  int status;
  unsigned char pkcsBlock[MAX_RSA_MODULUS_LEN];
  unsigned int i, modulusLen, pkcsBlockLen;
  
  modulusLen = (privateKey->bits + 7) / 8;
  if (inputLen > modulusLen)
    return (RE_LEN);
  
  if (status = RSAPrivateBlock
      (pkcsBlock, &pkcsBlockLen, input, inputLen, privateKey))
    return (status);
  
  if (pkcsBlockLen != modulusLen)
    return (RE_LEN);
  
  /* Require block type 2.
   */
  if ((pkcsBlock[0] != 0) || (pkcsBlock[1] != 2))
   return (RE_DATA);

  for (i = 2; i < modulusLen-1; i++)
    /* separator */
    if (pkcsBlock[i] == 0)
      break;
    
  i++;
  if (i >= modulusLen)
    return (RE_DATA);
    
  *outputLen = modulusLen - i;
  
  if (*outputLen + 11 > modulusLen)
    return (RE_DATA);

  R_memcpy ((POINTER)output, (POINTER)&pkcsBlock[i], *outputLen);
  
  /* Zeroize sensitive information.
   */
  R_memset ((POINTER)pkcsBlock, 0, sizeof (pkcsBlock));
  
  return (0);
}

/* Raw RSA public-key operation. Output has same length as modulus.

   Assumes inputLen < length of modulus.
   Requires input < modulus.
 */
static int RSAPublicBlock (output, outputLen, input, inputLen, publicKey)
unsigned char *output;                                      /* output block */
unsigned int *outputLen;                          /* length of output block */
unsigned char *input;                                        /* input block */
unsigned int inputLen;                             /* length of input block */
R_RSA_PUBLIC_KEY *publicKey;                              /* RSA public key */
{
  NN_DIGIT c[MAX_NN_DIGITS], e[MAX_NN_DIGITS], m[MAX_NN_DIGITS],
    n[MAX_NN_DIGITS];
  unsigned int eDigits, nDigits;

  NN_Decode (m, MAX_NN_DIGITS, input, inputLen);
  NN_Decode (n, MAX_NN_DIGITS, publicKey->modulus, MAX_RSA_MODULUS_LEN);
  NN_Decode (e, MAX_NN_DIGITS, publicKey->exponent, MAX_RSA_MODULUS_LEN);
  nDigits = NN_Digits (n, MAX_NN_DIGITS);
  eDigits = NN_Digits (e, MAX_NN_DIGITS);
  
  if (NN_Cmp (m, n, nDigits) >= 0)
    return (RE_DATA);
  
  /* Compute c = m^e mod n.
   */
  NN_ModExp (c, m, e, eDigits, n, nDigits);

  *outputLen = (publicKey->bits + 7) / 8;
  NN_Encode (output, *outputLen, c, nDigits);
  
  /* Zeroize sensitive information.
   */
  R_memset ((POINTER)c, 0, sizeof (c));
  R_memset ((POINTER)m, 0, sizeof (m));

  return (0);
}

/* Raw RSA private-key operation. Output has same length as modulus.

   Assumes inputLen < length of modulus.
   Requires input < modulus.
 */
static int RSAPrivateBlock (output, outputLen, input, inputLen, privateKey)
unsigned char *output;                                      /* output block */
unsigned int *outputLen;                          /* length of output block */
unsigned char *input;                                        /* input block */
unsigned int inputLen;                             /* length of input block */
R_RSA_PRIVATE_KEY *privateKey;                           /* RSA private key */
{
  NN_DIGIT c[MAX_NN_DIGITS], cP[MAX_NN_DIGITS], cQ[MAX_NN_DIGITS],
    dP[MAX_NN_DIGITS], dQ[MAX_NN_DIGITS], mP[MAX_NN_DIGITS],
    mQ[MAX_NN_DIGITS], n[MAX_NN_DIGITS], p[MAX_NN_DIGITS], q[MAX_NN_DIGITS],
    qInv[MAX_NN_DIGITS], t[MAX_NN_DIGITS];
  unsigned int cDigits, nDigits, pDigits;
  
  NN_Decode (c, MAX_NN_DIGITS, input, inputLen);
  NN_Decode (n, MAX_NN_DIGITS, privateKey->modulus, MAX_RSA_MODULUS_LEN);
  NN_Decode (p, MAX_NN_DIGITS, privateKey->prime[0], MAX_RSA_PRIME_LEN);
  NN_Decode (q, MAX_NN_DIGITS, privateKey->prime[1], MAX_RSA_PRIME_LEN);
  NN_Decode 
    (dP, MAX_NN_DIGITS, privateKey->primeExponent[0], MAX_RSA_PRIME_LEN);
  NN_Decode 
    (dQ, MAX_NN_DIGITS, privateKey->primeExponent[1], MAX_RSA_PRIME_LEN);
  NN_Decode (qInv, MAX_NN_DIGITS, privateKey->coefficient, MAX_RSA_PRIME_LEN);
  cDigits = NN_Digits (c, MAX_NN_DIGITS);
  nDigits = NN_Digits (n, MAX_NN_DIGITS);
  pDigits = NN_Digits (p, MAX_NN_DIGITS);

  if (NN_Cmp (c, n, nDigits) >= 0)
    return (RE_DATA);
  
  /* Compute mP = cP^dP mod p  and  mQ = cQ^dQ mod q. (Assumes q has
     length at most pDigits, i.e., p > q.)
   */
  NN_Mod (cP, c, cDigits, p, pDigits);
  NN_Mod (cQ, c, cDigits, q, pDigits);
  NN_ModExp (mP, cP, dP, pDigits, p, pDigits);
  NN_AssignZero (mQ, nDigits);
  NN_ModExp (mQ, cQ, dQ, pDigits, q, pDigits);
  
  /* Chinese Remainder Theorem:
       m = ((((mP - mQ) mod p) * qInv) mod p) * q + mQ.
   */
  if (NN_Cmp (mP, mQ, pDigits) >= 0)
    NN_Sub (t, mP, mQ, pDigits);
  else {
    NN_Sub (t, mQ, mP, pDigits);
    NN_Sub (t, p, t, pDigits);
  }
  NN_ModMult (t, t, qInv, p, pDigits);
  NN_Mult (t, t, q, pDigits);
  NN_Add (t, t, mQ, nDigits);

  *outputLen = (privateKey->bits + 7) / 8;
  NN_Encode (output, *outputLen, t, nDigits);

  /* Zeroize sensitive information.
   */
  R_memset ((POINTER)c, 0, sizeof (c));
  R_memset ((POINTER)cP, 0, sizeof (cP));
  R_memset ((POINTER)cQ, 0, sizeof (cQ));
  R_memset ((POINTER)dP, 0, sizeof (dP));
  R_memset ((POINTER)dQ, 0, sizeof (dQ));
  R_memset ((POINTER)mP, 0, sizeof (mP));
  R_memset ((POINTER)mQ, 0, sizeof (mQ));
  R_memset ((POINTER)p, 0, sizeof (p));
  R_memset ((POINTER)q, 0, sizeof (q));
  R_memset ((POINTER)qInv, 0, sizeof (qInv));
  R_memset ((POINTER)t, 0, sizeof (t));

  return (0);
}
