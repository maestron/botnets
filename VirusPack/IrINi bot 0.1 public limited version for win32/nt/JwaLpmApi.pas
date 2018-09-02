{******************************************************************************}
{                                                       	               }
{ Winsock2 RSVP/LPM API interface Unit for Object Pascal                       }
{                                                       	               }
{ Portions created by Microsoft are Copyright (C) 1995-2001 Microsoft          }
{ Corporation. All Rights Reserved.                                            }
{ 								               }
{ The original file is: lpmapi.h, released June 2000. The original Pascal      }
{ code is: LpmApi.pas, released December 2000. The initial developer of the    }
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

unit JwaLpmApi;

{$WEAKPACKAGEUNIT}

{$HPPEMIT ''}
{$HPPEMIT '#include "lpmapi.h"'}
{$HPPEMIT ''}

{$I WINDEFINES.INC}

interface

uses
  JwaWinSock2, JwaWinType;

type
  FLOAT = Single;
  {$NODEFINE FLOAT}

(****************************************************************************

            RSVPD -- ReSerVation Protocol Daemon

                USC Information Sciences Institute
                Marina del Rey, California

        Original Version: Shai Herzog, Nov. 1993.
        Current Version:  Steven Berson & Bob Braden, may 1996.

  Copyright (c) 1996 by the University of Southern California
  All rights reserved.

  Permission to use, copy, modify, and distribute this software and its
  documentation in source and binary forms for any purpose and without
  fee is hereby granted, provided that both the above copyright notice
  and this permission notice appear in all copies, and that any
  documentation, advertising materials, and other materials related to
  such distribution and use acknowledge that the software was developed
  in part by the University of Southern California, Information
  Sciences Institute.  The name of the University may not be used to
  endorse or promote products derived from this software without
  specific prior written permission.

  THE UNIVERSITY OF SOUTHERN CALIFORNIA makes no representations about
  the suitability of this software for any purpose.  THIS SOFTWARE IS
  PROVIDED "AS IS" AND WITHOUT ANY EXPRESS OR IMPLIED WARRANTIES,
  INCLUDING, WITHOUT LIMITATION, THE IMPLIED WARRANTIES OF
  MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.

  Other copyrights might apply to parts of this software and are so
  noted when applicable.

********************************************************************)

(*
 *  Standard format of an RSVP object header
 *)

type
  RsvpObjHdr = record
    obj_length: USHORT; (* Length in bytes *)
    obj_class: UCHAR;   (* Class (values defined below) *)
    obj_ctype: UCHAR;   (* C-Type (values defined below) *)
  end;
  {$EXTERNALSYM RsvpObjHdr}
  TRsvpObjHdr = RsvpObjHdr;
  PRsvpObjHdr = ^RsvpObjHdr;
  PPRsvpObjHdr = ^PRsvpObjHdr;


function ObjLength(const x: TRsvpObjHdr): USHORT;
{$EXTERNALSYM ObjLength}
function ObjCType(const x: TRsvpObjHdr): UCHAR;
{$EXTERNALSYM ObjCType}
function ObjClass(const x: TRsvpObjHdr): UCHAR;
{$EXTERNALSYM ObjClass}
function ObjData(const x: TRsvpObjHdr): Pointer;
{$EXTERNALSYM ObjData}

(*
 *  Define object classes: Class-Num values
 *)

const
  class_NULL            = 0;
  {$EXTERNALSYM class_NULL}
  class_SESSION         = 1;
  {$EXTERNALSYM class_SESSION}
  class_SESSION_GROUP   = 2;
  {$EXTERNALSYM class_SESSION_GROUP}
  class_RSVP_HOP        = 3;
  {$EXTERNALSYM class_RSVP_HOP}
  class_INTEGRITY       = 4;
  {$EXTERNALSYM class_INTEGRITY}
  class_TIME_VALUES     = 5;
  {$EXTERNALSYM class_TIME_VALUES}
  class_ERROR_SPEC      = 6;
  {$EXTERNALSYM class_ERROR_SPEC}
  class_SCOPE           = 7;
  {$EXTERNALSYM class_SCOPE}
  class_STYLE           = 8;
  {$EXTERNALSYM class_STYLE}
  class_FLOWSPEC        = 9; // these two are the same
  {$EXTERNALSYM class_FLOWSPEC}
  class_IS_FLOWSPEC     = 9; // since we added IS in front of the name
  {$EXTERNALSYM class_IS_FLOWSPEC}
  class_FILTER_SPEC     = 10;
  {$EXTERNALSYM class_FILTER_SPEC}
  class_SENDER_TEMPLATE = 11;
  {$EXTERNALSYM class_SENDER_TEMPLATE}
  class_SENDER_TSPEC    = 12;
  {$EXTERNALSYM class_SENDER_TSPEC}
  class_ADSPEC          = 13;
  {$EXTERNALSYM class_ADSPEC}
  class_POLICY_DATA     = 14;
  {$EXTERNALSYM class_POLICY_DATA}
  class_CONFIRM         = 15;
  {$EXTERNALSYM class_CONFIRM}
  class_MAX             = 15;
  {$EXTERNALSYM class_MAX}

(*
 *  RSVP SESSION object
 *)

  ctype_SESSION_ipv4    = 1;
  {$EXTERNALSYM ctype_SESSION_ipv4}
  ctype_SESSION_ipv4GPI = 3   (* IPSEC: Generalized Port Id *);
  {$EXTERNALSYM ctype_SESSION_ipv4GPI}

  SESSFLG_E_Police = $01    (* E_Police: Entry policing flag*);
  {$EXTERNALSYM SESSFLG_E_Police}

type
  Session_IPv4 = record
    sess_destaddr: IN_ADDR;  // DestAddress
    sess_protid: UCHAR;    // Protocol Id
    sess_flags: UCHAR;     // Use the flags defined above
    sess_destport: USHORT;  // DestPort
  end;
  {$EXTERNALSYM Session_IPv4}
  TSessionIPv4 = Session_IPv4;
  PSessionIPv4 = ^Session_IPv4;

(*    GPI versions have virtual dest port instead of dest port; this
 *    changes the interpretation but not the format, so we do not
 *    define new structs for GPI.
 *)

  RSVP_SESSION = record
    sess_header: RsvpObjHdr;
    case Integer of
      0: (sess_ipv4: Session_IPv4);
  end;
  {$EXTERNALSYM RSVP_SESSION}
  TRsvpSession = RSVP_SESSION;
  PRsvpSession = ^RSVP_SESSION;  

// Useful defines to access components of SESSION obect

//#define Sess4Addr       sess_u.sess_ipv4.sess_destaddr
//#define Sess4Port       sess_u.sess_ipv4.sess_destport
//#define Sess4Protocol   sess_u.sess_ipv4.sess_protid
//#define Sess4Flags      sess_u.sess_ipv4.sess_flags

(*
 *  RSVP HOP object
 *)

const
  ctype_RSVP_HOP_ipv4 = 1;
  {$EXTERNALSYM ctype_RSVP_HOP_ipv4}

type
  Rsvp_Hop_IPv4 = record
    hop_ipaddr: IN_ADDR;   // Next/Previous Hop Address
    hop_LIH: ULONG;        // Logical Interface Handle
  end;
  {$EXTERNALSYM Rsvp_Hop_IPv4}
  TRsvpHopIPv4 = Rsvp_Hop_IPv4;
  PRsvpHopIPv4 = ^Rsvp_Hop_IPv4;

  RSVP_HOP = record
    hop_header: RsvpObjHdr;
    case Integer of
      0: (hop_ipv4: Rsvp_Hop_IPv4);
  end;
  {$EXTERNALSYM RSVP_HOP}
  TRsvpHop = RSVP_HOP;
  PRsvpHop = ^RSVP_HOP;

//#define Hop4LIH    hop_u.hop_ipv4.hop_LIH
//#define Hop4Addr   hop_u.hop_ipv4.hop_ipaddr

(*
 *  RSVP STYLE object
 *)

//  Define values for option vector

const
  Opt_Share_mask = $00000018; // 2 bits: Sharing control
  {$EXTERNALSYM Opt_Share_mask}
  Opt_Distinct   = $00000008; // Distinct reservations
  {$EXTERNALSYM Opt_Distinct}
  Opt_Shared     = $00000010; // Shared reservations
  {$EXTERNALSYM Opt_Shared}

  Opt_SndSel_mask = $00000007; // 3 bits: Sender selection
  {$EXTERNALSYM Opt_SndSel_mask}
  Opt_Wildcard    = $00000001; // Wildcard scope
  {$EXTERNALSYM Opt_Wildcard}
  Opt_Explicit    = $00000002; // Explicit scope
  {$EXTERNALSYM Opt_Explicit}

function Style_is_Wildcard(p: DWORD): Boolean;
{$EXTERNALSYM Style_is_Wildcard}
function Style_is_Shared(p: DWORD): Boolean;
{$EXTERNALSYM Style_is_Shared}

//  Define style values

const
  STYLE_WF = Opt_Shared + Opt_Wildcard;
  {$EXTERNALSYM STYLE_WF}
  STYLE_FF = Opt_Distinct + Opt_Explicit;
  {$EXTERNALSYM STYLE_FF}
  STYLE_SE = Opt_Shared + Opt_Explicit;
  {$EXTERNALSYM STYLE_SE}

  ctype_STYLE = 1;
  {$EXTERNALSYM ctype_STYLE}

type
  RESV_STYLE = record
    style_header: RsvpObjHdr;
    style_word: ULONG;
  end;
  {$EXTERNALSYM RESV_STYLE}
  TResvStyle = RESV_STYLE;
  PResvStyle = ^RESV_STYLE;

(*
 *  RSVP FILTER SPEC object
 *)

const
  ctype_FILTER_SPEC_ipv4    = 1; // IPv4 FILTER_SPEC
  {$EXTERNALSYM ctype_FILTER_SPEC_ipv4}
  ctype_FILTER_SPEC_ipv4GPI = 4; // IPv4/GPI FILTER_SPEC
  {$EXTERNALSYM ctype_FILTER_SPEC_ipv4GPI}

type
  Filter_Spec_IPv4 = record
    filt_ipaddr: IN_ADDR;    // IPv4 SrcAddress
    filt_unused: USHORT;
    filt_port: USHORT;       // SrcPort
  end;
  {$EXTERNALSYM Filter_Spec_IPv4}
  TFilterSpecIPv4 = Filter_Spec_IPv4;
  PFilterSpecIPv4 = ^Filter_Spec_IPv4;

  Filter_Spec_IPv4GPI = record
    filt_ipaddr: IN_ADDR;    // IPv4 SrcAddress
    filt_gpi: ULONG;         // Generalized Port Id
  end;
  {$EXTERNALSYM Filter_Spec_IPv4GPI}
  TFilterSpecIPv4GPI = Filter_Spec_IPv4GPI;
  PFilterSpecIPv4GPI = ^Filter_Spec_IPv4GPI;

  FILTER_SPEC = record
    filt_header: RsvpObjHdr;
    case Integer of
      0: (filt_ipv4: Filter_Spec_IPv4);
      1: (filt_ipv4gpi: Filter_Spec_IPv4GPI);
  end;
  {$EXTERNALSYM FILTER_SPEC}
  TFilterSpec = FILTER_SPEC;
  PFilterSpec = ^FILTER_SPEC;  

//#define FilterSrcaddr   filt_u.filt_ipv4.filt_ipaddr
//#define FilterSrcport   filt_u.filt_ipv4.filt_port

(*
 *  RSVP SENDER_TEMPLATE object
 *)

const
  ctype_SENDER_TEMPLATE_ipv4    = 1; // IPv4 SENDER_TEMPLATE
  {$EXTERNALSYM ctype_SENDER_TEMPLATE_ipv4}
  ctype_SENDER_TEMPLATE_ipv4GPI = 4; // IPv4/GPI SENDER_TEMPLATE
  {$EXTERNALSYM ctype_SENDER_TEMPLATE_ipv4GPI}

type
  SENDER_TEMPLATE = FILTER_SPEC;       // Identical to FILTER_SPEC
  {$EXTERNALSYM SENDER_TEMPLATE}
  TSenderTemplate = SENDER_TEMPLATE;
  PSenderTemplate = ^SENDER_TEMPLATE;

(*
 *  RSVP SCOPE object class
 *)

const
  ctype_SCOPE_list_ipv4 = 1;
  {$EXTERNALSYM ctype_SCOPE_list_ipv4}

type
  Scope_list_ipv4 = record
    scopl_ipaddr: array [0..0] of IN_ADDR;        // var-len list of IP sender addrs
  end;
  {$EXTERNALSYM Scope_list_ipv4}
  TScopeListIPv4 = Scope_list_ipv4;
  PScopeListIPv4 = ^Scope_list_ipv4;

  RSVP_SCOPE = record
    scopl_header: RsvpObjHdr;
    case Integer of
      0: (scopl_ipv4: Scope_list_ipv4);
  end;
  {$EXTERNALSYM RSVP_SCOPE}
  TRsvpScope = RSVP_SCOPE;
  PRsvpScope = ^RSVP_SCOPE;

//#define Scope4Addr      scope_u.scopl_ipv4.scopl_ipaddr
//#define ScopeCnt(scp)   ((ObjLength(scp)-sizeof(RsvpObjHdr))/sizeof(struct in_addr))
//#define ScopeLen(cnt)   (cnt*sizeof(struct in_addr)+sizeof(RsvpObjHdr))

(*
 *  ERROR_SPEC object class
 *)

const
  ctype_ERROR_SPEC_ipv4 = 1;
  {$EXTERNALSYM ctype_ERROR_SPEC_ipv4}

  ERROR_SPECF_InPlace = $01;    (*   Left resv in place     *)
  {$EXTERNALSYM ERROR_SPECF_InPlace}
  ERROR_SPECF_NotGuilty = $02;    (*   This rcvr not guilty   *)
  {$EXTERNALSYM ERROR_SPECF_NotGuilty}
  ERR_FORWARD_OK  = $8000;      (* Flag: OK to forward state *)
  {$EXTERNALSYM ERR_FORWARD_OK}

function Error_Usage(x: DWORD): DWORD;
{$EXTERNALSYM Error_Usage}

const
  ERR_Usage_globl = $00;        (* Globally-defined sub-code *)
  {$EXTERNALSYM ERR_Usage_globl}
  ERR_Usage_local = $10;        (* Locally-defined sub-code *)
  {$EXTERNALSYM ERR_Usage_local}
  ERR_Usage_serv  = $11;        (* Service-defined sub-code *)
  {$EXTERNALSYM ERR_Usage_serv}
  ERR_global_mask = $0fff;      (* Sub-code bits in Error Val *)
  {$EXTERNALSYM ERR_global_mask}

type
  Error_Spec_IPv4 = record
    errs_errnode: in_addr;   (* Error Node Address       *)
    errs_flags: u_char;      (* Flags:           *)
    errs_code: UCHAR;        (* Error Code (def'd below) *)
    errs_value: USHORT;      (* Error Value      *)
  end;
  {$EXTERNALSYM Error_Spec_IPv4}
  TErrorSpecIPv4 = Error_Spec_IPv4;
  PErrorSpecIPv4 = ^Error_Spec_IPv4;

type
  ERROR_SPEC = record
    errs_header: RsvpObjHdr;
    case Integer of
      0: (errs_ipv4: Error_Spec_IPv4);
  end;
  {$EXTERNALSYM ERROR_SPEC}
  TErrorSpec = ERROR_SPEC;
  PErrorSpec = ^ERROR_SPEC;

//#define errspec4_enode  errs_u.errs_ipv4.errs_errnode
//#define errspec4_code   errs_u.errs_ipv4.errs_code
//#define errspec4_value  errs_u.errs_ipv4.errs_value
//#define errspec4_flags  errs_u.errs_ipv4.errs_flags

(*
 *  POLICY_DATA object class
 *
 *      Contents are Opaque RSVP/SBM
 *)

const
  ctype_POLICY_DATA = 1;
  {$EXTERNALSYM ctype_POLICY_DATA}

type
  POLICY_DATA = record
    PolicyObjHdr: RsvpObjHdr;
    usPeOffset: USHORT;     // Offset to the start of Policy Elements from the begining of Policy Data
    usReserved: USHORT;
  end;
  {$EXTERNALSYM POLICY_DATA}
  TPolicyData = POLICY_DATA;
  PPolicyData = ^POLICY_DATA;

const
  PD_HDR_LEN  = SizeOf(POLICY_DATA);
  {$EXTERNALSYM PD_HDR_LEN}

type
  POLICY_ELEMENT = record
    usPeLength: USHORT;     // Policy Element length
    usPeType: USHORT;       // Policy Element type
    ucPeData: array [0..3] of UCHAR;    // Just a place holder to the start of Policy Element data
  end;
  {$EXTERNALSYM POLICY_ELEMENT}
  TPolicyElement = POLICY_ELEMENT;
  PPolicyElement = ^POLICY_ELEMENT;

const
  PE_HDR_LEN = 2 * SizeOf(USHORT);
  {$EXTERNALSYM PE_HDR_LEN}

(**************************************************************************
 *
 *  Int-Serv Data Structures
 *
 **************************************************************************)

(*
 *  Service numbers
 *)

const
  GENERAL_INFO          = 1;
  {$EXTERNALSYM GENERAL_INFO}
  GUARANTEED_SERV       = 2;
  {$EXTERNALSYM GUARANTEED_SERV}
  PREDICTIVE_SERV       = 3;
  {$EXTERNALSYM PREDICTIVE_SERV}
  CONTROLLED_DELAY_SERV = 4;
  {$EXTERNALSYM CONTROLLED_DELAY_SERV}
  CONTROLLED_LOAD_SERV  = 5;
  {$EXTERNALSYM CONTROLLED_LOAD_SERV}
  QUALITATIVE_SERV      = 6;
  {$EXTERNALSYM QUALITATIVE_SERV}

(*
 *  Well-known parameter IDs
 *)

const
  IS_WKP_HOP_CNT =        4;
  {$EXTERNALSYM IS_WKP_HOP_CNT}
  IS_WKP_PATH_BW =        6;
  {$EXTERNALSYM IS_WKP_PATH_BW}
  IS_WKP_MIN_LATENCY =    8;
  {$EXTERNALSYM IS_WKP_MIN_LATENCY}
  IS_WKP_COMPOSED_MTU =   10;
  {$EXTERNALSYM IS_WKP_COMPOSED_MTU}
  IS_WKP_TB_TSPEC =       127; (* Token-bucket TSPEC parm *)
  {$EXTERNALSYM IS_WKP_TB_TSPEC}
  IS_WKP_Q_TSPEC =        128;
  {$EXTERNALSYM IS_WKP_Q_TSPEC}

type
  int_serv_wkp = DWORD;
  {$EXTERNALSYM int_serv_wkp}
  TIntServWkp = int_serv_wkp;

(*
 *  Int-serv Main header
 *)

  IntServMainHdr = record
    ismh_version: UCHAR;    // Version
    ismh_unused: UCHAR;
    ismh_len32b: USHORT;    // # 32-bit words excluding this hdr
  end;
  {$EXTERNALSYM IntServMainHdr}
  TIntServMainHdr = IntServMainHdr;
  PIntServMainHdr = ^IntServMainHdr;

const
  INTSERV_VERS_MASK   = $f0;
  {$EXTERNALSYM INTSERV_VERS_MASK}
  INTSERV_VERSION0    = 0;
  {$EXTERNALSYM INTSERV_VERSION0}

function Intserv_Version(x: DWORD): DWORD;
{$EXTERNALSYM Intserv_Version}
function Intserv_Version_OK(const x: TIntServMainHdr): Boolean;
{$EXTERNALSYM Intserv_Version_OK}

// Convert ishm_length to equivalent RSVP object size, for checking

function Intserv_Obj_size(const x: TIntServMainHdr): DWORD;
{$EXTERNALSYM Intserv_Obj_size}

(*
 *  Int-serv Service Element Header
 *)

// Flag: Break bit

const
  ISSH_BREAK_BIT = $80;
  {$EXTERNALSYM ISSH_BREAK_BIT}

type
  IntServServiceHdr = record
    issh_service: UCHAR;   // Service number
    issh_flags: UCHAR;     // Flag byte
    issh_len32b: USHORT;    // #32-bit words excluding this hdr
  end;
  {$EXTERNALSYM IntServServiceHdr}
  TIntServServiceHdr = IntServServiceHdr;
  PIntServServiceHdr = ^IntServServiceHdr;

function Issh_len32b(const p: TIntServServiceHdr): USHORT;
{$EXTERNALSYM Issh_len32b}

(*
 *  Int-serv Parameter Element Header
 *)

const
  ISPH_FLG_INV = $80; // Flag: Invalid
  {$EXTERNALSYM ISPH_FLG_INV}

type
  IntServParmHdr = record
    isph_parm_num: UCHAR;  // Parameter number
    isph_flags: UCHAR;     // Flags
    isph_len32b: USHORT;    // #32-bit words excluding this hdr
  end;
  {$EXTERNALSYM IntServParmHdr}
  TIntServParmHdr = IntServParmHdr;
  PIntServParmHdr = ^IntServParmHdr;

{
function Next_Main_Hdr(const p: TIntServMainHdr): PIntServMainHdr;
begin
   TODO (IntServMainHdr *)((ULONG *)(p)+1+(p)->ismh_len32b)
end;

function Next_Serv_Hdr(const p: TIntServMainHdr): ULONG;
begin
   TODO (IntServServiceHdr *)((ULONG *)(p)+1+(p)->issh_len32b)
end;

function Next_Parm_Hdr(const p: TIntServParmHdr): ULONG;
begin
   TODO (IntServParmHdr *)((ULONG *)(p)+1+(p)->isph_len32b)
end;
}

(*
 *  Generic Tspec Parameters
 *)

type
  GenTspecParms = record
    TB_Tspec_r: FLOAT;     // Token bucket rate (B/sec)
    TB_Tspec_b: FLOAT;     // Token bucket depth (B)
    TB_Tspec_p: FLOAT;     // Peak data rate (B/sec)
    TB_Tspec_m: ULONG;     // Min Policed Unit (B)
    TB_Tspec_M_: ULONG;     // Max pkt size (B)
  end;
  {$EXTERNALSYM GenTspecParms}
  TGenTspecParms = GenTspecParms;
  PGenTspecParms = ^GenTspecParms;

(*
 *  Generic Tspec
 *)

  GenTspec = record
    gen_Tspec_serv_hdr: IntServServiceHdr; // (GENERAL_INFO, length)
    gen_Tspec_parm_hdr: IntServParmHdr; // (IS_WKP_TB_TSPEC)
    gen_Tspec_parms: GenTspecParms;
  end;
  {$EXTERNALSYM GenTspec}
  TGenTspec = GenTspec;
  PGenTspec = ^GenTspec;

//#define gtspec_r        gen_Tspec_parms.TB_Tspec_r
//#define gtspec_b        gen_Tspec_parms.TB_Tspec_b
//#define gtspec_m        gen_Tspec_parms.TB_Tspec_m
//#define gtspec_M        gen_Tspec_parms.TB_Tspec_M
//#define gtspec_p        gen_Tspec_parms.TB_Tspec_p
//#define gtspec_parmno   gen_Tspec_parm_hdr.isph_parm_num
//#define gtspec_flags    gen_Tspec_parm_hdr.isph_flags

//#define gtspec_len      (sizeof(GenTspec) - sizeof(IntServServiceHdr))

(* contents of qualitative tspec *)

type
  QualTspecParms = record
    TB_Tspec_M: ULONG;     // Max pkt size (M)
  end;
  {$EXTERNALSYM QualTspecParms}
  TQualTspecParms = QualTspecParms;
  PQualTspecParms = ^QualTspecParms;

  QualTspec = record
    qual_Tspec_serv_hdr: IntServServiceHdr; // (QUALITATIVE_SERV, length)
    qual_Tspec_parm_hdr: IntServParmHdr; // (IS_WKP_Q_TSPEC)
    qual_Tspec_parms: QualTspecParms;
  end;
  {$EXTERNALSYM QualTspec}
  TQualTspec = QualTspec;
  PQualTspec = ^QualTspec;

  QualAppFlowSpec = record
    Q_spec_serv_hdr: IntServServiceHdr;    // (QUALITATIVE_SERV,0,len)
    Q_spec_parm_hdr: IntServParmHdr;    // (IS_WKP_Q_TSPEC)
    Q_spec_parms: QualTspecParms;       // QUALITATIVE Tspec parameters
  end;
  {$EXTERNALSYM QualAppFlowSpec}
  TQualAppFlowSpec = QualAppFlowSpec;
  PQualAppFlowSpec = ^QualAppFlowSpec;

//#define QAspec_M        Q_spec_parms.TB_Tspec_M

(*
 *  Contents of int-serv Tspec
 *)

  IntServTspecBody = record
    st_mh: IntServMainHdr;
    case Integer of
      0: (gen_stspec: GenTspec); // Generic Tspec
      1: (qual_stspec: QualTspec);
  end;
  {$EXTERNALSYM IntServTspecBody}
  TIntServTspecBody = IntServTspecBody;
  PIntServTspecBody = ^IntServTspecBody;

(*
 *  SENDER_TSPEC class object
 *)

const
  ctype_SENDER_TSPEC = 2;
  {$EXTERNALSYM ctype_SENDER_TSPEC}

type
  SENDER_TSPEC = record
    stspec_header: RsvpObjHdr;
    stspec_body: IntServTspecBody;
  end;
  {$EXTERNALSYM SENDER_TSPEC}
  TSenderTSpec = SENDER_TSPEC;
  PSenderTSpec = ^SENDER_TSPEC;

(*
 *  Controlled-Load Flowspec
 *)

  CtrlLoadFlowspec = record
    CL_spec_serv_hdr: IntServServiceHdr;    // (CONTROLLED_LOAD_SERV,0,len)
    CL_spec_parm_hdr: IntServParmHdr;    // (IS_WKP_TB_TSPEC)
    CL_spec_parms: GenTspecParms;       // GENERIC Tspec parameters
  end;
  {$EXTERNALSYM CtrlLoadFlowspec}
  TCtrlLoadFlowspec = CtrlLoadFlowspec;
  PCtrlLoadFlowspec = ^CtrlLoadFlowspec;

//#define CLspec_r        CL_spec_parms.TB_Tspec_r
//#define CLspec_b        CL_spec_parms.TB_Tspec_b
//#define CLspec_p        CL_spec_parms.TB_Tspec_p
//#define CLspec_m        CL_spec_parms.TB_Tspec_m
//#define CLspec_M        CL_spec_parms.TB_Tspec_M
//#define CLspec_parmno   CL_spec_parm_hdr.isph_parm_num
//#define CLspec_flags    CL_spec_parm_hdr.isph_flags
//#define CLspec_len32b   CL_spec_parm_hdr.isph_len32b

//#define CLspec_len      (sizeof(CtrlLoadFlowspec) - sizeof(IntServServiceHdr))

(*  Service-specific Parameter IDs
 *)

const
  IS_GUAR_RSPEC     = 130;
  {$EXTERNALSYM IS_GUAR_RSPEC}

  GUAR_ADSPARM_C    = 131;
  {$EXTERNALSYM GUAR_ADSPARM_C}
  GUAR_ADSPARM_D    = 132;
  {$EXTERNALSYM GUAR_ADSPARM_D}
  GUAR_ADSPARM_Ctot = 133;
  {$EXTERNALSYM GUAR_ADSPARM_Ctot}
  GUAR_ADSPARM_Dtot = 134;
  {$EXTERNALSYM GUAR_ADSPARM_Dtot}
  GUAR_ADSPARM_Csum = 135;
  {$EXTERNALSYM GUAR_ADSPARM_Csum}
  GUAR_ADSPARM_Dsum = 136;
  {$EXTERNALSYM GUAR_ADSPARM_Dsum}

(*
 *  Guaranteed Rspec parameters
 *)

type
  GuarRspec = record
    Guar_R: FLOAT;         //  Guaranteed Rate B/s
    Guar_S: ULONG;         //  Slack term secs
  end;
  {$EXTERNALSYM GuarRspec}
  TGuarRspec = GuarRspec;
  PGuarRspec = ^GuarRspec;

(*
 *  Guaranteed Flowspec
 *)

  GuarFlowSpec = record
    Guar_serv_hdr: IntServServiceHdr;      // (GUARANTEED, 0, length)
    Guar_Tspec_hdr: IntServParmHdr;     // (IS_WKP_TB_TSPEC,)
    Guar_Tspec_parms: GenTspecParms;   // GENERIC Tspec parms
    Guar_Rspec_hdr: IntServParmHdr;     // (IS_GUAR_RSPEC)
    Guar_Rspec: GuarRspec;         // Guaranteed rate (B/sec)
  end;
  {$EXTERNALSYM GuarFlowSpec}
  TGuarFlowSpec = GuarFlowSpec;
  PGuarFlowSpec = ^GuarFlowSpec;

//#define Gspec_r         Guar_Tspec_parms.TB_Tspec_r
//#define Gspec_b         Guar_Tspec_parms.TB_Tspec_b
//#define Gspec_p         Guar_Tspec_parms.TB_Tspec_p
//#define Gspec_m         Guar_Tspec_parms.TB_Tspec_m
//#define Gspec_M         Guar_Tspec_parms.TB_Tspec_M
//#define Gspec_R         Guar_Rspec.Guar_R
//#define Gspec_S         Guar_Rspec.Guar_S
//#define Gspec_T_parmno  Guar_Tspec_hdr.isph_parm_num
//#define Gspec_T_flags   Guar_Tspec_hdr.isph_flags
//#define Gspec_R_parmno  Guar_Rspec_hdr.isph_parm_num
//#define Gspec_R_flags   Guar_Rspec_hdr.isph_flags

//#define Gspec_len       (sizeof(GuarFlowSpec) - sizeof(IntServServiceHdr))

(*
 *  Contents of int-serv flowspec
 *)

type
  IntServFlowSpec = record
    spec_mh: IntServMainHdr;
    case Integer of
        0: (CL_spec: CtrlLoadFlowspec);   // Controlled-Load service
        1: (G_spec: GuarFlowSpec);    // Guaranteed service
        2: (Q_spec: QualAppFlowSpec);
  end;
  {$EXTERNALSYM IntServFlowSpec}
  TIntServFlowSpec = IntServFlowSpec;
  PIntServFlowSpec = ^IntServFlowSpec;

//#define ISmh_len32b     spec_mh.ismh_len32b
//#define ISmh_version    spec_mh.ismh_version
//#define ISmh_unused     spec_mh.ismh_unused

(*
 *  Int-Serv FLOWSPEC object
 *)

const
  ctype_FLOWSPEC_Intserv0 = 2; // The int-serv flowspec (v.0)
  {$EXTERNALSYM ctype_FLOWSPEC_Intserv0}

type
  IS_FLOWSPEC = record
    flow_header: RsvpObjHdr;
    flow_body: IntServFlowSpec;
  end;
  {$EXTERNALSYM IS_FLOWSPEC}
  TIsFlowSpec = IS_FLOWSPEC;
  PIsFlowSpec = ^IS_FLOWSPEC;

(*
 *  FLOW DESCRIPTOR
 *)

  FLOW_DESC = record
    u1: record
    case Integer of
      0: (stspec: ^SENDER_TSPEC);
      1: (isflow: ^IS_FLOWSPEC);
    end;
    u2: record
    case Integer of
      0: (stemp: ^SENDER_TEMPLATE);
      1: (fspec: ^FILTER_SPEC);
    end;
  end;
  {$EXTERNALSYM FLOW_DESC}
  TFlowDesc = FLOW_DESC;
  PFlowDesc = ^FLOW_DESC;

//#define FdSenderTspec       u1.stspec
//#define FdIsFlowSpec        u1.isflow

//#define FdSenderTemplate    u2.stemp
//#define FdFilterSpec        u2.fspec

(*
 *  ADSPEC class object
 *
 *      Opaque to RSVP -- Contents defined in rapi_lib.h
 *)

const
  ctype_ADSPEC_INTSERV = 2;
  {$EXTERNALSYM ctype_ADSPEC_INTSERV}

(*
 *  Guaranteed service Adspec parameters -- fixed part
 *)

type
  Gads_parms_t = record
    Gads_serv_hdr: IntServServiceHdr;  // GUARANTEED, x, len
    Gads_Ctot_hdr: IntServParmHdr;  // GUAR_ADSPARM_Ctot
    Gads_Ctot: ULONG;
    Gads_Dtot_hdr: IntServParmHdr;  // (GUAR_ADSPARM_Dtot
    Gads_Dtot: ULONG;
    Gads_Csum_hdr: IntServParmHdr;  // GUAR_ADSPARM_Csum
    Gads_Csum: ULONG;
    Gads_Dsum_hdr: IntServParmHdr;  // GUAR_ADSPARM_Dsum
    Gads_Dsum: ULONG;
    (*
     *  May be followed by override general param values
     *)
  end;
  {$EXTERNALSYM Gads_parms_t}
  TGadsParmsT = Gads_parms_t;
  PGadsParmsT = ^Gads_parms_t;

(*
 *  General Path Characterization Parameters
 *)
 
  GenAdspecParams = record
    gen_parm_hdr: IntServServiceHdr;           // GENERAL_INFO, len
    gen_parm_hopcnt_hdr: IntServParmHdr;    // (IS_WKP_HOP_CNT
    gen_parm_hopcnt: ULONG;
    gen_parm_pathbw_hdr: IntServParmHdr;    // IS_WKP_PATH_BW
    gen_parm_path_bw: FLOAT;
    gen_parm_minlat_hdr: IntServParmHdr;    // IS_WKP_MIN_LATENCY
    gen_parm_min_latency: ULONG;
    gen_parm_compmtu_hdr: IntServParmHdr;   // IS_WKP_COMPOSED_MTU
    gen_parm_composed_MTU: ULONG;
  end;
  {$EXTERNALSYM GenAdspecParams}
  TGenAdspecParams = GenAdspecParams;
  PGenAdspecParams = ^GenAdspecParams;

(*
 *  Contents of (minimal) int-serv Adspec
 *)

  IS_ADSPEC_BODY = record
    adspec_mh: IntServMainHdr;      // Main header
    adspec_genparms: GenAdspecParams;// General char parm fragment
    (*
     *  Followed by variable-length fragments for some or all
     *  services.  These can be minimal length fragments.
     *)
  end;
  {$EXTERNALSYM IS_ADSPEC_BODY}
  TIsAdSpecBody = IS_ADSPEC_BODY;
  PIsAdSpecBody = ^IS_ADSPEC_BODY;  

//const TODO Unknown Object_Header
//  GEN_ADSPEC_LEN = SizeOf(Object_header) + SizeOf(IS_adsbody_t);
//  {$EXTERNALSYM GEN_ADSPEC_LEN}

type
  ADSPEC = record
    adspec_header: RsvpObjHdr;
    adspec_body: IS_ADSPEC_BODY;    (* Defined in rapi_lib.h *)
  end;
  {$EXTERNALSYM ADSPEC}
  TAdSpec = ADSPEC;
  PAdSpec = ^ADSPEC;

// RSVP message types

const
  RSVP_PATH      = 1;
  {$EXTERNALSYM RSVP_PATH}
  RSVP_RESV      = 2;
  {$EXTERNALSYM RSVP_RESV}
  RSVP_PATH_ERR  = 3;
  {$EXTERNALSYM RSVP_PATH_ERR}
  RSVP_RESV_ERR  = 4;
  {$EXTERNALSYM RSVP_RESV_ERR}
  RSVP_PATH_TEAR = 5;
  {$EXTERNALSYM RSVP_PATH_TEAR}
  RSVP_RESV_TEAR = 6;
  {$EXTERNALSYM RSVP_RESV_TEAR}

(*  RSVP error codes
 *)

  RSVP_Err_NONE  = 0;   (* No error (CONFIRM)       *)
  {$EXTERNALSYM RSVP_Err_NONE}
  RSVP_Erv_Nonev = 0;   (*    No-error Error Value  *)
  {$EXTERNALSYM RSVP_Erv_Nonev}

(* Admission Control failure    *)

  RSVP_Err_ADMISSION = 1;
  {$EXTERNALSYM RSVP_Err_ADMISSION}

(* Globally-defined sub-codes for : Admission Control failure *)

  RSVP_Erv_Other     = 0;   (* Unspecified cause        *)
  {$EXTERNALSYM RSVP_Erv_Other}
  RSVP_Erv_DelayBnd  = 1;   (* Cannot meet delay bound req  *)
  {$EXTERNALSYM RSVP_Erv_DelayBnd}
  RSVP_Erv_Bandwidth = 2;   (* Insufficient bandwidth   *)
  {$EXTERNALSYM RSVP_Erv_Bandwidth}
  RSVP_Erv_MTU       = 3;   (* MTU in flowspec too large    *)
  {$EXTERNALSYM RSVP_Erv_MTU}

// Microsoft specific error values

  RSVP_Erv_Flow_Rate         = $8001;
  {$EXTERNALSYM RSVP_Erv_Flow_Rate}
  RSVP_Erv_Bucket_szie       = $8002;
  {$EXTERNALSYM RSVP_Erv_Bucket_szie}
  RSVP_Erv_Peak_Rate         = $8003;
  {$EXTERNALSYM RSVP_Erv_Peak_Rate}
  RSVP_Erv_Min_Policied_size = $8004;
  {$EXTERNALSYM RSVP_Erv_Min_Policied_size}

(* Policy control failure   *)

  RSVP_Err_POLICY = 2;
  {$EXTERNALSYM RSVP_Err_POLICY}

// Policy error values from Identity draft

  POLICY_ERRV_NO_MORE_INFO                = 1;
  {$EXTERNALSYM POLICY_ERRV_NO_MORE_INFO}
  POLICY_ERRV_UNSUPPORTED_CREDENTIAL_TYPE = 2;
  {$EXTERNALSYM POLICY_ERRV_UNSUPPORTED_CREDENTIAL_TYPE}
  POLICY_ERRV_INSUFFICIENT_PRIVILEGES     = 3;
  {$EXTERNALSYM POLICY_ERRV_INSUFFICIENT_PRIVILEGES}
  POLICY_ERRV_EXPIRED_CREDENTIALS         = 4;
  {$EXTERNALSYM POLICY_ERRV_EXPIRED_CREDENTIALS}
  POLICY_ERRV_IDENTITY_CHANGED            = 5;
  {$EXTERNALSYM POLICY_ERRV_IDENTITY_CHANGED}

// Microsoft specific policy error values

  POLICY_ERRV_UNKNOWN = 0;
  {$EXTERNALSYM POLICY_ERRV_UNKNOWN}

  POLICY_ERRV_GLOBAL_DEF_FLOW_COUNT         = 1;
  {$EXTERNALSYM POLICY_ERRV_GLOBAL_DEF_FLOW_COUNT}
  POLICY_ERRV_GLOBAL_GRP_FLOW_COUNT         = 2;
  {$EXTERNALSYM POLICY_ERRV_GLOBAL_GRP_FLOW_COUNT}
  POLICY_ERRV_GLOBAL_USER_FLOW_COUNT        = 3;
  {$EXTERNALSYM POLICY_ERRV_GLOBAL_USER_FLOW_COUNT}
  POLICY_ERRV_GLOBAL_UNAUTH_USER_FLOW_COUNT = 4;
  {$EXTERNALSYM POLICY_ERRV_GLOBAL_UNAUTH_USER_FLOW_COUNT}
  POLICY_ERRV_SUBNET_DEF_FLOW_COUNT         = 5;
  {$EXTERNALSYM POLICY_ERRV_SUBNET_DEF_FLOW_COUNT}
  POLICY_ERRV_SUBNET_GRP_FLOW_COUNT         = 6;
  {$EXTERNALSYM POLICY_ERRV_SUBNET_GRP_FLOW_COUNT}
  POLICY_ERRV_SUBNET_USER_FLOW_COUNT        = 7;
  {$EXTERNALSYM POLICY_ERRV_SUBNET_USER_FLOW_COUNT}
  POLICY_ERRV_SUBNET_UNAUTH_USER_FLOW_COUNT = 8;
  {$EXTERNALSYM POLICY_ERRV_SUBNET_UNAUTH_USER_FLOW_COUNT}

  POLICY_ERRV_GLOBAL_DEF_FLOW_DURATION         = 9;
  {$EXTERNALSYM POLICY_ERRV_GLOBAL_DEF_FLOW_DURATION}
  POLICY_ERRV_GLOBAL_GRP_FLOW_DURATION         = 10;
  {$EXTERNALSYM POLICY_ERRV_GLOBAL_GRP_FLOW_DURATION}
  POLICY_ERRV_GLOBAL_USER_FLOW_DURATION        = 11;
  {$EXTERNALSYM POLICY_ERRV_GLOBAL_USER_FLOW_DURATION}
  POLICY_ERRV_GLOBAL_UNAUTH_USER_FLOW_DURATION = 12;
  {$EXTERNALSYM POLICY_ERRV_GLOBAL_UNAUTH_USER_FLOW_DURATION}
  POLICY_ERRV_SUBNET_DEF_FLOW_DURATION         = 13;
  {$EXTERNALSYM POLICY_ERRV_SUBNET_DEF_FLOW_DURATION}
  POLICY_ERRV_SUBNET_GRP_FLOW_DURATION         = 14;
  {$EXTERNALSYM POLICY_ERRV_SUBNET_GRP_FLOW_DURATION}
  POLICY_ERRV_SUBNET_USER_FLOW_DURATION        = 15;
  {$EXTERNALSYM POLICY_ERRV_SUBNET_USER_FLOW_DURATION}
  POLICY_ERRV_SUBNET_UNAUTH_USER_FLOW_DURATION = 16;
  {$EXTERNALSYM POLICY_ERRV_SUBNET_UNAUTH_USER_FLOW_DURATION}

  POLICY_ERRV_GLOBAL_DEF_FLOW_RATE         = 17;
  {$EXTERNALSYM POLICY_ERRV_GLOBAL_DEF_FLOW_RATE}
  POLICY_ERRV_GLOBAL_GRP_FLOW_RATE         = 18;
  {$EXTERNALSYM POLICY_ERRV_GLOBAL_GRP_FLOW_RATE}
  POLICY_ERRV_GLOBAL_USER_FLOW_RATE        = 19;
  {$EXTERNALSYM POLICY_ERRV_GLOBAL_USER_FLOW_RATE}
  POLICY_ERRV_GLOBAL_UNAUTH_USER_FLOW_RATE = 20;
  {$EXTERNALSYM POLICY_ERRV_GLOBAL_UNAUTH_USER_FLOW_RATE}
  POLICY_ERRV_SUBNET_DEF_FLOW_RATE         = 21;
  {$EXTERNALSYM POLICY_ERRV_SUBNET_DEF_FLOW_RATE}
  POLICY_ERRV_SUBNET_GRP_FLOW_RATE         = 22;
  {$EXTERNALSYM POLICY_ERRV_SUBNET_GRP_FLOW_RATE}
  POLICY_ERRV_SUBNET_USER_FLOW_RATE        = 23;
  {$EXTERNALSYM POLICY_ERRV_SUBNET_USER_FLOW_RATE}
  POLICY_ERRV_SUBNET_UNAUTH_USER_FLOW_RATE = 24;
  {$EXTERNALSYM POLICY_ERRV_SUBNET_UNAUTH_USER_FLOW_RATE}

  POLICY_ERRV_GLOBAL_DEF_PEAK_RATE         = 25;
  {$EXTERNALSYM POLICY_ERRV_GLOBAL_DEF_PEAK_RATE}
  POLICY_ERRV_GLOBAL_GRP_PEAK_RATE         = 26;
  {$EXTERNALSYM POLICY_ERRV_GLOBAL_GRP_PEAK_RATE}
  POLICY_ERRV_GLOBAL_USER_PEAK_RATE        = 27;
  {$EXTERNALSYM POLICY_ERRV_GLOBAL_USER_PEAK_RATE}
  POLICY_ERRV_GLOBAL_UNAUTH_USER_PEAK_RATE = 28;
  {$EXTERNALSYM POLICY_ERRV_GLOBAL_UNAUTH_USER_PEAK_RATE}
  POLICY_ERRV_SUBNET_DEF_PEAK_RATE         = 29;
  {$EXTERNALSYM POLICY_ERRV_SUBNET_DEF_PEAK_RATE}
  POLICY_ERRV_SUBNET_GRP_PEAK_RATE         = 30;
  {$EXTERNALSYM POLICY_ERRV_SUBNET_GRP_PEAK_RATE}
  POLICY_ERRV_SUBNET_USER_PEAK_RATE        = 31;
  {$EXTERNALSYM POLICY_ERRV_SUBNET_USER_PEAK_RATE}
  POLICY_ERRV_SUBNET_UNAUTH_USER_PEAK_RATE = 32;
  {$EXTERNALSYM POLICY_ERRV_SUBNET_UNAUTH_USER_PEAK_RATE}

  POLICY_ERRV_GLOBAL_DEF_SUM_FLOW_RATE         = 33;
  {$EXTERNALSYM POLICY_ERRV_GLOBAL_DEF_SUM_FLOW_RATE}
  POLICY_ERRV_GLOBAL_GRP_SUM_FLOW_RATE         = 34;
  {$EXTERNALSYM POLICY_ERRV_GLOBAL_GRP_SUM_FLOW_RATE}
  POLICY_ERRV_GLOBAL_USER_SUM_FLOW_RATE        = 35;
  {$EXTERNALSYM POLICY_ERRV_GLOBAL_USER_SUM_FLOW_RATE}
  POLICY_ERRV_GLOBAL_UNAUTH_USER_SUM_FLOW_RATE = 36;
  {$EXTERNALSYM POLICY_ERRV_GLOBAL_UNAUTH_USER_SUM_FLOW_RATE}
  POLICY_ERRV_SUBNET_DEF_SUM_FLOW_RATE         = 37;
  {$EXTERNALSYM POLICY_ERRV_SUBNET_DEF_SUM_FLOW_RATE}
  POLICY_ERRV_SUBNET_GRP_SUM_FLOW_RATE         = 38;
  {$EXTERNALSYM POLICY_ERRV_SUBNET_GRP_SUM_FLOW_RATE}
  POLICY_ERRV_SUBNET_USER_SUM_FLOW_RATE        = 39;
  {$EXTERNALSYM POLICY_ERRV_SUBNET_USER_SUM_FLOW_RATE}
  POLICY_ERRV_SUBNET_UNAUTH_USER_SUM_FLOW_RATE = 40;
  {$EXTERNALSYM POLICY_ERRV_SUBNET_UNAUTH_USER_SUM_FLOW_RATE}

  POLICY_ERRV_GLOBAL_DEF_SUM_PEAK_RATE         = 41;
  {$EXTERNALSYM POLICY_ERRV_GLOBAL_DEF_SUM_PEAK_RATE}
  POLICY_ERRV_GLOBAL_GRP_SUM_PEAK_RATE         = 42;
  {$EXTERNALSYM POLICY_ERRV_GLOBAL_GRP_SUM_PEAK_RATE}
  POLICY_ERRV_GLOBAL_USER_SUM_PEAK_RATE        = 43;
  {$EXTERNALSYM POLICY_ERRV_GLOBAL_USER_SUM_PEAK_RATE}
  POLICY_ERRV_GLOBAL_UNAUTH_USER_SUM_PEAK_RATE = 44;
  {$EXTERNALSYM POLICY_ERRV_GLOBAL_UNAUTH_USER_SUM_PEAK_RATE}
  POLICY_ERRV_SUBNET_DEF_SUM_PEAK_RATE         = 45;
  {$EXTERNALSYM POLICY_ERRV_SUBNET_DEF_SUM_PEAK_RATE}
  POLICY_ERRV_SUBNET_GRP_SUM_PEAK_RATE         = 46;
  {$EXTERNALSYM POLICY_ERRV_SUBNET_GRP_SUM_PEAK_RATE}
  POLICY_ERRV_SUBNET_USER_SUM_PEAK_RATE        = 47;
  {$EXTERNALSYM POLICY_ERRV_SUBNET_USER_SUM_PEAK_RATE}
  POLICY_ERRV_SUBNET_UNAUTH_USER_SUM_PEAK_RATE = 48;
  {$EXTERNALSYM POLICY_ERRV_SUBNET_UNAUTH_USER_SUM_PEAK_RATE}

  POLICY_ERRV_UNKNOWN_USER       = 49;
  {$EXTERNALSYM POLICY_ERRV_UNKNOWN_USER}
  POLICY_ERRV_NO_PRIVILEGES      = 50;
  {$EXTERNALSYM POLICY_ERRV_NO_PRIVILEGES}
  POLICY_ERRV_EXPIRED_USER_TOKEN = 51;
  {$EXTERNALSYM POLICY_ERRV_EXPIRED_USER_TOKEN}
  POLICY_ERRV_NO_RESOURCES       = 52;
  {$EXTERNALSYM POLICY_ERRV_NO_RESOURCES}
  POLICY_ERRV_PRE_EMPTED         = 53;
  {$EXTERNALSYM POLICY_ERRV_PRE_EMPTED}
  POLICY_ERRV_USER_CHANGED       = 54;
  {$EXTERNALSYM POLICY_ERRV_USER_CHANGED}
  POLICY_ERRV_NO_ACCEPTS         = 55;
  {$EXTERNALSYM POLICY_ERRV_NO_ACCEPTS}
  POLICY_ERRV_NO_MEMORY          = 56;
  {$EXTERNALSYM POLICY_ERRV_NO_MEMORY}
  POLICY_ERRV_CRAZY_FLOWSPEC     = 57;
  {$EXTERNALSYM POLICY_ERRV_CRAZY_FLOWSPEC}


// Other RSVP defined Error codes

  RSVP_Err_NO_PATH       = 3;   (* No path state for Resv   *)
  {$EXTERNALSYM RSVP_Err_NO_PATH}
  RSVP_Err_NO_SENDER     = 4;   (* No sender info for Resv  *)
  {$EXTERNALSYM RSVP_Err_NO_SENDER}
  RSVP_Err_BAD_STYLE     = 5;   (* Conflicting style        *)
  {$EXTERNALSYM RSVP_Err_BAD_STYLE}
  RSVP_Err_UNKNOWN_STYLE = 6;   (* Unknown reservation style    *)
  {$EXTERNALSYM RSVP_Err_UNKNOWN_STYLE}
  RSVP_Err_BAD_DSTPORT   = 7;   (* Conflicting DstPort in Sess  *)
  {$EXTERNALSYM RSVP_Err_BAD_DSTPORT}
  RSVP_Err_BAD_SNDPORT   = 8;   (* Conflicting Sender port  *)
  {$EXTERNALSYM RSVP_Err_BAD_SNDPORT}
  RSVP_Err_AMBIG_FILTER  = 9;   (* Ambiguous Filter spec in Resv*)
  {$EXTERNALSYM RSVP_Err_AMBIG_FILTER}

  RSVP_Err_PREEMPTED     = 12;  (* Service Preempted        *)
  {$EXTERNALSYM RSVP_Err_PREEMPTED}

(* Unknown object Class-Num *)

  RSVP_Err_UNKN_OBJ_CLASS = 13;
  {$EXTERNALSYM RSVP_Err_UNKN_OBJ_CLASS}

(*   ErrVal = Class_num, CType  *)

 (* Unknown object C-Type    *)

  RSVP_Err_UNKNOWN_CTYPE = 14;
  {$EXTERNALSYM RSVP_Err_UNKNOWN_CTYPE}

(*   ErrVal = Class_num, CType  *)

  RSVP_Err_API_ERROR = 20;  (* API client error     *)
  {$EXTERNALSYM RSVP_Err_API_ERROR}

(*   ErrVal = API error code    *)

(* Traffic Control error    *)

  RSVP_Err_TC_ERROR = 21;
  {$EXTERNALSYM RSVP_Err_TC_ERROR}

(* Globally-defined sub-codes for : Traffic Control errors *)

  RSVP_Erv_Conflict_Serv  = 01;  (* Service Conflict     *)
  {$EXTERNALSYM RSVP_Erv_Conflict_Serv}
  RSVP_Erv_No_Serv        = 02;  (* Unknown Service      *)
  {$EXTERNALSYM RSVP_Erv_No_Serv}
  RSVP_Erv_Crazy_Flowspec = 03;  (* Unreasonable Flowspec    *)
  {$EXTERNALSYM RSVP_Erv_Crazy_Flowspec}
  RSVP_Erv_Crazy_Tspec    = 04;  (* Unreasonable Tspec       *)
  {$EXTERNALSYM RSVP_Erv_Crazy_Tspec}

  RSVP_Err_TC_SYS_ERROR = 22;  (* Traffic control system error *)
  {$EXTERNALSYM RSVP_Err_TC_SYS_ERROR}

(* ErrVal = kernel error code   *)


(* RSVP System error      *)

  RSVP_Err_RSVP_SYS_ERROR = 23;
  {$EXTERNALSYM RSVP_Err_RSVP_SYS_ERROR}

(* Globally-defined sub-codes for : RSVP system errors *)

  RSVP_Erv_MEMORY = 1;   (* Out of memory *)
  {$EXTERNALSYM RSVP_Erv_MEMORY}
  RSVP_Erv_API    = 2;   (* API logic error *)
  {$EXTERNALSYM RSVP_Erv_API}

// Identity Policy elements related defines

// Reseved Identity PE types

  LPM_PE_USER_IDENTITY = 2;
  {$EXTERNALSYM LPM_PE_USER_IDENTITY}
  LPM_PE_APP_IDENTITY  = 3;
  {$EXTERNALSYM LPM_PE_APP_IDENTITY}

// Defines for Identity error values

  ERROR_NO_MORE_INFO          = 1;
  {$EXTERNALSYM ERROR_NO_MORE_INFO}
  UNSUPPORTED_CREDENTIAL_TYPE = 2;
  {$EXTERNALSYM UNSUPPORTED_CREDENTIAL_TYPE}
  INSUFFICIENT_PRIVILEGES     = 3;
  {$EXTERNALSYM INSUFFICIENT_PRIVILEGES}
  EXPIRED_CREDENTIAL          = 4;
  {$EXTERNALSYM EXPIRED_CREDENTIAL}
  IDENTITY_CHANGED            = 5;
  {$EXTERNALSYM IDENTITY_CHANGED}

type
  ID_ERROR_OBJECT = record
    usIdErrLength: USHORT;
    ucAType: UCHAR;
    ucSubType: UCHAR;
    usReserved: USHORT;
    usIdErrorValue: USHORT;
    ucIdErrData: array [0..3] of UCHAR;
  end;
  {$EXTERNALSYM ID_ERROR_OBJECT}
  TIdErrorObject = ID_ERROR_OBJECT;
  PIdErrorObject = ^ID_ERROR_OBJECT;

const
  ID_ERR_OBJ_HDR_LEN = SizeOf(ID_ERROR_OBJECT) - 4 * SizeOf(UCHAR);
  {$EXTERNALSYM ID_ERR_OBJ_HDR_LEN}

(*

    LPM API specific definitions

*)

(**************************************

    LPM_Initialize

***************************************)

type
  LPM_HANDLE = HANDLE;
  {$EXTERNALSYM LPM_HANDLE}

  RHANDLE = HANDLE;
  {$EXTERNALSYM RHANDLE}

  LPV = ULONG;
  {$EXTERNALSYM LPV}

  PETYPE = USHORT;
  {$EXTERNALSYM PETYPE}

const
  LPM_OK = 0;
  {$EXTERNALSYM LPM_OK}

type
  MSG_TYPE = Integer;
  {$EXTERNALSYM MSG_TYPE}
  TMsgType = MSG_TYPE;

  rsvpmsgobjs = record
    RsvpMsgType: TMsgType;
    pRsvpSession: PRsvpSession;
    pRsvpFromHop: PRsvpHop;
    pRsvpToHop: PRsvpHop;
    pResvStyle: PResvStyle;
    pRsvpScope: PRsvpScope;
    FlowDescCount: Integer;
    pFlowDescs: PFlowDesc;
    PdObjectCount: Integer;
    ppPdObjects: ^PPolicyData;
    pErrorSpec: PErrorSpec;
    pAdspec: PADSpec;
  end;
  {$EXTERNALSYM rsvpmsgobjs}
  RSVP_MSG_OBJS = rsvpmsgobjs;
  {$EXTERNALSYM RSVP_MSG_OBJS}
  TRsvpMsgObjs = RSVP_MSG_OBJS;
  PRsvpMsgObjs = ^RSVP_MSG_OBJS;
  
  PALLOCMEM = function (Size: DWORD): Pointer; stdcall;
  {$EXTERNALSYM PALLOCMEM}
  TAllocMem = PALLOCMEM;

  PFREEMEM = procedure (pv: Pointer); stdcall;
  {$EXTERNALSYM PFREEMEM}
  TFreeMem = PFREEMEM;

  policy_decision = record
    lpvResult: LPV;        // Use the LPV values from above
    wPolicyErrCode: WORD;   // RSVP defined error codes
    wPolicyErrValue: WORD;  // RSVP defined error values
  end;
  {$EXTERNALSYM policy_decision}
  TPolicyDecision = policy_decision;
  PPolicyDecision = ^policy_decision;

  CBADMITRESULT = function (LpmHandle: LPM_HANDLE; RequestHandle: RHANDLE;
    ulPcmActionFlags: ULONG; LpmError: Integer; PolicyDecisionsCount: Integer;
    pPolicyDecisions: PPolicyDecision): ULONG; stdcall;
  {$EXTERNALSYM CBADMITRESULT}
  TCbAdmitResult = CBADMITRESULT;

  CBGETRSVPOBJECTS = function (LpmHandle: LPM_HANDLE; RequestHandle: RHANDLE;
    LpmError: Integer; RsvpObjectsCount: Integer; ppRsvpObjects: PPRsvpObjHdr): ULONG; stdcall;
  {$EXTERNALSYM CBGETRSVPOBJECTS}
  TCbGetRsvpObjects = CBGETRSVPOBJECTS;

// The above 2 call backs can return the following errors

const
  INV_LPM_HANDLE = 1; // Supplied LpmHandle is invalid
  {$EXTERNALSYM INV_LPM_HANDLE}
  LPM_TIME_OUT   = 2; // LPM has returned results after the time limit
  {$EXTERNALSYM LPM_TIME_OUT}
  INV_REQ_HANDLE = 3; // Supplied Request handle is invalid
  {$EXTERNALSYM INV_REQ_HANDLE}
  DUP_RESULTS    = 4; // LPM has already returned results for this request
  {$EXTERNALSYM DUP_RESULTS}
  INV_RESULTS    = 5; // Results supplied are invalid
  {$EXTERNALSYM INV_RESULTS}

type
  lpminitinfo = record
    PcmVersionNumber: DWORD;
    ResultTimeLimit: DWORD;
    ConfiguredLpmCount: Integer;
    AllocMemory: PALLOCMEM;
    FreeMemory: PFREEMEM;
    PcmAdmitResultCallback: CBADMITRESULT;
    GetRsvpObjectsCallback: CBGETRSVPOBJECTS;
  end;
  {$EXTERNALSYM lpminitinfo}
  LPM_INIT_INFO = lpminitinfo;
  {$EXTERNALSYM LPM_INIT_INFO}
  TLpmInitInfo = LPM_INIT_INFO;
  PLpmInitInfo = ^LPM_INIT_INFO;  

// Valid PE types
// XXX ISSUE - Is 0xFFFF a better choice?

const
  LPM_PE_ALL_TYPES = 0;
  {$EXTERNALSYM LPM_PE_ALL_TYPES}

// Current LPM API version number

  LPM_API_VERSION_1 = 1;
  {$EXTERNALSYM LPM_API_VERSION_1}

// Current PCM version number

  PCM_VERSION_1 = 1;
  {$EXTERNALSYM PCM_VERSION_1}

function LPM_Initialize(LpmHandle: LPM_HANDLE; const pLpmInitInfo: LPM_INIT_INFO;
  var pLpmVersionNumber: DWORD; var pSupportedPeType: PETYPE; Reserved: Pointer): ULONG; stdcall;
{$EXTERNALSYM LPM_Initialize}

(**************************************

    LPM_Deinitialize

***************************************)

function LPM_Deinitialize(LpmHandle: LPM_HANDLE): ULONG; stdcall;
{$EXTERNALSYM LPM_Deinitialize}

(**************************************

    LPM_AdmitRsvpMsg

***************************************)

// Valid LPV - LPM Priority Values

const
  LPV_RESERVED     = 0;
  {$EXTERNALSYM LPV_RESERVED}
  LPV_MIN_PRIORITY = 1;
  {$EXTERNALSYM LPV_MIN_PRIORITY}
  LPV_MAX_PRIORITY = $FF00;
  {$EXTERNALSYM LPV_MAX_PRIORITY}
  LPV_DROP_MSG     = $FFFD;
  {$EXTERNALSYM LPV_DROP_MSG}
  LPV_DONT_CARE    = $FFFE;
  {$EXTERNALSYM LPV_DONT_CARE}
  LPV_REJECT       = $FFFF;
  {$EXTERNALSYM LPV_REJECT}

// Valid values for PcmActionFlags

  FORCE_IMMEDIATE_REFRESH = 1;
  {$EXTERNALSYM FORCE_IMMEDIATE_REFRESH}

// Function return values for LPM_AdmitResvMsg

  LPM_RESULT_READY = 0;
  {$EXTERNALSYM LPM_RESULT_READY}
  LPM_RESULT_DEFER = 1;
  {$EXTERNALSYM LPM_RESULT_DEFER}

function LPM_AdmitRsvpMsg(PcmReqHandle: RHANDLE; const pRecvdIntf: RSVP_HOP;
  const pRsvpMsgObjs: RSVP_MSG_OBJS; RcvdRsvpMsgLength: Integer; RcvdRsvpMsg: PUCHAR;
  var pulPcmActionFlags: ULONG; pPolicyDecisions: PPolicyDecision; Reserved: Pointer): ULONG; stdcall;
{$EXTERNALSYM LPM_AdmitRsvpMsg}

(**************************************

    LPM_GetRsvpObjects

***************************************)

// Function return values are defined in LPM_AdmitResvMsg section

function LPM_GetRsvpObjects(PcmReqHandle: RHANDLE; MaxPdSize: ULONG;
  SendingIntfAddr: PRsvpHop; pRsvpMsgObjs: PRsvpMsgObjs; var pRsvpObjectsCount: Integer;
  var pppRsvpObjects: PRsvpObjHdr; Reserved: Pointer): ULONG; stdcall;
{$EXTERNALSYM LPM_GetRsvpObjects}

(**************************************

    LPM_DeleteState

***************************************)

// TearDown reasons

const
  RCVD_PATH_TEAR  = 1;
  {$EXTERNALSYM RCVD_PATH_TEAR}
  RCVD_RESV_TEAR  = 2;
  {$EXTERNALSYM RCVD_RESV_TEAR}
  ADM_CTRL_FAILED = 3;
  {$EXTERNALSYM ADM_CTRL_FAILED}
  STATE_TIMEOUT   = 4;
  {$EXTERNALSYM STATE_TIMEOUT}
  FLOW_DURATION   = 5;
  {$EXTERNALSYM FLOW_DURATION}


procedure LPM_DeleteState(pRcvdIfAddr: PRsvpHop; RsvpMsgType: TMsgType;
  pRsvpSession: PRsvpSession; pRsvpFromHop: PRsvpHop; pResvStyle: PResvStyle;
  FilterSpecCount: Integer; ppFilterSpecList: PFilterSpec; TearDownReason: Integer); stdcall;
{$EXTERNALSYM LPM_DeleteState}

(**************************************

    LPM_IpAddrTable

***************************************)

type
  lpmiptable = record
    ulIfIndex: ULONG;    // SNMP index for this interface
    MediaType: ULONG;    // As defined in IPIFCONS.H
    IfIpAddr: IN_ADDR;   // Interface IP address
    IfNetMask: IN_ADDR;  // Interface subnet mask
  end;
  {$EXTERNALSYM lpmiptable}
  TLpmIpTable = lpmiptable;
  PLpmIpTable = ^lpmiptable;

function LPM_IpAddressTable(cIpAddrTable: ULONG; pIpAddrTable: PLpmIpTable): BOOL; stdcall;
{$EXTERNALSYM LPM_IpAddressTable}

(**************************************

    LPM_CommitResv

***************************************)

// CommitDecision values

const
  RESOURCES_ALLOCATED = 1;
  {$EXTERNALSYM RESOURCES_ALLOCATED}
  RESOURCES_MODIFIED  = 2;
  {$EXTERNALSYM RESOURCES_MODIFIED}

procedure LPM_CommitResv(RsvpSession: PRsvpSession; FlowInstalledIntf: PRsvpHop;
  RsvpStyle: PResvStyle; FilterSpecCount: Integer; ppFilterSpecList: PFilterSpec;
  pMergedFlowSpec: PIsFlowSpec; CommitDecision: ULONG); stdcall;
{$EXTERNALSYM LPM_CommitResv}

implementation

function ObjLength(const x: TRsvpObjHdr): USHORT;
begin
  Result := x.obj_length;
end;

function ObjCType(const x: TRsvpObjHdr): UCHAR;
begin
  Result := x.obj_ctype;
end;

function ObjClass(const x: TRsvpObjHdr): UCHAR;
begin
  Result := x.obj_class;
end;

function ObjData(const x: TRsvpObjHdr): Pointer;
begin
  Result := Pointer(Integer(@x) + SizeOf(x));
end;

function Style_is_Wildcard(p: DWORD): Boolean;
begin
  Result := (p and Opt_SndSel_mask) = Opt_Wildcard;
end;

function Style_is_Shared(p: DWORD): Boolean;
begin
  Result := (p and Opt_Share_mask) = Opt_Shared;
end;

function Error_Usage(x: DWORD): DWORD;
begin
  Result := (x shr 12) and 3;
end;

function Intserv_Version(x: DWORD): DWORD;
begin
  Result := (x and INTSERV_VERS_MASK) shr 4;
end;

function Intserv_Version_OK(const x: TIntServMainHdr): Boolean;
begin
  Result := (x.ismh_version and INTSERV_VERS_MASK) = INTSERV_VERSION0;
end;

function Intserv_Obj_size(const x: TIntServMainHdr): DWORD;
begin
  Result := x.ismh_len32b * 4 + SizeOf(IntServMainHdr) + SizeOf(RsvpObjHdr);
end;

function Issh_len32b(const p: TIntServServiceHdr): USHORT;
begin
  Result := p.issh_len32b;
end;

const
  lpmlib = 'msidlpm.dll';


{$IFDEF DYNAMIC_LINK}
var
  _LPM_Initialize: Pointer;

function LPM_Initialize;
begin
  GetProcedureAddress(_LPM_Initialize, lpmlib, 'LPM_Initialize');
  asm
    mov esp, ebp
    pop ebp
    jmp [_LPM_Initialize]
  end;
end;
{$ELSE}
function LPM_Initialize; external lpmlib name 'LPM_Initialize';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _LPM_Deinitialize: Pointer;

function LPM_Deinitialize;
begin
  GetProcedureAddress(_LPM_Deinitialize, lpmlib, 'LPM_Deinitialize');
  asm
    mov esp, ebp
    pop ebp
    jmp [_LPM_Deinitialize]
  end;
end;
{$ELSE}
function LPM_Deinitialize; external lpmlib name 'LPM_Deinitialize';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _LPM_AdmitRsvpMsg: Pointer;

function LPM_AdmitRsvpMsg;
begin
  GetProcedureAddress(_LPM_AdmitRsvpMsg, lpmlib, 'LPM_AdmitRsvpMsg');
  asm
    mov esp, ebp
    pop ebp
    jmp [_LPM_AdmitRsvpMsg]
  end;
end;
{$ELSE}
function LPM_AdmitRsvpMsg; external lpmlib name 'LPM_AdmitRsvpMsg';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _LPM_GetRsvpObjects: Pointer;

function LPM_GetRsvpObjects;
begin
  GetProcedureAddress(_LPM_GetRsvpObjects, lpmlib, 'LPM_GetRsvpObjects');
  asm
    mov esp, ebp
    pop ebp
    jmp [_LPM_GetRsvpObjects]
  end;
end;
{$ELSE}
function LPM_GetRsvpObjects; external lpmlib name 'LPM_GetRsvpObjects';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _LPM_DeleteState: Pointer;

procedure LPM_DeleteState;
begin
  GetProcedureAddress(_LPM_DeleteState, lpmlib, 'LPM_DeleteState');
  asm
    mov esp, ebp
    pop ebp
    jmp [_LPM_DeleteState]
  end;
end;
{$ELSE}
procedure LPM_DeleteState; external lpmlib name 'LPM_DeleteState';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _LPM_IpAddressTable: Pointer;

function LPM_IpAddressTable;
begin
  GetProcedureAddress(_LPM_IpAddressTable, lpmlib, 'LPM_IpAddressTable');
  asm
    mov esp, ebp
    pop ebp
    jmp [_LPM_IpAddressTable]
  end;
end;
{$ELSE}
function LPM_IpAddressTable; external lpmlib name 'LPM_IpAddressTable';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _LPM_CommitResv: Pointer;

procedure LPM_CommitResv;
begin
  GetProcedureAddress(_LPM_CommitResv, lpmlib, 'LPM_CommitResv');
  asm
    mov esp, ebp
    pop ebp
    jmp [_LPM_CommitResv]
  end;
end;
{$ELSE}
procedure LPM_CommitResv; external lpmlib name 'LPM_CommitResv';
{$ENDIF DYNAMIC_LINK}

end.
