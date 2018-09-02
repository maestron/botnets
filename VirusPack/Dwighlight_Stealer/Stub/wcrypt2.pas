unit wcrypt2;

{.DEFINE NT5}

{$ALIGN ON}

{$IFNDEF VER90}
  {$WEAKPACKAGEUNIT}
{$ENDIF}

interface

uses
  Windows
  {$IFDEF VER90}
  ,Ole2
  {$ENDIF};

const
  ADVAPI32    = 'advapi32.dll';
{$IFDEF NT5}
  ADVAPI32NT5 = 'advapi32.dll';
{$ENDIF}

{Support Type}

type
  HCRYPTPROV  = ULONG;
  PHCRYPTPROV = ^HCRYPTPROV;
  HCRYPTKEY   = ULONG;
  PHCRYPTKEY  = ^HCRYPTKEY;
  HCRYPTHASH  = ULONG;
  PHCRYPTHASH = ^HCRYPTHASH;


type
    PVOID = Pointer;
    LONG  = DWORD;
    {$IFDEF UNICODE}
      LPAWSTR = PWideChar;
    {$ELSE}
      LPAWSTR = PAnsiChar;
    {$ENDIF}

//-----------------------------------------------------------------------------
    // Type support for a pointer to an array of pointer (type **name)
    PLPSTR          = Pointer; // type for a pointer to Array of pointer a type
    PPCERT_INFO     = Pointer; // type for a pointer to Array of pointer a type
    PPVOID          = Pointer; // type for a pointer to Array of pointer a type
    PPCCERT_CONTEXT = Pointer; // type for a pointer to Array of pointer a type
    PPCCTL_CONTEXT  = Pointer; // type for a pointer to Array of pointer a type
    PPCCRL_CONTEXT  = Pointer; // type for a pointer to Array of pointer a type
//-----------------------------------------------------------------------------

//+---------------------------------------------------------------------------
//
//  Microsoft Windows
//  Copyright (C) Microsoft Corporation, 1992 - 1997.
//
//  File:       wincrypt.h
//
//  Contents:   Cryptographic API Prototypes and Definitions
//
//----------------------------------------------------------------------------


//
// Algorithm IDs and Flags
//

// ALG_ID crackers

Const
  // Algorithm classes
  ALG_CLASS_ANY          = 0;
  ALG_CLASS_SIGNATURE    = (1 shl 13);
  ALG_CLASS_MSG_ENCRYPT  = (2 shl 13);
  ALG_CLASS_DATA_ENCRYPT = (3 shl 13);
  ALG_CLASS_HASH         = (4 shl 13);
  ALG_CLASS_KEY_EXCHANGE = (5 shl 13);

  // Algorithm types
  ALG_TYPE_ANY           = 0;
  ALG_TYPE_DSS           = (1 shl 9);
  ALG_TYPE_RSA           = (2 shl 9);
  ALG_TYPE_BLOCK         = (3 shl 9);
  ALG_TYPE_STREAM        = (4 shl 9);
  ALG_TYPE_DH            = (5 shl 9);
  ALG_TYPE_SECURECHANNEL = (6 shl 9);

  // Generic sub-ids
  ALG_SID_ANY = 0;

  // Some RSA sub-ids
  ALG_SID_RSA_ANY        = 0;
  ALG_SID_RSA_PKCS       = 1;
  ALG_SID_RSA_MSATWORK   = 2;
  ALG_SID_RSA_ENTRUST    = 3;
  ALG_SID_RSA_PGP        = 4;

  // Some DSS sub-ids
  ALG_SID_DSS_ANY        = 0;
  ALG_SID_DSS_PKCS       = 1;
  ALG_SID_DSS_DMS        = 2;

  // Block cipher sub ids
  // DES sub_ids
  ALG_SID_DES            = 1;
  ALG_SID_3DES           = 3;
  ALG_SID_DESX           = 4;
  ALG_SID_IDEA           = 5;
  ALG_SID_CAST           = 6;
  ALG_SID_SAFERSK64      = 7;
  ALD_SID_SAFERSK128     = 8;
  ALG_SID_SAFERSK128     = 8;
  ALG_SID_3DES_112       = 9;
  ALG_SID_CYLINK_MEK     = 12;
  ALG_SID_RC5            = 13;

  // Fortezza sub-ids
  ALG_SID_SKIPJACK       = 10;
  ALG_SID_TEK            = 11;

  // KP_MODE
  CRYPT_MODE_CBCI        = 6;  {ANSI CBC Interleaved}
  CRYPT_MODE_CFBP        = 7;  {ANSI CFB Pipelined}
  CRYPT_MODE_OFBP        = 8;  {ANSI OFB Pipelined}
  CRYPT_MODE_CBCOFM      = 9;  {ANSI CBC + OF Masking}
  CRYPT_MODE_CBCOFMI     = 10; {ANSI CBC + OFM Interleaved}

  // RC2 sub-ids
  ALG_SID_RC2            = 2;

  // Stream cipher sub-ids
  ALG_SID_RC4            = 1;
  ALG_SID_SEAL           = 2;

  // Diffie-Hellman sub-ids
  ALG_SID_DH_SANDF       = 1;
  ALG_SID_DH_EPHEM       = 2;
  ALG_SID_AGREED_KEY_ANY = 3;
  ALG_SID_KEA            = 4;

  // Hash sub ids
  ALG_SID_MD2            = 1;
  ALG_SID_MD4            = 2;
  ALG_SID_MD5            = 3;
  ALG_SID_SHA            = 4;
  ALG_SID_SHA1           = 4;
  ALG_SID_MAC            = 5;
  ALG_SID_RIPEMD         = 6;
  ALG_SID_RIPEMD160      = 7;
  ALG_SID_SSL3SHAMD5     = 8;
  ALG_SID_HMAC           = 9;

  // secure channel sub ids
  ALG_SID_SSL3_MASTER          = 1;
  ALG_SID_SCHANNEL_MASTER_HASH = 2;
  ALG_SID_SCHANNEL_MAC_KEY     = 3;
  ALG_SID_PCT1_MASTER          = 4;
  ALG_SID_SSL2_MASTER          = 5;
  ALG_SID_TLS1_MASTER          = 6;
  ALG_SID_SCHANNEL_ENC_KEY     = 7;

  // Our silly example sub-id
  ALG_SID_EXAMPLE              = 80;

{$IFNDEF ALGIDDEF}
  {$DEFINE ALGIDDEF}
Type ALG_ID = ULONG;
{$ENDIF}

// algorithm identifier definitions
Const
  CALG_MD2              = (ALG_CLASS_HASH or ALG_TYPE_ANY or ALG_SID_MD2);
  CALG_MD4              = (ALG_CLASS_HASH or ALG_TYPE_ANY or ALG_SID_MD4);
  CALG_MD5              = (ALG_CLASS_HASH or ALG_TYPE_ANY or ALG_SID_MD5);
  CALG_SHA              = (ALG_CLASS_HASH or ALG_TYPE_ANY or ALG_SID_SHA);
  CALG_SHA1             = (ALG_CLASS_HASH or ALG_TYPE_ANY or ALG_SID_SHA1);
  CALG_MAC              = (ALG_CLASS_HASH or ALG_TYPE_ANY or ALG_SID_MAC);
  CALG_RSA_SIGN         = (ALG_CLASS_SIGNATURE or ALG_TYPE_RSA or ALG_SID_RSA_ANY);
  CALG_DSS_SIGN         = (ALG_CLASS_SIGNATURE or ALG_TYPE_DSS or ALG_SID_DSS_ANY);
  CALG_RSA_KEYX         = (ALG_CLASS_KEY_EXCHANGE or ALG_TYPE_RSA or ALG_SID_RSA_ANY);
  CALG_DES              = (ALG_CLASS_DATA_ENCRYPT or ALG_TYPE_BLOCK or ALG_SID_DES);
  CALG_3DES_112         = (ALG_CLASS_DATA_ENCRYPT or ALG_TYPE_BLOCK or ALG_SID_3DES_112);
  CALG_3DES             = (ALG_CLASS_DATA_ENCRYPT or ALG_TYPE_BLOCK or ALG_SID_3DES);
  CALG_RC2              = (ALG_CLASS_DATA_ENCRYPT or ALG_TYPE_BLOCK or ALG_SID_RC2);
  CALG_RC4              = (ALG_CLASS_DATA_ENCRYPT or ALG_TYPE_STREAM or ALG_SID_RC4);
  CALG_SEAL             = (ALG_CLASS_DATA_ENCRYPT or ALG_TYPE_STREAM or ALG_SID_SEAL);
  CALG_DH_SF            = (ALG_CLASS_KEY_EXCHANGE or ALG_TYPE_DH or ALG_SID_DH_SANDF);
  CALG_DH_EPHEM         = (ALG_CLASS_KEY_EXCHANGE  or  ALG_TYPE_DH  or  ALG_SID_DH_EPHEM);
  CALG_AGREEDKEY_ANY    = (ALG_CLASS_KEY_EXCHANGE  or ALG_TYPE_DH or ALG_SID_AGREED_KEY_ANY);
  CALG_KEA_KEYX         = (ALG_CLASS_KEY_EXCHANGE or ALG_TYPE_DH or ALG_SID_KEA);
  CALG_HUGHES_MD5       = (ALG_CLASS_KEY_EXCHANGE or ALG_TYPE_ANY or ALG_SID_MD5);
  CALG_SKIPJACK         = (ALG_CLASS_DATA_ENCRYPT or ALG_TYPE_BLOCK or ALG_SID_SKIPJACK);
  CALG_TEK              = (ALG_CLASS_DATA_ENCRYPT or ALG_TYPE_BLOCK or ALG_SID_TEK);
  CALG_CYLINK_MEK       = (ALG_CLASS_DATA_ENCRYPT or ALG_TYPE_BLOCK or ALG_SID_CYLINK_MEK);
  CALG_SSL3_SHAMD5      = (ALG_CLASS_HASH  or  ALG_TYPE_ANY  or  ALG_SID_SSL3SHAMD5);
  CALG_SSL3_MASTER      = (ALG_CLASS_MSG_ENCRYPT or ALG_TYPE_SECURECHANNEL or ALG_SID_SSL3_MASTER);
  CALG_SCHANNEL_MASTER_HASH = (ALG_CLASS_MSG_ENCRYPT or ALG_TYPE_SECURECHANNEL or ALG_SID_SCHANNEL_MASTER_HASH);
  CALG_SCHANNEL_MAC_KEY = (ALG_CLASS_MSG_ENCRYPT or ALG_TYPE_SECURECHANNEL or ALG_SID_SCHANNEL_MAC_KEY);
  CALG_SCHANNEL_ENC_KEY = (ALG_CLASS_MSG_ENCRYPT or ALG_TYPE_SECURECHANNEL or ALG_SID_SCHANNEL_ENC_KEY);
  CALG_PCT1_MASTER      = (ALG_CLASS_MSG_ENCRYPT or ALG_TYPE_SECURECHANNEL or ALG_SID_PCT1_MASTER);
  CALG_SSL2_MASTER      = (ALG_CLASS_MSG_ENCRYPT or ALG_TYPE_SECURECHANNEL or ALG_SID_SSL2_MASTER);
  CALG_TLS1_MASTER      = (ALG_CLASS_MSG_ENCRYPT or ALG_TYPE_SECURECHANNEL or ALG_SID_TLS1_MASTER);
  CALG_RC5              = (ALG_CLASS_DATA_ENCRYPT or ALG_TYPE_BLOCK or ALG_SID_RC5);
  CALG_HMAC             = (ALG_CLASS_HASH  or  ALG_TYPE_ANY  or  ALG_SID_HMAC);

type
  PVTableProvStruc = ^VTableProvStruc;
  VTableProvStruc = record
    Version         :DWORD;
    FuncVerifyImage :TFarProc;
    FuncReturnhWnd  :TFarProc;
    dwProvType      :DWORD;
    pbContextInfo   :PBYTE;
    cbContextInfo   :DWORD;
end;

//type HCRYPTPROV = ULONG;
//type HCRYPTKEY  = ULONG;
//type HCRYPTHASH = ULONG;


const
  // dwFlags definitions for CryptAcquireContext
  CRYPT_VERIFYCONTEXT  = $F0000000;
  CRYPT_NEWKEYSET      = $00000008;
  CRYPT_DELETEKEYSET   = $00000010;
  CRYPT_MACHINE_KEYSET = $00000020;

  // dwFlag definitions for CryptGenKey
  CRYPT_EXPORTABLE     = $00000001;
  CRYPT_USER_PROTECTED = $00000002;
  CRYPT_CREATE_SALT    = $00000004;
  CRYPT_UPDATE_KEY     = $00000008;
  CRYPT_NO_SALT        = $00000010;
  CRYPT_PREGEN         = $00000040;
  CRYPT_RECIPIENT      = $00000010;
  CRYPT_INITIATOR      = $00000040;
  CRYPT_ONLINE         = $00000080;
  CRYPT_SF             = $00000100;
  CRYPT_CREATE_IV      = $00000200;
  CRYPT_KEK            = $00000400;
  CRYPT_DATA_KEY       = $00000800;

  // dwFlags definitions for CryptDeriveKey
  CRYPT_SERVER         = $00000400;

  KEY_LENGTH_MASK      = $FFFF0000;

  // dwFlag definitions for CryptExportKey
  CRYPT_Y_ONLY        = $00000001;
  CRYPT_SSL2_SLUMMING = $00000002;

  // dwFlags definitions for CryptHashSessionKey
  CRYPT_LITTLE_ENDIAN = $00000001;

  // dwFlag definitions for CryptSetProviderEx and CryptGetDefaultProvider
  CRYPT_MACHINE_DEFAULT = $00000001;
  CRYPT_USER_DEFAULT    = $00000002;
  CRYPT_DELETE_DEFAULT  = $00000004;

  // exported key blob definitions
  SIMPLEBLOB        = $1;
  PUBLICKEYBLOB     = $6;
  PRIVATEKEYBLOB    = $7;
  PLAINTEXTKEYBLOB  = $8;
  AT_KEYEXCHANGE    = 1;
  AT_SIGNATURE      = 2;
  CRYPT_USERDATA    = 1;

  // dwParam
  KP_IV                 = 1;  // Initialization vector
  KP_SALT               = 2;  // Salt value
  KP_PADDING            = 3;  // Padding values
  KP_MODE               = 4;  // Mode of the cipher
  KP_MODE_BITS          = 5;  // Number of bits to feedback
  KP_PERMISSIONS        = 6;  // Key permissions DWORD
  KP_ALGID              = 7;  // Key algorithm
  KP_BLOCKLEN           = 8;  // Block size of the cipher
  KP_KEYLEN             = 9;  // Length of key in bits
  KP_SALT_EX            = 10; // Length of salt in bytes
  KP_P                  = 11; // DSS/Diffie-Hellman P value
  KP_G                  = 12; // DSS/Diffie-Hellman G value
  KP_Q                  = 13; // DSS Q value
  KP_X                  = 14; // Diffie-Hellman X value
  KP_Y                  = 15; // Y value
  KP_RA                 = 16; // Fortezza RA value
  KP_RB                 = 17; // Fortezza RB value
  KP_INFO               = 18; // for putting information into an RSA envelope
  KP_EFFECTIVE_KEYLEN   = 19; // setting and getting RC2 effective key length
  KP_SCHANNEL_ALG	= 20; // for setting the Secure Channel algorithms
  KP_CLIENT_RANDOM      = 21; // for setting the Secure Channel client random data
  KP_SERVER_RANDOM      = 22; // for setting the Secure Channel server random data
  KP_RP                 = 23;
  KP_PRECOMP_MD5        = 24;
  KP_PRECOMP_SHA        = 25;
  KP_CERTIFICATE        = 26; // for setting Secure Channel certificate data (PCT1)
  KP_CLEAR_KEY          = 27; // for setting Secure Channel clear key data (PCT1)
  KP_PUB_EX_LEN         = 28;
  KP_PUB_EX_VAL         = 29;

  // KP_PADDING
  PKCS5_PADDING         = 1; {PKCS 5 (sec 6.2) padding method}
  RANDOM_PADDING        = 2;
  ZERO_PADDING          = 3;

  // KP_MODE
  CRYPT_MODE_CBC    = 1; // Cipher block chaining
  CRYPT_MODE_ECB    = 2; // Electronic code book
  CRYPT_MODE_OFB    = 3; // Output feedback mode
  CRYPT_MODE_CFB    = 4; // Cipher feedback mode
  CRYPT_MODE_CTS    = 5; // Ciphertext stealing mode

  // KP_PERMISSIONS
  CRYPT_ENCRYPT     = $0001; // Allow encryption
  CRYPT_DECRYPT     = $0002; // Allow decryption
  CRYPT_EXPORT      = $0004; // Allow key to be exported
  CRYPT_READ        = $0008; // Allow parameters to be read
  CRYPT_WRITE       = $0010; // Allow parameters to be set
  CRYPT_MAC         = $0020; // Allow MACs to be used with key
  CRYPT_EXPORT_KEY  = $0040; // Allow key to be used for exporting keys
  CRYPT_IMPORT_KEY  = $0080; // Allow key to be used for importing keys

  HP_ALGID          = $0001; // Hash algorithm
  HP_HASHVAL        = $0002; // Hash value
  HP_HASHSIZE       = $0004; // Hash value size

  HP_HMAC_INFO      = $0005; // information for creating an HMAC

  CRYPT_FAILED      = FALSE;
  CRYPT_SUCCEED     = TRUE;


const
  // CryptGetProvParam
  PP_ENUMALGS            = 1;
  PP_ENUMCONTAINERS      = 2;
  PP_IMPTYPE             = 3;
  PP_NAME                = 4;
  PP_VERSION             = 5;
  PP_CONTAINER           = 6;
  PP_CHANGE_PASSWORD     = 7;
  PP_KEYSET_SEC_DESCR    = 8;  // get/set security descriptor of keyset
  PP_CERTCHAIN           = 9;  // for retrieving certificates from tokens
  PP_KEY_TYPE_SUBTYPE    = 10;
  PP_PROVTYPE            = 16;
  PP_KEYSTORAGE          = 17;
  PP_APPLI_CERT          = 18;
  PP_SYM_KEYSIZE         = 19;
  PP_SESSION_KEYSIZE     = 20;
  PP_UI_PROMPT           = 21;
  PP_ENUMALGS_EX         = 22;
  CRYPT_FIRST            = 1;
  CRYPT_NEXT             = 2;
  CRYPT_IMPL_HARDWARE    = 1;
  CRYPT_IMPL_SOFTWARE    = 2;
  CRYPT_IMPL_MIXED       = 3;
  CRYPT_IMPL_UNKNOWN     = 4;

  // key storage flags
  CRYPT_SEC_DESCR        = $00000001;
  CRYPT_PSTORE           = $00000002;
  CRYPT_UI_PROMPT        = $00000004;

  // protocol flags
  CRYPT_FLAG_PCT1        = $0001;
  CRYPT_FLAG_SSL2        = $0002;
  CRYPT_FLAG_SSL3        = $0004;
  CRYPT_FLAG_TLS1        = $0008;

  // CryptSetProvParam
  PP_CLIENT_HWND         = 1;
  PP_CONTEXT_INFO        = 11;
  PP_KEYEXCHANGE_KEYSIZE = 12;
  PP_SIGNATURE_KEYSIZE   = 13;
  PP_KEYEXCHANGE_ALG     = 14;
  PP_SIGNATURE_ALG       = 15;
  PP_DELETEKEY           = 24;

  PROV_RSA_FULL          = 1;
  PROV_RSA_SIG           = 2;
  PROV_DSS               = 3;
  PROV_FORTEZZA          = 4;
  PROV_MS_EXCHANGE       = 5;
  PROV_SSL               = 6;

PROV_RSA_SCHANNEL        = 12;
PROV_DSS_DH              = 13;
PROV_EC_ECDSA_SIG        = 14;
PROV_EC_ECNRA_SIG        = 15;
PROV_EC_ECDSA_FULL       = 16;
PROV_EC_ECNRA_FULL       = 17;
PROV_SPYRUS_LYNKS        = 20;


  // STT defined Providers
  PROV_STT_MER           = 7;
  PROV_STT_ACQ           = 8;
  PROV_STT_BRND          = 9;
  PROV_STT_ROOT          = 10;
  PROV_STT_ISS           = 11;

  // Provider friendly names
  MS_DEF_PROV_A          = 'Microsoft Base Cryptographic Provider v1.0';
  {$IFNDEF VER90}
    MS_DEF_PROV_W        = WideString( 'Microsoft Base Cryptographic Provider v1.0');
  {$ELSE}
    MS_DEF_PROV_W        = ( 'Microsoft Base Cryptographic Provider v1.0');
  {$ENDIF}

{$IFDEF UNICODE}
  MS_DEF_PROV            = MS_DEF_PROV_W;
{$ELSE}
  MS_DEF_PROV            = MS_DEF_PROV_A;
{$ENDIF}

  MS_ENHANCED_PROV_A   = 'Microsoft Enhanced Cryptographic Provider v1.0';
  {$IFNDEF VER90}
    MS_ENHANCED_PROV_W = WideString('Microsoft Enhanced Cryptographic Provider v1.0');
  {$ELSE}
    MS_ENHANCED_PROV_W = ('Microsoft Enhanced Cryptographic Provider v1.0');
  {$ENDIF}

{$IFDEF UNICODE}
  MS_ENHANCED_PROV = MS_ENHANCED_PROV_W;
{$ELSE}
  MS_ENHANCED_PROV = MS_ENHANCED_PROV_A;
{$ENDIF}

  MS_DEF_RSA_SIG_PROV_A    = 'Microsoft RSA Signature Cryptographic Provider';
  {$IFNDEF VER90}
    MS_DEF_RSA_SIG_PROV_W  = WideString('Microsoft RSA Signature Cryptographic Provider');
  {$ELSE}
    MS_DEF_RSA_SIG_PROV_W  = ('Microsoft RSA Signature Cryptographic Provider');
  {$ENDIF}

{$IFDEF UNICODE}
  MS_DEF_RSA_SIG_PROV = MS_DEF_RSA_SIG_PROV_W;
{$ELSE}
  MS_DEF_RSA_SIG_PROV = MS_DEF_RSA_SIG_PROV_A;
{$ENDIF}

  MS_DEF_RSA_SCHANNEL_PROV_A    = 'Microsoft Base RSA SChannel Cryptographic Provider';
  {$IFNDEF VER90}
    MS_DEF_RSA_SCHANNEL_PROV_W  = WideString('Microsoft Base RSA SChannel Cryptographic Provider');
  {$ELSE}
    MS_DEF_RSA_SCHANNEL_PROV_W  = ('Microsoft Base RSA SChannel Cryptographic Provider');
  {$ENDIF}


{$IFDEF UNICODE}
  MS_DEF_RSA_SCHANNEL_PROV = MS_DEF_RSA_SCHANNEL_PROV_W;
{$ELSE}
  MS_DEF_RSA_SCHANNEL_PROV = MS_DEF_RSA_SCHANNEL_PROV_A;
{$ENDIF}

  MS_ENHANCED_RSA_SCHANNEL_PROV_A    = 'Microsoft Enhanced RSA SChannel Cryptographic Provider';
  {$IFNDEF VER90}
    MS_ENHANCED_RSA_SCHANNEL_PROV_W  = WideString('Microsoft Enhanced RSA SChannel Cryptographic Provider');
  {$ELSE}
    MS_ENHANCED_RSA_SCHANNEL_PROV_W  = ('Microsoft Enhanced RSA SChannel Cryptographic Provider');
  {$ENDIF}

{$IFDEF UNICODE}
  MS_ENHANCED_RSA_SCHANNEL_PROV = MS_ENHANCED_RSA_SCHANNEL_PROV_W;
{$ELSE}
  MS_ENHANCED_RSA_SCHANNEL_PROV = MS_ENHANCED_RSA_SCHANNEL_PROV_A;
{$ENDIF}

  MS_DEF_DSS_PROV_A    =  'Microsoft Base DSS Cryptographic Provider';
  {$IFNDEF VER90}
    MS_DEF_DSS_PROV_W  = WideString('Microsoft Base DSS Cryptographic Provider');
  {$ELSE}
    MS_DEF_DSS_PROV_W  = ('Microsoft Base DSS Cryptographic Provider');
  {$ENDIF}

{$IFDEF UNICODE}
  MS_DEF_DSS_PROV = MS_DEF_DSS_PROV_W;
{$ELSE}
  MS_DEF_DSS_PROV = MS_DEF_DSS_PROV_A;
{$ENDIF}

  MS_DEF_DSS_DH_PROV_A    = 'Microsoft Base DSS and Diffie-Hellman Cryptographic Provider';
  {$IFNDEF VER90}
    MS_DEF_DSS_DH_PROV_W  = WideString('Microsoft Base DSS and Diffie-Hellman Cryptographic Provider');
  {$ELSE}
    MS_DEF_DSS_DH_PROV_W  = ('Microsoft Base DSS and Diffie-Hellman Cryptographic Provider');
  {$ENDIF}

{$IFDEF UNICODE}
  MS_DEF_DSS_DH_PROV = MS_DEF_DSS_DH_PROV_W;
{$ELSE}
  MS_DEF_DSS_DH_PROV = MS_DEF_DSS_DH_PROV_A;
{$ENDIF}

  MAXUIDLEN              = 64;
  CUR_BLOB_VERSION       = 2;

{structure for use with CryptSetHashParam with CALG_HMAC}
type
  PHMAC_INFO = ^HMAC_INFO;
  HMAC_INFO = record
    HashAlgid     :ALG_ID;
    pbInnerString :PBYTE;
    cbInnerString :DWORD;
    pbOuterString :PBYTE;
    cbOuterString :DWORD;
  end;

// structure for use with CryptSetHashParam with CALG_HMAC
type
  PSCHANNEL_ALG = ^SCHANNEL_ALG;
  SCHANNEL_ALG  = record
    dwUse :DWORD;
    Algid :ALG_ID;
    cBits :DWORD;
  end;

// uses of algortihms for SCHANNEL_ALG structure
const
  SCHANNEL_MAC_KEY = $00000000;
  SCHANNEL_ENC_KEY = $00000001;

type
  PPROV_ENUMALGS = ^PROV_ENUMALGS;
  PROV_ENUMALGS = record
    aiAlgid   :ALG_ID;
    dwBitLen  :DWORD;
    dwNameLen :DWORD;
    szName    :array[0..20-1] of Char;
  end ;

type
  PPROV_ENUMALGS_EX = ^PROV_ENUMALGS_EX;
  PROV_ENUMALGS_EX = record
    aiAlgid       :ALG_ID;
    dwDefaultLen  :DWORD;
    dwMinLen      :DWORD;
    dwMaxLen      :DWORD;
    dwProtocols   :DWORD;
    dwNameLen     :DWORD;
    szName        :array[0..20-1] of Char;
    dwLongNameLen :DWORD;
    szLongName    :array[0..40-1] of Char;
    end;

type
  PPUBLICKEYSTRUC = ^PUBLICKEYSTRUC;
  PUBLICKEYSTRUC = record
    bType    :BYTE;
    bVersion :BYTE;
    reserved :Word;
    aiKeyAlg :ALG_ID;
  end;

type
  BLOBHEADER  = PUBLICKEYSTRUC;
  PBLOBHEADER = ^BLOBHEADER;

type
  PRSAPUBKEY = ^RSAPUBKEY;
  RSAPUBKEY = record
    magic  :DWORD;  // Has to be RSA1
    bitlen :DWORD;  // # of bits in modulus
    pubexp :DWORD;  // public exponent
                    // Modulus data follows
    end;

type
  PPUBKEY = ^PUBKEY;
  PUBKEY = record
    magic  :DWORD;
    bitlen :DWORD; // # of bits in modulus
  end;

type
  DHPUBKEY  = PUBKEY;
  DSSPUBKEY = PUBKEY;
  KEAPUBKEY = PUBKEY;
  TEKPUBKEY = PUBKEY;


type
  PDSSSEED = ^DSSSEED;
  DSSSEED = record
    counter :DWORD;
    seed    :array[0..20-1] of BYTE;
  end;

type
  PKEY_TYPE_SUBTYPE = ^KEY_TYPE_SUBTYPE;
  KEY_TYPE_SUBTYPE = record
    dwKeySpec :DWORD;
    Type_     :TGUID; {conflict with base Delphi type: original name 'Type'}
    Subtype   :TGUID;
  end;

function CryptAcquireContext(phProv        :PHCRYPTPROV;
                              pszContainer :LPAWSTR;
                              pszProvider  :LPAWSTR;
                              dwProvType   :DWORD;
                              dwFlags      :DWORD) :BOOL;stdcall;

function CryptCreateHash(hProv   :HCRYPTPROV;
                         Algid   :ALG_ID;
                         hKey    :HCRYPTKEY;
                         dwFlags :DWORD;
                         phHash  :PHCRYPTHASH) :BOOL;stdcall;

function CryptHashData(hHash       :HCRYPTHASH;
                 const pbData      :PBYTE;
                       dwDataLen   :DWORD;
                       dwFlags     :DWORD) :BOOL;stdcall;
function CryptGetHashParam(hHash      :HCRYPTHASH;
                           dwParam    :DWORD;
                           pbData     :PBYTE;
                           pdwDataLen :PDWORD;
                           dwFlags    :DWORD) :BOOL;stdcall;
function CryptDestroyHash(hHash :HCRYPTHASH) :BOOL;stdcall;
function CryptReleaseContext(hProv   :HCRYPTPROV;
                             dwFlags :DWORD) :BOOL;stdcall;


implementation
function CryptAcquireContext     ;external ADVAPI32 name 'CryptAcquireContextW';
function CryptCreateHash         ;external ADVAPI32 name 'CryptCreateHash';
function CryptHashData           ;external ADVAPI32 name 'CryptHashData';
function CryptGetHashParam       ;external ADVAPI32 name 'CryptGetHashParam';
function CryptDestroyHash        ;external ADVAPI32 name 'CryptDestroyHash';
function CryptReleaseContext     ;external ADVAPI32 name 'CryptReleaseContext';


end.