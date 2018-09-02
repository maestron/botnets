/* DESC.C - Data Encryption Standard routines for RSAREF
     Based on "Karn/Hoey/Outerbridge" implementation (KHODES)
 */

#include "global.h"
#include "rsaref.h"
#include "des.h"

static UINT2 BYTE_BIT[8] = {
  0200, 0100, 040, 020, 010, 04, 02, 01
};

static UINT4 BIG_BYTE[24] = {
  0x800000L, 0x400000L, 0x200000L, 0x100000L,
  0x80000L,  0x40000L,  0x20000L,  0x10000L,
  0x8000L,   0x4000L,   0x2000L,   0x1000L,
  0x800L,    0x400L,    0x200L,    0x100L,
  0x80L,     0x40L,     0x20L,     0x10L,
  0x8L,      0x4L,      0x2L,      0x1L
};

static unsigned char PC1[56] = {
  56, 48, 40, 32, 24, 16,  8,      0, 57, 49, 41, 33, 25, 17,
   9,  1, 58, 50, 42, 34, 26,     18, 10,  2, 59, 51, 43, 35,
  62, 54, 46, 38, 30, 22, 14,      6, 61, 53, 45, 37, 29, 21,
  13,  5, 60, 52, 44, 36, 28,     20, 12,  4, 27, 19, 11,  3
};

static unsigned char TOTAL_ROTATIONS[16] = {
  1, 2, 4, 6, 8, 10, 12, 14, 15, 17, 19, 21, 23, 25, 27, 28
};

static unsigned char PC2[48] = {
  13, 16, 10, 23,  0,  4,  2, 27, 14,  5, 20,  9,
  22, 18, 11,  3, 25,  7, 15,  6, 26, 19, 12,  1,
  40, 51, 30, 36, 46, 54, 29, 39, 50, 44, 32, 47,
  43, 48, 38, 55, 33, 52, 45, 41, 49, 35, 28, 31
};

static UINT4 SP1[64] = {
  0x01010400L, 0x00000000L, 0x00010000L, 0x01010404L,
  0x01010004L, 0x00010404L, 0x00000004L, 0x00010000L,
  0x00000400L, 0x01010400L, 0x01010404L, 0x00000400L,
  0x01000404L, 0x01010004L, 0x01000000L, 0x00000004L,
  0x00000404L, 0x01000400L, 0x01000400L, 0x00010400L,
  0x00010400L, 0x01010000L, 0x01010000L, 0x01000404L,
  0x00010004L, 0x01000004L, 0x01000004L, 0x00010004L,
  0x00000000L, 0x00000404L, 0x00010404L, 0x01000000L,
  0x00010000L, 0x01010404L, 0x00000004L, 0x01010000L,
  0x01010400L, 0x01000000L, 0x01000000L, 0x00000400L,
  0x01010004L, 0x00010000L, 0x00010400L, 0x01000004L,
  0x00000400L, 0x00000004L, 0x01000404L, 0x00010404L,
  0x01010404L, 0x00010004L, 0x01010000L, 0x01000404L,
  0x01000004L, 0x00000404L, 0x00010404L, 0x01010400L,
  0x00000404L, 0x01000400L, 0x01000400L, 0x00000000L,
  0x00010004L, 0x00010400L, 0x00000000L, 0x01010004L
};

static UINT4 SP2[64] = {
  0x80108020L, 0x80008000L, 0x00008000L, 0x00108020L,
  0x00100000L, 0x00000020L, 0x80100020L, 0x80008020L,
  0x80000020L, 0x80108020L, 0x80108000L, 0x80000000L,
  0x80008000L, 0x00100000L, 0x00000020L, 0x80100020L,
  0x00108000L, 0x00100020L, 0x80008020L, 0x00000000L,
  0x80000000L, 0x00008000L, 0x00108020L, 0x80100000L,
  0x00100020L, 0x80000020L, 0x00000000L, 0x00108000L,
  0x00008020L, 0x80108000L, 0x80100000L, 0x00008020L,
  0x00000000L, 0x00108020L, 0x80100020L, 0x00100000L,
  0x80008020L, 0x80100000L, 0x80108000L, 0x00008000L,
  0x80100000L, 0x80008000L, 0x00000020L, 0x80108020L,
  0x00108020L, 0x00000020L, 0x00008000L, 0x80000000L,
  0x00008020L, 0x80108000L, 0x00100000L, 0x80000020L,
  0x00100020L, 0x80008020L, 0x80000020L, 0x00100020L,
  0x00108000L, 0x00000000L, 0x80008000L, 0x00008020L,
  0x80000000L, 0x80100020L, 0x80108020L, 0x00108000L
};

static UINT4 SP3[64] = {
  0x00000208L, 0x08020200L, 0x00000000L, 0x08020008L,
  0x08000200L, 0x00000000L, 0x00020208L, 0x08000200L,
  0x00020008L, 0x08000008L, 0x08000008L, 0x00020000L,
  0x08020208L, 0x00020008L, 0x08020000L, 0x00000208L,
  0x08000000L, 0x00000008L, 0x08020200L, 0x00000200L,
  0x00020200L, 0x08020000L, 0x08020008L, 0x00020208L,
  0x08000208L, 0x00020200L, 0x00020000L, 0x08000208L,
  0x00000008L, 0x08020208L, 0x00000200L, 0x08000000L,
  0x08020200L, 0x08000000L, 0x00020008L, 0x00000208L,
  0x00020000L, 0x08020200L, 0x08000200L, 0x00000000L,
  0x00000200L, 0x00020008L, 0x08020208L, 0x08000200L,
  0x08000008L, 0x00000200L, 0x00000000L, 0x08020008L,
  0x08000208L, 0x00020000L, 0x08000000L, 0x08020208L,
  0x00000008L, 0x00020208L, 0x00020200L, 0x08000008L,
  0x08020000L, 0x08000208L, 0x00000208L, 0x08020000L,
  0x00020208L, 0x00000008L, 0x08020008L, 0x00020200L
};

static UINT4 SP4[64] = {
  0x00802001L, 0x00002081L, 0x00002081L, 0x00000080L,
  0x00802080L, 0x00800081L, 0x00800001L, 0x00002001L,
  0x00000000L, 0x00802000L, 0x00802000L, 0x00802081L,
  0x00000081L, 0x00000000L, 0x00800080L, 0x00800001L,
  0x00000001L, 0x00002000L, 0x00800000L, 0x00802001L,
  0x00000080L, 0x00800000L, 0x00002001L, 0x00002080L,
  0x00800081L, 0x00000001L, 0x00002080L, 0x00800080L,
  0x00002000L, 0x00802080L, 0x00802081L, 0x00000081L,
  0x00800080L, 0x00800001L, 0x00802000L, 0x00802081L,
  0x00000081L, 0x00000000L, 0x00000000L, 0x00802000L,
  0x00002080L, 0x00800080L, 0x00800081L, 0x00000001L,
  0x00802001L, 0x00002081L, 0x00002081L, 0x00000080L,
  0x00802081L, 0x00000081L, 0x00000001L, 0x00002000L,
  0x00800001L, 0x00002001L, 0x00802080L, 0x00800081L,
  0x00002001L, 0x00002080L, 0x00800000L, 0x00802001L,
  0x00000080L, 0x00800000L, 0x00002000L, 0x00802080L
};

static UINT4 SP5[64] = {
  0x00000100L, 0x02080100L, 0x02080000L, 0x42000100L,
  0x00080000L, 0x00000100L, 0x40000000L, 0x02080000L,
  0x40080100L, 0x00080000L, 0x02000100L, 0x40080100L,
  0x42000100L, 0x42080000L, 0x00080100L, 0x40000000L,
  0x02000000L, 0x40080000L, 0x40080000L, 0x00000000L,
  0x40000100L, 0x42080100L, 0x42080100L, 0x02000100L,
  0x42080000L, 0x40000100L, 0x00000000L, 0x42000000L,
  0x02080100L, 0x02000000L, 0x42000000L, 0x00080100L,
  0x00080000L, 0x42000100L, 0x00000100L, 0x02000000L,
  0x40000000L, 0x02080000L, 0x42000100L, 0x40080100L,
  0x02000100L, 0x40000000L, 0x42080000L, 0x02080100L,
  0x40080100L, 0x00000100L, 0x02000000L, 0x42080000L,
  0x42080100L, 0x00080100L, 0x42000000L, 0x42080100L,
  0x02080000L, 0x00000000L, 0x40080000L, 0x42000000L,
  0x00080100L, 0x02000100L, 0x40000100L, 0x00080000L,
  0x00000000L, 0x40080000L, 0x02080100L, 0x40000100L
};

static UINT4 SP6[64] = {
  0x20000010L, 0x20400000L, 0x00004000L, 0x20404010L,
  0x20400000L, 0x00000010L, 0x20404010L, 0x00400000L,
  0x20004000L, 0x00404010L, 0x00400000L, 0x20000010L,
  0x00400010L, 0x20004000L, 0x20000000L, 0x00004010L,
  0x00000000L, 0x00400010L, 0x20004010L, 0x00004000L,
  0x00404000L, 0x20004010L, 0x00000010L, 0x20400010L,
  0x20400010L, 0x00000000L, 0x00404010L, 0x20404000L,
  0x00004010L, 0x00404000L, 0x20404000L, 0x20000000L,
  0x20004000L, 0x00000010L, 0x20400010L, 0x00404000L,
  0x20404010L, 0x00400000L, 0x00004010L, 0x20000010L,
  0x00400000L, 0x20004000L, 0x20000000L, 0x00004010L,
  0x20000010L, 0x20404010L, 0x00404000L, 0x20400000L,
  0x00404010L, 0x20404000L, 0x00000000L, 0x20400010L,
  0x00000010L, 0x00004000L, 0x20400000L, 0x00404010L,
  0x00004000L, 0x00400010L, 0x20004010L, 0x00000000L,
  0x20404000L, 0x20000000L, 0x00400010L, 0x20004010L
};

static UINT4 SP7[64] = {
  0x00200000L, 0x04200002L, 0x04000802L, 0x00000000L,
  0x00000800L, 0x04000802L, 0x00200802L, 0x04200800L,
  0x04200802L, 0x00200000L, 0x00000000L, 0x04000002L,
  0x00000002L, 0x04000000L, 0x04200002L, 0x00000802L,
  0x04000800L, 0x00200802L, 0x00200002L, 0x04000800L,
  0x04000002L, 0x04200000L, 0x04200800L, 0x00200002L,
  0x04200000L, 0x00000800L, 0x00000802L, 0x04200802L,
  0x00200800L, 0x00000002L, 0x04000000L, 0x00200800L,
  0x04000000L, 0x00200800L, 0x00200000L, 0x04000802L,
  0x04000802L, 0x04200002L, 0x04200002L, 0x00000002L,
  0x00200002L, 0x04000000L, 0x04000800L, 0x00200000L,
  0x04200800L, 0x00000802L, 0x00200802L, 0x04200800L,
  0x00000802L, 0x04000002L, 0x04200802L, 0x04200000L,
  0x00200800L, 0x00000000L, 0x00000002L, 0x04200802L,
  0x00000000L, 0x00200802L, 0x04200000L, 0x00000800L,
  0x04000002L, 0x04000800L, 0x00000800L, 0x00200002L
};

static UINT4 SP8[64] = {
  0x10001040L, 0x00001000L, 0x00040000L, 0x10041040L,
  0x10000000L, 0x10001040L, 0x00000040L, 0x10000000L,
  0x00040040L, 0x10040000L, 0x10041040L, 0x00041000L,
  0x10041000L, 0x00041040L, 0x00001000L, 0x00000040L,
  0x10040000L, 0x10000040L, 0x10001000L, 0x00001040L,
  0x00041000L, 0x00040040L, 0x10040040L, 0x10041000L,
  0x00001040L, 0x00000000L, 0x00000000L, 0x10040040L,
  0x10000040L, 0x10001000L, 0x00041040L, 0x00040000L,
  0x00041040L, 0x00040000L, 0x10041000L, 0x00001000L,
  0x00000040L, 0x10040040L, 0x00001000L, 0x00041040L,
  0x10001000L, 0x00000040L, 0x10000040L, 0x10040000L,
  0x10040040L, 0x10000000L, 0x00040000L, 0x10001040L,
  0x00000000L, 0x10041040L, 0x00040040L, 0x10000040L,
  0x10040000L, 0x10001000L, 0x10001040L, 0x00000000L,
  0x10041040L, 0x00041000L, 0x00041000L, 0x00001040L,
  0x00001040L, 0x00040040L, 0x10000000L, 0x10041000L
};

static void Unpack PROTO_LIST ((unsigned char *, UINT4 *));
static void Pack PROTO_LIST ((UINT4 *, unsigned char *));
static void DESKey PROTO_LIST ((UINT4 *, unsigned char *, int));
static void CookKey PROTO_LIST ((UINT4 *, UINT4 *, int));
static void DESFunction PROTO_LIST ((UINT4 *, UINT4 *));

/* Initialize context.  Caller must zeroize the context when finished.
 */
void DES_CBCInit (context, key, iv, encrypt)
DES_CBC_CTX *context;                                            /* context */
unsigned char key[8];                                                /* key */
unsigned char iv[8];                                 /* initializing vector */
int encrypt;                     /* encrypt flag (1 = encrypt, 0 = decrypt) */
{  
  /* Copy encrypt flag to context.
   */
  context->encrypt = encrypt;

  /* Pack initializing vector into context.
   */
  Pack (context->iv, iv);

  /* Save the IV for use in Restart */
  context->originalIV[0] = context->iv[0];
  context->originalIV[1] = context->iv[1];

  /* Precompute key schedule
   */
  DESKey (context->subkeys, key, encrypt);
}

/* DES-CBC block update operation. Continues a DES-CBC encryption
   operation, processing eight-byte message blocks, and updating
   the context.
 */
int DES_CBCUpdate (context, output, input, len)
DES_CBC_CTX *context;                                            /* context */
unsigned char *output;                                      /* output block */
unsigned char *input;                                        /* input block */
unsigned int len;                      /* length of input and output blocks */
{
  UINT4 inputBlock[2], work[2];
  unsigned int i;
  
  if (len % 8)
    return (RE_LEN);

  for (i = 0; i < len/8; i++) {
    Pack (inputBlock, &input[8*i]);
        
    /* Chain if encrypting.
     */
    if (context->encrypt) {
      work[0] = inputBlock[0] ^ context->iv[0];
      work[1] = inputBlock[1] ^ context->iv[1];
    }
    else {
      work[0] = inputBlock[0];
      work[1] = inputBlock[1];         
    }

    DESFunction (work, context->subkeys);

    /* Chain if decrypting, then update IV.
     */
    if (context->encrypt) {
      context->iv[0] = work[0];
      context->iv[1] = work[1];
    }
    else {
      work[0] ^= context->iv[0];
      work[1] ^= context->iv[1];
      context->iv[0] = inputBlock[0];
      context->iv[1] = inputBlock[1];
    }
    Unpack (&output[8*i], work);
  }
  
  /* Zeroize sensitive information.
   */
  R_memset ((POINTER)inputBlock, 0, sizeof (inputBlock));
  R_memset ((POINTER)work, 0, sizeof (work));
  
  return (0);
}

void DES_CBCRestart (context)
DES_CBC_CTX *context;
{
  /* Reset to the original IV */
  context->iv[0] = context->originalIV[0];
  context->iv[1] = context->originalIV[1];
}

/* Initialize context.  Caller must zeroize the context when finished.
   The key has the DES key, input whitener and output whitener concatenated.
 */
void DESX_CBCInit (context, key, iv, encrypt)
DESX_CBC_CTX *context;
unsigned char key[24];                              /* DES key and whiteners */
unsigned char iv[8];                              /* DES initializing vector */
int encrypt;                      /* encrypt flag (1 = encrypt, 0 = decrypt) */
{  
  /* Copy encrypt flag to context.
   */
  context->encrypt = encrypt;

  /* Pack initializing vector and whiteners into context.
   */
  Pack (context->iv, iv);
  Pack (context->inputWhitener, key + 8);
  Pack (context->outputWhitener, key + 16);

  /* Save the IV for use in Restart */
  context->originalIV[0] = context->iv[0];
  context->originalIV[1] = context->iv[1];

  /* Precompute key schedule.
   */
  DESKey (context->subkeys, key, encrypt);
}

/* DESX-CBC block update operation. Continues a DESX-CBC encryption
   operation, processing eight-byte message blocks, and updating
   the context.
 */
int DESX_CBCUpdate (context, output, input, len)
DESX_CBC_CTX *context;                                           /* context */
unsigned char *output;                                      /* output block */
unsigned char *input;                                        /* input block */
unsigned int len;                      /* length of input and output blocks */
{
  UINT4 inputBlock[2], work[2];
  unsigned int i;
  
  if (len % 8)
    return (RE_LEN);

  for (i = 0; i < len/8; i++)  {
    Pack (inputBlock, &input[8*i]);
        
    /* Chain if encrypting, and xor with whitener.
     */
    if (context->encrypt) {
      work[0] =
        inputBlock[0] ^ context->iv[0] ^ context->inputWhitener[0];
      work[1] =
        inputBlock[1] ^ context->iv[1] ^ context->inputWhitener[1];
    }
    else {
      work[0] = inputBlock[0] ^ context->outputWhitener[0];
      work[1] = inputBlock[1] ^ context->outputWhitener[1];         
    }

    DESFunction (work, context->subkeys);

    /* Xor with whitener, chain if decrypting, then update IV.
     */
    if (context->encrypt) {
      work[0] ^= context->outputWhitener[0];
      work[1] ^= context->outputWhitener[1];
      context->iv[0] = work[0];
      context->iv[1] = work[1];
    }
    else {
      work[0] ^= context->iv[0] ^ context->inputWhitener[0];
      work[1] ^= context->iv[1] ^ context->inputWhitener[1];
      context->iv[0] = inputBlock[0];
      context->iv[1] = inputBlock[1];
    }
    Unpack (&output[8*i], work);
  }
  
  /* Zeroize sensitive information.
   */
  R_memset ((POINTER)inputBlock, 0, sizeof (inputBlock));
  R_memset ((POINTER)work, 0, sizeof (work));
  
  return (0);
}

void DESX_CBCRestart (context)
DESX_CBC_CTX *context;
{
  /* Reset to the original IV */
  context->iv[0] = context->originalIV[0];
  context->iv[1] = context->originalIV[1];
}

/* Initialize context.  Caller must zeroize the context when finished.
 */
void DES3_CBCInit(context, key, iv, encrypt)
DES3_CBC_CTX *context;                                           /* context */
unsigned char key[24];                                               /* key */
unsigned char iv[8];                                 /* initializing vector */
int encrypt;                     /* encrypt flag (1 = encrypt, 0 = decrypt) */
{  
  /* Copy encrypt flag to context.
   */
  context->encrypt = encrypt;

  /* Pack initializing vector into context.
   */
  Pack (context->iv, iv);

  /* Save the IV for use in Restart */
  context->originalIV[0] = context->iv[0];
  context->originalIV[1] = context->iv[1];

  /* Precompute key schedules.
   */
  DESKey (context->subkeys[0], encrypt ? key : &key[16], encrypt);
  DESKey (context->subkeys[1], &key[8], !encrypt);
  DESKey (context->subkeys[2], encrypt ? &key[16] : key, encrypt);
}

int DES3_CBCUpdate (context, output, input, len)
DES3_CBC_CTX *context;                                           /* context */
unsigned char *output;                                      /* output block */
unsigned char *input;                                        /* input block */
unsigned int len;                      /* length of input and output blocks */
{
  UINT4 inputBlock[2], work[2];
  unsigned int i;
  
  if (len % 8)
    return (RE_LEN);

  for (i = 0; i < len/8; i++) {
    Pack (inputBlock, &input[8*i]);
        
    /* Chain if encrypting.
     */
    if (context->encrypt) {
      work[0] = inputBlock[0] ^ context->iv[0];
      work[1] = inputBlock[1] ^ context->iv[1];
    }
    else {
      work[0] = inputBlock[0];
      work[1] = inputBlock[1];         
    }

    DESFunction (work, context->subkeys[0]);
    DESFunction (work, context->subkeys[1]);
    DESFunction (work, context->subkeys[2]);

    /* Chain if decrypting, then update IV.
     */
    if (context->encrypt) {
      context->iv[0] = work[0];
      context->iv[1] = work[1];
    }
    else {
      work[0] ^= context->iv[0];
      work[1] ^= context->iv[1];
      context->iv[0] = inputBlock[0];
      context->iv[1] = inputBlock[1];
    }
    Unpack (&output[8*i], work);
  }
  
  /* Zeroize sensitive information.
   */
  R_memset ((POINTER)inputBlock, 0, sizeof (inputBlock));
  R_memset ((POINTER)work, 0, sizeof (work));
  
  return (0);
}

void DES3_CBCRestart (context)
DES3_CBC_CTX *context;
{
  /* Reset to the original IV */
  context->iv[0] = context->originalIV[0];
  context->iv[1] = context->originalIV[1];
}

static void Pack (into, outof)
UINT4 *into;
unsigned char *outof;
{
  *into    = (*outof++ & 0xffL) << 24;
  *into   |= (*outof++ & 0xffL) << 16;
  *into   |= (*outof++ & 0xffL) << 8;
  *into++ |= (*outof++ & 0xffL);
  *into    = (*outof++ & 0xffL) << 24;
  *into   |= (*outof++ & 0xffL) << 16;
  *into   |= (*outof++ & 0xffL) << 8;
  *into   |= (*outof   & 0xffL);
}

static void Unpack (into, outof)
unsigned char *into;
UINT4 *outof;
{
  *into++ = (unsigned char)((*outof >> 24) & 0xffL);
  *into++ = (unsigned char)((*outof >> 16) & 0xffL);
  *into++ = (unsigned char)((*outof >>  8) & 0xffL);
  *into++ = (unsigned char)( *outof++      & 0xffL);
  *into++ = (unsigned char)((*outof >> 24) & 0xffL);
  *into++ = (unsigned char)((*outof >> 16) & 0xffL);
  *into++ = (unsigned char)((*outof >>  8) & 0xffL);
  *into   = (unsigned char)( *outof        & 0xffL);
}

static void DESKey (subkeys, key, encrypt)
UINT4 subkeys[32];
unsigned char key[8];
int encrypt;
{
  UINT4 kn[32];
  int i, j, l, m, n;
  unsigned char pc1m[56], pcr[56];

  for (j = 0; j < 56; j++) {
    l = PC1[j];
    m = l & 07;
    pc1m[j] = (unsigned char)((key[l >> 3] & BYTE_BIT[m]) ? 1 : 0);
  }
  for (i = 0; i < 16; i++) {
    m = i << 1;
    n = m + 1;
    kn[m] = kn[n] = 0L;
    for (j = 0; j < 28; j++) {
      l = j + TOTAL_ROTATIONS[i];
      if (l < 28)
        pcr[j] = pc1m[l];
      else
        pcr[j] = pc1m[l - 28];
    }
    for (j = 28; j < 56; j++) {
      l = j + TOTAL_ROTATIONS[i];
      if (l < 56)
        pcr[j] = pc1m[l];
      else
        pcr[j] = pc1m[l - 28];
    }
    for (j = 0; j < 24; j++) {
      if (pcr[PC2[j]])
        kn[m] |= BIG_BYTE[j];
      if (pcr[PC2[j+24]])
        kn[n] |= BIG_BYTE[j];
    }
  }
  CookKey (subkeys, kn, encrypt);

  /* Zeroize sensitive information.
   */
  R_memset ((POINTER)pc1m, 0, sizeof (pc1m));
  R_memset ((POINTER)pcr, 0, sizeof (pcr));
  R_memset ((POINTER)kn, 0, sizeof (kn));
}

static void CookKey (subkeys, kn, encrypt)
UINT4 *subkeys;
UINT4 *kn;
int encrypt;
{
  UINT4 *cooked, *raw0, *raw1;
  int increment;
  unsigned int i;

  raw1 = kn;
  cooked = encrypt ? subkeys : &subkeys[30];
  increment = encrypt ? 1 : -3;

  for (i = 0; i < 16; i++, raw1++) {
    raw0 = raw1++;
    *cooked    = (*raw0 & 0x00fc0000L) << 6;
    *cooked   |= (*raw0 & 0x00000fc0L) << 10;
    *cooked   |= (*raw1 & 0x00fc0000L) >> 10;
    *cooked++ |= (*raw1 & 0x00000fc0L) >> 6;
    *cooked    = (*raw0 & 0x0003f000L) << 12;
    *cooked   |= (*raw0 & 0x0000003fL) << 16;
    *cooked   |= (*raw1 & 0x0003f000L) >> 4;
    *cooked   |= (*raw1 & 0x0000003fL);
    cooked += increment;
  }
}

static void DESFunction (block, subkeys)
UINT4 *block;
UINT4 *subkeys;
{
  register UINT4 fval, work, right, left;
  register int round;
  
  left = block[0];
  right = block[1];
  work = ((left >> 4) ^ right) & 0x0f0f0f0fL;
  right ^= work;
  left ^= (work << 4);
  work = ((left >> 16) ^ right) & 0x0000ffffL;
  right ^= work;
  left ^= (work << 16);
  work = ((right >> 2) ^ left) & 0x33333333L;
  left ^= work;
  right ^= (work << 2);
  work = ((right >> 8) ^ left) & 0x00ff00ffL;
  left ^= work;
  right ^= (work << 8);
  right = ((right << 1) | ((right >> 31) & 1L)) & 0xffffffffL;
  work = (left ^ right) & 0xaaaaaaaaL;
  left ^= work;
  right ^= work;
  left = ((left << 1) | ((left >> 31) & 1L)) & 0xffffffffL;
  
  for (round = 0; round < 8; round++) {
    work  = (right << 28) | (right >> 4);
    work ^= *subkeys++;
    fval  = SP7[ work        & 0x3fL];
    fval |= SP5[(work >>  8) & 0x3fL];
    fval |= SP3[(work >> 16) & 0x3fL];
    fval |= SP1[(work >> 24) & 0x3fL];
    work  = right ^ *subkeys++;
    fval |= SP8[ work        & 0x3fL];
    fval |= SP6[(work >>  8) & 0x3fL];
    fval |= SP4[(work >> 16) & 0x3fL];
    fval |= SP2[(work >> 24) & 0x3fL];
    left ^= fval;
    work  = (left << 28) | (left >> 4);
    work ^= *subkeys++;
    fval  = SP7[ work        & 0x3fL];
    fval |= SP5[(work >>  8) & 0x3fL];
    fval |= SP3[(work >> 16) & 0x3fL];
    fval |= SP1[(work >> 24) & 0x3fL];
    work  = left ^ *subkeys++;
    fval |= SP8[ work        & 0x3fL];
    fval |= SP6[(work >>  8) & 0x3fL];
    fval |= SP4[(work >> 16) & 0x3fL];
    fval |= SP2[(work >> 24) & 0x3fL];
    right ^= fval;
  }
  
  right = (right << 31) | (right >> 1);
  work = (left ^ right) & 0xaaaaaaaaL;
  left ^= work;
  right ^= work;
  left = (left << 31) | (left >> 1);
  work = ((left >> 8) ^ right) & 0x00ff00ffL;
  right ^= work;
  left ^= (work << 8);
  work = ((left >> 2) ^ right) & 0x33333333L;
  right ^= work;
  left ^= (work << 2);
  work = ((right >> 16) ^ left) & 0x0000ffffL;
  left ^= work;
  right ^= (work << 16);
  work = ((right >> 4) ^ left) & 0x0f0f0f0fL;
  left ^= work;
  right ^= (work << 4);
  *block++ = right;
  *block = left;
}
