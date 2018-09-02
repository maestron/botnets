{******************************************************************************}
{                                                       	               }
{ RPC DCE API interface Unit for Object Pascal                                 }
{                                                       	               }
{ Portions created by Microsoft are Copyright (C) 1995-2001 Microsoft          }
{ Corporation. All Rights Reserved.                                            }
{ 								               }
{ The original file is: rpcdce.h, released June 2000. The original Pascal      }
{ code is: Rpcce.pas, released December 2000. The initial developer of the     }
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

unit JwaRpcDce;

{$WEAKPACKAGEUNIT}

{$HPPEMIT ''}
{$HPPEMIT '#include "RpcDce.h"'}
{$HPPEMIT ''}
{$HPPEMIT 'typedef RPC_BINDING_VECTOR *PRPC_BINDING_VECTOR'}
{$HPPEMIT 'typedef UUID_VECTOR *PUUID_VECTOR'}
{$HPPEMIT 'typedef RPC_IF_ID *PRPC_IF_ID'}
{$HPPEMIT 'typedef RPC_PROTSEQ_VECTORA *PRPC_PROTSEQ_VECTORA'}
{$HPPEMIT 'typedef RPC_PROTSEQ_VECTORW *PRPC_PROTSEQ_VECTORW'}
{$HPPEMIT 'typedef RPC_STATS_VECTOR *PRPC_STATS_VECTOR'}
{$HPPEMIT 'typedef RPC_IF_ID_VECTOR *PRPC_IF_ID_VECTOR'}
{$HPPEMIT 'typedef RPC_AUTHZ_HANDLE *PRPC_AUTHZ_HANDLE'}
{$HPPEMIT 'typedef RPC_AUTH_IDENTITY_HANDLE *PRPC_AUTH_IDENTITY_HANDLE'}
{$HPPEMIT 'typedef RPC_BINDING_HANDLE *PRPC_BINDING_HANDLE'}
{$HPPEMIT 'typedef UUID *PUUID'}
{$HPPEMIT 'typedef UUID *LPUUID'}
{$HPPEMIT ''}

{$I WINDEFINES.INC}

interface

uses
  JwaWinNT, JwaWinType, JwaRpc;

type
  PPChar = ^PChar;
  PPWideChar = ^PWideChar;
  PCardinal = ^Cardinal;

  RPC_BINDING_HANDLE = I_RPC_HANDLE;
  {$EXTERNALSYM RPC_BINDING_HANDLE}
  UUID = GUID;
  {$EXTERNALSYM UUID}

  PRPC_BINDING_HANDLE = ^RPC_BINDING_HANDLE;
  {$NODEFINE PRPC_BINDING_HANDLE}
  PUUID = ^UUID;
  {$NODEFINE PUUID}
  LPUUID = ^UUID;
  {$NODEFINE LPUUID}

type
  PRPC_BINDING_VECTOR = ^RPC_BINDING_VECTOR;
  {$NODEFINE PRPC_BINDING_VECTOR}
  _RPC_BINDING_VECTOR = record
    Count: Cardinal;
    BindingH: array [0..0] of RPC_BINDING_HANDLE;
  end;
  {$EXTERNALSYM _RPC_BINDING_VECTOR}
  RPC_BINDING_VECTOR = _RPC_BINDING_VECTOR;
  {$EXTERNALSYM RPC_BINDING_VECTOR}
  TRpcBindingVector = RPC_BINDING_VECTOR;
  PRpcBindingVector = PRPC_BINDING_VECTOR;

  PUUID_VECTOR = ^UUID_VECTOR;
  {$NODEFINE PUUID_VECTOR}
  _UUID_VECTOR = record
    Count: Cardinal;
    Uuid: array [0..0] of PUUID;
  end;
  {$EXTERNALSYM _UUID_VECTOR}
  UUID_VECTOR = _UUID_VECTOR;
  {$EXTERNALSYM UUID_VECTOR}
  TUuidVector = UUID_VECTOR;
  PUuidVector = ^TUuidVector;

  RPC_IF_HANDLE = LPVOID;
  {$EXTERNALSYM RPC_IF_HANDLE}

  PRPC_IF_ID = ^RPC_IF_ID;
  {$NODEFINE PRPC_IF_ID}
  _RPC_IF_ID = record
    Uuid: UUID;
    VersMajor: Word;
    VersMinor: Word;
  end;
  {$EXTERNALSYM _RPC_IF_ID}
  RPC_IF_ID = _RPC_IF_ID;
  {$EXTERNALSYM RPC_IF_ID}
  TRpcIfId = RPC_IF_ID;
  PRpcIfId = ^TRpcIfId;

const
  RPC_C_BINDING_INFINITE_TIMEOUT = 10;
  {$EXTERNALSYM RPC_C_BINDING_INFINITE_TIMEOUT}
  RPC_C_BINDING_MIN_TIMEOUT      = 0;
  {$EXTERNALSYM RPC_C_BINDING_MIN_TIMEOUT}
  RPC_C_BINDING_DEFAULT_TIMEOUT  = 5;
  {$EXTERNALSYM RPC_C_BINDING_DEFAULT_TIMEOUT}
  RPC_C_BINDING_MAX_TIMEOUT      = 9;
  {$EXTERNALSYM RPC_C_BINDING_MAX_TIMEOUT}

  RPC_C_CANCEL_INFINITE_TIMEOUT  = DWORD(-1);
  {$EXTERNALSYM RPC_C_CANCEL_INFINITE_TIMEOUT}

  RPC_C_LISTEN_MAX_CALLS_DEFAULT = 1234;
  {$EXTERNALSYM RPC_C_LISTEN_MAX_CALLS_DEFAULT}
  RPC_C_PROTSEQ_MAX_REQS_DEFAULT = 10;
  {$EXTERNALSYM RPC_C_PROTSEQ_MAX_REQS_DEFAULT}

// RPC_POLICY EndpointFlags.

  RPC_C_BIND_TO_ALL_NICS  = 1;
  {$EXTERNALSYM RPC_C_BIND_TO_ALL_NICS}
  RPC_C_USE_INTERNET_PORT = $1;
  {$EXTERNALSYM RPC_C_USE_INTERNET_PORT}
  RPC_C_USE_INTRANET_PORT = $2;
  {$EXTERNALSYM RPC_C_USE_INTRANET_PORT}
  RPC_C_DONT_FAIL         = $4;
  {$EXTERNALSYM RPC_C_DONT_FAIL}

// RPC_POLICY EndpointFlags specific to the Falcon/RPC transport:

  RPC_C_MQ_TEMPORARY                 = $0000;
  {$EXTERNALSYM RPC_C_MQ_TEMPORARY}
  RPC_C_MQ_PERMANENT                 = $0001;
  {$EXTERNALSYM RPC_C_MQ_PERMANENT}
  RPC_C_MQ_CLEAR_ON_OPEN             = $0002;
  {$EXTERNALSYM RPC_C_MQ_CLEAR_ON_OPEN}
  RPC_C_MQ_USE_EXISTING_SECURITY     = $0004;
  {$EXTERNALSYM RPC_C_MQ_USE_EXISTING_SECURITY}
  RPC_C_MQ_AUTHN_LEVEL_NONE          = $0000;
  {$EXTERNALSYM RPC_C_MQ_AUTHN_LEVEL_NONE}
  RPC_C_MQ_AUTHN_LEVEL_PKT_INTEGRITY = $0008;
  {$EXTERNALSYM RPC_C_MQ_AUTHN_LEVEL_PKT_INTEGRITY}
  RPC_C_MQ_AUTHN_LEVEL_PKT_PRIVACY   = $0010;
  {$EXTERNALSYM RPC_C_MQ_AUTHN_LEVEL_PKT_PRIVACY}

// Client: RpcBindingSetOption() values for the Falcon/RPC transport:

  RPC_C_OPT_MQ_DELIVERY            = 1;
  {$EXTERNALSYM RPC_C_OPT_MQ_DELIVERY}
  RPC_C_OPT_MQ_PRIORITY            = 2;
  {$EXTERNALSYM RPC_C_OPT_MQ_PRIORITY}
  RPC_C_OPT_MQ_JOURNAL             = 3;
  {$EXTERNALSYM RPC_C_OPT_MQ_JOURNAL}
  RPC_C_OPT_MQ_ACKNOWLEDGE         = 4;
  {$EXTERNALSYM RPC_C_OPT_MQ_ACKNOWLEDGE}
  RPC_C_OPT_MQ_AUTHN_SERVICE       = 5;
  {$EXTERNALSYM RPC_C_OPT_MQ_AUTHN_SERVICE}
  RPC_C_OPT_MQ_AUTHN_LEVEL         = 6;
  {$EXTERNALSYM RPC_C_OPT_MQ_AUTHN_LEVEL}
  RPC_C_OPT_MQ_TIME_TO_REACH_QUEUE = 7;
  {$EXTERNALSYM RPC_C_OPT_MQ_TIME_TO_REACH_QUEUE}
  RPC_C_OPT_MQ_TIME_TO_BE_RECEIVED = 8;
  {$EXTERNALSYM RPC_C_OPT_MQ_TIME_TO_BE_RECEIVED}
  RPC_C_OPT_BINDING_NONCAUSAL      = 9;
  {$EXTERNALSYM RPC_C_OPT_BINDING_NONCAUSAL}
  RPC_C_OPT_SECURITY_CALLBACK      = 10;
  {$EXTERNALSYM RPC_C_OPT_SECURITY_CALLBACK}
  RPC_C_OPT_UNIQUE_BINDING         = 11;
  {$EXTERNALSYM RPC_C_OPT_UNIQUE_BINDING}
  RPC_C_OPT_CALL_TIMEOUT           = 12;
  {$EXTERNALSYM RPC_C_OPT_CALL_TIMEOUT}
  RPC_C_OPT_DONT_LINGER            = 13;
  {$EXTERNALSYM RPC_C_OPT_DONT_LINGER}
  RPC_C_OPT_MAX_OPTIONS            = 14;
  {$EXTERNALSYM RPC_C_OPT_MAX_OPTIONS}

  RPC_C_MQ_EXPRESS     = 0; // Client: RPC_C_MQ_DELIVERY.
  {$EXTERNALSYM RPC_C_MQ_EXPRESS}
  RPC_C_MQ_RECOVERABLE = 1;
  {$EXTERNALSYM RPC_C_MQ_RECOVERABLE}

  RPC_C_MQ_JOURNAL_NONE       = 0; // Client: RPC_C_MQ_JOURNAL.
  {$EXTERNALSYM RPC_C_MQ_JOURNAL_NONE}
  RPC_C_MQ_JOURNAL_DEADLETTER = 1;
  {$EXTERNALSYM RPC_C_MQ_JOURNAL_DEADLETTER}
  RPC_C_MQ_JOURNAL_ALWAYS     = 2;
  {$EXTERNALSYM RPC_C_MQ_JOURNAL_ALWAYS}

// flags for RpcServerInqAuthClientEx

  RPC_C_FULL_CERT_CHAIN = $0001;
  {$EXTERNALSYM RPC_C_FULL_CERT_CHAIN}

type
  PRPC_PROTSEQ_VECTORA = ^RPC_PROTSEQ_VECTORA;
  {$NODEFINE PRPC_PROTSEQ_VECTORA}
  _RPC_PROTSEQ_VECTORA = record
    Count: Cardinal;
    Protseq: array [0..0] of PByte
  end;
  {$EXTERNALSYM _RPC_PROTSEQ_VECTORA}
  RPC_PROTSEQ_VECTORA = _RPC_PROTSEQ_VECTORA;
  {$EXTERNALSYM RPC_PROTSEQ_VECTORA}
  TRpcProtSeqVectorA = RPC_PROTSEQ_VECTORA;
  PRpcProtSeqVectorA = PRPC_PROTSEQ_VECTORA;

  PRPC_PROTSEQ_VECTORW = ^RPC_PROTSEQ_VECTORW;
  {$NODEFINE PRPC_PROTSEQ_VECTORW}
  _RPC_PROTSEQ_VECTORW = record
    Count: Cardinal;
    Protseq: array [0..0] of PWord;
  end;
  {$EXTERNALSYM _RPC_PROTSEQ_VECTORW}
  RPC_PROTSEQ_VECTORW = _RPC_PROTSEQ_VECTORW;
  {$EXTERNALSYM RPC_PROTSEQ_VECTORW}
  TRpcProtSeqVectorW = RPC_PROTSEQ_VECTORW;
  PRpcProtSeqVectorW = PRPC_PROTSEQ_VECTORW;

{$IFDEF UNICODE}
  RPC_PROTSEQ_VECTOR = RPC_PROTSEQ_VECTORW;
  {$EXTERNALSYM RPC_PROTSEQ_VECTOR}
  TRpcProtSeqVector = TRpcProtSeqVectorW;
  PRpcProtSeqVector = PRpcProtSeqVectorW;
{$ELSE}
  RPC_PROTSEQ_VECTOR = RPC_PROTSEQ_VECTORA;
  {$EXTERNALSYM RPC_PROTSEQ_VECTOR}  
  TRpcProtSeqVector = TRpcProtSeqVectorA;
  PRpcProtSeqVector = PRpcProtSeqVectorA;
{$ENDIF}

  PRPC_POLICY = ^RPC_POLICY;
  {$EXTERNALSYM PRPC_POLICY}
  _RPC_POLICY = record
    Length: Cardinal;
    EndpointFlags: Cardinal;
    NICFlags: Cardinal;
  end;
  {$EXTERNALSYM _RPC_POLICY}
  RPC_POLICY = _RPC_POLICY;
  {$EXTERNALSYM RPC_POLICY}
  TRpcPolicy = RPC_POLICY;
  PRpcPolicy = PRPC_POLICY;

  RPC_OBJECT_INQ_FN = procedure (const ObjectUuid: UUID; var TypeUuid: UUID;
    var Status: RPC_STATUS); stdcall;
  {$EXTERNALSYM RPC_OBJECT_INQ_FN}
  TRpcObjectInqFn = RPC_OBJECT_INQ_FN;

  RPC_IF_CALLBACK_FN = function (InterfaceUuid: RPC_IF_HANDLE; Context: Pointer): RPC_STATUS; stdcall;
  {$EXTERNALSYM RPC_IF_CALLBACK_FN}
  TRpcIfCallbackFn = RPC_IF_CALLBACK_FN;

  RPC_SECURITY_CALLBACK_FN = procedure (Context: Pointer); stdcall;
  {$EXTERNALSYM RPC_SECURITY_CALLBACK_FN}
  TRpcSecurityCallbackFn = RPC_SECURITY_CALLBACK_FN;

  PRPC_STATS_VECTOR = ^RPC_STATS_VECTOR;
  {$NODEFINE PRPC_STATS_VECTOR}
  RPC_STATS_VECTOR = record
    Count: Cardinal;
    Stats: array [0..0] of Cardinal;
  end;
  {$EXTERNALSYM RPC_STATS_VECTOR}
  TRpcStatsVector = RPC_STATS_VECTOR;
  PRpcStatsVector = PRPC_STATS_VECTOR;

const
  RPC_C_STATS_CALLS_IN  = 0;
  {$EXTERNALSYM RPC_C_STATS_CALLS_IN}
  RPC_C_STATS_CALLS_OUT = 1;
  {$EXTERNALSYM RPC_C_STATS_CALLS_OUT}
  RPC_C_STATS_PKTS_IN   = 2;
  {$EXTERNALSYM RPC_C_STATS_PKTS_IN}
  RPC_C_STATS_PKTS_OUT  = 3;
  {$EXTERNALSYM RPC_C_STATS_PKTS_OUT}

type
  PRPC_IF_ID_VECTOR = ^RPC_IF_ID_VECTOR;
  {$NODEFINE RPC_IF_ID_VECTOR}
  RPC_IF_ID_VECTOR = record
    Count: Cardinal;
    IfId: array [0..0] of PRpcIfId;
  end;
  {$EXTERNALSYM RPC_IF_ID_VECTOR}
  TRpcIfIdVector = RPC_IF_ID_VECTOR;
  PRpcIfIdVector = PRPC_IF_ID_VECTOR;

function RpcBindingCopy(SourceBinding: RPC_BINDING_HANDLE;
  var DestinationBinding: RPC_BINDING_HANDLE): RPC_STATUS; stdcall;
{$EXTERNALSYM RpcBindingCopy}

function RpcBindingFree(var Binding: RPC_BINDING_HANDLE): RPC_STATUS; stdcall;
{$EXTERNALSYM RpcBindingFree}

function RpcBindingSetOption(hBinding: RPC_BINDING_HANDLE; option: Cardinal;
  optionValue: ULONG_PTR): RPC_STATUS; stdcall;
{$EXTERNALSYM RpcBindingSetOption}

function RpcBindingInqOption(hBinding: RPC_BINDING_HANDLE; option: Cardinal;
  var pOptionValue: ULONG_PTR): RPC_STATUS; stdcall;
{$EXTERNALSYM RpcBindingInqOption}

function RpcBindingFromStringBindingA(StringBinding: PChar;
  var Binding: RPC_BINDING_HANDLE): RPC_STATUS; stdcall;
{$EXTERNALSYM RpcBindingFromStringBindingA}

function RpcBindingFromStringBindingW(StringBinding: PWideChar;
  var Binding: RPC_BINDING_HANDLE): RPC_STATUS; stdcall;
{$EXTERNALSYM RpcBindingFromStringBindingW}

{$IFDEF UNICODE}
function RpcBindingFromStringBinding(StringBinding: PWideChar;
  var Binding: RPC_BINDING_HANDLE): RPC_STATUS; stdcall;
{$EXTERNALSYM RpcBindingFromStringBinding}
{$ELSE}
function RpcBindingFromStringBinding(StringBinding: PChar;
  var Binding: RPC_BINDING_HANDLE): RPC_STATUS; stdcall;
{$EXTERNALSYM RpcBindingFromStringBinding}
{$ENDIF}

function RpcSsGetContextBinding(ContextHandle: Pointer; var Binding: RPC_BINDING_HANDLE): RPC_STATUS; stdcall;
{$EXTERNALSYM RpcSsGetContextBinding}

function RpcBindingInqObject(Binding: RPC_BINDING_HANDLE; var ObjectUuid: UUID): RPC_STATUS; stdcall;
{$EXTERNALSYM RpcBindingInqObject}

function RpcBindingReset(Binding: RPC_BINDING_HANDLE): RPC_STATUS; stdcall;
{$EXTERNALSYM RpcBindingReset}

// RpcBindingServerFromClient : UNSUPPORTED
// RpcBindingSetAuthInfo

function RpcBindingSetObject(Binding: RPC_BINDING_HANDLE; const ObjectUuid: UUID): RPC_STATUS; stdcall;
{$EXTERNALSYM RpcBindingSetObject}

function RpcMgmtInqDefaultProtectLevel(AuthnSvc: Cardinal; var AuthnLevel: Cardinal): RPC_STATUS; stdcall;
{$EXTERNALSYM RpcMgmtInqDefaultProtectLevel}

function RpcBindingToStringBindingA(Binding: RPC_BINDING_HANDLE;
  var StringBinding: PChar): RPC_STATUS; stdcall;
{$EXTERNALSYM RpcBindingToStringBindingA}

function RpcBindingToStringBindingW(Binding: RPC_BINDING_HANDLE;
  var StringBinding: PWideChar): RPC_STATUS; stdcall;
{$EXTERNALSYM RpcBindingToStringBindingW}

{$IFDEF UNICODE}
function RpcBindingToStringBinding(Binding: RPC_BINDING_HANDLE;
  var StringBinding: PWideChar): RPC_STATUS; stdcall;
{$EXTERNALSYM RpcBindingToStringBinding}
{$ELSE}
function RpcBindingToStringBinding(Binding: RPC_BINDING_HANDLE;
  var StringBinding: PChar): RPC_STATUS; stdcall;
{$EXTERNALSYM RpcBindingToStringBinding}
{$ENDIF}

function RpcBindingVectorFree(var BindingVector: PRPC_BINDING_VECTOR): RPC_STATUS; stdcall;
{$EXTERNALSYM RpcBindingVectorFree}

function RpcStringBindingComposeA(ObjUuid, Protseq, NetworkAddr, Endpoint,
  Options: PChar; var StringBinding: PChar): RPC_STATUS; stdcall;
{$EXTERNALSYM RpcStringBindingComposeA}

function RpcStringBindingComposeW(ObjUuid, Protseq, NetworkAddr, Endpoint,
  Options: PWideChar; var StringBinding: PWideChar): RPC_STATUS; stdcall;
{$EXTERNALSYM RpcStringBindingComposeW}

{$IFDEF UNICODE}
function RpcStringBindingCompose(ObjUuid, Protseq, NetworkAddr, Endpoint,
  Options: PWideChar; var StringBinding: PWideChar): RPC_STATUS; stdcall;
{$EXTERNALSYM RpcStringBindingCompose}
{$ELSE}
function RpcStringBindingCompose(ObjUuid, Protseq, NetworkAddr, Endpoint,
  Options: PChar; var StringBinding: PChar): RPC_STATUS; stdcall;
{$EXTERNALSYM RpcStringBindingCompose}
{$ENDIF}

function RpcStringBindingParseA(StringBinding: PChar; ObjUuid, Protseq,
  NetworkAddr, Endpoint, NetworkOptions: PPChar): RPC_STATUS; stdcall;
{$EXTERNALSYM RpcStringBindingParseA}

function RpcStringBindingParseW(StringBinding: PWideChar; ObjUuid, Protseq,
  NetworkAddr, Endpoint, NetworkOptions: PPWideChar): RPC_STATUS; stdcall;
{$EXTERNALSYM RpcStringBindingParseW}

{$IFDEF UNICODE}
function RpcStringBindingParse(StringBinding: PWideChar; ObjUuid, Protseq,
  NetworkAddr, Endpoint, NetworkOptions: PPWideChar): RPC_STATUS; stdcall;
{$EXTERNALSYM RpcStringBindingParse}
{$ELSE}
function RpcStringBindingParse(StringBinding: PChar; ObjUuid, Protseq,
  NetworkAddr, Endpoint, NetworkOptions: PPChar): RPC_STATUS; stdcall;
{$EXTERNALSYM RpcStringBindingParse}
{$ENDIF}

function RpcStringFreeA(var S: PChar): RPC_STATUS; stdcall;
{$EXTERNALSYM RpcStringFreeA}

function RpcStringFreeW(var S: PWideChar): RPC_STATUS; stdcall;
{$EXTERNALSYM RpcStringFreeW}

{$IFDEF UNICODE}
function RpcStringFree(var S: PWideChar): RPC_STATUS; stdcall;
{$EXTERNALSYM RpcStringFree}
{$ELSE}
function RpcStringFree(var S: PChar): RPC_STATUS; stdcall;
{$EXTERNALSYM RpcStringFree}
{$ENDIF}

function RpcIfInqId(RpcIfHandle: RPC_IF_HANDLE; var RpcIfId: RPC_IF_ID): RPC_STATUS; stdcall;
{$EXTERNALSYM RpcIfInqId}

function RpcNetworkIsProtseqValidA(Protseq: PChar): RPC_STATUS; stdcall;
{$EXTERNALSYM RpcNetworkIsProtseqValidA}

function RpcNetworkIsProtseqValidW(Protseq: PWideChar): RPC_STATUS; stdcall;
{$EXTERNALSYM RpcNetworkIsProtseqValidW}

function RpcMgmtInqComTimeout(Binding: RPC_BINDING_HANDLE; var Timeout: Cardinal): RPC_STATUS; stdcall;
{$EXTERNALSYM RpcMgmtInqComTimeout}

function RpcMgmtSetComTimeout(Binding: RPC_BINDING_HANDLE; Timeout: Cardinal): RPC_STATUS; stdcall;
{$EXTERNALSYM RpcMgmtSetComTimeout}

function RpcMgmtSetCancelTimeout(Timeout: Longint): RPC_STATUS; stdcall;
{$EXTERNALSYM RpcMgmtSetCancelTimeout}

function RpcNetworkInqProtseqsA(var ProtseqVector: PRPC_PROTSEQ_VECTORA): RPC_STATUS; stdcall;
{$EXTERNALSYM RpcNetworkInqProtseqsA}
function RpcNetworkInqProtseqsW(var ProtseqVector: PRPC_PROTSEQ_VECTORW): RPC_STATUS; stdcall;
{$EXTERNALSYM RpcNetworkInqProtseqsW}

{$IFDEF UNICODE}
function RpcNetworkInqProtseqs(var ProtseqVector: PRPC_PROTSEQ_VECTORW): RPC_STATUS; stdcall;
{$EXTERNALSYM RpcNetworkInqProtseqs}
{$ELSE}
function RpcNetworkInqProtseqs(var ProtseqVector: PRPC_PROTSEQ_VECTORA): RPC_STATUS; stdcall;
{$EXTERNALSYM RpcNetworkInqProtseqs}
{$ENDIF}

function RpcObjectInqType(const ObjUuid: UUID; TypeUuid: PUUID): RPC_STATUS; stdcall;
{$EXTERNALSYM RpcObjectInqType}

function RpcObjectSetInqFn(InquiryFn: RPC_OBJECT_INQ_FN): RPC_STATUS; stdcall;
{$EXTERNALSYM RpcObjectSetInqFn}

function RpcObjectSetType(const ObjUuid: UUID; TypeUuid: PUUID): RPC_STATUS; stdcall;
{$EXTERNALSYM RpcObjectSetType}

function RpcProtseqVectorFreeA(var ProtseqVector: PRPC_PROTSEQ_VECTORA): RPC_STATUS; stdcall;
{$EXTERNALSYM RpcProtseqVectorFreeA}
function RpcProtseqVectorFreeW(var ProtseqVector: PRPC_PROTSEQ_VECTORW): RPC_STATUS; stdcall;
{$EXTERNALSYM RpcProtseqVectorFreeW}

{$IFDEF UNICODE}
function RpcProtseqVectorFree(var ProtseqVector: PRPC_PROTSEQ_VECTORW): RPC_STATUS; stdcall;
{$EXTERNALSYM RpcProtseqVectorFree}
{$ELSE}
function RpcProtseqVectorFree(var ProtseqVector: PRPC_PROTSEQ_VECTORA): RPC_STATUS; stdcall;
{$EXTERNALSYM RpcProtseqVectorFree}
{$ENDIF}

function RpcServerInqBindings(var BindingVector: PRPC_BINDING_VECTOR): RPC_STATUS; stdcall;
{$EXTERNALSYM RpcServerInqBindings}

function RpcServerInqIf(IfSpec: RPC_IF_HANDLE; MgrTypeUuid: PUUID;
  MgrEpv: Pointer): RPC_STATUS; stdcall;
{$EXTERNALSYM RpcServerInqIf}

function RpcServerListen(MinimumCallThreads, MaxCalls, DontWait: Cardinal): RPC_STATUS; stdcall;
{$EXTERNALSYM RpcServerListen}

function RpcServerRegisterIf(IfSpec: RPC_IF_HANDLE; MgrTypeUuid: PUUID;
  MgrEpv: Pointer): RPC_STATUS; stdcall;
{$EXTERNALSYM RpcServerRegisterIf}

function RpcServerRegisterIfEx(IfSpec: RPC_IF_HANDLE; MgrTypeUuid: PUUID;
  MgrEpv: Pointer; Flags, MaxCalls: Cardinal; IfCallback: RPC_IF_CALLBACK_FN): RPC_STATUS; stdcall;
{$EXTERNALSYM RpcServerRegisterIfEx}

function RpcServerRegisterIf2(IfSpec: RPC_IF_HANDLE; MgrTypeUuid: PUUID;
  MgrEpv: Pointer; Flags, MaxCalls, MaxRpcSize: Cardinal;
  IfCallbackFn: RPC_IF_CALLBACK_FN): RPC_STATUS; stdcall;
{$EXTERNALSYM RpcServerRegisterIf2}

function RpcServerUnregisterIf(IfSpec: RPC_IF_HANDLE; MgrTypeUuid: PUUID;
  WaitForCallsToComplete: Cardinal): RPC_STATUS; stdcall;
{$EXTERNALSYM RpcServerUnregisterIf}

function RpcServerUnregisterIfEx(IfSpec: RPC_IF_HANDLE; MgrTypeUuid: PUUID;
  RundownContextHandles: Integer): RPC_STATUS; stdcall;
{$EXTERNALSYM RpcServerUnregisterIfEx}

function RpcServerUseAllProtseqs(MaxCalls: Cardinal; SecurityDescriptor: Pointer): RPC_STATUS; stdcall;
{$EXTERNALSYM RpcServerUseAllProtseqs}

function RpcServerUseAllProtseqsEx(MaxCalls: Cardinal; SecurityDescriptor: Pointer;
  Policy: PRPC_POLICY): RPC_STATUS; stdcall;
{$EXTERNALSYM RpcServerUseAllProtseqsEx}

function RpcServerUseAllProtseqsIf(MaxCalls: Cardinal; IfSpec: RPC_IF_HANDLE;
  SecurityDescriptor: Pointer): RPC_STATUS; stdcall;
{$EXTERNALSYM RpcServerUseAllProtseqsIf}

function RpcServerUseAllProtseqsIfEx(MaxCalls: Cardinal; IfSpec: RPC_IF_HANDLE;
  SecurityDescriptor: Pointer; Policy: PRPC_POLICY): RPC_STATUS; stdcall;
{$EXTERNALSYM RpcServerUseAllProtseqsIfEx}

function RpcServerUseProtseqA(Protseq: PChar; MaxCalls: Cardinal;
  SecurityDescriptor: Pointer): RPC_STATUS; stdcall;
{$EXTERNALSYM RpcServerUseProtseqA}
function RpcServerUseProtseqW(Protseq: PWideChar; MaxCalls: Cardinal;
  SecurityDescriptor: Pointer): RPC_STATUS; stdcall;
{$EXTERNALSYM RpcServerUseProtseqW}

{$IFDEF UNICODE}
function RpcServerUseProtseq(Protseq: PWideChar; MaxCalls: Cardinal;
  SecurityDescriptor: Pointer): RPC_STATUS; stdcall;
{$EXTERNALSYM RpcServerUseProtseq}
{$ELSE}
function RpcServerUseProtseq(Protseq: PChar; MaxCalls: Cardinal;
  SecurityDescriptor: Pointer): RPC_STATUS; stdcall;
{$EXTERNALSYM RpcServerUseProtseq}
{$ENDIF}

function RpcServerUseProtseqExA(Protseq: PChar; MaxCalls: Cardinal;
  SecurityDescriptor: Pointer; const Policy: RPC_POLICY): RPC_STATUS; stdcall;
{$EXTERNALSYM RpcServerUseProtseqExA}
function RpcServerUseProtseqExW(Protseq: PWideChar; MaxCalls: Cardinal;
  SecurityDescriptor: Pointer; const Policy: RPC_POLICY): RPC_STATUS; stdcall;
{$EXTERNALSYM RpcServerUseProtseqExW}

{$IFDEF UNICODE}
function RpcServerUseProtseqEx(Protseq: PWideChar; MaxCalls: Cardinal;
  SecurityDescriptor: Pointer; const Policy: RPC_POLICY): RPC_STATUS; stdcall;
{$EXTERNALSYM RpcServerUseProtseqEx}
{$ELSE}
function RpcServerUseProtseqEx(Protseq: PChar; MaxCalls: Cardinal;
  SecurityDescriptor: Pointer; const Policy: RPC_POLICY): RPC_STATUS; stdcall;
{$EXTERNALSYM RpcServerUseProtseqEx}
{$ENDIF}

function RpcServerUseProtseqEpA(Protseq: PChar; MaxCalls: Cardinal;
  Endpoint: PChar; SecurityDescriptor: Pointer): RPC_STATUS; stdcall;
{$EXTERNALSYM RpcServerUseProtseqEpA}
function RpcServerUseProtseqEpW(Protseq: PWideChar; MaxCalls: Cardinal;
  Endpoint: PWideChar; SecurityDescriptor: Pointer): RPC_STATUS; stdcall;
{$EXTERNALSYM RpcServerUseProtseqEpW}

{$IFDEF UNICODE}
function RpcServerUseProtseqEp(Protseq: PWideChar; MaxCalls: Cardinal;
  Endpoint: PWideChar; SecurityDescriptor: Pointer): RPC_STATUS; stdcall;
{$EXTERNALSYM RpcServerUseProtseqEp}
{$ELSE}
function RpcServerUseProtseqEp(Protseq: PChar; MaxCalls: Cardinal;
  Endpoint: PChar; SecurityDescriptor: Pointer): RPC_STATUS; stdcall;
{$EXTERNALSYM RpcServerUseProtseqEp}
{$ENDIF}

function RpcServerUseProtseqEpExA(Protseq: PChar; MaxCalls: Cardinal;
  Endpoint: PChar; SecurityDescriptor: Pointer; const Policy: RPC_POLICY): RPC_STATUS; stdcall;
{$EXTERNALSYM RpcServerUseProtseqEpExA}
function RpcServerUseProtseqEpExW(Protseq: PWideChar; MaxCalls: Cardinal;
  Endpoint: PWideChar; SecurityDescriptor: Pointer; const Policy: RPC_POLICY): RPC_STATUS; stdcall;
{$EXTERNALSYM RpcServerUseProtseqEpExW}

{$IFDEF UNICODE}
function RpcServerUseProtseqEpEx(Protseq: PWideChar; MaxCalls: Cardinal;
  Endpoint: PWideChar; SecurityDescriptor: Pointer; const Policy: RPC_POLICY): RPC_STATUS; stdcall;
{$EXTERNALSYM RpcServerUseProtseqEpEx}
{$ELSE}
function RpcServerUseProtseqEpEx(Protseq: PChar; MaxCalls: Cardinal;
  Endpoint: PChar; SecurityDescriptor: Pointer; const Policy: RPC_POLICY): RPC_STATUS; stdcall;
{$EXTERNALSYM RpcServerUseProtseqEpEx}
{$ENDIF}

function RpcServerUseProtseqIfA(Protseq: PChar; MaxCalls: Cardinal;
  IfSpec: RPC_IF_HANDLE; SecurityDescriptor: Pointer): RPC_STATUS; stdcall;
{$EXTERNALSYM RpcServerUseProtseqIfA}
function RpcServerUseProtseqIfW(Protseq: PWideChar; MaxCalls: Cardinal;
  IfSpec: RPC_IF_HANDLE; SecurityDescriptor: Pointer): RPC_STATUS; stdcall;
{$EXTERNALSYM RpcServerUseProtseqIfW}

function RpcServerUseProtseqIfExA(Protseq: PChar; MaxCalls: Cardinal;
  IfSpec: RPC_IF_HANDLE; SecurityDescriptor: Pointer; const Policy: RPC_POLICY): RPC_STATUS; stdcall;
{$EXTERNALSYM RpcServerUseProtseqIfExA}
function RpcServerUseProtseqIfExW(Protseq: PWideChar; MaxCalls: Cardinal;
  IfSpec: RPC_IF_HANDLE; SecurityDescriptor: Pointer; const Policy: RPC_POLICY): RPC_STATUS; stdcall;
{$EXTERNALSYM RpcServerUseProtseqIfExW}

{$IFDEF UNICODE}
function RpcServerUseProtseqIfEx(Protseq: PWideChar; MaxCalls: Cardinal;
  IfSpec: RPC_IF_HANDLE; SecurityDescriptor: Pointer; const Policy: RPC_POLICY): RPC_STATUS; stdcall;
{$EXTERNALSYM RpcServerUseProtseqIfEx}
{$ELSE}
function RpcServerUseProtseqIfEx(Protseq: PChar; MaxCalls: Cardinal;
  IfSpec: RPC_IF_HANDLE; SecurityDescriptor: Pointer; const Policy: RPC_POLICY): RPC_STATUS; stdcall;
{$EXTERNALSYM RpcServerUseProtseqIfEx}
{$ENDIF}

procedure RpcServerYield; stdcall;
{$EXTERNALSYM RpcServerYield}

function RpcMgmtStatsVectorFree(var StatsVector: PRPC_STATS_VECTOR): RPC_STATUS; stdcall;
{$EXTERNALSYM RpcMgmtStatsVectorFree}

function RpcMgmtInqStats(Binding: RPC_BINDING_HANDLE; var Statistics: PRPC_STATS_VECTOR): RPC_STATUS; stdcall;
{$EXTERNALSYM RpcMgmtInqStats}

function RpcMgmtIsServerListening(Binding: RPC_BINDING_HANDLE): RPC_STATUS; stdcall;
{$EXTERNALSYM RpcMgmtIsServerListening}

function RpcMgmtStopServerListening(Binding: RPC_BINDING_HANDLE): RPC_STATUS; stdcall;
{$EXTERNALSYM RpcMgmtStopServerListening}

function RpcMgmtWaitServerListen: RPC_STATUS; stdcall;
{$EXTERNALSYM RpcMgmtWaitServerListen}

function RpcMgmtSetServerStackSize(ThreadStackSize: Cardinal): RPC_STATUS; stdcall;
{$EXTERNALSYM RpcMgmtSetServerStackSize}

procedure RpcSsDontSerializeContext; stdcall;
{$EXTERNALSYM RpcSsDontSerializeContext}

function RpcMgmtEnableIdleCleanup: RPC_STATUS; stdcall;
{$EXTERNALSYM RpcMgmtEnableIdleCleanup}

function RpcMgmtInqIfIds(Binding: RPC_BINDING_HANDLE;
  var IfIdVector: PRPC_IF_ID_VECTOR): RPC_STATUS; stdcall;
{$EXTERNALSYM RpcMgmtInqIfIds}

function RpcIfIdVectorFree(var IfIdVector: PRPC_IF_ID_VECTOR): RPC_STATUS; stdcall;
{$EXTERNALSYM RpcIfIdVectorFree}

function RpcMgmtInqServerPrincNameA(Binding: RPC_BINDING_HANDLE;
  AuthnSvc: Cardinal; var ServerPrincName: PChar): RPC_STATUS; stdcall;
{$EXTERNALSYM RpcMgmtInqServerPrincNameA}
function RpcMgmtInqServerPrincNameW(Binding: RPC_BINDING_HANDLE;
  AuthnSvc: Cardinal; var ServerPrincName: PWideChar): RPC_STATUS; stdcall;
{$EXTERNALSYM RpcMgmtInqServerPrincNameW}

{$IFDEF UNICODE}
function RpcMgmtInqServerPrincName(Binding: RPC_BINDING_HANDLE;
  AuthnSvc: Cardinal; var ServerPrincName: PWideChar): RPC_STATUS; stdcall;
{$EXTERNALSYM RpcMgmtInqServerPrincName}
{$ELSE}
function RpcMgmtInqServerPrincName(Binding: RPC_BINDING_HANDLE;
  AuthnSvc: Cardinal; var ServerPrincName: PChar): RPC_STATUS; stdcall;
{$EXTERNALSYM RpcMgmtInqServerPrincName}
{$ENDIF}

function RpcServerInqDefaultPrincNameA(AuthnSvc: Cardinal; var PrincName: PChar): RPC_STATUS; stdcall;
{$EXTERNALSYM RpcServerInqDefaultPrincNameA}
function RpcServerInqDefaultPrincNameW(AuthnSvc: Cardinal; var PrincName: PWideChar): RPC_STATUS; stdcall;
{$EXTERNALSYM RpcServerInqDefaultPrincNameW}

{$IFDEF UNICODE}
function RpcServerInqDefaultPrincName(AuthnSvc: Cardinal; var PrincName: PWideChar): RPC_STATUS; stdcall;
{$EXTERNALSYM RpcServerInqDefaultPrincName}
{$ELSE}
function RpcServerInqDefaultPrincName(AuthnSvc: Cardinal; var PrincName: PChar): RPC_STATUS; stdcall;
{$EXTERNALSYM RpcServerInqDefaultPrincName}
{$ENDIF}

function RpcEpResolveBinding(Binding: RPC_BINDING_HANDLE; IfSpe: RPC_IF_HANDLE): RPC_STATUS; stdcall;
{$EXTERNALSYM RpcEpResolveBinding}

function RpcNsBindingInqEntryNameA(Binding: RPC_BINDING_HANDLE;
  EntryNameSyntax: Cardinal; var EntryName: PChar): RPC_STATUS; stdcall;
{$EXTERNALSYM RpcNsBindingInqEntryNameA}
function RpcNsBindingInqEntryNameW(Binding: RPC_BINDING_HANDLE;
  EntryNameSyntax: Cardinal; var EntryName: PWideChar): RPC_STATUS; stdcall;
{$EXTERNALSYM RpcNsBindingInqEntryNameW}

{$IFDEF UNICODE}
function RpcNsBindingInqEntryName(Binding: RPC_BINDING_HANDLE;
  EntryNameSyntax: Cardinal; var EntryName: PWideChar): RPC_STATUS; stdcall;
{$EXTERNALSYM RpcNsBindingInqEntryName}
{$ELSE}
function RpcNsBindingInqEntryName(Binding: RPC_BINDING_HANDLE;
  EntryNameSyntax: Cardinal; var EntryName: PChar): RPC_STATUS; stdcall;
{$EXTERNALSYM RpcNsBindingInqEntryName}
{$ENDIF}

type
  RPC_AUTH_IDENTITY_HANDLE = Pointer;
  {$EXTERNALSYM RPC_AUTH_IDENTITY_HANDLE}
  RPC_AUTHZ_HANDLE = Pointer;
  {$EXTERNALSYM RPC_AUTHZ_HANDLE}
  PRPC_AUTHZ_HANDLE = ^RPC_AUTHZ_HANDLE;
  {$NODEFINE PRPC_AUTHZ_HANDLE}

  PRPC_AUTH_IDENTITY_HANDLE = ^RPC_AUTH_IDENTITY_HANDLE;
  {$NODEFINE PRPC_AUTH_IDENTITY_HANDLE}

const
  RPC_C_AUTHN_LEVEL_DEFAULT       = 0;
  {$EXTERNALSYM RPC_C_AUTHN_LEVEL_DEFAULT}
  RPC_C_AUTHN_LEVEL_NONE          = 1;
  {$EXTERNALSYM RPC_C_AUTHN_LEVEL_NONE}
  RPC_C_AUTHN_LEVEL_CONNECT       = 2;
  {$EXTERNALSYM RPC_C_AUTHN_LEVEL_CONNECT}
  RPC_C_AUTHN_LEVEL_CALL          = 3;
  {$EXTERNALSYM RPC_C_AUTHN_LEVEL_CALL}
  RPC_C_AUTHN_LEVEL_PKT           = 4;
  {$EXTERNALSYM RPC_C_AUTHN_LEVEL_PKT}
  RPC_C_AUTHN_LEVEL_PKT_INTEGRITY = 5;
  {$EXTERNALSYM RPC_C_AUTHN_LEVEL_PKT_INTEGRITY}
  RPC_C_AUTHN_LEVEL_PKT_PRIVACY   = 6;
  {$EXTERNALSYM RPC_C_AUTHN_LEVEL_PKT_PRIVACY}

  RPC_C_IMP_LEVEL_DEFAULT     = 0;
  {$EXTERNALSYM RPC_C_IMP_LEVEL_DEFAULT}
  RPC_C_IMP_LEVEL_ANONYMOUS   = 1;
  {$EXTERNALSYM RPC_C_IMP_LEVEL_ANONYMOUS}
  RPC_C_IMP_LEVEL_IDENTIFY    = 2;
  {$EXTERNALSYM RPC_C_IMP_LEVEL_IDENTIFY}
  RPC_C_IMP_LEVEL_IMPERSONATE = 3;
  {$EXTERNALSYM RPC_C_IMP_LEVEL_IMPERSONATE}
  RPC_C_IMP_LEVEL_DELEGATE    = 4;
  {$EXTERNALSYM RPC_C_IMP_LEVEL_DELEGATE}

  RPC_C_QOS_IDENTITY_STATIC  = 0;
  {$EXTERNALSYM RPC_C_QOS_IDENTITY_STATIC}
  RPC_C_QOS_IDENTITY_DYNAMIC = 1;
  {$EXTERNALSYM RPC_C_QOS_IDENTITY_DYNAMIC}

  RPC_C_QOS_CAPABILITIES_DEFAULT                      = $0;
  {$EXTERNALSYM RPC_C_QOS_CAPABILITIES_DEFAULT}
  RPC_C_QOS_CAPABILITIES_MUTUAL_AUTH                  = $1;
  {$EXTERNALSYM RPC_C_QOS_CAPABILITIES_MUTUAL_AUTH}
  RPC_C_QOS_CAPABILITIES_MAKE_FULLSIC                 = $2;
  {$EXTERNALSYM RPC_C_QOS_CAPABILITIES_MAKE_FULLSIC}
  RPC_C_QOS_CAPABILITIES_ANY_AUTHORITY                = $4;
  {$EXTERNALSYM RPC_C_QOS_CAPABILITIES_ANY_AUTHORITY}
  RPC_C_QOS_CAPABILITIES_IGNORE_DELEGATE_FAILURE      = $8;
  {$EXTERNALSYM RPC_C_QOS_CAPABILITIES_IGNORE_DELEGATE_FAILURE}
  RPC_C_QOS_CAPABILITIES_LOCAL_MA_HINT                = $10;
  {$EXTERNALSYM RPC_C_QOS_CAPABILITIES_LOCAL_MA_HINT}

  RPC_C_PROTECT_LEVEL_DEFAULT       = (RPC_C_AUTHN_LEVEL_DEFAULT);
  {$EXTERNALSYM RPC_C_PROTECT_LEVEL_DEFAULT}
  RPC_C_PROTECT_LEVEL_NONE          = (RPC_C_AUTHN_LEVEL_NONE);
  {$EXTERNALSYM RPC_C_PROTECT_LEVEL_NONE}
  RPC_C_PROTECT_LEVEL_CONNECT       = (RPC_C_AUTHN_LEVEL_CONNECT);
  {$EXTERNALSYM RPC_C_PROTECT_LEVEL_CONNECT}
  RPC_C_PROTECT_LEVEL_CALL          = (RPC_C_AUTHN_LEVEL_CALL);
  {$EXTERNALSYM RPC_C_PROTECT_LEVEL_CALL}
  RPC_C_PROTECT_LEVEL_PKT           = (RPC_C_AUTHN_LEVEL_PKT);
  {$EXTERNALSYM RPC_C_PROTECT_LEVEL_PKT}
  RPC_C_PROTECT_LEVEL_PKT_INTEGRITY = (RPC_C_AUTHN_LEVEL_PKT_INTEGRITY);
  {$EXTERNALSYM RPC_C_PROTECT_LEVEL_PKT_INTEGRITY}
  RPC_C_PROTECT_LEVEL_PKT_PRIVACY   = (RPC_C_AUTHN_LEVEL_PKT_PRIVACY);
  {$EXTERNALSYM RPC_C_PROTECT_LEVEL_PKT_PRIVACY}

  RPC_C_AUTHN_NONE          = 0;
  {$EXTERNALSYM RPC_C_AUTHN_NONE}
  RPC_C_AUTHN_DCE_PRIVATE   = 1;
  {$EXTERNALSYM RPC_C_AUTHN_DCE_PRIVATE}
  RPC_C_AUTHN_DCE_PUBLIC    = 2;
  {$EXTERNALSYM RPC_C_AUTHN_DCE_PUBLIC}
  RPC_C_AUTHN_DEC_PUBLIC    = 4;
  {$EXTERNALSYM RPC_C_AUTHN_DEC_PUBLIC}
  RPC_C_AUTHN_GSS_NEGOTIATE = 9;
  {$EXTERNALSYM RPC_C_AUTHN_GSS_NEGOTIATE}
  RPC_C_AUTHN_WINNT         = 10;
  {$EXTERNALSYM RPC_C_AUTHN_WINNT}
  RPC_C_AUTHN_GSS_SCHANNEL  = 14;
  {$EXTERNALSYM RPC_C_AUTHN_GSS_SCHANNEL}
  RPC_C_AUTHN_GSS_KERBEROS  = 16;
  {$EXTERNALSYM RPC_C_AUTHN_GSS_KERBEROS}
  RPC_C_AUTHN_DPA           = 17;
  {$EXTERNALSYM RPC_C_AUTHN_DPA}
  RPC_C_AUTHN_MSN           = 18;
  {$EXTERNALSYM RPC_C_AUTHN_MSN}
  RPC_C_AUTHN_DIGEST        = 21;
  {$EXTERNALSYM RPC_C_AUTHN_DIGEST}
  RPC_C_AUTHN_MQ            = 100;
  {$EXTERNALSYM RPC_C_AUTHN_MQ}
  RPC_C_AUTHN_DEFAULT       = DWORD($FFFFFFFF);
  {$EXTERNALSYM RPC_C_AUTHN_DEFAULT}

  RPC_C_NO_CREDENTIALS = RPC_AUTH_IDENTITY_HANDLE(MAXUINT_PTR);
  {$EXTERNALSYM RPC_C_NO_CREDENTIALS}

  RPC_C_SECURITY_QOS_VERSION = 1;
  {$EXTERNALSYM RPC_C_SECURITY_QOS_VERSION}
  RPC_C_SECURITY_QOS_VERSION_1 = 1;
  {$EXTERNALSYM RPC_C_SECURITY_QOS_VERSION_1}

type
  _RPC_SECURITY_QOS = record
    Version: Longint;
    Capabilities: Longint;
    IdentityTracking: Longint;
    ImpersonationType: Longint;
  end;
  {$EXTERNALSYM _RPC_SECURITY_QOS}
  RPC_SECURITY_QOS = _RPC_SECURITY_QOS;
  {$EXTERNALSYM RPC_SECURITY_QOS}
  PRPC_SECURITY_QOS = ^RPC_SECURITY_QOS;
  {$EXTERNALSYM PRPC_SECURITY_QOS}
  TRpcSecurityQos = RPC_SECURITY_QOS;
  PRpcSecurityQos = PRPC_SECURITY_QOS;

const
  SEC_WINNT_AUTH_IDENTITY_ANSI    = $1;
  {$EXTERNALSYM SEC_WINNT_AUTH_IDENTITY_ANSI}
  SEC_WINNT_AUTH_IDENTITY_UNICODE = $2;
  {$EXTERNALSYM SEC_WINNT_AUTH_IDENTITY_UNICODE}

type
  _SEC_WINNT_AUTH_IDENTITY_W = record
    User: PWideChar;
    UserLength: Longint;
    Domain: PWideChar;
    DomainLength: Longint;
    Password: PWideChar;
    PasswordLength: Longint;
    Flags: Longint;
  end;
  {$EXTERNALSYM _SEC_WINNT_AUTH_IDENTITY_W}
  SEC_WINNT_AUTH_IDENTITY_W = _SEC_WINNT_AUTH_IDENTITY_W;
  {$EXTERNALSYM SEC_WINNT_AUTH_IDENTITY_W}
  PSEC_WINNT_AUTH_IDENTITY_W = ^SEC_WINNT_AUTH_IDENTITY_W;
  {$EXTERNALSYM PSEC_WINNT_AUTH_IDENTITY_W}
  TSecWinNTAuthIdentityW = SEC_WINNT_AUTH_IDENTITY_W;
  PSecWinNTAuthIdentityW = PSEC_WINNT_AUTH_IDENTITY_W;

  _SEC_WINNT_AUTH_IDENTITY_A = record
    User: PChar;
    UserLength: Longint;
    Domain: PChar;
    DomainLength: Longint;
    Password: PChar;
    PasswordLength: Longint;
    Flags: Longint;
  end;
  {$EXTERNALSYM _SEC_WINNT_AUTH_IDENTITY_A}
  SEC_WINNT_AUTH_IDENTITY_A = _SEC_WINNT_AUTH_IDENTITY_A;
  {$EXTERNALSYM SEC_WINNT_AUTH_IDENTITY_A}
  PSEC_WINNT_AUTH_IDENTITY_A = ^SEC_WINNT_AUTH_IDENTITY_A;
  {$EXTERNALSYM PSEC_WINNT_AUTH_IDENTITY_A}
  TSecWinNTAuthIdentityA = SEC_WINNT_AUTH_IDENTITY_A;
  PSecWinNTAuthIdentityA = PSEC_WINNT_AUTH_IDENTITY_A;

{$IFDEF UNICODE}
  SEC_WINNT_AUTH_IDENTITY = SEC_WINNT_AUTH_IDENTITY_W;
  {$EXTERNALSYM SEC_WINNT_AUTH_IDENTITY}
  PSEC_WINNT_AUTH_IDENTITY = PSEC_WINNT_AUTH_IDENTITY_W;
  {$EXTERNALSYM PSEC_WINNT_AUTH_IDENTITY}
  _SEC_WINNT_AUTH_IDENTITY = _SEC_WINNT_AUTH_IDENTITY_W;
  {$EXTERNALSYM _SEC_WINNT_AUTH_IDENTITY}
  TSecWinNTAuthIdentity = TSecWinNTAuthIdentityW;
  PSecWinNTAuthIdentity = PSecWinNTAuthIdentityW;
{$ELSE}
  SEC_WINNT_AUTH_IDENTITY = SEC_WINNT_AUTH_IDENTITY_A;
  {$EXTERNALSYM SEC_WINNT_AUTH_IDENTITY}
  PSEC_WINNT_AUTH_IDENTITY = PSEC_WINNT_AUTH_IDENTITY_A;
  {$EXTERNALSYM PSEC_WINNT_AUTH_IDENTITY}
  _SEC_WINNT_AUTH_IDENTITY = _SEC_WINNT_AUTH_IDENTITY_A;
  {$EXTERNALSYM _SEC_WINNT_AUTH_IDENTITY}
  TSecWinNTAuthIdentity = TSecWinNTAuthIdentityA;
  PSecWinNTAuthIdentity = PSecWinNTAuthIdentityA;
{$ENDIF}

const
  RPC_C_SECURITY_QOS_VERSION_2 = 2;
  {$EXTERNALSYM RPC_C_SECURITY_QOS_VERSION_2}

  RPC_C_AUTHN_INFO_TYPE_HTTP                 = 1;
  {$EXTERNALSYM RPC_C_AUTHN_INFO_TYPE_HTTP}

  RPC_C_HTTP_AUTHN_TARGET_SERVER             = 1;
  {$EXTERNALSYM RPC_C_HTTP_AUTHN_TARGET_SERVER}
  RPC_C_HTTP_AUTHN_TARGET_PROXY              = 2;
  {$EXTERNALSYM RPC_C_HTTP_AUTHN_TARGET_PROXY}

  RPC_C_HTTP_AUTHN_SCHEME_BASIC     = $00000001;
  {$EXTERNALSYM RPC_C_HTTP_AUTHN_SCHEME_BASIC}
  RPC_C_HTTP_AUTHN_SCHEME_NTLM      = $00000002;
  {$EXTERNALSYM RPC_C_HTTP_AUTHN_SCHEME_NTLM}
  RPC_C_HTTP_AUTHN_SCHEME_PASSPORT  = $00000004;
  {$EXTERNALSYM RPC_C_HTTP_AUTHN_SCHEME_PASSPORT}
  RPC_C_HTTP_AUTHN_SCHEME_DIGEST    = $00000008;
  {$EXTERNALSYM RPC_C_HTTP_AUTHN_SCHEME_DIGEST}
  RPC_C_HTTP_AUTHN_SCHEME_NEGOTIATE = $00000010;
  {$EXTERNALSYM RPC_C_HTTP_AUTHN_SCHEME_NEGOTIATE}

  RPC_C_HTTP_FLAG_USE_SSL                    = 1;
  {$EXTERNALSYM RPC_C_HTTP_FLAG_USE_SSL}
  RPC_C_HTTP_FLAG_USE_FIRST_AUTH_SCHEME      = 2;
  {$EXTERNALSYM RPC_C_HTTP_FLAG_USE_FIRST_AUTH_SCHEME}

type
  _RPC_HTTP_TRANSPORT_CREDENTIALS_W = record
    TransportCredentials: PSEC_WINNT_AUTH_IDENTITY_W;
    Flags: Cardinal;
    AuthenticationTarget: Cardinal;
    NumberOfAuthnSchemes: Cardinal;
    AuthnSchemes: PCardinal;
    ServerCertificateSubject: PWord;
  end;
  {$EXTERNALSYM RPC_HTTP_TRANSPORT_CREDENTIALS_W}
  RPC_HTTP_TRANSPORT_CREDENTIALS_W = _RPC_HTTP_TRANSPORT_CREDENTIALS_W;
  {$EXTERNALSYM RPC_HTTP_TRANSPORT_CREDENTIALS_W}
  PRPC_HTTP_TRANSPORT_CREDENTIALS_W = ^RPC_HTTP_TRANSPORT_CREDENTIALS_W;
  {$EXTERNALSYM PRPC_HTTP_TRANSPORT_CREDENTIALS_W}
  TRpcHttpTransportCredentialsW = RPC_HTTP_TRANSPORT_CREDENTIALS_W;
  PRpcHttpTransportCredentialsW = PRPC_HTTP_TRANSPORT_CREDENTIALS_W;

  _RPC_HTTP_TRANSPORT_CREDENTIALS_A = record
    TransportCredentials: PSEC_WINNT_AUTH_IDENTITY_A;
    Flags: Cardinal;
    AuthenticationTarget: Cardinal;
    NumberOfAuthnSchemes: Cardinal;
    AuthnSchemes: PCardinal;
    ServerCertificateSubject: PByte;
  end;
  {$EXTERNALSYM RPC_HTTP_TRANSPORT_CREDENTIALS_A}
  RPC_HTTP_TRANSPORT_CREDENTIALS_A = _RPC_HTTP_TRANSPORT_CREDENTIALS_A;
  {$EXTERNALSYM RPC_HTTP_TRANSPORT_CREDENTIALS_A}
  PRPC_HTTP_TRANSPORT_CREDENTIALS_A = ^RPC_HTTP_TRANSPORT_CREDENTIALS_A;
  {$EXTERNALSYM PRPC_HTTP_TRANSPORT_CREDENTIALS_A}
  TRpcHttpTransportCredentialsA = RPC_HTTP_TRANSPORT_CREDENTIALS_A;
  PRpcHttpTransportCredentialsA = PRPC_HTTP_TRANSPORT_CREDENTIALS_A;

  _RPC_SECURITY_QOS_V2_W = record
    Version: Cardinal;
    Capabilities: Cardinal;
    IdentityTracking: Cardinal;
    ImpersonationType: Cardinal;
    AdditionalSecurityInfoType: Cardinal;
    case Integer of
      0: (HttpCredentials: PRPC_HTTP_TRANSPORT_CREDENTIALS_W);
  end;
  {$EXTERNALSYM _RPC_SECURITY_QOS_V2_W}
  RPC_SECURITY_QOS_V2_W = _RPC_SECURITY_QOS_V2_W;
  {$EXTERNALSYM RPC_SECURITY_QOS_V2_W}
  PRPC_SECURITY_QOS_V2_W = ^RPC_SECURITY_QOS_V2_W;
  {$EXTERNALSYM PRPC_SECURITY_QOS_V2_W}
  TRpcSecurityQosV2W = RPC_SECURITY_QOS_V2_W;
  PRpcSecurityQosV2W = PRPC_SECURITY_QOS_V2_W;  

  _RPC_SECURITY_QOS_V2_A = record
    Version: Cardinal;
    Capabilities: Cardinal;
    IdentityTracking: Cardinal;
    ImpersonationType: Cardinal;
    AdditionalSecurityInfoType: Cardinal;
    case Integer of
      0: (HttpCredentials: PRPC_HTTP_TRANSPORT_CREDENTIALS_A);
  end;
  {$EXTERNALSYM _RPC_SECURITY_QOS_V2_A}
  RPC_SECURITY_QOS_V2_A = _RPC_SECURITY_QOS_V2_A;
  {$EXTERNALSYM RPC_SECURITY_QOS_V2_A}
  PRPC_SECURITY_QOS_V2_A = ^RPC_SECURITY_QOS_V2_A;
  {$EXTERNALSYM PRPC_SECURITY_QOS_V2_A}
  TRpcSecurityQosV2A = RPC_SECURITY_QOS_V2_A;
  PRpcSecurityQosV2A = PRPC_SECURITY_QOS_V2_A;

const
  RPC_C_SECURITY_QOS_VERSION_3 = 3;
  {$EXTERNALSYM RPC_C_SECURITY_QOS_VERSION_3}

type
  _RPC_SECURITY_QOS_V3_W = record
    Version: Cardinal;
    Capabilities: Cardinal;
    IdentityTracking: Cardinal;
    ImpersonationType: Cardinal;
    AdditionalSecurityInfoType: Cardinal;
    u: record
    case Integer of
      0: (HttpCredentials: PRPC_HTTP_TRANSPORT_CREDENTIALS_W);
    end;
    Sid: Pointer;
  end;
  {$EXTERNALSYM _RPC_SECURITY_QOS_V3_W}
  RPC_SECURITY_QOS_V3_W = _RPC_SECURITY_QOS_V3_W;
  {$EXTERNALSYM RPC_SECURITY_QOS_V3_W}
  PRPC_SECURITY_QOS_V3_W = ^RPC_SECURITY_QOS_V3_W;
  {$EXTERNALSYM PRPC_SECURITY_QOS_V3_W}
  TRpcSecurityQosV3W = RPC_SECURITY_QOS_V3_W;
  PRpcSecurityQosV3W = PRPC_SECURITY_QOS_V3_W;

  _RPC_SECURITY_QOS_V3_A = record
    Version: Cardinal;
    Capabilities: Cardinal;
    IdentityTracking: Cardinal;
    ImpersonationType: Cardinal;
    AdditionalSecurityInfoType: Cardinal;
    u: record
    case Integer of
      0: (HttpCredentials: PRPC_HTTP_TRANSPORT_CREDENTIALS_A);
    end;
    Sid: Pointer;
  end;
  {$EXTERNALSYM _RPC_SECURITY_QOS_V3_A}
  RPC_SECURITY_QOS_V3_A = _RPC_SECURITY_QOS_V3_A;
  {$EXTERNALSYM RPC_SECURITY_QOS_V3_A}
  PRPC_SECURITY_QOS_V3_A = ^RPC_SECURITY_QOS_V3_A;
  {$EXTERNALSYM PRPC_SECURITY_QOS_V3_A}
  TRpcSecurityQosV3A = RPC_SECURITY_QOS_V3_A;
  PRpcSecurityQosV3A = PRPC_SECURITY_QOS_V3_A;

{$IFDEF UNICODE}

  RPC_SECURITY_QOS_V2 = RPC_SECURITY_QOS_V2_W;
  {$EXTERNALSYM RPC_SECURITY_QOS_V2}
  PRPC_SECURITY_QOS_V2 = PRPC_SECURITY_QOS_V2_W;
  {$EXTERNALSYM PRPC_SECURITY_QOS_V2}
  _RPC_SECURITY_QOS_V2 = _RPC_SECURITY_QOS_V2_W;
  {$EXTERNALSYM _RPC_SECURITY_QOS_V2}
  TRpcSecurityQosV2 = TRpcSecurityQosV2W;
  PRpcSecurityQosV2 = PRpcSecurityQosV2W;

  RPC_HTTP_TRANSPORT_CREDENTIALS = RPC_HTTP_TRANSPORT_CREDENTIALS_W;
  {$EXTERNALSYM RPC_HTTP_TRANSPORT_CREDENTIALS}
  PRPC_HTTP_TRANSPORT_CREDENTIALS = PRPC_HTTP_TRANSPORT_CREDENTIALS_W;
  {$EXTERNALSYM PRPC_HTTP_TRANSPORT_CREDENTIALS}
  _RPC_HTTP_TRANSPORT_CREDENTIALS = _RPC_HTTP_TRANSPORT_CREDENTIALS_W;
  {$EXTERNALSYM _RPC_HTTP_TRANSPORT_CREDENTIALS}
  TRpcHttpTransportCredentials = TRpcHttpTransportCredentialsW;
  PRpcHttpTransportCredentials = PRpcHttpTransportCredentialsW;

  RPC_SECURITY_QOS_V3 = RPC_SECURITY_QOS_V3_W;
  {$EXTERNALSYM RPC_SECURITY_QOS_V3}
  PRPC_SECURITY_QOS_V3 = PRPC_SECURITY_QOS_V3_W;
  {$EXTERNALSYM PRPC_SECURITY_QOS_V3}
  _RPC_SECURITY_QOS_V3 = _RPC_SECURITY_QOS_V3_W;
  {$EXTERNALSYM _RPC_SECURITY_QOS_V3}
  TRpcSecurityQosV3 = TRpcSecurityQosV3W;
  PRpcSecurityQosV3 = PRpcSecurityQosV3W;

{$ELSE}

  RPC_SECURITY_QOS_V2 = RPC_SECURITY_QOS_V2_A;
  {$EXTERNALSYM RPC_SECURITY_QOS_V2}
  PRPC_SECURITY_QOS_V2 = PRPC_SECURITY_QOS_V2_A;
  {$EXTERNALSYM PRPC_SECURITY_QOS_V2}
  _RPC_SECURITY_QOS_V2 = _RPC_SECURITY_QOS_V2_A;
  {$EXTERNALSYM _RPC_SECURITY_QOS_V2}
  TRpcSecurityQosV2 = TRpcSecurityQosV2A;
  PRpcSecurityQosV2 = PRpcSecurityQosV2A;

  RPC_HTTP_TRANSPORT_CREDENTIALS = RPC_HTTP_TRANSPORT_CREDENTIALS_A;
  {$EXTERNALSYM RPC_HTTP_TRANSPORT_CREDENTIALS}
  PRPC_HTTP_TRANSPORT_CREDENTIALS = PRPC_HTTP_TRANSPORT_CREDENTIALS_A;
  {$EXTERNALSYM PRPC_HTTP_TRANSPORT_CREDENTIALS}
  _RPC_HTTP_TRANSPORT_CREDENTIALS = _RPC_HTTP_TRANSPORT_CREDENTIALS_A;
  {$EXTERNALSYM _RPC_HTTP_TRANSPORT_CREDENTIALS}
  TRpcHttpTransportCredentials = TRpcHttpTransportCredentialsA;
  PRpcHttpTransportCredentials = PRpcHttpTransportCredentialsA;

  RPC_SECURITY_QOS_V3 = RPC_SECURITY_QOS_V3_A;
  {$EXTERNALSYM RPC_SECURITY_QOS_V3}
  PRPC_SECURITY_QOS_V3 = PRPC_SECURITY_QOS_V3_A;
  {$EXTERNALSYM PRPC_SECURITY_QOS_V3}
  _RPC_SECURITY_QOS_V3 = _RPC_SECURITY_QOS_V3_A;
  {$EXTERNALSYM _RPC_SECURITY_QOS_V3}
  TRpcSecurityQosV3 = TRpcSecurityQosV3A;
  PRpcSecurityQosV3 = PRpcSecurityQosV3A;

{$ENDIF}

type
  RPC_NEW_HTTP_PROXY_CHANNEL = function (ServerName: PWideChar; ServerPort: PWord; RemoteUser: PByte; out NewServerName: PWord): RPC_STATUS; stdcall;
  {$EXTERNALSYM RPC_NEW_HTTP_PROXY_CHANNEL}

  RPC_HTTP_PROXY_FREE_STRING = procedure (ServerName: PWideChar); stdcall;
  {$EXTERNALSYM RPC_HTTP_PROXY_FREE_STRING}

const
  RPC_C_AUTHZ_NONE    = 0;
  {$EXTERNALSYM RPC_C_AUTHZ_NONE}
  RPC_C_AUTHZ_NAME    = 1;
  {$EXTERNALSYM RPC_C_AUTHZ_NAME}
  RPC_C_AUTHZ_DCE     = 2;
  {$EXTERNALSYM RPC_C_AUTHZ_DCE}
  RPC_C_AUTHZ_DEFAULT = DWORD($ffffffff);
  {$EXTERNALSYM RPC_C_AUTHZ_DEFAULT}

function RpcImpersonateClient(BindingHandle: RPC_BINDING_HANDLE): RPC_STATUS; stdcall;
{$EXTERNALSYM RpcImpersonateClient}

function RpcRevertToSelfEx(BindingHandle: RPC_BINDING_HANDLE): RPC_STATUS; stdcall;
{$EXTERNALSYM RpcRevertToSelfEx}

function RpcRevertToSelf: RPC_STATUS; stdcall;
{$EXTERNALSYM RpcRevertToSelf}

function RpcBindingInqAuthClientA(ClientBinding: RPC_BINDING_HANDLE;
  Privs: PRPC_AUTHZ_HANDLE; ServerPrincName: PPChar; AuthnLevel, AuthnSvc,
  AuthzSvc: PCardinal): RPC_STATUS; stdcall;
{$EXTERNALSYM RpcBindingInqAuthClientA}
function RpcBindingInqAuthClientW(ClientBinding: RPC_BINDING_HANDLE;
  Privs: PRPC_AUTHZ_HANDLE; ServerPrincName: PPWideChar; AuthnLevel, AuthnSvc,
  AuthzSvc: PCardinal): RPC_STATUS; stdcall;
{$EXTERNALSYM RpcBindingInqAuthClientW}

function RpcBindingInqAuthClientExA(ClientBinding: RPC_BINDING_HANDLE;
  Privs: PRPC_AUTHZ_HANDLE; ServerPrincName: PPChar; AuthnLevel, AuthnSvc,
  AuthzSvc: PCardinal; Flags: Cardinal): RPC_STATUS; stdcall;
{$EXTERNALSYM RpcBindingInqAuthClientExA}
function RpcBindingInqAuthClientExW(ClientBinding: RPC_BINDING_HANDLE;
  Privs: PRPC_AUTHZ_HANDLE; ServerPrincName: PPWideChar; AuthnLevel, AuthnSvc,
  AuthzSvc: PCardinal; Flags: Cardinal): RPC_STATUS; stdcall;
{$EXTERNALSYM RpcBindingInqAuthClientExW}

function RpcBindingInqAuthInfoA(Binding: RPC_BINDING_HANDLE; ServerPrincName: PPChar;
  AuthnLevel, AuthnSvc: PCardinal; AuthIdentity: PRPC_AUTH_IDENTITY_HANDLE;
  AuthzSvc: PCardinal): RPC_STATUS; stdcall;
{$EXTERNALSYM RpcBindingInqAuthInfoA}
function RpcBindingInqAuthInfoW(Binding: RPC_BINDING_HANDLE; ServerPrincName: PPWideChar;
  AuthnLevel, AuthnSvc: PCardinal; AuthIdentity: PRPC_AUTH_IDENTITY_HANDLE;
  AuthzSvc: PCardinal): RPC_STATUS; stdcall;
{$EXTERNALSYM RpcBindingInqAuthInfoW}

function RpcBindingSetAuthInfoA(Binding: RPC_BINDING_HANDLE; ServerPrincName: PChar;
  AuthnLevel, AuthnSvc: Cardinal; AuthIdentity: RPC_AUTH_IDENTITY_HANDLE;
  AuthzSvc: Cardinal): RPC_STATUS; stdcall;
{$EXTERNALSYM RpcBindingSetAuthInfoA}
function RpcBindingSetAuthInfoW(Binding: RPC_BINDING_HANDLE; ServerPrincName: PWideChar;
  AuthnLevel, AuthnSvc: Cardinal; AuthIdentity: RPC_AUTH_IDENTITY_HANDLE;
  AuthzSvc: Cardinal): RPC_STATUS; stdcall;
{$EXTERNALSYM RpcBindingSetAuthInfoW}

function RpcBindingSetAuthInfoExA(Binding: RPC_BINDING_HANDLE;
  ServerPrincName: PChar; AuthnLevel, AuthnSvc: Cardinal;
  AuthIdentity: RPC_AUTH_IDENTITY_HANDLE; AuthzSvc: Cardinal;
  const SecurityQOS: RPC_SECURITY_QOS): RPC_STATUS; stdcall;
{$EXTERNALSYM RpcBindingSetAuthInfoExA}
function RpcBindingSetAuthInfoExW(Binding: RPC_BINDING_HANDLE;
  ServerPrincName: PWideChar; AuthnLevel, AuthnSvc: Cardinal;
  AuthIdentity: RPC_AUTH_IDENTITY_HANDLE; AuthzSvc: Cardinal;
  const SecurityQOS: RPC_SECURITY_QOS): RPC_STATUS; stdcall;
{$EXTERNALSYM RpcBindingSetAuthInfoExW}

function RpcBindingInqAuthInfoExA(Binding: RPC_BINDING_HANDLE;
  ServerPrincName: PPChar; AuthnLevel, AuthnSvc: PCardinal;
  AuthIdentity: PRPC_AUTH_IDENTITY_HANDLE; AuthzSvc: PCardinal;
  RpcQosVersion: Cardinal; var SecurityQOS: RPC_SECURITY_QOS): RPC_STATUS; stdcall;
{$EXTERNALSYM RpcBindingInqAuthInfoExA}
function RpcBindingInqAuthInfoExW(Binding: RPC_BINDING_HANDLE;
  ServerPrincName: PPWideChar; AuthnLevel, AuthnSvc: PCardinal;
  AuthIdentity: PRPC_AUTH_IDENTITY_HANDLE; AuthzSvc: PCardinal;
  RpcQosVersion: Cardinal; var SecurityQOS: RPC_SECURITY_QOS): RPC_STATUS; stdcall;
{$EXTERNALSYM RpcBindingInqAuthInfoExW}

type
  RPC_AUTH_KEY_RETRIEVAL_FN = procedure (Arg: Pointer; ServerPrincName: PWideChar;
    KeyVer: Cardinal; var Key: Pointer; var Status: RPC_STATUS); stdcall;
  {$EXTERNALSYM RPC_AUTH_KEY_RETRIEVAL_FN}
  TRpcAuthKeyRetrievalFn = RPC_AUTH_KEY_RETRIEVAL_FN;

function RpcServerRegisterAuthInfoA(ServerPrincName: PChar; AuthnSvc: Cardinal;
  GetKeyFn: RPC_AUTH_KEY_RETRIEVAL_FN; Arg: Pointer): RPC_STATUS; stdcall;
{$EXTERNALSYM RpcServerRegisterAuthInfoA}
function RpcServerRegisterAuthInfoW(ServerPrincName: PWideChar; AuthnSvc: Cardinal;
  GetKeyFn: RPC_AUTH_KEY_RETRIEVAL_FN; Arg: Pointer): RPC_STATUS; stdcall;
{$EXTERNALSYM RpcServerRegisterAuthInfoW}

{$IFDEF UNICODE}
function RpcBindingInqAuthClient(ClientBinding: RPC_BINDING_HANDLE;
  Privs: PRPC_AUTHZ_HANDLE; ServerPrincName: PPWideChar; AuthnLevel, AuthnSvc,
  AuthzSvc: PCardinal): RPC_STATUS; stdcall;
{$EXTERNALSYM RpcBindingInqAuthClient}
function RpcBindingInqAuthClientEx(ClientBinding: RPC_BINDING_HANDLE;
  Privs: PRPC_AUTHZ_HANDLE; ServerPrincName: PPWideChar; AuthnLevel, AuthnSvc,
  AuthzSvc: PCardinal; Flags: Cardinal): RPC_STATUS; stdcall;
{$EXTERNALSYM RpcBindingInqAuthClientEx}
function RpcBindingInqAuthInfo(Binding: RPC_BINDING_HANDLE; ServerPrincName: PPWideChar;
  AuthnLevel, AuthnSvc: PCardinal; AuthIdentity: PRPC_AUTH_IDENTITY_HANDLE;
  AuthzSvc: PCardinal): RPC_STATUS; stdcall;
{$EXTERNALSYM RpcBindingInqAuthInfo}
function RpcBindingSetAuthInfo(Binding: RPC_BINDING_HANDLE; ServerPrincName: PWideChar;
  AuthnLevel, AuthnSvc: Cardinal; AuthIdentity: RPC_AUTH_IDENTITY_HANDLE;
  AuthzSvc: Cardinal): RPC_STATUS; stdcall;
{$EXTERNALSYM RpcBindingSetAuthInfo}
function RpcBindingSetAuthInfoEx(Binding: RPC_BINDING_HANDLE;
  ServerPrincName: PWideChar; AuthnLevel, AuthnSvc: Cardinal;
  AuthIdentity: RPC_AUTH_IDENTITY_HANDLE; AuthzSvc: Cardinal;
  const SecurityQOS: RPC_SECURITY_QOS): RPC_STATUS; stdcall;
{$EXTERNALSYM RpcBindingSetAuthInfoEx}
function RpcBindingInqAuthInfoEx(Binding: RPC_BINDING_HANDLE;
  ServerPrincName: PPWideChar; AuthnLevel, AuthnSvc: PCardinal;
  AuthIdentity: PRPC_AUTH_IDENTITY_HANDLE; AuthzSvc: PCardinal;
  RpcQosVersion: Cardinal; var SecurityQOS: RPC_SECURITY_QOS): RPC_STATUS; stdcall;
{$EXTERNALSYM RpcBindingInqAuthInfoEx}
function RpcServerRegisterAuthInfo(ServerPrincName: PWideChar; AuthnSvc: Cardinal;
  GetKeyFn: RPC_AUTH_KEY_RETRIEVAL_FN; Arg: Pointer): RPC_STATUS; stdcall;
{$EXTERNALSYM RpcServerRegisterAuthInfo}
{$ELSE}
function RpcBindingInqAuthClient(ClientBinding: RPC_BINDING_HANDLE;
  Privs: PRPC_AUTHZ_HANDLE; ServerPrincName: PPChar; AuthnLevel, AuthnSvc,
  AuthzSvc: PCardinal): RPC_STATUS; stdcall;
{$EXTERNALSYM RpcBindingInqAuthClient}
function RpcBindingInqAuthClientEx(ClientBinding: RPC_BINDING_HANDLE;
  Privs: PRPC_AUTHZ_HANDLE; ServerPrincName: PPChar; AuthnLevel, AuthnSvc,
  AuthzSvc: PCardinal; Flags: Cardinal): RPC_STATUS; stdcall;
{$EXTERNALSYM RpcBindingInqAuthClientEx}
function RpcBindingInqAuthInfo(Binding: RPC_BINDING_HANDLE; ServerPrincName: PPChar;
  AuthnLevel, AuthnSvc: PCardinal; AuthIdentity: PRPC_AUTH_IDENTITY_HANDLE;
  AuthzSvc: PCardinal): RPC_STATUS; stdcall;
{$EXTERNALSYM RpcBindingInqAuthInfo}
function RpcBindingSetAuthInfo(Binding: RPC_BINDING_HANDLE; ServerPrincName: PChar;
  AuthnLevel, AuthnSvc: Cardinal; AuthIdentity: RPC_AUTH_IDENTITY_HANDLE;
  AuthzSvc: Cardinal): RPC_STATUS; stdcall;
{$EXTERNALSYM RpcBindingSetAuthInfo}
function RpcBindingSetAuthInfoEx(Binding: RPC_BINDING_HANDLE;
  ServerPrincName: PChar; AuthnLevel, AuthnSvc: Cardinal;
  AuthIdentity: RPC_AUTH_IDENTITY_HANDLE; AuthzSvc: Cardinal;
  const SecurityQOS: RPC_SECURITY_QOS): RPC_STATUS; stdcall;
{$EXTERNALSYM RpcBindingSetAuthInfoEx}
function RpcBindingInqAuthInfoEx(Binding: RPC_BINDING_HANDLE;
  ServerPrincName: PPChar; AuthnLevel, AuthnSvc: PCardinal;
  AuthIdentity: PRPC_AUTH_IDENTITY_HANDLE; AuthzSvc: PCardinal;
  RpcQosVersion: Cardinal; var SecurityQOS: RPC_SECURITY_QOS): RPC_STATUS; stdcall;
{$EXTERNALSYM RpcBindingInqAuthInfoEx}
function RpcServerRegisterAuthInfo(ServerPrincName: PChar; AuthnSvc: Cardinal;
  GetKeyFn: RPC_AUTH_KEY_RETRIEVAL_FN; Arg: Pointer): RPC_STATUS; stdcall;
{$EXTERNALSYM RpcServerRegisterAuthInfo}
{$ENDIF}

type
  RPC_CLIENT_INFORMATION1 = record
    UserName: PChar;
    ComputerName: PChar;
    Privilege: Word;
    AuthFlags: Longword;
  end;
  {$EXTERNALSYM RPC_CLIENT_INFORMATION1}
  PRPC_CLIENT_INFORMATION1 = ^RPC_CLIENT_INFORMATION1;
  {$EXTERNALSYM PRPC_CLIENT_INFORMATION1}
  TRpcClientInformation1 = RPC_CLIENT_INFORMATION1;
  PRpcClientInformation1 = PRPC_CLIENT_INFORMATION1;

function RpcBindingServerFromClient(ClientBinding: RPC_BINDING_HANDLE;
  var ServerBinding: RPC_BINDING_HANDLE): RPC_STATUS; stdcall;
{$EXTERNALSYM RpcBindingServerFromClient}

procedure RpcRaiseException(exception: RPC_STATUS); stdcall;
{$EXTERNALSYM RpcRaiseException}

function RpcTestCancel: RPC_STATUS; stdcall;
{$EXTERNALSYM RpcTestCancel}

function RpcServerTestCancel(BindingHandle: RPC_BINDING_HANDLE): RPC_STATUS; stdcall;
{$EXTERNALSYM RpcServerTestCancel}

function RpcCancelThread(Thread: Pointer): RPC_STATUS; stdcall;
{$EXTERNALSYM RpcCancelThread}

function RpcCancelThreadEx(Thread: Pointer; Timeout: Longint): RPC_STATUS; stdcall;
{$EXTERNALSYM RpcCancelThreadEx}

function UuidCreate(var Uuid: UUID): RPC_STATUS; stdcall;
{$EXTERNALSYM UuidCreate}

function UuidCreateSequential(out Uuid: UUID): RPC_STATUS; stdcall;
{$EXTERNALSYM UuidCreateSequential}

function UuidFromStringA(StringUuid: PChar; var Uuid: UUID): RPC_STATUS; stdcall;
{$EXTERNALSYM UuidFromStringA}
function UuidFromStringW(StringUuid: PWideChar; var Uuid: UUID): RPC_STATUS; stdcall;
{$EXTERNALSYM UuidFromStringW}

{$IFDEF UNICODE}
function UuidFromString(StringUuid: PWideChar; var Uuid: UUID): RPC_STATUS; stdcall;
{$EXTERNALSYM UuidFromString}
{$ELSE}
function UuidFromString(StringUuid: PChar; var Uuid: UUID): RPC_STATUS; stdcall;
{$EXTERNALSYM UuidFromString}
{$ENDIF}

function UuidToStringA(const Uuid: UUID; var StringUuid: PChar): RPC_STATUS; stdcall;
{$EXTERNALSYM UuidToStringA}
function UuidToStringW(const Uuid: UUID; var StringUuid: PWideChar): RPC_STATUS; stdcall;
{$EXTERNALSYM UuidToStringW}

{$IFDEF UNICODE}
function UuidToString(const Uuid: UUID; var StringUuid: PWideChar): RPC_STATUS; stdcall;
{$EXTERNALSYM UuidToString}
{$ELSE}
function UuidToString(const Uuid: UUID; var StringUuid: PChar): RPC_STATUS; stdcall;
{$EXTERNALSYM UuidToString}
{$ENDIF}

function UuidCompare(const Uuid1, Uuid2: UUID; var Status: RPC_STATUS): Integer; stdcall;
{$EXTERNALSYM UuidCompare}

function UuidCreateNil(var NilUuid: UUID): RPC_STATUS; stdcall;
{$EXTERNALSYM UuidCreateNil}

function UuidEqual(const Uuid1, Uuid2: UUID; var Status: RPC_STATUS): Integer; stdcall;
{$EXTERNALSYM UuidEqual}

function UuidHash(const Uuid: UUID; var Status: RPC_STATUS): Word; stdcall;
{$EXTERNALSYM UuidHash}

function UuidIsNil(const Uuid: UUID; var Status: RPC_STATUS): Integer; stdcall;
{$EXTERNALSYM UuidIsNil}

function RpcEpRegisterNoReplaceA(IfSpec: RPC_IF_HANDLE;
  BindingVector: PRPC_BINDING_VECTOR; UuidVector: PUUID_VECTOR;
  Annotation: PChar): RPC_STATUS; stdcall;
{$EXTERNALSYM RpcEpRegisterNoReplaceA}
function RpcEpRegisterNoReplaceW(IfSpec: RPC_IF_HANDLE;
  BindingVector: PRPC_BINDING_VECTOR; UuidVector: PUUID_VECTOR;
  Annotation: PWideChar): RPC_STATUS; stdcall;
{$EXTERNALSYM RpcEpRegisterNoReplaceW}

{$IFDEF UNICODE}
function RpcEpRegisterNoReplace(IfSpec: RPC_IF_HANDLE;
  BindingVector: PRPC_BINDING_VECTOR; UuidVector: PUUID_VECTOR;
  Annotation: PWideChar): RPC_STATUS; stdcall;
{$EXTERNALSYM RpcEpRegisterNoReplace}
{$ELSE}
function RpcEpRegisterNoReplace(IfSpec: RPC_IF_HANDLE;
  BindingVector: PRPC_BINDING_VECTOR; UuidVector: PUUID_VECTOR;
  Annotation: PChar): RPC_STATUS; stdcall;
{$EXTERNALSYM RpcEpRegisterNoReplace}
{$ENDIF}

function RpcEpRegisterA(IfSpec: RPC_IF_HANDLE; BindingVector: PRPC_BINDING_VECTOR;
  UuidVector: PUUID_VECTOR; Annotation: PChar): RPC_STATUS; stdcall;
{$EXTERNALSYM RpcEpRegisterA}
function RpcEpRegisterW(IfSpec: RPC_IF_HANDLE; BindingVector: PRPC_BINDING_VECTOR;
  UuidVector: PUUID_VECTOR; Annotation: PWideChar): RPC_STATUS; stdcall;
{$EXTERNALSYM RpcEpRegisterW}

{$IFDEF UNICODE}
function RpcEpRegister(IfSpec: RPC_IF_HANDLE; BindingVector: PRPC_BINDING_VECTOR;
  UuidVector: PUUID_VECTOR; Annotation: PWideChar): RPC_STATUS; stdcall;
{$EXTERNALSYM RpcEpRegister}
{$ELSE}
function RpcEpRegister(IfSpec: RPC_IF_HANDLE; BindingVector: PRPC_BINDING_VECTOR;
  UuidVector: PUUID_VECTOR; Annotation: PChar): RPC_STATUS; stdcall;
{$EXTERNALSYM RpcEpRegister}
{$ENDIF}

function RpcEpUnregister(IfSpec: RPC_IF_HANDLE; BindingVector: PRPC_BINDING_VECTOR;
  UuidVector: UUID_VECTOR): RPC_STATUS; stdcall;
{$EXTERNALSYM RpcEpUnregister}

function DceErrorInqTextA(RpcStatus: RPC_STATUS; ErrorText: PChar): RPC_STATUS; stdcall;
{$EXTERNALSYM DceErrorInqTextA}
function DceErrorInqTextW(RpcStatus: RPC_STATUS; ErrorText: PWideChar): RPC_STATUS; stdcall;
{$EXTERNALSYM DceErrorInqTextW}

{$IFDEF UNICODE}
function DceErrorInqText(RpcStatus: RPC_STATUS; ErrorText: PWideChar): RPC_STATUS; stdcall;
{$EXTERNALSYM DceErrorInqText}
{$ELSE}
function DceErrorInqText(RpcStatus: RPC_STATUS; ErrorText: PChar): RPC_STATUS; stdcall;
{$EXTERNALSYM DceErrorInqText}
{$ENDIF}

const
  DCE_C_ERROR_STRING_LEN = 256;
  {$EXTERNALSYM DCE_C_ERROR_STRING_LEN}

type
  RPC_EP_INQ_HANDLE = ^I_RPC_HANDLE;
  {$EXTERNALSYM RPC_EP_INQ_HANDLE}

const
  RPC_C_EP_ALL_ELTS      = 0;
  {$EXTERNALSYM RPC_C_EP_ALL_ELTS}
  RPC_C_EP_MATCH_BY_IF   = 1;
  {$EXTERNALSYM RPC_C_EP_MATCH_BY_IF}
  RPC_C_EP_MATCH_BY_OBJ  = 2;
  {$EXTERNALSYM RPC_C_EP_MATCH_BY_OBJ}
  RPC_C_EP_MATCH_BY_BOTH = 3;
  {$EXTERNALSYM RPC_C_EP_MATCH_BY_BOTH}

  RPC_C_VERS_ALL        = 1;
  {$EXTERNALSYM RPC_C_VERS_ALL}
  RPC_C_VERS_COMPATIBLE = 2;
  {$EXTERNALSYM RPC_C_VERS_COMPATIBLE}
  RPC_C_VERS_EXACT      = 3;
  {$EXTERNALSYM RPC_C_VERS_EXACT}
  RPC_C_VERS_MAJOR_ONLY = 4;
  {$EXTERNALSYM RPC_C_VERS_MAJOR_ONLY}
  RPC_C_VERS_UPTO       = 5;
  {$EXTERNALSYM RPC_C_VERS_UPTO}

function RpcMgmtEpEltInqBegin(EpBinding: RPC_BINDING_HANDLE; InquiryType: Cardinal;
  IfId: PRPC_IF_ID; VersOption: Cardinal; ObjectUuid: PUUID;
  var InquiryContext: RPC_EP_INQ_HANDLE): RPC_STATUS; stdcall;
{$EXTERNALSYM RpcMgmtEpEltInqBegin}

function RpcMgmtEpEltInqDone(var InquiryContext: RPC_EP_INQ_HANDLE): RPC_STATUS; stdcall;
{$EXTERNALSYM RpcMgmtEpEltInqDone}

function RpcMgmtEpEltInqNextA(InquiryContext: RPC_EP_INQ_HANDLE; var IfId: RPC_IF_ID;
  Binding: PRPC_BINDING_HANDLE; ObjectUuid: PUUID; var Annotation: PChar): RPC_STATUS; stdcall;
{$EXTERNALSYM RpcMgmtEpEltInqNextA}

function RpcMgmtEpEltInqNextW(InquiryContext: RPC_EP_INQ_HANDLE; var IfId: RPC_IF_ID;
  Binding: PRPC_BINDING_HANDLE; ObjectUuid: PUUID; var Annotation: PWideChar): RPC_STATUS; stdcall;
{$EXTERNALSYM RpcMgmtEpEltInqNextW}

{$IFDEF UNICODE}
function RpcMgmtEpEltInqNext(InquiryContext: RPC_EP_INQ_HANDLE; var IfId: RPC_IF_ID;
  Binding: PRPC_BINDING_HANDLE; ObjectUuid: PUUID; var Annotation: PWideChar): RPC_STATUS; stdcall;
{$EXTERNALSYM RpcMgmtEpEltInqNext}
{$ELSE}
function RpcMgmtEpEltInqNext(InquiryContext: RPC_EP_INQ_HANDLE; var IfId: RPC_IF_ID;
  Binding: PRPC_BINDING_HANDLE; ObjectUuid: PUUID; var Annotation: PChar): RPC_STATUS; stdcall;
{$EXTERNALSYM RpcMgmtEpEltInqNext}
{$ENDIF}

function RpcMgmtEpUnregister(EpBinding: RPC_BINDING_HANDLE; IfId: PRPC_IF_ID;
  Binding: RPC_BINDING_HANDLE; ObjectUuid : PUUID): RPC_STATUS; stdcall;
{$EXTERNALSYM RpcMgmtEpUnregister}

type
  RPC_MGMT_AUTHORIZATION_FN = function (ClientBinding: RPC_BINDING_HANDLE;
    RequestedMgmtOperation: Cardinal; var Status: RPC_STATUS): Integer; stdcall;
  {$EXTERNALSYM RPC_MGMT_AUTHORIZATION_FN}
  TRpcMgmtAuthorizationFn = RPC_MGMT_AUTHORIZATION_FN;

const
  RPC_C_MGMT_INQ_IF_IDS         = 0;
  {$EXTERNALSYM RPC_C_MGMT_INQ_IF_IDS}
  RPC_C_MGMT_INQ_PRINC_NAME     = 1;
  {$EXTERNALSYM RPC_C_MGMT_INQ_PRINC_NAME}
  RPC_C_MGMT_INQ_STATS          = 2;
  {$EXTERNALSYM RPC_C_MGMT_INQ_STATS}
  RPC_C_MGMT_IS_SERVER_LISTEN   = 3;
  {$EXTERNALSYM RPC_C_MGMT_IS_SERVER_LISTEN}
  RPC_C_MGMT_STOP_SERVER_LISTEN = 4;
  {$EXTERNALSYM RPC_C_MGMT_STOP_SERVER_LISTEN}

function RpcMgmtSetAuthorizationFn(AuthorizationFn: RPC_MGMT_AUTHORIZATION_FN): RPC_STATUS; stdcall;
{$EXTERNALSYM RpcMgmtSetAuthorizationFn}

const
  RPC_C_PARM_MAX_PACKET_LENGTH = 1;
  {$EXTERNALSYM RPC_C_PARM_MAX_PACKET_LENGTH}
  RPC_C_PARM_BUFFER_LENGTH     = 2;
  {$EXTERNALSYM RPC_C_PARM_BUFFER_LENGTH}

  RPC_IF_AUTOLISTEN              = $0001;
  {$EXTERNALSYM RPC_IF_AUTOLISTEN}
  RPC_IF_OLE                     = $0002;
  {$EXTERNALSYM RPC_IF_OLE}
  RPC_IF_ALLOW_UNKNOWN_AUTHORITY = $0004;
  {$EXTERNALSYM RPC_IF_ALLOW_UNKNOWN_AUTHORITY}
  RPC_IF_ALLOW_SECURE_ONLY       = $0008;
  {$EXTERNALSYM RPC_IF_ALLOW_SECURE_ONLY}
  RPC_IF_ALLOW_CALLBACKS_WITH_NO_AUTH = $0010;
  {$EXTERNALSYM RPC_IF_ALLOW_CALLBACKS_WITH_NO_AUTH}

implementation

const
  rpclib = 'rpcrt4.dll';


{$IFDEF DYNAMIC_LINK}
var
  _RpcBindingCopy: Pointer;

function RpcBindingCopy;
begin
  GetProcedureAddress(_RpcBindingCopy, rpclib, 'RpcBindingCopy');
  asm
    mov esp, ebp
    pop ebp
    jmp [_RpcBindingCopy]
  end;
end;
{$ELSE}
function RpcBindingCopy; external rpclib name 'RpcBindingCopy';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _RpcBindingFree: Pointer;

function RpcBindingFree;
begin
  GetProcedureAddress(_RpcBindingFree, rpclib, 'RpcBindingFree');
  asm
    mov esp, ebp
    pop ebp
    jmp [_RpcBindingFree]
  end;
end;
{$ELSE}
function RpcBindingFree; external rpclib name 'RpcBindingFree';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _RpcBindingSetOption: Pointer;

function RpcBindingSetOption;
begin
  GetProcedureAddress(_RpcBindingSetOption, rpclib, 'RpcBindingSetOption');
  asm
    mov esp, ebp
    pop ebp
    jmp [_RpcBindingSetOption]
  end;
end;
{$ELSE}
function RpcBindingSetOption; external rpclib name 'RpcBindingSetOption';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _RpcBindingInqOption: Pointer;

function RpcBindingInqOption;
begin
  GetProcedureAddress(_RpcBindingInqOption, rpclib, 'RpcBindingInqOption');
  asm
    mov esp, ebp
    pop ebp
    jmp [_RpcBindingInqOption]
  end;
end;
{$ELSE}
function RpcBindingInqOption; external rpclib name 'RpcBindingInqOption';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _RpcBindingFromStringBindingA: Pointer;

function RpcBindingFromStringBindingA;
begin
  GetProcedureAddress(_RpcBindingFromStringBindingA, rpclib, 'RpcBindingFromStringBindingA');
  asm
    mov esp, ebp
    pop ebp
    jmp [_RpcBindingFromStringBindingA]
  end;
end;
{$ELSE}
function RpcBindingFromStringBindingA; external rpclib name 'RpcBindingFromStringBindingA';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _RpcBindingFromStringBindingW: Pointer;

function RpcBindingFromStringBindingW;
begin
  GetProcedureAddress(_RpcBindingFromStringBindingW, rpclib, 'RpcBindingFromStringBindingW');
  asm
    mov esp, ebp
    pop ebp
    jmp [_RpcBindingFromStringBindingW]
  end;
end;
{$ELSE}
function RpcBindingFromStringBindingW; external rpclib name 'RpcBindingFromStringBindingW';
{$ENDIF DYNAMIC_LINK}
{$IFDEF UNICODE}

{$IFDEF DYNAMIC_LINK}
var
  _RpcBindingFromStringBinding: Pointer;

function RpcBindingFromStringBinding;
begin
  GetProcedureAddress(_RpcBindingFromStringBinding, rpclib, 'RpcBindingFromStringBindingW');
  asm
    mov esp, ebp
    pop ebp
    jmp [_RpcBindingFromStringBinding]
  end;
end;
{$ELSE}
function RpcBindingFromStringBinding; external rpclib name 'RpcBindingFromStringBindingW';
{$ENDIF DYNAMIC_LINK}
{$ELSE}

{$IFDEF DYNAMIC_LINK}
var
  _RpcBindingFromStringBinding: Pointer;

function RpcBindingFromStringBinding;
begin
  GetProcedureAddress(_RpcBindingFromStringBinding, rpclib, 'RpcBindingFromStringBindingA');
  asm
    mov esp, ebp
    pop ebp
    jmp [_RpcBindingFromStringBinding]
  end;
end;
{$ELSE}
function RpcBindingFromStringBinding; external rpclib name 'RpcBindingFromStringBindingA';
{$ENDIF DYNAMIC_LINK}
{$ENDIF}

{$IFDEF DYNAMIC_LINK}
var
  _RpcSsGetContextBinding: Pointer;

function RpcSsGetContextBinding;
begin
  GetProcedureAddress(_RpcSsGetContextBinding, rpclib, 'RpcSsGetContextBinding');
  asm
    mov esp, ebp
    pop ebp
    jmp [_RpcSsGetContextBinding]
  end;
end;
{$ELSE}
function RpcSsGetContextBinding; external rpclib name 'RpcSsGetContextBinding';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _RpcBindingInqObject: Pointer;

function RpcBindingInqObject;
begin
  GetProcedureAddress(_RpcBindingInqObject, rpclib, 'RpcBindingInqObject');
  asm
    mov esp, ebp
    pop ebp
    jmp [_RpcBindingInqObject]
  end;
end;
{$ELSE}
function RpcBindingInqObject; external rpclib name 'RpcBindingInqObject';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _RpcBindingReset: Pointer;

function RpcBindingReset;
begin
  GetProcedureAddress(_RpcBindingReset, rpclib, 'RpcBindingReset');
  asm
    mov esp, ebp
    pop ebp
    jmp [_RpcBindingReset]
  end;
end;
{$ELSE}
function RpcBindingReset; external rpclib name 'RpcBindingReset';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _RpcBindingSetObject: Pointer;

function RpcBindingSetObject;
begin
  GetProcedureAddress(_RpcBindingSetObject, rpclib, 'RpcBindingSetObject');
  asm
    mov esp, ebp
    pop ebp
    jmp [_RpcBindingSetObject]
  end;
end;
{$ELSE}
function RpcBindingSetObject; external rpclib name 'RpcBindingSetObject';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _RpcMgmtInqDefaultProtectLevel: Pointer;

function RpcMgmtInqDefaultProtectLevel;
begin
  GetProcedureAddress(_RpcMgmtInqDefaultProtectLevel, rpclib, 'RpcMgmtInqDefaultProtectLevel');
  asm
    mov esp, ebp
    pop ebp
    jmp [_RpcMgmtInqDefaultProtectLevel]
  end;
end;
{$ELSE}
function RpcMgmtInqDefaultProtectLevel; external rpclib name 'RpcMgmtInqDefaultProtectLevel';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _RpcBindingToStringBindingA: Pointer;

function RpcBindingToStringBindingA;
begin
  GetProcedureAddress(_RpcBindingToStringBindingA, rpclib, 'RpcBindingToStringBindingA');
  asm
    mov esp, ebp
    pop ebp
    jmp [_RpcBindingToStringBindingA]
  end;
end;
{$ELSE}
function RpcBindingToStringBindingA; external rpclib name 'RpcBindingToStringBindingA';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _RpcBindingToStringBindingW: Pointer;

function RpcBindingToStringBindingW;
begin
  GetProcedureAddress(_RpcBindingToStringBindingW, rpclib, 'RpcBindingToStringBindingW');
  asm
    mov esp, ebp
    pop ebp
    jmp [_RpcBindingToStringBindingW]
  end;
end;
{$ELSE}
function RpcBindingToStringBindingW; external rpclib name 'RpcBindingToStringBindingW';
{$ENDIF DYNAMIC_LINK}
{$IFDEF UNICODE}

{$IFDEF DYNAMIC_LINK}
var
  _RpcBindingToStringBinding: Pointer;

function RpcBindingToStringBinding;
begin
  GetProcedureAddress(_RpcBindingToStringBinding, rpclib, 'RpcBindingToStringBindingW');
  asm
    mov esp, ebp
    pop ebp
    jmp [_RpcBindingToStringBinding]
  end;
end;
{$ELSE}
function RpcBindingToStringBinding; external rpclib name 'RpcBindingToStringBindingW';
{$ENDIF DYNAMIC_LINK}
{$ELSE}

{$IFDEF DYNAMIC_LINK}
var
  _RpcBindingToStringBinding: Pointer;

function RpcBindingToStringBinding;
begin
  GetProcedureAddress(_RpcBindingToStringBinding, rpclib, 'RpcBindingToStringBindingA');
  asm
    mov esp, ebp
    pop ebp
    jmp [_RpcBindingToStringBinding]
  end;
end;
{$ELSE}
function RpcBindingToStringBinding; external rpclib name 'RpcBindingToStringBindingA';
{$ENDIF DYNAMIC_LINK}
{$ENDIF}

{$IFDEF DYNAMIC_LINK}
var
  _RpcBindingVectorFree: Pointer;

function RpcBindingVectorFree;
begin
  GetProcedureAddress(_RpcBindingVectorFree, rpclib, 'RpcBindingVectorFree');
  asm
    mov esp, ebp
    pop ebp
    jmp [_RpcBindingVectorFree]
  end;
end;
{$ELSE}
function RpcBindingVectorFree; external rpclib name 'RpcBindingVectorFree';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _RpcStringBindingComposeA: Pointer;

function RpcStringBindingComposeA;
begin
  GetProcedureAddress(_RpcStringBindingComposeA, rpclib, 'RpcStringBindingComposeA');
  asm
    mov esp, ebp
    pop ebp
    jmp [_RpcStringBindingComposeA]
  end;
end;
{$ELSE}
function RpcStringBindingComposeA; external rpclib name 'RpcStringBindingComposeA';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _RpcStringBindingComposeW: Pointer;

function RpcStringBindingComposeW;
begin
  GetProcedureAddress(_RpcStringBindingComposeW, rpclib, 'RpcStringBindingComposeW');
  asm
    mov esp, ebp
    pop ebp
    jmp [_RpcStringBindingComposeW]
  end;
end;
{$ELSE}
function RpcStringBindingComposeW; external rpclib name 'RpcStringBindingComposeW';
{$ENDIF DYNAMIC_LINK}
{$IFDEF UNICODE}

{$IFDEF DYNAMIC_LINK}
var
  _RpcStringBindingCompose: Pointer;

function RpcStringBindingCompose;
begin
  GetProcedureAddress(_RpcStringBindingCompose, rpclib, 'RpcStringBindingComposeW');
  asm
    mov esp, ebp
    pop ebp
    jmp [_RpcStringBindingCompose]
  end;
end;
{$ELSE}
function RpcStringBindingCompose; external rpclib name 'RpcStringBindingComposeW';
{$ENDIF DYNAMIC_LINK}
{$ELSE}

{$IFDEF DYNAMIC_LINK}
var
  _RpcStringBindingCompose: Pointer;

function RpcStringBindingCompose;
begin
  GetProcedureAddress(_RpcStringBindingCompose, rpclib, 'RpcStringBindingComposeA');
  asm
    mov esp, ebp
    pop ebp
    jmp [_RpcStringBindingCompose]
  end;
end;
{$ELSE}
function RpcStringBindingCompose; external rpclib name 'RpcStringBindingComposeA';
{$ENDIF DYNAMIC_LINK}
{$ENDIF}

{$IFDEF DYNAMIC_LINK}
var
  _RpcStringBindingParseA: Pointer;

function RpcStringBindingParseA;
begin
  GetProcedureAddress(_RpcStringBindingParseA, rpclib, 'RpcStringBindingParseA');
  asm
    mov esp, ebp
    pop ebp
    jmp [_RpcStringBindingParseA]
  end;
end;
{$ELSE}
function RpcStringBindingParseA; external rpclib name 'RpcStringBindingParseA';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _RpcStringBindingParseW: Pointer;

function RpcStringBindingParseW;
begin
  GetProcedureAddress(_RpcStringBindingParseW, rpclib, 'RpcStringBindingParseW');
  asm
    mov esp, ebp
    pop ebp
    jmp [_RpcStringBindingParseW]
  end;
end;
{$ELSE}
function RpcStringBindingParseW; external rpclib name 'RpcStringBindingParseW';
{$ENDIF DYNAMIC_LINK}
{$IFDEF UNICODE}

{$IFDEF DYNAMIC_LINK}
var
  _RpcStringBindingParse: Pointer;

function RpcStringBindingParse;
begin
  GetProcedureAddress(_RpcStringBindingParse, rpclib, 'RpcStringBindingParseW');
  asm
    mov esp, ebp
    pop ebp
    jmp [_RpcStringBindingParse]
  end;
end;
{$ELSE}
function RpcStringBindingParse; external rpclib name 'RpcStringBindingParseW';
{$ENDIF DYNAMIC_LINK}
{$ELSE}

{$IFDEF DYNAMIC_LINK}
var
  _RpcStringBindingParse: Pointer;

function RpcStringBindingParse;
begin
  GetProcedureAddress(_RpcStringBindingParse, rpclib, 'RpcStringBindingParseA');
  asm
    mov esp, ebp
    pop ebp
    jmp [_RpcStringBindingParse]
  end;
end;
{$ELSE}
function RpcStringBindingParse; external rpclib name 'RpcStringBindingParseA';
{$ENDIF DYNAMIC_LINK}
{$ENDIF}

{$IFDEF DYNAMIC_LINK}
var
  _RpcStringFreeA: Pointer;

function RpcStringFreeA;
begin
  GetProcedureAddress(_RpcStringFreeA, rpclib, 'RpcStringFreeA');
  asm
    mov esp, ebp
    pop ebp
    jmp [_RpcStringFreeA]
  end;
end;
{$ELSE}
function RpcStringFreeA; external rpclib name 'RpcStringFreeA';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _RpcStringFreeW: Pointer;

function RpcStringFreeW;
begin
  GetProcedureAddress(_RpcStringFreeW, rpclib, 'RpcStringFreeW');
  asm
    mov esp, ebp
    pop ebp
    jmp [_RpcStringFreeW]
  end;
end;
{$ELSE}
function RpcStringFreeW; external rpclib name 'RpcStringFreeW';
{$ENDIF DYNAMIC_LINK}
{$IFDEF UNICODE}

{$IFDEF DYNAMIC_LINK}
var
  _RpcStringFree: Pointer;

function RpcStringFree;
begin
  GetProcedureAddress(_RpcStringFree, rpclib, 'RpcStringFreeW');
  asm
    mov esp, ebp
    pop ebp
    jmp [_RpcStringFree]
  end;
end;
{$ELSE}
function RpcStringFree; external rpclib name 'RpcStringFreeW';
{$ENDIF DYNAMIC_LINK}
{$ELSE}

{$IFDEF DYNAMIC_LINK}
var
  _RpcStringFree: Pointer;

function RpcStringFree;
begin
  GetProcedureAddress(_RpcStringFree, rpclib, 'RpcStringFreeA');
  asm
    mov esp, ebp
    pop ebp
    jmp [_RpcStringFree]
  end;
end;
{$ELSE}
function RpcStringFree; external rpclib name 'RpcStringFreeA';
{$ENDIF DYNAMIC_LINK}
{$ENDIF}

{$IFDEF DYNAMIC_LINK}
var
  _RpcIfInqId: Pointer;

function RpcIfInqId;
begin
  GetProcedureAddress(_RpcIfInqId, rpclib, 'RpcIfInqId');
  asm
    mov esp, ebp
    pop ebp
    jmp [_RpcIfInqId]
  end;
end;
{$ELSE}
function RpcIfInqId; external rpclib name 'RpcIfInqId';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _RpcNetworkIsProtseqValidA: Pointer;

function RpcNetworkIsProtseqValidA;
begin
  GetProcedureAddress(_RpcNetworkIsProtseqValidA, rpclib, 'RpcNetworkIsProtseqValidA');
  asm
    mov esp, ebp
    pop ebp
    jmp [_RpcNetworkIsProtseqValidA]
  end;
end;
{$ELSE}
function RpcNetworkIsProtseqValidA; external rpclib name 'RpcNetworkIsProtseqValidA';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _RpcNetworkIsProtseqValidW: Pointer;

function RpcNetworkIsProtseqValidW;
begin
  GetProcedureAddress(_RpcNetworkIsProtseqValidW, rpclib, 'RpcNetworkIsProtseqValidW');
  asm
    mov esp, ebp
    pop ebp
    jmp [_RpcNetworkIsProtseqValidW]
  end;
end;
{$ELSE}
function RpcNetworkIsProtseqValidW; external rpclib name 'RpcNetworkIsProtseqValidW';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _RpcMgmtInqComTimeout: Pointer;

function RpcMgmtInqComTimeout;
begin
  GetProcedureAddress(_RpcMgmtInqComTimeout, rpclib, 'RpcMgmtInqComTimeout');
  asm
    mov esp, ebp
    pop ebp
    jmp [_RpcMgmtInqComTimeout]
  end;
end;
{$ELSE}
function RpcMgmtInqComTimeout; external rpclib name 'RpcMgmtInqComTimeout';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _RpcMgmtSetComTimeout: Pointer;

function RpcMgmtSetComTimeout;
begin
  GetProcedureAddress(_RpcMgmtSetComTimeout, rpclib, 'RpcMgmtSetComTimeout');
  asm
    mov esp, ebp
    pop ebp
    jmp [_RpcMgmtSetComTimeout]
  end;
end;
{$ELSE}
function RpcMgmtSetComTimeout; external rpclib name 'RpcMgmtSetComTimeout';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _RpcMgmtSetCancelTimeout: Pointer;

function RpcMgmtSetCancelTimeout;
begin
  GetProcedureAddress(_RpcMgmtSetCancelTimeout, rpclib, 'RpcMgmtSetCancelTimeout');
  asm
    mov esp, ebp
    pop ebp
    jmp [_RpcMgmtSetCancelTimeout]
  end;
end;
{$ELSE}
function RpcMgmtSetCancelTimeout; external rpclib name 'RpcMgmtSetCancelTimeout';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _RpcNetworkInqProtseqsA: Pointer;

function RpcNetworkInqProtseqsA;
begin
  GetProcedureAddress(_RpcNetworkInqProtseqsA, rpclib, 'RpcNetworkInqProtseqsA');
  asm
    mov esp, ebp
    pop ebp
    jmp [_RpcNetworkInqProtseqsA]
  end;
end;
{$ELSE}
function RpcNetworkInqProtseqsA; external rpclib name 'RpcNetworkInqProtseqsA';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _RpcNetworkInqProtseqsW: Pointer;

function RpcNetworkInqProtseqsW;
begin
  GetProcedureAddress(_RpcNetworkInqProtseqsW, rpclib, 'RpcNetworkInqProtseqsW');
  asm
    mov esp, ebp
    pop ebp
    jmp [_RpcNetworkInqProtseqsW]
  end;
end;
{$ELSE}
function RpcNetworkInqProtseqsW; external rpclib name 'RpcNetworkInqProtseqsW';
{$ENDIF DYNAMIC_LINK}
{$IFDEF UNICODE}

{$IFDEF DYNAMIC_LINK}
var
  _RpcNetworkInqProtseqs: Pointer;

function RpcNetworkInqProtseqs;
begin
  GetProcedureAddress(_RpcNetworkInqProtseqs, rpclib, 'RpcNetworkInqProtseqsW');
  asm
    mov esp, ebp
    pop ebp
    jmp [_RpcNetworkInqProtseqs]
  end;
end;
{$ELSE}
function RpcNetworkInqProtseqs; external rpclib name 'RpcNetworkInqProtseqsW';
{$ENDIF DYNAMIC_LINK}
{$ELSE}

{$IFDEF DYNAMIC_LINK}
var
  _RpcNetworkInqProtseqs: Pointer;

function RpcNetworkInqProtseqs;
begin
  GetProcedureAddress(_RpcNetworkInqProtseqs, rpclib, 'RpcNetworkInqProtseqsA');
  asm
    mov esp, ebp
    pop ebp
    jmp [_RpcNetworkInqProtseqs]
  end;
end;
{$ELSE}
function RpcNetworkInqProtseqs; external rpclib name 'RpcNetworkInqProtseqsA';
{$ENDIF DYNAMIC_LINK}
{$ENDIF}

{$IFDEF DYNAMIC_LINK}
var
  _RpcObjectInqType: Pointer;

function RpcObjectInqType;
begin
  GetProcedureAddress(_RpcObjectInqType, rpclib, 'RpcObjectInqType');
  asm
    mov esp, ebp
    pop ebp
    jmp [_RpcObjectInqType]
  end;
end;
{$ELSE}
function RpcObjectInqType; external rpclib name 'RpcObjectInqType';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _RpcObjectSetInqFn: Pointer;

function RpcObjectSetInqFn;
begin
  GetProcedureAddress(_RpcObjectSetInqFn, rpclib, 'RpcObjectSetInqFn');
  asm
    mov esp, ebp
    pop ebp
    jmp [_RpcObjectSetInqFn]
  end;
end;
{$ELSE}
function RpcObjectSetInqFn; external rpclib name 'RpcObjectSetInqFn';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _RpcObjectSetType: Pointer;

function RpcObjectSetType;
begin
  GetProcedureAddress(_RpcObjectSetType, rpclib, 'RpcObjectSetType');
  asm
    mov esp, ebp
    pop ebp
    jmp [_RpcObjectSetType]
  end;
end;
{$ELSE}
function RpcObjectSetType; external rpclib name 'RpcObjectSetType';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _RpcProtseqVectorFreeA: Pointer;

function RpcProtseqVectorFreeA;
begin
  GetProcedureAddress(_RpcProtseqVectorFreeA, rpclib, 'RpcProtseqVectorFreeA');
  asm
    mov esp, ebp
    pop ebp
    jmp [_RpcProtseqVectorFreeA]
  end;
end;
{$ELSE}
function RpcProtseqVectorFreeA; external rpclib name 'RpcProtseqVectorFreeA';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _RpcProtseqVectorFreeW: Pointer;

function RpcProtseqVectorFreeW;
begin
  GetProcedureAddress(_RpcProtseqVectorFreeW, rpclib, 'RpcProtseqVectorFreeW');
  asm
    mov esp, ebp
    pop ebp
    jmp [_RpcProtseqVectorFreeW]
  end;
end;
{$ELSE}
function RpcProtseqVectorFreeW; external rpclib name 'RpcProtseqVectorFreeW';
{$ENDIF DYNAMIC_LINK}
{$IFDEF UNICODE}

{$IFDEF DYNAMIC_LINK}
var
  _RpcProtseqVectorFree: Pointer;

function RpcProtseqVectorFree;
begin
  GetProcedureAddress(_RpcProtseqVectorFree, rpclib, 'RpcProtseqVectorFreeW');
  asm
    mov esp, ebp
    pop ebp
    jmp [_RpcProtseqVectorFree]
  end;
end;
{$ELSE}
function RpcProtseqVectorFree; external rpclib name 'RpcProtseqVectorFreeW';
{$ENDIF DYNAMIC_LINK}
{$ELSE}

{$IFDEF DYNAMIC_LINK}
var
  _RpcProtseqVectorFree: Pointer;

function RpcProtseqVectorFree;
begin
  GetProcedureAddress(_RpcProtseqVectorFree, rpclib, 'RpcProtseqVectorFreeA');
  asm
    mov esp, ebp
    pop ebp
    jmp [_RpcProtseqVectorFree]
  end;
end;
{$ELSE}
function RpcProtseqVectorFree; external rpclib name 'RpcProtseqVectorFreeA';
{$ENDIF DYNAMIC_LINK}
{$ENDIF}

{$IFDEF DYNAMIC_LINK}
var
  _RpcServerInqBindings: Pointer;

function RpcServerInqBindings;
begin
  GetProcedureAddress(_RpcServerInqBindings, rpclib, 'RpcServerInqBindings');
  asm
    mov esp, ebp
    pop ebp
    jmp [_RpcServerInqBindings]
  end;
end;
{$ELSE}
function RpcServerInqBindings; external rpclib name 'RpcServerInqBindings';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _RpcServerInqIf: Pointer;

function RpcServerInqIf;
begin
  GetProcedureAddress(_RpcServerInqIf, rpclib, 'RpcServerInqIf');
  asm
    mov esp, ebp
    pop ebp
    jmp [_RpcServerInqIf]
  end;
end;
{$ELSE}
function RpcServerInqIf; external rpclib name 'RpcServerInqIf';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _RpcServerListen: Pointer;

function RpcServerListen;
begin
  GetProcedureAddress(_RpcServerListen, rpclib, 'RpcServerListen');
  asm
    mov esp, ebp
    pop ebp
    jmp [_RpcServerListen]
  end;
end;
{$ELSE}
function RpcServerListen; external rpclib name 'RpcServerListen';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _RpcServerRegisterIf: Pointer;

function RpcServerRegisterIf;
begin
  GetProcedureAddress(_RpcServerRegisterIf, rpclib, 'RpcServerRegisterIf');
  asm
    mov esp, ebp
    pop ebp
    jmp [_RpcServerRegisterIf]
  end;
end;
{$ELSE}
function RpcServerRegisterIf; external rpclib name 'RpcServerRegisterIf';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _RpcServerRegisterIfEx: Pointer;

function RpcServerRegisterIfEx;
begin
  GetProcedureAddress(_RpcServerRegisterIfEx, rpclib, 'RpcServerRegisterIfEx');
  asm
    mov esp, ebp
    pop ebp
    jmp [_RpcServerRegisterIfEx]
  end;
end;
{$ELSE}
function RpcServerRegisterIfEx; external rpclib name 'RpcServerRegisterIfEx';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _RpcServerRegisterIf2: Pointer;

function RpcServerRegisterIf2;
begin
  GetProcedureAddress(_RpcServerRegisterIf2, rpclib, 'RpcServerRegisterIf2');
  asm
    mov esp, ebp
    pop ebp
    jmp [_RpcServerRegisterIf2]
  end;
end;
{$ELSE}
function RpcServerRegisterIf2; external rpclib name 'RpcServerRegisterIf2';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _RpcServerUnregisterIf: Pointer;

function RpcServerUnregisterIf;
begin
  GetProcedureAddress(_RpcServerUnregisterIf, rpclib, 'RpcServerUnregisterIf');
  asm
    mov esp, ebp
    pop ebp
    jmp [_RpcServerUnregisterIf]
  end;
end;
{$ELSE}
function RpcServerUnregisterIf; external rpclib name 'RpcServerUnregisterIf';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _RpcServerUnregisterIfEx: Pointer;

function RpcServerUnregisterIfEx;
begin
  GetProcedureAddress(_RpcServerUnregisterIfEx, rpclib, 'RpcServerUnregisterIfEx');
  asm
    mov esp, ebp
    pop ebp
    jmp [_RpcServerUnregisterIfEx]
  end;
end;
{$ELSE}
function RpcServerUnregisterIfEx; external rpclib name 'RpcServerUnregisterIfEx';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _RpcServerUseAllProtseqs: Pointer;

function RpcServerUseAllProtseqs;
begin
  GetProcedureAddress(_RpcServerUseAllProtseqs, rpclib, 'RpcServerUseAllProtseqs');
  asm
    mov esp, ebp
    pop ebp
    jmp [_RpcServerUseAllProtseqs]
  end;
end;
{$ELSE}
function RpcServerUseAllProtseqs; external rpclib name 'RpcServerUseAllProtseqs';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _RpcServerUseAllProtseqsEx: Pointer;

function RpcServerUseAllProtseqsEx;
begin
  GetProcedureAddress(_RpcServerUseAllProtseqsEx, rpclib, 'RpcServerUseAllProtseqsEx');
  asm
    mov esp, ebp
    pop ebp
    jmp [_RpcServerUseAllProtseqsEx]
  end;
end;
{$ELSE}
function RpcServerUseAllProtseqsEx; external rpclib name 'RpcServerUseAllProtseqsEx';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _RpcServerUseAllProtseqsIf: Pointer;

function RpcServerUseAllProtseqsIf;
begin
  GetProcedureAddress(_RpcServerUseAllProtseqsIf, rpclib, 'RpcServerUseAllProtseqsIf');
  asm
    mov esp, ebp
    pop ebp
    jmp [_RpcServerUseAllProtseqsIf]
  end;
end;
{$ELSE}
function RpcServerUseAllProtseqsIf; external rpclib name 'RpcServerUseAllProtseqsIf';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _RpcServerUseAllProtseqsIfEx: Pointer;

function RpcServerUseAllProtseqsIfEx;
begin
  GetProcedureAddress(_RpcServerUseAllProtseqsIfEx, rpclib, 'RpcServerUseAllProtseqsIfEx');
  asm
    mov esp, ebp
    pop ebp
    jmp [_RpcServerUseAllProtseqsIfEx]
  end;
end;
{$ELSE}
function RpcServerUseAllProtseqsIfEx; external rpclib name 'RpcServerUseAllProtseqsIfEx';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _RpcServerUseProtseqA: Pointer;

function RpcServerUseProtseqA;
begin
  GetProcedureAddress(_RpcServerUseProtseqA, rpclib, 'RpcServerUseProtseqA');
  asm
    mov esp, ebp
    pop ebp
    jmp [_RpcServerUseProtseqA]
  end;
end;
{$ELSE}
function RpcServerUseProtseqA; external rpclib name 'RpcServerUseProtseqA';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _RpcServerUseProtseqW: Pointer;

function RpcServerUseProtseqW;
begin
  GetProcedureAddress(_RpcServerUseProtseqW, rpclib, 'RpcServerUseProtseqW');
  asm
    mov esp, ebp
    pop ebp
    jmp [_RpcServerUseProtseqW]
  end;
end;
{$ELSE}
function RpcServerUseProtseqW; external rpclib name 'RpcServerUseProtseqW';
{$ENDIF DYNAMIC_LINK}
{$IFDEF UNICODE}

{$IFDEF DYNAMIC_LINK}
var
  _RpcServerUseProtseq: Pointer;

function RpcServerUseProtseq;
begin
  GetProcedureAddress(_RpcServerUseProtseq, rpclib, 'RpcServerUseProtseqW');
  asm
    mov esp, ebp
    pop ebp
    jmp [_RpcServerUseProtseq]
  end;
end;
{$ELSE}
function RpcServerUseProtseq; external rpclib name 'RpcServerUseProtseqW';
{$ENDIF DYNAMIC_LINK}
{$ELSE}

{$IFDEF DYNAMIC_LINK}
var
  _RpcServerUseProtseq: Pointer;

function RpcServerUseProtseq;
begin
  GetProcedureAddress(_RpcServerUseProtseq, rpclib, 'RpcServerUseProtseqA');
  asm
    mov esp, ebp
    pop ebp
    jmp [_RpcServerUseProtseq]
  end;
end;
{$ELSE}
function RpcServerUseProtseq; external rpclib name 'RpcServerUseProtseqA';
{$ENDIF DYNAMIC_LINK}
{$ENDIF}

{$IFDEF DYNAMIC_LINK}
var
  _RpcServerUseProtseqExA: Pointer;

function RpcServerUseProtseqExA;
begin
  GetProcedureAddress(_RpcServerUseProtseqExA, rpclib, 'RpcServerUseProtseqExA');
  asm
    mov esp, ebp
    pop ebp
    jmp [_RpcServerUseProtseqExA]
  end;
end;
{$ELSE}
function RpcServerUseProtseqExA; external rpclib name 'RpcServerUseProtseqExA';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _RpcServerUseProtseqExW: Pointer;

function RpcServerUseProtseqExW;
begin
  GetProcedureAddress(_RpcServerUseProtseqExW, rpclib, 'RpcServerUseProtseqExW');
  asm
    mov esp, ebp
    pop ebp
    jmp [_RpcServerUseProtseqExW]
  end;
end;
{$ELSE}
function RpcServerUseProtseqExW; external rpclib name 'RpcServerUseProtseqExW';
{$ENDIF DYNAMIC_LINK}
{$IFDEF UNICODE}

{$IFDEF DYNAMIC_LINK}
var
  _RpcServerUseProtseqEx: Pointer;

function RpcServerUseProtseqEx;
begin
  GetProcedureAddress(_RpcServerUseProtseqEx, rpclib, 'RpcServerUseProtseqExW');
  asm
    mov esp, ebp
    pop ebp
    jmp [_RpcServerUseProtseqEx]
  end;
end;
{$ELSE}
function RpcServerUseProtseqEx; external rpclib name 'RpcServerUseProtseqExW';
{$ENDIF DYNAMIC_LINK}
{$ELSE}

{$IFDEF DYNAMIC_LINK}
var
  _RpcServerUseProtseqEx: Pointer;

function RpcServerUseProtseqEx;
begin
  GetProcedureAddress(_RpcServerUseProtseqEx, rpclib, 'RpcServerUseProtseqExA');
  asm
    mov esp, ebp
    pop ebp
    jmp [_RpcServerUseProtseqEx]
  end;
end;
{$ELSE}
function RpcServerUseProtseqEx; external rpclib name 'RpcServerUseProtseqExA';
{$ENDIF DYNAMIC_LINK}
{$ENDIF}

{$IFDEF DYNAMIC_LINK}
var
  _RpcServerUseProtseqEpA: Pointer;

function RpcServerUseProtseqEpA;
begin
  GetProcedureAddress(_RpcServerUseProtseqEpA, rpclib, 'RpcServerUseProtseqEpA');
  asm
    mov esp, ebp
    pop ebp
    jmp [_RpcServerUseProtseqEpA]
  end;
end;
{$ELSE}
function RpcServerUseProtseqEpA; external rpclib name 'RpcServerUseProtseqEpA';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _RpcServerUseProtseqEpW: Pointer;

function RpcServerUseProtseqEpW;
begin
  GetProcedureAddress(_RpcServerUseProtseqEpW, rpclib, 'RpcServerUseProtseqEpW');
  asm
    mov esp, ebp
    pop ebp
    jmp [_RpcServerUseProtseqEpW]
  end;
end;
{$ELSE}
function RpcServerUseProtseqEpW; external rpclib name 'RpcServerUseProtseqEpW';
{$ENDIF DYNAMIC_LINK}
{$IFDEF UNICODE}

{$IFDEF DYNAMIC_LINK}
var
  _RpcServerUseProtseqEp: Pointer;

function RpcServerUseProtseqEp;
begin
  GetProcedureAddress(_RpcServerUseProtseqEp, rpclib, 'RpcServerUseProtseqEpW');
  asm
    mov esp, ebp
    pop ebp
    jmp [_RpcServerUseProtseqEp]
  end;
end;
{$ELSE}
function RpcServerUseProtseqEp; external rpclib name 'RpcServerUseProtseqEpW';
{$ENDIF DYNAMIC_LINK}
{$ELSE}

{$IFDEF DYNAMIC_LINK}
var
  _RpcServerUseProtseqEp: Pointer;

function RpcServerUseProtseqEp;
begin
  GetProcedureAddress(_RpcServerUseProtseqEp, rpclib, 'RpcServerUseProtseqEpA');
  asm
    mov esp, ebp
    pop ebp
    jmp [_RpcServerUseProtseqEp]
  end;
end;
{$ELSE}
function RpcServerUseProtseqEp; external rpclib name 'RpcServerUseProtseqEpA';
{$ENDIF DYNAMIC_LINK}
{$ENDIF}

{$IFDEF DYNAMIC_LINK}
var
  _RpcServerUseProtseqEpExA: Pointer;

function RpcServerUseProtseqEpExA;
begin
  GetProcedureAddress(_RpcServerUseProtseqEpExA, rpclib, 'RpcServerUseProtseqEpExA');
  asm
    mov esp, ebp
    pop ebp
    jmp [_RpcServerUseProtseqEpExA]
  end;
end;
{$ELSE}
function RpcServerUseProtseqEpExA; external rpclib name 'RpcServerUseProtseqEpExA';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _RpcServerUseProtseqEpExW: Pointer;

function RpcServerUseProtseqEpExW;
begin
  GetProcedureAddress(_RpcServerUseProtseqEpExW, rpclib, 'RpcServerUseProtseqEpExW');
  asm
    mov esp, ebp
    pop ebp
    jmp [_RpcServerUseProtseqEpExW]
  end;
end;
{$ELSE}
function RpcServerUseProtseqEpExW; external rpclib name 'RpcServerUseProtseqEpExW';
{$ENDIF DYNAMIC_LINK}
{$IFDEF UNICODE}

{$IFDEF DYNAMIC_LINK}
var
  _RpcServerUseProtseqEpEx: Pointer;

function RpcServerUseProtseqEpEx;
begin
  GetProcedureAddress(_RpcServerUseProtseqEpEx, rpclib, 'RpcServerUseProtseqEpExW');
  asm
    mov esp, ebp
    pop ebp
    jmp [_RpcServerUseProtseqEpEx]
  end;
end;
{$ELSE}
function RpcServerUseProtseqEpEx; external rpclib name 'RpcServerUseProtseqEpExW';
{$ENDIF DYNAMIC_LINK}
{$ELSE}

{$IFDEF DYNAMIC_LINK}
var
  _RpcServerUseProtseqEpEx: Pointer;

function RpcServerUseProtseqEpEx;
begin
  GetProcedureAddress(_RpcServerUseProtseqEpEx, rpclib, 'RpcServerUseProtseqEpExA');
  asm
    mov esp, ebp
    pop ebp
    jmp [_RpcServerUseProtseqEpEx]
  end;
end;
{$ELSE}
function RpcServerUseProtseqEpEx; external rpclib name 'RpcServerUseProtseqEpExA';
{$ENDIF DYNAMIC_LINK}
{$ENDIF}

{$IFDEF DYNAMIC_LINK}
var
  _RpcServerUseProtseqIfA: Pointer;

function RpcServerUseProtseqIfA;
begin
  GetProcedureAddress(_RpcServerUseProtseqIfA, rpclib, 'RpcServerUseProtseqIfA');
  asm
    mov esp, ebp
    pop ebp
    jmp [_RpcServerUseProtseqIfA]
  end;
end;
{$ELSE}
function RpcServerUseProtseqIfA; external rpclib name 'RpcServerUseProtseqIfA';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _RpcServerUseProtseqIfW: Pointer;

function RpcServerUseProtseqIfW;
begin
  GetProcedureAddress(_RpcServerUseProtseqIfW, rpclib, 'RpcServerUseProtseqIfW');
  asm
    mov esp, ebp
    pop ebp
    jmp [_RpcServerUseProtseqIfW]
  end;
end;
{$ELSE}
function RpcServerUseProtseqIfW; external rpclib name 'RpcServerUseProtseqIfW';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _RpcServerUseProtseqIfExA: Pointer;

function RpcServerUseProtseqIfExA;
begin
  GetProcedureAddress(_RpcServerUseProtseqIfExA, rpclib, 'RpcServerUseProtseqIfExA');
  asm
    mov esp, ebp
    pop ebp
    jmp [_RpcServerUseProtseqIfExA]
  end;
end;
{$ELSE}
function RpcServerUseProtseqIfExA; external rpclib name 'RpcServerUseProtseqIfExA';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _RpcServerUseProtseqIfExW: Pointer;

function RpcServerUseProtseqIfExW;
begin
  GetProcedureAddress(_RpcServerUseProtseqIfExW, rpclib, 'RpcServerUseProtseqIfExW');
  asm
    mov esp, ebp
    pop ebp
    jmp [_RpcServerUseProtseqIfExW]
  end;
end;
{$ELSE}
function RpcServerUseProtseqIfExW; external rpclib name 'RpcServerUseProtseqIfExW';
{$ENDIF DYNAMIC_LINK}
{$IFDEF UNICODE}

{$IFDEF DYNAMIC_LINK}
var
  _RpcServerUseProtseqIfEx: Pointer;

function RpcServerUseProtseqIfEx;
begin
  GetProcedureAddress(_RpcServerUseProtseqIfEx, rpclib, 'RpcServerUseProtseqIfExW');
  asm
    mov esp, ebp
    pop ebp
    jmp [_RpcServerUseProtseqIfEx]
  end;
end;
{$ELSE}
function RpcServerUseProtseqIfEx; external rpclib name 'RpcServerUseProtseqIfExW';
{$ENDIF DYNAMIC_LINK}
{$ELSE}

{$IFDEF DYNAMIC_LINK}
var
  _RpcServerUseProtseqIfEx: Pointer;

function RpcServerUseProtseqIfEx;
begin
  GetProcedureAddress(_RpcServerUseProtseqIfEx, rpclib, 'RpcServerUseProtseqIfExA');
  asm
    mov esp, ebp
    pop ebp
    jmp [_RpcServerUseProtseqIfEx]
  end;
end;
{$ELSE}
function RpcServerUseProtseqIfEx; external rpclib name 'RpcServerUseProtseqIfExA';
{$ENDIF DYNAMIC_LINK}
{$ENDIF}

{$IFDEF DYNAMIC_LINK}
var
  _RpcServerYield: Pointer;

procedure RpcServerYield;
begin
  GetProcedureAddress(_RpcServerYield, rpclib, 'RpcServerYield');
  asm
    mov esp, ebp
    pop ebp
    jmp [_RpcServerYield]
  end;
end;
{$ELSE}
procedure RpcServerYield; external rpclib name 'RpcServerYield';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _RpcMgmtStatsVectorFree: Pointer;

function RpcMgmtStatsVectorFree;
begin
  GetProcedureAddress(_RpcMgmtStatsVectorFree, rpclib, 'RpcMgmtStatsVectorFree');
  asm
    mov esp, ebp
    pop ebp
    jmp [_RpcMgmtStatsVectorFree]
  end;
end;
{$ELSE}
function RpcMgmtStatsVectorFree; external rpclib name 'RpcMgmtStatsVectorFree';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _RpcMgmtInqStats: Pointer;

function RpcMgmtInqStats;
begin
  GetProcedureAddress(_RpcMgmtInqStats, rpclib, 'RpcMgmtInqStats');
  asm
    mov esp, ebp
    pop ebp
    jmp [_RpcMgmtInqStats]
  end;
end;
{$ELSE}
function RpcMgmtInqStats; external rpclib name 'RpcMgmtInqStats';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _RpcMgmtIsServerListening: Pointer;

function RpcMgmtIsServerListening;
begin
  GetProcedureAddress(_RpcMgmtIsServerListening, rpclib, 'RpcMgmtIsServerListening');
  asm
    mov esp, ebp
    pop ebp
    jmp [_RpcMgmtIsServerListening]
  end;
end;
{$ELSE}
function RpcMgmtIsServerListening; external rpclib name 'RpcMgmtIsServerListening';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _RpcMgmtStopServerListening: Pointer;

function RpcMgmtStopServerListening;
begin
  GetProcedureAddress(_RpcMgmtStopServerListening, rpclib, 'RpcMgmtStopServerListening');
  asm
    mov esp, ebp
    pop ebp
    jmp [_RpcMgmtStopServerListening]
  end;
end;
{$ELSE}
function RpcMgmtStopServerListening; external rpclib name 'RpcMgmtStopServerListening';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _RpcMgmtWaitServerListen: Pointer;

function RpcMgmtWaitServerListen;
begin
  GetProcedureAddress(_RpcMgmtWaitServerListen, rpclib, 'RpcMgmtWaitServerListen');
  asm
    mov esp, ebp
    pop ebp
    jmp [_RpcMgmtWaitServerListen]
  end;
end;
{$ELSE}
function RpcMgmtWaitServerListen; external rpclib name 'RpcMgmtWaitServerListen';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _RpcMgmtSetServerStackSize: Pointer;

function RpcMgmtSetServerStackSize;
begin
  GetProcedureAddress(_RpcMgmtSetServerStackSize, rpclib, 'RpcMgmtSetServerStackSize');
  asm
    mov esp, ebp
    pop ebp
    jmp [_RpcMgmtSetServerStackSize]
  end;
end;
{$ELSE}
function RpcMgmtSetServerStackSize; external rpclib name 'RpcMgmtSetServerStackSize';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _RpcSsDontSerializeContext: Pointer;

procedure RpcSsDontSerializeContext;
begin
  GetProcedureAddress(_RpcSsDontSerializeContext, rpclib, 'RpcSsDontSerializeContext');
  asm
    mov esp, ebp
    pop ebp
    jmp [_RpcSsDontSerializeContext]
  end;
end;
{$ELSE}
procedure RpcSsDontSerializeContext; external rpclib name 'RpcSsDontSerializeContext';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _RpcMgmtEnableIdleCleanup: Pointer;

function RpcMgmtEnableIdleCleanup;
begin
  GetProcedureAddress(_RpcMgmtEnableIdleCleanup, rpclib, 'RpcMgmtEnableIdleCleanup');
  asm
    mov esp, ebp
    pop ebp
    jmp [_RpcMgmtEnableIdleCleanup]
  end;
end;
{$ELSE}
function RpcMgmtEnableIdleCleanup; external rpclib name 'RpcMgmtEnableIdleCleanup';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _RpcMgmtInqIfIds: Pointer;

function RpcMgmtInqIfIds;
begin
  GetProcedureAddress(_RpcMgmtInqIfIds, rpclib, 'RpcMgmtInqIfIds');
  asm
    mov esp, ebp
    pop ebp
    jmp [_RpcMgmtInqIfIds]
  end;
end;
{$ELSE}
function RpcMgmtInqIfIds; external rpclib name 'RpcMgmtInqIfIds';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _RpcIfIdVectorFree: Pointer;

function RpcIfIdVectorFree;
begin
  GetProcedureAddress(_RpcIfIdVectorFree, rpclib, 'RpcIfIdVectorFree');
  asm
    mov esp, ebp
    pop ebp
    jmp [_RpcIfIdVectorFree]
  end;
end;
{$ELSE}
function RpcIfIdVectorFree; external rpclib name 'RpcIfIdVectorFree';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _RpcMgmtInqServerPrincNameA: Pointer;

function RpcMgmtInqServerPrincNameA;
begin
  GetProcedureAddress(_RpcMgmtInqServerPrincNameA, rpclib, 'RpcMgmtInqServerPrincNameA');
  asm
    mov esp, ebp
    pop ebp
    jmp [_RpcMgmtInqServerPrincNameA]
  end;
end;
{$ELSE}
function RpcMgmtInqServerPrincNameA; external rpclib name 'RpcMgmtInqServerPrincNameA';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _RpcMgmtInqServerPrincNameW: Pointer;

function RpcMgmtInqServerPrincNameW;
begin
  GetProcedureAddress(_RpcMgmtInqServerPrincNameW, rpclib, 'RpcMgmtInqServerPrincNameW');
  asm
    mov esp, ebp
    pop ebp
    jmp [_RpcMgmtInqServerPrincNameW]
  end;
end;
{$ELSE}
function RpcMgmtInqServerPrincNameW; external rpclib name 'RpcMgmtInqServerPrincNameW';
{$ENDIF DYNAMIC_LINK}
{$IFDEF UNICODE}

{$IFDEF DYNAMIC_LINK}
var
  _RpcMgmtInqServerPrincName: Pointer;

function RpcMgmtInqServerPrincName;
begin
  GetProcedureAddress(_RpcMgmtInqServerPrincName, rpclib, 'RpcMgmtInqServerPrincNameW');
  asm
    mov esp, ebp
    pop ebp
    jmp [_RpcMgmtInqServerPrincName]
  end;
end;
{$ELSE}
function RpcMgmtInqServerPrincName; external rpclib name 'RpcMgmtInqServerPrincNameW';
{$ENDIF DYNAMIC_LINK}
{$ELSE}

{$IFDEF DYNAMIC_LINK}
var
  _RpcMgmtInqServerPrincName: Pointer;

function RpcMgmtInqServerPrincName;
begin
  GetProcedureAddress(_RpcMgmtInqServerPrincName, rpclib, 'RpcMgmtInqServerPrincNameA');
  asm
    mov esp, ebp
    pop ebp
    jmp [_RpcMgmtInqServerPrincName]
  end;
end;
{$ELSE}
function RpcMgmtInqServerPrincName; external rpclib name 'RpcMgmtInqServerPrincNameA';
{$ENDIF DYNAMIC_LINK}
{$ENDIF}

{$IFDEF DYNAMIC_LINK}
var
  _RpcServerInqDefaultPrincNameA: Pointer;

function RpcServerInqDefaultPrincNameA;
begin
  GetProcedureAddress(_RpcServerInqDefaultPrincNameA, rpclib, 'RpcServerInqDefaultPrincNameA');
  asm
    mov esp, ebp
    pop ebp
    jmp [_RpcServerInqDefaultPrincNameA]
  end;
end;
{$ELSE}
function RpcServerInqDefaultPrincNameA; external rpclib name 'RpcServerInqDefaultPrincNameA';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _RpcServerInqDefaultPrincNameW: Pointer;

function RpcServerInqDefaultPrincNameW;
begin
  GetProcedureAddress(_RpcServerInqDefaultPrincNameW, rpclib, 'RpcServerInqDefaultPrincNameW');
  asm
    mov esp, ebp
    pop ebp
    jmp [_RpcServerInqDefaultPrincNameW]
  end;
end;
{$ELSE}
function RpcServerInqDefaultPrincNameW; external rpclib name 'RpcServerInqDefaultPrincNameW';
{$ENDIF DYNAMIC_LINK}
{$IFDEF UNICODE}

{$IFDEF DYNAMIC_LINK}
var
  _RpcServerInqDefaultPrincName: Pointer;

function RpcServerInqDefaultPrincName;
begin
  GetProcedureAddress(_RpcServerInqDefaultPrincName, rpclib, 'RpcServerInqDefaultPrincNameW');
  asm
    mov esp, ebp
    pop ebp
    jmp [_RpcServerInqDefaultPrincName]
  end;
end;
{$ELSE}
function RpcServerInqDefaultPrincName; external rpclib name 'RpcServerInqDefaultPrincNameW';
{$ENDIF DYNAMIC_LINK}
{$ELSE}

{$IFDEF DYNAMIC_LINK}
var
  _RpcServerInqDefaultPrincName: Pointer;

function RpcServerInqDefaultPrincName;
begin
  GetProcedureAddress(_RpcServerInqDefaultPrincName, rpclib, 'RpcServerInqDefaultPrincNameA');
  asm
    mov esp, ebp
    pop ebp
    jmp [_RpcServerInqDefaultPrincName]
  end;
end;
{$ELSE}
function RpcServerInqDefaultPrincName; external rpclib name 'RpcServerInqDefaultPrincNameA';
{$ENDIF DYNAMIC_LINK}
{$ENDIF}

{$IFDEF DYNAMIC_LINK}
var
  _RpcEpResolveBinding: Pointer;

function RpcEpResolveBinding;
begin
  GetProcedureAddress(_RpcEpResolveBinding, rpclib, 'RpcEpResolveBinding');
  asm
    mov esp, ebp
    pop ebp
    jmp [_RpcEpResolveBinding]
  end;
end;
{$ELSE}
function RpcEpResolveBinding; external rpclib name 'RpcEpResolveBinding';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _RpcNsBindingInqEntryNameA: Pointer;

function RpcNsBindingInqEntryNameA;
begin
  GetProcedureAddress(_RpcNsBindingInqEntryNameA, rpclib, 'RpcNsBindingInqEntryNameA');
  asm
    mov esp, ebp
    pop ebp
    jmp [_RpcNsBindingInqEntryNameA]
  end;
end;
{$ELSE}
function RpcNsBindingInqEntryNameA; external rpclib name 'RpcNsBindingInqEntryNameA';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _RpcNsBindingInqEntryNameW: Pointer;

function RpcNsBindingInqEntryNameW;
begin
  GetProcedureAddress(_RpcNsBindingInqEntryNameW, rpclib, 'RpcNsBindingInqEntryNameW');
  asm
    mov esp, ebp
    pop ebp
    jmp [_RpcNsBindingInqEntryNameW]
  end;
end;
{$ELSE}
function RpcNsBindingInqEntryNameW; external rpclib name 'RpcNsBindingInqEntryNameW';
{$ENDIF DYNAMIC_LINK}
{$IFDEF UNICODE}

{$IFDEF DYNAMIC_LINK}
var
  _RpcNsBindingInqEntryName: Pointer;

function RpcNsBindingInqEntryName;
begin
  GetProcedureAddress(_RpcNsBindingInqEntryName, rpclib, 'RpcNsBindingInqEntryNameW');
  asm
    mov esp, ebp
    pop ebp
    jmp [_RpcNsBindingInqEntryName]
  end;
end;
{$ELSE}
function RpcNsBindingInqEntryName; external rpclib name 'RpcNsBindingInqEntryNameW';
{$ENDIF DYNAMIC_LINK}
{$ELSE}

{$IFDEF DYNAMIC_LINK}
var
  _RpcNsBindingInqEntryName: Pointer;

function RpcNsBindingInqEntryName;
begin
  GetProcedureAddress(_RpcNsBindingInqEntryName, rpclib, 'RpcNsBindingInqEntryNameA');
  asm
    mov esp, ebp
    pop ebp
    jmp [_RpcNsBindingInqEntryName]
  end;
end;
{$ELSE}
function RpcNsBindingInqEntryName; external rpclib name 'RpcNsBindingInqEntryNameA';
{$ENDIF DYNAMIC_LINK}
{$ENDIF}

{$IFDEF DYNAMIC_LINK}
var
  _RpcImpersonateClient: Pointer;

function RpcImpersonateClient;
begin
  GetProcedureAddress(_RpcImpersonateClient, rpclib, 'RpcImpersonateClient');
  asm
    mov esp, ebp
    pop ebp
    jmp [_RpcImpersonateClient]
  end;
end;
{$ELSE}
function RpcImpersonateClient; external rpclib name 'RpcImpersonateClient';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _RpcRevertToSelfEx: Pointer;

function RpcRevertToSelfEx;
begin
  GetProcedureAddress(_RpcRevertToSelfEx, rpclib, 'RpcRevertToSelfEx');
  asm
    mov esp, ebp
    pop ebp
    jmp [_RpcRevertToSelfEx]
  end;
end;
{$ELSE}
function RpcRevertToSelfEx; external rpclib name 'RpcRevertToSelfEx';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _RpcRevertToSelf: Pointer;

function RpcRevertToSelf;
begin
  GetProcedureAddress(_RpcRevertToSelf, rpclib, 'RpcRevertToSelf');
  asm
    mov esp, ebp
    pop ebp
    jmp [_RpcRevertToSelf]
  end;
end;
{$ELSE}
function RpcRevertToSelf; external rpclib name 'RpcRevertToSelf';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _RpcBindingInqAuthClientA: Pointer;

function RpcBindingInqAuthClientA;
begin
  GetProcedureAddress(_RpcBindingInqAuthClientA, rpclib, 'RpcBindingInqAuthClientA');
  asm
    mov esp, ebp
    pop ebp
    jmp [_RpcBindingInqAuthClientA]
  end;
end;
{$ELSE}
function RpcBindingInqAuthClientA; external rpclib name 'RpcBindingInqAuthClientA';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _RpcBindingInqAuthClientW: Pointer;

function RpcBindingInqAuthClientW;
begin
  GetProcedureAddress(_RpcBindingInqAuthClientW, rpclib, 'RpcBindingInqAuthClientW');
  asm
    mov esp, ebp
    pop ebp
    jmp [_RpcBindingInqAuthClientW]
  end;
end;
{$ELSE}
function RpcBindingInqAuthClientW; external rpclib name 'RpcBindingInqAuthClientW';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _RpcBindingInqAuthClientExA: Pointer;

function RpcBindingInqAuthClientExA;
begin
  GetProcedureAddress(_RpcBindingInqAuthClientExA, rpclib, 'RpcBindingInqAuthClientExA');
  asm
    mov esp, ebp
    pop ebp
    jmp [_RpcBindingInqAuthClientExA]
  end;
end;
{$ELSE}
function RpcBindingInqAuthClientExA; external rpclib name 'RpcBindingInqAuthClientExA';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _RpcBindingInqAuthClientExW: Pointer;

function RpcBindingInqAuthClientExW;
begin
  GetProcedureAddress(_RpcBindingInqAuthClientExW, rpclib, 'RpcBindingInqAuthClientExW');
  asm
    mov esp, ebp
    pop ebp
    jmp [_RpcBindingInqAuthClientExW]
  end;
end;
{$ELSE}
function RpcBindingInqAuthClientExW; external rpclib name 'RpcBindingInqAuthClientExW';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _RpcBindingInqAuthInfoA: Pointer;

function RpcBindingInqAuthInfoA;
begin
  GetProcedureAddress(_RpcBindingInqAuthInfoA, rpclib, 'RpcBindingInqAuthInfoA');
  asm
    mov esp, ebp
    pop ebp
    jmp [_RpcBindingInqAuthInfoA]
  end;
end;
{$ELSE}
function RpcBindingInqAuthInfoA; external rpclib name 'RpcBindingInqAuthInfoA';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _RpcBindingInqAuthInfoW: Pointer;

function RpcBindingInqAuthInfoW;
begin
  GetProcedureAddress(_RpcBindingInqAuthInfoW, rpclib, 'RpcBindingInqAuthInfoW');
  asm
    mov esp, ebp
    pop ebp
    jmp [_RpcBindingInqAuthInfoW]
  end;
end;
{$ELSE}
function RpcBindingInqAuthInfoW; external rpclib name 'RpcBindingInqAuthInfoW';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _RpcBindingSetAuthInfoA: Pointer;

function RpcBindingSetAuthInfoA;
begin
  GetProcedureAddress(_RpcBindingSetAuthInfoA, rpclib, 'RpcBindingSetAuthInfoA');
  asm
    mov esp, ebp
    pop ebp
    jmp [_RpcBindingSetAuthInfoA]
  end;
end;
{$ELSE}
function RpcBindingSetAuthInfoA; external rpclib name 'RpcBindingSetAuthInfoA';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _RpcBindingSetAuthInfoW: Pointer;

function RpcBindingSetAuthInfoW;
begin
  GetProcedureAddress(_RpcBindingSetAuthInfoW, rpclib, 'RpcBindingSetAuthInfoW');
  asm
    mov esp, ebp
    pop ebp
    jmp [_RpcBindingSetAuthInfoW]
  end;
end;
{$ELSE}
function RpcBindingSetAuthInfoW; external rpclib name 'RpcBindingSetAuthInfoW';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _RpcBindingSetAuthInfoExA: Pointer;

function RpcBindingSetAuthInfoExA;
begin
  GetProcedureAddress(_RpcBindingSetAuthInfoExA, rpclib, 'RpcBindingSetAuthInfoExA');
  asm
    mov esp, ebp
    pop ebp
    jmp [_RpcBindingSetAuthInfoExA]
  end;
end;
{$ELSE}
function RpcBindingSetAuthInfoExA; external rpclib name 'RpcBindingSetAuthInfoExA';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _RpcBindingSetAuthInfoExW: Pointer;

function RpcBindingSetAuthInfoExW;
begin
  GetProcedureAddress(_RpcBindingSetAuthInfoExW, rpclib, 'RpcBindingSetAuthInfoExW');
  asm
    mov esp, ebp
    pop ebp
    jmp [_RpcBindingSetAuthInfoExW]
  end;
end;
{$ELSE}
function RpcBindingSetAuthInfoExW; external rpclib name 'RpcBindingSetAuthInfoExW';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _RpcBindingInqAuthInfoExA: Pointer;

function RpcBindingInqAuthInfoExA;
begin
  GetProcedureAddress(_RpcBindingInqAuthInfoExA, rpclib, 'RpcBindingInqAuthInfoExA');
  asm
    mov esp, ebp
    pop ebp
    jmp [_RpcBindingInqAuthInfoExA]
  end;
end;
{$ELSE}
function RpcBindingInqAuthInfoExA; external rpclib name 'RpcBindingInqAuthInfoExA';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _RpcBindingInqAuthInfoExW: Pointer;

function RpcBindingInqAuthInfoExW;
begin
  GetProcedureAddress(_RpcBindingInqAuthInfoExW, rpclib, 'RpcBindingInqAuthInfoExW');
  asm
    mov esp, ebp
    pop ebp
    jmp [_RpcBindingInqAuthInfoExW]
  end;
end;
{$ELSE}
function RpcBindingInqAuthInfoExW; external rpclib name 'RpcBindingInqAuthInfoExW';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _RpcServerRegisterAuthInfoA: Pointer;

function RpcServerRegisterAuthInfoA;
begin
  GetProcedureAddress(_RpcServerRegisterAuthInfoA, rpclib, 'RpcServerRegisterAuthInfoA');
  asm
    mov esp, ebp
    pop ebp
    jmp [_RpcServerRegisterAuthInfoA]
  end;
end;
{$ELSE}
function RpcServerRegisterAuthInfoA; external rpclib name 'RpcServerRegisterAuthInfoA';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _RpcServerRegisterAuthInfoW: Pointer;

function RpcServerRegisterAuthInfoW;
begin
  GetProcedureAddress(_RpcServerRegisterAuthInfoW, rpclib, 'RpcServerRegisterAuthInfoW');
  asm
    mov esp, ebp
    pop ebp
    jmp [_RpcServerRegisterAuthInfoW]
  end;
end;
{$ELSE}
function RpcServerRegisterAuthInfoW; external rpclib name 'RpcServerRegisterAuthInfoW';
{$ENDIF DYNAMIC_LINK}
{$IFDEF UNICODE}

{$IFDEF DYNAMIC_LINK}
var
  _RpcBindingInqAuthClient: Pointer;

function RpcBindingInqAuthClient;
begin
  GetProcedureAddress(_RpcBindingInqAuthClient, rpclib, 'RpcBindingInqAuthClientW');
  asm
    mov esp, ebp
    pop ebp
    jmp [_RpcBindingInqAuthClient]
  end;
end;
{$ELSE}
function RpcBindingInqAuthClient; external rpclib name 'RpcBindingInqAuthClientW';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _RpcBindingInqAuthClientEx: Pointer;

function RpcBindingInqAuthClientEx;
begin
  GetProcedureAddress(_RpcBindingInqAuthClientEx, rpclib, 'RpcBindingInqAuthClientExW');
  asm
    mov esp, ebp
    pop ebp
    jmp [_RpcBindingInqAuthClientEx]
  end;
end;
{$ELSE}
function RpcBindingInqAuthClientEx; external rpclib name 'RpcBindingInqAuthClientExW';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _RpcBindingInqAuthInfo: Pointer;

function RpcBindingInqAuthInfo;
begin
  GetProcedureAddress(_RpcBindingInqAuthInfo, rpclib, 'RpcBindingInqAuthInfoW');
  asm
    mov esp, ebp
    pop ebp
    jmp [_RpcBindingInqAuthInfo]
  end;
end;
{$ELSE}
function RpcBindingInqAuthInfo; external rpclib name 'RpcBindingInqAuthInfoW';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _RpcBindingSetAuthInfo: Pointer;

function RpcBindingSetAuthInfo;
begin
  GetProcedureAddress(_RpcBindingSetAuthInfo, rpclib, 'RpcBindingSetAuthInfoW');
  asm
    mov esp, ebp
    pop ebp
    jmp [_RpcBindingSetAuthInfo]
  end;
end;
{$ELSE}
function RpcBindingSetAuthInfo; external rpclib name 'RpcBindingSetAuthInfoW';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _RpcBindingSetAuthInfoEx: Pointer;

function RpcBindingSetAuthInfoEx;
begin
  GetProcedureAddress(_RpcBindingSetAuthInfoEx, rpclib, 'RpcBindingSetAuthInfoExW');
  asm
    mov esp, ebp
    pop ebp
    jmp [_RpcBindingSetAuthInfoEx]
  end;
end;
{$ELSE}
function RpcBindingSetAuthInfoEx; external rpclib name 'RpcBindingSetAuthInfoExW';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _RpcBindingInqAuthInfoEx: Pointer;

function RpcBindingInqAuthInfoEx;
begin
  GetProcedureAddress(_RpcBindingInqAuthInfoEx, rpclib, 'RpcBindingInqAuthInfoExW');
  asm
    mov esp, ebp
    pop ebp
    jmp [_RpcBindingInqAuthInfoEx]
  end;
end;
{$ELSE}
function RpcBindingInqAuthInfoEx; external rpclib name 'RpcBindingInqAuthInfoExW';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _RpcServerRegisterAuthInfo: Pointer;

function RpcServerRegisterAuthInfo;
begin
  GetProcedureAddress(_RpcServerRegisterAuthInfo, rpclib, 'RpcServerRegisterAuthInfoW');
  asm
    mov esp, ebp
    pop ebp
    jmp [_RpcServerRegisterAuthInfo]
  end;
end;
{$ELSE}
function RpcServerRegisterAuthInfo; external rpclib name 'RpcServerRegisterAuthInfoW';
{$ENDIF DYNAMIC_LINK}
{$ELSE}

{$IFDEF DYNAMIC_LINK}
var
  _RpcBindingInqAuthClient: Pointer;

function RpcBindingInqAuthClient;
begin
  GetProcedureAddress(_RpcBindingInqAuthClient, rpclib, 'RpcBindingInqAuthClientA');
  asm
    mov esp, ebp
    pop ebp
    jmp [_RpcBindingInqAuthClient]
  end;
end;
{$ELSE}
function RpcBindingInqAuthClient; external rpclib name 'RpcBindingInqAuthClientA';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _RpcBindingInqAuthClientEx: Pointer;

function RpcBindingInqAuthClientEx;
begin
  GetProcedureAddress(_RpcBindingInqAuthClientEx, rpclib, 'RpcBindingInqAuthClientExA');
  asm
    mov esp, ebp
    pop ebp
    jmp [_RpcBindingInqAuthClientEx]
  end;
end;
{$ELSE}
function RpcBindingInqAuthClientEx; external rpclib name 'RpcBindingInqAuthClientExA';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _RpcBindingInqAuthInfo: Pointer;

function RpcBindingInqAuthInfo;
begin
  GetProcedureAddress(_RpcBindingInqAuthInfo, rpclib, 'RpcBindingInqAuthInfoA');
  asm
    mov esp, ebp
    pop ebp
    jmp [_RpcBindingInqAuthInfo]
  end;
end;
{$ELSE}
function RpcBindingInqAuthInfo; external rpclib name 'RpcBindingInqAuthInfoA';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _RpcBindingSetAuthInfo: Pointer;

function RpcBindingSetAuthInfo;
begin
  GetProcedureAddress(_RpcBindingSetAuthInfo, rpclib, 'RpcBindingSetAuthInfoA');
  asm
    mov esp, ebp
    pop ebp
    jmp [_RpcBindingSetAuthInfo]
  end;
end;
{$ELSE}
function RpcBindingSetAuthInfo; external rpclib name 'RpcBindingSetAuthInfoA';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _RpcBindingSetAuthInfoEx: Pointer;

function RpcBindingSetAuthInfoEx;
begin
  GetProcedureAddress(_RpcBindingSetAuthInfoEx, rpclib, 'RpcBindingSetAuthInfoExA');
  asm
    mov esp, ebp
    pop ebp
    jmp [_RpcBindingSetAuthInfoEx]
  end;
end;
{$ELSE}
function RpcBindingSetAuthInfoEx; external rpclib name 'RpcBindingSetAuthInfoExA';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _RpcBindingInqAuthInfoEx: Pointer;

function RpcBindingInqAuthInfoEx;
begin
  GetProcedureAddress(_RpcBindingInqAuthInfoEx, rpclib, 'RpcBindingInqAuthInfoExA');
  asm
    mov esp, ebp
    pop ebp
    jmp [_RpcBindingInqAuthInfoEx]
  end;
end;
{$ELSE}
function RpcBindingInqAuthInfoEx; external rpclib name 'RpcBindingInqAuthInfoExA';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _RpcServerRegisterAuthInfo: Pointer;

function RpcServerRegisterAuthInfo;
begin
  GetProcedureAddress(_RpcServerRegisterAuthInfo, rpclib, 'RpcServerRegisterAuthInfoA');
  asm
    mov esp, ebp
    pop ebp
    jmp [_RpcServerRegisterAuthInfo]
  end;
end;
{$ELSE}
function RpcServerRegisterAuthInfo; external rpclib name 'RpcServerRegisterAuthInfoA';
{$ENDIF DYNAMIC_LINK}
{$ENDIF}

{$IFDEF DYNAMIC_LINK}
var
  _RpcBindingServerFromClient: Pointer;

function RpcBindingServerFromClient;
begin
  GetProcedureAddress(_RpcBindingServerFromClient, rpclib, 'RpcBindingServerFromClient');
  asm
    mov esp, ebp
    pop ebp
    jmp [_RpcBindingServerFromClient]
  end;
end;
{$ELSE}
function RpcBindingServerFromClient; external rpclib name 'RpcBindingServerFromClient';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _RpcRaiseException: Pointer;

procedure RpcRaiseException;
begin
  GetProcedureAddress(_RpcRaiseException, rpclib, 'RpcRaiseException');
  asm
    mov esp, ebp
    pop ebp
    jmp [_RpcRaiseException]
  end;
end;
{$ELSE}
procedure RpcRaiseException; external rpclib name 'RpcRaiseException';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _RpcTestCancel: Pointer;

function RpcTestCancel;
begin
  GetProcedureAddress(_RpcTestCancel, rpclib, 'RpcTestCancel');
  asm
    mov esp, ebp
    pop ebp
    jmp [_RpcTestCancel]
  end;
end;
{$ELSE}
function RpcTestCancel; external rpclib name 'RpcTestCancel';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _RpcServerTestCancel: Pointer;

function RpcServerTestCancel;
begin
  GetProcedureAddress(_RpcServerTestCancel, rpclib, 'RpcServerTestCancel');
  asm
    mov esp, ebp
    pop ebp
    jmp [_RpcServerTestCancel]
  end;
end;
{$ELSE}
function RpcServerTestCancel; external rpclib name 'RpcServerTestCancel';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _RpcCancelThread: Pointer;

function RpcCancelThread;
begin
  GetProcedureAddress(_RpcCancelThread, rpclib, 'RpcCancelThread');
  asm
    mov esp, ebp
    pop ebp
    jmp [_RpcCancelThread]
  end;
end;
{$ELSE}
function RpcCancelThread; external rpclib name 'RpcCancelThread';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _RpcCancelThreadEx: Pointer;

function RpcCancelThreadEx;
begin
  GetProcedureAddress(_RpcCancelThreadEx, rpclib, 'RpcCancelThreadEx');
  asm
    mov esp, ebp
    pop ebp
    jmp [_RpcCancelThreadEx]
  end;
end;
{$ELSE}
function RpcCancelThreadEx; external rpclib name 'RpcCancelThreadEx';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _UuidCreate: Pointer;

function UuidCreate;
begin
  GetProcedureAddress(_UuidCreate, rpclib, 'UuidCreate');
  asm
    mov esp, ebp
    pop ebp
    jmp [_UuidCreate]
  end;
end;
{$ELSE}
function UuidCreate; external rpclib name 'UuidCreate';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _UuidCreateSequential: Pointer;

function UuidCreateSequential;
begin
  GetProcedureAddress(_UuidCreateSequential, rpclib, 'UuidCreateSequential');
  asm
    mov esp, ebp
    pop ebp
    jmp [_UuidCreateSequential]
  end;
end;
{$ELSE}
function UuidCreateSequential; external rpclib name 'UuidCreateSequential';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _UuidFromStringA: Pointer;

function UuidFromStringA;
begin
  GetProcedureAddress(_UuidFromStringA, rpclib, 'UuidFromStringA');
  asm
    mov esp, ebp
    pop ebp
    jmp [_UuidFromStringA]
  end;
end;
{$ELSE}
function UuidFromStringA; external rpclib name 'UuidFromStringA';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _UuidFromStringW: Pointer;

function UuidFromStringW;
begin
  GetProcedureAddress(_UuidFromStringW, rpclib, 'UuidFromStringW');
  asm
    mov esp, ebp
    pop ebp
    jmp [_UuidFromStringW]
  end;
end;
{$ELSE}
function UuidFromStringW; external rpclib name 'UuidFromStringW';
{$ENDIF DYNAMIC_LINK}
{$IFDEF UNICODE}

{$IFDEF DYNAMIC_LINK}
var
  _UuidFromString: Pointer;

function UuidFromString;
begin
  GetProcedureAddress(_UuidFromString, rpclib, 'UuidFromStringW');
  asm
    mov esp, ebp
    pop ebp
    jmp [_UuidFromString]
  end;
end;
{$ELSE}
function UuidFromString; external rpclib name 'UuidFromStringW';
{$ENDIF DYNAMIC_LINK}
{$ELSE}

{$IFDEF DYNAMIC_LINK}
var
  _UuidFromString: Pointer;

function UuidFromString;
begin
  GetProcedureAddress(_UuidFromString, rpclib, 'UuidFromStringA');
  asm
    mov esp, ebp
    pop ebp
    jmp [_UuidFromString]
  end;
end;
{$ELSE}
function UuidFromString; external rpclib name 'UuidFromStringA';
{$ENDIF DYNAMIC_LINK}
{$ENDIF}

{$IFDEF DYNAMIC_LINK}
var
  _UuidToStringA: Pointer;

function UuidToStringA;
begin
  GetProcedureAddress(_UuidToStringA, rpclib, 'UuidToStringA');
  asm
    mov esp, ebp
    pop ebp
    jmp [_UuidToStringA]
  end;
end;
{$ELSE}
function UuidToStringA; external rpclib name 'UuidToStringA';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _UuidToStringW: Pointer;

function UuidToStringW;
begin
  GetProcedureAddress(_UuidToStringW, rpclib, 'UuidToStringW');
  asm
    mov esp, ebp
    pop ebp
    jmp [_UuidToStringW]
  end;
end;
{$ELSE}
function UuidToStringW; external rpclib name 'UuidToStringW';
{$ENDIF DYNAMIC_LINK}
{$IFDEF UNICODE}

{$IFDEF DYNAMIC_LINK}
var
  _UuidToString: Pointer;

function UuidToString;
begin
  GetProcedureAddress(_UuidToString, rpclib, 'UuidToStringW');
  asm
    mov esp, ebp
    pop ebp
    jmp [_UuidToString]
  end;
end;
{$ELSE}
function UuidToString; external rpclib name 'UuidToStringW';
{$ENDIF DYNAMIC_LINK}
{$ELSE}

{$IFDEF DYNAMIC_LINK}
var
  _UuidToString: Pointer;

function UuidToString;
begin
  GetProcedureAddress(_UuidToString, rpclib, 'UuidToStringA');
  asm
    mov esp, ebp
    pop ebp
    jmp [_UuidToString]
  end;
end;
{$ELSE}
function UuidToString; external rpclib name 'UuidToStringA';
{$ENDIF DYNAMIC_LINK}
{$ENDIF}

{$IFDEF DYNAMIC_LINK}
var
  _UuidCompare: Pointer;

function UuidCompare;
begin
  GetProcedureAddress(_UuidCompare, rpclib, 'UuidCompare');
  asm
    mov esp, ebp
    pop ebp
    jmp [_UuidCompare]
  end;
end;
{$ELSE}
function UuidCompare; external rpclib name 'UuidCompare';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _UuidCreateNil: Pointer;

function UuidCreateNil;
begin
  GetProcedureAddress(_UuidCreateNil, rpclib, 'UuidCreateNil');
  asm
    mov esp, ebp
    pop ebp
    jmp [_UuidCreateNil]
  end;
end;
{$ELSE}
function UuidCreateNil; external rpclib name 'UuidCreateNil';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _UuidEqual: Pointer;

function UuidEqual;
begin
  GetProcedureAddress(_UuidEqual, rpclib, 'UuidEqual');
  asm
    mov esp, ebp
    pop ebp
    jmp [_UuidEqual]
  end;
end;
{$ELSE}
function UuidEqual; external rpclib name 'UuidEqual';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _UuidHash: Pointer;

function UuidHash;
begin
  GetProcedureAddress(_UuidHash, rpclib, 'UuidHash');
  asm
    mov esp, ebp
    pop ebp
    jmp [_UuidHash]
  end;
end;
{$ELSE}
function UuidHash; external rpclib name 'UuidHash';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _UuidIsNil: Pointer;

function UuidIsNil;
begin
  GetProcedureAddress(_UuidIsNil, rpclib, 'UuidIsNil');
  asm
    mov esp, ebp
    pop ebp
    jmp [_UuidIsNil]
  end;
end;
{$ELSE}
function UuidIsNil; external rpclib name 'UuidIsNil';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _RpcEpRegisterNoReplaceA: Pointer;

function RpcEpRegisterNoReplaceA;
begin
  GetProcedureAddress(_RpcEpRegisterNoReplaceA, rpclib, 'RpcEpRegisterNoReplaceA');
  asm
    mov esp, ebp
    pop ebp
    jmp [_RpcEpRegisterNoReplaceA]
  end;
end;
{$ELSE}
function RpcEpRegisterNoReplaceA; external rpclib name 'RpcEpRegisterNoReplaceA';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _RpcEpRegisterNoReplaceW: Pointer;

function RpcEpRegisterNoReplaceW;
begin
  GetProcedureAddress(_RpcEpRegisterNoReplaceW, rpclib, 'RpcEpRegisterNoReplaceW');
  asm
    mov esp, ebp
    pop ebp
    jmp [_RpcEpRegisterNoReplaceW]
  end;
end;
{$ELSE}
function RpcEpRegisterNoReplaceW; external rpclib name 'RpcEpRegisterNoReplaceW';
{$ENDIF DYNAMIC_LINK}
{$IFDEF UNICODE}

{$IFDEF DYNAMIC_LINK}
var
  _RpcEpRegisterNoReplace: Pointer;

function RpcEpRegisterNoReplace;
begin
  GetProcedureAddress(_RpcEpRegisterNoReplace, rpclib, 'RpcEpRegisterNoReplaceW');
  asm
    mov esp, ebp
    pop ebp
    jmp [_RpcEpRegisterNoReplace]
  end;
end;
{$ELSE}
function RpcEpRegisterNoReplace; external rpclib name 'RpcEpRegisterNoReplaceW';
{$ENDIF DYNAMIC_LINK}
{$ELSE}

{$IFDEF DYNAMIC_LINK}
var
  _RpcEpRegisterNoReplace: Pointer;

function RpcEpRegisterNoReplace;
begin
  GetProcedureAddress(_RpcEpRegisterNoReplace, rpclib, 'RpcEpRegisterNoReplaceA');
  asm
    mov esp, ebp
    pop ebp
    jmp [_RpcEpRegisterNoReplace]
  end;
end;
{$ELSE}
function RpcEpRegisterNoReplace; external rpclib name 'RpcEpRegisterNoReplaceA';
{$ENDIF DYNAMIC_LINK}
{$ENDIF}

{$IFDEF DYNAMIC_LINK}
var
  _RpcEpRegisterA: Pointer;

function RpcEpRegisterA;
begin
  GetProcedureAddress(_RpcEpRegisterA, rpclib, 'RpcEpRegisterA');
  asm
    mov esp, ebp
    pop ebp
    jmp [_RpcEpRegisterA]
  end;
end;
{$ELSE}
function RpcEpRegisterA; external rpclib name 'RpcEpRegisterA';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _RpcEpRegisterW: Pointer;

function RpcEpRegisterW;
begin
  GetProcedureAddress(_RpcEpRegisterW, rpclib, 'RpcEpRegisterW');
  asm
    mov esp, ebp
    pop ebp
    jmp [_RpcEpRegisterW]
  end;
end;
{$ELSE}
function RpcEpRegisterW; external rpclib name 'RpcEpRegisterW';
{$ENDIF DYNAMIC_LINK}
{$IFDEF UNICODE}

{$IFDEF DYNAMIC_LINK}
var
  _RpcEpRegister: Pointer;

function RpcEpRegister;
begin
  GetProcedureAddress(_RpcEpRegister, rpclib, 'RpcEpRegisterW');
  asm
    mov esp, ebp
    pop ebp
    jmp [_RpcEpRegister]
  end;
end;
{$ELSE}
function RpcEpRegister; external rpclib name 'RpcEpRegisterW';
{$ENDIF DYNAMIC_LINK}
{$ELSE}

{$IFDEF DYNAMIC_LINK}
var
  _RpcEpRegister: Pointer;

function RpcEpRegister;
begin
  GetProcedureAddress(_RpcEpRegister, rpclib, 'RpcEpRegisterA');
  asm
    mov esp, ebp
    pop ebp
    jmp [_RpcEpRegister]
  end;
end;
{$ELSE}
function RpcEpRegister; external rpclib name 'RpcEpRegisterA';
{$ENDIF DYNAMIC_LINK}
{$ENDIF}

{$IFDEF DYNAMIC_LINK}
var
  _RpcEpUnregister: Pointer;

function RpcEpUnregister;
begin
  GetProcedureAddress(_RpcEpUnregister, rpclib, 'RpcEpUnregister');
  asm
    mov esp, ebp
    pop ebp
    jmp [_RpcEpUnregister]
  end;
end;
{$ELSE}
function RpcEpUnregister; external rpclib name 'RpcEpUnregister';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _DceErrorInqTextA: Pointer;

function DceErrorInqTextA;
begin
  GetProcedureAddress(_DceErrorInqTextA, rpclib, 'DceErrorInqTextA');
  asm
    mov esp, ebp
    pop ebp
    jmp [_DceErrorInqTextA]
  end;
end;
{$ELSE}
function DceErrorInqTextA; external rpclib name 'DceErrorInqTextA';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _DceErrorInqTextW: Pointer;

function DceErrorInqTextW;
begin
  GetProcedureAddress(_DceErrorInqTextW, rpclib, 'DceErrorInqTextW');
  asm
    mov esp, ebp
    pop ebp
    jmp [_DceErrorInqTextW]
  end;
end;
{$ELSE}
function DceErrorInqTextW; external rpclib name 'DceErrorInqTextW';
{$ENDIF DYNAMIC_LINK}
{$IFDEF UNICODE}

{$IFDEF DYNAMIC_LINK}
var
  _DceErrorInqText: Pointer;

function DceErrorInqText;
begin
  GetProcedureAddress(_DceErrorInqText, rpclib, 'DceErrorInqTextW');
  asm
    mov esp, ebp
    pop ebp
    jmp [_DceErrorInqText]
  end;
end;
{$ELSE}
function DceErrorInqText; external rpclib name 'DceErrorInqTextW';
{$ENDIF DYNAMIC_LINK}
{$ELSE}

{$IFDEF DYNAMIC_LINK}
var
  _DceErrorInqText: Pointer;

function DceErrorInqText;
begin
  GetProcedureAddress(_DceErrorInqText, rpclib, 'DceErrorInqTextA');
  asm
    mov esp, ebp
    pop ebp
    jmp [_DceErrorInqText]
  end;
end;
{$ELSE}
function DceErrorInqText; external rpclib name 'DceErrorInqTextA';
{$ENDIF DYNAMIC_LINK}
{$ENDIF}

{$IFDEF DYNAMIC_LINK}
var
  _RpcMgmtEpEltInqBegin: Pointer;

function RpcMgmtEpEltInqBegin;
begin
  GetProcedureAddress(_RpcMgmtEpEltInqBegin, rpclib, 'RpcMgmtEpEltInqBegin');
  asm
    mov esp, ebp
    pop ebp
    jmp [_RpcMgmtEpEltInqBegin]
  end;
end;
{$ELSE}
function RpcMgmtEpEltInqBegin; external rpclib name 'RpcMgmtEpEltInqBegin';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _RpcMgmtEpEltInqDone: Pointer;

function RpcMgmtEpEltInqDone;
begin
  GetProcedureAddress(_RpcMgmtEpEltInqDone, rpclib, 'RpcMgmtEpEltInqDone');
  asm
    mov esp, ebp
    pop ebp
    jmp [_RpcMgmtEpEltInqDone]
  end;
end;
{$ELSE}
function RpcMgmtEpEltInqDone; external rpclib name 'RpcMgmtEpEltInqDone';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _RpcMgmtEpEltInqNextA: Pointer;

function RpcMgmtEpEltInqNextA;
begin
  GetProcedureAddress(_RpcMgmtEpEltInqNextA, rpclib, 'RpcMgmtEpEltInqNextA');
  asm
    mov esp, ebp
    pop ebp
    jmp [_RpcMgmtEpEltInqNextA]
  end;
end;
{$ELSE}
function RpcMgmtEpEltInqNextA; external rpclib name 'RpcMgmtEpEltInqNextA';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _RpcMgmtEpEltInqNextW: Pointer;

function RpcMgmtEpEltInqNextW;
begin
  GetProcedureAddress(_RpcMgmtEpEltInqNextW, rpclib, 'RpcMgmtEpEltInqNextW');
  asm
    mov esp, ebp
    pop ebp
    jmp [_RpcMgmtEpEltInqNextW]
  end;
end;
{$ELSE}
function RpcMgmtEpEltInqNextW; external rpclib name 'RpcMgmtEpEltInqNextW';
{$ENDIF DYNAMIC_LINK}
{$IFDEF UNICODE}

{$IFDEF DYNAMIC_LINK}
var
  _RpcMgmtEpEltInqNext: Pointer;

function RpcMgmtEpEltInqNext;
begin
  GetProcedureAddress(_RpcMgmtEpEltInqNext, rpclib, 'RpcMgmtEpEltInqNextW');
  asm
    mov esp, ebp
    pop ebp
    jmp [_RpcMgmtEpEltInqNext]
  end;
end;
{$ELSE}
function RpcMgmtEpEltInqNext; external rpclib name 'RpcMgmtEpEltInqNextW';
{$ENDIF DYNAMIC_LINK}
{$ELSE}

{$IFDEF DYNAMIC_LINK}
var
  _RpcMgmtEpEltInqNext: Pointer;

function RpcMgmtEpEltInqNext;
begin
  GetProcedureAddress(_RpcMgmtEpEltInqNext, rpclib, 'RpcMgmtEpEltInqNextA');
  asm
    mov esp, ebp
    pop ebp
    jmp [_RpcMgmtEpEltInqNext]
  end;
end;
{$ELSE}
function RpcMgmtEpEltInqNext; external rpclib name 'RpcMgmtEpEltInqNextA';
{$ENDIF DYNAMIC_LINK}
{$ENDIF}

{$IFDEF DYNAMIC_LINK}
var
  _RpcMgmtEpUnregister: Pointer;

function RpcMgmtEpUnregister;
begin
  GetProcedureAddress(_RpcMgmtEpUnregister, rpclib, 'RpcMgmtEpUnregister');
  asm
    mov esp, ebp
    pop ebp
    jmp [_RpcMgmtEpUnregister]
  end;
end;
{$ELSE}
function RpcMgmtEpUnregister; external rpclib name 'RpcMgmtEpUnregister';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _RpcMgmtSetAuthorizationFn: Pointer;

function RpcMgmtSetAuthorizationFn;
begin
  GetProcedureAddress(_RpcMgmtSetAuthorizationFn, rpclib, 'RpcMgmtSetAuthorizationFn');
  asm
    mov esp, ebp
    pop ebp
    jmp [_RpcMgmtSetAuthorizationFn]
  end;
end;
{$ELSE}
function RpcMgmtSetAuthorizationFn; external rpclib name 'RpcMgmtSetAuthorizationFn';
{$ENDIF DYNAMIC_LINK}

end.
