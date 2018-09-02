/* R_ENCODE.C - RFC 1113 encoding and decoding routines
 */

/* Copyright (C) RSA Laboratories, a division of RSA Data Security,
     Inc., created 1991. All rights reserved.
 */

#include "global.h"
#include "rsaref.h"

/* RFC 1113 encoding:

   Value Encoding  Value Encoding  Value Encoding  Value Encoding
       0 A            17 R            34 i            51 z
       1 B            18 S            35 j            52 0
       2 C            19 T            36 k            53 1
       3 D            20 U            37 l            54 2
       4 E            21 V            38 m            55 3
       5 F            22 W            39 n            56 4
       6 G            23 X            40 o            57 5
       7 H            24 Y            41 p            58 6
       8 I            25 Z            42 q            59 7
       9 J            26 a            43 r            60 8
      10 K            27 b            44 s            61 9
      11 L            28 c            45 t            62 +
      12 M            29 d            46 u            63 /
      13 N            30 e            47 v
      14 O            31 f            48 w         (pad) =
      15 P            32 g            49 x
      16 Q            33 h            50 y
*/
#define ENCODING(i) \
  (unsigned char)(((i) < 26) ? ((i) + 0x41) : \
                  (((i) < 52) ? ((i) - 26 + 0x61) : \
                   (((i) < 62) ? ((i) - 52 + 0x30) : \
                    (((i) == 62) ? 0x2b : 0x2f))))
#define ENCODING_PAD 0x3d

#define IS_ENCODING(c) \
  ((((c) >= 0x41) && ((c) <= 0x5a)) || \
   (((c) >= 0x61) && ((c) <= 0x7a)) || \
   (((c) >= 0x30) && ((c) <= 0x39)) || \
   ((c) == 0x2b) || \
   ((c) == 0x2f))

/* assumes IS_ENCODING (c) == 1 */
#define DECODING(c) \
  (((c) == 0x2b) ? 62 : \
   (((c) == 0x2f) ? 63 : \
    (((c) <= 0x39) ? ((c) - 0x30 + 52) : \
     (((c) <= 0x5a) ? ((c) - 0x41) : ((c) - 0x61 + 26)))))
      
static void EncodeQuantum PROTO_LIST ((unsigned char [4], unsigned char [3]));
static int DecodeQuantum PROTO_LIST ((unsigned char [3], unsigned char [4]));
static void EncodeLastQuantum
  PROTO_LIST ((unsigned char [4], unsigned char *, unsigned int));
static int DecodeLastQuantum
  PROTO_LIST ((unsigned char *, unsigned int *, unsigned char [4]));

/* This always returns 0.  It is an int function for future compatibility.
 */
int R_EncodePEMBlock (encodedBlock, encodedBlockLen, block, blockLen)
unsigned char *encodedBlock;                               /* encoded block */
unsigned int *encodedBlockLen;                   /* length of encoded block */
unsigned char *block;                                              /* block */
unsigned int blockLen;                                   /* length of block */
{
  unsigned int i, lastLen;
  
  if (blockLen < 1) {
    *encodedBlockLen = 0;
    return (0);
  }
  
  for (i = 0; i < (blockLen-1)/3; i++)
    EncodeQuantum (&encodedBlock[4*i], &block[3*i]);
  
  lastLen = blockLen - 3*i;
  EncodeLastQuantum (&encodedBlock[4*i], &block[3*i], lastLen);
  *encodedBlockLen = 4*i + 4;

  return (0);
}
                    
int R_DecodePEMBlock (block, blockLen, encodedBlock, encodedBlockLen)
unsigned char *block;                                              /* block */
unsigned int *blockLen;                                  /* length of block */
unsigned char *encodedBlock;                               /* encoded block */
unsigned int encodedBlockLen;                    /* length of encoded block */
{
  int status;
  unsigned int i, lastLen;

  if (encodedBlockLen % 4)
    return (RE_ENCODING);
  
  if (encodedBlockLen < 1) {
    *blockLen = 0;
    return (0);
  }
  
  for (i = 0; i < (encodedBlockLen-1)/4; i++)
    if (status = DecodeQuantum (&block[3*i], &encodedBlock[4*i]))
      return (status);
    
  if (status = DecodeLastQuantum (&block[3*i], &lastLen, &encodedBlock[4*i]))
    return (status);

  *blockLen = 3*i + lastLen;
  return (0);
}

static void EncodeQuantum (encodedQuantum, quantum)
unsigned char encodedQuantum[4];
unsigned char quantum[3];
{
  UINT4 temp;
  unsigned int a, b, c, d;
  
  temp = ((UINT4)quantum[0]) << 16;
  temp |= ((UINT4)quantum[1]) << 8;
  temp |= (UINT4)quantum[2];
  
  a = (unsigned int)((temp >> 18) & 0x3f);
  b = (unsigned int)((temp >> 12) & 0x3f);
  c = (unsigned int)((temp >> 6) & 0x3f);
  d = (unsigned int)(temp & 0x3f);

  encodedQuantum[0] = ENCODING (a);
  encodedQuantum[1] = ENCODING (b);
  encodedQuantum[2] = ENCODING (c);
  encodedQuantum[3] = ENCODING (d);

  /* Zeroize potentially sensitive information.
   */
  temp = 0;
  a = b = c = d = 0;
}

static int DecodeQuantum (quantum, encodedQuantum)
unsigned char quantum[3];
unsigned char encodedQuantum[4];
{
  UINT4 temp;
  unsigned int a, b, c, d;
  
  if (! IS_ENCODING (encodedQuantum[0]) ||
      ! IS_ENCODING (encodedQuantum[1]) ||
      ! IS_ENCODING (encodedQuantum[2]) ||
      ! IS_ENCODING (encodedQuantum[3]))
    return (RE_ENCODING);
  
  a = DECODING (encodedQuantum[0]);
  b = DECODING (encodedQuantum[1]);
  c = DECODING (encodedQuantum[2]);
  d = DECODING (encodedQuantum[3]);
  
  temp = ((UINT4)a) << 18;
  temp |= ((UINT4)b) << 12;
  temp |= ((UINT4)c) << 6;
  temp |= (UINT4)d;

  quantum[0] = (unsigned char)(temp >> 16);
  quantum[1] = (unsigned char)(temp >> 8);
  quantum[2] = (unsigned char)temp;
  
  /* Zeroize potentially sensitive information.
   */
  temp = 0;
  a = b = c = d = 0;

  return (0);
}

static void EncodeLastQuantum (encodedQuantum, quantum, quantumLen)
unsigned char encodedQuantum[4];
unsigned char *quantum;
unsigned int quantumLen;                                       /* 1, 2 or 3 */
{
  UINT4 temp;
  unsigned int a, b, c, d;

  temp = ((UINT4)quantum[0]) << 16;
  if (quantumLen >= 2)
    temp |= ((UINT4)quantum[1]) << 8;
  if (quantumLen == 3)
    temp |= ((UINT4)quantum[2]);
  
  a = (unsigned int)((temp >> 18) & 0x3f);
  b = (unsigned int)((temp >> 12) & 0x3f);
  if (quantumLen >= 2)
    c = (unsigned int)((temp >> 6) & 0x3f);
  if (quantumLen == 3)
    d = (unsigned int)(temp & 0x3f);

  encodedQuantum[0] = ENCODING (a);
  encodedQuantum[1] = ENCODING (b);
  if (quantumLen >= 2)
    encodedQuantum[2] = ENCODING (c);
  else
    encodedQuantum[2] = ENCODING_PAD;
  if (quantumLen == 3)
    encodedQuantum[3] = ENCODING (d);
  else
    encodedQuantum[3] = ENCODING_PAD;

  /* Zeroize potentially sensitive information.
   */
  temp = 0;
  a = b = c = d = 0;
}

static int DecodeLastQuantum (quantum, quantumLen, encodedQuantum)
unsigned char *quantum;
unsigned int *quantumLen;                                      /* 1, 2 or 3 */
unsigned char encodedQuantum[4];
{
  UINT4 temp;
  unsigned int a, b, c, d;
  
  if (! IS_ENCODING (encodedQuantum[0]) ||
      ! IS_ENCODING (encodedQuantum[1]) ||
      (! IS_ENCODING (encodedQuantum[2]) &&
       (encodedQuantum[2] != ENCODING_PAD)) ||
      (! IS_ENCODING (encodedQuantum[3]) &&
       (encodedQuantum[3] != ENCODING_PAD)))
    return (RE_ENCODING);
        
  if (encodedQuantum[2] == ENCODING_PAD)
    *quantumLen = 1;
  else if (encodedQuantum[3] == ENCODING_PAD)
    *quantumLen = 2;
  else
    *quantumLen = 3;
  
  a = DECODING (encodedQuantum[0]);
  b = DECODING (encodedQuantum[1]);
  if (*quantumLen >= 2)
    c = DECODING (encodedQuantum[2]);
  if (*quantumLen == 3)
    d = DECODING (encodedQuantum[3]);
  
  temp = ((UINT4)a) << 18;
  temp |= ((UINT4)b) << 12;
  if (*quantumLen >= 2)
    temp |= ((UINT4)c) << 6;
  if (*quantumLen == 3)
    temp |= ((UINT4)d);

  quantum[0] = (unsigned char)(temp >> 16);
  if (*quantumLen >= 2)
    quantum[1] = (unsigned char)(temp >> 8);
  if (*quantumLen == 3)
    quantum[2] = (unsigned char)temp;
  
  /* Zeroize potentially sensitive information.
   */
  temp = 0;
  a = b = c = d = 0;
  
  return (0);
}
