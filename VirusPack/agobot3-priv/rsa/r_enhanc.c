/* R_ENHANC.C - cryptographic enhancements for RSAREF
 */

/* Copyright (C) RSA Laboratories, a division of RSA Data Security,
     Inc., created 1991. All rights reserved.
 */

#include "global.h"
#include "rsaref.h"
#include "r_random.h"
#include "rsa.h"

/* DigestInfo encoding is DIGEST_INFO_A, then 2 or 5 (for MD2/MD5),
   then DIGEST_INFO_B, then 16-byte message digest.
 */

static unsigned char DIGEST_INFO_A[] = {
  0x30, 0x20, 0x30, 0x0c, 0x06, 0x08, 0x2a, 0x86, 0x48, 0x86, 0xf7,
  0x0d, 0x02
};
#define DIGEST_INFO_A_LEN sizeof (DIGEST_INFO_A)

static unsigned char DIGEST_INFO_B[] = { 0x05, 0x00, 0x04, 0x10 };
#define DIGEST_INFO_B_LEN sizeof (DIGEST_INFO_B)

#define DIGEST_INFO_LEN (DIGEST_INFO_A_LEN + 1 + DIGEST_INFO_B_LEN + 16)

static unsigned char *PADDING[] = {
  (unsigned char *)"", (unsigned char *)"\001", (unsigned char *)"\002\002",
  (unsigned char *)"\003\003\003", (unsigned char *)"\004\004\004\004",
  (unsigned char *)"\005\005\005\005\005",
  (unsigned char *)"\006\006\006\006\006\006", 
  (unsigned char *)"\007\007\007\007\007\007\007",
  (unsigned char *)"\010\010\010\010\010\010\010\010"
};

#define MAX_ENCRYPTED_KEY_LEN MAX_RSA_MODULUS_LEN

static void R_EncodeDigestInfo PROTO_LIST
  ((unsigned char *, int, unsigned char *));
static void EncryptPEMUpdateFinal PROTO_LIST
  ((R_ENVELOPE_CTX *, unsigned char *, unsigned int *, unsigned char *,
    unsigned int));
static int DecryptPEMUpdateFinal PROTO_LIST
  ((R_ENVELOPE_CTX *, unsigned char *, unsigned int *, unsigned char *,
    unsigned int));
static int CipherInit PROTO_LIST
  ((R_ENVELOPE_CTX *, int, unsigned char *, unsigned char *, int));
static void CipherUpdate PROTO_LIST
  ((R_ENVELOPE_CTX *, unsigned char *, unsigned char *, unsigned int));
static void CipherRestart PROTO_LIST ((R_ENVELOPE_CTX *));

int R_DigestInit (context, digestAlgorithm)
R_DIGEST_CTX *context;                                       /* new context */
int digestAlgorithm;                            /* message-digest algorithm */
{
  context->digestAlgorithm = digestAlgorithm;

  switch (digestAlgorithm) {
  case DA_MD2:
    MD2Init (&context->context.md2);
    break;

  case DA_MD5:
    MD5Init (&context->context.md5);
    break;
  
  default:
    return (RE_DIGEST_ALGORITHM);
  }

  return (0);
}

int R_DigestUpdate (context, partIn, partInLen)
R_DIGEST_CTX *context;                                           /* context */
unsigned char *partIn;                                    /* next data part */
unsigned int partInLen;                         /* length of next data part */
{
  if (context->digestAlgorithm == DA_MD2)
    MD2Update (&context->context.md2, partIn, partInLen);
  else
    MD5Update (&context->context.md5, partIn, partInLen);
  return (0);
}

int R_DigestFinal (context, digest, digestLen)
R_DIGEST_CTX *context;                                           /* context */
unsigned char *digest;                                    /* message digest */
unsigned int *digestLen;                        /* length of message digest */
{
  *digestLen = 16;
  if (context->digestAlgorithm == DA_MD2)
    MD2Final (digest, &context->context.md2);
  else
    MD5Final (digest, &context->context.md5);

  return (0);
}

int R_SignInit (context, digestAlgorithm)
R_SIGNATURE_CTX *context;                                    /* new context */
int digestAlgorithm;                            /* message-digest algorithm */
{
  return (R_DigestInit (&context->digestContext, digestAlgorithm));
}

int R_SignUpdate (context, partIn, partInLen)
R_SIGNATURE_CTX *context;                                        /* context */
unsigned char *partIn;                                    /* next data part */
unsigned int partInLen;                         /* length of next data part */
{
  return (R_DigestUpdate (&context->digestContext, partIn, partInLen));
}

int R_SignFinal (context, signature, signatureLen, privateKey)
R_SIGNATURE_CTX *context;                                        /* context */
unsigned char *signature;                                      /* signature */
unsigned int *signatureLen;                          /* length of signature */
R_RSA_PRIVATE_KEY *privateKey;                  /* signer's RSA private key */
{
  int status;
  unsigned char digest[MAX_DIGEST_LEN], digestInfo[DIGEST_INFO_LEN];
  unsigned int digestLen;

  do {
    if ((status = R_DigestFinal (&context->digestContext, digest, &digestLen))
        != 0)
      break;

    R_EncodeDigestInfo
      (digestInfo, context->digestContext.digestAlgorithm, digest);
    
    if (RSAPrivateEncrypt
        (signature, signatureLen, digestInfo, DIGEST_INFO_LEN, privateKey)
        != 0) {
      status = RE_PRIVATE_KEY;
      break;
    }

    /* Reset for another verification. Assume Init won't fail */
    R_DigestInit
      (&context->digestContext, context->digestContext.digestAlgorithm);
  } while (0);
  
  /* Zeroize potentially sensitive information.
   */
  R_memset ((POINTER)digest, 0, sizeof (digest));
  R_memset ((POINTER)digestInfo, 0, sizeof (digestInfo));

  return (status);
}

int R_VerifyInit (context, digestAlgorithm)
R_SIGNATURE_CTX *context;                                    /* new context */
int digestAlgorithm;                            /* message-digest algorithm */
{
  return (R_DigestInit (&context->digestContext, digestAlgorithm));
}

int R_VerifyUpdate (context, partIn, partInLen)
R_SIGNATURE_CTX *context;                                        /* context */
unsigned char *partIn;                                    /* next data part */
unsigned int partInLen;                         /* length of next data part */
{
  return (R_DigestUpdate (&context->digestContext, partIn, partInLen));
}

int R_VerifyFinal (context, signature, signatureLen, publicKey)
R_SIGNATURE_CTX *context;                                        /* context */
unsigned char *signature;                                      /* signature */
unsigned int signatureLen;                           /* length of signature */
R_RSA_PUBLIC_KEY *publicKey;                     /* signer's RSA public key */
{
  int status;
  unsigned char digest[MAX_DIGEST_LEN], digestInfo[DIGEST_INFO_LEN],
    originalDigestInfo[MAX_SIGNATURE_LEN];
  unsigned int originalDigestInfoLen, digestLen;
  
  if (signatureLen > MAX_SIGNATURE_LEN)
    return (RE_LEN);

  status = 0;
  do {
    if ((status = R_DigestFinal (&context->digestContext, digest, &digestLen))
        != 0)
      break;

    R_EncodeDigestInfo
      (digestInfo, context->digestContext.digestAlgorithm, digest);
    
    if (RSAPublicDecrypt
        (originalDigestInfo, &originalDigestInfoLen, signature, signatureLen, 
         publicKey) != 0) {
      status = RE_PUBLIC_KEY;
      break;
    }
    
    if ((originalDigestInfoLen != DIGEST_INFO_LEN) ||
        (R_memcmp 
         ((POINTER)originalDigestInfo, (POINTER)digestInfo,
          DIGEST_INFO_LEN))) {
      status = RE_SIGNATURE;
      break;
    }

    /* Reset for another verification. Assume Init won't fail */
    R_DigestInit
      (&context->digestContext, context->digestContext.digestAlgorithm);
  } while (0);
  
  /* Zeroize potentially sensitive information.
   */
  R_memset ((POINTER)digest, 0, sizeof (digest));
  R_memset ((POINTER)digestInfo, 0, sizeof (digestInfo));
  R_memset ((POINTER)originalDigestInfo, 0, sizeof (originalDigestInfo));

  return (status);
}

/* Caller must ASCII recode the encrypted keys if desired.
 */
int R_SealInit
  (context, encryptedKeys, encryptedKeyLens, iv, publicKeyCount, publicKeys,
   encryptionAlgorithm, randomStruct)
R_ENVELOPE_CTX *context;                                     /* new context */
unsigned char **encryptedKeys;                            /* encrypted keys */
unsigned int *encryptedKeyLens;                /* lengths of encrypted keys */
unsigned char iv[8];                               /* initialization vector */
unsigned int publicKeyCount;                       /* number of public keys */
R_RSA_PUBLIC_KEY **publicKeys;                               /* public keys */
int encryptionAlgorithm;                       /* data encryption algorithm */
R_RANDOM_STRUCT *randomStruct;                          /* random structure */
{
  int status;
  unsigned char key[24];
  unsigned int keyLen, i;
  
  do {
    context->encryptionAlgorithm = encryptionAlgorithm;
    
    keyLen = (encryptionAlgorithm == EA_DES_CBC) ? 8 : 24;
    if ((status = R_GenerateBytes (key, keyLen, randomStruct)) != 0)
      break;
    if ((status = R_GenerateBytes (iv, 8, randomStruct)) != 0)
      break;

    if (encryptionAlgorithm == EA_DES_EDE2_CBC)
      /* Make both E keys the same */
      R_memcpy ((POINTER)(key + 16), (POINTER)key, 8);

    if ((status = CipherInit (context, encryptionAlgorithm, key, iv, 1)) != 0)
      break;

    for (i = 0; i < publicKeyCount; ++i) {
      if (RSAPublicEncrypt
          (encryptedKeys[i], &encryptedKeyLens[i], key, keyLen,
           publicKeys[i], randomStruct)) {
        status = RE_PUBLIC_KEY;
        break;
      }
    }
    if (status != 0)
      break;

    context->bufferLen = 0;
  } while (0);
  
  /* Zeroize sensitive information.
   */
  R_memset ((POINTER)key, 0, sizeof (key));

  return (status);
}

/* Assume partOut buffer is at least partInLen + 7, since this may flush
     buffered input.
 */
int R_SealUpdate (context, partOut, partOutLen, partIn, partInLen)
R_ENVELOPE_CTX *context;                                         /* context */
unsigned char *partOut;                         /* next encrypted data part */
unsigned int *partOutLen;             /* length of next encrypted data part */
unsigned char *partIn;                                    /* next data part */
unsigned int partInLen;                         /* length of next data part */
{
  unsigned int tempLen;

  tempLen = 8 - context->bufferLen;
  if (partInLen < tempLen) {
    /* Just accumulate into buffer.
     */
    R_memcpy
      ((POINTER)(context->buffer + context->bufferLen), (POINTER)partIn,
       partInLen);
    context->bufferLen += partInLen;
    *partOutLen = 0;
    return (0);
  }

  /* Fill the buffer and encrypt.
   */
  R_memcpy
    ((POINTER)(context->buffer + context->bufferLen), (POINTER)partIn,
     tempLen);
  CipherUpdate (context, partOut, context->buffer, 8);
  partIn += tempLen;
  partInLen -= tempLen;
  partOut += 8;
  *partOutLen = 8;

  /* Encrypt as many 8-byte blocks as possible.
   */
  tempLen = 8 * (partInLen / 8);
  CipherUpdate (context, partOut, partIn, tempLen);
  partIn += tempLen;
  partInLen -= tempLen;
  *partOutLen += tempLen;

  /* Length is now less than 8, so copy remainder to buffer.
   */
  R_memcpy
    ((POINTER)context->buffer, (POINTER)partIn,
     context->bufferLen = partInLen);

  return (0);
}

/* Assume partOut buffer is at least 8 bytes.
 */
int R_SealFinal (context, partOut, partOutLen)
R_ENVELOPE_CTX *context;                                         /* context */
unsigned char *partOut;                         /* last encrypted data part */
unsigned int *partOutLen;             /* length of last encrypted data part */
{
  unsigned int padLen;

  /* Pad and encrypt final block.
   */
  padLen = 8 - context->bufferLen;
  R_memset
    ((POINTER)(context->buffer + context->bufferLen), (int)padLen, padLen);
  CipherUpdate (context, partOut, context->buffer, 8);
  *partOutLen = 8;

  /* Restart the context.
   */
  CipherRestart (context);
  context->bufferLen = 0;

  return (0);
}

/* Assume caller has already ASCII decoded the encryptedKey if necessary.
 */
int R_OpenInit
  (context, encryptionAlgorithm, encryptedKey, encryptedKeyLen, iv, privateKey)
R_ENVELOPE_CTX *context;                                     /* new context */
int encryptionAlgorithm;                       /* data encryption algorithm */
unsigned char *encryptedKey;               /* encrypted data encryption key */
unsigned int encryptedKeyLen;                    /* length of encrypted key */
unsigned char iv[8];                               /* initialization vector */
R_RSA_PRIVATE_KEY *privateKey;               /* recipient's RSA private key */
{
  int status;
  unsigned char key[MAX_ENCRYPTED_KEY_LEN];
  unsigned int keyLen;
  
  if (encryptedKeyLen > MAX_ENCRYPTED_KEY_LEN)
    return (RE_LEN);
  
  do {
    context->encryptionAlgorithm = encryptionAlgorithm;

    if (RSAPrivateDecrypt
        (key, &keyLen, encryptedKey, encryptedKeyLen, privateKey)) {
      status = RE_PRIVATE_KEY;
      break;
    }

    if (encryptionAlgorithm == EA_DES_CBC) {    
      if (keyLen != 8) {
        status = RE_PRIVATE_KEY;
        break;
      }
    }
    else {
      if (keyLen != 24) {
        status = RE_PRIVATE_KEY;
        break;
      }
    }
    
    if ((status = CipherInit (context, encryptionAlgorithm, key, iv, 0)) != 0)
      break;

    context->bufferLen = 0;
  } while (0);
  
  /* Zeroize sensitive information.
   */
  R_memset ((POINTER)key, 0, sizeof (key));

  return (status);
}

/* Assume partOut buffer is at least partInLen + 7, since this may flush
     buffered input. Always leaves at least one byte in buffer.
 */
int R_OpenUpdate (context, partOut, partOutLen, partIn, partInLen)
R_ENVELOPE_CTX *context;                                         /* context */
unsigned char *partOut;                         /* next recovered data part */
unsigned int *partOutLen;             /* length of next recovered data part */
unsigned char *partIn;                          /* next encrypted data part */
unsigned int partInLen;               /* length of next encrypted data part */
{
  unsigned int tempLen;

  tempLen = 8 - context->bufferLen;
  if (partInLen <= tempLen) {
    /* Just accumulate into buffer.
     */
    R_memcpy
      ((POINTER)(context->buffer + context->bufferLen), (POINTER)partIn,
       partInLen);
    context->bufferLen += partInLen;
    *partOutLen = 0;
    return (0);
  }

  /* Fill the buffer and decrypt.  We know that there will be more left
       in partIn after decrypting the buffer.
   */
  R_memcpy
    ((POINTER)(context->buffer + context->bufferLen), (POINTER)partIn,
     tempLen);
  CipherUpdate (context, partOut, context->buffer, 8);
  partIn += tempLen;
  partInLen -= tempLen;
  partOut += 8;
  *partOutLen = 8;

  /* Decrypt as many 8 byte blocks as possible, leaving at least one byte
       in partIn.
   */
  tempLen = 8 * ((partInLen - 1) / 8);
  CipherUpdate (context, partOut, partIn, tempLen);
  partIn += tempLen;
  partInLen -= tempLen;
  *partOutLen += tempLen;

  /* Length is between 1 and 8, so copy into buffer.
   */
  R_memcpy
    ((POINTER)context->buffer, (POINTER)partIn,
     context->bufferLen = partInLen);

  return (0);
}

/* Assume partOut buffer is at least 7 bytes.
 */
int R_OpenFinal (context, partOut, partOutLen)
R_ENVELOPE_CTX *context;                                         /* context */
unsigned char *partOut;                         /* last recovered data part */
unsigned int *partOutLen;             /* length of last recovered data part */
{
  int status;
  unsigned char lastPart[8];
  unsigned int padLen;

  status = 0;
  do {
    if (context->bufferLen == 0)
      /* There was no input data to decrypt */
      *partOutLen = 0;
    else {
      if (context->bufferLen != 8) {
        status = RE_KEY;
        break;
      }

      /* Decrypt and strip padding from final block which is in buffer.
       */
      CipherUpdate (context, lastPart, context->buffer, 8);
    
      padLen = lastPart[7];
      if (padLen == 0 || padLen > 8) {
        status = RE_KEY;
        break;
      }
      if (R_memcmp 
          ((POINTER)&lastPart[8 - padLen], PADDING[padLen], padLen) != 0) {
        status = RE_KEY;
        break;
      }
      
      R_memcpy ((POINTER)partOut, (POINTER)lastPart, *partOutLen = 8 - padLen);
    }

    /* Restart the context.
     */
    CipherRestart (context);
    context->bufferLen = 0;
  } while (0);

  /* Zeroize sensitive information.
   */
  R_memset ((POINTER)lastPart, 0, sizeof (lastPart));

  return (status);
}

int R_SignPEMBlock 
  (encodedContent, encodedContentLen, encodedSignature, encodedSignatureLen,
   content, contentLen, recode, digestAlgorithm, privateKey)
unsigned char *encodedContent;                           /* encoded content */
unsigned int *encodedContentLen;               /* length of encoded content */
unsigned char *encodedSignature;                       /* encoded signature */
unsigned int *encodedSignatureLen;           /* length of encoded signature */
unsigned char *content;                                          /* content */
unsigned int contentLen;                               /* length of content */
int recode;                                                /* recoding flag */
int digestAlgorithm;                            /* message-digest algorithm */
R_RSA_PRIVATE_KEY *privateKey;                  /* signer's RSA private key */
{
  int status;
  unsigned char signature[MAX_SIGNATURE_LEN];
  unsigned int signatureLen;
  
  if ((status = R_SignBlock
       (signature, &signatureLen, content, contentLen, digestAlgorithm,
        privateKey)) != 0)
    return (status);

  R_EncodePEMBlock 
    (encodedSignature, encodedSignatureLen, signature, signatureLen);

  if (recode)
    R_EncodePEMBlock
    (encodedContent, encodedContentLen, content, contentLen);

  return (0);
}

int R_SignBlock
  (signature, signatureLen, block, blockLen, digestAlgorithm, privateKey)
unsigned char *signature;                                      /* signature */
unsigned int *signatureLen;                          /* length of signature */
unsigned char *block;                                              /* block */
unsigned int blockLen;                                   /* length of block */
int digestAlgorithm;                            /* message-digest algorithm */
R_RSA_PRIVATE_KEY *privateKey;                  /* signer's RSA private key */
{
  R_SIGNATURE_CTX context;
  int status;

  do {
    if ((status = R_SignInit (&context, digestAlgorithm)) != 0)
      break;
    if ((status = R_SignUpdate (&context, block, blockLen)) != 0)
      break;
    if ((status = R_SignFinal (&context, signature, signatureLen, privateKey))
        != 0)
      break;
  } while (0);

  /* Zeroize sensitive information. */
  R_memset ((POINTER)&context, 0, sizeof (context));

  return (status);
}

int R_VerifyPEMSignature 
  (content, contentLen, encodedContent, encodedContentLen, encodedSignature,
   encodedSignatureLen, recode, digestAlgorithm, publicKey)
unsigned char *content;                                          /* content */
unsigned int *contentLen;                              /* length of content */
unsigned char *encodedContent;                /* (possibly) encoded content */
unsigned int encodedContentLen;                /* length of encoded content */
unsigned char *encodedSignature;                       /* encoded signature */
unsigned int encodedSignatureLen;            /* length of encoded signature */
int recode;                                                /* recoding flag */
int digestAlgorithm;                            /* message-digest algorithm */
R_RSA_PUBLIC_KEY *publicKey;                     /* signer's RSA public key */
{
  unsigned char signature[MAX_SIGNATURE_LEN];
  unsigned int signatureLen;
  
  if (encodedSignatureLen > MAX_PEM_SIGNATURE_LEN)
    return (RE_SIGNATURE_ENCODING);
  
  if (recode) {
    if (R_DecodePEMBlock
        (content, contentLen, encodedContent, encodedContentLen))
      return (RE_CONTENT_ENCODING);
  }
  else {
    content = encodedContent;
    *contentLen = encodedContentLen;
  }
    
  if (R_DecodePEMBlock
      (signature, &signatureLen, encodedSignature, encodedSignatureLen))
    return (RE_SIGNATURE_ENCODING);
  
  return (R_VerifyBlockSignature 
          (content, *contentLen, signature, signatureLen, digestAlgorithm,
           publicKey));
}

int R_VerifyBlockSignature 
  (block, blockLen, signature, signatureLen, digestAlgorithm, publicKey)
unsigned char *block;                                              /* block */
unsigned int blockLen;                                   /* length of block */
unsigned char *signature;                                      /* signature */
unsigned int signatureLen;                           /* length of signature */
int digestAlgorithm;                            /* message-digest algorithm */
R_RSA_PUBLIC_KEY *publicKey;                     /* signer's RSA public key */
{
  R_SIGNATURE_CTX context;
  int status;

  do {
    if ((status = R_VerifyInit (&context, digestAlgorithm)) != 0)
      break;
    if ((status = R_VerifyUpdate (&context, block, blockLen)) != 0)
      break;
    if ((status = R_VerifyFinal (&context, signature, signatureLen, publicKey))
        != 0)
      break;
  } while (0);

  /* Zeroize sensitive information. */
  R_memset ((POINTER)&context, 0, sizeof (context));

  return (status);
}

int R_SealPEMBlock 
  (encryptedContent, encryptedContentLen, encryptedKey, encryptedKeyLen,
   encryptedSignature, encryptedSignatureLen, iv, content, contentLen,
   digestAlgorithm, publicKey, privateKey, randomStruct)
unsigned char *encryptedContent;              /* encoded, encrypted content */
unsigned int *encryptedContentLen;                                /* length */
unsigned char *encryptedKey;                      /* encoded, encrypted key */
unsigned int *encryptedKeyLen;                                    /* length */
unsigned char *encryptedSignature;          /* encoded, encrypted signature */
unsigned int *encryptedSignatureLen;                              /* length */
unsigned char iv[8];                           /* DES initialization vector */
unsigned char *content;                                          /* content */
unsigned int contentLen;                               /* length of content */
int digestAlgorithm;                           /* message-digest algorithms */
R_RSA_PUBLIC_KEY *publicKey;                  /* recipient's RSA public key */
R_RSA_PRIVATE_KEY *privateKey;                  /* signer's RSA private key */
R_RANDOM_STRUCT *randomStruct;                          /* random structure */
{
  R_ENVELOPE_CTX context;
  R_RSA_PUBLIC_KEY *publicKeys[1];
  int status;
  unsigned char encryptedKeyBlock[MAX_ENCRYPTED_KEY_LEN],
    signature[MAX_SIGNATURE_LEN], *encryptedKeys[1];
  unsigned int signatureLen, encryptedKeyBlockLen;
  
  do {
    if ((status = R_SignBlock
         (signature, &signatureLen, content, contentLen, digestAlgorithm,
          privateKey)) != 0)
      break;

    publicKeys[0] = publicKey;
    encryptedKeys[0] = encryptedKeyBlock;
    if ((status = R_SealInit
         (&context, encryptedKeys, &encryptedKeyBlockLen, iv, 1, publicKeys,
          EA_DES_CBC, randomStruct)) != 0)
      break;

    R_EncodePEMBlock 
      (encryptedKey, encryptedKeyLen, encryptedKeyBlock,
       encryptedKeyBlockLen);

    EncryptPEMUpdateFinal
      (&context, encryptedContent, encryptedContentLen, content,
       contentLen);
    
    EncryptPEMUpdateFinal
      (&context, encryptedSignature, encryptedSignatureLen, signature,
       signatureLen);
  } while (0);
  
  /* Zeroize sensitive information.
   */
  R_memset ((POINTER)&context, 0, sizeof (context));
  R_memset ((POINTER)signature, 0, sizeof (signature));

  return (status);
}

int R_OpenPEMBlock
  (content, contentLen, encryptedContent, encryptedContentLen, encryptedKey,
   encryptedKeyLen, encryptedSignature, encryptedSignatureLen,
   iv, digestAlgorithm, privateKey, publicKey)
unsigned char *content;                                          /* content */
unsigned int *contentLen;                              /* length of content */
unsigned char *encryptedContent;              /* encoded, encrypted content */
unsigned int encryptedContentLen;                                 /* length */
unsigned char *encryptedKey;                      /* encoded, encrypted key */
unsigned int encryptedKeyLen;                                     /* length */
unsigned char *encryptedSignature;          /* encoded, encrypted signature */
unsigned int encryptedSignatureLen;                               /* length */
unsigned char iv[8];                           /* DES initialization vector */
int digestAlgorithm;                           /* message-digest algorithms */
R_RSA_PRIVATE_KEY *privateKey;               /* recipient's RSA private key */
R_RSA_PUBLIC_KEY *publicKey;                     /* signer's RSA public key */
{
  R_ENVELOPE_CTX context;
  int status;
  unsigned char encryptedKeyBlock[MAX_ENCRYPTED_KEY_LEN],
    signature[MAX_SIGNATURE_LEN];
  unsigned int encryptedKeyBlockLen, signatureLen;
  
  if (encryptedKeyLen > MAX_PEM_ENCRYPTED_KEY_LEN)
    return (RE_KEY_ENCODING);
  
  if (encryptedSignatureLen > MAX_PEM_ENCRYPTED_SIGNATURE_LEN)
    return (RE_SIGNATURE_ENCODING);
  
  do {
    if (R_DecodePEMBlock 
        (encryptedKeyBlock, &encryptedKeyBlockLen, encryptedKey,
         encryptedKeyLen) != 0) {
      status = RE_KEY_ENCODING;
      break;
    }

    if ((status = R_OpenInit
         (&context, EA_DES_CBC, encryptedKeyBlock, encryptedKeyBlockLen,
          iv, privateKey)) != 0)
      break;

    if ((status = DecryptPEMUpdateFinal
         (&context, content, contentLen, encryptedContent,
          encryptedContentLen)) != 0) {
      if ((status == RE_LEN || status == RE_ENCODING))
        status = RE_CONTENT_ENCODING;
      else
        status = RE_KEY;
      break;
    }
    
    if (status = DecryptPEMUpdateFinal
        (&context, signature, &signatureLen, encryptedSignature,
         encryptedSignatureLen)) {
      if ((status == RE_LEN || status == RE_ENCODING))
        status = RE_SIGNATURE_ENCODING;
      else
        status = RE_KEY;
      break;
    }

    if ((status = R_VerifyBlockSignature
         (content, *contentLen, signature, signatureLen, digestAlgorithm,
          publicKey)) != 0)
      break;
  } while (0);
  
  /* Zeroize sensitive information.
   */
  R_memset ((POINTER)&context, 0, sizeof (context));
  R_memset ((POINTER)signature, 0, sizeof (signature));

  return (status);
}

int R_DigestBlock (digest, digestLen, block, blockLen, digestAlgorithm)
unsigned char *digest;                                    /* message digest */
unsigned int *digestLen;                        /* length of message digest */
unsigned char *block;                                              /* block */
unsigned int blockLen;                                   /* length of block */
int digestAlgorithm;                            /* message-digest algorithm */
{
  R_DIGEST_CTX context;
  int status;

  do {
    if ((status = R_DigestInit (&context, digestAlgorithm)) != 0)
      break;
    if ((status = R_DigestUpdate (&context, block, blockLen)) != 0)
      break;
    if ((status = R_DigestFinal (&context, digest, digestLen)) != 0)
      break;
  } while (0);

  /* Zeroize sensitive information. */
  R_memset ((POINTER)&context, 0, sizeof (context));

  return (status);
}

/* Assumes digestAlgorithm is DA_MD2 or DA_MD5 and digest length is 16.
 */
static void R_EncodeDigestInfo (digestInfo, digestAlgorithm, digest)
unsigned char *digestInfo;                           /* DigestInfo encoding */
int digestAlgorithm;                            /* message-digest algorithm */
unsigned char *digest;                                    /* message digest */
{
  R_memcpy 
    ((POINTER)digestInfo, (POINTER)DIGEST_INFO_A, DIGEST_INFO_A_LEN);
  
  digestInfo[DIGEST_INFO_A_LEN] =
    (digestAlgorithm == DA_MD2) ? (unsigned char)2 : (unsigned char)5;

  R_memcpy 
    ((POINTER)&digestInfo[DIGEST_INFO_A_LEN + 1], (POINTER)DIGEST_INFO_B,
     DIGEST_INFO_B_LEN);
  
  R_memcpy 
    ((POINTER)&digestInfo[DIGEST_INFO_A_LEN + 1 + DIGEST_INFO_B_LEN],
     (POINTER)digest, 16);
}

/* Call SealUpdate and SealFinal on the input and ASCII recode.
 */
static void EncryptPEMUpdateFinal
  (context, output, outputLen, input, inputLen)
R_ENVELOPE_CTX *context;
unsigned char *output;                          /* encrypted, encoded block */
unsigned int *outputLen;                                /* length of output */
unsigned char *input;                                   /* block to encrypt */
unsigned int inputLen;                                            /* length */
{
  unsigned char encryptedPart[24];
  unsigned int i, lastPartLen, tempLen, len;

  /* Choose a buffer size of 24 bytes to hold the temporary encrypted output
       which will be encoded.
     Encrypt and encode as many 24-byte blocks as possible.
   */
  for (i = 0; i < inputLen / 24; ++i) {
    /* Assume part out length will equal part in length since it is
         a multiple of 8.  Also assume no error output. */
    R_SealUpdate (context, encryptedPart, &tempLen, &input[24*i], 24);

    /* len is always 32 */
    R_EncodePEMBlock (&output[32*i], &tempLen, encryptedPart, 24);
  }
  
  /* Encrypt the last part into encryptedPart.
   */  
  R_SealUpdate
    (context, encryptedPart, &lastPartLen, &input[24*i], inputLen - 24*i);
  R_SealFinal (context, encryptedPart + lastPartLen, &len);
  lastPartLen += len;

  R_EncodePEMBlock (&output[32*i], &len, encryptedPart, lastPartLen);
  *outputLen = 32*i + len;

  /* Zeroize sensitive information.
   */
  R_memset ((POINTER)encryptedPart, 0, sizeof (encryptedPart));
}

static int DecryptPEMUpdateFinal (context, output, outputLen, input, inputLen)
R_ENVELOPE_CTX *context;
unsigned char *output;                          /* decoded, decrypted block */
unsigned int *outputLen;                                /* length of output */
unsigned char *input;                           /* encrypted, encoded block */
unsigned int inputLen;                                            /* length */
{
  int status;
  unsigned char encryptedPart[24];
  unsigned int i, len;
  
  do {
    /* Choose a buffer size of 24 bytes to hold the temporary decoded output
         which will be decrypted.
       Decode and decrypt as many 32-byte input blocks as possible.
     */
    *outputLen = 0;
    for (i = 0; i < inputLen/32; i++) {
      /* len is always 24 */
      if ((status = R_DecodePEMBlock
           (encryptedPart, &len, &input[32*i], 32)) != 0)
        break;

      /* Excpect no error return */
      R_OpenUpdate (context, output, &len, encryptedPart, 24);
      output += len;
      *outputLen += len;
    }
    if (status)
      break;

    /* Decode the last part */  
    if ((status = R_DecodePEMBlock
         (encryptedPart, &len, &input[32*i], inputLen - 32*i)) != 0)
      break;

    /* Decrypt the last part.
     */
    R_OpenUpdate (context, output, &len, encryptedPart, len);
    output += len;
    *outputLen += len;
    if ((status = R_OpenFinal (context, output, &len)) != 0)
      break;
    *outputLen += len;
  } while (0);

  /* Zeroize sensitive information.
   */
  R_memset ((POINTER)&context, 0, sizeof (context));
  R_memset ((POINTER)encryptedPart, 0, sizeof (encryptedPart));

  return (status);
}

static int CipherInit (context, encryptionAlgorithm, key, iv, encrypt)
R_ENVELOPE_CTX *context;
int encryptionAlgorithm;
unsigned char *key;                                              /* DES key */
unsigned char *iv;                             /* DES initialization vector */
int encrypt;                     /* encrypt flag (1 = encrypt, 0 = decrypt) */
{
  switch (encryptionAlgorithm) {
  case EA_DES_CBC:
    DES_CBCInit (&context->cipherContext.des, key, iv, encrypt);
    return (0);
  case EA_DESX_CBC:
    DESX_CBCInit (&context->cipherContext.desx, key, iv, encrypt);
    return (0);
  case EA_DES_EDE2_CBC:
  case EA_DES_EDE3_CBC:
    DES3_CBCInit (&context->cipherContext.des3, key, iv, encrypt);
    return (0);

  default:
    return (RE_ENCRYPTION_ALGORITHM);
  }
}

/* Assume len is a multiple of 8.
 */
static void CipherUpdate (context, output, input, len)
R_ENVELOPE_CTX *context;
unsigned char *output;                                      /* output block */
unsigned char *input;                                        /* input block */
unsigned int len;                      /* length of input and output blocks */
{
  if (context->encryptionAlgorithm == EA_DES_CBC)
    DES_CBCUpdate (&context->cipherContext.des, output, input, len);
  else if (context->encryptionAlgorithm == EA_DESX_CBC)
    DESX_CBCUpdate (&context->cipherContext.desx, output, input, len);
  else
    DES3_CBCUpdate (&context->cipherContext.des3, output, input, len);
}

static void CipherRestart (context)
R_ENVELOPE_CTX *context;
{
  if (context->encryptionAlgorithm == EA_DES_CBC)
    DES_CBCRestart (&context->cipherContext.des);
  else if (context->encryptionAlgorithm == EA_DESX_CBC)
    DESX_CBCRestart (&context->cipherContext.desx);
  else
    DES3_CBCRestart (&context->cipherContext.des3);
}
