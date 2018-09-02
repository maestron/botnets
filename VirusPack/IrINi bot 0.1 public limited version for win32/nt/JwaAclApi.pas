{******************************************************************************}
{                                                       	               }
{ Access Control API interface Unit for Object Pascal                          }
{                                                       	               }
{ Portions created by Microsoft are Copyright (C) 1995-2001 Microsoft          }
{ Corporation. All Rights Reserved.                                            }
{ 								               }
{ The original file is: aclapi.h, released June 2000. The original Pascal      }
{ code is: AclApi.pas, released December 2000. The initial developer of the    }
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

unit JwaAclApi;

{$WEAKPACKAGEUNIT}

{$HPPEMIT ''}
{$HPPEMIT '#include "aclapi.h"'}
{$HPPEMIT ''}

{$I WINDEFINES.INC}

interface

uses
  JwaAccCtrl, JwaWinNT, JwaWinType;

//
// Progress Function:
// Caller of tree operation implements this Progress function, then
// passes its function pointer to tree operation.
// Tree operation invokes Progress function to provide progress and error
// information to the caller during the potentially long execution
// of the tree operation.  Tree operation provides the name of the object
// last processed and the error status of the operation on that object.
// Tree operation also passes the current InvokeSetting value.
// Caller may change the InvokeSetting value, for example, from "Always"
// to "Only On Error."
//

type
  FN_PROGRESS = procedure (
    pObjectName: LPWSTR;    // name of object just processed
    Status: DWORD;          // status of operation on object
    var pInvokeSetting: PPROG_INVOKE_SETTING; // Never, always,
    Args: PVOID;            // Caller specific data
    SecuritySet: BOOL       // Whether security was set
    ); stdcall;
  {$EXTERNALSYM FN_PROGRESS}
  TFnProgress = FN_PROGRESS;

function SetEntriesInAclA(cCountOfExplicitEntries: ULONG;
  pListOfExplicitEntries: PEXPLICIT_ACCESS_A; OldAcl: PACL;
  var NewAcl: PACL): DWORD; stdcall;
{$EXTERNALSYM SetEntriesInAclA}
function SetEntriesInAclW(cCountOfExplicitEntries: ULONG;
  pListOfExplicitEntries: PEXPLICIT_ACCESS_W; OldAcl: PACL;
  var NewAcl: PACL): DWORD; stdcall;
{$EXTERNALSYM SetEntriesInAclW}

{$IFDEF UNICODE}
function SetEntriesInAcl(cCountOfExplicitEntries: ULONG;
  pListOfExplicitEntries: PEXPLICIT_ACCESS_W; OldAcl: PACL;
  var NewAcl: PACL): DWORD; stdcall;
{$EXTERNALSYM SetEntriesInAcl}
{$ELSE}
function SetEntriesInAcl(cCountOfExplicitEntries: ULONG;
  pListOfExplicitEntries: PEXPLICIT_ACCESS_A; OldAcl: PACL;
  var NewAcl: PACL): DWORD; stdcall;
{$EXTERNALSYM SetEntriesInAcl}
{$ENDIF}

function GetExplicitEntriesFromAclA(pacl: PACL; var pcCountOfExplicitEntries: ULONG;
  var pListOfExplicitEntries: PEXPLICIT_ACCESS_A): DWORD; stdcall;
{$EXTERNALSYM GetExplicitEntriesFromAclA}
function GetExplicitEntriesFromAclW(pacl: PACL; var pcCountOfExplicitEntries: ULONG;
  var pListOfExplicitEntries: PEXPLICIT_ACCESS_W): DWORD; stdcall;
{$EXTERNALSYM GetExplicitEntriesFromAclW}

{$IFDEF UNICODE}
function GetExplicitEntriesFromAcl(pacl: PACL; var pcCountOfExplicitEntries: ULONG;
  var pListOfExplicitEntries: PEXPLICIT_ACCESS_W): DWORD; stdcall;
{$EXTERNALSYM GetExplicitEntriesFromAcl}
{$ELSE}
function GetExplicitEntriesFromAcl(pacl: PACL; var pcCountOfExplicitEntries: ULONG;
  var pListOfExplicitEntries: PEXPLICIT_ACCESS_A): DWORD; stdcall;
{$EXTERNALSYM GetExplicitEntriesFromAcl}
{$ENDIF}

function GetEffectiveRightsFromAclA(pacl: PACL; pTrustee: PTRUSTEE_A;
  var pAccessRights: ACCESS_MASK): DWORD; stdcall;
{$EXTERNALSYM GetEffectiveRightsFromAclA}
function GetEffectiveRightsFromAclW(pacl: PACL; pTrustee: PTRUSTEE_W;
  var pAccessRights: ACCESS_MASK): DWORD; stdcall;
{$EXTERNALSYM GetEffectiveRightsFromAclW}

{$IFDEF UNICODE}
function GetEffectiveRightsFromAcl(pacl: PACL; pTrustee: PTRUSTEE_W;
  var pAccessRights: ACCESS_MASK): DWORD; stdcall;
{$EXTERNALSYM GetEffectiveRightsFromAcl}
{$ELSE}
function GetEffectiveRightsFromAcl(pacl: PACL; pTrustee: PTRUSTEE_A;
  var pAccessRights: ACCESS_MASK): DWORD; stdcall;
{$EXTERNALSYM GetEffectiveRightsFromAcl}
{$ENDIF}

function GetAuditedPermissionsFromAclA(pacl: PACL; pTrustee: PTRUSTEE_A;
  var pSuccessfulAuditedRights, pFailedAuditRights: ACCESS_MASK): DWORD; stdcall;
{$EXTERNALSYM GetAuditedPermissionsFromAclA}
function GetAuditedPermissionsFromAclW(pacl: PACL; pTrustee: PTRUSTEE_W;
  var pSuccessfulAuditedRights, pFailedAuditRights: ACCESS_MASK): DWORD; stdcall;
{$EXTERNALSYM GetAuditedPermissionsFromAclW}

{$IFDEF UNICODE}
function GetAuditedPermissionsFromAcl(pacl: PACL; pTrustee: PTRUSTEE_W;
  var pSuccessfulAuditedRights, pFailedAuditRights: ACCESS_MASK): DWORD; stdcall;
{$EXTERNALSYM GetAuditedPermissionsFromAcl}
{$ELSE}
function GetAuditedPermissionsFromAcl(pacl: PACL; pTrustee: PTRUSTEE_A;
  var pSuccessfulAuditedRights, pFailedAuditRights: ACCESS_MASK): DWORD; stdcall;
{$EXTERNALSYM GetAuditedPermissionsFromAcl}
{$ENDIF}

function GetNamedSecurityInfoA(pObjectName: LPSTR; ObjectType: SE_OBJECT_TYPE;
  SecurityInfo: SECURITY_INFORMATION; ppsidOwner, ppsidGroup: PPSID; ppDacl,
  ppSacl: PPACL; var ppSecurityDescriptor: PSECURITY_DESCRIPTOR): DWORD; stdcall;
{$EXTERNALSYM GetNamedSecurityInfoA}
function GetNamedSecurityInfoW(pObjectName: LPWSTR; ObjectType: SE_OBJECT_TYPE;
  SecurityInfo: SECURITY_INFORMATION; ppsidOwner, ppsidGroup: PPSID; ppDacl,
  ppSacl: PPACL; var ppSecurityDescriptor: PSECURITY_DESCRIPTOR): DWORD; stdcall;
{$EXTERNALSYM GetNamedSecurityInfoW}

{$IFDEF UNICODE}
function GetNamedSecurityInfo(pObjectName: LPWSTR; ObjectType: SE_OBJECT_TYPE;
  SecurityInfo: SECURITY_INFORMATION; ppsidOwner, ppsidGroup: PPSID; ppDacl,
  ppSacl: PPACL; var ppSecurityDescriptor: PSECURITY_DESCRIPTOR): DWORD; stdcall;
{$EXTERNALSYM GetNamedSecurityInfo}
{$ELSE}
function GetNamedSecurityInfo(pObjectName: LPSTR; ObjectType: SE_OBJECT_TYPE;
  SecurityInfo: SECURITY_INFORMATION; ppsidOwner, ppsidGroup: PPSID; ppDacl,
  ppSacl: PPACL; var ppSecurityDescriptor: PSECURITY_DESCRIPTOR): DWORD; stdcall;
{$EXTERNALSYM GetNamedSecurityInfo}
{$ENDIF}

function GetSecurityInfo(handle: HANDLE; ObjectType: SE_OBJECT_TYPE;
  SecurityInfo: SECURITY_INFORMATION; ppsidOwner: PPSID; ppsidGroup: PPSID;
  ppDacl, ppSacl: PPACL; var ppSecurityDescriptor: PSECURITY_DESCRIPTOR): DWORD; stdcall;
{$EXTERNALSYM GetSecurityInfo}

function SetNamedSecurityInfoA(pObjectName: LPSTR; ObjectType: SE_OBJECT_TYPE;
  SecurityInfo: SECURITY_INFORMATION; psidOwner, psidGroup: PSID;
  pDacl, pSacl: PACL): DWORD; stdcall;
{$EXTERNALSYM SetNamedSecurityInfoA}
function SetNamedSecurityInfoW(pObjectName: LPWSTR; ObjectType: SE_OBJECT_TYPE;
  SecurityInfo: SECURITY_INFORMATION; psidOwner, psidGroup: PSID;
  pDacl, pSacl: PACL): DWORD; stdcall;
{$EXTERNALSYM SetNamedSecurityInfoW}

{$IFDEF UNICODE}
function SetNamedSecurityInfo(pObjectName: LPWSTR; ObjectType: SE_OBJECT_TYPE;
  SecurityInfo: SECURITY_INFORMATION; psidOwner, psidGroup: PSID;
  pDacl, pSacl: PACL): DWORD; stdcall;
{$EXTERNALSYM SetNamedSecurityInfo}
{$ELSE}
function SetNamedSecurityInfo(pObjectName: LPSTR; ObjectType: SE_OBJECT_TYPE;
  SecurityInfo: SECURITY_INFORMATION; psidOwner, psidGroup: PSID;
  pDacl, pSacl: PACL): DWORD; stdcall;
{$EXTERNALSYM SetNamedSecurityInfo}
{$ENDIF}

function SetSecurityInfo(handle: HANDLE; ObjectType: SE_OBJECT_TYPE;
  SecurityInfo: SECURITY_INFORMATION; psidOwner, psidGroup: PSID;
  pDacl, pSacl: PACL): DWORD; stdcall;
{$EXTERNALSYM SetSecurityInfo}

function GetInheritanceSourceA(pObjectName: LPSTR; ObjectType: SE_OBJECT_TYPE;
  SecurityInfo: SECURITY_INFORMATION; Container: BOOL; pObjectClassGuids: LPGUID;
  GuidCount: DWORD; pAcl: PACL; pfnArray: PFN_OBJECT_MGR_FUNCTS;
  pGenericMapping: PGENERIC_MAPPING; pInheritArray:  PINHERITED_FROMA): DWORD; stdcall;
{$EXTERNALSYM GetInheritanceSourceA}

function GetInheritanceSourceW(pObjectName: LPWSTR; ObjectType: SE_OBJECT_TYPE;
  SecurityInfo: SECURITY_INFORMATION; Container: BOOL; pObjectClassGuids: LPGUID;
  GuidCount: DWORD; pAcl: PACL; pfnArray: PFN_OBJECT_MGR_FUNCTS;
  pGenericMapping: PGENERIC_MAPPING; pInheritArray:  PINHERITED_FROMW): DWORD; stdcall;
{$EXTERNALSYM GetInheritanceSourceW}

{$IFDEF UNICODE}
function GetInheritanceSource(pObjectName: LPWSTR; ObjectType: SE_OBJECT_TYPE;
  SecurityInfo: SECURITY_INFORMATION; Container: BOOL; pObjectClassGuids: LPGUID;
  GuidCount: DWORD; pAcl: PACL; pfnArray: PFN_OBJECT_MGR_FUNCTS;
  pGenericMapping: PGENERIC_MAPPING; pInheritArray:  PINHERITED_FROMW): DWORD; stdcall;
{$EXTERNALSYM GetInheritanceSource}
{$ELSE}
function GetInheritanceSource(pObjectName: LPSTR; ObjectType: SE_OBJECT_TYPE;
  SecurityInfo: SECURITY_INFORMATION; Container: BOOL; pObjectClassGuids: LPGUID;
  GuidCount: DWORD; pAcl: PACL; pfnArray: PFN_OBJECT_MGR_FUNCTS;
  pGenericMapping: PGENERIC_MAPPING; pInheritArray:  PINHERITED_FROMA): DWORD; stdcall;
{$EXTERNALSYM GetInheritanceSource}
{$ENDIF}

function FreeInheritedFromArray(pInheritArray: PINHERITED_FROMW; AceCnt: USHORT;
  pfnArray: PFN_OBJECT_MGR_FUNCTS): DWORD; stdcall;
{$EXTERNALSYM FreeInheritedFromArray}

function TreeResetNamedSecurityInfoA(pObjectName: LPSTR; ObjectType: SE_OBJECT_TYPE;
  SecurityInfo: SECURITY_INFORMATION; pOwner, pGroup: PSID; pDacl, pSacl: PACL;
  KeepExplicit: BOOL; fnProgress: FN_PROGRESS; ProgressInvokeSetting: PROG_INVOKE_SETTING;
  Args: PVOID): DWORD; stdcall;
{$EXTERNALSYM TreeResetNamedSecurityInfoA}

function TreeResetNamedSecurityInfoW(pObjectName: LPWSTR; ObjectType: SE_OBJECT_TYPE;
  SecurityInfo: SECURITY_INFORMATION; pOwner, pGroup: PSID; pDacl, pSacl: PACL;
  KeepExplicit: BOOL; fnProgress: FN_PROGRESS; ProgressInvokeSetting: PROG_INVOKE_SETTING;
  Args: PVOID): DWORD; stdcall;
{$EXTERNALSYM TreeResetNamedSecurityInfoW}

{$IFDEF UNICODE}
function TreeResetNamedSecurityInfo(pObjectName: LPWSTR; ObjectType: SE_OBJECT_TYPE;
  SecurityInfo: SECURITY_INFORMATION; pOwner, pGroup: PSID; pDacl, pSacl: PACL;
  KeepExplicit: BOOL; fnProgress: FN_PROGRESS; ProgressInvokeSetting: PROG_INVOKE_SETTING;
  Args: PVOID): DWORD; stdcall;
{$EXTERNALSYM TreeResetNamedSecurityInfo}
{$ELSE}
function TreeResetNamedSecurityInfo(pObjectName: LPSTR; ObjectType: SE_OBJECT_TYPE;
  SecurityInfo: SECURITY_INFORMATION; pOwner, pGroup: PSID; pDacl, pSacl: PACL;
  KeepExplicit: BOOL; fnProgress: FN_PROGRESS; ProgressInvokeSetting: PROG_INVOKE_SETTING;
  Args: PVOID): DWORD; stdcall;
{$EXTERNALSYM TreeResetNamedSecurityInfo}
{$ENDIF}

//----------------------------------------------------------------------------
// The following API are provided for trusted servers to use to
// implement access control on their own objects.
//----------------------------------------------------------------------------

function BuildSecurityDescriptorA(pOwner: PTRUSTEE_A; pGroup: PTRUSTEE_A;
  cCountOfAccessEntries: ULONG; pListOfAccessEntries: PEXPLICIT_ACCESS_A;
  cCountOfAuditEntries: ULONG; pListOfAuditEntries: PEXPLICIT_ACCESS_A;
  pOldSD: PSECURITY_DESCRIPTOR; var pSizeNewSD: ULONG;
  var pNewSD: PSECURITY_DESCRIPTOR): DWORD; stdcall;
{$EXTERNALSYM BuildSecurityDescriptorA}
function BuildSecurityDescriptorW(pOwner: PTRUSTEE_W; pGroup: PTRUSTEE_W;
  cCountOfAccessEntries: ULONG; pListOfAccessEntries: PEXPLICIT_ACCESS_W;
  cCountOfAuditEntries: ULONG; pListOfAuditEntries: PEXPLICIT_ACCESS_W;
  pOldSD: PSECURITY_DESCRIPTOR; var pSizeNewSD: ULONG;
  var pNewSD: PSECURITY_DESCRIPTOR): DWORD; stdcall;
{$EXTERNALSYM BuildSecurityDescriptorW}

{$IFDEF UNICODE}
function BuildSecurityDescriptor(pOwner: PTRUSTEE_W; pGroup: PTRUSTEE_W;
  cCountOfAccessEntries: ULONG; pListOfAccessEntries: PEXPLICIT_ACCESS_W;
  cCountOfAuditEntries: ULONG; pListOfAuditEntries: PEXPLICIT_ACCESS_W;
  pOldSD: PSECURITY_DESCRIPTOR; var pSizeNewSD: ULONG;
  var pNewSD: PSECURITY_DESCRIPTOR): DWORD; stdcall;
{$EXTERNALSYM BuildSecurityDescriptor}
{$ELSE}
function BuildSecurityDescriptor(pOwner: PTRUSTEE_A; pGroup: PTRUSTEE_A;
  cCountOfAccessEntries: ULONG; pListOfAccessEntries: PEXPLICIT_ACCESS_A;
  cCountOfAuditEntries: ULONG; pListOfAuditEntries: PEXPLICIT_ACCESS_A;
  pOldSD: PSECURITY_DESCRIPTOR; var pSizeNewSD: ULONG;
  var pNewSD: PSECURITY_DESCRIPTOR): DWORD; stdcall;
{$EXTERNALSYM BuildSecurityDescriptor}
{$ENDIF}

function LookupSecurityDescriptorPartsA(pOwner, pGroup: PPTRUSTEE_A;
  cCountOfAccessEntries: PULONG; pListOfAccessEntries: PEXPLICIT_ACCESS_A;
  cCountOfAuditEntries: PULONG; pListOfAuditEntries: PEXPLICIT_ACCESS_A;
  var pSD: SECURITY_DESCRIPTOR): DWORD; stdcall;
{$EXTERNALSYM LookupSecurityDescriptorPartsA}
function LookupSecurityDescriptorPartsW(pOwner, pGroup: PPTRUSTEE_W;
  cCountOfAccessEntries: PULONG; pListOfAccessEntries: PEXPLICIT_ACCESS_W;
  cCountOfAuditEntries: PULONG; pListOfAuditEntries: PEXPLICIT_ACCESS_W;
  var pSD: SECURITY_DESCRIPTOR): DWORD; stdcall;
{$EXTERNALSYM LookupSecurityDescriptorPartsW}

{$IFDEF UNICODE}
function LookupSecurityDescriptorParts(pOwner, pGroup: PPTRUSTEE_W;
  cCountOfAccessEntries: PULONG; pListOfAccessEntries: PEXPLICIT_ACCESS_W;
  cCountOfAuditEntries: PULONG; pListOfAuditEntries: PEXPLICIT_ACCESS_W;
  var pSD: SECURITY_DESCRIPTOR): DWORD; stdcall;
{$EXTERNALSYM LookupSecurityDescriptorParts}
{$ELSE}
function LookupSecurityDescriptorParts(pOwner, pGroup: PPTRUSTEE_A;
  cCountOfAccessEntries: PULONG; pListOfAccessEntries: PEXPLICIT_ACCESS_A;
  cCountOfAuditEntries: PULONG; pListOfAuditEntries: PEXPLICIT_ACCESS_A;
  var pSD: SECURITY_DESCRIPTOR): DWORD; stdcall;
{$EXTERNALSYM LookupSecurityDescriptorParts}
{$ENDIF}

//----------------------------------------------------------------------------
// The following helper API are provided for building
// access control structures.
//----------------------------------------------------------------------------

procedure BuildExplicitAccessWithNameA(pExplicitAccess: PEXPLICIT_ACCESS_A;
  pTrusteeName: LPSTR; AccessPermissions: DWORD; AccessMode: ACCESS_MODE;
  Inheritance: DWORD); stdcall;
{$EXTERNALSYM BuildExplicitAccessWithNameA}
procedure BuildExplicitAccessWithNameW(pExplicitAccess: PEXPLICIT_ACCESS_W;
  pTrusteeName: LPWSTR; AccessPermissions: DWORD; AccessMode: ACCESS_MODE;
  Inheritance: DWORD); stdcall;
{$EXTERNALSYM BuildExplicitAccessWithNameW}

{$IFDEF UNICODE}
procedure BuildExplicitAccessWithName(pExplicitAccess: PEXPLICIT_ACCESS_W;
  pTrusteeName: LPWSTR; AccessPermissions: DWORD; AccessMode: ACCESS_MODE;
  Inheritance: DWORD); stdcall;
{$EXTERNALSYM BuildExplicitAccessWithName}
{$ELSE}
procedure BuildExplicitAccessWithName(pExplicitAccess: PEXPLICIT_ACCESS_A;
  pTrusteeName: LPSTR; AccessPermissions: DWORD; AccessMode: ACCESS_MODE;
  Inheritance: DWORD); stdcall;
{$EXTERNALSYM BuildExplicitAccessWithName}
{$ENDIF}

procedure BuildImpersonateExplicitAccessWithNameA(pExplicitAccess: PEXPLICIT_ACCESS_A;
  pTrusteeName: LPSTR; pTrustee: PTRUSTEE_A; AccessPermissions: DWORD;
  AccessMode: ACCESS_MODE; Inheritance: DWORD); stdcall;
{$EXTERNALSYM BuildImpersonateExplicitAccessWithNameA}
procedure BuildImpersonateExplicitAccessWithNameW(pExplicitAccess: PEXPLICIT_ACCESS_W;
  pTrusteeName: LPWSTR; pTrustee: PTRUSTEE_W; AccessPermissions: DWORD;
  AccessMode: ACCESS_MODE; Inheritance: DWORD); stdcall;
{$EXTERNALSYM BuildImpersonateExplicitAccessWithNameW}

{$IFDEF UNICODE}
procedure BuildImpersonateExplicitAccessWithName(pExplicitAccess: PEXPLICIT_ACCESS_W;
  pTrusteeName: LPWSTR; pTrustee: PTRUSTEE_W; AccessPermissions: DWORD;
  AccessMode: ACCESS_MODE; Inheritance: DWORD); stdcall;
{$EXTERNALSYM BuildImpersonateExplicitAccessWithName}
{$ELSE}
procedure BuildImpersonateExplicitAccessWithName(pExplicitAccess: PEXPLICIT_ACCESS_A;
  pTrusteeName: LPSTR; pTrustee: PTRUSTEE_A; AccessPermissions: DWORD;
  AccessMode: ACCESS_MODE; Inheritance: DWORD); stdcall;
{$EXTERNALSYM BuildImpersonateExplicitAccessWithName}
{$ENDIF}

procedure BuildTrusteeWithNameA(pTrustee: PTRUSTEE_A; pName: LPSTR); stdcall;
{$EXTERNALSYM BuildTrusteeWithNameA}
procedure BuildTrusteeWithNameW(pTrustee: PTRUSTEE_W; pName: LPWSTR); stdcall;
{$EXTERNALSYM BuildTrusteeWithNameW}

{$IFDEF UNICODE}
procedure BuildTrusteeWithName(pTrustee: PTRUSTEE_W; pName: LPWSTR); stdcall;
{$EXTERNALSYM BuildTrusteeWithName}
{$ELSE}
procedure BuildTrusteeWithName(pTrustee: PTRUSTEE_A; pName: LPSTR); stdcall;
{$EXTERNALSYM BuildTrusteeWithName}
{$ENDIF}

procedure BuildImpersonateTrusteeA(pTrustee: PTRUSTEE_A;
  pImpersonateTrustee: PTRUSTEE_A); stdcall;
{$EXTERNALSYM BuildImpersonateTrusteeA}
procedure BuildImpersonateTrusteeW(pTrustee: PTRUSTEE_W;
  pImpersonateTrustee: PTRUSTEE_W); stdcall;
{$EXTERNALSYM BuildImpersonateTrusteeW}

{$IFDEF UNICODE}
procedure BuildImpersonateTrustee(pTrustee: PTRUSTEE_W;
  pImpersonateTrustee: PTRUSTEE_W); stdcall;
{$EXTERNALSYM BuildImpersonateTrustee}
{$ELSE}
procedure BuildImpersonateTrustee(pTrustee: PTRUSTEE_A;
  pImpersonateTrustee: PTRUSTEE_A); stdcall;
{$EXTERNALSYM BuildImpersonateTrustee}
{$ENDIF}

procedure BuildTrusteeWithSidA(pTrustee: PTRUSTEE_A; pSid: PSID); stdcall;
{$EXTERNALSYM BuildTrusteeWithSidA}
procedure BuildTrusteeWithSidW(pTrustee: PTRUSTEE_W; pSid: PSID); stdcall;
{$EXTERNALSYM BuildTrusteeWithSidW}

{$IFDEF UNICODE}
procedure BuildTrusteeWithSid(pTrustee: PTRUSTEE_W; pSid: PSID); stdcall;
{$EXTERNALSYM BuildTrusteeWithSid}
{$ELSE}
procedure BuildTrusteeWithSid(pTrustee: PTRUSTEE_A; pSid: PSID); stdcall;
{$EXTERNALSYM BuildTrusteeWithSid}
{$ENDIF}

procedure BuildTrusteeWithObjectsAndSidA(pTrustee: PTRUSTEE_A;
  pObjSid: POBJECTS_AND_SID; pObjectGuid: PGUID; pInheritedObjectGuid: PGUID;
  pSid: PSID); stdcall;
{$EXTERNALSYM BuildTrusteeWithObjectsAndSidA}
procedure BuildTrusteeWithObjectsAndSidW(pTrustee: PTRUSTEE_W;
  pObjSid: POBJECTS_AND_SID; pObjectGuid: PGUID; pInheritedObjectGuid: PGUID;
  pSid: PSID); stdcall;
{$EXTERNALSYM BuildTrusteeWithObjectsAndSidW}

{$IFDEF UNICODE}
procedure BuildTrusteeWithObjectsAndSid(pTrustee: PTRUSTEE_W;
  pObjSid: POBJECTS_AND_SID; pObjectGuid: PGUID; pInheritedObjectGuid: PGUID;
  pSid: PSID); stdcall;
{$EXTERNALSYM BuildTrusteeWithObjectsAndSid}
{$ELSE}
procedure BuildTrusteeWithObjectsAndSid(pTrustee: PTRUSTEE_A;
  pObjSid: POBJECTS_AND_SID; pObjectGuid: PGUID; pInheritedObjectGuid: PGUID;
  pSid: PSID); stdcall;
{$EXTERNALSYM BuildTrusteeWithObjectsAndSid}
{$ENDIF}

procedure BuildTrusteeWithObjectsAndNameA(pTrustee: PTRUSTEE_A;
  pObjName: POBJECTS_AND_NAME_A; ObjectType: SE_OBJECT_TYPE;
  ObjectTypeName, InheritedObjectTypeName, Name: LPSTR); stdcall;
{$EXTERNALSYM BuildTrusteeWithObjectsAndNameA}
procedure BuildTrusteeWithObjectsAndNameW(pTrustee: PTRUSTEE_W;
  pObjName: POBJECTS_AND_NAME_W; ObjectType: SE_OBJECT_TYPE;
  ObjectTypeName, InheritedObjectTypeName, Name: LPWSTR); stdcall;
{$EXTERNALSYM BuildTrusteeWithObjectsAndNameW}

{$IFDEF UNICODE}
procedure BuildTrusteeWithObjectsAndName(pTrustee: PTRUSTEE_W;
  pObjName: POBJECTS_AND_NAME_W; ObjectType: SE_OBJECT_TYPE;
  ObjectTypeName, InheritedObjectTypeName, Name: LPWSTR); stdcall;
{$EXTERNALSYM BuildTrusteeWithObjectsAndName}
{$ELSE}
procedure BuildTrusteeWithObjectsAndName(pTrustee: PTRUSTEE_A;
  pObjName: POBJECTS_AND_NAME_A; ObjectType: SE_OBJECT_TYPE;
  ObjectTypeName, InheritedObjectTypeName, Name: LPSTR); stdcall;
{$EXTERNALSYM BuildTrusteeWithObjectsAndName}
{$ENDIF}

function GetTrusteeNameA(pTrustee: PTRUSTEE_A): LPSTR; stdcall;
{$EXTERNALSYM GetTrusteeNameA}
function GetTrusteeNameW(pTrustee: PTRUSTEE_W): LPWSTR; stdcall;
{$EXTERNALSYM GetTrusteeNameW}

{$IFDEF UNICODE}
function GetTrusteeName(pTrustee: PTRUSTEE_W): LPWSTR; stdcall;
{$EXTERNALSYM GetTrusteeName}
{$ELSE}
function GetTrusteeName(pTrustee: PTRUSTEE_A): LPSTR; stdcall;
{$EXTERNALSYM GetTrusteeName}
{$ENDIF}

function GetTrusteeTypeA(pTrustee: PTRUSTEE_A): TRUSTEE_TYPE; stdcall;
{$EXTERNALSYM GetTrusteeTypeA}
function GetTrusteeTypeW(pTrustee: PTRUSTEE_W): TRUSTEE_TYPE; stdcall;
{$EXTERNALSYM GetTrusteeTypeW}

{$IFDEF UNICODE}
function GetTrusteeType(pTrustee: PTRUSTEE_W): TRUSTEE_TYPE; stdcall;
{$EXTERNALSYM GetTrusteeType}
{$ELSE}
function GetTrusteeType(pTrustee: PTRUSTEE_A): TRUSTEE_TYPE; stdcall;
{$EXTERNALSYM GetTrusteeType}
{$ENDIF}

function GetTrusteeFormA(pTrustee: PTRUSTEE_A): TRUSTEE_FORM; stdcall;
{$EXTERNALSYM GetTrusteeFormA}
function GetTrusteeFormW(pTrustee: PTRUSTEE_W): TRUSTEE_FORM; stdcall;
{$EXTERNALSYM GetTrusteeFormW}

{$IFDEF UNICODE}
function GetTrusteeForm(pTrustee: PTRUSTEE_W): TRUSTEE_FORM; stdcall;
{$EXTERNALSYM GetTrusteeForm}
{$ELSE}
function GetTrusteeForm(pTrustee: PTRUSTEE_A): TRUSTEE_FORM; stdcall;
{$EXTERNALSYM GetTrusteeForm}
{$ENDIF}

function GetMultipleTrusteeOperationA(pTrustee: PTRUSTEE_A): MULTIPLE_TRUSTEE_OPERATION; stdcall;
{$EXTERNALSYM GetMultipleTrusteeOperationA}
function GetMultipleTrusteeOperationW(pTrustee: PTRUSTEE_W): MULTIPLE_TRUSTEE_OPERATION; stdcall;
{$EXTERNALSYM GetMultipleTrusteeOperationW}

{$IFDEF UNICODE}
function GetMultipleTrusteeOperation(pTrustee: PTRUSTEE_W): MULTIPLE_TRUSTEE_OPERATION; stdcall;
{$EXTERNALSYM GetMultipleTrusteeOperation}
{$ELSE}
function GetMultipleTrusteeOperation(pTrustee: PTRUSTEE_A): MULTIPLE_TRUSTEE_OPERATION; stdcall;
{$EXTERNALSYM GetMultipleTrusteeOperation}
{$ENDIF}

function GetMultipleTrusteeA(pTrustee: PTRUSTEE_A): PTRUSTEE_A; stdcall;
{$EXTERNALSYM GetMultipleTrusteeA}
function GetMultipleTrusteeW(pTrustee: PTRUSTEE_W): PTRUSTEE_W; stdcall;
{$EXTERNALSYM GetMultipleTrusteeW}

{$IFDEF UNICODE}
function GetMultipleTrustee(pTrustee: PTRUSTEE_W): PTRUSTEE_W; stdcall;
{$EXTERNALSYM GetMultipleTrustee}
{$ELSE}
function GetMultipleTrustee(pTrustee: PTRUSTEE_A): PTRUSTEE_A; stdcall;
{$EXTERNALSYM GetMultipleTrustee}
{$ENDIF}

implementation

const
  aclapilib = 'advapi32.dll';


{$IFDEF DYNAMIC_LINK}
var
  _SetEntriesInAclA: Pointer;

function SetEntriesInAclA;
begin
  GetProcedureAddress(_SetEntriesInAclA, aclapilib, 'SetEntriesInAclA');
  asm
    mov esp, ebp
    pop ebp
    jmp [_SetEntriesInAclA]
  end;
end;
{$ELSE}
function SetEntriesInAclA; external aclapilib name 'SetEntriesInAclA';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _SetEntriesInAclW: Pointer;

function SetEntriesInAclW;
begin
  GetProcedureAddress(_SetEntriesInAclW, aclapilib, 'SetEntriesInAclW');
  asm
    mov esp, ebp
    pop ebp
    jmp [_SetEntriesInAclW]
  end;
end;
{$ELSE}
function SetEntriesInAclW; external aclapilib name 'SetEntriesInAclW';
{$ENDIF DYNAMIC_LINK}
{$IFDEF UNICODE}

{$IFDEF DYNAMIC_LINK}
var
  _SetEntriesInAcl: Pointer;

function SetEntriesInAcl;
begin
  GetProcedureAddress(_SetEntriesInAcl, aclapilib, 'SetEntriesInAclW');
  asm
    mov esp, ebp
    pop ebp
    jmp [_SetEntriesInAcl]
  end;
end;
{$ELSE}
function SetEntriesInAcl; external aclapilib name 'SetEntriesInAclW';
{$ENDIF DYNAMIC_LINK}
{$ELSE}

{$IFDEF DYNAMIC_LINK}
var
  _SetEntriesInAcl: Pointer;

function SetEntriesInAcl;
begin
  GetProcedureAddress(_SetEntriesInAcl, aclapilib, 'SetEntriesInAclA');
  asm
    mov esp, ebp
    pop ebp
    jmp [_SetEntriesInAcl]
  end;
end;
{$ELSE}
function SetEntriesInAcl; external aclapilib name 'SetEntriesInAclA';
{$ENDIF DYNAMIC_LINK}
{$ENDIF}

{$IFDEF DYNAMIC_LINK}
var
  _GetExplicitEntriesFromAclA: Pointer;

function GetExplicitEntriesFromAclA;
begin
  GetProcedureAddress(_GetExplicitEntriesFromAclA, aclapilib, 'GetExplicitEntriesFromAclA');
  asm
    mov esp, ebp
    pop ebp
    jmp [_GetExplicitEntriesFromAclA]
  end;
end;
{$ELSE}
function GetExplicitEntriesFromAclA; external aclapilib name 'GetExplicitEntriesFromAclA';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _GetExplicitEntriesFromAclW: Pointer;

function GetExplicitEntriesFromAclW;
begin
  GetProcedureAddress(_GetExplicitEntriesFromAclW, aclapilib, 'GetExplicitEntriesFromAclW');
  asm
    mov esp, ebp
    pop ebp
    jmp [_GetExplicitEntriesFromAclW]
  end;
end;
{$ELSE}
function GetExplicitEntriesFromAclW; external aclapilib name 'GetExplicitEntriesFromAclW';
{$ENDIF DYNAMIC_LINK}
{$IFDEF UNICODE}

{$IFDEF DYNAMIC_LINK}
var
  _GetExplicitEntriesFromAcl: Pointer;

function GetExplicitEntriesFromAcl;
begin
  GetProcedureAddress(_GetExplicitEntriesFromAcl, aclapilib, 'GetExplicitEntriesFromAclW');
  asm
    mov esp, ebp
    pop ebp
    jmp [_GetExplicitEntriesFromAcl]
  end;
end;
{$ELSE}
function GetExplicitEntriesFromAcl; external aclapilib name 'GetExplicitEntriesFromAclW';
{$ENDIF DYNAMIC_LINK}
{$ELSE}

{$IFDEF DYNAMIC_LINK}
var
  _GetExplicitEntriesFromAcl: Pointer;

function GetExplicitEntriesFromAcl;
begin
  GetProcedureAddress(_GetExplicitEntriesFromAcl, aclapilib, 'GetExplicitEntriesFromAclA');
  asm
    mov esp, ebp
    pop ebp
    jmp [_GetExplicitEntriesFromAcl]
  end;
end;
{$ELSE}
function GetExplicitEntriesFromAcl; external aclapilib name 'GetExplicitEntriesFromAclA';
{$ENDIF DYNAMIC_LINK}
{$ENDIF}

{$IFDEF DYNAMIC_LINK}
var
  _GetEffectiveRightsFromAclA: Pointer;

function GetEffectiveRightsFromAclA;
begin
  GetProcedureAddress(_GetEffectiveRightsFromAclA, aclapilib, 'GetEffectiveRightsFromAclA');
  asm
    mov esp, ebp
    pop ebp
    jmp [_GetEffectiveRightsFromAclA]
  end;
end;
{$ELSE}
function GetEffectiveRightsFromAclA; external aclapilib name 'GetEffectiveRightsFromAclA';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _GetEffectiveRightsFromAclW: Pointer;

function GetEffectiveRightsFromAclW;
begin
  GetProcedureAddress(_GetEffectiveRightsFromAclW, aclapilib, 'GetEffectiveRightsFromAclW');
  asm
    mov esp, ebp
    pop ebp
    jmp [_GetEffectiveRightsFromAclW]
  end;
end;
{$ELSE}
function GetEffectiveRightsFromAclW; external aclapilib name 'GetEffectiveRightsFromAclW';
{$ENDIF DYNAMIC_LINK}
{$IFDEF UNICODE}

{$IFDEF DYNAMIC_LINK}
var
  _GetEffectiveRightsFromAcl: Pointer;

function GetEffectiveRightsFromAcl;
begin
  GetProcedureAddress(_GetEffectiveRightsFromAcl, aclapilib, 'GetEffectiveRightsFromAclW');
  asm
    mov esp, ebp
    pop ebp
    jmp [_GetEffectiveRightsFromAcl]
  end;
end;
{$ELSE}
function GetEffectiveRightsFromAcl; external aclapilib name 'GetEffectiveRightsFromAclW';
{$ENDIF DYNAMIC_LINK}
{$ELSE}

{$IFDEF DYNAMIC_LINK}
var
  _GetEffectiveRightsFromAcl: Pointer;

function GetEffectiveRightsFromAcl;
begin
  GetProcedureAddress(_GetEffectiveRightsFromAcl, aclapilib, 'GetEffectiveRightsFromAclA');
  asm
    mov esp, ebp
    pop ebp
    jmp [_GetEffectiveRightsFromAcl]
  end;
end;
{$ELSE}
function GetEffectiveRightsFromAcl; external aclapilib name 'GetEffectiveRightsFromAclA';
{$ENDIF DYNAMIC_LINK}
{$ENDIF}

{$IFDEF DYNAMIC_LINK}
var
  _GetAuditedPermissionsFromAclA: Pointer;

function GetAuditedPermissionsFromAclA;
begin
  GetProcedureAddress(_GetAuditedPermissionsFromAclA, aclapilib, 'GetAuditedPermissionsFromAclA');
  asm
    mov esp, ebp
    pop ebp
    jmp [_GetAuditedPermissionsFromAclA]
  end;
end;
{$ELSE}
function GetAuditedPermissionsFromAclA; external aclapilib name 'GetAuditedPermissionsFromAclA';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _GetAuditedPermissionsFromAclW: Pointer;

function GetAuditedPermissionsFromAclW;
begin
  GetProcedureAddress(_GetAuditedPermissionsFromAclW, aclapilib, 'GetAuditedPermissionsFromAclW');
  asm
    mov esp, ebp
    pop ebp
    jmp [_GetAuditedPermissionsFromAclW]
  end;
end;
{$ELSE}
function GetAuditedPermissionsFromAclW; external aclapilib name 'GetAuditedPermissionsFromAclW';
{$ENDIF DYNAMIC_LINK}
{$IFDEF UNICODE}

{$IFDEF DYNAMIC_LINK}
var
  _GetAuditedPermissionsFromAcl: Pointer;

function GetAuditedPermissionsFromAcl;
begin
  GetProcedureAddress(_GetAuditedPermissionsFromAcl, aclapilib, 'GetAuditedPermissionsFromAclW');
  asm
    mov esp, ebp
    pop ebp
    jmp [_GetAuditedPermissionsFromAcl]
  end;
end;
{$ELSE}
function GetAuditedPermissionsFromAcl; external aclapilib name 'GetAuditedPermissionsFromAclW';
{$ENDIF DYNAMIC_LINK}
{$ELSE}

{$IFDEF DYNAMIC_LINK}
var
  _GetAuditedPermissionsFromAcl: Pointer;

function GetAuditedPermissionsFromAcl;
begin
  GetProcedureAddress(_GetAuditedPermissionsFromAcl, aclapilib, 'GetAuditedPermissionsFromAclA');
  asm
    mov esp, ebp
    pop ebp
    jmp [_GetAuditedPermissionsFromAcl]
  end;
end;
{$ELSE}
function GetAuditedPermissionsFromAcl; external aclapilib name 'GetAuditedPermissionsFromAclA';
{$ENDIF DYNAMIC_LINK}
{$ENDIF}

{$IFDEF DYNAMIC_LINK}
var
  _GetNamedSecurityInfoA: Pointer;

function GetNamedSecurityInfoA;
begin
  GetProcedureAddress(_GetNamedSecurityInfoA, aclapilib, 'GetNamedSecurityInfoA');
  asm
    mov esp, ebp
    pop ebp
    jmp [_GetNamedSecurityInfoA]
  end;
end;
{$ELSE}
function GetNamedSecurityInfoA; external aclapilib name 'GetNamedSecurityInfoA';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _GetNamedSecurityInfoW: Pointer;

function GetNamedSecurityInfoW;
begin
  GetProcedureAddress(_GetNamedSecurityInfoW, aclapilib, 'GetNamedSecurityInfoW');
  asm
    mov esp, ebp
    pop ebp
    jmp [_GetNamedSecurityInfoW]
  end;
end;
{$ELSE}
function GetNamedSecurityInfoW; external aclapilib name 'GetNamedSecurityInfoW';
{$ENDIF DYNAMIC_LINK}
{$IFDEF UNICODE}

{$IFDEF DYNAMIC_LINK}
var
  _GetNamedSecurityInfo: Pointer;

function GetNamedSecurityInfo;
begin
  GetProcedureAddress(_GetNamedSecurityInfo, aclapilib, 'GetNamedSecurityInfoW');
  asm
    mov esp, ebp
    pop ebp
    jmp [_GetNamedSecurityInfo]
  end;
end;
{$ELSE}
function GetNamedSecurityInfo; external aclapilib name 'GetNamedSecurityInfoW';
{$ENDIF DYNAMIC_LINK}
{$ELSE}

{$IFDEF DYNAMIC_LINK}
var
  _GetNamedSecurityInfo: Pointer;

function GetNamedSecurityInfo;
begin
  GetProcedureAddress(_GetNamedSecurityInfo, aclapilib, 'GetNamedSecurityInfoA');
  asm
    mov esp, ebp
    pop ebp
    jmp [_GetNamedSecurityInfo]
  end;
end;
{$ELSE}
function GetNamedSecurityInfo; external aclapilib name 'GetNamedSecurityInfoA';
{$ENDIF DYNAMIC_LINK}
{$ENDIF}

{$IFDEF DYNAMIC_LINK}
var
  _GetSecurityInfo: Pointer;

function GetSecurityInfo;
begin
  GetProcedureAddress(_GetSecurityInfo, aclapilib, 'GetSecurityInfo');
  asm
    mov esp, ebp
    pop ebp
    jmp [_GetSecurityInfo]
  end;
end;
{$ELSE}
function GetSecurityInfo; external aclapilib name 'GetSecurityInfo';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _SetNamedSecurityInfoA: Pointer;

function SetNamedSecurityInfoA;
begin
  GetProcedureAddress(_SetNamedSecurityInfoA, aclapilib, 'SetNamedSecurityInfoA');
  asm
    mov esp, ebp
    pop ebp
    jmp [_SetNamedSecurityInfoA]
  end;
end;
{$ELSE}
function SetNamedSecurityInfoA; external aclapilib name 'SetNamedSecurityInfoA';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _SetNamedSecurityInfoW: Pointer;

function SetNamedSecurityInfoW;
begin
  GetProcedureAddress(_SetNamedSecurityInfoW, aclapilib, 'SetNamedSecurityInfoW');
  asm
    mov esp, ebp
    pop ebp
    jmp [_SetNamedSecurityInfoW]
  end;
end;
{$ELSE}
function SetNamedSecurityInfoW; external aclapilib name 'SetNamedSecurityInfoW';
{$ENDIF DYNAMIC_LINK}
{$IFDEF UNICODE}

{$IFDEF DYNAMIC_LINK}
var
  _SetNamedSecurityInfo: Pointer;

function SetNamedSecurityInfo;
begin
  GetProcedureAddress(_SetNamedSecurityInfo, aclapilib, 'SetNamedSecurityInfoW');
  asm
    mov esp, ebp
    pop ebp
    jmp [_SetNamedSecurityInfo]
  end;
end;
{$ELSE}
function SetNamedSecurityInfo; external aclapilib name 'SetNamedSecurityInfoW';
{$ENDIF DYNAMIC_LINK}
{$ELSE}

{$IFDEF DYNAMIC_LINK}
var
  _SetNamedSecurityInfo: Pointer;

function SetNamedSecurityInfo;
begin
  GetProcedureAddress(_SetNamedSecurityInfo, aclapilib, 'SetNamedSecurityInfoA');
  asm
    mov esp, ebp
    pop ebp
    jmp [_SetNamedSecurityInfo]
  end;
end;
{$ELSE}
function SetNamedSecurityInfo; external aclapilib name 'SetNamedSecurityInfoA';
{$ENDIF DYNAMIC_LINK}
{$ENDIF}

{$IFDEF DYNAMIC_LINK}
var
  _SetSecurityInfo: Pointer;

function SetSecurityInfo;
begin
  GetProcedureAddress(_SetSecurityInfo, aclapilib, 'SetSecurityInfo');
  asm
    mov esp, ebp
    pop ebp
    jmp [_SetSecurityInfo]
  end;
end;
{$ELSE}
function SetSecurityInfo; external aclapilib name 'SetSecurityInfo';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _GetInheritanceSourceA: Pointer;

function GetInheritanceSourceA;
begin
  GetProcedureAddress(_GetInheritanceSourceA, aclapilib, 'GetInheritanceSourceA');
  asm
    mov esp, ebp
    pop ebp
    jmp [_GetInheritanceSourceA]
  end;
end;
{$ELSE}
function GetInheritanceSourceA; external aclapilib name 'GetInheritanceSourceA';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _GetInheritanceSourceW: Pointer;

function GetInheritanceSourceW;
begin
  GetProcedureAddress(_GetInheritanceSourceW, aclapilib, 'GetInheritanceSourceW');
  asm
    mov esp, ebp
    pop ebp
    jmp [_GetInheritanceSourceW]
  end;
end;
{$ELSE}
function GetInheritanceSourceW; external aclapilib name 'GetInheritanceSourceW';
{$ENDIF DYNAMIC_LINK}
{$IFDEF UNICODE}

{$IFDEF DYNAMIC_LINK}
var
  _GetInheritanceSource: Pointer;

function GetInheritanceSource;
begin
  GetProcedureAddress(_GetInheritanceSource, aclapilib, 'GetInheritanceSourceW');
  asm
    mov esp, ebp
    pop ebp
    jmp [_GetInheritanceSource]
  end;
end;
{$ELSE}
function GetInheritanceSource; external aclapilib name 'GetInheritanceSourceW';
{$ENDIF DYNAMIC_LINK}
{$ELSE}

{$IFDEF DYNAMIC_LINK}
var
  _GetInheritanceSource: Pointer;

function GetInheritanceSource;
begin
  GetProcedureAddress(_GetInheritanceSource, aclapilib, 'GetInheritanceSourceA');
  asm
    mov esp, ebp
    pop ebp
    jmp [_GetInheritanceSource]
  end;
end;
{$ELSE}
function GetInheritanceSource; external aclapilib name 'GetInheritanceSourceA';
{$ENDIF DYNAMIC_LINK}
{$ENDIF}

{$IFDEF DYNAMIC_LINK}
var
  _FreeInheritedFromArray: Pointer;

function FreeInheritedFromArray;
begin
  GetProcedureAddress(_FreeInheritedFromArray, aclapilib, 'FreeInheritedFromArray');
  asm
    mov esp, ebp
    pop ebp
    jmp [_FreeInheritedFromArray]
  end;
end;
{$ELSE}
function FreeInheritedFromArray; external aclapilib name 'FreeInheritedFromArray';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _TreeResetNamedSecurityInfoA: Pointer;

function TreeResetNamedSecurityInfoA;
begin
  GetProcedureAddress(_TreeResetNamedSecurityInfoA, aclapilib, 'TreeResetNamedSecurityInfoA');
  asm
    mov esp, ebp
    pop ebp
    jmp [_TreeResetNamedSecurityInfoA]
  end;
end;
{$ELSE}
function TreeResetNamedSecurityInfoA; external aclapilib name 'TreeResetNamedSecurityInfoA';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _TreeResetNamedSecurityInfoW: Pointer;

function TreeResetNamedSecurityInfoW;
begin
  GetProcedureAddress(_TreeResetNamedSecurityInfoW, aclapilib, 'TreeResetNamedSecurityInfoW');
  asm
    mov esp, ebp
    pop ebp
    jmp [_TreeResetNamedSecurityInfoW]
  end;
end;
{$ELSE}
function TreeResetNamedSecurityInfoW; external aclapilib name 'TreeResetNamedSecurityInfoW';
{$ENDIF DYNAMIC_LINK}
{$IFDEF UNICODE}

{$IFDEF DYNAMIC_LINK}
var
  _TreeResetNamedSecurityInfo: Pointer;

function TreeResetNamedSecurityInfo;
begin
  GetProcedureAddress(_TreeResetNamedSecurityInfo, aclapilib, 'TreeResetNamedSecurityInfoW');
  asm
    mov esp, ebp
    pop ebp
    jmp [_TreeResetNamedSecurityInfo]
  end;
end;
{$ELSE}
function TreeResetNamedSecurityInfo; external aclapilib name 'TreeResetNamedSecurityInfoW';
{$ENDIF DYNAMIC_LINK}
{$ELSE}

{$IFDEF DYNAMIC_LINK}
var
  _TreeResetNamedSecurityInfo: Pointer;

function TreeResetNamedSecurityInfo;
begin
  GetProcedureAddress(_TreeResetNamedSecurityInfo, aclapilib, 'TreeResetNamedSecurityInfoA');
  asm
    mov esp, ebp
    pop ebp
    jmp [_TreeResetNamedSecurityInfo]
  end;
end;
{$ELSE}
function TreeResetNamedSecurityInfo; external aclapilib name 'TreeResetNamedSecurityInfoA';
{$ENDIF DYNAMIC_LINK}
{$ENDIF}

{$IFDEF DYNAMIC_LINK}
var
  _BuildSecurityDescriptorA: Pointer;

function BuildSecurityDescriptorA;
begin
  GetProcedureAddress(_BuildSecurityDescriptorA, aclapilib, 'BuildSecurityDescriptorA');
  asm
    mov esp, ebp
    pop ebp
    jmp [_BuildSecurityDescriptorA]
  end;
end;
{$ELSE}
function BuildSecurityDescriptorA; external aclapilib name 'BuildSecurityDescriptorA';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _BuildSecurityDescriptorW: Pointer;

function BuildSecurityDescriptorW;
begin
  GetProcedureAddress(_BuildSecurityDescriptorW, aclapilib, 'BuildSecurityDescriptorW');
  asm
    mov esp, ebp
    pop ebp
    jmp [_BuildSecurityDescriptorW]
  end;
end;
{$ELSE}
function BuildSecurityDescriptorW; external aclapilib name 'BuildSecurityDescriptorW';
{$ENDIF DYNAMIC_LINK}
{$IFDEF UNICODE}

{$IFDEF DYNAMIC_LINK}
var
  _BuildSecurityDescriptor: Pointer;

function BuildSecurityDescriptor;
begin
  GetProcedureAddress(_BuildSecurityDescriptor, aclapilib, 'BuildSecurityDescriptorW');
  asm
    mov esp, ebp
    pop ebp
    jmp [_BuildSecurityDescriptor]
  end;
end;
{$ELSE}
function BuildSecurityDescriptor; external aclapilib name 'BuildSecurityDescriptorW';
{$ENDIF DYNAMIC_LINK}
{$ELSE}

{$IFDEF DYNAMIC_LINK}
var
  _BuildSecurityDescriptor: Pointer;

function BuildSecurityDescriptor;
begin
  GetProcedureAddress(_BuildSecurityDescriptor, aclapilib, 'BuildSecurityDescriptorA');
  asm
    mov esp, ebp
    pop ebp
    jmp [_BuildSecurityDescriptor]
  end;
end;
{$ELSE}
function BuildSecurityDescriptor; external aclapilib name 'BuildSecurityDescriptorA';
{$ENDIF DYNAMIC_LINK}
{$ENDIF}

{$IFDEF DYNAMIC_LINK}
var
  _LookupSecurityDescriptorPartsA: Pointer;

function LookupSecurityDescriptorPartsA;
begin
  GetProcedureAddress(_LookupSecurityDescriptorPartsA, aclapilib, 'LookupSecurityDescriptorPartsA');
  asm
    mov esp, ebp
    pop ebp
    jmp [_LookupSecurityDescriptorPartsA]
  end;
end;
{$ELSE}
function LookupSecurityDescriptorPartsA; external aclapilib name 'LookupSecurityDescriptorPartsA';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _LookupSecurityDescriptorPartsW: Pointer;

function LookupSecurityDescriptorPartsW;
begin
  GetProcedureAddress(_LookupSecurityDescriptorPartsW, aclapilib, 'LookupSecurityDescriptorPartsW');
  asm
    mov esp, ebp
    pop ebp
    jmp [_LookupSecurityDescriptorPartsW]
  end;
end;
{$ELSE}
function LookupSecurityDescriptorPartsW; external aclapilib name 'LookupSecurityDescriptorPartsW';
{$ENDIF DYNAMIC_LINK}
{$IFDEF UNICODE}

{$IFDEF DYNAMIC_LINK}
var
  _LookupSecurityDescriptorParts: Pointer;

function LookupSecurityDescriptorParts;
begin
  GetProcedureAddress(_LookupSecurityDescriptorParts, aclapilib, 'LookupSecurityDescriptorPartsW');
  asm
    mov esp, ebp
    pop ebp
    jmp [_LookupSecurityDescriptorParts]
  end;
end;
{$ELSE}
function LookupSecurityDescriptorParts; external aclapilib name 'LookupSecurityDescriptorPartsW';
{$ENDIF DYNAMIC_LINK}
{$ELSE}

{$IFDEF DYNAMIC_LINK}
var
  _LookupSecurityDescriptorParts: Pointer;

function LookupSecurityDescriptorParts;
begin
  GetProcedureAddress(_LookupSecurityDescriptorParts, aclapilib, 'LookupSecurityDescriptorPartsA');
  asm
    mov esp, ebp
    pop ebp
    jmp [_LookupSecurityDescriptorParts]
  end;
end;
{$ELSE}
function LookupSecurityDescriptorParts; external aclapilib name 'LookupSecurityDescriptorPartsA';
{$ENDIF DYNAMIC_LINK}
{$ENDIF}

{$IFDEF DYNAMIC_LINK}
var
  _BuildExplicitAccessWithNameA: Pointer;

procedure BuildExplicitAccessWithNameA;
begin
  GetProcedureAddress(_BuildExplicitAccessWithNameA, aclapilib, 'BuildExplicitAccessWithNameA');
  asm
    mov esp, ebp
    pop ebp
    jmp [_BuildExplicitAccessWithNameA]
  end;
end;
{$ELSE}
procedure BuildExplicitAccessWithNameA; external aclapilib name 'BuildExplicitAccessWithNameA';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _BuildExplicitAccessWithNameW: Pointer;

procedure BuildExplicitAccessWithNameW;
begin
  GetProcedureAddress(_BuildExplicitAccessWithNameW, aclapilib, 'BuildExplicitAccessWithNameW');
  asm
    mov esp, ebp
    pop ebp
    jmp [_BuildExplicitAccessWithNameW]
  end;
end;
{$ELSE}
procedure BuildExplicitAccessWithNameW; external aclapilib name 'BuildExplicitAccessWithNameW';
{$ENDIF DYNAMIC_LINK}
{$IFDEF UNICODE}

{$IFDEF DYNAMIC_LINK}
var
  _BuildExplicitAccessWithName: Pointer;

procedure BuildExplicitAccessWithName;
begin
  GetProcedureAddress(_BuildExplicitAccessWithName, aclapilib, 'BuildExplicitAccessWithNameW');
  asm
    mov esp, ebp
    pop ebp
    jmp [_BuildExplicitAccessWithName]
  end;
end;
{$ELSE}
procedure BuildExplicitAccessWithName; external aclapilib name 'BuildExplicitAccessWithNameW';
{$ENDIF DYNAMIC_LINK}
{$ELSE}

{$IFDEF DYNAMIC_LINK}
var
  _BuildExplicitAccessWithName: Pointer;

procedure BuildExplicitAccessWithName;
begin
  GetProcedureAddress(_BuildExplicitAccessWithName, aclapilib, 'BuildExplicitAccessWithNameA');
  asm
    mov esp, ebp
    pop ebp
    jmp [_BuildExplicitAccessWithName]
  end;
end;
{$ELSE}
procedure BuildExplicitAccessWithName; external aclapilib name 'BuildExplicitAccessWithNameA';
{$ENDIF DYNAMIC_LINK}
{$ENDIF}

{$IFDEF DYNAMIC_LINK}
var
  _BuildImpersonateExplAccWNA: Pointer;

procedure BuildImpersonateExplicitAccessWithNameA;
begin
  GetProcedureAddress(_BuildImpersonateExplAccWNA, aclapilib, 'BuildImpersonateExplicitAccessWithNameA');
  asm
    mov esp, ebp
    pop ebp
    jmp [_BuildImpersonateExplAccWNA]
  end;
end;
{$ELSE}
procedure BuildImpersonateExplicitAccessWithNameA; external aclapilib name 'BuildImpersonateExplicitAccessWithNameA';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _BuildImpersonateExplAccWNW: Pointer;

procedure BuildImpersonateExplicitAccessWithNameW;
begin
  GetProcedureAddress(_BuildImpersonateExplAccWNW, aclapilib, 'BuildImpersonateExplicitAccessWithNameW');
  asm
    mov esp, ebp
    pop ebp
    jmp [_BuildImpersonateExplAccWNW]
  end;
end;
{$ELSE}
procedure BuildImpersonateExplicitAccessWithNameW; external aclapilib name 'BuildImpersonateExplicitAccessWithNameW';
{$ENDIF DYNAMIC_LINK}
{$IFDEF UNICODE}

{$IFDEF DYNAMIC_LINK}
var
  _BuildImpersonateExplAccWN: Pointer;

procedure BuildImpersonateExplicitAccessWithName;
begin
  GetProcedureAddress(_BuildImpersonateExplAccWN, aclapilib, 'BuildImpersonateExplicitAccessWithNameW');
  asm
    mov esp, ebp
    pop ebp
    jmp [_BuildImpersonateExplAccWN]
  end;
end;
{$ELSE}
procedure BuildImpersonateExplicitAccessWithName; external aclapilib name 'BuildImpersonateExplicitAccessWithNameW';
{$ENDIF DYNAMIC_LINK}
{$ELSE}

{$IFDEF DYNAMIC_LINK}
var
  _BuildImpersonateExplAccWN: Pointer;

procedure BuildImpersonateExplicitAccessWithName;
begin
  GetProcedureAddress(_BuildImpersonateExplAccWN, aclapilib, 'BuildImpersonateExplicitAccessWithNameA');
  asm
    mov esp, ebp
    pop ebp
    jmp [_BuildImpersonateExplAccWN]
  end;
end;
{$ELSE}
procedure BuildImpersonateExplicitAccessWithName; external aclapilib name 'BuildImpersonateExplicitAccessWithNameA';
{$ENDIF DYNAMIC_LINK}
{$ENDIF}

{$IFDEF DYNAMIC_LINK}
var
  _BuildTrusteeWithNameA: Pointer;

procedure BuildTrusteeWithNameA;
begin
  GetProcedureAddress(_BuildTrusteeWithNameA, aclapilib, 'BuildTrusteeWithNameA');
  asm
    mov esp, ebp
    pop ebp
    jmp [_BuildTrusteeWithNameA]
  end;
end;
{$ELSE}
procedure BuildTrusteeWithNameA; external aclapilib name 'BuildTrusteeWithNameA';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _BuildTrusteeWithNameW: Pointer;

procedure BuildTrusteeWithNameW;
begin
  GetProcedureAddress(_BuildTrusteeWithNameW, aclapilib, 'BuildTrusteeWithNameW');
  asm
    mov esp, ebp
    pop ebp
    jmp [_BuildTrusteeWithNameW]
  end;
end;
{$ELSE}
procedure BuildTrusteeWithNameW; external aclapilib name 'BuildTrusteeWithNameW';
{$ENDIF DYNAMIC_LINK}
{$IFDEF UNICODE}

{$IFDEF DYNAMIC_LINK}
var
  _BuildTrusteeWithName: Pointer;

procedure BuildTrusteeWithName;
begin
  GetProcedureAddress(_BuildTrusteeWithName, aclapilib, 'BuildTrusteeWithNameW');
  asm
    mov esp, ebp
    pop ebp
    jmp [_BuildTrusteeWithName]
  end;
end;
{$ELSE}
procedure BuildTrusteeWithName; external aclapilib name 'BuildTrusteeWithNameW';
{$ENDIF DYNAMIC_LINK}
{$ELSE}

{$IFDEF DYNAMIC_LINK}
var
  _BuildTrusteeWithName: Pointer;

procedure BuildTrusteeWithName;
begin
  GetProcedureAddress(_BuildTrusteeWithName, aclapilib, 'BuildTrusteeWithNameA');
  asm
    mov esp, ebp
    pop ebp
    jmp [_BuildTrusteeWithName]
  end;
end;
{$ELSE}
procedure BuildTrusteeWithName; external aclapilib name 'BuildTrusteeWithNameA';
{$ENDIF DYNAMIC_LINK}
{$ENDIF}

{$IFDEF DYNAMIC_LINK}
var
  _BuildImpersonateTrusteeA: Pointer;

procedure BuildImpersonateTrusteeA;
begin
  GetProcedureAddress(_BuildImpersonateTrusteeA, aclapilib, 'BuildImpersonateTrusteeA');
  asm
    mov esp, ebp
    pop ebp
    jmp [_BuildImpersonateTrusteeA]
  end;
end;
{$ELSE}
procedure BuildImpersonateTrusteeA; external aclapilib name 'BuildImpersonateTrusteeA';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _BuildImpersonateTrusteeW: Pointer;

procedure BuildImpersonateTrusteeW;
begin
  GetProcedureAddress(_BuildImpersonateTrusteeW, aclapilib, 'BuildImpersonateTrusteeW');
  asm
    mov esp, ebp
    pop ebp
    jmp [_BuildImpersonateTrusteeW]
  end;
end;
{$ELSE}
procedure BuildImpersonateTrusteeW; external aclapilib name 'BuildImpersonateTrusteeW';
{$ENDIF DYNAMIC_LINK}
{$IFDEF UNICODE}

{$IFDEF DYNAMIC_LINK}
var
  _BuildImpersonateTrustee: Pointer;

procedure BuildImpersonateTrustee;
begin
  GetProcedureAddress(_BuildImpersonateTrustee, aclapilib, 'BuildImpersonateTrusteeW');
  asm
    mov esp, ebp
    pop ebp
    jmp [_BuildImpersonateTrustee]
  end;
end;
{$ELSE}
procedure BuildImpersonateTrustee; external aclapilib name 'BuildImpersonateTrusteeW';
{$ENDIF DYNAMIC_LINK}
{$ELSE}

{$IFDEF DYNAMIC_LINK}
var
  _BuildImpersonateTrustee: Pointer;

procedure BuildImpersonateTrustee;
begin
  GetProcedureAddress(_BuildImpersonateTrustee, aclapilib, 'BuildImpersonateTrusteeA');
  asm
    mov esp, ebp
    pop ebp
    jmp [_BuildImpersonateTrustee]
  end;
end;
{$ELSE}
procedure BuildImpersonateTrustee; external aclapilib name 'BuildImpersonateTrusteeA';
{$ENDIF DYNAMIC_LINK}
{$ENDIF}

{$IFDEF DYNAMIC_LINK}
var
  _BuildTrusteeWithSidA: Pointer;

procedure BuildTrusteeWithSidA;
begin
  GetProcedureAddress(_BuildTrusteeWithSidA, aclapilib, 'BuildTrusteeWithSidA');
  asm
    mov esp, ebp
    pop ebp
    jmp [_BuildTrusteeWithSidA]
  end;
end;
{$ELSE}
procedure BuildTrusteeWithSidA; external aclapilib name 'BuildTrusteeWithSidA';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _BuildTrusteeWithSidW: Pointer;

procedure BuildTrusteeWithSidW;
begin
  GetProcedureAddress(_BuildTrusteeWithSidW, aclapilib, 'BuildTrusteeWithSidW');
  asm
    mov esp, ebp
    pop ebp
    jmp [_BuildTrusteeWithSidW]
  end;
end;
{$ELSE}
procedure BuildTrusteeWithSidW; external aclapilib name 'BuildTrusteeWithSidW';
{$ENDIF DYNAMIC_LINK}
{$IFDEF UNICODE}

{$IFDEF DYNAMIC_LINK}
var
  _BuildTrusteeWithSid: Pointer;

procedure BuildTrusteeWithSid;
begin
  GetProcedureAddress(_BuildTrusteeWithSid, aclapilib, 'BuildTrusteeWithSidW');
  asm
    mov esp, ebp
    pop ebp
    jmp [_BuildTrusteeWithSid]
  end;
end;
{$ELSE}
procedure BuildTrusteeWithSid; external aclapilib name 'BuildTrusteeWithSidW';
{$ENDIF DYNAMIC_LINK}
{$ELSE}

{$IFDEF DYNAMIC_LINK}
var
  _BuildTrusteeWithSid: Pointer;

procedure BuildTrusteeWithSid;
begin
  GetProcedureAddress(_BuildTrusteeWithSid, aclapilib, 'BuildTrusteeWithSidA');
  asm
    mov esp, ebp
    pop ebp
    jmp [_BuildTrusteeWithSid]
  end;
end;
{$ELSE}
procedure BuildTrusteeWithSid; external aclapilib name 'BuildTrusteeWithSidA';
{$ENDIF DYNAMIC_LINK}
{$ENDIF}

{$IFDEF DYNAMIC_LINK}
var
  _BuildTrusteeWithObjectsAndSidA: Pointer;

procedure BuildTrusteeWithObjectsAndSidA;
begin
  GetProcedureAddress(_BuildTrusteeWithObjectsAndSidA, aclapilib, 'BuildTrusteeWithObjectsAndSidA');
  asm
    mov esp, ebp
    pop ebp
    jmp [_BuildTrusteeWithObjectsAndSidA]
  end;
end;
{$ELSE}
procedure BuildTrusteeWithObjectsAndSidA; external aclapilib name 'BuildTrusteeWithObjectsAndSidA';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _BuildTrusteeWithObjectsAndSidW: Pointer;

procedure BuildTrusteeWithObjectsAndSidW;
begin
  GetProcedureAddress(_BuildTrusteeWithObjectsAndSidW, aclapilib, 'BuildTrusteeWithObjectsAndSidW');
  asm
    mov esp, ebp
    pop ebp
    jmp [_BuildTrusteeWithObjectsAndSidW]
  end;
end;
{$ELSE}
procedure BuildTrusteeWithObjectsAndSidW; external aclapilib name 'BuildTrusteeWithObjectsAndSidW';
{$ENDIF DYNAMIC_LINK}
{$IFDEF UNICODE}

{$IFDEF DYNAMIC_LINK}
var
  _BuildTrusteeWithObjectsAndSid: Pointer;

procedure BuildTrusteeWithObjectsAndSid;
begin
  GetProcedureAddress(_BuildTrusteeWithObjectsAndSid, aclapilib, 'BuildTrusteeWithObjectsAndSidW');
  asm
    mov esp, ebp
    pop ebp
    jmp [_BuildTrusteeWithObjectsAndSid]
  end;
end;
{$ELSE}
procedure BuildTrusteeWithObjectsAndSid; external aclapilib name 'BuildTrusteeWithObjectsAndSidW';
{$ENDIF DYNAMIC_LINK}
{$ELSE}

{$IFDEF DYNAMIC_LINK}
var
  _BuildTrusteeWithObjectsAndSid: Pointer;

procedure BuildTrusteeWithObjectsAndSid;
begin
  GetProcedureAddress(_BuildTrusteeWithObjectsAndSid, aclapilib, 'BuildTrusteeWithObjectsAndSidA');
  asm
    mov esp, ebp
    pop ebp
    jmp [_BuildTrusteeWithObjectsAndSid]
  end;
end;
{$ELSE}
procedure BuildTrusteeWithObjectsAndSid; external aclapilib name 'BuildTrusteeWithObjectsAndSidA';
{$ENDIF DYNAMIC_LINK}
{$ENDIF}

{$IFDEF DYNAMIC_LINK}
var
  _BuildTrusteeWithObjectsAndNameA: Pointer;

procedure BuildTrusteeWithObjectsAndNameA;
begin
  GetProcedureAddress(_BuildTrusteeWithObjectsAndNameA, aclapilib, 'BuildTrusteeWithObjectsAndNameA');
  asm
    mov esp, ebp
    pop ebp
    jmp [_BuildTrusteeWithObjectsAndNameA]
  end;
end;
{$ELSE}
procedure BuildTrusteeWithObjectsAndNameA; external aclapilib name 'BuildTrusteeWithObjectsAndNameA';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _BuildTrusteeWithObjectsAndNameW: Pointer;

procedure BuildTrusteeWithObjectsAndNameW;
begin
  GetProcedureAddress(_BuildTrusteeWithObjectsAndNameW, aclapilib, 'BuildTrusteeWithObjectsAndNameW');
  asm
    mov esp, ebp
    pop ebp
    jmp [_BuildTrusteeWithObjectsAndNameW]
  end;
end;
{$ELSE}
procedure BuildTrusteeWithObjectsAndNameW; external aclapilib name 'BuildTrusteeWithObjectsAndNameW';
{$ENDIF DYNAMIC_LINK}
{$IFDEF UNICODE}

{$IFDEF DYNAMIC_LINK}
var
  _BuildTrusteeWithObjectsAndName: Pointer;

procedure BuildTrusteeWithObjectsAndName;
begin
  GetProcedureAddress(_BuildTrusteeWithObjectsAndName, aclapilib, 'BuildTrusteeWithObjectsAndNameW');
  asm
    mov esp, ebp
    pop ebp
    jmp [_BuildTrusteeWithObjectsAndName]
  end;
end;
{$ELSE}
procedure BuildTrusteeWithObjectsAndName; external aclapilib name 'BuildTrusteeWithObjectsAndNameW';
{$ENDIF DYNAMIC_LINK}
{$ELSE}

{$IFDEF DYNAMIC_LINK}
var
  _BuildTrusteeWithObjectsAndName: Pointer;

procedure BuildTrusteeWithObjectsAndName;
begin
  GetProcedureAddress(_BuildTrusteeWithObjectsAndName, aclapilib, 'BuildTrusteeWithObjectsAndNameA');
  asm
    mov esp, ebp
    pop ebp
    jmp [_BuildTrusteeWithObjectsAndName]
  end;
end;
{$ELSE}
procedure BuildTrusteeWithObjectsAndName; external aclapilib name 'BuildTrusteeWithObjectsAndNameA';
{$ENDIF DYNAMIC_LINK}
{$ENDIF}

{$IFDEF DYNAMIC_LINK}
var
  _GetTrusteeNameA: Pointer;

function GetTrusteeNameA;
begin
  GetProcedureAddress(_GetTrusteeNameA, aclapilib, 'GetTrusteeNameA');
  asm
    mov esp, ebp
    pop ebp
    jmp [_GetTrusteeNameA]
  end;
end;
{$ELSE}
function GetTrusteeNameA; external aclapilib name 'GetTrusteeNameA';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _GetTrusteeNameW: Pointer;

function GetTrusteeNameW;
begin
  GetProcedureAddress(_GetTrusteeNameW, aclapilib, 'GetTrusteeNameW');
  asm
    mov esp, ebp
    pop ebp
    jmp [_GetTrusteeNameW]
  end;
end;
{$ELSE}
function GetTrusteeNameW; external aclapilib name 'GetTrusteeNameW';
{$ENDIF DYNAMIC_LINK}
{$IFDEF UNICODE}

{$IFDEF DYNAMIC_LINK}
var
  _GetTrusteeName: Pointer;

function GetTrusteeName;
begin
  GetProcedureAddress(_GetTrusteeName, aclapilib, 'GetTrusteeNameW');
  asm
    mov esp, ebp
    pop ebp
    jmp [_GetTrusteeName]
  end;
end;
{$ELSE}
function GetTrusteeName; external aclapilib name 'GetTrusteeNameW';
{$ENDIF DYNAMIC_LINK}
{$ELSE}

{$IFDEF DYNAMIC_LINK}
var
  _GetTrusteeName: Pointer;

function GetTrusteeName;
begin
  GetProcedureAddress(_GetTrusteeName, aclapilib, 'GetTrusteeNameA');
  asm
    mov esp, ebp
    pop ebp
    jmp [_GetTrusteeName]
  end;
end;
{$ELSE}
function GetTrusteeName; external aclapilib name 'GetTrusteeNameA';
{$ENDIF DYNAMIC_LINK}
{$ENDIF}

{$IFDEF DYNAMIC_LINK}
var
  _GetTrusteeTypeA: Pointer;

function GetTrusteeTypeA;
begin
  GetProcedureAddress(_GetTrusteeTypeA, aclapilib, 'GetTrusteeTypeA');
  asm
    mov esp, ebp
    pop ebp
    jmp [_GetTrusteeTypeA]
  end;
end;
{$ELSE}
function GetTrusteeTypeA; external aclapilib name 'GetTrusteeTypeA';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _GetTrusteeTypeW: Pointer;

function GetTrusteeTypeW;
begin
  GetProcedureAddress(_GetTrusteeTypeW, aclapilib, 'GetTrusteeTypeW');
  asm
    mov esp, ebp
    pop ebp
    jmp [_GetTrusteeTypeW]
  end;
end;
{$ELSE}
function GetTrusteeTypeW; external aclapilib name 'GetTrusteeTypeW';
{$ENDIF DYNAMIC_LINK}
{$IFDEF UNICODE}

{$IFDEF DYNAMIC_LINK}
var
  _GetTrusteeType: Pointer;

function GetTrusteeType;
begin
  GetProcedureAddress(_GetTrusteeType, aclapilib, 'GetTrusteeTypeW');
  asm
    mov esp, ebp
    pop ebp
    jmp [_GetTrusteeType]
  end;
end;
{$ELSE}
function GetTrusteeType; external aclapilib name 'GetTrusteeTypeW';
{$ENDIF DYNAMIC_LINK}
{$ELSE}

{$IFDEF DYNAMIC_LINK}
var
  _GetTrusteeType: Pointer;

function GetTrusteeType;
begin
  GetProcedureAddress(_GetTrusteeType, aclapilib, 'GetTrusteeTypeA');
  asm
    mov esp, ebp
    pop ebp
    jmp [_GetTrusteeType]
  end;
end;
{$ELSE}
function GetTrusteeType; external aclapilib name 'GetTrusteeTypeA';
{$ENDIF DYNAMIC_LINK}
{$ENDIF}

{$IFDEF DYNAMIC_LINK}
var
  _GetTrusteeFormA: Pointer;

function GetTrusteeFormA;
begin
  GetProcedureAddress(_GetTrusteeFormA, aclapilib, 'GetTrusteeFormA');
  asm
    mov esp, ebp
    pop ebp
    jmp [_GetTrusteeFormA]
  end;
end;
{$ELSE}
function GetTrusteeFormA; external aclapilib name 'GetTrusteeFormA';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _GetTrusteeFormW: Pointer;

function GetTrusteeFormW;
begin
  GetProcedureAddress(_GetTrusteeFormW, aclapilib, 'GetTrusteeFormW');
  asm
    mov esp, ebp
    pop ebp
    jmp [_GetTrusteeFormW]
  end;
end;
{$ELSE}
function GetTrusteeFormW; external aclapilib name 'GetTrusteeFormW';
{$ENDIF DYNAMIC_LINK}
{$IFDEF UNICODE}

{$IFDEF DYNAMIC_LINK}
var
  _GetTrusteeForm: Pointer;

function GetTrusteeForm;
begin
  GetProcedureAddress(_GetTrusteeForm, aclapilib, 'GetTrusteeFormW');
  asm
    mov esp, ebp
    pop ebp
    jmp [_GetTrusteeForm]
  end;
end;
{$ELSE}
function GetTrusteeForm; external aclapilib name 'GetTrusteeFormW';
{$ENDIF DYNAMIC_LINK}
{$ELSE}

{$IFDEF DYNAMIC_LINK}
var
  _GetTrusteeForm: Pointer;

function GetTrusteeForm;
begin
  GetProcedureAddress(_GetTrusteeForm, aclapilib, 'GetTrusteeFormA');
  asm
    mov esp, ebp
    pop ebp
    jmp [_GetTrusteeForm]
  end;
end;
{$ELSE}
function GetTrusteeForm; external aclapilib name 'GetTrusteeFormA';
{$ENDIF DYNAMIC_LINK}
{$ENDIF}

{$IFDEF DYNAMIC_LINK}
var
  _GetMultipleTrusteeOperationA: Pointer;

function GetMultipleTrusteeOperationA;
begin
  GetProcedureAddress(_GetMultipleTrusteeOperationA, aclapilib, 'GetMultipleTrusteeOperationA');
  asm
    mov esp, ebp
    pop ebp
    jmp [_GetMultipleTrusteeOperationA]
  end;
end;
{$ELSE}
function GetMultipleTrusteeOperationA; external aclapilib name 'GetMultipleTrusteeOperationA';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _GetMultipleTrusteeOperationW: Pointer;

function GetMultipleTrusteeOperationW;
begin
  GetProcedureAddress(_GetMultipleTrusteeOperationW, aclapilib, 'GetMultipleTrusteeOperationW');
  asm
    mov esp, ebp
    pop ebp
    jmp [_GetMultipleTrusteeOperationW]
  end;
end;
{$ELSE}
function GetMultipleTrusteeOperationW; external aclapilib name 'GetMultipleTrusteeOperationW';
{$ENDIF DYNAMIC_LINK}
{$IFDEF UNICODE}

{$IFDEF DYNAMIC_LINK}
var
  _GetMultipleTrusteeOperation: Pointer;

function GetMultipleTrusteeOperation;
begin
  GetProcedureAddress(_GetMultipleTrusteeOperation, aclapilib, 'GetMultipleTrusteeOperationW');
  asm
    mov esp, ebp
    pop ebp
    jmp [_GetMultipleTrusteeOperation]
  end;
end;
{$ELSE}
function GetMultipleTrusteeOperation; external aclapilib name 'GetMultipleTrusteeOperationW';
{$ENDIF DYNAMIC_LINK}
{$ELSE}

{$IFDEF DYNAMIC_LINK}
var
  _GetMultipleTrusteeOperation: Pointer;

function GetMultipleTrusteeOperation;
begin
  GetProcedureAddress(_GetMultipleTrusteeOperation, aclapilib, 'GetMultipleTrusteeOperationA');
  asm
    mov esp, ebp
    pop ebp
    jmp [_GetMultipleTrusteeOperation]
  end;
end;
{$ELSE}
function GetMultipleTrusteeOperation; external aclapilib name 'GetMultipleTrusteeOperationA';
{$ENDIF DYNAMIC_LINK}
{$ENDIF}

{$IFDEF DYNAMIC_LINK}
var
  _GetMultipleTrusteeA: Pointer;

function GetMultipleTrusteeA;
begin
  GetProcedureAddress(_GetMultipleTrusteeA, aclapilib, 'GetMultipleTrusteeA');
  asm
    mov esp, ebp
    pop ebp
    jmp [_GetMultipleTrusteeA]
  end;
end;
{$ELSE}
function GetMultipleTrusteeA; external aclapilib name 'GetMultipleTrusteeA';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _GetMultipleTrusteeW: Pointer;

function GetMultipleTrusteeW;
begin
  GetProcedureAddress(_GetMultipleTrusteeW, aclapilib, 'GetMultipleTrusteeW');
  asm
    mov esp, ebp
    pop ebp
    jmp [_GetMultipleTrusteeW]
  end;
end;
{$ELSE}
function GetMultipleTrusteeW; external aclapilib name 'GetMultipleTrusteeW';
{$ENDIF DYNAMIC_LINK}
{$IFDEF UNICODE}

{$IFDEF DYNAMIC_LINK}
var
  _GetMultipleTrustee: Pointer;

function GetMultipleTrustee;
begin
  GetProcedureAddress(_GetMultipleTrustee, aclapilib, 'GetMultipleTrusteeW');
  asm
    mov esp, ebp
    pop ebp
    jmp [_GetMultipleTrustee]
  end;
end;
{$ELSE}
function GetMultipleTrustee; external aclapilib name 'GetMultipleTrusteeW';
{$ENDIF DYNAMIC_LINK}
{$ELSE}

{$IFDEF DYNAMIC_LINK}
var
  _GetMultipleTrustee: Pointer;

function GetMultipleTrustee;
begin
  GetProcedureAddress(_GetMultipleTrustee, aclapilib, 'GetMultipleTrusteeA');
  asm
    mov esp, ebp
    pop ebp
    jmp [_GetMultipleTrustee]
  end;
end;
{$ELSE}
function GetMultipleTrustee; external aclapilib name 'GetMultipleTrusteeA';
{$ENDIF DYNAMIC_LINK}
{$ENDIF}

end.
