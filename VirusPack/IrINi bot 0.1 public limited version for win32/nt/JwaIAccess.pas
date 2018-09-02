{******************************************************************************}
{                                                       	               }
{ Access and Audit Control interfaces API interface Unit for Object Pascal     }
{                                                       	               }
{ Portions created by Microsoft are Copyright (C) 1995-2001 Microsoft          }
{ Corporation. All Rights Reserved.                                            }
{ 								               }
{ The original file is: iaccess.h, released November 2002. The original Pascal }
{ code is: IAccess.pas, released March 2002. The initial developer of the      }
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

unit JwaIAccess;

{$WEAKPACKAGEUNIT}

{$HPPEMIT ''}
{$HPPEMIT '#include "iaccess.h"'}
{$HPPEMIT ''}

{$I WINDEFINES.INC}

interface

uses
  JwaAccCtrl, JwaWinType;

{****************************************************************************
 *  Storage access control interface
 ****************************************************************************}

// All nested structures are allocated in the same block of memory.
// Thus these types are freed with a single call to CoTaskMemFree.

type
  PACTRL_ACCESSW_ALLOCATE_ALL_NODES = PACTRL_ACCESSW;
  {$EXTERNALSYM PACTRL_ACCESSW_ALLOCATE_ALL_NODES}
  PActrlAccessWAllocateAllNodes = PACTRL_ACCESSW_ALLOCATE_ALL_NODES;
  PACTRL_AUDITW_ALLOCATE_ALL_NODES = PACTRL_AUDITW;
  {$EXTERNALSYM PACTRL_AUDITW_ALLOCATE_ALL_NODES}
  PActrlAuditWAllocateAllNodes = PACTRL_AUDITW_ALLOCATE_ALL_NODES;

const
  IID_IAccessControl = '{EEDD23E0-8410-11CE-A1C3-08002B2B8D8F}';
  {$EXTERNALSYM IID_IAccessControl}

type
  IAccessControl = interface (IUnknown)
  ['{EEDD23E0-8410-11CE-A1C3-08002B2B8D8F}']
    function GrantAccessRights(pAccessList: PACTRL_ACCESSW): HRESULT; stdcall;
    function SetAccessRights(pAccessList: PACTRL_ACCESSW): HRESULT; stdcall;
    function SetOwner(pOwner: PTRUSTEEW; pGroup: PTRUSTEEW): HRESULT; stdcall;
    function RevokeAccessRights(lpProperty: LPWSTR; cTrustees: ULONG; prgTrustees: PTRUSTEEW): HRESULT; stdcall;
    function GetAllAccessRights(lpProperty: LPWSTR; var ppAccessList: PACTRL_ACCESSW_ALLOCATE_ALL_NODES; var ppOwner, ppGroup: PTRUSTEEW): HRESULT; stdcall;
    function IsAccessAllowed(pTrustee: PTRUSTEEW; lpProperty: LPWSTR; AccessRights: ACCESS_RIGHTS; var pfAccessAllowed: BOOL): HRESULT; stdcall;
  end;
  {$EXTERNALSYM IAccessControl}

{****************************************************************************
 *  Storage audit control interface
 ****************************************************************************}

const
  IID_IAuditControl = '{1da6292f-bc66-11ce-aae3-00aa004c2737}';
  {$EXTERNALSYM IID_IAuditControl}

type
  IAuditControl = interface (IUnknown)
  ['{1da6292f-bc66-11ce-aae3-00aa004c2737}']
    function GrantAuditRights(pAuditList: PACTRL_AUDITW): HRESULT; stdcall;
    function SetAuditRights(pAuditList: PACTRL_AUDITW): HRESULT; stdcall;
    function RevokeAuditRights(lpProperty: LPWSTR; cTrustees: ULONG; prgTrustees: PTRUSTEEW): HRESULT; stdcall;
    function GetAllAuditRights(lpProperty: LPWSTR; var ppAuditList: PACTRL_AUDITW): HRESULT; stdcall;
    //
    // Determines if the given trustee with the state audit rights will generate an audit event if the object is accessed.
    //
    function IsAccessAudited(pTrustee: PTRUSTEEW; AuditRights: ACCESS_RIGHTS; var pfAccessAudited: BOOL): HRESULT; stdcall;
  end;
  {$EXTERNALSYM IAuditControl}

implementation

end.

