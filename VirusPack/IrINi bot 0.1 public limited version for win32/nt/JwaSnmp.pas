{******************************************************************************}
{                                                       	               }
{ Simple Network Management Protocol API interface Unit for Object Pascal      }
{                                                       	               }
{ Portions created by Microsoft are Copyright (C) 1995-2001 Microsoft          }
{ Corporation. All Rights Reserved.                                            }
{ 								               }
{ The original file is: snmp.h, released October 2001. The original Pascal     }
{ code is: SNMP.pas, released October 2001. The initial developer of the       }
{ Pascal code is Petr Vones (petr.v@mujmail.cz).                               }
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

unit JwaSnmp;

{$WEAKPACKAGEUNIT}

{$HPPEMIT ''}
{$HPPEMIT '#include "snmp.h"'}
{$HPPEMIT ''}

{$I WINDEFINES.INC}

interface

uses
  JwaWinType;

type
  PAsnOctetString = ^TAsnOctetString;
  TAsnOctetString = record
    stream: PChar;
    length: UINT;
    dynamic_: BOOL;
  end;
  {$EXTERNALSYM TAsnOctetString}

  PAsnObjectIdentifier = ^TAsnObjectIdentifier;
  TAsnObjectIdentifier = record
    idLength: UINT;
    ids: PUINT;
  end;
  {$EXTERNALSYM TAsnObjectIdentifier}

  TAsnInteger32        = LONG;
  {$EXTERNALSYM TAsnInteger32}
  TAsnUnsigned32       = ULONG;
  {$EXTERNALSYM TAsnUnsigned32}
  TAsnCounter64        = ULARGE_INTEGER;
  {$EXTERNALSYM TAsnCounter64}
  TAsnCounter32        = TAsnUnsigned32;
  {$EXTERNALSYM TAsnCounter32}
  TAsnGauge32          = TAsnUnsigned32;
  {$EXTERNALSYM TAsnGauge32}
  TAsnTimeticks        = TAsnUnsigned32;
  {$EXTERNALSYM TAsnTimeticks}
  TAsnBits             = TAsnOctetString;
  {$EXTERNALSYM TAsnBits}
  TAsnSequence         = TAsnOctetString;
  {$EXTERNALSYM TAsnSequence}
  TAsnImplicitSequence = TAsnOctetString;
  {$EXTERNALSYM TAsnImplicitSequence}
  TAsnIPAddress        = TAsnOctetString;
  {$EXTERNALSYM TAsnIPAddress}
  TAsnNetworkAddress   = TAsnOctetString;
  {$EXTERNALSYM TAsnNetworkAddress}
  TAsnDisplayString    = TAsnOctetString;
  {$EXTERNALSYM TAsnDisplayString}
  TAsnOpaque           = TAsnOctetString;
  {$EXTERNALSYM TAsnOpaque}

  PAsnAny = ^TAsnAny;
  TAsnAny = record
    asnType: Byte;
    case Integer of
      0: (number: TAsnInteger32);          // ASN_INTEGER, ASN_INTEGER32
      1: (unsigned32: TAsnUnsigned32);     // ASN_UNSIGNED32
      2: (counter64: TAsnCounter64);       // ASN_COUNTER64
      3: (string_: TAsnOctetString);       // ASN_OCTETSTRING
      4: (bits: TAsnBits);                 // ASN_BITS
      5: (object_: TAsnObjectIdentifier);  // ASN_OBJECTIDENTIFIER
      6: (sequence: TAsnSequence);         // ASN_SEQUENCE
      7: (address: TAsnIPAddress);         // ASN_IPADDRESS
      8: (counter: TAsnCounter32);         // ASN_COUNTER32
      9: (gauge: TAsnGauge32);             // ASN_GAUGE32
     10: (ticks: TAsnTimeticks);           // ASN_TIMETICKS
     11: (arbitrary: TAsnOpaque);          // ASN_OPAQUE
  end;
  {$EXTERNALSYM TAsnAny}

  TAsnObjectName = TAsnObjectIdentifier;
  {$EXTERNALSYM TAsnObjectName}
  TAsnObjectSyntax = TAsnAny;
  {$EXTERNALSYM TAsnObjectSyntax}

  PSnmpVarBind = ^TSnmpVarBind;
  TSnmpVarBind = record
    name: TAsnObjectName;
    value: TAsnObjectSyntax;
  end;
  {$EXTERNALSYM TSnmpVarBind}

  PSnmpVarBindList = ^TSnmpVarBindList;
  TSnmpVarBindList = record
    list: PSnmpVarBind;
    len: UINT;
  end;
  {$EXTERNALSYM TSnmpVarBindList}

const

{$IFNDEF _INC_WINSNMP}

{ ASN/BER Base Types }

  ASN_UNIVERSAL                   = $00;
  {$EXTERNALSYM ASN_UNIVERSAL}
  ASN_APPLICATION                 = $40;
  {$EXTERNALSYM ASN_APPLICATION}
  ASN_CONTEXT                     = $80;
  {$EXTERNALSYM ASN_CONTEXT}
  ASN_PRIVATE                     = $C0;
  {$EXTERNALSYM ASN_PRIVATE}

  ASN_PRIMITIVE                   = $00;
  {$EXTERNALSYM ASN_PRIMITIVE}
  ASN_CONSTRUCTOR                 = $20;
  {$EXTERNALSYM ASN_CONSTRUCTOR}

{ PDU Type Values }

  SNMP_PDU_GET                    = (ASN_CONTEXT or ASN_CONSTRUCTOR or $0);
  {$EXTERNALSYM SNMP_PDU_GET}
  SNMP_PDU_GETNEXT                = (ASN_CONTEXT or ASN_CONSTRUCTOR or $1);
  {$EXTERNALSYM SNMP_PDU_GETNEXT}
  SNMP_PDU_RESPONSE               = (ASN_CONTEXT or ASN_CONSTRUCTOR or $2);
  {$EXTERNALSYM SNMP_PDU_RESPONSE}
  SNMP_PDU_SET                    = (ASN_CONTEXT or ASN_CONSTRUCTOR or $3);
  {$EXTERNALSYM SNMP_PDU_SET}
  SNMP_PDU_V1TRAP                 = (ASN_CONTEXT or ASN_CONSTRUCTOR or $4);
  {$EXTERNALSYM SNMP_PDU_V1TRAP}
  SNMP_PDU_GETBULK                = (ASN_CONTEXT or ASN_CONSTRUCTOR or $5);
  {$EXTERNALSYM SNMP_PDU_GETBULK}
  SNMP_PDU_INFORM                 = (ASN_CONTEXT or ASN_CONSTRUCTOR or $6);
  {$EXTERNALSYM SNMP_PDU_INFORM}
  SNMP_PDU_TRAP                   = (ASN_CONTEXT or ASN_CONSTRUCTOR or $7);
  {$EXTERNALSYM SNMP_PDU_TRAP}

{$ENDIF _INC_WINSNMP}

{ SNMP Simple Syntax Values }

  ASN_INTEGER                     = (ASN_UNIVERSAL or ASN_PRIMITIVE or $02);
  {$EXTERNALSYM ASN_INTEGER}
  ASN_BITS                        = (ASN_UNIVERSAL or ASN_PRIMITIVE or $03);
  {$EXTERNALSYM ASN_BITS}
  ASN_OCTETSTRING                 = (ASN_UNIVERSAL or ASN_PRIMITIVE or $04);
  {$EXTERNALSYM ASN_OCTETSTRING}
  ASN_NULL                        = (ASN_UNIVERSAL or ASN_PRIMITIVE or $05);
  {$EXTERNALSYM ASN_NULL}
  ASN_OBJECTIDENTIFIER            = (ASN_UNIVERSAL or ASN_PRIMITIVE or $06);
  {$EXTERNALSYM ASN_OBJECTIDENTIFIER}
  ASN_INTEGER32                   = ASN_INTEGER;
  {$EXTERNALSYM ASN_INTEGER32}

{ SNMP Constructor Syntax Values }

  ASN_SEQUENCE                    = (ASN_UNIVERSAL or ASN_CONSTRUCTOR or $10);
  {$EXTERNALSYM ASN_SEQUENCE}
  ASN_SEQUENCEOF                  = ASN_SEQUENCE;
  {$EXTERNALSYM ASN_SEQUENCEOF}

{ SNMP Application Syntax Values }

  ASN_IPADDRESS                   = (ASN_APPLICATION or ASN_PRIMITIVE or $00);
  {$EXTERNALSYM ASN_IPADDRESS}
  ASN_COUNTER32                   = (ASN_APPLICATION or ASN_PRIMITIVE or $01);
  {$EXTERNALSYM ASN_COUNTER32}
  ASN_GAUGE32                     = (ASN_APPLICATION or ASN_PRIMITIVE or $02);
  {$EXTERNALSYM ASN_GAUGE32}
  ASN_TIMETICKS                   = (ASN_APPLICATION or ASN_PRIMITIVE or $03);
  {$EXTERNALSYM ASN_TIMETICKS}
  ASN_OPAQUE                      = (ASN_APPLICATION or ASN_PRIMITIVE or $04);
  {$EXTERNALSYM ASN_OPAQUE}
  ASN_COUNTER64                   = (ASN_APPLICATION or ASN_PRIMITIVE or $06);
  {$EXTERNALSYM ASN_COUNTER64}
  ASN_UINTEGER32                  = (ASN_APPLICATION or ASN_PRIMITIVE or $07);
  {$EXTERNALSYM ASN_UINTEGER32}
  ASN_RFC2578_UNSIGNED32          = ASN_GAUGE32;
  {$EXTERNALSYM ASN_RFC2578_UNSIGNED32}

{ SNMP Exception Conditions }

  SNMP_EXCEPTION_NOSUCHOBJECT     = (ASN_CONTEXT or ASN_PRIMITIVE or $00);
  {$EXTERNALSYM SNMP_EXCEPTION_NOSUCHOBJECT}
  SNMP_EXCEPTION_NOSUCHINSTANCE   = (ASN_CONTEXT or ASN_PRIMITIVE or $01);
  {$EXTERNALSYM SNMP_EXCEPTION_NOSUCHINSTANCE}
  SNMP_EXCEPTION_ENDOFMIBVIEW     = (ASN_CONTEXT or ASN_PRIMITIVE or $02);
  {$EXTERNALSYM SNMP_EXCEPTION_ENDOFMIBVIEW}

{ SNMP Request Types (used in SnmpExtensionQueryEx) }

  SNMP_EXTENSION_GET              = SNMP_PDU_GET;
  {$EXTERNALSYM SNMP_EXTENSION_GET}
  SNMP_EXTENSION_GET_NEXT         = SNMP_PDU_GETNEXT;
  {$EXTERNALSYM SNMP_EXTENSION_GET_NEXT}
  SNMP_EXTENSION_GET_BULK         = SNMP_PDU_GETBULK;
  {$EXTERNALSYM SNMP_EXTENSION_GET_BULK}
  SNMP_EXTENSION_SET_TEST         = (ASN_PRIVATE or ASN_CONSTRUCTOR or $0);
  {$EXTERNALSYM SNMP_EXTENSION_SET_TEST}
  SNMP_EXTENSION_SET_COMMIT       = SNMP_PDU_SET;
  {$EXTERNALSYM SNMP_EXTENSION_SET_COMMIT}
  SNMP_EXTENSION_SET_UNDO         = (ASN_PRIVATE or ASN_CONSTRUCTOR or $1);
  {$EXTERNALSYM SNMP_EXTENSION_SET_UNDO}
  SNMP_EXTENSION_SET_CLEANUP      = (ASN_PRIVATE or ASN_CONSTRUCTOR or $2);
  {$EXTERNALSYM SNMP_EXTENSION_SET_CLEANUP}

{ SNMP Error Codes }

  SNMP_ERRORSTATUS_NOERROR                    = 0;
  {$EXTERNALSYM SNMP_ERRORSTATUS_NOERROR}
  SNMP_ERRORSTATUS_TOOBIG                     = 1;
  {$EXTERNALSYM SNMP_ERRORSTATUS_TOOBIG}
  SNMP_ERRORSTATUS_NOSUCHNAME                 = 2;
  {$EXTERNALSYM SNMP_ERRORSTATUS_NOSUCHNAME}
  SNMP_ERRORSTATUS_BADVALUE                   = 3;
  {$EXTERNALSYM SNMP_ERRORSTATUS_BADVALUE}
  SNMP_ERRORSTATUS_READONLY                   = 4;
  {$EXTERNALSYM SNMP_ERRORSTATUS_READONLY}
  SNMP_ERRORSTATUS_GENERR                     = 5;
  {$EXTERNALSYM SNMP_ERRORSTATUS_GENERR}
  SNMP_ERRORSTATUS_NOACCESS                   = 6;
  {$EXTERNALSYM SNMP_ERRORSTATUS_NOACCESS}
  SNMP_ERRORSTATUS_WRONGTYPE                  = 7;
  {$EXTERNALSYM SNMP_ERRORSTATUS_WRONGTYPE}
  SNMP_ERRORSTATUS_WRONGLENGTH                = 8;
  {$EXTERNALSYM SNMP_ERRORSTATUS_WRONGLENGTH}
  SNMP_ERRORSTATUS_WRONGENCODING              = 9;
  {$EXTERNALSYM SNMP_ERRORSTATUS_WRONGENCODING}
  SNMP_ERRORSTATUS_WRONGVALUE                 = 10;
  {$EXTERNALSYM SNMP_ERRORSTATUS_WRONGVALUE}
  SNMP_ERRORSTATUS_NOCREATION                 = 11;
  {$EXTERNALSYM SNMP_ERRORSTATUS_NOCREATION}
  SNMP_ERRORSTATUS_INCONSISTENTVALUE          = 12;
  {$EXTERNALSYM SNMP_ERRORSTATUS_INCONSISTENTVALUE}
  SNMP_ERRORSTATUS_RESOURCEUNAVAILABLE        = 13;
  {$EXTERNALSYM SNMP_ERRORSTATUS_RESOURCEUNAVAILABLE}
  SNMP_ERRORSTATUS_COMMITFAILED               = 14;
  {$EXTERNALSYM SNMP_ERRORSTATUS_COMMITFAILED}
  SNMP_ERRORSTATUS_UNDOFAILED                 = 15;
  {$EXTERNALSYM SNMP_ERRORSTATUS_UNDOFAILED}
  SNMP_ERRORSTATUS_AUTHORIZATIONERROR         = 16;
  {$EXTERNALSYM SNMP_ERRORSTATUS_AUTHORIZATIONERROR}
  SNMP_ERRORSTATUS_NOTWRITABLE                = 17;
  {$EXTERNALSYM SNMP_ERRORSTATUS_NOTWRITABLE}
  SNMP_ERRORSTATUS_INCONSISTENTNAME           = 18;
  {$EXTERNALSYM SNMP_ERRORSTATUS_INCONSISTENTNAME}

{ SNMPv1 Trap Types }

  SNMP_GENERICTRAP_COLDSTART                  = 0;
  {$EXTERNALSYM SNMP_GENERICTRAP_COLDSTART}
  SNMP_GENERICTRAP_WARMSTART                  = 1;
  {$EXTERNALSYM SNMP_GENERICTRAP_WARMSTART}
  SNMP_GENERICTRAP_LINKDOWN                   = 2;
  {$EXTERNALSYM SNMP_GENERICTRAP_LINKDOWN}
  SNMP_GENERICTRAP_LINKUP                     = 3;
  {$EXTERNALSYM SNMP_GENERICTRAP_LINKUP}
  SNMP_GENERICTRAP_AUTHFAILURE                = 4;
  {$EXTERNALSYM SNMP_GENERICTRAP_AUTHFAILURE}
  SNMP_GENERICTRAP_EGPNEIGHLOSS               = 5;
  {$EXTERNALSYM SNMP_GENERICTRAP_EGPNEIGHLOSS}
  SNMP_GENERICTRAP_ENTERSPECIFIC              = 6;
  {$EXTERNALSYM SNMP_GENERICTRAP_ENTERSPECIFIC}

{ SNMP Access Types }

  SNMP_ACCESS_NONE                            = 0;
  {$EXTERNALSYM SNMP_ACCESS_NONE}
  SNMP_ACCESS_NOTIFY                          = 1;
  {$EXTERNALSYM SNMP_ACCESS_NOTIFY}
  SNMP_ACCESS_READ_ONLY                       = 2;
  {$EXTERNALSYM SNMP_ACCESS_READ_ONLY}
  SNMP_ACCESS_READ_WRITE                      = 3;
  {$EXTERNALSYM SNMP_ACCESS_READ_WRITE}
  SNMP_ACCESS_READ_CREATE                     = 4;
  {$EXTERNALSYM SNMP_ACCESS_READ_CREATE}

{ SNMP API Return Code Definitions }

type
  SNMPAPI = Integer;
  {$EXTERNALSYM SNMPAPI}

const
  SNMPAPI_NOERROR = True;
  {$EXTERNALSYM SNMPAPI_NOERROR}
  SNMPAPI_ERROR = False;
  {$EXTERNALSYM SNMPAPI_ERROR}

{ SNMP Extension API Type Definitions }

type
  TSnmpExtensionInit = function (dwUptimeReference: DWORD; var phSubagentTrapEvent: HANDLE;
    var pFirstSupportedRegion: PAsnObjectIdentifier): BOOL; stdcall;

  TSnmpExtensionInitEx = function (var pNextSupportedRegion: PAsnObjectIdentifier): BOOL; stdcall;

  TSnmpExtensionMonitor = function (pAgentMgmtData: LPVOID): BOOL; stdcall;

  TSnmpExtensionQuery = function (bPduType: Byte; var pVarBindList: TSnmpVarBindList;
    var pErrorStatus: TAsnInteger32; var pErrorIndex: TAsnInteger32): BOOL; stdcall;

  TSnmpExtensionQueryEx = function (nRequestType: UINT; nTransactionId: UINT; var pVarBindList: PSnmpVarBindList;
    var pContextInfo: PAsnOctetString; var pErrorStatus: TAsnInteger32; var pErrorIndex: TAsnInteger32): BOOL; stdcall;

  TSnmpExtensionTrap = function (pEnterpriseOid: PAsnObjectIdentifier; var pGenericTrapId: TAsnInteger32;
     var pSpecificTrapId: TAsnInteger32; var pTimeStamp: TAsnTimeticks; var pVarBindList: PSnmpVarBindList): BOOL; stdcall;

  TSnmpExtensionClose = procedure; stdcall;

{ SNMP API Prototypes }

function SnmpUtilOidCpy(pOidDst: PAsnObjectIdentifier; pOidSrc: PAsnObjectIdentifier): SNMPAPI; stdcall;
{$EXTERNALSYM SnmpUtilOidCpy}
function SnmpUtilOidAppend(pOidDst: PAsnObjectIdentifier; pOidSrc: PAsnObjectIdentifier): SNMPAPI; stdcall;
{$EXTERNALSYM SnmpUtilOidAppend}
function SnmpUtilOidNCmp(pOid1, pOid2: PAsnObjectIdentifier; nSubIds: UINT): SNMPAPI; stdcall;
{$EXTERNALSYM SnmpUtilOidNCmp}
function SnmpUtilOidCmp(pOid1, pOid2: PAsnObjectIdentifier): SNMPAPI; stdcall;
{$EXTERNALSYM SnmpUtilOidCmp}
procedure SnmpUtilOidFree(pOid: TAsnObjectIdentifier); stdcall;
{$EXTERNALSYM SnmpUtilOidFree}
function SnmpUtilOctetsCmp(pOctets1, pOctets2: PAsnOctetString): SNMPAPI; stdcall;
{$EXTERNALSYM SnmpUtilOctetsCmp}
function SnmpUtilOctetsNCmp(pOctets1, pOctets2: PAsnOctetString; nChars: UINT): SNMPAPI; stdcall;
{$EXTERNALSYM SnmpUtilOctetsNCmp}
function SnmpUtilOctetsCpy(pOctetsDst, pOctetsSrc: PAsnOctetString): SNMPAPI; stdcall;
{$EXTERNALSYM SnmpUtilOctetsCpy}
procedure SnmpUtilOctetsFree(pOctets: PAsnOctetString); stdcall;
{$EXTERNALSYM SnmpUtilOctetsFree}
function SnmpUtilAsnAnyCpy(pAnyDst, pAnySrc: PAsnAny): SNMPAPI; stdcall;
{$EXTERNALSYM SnmpUtilAsnAnyCpy}
procedure SnmpUtilAsnAnyFree(pAny: PAsnAny); stdcall;
{$EXTERNALSYM SnmpUtilAsnAnyFree}
function SnmpUtilVarBindCpy(pVbDst: PSnmpVarBind; pVbSrc: PSnmpVarBind): SNMPAPI; stdcall;
{$EXTERNALSYM SnmpUtilVarBindCpy}
procedure SnmpUtilVarBindFree(pVb: PSnmpVarBind); stdcall;
{$EXTERNALSYM SnmpUtilVarBindFree}
function SnmpUtilVarBindListCpy(pVblDst: PSnmpVarBindList; pVblSrc: PSnmpVarBindList): SNMPAPI; stdcall;
{$EXTERNALSYM SnmpUtilVarBindListCpy}
procedure SnmpUtilVarBindListFree(pVbl: PSnmpVarBindList); stdcall;
{$EXTERNALSYM SnmpUtilVarBindListFree}
procedure SnmpUtilMemFree(pMem: LPVOID); stdcall;
{$EXTERNALSYM SnmpUtilMemFree}
function SnmpUtilMemAlloc(nBytes: UINT): LPVOID; stdcall;
{$EXTERNALSYM SnmpUtilMemAlloc}
function SnmpUtilMemReAlloc(pMem: LPVOID; nBytes: UINT): LPVOID; stdcall;
{$EXTERNALSYM SnmpUtilMemReAlloc}
function SnmpUtilOidToA(Oid: PAsnObjectIdentifier): LPSTR; stdcall;
{$EXTERNALSYM SnmpUtilOidToA}
function SnmpUtilIdsToA(Ids: PUINT; IdLength: UINT): LPSTR; stdcall;
{$EXTERNALSYM SnmpUtilIdsToA}
procedure SnmpUtilPrintOid(Oid: PAsnObjectIdentifier); stdcall;
{$EXTERNALSYM SnmpUtilPrintOid}
procedure SnmpUtilPrintAsnAny(pAny: PAsnAny); stdcall;
{$EXTERNALSYM SnmpUtilPrintAsnAny}
function SnmpSvcGetUptime: DWORD; stdcall;
{$EXTERNALSYM SnmpSvcGetUptime}
procedure SnmpSvcSetLogLevel(nLogLevel: INT); stdcall;
{$EXTERNALSYM SnmpSvcSetLogLevel}
procedure SnmpSvcSetLogType(nLogType: INT); stdcall;
{$EXTERNALSYM SnmpSvcSetLogType}

{ SNMP Debugging Definitions }

const
  SNMP_LOG_SILENT                 = $0;
  {$EXTERNALSYM SNMP_LOG_SILENT}
  SNMP_LOG_FATAL                  = $1;
  {$EXTERNALSYM SNMP_LOG_FATAL}
  SNMP_LOG_ERROR                  = $2;
  {$EXTERNALSYM SNMP_LOG_ERROR}
  SNMP_LOG_WARNING                = $3;
  {$EXTERNALSYM SNMP_LOG_WARNING}
  SNMP_LOG_TRACE                  = $4;
  {$EXTERNALSYM SNMP_LOG_TRACE}
  SNMP_LOG_VERBOSE                = $5;
  {$EXTERNALSYM SNMP_LOG_VERBOSE}

  SNMP_OUTPUT_TO_CONSOLE          = $1;
  {$EXTERNALSYM SNMP_OUTPUT_TO_CONSOLE}
  SNMP_OUTPUT_TO_LOGFILE          = $2;
  {$EXTERNALSYM SNMP_OUTPUT_TO_LOGFILE}
  SNMP_OUTPUT_TO_EVENTLOG         = $4;  // no longer supported
  {$EXTERNALSYM SNMP_OUTPUT_TO_EVENTLOG}
  SNMP_OUTPUT_TO_DEBUGGER         = $8;
  {$EXTERNALSYM SNMP_OUTPUT_TO_DEBUGGER}

{ SNMP Debugging Prototypes }

procedure SnmpUtilDbgPrint(nLogLevel: INT; szFormat: LPSTR); stdcall;
{$EXTERNALSYM SnmpUtilDbgPrint}

{ Miscellaneous definitions }

const
  DEFINE_NULLOID: TAsnObjectIdentifier = (idLength: 0; ids: nil);
  {$EXTERNALSYM DEFINE_NULLOID}
  DEFINE_NULLOCTETS: TAsnOctetString = (stream: nil; length: 0; dynamic_: False);
  {$EXTERNALSYM DEFINE_NULLOCTETS}

  DEFAULT_SNMP_PORT_UDP       = 161;
  {$EXTERNALSYM DEFAULT_SNMP_PORT_UDP}
  DEFAULT_SNMP_PORT_IPX       = 36879;
  {$EXTERNALSYM DEFAULT_SNMP_PORT_IPX}
  DEFAULT_SNMPTRAP_PORT_UDP   = 162;
  {$EXTERNALSYM DEFAULT_SNMPTRAP_PORT_UDP}
  DEFAULT_SNMPTRAP_PORT_IPX   = 36880;
  {$EXTERNALSYM DEFAULT_SNMPTRAP_PORT_IPX}
  SNMP_MAX_OID_LEN            = 128;
  {$EXTERNALSYM SNMP_MAX_OID_LEN}

{ API Error Code Definitions }

  SNMP_MEM_ALLOC_ERROR            = 1;
  {$EXTERNALSYM SNMP_MEM_ALLOC_ERROR}
  SNMP_BERAPI_INVALID_LENGTH      = 10;
  {$EXTERNALSYM SNMP_BERAPI_INVALID_LENGTH}
  SNMP_BERAPI_INVALID_TAG         = 11;
  {$EXTERNALSYM SNMP_BERAPI_INVALID_TAG}
  SNMP_BERAPI_OVERFLOW            = 12;
  {$EXTERNALSYM SNMP_BERAPI_OVERFLOW}
  SNMP_BERAPI_SHORT_BUFFER        = 13;
  {$EXTERNALSYM SNMP_BERAPI_SHORT_BUFFER}
  SNMP_BERAPI_INVALID_OBJELEM     = 14;
  {$EXTERNALSYM SNMP_BERAPI_INVALID_OBJELEM}
  SNMP_PDUAPI_UNRECOGNIZED_PDU    = 20;
  {$EXTERNALSYM SNMP_PDUAPI_UNRECOGNIZED_PDU}
  SNMP_PDUAPI_INVALID_ES          = 21;
  {$EXTERNALSYM SNMP_PDUAPI_INVALID_ES}
  SNMP_PDUAPI_INVALID_GT          = 22;
  {$EXTERNALSYM SNMP_PDUAPI_INVALID_GT}
  SNMP_AUTHAPI_INVALID_VERSION    = 30;
  {$EXTERNALSYM SNMP_AUTHAPI_INVALID_VERSION}
  SNMP_AUTHAPI_INVALID_MSG_TYPE   = 31;
  {$EXTERNALSYM SNMP_AUTHAPI_INVALID_MSG_TYPE}
  SNMP_AUTHAPI_TRIV_AUTH_FAILED   = 32;
  {$EXTERNALSYM SNMP_AUTHAPI_TRIV_AUTH_FAILED}

{ Support for old definitions (support disabled via SNMPSTRICT) }

{$IFNDEF SNMPSTRICT}

function SNMP_oidcpy(pOidDst: PAsnObjectIdentifier; pOidSrc: PAsnObjectIdentifier): SNMPAPI; stdcall;
{$EXTERNALSYM SNMP_oidcpy}
function SNMP_oidappend(pOidDst: PAsnObjectIdentifier; pOidSrc: PAsnObjectIdentifier): SNMPAPI; stdcall;
{$EXTERNALSYM SNMP_oidappend}
function SNMP_oidncmp(pOid1, pOid2: PAsnObjectIdentifier; nSubIds: UINT): SNMPAPI; stdcall;
{$EXTERNALSYM SNMP_oidncmp}
function SNMP_oidcmp(pOid1, pOid2: PAsnObjectIdentifier): SNMPAPI; stdcall;
{$EXTERNALSYM SNMP_oidcmp}
procedure SNMP_oidfree(pOid: TAsnObjectIdentifier); stdcall;
{$EXTERNALSYM SNMP_oidfree}

function SNMP_CopyVarBind(pVbDst: PSnmpVarBind; pVbSrc: PSnmpVarBind): SNMPAPI; stdcall;
{$EXTERNALSYM SNMP_CopyVarBind}
procedure SNMP_FreeVarBind(pVb: PSnmpVarBind); stdcall;
{$EXTERNALSYM SNMP_FreeVarBind}
function SNMP_CopyVarBindList(pVblDst: PSnmpVarBindList; pVblSrc: PSnmpVarBindList): SNMPAPI; stdcall;
{$EXTERNALSYM SNMP_CopyVarBindList}
procedure SNMP_FreeVarBindList(pVbl: PSnmpVarBindList); stdcall;
{$EXTERNALSYM SNMP_FreeVarBindList}

procedure SNMP_printany(pAny: PAsnAny); stdcall;
{$EXTERNALSYM SNMP_printany}

procedure SNMP_free(pMem: LPVOID); stdcall;
{$EXTERNALSYM SNMP_free}
function SNMP_malloc(nBytes: UINT): LPVOID; stdcall;
{$EXTERNALSYM SNMP_malloc}
function SNMP_realloc(pMem: LPVOID; nBytes: UINT): LPVOID; stdcall;
{$EXTERNALSYM SNMP_realloc}

procedure SNMP_DBG_free(pMem: LPVOID); stdcall;
{$EXTERNALSYM SNMP_DBG_free}
function SNMP_DBG_malloc(nBytes: UINT): LPVOID; stdcall;
{$EXTERNALSYM SNMP_DBG_malloc}
function SNMP_DBG_realloc(pMem: LPVOID; nBytes: UINT): LPVOID; stdcall;
{$EXTERNALSYM SNMP_DBG_realloc}

const
  ASN_RFC1155_IPADDRESS           = ASN_IPADDRESS;
  {$EXTERNALSYM ASN_RFC1155_IPADDRESS}
  ASN_RFC1155_COUNTER             = ASN_COUNTER32;
  {$EXTERNALSYM ASN_RFC1155_COUNTER}
  ASN_RFC1155_GAUGE               = ASN_GAUGE32;
  {$EXTERNALSYM ASN_RFC1155_GAUGE}
  ASN_RFC1155_TIMETICKS           = ASN_TIMETICKS;
  {$EXTERNALSYM ASN_RFC1155_TIMETICKS}
  ASN_RFC1155_OPAQUE              = ASN_OPAQUE;
  {$EXTERNALSYM ASN_RFC1155_OPAQUE}
  ASN_RFC1213_DISPSTRING          = ASN_OCTETSTRING;
  {$EXTERNALSYM ASN_RFC1213_DISPSTRING}

  ASN_RFC1157_GETREQUEST          = SNMP_PDU_GET;
  {$EXTERNALSYM ASN_RFC1157_GETREQUEST}
  ASN_RFC1157_GETNEXTREQUEST      = SNMP_PDU_GETNEXT;
  {$EXTERNALSYM ASN_RFC1157_GETNEXTREQUEST}
  ASN_RFC1157_GETRESPONSE         = SNMP_PDU_RESPONSE;
  {$EXTERNALSYM ASN_RFC1157_GETRESPONSE}
  ASN_RFC1157_SETREQUEST          = SNMP_PDU_SET;
  {$EXTERNALSYM ASN_RFC1157_SETREQUEST}
  ASN_RFC1157_TRAP                = SNMP_PDU_V1TRAP;
  {$EXTERNALSYM ASN_RFC1157_TRAP}

  ASN_CONTEXTSPECIFIC             = ASN_CONTEXT;
  {$EXTERNALSYM ASN_CONTEXTSPECIFIC}
  ASN_PRIMATIVE                   = ASN_PRIMITIVE;
  {$EXTERNALSYM ASN_PRIMATIVE}

type
  RFC1157VarBindList              = TSnmpVarBindList;
  {$EXTERNALSYM RFC1157VarBindList}
  RFC1157VarBind                  = TSnmpVarBind;
  {$EXTERNALSYM RFC1157VarBind}
  TAsnInteger                     = TAsnInteger32;
  {$EXTERNALSYM TAsnInteger}
  TAsnCounter                     = TAsnCounter32;
  {$EXTERNALSYM TAsnCounter}
  TAsnGauge                       = TAsnGauge32;
  {$EXTERNALSYM TAsnGauge}

const
  ASN_UNSIGNED32                  = ASN_UINTEGER32;
  {$EXTERNALSYM ASN_UNSIGNED32}

{$ENDIF SNMPSTRICT}

implementation

uses
  JwaWinBase;

const
  snmpapilib = 'snmpapi.dll';


{$IFDEF DYNAMIC_LINK}
var
  _SnmpUtilOidCpy: Pointer;

function SnmpUtilOidCpy;
begin
  GetProcedureAddress(_SnmpUtilOidCpy, snmpapilib, 'SnmpUtilOidCpy');
  asm
    mov esp, ebp
    pop ebp
    jmp [_SnmpUtilOidCpy]
  end;
end;
{$ELSE}
function SnmpUtilOidCpy; external snmpapilib name 'SnmpUtilOidCpy';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _SnmpUtilOidAppend: Pointer;

function SnmpUtilOidAppend;
begin
  GetProcedureAddress(_SnmpUtilOidAppend, snmpapilib, 'SnmpUtilOidAppend');
  asm
    mov esp, ebp
    pop ebp
    jmp [_SnmpUtilOidAppend]
  end;
end;
{$ELSE}
function SnmpUtilOidAppend; external snmpapilib name 'SnmpUtilOidAppend';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _SnmpUtilOidNCmp: Pointer;

function SnmpUtilOidNCmp;
begin
  GetProcedureAddress(_SnmpUtilOidNCmp, snmpapilib, 'SnmpUtilOidNCmp');
  asm
    mov esp, ebp
    pop ebp
    jmp [_SnmpUtilOidNCmp]
  end;
end;
{$ELSE}
function SnmpUtilOidNCmp; external snmpapilib name 'SnmpUtilOidNCmp';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _SnmpUtilOidCmp: Pointer;

function SnmpUtilOidCmp;
begin
  GetProcedureAddress(_SnmpUtilOidCmp, snmpapilib, 'SnmpUtilOidCmp');
  asm
    mov esp, ebp
    pop ebp
    jmp [_SnmpUtilOidCmp]
  end;
end;
{$ELSE}
function SnmpUtilOidCmp; external snmpapilib name 'SnmpUtilOidCmp';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _SnmpUtilOidFree: Pointer;

procedure SnmpUtilOidFree;
begin
  GetProcedureAddress(_SnmpUtilOidFree, snmpapilib, 'SnmpUtilOidFree');
  asm
    mov esp, ebp
    pop ebp
    jmp [_SnmpUtilOidFree]
  end;
end;
{$ELSE}
procedure SnmpUtilOidFree; external snmpapilib name 'SnmpUtilOidFree';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _SnmpUtilOctetsCmp: Pointer;

function SnmpUtilOctetsCmp;
begin
  GetProcedureAddress(_SnmpUtilOctetsCmp, snmpapilib, 'SnmpUtilOctetsCmp');
  asm
    mov esp, ebp
    pop ebp
    jmp [_SnmpUtilOctetsCmp]
  end;
end;
{$ELSE}
function SnmpUtilOctetsCmp; external snmpapilib name 'SnmpUtilOctetsCmp';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _SnmpUtilOctetsNCmp: Pointer;

function SnmpUtilOctetsNCmp;
begin
  GetProcedureAddress(_SnmpUtilOctetsNCmp, snmpapilib, 'SnmpUtilOctetsNCmp');
  asm
    mov esp, ebp
    pop ebp
    jmp [_SnmpUtilOctetsNCmp]
  end;
end;
{$ELSE}
function SnmpUtilOctetsNCmp; external snmpapilib name 'SnmpUtilOctetsNCmp';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _SnmpUtilOctetsCpy: Pointer;

function SnmpUtilOctetsCpy;
begin
  GetProcedureAddress(_SnmpUtilOctetsCpy, snmpapilib, 'SnmpUtilOctetsCpy');
  asm
    mov esp, ebp
    pop ebp
    jmp [_SnmpUtilOctetsCpy]
  end;
end;
{$ELSE}
function SnmpUtilOctetsCpy; external snmpapilib name 'SnmpUtilOctetsCpy';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _SnmpUtilOctetsFree: Pointer;

procedure SnmpUtilOctetsFree;
begin
  GetProcedureAddress(_SnmpUtilOctetsFree, snmpapilib, 'SnmpUtilOctetsFree');
  asm
    mov esp, ebp
    pop ebp
    jmp [_SnmpUtilOctetsFree]
  end;
end;
{$ELSE}
procedure SnmpUtilOctetsFree; external snmpapilib name 'SnmpUtilOctetsFree';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _SnmpUtilAsnAnyCpy: Pointer;

function SnmpUtilAsnAnyCpy;
begin
  GetProcedureAddress(_SnmpUtilAsnAnyCpy, snmpapilib, 'SnmpUtilAsnAnyCpy');
  asm
    mov esp, ebp
    pop ebp
    jmp [_SnmpUtilAsnAnyCpy]
  end;
end;
{$ELSE}
function SnmpUtilAsnAnyCpy; external snmpapilib name 'SnmpUtilAsnAnyCpy';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _SnmpUtilAsnAnyFree: Pointer;

procedure SnmpUtilAsnAnyFree;
begin
  GetProcedureAddress(_SnmpUtilAsnAnyFree, snmpapilib, 'SnmpUtilAsnAnyFree');
  asm
    mov esp, ebp
    pop ebp
    jmp [_SnmpUtilAsnAnyFree]
  end;
end;
{$ELSE}
procedure SnmpUtilAsnAnyFree; external snmpapilib name 'SnmpUtilAsnAnyFree';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _SnmpUtilVarBindCpy: Pointer;

function SnmpUtilVarBindCpy;
begin
  GetProcedureAddress(_SnmpUtilVarBindCpy, snmpapilib, 'SnmpUtilVarBindCpy');
  asm
    mov esp, ebp
    pop ebp
    jmp [_SnmpUtilVarBindCpy]
  end;
end;
{$ELSE}
function SnmpUtilVarBindCpy; external snmpapilib name 'SnmpUtilVarBindCpy';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _SnmpUtilVarBindFree: Pointer;

procedure SnmpUtilVarBindFree;
begin
  GetProcedureAddress(_SnmpUtilVarBindFree, snmpapilib, 'SnmpUtilVarBindFree');
  asm
    mov esp, ebp
    pop ebp
    jmp [_SnmpUtilVarBindFree]
  end;
end;
{$ELSE}
procedure SnmpUtilVarBindFree; external snmpapilib name 'SnmpUtilVarBindFree';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _SnmpUtilVarBindListCpy: Pointer;

function SnmpUtilVarBindListCpy;
begin
  GetProcedureAddress(_SnmpUtilVarBindListCpy, snmpapilib, 'SnmpUtilVarBindListCpy');
  asm
    mov esp, ebp
    pop ebp
    jmp [_SnmpUtilVarBindListCpy]
  end;
end;
{$ELSE}
function SnmpUtilVarBindListCpy; external snmpapilib name 'SnmpUtilVarBindListCpy';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _SnmpUtilVarBindListFree: Pointer;

procedure SnmpUtilVarBindListFree;
begin
  GetProcedureAddress(_SnmpUtilVarBindListFree, snmpapilib, 'SnmpUtilVarBindListFree');
  asm
    mov esp, ebp
    pop ebp
    jmp [_SnmpUtilVarBindListFree]
  end;
end;
{$ELSE}
procedure SnmpUtilVarBindListFree; external snmpapilib name 'SnmpUtilVarBindListFree';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _SnmpUtilMemFree: Pointer;

procedure SnmpUtilMemFree;
begin
  GetProcedureAddress(_SnmpUtilMemFree, snmpapilib, 'SnmpUtilMemFree');
  asm
    mov esp, ebp
    pop ebp
    jmp [_SnmpUtilMemFree]
  end;
end;
{$ELSE}
procedure SnmpUtilMemFree; external snmpapilib name 'SnmpUtilMemFree';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _SnmpUtilMemAlloc: Pointer;

function SnmpUtilMemAlloc;
begin
  GetProcedureAddress(_SnmpUtilMemAlloc, snmpapilib, 'SnmpUtilMemAlloc');
  asm
    mov esp, ebp
    pop ebp
    jmp [_SnmpUtilMemAlloc]
  end;
end;
{$ELSE}
function SnmpUtilMemAlloc; external snmpapilib name 'SnmpUtilMemAlloc';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _SnmpUtilMemReAlloc: Pointer;

function SnmpUtilMemReAlloc;
begin
  GetProcedureAddress(_SnmpUtilMemReAlloc, snmpapilib, 'SnmpUtilMemReAlloc');
  asm
    mov esp, ebp
    pop ebp
    jmp [_SnmpUtilMemReAlloc]
  end;
end;
{$ELSE}
function SnmpUtilMemReAlloc; external snmpapilib name 'SnmpUtilMemReAlloc';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _SnmpUtilOidToA: Pointer;

function SnmpUtilOidToA;
begin
  GetProcedureAddress(_SnmpUtilOidToA, snmpapilib, 'SnmpUtilOidToA');
  asm
    mov esp, ebp
    pop ebp
    jmp [_SnmpUtilOidToA]
  end;
end;
{$ELSE}
function SnmpUtilOidToA; external snmpapilib name 'SnmpUtilOidToA';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _SnmpUtilIdsToA: Pointer;

function SnmpUtilIdsToA;
begin
  GetProcedureAddress(_SnmpUtilIdsToA, snmpapilib, 'SnmpUtilIdsToA');
  asm
    mov esp, ebp
    pop ebp
    jmp [_SnmpUtilIdsToA]
  end;
end;
{$ELSE}
function SnmpUtilIdsToA; external snmpapilib name 'SnmpUtilIdsToA';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _SnmpUtilPrintOid: Pointer;

procedure SnmpUtilPrintOid;
begin
  GetProcedureAddress(_SnmpUtilPrintOid, snmpapilib, 'SnmpUtilPrintOid');
  asm
    mov esp, ebp
    pop ebp
    jmp [_SnmpUtilPrintOid]
  end;
end;
{$ELSE}
procedure SnmpUtilPrintOid; external snmpapilib name 'SnmpUtilPrintOid';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _SnmpUtilPrintAsnAny: Pointer;

procedure SnmpUtilPrintAsnAny;
begin
  GetProcedureAddress(_SnmpUtilPrintAsnAny, snmpapilib, 'SnmpUtilPrintAsnAny');
  asm
    mov esp, ebp
    pop ebp
    jmp [_SnmpUtilPrintAsnAny]
  end;
end;
{$ELSE}
procedure SnmpUtilPrintAsnAny; external snmpapilib name 'SnmpUtilPrintAsnAny';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _SnmpSvcGetUptime: Pointer;

function SnmpSvcGetUptime;
begin
  GetProcedureAddress(_SnmpSvcGetUptime, snmpapilib, 'SnmpSvcGetUptime');
  asm
    mov esp, ebp
    pop ebp
    jmp [_SnmpSvcGetUptime]
  end;
end;
{$ELSE}
function SnmpSvcGetUptime; external snmpapilib name 'SnmpSvcGetUptime';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _SnmpSvcSetLogLevel: Pointer;

procedure SnmpSvcSetLogLevel;
begin
  GetProcedureAddress(_SnmpSvcSetLogLevel, snmpapilib, 'SnmpSvcSetLogLevel');
  asm
    mov esp, ebp
    pop ebp
    jmp [_SnmpSvcSetLogLevel]
  end;
end;
{$ELSE}
procedure SnmpSvcSetLogLevel; external snmpapilib name 'SnmpSvcSetLogLevel';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _SnmpSvcSetLogType: Pointer;

procedure SnmpSvcSetLogType;
begin
  GetProcedureAddress(_SnmpSvcSetLogType, snmpapilib, 'SnmpSvcSetLogType');
  asm
    mov esp, ebp
    pop ebp
    jmp [_SnmpSvcSetLogType]
  end;
end;
{$ELSE}
procedure SnmpSvcSetLogType; external snmpapilib name 'SnmpSvcSetLogType';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _SnmpUtilDbgPrint: Pointer;

procedure SnmpUtilDbgPrint;
begin
  GetProcedureAddress(_SnmpUtilDbgPrint, snmpapilib, 'SnmpUtilDbgPrint');
  asm
    mov esp, ebp
    pop ebp
    jmp [_SnmpUtilDbgPrint]
  end;
end;
{$ELSE}
procedure SnmpUtilDbgPrint; external snmpapilib name 'SnmpUtilDbgPrint';
{$ENDIF DYNAMIC_LINK}

{$IFNDEF SNMPSTRICT}

{$IFDEF DYNAMIC_LINK}
var
  _SNMP_oidcpy: Pointer;

function SNMP_oidcpy;
begin
  GetProcedureAddress(_SNMP_oidcpy, snmpapilib, 'SnmpUtilOidCpy');
  asm
    mov esp, ebp
    pop ebp
    jmp [_SNMP_oidcpy]
  end;
end;
{$ELSE}
function SNMP_oidcpy; external snmpapilib name 'SnmpUtilOidCpy';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _SNMP_oidappend: Pointer;

function SNMP_oidappend;
begin
  GetProcedureAddress(_SNMP_oidappend, snmpapilib, 'SnmpUtilOidAppend');
  asm
    mov esp, ebp
    pop ebp
    jmp [_SNMP_oidappend]
  end;
end;
{$ELSE}
function SNMP_oidappend; external snmpapilib name 'SnmpUtilOidAppend';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _SNMP_oidncmp: Pointer;

function SNMP_oidncmp;
begin
  GetProcedureAddress(_SNMP_oidncmp, snmpapilib, 'SnmpUtilOidNCmp');
  asm
    mov esp, ebp
    pop ebp
    jmp [_SNMP_oidncmp]
  end;
end;
{$ELSE}
function SNMP_oidncmp; external snmpapilib name 'SnmpUtilOidNCmp';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _SNMP_oidcmp: Pointer;

function SNMP_oidcmp;
begin
  GetProcedureAddress(_SNMP_oidcmp, snmpapilib, 'SnmpUtilOidCmp');
  asm
    mov esp, ebp
    pop ebp
    jmp [_SNMP_oidcmp]
  end;
end;
{$ELSE}
function SNMP_oidcmp; external snmpapilib name 'SnmpUtilOidCmp';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _SNMP_oidfree: Pointer;

procedure SNMP_oidfree;
begin
  GetProcedureAddress(_SNMP_oidfree, snmpapilib, 'SnmpUtilOidFree');
  asm
    mov esp, ebp
    pop ebp
    jmp [_SNMP_oidfree]
  end;
end;
{$ELSE}
procedure SNMP_oidfree; external snmpapilib name 'SnmpUtilOidFree';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _SNMP_CopyVarBind: Pointer;

function SNMP_CopyVarBind;
begin
  GetProcedureAddress(_SNMP_CopyVarBind, snmpapilib, 'SnmpUtilVarBindCpy');
  asm
    mov esp, ebp
    pop ebp
    jmp [_SNMP_CopyVarBind]
  end;
end;
{$ELSE}
function SNMP_CopyVarBind; external snmpapilib name 'SnmpUtilVarBindCpy';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _SNMP_FreeVarBind: Pointer;

procedure SNMP_FreeVarBind;
begin
  GetProcedureAddress(_SNMP_FreeVarBind, snmpapilib, 'SnmpUtilVarBindFree');
  asm
    mov esp, ebp
    pop ebp
    jmp [_SNMP_FreeVarBind]
  end;
end;
{$ELSE}
procedure SNMP_FreeVarBind; external snmpapilib name 'SnmpUtilVarBindFree';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _SNMP_CopyVarBindList: Pointer;

function SNMP_CopyVarBindList;
begin
  GetProcedureAddress(_SNMP_CopyVarBindList, snmpapilib, 'SnmpUtilVarBindListCpy');
  asm
    mov esp, ebp
    pop ebp
    jmp [_SNMP_CopyVarBindList]
  end;
end;
{$ELSE}
function SNMP_CopyVarBindList; external snmpapilib name 'SnmpUtilVarBindListCpy';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _SNMP_FreeVarBindList: Pointer;

procedure SNMP_FreeVarBindList;
begin
  GetProcedureAddress(_SNMP_FreeVarBindList, snmpapilib, 'SnmpUtilVarBindListFree');
  asm
    mov esp, ebp
    pop ebp
    jmp [_SNMP_FreeVarBindList]
  end;
end;
{$ELSE}
procedure SNMP_FreeVarBindList; external snmpapilib name 'SnmpUtilVarBindListFree';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _SNMP_printany: Pointer;

procedure SNMP_printany;
begin
  GetProcedureAddress(_SNMP_printany, snmpapilib, 'SnmpUtilPrintAsnAny');
  asm
    mov esp, ebp
    pop ebp
    jmp [_SNMP_printany]
  end;
end;
{$ELSE}
procedure SNMP_printany; external snmpapilib name 'SnmpUtilPrintAsnAny';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _SNMP_free: Pointer;

procedure SNMP_free;
begin
  GetProcedureAddress(_SNMP_free, snmpapilib, 'SnmpUtilMemFree');
  asm
    mov esp, ebp
    pop ebp
    jmp [_SNMP_free]
  end;
end;
{$ELSE}
procedure SNMP_free; external snmpapilib name 'SnmpUtilMemFree';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _SNMP_malloc: Pointer;

function SNMP_malloc;
begin
  GetProcedureAddress(_SNMP_malloc, snmpapilib, 'SnmpUtilMemAlloc');
  asm
    mov esp, ebp
    pop ebp
    jmp [_SNMP_malloc]
  end;
end;
{$ELSE}
function SNMP_malloc; external snmpapilib name 'SnmpUtilMemAlloc';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _SNMP_realloc: Pointer;

function SNMP_realloc;
begin
  GetProcedureAddress(_SNMP_realloc, snmpapilib, 'SnmpUtilMemReAlloc');
  asm
    mov esp, ebp
    pop ebp
    jmp [_SNMP_realloc]
  end;
end;
{$ELSE}
function SNMP_realloc; external snmpapilib name 'SnmpUtilMemReAlloc';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _SNMP_DBG_free: Pointer;

procedure SNMP_DBG_free;
begin
  GetProcedureAddress(_SNMP_DBG_free, snmpapilib, 'SnmpUtilMemFree');
  asm
    mov esp, ebp
    pop ebp
    jmp [_SNMP_DBG_free]
  end;
end;
{$ELSE}
procedure SNMP_DBG_free; external snmpapilib name 'SnmpUtilMemFree';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _SNMP_DBG_malloc: Pointer;

function SNMP_DBG_malloc;
begin
  GetProcedureAddress(_SNMP_DBG_malloc, snmpapilib, 'SnmpUtilMemAlloc');
  asm
    mov esp, ebp
    pop ebp
    jmp [_SNMP_DBG_malloc]
  end;
end;
{$ELSE}
function SNMP_DBG_malloc; external snmpapilib name 'SnmpUtilMemAlloc';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _SNMP_DBG_realloc: Pointer;

function SNMP_DBG_realloc;
begin
  GetProcedureAddress(_SNMP_DBG_realloc, snmpapilib, 'SnmpUtilMemReAlloc');
  asm
    mov esp, ebp
    pop ebp
    jmp [_SNMP_DBG_realloc]
  end;
end;
{$ELSE}
function SNMP_DBG_realloc; external snmpapilib name 'SnmpUtilMemReAlloc';
{$ENDIF DYNAMIC_LINK}
{$ENDIF SNMPSTRICT}

end.
