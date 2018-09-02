{******************************************************************************}
{                                                       	               }
{ Windows Cryptography API interface Unit for Object Pascal                    }
{                                                       	               }
{ Portions created by Microsoft are Copyright (C) 1995-2001 Microsoft          }
{ Corporation. All Rights Reserved.                                            }
{ 								               }
{ The original file is: wincrypt.h, released June 2000. The original Pascal    }
{ code is: WinCrypt.pas, released December 2000. The initial developer of the  }
{ Pascal code is Marcel van Brakel (brakelm@chello.nl).                        }
{                                                                              }
{ Portions created by Marcel van Brakel are Copyright (C) 1999-2001            }
{ Marcel van Brakel. All Rights Reserved.                                      }
{ 								               }
{ Obtained through: Joint Endeavour of Delphi Innovators (Project JEDI)        }
{								               }
{ You may retrieve the latest version of this file at the Project JEDI home    }
{ page, located at http://delphi-jedi.org or my personal homepage located at   }
{ http://members.chello.nl/m.vanbrakel2                                        }
{								               }
{ The contents of this file are used with permission, subject to the Mozilla   }
{ Public License Version 1.1 (the "License"); you may not use this file except }
{ in compliance with the License. You may obtain a copy of the License at      }
{ http://www.mozilla.org/MPL/MPL-1.1.html                                      }
{                                                                              }
{ Software distributed under the License is distributed on an "AS IS" basis,   }
{ WITHOUT WARRANTY OF ANY KIND, either express or implied. See the License for }
{ the specific language governing rights and limitations under the License.    }
{                                                                              }
{ Alternatively, the contents of this file may be used under the terms of the  }
{ GNU Lesser General Public License (the  "LGPL License"), in which case the   }
{ provisions of the LGPL License are applicable instead of those above.        }
{ If you wish to allow use of your version of this file only under the terms   }
{ of the LGPL License and not to allow others to use your version of this file }
{ under the MPL, indicate your decision by deleting  the provisions above and  }
{ replace  them with the notice and other provisions required by the LGPL      }
{ License.  If you do not delete the provisions above, a recipient may use     }
{ your version of this file under either the MPL or the LGPL License.          }
{ 								               }
{ For more information about the LGPL: http://www.gnu.org/copyleft/lesser.html }
{ 								               }
{******************************************************************************}

unit JwaWinCrypt;

{$WEAKPACKAGEUNIT}

{$HPPEMIT ''}
{$HPPEMIT '#include <WinCrypt.h>'}
{$HPPEMIT ''}
{$HPPEMIT 'typedef HCRYPTPROV *PHCRYPTPROV'}
{$HPPEMIT 'typedef HCRYPTKEY *PHCRYPTKEY'}
{$HPPEMIT 'typedef HCRYPTHASH *PHCRYPTHASH'}
{$HPPEMIT 'typedef PROV_ENUMALGS *PPROV_ENUMALGS'}
{$HPPEMIT 'typedef PROV_ENUMALGS_EX *PPROV_ENUMALGS_EX'}
{$HPPEMIT 'typedef PUBLICKEYSTRUC *PPUBLICKEYSTRUC'}
{$HPPEMIT 'typedef RSAPUBKEY *PRSAPUBKEY'}
{$HPPEMIT 'typedef DSSSEED *PDSSSEED'}
{$HPPEMIT 'typedef PUBKEYVER3 *PPUBKEYVER3'}
{$HPPEMIT 'typedef DHPRIVKEY_VER3 *PPRIVKEYVER3'}
{$HPPEMIT 'typedef CERT_FORTEZZA_DATA_PROP *PCERT_FORTEZZA_DATA_PROP'}
{$HPPEMIT 'typedef HCRYPTMSG *PHCRYPTMSG'}
{$HPPEMIT 'typedef CMSG_RECIPIENT_ENCODE_INFO *PCMSG_RECIPIENT_ENCODE_INFO'}
{$HPPEMIT 'typedef _CMSG_RECIPIENT_ENCODE_INFO CMSG_RECIPIENT_ENCODE_INFO'}
{$HPPEMIT 'typedef PCMSG_KEY_AGREE_KEY_ENCRYPT_INFO *PPCMSG_KEY_AGREE_KEY_ENCRYPT_INFO'}
{$HPPEMIT 'typedef HCERTSTORE *PHCERTSTORE'}
{$HPPEMIT 'typedef PCCERT_CONTEXT *PPCCERT_CONTEXT'}
{$HPPEMIT 'typedef PCCRL_CONTEXT *PPCCRL_CONTEXT'}
{$HPPEMIT 'typedef PCERT_CHAIN_CONTEXT *PPCCERT_CHAIN_CONTEXT'}
{$HPPEMIT ''}

{$I WINDEFINES.INC}

interface

uses
  JwaWinBase, JwaWinType;

//
// Algorithm IDs and Flags
//

// ALG_ID crackers

function GET_ALG_CLASS(x: DWORD): DWORD;
{$EXTERNALSYM GET_ALG_CLASS}

function GET_ALG_TYPE(x: DWORD): DWORD;
{$EXTERNALSYM GET_ALG_TYPE}

function GET_ALG_SID(x: DWORD): DWORD;
{$EXTERNALSYM GET_ALG_SID}

// Algorithm classes

const
  ALG_CLASS_ANY          = (0);
  {$EXTERNALSYM ALG_CLASS_ANY}
  ALG_CLASS_SIGNATURE    = (1 shl 13);
  {$EXTERNALSYM ALG_CLASS_SIGNATURE}
  ALG_CLASS_MSG_ENCRYPT  = (2 shl 13);
  {$EXTERNALSYM ALG_CLASS_MSG_ENCRYPT}
  ALG_CLASS_DATA_ENCRYPT = (3 shl 13);
  {$EXTERNALSYM ALG_CLASS_DATA_ENCRYPT}
  ALG_CLASS_HASH         = (4 shl 13);
  {$EXTERNALSYM ALG_CLASS_HASH}
  ALG_CLASS_KEY_EXCHANGE = (5 shl 13);
  {$EXTERNALSYM ALG_CLASS_KEY_EXCHANGE}
  ALG_CLASS_ALL          = (7 shl 13);
  {$EXTERNALSYM ALG_CLASS_ALL}

// Algorithm types

  ALG_TYPE_ANY           = (0);
  {$EXTERNALSYM ALG_TYPE_ANY}
  ALG_TYPE_DSS           = (1 shl 9);
  {$EXTERNALSYM ALG_TYPE_DSS}
  ALG_TYPE_RSA           = (2 shl 9);
  {$EXTERNALSYM ALG_TYPE_RSA}
  ALG_TYPE_BLOCK         = (3 shl 9);
  {$EXTERNALSYM ALG_TYPE_BLOCK}
  ALG_TYPE_STREAM        = (4 shl 9);
  {$EXTERNALSYM ALG_TYPE_STREAM}
  ALG_TYPE_DH            = (5 shl 9);
  {$EXTERNALSYM ALG_TYPE_DH}
  ALG_TYPE_SECURECHANNEL = (6 shl 9);
  {$EXTERNALSYM ALG_TYPE_SECURECHANNEL}

// Generic sub-ids

  ALG_SID_ANY = (0);
  {$EXTERNALSYM ALG_SID_ANY}

// Some RSA sub-ids

  ALG_SID_RSA_ANY      = 0;
  {$EXTERNALSYM ALG_SID_RSA_ANY}
  ALG_SID_RSA_PKCS     = 1;
  {$EXTERNALSYM ALG_SID_RSA_PKCS}
  ALG_SID_RSA_MSATWORK = 2;
  {$EXTERNALSYM ALG_SID_RSA_MSATWORK}
  ALG_SID_RSA_ENTRUST  = 3;
  {$EXTERNALSYM ALG_SID_RSA_ENTRUST}
  ALG_SID_RSA_PGP      = 4;
  {$EXTERNALSYM ALG_SID_RSA_PGP}

// Some DSS sub-ids
//

  ALG_SID_DSS_ANY  = 0;
  {$EXTERNALSYM ALG_SID_DSS_ANY}
  ALG_SID_DSS_PKCS = 1;
  {$EXTERNALSYM ALG_SID_DSS_PKCS}
  ALG_SID_DSS_DMS  = 2;
  {$EXTERNALSYM ALG_SID_DSS_DMS}

// Block cipher sub ids
// DES sub_ids

  ALG_SID_DES        = 1;
  {$EXTERNALSYM ALG_SID_DES}
  ALG_SID_3DES       = 3;
  {$EXTERNALSYM ALG_SID_3DES}
  ALG_SID_DESX       = 4;
  {$EXTERNALSYM ALG_SID_DESX}
  ALG_SID_IDEA       = 5;
  {$EXTERNALSYM ALG_SID_IDEA}
  ALG_SID_CAST       = 6;
  {$EXTERNALSYM ALG_SID_CAST}
  ALG_SID_SAFERSK64  = 7;
  {$EXTERNALSYM ALG_SID_SAFERSK64}
  ALG_SID_SAFERSK128 = 8;
  {$EXTERNALSYM ALG_SID_SAFERSK128}
  ALG_SID_3DES_112   = 9;
  {$EXTERNALSYM ALG_SID_3DES_112}
  ALG_SID_CYLINK_MEK = 12;
  {$EXTERNALSYM ALG_SID_CYLINK_MEK}
  ALG_SID_RC5        = 13;
  {$EXTERNALSYM ALG_SID_RC5}

// Fortezza sub-ids

  ALG_SID_SKIPJACK = 10;
  {$EXTERNALSYM ALG_SID_SKIPJACK}
  ALG_SID_TEK      = 11;
  {$EXTERNALSYM ALG_SID_TEK}

// KP_MODE

  CRYPT_MODE_CBCI    = 6; // ANSI CBC Interleaved
  {$EXTERNALSYM CRYPT_MODE_CBCI}
  CRYPT_MODE_CFBP    = 7; // ANSI CFB Pipelined
  {$EXTERNALSYM CRYPT_MODE_CFBP}
  CRYPT_MODE_OFBP    = 8; // ANSI OFB Pipelined
  {$EXTERNALSYM CRYPT_MODE_OFBP}
  CRYPT_MODE_CBCOFM  = 9; // ANSI CBC + OF Masking
  {$EXTERNALSYM CRYPT_MODE_CBCOFM}
  CRYPT_MODE_CBCOFMI = 10; // ANSI CBC + OFM Interleaved
  {$EXTERNALSYM CRYPT_MODE_CBCOFMI}

// RC2 sub-ids

  ALG_SID_RC2 = 2;
  {$EXTERNALSYM ALG_SID_RC2}

// Stream cipher sub-ids

  ALG_SID_RC4  = 1;
  {$EXTERNALSYM ALG_SID_RC4}
  ALG_SID_SEAL = 2;
  {$EXTERNALSYM ALG_SID_SEAL}

// Diffie-Hellman sub-ids

  ALG_SID_DH_SANDF       = 1;
  {$EXTERNALSYM ALG_SID_DH_SANDF}
  ALG_SID_DH_EPHEM       = 2;
  {$EXTERNALSYM ALG_SID_DH_EPHEM}
  ALG_SID_AGREED_KEY_ANY = 3;
  {$EXTERNALSYM ALG_SID_AGREED_KEY_ANY}
  ALG_SID_KEA            = 4;
  {$EXTERNALSYM ALG_SID_KEA}

// Hash sub ids

  ALG_SID_MD2        = 1;
  {$EXTERNALSYM ALG_SID_MD2}
  ALG_SID_MD4        = 2;
  {$EXTERNALSYM ALG_SID_MD4}
  ALG_SID_MD5        = 3;
  {$EXTERNALSYM ALG_SID_MD5}
  ALG_SID_SHA        = 4;
  {$EXTERNALSYM ALG_SID_SHA}
  ALG_SID_SHA1       = 4;
  {$EXTERNALSYM ALG_SID_SHA1}
  ALG_SID_MAC        = 5;
  {$EXTERNALSYM ALG_SID_MAC}
  ALG_SID_RIPEMD     = 6;
  {$EXTERNALSYM ALG_SID_RIPEMD}
  ALG_SID_RIPEMD160  = 7;
  {$EXTERNALSYM ALG_SID_RIPEMD160}
  ALG_SID_SSL3SHAMD5 = 8;
  {$EXTERNALSYM ALG_SID_SSL3SHAMD5}
  ALG_SID_HMAC       = 9;
  {$EXTERNALSYM ALG_SID_HMAC}
  ALG_SID_TLS1PRF    = 10;
  {$EXTERNALSYM ALG_SID_TLS1PRF}

// secure channel sub ids

  ALG_SID_SSL3_MASTER          = 1;
  {$EXTERNALSYM ALG_SID_SSL3_MASTER}
  ALG_SID_SCHANNEL_MASTER_HASH = 2;
  {$EXTERNALSYM ALG_SID_SCHANNEL_MASTER_HASH}
  ALG_SID_SCHANNEL_MAC_KEY     = 3;
  {$EXTERNALSYM ALG_SID_SCHANNEL_MAC_KEY}
  ALG_SID_PCT1_MASTER          = 4;
  {$EXTERNALSYM ALG_SID_PCT1_MASTER}
  ALG_SID_SSL2_MASTER          = 5;
  {$EXTERNALSYM ALG_SID_SSL2_MASTER}
  ALG_SID_TLS1_MASTER          = 6;
  {$EXTERNALSYM ALG_SID_TLS1_MASTER}
  ALG_SID_SCHANNEL_ENC_KEY     = 7;
  {$EXTERNALSYM ALG_SID_SCHANNEL_ENC_KEY}

// Our silly example sub-id

  ALG_SID_EXAMPLE = 80;
  {$EXTERNALSYM ALG_SID_EXAMPLE}

type
  ALG_ID = Cardinal;
  {$EXTERNALSYM ALG_ID}

// algorithm identifier definitions

const
  CALG_MD2                  = (ALG_CLASS_HASH or ALG_TYPE_ANY or ALG_SID_MD2);
  {$EXTERNALSYM CALG_MD2}
  CALG_MD4                  = (ALG_CLASS_HASH or ALG_TYPE_ANY or ALG_SID_MD4);
  {$EXTERNALSYM CALG_MD4}
  CALG_MD5                  = (ALG_CLASS_HASH or ALG_TYPE_ANY or ALG_SID_MD5);
  {$EXTERNALSYM CALG_MD5}
  CALG_SHA                  = (ALG_CLASS_HASH or ALG_TYPE_ANY or ALG_SID_SHA);
  {$EXTERNALSYM CALG_SHA}
  CALG_SHA1                 = (ALG_CLASS_HASH or ALG_TYPE_ANY or ALG_SID_SHA1);
  {$EXTERNALSYM CALG_SHA1}
  CALG_MAC                  = (ALG_CLASS_HASH or ALG_TYPE_ANY or ALG_SID_MAC);
  {$EXTERNALSYM CALG_MAC}
  CALG_RSA_SIGN             = (ALG_CLASS_SIGNATURE or ALG_TYPE_RSA or ALG_SID_RSA_ANY);
  {$EXTERNALSYM CALG_RSA_SIGN}
  CALG_DSS_SIGN             = (ALG_CLASS_SIGNATURE or ALG_TYPE_DSS or ALG_SID_DSS_ANY);
  {$EXTERNALSYM CALG_DSS_SIGN}
  CALG_RSA_KEYX             = (ALG_CLASS_KEY_EXCHANGE or ALG_TYPE_RSA or ALG_SID_RSA_ANY);
  {$EXTERNALSYM CALG_RSA_KEYX}
  CALG_DES                  = (ALG_CLASS_DATA_ENCRYPT or ALG_TYPE_BLOCK or ALG_SID_DES);
  {$EXTERNALSYM CALG_DES}
  CALG_3DES_112             = (ALG_CLASS_DATA_ENCRYPT or ALG_TYPE_BLOCK or ALG_SID_3DES_112);
  {$EXTERNALSYM CALG_3DES_112}
  CALG_3DES                 = (ALG_CLASS_DATA_ENCRYPT or ALG_TYPE_BLOCK or ALG_SID_3DES);
  {$EXTERNALSYM CALG_3DES}
  CALG_DESX                 = (ALG_CLASS_DATA_ENCRYPT or ALG_TYPE_BLOCK or ALG_SID_DESX);
  {$EXTERNALSYM CALG_DESX}
  CALG_RC2                  = (ALG_CLASS_DATA_ENCRYPT or ALG_TYPE_BLOCK or ALG_SID_RC2);
  {$EXTERNALSYM CALG_RC2}
  CALG_RC4                  = (ALG_CLASS_DATA_ENCRYPT or ALG_TYPE_STREAM or ALG_SID_RC4);
  {$EXTERNALSYM CALG_RC4}
  CALG_SEAL                 = (ALG_CLASS_DATA_ENCRYPT or ALG_TYPE_STREAM or ALG_SID_SEAL);
  {$EXTERNALSYM CALG_SEAL}
  CALG_DH_SF                = (ALG_CLASS_KEY_EXCHANGE or ALG_TYPE_DH or ALG_SID_DH_SANDF);
  {$EXTERNALSYM CALG_DH_SF}
  CALG_DH_EPHEM             = (ALG_CLASS_KEY_EXCHANGE or ALG_TYPE_DH or ALG_SID_DH_EPHEM);
  {$EXTERNALSYM CALG_DH_EPHEM}
  CALG_AGREEDKEY_ANY        = (ALG_CLASS_KEY_EXCHANGE or ALG_TYPE_DH or ALG_SID_AGREED_KEY_ANY);
  {$EXTERNALSYM CALG_AGREEDKEY_ANY}
  CALG_KEA_KEYX             = (ALG_CLASS_KEY_EXCHANGE or ALG_TYPE_DH or ALG_SID_KEA);
  {$EXTERNALSYM CALG_KEA_KEYX}
  CALG_HUGHES_MD5           = (ALG_CLASS_KEY_EXCHANGE or ALG_TYPE_ANY or ALG_SID_MD5);
  {$EXTERNALSYM CALG_HUGHES_MD5}
  CALG_SKIPJACK             = (ALG_CLASS_DATA_ENCRYPT or ALG_TYPE_BLOCK or ALG_SID_SKIPJACK);
  {$EXTERNALSYM CALG_SKIPJACK}
  CALG_TEK                  = (ALG_CLASS_DATA_ENCRYPT or ALG_TYPE_BLOCK or ALG_SID_TEK);
  {$EXTERNALSYM CALG_TEK}
  CALG_CYLINK_MEK           = (ALG_CLASS_DATA_ENCRYPT or ALG_TYPE_BLOCK or ALG_SID_CYLINK_MEK);
  {$EXTERNALSYM CALG_CYLINK_MEK}
  CALG_SSL3_SHAMD5          = (ALG_CLASS_HASH or ALG_TYPE_ANY or ALG_SID_SSL3SHAMD5);
  {$EXTERNALSYM CALG_SSL3_SHAMD5}
  CALG_SSL3_MASTER          = (ALG_CLASS_MSG_ENCRYPT or ALG_TYPE_SECURECHANNEL or ALG_SID_SSL3_MASTER);
  {$EXTERNALSYM CALG_SSL3_MASTER}
  CALG_SCHANNEL_MASTER_HASH = (ALG_CLASS_MSG_ENCRYPT or ALG_TYPE_SECURECHANNEL or ALG_SID_SCHANNEL_MASTER_HASH);
  {$EXTERNALSYM CALG_SCHANNEL_MASTER_HASH}
  CALG_SCHANNEL_MAC_KEY     = (ALG_CLASS_MSG_ENCRYPT or ALG_TYPE_SECURECHANNEL or ALG_SID_SCHANNEL_MAC_KEY);
  {$EXTERNALSYM CALG_SCHANNEL_MAC_KEY}
  CALG_SCHANNEL_ENC_KEY     = (ALG_CLASS_MSG_ENCRYPT or ALG_TYPE_SECURECHANNEL or ALG_SID_SCHANNEL_ENC_KEY);
  {$EXTERNALSYM CALG_SCHANNEL_ENC_KEY}
  CALG_PCT1_MASTER          = (ALG_CLASS_MSG_ENCRYPT or ALG_TYPE_SECURECHANNEL or ALG_SID_PCT1_MASTER);
  {$EXTERNALSYM CALG_PCT1_MASTER}
  CALG_SSL2_MASTER          = (ALG_CLASS_MSG_ENCRYPT or ALG_TYPE_SECURECHANNEL or ALG_SID_SSL2_MASTER);
  {$EXTERNALSYM CALG_SSL2_MASTER}
  CALG_TLS1_MASTER          = (ALG_CLASS_MSG_ENCRYPT or ALG_TYPE_SECURECHANNEL or ALG_SID_TLS1_MASTER);
  {$EXTERNALSYM CALG_TLS1_MASTER}
  CALG_RC5                  = (ALG_CLASS_DATA_ENCRYPT or ALG_TYPE_BLOCK or ALG_SID_RC5);
  {$EXTERNALSYM CALG_RC5}
  CALG_HMAC                 = (ALG_CLASS_HASH or ALG_TYPE_ANY or ALG_SID_HMAC);
  {$EXTERNALSYM CALG_HMAC}
  CALG_TLS1PRF              = (ALG_CLASS_HASH or ALG_TYPE_ANY or ALG_SID_TLS1PRF);
  {$EXTERNALSYM CALG_TLS1PRF}

// resource number for signatures in the CSP

  SIGNATURE_RESOURCE_NUMBER = $29A;
  {$EXTERNALSYM SIGNATURE_RESOURCE_NUMBER}

type
  PVTableProvStruc = ^VTableProvStruc;
  _VTableProvStruc = record
    Version: DWORD;
    FuncVerifyImage: FARPROC;
    FuncReturnhWnd: FARPROC;
    dwProvType: DWORD;
    pbContextInfo: LPBYTE;
    cbContextInfo: DWORD;
    pszProvName: LPSTR;
  end;
  {$EXTERNALSYM _VTableProvStruc}
  VTableProvStruc = _VTableProvStruc;
  {$EXTERNALSYM VTableProvStruc}
  TVTableProvStruc = VTableProvStruc;

  HCRYPTPROV = ULONG_PTR;
  {$EXTERNALSYM HCRYPTPROV}
  HCRYPTKEY = ULONG_PTR;
  {$EXTERNALSYM HCRYPTKEY}
  HCRYPTHASH = ULONG_PTR;
  {$EXTERNALSYM HCRYPTHASH}

  PHCRYPTPROV = ^HCRYPTPROV;
  {$NODEFINE PHCRYPTPROV}
  PHCRYPTKEY = ^HCRYPTKEY;
  {$NODEFINE PHCRYPTKEY}
  PHCRYPTHASH = ^HCRYPTHASH;
  {$NODEFINE PHCRYPTHASH}

// dwFlags definitions for CryptAcquireContext

const
  CRYPT_VERIFYCONTEXT  = DWORD($F0000000);
  {$EXTERNALSYM CRYPT_VERIFYCONTEXT}
  CRYPT_NEWKEYSET      = $00000008;
  {$EXTERNALSYM CRYPT_NEWKEYSET}
  CRYPT_DELETEKEYSET   = $00000010;
  {$EXTERNALSYM CRYPT_DELETEKEYSET}
  CRYPT_MACHINE_KEYSET = $00000020;
  {$EXTERNALSYM CRYPT_MACHINE_KEYSET}
  CRYPT_SILENT         = $00000040;
  {$EXTERNALSYM CRYPT_SILENT}

// dwFlag definitions for CryptGenKey

  CRYPT_EXPORTABLE     = $00000001;
  {$EXTERNALSYM CRYPT_EXPORTABLE}
  CRYPT_USER_PROTECTED = $00000002;
  {$EXTERNALSYM CRYPT_USER_PROTECTED}
  CRYPT_CREATE_SALT    = $00000004;
  {$EXTERNALSYM CRYPT_CREATE_SALT}
  CRYPT_UPDATE_KEY     = $00000008;
  {$EXTERNALSYM CRYPT_UPDATE_KEY}
  CRYPT_NO_SALT        = $00000010;
  {$EXTERNALSYM CRYPT_NO_SALT}
  CRYPT_PREGEN         = $00000040;
  {$EXTERNALSYM CRYPT_PREGEN}
  CRYPT_RECIPIENT      = $00000010;
  {$EXTERNALSYM CRYPT_RECIPIENT}
  CRYPT_INITIATOR      = $00000040;
  {$EXTERNALSYM CRYPT_INITIATOR}
  CRYPT_ONLINE         = $00000080;
  {$EXTERNALSYM CRYPT_ONLINE}
  CRYPT_SF             = $00000100;
  {$EXTERNALSYM CRYPT_SF}
  CRYPT_CREATE_IV      = $00000200;
  {$EXTERNALSYM CRYPT_CREATE_IV}
  CRYPT_KEK            = $00000400;
  {$EXTERNALSYM CRYPT_KEK}
  CRYPT_DATA_KEY       = $00000800;
  {$EXTERNALSYM CRYPT_DATA_KEY}
  CRYPT_VOLATILE       = $00001000;
  {$EXTERNALSYM CRYPT_VOLATILE}
  CRYPT_SGCKEY         = $00002000;
  {$EXTERNALSYM CRYPT_SGCKEY}

  RSA1024BIT_KEY       = $04000000;
  {$EXTERNALSYM RSA1024BIT_KEY}

// dwFlags definitions for CryptDeriveKey

  CRYPT_SERVER = $00000400;
  {$EXTERNALSYM CRYPT_SERVER}

  KEY_LENGTH_MASK = DWORD($FFFF0000);
  {$EXTERNALSYM KEY_LENGTH_MASK}

// dwFlag definitions for CryptExportKey

  CRYPT_Y_ONLY        = $00000001;
  {$EXTERNALSYM CRYPT_Y_ONLY}
  CRYPT_SSL2_FALLBACK = $00000002;
  {$EXTERNALSYM CRYPT_SSL2_FALLBACK}
  CRYPT_DESTROYKEY    = $00000004;
  {$EXTERNALSYM CRYPT_DESTROYKEY}
  CRYPT_OAEP          = $00000040; // used with RSA encryptions/decryptions
                                   // CryptExportKey, CryptImportKey,
                                   // CryptEncrypt and CryptDecrypt
  {$EXTERNALSYM CRYPT_OAEP}

  CRYPT_BLOB_VER3 = $00000080; // export version 3 of a blob type
  {$EXTERNALSYM CRYPT_BLOB_VER3}

// dwFlags definitions for CryptCreateHash

  CRYPT_SECRETDIGEST = $00000001;
  {$EXTERNALSYM CRYPT_SECRETDIGEST}

// dwFlags definitions for CryptHashSessionKey

  CRYPT_LITTLE_ENDIAN = $00000001;
  {$EXTERNALSYM CRYPT_LITTLE_ENDIAN}

// dwFlags definitions for CryptSignHash and CryptVerifySignature

  CRYPT_NOHASHOID    = $00000001;
  {$EXTERNALSYM CRYPT_NOHASHOID}
  CRYPT_TYPE2_FORMAT = $00000002;
  {$EXTERNALSYM CRYPT_TYPE2_FORMAT}
  CRYPT_X931_FORMAT  = $00000004;
  {$EXTERNALSYM CRYPT_X931_FORMAT}

// dwFlag definitions for CryptSetProviderEx and CryptGetDefaultProvider

  CRYPT_MACHINE_DEFAULT = $00000001;
  {$EXTERNALSYM CRYPT_MACHINE_DEFAULT}
  CRYPT_USER_DEFAULT    = $00000002;
  {$EXTERNALSYM CRYPT_USER_DEFAULT}
  CRYPT_DELETE_DEFAULT  = $00000004;
  {$EXTERNALSYM CRYPT_DELETE_DEFAULT}

// exported key blob definitions

  SIMPLEBLOB           = $1;
  {$EXTERNALSYM SIMPLEBLOB}
  PUBLICKEYBLOB        = $6;
  {$EXTERNALSYM PUBLICKEYBLOB}
  PRIVATEKEYBLOB       = $7;
  {$EXTERNALSYM PRIVATEKEYBLOB}
  PLAINTEXTKEYBLOB     = $8;
  {$EXTERNALSYM PLAINTEXTKEYBLOB}
  OPAQUEKEYBLOB        = $9;
  {$EXTERNALSYM OPAQUEKEYBLOB}
  PUBLICKEYBLOBEX      = $A;
  {$EXTERNALSYM PUBLICKEYBLOBEX}
  SYMMETRICWRAPKEYBLOB = $B;
  {$EXTERNALSYM SYMMETRICWRAPKEYBLOB}

  AT_KEYEXCHANGE = 1;
  {$EXTERNALSYM AT_KEYEXCHANGE}
  AT_SIGNATURE   = 2;
  {$EXTERNALSYM AT_SIGNATURE}

  CRYPT_USERDATA = 1;
  {$EXTERNALSYM CRYPT_USERDATA}

// dwParam

  KP_IV               = 1; // Initialization vector
  {$EXTERNALSYM KP_IV}
  KP_SALT             = 2; // Salt value
  {$EXTERNALSYM KP_SALT}
  KP_PADDING          = 3; // Padding values
  {$EXTERNALSYM KP_PADDING}
  KP_MODE             = 4; // Mode of the cipher
  {$EXTERNALSYM KP_MODE}
  KP_MODE_BITS        = 5; // Number of bits to feedback
  {$EXTERNALSYM KP_MODE_BITS}
  KP_PERMISSIONS      = 6; // Key permissions DWORD
  {$EXTERNALSYM KP_PERMISSIONS}
  KP_ALGID            = 7; // Key algorithm
  {$EXTERNALSYM KP_ALGID}
  KP_BLOCKLEN         = 8; // Block size of the cipher
  {$EXTERNALSYM KP_BLOCKLEN}
  KP_KEYLEN           = 9; // Length of key in bits
  {$EXTERNALSYM KP_KEYLEN}
  KP_SALT_EX          = 10; // Length of salt in bytes
  {$EXTERNALSYM KP_SALT_EX}
  KP_P                = 11; // DSS/Diffie-Hellman P value
  {$EXTERNALSYM KP_P}
  KP_G                = 12; // DSS/Diffie-Hellman G value
  {$EXTERNALSYM KP_G}
  KP_Q                = 13; // DSS Q value
  {$EXTERNALSYM KP_Q}
  KP_X                = 14; // Diffie-Hellman X value
  {$EXTERNALSYM KP_X}
  KP_Y                = 15; // Y value
  {$EXTERNALSYM KP_Y}
  KP_RA               = 16; // Fortezza RA value
  {$EXTERNALSYM KP_RA}
  KP_RB               = 17; // Fortezza RB value
  {$EXTERNALSYM KP_RB}
  KP_INFO             = 18; // for putting information into an RSA envelope
  {$EXTERNALSYM KP_INFO}
  KP_EFFECTIVE_KEYLEN = 19; // setting and getting RC2 effective key length
  {$EXTERNALSYM KP_EFFECTIVE_KEYLEN}
  KP_SCHANNEL_ALG     = 20; // for setting the Secure Channel algorithms
  {$EXTERNALSYM KP_SCHANNEL_ALG}
  KP_CLIENT_RANDOM    = 21; // for setting the Secure Channel client random data
  {$EXTERNALSYM KP_CLIENT_RANDOM}
  KP_SERVER_RANDOM    = 22; // for setting the Secure Channel server random data
  {$EXTERNALSYM KP_SERVER_RANDOM}
  KP_RP               = 23;
  {$EXTERNALSYM KP_RP}
  KP_PRECOMP_MD5      = 24;
  {$EXTERNALSYM KP_PRECOMP_MD5}
  KP_PRECOMP_SHA      = 25;
  {$EXTERNALSYM KP_PRECOMP_SHA}
  KP_CERTIFICATE      = 26; // for setting Secure Channel certificate data (PCT1)
  {$EXTERNALSYM KP_CERTIFICATE}
  KP_CLEAR_KEY        = 27; // for setting Secure Channel clear key data (PCT1)
  {$EXTERNALSYM KP_CLEAR_KEY}
  KP_PUB_EX_LEN       = 28;
  {$EXTERNALSYM KP_PUB_EX_LEN}
  KP_PUB_EX_VAL       = 29;
  {$EXTERNALSYM KP_PUB_EX_VAL}
  KP_KEYVAL           = 30;
  {$EXTERNALSYM KP_KEYVAL}
  KP_ADMIN_PIN        = 31;
  {$EXTERNALSYM KP_ADMIN_PIN}
  KP_KEYEXCHANGE_PIN  = 32;
  {$EXTERNALSYM KP_KEYEXCHANGE_PIN}
  KP_SIGNATURE_PIN    = 33;
  {$EXTERNALSYM KP_SIGNATURE_PIN}
  KP_PREHASH          = 34;
  {$EXTERNALSYM KP_PREHASH}

  KP_OAEP_PARAMS     = 36; // for setting OAEP params on RSA keys
  {$EXTERNALSYM KP_OAEP_PARAMS}
  KP_CMS_KEY_INFO    = 37;
  {$EXTERNALSYM KP_CMS_KEY_INFO}
  KP_CMS_DH_KEY_INFO = 38;
  {$EXTERNALSYM KP_CMS_DH_KEY_INFO}
  KP_PUB_PARAMS      = 39; // for setting public parameters
  {$EXTERNALSYM KP_PUB_PARAMS}
  KP_VERIFY_PARAMS   = 40; // for verifying DSA and DH parameters
  {$EXTERNALSYM KP_VERIFY_PARAMS}
  KP_HIGHEST_VERSION = 41; // for TLS protocol version setting
  {$EXTERNALSYM KP_HIGHEST_VERSION}

// KP_PADDING

  PKCS5_PADDING  = 1; // PKCS 5 (sec 6.2) padding method
  {$EXTERNALSYM PKCS5_PADDING}
  RANDOM_PADDING = 2;
  {$EXTERNALSYM RANDOM_PADDING}
  ZERO_PADDING   = 3;
  {$EXTERNALSYM ZERO_PADDING}

// KP_MODE

  CRYPT_MODE_CBC = 1; // Cipher block chaining
  {$EXTERNALSYM CRYPT_MODE_CBC}
  CRYPT_MODE_ECB = 2; // Electronic code book
  {$EXTERNALSYM CRYPT_MODE_ECB}
  CRYPT_MODE_OFB = 3; // Output feedback mode
  {$EXTERNALSYM CRYPT_MODE_OFB}
  CRYPT_MODE_CFB = 4; // Cipher feedback mode
  {$EXTERNALSYM CRYPT_MODE_CFB}
  CRYPT_MODE_CTS = 5; // Ciphertext stealing mode
  {$EXTERNALSYM CRYPT_MODE_CTS}

// KP_PERMISSIONS

  CRYPT_ENCRYPT    = $0001; // Allow encryption
  {$EXTERNALSYM CRYPT_ENCRYPT}
  CRYPT_DECRYPT    = $0002; // Allow decryption
  {$EXTERNALSYM CRYPT_DECRYPT}
  CRYPT_EXPORT     = $0004; // Allow key to be exported
  {$EXTERNALSYM CRYPT_EXPORT}
  CRYPT_READ       = $0008; // Allow parameters to be read
  {$EXTERNALSYM CRYPT_READ}
  CRYPT_WRITE      = $0010; // Allow parameters to be set
  {$EXTERNALSYM CRYPT_WRITE}
  CRYPT_MAC        = $0020; // Allow MACs to be used with key
  {$EXTERNALSYM CRYPT_MAC}
  CRYPT_EXPORT_KEY = $0040; // Allow key to be used for exporting keys
  {$EXTERNALSYM CRYPT_EXPORT_KEY}
  CRYPT_IMPORT_KEY = $0080; // Allow key to be used for importing keys
  {$EXTERNALSYM CRYPT_IMPORT_KEY}

  HP_ALGID         = $0001; // Hash algorithm
  {$EXTERNALSYM HP_ALGID}
  HP_HASHVAL       = $0002; // Hash value
  {$EXTERNALSYM HP_HASHVAL}
  HP_HASHSIZE      = $0004; // Hash value size
  {$EXTERNALSYM HP_HASHSIZE}
  HP_HMAC_INFO     = $0005; // information for creating an HMAC
  {$EXTERNALSYM HP_HMAC_INFO}
  HP_TLS1PRF_LABEL = $0006; // label for TLS1 PRF
  {$EXTERNALSYM HP_TLS1PRF_LABEL}
  HP_TLS1PRF_SEED  = $0007; // seed for TLS1 PRF
  {$EXTERNALSYM HP_TLS1PRF_SEED}

  CRYPT_FAILED  = FALSE;
  {$EXTERNALSYM CRYPT_FAILED}
  CRYPT_SUCCEED = TRUE;
  {$EXTERNALSYM CRYPT_SUCCEED}

function RCRYPT_SUCCEEDED(rt: BOOL): BOOL;
{$EXTERNALSYM RCRYPT_SUCCEEDED}

function RCRYPT_FAILED(rt: BOOL): BOOL;
{$EXTERNALSYM RCRYPT_FAILED}

//
// CryptGetProvParam
//

const
  PP_ENUMALGS            = 1;
  {$EXTERNALSYM PP_ENUMALGS}
  PP_ENUMCONTAINERS      = 2;
  {$EXTERNALSYM PP_ENUMCONTAINERS}
  PP_IMPTYPE             = 3;
  {$EXTERNALSYM PP_IMPTYPE}
  PP_NAME                = 4;
  {$EXTERNALSYM PP_NAME}
  PP_VERSION             = 5;
  {$EXTERNALSYM PP_VERSION}
  PP_CONTAINER           = 6;
  {$EXTERNALSYM PP_CONTAINER}
  PP_CHANGE_PASSWORD     = 7;
  {$EXTERNALSYM PP_CHANGE_PASSWORD}
  PP_KEYSET_SEC_DESCR    = 8; // get/set security descriptor of keyset
  {$EXTERNALSYM PP_KEYSET_SEC_DESCR}
  PP_CERTCHAIN           = 9; // for retrieving certificates from tokens
  {$EXTERNALSYM PP_CERTCHAIN}
  PP_KEY_TYPE_SUBTYPE    = 10;
  {$EXTERNALSYM PP_KEY_TYPE_SUBTYPE}
  PP_PROVTYPE            = 16;
  {$EXTERNALSYM PP_PROVTYPE}
  PP_KEYSTORAGE          = 17;
  {$EXTERNALSYM PP_KEYSTORAGE}
  PP_APPLI_CERT          = 18;
  {$EXTERNALSYM PP_APPLI_CERT}
  PP_SYM_KEYSIZE         = 19;
  {$EXTERNALSYM PP_SYM_KEYSIZE}
  PP_SESSION_KEYSIZE     = 20;
  {$EXTERNALSYM PP_SESSION_KEYSIZE}
  PP_UI_PROMPT           = 21;
  {$EXTERNALSYM PP_UI_PROMPT}
  PP_ENUMALGS_EX         = 22;
  {$EXTERNALSYM PP_ENUMALGS_EX}
  PP_ENUMMANDROOTS       = 25;
  {$EXTERNALSYM PP_ENUMMANDROOTS}
  PP_ENUMELECTROOTS      = 26;
  {$EXTERNALSYM PP_ENUMELECTROOTS}
  PP_KEYSET_TYPE         = 27;
  {$EXTERNALSYM PP_KEYSET_TYPE}
  PP_ADMIN_PIN           = 31;
  {$EXTERNALSYM PP_ADMIN_PIN}
  PP_KEYEXCHANGE_PIN     = 32;
  {$EXTERNALSYM PP_KEYEXCHANGE_PIN}
  PP_SIGNATURE_PIN       = 33;
  {$EXTERNALSYM PP_SIGNATURE_PIN}
  PP_SIG_KEYSIZE_INC     = 34;
  {$EXTERNALSYM PP_SIG_KEYSIZE_INC}
  PP_KEYX_KEYSIZE_INC    = 35;
  {$EXTERNALSYM PP_KEYX_KEYSIZE_INC}
  PP_UNIQUE_CONTAINER    = 36;
  {$EXTERNALSYM PP_UNIQUE_CONTAINER}
  PP_SGC_INFO            = 37;
  {$EXTERNALSYM PP_SGC_INFO}
  PP_USE_HARDWARE_RNG    = 38;
  {$EXTERNALSYM PP_USE_HARDWARE_RNG}
  PP_KEYSPEC             = 39;
  {$EXTERNALSYM PP_KEYSPEC}
  PP_ENUMEX_SIGNING_PROT = 40;
  {$EXTERNALSYM PP_ENUMEX_SIGNING_PROT}

  CRYPT_FIRST    = 1;
  {$EXTERNALSYM CRYPT_FIRST}
  CRYPT_NEXT     = 2;
  {$EXTERNALSYM CRYPT_NEXT}
  CRYPT_SGC_ENUM = 4;
  {$EXTERNALSYM CRYPT_SGC_ENUM}

  CRYPT_IMPL_HARDWARE  = 1;
  {$EXTERNALSYM CRYPT_IMPL_HARDWARE}
  CRYPT_IMPL_SOFTWARE  = 2;
  {$EXTERNALSYM CRYPT_IMPL_SOFTWARE}
  CRYPT_IMPL_MIXED     = 3;
  {$EXTERNALSYM CRYPT_IMPL_MIXED}
  CRYPT_IMPL_UNKNOWN   = 4;
  {$EXTERNALSYM CRYPT_IMPL_UNKNOWN}
  CRYPT_IMPL_REMOVABLE = 8;
  {$EXTERNALSYM CRYPT_IMPL_REMOVABLE}

// key storage flags

  CRYPT_SEC_DESCR = $00000001;
  {$EXTERNALSYM CRYPT_SEC_DESCR}
  CRYPT_PSTORE    = $00000002;
  {$EXTERNALSYM CRYPT_PSTORE}
  CRYPT_UI_PROMPT = $00000004;
  {$EXTERNALSYM CRYPT_UI_PROMPT}

// protocol flags

  CRYPT_FLAG_PCT1    = $0001;
  {$EXTERNALSYM CRYPT_FLAG_PCT1}
  CRYPT_FLAG_SSL2    = $0002;
  {$EXTERNALSYM CRYPT_FLAG_SSL2}
  CRYPT_FLAG_SSL3    = $0004;
  {$EXTERNALSYM CRYPT_FLAG_SSL3}
  CRYPT_FLAG_TLS1    = $0008;
  {$EXTERNALSYM CRYPT_FLAG_TLS1}
  CRYPT_FLAG_IPSEC   = $0010;
  {$EXTERNALSYM CRYPT_FLAG_IPSEC}
  CRYPT_FLAG_SIGNING = $0020;
  {$EXTERNALSYM CRYPT_FLAG_SIGNING}

// SGC flags

  CRYPT_SGC     = $0001;
  {$EXTERNALSYM CRYPT_SGC}
  CRYPT_FASTSGC = $0002;
  {$EXTERNALSYM CRYPT_FASTSGC}

//
// CryptSetProvParam
//

  PP_CLIENT_HWND         = 1;
  {$EXTERNALSYM PP_CLIENT_HWND}
  PP_CONTEXT_INFO        = 11;
  {$EXTERNALSYM PP_CONTEXT_INFO}
  PP_KEYEXCHANGE_KEYSIZE = 12;
  {$EXTERNALSYM PP_KEYEXCHANGE_KEYSIZE}
  PP_SIGNATURE_KEYSIZE   = 13;
  {$EXTERNALSYM PP_SIGNATURE_KEYSIZE}
  PP_KEYEXCHANGE_ALG     = 14;
  {$EXTERNALSYM PP_KEYEXCHANGE_ALG}
  PP_SIGNATURE_ALG       = 15;
  {$EXTERNALSYM PP_SIGNATURE_ALG}
  PP_DELETEKEY           = 24;
  {$EXTERNALSYM PP_DELETEKEY}

  PROV_RSA_FULL      = 1;
  {$EXTERNALSYM PROV_RSA_FULL}
  PROV_RSA_SIG       = 2;
  {$EXTERNALSYM PROV_RSA_SIG}
  PROV_DSS           = 3;
  {$EXTERNALSYM PROV_DSS}
  PROV_FORTEZZA      = 4;
  {$EXTERNALSYM PROV_FORTEZZA}
  PROV_MS_EXCHANGE   = 5;
  {$EXTERNALSYM PROV_MS_EXCHANGE}
  PROV_SSL           = 6;
  {$EXTERNALSYM PROV_SSL}
  PROV_RSA_SCHANNEL  = 12;
  {$EXTERNALSYM PROV_RSA_SCHANNEL}
  PROV_DSS_DH        = 13;
  {$EXTERNALSYM PROV_DSS_DH}
  PROV_EC_ECDSA_SIG  = 14;
  {$EXTERNALSYM PROV_EC_ECDSA_SIG}
  PROV_EC_ECNRA_SIG  = 15;
  {$EXTERNALSYM PROV_EC_ECNRA_SIG}
  PROV_EC_ECDSA_FULL = 16;
  {$EXTERNALSYM PROV_EC_ECDSA_FULL}
  PROV_EC_ECNRA_FULL = 17;
  {$EXTERNALSYM PROV_EC_ECNRA_FULL}
  PROV_DH_SCHANNEL   = 18;
  {$EXTERNALSYM PROV_DH_SCHANNEL}
  PROV_SPYRUS_LYNKS  = 20;
  {$EXTERNALSYM PROV_SPYRUS_LYNKS}
  PROV_RNG           = 21;
  {$EXTERNALSYM PROV_RNG}
  PROV_INTEL_SEC     = 22;
  {$EXTERNALSYM PROV_INTEL_SEC}

//
// STT defined Providers
//

  PROV_STT_MER  = 7;
  {$EXTERNALSYM PROV_STT_MER}
  PROV_STT_ACQ  = 8;
  {$EXTERNALSYM PROV_STT_ACQ}
  PROV_STT_BRND = 9;
  {$EXTERNALSYM PROV_STT_BRND}
  PROV_STT_ROOT = 10;
  {$EXTERNALSYM PROV_STT_ROOT}
  PROV_STT_ISS  = 11;
  {$EXTERNALSYM PROV_STT_ISS}

//
// Provider friendly names
//

  MS_DEF_PROV_A = 'Microsoft Base Cryptographic Provider v1.0';
  {$EXTERNALSYM MS_DEF_PROV_A}
  MS_DEF_PROV_W = 'Microsoft Base Cryptographic Provider v1.0';
  {$EXTERNALSYM MS_DEF_PROV_W}

{$IFDEF UNICODE}
  MS_DEF_PROV = MS_DEF_PROV_W;
  {$EXTERNALSYM MS_DEF_PROV}
{$ELSE}
  MS_DEF_PROV = MS_DEF_PROV_A;
  {$EXTERNALSYM MS_DEF_PROV}
{$ENDIF}

  MS_ENHANCED_PROV_A = 'Microsoft Enhanced Cryptographic Provider v1.0';
  {$EXTERNALSYM MS_ENHANCED_PROV_A}
  MS_ENHANCED_PROV_W = 'Microsoft Enhanced Cryptographic Provider v1.0';
  {$EXTERNALSYM MS_ENHANCED_PROV_W}
{$IFDEF UNICODE}
  MS_ENHANCED_PROV = MS_ENHANCED_PROV_W;
  {$EXTERNALSYM MS_ENHANCED_PROV}
{$ELSE}
  MS_ENHANCED_PROV = MS_ENHANCED_PROV_A;
  {$EXTERNALSYM MS_ENHANCED_PROV}
{$ENDIF}

  MS_STRONG_PROV_A = 'Microsoft Strong Cryptographic Provider';
  {$EXTERNALSYM MS_STRONG_PROV_A}
  MS_STRONG_PROV_W = 'Microsoft Strong Cryptographic Provider';
  {$EXTERNALSYM MS_STRONG_PROV_W}
{$IFDEF UNICODE}
  MS_STRONG_PROV = MS_STRONG_PROV_W;
  {$EXTERNALSYM MS_STRONG_PROV}
{$ELSE}
  MS_STRONG_PROV = MS_STRONG_PROV_A;
  {$EXTERNALSYM MS_STRONG_PROV}
{$ENDIF}

  MS_DEF_RSA_SIG_PROV_A = 'Microsoft RSA Signature Cryptographic Provider';
  {$EXTERNALSYM MS_DEF_RSA_SIG_PROV_A}
  MS_DEF_RSA_SIG_PROV_W = 'Microsoft RSA Signature Cryptographic Provider';
  {$EXTERNALSYM MS_DEF_RSA_SIG_PROV_W}
{$IFDEF UNICODE}
  MS_DEF_RSA_SIG_PROV = MS_DEF_RSA_SIG_PROV_W;
  {$EXTERNALSYM MS_DEF_RSA_SIG_PROV}
{$ELSE}
  MS_DEF_RSA_SIG_PROV = MS_DEF_RSA_SIG_PROV_A;
  {$EXTERNALSYM MS_DEF_RSA_SIG_PROV}
{$ENDIF}

  MS_DEF_RSA_SCHANNEL_PROV_A = 'Microsoft RSA SChannel Cryptographic Provider';
  {$EXTERNALSYM MS_DEF_RSA_SCHANNEL_PROV_A}
  MS_DEF_RSA_SCHANNEL_PROV_W = 'Microsoft RSA SChannel Cryptographic Provider';
  {$EXTERNALSYM MS_DEF_RSA_SCHANNEL_PROV_W}
{$IFDEF UNICODE}
  MS_DEF_RSA_SCHANNEL_PROV = MS_DEF_RSA_SCHANNEL_PROV_W;
  {$EXTERNALSYM MS_DEF_RSA_SCHANNEL_PROV}
{$ELSE}
  MS_DEF_RSA_SCHANNEL_PROV = MS_DEF_RSA_SCHANNEL_PROV_A;
  {$EXTERNALSYM MS_DEF_RSA_SCHANNEL_PROV}
{$ENDIF}

  MS_DEF_DSS_PROV_A = 'Microsoft Base DSS Cryptographic Provider';
  {$EXTERNALSYM MS_DEF_DSS_PROV_A}
  MS_DEF_DSS_PROV_W = 'Microsoft Base DSS Cryptographic Provider';
  {$EXTERNALSYM MS_DEF_DSS_PROV_W}
{$IFDEF UNICODE}
  MS_DEF_DSS_PROV = MS_DEF_DSS_PROV_W;
  {$EXTERNALSYM MS_DEF_DSS_PROV}
{$ELSE}
  MS_DEF_DSS_PROV = MS_DEF_DSS_PROV_A;
  {$EXTERNALSYM MS_DEF_DSS_PROV}
{$ENDIF}

  MS_DEF_DSS_DH_PROV_A = 'Microsoft Base DSS and Diffie-Hellman Cryptographic Provider';
  {$EXTERNALSYM MS_DEF_DSS_DH_PROV_A}
  MS_DEF_DSS_DH_PROV_W = 'Microsoft Base DSS and Diffie-Hellman Cryptographic Provider';
  {$EXTERNALSYM MS_DEF_DSS_DH_PROV_W}
{$IFDEF UNICODE}
  MS_DEF_DSS_DH_PROV = MS_DEF_DSS_DH_PROV_W;
  {$EXTERNALSYM MS_DEF_DSS_DH_PROV}
{$ELSE}
  MS_DEF_DSS_DH_PROV = MS_DEF_DSS_DH_PROV_A;
  {$EXTERNALSYM MS_DEF_DSS_DH_PROV}
{$ENDIF}

  MS_ENH_DSS_DH_PROV_A = 'Microsoft Enhanced DSS and Diffie-Hellman Cryptographic Provider';
  {$EXTERNALSYM MS_ENH_DSS_DH_PROV_A}
  MS_ENH_DSS_DH_PROV_W = 'Microsoft Enhanced DSS and Diffie-Hellman Cryptographic Provider';
  {$EXTERNALSYM MS_ENH_DSS_DH_PROV_W}
{$IFDEF UNICODE}
  MS_ENH_DSS_DH_PROV = MS_ENH_DSS_DH_PROV_W;
  {$EXTERNALSYM MS_ENH_DSS_DH_PROV}
{$ELSE}
  MS_ENH_DSS_DH_PROV = MS_ENH_DSS_DH_PROV_A;
  {$EXTERNALSYM MS_ENH_DSS_DH_PROV}
{$ENDIF}

  MS_DEF_DH_SCHANNEL_PROV_A = 'Microsoft DH SChannel Cryptographic Provider';
  {$EXTERNALSYM MS_DEF_DH_SCHANNEL_PROV_A}
  MS_DEF_DH_SCHANNEL_PROV_W = 'Microsoft DH SChannel Cryptographic Provider';
  {$EXTERNALSYM MS_DEF_DH_SCHANNEL_PROV_W}
{$IFDEF UNICODE}
  MS_DEF_DH_SCHANNEL_PROV = MS_DEF_DH_SCHANNEL_PROV_W;
  {$EXTERNALSYM MS_DEF_DH_SCHANNEL_PROV}
{$ELSE}
  MS_DEF_DH_SCHANNEL_PROV = MS_DEF_DH_SCHANNEL_PROV_A;
  {$EXTERNALSYM MS_DEF_DH_SCHANNEL_PROV}
{$ENDIF}

  MS_SCARD_PROV_A = 'Microsoft Base Smart Card Crypto Provider';
  {$EXTERNALSYM MS_SCARD_PROV_A}
  MS_SCARD_PROV_W = 'Microsoft Base Smart Card Crypto Provider';
  {$EXTERNALSYM MS_SCARD_PROV_W}
{$IFDEF UNICODE}
  MS_SCARD_PROV = MS_SCARD_PROV_W;
  {$EXTERNALSYM MS_SCARD_PROV}
{$ELSE}
  MS_SCARD_PROV = MS_SCARD_PROV_A;
  {$EXTERNALSYM MS_SCARD_PROV}
{$ENDIF}

  MAXUIDLEN = 64;
  {$EXTERNALSYM MAXUIDLEN}

// Exponentiation Offload Reg Location

  EXPO_OFFLOAD_REG_VALUE = 'ExpoOffload';
  {$EXTERNALSYM EXPO_OFFLOAD_REG_VALUE}
  EXPO_OFFLOAD_FUNC_NAME = 'OffloadModExpo';
  {$EXTERNALSYM EXPO_OFFLOAD_FUNC_NAME}

  CUR_BLOB_VERSION = 2;
  {$EXTERNALSYM CUR_BLOB_VERSION}

// structure for use with CryptSetKeyParam for CMS keys
// DO NOT USE THIS STRUCTURE!!!!!

type
  PCMS_KEY_INFO = ^CMS_KEY_INFO;
  {$EXTERNALSYM PCMS_KEY_INFO}
  _CMS_KEY_INFO = record
    dwVersion: DWORD; // sizeof(CMS_KEY_INFO)
    Algid: ALG_ID; // algorithmm id for the key to be converted
    pbOID: LPBYTE; // pointer to OID to hash in with Z
    cbOID: DWORD; // length of OID to hash in with Z
  end;
  {$EXTERNALSYM _CMS_KEY_INFO}
  CMS_KEY_INFO = _CMS_KEY_INFO;
  {$EXTERNALSYM CMS_KEY_INFO}
  TCmsKeyInfo = CMS_KEY_INFO;
  PCmsKeyInfo = PCMS_KEY_INFO;

// structure for use with CryptSetHashParam with CALG_HMAC

  PHMAC_Info = ^HMAC_Info;
  {$EXTERNALSYM PHMAC_Info}
  _HMAC_Info = record
    HashAlgid: ALG_ID;
    pbInnerString: LPBYTE;
    cbInnerString: DWORD;
    pbOuterString: LPBYTE;
    cbOuterString: DWORD;
  end;
  {$EXTERNALSYM _HMAC_Info}
  HMAC_Info = _HMAC_Info;
  {$EXTERNALSYM HMAC_Info}
  THMacInfo = HMAC_Info;
  PHMacInfo = PHMAC_Info;

// structure for use with CryptSetKeyParam with KP_SCHANNEL_ALG

  PSCHANNEL_ALG = ^SCHANNEL_ALG;
  {$EXTERNALSYM PSCHANNEL_ALG}
  _SCHANNEL_ALG = record
    dwUse: DWORD;
    Algid: ALG_ID;
    cBits: DWORD;
    dwFlags: DWORD;
    dwReserved: DWORD;
  end;
  {$EXTERNALSYM _SCHANNEL_ALG}
  SCHANNEL_ALG = _SCHANNEL_ALG;
  {$EXTERNALSYM SCHANNEL_ALG}
  TSChannelAlg = SCHANNEL_ALG;
  PSChannelAlg = PSCHANNEL_ALG;

// uses of algortihms for SCHANNEL_ALG structure

const
  SCHANNEL_MAC_KEY = $00000000;
  {$EXTERNALSYM SCHANNEL_MAC_KEY}
  SCHANNEL_ENC_KEY = $00000001;
  {$EXTERNALSYM SCHANNEL_ENC_KEY}

// uses of dwFlags SCHANNEL_ALG structure

  INTERNATIONAL_USAGE = $00000001;
  {$EXTERNALSYM INTERNATIONAL_USAGE}

type
  PPROV_ENUMALGS = ^PROV_ENUMALGS;
  {$NODEFINE PPROV_ENUMALGS}
  _PROV_ENUMALGS = record
    aiAlgid: ALG_ID;
    dwBitLen: DWORD;
    dwNameLen: DWORD;
    szName: array [0..19] of CHAR;
  end;
  {$EXTERNALSYM _PROV_ENUMALGS}
  PROV_ENUMALGS = _PROV_ENUMALGS;
  {$EXTERNALSYM PROV_ENUMALGS}
  TProvEnumAlgs = PROV_ENUMALGS;
  PProvEnumAlgs = PPROV_ENUMALGS;

  PPROV_ENUMALGS_EX = ^PROV_ENUMALGS_EX;
  {$NODEFINE PPROV_ENUMALGS_EX}
  _PROV_ENUMALGS_EX = record
    aiAlgid: ALG_ID;
    dwDefaultLen: DWORD;
    dwMinLen: DWORD;
    dwMaxLen: DWORD;
    dwProtocols: DWORD;
    dwNameLen: DWORD;
    szName: array [0..19] of CHAR;
    dwLongNameLen: DWORD;
    szLongName: array [0..39] of CHAR;
  end;
  {$EXTERNALSYM _PROV_ENUMALGS_EX}
  PROV_ENUMALGS_EX = _PROV_ENUMALGS_EX;
  {$EXTERNALSYM PROV_ENUMALGS_EX}
  TProvEnumAlgsEx = PROV_ENUMALGS_EX;
  PProvEnumAlgsEx = PPROV_ENUMALGS_EX;

  PPUBLICKEYSTRUC = ^PUBLICKEYSTRUC;
  {$NODEFINE PPUBLICKEYSTRUC}
  _PUBLICKEYSTRUC = record
    bType: BYTE;
    bVersion: BYTE;
    reserved: WORD;
    aiKeyAlg: ALG_ID;
  end;
  {$EXTERNALSYM _PUBLICKEYSTRUC}
  PUBLICKEYSTRUC = _PUBLICKEYSTRUC;
  {$EXTERNALSYM PUBLICKEYSTRUC}
  BLOBHEADER = _PUBLICKEYSTRUC;
  {$EXTERNALSYM BLOBHEADER}
  TPublicKeyStruc = PUBLICKEYSTRUC;

  PRSAPUBKEY = ^RSAPUBKEY;
  {$NODEFINE PRSAPUBKEY}
  _RSAPUBKEY = record
    magic: DWORD; // Has to be RSA1
    bitlen: DWORD; // # of bits in modulus
    pubexp: DWORD; // public exponent
    // Modulus data follows
  end;
  {$EXTERNALSYM _RSAPUBKEY}
  RSAPUBKEY = _RSAPUBKEY;
  {$EXTERNALSYM RSAPUBKEY}
  TRsaPubKey = RSAPUBKEY;

  _PUBKEY = record
    magic: DWORD;
    bitlen: DWORD; // # of bits in modulus
  end;
  {$EXTERNALSYM _PUBKEY}
  DHPUBKEY = _PUBKEY;
  {$EXTERNALSYM DHPUBKEY}
  DSSPUBKEY = _PUBKEY;
  {$EXTERNALSYM DSSPUBKEY}
  KEAPUBKEY = _PUBKEY;
  {$EXTERNALSYM KEAPUBKEY}
  TEKPUBKEY = _PUBKEY;
  {$EXTERNALSYM TEKPUBKEY}

  PDSSSEED = ^DSSSEED;
  {$NODEFINE PDSSSEED}
  _DSSSEED = record
    counter: DWORD;
    seed: array [0..19] of BYTE;
  end;
  {$EXTERNALSYM _DSSSEED}
  DSSSEED = _DSSSEED;
  {$EXTERNALSYM DSSSEED}
  TDssSeed = DSSSEED;

  PPUBKEYVER3 = ^PUBKEYVER3;
  {$NODEFINE PPUBKEYVER3}
  _PUBKEYVER3 = record
    magic: DWORD;
    bitlenP: DWORD; // # of bits in prime modulus
    bitlenQ: DWORD; // # of bits in prime q, 0 if not available
    bitlenJ: DWORD; // # of bits in (p-1)/q, 0 if not available
    DSSSeed: DSSSEED;
  end;
  {$EXTERNALSYM _PUBKEYVER3}
  PUBKEYVER3 = _PUBKEYVER3;
  {$EXTERNALSYM PUBKEYVER3}
  DHPUBKEY_VER3 = PUBKEYVER3;
  {$EXTERNALSYM DHPUBKEY_VER3}
  TPubKeyVer3 = PUBKEYVER3;

  PPRIVKEYVER3 = ^DHPRIVKEY_VER3;
  {$NODEFINE PPRIVKEYVER3}
  _PRIVKEYVER3 = record
    magic: DWORD;
    bitlenP: DWORD; // # of bits in prime modulus
    bitlenQ: DWORD; // # of bits in prime q, 0 if not available
    bitlenJ: DWORD; // # of bits in (p-1)/q, 0 if not available
    bitlenX: DWORD; // # of bits in X
    DSSSeed: DSSSEED;
  end;
  {$EXTERNALSYM _PRIVKEYVER3}
  DHPRIVKEY_VER3 = _PRIVKEYVER3;
  {$EXTERNALSYM DHPRIVKEY_VER3}
  DSSPRIVKEY_VER3 = _PRIVKEYVER3;
  {$EXTERNALSYM DSSPRIVKEY_VER3}
  TDssPrivKey3 = DHPRIVKEY_VER3;

  PKEY_TYPE_SUBTYPE = ^KEY_TYPE_SUBTYPE;
  {$EXTERNALSYM PKEY_TYPE_SUBTYPE}
  _KEY_TYPE_SUBTYPE = record
    dwKeySpec: DWORD;
    Type_: GUID;
    Subtype: GUID;
  end;
  {$EXTERNALSYM _KEY_TYPE_SUBTYPE}
  KEY_TYPE_SUBTYPE = _KEY_TYPE_SUBTYPE;
  {$EXTERNALSYM KEY_TYPE_SUBTYPE}
  TKeyTypeSubType = KEY_TYPE_SUBTYPE;
  PKeyTypeSubType = PKEY_TYPE_SUBTYPE;

  PCERT_FORTEZZA_DATA_PROP = ^CERT_FORTEZZA_DATA_PROP;
  {$NODEFINE PCERT_FORTEZZA_DATA_PROP}
  _CERT_FORTEZZA_DATA_PROP = record
    SerialNumber: array [0..7] of Byte;
    CertIndex: Integer;
    CertLabel: array [0..35] of Byte;
  end;
  {$EXTERNALSYM _CERT_FORTEZZA_DATA_PROP}
  CERT_FORTEZZA_DATA_PROP = _CERT_FORTEZZA_DATA_PROP;
  {$EXTERNALSYM CERT_FORTEZZA_DATA_PROP}
  TCertFortezzaDataProp = CERT_FORTEZZA_DATA_PROP;
  PCertFortezzaDataProp = PCERT_FORTEZZA_DATA_PROP;

//+-------------------------------------------------------------------------
//  CRYPTOAPI BLOB definitions
//--------------------------------------------------------------------------

type
  _CRYPTOAPI_BLOB = record
    cbData: DWORD;
    pbData: LPBYTE;
  end;
  {$EXTERNALSYM _CRYPTOAPI_BLOB}
  CRYPT_INTEGER_BLOB = _CRYPTOAPI_BLOB;
  TCryptIntegerBlob = CRYPT_INTEGER_BLOB;
  {$EXTERNALSYM CRYPT_INTEGER_BLOB}
  PCRYPT_INTEGER_BLOB = ^_CRYPTOAPI_BLOB;
  {$EXTERNALSYM PCRYPT_INTEGER_BLOB}
  PCryptIntegerBlob = PCRYPT_INTEGER_BLOB;
  CRYPT_UINT_BLOB = _CRYPTOAPI_BLOB;
  {$EXTERNALSYM CRYPT_UINT_BLOB}
  TCryptUintBlob = CRYPT_UINT_BLOB;
  PCRYPT_UINT_BLOB = ^_CRYPTOAPI_BLOB;
  {$EXTERNALSYM PCRYPT_UINT_BLOB}
  PCryptUintBlob = PCRYPT_UINT_BLOB;
  CRYPT_OBJID_BLOB = _CRYPTOAPI_BLOB;
  {$EXTERNALSYM CRYPT_OBJID_BLOB}
  TCryptObjIdBlob = CRYPT_OBJID_BLOB;
  PCRYPT_OBJID_BLOB = ^_CRYPTOAPI_BLOB;
  {$EXTERNALSYM PCRYPT_OBJID_BLOB}
  PCryptObjIdBlob = PCRYPT_OBJID_BLOB;
  CERT_NAME_BLOB = _CRYPTOAPI_BLOB;
  {$EXTERNALSYM CERT_NAME_BLOB}
  TCertNameBlob = CERT_NAME_BLOB;
  PCERT_NAME_BLOB = ^_CRYPTOAPI_BLOB;
  {$EXTERNALSYM PCERT_NAME_BLOB}
  PCertNameBlob = PCERT_NAME_BLOB;
  CERT_RDN_VALUE_BLOB = _CRYPTOAPI_BLOB;
  {$EXTERNALSYM CERT_RDN_VALUE_BLOB}
  TCertRdnValueBlob = CERT_RDN_VALUE_BLOB;
  PCERT_RDN_VALUE_BLOB = ^_CRYPTOAPI_BLOB;
  {$EXTERNALSYM PCERT_RDN_VALUE_BLOB}
  PCertRdnValueBlob = PCERT_RDN_VALUE_BLOB;
  CERT_BLOB = _CRYPTOAPI_BLOB;
  {$EXTERNALSYM CERT_BLOB}
  TCertBlob = CERT_BLOB;
  PCERT_BLOB = ^_CRYPTOAPI_BLOB;
  {$EXTERNALSYM PCERT_BLOB}
  PCertBlob = PCERT_BLOB;
  CRL_BLOB = _CRYPTOAPI_BLOB;
  {$EXTERNALSYM CRL_BLOB}
  TCrlBlob = CRL_BLOB;
  PCRL_BLOB = ^_CRYPTOAPI_BLOB;
  {$EXTERNALSYM PCRL_BLOB}
  PCrlBlob = PCRL_BLOB;
  DATA_BLOB = _CRYPTOAPI_BLOB;
  {$EXTERNALSYM DATA_BLOB}
  TDataBlob = DATA_BLOB;
  PDATA_BLOB = ^_CRYPTOAPI_BLOB;
  {$EXTERNALSYM PDATA_BLOB}
  PDataBlob = PDATA_BLOB;
  CRYPT_DATA_BLOB = _CRYPTOAPI_BLOB;
  {$EXTERNALSYM CRYPT_DATA_BLOB}
  TCryptDataBlob = CRYPT_DATA_BLOB;
  PCRYPT_DATA_BLOB = ^_CRYPTOAPI_BLOB;
  {$EXTERNALSYM PCRYPT_DATA_BLOB}
  PCryptDataBlob = PCRYPT_DATA_BLOB;
  CRYPT_HASH_BLOB = _CRYPTOAPI_BLOB;
  {$EXTERNALSYM CRYPT_HASH_BLOB}
  TCryptHashBlob = CRYPT_HASH_BLOB;
  PCRYPT_HASH_BLOB = ^_CRYPTOAPI_BLOB;
  {$EXTERNALSYM PCRYPT_HASH_BLOB}
  PCryptHashBlob = PCRYPT_HASH_BLOB;
  CRYPT_DIGEST_BLOB = _CRYPTOAPI_BLOB;
  {$EXTERNALSYM CRYPT_DIGEST_BLOB}
  TCryptDigestBlob = CRYPT_DIGEST_BLOB;
  PCRYPT_DIGEST_BLOB = ^_CRYPTOAPI_BLOB;
  {$EXTERNALSYM PCRYPT_DIGEST_BLOB}
  PCryptDigestBlob = PCRYPT_DIGEST_BLOB;
  CRYPT_DER_BLOB = _CRYPTOAPI_BLOB;
  {$EXTERNALSYM CRYPT_DER_BLOB}
  TCyptDerBlob = CRYPT_DER_BLOB;
  PCRYPT_DER_BLOB = ^_CRYPTOAPI_BLOB;
  {$EXTERNALSYM PCRYPT_DER_BLOB}
  PCyptDerBlob = PCRYPT_DER_BLOB;
  CRYPT_ATTR_BLOB = _CRYPTOAPI_BLOB;
  {$EXTERNALSYM CRYPT_ATTR_BLOB}
  TCryptAttrBlob = CRYPT_ATTR_BLOB;
  PCRYPT_ATTR_BLOB = ^_CRYPTOAPI_BLOB;
  {$EXTERNALSYM PCRYPT_ATTR_BLOB}
  PCryptAttrBlob = PCRYPT_ATTR_BLOB;  

// structure for use with CryptSetKeyParam for CMS keys

  PCMS_DH_KEY_INFO = ^CMS_DH_KEY_INFO;
  {$EXTERNALSYM PCMS_DH_KEY_INFO}
  _CMS_DH_KEY_INFO = record
    dwVersion: DWORD; // sizeof(CMS_DH_KEY_INFO)
    Algid: ALG_ID; // algorithmm id for the key to be converted
    pszContentEncObjId: LPSTR; // pointer to OID to hash in with Z
    PubInfo: CRYPT_DATA_BLOB; // OPTIONAL - public information
    pReserved: Pointer; // reserved - should be NULL
  end;
  {$EXTERNALSYM _CMS_DH_KEY_INFO}
  CMS_DH_KEY_INFO = _CMS_DH_KEY_INFO;
  {$EXTERNALSYM CMS_DH_KEY_INFO}
  TCmsDhKeyInfo = CMS_DH_KEY_INFO;
  PCmsDhKeyInfo = PCMS_DH_KEY_INFO;

function CryptAcquireContextA(var phProv: HCRYPTPROV; pszContainer: LPCSTR;
  pszProvider: LPCSTR; dwProvType: DWORD; dwFlags: DWORD): BOOL; stdcall;
{$EXTERNALSYM CryptAcquireContextA}
function CryptAcquireContextW(var phProv: HCRYPTPROV; pszContainer: LPCWSTR;
  pszProvider: LPCWSTR; dwProvType: DWORD; dwFlags: DWORD): BOOL; stdcall;
{$EXTERNALSYM CryptAcquireContextW}

{$IFDEF UNICODE}
function CryptAcquireContext(var phProv: HCRYPTPROV; pszContainer: LPCWSTR;
  pszProvider: LPCWSTR; dwProvType: DWORD; dwFlags: DWORD): BOOL; stdcall;
{$EXTERNALSYM CryptAcquireContext}
{$ELSE}
function CryptAcquireContext(var phProv: HCRYPTPROV; pszContainer: LPCSTR;
  pszProvider: LPCSTR; dwProvType: DWORD; dwFlags: DWORD): BOOL; stdcall;
{$EXTERNALSYM CryptAcquireContext}
{$ENDIF}

function CryptReleaseContext(hProv: HCRYPTPROV; dwFlags: ULONG_PTR): BOOL; stdcall;
{$EXTERNALSYM CryptReleaseContext}

function CryptGenKey(hProv: HCRYPTPROV; Algid: ALG_ID; dwFlags: DWORD;
  var phKey: HCRYPTKEY): BOOL; stdcall;
{$EXTERNALSYM CryptGenKey}

function CryptDeriveKey(hProv: HCRYPTPROV; Algid: ALG_ID; hBaseData: HCRYPTHASH;
  dwFlags: DWORD; var phKey: HCRYPTKEY): BOOL; stdcall;
{$EXTERNALSYM CryptDeriveKey}

function CryptDestroyKey(hKey: HCRYPTKEY): BOOL; stdcall;
{$EXTERNALSYM CryptDestroyKey}

function CryptSetKeyParam(hKey: HCRYPTKEY; dwParam: DWORD; pbData: LPBYTE;
  dwFlags: DWORD): BOOL; stdcall;
{$EXTERNALSYM CryptSetKeyParam}

function CryptGetKeyParam(hKey: HCRYPTKEY; dwParam: DWORD; pbData: LPBYTE;
  var pdwDataLen: DWORD; dwFlags: DWORD): BOOL; stdcall;
{$EXTERNALSYM CryptGetKeyParam}

function CryptSetHashParam(hHash: HCRYPTHASH; dwParam: DWORD; pbData: LPBYTE;
  dwFlags: DWORD): BOOL; stdcall;
{$EXTERNALSYM CryptSetHashParam}

function CryptGetHashParam(hHash: HCRYPTHASH; dwParam: DWORD; pbData: LPBYTE;
  var pdwDataLen: DWORD; dwFlags: DWORD): BOOL; stdcall;
{$EXTERNALSYM CryptGetHashParam}

function CryptSetProvParam(hProv: HCRYPTPROV; dwParam: DWORD; pbData: LPBYTE;
  dwFlags: DWORD): BOOL; stdcall;
{$EXTERNALSYM CryptSetProvParam}

function CryptGetProvParam(hProv: HCRYPTPROV; dwParam: DWORD; pbData: LPBYTE;
  var pdwDataLen: DWORD; dwFlags: DWORD): BOOL; stdcall;
{$EXTERNALSYM CryptGetProvParam}

function CryptGenRandom(hProv: HCRYPTPROV; dwLen: DWORD; pbBuffer: LPBYTE): BOOL; stdcall;
{$EXTERNALSYM CryptGenRandom}

function CryptGetUserKey(hProv: HCRYPTPROV; dwKeySpec: DWORD; var phUserKey: HCRYPTKEY): BOOL; stdcall;
{$EXTERNALSYM CryptGetUserKey}

function CryptExportKey(hKey, hExpKey: HCRYPTKEY; dwBlobType, dwFlags: DWORD;
  pbData: LPBYTE; var pdwDataLen: DWORD): BOOL; stdcall;
{$EXTERNALSYM CryptExportKey}

function CryptImportKey(hProv: HCRYPTPROV; pbData: LPBYTE; dwDataLen: DWORD;
  hPubKey: HCRYPTKEY; dwFlags: DWORD; var phKey: HCRYPTKEY): BOOL; stdcall;
{$EXTERNALSYM CryptImportKey}

function CryptEncrypt(hKey: HCRYPTKEY; hHash: HCRYPTHASH; Final: BOOL;
  dwFlags: DWORD; pbData: LPBYTE; var pdwDataLen: DWORD; dwBufLen: DWORD): BOOL; stdcall;
{$EXTERNALSYM CryptEncrypt}

function CryptDecrypt(hKey: HCRYPTKEY; hHash: HCRYPTHASH; Final: BOOL;
  dwFlags: DWORD; pbData: LPBYTE; var pdwDataLen: DWORD): BOOL; stdcall;
{$EXTERNALSYM CryptDecrypt}

function CryptCreateHash(hProv: HCRYPTPROV; Algid: ALG_ID; hKey: HCRYPTKEY;
  dwFlags: DWORD; var phHash: HCRYPTHASH): BOOL; stdcall;
{$EXTERNALSYM CryptCreateHash}

function CryptHashData(hHash: HCRYPTHASH; pbData: LPBYTE; dwDataLen, dwFlags: DWORD): BOOL; stdcall;
{$EXTERNALSYM CryptHashData}

function CryptHashSessionKey(hHash: HCRYPTHASH; hKey: HCRYPTKEY; dwFlags: DWORD): BOOL; stdcall;
{$EXTERNALSYM CryptHashSessionKey}

function CryptDestroyHash(hHash: HCRYPTHASH): BOOL; stdcall;
{$EXTERNALSYM CryptDestroyHash}

function CryptSignHashA(hHash: HCRYPTHASH; dwKeySpec: DWORD; sDescription: LPCSTR;
  dwFlags: DWORD; pbSignature: LPBYTE; var pdwSigLen: DWORD): BOOL; stdcall;
{$EXTERNALSYM CryptSignHashA}
function CryptSignHashW(hHash: HCRYPTHASH; dwKeySpec: DWORD; sDescription: LPCWSTR;
  dwFlags: DWORD; pbSignature: LPBYTE; var pdwSigLen: DWORD): BOOL; stdcall;
{$EXTERNALSYM CryptSignHashW}

{$IFDEF UNICODE}
function CryptSignHash(hHash: HCRYPTHASH; dwKeySpec: DWORD; sDescription: LPCWSTR;
  dwFlags: DWORD; pbSignature: LPBYTE; var pdwSigLen: DWORD): BOOL; stdcall;
{$EXTERNALSYM CryptSignHash}
{$ELSE}
function CryptSignHash(hHash: HCRYPTHASH; dwKeySpec: DWORD; sDescription: LPCSTR;
  dwFlags: DWORD; pbSignature: LPBYTE; var pdwSigLen: DWORD): BOOL; stdcall;
{$EXTERNALSYM CryptSignHash}
{$ENDIF}

function CryptVerifySignatureA(hHash: HCRYPTHASH; pbSignature: LPBYTE;
  dwSigLen: DWORD; hPubKey: HCRYPTKEY; sDescription: LPCSTR; dwFlags: DWORD): BOOL; stdcall;
{$EXTERNALSYM CryptVerifySignatureA}
function CryptVerifySignatureW(hHash: HCRYPTHASH; pbSignature: LPBYTE;
  dwSigLen: DWORD; hPubKey: HCRYPTKEY; sDescription: LPCWSTR; dwFlags: DWORD): BOOL; stdcall;
{$EXTERNALSYM CryptVerifySignatureW}

{$IFDEF UNICODE}
function CryptVerifySignature(hHash: HCRYPTHASH; pbSignature: LPBYTE;
  dwSigLen: DWORD; hPubKey: HCRYPTKEY; sDescription: LPCWSTR; dwFlags: DWORD): BOOL; stdcall;
{$EXTERNALSYM CryptVerifySignature}
{$ELSE}
function CryptVerifySignature(hHash: HCRYPTHASH; pbSignature: LPBYTE;
  dwSigLen: DWORD; hPubKey: HCRYPTKEY; sDescription: LPCSTR; dwFlags: DWORD): BOOL; stdcall;
{$EXTERNALSYM CryptVerifySignature}
{$ENDIF}

function CryptSetProviderA(pszProvName: LPCSTR; dwProvType: DWORD): BOOL; stdcall;
{$EXTERNALSYM CryptSetProviderA}
function CryptSetProviderW(pszProvName: LPCWSTR; dwProvType: DWORD): BOOL; stdcall;
{$EXTERNALSYM CryptSetProviderW}

{$IFDEF UNICODE}
function CryptSetProvider(pszProvName: LPCWSTR; dwProvType: DWORD): BOOL; stdcall;
{$EXTERNALSYM CryptSetProvider}
{$ELSE}
function CryptSetProvider(pszProvName: LPCSTR; dwProvType: DWORD): BOOL; stdcall;
{$EXTERNALSYM CryptSetProvider}
{$ENDIF}

function CryptSetProviderExA(pszProvName: LPCSTR; dwProvType: DWORD;
  pdwReserved: LPDWORD; dwFlags: DWORD): BOOL; stdcall;
{$EXTERNALSYM CryptSetProviderExA}
function CryptSetProviderExW(pszProvName: LPCWSTR; dwProvType: DWORD;
  pdwReserved: LPDWORD; dwFlags: DWORD): BOOL; stdcall;
{$EXTERNALSYM CryptSetProviderExW}

{$IFDEF UNICODE}
function CryptSetProviderEx(pszProvName: LPCWSTR; dwProvType: DWORD;
  pdwReserved: LPDWORD; dwFlags: DWORD): BOOL; stdcall;
{$EXTERNALSYM CryptSetProviderEx}
{$ELSE}
function CryptSetProviderEx(pszProvName: LPCSTR; dwProvType: DWORD;
  pdwReserved: LPDWORD; dwFlags: DWORD): BOOL; stdcall;
{$EXTERNALSYM CryptSetProviderEx}
{$ENDIF}

function CryptGetDefaultProviderA(dwProvType: DWORD; pdwReserved: LPDWORD;
  dwFlags: DWORD; pszProvName: LPSTR; var pcbProvName: DWORD): BOOL; stdcall;
{$EXTERNALSYM CryptGetDefaultProviderA}
function CryptGetDefaultProviderW(dwProvType: DWORD; pdwReserved: LPDWORD;
  dwFlags: DWORD; pszProvName: LPWSTR; var pcbProvName: DWORD): BOOL; stdcall;
{$EXTERNALSYM CryptGetDefaultProviderW}

{$IFDEF UNICODE}
function CryptGetDefaultProvider(dwProvType: DWORD; pdwReserved: LPDWORD;
  dwFlags: DWORD; pszProvName: LPWSTR; var pcbProvName: DWORD): BOOL; stdcall;
{$EXTERNALSYM CryptGetDefaultProvider}
{$ELSE}
function CryptGetDefaultProvider(dwProvType: DWORD; pdwReserved: LPDWORD;
  dwFlags: DWORD; pszProvName: LPSTR; var pcbProvName: DWORD): BOOL; stdcall;
{$EXTERNALSYM CryptGetDefaultProvider}
{$ENDIF}

function CryptEnumProviderTypesA(dwIndex: DWORD; pdwReserved: LPDWORD;
  dwFlags: DWORD; var pdwProvType: DWORD; pszTypeName: LPSTR;
  var pcbTypeName: DWORD): BOOL; stdcall;
{$EXTERNALSYM CryptEnumProviderTypesA}
function CryptEnumProviderTypesW(dwIndex: DWORD; pdwReserved: LPDWORD;
  dwFlags: DWORD; var pdwProvType: DWORD; pszTypeName: LPWSTR;
  var pcbTypeName: DWORD): BOOL; stdcall;
{$EXTERNALSYM CryptEnumProviderTypesW}

{$IFDEF UNICODE}
function CryptEnumProviderTypes(dwIndex: DWORD; pdwReserved: LPDWORD;
  dwFlags: DWORD; var pdwProvType: DWORD; pszTypeName: LPWSTR;
  var pcbTypeName: DWORD): BOOL; stdcall;
{$EXTERNALSYM CryptEnumProviderTypes}
{$ELSE}
function CryptEnumProviderTypes(dwIndex: DWORD; pdwReserved: LPDWORD;
  dwFlags: DWORD; var pdwProvType: DWORD; pszTypeName: LPSTR;
  var pcbTypeName: DWORD): BOOL; stdcall;
{$EXTERNALSYM CryptEnumProviderTypes}
{$ENDIF}

function CryptEnumProvidersA(dwIndex: DWORD; pdwReserved: LPDWORD; dwFlags: DWORD;
  var pdwProvType: DWORD; pszProvName: LPSTR; var pcbProvName: DWORD): BOOL; stdcall;
{$EXTERNALSYM CryptEnumProvidersA}
function CryptEnumProvidersW(dwIndex: DWORD; pdwReserved: LPDWORD; dwFlags: DWORD;
  var pdwProvType: DWORD; pszProvName: LPWSTR; var pcbProvName: DWORD): BOOL; stdcall;
{$EXTERNALSYM CryptEnumProvidersW}

{$IFDEF UNICODE}
function CryptEnumProviders(dwIndex: DWORD; pdwReserved: LPDWORD; dwFlags: DWORD;
  var pdwProvType: DWORD; pszProvName: LPWSTR; var pcbProvName: DWORD): BOOL; stdcall;
{$EXTERNALSYM CryptEnumProviders}
{$ELSE}
function CryptEnumProviders(dwIndex: DWORD; pdwReserved: LPDWORD; dwFlags: DWORD;
  var pdwProvType: DWORD; pszProvName: LPSTR; var pcbProvName: DWORD): BOOL; stdcall;
{$EXTERNALSYM CryptEnumProviders}
{$ENDIF}

function CryptContextAddRef(hProv: HCRYPTPROV; pdwReserved: LPDWORD; dwFlags: DWORD): BOOL; stdcall;
{$EXTERNALSYM CryptContextAddRef}

function CryptDuplicateKey(hKey: HCRYPTKEY; pdwReserved: LPDWORD; dwFlags: DWORD;
  var phKey: HCRYPTKEY): BOOL; stdcall;
{$EXTERNALSYM CryptDuplicateKey}

function CryptDuplicateHash(hHash: HCRYPTHASH; pdwReserved: LPDWORD;
  dwFlags: DWORD; var phHash: HCRYPTHASH): BOOL; stdcall;
{$EXTERNALSYM CryptDuplicateHash}

//+-------------------------------------------------------------------------
//  In a CRYPT_BIT_BLOB the last byte may contain 0-7 unused bits. Therefore, the
//  overall bit length is cbData * 8 - cUnusedBits.
//--------------------------------------------------------------------------

type
  PCRYPT_BIT_BLOB = ^CRYPT_BIT_BLOB;
  {$EXTERNALSYM PCRYPT_BIT_BLOB}
  _CRYPT_BIT_BLOB = record
    cbData: DWORD;
    pbData: LPBYTE;
    cUnusedBits: DWORD;
  end;
  {$EXTERNALSYM _CRYPT_BIT_BLOB}
  CRYPT_BIT_BLOB = _CRYPT_BIT_BLOB;
  {$EXTERNALSYM CRYPT_BIT_BLOB}
  TCryptBitBlob = CRYPT_BIT_BLOB;
  PCryptBitBlob = PCRYPT_BIT_BLOB;

//+-------------------------------------------------------------------------
//  Type used for any algorithm
//
//  Where the Parameters CRYPT_OBJID_BLOB is in its encoded representation. For most
//  algorithm types, the Parameters CRYPT_OBJID_BLOB is NULL (Parameters.cbData = 0).
//--------------------------------------------------------------------------

type
  PCRYPT_ALGORITHM_IDENTIFIER = ^CRYPT_ALGORITHM_IDENTIFIER;
  {$EXTERNALSYM PCRYPT_ALGORITHM_IDENTIFIER}
  _CRYPT_ALGORITHM_IDENTIFIER = record
    pszObjId: LPSTR;
    Parameters: CRYPT_OBJID_BLOB;
  end;
  {$EXTERNALSYM _CRYPT_ALGORITHM_IDENTIFIER}
  CRYPT_ALGORITHM_IDENTIFIER = _CRYPT_ALGORITHM_IDENTIFIER;
  {$EXTERNALSYM CRYPT_ALGORITHM_IDENTIFIER}
  TCryptAlgorithmIdentifier = CRYPT_ALGORITHM_IDENTIFIER;
  PCryptAlgorithmIdentifier = PCRYPT_ALGORITHM_IDENTIFIER;

// Following are the definitions of various algorithm object identifiers
// RSA

const
  szOID_RSA         = '1.2.840.113549';
  {$EXTERNALSYM szOID_RSA}
  szOID_PKCS        = '1.2.840.113549.1';
  {$EXTERNALSYM szOID_PKCS}
  szOID_RSA_HASH    = '1.2.840.113549.2';
  {$EXTERNALSYM szOID_RSA_HASH}
  szOID_RSA_ENCRYPT = '1.2.840.113549.3';
  {$EXTERNALSYM szOID_RSA_ENCRYPT}

  szOID_PKCS_1  = '1.2.840.113549.1.1';
  {$EXTERNALSYM szOID_PKCS_1}
  szOID_PKCS_2  = '1.2.840.113549.1.2';
  {$EXTERNALSYM szOID_PKCS_2}
  szOID_PKCS_3  = '1.2.840.113549.1.3';
  {$EXTERNALSYM szOID_PKCS_3}
  szOID_PKCS_4  = '1.2.840.113549.1.4';
  {$EXTERNALSYM szOID_PKCS_4}
  szOID_PKCS_5  = '1.2.840.113549.1.5';
  {$EXTERNALSYM szOID_PKCS_5}
  szOID_PKCS_6  = '1.2.840.113549.1.6';
  {$EXTERNALSYM szOID_PKCS_6}
  szOID_PKCS_7  = '1.2.840.113549.1.7';
  {$EXTERNALSYM szOID_PKCS_7}
  szOID_PKCS_8  = '1.2.840.113549.1.8';
  {$EXTERNALSYM szOID_PKCS_8}
  szOID_PKCS_9  = '1.2.840.113549.1.9';
  {$EXTERNALSYM szOID_PKCS_9}
  szOID_PKCS_10 = '1.2.840.113549.1.10';
  {$EXTERNALSYM szOID_PKCS_10}
  szOID_PKCS_12 = '1.2.840.113549.1.12';
  {$EXTERNALSYM szOID_PKCS_12}

  szOID_RSA_RSA         = '1.2.840.113549.1.1.1';
  {$EXTERNALSYM szOID_RSA_RSA}
  szOID_RSA_MD2RSA      = '1.2.840.113549.1.1.2';
  {$EXTERNALSYM szOID_RSA_MD2RSA}
  szOID_RSA_MD4RSA      = '1.2.840.113549.1.1.3';
  {$EXTERNALSYM szOID_RSA_MD4RSA}
  szOID_RSA_MD5RSA      = '1.2.840.113549.1.1.4';
  {$EXTERNALSYM szOID_RSA_MD5RSA}
  szOID_RSA_SHA1RSA     = '1.2.840.113549.1.1.5';
  {$EXTERNALSYM szOID_RSA_SHA1RSA}
  szOID_RSA_SETOAEP_RSA = '1.2.840.113549.1.1.6';
  {$EXTERNALSYM szOID_RSA_SETOAEP_RSA}

  szOID_RSA_DH = '1.2.840.113549.1.3.1';
  {$EXTERNALSYM szOID_RSA_DH}

  szOID_RSA_data          = '1.2.840.113549.1.7.1';
  {$EXTERNALSYM szOID_RSA_data}
  szOID_RSA_signedData    = '1.2.840.113549.1.7.2';
  {$EXTERNALSYM szOID_RSA_signedData}
  szOID_RSA_envelopedData = '1.2.840.113549.1.7.3';
  {$EXTERNALSYM szOID_RSA_envelopedData}
  szOID_RSA_signEnvData   = '1.2.840.113549.1.7.4';
  {$EXTERNALSYM szOID_RSA_signEnvData}
  szOID_RSA_digestedData  = '1.2.840.113549.1.7.5';
  {$EXTERNALSYM szOID_RSA_digestedData}
  szOID_RSA_hashedData    = '1.2.840.113549.1.7.5';
  {$EXTERNALSYM szOID_RSA_hashedData}
  szOID_RSA_encryptedData = '1.2.840.113549.1.7.6';
  {$EXTERNALSYM szOID_RSA_encryptedData}

  szOID_RSA_emailAddr         = '1.2.840.113549.1.9.1';
  {$EXTERNALSYM szOID_RSA_emailAddr}
  szOID_RSA_unstructName      = '1.2.840.113549.1.9.2';
  {$EXTERNALSYM szOID_RSA_unstructName}
  szOID_RSA_contentType       = '1.2.840.113549.1.9.3';
  {$EXTERNALSYM szOID_RSA_contentType}
  szOID_RSA_messageDigest     = '1.2.840.113549.1.9.4';
  {$EXTERNALSYM szOID_RSA_messageDigest}
  szOID_RSA_signingTime       = '1.2.840.113549.1.9.5';
  {$EXTERNALSYM szOID_RSA_signingTime}
  szOID_RSA_counterSign       = '1.2.840.113549.1.9.6';
  {$EXTERNALSYM szOID_RSA_counterSign}
  szOID_RSA_challengePwd      = '1.2.840.113549.1.9.7';
  {$EXTERNALSYM szOID_RSA_challengePwd}
  szOID_RSA_unstructAddr      = '1.2.840.113549.1.9.8';
  {$EXTERNALSYM szOID_RSA_unstructAddr}
  szOID_RSA_extCertAttrs      = '1.2.840.113549.1.9.9';
  {$EXTERNALSYM szOID_RSA_extCertAttrs}
  szOID_RSA_certExtensions    = '1.2.840.113549.1.9.14';
  {$EXTERNALSYM szOID_RSA_certExtensions}
  szOID_RSA_SMIMECapabilities = '1.2.840.113549.1.9.15';
  {$EXTERNALSYM szOID_RSA_SMIMECapabilities}
  szOID_RSA_preferSignedData  = '1.2.840.113549.1.9.15.1';
  {$EXTERNALSYM szOID_RSA_preferSignedData}

  szOID_RSA_SMIMEalg            = '1.2.840.113549.1.9.16.3';
  {$EXTERNALSYM szOID_RSA_SMIMEalg}
  szOID_RSA_SMIMEalgESDH        = '1.2.840.113549.1.9.16.3.5';
  {$EXTERNALSYM szOID_RSA_SMIMEalgESDH}
  szOID_RSA_SMIMEalgCMS3DESwrap = '1.2.840.113549.1.9.16.3.6';
  {$EXTERNALSYM szOID_RSA_SMIMEalgCMS3DESwrap}
  szOID_RSA_SMIMEalgCMSRC2wrap  = '1.2.840.113549.1.9.16.3.7';
  {$EXTERNALSYM szOID_RSA_SMIMEalgCMSRC2wrap}

  szOID_RSA_MD2 = '1.2.840.113549.2.2';
  {$EXTERNALSYM szOID_RSA_MD2}
  szOID_RSA_MD4 = '1.2.840.113549.2.4';
  {$EXTERNALSYM szOID_RSA_MD4}
  szOID_RSA_MD5 = '1.2.840.113549.2.5';
  {$EXTERNALSYM szOID_RSA_MD5}

  szOID_RSA_RC2CBC       = '1.2.840.113549.3.2';
  {$EXTERNALSYM szOID_RSA_RC2CBC}
  szOID_RSA_RC4          = '1.2.840.113549.3.4';
  {$EXTERNALSYM szOID_RSA_RC4}
  szOID_RSA_DES_EDE3_CBC = '1.2.840.113549.3.7';
  {$EXTERNALSYM szOID_RSA_DES_EDE3_CBC}
  szOID_RSA_RC5_CBCPad   = '1.2.840.113549.3.9';
  {$EXTERNALSYM szOID_RSA_RC5_CBCPad}


  szOID_ANSI_X942    = '1.2.840.10046';
  {$EXTERNALSYM szOID_ANSI_X942}
  szOID_ANSI_X942_DH = '1.2.840.10046.2.1';
  {$EXTERNALSYM szOID_ANSI_X942_DH}

  szOID_X957         = '1.2.840.10040';
  {$EXTERNALSYM szOID_X957}
  szOID_X957_DSA     = '1.2.840.10040.4.1';
  {$EXTERNALSYM szOID_X957_DSA}
  szOID_X957_SHA1DSA = '1.2.840.10040.4.3';
  {$EXTERNALSYM szOID_X957_SHA1DSA}

// ITU-T UsefulDefinitions

  szOID_DS         = '2.5';
  {$EXTERNALSYM szOID_DS}
  szOID_DSALG      = '2.5.8';
  {$EXTERNALSYM szOID_DSALG}
  szOID_DSALG_CRPT = '2.5.8.1';
  {$EXTERNALSYM szOID_DSALG_CRPT}
  szOID_DSALG_HASH = '2.5.8.2';
  {$EXTERNALSYM szOID_DSALG_HASH}
  szOID_DSALG_SIGN = '2.5.8.3';
  {$EXTERNALSYM szOID_DSALG_SIGN}
  szOID_DSALG_RSA  = '2.5.8.1.1';
  {$EXTERNALSYM szOID_DSALG_RSA}

// NIST OSE Implementors' Workshop (OIW)
// http://nemo.ncsl.nist.gov/oiw/agreements/stable/OSI/12s_9506.w51
// http://nemo.ncsl.nist.gov/oiw/agreements/working/OSI/12w_9503.w51

  szOID_OIW = '1.3.14';
  {$EXTERNALSYM szOID_OIW}

// NIST OSE Implementors' Workshop (OIW) Security SIG algorithm identifiers

  szOID_OIWSEC             = '1.3.14.3.2';
  {$EXTERNALSYM szOID_OIWSEC}
  szOID_OIWSEC_md4RSA      = '1.3.14.3.2.2';
  {$EXTERNALSYM szOID_OIWSEC_md4RSA}
  szOID_OIWSEC_md5RSA      = '1.3.14.3.2.3';
  {$EXTERNALSYM szOID_OIWSEC_md5RSA}
  szOID_OIWSEC_md4RSA2     = '1.3.14.3.2.4';
  {$EXTERNALSYM szOID_OIWSEC_md4RSA2}
  szOID_OIWSEC_desECB      = '1.3.14.3.2.6';
  {$EXTERNALSYM szOID_OIWSEC_desECB}
  szOID_OIWSEC_desCBC      = '1.3.14.3.2.7';
  {$EXTERNALSYM szOID_OIWSEC_desCBC}
  szOID_OIWSEC_desOFB      = '1.3.14.3.2.8';
  {$EXTERNALSYM szOID_OIWSEC_desOFB}
  szOID_OIWSEC_desCFB      = '1.3.14.3.2.9';
  {$EXTERNALSYM szOID_OIWSEC_desCFB}
  szOID_OIWSEC_desMAC      = '1.3.14.3.2.10';
  {$EXTERNALSYM szOID_OIWSEC_desMAC}
  szOID_OIWSEC_rsaSign     = '1.3.14.3.2.11';
  {$EXTERNALSYM szOID_OIWSEC_rsaSign}
  szOID_OIWSEC_dsa         = '1.3.14.3.2.12';
  {$EXTERNALSYM szOID_OIWSEC_dsa}
  szOID_OIWSEC_shaDSA      = '1.3.14.3.2.13';
  {$EXTERNALSYM szOID_OIWSEC_shaDSA}
  szOID_OIWSEC_mdc2RSA     = '1.3.14.3.2.14';
  {$EXTERNALSYM szOID_OIWSEC_mdc2RSA}
  szOID_OIWSEC_shaRSA      = '1.3.14.3.2.15';
  {$EXTERNALSYM szOID_OIWSEC_shaRSA}
  szOID_OIWSEC_dhCommMod   = '1.3.14.3.2.16';
  {$EXTERNALSYM szOID_OIWSEC_dhCommMod}
  szOID_OIWSEC_desEDE      = '1.3.14.3.2.17';
  {$EXTERNALSYM szOID_OIWSEC_desEDE}
  szOID_OIWSEC_sha         = '1.3.14.3.2.18';
  {$EXTERNALSYM szOID_OIWSEC_sha}
  szOID_OIWSEC_mdc2        = '1.3.14.3.2.19';
  {$EXTERNALSYM szOID_OIWSEC_mdc2}
  szOID_OIWSEC_dsaComm     = '1.3.14.3.2.20';
  {$EXTERNALSYM szOID_OIWSEC_dsaComm}
  szOID_OIWSEC_dsaCommSHA  = '1.3.14.3.2.21';
  {$EXTERNALSYM szOID_OIWSEC_dsaCommSHA}
  szOID_OIWSEC_rsaXchg     = '1.3.14.3.2.22';
  {$EXTERNALSYM szOID_OIWSEC_rsaXchg}
  szOID_OIWSEC_keyHashSeal = '1.3.14.3.2.23';
  {$EXTERNALSYM szOID_OIWSEC_keyHashSeal}
  szOID_OIWSEC_md2RSASign  = '1.3.14.3.2.24';
  {$EXTERNALSYM szOID_OIWSEC_md2RSASign}
  szOID_OIWSEC_md5RSASign  = '1.3.14.3.2.25';
  {$EXTERNALSYM szOID_OIWSEC_md5RSASign}
  szOID_OIWSEC_sha1        = '1.3.14.3.2.26';
  {$EXTERNALSYM szOID_OIWSEC_sha1}
  szOID_OIWSEC_dsaSHA1     = '1.3.14.3.2.27';
  {$EXTERNALSYM szOID_OIWSEC_dsaSHA1}
  szOID_OIWSEC_dsaCommSHA1 = '1.3.14.3.2.28';
  {$EXTERNALSYM szOID_OIWSEC_dsaCommSHA1}
  szOID_OIWSEC_sha1RSASign = '1.3.14.3.2.29';
  {$EXTERNALSYM szOID_OIWSEC_sha1RSASign}

// NIST OSE Implementors' Workshop (OIW) Directory SIG algorithm identifiers

  szOID_OIWDIR        = '1.3.14.7.2';
  {$EXTERNALSYM szOID_OIWDIR}
  szOID_OIWDIR_CRPT   = '1.3.14.7.2.1';
  {$EXTERNALSYM szOID_OIWDIR_CRPT}
  szOID_OIWDIR_HASH   = '1.3.14.7.2.2';
  {$EXTERNALSYM szOID_OIWDIR_HASH}
  szOID_OIWDIR_SIGN   = '1.3.14.7.2.3';
  {$EXTERNALSYM szOID_OIWDIR_SIGN}
  szOID_OIWDIR_md2    = '1.3.14.7.2.2.1';
  {$EXTERNALSYM szOID_OIWDIR_md2}
  szOID_OIWDIR_md2RSA = '1.3.14.7.2.3.1';
  {$EXTERNALSYM szOID_OIWDIR_md2RSA}

// INFOSEC Algorithms
// joint-iso-ccitt(2) country(16) us(840) organization(1) us-government(101) dod(2) id-infosec(1)

  szOID_INFOSEC                       = '2.16.840.1.101.2.1';
  {$EXTERNALSYM szOID_INFOSEC}
  szOID_INFOSEC_sdnsSignature         = '2.16.840.1.101.2.1.1.1';
  {$EXTERNALSYM szOID_INFOSEC_sdnsSignature}
  szOID_INFOSEC_mosaicSignature       = '2.16.840.1.101.2.1.1.2';
  {$EXTERNALSYM szOID_INFOSEC_mosaicSignature}
  szOID_INFOSEC_sdnsConfidentiality   = '2.16.840.1.101.2.1.1.3';
  {$EXTERNALSYM szOID_INFOSEC_sdnsConfidentiality}
  szOID_INFOSEC_mosaicConfidentiality = '2.16.840.1.101.2.1.1.4';
  {$EXTERNALSYM szOID_INFOSEC_mosaicConfidentiality}
  szOID_INFOSEC_sdnsIntegrity         = '2.16.840.1.101.2.1.1.5';
  {$EXTERNALSYM szOID_INFOSEC_sdnsIntegrity}
  szOID_INFOSEC_mosaicIntegrity       = '2.16.840.1.101.2.1.1.6';
  {$EXTERNALSYM szOID_INFOSEC_mosaicIntegrity}
  szOID_INFOSEC_sdnsTokenProtection   = '2.16.840.1.101.2.1.1.7';
  {$EXTERNALSYM szOID_INFOSEC_sdnsTokenProtection}
  szOID_INFOSEC_mosaicTokenProtection = '2.16.840.1.101.2.1.1.8';
  {$EXTERNALSYM szOID_INFOSEC_mosaicTokenProtection}
  szOID_INFOSEC_sdnsKeyManagement     = '2.16.840.1.101.2.1.1.9';
  {$EXTERNALSYM szOID_INFOSEC_sdnsKeyManagement}
  szOID_INFOSEC_mosaicKeyManagement   = '2.16.840.1.101.2.1.1.10';
  {$EXTERNALSYM szOID_INFOSEC_mosaicKeyManagement}
  szOID_INFOSEC_sdnsKMandSig          = '2.16.840.1.101.2.1.1.11';
  {$EXTERNALSYM szOID_INFOSEC_sdnsKMandSig}
  szOID_INFOSEC_mosaicKMandSig        = '2.16.840.1.101.2.1.1.12';
  {$EXTERNALSYM szOID_INFOSEC_mosaicKMandSig}
  szOID_INFOSEC_SuiteASignature       = '2.16.840.1.101.2.1.1.13';
  {$EXTERNALSYM szOID_INFOSEC_SuiteASignature}
  szOID_INFOSEC_SuiteAConfidentiality = '2.16.840.1.101.2.1.1.14';
  {$EXTERNALSYM szOID_INFOSEC_SuiteAConfidentiality}
  szOID_INFOSEC_SuiteAIntegrity       = '2.16.840.1.101.2.1.1.15';
  {$EXTERNALSYM szOID_INFOSEC_SuiteAIntegrity}
  szOID_INFOSEC_SuiteATokenProtection = '2.16.840.1.101.2.1.1.16';
  {$EXTERNALSYM szOID_INFOSEC_SuiteATokenProtection}
  szOID_INFOSEC_SuiteAKeyManagement   = '2.16.840.1.101.2.1.1.17';
  {$EXTERNALSYM szOID_INFOSEC_SuiteAKeyManagement}
  szOID_INFOSEC_SuiteAKMandSig        = '2.16.840.1.101.2.1.1.18';
  {$EXTERNALSYM szOID_INFOSEC_SuiteAKMandSig}
  szOID_INFOSEC_mosaicUpdatedSig      = '2.16.840.1.101.2.1.1.19';
  {$EXTERNALSYM szOID_INFOSEC_mosaicUpdatedSig}
  szOID_INFOSEC_mosaicKMandUpdSig     = '2.16.840.1.101.2.1.1.20';
  {$EXTERNALSYM szOID_INFOSEC_mosaicKMandUpdSig}
  szOID_INFOSEC_mosaicUpdatedInteg    = '2.16.840.1.101.2.1.1.21';
  {$EXTERNALSYM szOID_INFOSEC_mosaicUpdatedInteg}

type
  PCRYPT_OBJID_TABLE = ^CRYPT_OBJID_TABLE;
  {$EXTERNALSYM PCRYPT_OBJID_TABLE}
  _CRYPT_OBJID_TABLE = record
    dwAlgId: DWORD;
    pszObjId: LPCSTR;
  end;
  {$EXTERNALSYM _CRYPT_OBJID_TABLE}
  CRYPT_OBJID_TABLE = _CRYPT_OBJID_TABLE;
  {$EXTERNALSYM CRYPT_OBJID_TABLE}
  TCryptObjIdTable = CRYPT_OBJID_TABLE;
  PCryptObjIdTable = PCRYPT_OBJID_TABLE;

//+-------------------------------------------------------------------------
//  PKCS #1 HashInfo (DigestInfo)
//--------------------------------------------------------------------------

  PCRYPT_HASH_INFO = ^CRYPT_HASH_INFO;
  {$EXTERNALSYM PCRYPT_HASH_INFO}
  _CRYPT_HASH_INFO = record
    HashAlgorithm: CRYPT_ALGORITHM_IDENTIFIER;
    Hash: CRYPT_HASH_BLOB;
  end;
  {$EXTERNALSYM _CRYPT_HASH_INFO}
  CRYPT_HASH_INFO = _CRYPT_HASH_INFO;
  {$EXTERNALSYM CRYPT_HASH_INFO}
  TCryptHashInfo = CRYPT_HASH_INFO;
  PCryptHashInfo = PCRYPT_HASH_INFO;

//+-------------------------------------------------------------------------
//  Type used for an extension to an encoded content
//
//  Where the Value's CRYPT_OBJID_BLOB is in its encoded representation.
//--------------------------------------------------------------------------

  PCERT_EXTENSION = ^CERT_EXTENSION;
  {$EXTERNALSYM PCERT_EXTENSION}
  _CERT_EXTENSION = record
    pszObjId: LPSTR;
    fCritical: BOOL;
    Value: CRYPT_OBJID_BLOB;
  end;
  {$EXTERNALSYM _CERT_EXTENSION}
  CERT_EXTENSION = _CERT_EXTENSION;
  {$EXTERNALSYM CERT_EXTENSION}
  TCertExtension = CERT_EXTENSION;
  PCertExtension = PCERT_EXTENSION;

//+-------------------------------------------------------------------------
//  AttributeTypeValue
//
//  Where the Value's CRYPT_OBJID_BLOB is in its encoded representation.
//--------------------------------------------------------------------------

  PCRYPT_ATTRIBUTE_TYPE_VALUE = ^CRYPT_ATTRIBUTE_TYPE_VALUE;
  {$EXTERNALSYM PCRYPT_ATTRIBUTE_TYPE_VALUE}
  _CRYPT_ATTRIBUTE_TYPE_VALUE = record
    pszObjId: LPSTR;
    Value: CRYPT_OBJID_BLOB;
  end;
  {$EXTERNALSYM _CRYPT_ATTRIBUTE_TYPE_VALUE}
  CRYPT_ATTRIBUTE_TYPE_VALUE = _CRYPT_ATTRIBUTE_TYPE_VALUE;
  {$EXTERNALSYM CRYPT_ATTRIBUTE_TYPE_VALUE}
  TCryptAttributeTypeValue = CRYPT_ATTRIBUTE_TYPE_VALUE;
  PCryptAttributeTypeValue = PCRYPT_ATTRIBUTE_TYPE_VALUE;

//+-------------------------------------------------------------------------
//  Attributes
//
//  Where the Value's PATTR_BLOBs are in their encoded representation.
//--------------------------------------------------------------------------

  PCRYPT_ATTRIBUTE = ^CRYPT_ATTRIBUTE;
  {$EXTERNALSYM PCRYPT_ATTRIBUTE}
  _CRYPT_ATTRIBUTE = record
    pszObjId: LPSTR;
    cValue: DWORD;
    rgValue: PCRYPT_ATTR_BLOB;
  end;
  {$EXTERNALSYM _CRYPT_ATTRIBUTE}
  CRYPT_ATTRIBUTE = _CRYPT_ATTRIBUTE;
  {$EXTERNALSYM CRYPT_ATTRIBUTE}
  TCryptAttribute = CRYPT_ATTRIBUTE;
  PCryptAttribute = PCRYPT_ATTRIBUTE;

  PCRYPT_ATTRIBUTES = ^CRYPT_ATTRIBUTES;
  {$EXTERNALSYM PCRYPT_ATTRIBUTES}
  _CRYPT_ATTRIBUTES = record
    cAttr: DWORD;
    rgAttr: PCRYPT_ATTRIBUTE;
  end;
  {$EXTERNALSYM _CRYPT_ATTRIBUTES}
  CRYPT_ATTRIBUTES = _CRYPT_ATTRIBUTES;
  {$EXTERNALSYM CRYPT_ATTRIBUTES}
  TCryptAttributes = CRYPT_ATTRIBUTES;
  PCryptAttributes = PCRYPT_ATTRIBUTES;

//+-------------------------------------------------------------------------
//  Attributes making up a Relative Distinguished Name (CERT_RDN)
//
//  The interpretation of the Value depends on the dwValueType.
//  See below for a list of the types.
//--------------------------------------------------------------------------

  PCERT_RDN_ATTR = ^CERT_RDN_ATTR;
  {$EXTERNALSYM PCERT_RDN_ATTR}
  _CERT_RDN_ATTR = record
    pszObjId: LPSTR;
    dwValueType: DWORD;
    Value: CERT_RDN_VALUE_BLOB;
  end;
  {$EXTERNALSYM _CERT_RDN_ATTR}
  CERT_RDN_ATTR = _CERT_RDN_ATTR;
  {$EXTERNALSYM CERT_RDN_ATTR}
  TCertRdnAttr = CERT_RDN_ATTR;
  PCertRdnAttr = PCERT_RDN_ATTR;

//+-------------------------------------------------------------------------
//  CERT_RDN attribute Object Identifiers
//--------------------------------------------------------------------------

// Labeling attribute types:

const
  szOID_COMMON_NAME          = '2.5.4.3'; // case-ignore string
  {$EXTERNALSYM szOID_COMMON_NAME}
  szOID_SUR_NAME             = '2.5.4.4'; // case-ignore string
  {$EXTERNALSYM szOID_SUR_NAME}
  szOID_DEVICE_SERIAL_NUMBER = '2.5.4.5'; // printable string
  {$EXTERNALSYM szOID_DEVICE_SERIAL_NUMBER}

// Geographic attribute types:

  szOID_COUNTRY_NAME           = '2.5.4.6'; // printable 2char string
  {$EXTERNALSYM szOID_COUNTRY_NAME}
  szOID_LOCALITY_NAME          = '2.5.4.7'; // case-ignore string
  {$EXTERNALSYM szOID_LOCALITY_NAME}
  szOID_STATE_OR_PROVINCE_NAME = '2.5.4.8'; // case-ignore string
  {$EXTERNALSYM szOID_STATE_OR_PROVINCE_NAME}
  szOID_STREET_ADDRESS         = '2.5.4.9'; // case-ignore string
  {$EXTERNALSYM szOID_STREET_ADDRESS}

// Organizational attribute types:

  szOID_ORGANIZATION_NAME        = '2.5.4.10'; // case-ignore string
  {$EXTERNALSYM szOID_ORGANIZATION_NAME}
  szOID_ORGANIZATIONAL_UNIT_NAME = '2.5.4.11'; // case-ignore string
  {$EXTERNALSYM szOID_ORGANIZATIONAL_UNIT_NAME}
  szOID_TITLE                    = '2.5.4.12'; // case-ignore string
  {$EXTERNALSYM szOID_TITLE}

// Explanatory attribute types:

  szOID_DESCRIPTION       = '2.5.4.13'; // case-ignore string
  {$EXTERNALSYM szOID_DESCRIPTION}
  szOID_SEARCH_GUIDE      = '2.5.4.14';
  {$EXTERNALSYM szOID_SEARCH_GUIDE}
  szOID_BUSINESS_CATEGORY = '2.5.4.15'; // case-ignore string
  {$EXTERNALSYM szOID_BUSINESS_CATEGORY}

// Postal addressing attribute types:

  szOID_POSTAL_ADDRESS                = '2.5.4.16';
  {$EXTERNALSYM szOID_POSTAL_ADDRESS}
  szOID_POSTAL_CODE                   = '2.5.4.17'; // case-ignore string
  {$EXTERNALSYM szOID_POSTAL_CODE}
  szOID_POST_OFFICE_BOX               = '2.5.4.18'; // case-ignore string
  {$EXTERNALSYM szOID_POST_OFFICE_BOX}
  szOID_PHYSICAL_DELIVERY_OFFICE_NAME = '2.5.4.19'; // case-ignore string
  {$EXTERNALSYM szOID_PHYSICAL_DELIVERY_OFFICE_NAME}

// Telecommunications addressing attribute types:

  szOID_TELEPHONE_NUMBER             = '2.5.4.20'; // telephone number
  {$EXTERNALSYM szOID_TELEPHONE_NUMBER}
  szOID_TELEX_NUMBER                 = '2.5.4.21';
  {$EXTERNALSYM szOID_TELEX_NUMBER}
  szOID_TELETEXT_TERMINAL_IDENTIFIER = '2.5.4.22';
  {$EXTERNALSYM szOID_TELETEXT_TERMINAL_IDENTIFIER}
  szOID_FACSIMILE_TELEPHONE_NUMBER   = '2.5.4.23';
  {$EXTERNALSYM szOID_FACSIMILE_TELEPHONE_NUMBER}
  szOID_X21_ADDRESS                  = '2.5.4.24'; // numeric string
  {$EXTERNALSYM szOID_X21_ADDRESS}
  szOID_INTERNATIONAL_ISDN_NUMBER    = '2.5.4.25'; // numeric string
  {$EXTERNALSYM szOID_INTERNATIONAL_ISDN_NUMBER}
  szOID_REGISTERED_ADDRESS           = '2.5.4.26';
  {$EXTERNALSYM szOID_REGISTERED_ADDRESS}
  szOID_DESTINATION_INDICATOR        = '2.5.4.27'; // printable string
  {$EXTERNALSYM szOID_DESTINATION_INDICATOR}

// Preference attribute types:

  szOID_PREFERRED_DELIVERY_METHOD = '2.5.4.28';
  {$EXTERNALSYM szOID_PREFERRED_DELIVERY_METHOD}

// OSI application attribute types:

  szOID_PRESENTATION_ADDRESS          = '2.5.4.29';
  {$EXTERNALSYM szOID_PRESENTATION_ADDRESS}
  szOID_SUPPORTED_APPLICATION_CONTEXT = '2.5.4.30';
  {$EXTERNALSYM szOID_SUPPORTED_APPLICATION_CONTEXT}

// Relational application attribute types:

  szOID_MEMBER        = '2.5.4.31';
  {$EXTERNALSYM szOID_MEMBER}
  szOID_OWNER         = '2.5.4.32';
  {$EXTERNALSYM szOID_OWNER}
  szOID_ROLE_OCCUPANT = '2.5.4.33';
  {$EXTERNALSYM szOID_ROLE_OCCUPANT}
  szOID_SEE_ALSO      = '2.5.4.34';
  {$EXTERNALSYM szOID_SEE_ALSO}

// Security attribute types:

  szOID_USER_PASSWORD               = '2.5.4.35';
  {$EXTERNALSYM szOID_USER_PASSWORD}
  szOID_USER_CERTIFICATE            = '2.5.4.36';
  {$EXTERNALSYM szOID_USER_CERTIFICATE}
  szOID_CA_CERTIFICATE              = '2.5.4.37';
  {$EXTERNALSYM szOID_CA_CERTIFICATE}
  szOID_AUTHORITY_REVOCATION_LIST   = '2.5.4.38';
  {$EXTERNALSYM szOID_AUTHORITY_REVOCATION_LIST}
  szOID_CERTIFICATE_REVOCATION_LIST = '2.5.4.39';
  {$EXTERNALSYM szOID_CERTIFICATE_REVOCATION_LIST}
  szOID_CROSS_CERTIFICATE_PAIR      = '2.5.4.40';
  {$EXTERNALSYM szOID_CROSS_CERTIFICATE_PAIR}

// Undocumented attribute types???
//#define szOID_???                         "2.5.4.41"

  szOID_GIVEN_NAME = '2.5.4.42'; // case-ignore string
  {$EXTERNALSYM szOID_GIVEN_NAME}
  szOID_INITIALS   = '2.5.4.43'; // case-ignore string
  {$EXTERNALSYM szOID_INITIALS}

// The DN Qualifier attribute type specifies disambiguating information to add
// to the relative distinguished name of an entry. It is intended to be used
// for entries held in multiple DSAs which would otherwise have the same name,
// and that its value be the same in a given DSA for all entries to which
// the information has been added.

  szOID_DN_QUALIFIER = '2.5.4.46';
  {$EXTERNALSYM szOID_DN_QUALIFIER}

// Pilot user attribute types:

  szOID_DOMAIN_COMPONENT = '0.9.2342.19200300.100.1.25'; // IA5, UTF8 string
  {$EXTERNALSYM szOID_DOMAIN_COMPONENT}

// used for PKCS 12 attributes

  szOID_PKCS_12_FRIENDLY_NAME_ATTR     = '1.2.840.113549.1.9.20';
  {$EXTERNALSYM szOID_PKCS_12_FRIENDLY_NAME_ATTR}
  szOID_PKCS_12_LOCAL_KEY_ID           = '1.2.840.113549.1.9.21';
  {$EXTERNALSYM szOID_PKCS_12_LOCAL_KEY_ID}
  szOID_PKCS_12_KEY_PROVIDER_NAME_ATTR = '1.3.6.1.4.1.311.17.1';
  {$EXTERNALSYM szOID_PKCS_12_KEY_PROVIDER_NAME_ATTR}
  szOID_LOCAL_MACHINE_KEYSET           = '1.3.6.1.4.1.311.17.2';
  {$EXTERNALSYM szOID_LOCAL_MACHINE_KEYSET}

//+-------------------------------------------------------------------------
//  Microsoft CERT_RDN attribute Object Identifiers
//--------------------------------------------------------------------------
// Special RDN containing the KEY_ID. Its value type is CERT_RDN_OCTET_STRING.

  szOID_KEYID_RDN = '1.3.6.1.4.1.311.10.7.1';
  {$EXTERNALSYM szOID_KEYID_RDN}

//+-------------------------------------------------------------------------
//  CERT_RDN Attribute Value Types
//
//  For RDN_ENCODED_BLOB, the Value's CERT_RDN_VALUE_BLOB is in its encoded
//  representation. Otherwise, its an array of bytes.
//
//  For all CERT_RDN types, Value.cbData is always the number of bytes, not
//  necessarily the number of elements in the string. For instance,
//  RDN_UNIVERSAL_STRING is an array of ints (cbData == intCnt * 4) and
//  RDN_BMP_STRING is an array of unsigned shorts (cbData == ushortCnt * 2).
//
//  A RDN_UTF8_STRING is an array of UNICODE characters (cbData == charCnt *2).
//  These UNICODE characters are encoded as UTF8 8 bit characters.
//
//  For CertDecodeName, two 0 bytes are always appended to the end of the
//  string (ensures a CHAR or WCHAR string is null terminated).
//  These added 0 bytes are't included in the BLOB.cbData.
//--------------------------------------------------------------------------

  CERT_RDN_ANY_TYPE         = 0;
  {$EXTERNALSYM CERT_RDN_ANY_TYPE}
  CERT_RDN_ENCODED_BLOB     = 1;
  {$EXTERNALSYM CERT_RDN_ENCODED_BLOB}
  CERT_RDN_OCTET_STRING     = 2;
  {$EXTERNALSYM CERT_RDN_OCTET_STRING}
  CERT_RDN_NUMERIC_STRING   = 3;
  {$EXTERNALSYM CERT_RDN_NUMERIC_STRING}
  CERT_RDN_PRINTABLE_STRING = 4;
  {$EXTERNALSYM CERT_RDN_PRINTABLE_STRING}
  CERT_RDN_TELETEX_STRING   = 5;
  {$EXTERNALSYM CERT_RDN_TELETEX_STRING}
  CERT_RDN_T61_STRING       = 5;
  {$EXTERNALSYM CERT_RDN_T61_STRING}
  CERT_RDN_VIDEOTEX_STRING  = 6;
  {$EXTERNALSYM CERT_RDN_VIDEOTEX_STRING}
  CERT_RDN_IA5_STRING       = 7;
  {$EXTERNALSYM CERT_RDN_IA5_STRING}
  CERT_RDN_GRAPHIC_STRING   = 8;
  {$EXTERNALSYM CERT_RDN_GRAPHIC_STRING}
  CERT_RDN_VISIBLE_STRING   = 9;
  {$EXTERNALSYM CERT_RDN_VISIBLE_STRING}
  CERT_RDN_ISO646_STRING    = 9;
  {$EXTERNALSYM CERT_RDN_ISO646_STRING}
  CERT_RDN_GENERAL_STRING   = 10;
  {$EXTERNALSYM CERT_RDN_GENERAL_STRING}
  CERT_RDN_UNIVERSAL_STRING = 11;
  {$EXTERNALSYM CERT_RDN_UNIVERSAL_STRING}
  CERT_RDN_INT4_STRING      = 11;
  {$EXTERNALSYM CERT_RDN_INT4_STRING}
  CERT_RDN_BMP_STRING       = 12;
  {$EXTERNALSYM CERT_RDN_BMP_STRING}
  CERT_RDN_UNICODE_STRING   = 12;
  {$EXTERNALSYM CERT_RDN_UNICODE_STRING}
  CERT_RDN_UTF8_STRING      = 13;
  {$EXTERNALSYM CERT_RDN_UTF8_STRING}

  CERT_RDN_TYPE_MASK  = $000000FF;
  {$EXTERNALSYM CERT_RDN_TYPE_MASK}
  CERT_RDN_FLAGS_MASK = DWORD($FF000000);
  {$EXTERNALSYM CERT_RDN_FLAGS_MASK}

//+-------------------------------------------------------------------------
//  Flags that can be or'ed with the above Value Type when encoding/decoding
//--------------------------------------------------------------------------
// For encoding: when set, CERT_RDN_T61_STRING is selected instead of
// CERT_RDN_UNICODE_STRING if all the unicode characters are <= 0xFF

  CERT_RDN_ENABLE_T61_UNICODE_FLAG = DWORD($80000000);
  {$EXTERNALSYM CERT_RDN_ENABLE_T61_UNICODE_FLAG}

// For encoding: when set, CERT_RDN_UTF8_STRING is selected instead of
// CERT_RDN_UNICODE_STRING.

  CERT_RDN_ENABLE_UTF8_UNICODE_FLAG = $20000000;
  {$EXTERNALSYM CERT_RDN_ENABLE_UTF8_UNICODE_FLAG}

// For encoding: when set, the characters aren't checked to see if they
// are valid for the Value Type.

  CERT_RDN_DISABLE_CHECK_TYPE_FLAG = $40000000;
  {$EXTERNALSYM CERT_RDN_DISABLE_CHECK_TYPE_FLAG}

// For decoding: by default, CERT_RDN_T61_STRING values are initially decoded
// as UTF8. If the UTF8 decoding fails, then, decoded as 8 bit characters.
// Setting this flag skips the initial attempt to decode as UTF8.

  CERT_RDN_DISABLE_IE4_UTF8_FLAG = $01000000;
  {$EXTERNALSYM CERT_RDN_DISABLE_IE4_UTF8_FLAG}

// Macro to check that the dwValueType is a character string and not an
// encoded blob or octet string

function IS_CERT_RDN_CHAR_STRING(X: DWORD): Boolean;
{$EXTERNALSYM IS_CERT_RDN_CHAR_STRING}

//+-------------------------------------------------------------------------
//  A CERT_RDN consists of an array of the above attributes
//--------------------------------------------------------------------------

type
  PCERT_RDN = ^CERT_RDN;
  {$EXTERNALSYM PCERT_RDN}
  _CERT_RDN = record
    cRDNAttr: DWORD;
    rgRDNAttr: PCERT_RDN_ATTR;
  end;
  {$EXTERNALSYM _CERT_RDN}
  CERT_RDN = _CERT_RDN;
  {$EXTERNALSYM CERT_RDN}
  TCertRdn = CERT_RDN;
  PCertRdn = PCERT_RDN;

//+-------------------------------------------------------------------------
//  Information stored in a subject's or issuer's name. The information
//  is represented as an array of the above RDNs.
//--------------------------------------------------------------------------

  PCERT_NAME_INFO = ^CERT_NAME_INFO;
  {$EXTERNALSYM PCERT_NAME_INFO}
  _CERT_NAME_INFO = record
    cRDN: DWORD;
    rgRDN: PCERT_RDN;
  end;
  {$EXTERNALSYM _CERT_NAME_INFO}
  CERT_NAME_INFO = _CERT_NAME_INFO;
  {$EXTERNALSYM CERT_NAME_INFO}
  TCertNameInfo = CERT_NAME_INFO;
  PCertNameInfo = PCERT_NAME_INFO;

//+-------------------------------------------------------------------------
//  Name attribute value without the Object Identifier
//
//  The interpretation of the Value depends on the dwValueType.
//  See above for a list of the types.
//--------------------------------------------------------------------------

  PCERT_NAME_VALUE = ^CERT_NAME_VALUE;
  {$EXTERNALSYM PCERT_NAME_VALUE}
  _CERT_NAME_VALUE = record
    dwValueType: DWORD;
    Value: CERT_RDN_VALUE_BLOB;
  end;
  {$EXTERNALSYM _CERT_NAME_VALUE}
  CERT_NAME_VALUE = _CERT_NAME_VALUE;
  {$EXTERNALSYM CERT_NAME_VALUE}
  TCertNameValue = CERT_NAME_VALUE;
  PCertNameValue = PCERT_NAME_VALUE;

//+-------------------------------------------------------------------------
//  Public Key Info
//
//  The PublicKey is the encoded representation of the information as it is
//  stored in the bit string
//--------------------------------------------------------------------------

  PCERT_PUBLIC_KEY_INFO = ^CERT_PUBLIC_KEY_INFO;
  {$EXTERNALSYM PCERT_PUBLIC_KEY_INFO}
  _CERT_PUBLIC_KEY_INFO = record
    Algorithm: CRYPT_ALGORITHM_IDENTIFIER;
    PublicKey: CRYPT_BIT_BLOB;
  end;
  {$EXTERNALSYM _CERT_PUBLIC_KEY_INFO}
  CERT_PUBLIC_KEY_INFO = _CERT_PUBLIC_KEY_INFO;
  {$EXTERNALSYM CERT_PUBLIC_KEY_INFO}
  TCertPublicKeyInfo = CERT_PUBLIC_KEY_INFO;
  PCertPublicKeyInfo = PCERT_PUBLIC_KEY_INFO;

const
  CERT_RSA_PUBLIC_KEY_OBJID        = szOID_RSA_RSA;
  {$EXTERNALSYM CERT_RSA_PUBLIC_KEY_OBJID}
  CERT_DEFAULT_OID_PUBLIC_KEY_SIGN = szOID_RSA_RSA;
  {$EXTERNALSYM CERT_DEFAULT_OID_PUBLIC_KEY_SIGN}
  CERT_DEFAULT_OID_PUBLIC_KEY_XCHG = szOID_RSA_RSA;
  {$EXTERNALSYM CERT_DEFAULT_OID_PUBLIC_KEY_XCHG}

//+-------------------------------------------------------------------------
//  structure that contains all the information in a PKCS#8 PrivateKeyInfo
//--------------------------------------------------------------------------

type
  PCRYPT_PRIVATE_KEY_INFO = ^CRYPT_PRIVATE_KEY_INFO;
  {$EXTERNALSYM PCRYPT_PRIVATE_KEY_INFO}
  _CRYPT_PRIVATE_KEY_INFO = record
    Version: DWORD;
    Algorithm: CRYPT_ALGORITHM_IDENTIFIER;
    PrivateKey: CRYPT_DER_BLOB;
    pAttributes: PCRYPT_ATTRIBUTES;
  end;
  {$EXTERNALSYM _CRYPT_PRIVATE_KEY_INFO}
  CRYPT_PRIVATE_KEY_INFO = _CRYPT_PRIVATE_KEY_INFO;
  {$EXTERNALSYM CRYPT_PRIVATE_KEY_INFO}
  TCryptPrivateKeyInfo = CRYPT_PRIVATE_KEY_INFO;
  PCryptPrivateKeyInfo = PCRYPT_PRIVATE_KEY_INFO;

//+-------------------------------------------------------------------------
//  structure that contains all the information in a PKCS#8
//  EncryptedPrivateKeyInfo
//--------------------------------------------------------------------------

  PCRYPT_ENCRYPTED_PRIVATE_KEY_INFO = ^CRYPT_ENCRYPTED_PRIVATE_KEY_INFO;
  {$EXTERNALSYM PCRYPT_ENCRYPTED_PRIVATE_KEY_INFO}
  _CRYPT_ENCRYPTED_PRIVATE_KEY_INFO = record
    EncryptionAlgorithm: CRYPT_ALGORITHM_IDENTIFIER;
    EncryptedPrivateKey: CRYPT_DATA_BLOB;
  end;
  {$EXTERNALSYM _CRYPT_ENCRYPTED_PRIVATE_KEY_INFO}
  CRYPT_ENCRYPTED_PRIVATE_KEY_INFO = _CRYPT_ENCRYPTED_PRIVATE_KEY_INFO;
  {$EXTERNALSYM CRYPT_ENCRYPTED_PRIVATE_KEY_INFO}
  TCryptEncryptedPrivateKeyInfo = CRYPT_ENCRYPTED_PRIVATE_KEY_INFO;
  PCryptEncryptedPrivateKeyInfo = PCRYPT_ENCRYPTED_PRIVATE_KEY_INFO;

//+-------------------------------------------------------------------------
// this callback is given when an EncryptedProvateKeyInfo structure is
// encountered during ImportPKCS8.  the caller is then expected to decrypt
// the private key and hand back the decrypted contents.
//
// the parameters are:
// Algorithm - the algorithm used to encrypt the PrivateKeyInfo
// EncryptedPrivateKey - the encrypted private key blob
// pClearTextKey - a buffer to receive the clear text
// cbClearTextKey - the number of bytes of the pClearTextKey buffer
//                  note the if this is zero then this should be
//                  filled in with the size required to decrypt the
//                  key into, and pClearTextKey should be ignored
// pVoidDecryptFunc - this is the pVoid that was passed into the call
//                    and is preserved and passed back as context
//+-------------------------------------------------------------------------

type
  PCRYPT_DECRYPT_PRIVATE_KEY_FUNC = function (Algorithm: CRYPT_ALGORITHM_IDENTIFIER;
    EncryptedPrivateKey: CRYPT_DATA_BLOB; pbClearTextKey: LPBYTE;
    pcbClearTextKey: LPDWORD; pVoidDecryptFunc: LPVOID): BOOL; stdcall;
  {$EXTERNALSYM PCRYPT_DECRYPT_PRIVATE_KEY_FUNC}
  PCryptDecryptPrivateKeyFunc = PCRYPT_DECRYPT_PRIVATE_KEY_FUNC;

//+-------------------------------------------------------------------------
// this callback is given when creating a PKCS8 EncryptedPrivateKeyInfo.
// The caller is then expected to encrypt the private key and hand back
// the encrypted contents.
//
// the parameters are:
// Algorithm - the algorithm used to encrypt the PrivateKeyInfo
// pClearTextPrivateKey - the cleartext private key to be encrypted
// pbEncryptedKey - the output encrypted private key blob
// cbEncryptedKey - the number of bytes of the pbEncryptedKey buffer
//                  note the if this is zero then this should be
//                  filled in with the size required to encrypt the
//                  key into, and pbEncryptedKey should be ignored
// pVoidEncryptFunc - this is the pVoid that was passed into the call
//                    and is preserved and passed back as context
//+-------------------------------------------------------------------------

type
  PCRYPT_ENCRYPT_PRIVATE_KEY_FUNC = function (pAlgorithm: PCRYPT_ALGORITHM_IDENTIFIER;
    pClearTextPrivateKey: PCRYPT_DATA_BLOB; pbEncryptedKey: LPBYTE;
    pcbEncryptedKey: LPDWORD; pVoidEncryptFunc: LPVOID): BOOL; stdcall;
  {$EXTERNALSYM PCRYPT_ENCRYPT_PRIVATE_KEY_FUNC}
  PCryptEncryptPrivateKeyFunc = PCRYPT_ENCRYPT_PRIVATE_KEY_FUNC;

//+-------------------------------------------------------------------------
// this callback is given from the context of a ImportPKCS8 calls.  the caller
// is then expected to hand back an HCRYPTPROV to receive the key being imported
//
// the parameters are:
// pPrivateKeyInfo - pointer to a CRYPT_PRIVATE_KEY_INFO structure which
//                   describes the key being imported
// EncryptedPrivateKey - the encrypted private key blob
// phCryptProv - a pointer to a HCRRYPTPROV to be filled in
// pVoidResolveFunc - this is the pVoidResolveFunc passed in by the caller in the
//                    CRYPT_PRIVATE_KEY_BLOB_AND_PARAMS struct
//+-------------------------------------------------------------------------

type
  PCRYPT_RESOLVE_HCRYPTPROV_FUNC = function (pPrivateKeyInfo: PCRYPT_PRIVATE_KEY_INFO;
    phCryptProv: PHCRYPTPROV; pVoidResolveFunc: LPVOID): BOOL; stdcall;
  {$EXTERNALSYM PCRYPT_RESOLVE_HCRYPTPROV_FUNC}
  PCryptResolveHCryptProvFunc = PCRYPT_RESOLVE_HCRYPTPROV_FUNC;

//+-------------------------------------------------------------------------
// this struct contains a PKCS8 private key and two pointers to callback
// functions, with a corresponding pVoids.  the first callback is used to give
// the caller the opportunity to specify where the key is imported to.  the callback
// passes the caller the algoroithm OID and key size to use in making the decision.
// the other callback is used to decrypt the private key if the PKCS8 contains an
// EncryptedPrivateKeyInfo.  both pVoids are preserved and passed back to the caller
// in the respective callback
//+-------------------------------------------------------------------------

  PCRYPT_PKCS8_IMPORT_PARAMS = ^CRYPT_PKCS8_IMPORT_PARAMS;
  {$EXTERNALSYM PCRYPT_PKCS8_IMPORT_PARAMS}
  _CRYPT_PKCS8_IMPORT_PARAMS = record
    PrivateKey: CRYPT_DIGEST_BLOB; // PKCS8 blob
    pResolvehCryptProvFunc: PCRYPT_RESOLVE_HCRYPTPROV_FUNC; // optional
    pVoidResolveFunc: LPVOID; // optional
    pDecryptPrivateKeyFunc: PCRYPT_DECRYPT_PRIVATE_KEY_FUNC;
    pVoidDecryptFunc: LPVOID;
  end;
  {$EXTERNALSYM _CRYPT_PKCS8_IMPORT_PARAMS}
  CRYPT_PKCS8_IMPORT_PARAMS = _CRYPT_PKCS8_IMPORT_PARAMS;
  {$EXTERNALSYM CRYPT_PKCS8_IMPORT_PARAMS}
  TCryptPkcs8ImportParams = CRYPT_PKCS8_IMPORT_PARAMS;
  PCryptPkcs8ImportParams = PCRYPT_PKCS8_IMPORT_PARAMS;

  CRYPT_PRIVATE_KEY_BLOB_AND_PARAMS = CRYPT_PKCS8_IMPORT_PARAMS;
  {$EXTERNALSYM CRYPT_PRIVATE_KEY_BLOB_AND_PARAMS}
  PCRYPT_PRIVATE_KEY_BLOB_AND_PARAMS = PCRYPT_PKCS8_IMPORT_PARAMS;
  {$EXTERNALSYM PCRYPT_PRIVATE_KEY_BLOB_AND_PARAMS}

//+-------------------------------------------------------------------------
// this struct contains information identifying a private key and a pointer
// to a callback function, with a corresponding pVoid. The callback is used
// to encrypt the private key. If the pEncryptPrivateKeyFunc is NULL, the
// key will not be encrypted and an EncryptedPrivateKeyInfo will not be generated.
// The pVoid is preserved and passed back to the caller in the respective callback
//+-------------------------------------------------------------------------

  PCRYPT_PKCS8_EXPORT_PARAMS = ^CRYPT_PKCS8_EXPORT_PARAMS;
  {$EXTERNALSYM PCRYPT_PKCS8_EXPORT_PARAMS}
  _CRYPT_PKCS8_EXPORT_PARAMS = record
    hCryptProv: HCRYPTPROV;
    dwKeySpec: DWORD;
    pszPrivateKeyObjId: LPSTR;
    pEncryptPrivateKeyFunc: PCRYPT_ENCRYPT_PRIVATE_KEY_FUNC;
    pVoidEncryptFunc: LPVOID;
  end;
  {$EXTERNALSYM _CRYPT_PKCS8_EXPORT_PARAMS}
  CRYPT_PKCS8_EXPORT_PARAMS = _CRYPT_PKCS8_EXPORT_PARAMS;
  {$EXTERNALSYM CRYPT_PKCS8_EXPORT_PARAMS}
  TCryptPkcs8ExportParams = CRYPT_PKCS8_EXPORT_PARAMS;
  PCryptPkcs8ExportParams = PCRYPT_PKCS8_EXPORT_PARAMS;

//+-------------------------------------------------------------------------
//  Information stored in a certificate
//
//  The Issuer, Subject, Algorithm, PublicKey and Extension BLOBs are the
//  encoded representation of the information.
//--------------------------------------------------------------------------

  PCERT_INFO = ^CERT_INFO;
  {$EXTERNALSYM PCERT_INFO}
  _CERT_INFO = record
    dwVersion: DWORD;
    SerialNumber: CRYPT_INTEGER_BLOB;
    SignatureAlgorithm: CRYPT_ALGORITHM_IDENTIFIER;
    Issuer: CERT_NAME_BLOB;
    NotBefore: FILETIME;
    NotAfter: FILETIME;
    Subject: CERT_NAME_BLOB;
    SubjectPublicKeyInfo: CERT_PUBLIC_KEY_INFO;
    IssuerUniqueId: CRYPT_BIT_BLOB;
    SubjectUniqueId: CRYPT_BIT_BLOB;
    cExtension: DWORD;
    rgExtension: PCERT_EXTENSION;
  end;
  {$EXTERNALSYM _CERT_INFO}
  CERT_INFO = _CERT_INFO;
  {$EXTERNALSYM CERT_INFO}
  TCertInfo = CERT_INFO;
  PCertInfo = PCERT_INFO;

//+-------------------------------------------------------------------------
//  Certificate versions
//--------------------------------------------------------------------------

const
  CERT_V1 = 0;
  {$EXTERNALSYM CERT_V1}
  CERT_V2 = 1;
  {$EXTERNALSYM CERT_V2}
  CERT_V3 = 2;
  {$EXTERNALSYM CERT_V3}

//+-------------------------------------------------------------------------
//  Certificate Information Flags
//--------------------------------------------------------------------------

  CERT_INFO_VERSION_FLAG                 = 1;
  {$EXTERNALSYM CERT_INFO_VERSION_FLAG}
  CERT_INFO_SERIAL_NUMBER_FLAG           = 2;
  {$EXTERNALSYM CERT_INFO_SERIAL_NUMBER_FLAG}
  CERT_INFO_SIGNATURE_ALGORITHM_FLAG     = 3;
  {$EXTERNALSYM CERT_INFO_SIGNATURE_ALGORITHM_FLAG}
  CERT_INFO_ISSUER_FLAG                  = 4;
  {$EXTERNALSYM CERT_INFO_ISSUER_FLAG}
  CERT_INFO_NOT_BEFORE_FLAG              = 5;
  {$EXTERNALSYM CERT_INFO_NOT_BEFORE_FLAG}
  CERT_INFO_NOT_AFTER_FLAG               = 6;
  {$EXTERNALSYM CERT_INFO_NOT_AFTER_FLAG}
  CERT_INFO_SUBJECT_FLAG                 = 7;
  {$EXTERNALSYM CERT_INFO_SUBJECT_FLAG}
  CERT_INFO_SUBJECT_PUBLIC_KEY_INFO_FLAG = 8;
  {$EXTERNALSYM CERT_INFO_SUBJECT_PUBLIC_KEY_INFO_FLAG}
  CERT_INFO_ISSUER_UNIQUE_ID_FLAG        = 9;
  {$EXTERNALSYM CERT_INFO_ISSUER_UNIQUE_ID_FLAG}
  CERT_INFO_SUBJECT_UNIQUE_ID_FLAG       = 10;
  {$EXTERNALSYM CERT_INFO_SUBJECT_UNIQUE_ID_FLAG}
  CERT_INFO_EXTENSION_FLAG               = 11;
  {$EXTERNALSYM CERT_INFO_EXTENSION_FLAG}

//+-------------------------------------------------------------------------
//  An entry in a CRL
//
//  The Extension BLOBs are the encoded representation of the information.
//--------------------------------------------------------------------------

type
  PCRL_ENTRY = ^CRL_ENTRY;
  {$EXTERNALSYM PCRL_ENTRY}
  _CRL_ENTRY = record
    SerialNumber: CRYPT_INTEGER_BLOB;
    RevocationDate: FILETIME;
    cExtension: DWORD;
    rgExtension: PCERT_EXTENSION;
  end;
  {$EXTERNALSYM _CRL_ENTRY}
  CRL_ENTRY = _CRL_ENTRY;
  {$EXTERNALSYM CRL_ENTRY}
  TCrlEntry = CRL_ENTRY;
  PCrlEntry = PCRL_ENTRY;

//+-------------------------------------------------------------------------
//  Information stored in a CRL
//
//  The Issuer, Algorithm and Extension BLOBs are the encoded
//  representation of the information.
//--------------------------------------------------------------------------

  PCRL_INFO = ^CRL_INFO;
  {$EXTERNALSYM PCRL_INFO}
  _CRL_INFO = record
    dwVersion: DWORD;
    SignatureAlgorithm: CRYPT_ALGORITHM_IDENTIFIER;
    Issuer: CERT_NAME_BLOB;
    ThisUpdate: FILETIME;
    NextUpdate: FILETIME;
    cCRLEntry: DWORD;
    rgCRLEntry: PCRL_ENTRY;
    cExtension: DWORD;
    rgExtension: PCERT_EXTENSION;
  end;
  {$EXTERNALSYM _CRL_INFO}
  CRL_INFO = _CRL_INFO;
  {$EXTERNALSYM CRL_INFO}
  TCrlInfo = CRL_INFO;
  PCrlInfo = PCRL_INFO;

//+-------------------------------------------------------------------------
//  CRL versions
//--------------------------------------------------------------------------

const
  CRL_V1 = 0;
  {$EXTERNALSYM CRL_V1}
  CRL_V2 = 1;
  {$EXTERNALSYM CRL_V2}

//+-------------------------------------------------------------------------
//  Information stored in a certificate request
//
//  The Subject, Algorithm, PublicKey and Attribute BLOBs are the encoded
//  representation of the information.
//--------------------------------------------------------------------------

type
  PCERT_REQUEST_INFO = ^CERT_REQUEST_INFO;
  {$EXTERNALSYM PCERT_REQUEST_INFO}
  _CERT_REQUEST_INFO = record
    dwVersion: DWORD;
    Subject: CERT_NAME_BLOB;
    SubjectPublicKeyInfo: CERT_PUBLIC_KEY_INFO;
    cAttribute: DWORD;
    rgAttribute: PCRYPT_ATTRIBUTE;
  end;
  {$EXTERNALSYM _CERT_REQUEST_INFO}
  CERT_REQUEST_INFO = _CERT_REQUEST_INFO;
  {$EXTERNALSYM CERT_REQUEST_INFO}
  TCertRequestInfo = CERT_REQUEST_INFO;
  PCertRequestInfo = PCERT_REQUEST_INFO;

//+-------------------------------------------------------------------------
//  Certificate Request versions
//--------------------------------------------------------------------------

const
  CERT_REQUEST_V1 = 0;
  {$EXTERNALSYM CERT_REQUEST_V1}

//+-------------------------------------------------------------------------
//  Information stored in Netscape's Keygen request
//--------------------------------------------------------------------------

type
  PCERT_KEYGEN_REQUEST_INFO = ^CERT_KEYGEN_REQUEST_INFO;
  {$EXTERNALSYM PCERT_KEYGEN_REQUEST_INFO}
  _CERT_KEYGEN_REQUEST_INFO = record
    dwVersion: DWORD;
    SubjectPublicKeyInfo: CERT_PUBLIC_KEY_INFO;
    pwszChallengeString: LPWSTR; // encoded as IA5
  end;
  {$EXTERNALSYM _CERT_KEYGEN_REQUEST_INFO}
  CERT_KEYGEN_REQUEST_INFO = _CERT_KEYGEN_REQUEST_INFO;
  {$EXTERNALSYM CERT_KEYGEN_REQUEST_INFO}
  TCertKeygenRequestInfo = CERT_KEYGEN_REQUEST_INFO;
  PCertKeygenRequestInfo = PCERT_KEYGEN_REQUEST_INFO;

const
  CERT_KEYGEN_REQUEST_V1 = 0;
  {$EXTERNALSYM CERT_KEYGEN_REQUEST_V1}

//+-------------------------------------------------------------------------
//  Certificate, CRL, Certificate Request or Keygen Request Signed Content
//
//  The "to be signed" encoded content plus its signature. The ToBeSigned
//  is the encoded CERT_INFO, CRL_INFO, CERT_REQUEST_INFO or
//  CERT_KEYGEN_REQUEST_INFO.
//--------------------------------------------------------------------------

type
  PCERT_SIGNED_CONTENT_INFO = ^CERT_SIGNED_CONTENT_INFO;
  {$EXTERNALSYM PCERT_SIGNED_CONTENT_INFO}
  _CERT_SIGNED_CONTENT_INFO = record
    ToBeSigned: CRYPT_DER_BLOB;
    SignatureAlgorithm: CRYPT_ALGORITHM_IDENTIFIER;
    Signature: CRYPT_BIT_BLOB;
  end;
  {$EXTERNALSYM _CERT_SIGNED_CONTENT_INFO}
  CERT_SIGNED_CONTENT_INFO = _CERT_SIGNED_CONTENT_INFO;
  {$EXTERNALSYM CERT_SIGNED_CONTENT_INFO}
  TCertSignedContentInfo = CERT_SIGNED_CONTENT_INFO;
  PCertSignedContentInfo = PCERT_SIGNED_CONTENT_INFO;

//+-------------------------------------------------------------------------
//  Certificate Trust List (CTL)
//--------------------------------------------------------------------------

//+-------------------------------------------------------------------------
//  CTL Usage. Also used for EnhancedKeyUsage extension.
//--------------------------------------------------------------------------

  PCTL_USAGE = ^CTL_USAGE;
  {$EXTERNALSYM PCTL_USAGE}
  _CTL_USAGE = record
    cUsageIdentifier: DWORD;
    rgpszUsageIdentifier: LPSTR; // array of pszObjId
  end;
  {$EXTERNALSYM _CTL_USAGE}
  CTL_USAGE = _CTL_USAGE;
  {$EXTERNALSYM CTL_USAGE}
  TCtlUsage = CTL_USAGE;
  PCtlUsage = PCTL_USAGE;

  CERT_ENHKEY_USAGE = CTL_USAGE;
  {$EXTERNALSYM CERT_ENHKEY_USAGE}
  PCERT_ENHKEY_USAGE = PCTL_USAGE;
  {$EXTERNALSYM PCERT_ENHKEY_USAGE}

//+-------------------------------------------------------------------------
//  An entry in a CTL
//--------------------------------------------------------------------------

  PCTL_ENTRY = ^CTL_ENTRY;
  {$EXTERNALSYM PCTL_ENTRY}
  _CTL_ENTRY = record
    SubjectIdentifier: CRYPT_DATA_BLOB; // For example, its hash
    cAttribute: DWORD;
    rgAttribute: PCRYPT_ATTRIBUTE; // OPTIONAL
  end;
  {$EXTERNALSYM _CTL_ENTRY}
  CTL_ENTRY = _CTL_ENTRY;
  {$EXTERNALSYM CTL_ENTRY}
  TCtlEntry = CTL_ENTRY;
  PCtlEntry = PCTL_ENTRY;

//+-------------------------------------------------------------------------
//  Information stored in a CTL
//--------------------------------------------------------------------------

  PCTL_INFO = ^CTL_INFO;
  {$EXTERNALSYM PCTL_INFO}
  _CTL_INFO = record
    dwVersion: DWORD;
    SubjectUsage: CTL_USAGE;
    ListIdentifier: CRYPT_DATA_BLOB; // OPTIONAL
    SequenceNumber: CRYPT_INTEGER_BLOB; // OPTIONAL
    ThisUpdate: FILETIME;
    NextUpdate: FILETIME; // OPTIONAL
    SubjectAlgorithm: CRYPT_ALGORITHM_IDENTIFIER;
    cCTLEntry: DWORD;
    rgCTLEntry: PCTL_ENTRY; // OPTIONAL
    cExtension: DWORD;
    rgExtension: PCERT_EXTENSION; // OPTIONAL
  end;
  {$EXTERNALSYM _CTL_INFO}
  CTL_INFO = _CTL_INFO;
  {$EXTERNALSYM CTL_INFO}
  TCtlInfo = CTL_INFO;
  PCtlInfo = PCTL_INFO;

//+-------------------------------------------------------------------------
//  CTL versions
//--------------------------------------------------------------------------

const
  CTL_V1 = 0;
  {$EXTERNALSYM CTL_V1}

//+-------------------------------------------------------------------------
//  TimeStamp Request
//
//  The pszTimeStamp is the OID for the Time type requested
//  The pszContentType is the Content Type OID for the content, usually DATA
//  The Content is a un-decoded blob
//--------------------------------------------------------------------------

type
  PCRYPT_TIME_STAMP_REQUEST_INFO = ^CRYPT_TIME_STAMP_REQUEST_INFO;
  {$EXTERNALSYM PCRYPT_TIME_STAMP_REQUEST_INFO}
  _CRYPT_TIME_STAMP_REQUEST_INFO = record
    pszTimeStampAlgorithm: LPSTR; // pszObjId
    pszContentType: LPSTR; // pszObjId
    Content: CRYPT_OBJID_BLOB;
    cAttribute: DWORD;
    rgAttribute: PCRYPT_ATTRIBUTE;
  end;
  {$EXTERNALSYM _CRYPT_TIME_STAMP_REQUEST_INFO}
  CRYPT_TIME_STAMP_REQUEST_INFO = _CRYPT_TIME_STAMP_REQUEST_INFO;
  {$EXTERNALSYM CRYPT_TIME_STAMP_REQUEST_INFO}
  TCryptTimeStampRequestInfo = CRYPT_TIME_STAMP_REQUEST_INFO;
  PCryptTimeStampRequestInfo = PCRYPT_TIME_STAMP_REQUEST_INFO;

//+-------------------------------------------------------------------------
//  Name Value Attribute
//--------------------------------------------------------------------------

  PCRYPT_ENROLLMENT_NAME_VALUE_PAIR = ^CRYPT_ENROLLMENT_NAME_VALUE_PAIR;
  {$EXTERNALSYM PCRYPT_ENROLLMENT_NAME_VALUE_PAIR}
  _CRYPT_ENROLLMENT_NAME_VALUE_PAIR = record
    pwszName: LPWSTR;
    pwszValue: LPWSTR;
  end;
  {$EXTERNALSYM _CRYPT_ENROLLMENT_NAME_VALUE_PAIR}
  CRYPT_ENROLLMENT_NAME_VALUE_PAIR = _CRYPT_ENROLLMENT_NAME_VALUE_PAIR;
  {$EXTERNALSYM CRYPT_ENROLLMENT_NAME_VALUE_PAIR}
  TCryptEnrollmentNameValuePair = CRYPT_ENROLLMENT_NAME_VALUE_PAIR;
  PCryptEnrollmentNameValuePair = PCRYPT_ENROLLMENT_NAME_VALUE_PAIR;

//+-------------------------------------------------------------------------
//  CSP Provider
//--------------------------------------------------------------------------

  PCRYPT_CSP_PROVIDER = ^CRYPT_CSP_PROVIDER;
  {$EXTERNALSYM PCRYPT_CSP_PROVIDER}
  _CRYPT_CSP_PROVIDER = record
    dwKeySpec: DWORD;
    pwszProviderName: LPWSTR;
    Signature: CRYPT_BIT_BLOB;
  end;
  {$EXTERNALSYM _CRYPT_CSP_PROVIDER}
  CRYPT_CSP_PROVIDER = _CRYPT_CSP_PROVIDER;
  {$EXTERNALSYM CRYPT_CSP_PROVIDER}
  TCryptCspProvider = CRYPT_CSP_PROVIDER;
  PCryptCspProvider = PCRYPT_CSP_PROVIDER;

//+-------------------------------------------------------------------------
//  Certificate and Message encoding types
//
//  The encoding type is a DWORD containing both the certificate and message
//  encoding types. The certificate encoding type is stored in the LOWORD.
//  The message encoding type is stored in the HIWORD. Some functions or
//  structure fields require only one of the encoding types. The following
//  naming convention is used to indicate which encoding type(s) are
//  required:
//      dwEncodingType              (both encoding types are required)
//      dwMsgAndCertEncodingType    (both encoding types are required)
//      dwMsgEncodingType           (only msg encoding type is required)
//      dwCertEncodingType          (only cert encoding type is required)
//
//  Its always acceptable to specify both.
//--------------------------------------------------------------------------

const
  CERT_ENCODING_TYPE_MASK = $0000FFFF;
  {$EXTERNALSYM CERT_ENCODING_TYPE_MASK}
  CMSG_ENCODING_TYPE_MASK = DWORD($FFFF0000);
  {$EXTERNALSYM CMSG_ENCODING_TYPE_MASK}

function GET_CERT_ENCODING_TYPE(X: DWORD): DWORD;
{$EXTERNALSYM GET_CERT_ENCODING_TYPE}

function GET_CMSG_ENCODING_TYPE(X: DWORD): DWORD;
{$EXTERNALSYM GET_CMSG_ENCODING_TYPE}

const
  CRYPT_ASN_ENCODING  = $00000001;
  {$EXTERNALSYM CRYPT_ASN_ENCODING}
  CRYPT_NDR_ENCODING  = $00000002;
  {$EXTERNALSYM CRYPT_NDR_ENCODING}
  X509_ASN_ENCODING   = $00000001;
  {$EXTERNALSYM X509_ASN_ENCODING}
  X509_NDR_ENCODING   = $00000002;
  {$EXTERNALSYM X509_NDR_ENCODING}
  PKCS_7_ASN_ENCODING = $00010000;
  {$EXTERNALSYM PKCS_7_ASN_ENCODING}
  PKCS_7_NDR_ENCODING = $00020000;
  {$EXTERNALSYM PKCS_7_NDR_ENCODING}

//+-------------------------------------------------------------------------
//  format the specified data structure according to the certificate
//  encoding type.
//
//  The default behavior of CryptFormatObject is to return single line
//  display of the encoded data, that is, each subfield will be concatenated with
//  a ", " on one line.  If user prefers to display the data in multiple line,
//  set the flag CRYPT_FORMAT_STR_MULTI_LINE, that is, each subfield will be displayed
//  on a seperate line.
//
//  If there is no formatting routine installed or registered
//  for the lpszStructType, the hex dump of the encoded BLOB will be returned.
//  User can set the flag CRYPT_FORMAT_STR_NO_HEX to disable the hex dump.
//--------------------------------------------------------------------------

function CryptFormatObject(dwCertEncodingType, dwFormatType, dwFormatStrType: DWORD;
  pFormatStruct: Pointer; lpszStructType: LPCSTR; pbEncoded: LPBYTE;
    cbEncoded: DWORD; pbFormat: Pointer; var pcbFormat: DWORD): BOOL; stdcall;
{$EXTERNALSYM CryptFormatObject}

//-------------------------------------------------------------------------
// constants for dwFormatStrType of function CryptFormatObject
//-------------------------------------------------------------------------

const
  CRYPT_FORMAT_STR_MULTI_LINE = $0001;
  {$EXTERNALSYM CRYPT_FORMAT_STR_MULTI_LINE}
  CRYPT_FORMAT_STR_NO_HEX     = $0010;
  {$EXTERNALSYM CRYPT_FORMAT_STR_NO_HEX}

//-------------------------------------------------------------------------
// constants for dwFormatType of function CryptFormatObject
// when format X509_NAME or X509_UNICODE_NAME
//-------------------------------------------------------------------------
// Just get the simple string

  CRYPT_FORMAT_SIMPLE = $0001;
  {$EXTERNALSYM CRYPT_FORMAT_SIMPLE}

//Put an attribute name infront of the attribute
//such as "O=Microsoft,DN=xiaohs"

  CRYPT_FORMAT_X509 = $0002;
  {$EXTERNALSYM CRYPT_FORMAT_X509}

//Put an OID infront of the simple string, such as
//"2.5.4.22=Microsoft,2.5.4.3=xiaohs"

  CRYPT_FORMAT_OID = $0004;
  {$EXTERNALSYM CRYPT_FORMAT_OID}

//Put a ";" between each RDN.  The default is ","

  CRYPT_FORMAT_RDN_SEMICOLON = $0100;
  {$EXTERNALSYM CRYPT_FORMAT_RDN_SEMICOLON}

//Put a "\n" between each RDN.

  CRYPT_FORMAT_RDN_CRLF = $0200;
  {$EXTERNALSYM CRYPT_FORMAT_RDN_CRLF}

//Unquote the DN value, which is quoated by default va the following
//rules: if the DN contains leading or trailing
//white space or one of the following characters: ",", "+", "=",
//""", "\n",  "<", ">", "#" or ";". The quoting character is ".
//If the DN Value contains a " it is double quoted ("").

  CRYPT_FORMAT_RDN_UNQUOTE = $0400;
  {$EXTERNALSYM CRYPT_FORMAT_RDN_UNQUOTE}

//reverse the order of the RDNs before converting to the string

  CRYPT_FORMAT_RDN_REVERSE = $0800;
  {$EXTERNALSYM CRYPT_FORMAT_RDN_REVERSE}

//-------------------------------------------------------------------------
//  contants dwFormatType of function CryptFormatObject when format a DN.:
//
//  The following three values are defined in the section above:
//  CRYPT_FORMAT_SIMPLE:    Just a simple string
//                          such as  "Microsoft+xiaohs+NT"
//  CRYPT_FORMAT_X509       Put an attribute name infront of the attribute
//                          such as "O=Microsoft+xiaohs+NT"
//
//  CRYPT_FORMAT_OID        Put an OID infront of the simple string,
//                          such as "2.5.4.22=Microsoft+xiaohs+NT"
//
//  Additional values are defined as following:
//----------------------------------------------------------------------------
//Put a "," between each value.  Default is "+"

  CRYPT_FORMAT_COMMA = $1000;
  {$EXTERNALSYM CRYPT_FORMAT_COMMA}

//Put a ";" between each value

  CRYPT_FORMAT_SEMICOLON = CRYPT_FORMAT_RDN_SEMICOLON;
  {$EXTERNALSYM CRYPT_FORMAT_SEMICOLON}

//Put a "\n" between each value

  CRYPT_FORMAT_CRLF = CRYPT_FORMAT_RDN_CRLF;
  {$EXTERNALSYM CRYPT_FORMAT_CRLF}

//+-------------------------------------------------------------------------
//  Encode / decode the specified data structure according to the certificate
//  encoding type.
//
//  See below for a list of the predefined data structures.
//--------------------------------------------------------------------------

type
  PFN_CRYPT_ALLOC = function (cbSize: size_t): LPVOID; stdcall;
  {$EXTERNALSYM PFN_CRYPT_ALLOC}

  PFN_CRYPT_FREE = procedure (pv: LPVOID); stdcall;
  {$EXTERNALSYM PFN_CRYPT_FREE}

  PCRYPT_ENCODE_PARA = ^CRYPT_ENCODE_PARA;
  {$EXTERNALSYM PCRYPT_ENCODE_PARA}
  _CRYPT_ENCODE_PARA = record
    cbSize: DWORD;
    pfnAlloc: PFN_CRYPT_ALLOC; // OPTIONAL
    pfnFree: PFN_CRYPT_FREE; // OPTIONAL
  end;
  {$EXTERNALSYM _CRYPT_ENCODE_PARA}
  CRYPT_ENCODE_PARA = _CRYPT_ENCODE_PARA;
  {$EXTERNALSYM CRYPT_ENCODE_PARA}
  TCryptEncodePara = CRYPT_ENCODE_PARA;
  PCryptEncodePara = PCRYPT_ENCODE_PARA;

function CryptEncodeObjectEx(dwCertEncodingType: DWORD; lpszStructType: LPCSTR;
  pvStructInfo: Pointer; dwFlags: DWORD; pEncodePara: PCRYPT_ENCODE_PARA;
  pvEncoded: Pointer; var pcbEncoded: DWORD): BOOL; stdcall;
{$EXTERNALSYM CryptEncodeObjectEx}

function CryptEncodeObject(dwCertEncodingType: DWORD; lpszStructType: LPCSTR;
  pvStructInfo: Pointer; pbEncoded: LPBYTE; var pcbEncoded: DWORD): BOOL; stdcall;
{$EXTERNALSYM CryptEncodeObject}

// By default the signature bytes are reversed. The following flag can
// be set to inhibit the byte reversal.
//
// This flag is applicable to
//      X509_CERT_TO_BE_SIGNED

const
  CRYPT_ENCODE_NO_SIGNATURE_BYTE_REVERSAL_FLAG = $8;
  {$EXTERNALSYM CRYPT_ENCODE_NO_SIGNATURE_BYTE_REVERSAL_FLAG}

//  When the following flag is set the called encode function allocates
//  memory for the encoded bytes. A pointer to the allocated bytes
//  is returned in pvEncoded. If pEncodePara or pEncodePara->pfnAlloc is
//  NULL, then, LocalAlloc is called for the allocation and LocalFree must
//  be called to do the free. Otherwise, pEncodePara->pfnAlloc is called
//  for the allocation.
//
//  *pcbEncoded is ignored on input and updated with the length of the
//  allocated, encoded bytes.
//
//  If pfnAlloc is set, then, pfnFree should also be set.

  CRYPT_ENCODE_ALLOC_FLAG = $8000;
  {$EXTERNALSYM CRYPT_ENCODE_ALLOC_FLAG}

//  The following flag is applicable when encoding X509_UNICODE_NAME.
//  When set, CERT_RDN_T61_STRING is selected instead of
//  CERT_RDN_UNICODE_STRING if all the unicode characters are <= 0xFF

  CRYPT_UNICODE_NAME_ENCODE_ENABLE_T61_UNICODE_FLAG = CERT_RDN_ENABLE_T61_UNICODE_FLAG;
  {$EXTERNALSYM CRYPT_UNICODE_NAME_ENCODE_ENABLE_T61_UNICODE_FLAG}

//  The following flag is applicable when encoding X509_UNICODE_NAME.
//  When set, CERT_RDN_UTF8_STRING is selected instead of
//  CERT_RDN_UNICODE_STRING.

  CRYPT_UNICODE_NAME_ENCODE_ENABLE_UTF8_UNICODE_FLAG = CERT_RDN_ENABLE_UTF8_UNICODE_FLAG;
  {$EXTERNALSYM CRYPT_UNICODE_NAME_ENCODE_ENABLE_UTF8_UNICODE_FLAG}

//  The following flag is applicable when encoding X509_UNICODE_NAME,
//  X509_UNICODE_NAME_VALUE or X509_UNICODE_ANY_STRING.
//  When set, the characters aren't checked to see if they
//  are valid for the specified Value Type.

  CRYPT_UNICODE_NAME_ENCODE_DISABLE_CHECK_TYPE_FLAG = CERT_RDN_DISABLE_CHECK_TYPE_FLAG;
  {$EXTERNALSYM CRYPT_UNICODE_NAME_ENCODE_DISABLE_CHECK_TYPE_FLAG}

//  The following flag is applicable when encoding the PKCS_SORTED_CTL. This
//  flag should be set if the identifier for the TrustedSubjects is a hash,
//  such as, MD5 or SHA1.

  CRYPT_SORTED_CTL_ENCODE_HASHED_SUBJECT_IDENTIFIER_FLAG = $10000;
  {$EXTERNALSYM CRYPT_SORTED_CTL_ENCODE_HASHED_SUBJECT_IDENTIFIER_FLAG}

type
  PCRYPT_DECODE_PARA = ^CRYPT_DECODE_PARA;
  {$EXTERNALSYM PCRYPT_DECODE_PARA}
  _CRYPT_DECODE_PARA = record
    cbSize: DWORD;
    pfnAlloc: PFN_CRYPT_ALLOC; // OPTIONAL
    pfnFree: PFN_CRYPT_FREE;   // OPTIONAL
  end;
  {$EXTERNALSYM _CRYPT_DECODE_PARA}
  CRYPT_DECODE_PARA = _CRYPT_DECODE_PARA;
  {$EXTERNALSYM CRYPT_DECODE_PARA}
  TCryptDecodePara = CRYPT_DECODE_PARA;
  PCryptDecodePara = PCRYPT_DECODE_PARA;

function CryptDecodeObjectEx(dwCertEncodingType: DWORD; lpszStructType: LPCSTR;
  pbEncoded: Pointer; cbEncoded, dwFlags: DWORD; pDecodePara: PCRYPT_DECODE_PARA;
  pvStructInfo: Pointer; var pcbStructInfo: DWORD): BOOL; stdcall;
{$EXTERNALSYM CryptDecodeObjectEx}

function CryptDecodeObject(dwCertEncodingType: DWORD; lpszStructType: LPCSTR;
  pbEncoded: LPBYTE; cbEncoded, dwFlags: DWORD; pvStructInfo: Pointer;
  var pcbStructInfo: DWORD): BOOL; stdcall;
{$EXTERNALSYM CryptDecodeObject}

// When the following flag is set the nocopy optimization is enabled.
// This optimization where appropriate, updates the pvStructInfo fields
// to point to content residing within pbEncoded instead of making a copy
// of and appending to pvStructInfo.
//
// Note, when set, pbEncoded can't be freed until pvStructInfo is freed.

const
  CRYPT_DECODE_NOCOPY_FLAG = $1;
  {$EXTERNALSYM CRYPT_DECODE_NOCOPY_FLAG}

// For CryptDecodeObject(), by default the pbEncoded is the "to be signed"
// plus its signature. Set the following flag, if pbEncoded points to only
// the "to be signed".
//
// This flag is applicable to
//      X509_CERT_TO_BE_SIGNED
//      X509_CERT_CRL_TO_BE_SIGNED
//      X509_CERT_REQUEST_TO_BE_SIGNED
//      X509_KEYGEN_REQUEST_TO_BE_SIGNED

  CRYPT_DECODE_TO_BE_SIGNED_FLAG = $2;
  {$EXTERNALSYM CRYPT_DECODE_TO_BE_SIGNED_FLAG}

// When the following flag is set, the OID strings are allocated in
// crypt32.dll and shared instead of being copied into the returned
// data structure. This flag may be set if crypt32.dll isn't unloaded
// before the caller is unloaded.

  CRYPT_DECODE_SHARE_OID_STRING_FLAG = $4;
  {$EXTERNALSYM CRYPT_DECODE_SHARE_OID_STRING_FLAG}

// By default the signature bytes are reversed. The following flag can
// be set to inhibit the byte reversal.
//
// This flag is applicable to
//      X509_CERT_TO_BE_SIGNED

  CRYPT_DECODE_NO_SIGNATURE_BYTE_REVERSAL_FLAG = $8;
  {$EXTERNALSYM CRYPT_DECODE_NO_SIGNATURE_BYTE_REVERSAL_FLAG}

// When the following flag is set the called decode function allocates
// memory for the decoded structure. A pointer to the allocated structure
// is returned in pvStructInfo. If pDecodePara or pDecodePara->pfnAlloc is
// NULL, then, LocalAlloc is called for the allocation and LocalFree must
// be called to do the free. Otherwise, pDecodePara->pfnAlloc is called
// for the allocation.
//
// *pcbStructInfo is ignored on input and updated with the length of the
// allocated, decoded structure.
//
// This flag may also be set in the CryptDecodeObject API. Since
// CryptDecodeObject doesn't take a pDecodePara, LocalAlloc is always
// called for the allocation which must be freed by calling LocalFree.

  CRYPT_DECODE_ALLOC_FLAG = $8000;
  {$EXTERNALSYM CRYPT_DECODE_ALLOC_FLAG}

// The following flag is applicable when decoding X509_UNICODE_NAME,
// X509_UNICODE_NAME_VALUE or X509_UNICODE_ANY_STRING.
// By default, CERT_RDN_T61_STRING values are initially decoded
// as UTF8. If the UTF8 decoding fails, then, decoded as 8 bit characters.
// Setting this flag skips the initial attempt to decode as UTF8.

  CRYPT_UNICODE_NAME_DECODE_DISABLE_IE4_UTF8_FLAG = CERT_RDN_DISABLE_IE4_UTF8_FLAG;
  {$EXTERNALSYM CRYPT_UNICODE_NAME_DECODE_DISABLE_IE4_UTF8_FLAG}

//+-------------------------------------------------------------------------
//  Predefined X509 certificate data structures that can be encoded / decoded.
//--------------------------------------------------------------------------

  CRYPT_ENCODE_DECODE_NONE       = 0;
  {$EXTERNALSYM CRYPT_ENCODE_DECODE_NONE}
  X509_CERT                      = LPCSTR(1);
  {$EXTERNALSYM X509_CERT}
  X509_CERT_TO_BE_SIGNED         = LPCSTR(2);
  {$EXTERNALSYM X509_CERT_TO_BE_SIGNED}
  X509_CERT_CRL_TO_BE_SIGNED     = LPCSTR(3);
  {$EXTERNALSYM X509_CERT_CRL_TO_BE_SIGNED}
  X509_CERT_REQUEST_TO_BE_SIGNED = LPCSTR(4);
  {$EXTERNALSYM X509_CERT_REQUEST_TO_BE_SIGNED}
  X509_EXTENSIONS                = LPCSTR(5);
  {$EXTERNALSYM X509_EXTENSIONS}
  X509_NAME_VALUE                = LPCSTR(6);
  {$EXTERNALSYM X509_NAME_VALUE}
  X509_NAME                      = LPCSTR(7);
  {$EXTERNALSYM X509_NAME}
  X509_PUBLIC_KEY_INFO           = LPCSTR(8);
  {$EXTERNALSYM X509_PUBLIC_KEY_INFO}

//+-------------------------------------------------------------------------
//  Predefined X509 certificate extension data structures that can be
//  encoded / decoded.
//--------------------------------------------------------------------------

  X509_AUTHORITY_KEY_ID      = LPCSTR(9);
  {$EXTERNALSYM X509_AUTHORITY_KEY_ID}
  X509_KEY_ATTRIBUTES        = LPCSTR(10);
  {$EXTERNALSYM X509_KEY_ATTRIBUTES}
  X509_KEY_USAGE_RESTRICTION = LPCSTR(11);
  {$EXTERNALSYM X509_KEY_USAGE_RESTRICTION}
  X509_ALTERNATE_NAME        = LPCSTR(12);
  {$EXTERNALSYM X509_ALTERNATE_NAME}
  X509_BASIC_CONSTRAINTS     = LPCSTR(13);
  {$EXTERNALSYM X509_BASIC_CONSTRAINTS}
  X509_KEY_USAGE             = LPCSTR(14);
  {$EXTERNALSYM X509_KEY_USAGE}
  X509_BASIC_CONSTRAINTS2    = LPCSTR(15);
  {$EXTERNALSYM X509_BASIC_CONSTRAINTS2}
  X509_CERT_POLICIES         = LPCSTR(16);
  {$EXTERNALSYM X509_CERT_POLICIES}

//+-------------------------------------------------------------------------
//  Additional predefined data structures that can be encoded / decoded.
//--------------------------------------------------------------------------

  PKCS_UTC_TIME         = LPCSTR(17);
  {$EXTERNALSYM PKCS_UTC_TIME}
  PKCS_TIME_REQUEST     = LPCSTR(18);
  {$EXTERNALSYM PKCS_TIME_REQUEST}
  RSA_CSP_PUBLICKEYBLOB = LPCSTR(19);
  {$EXTERNALSYM RSA_CSP_PUBLICKEYBLOB}
  X509_UNICODE_NAME     = LPCSTR(20);
  {$EXTERNALSYM X509_UNICODE_NAME}

  X509_KEYGEN_REQUEST_TO_BE_SIGNED  = LPCSTR(21);
  {$EXTERNALSYM X509_KEYGEN_REQUEST_TO_BE_SIGNED}
  PKCS_ATTRIBUTE                    = LPCSTR(22);
  {$EXTERNALSYM PKCS_ATTRIBUTE}
  PKCS_CONTENT_INFO_SEQUENCE_OF_ANY = LPCSTR(23);
  {$EXTERNALSYM PKCS_CONTENT_INFO_SEQUENCE_OF_ANY}

//+-------------------------------------------------------------------------
//  Predefined primitive data structures that can be encoded / decoded.
//--------------------------------------------------------------------------

  X509_UNICODE_NAME_VALUE = LPCSTR(24);
  {$EXTERNALSYM X509_UNICODE_NAME_VALUE}
  X509_ANY_STRING         = X509_NAME_VALUE;
  {$EXTERNALSYM X509_ANY_STRING}
  X509_UNICODE_ANY_STRING = X509_UNICODE_NAME_VALUE;
  {$EXTERNALSYM X509_UNICODE_ANY_STRING}
  X509_OCTET_STRING       = LPCSTR(25);
  {$EXTERNALSYM X509_OCTET_STRING}
  X509_BITS               = LPCSTR(26);
  {$EXTERNALSYM X509_BITS}
  X509_INTEGER            = LPCSTR(27);
  {$EXTERNALSYM X509_INTEGER}
  X509_MULTI_BYTE_INTEGER = LPCSTR(28);
  {$EXTERNALSYM X509_MULTI_BYTE_INTEGER}
  X509_ENUMERATED         = LPCSTR(29);
  {$EXTERNALSYM X509_ENUMERATED}
  X509_CHOICE_OF_TIME     = LPCSTR(30);
  {$EXTERNALSYM X509_CHOICE_OF_TIME}

//+-------------------------------------------------------------------------
//  More predefined X509 certificate extension data structures that can be
//  encoded / decoded.
//--------------------------------------------------------------------------

  X509_AUTHORITY_KEY_ID2     = LPCSTR(31);
  {$EXTERNALSYM X509_AUTHORITY_KEY_ID2}
  X509_AUTHORITY_INFO_ACCESS = LPCSTR(32);
  {$EXTERNALSYM X509_AUTHORITY_INFO_ACCESS}
  X509_CRL_REASON_CODE       = X509_ENUMERATED;
  {$EXTERNALSYM X509_CRL_REASON_CODE}
  PKCS_CONTENT_INFO          = LPCSTR(33);
  {$EXTERNALSYM PKCS_CONTENT_INFO}
  X509_SEQUENCE_OF_ANY       = LPCSTR(34);
  {$EXTERNALSYM X509_SEQUENCE_OF_ANY}
  X509_CRL_DIST_POINTS       = LPCSTR(35);
  {$EXTERNALSYM X509_CRL_DIST_POINTS}
  X509_ENHANCED_KEY_USAGE    = LPCSTR(36);
  {$EXTERNALSYM X509_ENHANCED_KEY_USAGE}
  PKCS_CTL                   = LPCSTR(37);
  {$EXTERNALSYM PKCS_CTL}

  X509_MULTI_BYTE_UINT    = LPCSTR(38);
  {$EXTERNALSYM X509_MULTI_BYTE_UINT}
  X509_DSS_PUBLICKEY      = X509_MULTI_BYTE_UINT;
  {$EXTERNALSYM X509_DSS_PUBLICKEY}
  X509_DSS_PARAMETERS     = LPCSTR(39);
  {$EXTERNALSYM X509_DSS_PARAMETERS}
  X509_DSS_SIGNATURE      = LPCSTR(40);
  {$EXTERNALSYM X509_DSS_SIGNATURE}
  PKCS_RC2_CBC_PARAMETERS = LPCSTR(41);
  {$EXTERNALSYM PKCS_RC2_CBC_PARAMETERS}
  PKCS_SMIME_CAPABILITIES = LPCSTR(42);
  {$EXTERNALSYM PKCS_SMIME_CAPABILITIES}

//+-------------------------------------------------------------------------
//  data structures for private keys
//--------------------------------------------------------------------------

  PKCS_RSA_PRIVATE_KEY            = LPCSTR(43);
  {$EXTERNALSYM PKCS_RSA_PRIVATE_KEY}
  PKCS_PRIVATE_KEY_INFO           = LPCSTR(44);
  {$EXTERNALSYM PKCS_PRIVATE_KEY_INFO}
  PKCS_ENCRYPTED_PRIVATE_KEY_INFO = LPCSTR(45);
  {$EXTERNALSYM PKCS_ENCRYPTED_PRIVATE_KEY_INFO}

//+-------------------------------------------------------------------------
//  certificate policy qualifier
//--------------------------------------------------------------------------

  X509_PKIX_POLICY_QUALIFIER_USERNOTICE = LPCSTR(46);
  {$EXTERNALSYM X509_PKIX_POLICY_QUALIFIER_USERNOTICE}

//+-------------------------------------------------------------------------
//  Diffie-Hellman Key Exchange
//--------------------------------------------------------------------------

  X509_DH_PUBLICKEY  = X509_MULTI_BYTE_UINT;
  {$EXTERNALSYM X509_DH_PUBLICKEY}
  X509_DH_PARAMETERS = LPCSTR(47);
  {$EXTERNALSYM X509_DH_PARAMETERS}
  PKCS_ATTRIBUTES    = LPCSTR(48);
  {$EXTERNALSYM PKCS_ATTRIBUTES}
  PKCS_SORTED_CTL    = LPCSTR(49);
  {$EXTERNALSYM PKCS_SORTED_CTL}

//+-------------------------------------------------------------------------
//  X942 Diffie-Hellman
//--------------------------------------------------------------------------

  X942_DH_PARAMETERS = LPCSTR(50);
  {$EXTERNALSYM X942_DH_PARAMETERS}

//+-------------------------------------------------------------------------
//  The following is the same as X509_BITS, except before encoding,
//  the bit length is decremented to exclude trailing zero bits.
//--------------------------------------------------------------------------

  X509_BITS_WITHOUT_TRAILING_ZEROES = LPCSTR(51);
  {$EXTERNALSYM X509_BITS_WITHOUT_TRAILING_ZEROES}

//+-------------------------------------------------------------------------
//  X942 Diffie-Hellman Other Info
//--------------------------------------------------------------------------

  X942_OTHER_INFO = LPCSTR(52);
  {$EXTERNALSYM X942_OTHER_INFO}

//+-------------------------------------------------------------------------
//  Predefined PKCS #7 data structures that can be encoded / decoded.
//--------------------------------------------------------------------------

  PKCS7_SIGNER_INFO = LPCSTR(500);
  {$EXTERNALSYM PKCS7_SIGNER_INFO}

//+-------------------------------------------------------------------------
//  Predefined PKCS #7 data structures that can be encoded / decoded.
//--------------------------------------------------------------------------

  CMS_SIGNER_INFO = LPCSTR(501);
  {$EXTERNALSYM CMS_SIGNER_INFO}

//+-------------------------------------------------------------------------
//  Predefined Software Publishing Credential (SPC)  data structures that
//  can be encoded / decoded.
//
//  Predefined values: 2000 .. 2999
//
//  See spc.h for value and data structure definitions.
//--------------------------------------------------------------------------

//+-------------------------------------------------------------------------
//  Extension Object Identifiers
//--------------------------------------------------------------------------

  szOID_AUTHORITY_KEY_IDENTIFIER = '2.5.29.1';
  {$EXTERNALSYM szOID_AUTHORITY_KEY_IDENTIFIER}
  szOID_KEY_ATTRIBUTES           = '2.5.29.2';
  {$EXTERNALSYM szOID_KEY_ATTRIBUTES}
  szOID_CERT_POLICIES_95         = '2.5.29.3';
  {$EXTERNALSYM szOID_CERT_POLICIES_95}
  szOID_KEY_USAGE_RESTRICTION    = '2.5.29.4';
  {$EXTERNALSYM szOID_KEY_USAGE_RESTRICTION}
  szOID_SUBJECT_ALT_NAME         = '2.5.29.7';
  {$EXTERNALSYM szOID_SUBJECT_ALT_NAME}
  szOID_ISSUER_ALT_NAME          = '2.5.29.8';
  {$EXTERNALSYM szOID_ISSUER_ALT_NAME}
  szOID_BASIC_CONSTRAINTS        = '2.5.29.10';
  {$EXTERNALSYM szOID_BASIC_CONSTRAINTS}
  szOID_KEY_USAGE                = '2.5.29.15';
  {$EXTERNALSYM szOID_KEY_USAGE}
  szOID_PRIVATEKEY_USAGE_PERIOD  = '2.5.29.16';
  {$EXTERNALSYM szOID_PRIVATEKEY_USAGE_PERIOD}
  szOID_BASIC_CONSTRAINTS2       = '2.5.29.19';
  {$EXTERNALSYM szOID_BASIC_CONSTRAINTS2}
  szOID_CERT_POLICIES            = '2.5.29.32';
  {$EXTERNALSYM szOID_CERT_POLICIES}

  szOID_AUTHORITY_KEY_IDENTIFIER2 = '2.5.29.35';
  {$EXTERNALSYM szOID_AUTHORITY_KEY_IDENTIFIER2}
  szOID_SUBJECT_KEY_IDENTIFIER    = '2.5.29.14';
  {$EXTERNALSYM szOID_SUBJECT_KEY_IDENTIFIER}
  szOID_SUBJECT_ALT_NAME2         = '2.5.29.17';
  {$EXTERNALSYM szOID_SUBJECT_ALT_NAME2}
  szOID_ISSUER_ALT_NAME2          = '2.5.29.18';
  {$EXTERNALSYM szOID_ISSUER_ALT_NAME2}
  szOID_CRL_REASON_CODE           = '2.5.29.21';
  {$EXTERNALSYM szOID_CRL_REASON_CODE}
  szOID_CRL_DIST_POINTS           = '2.5.29.31';
  {$EXTERNALSYM szOID_CRL_DIST_POINTS}
  szOID_ENHANCED_KEY_USAGE        = '2.5.29.37';
  {$EXTERNALSYM szOID_ENHANCED_KEY_USAGE}

// Microsoft PKCS10 Attributes

  szOID_RENEWAL_CERTIFICATE        = '1.3.6.1.4.1.311.13.1';
  {$EXTERNALSYM szOID_RENEWAL_CERTIFICATE}
  szOID_ENROLLMENT_NAME_VALUE_PAIR = '1.3.6.1.4.1.311.13.2.1';
  {$EXTERNALSYM szOID_ENROLLMENT_NAME_VALUE_PAIR}
  szOID_ENROLLMENT_CSP_PROVIDER    = '1.3.6.1.4.1.311.13.2.2';
  {$EXTERNALSYM szOID_ENROLLMENT_CSP_PROVIDER}
  szOID_OS_VERSION                 = '1.3.6.1.4.1.311.13.2.3';
  {$EXTERNALSYM szOID_OS_VERSION}

//
// Extension contain certificate type

  szOID_ENROLLMENT_AGENT = '1.3.6.1.4.1.311.20.2.1';
  {$EXTERNALSYM szOID_ENROLLMENT_AGENT}

// Internet Public Key Infrastructure (PKIX)

  szOID_PKIX                  = '1.3.6.1.5.5.7';
  {$EXTERNALSYM szOID_PKIX}
  szOID_PKIX_PE               = '1.3.6.1.5.5.7.1';
  {$EXTERNALSYM szOID_PKIX_PE}
  szOID_AUTHORITY_INFO_ACCESS = '1.3.6.1.5.5.7.1.1';
  {$EXTERNALSYM szOID_AUTHORITY_INFO_ACCESS}

// Microsoft extensions or attributes

  szOID_CERT_EXTENSIONS      = '1.3.6.1.4.1.311.2.1.14';
  {$EXTERNALSYM szOID_CERT_EXTENSIONS}
  szOID_NEXT_UPDATE_LOCATION = '1.3.6.1.4.1.311.10.2';
  {$EXTERNALSYM szOID_NEXT_UPDATE_LOCATION}

//  Microsoft PKCS #7 ContentType Object Identifiers

  szOID_CTL = '1.3.6.1.4.1.311.10.1';
  {$EXTERNALSYM szOID_CTL}

//  Microsoft Sorted CTL Extension Object Identifier

  szOID_SORTED_CTL = '1.3.6.1.4.1.311.10.1.1';
  {$EXTERNALSYM szOID_SORTED_CTL}

// serialized serial numbers for PRS

  szOID_SERIALIZED = '1.3.6.1.4.1.311.10.3.3.1';
  {$EXTERNALSYM szOID_SERIALIZED}

// UPN principal name in SubjectAltName

  szOID_NT_PRINCIPAL_NAME = '1.3.6.1.4.1.311.20.2.3';
  {$EXTERNALSYM szOID_NT_PRINCIPAL_NAME}

// Windows product update unauthenticated attribute

  szOID_PRODUCT_UPDATE = '1.3.6.1.4.1.311.31.1';
  {$EXTERNALSYM szOID_PRODUCT_UPDATE}

//+-------------------------------------------------------------------------
//  Object Identifiers for use with Auto Enrollment
//--------------------------------------------------------------------------

  szOID_AUTO_ENROLL_CTL_USAGE = '1.3.6.1.4.1.311.20.1';
  {$EXTERNALSYM szOID_AUTO_ENROLL_CTL_USAGE}

// Extension contain certificate type

  szOID_ENROLL_CERTTYPE_EXTENSION = '1.3.6.1.4.1.311.20.2';
  {$EXTERNALSYM szOID_ENROLL_CERTTYPE_EXTENSION}

  szOID_CERT_MANIFOLD = '1.3.6.1.4.1.311.20.3';
  {$EXTERNALSYM szOID_CERT_MANIFOLD}

//+-------------------------------------------------------------------------
//  Object Identifiers for use with the MS Certificate Server
//--------------------------------------------------------------------------

  szOID_CERTSRV_CA_VERSION = '1.3.6.1.4.1.311.21.1';
  {$EXTERNALSYM szOID_CERTSRV_CA_VERSION}

//+-------------------------------------------------------------------------
//  Object Identifiers for use with the MS Directory Service
//--------------------------------------------------------------------------

  szOID_NTDS_REPLICATION = '1.3.6.1.4.1.311.25.1';
  {$EXTERNALSYM szOID_NTDS_REPLICATION}

//+-------------------------------------------------------------------------
//  Extension Object Identifiers (currently not implemented)
//--------------------------------------------------------------------------

  szOID_POLICY_MAPPINGS   = '2.5.29.5';
  {$EXTERNALSYM szOID_POLICY_MAPPINGS}
  szOID_SUBJECT_DIR_ATTRS = '2.5.29.9';
  {$EXTERNALSYM szOID_SUBJECT_DIR_ATTRS}

//+-------------------------------------------------------------------------
//  Enhanced Key Usage (Purpose) Object Identifiers
//--------------------------------------------------------------------------

  szOID_PKIX_KP = '1.3.6.1.5.5.7.3';
  {$EXTERNALSYM szOID_PKIX_KP}

// Consistent key usage bits: DIGITAL_SIGNATURE, KEY_ENCIPHERMENT
// or KEY_AGREEMENT

  szOID_PKIX_KP_SERVER_AUTH = '1.3.6.1.5.5.7.3.1';
  {$EXTERNALSYM szOID_PKIX_KP_SERVER_AUTH}

// Consistent key usage bits: DIGITAL_SIGNATURE

  szOID_PKIX_KP_CLIENT_AUTH = '1.3.6.1.5.5.7.3.2';
  {$EXTERNALSYM szOID_PKIX_KP_CLIENT_AUTH}

// Consistent key usage bits: DIGITAL_SIGNATURE

  szOID_PKIX_KP_CODE_SIGNING = '1.3.6.1.5.5.7.3.3';
  {$EXTERNALSYM szOID_PKIX_KP_CODE_SIGNING}

// Consistent key usage bits: DIGITAL_SIGNATURE, NON_REPUDIATION and/or
// (KEY_ENCIPHERMENT or KEY_AGREEMENT)

  szOID_PKIX_KP_EMAIL_PROTECTION = '1.3.6.1.5.5.7.3.4';
  {$EXTERNALSYM szOID_PKIX_KP_EMAIL_PROTECTION}

// Consistent key usage bits: DIGITAL_SIGNATURE and/or
// (KEY_ENCIPHERMENT or KEY_AGREEMENT)

  szOID_PKIX_KP_IPSEC_END_SYSTEM = '1.3.6.1.5.5.7.3.5';
  {$EXTERNALSYM szOID_PKIX_KP_IPSEC_END_SYSTEM}

// Consistent key usage bits: DIGITAL_SIGNATURE and/or
// (KEY_ENCIPHERMENT or KEY_AGREEMENT)

  szOID_PKIX_KP_IPSEC_TUNNEL = '1.3.6.1.5.5.7.3.6';
  {$EXTERNALSYM szOID_PKIX_KP_IPSEC_TUNNEL}

// Consistent key usage bits: DIGITAL_SIGNATURE and/or
// (KEY_ENCIPHERMENT or KEY_AGREEMENT)

  szOID_PKIX_KP_IPSEC_USER = '1.3.6.1.5.5.7.3.7';
  {$EXTERNALSYM szOID_PKIX_KP_IPSEC_USER}

// Consistent key usage bits: DIGITAL_SIGNATURE or NON_REPUDIATION

  szOID_PKIX_KP_TIMESTAMP_SIGNING = '1.3.6.1.5.5.7.3.8';
  {$EXTERNALSYM szOID_PKIX_KP_TIMESTAMP_SIGNING}

//+-------------------------------------------------------------------------
//  Microsoft Enhanced Key Usage (Purpose) Object Identifiers
//+-------------------------------------------------------------------------

//  Signer of CTLs

  szOID_KP_CTL_USAGE_SIGNING = '1.3.6.1.4.1.311.10.3.1';
  {$EXTERNALSYM szOID_KP_CTL_USAGE_SIGNING}

//  Signer of TimeStamps

  szOID_KP_TIME_STAMP_SIGNING = '1.3.6.1.4.1.311.10.3.2';
  {$EXTERNALSYM szOID_KP_TIME_STAMP_SIGNING}

  szOID_SERVER_GATED_CRYPTO = '1.3.6.1.4.1.311.10.3.3';
  {$EXTERNALSYM szOID_SERVER_GATED_CRYPTO}

  szOID_SGC_NETSCAPE = '2.16.840.1.113730.4.1';
  {$EXTERNALSYM szOID_SGC_NETSCAPE}

  szOID_KP_EFS = '1.3.6.1.4.1.311.10.3.4';
  {$EXTERNALSYM szOID_KP_EFS}

// Can use Windows Hardware Compatible (WHQL)

  szOID_WHQL_CRYPTO = '1.3.6.1.4.1.311.10.3.5';
  {$EXTERNALSYM szOID_WHQL_CRYPTO}

// Signed by the NT5 build lab

  szOID_NT5_CRYPTO = '1.3.6.1.4.1.311.10.3.6';
  {$EXTERNALSYM szOID_NT5_CRYPTO}

// Signed by and OEM of WHQL

  szOID_OEM_WHQL_CRYPTO = '1.3.6.1.4.1.311.10.3.7';
  {$EXTERNALSYM szOID_OEM_WHQL_CRYPTO}

// Signed by the Embedded NT

  szOID_EMBEDDED_NT_CRYPTO = '1.3.6.1.4.1.311.10.3.8';
  {$EXTERNALSYM szOID_EMBEDDED_NT_CRYPTO}

  szOID_DRM = '1.3.6.1.4.1.311.10.5.1';
  {$EXTERNALSYM szOID_DRM}

  szOID_LICENSES = '1.3.6.1.4.1.311.10.6.1';
  {$EXTERNALSYM szOID_LICENSES}

  szOID_LICENSE_SERVER = '1.3.6.1.4.1.311.10.6.2';
  {$EXTERNALSYM szOID_LICENSE_SERVER}

  szOID_KP_SMARTCARD_LOGON = '1.3.6.1.4.1.311.20.2.2';
  {$EXTERNALSYM szOID_KP_SMARTCARD_LOGON}

//+-------------------------------------------------------------------------
//  Microsoft Attribute Object Identifiers
//+-------------------------------------------------------------------------

  szOID_YESNO_TRUST_ATTR = '1.3.6.1.4.1.311.10.4.1';
  {$EXTERNALSYM szOID_YESNO_TRUST_ATTR}

//+-------------------------------------------------------------------------
//  Qualifiers that may be part of the szOID_CERT_POLICIES and
//  szOID_CERT_POLICIES95 extensions
//+-------------------------------------------------------------------------

  szOID_PKIX_POLICY_QUALIFIER_CPS        = '1.3.6.1.5.5.7.2.1';
  {$EXTERNALSYM szOID_PKIX_POLICY_QUALIFIER_CPS}
  szOID_PKIX_POLICY_QUALIFIER_USERNOTICE = '1.3.6.1.5.5.7.2.2';
  {$EXTERNALSYM szOID_PKIX_POLICY_QUALIFIER_USERNOTICE}

// OID for old qualifer

  szOID_CERT_POLICIES_95_QUALIFIER1 = '2.16.840.1.113733.1.7.1.1';
  {$EXTERNALSYM szOID_CERT_POLICIES_95_QUALIFIER1}

//+-------------------------------------------------------------------------
//  X509_CERT
//
//  The "to be signed" encoded content plus its signature. The ToBeSigned
//  content is the CryptEncodeObject() output for one of the following:
//  X509_CERT_TO_BE_SIGNED, X509_CERT_CRL_TO_BE_SIGNED or
//  X509_CERT_REQUEST_TO_BE_SIGNED.
//
//  pvStructInfo points to CERT_SIGNED_CONTENT_INFO.
//--------------------------------------------------------------------------

//+-------------------------------------------------------------------------
//  X509_CERT_TO_BE_SIGNED
//
//  pvStructInfo points to CERT_INFO.
//
//  For CryptDecodeObject(), the pbEncoded is the "to be signed" plus its
//  signature (output of a X509_CERT CryptEncodeObject()).
//
//  For CryptEncodeObject(), the pbEncoded is just the "to be signed".
//--------------------------------------------------------------------------

//+-------------------------------------------------------------------------
//  X509_CERT_CRL_TO_BE_SIGNED
//
//  pvStructInfo points to CRL_INFO.
//
//  For CryptDecodeObject(), the pbEncoded is the "to be signed" plus its
//  signature (output of a X509_CERT CryptEncodeObject()).
//
//  For CryptEncodeObject(), the pbEncoded is just the "to be signed".
//--------------------------------------------------------------------------

//+-------------------------------------------------------------------------
//  X509_CERT_REQUEST_TO_BE_SIGNED
//
//  pvStructInfo points to CERT_REQUEST_INFO.
//
//  For CryptDecodeObject(), the pbEncoded is the "to be signed" plus its
//  signature (output of a X509_CERT CryptEncodeObject()).
//
//  For CryptEncodeObject(), the pbEncoded is just the "to be signed".
//--------------------------------------------------------------------------

//+-------------------------------------------------------------------------
//  X509_EXTENSIONS
//  szOID_CERT_EXTENSIONS
//
//  pvStructInfo points to following CERT_EXTENSIONS.
//--------------------------------------------------------------------------

type
  PCERT_EXTENSIONS = ^CERT_EXTENSIONS;
  {$EXTERNALSYM PCERT_EXTENSIONS}
  _CERT_EXTENSIONS = record
    cExtension: DWORD;
    rgExtension: PCERT_EXTENSION;
  end;
  {$EXTERNALSYM _CERT_EXTENSIONS}
  CERT_EXTENSIONS = _CERT_EXTENSIONS;
  {$EXTERNALSYM CERT_EXTENSIONS}
  TCertExtensions = CERT_EXTENSIONS;
  PCertExtensions = PCERT_EXTENSIONS;

//+-------------------------------------------------------------------------
//  X509_NAME_VALUE
//  X509_ANY_STRING
//
//  pvStructInfo points to CERT_NAME_VALUE.
//--------------------------------------------------------------------------

//+-------------------------------------------------------------------------
//  X509_UNICODE_NAME_VALUE
//  X509_UNICODE_ANY_STRING
//
//  pvStructInfo points to CERT_NAME_VALUE.
//
//  The name values are unicode strings.
//
//  For CryptEncodeObject:
//    Value.pbData points to the unicode string.
//    If Value.cbData = 0, then, the unicode string is NULL terminated.
//    Otherwise, Value.cbData is the unicode string byte count. The byte count
//    is twice the character count.
//
//    If the unicode string contains an invalid character for the specified
//    dwValueType, then, *pcbEncoded is updated with the unicode character
//    index of the first invalid character. LastError is set to:
//    CRYPT_E_INVALID_NUMERIC_STRING, CRYPT_E_INVALID_PRINTABLE_STRING or
//    CRYPT_E_INVALID_IA5_STRING.
//
//    To disable the above check, either set CERT_RDN_DISABLE_CHECK_TYPE_FLAG
//    in dwValueType or set CRYPT_UNICODE_NAME_ENCODE_DISABLE_CHECK_TYPE_FLAG
//    in dwFlags passed to CryptEncodeObjectEx.
//
//    The unicode string is converted before being encoded according to
//    the specified dwValueType. If dwValueType is set to 0, LastError
//    is set to E_INVALIDARG.
//
//    If the dwValueType isn't one of the character strings (its a
//    CERT_RDN_ENCODED_BLOB or CERT_RDN_OCTET_STRING), then, CryptEncodeObject
//    will return FALSE with LastError set to CRYPT_E_NOT_CHAR_STRING.
//
//  For CryptDecodeObject:
//    Value.pbData points to a NULL terminated unicode string. Value.cbData
//    contains the byte count of the unicode string excluding the NULL
//    terminator. dwValueType contains the type used in the encoded object.
//    Its not forced to CERT_RDN_UNICODE_STRING. The encoded value is
//    converted to the unicode string according to the dwValueType.
//
//    If the encoded object isn't one of the character string types, then,
//    CryptDecodeObject will return FALSE with LastError set to
//    CRYPT_E_NOT_CHAR_STRING. For a non character string, decode using
//    X509_NAME_VALUE or X509_ANY_STRING.
//
//    By default, CERT_RDN_T61_STRING values are initially decoded
//    as UTF8. If the UTF8 decoding fails, then, decoded as 8 bit characters.
//    Set CRYPT_UNICODE_NAME_DECODE_DISABLE_IE4_UTF8_FLAG in dwFlags
//    passed to either CryptDecodeObject or CryptDecodeObjectEx to
//    skip the initial attempt to decode as UTF8.
//--------------------------------------------------------------------------

//+-------------------------------------------------------------------------
//  X509_NAME
//
//  pvStructInfo points to CERT_NAME_INFO.
//--------------------------------------------------------------------------

//+-------------------------------------------------------------------------
//  X509_UNICODE_NAME
//
//  pvStructInfo points to CERT_NAME_INFO.
//
//  The RDN attribute values are unicode strings except for the dwValueTypes of
//  CERT_RDN_ENCODED_BLOB or CERT_RDN_OCTET_STRING. These dwValueTypes are
//  the same as for a X509_NAME. Their values aren't converted to/from unicode.
//
//  For CryptEncodeObject:
//    Value.pbData points to the unicode string.
//    If Value.cbData = 0, then, the unicode string is NULL terminated.
//    Otherwise, Value.cbData is the unicode string byte count. The byte count
//    is twice the character count.
//
//    If dwValueType = 0 (CERT_RDN_ANY_TYPE), the pszObjId is used to find
//    an acceptable dwValueType. If the unicode string contains an
//    invalid character for the found or specified dwValueType, then,
//    *pcbEncoded is updated with the error location of the invalid character.
//    See below for details. LastError is set to:
//    CRYPT_E_INVALID_NUMERIC_STRING, CRYPT_E_INVALID_PRINTABLE_STRING or
//    CRYPT_E_INVALID_IA5_STRING.
//
//    To disable the above check, either set CERT_RDN_DISABLE_CHECK_TYPE_FLAG
//    in dwValueType or set CRYPT_UNICODE_NAME_ENCODE_DISABLE_CHECK_TYPE_FLAG
//    in dwFlags passed to CryptEncodeObjectEx.
//
//    Set CERT_RDN_UNICODE_STRING in dwValueType or set
//    CRYPT_UNICODE_NAME_ENCODE_ENABLE_T61_UNICODE_FLAG in dwFlags passed
//    to CryptEncodeObjectEx to select CERT_RDN_T61_STRING instead of
//    CERT_RDN_UNICODE_STRING if all the unicode characters are <= 0xFF.
//
//    Set CERT_RDN_ENABLE_UTF8_UNICODE_STRING in dwValueType or set
//    CRYPT_UNICODE_NAME_ENCODE_ENABLE_UTF8_UNICODE_FLAG in dwFlags passed
//    to CryptEncodeObjectEx to select CERT_RDN_UTF8_STRING instead of
//    CERT_RDN_UNICODE_STRING.
//
//    The unicode string is converted before being encoded according to
//    the specified or ObjId matching dwValueType.
//
//  For CryptDecodeObject:
//    Value.pbData points to a NULL terminated unicode string. Value.cbData
//    contains the byte count of the unicode string excluding the NULL
//    terminator. dwValueType contains the type used in the encoded object.
//    Its not forced to CERT_RDN_UNICODE_STRING. The encoded value is
//    converted to the unicode string according to the dwValueType.
//
//    If the dwValueType of the encoded value isn't a character string
//    type, then, it isn't converted to UNICODE. Use the
//    IS_CERT_RDN_CHAR_STRING() macro on the dwValueType to check
//    that Value.pbData points to a converted unicode string.
//
//    By default, CERT_RDN_T61_STRING values are initially decoded
//    as UTF8. If the UTF8 decoding fails, then, decoded as 8 bit characters.
//    Set CRYPT_UNICODE_NAME_DECODE_DISABLE_IE4_UTF8_FLAG in dwFlags
//    passed to either CryptDecodeObject or CryptDecodeObjectEx to
//    skip the initial attempt to decode as UTF8.
//--------------------------------------------------------------------------

//+-------------------------------------------------------------------------
//  Unicode Name Value Error Location Definitions
//
//  Error location is returned in *pcbEncoded by
//  CryptEncodeObject(X509_UNICODE_NAME)
//
//  Error location consists of:
//    RDN_INDEX     - 10 bits << 22
//    ATTR_INDEX    - 6 bits << 16
//    VALUE_INDEX   - 16 bits (unicode character index)
//--------------------------------------------------------------------------

const
  CERT_UNICODE_RDN_ERR_INDEX_MASK    = $3FF;
  {$EXTERNALSYM CERT_UNICODE_RDN_ERR_INDEX_MASK}
  CERT_UNICODE_RDN_ERR_INDEX_SHIFT   = 22;
  {$EXTERNALSYM CERT_UNICODE_RDN_ERR_INDEX_SHIFT}
  CERT_UNICODE_ATTR_ERR_INDEX_MASK   = $003F;
  {$EXTERNALSYM CERT_UNICODE_ATTR_ERR_INDEX_MASK}
  CERT_UNICODE_ATTR_ERR_INDEX_SHIFT  = 16;
  {$EXTERNALSYM CERT_UNICODE_ATTR_ERR_INDEX_SHIFT}
  CERT_UNICODE_VALUE_ERR_INDEX_MASK  = $0000FFFF;
  {$EXTERNALSYM CERT_UNICODE_VALUE_ERR_INDEX_MASK}
  CERT_UNICODE_VALUE_ERR_INDEX_SHIFT = 0;
  {$EXTERNALSYM CERT_UNICODE_VALUE_ERR_INDEX_SHIFT}

function GET_CERT_UNICODE_RDN_ERR_INDEX(X: DWORD): DWORD;
{$EXTERNALSYM GET_CERT_UNICODE_RDN_ERR_INDEX}

function GET_CERT_UNICODE_ATTR_ERR_INDEX(X: DWORD): DWORD;
{$EXTERNALSYM GET_CERT_UNICODE_ATTR_ERR_INDEX}

function GET_CERT_UNICODE_VALUE_ERR_INDEX(X: DWORD): DWORD;
{$EXTERNALSYM GET_CERT_UNICODE_VALUE_ERR_INDEX}

//+-------------------------------------------------------------------------
//  X509_PUBLIC_KEY_INFO
//
//  pvStructInfo points to CERT_PUBLIC_KEY_INFO.
//--------------------------------------------------------------------------


//+-------------------------------------------------------------------------
//  X509_AUTHORITY_KEY_ID
//  szOID_AUTHORITY_KEY_IDENTIFIER
//
//  pvStructInfo points to following CERT_AUTHORITY_KEY_ID_INFO.
//--------------------------------------------------------------------------

type
  PCERT_AUTHORITY_KEY_ID_INFO = ^CERT_AUTHORITY_KEY_ID_INFO;
  {$EXTERNALSYM PCERT_AUTHORITY_KEY_ID_INFO}
  _CERT_AUTHORITY_KEY_ID_INFO = record
    KeyId: CRYPT_DATA_BLOB;
    CertIssuer: CERT_NAME_BLOB;
    CertSerialNumber: CRYPT_INTEGER_BLOB;
  end;
  {$EXTERNALSYM _CERT_AUTHORITY_KEY_ID_INFO}
  CERT_AUTHORITY_KEY_ID_INFO = _CERT_AUTHORITY_KEY_ID_INFO;
  {$EXTERNALSYM CERT_AUTHORITY_KEY_ID_INFO}
  TCertAuthorityKeyIdInfo = CERT_AUTHORITY_KEY_ID_INFO;
  PCertAuthorityKeyIdInfo = PCERT_AUTHORITY_KEY_ID_INFO;

//+-------------------------------------------------------------------------
//  X509_KEY_ATTRIBUTES
//  szOID_KEY_ATTRIBUTES
//
//  pvStructInfo points to following CERT_KEY_ATTRIBUTES_INFO.
//--------------------------------------------------------------------------

  PCERT_PRIVATE_KEY_VALIDITY = ^CERT_PRIVATE_KEY_VALIDITY;
  {$EXTERNALSYM PCERT_PRIVATE_KEY_VALIDITY}
  _CERT_PRIVATE_KEY_VALIDITY = record
    NotBefore: FILETIME;
    NotAfter: FILETIME;
  end;
  {$EXTERNALSYM _CERT_PRIVATE_KEY_VALIDITY}
  CERT_PRIVATE_KEY_VALIDITY = _CERT_PRIVATE_KEY_VALIDITY;
  {$EXTERNALSYM CERT_PRIVATE_KEY_VALIDITY}
  TCertPrivateKeyValidity = CERT_PRIVATE_KEY_VALIDITY;
  PCertPrivateKeyValidity = PCERT_PRIVATE_KEY_VALIDITY;

  PCERT_KEY_ATTRIBUTES_INFO = ^CERT_KEY_ATTRIBUTES_INFO;
  {$EXTERNALSYM PCERT_KEY_ATTRIBUTES_INFO}
  _CERT_KEY_ATTRIBUTES_INFO = record
    KeyId: CRYPT_DATA_BLOB;
    IntendedKeyUsage: CRYPT_BIT_BLOB;
    pPrivateKeyUsagePeriod: PCERT_PRIVATE_KEY_VALIDITY; // OPTIONAL
  end;
  {$EXTERNALSYM _CERT_KEY_ATTRIBUTES_INFO}
  CERT_KEY_ATTRIBUTES_INFO = _CERT_KEY_ATTRIBUTES_INFO;
  {$EXTERNALSYM CERT_KEY_ATTRIBUTES_INFO}
  TCertKeyAttributesInfo = CERT_KEY_ATTRIBUTES_INFO;
  PCertKeyAttributesInfo = PCERT_KEY_ATTRIBUTES_INFO;

// Byte[0]

const
  CERT_DIGITAL_SIGNATURE_KEY_USAGE = $80;
  {$EXTERNALSYM CERT_DIGITAL_SIGNATURE_KEY_USAGE}
  CERT_NON_REPUDIATION_KEY_USAGE   = $40;
  {$EXTERNALSYM CERT_NON_REPUDIATION_KEY_USAGE}
  CERT_KEY_ENCIPHERMENT_KEY_USAGE  = $20;
  {$EXTERNALSYM CERT_KEY_ENCIPHERMENT_KEY_USAGE}
  CERT_DATA_ENCIPHERMENT_KEY_USAGE = $10;
  {$EXTERNALSYM CERT_DATA_ENCIPHERMENT_KEY_USAGE}
  CERT_KEY_AGREEMENT_KEY_USAGE     = $08;
  {$EXTERNALSYM CERT_KEY_AGREEMENT_KEY_USAGE}
  CERT_KEY_CERT_SIGN_KEY_USAGE     = $04;
  {$EXTERNALSYM CERT_KEY_CERT_SIGN_KEY_USAGE}
  CERT_OFFLINE_CRL_SIGN_KEY_USAGE  = $02;
  {$EXTERNALSYM CERT_OFFLINE_CRL_SIGN_KEY_USAGE}
  CERT_CRL_SIGN_KEY_USAGE          = $02;
  {$EXTERNALSYM CERT_CRL_SIGN_KEY_USAGE}
  CERT_ENCIPHER_ONLY_KEY_USAGE     = $01;
  {$EXTERNALSYM CERT_ENCIPHER_ONLY_KEY_USAGE}

// Byte[1]

  CERT_DECIPHER_ONLY_KEY_USAGE     = $80;
  {$EXTERNALSYM CERT_DECIPHER_ONLY_KEY_USAGE}

//+-------------------------------------------------------------------------
//  X509_KEY_USAGE_RESTRICTION
//  szOID_KEY_USAGE_RESTRICTION
//
//  pvStructInfo points to following CERT_KEY_USAGE_RESTRICTION_INFO.
//--------------------------------------------------------------------------

type
  PCERT_POLICY_ID = ^CERT_POLICY_ID;
  {$EXTERNALSYM PCERT_POLICY_ID}
  _CERT_POLICY_ID = record
    cCertPolicyElementId: DWORD;
    rgpszCertPolicyElementId: LPSTR; // pszObjId
  end;
  {$EXTERNALSYM _CERT_POLICY_ID}
  CERT_POLICY_ID = _CERT_POLICY_ID;
  {$EXTERNALSYM CERT_POLICY_ID}
  TCertPolicyId = CERT_POLICY_ID;
  PCertPolicyId = PCERT_POLICY_ID;

  PCERT_KEY_USAGE_RESTRICTION_INFO = ^CERT_KEY_USAGE_RESTRICTION_INFO;
  {$EXTERNALSYM PCERT_KEY_USAGE_RESTRICTION_INFO}
  _CERT_KEY_USAGE_RESTRICTION_INFO = record
    cCertPolicyId: DWORD;
    rgCertPolicyId: PCERT_POLICY_ID;
    RestrictedKeyUsage: CRYPT_BIT_BLOB;
  end;
  {$EXTERNALSYM _CERT_KEY_USAGE_RESTRICTION_INFO}
  CERT_KEY_USAGE_RESTRICTION_INFO = _CERT_KEY_USAGE_RESTRICTION_INFO;
  {$EXTERNALSYM CERT_KEY_USAGE_RESTRICTION_INFO}
  TCertKeyUsageRestrictionInfo = CERT_KEY_USAGE_RESTRICTION_INFO;
  PCertKeyUsageRestrictionInfo = PCERT_KEY_USAGE_RESTRICTION_INFO;

// See CERT_KEY_ATTRIBUTES_INFO for definition of the RestrictedKeyUsage bits

//+-------------------------------------------------------------------------
//  X509_ALTERNATE_NAME
//  szOID_SUBJECT_ALT_NAME
//  szOID_ISSUER_ALT_NAME
//  szOID_SUBJECT_ALT_NAME2
//  szOID_ISSUER_ALT_NAME2
//
//  pvStructInfo points to following CERT_ALT_NAME_INFO.
//--------------------------------------------------------------------------

  PCERT_OTHER_NAME = ^CERT_OTHER_NAME;
  {$EXTERNALSYM PCERT_OTHER_NAME}
  _CERT_OTHER_NAME = record
    pszObjId: LPSTR;
    Value: CRYPT_OBJID_BLOB;
  end;
  {$EXTERNALSYM _CERT_OTHER_NAME}
  CERT_OTHER_NAME = _CERT_OTHER_NAME;
  {$EXTERNALSYM CERT_OTHER_NAME}
  TCertOtherName = CERT_OTHER_NAME;
  PCertOtherName = PCERT_OTHER_NAME;

  PCERT_ALT_NAME_ENTRY = ^CERT_ALT_NAME_ENTRY;
  {$EXTERNALSYM PCERT_ALT_NAME_ENTRY}
  _CERT_ALT_NAME_ENTRY = record
    dwAltNameChoice: DWORD;
    //union {
    case Integer of
      0: (pOtherName: PCERT_OTHER_NAME);  // 1
      1: (pwszRfc822Name: LPWSTR);        // 2  (encoded IA5)
      2: (pwszDNSName: LPWSTR);           // 3  (encoded IA5)
      3: ();// Not implemented          x400Address;        // 4
      4: (DirectoryName: CERT_NAME_BLOB); // 5
      5: ();// Not implemented          pEdiPartyName;      // 6
      6: (pwszURL: LPWSTR);               // 7  (encoded IA5)
      7: (IPAddress: CRYPT_DATA_BLOB);    // 8  (Octet String)
      8: (pszRegisteredID: LPSTR);        // 9  (Object Identifer)
  end;
  {$EXTERNALSYM _CERT_ALT_NAME_ENTRY}
  CERT_ALT_NAME_ENTRY = _CERT_ALT_NAME_ENTRY;
  {$EXTERNALSYM CERT_ALT_NAME_ENTRY}
  TCertAltNameEntry = CERT_ALT_NAME_ENTRY;
  PCertAltNameEntry = PCERT_ALT_NAME_ENTRY;

const
  CERT_ALT_NAME_OTHER_NAME     = 1;
  {$EXTERNALSYM CERT_ALT_NAME_OTHER_NAME}
  CERT_ALT_NAME_RFC822_NAME    = 2;
  {$EXTERNALSYM CERT_ALT_NAME_RFC822_NAME}
  CERT_ALT_NAME_DNS_NAME       = 3;
  {$EXTERNALSYM CERT_ALT_NAME_DNS_NAME}
  CERT_ALT_NAME_X400_ADDRESS   = 4;
  {$EXTERNALSYM CERT_ALT_NAME_X400_ADDRESS}
  CERT_ALT_NAME_DIRECTORY_NAME = 5;
  {$EXTERNALSYM CERT_ALT_NAME_DIRECTORY_NAME}
  CERT_ALT_NAME_EDI_PARTY_NAME = 6;
  {$EXTERNALSYM CERT_ALT_NAME_EDI_PARTY_NAME}
  CERT_ALT_NAME_URL            = 7;
  {$EXTERNALSYM CERT_ALT_NAME_URL}
  CERT_ALT_NAME_IP_ADDRESS     = 8;
  {$EXTERNALSYM CERT_ALT_NAME_IP_ADDRESS}
  CERT_ALT_NAME_REGISTERED_ID  = 9;
  {$EXTERNALSYM CERT_ALT_NAME_REGISTERED_ID}

type
  PCERT_ALT_NAME_INFO = ^CERT_ALT_NAME_INFO;
  {$EXTERNALSYM PCERT_ALT_NAME_INFO}
  _CERT_ALT_NAME_INFO = record
    cAltEntry: DWORD;
    rgAltEntry: PCERT_ALT_NAME_ENTRY;
  end;
  {$EXTERNALSYM _CERT_ALT_NAME_INFO}
  CERT_ALT_NAME_INFO = _CERT_ALT_NAME_INFO;
  {$EXTERNALSYM CERT_ALT_NAME_INFO}
  TCertAltNameInfo = CERT_ALT_NAME_INFO;
  PCertAltNameInfo = PCERT_ALT_NAME_INFO;

//+-------------------------------------------------------------------------
//  Alternate name IA5 Error Location Definitions for
//  CRYPT_E_INVALID_IA5_STRING.
//
//  Error location is returned in *pcbEncoded by
//  CryptEncodeObject(X509_ALTERNATE_NAME)
//
//  Error location consists of:
//    ENTRY_INDEX   - 8 bits << 16
//    VALUE_INDEX   - 16 bits (unicode character index)
//--------------------------------------------------------------------------

const
  CERT_ALT_NAME_ENTRY_ERR_INDEX_MASK  = $FF;
  {$EXTERNALSYM CERT_ALT_NAME_ENTRY_ERR_INDEX_MASK}
  CERT_ALT_NAME_ENTRY_ERR_INDEX_SHIFT = 16;
  {$EXTERNALSYM CERT_ALT_NAME_ENTRY_ERR_INDEX_SHIFT}
  CERT_ALT_NAME_VALUE_ERR_INDEX_MASK  = $0000FFFF;
  {$EXTERNALSYM CERT_ALT_NAME_VALUE_ERR_INDEX_MASK}
  CERT_ALT_NAME_VALUE_ERR_INDEX_SHIFT = 0;
  {$EXTERNALSYM CERT_ALT_NAME_VALUE_ERR_INDEX_SHIFT}

function GET_CERT_ALT_NAME_ENTRY_ERR_INDEX(X: DWORD): DWORD;
{$EXTERNALSYM GET_CERT_ALT_NAME_ENTRY_ERR_INDEX}

function GET_CERT_ALT_NAME_VALUE_ERR_INDEX(X: DWORD): DWORD;
{$EXTERNALSYM GET_CERT_ALT_NAME_VALUE_ERR_INDEX}

//+-------------------------------------------------------------------------
//  X509_BASIC_CONSTRAINTS
//  szOID_BASIC_CONSTRAINTS
//
//  pvStructInfo points to following CERT_BASIC_CONSTRAINTS_INFO.
//--------------------------------------------------------------------------

type
  PCERT_BASIC_CONSTRAINTS_INFO = ^CERT_BASIC_CONSTRAINTS_INFO;
  {$EXTERNALSYM PCERT_BASIC_CONSTRAINTS_INFO}
  _CERT_BASIC_CONSTRAINTS_INFO = record
    SubjectType: CRYPT_BIT_BLOB;
    fPathLenConstraint: BOOL;
    dwPathLenConstraint: DWORD;
    cSubtreesConstraint: DWORD;
    rgSubtreesConstraint: PCERT_NAME_BLOB;
  end;
  {$EXTERNALSYM _CERT_BASIC_CONSTRAINTS_INFO}
  CERT_BASIC_CONSTRAINTS_INFO = _CERT_BASIC_CONSTRAINTS_INFO;
  {$EXTERNALSYM CERT_BASIC_CONSTRAINTS_INFO}
  TCertBasicConstraintsInfo = CERT_BASIC_CONSTRAINTS_INFO;
  PCertBasicConstraintsInfo = PCERT_BASIC_CONSTRAINTS_INFO;

const
  CERT_CA_SUBJECT_FLAG         = $80;
  {$EXTERNALSYM CERT_CA_SUBJECT_FLAG}
  CERT_END_ENTITY_SUBJECT_FLAG = $40;
  {$EXTERNALSYM CERT_END_ENTITY_SUBJECT_FLAG}

//+-------------------------------------------------------------------------
//  X509_BASIC_CONSTRAINTS2
//  szOID_BASIC_CONSTRAINTS2
//
//  pvStructInfo points to following CERT_BASIC_CONSTRAINTS2_INFO.
//--------------------------------------------------------------------------

type
  PCERT_BASIC_CONSTRAINTS2_INFO = ^CERT_BASIC_CONSTRAINTS2_INFO;
  {$EXTERNALSYM PCERT_BASIC_CONSTRAINTS2_INFO}
  _CERT_BASIC_CONSTRAINTS2_INFO = record
    fCA: BOOL;
    fPathLenConstraint: BOOL;
    dwPathLenConstraint: DWORD;
  end;
  {$EXTERNALSYM _CERT_BASIC_CONSTRAINTS2_INFO}
  CERT_BASIC_CONSTRAINTS2_INFO = _CERT_BASIC_CONSTRAINTS2_INFO;
  {$EXTERNALSYM CERT_BASIC_CONSTRAINTS2_INFO}
  TCertBasicConstraints2Info = CERT_BASIC_CONSTRAINTS2_INFO;
  PCertBasicConstraints2Info = PCERT_BASIC_CONSTRAINTS2_INFO;

//+-------------------------------------------------------------------------
//  X509_KEY_USAGE
//  szOID_KEY_USAGE
//
//  pvStructInfo points to a CRYPT_BIT_BLOB. Has same bit definitions as
//  CERT_KEY_ATTRIBUTES_INFO's IntendedKeyUsage.
//--------------------------------------------------------------------------

//+-------------------------------------------------------------------------
//  X509_CERT_POLICIES
//  szOID_CERT_POLICIES
//  szOID_CERT_POLICIES_95   NOTE--Only allowed for decoding!!!
//
//  pvStructInfo points to following CERT_POLICIES_INFO.
//
//  NOTE: when decoding using szOID_CERT_POLICIES_95 the pszPolicyIdentifier
//        may contain an empty string
//--------------------------------------------------------------------------

  PCERT_POLICY_QUALIFIER_INFO = ^CERT_POLICY_QUALIFIER_INFO;
  {$EXTERNALSYM PCERT_POLICY_QUALIFIER_INFO}
  _CERT_POLICY_QUALIFIER_INFO = record
    pszPolicyQualifierId: LPSTR; // pszObjId
    Qualifier: CRYPT_OBJID_BLOB; // optional
  end;
  {$EXTERNALSYM _CERT_POLICY_QUALIFIER_INFO}
  CERT_POLICY_QUALIFIER_INFO = _CERT_POLICY_QUALIFIER_INFO;
  {$EXTERNALSYM CERT_POLICY_QUALIFIER_INFO}
  TCertPolicyQualifierInfo = CERT_POLICY_QUALIFIER_INFO;
  PCertPolicyQualifierInfo = PCERT_POLICY_QUALIFIER_INFO;

  PCERT_POLICY_INFO = ^CERT_POLICY_INFO;
  {$EXTERNALSYM PCERT_POLICY_INFO}
  _CERT_POLICY_INFO = record
    pszPolicyIdentifier: LPSTR; // pszObjId
    cPolicyQualifier: DWORD; // optional
    rgPolicyQualifier: PCERT_POLICY_QUALIFIER_INFO;
  end;
  {$EXTERNALSYM _CERT_POLICY_INFO}
  CERT_POLICY_INFO = _CERT_POLICY_INFO;
  {$EXTERNALSYM CERT_POLICY_INFO}
  TCertPolicyInfo = CERT_POLICY_INFO;
  PCertPolicyInfo = PCERT_POLICY_INFO;

  PCERT_POLICIES_INFO = ^CERT_POLICIES_INFO;
  {$EXTERNALSYM PCERT_POLICIES_INFO}
  _CERT_POLICIES_INFO = record
    cPolicyInfo: DWORD;
    rgPolicyInfo: PCERT_POLICY_INFO;
  end;
  {$EXTERNALSYM _CERT_POLICIES_INFO}
  CERT_POLICIES_INFO = _CERT_POLICIES_INFO;
  {$EXTERNALSYM CERT_POLICIES_INFO}
  TCertPoliciesInfo = CERT_POLICIES_INFO;
  PCertPoliciesInfo = PCERT_POLICIES_INFO;

//+-------------------------------------------------------------------------
//  X509_PKIX_POLICY_QUALIFIER_USERNOTICE
//  szOID_PKIX_POLICY_QUALIFIER_USERNOTICE
//
//  pvStructInfo points to following CERT_POLICY_QUALIFIER_USER_NOTICE.
//
//--------------------------------------------------------------------------

  PCERT_POLICY_QUALIFIER_NOTICE_REFERENCE = ^CERT_POLICY_QUALIFIER_NOTICE_REFERENCE;
  {$EXTERNALSYM PCERT_POLICY_QUALIFIER_NOTICE_REFERENCE}
  _CERT_POLICY_QUALIFIER_NOTICE_REFERENCE = record
    pszOrganization: LPSTR;
    cNoticeNumbers: DWORD;
    rgNoticeNumbers: LPINT;
  end;
  {$EXTERNALSYM _CERT_POLICY_QUALIFIER_NOTICE_REFERENCE}
  CERT_POLICY_QUALIFIER_NOTICE_REFERENCE = _CERT_POLICY_QUALIFIER_NOTICE_REFERENCE;
  {$EXTERNALSYM CERT_POLICY_QUALIFIER_NOTICE_REFERENCE}
  TCertPolicyQualifierNoticeReference = CERT_POLICY_QUALIFIER_NOTICE_REFERENCE;
  PCertPolicyQualifierNoticeReference = PCERT_POLICY_QUALIFIER_NOTICE_REFERENCE;

  PCERT_POLICY_QUALIFIER_USER_NOTICE = ^CERT_POLICY_QUALIFIER_USER_NOTICE;
  {$EXTERNALSYM PCERT_POLICY_QUALIFIER_USER_NOTICE}
  _CERT_POLICY_QUALIFIER_USER_NOTICE = record
    pNoticeReference: PCERT_POLICY_QUALIFIER_NOTICE_REFERENCE; // optional
    pszDisplayText: LPWSTR; // optional
  end;
  {$EXTERNALSYM _CERT_POLICY_QUALIFIER_USER_NOTICE}
  CERT_POLICY_QUALIFIER_USER_NOTICE = _CERT_POLICY_QUALIFIER_USER_NOTICE;
  {$EXTERNALSYM CERT_POLICY_QUALIFIER_USER_NOTICE}
  TCertPolicyQualifierUserNotice = CERT_POLICY_QUALIFIER_USER_NOTICE;
  PCertPolicyQualifierUserNotice = PCERT_POLICY_QUALIFIER_USER_NOTICE;

//+-------------------------------------------------------------------------
//  szOID_CERT_POLICIES_95_QUALIFIER1 - Decode Only!!!!
//
//  pvStructInfo points to following CERT_POLICY95_QUALIFIER1.
//
//--------------------------------------------------------------------------

  PCPS_URLS = ^CPS_URLS;
  {$EXTERNALSYM PCPS_URLS}
  _CPS_URLS = record
    pszURL: LPWSTR;
    pAlgorithm: PCRYPT_ALGORITHM_IDENTIFIER; // optional
    pDigest: PCRYPT_DATA_BLOB; // optional
  end;
  {$EXTERNALSYM _CPS_URLS}
  CPS_URLS = _CPS_URLS;
  {$EXTERNALSYM CPS_URLS}
  TCpsUrls = CPS_URLS;
  PCpsUrls = PCPS_URLS;

  PCERT_POLICY95_QUALIFIER1 = ^CERT_POLICY95_QUALIFIER1;
  {$EXTERNALSYM PCERT_POLICY95_QUALIFIER1}
  _CERT_POLICY95_QUALIFIER1 = record
    pszPracticesReference: LPWSTR; // optional
    pszNoticeIdentifier: LPSTR; // optional
    pszNSINoticeIdentifier: LPSTR; // optional
    cCPSURLs: DWORD;
    rgCPSURLs: PCPS_URLS; // optional
  end;
  {$EXTERNALSYM _CERT_POLICY95_QUALIFIER1}
  CERT_POLICY95_QUALIFIER1 = _CERT_POLICY95_QUALIFIER1;
  {$EXTERNALSYM CERT_POLICY95_QUALIFIER1}
  TCertPolicy95Qualifier1 = CERT_POLICY95_QUALIFIER1;
  PCertPolicy95Qualifier1 = PCERT_POLICY95_QUALIFIER1;

//+-------------------------------------------------------------------------
//  RSA_CSP_PUBLICKEYBLOB
//
//  pvStructInfo points to a PUBLICKEYSTRUC immediately followed by a
//  RSAPUBKEY and the modulus bytes.
//
//  CryptExportKey outputs the above StructInfo for a dwBlobType of
//  PUBLICKEYBLOB. CryptImportKey expects the above StructInfo when
//  importing a public key.
//
//  For dwCertEncodingType = X509_ASN_ENCODING, the RSA_CSP_PUBLICKEYBLOB is
//  encoded as a PKCS #1 RSAPublicKey consisting of a SEQUENCE of a
//  modulus INTEGER and a publicExponent INTEGER. The modulus is encoded
//  as being a unsigned integer. When decoded, if the modulus was encoded
//  as unsigned integer with a leading 0 byte, the 0 byte is removed before
//  converting to the CSP modulus bytes.
//
//  For decode, the aiKeyAlg field of PUBLICKEYSTRUC is always set to
//  CALG_RSA_KEYX.
//--------------------------------------------------------------------------

//+-------------------------------------------------------------------------
//  X509_KEYGEN_REQUEST_TO_BE_SIGNED
//
//  pvStructInfo points to CERT_KEYGEN_REQUEST_INFO.
//
//  For CryptDecodeObject(), the pbEncoded is the "to be signed" plus its
//  signature (output of a X509_CERT CryptEncodeObject()).
//
//  For CryptEncodeObject(), the pbEncoded is just the "to be signed".
//--------------------------------------------------------------------------

//+-------------------------------------------------------------------------
//  PKCS_ATTRIBUTE data structure
//
//  pvStructInfo points to a CRYPT_ATTRIBUTE.
//--------------------------------------------------------------------------

//+-------------------------------------------------------------------------
//  PKCS_ATTRIBUTES data structure
//
//  pvStructInfo points to a CRYPT_ATTRIBUTES.
//--------------------------------------------------------------------------

//+-------------------------------------------------------------------------
//  PKCS_CONTENT_INFO_SEQUENCE_OF_ANY data structure
//
//  pvStructInfo points to following CRYPT_CONTENT_INFO_SEQUENCE_OF_ANY.
//
//  For X509_ASN_ENCODING: encoded as a PKCS#7 ContentInfo structure wrapping
//  a sequence of ANY. The value of the contentType field is pszObjId,
//  while the content field is the following structure:
//      SequenceOfAny ::= SEQUENCE OF ANY
//
//  The CRYPT_DER_BLOBs point to the already encoded ANY content.
//--------------------------------------------------------------------------

  PCRYPT_CONTENT_INFO_SEQUENCE_OF_ANY = ^CRYPT_CONTENT_INFO_SEQUENCE_OF_ANY;
  {$EXTERNALSYM PCRYPT_CONTENT_INFO_SEQUENCE_OF_ANY}
  _CRYPT_CONTENT_INFO_SEQUENCE_OF_ANY = record
    pszObjId: LPSTR;
    cValue: DWORD;
    rgValue: PCRYPT_DER_BLOB;
  end;
  {$EXTERNALSYM _CRYPT_CONTENT_INFO_SEQUENCE_OF_ANY}
  CRYPT_CONTENT_INFO_SEQUENCE_OF_ANY = _CRYPT_CONTENT_INFO_SEQUENCE_OF_ANY;
  {$EXTERNALSYM CRYPT_CONTENT_INFO_SEQUENCE_OF_ANY}
  TCryptContentInfoSequenceOfAny = CRYPT_CONTENT_INFO_SEQUENCE_OF_ANY;
  PCryptContentInfoSequenceOfAny = PCRYPT_CONTENT_INFO_SEQUENCE_OF_ANY;

//+-------------------------------------------------------------------------
//  PKCS_CONTENT_INFO data structure
//
//  pvStructInfo points to following CRYPT_CONTENT_INFO.
//
//  For X509_ASN_ENCODING: encoded as a PKCS#7 ContentInfo structure.
//  The CRYPT_DER_BLOB points to the already encoded ANY content.
//--------------------------------------------------------------------------

  PCRYPT_CONTENT_INFO = ^CRYPT_CONTENT_INFO;
  {$EXTERNALSYM PCRYPT_CONTENT_INFO}
  _CRYPT_CONTENT_INFO = record
    pszObjId: LPSTR;
    Content: CRYPT_DER_BLOB;
  end;
  {$EXTERNALSYM _CRYPT_CONTENT_INFO}
  CRYPT_CONTENT_INFO = _CRYPT_CONTENT_INFO;
  {$EXTERNALSYM CRYPT_CONTENT_INFO}
  TCryptContentInfo = CRYPT_CONTENT_INFO;
  PCryptContentInfo = PCRYPT_CONTENT_INFO;

//+-------------------------------------------------------------------------
//  X509_OCTET_STRING data structure
//
//  pvStructInfo points to a CRYPT_DATA_BLOB.
//--------------------------------------------------------------------------

//+-------------------------------------------------------------------------
//  X509_BITS data structure
//
//  pvStructInfo points to a CRYPT_BIT_BLOB.
//--------------------------------------------------------------------------

//+-------------------------------------------------------------------------
//  X509_BITS_WITHOUT_TRAILING_ZEROES data structure
//
//  pvStructInfo points to a CRYPT_BIT_BLOB.
//
//  The same as X509_BITS, except before encoding, the bit length is
//  decremented to exclude trailing zero bits.
//--------------------------------------------------------------------------

//+-------------------------------------------------------------------------
//  X509_INTEGER data structure
//
//  pvStructInfo points to an int.
//--------------------------------------------------------------------------

//+-------------------------------------------------------------------------
//  X509_MULTI_BYTE_INTEGER data structure
//
//  pvStructInfo points to a CRYPT_INTEGER_BLOB.
//--------------------------------------------------------------------------

//+-------------------------------------------------------------------------
//  X509_ENUMERATED data structure
//
//  pvStructInfo points to an int containing the enumerated value
//--------------------------------------------------------------------------

//+-------------------------------------------------------------------------
//  X509_CHOICE_OF_TIME data structure
//
//  pvStructInfo points to a FILETIME.
//--------------------------------------------------------------------------

//+-------------------------------------------------------------------------
//  X509_SEQUENCE_OF_ANY data structure
//
//  pvStructInfo points to following CRYPT_SEQUENCE_OF_ANY.
//
//  The CRYPT_DER_BLOBs point to the already encoded ANY content.
//--------------------------------------------------------------------------

  PCRYPT_SEQUENCE_OF_ANY = ^CRYPT_SEQUENCE_OF_ANY;
  {$EXTERNALSYM PCRYPT_SEQUENCE_OF_ANY}
  _CRYPT_SEQUENCE_OF_ANY = record
    cValue: DWORD;
    rgValue: PCRYPT_DER_BLOB;
  end;
  {$EXTERNALSYM _CRYPT_SEQUENCE_OF_ANY}
  CRYPT_SEQUENCE_OF_ANY = _CRYPT_SEQUENCE_OF_ANY;
  {$EXTERNALSYM CRYPT_SEQUENCE_OF_ANY}
  TCryptSequenceOfAny = CRYPT_SEQUENCE_OF_ANY;
  PCryptSequenceOfAny = PCRYPT_SEQUENCE_OF_ANY;

//+-------------------------------------------------------------------------
//  X509_AUTHORITY_KEY_ID2
//  szOID_AUTHORITY_KEY_IDENTIFIER2
//
//  pvStructInfo points to following CERT_AUTHORITY_KEY_ID2_INFO.
//
//  For CRYPT_E_INVALID_IA5_STRING, the error location is returned in
//  *pcbEncoded by CryptEncodeObject(X509_AUTHORITY_KEY_ID2)
//
//  See X509_ALTERNATE_NAME for error location defines.
//--------------------------------------------------------------------------

  PCERT_AUTHORITY_KEY_ID2_INFO = ^CERT_AUTHORITY_KEY_ID2_INFO;
  {$EXTERNALSYM PCERT_AUTHORITY_KEY_ID2_INFO}
  _CERT_AUTHORITY_KEY_ID2_INFO = record
    KeyId: CRYPT_DATA_BLOB;
    AuthorityCertIssuer: CERT_ALT_NAME_INFO; // Optional, set cAltEntry
    // to 0 to omit.
    AuthorityCertSerialNumber: CRYPT_INTEGER_BLOB;
  end;
  {$EXTERNALSYM _CERT_AUTHORITY_KEY_ID2_INFO}
  CERT_AUTHORITY_KEY_ID2_INFO = _CERT_AUTHORITY_KEY_ID2_INFO;
  {$EXTERNALSYM CERT_AUTHORITY_KEY_ID2_INFO}
  TCertAuthorityKeyId2Info = CERT_AUTHORITY_KEY_ID2_INFO;
  PCertAuthorityKeyId2Info = PCERT_AUTHORITY_KEY_ID2_INFO;

//+-------------------------------------------------------------------------
//  szOID_SUBJECT_KEY_IDENTIFIER
//
//  pvStructInfo points to a CRYPT_DATA_BLOB.
//--------------------------------------------------------------------------

//+-------------------------------------------------------------------------
//  X509_AUTHORITY_INFO_ACCESS
//  szOID_AUTHORITY_INFO_ACCESS
//
//  pvStructInfo points to following CERT_AUTHORITY_INFO_ACCESS.
//
//  For CRYPT_E_INVALID_IA5_STRING, the error location is returned in
//  *pcbEncoded by CryptEncodeObject(X509_AUTHORITY_INFO_ACCESS)
//
//  Error location consists of:
//    ENTRY_INDEX   - 8 bits << 16
//    VALUE_INDEX   - 16 bits (unicode character index)
//
//  See X509_ALTERNATE_NAME for ENTRY_INDEX and VALUE_INDEX error location
//  defines.
//--------------------------------------------------------------------------

  PCERT_ACCESS_DESCRIPTION = ^CERT_ACCESS_DESCRIPTION;
  {$EXTERNALSYM PCERT_ACCESS_DESCRIPTION}
  _CERT_ACCESS_DESCRIPTION = record
    pszAccessMethod: LPSTR; // pszObjId
    AccessLocation: CERT_ALT_NAME_ENTRY;
  end;
  {$EXTERNALSYM _CERT_ACCESS_DESCRIPTION}
  CERT_ACCESS_DESCRIPTION = _CERT_ACCESS_DESCRIPTION;
  {$EXTERNALSYM CERT_ACCESS_DESCRIPTION}
  TCertAccessDescription = CERT_ACCESS_DESCRIPTION;
  PCertAccessDescription = PCERT_ACCESS_DESCRIPTION;

  PCERT_AUTHORITY_INFO_ACCESS = ^CERT_AUTHORITY_INFO_ACCESS;
  {$EXTERNALSYM PCERT_AUTHORITY_INFO_ACCESS}
  _CERT_AUTHORITY_INFO_ACCESS = record
    cAccDescr: DWORD;
    rgAccDescr: PCERT_ACCESS_DESCRIPTION;
  end;
  {$EXTERNALSYM _CERT_AUTHORITY_INFO_ACCESS}
  CERT_AUTHORITY_INFO_ACCESS = _CERT_AUTHORITY_INFO_ACCESS;
  {$EXTERNALSYM CERT_AUTHORITY_INFO_ACCESS}
  TCertAuthorityInfoAccess = CERT_AUTHORITY_INFO_ACCESS;
  PCertAuthorityInfoAccess = PCERT_AUTHORITY_INFO_ACCESS;

//+-------------------------------------------------------------------------
//  PKIX Access Description: Access Method Object Identifiers
//--------------------------------------------------------------------------

const
  szOID_PKIX_ACC_DESCR  = '1.3.6.1.5.5.7.48';
  {$EXTERNALSYM szOID_PKIX_ACC_DESCR}
  szOID_PKIX_OCSP       = '1.3.6.1.5.5.7.48.1';
  {$EXTERNALSYM szOID_PKIX_OCSP}
  szOID_PKIX_CA_ISSUERS = '1.3.6.1.5.5.7.48.2';
  {$EXTERNALSYM szOID_PKIX_CA_ISSUERS}

//+-------------------------------------------------------------------------
//  X509_CRL_REASON_CODE
//  szOID_CRL_REASON_CODE
//
//  pvStructInfo points to an int which can be set to one of the following
//  enumerated values:
//--------------------------------------------------------------------------

  CRL_REASON_UNSPECIFIED            = 0;
  {$EXTERNALSYM CRL_REASON_UNSPECIFIED}
  CRL_REASON_KEY_COMPROMISE         = 1;
  {$EXTERNALSYM CRL_REASON_KEY_COMPROMISE}
  CRL_REASON_CA_COMPROMISE          = 2;
  {$EXTERNALSYM CRL_REASON_CA_COMPROMISE}
  CRL_REASON_AFFILIATION_CHANGED    = 3;
  {$EXTERNALSYM CRL_REASON_AFFILIATION_CHANGED}
  CRL_REASON_SUPERSEDED             = 4;
  {$EXTERNALSYM CRL_REASON_SUPERSEDED}
  CRL_REASON_CESSATION_OF_OPERATION = 5;
  {$EXTERNALSYM CRL_REASON_CESSATION_OF_OPERATION}
  CRL_REASON_CERTIFICATE_HOLD       = 6;
  {$EXTERNALSYM CRL_REASON_CERTIFICATE_HOLD}
  CRL_REASON_REMOVE_FROM_CRL        = 8;
  {$EXTERNALSYM CRL_REASON_REMOVE_FROM_CRL}

//+-------------------------------------------------------------------------
//  X509_CRL_DIST_POINTS
//  szOID_CRL_DIST_POINTS
//
//  pvStructInfo points to following CRL_DIST_POINTS_INFO.
//
//  For CRYPT_E_INVALID_IA5_STRING, the error location is returned in
//  *pcbEncoded by CryptEncodeObject(X509_CRL_DIST_POINTS)
//
//  Error location consists of:
//    CRL_ISSUER_BIT    - 1 bit  << 31 (0 for FullName, 1 for CRLIssuer)
//    POINT_INDEX       - 7 bits << 24
//    ENTRY_INDEX       - 8 bits << 16
//    VALUE_INDEX       - 16 bits (unicode character index)
//
//  See X509_ALTERNATE_NAME for ENTRY_INDEX and VALUE_INDEX error location
//  defines.
//--------------------------------------------------------------------------

type
  PCRL_DIST_POINT_NAME = ^CRL_DIST_POINT_NAME;
  {$EXTERNALSYM PCRL_DIST_POINT_NAME}
  _CRL_DIST_POINT_NAME = record
    dwDistPointNameChoice: DWORD;
    case Integer of
      0: (FullName: CERT_ALT_NAME_INFO); // 1
      1: ();// Not implemented      IssuerRDN;      // 2
  end;
  {$EXTERNALSYM _CRL_DIST_POINT_NAME}
  CRL_DIST_POINT_NAME = _CRL_DIST_POINT_NAME;
  {$EXTERNALSYM CRL_DIST_POINT_NAME}
  TCrlDistPointName = CRL_DIST_POINT_NAME;
  PCrlDistPointName = PCRL_DIST_POINT_NAME;

const
  CRL_DIST_POINT_NO_NAME         = 0;
  {$EXTERNALSYM CRL_DIST_POINT_NO_NAME}
  CRL_DIST_POINT_FULL_NAME       = 1;
  {$EXTERNALSYM CRL_DIST_POINT_FULL_NAME}
  CRL_DIST_POINT_ISSUER_RDN_NAME = 2;
  {$EXTERNALSYM CRL_DIST_POINT_ISSUER_RDN_NAME}

type
  PCRL_DIST_POINT = ^CRL_DIST_POINT;
  {$EXTERNALSYM PCRL_DIST_POINT}
  _CRL_DIST_POINT = record
    DistPointName: CRL_DIST_POINT_NAME; // OPTIONAL
    ReasonFlags: CRYPT_BIT_BLOB; // OPTIONAL
    CRLIssuer: CERT_ALT_NAME_INFO; // OPTIONAL
  end;
  {$EXTERNALSYM _CRL_DIST_POINT}
  CRL_DIST_POINT = _CRL_DIST_POINT;
  {$EXTERNALSYM CRL_DIST_POINT}
  TCrlDistPoint = CRL_DIST_POINT;
  PCrlDistPoint = PCRL_DIST_POINT;

const
  CRL_REASON_UNUSED_FLAG                 = $80;
  {$EXTERNALSYM CRL_REASON_UNUSED_FLAG}
  CRL_REASON_KEY_COMPROMISE_FLAG         = $40;
  {$EXTERNALSYM CRL_REASON_KEY_COMPROMISE_FLAG}
  CRL_REASON_CA_COMPROMISE_FLAG          = $20;
  {$EXTERNALSYM CRL_REASON_CA_COMPROMISE_FLAG}
  CRL_REASON_AFFILIATION_CHANGED_FLAG    = $10;
  {$EXTERNALSYM CRL_REASON_AFFILIATION_CHANGED_FLAG}
  CRL_REASON_SUPERSEDED_FLAG             = $08;
  {$EXTERNALSYM CRL_REASON_SUPERSEDED_FLAG}
  CRL_REASON_CESSATION_OF_OPERATION_FLAG = $04;
  {$EXTERNALSYM CRL_REASON_CESSATION_OF_OPERATION_FLAG}
  CRL_REASON_CERTIFICATE_HOLD_FLAG       = $02;
  {$EXTERNALSYM CRL_REASON_CERTIFICATE_HOLD_FLAG}

type
  PCRL_DIST_POINTS_INFO = ^CRL_DIST_POINTS_INFO;
  {$EXTERNALSYM PCRL_DIST_POINTS_INFO}
  _CRL_DIST_POINTS_INFO = record
    cDistPoint: DWORD;
    rgDistPoint: PCRL_DIST_POINT;
  end;
  {$EXTERNALSYM _CRL_DIST_POINTS_INFO}
  CRL_DIST_POINTS_INFO = _CRL_DIST_POINTS_INFO;
  {$EXTERNALSYM CRL_DIST_POINTS_INFO}
  TCrlDistPointsInfo = CRL_DIST_POINTS_INFO;
  PCrlDistPointsInfo = PCRL_DIST_POINTS_INFO;

const
  CRL_DIST_POINT_ERR_INDEX_MASK   = $7F;
  {$EXTERNALSYM CRL_DIST_POINT_ERR_INDEX_MASK}
  CRL_DIST_POINT_ERR_INDEX_SHIFT  = 24;
  {$EXTERNALSYM CRL_DIST_POINT_ERR_INDEX_SHIFT}

function GET_CRL_DIST_POINT_ERR_INDEX(X: DWORD): DWORD;
{$EXTERNALSYM GET_CRL_DIST_POINT_ERR_INDEX}

const
  CRL_DIST_POINT_ERR_CRL_ISSUER_BIT = DWORD($80000000);
  {$EXTERNALSYM CRL_DIST_POINT_ERR_CRL_ISSUER_BIT}

function IS_CRL_DIST_POINT_ERR_CRL_ISSUER(X: DWORD): Boolean;
{$EXTERNALSYM IS_CRL_DIST_POINT_ERR_CRL_ISSUER}

//+-------------------------------------------------------------------------
//  X509_ENHANCED_KEY_USAGE
//  szOID_ENHANCED_KEY_USAGE
//
//  pvStructInfo points to a CERT_ENHKEY_USAGE, CTL_USAGE.
//--------------------------------------------------------------------------

//+-------------------------------------------------------------------------
//  szOID_NEXT_UPDATE_LOCATION
//
//  pvStructInfo points to a CERT_ALT_NAME_INFO.
//--------------------------------------------------------------------------

//+-------------------------------------------------------------------------
//  PKCS_CTL
//  szOID_CTL
//
//  pvStructInfo points to a CTL_INFO.
//--------------------------------------------------------------------------

//+-------------------------------------------------------------------------
//  PKCS_SORTED_CTL
//
//  pvStructInfo points to a CTL_INFO.
//
//  Same as for PKCS_CTL, except, the CTL entries are sorted. The following
//  extension containing the sort information is inserted as the first
//  extension in the encoded CTL.
//
//  Only supported for Encoding. CRYPT_ENCODE_ALLOC_FLAG flag must be
//  set.
//--------------------------------------------------------------------------


//+-------------------------------------------------------------------------
// Sorted CTL TrustedSubjects extension
//
//  Array of little endian DWORDs:
//   [0] - Flags
//   [1] - Count of HashBucket entry offsets
//   [2] - Maximum HashBucket entry collision count
//   [3 ..] (Count + 1) HashBucket entry offsets
//
//  When this extension is present in the CTL,
//  the ASN.1 encoded sequence of TrustedSubjects are HashBucket ordered.
//
//  The entry offsets point to the start of the first encoded TrustedSubject
//  sequence for the HashBucket. The encoded TrustedSubjects for a HashBucket
//  continue until the encoded offset of the next HashBucket. A HashBucket has
//  no entries if HashBucket[N] == HashBucket[N + 1].
//
//  The HashBucket offsets are from the start of the ASN.1 encoded CTL_INFO.
//--------------------------------------------------------------------------

const
  SORTED_CTL_EXT_FLAGS_OFFSET         = (0*4);
  {$EXTERNALSYM SORTED_CTL_EXT_FLAGS_OFFSET}
  SORTED_CTL_EXT_COUNT_OFFSET         = (1*4);
  {$EXTERNALSYM SORTED_CTL_EXT_COUNT_OFFSET}
  SORTED_CTL_EXT_MAX_COLLISION_OFFSET = (2*4);
  {$EXTERNALSYM SORTED_CTL_EXT_MAX_COLLISION_OFFSET}
  SORTED_CTL_EXT_HASH_BUCKET_OFFSET   = (3*4);
  {$EXTERNALSYM SORTED_CTL_EXT_HASH_BUCKET_OFFSET}

// If the SubjectIdentifiers are a MD5 or SHA1 hash, the following flag is
// set. When set, the first 4 bytes of the SubjectIdentifier are used as
// the dwhash. Otherwise, the SubjectIdentifier bytes are hashed into dwHash.
// In either case the HashBucket index = dwHash % cHashBucket.

  SORTED_CTL_EXT_HASHED_SUBJECT_IDENTIFIER_FLAG = $1;
  {$EXTERNALSYM SORTED_CTL_EXT_HASHED_SUBJECT_IDENTIFIER_FLAG}

//+-------------------------------------------------------------------------
//  X509_MULTI_BYTE_UINT
//
//  pvStructInfo points to a CRYPT_UINT_BLOB. Before encoding, inserts a
//  leading 0x00. After decoding, removes a leading 0x00.
//--------------------------------------------------------------------------

//+-------------------------------------------------------------------------
//  X509_DSS_PUBLICKEY
//
//  pvStructInfo points to a CRYPT_UINT_BLOB.
//--------------------------------------------------------------------------

//+-------------------------------------------------------------------------
//  X509_DSS_PARAMETERS
//
//  pvStructInfo points to following CERT_DSS_PARAMETERS data structure.
//--------------------------------------------------------------------------

type
  PCERT_DSS_PARAMETERS = ^CERT_DSS_PARAMETERS;
  {$EXTERNALSYM PCERT_DSS_PARAMETERS}
  _CERT_DSS_PARAMETERS = record
    p: CRYPT_UINT_BLOB;
    q: CRYPT_UINT_BLOB;
    g: CRYPT_UINT_BLOB;
  end;
  {$EXTERNALSYM _CERT_DSS_PARAMETERS}
  CERT_DSS_PARAMETERS = _CERT_DSS_PARAMETERS;
  {$EXTERNALSYM CERT_DSS_PARAMETERS}
  TCertDssParameters = CERT_DSS_PARAMETERS;
  PCertDssParameters = PCERT_DSS_PARAMETERS;

//+-------------------------------------------------------------------------
//  X509_DSS_SIGNATURE
//
//  pvStructInfo is a BYTE rgbSignature[CERT_DSS_SIGNATURE_LEN]. The
//  bytes are ordered as output by the DSS CSP's CryptSignHash().
//--------------------------------------------------------------------------

const
  CERT_DSS_R_LEN         = 20;
  {$EXTERNALSYM CERT_DSS_R_LEN}
  CERT_DSS_S_LEN         = 20;
  {$EXTERNALSYM CERT_DSS_S_LEN}
  CERT_DSS_SIGNATURE_LEN = (CERT_DSS_R_LEN + CERT_DSS_S_LEN);
  {$EXTERNALSYM CERT_DSS_SIGNATURE_LEN}

// Sequence of 2 unsigned integers (the extra +1 is for a potential leading
// 0x00 to make the integer unsigned)

  CERT_MAX_ASN_ENCODED_DSS_SIGNATURE_LEN = (2 + 2 * (2 + 20 + 1));
  {$EXTERNALSYM CERT_MAX_ASN_ENCODED_DSS_SIGNATURE_LEN}

//+-------------------------------------------------------------------------
//  X509_DH_PUBLICKEY
//
//  pvStructInfo points to a CRYPT_UINT_BLOB.
//--------------------------------------------------------------------------

//+-------------------------------------------------------------------------
//  X509_DH_PARAMETERS
//
//  pvStructInfo points to following CERT_DH_PARAMETERS data structure.
//--------------------------------------------------------------------------

type
  PCERT_DH_PARAMETERS = ^CERT_DH_PARAMETERS;
  {$EXTERNALSYM PCERT_DH_PARAMETERS}
  _CERT_DH_PARAMETERS = record
    p: CRYPT_UINT_BLOB;
    g: CRYPT_UINT_BLOB;
  end;
  {$EXTERNALSYM _CERT_DH_PARAMETERS}
  CERT_DH_PARAMETERS = _CERT_DH_PARAMETERS;
  {$EXTERNALSYM CERT_DH_PARAMETERS}
  TCertDhParameters = CERT_DH_PARAMETERS;
  PCertDhParameters = PCERT_DH_PARAMETERS;

//+-------------------------------------------------------------------------
//  X942_DH_PARAMETERS
//
//  pvStructInfo points to following CERT_X942_DH_PARAMETERS data structure.
//
//  If q.cbData == 0, then, the following fields are zero'ed.
//--------------------------------------------------------------------------

  PCERT_X942_DH_VALIDATION_PARAMS = ^CERT_X942_DH_VALIDATION_PARAMS;
  {$EXTERNALSYM PCERT_X942_DH_VALIDATION_PARAMS}
  _CERT_X942_DH_VALIDATION_PARAMS = record
    seed: CRYPT_BIT_BLOB;
    pgenCounter: DWORD;
  end;
  {$EXTERNALSYM _CERT_X942_DH_VALIDATION_PARAMS}
  CERT_X942_DH_VALIDATION_PARAMS = _CERT_X942_DH_VALIDATION_PARAMS;
  {$EXTERNALSYM CERT_X942_DH_VALIDATION_PARAMS}
  TCertX942DhValidationParams = CERT_X942_DH_VALIDATION_PARAMS;
  PCertX942DhValidationParams = PCERT_X942_DH_VALIDATION_PARAMS;

  PCERT_X942_DH_PARAMETERS = ^CERT_X942_DH_PARAMETERS;
  {$EXTERNALSYM PCERT_X942_DH_PARAMETERS}
  _CERT_X942_DH_PARAMETERS = record
    p: CRYPT_UINT_BLOB; // odd prime, p = jq + 1
    g: CRYPT_UINT_BLOB; // generator, g
    q: CRYPT_UINT_BLOB; // factor of p - 1, OPTIONAL
    j: CRYPT_UINT_BLOB; // subgroup factor, OPTIONAL
    pValidationParams: PCERT_X942_DH_VALIDATION_PARAMS; // OPTIONAL
  end;
  {$EXTERNALSYM _CERT_X942_DH_PARAMETERS}
  CERT_X942_DH_PARAMETERS = _CERT_X942_DH_PARAMETERS;
  {$EXTERNALSYM CERT_X942_DH_PARAMETERS}
  TCertX942DhParameters = CERT_X942_DH_PARAMETERS;
  PCertX942DhParameters = PCERT_X942_DH_PARAMETERS;

//+-------------------------------------------------------------------------
//  X942_OTHER_INFO
//
//  pvStructInfo points to following CRYPT_X942_OTHER_INFO data structure.
//
//  rgbCounter and rgbKeyLength are in Little Endian order.
//--------------------------------------------------------------------------

const
  CRYPT_X942_COUNTER_BYTE_LENGTH    = 4;
  {$EXTERNALSYM CRYPT_X942_COUNTER_BYTE_LENGTH}
  CRYPT_X942_KEY_LENGTH_BYTE_LENGTH = 4;
  {$EXTERNALSYM CRYPT_X942_KEY_LENGTH_BYTE_LENGTH}
  CRYPT_X942_PUB_INFO_BYTE_LENGTH   = (512 div 8);
  {$EXTERNALSYM CRYPT_X942_PUB_INFO_BYTE_LENGTH}

type
  PCRYPT_X942_OTHER_INFO = ^CRYPT_X942_OTHER_INFO;
  {$EXTERNALSYM PCRYPT_X942_OTHER_INFO}
  _CRYPT_X942_OTHER_INFO = record
    pszContentEncryptionObjId: LPSTR;
    rgbCounter: array [0..CRYPT_X942_COUNTER_BYTE_LENGTH - 1] of BYTE;
    rgbKeyLength: array [0..CRYPT_X942_KEY_LENGTH_BYTE_LENGTH - 1] of BYTE;
    PubInfo: CRYPT_DATA_BLOB; // OPTIONAL
  end;
  {$EXTERNALSYM _CRYPT_X942_OTHER_INFO}
  CRYPT_X942_OTHER_INFO = _CRYPT_X942_OTHER_INFO;
  {$EXTERNALSYM CRYPT_X942_OTHER_INFO}
  TCryptX942OtherInfo = CRYPT_X942_OTHER_INFO;
  PCryptX942OtherInfo = PCRYPT_X942_OTHER_INFO;

//+-------------------------------------------------------------------------
//  PKCS_RC2_CBC_PARAMETERS
//  szOID_RSA_RC2CBC
//
//  pvStructInfo points to following CRYPT_RC2_CBC_PARAMETERS data structure.
//--------------------------------------------------------------------------
  PCRYPT_RC2_CBC_PARAMETERS = ^CRYPT_RC2_CBC_PARAMETERS;
  {$EXTERNALSYM PCRYPT_RC2_CBC_PARAMETERS}
  _CRYPT_RC2_CBC_PARAMETERS = record
    dwVersion: DWORD;
    fIV: BOOL; // set if has following IV
    rgbIV: array [0..7] of BYTE;
  end;
  {$EXTERNALSYM _CRYPT_RC2_CBC_PARAMETERS}
  CRYPT_RC2_CBC_PARAMETERS = _CRYPT_RC2_CBC_PARAMETERS;
  {$EXTERNALSYM CRYPT_RC2_CBC_PARAMETERS}
  TCryptRc2CbcParameters = CRYPT_RC2_CBC_PARAMETERS;
  PCryptRc2CbcParameters = PCRYPT_RC2_CBC_PARAMETERS;

const
  CRYPT_RC2_40BIT_VERSION  = 160;
  {$EXTERNALSYM CRYPT_RC2_40BIT_VERSION}
  CRYPT_RC2_56BIT_VERSION  = 52;
  {$EXTERNALSYM CRYPT_RC2_56BIT_VERSION}
  CRYPT_RC2_64BIT_VERSION  = 120;
  {$EXTERNALSYM CRYPT_RC2_64BIT_VERSION}
  CRYPT_RC2_128BIT_VERSION = 58;
  {$EXTERNALSYM CRYPT_RC2_128BIT_VERSION}

//+-------------------------------------------------------------------------
//  PKCS_SMIME_CAPABILITIES
//  szOID_RSA_SMIMECapabilities
//
//  pvStructInfo points to following CRYPT_SMIME_CAPABILITIES data structure.
//
//  Note, for CryptEncodeObject(X509_ASN_ENCODING), Parameters.cbData == 0
//  causes the encoded parameters to be omitted and not encoded as a NULL
//  (05 00) as is done when encoding a CRYPT_ALGORITHM_IDENTIFIER. This
//  is per the SMIME specification for encoding capabilities.
//--------------------------------------------------------------------------

type
  PCRYPT_SMIME_CAPABILITY = ^CRYPT_SMIME_CAPABILITY;
  {$EXTERNALSYM PCRYPT_SMIME_CAPABILITY}
  _CRYPT_SMIME_CAPABILITY = record
    pszObjId: LPSTR;
    Parameters: CRYPT_OBJID_BLOB;
  end;
  {$EXTERNALSYM _CRYPT_SMIME_CAPABILITY}
  CRYPT_SMIME_CAPABILITY = _CRYPT_SMIME_CAPABILITY;
  {$EXTERNALSYM CRYPT_SMIME_CAPABILITY}
  TCryptSmimeCapability = CRYPT_SMIME_CAPABILITY;
  PCryptSmimeCapability = PCRYPT_SMIME_CAPABILITY;

  PCRYPT_SMIME_CAPABILITIES = ^CRYPT_SMIME_CAPABILITIES;
  {$EXTERNALSYM PCRYPT_SMIME_CAPABILITIES}
  _CRYPT_SMIME_CAPABILITIES = record
    cCapability: DWORD;
    rgCapability: PCRYPT_SMIME_CAPABILITY;
  end;
  {$EXTERNALSYM _CRYPT_SMIME_CAPABILITIES}
  CRYPT_SMIME_CAPABILITIES = _CRYPT_SMIME_CAPABILITIES;
  {$EXTERNALSYM CRYPT_SMIME_CAPABILITIES}
  TCryptSmimeCapabilities = CRYPT_SMIME_CAPABILITIES;
  PCryptSmimeCapabilities = PCRYPT_SMIME_CAPABILITIES;

//+-------------------------------------------------------------------------
//  PKCS7_SIGNER_INFO
//
//  pvStructInfo points to CMSG_SIGNER_INFO.
//--------------------------------------------------------------------------

//+-------------------------------------------------------------------------
//  CMS_SIGNER_INFO
//
//  pvStructInfo points to CMSG_CMS_SIGNER_INFO.
//--------------------------------------------------------------------------


//+-------------------------------------------------------------------------
//  Netscape Certificate Extension Object Identifiers
//--------------------------------------------------------------------------

const
  szOID_NETSCAPE                   = '2.16.840.1.113730';
  {$EXTERNALSYM szOID_NETSCAPE}
  szOID_NETSCAPE_CERT_EXTENSION    = '2.16.840.1.113730.1';
  {$EXTERNALSYM szOID_NETSCAPE_CERT_EXTENSION}
  szOID_NETSCAPE_CERT_TYPE         = '2.16.840.1.113730.1.1';
  {$EXTERNALSYM szOID_NETSCAPE_CERT_TYPE}
  szOID_NETSCAPE_BASE_URL          = '2.16.840.1.113730.1.2';
  {$EXTERNALSYM szOID_NETSCAPE_BASE_URL}
  szOID_NETSCAPE_REVOCATION_URL    = '2.16.840.1.113730.1.3';
  {$EXTERNALSYM szOID_NETSCAPE_REVOCATION_URL}
  szOID_NETSCAPE_CA_REVOCATION_URL = '2.16.840.1.113730.1.4';
  {$EXTERNALSYM szOID_NETSCAPE_CA_REVOCATION_URL}
  szOID_NETSCAPE_CERT_RENEWAL_URL  = '2.16.840.1.113730.1.7';
  {$EXTERNALSYM szOID_NETSCAPE_CERT_RENEWAL_URL}
  szOID_NETSCAPE_CA_POLICY_URL     = '2.16.840.1.113730.1.8';
  {$EXTERNALSYM szOID_NETSCAPE_CA_POLICY_URL}
  szOID_NETSCAPE_SSL_SERVER_NAME   = '2.16.840.1.113730.1.12';
  {$EXTERNALSYM szOID_NETSCAPE_SSL_SERVER_NAME}
  szOID_NETSCAPE_COMMENT           = '2.16.840.1.113730.1.13';
  {$EXTERNALSYM szOID_NETSCAPE_COMMENT}

//+-------------------------------------------------------------------------
//  Netscape Certificate Data Type Object Identifiers
//--------------------------------------------------------------------------

  szOID_NETSCAPE_DATA_TYPE     = '2.16.840.1.113730.2';
  {$EXTERNALSYM szOID_NETSCAPE_DATA_TYPE}
  szOID_NETSCAPE_CERT_SEQUENCE = '2.16.840.1.113730.2.5';
  {$EXTERNALSYM szOID_NETSCAPE_CERT_SEQUENCE}

//+-------------------------------------------------------------------------
//  szOID_NETSCAPE_CERT_TYPE extension
//
//  Its value is a bit string. CryptDecodeObject/CryptEncodeObject using
//  X509_BITS or X509_BITS_WITHOUT_TRAILING_ZEROES.
//
//  The following bits are defined:
//--------------------------------------------------------------------------

  NETSCAPE_SSL_CLIENT_AUTH_CERT_TYPE = $80;
  {$EXTERNALSYM NETSCAPE_SSL_CLIENT_AUTH_CERT_TYPE}
  NETSCAPE_SSL_SERVER_AUTH_CERT_TYPE = $40;
  {$EXTERNALSYM NETSCAPE_SSL_SERVER_AUTH_CERT_TYPE}
  NETSCAPE_SMIME_CERT_TYPE           = $20;
  {$EXTERNALSYM NETSCAPE_SMIME_CERT_TYPE}
  NETSCAPE_SIGN_CERT_TYPE            = $10;
  {$EXTERNALSYM NETSCAPE_SIGN_CERT_TYPE}
  NETSCAPE_SSL_CA_CERT_TYPE          = $04;
  {$EXTERNALSYM NETSCAPE_SSL_CA_CERT_TYPE}
  NETSCAPE_SMIME_CA_CERT_TYPE        = $02;
  {$EXTERNALSYM NETSCAPE_SMIME_CA_CERT_TYPE}
  NETSCAPE_SIGN_CA_CERT_TYPE         = $01;
  {$EXTERNALSYM NETSCAPE_SIGN_CA_CERT_TYPE}

//+-------------------------------------------------------------------------
//  szOID_NETSCAPE_BASE_URL extension
//
//  Its value is an IA5_STRING. CryptDecodeObject/CryptEncodeObject using
//  X509_ANY_STRING or X509_UNICODE_ANY_STRING, where,
//  dwValueType = CERT_RDN_IA5_STRING.
//
//  When present this string is added to the beginning of all relative URLs
//  in the certificate.  This extension can be considered an optimization
//  to reduce the size of the URL extensions.
//--------------------------------------------------------------------------

//+-------------------------------------------------------------------------
//  szOID_NETSCAPE_REVOCATION_URL extension
//
//  Its value is an IA5_STRING. CryptDecodeObject/CryptEncodeObject using
//  X509_ANY_STRING or X509_UNICODE_ANY_STRING, where,
//  dwValueType = CERT_RDN_IA5_STRING.
//
//  It is a relative or absolute URL that can be used to check the
//  revocation status of a certificate. The revocation check will be
//  performed as an HTTP GET method using a url that is the concatenation of
//  revocation-url and certificate-serial-number.
//  Where the certificate-serial-number is encoded as a string of
//  ascii hexadecimal digits. For example, if the netscape-base-url is
//  https://www.certs-r-us.com/, the netscape-revocation-url is
//  cgi-bin/check-rev.cgi?, and the certificate serial number is 173420,
//  the resulting URL would be:
//  https://www.certs-r-us.com/cgi-bin/check-rev.cgi?02a56c
//
//  The server should return a document with a Content-Type of
//  application/x-netscape-revocation.  The document should contain
//  a single ascii digit, '1' if the certificate is not curently valid,
//  and '0' if it is curently valid.
//
//  Note: for all of the URLs that include the certificate serial number,
//  the serial number will be encoded as a string which consists of an even
//  number of hexadecimal digits.  If the number of significant digits is odd,
//  the string will have a single leading zero to ensure an even number of
//  digits is generated.
//--------------------------------------------------------------------------

//+-------------------------------------------------------------------------
//  szOID_NETSCAPE_CA_REVOCATION_URL extension
//
//  Its value is an IA5_STRING. CryptDecodeObject/CryptEncodeObject using
//  X509_ANY_STRING or X509_UNICODE_ANY_STRING, where,
//  dwValueType = CERT_RDN_IA5_STRING.
//
//  It is a relative or absolute URL that can be used to check the
//  revocation status of any certificates that are signed by the CA that
//  this certificate belongs to. This extension is only valid in CA
//  certificates.  The use of this extension is the same as the above
//  szOID_NETSCAPE_REVOCATION_URL extension.
//--------------------------------------------------------------------------

//+-------------------------------------------------------------------------
//  szOID_NETSCAPE_CERT_RENEWAL_URL extension
//
//  Its value is an IA5_STRING. CryptDecodeObject/CryptEncodeObject using
//  X509_ANY_STRING or X509_UNICODE_ANY_STRING, where,
//  dwValueType = CERT_RDN_IA5_STRING.
//
//  It is a relative or absolute URL that points to a certificate renewal
//  form. The renewal form will be accessed with an HTTP GET method using a
//  url that is the concatenation of renewal-url and
//  certificate-serial-number. Where the certificate-serial-number is
//  encoded as a string of ascii hexadecimal digits. For example, if the
//  netscape-base-url is https://www.certs-r-us.com/, the
//  netscape-cert-renewal-url is cgi-bin/check-renew.cgi?, and the
//  certificate serial number is 173420, the resulting URL would be:
//  https://www.certs-r-us.com/cgi-bin/check-renew.cgi?02a56c
//  The document returned should be an HTML form that will allow the user
//  to request a renewal of their certificate.
//--------------------------------------------------------------------------

//+-------------------------------------------------------------------------
//  szOID_NETSCAPE_CA_POLICY_URL extension
//
//  Its value is an IA5_STRING. CryptDecodeObject/CryptEncodeObject using
//  X509_ANY_STRING or X509_UNICODE_ANY_STRING, where,
//  dwValueType = CERT_RDN_IA5_STRING.
//
//  It is a relative or absolute URL that points to a web page that
//  describes the policies under which the certificate was issued.
//--------------------------------------------------------------------------

//+-------------------------------------------------------------------------
//  szOID_NETSCAPE_SSL_SERVER_NAME extension
//
//  Its value is an IA5_STRING. CryptDecodeObject/CryptEncodeObject using
//  X509_ANY_STRING or X509_UNICODE_ANY_STRING, where,
//  dwValueType = CERT_RDN_IA5_STRING.
//
//  It is a "shell expression" that can be used to match the hostname of the
//  SSL server that is using this certificate.  It is recommended that if
//  the server's hostname does not match this pattern the user be notified
//  and given the option to terminate the SSL connection.  If this extension
//  is not present then the CommonName in the certificate subject's
//  distinguished name is used for the same purpose.
//--------------------------------------------------------------------------

//+-------------------------------------------------------------------------
//  szOID_NETSCAPE_COMMENT extension
//
//  Its value is an IA5_STRING. CryptDecodeObject/CryptEncodeObject using
//  X509_ANY_STRING or X509_UNICODE_ANY_STRING, where,
//  dwValueType = CERT_RDN_IA5_STRING.
//
//  It is a comment that may be displayed to the user when the certificate
//  is viewed.
//--------------------------------------------------------------------------

//+-------------------------------------------------------------------------
//  szOID_NETSCAPE_CERT_SEQUENCE
//
//  Its value is a PKCS#7 ContentInfo structure wrapping a sequence of
//  certificates. The value of the contentType field is
//  szOID_NETSCAPE_CERT_SEQUENCE, while the content field is the following
//  structure:
//      CertificateSequence ::= SEQUENCE OF Certificate.
//
//  CryptDecodeObject/CryptEncodeObject using
//  PKCS_CONTENT_INFO_SEQUENCE_OF_ANY, where,
//  pszObjId = szOID_NETSCAPE_CERT_SEQUENCE and the CRYPT_DER_BLOBs point
//  to encoded X509 certificates.
//--------------------------------------------------------------------------


//+=========================================================================
//  Object IDentifier (OID) Installable Functions:  Data Structures and APIs
//==========================================================================

type
  HCRYPTOIDFUNCSET = Pointer;
  {$EXTERNALSYM HCRYPTOIDFUNCSET}
  HCRYPTOIDFUNCADDR = Pointer;
  {$EXTERNALSYM HCRYPTOIDFUNCADDR}

// Predefined OID Function Names

const
  CRYPT_OID_ENCODE_OBJECT_FUNC       = 'CryptDllEncodeObject';
  {$EXTERNALSYM CRYPT_OID_ENCODE_OBJECT_FUNC}
  CRYPT_OID_DECODE_OBJECT_FUNC       = 'CryptDllDecodeObject';
  {$EXTERNALSYM CRYPT_OID_DECODE_OBJECT_FUNC}
  CRYPT_OID_ENCODE_OBJECT_EX_FUNC    = 'CryptDllEncodeObjectEx';
  {$EXTERNALSYM CRYPT_OID_ENCODE_OBJECT_EX_FUNC}
  CRYPT_OID_DECODE_OBJECT_EX_FUNC    = 'CryptDllDecodeObjectEx';
  {$EXTERNALSYM CRYPT_OID_DECODE_OBJECT_EX_FUNC}
  CRYPT_OID_CREATE_COM_OBJECT_FUNC   = 'CryptDllCreateCOMObject';
  {$EXTERNALSYM CRYPT_OID_CREATE_COM_OBJECT_FUNC}
  CRYPT_OID_VERIFY_REVOCATION_FUNC   = 'CertDllVerifyRevocation';
  {$EXTERNALSYM CRYPT_OID_VERIFY_REVOCATION_FUNC}
  CRYPT_OID_VERIFY_CTL_USAGE_FUNC    = 'CertDllVerifyCTLUsage';
  {$EXTERNALSYM CRYPT_OID_VERIFY_CTL_USAGE_FUNC}
  CRYPT_OID_FORMAT_OBJECT_FUNC       = 'CryptDllFormatObject';
  {$EXTERNALSYM CRYPT_OID_FORMAT_OBJECT_FUNC}
  CRYPT_OID_FIND_OID_INFO_FUNC       = 'CryptDllFindOIDInfo';
  {$EXTERNALSYM CRYPT_OID_FIND_OID_INFO_FUNC}
  CRYPT_OID_FIND_LOCALIZED_NAME_FUNC = 'CryptDllFindLocalizedName';
  {$EXTERNALSYM CRYPT_OID_FIND_LOCALIZED_NAME_FUNC}

// CryptDllEncodeObject has same function signature as CryptEncodeObject.

// CryptDllDecodeObject has same function signature as CryptDecodeObject.

// CryptDllEncodeObjectEx has same function signature as CryptEncodeObjectEx.
// The Ex version MUST support the CRYPT_ENCODE_ALLOC_FLAG option.
//
// If an Ex function isn't installed or registered, then, attempts to find
// a non-EX version. If the ALLOC flag is set, then, CryptEncodeObjectEx,
// does the allocation and calls the non-EX version twice.

// CryptDllDecodeObjectEx has same function signature as CryptDecodeObjectEx.
// The Ex version MUST support the CRYPT_DECODE_ALLOC_FLAG option.
//
// If an Ex function isn't installed or registered, then, attempts to find
// a non-EX version. If the ALLOC flag is set, then, CryptDecodeObjectEx,
// does the allocation and calls the non-EX version twice.

// CryptDllCreateCOMObject has the following signature:
//      BOOL WINAPI CryptDllCreateCOMObject(
//          IN DWORD dwEncodingType,
//          IN LPCSTR pszOID,
//          IN PCRYPT_DATA_BLOB pEncodedContent,
//          IN DWORD dwFlags,
//          IN REFIID riid,
//          OUT void **ppvObj);

// CertDllVerifyRevocation has the same signature as CertVerifyRevocation
//  (See CertVerifyRevocation for details on when called)

// CertDllVerifyCTLUsage has the same signature as CertVerifyCTLUsage

// CryptDllFindOIDInfo currently is only used to store values used by
// CryptFindOIDInfo. See CryptFindOIDInfo() for more details.

// CryptDllFindLocalizedName is only used to store localized string
// values used by CryptFindLocalizedName. See CryptFindLocalizedName() for
// more details.

//  Example of a complete OID Function Registry Name:
//    HKEY_LOCAL_MACHINE\Software\Microsoft\Cryptography\OID
//      Encoding Type 1\CryptDllEncodeObject\1.2.3
//
//  The key's L"Dll" value contains the name of the Dll.
//  The key's L"FuncName" value overrides the default function name

  CRYPT_OID_REGPATH                    = 'Software\Microsoft\Cryptography\OID';
  {$EXTERNALSYM CRYPT_OID_REGPATH}
  CRYPT_OID_REG_ENCODING_TYPE_PREFIX   = 'EncodingType ';
  {$EXTERNALSYM CRYPT_OID_REG_ENCODING_TYPE_PREFIX}
  CRYPT_OID_REG_DLL_VALUE_NAME         = 'Dll';
  {$EXTERNALSYM CRYPT_OID_REG_DLL_VALUE_NAME}
  CRYPT_OID_REG_FUNC_NAME_VALUE_NAME   = 'FuncName';
  {$EXTERNALSYM CRYPT_OID_REG_FUNC_NAME_VALUE_NAME}
  CRYPT_OID_REG_FUNC_NAME_VALUE_NAME_A = 'FuncName';
  {$EXTERNALSYM CRYPT_OID_REG_FUNC_NAME_VALUE_NAME_A}

// CRYPT_INSTALL_OID_FUNC_BEFORE_FLAG can be set in the key's L"CryptFlags"
// value to register the functions before the installed functions.
//
// CryptSetOIDFunctionValue must be called to set this value. L"CryptFlags"
// must be set using a dwValueType of REG_DWORD.

  CRYPT_OID_REG_FLAGS_VALUE_NAME = 'CryptFlags';
  {$EXTERNALSYM CRYPT_OID_REG_FLAGS_VALUE_NAME}

// OID used for Default OID functions

  CRYPT_DEFAULT_OID = 'DEFAULT';
  {$EXTERNALSYM CRYPT_DEFAULT_OID}

type
  PCRYPT_OID_FUNC_ENTRY = ^CRYPT_OID_FUNC_ENTRY;
  {$EXTERNALSYM PCRYPT_OID_FUNC_ENTRY}
  _CRYPT_OID_FUNC_ENTRY = record
    pszOID: LPCSTR;
    pvFuncAddr: Pointer;
  end;
  {$EXTERNALSYM _CRYPT_OID_FUNC_ENTRY}
  CRYPT_OID_FUNC_ENTRY = _CRYPT_OID_FUNC_ENTRY;
  {$EXTERNALSYM CRYPT_OID_FUNC_ENTRY}
  TCryptOidFuncEntry = CRYPT_OID_FUNC_ENTRY;
  PCryptOidFuncEntry = PCRYPT_OID_FUNC_ENTRY;

const
  CRYPT_INSTALL_OID_FUNC_BEFORE_FLAG = 1;
  {$EXTERNALSYM CRYPT_INSTALL_OID_FUNC_BEFORE_FLAG}

//+-------------------------------------------------------------------------
//  Install a set of callable OID function addresses.
//
//  By default the functions are installed at end of the list.
//  Set CRYPT_INSTALL_OID_FUNC_BEFORE_FLAG to install at beginning of list.
//
//  hModule should be updated with the hModule passed to DllMain to prevent
//  the Dll containing the function addresses from being unloaded by
//  CryptGetOIDFuncAddress/CryptFreeOIDFunctionAddress. This would be the
//  case when the Dll has also regsvr32'ed OID functions via
//  CryptRegisterOIDFunction.
//
//  DEFAULT functions are installed by setting rgFuncEntry[].pszOID =
//  CRYPT_DEFAULT_OID.
//--------------------------------------------------------------------------

function CryptInstallOIDFunctionAddress(hModule: HMODULE; dwEncodingType: DWORD;
  pszFuncName: LPCSTR; cFuncEntry: DWORD; rgFuncEntry: PCRYPT_OID_FUNC_ENTRY;
  dwFlags: DWORD): BOOL; stdcall;
{$EXTERNALSYM CryptInstallOIDFunctionAddress}

//+-------------------------------------------------------------------------
//  Initialize and return handle to the OID function set identified by its
//  function name.
//
//  If the set already exists, a handle to the existing set is returned.
//--------------------------------------------------------------------------

function CryptInitOIDFunctionSet(pszFuncName: LPCSTR; dwFlags: DWORD): HCRYPTOIDFUNCSET; stdcall;
{$EXTERNALSYM CryptInitOIDFunctionSet}

//+-------------------------------------------------------------------------
//  Search the list of installed functions for an encoding type and OID match.
//  If not found, search the registry.
//
//  For success, returns TRUE with *ppvFuncAddr updated with the function's
//  address and *phFuncAddr updated with the function address's handle.
//  The function's handle is AddRef'ed. CryptFreeOIDFunctionAddress needs to
//  be called to release it.
//
//  For a registry match, the Dll containing the function is loaded.
//
//  By default, both the registered and installed function lists are searched.
//  Set CRYPT_GET_INSTALLED_OID_FUNC_FLAG to only search the installed list
//  of functions. This flag would be set by a registered function to get
//  the address of a pre-installed function it was replacing. For example,
//  the registered function might handle a new special case and call the
//  pre-installed function to handle the remaining cases.
//--------------------------------------------------------------------------

function CryptGetOIDFunctionAddress(hFuncSet: HCRYPTOIDFUNCSET;
  dwEncodingType: DWORD; pszOID: LPCSTR; dwFlags: DWORD;
  var ppvFuncAddr: Pointer; var phFuncAddr: HCRYPTOIDFUNCADDR): BOOL; stdcall;
{$EXTERNALSYM CryptGetOIDFunctionAddress}

const
  CRYPT_GET_INSTALLED_OID_FUNC_FLAG = $1;
  {$EXTERNALSYM CRYPT_GET_INSTALLED_OID_FUNC_FLAG}

//+-------------------------------------------------------------------------
//  Get the list of registered default Dll entries for the specified
//  function set and encoding type.
//
//  The returned list consists of none, one or more null terminated Dll file
//  names. The list is terminated with an empty (L"\0") Dll file name.
//  For example: L"first.dll" L"\0" L"second.dll" L"\0" L"\0"
//--------------------------------------------------------------------------

function CryptGetDefaultOIDDllList(hFuncSet: HCRYPTOIDFUNCSET; dwEncodingType: DWORD;
  pwszDllList: LPWSTR; pcchDllList: DWORD): BOOL; stdcall;
{$EXTERNALSYM CryptGetDefaultOIDDllList}

//+-------------------------------------------------------------------------
//  Either: get the first or next installed DEFAULT function OR
//  load the Dll containing the DEFAULT function.
//
//  If pwszDll is NULL, search the list of installed DEFAULT functions.
//  *phFuncAddr must be set to NULL to get the first installed function.
//  Successive installed functions are returned by setting *phFuncAddr
//  to the hFuncAddr returned by the previous call.
//
//  If pwszDll is NULL, the input *phFuncAddr
//  is always CryptFreeOIDFunctionAddress'ed by this function, even for
//  an error.
//
//  If pwszDll isn't NULL, then, attempts to load the Dll and the DEFAULT
//  function. *phFuncAddr is ignored upon entry and isn't
//  CryptFreeOIDFunctionAddress'ed.
//
//  For success, returns TRUE with *ppvFuncAddr updated with the function's
//  address and *phFuncAddr updated with the function address's handle.
//  The function's handle is AddRef'ed. CryptFreeOIDFunctionAddress needs to
//  be called to release it or CryptGetDefaultOIDFunctionAddress can also
//  be called for a NULL pwszDll.
//--------------------------------------------------------------------------

function CryptGetDefaultOIDFunctionAddress(hFuncSet: HCRYPTOIDFUNCSET;
  dwEncodingType: DWORD; pwszDll: LPCWSTR; dwFlags: DWORD;
  var ppvFuncAddr: Pointer; phFuncAddr: HCRYPTOIDFUNCADDR): BOOL; stdcall;
{$EXTERNALSYM CryptGetDefaultOIDFunctionAddress}

//+-------------------------------------------------------------------------
//  Releases the handle AddRef'ed and returned by CryptGetOIDFunctionAddress
//  or CryptGetDefaultOIDFunctionAddress.
//
//  If a Dll was loaded for the function its unloaded. However, before doing
//  the unload, the DllCanUnloadNow function exported by the loaded Dll is
//  called. It should return S_FALSE to inhibit the unload or S_TRUE to enable
//  the unload. If the Dll doesn't export DllCanUnloadNow, the Dll is unloaded.
//
//  DllCanUnloadNow has the following signature:
//      STDAPI  DllCanUnloadNow(void);
//--------------------------------------------------------------------------

function CryptFreeOIDFunctionAddress(hFuncAddr: HCRYPTOIDFUNCADDR; dwFlags: DWORD): BOOL; stdcall;
{$EXTERNALSYM CryptFreeOIDFunctionAddress}

//+-------------------------------------------------------------------------
//  Register the Dll containing the function to be called for the specified
//  encoding type, function name and OID.
//
//  pwszDll may contain environment-variable strings
//  which are ExpandEnvironmentStrings()'ed before loading the Dll.
//
//  In addition to registering the DLL, you may override the
//  name of the function to be called. For example,
//      pszFuncName = "CryptDllEncodeObject",
//      pszOverrideFuncName = "MyEncodeXyz".
//  This allows a Dll to export multiple OID functions for the same
//  function name without needing to interpose its own OID dispatcher function.
//--------------------------------------------------------------------------

function CryptRegisterOIDFunction(dwEncodingType: DWORD; pszFuncName: LPCSTR;
  pszOID: LPCSTR; pwszDll: LPCWSTR; pszOverrideFuncName: LPCSTR): BOOL; stdcall;
{$EXTERNALSYM CryptRegisterOIDFunction}

//+-------------------------------------------------------------------------
//  Unregister the Dll containing the function to be called for the specified
//  encoding type, function name and OID.
//--------------------------------------------------------------------------

function CryptUnregisterOIDFunction(dwEncodingType: DWORD; pszFuncName: LPCSTR;
  pszOID: LPCSTR): BOOL; stdcall;
{$EXTERNALSYM CryptUnregisterOIDFunction}

//+-------------------------------------------------------------------------
//  Register the Dll containing the default function to be called for the
//  specified encoding type and function name.
//
//  Unlike CryptRegisterOIDFunction, you can't override the function name
//  needing to be exported by the Dll.
//
//  The Dll is inserted before the entry specified by dwIndex.
//    dwIndex == 0, inserts at the beginning.
//    dwIndex == CRYPT_REGISTER_LAST_INDEX, appends at the end.
//
//  pwszDll may contain environment-variable strings
//  which are ExpandEnvironmentStrings()'ed before loading the Dll.
//--------------------------------------------------------------------------

function CryptRegisterDefaultOIDFunction(dwEncodingType: DWORD; pszFuncName: LPCSTR;
  dwIndex: DWORD; pwszDll: LPCWSTR): BOOL; stdcall;
{$EXTERNALSYM CryptRegisterDefaultOIDFunction}

const
  CRYPT_REGISTER_FIRST_INDEX = 0;
  {$EXTERNALSYM CRYPT_REGISTER_FIRST_INDEX}
  CRYPT_REGISTER_LAST_INDEX  = DWORD($FFFFFFFF);
  {$EXTERNALSYM CRYPT_REGISTER_LAST_INDEX}

//+-------------------------------------------------------------------------
//  Unregister the Dll containing the default function to be called for
//  the specified encoding type and function name.
//--------------------------------------------------------------------------

function CryptUnregisterDefaultOIDFunction(dwEncodingType: DWORD;
  pszFuncName: LPCSTR; pwszDll: LPCWSTR): BOOL; stdcall;
{$EXTERNALSYM CryptUnregisterDefaultOIDFunction}

//+-------------------------------------------------------------------------
//  Set the value for the specified encoding type, function name, OID and
//  value name.
//
//  See RegSetValueEx for the possible value types.
//
//  String types are UNICODE.
//--------------------------------------------------------------------------

function CryptSetOIDFunctionValue(dwEncodingType: DWORD; pszFuncName: LPCSTR;
  pszOID: LPCSTR; pwszValueName: LPCWSTR; dwValueType: DWORD; pbValueData: LPBYTE;
  cbValueData: DWORD): BOOL; stdcall;
{$EXTERNALSYM CryptSetOIDFunctionValue}

//+-------------------------------------------------------------------------
//  Get the value for the specified encoding type, function name, OID and
//  value name.
//
//  See RegEnumValue for the possible value types.
//
//  String types are UNICODE.
//--------------------------------------------------------------------------

function CryptGetOIDFunctionValue(dwEncodingType: DWORD; pszFuncName: LPCSTR;
  pszOID: LPCSTR; pwszValueName: LPCWSTR; var pdwValueType: DWORD;
  pbValueData: LPBYTE; var pcbValueData: DWORD): BOOL; stdcall;
{$EXTERNALSYM CryptGetOIDFunctionValue}

type
  PFN_CRYPT_ENUM_OID_FUNC = function (dwEncodingType: DWORD; pszFuncName,
    pszOID: LPCSTR; cValue: DWORD; rgdwValueType: LPDWORD;
    rgpwszValueName: LPCWSTR; rgpbValueData: LPBYTE; rgcbValueData: LPDWORD;
    pvArg: Pointer): BOOL; stdcall;
  {$EXTERNALSYM PFN_CRYPT_ENUM_OID_FUNC}
  PFnCryptEnumOidFunc = PFN_CRYPT_ENUM_OID_FUNC;

//+-------------------------------------------------------------------------
//  Enumerate the OID functions identified by their encoding type,
//  function name and OID.
//
//  pfnEnumOIDFunc is called for each registry key matching the input
//  parameters. Setting dwEncodingType to CRYPT_MATCH_ANY_ENCODING_TYPE matches
//  any. Setting pszFuncName or pszOID to NULL matches any.
//
//  Set pszOID == CRYPT_DEFAULT_OID to restrict the enumeration to only the
//  DEFAULT functions
//
//  String types are UNICODE.
//--------------------------------------------------------------------------

function CryptEnumOIDFunction(dwEncodingType: DWORD; pszFuncName, pszOID: LPCSTR;
  dwFlags: DWORD; pvArg: Pointer; pfnEnumOIDFunc: PFN_CRYPT_ENUM_OID_FUNC): BOOL; stdcall;
{$EXTERNALSYM CryptEnumOIDFunction}

const
  CRYPT_MATCH_ANY_ENCODING_TYPE = DWORD($FFFFFFFF);
  {$EXTERNALSYM CRYPT_MATCH_ANY_ENCODING_TYPE}

//+=========================================================================
//  Object IDentifier (OID) Information:  Data Structures and APIs
//==========================================================================

//+-------------------------------------------------------------------------
//  OID Information
//--------------------------------------------------------------------------

type
  PCRYPT_OID_INFO = ^CRYPT_OID_INFO;
  {$EXTERNALSYM PCRYPT_OID_INFO}
  _CRYPT_OID_INFO = record
    cbSize: DWORD;
    pszOID: LPCSTR;
    pwszName: LPCWSTR;
    dwGroupId: DWORD;
    Union: record
    case Integer of
      0: (dwValue: DWORD);
      1: (Algid: ALG_ID);
      2: (dwLength: DWORD);
    end;
    ExtraInfo: CRYPT_DATA_BLOB;
  end;
  {$EXTERNALSYM _CRYPT_OID_INFO}
  CRYPT_OID_INFO = _CRYPT_OID_INFO;
  {$EXTERNALSYM CRYPT_OID_INFO}
  TCryptOidInfo = CRYPT_OID_INFO;
  PCryptOidInfo = PCRYPT_OID_INFO;

  CCRYPT_OID_INFO = CRYPT_OID_INFO;
  {$EXTERNALSYM CCRYPT_OID_INFO}
  PCCRYPT_OID_INFO = PCRYPT_OID_INFO;
  {$EXTERNALSYM PCCRYPT_OID_INFO}

//+-------------------------------------------------------------------------
//  OID Group IDs
//--------------------------------------------------------------------------

const
  CRYPT_HASH_ALG_OID_GROUP_ID     = 1;
  {$EXTERNALSYM CRYPT_HASH_ALG_OID_GROUP_ID}
  CRYPT_ENCRYPT_ALG_OID_GROUP_ID  = 2;
  {$EXTERNALSYM CRYPT_ENCRYPT_ALG_OID_GROUP_ID}
  CRYPT_PUBKEY_ALG_OID_GROUP_ID   = 3;
  {$EXTERNALSYM CRYPT_PUBKEY_ALG_OID_GROUP_ID}
  CRYPT_SIGN_ALG_OID_GROUP_ID     = 4;
  {$EXTERNALSYM CRYPT_SIGN_ALG_OID_GROUP_ID}
  CRYPT_RDN_ATTR_OID_GROUP_ID     = 5;
  {$EXTERNALSYM CRYPT_RDN_ATTR_OID_GROUP_ID}
  CRYPT_EXT_OR_ATTR_OID_GROUP_ID  = 6;
  {$EXTERNALSYM CRYPT_EXT_OR_ATTR_OID_GROUP_ID}
  CRYPT_ENHKEY_USAGE_OID_GROUP_ID = 7;
  {$EXTERNALSYM CRYPT_ENHKEY_USAGE_OID_GROUP_ID}
  CRYPT_POLICY_OID_GROUP_ID       = 8;
  {$EXTERNALSYM CRYPT_POLICY_OID_GROUP_ID}
  CRYPT_LAST_OID_GROUP_ID         = 8;
  {$EXTERNALSYM CRYPT_LAST_OID_GROUP_ID}

  CRYPT_FIRST_ALG_OID_GROUP_ID = CRYPT_HASH_ALG_OID_GROUP_ID;
  {$EXTERNALSYM CRYPT_FIRST_ALG_OID_GROUP_ID}
  CRYPT_LAST_ALG_OID_GROUP_ID  = CRYPT_SIGN_ALG_OID_GROUP_ID;
  {$EXTERNALSYM CRYPT_LAST_ALG_OID_GROUP_ID}

// The CRYPT_*_ALG_OID_GROUP_ID's have an Algid. The CRYPT_RDN_ATTR_OID_GROUP_ID
// has a dwLength. The CRYPT_EXT_OR_ATTR_OID_GROUP_ID,
// CRYPT_ENHKEY_USAGE_OID_GROUP_ID or CRYPT_POLICY_OID_GROUP_ID don't have a
// dwValue.
//

// CRYPT_PUBKEY_ALG_OID_GROUP_ID has the following optional ExtraInfo:
//  DWORD[0] - Flags. CRYPT_OID_INHIBIT_SIGNATURE_FORMAT_FLAG can be set to
//             inhibit the reformatting of the signature before
//             CryptVerifySignature is called or after CryptSignHash
//             is called. CRYPT_OID_USE_PUBKEY_PARA_FOR_PKCS7_FLAG can
//             be set to include the public key algorithm's parameters
//             in the PKCS7's digestEncryptionAlgorithm's parameters.
//             CRYPT_OID_NO_NULL_ALGORITHM_PARA_FLAG can be set to omit
//             NULL parameters when encoding.

  CRYPT_OID_INHIBIT_SIGNATURE_FORMAT_FLAG  = $1;
  {$EXTERNALSYM CRYPT_OID_INHIBIT_SIGNATURE_FORMAT_FLAG}
  CRYPT_OID_USE_PUBKEY_PARA_FOR_PKCS7_FLAG = $2;
  {$EXTERNALSYM CRYPT_OID_USE_PUBKEY_PARA_FOR_PKCS7_FLAG}
  CRYPT_OID_NO_NULL_ALGORITHM_PARA_FLAG    = $4;
  {$EXTERNALSYM CRYPT_OID_NO_NULL_ALGORITHM_PARA_FLAG}

// CRYPT_SIGN_ALG_OID_GROUP_ID has the following optional ExtraInfo:
//  DWORD[0] - Public Key Algid.
//  DWORD[1] - Flags. Same as above for CRYPT_PUBKEY_ALG_OID_GROUP_ID.
//  DWORD[2] - Optional CryptAcquireContext(CRYPT_VERIFYCONTEXT)'s dwProvType.
//             If omitted or 0, uses Public Key Algid to select
//             appropriate dwProvType for signature verification.

// CRYPT_RDN_ATTR_OID_GROUP_ID has the following optional ExtraInfo:
//  Array of DWORDs:
//   [0 ..] - Null terminated list of acceptable RDN attribute
//            value types. An empty list implies CERT_RDN_PRINTABLE_STRING,
//            CERT_RDN_UNICODE_STRING, 0.

//+-------------------------------------------------------------------------
//  Find OID information. Returns NULL if unable to find any information
//  for the specified key and group. Note, returns a pointer to a constant
//  data structure. The returned pointer MUST NOT be freed.
//
//  dwKeyType's:
//    CRYPT_OID_INFO_OID_KEY, pvKey points to a szOID
//    CRYPT_OID_INFO_NAME_KEY, pvKey points to a wszName
//    CRYPT_OID_INFO_ALGID_KEY, pvKey points to an ALG_ID
//    CRYPT_OID_INFO_SIGN_KEY, pvKey points to an array of two ALG_ID's:
//      ALG_ID[0] - Hash Algid
//      ALG_ID[1] - PubKey Algid
//
//  Setting dwGroupId to 0, searches all groups according to the dwKeyType.
//  Otherwise, only the dwGroupId is searched.
//--------------------------------------------------------------------------

function CryptFindOIDInfo(dwKeyType: DWORD; pvKey: Pointer; dwGroupId: DWORD): PCCRYPT_OID_INFO; stdcall;
{$EXTERNALSYM CryptFindOIDInfo}

const
  CRYPT_OID_INFO_OID_KEY   = 1;
  {$EXTERNALSYM CRYPT_OID_INFO_OID_KEY}
  CRYPT_OID_INFO_NAME_KEY  = 2;
  {$EXTERNALSYM CRYPT_OID_INFO_NAME_KEY}
  CRYPT_OID_INFO_ALGID_KEY = 3;
  {$EXTERNALSYM CRYPT_OID_INFO_ALGID_KEY}
  CRYPT_OID_INFO_SIGN_KEY  = 4;
  {$EXTERNALSYM CRYPT_OID_INFO_SIGN_KEY}

//+-------------------------------------------------------------------------
//  Register OID information. The OID information specified in the
//  CCRYPT_OID_INFO structure is persisted to the registry.
//
//  crypt32.dll contains information for the commonly known OIDs. This function
//  allows applications to augment crypt32.dll's OID information. During
//  CryptFindOIDInfo's first call, the registered OID information is installed.
//
//  By default the registered OID information is installed after crypt32.dll's
//  OID entries. Set CRYPT_INSTALL_OID_INFO_BEFORE_FLAG to install before.
//--------------------------------------------------------------------------

function CryptRegisterOIDInfo(pInfo: PCCRYPT_OID_INFO; dwFlags: DWORD): BOOL; stdcall;
{$EXTERNALSYM CryptRegisterOIDInfo}

const
  CRYPT_INSTALL_OID_INFO_BEFORE_FLAG = 1;
  {$EXTERNALSYM CRYPT_INSTALL_OID_INFO_BEFORE_FLAG}

//+-------------------------------------------------------------------------
//  Unregister OID information. Only the pszOID and dwGroupId fields are
//  used to identify the OID information to be unregistered.
//--------------------------------------------------------------------------

function CryptUnregisterOIDInfo(pInfo: PCCRYPT_OID_INFO): BOOL; stdcall;
{$EXTERNALSYM CryptUnregisterOIDInfo}

// If the callback returns FALSE, stops the enumeration.

type
  PFN_CRYPT_ENUM_OID_INFO = function (pInfo: PCCRYPT_OID_INFO; pvArg: Pointer): BOOL; stdcall;
  {$EXTERNALSYM PFN_CRYPT_ENUM_OID_INFO}
  PFnCryptEnumOidInfo = PFN_CRYPT_ENUM_OID_INFO;

//+-------------------------------------------------------------------------
//  Enumerate the OID information.
//
//  pfnEnumOIDInfo is called for each OID information entry.
//
//  Setting dwGroupId to 0 matches all groups. Otherwise, only enumerates
//  entries in the specified group.
//
//  dwFlags currently isn't used and must be set to 0.
//--------------------------------------------------------------------------

function CryptEnumOIDInfo(dwGroupId: DWORD; dwFlags: DWORD; pvArg: Pointer;
  pfnEnumOIDInfo: PFN_CRYPT_ENUM_OID_INFO): BOOL; stdcall;
{$EXTERNALSYM CryptEnumOIDInfo}

//+-------------------------------------------------------------------------
//  Find the localized name for the specified name. For example, find the
//  localized name for the "Root" system store name. A case insensitive
//  string comparison is done.
//
//  Returns NULL if unable to find the the specified name.
//
//  Localized names for the predefined system stores ("Root", "My") and
//  predefined physical stores (".Default", ".LocalMachine") are pre-installed
//  as resource strings in crypt32.dll. CryptSetOIDFunctionValue can be called
//  as follows to register additional localized strings:
//      dwEncodingType = CRYPT_LOCALIZED_NAME_ENCODING_TYPE
//      pszFuncName = CRYPT_OID_FIND_LOCALIZED_NAME_FUNC
//      pszOID = CRYPT_LOCALIZED_NAME_OID
//      pwszValueName = Name to be localized, for example, L"ApplicationStore"
//      dwValueType = REG_SZ
//      pbValueData = pointer to the UNICODE localized string
//      cbValueData = (wcslen(UNICODE localized string) + 1) * sizeof(WCHAR)
//
//  To unregister, set pbValueData to NULL and cbValueData to 0.
//
//  The registered names are searched before the pre-installed names.
//--------------------------------------------------------------------------

function CryptFindLocalizedName(pwszCryptName: LPCWSTR): LPCWSTR; stdcall;
{$EXTERNALSYM CryptFindLocalizedName}

const
  CRYPT_LOCALIZED_NAME_ENCODING_TYPE = 0;
  {$EXTERNALSYM CRYPT_LOCALIZED_NAME_ENCODING_TYPE}
  CRYPT_LOCALIZED_NAME_OID           = 'LocalizedNames';
  {$EXTERNALSYM CRYPT_LOCALIZED_NAME_OID}

//+=========================================================================
//  Low Level Cryptographic Message Data Structures and APIs
//==========================================================================

type
  HCRYPTMSG = Pointer;
  {$EXTERNALSYM HCRYPTMSG}
  PHCRYPTMSG = ^HCRYPTMSG;
  {$NODEFINE PHCRYPTMSG}

const
  szOID_PKCS_7_DATA               = '1.2.840.113549.1.7.1';
  {$EXTERNALSYM szOID_PKCS_7_DATA}
  szOID_PKCS_7_SIGNED             = '1.2.840.113549.1.7.2';
  {$EXTERNALSYM szOID_PKCS_7_SIGNED}
  szOID_PKCS_7_ENVELOPED          = '1.2.840.113549.1.7.3';
  {$EXTERNALSYM szOID_PKCS_7_ENVELOPED}
  szOID_PKCS_7_SIGNEDANDENVELOPED = '1.2.840.113549.1.7.4';
  {$EXTERNALSYM szOID_PKCS_7_SIGNEDANDENVELOPED}
  szOID_PKCS_7_DIGESTED           = '1.2.840.113549.1.7.5';
  {$EXTERNALSYM szOID_PKCS_7_DIGESTED}
  szOID_PKCS_7_ENCRYPTED          = '1.2.840.113549.1.7.6';
  {$EXTERNALSYM szOID_PKCS_7_ENCRYPTED}

  szOID_PKCS_9_CONTENT_TYPE   = '1.2.840.113549.1.9.3';
  {$EXTERNALSYM szOID_PKCS_9_CONTENT_TYPE}
  szOID_PKCS_9_MESSAGE_DIGEST = '1.2.840.113549.1.9.4';
  {$EXTERNALSYM szOID_PKCS_9_MESSAGE_DIGEST}

//+-------------------------------------------------------------------------
//  Message types
//--------------------------------------------------------------------------

  CMSG_DATA                 = 1;
  {$EXTERNALSYM CMSG_DATA}
  CMSG_SIGNED               = 2;
  {$EXTERNALSYM CMSG_SIGNED}
  CMSG_ENVELOPED            = 3;
  {$EXTERNALSYM CMSG_ENVELOPED}
  CMSG_SIGNED_AND_ENVELOPED = 4;
  {$EXTERNALSYM CMSG_SIGNED_AND_ENVELOPED}
  CMSG_HASHED               = 5;
  {$EXTERNALSYM CMSG_HASHED}
  CMSG_ENCRYPTED            = 6;
  {$EXTERNALSYM CMSG_ENCRYPTED}

//+-------------------------------------------------------------------------
//  Message Type Bit Flags
//--------------------------------------------------------------------------

  CMSG_ALL_FLAGS                 = (not 0);
  {$EXTERNALSYM CMSG_ALL_FLAGS}
  CMSG_DATA_FLAG                 = (1 shl CMSG_DATA);
  {$EXTERNALSYM CMSG_DATA_FLAG}
  CMSG_SIGNED_FLAG               = (1 shl CMSG_SIGNED);
  {$EXTERNALSYM CMSG_SIGNED_FLAG}
  CMSG_ENVELOPED_FLAG            = (1 shl CMSG_ENVELOPED);
  {$EXTERNALSYM CMSG_ENVELOPED_FLAG}
  CMSG_SIGNED_AND_ENVELOPED_FLAG = (1 shl CMSG_SIGNED_AND_ENVELOPED);
  {$EXTERNALSYM CMSG_SIGNED_AND_ENVELOPED_FLAG}
  CMSG_HASHED_FLAG               = (1 shl CMSG_HASHED);
  {$EXTERNALSYM CMSG_HASHED_FLAG}
  CMSG_ENCRYPTED_FLAG            = (1 shl CMSG_ENCRYPTED);
  {$EXTERNALSYM CMSG_ENCRYPTED_FLAG}

//+-------------------------------------------------------------------------
//  Certificate Issuer and SerialNumber
//--------------------------------------------------------------------------

type
  PCERT_ISSUER_SERIAL_NUMBER = ^CERT_ISSUER_SERIAL_NUMBER;
  {$EXTERNALSYM PCERT_ISSUER_SERIAL_NUMBER}
  _CERT_ISSUER_SERIAL_NUMBER = record
    Issuer: CERT_NAME_BLOB;
    SerialNumber: CRYPT_INTEGER_BLOB;
  end;
  {$EXTERNALSYM _CERT_ISSUER_SERIAL_NUMBER}
  CERT_ISSUER_SERIAL_NUMBER = _CERT_ISSUER_SERIAL_NUMBER;
  {$EXTERNALSYM CERT_ISSUER_SERIAL_NUMBER}
  TCertIssuerSerialNumber = CERT_ISSUER_SERIAL_NUMBER;
  PCertIssuerSerialNumber = PCERT_ISSUER_SERIAL_NUMBER;

//+-------------------------------------------------------------------------
//  Certificate Identifier
//--------------------------------------------------------------------------

  PCERT_ID = ^CERT_ID;
  {$EXTERNALSYM PCERT_ID}
  _CERT_ID = record
    dwIdChoice: DWORD;
    case Integer of
      // CERT_ID_ISSUER_SERIAL_NUMBER
      0: (IssuerSerialNumber: CERT_ISSUER_SERIAL_NUMBER);
      // CERT_ID_KEY_IDENTIFIER
      1: (KeyId: CRYPT_HASH_BLOB);
      // CERT_ID_SHA1_HASH
      2: (HashId: CRYPT_HASH_BLOB);
  end;
  {$EXTERNALSYM _CERT_ID}
  CERT_ID = _CERT_ID;
  {$EXTERNALSYM CERT_ID}
  TCertId = CERT_ID;
  PCertId = PCERT_ID;

const
  CERT_ID_ISSUER_SERIAL_NUMBER = 1;
  {$EXTERNALSYM CERT_ID_ISSUER_SERIAL_NUMBER}
  CERT_ID_KEY_IDENTIFIER       = 2;
  {$EXTERNALSYM CERT_ID_KEY_IDENTIFIER}
  CERT_ID_SHA1_HASH            = 3;
  {$EXTERNALSYM CERT_ID_SHA1_HASH}

//+-------------------------------------------------------------------------
//  The message encode information (pvMsgEncodeInfo) is message type dependent
//--------------------------------------------------------------------------

//+-------------------------------------------------------------------------
//  CMSG_DATA: pvMsgEncodeInfo = NULL
//--------------------------------------------------------------------------

//+-------------------------------------------------------------------------
//  CMSG_SIGNED
//
//  The pCertInfo in the CMSG_SIGNER_ENCODE_INFO provides the Issuer, SerialNumber
//  and PublicKeyInfo.Algorithm. The PublicKeyInfo.Algorithm implicitly
//  specifies the HashEncryptionAlgorithm to be used.
//
//  If the SignerId is present with a nonzero dwIdChoice its used instead
//  of the Issuer and SerialNumber in pCertInfo.
//
//  CMS supports the KEY_IDENTIFIER and ISSUER_SERIAL_NUMBER CERT_IDs. PKCS #7
//  version 1.5 only supports the ISSUER_SERIAL_NUMBER CERT_ID choice.
//
//  If HashEncryptionAlgorithm is present and not NULL its used instead of
//  the PublicKeyInfo.Algorithm.
//
//  Note, for RSA, the hash encryption algorithm is normally the same as
//  the public key algorithm. For DSA, the hash encryption algorithm is
//  normally a DSS signature algorithm.
//
//  pvHashEncryptionAuxInfo currently isn't used and must be set to NULL if
//  present in the data structure.
//
//  The hCryptProv and dwKeySpec specify the private key to use. If dwKeySpec
//  == 0, then, defaults to AT_SIGNATURE.
//
//  If CMSG_CRYPT_RELEASE_CONTEXT_FLAG is set in the dwFlags
//  passed to CryptMsgOpenToEncode(), the signer hCryptProv's are released.
//
//  pvHashAuxInfo currently isn't used and must be set to NULL.
//
//  CMS signed messages allow the inclusion of Attribute Certs.
//--------------------------------------------------------------------------

type
  PCMSG_SIGNER_ENCODE_INFO = ^CMSG_SIGNER_ENCODE_INFO;
  {$EXTERNALSYM PCMSG_SIGNER_ENCODE_INFO}
  _CMSG_SIGNER_ENCODE_INFO = record
    cbSize: DWORD;
    pCertInfo: PCERT_INFO;
    hCryptProv: HCRYPTPROV;
    dwKeySpec: DWORD;
    HashAlgorithm: CRYPT_ALGORITHM_IDENTIFIER;
    pvHashAuxInfo: Pointer;
    cAuthAttr: DWORD;
    rgAuthAttr: PCRYPT_ATTRIBUTE;
    cUnauthAttr: DWORD;
    rgUnauthAttr: PCRYPT_ATTRIBUTE;
    {$IFDEF CMSG_SIGNER_ENCODE_INFO_HAS_CMS_FIELDS}
    SignerId: CERT_ID;
    HashEncryptionAlgorithm: CRYPT_ALGORITHM_IDENTIFIER;
    pvHashEncryptionAuxInfo: Pointer;
    {$ENDIF}
  end;
  {$EXTERNALSYM _CMSG_SIGNER_ENCODE_INFO}
  CMSG_SIGNER_ENCODE_INFO = _CMSG_SIGNER_ENCODE_INFO;
  {$EXTERNALSYM CMSG_SIGNER_ENCODE_INFO}
  TCmsgSignerEncodeInfo = CMSG_SIGNER_ENCODE_INFO;
  PCmsgSignerEncodeInfo = PCMSG_SIGNER_ENCODE_INFO;

  PCMSG_SIGNED_ENCODE_INFO = ^CMSG_SIGNED_ENCODE_INFO;
  {$EXTERNALSYM PCMSG_SIGNED_ENCODE_INFO}
  _CMSG_SIGNED_ENCODE_INFO = record
    cbSize: DWORD;
    cSigners: DWORD;
    rgSigners: PCMSG_SIGNER_ENCODE_INFO;
    cCertEncoded: DWORD;
    rgCertEncoded: PCERT_BLOB;
    cCrlEncoded: DWORD;
    rgCrlEncoded: PCRL_BLOB;
    {$IFDEF CMSG_SIGNED_ENCODE_INFO_HAS_CMS_FIELDS}
    cAttrCertEncoded: DWORD;
    rgAttrCertEncoded: PCERT_BLOB;
    {$ENDIF}
  end;
  {$EXTERNALSYM _CMSG_SIGNED_ENCODE_INFO}
  CMSG_SIGNED_ENCODE_INFO = _CMSG_SIGNED_ENCODE_INFO;
  {$EXTERNALSYM CMSG_SIGNED_ENCODE_INFO}
  TCmsgSignedEncodeInfo = CMSG_SIGNED_ENCODE_INFO;
  PCmsgSignedEncodeInfo = PCMSG_SIGNED_ENCODE_INFO;

//+-------------------------------------------------------------------------
//  CMSG_ENVELOPED
//
//  The PCERT_INFO for the rgRecipients provides the Issuer, SerialNumber
//  and PublicKeyInfo. The PublicKeyInfo.Algorithm implicitly
//  specifies the KeyEncryptionAlgorithm to be used.
//
//  The PublicKeyInfo.PublicKey in PCERT_INFO is used to encrypt the content
//  encryption key for the recipient.
//
//  hCryptProv is used to do the content encryption, recipient key encryption
//  and export. The hCryptProv's private keys aren't used. If hCryptProv
//  is NULL, a default hCryptProv is chosen according to the
//  ContentEncryptionAlgorithm and the first recipient KeyEncryptionAlgorithm.
//
//  If CMSG_CRYPT_RELEASE_CONTEXT_FLAG is set in the dwFlags
//  passed to CryptMsgOpenToEncode(), the envelope's hCryptProv is released.
//
//  Note: CAPI currently doesn't support more than one KeyEncryptionAlgorithm
//  per provider. This will need to be fixed.
//
//  Currently, pvEncryptionAuxInfo is only defined for RC2 or RC4 encryption
//  algorithms. Otherwise, its not used and must be set to NULL.
//  See CMSG_RC2_AUX_INFO for the RC2 encryption algorithms.
//  See CMSG_RC4_AUX_INFO for the RC4 encryption algorithms.
//
//  To enable SP3 compatible encryption, pvEncryptionAuxInfo should point to
//  a CMSG_SP3_COMPATIBLE_AUX_INFO data structure.
//
//  To enable the CMS envelope enhancements, rgpRecipients must be set to
//  NULL, and rgCmsRecipients updated to point to an array of
//  CMSG_RECIPIENT_ENCODE_INFO's.
//
//  Also, CMS envelope enhancements support the inclusion of a bag of
//  Certs, CRLs, Attribute Certs and/or Unprotected Attributes.
//--------------------------------------------------------------------------

type
  PCMSG_ENVELOPED_ENCODE_INFO = ^CMSG_ENVELOPED_ENCODE_INFO;
  {$EXTERNALSYM PCMSG_ENVELOPED_ENCODE_INFO}
  _CMSG_ENVELOPED_ENCODE_INFO = record
    cbSize: DWORD;
    hCryptProv: HCRYPTPROV;
    ContentEncryptionAlgorithm: CRYPT_ALGORITHM_IDENTIFIER;
    pvEncryptionAuxInfo: Pointer;
    cRecipients: DWORD;
    // The following array may only be used for transport recipients identified
    // by their IssuereAndSerialNumber. If rgpRecipients != NULL, then,
    // the rgCmsRecipients must be NULL.
    rgpRecipients: PCERT_INFO;
    {$IFDEF CMSG_ENVELOPED_ENCODE_INFO_HAS_CMS_FIELDS}
    // If rgCmsRecipients != NULL, then, the above rgpRecipients must be
    // NULL.
    rgCmsRecipients: PCMSG_RECIPIENT_ENCODE_INFO;
    cCertEncoded: DWORD;
    rgCertEncoded: PCERT_BLOB;
    cCrlEncoded: DWORD;
    rgCrlEncoded: PCRL_BLOB;
    cAttrCertEncoded: DWORD;
    rgAttrCertEncoded: PCERT_BLOB;
    cUnprotectedAttr: DWORD;
    rgUnprotectedAttr: PCRYPT_ATTRIBUTE;
    {$ENDIF}
  end;
  {$EXTERNALSYM _CMSG_ENVELOPED_ENCODE_INFO}
  CMSG_ENVELOPED_ENCODE_INFO = _CMSG_ENVELOPED_ENCODE_INFO;
  {$EXTERNALSYM CMSG_ENVELOPED_ENCODE_INFO}
  TCmsgEnvelopedEncodeInfo = CMSG_ENVELOPED_ENCODE_INFO;
  PCmsgEnvelopedEncodeInfo = PCMSG_ENVELOPED_ENCODE_INFO;

//+-------------------------------------------------------------------------
//  Key Transport Recipient Encode Info
//
//  hCryptProv is used to do the recipient key encryption
//  and export. The hCryptProv's private keys aren't used.
//
//  If hCryptProv is NULL, then, the hCryptProv specified in
//  CMSG_ENVELOPED_ENCODE_INFO is used.
//
//  Note, even if CMSG_CRYPT_RELEASE_CONTEXT_FLAG is set in the dwFlags
//  passed to CryptMsgOpenToEncode(), this hCryptProv isn't released.
//
//  CMS supports the KEY_IDENTIFIER and ISSUER_SERIAL_NUMBER CERT_IDs. PKCS #7
//  version 1.5 only supports the ISSUER_SERIAL_NUMBER CERT_ID choice.
//--------------------------------------------------------------------------

  PCMSG_KEY_TRANS_RECIPIENT_ENCODE_INFO = ^CMSG_KEY_TRANS_RECIPIENT_ENCODE_INFO;
  {$EXTERNALSYM PCMSG_KEY_TRANS_RECIPIENT_ENCODE_INFO}
  _CMSG_KEY_TRANS_RECIPIENT_ENCODE_INFO = record
    cbSize: DWORD;
    KeyEncryptionAlgorithm: CRYPT_ALGORITHM_IDENTIFIER;
    pvKeyEncryptionAuxInfo: Pointer;
    hCryptProv: HCRYPTPROV;
    RecipientPublicKey: CRYPT_BIT_BLOB;
    RecipientId: CERT_ID;
  end;
  {$EXTERNALSYM _CMSG_KEY_TRANS_RECIPIENT_ENCODE_INFO}
  CMSG_KEY_TRANS_RECIPIENT_ENCODE_INFO = _CMSG_KEY_TRANS_RECIPIENT_ENCODE_INFO;
  {$EXTERNALSYM CMSG_KEY_TRANS_RECIPIENT_ENCODE_INFO}
  TCmsgKeyTransRecipientEncodeInfo = CMSG_KEY_TRANS_RECIPIENT_ENCODE_INFO;
  PCmsgKeyTransRecipientEncodeInfo = PCMSG_KEY_TRANS_RECIPIENT_ENCODE_INFO;

//+-------------------------------------------------------------------------
//  Key Agreement Recipient Encode Info
//
//  If hCryptProv is NULL, then, the hCryptProv specified in
//  CMSG_ENVELOPED_ENCODE_INFO is used.
//
//  For the CMSG_KEY_AGREE_STATIC_KEY_CHOICE, both the hCryptProv and
//  dwKeySpec must be specified to select the sender's private key.
//
//  Note, even if CMSG_CRYPT_RELEASE_CONTEXT_FLAG is set in the dwFlags
//  passed to CryptMsgOpenToEncode(), this hCryptProv isn't released.
//
//  CMS supports the KEY_IDENTIFIER and ISSUER_SERIAL_NUMBER CERT_IDs.
//
//  There is 1 key choice, ephemeral originator. The originator's ephemeral
//  key is generated using the public key algorithm parameters shared
//  amongst all the recipients.
//
//  There are 2 key choices: ephemeral originator or static sender. The
//  originator's ephemeral key is generated using the public key algorithm
//  parameters shared amongst all the recipients. For the static sender its
//  private key is used. The hCryptProv and dwKeySpec specify the private key.
//  The pSenderId identifies the certificate containing the sender's public key.
//
//  Currently, pvKeyEncryptionAuxInfo isn't used and must be set to NULL. 
//
//  If KeyEncryptionAlgorithm.Parameters.cbData == 0, then, its Parameters
//  are updated with the encoded KeyWrapAlgorithm.
//
//  Currently, pvKeyWrapAuxInfo is only defined for algorithms with
//  RC2. Otherwise, its not used and must be set to NULL.
//  When set for RC2 algorithms, points to a CMSG_RC2_AUX_INFO containing
//  the RC2 effective key length.
//
//  Note, key agreement recipients are not supported in PKCS #7 version 1.5.
//--------------------------------------------------------------------------

  PCMSG_RECIPIENT_ENCRYPTED_KEY_ENCODE_INFO = ^CMSG_RECIPIENT_ENCRYPTED_KEY_ENCODE_INFO;
  {$EXTERNALSYM PCMSG_RECIPIENT_ENCRYPTED_KEY_ENCODE_INFO}
  _CMSG_RECIPIENT_ENCRYPTED_KEY_ENCODE_INFO = record
    cbSize: DWORD;
    RecipientPublicKey: CRYPT_BIT_BLOB;
    RecipientId: CERT_ID;
    // Following fields are optional and only applicable to KEY_IDENTIFIER
    // CERT_IDs.
    Date: FILETIME;
    pOtherAttr: PCRYPT_ATTRIBUTE_TYPE_VALUE;
  end;
  {$EXTERNALSYM _CMSG_RECIPIENT_ENCRYPTED_KEY_ENCODE_INFO}
  CMSG_RECIPIENT_ENCRYPTED_KEY_ENCODE_INFO = _CMSG_RECIPIENT_ENCRYPTED_KEY_ENCODE_INFO;
  {$EXTERNALSYM CMSG_RECIPIENT_ENCRYPTED_KEY_ENCODE_INFO}
  TCmsgRecipientEncryptedKeyEncodeInfo = CMSG_RECIPIENT_ENCRYPTED_KEY_ENCODE_INFO;
  PCmsgRecipientEncryptedKeyEncodeInfo = PCMSG_RECIPIENT_ENCRYPTED_KEY_ENCODE_INFO;

  PCMSG_KEY_AGREE_RECIPIENT_ENCODE_INFO = ^CMSG_KEY_AGREE_RECIPIENT_ENCODE_INFO;
  {$EXTERNALSYM PCMSG_KEY_AGREE_RECIPIENT_ENCODE_INFO}
  _CMSG_KEY_AGREE_RECIPIENT_ENCODE_INFO = record
    cbSize: DWORD;
    KeyEncryptionAlgorithm: CRYPT_ALGORITHM_IDENTIFIER;
    pvKeyEncryptionAuxInfo: Pointer;
    KeyWrapAlgorithm: CRYPT_ALGORITHM_IDENTIFIER;
    pvKeyWrapAuxInfo: Pointer;
    // The following hCryptProv and dwKeySpec must be specified for the
    // CMSG_KEY_AGREE_STATIC_KEY_CHOICE.
    //
    // For CMSG_KEY_AGREE_EPHEMERAL_KEY_CHOICE, dwKeySpec isn't applicable
    // and hCryptProv is optional.
    hCryptProv: HCRYPTPROV;
    dwKeySpec: DWORD;
    dwKeyChoice: DWORD;
    Union: record
    case Integer of
      // CMSG_KEY_AGREE_EPHEMERAL_KEY_CHOICE
      //
      // The ephemeral public key algorithm and parameters.
      0: (pEphemeralAlgorithm: PCRYPT_ALGORITHM_IDENTIFIER);
      // CMSG_KEY_AGREE_STATIC_KEY_CHOICE
      //
      // The CertId of the sender's certificate
      1: (pSenderId: PCERT_ID);
    end;
    UserKeyingMaterial: CRYPT_DATA_BLOB; // OPTIONAL
    cRecipientEncryptedKeys: DWORD;
    rgpRecipientEncryptedKeys: PCMSG_RECIPIENT_ENCRYPTED_KEY_ENCODE_INFO;
  end;
  {$EXTERNALSYM _CMSG_KEY_AGREE_RECIPIENT_ENCODE_INFO}
  CMSG_KEY_AGREE_RECIPIENT_ENCODE_INFO = _CMSG_KEY_AGREE_RECIPIENT_ENCODE_INFO;
  {$EXTERNALSYM CMSG_KEY_AGREE_RECIPIENT_ENCODE_INFO}
  TCmsgKeyAgreeRecipientEncodeInfo = CMSG_KEY_AGREE_RECIPIENT_ENCODE_INFO;
  PCmsgKeyAgreeRecipientEncodeInfo = PCMSG_KEY_AGREE_RECIPIENT_ENCODE_INFO;

const
  CMSG_KEY_AGREE_EPHEMERAL_KEY_CHOICE = 1;
  {$EXTERNALSYM CMSG_KEY_AGREE_EPHEMERAL_KEY_CHOICE}
  CMSG_KEY_AGREE_STATIC_KEY_CHOICE    = 2;
  {$EXTERNALSYM CMSG_KEY_AGREE_STATIC_KEY_CHOICE}

//+-------------------------------------------------------------------------
//  Mail List Recipient Encode Info
//
//  There is 1 choice for the KeyEncryptionKey: an already created CSP key
//  handle. For the key handle choice, hCryptProv must be nonzero. This key
//  handle isn't destroyed.
//
//  Note, even if CMSG_CRYPT_RELEASE_CONTEXT_FLAG is set in the dwFlags
//  passed to CryptMsgOpenToEncode(), this hCryptProv isn't released.
//
//  Currently, pvKeyEncryptionAuxInfo is only defined for RC2 key wrap
//  algorithms. Otherwise, its not used and must be set to NULL.
//  When set for RC2 algorithms, points to a CMSG_RC2_AUX_INFO containing
//  the RC2 effective key length.
//
//  Note, mail list recipients are not supported in PKCS #7 version 1.5.
//--------------------------------------------------------------------------

type
  PCMSG_MAIL_LIST_RECIPIENT_ENCODE_INFO = ^CMSG_MAIL_LIST_RECIPIENT_ENCODE_INFO;
  {$EXTERNALSYM PCMSG_MAIL_LIST_RECIPIENT_ENCODE_INFO}
  _CMSG_MAIL_LIST_RECIPIENT_ENCODE_INFO = record
    cbSize: DWORD;
    KeyEncryptionAlgorithm: CRYPT_ALGORITHM_IDENTIFIER;
    pvKeyEncryptionAuxInfo: Pointer;
    hCryptProv: HCRYPTPROV;
    dwKeyChoice: DWORD;
    Union: record
    case Integer of
      // CMSG_MAIL_LIST_HANDLE_KEY_CHOICE
      0: (hKeyEncryptionKey: HCRYPTKEY);
      // Reserve space for a potential pointer choice
      1: (pvKeyEncryptionKey: Pointer);
    end;
    KeyId: CRYPT_DATA_BLOB;
    // Following fields are optional.
    Date: FILETIME;
    pOtherAttr: PCRYPT_ATTRIBUTE_TYPE_VALUE;
  end;
  {$EXTERNALSYM _CMSG_MAIL_LIST_RECIPIENT_ENCODE_INFO}
  CMSG_MAIL_LIST_RECIPIENT_ENCODE_INFO = _CMSG_MAIL_LIST_RECIPIENT_ENCODE_INFO;
  {$EXTERNALSYM CMSG_MAIL_LIST_RECIPIENT_ENCODE_INFO}
  TCmsgMailListRecipientEncodeInfo = CMSG_MAIL_LIST_RECIPIENT_ENCODE_INFO;
  PCmsgMailListRecipientEncodeInfo = PCMSG_MAIL_LIST_RECIPIENT_ENCODE_INFO;

const
  CMSG_MAIL_LIST_HANDLE_KEY_CHOICE = 1;
  {$EXTERNALSYM CMSG_MAIL_LIST_HANDLE_KEY_CHOICE}

//+-------------------------------------------------------------------------
//  Recipient Encode Info
//
//  Note, only key transport recipients are supported in PKCS #7 version 1.5.
//--------------------------------------------------------------------------

type
  PCMSG_RECIPIENT_ENCODE_INFO = ^CMSG_RECIPIENT_ENCODE_INFO;
  {$NODEFINE PCMSG_RECIPIENT_ENCODE_INFO}
  _CMSG_RECIPIENT_ENCODE_INFO = record
    dwRecipientChoice: DWORD;
    case Integer of
      // CMSG_KEY_TRANS_RECIPIENT
      0: (pKeyTrans: PCMSG_KEY_TRANS_RECIPIENT_ENCODE_INFO);
      // CMSG_KEY_AGREE_RECIPIENT
      1: (pKeyAgree: PCMSG_KEY_AGREE_RECIPIENT_ENCODE_INFO);
      // CMSG_MAIL_LIST_RECIPIENT
      2: (pMailList: PCMSG_MAIL_LIST_RECIPIENT_ENCODE_INFO);
  end;
  {$EXTERNALSYM _CMSG_RECIPIENT_ENCODE_INFO}
  CMSG_RECIPIENT_ENCODE_INFO = _CMSG_RECIPIENT_ENCODE_INFO;
  {$NODEFINE CMSG_RECIPIENT_ENCODE_INFO}
  TCmsgRecipientEncodeInfo = CMSG_RECIPIENT_ENCODE_INFO;
  PCmsgRecipientEncodeInfo = PCMSG_RECIPIENT_ENCODE_INFO;

const
  CMSG_KEY_TRANS_RECIPIENT = 1;
  {$EXTERNALSYM CMSG_KEY_TRANS_RECIPIENT}
  CMSG_KEY_AGREE_RECIPIENT = 2;
  {$EXTERNALSYM CMSG_KEY_AGREE_RECIPIENT}
  CMSG_MAIL_LIST_RECIPIENT = 3;
  {$EXTERNALSYM CMSG_MAIL_LIST_RECIPIENT}

//+-------------------------------------------------------------------------
//  CMSG_RC2_AUX_INFO
//
//  AuxInfo for RC2 encryption algorithms. The pvEncryptionAuxInfo field
//  in CMSG_ENCRYPTED_ENCODE_INFO should be updated to point to this
//  structure. If not specified, defaults to 40 bit.
//
//  Note, this AuxInfo is only used when, the ContentEncryptionAlgorithm's
//  Parameter.cbData is zero. Otherwise, the Parameters is decoded to
//  get the bit length.
//
//  If CMSG_SP3_COMPATIBLE_ENCRYPT_FLAG is set in dwBitLen, then, SP3
//  compatible encryption is done and the bit length is ignored.
//--------------------------------------------------------------------------

type
  PCMSG_RC2_AUX_INFO = ^CMSG_RC2_AUX_INFO;
  {$EXTERNALSYM PCMSG_RC2_AUX_INFO}
  _CMSG_RC2_AUX_INFO = record
    cbSize: DWORD;
    dwBitLen: DWORD;
  end;
  {$EXTERNALSYM _CMSG_RC2_AUX_INFO}
  CMSG_RC2_AUX_INFO = _CMSG_RC2_AUX_INFO;
  {$EXTERNALSYM CMSG_RC2_AUX_INFO}
  TCmsgRc2AuxInfo = CMSG_RC2_AUX_INFO;
  PCmsgRc2AuxInfo = PCMSG_RC2_AUX_INFO;

//+-------------------------------------------------------------------------
//  CMSG_SP3_COMPATIBLE_AUX_INFO
//
//  AuxInfo for enabling SP3 compatible encryption.
//
//  The CMSG_SP3_COMPATIBLE_ENCRYPT_FLAG is set in dwFlags to enable SP3
//  compatible encryption. When set, uses zero salt instead of no salt,
//  the encryption algorithm parameters are NULL instead of containing the
//  encoded RC2 parameters or encoded IV octet string and the encrypted
//  symmetric key is encoded little endian instead of big endian.
//--------------------------------------------------------------------------

  PCMSG_SP3_COMPATIBLE_AUX_INFO = ^CMSG_SP3_COMPATIBLE_AUX_INFO;
  {$EXTERNALSYM PCMSG_SP3_COMPATIBLE_AUX_INFO}
  _CMSG_SP3_COMPATIBLE_AUX_INFO = record
    cbSize: DWORD;
    dwFlags: DWORD;
  end;
  {$EXTERNALSYM _CMSG_SP3_COMPATIBLE_AUX_INFO}
  CMSG_SP3_COMPATIBLE_AUX_INFO = _CMSG_SP3_COMPATIBLE_AUX_INFO;
  {$EXTERNALSYM CMSG_SP3_COMPATIBLE_AUX_INFO}
  TCmsgSp3CompatibleAuxInfo = CMSG_SP3_COMPATIBLE_AUX_INFO;
  PCmsgSp3CompatibleAuxInfo = PCMSG_SP3_COMPATIBLE_AUX_INFO;

const
  CMSG_SP3_COMPATIBLE_ENCRYPT_FLAG = DWORD($80000000);
  {$EXTERNALSYM CMSG_SP3_COMPATIBLE_ENCRYPT_FLAG}

//+-------------------------------------------------------------------------
//  CMSG_RC4_AUX_INFO
//
//  AuxInfo for RC4 encryption algorithms. The pvEncryptionAuxInfo field
//  in CMSG_ENCRYPTED_ENCODE_INFO should be updated to point to this
//  structure. If not specified, uses the CSP's default bit length with no
//  salt. Note, the base CSP has a 40 bit default and the enhanced CSP has
//  a 128 bit default.
//
//  If CMSG_RC4_NO_SALT_FLAG is set in dwBitLen, then, no salt is generated.
//  Otherwise, (128 - dwBitLen)/8 bytes of salt are generated and encoded
//  as an OCTET STRING in the algorithm parameters field.
//--------------------------------------------------------------------------

type
  PCMSG_RC4_AUX_INFO = ^CMSG_RC4_AUX_INFO;
  {$EXTERNALSYM PCMSG_RC4_AUX_INFO}
  _CMSG_RC4_AUX_INFO = record
    cbSize: DWORD;
    dwBitLen: DWORD;
  end;
  {$EXTERNALSYM _CMSG_RC4_AUX_INFO}
  CMSG_RC4_AUX_INFO = _CMSG_RC4_AUX_INFO;
  {$EXTERNALSYM CMSG_RC4_AUX_INFO}
  TCmsgRc4AuxInfo = CMSG_RC4_AUX_INFO;
  PCmsgRc4AuxInfo = PCMSG_RC4_AUX_INFO;

const
  CMSG_RC4_NO_SALT_FLAG = $40000000;
  {$EXTERNALSYM CMSG_RC4_NO_SALT_FLAG}

//+-------------------------------------------------------------------------
//  CMSG_SIGNED_AND_ENVELOPED
//
//  For PKCS #7, a signed and enveloped message doesn't have the
//  signer's authenticated or unauthenticated attributes. Otherwise, a
//  combination of the CMSG_SIGNED_ENCODE_INFO and CMSG_ENVELOPED_ENCODE_INFO.
//--------------------------------------------------------------------------

type
  PCMSG_SIGNED_AND_ENVELOPED_ENCODE_INFO = ^CMSG_SIGNED_AND_ENVELOPED_ENCODE_INFO;
  {$EXTERNALSYM PCMSG_SIGNED_AND_ENVELOPED_ENCODE_INFO}
  _CMSG_SIGNED_AND_ENVELOPED_ENCODE_INFO = record
    cbSize: DWORD;
    SignedInfo: CMSG_SIGNED_ENCODE_INFO;
    EnvelopedInfo: CMSG_ENVELOPED_ENCODE_INFO;
  end;
  {$EXTERNALSYM _CMSG_SIGNED_AND_ENVELOPED_ENCODE_INFO}
  CMSG_SIGNED_AND_ENVELOPED_ENCODE_INFO = _CMSG_SIGNED_AND_ENVELOPED_ENCODE_INFO;
  {$EXTERNALSYM CMSG_SIGNED_AND_ENVELOPED_ENCODE_INFO}
  TCmsgSignedAndEnvelopedEncodeInfo = CMSG_SIGNED_AND_ENVELOPED_ENCODE_INFO;
  PCmsgSignedAndEnvelopedEncodeInfo = PCMSG_SIGNED_AND_ENVELOPED_ENCODE_INFO;

//+-------------------------------------------------------------------------
//  CMSG_HASHED
//
//  hCryptProv is used to do the hash. Doesn't need to use a private key.
//
//  If CMSG_CRYPT_RELEASE_CONTEXT_FLAG is set in the dwFlags
//  passed to CryptMsgOpenToEncode(), the hCryptProv is released.
//
//  If fDetachedHash is set, then, the encoded message doesn't contain
//  any content (its treated as NULL Data)
//
//  pvHashAuxInfo currently isn't used and must be set to NULL.
//--------------------------------------------------------------------------

  PCMSG_HASHED_ENCODE_INFO = ^CMSG_HASHED_ENCODE_INFO;
  {$EXTERNALSYM PCMSG_HASHED_ENCODE_INFO}
  _CMSG_HASHED_ENCODE_INFO = record
    cbSize: DWORD;
    hCryptProv: HCRYPTPROV;
    HashAlgorithm: CRYPT_ALGORITHM_IDENTIFIER;
    pvHashAuxInfo: Pointer;
  end;
  {$EXTERNALSYM _CMSG_HASHED_ENCODE_INFO}
  CMSG_HASHED_ENCODE_INFO = _CMSG_HASHED_ENCODE_INFO;
  {$EXTERNALSYM CMSG_HASHED_ENCODE_INFO}
  TCmsgHashedEncodeInfo = CMSG_HASHED_ENCODE_INFO;
  PCmsgHashedEncodeInfo = PCMSG_HASHED_ENCODE_INFO;

//+-------------------------------------------------------------------------
//  CMSG_ENCRYPTED
//
//  The key used to encrypt the message is identified outside of the message
//  content (for example, password).
//
//  The content input to CryptMsgUpdate has already been encrypted.
//
//  pvEncryptionAuxInfo currently isn't used and must be set to NULL.
//--------------------------------------------------------------------------

  PCMSG_ENCRYPTED_ENCODE_INFO = ^CMSG_ENCRYPTED_ENCODE_INFO;
  {$EXTERNALSYM PCMSG_ENCRYPTED_ENCODE_INFO}
  _CMSG_ENCRYPTED_ENCODE_INFO = record
    cbSize: DWORD;
    ContentEncryptionAlgorithm: CRYPT_ALGORITHM_IDENTIFIER;
    pvEncryptionAuxInfo: Pointer;
  end;
  {$EXTERNALSYM _CMSG_ENCRYPTED_ENCODE_INFO}
  CMSG_ENCRYPTED_ENCODE_INFO = _CMSG_ENCRYPTED_ENCODE_INFO;
  {$EXTERNALSYM CMSG_ENCRYPTED_ENCODE_INFO}
  TCmsgEncryptedEncodeInfo = CMSG_ENCRYPTED_ENCODE_INFO;
  PCmsgEncryptedEncodeInfo = PCMSG_ENCRYPTED_ENCODE_INFO;

//+-------------------------------------------------------------------------
//  This parameter allows messages to be of variable length with streamed
//  output.
//
//  By default, messages are of a definite length and
//  CryptMsgGetParam(CMSG_CONTENT_PARAM) is
//  called to get the cryptographically processed content. Until closed,
//  the handle keeps a copy of the processed content.
//
//  With streamed output, the processed content can be freed as its streamed.
//
//  If the length of the content to be updated is known at the time of the
//  open, then, ContentLength should be set to that length. Otherwise, it
//  should be set to CMSG_INDEFINITE_LENGTH.
//--------------------------------------------------------------------------

type
  PFN_CMSG_STREAM_OUTPUT = function (pvArg: Pointer; pbData: LPBYTE;
    cbData: DWORD; fFinal: BOOL): BOOL; stdcall;
  {$EXTERNALSYM PFN_CMSG_STREAM_OUTPUT}
  PFnCMsgStreamOutput = PFN_CMSG_STREAM_OUTPUT;

const
  CMSG_INDEFINITE_LENGTH = DWORD($FFFFFFFF);
  {$EXTERNALSYM CMSG_INDEFINITE_LENGTH}

type
  PCMSG_STREAM_INFO = ^CMSG_STREAM_INFO;
  {$EXTERNALSYM PCMSG_STREAM_INFO}
  _CMSG_STREAM_INFO = record
    cbContent: DWORD;
    pfnStreamOutput: PFN_CMSG_STREAM_OUTPUT;
    pvArg: Pointer;
  end;
  {$EXTERNALSYM _CMSG_STREAM_INFO}
  CMSG_STREAM_INFO = _CMSG_STREAM_INFO;
  {$EXTERNALSYM CMSG_STREAM_INFO}
  TCmsgStreamInfo = CMSG_STREAM_INFO;
  PCmsgStreamInfo = PCMSG_STREAM_INFO;

//+-------------------------------------------------------------------------
//  Open dwFlags
//--------------------------------------------------------------------------

const
  CMSG_BARE_CONTENT_FLAG             = $00000001;
  {$EXTERNALSYM CMSG_BARE_CONTENT_FLAG}
  CMSG_LENGTH_ONLY_FLAG              = $00000002;
  {$EXTERNALSYM CMSG_LENGTH_ONLY_FLAG}
  CMSG_DETACHED_FLAG                 = $00000004;
  {$EXTERNALSYM CMSG_DETACHED_FLAG}
  CMSG_AUTHENTICATED_ATTRIBUTES_FLAG = $00000008;
  {$EXTERNALSYM CMSG_AUTHENTICATED_ATTRIBUTES_FLAG}
  CMSG_CONTENTS_OCTETS_FLAG          = $00000010;
  {$EXTERNALSYM CMSG_CONTENTS_OCTETS_FLAG}
  CMSG_MAX_LENGTH_FLAG               = $00000020;
  {$EXTERNALSYM CMSG_MAX_LENGTH_FLAG}

// When set, nonData type inner content is encapsulated within an
// OCTET STRING. Applicable to both Signed and Enveloped messages.

  CMSG_CMS_ENCAPSULATED_CONTENT_FLAG = $00000040;
  {$EXTERNALSYM CMSG_CMS_ENCAPSULATED_CONTENT_FLAG}

// If set, then, the hCryptProv passed to CryptMsgOpenToEncode or
// CryptMsgOpenToDecode is released on the final CryptMsgClose.
// Not released if CryptMsgOpenToEncode or CryptMsgOpenToDecode fails.
//
// Note, the envelope recipient hCryptProv's aren't released.

  CMSG_CRYPT_RELEASE_CONTEXT_FLAG = $00008000;
  {$EXTERNALSYM CMSG_CRYPT_RELEASE_CONTEXT_FLAG}

//+-------------------------------------------------------------------------
//  Open a cryptographic message for encoding
//
//  For PKCS #7:
//  If the content to be passed to CryptMsgUpdate has already
//  been message encoded (the input to CryptMsgUpdate is the streamed output
//  from another message encode), then, the CMSG_ENCODED_CONTENT_INFO_FLAG should
//  be set in dwFlags. If not set, then, the inner ContentType is Data and
//  the input to CryptMsgUpdate is treated as the inner Data type's Content,
//  a string of bytes.
//  If CMSG_BARE_CONTENT_FLAG is specified for a streamed message,
//  the streamed output will not have an outer ContentInfo wrapper. This
//  makes it suitable to be streamed into an enclosing message.
//
//  The pStreamInfo parameter needs to be set to stream the encoded message
//  output.
//--------------------------------------------------------------------------

function CryptMsgOpenToEncode(dwMsgEncodingType, dwFlags, dwMsgType: DWORD;
  pvMsgEncodeInfo: Pointer; pszInnerContentObjID: LPSTR;
  pStreamInfo: PCMSG_STREAM_INFO): HCRYPTMSG; stdcall;
{$EXTERNALSYM CryptMsgOpenToEncode}

//+-------------------------------------------------------------------------
//  Calculate the length of an encoded cryptographic message.
//
//  Calculates the length of the encoded message given the
//  message type, encoding parameters and total length of
//  the data to be updated. Note, this might not be the exact length. However,
//  it will always be greater than or equal to the actual length.
//--------------------------------------------------------------------------

function CryptMsgCalculateEncodedLength(dwMsgEncodingType, dwFlags, dwMsgType: DWORD;
  pvMsgEncodeInfo: Pointer; pszInnerContentObjID: LPSTR; cbData: DWORD): DWORD; stdcall;
{$EXTERNALSYM CryptMsgCalculateEncodedLength}

//+-------------------------------------------------------------------------
//  Open a cryptographic message for decoding
//
//  hCryptProv specifies the crypto provider to use for hashing and/or
//  decrypting the message. If hCryptProv is NULL, a default crypt provider
//  is used.
//
//  Currently pRecipientInfo isn't used and should be set to NULL.
//
//  The pStreamInfo parameter needs to be set to stream the decoded content
//  output.
//--------------------------------------------------------------------------

function CryptMsgOpenToDecode(dwMsgEncodingType, dwFlags, dwMsgType: DWORD;
  hCryptProv: HCRYPTPROV; pRecipientInfo: PCERT_INFO;
  pStreamInfo: PCMSG_STREAM_INFO): HCRYPTMSG; stdcall;
{$EXTERNALSYM CryptMsgOpenToDecode}

//+-------------------------------------------------------------------------
//  Duplicate a cryptographic message handle
//--------------------------------------------------------------------------

function CryptMsgDuplicate(hCryptMsg: HCRYPTMSG): HCRYPTMSG; stdcall;
{$EXTERNALSYM CryptMsgDuplicate}

//+-------------------------------------------------------------------------
//  Close a cryptographic message handle
//
//  LastError is preserved unless FALSE is returned.
//--------------------------------------------------------------------------

function CryptMsgClose(hCryptMsg: HCRYPTMSG): BOOL; stdcall;
{$EXTERNALSYM CryptMsgClose}

//+-------------------------------------------------------------------------
//  Update the content of a cryptographic message. Depending on how the
//  message was opened, the content is either encoded or decoded.
//
//  This function is repetitively called to append to the message content.
//  fFinal is set to identify the last update. On fFinal, the encode/decode
//  is completed. The encoded/decoded content and the decoded parameters
//  are valid until the open and all duplicated handles are closed.
//--------------------------------------------------------------------------

function CryptMsgUpdate(hCryptMsg: HCRYPTMSG; pbData: LPBYTE; cbData: DWORD;
  fFinal: BOOL): BOOL; stdcall;
{$EXTERNALSYM CryptMsgUpdate}

//+-------------------------------------------------------------------------
//  Get a parameter after encoding/decoding a cryptographic message. Called
//  after the final CryptMsgUpdate. Only the CMSG_CONTENT_PARAM and
//  CMSG_COMPUTED_HASH_PARAM are valid for an encoded message.
//
//  For an encoded HASHED message, the CMSG_COMPUTED_HASH_PARAM can be got
//  before any CryptMsgUpdates to get its length.
//
//  The pvData type definition depends on the dwParamType value.
//
//  Elements pointed to by fields in the pvData structure follow the
//  structure. Therefore, *pcbData may exceed the size of the structure.
//
//  Upon input, if *pcbData == 0, then, *pcbData is updated with the length
//  of the data and the pvData parameter is ignored.
//
//  Upon return, *pcbData is updated with the length of the data.
//
//  The OBJID BLOBs returned in the pvData structures point to
//  their still encoded representation. The appropriate functions
//  must be called to decode the information.
//
//  See below for a list of the parameters to get.
//--------------------------------------------------------------------------

function CryptMsgGetParam(hCryptMsg: HCRYPTMSG; dwParamType, dwIndex: DWORD;
  pvData: Pointer; var pcbData: DWORD): BOOL; stdcall;
{$EXTERNALSYM CryptMsgGetParam}

//+-------------------------------------------------------------------------
//  Get parameter types and their corresponding data structure definitions.
//--------------------------------------------------------------------------

const
  CMSG_TYPE_PARAM                              = 1;
  {$EXTERNALSYM CMSG_TYPE_PARAM}
  CMSG_CONTENT_PARAM                           = 2;
  {$EXTERNALSYM CMSG_CONTENT_PARAM}
  CMSG_BARE_CONTENT_PARAM                      = 3;
  {$EXTERNALSYM CMSG_BARE_CONTENT_PARAM}
  CMSG_INNER_CONTENT_TYPE_PARAM                = 4;
  {$EXTERNALSYM CMSG_INNER_CONTENT_TYPE_PARAM}
  CMSG_SIGNER_COUNT_PARAM                      = 5;
  {$EXTERNALSYM CMSG_SIGNER_COUNT_PARAM}
  CMSG_SIGNER_INFO_PARAM                       = 6;
  {$EXTERNALSYM CMSG_SIGNER_INFO_PARAM}
  CMSG_SIGNER_CERT_INFO_PARAM                  = 7;
  {$EXTERNALSYM CMSG_SIGNER_CERT_INFO_PARAM}
  CMSG_SIGNER_HASH_ALGORITHM_PARAM             = 8;
  {$EXTERNALSYM CMSG_SIGNER_HASH_ALGORITHM_PARAM}
  CMSG_SIGNER_AUTH_ATTR_PARAM                  = 9;
  {$EXTERNALSYM CMSG_SIGNER_AUTH_ATTR_PARAM}
  CMSG_SIGNER_UNAUTH_ATTR_PARAM                = 10;
  {$EXTERNALSYM CMSG_SIGNER_UNAUTH_ATTR_PARAM}
  CMSG_CERT_COUNT_PARAM                        = 11;
  {$EXTERNALSYM CMSG_CERT_COUNT_PARAM}
  CMSG_CERT_PARAM                              = 12;
  {$EXTERNALSYM CMSG_CERT_PARAM}
  CMSG_CRL_COUNT_PARAM                         = 13;
  {$EXTERNALSYM CMSG_CRL_COUNT_PARAM}
  CMSG_CRL_PARAM                               = 14;
  {$EXTERNALSYM CMSG_CRL_PARAM}
  CMSG_ENVELOPE_ALGORITHM_PARAM                = 15;
  {$EXTERNALSYM CMSG_ENVELOPE_ALGORITHM_PARAM}
  CMSG_RECIPIENT_COUNT_PARAM                   = 17;
  {$EXTERNALSYM CMSG_RECIPIENT_COUNT_PARAM}
  CMSG_RECIPIENT_INDEX_PARAM                   = 18;
  {$EXTERNALSYM CMSG_RECIPIENT_INDEX_PARAM}
  CMSG_RECIPIENT_INFO_PARAM                    = 19;
  {$EXTERNALSYM CMSG_RECIPIENT_INFO_PARAM}
  CMSG_HASH_ALGORITHM_PARAM                    = 20;
  {$EXTERNALSYM CMSG_HASH_ALGORITHM_PARAM}
  CMSG_HASH_DATA_PARAM                         = 21;
  {$EXTERNALSYM CMSG_HASH_DATA_PARAM}
  CMSG_COMPUTED_HASH_PARAM                     = 22;
  {$EXTERNALSYM CMSG_COMPUTED_HASH_PARAM}
  CMSG_ENCRYPT_PARAM                           = 26;
  {$EXTERNALSYM CMSG_ENCRYPT_PARAM}
  CMSG_ENCRYPTED_DIGEST                        = 27;
  {$EXTERNALSYM CMSG_ENCRYPTED_DIGEST}
  CMSG_ENCODED_SIGNER                          = 28;
  {$EXTERNALSYM CMSG_ENCODED_SIGNER}
  CMSG_ENCODED_MESSAGE                         = 29;
  {$EXTERNALSYM CMSG_ENCODED_MESSAGE}
  CMSG_VERSION_PARAM                           = 30;
  {$EXTERNALSYM CMSG_VERSION_PARAM}
  CMSG_ATTR_CERT_COUNT_PARAM                   = 31;
  {$EXTERNALSYM CMSG_ATTR_CERT_COUNT_PARAM}
  CMSG_ATTR_CERT_PARAM                         = 32;
  {$EXTERNALSYM CMSG_ATTR_CERT_PARAM}
  CMSG_CMS_RECIPIENT_COUNT_PARAM               = 33;
  {$EXTERNALSYM CMSG_CMS_RECIPIENT_COUNT_PARAM}
  CMSG_CMS_RECIPIENT_INDEX_PARAM               = 34;
  {$EXTERNALSYM CMSG_CMS_RECIPIENT_INDEX_PARAM}
  CMSG_CMS_RECIPIENT_ENCRYPTED_KEY_INDEX_PARAM = 35;
  {$EXTERNALSYM CMSG_CMS_RECIPIENT_ENCRYPTED_KEY_INDEX_PARAM}
  CMSG_CMS_RECIPIENT_INFO_PARAM                = 36;
  {$EXTERNALSYM CMSG_CMS_RECIPIENT_INFO_PARAM}
  CMSG_UNPROTECTED_ATTR_PARAM                  = 37;
  {$EXTERNALSYM CMSG_UNPROTECTED_ATTR_PARAM}
  CMSG_SIGNER_CERT_ID_PARAM                    = 38;
  {$EXTERNALSYM CMSG_SIGNER_CERT_ID_PARAM}
  CMSG_CMS_SIGNER_INFO_PARAM                   = 39;
  {$EXTERNALSYM CMSG_CMS_SIGNER_INFO_PARAM}

//+-------------------------------------------------------------------------
//  CMSG_TYPE_PARAM
//
//  The type of the decoded message.
//
//  pvData points to a DWORD
//--------------------------------------------------------------------------

//+-------------------------------------------------------------------------
//  CMSG_CONTENT_PARAM
//
//  The encoded content of a cryptographic message. Depending on how the
//  message was opened, the content is either the whole PKCS#7
//  message (opened to encode) or the inner content (opened to decode).
//  In the decode case, the decrypted content is returned, if enveloped.
//  If not enveloped, and if the inner content is of type DATA, the returned
//  data is the contents octets of the inner content.
//
//  pvData points to the buffer receiving the content bytes
//--------------------------------------------------------------------------

//+-------------------------------------------------------------------------
//  CMSG_BARE_CONTENT_PARAM
//
//  The encoded content of an encoded cryptographic message, without the
//  outer layer of ContentInfo. That is, only the encoding of the
//  ContentInfo.content field is returned.
//
//  pvData points to the buffer receiving the content bytes
//--------------------------------------------------------------------------

//+-------------------------------------------------------------------------
//  CMSG_INNER_CONTENT_TYPE_PARAM
//
//  The type of the inner content of a decoded cryptographic message,
//  in the form of a NULL-terminated object identifier string
//  (eg. "1.2.840.113549.1.7.1").
//
//  pvData points to the buffer receiving the object identifier string
//--------------------------------------------------------------------------

//+-------------------------------------------------------------------------
//  CMSG_SIGNER_COUNT_PARAM
//
//  Count of signers in a SIGNED or SIGNED_AND_ENVELOPED message
//
//  pvData points to a DWORD
//--------------------------------------------------------------------------

//+-------------------------------------------------------------------------
//  CMSG_SIGNER_CERT_INFO_PARAM
//
//  To get all the signers, repetitively call CryptMsgGetParam, with
//  dwIndex set to 0 .. SignerCount - 1.
//
//  pvData points to a CERT_INFO struct.
//
//  Only the following fields have been updated in the CERT_INFO struct:
//  Issuer and SerialNumber.
//
//  Note, if the KEYID choice was selected for a CMS SignerId, then, the
//  SerialNumber is 0 and the Issuer is encoded containing a single RDN with a
//  single Attribute whose OID is szOID_KEYID_RDN, value type is
//  CERT_RDN_OCTET_STRING and value is the KEYID. When the
//  CertGetSubjectCertificateFromStore and
//  CertFindCertificateInStore(CERT_FIND_SUBJECT_CERT) APIs see this
//  special KEYID Issuer and SerialNumber, they do a KEYID match.
//--------------------------------------------------------------------------

//+-------------------------------------------------------------------------
//  CMSG_SIGNER_INFO_PARAM
//
//  To get all the signers, repetitively call CryptMsgGetParam, with
//  dwIndex set to 0 .. SignerCount - 1.
//
//  pvData points to a CMSG_SIGNER_INFO struct.
//
//  Note, if the KEYID choice was selected for a CMS SignerId, then, the
//  SerialNumber is 0 and the Issuer is encoded containing a single RDN with a
//  single Attribute whose OID is szOID_KEYID_RDN, value type is
//  CERT_RDN_OCTET_STRING and value is the KEYID. When the
//  CertGetSubjectCertificateFromStore and
//  CertFindCertificateInStore(CERT_FIND_SUBJECT_CERT) APIs see this
//  special KEYID Issuer and SerialNumber, they do a KEYID match.
//--------------------------------------------------------------------------

type
  PCMSG_SIGNER_INFO = ^CMSG_SIGNER_INFO;
  {$EXTERNALSYM PCMSG_SIGNER_INFO}
  _CMSG_SIGNER_INFO = record
    dwVersion: DWORD;
    Issuer: CERT_NAME_BLOB;
    SerialNumber: CRYPT_INTEGER_BLOB;
    HashAlgorithm: CRYPT_ALGORITHM_IDENTIFIER;
    HashEncryptionAlgorithm: CRYPT_ALGORITHM_IDENTIFIER;
    EncryptedHash: CRYPT_DATA_BLOB;
    AuthAttrs: CRYPT_ATTRIBUTES;
    UnauthAttrs: CRYPT_ATTRIBUTES;
  end;
  {$EXTERNALSYM _CMSG_SIGNER_INFO}
  CMSG_SIGNER_INFO = _CMSG_SIGNER_INFO;
  {$EXTERNALSYM CMSG_SIGNER_INFO}
  TCmsgSignerInfo = CMSG_SIGNER_INFO;
  PCmsgSignerInfo = PCMSG_SIGNER_INFO;

//+-------------------------------------------------------------------------
//  CMSG_SIGNER_CERT_ID_PARAM
//
//  To get all the signers, repetitively call CryptMsgGetParam, with
//  dwIndex set to 0 .. SignerCount - 1.
//
//  pvData points to a CERT_ID struct.
//--------------------------------------------------------------------------

//+-------------------------------------------------------------------------
//  CMSG_CMS_SIGNER_INFO_PARAM
//
//  Same as CMSG_SIGNER_INFO_PARAM, except, contains SignerId instead of
//  Issuer and SerialNumber.
//
//  To get all the signers, repetitively call CryptMsgGetParam, with
//  dwIndex set to 0 .. SignerCount - 1.
//
//  pvData points to a CMSG_CMS_SIGNER_INFO struct.
//--------------------------------------------------------------------------

  PCMSG_CMS_SIGNER_INFO = ^CMSG_CMS_SIGNER_INFO;
  {$EXTERNALSYM PCMSG_CMS_SIGNER_INFO}
  _CMSG_CMS_SIGNER_INFO = record
    dwVersion: DWORD;
    SignerId: CERT_ID;
    HashAlgorithm: CRYPT_ALGORITHM_IDENTIFIER;
    HashEncryptionAlgorithm: CRYPT_ALGORITHM_IDENTIFIER;
    EncryptedHash: CRYPT_DATA_BLOB;
    AuthAttrs: CRYPT_ATTRIBUTES;
    UnauthAttrs: CRYPT_ATTRIBUTES;
  end;
  {$EXTERNALSYM _CMSG_CMS_SIGNER_INFO}
  CMSG_CMS_SIGNER_INFO = _CMSG_CMS_SIGNER_INFO;
  {$EXTERNALSYM CMSG_CMS_SIGNER_INFO}
  TCmsgCmsSignerInfo = CMSG_CMS_SIGNER_INFO;
  PCmsgCmsSignerInfo = PCMSG_CMS_SIGNER_INFO;

//+-------------------------------------------------------------------------
//  CMSG_SIGNER_HASH_ALGORITHM_PARAM
//
//  This parameter specifies the HashAlgorithm that was used for the signer.
//
//  Set dwIndex to iterate through all the signers.
//
//  pvData points to an CRYPT_ALGORITHM_IDENTIFIER struct.
//--------------------------------------------------------------------------

//+-------------------------------------------------------------------------
//  CMSG_SIGNER_AUTH_ATTR_PARAM
//
//  The authenticated attributes for the signer.
//
//  Set dwIndex to iterate through all the signers.
//
//  pvData points to a CMSG_ATTR struct.
//--------------------------------------------------------------------------

  CMSG_ATTR = CRYPT_ATTRIBUTES;
  {$EXTERNALSYM CMSG_ATTR}
  PCMSG_ATTR = ^CRYPT_ATTRIBUTES;
  {$EXTERNALSYM PCMSG_ATTR}

//+-------------------------------------------------------------------------
//  CMSG_SIGNER_UNAUTH_ATTR_PARAM
//
//  The unauthenticated attributes for the signer.
//
//  Set dwIndex to iterate through all the signers.
//
//  pvData points to a CMSG_ATTR struct.
//--------------------------------------------------------------------------

//+-------------------------------------------------------------------------
//  CMSG_CERT_COUNT_PARAM
//
//  Count of certificates in a SIGNED or SIGNED_AND_ENVELOPED message.
//
//  CMS, also supports certificates in an ENVELOPED message.
//
//  pvData points to a DWORD
//--------------------------------------------------------------------------

//+-------------------------------------------------------------------------
//  CMSG_CERT_PARAM
//
//  To get all the certificates, repetitively call CryptMsgGetParam, with
//  dwIndex set to 0 .. CertCount - 1.
//
//  pvData points to an array of the certificate's encoded bytes.
//--------------------------------------------------------------------------

//+-------------------------------------------------------------------------
//  CMSG_CRL_COUNT_PARAM
//
//  Count of CRLs in a SIGNED or SIGNED_AND_ENVELOPED message.
//
//  CMS, also supports CRLs in an ENVELOPED message.
//
//  pvData points to a DWORD
//--------------------------------------------------------------------------

//+-------------------------------------------------------------------------
//  CMSG_CRL_PARAM
//
//  To get all the CRLs, repetitively call CryptMsgGetParam, with
//  dwIndex set to 0 .. CrlCount - 1.
//
//  pvData points to an array of the CRL's encoded bytes.
//--------------------------------------------------------------------------


//+-------------------------------------------------------------------------
//  CMSG_ENVELOPE_ALGORITHM_PARAM
//
//  The ContentEncryptionAlgorithm that was used in
//  an ENVELOPED or SIGNED_AND_ENVELOPED message.
//
//  For streaming you must be able to successfully get this parameter before
//  doing a CryptMsgControl decrypt.
//
//  pvData points to an CRYPT_ALGORITHM_IDENTIFIER struct.
//--------------------------------------------------------------------------

//+-------------------------------------------------------------------------
//  CMSG_RECIPIENT_COUNT_PARAM
//
//  Count of recipients in an ENVELOPED or SIGNED_AND_ENVELOPED message.
//
//  Count of key transport recepients.
//
//  The CMSG_CMS_RECIPIENT_COUNT_PARAM has the total count of
//  recipients (it also includes key agree and mail list recipients).
//
//  pvData points to a DWORD
//--------------------------------------------------------------------------

//+-------------------------------------------------------------------------
//  CMSG_RECIPIENT_INDEX_PARAM
//
//  Index of the recipient used to decrypt an ENVELOPED or SIGNED_AND_ENVELOPED
//  message.
//
//  Index of a key transport recipient. If a non key transport
//  recipient was used to decrypt, fails with LastError set to
//  CRYPT_E_INVALID_INDEX.
//
//  pvData points to a DWORD
//--------------------------------------------------------------------------

//+-------------------------------------------------------------------------
//  CMSG_RECIPIENT_INFO_PARAM
//
//  To get all the recipients, repetitively call CryptMsgGetParam, with
//  dwIndex set to 0 .. RecipientCount - 1.
//
//  Only returns the key transport recepients.
//
//  The CMSG_CMS_RECIPIENT_INFO_PARAM returns all recipients.
//
//  pvData points to a CERT_INFO struct.
//
//  Only the following fields have been updated in the CERT_INFO struct:
//  Issuer, SerialNumber and PublicKeyAlgorithm. The PublicKeyAlgorithm
//  specifies the KeyEncryptionAlgorithm that was used.
//
//  Note, if the KEYID choice was selected for a key transport recipient, then,
//  the SerialNumber is 0 and the Issuer is encoded containing a single RDN
//  with a single Attribute whose OID is szOID_KEYID_RDN, value type is
//  CERT_RDN_OCTET_STRING and value is the KEYID. When the
//  CertGetSubjectCertificateFromStore and
//  CertFindCertificateInStore(CERT_FIND_SUBJECT_CERT) APIs see this
//  special KEYID Issuer and SerialNumber, they do a KEYID match.
//--------------------------------------------------------------------------

//+-------------------------------------------------------------------------
//  CMSG_HASH_ALGORITHM_PARAM
//
//  The HashAlgorithm in a HASHED message.
//
//  pvData points to an CRYPT_ALGORITHM_IDENTIFIER struct.
//--------------------------------------------------------------------------

//+-------------------------------------------------------------------------
//  CMSG_HASH_DATA_PARAM
//
//  The hash in a HASHED message.
//
//  pvData points to an array of bytes.
//--------------------------------------------------------------------------

//+-------------------------------------------------------------------------
//  CMSG_COMPUTED_HASH_PARAM
//
//  The computed hash for a HASHED message.
//  This may be called for either an encoded or decoded message.
//
//  Also, the computed hash for one of the signer's in a SIGNED message.
//  It may be called for either an encoded or decoded message after the
//  final update.  Set dwIndex to iterate through all the signers.
//
//  pvData points to an array of bytes.
//--------------------------------------------------------------------------

//+-------------------------------------------------------------------------
//  CMSG_ENCRYPT_PARAM
//
//  The ContentEncryptionAlgorithm that was used in an ENCRYPTED message.
//
//  pvData points to an CRYPT_ALGORITHM_IDENTIFIER struct.
//--------------------------------------------------------------------------

//+-------------------------------------------------------------------------
//  CMSG_ENCODED_MESSAGE
//
//  The full encoded message. This is useful in the case of a decoded
//  message which has been modified (eg. a signed-data or
//  signed-and-enveloped-data message which has been countersigned).
//
//  pvData points to an array of the message's encoded bytes.
//--------------------------------------------------------------------------

//+-------------------------------------------------------------------------
//  CMSG_VERSION_PARAM
//
//  The version of the decoded message.
//
//  pvData points to a DWORD
//--------------------------------------------------------------------------

const
  CMSG_SIGNED_DATA_V1               = 1;
  {$EXTERNALSYM CMSG_SIGNED_DATA_V1}
  CMSG_SIGNED_DATA_V3               = 3;
  {$EXTERNALSYM CMSG_SIGNED_DATA_V3}
  CMSG_SIGNED_DATA_PKCS_1_5_VERSION = CMSG_SIGNED_DATA_V1;
  {$EXTERNALSYM CMSG_SIGNED_DATA_PKCS_1_5_VERSION}
  CMSG_SIGNED_DATA_CMS_VERSION      = CMSG_SIGNED_DATA_V3;
  {$EXTERNALSYM CMSG_SIGNED_DATA_CMS_VERSION}

  CMSG_SIGNER_INFO_V1               = 1;
  {$EXTERNALSYM CMSG_SIGNER_INFO_V1}
  CMSG_SIGNER_INFO_V3               = 3;
  {$EXTERNALSYM CMSG_SIGNER_INFO_V3}
  CMSG_SIGNER_INFO_PKCS_1_5_VERSION = CMSG_SIGNER_INFO_V1;
  {$EXTERNALSYM CMSG_SIGNER_INFO_PKCS_1_5_VERSION}
  CMSG_SIGNER_INFO_CMS_VERSION      = CMSG_SIGNER_INFO_V3;
  {$EXTERNALSYM CMSG_SIGNER_INFO_CMS_VERSION}

  CMSG_HASHED_DATA_V0               = 0;
  {$EXTERNALSYM CMSG_HASHED_DATA_V0}
  CMSG_HASHED_DATA_V2               = 2;
  {$EXTERNALSYM CMSG_HASHED_DATA_V2}
  CMSG_HASHED_DATA_PKCS_1_5_VERSION = CMSG_HASHED_DATA_V0;
  {$EXTERNALSYM CMSG_HASHED_DATA_PKCS_1_5_VERSION}
  CMSG_HASHED_DATA_CMS_VERSION      = CMSG_HASHED_DATA_V2;
  {$EXTERNALSYM CMSG_HASHED_DATA_CMS_VERSION}

  CMSG_ENVELOPED_DATA_V0               = 0;
  {$EXTERNALSYM CMSG_ENVELOPED_DATA_V0}
  CMSG_ENVELOPED_DATA_V2               = 2;
  {$EXTERNALSYM CMSG_ENVELOPED_DATA_V2}
  CMSG_ENVELOPED_DATA_PKCS_1_5_VERSION = CMSG_ENVELOPED_DATA_V0;
  {$EXTERNALSYM CMSG_ENVELOPED_DATA_PKCS_1_5_VERSION}
  CMSG_ENVELOPED_DATA_CMS_VERSION      = CMSG_ENVELOPED_DATA_V2;
  {$EXTERNALSYM CMSG_ENVELOPED_DATA_CMS_VERSION}

//+-------------------------------------------------------------------------
//  CMSG_ATTR_CERT_COUNT_PARAM
//
//  Count of attribute certificates in a SIGNED or ENVELOPED message.
//
//  pvData points to a DWORD
//--------------------------------------------------------------------------

//+-------------------------------------------------------------------------
//  CMSG_ATTR_CERT_PARAM
//
//  To get all the attribute certificates, repetitively call CryptMsgGetParam,
//  with dwIndex set to 0 .. AttrCertCount - 1.
//
//  pvData points to an array of the attribute certificate's encoded bytes.
//--------------------------------------------------------------------------

//+-------------------------------------------------------------------------
//  CMSG_CMS_RECIPIENT_COUNT_PARAM
//
//  Count of all CMS recipients in an ENVELOPED message.
//
//  pvData points to a DWORD
//--------------------------------------------------------------------------

//+-------------------------------------------------------------------------
//  CMSG_CMS_RECIPIENT_INDEX_PARAM
//
//  Index of the CMS recipient used to decrypt an ENVELOPED message.
//
//  pvData points to a DWORD
//--------------------------------------------------------------------------

//+-------------------------------------------------------------------------
//  CMSG_CMS_RECIPIENT_ENCRYPTED_KEY_INDEX_PARAM
//
//  For a CMS key agreement recipient, the index of the encrypted key
//  used to decrypt an ENVELOPED message.
//
//  pvData points to a DWORD
//--------------------------------------------------------------------------

//+-------------------------------------------------------------------------
//  CMSG_CMS_RECIPIENT_INFO_PARAM
//
//  To get all the CMS recipients, repetitively call CryptMsgGetParam, with
//  dwIndex set to 0 .. CmsRecipientCount - 1.
//
//  pvData points to a CMSG_CMS_RECIPIENT_INFO struct.
//--------------------------------------------------------------------------

type
  PCMSG_KEY_TRANS_RECIPIENT_INFO = ^CMSG_KEY_TRANS_RECIPIENT_INFO;
  {$EXTERNALSYM PCMSG_KEY_TRANS_RECIPIENT_INFO}
  _CMSG_KEY_TRANS_RECIPIENT_INFO = record
    dwVersion: DWORD;
    // Currently, only ISSUER_SERIAL_NUMBER or KEYID choices
    RecipientId: CERT_ID;
    KeyEncryptionAlgorithm: CRYPT_ALGORITHM_IDENTIFIER;
    EncryptedKey: CRYPT_DATA_BLOB;
  end;
  {$EXTERNALSYM _CMSG_KEY_TRANS_RECIPIENT_INFO}
  CMSG_KEY_TRANS_RECIPIENT_INFO = _CMSG_KEY_TRANS_RECIPIENT_INFO;
  {$EXTERNALSYM CMSG_KEY_TRANS_RECIPIENT_INFO}
  TCmsgKeyTransRecipientInfo = CMSG_KEY_TRANS_RECIPIENT_INFO;
  PCmsgKeyTransRecipientInfo = PCMSG_KEY_TRANS_RECIPIENT_INFO;

  PCMSG_RECIPIENT_ENCRYPTED_KEY_INFO = ^CMSG_RECIPIENT_ENCRYPTED_KEY_INFO;
  {$EXTERNALSYM PCMSG_RECIPIENT_ENCRYPTED_KEY_INFO}
  _CMSG_RECIPIENT_ENCRYPTED_KEY_INFO = record
    // Currently, only ISSUER_SERIAL_NUMBER or KEYID choices
    RecipientId: CERT_ID;
    EncryptedKey: CRYPT_DATA_BLOB;
    // The following optional fields are only applicable to KEYID choice
    Date: FILETIME;
    pOtherAttr: PCRYPT_ATTRIBUTE_TYPE_VALUE;
  end;
  {$EXTERNALSYM _CMSG_RECIPIENT_ENCRYPTED_KEY_INFO}
  CMSG_RECIPIENT_ENCRYPTED_KEY_INFO = _CMSG_RECIPIENT_ENCRYPTED_KEY_INFO;
  {$EXTERNALSYM CMSG_RECIPIENT_ENCRYPTED_KEY_INFO}
  TCmsgRecipientEncryptedKeyInfo = CMSG_RECIPIENT_ENCRYPTED_KEY_INFO;
  PCmsgRecipientEncryptedKeyInfo = PCMSG_RECIPIENT_ENCRYPTED_KEY_INFO;

  PCMSG_KEY_AGREE_RECIPIENT_INFO = ^CMSG_KEY_AGREE_RECIPIENT_INFO;
  {$EXTERNALSYM PCMSG_KEY_AGREE_RECIPIENT_INFO}
  _CMSG_KEY_AGREE_RECIPIENT_INFO = record
    dwVersion: DWORD;
    dwOriginatorChoice: DWORD;
    Union: record
    case Integer of
      // CMSG_KEY_AGREE_ORIGINATOR_CERT
      0: (OriginatorCertId: CERT_ID);
      // CMSG_KEY_AGREE_ORIGINATOR_PUBLIC_KEY
      1: (OriginatorPublicKeyInfo: CERT_PUBLIC_KEY_INFO);
    end;
    UserKeyingMaterial: CRYPT_DATA_BLOB;
    KeyEncryptionAlgorithm: CRYPT_ALGORITHM_IDENTIFIER;
    cRecipientEncryptedKeys: DWORD;
    rgpRecipientEncryptedKeys: PCMSG_RECIPIENT_ENCRYPTED_KEY_INFO;
  end;
  {$EXTERNALSYM _CMSG_KEY_AGREE_RECIPIENT_INFO}
  CMSG_KEY_AGREE_RECIPIENT_INFO = _CMSG_KEY_AGREE_RECIPIENT_INFO;
  {$EXTERNALSYM CMSG_KEY_AGREE_RECIPIENT_INFO}
  TCmsgKeyAgreeRecipientInfo = CMSG_KEY_AGREE_RECIPIENT_INFO;
  PCmsgKeyAgreeRecipientInfo = PCMSG_KEY_AGREE_RECIPIENT_INFO;

const
  CMSG_KEY_AGREE_ORIGINATOR_CERT       = 1;
  {$EXTERNALSYM CMSG_KEY_AGREE_ORIGINATOR_CERT}
  CMSG_KEY_AGREE_ORIGINATOR_PUBLIC_KEY = 2;
  {$EXTERNALSYM CMSG_KEY_AGREE_ORIGINATOR_PUBLIC_KEY}

type
  PCMSG_MAIL_LIST_RECIPIENT_INFO = ^CMSG_MAIL_LIST_RECIPIENT_INFO;
  {$EXTERNALSYM PCMSG_MAIL_LIST_RECIPIENT_INFO}
  _CMSG_MAIL_LIST_RECIPIENT_INFO = record
    dwVersion: DWORD;
    KeyId: CRYPT_DATA_BLOB;
    KeyEncryptionAlgorithm: CRYPT_ALGORITHM_IDENTIFIER;
    EncryptedKey: CRYPT_DATA_BLOB;
    // The following fields are optional
    Date: FILETIME;
    pOtherAttr: PCRYPT_ATTRIBUTE_TYPE_VALUE;
  end;
  {$EXTERNALSYM _CMSG_MAIL_LIST_RECIPIENT_INFO}
  CMSG_MAIL_LIST_RECIPIENT_INFO = _CMSG_MAIL_LIST_RECIPIENT_INFO;
  {$EXTERNALSYM CMSG_MAIL_LIST_RECIPIENT_INFO}
  TCmsgMailListRecipientInfo = CMSG_MAIL_LIST_RECIPIENT_INFO;
  PCmsgMailListRecipientInfo = PCMSG_MAIL_LIST_RECIPIENT_INFO;

  PCMSG_CMS_RECIPIENT_INFO = ^CMSG_CMS_RECIPIENT_INFO;
  {$EXTERNALSYM PCMSG_CMS_RECIPIENT_INFO}
  _CMSG_CMS_RECIPIENT_INFO = record
    dwRecipientChoice: DWORD;
    case Integer of
      // CMSG_KEY_TRANS_RECIPIENT
      0: (pKeyTrans: PCMSG_KEY_TRANS_RECIPIENT_INFO);
      // CMSG_KEY_AGREE_RECIPIENT
      1: (pKeyAgree: PCMSG_KEY_AGREE_RECIPIENT_INFO);
      // CMSG_MAIL_LIST_RECIPIENT
      2: (pMailList: PCMSG_MAIL_LIST_RECIPIENT_INFO);
  end;
  {$EXTERNALSYM _CMSG_CMS_RECIPIENT_INFO}
  CMSG_CMS_RECIPIENT_INFO = _CMSG_CMS_RECIPIENT_INFO;
  {$EXTERNALSYM CMSG_CMS_RECIPIENT_INFO}
  TCmsgCmsRecipientInfo = CMSG_CMS_RECIPIENT_INFO;
  PCmsgCmsRecipientInfo = PCMSG_CMS_RECIPIENT_INFO;

// dwVersion numbers for the KeyTrans, KeyAgree and MailList recipients

const
  CMSG_ENVELOPED_RECIPIENT_V0     = 0;
  {$EXTERNALSYM CMSG_ENVELOPED_RECIPIENT_V0}
  CMSG_ENVELOPED_RECIPIENT_V2     = 2;
  {$EXTERNALSYM CMSG_ENVELOPED_RECIPIENT_V2}
  CMSG_ENVELOPED_RECIPIENT_V3     = 3;
  {$EXTERNALSYM CMSG_ENVELOPED_RECIPIENT_V3}
  CMSG_ENVELOPED_RECIPIENT_V4     = 4;
  {$EXTERNALSYM CMSG_ENVELOPED_RECIPIENT_V4}
  CMSG_KEY_TRANS_PKCS_1_5_VERSION = CMSG_ENVELOPED_RECIPIENT_V0;
  {$EXTERNALSYM CMSG_KEY_TRANS_PKCS_1_5_VERSION}
  CMSG_KEY_TRANS_CMS_VERSION      = CMSG_ENVELOPED_RECIPIENT_V2;
  {$EXTERNALSYM CMSG_KEY_TRANS_CMS_VERSION}
  CMSG_KEY_AGREE_VERSION          = CMSG_ENVELOPED_RECIPIENT_V3;
  {$EXTERNALSYM CMSG_KEY_AGREE_VERSION}
  CMSG_MAIL_LIST_VERSION          = CMSG_ENVELOPED_RECIPIENT_V4;
  {$EXTERNALSYM CMSG_MAIL_LIST_VERSION}

//+-------------------------------------------------------------------------
//  CMSG_UNPROTECTED_ATTR_PARAM
//
//  The unprotected attributes in the envelped message.
//
//  pvData points to a CMSG_ATTR struct.
//--------------------------------------------------------------------------


//+-------------------------------------------------------------------------
//  Perform a special "control" function after the final CryptMsgUpdate of a
//  encoded/decoded cryptographic message.
//
//  The dwCtrlType parameter specifies the type of operation to be performed.
//
//  The pvCtrlPara definition depends on the dwCtrlType value.
//
//  See below for a list of the control operations and their pvCtrlPara
//  type definition.
//--------------------------------------------------------------------------

function CryptMsgControl(hCryptMsg: HCRYPTMSG; dwFlags, dwCtrlType: DWORD;
  pvCtrlPara: Pointer): BOOL; stdcall;
{$EXTERNALSYM CryptMsgControl}

//+-------------------------------------------------------------------------
//  Message control types
//--------------------------------------------------------------------------

const
  CMSG_CTRL_VERIFY_SIGNATURE       = 1;
  {$EXTERNALSYM CMSG_CTRL_VERIFY_SIGNATURE}
  CMSG_CTRL_DECRYPT                = 2;
  {$EXTERNALSYM CMSG_CTRL_DECRYPT}
  CMSG_CTRL_VERIFY_HASH            = 5;
  {$EXTERNALSYM CMSG_CTRL_VERIFY_HASH}
  CMSG_CTRL_ADD_SIGNER             = 6;
  {$EXTERNALSYM CMSG_CTRL_ADD_SIGNER}
  CMSG_CTRL_DEL_SIGNER             = 7;
  {$EXTERNALSYM CMSG_CTRL_DEL_SIGNER}
  CMSG_CTRL_ADD_SIGNER_UNAUTH_ATTR = 8;
  {$EXTERNALSYM CMSG_CTRL_ADD_SIGNER_UNAUTH_ATTR}
  CMSG_CTRL_DEL_SIGNER_UNAUTH_ATTR = 9;
  {$EXTERNALSYM CMSG_CTRL_DEL_SIGNER_UNAUTH_ATTR}
  CMSG_CTRL_ADD_CERT               = 10;
  {$EXTERNALSYM CMSG_CTRL_ADD_CERT}
  CMSG_CTRL_DEL_CERT               = 11;
  {$EXTERNALSYM CMSG_CTRL_DEL_CERT}
  CMSG_CTRL_ADD_CRL                = 12;
  {$EXTERNALSYM CMSG_CTRL_ADD_CRL}
  CMSG_CTRL_DEL_CRL                = 13;
  {$EXTERNALSYM CMSG_CTRL_DEL_CRL}
  CMSG_CTRL_ADD_ATTR_CERT          = 14;
  {$EXTERNALSYM CMSG_CTRL_ADD_ATTR_CERT}
  CMSG_CTRL_DEL_ATTR_CERT          = 15;
  {$EXTERNALSYM CMSG_CTRL_DEL_ATTR_CERT}
  CMSG_CTRL_KEY_TRANS_DECRYPT      = 16;
  {$EXTERNALSYM CMSG_CTRL_KEY_TRANS_DECRYPT}
  CMSG_CTRL_KEY_AGREE_DECRYPT      = 17;
  {$EXTERNALSYM CMSG_CTRL_KEY_AGREE_DECRYPT}
  CMSG_CTRL_MAIL_LIST_DECRYPT      = 18;
  {$EXTERNALSYM CMSG_CTRL_MAIL_LIST_DECRYPT}
  CMSG_CTRL_VERIFY_SIGNATURE_EX    = 19;
  {$EXTERNALSYM CMSG_CTRL_VERIFY_SIGNATURE_EX}
  CMSG_CTRL_ADD_CMS_SIGNER_INFO    = 20;
  {$EXTERNALSYM CMSG_CTRL_ADD_CMS_SIGNER_INFO}

//+-------------------------------------------------------------------------
//  CMSG_CTRL_VERIFY_SIGNATURE
//
//  Verify the signature of a SIGNED or SIGNED_AND_ENVELOPED
//  message after it has been decoded.
//
//  For a SIGNED_AND_ENVELOPED message, called after
//  CryptMsgControl(CMSG_CTRL_DECRYPT), if CryptMsgOpenToDecode was called
//  with a NULL pRecipientInfo.
//
//  pvCtrlPara points to a CERT_INFO struct.
//
//  The CERT_INFO contains the Issuer and SerialNumber identifying
//  the Signer of the message. The CERT_INFO also contains the
//  PublicKeyInfo
//  used to verify the signature. The cryptographic provider specified
//  in CryptMsgOpenToDecode is used.
//
//  Note, if the message contains CMS signers identified by KEYID, then,
//  the CERT_INFO's Issuer and SerialNumber is ignored and only the public
//  key is used to find a signer whose signature verifies.
//
//  The following CMSG_CTRL_VERIFY_SIGNATURE_EX should be used instead.
//--------------------------------------------------------------------------

//+-------------------------------------------------------------------------
//  CMSG_CTRL_VERIFY_SIGNATURE_EX
//
//  Verify the signature of a SIGNED message after it has been decoded.
//
//  pvCtrlPara points to the following CMSG_CTRL_VERIFY_SIGNATURE_EX_PARA.
//
//  If hCryptProv is NULL, uses the cryptographic provider specified in
//  CryptMsgOpenToDecode. If CryptMsgOpenToDecode's hCryptProv is also NULL,
//  gets default provider according to the signer's public key OID.
//
//  dwSignerIndex is the index of the signer to use to verify the signature.
//
//  The signer can be a pointer to a CERT_PUBLIC_KEY_INFO, certificate
//  context or a chain context.
//--------------------------------------------------------------------------

type
  PCMSG_CTRL_VERIFY_SIGNATURE_EX_PARA = ^CMSG_CTRL_VERIFY_SIGNATURE_EX_PARA;
  {$EXTERNALSYM PCMSG_CTRL_VERIFY_SIGNATURE_EX_PARA}
  _CMSG_CTRL_VERIFY_SIGNATURE_EX_PARA = record
    cbSize: DWORD;
    hCryptProv: HCRYPTPROV;
    dwSignerIndex: DWORD;
    dwSignerType: DWORD;
    pvSigner: Pointer;
  end;
  {$EXTERNALSYM _CMSG_CTRL_VERIFY_SIGNATURE_EX_PARA}
  CMSG_CTRL_VERIFY_SIGNATURE_EX_PARA = _CMSG_CTRL_VERIFY_SIGNATURE_EX_PARA;
  {$EXTERNALSYM CMSG_CTRL_VERIFY_SIGNATURE_EX_PARA}
  TCmsgCtrlVerifySignatureExPara = CMSG_CTRL_VERIFY_SIGNATURE_EX_PARA;
  PCmsgCtrlVerifySignatureExPara = PCMSG_CTRL_VERIFY_SIGNATURE_EX_PARA;

// Signer Types

const
  CMSG_VERIFY_SIGNER_PUBKEY = 1;
  {$EXTERNALSYM CMSG_VERIFY_SIGNER_PUBKEY}
  // pvSigner :: PCERT_PUBLIC_KEY_INFO
  CMSG_VERIFY_SIGNER_CERT = 2;
  {$EXTERNALSYM CMSG_VERIFY_SIGNER_CERT}
  // pvSigner :: PCCERT_CONTEXT
  CMSG_VERIFY_SIGNER_CHAIN = 3;
  {$EXTERNALSYM CMSG_VERIFY_SIGNER_CHAIN}
  // pvSigner :: PCCERT_CHAIN_CONTEXT

//+-------------------------------------------------------------------------
//  CMSG_CTRL_DECRYPT
//
//  Decrypt an ENVELOPED or SIGNED_AND_ENVELOPED message after it has been
//  decoded.
//
//  This decrypt is only applicable to key transport recipients.
//
//  hCryptProv and dwKeySpec specify the private key to use. For dwKeySpec ==
//  0, defaults to AT_KEYEXCHANGE.
//
//  If CMSG_CRYPT_RELEASE_CONTEXT_FLAG is set in the dwFlags passed
//  to CryptMsgControl, then, the hCryptProv is released on the final
//  CryptMsgClose. Not released if CryptMsgControl fails.
//
//  dwRecipientIndex is the index of the recipient in the message associated
//  with the hCryptProv's private key.
//
//  The dwRecipientIndex is the index of a key transport recipient.
//
//  Note, the message can only be decrypted once.
//--------------------------------------------------------------------------

type
  PCMSG_CTRL_DECRYPT_PARA = ^CMSG_CTRL_DECRYPT_PARA;
  {$EXTERNALSYM PCMSG_CTRL_DECRYPT_PARA}
  _CMSG_CTRL_DECRYPT_PARA = record
    cbSize: DWORD;
    hCryptProv: HCRYPTPROV;
    dwKeySpec: DWORD;
    dwRecipientIndex: DWORD;
  end;
  {$EXTERNALSYM _CMSG_CTRL_DECRYPT_PARA}
  CMSG_CTRL_DECRYPT_PARA = _CMSG_CTRL_DECRYPT_PARA;
  {$EXTERNALSYM CMSG_CTRL_DECRYPT_PARA}
  TCmsgCtrlDecryptPara = CMSG_CTRL_DECRYPT_PARA;
  PCmsgCtrlDecryptPara = PCMSG_CTRL_DECRYPT_PARA;

//+-------------------------------------------------------------------------
//  CMSG_CTRL_KEY_TRANS_DECRYPT
//
//  Decrypt an ENVELOPED message after it has been decoded for a key
//  transport recipient.
//
//  hCryptProv and dwKeySpec specify the private key to use. For dwKeySpec ==
//  0, defaults to AT_KEYEXCHANGE.
//
//  If CMSG_CRYPT_RELEASE_CONTEXT_FLAG is set in the dwFlags passed
//  to CryptMsgControl, then, the hCryptProv is released on the final
//  CryptMsgClose. Not released if CryptMsgControl fails.
//
//  pKeyTrans points to the CMSG_KEY_TRANS_RECIPIENT_INFO obtained via
//  CryptMsgGetParam(CMSG_CMS_RECIPIENT_INFO_PARAM)
//
//  dwRecipientIndex is the index of the recipient in the message associated
//  with the hCryptProv's private key.
//
//  Note, the message can only be decrypted once.
//--------------------------------------------------------------------------

  PCMSG_CTRL_KEY_TRANS_DECRYPT_PARA = ^CMSG_CTRL_KEY_TRANS_DECRYPT_PARA;
  {$EXTERNALSYM PCMSG_CTRL_KEY_TRANS_DECRYPT_PARA}
  _CMSG_CTRL_KEY_TRANS_DECRYPT_PARA = record
    cbSize: DWORD;
    hCryptProv: HCRYPTPROV;
    dwKeySpec: DWORD;
    pKeyTrans: PCMSG_KEY_TRANS_RECIPIENT_INFO;
    dwRecipientIndex: DWORD;
  end;
  {$EXTERNALSYM _CMSG_CTRL_KEY_TRANS_DECRYPT_PARA}
  CMSG_CTRL_KEY_TRANS_DECRYPT_PARA = _CMSG_CTRL_KEY_TRANS_DECRYPT_PARA;
  {$EXTERNALSYM CMSG_CTRL_KEY_TRANS_DECRYPT_PARA}
  TCmsgCtrlKeyTransDecryptPara = CMSG_CTRL_KEY_TRANS_DECRYPT_PARA;
  PCmsgCtrlKeyTransDecryptPara = PCMSG_CTRL_KEY_TRANS_DECRYPT_PARA;

//+-------------------------------------------------------------------------
//  CMSG_CTRL_KEY_AGREE_DECRYPT
//
//  Decrypt an ENVELOPED message after it has been decoded for a key
//  agreement recipient.
//
//  hCryptProv and dwKeySpec specify the private key to use. For dwKeySpec ==
//  0, defaults to AT_KEYEXCHANGE.
//
//  If CMSG_CRYPT_RELEASE_CONTEXT_FLAG is set in the dwFlags passed
//  to CryptMsgControl, then, the hCryptProv is released on the final
//  CryptMsgClose. Not released if CryptMsgControl fails.
//
//  pKeyAgree points to the CMSG_KEY_AGREE_RECIPIENT_INFO obtained via
//  CryptMsgGetParam(CMSG_CMS_RECIPIENT_INFO_PARAM) for dwRecipientIndex.
//
//  dwRecipientIndex, dwRecipientEncryptedKeyIndex are the indices of the
//  recipient's encrypted key in the message associated with the hCryptProv's
//  private key.
//
//  OriginatorPublicKey is the originator's public key obtained from either
//  the originator's certificate or the CMSG_KEY_AGREE_RECIPIENT_INFO obtained
//  via the CMSG_CMS_RECIPIENT_INFO_PARAM.
//
//  Note, the message can only be decrypted once.
//--------------------------------------------------------------------------

  PCMSG_CTRL_KEY_AGREE_DECRYPT_PARA = ^CMSG_CTRL_KEY_AGREE_DECRYPT_PARA;
  {$EXTERNALSYM PCMSG_CTRL_KEY_AGREE_DECRYPT_PARA}
  _CMSG_CTRL_KEY_AGREE_DECRYPT_PARA = record
    cbSize: DWORD;
    hCryptProv: HCRYPTPROV;
    dwKeySpec: DWORD;
    pKeyAgree: PCMSG_KEY_AGREE_RECIPIENT_INFO;
    dwRecipientIndex: DWORD;
    dwRecipientEncryptedKeyIndex: DWORD;
    OriginatorPublicKey: CRYPT_BIT_BLOB;
  end;
  {$EXTERNALSYM _CMSG_CTRL_KEY_AGREE_DECRYPT_PARA}
  CMSG_CTRL_KEY_AGREE_DECRYPT_PARA = _CMSG_CTRL_KEY_AGREE_DECRYPT_PARA;
  {$EXTERNALSYM CMSG_CTRL_KEY_AGREE_DECRYPT_PARA}
  TCmsgCtrlKeyAgreeDecryptPara = CMSG_CTRL_KEY_AGREE_DECRYPT_PARA;
  PCmsgCtrlKeyAgreeDecryptPara = PCMSG_CTRL_KEY_AGREE_DECRYPT_PARA;

//+-------------------------------------------------------------------------
//  CMSG_CTRL_MAIL_LIST_DECRYPT
//
//  Decrypt an ENVELOPED message after it has been decoded for a mail
//  list recipient.
//
//  pMailList points to the CMSG_MAIL_LIST_RECIPIENT_INFO obtained via
//  CryptMsgGetParam(CMSG_CMS_RECIPIENT_INFO_PARAM) for dwRecipientIndex.
//
//  There is 1 choice for the KeyEncryptionKey: an already created CSP key
//  handle. For the key handle choice, hCryptProv must be nonzero. This key
//  handle isn't destroyed.
//
//  If CMSG_CRYPT_RELEASE_CONTEXT_FLAG is set in the dwFlags passed
//  to CryptMsgControl, then, the hCryptProv is released on the final
//  CryptMsgClose. Not released if CryptMsgControl fails.
//
//  For RC2 wrap, the effective key length is obtained from the
//  KeyEncryptionAlgorithm parameters and set on the hKeyEncryptionKey before
//  decrypting.
//
//  Note, the message can only be decrypted once.
//--------------------------------------------------------------------------

  PCMSG_CTRL_MAIL_LIST_DECRYPT_PARA = ^CMSG_CTRL_MAIL_LIST_DECRYPT_PARA;
  {$EXTERNALSYM PCMSG_CTRL_MAIL_LIST_DECRYPT_PARA}
  _CMSG_CTRL_MAIL_LIST_DECRYPT_PARA = record
    cbSize: DWORD;
    hCryptProv: HCRYPTPROV;
    pMailList: PCMSG_MAIL_LIST_RECIPIENT_INFO;
    dwRecipientIndex: DWORD;
    dwKeyChoice: DWORD;
    case Integer of
      // CMSG_MAIL_LIST_HANDLE_KEY_CHOICE
      0: (hKeyEncryptionKey: HCRYPTKEY);
      // Reserve space for a potential pointer choice
      1: (pvKeyEncryptionKey: Pointer);
  end;
  {$EXTERNALSYM _CMSG_CTRL_MAIL_LIST_DECRYPT_PARA}
  CMSG_CTRL_MAIL_LIST_DECRYPT_PARA = _CMSG_CTRL_MAIL_LIST_DECRYPT_PARA;
  {$EXTERNALSYM CMSG_CTRL_MAIL_LIST_DECRYPT_PARA}
  TCmsgCtrlMailListDecryptPara = CMSG_CTRL_MAIL_LIST_DECRYPT_PARA;
  PCmsgCtrlMailListDecryptPara = PCMSG_CTRL_MAIL_LIST_DECRYPT_PARA;

//+-------------------------------------------------------------------------
//  CMSG_CTRL_VERIFY_HASH
//
//  Verify the hash of a HASHED message after it has been decoded.
//
//  Only the hCryptMsg parameter is used, to specify the message whose
//  hash is being verified.
//--------------------------------------------------------------------------

//+-------------------------------------------------------------------------
//  CMSG_CTRL_ADD_SIGNER
//
//  Add a signer to a signed-data message.
//
//  pvCtrlPara points to a CMSG_SIGNER_ENCODE_INFO.
//--------------------------------------------------------------------------

//+-------------------------------------------------------------------------
//  CMSG_CTRL_ADD_CMS_SIGNER_INFO
//
//  Add a signer to a signed-data message.
//
//  Differs from the above, CMSG_CTRL_ADD_SIGNER, wherein, the signer info
//  already contains the signature.
//
//  pvCtrlPara points to a CMSG_CMS_SIGNER_INFO.
//--------------------------------------------------------------------------

//+-------------------------------------------------------------------------
//  CMSG_CTRL_DEL_SIGNER
//
//  Remove a signer from a signed-data or signed-and-enveloped-data message.
//
//  pvCtrlPara points to a DWORD containing the 0-based index of the
//  signer to be removed.
//--------------------------------------------------------------------------

//+-------------------------------------------------------------------------
//  CMSG_CTRL_ADD_SIGNER_UNAUTH_ATTR
//
//  Add an unauthenticated attribute to the SignerInfo of a signed-data or
//  signed-and-enveloped-data message.
//
//  The unauthenticated attribute is input in the form of an encoded blob.
//--------------------------------------------------------------------------

  PCMSG_CTRL_ADD_SIGNER_UNAUTH_ATTR_PARA = ^CMSG_CTRL_ADD_SIGNER_UNAUTH_ATTR_PARA;
  {$EXTERNALSYM PCMSG_CTRL_ADD_SIGNER_UNAUTH_ATTR_PARA}
  _CMSG_CTRL_ADD_SIGNER_UNAUTH_ATTR_PARA = record
    cbSize: DWORD;
    dwSignerIndex: DWORD;
    blob: CRYPT_DATA_BLOB;
  end;
  {$EXTERNALSYM _CMSG_CTRL_ADD_SIGNER_UNAUTH_ATTR_PARA}
  CMSG_CTRL_ADD_SIGNER_UNAUTH_ATTR_PARA = _CMSG_CTRL_ADD_SIGNER_UNAUTH_ATTR_PARA;
  {$EXTERNALSYM CMSG_CTRL_ADD_SIGNER_UNAUTH_ATTR_PARA}
  TCmsgCtrlAddSignerUnauthAttrPara = CMSG_CTRL_ADD_SIGNER_UNAUTH_ATTR_PARA;
  PCmsgCtrlAddSignerUnauthAttrPara = PCMSG_CTRL_ADD_SIGNER_UNAUTH_ATTR_PARA;

//+-------------------------------------------------------------------------
//  CMSG_CTRL_DEL_SIGNER_UNAUTH_ATTR
//
//  Delete an unauthenticated attribute from the SignerInfo of a signed-data
//  or signed-and-enveloped-data message.
//
//  The unauthenticated attribute to be removed is specified by
//  a 0-based index.
//--------------------------------------------------------------------------

  PCMSG_CTRL_DEL_SIGNER_UNAUTH_ATTR_PARA = ^CMSG_CTRL_DEL_SIGNER_UNAUTH_ATTR_PARA;
  {$EXTERNALSYM PCMSG_CTRL_DEL_SIGNER_UNAUTH_ATTR_PARA}
  _CMSG_CTRL_DEL_SIGNER_UNAUTH_ATTR_PARA = record
    cbSize: DWORD;
    dwSignerIndex: DWORD;
    dwUnauthAttrIndex: DWORD;
  end;
  {$EXTERNALSYM _CMSG_CTRL_DEL_SIGNER_UNAUTH_ATTR_PARA}
  CMSG_CTRL_DEL_SIGNER_UNAUTH_ATTR_PARA = _CMSG_CTRL_DEL_SIGNER_UNAUTH_ATTR_PARA;
  {$EXTERNALSYM CMSG_CTRL_DEL_SIGNER_UNAUTH_ATTR_PARA}
  TCmsgCtrlDelSignerUnauthAttrPara = CMSG_CTRL_DEL_SIGNER_UNAUTH_ATTR_PARA;
  PCmsgCtrlDelSignerUnauthAttrPara = PCMSG_CTRL_DEL_SIGNER_UNAUTH_ATTR_PARA;

//+-------------------------------------------------------------------------
//  CMSG_CTRL_ADD_CERT
//
//  Add a certificate to a signed-data or signed-and-enveloped-data message.
//
//  pvCtrlPara points to a CRYPT_DATA_BLOB containing the certificate's
//  encoded bytes.
//--------------------------------------------------------------------------

//+-------------------------------------------------------------------------
//  CMSG_CTRL_DEL_CERT
//
//  Delete a certificate from a signed-data or signed-and-enveloped-data
//  message.
//
//  pvCtrlPara points to a DWORD containing the 0-based index of the
//  certificate to be removed.
//--------------------------------------------------------------------------

//+-------------------------------------------------------------------------
//  CMSG_CTRL_ADD_CRL
//
//  Add a CRL to a signed-data or signed-and-enveloped-data message.
//
//  pvCtrlPara points to a CRYPT_DATA_BLOB containing the CRL's
//  encoded bytes.
//--------------------------------------------------------------------------

//+-------------------------------------------------------------------------
//  CMSG_CTRL_DEL_CRL
//
//  Delete a CRL from a signed-data or signed-and-enveloped-data message.
//
//  pvCtrlPara points to a DWORD containing the 0-based index of the CRL
//  to be removed.
//--------------------------------------------------------------------------

//+-------------------------------------------------------------------------
//  CMSG_CTRL_ADD_ATTR_CERT
//
//  Add an attribute certificate to a signed-data message.
//
//  pvCtrlPara points to a CRYPT_DATA_BLOB containing the attribute
//  certificate's encoded bytes.
//--------------------------------------------------------------------------

//+-------------------------------------------------------------------------
//  CMSG_CTRL_DEL_ATTR_CERT
//
//  Delete an attribute certificate from a signed-data message.
//
//  pvCtrlPara points to a DWORD containing the 0-based index of the
//  attribute certificate to be removed.
//--------------------------------------------------------------------------


//+-------------------------------------------------------------------------
//  Verify a countersignature, at the SignerInfo level.
//  ie. verify that pbSignerInfoCountersignature contains the encrypted
//  hash of the encryptedDigest field of pbSignerInfo.
//
//  hCryptProv is used to hash the encryptedDigest field of pbSignerInfo.
//  The only fields referenced from pciCountersigner are SerialNumber, Issuer,
//  and SubjectPublicKeyInfo.
//--------------------------------------------------------------------------

function CryptMsgVerifyCountersignatureEncoded(hCryptProv: HCRYPTPROV;
  dwEncodingType: DWORD; pbSignerInfo: PBYTE; cbSignerInfo: DWORD;
  pbSignerInfoCountersignature: PBYTE; cbSignerInfoCountersignature: DWORD;
  pciCountersigner: PCERT_INFO): BOOL; stdcall;
{$EXTERNALSYM CryptMsgVerifyCountersignatureEncoded}

//+-------------------------------------------------------------------------
//  Verify a countersignature, at the SignerInfo level.
//  ie. verify that pbSignerInfoCountersignature contains the encrypted
//  hash of the encryptedDigest field of pbSignerInfo.
//
//  hCryptProv is used to hash the encryptedDigest field of pbSignerInfo.
//
//  The signer can be a CERT_PUBLIC_KEY_INFO, certificate context or a
//  chain context.
//--------------------------------------------------------------------------

function CryptMsgVerifyCountersignatureEncodedEx(hCryptProv: HCRYPTPROV;
  dwEncodingType: DWORD; pbSignerInfo: PBYTE; cbSignerInfo: DWORD;
  pbSignerInfoCountersignature: PBYTE; cbSignerInfoCountersignature: DWORD;
  dwSignerType: DWORD; pvSigner: Pointer; dwFlags: DWORD; pvReserved: Pointer): BOOL; stdcall;
{$EXTERNALSYM CryptMsgVerifyCountersignatureEncodedEx}

// See CMSG_CTRL_VERIFY_SIGNATURE_EX_PARA for dwSignerType definitions

//+-------------------------------------------------------------------------
//  Countersign an already-existing signature in a message
//
//  dwIndex is a zero-based index of the SignerInfo to be countersigned.
//--------------------------------------------------------------------------

function CryptMsgCountersign(hCryptMsg: HCRYPTMSG; dwIndex, cCountersigners: DWORD;
  rgCountersigners: PCMSG_SIGNER_ENCODE_INFO): BOOL; stdcall;
{$EXTERNALSYM CryptMsgCountersign}

//+-------------------------------------------------------------------------
//  Countersign an already-existing signature (encoded SignerInfo).
//  Output an encoded SignerInfo blob, suitable for use as a countersignature
//  attribute in the unauthenticated attributes of a signed-data or
//  signed-and-enveloped-data message.
//--------------------------------------------------------------------------

function CryptMsgCountersignEncoded(dwEncodingType: DWORD; pbSignerInfo: PBYTE;
  cbSignerInfo: DWORD; cCountersigners: DWORD; rgCountersigners: PCMSG_SIGNER_ENCODE_INFO;
  pbCountersignature: PBYTE; var pcbCountersignature: DWORD): BOOL; stdcall;
{$EXTERNALSYM CryptMsgCountersignEncoded}

//+-------------------------------------------------------------------------
//  CryptMsg OID installable functions
//--------------------------------------------------------------------------

type
  PFN_CMSG_ALLOC = function (cb: size_t): Pointer; stdcall;
  {$EXTERNALSYM PFN_CMSG_ALLOC}
  PFnCMsgAlloc = PFN_CMSG_ALLOC;

  PFN_CMSG_FREE = procedure (pv: Pointer); stdcall;
  {$EXTERNALSYM PFN_CMSG_FREE}
  PFnCMsgFree = PFN_CMSG_FREE;

// Note, the following 3 installable functions are obsolete and have been
// replaced with GenContentEncryptKey, ExportKeyTrans, ExportKeyAgree,
// ExportMailList, ImportKeyTrans, ImportKeyAgree and ImportMailList
// installable functions.

// If *phCryptProv is NULL upon entry, then, if supported, the installable
// function should acquire a default provider and return. Note, its up
// to the installable function to release at process detach.
//
// If paiEncrypt->Parameters.cbData is 0, then, the callback may optionally
// return default encoded parameters in *ppbEncryptParameters and
// *pcbEncryptParameters. pfnAlloc must be called for the allocation.

const
  CMSG_OID_GEN_ENCRYPT_KEY_FUNC = 'CryptMsgDllGenEncryptKey';
  {$EXTERNALSYM CMSG_OID_GEN_ENCRYPT_KEY_FUNC}

type
  PFN_CMSG_GEN_ENCRYPT_KEY = function (phCryptProv: PHCRYPTPROV;
    paiEncrypt: PCRYPT_ALGORITHM_IDENTIFIER; pvEncryptAuxInfo: PVOID;
    pPublicKeyInfo: PCERT_PUBLIC_KEY_INFO; pfnAlloc: PFN_CMSG_ALLOC;
    var phEncryptKey: HCRYPTKEY; var ppbEncryptParameters: PBYTE;
    pcbEncryptParameters: PDWORD): BOOL; stdcall;
  {$EXTERNALSYM PFN_CMSG_GEN_ENCRYPT_KEY}
  PfnCmsgGenEncryptKey = PFN_CMSG_GEN_ENCRYPT_KEY;

const
  CMSG_OID_EXPORT_ENCRYPT_KEY_FUNC = 'CryptMsgDllExportEncryptKey';
  {$EXTERNALSYM CMSG_OID_EXPORT_ENCRYPT_KEY_FUNC}

type
  PFN_CMSG_EXPORT_ENCRYPT_KEY = function (hCryptProv: HCRYPTPROV;
    hEncryptKey: HCRYPTKEY; pPublicKeyInfo: PCERT_PUBLIC_KEY_INFO;
    pbData: PBYTE; var pcbData: DWORD): BOOL; stdcall;
  {$EXTERNALSYM PFN_CMSG_EXPORT_ENCRYPT_KEY}
  PfnCmsgExportEncryptKey = PFN_CMSG_EXPORT_ENCRYPT_KEY;

const
  CMSG_OID_IMPORT_ENCRYPT_KEY_FUNC = 'CryptMsgDllImportEncryptKey';
  {$EXTERNALSYM CMSG_OID_IMPORT_ENCRYPT_KEY_FUNC}

type
  PFN_CMSG_IMPORT_ENCRYPT_KEY = function (hCryptProv: HCRYPTPROV;
    dwKeySpec: DWORD; paiEncrypt: PCRYPT_ALGORITHM_IDENTIFIER;
    paiPubKey: PCRYPT_ALGORITHM_IDENTIFIER; pbEncodedKey: PBYTE;
    cbEncodedKey: DWORD; var phEncryptKey: HCRYPTKEY): BOOL; stdcall;
  {$EXTERNALSYM PFN_CMSG_IMPORT_ENCRYPT_KEY}
  PfnCmsgImportEncryptKey = PFN_CMSG_IMPORT_ENCRYPT_KEY;

// To get the default installable function for GenContentEncryptKey,
// ExportKeyTrans, ExportKeyAgree, ExportMailList, ImportKeyTrans,
// ImportKeyAgree or ImportMailList call CryptGetOIDFunctionAddress()
// with the pszOID argument set to the following constant. dwEncodingType
// should be set to CRYPT_ASN_ENCODING or X509_ASN_ENCODING.

const
  CMSG_DEFAULT_INSTALLABLE_FUNC_OID = LPCSTR(1);
  {$EXTERNALSYM CMSG_DEFAULT_INSTALLABLE_FUNC_OID}

//+-------------------------------------------------------------------------
//  Content Encrypt Info
//
//  The following data structure contains the information shared between
//  the GenContentEncryptKey and the ExportKeyTrans, ExportKeyAgree and
//  ExportMailList installable functions.
//--------------------------------------------------------------------------

type
  PCMSG_CONTENT_ENCRYPT_INFO = ^CMSG_CONTENT_ENCRYPT_INFO;
  {$EXTERNALSYM PCMSG_CONTENT_ENCRYPT_INFO}
  _CMSG_CONTENT_ENCRYPT_INFO = record
    cbSize: DWORD;
    hCryptProv: HCRYPTPROV;
    ContentEncryptionAlgorithm: CRYPT_ALGORITHM_IDENTIFIER;
    pvEncryptionAuxInfo: Pointer;
    cRecipients: DWORD;
    rgCmsRecipients: PCMSG_RECIPIENT_ENCODE_INFO;
    pfnAlloc: PFN_CMSG_ALLOC;
    pfnFree: PFN_CMSG_FREE;
    dwEncryptFlags: DWORD;
    hContentEncryptKey: HCRYPTKEY;
    dwFlags: DWORD;
  end;
  {$EXTERNALSYM _CMSG_CONTENT_ENCRYPT_INFO}
  CMSG_CONTENT_ENCRYPT_INFO = _CMSG_CONTENT_ENCRYPT_INFO;
  {$EXTERNALSYM CMSG_CONTENT_ENCRYPT_INFO}
  TCmsgContentEncryptInfo = CMSG_CONTENT_ENCRYPT_INFO;
  PCmsgContentEncryptInfo = PCMSG_CONTENT_ENCRYPT_INFO;

const
  CMSG_CONTENT_ENCRYPT_PAD_ENCODED_LEN_FLAG = $00000001;
  {$EXTERNALSYM CMSG_CONTENT_ENCRYPT_PAD_ENCODED_LEN_FLAG}

  CMSG_CONTENT_ENCRYPT_FREE_PARA_FLAG       = $00000001;
  {$EXTERNALSYM CMSG_CONTENT_ENCRYPT_FREE_PARA_FLAG}
  CMSG_CONTENT_ENCRYPT_RELEASE_CONTEXT_FLAG = $00008000;
  {$EXTERNALSYM CMSG_CONTENT_ENCRYPT_RELEASE_CONTEXT_FLAG}

//+-------------------------------------------------------------------------
// Upon input, ContentEncryptInfo has been initialized from the
// EnvelopedEncodeInfo.
//
// Note, if rgpRecipients instead of rgCmsRecipients are set in the
// EnvelopedEncodeInfo, then, the rgpRecipients have been converted
// to rgCmsRecipients in the ContentEncryptInfo.
//
// The following fields may be changed in ContentEncryptInfo:
//      hContentEncryptKey
//      hCryptProv
//      ContentEncryptionAlgorithm.Parameters
//      dwFlags
//
// All other fields in the ContentEncryptInfo are READONLY.
//
// If CMSG_CONTENT_ENCRYPT_PAD_ENCODED_LEN_FLAG is set upon entry
// in dwEncryptFlags, then, any potentially variable length encoded
// output should be padded with zeroes to always obtain the
// same maximum encoded length. This is necessary for
// CryptMsgCalculateEncodedLength() or CryptMsgOpenToEncode() with
// definite length streaming.
//
// The hContentEncryptKey must be updated.
//
// If hCryptProv is NULL upon input, then, it must be updated.
// If a HCRYPTPROV is acquired that must be released, then, the
// CMSG_CONTENT_ENCRYPT_RELEASE_CONTEXT_FLAG must be set in dwFlags.
//
// If ContentEncryptionAlgorithm.Parameters is updated, then, the
// CMSG_CONTENT_ENCRYPT_FREE_PARA_FLAG must be set in dwFlags. pfnAlloc and
// pfnFree must be used for doing the allocation.
//
// ContentEncryptionAlgorithm.pszObjId is used to get the OIDFunctionAddress.
//--------------------------------------------------------------------------

const
  CMSG_OID_GEN_CONTENT_ENCRYPT_KEY_FUNC = 'CryptMsgDllGenContentEncryptKey';
  {$EXTERNALSYM CMSG_OID_GEN_CONTENT_ENCRYPT_KEY_FUNC}

type
  PFN_CMSG_GEN_CONTENT_ENCRYPT_KEY = function (pContentEncryptInfo: PCMSG_CONTENT_ENCRYPT_INFO;
    dwFlags: DWORD; pvReserved: PPointer): BOOL; stdcall;
  {$EXTERNALSYM PFN_CMSG_GEN_CONTENT_ENCRYPT_KEY}
  PfnCmsgGenContentEncryptKey = PFN_CMSG_GEN_CONTENT_ENCRYPT_KEY;

//+-------------------------------------------------------------------------
//  Key Transport Encrypt Info
//
//  The following data structure contains the information updated by the
//  ExportKeyTrans installable function.
//--------------------------------------------------------------------------

type
  PCMSG_KEY_TRANS_ENCRYPT_INFO = ^CMSG_KEY_TRANS_ENCRYPT_INFO;
  {$EXTERNALSYM PCMSG_KEY_TRANS_ENCRYPT_INFO}
  _CMSG_KEY_TRANS_ENCRYPT_INFO = record
    cbSize: DWORD;
    dwRecipientIndex: DWORD;
    KeyEncryptionAlgorithm: CRYPT_ALGORITHM_IDENTIFIER;
    EncryptedKey: CRYPT_DATA_BLOB;
    dwFlags: DWORD;
  end;
  {$EXTERNALSYM _CMSG_KEY_TRANS_ENCRYPT_INFO}
  CMSG_KEY_TRANS_ENCRYPT_INFO = _CMSG_KEY_TRANS_ENCRYPT_INFO;
  {$EXTERNALSYM CMSG_KEY_TRANS_ENCRYPT_INFO}
  TCmsgKeyTransEncryptInfo = CMSG_KEY_TRANS_ENCRYPT_INFO;
  PCmsgKeyTransEncryptInfo = PCMSG_KEY_TRANS_ENCRYPT_INFO;

const
  CMSG_KEY_TRANS_ENCRYPT_FREE_PARA_FLAG = $00000001;
  {$EXTERNALSYM CMSG_KEY_TRANS_ENCRYPT_FREE_PARA_FLAG}

//+-------------------------------------------------------------------------
// Upon input, KeyTransEncryptInfo has been initialized from the
// KeyTransEncodeInfo.
//
// The following fields may be changed in KeyTransEncryptInfo:
//      EncryptedKey
//      KeyEncryptionAlgorithm.Parameters
//      dwFlags
//
// All other fields in the KeyTransEncryptInfo are READONLY.
//
// The EncryptedKey must be updated. The pfnAlloc and pfnFree specified in
// ContentEncryptInfo must be used for doing the allocation.
//
// If the KeyEncryptionAlgorithm.Parameters is updated, then, the
// CMSG_KEY_TRANS_ENCRYPT_FREE_PARA_FLAG must be set in dwFlags.
// The pfnAlloc and pfnFree specified in ContentEncryptInfo must be used
// for doing the allocation.
//
// KeyEncryptionAlgorithm.pszObjId is used to get the OIDFunctionAddress.
//--------------------------------------------------------------------------

const
  CMSG_OID_EXPORT_KEY_TRANS_FUNC = 'CryptMsgDllExportKeyTrans';
  {$EXTERNALSYM CMSG_OID_EXPORT_KEY_TRANS_FUNC}

type
  PFN_CMSG_EXPORT_KEY_TRANS = function (pContentEncryptInfo: PCMSG_CONTENT_ENCRYPT_INFO;
    pKeyTransEncodeInfo: PCMSG_KEY_TRANS_RECIPIENT_ENCODE_INFO;
    pKeyTransEncryptInfo: PCMSG_KEY_TRANS_ENCRYPT_INFO; dwFlags: DWORD;
    pvReserved: Pointer): BOOL; stdcall;
  {$EXTERNALSYM PFN_CMSG_EXPORT_KEY_TRANS}
  PfnCmsgExportKeyTrans = PFN_CMSG_EXPORT_KEY_TRANS;

//+-------------------------------------------------------------------------
//  Key Agree Key Encrypt Info
//
//  The following data structure contains the information updated by the
//  ExportKeyAgree installable function for each encrypted key agree
//  recipient.
//--------------------------------------------------------------------------

type
  PCMSG_KEY_AGREE_KEY_ENCRYPT_INFO = ^CMSG_KEY_AGREE_KEY_ENCRYPT_INFO;
  {$EXTERNALSYM PCMSG_KEY_AGREE_KEY_ENCRYPT_INFO}
  _CMSG_KEY_AGREE_KEY_ENCRYPT_INFO = record
    cbSize: DWORD;
    EncryptedKey: CRYPT_DATA_BLOB;
  end;
  {$EXTERNALSYM _CMSG_KEY_AGREE_KEY_ENCRYPT_INFO}
  CMSG_KEY_AGREE_KEY_ENCRYPT_INFO = _CMSG_KEY_AGREE_KEY_ENCRYPT_INFO;
  {$EXTERNALSYM CMSG_KEY_AGREE_KEY_ENCRYPT_INFO}
  TCmsgKeyAgreeKeyEncryptInfo = CMSG_KEY_AGREE_KEY_ENCRYPT_INFO;
  PCmsgKeyAgreeKeyEncryptInfo = PCMSG_KEY_AGREE_KEY_ENCRYPT_INFO;

  PPCMSG_KEY_AGREE_KEY_ENCRYPT_INFO = ^PCMSG_KEY_AGREE_KEY_ENCRYPT_INFO;
  {$NODEFINE PPCMSG_KEY_AGREE_KEY_ENCRYPT_INFO}

//+-------------------------------------------------------------------------
//  Key Agree Encrypt Info
//
//  The following data structure contains the information applicable to
//  all recipients. Its updated by the ExportKeyAgree installable function.
//--------------------------------------------------------------------------

  PCMSG_KEY_AGREE_ENCRYPT_INFO = ^CMSG_KEY_AGREE_ENCRYPT_INFO;
  {$EXTERNALSYM PCMSG_KEY_AGREE_ENCRYPT_INFO}
  _CMSG_KEY_AGREE_ENCRYPT_INFO = record
    cbSize: DWORD;
    dwRecipientIndex: DWORD;
    KeyEncryptionAlgorithm: CRYPT_ALGORITHM_IDENTIFIER;
    UserKeyingMaterial: CRYPT_DATA_BLOB;
    dwOriginatorChoice: DWORD;
    Union: record
    case Integer of
      // CMSG_KEY_AGREE_ORIGINATOR_CERT
      0: (OriginatorCertId: CERT_ID);
      // CMSG_KEY_AGREE_ORIGINATOR_PUBLIC_KEY
      1: (OriginatorPublicKeyInfo: CERT_PUBLIC_KEY_INFO);
    end;
    cKeyAgreeKeyEncryptInfo: DWORD;
    rgpKeyAgreeKeyEncryptInfo: PPCMSG_KEY_AGREE_KEY_ENCRYPT_INFO;
    dwFlags: DWORD;
  end;
  {$EXTERNALSYM _CMSG_KEY_AGREE_ENCRYPT_INFO}
  CMSG_KEY_AGREE_ENCRYPT_INFO = _CMSG_KEY_AGREE_ENCRYPT_INFO;
  {$EXTERNALSYM CMSG_KEY_AGREE_ENCRYPT_INFO}
  TCmsgKeyAgreeEncryptInfo = CMSG_KEY_AGREE_ENCRYPT_INFO;
  PCmsgKeyAgreeEncryptInfo = PCMSG_KEY_AGREE_ENCRYPT_INFO;

const
  CMSG_KEY_AGREE_ENCRYPT_FREE_PARA_FLAG        = $00000001;
  {$EXTERNALSYM CMSG_KEY_AGREE_ENCRYPT_FREE_PARA_FLAG}
  CMSG_KEY_AGREE_ENCRYPT_FREE_MATERIAL_FLAG    = $00000002;
  {$EXTERNALSYM CMSG_KEY_AGREE_ENCRYPT_FREE_MATERIAL_FLAG}
  CMSG_KEY_AGREE_ENCRYPT_FREE_PUBKEY_ALG_FLAG  = $00000004;
  {$EXTERNALSYM CMSG_KEY_AGREE_ENCRYPT_FREE_PUBKEY_ALG_FLAG}
  CMSG_KEY_AGREE_ENCRYPT_FREE_PUBKEY_PARA_FLAG = $00000008;
  {$EXTERNALSYM CMSG_KEY_AGREE_ENCRYPT_FREE_PUBKEY_PARA_FLAG}
  CMSG_KEY_AGREE_ENCRYPT_FREE_PUBKEY_BITS_FLAG = $00000010;
  {$EXTERNALSYM CMSG_KEY_AGREE_ENCRYPT_FREE_PUBKEY_BITS_FLAG}

//+-------------------------------------------------------------------------
// Upon input, KeyAgreeEncryptInfo has been initialized from the
// KeyAgreeEncodeInfo.
//
// The following fields may be changed in KeyAgreeEncryptInfo:
//      KeyEncryptionAlgorithm.Parameters
//      UserKeyingMaterial
//      dwOriginatorChoice
//      OriginatorCertId
//      OriginatorPublicKeyInfo
//      dwFlags
//
// All other fields in the KeyAgreeEncryptInfo are READONLY.
//
// If the KeyEncryptionAlgorithm.Parameters is updated, then, the
// CMSG_KEY_AGREE_ENCRYPT_FREE_PARA_FLAG must be set in dwFlags.
// The pfnAlloc and pfnFree specified in ContentEncryptInfo must be used
// for doing the allocation.
//
// If the UserKeyingMaterial is updated, then, the
// CMSG_KEY_AGREE_ENCRYPT_FREE_MATERIAL_FLAG must be set in dwFlags.
// pfnAlloc and pfnFree must be used for doing the allocation.
//
// The dwOriginatorChoice must be updated to either
// CMSG_KEY_AGREE_ORIGINATOR_CERT or CMSG_KEY_AGREE_ORIGINATOR_PUBLIC_KEY.
//
// If the OriginatorPublicKeyInfo is updated, then, the appropriate
// CMSG_KEY_AGREE_ENCRYPT_FREE_PUBKEY_*_FLAG must be set in dwFlags and
// pfnAlloc and pfnFree must be used for doing the allocation.
//
// If CMSG_CONTENT_ENCRYPT_PAD_ENCODED_LEN_FLAG is set upon entry
// in pContentEncryptInfo->dwEncryptFlags, then, the OriginatorPublicKeyInfo's
// Ephemeral PublicKey should be padded with zeroes to always obtain the
// same maximum encoded length. Note, the length of the generated ephemeral Y
// public key can vary depending on the number of leading zero bits.
//
// Upon input, the array of *rgpKeyAgreeKeyEncryptInfo has been initialized.
// The EncryptedKey must be updated for each recipient key.
// The pfnAlloc and pfnFree specified in
// ContentEncryptInfo must be used for doing the allocation.
//
// KeyEncryptionAlgorithm.pszObjId is used to get the OIDFunctionAddress.
//--------------------------------------------------------------------------

const
  CMSG_OID_EXPORT_KEY_AGREE_FUNC = 'CryptMsgDllExportKeyAgree';
  {$EXTERNALSYM CMSG_OID_EXPORT_KEY_AGREE_FUNC}

type
  PFN_CMSG_EXPORT_KEY_AGREE = function (pContentEncryptInfo: PCMSG_CONTENT_ENCRYPT_INFO;
    pKeyAgreeEncodeInfo: PCMSG_KEY_AGREE_RECIPIENT_ENCODE_INFO;
    pKeyAgreeEncryptInfo: PCMSG_KEY_AGREE_ENCRYPT_INFO; dwFlags: DWORD;
    pvReserved: Pointer): BOOL; stdcall;
  {$EXTERNALSYM PFN_CMSG_EXPORT_KEY_AGREE}
  PfnCmsgExportKeyAgree = PFN_CMSG_EXPORT_KEY_AGREE;

//+-------------------------------------------------------------------------
//  Mail List Encrypt Info
//
//  The following data structure contains the information updated by the
//  ExportMailList installable function.
//--------------------------------------------------------------------------

type
  PCMSG_MAIL_LIST_ENCRYPT_INFO = ^CMSG_MAIL_LIST_ENCRYPT_INFO;
  {$EXTERNALSYM PCMSG_MAIL_LIST_ENCRYPT_INFO}
  _CMSG_MAIL_LIST_ENCRYPT_INFO = record
    cbSize: DWORD;
    dwRecipientIndex: DWORD;
    KeyEncryptionAlgorithm: CRYPT_ALGORITHM_IDENTIFIER;
    EncryptedKey: CRYPT_DATA_BLOB;
    dwFlags: DWORD;
  end;
  {$EXTERNALSYM _CMSG_MAIL_LIST_ENCRYPT_INFO}
  CMSG_MAIL_LIST_ENCRYPT_INFO = _CMSG_MAIL_LIST_ENCRYPT_INFO;
  {$EXTERNALSYM CMSG_MAIL_LIST_ENCRYPT_INFO}
  TCmsgMailListEncryptInfo = CMSG_MAIL_LIST_ENCRYPT_INFO;
  PCmsgMailListEncryptInfo = PCMSG_MAIL_LIST_ENCRYPT_INFO;

const
  CMSG_MAIL_LIST_ENCRYPT_FREE_PARA_FLAG = $00000001;
  {$EXTERNALSYM CMSG_MAIL_LIST_ENCRYPT_FREE_PARA_FLAG}

//+-------------------------------------------------------------------------
// Upon input, MailListEncryptInfo has been initialized from the
// MailListEncodeInfo.
//
// The following fields may be changed in MailListEncryptInfo:
//      EncryptedKey
//      KeyEncryptionAlgorithm.Parameters
//      dwFlags
//
// All other fields in the MailListEncryptInfo are READONLY.
//
// The EncryptedKey must be updated. The pfnAlloc and pfnFree specified in
// ContentEncryptInfo must be used for doing the allocation.
//
// If the KeyEncryptionAlgorithm.Parameters is updated, then, the
// CMSG_MAIL_LIST_ENCRYPT_FREE_PARA_FLAG must be set in dwFlags.
// The pfnAlloc and pfnFree specified in ContentEncryptInfo must be used
// for doing the allocation.
//
// KeyEncryptionAlgorithm.pszObjId is used to get the OIDFunctionAddress.
//--------------------------------------------------------------------------

const
  CMSG_OID_EXPORT_MAIL_LIST_FUNC = 'CryptMsgDllExportMailList';
  {$EXTERNALSYM CMSG_OID_EXPORT_MAIL_LIST_FUNC}

type
  PFN_CMSG_EXPORT_MAIL_LIST = function (pContentEncryptInfo: PCMSG_CONTENT_ENCRYPT_INFO;
    pMailListEncodeInfo: PCMSG_MAIL_LIST_RECIPIENT_ENCODE_INFO;
    pMailListEncryptInfo: PCMSG_MAIL_LIST_ENCRYPT_INFO; dwFlags: DWORD;
    pvReserved: Pointer): BOOL; stdcall;
  {$EXTERNALSYM PFN_CMSG_EXPORT_MAIL_LIST}
  PfnCmsgExportMailList = PFN_CMSG_EXPORT_MAIL_LIST;

//+-------------------------------------------------------------------------
// OID Installable functions for importing an encoded and encrypted content
// encryption key.
//
// There's a different installable function for each CMS Recipient choice:
//  ImportKeyTrans
//  ImportKeyAgree
//  ImportMailList
//
// Iterates through the following OIDs to get the OID installable function:
//   KeyEncryptionOID!ContentEncryptionOID
//   KeyEncryptionOID
//   ContentEncryptionOID
//
// If the OID installable function doesn't support the specified
// KeyEncryption and ContentEncryption OIDs, then, return FALSE with
// LastError set to E_NOTIMPL.
//--------------------------------------------------------------------------

const
  CMSG_OID_IMPORT_KEY_TRANS_FUNC = 'CryptMsgDllImportKeyTrans';
  {$EXTERNALSYM CMSG_OID_IMPORT_KEY_TRANS_FUNC}

type
  PFN_CMSG_IMPORT_KEY_TRANS = function (pContentEncryptionAlgorithm: PCRYPT_ALGORITHM_IDENTIFIER;
    pKeyTransDecryptPara: PCMSG_CTRL_KEY_TRANS_DECRYPT_PARA; dwFlags: DWORD;
    pvReserved: Pointer; var phContentEncryptKey: HCRYPTKEY): BOOL; stdcall;
  {$EXTERNALSYM PFN_CMSG_IMPORT_KEY_TRANS}
  PfnCmsgImportKeyTrans = PFN_CMSG_IMPORT_KEY_TRANS;

const
  CMSG_OID_IMPORT_KEY_AGREE_FUNC = 'CryptMsgDllImportKeyAgree';
  {$EXTERNALSYM CMSG_OID_IMPORT_KEY_AGREE_FUNC}

type
  PFN_CMSG_IMPORT_KEY_AGREE = function (pContentEncryptionAlgorithm: PCRYPT_ALGORITHM_IDENTIFIER;
    pKeyAgreeDecryptPara: PCMSG_CTRL_KEY_AGREE_DECRYPT_PARA; dwFlags: DWORD;
    pvReserved: Pointer; var phContentEncryptKey: HCRYPTKEY): BOOL; stdcall;
  {$EXTERNALSYM PFN_CMSG_IMPORT_KEY_AGREE}
  PfnCmsgImportKeyAgree = PFN_CMSG_IMPORT_KEY_AGREE;

const
  CMSG_OID_IMPORT_MAIL_LIST_FUNC = 'CryptMsgDllImportMailList';
  {$EXTERNALSYM CMSG_OID_IMPORT_MAIL_LIST_FUNC}

type
  PFN_CMSG_IMPORT_MAIL_LIST = function (pContentEncryptionAlgorithm: PCRYPT_ALGORITHM_IDENTIFIER;
    pMailListDecryptPara: PCMSG_CTRL_MAIL_LIST_DECRYPT_PARA; dwFlags: DWORD;
    pvReserved: Pointer; var phContentEncryptKey: HCRYPTKEY): BOOL; stdcall;
  {$EXTERNALSYM PFN_CMSG_IMPORT_MAIL_LIST}
  PfnCmsgImportMailList = PFN_CMSG_IMPORT_MAIL_LIST;

//+=========================================================================
//  Certificate Store Data Structures and APIs
//==========================================================================

//+-------------------------------------------------------------------------
//              In its most basic implementation, a cert store is simply a
//              collection of certificates and/or CRLs. This is the case when
//              a cert store is opened with all of its certificates and CRLs
//              coming from a PKCS #7 encoded cryptographic message.
//
//              Nonetheless, all cert stores have the following properties:
//               - A public key may have more than one certificate in the store.
//                 For example, a private/public key used for signing may have a
//                 certificate issued for VISA and another issued for
//                 Mastercard. Also, when a certificate is renewed there might
//                 be more than one certificate with the same subject and
//                 issuer.
//               - However, each certificate in the store is uniquely
//                 identified by its Issuer and SerialNumber.
//               - There's an issuer of subject certificate relationship. A
//                 certificate's issuer is found by doing a match of
//                 pSubjectCert->Issuer with pIssuerCert->Subject.
//                 The relationship is verified by using
//                 the issuer's public key to verify the subject certificate's
//                 signature. Note, there might be X.509 v3 extensions
//                 to assist in finding the issuer certificate.
//               - Since issuer certificates might be renewed, a subject
//                 certificate might have more than one issuer certificate.
//               - There's an issuer of CRL relationship. An
//                 issuer's CRL is found by doing a match of
//                 pIssuerCert->Subject with pCrl->Issuer.
//                 The relationship is verified by using
//                 the issuer's public key to verify the CRL's
//                 signature. Note, there might be X.509 v3 extensions
//                 to assist in finding the CRL.
//               - Since some issuers might support the X.509 v3 delta CRL
//                 extensions, an issuer might have more than one CRL.
//               - The store shouldn't have any redundant certificates or
//                 CRLs. There shouldn't be two certificates with the same
//                 Issuer and SerialNumber. There shouldn't be two CRLs with
//                 the same Issuer, ThisUpdate and NextUpdate.
//               - The store has NO policy or trust information. No
//                 certificates are tagged as being "root". Its up to
//                 the application to maintain a list of CertIds (Issuer +
//                 SerialNumber) for certificates it trusts.
//               - The store might contain bad certificates and/or CRLs.
//                 The issuer's signature of a subject certificate or CRL may
//                 not verify. Certificates or CRLs may not satisfy their
//                 time validity requirements. Certificates may be
//                 revoked.
//
//              In addition to the certificates and CRLs, properties can be
//              stored. There are two predefined property IDs for a user
//              certificate: CERT_KEY_PROV_HANDLE_PROP_ID and
//              CERT_KEY_PROV_INFO_PROP_ID. The CERT_KEY_PROV_HANDLE_PROP_ID
//              is a HCRYPTPROV handle to the private key assoicated
//              with the certificate. The CERT_KEY_PROV_INFO_PROP_ID contains
//              information to be used to call
//              CryptAcquireContext and CryptSetProvParam to get a handle
//              to the private key associated with the certificate.
//
//              There exists two more predefined property IDs for certificates
//              and CRLs, CERT_SHA1_HASH_PROP_ID and CERT_MD5_HASH_PROP_ID.
//              If these properties don't already exist, then, a hash of the
//              content is computed. (CERT_HASH_PROP_ID maps to the default
//              hash algorithm, currently, CERT_SHA1_HASH_PROP_ID).
//
//              There are additional APIs for creating certificate and CRL
//      contexts not in a store (CertCreateCertificateContext and
//      CertCreateCRLContext).
//
//--------------------------------------------------------------------------

type
  HCERTSTORE = Pointer;
  {$EXTERNALSYM HCERTSTORE}
  PHCERTSTORE = ^HCERTSTORE;
  {$NODEFINE PHCERTSTORE}

//+-------------------------------------------------------------------------
//  Certificate context.
//
//  A certificate context contains both the encoded and decoded representation
//  of a certificate. A certificate context returned by a cert store function
//  must be freed by calling the CertFreeCertificateContext function. The
//  CertDuplicateCertificateContext function can be called to make a duplicate
//  copy (which also must be freed by calling CertFreeCertificateContext).
//--------------------------------------------------------------------------

  PCERT_CONTEXT = ^CERT_CONTEXT;
  {$EXTERNALSYM CERT_CONTEXT}
  _CERT_CONTEXT = record
    dwCertEncodingType: DWORD;
    pbCertEncoded: LPBYTE;
    cbCertEncoded: DWORD;
    pCertInfo: PCERT_INFO;
    hCertStore: HCERTSTORE;
  end;
  {$EXTERNALSYM _CERT_CONTEXT}
  CERT_CONTEXT = _CERT_CONTEXT;
  {$EXTERNALSYM CERT_CONTEXT}
  TCertContext = CERT_CONTEXT;
  PCertContext = PCERT_CONTEXT;

  PCCERT_CONTEXT = PCERT_CONTEXT;
  {$EXTERNALSYM PCCERT_CONTEXT}
  PPCCERT_CONTEXT = ^PCCERT_CONTEXT;
  {$NODEFINE PCCERT_CONTEXT}

//+-------------------------------------------------------------------------
//  CRL context.
//
//  A CRL context contains both the encoded and decoded representation
//  of a CRL. A CRL context returned by a cert store function
//  must be freed by calling the CertFreeCRLContext function. The
//  CertDuplicateCRLContext function can be called to make a duplicate
//  copy (which also must be freed by calling CertFreeCRLContext).
//--------------------------------------------------------------------------

  PCRL_CONTEXT = ^CRL_CONTEXT;
  {$EXTERNALSYM PCRL_CONTEXT}
  _CRL_CONTEXT = record
    dwCertEncodingType: DWORD;
    pbCrlEncoded: LPBYTE;
    cbCrlEncoded: DWORD;
    pCrlInfo: PCRL_INFO;
    hCertStore: HCERTSTORE;
  end;
  {$EXTERNALSYM _CRL_CONTEXT}
  CRL_CONTEXT = _CRL_CONTEXT;
  {$EXTERNALSYM CRL_CONTEXT}
  TCrlContext = CRL_CONTEXT;
  PCrlContext = PCRL_CONTEXT;

  PCCRL_CONTEXT = PCRL_CONTEXT;
  {$EXTERNALSYM PCCRL_CONTEXT}
  PPCCRL_CONTEXT = ^PCCRL_CONTEXT;
  {$NODEFINE PPCCRL_CONTEXT}

//+-------------------------------------------------------------------------
//  Certificate Trust List (CTL) context.
//
//  A CTL context contains both the encoded and decoded representation
//  of a CTL. Also contains an opened HCRYPTMSG handle to the decoded
//  cryptographic signed message containing the CTL_INFO as its inner content.
//  pbCtlContent is the encoded inner content of the signed message.
//
//  The CryptMsg APIs can be used to extract additional signer information.
//--------------------------------------------------------------------------

  PCTL_CONTEXT = ^CTL_CONTEXT;
  {$EXTERNALSYM PCTL_CONTEXT}
  _CTL_CONTEXT = record
    dwMsgAndCertEncodingType: DWORD;
    pbCtlEncoded: LPBYTE;
    cbCtlEncoded: DWORD;
    pCtlInfo: PCTL_INFO;
    hCertStore: HCERTSTORE;
    hCryptMsg: HCRYPTMSG;
    pbCtlContent: LPBYTE;
    cbCtlContent: DWORD;
  end;
  {$EXTERNALSYM _CTL_CONTEXT}
  CTL_CONTEXT = _CTL_CONTEXT;
  {$EXTERNALSYM CTL_CONTEXT}
  TCtlContext = CTL_CONTEXT;
  PCtlContext = PCTL_CONTEXT;

  PCCTL_CONTEXT = PCTL_CONTEXT;
  {$EXTERNALSYM PCCTL_CONTEXT}
  PPCCTL_CONTEXT = ^PCCTL_CONTEXT;
  {$EXTERNALSYM PPCCTL_CONTEXT}
  
//+-------------------------------------------------------------------------
//  Certificate, CRL and CTL property IDs
//
//  See CertSetCertificateContextProperty or CertGetCertificateContextProperty
//  for usage information.
//--------------------------------------------------------------------------

const
  CERT_KEY_PROV_HANDLE_PROP_ID      = 1;
  {$EXTERNALSYM CERT_KEY_PROV_HANDLE_PROP_ID}
  CERT_KEY_PROV_INFO_PROP_ID        = 2;
  {$EXTERNALSYM CERT_KEY_PROV_INFO_PROP_ID}
  CERT_SHA1_HASH_PROP_ID            = 3;
  {$EXTERNALSYM CERT_SHA1_HASH_PROP_ID}
  CERT_MD5_HASH_PROP_ID             = 4;
  {$EXTERNALSYM CERT_MD5_HASH_PROP_ID}
  CERT_HASH_PROP_ID                 = CERT_SHA1_HASH_PROP_ID;
  {$EXTERNALSYM CERT_HASH_PROP_ID}
  CERT_KEY_CONTEXT_PROP_ID          = 5;
  {$EXTERNALSYM CERT_KEY_CONTEXT_PROP_ID}
  CERT_KEY_SPEC_PROP_ID             = 6;
  {$EXTERNALSYM CERT_KEY_SPEC_PROP_ID}
  CERT_IE30_RESERVED_PROP_ID        = 7;
  {$EXTERNALSYM CERT_IE30_RESERVED_PROP_ID}
  CERT_PUBKEY_HASH_RESERVED_PROP_ID = 8;
  {$EXTERNALSYM CERT_PUBKEY_HASH_RESERVED_PROP_ID}
  CERT_ENHKEY_USAGE_PROP_ID         = 9;
  {$EXTERNALSYM CERT_ENHKEY_USAGE_PROP_ID}
  CERT_CTL_USAGE_PROP_ID            = CERT_ENHKEY_USAGE_PROP_ID;
  {$EXTERNALSYM CERT_CTL_USAGE_PROP_ID}
  CERT_NEXT_UPDATE_LOCATION_PROP_ID = 10;
  {$EXTERNALSYM CERT_NEXT_UPDATE_LOCATION_PROP_ID}
  CERT_FRIENDLY_NAME_PROP_ID        = 11;
  {$EXTERNALSYM CERT_FRIENDLY_NAME_PROP_ID}
  CERT_PVK_FILE_PROP_ID             = 12;
  {$EXTERNALSYM CERT_PVK_FILE_PROP_ID}
  CERT_DESCRIPTION_PROP_ID          = 13;
  {$EXTERNALSYM CERT_DESCRIPTION_PROP_ID}
  CERT_ACCESS_STATE_PROP_ID         = 14;
  {$EXTERNALSYM CERT_ACCESS_STATE_PROP_ID}
  CERT_SIGNATURE_HASH_PROP_ID       = 15;
  {$EXTERNALSYM CERT_SIGNATURE_HASH_PROP_ID}
  CERT_SMART_CARD_DATA_PROP_ID      = 16;
  {$EXTERNALSYM CERT_SMART_CARD_DATA_PROP_ID}
  CERT_EFS_PROP_ID                  = 17;
  {$EXTERNALSYM CERT_EFS_PROP_ID}
  CERT_FORTEZZA_DATA_PROP_ID        = 18;
  {$EXTERNALSYM CERT_FORTEZZA_DATA_PROP_ID}
  CERT_ARCHIVED_PROP_ID             = 19;
  {$EXTERNALSYM CERT_ARCHIVED_PROP_ID}
  CERT_KEY_IDENTIFIER_PROP_ID       = 20;
  {$EXTERNALSYM CERT_KEY_IDENTIFIER_PROP_ID}
  CERT_AUTO_ENROLL_PROP_ID          = 21;
  {$EXTERNALSYM CERT_AUTO_ENROLL_PROP_ID}
  CERT_PUBKEY_ALG_PARA_PROP_ID      = 22;
  {$EXTERNALSYM CERT_PUBKEY_ALG_PARA_PROP_ID}

  CERT_FIRST_RESERVED_PROP_ID = 23;
  {$EXTERNALSYM CERT_FIRST_RESERVED_PROP_ID}

// Note, 32 - 35 are reserved for the CERT, CRL, CTL and KeyId file element IDs.

  CERT_LAST_RESERVED_PROP_ID = $00007FFF;
  {$EXTERNALSYM CERT_LAST_RESERVED_PROP_ID}
  CERT_FIRST_USER_PROP_ID    = $00008000;
  {$EXTERNALSYM CERT_FIRST_USER_PROP_ID}
  CERT_LAST_USER_PROP_ID     = $0000FFFF;
  {$EXTERNALSYM CERT_LAST_USER_PROP_ID}

function IS_CERT_HASH_PROP_ID(X: DWORD): Boolean;
{$EXTERNALSYM IS_CERT_HASH_PROP_ID}

//+-------------------------------------------------------------------------
//  Access State flags returned by CERT_ACCESS_STATE_PROP_ID. Note,
//  CERT_ACCESS_PROP_ID is read only.
//--------------------------------------------------------------------------

// Set if context property writes are persisted. For instance, not set for
// memory store contexts. Set for registry based stores opened as read or write.
// Not set for registry based stores opened as read only.

const
  CERT_ACCESS_STATE_WRITE_PERSIST_FLAG = $1;
  {$EXTERNALSYM CERT_ACCESS_STATE_WRITE_PERSIST_FLAG}

// Set if context resides in a SYSTEM or SYSTEM_REGISTRY store.

  CERT_ACCESS_STATE_SYSTEM_STORE_FLAG = $2;
  {$EXTERNALSYM CERT_ACCESS_STATE_SYSTEM_STORE_FLAG}

//+-------------------------------------------------------------------------
//  Cryptographic Key Provider Information
//
//  CRYPT_KEY_PROV_INFO defines the CERT_KEY_PROV_INFO_PROP_ID's pvData.
//
//  The CRYPT_KEY_PROV_INFO fields are passed to CryptAcquireContext
//  to get a HCRYPTPROV handle. The optional CRYPT_KEY_PROV_PARAM fields are
//  passed to CryptSetProvParam to further initialize the provider.
//
//  The dwKeySpec field identifies the private key to use from the container
//  For example, AT_KEYEXCHANGE or AT_SIGNATURE.
//--------------------------------------------------------------------------

type
  PCRYPT_KEY_PROV_PARAM = ^CRYPT_KEY_PROV_PARAM;
  {$EXTERNALSYM PCRYPT_KEY_PROV_PARAM}
  _CRYPT_KEY_PROV_PARAM = record
    dwParam: DWORD;
    pbData: LPBYTE;
    cbData: DWORD;
    dwFlags: DWORD;
  end;
  {$EXTERNALSYM _CRYPT_KEY_PROV_PARAM}
  CRYPT_KEY_PROV_PARAM = _CRYPT_KEY_PROV_PARAM;
  {$EXTERNALSYM CRYPT_KEY_PROV_PARAM}
  TCryptKeyProvParam = CRYPT_KEY_PROV_PARAM;
  PCryptKeyProvParam = PCRYPT_KEY_PROV_PARAM;

  PCRYPT_KEY_PROV_INFO = ^CRYPT_KEY_PROV_INFO;
  {$EXTERNALSYM PCRYPT_KEY_PROV_INFO}
  _CRYPT_KEY_PROV_INFO = record
    pwszContainerName: LPWSTR;
    pwszProvName: LPWSTR;
    dwProvType: DWORD;
    dwFlags: DWORD;
    cProvParam: DWORD;
    rgProvParam: PCRYPT_KEY_PROV_PARAM;
    dwKeySpec: DWORD;
  end;
  {$EXTERNALSYM _CRYPT_KEY_PROV_INFO}
  CRYPT_KEY_PROV_INFO = _CRYPT_KEY_PROV_INFO;
  {$EXTERNALSYM CRYPT_KEY_PROV_INFO}
  TCryptKeyProvInfo = CRYPT_KEY_PROV_INFO;
  PCryptKeyProvInfo = PCRYPT_KEY_PROV_INFO;

//+-------------------------------------------------------------------------
//  The following flag should be set in the above dwFlags to enable
//  a CertSetCertificateContextProperty(CERT_KEY_CONTEXT_PROP_ID) after a
//  CryptAcquireContext is done in the Sign or Decrypt Message functions.
//
//  The following define must not collide with any of the
//  CryptAcquireContext dwFlag defines.
//--------------------------------------------------------------------------

const
  CERT_SET_KEY_PROV_HANDLE_PROP_ID = $00000001;
  {$EXTERNALSYM CERT_SET_KEY_PROV_HANDLE_PROP_ID}
  CERT_SET_KEY_CONTEXT_PROP_ID     = $00000001;
  {$EXTERNALSYM CERT_SET_KEY_CONTEXT_PROP_ID}

//+-------------------------------------------------------------------------
//  Certificate Key Context
//
//  CERT_KEY_CONTEXT defines the CERT_KEY_CONTEXT_PROP_ID's pvData.
//--------------------------------------------------------------------------

type
  PCERT_KEY_CONTEXT = ^CERT_KEY_CONTEXT;
  {$EXTERNALSYM PCERT_KEY_CONTEXT}
  _CERT_KEY_CONTEXT = record
    cbSize: DWORD; // sizeof(CERT_KEY_CONTEXT)
    hCryptProv: HCRYPTPROV;
    dwKeySpec: DWORD;
  end;
  {$EXTERNALSYM _CERT_KEY_CONTEXT}
  CERT_KEY_CONTEXT = _CERT_KEY_CONTEXT;
  {$EXTERNALSYM CERT_KEY_CONTEXT}
  TCertKeyContext = CERT_KEY_CONTEXT;
  PCertKeyContext = PCERT_KEY_CONTEXT;

//+-------------------------------------------------------------------------
//  Certificate Store Provider Types
//--------------------------------------------------------------------------

const
  CERT_STORE_PROV_MSG    = LPCSTR(1);
  {$EXTERNALSYM CERT_STORE_PROV_MSG}
  CERT_STORE_PROV_MEMORY = LPCSTR(2);
  {$EXTERNALSYM CERT_STORE_PROV_MEMORY}
  CERT_STORE_PROV_FILE   = LPCSTR(3);
  {$EXTERNALSYM CERT_STORE_PROV_FILE}
  CERT_STORE_PROV_REG    = LPCSTR(4);
  {$EXTERNALSYM CERT_STORE_PROV_REG}

  CERT_STORE_PROV_PKCS7      = LPCSTR(5);
  {$EXTERNALSYM CERT_STORE_PROV_PKCS7}
  CERT_STORE_PROV_SERIALIZED = LPCSTR(6);
  {$EXTERNALSYM CERT_STORE_PROV_SERIALIZED}
  CERT_STORE_PROV_FILENAME_A = LPCSTR(7);
  {$EXTERNALSYM CERT_STORE_PROV_FILENAME_A}
  CERT_STORE_PROV_FILENAME_W = LPCSTR(8);
  {$EXTERNALSYM CERT_STORE_PROV_FILENAME_W}
  CERT_STORE_PROV_FILENAME   = CERT_STORE_PROV_FILENAME_W;
  {$EXTERNALSYM CERT_STORE_PROV_FILENAME}
  CERT_STORE_PROV_SYSTEM_A   = LPCSTR(9);
  {$EXTERNALSYM CERT_STORE_PROV_SYSTEM_A}
  CERT_STORE_PROV_SYSTEM_W   = LPCSTR(10);
  {$EXTERNALSYM CERT_STORE_PROV_SYSTEM_W}
  CERT_STORE_PROV_SYSTEM     = CERT_STORE_PROV_SYSTEM_W;
  {$EXTERNALSYM CERT_STORE_PROV_SYSTEM}

  CERT_STORE_PROV_COLLECTION        = LPCSTR(11);
  {$EXTERNALSYM CERT_STORE_PROV_COLLECTION}
  CERT_STORE_PROV_SYSTEM_REGISTRY_A = LPCSTR(12);
  {$EXTERNALSYM CERT_STORE_PROV_SYSTEM_REGISTRY_A}
  CERT_STORE_PROV_SYSTEM_REGISTRY_W = LPCSTR(13);
  {$EXTERNALSYM CERT_STORE_PROV_SYSTEM_REGISTRY_W}
  CERT_STORE_PROV_SYSTEM_REGISTRY   = CERT_STORE_PROV_SYSTEM_REGISTRY_W;
  {$EXTERNALSYM CERT_STORE_PROV_SYSTEM_REGISTRY}
  CERT_STORE_PROV_PHYSICAL_W        = LPCSTR(14);
  {$EXTERNALSYM CERT_STORE_PROV_PHYSICAL_W}
  CERT_STORE_PROV_PHYSICAL          = CERT_STORE_PROV_PHYSICAL_W;
  {$EXTERNALSYM CERT_STORE_PROV_PHYSICAL}
  CERT_STORE_PROV_SMART_CARD_W      = LPCSTR(15);
  {$EXTERNALSYM CERT_STORE_PROV_SMART_CARD_W}
  CERT_STORE_PROV_SMART_CARD        = CERT_STORE_PROV_SMART_CARD_W;
  {$EXTERNALSYM CERT_STORE_PROV_SMART_CARD}
  CERT_STORE_PROV_LDAP_W            = LPCSTR(16);
  {$EXTERNALSYM CERT_STORE_PROV_LDAP_W}
  CERT_STORE_PROV_LDAP              = CERT_STORE_PROV_LDAP_W;
  {$EXTERNALSYM CERT_STORE_PROV_LDAP}

  sz_CERT_STORE_PROV_MEMORY     = 'Memory';
  {$EXTERNALSYM sz_CERT_STORE_PROV_MEMORY}
  sz_CERT_STORE_PROV_FILENAME_W = 'File';
  {$EXTERNALSYM sz_CERT_STORE_PROV_FILENAME_W}
  sz_CERT_STORE_PROV_FILENAME   = sz_CERT_STORE_PROV_FILENAME_W;
  {$EXTERNALSYM sz_CERT_STORE_PROV_FILENAME}
  sz_CERT_STORE_PROV_SYSTEM_W   = 'System';
  {$EXTERNALSYM sz_CERT_STORE_PROV_SYSTEM_W}
  sz_CERT_STORE_PROV_SYSTEM     = sz_CERT_STORE_PROV_SYSTEM_W;
  {$EXTERNALSYM sz_CERT_STORE_PROV_SYSTEM}
  sz_CERT_STORE_PROV_PKCS7      = 'PKCS7';
  {$EXTERNALSYM sz_CERT_STORE_PROV_PKCS7}
  sz_CERT_STORE_PROV_SERIALIZED = 'Serialized';
  {$EXTERNALSYM sz_CERT_STORE_PROV_SERIALIZED}

  sz_CERT_STORE_PROV_COLLECTION        = 'Collection';
  {$EXTERNALSYM sz_CERT_STORE_PROV_COLLECTION}
  sz_CERT_STORE_PROV_SYSTEM_REGISTRY_W = 'SystemRegistry';
  {$EXTERNALSYM sz_CERT_STORE_PROV_SYSTEM_REGISTRY_W}
  sz_CERT_STORE_PROV_SYSTEM_REGISTRY   = sz_CERT_STORE_PROV_SYSTEM_REGISTRY_W;
  {$EXTERNALSYM sz_CERT_STORE_PROV_SYSTEM_REGISTRY}
  sz_CERT_STORE_PROV_PHYSICAL_W        = 'Physical';
  {$EXTERNALSYM sz_CERT_STORE_PROV_PHYSICAL_W}
  sz_CERT_STORE_PROV_PHYSICAL          = sz_CERT_STORE_PROV_PHYSICAL_W;
  {$EXTERNALSYM sz_CERT_STORE_PROV_PHYSICAL}
  sz_CERT_STORE_PROV_SMART_CARD_W      = 'SmartCard';
  {$EXTERNALSYM sz_CERT_STORE_PROV_SMART_CARD_W}
  sz_CERT_STORE_PROV_SMART_CARD        = sz_CERT_STORE_PROV_SMART_CARD_W;
  {$EXTERNALSYM sz_CERT_STORE_PROV_SMART_CARD}
  sz_CERT_STORE_PROV_LDAP_W            = 'Ldap';
  {$EXTERNALSYM sz_CERT_STORE_PROV_LDAP_W}
  sz_CERT_STORE_PROV_LDAP              = sz_CERT_STORE_PROV_LDAP_W;
  {$EXTERNALSYM sz_CERT_STORE_PROV_LDAP}

//+-------------------------------------------------------------------------
//  Certificate Store verify/results flags
//--------------------------------------------------------------------------

  CERT_STORE_SIGNATURE_FLAG     = $00000001;
  {$EXTERNALSYM CERT_STORE_SIGNATURE_FLAG}
  CERT_STORE_TIME_VALIDITY_FLAG = $00000002;
  {$EXTERNALSYM CERT_STORE_TIME_VALIDITY_FLAG}
  CERT_STORE_REVOCATION_FLAG    = $00000004;
  {$EXTERNALSYM CERT_STORE_REVOCATION_FLAG}
  CERT_STORE_NO_CRL_FLAG        = $00010000;
  {$EXTERNALSYM CERT_STORE_NO_CRL_FLAG}
  CERT_STORE_NO_ISSUER_FLAG     = $00020000;
  {$EXTERNALSYM CERT_STORE_NO_ISSUER_FLAG}

//+-------------------------------------------------------------------------
//  Certificate Store open/property flags
//--------------------------------------------------------------------------

  CERT_STORE_NO_CRYPT_RELEASE_FLAG            = $00000001;
  {$EXTERNALSYM CERT_STORE_NO_CRYPT_RELEASE_FLAG}
  CERT_STORE_SET_LOCALIZED_NAME_FLAG          = $00000002;
  {$EXTERNALSYM CERT_STORE_SET_LOCALIZED_NAME_FLAG}
  CERT_STORE_DEFER_CLOSE_UNTIL_LAST_FREE_FLAG = $00000004;
  {$EXTERNALSYM CERT_STORE_DEFER_CLOSE_UNTIL_LAST_FREE_FLAG}
  CERT_STORE_DELETE_FLAG                      = $00000010;
  {$EXTERNALSYM CERT_STORE_DELETE_FLAG}
  CERT_STORE_MANIFOLD_FLAG                    = $00000100;
  {$EXTERNALSYM CERT_STORE_MANIFOLD_FLAG}
  CERT_STORE_ENUM_ARCHIVED_FLAG               = $00000200;
  {$EXTERNALSYM CERT_STORE_ENUM_ARCHIVED_FLAG}
  CERT_STORE_UPDATE_KEYID_FLAG                = $00000400;
  {$EXTERNALSYM CERT_STORE_UPDATE_KEYID_FLAG}
  CERT_STORE_READONLY_FLAG                    = $00008000;
  {$EXTERNALSYM CERT_STORE_READONLY_FLAG}
  CERT_STORE_OPEN_EXISTING_FLAG               = $00004000;
  {$EXTERNALSYM CERT_STORE_OPEN_EXISTING_FLAG}
  CERT_STORE_CREATE_NEW_FLAG                  = $00002000;
  {$EXTERNALSYM CERT_STORE_CREATE_NEW_FLAG}
  CERT_STORE_MAXIMUM_ALLOWED_FLAG             = $00001000;
  {$EXTERNALSYM CERT_STORE_MAXIMUM_ALLOWED_FLAG}

//+-------------------------------------------------------------------------
//  Certificate Store Provider flags are in the HiWord (0xFFFF0000)
//--------------------------------------------------------------------------

//+-------------------------------------------------------------------------
//  Certificate System Store Flag Values
//--------------------------------------------------------------------------
// Includes flags and location

  CERT_SYSTEM_STORE_MASK = DWORD($FFFF0000);
  {$EXTERNALSYM CERT_SYSTEM_STORE_MASK}

// Set if pvPara points to a CERT_SYSTEM_STORE_RELOCATE_PARA structure

  CERT_SYSTEM_STORE_RELOCATE_FLAG = DWORD($80000000);
  {$EXTERNALSYM CERT_SYSTEM_STORE_RELOCATE_FLAG}

type
  PCERT_SYSTEM_STORE_RELOCATE_PARA = ^CERT_SYSTEM_STORE_RELOCATE_PARA;
  {$EXTERNALSYM PCERT_SYSTEM_STORE_RELOCATE_PARA}
  _CERT_SYSTEM_STORE_RELOCATE_PARA = record
    Union1: record
    case Integer of
      0: (hKeyBase: HKEY);
      1: (pvBase: Pointer);
    end;
    case Integer of
      0: (pvSystemStore: Pointer);
      1: (pszSystemStore: LPCSTR);
      2: (pwszSystemStore: LPCWSTR);
  end;
  {$EXTERNALSYM _CERT_SYSTEM_STORE_RELOCATE_PARA}
  CERT_SYSTEM_STORE_RELOCATE_PARA = _CERT_SYSTEM_STORE_RELOCATE_PARA;
  {$EXTERNALSYM CERT_SYSTEM_STORE_RELOCATE_PARA}
  TCertSystemStoreRelocatePara = CERT_SYSTEM_STORE_RELOCATE_PARA;
  PCertSystemStoreRelocatePara = PCERT_SYSTEM_STORE_RELOCATE_PARA;

// By default, when the CurrentUser "Root" store is opened, any SystemRegistry
// roots not also on the protected root list are deleted from the cache before
// CertOpenStore() returns. Set the following flag to return all the roots
// in the SystemRegistry without checking the protected root list.

const
  CERT_SYSTEM_STORE_UNPROTECTED_FLAG = $40000000;
  {$EXTERNALSYM CERT_SYSTEM_STORE_UNPROTECTED_FLAG}

// Location of the system store:

  CERT_SYSTEM_STORE_LOCATION_MASK  = $00FF0000;
  {$EXTERNALSYM CERT_SYSTEM_STORE_LOCATION_MASK}
  CERT_SYSTEM_STORE_LOCATION_SHIFT = 16;
  {$EXTERNALSYM CERT_SYSTEM_STORE_LOCATION_SHIFT}

//  Registry: HKEY_CURRENT_USER or HKEY_LOCAL_MACHINE

  CERT_SYSTEM_STORE_CURRENT_USER_ID  = 1;
  {$EXTERNALSYM CERT_SYSTEM_STORE_CURRENT_USER_ID}
  CERT_SYSTEM_STORE_LOCAL_MACHINE_ID = 2;
  {$EXTERNALSYM CERT_SYSTEM_STORE_LOCAL_MACHINE_ID}

//  Registry: HKEY_LOCAL_MACHINE\Software\Microsoft\Cryptography\Services

  CERT_SYSTEM_STORE_CURRENT_SERVICE_ID = 4;
  {$EXTERNALSYM CERT_SYSTEM_STORE_CURRENT_SERVICE_ID}
  CERT_SYSTEM_STORE_SERVICES_ID        = 5;
  {$EXTERNALSYM CERT_SYSTEM_STORE_SERVICES_ID}

//  Registry: HKEY_USERS

  CERT_SYSTEM_STORE_USERS_ID = 6;
  {$EXTERNALSYM CERT_SYSTEM_STORE_USERS_ID}

//  Registry: HKEY_CURRENT_USER\Software\Policies\Microsoft\SystemCertificates

  CERT_SYSTEM_STORE_CURRENT_USER_GROUP_POLICY_ID = 7;
  {$EXTERNALSYM CERT_SYSTEM_STORE_CURRENT_USER_GROUP_POLICY_ID}

//  Registry: HKEY_LOCAL_MACHINE\Software\Policies\Microsoft\SystemCertificates

  CERT_SYSTEM_STORE_LOCAL_MACHINE_GROUP_POLICY_ID = 8;
  {$EXTERNALSYM CERT_SYSTEM_STORE_LOCAL_MACHINE_GROUP_POLICY_ID}

//  Registry: HKEY_LOCAL_MACHINE\Software\Microsoft\EnterpriseCertificates

  CERT_SYSTEM_STORE_LOCAL_MACHINE_ENTERPRISE_ID = 9;
  {$EXTERNALSYM CERT_SYSTEM_STORE_LOCAL_MACHINE_ENTERPRISE_ID}

  CERT_SYSTEM_STORE_CURRENT_USER    = (CERT_SYSTEM_STORE_CURRENT_USER_ID shl CERT_SYSTEM_STORE_LOCATION_SHIFT);
  {$EXTERNALSYM CERT_SYSTEM_STORE_CURRENT_USER}
  CERT_SYSTEM_STORE_LOCAL_MACHINE   = (CERT_SYSTEM_STORE_LOCAL_MACHINE_ID shl CERT_SYSTEM_STORE_LOCATION_SHIFT);
  {$EXTERNALSYM CERT_SYSTEM_STORE_LOCAL_MACHINE}
  CERT_SYSTEM_STORE_CURRENT_SERVICE = (CERT_SYSTEM_STORE_CURRENT_SERVICE_ID shl CERT_SYSTEM_STORE_LOCATION_SHIFT);
  {$EXTERNALSYM CERT_SYSTEM_STORE_CURRENT_SERVICE}
  CERT_SYSTEM_STORE_SERVICES        = (CERT_SYSTEM_STORE_SERVICES_ID shl CERT_SYSTEM_STORE_LOCATION_SHIFT);
  {$EXTERNALSYM CERT_SYSTEM_STORE_SERVICES}
  CERT_SYSTEM_STORE_USERS           = (CERT_SYSTEM_STORE_USERS_ID shl CERT_SYSTEM_STORE_LOCATION_SHIFT);
  {$EXTERNALSYM CERT_SYSTEM_STORE_USERS}

  CERT_SYSTEM_STORE_CURRENT_USER_GROUP_POLICY  = (CERT_SYSTEM_STORE_CURRENT_USER_GROUP_POLICY_ID shl CERT_SYSTEM_STORE_LOCATION_SHIFT);
  {$EXTERNALSYM CERT_SYSTEM_STORE_CURRENT_USER_GROUP_POLICY}
  CERT_SYSTEM_STORE_LOCAL_MACHINE_GROUP_POLICY = (CERT_SYSTEM_STORE_LOCAL_MACHINE_GROUP_POLICY_ID shl CERT_SYSTEM_STORE_LOCATION_SHIFT);
  {$EXTERNALSYM CERT_SYSTEM_STORE_LOCAL_MACHINE_GROUP_POLICY}

  CERT_SYSTEM_STORE_LOCAL_MACHINE_ENTERPRISE = (CERT_SYSTEM_STORE_LOCAL_MACHINE_ENTERPRISE_ID shl CERT_SYSTEM_STORE_LOCATION_SHIFT);
  {$EXTERNALSYM CERT_SYSTEM_STORE_LOCAL_MACHINE_ENTERPRISE}

//+-------------------------------------------------------------------------
//  Group Policy Store Defines
//--------------------------------------------------------------------------
// Registry path to the Group Policy system stores

  CERT_GROUP_POLICY_SYSTEM_STORE_REGPATH = 'Software\Policies\Microsoft\SystemCertificates';
  {$EXTERNALSYM CERT_GROUP_POLICY_SYSTEM_STORE_REGPATH}

//+-------------------------------------------------------------------------
//  EFS Defines
//--------------------------------------------------------------------------
// Registry path to the EFS EFSBlob SubKey - Value type is REG_BINARY

  CERT_EFSBLOB_REGPATH    = CERT_GROUP_POLICY_SYSTEM_STORE_REGPATH + '\EFS';
  {$EXTERNALSYM CERT_EFSBLOB_REGPATH}
  CERT_EFSBLOB_VALUE_NAME = 'EFSBlob';
  {$EXTERNALSYM CERT_EFSBLOB_VALUE_NAME}

//+-------------------------------------------------------------------------
//  Protected Root Defines
//--------------------------------------------------------------------------
// Registry path to the Protected Roots Flags SubKey

  CERT_PROT_ROOT_FLAGS_REGPATH    = CERT_GROUP_POLICY_SYSTEM_STORE_REGPATH + '\Root\ProtectedRoots';
  {$EXTERNALSYM CERT_PROT_ROOT_FLAGS_REGPATH}
  CERT_PROT_ROOT_FLAGS_VALUE_NAME = 'Flags';
  {$EXTERNALSYM CERT_PROT_ROOT_FLAGS_VALUE_NAME}

// Set the following flag to inhibit the opening of the CurrentUser's
// .Default physical store when opening the CurrentUser's "Root" system store.
// The .Default physical store open's the CurrentUser SystemRegistry "Root"
// store.

  CERT_PROT_ROOT_DISABLE_CURRENT_USER_FLAG = $1;
  {$EXTERNALSYM CERT_PROT_ROOT_DISABLE_CURRENT_USER_FLAG}

// Set the following flag to inhibit the adding of roots from the
// CurrentUser SystemRegistry "Root" store to the protected root list
// when the "Root" store is initially protected.

  CERT_PROT_ROOT_INHIBIT_ADD_AT_INIT_FLAG = $2;
  {$EXTERNALSYM CERT_PROT_ROOT_INHIBIT_ADD_AT_INIT_FLAG}

// Set the following flag to inhibit the purging of protected roots from the
// CurrentUser SystemRegistry "Root" store that are
// also in the LocalMachine SystemRegistry "Root" store. Note, when not
// disabled, the purging is done silently without UI.

  CERT_PROT_ROOT_INHIBIT_PURGE_LM_FLAG = $4;
  {$EXTERNALSYM CERT_PROT_ROOT_INHIBIT_PURGE_LM_FLAG}

// Set the following flag to only open the .LocalMachineGroupPolicy
// physical store when opening the CurrentUser's "Root" system store.

  CERT_PROT_ROOT_ONLY_LM_GPT_FLAG = $8;
  {$EXTERNALSYM CERT_PROT_ROOT_ONLY_LM_GPT_FLAG}

//+-------------------------------------------------------------------------
//  Certificate Registry Store Flag Values (CERT_STORE_REG)
//--------------------------------------------------------------------------

// Set this flag if the HKEY passed in pvPara points to a remote computer
// registry key.

  CERT_REGISTRY_STORE_REMOTE_FLAG = $10000;
  {$EXTERNALSYM CERT_REGISTRY_STORE_REMOTE_FLAG}

// Set this flag if the contexts are to be persisted as a single serialized
// store in the registry. Mainly used for stores downloaded from the GPT.
// Such as the CurrentUserGroupPolicy or LocalMachineGroupPolicy stores.

  CERT_REGISTRY_STORE_SERIALIZED_FLAG = $20000;
  {$EXTERNALSYM CERT_REGISTRY_STORE_SERIALIZED_FLAG}

// The following flags are for internal use. When set, the
// pvPara parameter passed to CertOpenStore is a pointer to the following
// data structure and not the HKEY. The above CERT_REGISTRY_STORE_REMOTE_FLAG
// is also set if hKeyBase was obtained via RegConnectRegistry().

  CERT_REGISTRY_STORE_CLIENT_GPT_FLAG = DWORD($80000000);
  {$EXTERNALSYM CERT_REGISTRY_STORE_CLIENT_GPT_FLAG}
  CERT_REGISTRY_STORE_LM_GPT_FLAG     = $01000000;
  {$EXTERNALSYM CERT_REGISTRY_STORE_LM_GPT_FLAG}

type
  PCERT_REGISTRY_STORE_CLIENT_GPT_PARA = ^CERT_REGISTRY_STORE_CLIENT_GPT_PARA;
  {$EXTERNALSYM PCERT_REGISTRY_STORE_CLIENT_GPT_PARA}
  _CERT_REGISTRY_STORE_CLIENT_GPT_PARA = record
    hKeyBase: HKEY;
    pwszRegPath: LPWSTR;
  end;
  {$EXTERNALSYM _CERT_REGISTRY_STORE_CLIENT_GPT_PARA}
  CERT_REGISTRY_STORE_CLIENT_GPT_PARA = _CERT_REGISTRY_STORE_CLIENT_GPT_PARA;
  {$EXTERNALSYM CERT_REGISTRY_STORE_CLIENT_GPT_PARA}
  TCertRegistryStoreClientGptPara = CERT_REGISTRY_STORE_CLIENT_GPT_PARA;
  PCertRegistryStoreClientGptPara = PCERT_REGISTRY_STORE_CLIENT_GPT_PARA;

// The following flag is for internal use. When set, the contexts are
// persisted into roaming files instead of the registry. Such as, the
// CurrentUser "My" store. When this flag is set, the following data structure
// is passed to CertOpenStore instead of HKEY.

const
  CERT_REGISTRY_STORE_ROAMING_FLAG = $40000;
  {$EXTERNALSYM CERT_REGISTRY_STORE_ROAMING_FLAG}

// hKey may be NULL or non-NULL. When non-NULL, existing contexts are
// moved from the registry to roaming files.

type
  PCERT_REGISTRY_STORE_ROAMING_PARA = ^CERT_REGISTRY_STORE_ROAMING_PARA;
  {$EXTERNALSYM PCERT_REGISTRY_STORE_ROAMING_PARA}
  _CERT_REGISTRY_STORE_ROAMING_PARA = record
    hKey: HKEY;
    pwszStoreDirectory: LPWSTR;
  end;
  {$EXTERNALSYM _CERT_REGISTRY_STORE_ROAMING_PARA}
  CERT_REGISTRY_STORE_ROAMING_PARA = _CERT_REGISTRY_STORE_ROAMING_PARA;
  {$EXTERNALSYM CERT_REGISTRY_STORE_ROAMING_PARA}
  TCertRegistryStoreRoamingPara = CERT_REGISTRY_STORE_ROAMING_PARA;
  PCertRegistryStoreRoamingPara = PCERT_REGISTRY_STORE_ROAMING_PARA;

// The following flag is for internal use. When set, the "My" DWORD value
// at HKLM\Software\Microsoft\Cryptography\IEDirtyFlags is set to 0x1
// whenever a certificate is added to the registry store.

const
  CERT_REGISTRY_STORE_MY_IE_DIRTY_FLAG = $80000;
  {$EXTERNALSYM CERT_REGISTRY_STORE_MY_IE_DIRTY_FLAG}

// Registry path to the subkey containing the "My" DWORD value to be set

  CERT_IE_DIRTY_FLAGS_REGPATH = 'Software\Microsoft\Cryptography\IEDirtyFlags';
  {$EXTERNALSYM CERT_IE_DIRTY_FLAGS_REGPATH}

//+-------------------------------------------------------------------------
//  Certificate File Store Flag Values for the providers:
//      CERT_STORE_PROV_FILE
//      CERT_STORE_PROV_FILENAME
//      CERT_STORE_PROV_FILENAME_A
//      CERT_STORE_PROV_FILENAME_W
//      sz_CERT_STORE_PROV_FILENAME_W
//--------------------------------------------------------------------------

// Set this flag if any store changes are to be committed to the file.
// The changes are committed at CertCloseStore or by calling
// CertControlStore(CERT_STORE_CTRL_COMMIT).
//
// The open fails with E_INVALIDARG if both CERT_FILE_STORE_COMMIT_ENABLE_FLAG
// and CERT_STORE_READONLY_FLAG are set in dwFlags.
//
// For the FILENAME providers:  if the file contains an X509 encoded
// certificate, the open fails with ERROR_ACCESS_DENIED.
//
// For the FILENAME providers: if CERT_STORE_CREATE_NEW_FLAG is set, the
// CreateFile uses CREATE_NEW. If CERT_STORE_OPEN_EXISTING is set, uses
// OPEN_EXISTING. Otherwise, defaults to OPEN_ALWAYS.
//
// For the FILENAME providers:  the file is committed as either a PKCS7 or
// serialized store depending on the type read at open. However, if the
// file is empty then, if the filename has either a ".p7c" or ".spc"
// extension its committed as a PKCS7. Otherwise, its committed as a
// serialized store.
//
// For CERT_STORE_PROV_FILE, the file handle is duplicated. Its always
// committed as a serialized store.
//

  CERT_FILE_STORE_COMMIT_ENABLE_FLAG = $10000;
  {$EXTERNALSYM CERT_FILE_STORE_COMMIT_ENABLE_FLAG}

//+-------------------------------------------------------------------------
//  Open the cert store using the specified store provider.
//
//  If CERT_STORE_DELETE_FLAG is set, then, the store is deleted. NULL is
//  returned for both success and failure. However, GetLastError() returns 0
//  for success and nonzero for failure.
//
//  If CERT_STORE_SET_LOCALIZED_NAME_FLAG is set, then, if supported, the
//  provider sets the store's CERT_STORE_LOCALIZED_NAME_PROP_ID property.
//  The store's localized name can be retrieved by calling
//  CertSetStoreProperty(dwPropID = CERT_STORE_LOCALIZED_NAME_PROP_ID).
//  This flag is supported by the following providers (and their sz_
//  equivalent):
//      CERT_STORE_PROV_FILENAME_A
//      CERT_STORE_PROV_FILENAME_W
//      CERT_STORE_PROV_SYSTEM_A
//      CERT_STORE_PROV_SYSTEM_W
//      CERT_STORE_PROV_SYSTEM_REGISTRY_A
//      CERT_STORE_PROV_SYSTEM_REGISTRY_W
//      CERT_STORE_PROV_PHYSICAL_W
//
//  If CERT_STORE_DEFER_CLOSE_UNTIL_LAST_FREE_FLAG is set, then, the
//  closing of the store's provider is deferred until all certificate,
//  CRL and CTL contexts obtained from the store are freed. Also,
//  if a non NULL HCRYPTPROV was passed, then, it will continue to be used.
//  By default, the store's provider is closed on the final CertCloseStore.
//  If this flag isn't set, then, any property changes made to previously
//  duplicated contexts after the final CertCloseStore will not be persisted.
//  By setting this flag, property changes made
//  after the CertCloseStore will be persisted. Note, setting this flag
//  causes extra overhead in doing context duplicates and frees.
//  If CertCloseStore is called with CERT_CLOSE_STORE_FORCE_FLAG, then,
//  the CERT_STORE_DEFER_CLOSE_UNTIL_LAST_FREE_FLAG flag is ignored.
//
//  CERT_STORE_MANIFOLD_FLAG can be set to check for certificates having the
//  manifold extension and archive the "older" certificates with the same
//  manifold extension value. A certificate is archived by setting the
//  CERT_ARCHIVED_PROP_ID.
//
//  By default, contexts having the CERT_ARCHIVED_PROP_ID, are skipped
//  during enumeration. CERT_STORE_ENUM_ARCHIVED_FLAG can be set to include
//  archived contexts when enumerating. Note, contexts having the
//  CERT_ARCHIVED_PROP_ID are still found for explicit finds, such as,
//  finding a context with a specific hash or finding a certificate having
//  a specific issuer and serial number.
//
//  CERT_STORE_UPDATE_KEYID_FLAG can be set to also update the Key Identifier's
//  CERT_KEY_PROV_INFO_PROP_ID property whenever a certificate's
//  CERT_KEY_IDENTIFIER_PROP_ID or CERT_KEY_PROV_INFO_PROP_ID property is set
//  and the other property already exists. If the Key Identifier's
//  CERT_KEY_PROV_INFO_PROP_ID already exists, it isn't updated. Any
//  errors encountered are silently ignored.
//
//  By default, this flag is implicitly set for the "My\.Default" CurrentUser
//  and LocalMachine physical stores.
//
//  CERT_STORE_READONLY_FLAG can be set to open the store as read only.
//  Otherwise, the store is opened as read/write.
//
//  CERT_STORE_OPEN_EXISTING_FLAG can be set to only open an existing
//  store. CERT_STORE_CREATE_NEW_FLAG can be set to create a new store and
//  fail if the store already exists. Otherwise, the default is to open
//  an existing store or create a new store if it doesn't already exist.
//
//  hCryptProv specifies the crypto provider to use to create the hash
//  properties or verify the signature of a subject certificate or CRL.
//  The store doesn't need to use a private
//  key. If the CERT_STORE_NO_CRYPT_RELEASE_FLAG isn't set, hCryptProv is
//  CryptReleaseContext'ed on the final CertCloseStore.
//
//  Note, if the open fails, hCryptProv is released if it would have been
//  released when the store was closed.
//
//  If hCryptProv is zero, then, the default provider and container for the
//  PROV_RSA_FULL provider type is CryptAcquireContext'ed with
//  CRYPT_VERIFYCONTEXT access. The CryptAcquireContext is deferred until
//  the first create hash or verify signature. In addition, once acquired,
//  the default provider isn't released until process exit when crypt32.dll
//  is unloaded. The acquired default provider is shared across all stores
//  and threads.
//
//  After initializing the store's data structures and optionally acquiring a
//  default crypt provider, CertOpenStore calls CryptGetOIDFunctionAddress to
//  get the address of the CRYPT_OID_OPEN_STORE_PROV_FUNC specified by
//  lpszStoreProvider. Since a store can contain certificates with different
//  encoding types, CryptGetOIDFunctionAddress is called with dwEncodingType
//  set to 0 and not the dwEncodingType passed to CertOpenStore.
//  PFN_CERT_DLL_OPEN_STORE_FUNC specifies the signature of the provider's
//  open function. This provider open function is called to load the
//  store's certificates and CRLs. Optionally, the provider may return an
//  array of functions called before a certificate or CRL is added or deleted
//  or has a property that is set.
//
//  Use of the dwEncodingType parameter is provider dependent. The type
//  definition for pvPara also depends on the provider.
//
//  Store providers are installed or registered via
//  CryptInstallOIDFunctionAddress or CryptRegisterOIDFunction, where,
//  dwEncodingType is 0 and pszFuncName is CRYPT_OID_OPEN_STORE_PROV_FUNC.
//
//  Here's a list of the predefined provider types (implemented in crypt32.dll):
//
//  CERT_STORE_PROV_MSG:
//      Gets the certificates and CRLs from the specified cryptographic message.
//      dwEncodingType contains the message and certificate encoding types.
//      The message's handle is passed in pvPara. Given,
//          HCRYPTMSG hCryptMsg; pvPara = (const void *) hCryptMsg;
//
//  CERT_STORE_PROV_MEMORY
//  sz_CERT_STORE_PROV_MEMORY:
//      Opens a store without any initial certificates or CRLs. pvPara
//      isn't used.
//
//  CERT_STORE_PROV_FILE:
//      Reads the certificates and CRLs from the specified file. The file's
//      handle is passed in pvPara. Given,
//          HANDLE hFile; pvPara = (const void *) hFile;
//
//      For a successful open, the file pointer is advanced past
//      the certificates and CRLs and their properties read from the file.
//      Note, only expects a serialized store and not a file containing
//      either a PKCS #7 signed message or a single encoded certificate.
//
//      The hFile isn't closed.
//
//  CERT_STORE_PROV_REG:
//      Reads the certificates and CRLs from the registry. The registry's
//      key handle is passed in pvPara. Given,
//          HKEY hKey; pvPara = (const void *) hKey;
//
//      The input hKey isn't closed by the provider. Before returning, the
//      provider opens it own copy of the hKey.
//
//      If CERT_STORE_READONLY_FLAG is set, then, the registry subkeys are
//      RegOpenKey'ed with KEY_READ_ACCESS. Otherwise, the registry subkeys
//      are RegCreateKey'ed with KEY_ALL_ACCESS.
//
//      This provider returns the array of functions for reading, writing,
//      deleting and property setting certificates and CRLs.
//      Any changes to the opened store are immediately pushed through to
//      the registry. However, if CERT_STORE_READONLY_FLAG is set, then,
//      writing, deleting or property setting results in a
//      SetLastError(E_ACCESSDENIED).
//
//      Note, all the certificates and CRLs are read from the registry
//      when the store is opened. The opened store serves as a write through
//      cache.
//
//      If CERT_REGISTRY_STORE_SERIALIZED_FLAG is set, then, the
//      contexts are persisted as a single serialized store subkey in the
//      registry.
//
//  CERT_STORE_PROV_PKCS7:
//  sz_CERT_STORE_PROV_PKCS7:
//      Gets the certificates and CRLs from the encoded PKCS #7 signed message.
//      dwEncodingType specifies the message and certificate encoding types.
//      The pointer to the encoded message's blob is passed in pvPara. Given,
//          CRYPT_DATA_BLOB EncodedMsg; pvPara = (const void *) &EncodedMsg;
//
//      Note, also supports the IE3.0 special version of a
//      PKCS #7 signed message referred to as a "SPC" formatted message.
//
//  CERT_STORE_PROV_SERIALIZED:
//  sz_CERT_STORE_PROV_SERIALIZED:
//      Gets the certificates and CRLs from memory containing a serialized
//      store.  The pointer to the serialized memory blob is passed in pvPara.
//      Given,
//          CRYPT_DATA_BLOB Serialized; pvPara = (const void *) &Serialized;
//
//  CERT_STORE_PROV_FILENAME_A:
//  CERT_STORE_PROV_FILENAME_W:
//  CERT_STORE_PROV_FILENAME:
//  sz_CERT_STORE_PROV_FILENAME_W:
//  sz_CERT_STORE_PROV_FILENAME:
//      Opens the file and first attempts to read as a serialized store. Then,
//      as a PKCS #7 signed message. Finally, as a single encoded certificate.
//      The filename is passed in pvPara. The filename is UNICODE for the
//      "_W" provider and ASCII for the "_A" provider. For "_W": given,
//          LPCWSTR pwszFilename; pvPara = (const void *) pwszFilename;
//      For "_A": given,
//          LPCSTR pszFilename; pvPara = (const void *) pszFilename;
//
//      Note, the default (without "_A" or "_W") is unicode.
//
//      Note, also supports the reading of the IE3.0 special version of a
//      PKCS #7 signed message file referred to as a "SPC" formatted file.
//
//  CERT_STORE_PROV_SYSTEM_A:
//  CERT_STORE_PROV_SYSTEM_W:
//  CERT_STORE_PROV_SYSTEM:
//  sz_CERT_STORE_PROV_SYSTEM_W:
//  sz_CERT_STORE_PROV_SYSTEM:
//      Opens the specified logical "System" store. The upper word of the
//      dwFlags parameter is used to specify the location of the system store.
//
//      A "System" store is a collection consisting of one or more "Physical"
//      stores. A "Physical" store is registered via the
//      CertRegisterPhysicalStore API. Each of the registered physical stores
//      is CertStoreOpen'ed and added to the collection via
//      CertAddStoreToCollection.
//
//      The CERT_SYSTEM_STORE_CURRENT_USER, CERT_SYSTEM_STORE_LOCAL_MACHINE,
//      CERT_SYSTEM_STORE_CURRENT_SERVICE, CERT_SYSTEM_STORE_SERVICES,
//      CERT_SYSTEM_STORE_USERS, CERT_SYSTEM_STORE_CURRENT_USER_GROUP_POLICY,
//      CERT_SYSTEM_STORE_LOCAL_MACHINE_GROUP_POLICY and
//      CERT_SYSTEM_STORE_LOCAL_MACHINE_ENTERPRSE
//      system stores by default have a "SystemRegistry" store that is
//      opened and added to the collection.
//
//      The system store name is passed in pvPara. The name is UNICODE for the
//      "_W" provider and ASCII for the "_A" provider. For "_W": given,
//          LPCWSTR pwszSystemName; pvPara = (const void *) pwszSystemName;
//      For "_A": given,
//          LPCSTR pszSystemName; pvPara = (const void *) pszSystemName;
//
//      Note, the default (without "_A" or "_W") is UNICODE.
//
//      The system store name can't contain any backslashes.
//
//      If CERT_SYSTEM_STORE_RELOCATE_FLAG is set in dwFlags, pvPara
//      points to a CERT_SYSTEM_STORE_RELOCATE_PARA data structure instead
//      of pointing to a null terminated UNICODE or ASCII string.
//      Sibling physical stores are also opened as relocated using
//      pvPara's hKeyBase.
//
//      The CERT_SYSTEM_STORE_SERVICES or CERT_SYSTEM_STORE_USERS system
//      store name must be prefixed with the ServiceName or UserName.
//      For example, "ServiceName\Trust".
//
//      Stores on remote computers can be accessed for the
//      CERT_SYSTEM_STORE_LOCAL_MACHINE, CERT_SYSTEM_STORE_SERVICES,
//      CERT_SYSTEM_STORE_USERS, CERT_SYSTEM_STORE_LOCAL_MACHINE_GROUP_POLICY
//      or CERT_SYSTEM_STORE_LOCAL_MACHINE_ENTERPRISE
//      locations by prepending the computer name. For example, a remote
//      local machine store is accessed via "\\ComputerName\Trust" or
//      "ComputerName\Trust". A remote service store is accessed via
//      "\\ComputerName\ServiceName\Trust". The leading "\\" backslashes are
//      optional in the ComputerName.
//
//      If CERT_STORE_READONLY_FLAG is set, then, the registry is
//      RegOpenKey'ed with KEY_READ_ACCESS. Otherwise, the registry is
//      RegCreateKey'ed with KEY_ALL_ACCESS.
//
//      The "root" store is treated differently from the other system
//      stores. Before a certificate is added to or deleted from the "root"
//      store, a pop up message box is displayed. The certificate's subject,
//      issuer, serial number, time validity, sha1 and md5 thumbprints are
//      displayed. The user is given the option to do the add or delete.
//      If they don't allow the operation, LastError is set to E_ACCESSDENIED.
//
//  CERT_STORE_PROV_SYSTEM_REGISTRY_A
//  CERT_STORE_PROV_SYSTEM_REGISTRY_W
//  CERT_STORE_PROV_SYSTEM_REGISTRY
//  sz_CERT_STORE_PROV_SYSTEM_REGISTRY_W
//  sz_CERT_STORE_PROV_SYSTEM_REGISTRY
//      Opens the "System" store's default "Physical" store residing in the
//      registry. The upper word of the dwFlags
//      parameter is used to specify the location of the system store.
//
//      After opening the registry key associated with the system name,
//      the CERT_STORE_PROV_REG provider is called to complete the open.
//
//      The system store name is passed in pvPara. The name is UNICODE for the
//      "_W" provider and ASCII for the "_A" provider. For "_W": given,
//          LPCWSTR pwszSystemName; pvPara = (const void *) pwszSystemName;
//      For "_A": given,
//          LPCSTR pszSystemName; pvPara = (const void *) pszSystemName;
//
//      Note, the default (without "_A" or "_W") is UNICODE.
//
//      If CERT_SYSTEM_STORE_RELOCATE_FLAG is set in dwFlags, pvPara
//      points to a CERT_SYSTEM_STORE_RELOCATE_PARA data structure instead
//      of pointing to a null terminated UNICODE or ASCII string.
//
//      See above for details on prepending a ServiceName and/or ComputerName
//      to the store name.
//
//      If CERT_STORE_READONLY_FLAG is set, then, the registry is
//      RegOpenKey'ed with KEY_READ_ACCESS. Otherwise, the registry is
//      RegCreateKey'ed with KEY_ALL_ACCESS.
//
//      The "root" store is treated differently from the other system
//      stores. Before a certificate is added to or deleted from the "root"
//      store, a pop up message box is displayed. The certificate's subject,
//      issuer, serial number, time validity, sha1 and md5 thumbprints are
//      displayed. The user is given the option to do the add or delete.
//      If they don't allow the operation, LastError is set to E_ACCESSDENIED.
//
//  CERT_STORE_PROV_PHYSICAL_W
//  CERT_STORE_PROV_PHYSICAL
//  sz_CERT_STORE_PROV_PHYSICAL_W
//  sz_CERT_STORE_PROV_PHYSICAL
//      Opens the specified "Physical" store in the "System" store.
//
//      Both the system store and physical names are passed in pvPara. The
//      names are separated with an intervening "\". For example,
//      "Root\.Default". The string is UNICODE.
//
//      The system and physical store names can't contain any backslashes.
//
//      If CERT_SYSTEM_STORE_RELOCATE_FLAG is set in dwFlags, pvPara
//      points to a CERT_SYSTEM_STORE_RELOCATE_PARA data structure instead
//      of pointing to a null terminated UNICODE string.
//      The specified physical store is opened as relocated using pvPara's
//      hKeyBase.
//
//      For CERT_SYSTEM_STORE_SERVICES or CERT_SYSTEM_STORE_USERS,
//      the system and physical store names
//      must be prefixed with the ServiceName or UserName. For example,
//      "ServiceName\Root\.Default".
//
//      Physical stores on remote computers can be accessed for the
//      CERT_SYSTEM_STORE_LOCAL_MACHINE, CERT_SYSTEM_STORE_SERVICES,
//      CERT_SYSTEM_STORE_USERS, CERT_SYSTEM_STORE_LOCAL_MACHINE_GROUP_POLICY
//      or CERT_SYSTEM_STORE_LOCAL_MACHINE_ENTERPRISE
//      locations by prepending the computer name. For example, a remote
//      local machine store is accessed via "\\ComputerName\Root\.Default"
//      or "ComputerName\Root\.Default". A remote service store is
//      accessed via "\\ComputerName\ServiceName\Root\.Default". The
//      leading "\\" backslashes are optional in the ComputerName.
//
//  CERT_STORE_PROV_COLLECTION
//  sz_CERT_STORE_PROV_COLLECTION
//      Opens a store that is a collection of other stores. Stores are
//      added or removed to/from the collection via the CertAddStoreToCollection
//      and CertRemoveStoreFromCollection APIs.
//
//  CERT_STORE_PROV_SMART_CARD_W
//  CERT_STORE_PROV_SMART_CARD
//  sz_CERT_STORE_PROV_SMART_CARD_W
//  sz_CERT_STORE_PROV_SMART_CARD
//      Opens a store instantiated over a particular smart card storage.  pvPara
//      identifies where on the card the store is located and is of the
//      following format:
//
//                Card Name\Provider Name\Provider Type[\Container Name]
//
//      Container Name is optional and if NOT specified the Card Name is used
//      as the Container Name.  Future versions of the provider will support
//      instantiating the store over the entire card in which case just
//      Card Name ( or id ) will be sufficient.
//
//  Here's a list of the predefined provider types (implemented in
//  cryptnet.dll):
//
//  CERT_STORE_PROV_LDAP_W
//  CERT_STORE_PROV_LDAP
//  sz_CERT_STORE_PROV_LDAP_W
//  sz_CERT_STORE_PROV_LDAP
//      Opens a store over the results of the query specified by and LDAP
//      URL which is passed in via pvPara.  In order to do writes to the
//      store the URL must specify a BASE query, no filter and a single
//      attribute.
//
//--------------------------------------------------------------------------

function CertOpenStore(lpszStoreProvider: LPCSTR; dwEncodingType: DWORD;
  hCryptProv: HCRYPTPROV; dwFlags: DWORD; pvPara: Pointer): HCERTSTORE; stdcall;
{$EXTERNALSYM CertOpenStore}

//+-------------------------------------------------------------------------
//  OID Installable Certificate Store Provider Data Structures
//--------------------------------------------------------------------------

// Handle returned by the store provider when opened.

type
  HCERTSTOREPROV = Pointer;
  {$EXTERNALSYM HCERTSTOREPROV}

// Store Provider OID function's pszFuncName.

const
  CRYPT_OID_OPEN_STORE_PROV_FUNC = 'CertDllOpenStoreProv';
  {$EXTERNALSYM CRYPT_OID_OPEN_STORE_PROV_FUNC}

// Note, the Store Provider OID function's dwEncodingType is always 0.

// The following information is returned by the provider when opened. Its
// zeroed with cbSize set before the provider is called. If the provider
// doesn't need to be called again after the open it doesn't need to
// make any updates to the CERT_STORE_PROV_INFO.

type
  PCERT_STORE_PROV_INFO = ^CERT_STORE_PROV_INFO;
  {$EXTERNALSYM PCERT_STORE_PROV_INFO}
  _CERT_STORE_PROV_INFO = record
    cbSize: DWORD;
    cStoreProvFunc: DWORD;
    rgpvStoreProvFunc: Pointer;
    hStoreProv: HCERTSTOREPROV;
    dwStoreProvFlags: DWORD;
    hStoreProvFuncAddr2: HCRYPTOIDFUNCADDR;
  end;
  {$EXTERNALSYM _CERT_STORE_PROV_INFO}
  CERT_STORE_PROV_INFO = _CERT_STORE_PROV_INFO;
  {$EXTERNALSYM CERT_STORE_PROV_INFO}
  TCertStoreProvInfo = CERT_STORE_PROV_INFO;
  PCertStoreProvInfo = PCERT_STORE_PROV_INFO;

// Definition of the store provider's open function.
//
// *pStoreProvInfo has been zeroed before the call.
//
// Note, pStoreProvInfo->cStoreProvFunc should be set last.  Once set,
// all subsequent store calls, such as CertAddSerializedElementToStore will
// call the appropriate provider callback function.

type
  PFN_CERT_DLL_OPEN_STORE_PROV_FUNC = function (
    lpszStoreProvider: LPCSTR;
    dwEncodingType: DWORD;
    hCryptProv: HCRYPTPROV;
    dwFlags: DWORD;
    pvPara: Pointer;
    hCertStore: HCERTSTORE;
    var pStoreProvInfo: PCERT_STORE_PROV_INFO): BOOL; stdcall;
  {$EXTERNALSYM PFN_CERT_DLL_OPEN_STORE_PROV_FUNC}
  PFnCertDllOpenStoreProvFunc = PFN_CERT_DLL_OPEN_STORE_PROV_FUNC;

// The open callback sets the following flag, if it maintains its
// contexts externally and not in the cached store.

const
  CERT_STORE_PROV_EXTERNAL_FLAG = $1;
  {$EXTERNALSYM CERT_STORE_PROV_EXTERNAL_FLAG}

// The open callback sets the following flag for a successful delete.
// When set, the close callback isn't called.

  CERT_STORE_PROV_DELETED_FLAG = $2;
  {$EXTERNALSYM CERT_STORE_PROV_DELETED_FLAG}

// The open callback sets the following flag if it doesn't persist store
// changes.

  CERT_STORE_PROV_NO_PERSIST_FLAG = $4;
  {$EXTERNALSYM CERT_STORE_PROV_NO_PERSIST_FLAG}

// The open callback sets the following flag if the contexts are persisted
// to a system store.

  CERT_STORE_PROV_SYSTEM_STORE_FLAG = $8;
  {$EXTERNALSYM CERT_STORE_PROV_SYSTEM_STORE_FLAG}

// Indices into the store provider's array of callback functions.
//
// The provider can implement any subset of the following functions. It
// sets pStoreProvInfo->cStoreProvFunc to the last index + 1 and any
// preceding not implemented functions to NULL.

  CERT_STORE_PROV_CLOSE_FUNC             = 0;
  {$EXTERNALSYM CERT_STORE_PROV_CLOSE_FUNC}
  CERT_STORE_PROV_READ_CERT_FUNC         = 1;
  {$EXTERNALSYM CERT_STORE_PROV_READ_CERT_FUNC}
  CERT_STORE_PROV_WRITE_CERT_FUNC        = 2;
  {$EXTERNALSYM CERT_STORE_PROV_WRITE_CERT_FUNC}
  CERT_STORE_PROV_DELETE_CERT_FUNC       = 3;
  {$EXTERNALSYM CERT_STORE_PROV_DELETE_CERT_FUNC}
  CERT_STORE_PROV_SET_CERT_PROPERTY_FUNC = 4;
  {$EXTERNALSYM CERT_STORE_PROV_SET_CERT_PROPERTY_FUNC}
  CERT_STORE_PROV_READ_CRL_FUNC          = 5;
  {$EXTERNALSYM CERT_STORE_PROV_READ_CRL_FUNC}
  CERT_STORE_PROV_WRITE_CRL_FUNC         = 6;
  {$EXTERNALSYM CERT_STORE_PROV_WRITE_CRL_FUNC}
  CERT_STORE_PROV_DELETE_CRL_FUNC        = 7;
  {$EXTERNALSYM CERT_STORE_PROV_DELETE_CRL_FUNC}
  CERT_STORE_PROV_SET_CRL_PROPERTY_FUNC  = 8;
  {$EXTERNALSYM CERT_STORE_PROV_SET_CRL_PROPERTY_FUNC}
  CERT_STORE_PROV_READ_CTL_FUNC          = 9;
  {$EXTERNALSYM CERT_STORE_PROV_READ_CTL_FUNC}
  CERT_STORE_PROV_WRITE_CTL_FUNC         = 10;
  {$EXTERNALSYM CERT_STORE_PROV_WRITE_CTL_FUNC}
  CERT_STORE_PROV_DELETE_CTL_FUNC        = 11;
  {$EXTERNALSYM CERT_STORE_PROV_DELETE_CTL_FUNC}
  CERT_STORE_PROV_SET_CTL_PROPERTY_FUNC  = 12;
  {$EXTERNALSYM CERT_STORE_PROV_SET_CTL_PROPERTY_FUNC}
  CERT_STORE_PROV_CONTROL_FUNC           = 13;
  {$EXTERNALSYM CERT_STORE_PROV_CONTROL_FUNC}
  CERT_STORE_PROV_FIND_CERT_FUNC         = 14;
  {$EXTERNALSYM CERT_STORE_PROV_FIND_CERT_FUNC}
  CERT_STORE_PROV_FREE_FIND_CERT_FUNC    = 15;
  {$EXTERNALSYM CERT_STORE_PROV_FREE_FIND_CERT_FUNC}
  CERT_STORE_PROV_GET_CERT_PROPERTY_FUNC = 16;
  {$EXTERNALSYM CERT_STORE_PROV_GET_CERT_PROPERTY_FUNC}
  CERT_STORE_PROV_FIND_CRL_FUNC          = 17;
  {$EXTERNALSYM CERT_STORE_PROV_FIND_CRL_FUNC}
  CERT_STORE_PROV_FREE_FIND_CRL_FUNC     = 18;
  {$EXTERNALSYM CERT_STORE_PROV_FREE_FIND_CRL_FUNC}
  CERT_STORE_PROV_GET_CRL_PROPERTY_FUNC  = 19;
  {$EXTERNALSYM CERT_STORE_PROV_GET_CRL_PROPERTY_FUNC}
  CERT_STORE_PROV_FIND_CTL_FUNC          = 20;
  {$EXTERNALSYM CERT_STORE_PROV_FIND_CTL_FUNC}
  CERT_STORE_PROV_FREE_FIND_CTL_FUNC     = 21;
  {$EXTERNALSYM CERT_STORE_PROV_FREE_FIND_CTL_FUNC}
  CERT_STORE_PROV_GET_CTL_PROPERTY_FUNC  = 22;
  {$EXTERNALSYM CERT_STORE_PROV_GET_CTL_PROPERTY_FUNC}

// Called by CertCloseStore when the store's reference count is
// decremented to 0.

type
  PFN_CERT_STORE_PROV_CLOSE = procedure (hStoreProv: HCERTSTOREPROV; dwFlags: DWORD); stdcall;
  {$EXTERNALSYM PFN_CERT_STORE_PROV_CLOSE}
  PFnCertStoreProvClose = PFN_CERT_STORE_PROV_CLOSE;

// Currently not called directly by the store APIs. However, may be exported
// to support other providers based on it.
//
// Reads the provider's copy of the certificate context. If it exists,
// creates a new certificate context.

  PFN_CERT_STORE_PROV_READ_CERT = function (hStoreProv: HCERTSTOREPROV;
    pStoreCertContext: PCCERT_CONTEXT; dwFlags: DWORD;
    var ppProvCertContext: PCCERT_CONTEXT): BOOL; stdcall;
  {$EXTERNALSYM PFN_CERT_STORE_PROV_READ_CERT}
  PfnCertStoreProvReadCert = PFN_CERT_STORE_PROV_READ_CERT;

const
  CERT_STORE_PROV_WRITE_ADD_FLAG = $1;
  {$EXTERNALSYM CERT_STORE_PROV_WRITE_ADD_FLAG}

// Called by CertAddEncodedCertificateToStore,
// CertAddCertificateContextToStore or CertAddSerializedElementToStore before
// adding to the store. The CERT_STORE_PROV_WRITE_ADD_FLAG is set. In
// addition to the encoded certificate, the added pCertContext might also
// have properties.
//
// Returns TRUE if its OK to update the the store.

type
  PFN_CERT_STORE_PROV_WRITE_CERT = function (hStoreProv: HCERTSTOREPROV;
    pCertContext: PCCERT_CONTEXT; dwFlags: DWORD): BOOL; stdcall;
  {$EXTERNALSYM PFN_CERT_STORE_PROV_WRITE_CERT}
  PfnCertStoreProvWriteCert = PFN_CERT_STORE_PROV_WRITE_CERT;

// Called by CertDeleteCertificateFromStore before deleting from the
// store.
//
// Returns TRUE if its OK to delete from the store.

  PFN_CERT_STORE_PROV_DELETE_CERT = function (hStoreProv: HCERTSTOREPROV;
    pCertContext: PCCERT_CONTEXT; dwFlags: DWORD): BOOL; stdcall;
  {$EXTERNALSYM PFN_CERT_STORE_PROV_DELETE_CERT}
  PfnCertStoreProvDeleteCert = PFN_CERT_STORE_PROV_DELETE_CERT;

// Called by CertSetCertificateContextProperty before setting the
// certificate's property. Also called by CertGetCertificateContextProperty,
// when getting a hash property that needs to be created and then persisted
// via the set.
//
// Upon input, the property hasn't been set for the pCertContext parameter.
//
// Returns TRUE if its OK to set the property.

type
  PFN_CERT_STORE_PROV_SET_CERT_PROPERTY = function (hStoreProv: HCERTSTOREPROV;
    pCertContext: PCCERT_CONTEXT; dwPropId: DWORD; dwFlags: DWORD;
    pvData: Pointer): BOOL; stdcall;
  {$EXTERNALSYM PFN_CERT_STORE_PROV_SET_CERT_PROPERTY}
  PfnCertStoreProvSetCertProperty = PFN_CERT_STORE_PROV_SET_CERT_PROPERTY;

// Currently not called directly by the store APIs. However, may be exported
// to support other providers based on it.
//
// Reads the provider's copy of the CRL context. If it exists,
// creates a new CRL context.

  PFN_CERT_STORE_PROV_READ_CRL = function (hStoreProv: HCERTSTOREPROV;
    pStoreCrlContext: PCCRL_CONTEXT; dwFlags: DWORD;
    var ppProvCrlContext: PCCRL_CONTEXT): BOOL; stdcall;
  {$EXTERNALSYM PFN_CERT_STORE_PROV_READ_CRL}
  PfnCertStoreProvReadCrl = PFN_CERT_STORE_PROV_READ_CRL;

// Called by CertAddEncodedCRLToStore,
// CertAddCRLContextToStore or CertAddSerializedElementToStore before
// adding to the store. The CERT_STORE_PROV_WRITE_ADD_FLAG is set. In
// addition to the encoded CRL, the added pCertContext might also
// have properties.
//
// Returns TRUE if its OK to update the the store.

  PFN_CERT_STORE_PROV_WRITE_CRL = function (hStoreProv: HCERTSTOREPROV;
    pCrlContext: PCCRL_CONTEXT; dwFlags: DWORD): BOOL; stdcall;
  {$EXTERNALSYM PFN_CERT_STORE_PROV_WRITE_CRL}
  PfnCertStoreProvWriteCrl = PFN_CERT_STORE_PROV_WRITE_CRL;

// Called by CertDeleteCRLFromStore before deleting from the store.
//
// Returns TRUE if its OK to delete from the store.

  PFN_CERT_STORE_PROV_DELETE_CRL = function (hStoreProv: HCERTSTOREPROV;
    pCrlContext: PCCRL_CONTEXT; dwFlags: DWORD): BOOL; stdcall;
  {$EXTERNALSYM PFN_CERT_STORE_PROV_DELETE_CRL}
  PfnCertStoreProvDeleteCrl = PFN_CERT_STORE_PROV_DELETE_CRL;

// Called by CertSetCRLContextProperty before setting the
// CRL's property. Also called by CertGetCRLContextProperty,
// when getting a hash property that needs to be created and then persisted
// via the set.
//
// Upon input, the property hasn't been set for the pCrlContext parameter.
//
// Returns TRUE if its OK to set the property.

  PFN_CERT_STORE_PROV_SET_CRL_PROPERTY = function (hStoreProv: HCERTSTOREPROV;
    pCrlContext: PCCRL_CONTEXT; dwPropId: DWORD; dwFlags: DWORD;
    pvData: Pointer): BOOL; stdcall;
  {$EXTERNALSYM PFN_CERT_STORE_PROV_SET_CRL_PROPERTY}
  PfnCertStoreProvSetCrlProperty = PFN_CERT_STORE_PROV_SET_CRL_PROPERTY;

// Currently not called directly by the store APIs. However, may be exported
// to support other providers based on it.
//
// Reads the provider's copy of the CTL context. If it exists,
// creates a new CTL context.

  PFN_CERT_STORE_PROV_READ_CTL = function (hStoreProv: HCERTSTOREPROV;
    pStoreCtlContext: PCCTL_CONTEXT; dwFlags: DWORD;
    var ppProvCtlContext: PCCTL_CONTEXT): BOOL; stdcall;
  {$EXTERNALSYM PFN_CERT_STORE_PROV_READ_CTL}
  PfnCertStoreProvReadCtl = PFN_CERT_STORE_PROV_READ_CTL;

// Called by CertAddEncodedCTLToStore,
// CertAddCTLContextToStore or CertAddSerializedElementToStore before
// adding to the store. The CERT_STORE_PROV_WRITE_ADD_FLAG is set. In
// addition to the encoded CTL, the added pCertContext might also
// have properties.
//
// Returns TRUE if its OK to update the the store.

  PFN_CERT_STORE_PROV_WRITE_CTL = function (hStoreProv: HCERTSTOREPROV;
    pCtlContext: PCCTL_CONTEXT; dwFlags: DWORD): BOOL; stdcall;
  {$EXTERNALSYM PFN_CERT_STORE_PROV_WRITE_CTL}
  PfnCertStoreProvWriteCtl = PFN_CERT_STORE_PROV_WRITE_CTL;

// Called by CertDeleteCTLFromStore before deleting from the store.
//
// Returns TRUE if its OK to delete from the store.

  PFN_CERT_STORE_PROV_DELETE_CTL = function (hStoreProv: HCERTSTOREPROV;
    pCtlContext: PCCTL_CONTEXT; dwFlags: DWORD): BOOL; stdcall;
  {$EXTERNALSYM PFN_CERT_STORE_PROV_DELETE_CTL}
  PfnCertStoreProvDeleteCtl = PFN_CERT_STORE_PROV_DELETE_CTL;

// Called by CertSetCTLContextProperty before setting the
// CTL's property. Also called by CertGetCTLContextProperty,
// when getting a hash property that needs to be created and then persisted
// via the set.
//
// Upon input, the property hasn't been set for the pCtlContext parameter.
//
// Returns TRUE if its OK to set the property.

  PFN_CERT_STORE_PROV_SET_CTL_PROPERTY = function (hStoreProv: HCERTSTOREPROV;
    pCtlContext: PCCTL_CONTEXT; dwPropId, dwFlags: DWORD;  pvData: Pointer): BOOL; stdcall;
  {$EXTERNALSYM PFN_CERT_STORE_PROV_SET_CTL_PROPERTY}
  PfnCertStoreProvSetCtlProperty = PFN_CERT_STORE_PROV_SET_CTL_PROPERTY;

  PFN_CERT_STORE_PROV_CONTROL = function (hStoreProv: HCERTSTOREPROV;
    dwFlags: DWORD; dwCtrlType: DWORD; pvCtrlPara: Pointer): BOOL; stdcall;
  {$EXTERNALSYM PFN_CERT_STORE_PROV_CONTROL}
  PfnCertStoreProvControl = PFN_CERT_STORE_PROV_CONTROL;

  PCERT_STORE_PROV_FIND_INFO = ^CERT_STORE_PROV_FIND_INFO;
  {$EXTERNALSYM PCERT_STORE_PROV_FIND_INFO}
  _CERT_STORE_PROV_FIND_INFO = record
    cbSize: DWORD;
    dwMsgAndCertEncodingType: DWORD;
    dwFindFlags: DWORD;
    dwFindType: DWORD;
    pvFindPara: Pointer;
  end;
  {$EXTERNALSYM _CERT_STORE_PROV_FIND_INFO}
  CERT_STORE_PROV_FIND_INFO = _CERT_STORE_PROV_FIND_INFO;
  {$EXTERNALSYM CERT_STORE_PROV_FIND_INFO}
  TCertStoreProvFindInfo = CERT_STORE_PROV_FIND_INFO;
  PCertStoreProvFindInfo = PCERT_STORE_PROV_FIND_INFO;

  CCERT_STORE_PROV_FIND_INFO = CERT_STORE_PROV_FIND_INFO;
  {$EXTERNALSYM CCERT_STORE_PROV_FIND_INFO}
  PCCERT_STORE_PROV_FIND_INFO = PCERT_STORE_PROV_FIND_INFO;
  {$EXTERNALSYM PCCERT_STORE_PROV_FIND_INFO}

  PFN_CERT_STORE_PROV_FIND_CERT = function (hStoreProv: HCERTSTOREPROV;
    pFindInfo: PCCERT_STORE_PROV_FIND_INFO; pPrevCertContext: PCCERT_CONTEXT;
    dwFlags: DWORD; var ppvStoreProvFindInfo: Pointer;
    var ppProvCertContext: PCCERT_CONTEXT): BOOL; stdcall;
  {$EXTERNALSYM PFN_CERT_STORE_PROV_FIND_CERT}
  PfnCertStoreProvFindCert = PFN_CERT_STORE_PROV_FIND_CERT;

  PFN_CERT_STORE_PROV_FREE_FIND_CERT = function (hStoreProv: HCERTSTOREPROV;
    pCertContext: PCCERT_CONTEXT; pvStoreProvFindInfo: Pointer; dwFlags: DWORD): BOOL; stdcall;
  {$EXTERNALSYM PFN_CERT_STORE_PROV_FREE_FIND_CERT}
  PfnCertStoreProvFreeFindCert = PFN_CERT_STORE_PROV_FREE_FIND_CERT;

  PFN_CERT_STORE_PROV_GET_CERT_PROPERTY = function (hStoreProv: HCERTSTOREPROV;
    pCertContext: PCCERT_CONTEXT; dwPropId: DWORD; dwFlags: DWORD; pvData: Pointer;
    var pcbData: DWORD): BOOL; stdcall;
  {$EXTERNALSYM PFN_CERT_STORE_PROV_GET_CERT_PROPERTY}
  PfnCertStoreProvGetCertProperty = PFN_CERT_STORE_PROV_GET_CERT_PROPERTY;

  PFN_CERT_STORE_PROV_FIND_CRL = function (hStoreProv: HCERTSTOREPROV;
    pFindInfo: PCCERT_STORE_PROV_FIND_INFO; pPrevCrlContext: PCCRL_CONTEXT;
    dwFlags: DWORD; var ppvStoreProvFindInfo: Pointer;
    var ppProvCrlContext: PCCRL_CONTEXT): BOOL; stdcall;
  {$EXTERNALSYM PFN_CERT_STORE_PROV_FIND_CRL}
  PfnCertStoreProvFindCrl = PFN_CERT_STORE_PROV_FIND_CRL;

  PFN_CERT_STORE_PROV_FREE_FIND_CRL = function (hStoreProv: HCERTSTOREPROV;
    pCrlContext: PCCRL_CONTEXT; pvStoreProvFindInfo: Pointer; dwFlags: DWORD): BOOL; stdcall;
  {$EXTERNALSYM PFN_CERT_STORE_PROV_FREE_FIND_CRL}
  PfnCertStoreProvFreeFindCrl = PFN_CERT_STORE_PROV_FREE_FIND_CRL;

  PFN_CERT_STORE_PROV_GET_CRL_PROPERTY = function (hStoreProv: HCERTSTOREPROV;
    pCrlContext: PCCRL_CONTEXT; dwPropId: DWORD; dwFlags: DWORD; pvData: Pointer;
    var pcbData: DWORD): BOOL; stdcall;
  {$EXTERNALSYM PFN_CERT_STORE_PROV_GET_CRL_PROPERTY}
  PfnCertStoreProvGetCrlProperty = PFN_CERT_STORE_PROV_GET_CRL_PROPERTY;

  PFN_CERT_STORE_PROV_FIND_CTL = function (hStoreProv: HCERTSTOREPROV;
    pFindInfo: PCCERT_STORE_PROV_FIND_INFO; pPrevCtlContext: PCCTL_CONTEXT;
    dwFlags: DWORD; var ppvStoreProvFindInfo: Pointer;
    var ppProvCtlContext: PCCTL_CONTEXT): BOOL; stdcall;
  {$EXTERNALSYM PFN_CERT_STORE_PROV_FIND_CTL}
  PfnCertStoreProvFindCtl = PFN_CERT_STORE_PROV_FIND_CTL;

  PFN_CERT_STORE_PROV_FREE_FIND_CTL = function (hStoreProv: HCERTSTOREPROV;
    pCtlContext: PCCTL_CONTEXT; pvStoreProvFindInfo: Pointer; dwFlags: DWORD): BOOL; stdcall;
  {$EXTERNALSYM PFN_CERT_STORE_PROV_FREE_FIND_CTL}
  PfnCertStoreProvFreeFindCtl = PFN_CERT_STORE_PROV_FREE_FIND_CTL;

  PFN_CERT_STORE_PROV_GET_CTL_PROPERTY = function (hStoreProv: HCERTSTOREPROV;
    pCtlContext: PCCTL_CONTEXT; dwPropId: DWORD; dwFlags: DWORD; pvData: Pointer;
    var pcbData: DWORD): BOOL; stdcall;
  {$EXTERNALSYM PFN_CERT_STORE_PROV_GET_CTL_PROPERTY}
  PfnCertStoreProvGetCtlProperty = PFN_CERT_STORE_PROV_GET_CTL_PROPERTY;

//+-------------------------------------------------------------------------
//  Duplicate a cert store handle
//--------------------------------------------------------------------------

function CertDuplicateStore(hCertStore: HCERTSTORE): HCERTSTORE; stdcall;
{$EXTERNALSYM CertDuplicateStore}

const
  CERT_STORE_SAVE_AS_STORE = 1;
  {$EXTERNALSYM CERT_STORE_SAVE_AS_STORE}
  CERT_STORE_SAVE_AS_PKCS7 = 2;
  {$EXTERNALSYM CERT_STORE_SAVE_AS_PKCS7}

  CERT_STORE_SAVE_TO_FILE       = 1;
  {$EXTERNALSYM CERT_STORE_SAVE_TO_FILE}
  CERT_STORE_SAVE_TO_MEMORY     = 2;
  {$EXTERNALSYM CERT_STORE_SAVE_TO_MEMORY}
  CERT_STORE_SAVE_TO_FILENAME_A = 3;
  {$EXTERNALSYM CERT_STORE_SAVE_TO_FILENAME_A}
  CERT_STORE_SAVE_TO_FILENAME_W = 4;
  {$EXTERNALSYM CERT_STORE_SAVE_TO_FILENAME_W}
  CERT_STORE_SAVE_TO_FILENAME   = CERT_STORE_SAVE_TO_FILENAME_W;
  {$EXTERNALSYM CERT_STORE_SAVE_TO_FILENAME}

//+-------------------------------------------------------------------------
//  Save the cert store. Extended version with lots of options.
//
//  According to the dwSaveAs parameter, the store can be saved as a
//  serialized store (CERT_STORE_SAVE_AS_STORE) containing properties in
//  addition to encoded certificates, CRLs and CTLs or the store can be saved
//  as a PKCS #7 signed message (CERT_STORE_SAVE_AS_PKCS7) which doesn't
//  include the properties or CTLs.
//
//  Note, the CERT_KEY_CONTEXT_PROP_ID property (and its
//  CERT_KEY_PROV_HANDLE_PROP_ID or CERT_KEY_SPEC_PROP_ID) isn't saved into
//  a serialized store.
//
//  For CERT_STORE_SAVE_AS_PKCS7, the dwEncodingType specifies the message
//  encoding type. The dwEncodingType parameter isn't used for
//  CERT_STORE_SAVE_AS_STORE.
//
//  The dwFlags parameter currently isn't used and should be set to 0.
//
//  The dwSaveTo and pvSaveToPara parameters specify where to save the
//  store as follows:
//    CERT_STORE_SAVE_TO_FILE:
//      Saves to the specified file. The file's handle is passed in
//      pvSaveToPara. Given,
//          HANDLE hFile; pvSaveToPara = (void *) hFile;
//
//      For a successful save, the file pointer is positioned after the
//      last write.
//
//    CERT_STORE_SAVE_TO_MEMORY:
//      Saves to the specified memory blob. The pointer to
//      the memory blob is passed in pvSaveToPara. Given,
//          CRYPT_DATA_BLOB SaveBlob; pvSaveToPara = (void *) &SaveBlob;
//      Upon entry, the SaveBlob's pbData and cbData need to be initialized.
//      Upon return, cbData is updated with the actual length.
//      For a length only calculation, pbData should be set to NULL. If
//      pbData is non-NULL and cbData isn't large enough, FALSE is returned
//      with a last error of ERRROR_MORE_DATA.
//
//    CERT_STORE_SAVE_TO_FILENAME_A:
//    CERT_STORE_SAVE_TO_FILENAME_W:
//    CERT_STORE_SAVE_TO_FILENAME:
//      Opens the file and saves to it. The filename is passed in pvSaveToPara.
//      The filename is UNICODE for the "_W" option and ASCII for the "_A"
//      option. For "_W": given,
//          LPCWSTR pwszFilename; pvSaveToPara = (void *) pwszFilename;
//      For "_A": given,
//          LPCSTR pszFilename; pvSaveToPara = (void *) pszFilename;
//
//      Note, the default (without "_A" or "_W") is UNICODE.
//
//--------------------------------------------------------------------------

function CertSaveStore(hCertStore: HCERTSTORE; dwEncodingType, dwSaveAs: DWORD;
  dwSaveTo: DWORD; pvSaveToPara: Pointer; dwFlags: DWORD): BOOL; stdcall;
{$EXTERNALSYM CertSaveStore}

//+-------------------------------------------------------------------------
//  Certificate Store close flags
//--------------------------------------------------------------------------

const
  CERT_CLOSE_STORE_FORCE_FLAG = $00000001;
  {$EXTERNALSYM CERT_CLOSE_STORE_FORCE_FLAG}
  CERT_CLOSE_STORE_CHECK_FLAG = $00000002;
  {$EXTERNALSYM CERT_CLOSE_STORE_CHECK_FLAG}

//+-------------------------------------------------------------------------
//  Close a cert store handle.
//
//  There needs to be a corresponding close for each open and duplicate.
//
//  Even on the final close, the cert store isn't freed until all of its
//  certificate and CRL contexts have also been freed.
//
//  On the final close, the hCryptProv passed to CertStoreOpen is
//  CryptReleaseContext'ed.
//
//  To force the closure of the store with all of its memory freed, set the
//  CERT_STORE_CLOSE_FORCE_FLAG. This flag should be set when the caller does
//  its own reference counting and wants everything to vanish.
//
//  To check if all the store's certificates and CRLs have been freed and that
//  this is the last CertCloseStore, set the CERT_CLOSE_STORE_CHECK_FLAG. If
//  set and certs, CRLs or stores still need to be freed/closed, FALSE is
//  returned with LastError set to CRYPT_E_PENDING_CLOSE. Note, for FALSE,
//  the store is still closed. This is a diagnostic flag.
//
//  LastError is preserved unless CERT_CLOSE_STORE_CHECK_FLAG is set and FALSE
//  is returned.
//--------------------------------------------------------------------------

function CertCloseStore(hCertStore: HCERTSTORE; dwFlags: DWORD): BOOL; stdcall;
{$EXTERNALSYM CertCloseStore}

//+-------------------------------------------------------------------------
//  Get the subject certificate context uniquely identified by its Issuer and
//  SerialNumber from the store.
//
//  If the certificate isn't found, NULL is returned. Otherwise, a pointer to
//  a read only CERT_CONTEXT is returned. CERT_CONTEXT must be freed by calling
//  CertFreeCertificateContext. CertDuplicateCertificateContext can be called to make a
//  duplicate.
//
//  The returned certificate might not be valid. Normally, it would be
//  verified when getting its issuer certificate (CertGetIssuerCertificateFromStore).
//--------------------------------------------------------------------------

function CertGetSubjectCertificateFromStore(hCertStore: HCERTSTORE;
  dwCertEncodingType: DWORD; pCertId: PCERT_INFO): PCCERT_CONTEXT; stdcall;
{$EXTERNALSYM CertGetSubjectCertificateFromStore}

//+-------------------------------------------------------------------------
//  Enumerate the certificate contexts in the store.
//
//  If a certificate isn't found, NULL is returned.
//  Otherwise, a pointer to a read only CERT_CONTEXT is returned. CERT_CONTEXT
//  must be freed by calling CertFreeCertificateContext or is freed when passed as the
//  pPrevCertContext on a subsequent call. CertDuplicateCertificateContext
//  can be called to make a duplicate.
//
//  pPrevCertContext MUST BE NULL to enumerate the first
//  certificate in the store. Successive certificates are enumerated by setting
//  pPrevCertContext to the CERT_CONTEXT returned by a previous call.
//
//  NOTE: a NON-NULL pPrevCertContext is always CertFreeCertificateContext'ed by
//  this function, even for an error.
//--------------------------------------------------------------------------

function CertEnumCertificatesInStore(hCertStore: HCERTSTORE;
  pPrevCertContext: PCCERT_CONTEXT): PCCERT_CONTEXT; stdcall;
{$EXTERNALSYM CertEnumCertificatesInStore}

//+-------------------------------------------------------------------------
//  Find the first or next certificate context in the store.
//
//  The certificate is found according to the dwFindType and its pvFindPara.
//  See below for a list of the find types and its parameters.
//
//  Currently dwFindFlags is only used for CERT_FIND_SUBJECT_ATTR,
//  CERT_FIND_ISSUER_ATTR or CERT_FIND_CTL_USAGE. Otherwise, must be set to 0.
//
//  Usage of dwCertEncodingType depends on the dwFindType.
//
//  If the first or next certificate isn't found, NULL is returned.
//  Otherwise, a pointer to a read only CERT_CONTEXT is returned. CERT_CONTEXT
//  must be freed by calling CertFreeCertificateContext or is freed when passed as the
//  pPrevCertContext on a subsequent call. CertDuplicateCertificateContext
//  can be called to make a duplicate.
//
//  pPrevCertContext MUST BE NULL on the first
//  call to find the certificate. To find the next certificate, the
//  pPrevCertContext is set to the CERT_CONTEXT returned by a previous call.
//
//  NOTE: a NON-NULL pPrevCertContext is always CertFreeCertificateContext'ed by
//  this function, even for an error.
//--------------------------------------------------------------------------

function CertFindCertificateInStore(hCertStore: HCERTSTORE;
  dwCertEncodingType, dwFindFlags, dwFindType: DWORD; pvFindPara: Pointer;
  pPrevCertContext: PCCERT_CONTEXT): PCCERT_CONTEXT; stdcall;
{$EXTERNALSYM CertFindCertificateInStore}

//+-------------------------------------------------------------------------
// Certificate comparison functions
//--------------------------------------------------------------------------

const
  CERT_COMPARE_MASK           = $FFFF;
  {$EXTERNALSYM CERT_COMPARE_MASK}
  CERT_COMPARE_SHIFT          = 16;
  {$EXTERNALSYM CERT_COMPARE_SHIFT}
  CERT_COMPARE_ANY            = 0;
  {$EXTERNALSYM CERT_COMPARE_ANY}
  CERT_COMPARE_SHA1_HASH      = 1;
  {$EXTERNALSYM CERT_COMPARE_SHA1_HASH}
  CERT_COMPARE_NAME           = 2;
  {$EXTERNALSYM CERT_COMPARE_NAME}
  CERT_COMPARE_ATTR           = 3;
  {$EXTERNALSYM CERT_COMPARE_ATTR}
  CERT_COMPARE_MD5_HASH       = 4;
  {$EXTERNALSYM CERT_COMPARE_MD5_HASH}
  CERT_COMPARE_PROPERTY       = 5;
  {$EXTERNALSYM CERT_COMPARE_PROPERTY}
  CERT_COMPARE_PUBLIC_KEY     = 6;
  {$EXTERNALSYM CERT_COMPARE_PUBLIC_KEY}
  CERT_COMPARE_HASH           = CERT_COMPARE_SHA1_HASH;
  {$EXTERNALSYM CERT_COMPARE_HASH}
  CERT_COMPARE_NAME_STR_A     = 7;
  {$EXTERNALSYM CERT_COMPARE_NAME_STR_A}
  CERT_COMPARE_NAME_STR_W     = 8;
  {$EXTERNALSYM CERT_COMPARE_NAME_STR_W}
  CERT_COMPARE_KEY_SPEC       = 9;
  {$EXTERNALSYM CERT_COMPARE_KEY_SPEC}
  CERT_COMPARE_ENHKEY_USAGE   = 10;
  {$EXTERNALSYM CERT_COMPARE_ENHKEY_USAGE}
  CERT_COMPARE_CTL_USAGE      = CERT_COMPARE_ENHKEY_USAGE;
  {$EXTERNALSYM CERT_COMPARE_CTL_USAGE}
  CERT_COMPARE_SUBJECT_CERT   = 11;
  {$EXTERNALSYM CERT_COMPARE_SUBJECT_CERT}
  CERT_COMPARE_ISSUER_OF      = 12;
  {$EXTERNALSYM CERT_COMPARE_ISSUER_OF}
  CERT_COMPARE_EXISTING       = 13;
  {$EXTERNALSYM CERT_COMPARE_EXISTING}
  CERT_COMPARE_SIGNATURE_HASH = 14;
  {$EXTERNALSYM CERT_COMPARE_SIGNATURE_HASH}
  CERT_COMPARE_KEY_IDENTIFIER = 15;
  {$EXTERNALSYM CERT_COMPARE_KEY_IDENTIFIER}
  CERT_COMPARE_CERT_ID        = 16;
  {$EXTERNALSYM CERT_COMPARE_CERT_ID}

//+-------------------------------------------------------------------------
//  dwFindType
//
//  The dwFindType definition consists of two components:
//   - comparison function
//   - certificate information flag
//--------------------------------------------------------------------------

  CERT_FIND_ANY            = (CERT_COMPARE_ANY shl CERT_COMPARE_SHIFT);
  {$EXTERNALSYM CERT_FIND_ANY}
  CERT_FIND_SHA1_HASH      = (CERT_COMPARE_SHA1_HASH shl CERT_COMPARE_SHIFT);
  {$EXTERNALSYM CERT_FIND_SHA1_HASH}
  CERT_FIND_MD5_HASH       = (CERT_COMPARE_MD5_HASH shl CERT_COMPARE_SHIFT);
  {$EXTERNALSYM CERT_FIND_MD5_HASH}
  CERT_FIND_SIGNATURE_HASH = (CERT_COMPARE_SIGNATURE_HASH shl CERT_COMPARE_SHIFT);
  {$EXTERNALSYM CERT_FIND_SIGNATURE_HASH}
  CERT_FIND_KEY_IDENTIFIER = (CERT_COMPARE_KEY_IDENTIFIER shl CERT_COMPARE_SHIFT);
  {$EXTERNALSYM CERT_FIND_KEY_IDENTIFIER}
  CERT_FIND_HASH           = CERT_FIND_SHA1_HASH;
  {$EXTERNALSYM CERT_FIND_HASH}
  CERT_FIND_PROPERTY       = (CERT_COMPARE_PROPERTY shl CERT_COMPARE_SHIFT);
  {$EXTERNALSYM CERT_FIND_PROPERTY}
  CERT_FIND_PUBLIC_KEY     = (CERT_COMPARE_PUBLIC_KEY shl CERT_COMPARE_SHIFT);
  {$EXTERNALSYM CERT_FIND_PUBLIC_KEY}
  CERT_FIND_SUBJECT_NAME   = (CERT_COMPARE_NAME shl CERT_COMPARE_SHIFT or CERT_INFO_SUBJECT_FLAG);
  {$EXTERNALSYM CERT_FIND_SUBJECT_NAME}
  CERT_FIND_SUBJECT_ATTR   = (CERT_COMPARE_ATTR shl CERT_COMPARE_SHIFT or CERT_INFO_SUBJECT_FLAG);
  {$EXTERNALSYM CERT_FIND_SUBJECT_ATTR}
  CERT_FIND_ISSUER_NAME    = (CERT_COMPARE_NAME shl CERT_COMPARE_SHIFT or CERT_INFO_ISSUER_FLAG);
  {$EXTERNALSYM CERT_FIND_ISSUER_NAME}
  CERT_FIND_ISSUER_ATTR    = (CERT_COMPARE_ATTR shl CERT_COMPARE_SHIFT or CERT_INFO_ISSUER_FLAG);
  {$EXTERNALSYM CERT_FIND_ISSUER_ATTR}
  CERT_FIND_SUBJECT_STR_A  = (CERT_COMPARE_NAME_STR_A shl CERT_COMPARE_SHIFT or CERT_INFO_SUBJECT_FLAG);
  {$EXTERNALSYM CERT_FIND_SUBJECT_STR_A}
  CERT_FIND_SUBJECT_STR_W  = (CERT_COMPARE_NAME_STR_W shl CERT_COMPARE_SHIFT or CERT_INFO_SUBJECT_FLAG);
  {$EXTERNALSYM CERT_FIND_SUBJECT_STR_W}
  CERT_FIND_SUBJECT_STR    = CERT_FIND_SUBJECT_STR_W;
  {$EXTERNALSYM CERT_FIND_SUBJECT_STR}
  CERT_FIND_ISSUER_STR_A   = (CERT_COMPARE_NAME_STR_A shl CERT_COMPARE_SHIFT or CERT_INFO_ISSUER_FLAG);
  {$EXTERNALSYM CERT_FIND_ISSUER_STR_A}
  CERT_FIND_ISSUER_STR_W   = (CERT_COMPARE_NAME_STR_W shl CERT_COMPARE_SHIFT or CERT_INFO_ISSUER_FLAG);
  {$EXTERNALSYM CERT_FIND_ISSUER_STR_W}
  CERT_FIND_ISSUER_STR     = CERT_FIND_ISSUER_STR_W;
  {$EXTERNALSYM CERT_FIND_ISSUER_STR}
  CERT_FIND_KEY_SPEC       = (CERT_COMPARE_KEY_SPEC shl CERT_COMPARE_SHIFT);
  {$EXTERNALSYM CERT_FIND_KEY_SPEC}
  CERT_FIND_ENHKEY_USAGE   = (CERT_COMPARE_ENHKEY_USAGE shl CERT_COMPARE_SHIFT);
  {$EXTERNALSYM CERT_FIND_ENHKEY_USAGE}
  CERT_FIND_CTL_USAGE      = CERT_FIND_ENHKEY_USAGE;
  {$EXTERNALSYM CERT_FIND_CTL_USAGE}

  CERT_FIND_SUBJECT_CERT = (CERT_COMPARE_SUBJECT_CERT shl CERT_COMPARE_SHIFT);
  {$EXTERNALSYM CERT_FIND_SUBJECT_CERT}
  CERT_FIND_ISSUER_OF    = (CERT_COMPARE_ISSUER_OF shl CERT_COMPARE_SHIFT);
  {$EXTERNALSYM CERT_FIND_ISSUER_OF}
  CERT_FIND_EXISTING     = (CERT_COMPARE_EXISTING shl CERT_COMPARE_SHIFT);
  {$EXTERNALSYM CERT_FIND_EXISTING}
  CERT_FIND_CERT_ID      = (CERT_COMPARE_CERT_ID shl CERT_COMPARE_SHIFT);
  {$EXTERNALSYM CERT_FIND_CERT_ID}

//+-------------------------------------------------------------------------
//  CERT_FIND_ANY
//
//  Find any certificate.
//
//  pvFindPara isn't used.
//--------------------------------------------------------------------------

//+-------------------------------------------------------------------------
//  CERT_FIND_HASH
//
//  Find a certificate with the specified hash.
//
//  pvFindPara points to a CRYPT_HASH_BLOB.
//--------------------------------------------------------------------------

//+-------------------------------------------------------------------------
//  CERT_FIND_KEY_IDENTIFIER
//
//  Find a certificate with the specified KeyIdentifier. Gets the
//  CERT_KEY_IDENTIFIER_PROP_ID property and compares with the input
//  CRYPT_HASH_BLOB.
//
//  pvFindPara points to a CRYPT_HASH_BLOB.
//--------------------------------------------------------------------------

//+-------------------------------------------------------------------------
//  CERT_FIND_PROPERTY
//
//  Find a certificate having the specified property.
//
//  pvFindPara points to a DWORD containing the PROP_ID
//--------------------------------------------------------------------------

//+-------------------------------------------------------------------------
//  CERT_FIND_PUBLIC_KEY
//
//  Find a certificate matching the specified public key.
//
//  pvFindPara points to a CERT_PUBLIC_KEY_INFO containing the public key
//--------------------------------------------------------------------------

//+-------------------------------------------------------------------------
//  CERT_FIND_SUBJECT_NAME
//  CERT_FIND_ISSUER_NAME
//
//  Find a certificate with the specified subject/issuer name. Does an exact
//  match of the entire name.
//
//  Restricts search to certificates matching the dwCertEncodingType.
//
//  pvFindPara points to a CERT_NAME_BLOB.
//--------------------------------------------------------------------------

//+-------------------------------------------------------------------------
//  CERT_FIND_SUBJECT_ATTR
//  CERT_FIND_ISSUER_ATTR
//
//  Find a certificate with the specified subject/issuer attributes.
//
//  Compares the attributes in the subject/issuer name with the
//  Relative Distinguished Name's (CERT_RDN) array of attributes specified in
//  pvFindPara. The comparison iterates through the CERT_RDN attributes and looks
//  for an attribute match in any of the subject/issuer's RDNs.
//
//  The CERT_RDN_ATTR fields can have the following special values:
//    pszObjId == NULL              - ignore the attribute object identifier
//    dwValueType == RDN_ANY_TYPE   - ignore the value type
//    Value.pbData == NULL          - match any value
//
//  CERT_CASE_INSENSITIVE_IS_RDN_ATTRS_FLAG should be set in dwFindFlags to do
//  a case insensitive match. Otherwise, defaults to an exact, case sensitive
//  match.
//
//  CERT_UNICODE_IS_RDN_ATTRS_FLAG should be set in dwFindFlags if the RDN was
//  initialized with unicode strings as for
//  CryptEncodeObject(X509_UNICODE_NAME).
//
//  Restricts search to certificates matching the dwCertEncodingType.
//
//  pvFindPara points to a CERT_RDN (defined in wincert.h).
//--------------------------------------------------------------------------

//+-------------------------------------------------------------------------
//  CERT_FIND_SUBJECT_STR_A
//  CERT_FIND_SUBJECT_STR_W | CERT_FIND_SUBJECT_STR
//  CERT_FIND_ISSUER_STR_A
//  CERT_FIND_ISSUER_STR_W  | CERT_FIND_ISSUER_STR
//
//  Find a certificate containing the specified subject/issuer name string.
//
//  First, the certificate's subject/issuer is converted to a name string
//  via CertNameToStrA/CertNameToStrW(CERT_SIMPLE_NAME_STR). Then, a
//  case insensitive substring within string match is performed.
//
//  Restricts search to certificates matching the dwCertEncodingType.
//
//  For *_STR_A, pvFindPara points to a null terminated character string.
//  For *_STR_W, pvFindPara points to a null terminated wide character string.
//--------------------------------------------------------------------------

//+-------------------------------------------------------------------------
//  CERT_FIND_KEY_SPEC
//
//  Find a certificate having a CERT_KEY_SPEC_PROP_ID property matching
//  the specified KeySpec.
//
//  pvFindPara points to a DWORD containing the KeySpec.
//--------------------------------------------------------------------------

//+-------------------------------------------------------------------------
//  CERT_FIND_ENHKEY_USAGE
//
//  Find a certificate having the szOID_ENHANCED_KEY_USAGE extension or
//  the CERT_ENHKEY_USAGE_PROP_ID and matching the specified pszUsageIdentifers.
//
//  pvFindPara points to a CERT_ENHKEY_USAGE data structure. If pvFindPara
//  is NULL or CERT_ENHKEY_USAGE's cUsageIdentifier is 0, then, matches any
//  certificate having enhanced key usage.
//
//  If the CERT_FIND_VALID_ENHKEY_USAGE_FLAG is set, then, only does a match
//  for certificates that are valid for the specified usages. By default,
//  the ceriticate must be valid for all usages. CERT_FIND_OR_ENHKEY_USAGE_FLAG
//  can be set, if the certificate only needs to be valid for one of the
//  specified usages. Note, CertGetValidUsages() is called to get the
//  certificate's list of valid usages. Only the CERT_FIND_OR_ENHKEY_USAGE_FLAG
//  is applicable when this flag is set.
//
//  The CERT_FIND_OPTIONAL_ENHKEY_USAGE_FLAG can be set in dwFindFlags to
//  also match a certificate without either the extension or property.
//
//  If CERT_FIND_NO_ENHKEY_USAGE_FLAG is set in dwFindFlags, finds
//  certificates without the key usage extension or property. Setting this
//  flag takes precedence over pvFindPara being NULL.
//
//  If the CERT_FIND_EXT_ONLY_ENHKEY_USAGE_FLAG is set, then, only does a match
//  using the extension. If pvFindPara is NULL or cUsageIdentifier is set to
//  0, finds certificates having the extension. If
//  CERT_FIND_OPTIONAL_ENHKEY_USAGE_FLAG is set, also matches a certificate
//  without the extension. If CERT_FIND_NO_ENHKEY_USAGE_FLAG is set, finds
//  certificates without the extension.
//
//  If the CERT_FIND_PROP_ONLY_ENHKEY_USAGE_FLAG is set, then, only does a match
//  using the property. If pvFindPara is NULL or cUsageIdentifier is set to
//  0, finds certificates having the property. If
//  CERT_FIND_OPTIONAL_ENHKEY_USAGE_FLAG is set, also matches a certificate
//  without the property. If CERT_FIND_NO_ENHKEY_USAGE_FLAG is set, finds
//  certificates without the property.
//
//  If CERT_FIND_OR_ENHKEY_USAGE_FLAG is set, does an "OR" match of any of
//  the specified pszUsageIdentifiers. If not set, then, does an "AND" match
//  of all of the specified pszUsageIdentifiers.
//--------------------------------------------------------------------------

const
  CERT_FIND_OPTIONAL_ENHKEY_USAGE_FLAG  = $1;
  {$EXTERNALSYM CERT_FIND_OPTIONAL_ENHKEY_USAGE_FLAG}
  CERT_FIND_EXT_ONLY_ENHKEY_USAGE_FLAG  = $2;
  {$EXTERNALSYM CERT_FIND_EXT_ONLY_ENHKEY_USAGE_FLAG}
  CERT_FIND_PROP_ONLY_ENHKEY_USAGE_FLAG = $4;
  {$EXTERNALSYM CERT_FIND_PROP_ONLY_ENHKEY_USAGE_FLAG}
  CERT_FIND_NO_ENHKEY_USAGE_FLAG        = $8;
  {$EXTERNALSYM CERT_FIND_NO_ENHKEY_USAGE_FLAG}
  CERT_FIND_OR_ENHKEY_USAGE_FLAG        = $10;
  {$EXTERNALSYM CERT_FIND_OR_ENHKEY_USAGE_FLAG}
  CERT_FIND_VALID_ENHKEY_USAGE_FLAG     = $20;
  {$EXTERNALSYM CERT_FIND_VALID_ENHKEY_USAGE_FLAG}

  CERT_FIND_OPTIONAL_CTL_USAGE_FLAG = CERT_FIND_OPTIONAL_ENHKEY_USAGE_FLAG;
  {$EXTERNALSYM CERT_FIND_OPTIONAL_CTL_USAGE_FLAG}

  CERT_FIND_EXT_ONLY_CTL_USAGE_FLAG = CERT_FIND_EXT_ONLY_ENHKEY_USAGE_FLAG;
  {$EXTERNALSYM CERT_FIND_EXT_ONLY_CTL_USAGE_FLAG}

  CERT_FIND_PROP_ONLY_CTL_USAGE_FLAG = CERT_FIND_PROP_ONLY_ENHKEY_USAGE_FLAG;
  {$EXTERNALSYM CERT_FIND_PROP_ONLY_CTL_USAGE_FLAG}

  CERT_FIND_NO_CTL_USAGE_FLAG    = CERT_FIND_NO_ENHKEY_USAGE_FLAG;
  {$EXTERNALSYM CERT_FIND_NO_CTL_USAGE_FLAG}
  CERT_FIND_OR_CTL_USAGE_FLAG    = CERT_FIND_OR_ENHKEY_USAGE_FLAG;
  {$EXTERNALSYM CERT_FIND_OR_CTL_USAGE_FLAG}
  CERT_FIND_VALID_CTL_USAGE_FLAG = CERT_FIND_VALID_ENHKEY_USAGE_FLAG;
  {$EXTERNALSYM CERT_FIND_VALID_CTL_USAGE_FLAG}

//+-------------------------------------------------------------------------
//  CERT_FIND_CERT_ID
//
//  Find a certificate with the specified CERT_ID.
//
//  pvFindPara points to a CERT_ID.
//--------------------------------------------------------------------------

//+-------------------------------------------------------------------------
//  Get the certificate context from the store for the first or next issuer
//  of the specified subject certificate. Perform the enabled
//  verification checks on the subject. (Note, the checks are on the subject
//  using the returned issuer certificate.)
//
//  If the first or next issuer certificate isn't found, NULL is returned.
//  Otherwise, a pointer to a read only CERT_CONTEXT is returned. CERT_CONTEXT
//  must be freed by calling CertFreeCertificateContext or is freed when passed as the
//  pPrevIssuerContext on a subsequent call. CertDuplicateCertificateContext
//  can be called to make a duplicate.
//
//  For a self signed subject certificate, NULL is returned with LastError set
//  to CERT_STORE_SELF_SIGNED. The enabled verification checks are still done.
//
//  The pSubjectContext may have been obtained from this store, another store
//  or created by the caller application. When created by the caller, the
//  CertCreateCertificateContext function must have been called.
//
//  An issuer may have multiple certificates. This may occur when the validity
//  period is about to change. pPrevIssuerContext MUST BE NULL on the first
//  call to get the issuer. To get the next certificate for the issuer, the
//  pPrevIssuerContext is set to the CERT_CONTEXT returned by a previous call.
//
//  NOTE: a NON-NULL pPrevIssuerContext is always CertFreeCertificateContext'ed by
//  this function, even for an error.
//
//  The following flags can be set in *pdwFlags to enable verification checks
//  on the subject certificate context:
//      CERT_STORE_SIGNATURE_FLAG     - use the public key in the returned
//                                      issuer certificate to verify the
//                                      signature on the subject certificate.
//                                      Note, if pSubjectContext->hCertStore ==
//                                      hCertStore, the store provider might
//                                      be able to eliminate a redo of
//                                      the signature verify.
//      CERT_STORE_TIME_VALIDITY_FLAG - get the current time and verify that
//                                      its within the subject certificate's
//                                      validity period
//      CERT_STORE_REVOCATION_FLAG    - check if the subject certificate is on
//                                      the issuer's revocation list
//
//  If an enabled verification check fails, then, its flag is set upon return.
//  If CERT_STORE_REVOCATION_FLAG was enabled and the issuer doesn't have a
//  CRL in the store, then, CERT_STORE_NO_CRL_FLAG is set in addition to
//  the CERT_STORE_REVOCATION_FLAG.
//
//  If CERT_STORE_SIGNATURE_FLAG or CERT_STORE_REVOCATION_FLAG is set, then,
//  CERT_STORE_NO_ISSUER_FLAG is set if it doesn't have an issuer certificate
//  in the store.
//
//  For a verification check failure, a pointer to the issuer's CERT_CONTEXT
//  is still returned and SetLastError isn't updated.
//--------------------------------------------------------------------------

function CertGetIssuerCertificateFromStore(hCertStore: HCERTSTORE;
  pSubjectContext, pPrevIssuerContext: PCCERT_CONTEXT; var pdwFlags: DWORD): PCCERT_CONTEXT; stdcall;
{$EXTERNALSYM CertGetIssuerCertificateFromStore}

//+-------------------------------------------------------------------------
//  Perform the enabled verification checks on the subject certificate
//  using the issuer. Same checks and flags definitions as for the above
//  CertGetIssuerCertificateFromStore.
//
//  If you are only checking CERT_STORE_TIME_VALIDITY_FLAG, then, the
//  issuer can be NULL.
//
//  For a verification check failure, SUCCESS is still returned.
//--------------------------------------------------------------------------

function CertVerifySubjectCertificateContext(pSubject: PCCERT_CONTEXT;
  pIssuer: PCCERT_CONTEXT; var pdwFlags: DWORD): BOOL; stdcall;
{$EXTERNALSYM CertVerifySubjectCertificateContext}

//+-------------------------------------------------------------------------
//  Duplicate a certificate context
//--------------------------------------------------------------------------

function CertDuplicateCertificateContext(pCertContext: PCCERT_CONTEXT): PCCERT_CONTEXT; stdcall;
{$EXTERNALSYM CertDuplicateCertificateContext}

//+-------------------------------------------------------------------------
//  Create a certificate context from the encoded certificate. The created
//  context isn't put in a store.
//
//  Makes a copy of the encoded certificate in the created context.
//
//  If unable to decode and create the certificate context, NULL is returned.
//  Otherwise, a pointer to a read only CERT_CONTEXT is returned.
//  CERT_CONTEXT must be freed by calling CertFreeCertificateContext.
//  CertDuplicateCertificateContext can be called to make a duplicate.
//
//  CertSetCertificateContextProperty and CertGetCertificateContextProperty can be called
//  to store properties for the certificate.
//--------------------------------------------------------------------------

function CertCreateCertificateContext(dwCertEncodingType: DWORD;
  pbCertEncoded: LPBYTE; cbCertEncoded: DWORD): PCCERT_CONTEXT; stdcall;
{$EXTERNALSYM CertCreateCertificateContext}

//+-------------------------------------------------------------------------
//  Free a certificate context
//
//  There needs to be a corresponding free for each context obtained by a
//  get, find, duplicate or create.
//--------------------------------------------------------------------------

function CertFreeCertificateContext(pCertContext: PCCERT_CONTEXT): BOOL; stdcall;
{$EXTERNALSYM CertFreeCertificateContext}

//+-------------------------------------------------------------------------
//  Set the property for the specified certificate context.
//
//  The type definition for pvData depends on the dwPropId value. There are
//  five predefined types:
//      CERT_KEY_PROV_HANDLE_PROP_ID - a HCRYPTPROV for the certificate's
//      private key is passed in pvData. Updates the hCryptProv field
//      of the CERT_KEY_CONTEXT_PROP_ID. If the CERT_KEY_CONTEXT_PROP_ID
//      doesn't exist, its created with all the other fields zeroed out. If
//      CERT_STORE_NO_CRYPT_RELEASE_FLAG isn't set, HCRYPTPROV is implicitly
//      released when either the property is set to NULL or on the final
//      free of the CertContext.
//
//      CERT_KEY_PROV_INFO_PROP_ID - a PCRYPT_KEY_PROV_INFO for the certificate's
//      private key is passed in pvData.
//
//      CERT_SHA1_HASH_PROP_ID       -
//      CERT_MD5_HASH_PROP_ID        -
//      CERT_SIGNATURE_HASH_PROP_ID  - normally, a hash property is implicitly
//      set by doing a CertGetCertificateContextProperty. pvData points to a
//      CRYPT_HASH_BLOB.
//
//      CERT_KEY_CONTEXT_PROP_ID - a PCERT_KEY_CONTEXT for the certificate's
//      private key is passed in pvData. The CERT_KEY_CONTEXT contains both the
//      hCryptProv and dwKeySpec for the private key.
//      See the CERT_KEY_PROV_HANDLE_PROP_ID for more information about
//      the hCryptProv field and dwFlags settings. Note, more fields may
//      be added for this property. The cbSize field value will be adjusted
//      accordingly.
//
//      CERT_KEY_SPEC_PROP_ID - the dwKeySpec for the private key. pvData
//      points to a DWORD containing the KeySpec
//
//      CERT_ENHKEY_USAGE_PROP_ID - enhanced key usage definition for the
//      certificate. pvData points to a CRYPT_DATA_BLOB containing an
//      ASN.1 encoded CERT_ENHKEY_USAGE (encoded via
//      CryptEncodeObject(X509_ENHANCED_KEY_USAGE).
//
//      CERT_NEXT_UPDATE_LOCATION_PROP_ID - location of the next update.
//      Currently only applicable to CTLs. pvData points to a CRYPT_DATA_BLOB
//      containing an ASN.1 encoded CERT_ALT_NAME_INFO (encoded via
//      CryptEncodeObject(X509_ALTERNATE_NAME)).
//
//      CERT_FRIENDLY_NAME_PROP_ID - friendly name for the cert, CRL or CTL.
//      pvData points to a CRYPT_DATA_BLOB. pbData is a pointer to a NULL
//      terminated unicode, wide character string.
//      cbData = (wcslen((LPWSTR) pbData) + 1) * sizeof(WCHAR).
//
//      CERT_DESCRIPTION_PROP_ID - description for the cert, CRL or CTL.
//      pvData points to a CRYPT_DATA_BLOB. pbData is a pointer to a NULL
//      terminated unicode, wide character string.
//      cbData = (wcslen((LPWSTR) pbData) + 1) * sizeof(WCHAR).
//
//      CERT_ARCHIVED_PROP_ID - when this property is set, the certificate
//      is skipped during enumeration. Note, certificates having this property
//      are still found for explicit finds, such as, finding a certificate
//      with a specific hash or finding a certificate having a specific issuer
//      and serial number. pvData points to a CRYPT_DATA_BLOB. This blob
//      can be NULL (pbData = NULL, cbData = 0).
//
//      CERT_PUBKEY_ALG_PARA_PROP_ID - for public keys supporting
//      algorithm parameter inheritance. pvData points to a CRYPT_OBJID_BLOB
//      containing the ASN.1 encoded PublicKey Algorithm Parameters. For
//      DSS this would be the parameters encoded via
//      CryptEncodeObject(X509_DSS_PARAMETERS). This property may be set
//      by CryptVerifyCertificateSignatureEx().
//
//  For all the other PROP_IDs: an encoded PCRYPT_DATA_BLOB is passed in pvData.
//
//  If the property already exists, then, the old value is deleted and silently
//  replaced. Setting, pvData to NULL, deletes the property.
//
//  CERT_SET_PROPERTY_IGNORE_PERSIST_ERROR_FLAG can be set to ignore any
//  provider write errors and always update the cached context's property.
//--------------------------------------------------------------------------

function CertSetCertificateContextProperty(pCertContext: PCCERT_CONTEXT;
  dwPropId: DWORD; dwFlags: DWORD; pvData: Pointer): BOOL; stdcall;
{$EXTERNALSYM CertSetCertificateContextProperty}

// Set this flag to ignore any store provider write errors and always update
// the cached context's property

const
  CERT_SET_PROPERTY_IGNORE_PERSIST_ERROR_FLAG = DWORD($80000000);
  {$EXTERNALSYM CERT_SET_PROPERTY_IGNORE_PERSIST_ERROR_FLAG}

//+-------------------------------------------------------------------------
//  Get the property for the specified certificate context.
//
//  For CERT_KEY_PROV_HANDLE_PROP_ID, pvData points to a HCRYPTPROV.
//
//  For CERT_KEY_PROV_INFO_PROP_ID, pvData points to a CRYPT_KEY_PROV_INFO structure.
//  Elements pointed to by fields in the pvData structure follow the
//  structure. Therefore, *pcbData may exceed the size of the structure.
//
//  For CERT_KEY_CONTEXT_PROP_ID, pvData points to a CERT_KEY_CONTEXT structure.
//
//  For CERT_KEY_SPEC_PROP_ID, pvData points to a DWORD containing the KeySpec.
//  If the CERT_KEY_CONTEXT_PROP_ID exists, the KeySpec is obtained from there.
//  Otherwise, if the CERT_KEY_PROV_INFO_PROP_ID exists, its the source
//  of the KeySpec.
//
//  For CERT_SHA1_HASH_PROP_ID or CERT_MD5_HASH_PROP_ID, if the hash
//  doesn't already exist, then, its computed via CryptHashCertificate()
//  and then set. pvData points to the computed hash. Normally, the length
//  is 20 bytes for SHA and 16 for MD5.
//
//  For CERT_SIGNATURE_HASH_PROP_ID, if the hash
//  doesn't already exist, then, its computed via CryptHashToBeSigned()
//  and then set. pvData points to the computed hash. Normally, the length
//  is 20 bytes for SHA and 16 for MD5.
//
//  For CERT_ACCESS_STATE_PROP_ID, pvData points to a DWORD containing the
//  access state flags. The appropriate CERT_ACCESS_STATE_*_FLAG's are set
//  in the returned DWORD. See the CERT_ACCESS_STATE_*_FLAG definitions
//  above. Note, this property is read only. It can't be set.
//
//  For CERT_KEY_IDENTIFIER_PROP_ID, if property doesn't already exist,
//  first searches for the szOID_SUBJECT_KEY_IDENTIFIER extension. Next,
//  does SHA1 hash of the certficate's SubjectPublicKeyInfo. pvData
//  points to the key identifier bytes. Normally, the length is 20 bytes.
//
//  For CERT_PUBKEY_ALG_PARA_PROP_ID, pvPara points to the ASN.1 encoded
//  PublicKey Algorithm Parameters. This property will only be set
//  for public keys supporting algorithm parameter inheritance and when the
//  parameters have been omitted from the encoded and signed certificate.
//
//  For all other PROP_IDs, pvData points to an encoded array of bytes.
//--------------------------------------------------------------------------

function CertGetCertificateContextProperty(pCertContext: PCCERT_CONTEXT;
  dwPropId: DWORD; pvData: Pointer; var pcbData: DWORD): BOOL; stdcall;
{$EXTERNALSYM CertGetCertificateContextProperty}

//+-------------------------------------------------------------------------
//  Enumerate the properties for the specified certificate context.
//
//  To get the first property, set dwPropId to 0. The ID of the first
//  property is returned. To get the next property, set dwPropId to the
//  ID returned by the last call. To enumerate all the properties continue
//  until 0 is returned.
//
//  CertGetCertificateContextProperty is called to get the property's data.
//
//  Note, since, the CERT_KEY_PROV_HANDLE_PROP_ID and CERT_KEY_SPEC_PROP_ID
//  properties are stored as fields in the CERT_KEY_CONTEXT_PROP_ID
//  property, they aren't enumerated individually.
//--------------------------------------------------------------------------

function CertEnumCertificateContextProperties(pCertContext: PCCERT_CONTEXT;
  dwPropId: DWORD): DWORD; stdcall;
{$EXTERNALSYM CertEnumCertificateContextProperties}

//+-------------------------------------------------------------------------
//  Get the first or next CRL context from the store for the specified
//  issuer certificate. Perform the enabled verification checks on the CRL.
//
//  If the first or next CRL isn't found, NULL is returned.
//  Otherwise, a pointer to a read only CRL_CONTEXT is returned. CRL_CONTEXT
//  must be freed by calling CertFreeCRLContext. However, the free must be
//  pPrevCrlContext on a subsequent call. CertDuplicateCRLContext
//  can be called to make a duplicate.
//
//  The pIssuerContext may have been obtained from this store, another store
//  or created by the caller application. When created by the caller, the
//  CertCreateCertificateContext function must have been called.
//
//  If pIssuerContext == NULL, finds all the CRLs in the store.
//
//  An issuer may have multiple CRLs. For example, it generates delta CRLs
//  using a X.509 v3 extension. pPrevCrlContext MUST BE NULL on the first
//  call to get the CRL. To get the next CRL for the issuer, the
//  pPrevCrlContext is set to the CRL_CONTEXT returned by a previous call.
//
//  NOTE: a NON-NULL pPrevCrlContext is always CertFreeCRLContext'ed by
//  this function, even for an error.
//
//  The following flags can be set in *pdwFlags to enable verification checks
//  on the returned CRL:
//      CERT_STORE_SIGNATURE_FLAG     - use the public key in the
//                                      issuer's certificate to verify the
//                                      signature on the returned CRL.
//                                      Note, if pIssuerContext->hCertStore ==
//                                      hCertStore, the store provider might
//                                      be able to eliminate a redo of
//                                      the signature verify.
//      CERT_STORE_TIME_VALIDITY_FLAG - get the current time and verify that
//                                      its within the CRL's ThisUpdate and
//                                      NextUpdate validity period.
//
//  If an enabled verification check fails, then, its flag is set upon return.
//
//  If pIssuerContext == NULL, then, an enabled CERT_STORE_SIGNATURE_FLAG
//  always fails and the CERT_STORE_NO_ISSUER_FLAG is also set.
//
//  For a verification check failure, a pointer to the first or next
//  CRL_CONTEXT is still returned and SetLastError isn't updated.
//--------------------------------------------------------------------------

function CertGetCRLFromStore(hCertStore: HCERTSTORE; pIssuerContext: PCCERT_CONTEXT;
  pPrevCrlContext: PCCRL_CONTEXT; var pdwFlags: DWORD): PCCRL_CONTEXT; stdcall;
{$EXTERNALSYM CertGetCRLFromStore}

//+-------------------------------------------------------------------------
//  Enumerate the CRL contexts in the store.
//
//  If a CRL isn't found, NULL is returned.
//  Otherwise, a pointer to a read only CRL_CONTEXT is returned. CRL_CONTEXT
//  must be freed by calling CertFreeCRLContext or is freed when passed as the
//  pPrevCrlContext on a subsequent call. CertDuplicateCRLContext
//  can be called to make a duplicate.
//
//  pPrevCrlContext MUST BE NULL to enumerate the first
//  CRL in the store. Successive CRLs are enumerated by setting
//  pPrevCrlContext to the CRL_CONTEXT returned by a previous call.
//
//  NOTE: a NON-NULL pPrevCrlContext is always CertFreeCRLContext'ed by
//  this function, even for an error.
//--------------------------------------------------------------------------

function CertEnumCRLsInStore(hCertStore: HCERTSTORE;
  pPrevCrlContext: PCCRL_CONTEXT): PCCRL_CONTEXT; stdcall;
{$EXTERNALSYM CertEnumCRLsInStore}

//+-------------------------------------------------------------------------
//  Find the first or next CRL context in the store.
//
//  The CRL is found according to the dwFindType and its pvFindPara.
//  See below for a list of the find types and its parameters.
//
//  Currently dwFindFlags isn't used and must be set to 0.
//
//  Usage of dwCertEncodingType depends on the dwFindType.
//
//  If the first or next CRL isn't found, NULL is returned.
//  Otherwise, a pointer to a read only CRL_CONTEXT is returned. CRL_CONTEXT
//  must be freed by calling CertFreeCRLContext or is freed when passed as the
//  pPrevCrlContext on a subsequent call. CertDuplicateCRLContext
//  can be called to make a duplicate.
//
//  pPrevCrlContext MUST BE NULL on the first
//  call to find the CRL. To find the next CRL, the
//  pPrevCrlContext is set to the CRL_CONTEXT returned by a previous call.
//
//  NOTE: a NON-NULL pPrevCrlContext is always CertFreeCRLContext'ed by
//  this function, even for an error.
//--------------------------------------------------------------------------

function CertFindCRLInStore(hCertStore: HCERTSTORE; dwCertEncodingType: DWORD;
  dwFindFlags: DWORD; dwFindType: DWORD; pvFindPara: Pointer;
  pPrevCrlContext: PCCRL_CONTEXT): PCCRL_CONTEXT; stdcall;
{$EXTERNALSYM CertFindCRLInStore}

const
  CRL_FIND_ANY       = 0;
  {$EXTERNALSYM CRL_FIND_ANY}
  CRL_FIND_ISSUED_BY = 1;
  {$EXTERNALSYM CRL_FIND_ISSUED_BY}
  CRL_FIND_EXISTING  = 2;
  {$EXTERNALSYM CRL_FIND_EXISTING}

//+-------------------------------------------------------------------------
//  CRL_FIND_ANY
//
//  Find any CRL.
//
//  pvFindPara isn't used.
//--------------------------------------------------------------------------

//+-------------------------------------------------------------------------
//  CRL_FIND_ISSUED_BY
//
//  Find CRL matching the specified issuer. 
//
//  pvFindPara is the PCCERT_CONTEXT of the CRL issuer.
//
//  By default, only does issuer name matching. The following flags can be
//  set in dwFindFlags to do additional filtering.
//
//  If CRL_FIND_ISSUED_BY_AKI_FLAG is set in dwFindFlags, then, checks if the
//  CRL has an Authority Key Identifier (AKI) extension. If the CRL has an
//  AKI, then, only returns a CRL whose AKI matches the issuer.
//
//  Note, the AKI extension has the following OID:
//  szOID_AUTHORITY_KEY_IDENTIFIER2 and its corresponding data structure.
//
//  If CRL_FIND_ISSUED_BY_SIGNATURE_FLAG is set in dwFindFlags, then,
//  uses the public key in the issuer's certificate to verify the
//  signature on the CRL. Only returns a CRL having a valid signature.
//--------------------------------------------------------------------------

const
  CRL_FIND_ISSUED_BY_AKI_FLAG       = $1;
  {$EXTERNALSYM CRL_FIND_ISSUED_BY_AKI_FLAG}
  CRL_FIND_ISSUED_BY_SIGNATURE_FLAG = $2;
  {$EXTERNALSYM CRL_FIND_ISSUED_BY_SIGNATURE_FLAG}

//+-------------------------------------------------------------------------
//  CRL_FIND_EXISTING
//
//  Find existing CRL in the store.
//
//  pvFindPara is the PCCRL_CONTEXT of the CRL to check if it already
//  exists in the store.
//--------------------------------------------------------------------------


//+-------------------------------------------------------------------------
//  Duplicate a CRL context
//--------------------------------------------------------------------------

function CertDuplicateCRLContext(pCrlContext: PCCRL_CONTEXT): PCCRL_CONTEXT; stdcall;
{$EXTERNALSYM CertDuplicateCRLContext}

//+-------------------------------------------------------------------------
//  Create a CRL context from the encoded CRL. The created
//  context isn't put in a store.
//
//  Makes a copy of the encoded CRL in the created context.
//
//  If unable to decode and create the CRL context, NULL is returned.
//  Otherwise, a pointer to a read only CRL_CONTEXT is returned.
//  CRL_CONTEXT must be freed by calling CertFreeCRLContext.
//  CertDuplicateCRLContext can be called to make a duplicate.
//
//  CertSetCRLContextProperty and CertGetCRLContextProperty can be called
//  to store properties for the CRL.
//--------------------------------------------------------------------------

function CertCreateCRLContext(dwCertEncodingType: DWORD; pbCrlEncoded: LPBYTE;
  cbCrlEncoded: DWORD): PCCRL_CONTEXT; stdcall;
{$EXTERNALSYM CertCreateCRLContext}

//+-------------------------------------------------------------------------
//  Free a CRL context
//
//  There needs to be a corresponding free for each context obtained by a
//  get, duplicate or create.
//--------------------------------------------------------------------------

function CertFreeCRLContext(pCrlContext: PCCRL_CONTEXT): BOOL; stdcall;
{$EXTERNALSYM CertFreeCRLContext}

//+-------------------------------------------------------------------------
//  Set the property for the specified CRL context.
//
//  Same Property Ids and semantics as CertSetCertificateContextProperty.
//--------------------------------------------------------------------------

function CertSetCRLContextProperty(pCrlContext: PCCRL_CONTEXT; dwPropId: DWORD;
  dwFlags: DWORD; pvData: Pointer): BOOL; stdcall;
{$EXTERNALSYM CertSetCRLContextProperty}

//+-------------------------------------------------------------------------
//  Get the property for the specified CRL context.
//
//  Same Property Ids and semantics as CertGetCertificateContextProperty.
//
//  CERT_SHA1_HASH_PROP_ID, CERT_MD5_HASH_PROP_ID or
//  CERT_SIGNATURE_HASH_PROP_ID is the predefined property of most interest.
//--------------------------------------------------------------------------

function CertGetCRLContextProperty(pCrlContext: PCCRL_CONTEXT; dwPropId: DWORD;
  pvData: Pointer; var pcbData: DWORD): BOOL; stdcall;
{$EXTERNALSYM CertGetCRLContextProperty}

//+-------------------------------------------------------------------------
//  Enumerate the properties for the specified CRL context.
//
//  To get the first property, set dwPropId to 0. The ID of the first
//  property is returned. To get the next property, set dwPropId to the
//  ID returned by the last call. To enumerate all the properties continue
//  until 0 is returned.
//
//  CertGetCRLContextProperty is called to get the property's data.
//--------------------------------------------------------------------------

function CertEnumCRLContextProperties(pCrlContext: PCCRL_CONTEXT;
  dwPropId: DWORD): DWORD; stdcall;
{$EXTERNALSYM CertEnumCRLContextProperties}

//+-------------------------------------------------------------------------
//  Search the CRL's list of entries for the specified certificate.
//
//  TRUE is returned if we were able to search the list. Otherwise, FALSE is
//  returned,
//
//  For success, if the certificate was found in the list, *ppCrlEntry is
//  updated with a pointer to the entry. Otherwise, *ppCrlEntry is set to NULL.
//  The returned entry isn't allocated and must not be freed.
//
//  dwFlags and pvReserved currently aren't used and must be set to 0 or NULL.
//--------------------------------------------------------------------------

function CertFindCertificateInCRL(pCert: PCCERT_CONTEXT; pCrlContext: PCCRL_CONTEXT;
  dwFlags: DWORD; pvReserved: Pointer; var ppCrlEntry: PCRL_ENTRY): BOOL; stdcall;
{$EXTERNALSYM CertFindCertificateInCRL}

//+-------------------------------------------------------------------------
// Add certificate/CRL, encoded, context or element disposition values.
//--------------------------------------------------------------------------

const
  CERT_STORE_ADD_NEW                                 = 1;
  {$EXTERNALSYM CERT_STORE_ADD_NEW}
  CERT_STORE_ADD_USE_EXISTING                        = 2;
  {$EXTERNALSYM CERT_STORE_ADD_USE_EXISTING}
  CERT_STORE_ADD_REPLACE_EXISTING                    = 3;
  {$EXTERNALSYM CERT_STORE_ADD_REPLACE_EXISTING}
  CERT_STORE_ADD_ALWAYS                              = 4;
  {$EXTERNALSYM CERT_STORE_ADD_ALWAYS}
  CERT_STORE_ADD_REPLACE_EXISTING_INHERIT_PROPERTIES = 5;
  {$EXTERNALSYM CERT_STORE_ADD_REPLACE_EXISTING_INHERIT_PROPERTIES}
  CERT_STORE_ADD_NEWER                               = 6;
  {$EXTERNALSYM CERT_STORE_ADD_NEWER}
  CERT_STORE_ADD_NEWER_INHERIT_PROPERTIES            = 7;
  {$EXTERNALSYM CERT_STORE_ADD_NEWER_INHERIT_PROPERTIES}

//+-------------------------------------------------------------------------
//  Add the encoded certificate to the store according to the specified
//  disposition action.
//
//  Makes a copy of the encoded certificate before adding to the store.
//
//  dwAddDispostion specifies the action to take if the certificate
//  already exists in the store. This parameter must be one of the following
//  values:
//    CERT_STORE_ADD_NEW
//      Fails if the certificate already exists in the store. LastError
//      is set to CRYPT_E_EXISTS.
//    CERT_STORE_ADD_USE_EXISTING
//      If the certifcate already exists, then, its used and if ppCertContext
//      is non-NULL, the existing context is duplicated.
//    CERT_STORE_ADD_REPLACE_EXISTING
//      If the certificate already exists, then, the existing certificate
//      context is deleted before creating and adding the new context.
//    CERT_STORE_ADD_ALWAYS
//      No check is made to see if the certificate already exists. A
//      new certificate context is always created. This may lead to
//      duplicates in the store.
//    CERT_STORE_ADD_REPLACE_EXISTING_INHERIT_PROPERTIES
//      If the certificate already exists, then, its used.
//    CERT_STORE_ADD_NEWER
//      Fails if the certificate already exists in the store AND the NotBefore
//      time of the existing certificate is equal to or greater than the
//      NotBefore time of the new certificate being added. LastError
//      is set to CRYPT_E_EXISTS.
//
//      If an older certificate is replaced, same as
//      CERT_STORE_ADD_REPLACE_EXISTING.
//
//      For CRLs or CTLs compares the ThisUpdate times.
//
//    CERT_STORE_ADD_NEWER_INHERIT_PROPERTIES
//      Same as CERT_STORE_ADD_NEWER. However, if an older certificate is
//      replaced, same as CERT_STORE_ADD_REPLACE_EXISTING_INHERIT_PROPERTIES.
//
//  CertGetSubjectCertificateFromStore is called to determine if the
//  certificate already exists in the store.
//
//  ppCertContext can be NULL, indicating the caller isn't interested
//  in getting the CERT_CONTEXT of the added or existing certificate.
//--------------------------------------------------------------------------

function CertAddEncodedCertificateToStore(hCertStore: HCERTSTORE;
  dwCertEncodingType: DWORD; pbCertEncoded: LPBYTE; cbCertEncoded: DWORD;
  dwAddDisposition: DWORD; ppCertContext: PPCCERT_CONTEXT): BOOL; stdcall;
{$EXTERNALSYM CertAddEncodedCertificateToStore}

//+-------------------------------------------------------------------------
//  Add the certificate context to the store according to the specified
//  disposition action.
//
//  In addition to the encoded certificate, the context's properties are
//  also copied.  Note, the CERT_KEY_CONTEXT_PROP_ID property (and its
//  CERT_KEY_PROV_HANDLE_PROP_ID or CERT_KEY_SPEC_PROP_ID) isn't copied.
//
//  Makes a copy of the certificate context before adding to the store.
//
//  dwAddDispostion specifies the action to take if the certificate
//  already exists in the store. This parameter must be one of the following
//  values:
//    CERT_STORE_ADD_NEW
//      Fails if the certificate already exists in the store. LastError
//      is set to CRYPT_E_EXISTS.
//    CERT_STORE_ADD_USE_EXISTING
//      If the certifcate already exists, then, its used and if ppStoreContext
//      is non-NULL, the existing context is duplicated. Iterates
//      through pCertContext's properties and only copies the properties
//      that don't already exist. The SHA1 and MD5 hash properties aren't
//      copied.
//    CERT_STORE_ADD_REPLACE_EXISTING
//      If the certificate already exists, then, the existing certificate
//      context is deleted before creating and adding a new context.
//      Properties are copied before doing the add.
//    CERT_STORE_ADD_ALWAYS
//      No check is made to see if the certificate already exists. A
//      new certificate context is always created and added. This may lead to
//      duplicates in the store. Properties are
//      copied before doing the add.
//    CERT_STORE_ADD_REPLACE_EXISTING_INHERIT_PROPERTIES
//      If the certificate already exists, then, the existing certificate
//      context is used. Properties from the added context are copied and
//      replace existing properties. However, any existing properties not
//      in the added context remain and aren't deleted.
//    CERT_STORE_ADD_NEWER
//      Fails if the certificate already exists in the store AND the NotBefore
//      time of the existing context is equal to or greater than the
//      NotBefore time of the new context being added. LastError
//      is set to CRYPT_E_EXISTS.
//
//      If an older context is replaced, same as
//      CERT_STORE_ADD_REPLACE_EXISTING.
//
//      For CRLs or CTLs compares the ThisUpdate times.
//
//    CERT_STORE_ADD_NEWER_INHERIT_PROPERTIES
//      Same as CERT_STORE_ADD_NEWER. However, if an older context is
//      replaced, same as CERT_STORE_ADD_REPLACE_EXISTING_INHERIT_PROPERTIES.
//
//  CertGetSubjectCertificateFromStore is called to determine if the
//  certificate already exists in the store.
//
//  ppStoreContext can be NULL, indicating the caller isn't interested
//  in getting the CERT_CONTEXT of the added or existing certificate.
//--------------------------------------------------------------------------

function CertAddCertificateContextToStore(hCertStore: HCERTSTORE;
  pCertContext: PCCERT_CONTEXT; dwAddDisposition: DWORD;
  ppStoreContext: PPCCERT_CONTEXT): BOOL; stdcall;
{$EXTERNALSYM CertAddCertificateContextToStore}

//+-------------------------------------------------------------------------
//  Certificate Store Context Types
//--------------------------------------------------------------------------

const
  CERT_STORE_CERTIFICATE_CONTEXT = 1;
  {$EXTERNALSYM CERT_STORE_CERTIFICATE_CONTEXT}
  CERT_STORE_CRL_CONTEXT         = 2;
  {$EXTERNALSYM CERT_STORE_CRL_CONTEXT}
  CERT_STORE_CTL_CONTEXT         = 3;
  {$EXTERNALSYM CERT_STORE_CTL_CONTEXT}

//+-------------------------------------------------------------------------
//  Certificate Store Context Bit Flags
//--------------------------------------------------------------------------

  CERT_STORE_ALL_CONTEXT_FLAG         = (not 0);
  {$EXTERNALSYM CERT_STORE_ALL_CONTEXT_FLAG}
  CERT_STORE_CERTIFICATE_CONTEXT_FLAG = (1 shl CERT_STORE_CERTIFICATE_CONTEXT);
  {$EXTERNALSYM CERT_STORE_CERTIFICATE_CONTEXT_FLAG}
  CERT_STORE_CRL_CONTEXT_FLAG         = (1 shl CERT_STORE_CRL_CONTEXT);
  {$EXTERNALSYM CERT_STORE_CRL_CONTEXT_FLAG}
  CERT_STORE_CTL_CONTEXT_FLAG         = (1 shl CERT_STORE_CTL_CONTEXT);
  {$EXTERNALSYM CERT_STORE_CTL_CONTEXT_FLAG}

//+-------------------------------------------------------------------------
//  Add the serialized certificate or CRL element to the store.
//
//  The serialized element contains the encoded certificate, CRL or CTL and
//  its properties, such as, CERT_KEY_PROV_INFO_PROP_ID.
//
//  If hCertStore is NULL, creates a certificate, CRL or CTL context not
//  residing in any store.
//
//  dwAddDispostion specifies the action to take if the certificate or CRL
//  already exists in the store. See CertAddCertificateContextToStore for a
//  list of and actions taken.
//
//  dwFlags currently isn't used and should be set to 0.
//
//  dwContextTypeFlags specifies the set of allowable contexts. For example, to
//  add either a certificate or CRL, set dwContextTypeFlags to:
//      CERT_STORE_CERTIFICATE_CONTEXT_FLAG | CERT_STORE_CRL_CONTEXT_FLAG
//
//  *pdwContextType is updated with the type of the context returned in
//  *ppvContxt. pdwContextType or ppvContext can be NULL, indicating the
//  caller isn't interested in getting the output. If *ppvContext is
//  returned it must be freed by calling CertFreeCertificateContext or
//  CertFreeCRLContext.
//--------------------------------------------------------------------------

function CertAddSerializedElementToStore(hCertStore: HCERTSTORE; pbElement: LPBYTE;
  cbElement, dwAddDisposition, dwFlags, dwContextTypeFlags: DWORD;
  pdwContextType: LPDWORD; ppvContext: PPointer): BOOL; stdcall;
{$EXTERNALSYM CertAddSerializedElementToStore}

//+-------------------------------------------------------------------------
//  Delete the specified certificate from the store.
//
//  All subsequent gets or finds for the certificate will fail. However,
//  memory allocated for the certificate isn't freed until all of its contexts
//  have also been freed.
//
//  The pCertContext is obtained from a get, enum, find or duplicate.
//
//  Some store provider implementations might also delete the issuer's CRLs
//  if this is the last certificate for the issuer in the store.
//
//  NOTE: the pCertContext is always CertFreeCertificateContext'ed by
//  this function, even for an error.
//--------------------------------------------------------------------------

function CertDeleteCertificateFromStore(pCertContext: PCCERT_CONTEXT): BOOL; stdcall;
{$EXTERNALSYM CertDeleteCertificateFromStore}

//+-------------------------------------------------------------------------
//  Add the encoded CRL to the store according to the specified
//  disposition option.
//
//  Makes a copy of the encoded CRL before adding to the store.
//
//  dwAddDispostion specifies the action to take if the CRL
//  already exists in the store. See CertAddEncodedCertificateToStore for a
//  list of and actions taken.
//
//  Compares the CRL's Issuer to determine if the CRL already exists in the
//  store.
//
//  ppCrlContext can be NULL, indicating the caller isn't interested
//  in getting the CRL_CONTEXT of the added or existing CRL.
//--------------------------------------------------------------------------

function CertAddEncodedCRLToStore(hCertStore: HCERTSTORE; dwCertEncodingType: DWORD;
  pbCrlEncoded: LPBYTE; cbCrlEncoded, dwAddDisposition: DWORD;
  ppCrlContext: PPCCRL_CONTEXT): BOOL; stdcall;
{$EXTERNALSYM CertAddEncodedCRLToStore}

//+-------------------------------------------------------------------------
//  Add the CRL context to the store according to the specified
//  disposition option.
//
//  In addition to the encoded CRL, the context's properties are
//  also copied.  Note, the CERT_KEY_CONTEXT_PROP_ID property (and its
//  CERT_KEY_PROV_HANDLE_PROP_ID or CERT_KEY_SPEC_PROP_ID) isn't copied.
//
//  Makes a copy of the encoded CRL before adding to the store.
//
//  dwAddDispostion specifies the action to take if the CRL
//  already exists in the store. See CertAddCertificateContextToStore for a
//  list of and actions taken.
//
//  Compares the CRL's Issuer, ThisUpdate and NextUpdate to determine
//  if the CRL already exists in the store.
//
//  ppStoreContext can be NULL, indicating the caller isn't interested
//  in getting the CRL_CONTEXT of the added or existing CRL.
//--------------------------------------------------------------------------

function CertAddCRLContextToStore(hCertStore: HCERTSTORE; pCrlContext: PCCRL_CONTEXT;
  dwAddDisposition: DWORD; ppStoreContext: PPCCRL_CONTEXT): BOOL; stdcall;
{$EXTERNALSYM CertAddCRLContextToStore}

//+-------------------------------------------------------------------------
//  Delete the specified CRL from the store.
//
//  All subsequent gets for the CRL will fail. However,
//  memory allocated for the CRL isn't freed until all of its contexts
//  have also been freed.
//
//  The pCrlContext is obtained from a get or duplicate.
//
//  NOTE: the pCrlContext is always CertFreeCRLContext'ed by
//  this function, even for an error.
//--------------------------------------------------------------------------

function CertDeleteCRLFromStore(pCrlContext: PCCRL_CONTEXT): BOOL; stdcall;
{$EXTERNALSYM CertDeleteCRLFromStore}

//+-------------------------------------------------------------------------
//  Serialize the certificate context's encoded certificate and its
//  properties.
//--------------------------------------------------------------------------

function CertSerializeCertificateStoreElement(pCertContext: PCCERT_CONTEXT;
  dwFlags: DWORD; pbElement: LPBYTE; var pcbElement: DWORD): BOOL; stdcall;
{$EXTERNALSYM CertSerializeCertificateStoreElement}

//+-------------------------------------------------------------------------
//  Serialize the CRL context's encoded CRL and its properties.
//--------------------------------------------------------------------------

function CertSerializeCRLStoreElement(pCrlContext: PCCRL_CONTEXT; dwFlags: DWORD;
  pbElement: LPBYTE; var pcbElement: DWORD): BOOL; stdcall;
{$EXTERNALSYM CertSerializeCRLStoreElement}

//+=========================================================================
//  Certificate Trust List (CTL) Store Data Structures and APIs
//==========================================================================

//+-------------------------------------------------------------------------
//  Duplicate a CTL context
//--------------------------------------------------------------------------

function CertDuplicateCTLContext(pCtlContext: PCCTL_CONTEXT): PCCTL_CONTEXT; stdcall;
{$EXTERNALSYM CertDuplicateCTLContext}

//+-------------------------------------------------------------------------
//  Create a CTL context from the encoded CTL. The created
//  context isn't put in a store.
//
//  Makes a copy of the encoded CTL in the created context.
//
//  If unable to decode and create the CTL context, NULL is returned.
//  Otherwise, a pointer to a read only CTL_CONTEXT is returned.
//  CTL_CONTEXT must be freed by calling CertFreeCTLContext.
//  CertDuplicateCTLContext can be called to make a duplicate.
//
//  CertSetCTLContextProperty and CertGetCTLContextProperty can be called
//  to store properties for the CTL.
//--------------------------------------------------------------------------

function CertCreateCTLContext(dwMsgAndCertEncodingType: DWORD;
  pbCtlEncoded: LPBYTE; cbCtlEncoded: DWORD): PCCTL_CONTEXT; stdcall;
{$EXTERNALSYM CertCreateCTLContext}

//+-------------------------------------------------------------------------
//  Free a CTL context
//
//  There needs to be a corresponding free for each context obtained by a
//  get, duplicate or create.
//--------------------------------------------------------------------------

function CertFreeCTLContext(pCtlContext: PCCTL_CONTEXT): BOOL; stdcall;
{$EXTERNALSYM CertFreeCTLContext}

//+-------------------------------------------------------------------------
//  Set the property for the specified CTL context.
//
//  Same Property Ids and semantics as CertSetCertificateContextProperty.
//--------------------------------------------------------------------------

function CertSetCTLContextProperty(pCtlContext: PCCTL_CONTEXT; dwPropId: DWORD;
  dwFlags: DWORD; pvData: Pointer): BOOL; stdcall;
{$EXTERNALSYM CertSetCTLContextProperty}

//+-------------------------------------------------------------------------
//  Get the property for the specified CTL context.
//
//  Same Property Ids and semantics as CertGetCertificateContextProperty.
//
//  CERT_SHA1_HASH_PROP_ID or CERT_NEXT_UPDATE_LOCATION_PROP_ID are the
//  predefined properties of most interest.
//--------------------------------------------------------------------------

function CertGetCTLContextProperty(pCtlContext: PCCTL_CONTEXT; dwPropId: DWORD;
  pvData: Pointer; var pcbData: DWORD): BOOL; stdcall;
{$EXTERNALSYM CertGetCTLContextProperty}

//+-------------------------------------------------------------------------
//  Enumerate the properties for the specified CTL context.
//--------------------------------------------------------------------------

function CertEnumCTLContextProperties(pCtlContext: PCCTL_CONTEXT; dwPropId: DWORD): DWORD; stdcall;
{$EXTERNALSYM CertEnumCTLContextProperties}

//+-------------------------------------------------------------------------
//  Enumerate the CTL contexts in the store.
//
//  If a CTL isn't found, NULL is returned.
//  Otherwise, a pointer to a read only CTL_CONTEXT is returned. CTL_CONTEXT
//  must be freed by calling CertFreeCTLContext or is freed when passed as the
//  pPrevCtlContext on a subsequent call. CertDuplicateCTLContext
//  can be called to make a duplicate.
//
//  pPrevCtlContext MUST BE NULL to enumerate the first
//  CTL in the store. Successive CTLs are enumerated by setting
//  pPrevCtlContext to the CTL_CONTEXT returned by a previous call.
//
//  NOTE: a NON-NULL pPrevCtlContext is always CertFreeCTLContext'ed by
//  this function, even for an error.
//--------------------------------------------------------------------------

function CertEnumCTLsInStore(hCertStore: HCERTSTORE; pPrevCtlContext: PCCTL_CONTEXT): PCCTL_CONTEXT; stdcall;
{$EXTERNALSYM CertEnumCTLsInStore}

//+-------------------------------------------------------------------------
//  Attempt to find the specified subject in the CTL.
//
//  For CTL_CERT_SUBJECT_TYPE, pvSubject points to a CERT_CONTEXT. The CTL's
//  SubjectAlgorithm is examined to determine the representation of the
//  subject's identity. Initially, only SHA1 or MD5 hash will be supported.
//  The appropriate hash property is obtained from the CERT_CONTEXT.
//
//  For CTL_ANY_SUBJECT_TYPE, pvSubject points to the CTL_ANY_SUBJECT_INFO
//  structure which contains the SubjectAlgorithm to be matched in the CTL
//  and the SubjectIdentifer to be matched in one of the CTL entries.
//
//  The certificate's hash or the CTL_ANY_SUBJECT_INFO's SubjectIdentifier
//  is used as the key in searching the subject entries. A binary
//  memory comparison is done between the key and the entry's SubjectIdentifer.
//
//  dwEncodingType isn't used for either of the above SubjectTypes.
//--------------------------------------------------------------------------

function CertFindSubjectInCTL(dwEncodingType: DWORD; dwSubjectType: DWORD;
  pvSubject: Pointer; pCtlContext: PCCTL_CONTEXT; dwFlags: DWORD): PCTL_ENTRY; stdcall;
{$EXTERNALSYM CertFindSubjectInCTL}

// Subject Types:
//  CTL_ANY_SUBJECT_TYPE, pvSubject points to following CTL_ANY_SUBJECT_INFO.
//  CTL_CERT_SUBJECT_TYPE, pvSubject points to CERT_CONTEXT.

const
  CTL_ANY_SUBJECT_TYPE  = 1;
  {$EXTERNALSYM CTL_ANY_SUBJECT_TYPE}
  CTL_CERT_SUBJECT_TYPE = 2;
  {$EXTERNALSYM CTL_CERT_SUBJECT_TYPE}

type
  PCTL_ANY_SUBJECT_INFO = ^CTL_ANY_SUBJECT_INFO;
  {$EXTERNALSYM PCTL_ANY_SUBJECT_INFO}
  _CTL_ANY_SUBJECT_INFO = record
    SubjectAlgorithm: CRYPT_ALGORITHM_IDENTIFIER;
    SubjectIdentifier: CRYPT_DATA_BLOB;
  end;
  {$EXTERNALSYM _CTL_ANY_SUBJECT_INFO}
  CTL_ANY_SUBJECT_INFO = _CTL_ANY_SUBJECT_INFO;
  {$EXTERNALSYM CTL_ANY_SUBJECT_INFO}
  TCtlAnySubjectInfo = CTL_ANY_SUBJECT_INFO;
  PCtlAnySubjectInfo = PCTL_ANY_SUBJECT_INFO;

//+-------------------------------------------------------------------------
//  Find the first or next CTL context in the store.
//
//  The CTL is found according to the dwFindType and its pvFindPara.
//  See below for a list of the find types and its parameters.
//
//  Currently dwFindFlags isn't used and must be set to 0.
//
//  Usage of dwMsgAndCertEncodingType depends on the dwFindType.
//
//  If the first or next CTL isn't found, NULL is returned.
//  Otherwise, a pointer to a read only CTL_CONTEXT is returned. CTL_CONTEXT
//  must be freed by calling CertFreeCTLContext or is freed when passed as the
//  pPrevCtlContext on a subsequent call. CertDuplicateCTLContext
//  can be called to make a duplicate.
//
//  pPrevCtlContext MUST BE NULL on the first
//  call to find the CTL. To find the next CTL, the
//  pPrevCtlContext is set to the CTL_CONTEXT returned by a previous call.
//
//  NOTE: a NON-NULL pPrevCtlContext is always CertFreeCTLContext'ed by
//  this function, even for an error.
//--------------------------------------------------------------------------

function CertFindCTLInStore(hCertStore: HCERTSTORE; dwMsgAndCertEncodingType,
  dwFindFlags, dwFindType: DWORD; pvFindPara: Pointer;
  pPrevCtlContext: PCCTL_CONTEXT): PCCTL_CONTEXT; stdcall;
{$EXTERNALSYM CertFindCTLInStore}

const
  CTL_FIND_ANY       = 0;
  {$EXTERNALSYM CTL_FIND_ANY}
  CTL_FIND_SHA1_HASH = 1;
  {$EXTERNALSYM CTL_FIND_SHA1_HASH}
  CTL_FIND_MD5_HASH  = 2;
  {$EXTERNALSYM CTL_FIND_MD5_HASH}
  CTL_FIND_USAGE     = 3;
  {$EXTERNALSYM CTL_FIND_USAGE}
  CTL_FIND_SUBJECT   = 4;
  {$EXTERNALSYM CTL_FIND_SUBJECT}
  CTL_FIND_EXISTING  = 5;
  {$EXTERNALSYM CTL_FIND_EXISTING}

type
  PCTL_FIND_USAGE_PARA = ^CTL_FIND_USAGE_PARA;
  {$EXTERNALSYM PCTL_FIND_USAGE_PARA}
  _CTL_FIND_USAGE_PARA = record
    cbSize: DWORD;
    SubjectUsage: CTL_USAGE; // optional
    ListIdentifier: CRYPT_DATA_BLOB; // optional
    pSigner: PCERT_INFO; // optional
  end;
  {$EXTERNALSYM _CTL_FIND_USAGE_PARA}
  CTL_FIND_USAGE_PARA = _CTL_FIND_USAGE_PARA;
  {$EXTERNALSYM CTL_FIND_USAGE_PARA}
  TCtlFindUsagePara = CTL_FIND_USAGE_PARA;
  PCtlFindUsagePara = PCTL_FIND_USAGE_PARA;

const
  CTL_FIND_NO_LIST_ID_CBDATA = DWORD($FFFFFFFF);
  {$EXTERNALSYM CTL_FIND_NO_LIST_ID_CBDATA}
  CTL_FIND_NO_SIGNER_PTR     = PCERT_INFO(-1);
  {$EXTERNALSYM CTL_FIND_NO_SIGNER_PTR}

  CTL_FIND_SAME_USAGE_FLAG = $1;
  {$EXTERNALSYM CTL_FIND_SAME_USAGE_FLAG}

type
  PCTL_FIND_SUBJECT_PARA = ^CTL_FIND_SUBJECT_PARA;
  {$EXTERNALSYM PCTL_FIND_SUBJECT_PARA}
  _CTL_FIND_SUBJECT_PARA = record
    cbSize: DWORD;
    pUsagePara: PCTL_FIND_USAGE_PARA; // optional
    dwSubjectType: DWORD;
    pvSubject: Pointer;
  end;
  {$EXTERNALSYM _CTL_FIND_SUBJECT_PARA}
  CTL_FIND_SUBJECT_PARA = _CTL_FIND_SUBJECT_PARA;
  {$EXTERNALSYM CTL_FIND_SUBJECT_PARA}
  TCtlFindSubjectPara = CTL_FIND_SUBJECT_PARA;
  PCtlFindSubjectPara = PCTL_FIND_SUBJECT_PARA;

//+-------------------------------------------------------------------------
//  CTL_FIND_ANY
//
//  Find any CTL.
//
//  pvFindPara isn't used.
//--------------------------------------------------------------------------

//+-------------------------------------------------------------------------
//  CTL_FIND_SHA1_HASH
//  CTL_FIND_MD5_HASH
//
//  Find a CTL with the specified hash.
//
//  pvFindPara points to a CRYPT_HASH_BLOB.
//--------------------------------------------------------------------------

//+-------------------------------------------------------------------------
//  CTL_FIND_USAGE
//
//  Find a CTL having the specified usage identifiers, list identifier or
//  signer. The CertEncodingType of the signer is obtained from the
//  dwMsgAndCertEncodingType parameter.
//
//  pvFindPara points to a CTL_FIND_USAGE_PARA data structure. The
//  SubjectUsage.cUsageIdentifer can be 0 to match any usage. The
//  ListIdentifier.cbData can be 0 to match any list identifier. To only match
//  CTLs without a ListIdentifier, cbData must be set to
//  CTL_FIND_NO_LIST_ID_CBDATA. pSigner can be NULL to match any signer. Only
//  the Issuer and SerialNumber fields of the pSigner's PCERT_INFO are used.
//  To only match CTLs without a signer, pSigner must be set to
//  CTL_FIND_NO_SIGNER_PTR.
//
//  The CTL_FIND_SAME_USAGE_FLAG can be set in dwFindFlags to
//  only match CTLs with the same usage identifiers. CTLs having additional
//  usage identifiers aren't matched. For example, if only "1.2.3" is specified
//  in CTL_FIND_USAGE_PARA, then, for a match, the CTL must only contain
//  "1.2.3" and not any additional usage identifers.
//--------------------------------------------------------------------------

//+-------------------------------------------------------------------------
//  CTL_FIND_SUBJECT
//
//  Find a CTL having the specified subject. CertFindSubjectInCTL can be
//  called to get a pointer to the subject's entry in the CTL.  pUsagePara can
//  optionally be set to enable the above CTL_FIND_USAGE matching.
//
//  pvFindPara points to a CTL_FIND_SUBJECT_PARA data structure.
//--------------------------------------------------------------------------

//+-------------------------------------------------------------------------
//  Add the encoded CTL to the store according to the specified
//  disposition option.
//
//  Makes a copy of the encoded CTL before adding to the store.
//
//  dwAddDispostion specifies the action to take if the CTL
//  already exists in the store. See CertAddEncodedCertificateToStore for a
//  list of and actions taken.
//
//  Compares the CTL's SubjectUsage, ListIdentifier and any of its signers
//  to determine if the CTL already exists in the store.
//
//  ppCtlContext can be NULL, indicating the caller isn't interested
//  in getting the CTL_CONTEXT of the added or existing CTL.
//--------------------------------------------------------------------------

function CertAddEncodedCTLToStore(hCertStore: HCERTSTORE;
  dwMsgAndCertEncodingType: DWORD; pbCtlEncoded: LPBYTE; cbCtlEncoded: DWORD;
  dwAddDisposition: DWORD; ppCtlContext: PPCCTL_CONTEXT): BOOL; stdcall;
{$EXTERNALSYM CertAddEncodedCTLToStore}

//+-------------------------------------------------------------------------
//  Add the CTL context to the store according to the specified
//  disposition option.
//
//  In addition to the encoded CTL, the context's properties are
//  also copied.  Note, the CERT_KEY_CONTEXT_PROP_ID property (and its
//  CERT_KEY_PROV_HANDLE_PROP_ID or CERT_KEY_SPEC_PROP_ID) isn't copied.
//
//  Makes a copy of the encoded CTL before adding to the store.
//
//  dwAddDispostion specifies the action to take if the CTL
//  already exists in the store. See CertAddCertificateContextToStore for a
//  list of and actions taken.
//
//  Compares the CTL's SubjectUsage, ListIdentifier and any of its signers
//  to determine if the CTL already exists in the store.
//
//  ppStoreContext can be NULL, indicating the caller isn't interested
//  in getting the CTL_CONTEXT of the added or existing CTL.
//--------------------------------------------------------------------------

function CertAddCTLContextToStore(hCertStore: HCERTSTORE; pCtlContext: PCCTL_CONTEXT;
  dwAddDisposition: DWORD; ppStoreContext: PPCCTL_CONTEXT): BOOL; stdcall;
{$EXTERNALSYM CertAddCTLContextToStore}

//+-------------------------------------------------------------------------
//  Serialize the CTL context's encoded CTL and its properties.
//--------------------------------------------------------------------------

function CertSerializeCTLStoreElement(pCtlContext: PCCTL_CONTEXT; dwFlags: DWORD;
  pbElement: LPBYTE; var pcbElement: DWORD): BOOL; stdcall;
{$EXTERNALSYM CertSerializeCTLStoreElement}

//+-------------------------------------------------------------------------
//  Delete the specified CTL from the store.
//
//  All subsequent gets for the CTL will fail. However,
//  memory allocated for the CTL isn't freed until all of its contexts
//  have also been freed.
//
//  The pCtlContext is obtained from a get or duplicate.
//
//  NOTE: the pCtlContext is always CertFreeCTLContext'ed by
//  this function, even for an error.
//--------------------------------------------------------------------------

function CertDeleteCTLFromStore(pCtlContext: PCCTL_CONTEXT): BOOL; stdcall;
{$EXTERNALSYM CertDeleteCTLFromStore}

function CertAddCertificateLinkToStore(hCertStore: HCERTSTORE;
  pCertContext: PCCERT_CONTEXT; dwAddDisposition: DWORD;
  ppStoreContext: PPCCERT_CONTEXT): BOOL; stdcall;
{$EXTERNALSYM CertAddCertificateLinkToStore}

function CertAddCRLLinkToStore(hCertStore: HCERTSTORE; pCrlContext: PCCRL_CONTEXT;
  dwAddDisposition: DWORD; ppStoreContext: PPCCRL_CONTEXT): BOOL; stdcall;
{$EXTERNALSYM CertAddCRLLinkToStore}

function CertAddCTLLinkToStore(hCertStore: HCERTSTORE; pCtlContext: PCCTL_CONTEXT;
  dwAddDisposition: DWORD; ppStoreContext: PPCCTL_CONTEXT): BOOL; stdcall;
{$EXTERNALSYM CertAddCTLLinkToStore}

function CertAddStoreToCollection(hCollectionStore: HCERTSTORE;
  hSiblingStore: HCERTSTORE; dwUpdateFlags, dwPriority: DWORD): BOOL; stdcall;
{$EXTERNALSYM CertAddStoreToCollection}

procedure CertRemoveStoreFromCollection(hCollectionStore, hSiblingStore: HCERTSTORE); stdcall;
{$EXTERNALSYM CertRemoveStoreFromCollection}

function CertControlStore(hCertStore: HCERTSTORE; dwFlags, dwCtrlType: DWORD;
  pvCtrlPara: Pointer): BOOL; stdcall;
{$EXTERNALSYM CertControlStore}

//+-------------------------------------------------------------------------
//  Certificate Store control types
//--------------------------------------------------------------------------

const
  CERT_STORE_CTRL_RESYNC        = 1;
  {$EXTERNALSYM CERT_STORE_CTRL_RESYNC}
  CERT_STORE_CTRL_NOTIFY_CHANGE = 2;
  {$EXTERNALSYM CERT_STORE_CTRL_NOTIFY_CHANGE}
  CERT_STORE_CTRL_COMMIT        = 3;
  {$EXTERNALSYM CERT_STORE_CTRL_COMMIT}
  CERT_STORE_CTRL_AUTO_RESYNC   = 4;
  {$EXTERNALSYM CERT_STORE_CTRL_AUTO_RESYNC}

//+-------------------------------------------------------------------------
//  CERT_STORE_CTRL_RESYNC
//
//  Re-synchronize the store.
//
//  The pvCtrlPara points to the event HANDLE to be signaled on
//  the next store change. Normally, this would be the same
//  event HANDLE passed to CERT_STORE_CTRL_NOTIFY_CHANGE during initialization.
//
//  If pvCtrlPara is NULL, no events are re-armed.
//--------------------------------------------------------------------------

//+-------------------------------------------------------------------------
//  CERT_STORE_CTRL_NOTIFY_CHANGE
//
//  Signal the event when the underlying store is changed.
//
//  pvCtrlPara points to the event HANDLE to be signaled.
//
//  pvCtrlPara can be NULL to inform the store of a subsequent
//  CERT_STORE_CTRL_RESYNC and allow it to optimize by only doing a resync
//  if the store has changed. For the registry based stores, an internal
//  notify change event is created and registered to be signaled.
//
//  Recommend calling CERT_STORE_CTRL_NOTIFY_CHANGE once for each event to
//  be passed to CERT_STORE_CTRL_RESYNC. This should only happen after
//  the event has been created. Not after each time the event is signaled.
//--------------------------------------------------------------------------

//+-------------------------------------------------------------------------
//  CERT_STORE_CTRL_AUTO_RESYNC
//
//  At the start of every enumeration or find store API call, check if the
//  underlying store has changed. If it has changed, re-synchronize.
//
//  This check is only done in the enumeration or find APIs when the
//  pPrevContext is NULL.
//
//  The pvCtrlPara isn't used and must be set to NULL.
//--------------------------------------------------------------------------

//+-------------------------------------------------------------------------
//  CERT_STORE_CTRL_COMMIT
//
//  If any changes have been to the cached store, they are committed to
//  persisted storage. If no changes have been made since the store was
//  opened or the last commit, this call is ignored. May also be ignored by
//  store providers that persist changes immediately.
//
//  CERT_STORE_CTRL_COMMIT_FORCE_FLAG can be set to force the store
//  to be committed even if it hasn't been touched.
//
//  CERT_STORE_CTRL_COMMIT_CLEAR_FLAG can be set to inhibit a commit on
//  store close.
//--------------------------------------------------------------------------

const
  CERT_STORE_CTRL_COMMIT_FORCE_FLAG = $1;
  {$EXTERNALSYM CERT_STORE_CTRL_COMMIT_FORCE_FLAG}
  CERT_STORE_CTRL_COMMIT_CLEAR_FLAG = $2;
  {$EXTERNALSYM CERT_STORE_CTRL_COMMIT_CLEAR_FLAG}

//+=========================================================================
//  Cert Store Property Defines and APIs
//==========================================================================

//+-------------------------------------------------------------------------
//  Store property IDs. This is a property applicable to the entire store.
//  Its not a property on an individual certificate, CRL or CTL context.
//
//  Currently, no store properties are persisted. (This differs from
//  most context properties which are persisted.)
//
//  See CertSetStoreProperty or CertGetStoreProperty for usage information.
//
//  Note, the range for predefined store properties should be outside
//  the range of predefined context properties. We will start at 4096.
//--------------------------------------------------------------------------

  CERT_STORE_LOCALIZED_NAME_PROP_ID = $1000;
  {$EXTERNALSYM CERT_STORE_LOCALIZED_NAME_PROP_ID}

//+-------------------------------------------------------------------------
//  Set a store property.
//
//  The type definition for pvData depends on the dwPropId value.
//      CERT_STORE_LOCALIZED_NAME_PROP_ID - localized name of the store.
//      pvData points to a CRYPT_DATA_BLOB. pbData is a pointer to a NULL
//      terminated unicode, wide character string.
//      cbData = (wcslen((LPWSTR) pbData) + 1) * sizeof(WCHAR).
//
//  For all the other PROP_IDs: an encoded PCRYPT_DATA_BLOB is passed in pvData.
//
//  If the property already exists, then, the old value is deleted and silently
//  replaced. Setting, pvData to NULL, deletes the property.
//--------------------------------------------------------------------------

function CertSetStoreProperty(hCertStore: HCERTSTORE; dwPropId, dwFlags: DWORD;
  pvData: Pointer): BOOL; stdcall;
{$EXTERNALSYM CertSetStoreProperty}

//+-------------------------------------------------------------------------
//  Get a store property.
//
//  The type definition for pvData depends on the dwPropId value.
//      CERT_STORE_LOCALIZED_NAME_PROP_ID - localized name of the store.
//      pvData points to a NULL terminated unicode, wide character string.
//      cbData = (wcslen((LPWSTR) pvData) + 1) * sizeof(WCHAR).
//
//  For all other PROP_IDs, pvData points to an array of bytes.
//
//  If the property doesn't exist, returns FALSE and sets LastError to
//  CRYPT_E_NOT_FOUND.
//--------------------------------------------------------------------------

function CertGetStoreProperty(hCertStore: HCERTSTORE; dwPropId: DWORD;
  pvData: Pointer; var pcbData: DWORD): BOOL; stdcall;
{$EXTERNALSYM CertGetStoreProperty}

type
  PCERT_CREATE_CONTEXT_PARA = ^CERT_CREATE_CONTEXT_PARA;
  {$EXTERNALSYM PCERT_CREATE_CONTEXT_PARA}
  _CERT_CREATE_CONTEXT_PARA = record
    cbSize: DWORD;
    pfnFree: PFN_CRYPT_FREE; // OPTIONAL
    pvFree: Pointer; // OPTIONAL
  end;
  {$EXTERNALSYM _CERT_CREATE_CONTEXT_PARA}
  CERT_CREATE_CONTEXT_PARA = _CERT_CREATE_CONTEXT_PARA;
  {$EXTERNALSYM CERT_CREATE_CONTEXT_PARA}
  TCertCreateContextPara = CERT_CREATE_CONTEXT_PARA;
  PCertCreateContextPara = PCERT_CREATE_CONTEXT_PARA;

//+-------------------------------------------------------------------------
//  Creates the specified context from the encoded bytes. The created
//  context isn't put in a store.
//
//  dwContextType values:
//      CERT_STORE_CERTIFICATE_CONTEXT
//      CERT_STORE_CRL_CONTEXT
//      CERT_STORE_CTL_CONTEXT
//
//  If CERT_CREATE_CONTEXT_NOCOPY_FLAG is set, the created context points
//  directly to the pbEncoded instead of an allocated copy. See flag
//  definition for more details.
//
//  If CERT_CREATE_CONTEXT_SORTED_FLAG is set, the context is created
//  with sorted entries. This flag may only be set for CERT_STORE_CTL_CONTEXT.
//  Setting this flag implicitly sets CERT_CREATE_CONTEXT_NO_HCRYPTMSG_FLAG and
//  CERT_CREATE_CONTEXT_NO_ENTRY_FLAG. See flag definition for
//  more details.
//
//  If CERT_CREATE_CONTEXT_NO_HCRYPTMSG_FLAG is set, the context is created
//  without creating a HCRYPTMSG handle for the context. This flag may only be
//  set for CERT_STORE_CTL_CONTEXT.  See flag definition for more details.
//
//  If CERT_CREATE_CONTEXT_NO_ENTRY_FLAG is set, the context is created
//  without decoding the entries. This flag may only be set for
//  CERT_STORE_CTL_CONTEXT.  See flag definition for more details.
//
//  If unable to decode and create the context, NULL is returned.
//  Otherwise, a pointer to a read only CERT_CONTEXT, CRL_CONTEXT or
//  CTL_CONTEXT is returned. The context must be freed by the appropriate
//  free context API. The context can be duplicated by calling the
//  appropriate duplicate context API.
//--------------------------------------------------------------------------

function CertCreateContext(dwContextType, dwEncodingType: DWORD;
  pbEncoded: LPBYTE; cbEncoded, dwFlags: DWORD;
  pCreatePara: PCERT_CREATE_CONTEXT_PARA): Pointer; stdcall;
{$EXTERNALSYM CertCreateContext}

// When the following flag is set, the created context points directly to the
// pbEncoded instead of an allocated copy. If pCreatePara and
// pCreatePara->pfnFree are non-NULL, then, pfnFree is called to free
// the pbEncoded when the context is last freed. Otherwise, no attempt is
// made to free the pbEncoded. If pCreatePara->pvFree is non-NULL, then its
// passed to pfnFree instead of pbEncoded.
//
// Note, if CertCreateContext fails, pfnFree is still called.

const
  CERT_CREATE_CONTEXT_NOCOPY_FLAG = $1;
  {$EXTERNALSYM CERT_CREATE_CONTEXT_NOCOPY_FLAG}

// When the following flag is set, a context with sorted entries is created.
// Currently only applicable to a CTL context.
//
// For CTLs: the cCTLEntry in the returned CTL_INFO is always
// 0. CertFindSubjectInSortedCTL and CertEnumSubjectInSortedCTL must be called
// to find or enumerate the CTL entries.
//
// The Sorted CTL TrustedSubjects extension isn't returned in the created
// context's CTL_INFO.

  CERT_CREATE_CONTEXT_SORTED_FLAG = $2;
  {$EXTERNALSYM CERT_CREATE_CONTEXT_SORTED_FLAG}

// By default when a CTL context is created, a HCRYPTMSG handle to its
// SignedData message is created. This flag can be set to improve performance
// by not creating the HCRYPTMSG handle.
//
// This flag is only applicable to a CTL context.

  CERT_CREATE_CONTEXT_NO_HCRYPTMSG_FLAG = $4;
  {$EXTERNALSYM CERT_CREATE_CONTEXT_NO_HCRYPTMSG_FLAG}

// By default when a CTL context is created, its entries are decoded.
// This flag can be set to improve performance by not decoding the
// entries.
//
// This flag is only applicable to a CTL context.

  CERT_CREATE_CONTEXT_NO_ENTRY_FLAG = $8;
  {$EXTERNALSYM CERT_CREATE_CONTEXT_NO_ENTRY_FLAG}

//+=========================================================================
//  Certificate System Store Data Structures and APIs
//==========================================================================

//+-------------------------------------------------------------------------
//  System Store Information
//
//  Currently, no system store information is persisted.
//--------------------------------------------------------------------------

type
  PCERT_SYSTEM_STORE_INFO = ^CERT_SYSTEM_STORE_INFO;
  {$EXTERNALSYM PCERT_SYSTEM_STORE_INFO}
  _CERT_SYSTEM_STORE_INFO = record
    cbSize: DWORD;
  end;
  {$EXTERNALSYM _CERT_SYSTEM_STORE_INFO}
  CERT_SYSTEM_STORE_INFO = _CERT_SYSTEM_STORE_INFO;
  {$EXTERNALSYM CERT_SYSTEM_STORE_INFO}
  TCertSystemStoreInfo = CERT_SYSTEM_STORE_INFO;
  PCertSystemStoreInfo = PCERT_SYSTEM_STORE_INFO;

//+-------------------------------------------------------------------------
//  Physical Store Information
//
//  The Open fields are passed directly to CertOpenStore() to open
//  the physical store.
//
//  By default all system stores located in the registry have an
//  implicit SystemRegistry physical store that is opened. To disable the
//  opening of this store, the SystemRegistry
//  physical store corresponding to the System store must be registered with
//  CERT_PHYSICAL_STORE_OPEN_DISABLE_FLAG set in dwFlags. Alternatively,
//  a physical store with the name of ".Default" may be registered.
//
//  Depending on the store location and store name, additional predefined
//  physical stores may be opened. For example, system stores in
//  CURRENT_USER have the predefined physical store, .LocalMachine.
//  To disable the opening of these predefined physical stores, the
//  corresponding physical store must be registered with
//  CERT_PHYSICAL_STORE_OPEN_DISABLE_FLAG set in dwFlags.
//
//  The CERT_PHYSICAL_STORE_ADD_ENABLE_FLAG must be set in dwFlags
//  to enable the adding of a context to the store.
//
//  When a system store is opened via the SERVICES or USERS store location,
//  the ServiceName\ is prepended to the OpenParameters
//  for CERT_SYSTEM_STORE_CURRENT_USER or CERT_SYSTEM_STORE_CURRENT_SERVICE
//  physical stores and the dwOpenFlags store location is changed to
//  CERT_SYSTEM_STORE_USERS or CERT_SYSTEM_STORE_SERVICES.
//
//  By default the SYSTEM, SYSTEM_REGISTRY and PHYSICAL provider
//  stores are also opened remotely when the outer system store is opened.
//  The CERT_PHYSICAL_STORE_REMOTE_OPEN_DISABLE_FLAG may be set in dwFlags
//  to disable remote opens.
//
//  When opened remotely, the \\ComputerName is implicitly prepended to the
//  OpenParameters for the SYSTEM, SYSTEM_REGISTRY and PHYSICAL provider types.
//  To also prepend the \\ComputerName to other provider types, set the
//  CERT_PHYSICAL_STORE_INSERT_COMPUTER_NAME_ENABLE_FLAG in dwFlags.
//
//  When the system store is opened, its physical stores are ordered
//  according to the dwPriority. A larger dwPriority indicates higher priority.
//--------------------------------------------------------------------------

type
  PCERT_PHYSICAL_STORE_INFO = ^CERT_PHYSICAL_STORE_INFO;
  {$EXTERNALSYM PCERT_PHYSICAL_STORE_INFO}
  _CERT_PHYSICAL_STORE_INFO = record
    cbSize: DWORD;
    pszOpenStoreProvider: LPSTR; // REG_SZ
    dwOpenEncodingType: DWORD; // REG_DWORD
    dwOpenFlags: DWORD; // REG_DWORD
    OpenParameters: CRYPT_DATA_BLOB; // REG_BINARY
    dwFlags: DWORD; // REG_DWORD
    dwPriority: DWORD; // REG_DWORD
  end;
  {$EXTERNALSYM _CERT_PHYSICAL_STORE_INFO}
  CERT_PHYSICAL_STORE_INFO = _CERT_PHYSICAL_STORE_INFO;
  {$EXTERNALSYM CERT_PHYSICAL_STORE_INFO}
  TCertPhysicalStoreInfo = CERT_PHYSICAL_STORE_INFO;
  PCertPhysicalStoreInfo = PCERT_PHYSICAL_STORE_INFO;

//+-------------------------------------------------------------------------
//  Physical Store Information dwFlags
//--------------------------------------------------------------------------

const
  CERT_PHYSICAL_STORE_ADD_ENABLE_FLAG                  = $1;
  {$EXTERNALSYM CERT_PHYSICAL_STORE_ADD_ENABLE_FLAG}
  CERT_PHYSICAL_STORE_OPEN_DISABLE_FLAG                = $2;
  {$EXTERNALSYM CERT_PHYSICAL_STORE_OPEN_DISABLE_FLAG}
  CERT_PHYSICAL_STORE_REMOTE_OPEN_DISABLE_FLAG         = $4;
  {$EXTERNALSYM CERT_PHYSICAL_STORE_REMOTE_OPEN_DISABLE_FLAG}
  CERT_PHYSICAL_STORE_INSERT_COMPUTER_NAME_ENABLE_FLAG = $8;
  {$EXTERNALSYM CERT_PHYSICAL_STORE_INSERT_COMPUTER_NAME_ENABLE_FLAG}

//+-------------------------------------------------------------------------
//  Register a system store.
//
//  The upper word of the dwFlags parameter is used to specify the location of
//  the system store.
//
//  If CERT_SYSTEM_STORE_RELOCATE_FLAG is set in dwFlags, pvSystemStore
//  points to a CERT_SYSTEM_STORE_RELOCATE_PARA data structure. Otherwise,
//  pvSystemStore points to a null terminated UNICODE string.
//
//  The CERT_SYSTEM_STORE_SERVICES or CERT_SYSTEM_STORE_USERS system store
//  name must be prefixed with the ServiceName or UserName. For example,
//  "ServiceName\Trust".
//
//  Stores on remote computers can be registered for the
//  CERT_SYSTEM_STORE_LOCAL_MACHINE, CERT_SYSTEM_STORE_SERVICES,
//  CERT_SYSTEM_STORE_USERS, CERT_SYSTEM_STORE_LOCAL_MACHINE_GROUP_POLICY
//  or CERT_SYSTEM_STORE_LOCAL_MACHINE_ENTERPRISE
//  locations by prepending the computer name. For example, a remote
//  local machine store is registered via "\\ComputerName\Trust" or
//  "ComputerName\Trust". A remote service store is registered via
//  "\\ComputerName\ServiceName\Trust". The leading "\\" backslashes are
//  optional in the ComputerName.
//
//  Set CERT_STORE_CREATE_NEW_FLAG to cause a failure if the system store
//  already exists in the store location.
//--------------------------------------------------------------------------

function CertRegisterSystemStore(pvSystemStore: Pointer; dwFlags: DWORD;
  pStoreInfo: PCERT_SYSTEM_STORE_INFO; pvReserved: Pointer): BOOL; stdcall;
{$EXTERNALSYM CertRegisterSystemStore}

//+-------------------------------------------------------------------------
//  Register a physical store for the specified system store.
//
//  The upper word of the dwFlags parameter is used to specify the location of
//  the system store.
//
//  If CERT_SYSTEM_STORE_RELOCATE_FLAG is set in dwFlags, pvSystemStore
//  points to a CERT_SYSTEM_STORE_RELOCATE_PARA data structure. Otherwise,
//  pvSystemStore points to a null terminated UNICODE string.
//
//  See CertRegisterSystemStore for details on prepending a ServiceName
//  and/or ComputerName to the system store name.
//
//  Set CERT_STORE_CREATE_NEW_FLAG to cause a failure if the physical store
//  already exists in the system store.
//--------------------------------------------------------------------------

function CertRegisterPhysicalStore(pvSystemStore: Pointer; dwFlags: DWORD;
  pwszStoreName: LPCWSTR; pStoreInfo: PCERT_PHYSICAL_STORE_INFO;
  pvReserved: Pointer): BOOL; stdcall;
{$EXTERNALSYM CertRegisterPhysicalStore}

//+-------------------------------------------------------------------------
//  Unregister the specified system store.
//
//  The upper word of the dwFlags parameter is used to specify the location of
//  the system store.
//
//  If CERT_SYSTEM_STORE_RELOCATE_FLAG is set in dwFlags, pvSystemStore
//  points to a CERT_SYSTEM_STORE_RELOCATE_PARA data structure. Otherwise,
//  pvSystemStore points to a null terminated UNICODE string.
//
//  See CertRegisterSystemStore for details on prepending a ServiceName
//  and/or ComputerName to the system store name.
//
//  CERT_STORE_DELETE_FLAG can optionally be set in dwFlags.
//--------------------------------------------------------------------------

function CertUnregisterSystemStore(pvSystemStore: Pointer; dwFlags: DWORD): BOOL; stdcall;
{$EXTERNALSYM CertUnregisterSystemStore}

//+-------------------------------------------------------------------------
//  Unregister the physical store from the specified system store.
//
//  The upper word of the dwFlags parameter is used to specify the location of
//  the system store.
//
//  If CERT_SYSTEM_STORE_RELOCATE_FLAG is set in dwFlags, pvSystemStore
//  points to a CERT_SYSTEM_STORE_RELOCATE_PARA data structure. Otherwise,
//  pvSystemStore points to a null terminated UNICODE string.
//
//  See CertRegisterSystemStore for details on prepending a ServiceName
//  and/or ComputerName to the system store name.
//
//  CERT_STORE_DELETE_FLAG can optionally be set in dwFlags.
//--------------------------------------------------------------------------

function CertUnregisterPhysicalStore(pvSystemStore: Pointer; dwFlags: DWORD;
  pwszStoreName: LPCWSTR): BOOL; stdcall;
{$EXTERNALSYM CertUnregisterPhysicalStore}

//+-------------------------------------------------------------------------
//  Enum callbacks
//
//  The CERT_SYSTEM_STORE_LOCATION_MASK bits in the dwFlags parameter
//  specifies the location of the system store
//
//  If CERT_SYSTEM_STORE_RELOCATE_FLAG is set in dwFlags, pvSystemStore
//  points to a CERT_SYSTEM_STORE_RELOCATE_PARA data structure. Otherwise,
//  pvSystemStore points to a null terminated UNICODE string.
//
//  The callback returns FALSE and sets LAST_ERROR to stop the enumeration.
//  The LAST_ERROR is returned to the caller of the enumeration.
//
//  The pvSystemStore passed to the callback has leading ComputerName and/or
//  ServiceName prefixes where appropriate.
//--------------------------------------------------------------------------

type
  PFN_CERT_ENUM_SYSTEM_STORE_LOCATION = function (pwszStoreLocation: LPCWSTR;
    dwFlags: DWORD; pvReserved: Pointer; pvArg: Pointer): BOOL; stdcall;
  {$EXTERNALSYM PFN_CERT_ENUM_SYSTEM_STORE_LOCATION}
  PfnCertEnumSystemStoreLocation = PFN_CERT_ENUM_SYSTEM_STORE_LOCATION;

  PFN_CERT_ENUM_SYSTEM_STORE = function (pvSystemStore: Pointer;
    dwFlags: DWORD; pStoreInfo: PCERT_SYSTEM_STORE_INFO; pvReserved: Pointer;
    pvArg: Pointer): BOOL; stdcall;
  {$EXTERNALSYM PFN_CERT_ENUM_SYSTEM_STORE}
  PfnCertEnumSystemStore = PFN_CERT_ENUM_SYSTEM_STORE;

  PFN_CERT_ENUM_PHYSICAL_STORE = function (pvSystemStore: Pointer;
    dwFlags: DWORD; pwszStoreName: LPCWSTR; pStoreInfo: PCERT_PHYSICAL_STORE_INFO;
    pvReserved: Pointer; pvArg: Pointer): BOOL; stdcall;
  {$EXTERNALSYM PFN_CERT_ENUM_PHYSICAL_STORE}
  PfnCertEnumPhysicalStore = PFN_CERT_ENUM_PHYSICAL_STORE;

// In the PFN_CERT_ENUM_PHYSICAL_STORE callback the following flag is
// set if the physical store wasn't registered and is an implicitly created
// predefined physical store.

const
  CERT_PHYSICAL_STORE_PREDEFINED_ENUM_FLAG = $1;
  {$EXTERNALSYM CERT_PHYSICAL_STORE_PREDEFINED_ENUM_FLAG}

// Names of implicitly created predefined physical stores

  CERT_PHYSICAL_STORE_DEFAULT_NAME                    = '.Default';
  {$EXTERNALSYM CERT_PHYSICAL_STORE_DEFAULT_NAME}
  CERT_PHYSICAL_STORE_GROUP_POLICY_NAME               = '.GroupPolicy';
  {$EXTERNALSYM CERT_PHYSICAL_STORE_GROUP_POLICY_NAME}
  CERT_PHYSICAL_STORE_LOCAL_MACHINE_NAME              = '.LocalMachine';
  {$EXTERNALSYM CERT_PHYSICAL_STORE_LOCAL_MACHINE_NAME}
  CERT_PHYSICAL_STORE_DS_USER_CERTIFICATE_NAME        = '.UserCertificate';
  {$EXTERNALSYM CERT_PHYSICAL_STORE_DS_USER_CERTIFICATE_NAME}
  CERT_PHYSICAL_STORE_LOCAL_MACHINE_GROUP_POLICY_NAME = '.LocalMachineGroupPolicy';
  {$EXTERNALSYM CERT_PHYSICAL_STORE_LOCAL_MACHINE_GROUP_POLICY_NAME}
  CERT_PHYSICAL_STORE_ENTERPRISE_NAME                 = '.Enterprise';
  {$EXTERNALSYM CERT_PHYSICAL_STORE_ENTERPRISE_NAME}

//+-------------------------------------------------------------------------
//  Enumerate the system store locations.
//--------------------------------------------------------------------------

function CertEnumSystemStoreLocation(dwFlags: DWORD; pvArg: Pointer;
  pfnEnum: PFN_CERT_ENUM_SYSTEM_STORE_LOCATION): BOOL; stdcall;
{$EXTERNALSYM CertEnumSystemStoreLocation}

//+-------------------------------------------------------------------------
//  Enumerate the system stores.
//
//  The upper word of the dwFlags parameter is used to specify the location of
//  the system store.
//
//  If CERT_SYSTEM_STORE_RELOCATE_FLAG is set in dwFlags,
//  pvSystemStoreLocationPara points to a CERT_SYSTEM_STORE_RELOCATE_PARA
//  data structure. Otherwise, pvSystemStoreLocationPara points to a null
//  terminated UNICODE string.
//
//  For CERT_SYSTEM_STORE_LOCAL_MACHINE,
//  CERT_SYSTEM_STORE_LOCAL_MACHINE_GROUP_POLICY or
//  CERT_SYSTEM_STORE_LOCAL_MACHINE_ENTERPRISE, pvSystemStoreLocationPara can
//  optionally be set to a unicode computer name for enumerating local machine
//  stores on a remote computer. For example, "\\ComputerName" or
//  "ComputerName".  The leading "\\" backslashes are optional in the
//  ComputerName.
//
//  For CERT_SYSTEM_STORE_SERVICES or CERT_SYSTEM_STORE_USERS,
//  if pvSystemStoreLocationPara is NULL, then,
//  enumerates both the service/user names and the stores for each service/user
//  name. Otherwise, pvSystemStoreLocationPara is a unicode string specifying a
//  remote computer name and/or service/user name. For example:
//      "ServiceName"
//      "\\ComputerName" or "ComputerName\"
//      "ComputerName\ServiceName"
//  Note, if only the ComputerName is specified, then, it must have either
//  the leading "\\" backslashes or a trailing backslash. Otherwise, its
//  interpretted as the ServiceName or UserName.
//--------------------------------------------------------------------------

function CertEnumSystemStore(dwFlags: DWORD; pvSystemStoreLocationPara: Pointer;
  pvArg: Pointer; pfnEnum: PFN_CERT_ENUM_SYSTEM_STORE): BOOL; stdcall;
{$EXTERNALSYM CertEnumSystemStore}

//+-------------------------------------------------------------------------
//  Enumerate the physical stores for the specified system store.
//
//  The upper word of the dwFlags parameter is used to specify the location of
//  the system store.
//
//  If CERT_SYSTEM_STORE_RELOCATE_FLAG is set in dwFlags, pvSystemStore
//  points to a CERT_SYSTEM_STORE_RELOCATE_PARA data structure. Otherwise,
//  pvSystemStore points to a null terminated UNICODE string.
//
//  See CertRegisterSystemStore for details on prepending a ServiceName
//  and/or ComputerName to the system store name.
//
//  If the system store location only supports system stores and doesn't
//  support physical stores, LastError is set to ERROR_CALL_NOT_IMPLEMENTED.
//--------------------------------------------------------------------------

function CertEnumPhysicalStore(pvSystemStore: Pointer; dwFlags: DWORD;
  pvArg: Pointer; pfnEnum: PFN_CERT_ENUM_PHYSICAL_STORE): BOOL; stdcall;
{$EXTERNALSYM CertEnumPhysicalStore}

//+-------------------------------------------------------------------------
//  Certificate System Store Installable Functions
//
//  The CERT_SYSTEM_STORE_LOCATION_MASK bits in the dwFlags parameter passed
//  to the CertOpenStore(for "System", "SystemRegistry" or "Physical"
//  Provider), CertRegisterSystemStore,
//  CertUnregisterSystemStore, CertEnumSystemStore, CertRegisterPhysicalStore,
//  CertUnregisterPhysicalStore and CertEnumPhysicalStore APIs is used as the
//  constant pszOID value passed to the OID installable functions.
//  Therefore, the pszOID is restricted to a constant <= (LPCSTR) 0x0FFF.
//
//  The EncodingType is 0.
//--------------------------------------------------------------------------

// Installable System Store Provider OID pszFuncNames.

const
  CRYPT_OID_OPEN_SYSTEM_STORE_PROV_FUNC    = 'CertDllOpenSystemStoreProv';
  {$EXTERNALSYM CRYPT_OID_OPEN_SYSTEM_STORE_PROV_FUNC}
  CRYPT_OID_REGISTER_SYSTEM_STORE_FUNC     = 'CertDllRegisterSystemStore';
  {$EXTERNALSYM CRYPT_OID_REGISTER_SYSTEM_STORE_FUNC}
  CRYPT_OID_UNREGISTER_SYSTEM_STORE_FUNC   = 'CertDllUnregisterSystemStore';
  {$EXTERNALSYM CRYPT_OID_UNREGISTER_SYSTEM_STORE_FUNC}
  CRYPT_OID_ENUM_SYSTEM_STORE_FUNC         = 'CertDllEnumSystemStore';
  {$EXTERNALSYM CRYPT_OID_ENUM_SYSTEM_STORE_FUNC}
  CRYPT_OID_REGISTER_PHYSICAL_STORE_FUNC   = 'CertDllRegisterPhysicalStore';
  {$EXTERNALSYM CRYPT_OID_REGISTER_PHYSICAL_STORE_FUNC}
  CRYPT_OID_UNREGISTER_PHYSICAL_STORE_FUNC = 'CertDllUnregisterPhysicalStore';
  {$EXTERNALSYM CRYPT_OID_UNREGISTER_PHYSICAL_STORE_FUNC}
  CRYPT_OID_ENUM_PHYSICAL_STORE_FUNC       = 'CertDllEnumPhysicalStore';
  {$EXTERNALSYM CRYPT_OID_ENUM_PHYSICAL_STORE_FUNC}

// CertDllOpenSystemStoreProv has the same function signature as the
// installable "CertDllOpenStoreProv" function. See CertOpenStore for
// more details.

// CertDllRegisterSystemStore has the same function signature as
// CertRegisterSystemStore.
//
// The "SystemStoreLocation" REG_SZ value must also be set for registered
// CertDllEnumSystemStore OID functions.

  CRYPT_OID_SYSTEM_STORE_LOCATION_VALUE_NAME = 'SystemStoreLocation';
  {$EXTERNALSYM CRYPT_OID_SYSTEM_STORE_LOCATION_VALUE_NAME}

// The remaining Register, Enum and Unregister OID installable functions
// have the same signature as their Cert Store API counterpart.


//+=========================================================================
//  Enhanced Key Usage Helper Functions
//==========================================================================

//+-------------------------------------------------------------------------
//  Get the enhanced key usage extension or property from the certificate
//  and decode.
//
//  If the CERT_FIND_EXT_ONLY_ENHKEY_USAGE_FLAG is set, then, only get the
//  extension.
//
//  If the CERT_FIND_PROP_ONLY_ENHKEY_USAGE_FLAG is set, then, only get the
//  property.
//--------------------------------------------------------------------------

function CertGetEnhancedKeyUsage(pCertContext: PCCERT_CONTEXT; dwFlags: DWORD;
  pUsage: PCERT_ENHKEY_USAGE; var pcbUsage: DWORD): BOOL; stdcall;
{$EXTERNALSYM CertGetEnhancedKeyUsage}

//+-------------------------------------------------------------------------
//  Set the enhanced key usage property for the certificate.
//--------------------------------------------------------------------------

function CertSetEnhancedKeyUsage(pCertContext: PCCERT_CONTEXT;
  pUsage: PCERT_ENHKEY_USAGE): BOOL; stdcall;
{$EXTERNALSYM CertSetEnhancedKeyUsage}

//+-------------------------------------------------------------------------
//  Add the usage identifier to the certificate's enhanced key usage property.
//--------------------------------------------------------------------------

function CertAddEnhancedKeyUsageIdentifier(pCertContext: PCCERT_CONTEXT;
  pszUsageIdentifier: LPCSTR): BOOL; stdcall;
{$EXTERNALSYM CertAddEnhancedKeyUsageIdentifier}

//+-------------------------------------------------------------------------
//  Remove the usage identifier from the certificate's enhanced key usage
//  property.
//--------------------------------------------------------------------------

function CertRemoveEnhancedKeyUsageIdentifier(pCertContext: PCCERT_CONTEXT;
  pszUsageIdentifier: LPCSTR): BOOL; stdcall;
{$EXTERNALSYM CertRemoveEnhancedKeyUsageIdentifier}

//+---------------------------------------------------------------------------
//
//
//  Takes an array of certs and returns an array of usages
//  which consists of the intersection of the valid usages for each cert.
//  If each cert is good for all possible usages then the cNumOIDs is set to -1.
//
//----------------------------------------------------------------------------

function CertGetValidUsages(cCerts: DWORD; rghCerts: PCCERT_CONTEXT;
  var cNumOIDs: Integer; rghOIDs: LPLPSTR; var pcbOIDs: DWORD): BOOL; stdcall;
{$EXTERNALSYM CertGetValidUsages}

//+=========================================================================
//  Cryptographic Message helper functions for verifying and signing a
//  CTL.
//==========================================================================

//+-------------------------------------------------------------------------
//  Get and verify the signer of a cryptographic message.
//
//  To verify a CTL, the hCryptMsg is obtained from the CTL_CONTEXT's
//  hCryptMsg field.
//
//  If CMSG_TRUSTED_SIGNER_FLAG is set, then, treat the Signer stores as being
//  trusted and only search them to find the certificate corresponding to the
//  signer's issuer and serial number.  Otherwise, the SignerStores are
//  optionally provided to supplement the message's store of certificates.
//  If a signer certificate is found, its public key is used to verify
//  the message signature. The CMSG_SIGNER_ONLY_FLAG can be set to
//  return the signer without doing the signature verify.
//
//  If CMSG_USE_SIGNER_INDEX_FLAG is set, then, only get the signer specified
//  by *pdwSignerIndex. Otherwise, iterate through all the signers
//  until a signer verifies or no more signers.
//
//  For a verified signature, *ppSigner is updated with certificate context
//  of the signer and *pdwSignerIndex is updated with the index of the signer.
//  ppSigner and/or pdwSignerIndex can be NULL, indicating the caller isn't
//  interested in getting the CertContext and/or index of the signer.
//--------------------------------------------------------------------------

function CryptMsgGetAndVerifySigner(hCryptMsg: HCRYPTMSG; cSignerStore: DWORD;
  rghSignerStore: PHCERTSTORE; dwFlags: DWORD; ppSigner: PPCCERT_CONTEXT;
  pdwSignerIndex: LPDWORD): BOOL; stdcall;
{$EXTERNALSYM CryptMsgGetAndVerifySigner}

const
  CMSG_TRUSTED_SIGNER_FLAG   = $1;
  {$EXTERNALSYM CMSG_TRUSTED_SIGNER_FLAG}
  CMSG_SIGNER_ONLY_FLAG      = $2;
  {$EXTERNALSYM CMSG_SIGNER_ONLY_FLAG}
  CMSG_USE_SIGNER_INDEX_FLAG = $4;
  {$EXTERNALSYM CMSG_USE_SIGNER_INDEX_FLAG}

//+-------------------------------------------------------------------------
//  Sign an encoded CTL.
//
//  The pbCtlContent can be obtained via a CTL_CONTEXT's pbCtlContent
//  field or via a CryptEncodeObject(PKCS_CTL or PKCS_SORTED_CTL).
//
//  CMSG_CMS_ENCAPSULATED_CTL_FLAG can be set to encode a CMS compatible
//  V3 SignedData message.
//--------------------------------------------------------------------------

function CryptMsgSignCTL(dwMsgEncodingType: DWORD; pbCtlContent: LPBYTE;
  cbCtlContent: DWORD; pSignInfo: PCMSG_SIGNED_ENCODE_INFO; dwFlags: DWORD;
  pbEncoded: LPBYTE; var pcbEncoded: DWORD): BOOL; stdcall;
{$EXTERNALSYM CryptMsgSignCTL}

// When set, CTL inner content is encapsulated within an OCTET STRING

const
  CMSG_CMS_ENCAPSULATED_CTL_FLAG = $00008000;
  {$EXTERNALSYM CMSG_CMS_ENCAPSULATED_CTL_FLAG}

//+-------------------------------------------------------------------------
//  Encode the CTL and create a signed message containing the encoded CTL.
//
//  Set CMSG_ENCODE_SORTED_CTL_FLAG if the CTL entries are to be sorted
//  before encoding. This flag should be set, if the
//  CertFindSubjectInSortedCTL or CertEnumSubjectInSortedCTL APIs will
//  be called. If the identifier for the CTL entries is a hash, such as,
//  MD5 or SHA1, then, CMSG_ENCODE_HASHED_SUBJECT_IDENTIFIER_FLAG should
//  also be set.
//
//  CMSG_CMS_ENCAPSULATED_CTL_FLAG can be set to encode a CMS compatible
//  V3 SignedData message.
//--------------------------------------------------------------------------

function CryptMsgEncodeAndSignCTL(dwMsgEncodingType: DWORD; pCtlInfo: PCTL_INFO;
  pSignInfo: PCMSG_SIGNED_ENCODE_INFO; dwFlags: DWORD; pbEncoded: LPBYTE;
  var pcbEncoded: DWORD): BOOL; stdcall;
{$EXTERNALSYM CryptMsgEncodeAndSignCTL}

//  The following flag is set if the CTL is to be encoded with sorted
//  trusted subjects and the szOID_SORTED_CTL extension is inserted containing
//  sorted offsets to the encoded subjects.

const
  CMSG_ENCODE_SORTED_CTL_FLAG = $1;
  {$EXTERNALSYM CMSG_ENCODE_SORTED_CTL_FLAG}

//  If the above sorted flag is set, then, the following flag should also
//  be set if the identifier for the TrustedSubjects is a hash,
//  such as, MD5 or SHA1.

  CMSG_ENCODE_HASHED_SUBJECT_IDENTIFIER_FLAG = $2;
  {$EXTERNALSYM CMSG_ENCODE_HASHED_SUBJECT_IDENTIFIER_FLAG}

//+-------------------------------------------------------------------------
//  Returns TRUE if the SubjectIdentifier exists in the CTL. Optionally
//  returns a pointer to and byte count of the Subject's encoded attributes.
//--------------------------------------------------------------------------

function CertFindSubjectInSortedCTL(pSubjectIdentifier: PCRYPT_DATA_BLOB;
  pCtlContext: PCCTL_CONTEXT; dwFlags: DWORD; pvReserved: Pointer;
  pEncodedAttributes: PCRYPT_DER_BLOB): BOOL; stdcall;
{$EXTERNALSYM CertFindSubjectInSortedCTL}

//+-------------------------------------------------------------------------
//  Enumerates through the sequence of TrustedSubjects in a CTL context
//  created with CERT_CREATE_CONTEXT_SORTED_FLAG set.
//
//  To start the enumeration, *ppvNextSubject must be NULL. Upon return,
//  *ppvNextSubject is updated to point to the next TrustedSubject in
//  the encoded sequence.
//
//  Returns FALSE for no more subjects or invalid arguments.
//
//  Note, the returned DER_BLOBs point directly into the encoded
//  bytes (not allocated, and must not be freed).
//--------------------------------------------------------------------------

function CertEnumSubjectInSortedCTL(pCtlContext: PCCTL_CONTEXT;
  var ppvNextSubject: Pointer; pSubjectIdentifier: PCRYPT_DER_BLOB;
  pEncodedAttributes: PCRYPT_DER_BLOB): BOOL; stdcall;
{$EXTERNALSYM CertEnumSubjectInSortedCTL}

//+=========================================================================
//  Certificate Verify CTL Usage Data Structures and APIs
//==========================================================================

type
  PCTL_VERIFY_USAGE_PARA = ^CTL_VERIFY_USAGE_PARA;
  {$EXTERNALSYM PCTL_VERIFY_USAGE_PARA}
  _CTL_VERIFY_USAGE_PARA = record
    cbSize: DWORD;
    ListIdentifier: CRYPT_DATA_BLOB; // OPTIONAL
    cCtlStore: DWORD;
    rghCtlStore: PHCERTSTORE; // OPTIONAL
    cSignerStore: DWORD;
    rghSignerStore: PHCERTSTORE; // OPTIONAL
  end;
  {$EXTERNALSYM _CTL_VERIFY_USAGE_PARA}
  CTL_VERIFY_USAGE_PARA = _CTL_VERIFY_USAGE_PARA;
  {$EXTERNALSYM CTL_VERIFY_USAGE_PARA}
  TCtlVerifyUsagePara = CTL_VERIFY_USAGE_PARA;
  PCtlVerifyUsagePara = PCTL_VERIFY_USAGE_PARA;

  PCTL_VERIFY_USAGE_STATUS = ^CTL_VERIFY_USAGE_STATUS;
  {$EXTERNALSYM PCTL_VERIFY_USAGE_STATUS}
  _CTL_VERIFY_USAGE_STATUS = record
    cbSize: DWORD;
    dwError: DWORD;
    dwFlags: DWORD;
    ppCtl: PPCCTL_CONTEXT; // IN OUT OPTIONAL
    dwCtlEntryIndex: DWORD;
    ppSigner: PPCCERT_CONTEXT; // IN OUT OPTIONAL
    dwSignerIndex: DWORD;
  end;
  {$EXTERNALSYM _CTL_VERIFY_USAGE_STATUS}
  CTL_VERIFY_USAGE_STATUS = _CTL_VERIFY_USAGE_STATUS;
  {$EXTERNALSYM CTL_VERIFY_USAGE_STATUS}
  TCtlVerifyUsageStatus = CTL_VERIFY_USAGE_STATUS;
  PCtlVerifyUsageStatus = PCTL_VERIFY_USAGE_STATUS;

const
  CERT_VERIFY_INHIBIT_CTL_UPDATE_FLAG = $1;
  {$EXTERNALSYM CERT_VERIFY_INHIBIT_CTL_UPDATE_FLAG}
  CERT_VERIFY_TRUSTED_SIGNERS_FLAG    = $2;
  {$EXTERNALSYM CERT_VERIFY_TRUSTED_SIGNERS_FLAG}
  CERT_VERIFY_NO_TIME_CHECK_FLAG      = $4;
  {$EXTERNALSYM CERT_VERIFY_NO_TIME_CHECK_FLAG}
  CERT_VERIFY_ALLOW_MORE_USAGE_FLAG   = $8;
  {$EXTERNALSYM CERT_VERIFY_ALLOW_MORE_USAGE_FLAG}

  CERT_VERIFY_UPDATED_CTL_FLAG = $1;
  {$EXTERNALSYM CERT_VERIFY_UPDATED_CTL_FLAG}

//+-------------------------------------------------------------------------
//  Verify that a subject is trusted for the specified usage by finding a
//  signed and time valid CTL with the usage identifiers and containing the
//  the subject. A subject can be identified by either its certificate context
//  or any identifier such as its SHA1 hash.
//
//  See CertFindSubjectInCTL for definition of dwSubjectType and pvSubject
//  parameters.
//
//  Via pVerifyUsagePara, the caller can specify the stores to be searched
//  to find the CTL. The caller can also specify the stores containing
//  acceptable CTL signers. By setting the ListIdentifier, the caller
//  can also restrict to a particular signer CTL list.
//
//  Via pVerifyUsageStatus, the CTL containing the subject, the subject's
//  index into the CTL's array of entries, and the signer of the CTL
//  are returned. If the caller is not interested, ppCtl and ppSigner can be set
//  to NULL. Returned contexts must be freed via the store's free context APIs.
//
//  If the CERT_VERIFY_INHIBIT_CTL_UPDATE_FLAG isn't set, then, a time
//  invalid CTL in one of the CtlStores may be replaced. When replaced, the
//  CERT_VERIFY_UPDATED_CTL_FLAG is set in pVerifyUsageStatus->dwFlags.
//
//  If the CERT_VERIFY_TRUSTED_SIGNERS_FLAG is set, then, only the
//  SignerStores specified in pVerifyUsageStatus are searched to find
//  the signer. Otherwise, the SignerStores provide additional sources
//  to find the signer's certificate.
//
//  If CERT_VERIFY_NO_TIME_CHECK_FLAG is set, then, the CTLs aren't checked
//  for time validity.
//
//  If CERT_VERIFY_ALLOW_MORE_USAGE_FLAG is set, then, the CTL may contain
//  additional usage identifiers than specified by pSubjectUsage. Otherwise,
//  the found CTL will contain the same usage identifers and no more.
//
//  CertVerifyCTLUsage will be implemented as a dispatcher to OID installable
//  functions. First, it will try to find an OID function matching the first
//  usage object identifier in the pUsage sequence. Next, it will dispatch
//  to the default CertDllVerifyCTLUsage functions.
//
//  If the subject is trusted for the specified usage, then, TRUE is
//  returned. Otherwise, FALSE is returned with dwError set to one of the
//  following:
//      CRYPT_E_NO_VERIFY_USAGE_DLL
//      CRYPT_E_NO_VERIFY_USAGE_CHECK
//      CRYPT_E_VERIFY_USAGE_OFFLINE
//      CRYPT_E_NOT_IN_CTL
//      CRYPT_E_NO_TRUSTED_SIGNER
//--------------------------------------------------------------------------

function CertVerifyCTLUsage(dwEncodingType: DWORD; dwSubjectType: DWORD;
  pvSubject: Pointer; pSubjectUsage: PCTL_USAGE; dwFlags: DWORD;
  pVerifyUsagePara: PCTL_VERIFY_USAGE_PARA;
  pVerifyUsageStatus: PCTL_VERIFY_USAGE_STATUS): BOOL; stdcall;
{$EXTERNALSYM CertVerifyCTLUsage}

//+=========================================================================
//  Certificate Revocation Data Structures and APIs
//==========================================================================

//+-------------------------------------------------------------------------
//  The following data structure may be passed to CertVerifyRevocation to
//  assist in finding the issuer of the context to be verified.
//
//  When pIssuerCert is specified, pIssuerCert is the issuer of
//  rgpvContext[cContext - 1].
//
//  When cCertStore and rgCertStore are specified, these stores may contain
//  an issuer certificate.
//
//  When hCrlStore is specified then a handler which uses CRLs can search this
//  store for them
//
//  When pftTimeToUse is specified then the handler (if possible) must determine
//  revocation status relative to the time given otherwise the answer may be
//  independent of time or relative to current time
//--------------------------------------------------------------------------

type
  PCERT_REVOCATION_PARA = ^CERT_REVOCATION_PARA;
  {$EXTERNALSYM PCERT_REVOCATION_PARA}
  _CERT_REVOCATION_PARA = record
    cbSize: DWORD;
    pIssuerCert: PCCERT_CONTEXT;
    cCertStore: DWORD;
    rgCertStore: PHCERTSTORE;
    hCrlStore: HCERTSTORE;
    pftTimeToUse: LPFILETIME;
  end;
  {$EXTERNALSYM _CERT_REVOCATION_PARA}
  CERT_REVOCATION_PARA = _CERT_REVOCATION_PARA;
  {$EXTERNALSYM CERT_REVOCATION_PARA}
  TCertRevocationPara = CERT_REVOCATION_PARA;
  PCertRevocationPara = PCERT_REVOCATION_PARA;

//+-------------------------------------------------------------------------
//  The following data structure is returned by CertVerifyRevocation to
//  specify the status of the revoked or unchecked context. Review the
//  following CertVerifyRevocation comments for details.
//
//  Upon input to CertVerifyRevocation, cbSize must be set to a size
//  >= sizeof(CERT_REVOCATION_STATUS). Otherwise, CertVerifyRevocation
//  returns FALSE and sets LastError to E_INVALIDARG.
//
//  Upon input to the installed or registered CRYPT_OID_VERIFY_REVOCATION_FUNC
//  functions, the dwIndex, dwError and dwReason have been zero'ed.
//--------------------------------------------------------------------------

  PCERT_REVOCATION_STATUS = ^CERT_REVOCATION_STATUS;
  {$EXTERNALSYM PCERT_REVOCATION_STATUS}
  _CERT_REVOCATION_STATUS = record
    cbSize: DWORD;
    dwIndex: DWORD;
    dwError: DWORD;
    dwReason: DWORD;
  end;
  {$EXTERNALSYM _CERT_REVOCATION_STATUS}
  CERT_REVOCATION_STATUS = _CERT_REVOCATION_STATUS;
  {$EXTERNALSYM CERT_REVOCATION_STATUS}
  TCertRevocationStatus = CERT_REVOCATION_STATUS;
  PCertRevocationStatus = PCERT_REVOCATION_STATUS;

//+-------------------------------------------------------------------------
//  Verifies the array of contexts for revocation. The dwRevType parameter
//  indicates the type of the context data structure passed in rgpvContext.
//  Currently only the revocation of certificates is defined.
//
//  If the CERT_VERIFY_REV_CHAIN_FLAG flag is set, then, CertVerifyRevocation
//  is verifying a chain of certs where, rgpvContext[i + 1] is the issuer
//  of rgpvContext[i]. Otherwise, CertVerifyRevocation makes no assumptions
//  about the order of the contexts.
//
//  To assist in finding the issuer, the pRevPara may optionally be set. See
//  the CERT_REVOCATION_PARA data structure for details.
//
//  The contexts must contain enough information to allow the
//  installable or registered revocation DLLs to find the revocation server. For
//  certificates, this information would normally be conveyed in an
//  extension such as the IETF's AuthorityInfoAccess extension.
//
//  CertVerifyRevocation returns TRUE if all of the contexts were successfully
//  checked and none were revoked. Otherwise, returns FALSE and updates the
//  returned pRevStatus data structure as follows:
//    dwIndex
//      Index of the first context that was revoked or unable to
//      be checked for revocation
//    dwError
//      Error status. LastError is also set to this error status.
//      dwError can be set to one of the following error codes defined
//      in winerror.h:
//        ERROR_SUCCESS - good context
//        CRYPT_E_REVOKED - context was revoked. dwReason contains the
//           reason for revocation
//        CRYPT_E_REVOCATION_OFFLINE - unable to connect to the
//           revocation server
//        CRYPT_E_NOT_IN_REVOCATION_DATABASE - the context to be checked
//           was not found in the revocation server's database.
//        CRYPT_E_NO_REVOCATION_CHECK - the called revocation function
//           wasn't able to do a revocation check on the context
//        CRYPT_E_NO_REVOCATION_DLL - no installed or registered Dll was
//           found to verify revocation
//    dwReason
//      The dwReason is currently only set for CRYPT_E_REVOKED and contains
//      the reason why the context was revoked. May be one of the following
//      CRL reasons defined by the CRL Reason Code extension ("2.5.29.21")
//          CRL_REASON_UNSPECIFIED              0
//          CRL_REASON_KEY_COMPROMISE           1
//          CRL_REASON_CA_COMPROMISE            2
//          CRL_REASON_AFFILIATION_CHANGED      3
//          CRL_REASON_SUPERSEDED               4
//          CRL_REASON_CESSATION_OF_OPERATION   5
//          CRL_REASON_CERTIFICATE_HOLD         6
//
//  For each entry in rgpvContext, CertVerifyRevocation iterates
//  through the CRYPT_OID_VERIFY_REVOCATION_FUNC
//  function set's list of installed DEFAULT functions.
//  CryptGetDefaultOIDFunctionAddress is called with pwszDll = NULL. If no
//  installed functions are found capable of doing the revocation verification,
//  CryptVerifyRevocation iterates through CRYPT_OID_VERIFY_REVOCATION_FUNC's
//  list of registered DEFAULT Dlls. CryptGetDefaultOIDDllList is called to
//  get the list. CryptGetDefaultOIDFunctionAddress is called to load the Dll.
//
//  The called functions have the same signature as CertVerifyRevocation. A
//  called function returns TRUE if it was able to successfully check all of
//  the contexts and none were revoked. Otherwise, the called function returns
//  FALSE and updates pRevStatus. dwIndex is set to the index of
//  the first context that was found to be revoked or unable to be checked.
//  dwError and LastError are updated. For CRYPT_E_REVOKED, dwReason
//  is updated. Upon input to the called function, dwIndex, dwError and
//  dwReason have been zero'ed. cbSize has been checked to be >=
//  sizeof(CERT_REVOCATION_STATUS).
//
//  If the called function returns FALSE, and dwError isn't set to
//  CRYPT_E_REVOKED, then, CertVerifyRevocation either continues on to the
//  next DLL in the list for a returned dwIndex of 0 or for a returned
//  dwIndex > 0, restarts the process of finding a verify function by
//  advancing the start of the context array to the returned dwIndex and
//  decrementing the count of remaining contexts.
//--------------------------------------------------------------------------

function CertVerifyRevocation(dwEncodingType, dwRevType, cContext: DWORD;
  rgpvContext: PVOID; dwFlags: DWORD; pRevPara: PCERT_REVOCATION_PARA;
  pRevStatus: PCERT_REVOCATION_STATUS): BOOL; stdcall;
{$EXTERNALSYM CertVerifyRevocation}

//+-------------------------------------------------------------------------
//  Revocation types
//--------------------------------------------------------------------------

const
  CERT_CONTEXT_REVOCATION_TYPE = 1;
  {$EXTERNALSYM CERT_CONTEXT_REVOCATION_TYPE}

//+-------------------------------------------------------------------------
//  When the following flag is set, rgpvContext[] consists of a chain
//  of certificates, where rgpvContext[i + 1] is the issuer of rgpvContext[i].
//--------------------------------------------------------------------------

  CERT_VERIFY_REV_CHAIN_FLAG = $00000001;
  {$EXTERNALSYM CERT_VERIFY_REV_CHAIN_FLAG}

//+-------------------------------------------------------------------------
// CERT_VERIFY_CACHE_ONLY_BASED_REVOCATION prevents the revocation handler from
// accessing any network based resources for revocation checking
//--------------------------------------------------------------------------

  CERT_VERIFY_CACHE_ONLY_BASED_REVOCATION = $00000002;
  {$EXTERNALSYM CERT_VERIFY_CACHE_ONLY_BASED_REVOCATION}

//+-------------------------------------------------------------------------
//  CERT_CONTEXT_REVOCATION_TYPE
//
//  pvContext points to a const CERT_CONTEXT.
//--------------------------------------------------------------------------

//+=========================================================================
//  Certificate Helper APIs
//==========================================================================


//+-------------------------------------------------------------------------
//  Compare two multiple byte integer blobs to see if they are identical.
//
//  Before doing the comparison, leading zero bytes are removed from a
//  positive number and leading 0xFF bytes are removed from a negative
//  number.
//
//  The multiple byte integers are treated as Little Endian. pbData[0] is the
//  least significant byte and pbData[cbData - 1] is the most significant
//  byte.
//
//  Returns TRUE if the integer blobs are identical after removing leading
//  0 or 0xFF bytes.
//--------------------------------------------------------------------------

function CertCompareIntegerBlob(pInt1, pInt2: PCRYPT_INTEGER_BLOB): BOOL; stdcall;
{$EXTERNALSYM CertCompareIntegerBlob}

//+-------------------------------------------------------------------------
//  Compare two certificates to see if they are identical.
//
//  Since a certificate is uniquely identified by its Issuer and SerialNumber,
//  these are the only fields needing to be compared.
//
//  Returns TRUE if the certificates are identical.
//--------------------------------------------------------------------------

function CertCompareCertificate(dwCertEncodingType: DWORD; pCertId1, pCertId2: PCERT_INFO): BOOL; stdcall;
{$EXTERNALSYM CertCompareCertificate}

//+-------------------------------------------------------------------------
//  Compare two certificate names to see if they are identical.
//
//  Returns TRUE if the names are identical.
//--------------------------------------------------------------------------

function CertCompareCertificateName(dwCertEncodingType: DWORD;
  pCertName1: PCERT_NAME_BLOB; pCertName2: PCERT_NAME_BLOB): BOOL; stdcall;
{$EXTERNALSYM CertCompareCertificateName}

//+-------------------------------------------------------------------------
//  Compare the attributes in the certificate name with the specified
//  Relative Distinguished Name's (CERT_RDN) array of attributes.
//  The comparison iterates through the CERT_RDN attributes and looks for an
//  attribute match in any of the certificate name's RDNs.
//  Returns TRUE if all the attributes are found and match.
//
//  The CERT_RDN_ATTR fields can have the following special values:
//    pszObjId == NULL              - ignore the attribute object identifier
//    dwValueType == RDN_ANY_TYPE   - ignore the value type
//
//  CERT_CASE_INSENSITIVE_IS_RDN_ATTRS_FLAG should be set to do
//  a case insensitive match. Otherwise, defaults to an exact, case sensitive
//  match.
//
//  CERT_UNICODE_IS_RDN_ATTRS_FLAG should be set if the pRDN was initialized
//  with unicode strings as for CryptEncodeObject(X509_UNICODE_NAME).
//--------------------------------------------------------------------------

function CertIsRDNAttrsInCertificateName(dwCertEncodingType, dwFlags: DWORD;
  pCertName: PCERT_NAME_BLOB; pRDN: PCERT_RDN): BOOL; stdcall;
{$EXTERNALSYM CertIsRDNAttrsInCertificateName}

const
  CERT_UNICODE_IS_RDN_ATTRS_FLAG          = $1;
  {$EXTERNALSYM CERT_UNICODE_IS_RDN_ATTRS_FLAG}
  CERT_CASE_INSENSITIVE_IS_RDN_ATTRS_FLAG = $2;
  {$EXTERNALSYM CERT_CASE_INSENSITIVE_IS_RDN_ATTRS_FLAG}

//+-------------------------------------------------------------------------
//  Compare two public keys to see if they are identical.
//
//  Returns TRUE if the keys are identical.
//--------------------------------------------------------------------------

function CertComparePublicKeyInfo(dwCertEncodingType: DWORD;
  pPublicKey1, pPublicKey2: PCERT_PUBLIC_KEY_INFO): BOOL; stdcall;
{$EXTERNALSYM CertComparePublicKeyInfo}

//+-------------------------------------------------------------------------
//  Get the public/private key's bit length.
//
//  Returns 0 if unable to determine the key's length.
//--------------------------------------------------------------------------

function CertGetPublicKeyLength(dwCertEncodingType: DWORD;
  pPublicKey: PCERT_PUBLIC_KEY_INFO): DWORD; stdcall;
{$EXTERNALSYM CertGetPublicKeyLength}

//+-------------------------------------------------------------------------
//  Verify the signature of a subject certificate or a CRL using the
//  public key info
//
//  Returns TRUE for a valid signature.
//
//  hCryptProv specifies the crypto provider to use to verify the signature.
//  It doesn't need to use a private key.
//--------------------------------------------------------------------------

function CryptVerifyCertificateSignature(hCryptProv: HCRYPTPROV;
  dwCertEncodingType: DWORD; pbEncoded: LPBYTE; cbEncoded: DWORD;
  pPublicKey: PCERT_PUBLIC_KEY_INFO): BOOL; stdcall;
{$EXTERNALSYM CryptVerifyCertificateSignature}

//+-------------------------------------------------------------------------
//  Verify the signature of a subject certificate, CRL, certificate request
//  or keygen request using the issuer's public key.
//
//  Returns TRUE for a valid signature.
//
//  The subject can be an encoded blob or a context for a certificate or CRL.
//  For a subject certificate context, if the certificate is missing
//  inheritable PublicKey Algorithm Parameters, the context's
//  CERT_PUBKEY_ALG_PARA_PROP_ID is updated with the issuer's public key
//  algorithm parameters for a valid signature.
//
//  The issuer can be a pointer to a CERT_PUBLIC_KEY_INFO, certificate
//  context or a chain context.
//
//  hCryptProv specifies the crypto provider to use to verify the signature.
//  Its private key isn't used. If hCryptProv is NULL, a default
//  provider is picked according to the PublicKey Algorithm OID.
//--------------------------------------------------------------------------

function CryptVerifyCertificateSignatureEx(hCryptProv: HCRYPTPROV;
  dwCertEncodingType, dwSubjectType: DWORD; pvSubject: Pointer;
  dwIssuerType: DWORD; pvIssuer: Pointer; dwFlags: DWORD; pvReserved: Pointer): BOOL; stdcall;
{$EXTERNALSYM CryptVerifyCertificateSignatureEx}

// Subject Types

const
  CRYPT_VERIFY_CERT_SIGN_SUBJECT_BLOB = 1;
  {$EXTERNALSYM CRYPT_VERIFY_CERT_SIGN_SUBJECT_BLOB}
    // pvSubject :: PCRYPT_DATA_BLOB
  CRYPT_VERIFY_CERT_SIGN_SUBJECT_CERT = 2;
  {$EXTERNALSYM CRYPT_VERIFY_CERT_SIGN_SUBJECT_CERT}
    // pvSubject :: PCCERT_CONTEXT
  CRYPT_VERIFY_CERT_SIGN_SUBJECT_CRL = 3;
  {$EXTERNALSYM CRYPT_VERIFY_CERT_SIGN_SUBJECT_CRL}
    // pvSubject :: PCCRL_CONTEXT

// Issuer Types
  CRYPT_VERIFY_CERT_SIGN_ISSUER_PUBKEY = 1;
  {$EXTERNALSYM CRYPT_VERIFY_CERT_SIGN_ISSUER_PUBKEY}
    // pvIssuer :: PCERT_PUBLIC_KEY_INFO
  CRYPT_VERIFY_CERT_SIGN_ISSUER_CERT = 2;
  {$EXTERNALSYM CRYPT_VERIFY_CERT_SIGN_ISSUER_CERT}
    // pvIssuer :: PCCERT_CONTEXT
  CRYPT_VERIFY_CERT_SIGN_ISSUER_CHAIN = 3;
  {$EXTERNALSYM CRYPT_VERIFY_CERT_SIGN_ISSUER_CHAIN}
    // pvIssuer :: PCCERT_CHAIN_CONTEXT

//+-------------------------------------------------------------------------
//  Compute the hash of the "to be signed" information in the encoded
//  signed content (CERT_SIGNED_CONTENT_INFO).
//
//  hCryptProv specifies the crypto provider to use to compute the hash.
//  It doesn't need to use a private key.
//--------------------------------------------------------------------------

function CryptHashToBeSigned(hCryptProv: HCRYPTPROV; dwCertEncodingType: DWORD;
  pbEncoded: LPBYTE; cbEncoded: DWORD; pbComputedHash: LPBYTE;
  var pcbComputedHash: DWORD): BOOL; stdcall;
{$EXTERNALSYM CryptHashToBeSigned}

//+-------------------------------------------------------------------------
//  Hash the encoded content.
//
//  hCryptProv specifies the crypto provider to use to compute the hash.
//  It doesn't need to use a private key.
//
//  Algid specifies the CAPI hash algorithm to use. If Algid is 0, then, the
//  default hash algorithm (currently SHA1) is used.
//--------------------------------------------------------------------------

function CryptHashCertificate(hCryptProv: HCRYPTPROV; Algid: ALG_ID;
  dwFlags: DWORD; pbEncoded: LPBYTE; cbEncoded: DWORD; pbComputedHash: LPBYTE;
  var pcbComputedHash: DWORD): BOOL; stdcall;
{$EXTERNALSYM CryptHashCertificate}

//+-------------------------------------------------------------------------
//  Sign the "to be signed" information in the encoded signed content.
//
//  hCryptProv specifies the crypto provider to use to do the signature.
//  It uses the specified private key.
//--------------------------------------------------------------------------

function CryptSignCertificate(hCryptProv: HCRYPTPROV; dwKeySpec: DWORD;
  dwCertEncodingType: DWORD; pbEncodedToBeSigned: LPBYTE; cbEncodedToBeSigned: DWORD;
  pSignatureAlgorithm: PCRYPT_ALGORITHM_IDENTIFIER; pvHashAuxInfo: Pointer;
  pbSignature: LPBYTE; var pcbSignature: DWORD): BOOL; stdcall;
{$EXTERNALSYM CryptSignCertificate}

//+-------------------------------------------------------------------------
//  Encode the "to be signed" information. Sign the encoded "to be signed".
//  Encode the "to be signed" and the signature.
//
//  hCryptProv specifies the crypto provider to use to do the signature.
//  It uses the specified private key.
//--------------------------------------------------------------------------

function CryptSignAndEncodeCertificate(hCryptProv: HCRYPTPROV; dwKeySpec: DWORD;
  dwCertEncodingType: DWORD; lpszStructType: LPCSTR; pvStructInfo: Pointer;
  pSignatureAlgorithm: PCRYPT_ALGORITHM_IDENTIFIER; pvHashAuxInfo: Pointer;
  pbEncoded: PBYTE; var pcbEncoded: DWORD): BOOL; stdcall;
{$EXTERNALSYM CryptSignAndEncodeCertificate}

//+-------------------------------------------------------------------------
//  Verify the time validity of a certificate.
//
//  Returns -1 if before NotBefore, +1 if after NotAfter and otherwise 0 for
//  a valid certificate
//
//  If pTimeToVerify is NULL, uses the current time.
//--------------------------------------------------------------------------

function CertVerifyTimeValidity(pTimeToVerify: LPFILETIME; pCertInfo: PCERT_INFO): LONG; stdcall;
{$EXTERNALSYM CertVerifyTimeValidity}

//+-------------------------------------------------------------------------
//  Verify the time validity of a CRL.
//
//  Returns -1 if before ThisUpdate, +1 if after NextUpdate and otherwise 0 for
//  a valid CRL
//
//  If pTimeToVerify is NULL, uses the current time.
//--------------------------------------------------------------------------

function CertVerifyCRLTimeValidity(pTimeToVerify: LPFILETIME; pCrlInfo: PCRL_INFO): LONG; stdcall;
{$EXTERNALSYM CertVerifyCRLTimeValidity}

//+-------------------------------------------------------------------------
//  Verify that the subject's time validity nests within the issuer's time
//  validity.
//
//  Returns TRUE if it nests. Otherwise, returns FALSE.
//--------------------------------------------------------------------------

function CertVerifyValidityNesting(pSubjectInfo, pIssuerInfo: PCERT_INFO): BOOL; stdcall;
{$EXTERNALSYM CertVerifyValidityNesting}

//+-------------------------------------------------------------------------
//  Verify that the subject certificate isn't on its issuer CRL.
//
//  Returns true if the certificate isn't on the CRL.
//--------------------------------------------------------------------------

function CertVerifyCRLRevocation(dwCertEncodingType: DWORD; pCertId: PCERT_INFO;
  cCrlInfo: DWORD; rgpCrlInfo: PCRL_INFO): BOOL; stdcall;
{$EXTERNALSYM CertVerifyCRLRevocation}

//+-------------------------------------------------------------------------
//  Convert the CAPI AlgId to the ASN.1 Object Identifier string
//
//  Returns NULL if there isn't an ObjId corresponding to the AlgId.
//--------------------------------------------------------------------------

function CertAlgIdToOID(dwAlgId: DWORD): LPCSTR; stdcall;
{$EXTERNALSYM CertAlgIdToOID}

//+-------------------------------------------------------------------------
//  Convert the ASN.1 Object Identifier string to the CAPI AlgId.
//
//  Returns 0 if there isn't an AlgId corresponding to the ObjId.
//--------------------------------------------------------------------------

function CertOIDToAlgId(pszObjId: LPCSTR): DWORD; stdcall;
{$EXTERNALSYM CertOIDToAlgId}

//+-------------------------------------------------------------------------
//  Find an extension identified by its Object Identifier.
//
//  If found, returns pointer to the extension. Otherwise, returns NULL.
//--------------------------------------------------------------------------

function CertFindExtension(pszObjId: LPCSTR; cExtensions: DWORD;
  rgExtensions: PCERT_EXTENSION): PCERT_EXTENSION; stdcall;
{$EXTERNALSYM CertFindExtension}

//+-------------------------------------------------------------------------
//  Find the first attribute identified by its Object Identifier.
//
//  If found, returns pointer to the attribute. Otherwise, returns NULL.
//--------------------------------------------------------------------------

function CertFindAttribute(pszObjId: LPCSTR; cAttr: DWORD;
  rgAttr: PCRYPT_ATTRIBUTE): PCRYPT_ATTRIBUTE; stdcall;
{$EXTERNALSYM CertFindAttribute}

//+-------------------------------------------------------------------------
//  Find the first CERT_RDN attribute identified by its Object Identifier in
//  the name's list of Relative Distinguished Names.
//
//  If found, returns pointer to the attribute. Otherwise, returns NULL.
//--------------------------------------------------------------------------

function CertFindRDNAttr(pszObjId: LPCSTR; pName: PCERT_NAME_INFO): PCERT_RDN_ATTR; stdcall;
{$EXTERNALSYM CertFindRDNAttr}

//+-------------------------------------------------------------------------
//  Get the intended key usage bytes from the certificate.
//
//  If the certificate doesn't have any intended key usage bytes, returns FALSE
//  and *pbKeyUsage is zeroed. Otherwise, returns TRUE and up through
//  cbKeyUsage bytes are copied into *pbKeyUsage. Any remaining uncopied
//  bytes are zeroed.
//--------------------------------------------------------------------------

function CertGetIntendedKeyUsage(dwCertEncodingType: DWORD; pCertInfo: PCERT_INFO;
  pbKeyUsage: LPBYTE; cbKeyUsage: DWORD): BOOL; stdcall;
{$EXTERNALSYM CertGetIntendedKeyUsage}

type
  HCRYPTDEFAULTCONTEXT = Pointer;
  {$EXTERNALSYM HCRYPTDEFAULTCONTEXT}

//+-------------------------------------------------------------------------
//  Install a previously CryptAcquiredContext'ed HCRYPTPROV to be used as
//  a default context.
//
//  dwDefaultType and pvDefaultPara specify where the default context is used.
//  For example, install the HCRYPTPROV to be used to verify certificate's
//  having szOID_OIWSEC_md5RSA signatures.
//
//  By default, the installed HCRYPTPROV is only applicable to the current
//  thread. Set CRYPT_DEFAULT_CONTEXT_PROCESS_FLAG to allow the HCRYPTPROV
//  to be used by all threads in the current process.
//
//  For a successful install, TRUE is returned and *phDefaultContext is
//  updated with the HANDLE to be passed to CryptUninstallDefaultContext.
//
//  The installed HCRYPTPROVs are stack ordered (the last installed
//  HCRYPTPROV is checked first). All thread installed HCRYPTPROVs are
//  checked before any process HCRYPTPROVs.
//
//  The installed HCRYPTPROV remains available for default usage until
//  CryptUninstallDefaultContext is called or the thread or process exits.
//
//  If CRYPT_DEFAULT_CONTEXT_AUTO_RELEASE_FLAG is set, then, the HCRYPTPROV
//  is CryptReleaseContext'ed at thread or process exit. However,
//  not CryptReleaseContext'ed if CryptUninstallDefaultContext is
//  called.
//--------------------------------------------------------------------------

function CryptInstallDefaultContext(hCryptProv: HCRYPTPROV; dwDefaultType: DWORD;
  pvDefaultPara: Pointer; dwFlags: DWORD; pvReserved: Pointer;
  var phDefaultContext: HCRYPTDEFAULTCONTEXT): BOOL; stdcall;
{$EXTERNALSYM CryptInstallDefaultContext}

// dwFlags

const
  CRYPT_DEFAULT_CONTEXT_AUTO_RELEASE_FLAG = $00000001;
  {$EXTERNALSYM CRYPT_DEFAULT_CONTEXT_AUTO_RELEASE_FLAG}
  CRYPT_DEFAULT_CONTEXT_PROCESS_FLAG      = $00000002;
  {$EXTERNALSYM CRYPT_DEFAULT_CONTEXT_PROCESS_FLAG}

// List of dwDefaultType's

  CRYPT_DEFAULT_CONTEXT_CERT_SIGN_OID       = 1;
  {$EXTERNALSYM CRYPT_DEFAULT_CONTEXT_CERT_SIGN_OID}
  CRYPT_DEFAULT_CONTEXT_MULTI_CERT_SIGN_OID = 2;
  {$EXTERNALSYM CRYPT_DEFAULT_CONTEXT_MULTI_CERT_SIGN_OID}

//+-------------------------------------------------------------------------
//  CRYPT_DEFAULT_CONTEXT_CERT_SIGN_OID
//
//  Install a default HCRYPTPROV used to verify a certificate
//  signature. pvDefaultPara points to the szOID of the certificate
//  signature algorithm, for example, szOID_OIWSEC_md5RSA. If
//  pvDefaultPara is NULL, then, the HCRYPTPROV is used to verify all
//  certificate signatures. Note, pvDefaultPara can't be NULL when
//  CRYPT_DEFAULT_CONTEXT_PROCESS_FLAG is set.
//--------------------------------------------------------------------------

//+-------------------------------------------------------------------------
//  CRYPT_DEFAULT_CONTEXT_MULTI_CERT_SIGN_OID
//
//  Same as CRYPT_DEFAULT_CONTEXT_CERT_SIGN_OID. However, the default
//  HCRYPTPROV is to be used for multiple signature szOIDs. pvDefaultPara
//  points to a CRYPT_DEFAULT_CONTEXT_MULTI_OID_PARA structure containing
//  an array of szOID pointers.
//--------------------------------------------------------------------------

type
  PCRYPT_DEFAULT_CONTEXT_MULTI_OID_PARA = ^CRYPT_DEFAULT_CONTEXT_MULTI_OID_PARA;
  {$EXTERNALSYM PCRYPT_DEFAULT_CONTEXT_MULTI_OID_PARA}
  _CRYPT_DEFAULT_CONTEXT_MULTI_OID_PARA = record
    cOID: DWORD;
    rgpszOID: LPLPSTR;
  end;
  {$EXTERNALSYM _CRYPT_DEFAULT_CONTEXT_MULTI_OID_PARA}
  CRYPT_DEFAULT_CONTEXT_MULTI_OID_PARA = _CRYPT_DEFAULT_CONTEXT_MULTI_OID_PARA;
  {$EXTERNALSYM CRYPT_DEFAULT_CONTEXT_MULTI_OID_PARA}
  TCryptDefaultContextMultiOidPara = CRYPT_DEFAULT_CONTEXT_MULTI_OID_PARA;
  PCryptDefaultContextMultiOidPara = PCRYPT_DEFAULT_CONTEXT_MULTI_OID_PARA;

//+-------------------------------------------------------------------------
//  Uninstall a default context previously installed by
//  CryptInstallDefaultContext.
//
//  For a default context installed with CRYPT_DEFAULT_CONTEXT_PROCESS_FLAG
//  set, if any other threads are currently using this context,
//  this function will block until they finish.
//--------------------------------------------------------------------------

function CryptUninstallDefaultContext(hDefaultContext: HCRYPTDEFAULTCONTEXT;
  dwFlags: DWORD; pvReserved: Pointer): BOOL; stdcall;
{$EXTERNALSYM CryptUninstallDefaultContext}

//+-------------------------------------------------------------------------
//  Export the public key info associated with the provider's corresponding
//  private key.
//
//  Calls CryptExportPublicKeyInfo with pszPublicKeyObjId = szOID_RSA_RSA,
//  dwFlags = 0 and pvAuxInfo = NULL.
//--------------------------------------------------------------------------

function CryptExportPublicKeyInfo(hCryptProv: HCRYPTPROV; dwKeySpec: DWORD;
  dwCertEncodingType: DWORD; pInfo: PCERT_PUBLIC_KEY_INFO; var pcbInfo: DWORD): BOOL; stdcall;
{$EXTERNALSYM CryptExportPublicKeyInfo}

//+-------------------------------------------------------------------------
//  Export the public key info associated with the provider's corresponding
//  private key.
//
//  Uses the dwCertEncodingType and pszPublicKeyObjId to call the
//  installable CRYPT_OID_EXPORT_PUBLIC_KEY_INFO_FUNC. The called function
//  has the same signature as CryptExportPublicKeyInfoEx.
//
//  If unable to find an installable OID function for the pszPublicKeyObjId,
//  attempts to export as a RSA Public Key (szOID_RSA_RSA).
//
//  The dwFlags and pvAuxInfo aren't used for szOID_RSA_RSA.
//--------------------------------------------------------------------------

const
  CRYPT_OID_EXPORT_PUBLIC_KEY_INFO_FUNC = 'CryptDllExportPublicKeyInfoEx';
  {$EXTERNALSYM CRYPT_OID_EXPORT_PUBLIC_KEY_INFO_FUNC}

function CryptExportPublicKeyInfoEx(hCryptProv: HCRYPTPROV; dwKeySpec: DWORD;
  dwCertEncodingType: DWORD; pszPublicKeyObjId: LPSTR; dwFlags: DWORD;
  pvAuxInfo: Pointer; pInfo: PCERT_PUBLIC_KEY_INFO; var pcbInfo: DWORD): BOOL; stdcall;
{$EXTERNALSYM CryptExportPublicKeyInfoEx}

//+-------------------------------------------------------------------------
//  Convert and import the public key info into the provider and return a
//  handle to the public key.
//
//  Calls CryptImportPublicKeyInfoEx with aiKeyAlg = 0, dwFlags = 0 and
//  pvAuxInfo = NULL.
//--------------------------------------------------------------------------

function CryptImportPublicKeyInfo(hCryptProv: HCRYPTPROV; dwCertEncodingType: DWORD;
  pInfo: PCERT_PUBLIC_KEY_INFO; var phKey: HCRYPTKEY): BOOL; stdcall;
{$EXTERNALSYM CryptImportPublicKeyInfo}

//+-------------------------------------------------------------------------
//  Convert and import the public key info into the provider and return a
//  handle to the public key.
//
//  Uses the dwCertEncodingType and pInfo->Algorithm.pszObjId to call the
//  installable CRYPT_OID_IMPORT_PUBLIC_KEY_INFO_FUNC. The called function
//  has the same signature as CryptImportPublicKeyInfoEx.
//
//  If unable to find an installable OID function for the pszObjId,
//  attempts to import as a RSA Public Key (szOID_RSA_RSA).
//
//  For szOID_RSA_RSA: aiKeyAlg may be set to CALG_RSA_SIGN or CALG_RSA_KEYX.
//  Defaults to CALG_RSA_KEYX. The dwFlags and pvAuxInfo aren't used.
//--------------------------------------------------------------------------

const
  CRYPT_OID_IMPORT_PUBLIC_KEY_INFO_FUNC = 'CryptDllImportPublicKeyInfoEx';
  {$EXTERNALSYM CRYPT_OID_IMPORT_PUBLIC_KEY_INFO_FUNC}

function CryptImportPublicKeyInfoEx(hCryptProv: HCRYPTPROV; dwCertEncodingType: DWORD;
  pInfo: PCERT_PUBLIC_KEY_INFO; aiKeyAlg: ALG_ID; dwFlags: DWORD; pvAuxInfo: Pointer;
  var phKey: HCRYPTKEY): BOOL; stdcall;
{$EXTERNALSYM CryptImportPublicKeyInfoEx}

//+-------------------------------------------------------------------------
//  Acquire a HCRYPTPROV handle and dwKeySpec for the specified certificate
//  context. Uses the certificate's CERT_KEY_PROV_INFO_PROP_ID property.
//  The returned HCRYPTPROV handle may optionally be cached using the
//  certificate's CERT_KEY_CONTEXT_PROP_ID property.
//
//  If CRYPT_ACQUIRE_CACHE_FLAG is set, then, if an already acquired and
//  cached HCRYPTPROV exists for the certificate, its returned. Otherwise,
//  a HCRYPTPROV is acquired and then cached via the certificate's
//  CERT_KEY_CONTEXT_PROP_ID.
//
//  The CRYPT_ACQUIRE_USE_PROV_INFO_FLAG can be set to use the dwFlags field of
//  the certificate's CERT_KEY_PROV_INFO_PROP_ID property's CRYPT_KEY_PROV_INFO
//  data structure to determine if the returned HCRYPTPROV should be cached.
//  HCRYPTPROV caching is enabled if the CERT_SET_KEY_CONTEXT_PROP_ID flag was
//  set.
//
//  If CRYPT_ACQUIRE_COMPARE_KEY_FLAG is set, then,
//  the public key in the certificate is compared with the public
//  key returned by the cryptographic provider. If the keys don't match, the
//  acquire fails and LastError is set to NTE_BAD_PUBLIC_KEY. Note, if
//  a cached HCRYPTPROV is returned, the comparison isn't done. We assume the
//  comparison was done on the initial acquire.
//
//  *pfCallerFreeProv is returned set to FALSE for:
//    - Acquire or public key comparison fails.
//    - CRYPT_ACQUIRE_CACHE_FLAG is set.
//    - CRYPT_ACQUIRE_USE_PROV_INFO_FLAG is set AND
//      CERT_SET_KEY_CONTEXT_PROP_ID flag is set in the dwFlags field of the
//      certificate's CERT_KEY_PROV_INFO_PROP_ID property's
//      CRYPT_KEY_PROV_INFO data structure.
//  When *pfCallerFreeProv is FALSE, the caller must not release. The
//  returned HCRYPTPROV will be released on the last free of the certificate
//  context.
//
//  Otherwise, *pfCallerFreeProv is TRUE and the returned HCRYPTPROV must
//  be released by the caller by calling CryptReleaseContext.
//--------------------------------------------------------------------------

function CryptAcquireCertificatePrivateKey(pCert: PCCERT_CONTEXT; dwFlags: DWORD;
  pvReserved: Pointer; var phCryptProv: HCRYPTPROV; pdwKeySpec: LPDWORD;
  pfCallerFreeProv: PBOOL): BOOL; stdcall;
{$EXTERNALSYM CryptAcquireCertificatePrivateKey}

const
  CRYPT_ACQUIRE_CACHE_FLAG         = $1;
  {$EXTERNALSYM CRYPT_ACQUIRE_CACHE_FLAG}
  CRYPT_ACQUIRE_USE_PROV_INFO_FLAG = $2;
  {$EXTERNALSYM CRYPT_ACQUIRE_USE_PROV_INFO_FLAG}
  CRYPT_ACQUIRE_COMPARE_KEY_FLAG   = $4;
  {$EXTERNALSYM CRYPT_ACQUIRE_COMPARE_KEY_FLAG}

//+-------------------------------------------------------------------------
//  Enumerates the cryptographic providers and their containers to find the
//  private key corresponding to the certificate's public key. For a match,
//  the certificate's CERT_KEY_PROV_INFO_PROP_ID property is updated.
//
//  If the CERT_KEY_PROV_INFO_PROP_ID is already set, then, its checked to
//  see if it matches the provider's public key. For a match, the above
//  enumeration is skipped.
//
//  By default both the user and machine key containers are searched.
//  The CRYPT_FIND_USER_KEYSET_FLAG or CRYPT_FIND_MACHINE_KEYSET_FLAG
//  can be set in dwFlags to restrict the search to either of the containers.
//
//  If a container isn't found, returns FALSE with LastError set to
//  NTE_NO_KEY.
//--------------------------------------------------------------------------

function CryptFindCertificateKeyProvInfo(pCert: PCCERT_CONTEXT; dwFlags: DWORD;
  pvReserved: Pointer): BOOL; stdcall;
{$EXTERNALSYM CryptFindCertificateKeyProvInfo}

const
  CRYPT_FIND_USER_KEYSET_FLAG    = $1;
  {$EXTERNALSYM CRYPT_FIND_USER_KEYSET_FLAG}
  CRYPT_FIND_MACHINE_KEYSET_FLAG = $2;
  {$EXTERNALSYM CRYPT_FIND_MACHINE_KEYSET_FLAG}

//+-------------------------------------------------------------------------
//  This is the prototype for the installable function which is called to
//  actually import a key into a CSP.  an installable of this type is called
//  from CryptImportPKCS8.  the algorithm OID of the private key is used
//  to look up the proper installable function to call.
//
//  hCryptProv - the provider to import the key to
//  pPrivateKeyInfo - describes the key to be imported
//  dwFlags - The available flags are:
//              CRYPT_EXPORTABLE
//              this flag is used when importing private keys, for a full
//              explanation please see the documentation for CryptImportKey.
//  pvAuxInfo - reserved for future, must be NULL
//--------------------------------------------------------------------------

type
  PFN_IMPORT_PRIV_KEY_FUNC = function (hCryptProv: HCRYPTPROV;
    pPrivateKeyInfo: PCRYPT_PRIVATE_KEY_INFO; dwFlags: DWORD;
    pvAuxInfo: Pointer): BOOL; stdcall;
  {$EXTERNALSYM PFN_IMPORT_PRIV_KEY_FUNC}
  PFnImportPrivKeyFunc = PFN_IMPORT_PRIV_KEY_FUNC;

const
  CRYPT_OID_IMPORT_PRIVATE_KEY_INFO_FUNC = 'CryptDllImportPrivateKeyInfoEx';
  {$EXTERNALSYM CRYPT_OID_IMPORT_PRIVATE_KEY_INFO_FUNC}

//+-------------------------------------------------------------------------
// Convert (from PKCS8 format) and import the private key into a provider
// and return a handle to the provider as well as the KeySpec used to import to.
//
// This function will call the PRESOLVE_HCRYPTPROV_FUNC in the
// privateKeyAndParams to obtain a handle of provider to import the key to.
// if the PRESOLVE_HCRYPTPROV_FUNC is NULL then the default provider will be used.
//
// privateKeyAndParams - private key blob and corresponding parameters
// dwFlags - The available flags are:
//              CRYPT_EXPORTABLE
//              this flag is used when importing private keys, for a full
//              explanation please see the documentation for CryptImportKey.
// phCryptProv - filled in with the handle of the provider the key was
//               imported to, the caller is responsible for freeing it
// pvAuxInfo - This parameter is reserved for future use and should be set
//             to NULL in the interim.
//--------------------------------------------------------------------------

function CryptImportPKCS8(sImportParams: CRYPT_PKCS8_IMPORT_PARAMS; dwFlags: DWORD;
  phCryptProv: PHCRYPTPROV; pvAuxInfo: Pointer): BOOL; stdcall;
{$EXTERNALSYM CryptImportPKCS8}

//+-------------------------------------------------------------------------
// this is the prototype for installable functions for exporting the private key
//--------------------------------------------------------------------------

type
  PFN_EXPORT_PRIV_KEY_FUNC = function (hCryptProv: HCRYPTPROV; dwKeySpec: DWORD;
    pszPrivateKeyObjId: LPSTR; dwFlags: DWORD; pvAuxInfo: Pointer;
    var pPrivateKeyInfo: CRYPT_PRIVATE_KEY_INFO; var pcbPrivateKeyBlob: DWORD): BOOL; stdcall;
  {$EXTERNALSYM PFN_EXPORT_PRIV_KEY_FUNC}
  PfnExportPrivKeyFunc = PFN_EXPORT_PRIV_KEY_FUNC;

const
  CRYPT_OID_EXPORT_PRIVATE_KEY_INFO_FUNC = 'CryptDllExportPrivateKeyInfoEx';
  {$EXTERNALSYM CRYPT_OID_EXPORT_PRIVATE_KEY_INFO_FUNC}

  CRYPT_DELETE_KEYSET = $0001;
  {$EXTERNALSYM CRYPT_DELETE_KEYSET}

//+-------------------------------------------------------------------------
//  CryptExportPKCS8 -- superseded by CryptExportPKCS8Ex
//
//  Export the private key in PKCS8 format
//--------------------------------------------------------------------------

function CryptExportPKCS8(hCryptProv: HCRYPTPROV; dwKeySpec: DWORD;
  pszPrivateKeyObjId: LPSTR; dwFlags: DWORD; pvAuxInfo: Pointer;
  pbPrivateKeyBlob: LPBYTE; var pcbPrivateKeyBlob: DWORD): BOOL; stdcall;
{$EXTERNALSYM CryptExportPKCS8}

//+-------------------------------------------------------------------------
// CryptExportPKCS8Ex
//
//  Export the private key in PKCS8 format
//
//
//  Uses the pszPrivateKeyObjId to call the
//  installable CRYPT_OID_EXPORT_PRIVATE_KEY_INFO_FUNC. The called function
//  has the signature defined by PFN_EXPORT_PRIV_KEY_FUNC.
//
//  If unable to find an installable OID function for the pszPrivateKeyObjId,
//  attempts to export as a RSA Private Key (szOID_RSA_RSA).
//
// psExportParams - specifies information about the key to export
// dwFlags - The flag values. None currently supported
// pvAuxInfo - This parameter is reserved for future use and should be set to
//                           NULL in the interim.
// pbPrivateKeyBlob - A pointer to the private key blob.  It will be encoded
//                                          as a PKCS8 PrivateKeyInfo.
// pcbPrivateKeyBlob - A pointer to a DWORD that contains the size, in bytes,
//                                           of the private key blob being exported.
//+-------------------------------------------------------------------------

function CryptExportPKCS8Ex(psExportParams: PCRYPT_PKCS8_EXPORT_PARAMS;
  dwFlags: DWORD; pvAuxInfo: Pointer; pbPrivateKeyBlob: LPBYTE;
  var pcbPrivateKeyBlob: DWORD): BOOL; stdcall;
{$EXTERNALSYM CryptExportPKCS8Ex}

//+-------------------------------------------------------------------------
//  Compute the hash of the encoded public key info.
//
//  The public key info is encoded and then hashed.
//--------------------------------------------------------------------------

function CryptHashPublicKeyInfo(hCryptProv: HCRYPTPROV; Algid: ALG_ID;
  dwFlags: DWORD; dwCertEncodingType: DWORD; pInfo: PCERT_PUBLIC_KEY_INFO;
  pbComputedHash: LPBYTE; var pcbComputedHash: DWORD): BOOL; stdcall;
{$EXTERNALSYM CryptHashPublicKeyInfo}

//+-------------------------------------------------------------------------
//  Convert a Name Value to a null terminated char string
//
//  Returns the number of characters converted including the terminating null
//  character. If psz is NULL or csz is 0, returns the required size of the
//  destination string (including the terminating null char).
//
//  If psz != NULL && csz != 0, returned psz is always NULL terminated.
//
//  Note: csz includes the NULL char.
//--------------------------------------------------------------------------

function CertRDNValueToStrA(dwValueType: DWORD; pValue: PCERT_RDN_VALUE_BLOB;
  psz: LPSTR; csz: DWORD): DWORD; stdcall;
{$EXTERNALSYM CertRDNValueToStrA}

//+-------------------------------------------------------------------------
//  Convert a Name Value to a null terminated char string
//
//  Returns the number of characters converted including the terminating null
//  character. If psz is NULL or csz is 0, returns the required size of the
//  destination string (including the terminating null char).
//
//  If psz != NULL && csz != 0, returned psz is always NULL terminated.
//
//  Note: csz includes the NULL char.
//--------------------------------------------------------------------------

function CertRDNValueToStrW(dwValueType: DWORD; pValue: PCERT_RDN_VALUE_BLOB;
  psz: LPWSTR; csz: DWORD): DWORD; stdcall;
{$EXTERNALSYM CertRDNValueToStrW}

{$IFDEF UNICODE}
function CertRDNValueToStr(dwValueType: DWORD; pValue: PCERT_RDN_VALUE_BLOB;
  psz: LPWSTR; csz: DWORD): DWORD; stdcall;
{$EXTERNALSYM CertRDNValueToStr}
{$ELSE}
function CertRDNValueToStr(dwValueType: DWORD; pValue: PCERT_RDN_VALUE_BLOB;
  psz: LPSTR; csz: DWORD): DWORD; stdcall;
{$EXTERNALSYM CertRDNValueToStr}
{$ENDIF}

//+-------------------------------------------------------------------------
//  Convert the certificate name blob to a null terminated char string.
//
//  Follows the string representation of distinguished names specified in
//  RFC 1779. (Note, added double quoting "" for embedded quotes, quote
//  empty strings and don't quote strings containing consecutive spaces).
//  RDN values of type CERT_RDN_ENCODED_BLOB or CERT_RDN_OCTET_STRING are
//  formatted in hexadecimal (e.g. #0A56CF).
//
//  The name string is formatted according to the dwStrType:
//    CERT_SIMPLE_NAME_STR
//      The object identifiers are discarded. CERT_RDN entries are separated
//      by ", ". Multiple attributes per CERT_RDN are separated by " + ".
//      For example:
//          Microsoft, Joe Cool + Programmer
//    CERT_OID_NAME_STR
//      The object identifiers are included with a "=" separator from their
//      attribute value. CERT_RDN entries are separated by ", ".
//      Multiple attributes per CERT_RDN are separated by " + ". For example:
//          2.5.4.11=Microsoft, 2.5.4.3=Joe Cool + 2.5.4.12=Programmer
//    CERT_X500_NAME_STR
//      The object identifiers are converted to their X500 key name. Otherwise,
//      same as CERT_OID_NAME_STR. If the object identifier doesn't have
//      a corresponding X500 key name, then, the object identifier is used with
//      a "OID." prefix. For example:
//          OU=Microsoft, CN=Joe Cool + T=Programmer, OID.1.2.3.4.5.6=Unknown
//
//  We quote the RDN value if it contains leading or trailing whitespace
//  or one of the following characters: ",", "+", "=", """, "\n",  "<", ">",
//  "#" or ";". The quoting character is ". If the the RDN Value contains
//  a " it is double quoted (""). For example:
//      OU="  Microsoft", CN="Joe ""Cool""" + T="Programmer, Manager"
//
//  CERT_NAME_STR_SEMICOLON_FLAG can be or'ed into dwStrType to replace
//  the ", " separator with a "; " separator.
//
//  CERT_NAME_STR_CRLF_FLAG can be or'ed into dwStrType to replace
//  the ", " separator with a "\r\n" separator.
//
//  CERT_NAME_STR_NO_PLUS_FLAG can be or'ed into dwStrType to replace the
//  " + " separator with a single space, " ".
//
//  CERT_NAME_STR_NO_QUOTING_FLAG can be or'ed into dwStrType to inhibit
//  the above quoting.
//
//  CERT_NAME_STR_REVERSE_FLAG can be or'ed into dwStrType to reverse the
//  order of the RDNs before converting to the string.
//
//  By default, CERT_RDN_T61_STRING encoded values are initially decoded
//  as UTF8. If the UTF8 decoding fails, then, decoded as 8 bit characters.
//  CERT_NAME_STR_DISABLE_IE4_UTF8_FLAG can be or'ed into dwStrType to
//  skip the initial attempt to decode as UTF8.
//
//  Returns the number of characters converted including the terminating null
//  character. If psz is NULL or csz is 0, returns the required size of the
//  destination string (including the terminating null char).
//
//  If psz != NULL && csz != 0, returned psz is always NULL terminated.
//
//  Note: csz includes the NULL char.
//--------------------------------------------------------------------------

//+-------------------------------------------------------------------------
//--------------------------------------------------------------------------

function CertNameToStrA(dwCertEncodingType: DWORD; pName: PCERT_NAME_BLOB;
  dwStrType: DWORD; psz: LPSTR; csz: DWORD): DWORD; stdcall;
{$EXTERNALSYM CertNameToStrA}

//+-------------------------------------------------------------------------
//--------------------------------------------------------------------------

function CertNameToStrW(dwCertEncodingType: DWORD; pName: PCERT_NAME_BLOB;
  dwStrType: DWORD; psz: LPWSTR; csz: DWORD): DWORD; stdcall;
{$EXTERNALSYM CertNameToStrW}

{$IFDEF UNICODE}
function CertNameToStr(dwCertEncodingType: DWORD; pName: PCERT_NAME_BLOB;
  dwStrType: DWORD; psz: LPWSTR; csz: DWORD): DWORD; stdcall;
{$EXTERNALSYM CertNameToStr}
{$ELSE}
function CertNameToStr(dwCertEncodingType: DWORD; pName: PCERT_NAME_BLOB;
  dwStrType: DWORD; psz: LPSTR; csz: DWORD): DWORD; stdcall;
{$EXTERNALSYM CertNameToStr}
{$ENDIF}

//+-------------------------------------------------------------------------
//  Certificate name string types
//--------------------------------------------------------------------------

const
  CERT_SIMPLE_NAME_STR = 1;
  {$EXTERNALSYM CERT_SIMPLE_NAME_STR}
  CERT_OID_NAME_STR    = 2;
  {$EXTERNALSYM CERT_OID_NAME_STR}
  CERT_X500_NAME_STR   = 3;
  {$EXTERNALSYM CERT_X500_NAME_STR}

//+-------------------------------------------------------------------------
//  Certificate name string type flags OR'ed with the above types
//--------------------------------------------------------------------------

  CERT_NAME_STR_SEMICOLON_FLAG  = $40000000;
  {$EXTERNALSYM CERT_NAME_STR_SEMICOLON_FLAG}
  CERT_NAME_STR_NO_PLUS_FLAG    = $20000000;
  {$EXTERNALSYM CERT_NAME_STR_NO_PLUS_FLAG}
  CERT_NAME_STR_NO_QUOTING_FLAG = $10000000;
  {$EXTERNALSYM CERT_NAME_STR_NO_QUOTING_FLAG}
  CERT_NAME_STR_CRLF_FLAG       = $08000000;
  {$EXTERNALSYM CERT_NAME_STR_CRLF_FLAG}
  CERT_NAME_STR_COMMA_FLAG      = $04000000;
  {$EXTERNALSYM CERT_NAME_STR_COMMA_FLAG}
  CERT_NAME_STR_REVERSE_FLAG    = $02000000;
  {$EXTERNALSYM CERT_NAME_STR_REVERSE_FLAG}

  CERT_NAME_STR_DISABLE_IE4_UTF8_FLAG    = $00010000;
  {$EXTERNALSYM CERT_NAME_STR_DISABLE_IE4_UTF8_FLAG}
  CERT_NAME_STR_ENABLE_T61_UNICODE_FLAG  = $00020000;
  {$EXTERNALSYM CERT_NAME_STR_ENABLE_T61_UNICODE_FLAG}
  CERT_NAME_STR_ENABLE_UTF8_UNICODE_FLAG = $00040000;
  {$EXTERNALSYM CERT_NAME_STR_ENABLE_UTF8_UNICODE_FLAG}

//+-------------------------------------------------------------------------
//  Convert the null terminated X500 string to an encoded certificate name.
//
//  The input string is expected to be formatted the same as the output
//  from the above CertNameToStr API.
//
//  The CERT_SIMPLE_NAME_STR type isn't supported. Otherwise, when dwStrType
//  is set to 0, CERT_OID_NAME_STR or CERT_X500_NAME_STR, allow either a
//  case insensitive X500 key (CN=), case insensitive "OID." prefixed
//  object identifier (OID.1.2.3.4.5.6=) or an object identifier (1.2.3.4=).
//
//  If no flags are OR'ed into dwStrType, then, allow "," or ";" as RDN
//  separators and "+" as the multiple RDN value separator. Quoting is
//  supported. A quote may be included in a quoted value by double quoting,
//  for example (CN="Joe ""Cool"""). A value starting with a "#" is treated
//  as ascii hex and converted to a CERT_RDN_OCTET_STRING. Embedded whitespace
//  is skipped (1.2.3 = # AB CD 01  is the same as 1.2.3=#ABCD01).
//
//  Whitespace surrounding the keys, object identifers and values is removed.
//
//  CERT_NAME_STR_COMMA_FLAG can be or'ed into dwStrType to only allow the
//  "," as the RDN separator.
//
//  CERT_NAME_STR_SEMICOLON_FLAG can be or'ed into dwStrType to only allow the
//  ";" as the RDN separator.
//
//  CERT_NAME_STR_CRLF_FLAG can be or'ed into dwStrType to only allow
//  "\r" or "\n" as the RDN separator.
//
//  CERT_NAME_STR_NO_PLUS_FLAG can be or'ed into dwStrType to ignore "+"
//  as a separator and not allow multiple values per RDN.
//
//  CERT_NAME_STR_NO_QUOTING_FLAG can be or'ed into dwStrType to inhibit
//  quoting.
//
//  CERT_NAME_STR_REVERSE_FLAG can be or'ed into dwStrType to reverse the
//  order of the RDNs after converting from the string and before encoding.
//
//  CERT_NAME_STR_ENABLE_T61_UNICODE_FLAG can be or'ed into dwStrType to
//  to select the CERT_RDN_T61_STRING encoded value type instead of
//  CERT_RDN_UNICODE_STRING if all the UNICODE characters are <= 0xFF.
//
//  CERT_NAME_STR_ENABLE_UTF8_UNICODE_FLAG can be or'ed into dwStrType to
//  to select the CERT_RDN_UTF8_STRING encoded value type instead of
//  CERT_RDN_UNICODE_STRING.
//
//  Support the following X500 Keys:
//
//  Key         Object Identifier               RDN Value Type(s)
//  ---         -----------------               -----------------
//  CN          szOID_COMMON_NAME               Printable, Unicode
//  L           szOID_LOCALITY_NAME             Printable, Unicode
//  O           szOID_ORGANIZATION_NAME         Printable, Unicode
//  OU          szOID_ORGANIZATIONAL_UNIT_NAME  Printable, Unicode
//  E           szOID_RSA_emailAddr             Only IA5
//  Email       szOID_RSA_emailAddr             Only IA5
//  C           szOID_COUNTRY_NAME              Only Printable
//  S           szOID_STATE_OR_PROVINCE_NAME    Printable, Unicode
//  ST          szOID_STATE_OR_PROVINCE_NAME    Printable, Unicode
//  STREET      szOID_STREET_ADDRESS            Printable, Unicode
//  T           szOID_TITLE                     Printable, Unicode
//  Title       szOID_TITLE                     Printable, Unicode
//  G           szOID_GIVEN_NAME                Printable, Unicode
//  GivenName   szOID_GIVEN_NAME                Printable, Unicode
//  I           szOID_INITIALS                  Printable, Unicode
//  Initials    szOID_INITIALS                  Printable, Unicode
//  SN          szOID_SUR_NAME                  Printable, Unicode
//  DC          szOID_DOMAIN_COMPONENT          IA5, UTF8
//
//  Note, T61 is selected instead of Unicode if
//  CERT_NAME_STR_ENABLE_T61_UNICODE_FLAG is set and all the unicode
//  characters are <= 0xFF.
//
//  Note, UTF8 is selected instead of Unicode if
//  CERT_NAME_STR_ENABLE_UTF8_UNICODE_FLAG is set.
//
//  Returns TRUE if successfully parsed the input string and encoded
//  the name.
//
//  If the input string is detected to be invalid, *ppszError is updated
//  to point to the beginning of the invalid character sequence. Otherwise,
//  *ppszError is set to NULL. *ppszError is updated with a non-NULL pointer
//  for the following errors:
//      CRYPT_E_INVALID_X500_STRING
//      CRYPT_E_INVALID_NUMERIC_STRING
//      CRYPT_E_INVALID_PRINTABLE_STRING
//      CRYPT_E_INVALID_IA5_STRING
//
//  ppszError can be set to NULL if not interested in getting a pointer
//  to the invalid character sequence.
//--------------------------------------------------------------------------

//+-------------------------------------------------------------------------
//--------------------------------------------------------------------------

function CertStrToNameA(dwCertEncodingType: DWORD; pszX500: LPCSTR;
  dwStrType: DWORD; pvReserved: Pointer; pbEncoded: LPBYTE; var pcbEncoded: DWORD;
  ppszError: LPLPCSTR): BOOL; stdcall;
{$EXTERNALSYM CertStrToNameA}
function CertStrToNameW(dwCertEncodingType: DWORD; pszX500: LPCWSTR;
  dwStrType: DWORD; pvReserved: Pointer; pbEncoded: LPBYTE; var pcbEncoded: DWORD;
  ppszError: LPLPCWSTR): BOOL; stdcall;
{$EXTERNALSYM CertStrToNameW}

{$IFDEF UNICODE}
function CertStrToName(dwCertEncodingType: DWORD; pszX500: LPCWSTR;
  dwStrType: DWORD; pvReserved: Pointer; pbEncoded: LPBYTE; var pcbEncoded: DWORD;
  ppszError: LPLPCWSTR): BOOL; stdcall;
{$EXTERNALSYM CertStrToName}
{$ELSE}
function CertStrToName(dwCertEncodingType: DWORD; pszX500: LPCSTR;
  dwStrType: DWORD; pvReserved: Pointer; pbEncoded: LPBYTE; var pcbEncoded: DWORD;
  ppszError: LPLPCSTR): BOOL; stdcall;
{$EXTERNALSYM CertStrToName}
{$ENDIF}

//+-------------------------------------------------------------------------
//  Get the subject or issuer name from the certificate and
//  according to the specified format type, convert to a null terminated
//  character string.
//
//  CERT_NAME_ISSUER_FLAG can be set to get the issuer's name. Otherwise,
//  gets the subject's name.
//
//  By default, CERT_RDN_T61_STRING encoded values are initially decoded
//  as UTF8. If the UTF8 decoding fails, then, decoded as 8 bit characters.
//  CERT_NAME_DISABLE_IE4_UTF8_FLAG can be set in dwFlags to
//  skip the initial attempt to decode as UTF8.
//
//  The name string is formatted according to the dwType:
//    CERT_NAME_EMAIL_TYPE
//      If the certificate has a Subject Alternative Name extension (for
//      issuer, Issuer Alternative Name), searches for first rfc822Name choice.
//      If the rfc822Name choice isn't found in the extension, searches the
//      Subject Name field for the Email OID, "1.2.840.113549.1.9.1".
//      If the rfc822Name or Email OID is found, returns the string. Otherwise,
//      returns an empty string (returned character count is 1).
//    CERT_NAME_RDN_TYPE
//      Converts the Subject Name blob by calling CertNameToStr. pvTypePara
//      points to a DWORD containing the dwStrType passed to CertNameToStr.
//      If the Subject Name field is empty and the certificate has a
//      Subject Alternative Name extension, searches for and converts
//      the first directoryName choice.
//    CERT_NAME_ATTR_TYPE
//      pvTypePara points to the Object Identifier specifying the name attribute
//      to be returned. For example, to get the CN,
//      pvTypePara = szOID_COMMON_NAME ("2.5.4.3"). Searches, the Subject Name
//      field for the attribute.
//      If the Subject Name field is empty and the certificate has a
//      Subject Alternative Name extension, checks for
//      the first directoryName choice and searches it.
//
//      Note, searches the RDNs in reverse order.
//
//    CERT_NAME_SIMPLE_DISPLAY_TYPE
//      Iterates through the following list of name attributes and searches
//      the Subject Name and then the Subject Alternative Name extension
//      for the first occurrence of:
//          szOID_COMMON_NAME ("2.5.4.3")
//          szOID_ORGANIZATIONAL_UNIT_NAME ("2.5.4.11")
//          szOID_ORGANIZATION_NAME ("2.5.4.10")
//          szOID_RSA_emailAddr ("1.2.840.113549.1.9.1")
//
//      If none of the above attributes is found, then, searches the
//      Subject Alternative Name extension for a rfc822Name choice.
//
//      If still no match, then, returns the first attribute.
//
//      Note, like CERT_NAME_ATTR_TYPE, searches the RDNs in reverse order.
//
//    CERT_NAME_FRIENDLY_DISPLAY_TYPE
//      First checks if the certificate has a CERT_FRIENDLY_NAME_PROP_ID
//      property. If it does, then, this property is returned. Otherwise,
//      returns the above CERT_NAME_SIMPLE_DISPLAY_TYPE.
//
//  Returns the number of characters converted including the terminating null
//  character. If pwszNameString is NULL or cchNameString is 0, returns the
//  required size of the destination string (including the terminating null
//  char). If the specified name type isn't found. returns an empty string
//  with a returned character count of 1.
//
//  If pwszNameString != NULL && cwszNameString != 0, returned pwszNameString
//  is always NULL terminated.
//
//  Note: cchNameString includes the NULL char.
//--------------------------------------------------------------------------

//+-------------------------------------------------------------------------
//--------------------------------------------------------------------------

function CertGetNameStringA(pCertContext: PCCERT_CONTEXT; dwType, dwFlags: DWORD;
  pvTypePara: Pointer; pszNameString: LPSTR; cchNameString: DWORD): DWORD; stdcall;
{$EXTERNALSYM CertGetNameStringA}
function CertGetNameStringW(pCertContext: PCCERT_CONTEXT; dwType, dwFlags: DWORD;
  pvTypePara: Pointer; pszNameString: LPWSTR; cchNameString: DWORD): DWORD; stdcall;
{$EXTERNALSYM CertGetNameStringW}

{$IFDEF UNICODE}
function CertGetNameString(pCertContext: PCCERT_CONTEXT; dwType, dwFlags: DWORD;
  pvTypePara: Pointer; pszNameString: LPWSTR; cchNameString: DWORD): DWORD; stdcall;
{$EXTERNALSYM CertGetNameString}
{$ELSE}
function CertGetNameString(pCertContext: PCCERT_CONTEXT; dwType, dwFlags: DWORD;
  pvTypePara: Pointer; pszNameString: LPSTR; cchNameString: DWORD): DWORD; stdcall;
{$EXTERNALSYM CertGetNameString}
{$ENDIF}

//+-------------------------------------------------------------------------
//  Certificate name types
//--------------------------------------------------------------------------

const
  CERT_NAME_EMAIL_TYPE            = 1;
  {$EXTERNALSYM CERT_NAME_EMAIL_TYPE}
  CERT_NAME_RDN_TYPE              = 2;
  {$EXTERNALSYM CERT_NAME_RDN_TYPE}
  CERT_NAME_ATTR_TYPE             = 3;
  {$EXTERNALSYM CERT_NAME_ATTR_TYPE}
  CERT_NAME_SIMPLE_DISPLAY_TYPE   = 4;
  {$EXTERNALSYM CERT_NAME_SIMPLE_DISPLAY_TYPE}
  CERT_NAME_FRIENDLY_DISPLAY_TYPE = 5;
  {$EXTERNALSYM CERT_NAME_FRIENDLY_DISPLAY_TYPE}

//+-------------------------------------------------------------------------
//  Certificate name flags
//--------------------------------------------------------------------------

  CERT_NAME_ISSUER_FLAG           = $1;
  {$EXTERNALSYM CERT_NAME_ISSUER_FLAG}
  CERT_NAME_DISABLE_IE4_UTF8_FLAG = $00010000;
  {$EXTERNALSYM CERT_NAME_DISABLE_IE4_UTF8_FLAG}

//+=========================================================================
//  Simplified Cryptographic Message Data Structures and APIs
//==========================================================================


//+-------------------------------------------------------------------------
//              Conventions for the *pb and *pcb output parameters:
//
//              Upon entry to the function:
//                  if pcb is OPTIONAL && pcb == NULL, then,
//                      No output is returned
//                  else if pb == NULL && pcb != NULL, then,
//                      Length only determination. No length error is
//                      returned.
//                  otherwise where (pb != NULL && pcb != NULL && *pcb != 0)
//                      Output is returned. If *pcb isn't big enough a
//                      length error is returned. In all cases *pcb is updated
//                      with the actual length needed/returned.
//--------------------------------------------------------------------------


//+-------------------------------------------------------------------------
//  Type definitions of the parameters used for doing the cryptographic
//  operations.
//--------------------------------------------------------------------------

//+-------------------------------------------------------------------------
//  Callback to get and verify the signer's certificate.
//
//  Passed the CertId of the signer (its Issuer and SerialNumber) and a
//  handle to its cryptographic signed message's cert store.
//
//  For CRYPT_E_NO_SIGNER, called with pSignerId == NULL.
//
//  For a valid signer certificate, returns a pointer to a read only
//  CERT_CONTEXT. The returned CERT_CONTEXT is either obtained from a
//  cert store or was created via CertCreateCertificateContext. For either case,
//  its freed via CertFreeCertificateContext.
//
//  If a valid certificate isn't found, this callback returns NULL with
//  LastError set via SetLastError().
//
//  The NULL implementation tries to get the Signer certificate from the
//  message cert store. It doesn't verify the certificate.
//
//  Note, if the KEYID choice was selected for a CMS SignerId, then, the
//  SerialNumber is 0 and the Issuer is encoded containing a single RDN with a
//  single Attribute whose OID is szOID_KEYID_RDN, value type is
//  CERT_RDN_OCTET_STRING and value is the KEYID. When the
//  CertGetSubjectCertificateFromStore and
//  CertFindCertificateInStore(CERT_FIND_SUBJECT_CERT) APIs see this
//  special KEYID Issuer and SerialNumber, they do a KEYID match.
//--------------------------------------------------------------------------

type
  PFN_CRYPT_GET_SIGNER_CERTIFICATE = function (pvGetArg: Pointer;
    dwCertEncodingType: DWORD; pSignerId: PCERT_INFO;
    hMsgCertStore: HCERTSTORE): PCCERT_CONTEXT; stdcall;
  {$EXTERNALSYM PFN_CRYPT_GET_SIGNER_CERTIFICATE}
  PfnCryptGetSignerCertificate = PFN_CRYPT_GET_SIGNER_CERTIFICATE;

//+-------------------------------------------------------------------------
//  The CRYPT_SIGN_MESSAGE_PARA are used for signing messages using the
//  specified signing certificate context.
//
//  Either the CERT_KEY_PROV_HANDLE_PROP_ID or CERT_KEY_PROV_INFO_PROP_ID must
//  be set for each rgpSigningCert[]. Either one specifies the private
//  signature key to use.
//
//  If any certificates and/or CRLs are to be included in the signed message,
//  then, the MsgCert and MsgCrl parameters need to be updated. If the
//  rgpSigningCerts are to be included, then, they must also be in the
//  rgpMsgCert array.
//
//  cbSize must be set to the sizeof(CRYPT_SIGN_MESSAGE_PARA) or else
//  LastError will be updated with E_INVALIDARG.
//
//  pvHashAuxInfo currently isn't used and must be set to NULL.
//
//  dwFlags normally is set to 0. However, if the encoded output
//  is to be a CMSG_SIGNED inner content of an outer cryptographic message,
//  such as a CMSG_ENVELOPED, then, the CRYPT_MESSAGE_BARE_CONTENT_OUT_FLAG
//  should be set. If not set, then it would be encoded as an inner content
//  type of CMSG_DATA.
//
//  dwInnerContentType is normally set to 0. It needs to be set if the
//  ToBeSigned input is the encoded output of another cryptographic
//  message, such as, an CMSG_ENVELOPED. When set, it's one of the cryptographic
//  message types, for example, CMSG_ENVELOPED.
//
//  If the inner content of a nested cryptographic message is data (CMSG_DATA
//  the default), then, neither dwFlags or dwInnerContentType need to be set.
//
//  For CMS messages, CRYPT_MESSAGE_ENCAPSULATED_CONTENT_OUT_FLAG may be
//  set to encapsulate nonData inner content within an OCTET STRING.
//
//  For CMS messages, CRYPT_MESSAGE_KEYID_SIGNER_FLAG may be set to identify
//  signers by their Key Identifier and not their Issuer and Serial Number.
//
//  If HashEncryptionAlgorithm is present and not NULL its used instead of
//  the SigningCert's PublicKeyInfo.Algorithm.
//
//  Note, for RSA, the hash encryption algorithm is normally the same as
//  the public key algorithm. For DSA, the hash encryption algorithm is
//  normally a DSS signature algorithm.
//
//  pvHashEncryptionAuxInfo currently isn't used and must be set to NULL if
//  present in the data structure.
//--------------------------------------------------------------------------

type
  PCRYPT_SIGN_MESSAGE_PARA = ^CRYPT_SIGN_MESSAGE_PARA;
  {$EXTERNALSYM PCRYPT_SIGN_MESSAGE_PARA}
  _CRYPT_SIGN_MESSAGE_PARA = record
    cbSize: DWORD;
    dwMsgEncodingType: DWORD;
    pSigningCert: PCCERT_CONTEXT;
    HashAlgorithm: CRYPT_ALGORITHM_IDENTIFIER;
    pvHashAuxInfo: Pointer;
    cMsgCert: DWORD;
    rgpMsgCert: PPCCERT_CONTEXT;
    cMsgCrl: DWORD;
    rgpMsgCrl: PPCCRL_CONTEXT;
    cAuthAttr: DWORD;
    rgAuthAttr: PCRYPT_ATTRIBUTE;
    cUnauthAttr: DWORD;
    rgUnauthAttr: PCRYPT_ATTRIBUTE;
    dwFlags: DWORD;
    dwInnerContentType: DWORD;
    {$IFDEF CRYPT_SIGN_MESSAGE_PARA_HAS_CMS_FIELDS}
    HashEncryptionAlgorithm: CRYPT_ALGORITHM_IDENTIFIER;
    pvHashEncryptionAuxInfo: Pointer;
    {$ENDIF}
  end;
  {$EXTERNALSYM _CRYPT_SIGN_MESSAGE_PARA}
  CRYPT_SIGN_MESSAGE_PARA = _CRYPT_SIGN_MESSAGE_PARA;
  {$EXTERNALSYM CRYPT_SIGN_MESSAGE_PARA}
  TCryptSignMessagePara = CRYPT_SIGN_MESSAGE_PARA;
  PCryptSignMessagePara = PCRYPT_SIGN_MESSAGE_PARA;

const
  CRYPT_MESSAGE_BARE_CONTENT_OUT_FLAG = $1;
  {$EXTERNALSYM CRYPT_MESSAGE_BARE_CONTENT_OUT_FLAG}

// When set, nonData type inner content is encapsulated within an
// OCTET STRING

  CRYPT_MESSAGE_ENCAPSULATED_CONTENT_OUT_FLAG = $2;
  {$EXTERNALSYM CRYPT_MESSAGE_ENCAPSULATED_CONTENT_OUT_FLAG}

// When set, signers are identified by their Key Identifier and not
// their Issuer and Serial Number.

  CRYPT_MESSAGE_KEYID_SIGNER_FLAG = $4;
  {$EXTERNALSYM CRYPT_MESSAGE_KEYID_SIGNER_FLAG}

//+-------------------------------------------------------------------------
//  The CRYPT_VERIFY_MESSAGE_PARA are used to verify signed messages.
//
//  hCryptProv is used to do hashing and signature verification.
//
//  The dwCertEncodingType specifies the encoding type of the certificates
//  and/or CRLs in the message.
//
//  pfnGetSignerCertificate is called to get and verify the message signer's
//  certificate.
//
//  cbSize must be set to the sizeof(CRYPT_VERIFY_MESSAGE_PARA) or else
//  LastError will be updated with E_INVALIDARG.
//--------------------------------------------------------------------------

type
  PCRYPT_VERIFY_MESSAGE_PARA = ^CRYPT_VERIFY_MESSAGE_PARA;
  {$EXTERNALSYM PCRYPT_VERIFY_MESSAGE_PARA}
  _CRYPT_VERIFY_MESSAGE_PARA = record
    cbSize: DWORD;
    dwMsgAndCertEncodingType: DWORD;
    hCryptProv: HCRYPTPROV;
    pfnGetSignerCertificate: PFN_CRYPT_GET_SIGNER_CERTIFICATE;
    pvGetArg: Pointer;
  end;
  {$EXTERNALSYM _CRYPT_VERIFY_MESSAGE_PARA}
  CRYPT_VERIFY_MESSAGE_PARA = _CRYPT_VERIFY_MESSAGE_PARA;
  {$EXTERNALSYM CRYPT_VERIFY_MESSAGE_PARA}
  TCryptVerifyMessagePara = CRYPT_VERIFY_MESSAGE_PARA;
  PCryptVerifyMessagePara = PCRYPT_VERIFY_MESSAGE_PARA;

//+-------------------------------------------------------------------------
//  The CRYPT_ENCRYPT_MESSAGE_PARA are used for encrypting messages.
//
//  hCryptProv is used to do content encryption, recipient key
//  encryption, and recipient key export. Its private key
//  isn't used.
//
//  Currently, pvEncryptionAuxInfo is only defined for RC2 or RC4 encryption
//  algorithms. Otherwise, its not used and must be set to NULL.
//  See CMSG_RC2_AUX_INFO for the RC2 encryption algorithms.
//  See CMSG_RC4_AUX_INFO for the RC4 encryption algorithms.
//
//  To enable SP3 compatible encryption, pvEncryptionAuxInfo should point to
//  a CMSG_SP3_COMPATIBLE_AUX_INFO data structure.
//
//  cbSize must be set to the sizeof(CRYPT_ENCRYPT_MESSAGE_PARA) or else
//  LastError will be updated with E_INVALIDARG.
//
//  dwFlags normally is set to 0. However, if the encoded output
//  is to be a CMSG_ENVELOPED inner content of an outer cryptographic message,
//  such as a CMSG_SIGNED, then, the CRYPT_MESSAGE_BARE_CONTENT_OUT_FLAG
//  should be set. If not set, then it would be encoded as an inner content
//  type of CMSG_DATA.
//
//  dwInnerContentType is normally set to 0. It needs to be set if the
//  ToBeEncrypted input is the encoded output of another cryptographic
//  message, such as, an CMSG_SIGNED. When set, it's one of the cryptographic
//  message types, for example, CMSG_SIGNED.
//
//  If the inner content of a nested cryptographic message is data (CMSG_DATA
//  the default), then, neither dwFlags or dwInnerContentType need to be set.
//
//  For CMS messages, CRYPT_MESSAGE_ENCAPSULATED_CONTENT_OUT_FLAG may be
//  set to encapsulate nonData inner content within an OCTET STRING before
//  encrypting.
//
//  For CMS messages, CRYPT_MESSAGE_KEYID_RECIPIENT_FLAG may be set to identify
//  recipients by their Key Identifier and not their Issuer and Serial Number.
//--------------------------------------------------------------------------

type
  PCRYPT_ENCRYPT_MESSAGE_PARA = ^CRYPT_ENCRYPT_MESSAGE_PARA;
  {$EXTERNALSYM PCRYPT_ENCRYPT_MESSAGE_PARA}
  _CRYPT_ENCRYPT_MESSAGE_PARA = record
    cbSize: DWORD;
    dwMsgEncodingType: DWORD;
    hCryptProv: HCRYPTPROV;
    ContentEncryptionAlgorithm: CRYPT_ALGORITHM_IDENTIFIER;
    pvEncryptionAuxInfo: Pointer;
    dwFlags: DWORD;
    dwInnerContentType: DWORD;
  end;
  {$EXTERNALSYM _CRYPT_ENCRYPT_MESSAGE_PARA}
  CRYPT_ENCRYPT_MESSAGE_PARA = _CRYPT_ENCRYPT_MESSAGE_PARA;
  {$EXTERNALSYM CRYPT_ENCRYPT_MESSAGE_PARA}
  TCryptEncryptMessagePara = CRYPT_ENCRYPT_MESSAGE_PARA;
  PCryptEncryptMessagePara = PCRYPT_ENCRYPT_MESSAGE_PARA;

// When set, recipients are identified by their Key Identifier and not
// their Issuer and Serial Number.

const
  CRYPT_MESSAGE_KEYID_RECIPIENT_FLAG = $4;
  {$EXTERNALSYM CRYPT_MESSAGE_KEYID_RECIPIENT_FLAG}

//+-------------------------------------------------------------------------
//  The CRYPT_DECRYPT_MESSAGE_PARA are used for decrypting messages.
//
//  The CertContext to use for decrypting a message is obtained from one
//  of the specified cert stores. An encrypted message can have one or
//  more recipients. The recipients are identified by their CertId (Issuer
//  and SerialNumber). The cert stores are searched to find the CertContext
//  corresponding to the CertId.
//
//  For CMS, the recipients may also be identified by their KeyId.
//  CMS also allows Key Agreement (Diffie Hellman) in addition to
//  Key Transport (RSA) recipients.
//
//  Only CertContexts in the store with either
//  the CERT_KEY_PROV_HANDLE_PROP_ID or CERT_KEY_PROV_INFO_PROP_ID set
//  can be used. Either property specifies the private exchange key to use.
//
//  cbSize must be set to the sizeof(CRYPT_DECRYPT_MESSAGE_PARA) or else
//  LastError will be updated with E_INVALIDARG.
//--------------------------------------------------------------------------

type
  PCRYPT_DECRYPT_MESSAGE_PARA = ^CRYPT_DECRYPT_MESSAGE_PARA;
  {$EXTERNALSYM PCRYPT_DECRYPT_MESSAGE_PARA}
  _CRYPT_DECRYPT_MESSAGE_PARA = record
    cbSize: DWORD;
    dwMsgAndCertEncodingType: DWORD;
    cCertStore: DWORD;
    rghCertStore: PHCERTSTORE;
  end;
  {$EXTERNALSYM _CRYPT_DECRYPT_MESSAGE_PARA}
  CRYPT_DECRYPT_MESSAGE_PARA = _CRYPT_DECRYPT_MESSAGE_PARA;
  {$EXTERNALSYM CRYPT_DECRYPT_MESSAGE_PARA}
  TCryptDecryptMessagePara = CRYPT_DECRYPT_MESSAGE_PARA;
  PCryptDecryptMessagePara = PCRYPT_DECRYPT_MESSAGE_PARA;

//+-------------------------------------------------------------------------
//  The CRYPT_HASH_MESSAGE_PARA are used for hashing or unhashing
//  messages.
//
//  hCryptProv is used to compute the hash.
//
//  pvHashAuxInfo currently isn't used and must be set to NULL.
//
//  cbSize must be set to the sizeof(CRYPT_HASH_MESSAGE_PARA) or else
//  LastError will be updated with E_INVALIDARG.
//--------------------------------------------------------------------------

  PCRYPT_HASH_MESSAGE_PARA = ^CRYPT_HASH_MESSAGE_PARA;
  {$EXTERNALSYM PCRYPT_HASH_MESSAGE_PARA}
  _CRYPT_HASH_MESSAGE_PARA = record
    cbSize: DWORD;
    dwMsgEncodingType: DWORD;
    hCryptProv: HCRYPTPROV;
    HashAlgorithm: CRYPT_ALGORITHM_IDENTIFIER;
    pvHashAuxInfo: Pointer;
  end;
  {$EXTERNALSYM _CRYPT_HASH_MESSAGE_PARA}
  CRYPT_HASH_MESSAGE_PARA = _CRYPT_HASH_MESSAGE_PARA;
  {$EXTERNALSYM CRYPT_HASH_MESSAGE_PARA}
  TCryptHashMessagePara = CRYPT_HASH_MESSAGE_PARA;
  PCryptHashMessagePara = PCRYPT_HASH_MESSAGE_PARA;

//+-------------------------------------------------------------------------
//  The CRYPT_KEY_SIGN_MESSAGE_PARA are used for signing messages until a
//  certificate has been created for the signature key.
//
//  pvHashAuxInfo currently isn't used and must be set to NULL.
//
//  If PubKeyAlgorithm isn't set, defaults to szOID_RSA_RSA.
//
//  cbSize must be set to the sizeof(CRYPT_KEY_SIGN_MESSAGE_PARA) or else
//  LastError will be updated with E_INVALIDARG.
//--------------------------------------------------------------------------

  PCRYPT_KEY_SIGN_MESSAGE_PARA = ^CRYPT_KEY_SIGN_MESSAGE_PARA;
  {$EXTERNALSYM PCRYPT_KEY_SIGN_MESSAGE_PARA}
  _CRYPT_KEY_SIGN_MESSAGE_PARA = record
    cbSize: DWORD;
    dwMsgAndCertEncodingType: DWORD;
    hCryptProv: HCRYPTPROV;
    dwKeySpec: DWORD;
    HashAlgorithm: CRYPT_ALGORITHM_IDENTIFIER;
    pvHashAuxInfo: Pointer;
    PubKeyAlgorithm: CRYPT_ALGORITHM_IDENTIFIER;
  end;
  {$EXTERNALSYM _CRYPT_KEY_SIGN_MESSAGE_PARA}
  CRYPT_KEY_SIGN_MESSAGE_PARA = _CRYPT_KEY_SIGN_MESSAGE_PARA;
  {$EXTERNALSYM CRYPT_KEY_SIGN_MESSAGE_PARA}
  TCryptKeySignMessagePara = CRYPT_KEY_SIGN_MESSAGE_PARA;
  PCryptKeySignMessagePara = PCRYPT_KEY_SIGN_MESSAGE_PARA;

//+-------------------------------------------------------------------------
//  The CRYPT_KEY_VERIFY_MESSAGE_PARA are used to verify signed messages without
//  a certificate for the signer.
//
//  Normally used until a certificate has been created for the key.
//
//  hCryptProv is used to do hashing and signature verification.
//
//  cbSize must be set to the sizeof(CRYPT_KEY_VERIFY_MESSAGE_PARA) or else
//  LastError will be updated with E_INVALIDARG.
//--------------------------------------------------------------------------

  PCRYPT_KEY_VERIFY_MESSAGE_PARA = ^CRYPT_KEY_VERIFY_MESSAGE_PARA;
  {$EXTERNALSYM PCRYPT_KEY_VERIFY_MESSAGE_PARA}
  _CRYPT_KEY_VERIFY_MESSAGE_PARA = record
    cbSize: DWORD;
    dwMsgEncodingType: DWORD;
    hCryptProv: HCRYPTPROV;
  end;
  {$EXTERNALSYM _CRYPT_KEY_VERIFY_MESSAGE_PARA}
  CRYPT_KEY_VERIFY_MESSAGE_PARA = _CRYPT_KEY_VERIFY_MESSAGE_PARA;
  {$EXTERNALSYM CRYPT_KEY_VERIFY_MESSAGE_PARA}
  TCryptKeyVerifyMessagePara = CRYPT_KEY_VERIFY_MESSAGE_PARA;
  PCryptKeyVerifyMessagePara = PCRYPT_KEY_VERIFY_MESSAGE_PARA;

//+-------------------------------------------------------------------------
//  Sign the message.
//
//  If fDetachedSignature is TRUE, the "to be signed" content isn't included
//  in the encoded signed blob.
//--------------------------------------------------------------------------

function CryptSignMessage(pSignPara: PCRYPT_SIGN_MESSAGE_PARA;
  fDetachedSignature: BOOL; cToBeSigned: DWORD; rgpbToBeSigned: LPBYTE;
  rgcbToBeSigned: LPDWORD; pbSignedBlob: LPBYTE; var pcbSignedBlob: DWORD): BOOL; stdcall;
{$EXTERNALSYM CryptSignMessage}

//+-------------------------------------------------------------------------
//  Verify a signed message.
//
//  If pbDecoded == NULL, then, *pcbDecoded is implicitly set to 0 on input.
//  For *pcbDecoded == 0 && ppSignerCert == NULL on input, the signer isn't
//  verified.
//
//  A message might have more than one signer. Set dwSignerIndex to iterate
//  through all the signers. dwSignerIndex == 0 selects the first signer.
//
//  pVerifyPara's pfnGetSignerCertificate is called to get the signer's
//  certificate.
//
//  For a verified signer and message, *ppSignerCert is updated
//  with the CertContext of the signer. It must be freed by calling
//  CertFreeCertificateContext. Otherwise, *ppSignerCert is set to NULL.
//
//  ppSignerCert can be NULL, indicating the caller isn't interested
//  in getting the CertContext of the signer.
//
//  pcbDecoded can be NULL, indicating the caller isn't interested in getting
//  the decoded content. Furthermore, if the message doesn't contain any
//  content or signers, then, pcbDecoded must be set to NULL, to allow the
//  pVerifyPara->pfnGetCertificate to be called. Normally, this would be
//  the case when the signed message contains only certficates and CRLs.
//  If pcbDecoded is NULL and the message doesn't have the indicated signer,
//  pfnGetCertificate is called with pSignerId set to NULL.
//
//  If the message doesn't contain any signers || dwSignerIndex > message's
//  SignerCount, then, an error is returned with LastError set to
//  CRYPT_E_NO_SIGNER. Also, for CRYPT_E_NO_SIGNER, pfnGetSignerCertificate
//  is still called with pSignerId set to NULL.
//
//  Note, an alternative way to get the certificates and CRLs from a
//  signed message is to call CryptGetMessageCertificates.
//--------------------------------------------------------------------------

function CryptVerifyMessageSignature(pVerifyPara: PCRYPT_VERIFY_MESSAGE_PARA;
  dwSignerIndex: DWORD; pbSignedBlob: LPBYTE; cbSignedBlob: DWORD;
  pbDecoded: LPBYTE; pcbDecoded: LPDWORD; ppSignerCert: PPCCERT_CONTEXT): BOOL; stdcall;
{$EXTERNALSYM CryptVerifyMessageSignature}

//+-------------------------------------------------------------------------
//  Returns the count of signers in the signed message. For no signers, returns
//  0. For an error returns -1 with LastError updated accordingly.
//--------------------------------------------------------------------------

function CryptGetMessageSignerCount(dwMsgEncodingType: DWORD; pbSignedBlob: LPBYTE;
  cbSignedBlob: DWORD): LONG; stdcall;
{$EXTERNALSYM CryptGetMessageSignerCount}

//+-------------------------------------------------------------------------
//  Returns the cert store containing the message's certs and CRLs.
//  For an error, returns NULL with LastError updated.
//--------------------------------------------------------------------------

function CryptGetMessageCertificates(dwMsgAndCertEncodingType: DWORD;
  hCryptProv: HCRYPTPROV; dwFlags: DWORD; pbSignedBlob: LPBYTE;
  cbSignedBlob: DWORD): HCERTSTORE; stdcall;
{$EXTERNALSYM CryptGetMessageCertificates}

//+-------------------------------------------------------------------------
//  Verify a signed message containing detached signature(s).
//  The "to be signed" content is passed in separately. No
//  decoded output. Otherwise, identical to CryptVerifyMessageSignature.
//--------------------------------------------------------------------------

function CryptVerifyDetachedMessageSignature(pVerifyPara: PCRYPT_VERIFY_MESSAGE_PARA;
  dwSignerIndex: DWORD; pbDetachedSignBlob: LPBYTE; cbDetachedSignBlob: DWORD;
  cToBeSigned: DWORD; rgpbToBeSigned: LPBYTE; rgcbToBeSigned: LPDWORD;
  ppSignerCert: PPCCERT_CONTEXT): BOOL; stdcall;
{$EXTERNALSYM CryptVerifyDetachedMessageSignature}

//+-------------------------------------------------------------------------
//  Encrypts the message for the recipient(s).
//--------------------------------------------------------------------------

function CryptEncryptMessage(pEncryptPara: PCRYPT_ENCRYPT_MESSAGE_PARA;
  cRecipientCert: DWORD; rgpRecipientCert: PCCERT_CONTEXT; pbToBeEncrypted: LPBYTE;
  cbToBeEncrypted: DWORD; pbEncryptedBlob: LPBYTE; var pcbEncryptedBlob: DWORD): BOOL; stdcall;
{$EXTERNALSYM CryptEncryptMessage}

//+-------------------------------------------------------------------------
//  Decrypts the message.
//
//  If pbDecrypted == NULL, then, *pcbDecrypted is implicitly set to 0 on input.
//  For *pcbDecrypted == 0 && ppXchgCert == NULL on input, the message isn't
//  decrypted.
//
//  For a successfully decrypted message, *ppXchgCert is updated
//  with the CertContext used to decrypt. It must be freed by calling
//  CertStoreFreeCert. Otherwise, *ppXchgCert is set to NULL.
//
//  ppXchgCert can be NULL, indicating the caller isn't interested
//  in getting the CertContext used to decrypt.
//--------------------------------------------------------------------------

function CryptDecryptMessage(pDecryptPara: PCRYPT_DECRYPT_MESSAGE_PARA;
  pbEncryptedBlob: LPBYTE; cbEncryptedBlob: DWORD; pbDecrypted: LPBYTE;
  pcbDecrypted: LPDWORD; ppXchgCert: PPCCERT_CONTEXT): BOOL; stdcall;
{$EXTERNALSYM CryptDecryptMessage}

//+-------------------------------------------------------------------------
//  Sign the message and encrypt for the recipient(s). Does a CryptSignMessage
//  followed with a CryptEncryptMessage.
//
//  Note: this isn't the CMSG_SIGNED_AND_ENVELOPED. Its a CMSG_SIGNED
//  inside of an CMSG_ENVELOPED.
//--------------------------------------------------------------------------

function CryptSignAndEncryptMessage(pSignPara: PCRYPT_SIGN_MESSAGE_PARA;
  pEncryptPara: PCRYPT_ENCRYPT_MESSAGE_PARA; cRecipientCert: DWORD;
  rgpRecipientCert: PCCERT_CONTEXT; pbToBeSignedAndEncrypted: LPBYTE;
  cbToBeSignedAndEncrypted: DWORD; pbSignedAndEncryptedBlob: LPBYTE;
  var pcbSignedAndEncryptedBlob: DWORD): BOOL; stdcall;
{$EXTERNALSYM CryptSignAndEncryptMessage}

//+-------------------------------------------------------------------------
//  Decrypts the message and verifies the signer. Does a CryptDecryptMessage
//  followed with a CryptVerifyMessageSignature.
//
//  If pbDecrypted == NULL, then, *pcbDecrypted is implicitly set to 0 on input.
//  For *pcbDecrypted == 0 && ppSignerCert == NULL on input, the signer isn't
//  verified.
//
//  A message might have more than one signer. Set dwSignerIndex to iterate
//  through all the signers. dwSignerIndex == 0 selects the first signer.
//
//  The pVerifyPara's VerifySignerPolicy is called to verify the signer's
//  certificate.
//
//  For a successfully decrypted and verified message, *ppXchgCert and
//  *ppSignerCert are updated. They must be freed by calling
//  CertStoreFreeCert. Otherwise, they are set to NULL.
//
//  ppXchgCert and/or ppSignerCert can be NULL, indicating the
//  caller isn't interested in getting the CertContext.
//
//  Note: this isn't the CMSG_SIGNED_AND_ENVELOPED. Its a CMSG_SIGNED
//  inside of an CMSG_ENVELOPED.
//
//  The message always needs to be decrypted to allow access to the
//  signed message. Therefore, if ppXchgCert != NULL, its always updated.
//--------------------------------------------------------------------------

function CryptDecryptAndVerifyMessageSignature(pDecryptPara: PCRYPT_DECRYPT_MESSAGE_PARA;
  pVerifyPara: PCRYPT_VERIFY_MESSAGE_PARA; dwSignerIndex: DWORD; pbEncryptedBlob: LPBYTE;
  cbEncryptedBlob: DWORD; pbDecrypted: LPBYTE; pcbDecrypted: LPDWORD;
  ppXchgCert: PPCCERT_CONTEXT; ppSignerCert: PPCCERT_CONTEXT): BOOL; stdcall;
{$EXTERNALSYM CryptDecryptAndVerifyMessageSignature}

//+-------------------------------------------------------------------------
//  Decodes a cryptographic message which may be one of the following types:
//    CMSG_DATA
//    CMSG_SIGNED
//    CMSG_ENVELOPED
//    CMSG_SIGNED_AND_ENVELOPED
//    CMSG_HASHED
//
//  dwMsgTypeFlags specifies the set of allowable messages. For example, to
//  decode either SIGNED or ENVELOPED messages, set dwMsgTypeFlags to:
//      CMSG_SIGNED_FLAG | CMSG_ENVELOPED_FLAG.
//
//  dwProvInnerContentType is only applicable when processing nested
//  crytographic messages. When processing an outer crytographic message
//  it must be set to 0. When decoding a nested cryptographic message
//  its the dwInnerContentType returned by a previous CryptDecodeMessage
//  of the outer message. The InnerContentType can be any of the CMSG types,
//  for example, CMSG_DATA, CMSG_SIGNED, ...
//
//  The optional *pdwMsgType is updated with the type of message.
//
//  The optional *pdwInnerContentType is updated with the type of the inner
//  message. Unless there is cryptographic message nesting, CMSG_DATA
//  is returned.
//
//  For CMSG_DATA: returns decoded content.
//  For CMSG_SIGNED: same as CryptVerifyMessageSignature.
//  For CMSG_ENVELOPED: same as CryptDecryptMessage.
//  For CMSG_SIGNED_AND_ENVELOPED: same as CryptDecryptMessage plus
//      CryptVerifyMessageSignature.
//  For CMSG_HASHED: verifies the hash and returns decoded content.
//--------------------------------------------------------------------------

function CryptDecodeMessage(dwMsgTypeFlags: DWORD; pDecryptPara: PCRYPT_DECRYPT_MESSAGE_PARA;
  pVerifyPara: PCRYPT_VERIFY_MESSAGE_PARA; dwSignerIndex: DWORD; pbEncodedBlob: LPBYTE;
  cbEncodedBlob: DWORD; dwPrevInnerContentType: DWORD; pdwMsgType: LPDWORD;
  pdwInnerContentType: LPDWORD; pbDecoded: LPBYTE; pcbDecoded: LPDWORD;
  ppXchgCert: PPCCERT_CONTEXT; ppSignerCert: PPCCERT_CONTEXT): BOOL; stdcall;
{$EXTERNALSYM CryptDecodeMessage}

//+-------------------------------------------------------------------------
//  Hash the message.
//
//  If fDetachedHash is TRUE, only the ComputedHash is encoded in the
//  pbHashedBlob. Otherwise, both the ToBeHashed and ComputedHash
//  are encoded.
//
//  pcbHashedBlob or pcbComputedHash can be NULL, indicating the caller
//  isn't interested in getting the output.
//--------------------------------------------------------------------------

function CryptHashMessage(pHashPara: PCRYPT_HASH_MESSAGE_PARA; fDetachedHash: BOOL;
  cToBeHashed: DWORD; rgpbToBeHashed: LPBYTE; rgcbToBeHashed: LPDWORD;
  pbHashedBlob: LPBYTE; pcbHashedBlob: LPDWORD; pbComputedHash: LPBYTE;
  pcbComputedHash: LPDWORD): BOOL; stdcall;
{$EXTERNALSYM CryptHashMessage}

//+-------------------------------------------------------------------------
//  Verify a hashed message.
//
//  pcbToBeHashed or pcbComputedHash can be NULL,
//  indicating the caller isn't interested in getting the output.
//--------------------------------------------------------------------------

function CryptVerifyMessageHash(pHashPara: PCRYPT_HASH_MESSAGE_PARA;
  pbHashedBlob: LPBYTE; cbHashedBlob: DWORD; pbToBeHashed: LPBYTE;
  pcbToBeHashed: LPDWORD; pbComputedHash: LPBYTE; pcbComputedHash: LPDWORD): BOOL; stdcall;
{$EXTERNALSYM CryptVerifyMessageHash}

//+-------------------------------------------------------------------------
//  Verify a hashed message containing a detached hash.
//  The "to be hashed" content is passed in separately. No
//  decoded output. Otherwise, identical to CryptVerifyMessageHash.
//
//  pcbComputedHash can be NULL, indicating the caller isn't interested
//  in getting the output.
//--------------------------------------------------------------------------

function CryptVerifyDetachedMessageHash(pHashPara: PCRYPT_HASH_MESSAGE_PARA;
  pbDetachedHashBlob: LPBYTE; cbDetachedHashBlob: DWORD; cToBeHashed: DWORD;
  rgpbToBeHashed: LPBYTE; rgcbToBeHashed: LPDWORD; pbComputedHash: LPBYTE;
  pcbComputedHash: LPDWORD): BOOL; stdcall;
{$EXTERNALSYM CryptVerifyDetachedMessageHash}

//+-------------------------------------------------------------------------
//  Sign the message using the provider's private key specified in the
//  parameters. A dummy SignerId is created and stored in the message.
//
//  Normally used until a certificate has been created for the key.
//--------------------------------------------------------------------------

function CryptSignMessageWithKey(pSignPara: PCRYPT_KEY_SIGN_MESSAGE_PARA;
  pbToBeSigned: LPBYTE; cbToBeSigned: DWORD; pbSignedBlob: LPBYTE;
  var pcbSignedBlob: DWORD): BOOL; stdcall;
{$EXTERNALSYM CryptSignMessageWithKey}

//+-------------------------------------------------------------------------
//  Verify a signed message using the specified public key info.
//
//  Normally called by a CA until it has created a certificate for the
//  key.
//
//  pPublicKeyInfo contains the public key to use to verify the signed
//  message. If NULL, the signature isn't verified (for instance, the decoded
//  content may contain the PublicKeyInfo).
//
//  pcbDecoded can be NULL, indicating the caller isn't interested
//  in getting the decoded content.
//--------------------------------------------------------------------------

function CryptVerifyMessageSignatureWithKey(pVerifyPara: PCRYPT_KEY_VERIFY_MESSAGE_PARA;
  pPublicKeyInfo: PCERT_PUBLIC_KEY_INFO; pbSignedBlob: LPBYTE; cbSignedBlob: DWORD;
  pbDecoded: LPBYTE; pcbDecoded: LPDWORD): BOOL; stdcall;
{$EXTERNALSYM CryptVerifyMessageSignatureWithKey}

//+=========================================================================
//  System Certificate Store Data Structures and APIs
//==========================================================================


//+-------------------------------------------------------------------------
//  Get a system certificate store based on a subsystem protocol.
//
//  Current examples of subsystems protocols are:
//      "MY"    Cert Store hold certs with associated Private Keys
//      "CA"    Certifying Authority certs
//      "ROOT"  Root Certs
//      "SPC"   Software publisher certs
//
//
//  If hProv is NULL the default provider "1" is opened for you.
//  When the store is closed the provider is release. Otherwise
//  if hProv is not NULL, no provider is created or released.
//
//  The returned Cert Store can be searched for an appropriate Cert
//  using the Cert Store API's (see certstor.h)
//
//  When done, the cert store should be closed using CertStoreClose
//--------------------------------------------------------------------------

function CertOpenSystemStoreA(hProv: HCRYPTPROV; szSubsystemProtocol: LPCSTR): HCERTSTORE; stdcall;
{$EXTERNALSYM CertOpenSystemStoreA}
function CertOpenSystemStoreW(hProv: HCRYPTPROV; szSubsystemProtocol: LPCWSTR): HCERTSTORE; stdcall;
{$EXTERNALSYM CertOpenSystemStoreW}

{$IFDEF UNICODE}
function CertOpenSystemStore(hProv: HCRYPTPROV; szSubsystemProtocol: LPCWSTR): HCERTSTORE; stdcall;
{$EXTERNALSYM CertOpenSystemStore}
{$ELSE}
function CertOpenSystemStore(hProv: HCRYPTPROV; szSubsystemProtocol: LPCSTR): HCERTSTORE; stdcall;
{$EXTERNALSYM CertOpenSystemStore}
{$ENDIF}

function CertAddEncodedCertificateToSystemStoreA(szCertStoreName: LPCSTR;
  pbCertEncoded: LPBYTE; cbCertEncoded: DWORD): BOOL; stdcall;
{$EXTERNALSYM CertAddEncodedCertificateToSystemStoreA}
function CertAddEncodedCertificateToSystemStoreW(szCertStoreName: LPCWSTR;
  pbCertEncoded: LPBYTE; cbCertEncoded: DWORD): BOOL; stdcall;
{$EXTERNALSYM CertAddEncodedCertificateToSystemStoreW}

{$IFDEF UNICODE}
function CertAddEncodedCertificateToSystemStore(szCertStoreName: LPCWSTR;
  pbCertEncoded: LPBYTE; cbCertEncoded: DWORD): BOOL; stdcall;
{$EXTERNALSYM CertAddEncodedCertificateToSystemStore}
{$ELSE}
function CertAddEncodedCertificateToSystemStore(szCertStoreName: LPCSTR;
  pbCertEncoded: LPBYTE; cbCertEncoded: DWORD): BOOL; stdcall;
{$EXTERNALSYM CertAddEncodedCertificateToSystemStore}
{$ENDIF}

//+-------------------------------------------------------------------------
//  Find all certificate chains tying the given issuer name to any certificate
//  that the current user has a private key for.
//
//  If no certificate chain is found, FALSE is returned with LastError set
//  to CRYPT_E_NOT_FOUND and the counts zeroed.
//
//  IE 3.0 ASSUMPTION:
//   The client certificates are in the "My" system store. The issuer
//   cerificates may be in the "Root", "CA" or "My" system stores.
//--------------------------------------------------------------------------

type
  PCERT_CHAIN = ^CERT_CHAIN;
  {$EXTERNALSYM PCERT_CHAIN}
  _CERT_CHAIN = record
    cCerts: DWORD; // number of certs in chain
    certs: PCERT_BLOB; // pointer to array of cert chain blobs
    // representing the certs
    keyLocatorInfo: CRYPT_KEY_PROV_INFO; // key locator for cert
  end;
  {$EXTERNALSYM _CERT_CHAIN}
  CERT_CHAIN = _CERT_CHAIN;
  {$EXTERNALSYM CERT_CHAIN}
  TCertChain = CERT_CHAIN;
  PCertChain = PCERT_CHAIN;

// WINCRYPT32API    This is not exported by crypt32, it is exported by softpub

function FindCertsByIssuer(pCertChains: PCERT_CHAIN; var pcbCertChains: DWORD;
  pcCertChains: LPDWORD; pbEncodedIssuerName: LPBYTE; cbEncodedIssuerName: DWORD;
  pwszPurpose: LPCWSTR; dwKeySpec: DWORD): HRESULT; stdcall;
{$EXTERNALSYM FindCertsByIssuer}

//-------------------------------------------------------------------------
//
//  CryptQueryObject takes a CERT_BLOB or a file name and returns the
//  information about the content in the blob or in the file.
//
//  Parameters:
//  INPUT   dwObjectType:
//                       Indicate the type of the object.  Should be one of the
//                       following:
//                          CERT_QUERY_OBJECT_FILE
//                          CERT_QUERY_OBJECT_BLOB
//
//  INPUT   pvObject:
//                        If dwObjectType == CERT_QUERY_OBJECT_FILE, it is a
//                        LPWSTR, that is, the pointer to a wchar file name
//                        if dwObjectType == CERT_QUERY_OBJECT_BLOB, it is a
//                        PCERT_BLOB, that is, a pointer to a CERT_BLOB
//
//  INPUT   dwExpectedContentTypeFlags:
//                        Indicate the expected contenet type.
//                        Can be one of the following:
//                              CERT_QUERY_CONTENT_FLAG_ALL  (the content can be any type)
//                              CERT_QUERY_CONTENT_FLAG_CERT
//                              CERT_QUERY_CONTENT_FLAG_CTL
//                              CERT_QUERY_CONTENT_FLAG_CRL
//                              CERT_QUERY_CONTENT_FLAG_SERIALIZED_STORE
//                              CERT_QUERY_CONTENT_FLAG_SERIALIZED_CERT
//                              CERT_QUERY_CONTENT_FLAG_SERIALIZED_CTL
//                              CERT_QUERY_CONTENT_FLAG_SERIALIZED_CRL
//                              CERT_QUERY_CONTENT_FLAG_PKCS7_SIGNED
//                              CERT_QUERY_CONTENT_FLAG_PKCS7_UNSIGNED
//                              CERT_QUERY_CONTENT_FLAG_PKCS7_SIGNED_EMBED
//                              CERT_QUERY_CONTNET_FLAG_PKCS10
//                              CERT_QUERY_CONTNET_FLAG_PFX
//
//  INPUT   dwExpectedFormatTypeFlags:
//                        Indicate the expected format type.
//                        Can be one of the following:
//                              CERT_QUERY_FORMAT_FLAG_ALL (the content can be any format)
//                              CERT_QUERY_FORMAT_FLAG_BINARY
//                              CERT_QUERY_FORMAT_FLAG_BASE64_ENCODED
//
//
//  INPUT   dwFlags
//                        Reserved flag.  Should always set to 0
//
//  OUTPUT  pdwMsgAndCertEncodingType
//                        Optional output.  If NULL != pdwMsgAndCertEncodingType,
//                        it contains the encoding type of the content as any
//                        combination of the following:
//                              X509_ASN_ENCODING
//                              PKCS_7_ASN_ENCODING
//
//  OUTPUT  pdwContentType
//                        Optional output.  If NULL!=pdwContentType, it contains
//                        the content type as one of the the following:
//                              CERT_QUERY_CONTENT_CERT
//                              CERT_QUERY_CONTENT_CTL
//                              CERT_QUERY_CONTENT_CRL
//                              CERT_QUERY_CONTENT_SERIALIZED_STORE
//                              CERT_QUERY_CONTENT_SERIALIZED_CERT
//                              CERT_QUERY_CONTENT_SERIALIZED_CTL
//                              CERT_QUERY_CONTENT_SERIALIZED_CRL
//                              CERT_QUERY_CONTENT_PKCS7_SIGNED
//                              CERT_QUERY_CONTENT_PKCS7_UNSIGNED
//                              CERT_QUERY_CONTENT_PKCS7_SIGNED_EMBED
//                              CERT_QUERY_CONTENT_PKCS10
//                              CERT_QUERY_CONTENT_PFX
//
//  OUTPUT  pdwFormatType
//                        Optional output.  If NULL !=pdwFormatType, it
//                        contains the format type of the content as one of the
//                        following:
//                              CERT_QUERY_FORMAT_BINARY
//                              CERT_QUERY_FORMAT_BASE64_ENCODED
//
//
//  OUTPUT  phCertStore
//                        Optional output.  If NULL !=phStore,
//                        it contains a cert store that includes all of certificates,
//                        CRL, and CTL in the object if the object content type is
//                        one of the following:
//                              CERT_QUERY_CONTENT_CERT
//                              CERT_QUERY_CONTENT_CTL
//                              CERT_QUERY_CONTENT_CRL
//                              CERT_QUERY_CONTENT_SERIALIZED_STORE
//                              CERT_QUERY_CONTENT_SERIALIZED_CERT
//                              CERT_QUERY_CONTENT_SERIALIZED_CTL
//                              CERT_QUERY_CONTENT_SERIALIZED_CRL
//                              CERT_QUERY_CONTENT_PKCS7_SIGNED
//                              CERT_QUERY_CONTENT_PKCS7_SIGNED_EMBED
//
//                       Caller should free *phCertStore via CertCloseStore.
//
//
//  OUTPUT  phMsg        Optional output.  If NULL != phMsg,
//                        it contains a handle to a opened message if
//                        the content type is one of the following:
//                              CERT_QUERY_CONTENT_PKCS7_SIGNED
//                              CERT_QUERY_CONTENT_PKCS7_UNSIGNED
//                              CERT_QUERY_CONTENT_PKCS7_SIGNED_EMBED
//
//                       Caller should free *phMsg via CryptMsgClose.
//
//  OUTPUT pContext     Optional output.  If NULL != pContext,
//                      it contains either a PCCERT_CONTEXT or PCCRL_CONTEXT,
//                      or PCCTL_CONTEXT based on the content type.
//
//                      If the content type is CERT_QUERY_CONTENT_CERT or
//                      CERT_QUERY_CONTENT_SERIALIZED_CERT, it is a PCCERT_CONTEXT;
//                      Caller should free the pContext via CertFreeCertificateContext.
//
//                      If the content type is CERT_QUERY_CONTENT_CRL or
//                      CERT_QUERY_CONTENT_SERIALIZED_CRL, it is a PCCRL_CONTEXT;
//                      Caller should free the pContext via CertFreeCRLContext.
//
//                      If the content type is CERT_QUERY_CONTENT_CTL or
//                      CERT_QUERY_CONTENT_SERIALIZED_CTL, it is a PCCTL_CONTEXT;
//                      Caller should free the pContext via CertFreeCTLContext.
//
//  If the *pbObject is of type CERT_QUERY_CONTENT_PKCS10 or CERT_QUERY_CONTENT_PFX, CryptQueryObject
//  will not return anything in *phCertstore, *phMsg, or *ppvContext.
//--------------------------------------------------------------------------

function CryptQueryObject(dwObjectType: DWORD; pvObject: Pointer;
  dwExpectedContentTypeFlags, dwExpectedFormatTypeFlags, dwFlags: DWORD;
  pdwMsgAndCertEncodingType, pdwContentType, pdwFormatType: LPDWORD;
  phCertStore: PHCERTSTORE; phMsg: PHCRYPTMSG; ppvContext: PPointer): BOOL; stdcall;
{$EXTERNALSYM CryptQueryObject}

//-------------------------------------------------------------------------
//dwObjectType for CryptQueryObject
//-------------------------------------------------------------------------

const
  CERT_QUERY_OBJECT_FILE = $00000001;
  {$EXTERNALSYM CERT_QUERY_OBJECT_FILE}
  CERT_QUERY_OBJECT_BLOB = $00000002;
  {$EXTERNALSYM CERT_QUERY_OBJECT_BLOB}

//-------------------------------------------------------------------------
//dwConentType for CryptQueryObject
//-------------------------------------------------------------------------

//encoded single certificate

  CERT_QUERY_CONTENT_CERT = 1;
  {$EXTERNALSYM CERT_QUERY_CONTENT_CERT}

//encoded single CTL

  CERT_QUERY_CONTENT_CTL = 2;
  {$EXTERNALSYM CERT_QUERY_CONTENT_CTL}

//encoded single CRL

  CERT_QUERY_CONTENT_CRL = 3;
  {$EXTERNALSYM CERT_QUERY_CONTENT_CRL}

//serialized store

  CERT_QUERY_CONTENT_SERIALIZED_STORE = 4;
  {$EXTERNALSYM CERT_QUERY_CONTENT_SERIALIZED_STORE}

//serialized single certificate

  CERT_QUERY_CONTENT_SERIALIZED_CERT = 5;
  {$EXTERNALSYM CERT_QUERY_CONTENT_SERIALIZED_CERT}

//serialized single CTL

  CERT_QUERY_CONTENT_SERIALIZED_CTL = 6;
  {$EXTERNALSYM CERT_QUERY_CONTENT_SERIALIZED_CTL}

//serialized single CRL

  CERT_QUERY_CONTENT_SERIALIZED_CRL = 7;
  {$EXTERNALSYM CERT_QUERY_CONTENT_SERIALIZED_CRL}

//a PKCS#7 signed message

  CERT_QUERY_CONTENT_PKCS7_SIGNED = 8;
  {$EXTERNALSYM CERT_QUERY_CONTENT_PKCS7_SIGNED}

//a PKCS#7 message, such as enveloped message.  But it is not a signed message,

  CERT_QUERY_CONTENT_PKCS7_UNSIGNED = 9;
  {$EXTERNALSYM CERT_QUERY_CONTENT_PKCS7_UNSIGNED}

//a PKCS7 signed message embedded in a file

  CERT_QUERY_CONTENT_PKCS7_SIGNED_EMBED = 10;
  {$EXTERNALSYM CERT_QUERY_CONTENT_PKCS7_SIGNED_EMBED}

//an encoded PKCS#10

  CERT_QUERY_CONTENT_PKCS10 = 11;
  {$EXTERNALSYM CERT_QUERY_CONTENT_PKCS10}

//an encoded PKX BLOB

  CERT_QUERY_CONTENT_PFX = 12;
  {$EXTERNALSYM CERT_QUERY_CONTENT_PFX}

//-------------------------------------------------------------------------
//dwExpectedConentTypeFlags for CryptQueryObject
//-------------------------------------------------------------------------

//encoded single certificate

  CERT_QUERY_CONTENT_FLAG_CERT = (1 shl CERT_QUERY_CONTENT_CERT);
  {$EXTERNALSYM CERT_QUERY_CONTENT_FLAG_CERT}

//encoded single CTL

  CERT_QUERY_CONTENT_FLAG_CTL = (1 shl CERT_QUERY_CONTENT_CTL);
  {$EXTERNALSYM CERT_QUERY_CONTENT_FLAG_CTL}

//encoded single CRL

  CERT_QUERY_CONTENT_FLAG_CRL = (1 shl CERT_QUERY_CONTENT_CRL);
  {$EXTERNALSYM CERT_QUERY_CONTENT_FLAG_CRL}

//serialized store

  CERT_QUERY_CONTENT_FLAG_SERIALIZED_STORE = (1 shl CERT_QUERY_CONTENT_SERIALIZED_STORE);
  {$EXTERNALSYM CERT_QUERY_CONTENT_FLAG_SERIALIZED_STORE}

//serialized single certificate

  CERT_QUERY_CONTENT_FLAG_SERIALIZED_CERT = (1 shl CERT_QUERY_CONTENT_SERIALIZED_CERT);
  {$EXTERNALSYM CERT_QUERY_CONTENT_FLAG_SERIALIZED_CERT}

//serialized single CTL

  CERT_QUERY_CONTENT_FLAG_SERIALIZED_CTL = (1 shl CERT_QUERY_CONTENT_SERIALIZED_CTL);
  {$EXTERNALSYM CERT_QUERY_CONTENT_FLAG_SERIALIZED_CTL}

//serialized single CRL

  CERT_QUERY_CONTENT_FLAG_SERIALIZED_CRL = (1 shl CERT_QUERY_CONTENT_SERIALIZED_CRL);
  {$EXTERNALSYM CERT_QUERY_CONTENT_FLAG_SERIALIZED_CRL}

//an encoded PKCS#7 signed message

  CERT_QUERY_CONTENT_FLAG_PKCS7_SIGNED = (1 shl CERT_QUERY_CONTENT_PKCS7_SIGNED);
  {$EXTERNALSYM CERT_QUERY_CONTENT_FLAG_PKCS7_SIGNED}

//an encoded PKCS#7 message.  But it is not a signed message

  CERT_QUERY_CONTENT_FLAG_PKCS7_UNSIGNED = (1 shl CERT_QUERY_CONTENT_PKCS7_UNSIGNED);
  {$EXTERNALSYM CERT_QUERY_CONTENT_FLAG_PKCS7_UNSIGNED}

//the content includes an embedded PKCS7 signed message

  CERT_QUERY_CONTENT_FLAG_PKCS7_SIGNED_EMBED = (1 shl CERT_QUERY_CONTENT_PKCS7_SIGNED_EMBED);
  {$EXTERNALSYM CERT_QUERY_CONTENT_FLAG_PKCS7_SIGNED_EMBED}

//an encoded PKCS#10

  CERT_QUERY_CONTENT_FLAG_PKCS10 = (1 shl CERT_QUERY_CONTENT_PKCS10);
  {$EXTERNALSYM CERT_QUERY_CONTENT_FLAG_PKCS10}

//an encoded PFX BLOB

  CERT_QUERY_CONTENT_FLAG_PFX = (1 shl CERT_QUERY_CONTENT_PFX);
  {$EXTERNALSYM CERT_QUERY_CONTENT_FLAG_PFX}

//content can be any type
  CERT_QUERY_CONTENT_FLAG_ALL = CERT_QUERY_CONTENT_FLAG_CERT or
                                CERT_QUERY_CONTENT_FLAG_CTL or
                                CERT_QUERY_CONTENT_FLAG_CRL or
                                CERT_QUERY_CONTENT_FLAG_SERIALIZED_STORE or
                                CERT_QUERY_CONTENT_FLAG_SERIALIZED_CERT or
                                CERT_QUERY_CONTENT_FLAG_SERIALIZED_CTL or
                                CERT_QUERY_CONTENT_FLAG_SERIALIZED_CRL or
                                CERT_QUERY_CONTENT_FLAG_PKCS7_SIGNED or
                                CERT_QUERY_CONTENT_FLAG_PKCS7_UNSIGNED or
                                CERT_QUERY_CONTENT_FLAG_PKCS7_SIGNED_EMBED or
                                CERT_QUERY_CONTENT_FLAG_PKCS10 or
                                CERT_QUERY_CONTENT_FLAG_PFX;
  {$EXTERNALSYM CERT_QUERY_CONTENT_FLAG_ALL}

//-------------------------------------------------------------------------
//dwFormatType for CryptQueryObject
//-------------------------------------------------------------------------
//the content is in binary format

  CERT_QUERY_FORMAT_BINARY = 1;
  {$EXTERNALSYM CERT_QUERY_FORMAT_BINARY}

//the content is base64 encoded

  CERT_QUERY_FORMAT_BASE64_ENCODED = 2;
  {$EXTERNALSYM CERT_QUERY_FORMAT_BASE64_ENCODED}

//-------------------------------------------------------------------------
//dwExpectedFormatTypeFlags for CryptQueryObject
//-------------------------------------------------------------------------

//the content is in binary format

  CERT_QUERY_FORMAT_FLAG_BINARY = (1 shl CERT_QUERY_FORMAT_BINARY);
  {$EXTERNALSYM CERT_QUERY_FORMAT_FLAG_BINARY}

//the content is base64 encoded

  CERT_QUERY_FORMAT_FLAG_BASE64_ENCODED = (1 shl CERT_QUERY_FORMAT_BASE64_ENCODED);
  {$EXTERNALSYM CERT_QUERY_FORMAT_FLAG_BASE64_ENCODED}

//the content can be of any format

  CERT_QUERY_FORMAT_FLAG_ALL = CERT_QUERY_FORMAT_FLAG_BINARY or CERT_QUERY_FORMAT_FLAG_BASE64_ENCODED;
  {$EXTERNALSYM CERT_QUERY_FORMAT_FLAG_ALL}

//
// Crypt32 Memory Management Routines.  All Crypt32 API which return allocated
// buffers will do so via CryptMemAlloc, CryptMemRealloc.  Clients can free
// those buffers using CryptMemFree.  Also included is CryptMemSize
//

function CryptMemAlloc(cbSize: ULONG): LPVOID; stdcall;
{$EXTERNALSYM CryptMemAlloc}

function CryptMemRealloc(pv: LPVOID; cbSize: ULONG): LPVOID; stdcall;
{$EXTERNALSYM CryptMemRealloc}

procedure CryptMemFree(pv: LPVOID); stdcall;
{$EXTERNALSYM CryptMemFree}

//
// Crypt32 Asynchronous Parameter Management Routines.  All Crypt32 API which
// expose asynchronous mode operation use a Crypt32 Async Handle to pass
// around information about the operation e.g. callback routines.  The
// following API are used for manipulation of the async handle
//

type
  HCRYPTASYNC = HANDLE;
  {$EXTERNALSYM HCRYPTASYNC}
  PHCRYPTASYNC = ^HCRYPTASYNC;
  {$EXTERNALSYM PHCRYPTASYNC}

  PFN_CRYPT_ASYNC_PARAM_FREE_FUNC = procedure (pszParamOid: LPSTR; pvParam: LPVOID); stdcall;
  {$EXTERNALSYM PFN_CRYPT_ASYNC_PARAM_FREE_FUNC}
  PFnCryptAsyncParamFreeFunc = PFN_CRYPT_ASYNC_PARAM_FREE_FUNC;

function CryptCreateAsyncHandle(dwFlags: DWORD; phAsync: PHCRYPTASYNC): BOOL; stdcall;
{$EXTERNALSYM CryptCreateAsyncHandle}

function CryptSetAsyncParam(hAsync: HCRYPTASYNC; pszParamOid: LPSTR;
  pvParam: LPVOID; pfnFree: PFN_CRYPT_ASYNC_PARAM_FREE_FUNC): BOOL; stdcall;
{$EXTERNALSYM CryptSetAsyncParam}

function CryptGetAsyncParam(hAsync: HCRYPTASYNC; pszParamOid: LPSTR;
  var ppvParam: LPVOID; var ppfnFree: PFN_CRYPT_ASYNC_PARAM_FREE_FUNC): BOOL; stdcall;
{$EXTERNALSYM CryptGetAsyncParam}

function CryptCloseAsyncHandle(hAsync: HCRYPTASYNC): BOOL; stdcall;
{$EXTERNALSYM CryptCloseAsyncHandle}

//
// Crypt32 Remote Object Retrieval Routines.  This API allows retrieval of
// remote PKI objects where the location is given by an URL.  The remote
// object retrieval manager exposes two provider models.  One is the "Scheme
// Provider" model which allows for installable protocol providers as defined
// by the URL scheme e.g. ldap, http, ftp.  The scheme provider entry point is
// the same as the CryptRetrieveObjectByUrl however the *ppvObject returned
// is ALWAYS a counted array of encoded bits (one per object retrieved).  The
// second provider model is the "Context Provider" model which allows for
// installable creators of CAPI2 context handles (objects) based on the
// retrieved encoded bits.  These are dispatched based on the object OID given
// in the call to CryptRetrieveObjectByUrl.
//

type
  PCRYPT_BLOB_ARRAY = ^CRYPT_BLOB_ARRAY;
  {$EXTERNALSYM PCRYPT_BLOB_ARRAY}
  _CRYPT_BLOB_ARRAY = record
    cBlob: DWORD;
    rgBlob: PCRYPT_DATA_BLOB;
  end;
  {$EXTERNALSYM _CRYPT_BLOB_ARRAY}
  CRYPT_BLOB_ARRAY = _CRYPT_BLOB_ARRAY;
  {$EXTERNALSYM CRYPT_BLOB_ARRAY}
  TCryptBlobArray = CRYPT_BLOB_ARRAY;
  PCryptBlobArray = PCRYPT_BLOB_ARRAY;  

  PCRYPT_CREDENTIALS = ^CRYPT_CREDENTIALS;
  {$EXTERNALSYM PCRYPT_CREDENTIALS}
  _CRYPT_CREDENTIALS = record
    cbSize: DWORD;
    pszCredentialsOid: LPCSTR;
    pvCredentials: LPVOID;
  end;
  {$EXTERNALSYM _CRYPT_CREDENTIALS}
  CRYPT_CREDENTIALS = _CRYPT_CREDENTIALS;
  {$EXTERNALSYM CRYPT_CREDENTIALS}
  TCryptCredentials = CRYPT_CREDENTIALS;
  PCryptCredentials = PCRYPT_CREDENTIALS;

const
  CREDENTIAL_OID_PASSWORD_CREDENTIALS_A = LPCSTR(1);
  {$EXTERNALSYM CREDENTIAL_OID_PASSWORD_CREDENTIALS_A}
  CREDENTIAL_OID_PASSWORD_CREDENTIALS_W = LPCSTR(2);
  {$EXTERNALSYM CREDENTIAL_OID_PASSWORD_CREDENTIALS_W}

{$IFDEF UNICODE}
  CREDENTIAL_OID_PASSWORD_CREDENTIALS = CREDENTIAL_OID_PASSWORD_CREDENTIALS_W;
  {$EXTERNALSYM CREDENTIAL_OID_PASSWORD_CREDENTIALS}
{$ELSE}
  CREDENTIAL_OID_PASSWORD_CREDENTIALS = CREDENTIAL_OID_PASSWORD_CREDENTIALS_A;
  {$EXTERNALSYM CREDENTIAL_OID_PASSWORD_CREDENTIALS}
{$ENDIF}

type
  PCRYPT_PASSWORD_CREDENTIALSA = ^CRYPT_PASSWORD_CREDENTIALSA;
  {$EXTERNALSYM PCRYPT_PASSWORD_CREDENTIALSA}
  _CRYPT_PASSWORD_CREDENTIALSA = record
    cbSize: DWORD;
    pszUsername: LPSTR;
    pszPassword: LPSTR;
  end;
  {$EXTERNALSYM _CRYPT_PASSWORD_CREDENTIALSA}
  CRYPT_PASSWORD_CREDENTIALSA = _CRYPT_PASSWORD_CREDENTIALSA;
  {$EXTERNALSYM CRYPT_PASSWORD_CREDENTIALSA}
  TCryptPasswordCredentialsA = CRYPT_PASSWORD_CREDENTIALSA;
  PCryptPasswordCredentialsA = PCRYPT_PASSWORD_CREDENTIALSA;

  PCRYPT_PASSWORD_CREDENTIALSW = ^CRYPT_PASSWORD_CREDENTIALSW;
  {$EXTERNALSYM PCRYPT_PASSWORD_CREDENTIALSW}
  _CRYPT_PASSWORD_CREDENTIALSW = record
    cbSize: DWORD;
    pszUsername: LPWSTR;
    pszPassword: LPWSTR;
  end;
  {$EXTERNALSYM _CRYPT_PASSWORD_CREDENTIALSW}
  CRYPT_PASSWORD_CREDENTIALSW = _CRYPT_PASSWORD_CREDENTIALSW;
  {$EXTERNALSYM CRYPT_PASSWORD_CREDENTIALSW}
  TCryptPasswordCredentialsW = CRYPT_PASSWORD_CREDENTIALSW;
  PCryptPasswordCredentialsW = PCRYPT_PASSWORD_CREDENTIALSW;

{$IFDEF UNICODE}
  CRYPT_PASSWORD_CREDENTIALS = CRYPT_PASSWORD_CREDENTIALSW;
  {$EXTERNALSYM CRYPT_PASSWORD_CREDENTIALS}
  PCRYPT_PASSWORD_CREDENTIALS = PCRYPT_PASSWORD_CREDENTIALSW;
  {$EXTERNALSYM PCRYPT_PASSWORD_CREDENTIALS}
  TCryptPasswordCredentials = TCryptPasswordCredentialsW;
  PCryptPasswordCredentials = PCryptPasswordCredentialsW;
{$ELSE}
  CRYPT_PASSWORD_CREDENTIALS = CRYPT_PASSWORD_CREDENTIALSA;
  {$EXTERNALSYM CRYPT_PASSWORD_CREDENTIALS}
  PCRYPT_PASSWORD_CREDENTIALS = PCRYPT_PASSWORD_CREDENTIALSA;
  {$EXTERNALSYM PCRYPT_PASSWORD_CREDENTIALS}
  TCryptPasswordCredentials = TCryptPasswordCredentialsA;
  PCryptPasswordCredentials = PCryptPasswordCredentialsA;
{$ENDIF}

//
// Scheme Provider Signatures
//

const
  SCHEME_OID_RETRIEVE_ENCODED_OBJECT_FUNC = 'SchemeDllRetrieveEncodedObject';
  {$EXTERNALSYM SCHEME_OID_RETRIEVE_ENCODED_OBJECT_FUNC}

type
  PFN_FREE_ENCODED_OBJECT_FUNC = procedure (pszObjectOid: LPCSTR;
    pObject: PCRYPT_BLOB_ARRAY; pvFreeContext: LPVOID); stdcall;
  {$EXTERNALSYM PFN_FREE_ENCODED_OBJECT_FUNC}
  PFnFreeEncodedObjectFunc = PFN_FREE_ENCODED_OBJECT_FUNC;

//
// SchemeDllRetrieveEncodedObject has the following signature:
//
// BOOL WINAPI SchemeDllRetrieveEncodedObject (
//                   IN LPCSTR pszUrl,
//                   IN LPCSTR pszObjectOid,
//                   IN DWORD dwRetrievalFlags,
//                   IN DWORD dwTimeout,
//                   OUT PCRYPT_BLOB_ARRAY pObject,
//                   OUT PFN_FREE_ENCODED_OBJECT_FUNC* ppfnFreeObject,
//                   OUT LPVOID* ppvFreeContext,
//                   IN HCRYPTASYNC hAsyncRetrieve,
//                   IN PCRYPT_CREDENTIALS pCredentials,
//                   IN LPVOID pvReserved
//                   )
//

//
// Context Provider Signatures
//

const
  CONTEXT_OID_CREATE_OBJECT_CONTEXT_FUNC = 'ContextDllCreateObjectContext';
  {$EXTERNALSYM CONTEXT_OID_CREATE_OBJECT_CONTEXT_FUNC}

  CONTEXT_OID_CERTIFICATE = LPCSTR(1);
  {$EXTERNALSYM CONTEXT_OID_CERTIFICATE}
  CONTEXT_OID_CRL         = LPCSTR(2);
  {$EXTERNALSYM CONTEXT_OID_CRL}
  CONTEXT_OID_CTL         = LPCSTR(3);
  {$EXTERNALSYM CONTEXT_OID_CTL}
  CONTEXT_OID_PKCS7       = LPCSTR(4);
  {$EXTERNALSYM CONTEXT_OID_PKCS7}
  CONTEXT_OID_CAPI2_ANY   = LPCSTR(5);
  {$EXTERNALSYM CONTEXT_OID_CAPI2_ANY}

//
// ContextDllCreateObjectContext has the following signature:
//
// BOOL WINAPI ContextDllCreateObjectContext (
//                    IN LPCSTR pszObjectOid,
//                    IN DWORD dwRetrievalFlags,
//                    IN PCRYPT_BLOB_ARRAY pObject,
//                    OUT LPVOID* ppvContext
//                    )
//

//
// Remote Object Retrieval API
//

//
// Retrieval flags
//

  CRYPT_RETRIEVE_MULTIPLE_OBJECTS = $00000001;
  {$EXTERNALSYM CRYPT_RETRIEVE_MULTIPLE_OBJECTS}
  CRYPT_CACHE_ONLY_RETRIEVAL      = $00000002;
  {$EXTERNALSYM CRYPT_CACHE_ONLY_RETRIEVAL}
  CRYPT_WIRE_ONLY_RETRIEVAL       = $00000004;
  {$EXTERNALSYM CRYPT_WIRE_ONLY_RETRIEVAL}
  CRYPT_DONT_CACHE_RESULT         = $00000008;
  {$EXTERNALSYM CRYPT_DONT_CACHE_RESULT}
  CRYPT_ASYNC_RETRIEVAL           = $00000010;
  {$EXTERNALSYM CRYPT_ASYNC_RETRIEVAL}

//
// Data verification retrieval flags
//
// CRYPT_VERIFY_CONTEXT_SIGNATURE is used to get signature verification
// on the context created.  In this case pszObjectOid must be non-NULL and
// pvVerify points to the signer certificate context
//
// CRYPT_VERIFY_DATA_HASH is used to get verification of the blob data
// retrieved by the protocol.  The pvVerify points to an URL_DATA_HASH
// structure (TBD)
//

  CRYPT_VERIFY_CONTEXT_SIGNATURE = $00000020;
  {$EXTERNALSYM CRYPT_VERIFY_CONTEXT_SIGNATURE}
  CRYPT_VERIFY_DATA_HASH         = $00000040;
  {$EXTERNALSYM CRYPT_VERIFY_DATA_HASH}

//
// Time Valid Object flags
//

  CRYPT_KEEP_TIME_VALID          = $00000080;
  {$EXTERNALSYM CRYPT_KEEP_TIME_VALID}
  CRYPT_DONT_VERIFY_SIGNATURE    = $00000100;
  {$EXTERNALSYM CRYPT_DONT_VERIFY_SIGNATURE}
  CRYPT_DONT_CHECK_TIME_VALIDITY = $00000200;
  {$EXTERNALSYM CRYPT_DONT_CHECK_TIME_VALIDITY}

function CryptRetrieveObjectByUrlA(pszUrl: LPCSTR; pszObjectOid: LPCSTR;
  dwRetrievalFlags: DWORD; dwTimeout: DWORD; var ppvObject: LPVOID;
  hAsyncRetrieve: HCRYPTASYNC; pCredentials: PCRYPT_CREDENTIALS;
  pvVerify: LPVOID; pvReserved: LPVOID): BOOL; stdcall;
{$EXTERNALSYM CryptRetrieveObjectByUrlA}
function CryptRetrieveObjectByUrlW(pszUrl: LPCWSTR; pszObjectOid: LPCSTR;
  dwRetrievalFlags: DWORD; dwTimeout: DWORD; var ppvObject: LPVOID;
  hAsyncRetrieve: HCRYPTASYNC; pCredentials: PCRYPT_CREDENTIALS;
  pvVerify: LPVOID; pvReserved: LPVOID): BOOL; stdcall;
{$EXTERNALSYM CryptRetrieveObjectByUrlW}

{$IFDEF UNICODE}
function CryptRetrieveObjectByUrl(pszUrl: LPCWSTR; pszObjectOid: LPCSTR;
  dwRetrievalFlags: DWORD; dwTimeout: DWORD; var ppvObject: LPVOID;
  hAsyncRetrieve: HCRYPTASYNC; pCredentials: PCRYPT_CREDENTIALS;
  pvVerify: LPVOID; pvReserved: LPVOID): BOOL; stdcall;
{$EXTERNALSYM CryptRetrieveObjectByUrl}
{$ELSE}
function CryptRetrieveObjectByUrl(pszUrl: LPCSTR; pszObjectOid: LPCSTR;
  dwRetrievalFlags: DWORD; dwTimeout: DWORD; var ppvObject: LPVOID;
  hAsyncRetrieve: HCRYPTASYNC; pCredentials: PCRYPT_CREDENTIALS;
  pvVerify: LPVOID; pvReserved: LPVOID): BOOL; stdcall;
{$EXTERNALSYM CryptRetrieveObjectByUrl}
{$ENDIF}

//
// Call back function to cancel object retrieval
//
// The function can be installed on a per thread basis.  
// If CryptInstallCancelRetrieval is called for multiple times, only the most recent
// installation will be kept.
//
// This is only effective for http, https, gopher, and ftp protocol.  
// It is ignored by the rest of the protocols.

type
  PFN_CRYPT_CANCEL_RETRIEVAL = function (dwFlags: DWORD; pvArg: Pointer): BOOL; stdcall;
  {$EXTERNALSYM PFN_CRYPT_CANCEL_RETRIEVAL}
  PFnCryptCancelRetrieval = PFN_CRYPT_CANCEL_RETRIEVAL;

//
// PFN_CRYPT_CANCEL_RETRIEVAL
//
// This function should return FALSE when the object retrieval should be continued
// and return TRUE when the object retrieval should be cancelled.
//

function CryptInstallCancelRetrieval(pfnCancel: PFN_CRYPT_CANCEL_RETRIEVAL;
  pvArg: Pointer; dwFlags: DWORD; pvReserved: Pointer): BOOL; stdcall;
{$EXTERNALSYM CryptInstallCancelRetrieval}

function CryptUninstallCancelRetrieval(dwFlags: DWORD; pvReserved: Pointer): BOOL; stdcall;
{$EXTERNALSYM CryptUninstallCancelRetrieval}

function CryptCancelAsyncRetrieval(hAsyncRetrieval: HCRYPTASYNC): BOOL; stdcall;
{$EXTERNALSYM CryptCancelAsyncRetrieval}

//
// Remote Object Async Retrieval parameters
//

//
// A client that wants to be notified of asynchronous object retrieval
// completion sets this parameter on the async handle
//

const
  CRYPT_PARAM_ASYNC_RETRIEVAL_COMPLETION = LPCSTR(1);
  {$EXTERNALSYM CRYPT_PARAM_ASYNC_RETRIEVAL_COMPLETION}

type
  PFN_CRYPT_ASYNC_RETRIEVAL_COMPLETION_FUNC = procedure (pvCompletion: LPVOID;
    dwCompletionCode: DWORD; pszUrl: LPCSTR; pszObjectOid: LPSTR; pvObject: LPVOID); stdcall;
  {$EXTERNALSYM PFN_CRYPT_ASYNC_RETRIEVAL_COMPLETION_FUNC}
  PFnCryptASynchRetrievalCompletionFunc = PFN_CRYPT_ASYNC_RETRIEVAL_COMPLETION_FUNC;

  PCRYPT_ASYNC_RETRIEVAL_COMPLETION = ^CRYPT_ASYNC_RETRIEVAL_COMPLETION;
  {$EXTERNALSYM PCRYPT_ASYNC_RETRIEVAL_COMPLETION}
  _CRYPT_ASYNC_RETRIEVAL_COMPLETION = record
    pfnCompletion: PFN_CRYPT_ASYNC_RETRIEVAL_COMPLETION_FUNC;
    pvCompletion: LPVOID;
  end;
  {$EXTERNALSYM _CRYPT_ASYNC_RETRIEVAL_COMPLETION}
  CRYPT_ASYNC_RETRIEVAL_COMPLETION = _CRYPT_ASYNC_RETRIEVAL_COMPLETION;
  {$EXTERNALSYM CRYPT_ASYNC_RETRIEVAL_COMPLETION}
  TCryptAsyncRetrievalCompletion = CRYPT_ASYNC_RETRIEVAL_COMPLETION;
  PCryptAsyncRetrievalCompletion = PCRYPT_ASYNC_RETRIEVAL_COMPLETION;

//
// This function is set on the async handle by a scheme provider that
// supports asynchronous retrieval
//

const
  CRYPT_PARAM_CANCEL_ASYNC_RETRIEVAL = LPCSTR(2);
  {$EXTERNALSYM CRYPT_PARAM_CANCEL_ASYNC_RETRIEVAL}

type
  PFN_CANCEL_ASYNC_RETRIEVAL_FUNC = function (hAsyncRetrieve: HCRYPTASYNC): BOOL; stdcall;
  {$EXTERNALSYM PFN_CANCEL_ASYNC_RETRIEVAL_FUNC}
  PFnCancelASynchRetrievalFunc = PFN_CANCEL_ASYNC_RETRIEVAL_FUNC;

//
// Get the locator for a CAPI object
//

const
  CRYPT_GET_URL_FROM_PROPERTY         = $00000001;
  {$EXTERNALSYM CRYPT_GET_URL_FROM_PROPERTY}
  CRYPT_GET_URL_FROM_EXTENSION        = $00000002;
  {$EXTERNALSYM CRYPT_GET_URL_FROM_EXTENSION}
  CRYPT_GET_URL_FROM_UNAUTH_ATTRIBUTE = $00000004;
  {$EXTERNALSYM CRYPT_GET_URL_FROM_UNAUTH_ATTRIBUTE}
  CRYPT_GET_URL_FROM_AUTH_ATTRIBUTE   = $00000008;
  {$EXTERNALSYM CRYPT_GET_URL_FROM_AUTH_ATTRIBUTE}

type
  PCRYPT_URL_ARRAY = ^CRYPT_URL_ARRAY;
  {$EXTERNALSYM PCRYPT_URL_ARRAY}
  _CRYPT_URL_ARRAY = record
    cUrl: DWORD;
    rgwszUrl: LPWSTR;
  end;
  {$EXTERNALSYM _CRYPT_URL_ARRAY}
  CRYPT_URL_ARRAY = _CRYPT_URL_ARRAY;
  {$EXTERNALSYM CRYPT_URL_ARRAY}
  TCryptUrlArray = CRYPT_URL_ARRAY;
  PCryptUrlArray = PCRYPT_URL_ARRAY;

  PCRYPT_URL_INFO = ^CRYPT_URL_INFO;
  {$EXTERNALSYM PCRYPT_URL_INFO}
  _CRYPT_URL_INFO = record
    cbSize: DWORD;
  end;
  {$EXTERNALSYM _CRYPT_URL_INFO}
  CRYPT_URL_INFO = _CRYPT_URL_INFO;
  {$EXTERNALSYM CRYPT_URL_INFO}
  TCryptUrlInfo = CRYPT_URL_INFO;
  PCryptUrlInfo = PCRYPT_URL_INFO;

function CryptGetObjectUrl(pszUrlOid: LPCSTR; pvPara: LPVOID; dwFlags: DWORD;
  pUrlArray: PCRYPT_URL_ARRAY; var pcbUrlArray: DWORD; pUrlInfo: PCRYPT_URL_INFO;
  pcbUrlInfo: LPDWORD; pvReserved: LPVOID): BOOL; stdcall;
{$EXTERNALSYM CryptGetObjectUrl}

const
  URL_OID_GET_OBJECT_URL_FUNC = 'UrlDllGetObjectUrl';
  {$EXTERNALSYM URL_OID_GET_OBJECT_URL_FUNC}

//
// UrlDllGetObjectUrl has the same signature as CryptGetObjectUrl
//

//
// URL_OID_CERTIFICATE_ISSUER
//
// pvPara == PCCERT_CONTEXT, certificate whose issuer's URL is being requested
//
// This will be retrieved from the authority info access extension or property
// on the certificate
//
// URL_OID_CERTIFICATE_CRL_DIST_POINT
//
// pvPara == PCCERT_CONTEXT, certificate whose CRL distribution point is being
// requested
//
// This will be retrieved from the CRL distribution point extension or property
// on the certificate
//
// URL_OID_CTL_ISSUER
//
// pvPara == PCCTL_CONTEXT, Signer Index, CTL whose issuer's URL (identified
// by the signer index) is being requested
//
// This will be retrieved from an authority info access attribute method encoded
// in each signer info in the PKCS7 (CTL)
//
// URL_OID_CTL_NEXT_UPDATE
//
// pvPara == PCCTL_CONTEXT, Signer Index, CTL whose next update URL is being
// requested and an optional signer index in case we need to check signer
// info attributes
//
// This will be retrieved from an authority info access CTL extension, property,
// or signer info attribute method
//
// URL_OID_CRL_ISSUER
//
// pvPara == PCCRL_CONTEXT, CRL whose issuer's URL is being requested
//
// This will be retrieved from a property on the CRL which has been inherited
// from the subject cert (either from the subject cert issuer or the subject
// cert distribution point extension).  It will be encoded as an authority
// info access extension method.
//

const
  URL_OID_CERTIFICATE_ISSUER         = LPCSTR(1);
  {$EXTERNALSYM URL_OID_CERTIFICATE_ISSUER}
  URL_OID_CERTIFICATE_CRL_DIST_POINT = LPCSTR(2);
  {$EXTERNALSYM URL_OID_CERTIFICATE_CRL_DIST_POINT}
  URL_OID_CTL_ISSUER                 = LPCSTR(3);
  {$EXTERNALSYM URL_OID_CTL_ISSUER}
  URL_OID_CTL_NEXT_UPDATE            = LPCSTR(4);
  {$EXTERNALSYM URL_OID_CTL_NEXT_UPDATE}
  URL_OID_CRL_ISSUER                 = LPCSTR(5);
  {$EXTERNALSYM URL_OID_CRL_ISSUER}

//
// Get a time valid CAPI2 object
//

function CryptGetTimeValidObject(pszTimeValidOid: LPCSTR; pvPara: LPVOID;
  pIssuer: PCCERT_CONTEXT; pftValidFor: LPFILETIME; dwFlags, dwTimeout: DWORD;
  ppvObject: LPLPVOID; pCredentials: PCRYPT_CREDENTIALS; pvReserved: LPVOID): BOOL; stdcall;
{$EXTERNALSYM CryptGetTimeValidObject}

const
  TIME_VALID_OID_GET_OBJECT_FUNC = 'TimeValidDllGetObject';
  {$EXTERNALSYM TIME_VALID_OID_GET_OBJECT_FUNC}

//
// TimeValidDllGetObject has the same signature as CryptGetTimeValidObject
//

//
// TIME_VALID_OID_GET_CTL
//
// pvPara == PCCTL_CONTEXT, the current CTL
//
// TIME_VALID_OID_GET_CRL
//
// pvPara == PCCRL_CONTEXT, the current CRL
//
// TIME_VALID_OID_GET_CRL_FROM_CERT
//
// pvPara == PCCERT_CONTEXT, the subject cert
//

  TIME_VALID_OID_GET_CTL           = LPCSTR(1);
  {$EXTERNALSYM TIME_VALID_OID_GET_CTL}
  TIME_VALID_OID_GET_CRL           = LPCSTR(2);
  {$EXTERNALSYM TIME_VALID_OID_GET_CRL}
  TIME_VALID_OID_GET_CRL_FROM_CERT = LPCSTR(3);
  {$EXTERNALSYM TIME_VALID_OID_GET_CRL_FROM_CERT}

function CryptFlushTimeValidObject(pszFlushTimeValidOid: LPCSTR; pvPara: LPVOID;
  pIssuer: PCCERT_CONTEXT; dwFlags: DWORD; pvReserved: LPVOID): BOOL; stdcall;
{$EXTERNALSYM CryptFlushTimeValidObject}

const
  TIME_VALID_OID_FLUSH_OBJECT_FUNC = 'TimeValidDllFlushObject';
  {$EXTERNALSYM TIME_VALID_OID_FLUSH_OBJECT_FUNC}

//
// TimeValidDllFlushObject has the same signature as CryptFlushTimeValidObject
//

//
// TIME_VALID_OID_FLUSH_CTL
//
// pvPara == PCCTL_CONTEXT, the CTL to flush
//
// TIME_VALID_OID_FLUSH_CRL
//
// pvPara == PCCRL_CONTEXT, the CRL to flush
//
// TIME_VALID_OID_FLUSH_CRL_FROM_CERT
//

  TIME_VALID_OID_FLUSH_CTL           = LPCSTR(1);
  {$EXTERNALSYM TIME_VALID_OID_FLUSH_CTL}
  TIME_VALID_OID_FLUSH_CRL           = LPCSTR(2);
  {$EXTERNALSYM TIME_VALID_OID_FLUSH_CRL}
  TIME_VALID_OID_FLUSH_CRL_FROM_CERT = LPCSTR(3);
  {$EXTERNALSYM TIME_VALID_OID_FLUSH_CRL_FROM_CERT}

//-------------------------------------------------------------------------
// Data Protection APIs
//-------------------------------------------------------------------------

//
// Data protection APIs enable applications to easily secure data.
//
// The base provider provides protection based on the users' logon
// credentials. The data secured with these APIs follow the same
// roaming characteristics as HKCU -- if HKCU roams, the data
// protected by the base provider may roam as well. This makes
// the API ideal for the munging of data stored in the registry.
//

//
// Prompt struct -- what to tell users about the access
//

type
  PCRYPTPROTECT_PROMPTSTRUCT = ^CRYPTPROTECT_PROMPTSTRUCT;
  {$EXTERNALSYM PCRYPTPROTECT_PROMPTSTRUCT}
  _CRYPTPROTECT_PROMPTSTRUCT = record
    cbSize: DWORD;
    dwPromptFlags: DWORD;
    hwndApp: HWND;
    szPrompt: LPCWSTR;
  end;
  {$EXTERNALSYM _CRYPTPROTECT_PROMPTSTRUCT}
  CRYPTPROTECT_PROMPTSTRUCT = _CRYPTPROTECT_PROMPTSTRUCT;
  {$EXTERNALSYM CRYPTPROTECT_PROMPTSTRUCT}
  TCryptProtectPromptStruct = CRYPTPROTECT_PROMPTSTRUCT;
  PCryptProtectPromptStruct = PCRYPTPROTECT_PROMPTSTRUCT;

//
// base provider action
//

const
  CRYPTPROTECT_DEFAULT_PROVIDER: GUID = (
    D1:$df9d8cd0; D2:$1501; D3:$11d1; D4:($8c, $7a, $00, $c0, $4f, $c2, $97, $eb));
  {$EXTERNALSYM CRYPTPROTECT_DEFAULT_PROVIDER}

//
// CryptProtect PromptStruct dwPromtFlags
//
//
// prompt on unprotect

  CRYPTPROTECT_PROMPT_ON_UNPROTECT = $1; // 1<<0
  {$EXTERNALSYM CRYPTPROTECT_PROMPT_ON_UNPROTECT}

//
// prompt on protect

  CRYPTPROTECT_PROMPT_ON_PROTECT = $2; // 1<<1
  {$EXTERNALSYM CRYPTPROTECT_PROMPT_ON_PROTECT}
  CRYPTPROTECT_PROMPT_RESERVED   = $04; // reserved, do not use.
  {$EXTERNALSYM CRYPTPROTECT_PROMPT_RESERVED}

//
// only allow strong variant UI protection (user supplied password currently).

  CRYPTPROTECT_PROMPT_STRONG = $08; // 1<<3
  {$EXTERNALSYM CRYPTPROTECT_PROMPT_STRONG}

//
// CryptProtectData and CryptUnprotectData dwFlags
//
// for remote-access situations where ui is not an option
// if UI was specified on protect or unprotect operation, the call
// will fail and GetLastError() will indicate ERROR_PASSWORD_RESTRICTION

  CRYPTPROTECT_UI_FORBIDDEN = $1;
  {$EXTERNALSYM CRYPTPROTECT_UI_FORBIDDEN}

//
// per machine protected data -- any user on machine where CryptProtectData
// took place may CryptUnprotectData

  CRYPTPROTECT_LOCAL_MACHINE = $4;
  {$EXTERNALSYM CRYPTPROTECT_LOCAL_MACHINE}

//
// force credential synchronize during CryptProtectData()
// Synchronize is only operation that occurs during this operation

  CRYPTPROTECT_CRED_SYNC = $8;
  {$EXTERNALSYM CRYPTPROTECT_CRED_SYNC}

// flags reserved for system use

  CRYPTPROTECT_FIRST_RESERVED_FLAGVAL = $0FFFFFFF;
  {$EXTERNALSYM CRYPTPROTECT_FIRST_RESERVED_FLAGVAL}
  CRYPTPROTECT_LAST_RESERVED_FLAGVAL  = DWORD($FFFFFFFF);
  {$EXTERNALSYM CRYPTPROTECT_LAST_RESERVED_FLAGVAL}

//
// flags specific to base provider
//

function CryptProtectData(pDataIn: PDATA_BLOB; szDataDescr: LPCWSTR;
  pOptionalEntropy: PDATA_BLOB; pvReserved: PVOID;
  pPromptStruct: PCRYPTPROTECT_PROMPTSTRUCT; dwFlags: DWORD; pDataOut: PDATA_BLOB): BOOL; stdcall;
{$EXTERNALSYM CryptProtectData}

function CryptUnprotectData(pDataIn: PDATA_BLOB; ppszDataDescr: LPLPWSTR;
  pOptionalEntropy: PDATA_BLOB; pvReserved: PVOID;
  pPromptStruct: PCRYPTPROTECT_PROMPTSTRUCT; dwFlags: DWORD; pDataOut: PDATA_BLOB): BOOL; stdcall;
{$EXTERNALSYM CryptUnprotectData}

//+=========================================================================
//  Helper functions to build certificates
//==========================================================================

//+-------------------------------------------------------------------------
//
// Builds a self-signed certificate and returns a PCCERT_CONTEXT representing
// the certificate. A hProv must be specified to build the cert context.
//
// pSubjectIssuerBlob is the DN for the certifcate. If an alternate subject
// name is desired it must be specified as an extension in the pExtensions
// parameter. pSubjectIssuerBlob can NOT be NULL, so minimually an empty DN
// must be specified.
//
// By default:
// pKeyProvInfo - The CSP is queried for the KeyProvInfo parameters. Only the Provider,
// Provider Type and Container is queried. Many CSPs don't support these
// queries and will cause a failure. In such cases the pKeyProvInfo
// must be specified (RSA BASE works fine).
//
// pSignatureAlgorithm - will default to SHA1RSA
// pStartTime will default to the current time
// pEndTime will default to 1 year
// pEntensions will be empty.
//
// The returned PCCERT_CONTEXT will reference the private keys by setting the
// CERT_KEY_PROV_INFO_PROP_ID. However, if this property is not desired specify the
// CERT_CREATE_SELFSIGN_NO_KEY_INFO in dwFlags.
//
// If the cert being built is only a dummy placeholder cert for speed it may not
// need to be signed. Signing of the cert is skipped if CERT_CREATE_SELFSIGN_NO_SIGN
// is specified in dwFlags.
//
//--------------------------------------------------------------------------

function CertCreateSelfSignCertificate(hProv: HCRYPTPROV;
  pSubjectIssuerBlob: PCERT_NAME_BLOB; dwFlags: DWORD;
  pKeyProvInfo: PCRYPT_KEY_PROV_INFO; pSignatureAlgorithm: PCRYPT_ALGORITHM_IDENTIFIER;
  pStartTime, pEndTime: PSYSTEMTIME; pExtensions: PCERT_EXTENSIONS): PCCERT_CONTEXT; stdcall;
{$EXTERNALSYM CertCreateSelfSignCertificate}

const
  CERT_CREATE_SELFSIGN_NO_SIGN     = 1;
  {$EXTERNALSYM CERT_CREATE_SELFSIGN_NO_SIGN}
  CERT_CREATE_SELFSIGN_NO_KEY_INFO = 2;
  {$EXTERNALSYM CERT_CREATE_SELFSIGN_NO_KEY_INFO}

//+=========================================================================
//  Key Identifier Property Data Structures and APIs
//==========================================================================

//+-------------------------------------------------------------------------
//  Get the property for the specified Key Identifier.
//
//  The Key Identifier is the SHA1 hash of the encoded CERT_PUBLIC_KEY_INFO.
//  The Key Identifier for a certificate can be obtained by getting the
//  certificate's CERT_KEY_IDENTIFIER_PROP_ID. The
//  CryptCreateKeyIdentifierFromCSP API can be called to create the Key
//  Identifier from a CSP Public Key Blob.
//
//  A Key Identifier can have the same properties as a certificate context.
//  CERT_KEY_PROV_INFO_PROP_ID is the property of most interest.
//  For CERT_KEY_PROV_INFO_PROP_ID, pvData points to a CRYPT_KEY_PROV_INFO
//  structure. Elements pointed to by fields in the pvData structure follow the
//  structure. Therefore, *pcbData will exceed the size of the structure.
//
//  If CRYPT_KEYID_ALLOC_FLAG is set, then, *pvData is updated with a
//  pointer to allocated memory. LocalFree() must be called to free the
//  allocated memory.
//
//  By default, searches the CurrentUser's list of Key Identifiers.
//  CRYPT_KEYID_MACHINE_FLAG can be set to search the LocalMachine's list
//  of Key Identifiers. When CRYPT_KEYID_MACHINE_FLAG is set, pwszComputerName
//  can also be set to specify the name of a remote computer to be searched
//  instead of the local machine.
//--------------------------------------------------------------------------

function CryptGetKeyIdentifierProperty(pKeyIdentifier: PCRYPT_HASH_BLOB;
  dwPropId: DWORD; dwFlags: DWORD; pwszComputerName: LPCWSTR; pvReserved: Pointer;
  pvData: Pointer; var pcbData: DWORD): BOOL; stdcall;
{$EXTERNALSYM CryptGetKeyIdentifierProperty}

// When the following flag is set, searches the LocalMachine instead of the
// CurrentUser. This flag is applicable to all the KeyIdentifierProperty APIs.

const
  CRYPT_KEYID_MACHINE_FLAG = $00000020;
  {$EXTERNALSYM CRYPT_KEYID_MACHINE_FLAG}

// When the following flag is set, *pvData is updated with a pointer to
// allocated memory. LocalFree() must be called to free the allocated memory.

  CRYPT_KEYID_ALLOC_FLAG = $00008000;
  {$EXTERNALSYM CRYPT_KEYID_ALLOC_FLAG}

//+-------------------------------------------------------------------------
//  Set the property for the specified Key Identifier.
//
//  For CERT_KEY_PROV_INFO_PROP_ID pvData points to the
//  CRYPT_KEY_PROV_INFO data structure. For all other properties, pvData
//  points to a CRYPT_DATA_BLOB.
//
//  Setting pvData == NULL, deletes the property.
//
//  Set CRYPT_KEYID_MACHINE_FLAG to set the property for a LocalMachine
//  Key Identifier. Set pwszComputerName, to select a remote computer.
//
//  If CRYPT_KEYID_DELETE_FLAG is set, the Key Identifier and all its
//  properties is deleted.
//
//  If CRYPT_KEYID_SET_NEW_FLAG is set, the set fails if the property already
//  exists. For an existing property, FALSE is returned with LastError set to
//  CRYPT_E_EXISTS.
//--------------------------------------------------------------------------

function CryptSetKeyIdentifierProperty(pKeyIdentifier: PCRYPT_HASH_BLOB;
  dwPropId: DWORD; dwFlags: DWORD; pwszComputerName: LPCWSTR; pvReserved: Pointer;
  pvData: Pointer): BOOL; stdcall;
{$EXTERNALSYM CryptSetKeyIdentifierProperty}

// When the following flag is set, the Key Identifier and all its properties
// are deleted.

const
  CRYPT_KEYID_DELETE_FLAG = $00000010;
  {$EXTERNALSYM CRYPT_KEYID_DELETE_FLAG}

// When the following flag is set, the set fails if the property already
// exists.

  CRYPT_KEYID_SET_NEW_FLAG = $00002000;
  {$EXTERNALSYM CRYPT_KEYID_SET_NEW_FLAG}

//+-------------------------------------------------------------------------
//  For CERT_KEY_PROV_INFO_PROP_ID, rgppvData[] points to a
//  CRYPT_KEY_PROV_INFO.
//
//  Return FALSE to stop the enumeration.
//--------------------------------------------------------------------------

type
  PFN_CRYPT_ENUM_KEYID_PROP = function (pKeyIdentifier: PCRYPT_HASH_BLOB;
    dwFlags: DWORD; pvReserved: Pointer; pvArg: Pointer; cProp: DWORD;
    rgdwPropId: LPDWORD; rgpvData: Pointer; rgcbData: LPDWORD): BOOL; stdcall;
  {$EXTERNALSYM PFN_CRYPT_ENUM_KEYID_PROP}
  PFnCryptEnumKeyIdProp = PFN_CRYPT_ENUM_KEYID_PROP;

//+-------------------------------------------------------------------------
//  Enumerate the Key Identifiers.
//
//  If pKeyIdentifier is NULL, enumerates all Key Identifers. Otherwise,
//  calls the callback for the specified KeyIdentifier. If dwPropId is
//  0, calls the callback with all the properties. Otherwise, only calls
//  the callback with the specified property (cProp = 1).
//  Furthermore, when dwPropId is specified, skips KeyIdentifiers not
//  having the property.
//
//  Set CRYPT_KEYID_MACHINE_FLAG to enumerate the LocalMachine
//  Key Identifiers. Set pwszComputerName, to enumerate Key Identifiers on
//  a remote computer.
//--------------------------------------------------------------------------

function CryptEnumKeyIdentifierProperties(pKeyIdentifier: PCRYPT_HASH_BLOB;
  dwPropId: DWORD; dwFlags: DWORD; pwszComputerName: LPCWSTR; pvReserved: Pointer;
  pvArg: Pointer; pfnEnum: PFN_CRYPT_ENUM_KEYID_PROP): BOOL; stdcall;
{$EXTERNALSYM CryptEnumKeyIdentifierProperties}

//+-------------------------------------------------------------------------
//  Create a KeyIdentifier from the CSP Public Key Blob.
//
//  Converts the CSP PUBLICKEYSTRUC into a X.509 CERT_PUBLIC_KEY_INFO and
//  encodes. The encoded CERT_PUBLIC_KEY_INFO is SHA1 hashed to obtain
//  the Key Identifier.
//
//  By default, the pPubKeyStruc->aiKeyAlg is used to find the appropriate
//  public key Object Identifier. pszPubKeyOID can be set to override
//  the default OID obtained from the aiKeyAlg.
//--------------------------------------------------------------------------

function CryptCreateKeyIdentifierFromCSP(dwCertEncodingType: DWORD;
  pszPubKeyOID: LPCSTR; pPubKeyStruc: PPUBLICKEYSTRUC; cbPubKeyStruc: DWORD;
  dwFlags: DWORD; pvReserved: Pointer; pbHash: LPBYTE; pcbHash: DWORD): BOOL; stdcall;
{$EXTERNALSYM CryptCreateKeyIdentifierFromCSP}

//+=========================================================================
//  Certificate Chaining Infrastructure
//==========================================================================

//
// The chain engine defines the store namespace and cache partitioning for
// the Certificate Chaining infrastructure.  A default chain engine
// is defined for the process which uses all default system stores e.g.
// Root, CA, Trust, for chain building and caching.  If an application
// wishes to define its own store namespace or have its own partitioned
// cache then it can create its own chain engine.  It is advisable to create
// a chain engine at application startup and use it throughout the lifetime
// of the application in order to get optimal caching behavior
//

type
  HCERTCHAINENGINE = HANDLE;
  {$EXTERNALSYM HCERTCHAINENGINE}

const
  HCCE_CURRENT_USER  = HCERTCHAINENGINE(0);
  {$EXTERNALSYM HCCE_CURRENT_USER}
  HCCE_LOCAL_MACHINE = HCERTCHAINENGINE($1);
  {$EXTERNALSYM HCCE_LOCAL_MACHINE}

//
// Create a certificate chain engine.
//

//
// Configuration parameters for the certificate chain engine
//
//      hRestrictedRoot - restrict the root store (must be a subset of "Root")
//
//      hRestrictedTrust - restrict the store for CTLs
//
//      hRestrictedOther - restrict the store for certs and CRLs
//
//      cAdditionalStore, rghAdditionalStore - additional stores
//
//      NOTE: The algorithm used to define the stores for the engine is as
//            follows:
//
//            hRoot = hRestrictedRoot or System Store "Root"
//
//            hTrust = hRestrictedTrust or hWorld (defined later)
//
//            hOther = hRestrictedOther or (hRestrictedTrust == NULL) ? hWorld :
//                     hRestrictedTrust + hWorld
//
//            hWorld = hRoot + "CA" + "My" + "Trust" + rghAdditionalStore
//
//      dwFlags  - flags
//
//          CERT_CHAIN_CACHE_END_CERT - information will be cached on
//                                      the end cert as well as the other
//                                      certs in the chain
//
//          CERT_CHAIN_THREAD_STORE_SYNC - use separate thread for store syncs
//                                         and related cache updates
//
//          CERT_CHAIN_CACHE_ONLY_URL_RETRIEVAL - don't hit the wire to get
//                                                URL based objects
//
//      dwUrlRetrievalTimeout - timeout for wire based URL object retrievals
//

const
  CERT_CHAIN_CACHE_END_CERT           = $00000001;
  {$EXTERNALSYM CERT_CHAIN_CACHE_END_CERT}
  CERT_CHAIN_THREAD_STORE_SYNC        = $00000002;
  {$EXTERNALSYM CERT_CHAIN_THREAD_STORE_SYNC}
  CERT_CHAIN_CACHE_ONLY_URL_RETRIEVAL = $00000004;
  {$EXTERNALSYM CERT_CHAIN_CACHE_ONLY_URL_RETRIEVAL}
  CERT_CHAIN_USE_LOCAL_MACHINE_STORE  = $00000008;
  {$EXTERNALSYM CERT_CHAIN_USE_LOCAL_MACHINE_STORE}
  CERT_CHAIN_ENABLE_CACHE_AUTO_UPDATE = $00000010;
  {$EXTERNALSYM CERT_CHAIN_ENABLE_CACHE_AUTO_UPDATE}

type
  PCERT_CHAIN_ENGINE_CONFIG = ^CERT_CHAIN_ENGINE_CONFIG;
  {$EXTERNALSYM PCERT_CHAIN_ENGINE_CONFIG}
  _CERT_CHAIN_ENGINE_CONFIG = record
    cbSize: DWORD;
    hRestrictedRoot: HCERTSTORE;
    hRestrictedTrust: HCERTSTORE;
    hRestrictedOther: HCERTSTORE;
    cAdditionalStore: DWORD;
    rghAdditionalStore: PHCERTSTORE;
    dwFlags: DWORD;
    dwUrlRetrievalTimeout: DWORD;
    MaximumCachedCertificates: DWORD;
    CycleDetectionModulus: DWORD;
  end;
  {$EXTERNALSYM _CERT_CHAIN_ENGINE_CONFIG}
  CERT_CHAIN_ENGINE_CONFIG = _CERT_CHAIN_ENGINE_CONFIG;
  {$EXTERNALSYM CERT_CHAIN_ENGINE_CONFIG}
  TCertChainEngineConfig = CERT_CHAIN_ENGINE_CONFIG;
  PCertChainEngineConfig = PCERT_CHAIN_ENGINE_CONFIG;

function CertCreateCertificateChainEngine(pConfig: PCERT_CHAIN_ENGINE_CONFIG;
  var phChainEngine: HCERTCHAINENGINE): BOOL; stdcall;
{$EXTERNALSYM CertCreateCertificateChainEngine}

//
// Free a certificate trust engine
//

procedure CertFreeCertificateChainEngine(hChainEngine: HCERTCHAINENGINE); stdcall;
{$EXTERNALSYM CertFreeCertificateChainEngine}

//
// Resync the certificate chain engine.  This resync's the stores backing
// the engine and updates the engine caches.
//

function CertResyncCertificateChainEngine(hChainEngine: HCERTCHAINENGINE): BOOL; stdcall;
{$EXTERNALSYM CertResyncCertificateChainEngine}

//
// When an application requests a certificate chain, the data structure
// returned is in the form of a CERT_CHAIN_CONTEXT.  This contains
// an array of CERT_SIMPLE_CHAIN where each simple chain goes from
// an end cert to a self signed cert and the chain context connects simple
// chains via trust lists.  Each simple chain contains the chain of
// certificates, summary trust information about the chain and trust information
// about each certificate element in the chain.
//

//
// Trust status bits
//

type
  PCERT_TRUST_STATUS = ^CERT_TRUST_STATUS;
  {$EXTERNALSYM PCERT_TRUST_STATUS}
  _CERT_TRUST_STATUS = record
    dwErrorStatus: DWORD;
    dwInfoStatus: DWORD;
  end;
  {$EXTERNALSYM _CERT_TRUST_STATUS}
  CERT_TRUST_STATUS = _CERT_TRUST_STATUS;
  {$EXTERNALSYM CERT_TRUST_STATUS}
  TCertTrustStatus = CERT_TRUST_STATUS;
  PCertTrustStatus = PCERT_TRUST_STATUS;

//
// The following are error status bits
//

// These can be applied to certificates and chains

const
  CERT_TRUST_NO_ERROR                  = $00000000;
  {$EXTERNALSYM CERT_TRUST_NO_ERROR}
  CERT_TRUST_IS_NOT_TIME_VALID         = $00000001;
  {$EXTERNALSYM CERT_TRUST_IS_NOT_TIME_VALID}
  CERT_TRUST_IS_NOT_TIME_NESTED        = $00000002;
  {$EXTERNALSYM CERT_TRUST_IS_NOT_TIME_NESTED}
  CERT_TRUST_IS_REVOKED                = $00000004;
  {$EXTERNALSYM CERT_TRUST_IS_REVOKED}
  CERT_TRUST_IS_NOT_SIGNATURE_VALID    = $00000008;
  {$EXTERNALSYM CERT_TRUST_IS_NOT_SIGNATURE_VALID}
  CERT_TRUST_IS_NOT_VALID_FOR_USAGE    = $00000010;
  {$EXTERNALSYM CERT_TRUST_IS_NOT_VALID_FOR_USAGE}
  CERT_TRUST_IS_UNTRUSTED_ROOT         = $00000020;
  {$EXTERNALSYM CERT_TRUST_IS_UNTRUSTED_ROOT}
  CERT_TRUST_REVOCATION_STATUS_UNKNOWN = $00000040;
  {$EXTERNALSYM CERT_TRUST_REVOCATION_STATUS_UNKNOWN}
  CERT_TRUST_IS_CYCLIC                 = $00000080;
  {$EXTERNALSYM CERT_TRUST_IS_CYCLIC}

// These can be applied to chains only

  CERT_TRUST_IS_PARTIAL_CHAIN           = $00010000;
  {$EXTERNALSYM CERT_TRUST_IS_PARTIAL_CHAIN}
  CERT_TRUST_CTL_IS_NOT_TIME_VALID      = $00020000;
  {$EXTERNALSYM CERT_TRUST_CTL_IS_NOT_TIME_VALID}
  CERT_TRUST_CTL_IS_NOT_SIGNATURE_VALID = $00040000;
  {$EXTERNALSYM CERT_TRUST_CTL_IS_NOT_SIGNATURE_VALID}
  CERT_TRUST_CTL_IS_NOT_VALID_FOR_USAGE = $00080000;
  {$EXTERNALSYM CERT_TRUST_CTL_IS_NOT_VALID_FOR_USAGE}

//
// The following are info status bits
//

// These can be applied to certificates only

  CERT_TRUST_HAS_EXACT_MATCH_ISSUER = $00000001;
  {$EXTERNALSYM CERT_TRUST_HAS_EXACT_MATCH_ISSUER}
  CERT_TRUST_HAS_KEY_MATCH_ISSUER   = $00000002;
  {$EXTERNALSYM CERT_TRUST_HAS_KEY_MATCH_ISSUER}
  CERT_TRUST_HAS_NAME_MATCH_ISSUER  = $00000004;
  {$EXTERNALSYM CERT_TRUST_HAS_NAME_MATCH_ISSUER}
  CERT_TRUST_IS_SELF_SIGNED         = $00000008;
  {$EXTERNALSYM CERT_TRUST_IS_SELF_SIGNED}

// These can be applied to chains only

  CERT_TRUST_IS_COMPLEX_CHAIN = $00010000;
  {$EXTERNALSYM CERT_TRUST_IS_COMPLEX_CHAIN}

//
// Each certificate context in a simple chain has a corresponding chain element
// in the simple chain context
//
// dwErrorStatus has CERT_TRUST_IS_REVOKED, pRevocationInfo set
// dwErrorStatus has CERT_TRUST_REVOCATION_STATUS_UNKNOWN, pRevocationInfo set

//
// BUGBUG: Note that the post processing revocation supported in the first
//         version only sets cbSize and dwRevocationResult.  Everything else
//         is NULL
//

//
// Revocation Information
//

type
  PCERT_REVOCATION_INFO = ^CERT_REVOCATION_INFO;
  {$EXTERNALSYM PCERT_REVOCATION_INFO}
  _CERT_REVOCATION_INFO = record
    cbSize: DWORD;
    dwRevocationResult: DWORD;
    pszRevocationOid: LPCSTR;
    pvOidSpecificInfo: LPVOID;
  end;
  {$EXTERNALSYM _CERT_REVOCATION_INFO}
  CERT_REVOCATION_INFO = _CERT_REVOCATION_INFO;
  {$EXTERNALSYM CERT_REVOCATION_INFO}
  TCertRevocationInfo = CERT_REVOCATION_INFO;
  PCertRevocationInfo = PCERT_REVOCATION_INFO;

//
// Trust List Information
//

  PCERT_TRUST_LIST_INFO = ^CERT_TRUST_LIST_INFO;
  {$EXTERNALSYM PCERT_TRUST_LIST_INFO}
  _CERT_TRUST_LIST_INFO = record
    cbSize: DWORD;
    pCtlEntry: PCTL_ENTRY;
    pCtlContext: PCCTL_CONTEXT;
  end;
  {$EXTERNALSYM _CERT_TRUST_LIST_INFO}
  CERT_TRUST_LIST_INFO = _CERT_TRUST_LIST_INFO;
  {$EXTERNALSYM CERT_TRUST_LIST_INFO}
  TCertTrustListInfo = CERT_TRUST_LIST_INFO;
  PCertTrustListInfo = PCERT_TRUST_LIST_INFO;

//
// Chain Element
//

  PCERT_CHAIN_ELEMENT = ^CERT_CHAIN_ELEMENT;
  {$EXTERNALSYM PCERT_CHAIN_ELEMENT}
  _CERT_CHAIN_ELEMENT = record
    cbSize: DWORD;
    pCertContext: PCCERT_CONTEXT;
    TrustStatus: CERT_TRUST_STATUS;
    pRevocationInfo: PCERT_REVOCATION_INFO;
  end;
  {$EXTERNALSYM _CERT_CHAIN_ELEMENT}
  CERT_CHAIN_ELEMENT = _CERT_CHAIN_ELEMENT;
  {$EXTERNALSYM CERT_CHAIN_ELEMENT}
  TCertChainElement = CERT_CHAIN_ELEMENT;
  PCertChainElement = PCERT_CHAIN_ELEMENT;

//
// The simple chain is an array of chain elements and a summary trust status
// for the chain
//
// rgpElements[0] is the end certificate chain element
//
// rgpElements[cElement-1] is the self-signed "root" certificate chain element
//

  PCERT_SIMPLE_CHAIN = ^CERT_SIMPLE_CHAIN;
  {$EXTERNALSYM PCERT_SIMPLE_CHAIN}
  _CERT_SIMPLE_CHAIN = record
    cbSize: DWORD;
    TrustStatus: CERT_TRUST_STATUS;
    cElement: DWORD;
    rgpElement: PCERT_CHAIN_ELEMENT;
    pTrustListInfo: PCERT_TRUST_LIST_INFO;
  end;
  {$EXTERNALSYM _CERT_SIMPLE_CHAIN}
  CERT_SIMPLE_CHAIN = _CERT_SIMPLE_CHAIN;
  {$EXTERNALSYM CERT_SIMPLE_CHAIN}
  TCertSimpleChain = CERT_SIMPLE_CHAIN;
  PCertSimpleChain = PCERT_SIMPLE_CHAIN;

//
// And the chain context contains an array of simple chains and summary trust
// status for all the connected simple chains
//
// rgpChains[0] is the end certificate simple chain
//
// rgpChains[cChain-1] is the final (possibly trust list signer) chain which
// ends in a certificate which is contained in the root store
//

  PCERT_CHAIN_CONTEXT = ^CERT_CHAIN_CONTEXT;
  {$EXTERNALSYM PCERT_CHAIN_CONTEXT}
  _CERT_CHAIN_CONTEXT = record
    cbSize: DWORD;
    TrustStatus: CERT_TRUST_STATUS;
    cChain: DWORD;
    rgpChain: PCERT_SIMPLE_CHAIN;
  end;
  {$EXTERNALSYM _CERT_CHAIN_CONTEXT}
  CERT_CHAIN_CONTEXT = _CERT_CHAIN_CONTEXT;
  {$EXTERNALSYM CERT_CHAIN_CONTEXT}
  TCertChainContext = CERT_CHAIN_CONTEXT;
  PCertChainContext = PCERT_CHAIN_CONTEXT;

  PCCERT_CHAIN_CONTEXT = ^CERT_CHAIN_CONTEXT;
  {$EXTERNALSYM PCCERT_CHAIN_CONTEXT}
  PPCCERT_CHAIN_CONTEXT = ^PCERT_CHAIN_CONTEXT;
  {$NODEFINE PPCCERT_CHAIN_CONTEXT}

//
// When building a chain, the there are various parameters used for finding
// issuing certificates and trust lists.  They are identified in the
// following structure
//

// Default usage match type is AND with value zero

const
  USAGE_MATCH_TYPE_AND = $00000000;
  {$EXTERNALSYM USAGE_MATCH_TYPE_AND}
  USAGE_MATCH_TYPE_OR  = $00000001;
  {$EXTERNALSYM USAGE_MATCH_TYPE_OR}

type
  PCERT_USAGE_MATCH = ^CERT_USAGE_MATCH;
  {$EXTERNALSYM PCERT_USAGE_MATCH}
  _CERT_USAGE_MATCH = record
    dwType: DWORD;
    Usage: CERT_ENHKEY_USAGE;
  end;
  {$EXTERNALSYM _CERT_USAGE_MATCH}
  CERT_USAGE_MATCH = _CERT_USAGE_MATCH;
  {$EXTERNALSYM CERT_USAGE_MATCH}
  TCertUsageMatch = CERT_USAGE_MATCH;
  PCertUsageMatch = PCERT_USAGE_MATCH;

  PCTL_USAGE_MATCH = ^CTL_USAGE_MATCH;
  {$EXTERNALSYM PCTL_USAGE_MATCH}
  _CTL_USAGE_MATCH = record
    dwType: DWORD;
    Usage: CTL_USAGE;
  end;
  {$EXTERNALSYM _CTL_USAGE_MATCH}
  CTL_USAGE_MATCH = _CTL_USAGE_MATCH;
  {$EXTERNALSYM CTL_USAGE_MATCH}
  TCtlUsageMatch = CTL_USAGE_MATCH;
  PCtlUsageMatch = PCTL_USAGE_MATCH;

  PCERT_CHAIN_PARA = ^CERT_CHAIN_PARA;
  {$EXTERNALSYM PCERT_CHAIN_PARA}
  _CERT_CHAIN_PARA = record
    cbSize: DWORD;
    RequestedUsage: CERT_USAGE_MATCH;
  end;
  {$EXTERNALSYM _CERT_CHAIN_PARA}
  CERT_CHAIN_PARA = _CERT_CHAIN_PARA;
  {$EXTERNALSYM CERT_CHAIN_PARA}
  TCertChainPara = CERT_CHAIN_PARA;
  PCertChainPara = PCERT_CHAIN_PARA;

//
// The following API is used for retrieving certificate chains
//
// Parameters:
//
//      hChainEngine     - the chain engine (namespace and cache) to use, NULL
//                         mean use the default chain engine
//
//      pCertContext     - the context we are retrieving the chain for, it
//                         will be the zero index element in the chain
//
//      pTime            - the point in time that we want the chain validated
//                         for.  Note that the time does not affect trust list,
//                         revocation, or root store checking.  NULL means use
//                         the current system time
//
//      hAdditionalStore - additional store to use when looking up objects
//
//      pChainPara       - parameters for chain building
//
//      dwFlags          - flags such as should revocation checking be done
//                         on the chain?
//
//      pvReserved       - reserved parameter, must be NULL
//
//      ppChainContext   - chain context returned
//

// CERT_CHAIN_CACHE_END_CERT can be used here as well
// Revocation flags are in the high nibble

const
  CERT_CHAIN_REVOCATION_CHECK_END_CERT           = $10000000;
  {$EXTERNALSYM CERT_CHAIN_REVOCATION_CHECK_END_CERT}
  CERT_CHAIN_REVOCATION_CHECK_CHAIN              = $20000000;
  {$EXTERNALSYM CERT_CHAIN_REVOCATION_CHECK_CHAIN}
  CERT_CHAIN_REVOCATION_CHECK_CHAIN_EXCLUDE_ROOT = $40000000;
  {$EXTERNALSYM CERT_CHAIN_REVOCATION_CHECK_CHAIN_EXCLUDE_ROOT}
  CERT_CHAIN_REVOCATION_CHECK_CACHE_ONLY         = DWORD($80000000);
  {$EXTERNALSYM CERT_CHAIN_REVOCATION_CHECK_CACHE_ONLY}

function CertGetCertificateChain(hChainEngine: HCERTCHAINENGINE;
  pCertContext: PCCERT_CONTEXT; pTime: LPFILETIME; hAdditionalStore: HCERTSTORE;
  pChainPara: PCERT_CHAIN_PARA; dwFlags: DWORD; pvReserved: LPVOID;
  ppChainContext: PPCCERT_CHAIN_CONTEXT): BOOL; stdcall;
{$EXTERNALSYM CertGetCertificateChain}

//
// Free a certificate chain
//

procedure CertFreeCertificateChain(pChainContext: PCCERT_CHAIN_CONTEXT); stdcall;
{$EXTERNALSYM CertFreeCertificateChain}

//
// Duplicate (add a reference to) a certificate chain
//

function CertDuplicateCertificateChain(pChainContext: PCCERT_CHAIN_CONTEXT): PCCERT_CHAIN_CONTEXT; stdcall;
{$EXTERNALSYM CertDuplicateCertificateChain}

//
// Specific Revocation Type OID and structure definitions
//

//
// CRL Revocation OID
//

const
  REVOCATION_OID_CRL_REVOCATION = LPCSTR(1);
  {$EXTERNALSYM REVOCATION_OID_CRL_REVOCATION}

//
// For the CRL revocation OID the pvRevocationPara is NULL
//

//
// CRL Revocation Info
//

type
  PCRL_REVOCATION_INFO = ^CRL_REVOCATION_INFO;
  {$EXTERNALSYM PCRL_REVOCATION_INFO}
  _CRL_REVOCATION_INFO = record
    pCrlEntry: PCRL_ENTRY;
    pCrlContext: PCCRL_CONTEXT;
    pCrlIssuerChain: PCCERT_CHAIN_CONTEXT;
  end;
  {$EXTERNALSYM _CRL_REVOCATION_INFO}
  CRL_REVOCATION_INFO = _CRL_REVOCATION_INFO;
  {$EXTERNALSYM CRL_REVOCATION_INFO}
  TCrlRevocationInfo = CRL_REVOCATION_INFO;
  PCrlRevocationInfo = PCRL_REVOCATION_INFO;

//+-------------------------------------------------------------------------
//  Find the first or next certificate chain context in the store.
//
//  The chain context is found according to the dwFindFlags, dwFindType and
//  its pvFindPara. See below for a list of the find types and its parameters.
//
//  If the first or next chain context isn't found, NULL is returned.
//  Otherwise, a pointer to a read only CERT_CHAIN_CONTEXT is returned.
//  CERT_CHAIN_CONTEXT must be freed by calling CertFreeCertificateChain
//  or is freed when passed as the
//  pPrevChainContext on a subsequent call. CertDuplicateCertificateChain
//  can be called to make a duplicate.
//
//  pPrevChainContext MUST BE NULL on the first
//  call to find the chain context. To find the next chain context, the
//  pPrevChainContext is set to the CERT_CHAIN_CONTEXT returned by a previous
//  call.
//
//  NOTE: a NON-NULL pPrevChainContext is always CertFreeCertificateChain'ed by
//  this function, even for an error.
//--------------------------------------------------------------------------

function CertFindChainInStore(hCertStore: HCERTSTORE; dwCertEncodingType: DWORD;
  dwFindFlags: DWORD; dwFindType: DWORD; pvFindPara: Pointer;
  pPrevChainContext: PCCERT_CHAIN_CONTEXT): PCCERT_CHAIN_CONTEXT; stdcall;
{$EXTERNALSYM CertFindChainInStore}

const
  CERT_CHAIN_FIND_BY_ISSUER = 1;
  {$EXTERNALSYM CERT_CHAIN_FIND_BY_ISSUER}

//+-------------------------------------------------------------------------
//  CERT_CHAIN_FIND_BY_ISSUER
//
//  Find a certificate chain having a private key for the end certificate and
//  matching one of the given issuer names. A matching dwKeySpec and
//  enhanced key usage can also be specified. Additionally a callback can
//  be provided for even more caller provided filtering before building the
//  chain.
//
//  By default, only the issuers in the first simple chain are compared
//  for a name match. CERT_CHAIN_FIND_BY_ISSUER_COMPLEX_CHAIN_FLAG can
//  be set in dwFindFlags to match issuers in all the simple chains.
//
//  CERT_CHAIN_FIND_BY_ISSUER_NO_KEY_FLAG can be set in dwFindFlags to
//  not check if the end certificate has a private key.
//
//  CERT_CHAIN_FIND_BY_ISSUER_COMPARE_KEY_FLAG can be set in dwFindFlags
//  to compare the public key in the end certificate with the crypto
//  provider's public key. The dwAcquirePrivateKeyFlags can be set
//  in CERT_CHAIN_FIND_BY_ISSUER_PARA to enable caching of the private key's
//  HKEY returned by the CSP.
//
//  If dwCertEncodingType == 0, defaults to X509_ASN_ENCODING for the
//  array of encoded issuer names.
//
//  By default, the hCertStore passed to CertFindChainInStore, is passed
//  as an additional store to CertGetCertificateChain.
//  CERT_CHAIN_FIND_BY_ISSUER_CACHE_ONLY_FLAG can be set in dwFindFlags
//  to improve performance by only searching the cached system stores
//  (root, my, ca, trust) to find the issuer certificates. If you are doing
//  a find in the "my" system store, than, this flag should be set to
//  improve performance.
//
//  Setting CERT_CHAIN_FIND_BY_ISSUER_LOCAL_MACHINE_FLAG in dwFindFlags
//  restricts CertGetCertificateChain to search the Local Machine
//  cached system stores instead of the Current User's.
//
//  Setting CERT_CHAIN_FIND_BY_ISSUER_CACHE_ONLY_URL_FLAG in dwFindFlags
//  restricts CertGetCertificateChain to only search the URL cache
//  and not hit the wire.
//--------------------------------------------------------------------------

// Returns FALSE to skip this certificate. Otherwise, returns TRUE to
// build a chain for this certificate.

type
  PFN_CERT_CHAIN_FIND_BY_ISSUER_CALLBACK = function (pCert: PCCERT_CONTEXT;
    pvFindArg: Pointer): BOOL; stdcall;
  {$EXTERNALSYM PFN_CERT_CHAIN_FIND_BY_ISSUER_CALLBACK}
  PFnCertChainFindByIssuerCallback = PFN_CERT_CHAIN_FIND_BY_ISSUER_CALLBACK;

  PCERT_CHAIN_FIND_BY_ISSUER_PARA = ^CERT_CHAIN_FIND_BY_ISSUER_PARA;
  {$EXTERNALSYM PCERT_CHAIN_FIND_BY_ISSUER_PARA}
  _CERT_CHAIN_FIND_BY_ISSUER_PARA = record
    cbSize: DWORD;
    // If pszUsageIdentifier == NULL, matches any usage.
    pszUsageIdentifier: LPCSTR;
    // If dwKeySpec == 0, matches any KeySpec
    dwKeySpec: DWORD;
    // When CERT_CHAIN_FIND_BY_ISSUER_COMPARE_KEY_FLAG is set in dwFindFlags,
    // CryptAcquireCertificatePrivateKey is called to do the public key
    // comparison. The following flags can be set to enable caching
    // of the acquired private key. See the API for more details on these
    // flags.
    dwAcquirePrivateKeyFlags: DWORD;
    // Pointer to an array of X509, ASN.1 encoded issuer name blobs. If
    // cIssuer == 0, matches any issuer
    cIssuer: DWORD;
    rgIssuer: PCERT_NAME_BLOB;
    // If NULL or Callback returns TRUE, builds the chain for the end
    // certificate having a private key with the specified KeySpec and
    // enhanced key usage.
    pfnFindCallback: PFN_CERT_CHAIN_FIND_BY_ISSUER_CALLBACK;
    pvFindArg: Pointer;
  end;
  {$EXTERNALSYM _CERT_CHAIN_FIND_BY_ISSUER_PARA}
  CERT_CHAIN_FIND_BY_ISSUER_PARA = _CERT_CHAIN_FIND_BY_ISSUER_PARA;
  {$EXTERNALSYM CERT_CHAIN_FIND_BY_ISSUER_PARA}
  TCertChainFindByIssuerPara = CERT_CHAIN_FIND_BY_ISSUER_PARA;
  PCertChainFindByIssuerPara = PCERT_CHAIN_FIND_BY_ISSUER_PARA;

// The following dwFindFlags can be set for CERT_CHAIN_FIND_BY_ISSUER

// If set, compares the public key in the end certificate with the crypto
// provider's public key. This comparison is the last check made on the
// build chain.

const
  CERT_CHAIN_FIND_BY_ISSUER_COMPARE_KEY_FLAG = $0001;
  {$EXTERNALSYM CERT_CHAIN_FIND_BY_ISSUER_COMPARE_KEY_FLAG}

// If not set, only checks the first simple chain for an issuer name match.
// When set, also checks second and subsequent simple chains.

  CERT_CHAIN_FIND_BY_ISSUER_COMPLEX_CHAIN_FLAG = $0002;
  {$EXTERNALSYM CERT_CHAIN_FIND_BY_ISSUER_COMPLEX_CHAIN_FLAG}

// If set, CertGetCertificateChain only searches the URL cache and
// doesn't hit the wire.

  CERT_CHAIN_FIND_BY_ISSUER_CACHE_ONLY_URL_FLAG = $0004;
  {$EXTERNALSYM CERT_CHAIN_FIND_BY_ISSUER_CACHE_ONLY_URL_FLAG}

// If set, CertGetCertificateChain only opens the Local Machine
// certificate stores instead of the Current User's.

  CERT_CHAIN_FIND_BY_ISSUER_LOCAL_MACHINE_FLAG = $0008;
  {$EXTERNALSYM CERT_CHAIN_FIND_BY_ISSUER_LOCAL_MACHINE_FLAG}

// If set, no check is made to see if the end certificate has a private
// key associated with it.

  CERT_CHAIN_FIND_BY_ISSUER_NO_KEY_FLAG = $4000;
  {$EXTERNALSYM CERT_CHAIN_FIND_BY_ISSUER_NO_KEY_FLAG}

// By default, the hCertStore passed to CertFindChainInStore, is passed
// as the additional store to CertGetCertificateChain. This flag can be
// set to improve performance by only searching the cached system stores
// (root, my, ca, trust) to find the issuer certificates. If not set, then,
// the hCertStore is always searched in addition to the cached system
// stores.

  CERT_CHAIN_FIND_BY_ISSUER_CACHE_ONLY_FLAG = $8000;
  {$EXTERNALSYM CERT_CHAIN_FIND_BY_ISSUER_CACHE_ONLY_FLAG}

//+=========================================================================
//  Certificate Chain Policy Data Structures and APIs
//==========================================================================

type
  PCERT_CHAIN_POLICY_PARA = ^CERT_CHAIN_POLICY_PARA;
  {$EXTERNALSYM PCERT_CHAIN_POLICY_PARA}
  _CERT_CHAIN_POLICY_PARA = record
    cbSize: DWORD;
    dwFlags: DWORD;
    pvExtraPolicyPara: Pointer; // pszPolicyOID specific
  end;
  {$EXTERNALSYM _CERT_CHAIN_POLICY_PARA}
  CERT_CHAIN_POLICY_PARA = _CERT_CHAIN_POLICY_PARA;
  {$EXTERNALSYM CERT_CHAIN_POLICY_PARA}
  TCertChainPolicyPara = CERT_CHAIN_POLICY_PARA;
  PCertChainPolicyPara = PCERT_CHAIN_POLICY_PARA;

// If both lChainIndex and lElementIndex are set to -1, the dwError applies
// to the whole chain context. If only lElementIndex is set to -1, the
// dwError applies to the lChainIndex'ed chain. Otherwise, the dwError applies
// to the certificate element at
// pChainContext->rgpChain[lChainIndex]->rgpElement[lElementIndex].

  PCERT_CHAIN_POLICY_STATUS = ^CERT_CHAIN_POLICY_STATUS;
  {$EXTERNALSYM PCERT_CHAIN_POLICY_STATUS}
  _CERT_CHAIN_POLICY_STATUS = record
    cbSize: DWORD;
    dwError: DWORD;
    lChainIndex: LONG;
    lElementIndex: LONG;
    pvExtraPolicyStatus: Pointer; // pszPolicyOID specific
  end;
  {$EXTERNALSYM _CERT_CHAIN_POLICY_STATUS}
  CERT_CHAIN_POLICY_STATUS = _CERT_CHAIN_POLICY_STATUS;
  {$EXTERNALSYM CERT_CHAIN_POLICY_STATUS}
  TCertChainPolicyStatus = CERT_CHAIN_POLICY_STATUS;
  PCertChainPolicyStatus = PCERT_CHAIN_POLICY_STATUS;

// Common chain policy flags

const
  CERT_CHAIN_POLICY_IGNORE_NOT_TIME_VALID_FLAG     = $00000001;
  {$EXTERNALSYM CERT_CHAIN_POLICY_IGNORE_NOT_TIME_VALID_FLAG}
  CERT_CHAIN_POLICY_IGNORE_CTL_NOT_TIME_VALID_FLAG = $00000002;
  {$EXTERNALSYM CERT_CHAIN_POLICY_IGNORE_CTL_NOT_TIME_VALID_FLAG}
  CERT_CHAIN_POLICY_IGNORE_NOT_TIME_NESTED_FLAG    = $00000004;
  {$EXTERNALSYM CERT_CHAIN_POLICY_IGNORE_NOT_TIME_NESTED_FLAG}

  CERT_CHAIN_POLICY_IGNORE_ALL_NOT_TIME_VALID_FLAGS = (
    CERT_CHAIN_POLICY_IGNORE_NOT_TIME_VALID_FLAG or
    CERT_CHAIN_POLICY_IGNORE_CTL_NOT_TIME_VALID_FLAG or
    CERT_CHAIN_POLICY_IGNORE_NOT_TIME_NESTED_FLAG);
  {$EXTERNALSYM CERT_CHAIN_POLICY_IGNORE_ALL_NOT_TIME_VALID_FLAGS}

  CERT_CHAIN_POLICY_ALLOW_UNKNOWN_CA_FLAG   = $00000010;
  {$EXTERNALSYM CERT_CHAIN_POLICY_ALLOW_UNKNOWN_CA_FLAG}
  CERT_CHAIN_POLICY_IGNORE_WRONG_USAGE_FLAG = $00000020;
  {$EXTERNALSYM CERT_CHAIN_POLICY_IGNORE_WRONG_USAGE_FLAG}

  CERT_CHAIN_POLICY_IGNORE_END_REV_UNKNOWN_FLAG        = $00000100;
  {$EXTERNALSYM CERT_CHAIN_POLICY_IGNORE_END_REV_UNKNOWN_FLAG}
  CERT_CHAIN_POLICY_IGNORE_CTL_SIGNER_REV_UNKNOWN_FLAG = $00000200;
  {$EXTERNALSYM CERT_CHAIN_POLICY_IGNORE_CTL_SIGNER_REV_UNKNOWN_FLAG}
  CERT_CHAIN_POLICY_IGNORE_CA_REV_UNKNOWN_FLAG         = $00000400;
  {$EXTERNALSYM CERT_CHAIN_POLICY_IGNORE_CA_REV_UNKNOWN_FLAG}
  CERT_CHAIN_POLICY_IGNORE_ROOT_REV_UNKNOWN_FLAG       = $00000800;
  {$EXTERNALSYM CERT_CHAIN_POLICY_IGNORE_ROOT_REV_UNKNOWN_FLAG}

  CERT_CHAIN_POLICY_IGNORE_ALL_REV_UNKNOWN_FLAGS = (
    CERT_CHAIN_POLICY_IGNORE_END_REV_UNKNOWN_FLAG or
    CERT_CHAIN_POLICY_IGNORE_CTL_SIGNER_REV_UNKNOWN_FLAG or
    CERT_CHAIN_POLICY_IGNORE_CA_REV_UNKNOWN_FLAG or
    CERT_CHAIN_POLICY_IGNORE_ROOT_REV_UNKNOWN_FLAG);
  {$EXTERNALSYM CERT_CHAIN_POLICY_IGNORE_ALL_REV_UNKNOWN_FLAGS}

  CERT_CHAIN_POLICY_ALLOW_TESTROOT_FLAG = $00008000;
  {$EXTERNALSYM CERT_CHAIN_POLICY_ALLOW_TESTROOT_FLAG}
  CERT_CHAIN_POLICY_TRUST_TESTROOT_FLAG = $00004000;
  {$EXTERNALSYM CERT_CHAIN_POLICY_TRUST_TESTROOT_FLAG}

//+-------------------------------------------------------------------------
//  Verify that the certificate chain satisfies the specified policy
//  requirements. If we were able to verify the chain policy, TRUE is returned
//  and the dwError field of the pPolicyStatus is updated. A dwError of 0
//  (ERROR_SUCCESS, S_OK) indicates the chain satisfies the specified policy.
//
//  If dwError applies to the entire chain context, both lChainIndex and
//  lElementIndex are set to -1. If dwError applies to a simple chain,
//  lElementIndex is set to -1 and lChainIndex is set to the index of the
//  first offending chain having the error. If dwError applies to a
//  certificate element, lChainIndex and lElementIndex are updated to
//  index the first offending certificate having the error, where, the
//  the certificate element is at:
//      pChainContext->rgpChain[lChainIndex]->rgpElement[lElementIndex].
//
//  The dwFlags in pPolicyPara can be set to change the default policy checking
//  behaviour. In addition, policy specific parameters can be passed in
//  the pvExtraPolicyPara field of pPolicyPara.
//
//  In addition to returning dwError, in pPolicyStatus, policy OID specific
//  extra status may be returned via pvExtraPolicyStatus.
//--------------------------------------------------------------------------

function CertVerifyCertificateChainPolicy(pszPolicyOID: LPCSTR;
  pChainContext: PCCERT_CHAIN_CONTEXT; pPolicyPara: PCERT_CHAIN_POLICY_PARA;
  pPolicyStatus: PCERT_CHAIN_POLICY_STATUS): BOOL; stdcall;
{$EXTERNALSYM CertVerifyCertificateChainPolicy}

// Predefined OID Function Names

const
  CRYPT_OID_VERIFY_CERTIFICATE_CHAIN_POLICY_FUNC = 'CertDllVerifyCertificateChainPolicy';
  {$EXTERNALSYM CRYPT_OID_VERIFY_CERTIFICATE_CHAIN_POLICY_FUNC}

// CertDllVerifyCertificateChainPolicy has same function signature as
// CertVerifyCertificateChainPolicy.

//+-------------------------------------------------------------------------
//  Predefined verify chain policies
//--------------------------------------------------------------------------

  CERT_CHAIN_POLICY_BASE              = LPCSTR(1);
  {$EXTERNALSYM CERT_CHAIN_POLICY_BASE}
  CERT_CHAIN_POLICY_AUTHENTICODE      = LPCSTR(2);
  {$EXTERNALSYM CERT_CHAIN_POLICY_AUTHENTICODE}
  CERT_CHAIN_POLICY_AUTHENTICODE_TS   = LPCSTR(3);
  {$EXTERNALSYM CERT_CHAIN_POLICY_AUTHENTICODE_TS}
  CERT_CHAIN_POLICY_SSL               = LPCSTR(4);
  {$EXTERNALSYM CERT_CHAIN_POLICY_SSL}
  CERT_CHAIN_POLICY_BASIC_CONSTRAINTS = LPCSTR(5);
  {$EXTERNALSYM CERT_CHAIN_POLICY_BASIC_CONSTRAINTS}
  CERT_CHAIN_POLICY_NT_AUTH           = LPCSTR(6);
  {$EXTERNALSYM CERT_CHAIN_POLICY_NT_AUTH}

//+-------------------------------------------------------------------------
//  CERT_CHAIN_POLICY_BASE
//
//  Implements the base chain policy verification checks. dwFlags can
//  be set in pPolicyPara to alter the default policy checking behaviour.
//--------------------------------------------------------------------------

//+-------------------------------------------------------------------------
//  CERT_CHAIN_POLICY_AUTHENTICODE
//
//  Implements the Authenticode chain policy verification checks.
//
//  pvExtraPolicyPara may optionally be set to point to the following
//  AUTHENTICODE_EXTRA_CERT_CHAIN_POLICY_PARA.
//
//  pvExtraPolicyStatus may optionally be set to point to the following
//  AUTHENTICODE_EXTRA_CERT_CHAIN_POLICY_STATUS.
//--------------------------------------------------------------------------

// dwRegPolicySettings are defined in wintrust.h

type
  PAUTHENTICODE_EXTRA_CERT_CHAIN_POLICY_PARA = ^AUTHENTICODE_EXTRA_CERT_CHAIN_POLICY_PARA;
  {$EXTERNALSYM PAUTHENTICODE_EXTRA_CERT_CHAIN_POLICY_PARA}
  _AUTHENTICODE_EXTRA_CERT_CHAIN_POLICY_PARA = record
    cbSize: DWORD;
    dwRegPolicySettings: DWORD;
    pSignerInfo: PCMSG_SIGNER_INFO; // optional
  end;
  {$EXTERNALSYM _AUTHENTICODE_EXTRA_CERT_CHAIN_POLICY_PARA}
  AUTHENTICODE_EXTRA_CERT_CHAIN_POLICY_PARA = _AUTHENTICODE_EXTRA_CERT_CHAIN_POLICY_PARA;
  {$EXTERNALSYM AUTHENTICODE_EXTRA_CERT_CHAIN_POLICY_PARA}
  TAuthenticodeExtraCertChainPolicyPara = AUTHENTICODE_EXTRA_CERT_CHAIN_POLICY_PARA;
  PAuthenticodeExtraCertChainPolicyPara = PAUTHENTICODE_EXTRA_CERT_CHAIN_POLICY_PARA;

  PAUTHENTICODE_EXTRA_CERT_CHAIN_POLICY_STATUS = ^AUTHENTICODE_EXTRA_CERT_CHAIN_POLICY_STATUS;
  {$EXTERNALSYM PAUTHENTICODE_EXTRA_CERT_CHAIN_POLICY_STATUS}
  _AUTHENTICODE_EXTRA_CERT_CHAIN_POLICY_STATUS = record
    cbSize: DWORD;
    fCommercial: BOOL; // obtained from signer statement
  end;
  {$EXTERNALSYM _AUTHENTICODE_EXTRA_CERT_CHAIN_POLICY_STATUS}
  AUTHENTICODE_EXTRA_CERT_CHAIN_POLICY_STATUS = _AUTHENTICODE_EXTRA_CERT_CHAIN_POLICY_STATUS;
  {$EXTERNALSYM AUTHENTICODE_EXTRA_CERT_CHAIN_POLICY_STATUS}
  TAuthenticodeExtraCertChainPolicyStatus = AUTHENTICODE_EXTRA_CERT_CHAIN_POLICY_STATUS;
  PAuthenticodeExtraCertChainPolicyStatus = PAUTHENTICODE_EXTRA_CERT_CHAIN_POLICY_STATUS;

//+-------------------------------------------------------------------------
//  CERT_CHAIN_POLICY_AUTHENTICODE_TS
//
//  Implements the Authenticode Time Stamp chain policy verification checks.
//
//  pvExtraPolicyPara may optionally be set to point to the following
//  AUTHENTICODE_TS_EXTRA_CERT_CHAIN_POLICY_PARA.
//
//  pvExtraPolicyStatus isn't used and must be set to NULL.
//--------------------------------------------------------------------------

// dwRegPolicySettings are defined in wintrust.h

  PAUTHENTICODE_TS_EXTRA_CERT_CHAIN_POLICY_PARA = ^AUTHENTICODE_TS_EXTRA_CERT_CHAIN_POLICY_PARA;
  {$EXTERNALSYM PAUTHENTICODE_TS_EXTRA_CERT_CHAIN_POLICY_PARA}
  _AUTHENTICODE_TS_EXTRA_CERT_CHAIN_POLICY_PARA = record
    cbSize: DWORD;
    dwRegPolicySettings: DWORD;
    fCommercial: BOOL;
  end;
  {$EXTERNALSYM _AUTHENTICODE_TS_EXTRA_CERT_CHAIN_POLICY_PARA}
  AUTHENTICODE_TS_EXTRA_CERT_CHAIN_POLICY_PARA = _AUTHENTICODE_TS_EXTRA_CERT_CHAIN_POLICY_PARA;
  {$EXTERNALSYM AUTHENTICODE_TS_EXTRA_CERT_CHAIN_POLICY_PARA}
  TAuthenticodeTsExtraCertChainPolicyPara = AUTHENTICODE_TS_EXTRA_CERT_CHAIN_POLICY_PARA;
  PAuthenticodeTsExtraCertChainPolicyPara = PAUTHENTICODE_TS_EXTRA_CERT_CHAIN_POLICY_PARA;

//+-------------------------------------------------------------------------
//  CERT_CHAIN_POLICY_SSL
//
//  Implements the SSL client/server chain policy verification checks.
//
//  pvExtraPolicyPara may optionally be set to point to the following
//  SSL_EXTRA_CERT_CHAIN_POLICY_PARA data structure
//--------------------------------------------------------------------------

// fdwChecks flags are defined in wininet.h

const
  AUTHTYPE_CLIENT = 1;
  {$EXTERNALSYM AUTHTYPE_CLIENT}
  AUTHTYPE_SERVER = 2;
  {$EXTERNALSYM AUTHTYPE_SERVER}

type
  PHTTPSPolicyCallbackData = ^HTTPSPolicyCallbackData;
  {$EXTERNALSYM PHTTPSPolicyCallbackData}
  _HTTPSPolicyCallbackData = record
    //union {
    //cbStruct: DWORD; // sizeof(HTTPSPolicyCallbackData);
    cbSize: DWORD; // sizeof(HTTPSPolicyCallbackData);
    //};
    dwAuthType: DWORD;
    fdwChecks: DWORD;
    pwszServerName: PWCHAR; // used to check against CN=xxxx
  end;
  {$EXTERNALSYM _HTTPSPolicyCallbackData}
  HTTPSPolicyCallbackData = _HTTPSPolicyCallbackData;
  {$EXTERNALSYM HTTPSPolicyCallbackData}
  THttpsPolicyCallbackData = HTTPSPolicyCallbackData;

  SSL_EXTRA_CERT_CHAIN_POLICY_PARA = HTTPSPolicyCallbackData;
  {$EXTERNALSYM SSL_EXTRA_CERT_CHAIN_POLICY_PARA}
  PSSL_EXTRA_CERT_CHAIN_POLICY_PARA = PHTTPSPolicyCallbackData;
  {$EXTERNALSYM PSSL_EXTRA_CERT_CHAIN_POLICY_PARA}
  TSSLExtraCertChainPolicyPara = SSL_EXTRA_CERT_CHAIN_POLICY_PARA;
  PSSLExtraCertChainPolicyPara = PSSL_EXTRA_CERT_CHAIN_POLICY_PARA;

//+-------------------------------------------------------------------------
//  CERT_CHAIN_POLICY_BASIC_CONSTRAINTS
//
//  Implements the basic constraints chain policy.
//
//  Iterates through all the certificates in the chain checking for either
//  a szOID_BASIC_CONSTRAINTS or a szOID_BASIC_CONSTRAINTS2 extension. If
//  neither extension is present, the certificate is assumed to have
//  valid policy. Otherwise, for the first certificate element, checks if
//  it matches the expected CA_FLAG or END_ENTITY_FLAG specified in
//  pPolicyPara->dwFlags. If neither or both flags are set, then, the first
//  element can be either a CA or END_ENTITY. All other elements must be
//  a CA. If the PathLenConstraint is present in the extension, its
//  checked.
//
//  The first elements in the remaining simple chains (ie, the certificate
//  used to sign the CTL) are checked to be an END_ENTITY.
//
//  If this verification fails, dwError will be set to
//  TRUST_E_BASIC_CONSTRAINTS.
//--------------------------------------------------------------------------

const
  BASIC_CONSTRAINTS_CERT_CHAIN_POLICY_CA_FLAG         = DWORD($80000000);
  {$EXTERNALSYM BASIC_CONSTRAINTS_CERT_CHAIN_POLICY_CA_FLAG}
  BASIC_CONSTRAINTS_CERT_CHAIN_POLICY_END_ENTITY_FLAG = $40000000;
  {$EXTERNALSYM BASIC_CONSTRAINTS_CERT_CHAIN_POLICY_END_ENTITY_FLAG}

//+-------------------------------------------------------------------------
//  CERT_CHAIN_POLICY_NT_AUTH
//
//  Implements the NT Authentication chain policy.
//
//  The NT Authentication chain policy consists of 3 distinct chain
//  verifications in the following order:
//      [1] CERT_CHAIN_POLICY_BASE - Implements the base chain policy
//          verification checks. The LOWORD of dwFlags can be set in
//          pPolicyPara to alter the default policy checking behaviour. See
//          CERT_CHAIN_POLICY_BASE for more details.
//
//      [2] CERT_CHAIN_POLICY_BASIC_CONSTRAINTS - Implements the basic
//          constraints chain policy. The HIWORD of dwFlags can be set
//          to specify if the first element must be either a CA or END_ENTITY.
//          See CERT_CHAIN_POLICY_BASIC_CONSTRAINTS for more details.
//
//      [3] Checks if the second element in the chain, the CA that issued
//          the end certificate, is a trusted CA for NT
//          Authentication. A CA is considered to be trusted if it exists in
//          the "NTAuth" system registry store found in the
//          CERT_SYSTEM_STORE_LOCAL_MACHINE_ENTERPRISE store location.
//          If this verification fails, whereby the CA isn't trusted,
//          dwError is set to CERT_E_UNTRUSTEDCA.
//--------------------------------------------------------------------------

implementation

function GET_ALG_CLASS(x: DWORD): DWORD;
begin
  Result := (x and (7 shl 13));
end;

function GET_ALG_TYPE(x: DWORD): DWORD;
begin
  Result := (x and (15 shl 9));
end;

function GET_ALG_SID(x: DWORD): DWORD;
begin
  Result := x and 511;
end;

function RCRYPT_SUCCEEDED(rt: BOOL): BOOL;
begin
  Result := (rt = CRYPT_SUCCEED);
end;

function RCRYPT_FAILED(rt: BOOL): BOOL;
begin
  Result := (rt = CRYPT_FAILED)
end;

function IS_CERT_RDN_CHAR_STRING(X: DWORD): Boolean;
begin
  Result := (X and CERT_RDN_TYPE_MASK) >= CERT_RDN_NUMERIC_STRING;
end;

function GET_CERT_ENCODING_TYPE(X: DWORD): DWORD;
begin
  Result := X and CERT_ENCODING_TYPE_MASK;
end;

function GET_CMSG_ENCODING_TYPE(X: DWORD): DWORD;
begin
  Result := X and CMSG_ENCODING_TYPE_MASK;
end;

function GET_CERT_UNICODE_RDN_ERR_INDEX(X: DWORD): DWORD;
begin
  Result := (X shr CERT_UNICODE_RDN_ERR_INDEX_SHIFT) and CERT_UNICODE_RDN_ERR_INDEX_MASK;
end;

function GET_CERT_UNICODE_ATTR_ERR_INDEX(X: DWORD): DWORD;
begin
  Result := (X shr CERT_UNICODE_ATTR_ERR_INDEX_SHIFT) and CERT_UNICODE_ATTR_ERR_INDEX_MASK;
end;

function GET_CERT_UNICODE_VALUE_ERR_INDEX(X: DWORD): DWORD;
begin
  Result := X and CERT_UNICODE_VALUE_ERR_INDEX_MASK;
end;

function GET_CERT_ALT_NAME_ENTRY_ERR_INDEX(X: DWORD): DWORD;
begin
  Result := (X shr CERT_ALT_NAME_ENTRY_ERR_INDEX_SHIFT) and CERT_ALT_NAME_ENTRY_ERR_INDEX_MASK;
end;

function GET_CERT_ALT_NAME_VALUE_ERR_INDEX(X: DWORD): DWORD;
begin
  Result := X and CERT_ALT_NAME_VALUE_ERR_INDEX_MASK;
end;

function IS_CRL_DIST_POINT_ERR_CRL_ISSUER(X: DWORD): Boolean;
begin
  Result := (X and CRL_DIST_POINT_ERR_CRL_ISSUER_BIT) <> 0;
end;

function GET_CRL_DIST_POINT_ERR_INDEX(X: DWORD): DWORD;
begin
  Result := ((X shr CRL_DIST_POINT_ERR_INDEX_SHIFT) and CRL_DIST_POINT_ERR_INDEX_MASK);
end;

function IS_CERT_HASH_PROP_ID(X: DWORD): Boolean;
begin
  Result := (CERT_SHA1_HASH_PROP_ID = X) or (CERT_MD5_HASH_PROP_ID = X) or
    (CERT_SIGNATURE_HASH_PROP_ID = X);
end;

const
  crypt32 = 'crypt32.dll';
  advapi32 = 'advapi32.dll';
  softpub = 'softpub.dll';


{$IFDEF DYNAMIC_LINK}
var
  _CryptAcquireContextA: Pointer;

function CryptAcquireContextA;
begin
  GetProcedureAddress(_CryptAcquireContextA, advapi32, 'CryptAcquireContextA');
  asm
    mov esp, ebp
    pop ebp
    jmp [_CryptAcquireContextA]
  end;
end;
{$ELSE}
function CryptAcquireContextA; external advapi32 name 'CryptAcquireContextA';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _CryptAcquireContextW: Pointer;

function CryptAcquireContextW;
begin
  GetProcedureAddress(_CryptAcquireContextW, advapi32, 'CryptAcquireContextW');
  asm
    mov esp, ebp
    pop ebp
    jmp [_CryptAcquireContextW]
  end;
end;
{$ELSE}
function CryptAcquireContextW; external advapi32 name 'CryptAcquireContextW';
{$ENDIF DYNAMIC_LINK}
{$IFDEF UNICODE}

{$IFDEF DYNAMIC_LINK}
var
  _CryptAcquireContext: Pointer;

function CryptAcquireContext;
begin
  GetProcedureAddress(_CryptAcquireContext, advapi32, 'CryptAcquireContextW');
  asm
    mov esp, ebp
    pop ebp
    jmp [_CryptAcquireContext]
  end;
end;
{$ELSE}
function CryptAcquireContext; external advapi32 name 'CryptAcquireContextW';
{$ENDIF DYNAMIC_LINK}
{$ELSE}

{$IFDEF DYNAMIC_LINK}
var
  _CryptAcquireContext: Pointer;

function CryptAcquireContext;
begin
  GetProcedureAddress(_CryptAcquireContext, advapi32, 'CryptAcquireContextA');
  asm
    mov esp, ebp
    pop ebp
    jmp [_CryptAcquireContext]
  end;
end;
{$ELSE}
function CryptAcquireContext; external advapi32 name 'CryptAcquireContextA';
{$ENDIF DYNAMIC_LINK}
{$ENDIF}

{$IFDEF DYNAMIC_LINK}
var
  _CryptReleaseContext: Pointer;

function CryptReleaseContext;
begin
  GetProcedureAddress(_CryptReleaseContext, advapi32, 'CryptReleaseContext');
  asm
    mov esp, ebp
    pop ebp
    jmp [_CryptReleaseContext]
  end;
end;
{$ELSE}
function CryptReleaseContext; external advapi32 name 'CryptReleaseContext';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _CryptGenKey: Pointer;

function CryptGenKey;
begin
  GetProcedureAddress(_CryptGenKey, advapi32, 'CryptGenKey');
  asm
    mov esp, ebp
    pop ebp
    jmp [_CryptGenKey]
  end;
end;
{$ELSE}
function CryptGenKey; external advapi32 name 'CryptGenKey';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _CryptDeriveKey: Pointer;

function CryptDeriveKey;
begin
  GetProcedureAddress(_CryptDeriveKey, advapi32, 'CryptDeriveKey');
  asm
    mov esp, ebp
    pop ebp
    jmp [_CryptDeriveKey]
  end;
end;
{$ELSE}
function CryptDeriveKey; external advapi32 name 'CryptDeriveKey';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _CryptDestroyKey: Pointer;

function CryptDestroyKey;
begin
  GetProcedureAddress(_CryptDestroyKey, advapi32, 'CryptDestroyKey');
  asm
    mov esp, ebp
    pop ebp
    jmp [_CryptDestroyKey]
  end;
end;
{$ELSE}
function CryptDestroyKey; external advapi32 name 'CryptDestroyKey';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _CryptSetKeyParam: Pointer;

function CryptSetKeyParam;
begin
  GetProcedureAddress(_CryptSetKeyParam, crypt32, 'CryptSetKeyParam');
  asm
    mov esp, ebp
    pop ebp
    jmp [_CryptSetKeyParam]
  end;
end;
{$ELSE}
function CryptSetKeyParam; external crypt32 name 'CryptSetKeyParam';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _CryptGetKeyParam: Pointer;

function CryptGetKeyParam;
begin
  GetProcedureAddress(_CryptGetKeyParam, advapi32, 'CryptGetKeyParam');
  asm
    mov esp, ebp
    pop ebp
    jmp [_CryptGetKeyParam]
  end;
end;
{$ELSE}
function CryptGetKeyParam; external advapi32 name 'CryptGetKeyParam';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _CryptSetHashParam: Pointer;

function CryptSetHashParam;
begin
  GetProcedureAddress(_CryptSetHashParam, advapi32, 'CryptSetHashParam');
  asm
    mov esp, ebp
    pop ebp
    jmp [_CryptSetHashParam]
  end;
end;
{$ELSE}
function CryptSetHashParam; external advapi32 name 'CryptSetHashParam';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _CryptGetHashParam: Pointer;

function CryptGetHashParam;
begin
  GetProcedureAddress(_CryptGetHashParam, advapi32, 'CryptGetHashParam');
  asm
    mov esp, ebp
    pop ebp
    jmp [_CryptGetHashParam]
  end;
end;
{$ELSE}
function CryptGetHashParam; external advapi32 name 'CryptGetHashParam';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _CryptSetProvParam: Pointer;

function CryptSetProvParam;
begin
  GetProcedureAddress(_CryptSetProvParam, advapi32, 'CryptSetProvParam');
  asm
    mov esp, ebp
    pop ebp
    jmp [_CryptSetProvParam]
  end;
end;
{$ELSE}
function CryptSetProvParam; external advapi32 name 'CryptSetProvParam';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _CryptGetProvParam: Pointer;

function CryptGetProvParam;
begin
  GetProcedureAddress(_CryptGetProvParam, advapi32, 'CryptGetProvParam');
  asm
    mov esp, ebp
    pop ebp
    jmp [_CryptGetProvParam]
  end;
end;
{$ELSE}
function CryptGetProvParam; external advapi32 name 'CryptGetProvParam';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _CryptGenRandom: Pointer;

function CryptGenRandom;
begin
  GetProcedureAddress(_CryptGenRandom, advapi32, 'CryptGenRandom');
  asm
    mov esp, ebp
    pop ebp
    jmp [_CryptGenRandom]
  end;
end;
{$ELSE}
function CryptGenRandom; external advapi32 name 'CryptGenRandom';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _CryptGetUserKey: Pointer;

function CryptGetUserKey;
begin
  GetProcedureAddress(_CryptGetUserKey, advapi32, 'CryptGetUserKey');
  asm
    mov esp, ebp
    pop ebp
    jmp [_CryptGetUserKey]
  end;
end;
{$ELSE}
function CryptGetUserKey; external advapi32 name 'CryptGetUserKey';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _CryptExportKey: Pointer;

function CryptExportKey;
begin
  GetProcedureAddress(_CryptExportKey, advapi32, 'CryptExportKey');
  asm
    mov esp, ebp
    pop ebp
    jmp [_CryptExportKey]
  end;
end;
{$ELSE}
function CryptExportKey; external advapi32 name 'CryptExportKey';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _CryptImportKey: Pointer;

function CryptImportKey;
begin
  GetProcedureAddress(_CryptImportKey, advapi32, 'CryptImportKey');
  asm
    mov esp, ebp
    pop ebp
    jmp [_CryptImportKey]
  end;
end;
{$ELSE}
function CryptImportKey; external advapi32 name 'CryptImportKey';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _CryptEncrypt: Pointer;

function CryptEncrypt;
begin
  GetProcedureAddress(_CryptEncrypt, advapi32, 'CryptEncrypt');
  asm
    mov esp, ebp
    pop ebp
    jmp [_CryptEncrypt]
  end;
end;
{$ELSE}
function CryptEncrypt; external advapi32 name 'CryptEncrypt';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _CryptDecrypt: Pointer;

function CryptDecrypt;
begin
  GetProcedureAddress(_CryptDecrypt, advapi32, 'CryptDecrypt');
  asm
    mov esp, ebp
    pop ebp
    jmp [_CryptDecrypt]
  end;
end;
{$ELSE}
function CryptDecrypt; external advapi32 name 'CryptDecrypt';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _CryptCreateHash: Pointer;

function CryptCreateHash;
begin
  GetProcedureAddress(_CryptCreateHash, advapi32, 'CryptCreateHash');
  asm
    mov esp, ebp
    pop ebp
    jmp [_CryptCreateHash]
  end;
end;
{$ELSE}
function CryptCreateHash; external advapi32 name 'CryptCreateHash';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _CryptHashData: Pointer;

function CryptHashData;
begin
  GetProcedureAddress(_CryptHashData, advapi32, 'CryptHashData');
  asm
    mov esp, ebp
    pop ebp
    jmp [_CryptHashData]
  end;
end;
{$ELSE}
function CryptHashData; external advapi32 name 'CryptHashData';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _CryptHashSessionKey: Pointer;

function CryptHashSessionKey;
begin
  GetProcedureAddress(_CryptHashSessionKey, advapi32, 'CryptHashSessionKey');
  asm
    mov esp, ebp
    pop ebp
    jmp [_CryptHashSessionKey]
  end;
end;
{$ELSE}
function CryptHashSessionKey; external advapi32 name 'CryptHashSessionKey';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _CryptDestroyHash: Pointer;

function CryptDestroyHash;
begin
  GetProcedureAddress(_CryptDestroyHash, advapi32, 'CryptDestroyHash');
  asm
    mov esp, ebp
    pop ebp
    jmp [_CryptDestroyHash]
  end;
end;
{$ELSE}
function CryptDestroyHash; external advapi32 name 'CryptDestroyHash';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _CryptSignHashA: Pointer;

function CryptSignHashA;
begin
  GetProcedureAddress(_CryptSignHashA, advapi32, 'CryptSignHashA');
  asm
    mov esp, ebp
    pop ebp
    jmp [_CryptSignHashA]
  end;
end;
{$ELSE}
function CryptSignHashA; external advapi32 name 'CryptSignHashA';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _CryptSignHashW: Pointer;

function CryptSignHashW;
begin
  GetProcedureAddress(_CryptSignHashW, advapi32, 'CryptSignHashW');
  asm
    mov esp, ebp
    pop ebp
    jmp [_CryptSignHashW]
  end;
end;
{$ELSE}
function CryptSignHashW; external advapi32 name 'CryptSignHashW';
{$ENDIF DYNAMIC_LINK}
{$IFDEF UNICODE}

{$IFDEF DYNAMIC_LINK}
var
  _CryptSignHash: Pointer;

function CryptSignHash;
begin
  GetProcedureAddress(_CryptSignHash, advapi32, 'CryptSignHashW');
  asm
    mov esp, ebp
    pop ebp
    jmp [_CryptSignHash]
  end;
end;
{$ELSE}
function CryptSignHash; external advapi32 name 'CryptSignHashW';
{$ENDIF DYNAMIC_LINK}
{$ELSE}

{$IFDEF DYNAMIC_LINK}
var
  _CryptSignHash: Pointer;

function CryptSignHash;
begin
  GetProcedureAddress(_CryptSignHash, advapi32, 'CryptSignHashA');
  asm
    mov esp, ebp
    pop ebp
    jmp [_CryptSignHash]
  end;
end;
{$ELSE}
function CryptSignHash; external advapi32 name 'CryptSignHashA';
{$ENDIF DYNAMIC_LINK}
{$ENDIF}

{$IFDEF DYNAMIC_LINK}
var
  _CryptVerifySignatureA: Pointer;

function CryptVerifySignatureA;
begin
  GetProcedureAddress(_CryptVerifySignatureA, advapi32, 'CryptVerifySignatureA');
  asm
    mov esp, ebp
    pop ebp
    jmp [_CryptVerifySignatureA]
  end;
end;
{$ELSE}
function CryptVerifySignatureA; external advapi32 name 'CryptVerifySignatureA';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _CryptVerifySignatureW: Pointer;

function CryptVerifySignatureW;
begin
  GetProcedureAddress(_CryptVerifySignatureW, advapi32, 'CryptVerifySignatureW');
  asm
    mov esp, ebp
    pop ebp
    jmp [_CryptVerifySignatureW]
  end;
end;
{$ELSE}
function CryptVerifySignatureW; external advapi32 name 'CryptVerifySignatureW';
{$ENDIF DYNAMIC_LINK}
{$IFDEF UNICODE}

{$IFDEF DYNAMIC_LINK}
var
  _CryptVerifySignature: Pointer;

function CryptVerifySignature;
begin
  GetProcedureAddress(_CryptVerifySignature, advapi32, 'CryptVerifySignatureW');
  asm
    mov esp, ebp
    pop ebp
    jmp [_CryptVerifySignature]
  end;
end;
{$ELSE}
function CryptVerifySignature; external advapi32 name 'CryptVerifySignatureW';
{$ENDIF DYNAMIC_LINK}
{$ELSE}

{$IFDEF DYNAMIC_LINK}
var
  _CryptVerifySignature: Pointer;

function CryptVerifySignature;
begin
  GetProcedureAddress(_CryptVerifySignature, advapi32, 'CryptVerifySignatureA');
  asm
    mov esp, ebp
    pop ebp
    jmp [_CryptVerifySignature]
  end;
end;
{$ELSE}
function CryptVerifySignature; external advapi32 name 'CryptVerifySignatureA';
{$ENDIF DYNAMIC_LINK}
{$ENDIF}

{$IFDEF DYNAMIC_LINK}
var
  _CryptSetProviderA: Pointer;

function CryptSetProviderA;
begin
  GetProcedureAddress(_CryptSetProviderA, advapi32, 'CryptSetProviderA');
  asm
    mov esp, ebp
    pop ebp
    jmp [_CryptSetProviderA]
  end;
end;
{$ELSE}
function CryptSetProviderA; external advapi32 name 'CryptSetProviderA';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _CryptSetProviderW: Pointer;

function CryptSetProviderW;
begin
  GetProcedureAddress(_CryptSetProviderW, advapi32, 'CryptSetProviderW');
  asm
    mov esp, ebp
    pop ebp
    jmp [_CryptSetProviderW]
  end;
end;
{$ELSE}
function CryptSetProviderW; external advapi32 name 'CryptSetProviderW';
{$ENDIF DYNAMIC_LINK}
{$IFDEF UNICODE}

{$IFDEF DYNAMIC_LINK}
var
  _CryptSetProvider: Pointer;

function CryptSetProvider;
begin
  GetProcedureAddress(_CryptSetProvider, advapi32, 'CryptSetProviderW');
  asm
    mov esp, ebp
    pop ebp
    jmp [_CryptSetProvider]
  end;
end;
{$ELSE}
function CryptSetProvider; external advapi32 name 'CryptSetProviderW';
{$ENDIF DYNAMIC_LINK}
{$ELSE}

{$IFDEF DYNAMIC_LINK}
var
  _CryptSetProvider: Pointer;

function CryptSetProvider;
begin
  GetProcedureAddress(_CryptSetProvider, advapi32, 'CryptSetProviderA');
  asm
    mov esp, ebp
    pop ebp
    jmp [_CryptSetProvider]
  end;
end;
{$ELSE}
function CryptSetProvider; external advapi32 name 'CryptSetProviderA';
{$ENDIF DYNAMIC_LINK}
{$ENDIF}

{$IFDEF DYNAMIC_LINK}
var
  _CryptSetProviderExA: Pointer;

function CryptSetProviderExA;
begin
  GetProcedureAddress(_CryptSetProviderExA, advapi32, 'CryptSetProviderExA');
  asm
    mov esp, ebp
    pop ebp
    jmp [_CryptSetProviderExA]
  end;
end;
{$ELSE}
function CryptSetProviderExA; external advapi32 name 'CryptSetProviderExA';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _CryptSetProviderExW: Pointer;

function CryptSetProviderExW;
begin
  GetProcedureAddress(_CryptSetProviderExW, advapi32, 'CryptSetProviderExW');
  asm
    mov esp, ebp
    pop ebp
    jmp [_CryptSetProviderExW]
  end;
end;
{$ELSE}
function CryptSetProviderExW; external advapi32 name 'CryptSetProviderExW';
{$ENDIF DYNAMIC_LINK}
{$IFDEF UNICODE}

{$IFDEF DYNAMIC_LINK}
var
  _CryptSetProviderEx: Pointer;

function CryptSetProviderEx;
begin
  GetProcedureAddress(_CryptSetProviderEx, advapi32, 'CryptSetProviderExW');
  asm
    mov esp, ebp
    pop ebp
    jmp [_CryptSetProviderEx]
  end;
end;
{$ELSE}
function CryptSetProviderEx; external advapi32 name 'CryptSetProviderExW';
{$ENDIF DYNAMIC_LINK}
{$ELSE}

{$IFDEF DYNAMIC_LINK}
var
  _CryptSetProviderEx: Pointer;

function CryptSetProviderEx;
begin
  GetProcedureAddress(_CryptSetProviderEx, advapi32, 'CryptSetProviderExA');
  asm
    mov esp, ebp
    pop ebp
    jmp [_CryptSetProviderEx]
  end;
end;
{$ELSE}
function CryptSetProviderEx; external advapi32 name 'CryptSetProviderExA';
{$ENDIF DYNAMIC_LINK}
{$ENDIF}

{$IFDEF DYNAMIC_LINK}
var
  _CryptGetDefaultProviderA: Pointer;

function CryptGetDefaultProviderA;
begin
  GetProcedureAddress(_CryptGetDefaultProviderA, advapi32, 'CryptGetDefaultProviderA');
  asm
    mov esp, ebp
    pop ebp
    jmp [_CryptGetDefaultProviderA]
  end;
end;
{$ELSE}
function CryptGetDefaultProviderA; external advapi32 name 'CryptGetDefaultProviderA';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _CryptGetDefaultProviderW: Pointer;

function CryptGetDefaultProviderW;
begin
  GetProcedureAddress(_CryptGetDefaultProviderW, advapi32, 'CryptGetDefaultProviderW');
  asm
    mov esp, ebp
    pop ebp
    jmp [_CryptGetDefaultProviderW]
  end;
end;
{$ELSE}
function CryptGetDefaultProviderW; external advapi32 name 'CryptGetDefaultProviderW';
{$ENDIF DYNAMIC_LINK}
{$IFDEF UNICODE}

{$IFDEF DYNAMIC_LINK}
var
  _CryptGetDefaultProvider: Pointer;

function CryptGetDefaultProvider;
begin
  GetProcedureAddress(_CryptGetDefaultProvider, advapi32, 'CryptGetDefaultProviderW');
  asm
    mov esp, ebp
    pop ebp
    jmp [_CryptGetDefaultProvider]
  end;
end;
{$ELSE}
function CryptGetDefaultProvider; external advapi32 name 'CryptGetDefaultProviderW';
{$ENDIF DYNAMIC_LINK}
{$ELSE}

{$IFDEF DYNAMIC_LINK}
var
  _CryptGetDefaultProvider: Pointer;

function CryptGetDefaultProvider;
begin
  GetProcedureAddress(_CryptGetDefaultProvider, advapi32, 'CryptGetDefaultProviderA');
  asm
    mov esp, ebp
    pop ebp
    jmp [_CryptGetDefaultProvider]
  end;
end;
{$ELSE}
function CryptGetDefaultProvider; external advapi32 name 'CryptGetDefaultProviderA';
{$ENDIF DYNAMIC_LINK}
{$ENDIF}

{$IFDEF DYNAMIC_LINK}
var
  _CryptEnumProviderTypesA: Pointer;

function CryptEnumProviderTypesA;
begin
  GetProcedureAddress(_CryptEnumProviderTypesA, advapi32, 'CryptEnumProviderTypesA');
  asm
    mov esp, ebp
    pop ebp
    jmp [_CryptEnumProviderTypesA]
  end;
end;
{$ELSE}
function CryptEnumProviderTypesA; external advapi32 name 'CryptEnumProviderTypesA';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _CryptEnumProviderTypesW: Pointer;

function CryptEnumProviderTypesW;
begin
  GetProcedureAddress(_CryptEnumProviderTypesW, advapi32, 'CryptEnumProviderTypesW');
  asm
    mov esp, ebp
    pop ebp
    jmp [_CryptEnumProviderTypesW]
  end;
end;
{$ELSE}
function CryptEnumProviderTypesW; external advapi32 name 'CryptEnumProviderTypesW';
{$ENDIF DYNAMIC_LINK}
{$IFDEF UNICODE}

{$IFDEF DYNAMIC_LINK}
var
  _CryptEnumProviderTypes: Pointer;

function CryptEnumProviderTypes;
begin
  GetProcedureAddress(_CryptEnumProviderTypes, advapi32, 'CryptEnumProviderTypesW');
  asm
    mov esp, ebp
    pop ebp
    jmp [_CryptEnumProviderTypes]
  end;
end;
{$ELSE}
function CryptEnumProviderTypes; external advapi32 name 'CryptEnumProviderTypesW';
{$ENDIF DYNAMIC_LINK}
{$ELSE}

{$IFDEF DYNAMIC_LINK}
var
  _CryptEnumProviderTypes: Pointer;

function CryptEnumProviderTypes;
begin
  GetProcedureAddress(_CryptEnumProviderTypes, advapi32, 'CryptEnumProviderTypesA');
  asm
    mov esp, ebp
    pop ebp
    jmp [_CryptEnumProviderTypes]
  end;
end;
{$ELSE}
function CryptEnumProviderTypes; external advapi32 name 'CryptEnumProviderTypesA';
{$ENDIF DYNAMIC_LINK}
{$ENDIF}

{$IFDEF DYNAMIC_LINK}
var
  _CryptEnumProvidersA: Pointer;

function CryptEnumProvidersA;
begin
  GetProcedureAddress(_CryptEnumProvidersA, advapi32, 'CryptEnumProvidersA');
  asm
    mov esp, ebp
    pop ebp
    jmp [_CryptEnumProvidersA]
  end;
end;
{$ELSE}
function CryptEnumProvidersA; external advapi32 name 'CryptEnumProvidersA';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _CryptEnumProvidersW: Pointer;

function CryptEnumProvidersW;
begin
  GetProcedureAddress(_CryptEnumProvidersW, advapi32, 'CryptEnumProvidersW');
  asm
    mov esp, ebp
    pop ebp
    jmp [_CryptEnumProvidersW]
  end;
end;
{$ELSE}
function CryptEnumProvidersW; external advapi32 name 'CryptEnumProvidersW';
{$ENDIF DYNAMIC_LINK}
{$IFDEF UNICODE}

{$IFDEF DYNAMIC_LINK}
var
  _CryptEnumProviders: Pointer;

function CryptEnumProviders;
begin
  GetProcedureAddress(_CryptEnumProviders, advapi32, 'CryptEnumProvidersW');
  asm
    mov esp, ebp
    pop ebp
    jmp [_CryptEnumProviders]
  end;
end;
{$ELSE}
function CryptEnumProviders; external advapi32 name 'CryptEnumProvidersW';
{$ENDIF DYNAMIC_LINK}
{$ELSE}

{$IFDEF DYNAMIC_LINK}
var
  _CryptEnumProviders: Pointer;

function CryptEnumProviders;
begin
  GetProcedureAddress(_CryptEnumProviders, advapi32, 'CryptEnumProvidersA');
  asm
    mov esp, ebp
    pop ebp
    jmp [_CryptEnumProviders]
  end;
end;
{$ELSE}
function CryptEnumProviders; external advapi32 name 'CryptEnumProvidersA';
{$ENDIF DYNAMIC_LINK}
{$ENDIF}

{$IFDEF DYNAMIC_LINK}
var
  _CryptContextAddRef: Pointer;

function CryptContextAddRef;
begin
  GetProcedureAddress(_CryptContextAddRef, advapi32, 'CryptContextAddRef');
  asm
    mov esp, ebp
    pop ebp
    jmp [_CryptContextAddRef]
  end;
end;
{$ELSE}
function CryptContextAddRef; external advapi32 name 'CryptContextAddRef';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _CryptDuplicateKey: Pointer;

function CryptDuplicateKey;
begin
  GetProcedureAddress(_CryptDuplicateKey, advapi32, 'CryptDuplicateKey');
  asm
    mov esp, ebp
    pop ebp
    jmp [_CryptDuplicateKey]
  end;
end;
{$ELSE}
function CryptDuplicateKey; external advapi32 name 'CryptDuplicateKey';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _CryptDuplicateHash: Pointer;

function CryptDuplicateHash;
begin
  GetProcedureAddress(_CryptDuplicateHash, advapi32, 'CryptDuplicateHash');
  asm
    mov esp, ebp
    pop ebp
    jmp [_CryptDuplicateHash]
  end;
end;
{$ELSE}
function CryptDuplicateHash; external advapi32 name 'CryptDuplicateHash';
{$ENDIF DYNAMIC_LINK}


{$IFDEF DYNAMIC_LINK}
var
  _CryptFormatObject: Pointer;

function CryptFormatObject;
begin
  GetProcedureAddress(_CryptFormatObject, crypt32, 'CryptFormatObject');
  asm
    mov esp, ebp
    pop ebp
    jmp [_CryptFormatObject]
  end;
end;
{$ELSE}
function CryptFormatObject; external crypt32 name 'CryptFormatObject';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _CryptEncodeObjectEx: Pointer;

function CryptEncodeObjectEx;
begin
  GetProcedureAddress(_CryptEncodeObjectEx, crypt32, 'CryptEncodeObjectEx');
  asm
    mov esp, ebp
    pop ebp
    jmp [_CryptEncodeObjectEx]
  end;
end;
{$ELSE}
function CryptEncodeObjectEx; external crypt32 name 'CryptEncodeObjectEx';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _CryptEncodeObject: Pointer;

function CryptEncodeObject;
begin
  GetProcedureAddress(_CryptEncodeObject, crypt32, 'CryptEncodeObject');
  asm
    mov esp, ebp
    pop ebp
    jmp [_CryptEncodeObject]
  end;
end;
{$ELSE}
function CryptEncodeObject; external crypt32 name 'CryptEncodeObject';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _CryptDecodeObjectEx: Pointer;

function CryptDecodeObjectEx;
begin
  GetProcedureAddress(_CryptDecodeObjectEx, crypt32, 'CryptDecodeObjectEx');
  asm
    mov esp, ebp
    pop ebp
    jmp [_CryptDecodeObjectEx]
  end;
end;
{$ELSE}
function CryptDecodeObjectEx; external crypt32 name 'CryptDecodeObjectEx';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _CryptDecodeObject: Pointer;

function CryptDecodeObject;
begin
  GetProcedureAddress(_CryptDecodeObject, crypt32, 'CryptDecodeObject');
  asm
    mov esp, ebp
    pop ebp
    jmp [_CryptDecodeObject]
  end;
end;
{$ELSE}
function CryptDecodeObject; external crypt32 name 'CryptDecodeObject';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _CryptInstallOIDFunctionAddress: Pointer;

function CryptInstallOIDFunctionAddress;
begin
  GetProcedureAddress(_CryptInstallOIDFunctionAddress, crypt32, 'CryptInstallOIDFunctionAddress');
  asm
    mov esp, ebp
    pop ebp
    jmp [_CryptInstallOIDFunctionAddress]
  end;
end;
{$ELSE}
function CryptInstallOIDFunctionAddress; external crypt32 name 'CryptInstallOIDFunctionAddress';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _CryptInitOIDFunctionSet: Pointer;

function CryptInitOIDFunctionSet;
begin
  GetProcedureAddress(_CryptInitOIDFunctionSet, crypt32, 'CryptInitOIDFunctionSet');
  asm
    mov esp, ebp
    pop ebp
    jmp [_CryptInitOIDFunctionSet]
  end;
end;
{$ELSE}
function CryptInitOIDFunctionSet; external crypt32 name 'CryptInitOIDFunctionSet';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _CryptGetOIDFunctionAddress: Pointer;

function CryptGetOIDFunctionAddress;
begin
  GetProcedureAddress(_CryptGetOIDFunctionAddress, crypt32, 'CryptGetOIDFunctionAddress');
  asm
    mov esp, ebp
    pop ebp
    jmp [_CryptGetOIDFunctionAddress]
  end;
end;
{$ELSE}
function CryptGetOIDFunctionAddress; external crypt32 name 'CryptGetOIDFunctionAddress';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _CryptGetDefaultOIDDllList: Pointer;

function CryptGetDefaultOIDDllList;
begin
  GetProcedureAddress(_CryptGetDefaultOIDDllList, crypt32, 'CryptGetDefaultOIDDllList');
  asm
    mov esp, ebp
    pop ebp
    jmp [_CryptGetDefaultOIDDllList]
  end;
end;
{$ELSE}
function CryptGetDefaultOIDDllList; external crypt32 name 'CryptGetDefaultOIDDllList';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _CryptGetDefaultOIDFunctionAddr: Pointer;

function CryptGetDefaultOIDFunctionAddress;
begin
  GetProcedureAddress(_CryptGetDefaultOIDFunctionAddr, crypt32, 'CryptGetDefaultOIDFunctionAddress');
  asm
    mov esp, ebp
    pop ebp
    jmp [_CryptGetDefaultOIDFunctionAddr]
  end;
end;
{$ELSE}
function CryptGetDefaultOIDFunctionAddress; external crypt32 name 'CryptGetDefaultOIDFunctionAddress';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _CryptFreeOIDFunctionAddress: Pointer;

function CryptFreeOIDFunctionAddress;
begin
  GetProcedureAddress(_CryptFreeOIDFunctionAddress, crypt32, 'CryptFreeOIDFunctionAddress');
  asm
    mov esp, ebp
    pop ebp
    jmp [_CryptFreeOIDFunctionAddress]
  end;
end;
{$ELSE}
function CryptFreeOIDFunctionAddress; external crypt32 name 'CryptFreeOIDFunctionAddress';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _CryptRegisterOIDFunction: Pointer;

function CryptRegisterOIDFunction;
begin
  GetProcedureAddress(_CryptRegisterOIDFunction, crypt32, 'CryptRegisterOIDFunction');
  asm
    mov esp, ebp
    pop ebp
    jmp [_CryptRegisterOIDFunction]
  end;
end;
{$ELSE}
function CryptRegisterOIDFunction; external crypt32 name 'CryptRegisterOIDFunction';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _CryptUnregisterOIDFunction: Pointer;

function CryptUnregisterOIDFunction;
begin
  GetProcedureAddress(_CryptUnregisterOIDFunction, crypt32, 'CryptUnregisterOIDFunction');
  asm
    mov esp, ebp
    pop ebp
    jmp [_CryptUnregisterOIDFunction]
  end;
end;
{$ELSE}
function CryptUnregisterOIDFunction; external crypt32 name 'CryptUnregisterOIDFunction';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _CryptRegisterDefaultOIDFunction: Pointer;

function CryptRegisterDefaultOIDFunction;
begin
  GetProcedureAddress(_CryptRegisterDefaultOIDFunction, crypt32, 'CryptRegisterDefaultOIDFunction');
  asm
    mov esp, ebp
    pop ebp
    jmp [_CryptRegisterDefaultOIDFunction]
  end;
end;
{$ELSE}
function CryptRegisterDefaultOIDFunction; external crypt32 name 'CryptRegisterDefaultOIDFunction';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _CryptUnregisterDefaultOIDFunc: Pointer;

function CryptUnregisterDefaultOIDFunction;
begin
  GetProcedureAddress(_CryptUnregisterDefaultOIDFunc, crypt32, 'CryptUnregisterDefaultOIDFunction');
  asm
    mov esp, ebp
    pop ebp
    jmp [_CryptUnregisterDefaultOIDFunc]
  end;
end;
{$ELSE}
function CryptUnregisterDefaultOIDFunction; external crypt32 name 'CryptUnregisterDefaultOIDFunction';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _CryptSetOIDFunctionValue: Pointer;

function CryptSetOIDFunctionValue;
begin
  GetProcedureAddress(_CryptSetOIDFunctionValue, crypt32, 'CryptSetOIDFunctionValue');
  asm
    mov esp, ebp
    pop ebp
    jmp [_CryptSetOIDFunctionValue]
  end;
end;
{$ELSE}
function CryptSetOIDFunctionValue; external crypt32 name 'CryptSetOIDFunctionValue';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _CryptGetOIDFunctionValue: Pointer;

function CryptGetOIDFunctionValue;
begin
  GetProcedureAddress(_CryptGetOIDFunctionValue, crypt32, 'CryptGetOIDFunctionValue');
  asm
    mov esp, ebp
    pop ebp
    jmp [_CryptGetOIDFunctionValue]
  end;
end;
{$ELSE}
function CryptGetOIDFunctionValue; external crypt32 name 'CryptGetOIDFunctionValue';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _CryptEnumOIDFunction: Pointer;

function CryptEnumOIDFunction;
begin
  GetProcedureAddress(_CryptEnumOIDFunction, crypt32, 'CryptEnumOIDFunction');
  asm
    mov esp, ebp
    pop ebp
    jmp [_CryptEnumOIDFunction]
  end;
end;
{$ELSE}
function CryptEnumOIDFunction; external crypt32 name 'CryptEnumOIDFunction';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _CryptFindOIDInfo: Pointer;

function CryptFindOIDInfo;
begin
  GetProcedureAddress(_CryptFindOIDInfo, crypt32, 'CryptFindOIDInfo');
  asm
    mov esp, ebp
    pop ebp
    jmp [_CryptFindOIDInfo]
  end;
end;
{$ELSE}
function CryptFindOIDInfo; external crypt32 name 'CryptFindOIDInfo';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _CryptRegisterOIDInfo: Pointer;

function CryptRegisterOIDInfo;
begin
  GetProcedureAddress(_CryptRegisterOIDInfo, crypt32, 'CryptRegisterOIDInfo');
  asm
    mov esp, ebp
    pop ebp
    jmp [_CryptRegisterOIDInfo]
  end;
end;
{$ELSE}
function CryptRegisterOIDInfo; external crypt32 name 'CryptRegisterOIDInfo';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _CryptUnregisterOIDInfo: Pointer;

function CryptUnregisterOIDInfo;
begin
  GetProcedureAddress(_CryptUnregisterOIDInfo, crypt32, 'CryptUnregisterOIDInfo');
  asm
    mov esp, ebp
    pop ebp
    jmp [_CryptUnregisterOIDInfo]
  end;
end;
{$ELSE}
function CryptUnregisterOIDInfo; external crypt32 name 'CryptUnregisterOIDInfo';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _CryptEnumOIDInfo: Pointer;

function CryptEnumOIDInfo;
begin
  GetProcedureAddress(_CryptEnumOIDInfo, crypt32, 'CryptEnumOIDInfo');
  asm
    mov esp, ebp
    pop ebp
    jmp [_CryptEnumOIDInfo]
  end;
end;
{$ELSE}
function CryptEnumOIDInfo; external crypt32 name 'CryptEnumOIDInfo';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _CryptFindLocalizedName: Pointer;

function CryptFindLocalizedName;
begin
  GetProcedureAddress(_CryptFindLocalizedName, crypt32, 'CryptFindLocalizedName');
  asm
    mov esp, ebp
    pop ebp
    jmp [_CryptFindLocalizedName]
  end;
end;
{$ELSE}
function CryptFindLocalizedName; external crypt32 name 'CryptFindLocalizedName';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _CryptMsgOpenToEncode: Pointer;

function CryptMsgOpenToEncode;
begin
  GetProcedureAddress(_CryptMsgOpenToEncode, crypt32, 'CryptMsgOpenToEncode');
  asm
    mov esp, ebp
    pop ebp
    jmp [_CryptMsgOpenToEncode]
  end;
end;
{$ELSE}
function CryptMsgOpenToEncode; external crypt32 name 'CryptMsgOpenToEncode';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _CryptMsgCalculateEncodedLength: Pointer;

function CryptMsgCalculateEncodedLength;
begin
  GetProcedureAddress(_CryptMsgCalculateEncodedLength, crypt32, 'CryptMsgCalculateEncodedLength');
  asm
    mov esp, ebp
    pop ebp
    jmp [_CryptMsgCalculateEncodedLength]
  end;
end;
{$ELSE}
function CryptMsgCalculateEncodedLength; external crypt32 name 'CryptMsgCalculateEncodedLength';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _CryptMsgOpenToDecode: Pointer;

function CryptMsgOpenToDecode;
begin
  GetProcedureAddress(_CryptMsgOpenToDecode, crypt32, 'CryptMsgOpenToDecode');
  asm
    mov esp, ebp
    pop ebp
    jmp [_CryptMsgOpenToDecode]
  end;
end;
{$ELSE}
function CryptMsgOpenToDecode; external crypt32 name 'CryptMsgOpenToDecode';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _CryptMsgDuplicate: Pointer;

function CryptMsgDuplicate;
begin
  GetProcedureAddress(_CryptMsgDuplicate, crypt32, 'CryptMsgDuplicate');
  asm
    mov esp, ebp
    pop ebp
    jmp [_CryptMsgDuplicate]
  end;
end;
{$ELSE}
function CryptMsgDuplicate; external crypt32 name 'CryptMsgDuplicate';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _CryptMsgClose: Pointer;

function CryptMsgClose;
begin
  GetProcedureAddress(_CryptMsgClose, crypt32, 'CryptMsgClose');
  asm
    mov esp, ebp
    pop ebp
    jmp [_CryptMsgClose]
  end;
end;
{$ELSE}
function CryptMsgClose; external crypt32 name 'CryptMsgClose';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _CryptMsgUpdate: Pointer;

function CryptMsgUpdate;
begin
  GetProcedureAddress(_CryptMsgUpdate, crypt32, 'CryptMsgUpdate');
  asm
    mov esp, ebp
    pop ebp
    jmp [_CryptMsgUpdate]
  end;
end;
{$ELSE}
function CryptMsgUpdate; external crypt32 name 'CryptMsgUpdate';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _CryptMsgGetParam: Pointer;

function CryptMsgGetParam;
begin
  GetProcedureAddress(_CryptMsgGetParam, crypt32, 'CryptMsgGetParam');
  asm
    mov esp, ebp
    pop ebp
    jmp [_CryptMsgGetParam]
  end;
end;
{$ELSE}
function CryptMsgGetParam; external crypt32 name 'CryptMsgGetParam';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _CryptMsgControl: Pointer;

function CryptMsgControl;
begin
  GetProcedureAddress(_CryptMsgControl, crypt32, 'CryptMsgControl');
  asm
    mov esp, ebp
    pop ebp
    jmp [_CryptMsgControl]
  end;
end;
{$ELSE}
function CryptMsgControl; external crypt32 name 'CryptMsgControl';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _CryptMsgVerifyCountersigEnc: Pointer;

function CryptMsgVerifyCountersignatureEncoded;
begin
  GetProcedureAddress(_CryptMsgVerifyCountersigEnc, crypt32, 'CryptMsgVerifyCountersignatureEncoded');
  asm
    mov esp, ebp
    pop ebp
    jmp [_CryptMsgVerifyCountersigEnc]
  end;
end;
{$ELSE}
function CryptMsgVerifyCountersignatureEncoded; external crypt32 name 'CryptMsgVerifyCountersignatureEncoded';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _CryptMsgVerifyCountersigEncEx: Pointer;

function CryptMsgVerifyCountersignatureEncodedEx;
begin
  GetProcedureAddress(_CryptMsgVerifyCountersigEncEx, crypt32, 'CryptMsgVerifyCountersignatureEncodedEx');
  asm
    mov esp, ebp
    pop ebp
    jmp [_CryptMsgVerifyCountersigEncEx]
  end;
end;
{$ELSE}
function CryptMsgVerifyCountersignatureEncodedEx; external crypt32 name 'CryptMsgVerifyCountersignatureEncodedEx';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _CryptMsgCountersign: Pointer;

function CryptMsgCountersign;
begin
  GetProcedureAddress(_CryptMsgCountersign, crypt32, 'CryptMsgCountersign');
  asm
    mov esp, ebp
    pop ebp
    jmp [_CryptMsgCountersign]
  end;
end;
{$ELSE}
function CryptMsgCountersign; external crypt32 name 'CryptMsgCountersign';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _CryptMsgCountersignEncoded: Pointer;

function CryptMsgCountersignEncoded;
begin
  GetProcedureAddress(_CryptMsgCountersignEncoded, crypt32, 'CryptMsgCountersignEncoded');
  asm
    mov esp, ebp
    pop ebp
    jmp [_CryptMsgCountersignEncoded]
  end;
end;
{$ELSE}
function CryptMsgCountersignEncoded; external crypt32 name 'CryptMsgCountersignEncoded';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _CertOpenStore: Pointer;

function CertOpenStore;
begin
  GetProcedureAddress(_CertOpenStore, crypt32, 'CertOpenStore');
  asm
    mov esp, ebp
    pop ebp
    jmp [_CertOpenStore]
  end;
end;
{$ELSE}
function CertOpenStore; external crypt32 name 'CertOpenStore';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _CertDuplicateStore: Pointer;

function CertDuplicateStore;
begin
  GetProcedureAddress(_CertDuplicateStore, crypt32, 'CertDuplicateStore');
  asm
    mov esp, ebp
    pop ebp
    jmp [_CertDuplicateStore]
  end;
end;
{$ELSE}
function CertDuplicateStore; external crypt32 name 'CertDuplicateStore';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _CertSaveStore: Pointer;

function CertSaveStore;
begin
  GetProcedureAddress(_CertSaveStore, crypt32, 'CertSaveStore');
  asm
    mov esp, ebp
    pop ebp
    jmp [_CertSaveStore]
  end;
end;
{$ELSE}
function CertSaveStore; external crypt32 name 'CertSaveStore';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _CertCloseStore: Pointer;

function CertCloseStore;
begin
  GetProcedureAddress(_CertCloseStore, crypt32, 'CertCloseStore');
  asm
    mov esp, ebp
    pop ebp
    jmp [_CertCloseStore]
  end;
end;
{$ELSE}
function CertCloseStore; external crypt32 name 'CertCloseStore';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _CertGetSubjectCertFromStore: Pointer;

function CertGetSubjectCertificateFromStore;
begin
  GetProcedureAddress(_CertGetSubjectCertFromStore, crypt32, 'CertGetSubjectCertificateFromStore');
  asm
    mov esp, ebp
    pop ebp
    jmp [_CertGetSubjectCertFromStore]
  end;
end;
{$ELSE}
function CertGetSubjectCertificateFromStore; external crypt32 name 'CertGetSubjectCertificateFromStore';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _CertEnumCertificatesInStore: Pointer;

function CertEnumCertificatesInStore;
begin
  GetProcedureAddress(_CertEnumCertificatesInStore, crypt32, 'CertEnumCertificatesInStore');
  asm
    mov esp, ebp
    pop ebp
    jmp [_CertEnumCertificatesInStore]
  end;
end;
{$ELSE}
function CertEnumCertificatesInStore; external crypt32 name 'CertEnumCertificatesInStore';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _CertFindCertificateInStore: Pointer;

function CertFindCertificateInStore;
begin
  GetProcedureAddress(_CertFindCertificateInStore, crypt32, 'CertFindCertificateInStore');
  asm
    mov esp, ebp
    pop ebp
    jmp [_CertFindCertificateInStore]
  end;
end;
{$ELSE}
function CertFindCertificateInStore; external crypt32 name 'CertFindCertificateInStore';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _CertGetIssuerCertFromStore: Pointer;

function CertGetIssuerCertificateFromStore;
begin
  GetProcedureAddress(_CertGetIssuerCertFromStore, crypt32, 'CertGetIssuerCertificateFromStore');
  asm
    mov esp, ebp
    pop ebp
    jmp [_CertGetIssuerCertFromStore]
  end;
end;
{$ELSE}
function CertGetIssuerCertificateFromStore; external crypt32 name 'CertGetIssuerCertificateFromStore';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _CertVerifySubjectCertContext: Pointer;

function CertVerifySubjectCertificateContext;
begin
  GetProcedureAddress(_CertVerifySubjectCertContext, crypt32, 'CertVerifySubjectCertificateContext');
  asm
    mov esp, ebp
    pop ebp
    jmp [_CertVerifySubjectCertContext]
  end;
end;
{$ELSE}
function CertVerifySubjectCertificateContext; external crypt32 name 'CertVerifySubjectCertificateContext';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _CertDuplicateCertificateContext: Pointer;

function CertDuplicateCertificateContext;
begin
  GetProcedureAddress(_CertDuplicateCertificateContext, crypt32, 'CertDuplicateCertificateContext');
  asm
    mov esp, ebp
    pop ebp
    jmp [_CertDuplicateCertificateContext]
  end;
end;
{$ELSE}
function CertDuplicateCertificateContext; external crypt32 name 'CertDuplicateCertificateContext';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _CertCreateCertificateContext: Pointer;

function CertCreateCertificateContext;
begin
  GetProcedureAddress(_CertCreateCertificateContext, crypt32, 'CertCreateCertificateContext');
  asm
    mov esp, ebp
    pop ebp
    jmp [_CertCreateCertificateContext]
  end;
end;
{$ELSE}
function CertCreateCertificateContext; external crypt32 name 'CertCreateCertificateContext';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _CertFreeCertificateContext: Pointer;

function CertFreeCertificateContext;
begin
  GetProcedureAddress(_CertFreeCertificateContext, crypt32, 'CertFreeCertificateContext');
  asm
    mov esp, ebp
    pop ebp
    jmp [_CertFreeCertificateContext]
  end;
end;
{$ELSE}
function CertFreeCertificateContext; external crypt32 name 'CertFreeCertificateContext';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _CertSetCertContextProperty: Pointer;

function CertSetCertificateContextProperty;
begin
  GetProcedureAddress(_CertSetCertContextProperty, crypt32, 'CertSetCertificateContextProperty');
  asm
    mov esp, ebp
    pop ebp
    jmp [_CertSetCertContextProperty]
  end;
end;
{$ELSE}
function CertSetCertificateContextProperty; external crypt32 name 'CertSetCertificateContextProperty';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _CertGetCertContextProperty: Pointer;

function CertGetCertificateContextProperty;
begin
  GetProcedureAddress(_CertGetCertContextProperty, crypt32, 'CertGetCertificateContextProperty');
  asm
    mov esp, ebp
    pop ebp
    jmp [_CertGetCertContextProperty]
  end;
end;
{$ELSE}
function CertGetCertificateContextProperty; external crypt32 name 'CertGetCertificateContextProperty';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _CertEnumCertContextProperties: Pointer;

function CertEnumCertificateContextProperties;
begin
  GetProcedureAddress(_CertEnumCertContextProperties, crypt32, 'CertEnumCertificateContextProperties');
  asm
    mov esp, ebp
    pop ebp
    jmp [_CertEnumCertContextProperties]
  end;
end;
{$ELSE}
function CertEnumCertificateContextProperties; external crypt32 name 'CertEnumCertificateContextProperties';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _CertGetCRLFromStore: Pointer;

function CertGetCRLFromStore;
begin
  GetProcedureAddress(_CertGetCRLFromStore, crypt32, 'CertGetCRLFromStore');
  asm
    mov esp, ebp
    pop ebp
    jmp [_CertGetCRLFromStore]
  end;
end;
{$ELSE}
function CertGetCRLFromStore; external crypt32 name 'CertGetCRLFromStore';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _CertEnumCRLsInStore: Pointer;

function CertEnumCRLsInStore;
begin
  GetProcedureAddress(_CertEnumCRLsInStore, crypt32, 'CertEnumCRLsInStore');
  asm
    mov esp, ebp
    pop ebp
    jmp [_CertEnumCRLsInStore]
  end;
end;
{$ELSE}
function CertEnumCRLsInStore; external crypt32 name 'CertEnumCRLsInStore';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _CertFindCRLInStore: Pointer;

function CertFindCRLInStore;
begin
  GetProcedureAddress(_CertFindCRLInStore, crypt32, 'CertFindCRLInStore');
  asm
    mov esp, ebp
    pop ebp
    jmp [_CertFindCRLInStore]
  end;
end;
{$ELSE}
function CertFindCRLInStore; external crypt32 name 'CertFindCRLInStore';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _CertDuplicateCRLContext: Pointer;

function CertDuplicateCRLContext;
begin
  GetProcedureAddress(_CertDuplicateCRLContext, crypt32, 'CertDuplicateCRLContext');
  asm
    mov esp, ebp
    pop ebp
    jmp [_CertDuplicateCRLContext]
  end;
end;
{$ELSE}
function CertDuplicateCRLContext; external crypt32 name 'CertDuplicateCRLContext';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _CertCreateCRLContext: Pointer;

function CertCreateCRLContext;
begin
  GetProcedureAddress(_CertCreateCRLContext, crypt32, 'CertCreateCRLContext');
  asm
    mov esp, ebp
    pop ebp
    jmp [_CertCreateCRLContext]
  end;
end;
{$ELSE}
function CertCreateCRLContext; external crypt32 name 'CertCreateCRLContext';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _CertFreeCRLContext: Pointer;

function CertFreeCRLContext;
begin
  GetProcedureAddress(_CertFreeCRLContext, crypt32, 'CertFreeCRLContext');
  asm
    mov esp, ebp
    pop ebp
    jmp [_CertFreeCRLContext]
  end;
end;
{$ELSE}
function CertFreeCRLContext; external crypt32 name 'CertFreeCRLContext';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _CertSetCRLContextProperty: Pointer;

function CertSetCRLContextProperty;
begin
  GetProcedureAddress(_CertSetCRLContextProperty, crypt32, 'CertSetCRLContextProperty');
  asm
    mov esp, ebp
    pop ebp
    jmp [_CertSetCRLContextProperty]
  end;
end;
{$ELSE}
function CertSetCRLContextProperty; external crypt32 name 'CertSetCRLContextProperty';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _CertGetCRLContextProperty: Pointer;

function CertGetCRLContextProperty;
begin
  GetProcedureAddress(_CertGetCRLContextProperty, crypt32, 'CertGetCRLContextProperty');
  asm
    mov esp, ebp
    pop ebp
    jmp [_CertGetCRLContextProperty]
  end;
end;
{$ELSE}
function CertGetCRLContextProperty; external crypt32 name 'CertGetCRLContextProperty';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _CertEnumCRLContextProperties: Pointer;

function CertEnumCRLContextProperties;
begin
  GetProcedureAddress(_CertEnumCRLContextProperties, crypt32, 'CertEnumCRLContextProperties');
  asm
    mov esp, ebp
    pop ebp
    jmp [_CertEnumCRLContextProperties]
  end;
end;
{$ELSE}
function CertEnumCRLContextProperties; external crypt32 name 'CertEnumCRLContextProperties';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _CertFindCertificateInCRL: Pointer;

function CertFindCertificateInCRL;
begin
  GetProcedureAddress(_CertFindCertificateInCRL, crypt32, 'CertFindCertificateInCRL');
  asm
    mov esp, ebp
    pop ebp
    jmp [_CertFindCertificateInCRL]
  end;
end;
{$ELSE}
function CertFindCertificateInCRL; external crypt32 name 'CertFindCertificateInCRL';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _CertAddEncodedCertToStore: Pointer;

function CertAddEncodedCertificateToStore;
begin
  GetProcedureAddress(_CertAddEncodedCertToStore, crypt32, 'CertAddEncodedCertificateToStore');
  asm
    mov esp, ebp
    pop ebp
    jmp [_CertAddEncodedCertToStore]
  end;
end;
{$ELSE}
function CertAddEncodedCertificateToStore; external crypt32 name 'CertAddEncodedCertificateToStore';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _CertAddCertContextToStore: Pointer;

function CertAddCertificateContextToStore;
begin
  GetProcedureAddress(_CertAddCertContextToStore, crypt32, 'CertAddCertificateContextToStore');
  asm
    mov esp, ebp
    pop ebp
    jmp [_CertAddCertContextToStore]
  end;
end;
{$ELSE}
function CertAddCertificateContextToStore; external crypt32 name 'CertAddCertificateContextToStore';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _CertAddSerializedElementToStore: Pointer;

function CertAddSerializedElementToStore;
begin
  GetProcedureAddress(_CertAddSerializedElementToStore, crypt32, 'CertAddSerializedElementToStore');
  asm
    mov esp, ebp
    pop ebp
    jmp [_CertAddSerializedElementToStore]
  end;
end;
{$ELSE}
function CertAddSerializedElementToStore; external crypt32 name 'CertAddSerializedElementToStore';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _CertDeleteCertificateFromStore: Pointer;

function CertDeleteCertificateFromStore;
begin
  GetProcedureAddress(_CertDeleteCertificateFromStore, crypt32, 'CertDeleteCertificateFromStore');
  asm
    mov esp, ebp
    pop ebp
    jmp [_CertDeleteCertificateFromStore]
  end;
end;
{$ELSE}
function CertDeleteCertificateFromStore; external crypt32 name 'CertDeleteCertificateFromStore';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _CertAddEncodedCRLToStore: Pointer;

function CertAddEncodedCRLToStore;
begin
  GetProcedureAddress(_CertAddEncodedCRLToStore, crypt32, 'CertAddEncodedCRLToStore');
  asm
    mov esp, ebp
    pop ebp
    jmp [_CertAddEncodedCRLToStore]
  end;
end;
{$ELSE}
function CertAddEncodedCRLToStore; external crypt32 name 'CertAddEncodedCRLToStore';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _CertAddCRLContextToStore: Pointer;

function CertAddCRLContextToStore;
begin
  GetProcedureAddress(_CertAddCRLContextToStore, crypt32, 'CertAddCRLContextToStore');
  asm
    mov esp, ebp
    pop ebp
    jmp [_CertAddCRLContextToStore]
  end;
end;
{$ELSE}
function CertAddCRLContextToStore; external crypt32 name 'CertAddCRLContextToStore';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _CertDeleteCRLFromStore: Pointer;

function CertDeleteCRLFromStore;
begin
  GetProcedureAddress(_CertDeleteCRLFromStore, crypt32, 'CertDeleteCRLFromStore');
  asm
    mov esp, ebp
    pop ebp
    jmp [_CertDeleteCRLFromStore]
  end;
end;
{$ELSE}
function CertDeleteCRLFromStore; external crypt32 name 'CertDeleteCRLFromStore';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _CertSerializeCertStoreElement: Pointer;

function CertSerializeCertificateStoreElement;
begin
  GetProcedureAddress(_CertSerializeCertStoreElement, crypt32, 'CertSerializeCertificateStoreElement');
  asm
    mov esp, ebp
    pop ebp
    jmp [_CertSerializeCertStoreElement]
  end;
end;
{$ELSE}
function CertSerializeCertificateStoreElement; external crypt32 name 'CertSerializeCertificateStoreElement';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _CertSerializeCRLStoreElement: Pointer;

function CertSerializeCRLStoreElement;
begin
  GetProcedureAddress(_CertSerializeCRLStoreElement, crypt32, 'CertSerializeCRLStoreElement');
  asm
    mov esp, ebp
    pop ebp
    jmp [_CertSerializeCRLStoreElement]
  end;
end;
{$ELSE}
function CertSerializeCRLStoreElement; external crypt32 name 'CertSerializeCRLStoreElement';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _CertDuplicateCTLContext: Pointer;

function CertDuplicateCTLContext;
begin
  GetProcedureAddress(_CertDuplicateCTLContext, crypt32, 'CertDuplicateCTLContext');
  asm
    mov esp, ebp
    pop ebp
    jmp [_CertDuplicateCTLContext]
  end;
end;
{$ELSE}
function CertDuplicateCTLContext; external crypt32 name 'CertDuplicateCTLContext';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _CertCreateCTLContext: Pointer;

function CertCreateCTLContext;
begin
  GetProcedureAddress(_CertCreateCTLContext, crypt32, 'CertCreateCTLContext');
  asm
    mov esp, ebp
    pop ebp
    jmp [_CertCreateCTLContext]
  end;
end;
{$ELSE}
function CertCreateCTLContext; external crypt32 name 'CertCreateCTLContext';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _CertFreeCTLContext: Pointer;

function CertFreeCTLContext;
begin
  GetProcedureAddress(_CertFreeCTLContext, crypt32, 'CertFreeCTLContext');
  asm
    mov esp, ebp
    pop ebp
    jmp [_CertFreeCTLContext]
  end;
end;
{$ELSE}
function CertFreeCTLContext; external crypt32 name 'CertFreeCTLContext';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _CertSetCTLContextProperty: Pointer;

function CertSetCTLContextProperty;
begin
  GetProcedureAddress(_CertSetCTLContextProperty, crypt32, 'CertSetCTLContextProperty');
  asm
    mov esp, ebp
    pop ebp
    jmp [_CertSetCTLContextProperty]
  end;
end;
{$ELSE}
function CertSetCTLContextProperty; external crypt32 name 'CertSetCTLContextProperty';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _CertGetCTLContextProperty: Pointer;

function CertGetCTLContextProperty;
begin
  GetProcedureAddress(_CertGetCTLContextProperty, crypt32, 'CertGetCTLContextProperty');
  asm
    mov esp, ebp
    pop ebp
    jmp [_CertGetCTLContextProperty]
  end;
end;
{$ELSE}
function CertGetCTLContextProperty; external crypt32 name 'CertGetCTLContextProperty';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _CertEnumCTLContextProperties: Pointer;

function CertEnumCTLContextProperties;
begin
  GetProcedureAddress(_CertEnumCTLContextProperties, crypt32, 'CertEnumCTLContextProperties');
  asm
    mov esp, ebp
    pop ebp
    jmp [_CertEnumCTLContextProperties]
  end;
end;
{$ELSE}
function CertEnumCTLContextProperties; external crypt32 name 'CertEnumCTLContextProperties';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _CertEnumCTLsInStore: Pointer;

function CertEnumCTLsInStore;
begin
  GetProcedureAddress(_CertEnumCTLsInStore, crypt32, 'CertEnumCTLsInStore');
  asm
    mov esp, ebp
    pop ebp
    jmp [_CertEnumCTLsInStore]
  end;
end;
{$ELSE}
function CertEnumCTLsInStore; external crypt32 name 'CertEnumCTLsInStore';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _CertFindSubjectInCTL: Pointer;

function CertFindSubjectInCTL;
begin
  GetProcedureAddress(_CertFindSubjectInCTL, crypt32, 'CertFindSubjectInCTL');
  asm
    mov esp, ebp
    pop ebp
    jmp [_CertFindSubjectInCTL]
  end;
end;
{$ELSE}
function CertFindSubjectInCTL; external crypt32 name 'CertFindSubjectInCTL';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _CertFindCTLInStore: Pointer;

function CertFindCTLInStore;
begin
  GetProcedureAddress(_CertFindCTLInStore, crypt32, 'CertFindCTLInStore');
  asm
    mov esp, ebp
    pop ebp
    jmp [_CertFindCTLInStore]
  end;
end;
{$ELSE}
function CertFindCTLInStore; external crypt32 name 'CertFindCTLInStore';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _CertAddEncodedCTLToStore: Pointer;

function CertAddEncodedCTLToStore;
begin
  GetProcedureAddress(_CertAddEncodedCTLToStore, crypt32, 'CertAddEncodedCTLToStore');
  asm
    mov esp, ebp
    pop ebp
    jmp [_CertAddEncodedCTLToStore]
  end;
end;
{$ELSE}
function CertAddEncodedCTLToStore; external crypt32 name 'CertAddEncodedCTLToStore';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _CertAddCTLContextToStore: Pointer;

function CertAddCTLContextToStore;
begin
  GetProcedureAddress(_CertAddCTLContextToStore, crypt32, 'CertAddCTLContextToStore');
  asm
    mov esp, ebp
    pop ebp
    jmp [_CertAddCTLContextToStore]
  end;
end;
{$ELSE}
function CertAddCTLContextToStore; external crypt32 name 'CertAddCTLContextToStore';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _CertSerializeCTLStoreElement: Pointer;

function CertSerializeCTLStoreElement;
begin
  GetProcedureAddress(_CertSerializeCTLStoreElement, crypt32, 'CertSerializeCTLStoreElement');
  asm
    mov esp, ebp
    pop ebp
    jmp [_CertSerializeCTLStoreElement]
  end;
end;
{$ELSE}
function CertSerializeCTLStoreElement; external crypt32 name 'CertSerializeCTLStoreElement';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _CertDeleteCTLFromStore: Pointer;

function CertDeleteCTLFromStore;
begin
  GetProcedureAddress(_CertDeleteCTLFromStore, crypt32, 'CertDeleteCTLFromStore');
  asm
    mov esp, ebp
    pop ebp
    jmp [_CertDeleteCTLFromStore]
  end;
end;
{$ELSE}
function CertDeleteCTLFromStore; external crypt32 name 'CertDeleteCTLFromStore';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _CertAddCertificateLinkToStore: Pointer;

function CertAddCertificateLinkToStore;
begin
  GetProcedureAddress(_CertAddCertificateLinkToStore, crypt32, 'CertAddCertificateLinkToStore');
  asm
    mov esp, ebp
    pop ebp
    jmp [_CertAddCertificateLinkToStore]
  end;
end;
{$ELSE}
function CertAddCertificateLinkToStore; external crypt32 name 'CertAddCertificateLinkToStore';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _CertAddCRLLinkToStore: Pointer;

function CertAddCRLLinkToStore;
begin
  GetProcedureAddress(_CertAddCRLLinkToStore, crypt32, 'CertAddCRLLinkToStore');
  asm
    mov esp, ebp
    pop ebp
    jmp [_CertAddCRLLinkToStore]
  end;
end;
{$ELSE}
function CertAddCRLLinkToStore; external crypt32 name 'CertAddCRLLinkToStore';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _CertAddCTLLinkToStore: Pointer;

function CertAddCTLLinkToStore;
begin
  GetProcedureAddress(_CertAddCTLLinkToStore, crypt32, 'CertAddCTLLinkToStore');
  asm
    mov esp, ebp
    pop ebp
    jmp [_CertAddCTLLinkToStore]
  end;
end;
{$ELSE}
function CertAddCTLLinkToStore; external crypt32 name 'CertAddCTLLinkToStore';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _CertAddStoreToCollection: Pointer;

function CertAddStoreToCollection;
begin
  GetProcedureAddress(_CertAddStoreToCollection, crypt32, 'CertAddStoreToCollection');
  asm
    mov esp, ebp
    pop ebp
    jmp [_CertAddStoreToCollection]
  end;
end;
{$ELSE}
function CertAddStoreToCollection; external crypt32 name 'CertAddStoreToCollection';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _CertRemoveStoreFromCollection: Pointer;

procedure CertRemoveStoreFromCollection;
begin
  GetProcedureAddress(_CertRemoveStoreFromCollection, crypt32, 'CertRemoveStoreFromCollection');
  asm
    mov esp, ebp
    pop ebp
    jmp [_CertRemoveStoreFromCollection]
  end;
end;
{$ELSE}
procedure CertRemoveStoreFromCollection; external crypt32 name 'CertRemoveStoreFromCollection';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _CertControlStore: Pointer;

function CertControlStore;
begin
  GetProcedureAddress(_CertControlStore, crypt32, 'CertControlStore');
  asm
    mov esp, ebp
    pop ebp
    jmp [_CertControlStore]
  end;
end;
{$ELSE}
function CertControlStore; external crypt32 name 'CertControlStore';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _CertSetStoreProperty: Pointer;

function CertSetStoreProperty;
begin
  GetProcedureAddress(_CertSetStoreProperty, crypt32, 'CertSetStoreProperty');
  asm
    mov esp, ebp
    pop ebp
    jmp [_CertSetStoreProperty]
  end;
end;
{$ELSE}
function CertSetStoreProperty; external crypt32 name 'CertSetStoreProperty';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _CertGetStoreProperty: Pointer;

function CertGetStoreProperty;
begin
  GetProcedureAddress(_CertGetStoreProperty, crypt32, 'CertGetStoreProperty');
  asm
    mov esp, ebp
    pop ebp
    jmp [_CertGetStoreProperty]
  end;
end;
{$ELSE}
function CertGetStoreProperty; external crypt32 name 'CertGetStoreProperty';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _CertCreateContext: Pointer;

function CertCreateContext;
begin
  GetProcedureAddress(_CertCreateContext, crypt32, 'CertCreateContext');
  asm
    mov esp, ebp
    pop ebp
    jmp [_CertCreateContext]
  end;
end;
{$ELSE}
function CertCreateContext; external crypt32 name 'CertCreateContext';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _CertRegisterSystemStore: Pointer;

function CertRegisterSystemStore;
begin
  GetProcedureAddress(_CertRegisterSystemStore, crypt32, 'CertRegisterSystemStore');
  asm
    mov esp, ebp
    pop ebp
    jmp [_CertRegisterSystemStore]
  end;
end;
{$ELSE}
function CertRegisterSystemStore; external crypt32 name 'CertRegisterSystemStore';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _CertRegisterPhysicalStore: Pointer;

function CertRegisterPhysicalStore;
begin
  GetProcedureAddress(_CertRegisterPhysicalStore, crypt32, 'CertRegisterPhysicalStore');
  asm
    mov esp, ebp
    pop ebp
    jmp [_CertRegisterPhysicalStore]
  end;
end;
{$ELSE}
function CertRegisterPhysicalStore; external crypt32 name 'CertRegisterPhysicalStore';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _CertUnregisterSystemStore: Pointer;

function CertUnregisterSystemStore;
begin
  GetProcedureAddress(_CertUnregisterSystemStore, crypt32, 'CertUnregisterSystemStore');
  asm
    mov esp, ebp
    pop ebp
    jmp [_CertUnregisterSystemStore]
  end;
end;
{$ELSE}
function CertUnregisterSystemStore; external crypt32 name 'CertUnregisterSystemStore';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _CertUnregisterPhysicalStore: Pointer;

function CertUnregisterPhysicalStore;
begin
  GetProcedureAddress(_CertUnregisterPhysicalStore, crypt32, 'CertUnregisterPhysicalStore');
  asm
    mov esp, ebp
    pop ebp
    jmp [_CertUnregisterPhysicalStore]
  end;
end;
{$ELSE}
function CertUnregisterPhysicalStore; external crypt32 name 'CertUnregisterPhysicalStore';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _CertEnumSystemStoreLocation: Pointer;

function CertEnumSystemStoreLocation;
begin
  GetProcedureAddress(_CertEnumSystemStoreLocation, crypt32, 'CertEnumSystemStoreLocation');
  asm
    mov esp, ebp
    pop ebp
    jmp [_CertEnumSystemStoreLocation]
  end;
end;
{$ELSE}
function CertEnumSystemStoreLocation; external crypt32 name 'CertEnumSystemStoreLocation';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _CertEnumSystemStore: Pointer;

function CertEnumSystemStore;
begin
  GetProcedureAddress(_CertEnumSystemStore, crypt32, 'CertEnumSystemStore');
  asm
    mov esp, ebp
    pop ebp
    jmp [_CertEnumSystemStore]
  end;
end;
{$ELSE}
function CertEnumSystemStore; external crypt32 name 'CertEnumSystemStore';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _CertEnumPhysicalStore: Pointer;

function CertEnumPhysicalStore;
begin
  GetProcedureAddress(_CertEnumPhysicalStore, crypt32, 'CertEnumPhysicalStore');
  asm
    mov esp, ebp
    pop ebp
    jmp [_CertEnumPhysicalStore]
  end;
end;
{$ELSE}
function CertEnumPhysicalStore; external crypt32 name 'CertEnumPhysicalStore';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _CertGetEnhancedKeyUsage: Pointer;

function CertGetEnhancedKeyUsage;
begin
  GetProcedureAddress(_CertGetEnhancedKeyUsage, crypt32, 'CertGetEnhancedKeyUsage');
  asm
    mov esp, ebp
    pop ebp
    jmp [_CertGetEnhancedKeyUsage]
  end;
end;
{$ELSE}
function CertGetEnhancedKeyUsage; external crypt32 name 'CertGetEnhancedKeyUsage';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _CertSetEnhancedKeyUsage: Pointer;

function CertSetEnhancedKeyUsage;
begin
  GetProcedureAddress(_CertSetEnhancedKeyUsage, crypt32, 'CertSetEnhancedKeyUsage');
  asm
    mov esp, ebp
    pop ebp
    jmp [_CertSetEnhancedKeyUsage]
  end;
end;
{$ELSE}
function CertSetEnhancedKeyUsage; external crypt32 name 'CertSetEnhancedKeyUsage';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _CertAddEnhKeyUsageIdentifier: Pointer;

function CertAddEnhancedKeyUsageIdentifier;
begin
  GetProcedureAddress(_CertAddEnhKeyUsageIdentifier, crypt32, 'CertAddEnhancedKeyUsageIdentifier');
  asm
    mov esp, ebp
    pop ebp
    jmp [_CertAddEnhKeyUsageIdentifier]
  end;
end;
{$ELSE}
function CertAddEnhancedKeyUsageIdentifier; external crypt32 name 'CertAddEnhancedKeyUsageIdentifier';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _CertRemoveEnhKeyUsageIdent: Pointer;

function CertRemoveEnhancedKeyUsageIdentifier;
begin
  GetProcedureAddress(_CertRemoveEnhKeyUsageIdent, crypt32, 'CertRemoveEnhancedKeyUsageIdentifier');
  asm
    mov esp, ebp
    pop ebp
    jmp [_CertRemoveEnhKeyUsageIdent]
  end;
end;
{$ELSE}
function CertRemoveEnhancedKeyUsageIdentifier; external crypt32 name 'CertRemoveEnhancedKeyUsageIdentifier';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _CertGetValidUsages: Pointer;

function CertGetValidUsages;
begin
  GetProcedureAddress(_CertGetValidUsages, crypt32, 'CertGetValidUsages');
  asm
    mov esp, ebp
    pop ebp
    jmp [_CertGetValidUsages]
  end;
end;
{$ELSE}
function CertGetValidUsages; external crypt32 name 'CertGetValidUsages';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _CryptMsgGetAndVerifySigner: Pointer;

function CryptMsgGetAndVerifySigner;
begin
  GetProcedureAddress(_CryptMsgGetAndVerifySigner, crypt32, 'CryptMsgGetAndVerifySigner');
  asm
    mov esp, ebp
    pop ebp
    jmp [_CryptMsgGetAndVerifySigner]
  end;
end;
{$ELSE}
function CryptMsgGetAndVerifySigner; external crypt32 name 'CryptMsgGetAndVerifySigner';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _CryptMsgSignCTL: Pointer;

function CryptMsgSignCTL;
begin
  GetProcedureAddress(_CryptMsgSignCTL, crypt32, 'CryptMsgSignCTL');
  asm
    mov esp, ebp
    pop ebp
    jmp [_CryptMsgSignCTL]
  end;
end;
{$ELSE}
function CryptMsgSignCTL; external crypt32 name 'CryptMsgSignCTL';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _CryptMsgEncodeAndSignCTL: Pointer;

function CryptMsgEncodeAndSignCTL;
begin
  GetProcedureAddress(_CryptMsgEncodeAndSignCTL, crypt32, 'CryptMsgEncodeAndSignCTL');
  asm
    mov esp, ebp
    pop ebp
    jmp [_CryptMsgEncodeAndSignCTL]
  end;
end;
{$ELSE}
function CryptMsgEncodeAndSignCTL; external crypt32 name 'CryptMsgEncodeAndSignCTL';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _CertFindSubjectInSortedCTL: Pointer;

function CertFindSubjectInSortedCTL;
begin
  GetProcedureAddress(_CertFindSubjectInSortedCTL, crypt32, 'CertFindSubjectInSortedCTL');
  asm
    mov esp, ebp
    pop ebp
    jmp [_CertFindSubjectInSortedCTL]
  end;
end;
{$ELSE}
function CertFindSubjectInSortedCTL; external crypt32 name 'CertFindSubjectInSortedCTL';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _CertEnumSubjectInSortedCTL: Pointer;

function CertEnumSubjectInSortedCTL;
begin
  GetProcedureAddress(_CertEnumSubjectInSortedCTL, crypt32, 'CertEnumSubjectInSortedCTL');
  asm
    mov esp, ebp
    pop ebp
    jmp [_CertEnumSubjectInSortedCTL]
  end;
end;
{$ELSE}
function CertEnumSubjectInSortedCTL; external crypt32 name 'CertEnumSubjectInSortedCTL';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _CertVerifyCTLUsage: Pointer;

function CertVerifyCTLUsage;
begin
  GetProcedureAddress(_CertVerifyCTLUsage, crypt32, 'CertVerifyCTLUsage');
  asm
    mov esp, ebp
    pop ebp
    jmp [_CertVerifyCTLUsage]
  end;
end;
{$ELSE}
function CertVerifyCTLUsage; external crypt32 name 'CertVerifyCTLUsage';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _CertVerifyRevocation: Pointer;

function CertVerifyRevocation;
begin
  GetProcedureAddress(_CertVerifyRevocation, crypt32, 'CertVerifyRevocation');
  asm
    mov esp, ebp
    pop ebp
    jmp [_CertVerifyRevocation]
  end;
end;
{$ELSE}
function CertVerifyRevocation; external crypt32 name 'CertVerifyRevocation';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _CertCompareIntegerBlob: Pointer;

function CertCompareIntegerBlob;
begin
  GetProcedureAddress(_CertCompareIntegerBlob, crypt32, 'CertCompareIntegerBlob');
  asm
    mov esp, ebp
    pop ebp
    jmp [_CertCompareIntegerBlob]
  end;
end;
{$ELSE}
function CertCompareIntegerBlob; external crypt32 name 'CertCompareIntegerBlob';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _CertCompareCertificate: Pointer;

function CertCompareCertificate;
begin
  GetProcedureAddress(_CertCompareCertificate, crypt32, 'CertCompareCertificate');
  asm
    mov esp, ebp
    pop ebp
    jmp [_CertCompareCertificate]
  end;
end;
{$ELSE}
function CertCompareCertificate; external crypt32 name 'CertCompareCertificate';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _CertCompareCertificateName: Pointer;

function CertCompareCertificateName;
begin
  GetProcedureAddress(_CertCompareCertificateName, crypt32, 'CertCompareCertificateName');
  asm
    mov esp, ebp
    pop ebp
    jmp [_CertCompareCertificateName]
  end;
end;
{$ELSE}
function CertCompareCertificateName; external crypt32 name 'CertCompareCertificateName';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _CertIsRDNAttrsInCertificateName: Pointer;

function CertIsRDNAttrsInCertificateName;
begin
  GetProcedureAddress(_CertIsRDNAttrsInCertificateName, crypt32, 'CertIsRDNAttrsInCertificateName');
  asm
    mov esp, ebp
    pop ebp
    jmp [_CertIsRDNAttrsInCertificateName]
  end;
end;
{$ELSE}
function CertIsRDNAttrsInCertificateName; external crypt32 name 'CertIsRDNAttrsInCertificateName';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _CertComparePublicKeyInfo: Pointer;

function CertComparePublicKeyInfo;
begin
  GetProcedureAddress(_CertComparePublicKeyInfo, crypt32, 'CertComparePublicKeyInfo');
  asm
    mov esp, ebp
    pop ebp
    jmp [_CertComparePublicKeyInfo]
  end;
end;
{$ELSE}
function CertComparePublicKeyInfo; external crypt32 name 'CertComparePublicKeyInfo';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _CertGetPublicKeyLength: Pointer;

function CertGetPublicKeyLength;
begin
  GetProcedureAddress(_CertGetPublicKeyLength, crypt32, 'CertGetPublicKeyLength');
  asm
    mov esp, ebp
    pop ebp
    jmp [_CertGetPublicKeyLength]
  end;
end;
{$ELSE}
function CertGetPublicKeyLength; external crypt32 name 'CertGetPublicKeyLength';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _CryptVerifyCertificateSignature: Pointer;

function CryptVerifyCertificateSignature;
begin
  GetProcedureAddress(_CryptVerifyCertificateSignature, crypt32, 'CryptVerifyCertificateSignature');
  asm
    mov esp, ebp
    pop ebp
    jmp [_CryptVerifyCertificateSignature]
  end;
end;
{$ELSE}
function CryptVerifyCertificateSignature; external crypt32 name 'CryptVerifyCertificateSignature';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _CryptVerifyCertSignatureEx: Pointer;

function CryptVerifyCertificateSignatureEx;
begin
  GetProcedureAddress(_CryptVerifyCertSignatureEx, crypt32, 'CryptVerifyCertificateSignatureEx');
  asm
    mov esp, ebp
    pop ebp
    jmp [_CryptVerifyCertSignatureEx]
  end;
end;
{$ELSE}
function CryptVerifyCertificateSignatureEx; external crypt32 name 'CryptVerifyCertificateSignatureEx';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _CryptHashToBeSigned: Pointer;

function CryptHashToBeSigned;
begin
  GetProcedureAddress(_CryptHashToBeSigned, crypt32, 'CryptHashToBeSigned');
  asm
    mov esp, ebp
    pop ebp
    jmp [_CryptHashToBeSigned]
  end;
end;
{$ELSE}
function CryptHashToBeSigned; external crypt32 name 'CryptHashToBeSigned';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _CryptHashCertificate: Pointer;

function CryptHashCertificate;
begin
  GetProcedureAddress(_CryptHashCertificate, crypt32, 'CryptHashCertificate');
  asm
    mov esp, ebp
    pop ebp
    jmp [_CryptHashCertificate]
  end;
end;
{$ELSE}
function CryptHashCertificate; external crypt32 name 'CryptHashCertificate';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _CryptSignCertificate: Pointer;

function CryptSignCertificate;
begin
  GetProcedureAddress(_CryptSignCertificate, crypt32, 'CryptSignCertificate');
  asm
    mov esp, ebp
    pop ebp
    jmp [_CryptSignCertificate]
  end;
end;
{$ELSE}
function CryptSignCertificate; external crypt32 name 'CryptSignCertificate';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _CryptSignAndEncodeCertificate: Pointer;

function CryptSignAndEncodeCertificate;
begin
  GetProcedureAddress(_CryptSignAndEncodeCertificate, crypt32, 'CryptSignAndEncodeCertificate');
  asm
    mov esp, ebp
    pop ebp
    jmp [_CryptSignAndEncodeCertificate]
  end;
end;
{$ELSE}
function CryptSignAndEncodeCertificate; external crypt32 name 'CryptSignAndEncodeCertificate';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _CertVerifyTimeValidity: Pointer;

function CertVerifyTimeValidity;
begin
  GetProcedureAddress(_CertVerifyTimeValidity, crypt32, 'CertVerifyTimeValidity');
  asm
    mov esp, ebp
    pop ebp
    jmp [_CertVerifyTimeValidity]
  end;
end;
{$ELSE}
function CertVerifyTimeValidity; external crypt32 name 'CertVerifyTimeValidity';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _CertVerifyCRLTimeValidity: Pointer;

function CertVerifyCRLTimeValidity;
begin
  GetProcedureAddress(_CertVerifyCRLTimeValidity, crypt32, 'CertVerifyCRLTimeValidity');
  asm
    mov esp, ebp
    pop ebp
    jmp [_CertVerifyCRLTimeValidity]
  end;
end;
{$ELSE}
function CertVerifyCRLTimeValidity; external crypt32 name 'CertVerifyCRLTimeValidity';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _CertVerifyValidityNesting: Pointer;

function CertVerifyValidityNesting;
begin
  GetProcedureAddress(_CertVerifyValidityNesting, crypt32, 'CertVerifyValidityNesting');
  asm
    mov esp, ebp
    pop ebp
    jmp [_CertVerifyValidityNesting]
  end;
end;
{$ELSE}
function CertVerifyValidityNesting; external crypt32 name 'CertVerifyValidityNesting';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _CertVerifyCRLRevocation: Pointer;

function CertVerifyCRLRevocation;
begin
  GetProcedureAddress(_CertVerifyCRLRevocation, crypt32, 'CertVerifyCRLRevocation');
  asm
    mov esp, ebp
    pop ebp
    jmp [_CertVerifyCRLRevocation]
  end;
end;
{$ELSE}
function CertVerifyCRLRevocation; external crypt32 name 'CertVerifyCRLRevocation';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _CertAlgIdToOID: Pointer;

function CertAlgIdToOID;
begin
  GetProcedureAddress(_CertAlgIdToOID, crypt32, 'CertAlgIdToOID');
  asm
    mov esp, ebp
    pop ebp
    jmp [_CertAlgIdToOID]
  end;
end;
{$ELSE}
function CertAlgIdToOID; external crypt32 name 'CertAlgIdToOID';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _CertOIDToAlgId: Pointer;

function CertOIDToAlgId;
begin
  GetProcedureAddress(_CertOIDToAlgId, crypt32, 'CertOIDToAlgId');
  asm
    mov esp, ebp
    pop ebp
    jmp [_CertOIDToAlgId]
  end;
end;
{$ELSE}
function CertOIDToAlgId; external crypt32 name 'CertOIDToAlgId';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _CertFindExtension: Pointer;

function CertFindExtension;
begin
  GetProcedureAddress(_CertFindExtension, crypt32, 'CertFindExtension');
  asm
    mov esp, ebp
    pop ebp
    jmp [_CertFindExtension]
  end;
end;
{$ELSE}
function CertFindExtension; external crypt32 name 'CertFindExtension';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _CertFindAttribute: Pointer;

function CertFindAttribute;
begin
  GetProcedureAddress(_CertFindAttribute, crypt32, 'CertFindAttribute');
  asm
    mov esp, ebp
    pop ebp
    jmp [_CertFindAttribute]
  end;
end;
{$ELSE}
function CertFindAttribute; external crypt32 name 'CertFindAttribute';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _CertFindRDNAttr: Pointer;

function CertFindRDNAttr;
begin
  GetProcedureAddress(_CertFindRDNAttr, crypt32, 'CertFindRDNAttr');
  asm
    mov esp, ebp
    pop ebp
    jmp [_CertFindRDNAttr]
  end;
end;
{$ELSE}
function CertFindRDNAttr; external crypt32 name 'CertFindRDNAttr';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _CertGetIntendedKeyUsage: Pointer;

function CertGetIntendedKeyUsage;
begin
  GetProcedureAddress(_CertGetIntendedKeyUsage, crypt32, 'CertGetIntendedKeyUsage');
  asm
    mov esp, ebp
    pop ebp
    jmp [_CertGetIntendedKeyUsage]
  end;
end;
{$ELSE}
function CertGetIntendedKeyUsage; external crypt32 name 'CertGetIntendedKeyUsage';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _CryptInstallDefaultContext: Pointer;

function CryptInstallDefaultContext;
begin
  GetProcedureAddress(_CryptInstallDefaultContext, crypt32, 'CryptInstallDefaultContext');
  asm
    mov esp, ebp
    pop ebp
    jmp [_CryptInstallDefaultContext]
  end;
end;
{$ELSE}
function CryptInstallDefaultContext; external crypt32 name 'CryptInstallDefaultContext';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _CryptUninstallDefaultContext: Pointer;

function CryptUninstallDefaultContext;
begin
  GetProcedureAddress(_CryptUninstallDefaultContext, crypt32, 'CryptUninstallDefaultContext');
  asm
    mov esp, ebp
    pop ebp
    jmp [_CryptUninstallDefaultContext]
  end;
end;
{$ELSE}
function CryptUninstallDefaultContext; external crypt32 name 'CryptUninstallDefaultContext';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _CryptExportPublicKeyInfo: Pointer;

function CryptExportPublicKeyInfo;
begin
  GetProcedureAddress(_CryptExportPublicKeyInfo, crypt32, 'CryptExportPublicKeyInfo');
  asm
    mov esp, ebp
    pop ebp
    jmp [_CryptExportPublicKeyInfo]
  end;
end;
{$ELSE}
function CryptExportPublicKeyInfo; external crypt32 name 'CryptExportPublicKeyInfo';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _CryptExportPublicKeyInfoEx: Pointer;

function CryptExportPublicKeyInfoEx;
begin
  GetProcedureAddress(_CryptExportPublicKeyInfoEx, crypt32, 'CryptExportPublicKeyInfoEx');
  asm
    mov esp, ebp
    pop ebp
    jmp [_CryptExportPublicKeyInfoEx]
  end;
end;
{$ELSE}
function CryptExportPublicKeyInfoEx; external crypt32 name 'CryptExportPublicKeyInfoEx';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _CryptImportPublicKeyInfo: Pointer;

function CryptImportPublicKeyInfo;
begin
  GetProcedureAddress(_CryptImportPublicKeyInfo, crypt32, 'CryptImportPublicKeyInfo');
  asm
    mov esp, ebp
    pop ebp
    jmp [_CryptImportPublicKeyInfo]
  end;
end;
{$ELSE}
function CryptImportPublicKeyInfo; external crypt32 name 'CryptImportPublicKeyInfo';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _CryptImportPublicKeyInfoEx: Pointer;

function CryptImportPublicKeyInfoEx;
begin
  GetProcedureAddress(_CryptImportPublicKeyInfoEx, crypt32, 'CryptImportPublicKeyInfoEx');
  asm
    mov esp, ebp
    pop ebp
    jmp [_CryptImportPublicKeyInfoEx]
  end;
end;
{$ELSE}
function CryptImportPublicKeyInfoEx; external crypt32 name 'CryptImportPublicKeyInfoEx';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _CryptAcquireCertPrivateKey: Pointer;

function CryptAcquireCertificatePrivateKey;
begin
  GetProcedureAddress(_CryptAcquireCertPrivateKey, crypt32, 'CryptAcquireCertificatePrivateKey');
  asm
    mov esp, ebp
    pop ebp
    jmp [_CryptAcquireCertPrivateKey]
  end;
end;
{$ELSE}
function CryptAcquireCertificatePrivateKey; external crypt32 name 'CryptAcquireCertificatePrivateKey';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _CryptFindCertificateKeyProvInfo: Pointer;

function CryptFindCertificateKeyProvInfo;
begin
  GetProcedureAddress(_CryptFindCertificateKeyProvInfo, crypt32, 'CryptFindCertificateKeyProvInfo');
  asm
    mov esp, ebp
    pop ebp
    jmp [_CryptFindCertificateKeyProvInfo]
  end;
end;
{$ELSE}
function CryptFindCertificateKeyProvInfo; external crypt32 name 'CryptFindCertificateKeyProvInfo';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _CryptImportPKCS8: Pointer;

function CryptImportPKCS8;
begin
  GetProcedureAddress(_CryptImportPKCS8, crypt32, 'CryptImportPKCS8');
  asm
    mov esp, ebp
    pop ebp
    jmp [_CryptImportPKCS8]
  end;
end;
{$ELSE}
function CryptImportPKCS8; external crypt32 name 'CryptImportPKCS8';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _CryptExportPKCS8: Pointer;

function CryptExportPKCS8;
begin
  GetProcedureAddress(_CryptExportPKCS8, crypt32, 'CryptExportPKCS8');
  asm
    mov esp, ebp
    pop ebp
    jmp [_CryptExportPKCS8]
  end;
end;
{$ELSE}
function CryptExportPKCS8; external crypt32 name 'CryptExportPKCS8';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _CryptExportPKCS8Ex: Pointer;

function CryptExportPKCS8Ex;
begin
  GetProcedureAddress(_CryptExportPKCS8Ex, crypt32, 'CryptExportPKCS8Ex');
  asm
    mov esp, ebp
    pop ebp
    jmp [_CryptExportPKCS8Ex]
  end;
end;
{$ELSE}
function CryptExportPKCS8Ex; external crypt32 name 'CryptExportPKCS8Ex';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _CryptHashPublicKeyInfo: Pointer;

function CryptHashPublicKeyInfo;
begin
  GetProcedureAddress(_CryptHashPublicKeyInfo, crypt32, 'CryptHashPublicKeyInfo');
  asm
    mov esp, ebp
    pop ebp
    jmp [_CryptHashPublicKeyInfo]
  end;
end;
{$ELSE}
function CryptHashPublicKeyInfo; external crypt32 name 'CryptHashPublicKeyInfo';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _CertRDNValueToStrA: Pointer;

function CertRDNValueToStrA;
begin
  GetProcedureAddress(_CertRDNValueToStrA, crypt32, 'CertRDNValueToStrA');
  asm
    mov esp, ebp
    pop ebp
    jmp [_CertRDNValueToStrA]
  end;
end;
{$ELSE}
function CertRDNValueToStrA; external crypt32 name 'CertRDNValueToStrA';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _CertRDNValueToStrW: Pointer;

function CertRDNValueToStrW;
begin
  GetProcedureAddress(_CertRDNValueToStrW, crypt32, 'CertRDNValueToStrW');
  asm
    mov esp, ebp
    pop ebp
    jmp [_CertRDNValueToStrW]
  end;
end;
{$ELSE}
function CertRDNValueToStrW; external crypt32 name 'CertRDNValueToStrW';
{$ENDIF DYNAMIC_LINK}
{$IFDEF UNICODE}

{$IFDEF DYNAMIC_LINK}
var
  _CertRDNValueToStr: Pointer;

function CertRDNValueToStr;
begin
  GetProcedureAddress(_CertRDNValueToStr, crypt32, 'CertRDNValueToStrW');
  asm
    mov esp, ebp
    pop ebp
    jmp [_CertRDNValueToStr]
  end;
end;
{$ELSE}
function CertRDNValueToStr; external crypt32 name 'CertRDNValueToStrW';
{$ENDIF DYNAMIC_LINK}
{$ELSE}

{$IFDEF DYNAMIC_LINK}
var
  _CertRDNValueToStr: Pointer;

function CertRDNValueToStr;
begin
  GetProcedureAddress(_CertRDNValueToStr, crypt32, 'CertRDNValueToStrA');
  asm
    mov esp, ebp
    pop ebp
    jmp [_CertRDNValueToStr]
  end;
end;
{$ELSE}
function CertRDNValueToStr; external crypt32 name 'CertRDNValueToStrA';
{$ENDIF DYNAMIC_LINK}
{$ENDIF}

{$IFDEF DYNAMIC_LINK}
var
  _CertNameToStrA: Pointer;

function CertNameToStrA;
begin
  GetProcedureAddress(_CertNameToStrA, crypt32, 'CertNameToStrA');
  asm
    mov esp, ebp
    pop ebp
    jmp [_CertNameToStrA]
  end;
end;
{$ELSE}
function CertNameToStrA; external crypt32 name 'CertNameToStrA';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _CertNameToStrW: Pointer;

function CertNameToStrW;
begin
  GetProcedureAddress(_CertNameToStrW, crypt32, 'CertNameToStrW');
  asm
    mov esp, ebp
    pop ebp
    jmp [_CertNameToStrW]
  end;
end;
{$ELSE}
function CertNameToStrW; external crypt32 name 'CertNameToStrW';
{$ENDIF DYNAMIC_LINK}
{$IFDEF UNICODE}

{$IFDEF DYNAMIC_LINK}
var
  _CertNameToStr: Pointer;

function CertNameToStr;
begin
  GetProcedureAddress(_CertNameToStr, crypt32, 'CertNameToStrW');
  asm
    mov esp, ebp
    pop ebp
    jmp [_CertNameToStr]
  end;
end;
{$ELSE}
function CertNameToStr; external crypt32 name 'CertNameToStrW';
{$ENDIF DYNAMIC_LINK}
{$ELSE}

{$IFDEF DYNAMIC_LINK}
var
  _CertNameToStr: Pointer;

function CertNameToStr;
begin
  GetProcedureAddress(_CertNameToStr, crypt32, 'CertNameToStrA');
  asm
    mov esp, ebp
    pop ebp
    jmp [_CertNameToStr]
  end;
end;
{$ELSE}
function CertNameToStr; external crypt32 name 'CertNameToStrA';
{$ENDIF DYNAMIC_LINK}
{$ENDIF}

{$IFDEF DYNAMIC_LINK}
var
  _CertStrToNameA: Pointer;

function CertStrToNameA;
begin
  GetProcedureAddress(_CertStrToNameA, crypt32, 'CertStrToNameA');
  asm
    mov esp, ebp
    pop ebp
    jmp [_CertStrToNameA]
  end;
end;
{$ELSE}
function CertStrToNameA; external crypt32 name 'CertStrToNameA';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _CertStrToNameW: Pointer;

function CertStrToNameW;
begin
  GetProcedureAddress(_CertStrToNameW, crypt32, 'CertStrToNameW');
  asm
    mov esp, ebp
    pop ebp
    jmp [_CertStrToNameW]
  end;
end;
{$ELSE}
function CertStrToNameW; external crypt32 name 'CertStrToNameW';
{$ENDIF DYNAMIC_LINK}
{$IFDEF UNICODE}

{$IFDEF DYNAMIC_LINK}
var
  _CertStrToName: Pointer;

function CertStrToName;
begin
  GetProcedureAddress(_CertStrToName, crypt32, 'CertStrToNameW');
  asm
    mov esp, ebp
    pop ebp
    jmp [_CertStrToName]
  end;
end;
{$ELSE}
function CertStrToName; external crypt32 name 'CertStrToNameW';
{$ENDIF DYNAMIC_LINK}
{$ELSE}

{$IFDEF DYNAMIC_LINK}
var
  _CertStrToName: Pointer;

function CertStrToName;
begin
  GetProcedureAddress(_CertStrToName, crypt32, 'CertStrToNameA');
  asm
    mov esp, ebp
    pop ebp
    jmp [_CertStrToName]
  end;
end;
{$ELSE}
function CertStrToName; external crypt32 name 'CertStrToNameA';
{$ENDIF DYNAMIC_LINK}
{$ENDIF}

{$IFDEF DYNAMIC_LINK}
var
  _CertGetNameStringA: Pointer;

function CertGetNameStringA;
begin
  GetProcedureAddress(_CertGetNameStringA, crypt32, 'CertGetNameStringA');
  asm
    mov esp, ebp
    pop ebp
    jmp [_CertGetNameStringA]
  end;
end;
{$ELSE}
function CertGetNameStringA; external crypt32 name 'CertGetNameStringA';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _CertGetNameStringW: Pointer;

function CertGetNameStringW;
begin
  GetProcedureAddress(_CertGetNameStringW, crypt32, 'CertGetNameStringW');
  asm
    mov esp, ebp
    pop ebp
    jmp [_CertGetNameStringW]
  end;
end;
{$ELSE}
function CertGetNameStringW; external crypt32 name 'CertGetNameStringW';
{$ENDIF DYNAMIC_LINK}
{$IFDEF UNICODE}

{$IFDEF DYNAMIC_LINK}
var
  _CertGetNameString: Pointer;

function CertGetNameString;
begin
  GetProcedureAddress(_CertGetNameString, crypt32, 'CertGetNameStringW');
  asm
    mov esp, ebp
    pop ebp
    jmp [_CertGetNameString]
  end;
end;
{$ELSE}
function CertGetNameString; external crypt32 name 'CertGetNameStringW';
{$ENDIF DYNAMIC_LINK}
{$ELSE}

{$IFDEF DYNAMIC_LINK}
var
  _CertGetNameString: Pointer;

function CertGetNameString;
begin
  GetProcedureAddress(_CertGetNameString, crypt32, 'CertGetNameStringA');
  asm
    mov esp, ebp
    pop ebp
    jmp [_CertGetNameString]
  end;
end;
{$ELSE}
function CertGetNameString; external crypt32 name 'CertGetNameStringA';
{$ENDIF DYNAMIC_LINK}
{$ENDIF}

{$IFDEF DYNAMIC_LINK}
var
  _CryptSignMessage: Pointer;

function CryptSignMessage;
begin
  GetProcedureAddress(_CryptSignMessage, crypt32, 'CryptSignMessage');
  asm
    mov esp, ebp
    pop ebp
    jmp [_CryptSignMessage]
  end;
end;
{$ELSE}
function CryptSignMessage; external crypt32 name 'CryptSignMessage';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _CryptVerifyMessageSignature: Pointer;

function CryptVerifyMessageSignature;
begin
  GetProcedureAddress(_CryptVerifyMessageSignature, crypt32, 'CryptVerifyMessageSignature');
  asm
    mov esp, ebp
    pop ebp
    jmp [_CryptVerifyMessageSignature]
  end;
end;
{$ELSE}
function CryptVerifyMessageSignature; external crypt32 name 'CryptVerifyMessageSignature';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _CryptGetMessageSignerCount: Pointer;

function CryptGetMessageSignerCount;
begin
  GetProcedureAddress(_CryptGetMessageSignerCount, crypt32, 'CryptGetMessageSignerCount');
  asm
    mov esp, ebp
    pop ebp
    jmp [_CryptGetMessageSignerCount]
  end;
end;
{$ELSE}
function CryptGetMessageSignerCount; external crypt32 name 'CryptGetMessageSignerCount';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _CryptGetMessageCertificates: Pointer;

function CryptGetMessageCertificates;
begin
  GetProcedureAddress(_CryptGetMessageCertificates, crypt32, 'CryptGetMessageCertificates');
  asm
    mov esp, ebp
    pop ebp
    jmp [_CryptGetMessageCertificates]
  end;
end;
{$ELSE}
function CryptGetMessageCertificates; external crypt32 name 'CryptGetMessageCertificates';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _CryptVerDetachedMsgSignature: Pointer;

function CryptVerifyDetachedMessageSignature;
begin
  GetProcedureAddress(_CryptVerDetachedMsgSignature, crypt32, 'CryptVerifyDetachedMessageSignature');
  asm
    mov esp, ebp
    pop ebp
    jmp [_CryptVerDetachedMsgSignature]
  end;
end;
{$ELSE}
function CryptVerifyDetachedMessageSignature; external crypt32 name 'CryptVerifyDetachedMessageSignature';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _CryptEncryptMessage: Pointer;

function CryptEncryptMessage;
begin
  GetProcedureAddress(_CryptEncryptMessage, crypt32, 'CryptEncryptMessage');
  asm
    mov esp, ebp
    pop ebp
    jmp [_CryptEncryptMessage]
  end;
end;
{$ELSE}
function CryptEncryptMessage; external crypt32 name 'CryptEncryptMessage';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _CryptDecryptMessage: Pointer;

function CryptDecryptMessage;
begin
  GetProcedureAddress(_CryptDecryptMessage, crypt32, 'CryptDecryptMessage');
  asm
    mov esp, ebp
    pop ebp
    jmp [_CryptDecryptMessage]
  end;
end;
{$ELSE}
function CryptDecryptMessage; external crypt32 name 'CryptDecryptMessage';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _CryptSignAndEncryptMessage: Pointer;

function CryptSignAndEncryptMessage;
begin
  GetProcedureAddress(_CryptSignAndEncryptMessage, crypt32, 'CryptSignAndEncryptMessage');
  asm
    mov esp, ebp
    pop ebp
    jmp [_CryptSignAndEncryptMessage]
  end;
end;
{$ELSE}
function CryptSignAndEncryptMessage; external crypt32 name 'CryptSignAndEncryptMessage';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _CryptDecryptAndVerMsgSig: Pointer;

function CryptDecryptAndVerifyMessageSignature;
begin
  GetProcedureAddress(_CryptDecryptAndVerMsgSig, crypt32, 'CryptDecryptAndVerifyMessageSignature');
  asm
    mov esp, ebp
    pop ebp
    jmp [_CryptDecryptAndVerMsgSig]
  end;
end;
{$ELSE}
function CryptDecryptAndVerifyMessageSignature; external crypt32 name 'CryptDecryptAndVerifyMessageSignature';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _CryptDecodeMessage: Pointer;

function CryptDecodeMessage;
begin
  GetProcedureAddress(_CryptDecodeMessage, crypt32, 'CryptDecodeMessage');
  asm
    mov esp, ebp
    pop ebp
    jmp [_CryptDecodeMessage]
  end;
end;
{$ELSE}
function CryptDecodeMessage; external crypt32 name 'CryptDecodeMessage';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _CryptHashMessage: Pointer;

function CryptHashMessage;
begin
  GetProcedureAddress(_CryptHashMessage, crypt32, 'CryptHashMessage');
  asm
    mov esp, ebp
    pop ebp
    jmp [_CryptHashMessage]
  end;
end;
{$ELSE}
function CryptHashMessage; external crypt32 name 'CryptHashMessage';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _CryptVerifyMessageHash: Pointer;

function CryptVerifyMessageHash;
begin
  GetProcedureAddress(_CryptVerifyMessageHash, crypt32, 'CryptVerifyMessageHash');
  asm
    mov esp, ebp
    pop ebp
    jmp [_CryptVerifyMessageHash]
  end;
end;
{$ELSE}
function CryptVerifyMessageHash; external crypt32 name 'CryptVerifyMessageHash';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _CryptVerifyDetachedMessageHash: Pointer;

function CryptVerifyDetachedMessageHash;
begin
  GetProcedureAddress(_CryptVerifyDetachedMessageHash, crypt32, 'CryptVerifyDetachedMessageHash');
  asm
    mov esp, ebp
    pop ebp
    jmp [_CryptVerifyDetachedMessageHash]
  end;
end;
{$ELSE}
function CryptVerifyDetachedMessageHash; external crypt32 name 'CryptVerifyDetachedMessageHash';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _CryptSignMessageWithKey: Pointer;

function CryptSignMessageWithKey;
begin
  GetProcedureAddress(_CryptSignMessageWithKey, crypt32, 'CryptSignMessageWithKey');
  asm
    mov esp, ebp
    pop ebp
    jmp [_CryptSignMessageWithKey]
  end;
end;
{$ELSE}
function CryptSignMessageWithKey; external crypt32 name 'CryptSignMessageWithKey';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _CryptVerifyMsgSigWithKey: Pointer;

function CryptVerifyMessageSignatureWithKey;
begin
  GetProcedureAddress(_CryptVerifyMsgSigWithKey, crypt32, 'CryptVerifyMessageSignatureWithKey');
  asm
    mov esp, ebp
    pop ebp
    jmp [_CryptVerifyMsgSigWithKey]
  end;
end;
{$ELSE}
function CryptVerifyMessageSignatureWithKey; external crypt32 name 'CryptVerifyMessageSignatureWithKey';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _CertOpenSystemStoreA: Pointer;

function CertOpenSystemStoreA;
begin
  GetProcedureAddress(_CertOpenSystemStoreA, crypt32, 'CertOpenSystemStoreA');
  asm
    mov esp, ebp
    pop ebp
    jmp [_CertOpenSystemStoreA]
  end;
end;
{$ELSE}
function CertOpenSystemStoreA; external crypt32 name 'CertOpenSystemStoreA';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _CertOpenSystemStoreW: Pointer;

function CertOpenSystemStoreW;
begin
  GetProcedureAddress(_CertOpenSystemStoreW, crypt32, 'CertOpenSystemStoreW');
  asm
    mov esp, ebp
    pop ebp
    jmp [_CertOpenSystemStoreW]
  end;
end;
{$ELSE}
function CertOpenSystemStoreW; external crypt32 name 'CertOpenSystemStoreW';
{$ENDIF DYNAMIC_LINK}
{$IFDEF UNICODE}

{$IFDEF DYNAMIC_LINK}
var
  _CertOpenSystemStore: Pointer;

function CertOpenSystemStore;
begin
  GetProcedureAddress(_CertOpenSystemStore, crypt32, 'CertOpenSystemStoreW');
  asm
    mov esp, ebp
    pop ebp
    jmp [_CertOpenSystemStore]
  end;
end;
{$ELSE}
function CertOpenSystemStore; external crypt32 name 'CertOpenSystemStoreW';
{$ENDIF DYNAMIC_LINK}
{$ELSE}

{$IFDEF DYNAMIC_LINK}
var
  _CertOpenSystemStore: Pointer;

function CertOpenSystemStore;
begin
  GetProcedureAddress(_CertOpenSystemStore, crypt32, 'CertOpenSystemStoreA');
  asm
    mov esp, ebp
    pop ebp
    jmp [_CertOpenSystemStore]
  end;
end;
{$ELSE}
function CertOpenSystemStore; external crypt32 name 'CertOpenSystemStoreA';
{$ENDIF DYNAMIC_LINK}
{$ENDIF}

{$IFDEF DYNAMIC_LINK}
var
  _CertAddEncodedCertToSysStoreA: Pointer;

function CertAddEncodedCertificateToSystemStoreA;
begin
  GetProcedureAddress(_CertAddEncodedCertToSysStoreA, crypt32, 'CertAddEncodedCertificateToSystemStoreA');
  asm
    mov esp, ebp
    pop ebp
    jmp [_CertAddEncodedCertToSysStoreA]
  end;
end;
{$ELSE}
function CertAddEncodedCertificateToSystemStoreA; external crypt32 name 'CertAddEncodedCertificateToSystemStoreA';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _CertAddEncodedCertToSysStoreW: Pointer;

function CertAddEncodedCertificateToSystemStoreW;
begin
  GetProcedureAddress(_CertAddEncodedCertToSysStoreW, crypt32, 'CertAddEncodedCertificateToSystemStoreW');
  asm
    mov esp, ebp
    pop ebp
    jmp [_CertAddEncodedCertToSysStoreW]
  end;
end;
{$ELSE}
function CertAddEncodedCertificateToSystemStoreW; external crypt32 name 'CertAddEncodedCertificateToSystemStoreW';
{$ENDIF DYNAMIC_LINK}
{$IFDEF UNICODE}

{$IFDEF DYNAMIC_LINK}
var
  _CertAddEncodedCertToSysStore: Pointer;

function CertAddEncodedCertificateToSystemStore;
begin
  GetProcedureAddress(_CertAddEncodedCertToSysStore, crypt32, 'CertAddEncodedCertificateToSystemStoreW');
  asm
    mov esp, ebp
    pop ebp
    jmp [_CertAddEncodedCertToSysStore]
  end;
end;
{$ELSE}
function CertAddEncodedCertificateToSystemStore; external crypt32 name 'CertAddEncodedCertificateToSystemStoreW';
{$ENDIF DYNAMIC_LINK}
{$ELSE}

{$IFDEF DYNAMIC_LINK}
var
  _CertAddEncodedCertToSysStore: Pointer;

function CertAddEncodedCertificateToSystemStore;
begin
  GetProcedureAddress(_CertAddEncodedCertToSysStore, crypt32, 'CertAddEncodedCertificateToSystemStoreA');
  asm
    mov esp, ebp
    pop ebp
    jmp [_CertAddEncodedCertToSysStore]
  end;
end;
{$ELSE}
function CertAddEncodedCertificateToSystemStore; external crypt32 name 'CertAddEncodedCertificateToSystemStoreA';
{$ENDIF DYNAMIC_LINK}
{$ENDIF}

{$IFDEF DYNAMIC_LINK}
var
  _FindCertsByIssuer: Pointer;

function FindCertsByIssuer;
begin
  GetProcedureAddress(_FindCertsByIssuer, softpub, 'FindCertsByIssuer');
  asm
    mov esp, ebp
    pop ebp
    jmp [_FindCertsByIssuer]
  end;
end;
{$ELSE}
function FindCertsByIssuer; external softpub name 'FindCertsByIssuer';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _CryptQueryObject: Pointer;

function CryptQueryObject;
begin
  GetProcedureAddress(_CryptQueryObject, crypt32, 'CryptQueryObject');
  asm
    mov esp, ebp
    pop ebp
    jmp [_CryptQueryObject]
  end;
end;
{$ELSE}
function CryptQueryObject; external crypt32 name 'CryptQueryObject';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _CryptMemAlloc: Pointer;

function CryptMemAlloc;
begin
  GetProcedureAddress(_CryptMemAlloc, crypt32, 'CryptMemAlloc');
  asm
    mov esp, ebp
    pop ebp
    jmp [_CryptMemAlloc]
  end;
end;
{$ELSE}
function CryptMemAlloc; external crypt32 name 'CryptMemAlloc';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _CryptMemRealloc: Pointer;

function CryptMemRealloc;
begin
  GetProcedureAddress(_CryptMemRealloc, crypt32, 'CryptMemRealloc');
  asm
    mov esp, ebp
    pop ebp
    jmp [_CryptMemRealloc]
  end;
end;
{$ELSE}
function CryptMemRealloc; external crypt32 name 'CryptMemRealloc';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _CryptMemFree: Pointer;

procedure CryptMemFree;
begin
  GetProcedureAddress(_CryptMemFree, crypt32, 'CryptMemFree');
  asm
    mov esp, ebp
    pop ebp
    jmp [_CryptMemFree]
  end;
end;
{$ELSE}
procedure CryptMemFree; external crypt32 name 'CryptMemFree';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _CryptCreateAsyncHandle: Pointer;

function CryptCreateAsyncHandle;
begin
  GetProcedureAddress(_CryptCreateAsyncHandle, crypt32, 'CryptCreateAsyncHandle');
  asm
    mov esp, ebp
    pop ebp
    jmp [_CryptCreateAsyncHandle]
  end;
end;
{$ELSE}
function CryptCreateAsyncHandle; external crypt32 name 'CryptCreateAsyncHandle';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _CryptSetAsyncParam: Pointer;

function CryptSetAsyncParam;
begin
  GetProcedureAddress(_CryptSetAsyncParam, crypt32, 'CryptSetAsyncParam');
  asm
    mov esp, ebp
    pop ebp
    jmp [_CryptSetAsyncParam]
  end;
end;
{$ELSE}
function CryptSetAsyncParam; external crypt32 name 'CryptSetAsyncParam';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _CryptGetAsyncParam: Pointer;

function CryptGetAsyncParam;
begin
  GetProcedureAddress(_CryptGetAsyncParam, crypt32, 'CryptGetAsyncParam');
  asm
    mov esp, ebp
    pop ebp
    jmp [_CryptGetAsyncParam]
  end;
end;
{$ELSE}
function CryptGetAsyncParam; external crypt32 name 'CryptGetAsyncParam';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _CryptCloseAsyncHandle: Pointer;

function CryptCloseAsyncHandle;
begin
  GetProcedureAddress(_CryptCloseAsyncHandle, crypt32, 'CryptCloseAsyncHandle');
  asm
    mov esp, ebp
    pop ebp
    jmp [_CryptCloseAsyncHandle]
  end;
end;
{$ELSE}
function CryptCloseAsyncHandle; external crypt32 name 'CryptCloseAsyncHandle';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _CryptRetrieveObjectByUrlA: Pointer;

function CryptRetrieveObjectByUrlA;
begin
  GetProcedureAddress(_CryptRetrieveObjectByUrlA, crypt32, 'CryptRetrieveObjectByUrlA');
  asm
    mov esp, ebp
    pop ebp
    jmp [_CryptRetrieveObjectByUrlA]
  end;
end;
{$ELSE}
function CryptRetrieveObjectByUrlA; external crypt32 name 'CryptRetrieveObjectByUrlA';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _CryptRetrieveObjectByUrlW: Pointer;

function CryptRetrieveObjectByUrlW;
begin
  GetProcedureAddress(_CryptRetrieveObjectByUrlW, crypt32, 'CryptRetrieveObjectByUrlW');
  asm
    mov esp, ebp
    pop ebp
    jmp [_CryptRetrieveObjectByUrlW]
  end;
end;
{$ELSE}
function CryptRetrieveObjectByUrlW; external crypt32 name 'CryptRetrieveObjectByUrlW';
{$ENDIF DYNAMIC_LINK}
{$IFDEF UNICODE}

{$IFDEF DYNAMIC_LINK}
var
  _CryptRetrieveObjectByUrl: Pointer;

function CryptRetrieveObjectByUrl;
begin
  GetProcedureAddress(_CryptRetrieveObjectByUrl, crypt32, 'CryptRetrieveObjectByUrlW');
  asm
    mov esp, ebp
    pop ebp
    jmp [_CryptRetrieveObjectByUrl]
  end;
end;
{$ELSE}
function CryptRetrieveObjectByUrl; external crypt32 name 'CryptRetrieveObjectByUrlW';
{$ENDIF DYNAMIC_LINK}
{$ELSE}

{$IFDEF DYNAMIC_LINK}
var
  _CryptRetrieveObjectByUrl: Pointer;

function CryptRetrieveObjectByUrl;
begin
  GetProcedureAddress(_CryptRetrieveObjectByUrl, crypt32, 'CryptRetrieveObjectByUrlA');
  asm
    mov esp, ebp
    pop ebp
    jmp [_CryptRetrieveObjectByUrl]
  end;
end;
{$ELSE}
function CryptRetrieveObjectByUrl; external crypt32 name 'CryptRetrieveObjectByUrlA';
{$ENDIF DYNAMIC_LINK}
{$ENDIF}

{$IFDEF DYNAMIC_LINK}
var
  _CryptInstallCancelRetrieval: Pointer;

function CryptInstallCancelRetrieval;
begin
  GetProcedureAddress(_CryptInstallCancelRetrieval, crypt32, 'CryptInstallCancelRetrieval');
  asm
    mov esp, ebp
    pop ebp
    jmp [_CryptInstallCancelRetrieval]
  end;
end;
{$ELSE}
function CryptInstallCancelRetrieval; external crypt32 name 'CryptInstallCancelRetrieval';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _CryptUninstallCancelRetrieval: Pointer;

function CryptUninstallCancelRetrieval;
begin
  GetProcedureAddress(_CryptUninstallCancelRetrieval, crypt32, 'CryptUninstallCancelRetrieval');
  asm
    mov esp, ebp
    pop ebp
    jmp [_CryptUninstallCancelRetrieval]
  end;
end;
{$ELSE}
function CryptUninstallCancelRetrieval; external crypt32 name 'CryptUninstallCancelRetrieval';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _CryptCancelAsyncRetrieval: Pointer;

function CryptCancelAsyncRetrieval;
begin
  GetProcedureAddress(_CryptCancelAsyncRetrieval, crypt32, 'CryptCancelAsyncRetrieval');
  asm
    mov esp, ebp
    pop ebp
    jmp [_CryptCancelAsyncRetrieval]
  end;
end;
{$ELSE}
function CryptCancelAsyncRetrieval; external crypt32 name 'CryptCancelAsyncRetrieval';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _CryptGetObjectUrl: Pointer;

function CryptGetObjectUrl;
begin
  GetProcedureAddress(_CryptGetObjectUrl, crypt32, 'CryptGetObjectUrl');
  asm
    mov esp, ebp
    pop ebp
    jmp [_CryptGetObjectUrl]
  end;
end;
{$ELSE}
function CryptGetObjectUrl; external crypt32 name 'CryptGetObjectUrl';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _CryptGetTimeValidObject: Pointer;

function CryptGetTimeValidObject;
begin
  GetProcedureAddress(_CryptGetTimeValidObject, crypt32, 'CryptGetTimeValidObject');
  asm
    mov esp, ebp
    pop ebp
    jmp [_CryptGetTimeValidObject]
  end;
end;
{$ELSE}
function CryptGetTimeValidObject; external crypt32 name 'CryptGetTimeValidObject';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _CryptFlushTimeValidObject: Pointer;

function CryptFlushTimeValidObject;
begin
  GetProcedureAddress(_CryptFlushTimeValidObject, crypt32, 'CryptFlushTimeValidObject');
  asm
    mov esp, ebp
    pop ebp
    jmp [_CryptFlushTimeValidObject]
  end;
end;
{$ELSE}
function CryptFlushTimeValidObject; external crypt32 name 'CryptFlushTimeValidObject';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _CryptProtectData: Pointer;

function CryptProtectData;
begin
  GetProcedureAddress(_CryptProtectData, crypt32, 'CryptProtectData');
  asm
    mov esp, ebp
    pop ebp
    jmp [_CryptProtectData]
  end;
end;
{$ELSE}
function CryptProtectData; external crypt32 name 'CryptProtectData';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _CryptUnprotectData: Pointer;

function CryptUnprotectData;
begin
  GetProcedureAddress(_CryptUnprotectData, crypt32, 'CryptUnprotectData');
  asm
    mov esp, ebp
    pop ebp
    jmp [_CryptUnprotectData]
  end;
end;
{$ELSE}
function CryptUnprotectData; external crypt32 name 'CryptUnprotectData';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _CertCreateSelfSignCertificate: Pointer;

function CertCreateSelfSignCertificate;
begin
  GetProcedureAddress(_CertCreateSelfSignCertificate, crypt32, 'CertCreateSelfSignCertificate');
  asm
    mov esp, ebp
    pop ebp
    jmp [_CertCreateSelfSignCertificate]
  end;
end;
{$ELSE}
function CertCreateSelfSignCertificate; external crypt32 name 'CertCreateSelfSignCertificate';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _CryptGetKeyIdentifierProperty: Pointer;

function CryptGetKeyIdentifierProperty;
begin
  GetProcedureAddress(_CryptGetKeyIdentifierProperty, crypt32, 'CryptGetKeyIdentifierProperty');
  asm
    mov esp, ebp
    pop ebp
    jmp [_CryptGetKeyIdentifierProperty]
  end;
end;
{$ELSE}
function CryptGetKeyIdentifierProperty; external crypt32 name 'CryptGetKeyIdentifierProperty';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _CryptSetKeyIdentifierProperty: Pointer;

function CryptSetKeyIdentifierProperty;
begin
  GetProcedureAddress(_CryptSetKeyIdentifierProperty, crypt32, 'CryptSetKeyIdentifierProperty');
  asm
    mov esp, ebp
    pop ebp
    jmp [_CryptSetKeyIdentifierProperty]
  end;
end;
{$ELSE}
function CryptSetKeyIdentifierProperty; external crypt32 name 'CryptSetKeyIdentifierProperty';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _CryptEnumKeyIdentProperties: Pointer;

function CryptEnumKeyIdentifierProperties;
begin
  GetProcedureAddress(_CryptEnumKeyIdentProperties, crypt32, 'CryptEnumKeyIdentifierProperties');
  asm
    mov esp, ebp
    pop ebp
    jmp [_CryptEnumKeyIdentProperties]
  end;
end;
{$ELSE}
function CryptEnumKeyIdentifierProperties; external crypt32 name 'CryptEnumKeyIdentifierProperties';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _CryptCreateKeyIdentifierFromCSP: Pointer;

function CryptCreateKeyIdentifierFromCSP;
begin
  GetProcedureAddress(_CryptCreateKeyIdentifierFromCSP, crypt32, 'CryptCreateKeyIdentifierFromCSP');
  asm
    mov esp, ebp
    pop ebp
    jmp [_CryptCreateKeyIdentifierFromCSP]
  end;
end;
{$ELSE}
function CryptCreateKeyIdentifierFromCSP; external crypt32 name 'CryptCreateKeyIdentifierFromCSP';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _CertCreateCertChainEngine: Pointer;

function CertCreateCertificateChainEngine;
begin
  GetProcedureAddress(_CertCreateCertChainEngine, crypt32, 'CertCreateCertificateChainEngine');
  asm
    mov esp, ebp
    pop ebp
    jmp [_CertCreateCertChainEngine]
  end;
end;
{$ELSE}
function CertCreateCertificateChainEngine; external crypt32 name 'CertCreateCertificateChainEngine';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _CertFreeCertificateChainEngine: Pointer;

procedure CertFreeCertificateChainEngine;
begin
  GetProcedureAddress(_CertFreeCertificateChainEngine, crypt32, 'CertFreeCertificateChainEngine');
  asm
    mov esp, ebp
    pop ebp
    jmp [_CertFreeCertificateChainEngine]
  end;
end;
{$ELSE}
procedure CertFreeCertificateChainEngine; external crypt32 name 'CertFreeCertificateChainEngine';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _CertResyncCertChainEngine: Pointer;

function CertResyncCertificateChainEngine;
begin
  GetProcedureAddress(_CertResyncCertChainEngine, crypt32, 'CertResyncCertificateChainEngine');
  asm
    mov esp, ebp
    pop ebp
    jmp [_CertResyncCertChainEngine]
  end;
end;
{$ELSE}
function CertResyncCertificateChainEngine; external crypt32 name 'CertResyncCertificateChainEngine';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _CertGetCertificateChain: Pointer;

function CertGetCertificateChain;
begin
  GetProcedureAddress(_CertGetCertificateChain, crypt32, 'CertGetCertificateChain');
  asm
    mov esp, ebp
    pop ebp
    jmp [_CertGetCertificateChain]
  end;
end;
{$ELSE}
function CertGetCertificateChain; external crypt32 name 'CertGetCertificateChain';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _CertFreeCertificateChain: Pointer;

procedure CertFreeCertificateChain;
begin
  GetProcedureAddress(_CertFreeCertificateChain, crypt32, 'CertFreeCertificateChain');
  asm
    mov esp, ebp
    pop ebp
    jmp [_CertFreeCertificateChain]
  end;
end;
{$ELSE}
procedure CertFreeCertificateChain; external crypt32 name 'CertFreeCertificateChain';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _CertDuplicateCertificateChain: Pointer;

function CertDuplicateCertificateChain;
begin
  GetProcedureAddress(_CertDuplicateCertificateChain, crypt32, 'CertDuplicateCertificateChain');
  asm
    mov esp, ebp
    pop ebp
    jmp [_CertDuplicateCertificateChain]
  end;
end;
{$ELSE}
function CertDuplicateCertificateChain; external crypt32 name 'CertDuplicateCertificateChain';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _CertFindChainInStore: Pointer;

function CertFindChainInStore;
begin
  GetProcedureAddress(_CertFindChainInStore, crypt32, 'CertFindChainInStore');
  asm
    mov esp, ebp
    pop ebp
    jmp [_CertFindChainInStore]
  end;
end;
{$ELSE}
function CertFindChainInStore; external crypt32 name 'CertFindChainInStore';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _CertVerifyCertChainPolicy: Pointer;

function CertVerifyCertificateChainPolicy;
begin
  GetProcedureAddress(_CertVerifyCertChainPolicy, crypt32, 'CertVerifyCertificateChainPolicy');
  asm
    mov esp, ebp
    pop ebp
    jmp [_CertVerifyCertChainPolicy]
  end;
end;
{$ELSE}
function CertVerifyCertificateChainPolicy; external crypt32 name 'CertVerifyCertificateChainPolicy';
{$ENDIF DYNAMIC_LINK}

end.
