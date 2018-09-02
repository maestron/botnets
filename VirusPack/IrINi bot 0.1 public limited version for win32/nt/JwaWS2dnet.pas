{******************************************************************************}
{                                                       	               }
{ Winsock2 DecNET API interface Unit for Object Pascal                         }
{                                                       	               }
{ Portions created by Microsoft are Copyright (C) 1995-2001 Microsoft          }
{ Corporation. All Rights Reserved.                                            }
{ 								               }
{ The original file is: ws2dnet.h, released June 2000. The original Pascal     }
{ code is: WS2dnet.pas, released December 2000. The initial developer of the   }
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

unit JwaWS2dnet;

{$WEAKPACKAGEUNIT}

{$HPPEMIT ''}
{$HPPEMIT '#include "ws2dnet.h"'}
{$HPPEMIT ''}

{$I WINDEFINES.INC}

interface

uses
  JwaWinSock2;

//************************************************************************
//  Winsock V2.0  DECnet definitions		File: WS2DNET.H
//************************************************************************

//
//  DECnet WinSock Definitions
//

const
  DNPROTO_NSP = 1; // DECnet NSP transport protocol
  {$EXTERNALSYM DNPROTO_NSP}
  DNPROTO_RAW = 255;
  {$EXTERNALSYM DNPROTO_RAW}

  DN_MAXADDL   = 20; // maximum DECnet address length
  {$EXTERNALSYM DN_MAXADDL}
  DN_ADDL      = 2; // DECnet NSP address length
  {$EXTERNALSYM DN_ADDL}
  DN_MAXOPTL   = 16; // Maximum DECnet optional data length
  {$EXTERNALSYM DN_MAXOPTL}
  DN_MAXOBJL   = 16; // Maximum DECnet object name length
  {$EXTERNALSYM DN_MAXOBJL}
  DN_MAXACCL   = 39; // Maximum DECnet access string length
  {$EXTERNALSYM DN_MAXACCL}
  DN_MAXALIASL = 128; // Maximum DECnet alias string length
  {$EXTERNALSYM DN_MAXALIASL}
  DN_MAXNODEL  = 7; // Maximum DECnet Phase IV node string length
  {$EXTERNALSYM DN_MAXNODEL}

// DECnet Extension Function Identifiers

  WS2API_DECNET_dnet_addr     = 1;
  {$EXTERNALSYM WS2API_DECNET_dnet_addr}
  WS2API_DECNET_dnet_eof      = 2;
  {$EXTERNALSYM WS2API_DECNET_dnet_eof}
  WS2API_DECNET_dnet_getacc   = 3;
  {$EXTERNALSYM WS2API_DECNET_dnet_getacc}
  WS2API_DECNET_dnet_getalias = 4;
  {$EXTERNALSYM WS2API_DECNET_dnet_getalias}
  WS2API_DECNET_dnet_htoa     = 5;
  {$EXTERNALSYM WS2API_DECNET_dnet_htoa}
  WS2API_DECNET_dnet_ntoa     = 6;
  {$EXTERNALSYM WS2API_DECNET_dnet_ntoa}
  WS2API_DECNET_getnodeadd    = 7;
  {$EXTERNALSYM WS2API_DECNET_getnodeadd}
  WS2API_DECNET_getnodebyaddr = 8;
  {$EXTERNALSYM WS2API_DECNET_getnodebyaddr}
  WS2API_DECNET_getnodebyname = 9;
  {$EXTERNALSYM WS2API_DECNET_getnodebyname}
  WS2API_DECNET_getnodename   = 10;
  {$EXTERNALSYM WS2API_DECNET_getnodename}
  WS2API_DECNET_MAX           = 10;
  {$EXTERNALSYM WS2API_DECNET_MAX}

//
//  DECnet address structure
//

type
  dn_naddr = packed record
    a_len: Word;		               // length of address
    a_addr: array [0..DN_MAXADDL - 1] of Byte; // address as bytes
  end;
  {$EXTERNALSYM dn_naddr}
  DNNADDR = dn_naddr;
  {$EXTERNALSYM DNNADDR}
  LPDNNADDR = ^DNNADDR;
  {$EXTERNALSYM LPDNNADDR}
  TDNNAddr = DNNADDR;
  PDNNAddr = LPDNNADDR;  

//
//  DECnet socket address structure
//

  sockaddr_dn = packed record
    sdn_family: Word;	    // AF_DECnet
    sdn_flags: Byte;	    // flags
    sdn_objnum: Byte;	    // object number
    sdn_objnamel: Word;	// size of object name
    sdn_objname: array [0..DN_MAXOBJL - 1] of Char;	// object name
    sdn_add: dn_naddr;	    // node address
  end;
  {$EXTERNALSYM sockaddr_dn}
  SOCKADDRDN = sockaddr_dn;
  {$EXTERNALSYM SOCKADDRDN}
  LPSOCKADDRDN = ^SOCKADDRDN;
  {$EXTERNALSYM LPSOCKADDRDN}
  TSockAddrDN = SOCKADDRDN;
  PSockAddrDN = LPSOCKADDRDN;

//  Common DECnet object numbers (used in sockaddr_dn)

const
  DNOBJECT_FAL	= 17;		//    = file access listener;
  {$EXTERNALSYM DNOBJECT_FAL}
  DNOBJECT_NICE	= 19;		//   = network management;
  {$EXTERNALSYM DNOBJECT_NICE}
  DNOBJECT_DTERM  = 23;		//  = remote terminals;
  {$EXTERNALSYM DNOBJECT_DTERM}
  DNOBJECT_MIRROR = 25;		// = loopback mirror;
  {$EXTERNALSYM DNOBJECT_MIRROR}
  DNOBJECT_EVR = 26;		//    = event receiver;
  {$EXTERNALSYM DNOBJECT_EVR}
  DNOBJECT_MAIL11 = 27;		// = Mail-11 service;
  {$EXTERNALSYM DNOBJECT_MAIL11}
  DNOBJECT_PHONE = 29;		//  = phone utility;
  {$EXTERNALSYM DNOBJECT_PHONE}
  DNOBJECT_CTERM = 42;		//  = command terminals;
  {$EXTERNALSYM DNOBJECT_CTERM}
  DNOBJECT_DTR = 63;		//    = data test receiver;
  {$EXTERNALSYM DNOBJECT_DTR}

//
//  DECnet node structure
//

type
  nodeent_f = packed record
    n_name: PChar;      // name of node
    n_addrtype: Word;	// node address type
    n_length: Word;	// address length
    n_addr: PChar;	// address
    n_params: PChar;	// node parameters
    n_reserved: array [0..15] of Byte;	// Reserved
  end;
  {$EXTERNALSYM nodeent_f}
  NODEENTF = nodeent_f;
  {$EXTERNALSYM NODEENTF}
  LPNODEENTF = ^NODEENTF;
  {$EXTERNALSYM LPNODEENTF}
  TNodeEntF = NODEENTF;
  PNodeEntF = LPNODEENTF;

//
//  DECnet set/get DSO_CONDATA, DSO_DISDATA (optional data) structure
//

  optdata_dn = packed record
    opt_status: Word;	          // extended status return
    opt_optl: Word;	          // user data length
    opt_data: array [0..DN_MAXOPTL - 1] of Byte; // user data
  end;
  {$EXTERNALSYM optdata_dn}
  OPTDATADN = optdata_dn;
  {$EXTERNALSYM OPTDATADN}
  LPOPTDATADN = ^OPTDATADN;
  {$EXTERNALSYM LPOPTDATADN}
  TOptDataDN = OPTDATADN;
  POptDataDN = LPOPTDATADN;

//
//  DECnet set/get DSO_CONACCESS access (control data) structure
//

  accessdata_dn = packed record
    acc_accl: Word;	            // account string length
    acc_acc: array [0..DN_MAXACCL] of Byte;	// account string
    acc_passl: Word;	            // password string length
    acc_pass: array [0..DN_MAXACCL] of Byte;	// password string
    acc_userl: Word;	            // user string length
    acc_user: array [0..DN_MAXACCL] of Byte;	// user string
  end;
  {$EXTERNALSYM accessdata_dn}
  ACCESSDATADN = accessdata_dn;
  {$EXTERNALSYM ACCESSDATADN}
  LPACCESSDATADN = ^ACCESSDATADN;
  {$EXTERNALSYM LPACCESSDATADN}
  TAccessDataDN = ACCESSDATADN;
  PAccessDataDN = LPACCESSDATADN;  

//
//  DECnet call data structure (concatenated access and optional data)
//

  calldata_dn = packed record
    optdata_dn: optdata_dn;
    accessdata_dn: accessdata_dn;
  end;
  {$EXTERNALSYM calldata_dn}
  CALLDATADN = calldata_dn;
  {$EXTERNALSYM CALLDATADN}
  LPCALLDATADN = ^CALLDATADN;
  {$EXTERNALSYM LPCALLDATADN}
  TCallDataDN = CALLDATADN;
  PCallDataDN = LPCALLDATADN;  

//
//  DECnet incoming access control structure
//

  dnet_accent = packed record
    dac_status: Byte;      // Reserved
    dac_type: Byte;        // DN_NONE, etc.
    dac_username: array [0..DN_MAXACCL] of Char;
    dac_password: array [0..DN_MAXACCL] of Char;
  end;
  {$EXTERNALSYM dnet_accent}
  DNETACCENT = dnet_accent;
  {$EXTERNALSYM DNETACCENT}
  LPDNETACCENT = ^DNETACCENT;
  {$EXTERNALSYM LPDNETACCENT}
  TDNetAccent = DNETACCENT;
  PDNetAccent = LPDNETACCENT;  

const
  DN_NONE = $00;
  {$EXTERNALSYM DN_NONE}
  DN_RO   = $01;
  {$EXTERNALSYM DN_RO}
  DN_WO   = $02;
  {$EXTERNALSYM DN_WO}
  DN_RW   = $03;
  {$EXTERNALSYM DN_RW}

// DECnet logical link information structure

type
  linkinfo_dn = packed record
    idn_segsize: Word;   // segment size for link
    idn_linkstate: Byte; // logical link state
  end;
  {$EXTERNALSYM linkinfo_dn}
  LINKINFODN = linkinfo_dn;
  {$EXTERNALSYM LINKINFODN}
  LPLINKINFODN = ^LINKINFODN;
  {$EXTERNALSYM LPLINKINFODN}
  TLinkInfoDN = LINKINFODN;
  PLinkInfoDN = LPLINKINFODN;

const
  SO_LINKINFO      = 7; // set/get link information
  {$EXTERNALSYM SO_LINKINFO}
  LL_INACTIVE      = 0; // logical link inactive
  {$EXTERNALSYM LL_INACTIVE}
  LL_CONNECTING    = 1; // logical link connecting
  {$EXTERNALSYM LL_CONNECTING}
  LL_RUNNING       = 2; // logical link running
  {$EXTERNALSYM LL_RUNNING}
  LL_DISCONNECTING = 3; // logical link disconnecting
  {$EXTERNALSYM LL_DISCONNECTING}

//*********************************************************************
//  DECnet WinSock 2 extended function prototypes
//*********************************************************************

(*
MVB TODO: Extension functions must be dynamically queried for using WSAIoctl.

function dnet_addr(cp: PChar): PDNAddr; stdcall;
{$EXTERNALSYM dnet_addr}
function dnet_eof(s: SOCKET): Integer; stdcall;
{$EXTERNALSYM dnet_eof}
function dnet_getacc(const nacc: TDNetAccent): PDNetAccent; stdcall;
{$EXTERNALSYM dnet_getacc}
function dnet_getalias(P: PChar): PChar; stdcall;
{$EXTERNALSYM dnet_getalias}
function dnet_htoa(const add: TDNNAddr): PChar; stdcall;
{$EXTERNALSYM dnet_htoa}
function dnet_ntoa(const add: TDNNAddr): PChar; stdcall;
{$EXTERNALSYM dnet_ntoa}
function getnodeadd: PDNNAddr; stdcall;
{$EXTERNALSYM getnodeadd}
function getnodebyaddr(addr: PChar; len, type_: Integer): PNodeEntF; stdcall;
{$EXTERNALSYM getnodebyaddr}
function getnodebyname(name: PChar): PNodeEntF; stdcall;
{$EXTERNALSYM getnodebyname}
function getnodename: PChar; stdcall;
{$EXTERNALSYM getnodename}
*)

// typedefs for C++ compatability

type
  LPDNETADDR = function (cp: PChar): PDNNAddr; stdcall;
  {$EXTERNALSYM LPDNETADDR}
  TDNetAddr = LPDNETADDR;
  LPDNETEOF = function (s: TSocket): Integer; stdcall;
  {$EXTERNALSYM LPDNETEOF}
  TDNetEOF = LPDNETEOF;
  LPDNETGETACC = function (const nacc: TDNetAccent): PDNetAccent; stdcall;
  {$EXTERNALSYM LPDNETGETACC}
  TDNetGetAcc = LPDNETGETACC;
  LPDNETGETALIAS = function (P: PChar): PChar; stdcall;
  {$EXTERNALSYM LPDNETGETALIAS}
  TDNetGetAlias = LPDNETGETALIAS;
  LPDNETHTOA = function (const add: TDNNAddr): PChar; stdcall;
  {$EXTERNALSYM LPDNETHTOA}
  TDNetHToA = LPDNETHTOA;
  LPDNETNTOA = function (const add: TDNNAddr): PChar; stdcall;
  {$EXTERNALSYM LPDNETNTOA}
  TDNetNToA = LPDNETNTOA;
  LPGETNODEADD = function: PDNNAddr; stdcall;
  {$EXTERNALSYM LPGETNODEADD}
  TGetNodeAdd = LPGETNODEADD;
  LPGETNODEBYADDR = function (addr: PChar; len, type_: Integer): PNodeEntF; stdcall;
  {$EXTERNALSYM LPGETNODEBYADDR}
  TGetNodeByAddr = LPGETNODEBYADDR;
  LPGETNODEBYNAME = function (name: PChar): PNodeEntF; stdcall;
  {$EXTERNALSYM LPGETNODEBYNAME}
  TGetNodeByName = LPGETNODEBYNAME;
  LPGETNODENAME = function: PChar; stdcall;
  {$EXTERNALSYM LPGETNODENAME}
  TGetNodeName = LPGETNODENAME;

implementation

end.
