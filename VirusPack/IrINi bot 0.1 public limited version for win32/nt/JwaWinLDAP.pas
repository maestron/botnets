{******************************************************************************}
{                                                       	               }
{ LDAP Client 32 API interface Unit for Object Pascal                          }
{                                                       	               }
{ Portions created by Microsoft are Copyright (C) 1995-2001 Microsoft          }
{ Corporation. All Rights Reserved.                                            }
{ 								               }
{ The original file is: winldap.h, released August 1999. The original Pascal   }
{ code is: WinLDAP.pas, released December 1998. The initial developer of the   }
{ Pascal code is Luk Vermeulen (lvermeulen@seria.com).                         }
{                                                                              }
{ Portions created by Luk Vermeulen are Copyright (C) 1998 Luk Vermeulen.      }
{ Portions created by Rudy Velthuis are Copyright (C) 2000 Rudy Velthuis.      }
{ Portions created by M. van Brakel are Copyright (C) 2001 Marcel van Brakel.  }
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
{******************************************************************************}

unit JwaWinLDAP;

{$WEAKPACKAGEUNIT}

interface

uses
  Windows;

{$HPPEMIT '#ifndef LDAP_CLIENT_DEFINED'}
{$HPPEMIT '#pragma option push -b -a8 -pc -A- /*P_O_Push_S*/'}
{$HPPEMIT '#define LDAP_CLIENT_DEFINED'}

{$HPPEMIT '#ifndef BASETYPES'}
{$HPPEMIT '#include <windef.h>'}
{$HPPEMIT '#endif'}

(*
Copyright (c) 1996-1999  Microsoft Corporation

Module Name:

    winldap.h   LDAP client 32 API header file

Abstract:

   This module is the header file for the 32 bit LDAP client API for
   Windows NT and Windows 95.  This API is based on RFC 1823 with some
   enhancements for LDAP v3.

   Notes about Unicode support :

   If you have UNICODE defined at compile time, you'll pull in the unicode
   versions of the calls.  Note that your executable may then not work with
   other implementations of the LDAP API that don't support Unicode.  If
   UNICODE is not defined, then we define the LDAP calls without the trailing
   'A'(as in ldap_bind rather than ldap_bindA)so that your app may work
   with other implementations that don't support Unicode.

   The import library has all three forms of the call present... ldap_bindW,
   ldap_bindA, and ldap_bind.  ldap_bindA simply calls ldap_bind.  ldap_bind
   simply converts the arguments to unicode and calls ldap_bindW.  The
   reason this is done is because we have to put UTF-8 on the wire, so if
   we converted from Unicode to single byte, we'd loose information.  Since
   all core processing is done in Unicode, nothing is lost.

Updates :

   11/01/96  Modified for new API RFC draft.

Environments :

    Win32 user mode

*)

// Extra defines to keep compiler happy.
type
  PPCharA = ^PAnsiChar;
  {$NODEFINE PPCharA}
  PPCharW = ^PWideChar;
  {$NODEFINE PPCharW}
  PPChar = PPCharA;

  PPPCharA = ^PPCharA;
  {$NODEFINE PPPCharA}
  PPPCharW = ^PPCharW;
  {$NODEFINE PPPCharW}
  PPPChar = PPPCharA;

//
//  The #define LDAP_UNICODE controls if we map the undecorated calls to
//  their unicode counterparts or just leave them defined as the normal
//  single byte entry points.
//
//  If you want to write a UNICODE enabled application, you'd normally
//  just have UNICODE defined and then we'll default to using all LDAP
//  Unicode calls.
//

const
  //
  //  Global constants
  //

  {$EXTERNALSYM LDAP_PORT}
  LDAP_PORT               = 389;
  {$EXTERNALSYM LDAP_SSL_PORT}
  LDAP_SSL_PORT           = 636;
  {$EXTERNALSYM LDAP_GC_PORT}
  LDAP_GC_PORT            = 3268;
  {$EXTERNALSYM LDAP_SSL_GC_PORT}
  LDAP_SSL_GC_PORT        = 3269;


//
//  We currently support going to either v2 or v3 servers, though the API
//  is only a V2 API.  We'll add support for result sets, server side
//  sorting, extended operations, etc as soon as they stabilize.
//

  {$EXTERNALSYM LDAP_VERSION1}
  LDAP_VERSION1          = 1;
  {$EXTERNALSYM LDAP_VERSION2}
  LDAP_VERSION2          = 2;
  {$EXTERNALSYM LDAP_VERSION3}
  LDAP_VERSION3          = 3;
  {$EXTERNALSYM LDAP_VERSION}
  LDAP_VERSION           = LDAP_VERSION2;

//
//  All tags are CCFTTTTT.
//               CC        Tag Class 00 = universal
//                                   01 = application wide
//                                   10 = context specific
//                                   11 = private use
//
//                 F       Form 0 primitive
//                              1 constructed
//
//                  TTTTT  Tag Number
//

//
// LDAP v2 & v3 commands.
//

  {$EXTERNALSYM LDAP_BIND_CMD}
  LDAP_BIND_CMD          = $60;   // application + constructed
  {$EXTERNALSYM LDAP_UNBIND_CMD}
  LDAP_UNBIND_CMD        = $42;   // application + primitive
  {$EXTERNALSYM LDAP_SEARCH_CMD}
  LDAP_SEARCH_CMD        = $63;   // application + constructed
  {$EXTERNALSYM LDAP_MODIFY_CMD}
  LDAP_MODIFY_CMD        = $66;   // application + constructed
  {$EXTERNALSYM LDAP_ADD_CMD}
  LDAP_ADD_CMD           = $68;   // application + constructed
  {$EXTERNALSYM LDAP_DELETE_CMD}
  LDAP_DELETE_CMD        = $4a;   // application + primitive
  {$EXTERNALSYM LDAP_MODRDN_CMD}
  LDAP_MODRDN_CMD        = $6c;   // application + constructed
  {$EXTERNALSYM LDAP_COMPARE_CMD}
  LDAP_COMPARE_CMD       = $6e;   // application + constructed
  {$EXTERNALSYM LDAP_ABANDON_CMD}
  LDAP_ABANDON_CMD       = $50;   // application + primitive
  {$EXTERNALSYM LDAP_SESSION_CMD}
  LDAP_SESSION_CMD       = $71;   // application + constructed
  {$EXTERNALSYM LDAP_EXTENDED_CMD}
  LDAP_EXTENDED_CMD      = $77;   // application + constructed

//
// Responses/Results for LDAP v2 & v3
//

  {$EXTERNALSYM LDAP_RES_BIND}
  LDAP_RES_BIND           = $61;   // application + constructed
  {$EXTERNALSYM LDAP_RES_SEARCH_ENTRY}
  LDAP_RES_SEARCH_ENTRY   = $64;   // application + constructed
  {$EXTERNALSYM LDAP_RES_SEARCH_RESULT}
  LDAP_RES_SEARCH_RESULT  = $65;   // application + constructed
  {$EXTERNALSYM LDAP_RES_MODIFY}
  LDAP_RES_MODIFY         = $67;   // application + constructed
  {$EXTERNALSYM LDAP_RES_ADD}
  LDAP_RES_ADD            = $69;   // application + constructed
  {$EXTERNALSYM LDAP_RES_DELETE}
  LDAP_RES_DELETE         = $6b;   // application + constructed
  {$EXTERNALSYM LDAP_RES_MODRDN}
  LDAP_RES_MODRDN         = $6d;   // application + constructed
  {$EXTERNALSYM LDAP_RES_COMPARE}
  LDAP_RES_COMPARE        = $6f;   // application + constructed
  {$EXTERNALSYM LDAP_RES_SESSION}
  LDAP_RES_SESSION        = $72;   // application + constructed
  {$EXTERNALSYM LDAP_RES_REFERRAL}
  LDAP_RES_REFERRAL       = $73;   // application + constructed
  {$EXTERNALSYM LDAP_RES_EXTENDED}
  LDAP_RES_EXTENDED       = $78;   // application + constructed
  {$EXTERNALSYM LDAP_RES_ANY}
  LDAP_RES_ANY            = -1;

  {$EXTERNALSYM LDAP_INVALID_CMD}
  LDAP_INVALID_CMD         = $FF;
  {$EXTERNALSYM LDAP_INVALID_RES}
  LDAP_INVALID_RES         = $FF;


//
// We'll make the error codes compatible with reference implementation
//

type
  {$EXTERNALSYM LDAP_RETCODE}
  LDAP_RETCODE = ULONG;

const
  {$EXTERNALSYM LDAP_SUCCESS}
  LDAP_SUCCESS                    =   $00;
  {$EXTERNALSYM LDAP_OPERATIONS_ERROR}
  LDAP_OPERATIONS_ERROR           =   $01;
  {$EXTERNALSYM LDAP_PROTOCOL_ERROR}
  LDAP_PROTOCOL_ERROR             =   $02;
  {$EXTERNALSYM LDAP_TIMELIMIT_EXCEEDED}
  LDAP_TIMELIMIT_EXCEEDED         =   $03;
  {$EXTERNALSYM LDAP_SIZELIMIT_EXCEEDED}
  LDAP_SIZELIMIT_EXCEEDED         =   $04;
  {$EXTERNALSYM LDAP_COMPARE_FALSE}
  LDAP_COMPARE_FALSE              =   $05;
  {$EXTERNALSYM LDAP_COMPARE_TRUE}
  LDAP_COMPARE_TRUE               =   $06;
  {$EXTERNALSYM LDAP_AUTH_METHOD_NOT_SUPPORTED}
  LDAP_AUTH_METHOD_NOT_SUPPORTED  =   $07;
  {$EXTERNALSYM LDAP_STRONG_AUTH_REQUIRED}
  LDAP_STRONG_AUTH_REQUIRED       =   $08;
  {$EXTERNALSYM LDAP_REFERRAL_V2}
  LDAP_REFERRAL_V2                =   $09;
  {$EXTERNALSYM LDAP_PARTIAL_RESULTS}
  LDAP_PARTIAL_RESULTS            =   $09;
  {$EXTERNALSYM LDAP_REFERRAL}
  LDAP_REFERRAL                   =   $0a;
  {$EXTERNALSYM LDAP_ADMIN_LIMIT_EXCEEDED}
  LDAP_ADMIN_LIMIT_EXCEEDED       =   $0b;
  {$EXTERNALSYM LDAP_UNAVAILABLE_CRIT_EXTENSION}
  LDAP_UNAVAILABLE_CRIT_EXTENSION =   $0c;
  {$EXTERNALSYM LDAP_CONFIDENTIALITY_REQUIRED}
  LDAP_CONFIDENTIALITY_REQUIRED   =   $0d;
  {$EXTERNALSYM LDAP_SASL_BIND_IN_PROGRESS}
  LDAP_SASL_BIND_IN_PROGRESS      =   $0e;


  {$EXTERNALSYM LDAP_NO_SUCH_ATTRIBUTE}
  LDAP_NO_SUCH_ATTRIBUTE          =   $10;
  {$EXTERNALSYM LDAP_UNDEFINED_TYPE}
  LDAP_UNDEFINED_TYPE             =   $11;
  {$EXTERNALSYM LDAP_INAPPROPRIATE_MATCHING}
  LDAP_INAPPROPRIATE_MATCHING     =   $12;
  {$EXTERNALSYM LDAP_CONSTRAINT_VIOLATION}
  LDAP_CONSTRAINT_VIOLATION       =   $13;
  {$EXTERNALSYM LDAP_ATTRIBUTE_OR_VALUE_EXISTS}
  LDAP_ATTRIBUTE_OR_VALUE_EXISTS  =   $14;
  {$EXTERNALSYM LDAP_INVALID_SYNTAX}
  LDAP_INVALID_SYNTAX             =   $15;

  {$EXTERNALSYM LDAP_NO_SUCH_OBJECT}
  LDAP_NO_SUCH_OBJECT             =   $20;
  {$EXTERNALSYM LDAP_ALIAS_PROBLEM}
  LDAP_ALIAS_PROBLEM              =   $21;
  {$EXTERNALSYM LDAP_INVALID_DN_SYNTAX}
  LDAP_INVALID_DN_SYNTAX          =   $22;
  {$EXTERNALSYM LDAP_IS_LEAF}
  LDAP_IS_LEAF                    =   $23;
  {$EXTERNALSYM LDAP_ALIAS_DEREF_PROBLEM}
  LDAP_ALIAS_DEREF_PROBLEM        =   $24;

  {$EXTERNALSYM LDAP_INAPPROPRIATE_AUTH}
  LDAP_INAPPROPRIATE_AUTH         =   $30;
  {$EXTERNALSYM LDAP_INVALID_CREDENTIALS}
  LDAP_INVALID_CREDENTIALS        =   $31;
  {$EXTERNALSYM LDAP_INSUFFICIENT_RIGHTS}
  LDAP_INSUFFICIENT_RIGHTS        =   $32;
  {$EXTERNALSYM LDAP_BUSY}
  LDAP_BUSY                       =   $33;
  {$EXTERNALSYM LDAP_UNAVAILABLE}
  LDAP_UNAVAILABLE                =   $34;
  {$EXTERNALSYM LDAP_UNWILLING_TO_PERFORM}
  LDAP_UNWILLING_TO_PERFORM       =   $35;
  {$EXTERNALSYM LDAP_LOOP_DETECT}
  LDAP_LOOP_DETECT                =   $36;

  {$EXTERNALSYM LDAP_NAMING_VIOLATION}
  LDAP_NAMING_VIOLATION           =   $40;
  {$EXTERNALSYM LDAP_OBJECT_CLASS_VIOLATION}
  LDAP_OBJECT_CLASS_VIOLATION     =   $41;
  {$EXTERNALSYM LDAP_NOT_ALLOWED_ON_NONLEAF}
  LDAP_NOT_ALLOWED_ON_NONLEAF     =   $42;
  {$EXTERNALSYM LDAP_NOT_ALLOWED_ON_RDN}
  LDAP_NOT_ALLOWED_ON_RDN         =   $43;
  {$EXTERNALSYM LDAP_ALREADY_EXISTS}
  LDAP_ALREADY_EXISTS             =   $44;
  {$EXTERNALSYM LDAP_NO_OBJECT_CLASS_MODS}
  LDAP_NO_OBJECT_CLASS_MODS       =   $45;
  {$EXTERNALSYM LDAP_RESULTS_TOO_LARGE}
  LDAP_RESULTS_TOO_LARGE          =   $46;
  {$EXTERNALSYM LDAP_AFFECTS_MULTIPLE_DSAS}
  LDAP_AFFECTS_MULTIPLE_DSAS      =   $47;

  {$EXTERNALSYM LDAP_OTHER}
  LDAP_OTHER                      =   $50;
  {$EXTERNALSYM LDAP_SERVER_DOWN}
  LDAP_SERVER_DOWN                =   $51;
  {$EXTERNALSYM LDAP_LOCAL_ERROR}
  LDAP_LOCAL_ERROR                =   $52;
  {$EXTERNALSYM LDAP_ENCODING_ERROR}
  LDAP_ENCODING_ERROR             =   $53;
  {$EXTERNALSYM LDAP_DECODING_ERROR}
  LDAP_DECODING_ERROR             =   $54;
  {$EXTERNALSYM LDAP_TIMEOUT}
  LDAP_TIMEOUT                    =   $55;
  {$EXTERNALSYM LDAP_AUTH_UNKNOWN}
  LDAP_AUTH_UNKNOWN               =   $56;
  {$EXTERNALSYM LDAP_FILTER_ERROR}
  LDAP_FILTER_ERROR               =   $57;
  {$EXTERNALSYM LDAP_USER_CANCELLED}
  LDAP_USER_CANCELLED             =   $58;
  {$EXTERNALSYM LDAP_PARAM_ERROR}
  LDAP_PARAM_ERROR                =   $59;
  {$EXTERNALSYM LDAP_NO_MEMORY}
  LDAP_NO_MEMORY                  =   $5a;
  {$EXTERNALSYM LDAP_CONNECT_ERROR}
  LDAP_CONNECT_ERROR              =   $5b;
  {$EXTERNALSYM LDAP_NOT_SUPPORTED}
  LDAP_NOT_SUPPORTED              =   $5c;
  {$EXTERNALSYM LDAP_NO_RESULTS_RETURNED}
  LDAP_NO_RESULTS_RETURNED        =   $5e;
  {$EXTERNALSYM LDAP_CONTROL_NOT_FOUND}
  LDAP_CONTROL_NOT_FOUND          =   $5d;
  {$EXTERNALSYM LDAP_MORE_RESULTS_TO_RETURN}
  LDAP_MORE_RESULTS_TO_RETURN     =   $5f;

  {$EXTERNALSYM LDAP_CLIENT_LOOP}
  LDAP_CLIENT_LOOP                =   $60;
  {$EXTERNALSYM LDAP_REFERRAL_LIMIT_EXCEEDED}
  LDAP_REFERRAL_LIMIT_EXCEEDED    =   $61;


//
//  Bind methods.  We support the following methods :
//
//      Simple         Clear text password... try not to use as it's not secure.
//
//      MSN            MSN(Microsoft Network)authentication. This package
//                     may bring up UI to prompt the user for MSN credentials.
//
//      DPA            Normandy authentication... new MSN authentication.  Same
//                     usage as MSN.
//
//      NTLM           NT domain authentication.  Use NULL credentials and
//                     we'll try to use default logged in user credentials.
//
//      Sicily         Negotiate with the server for any of: MSN, DPA, NTLM
//
//      SSPI           Use GSSAPI Negotiate package to negotiate security
//                     package of either Kerberos v5 or NTLM(or any other
//                     package the client and server negotiate).  Pass in
//                     NULL credentials to specify default logged in user or
//                     you may pass in a SEC_WINNT_AUTH_IDENTITY_W(defined
//                     in rpcdce.h)to specify alternate credentials.
//
//  For all bind methods except for Simple, you may pass in a
//  SEC_WINNT_AUTH_IDENTITY_W (defined in rpcdce.h) or the newer
//  SEC_WINNT_AUTH_IDENTITY_EXW (defined in secext.h) to specify alternate
//  credentials.
//
//  All bind methods other than simple are synchronous only calls.
//  Calling the asynchronous bind call for any of these messages will
//  return LDAP_PARAM_ERROR.
//
//  Using any other method besides simple will cause WLDAP32 to pull in
//  the SSPI security DLLs(SECURITY.DLL etc).
//
//  On NTLM and SSPI, if you specify NULL credentials, we'll attempt to use
//  the default logged in user.
//

const
  {$EXTERNALSYM LDAP_AUTH_SIMPLE}
  LDAP_AUTH_SIMPLE                = $80;
  {$EXTERNALSYM LDAP_AUTH_SASL}
  LDAP_AUTH_SASL                  = $83;

  {$EXTERNALSYM LDAP_AUTH_OTHERKIND}
  LDAP_AUTH_OTHERKIND             = $86;

// The SICILY type covers package negotiation to MSN servers.
// Each of the supported types can also be specified without
// doing the package negotiation, assuming the caller knows
// what the server supports.

  {$EXTERNALSYM LDAP_AUTH_SICILY}
  LDAP_AUTH_SICILY                = LDAP_AUTH_OTHERKIND or $0200;

  {$EXTERNALSYM LDAP_AUTH_MSN}
  LDAP_AUTH_MSN                   = LDAP_AUTH_OTHERKIND or $0800;
  {$EXTERNALSYM LDAP_AUTH_NTLM}
  LDAP_AUTH_NTLM                  = LDAP_AUTH_OTHERKIND or $1000;
  {$EXTERNALSYM LDAP_AUTH_DPA}
  LDAP_AUTH_DPA                   = LDAP_AUTH_OTHERKIND or $2000;

// This will cause the client to use the GSSAPI negotiation
// package to determine the most appropriate authentication type.
// This type should be used when talking to NT5.

  {$EXTERNALSYM LDAP_AUTH_NEGOTIATE}
  LDAP_AUTH_NEGOTIATE             = LDAP_AUTH_OTHERKIND or $0400;

// backward compatible #define for older constant name.

  {$EXTERNALSYM LDAP_AUTH_SSPI}
  LDAP_AUTH_SSPI                  = LDAP_AUTH_NEGOTIATE;

//
//  Client applications typically don't have to encode/decode LDAP filters,
//  but if they do, we define the operators here.
//
//  Filter types.

  {$EXTERNALSYM LDAP_FILTER_AND}
  LDAP_FILTER_AND         = $a0;    // context specific + constructed - SET OF Filters.
  {$EXTERNALSYM LDAP_FILTER_OR}
  LDAP_FILTER_OR          = $a1;    // context specific + constructed - SET OF Filters.
  {$EXTERNALSYM LDAP_FILTER_NOT}
  LDAP_FILTER_NOT         = $a2;    // context specific + constructed - Filter
  {$EXTERNALSYM LDAP_FILTER_EQUALITY}
  LDAP_FILTER_EQUALITY    = $a3;    // context specific + constructed - AttributeValueAssertion.
  {$EXTERNALSYM LDAP_FILTER_SUBSTRINGS}
  LDAP_FILTER_SUBSTRINGS  = $a4;    // context specific + constructed - SubstringFilter
  {$EXTERNALSYM LDAP_FILTER_GE}
  LDAP_FILTER_GE          = $a5;    // context specific + constructed - AttributeValueAssertion.
  {$EXTERNALSYM LDAP_FILTER_LE}
  LDAP_FILTER_LE          = $a6;    // context specific + constructed - AttributeValueAssertion.
  {$EXTERNALSYM LDAP_FILTER_PRESENT}
  LDAP_FILTER_PRESENT     = $87;    // context specific + primitive   - AttributeType.
  {$EXTERNALSYM LDAP_FILTER_APPROX}
  LDAP_FILTER_APPROX      = $a8;    // context specific + constructed - AttributeValueAssertion.
  {$EXTERNALSYM LDAP_FILTER_EXTENSIBLE}
  LDAP_FILTER_EXTENSIBLE  = $a9;    // context specific + constructed - MatchingRuleAssertion.

//  Substring filter types

  {$EXTERNALSYM LDAP_SUBSTRING_INITIAL}
  LDAP_SUBSTRING_INITIAL  = $80;   // class context specific
  {$EXTERNALSYM LDAP_SUBSTRING_ANY}
  LDAP_SUBSTRING_ANY      = $81;   // class context specific
  {$EXTERNALSYM LDAP_SUBSTRING_FINAL}
  LDAP_SUBSTRING_FINAL    = $82;   // class context specific

//
//  Possible values for ld_deref field.
//      "Never"     - never deref aliases.  return only the alias.
//      "Searching" - only deref aliases when searching, not when locating
//                    the base object of a search.
//      "Finding"   - dereference the alias when locating the base object but
//                    not during a search.
//      "Always"    - always dereference aliases.
//

  {$EXTERNALSYM LDAP_DEREF_NEVER}
  LDAP_DEREF_NEVER        = 0;
  {$EXTERNALSYM LDAP_DEREF_SEARCHING}
  LDAP_DEREF_SEARCHING    = 1;
  {$EXTERNALSYM LDAP_DEREF_FINDING}
  LDAP_DEREF_FINDING      = 2;
  {$EXTERNALSYM LDAP_DEREF_ALWAYS}
  LDAP_DEREF_ALWAYS       = 3;

//  Special values for ld_sizelimit :

  {$EXTERNALSYM LDAP_NO_LIMIT}
  LDAP_NO_LIMIT       = 0;

//  Flags for ld_options field :

  {$EXTERNALSYM LDAP_OPT_DNS}
  LDAP_OPT_DNS                = $00000001;  // utilize DN & DNS
  {$EXTERNALSYM LDAP_OPT_CHASE_REFERRALS}
  LDAP_OPT_CHASE_REFERRALS    = $00000002;  // chase referrals
  {$EXTERNALSYM LDAP_OPT_RETURN_REFS}
  LDAP_OPT_RETURN_REFS        = $00000004;  // return referrals to calling app

//
//  LDAP structure per connection
//

{$HPPEMIT '#pragma pack(push, 4)'}
{$ALIGN ON}

type
  {$EXTERNALSYM PLDAP}
  PLDAP = ^LDAP;
  {$EXTERNALSYM LDAP}
  LDAP = record

    ld_sb: record
      sb_sd: ULONG;
      Reserved1: array [0..(10 * sizeof(ULONG))] of Byte;
      sb_naddr: ULONG;   // notzero implies CLDAP available
      Reserved2: array [0..(6 * sizeof(ULONG)) - 1] of Byte;
    end;

    //
    //  Following parameters MAY match up to reference implementation of LDAP
    //

    ld_host: PChar;
    ld_version: ULONG;
    ld_lberoptions: Byte;

    //
    //  Safe to assume that these parameters are in same location as
    //  reference implementation of LDAP API.
    //

    ld_deref: ULONG;

    ld_timelimit: ULONG;
    ld_sizelimit: ULONG;

    ld_errno: ULONG;
    ld_matched: PChar;
    ld_error: PChar;
    ld_msgid: ULONG;

    Reserved3: array  [0..(6*sizeof(ULONG))] of Byte;

    //
    //  Following parameters may match up to reference implementation of LDAP API.
    //

    ld_cldaptries: ULONG;
    ld_cldaptimeout: ULONG;
    ld_refhoplimit: ULONG;
    ld_options: ULONG;
  end;

//
//  Our timeval structure is a bit different from the reference implementation
//  since Win32 defines a _timeval structure that is different from the LDAP
//  one.
//

  PLDAPTimeVal = ^TLDAPTimeVal;
  {$EXTERNALSYM l_timeval}
  l_timeval = packed record
    tv_sec: Longint;
    tv_usec: Longint;
  end;
  {$EXTERNALSYM LDAP_TIMEVAL}
  LDAP_TIMEVAL = l_timeval;
  {$EXTERNALSYM PLDAP_TIMEVAL}
  PLDAP_TIMEVAL = ^LDAP_TIMEVAL;
  TLDAPTimeVal = l_timeval;

//
//  The berval structure is used to pass in any arbitrary octet string.  It
//  is useful for attributes that cannot be represented using a null
//  terminated string.
//

  PLDAPBerVal = ^TLDAPBerVal;
  PPLDAPBerVal = ^PLDAPBerVal;
  {$EXTERNALSYM PLDAP_BERVAL}
  PLDAP_BERVAL = ^berval;
  {$EXTERNALSYM PBERVAL}
  PBERVAL = ^berval;
  {$EXTERNALSYM berval}
  berval = record
    bv_len: ULONG;
    bv_val: PChar;
  end;
  {$EXTERNALSYM LDAP_BERVAL}
  LDAP_BERVAL = berval;
  TLDAPBerVal = berval;

//
//  The following structure has to be compatible with reference implementation.
//

  PPLDAPMessage = ^PLDAPMessage;
  {$EXTERNALSYM PLDAPMessage}
  PLDAPMessage = ^LDAPMessage;
  {$EXTERNALSYM ldapmsg}
  ldapmsg = record
    lm_msgid: ULONG;             // message number for given connection
    lm_msgtype: ULONG;           // message type of the form LDAP_RES_xxx

    lm_ber: Pointer;             // ber form of message

    lm_chain: PLDAPMessage;      // pointer to next result value
    lm_next: PLDAPMessage;       // pointer to next message
    lm_time: ULONG;

    //
    //  new fields below not in reference implementation
    //

    Connection: PLDAP;           // connection from which we received response
    Request: Pointer;            // owning request(opaque structure)
    lm_returncode: ULONG;        // server's return code
    lm_referral: Word;           // index of referral within ref table
    lm_chased: ByteBool;         // has referral been chased already?
    lm_eom: ByteBool;            // is this the last entry for this message?
    ConnectionReferenced: ByteBool; // is the Connection still valid?
  end;
  {$EXTERNALSYM LDAPMessage}
  LDAPMessage = ldapmsg;

//
//  Controls... there are three types :
//
//   1) those passed to the server
//   2) those passed to the client and handled by the client API
//   3) those returned by the server
//

// Extra types defined for use as parameter.
  PPPLDAPControlA = ^PPLDAPControlA;
  {$NODEFINE PPPLDAPControlA}
  PPPLDAPControlW = ^PPLDAPControlW;
  {$NODEFINE PPPLDAPControlW}
  PPPLDAPControl = PPPLDAPControlA;
  PPLDAPControlA = ^PLDAPControlA;
  {$NODEFINE PPLDAPControlA}
  PPLDAPControlW = ^PLDAPControlW;
  {$NODEFINE PPLDAPControlW}
  PPLDAPControl = PPLDAPControlA;

  {$EXTERNALSYM PLDAPControlA}
  PLDAPControlA = ^LDAPControlA;
  {$EXTERNALSYM PLDAPControlW}
  PLDAPControlW = ^LDAPControlW;
  {$EXTERNALSYM PLDAPControl}
  PLDAPControl = PLDAPControlA;

  {$EXTERNALSYM LDAPControlA}
  LDAPControlA = record
    ldctl_oid: PAnsiChar;
    ldctl_value: TLDAPBerVal;
    ldctl_iscritical: ByteBool;
  end;
  {$EXTERNALSYM LDAPControlW}
  LDAPControlW = record
    ldctl_oid: PWideChar;
    ldctl_value: TLDAPBerVal;
    ldctl_iscritical: ByteBool;
  end;
  {$EXTERNALSYM LDAPControl}
  LDAPControl = LDAPControlA;

  TLDAPControlA = LDAPControlA;
  TLDAPControlW = LDAPControlW;
  TLDAPControl = TLDAPControlA;

//
//  Client controls section : these are the client controls that wldap32.dll
//  supports.
//
//  If you specify LDAP_CONTROL_REFERRALS in a control, the value field should
//  point to a ULONG of the following flags :
//
//      LDAP_CHASE_SUBORDINATE_REFERRALS
//      LDAP_CHASE_EXTERNAL_REFERRALS
//
const
  {$EXTERNALSYM LDAP_CONTROL_REFERRALS_W}
  LDAP_CONTROL_REFERRALS_W = '1.2.840.113556.1.4.616';
  {$EXTERNALSYM LDAP_CONTROL_REFERRALS}
  LDAP_CONTROL_REFERRALS   = '1.2.840.113556.1.4.616';


//
//  Values required for Modification command  These are options for the
//  mod_op field of LDAPMod structure
//

const
  {$EXTERNALSYM LDAP_MOD_ADD}
  LDAP_MOD_ADD            = $00;
  {$EXTERNALSYM LDAP_MOD_DELETE}
  LDAP_MOD_DELETE         = $01;
  {$EXTERNALSYM LDAP_MOD_REPLACE}
  LDAP_MOD_REPLACE        = $02;
  {$EXTERNALSYM LDAP_MOD_BVALUES}
  LDAP_MOD_BVALUES        = $80;


type
  {$EXTERNALSYM PLDAPModA}
  PLDAPModA = ^LDAPModA;
  {$EXTERNALSYM PLDAPModW}
  PLDAPModW = ^LDAPModW;
  {$EXTERNALSYM PLDAPMod}
  PLDAPMod = PLDAPModA;
  {$EXTERNALSYM LDAPModA}
  LDAPModA = record
    mod_op: ULONG;
    mod_type: PAnsiChar;
    case integer of
      0:(modv_strvals: ^PAnsiChar);
      1:(modv_bvals: ^PLDAPBerVal);
  end;
  {$EXTERNALSYM LDAPModW}
  LDAPModW = record
    mod_op: ULONG;
    mod_type: PWideChar;
    case integer of
      0:(modv_strvals: ^PWideChar);
      1:(modv_bvals: ^PLDAPBerVal);
  end;
  {$EXTERNALSYM LDAPMod}
  LDAPMod = LDAPModA;
  TLDAPModA = LDAPModA;
  TLDAPModW = LDAPModW;
  TLDAPMod = TLDAPModA;

{$HPPEMIT '#pragma pack(pop)'}

//
//  macros compatible with reference implementation...
//

{$EXTERNALSYM LDAP_IS_CLDAP}
function LDAP_IS_CLDAP(ld: PLDAP): Boolean;
{$EXTERNALSYM NAME_ERROR}
function NAME_ERROR(n: Integer): Boolean;

//
//  function definitions for LDAP API
//

//
//  Create a connection block to an LDAP server.  HostName can be NULL, in
//  which case we'll try to go off and find the "default" LDAP server.
//
//  Note that if we have to go off and find the default server, we'll pull
//  in NETAPI32.DLL and ADVAPI32.DLL.
//
//  If it returns NULL, an error occurred.  Pick up error code with
//     GetLastError().
//
//  ldap_open actually opens the connection at the time of the call,
//  whereas ldap_init only opens the connection when an operation is performed
//  that requires it.

{$EXTERNALSYM ldap_openA}
function ldap_openA(HostName: PAnsiChar; PortNumber: ULONG): PLDAP; cdecl;
{$EXTERNALSYM ldap_openW}
function ldap_openW(HostName: PWideChar; PortNumber: ULONG): PLDAP; cdecl;
{$EXTERNALSYM ldap_open}
function ldap_open(HostName: PChar; PortNumber: ULONG): PLDAP; cdecl;

{$EXTERNALSYM ldap_initA}
function ldap_initA(HostName: PAnsiChar; PortNumber: ULONG): PLDAP; cdecl;
{$EXTERNALSYM ldap_initW}
function ldap_initW(HostName: PWideChar; PortNumber: ULONG): PLDAP; cdecl;
{$EXTERNALSYM ldap_init}
function ldap_init(HostName: PChar; PortNumber: ULONG): PLDAP; cdecl;

{$EXTERNALSYM ldap_sslinitA}
function ldap_sslinitA(HostName: PAnsiChar; PortNumber: ULONG; secure: integer): PLDAP; cdecl;
{$EXTERNALSYM ldap_sslinitW}
function ldap_sslinitW(HostName: PWideChar; PortNumber: ULONG; secure: integer): PLDAP; cdecl;
{$EXTERNALSYM ldap_sslinit}
function ldap_sslinit(HostName: PChar; PortNumber: ULONG; secure: integer): PLDAP; cdecl;

//
//  when calling ldap_init, you can call ldap_connect explicitly to have the
//  library contact the server.  This is useful for checking for server
//  availability.  This call is not required however, since the other functions
//  will call it internally if it hasn't already been called.
//

{$EXTERNALSYM ldap_connect}
function ldap_connect(ld: PLDAP; timeout: PLDAPTimeval): ULONG; cdecl;

//
//  This is similar to ldap_open except it creates a connection block for
//  UDP based Connectionless LDAP services.  No TCP session is maintained.
//
//  If it returns NULL, an error occurred.  Pick up error code with
//     GetLastError().
//

{$EXTERNALSYM cldap_openA}
function cldap_openA(HostName: PAnsiChar; PortNumber: ULONG): PLDAP; cdecl;
{$EXTERNALSYM cldap_openW}
function cldap_openW(HostName: PWideChar; PortNumber: ULONG): PLDAP; cdecl;
{$EXTERNALSYM cldap_open}
function cldap_open(HostName: PChar; PortNumber: ULONG): PLDAP; cdecl;


//
//  Call unbind when you're done with the connection, it will free all
//  resources associated with the connection.
//
//  There is no ldap_close... use ldap_unbind even if you haven't called
//  ldap_bind on the connection.
//

{$EXTERNALSYM ldap_unbind}
function ldap_unbind(ld: PLDAP): ULONG; cdecl;
{$EXTERNALSYM ldap_unbind_s}
function ldap_unbind_s(ld: PLDAP): ULONG; cdecl; // calls ldap_unbind

//
//  Calls to get and set options on connection blocks... use them rather
//  than modifying the LDAP block directly.
//

{$EXTERNALSYM ldap_get_option}
function ldap_get_option(ld: PLDAP; option: integer; outvalue: pointer): ULONG; cdecl;
{$EXTERNALSYM ldap_get_optionW}
function ldap_get_optionW(ld: PLDAP; option: integer; outvalue: pointer): ULONG; cdecl;
{$EXTERNALSYM ldap_set_option}
function ldap_set_option(ld: PLDAP; option: integer; invalue: pointer): ULONG; cdecl;
{$EXTERNALSYM ldap_set_optionW}
function ldap_set_optionW(ld: PLDAP; option: integer; invalue: pointer): ULONG; cdecl;

//
//  These are the values to pass to ldap_get/set_option :
//

const
  {$EXTERNALSYM LDAP_OPT_DESC}
  LDAP_OPT_DESC               = $01;
  {$EXTERNALSYM LDAP_OPT_DEREF}
  LDAP_OPT_DEREF              = $02;
  {$EXTERNALSYM LDAP_OPT_SIZELIMIT}
  LDAP_OPT_SIZELIMIT          = $03;
  {$EXTERNALSYM LDAP_OPT_TIMELIMIT}
  LDAP_OPT_TIMELIMIT          = $04;
  {$EXTERNALSYM LDAP_OPT_THREAD_FN_PTRS}
  LDAP_OPT_THREAD_FN_PTRS     = $05;
  {$EXTERNALSYM LDAP_OPT_REBIND_FN}
  LDAP_OPT_REBIND_FN          = $06;
  {$EXTERNALSYM LDAP_OPT_REBIND_ARG}
  LDAP_OPT_REBIND_ARG         = $07;
  {$EXTERNALSYM LDAP_OPT_REFERRALS}
  LDAP_OPT_REFERRALS          = $08;
  {$EXTERNALSYM LDAP_OPT_RESTART}
  LDAP_OPT_RESTART            = $09;

  LDAP_OPT_SSL                = $0a;
  {$EXTERNALSYM LDAP_OPT_IO_FN_PTRS}
  LDAP_OPT_IO_FN_PTRS         = $0b;
  {$EXTERNALSYM LDAP_OPT_CACHE_FN_PTRS}
  LDAP_OPT_CACHE_FN_PTRS      = $0d;
  {$EXTERNALSYM LDAP_OPT_CACHE_STRATEGY}
  LDAP_OPT_CACHE_STRATEGY     = $0e;
  {$EXTERNALSYM LDAP_OPT_CACHE_ENABLE}
  LDAP_OPT_CACHE_ENABLE       = $0f;
  {$EXTERNALSYM LDAP_OPT_REFERRAL_HOP_LIMIT}
  LDAP_OPT_REFERRAL_HOP_LIMIT = $10;

  {$EXTERNALSYM LDAP_OPT_PROTOCOL_VERSION}
  LDAP_OPT_PROTOCOL_VERSION   = $11;
  {$EXTERNALSYM LDAP_OPT_VERSION}
  LDAP_OPT_VERSION            = $11;
  {$EXTERNALSYM LDAP_OPT_SORTKEYS}
  LDAP_OPT_SORTKEYS           = $11;

//
//  These are new ones that we've defined, not in current RFC draft.
//

  {$EXTERNALSYM LDAP_OPT_HOST_NAME}
  LDAP_OPT_HOST_NAME          = $30;
  {$EXTERNALSYM LDAP_OPT_ERROR_NUMBER}
  LDAP_OPT_ERROR_NUMBER       = $31;
  {$EXTERNALSYM LDAP_OPT_ERROR_STRING}
  LDAP_OPT_ERROR_STRING       = $32;
  {$EXTERNALSYM LDAP_OPT_SERVER_ERROR}
  LDAP_OPT_SERVER_ERROR       = $33;
  {$EXTERNALSYM LDAP_OPT_SERVER_EXT_ERROR}
  LDAP_OPT_SERVER_EXT_ERROR   = $34;
  {$EXTERNALSYM LDAP_OPT_HOST_REACHABLE}
  LDAP_OPT_HOST_REACHABLE     = $3E;

//
//  These options control the keep-alive logic.  Keep alives are sent as
//  ICMP ping messages (which currently don't go through firewalls).
//
//  There are three values that control how this works :
//  PING_KEEP_ALIVE : min number of seconds since we last received a response
//                    from the server before we send a keep-alive ping
//  PING_WAIT_TIME  : number of milliseconds we wait for the response to
//                    come back when we send a ping
//  PING_LIMIT      : number of unanswered pings we send before we close the
//                    connection.
//
//  To disable the keep-alive logic, set any of the values (PING_KEEP_ALIVE,
//  PING_LIMIT, or PING_WAIT_TIME) to zero.
//
//  The current default/min/max for these values are as follows :
//
//  PING_KEEP_ALIVE :  120/5/maxInt  seconds (may also be zero)
//  PING_WAIT_TIME  :  2000/10/60000 milliseconds (may also be zero)
//  PING_LIMIT      :  4/0/maxInt
//

  {$EXTERNALSYM LDAP_OPT_PING_KEEP_ALIVE}
  LDAP_OPT_PING_KEEP_ALIVE    = $36;
  {$EXTERNALSYM LDAP_OPT_PING_WAIT_TIME}
  LDAP_OPT_PING_WAIT_TIME     = $37;
  {$EXTERNALSYM LDAP_OPT_PING_LIMIT}
  LDAP_OPT_PING_LIMIT         = $38;

//
//  These won't be in the RFC.  Only use these if you're going to be dependent
//  on our implementation.
//

  {$EXTERNALSYM LDAP_OPT_DNSDOMAIN_NAME}
  LDAP_OPT_DNSDOMAIN_NAME     = $3B;    // return DNS name of domain
  {$EXTERNALSYM LDAP_OPT_GETDSNAME_FLAGS}
  LDAP_OPT_GETDSNAME_FLAGS    = $3D;    // flags for DsGetDcName

  {$EXTERNALSYM LDAP_OPT_PROMPT_CREDENTIALS}
  LDAP_OPT_PROMPT_CREDENTIALS = $3F;    // prompt for creds? currently
                                        // only for DPA & NTLM if no creds
                                        // are loaded

  {$EXTERNALSYM LDAP_OPT_AUTO_RECONNECT}
  LDAP_OPT_AUTO_RECONNECT     = $91;    // enable/disable autoreconnect
  {$EXTERNALSYM LDAP_OPT_SSPI_FLAGS}
  LDAP_OPT_SSPI_FLAGS         = $92;    // flags to pass to InitSecurityContext

//
// To retrieve information on an secure connection, a pointer to a
// SecPkgContext_connectionInfo structure (defined in schnlsp.h) must be
// passed in. On success, it is filled with relevent security information.
//

  {$EXTERNALSYM LDAP_OPT_SSL_INFO}
  LDAP_OPT_SSL_INFO           = $93;

//
// Turing on either the sign or the encrypt option prior to binding using
// LDAP_AUTH_NEGOTIATE will result in the ensuing LDAP session to be signed
// or encrypted using either Kerberos or NTLM (as negotiated by the underlying
// security packages). Note that these options can't be used with SSL.
//

  {$EXTERNALSYM LDAP_OPT_SIGN}
  LDAP_OPT_SIGN               = $95;
  {$EXTERNALSYM LDAP_OPT_ENCRYPT}
  LDAP_OPT_ENCRYPT            = $96;

//
// The user can set a preferred SASL method prior to binding using LDAP_AUTH_NEGOTIATE
// We will try to use this mechanism while binding. One example is "GSSAPI".
//

  {$EXTERNALSYM LDAP_OPT_SASL_METHOD}
  LDAP_OPT_SASL_METHOD        = $97;

//
// Setting this option to LDAP_OPT_ON will instruct the library to only perform an
// A-Record DNS lookup on the supplied host string. This option is OFF by default.
//

  {$EXTERNALSYM LDAP_OPT_AREC_EXCLUSIVE}
  LDAP_OPT_AREC_EXCLUSIVE     = $98;

//
// Retrieve the security context associated with the connection.
//

  {$EXTERNALSYM LDAP_OPT_SECURITY_CONTEXT}
  LDAP_OPT_SECURITY_CONTEXT   = $99;


//
//  End of Microsoft only options
//

  {$EXTERNALSYM LDAP_OPT_ON}
  LDAP_OPT_ON                 = Pointer(1);
  {$EXTERNALSYM LDAP_OPT_OFF}
  LDAP_OPT_OFF                = Pointer(0);

//
//  For chasing referrals, we extend this a bit for LDAP_OPT_REFERRALS.  If
//  the value is not LDAP_OPT_ON or LDAP_OPT_OFF, we'll treat them as the
//  following :
//
//  LDAP_CHASE_SUBORDINATE_REFERRALS  : chase subordinate referrals (or
//                                      references) returned in a v3 search
//  LDAP_CHASE_EXTERNAL_REFERRALS : chase external referrals. These are
//                          returned possibly on any operation except bind.
//
//  If you OR these flags together, it's equivalent to setting referrals to
//  LDAP_OPT_ON.
//

  {$EXTERNALSYM LDAP_CHASE_SUBORDINATE_REFERRALS}
  LDAP_CHASE_SUBORDINATE_REFERRALS    = $00000020;
  {$EXTERNALSYM LDAP_CHASE_EXTERNAL_REFERRALS}
  LDAP_CHASE_EXTERNAL_REFERRALS       = $00000040;

//
//  Bind is required as the first operation to v2 servers, not so for v3
//  servers.  See above description of authentication methods.
//

{$EXTERNALSYM ldap_simple_bindA}
function ldap_simple_bindA(ld: PLDAP; dn, passwd: PAnsiChar): ULONG; cdecl;
{$EXTERNALSYM ldap_simple_bindW}
function ldap_simple_bindW(ld: PLDAP; dn, passwd: PWideChar): ULONG; cdecl;
{$EXTERNALSYM ldap_simple_bind}
function ldap_simple_bind(ld: PLDAP; dn, passwd: PChar): ULONG; cdecl;
{$EXTERNALSYM ldap_simple_bind_sA}
function ldap_simple_bind_sA(ld: PLDAP; dn, passwd: PAnsiChar): ULONG; cdecl;
{$EXTERNALSYM ldap_simple_bind_sW}
function ldap_simple_bind_sW(ld: PLDAP; dn, passwd: PWideChar): ULONG; cdecl;
{$EXTERNALSYM ldap_simple_bind_s}
function ldap_simple_bind_s(ld: PLDAP; dn, passwd: PChar): ULONG; cdecl;

{$EXTERNALSYM ldap_bindA}
function ldap_bindA(ld: PLDAP; dn, cred: PAnsiChar; method: ULONG): ULONG; cdecl;
{$EXTERNALSYM ldap_bindW}
function ldap_bindW(ld: PLDAP; dn, cred: PWideChar; method: ULONG): ULONG; cdecl;
{$EXTERNALSYM ldap_bind}
function ldap_bind(ld: PLDAP; dn, cred: PChar; method: ULONG): ULONG; cdecl;
{$EXTERNALSYM ldap_bind_sA}
function ldap_bind_sA(ld: PLDAP; dn, cred: PAnsiChar; method: ULONG): ULONG; cdecl;
{$EXTERNALSYM ldap_bind_sW}
function ldap_bind_sW(ld: PLDAP; dn, cred: PWideChar; method: ULONG): ULONG; cdecl;
{$EXTERNALSYM ldap_bind_s}
function ldap_bind_s(ld: PLDAP; dn, cred: PChar; method: ULONG): ULONG; cdecl;

// The following functions can be used to pass in any arbitrary credentials
// to the server. The application must be ready to interpret the response
// sent back from the server.
//

{$EXTERNALSYM ldap_sasl_bindA}
function ldap_sasl_bindA(ExternalHandle: PLDAP; DistName: PAnsiChar;
  AuthMechanism: PAnsiChar; cred: PBERVAL;
  var ServerCtrls, ClientCtrls: PLDAPControlA;
  var MessageNumber: Integer): Integer; cdecl;
{$EXTERNALSYM ldap_sasl_bindW}
function ldap_sasl_bindW(ExternalHandle: PLDAP; DistName: PWideChar;
  AuthMechanism: PWideChar; cred: PBERVAL;
  var ServerCtrls, ClientCtrls: PLDAPControlW;
  var MessageNumber: Integer): Integer; cdecl;
{$EXTERNALSYM ldap_sasl_bind}
function ldap_sasl_bind(ExternalHandle: PLDAP; DistName: PChar;
  AuthMechanism: PChar; cred: PBERVAL;
  var ServerCtrls, ClientCtrls: PLDAPControl;
  var MessageNumber: Integer): Integer; cdecl;

function ldap_sasl_bind_sA(ExternalHandle: PLDAP; DistName: PAnsiChar;
  AuthMechanism: PAnsiChar; cred: PBERVAL;
  var ServerCtrls, ClientCtrls: PLDAPControlA;
  var ServerData: PBERVAL): Integer; cdecl;
function ldap_sasl_bind_sW(ExternalHandle: PLDAP; DistName: PWideChar;
  AuthMechanism: PWideChar; cred: PBERVAL;
  var ServerCtrls, ClientCtrls: PLDAPControlW;
  var ServerData: PBERVAL): Integer; cdecl;
function ldap_sasl_bind_s(ExternalHandle: PLDAP; DistName: PChar;
  AuthMechanism: PChar; cred: PBERVAL;
  var ServerCtrls, ClientCtrls: PLDAPControl;
  var ServerData: PBERVAL): Integer; cdecl;


//
//  Synchronous and asynch search routines.
//
//  filter follows RFC 1960 with the addition that '(' ')' '*' ' ' '\' and
//   '\0' are all escaped with '\'
//
// Scope of search.  This corresponds to the "scope" parameter on search

const
  {$EXTERNALSYM LDAP_SCOPE_BASE}
  LDAP_SCOPE_BASE         = $00;
  {$EXTERNALSYM LDAP_SCOPE_ONELEVEL}
  LDAP_SCOPE_ONELEVEL     = $01;
  {$EXTERNALSYM LDAP_SCOPE_SUBTREE}
  LDAP_SCOPE_SUBTREE      = $02;

{$EXTERNALSYM ldap_searchA}
function ldap_searchA(
  ld: PLDAP;
  base: PAnsiChar;        // distinguished name or ''
  scope: ULONG;           // LDAP_SCOPE_xxxx
  filter: PAnsiChar;
  attrs: PAnsiChar;       // pointer to an array of PAnsiChar attribute names
  attrsonly: ULONG        // boolean on whether to only return attr names
): ULONG; cdecl;
{$EXTERNALSYM ldap_searchW}
function ldap_searchW(
  ld: PLDAP;
  base: PWideChar;        // distinguished name or ''
  scope: ULONG;           // LDAP_SCOPE_xxxx
  filter: PWideChar;
  attrs: PWideChar;       // pointer to an array of PAnsiChar attribute names
  attrsonly: ULONG        // boolean on whether to only return attr names
): ULONG; cdecl;
{$EXTERNALSYM ldap_search}
function ldap_search(
  ld: PLDAP;
  base: PChar;        // distinguished name or ''
  scope: ULONG;           // LDAP_SCOPE_xxxx
  filter: PChar;
  attrs: PChar;       // pointer to an array of PAnsiChar attribute names
  attrsonly: ULONG        // boolean on whether to only return attr names
): ULONG; cdecl;

{$EXTERNALSYM ldap_search_sA}
function ldap_search_sA(ld: PLDAP; base: PAnsiChar; scope: ULONG;
  filter, attrs: PAnsiChar; attrsonly: ULONG;
  var res: PLDAPMessage): ULONG; cdecl;
{$EXTERNALSYM ldap_search_sW}
function ldap_search_sW(ld: PLDAP; base: PWideChar; scope: ULONG;
  filter, attrs: PWideChar; attrsonly: ULONG;
  var res: PLDAPMessage): ULONG; cdecl;
{$EXTERNALSYM ldap_search_s}
function ldap_search_s(ld: PLDAP; base: PChar; scope: ULONG;
  filter, attrs: PChar; attrsonly: ULONG;
  var res: PLDAPMessage): ULONG; cdecl;

{$EXTERNALSYM ldap_search_stA}
function ldap_search_stA(ld: PLDAP; base: PAnsiChar; scope: ULONG;
  filter, attrs: PAnsiChar; attrsonly:  ULONG; var timeout: TLDAPTimeVal;
  var res: PLDAPMessage): ULONG; cdecl;
{$EXTERNALSYM ldap_search_stW}
function ldap_search_stW(ld: PLDAP; base: PWideChar; scope: ULONG;
  filter, attrs: PWideChar; attrsonly:  ULONG; var timeout: TLDAPTimeVal;
  var res: PLDAPMessage): ULONG; cdecl;
{$EXTERNALSYM ldap_search_st}
function ldap_search_st(ld: PLDAP; base: PChar; scope: ULONG;
  filter, attrs: PChar; attrsonly:  ULONG; var timeout: TLDAPTimeVal;
  var res: PLDAPMessage): ULONG; cdecl;

{$EXTERNALSYM ldap_search_extA}
function ldap_search_extA(ld: PLDAP; base: PAnsiChar; scope: ULONG;
  filter, attrs: PAnsiChar; attrsonly: ULONG;
  var ServerControls, ClientControls: PLDAPControlA;
  TimeLimit, SizeLimit: ULONG; var MessageNumber: ULONG): ULONG; cdecl;
{$EXTERNALSYM ldap_search_extW}
function ldap_search_extW(ld: PLDAP; base: PWideChar; scope: ULONG;
  filter, attrs: PWideChar; attrsonly: ULONG;
  var ServerControls, ClientControls: PLDAPControlW;
  TimeLimit, SizeLimit: ULONG; var MessageNumber: ULONG): ULONG; cdecl;
{$EXTERNALSYM ldap_search_ext}
function ldap_search_ext(ld: PLDAP; base: PChar; scope: ULONG;
  filter, attrs: PChar; attrsonly: ULONG;
  ServerControls, ClientControls: PPLDAPControl;
  TimeLimit, SizeLimit: ULONG; var MessageNumber: ULONG): ULONG; cdecl;

{$EXTERNALSYM ldap_search_ext_sA}
function ldap_search_ext_sA(ld: PLDAP; base: PAnsiChar; scope: ULONG;
  filter, attrs: PAnsiChar; attrsonly: ULONG;
  var ServerControls, ClientControls: PLDAPControlA;
  var timeout: TLDAPTimeVal; SizeLimit: ULONG;
  var res: PLDAPMessage): ULONG; cdecl;
{$EXTERNALSYM ldap_search_ext_sW}
function ldap_search_ext_sW(ld: PLDAP; base: PWideChar; scope: ULONG;
  filter, attrs: PWideChar; attrsonly: ULONG;
  var ServerControls, ClientControls: PLDAPControlW;
  var timeout: TLDAPTimeVal; SizeLimit: ULONG;
  var res: PLDAPMessage): ULONG; cdecl;
{$EXTERNALSYM ldap_search_ext_s}
function ldap_search_ext_s(ld: PLDAP; base: PChar; scope: ULONG;
  filter, attrs: PChar; attrsonly: ULONG;
  ServerControls, ClientControls: PPLDAPControl;
  timeout: PLDAPTimeVal; SizeLimit: ULONG;
  var res: PLDAPMessage): ULONG; cdecl;

//
//  Extended API to check filter syntax.  Returns LDAP error code if syntax
//  is invalid or LDAP_SUCCESS if it's ok.
//

{$EXTERNALSYM ldap_check_filterA}
function ldap_check_filterA(ld: PLDAP; SearchFilter: PAnsiChar): ULONG; cdecl;
{$EXTERNALSYM ldap_check_filterW}
function ldap_check_filterW(ld: PLDAP; SearchFilter: PWideChar): ULONG; cdecl;
{$EXTERNALSYM ldap_check_filter}
function ldap_check_filter(ld: PLDAP; SearchFilter: PChar): ULONG; cdecl;

//
//  modify an existing entry
//

//
//  multi-thread: ldap_modify calls are not safe in that the message number
//                is returned rather than the return code.  You have to look
//                at the connection block in an error case and the return code
//                may be overwritten by another thread inbetween.
//
//                Use ldap_modify_ext instead, as these are thread safe.
//
//                ldap_modify_s and ldap_modify_ext* calls are thread safe.
//

{$EXTERNALSYM ldap_modifyA}
function ldap_modifyA(ld: PLDAP; dn: PAnsiChar; var mods: PLDAPModA): ULONG; cdecl;
{$EXTERNALSYM ldap_modifyW}
function ldap_modifyW(ld: PLDAP; dn: PWideChar; var mods: PLDAPModW): ULONG; cdecl;
{$EXTERNALSYM ldap_modify}
function ldap_modify(ld: PLDAP; dn: PChar; var mods: PLDAPMod): ULONG; cdecl;

{$EXTERNALSYM ldap_modify_sA}
function ldap_modify_sA(ld: PLDAP; dn: PAnsiChar; var mods: PLDAPModA): ULONG; cdecl;
{$EXTERNALSYM ldap_modify_sW}
function ldap_modify_sW(ld: PLDAP; dn: PWideChar; var mods: PLDAPModW): ULONG; cdecl;
{$EXTERNALSYM ldap_modify_s}
function ldap_modify_s(ld: PLDAP; dn: PChar; var mods: PLDAPMod): ULONG; cdecl;

{$EXTERNALSYM ldap_modify_extA}
function ldap_modify_extA(ld: PLDAP; dn: PAnsiChar; var mods: PLDAPModA;
  var ServerControls, ClientControls: PLDAPControlA;
  var MessageNumber: ULONG): ULONG; cdecl;
{$EXTERNALSYM ldap_modify_extW}
function ldap_modify_extW(ld: PLDAP; dn: PWideChar; var mods: PLDAPModW;
  var ServerControls, ClientControls: PLDAPControlW;
  var MessageNumber: ULONG): ULONG; cdecl;
{$EXTERNALSYM ldap_modify_ext}
function ldap_modify_ext(ld: PLDAP; dn: PChar; var mods: PLDAPMod;
  var ServerControls, ClientControls: PLDAPControl;
  var MessageNumber: ULONG): ULONG; cdecl;

{$EXTERNALSYM ldap_modify_ext_sA}
function ldap_modify_ext_sA(ld: PLDAP; dn: PAnsiChar; var mods: PLDAPModA;
  var ServerControls, ClientControls: PLDAPControlA): ULONG; cdecl;
{$EXTERNALSYM ldap_modify_ext_sW}
function ldap_modify_ext_sW(ld: PLDAP; dn: PWideChar; var mods: PLDAPModW;
  var ServerControls, ClientControls: PLDAPControlW): ULONG; cdecl;
{$EXTERNALSYM ldap_modify_ext_s}
function ldap_modify_ext_s(ld: PLDAP; dn: PChar; var mods: PLDAPMod;
  var ServerControls, ClientControls: PLDAPControl): ULONG; cdecl;


//
//  modrdn and modrdn2 function both as RenameObject and MoveObject.
//
//  Note that to LDAP v2 servers, only rename within a given container
//  is supported... therefore NewDistinguishedName is actually NewRDN.
//  Here are some examples :
//
//  This works to both v2 and v3 servers :
//
//    DN = CN=Bob,OU=FOO,O=BAR
//    NewDN = CN=Joe
//
//    result is: CN=Joe,OU=FOO,O=BAR
//
//  This works to only v3 and above servers :
//
//    DN = CN=Bob,OU=FOO,O=BAR
//    NewDN = CN=Joe,OU=FOOBAR,O=BAR
//
//    result is: CN=Joe,OU=FOOBAR,O=BAR
//
//  If you try the second example to a v2 server, we'll send the whole
//  NewDN over as the new RDN(rather than break up the parent OU and
//  child).  The server will then give you back some unknown error.
//

//
//  multi-thread: ldap_modrdn and ldap_modrdn2 calls are not safe in that
//                the message number is returned rather than the return code.
//                You have to look   at the connection block in an error case
//                and the return code may be overwritten by another thread
//                inbetween.
//
//                Use ldap_rename_ext instead, as these are thread safe.
//


{$EXTERNALSYM ldap_modrdn2A}
function ldap_modrdn2A(var ExternalHandle: LDAP;
  DistinguishedName, NewDistinguishedName: PAnsiChar;
  DeleteOldRdn: Integer): ULONG; cdecl;
{$EXTERNALSYM ldap_modrdn2W}
function ldap_modrdn2W(var ExternalHandle: LDAP;
  DistinguishedName, NewDistinguishedName: PWideChar;
  DeleteOldRdn: Integer): ULONG; cdecl;
{$EXTERNALSYM ldap_modrdn2}
function ldap_modrdn2(var ExternalHandle: LDAP;
  DistinguishedName, NewDistinguishedName: PChar;
  DeleteOldRdn: Integer): ULONG; cdecl;

//
//  ldap_modrdn simply calls ldap_modrdn2 with a value of 1 for DeleteOldRdn.
//

{$EXTERNALSYM ldap_modrdnA}
function ldap_modrdnA(var ExternalHandle: LDAP;
  DistinguishedName, NewDistinguishedName: PAnsiChar): ULONG; cdecl;
{$EXTERNALSYM ldap_modrdnW}
function ldap_modrdnW(var ExternalHandle: LDAP;
  DistinguishedName, NewDistinguishedName: PWideChar): ULONG; cdecl;
{$EXTERNALSYM ldap_modrdn}
function ldap_modrdn(var ExternalHandle: LDAP;
  DistinguishedName, NewDistinguishedName: PChar): ULONG; cdecl;

{$EXTERNALSYM ldap_modrdn2_sA}
function ldap_modrdn2_sA(var ExternalHandle: LDAP;
  DistinguishedName, NewDistinguishedName: PAnsiChar;
  DeleteOldRdn: Integer): ULONG; cdecl;
{$EXTERNALSYM ldap_modrdn2_sW}
function ldap_modrdn2_sW(var ExternalHandle: LDAP;
  DistinguishedName, NewDistinguishedName: PWideChar;
  DeleteOldRdn: Integer): ULONG; cdecl;
{$EXTERNALSYM ldap_modrdn2_s}
function ldap_modrdn2_s(var ExternalHandle: LDAP;
  DistinguishedName, NewDistinguishedName: PChar;
  DeleteOldRdn: Integer): ULONG; cdecl;

{$EXTERNALSYM ldap_modrdn_sA}
function ldap_modrdn_sA(var ExternalHandle: LDAP;
  DistinguishedName, NewDistinguishedName: PAnsiChar): ULONG; cdecl;
{$EXTERNALSYM ldap_modrdn_sW}
function ldap_modrdn_sW(var ExternalHandle: LDAP;
  DistinguishedName, NewDistinguishedName: PWideChar): ULONG; cdecl;
{$EXTERNALSYM ldap_modrdn_s}
function ldap_modrdn_s(var ExternalHandle: LDAP;
  DistinguishedName, NewDistinguishedName: PChar): ULONG; cdecl;


//
//  Extended Rename operations.  These take controls and separate out the
//  parent from the RDN, for clarity.
//

{$EXTERNALSYM ldap_rename_extA}
function ldap_rename_extA(ld: PLDAP; dn, NewRDN, NewParent: PAnsiChar;
  DeleteOldRdn: Integer; var ServerControls, ClientControls: PLDAPControlA;
  var MessageNumber: ULONG): ULONG; cdecl;
{$EXTERNALSYM ldap_rename_extW}
function ldap_rename_extW(ld: PLDAP; dn, NewRDN, NewParent: PWideChar;
  DeleteOldRdn: Integer; var ServerControls, ClientControls: PLDAPControlW;
  var MessageNumber: ULONG): ULONG; cdecl;
{$EXTERNALSYM ldap_rename_ext}
function ldap_rename_ext(ld: PLDAP; dn, NewRDN, NewParent: PChar;
  DeleteOldRdn: Integer; var ServerControls, ClientControls: PLDAPControl;
  var MessageNumber: ULONG): ULONG; cdecl;

{$EXTERNALSYM ldap_rename_ext_sA}
function ldap_rename_ext_sA(ld: PLDAP;
  dn, NewRDN, NewParent: PAnsiChar; DeleteOldRdn: Integer;
  var ServerControls, ClientControls: PLDAPControlA): ULONG; cdecl;
{$EXTERNALSYM ldap_rename_ext_sW}
function ldap_rename_ext_sW(ld: PLDAP;
  dn, NewRDN, NewParent: PWideChar; DeleteOldRdn: Integer;
  var ServerControls, ClientControls: PLDAPControlW): ULONG; cdecl;
{$EXTERNALSYM ldap_rename_ext_s}
function ldap_rename_ext_s(ld: PLDAP;
  dn, NewRDN, NewParent: PChar; DeleteOldRdn: Integer;
  var ServerControls, ClientControls: PLDAPControl): ULONG; cdecl;


//
//  Add an entry to the tree
//

//
//  multi-thread: ldap_add calls are not safe in that the message number
//                is returned rather than the return code.  You have to look
//                at the connection block in an error case and the return code
//                may be overwritten by another thread inbetween.
//
//                Use ldap_add_ext instead, as these are thread safe.
//
//                ldap_add_s and ldap_add_ext* calls are thread safe.
//

{$EXTERNALSYM ldap_addA}
function ldap_addA(ld: PLDAP; dn: PAnsiChar; var attrs: PLDAPModA): ULONG; cdecl;
{$EXTERNALSYM ldap_addW}
function ldap_addW(ld: PLDAP; dn: PWideChar; var attrs: PLDAPModW): ULONG; cdecl;
{$EXTERNALSYM ldap_add}
function ldap_add(ld: PLDAP; dn: PChar; var attrs: PLDAPMod): ULONG; cdecl;

{$EXTERNALSYM ldap_add_sA}
function ldap_add_sA(ld: PLDAP; dn: PAnsiChar; var attrs: PLDAPModA): ULONG; cdecl;
{$EXTERNALSYM ldap_add_sW}
function ldap_add_sW(ld: PLDAP; dn: PWideChar; var attrs: PLDAPModW): ULONG; cdecl;
{$EXTERNALSYM ldap_add_s}
function ldap_add_s(ld: PLDAP; dn: PChar; var attrs: PLDAPMod): ULONG; cdecl;

{$EXTERNALSYM ldap_add_extA}
function ldap_add_extA(ld: PLDAP; dn: PAnsiChar; var attrs: PLDAPModA;
  var ServerControls, ClientControls: PLDAPControlA;
  var MessageNumber: ULONG): ULONG; cdecl;
{$EXTERNALSYM ldap_add_extW}
function ldap_add_extW(ld: PLDAP; dn: PWideChar; var attrs: PLDAPModW;
  var ServerControls, ClientControls: PLDAPControlW;
  var MessageNumber: ULONG): ULONG; cdecl;
{$EXTERNALSYM ldap_add_ext}
function ldap_add_ext(ld: PLDAP; dn: PChar; var attrs: PLDAPMod;
  var ServerControls, ClientControls: PLDAPControl;
  var MessageNumber: ULONG): ULONG; cdecl;

{$EXTERNALSYM ldap_add_ext_sA}
function ldap_add_ext_sA(ld: PLDAP; dn: PAnsiChar; var attrs: PLDAPModA;
  var ServerControls, ClientControls: PLDAPControlA): ULONG; cdecl;
{$EXTERNALSYM ldap_add_ext_sW}
function ldap_add_ext_sW(ld: PLDAP; dn: PWideChar; var attrs: PLDAPModW;
  var ServerControls, ClientControls: PLDAPControlW): ULONG; cdecl;
{$EXTERNALSYM ldap_add_ext_s}
function ldap_add_ext_s(ld: PLDAP; dn: PChar; var attrs: PLDAPMod;
  var ServerControls, ClientControls: PLDAPControl): ULONG; cdecl;

//
//  Compare the attribute for a given entry to a known value.
//

{$EXTERNALSYM ldap_compareA}
function ldap_compareA(ld: PLDAP; dn, attr, value: PAnsiChar): ULONG; cdecl;
{$EXTERNALSYM ldap_compareW}
function ldap_compareW(ld: PLDAP; dn, attr, value: PWideChar): ULONG; cdecl;
{$EXTERNALSYM ldap_compare}
function ldap_compare(ld: PLDAP; dn, attr, value: PChar): ULONG; cdecl;

{$EXTERNALSYM ldap_compare_sA}
function ldap_compare_sA(ld: PLDAP; dn, attr, value: PAnsiChar): ULONG; cdecl;
{$EXTERNALSYM ldap_compare_sW}
function ldap_compare_sW(ld: PLDAP; dn, attr, value: PWideChar): ULONG; cdecl;
{$EXTERNALSYM ldap_compare_s}
function ldap_compare_s(ld: PLDAP; dn, attr, value: PChar): ULONG; cdecl;

//
//  Extended Compare operations.  These take controls and are thread safe.
//  They also allow you to specify a bval structure for the data, so that it
//  isn't translated from Unicode or ANSI to UTF8.  Allows for comparison of
//  raw binary data.
//
//  Specify either Data or Value as not NULL.  If both are not NULL, the
//  berval Data will be used.
//

// either value or Data is not null, not both
{$EXTERNALSYM ldap_compare_extA}
function ldap_compare_extA(ld: PLDAP; dn, Attr, Value: PAnsiChar;
  Data: PLDAPBerVal; var ServerControls, ClientControls: PLDAPControlA;
  var MessageNumber: ULONG): ULONG; cdecl;
{$EXTERNALSYM ldap_compare_extW}
function ldap_compare_extW(ld: PLDAP; dn, Attr, Value: PWideChar;
  Data: PLDAPBerVal; var ServerControls, ClientControls: PLDAPControlW;
  var MessageNumber: ULONG): ULONG; cdecl;
{$EXTERNALSYM ldap_compare_ext}
function ldap_compare_ext(ld: PLDAP; dn, Attr, Value: PChar;
  Data: PLDAPBerVal; var ServerControls, ClientControls: PLDAPControl;
  var MessageNumber: ULONG): ULONG; cdecl;

{$EXTERNALSYM ldap_compare_ext_sA}
function ldap_compare_ext_sA(ld: PLDAP;
  dn, Attr, Value: PAnsiChar; Data: PLDAPBerVal;
  var ServerControls, ClientControls: PLDAPControlA): ULONG; cdecl;
{$EXTERNALSYM ldap_compare_ext_sW}
function ldap_compare_ext_sW(ld: PLDAP;
  dn, Attr, Value: PWideChar; Data: PLDAPBerVal;
  var ServerControls, ClientControls: PLDAPControlW): ULONG; cdecl;
{$EXTERNALSYM ldap_compare_ext_s}
function ldap_compare_ext_s(ld: PLDAP;
  dn, Attr, Value: PChar; Data: PLDAPBerVal;
  var ServerControls, ClientControls: PLDAPControl): ULONG; cdecl;


//
//  Delete an object out of the tree
//

//
//  multi-thread: ldap_delete calls are not safe in that the message number
//                is returned rather than the return code.  You have to look
//                at the connection block in an error case and the return code
//                may be overwritten by another thread inbetween.
//
//                Use ldap_delete_ext instead, as these are thread safe.
//
//                ldap_delete_s and ldap_delete_ext* calls are thread safe.
//

{$EXTERNALSYM ldap_deleteA}
function ldap_deleteA(ld: PLDAP; dn: PAnsiChar): ULONG; cdecl;
{$EXTERNALSYM ldap_deleteW}
function ldap_deleteW(ld: PLDAP; dn: PWideChar): ULONG; cdecl;
{$EXTERNALSYM ldap_delete}
function ldap_delete(ld: PLDAP; dn: PChar): ULONG; cdecl;

{$EXTERNALSYM ldap_delete_sA}
function ldap_delete_sA(ld: PLDAP; dn: PAnsiChar): ULONG; cdecl;
{$EXTERNALSYM ldap_delete_sW}
function ldap_delete_sW(ld: PLDAP; dn: PWideChar): ULONG; cdecl;
{$EXTERNALSYM ldap_delete_s}
function ldap_delete_s(ld: PLDAP; dn: PChar): ULONG; cdecl;

{$EXTERNALSYM ldap_delete_extA}
function ldap_delete_extA(ld: PLDAP; dn: PAnsiChar;
  var ServerControls, ClientControls: PLDAPControlA;
  var MessageNumber: ULONG): ULONG; cdecl;
{$EXTERNALSYM ldap_delete_extW}
function ldap_delete_extW(ld: PLDAP; dn: PWideChar;
  var ServerControls, ClientControls: PLDAPControlW;
  var MessageNumber: ULONG): ULONG; cdecl;
{$EXTERNALSYM ldap_delete_ext}
function ldap_delete_ext(ld: PLDAP; dn: PChar;
  var ServerControls, ClientControls: PLDAPControl;
  var MessageNumber: ULONG): ULONG; cdecl;

{$EXTERNALSYM ldap_delete_ext_sA}
function ldap_delete_ext_sA(ld: PLDAP; dn: PAnsiChar;
  var ServerControls, ClientControls: PLDAPControlA): ULONG; cdecl;
{$EXTERNALSYM ldap_delete_ext_sW}
function ldap_delete_ext_sW(ld: PLDAP; dn: PWideChar;
  var ServerControls, ClientControls: PLDAPControlW): ULONG; cdecl;
{$EXTERNALSYM ldap_delete_ext_s}
function ldap_delete_ext_s(ld: PLDAP; dn: PChar;
  var ServerControls, ClientControls: PLDAPControl): ULONG; cdecl;


//
//  Give up on a request.  No guarentee that it got there as there is no
//  response from the server.
//

{$EXTERNALSYM ldap_abandon}
function ldap_abandon(ld: PLDAP; msgid: ULONG): ULONG; cdecl;


//
//  Possible values for "all" field in ldap_result.  We've enhanced it such
//  that if someone passes in LDAP_MSG_RECEIVED, we'll pass all values we've
//  received up to that point.
//

const
  {$EXTERNALSYM LDAP_MSG_ONE}
  LDAP_MSG_ONE       = 0;
  {$EXTERNALSYM LDAP_MSG_ALL}
  LDAP_MSG_ALL       = 1;
  {$EXTERNALSYM LDAP_MSG_RECEIVED}
  LDAP_MSG_RECEIVED  = 2;

//
//  Get a response from a connection.  One enhancement here is that ld can
//  be null, in which case we'll return responses from any server.  Free
//  responses here with ldap_msgfree.
//
//  For connection-less LDAP, you should pass in both a LDAP connection
//  handle and a msgid.  This will ensure we know which request the app
//  is waiting on a reply to. (we actively resend request until we get
//  a response.)
//

{$EXTERNALSYM ldap_result}
function ldap_result(ld: PLDAP; msgid, all: ULONG;
  timeout: PLDAP_TIMEVAL; var res: PLDAPMessage): ULONG; cdecl;

{$EXTERNALSYM ldap_msgfree}
function ldap_msgfree(res: PLDAPMessage): ULONG; cdecl;

//
//  This parses a message and returns the error code.  It optionally frees
//  the message by calling ldap_msgfree.
//

//  multi-thread: ldap_result2error call is thread safe

// freeit is boolean.. free the message?
{$EXTERNALSYM ldap_result2error}
function ldap_result2error(ld: PLDAP; res: PLDAPMessage;
  freeit: ULONG): ULONG; cdecl;

//
//  Similar to ldap_result2error, this parses responses from the server and
//  returns the appropriate fields.  Use this one if you want to get at the
//  referrals, matchingDNs, or server controls returned.
//

//  multi-thread: ldap_parse_result call is thread safe

{$EXTERNALSYM ldap_parse_resultA}
function ldap_parse_resultA (
        var Connection: LDAP;
        ResultMessage: PLDAPMessage;
        ReturnCode: PULONG;                     // returned by server
        MatchedDNs: PPCharA;                    // free with ldap_memfree
        ErrorMessage: PPCharA;                  // free with ldap_memfree
        Referrals: PPPCharA;                    // free with ldap_value_freeW
        var ServerControls: PPLDAPControlA;     // free with ldap_free_controlsW
        Freeit: BOOL): ULONG; cdecl;
{$EXTERNALSYM ldap_parse_resultW}
function ldap_parse_resultW (
        var Connection: LDAP;
        ResultMessage: PLDAPMessage;
        ReturnCode: PULONG;                     // returned by server
        MatchedDNs: PPCharW;                    // free with ldap_memfree
        ErrorMessage: PPCharW;                  // free with ldap_memfree
        Referrals: PPPCharW;                    // free with ldap_value_freeW
        var ServerControls: PPLDAPControlW;     // free with ldap_free_controlsW
        Freeit: BOOL): ULONG; cdecl;
{$EXTERNALSYM ldap_parse_result}
function ldap_parse_result (
        var Connection: LDAP;
        ResultMessage: PLDAPMessage;
        ReturnCode: PULONG;                     // returned by server
        MatchedDNs: PPChar;                    // free with ldap_memfree
        ErrorMessage: PPChar;                  // free with ldap_memfree
        Referrals: PPPChar;                    // free with ldap_value_freeW
        var ServerControls: PPLDAPControl;     // free with ldap_free_controlsW
        Freeit: BOOL): ULONG; cdecl;

{$EXTERNALSYM ldap_controls_freeA}
function ldap_controls_freeA(var Controls: PLDAPControlA): ULONG; cdecl;
{$EXTERNALSYM ldap_controls_freeW}
function ldap_controls_freeW(var Controls: PLDAPControlW): ULONG; cdecl;
{$EXTERNALSYM ldap_controls_free}
function ldap_controls_free(var Controls: PLDAPControl): ULONG; cdecl;

{$EXTERNALSYM ldap_parse_extended_resultA}
function ldap_parse_extended_resultA(
  Connection: PLDAP;
  ResultMessage: PLDAPMessage;          // returned by server
  var ResultOID: PAnsiChar;             // free with ldap_memfree
  var ResultData: PBERVAL;              // free with ldap_memfree
  Freeit: ByteBool                      // Don't need the message anymore
): ULONG; cdecl;
{$EXTERNALSYM ldap_parse_extended_resultW}
function ldap_parse_extended_resultW(
  Connection: PLDAP;
  ResultMessage: PLDAPMessage;          // returned by server
  var ResultOID: PWideChar;             // free with ldap_memfree
  var ResultData: PBERVAL;              // free with ldap_memfree
  Freeit: ByteBool                      // Don't need the message anymore
): ULONG; cdecl;
{$EXTERNALSYM ldap_parse_extended_result}
function ldap_parse_extended_result(
  Connection: PLDAP;
  ResultMessage: PLDAPMessage;          // returned by server
  var ResultOID: PChar;             // free with ldap_memfree
  var ResultData: PBERVAL;              // free with ldap_memfree
  Freeit: ByteBool                      // Don't need the message anymore
): ULONG; cdecl;

{$EXTERNALSYM ldap_control_freeA}
function ldap_control_freeA(var Control: LDAPControlA): ULONG; cdecl;
{$EXTERNALSYM ldap_control_freeW}
function ldap_control_freeW(var Control: LDAPControlW): ULONG; cdecl;
{$EXTERNALSYM ldap_control_free}
function ldap_control_free(var Control: LDAPControl): ULONG; cdecl;

//
// ldap_free_controls are old, use ldap_controls_free
//

{$EXTERNALSYM ldap_free_controlsA}
function ldap_free_controlsA(var Controls: PLDAPControlA): ULONG; cdecl;
{$EXTERNALSYM ldap_free_controlsW}
function ldap_free_controlsW(var Controls: PLDAPControlW): ULONG; cdecl;
{$EXTERNALSYM ldap_free_controls}
function ldap_free_controls(var Controls: PLDAPControl): ULONG; cdecl;

//
//  ldap_err2string returns a pointer to a string describing the error.  This
//  string should not be freed.
//

{$EXTERNALSYM ldap_err2stringA}
function ldap_err2stringA(err: ULONG): PAnsiChar; cdecl;
{$EXTERNALSYM ldap_err2stringW}
function ldap_err2stringW(err: ULONG): PWideChar; cdecl;
{$EXTERNALSYM ldap_err2string}
function ldap_err2string(err: ULONG): PChar; cdecl;

//
//  ldap_perror does nothing and is here just for compatibility.
//

{$EXTERNALSYM ldap_perror}
procedure ldap_perror(ld: PLDAP; msg: PChar); cdecl;

//
//  Return the first entry of a message.  It is freed when the message is
//  freed so should not be freed explicitly.
//

{$EXTERNALSYM ldap_first_entry}
function ldap_first_entry(ld: PLDAP; res: PLDAPMessage): PLDAPMessage; cdecl;

//
//  Return the next entry of a message.  It is freed when the message is
//  freed so should not be freed explicitly.
//

{$EXTERNALSYM ldap_next_entry}
function ldap_next_entry(ld: PLDAP; entry: PLDAPMessage): PLDAPMessage; cdecl;

//
//  Count the number of search entries returned by the server in a response
//  to a server request.
//

{$EXTERNALSYM ldap_count_entries}
function ldap_count_entries(ld: PLDAP; res: PLDAPMessage): ULONG; cdecl;

//
//  A BerElement really maps out to a C++ class object that does BER encoding.
//  Don't mess with it as it's opaque.
//
type
  PBerElement = ^BerElement;
  {$EXTERNALSYM BerElement}
  BerElement = record
    opaque: PChar;      // this is an opaque structure used just for
                        // compatibility with reference implementation
  end;

const
  {$EXTERNALSYM NULLBER}
  NULLBER = PBerElement(nil);

//
//  For a given entry, return the first attribute.  The pointer returned is
//  actually a buffer in the connection block(with allowances for
//  multi-threaded apps)so it should not be freed.
//

{$EXTERNALSYM ldap_first_attributeA}
function ldap_first_attributeA(ld: PLDAP; entry: PLDAPMessage;
  var ptr: PBerElement): PAnsiChar; cdecl;
{$EXTERNALSYM ldap_first_attributeW}
function ldap_first_attributeW(ld: PLDAP; entry: PLDAPMessage;
  var ptr: PBerElement): PWideChar; cdecl;
{$EXTERNALSYM ldap_first_attribute}
function ldap_first_attribute(ld: PLDAP; entry: PLDAPMessage;
  var ptr: PBerElement): PChar; cdecl;

//
//  Return the next attribute... again, the attribute pointer should not be
//  freed.
//

{$EXTERNALSYM ldap_next_attributeA}
function ldap_next_attributeA(ld: PLDAP; entry: PLDAPMessage;
  ptr: PBerElement): PAnsiChar; cdecl;
{$EXTERNALSYM ldap_next_attributeW}
function ldap_next_attributeW(ld: PLDAP; entry: PLDAPMessage;
  ptr: PBerElement): PWideChar; cdecl;
{$EXTERNALSYM ldap_next_attribute}
function ldap_next_attribute(ld: PLDAP; entry: PLDAPMessage;
  ptr: PBerElement): PChar; cdecl;


//
//  Get a given attribute's list of values.  This is used during parsing of
//  a search response.  It returns a list of pointers to values, the list is
//  null terminated.
//
//  If the values are generic octet strings and not null terminated strings,
//  use ldap_get_values_len instead.
//
//  The returned value should be freed when your done with it by calling
//  ldap_value_free.
//

{$EXTERNALSYM ldap_get_valuesA}
function ldap_get_valuesA(ld: PLDAP; entry: PLDAPMessage;
  attr: PAnsiChar): PPCharA; cdecl;
{$EXTERNALSYM ldap_get_valuesW}
function ldap_get_valuesW(ld: PLDAP; entry: PLDAPMessage;
  attr: PWideChar): PPCharW; cdecl;
{$EXTERNALSYM ldap_get_values}
function ldap_get_values(ld: PLDAP; entry: PLDAPMessage;
  attr: PChar): PPChar; cdecl;


//
//  Get a given attribute's list of values.  This is used during parsing of
//  a search response.  It returns a list of berval structures to values,
//  the list is null terminated.
//
//  If the values are null terminated strings, it may be easier to process them
//  by calling ldap_get_values instead.
//
//  The returned value should be freed when your done with it by calling
//  ldap_value_free_len.
//

{$EXTERNALSYM ldap_get_values_lenA}
function ldap_get_values_lenA(ExternalHandle: PLDAP; Message: PLDAPMessage;
 attr: PAnsiChar): PPLDAPBerVal; cdecl;
{$EXTERNALSYM ldap_get_values_lenW}
function ldap_get_values_lenW(ExternalHandle: PLDAP; Message: PLDAPMessage;
 attr: PWideChar): PPLDAPBerVal; cdecl;
{$EXTERNALSYM ldap_get_values_len}
function ldap_get_values_len(ExternalHandle: PLDAP; Message: PLDAPMessage;
 attr: PChar): PPLDAPBerVal; cdecl;


//
//  Return the number of values in a list returned by ldap_get_values.
//

{$EXTERNALSYM ldap_count_valuesA}
function ldap_count_valuesA(vals: PPCharA): ULONG; cdecl;
{$EXTERNALSYM ldap_count_valuesW}
function ldap_count_valuesW(vals: PPCharW): ULONG; cdecl;
{$EXTERNALSYM ldap_count_values}
function ldap_count_values(vals: PPChar): ULONG; cdecl;


//
//  Return the number of values in a list returned by ldap_get_values_len.
//

{$EXTERNALSYM ldap_count_values_len}
function ldap_count_values_len(vals: PPLDAPBerVal): ULONG; cdecl;

//
//  Free structures returned by ldap_get_values.
//

{$EXTERNALSYM ldap_value_freeA}
function ldap_value_freeA(vals: PPCharA): ULONG; cdecl;
{$EXTERNALSYM ldap_value_freeW}
function ldap_value_freeW(vals: PPCharW): ULONG; cdecl;
{$EXTERNALSYM ldap_value_free}
function ldap_value_free(vals: PPChar): ULONG; cdecl;


//
//  Free structures returned by ldap_get_values_len.
//

{$EXTERNALSYM ldap_value_free_len}
function ldap_value_free_len(vals: PPLDAPBerVal): ULONG; cdecl;

//
//  Get the distinguished name for a given search entry.  It should be freed
//  by calling ldap_memfree.
//

{$EXTERNALSYM ldap_get_dnA}
function ldap_get_dnA(ld: PLDAP; entry: PLDAPMessage): PAnsiChar; cdecl;
{$EXTERNALSYM ldap_get_dnW}
function ldap_get_dnW(ld: PLDAP; entry: PLDAPMessage): PWideChar; cdecl;
{$EXTERNALSYM ldap_get_dn}
function ldap_get_dn(ld: PLDAP; entry: PLDAPMessage): PChar; cdecl;


//
//  When using ldap_explode_dn, you should free the returned string by
//  calling ldap_value_free.
//

{$EXTERNALSYM ldap_explode_dnA}
function ldap_explode_dnA(dn: PAnsiChar; notypes: ULONG): PPCharA; cdecl;
{$EXTERNALSYM ldap_explode_dnW}
function ldap_explode_dnW(dn: PWideChar; notypes: ULONG): PPCharW; cdecl;
{$EXTERNALSYM ldap_explode_dn}
function ldap_explode_dn(dn: PChar; notypes: ULONG): PPChar; cdecl;


//
//  When calling ldap_dn2ufn, you should free the returned string by calling
//  ldap_memfree.
//

{$EXTERNALSYM ldap_dn2ufnA}
function ldap_dn2ufnA(dn: PAnsiChar): PAnsiChar; cdecl;
{$EXTERNALSYM ldap_dn2ufnW}
function ldap_dn2ufnW(dn: PWideChar): PWideChar; cdecl;
{$EXTERNALSYM ldap_dn2ufn}
function ldap_dn2ufn(dn: PChar): PChar; cdecl;


//
//  This is used to free strings back to the LDAP API heap.  Don't pass in
//  values that you've gotten from ldap_open, ldap_get_values, etc.
//

{$EXTERNALSYM ldap_memfreeA}
procedure ldap_memfreeA(Block: PAnsiChar); cdecl;
{$EXTERNALSYM ldap_memfreeW}
procedure ldap_memfreeW(Block: PWideChar); cdecl;
{$EXTERNALSYM ldap_memfree}
procedure ldap_memfree(Block: PChar); cdecl;

{$EXTERNALSYM ber_bvfree}
procedure ber_bvfree(bv: PLDAPBerVal); cdecl;


//
//  The function ldap_ufn2dn attempts to "normalize" a user specified DN
//  to make it "proper".  It follows RFC 1781(add CN= if not present,
//  add OU= if none present, etc).  If it runs into any problems at all
//  while normalizing, it simply returns a copy of what was passed in.
//
//  It allocates the output string from the LDAP memory pool.  If the pDn
//  comes back as non-NULL, you should free it when you're done with a call
//  to ldap_memfree.
//

{$EXTERNALSYM ldap_ufn2dnA}
function ldap_ufn2dnA(ufn: PAnsiChar; var pDn: PAnsiChar): ULONG; cdecl;
{$EXTERNALSYM ldap_ufn2dnW}
function ldap_ufn2dnW(ufn: PWideChar; var pDn: PWideChar): ULONG; cdecl;
{$EXTERNALSYM ldap_ufn2dn}
function ldap_ufn2dn(ufn: PChar; var pDn: PChar): ULONG; cdecl;

const
  {$EXTERNALSYM LBER_USE_DER}
  LBER_USE_DER            = $01;
  {$EXTERNALSYM LBER_USE_INDEFINITE_LEN}
  LBER_USE_INDEFINITE_LEN = $02;
  {$EXTERNALSYM LBER_TRANSLATE_STRINGS}
  LBER_TRANSLATE_STRINGS  = $04;

//
//  Call to initialize the LDAP library.  Pass in a version structure with
//  lv_size set to sizeof(LDAP_VERSION), lv_major set to LAPI_MAJOR_VER1,
//  and lv_minor set to LAPI_MINOR_VER1.  Return value will be either
//  LDAP_SUCCESS if OK or LDAP_OPERATIONS_ERROR if can't be supported.
//

  {$EXTERNALSYM LAPI_MAJOR_VER1}
  LAPI_MAJOR_VER1     = 1;
  {$EXTERNALSYM LAPI_MINOR_VER1}
  LAPI_MINOR_VER1     = 1;

type
  PLDAPVersionInfo = ^TLDAPVersionInfo;
  {$EXTERNALSYM PLDAP_VERSION_INFO}
  PLDAP_VERSION_INFO = ^LDAP_VERSION_INFO;
  {$EXTERNALSYM LDAP_VERSION_INFO}
  LDAP_VERSION_INFO = record
     lv_size: ULONG;
     lv_major: ULONG;
     lv_minor: ULONG;
  end;
  TLDAPVersionInfo = LDAP_VERSION_INFO;

{$EXTERNALSYM ldap_startup}
function ldap_startup(var version: TLDAPVersionInfo): ULONG; cdecl;

//
//  ldap_cleanup unloads the library when the refcount of opens goes to zero.
// (i.e. if a DLL calls it within a program that is also using it, it won't
//  free all resources)
//

{$EXTERNALSYM ldap_cleanup}
function ldap_cleanup(hInstance: THandle): ULONG; cdecl;


//
//  Extended API to support allowing opaque blobs of data in search filters.
//  This API takes any filter element and converts it to a safe text string that
//  can safely be passed in a search filter.
//  An example of using this is :
//
//  filter is something like guid=4826BF6CF0123444
//  this will put out on the wire guid of binary 0x4826BF6CF0123444
//
//  call ldap_escape_filter_element with sourceFilterElement pointing to
//  raw data, sourceCount set appropriately to length of data.
//
//  if destFilterElement is NULL, then return value is length required for
//  output buffer.
//
//  if destFilterElement is not NULL, then the function will copy the source
//  into the dest buffer and ensure that it is of a safe format.
//
//  then simply insert the dest buffer into your search filter after the
//  "attributetype=".
//
//  this will put out on the wire guid of binary 0x004826BF6CF000123444
//
//  Note : don't call this for attribute values that are really strings, as
//  we won't do any conversion from what you passed in to UTF-8.  Should only
//  be used for attributes that really are raw binary.
//

{$EXTERNALSYM ldap_escape_filter_elementA}
function ldap_escape_filter_elementA(
  sourceFilterElement: PChar; sourceLength: ULONG;
  destFilterElement: PAnsiChar; destLength: ULONG): ULONG; cdecl;
{$EXTERNALSYM ldap_escape_filter_elementW}
function ldap_escape_filter_elementW(
  sourceFilterElement: PChar; sourceLength: ULONG;
  destFilterElement: PWideChar; destLength: ULONG): ULONG; cdecl;
{$EXTERNALSYM ldap_escape_filter_element}
function ldap_escape_filter_element(
  sourceFilterElement: PChar; sourceLength: ULONG;
  destFilterElement: PChar; destLength: ULONG): ULONG; cdecl;


//
//  Misc extensions for additional debugging.
//
//  Note that these do nothing on free builds.
//

{$EXTERNALSYM ldap_set_dbg_flags}
function ldap_set_dbg_flags(NewFlags: ULONG): ULONG; cdecl;

// NOTE by translator: Original function type has ellipsis, which means
// there can be var_args. Object Pascal doesn't support this, so you'll
// have to define a function that does what you want (probably using BASM
// to get the extra parameters, or linking a C function), and then cast
// that to TDbgPrint.

type
  {$EXTERNALSYM DBGPRINT}
  DBGPRINT = function(Format: PChar {; ...} ): ULONG cdecl;
  TDbgPrint = DBGPRINT;

{$EXTERNALSYM ldap_set_dbg_routine}
procedure ldap_set_dbg_routine(DebugPrintRoutine: TDbgPrint); cdecl;

//
//  These routines are possibly useful by other modules.  Note that Win95
//  doesn't by default have the UTF-8 codepage loaded.  So a good way to
//  convert from UTF-8 to Unicode.
//

{$EXTERNALSYM LdapUTF8ToUnicode}
function LdapUTF8ToUnicode(lpSrcStr: LPCSTR; cchSrc: Integer;
  lpDestStr: LPWSTR; cchDest: Integer): Integer; cdecl;

{$EXTERNALSYM LdapUnicodeToUTF8}
function LdapUnicodeToUTF8(lpSrcStr: LPCWSTR; cchSrc: Integer;
  lpDestStr: LPSTR; cchDest: Integer): Integer; cdecl;

//
//  LDAPv3 features :
//
//  Sort Keys... these are used to ask the server to sort the results
//  before sending the results back.  LDAPv3 only and optional to implement
//  on the server side.  Check supportedControl for an OID of
//  "1.2.840.113556.1.4.473" to see if the server supports it.
//

const
  {$EXTERNALSYM LDAP_SERVER_SORT_OID}
  LDAP_SERVER_SORT_OID        = '1.2.840.113556.1.4.473';
  {$EXTERNALSYM LDAP_SERVER_SORT_OID_W}
  LDAP_SERVER_SORT_OID_W      = '1.2.840.113556.1.4.473';

  {$EXTERNALSYM LDAP_SERVER_RESP_SORT_OID}
  LDAP_SERVER_RESP_SORT_OID   = '1.2.840.113556.1.4.474';
  {$EXTERNALSYM LDAP_SERVER_RESP_SORT_OID_W}
  LDAP_SERVER_RESP_SORT_OID_W = '1.2.840.113556.1.4.474';

{
  NOTE from translator: I'm not quite sure about the following
  declaration:

  typedef struct ldapsearch LDAPSearch, *PLDAPSearch;
}

type
// Note from translator:
// The following two types don't have a TLDAPxxx type declared, since they are
// meant as opaque pointer types only, so a TLDAPxxx is not needed.

  {$EXTERNALSYM PLDAPSearch}
  PLDAPSearch = ^LDAPSearch;
  {$EXTERNALSYM LDAPSearch}
  LDAPSearch = record end;

  {$EXTERNALSYM PLDAPSortKeyA}
  PLDAPSortKeyA = ^LDAPSortKeyA;
  {$EXTERNALSYM PLDAPSortKeyW}
  PLDAPSortKeyW = ^LDAPSortKeyW;
  {$EXTERNALSYM PLDAPSortKey}
  PLDAPSortKey = PLDAPSortKeyA;
  {$EXTERNALSYM LDAPSortKeyA}
  LDAPSortKeyA = packed record
    sk_attrtype: PAnsiChar;
    sk_matchruleoid: PAnsiChar;
    sk_reverseorder: ByteBool;
  end;
  {$EXTERNALSYM LDAPSortKeyW}
  LDAPSortKeyW = packed record
    sk_attrtype: PWideChar;
    sk_matchruleoid: PWideChar;
    sk_reverseorder: ByteBool;
  end;
  {$EXTERNALSYM LDAPSortKey}
  LDAPSortKey = LDAPSortKeyA;

//
//  This API formats a list of sort keys into a search control.  Call
//  ldap_control_free when you're finished with the control.
//
//  Use this one rather than ldap_encode_sort_control as this is per RFC.
//

{$EXTERNALSYM ldap_create_sort_controlA}
function ldap_create_sort_controlA(ExternalHandle: PLDAP;
  var SortKeys: PLDAPSortKeyA; IsCritical: UCHAR;
  var Control: PLDAPControlA): ULONG; cdecl;
{$EXTERNALSYM ldap_create_sort_controlW}
function ldap_create_sort_controlW(ExternalHandle: PLDAP;
  var SortKeys: PLDAPSortKeyW; IsCritical: UCHAR;
  var Control: PLDAPControlW): ULONG; cdecl;
{$EXTERNALSYM ldap_create_sort_control}
function ldap_create_sort_control(ExternalHandle: PLDAP;
  var SortKeys: PLDAPSortKey; IsCritical: UCHAR;
  var Control: PLDAPControl): ULONG; cdecl;

//
//  This API parses the sort control returned by the server.  Use ldap_memfree
//  to free the attribute value, if it's returned.
//

{$EXTERNALSYM ldap_parse_sort_controlA}
function ldap_parse_sort_controlA(ExternalHandle: PLDAP;
  var Control: PLDAPControlA; var Result: ULONG;
  var Attribute: PAnsiChar): ULONG; cdecl;
{$EXTERNALSYM ldap_parse_sort_controlW}
function ldap_parse_sort_controlW(ExternalHandle: PLDAP;
  var Control: PLDAPControlW; var Result: ULONG;
  var Attribute: PWideChar): ULONG; cdecl;
{$EXTERNALSYM ldap_parse_sort_control}
function ldap_parse_sort_control(ExternalHandle: PLDAP;
  var Control: PLDAPControl; var Result: ULONG;
  var Attribute: PChar): ULONG; cdecl;

//
//  This API formats a list of sort keys into a search control.  Call
//  ldap_memfree for both Control->ldctl_value.bv_val and
//  Control->currentControl->ldctl_oid when you're finished with the control.
//
//  This is the old sort API that will be shortly pulled.  Please use
//  ldap_create_sort_control defined above.
//

{$EXTERNALSYM ldap_encode_sort_controlA}
function ldap_encode_sort_controlA(ExternalHandle: PLDAP;
  var SortKeys: PLDAPSortKeyA; Control: PLDAPControlA;
  Criticality: ByteBool): ULONG; cdecl;
{$EXTERNALSYM ldap_encode_sort_controlW}
function ldap_encode_sort_controlW(ExternalHandle: PLDAP;
  var SortKeys: PLDAPSortKeyW; Control: PLDAPControlW;
  Criticality: ByteBool): ULONG; cdecl;
{$EXTERNALSYM ldap_encode_sort_control}
function ldap_encode_sort_control(ExternalHandle: PLDAP;
  var SortKeys: PLDAPSortKey; Control: PLDAPControl;
  Criticality: ByteBool): ULONG; cdecl;


//
//  LDAPv3: This is the RFC defined API for the simple paging of results
//  control.  Use ldap_control_free to free the control allocated by
//  ldap_create_page_control.
//

{$EXTERNALSYM ldap_create_page_controlA}
function ldap_create_page_controlA(ExternalHandle: PLDAP;
  PageSize: ULONG; var Cookie: TLDAPBerVal; IsCritical: UCHAR;
  var Control: PLDAPControlA): ULONG; cdecl;
{$EXTERNALSYM ldap_create_page_controlW}
function ldap_create_page_controlW(ExternalHandle: PLDAP;
  PageSize: ULONG; var Cookie: TLDAPBerVal; IsCritical: UCHAR;
  var Control: PLDAPControlW): ULONG; cdecl;
{$EXTERNALSYM ldap_create_page_control}
function ldap_create_page_control(ExternalHandle: PLDAP;
  PageSize: ULONG; var Cookie: TLDAPBerVal; IsCritical: UCHAR;
  var Control: PLDAPControl): ULONG; cdecl;

{$EXTERNALSYM ldap_parse_page_controlA}
function ldap_parse_page_controlA(ExternalHandle: PLDAP;
  ServerControls: PPLDAPControlA; var TotalCount: ULONG;
  var Cookie: PLDAPBerVal): ULONG; cdecl; // Use ber_bvfree to free Cookie
{$EXTERNALSYM ldap_parse_page_controlW}
function ldap_parse_page_controlW(ExternalHandle: PLDAP;
  ServerControls: PPLDAPControlW; var TotalCount: ULONG;
  var Cookie: PLDAPBerVal): ULONG; cdecl; // Use ber_bvfree to free Cookie
{$EXTERNALSYM ldap_parse_page_control}
function ldap_parse_page_control(ExternalHandle: PLDAP;
  ServerControls: PPLDAPControl; var TotalCount: ULONG;
  var Cookie: PLDAPBerVal): ULONG; cdecl; // Use ber_bvfree to free Cookie


//
//  LDAPv3: This is the interface for simple paging of results.  To ensure
//  that the server supports it, check the supportedControl property off of
//  the root for an OID of 1.2.840.113556.1.4.319.  If it is there, then it
//  supports this feature.
//
//  If you're going to specify sort keys, see section above on sort keys on
//  now to tell if they're supported by the server.
//
//  You first call ldap_search_init_page.  If it returns a non-NULL LDAPSearch
//  block, then it worked ok.  Otherwise call LdapGetLastError to find error.
//
//  With a valid LDAPSearch block (there are opaque), call ldap_get_next_page
//  or ldap_get_next_page_s.  If you call ldap_get_next_page, you MUST call
//  ldap_get_paged_count for each set of results that you get for that message.
//  This allows the library to save off the cookie that the server sent to
//  resume the search.
//
//  Other than calling ldap_get_paged_count, the results you get back from
//  ldap_get_next_page can be treated as any other search result, and should
//  be freed when you're done by calling ldap_msgfree.
//
//  When the end of the search is hit, you'll get a return code of
//  LDAP_NO_RESULTS_RETURNED.  At this point, (or any point after LDAPSearch
//  structure has been allocated), you call ldap_search_abandon_page.  You
//  need to call this even after you get a return code of
//  LDAP_NO_RESULTS_RETURNED.
//
//  If you call ldap_get_next_page_s, you don't need to call
//  ldap_get_paged_count.
//

const
  {$EXTERNALSYM LDAP_PAGED_RESULT_OID_STRING}
  LDAP_PAGED_RESULT_OID_STRING   = '1.2.840.113556.1.4.319';
  {$EXTERNALSYM LDAP_PAGED_RESULT_OID_STRING_W}
  LDAP_PAGED_RESULT_OID_STRING_W = '1.2.840.113556.1.4.319';

{$EXTERNALSYM ldap_search_init_pageA}
function ldap_search_init_pageA(ExternalHandle: PLDAP;
  DistinguishedName: PAnsiChar; ScopeOfSearch: ULONG; SearchFilter: PAnsiChar;
  AttributeList: PPCharA; AttributesOnly: ULONG;
  var ServerControls, ClientControls: PLDAPControlA;
  PageTimeLimit, TotalSizeLimit: ULONG;
  var SortKeys: PLDAPSortKeyA): PLDAPSearch; cdecl;

{$EXTERNALSYM ldap_search_init_pageW}
function ldap_search_init_pageW(ExternalHandle: PLDAP;
  DistinguishedName: PWideChar; ScopeOfSearch: ULONG; SearchFilter: PWideChar;
  AttributeList: PPCharW; AttributesOnly: ULONG;
  var ServerControls, ClientControls: PLDAPControlW;
  PageTimeLimit, TotalSizeLimit: ULONG;
  var SortKeys: PLDAPSortKeyW): PLDAPSearch; cdecl;

{$EXTERNALSYM ldap_search_init_page}
function ldap_search_init_page(ExternalHandle: PLDAP;
  DistinguishedName: PChar; ScopeOfSearch: ULONG; SearchFilter: PChar;
  AttributeList: PPChar; AttributesOnly: ULONG;
  var ServerControls, ClientControls: PLDAPControl;
  PageTimeLimit, TotalSizeLimit: ULONG;
  var SortKeys: PLDAPSortKey): PLDAPSearch; cdecl;


{$EXTERNALSYM ldap_get_next_page}
function ldap_get_next_page(ExternalHandle: PLDAP; SearchHandle: PLDAPSearch;
  PageSize: ULONG; var MessageNumber: ULONG): ULONG; cdecl;

{$EXTERNALSYM ldap_get_next_page_s}
function ldap_get_next_page_s(ExternalHandle: PLDAP; SearchHandle: PLDAPSearch;
  var timeout: TLDAPTimeVal; PageSize: ULONG; var TotalCount: ULONG;
  var Results: PLDAPMessage): ULONG; cdecl;

{$EXTERNALSYM ldap_get_paged_count}
function ldap_get_paged_count(ExternalHandle: PLDAP; SearchBlock: PLDAPSearch;
  var TotalCount: ULONG; Results: PLDAPMessage): ULONG; cdecl;

{$EXTERNALSYM ldap_search_abandon_page}
function ldap_search_abandon_page(ExternalHandle: PLDAP;
  SearchBlock: PLDAPSearch): ULONG; cdecl;

//
//  These functions return subordinate referrals (references) that are returned
//  in search responses.  There are two types of referrals.  External referrals
//  where the naming context doesn't reside on the server (e.g. server says 'I
//  don't have the data, look over there') and Subordinate referrals (or
//  references) where some data has been returned and the referrals are passed
//  to other naming contexts below the current one (e.g. servers says 'Here's
//  some data from the tree I hold, go look here, there, and over there for
//  more data that is further down in the tree.').
//
//  These routines handle the latter.  For external references, use
//  ldap_parse_result.
//
//  Return the first reference from a message.  It is freed when the message is
//  freed so should not be freed explicitly.
//

{$EXTERNALSYM ldap_first_reference}
function ldap_first_reference(ld: PLDAP; res: PLDAPMessage): PLDAPMessage;

//
//  Return the next entry of a message.  It is freed when the message is
//  freed so should not be freed explicitly.
//

{$EXTERNALSYM ldap_next_reference}
function ldap_next_reference(ld: PLDAP; entry: PLDAPMessage): PLDAPMessage;

//
//  Count the number of subordinate references returned by the server in a
//  response to a search request.
//

{$EXTERNALSYM ldap_count_references}
function ldap_count_references(ld: PLDAP; res: PLDAPMessage): ULONG; cdecl;

//
//  We return the list of subordinate referrals in a search response message.
//

// free Referrals with ldap_value_freeW
{$EXTERNALSYM ldap_parse_referenceA}
function ldap_parse_referenceA(Connection: PLDAP; ResultMessage: PLDAPMessage;
  var Referrals: PPCharA): ULONG; cdecl;
{$EXTERNALSYM ldap_parse_referenceW}
function ldap_parse_referenceW(Connection: PLDAP; ResultMessage: PLDAPMessage;
  var Referrals: PPCharW): ULONG; cdecl;
{$EXTERNALSYM ldap_parse_reference}
function ldap_parse_reference(Connection: PLDAP; ResultMessage: PLDAPMessage;
  var Referrals: PPChar): ULONG; cdecl;

//
//  These APIs allow a client to send an extended request (free for all) to
//  an LDAPv3 (or above) server.  The functionality is fairly open... you can
//  send any request you'd like.  Note that since we don't know if you'll
//  be receiving a single or multiple responses, you'll have to explicitly tell
//  us when you're done with the request by calling ldap_close_extended_op.
//
//  These are thread safe.
//

{$EXTERNALSYM ldap_extended_operationA}
function ldap_extended_operationA(ld: PLDAP; Oid: PAnsiChar;
  var Data: TLDAPBerVal; var ServerControls, ClientControls: PLDAPControlA;
  var MessageNumber: ULONG): ULONG; cdecl;
{$EXTERNALSYM ldap_extended_operationW}
function ldap_extended_operationW(ld: PLDAP; Oid: PWideChar;
  var Data: TLDAPBerVal; var ServerControls, ClientControls: PLDAPControlW;
  var MessageNumber: ULONG): ULONG; cdecl;
{$EXTERNALSYM ldap_extended_operation}
function ldap_extended_operation(ld: PLDAP; Oid: PChar;
  var Data: TLDAPBerVal; var ServerControls, ClientControls: PLDAPControl;
  var MessageNumber: ULONG): ULONG; cdecl;

{$EXTERNALSYM ldap_close_extended_op}
function ldap_close_extended_op(ld: PLDAP; MessageNumber: ULONG): ULONG; cdecl;

//
//  Some enhancements that will probably never make it into the RFC related
//  to callouts to allow external caching of connections.
//
//  Call ldap_set_option( conn, LDAP_OPT_REFERRAL_CALLBACK, &referralRoutines )
//  where referralRoutines is the address of an LDAP_REFERRAL_CALLBACK
//  structure with your routines.  They may be NULL, in which case we'll
//  obviously not make the calls.
//
//  Any connections that are created will inherit the current callbacks from
//  the primary connection that the request was initiated on.
//

const
  {$EXTERNALSYM LDAP_OPT_REFERRAL_CALLBACK}
  LDAP_OPT_REFERRAL_CALLBACK = $70;

//
//  This first routine is called when we're about to chase a referral.  We
//  callout to it to see if there is already a connection cached that we
//  can use.  If so, the callback routine returns the pointer to the
//  connection to use in ConnectionToUse.  If not, it sets
//  *ConnectionToUse to NULL.
//
//  For a return code, it should return 0 if we should continue to chase the
//  referral.  If it returns a non-zero return code, we'll treat that as the
//  error code for chasing the referral.  This allows caching of host names
//  that are not reachable, if we decide to add that in the future.
//

type
  {$EXTERNALSYM QUERYFORCONNECTION}
  QUERYFORCONNECTION = function(
    PrimaryConnection: PLDAP;
    ReferralFromConnection: PLDAP;
    NewDN: PWideChar;
    HostName: PChar;
    PortNumber: ULONG;
    SecAuthIdentity: Pointer;    // if null, use CurrentUser below
    CurrentUserToken: Pointer;   // pointer to current user's LUID
    var ConnectionToUse: PLDAP):ULONG cdecl;
  TQueryForConnection = QUERYFORCONNECTION;

//
//  This next function is called when we've created a new connection while
//  chasing a referral.  Note that it gets assigned the same callback functions
//  as the PrimaryConnection.  If the return code is FALSE, then the call
//  back function doesn't want to cache the connection and it will be
//  destroyed after the operation is complete.  If TRUE is returned, we'll
//  assume that the callee has taken ownership of the connection and it will
//  not be destroyed after the operation is complete.
//
//  If the ErrorCodeFromBind field is not 0, then the bind operation to
//  that server failed.
//

  {$EXTERNALSYM NOTIFYOFNEWCONNECTION}
  NOTIFYOFNEWCONNECTION = function(
    PrimaryConnection: PLDAP;
    ReferralFromConnection: PLDAP;
    NewDN: PWideChar;
    HostName: PChar;
    NewConnection: PLDAP;
    PortNumber: ULONG;
    SecAuthIdentity: Pointer;    // if null, use CurrentUser below
    CurrentUser: Pointer;        // pointer to current user's LUID
    ErrorCodeFromBind: ULONG): ByteBool cdecl;
  TNotifyOfNewConnection = NOTIFYOFNEWCONNECTION;

//
//  This next function is called when we've successfully called off to the
//  QueryForConnection call and received a connection OR when we called off
//  to the NotifyOfNewConnection call and it returned TRUE.  We call this
//  function when we're dereferencing the connection after we're done with it.
//
//  Return code is currently ignored, but the function should return
//  LDAP_SUCCESS if all went well.
//

 {$EXTERNALSYM DEREFERENCECONNECTION}
 DEREFERENCECONNECTION = function(PrimaryConnection: PLDAP;
   ConnectionToDereference: PLDAP): ULONG cdecl;
 TDereferenceConnection = DEREFERENCECONNECTION;

  PLDAPReferralCallback = ^TLDAPReferralCallback;
  {$EXTERNALSYM LdapReferralCallback}
  LdapReferralCallback = packed record
    SizeOfCallbacks: ULONG;        // set to sizeof( LDAP_REFERRAL_CALLBACK )
    QueryForConnection: QUERYFORCONNECTION;
    NotifyRoutine: NOTIFYOFNEWCONNECTION;
    DereferenceRoutine: DEREFERENCECONNECTION;
  end;
  {$EXTERNALSYM LDAP_REFERRAL_CALLBACK}
  LDAP_REFERRAL_CALLBACK = LdapReferralCallback;
  {$EXTERNALSYM PLDAP_REFERRAL_CALLBACK}
  PLDAP_REFERRAL_CALLBACK = ^LdapReferralCallback;
  TLDAPReferralCallback = LdapReferralCallback;

//
//  Thread Safe way to get last error code returned by LDAP API is to call
//  LdapGetLastError();
//

{$EXTERNALSYM LdapGetLastError}
function LdapGetLastError: ULONG; cdecl;

//
//  Translate from LdapError to closest Win32 error code.
//

{$EXTERNALSYM LdapMapErrorToWin32}
function LdapMapErrorToWin32(LdapError: ULONG): ULONG; cdecl;

//
// This is an arrangement for specifying client certificates while establishing
// an SSL connection.
// Simply Call ldap_set_option( conn, LDAP_OPT_CLIENT_CERTIFICATE, &CertRoutine )
// where CertRoutine is the address of your callback routine. If it is NULL,
// we will obviously not make the call.
//

const
  {$EXTERNALSYM LDAP_OPT_CLIENT_CERTIFICATE}
  LDAP_OPT_CLIENT_CERTIFICATE    = $80;

//
// This callback is invoked when the server demands a client certificate for
// authorization. We pass a structure containing a list of server-trusted
// Certificate Authorities. If the client has certificates to provide, it
// converts them to CERT_CONTEXTs and adds them to the given certificate
// store. LDAP subsequently passes these credentials to the SSL server as part
// of the handshake.
//

type
  {$EXTERNALSYM QUERYCLIENTCERT}
  QUERYCLIENTCERT = function(
    Connection: PLDAP;
    trusted_CAs: Pointer {PSecPkgContext_IssuerListInfoEx};
    hCertStore: LongWord {HCERTSTORE};
    var pcCreds: DWORD
  ): ByteBool cdecl;

//
// We are also giving an opportunity for the client to verify the certificate
// of the server. The client registers a callback which is invoked after the
// secure connection is setup. The server certificate is presented to the
// client who invokes it and decides it it is acceptable. To register this
// callback, simply call ldap_set_option( conn, LDAP_OPT_SERVER_CERTIFICATE, &CertRoutine )
//

const
  {$EXTERNALSYM LDAP_OPT_SERVER_CERTIFICATE}
  LDAP_OPT_SERVER_CERTIFICATE    = $81;

//
// This function is called after the secure connection has been established. The
// certificate of the server is supplied for examination by the client. If the
// client approves it, it returns TRUE else, it returns false and the secure
// connection is torn down.
//

type
  VERIFYSERVERCERT = function(
    Connection: PLDAP;
    pServerCert: Pointer {PCCERT_CONTEXT}
  ): ByteBool cdecl;



//
//  Given an LDAP message, return the connection pointer where the message
//  came from.  It can return NULL if the connection has already been freed.
//

{$EXTERNALSYM ldap_conn_from_msg}
function ldap_conn_from_msg(PrimaryConn: PLDAP; res: PLDAPMessage): PLDAP; cdecl;

//
//  Do we reference the connection for each message so that we can safely get
//  the connection pointer back by calling ldap_conn_from_msg?
//
const
  {$EXTERNALSYM LDAP_OPT_REF_DEREF_CONN_PER_MSG}
  LDAP_OPT_REF_DEREF_CONN_PER_MSG = $94;


implementation

const
  LDAPLib = 'wldap32.dll';

function ldap_openA; external LDAPLib name 'ldap_openA';
function ldap_openW; external LDAPLib name 'ldap_openW';
function ldap_open; external LDAPLib name 'ldap_openA';
function ldap_initA; external LDAPLib name 'ldap_initA';
function ldap_initW; external LDAPLib name 'ldap_initW';
function ldap_init; external LDAPLib name 'ldap_initA';
function ldap_sslinitA; external LDAPLib name 'ldap_sslinitA';
function ldap_sslinitW; external LDAPLib name 'ldap_sslinitW';
function ldap_sslinit; external LDAPLib name 'ldap_sslinitA';
function cldap_openA; external LDAPLib name 'cldap_openA';
function cldap_openW; external LDAPLib name 'cldap_openW';
function cldap_open; external LDAPLib name 'cldap_openA';
function ldap_simple_bindA; external LDAPLib name 'ldap_simple_bindA';
function ldap_simple_bindW; external LDAPLib name 'ldap_simple_bindW';
function ldap_simple_bind; external LDAPLib name 'ldap_simple_bindA';
function ldap_simple_bind_sA; external LDAPLib name 'ldap_simple_bind_sA';
function ldap_simple_bind_sW; external LDAPLib name 'ldap_simple_bind_sW';
function ldap_simple_bind_s; external LDAPLib name 'ldap_simple_bind_sA';
function ldap_bindA; external LDAPLib name 'ldap_bindA';
function ldap_bindW; external LDAPLib name 'ldap_bindW';
function ldap_bind; external LDAPLib name 'ldap_bindA';
function ldap_bind_sA; external LDAPLib name 'ldap_bind_sA';
function ldap_bind_sW; external LDAPLib name 'ldap_bind_sW';
function ldap_bind_s; external LDAPLib name 'ldap_bind_sA';
function ldap_sasl_bindA; external LDAPLib name 'ldap_sasl_bindA';
function ldap_sasl_bindW; external LDAPLib name 'ldap_sasl_bindW';
function ldap_sasl_bind; external LDAPLib name 'ldap_sasl_bindA';
function ldap_sasl_bind_sA; external LDAPLib name 'ldap_sasl_bind_sA';
function ldap_sasl_bind_sW; external LDAPLib name 'ldap_sasl_bind_sW';
function ldap_sasl_bind_s; external LDAPLib name 'ldap_sasl_bind_sA';
function ldap_searchA; external LDAPLib name 'ldap_searchA';
function ldap_searchW; external LDAPLib name 'ldap_searchW';
function ldap_search; external LDAPLib name 'ldap_searchA';
function ldap_search_sA; external LDAPLib name 'ldap_search_sA';
function ldap_search_sW; external LDAPLib name 'ldap_search_sW';
function ldap_search_s; external LDAPLib name 'ldap_search_sA';
function ldap_search_stA; external LDAPLib name 'ldap_search_stA';
function ldap_search_stW; external LDAPLib name 'ldap_search_stW';
function ldap_search_st; external LDAPLib name 'ldap_search_stA';
function ldap_modifyA; external LDAPLib name 'ldap_modifyA';
function ldap_modifyW; external LDAPLib name 'ldap_modifyW';
function ldap_modify; external LDAPLib name 'ldap_modifyA';
function ldap_modify_sA; external LDAPLib name 'ldap_modify_sA';
function ldap_modify_sW; external LDAPLib name 'ldap_modify_sW';
function ldap_modify_s; external LDAPLib name 'ldap_modify_sA';
function ldap_modrdn2A; external LDAPLib name 'ldap_modrdn2A';
function ldap_modrdn2W; external LDAPLib name 'ldap_modrdn2W';
function ldap_modrdn2; external LDAPLib name 'ldap_modrdn2A';
function ldap_modrdnA; external LDAPLib name 'ldap_modrdnA';
function ldap_modrdnW; external LDAPLib name 'ldap_modrdnW';
function ldap_modrdn; external LDAPLib name 'ldap_modrdnA';
function ldap_modrdn2_sA; external LDAPLib name 'ldap_modrdn2_sA';
function ldap_modrdn2_sW; external LDAPLib name 'ldap_modrdn2_sW';
function ldap_modrdn2_s; external LDAPLib name 'ldap_modrdn2_sA';
function ldap_modrdn_sA; external LDAPLib name 'ldap_modrdn_sA';
function ldap_modrdn_sW; external LDAPLib name 'ldap_modrdn_sW';
function ldap_modrdn_s; external LDAPLib name 'ldap_modrdn_sA';
function ldap_addA; external LDAPLib name 'ldap_addA';
function ldap_addW; external LDAPLib name 'ldap_addW';
function ldap_add; external LDAPLib name 'ldap_addA';
function ldap_add_sA; external LDAPLib name 'ldap_add_sA';
function ldap_add_sW; external LDAPLib name 'ldap_add_sW';
function ldap_add_s; external LDAPLib name 'ldap_add_sA';
function ldap_compareA; external LDAPLib name 'ldap_compareA';
function ldap_compareW; external LDAPLib name 'ldap_compareW';
function ldap_compare; external LDAPLib name 'ldap_compareA';
function ldap_compare_sA; external LDAPLib name 'ldap_compare_sA';
function ldap_compare_sW; external LDAPLib name 'ldap_compare_sW';
function ldap_compare_s; external LDAPLib name 'ldap_compare_sA';
function ldap_deleteA; external LDAPLib name 'ldap_deleteA';
function ldap_deleteW; external LDAPLib name 'ldap_deleteW';
function ldap_delete; external LDAPLib name 'ldap_deleteA';
function ldap_delete_sA; external LDAPLib name 'ldap_delete_sA';
function ldap_delete_sW; external LDAPLib name 'ldap_delete_sW';
function ldap_delete_s; external LDAPLib name 'ldap_delete_sA';
function ldap_err2stringA; external LDAPLib name 'ldap_err2stringA';
function ldap_err2stringW; external LDAPLib name 'ldap_err2stringW';
function ldap_err2string; external LDAPLib name 'ldap_err2stringA';
function ldap_first_attributeA; external LDAPLib name 'ldap_first_attributeA';
function ldap_first_attributeW; external LDAPLib name 'ldap_first_attributeW';
function ldap_first_attribute; external LDAPLib name 'ldap_first_attributeA';
function ldap_next_attributeA; external LDAPLib name 'ldap_next_attributeA';
function ldap_next_attributeW; external LDAPLib name 'ldap_next_attributeW';
function ldap_next_attribute; external LDAPLib name 'ldap_next_attributeA';
function ldap_get_valuesA; external LDAPLib name 'ldap_get_valuesA';
function ldap_get_valuesW; external LDAPLib name 'ldap_get_valuesW';
function ldap_get_values; external LDAPLib name 'ldap_get_valuesA';
function ldap_get_values_lenA; external LDAPLib name 'ldap_get_values_lenA';
function ldap_get_values_lenW; external LDAPLib name 'ldap_get_values_lenW';
function ldap_get_values_len; external LDAPLib name 'ldap_get_values_lenA';
function ldap_count_valuesA; external LDAPLib name 'ldap_count_valuesA';
function ldap_count_valuesW; external LDAPLib name 'ldap_count_valuesW';
function ldap_count_values; external LDAPLib name 'ldap_count_valuesA';
function ldap_value_freeA; external LDAPLib name 'ldap_value_freeA';
function ldap_value_freeW; external LDAPLib name 'ldap_value_freeW';
function ldap_value_free; external LDAPLib name 'ldap_value_freeA';
function ldap_get_dnA; external LDAPLib name 'ldap_get_dnA';
function ldap_get_dnW; external LDAPLib name 'ldap_get_dnW';
function ldap_get_dn; external LDAPLib name 'ldap_get_dnA';
function ldap_explode_dnA; external LDAPLib name 'ldap_explode_dnA';
function ldap_explode_dnW; external LDAPLib name 'ldap_explode_dnW';
function ldap_explode_dn; external LDAPLib name 'ldap_explode_dnA';
function ldap_dn2ufnA; external LDAPLib name 'ldap_dn2ufnA';
function ldap_dn2ufnW; external LDAPLib name 'ldap_dn2ufnW';
function ldap_dn2ufn; external LDAPLib name 'ldap_dn2ufnA';
procedure ldap_memfreeA; external LDAPLib name 'ldap_memfreeA';
procedure ldap_memfreeW; external LDAPLib name 'ldap_memfreeW';
procedure ldap_memfree; external LDAPLib name 'ldap_memfreeA';
function ldap_ufn2dnA; external LDAPLib name 'ldap_ufn2dnA';
function ldap_ufn2dnW; external LDAPLib name 'ldap_ufn2dnW';
function ldap_ufn2dn; external LDAPLib name 'ldap_ufn2dnA';
function ldap_escape_filter_elementA; external LDAPLib name 'ldap_escape_filter_elementA';
function ldap_escape_filter_elementW; external LDAPLib name 'ldap_escape_filter_elementW';
function ldap_escape_filter_element; external LDAPLib name 'ldap_escape_filter_elementA';
function ldap_search_extA; external LDAPLib name 'ldap_search_extA';
function ldap_search_extW; external LDAPLib name 'ldap_search_extW';
function ldap_search_ext; external LDAPLib name 'ldap_search_extA';
function ldap_search_ext_sA; external LDAPLib name 'ldap_search_ext_sA';
function ldap_search_ext_sW; external LDAPLib name 'ldap_search_ext_sW';
function ldap_search_ext_s; external LDAPLib name 'ldap_search_ext_sA';
function ldap_check_filterA; EXTERNAL LDAPLib name 'ldap_check_filterA';
function ldap_check_filterW; EXTERNAL LDAPLib name 'ldap_check_filterW';
function ldap_check_filter; EXTERNAL LDAPLib name 'ldap_check_filterA';
function ldap_modify_extA; external LDAPLib name 'ldap_modify_extA';
function ldap_modify_extW; external LDAPLib name 'ldap_modify_extW';
function ldap_modify_ext; external LDAPLib name 'ldap_modify_extA';
function ldap_modify_ext_sA; external LDAPLib name 'ldap_modify_ext_sA';
function ldap_modify_ext_sW; external LDAPLib name 'ldap_modify_ext_sW';
function ldap_modify_ext_s; external LDAPLib name 'ldap_modify_ext_sA';
function ldap_rename_extA; external LDAPLib name 'ldap_rename_extA';
function ldap_rename_extW; external LDAPLib name 'ldap_rename_extW';
function ldap_rename_ext; external LDAPLib name 'ldap_rename_extA';
function ldap_rename_ext_sA; external LDAPLib name 'ldap_rename_ext_sA';
function ldap_rename_ext_sW; external LDAPLib name 'ldap_rename_ext_sW';
function ldap_rename_ext_s; external LDAPLib name 'ldap_rename_ext_sA';
function ldap_add_extA; external LDAPLib name 'ldap_add_extA';
function ldap_add_extW; external LDAPLib name 'ldap_add_extW';
function ldap_add_ext; external LDAPLib name 'ldap_add_extA';
function ldap_add_ext_sA; external LDAPLib name 'ldap_add_ext_sA';
function ldap_add_ext_sW; external LDAPLib name 'ldap_add_ext_sW';
function ldap_add_ext_s; external LDAPLib name 'ldap_add_ext_sA';
function ldap_compare_extA; external LDAPLib name 'ldap_compare_extA';
function ldap_compare_extW; external LDAPLib name 'ldap_compare_extW';
function ldap_compare_ext; external LDAPLib name 'ldap_compare_extA';
function ldap_compare_ext_sA; external LDAPLib name 'ldap_compare_ext_sA';
function ldap_compare_ext_sW; external LDAPLib name 'ldap_compare_ext_sW';
function ldap_compare_ext_s; external LDAPLib name 'ldap_compare_ext_sA';
function ldap_delete_extA; external LDAPLib name 'ldap_delete_extA';
function ldap_delete_extW; external LDAPLib name 'ldap_delete_extW';
function ldap_delete_ext; external LDAPLib name 'ldap_delete_extA';
function ldap_delete_ext_sA; external LDAPLib name 'ldap_delete_ext_sA';
function ldap_delete_ext_sW; external LDAPLib name 'ldap_delete_ext_sW';
function ldap_delete_ext_s; external LDAPLib name 'ldap_delete_ext_sA';
function ldap_parse_resultA; external LDAPLib name 'ldap_parse_resultA';
function ldap_parse_resultW; external LDAPLib name 'ldap_parse_resultW';
function ldap_parse_result; external LDAPLib name 'ldap_parse_resultA';
function ldap_controls_freeA; external LDAPLib name 'ldap_controls_freeA';
function ldap_controls_freeW; external LDAPLib name 'ldap_controls_freeW';
function ldap_controls_free; external LDAPLib name 'ldap_controls_freeA';
function ldap_parse_extended_resultA; external LDAPLib name 'ldap_parse_extended_resultA';
function ldap_parse_extended_resultW; external LDAPLib name 'ldap_parse_extended_resultW';
function ldap_parse_extended_result; external LDAPLib name 'ldap_parse_extended_resultA';
function ldap_control_freeA; external LDAPLib name 'ldap_control_freeA';
function ldap_control_freeW; external LDAPLib name 'ldap_control_freeW';
function ldap_control_free; external LDAPLib name 'ldap_control_freeA';
function ldap_free_controlsA; external LDAPLib name 'ldap_free_controlsA';
function ldap_free_controlsW; external LDAPLib name 'ldap_free_controlsW';
function ldap_free_controls; external LDAPLib name 'ldap_free_controlsA';
function ldap_create_sort_controlA; external LDAPLib name 'ldap_create_sort_controlA';
function ldap_create_sort_controlW; external LDAPLib name 'ldap_create_sort_controlW';
function ldap_create_sort_control; external LDAPLib name 'ldap_create_sort_controlA';
function ldap_parse_sort_controlA; external LDAPLib name 'ldap_parse_sort_controlA';
function ldap_parse_sort_controlW; external LDAPLib name 'ldap_parse_sort_controlW';
function ldap_parse_sort_control; external LDAPLib name 'ldap_parse_sort_controlA';
function ldap_encode_sort_controlA; external LDAPLib name 'ldap_encode_sort_controlA';
function ldap_encode_sort_controlW; external LDAPLib name 'ldap_encode_sort_controlW';
function ldap_encode_sort_control; external LDAPLib name 'ldap_encode_sort_controlA';
function ldap_create_page_controlA; external LDAPLib name 'ldap_create_page_controlA';
function ldap_create_page_controlW; external LDAPLib name 'ldap_create_page_controlW';
function ldap_create_page_control; external LDAPLib name 'ldap_create_page_controlA';
function ldap_parse_page_controlA; external LDAPLib name 'ldap_parse_page_controlA';
function ldap_parse_page_controlW; external LDAPLib name 'ldap_parse_page_controlW';
function ldap_parse_page_control; external LDAPLib name 'ldap_parse_page_controlA';
function ldap_search_init_pageA; external LDAPLib name 'ldap_search_init_pageA';
function ldap_search_init_pageW; external LDAPLib name 'ldap_search_init_pageW';
function ldap_search_init_page; external LDAPLib name 'ldap_search_init_pageA';
function ldap_parse_referenceA; external LDAPLib name 'ldap_parse_referenceA';
function ldap_parse_referenceW; external LDAPLib name 'ldap_parse_referenceW';
function ldap_parse_reference; external LDAPLib name 'ldap_parse_referenceA';
function ldap_extended_operationA; external LDAPLib name 'ldap_extended_operationA';
function ldap_extended_operationW; external LDAPLib name 'ldap_extended_operationW';
function ldap_extended_operation; external LDAPLib name 'ldap_extended_operationA';
function ldap_unbind; external LDAPLib name 'ldap_unbind';
function ldap_unbind_s; external LDAPLib name 'ldap_unbind_s';
function ldap_get_option; external LDAPLib name 'ldap_get_option';
function ldap_set_option; external LDAPLib name 'ldap_set_option';
function ldap_get_optionW; external LDAPLib name 'ldap_get_optionW';
function ldap_set_optionW; external LDAPLib name 'ldap_set_optionW';
function ldap_abandon; external LDAPLib name 'ldap_abandon';
function ldap_result; external LDAPLib name 'ldap_result';
function ldap_msgfree; external LDAPLib name 'ldap_msgfree';
function ldap_result2error; external LDAPLib name 'ldap_result2error';
procedure ldap_perror; external LDAPLib name 'ldap_perror';
function ldap_first_entry; external LDAPLib name 'ldap_first_entry';
function ldap_next_entry; external LDAPLib name 'ldap_next_entry';
function ldap_count_entries; external LDAPLib name 'ldap_count_entries';
function ldap_count_values_len; external LDAPLib name 'ldap_count_values_len';
function ldap_value_free_len; external LDAPLib name 'ldap_value_free_len';
function ldap_startup; external LDAPLib name 'ldap_startup';
function ldap_cleanup; external LDAPLib name 'ldap_cleanup';
function ldap_set_dbg_flags; external LDAPLib name 'ldap_set_dbg_flags';
function ldap_connect; external LDAPLib name 'ldap_connect';
procedure ber_bvfree; external LDAPLib name 'ber_bvfree';
procedure ldap_set_dbg_routine; external LDAPLib name 'ldap_set_dbg_routine';
function LdapUTF8ToUnicode; external LDAPLib name 'LdapUTF8ToUnicode';
function LdapUnicodeToUTF8; external LDAPLib name 'LdapUnicodeToUTF8';
function ldap_get_next_page; external LDAPLib name 'ldap_get_next_page';
function ldap_get_next_page_s; external LDAPLib name 'ldap_get_next_page_s';
function ldap_get_paged_count; external LDAPLib name 'ldap_get_paged_count';
function ldap_search_abandon_page; external LDAPLib name 'ldap_search_abandon_page';
function ldap_first_reference; external LDAPLib name 'ldap_first_reference';
function ldap_next_reference; external LDAPLib name 'ldap_next_reference';
function ldap_count_references; external LDAPLib name 'ldap_count_references';
function ldap_close_extended_op; external LDAPLib name 'ldap_close_extended_op';
function LdapGetLastError; external LDAPLib name 'LdapGetLastError';
function LdapMapErrorToWin32; external LDAPLib name 'LdapMapErrorToWin32';
function ldap_conn_from_msg; external LDAPLib name 'ldap_conn_from_msg';



// Macros.
function LDAP_IS_CLDAP(ld: PLDAP): boolean;
begin
  Result :=(ld^.ld_sb.sb_naddr > 0);
end;

function NAME_ERROR(n: integer): boolean;
begin
  Result :=((n and $f0) = $20);
end;

end.

