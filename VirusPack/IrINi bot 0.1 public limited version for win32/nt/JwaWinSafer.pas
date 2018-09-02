{******************************************************************************}
{                                                       	               }
{ Windows Safer API interface Unit for Object Pascal                           }
{                                                       	               }
{ Portions created by Microsoft are Copyright (C) 1995-2001 Microsoft          }
{ Corporation. All Rights Reserved.                                            }
{ 								               }
{ The original file is: winsafer.h, released Nov 2001. The original Pascal     }
{ code is: WinSafer.pas, released Februari 2002. The initial developer of the  }
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

unit JwaWinSafer;

{$WEAKPACKAGEUNIT}

{$HPPEMIT ''}
{$HPPEMIT '#include "winsafer.h"'}
{$HPPEMIT ''}

{$I WINDEFINES.INC}

interface

uses
  JwaWinCrypt, JwaWinType;

//
// Opaque datatype for representing handles to Safer objects.
//

type
  SAFER_LEVEL_HANDLE = HANDLE;
  {$EXTERNALSYM SAFER_LEVEL_HANDLE}
  PSAFER_LEVEL_HANDLE = ^SAFER_LEVEL_HANDLE;
  {$EXTERNALSYM PSAFER_LEVEL_HANDLE}
  TSaferLevelHandle = SAFER_LEVEL_HANDLE;
  PSaferLevelHandle = PSAFER_LEVEL_HANDLE;

//
// Constants to represent scope with SaferCreateLevel and others.
//

const
  SAFER_SCOPEID_MACHINE = 1;
  {$EXTERNALSYM SAFER_SCOPEID_MACHINE}
  SAFER_SCOPEID_USER    = 2;
  {$EXTERNALSYM SAFER_SCOPEID_USER}

//
// Pre-defined levels that can be used with SaferCreateLevel
//

  SAFER_LEVELID_FULLYTRUSTED = $40000;
  {$EXTERNALSYM SAFER_LEVELID_FULLYTRUSTED}
  SAFER_LEVELID_NORMALUSER   = $20000;
  {$EXTERNALSYM SAFER_LEVELID_NORMALUSER}
  SAFER_LEVELID_CONSTRAINED  = $10000;
  {$EXTERNALSYM SAFER_LEVELID_CONSTRAINED}
  SAFER_LEVELID_UNTRUSTED    = $01000;
  {$EXTERNALSYM SAFER_LEVELID_UNTRUSTED}
  SAFER_LEVELID_DISALLOWED   = $00000;
  {$EXTERNALSYM SAFER_LEVELID_DISALLOWED}

//
// Flags to use when creating/opening a Level with SaferCreateLevel
//

  SAFER_LEVEL_OPEN = 1;
  {$EXTERNALSYM SAFER_LEVEL_OPEN}

//
// Maximum string size.
//

  SAFER_MAX_FRIENDLYNAME_SIZE = 256;
  {$EXTERNALSYM SAFER_MAX_FRIENDLYNAME_SIZE}
  SAFER_MAX_DESCRIPTION_SIZE  = 256;
  {$EXTERNALSYM SAFER_MAX_DESCRIPTION_SIZE}
  SAFER_MAX_HASH_SIZE         = 64;
  {$EXTERNALSYM SAFER_MAX_HASH_SIZE}

//
// Flags to use with SaferComputeTokenFromLevel.
//

  SAFER_TOKEN_NULL_IF_EQUAL = $00000001;
  {$EXTERNALSYM SAFER_TOKEN_NULL_IF_EQUAL}
  SAFER_TOKEN_COMPARE_ONLY  = $00000002;
  {$EXTERNALSYM SAFER_TOKEN_COMPARE_ONLY}
  SAFER_TOKEN_MAKE_INERT    = $00000004;
  {$EXTERNALSYM SAFER_TOKEN_MAKE_INERT}
  SAFER_TOKEN_WANT_FLAGS    = $00000008;
  {$EXTERNALSYM SAFER_TOKEN_WANT_FLAGS}

//
// Flags for specifying what criteria within SAFER_CODE_PROPERTIES to evaluate
// when finding code identity with SaferIdentifyLevel.
//

  SAFER_CRITERIA_IMAGEPATH    = $00001;
  {$EXTERNALSYM SAFER_CRITERIA_IMAGEPATH}
  SAFER_CRITERIA_NOSIGNEDHASH = $00002;
  {$EXTERNALSYM SAFER_CRITERIA_NOSIGNEDHASH}
  SAFER_CRITERIA_IMAGEHASH    = $00004;
  {$EXTERNALSYM SAFER_CRITERIA_IMAGEHASH}
  SAFER_CRITERIA_AUTHENTICODE = $00008;
  {$EXTERNALSYM SAFER_CRITERIA_AUTHENTICODE}
  SAFER_CRITERIA_URLZONE      = $00010;
  {$EXTERNALSYM SAFER_CRITERIA_URLZONE}
  SAFER_CRITERIA_IMAGEPATH_NT = $01000;
  {$EXTERNALSYM SAFER_CRITERIA_IMAGEPATH_NT}

//
// Code image information structure passed to SaferIdentifyLevel.
//

// #include <pshpack8.h> todo

type
  _SAFER_CODE_PROPERTIES = record
    //
    // Must be initialized to be the size of this structure,
    // for the purposes of future/backwards compatibility.
    //
    cbSize: DWORD;
    //
    // Must be initialized to the types of criteria that should
    // be considered when evaluating this structure.  This can be
    // a combination of the SAFER_CRITERIA_xxxx flags.  If not enough
    // of the structure elements needed to evaluate the criteria
    // types indicated were supplied, then some of those criteria
    // flags may be silently ignored.  Specifying 0 for this value
    // will cause the entire structure's contents to be ignored.
    //
    dwCheckFlags: DWORD;
    //
    // Optionally specifies the fully-qualified path and filename
    // to be used for discrimination checks based on the path.
    // The ImagePath will additionally be used to open and read the
    // file to identify any other discrimination criteria that was
    // unsupplied in this structure.
    //
    ImagePath: LPCWSTR;
    //
    // Optionally specifies a file handle that has been opened to
    // code image with at least GENERIC_READ access.  The handle will
    // be used instead of explicitly opening the file again to compute
    // other discrimination criteria that was unsupplied in this structure.
    //
    hImageFileHandle: HANDLE;
    //
    // Optionally specifies the pre-determined Internet Explorer
    // security zone.  These enums are defined within urlmon.h
    // For example: URLZONE_LOCAL_MACHINE, URLZONE_INTRANET,
    //   URLZONE_TRUSTED, URLZONE_INTERNET, or URLZONE_UNTRUSTED.
    //
    UrlZoneId: DWORD;
    //
    // Optionally specifies the pre-computed hash of the image.
    // The supplied hash is interpreted as being valid if ImageSize
    // is non-zero and dwImageHashSize is non-zero and HashAlgorithm
    // represents a valid hashing algorithm from wincrypt.h
    //
    // If the supplied hash fails to meet the conditions above, then
    // the hash will be automatically computed against:
    //      1) by using ImageSize and pByteBlock if both are non-zero.
    //      2) by using hImageFileHandle if it is non-null.
    //      3) by attempting to open ImagePath if it is non-null.
    //
    ImageHash: array [0..SAFER_MAX_HASH_SIZE - 1] of BYTE;
    dwImageHashSize: DWORD;
    ImageSize: LARGE_INTEGER;
    HashAlgorithm: ALG_ID;
    //
    // Optionally specifies a memory block of memory representing
    // the image for which the trust is being requested for.  When
    // this member is specified, ImageSize must also be supplied.
    //
    pByteBlock: LPBYTE;
    //
    // Optionally gives the arguments used for Authenticode signer
    // certificate verification.  These arguments are supplied to the
    // WinVerifyTrust() API and control the user-interface prompting
    // to accept untrusted certificates.
    //
    hWndParent: HWND;
    dwWVTUIChoice: DWORD;
  end;
  {$EXTERNALSYM _SAFER_CODE_PROPERTIES}
  SAFER_CODE_PROPERTIES = _SAFER_CODE_PROPERTIES;
  {$EXTERNALSYM SAFER_CODE_PROPERTIES}
  PSAFER_CODE_PROPERTIES = ^SAFER_CODE_PROPERTIES;
  {$EXTERNALSYM PSAFER_CODE_PROPERTIES}
  TSaferCodeProperties = SAFER_CODE_PROPERTIES;
  PSaferCodeProperties = PSAFER_CODE_PROPERTIES;

// #include <poppack.h>

//
// Masks for the per-identity WinSafer flags
//

const
  SAFER_POLICY_JOBID_MASK                 = DWORD($FF000000);
  {$EXTERNALSYM SAFER_POLICY_JOBID_MASK}
  SAFER_POLICY_JOBID_CONSTRAINED          = $04000000;
  {$EXTERNALSYM SAFER_POLICY_JOBID_CONSTRAINED}
  SAFER_POLICY_JOBID_UNTRUSTED            = $03000000;
  {$EXTERNALSYM SAFER_POLICY_JOBID_UNTRUSTED}
  SAFER_POLICY_ONLY_EXES                  = $00010000;
  {$EXTERNALSYM SAFER_POLICY_ONLY_EXES}
  SAFER_POLICY_SANDBOX_INERT              = $00020000;
  {$EXTERNALSYM SAFER_POLICY_SANDBOX_INERT}
  SAFER_POLICY_UIFLAGS_MASK               = $000000FF;
  {$EXTERNALSYM SAFER_POLICY_UIFLAGS_MASK}
  SAFER_POLICY_UIFLAGS_INFORMATION_PROMPT = $00000001;
  {$EXTERNALSYM SAFER_POLICY_UIFLAGS_INFORMATION_PROMPT}
  SAFER_POLICY_UIFLAGS_OPTION_PROMPT      = $00000002;
  {$EXTERNALSYM SAFER_POLICY_UIFLAGS_OPTION_PROMPT}

//
// Information classes on the overall policy that can be queried
// with SaferSet/GetPolicyInformation and set at different
// policy scopes based on access of the caller.
//

type
  _SAFER_POLICY_INFO_CLASS = (

    spicFiller0,

    //
    // Accesses the list of all Levels defined in a policy.
    // The corresponding data element is a buffer that is filled
    // with multiple DWORDs, each representing the LevelIds that
    // are defined within this scope.
    //
    
    SaferPolicyLevelList,

    //
    // for transparent enforcement of policy in the execution
    // framework -- will be used by native code execution but can
    // be used by any policy enforcement environment.
    // Corresponding data element is a DWORD holding a Boolean value.
    //
    
    SaferPolicyEnableTransparentEnforcement,

    //
    // Returns the name of the Level that has been designed
    // as the default level within the specified scope.
    // The corresponding data element is a single DWORD buffer
    // representing the LevelId of the default Level.  If no
    // level has been configured to be the default, then the
    // GetInfo API will return FALSE and GetLastError will
    // return ERROR_NOT_FOUND.
    //
    
    SaferPolicyDefaultLevel,

    //
    // Returns whether Code Identities or Default Level within the
    // user scope can be considered during identification.
    //
    
    SaferPolicyEvaluateUserScope,
    
    //
    // Control Flags for for safer policy scope.
    //
    
    SaferPolicyScopeFlags);
  {$EXTERNALSYM _SAFER_POLICY_INFO_CLASS}
  SAFER_POLICY_INFO_CLASS = _SAFER_POLICY_INFO_CLASS;
  {$EXTERNALSYM SAFER_POLICY_INFO_CLASS}
  TSaferPolicyInfoClass = SAFER_POLICY_INFO_CLASS;

//
// Enumerations used for retrieving specific information about a
// single authorization Level via SaferGet/SetInformationFromLevel.
//

  _SAFER_OBJECT_INFO_CLASS = (
    soicFillter0,
    SaferObjectLevelId,               // get: DWORD
    SaferObjectScopeId,                   // get: DWORD
    SaferObjectFriendlyName,              // get/set: LPCWSTR 
    SaferObjectDescription,               // get/set: LPCWSTR
    SaferObjectBuiltin,                   // get: DWORD boolean
    SaferObjectDisallowed,                // get: DWORD boolean
    SaferObjectDisableMaxPrivilege,       // get: DWORD boolean
    SaferObjectInvertDeletedPrivileges,   // get: DWORD boolean
    SaferObjectDeletedPrivileges,         // get: TOKEN_PRIVILEGES
    SaferObjectDefaultOwner,              // get: TOKEN_OWNER
    SaferObjectSidsToDisable,             // get: TOKEN_GROUPS
    SaferObjectRestrictedSidsInverted,    // get: TOKEN_GROUPS
    SaferObjectRestrictedSidsAdded,       // get: TOKEN_GROUPS

    //
    // To enumerate all identities, call GetInfo with
    //      SaferObjectAllIdentificationGuids.
    //
    
    SaferObjectAllIdentificationGuids,    // get: SAFER_IDENTIFICATION_GUIDS

    //
    // To create a new identity, call SetInfo with
    //      SaferObjectSingleIdentification with a new
    //      unique GUID that you have generated.
    // To get details on a single identity, call GetInfo with
    //      SaferObjectSingleIdentification with desired GUID.
    // To modify details of a single identity, call SetInfo with
    //      SaferObjectSingleIdentification with desired info and GUID.
    // To delete an identity, call SetInfo with
    //      SaferObjectSingleIdentification with the
    //      header.dwIdentificationType set to 0.
    //
    
    SaferObjectSingleIdentification,      // get/set: SAFER_IDENTIFICATION_*

    SaferObjectExtendedError);            // get: DWORD dwError
  {$EXTERNALSYM _SAFER_OBJECT_INFO_CLASS}
  SAFER_OBJECT_INFO_CLASS = _SAFER_OBJECT_INFO_CLASS;
  {$EXTERNALSYM SAFER_OBJECT_INFO_CLASS}
  TSaferObjectInfoClass = SAFER_OBJECT_INFO_CLASS;

//
// Structures and enums used by the SaferGet/SetLevelInformation APIs.
//

// #include <pshpack8.h> todo

  _SAFER_IDENTIFICATION_TYPES = (
    SaferIdentityDefault,
    SaferIdentityTypeImageName,
    SaferIdentityTypeImageHash,
    SaferIdentityTypeUrlZone,
    SaferIdentityTypeCertificate);
  {$EXTERNALSYM _SAFER_IDENTIFICATION_TYPES}
  SAFER_IDENTIFICATION_TYPES = _SAFER_IDENTIFICATION_TYPES;
  {$EXTERNALSYM SAFER_IDENTIFICATION_TYPES}
  TSaferIdentificationTypes = SAFER_IDENTIFICATION_TYPES;

  _SAFER_IDENTIFICATION_HEADER = record
    //
    // indicates the type of the structure, one of SaferIdentityType*
    //
    dwIdentificationType: SAFER_IDENTIFICATION_TYPES;
    //
    // size of the whole structure, not just the common header.
    //
    cbStructSize: DWORD;
    //
    // the unique GUID of the Identity in question.
    //
    IdentificationGuid: GUID;
    //
    // last change of this identification.
    //
    lastModified: FILETIME;
  end;
  {$EXTERNALSYM _SAFER_IDENTIFICATION_HEADER}
  SAFER_IDENTIFICATION_HEADER = _SAFER_IDENTIFICATION_HEADER;
  {$EXTERNALSYM SAFER_IDENTIFICATION_HEADER}
  PSAFER_IDENTIFICATION_HEADER = ^SAFER_IDENTIFICATION_HEADER;
  {$EXTERNALSYM PSAFER_IDENTIFICATION_HEADER}
  TSaferIdentificationHeader = SAFER_IDENTIFICATION_HEADER;
  PSaferIdentificationHeader = PSAFER_IDENTIFICATION_HEADER;

  _SAFER_PATHNAME_IDENTIFICATION = record
    //
    // header.dwIdentificationType must be SaferIdentityTypeImageName
    // header.cbStructSize must be sizeof(SAFER_PATHNAME_IDENTIFICATION)
    //
    header: SAFER_IDENTIFICATION_HEADER;
    //
    // user-entered description
    //
    Description: array [0..SAFER_MAX_DESCRIPTION_SIZE - 1] of WCHAR;
    //
    // filepath or name, possibly with vars
    //
    ImageName: PWCHAR;
    //
    // any combo of SAFER_POL_SAFERFLAGS_*
    //
    dwSaferFlags: DWORD;
  end;
  {$EXTERNALSYM _SAFER_PATHNAME_IDENTIFICATION}
  SAFER_PATHNAME_IDENTIFICATION = _SAFER_PATHNAME_IDENTIFICATION;
  {$EXTERNALSYM SAFER_PATHNAME_IDENTIFICATION}
  PSAFER_PATHNAME_IDENTIFICATION = ^SAFER_PATHNAME_IDENTIFICATION;
  {$EXTERNALSYM PSAFER_PATHNAME_IDENTIFICATION}
  TSaferPathNameIdentification = SAFER_PATHNAME_IDENTIFICATION;
  PSaferPathNameIdentification = PSAFER_PATHNAME_IDENTIFICATION;

  _SAFER_HASH_IDENTIFICATION = record
    //
    // header.dwIdentificationType must be SaferIdentityTypeImageHash
    // header.cbStructSize must be sizeof(SAFER_HASH_IDENTIFICATION)
    //
    header: SAFER_IDENTIFICATION_HEADER;
    //
    // user-entered friendly name, initially from file's resources.
    //
    Description: array [0..SAFER_MAX_DESCRIPTION_SIZE - 1] of WCHAR;
    //
    // user-entered description.
    //
    FriendlyName: array [0..SAFER_MAX_FRIENDLYNAME_SIZE - 1] of WCHAR;
    //
    // amount of ImageHash actually used, in bytes (MD5 is 16 bytes).
    //
    HashSize: DWORD;
    //
    // computed hash data itself.
    //
    ImageHash: array [0..SAFER_MAX_HASH_SIZE - 1] of BYTE;
    //
    // algorithm in which the hash was computed (CALG_MD5, etc).
    //
    HashAlgorithm: ALG_ID;
    //
    // size of the original file in bytes.
    //
    ImageSize: LARGE_INTEGER;
    //
    // any combo of SAFER_POL_SAFERFLAGS_*
    //
    dwSaferFlags: DWORD;
  end;
  {$EXTERNALSYM _SAFER_HASH_IDENTIFICATION}
  SAFER_HASH_IDENTIFICATION = _SAFER_HASH_IDENTIFICATION;
  {$EXTERNALSYM SAFER_HASH_IDENTIFICATION}
  PSAFER_HASH_IDENTIFICATION = ^SAFER_HASH_IDENTIFICATION;
  {$EXTERNALSYM PSAFER_HASH_IDENTIFICATION}
  TSaferHashIdentification = SAFER_HASH_IDENTIFICATION;
  PSaferHashIdentification = PSAFER_HASH_IDENTIFICATION;

  _SAFER_URLZONE_IDENTIFICATION = record
    //
    // header.dwIdentificationType must be SaferIdentityTypeUrlZone
    // header.cbStructSize must be sizeof(SAFER_URLZONE_IDENTIFICATION)
    //
    header: SAFER_IDENTIFICATION_HEADER;
    //
    // any single URLZONE_* from urlmon.h
    //
    UrlZoneId: DWORD;
    //
    // any combo of SAFER_POLICY_*
    //
    dwSaferFlags: DWORD;
  end;
  {$EXTERNALSYM _SAFER_URLZONE_IDENTIFICATION}
  SAFER_URLZONE_IDENTIFICATION = _SAFER_URLZONE_IDENTIFICATION;
  {$EXTERNALSYM SAFER_URLZONE_IDENTIFICATION}
  PSAFER_URLZONE_IDENTIFICATION = ^SAFER_URLZONE_IDENTIFICATION;
  {$EXTERNALSYM PSAFER_URLZONE_IDENTIFICATION}
  TSaferUrlZoneIdentification = SAFER_URLZONE_IDENTIFICATION;
  PSaferUrlZoneIdentification = PSAFER_URLZONE_IDENTIFICATION;

// #include <poppack.h>

//
// Functions related to querying and setting the global policy
// controls to disable transparent enforcement, and perform level
// enumeration operations.
//

function SaferGetPolicyInformation(dwScopeId: DWORD; SaferPolicyInfoClass: SAFER_POLICY_INFO_CLASS;
  InfoBufferSize: DWORD; InfoBuffer: PVOID; var InfoBufferRetSize: DWORD; lpReserved: LPVOID): BOOL; stdcall;
{$EXTERNALSYM SaferGetPolicyInformation}

function SaferSetPolicyInformation(dwScopeId: DWORD; SaferPolicyInfoClass: SAFER_POLICY_INFO_CLASS;
  InfoBufferSize: DWORD; InfoBuffer: PVOID; lpReserved: LPVOID): BOOL; stdcall;
{$EXTERNALSYM SaferSetPolicyInformation}

//
// Functions to open or close a handle to a Safer Level.
//

function SaferCreateLevel(dwScopeId, dwLevelId, OpenFlags: DWORD; pLevelHandle: PSAFER_LEVEL_HANDLE; lpReserved: LPVOID): BOOL; stdcall;
{$EXTERNALSYM SaferCreateLevel}

function SaferCloseLevel(hLevelHandle: SAFER_LEVEL_HANDLE): BOOL; stdcall;
{$EXTERNALSYM SaferCloseLevel}

function SaferIdentifyLevel(dwNumProperties: DWORD; pCodeProperties: PSAFER_CODE_PROPERTIES;
  var pLevelHandle: SAFER_LEVEL_HANDLE; lpReserved: LPVOID): BOOL; stdcall;
{$EXTERNALSYM SaferIdentifyLevel}

function SaferComputeTokenFromLevel(LevelHandle: SAFER_LEVEL_HANDLE; InAccessToken: HANDLE; OutAccessToken: PHANDLE;
  dwFlags: DWORD; lpReserved: LPVOID): BOOL; stdcall;
{$EXTERNALSYM SaferComputeTokenFromLevel}

function SaferGetLevelInformation(LevelHandle: SAFER_LEVEL_HANDLE; dwInfoType: SAFER_OBJECT_INFO_CLASS;
  lpQueryBuffer: LPVOID; dwInBufferSize: DWORD; var lpdwOutBufferSize: DWORD): BOOL; stdcall;
{$EXTERNALSYM SaferGetLevelInformation}

function SaferSetLevelInformation(LevelHandle: SAFER_LEVEL_HANDLE; dwInfoType: SAFER_OBJECT_INFO_CLASS;
  lpQueryBuffer: LPVOID; dwInBufferSize: DWORD): BOOL; stdcall;
{$EXTERNALSYM SaferSetLevelInformation}

//
// This function performs logging of messages to the Application
// event log.  This is called by the hooks within CreateProcess,
// ShellExecute and cmd when a lower trust evaluation result occurs.
//

function SaferRecordEventLogEntry(hLevel: SAFER_LEVEL_HANDLE; szTargetPath: LPCWSTR; lpReserved: LPVOID): BOOL; stdcall;
{$EXTERNALSYM SaferRecordEventLogEntry}

function SaferiIsExecutableFileType(szFullPathname: LPCWSTR; bFromShellExecute: BOOL): BOOL; stdcall;
{$EXTERNALSYM SaferiIsExecutableFileType}

implementation

const
  advapi32 = 'advapi32.dll';

{$IFDEF DYNAMIC_LINK}
var
  _SaferGetPolicyInformation: Pointer;

function SaferGetPolicyInformation;
begin
  GetProcedureAddress(_SaferGetPolicyInformation, advapi32, 'SaferGetPolicyInformation');
  asm
    mov esp, ebp
    pop ebp
    jmp [_SaferGetPolicyInformation]
  end;
end;
{$ELSE}
function SaferGetPolicyInformation; external advapi32 name 'SaferGetPolicyInformation';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _SaferSetPolicyInformation: Pointer;

function SaferSetPolicyInformation;
begin
  GetProcedureAddress(_SaferSetPolicyInformation, advapi32, 'SaferSetPolicyInformation');
  asm
    mov esp, ebp
    pop ebp
    jmp [_SaferSetPolicyInformation]
  end;
end;
{$ELSE}
function SaferSetPolicyInformation; external advapi32 name 'SaferSetPolicyInformation';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _SaferCreateLevel: Pointer;

function SaferCreateLevel;
begin
  GetProcedureAddress(_SaferCreateLevel, advapi32, 'SaferCreateLevel');
  asm
    mov esp, ebp
    pop ebp
    jmp [_SaferCreateLevel]
  end;
end;
{$ELSE}
function SaferCreateLevel; external advapi32 name 'SaferCreateLevel';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _SaferCloseLevel: Pointer;

function SaferCloseLevel;
begin
  GetProcedureAddress(_SaferCloseLevel, advapi32, 'SaferCloseLevel');
  asm
    mov esp, ebp
    pop ebp
    jmp [_SaferCloseLevel]
  end;
end;
{$ELSE}
function SaferCloseLevel; external advapi32 name 'SaferCloseLevel';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _SaferIdentifyLevel: Pointer;

function SaferIdentifyLevel;
begin
  GetProcedureAddress(_SaferIdentifyLevel, advapi32, 'SaferIdentifyLevel');
  asm
    mov esp, ebp
    pop ebp
    jmp [_SaferIdentifyLevel]
  end;
end;
{$ELSE}
function SaferIdentifyLevel; external advapi32 name 'SaferIdentifyLevel';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _SaferComputeTokenFromLevel: Pointer;

function SaferComputeTokenFromLevel;
begin
  GetProcedureAddress(_SaferComputeTokenFromLevel, advapi32, 'SaferComputeTokenFromLevel');
  asm
    mov esp, ebp
    pop ebp
    jmp [_SaferComputeTokenFromLevel]
  end;
end;
{$ELSE}
function SaferComputeTokenFromLevel; external advapi32 name 'SaferComputeTokenFromLevel';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _SaferGetLevelInformation: Pointer;

function SaferGetLevelInformation;
begin
  GetProcedureAddress(_SaferGetLevelInformation, advapi32, 'SaferGetLevelInformation');
  asm
    mov esp, ebp
    pop ebp
    jmp [_SaferGetLevelInformation]
  end;
end;
{$ELSE}
function SaferGetLevelInformation; external advapi32 name 'SaferGetLevelInformation';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _SaferSetLevelInformation: Pointer;

function SaferSetLevelInformation;
begin
  GetProcedureAddress(_SaferSetLevelInformation, advapi32, 'SaferSetLevelInformation');
  asm
    mov esp, ebp
    pop ebp
    jmp [_SaferSetLevelInformation]
  end;
end;
{$ELSE}
function SaferSetLevelInformation; external advapi32 name 'SaferSetLevelInformation';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _SaferRecordEventLogEntry: Pointer;

function SaferRecordEventLogEntry;
begin
  GetProcedureAddress(_SaferRecordEventLogEntry, advapi32, 'SaferRecordEventLogEntry');
  asm
    mov esp, ebp
    pop ebp
    jmp [_SaferRecordEventLogEntry]
  end;
end;
{$ELSE}
function SaferRecordEventLogEntry; external advapi32 name 'SaferRecordEventLogEntry';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _SaferiIsExecutableFileType: Pointer;

function SaferiIsExecutableFileType;
begin
  GetProcedureAddress(_SaferiIsExecutableFileType, advapi32, 'SaferiIsExecutableFileType');
  asm
    mov esp, ebp
    pop ebp
    jmp [_SaferiIsExecutableFileType]
  end;
end;
{$ELSE}
function SaferiIsExecutableFileType; external advapi32 name 'SaferiIsExecutableFileType';
{$ENDIF DYNAMIC_LINK}

end.
