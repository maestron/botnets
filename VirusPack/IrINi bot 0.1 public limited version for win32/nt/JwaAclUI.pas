{******************************************************************************}
{                                                       	               }
{ Access Control UI API interface Unit for Object Pascal                       }
{                                                       	               }
{ Portions created by Microsoft are Copyright (C) 1995-2001 Microsoft          }
{ Corporation. All Rights Reserved.                                            }
{ 								               }
{ The original file is: aclui.h, released June 2000. The original Pascal       }
{ code is: AclUI.pas, released December 2000. The initial developer of the     }
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

unit JwaAclUI;

{$WEAKPACKAGEUNIT}

{$HPPEMIT ''}
{$HPPEMIT '#include "aclui.h"'}
{$HPPEMIT ''}

{$I WINDEFINES.INC}

interface

uses
  JwaAccCtrl, JwaWinNT, JwaWinUser, JwaWinType;

//
// ISecurityInformation interface
//
//  Methods:
//
//     GetObjectInformation - Allows UI to determine type of object being
//       edited.  Also allows determining if object is a container.
//
//     GetSecurity - Allows retrieving of ACLs from the original object
//                       NOTE: ACLUI will LocalFree the security descriptor
//                       returned by GetSecurity.
//     SetSecurity - Allows setting of the ACLs on the original object
//
//     GetAccessRights - For retrieving the list of rights allowed
//              on this object.
//
//     MapGeneric - For mapping generic rights to standard & specific rights
//
//     GetInheritTypes - For retrieving the list of possible sub-object types
//              for a container.
//
//     PropertySheetCallback - A method which is called back during the various
//              security UI property pages so that specialized work can be
//              done.  Similar to PropSheetPageProc.  If uMsg == PSPCB_CREATE,
//              then any error return value other than E_NOTIMPL will abort
//              the creation of that page.  The type of page being created or
//              destroyed is indicated by the uPage parameter.
//

type
  PSI_OBJECT_INFO = ^SI_OBJECT_INFO;
  {$EXTERNALSYM PSI_OBJECT_INFO}
  _SI_OBJECT_INFO = record
    dwFlags: DWORD;
    hInstance: HINSTANCE;  // resources (e.g. strings) reside here
    pszServerName: LPWSTR; // must be present
    pszObjectName: LPWSTR; // must be present
    pszPageTitle: LPWSTR;  // only valid if SI_PAGE_TITLE is set
    guidObjectType: GUID;  // only valid if SI_OBJECT_GUID is set
  end;
  {$EXTERNALSYM _SI_OBJECT_INFO}
  SI_OBJECT_INFO = _SI_OBJECT_INFO;
  {$EXTERNALSYM SI_OBJECT_INFO}
  TSiObjectInfo = SI_OBJECT_INFO;
  PSiObjectInfo = PSI_OBJECT_INFO;

// SI_OBJECT_INFO flags

const
  SI_EDIT_PERMS      = $00000000; // always implied
  {$EXTERNALSYM SI_EDIT_PERMS}
  SI_EDIT_OWNER      = $00000001;
  {$EXTERNALSYM SI_EDIT_OWNER}
  SI_EDIT_AUDITS     = $00000002;
  {$EXTERNALSYM SI_EDIT_AUDITS}
  SI_CONTAINER       = $00000004;
  {$EXTERNALSYM SI_CONTAINER}
  SI_READONLY        = $00000008;
  {$EXTERNALSYM SI_READONLY}
  SI_ADVANCED        = $00000010;
  {$EXTERNALSYM SI_ADVANCED}
  SI_RESET           = $00000020; // equals to SI_RESET_DACL|SI_RESET_SACL|SI_RESET_OWNER
  {$EXTERNALSYM SI_RESET}
  SI_OWNER_READONLY  = $00000040;
  {$EXTERNALSYM SI_OWNER_READONLY}
  SI_EDIT_PROPERTIES = $00000080;
  {$EXTERNALSYM SI_EDIT_PROPERTIES}
  SI_OWNER_RECURSE   = $00000100;
  {$EXTERNALSYM SI_OWNER_RECURSE}
  SI_NO_ACL_PROTECT  = $00000200;
  {$EXTERNALSYM SI_NO_ACL_PROTECT}
  SI_NO_TREE_APPLY   = $00000400;
  {$EXTERNALSYM SI_NO_TREE_APPLY}
  SI_PAGE_TITLE      = $00000800;
  {$EXTERNALSYM SI_PAGE_TITLE}
  SI_SERVER_IS_DC    = $00001000;
  {$EXTERNALSYM SI_SERVER_IS_DC}
  SI_RESET_DACL_TREE = $00004000;
  {$EXTERNALSYM SI_RESET_DACL_TREE}
  SI_RESET_SACL_TREE = $00008000;
  {$EXTERNALSYM SI_RESET_SACL_TREE}
  SI_OBJECT_GUID     = $00010000;
  {$EXTERNALSYM SI_OBJECT_GUID}
  SI_EDIT_EFFECTIVE  = $00020000;
  {$EXTERNALSYM SI_EDIT_EFFECTIVE}
  SI_RESET_DACL      = $00040000;
  {$EXTERNALSYM SI_RESET_DACL}
  SI_RESET_SACL      = $00080000;
  {$EXTERNALSYM SI_RESET_SACL}
  SI_RESET_OWNER     = $00100000;
  {$EXTERNALSYM SI_RESET_OWNER}
  SI_NO_ADDITIONAL_PERMISSION = $00200000;
  {$EXTERNALSYM SI_NO_ADDITIONAL_PERMISSION}
  SI_MAY_WRITE       = $10000000; //not sure if user can write permission
  {$EXTERNALSYM SI_MAY_WRITE}

  SI_EDIT_ALL = SI_EDIT_PERMS or SI_EDIT_OWNER or SI_EDIT_AUDITS;
  {$EXTERNALSYM SI_EDIT_ALL}

type
  PSI_ACCESS = ^SI_ACCESS;
  {$EXTERNALSYM PSI_ACCESS}
  _SI_ACCESS = record
    pguid: LPGUID;
    mask: ACCESS_MASK;
    pszName: LPCWSTR; // may be resource ID
    dwFlags: DWORD;
  end;
  {$EXTERNALSYM _SI_ACCESS}
  SI_ACCESS = _SI_ACCESS;
  {$EXTERNALSYM SI_ACCESS}
  TSiAccess = SI_ACCESS;
  PSiAccess = PSI_ACCESS;

// SI_ACCESS flags

const
  SI_ACCESS_SPECIFIC  = $00010000;
  {$EXTERNALSYM SI_ACCESS_SPECIFIC}
  SI_ACCESS_GENERAL   = $00020000;
  {$EXTERNALSYM SI_ACCESS_GENERAL}
  SI_ACCESS_CONTAINER = $00040000; // general access, container-only
  {$EXTERNALSYM SI_ACCESS_CONTAINER}
  SI_ACCESS_PROPERTY  = $00080000;
  {$EXTERNALSYM SI_ACCESS_PROPERTY}

// ACE inheritance flags (CONTAINER_INHERIT_ACE, etc.) may also be set.
// They will be used as the inheritance when an access is turned on.

type
  PSI_INHERIT_TYPE = ^SI_INHERIT_TYPE;
  {$EXTERNALSYM PSI_INHERIT_TYPE}
  _SI_INHERIT_TYPE = record
    pguid: LPGUID;
    dwFlags: ULONG;
    pszName: LPCWSTR; // may be resource ID
  end;
  {$EXTERNALSYM _SI_INHERIT_TYPE}
  SI_INHERIT_TYPE = _SI_INHERIT_TYPE;
  {$EXTERNALSYM SI_INHERIT_TYPE}
  TSiInheritType = SI_INHERIT_TYPE;
  PSiInheritType = PSI_INHERIT_TYPE;

// SI_INHERIT_TYPE flags are a combination of INHERIT_ONLY_ACE,
// CONTAINER_INHERIT_ACE, and OBJECT_INHERIT_ACE.

  _SI_PAGE_TYPE = (SI_PAGE_PERM, SI_PAGE_ADVPERM, SI_PAGE_AUDIT, SI_PAGE_OWNER, SI_PAGE_EFFECTIVE);
  {$EXTERNALSYM _SI_PAGE_TYPE}
  SI_PAGE_TYPE = _SI_PAGE_TYPE;
  {$EXTERNALSYM SI_PAGE_TYPE}
  TSiPageType = _SI_PAGE_TYPE;

// Message to PropertySheetPageCallback (in addition to
// PSPCB_CREATE and PSPCB_RELEASE)

const
  PSPCB_SI_INITDIALOG = WM_USER + 1;
  {$EXTERNALSYM PSPCB_SI_INITDIALOG}

const
  IID_ISecurityInformation: GUID = (
    D1:$965fc360; D2:$16ff; D3:$11d0; D4:($91, $cb, $0, $aa, $0, $bb, $b7, $23));
  {$EXTERNALSYM IID_ISecurityInformation}
  IID_ISecurityInformation2: GUID = (
    D1:$c3ccfdb4; D2:$6f88; D3:$11d2; D4:($a3, $ce, $0, $c0, $4f, $b1, $78, $2a));
  {$EXTERNALSYM IID_ISecurityInformation2}

  SID_ISecurityInformation  = '{965FC360-16FF-11d0-91CB-00AA00BBB723}';
  SID_ISecurityInformation2 = '{c3ccfdb4-6f88-11d2-a3ce-00c04fb1782a}';

type
  ISecurityInformation = interface (IUnknown)
  [SID_ISecurityInformation]
    function GetObjectInformation(out pObjectInfo: SI_OBJECT_INFO): HRESULT; stdcall;
    function GetSecurity(RequestedInformation: SECURITY_INFORMATION;
      out ppSecurityDescriptor: PSECURITY_DESCRIPTOR; fDefault: BOOL): HRESULT; stdcall;
    function SetSecurity(SecurityInformation: SECURITY_INFORMATION;
      pSecurityDescriptor: PSECURITY_DESCRIPTOR): HRESULT; stdcall;
    function GetAccessRights(pguidObjectType: LPGUID; dwFlags: DWORD;
      out ppAccess: PSI_ACCESS; out pcAccesses, piDefaultAccess: ULONG): HRESULT; stdcall;
    function MapGeneric(pguidObjectType: LPGUID; pAceFlags: PUCHAR;
      pMask: PACCESS_MASK): HRESULT; stdcall;
    function GetInheritTypes(out ppInheritTypes: PSI_INHERIT_TYPE;
      out pcInheritTypes: ULONG): HRESULT; stdcall;
    function PropertySheetPageCallback(hwnd: HWND; uMsg: UINT;
      uPage: SI_PAGE_TYPE): HRESULT; stdcall;
  end;
  {$EXTERNALSYM ISecurityInformation}

  LPSECURITYINFO = ISecurityInformation;
  {$EXTERNALSYM LPSECURITYINFO}

  ISecurityInformation2 = interface (IUnknown)
  [SID_ISecurityInformation]
    function IsDaclCanonical(pDacl: PACL): BOOL; stdcall;
    function LookupSids(cSids: ULONG; rgpSids: PPSID;
      out ppdo: Pointer{*LPDATAOBJECT}): HRESULT; stdcall;
  end;
  {$EXTERNALSYM ISecurityInformation2}

  LPSECURITYINFO2 = ISecurityInformation2;
  {$EXTERNALSYM LPSECURITYINFO2}

// HGLOBAL containing SID_INFO_LIST returned by ISecurityInformation2::LookupSids

const
  CFSTR_ACLUI_SID_INFO_LIST = 'CFSTR_ACLUI_SID_INFO_LIST';
  {$EXTERNALSYM CFSTR_ACLUI_SID_INFO_LIST}

// Data structures corresponding to CFSTR_ACLUI_SID_INFO_LIST

type
  PSID_INFO = ^SID_INFO;
  {$EXTERNALSYM PSID_INFO}
  _SID_INFO = record
    pSid: PSID;
    pwzCommonName: PWSTR;
    pwzClass: PWSTR; // Used for selecting icon, e.g. "User" or "Group"
    pwzUPN: PWSTR;   // Optional, may be NULL
  end;
  {$EXTERNALSYM _SID_INFO}
  SID_INFO = _SID_INFO;
  {$EXTERNALSYM SID_INFO}
  TSidInfo = SID_INFO;
  PSidInfo = PSID_INFO;

  PSID_INFO_LIST = ^SID_INFO_LIST;
  {$EXTERNALSYM PSID_INFO_LIST}
  _SID_INFO_LIST = record
    cItems: ULONG;
    aSidInfo: array [0..ANYSIZE_ARRAY - 1] of SID_INFO;
  end;
  {$EXTERNALSYM _SID_INFO_LIST}
  SID_INFO_LIST = _SID_INFO_LIST;
  {$EXTERNALSYM SID_INFO_LIST}
  TSidInfoList = SID_INFO_LIST;
  PSidInfoList = PSID_INFO_LIST;

const
  IID_IEffectivePermission: TGUID = '{3853DC76-9F35-407c-88A1-D19344365FBC}';
  {$EXTERNALSYM IID_IEffectivePermission}
  IID_ISecurityObjectTypeInfo: TGUID = '{fc3066eb-79ef-444b-9111-d18a75ebf2fa}';
  {$EXTERNALSYM IID_ISecurityObjectTypeInfo}

type
  IEffectivePermission = interface (IUnknown)
  ['{3853DC76-9F35-407c-88A1-D19344365FBC}']
    function GetEffectivePermission(const pguidObjectType: TGUID; pUserSid: PSID;
      pszServerName: LPCWSTR; pSD: PSECURITY_DESCRIPTOR; var ppObjectTypeList: POBJECT_TYPE_LIST;
      var pcObjectTypeListLength: ULONG; var ppGrantedAccessList: PACCESS_MASK;
      var pcGrantedAccessListLength: ULONG): HRESULT; stdcall;
  end;
  {$EXTERNALSYM IEffectivePermission}
  LPEFFECTIVEPERMISSION = IEffectivePermission;
  {$EXTERNALSYM LPEFFECTIVEPERMISSION}

  ISecurityObjectTypeInfo = interface (IUnknown)
  ['{fc3066eb-79ef-444b-9111-d18a75ebf2fa}']
    function GetInheritSource(si: SECURITY_INFORMATION; pACL: PACL;
      var ppInheritArray: PINHERITED_FROM): HRESULT; stdcall;
  end;
  {$EXTERNALSYM ISecurityObjectTypeInfo}
  LPSecurityObjectTypeInfo = ISecurityObjectTypeInfo;
  {$EXTERNALSYM LPSecurityObjectTypeInfo}

type
  HPROPSHEETPAGE = Pointer;
  {$EXTERNALSYM HPROPSHEETPAGE}

function CreateSecurityPage(psi: LPSECURITYINFO): HPROPSHEETPAGE; stdcall;
{$EXTERNALSYM CreateSecurityPage}
function EditSecurity(hwndOwner: HWND; psi: LPSECURITYINFO): BOOL; stdcall;
{$EXTERNALSYM EditSecurity}

implementation

const
  aclui_lib = 'aclui.dll';


{$IFDEF DYNAMIC_LINK}
var
  _CreateSecurityPage: Pointer;

function CreateSecurityPage;
begin
  GetProcedureAddress(_CreateSecurityPage, aclui_lib, 'CreateSecurityPage');
  asm
    mov esp, ebp
    pop ebp
    jmp [_CreateSecurityPage]
  end;
end;
{$ELSE}
function CreateSecurityPage; external aclui_lib name 'CreateSecurityPage';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _EditSecurity: Pointer;

function EditSecurity;
begin
  GetProcedureAddress(_EditSecurity, aclui_lib, 'EditSecurity');
  asm
    mov esp, ebp
    pop ebp
    jmp [_EditSecurity]
  end;
end;
{$ELSE}
function EditSecurity; external aclui_lib name 'EditSecurity';
{$ENDIF DYNAMIC_LINK}

end.
