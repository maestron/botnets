{******************************************************************************}
{                                                       	               }
{ Authorization Framework API interface Unit for Object Pascal                 }
{                                                       	               }
{ Portions created by Microsoft are Copyright (C) 1995-2001 Microsoft          }
{ Corporation. All Rights Reserved.                                            }
{ 								               }
{ The original file is: authz.h, released August 2001. The original Pascal     }
{ code is: Authz.pas, released October 2001. The initial developer of the      }
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

unit JwaAuthz;

{$WEAKPACKAGEUNIT}

{$HPPEMIT ''}
{$HPPEMIT '#include "authz.h"'}
{$HPPEMIT ''}

{$I WINDEFINES.INC}

interface

uses
  JwaWinNT, JwaWinType;

//
// Flags which may be used at the time of client context creation using a sid.
//

const
  AUTHZ_SKIP_TOKEN_GROUPS = $2;
  {$EXTERNALSYM AUTHZ_SKIP_TOKEN_GROUPS}
  AUTHZ_REQUIRE_S4U_LOGON = $4;
  {$EXTERNALSYM AUTHZ_REQUIRE_S4U_LOGON}

type
  AUTHZ_ACCESS_CHECK_RESULTS_HANDLE = HANDLE;
  {$EXTERNALSYM AUTHZ_ACCESS_CHECK_RESULTS_HANDLE}
  AUTHZ_CLIENT_CONTEXT_HANDLE = HANDLE;
  {$EXTERNALSYM AUTHZ_CLIENT_CONTEXT_HANDLE}
  AUTHZ_RESOURCE_MANAGER_HANDLE = HANDLE;
  {$EXTERNALSYM AUTHZ_RESOURCE_MANAGER_HANDLE}
  AUTHZ_AUDIT_EVENT_HANDLE = HANDLE;
  {$EXTERNALSYM AUTHZ_AUDIT_EVENT_HANDLE}
  AUTHZ_AUDIT_EVENT_TYPE_HANDLE = HANDLE;
  {$EXTERNALSYM AUTHZ_AUDIT_EVENT_TYPE_HANDLE}
  AUTHZ_SECURITY_EVENT_PROVIDER_HANDLE = HANDLE;
  {$EXTERNALSYM AUTHZ_SECURITY_EVENT_PROVIDER_HANDLE}

  PAUTHZ_ACCESS_CHECK_RESULTS_HANDLE = ^AUTHZ_ACCESS_CHECK_RESULTS_HANDLE;
  {$EXTERNALSYM PAUTHZ_ACCESS_CHECK_RESULTS_HANDLE}
  PAUTHZ_CLIENT_CONTEXT_HANDLE = ^AUTHZ_CLIENT_CONTEXT_HANDLE;
  {$EXTERNALSYM PAUTHZ_CLIENT_CONTEXT_HANDLE}
  PAUTHZ_RESOURCE_MANAGER_HANDLE = ^AUTHZ_RESOURCE_MANAGER_HANDLE;
  {$EXTERNALSYM PAUTHZ_RESOURCE_MANAGER_HANDLE}
  PAUTHZ_AUDIT_EVENT_HANDLE = ^AUTHZ_AUDIT_EVENT_HANDLE;
  {$EXTERNALSYM PAUTHZ_AUDIT_EVENT_HANDLE}
  PAUTHZ_AUDIT_EVENT_TYPE_HANDLE = ^AUTHZ_AUDIT_EVENT_TYPE_HANDLE;
  {$EXTERNALSYM PAUTHZ_AUDIT_EVENT_TYPE_HANDLE}
  PAUTHZ_SECURITY_EVENT_PROVIDER_HANDLE = ^AUTHZ_SECURITY_EVENT_PROVIDER_HANDLE;
  {$EXTERNALSYM PAUTHZ_SECURITY_EVENT_PROVIDER_HANDLE}

//
// Structure defining the access check request.
//

  PAUTHZ_ACCESS_REQUEST = ^AUTHZ_ACCESS_REQUEST;
  {$EXTERNALSYM PAUTHZ_ACCESS_REQUEST}
  _AUTHZ_ACCESS_REQUEST = record
    DesiredAccess: ACCESS_MASK;
    //
    // To replace the principal self sid in the acl.
    //
    PrincipalSelfSid: PSID;
    //
    // Object type list represented by an array of (level, guid) pair and the
    // number of elements in the array. This is a post-fix representation of the
    // object tree.
    // These fields should be set to NULL and 0 respectively except when per
    // property access is desired.
    //
    ObjectTypeList: POBJECT_TYPE_LIST;
    ObjectTypeListLength: DWORD;
    //
    // To support completely business rules based access. This will be passed as
    // input to the callback access check function. Access check algorithm does
    // not interpret these.
    //
    OptionalArguments: PVOID;
  end;
  {$EXTERNALSYM _AUTHZ_ACCESS_REQUEST}
  AUTHZ_ACCESS_REQUEST = _AUTHZ_ACCESS_REQUEST;
  {$EXTERNALSYM AUTHZ_ACCESS_REQUEST}
  TAuthzAccessRequest = AUTHZ_ACCESS_REQUEST;
  PAuthzAccessRequest = PAUTHZ_ACCESS_REQUEST;

//
// Structure to return the results of the access check call.
//

const
  AUTHZ_GENERATE_SUCCESS_AUDIT = $1;
  {$EXTERNALSYM AUTHZ_GENERATE_SUCCESS_AUDIT}
  AUTHZ_GENERATE_FAILURE_AUDIT = $2;
  {$EXTERNALSYM AUTHZ_GENERATE_FAILURE_AUDIT}

type
  PAUTHZ_ACCESS_REPLY = ^AUTHZ_ACCESS_REPLY;
  {$EXTERNALSYM PAUTHZ_ACCESS_REPLY}
  _AUTHZ_ACCESS_REPLY = record
    //
    // The length of the array representing the object type list structure. If
    // no object type is used to represent the object, then the length must be
    // set to 1.
    //
    // Note: This parameter must be filled!
    //
    ResultListLength: DWORD;
    //
    // Array of granted access masks. This memory is allocated by the RM. Access
    // check routines just fill in the values.
    //
    GrantedAccessMask: PACCESS_MASK;
    //
    // Array of SACL evaluation results.  This memory is allocated by the RM, if SACL
    // evaluation results are desired. Access check routines just fill in the values.
    // Sacl evaluation will only be performed if auditing is requested.
    //
    SaclEvaluationResults: PDWORD;
    //
    // Array of results for each element of the array. This memory is allocated
    // by the RM. Access check routines just fill in the values.
    //
    Error: PDWORD;
  end;
  {$EXTERNALSYM _AUTHZ_ACCESS_REPLY}
  AUTHZ_ACCESS_REPLY = _AUTHZ_ACCESS_REPLY;
  {$EXTERNALSYM AUTHZ_ACCESS_REPLY}
  TAuthzAccessReply = AUTHZ_ACCESS_REPLY;
  PAuthzAccessReply = PAUTHZ_ACCESS_REPLY;


//
// Typedefs for callback functions to be provided by the resource manager.
//

//
// Callback access check function takes in
//     AuthzClientContext - a client context
//     pAce - pointer to a callback ace
//     pArgs - Optional arguments that were passed to AuthzAccessCheck thru
//             AuthzAccessRequest->OptionalArguments are passed back here.
//     pbAceApplicable - The resource manager must supply whether the ace should
//         be used in the computation of access evaluation
//
// Returns
//     TRUE if the API succeeded.
//     FALSE on any intermediate errors (like failed memory allocation)
//         In case of failure, the caller must use SetLastError(ErrorValue).
//

type
  PFN_AUTHZ_DYNAMIC_ACCESS_CHECK = function (hAuthzClientContext: AUTHZ_CLIENT_CONTEXT_HANDLE;
    pAce: PACE_HEADER; pArgs: PVOID; var pbAceApplicable: BOOL): BOOL; stdcall;
  {$EXTERNALSYM PFN_AUTHZ_DYNAMIC_ACCESS_CHECK}
  PFnAuthzDynamicAccessCheck = PFN_AUTHZ_DYNAMIC_ACCESS_CHECK;

//
// Callback compute dynamic groups function takes in
//     AuthzClientContext - a client context
//     pArgs - Optional arguments that supplied to AuthzInitializeClientContext*
//         thru DynamicGroupArgs are passed back here..
//     pSidAttrArray - To allocate and return an array of (sids, attribute)
//         pairs to be added to the normal part of the client context.
//     pSidCount - Number of elements in pSidAttrArray
//     pRestrictedSidAttrArray - To allocate and return an array of (sids, attribute)
//         pairs to be added to the restricted part of the client context.
//     pRestrictedSidCount - Number of elements in pRestrictedSidAttrArray
//
// Note:
//    Memory returned thru both these array will be freed by the callback
//    free function defined by the resource manager.
//
// Returns
//     TRUE if the API succeeded.
//     FALSE on any intermediate errors (like failed memory allocation)
//         In case of failure, the caller must use SetLastError(ErrorValue).
//

type
  PFN_AUTHZ_COMPUTE_DYNAMIC_GROUPS = function (hAuthzClientContext: AUTHZ_CLIENT_CONTEXT_HANDLE;
    Args: PVOID; var pSidAttrArray: PSID_AND_ATTRIBUTES; var pSidCount: DWORD;
    var pRestrictedSidAttrArray: PSID_AND_ATTRIBUTES; var pRestrictedSidCount: DWORD): BOOL; stdcall;
  {$EXTERNALSYM PFN_AUTHZ_COMPUTE_DYNAMIC_GROUPS}
  PFnAuthzComputeDynamicGroups = PFN_AUTHZ_COMPUTE_DYNAMIC_GROUPS;

//
// Callback free function takes in
//     pSidAttrArray - To be freed. This has been allocated by the compute
//     dynamic groups function.
//

  PFN_AUTHZ_FREE_DYNAMIC_GROUPS = procedure (pSidAttrArray: PSID_AND_ATTRIBUTES); stdcall;
  {$EXTERNALSYM PFN_AUTHZ_FREE_DYNAMIC_GROUPS}
  PFnAuthzFreeDynamicGroups = PFN_AUTHZ_FREE_DYNAMIC_GROUPS;

//
// Valid flags for AuthzAccessCheck
//

const
  AUTHZ_ACCESS_CHECK_NO_DEEP_COPY_SD = $00000001;
  {$EXTERNALSYM AUTHZ_ACCESS_CHECK_NO_DEEP_COPY_SD}

function AuthzAccessCheck(Flags: DWORD; hAuthzClientContext: AUTHZ_CLIENT_CONTEXT_HANDLE; pRequest: PAUTHZ_ACCESS_REQUEST;
  hAuditEvent: AUTHZ_AUDIT_EVENT_HANDLE; pSecurityDescriptor: PSECURITY_DESCRIPTOR; OptionalSecurityDescriptorArray: PPSECURITY_DESCRIPTOR;
  OptionalSecurityDescriptorCount: DWORD; pReply: PAUTHZ_ACCESS_REPLY; phAccessCheckResultsOPTIONAL: PAUTHZ_ACCESS_CHECK_RESULTS_HANDLE): BOOL; stdcall;
{$EXTERNALSYM AuthzAccessCheck}

function AuthzCachedAccessCheck(Flags: DWORD; hAccessCheckResults: AUTHZ_ACCESS_CHECK_RESULTS_HANDLE; pRequest: PAUTHZ_ACCESS_REQUEST; hAuditEvent: AUTHZ_AUDIT_EVENT_HANDLE; pReply: PAUTHZ_ACCESS_REPLY): BOOL; stdcall;
{$EXTERNALSYM AuthzCachedAccessCheck}

function AuthzOpenObjectAudit(Flags: DWORD; hAuthzClientContext: AUTHZ_CLIENT_CONTEXT_HANDLE; pRequest: PAUTHZ_ACCESS_REQUEST; hAuditEvent: AUTHZ_AUDIT_EVENT_HANDLE; pSecurityDescriptor: PSECURITY_DESCRIPTOR; OptionalSecurityDescriptorArray: PPSECURITY_DESCRIPTOR; OptionalSecurityDescriptorCount: DWORD; pReply: PAUTHZ_ACCESS_REPLY): BOOL; stdcall;
{$EXTERNALSYM AuthzOpenObjectAudit}

function AuthzFreeHandle(hAccessCheckResults: AUTHZ_ACCESS_CHECK_RESULTS_HANDLE): BOOL; stdcall;
{$EXTERNALSYM AuthzFreeHandle}

//
// Flags for AuthzInitializeResourceManager
//

const
  AUTHZ_RM_FLAG_NO_AUDIT = $1;
  {$EXTERNALSYM AUTHZ_RM_FLAG_NO_AUDIT}

  AUTHZ_RM_FLAG_INITIALIZE_UNDER_IMPERSONATION = $2;
  {$EXTERNALSYM AUTHZ_RM_FLAG_INITIALIZE_UNDER_IMPERSONATION}

  AUTHZ_VALID_RM_INIT_FLAGS = (AUTHZ_RM_FLAG_NO_AUDIT or AUTHZ_RM_FLAG_INITIALIZE_UNDER_IMPERSONATION);
  {$EXTERNALSYM AUTHZ_VALID_RM_INIT_FLAGS}

function AuthzInitializeResourceManager(Flags: DWORD; pfnDynamicAccessCheck: PFN_AUTHZ_DYNAMIC_ACCESS_CHECK; pfnComputeDynamicGroups: PFN_AUTHZ_COMPUTE_DYNAMIC_GROUPS; pfnFreeDynamicGroups: PFN_AUTHZ_FREE_DYNAMIC_GROUPS; szResourceManagerName: LPCWSTR; phAuthzResourceManager: PAUTHZ_RESOURCE_MANAGER_HANDLE): BOOL; stdcall;
{$EXTERNALSYM AuthzInitializeResourceManager}

function AuthzFreeResourceManager(hAuthzResourceManager: AUTHZ_RESOURCE_MANAGER_HANDLE): BOOL; stdcall;
{$EXTERNALSYM AuthzFreeResourceManager}

function AuthzInitializeContextFromToken(Flags: DWORD; TokenHandle: HANDLE; hAuthzResourceManager: AUTHZ_RESOURCE_MANAGER_HANDLE; pExpirationTime: PLARGE_INTEGER; Identifier: LUID; DynamicGroupArgs: PVOID; phAuthzClientContext: PAUTHZ_CLIENT_CONTEXT_HANDLE): BOOL; stdcall;
{$EXTERNALSYM AuthzInitializeContextFromToken}

function AuthzInitializeContextFromSid(Flags: DWORD; UserSid: PSID; hAuthzResourceManager: AUTHZ_RESOURCE_MANAGER_HANDLE; pExpirationTime: PLARGE_INTEGER; Identifier: LUID; DynamicGroupArgs: PVOID; phAuthzClientContext: PAUTHZ_CLIENT_CONTEXT_HANDLE): BOOL; stdcall;
{$EXTERNALSYM AuthzInitializeContextFromSid}

function AuthzInitializeContextFromAuthzContext(Flags: DWORD; hAuthzClientContext: AUTHZ_CLIENT_CONTEXT_HANDLE; pExpirationTime: PLARGE_INTEGER; Identifier: LUID; DynamicGroupArgs: PVOID; phNewAuthzClientContext: PAUTHZ_CLIENT_CONTEXT_HANDLE): BOOL; stdcall;
{$EXTERNALSYM AuthzInitializeContextFromAuthzContext}

function AuthzAddSidsToContext(hAuthzClientContext: AUTHZ_CLIENT_CONTEXT_HANDLE; Sids: PSID_AND_ATTRIBUTES; SidCount: DWORD; RestrictedSids: PSID_AND_ATTRIBUTES; RestrictedSidCount: DWORD; phNewAuthzClientContext: PAUTHZ_CLIENT_CONTEXT_HANDLE): BOOL; stdcall;
{$EXTERNALSYM AuthzAddSidsToContext}

//
// Enumeration type to be used to specify the type of information to be
// retrieved from an existing AuthzClientContext.
//

type
  _AUTHZ_CONTEXT_INFORMATION_CLASS = (
    AuthzContextInfo__0,
    AuthzContextInfoUserSid,
    AuthzContextInfoGroupsSids,
    AuthzContextInfoRestrictedSids,
    AuthzContextInfoPrivileges,
    AuthzContextInfoExpirationTime,
    AuthzContextInfoServerContext,
    AuthzContextInfoIdentifier,
    AuthzContextInfoSource,
    AuthzContextInfoAll,
    AuthzContextInfoAuthenticationId);
  {$EXTERNALSYM _AUTHZ_CONTEXT_INFORMATION_CLASS}
  AUTHZ_CONTEXT_INFORMATION_CLASS = _AUTHZ_CONTEXT_INFORMATION_CLASS;
  {$EXTERNALSYM AUTHZ_CONTEXT_INFORMATION_CLASS}
  TAuthzContextInformationClass = AUTHZ_CONTEXT_INFORMATION_CLASS;

function AuthzGetInformationFromContext(hAuthzClientContext: AUTHZ_CLIENT_CONTEXT_HANDLE; InfoClass: AUTHZ_CONTEXT_INFORMATION_CLASS; BufferSize: DWORD; pSizeRequired: PDWORD; Buffer: PVOID): BOOL; stdcall;
{$EXTERNALSYM AuthzGetInformationFromContext}

function AuthzFreeContext(hAuthzClientContext: AUTHZ_CLIENT_CONTEXT_HANDLE): BOOL; stdcall;
{$EXTERNALSYM AuthzFreeContext}

//
// Valid flags that may be used in AuthzInitializeObjectAccessAuditEvent().
//

const
  AUTHZ_NO_SUCCESS_AUDIT = $00000001;
  {$EXTERNALSYM AUTHZ_NO_SUCCESS_AUDIT}
  AUTHZ_NO_FAILURE_AUDIT = $00000002;
  {$EXTERNALSYM AUTHZ_NO_FAILURE_AUDIT}
  AUTHZ_NO_ALLOC_STRINGS = $00000004;
  {$EXTERNALSYM AUTHZ_NO_ALLOC_STRINGS}

  AUTHZ_VALID_OBJECT_ACCESS_AUDIT_FLAGS = (AUTHZ_NO_SUCCESS_AUDIT or AUTHZ_NO_FAILURE_AUDIT or AUTHZ_NO_ALLOC_STRINGS);
  {$EXTERNALSYM AUTHZ_VALID_OBJECT_ACCESS_AUDIT_FLAGS}

function AuthzInitializeObjectAccessAuditEvent(Flags: DWORD; hAuditEventType: AUTHZ_AUDIT_EVENT_TYPE_HANDLE; szOperationType: PWSTR; szObjectType: PWSTR; szObjectName: PWSTR; szAdditionalInfo: PWSTR; phAuditEvent: PAUTHZ_AUDIT_EVENT_HANDLE; dwAdditionalParameterCount: DWORD {, ...}): BOOL; stdcall;
{$EXTERNALSYM AuthzInitializeObjectAccessAuditEvent}

function AuthzInitializeObjectAccessAuditEvent2(Flags: DWORD; hAuditEventType: AUTHZ_AUDIT_EVENT_TYPE_HANDLE; szOperationType: PWSTR; szObjectType: PWSTR; szObjectName: PWSTR; szAdditionalInfo, szAdditionalInfo2: PWSTR; phAuditEvent: PAUTHZ_AUDIT_EVENT_HANDLE; dwAdditionalParameterCount: DWORD {, ...}): BOOL; stdcall;
{$EXTERNALSYM AuthzInitializeObjectAccessAuditEvent2}

//
// Enumeration type to be used to specify the type of information to be
// retrieved from an existing AUTHZ_AUDIT_EVENT_HANDLE.
//

type
  _AUTHZ_AUDIT_EVENT_INFORMATION_CLASS = (
    AuthzAuditEvent__0,
    AuthzAuditEventInfoFlags,
    AuthzAuditEventInfoOperationType,
    AuthzAuditEventInfoObjectType,
    AuthzAuditEventInfoObjectName,
    AuthzAuditEventInfoAdditionalInfo);
  {$EXTERNALSYM _AUTHZ_AUDIT_EVENT_INFORMATION_CLASS}
  AUTHZ_AUDIT_EVENT_INFORMATION_CLASS = _AUTHZ_AUDIT_EVENT_INFORMATION_CLASS;
  {$EXTERNALSYM AUTHZ_AUDIT_EVENT_INFORMATION_CLASS}
  AuthzAuditEventInformationClass = AUTHZ_AUDIT_EVENT_INFORMATION_CLASS;

// todo this one seems not to be exported from authz.dll

function AuthzGetInformationFromAuditEvent(hAuditEvent: AUTHZ_AUDIT_EVENT_HANDLE; InfoClass: AUTHZ_AUDIT_EVENT_INFORMATION_CLASS; BufferSize: DWORD; pSizeRequired: PDWORD; Buffer: PVOID): BOOL; stdcall;
{$EXTERNALSYM AuthzGetInformationFromAuditEvent}

function AuthzFreeAuditEvent(hAuditEvent: AUTHZ_AUDIT_EVENT_HANDLE): BOOL; stdcall;
{$EXTERNALSYM AuthzFreeAuditEvent}

(* TODO
//
// Support for generic auditing.
//

typedef struct _AUTHZ_REGISTRATION_OBJECT_TYPE_NAME_OFFSET
{
    PWSTR szObjectTypeName;
    DWORD dwOffset;
} AUTHZ_REGISTRATION_OBJECT_TYPE_NAME_OFFSET, *PAUTHZ_REGISTRATION_OBJECT_TYPE_NAME_OFFSET;

typedef struct _AUTHZ_SOURCE_SCHEMA_REGISTRATION
{
    DWORD dwFlags;
    PWSTR szEventSourceName;
    PWSTR szEventMessageFile;
    PWSTR szEventSourceXmlSchemaFile;
    PWSTR szEventAccessStringsFile;
    PWSTR szExecutableImagePath;
    PVOID pReserved;
    DWORD dwObjectTypeNameCount;
    AUTHZ_REGISTRATION_OBJECT_TYPE_NAME_OFFSET ObjectTypeNames[ANYSIZE_ARRAY];
} AUTHZ_SOURCE_SCHEMA_REGISTRATION, *PAUTHZ_SOURCE_SCHEMA_REGISTRATION;

#define AUTHZ_FLAG_ALLOW_MULTIPLE_SOURCE_INSTANCES 0x1

AUTHZAPI
BOOL 
WINAPI
AuthzInstallSecurityEventSource(
    IN DWORD                             dwFlags,
    IN PAUTHZ_SOURCE_SCHEMA_REGISTRATION pRegistration
    );

AUTHZAPI
BOOL
WINAPI
AuthzUninstallSecurityEventSource(
    IN DWORD  dwFlags,
    IN PCWSTR szEventSourceName
    );


AUTHZAPI
BOOL
WINAPI
AuthzEnumerateSecurityEventSources(
    IN     DWORD                             dwFlags,
    OUT    PAUTHZ_SOURCE_SCHEMA_REGISTRATION Buffer,
    OUT    PDWORD                            pdwCount,
    IN OUT PDWORD                            pdwLength
    );
    
AUTHZAPI
BOOL
WINAPI
AuthzRegisterSecurityEventSource(
    IN  DWORD                                 dwFlags,
    IN  PCWSTR                                szEventSourceName,
    OUT PAUTHZ_SECURITY_EVENT_PROVIDER_HANDLE phEventProvider
    );
    
AUTHZAPI
BOOL
WINAPI
AuthzUnregisterSecurityEventSource(
    IN     DWORD                                 dwFlags,
    IN OUT PAUTHZ_SECURITY_EVENT_PROVIDER_HANDLE phEventProvider
    );

AUTHZAPI
BOOL
WINAPI
AuthzReportSecurityEvent(
    IN     DWORD                                dwFlags,
    IN OUT AUTHZ_SECURITY_EVENT_PROVIDER_HANDLE hEventProvider,
    IN     DWORD                                dwAuditId,
    IN     PSID                                 pUserSid        OPTIONAL,
    IN     DWORD                                dwCount,
    ...    
    );

AUTHZAPI
BOOL
WINAPI
AuthzReportSecurityEventFromParams(
    IN     DWORD                                dwFlags,
    IN OUT AUTHZ_SECURITY_EVENT_PROVIDER_HANDLE hEventProvider,
    IN     DWORD                                dwAuditId,
    IN     PSID                                 pUserSid       OPTIONAL,
    IN     PAUDIT_PARAMS                        pParams
    );
*)

implementation

const
  authz_lib = 'authz.dll';


{$IFDEF DYNAMIC_LINK}
var
  _AuthzAccessCheck: Pointer;

function AuthzAccessCheck;
begin
  GetProcedureAddress(_AuthzAccessCheck, authz_lib, 'AuthzAccessCheck');
  asm
    mov esp, ebp
    pop ebp
    jmp [_AuthzAccessCheck]
  end;
end;
{$ELSE}
function AuthzAccessCheck; external authz_lib name 'AuthzAccessCheck';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _AuthzCachedAccessCheck: Pointer;

function AuthzCachedAccessCheck;
begin
  GetProcedureAddress(_AuthzCachedAccessCheck, authz_lib, 'AuthzCachedAccessCheck');
  asm
    mov esp, ebp
    pop ebp
    jmp [_AuthzCachedAccessCheck]
  end;
end;
{$ELSE}
function AuthzCachedAccessCheck; external authz_lib name 'AuthzCachedAccessCheck';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _AuthzOpenObjectAudit: Pointer;

function AuthzOpenObjectAudit;
begin
  GetProcedureAddress(_AuthzOpenObjectAudit, authz_lib, 'AuthzOpenObjectAudit');
  asm
    mov esp, ebp
    pop ebp
    jmp [_AuthzOpenObjectAudit]
  end;
end;
{$ELSE}
function AuthzOpenObjectAudit; external authz_lib name 'AuthzOpenObjectAudit';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _AuthzFreeHandle: Pointer;

function AuthzFreeHandle;
begin
  GetProcedureAddress(_AuthzFreeHandle, authz_lib, 'AuthzFreeHandle');
  asm
    mov esp, ebp
    pop ebp
    jmp [_AuthzFreeHandle]
  end;
end;
{$ELSE}
function AuthzFreeHandle; external authz_lib name 'AuthzFreeHandle';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _AuthzInitializeResourceManager: Pointer;

function AuthzInitializeResourceManager;
begin
  GetProcedureAddress(_AuthzInitializeResourceManager, authz_lib, 'AuthzInitializeResourceManager');
  asm
    mov esp, ebp
    pop ebp
    jmp [_AuthzInitializeResourceManager]
  end;
end;
{$ELSE}
function AuthzInitializeResourceManager; external authz_lib name 'AuthzInitializeResourceManager';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _AuthzFreeResourceManager: Pointer;

function AuthzFreeResourceManager;
begin
  GetProcedureAddress(_AuthzFreeResourceManager, authz_lib, 'AuthzFreeResourceManager');
  asm
    mov esp, ebp
    pop ebp
    jmp [_AuthzFreeResourceManager]
  end;
end;
{$ELSE}
function AuthzFreeResourceManager; external authz_lib name 'AuthzFreeResourceManager';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _AuthzInitializeContextFromToken: Pointer;

function AuthzInitializeContextFromToken;
begin
  GetProcedureAddress(_AuthzInitializeContextFromToken, authz_lib, 'AuthzInitializeContextFromToken');
  asm
    mov esp, ebp
    pop ebp
    jmp [_AuthzInitializeContextFromToken]
  end;
end;
{$ELSE}
function AuthzInitializeContextFromToken; external authz_lib name 'AuthzInitializeContextFromToken';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _AuthzInitializeContextFromSid: Pointer;

function AuthzInitializeContextFromSid;
begin
  GetProcedureAddress(_AuthzInitializeContextFromSid, authz_lib, 'AuthzInitializeContextFromSid');
  asm
    mov esp, ebp
    pop ebp
    jmp [_AuthzInitializeContextFromSid]
  end;
end;
{$ELSE}
function AuthzInitializeContextFromSid; external authz_lib name 'AuthzInitializeContextFromSid';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _AuthzInitCxtFromAuthzCxt: Pointer;

function AuthzInitializeContextFromAuthzContext;
begin
  GetProcedureAddress(_AuthzInitCxtFromAuthzCxt, authz_lib, 'AuthzInitializeContextFromAuthzContext');
  asm
    mov esp, ebp
    pop ebp
    jmp [_AuthzInitCxtFromAuthzCxt]
  end;
end;
{$ELSE}
function AuthzInitializeContextFromAuthzContext; external authz_lib name 'AuthzInitializeContextFromAuthzContext';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _AuthzAddSidsToContext: Pointer;

function AuthzAddSidsToContext;
begin
  GetProcedureAddress(_AuthzAddSidsToContext, authz_lib, 'AuthzAddSidsToContext');
  asm
    mov esp, ebp
    pop ebp
    jmp [_AuthzAddSidsToContext]
  end;
end;
{$ELSE}
function AuthzAddSidsToContext; external authz_lib name 'AuthzAddSidsToContext';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _AuthzGetInformationFromContext: Pointer;

function AuthzGetInformationFromContext;
begin
  GetProcedureAddress(_AuthzGetInformationFromContext, authz_lib, 'AuthzGetInformationFromContext');
  asm
    mov esp, ebp
    pop ebp
    jmp [_AuthzGetInformationFromContext]
  end;
end;
{$ELSE}
function AuthzGetInformationFromContext; external authz_lib name 'AuthzGetInformationFromContext';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _AuthzFreeContext: Pointer;

function AuthzFreeContext;
begin
  GetProcedureAddress(_AuthzFreeContext, authz_lib, 'AuthzFreeContext');
  asm
    mov esp, ebp
    pop ebp
    jmp [_AuthzFreeContext]
  end;
end;
{$ELSE}
function AuthzFreeContext; external authz_lib name 'AuthzFreeContext';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _AuthzInitObjAccAuditEvent: Pointer;

function AuthzInitializeObjectAccessAuditEvent;
begin
  GetProcedureAddress(_AuthzInitObjAccAuditEvent, authz_lib, 'AuthzInitializeObjectAccessAuditEvent');
  asm
    mov esp, ebp
    pop ebp
    jmp [_AuthzInitObjAccAuditEvent]
  end;
end;
{$ELSE}
function AuthzInitializeObjectAccessAuditEvent; external authz_lib name 'AuthzInitializeObjectAccessAuditEvent';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _AuthzInitObjAccAuditEvent2: Pointer;

function AuthzInitializeObjectAccessAuditEvent2;
begin
  GetProcedureAddress(_AuthzInitObjAccAuditEvent2, authz_lib, 'AuthzInitializeObjectAccessAuditEvent2');
  asm
    mov esp, ebp
    pop ebp
    jmp [_AuthzInitObjAccAuditEvent2]
  end;
end;
{$ELSE}
function AuthzInitializeObjectAccessAuditEvent2; external authz_lib name 'AuthzInitializeObjectAccessAuditEvent2';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _AuthzGetInfoFromAuditEvent: Pointer;

function AuthzGetInformationFromAuditEvent;
begin
  GetProcedureAddress(_AuthzGetInfoFromAuditEvent, authz_lib, 'AuthzGetInformationFromAuditEvent');
  asm
    mov esp, ebp
    pop ebp
    jmp [_AuthzGetInfoFromAuditEvent]
  end;
end;
{$ELSE}
function AuthzGetInformationFromAuditEvent; external authz_lib name 'AuthzGetInformationFromAuditEvent';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _AuthzFreeAuditEvent: Pointer;

function AuthzFreeAuditEvent;
begin
  GetProcedureAddress(_AuthzFreeAuditEvent, authz_lib, 'AuthzFreeAuditEvent');
  asm
    mov esp, ebp
    pop ebp
    jmp [_AuthzFreeAuditEvent]
  end;
end;
{$ELSE}
function AuthzFreeAuditEvent; external authz_lib name 'AuthzFreeAuditEvent';
{$ENDIF DYNAMIC_LINK}

end.
