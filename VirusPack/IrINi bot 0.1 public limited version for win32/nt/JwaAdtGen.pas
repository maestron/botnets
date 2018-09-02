{******************************************************************************}
{                                                       	               }
{ Authz Generic Audits API interface Unit for Object Pascal                    }
{                                                       	               }
{ Portions created by Microsoft are Copyright (C) 1995-2001 Microsoft          }
{ Corporation. All Rights Reserved.                                            }
{ 								               }
{ The original file is: adtgen.h, released August 2001. The original Pascal    }
{ code is: AdtGen.pas, released October 2001. The initial developer of the     }
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

unit JwaAdtGen;

{$WEAKPACKAGEUNIT}

{$HPPEMIT ''}
{$HPPEMIT '#include "adtgen.h"'}
{$HPPEMIT ''}

{$I WINDEFINES.INC}

interface

uses
  JwaWinNT, JwaWinType;

//
// type of audit 
//
// AUDIT_TYPE_LEGACY 
//     In this case the audit event schema is stored in a .mc file.
//
// AUDIT_TYPE_WMI    
//     The schema is stored in WMI. (currently not supported)
//

const
  AUDIT_TYPE_LEGACY = 1;
  {$EXTERNALSYM AUDIT_TYPE_LEGACY}
  AUDIT_TYPE_WMI    = 2;
  {$EXTERNALSYM AUDIT_TYPE_WMI}

//
// Type of parameters passed in the AUDIT_PARAMS.Parameters array
// 
// Use the AdtInitParams function to initialize and prepare 
// an array of audit parameters.
//

type
  _AUDIT_PARAM_TYPE = (

    APT__0,

    //
    // do we need this?
    //

    APT_None,

    //
    // NULL terminated string 
    //

    APT_String,

    //
    // unsigned long
    //

    APT_Ulong,

    //
    // a pointer. use for specifying handles/pointers
    // (32 bit on 32 bit systems and 64 bit on 64 bit systems)
    // Note that the memory to which the pointer points to
    // is not marshalled when using this type. Use this when you
    // are interested in the absolute value of the pointer.
    // A good example of this is when specifying HANDLE values.
    //

    APT_Pointer,

    //
    // SID
    //

    APT_Sid,

    //
    // Logon ID (LUID)
    //

    APT_LogonId,

    //
    // Object Type List
    //

    APT_ObjectTypeList,

    //
    // Luid (not translated to LogonId)
    //
    
    APT_Luid,
    
    //
    // Guid
    //
     
    APT_Guid,

    //
    // Time (FILETIME)
    //

    APT_Time,

    //
    // ULONGLONG
    // 

    APT_Int64
    );
  {$EXTERNALSYM _AUDIT_PARAM_TYPE}
  AUDIT_PARAM_TYPE = _AUDIT_PARAM_TYPE;
  {$EXTERNALSYM AUDIT_PARAM_TYPE}
  TAuditParamType = AUDIT_PARAM_TYPE;

// 
// There are two types of flags that can be used with a parameter.
//
// - formatting flag
//   This defines the appearance of a parameter when
//   written to the eventlog. Such flags may become obsolete
//   when we move to WMI auditing.
//
// - control flag
//   This causes a specified action to be taken that affects 
//   a parameter value.
//
//   For example:
//   If you use the AP_PrimaryLogonId/AP_ClientLogonId flag,
//   the system will capture the logon-id from the process/thread token.
//

const
  AP_ParamTypeBits = 8;
  {$EXTERNALSYM AP_ParamTypeBits}
  AP_ParamTypeMask = $000000ff;
  {$EXTERNALSYM AP_ParamTypeMask}

//
// the flags values below have overlapping values. this is ok since
// the scope of each flag is limited to the type to which it applies.
//

//
// APT_Ulong : format flag : causes a number to appear in hex
//

  AP_FormatHex = ($0001 shl AP_ParamTypeBits);
  {$EXTERNALSYM AP_FormatHex}

//
// APT_Ulong : format flag : causes a number to be treated as access-mask.
//                           The meaning of each bit depends on the associated
//                           object type.
//

  AP_AccessMask = ($0002 shl AP_ParamTypeBits);
  {$EXTERNALSYM AP_AccessMask}

                                                       
//
// APT_String : format flag : causes a string to be treated as a file-path
//

  AP_Filespec = ($0001 shl AP_ParamTypeBits);
  {$EXTERNALSYM AP_Filespec}

//
// APT_LogonId : control flag : logon-id is captured from the process token
//

  AP_PrimaryLogonId = ($0001 shl AP_ParamTypeBits);
  {$EXTERNALSYM AP_PrimaryLogonId}

//
// APT_LogonId : control flag : logon-id is captured from the thread token
//

  AP_ClientLogonId = ($0002 shl AP_ParamTypeBits);
  {$EXTERNALSYM AP_ClientLogonId}

//
// internal helper macros
//

function ApExtractType(TypeFlags: DWORD): AUDIT_PARAM_TYPE;
{$EXTERNALSYM ApExtractType}

function ApExtractFlags(TypeFlags: DWORD): DWORD;
{$EXTERNALSYM ApExtractFlags}

//
// Element of an object-type-list
//
// The AUDIT_OBJECT_TYPES structure identifies an object type element 
// in a hierarchy of object types. The AccessCheckByType functions use 
// an array of such structures to define a hierarchy of an object and 
// its subobjects, such as property sets and properties.
//

type
  PAUDIT_OBJECT_TYPE = ^AUDIT_OBJECT_TYPE;
  {$EXTERNALSYM PAUDIT_OBJECT_TYPE}
  _AUDIT_OBJECT_TYPE = record
    ObjectType: GUID; // guid of the (sub)object
    Flags: USHORT; // currently not defined
    Level: USHORT; // level within the hierarchy.
    // 0 is the root level
    AccessMask: ACCESS_MASK; // access-mask for this (sub)object
  end;
  {$EXTERNALSYM _AUDIT_OBJECT_TYPE}
  AUDIT_OBJECT_TYPE = _AUDIT_OBJECT_TYPE;
  {$EXTERNALSYM AUDIT_OBJECT_TYPE}
  TAuditObjectType = AUDIT_OBJECT_TYPE;
  PAuditObjectType = PAUDIT_OBJECT_TYPE;

  PAUDIT_OBJECT_TYPES = ^AUDIT_OBJECT_TYPES;
  {$EXTERNALSYM PAUDIT_OBJECT_TYPES}
  _AUDIT_OBJECT_TYPES = record
    Count: USHORT; // number of object-types in pObjectTypes
    Flags: USHORT; // currently not defined
    pObjectTypes: PAUDIT_OBJECT_TYPE; // array of object-types
  end;
  {$EXTERNALSYM _AUDIT_OBJECT_TYPES}
  AUDIT_OBJECT_TYPES = _AUDIT_OBJECT_TYPES;
  {$EXTERNALSYM AUDIT_OBJECT_TYPES}
  TAuditObjectTypes = AUDIT_OBJECT_TYPES;
  PAuditObjectTypes = PAUDIT_OBJECT_TYPES;

//
// Structure that defines a single audit parameter.
//
// LsaGenAuditEvent accepts an array of such elements to
// represent the parameters of the audit to be generated.
//
// It is best to initialize this structure using AdtInitParams function.
// This will ensure compatibility with any future changes to this
// structure.
//

type
  _AUDIT_PARAM = record
    Type_: AUDIT_PARAM_TYPE;     // type
    Length: ULONG;               // currently unused
    Flags: DWORD;                // currently unused
    U: record
    case Integer of
      0: (Data0: ULONG_PTR);
      1: (String_: PWSTR);
      2: (u: ULONG_PTR);
      3: (psid: PSID);
      4: (pguid: LPGUID);      
      5: (LogonId_LowPart: ULONG);
      6: (pObjectTypes: PAUDIT_OBJECT_TYPES);
    end;
    case Integer of
      0: (Data1: ULONG_PTR);
      1: (LogonId_HighPart: LONG);
  end;
  {$EXTERNALSYM _AUDIT_PARAM}
  AUDIT_PARAM = _AUDIT_PARAM;
  {$EXTERNALSYM AUDIT_PARAM}
  PAUDIT_PARAM = ^AUDIT_PARAM;
  {$EXTERNALSYM PAUDIT_PARAM}
  TAuditParam = AUDIT_PARAM;
  PAuditParam = PAUDIT_PARAM;

//
// Audit control flags. To be used with AUDIT_PARAMS.Flags
//

const
  APF_AuditFailure = $00000000; // generate a failure audit
  {$EXTERNALSYM APF_AuditFailure}
  APF_AuditSuccess = $00000001; // generate a success audit when set, a failure audit otherwise.
  {$EXTERNALSYM APF_AuditSuccess}

//
// set of valid audit control flags 
//

  APF_ValidFlags = (APF_AuditSuccess);
  {$EXTERNALSYM APF_ValidFlags}

//
// Audit parameters passed to LsaGenAuditEvent
//

type
  PAUDIT_PARAMS = ^AUDIT_PARAMS;
  {$EXTERNALSYM PAUDIT_PARAMS}
  _AUDIT_PARAMS = record
    Length: ULONG; // size in bytes
    Flags: DWORD; // currently unused
    Count: USHORT; // number of parameters
    Parameters: PAUDIT_PARAM; // array of parameters
  end;
  {$EXTERNALSYM _AUDIT_PARAMS}
  AUDIT_PARAMS = _AUDIT_PARAMS;
  {$EXTERNALSYM AUDIT_PARAMS}
  TAuditParams = AUDIT_PARAMS;
  PAuditParams = PAUDIT_PARAMS;

//
// Defines the elements of a legacy audit event.
//

  PAUTHZ_AUDIT_EVENT_TYPE_LEGACY = ^AUTHZ_AUDIT_EVENT_TYPE_LEGACY;
  {$EXTERNALSYM PAUTHZ_AUDIT_EVENT_TYPE_LEGACY}
  _AUTHZ_AUDIT_EVENT_TYPE_LEGACY = record
    //
    // Audit category ID
    //
    CategoryId: USHORT;
    //
    // Audit event ID
    //
    AuditId: USHORT;
    //
    // Parameter count
    //
    ParameterCount: USHORT;
  end;
  {$EXTERNALSYM _AUTHZ_AUDIT_EVENT_TYPE_LEGACY}
  AUTHZ_AUDIT_EVENT_TYPE_LEGACY = _AUTHZ_AUDIT_EVENT_TYPE_LEGACY;
  {$EXTERNALSYM AUTHZ_AUDIT_EVENT_TYPE_LEGACY}
  TAuthzAuditEventTypeLegacy = AUTHZ_AUDIT_EVENT_TYPE_LEGACY;
  PAuthzAuditEventTypeLegacy = PAUTHZ_AUDIT_EVENT_TYPE_LEGACY;

  _AUTHZ_AUDIT_EVENT_TYPE_UNION = record
    case Integer of
      0: (Legacy: AUTHZ_AUDIT_EVENT_TYPE_LEGACY);
  end;
  {$EXTERNALSYM _AUTHZ_AUDIT_EVENT_TYPE_UNION}
  AUTHZ_AUDIT_EVENT_TYPE_UNION = _AUTHZ_AUDIT_EVENT_TYPE_UNION;
  {$EXTERNALSYM AUTHZ_AUDIT_EVENT_TYPE_UNION}
  PAUTHZ_AUDIT_EVENT_TYPE_UNION = ^AUTHZ_AUDIT_EVENT_TYPE_UNION;
  {$EXTERNALSYM PAUTHZ_AUDIT_EVENT_TYPE_UNION}
  TAuthzAuditEventTypeUnion = AUTHZ_AUDIT_EVENT_TYPE_UNION;
  PAuthzAuditEventTypeUnion = PAUTHZ_AUDIT_EVENT_TYPE_UNION;  

//
// description of an audit event
//

  _AUTHZ_AUDIT_EVENT_TYPE_OLD = record
    // version number
    Version: ULONG;
    dwFlags: DWORD;
    RefCount: LONG;
    hAudit: ULONG_PTR;
    LinkId: LUID;
    u: AUTHZ_AUDIT_EVENT_TYPE_UNION;
  end;
  {$EXTERNALSYM _AUTHZ_AUDIT_EVENT_TYPE_OLD}
  AUTHZ_AUDIT_EVENT_TYPE_OLD = _AUTHZ_AUDIT_EVENT_TYPE_OLD;
  {$EXTERNALSYM AUTHZ_AUDIT_EVENT_TYPE_OLD}
  TAuthzAuditEventTypeOld = AUTHZ_AUDIT_EVENT_TYPE_OLD;
  PAuthzAuditEventTypeOld = ^AUTHZ_AUDIT_EVENT_TYPE_OLD;

  PAUTHZ_AUDIT_EVENT_TYPE_OLD = ^AUTHZ_AUDIT_EVENT_TYPE_OLD;
  {$EXTERNALSYM PAUTHZ_AUDIT_EVENT_TYPE_OLD}
  AUDIT_HANDLE = PVOID;
  {$EXTERNALSYM AUDIT_HANDLE}
  PAUDIT_HANDLE = ^AUDIT_HANDLE;
  {$EXTERNALSYM PAUDIT_HANDLE}

(* todo
function AuthzpRegisterAuditEvent(pAuditEventType: PAUTHZ_AUDIT_EVENT_TYPE_OLD; var phAuditContext: AUDIT_HANDLE): BOOL; stdcall;
{$EXTERNALSYM AuthzpRegisterAuditEvent}

function AuthzpUnregisterAuditEvent(var phAuditContext: AUDIT_HANDLE): BOOL; stdcall;
{$EXTERNALSYM AuthzpUnregisterAuditEvent}
*)

//
// Begin support for extensible auditing.
//

const
  AUTHZ_ALLOW_MULTIPLE_SOURCE_INSTANCES = $1;
  {$EXTERNALSYM AUTHZ_ALLOW_MULTIPLE_SOURCE_INSTANCES}

  AUTHZ_AUDIT_INSTANCE_INFORMATION = $2;
  {$EXTERNALSYM AUTHZ_AUDIT_INSTANCE_INFORMATION}

implementation

const
  authz_lib = 'authz.dll';

function ApExtractType(TypeFlags: DWORD): AUDIT_PARAM_TYPE;
begin
  Result := AUDIT_PARAM_TYPE(TypeFlags and AP_ParamTypeMask);
end;

function ApExtractFlags(TypeFlags: DWORD): DWORD;
begin
  Result := TypeFlags and not AP_ParamTypeMask;
end;

{
AuthzpRegisterAuditEvent
AuthzpUnregisterAuditEvent
}
end.
