{******************************************************************************}
{                                                       	               }
{ Interface Unit for Object Pascal                          }
{                                                       	               }
{ Portions created by Microsoft are Copyright (C) 1995-2003 Microsoft          }
{ Corporation. All Rights Reserved.                                            }
{ 								               }
{ Portions created by Marcel van Brakel are Copyright (C) 2003                 }
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

unit JwaAccCtrl;

{$WEAKPACKAGEUNIT}

{$HPPEMIT ''}
{$HPPEMIT '#include "aclapi.h"'}
{$HPPEMIT ''}
{$HPPEMIT 'typedef PTRUSTEE_A *PPTRUSTEE_A'}
{$HPPEMIT 'typedef PTRUSTEE_W *PPTRUSTEE_W'}
{$HPPEMIT '#ifdef UNICODE'}
{$HPPEMIT 'typedef PPTRUSTEE_W PPTRUSTEE'}
{$HPPEMIT '#else'}
{$HPPEMIT 'typedef PPTRUSTEE_A PPTRUSTEE'}
{$HPPEMIT '#endif'}
{$HPPEMIT ''}

{$I WINDEFINES.INC}

interface

uses
  JwaWinNT, JwaWinType;

(* Dependencies
// winnt
PSID
//wintype
HLOCAL
DWORD
GUID
LPSTR
LPWSTR
ULONG
PVOID
HANDLE
BOOL
LONG
*)

function AccFree(hMem: HLOCAL): HLOCAL;
{$EXTERNALSYM AccFree}

//
// Definition:
// This enumerated type defines the objects supported by the get/set API within
// this document.  See section 3.1, Object Types for a detailed definition of the
// supported object types, and their name formats.
//

type
  _SE_OBJECT_TYPE = (
    SE_UNKNOWN_OBJECT_TYPE,
    SE_FILE_OBJECT,
    SE_SERVICE,
    SE_PRINTER,
    SE_REGISTRY_KEY,
    SE_LMSHARE,
    SE_KERNEL_OBJECT,
    SE_WINDOW_OBJECT,
    SE_DS_OBJECT,
    SE_DS_OBJECT_ALL,
    SE_PROVIDER_DEFINED_OBJECT,
    SE_WMIGUID_OBJECT,
    SE_REGISTRY_WOW64_32KEY);
  {$EXTERNALSYM _SE_OBJECT_TYPE}
  SE_OBJECT_TYPE = _SE_OBJECT_TYPE;
  {$EXTERNALSYM SE_OBJECT_TYPE}
  TSeObjectType = SE_OBJECT_TYPE;

//
// Definition: TRUSTEE_TYPE
// This enumerated type specifies the type of trustee account for the trustee
// returned by the API described in this document.
// TRUSTEE_IS_UNKNOWN - The trustee is an unknown, but not necessarily invalid
//                      type.  This field is not validated on input to the APIs
//                      that take Trustees.
// TRUSTEE_IS_USER      The trustee account is a user account.
// TRUSTEE_IS_GROUP     The trustee account is a group account.
//

  _TRUSTEE_TYPE = (
    TRUSTEE_IS_UNKNOWN,
    TRUSTEE_IS_USER,
    TRUSTEE_IS_GROUP,
    TRUSTEE_IS_DOMAIN,
    TRUSTEE_IS_ALIAS,
    TRUSTEE_IS_WELL_KNOWN_GROUP,
    TRUSTEE_IS_DELETED,
    TRUSTEE_IS_INVALID,
    TRUSTEE_IS_COMPUTER);
  {$EXTERNALSYM _TRUSTEE_TYPE}
  TRUSTEE_TYPE = _TRUSTEE_TYPE;
  {$EXTERNALSYM TRUSTEE_TYPE}
  TTrusteeType = TRUSTEE_TYPE;

//
// Definition: TRUSTEE_FORM
// This enumerated type specifies the form the trustee identifier is in for a
// particular trustee.
// TRUSTEE_IS_SID       The trustee is identified with a SID rather than with a name.
// TRUSTEE_IS_NAME      The trustee is identified with a name.
//

  _TRUSTEE_FORM = (
    TRUSTEE_IS_SID,
    TRUSTEE_IS_NAME,
    TRUSTEE_BAD_FORM,
    TRUSTEE_IS_OBJECTS_AND_SID,
    TRUSTEE_IS_OBJECTS_AND_NAME);
  {$EXTERNALSYM _TRUSTEE_FORM}
  TRUSTEE_FORM = _TRUSTEE_FORM;
  {$EXTERNALSYM TRUSTEE_FORM}
  TTrusteeForm = TRUSTEE_FORM;

//
// Definition: MULTIPLE_TRUSTEE_OPERATION
// If the trustee is a multiple trustee, this enumerated type specifies the type.
// TRUSTEE_IS_IMPERSONATE       The trustee is an impersonate trustee and the multiple
//                          trustee field in the trustee points to another trustee
//                          that is a trustee for the server that will be doing the
//                          impersonation.
//

  _MULTIPLE_TRUSTEE_OPERATION = (NO_MULTIPLE_TRUSTEE, TRUSTEE_IS_IMPERSONATE);
  {$EXTERNALSYM _MULTIPLE_TRUSTEE_OPERATION}
  MULTIPLE_TRUSTEE_OPERATION = _MULTIPLE_TRUSTEE_OPERATION;
  {$EXTERNALSYM MULTIPLE_TRUSTEE_OPERATION}
  TMultipleTrusteeOperation = MULTIPLE_TRUSTEE_OPERATION;

  POBJECTS_AND_SID = ^OBJECTS_AND_SID;
  {$EXTERNALSYM POBJECTS_AND_SID}
  _OBJECTS_AND_SID = packed record
    ObjectsPresent: DWORD;
    ObjectTypeGuid: GUID;
    InheritedObjectTypeGuid: GUID;
    pSid: PSID;
  end;
  {$EXTERNALSYM _OBJECTS_AND_SID}
  OBJECTS_AND_SID = _OBJECTS_AND_SID;
  {$EXTERNALSYM OBJECTS_AND_SID}
  TObjectsAndSid = OBJECTS_AND_SID;
  PObjectsAndSid = POBJECTS_AND_SID;

  POBJECTS_AND_NAME_A = ^OBJECTS_AND_NAME_A;
  {$EXTERNALSYM POBJECTS_AND_NAME_A}
  _OBJECTS_AND_NAME_A = packed record
    ObjectsPresent: DWORD;
    ObjectType: SE_OBJECT_TYPE;
    ObjectTypeName: LPSTR;
    InheritedObjectTypeName: LPSTR;
    ptstrName: LPSTR;
  end;
  {$EXTERNALSYM _OBJECTS_AND_NAME_A}
  OBJECTS_AND_NAME_A = _OBJECTS_AND_NAME_A;
  {$EXTERNALSYM OBJECTS_AND_NAME_A}
  TObjectsAndNameA = OBJECTS_AND_NAME_A;
  PObjectsAndNameA = POBJECTS_AND_NAME_A;

  POBJECTS_AND_NAME_W = ^OBJECTS_AND_NAME_W;
  {$EXTERNALSYM POBJECTS_AND_NAME_W}
  _OBJECTS_AND_NAME_W = packed record
    ObjectsPresent: DWORD;
    ObjectType: SE_OBJECT_TYPE;
    ObjectTypeName: LPWSTR;
    InheritedObjectTypeName: LPWSTR;
    ptstrName: LPWSTR;
  end;
  {$EXTERNALSYM _OBJECTS_AND_NAME_W}
  OBJECTS_AND_NAME_W = _OBJECTS_AND_NAME_W;
  {$EXTERNALSYM OBJECTS_AND_NAME_W}
  TObjectsAndNameW = OBJECTS_AND_NAME_W;
  PObjectsAndNameW = POBJECTS_AND_NAME_W;

{$IFDEF UNICODE}
  OBJECTS_AND_NAME_ = OBJECTS_AND_NAME_W;
  {$EXTERNALSYM OBJECTS_AND_NAME_}
  POBJECTS_AND_NAME_ = POBJECTS_AND_NAME_W;
  {$EXTERNALSYM POBJECTS_AND_NAME_}
  TObjectsAndName = TObjectsAndNameW;
  PObjectsAndName = PObjectsAndNameW;
{$ELSE}
  OBJECTS_AND_NAME_ = OBJECTS_AND_NAME_A;
  {$EXTERNALSYM OBJECTS_AND_NAME_}
  POBJECTS_AND_NAME_ = POBJECTS_AND_NAME_A;
  {$EXTERNALSYM POBJECTS_AND_NAME_}
  TObjectsAndName = TObjectsAndNameA;
  PObjectsAndName = PObjectsAndNameA;
{$ENDIF}

//
// Definition: TRUSTEE
// This structure is used to pass account information into and out of the system
// using the API defined in this document.
// PMultipleTrustee     - if NON-NULL, points to another trustee structure, as
//                    defined by the multiple trustee operation field.
// MultipleTrusteeOperation - Defines the multiple trustee operation/type.
// TrusteeForm - defines if the trustee is defined by name or SID.
// TrusteeType - defines if the trustee type is unknown, a user or a group.
// PwcsName     - points to the trustee name or the trustee SID.
//

  PTRUSTEE_A = ^TRUSTEE_A;
  {$EXTERNALSYM PTRUSTEE_A}
  _TRUSTEE_A = packed record
    pMultipleTrustee: PTRUSTEE_A;
    MultipleTrusteeOperation: MULTIPLE_TRUSTEE_OPERATION;
    TrusteeForm: TRUSTEE_FORM;
    TrusteeType: TRUSTEE_TYPE;
    ptstrName: LPSTR;
  end;
  {$EXTERNALSYM _TRUSTEE_A}
  TRUSTEE_A = _TRUSTEE_A;
  {$EXTERNALSYM TRUSTEE_A}
  TRUSTEEA = TRUSTEE_A;
  {$EXTERNALSYM PTRUSTEEA}
  PPTRUSTEE_A = ^PTRUSTEE_A;
  {$NODEFINE PPTRUSTEE_A}
  TTrusteeA = TRUSTEE_A;
  PTrusteeA = PTRUSTEE_A;

  PTRUSTEE_W = ^TRUSTEE_W;
  {$EXTERNALSYM PTRUSTEE_W}
  _TRUSTEE_W = packed record
    pMultipleTrustee: PTRUSTEE_W;
    MultipleTrusteeOperation: MULTIPLE_TRUSTEE_OPERATION;
    TrusteeForm: TRUSTEE_FORM;
    TrusteeType: TRUSTEE_TYPE;
    ptstrName: LPWSTR;
  end;
  {$EXTERNALSYM _TRUSTEE_W}
  TRUSTEE_W = _TRUSTEE_W;
  {$EXTERNALSYM TRUSTEE_W}
  TRUSTEEW = TRUSTEE_W;
  {$EXTERNALSYM TRUSTEEW}
  PPTRUSTEE_W = ^PTRUSTEE_W;
  {$NODEFINE PPTRUSTEE_W}
  TTrusteeW = TRUSTEE_W;
  PTrusteeW = PTRUSTEE_W;

{$IFDEF UNICODE}
  TRUSTEE_ = TRUSTEE_W;
  {$EXTERNALSYM TRUSTEE_}
  PTRUSTEE_ = PTRUSTEE_W;
  {$EXTERNALSYM PTRUSTEE_}
  TRUSTEE = TRUSTEEW;
  {$EXTERNALSYM TRUSTEE}
  PPTRUSTEE = ^PPTRUSTEE_W;
  {$NODEFINE PPTRUSTEE}
  TTrustee = TTrusteeW;
  PTrustee = PTrusteeW;
{$ELSE}
  TRUSTEE_ = TRUSTEE_A;
  {$EXTERNALSYM TRUSTEE_}
  PTRUSTEE_ = PTRUSTEE_A;
  {$EXTERNALSYM PTRUSTEE_}
  TRUSTEE = TRUSTEEA;
  {$EXTERNALSYM TRUSTEE}
  PPTRUSTEE = ^PPTRUSTEE_A;
  {$NODEFINE PPTRUSTEE}
  TTrustee = TTrusteeA;
  PTrustee = PTrusteeA;
{$ENDIF}

//
// Definition: ACCESS_MODE
// This enumerated type specifies how permissions are (requested)/to be applied
//  for the trustee by the access control entry.  On input this field can by any
//  of the values, although it is not meaningful to mix access control and audit
//  control entries.  On output this field will be either SET_ACCESS, DENY_ACCESS,
// SET_AUDIT_SUCCESS, SET_AUDIT_FAILURE.
// The following descriptions define how this type effects an explicit access
// request to apply access permissions to an object.
// GRANT_ACCESS - The trustee will have at least the requested permissions upon
//                successful completion of the command. (If the trustee has
//                additional permissions they will not be removed).
// SET_ACCESS - The trustee will have exactly the requested permissions upon
//              successful completion of the command.
// DENY_ACCESS - The trustee will be denied the specified permissions.
// REVOKE_ACCESS - Any explicit access rights the trustee has will be revoked.
// SET_AUDIT_SUCCESS - The trustee will be audited for successful opens of the
//                     object using the requested permissions.
// SET_AUDIT_FAILURE - The trustee will be audited for failed opens of the object
//                     using the requested permissions.
//

  _ACCESS_MODE = (
    NOT_USED_ACCESS,
    GRANT_ACCESS,
    SET_ACCESS,
    DENY_ACCESS,
    REVOKE_ACCESS,
    SET_AUDIT_SUCCESS,
    SET_AUDIT_FAILURE);
  {$EXTERNALSYM _ACCESS_MODE}
  ACCESS_MODE = _ACCESS_MODE;
  {$EXTERNALSYM ACCESS_MODE}
  TAccessMode = _ACCESS_MODE;

//
// Definition: Inheritance flags
// These bit masks are provided to allow simple application of inheritance in
// explicit access requests on containers.
// NO_INHERITANCE       The specific access permissions will only be applied to
//                  the container, and will not be inherited by objects created
//                  within the container.
// SUB_CONTAINERS_ONLY_INHERIT  The specific access permissions will be inherited
//                              and applied to sub containers created within the
//                              container, and will be applied to the container
//                              itself.
// SUB_OBJECTS_ONLY_INHERIT     The specific access permissions will only be inherited
//                              by objects created within the specific container.
//                              The access permissions will not be applied to the
//                              container itself.
// SUB_CONTAINERS_AND_OBJECTS_INHERIT   The specific access permissions will be
//                                      inherited by containers created within the
//                                      specific container, will be applied to
//                                      objects created within the container, but
//                                      will not be applied to the container itself.
//

const
  NO_INHERITANCE                     = $0;
  {$EXTERNALSYM NO_INHERITANCE}
  SUB_OBJECTS_ONLY_INHERIT           = $1;
  {$EXTERNALSYM SUB_OBJECTS_ONLY_INHERIT}
  SUB_CONTAINERS_ONLY_INHERIT        = $2;
  {$EXTERNALSYM SUB_CONTAINERS_ONLY_INHERIT}
  SUB_CONTAINERS_AND_OBJECTS_INHERIT = $3;
  {$EXTERNALSYM SUB_CONTAINERS_AND_OBJECTS_INHERIT}
  INHERIT_NO_PROPAGATE               = $4;
  {$EXTERNALSYM INHERIT_NO_PROPAGATE}
  INHERIT_ONLY                       = $8;
  {$EXTERNALSYM INHERIT_ONLY}

//
// Informational bit that is returned
//

  INHERITED_ACCESS_ENTRY = $10;
  {$EXTERNALSYM INHERITED_ACCESS_ENTRY}

//
// Informational bit that tells where a node was inherited from.  Valid only
// for NT 5 APIs
//

  INHERITED_PARENT      = $10000000;
  {$EXTERNALSYM INHERITED_PARENT}
  INHERITED_GRANDPARENT = $20000000;
  {$EXTERNALSYM INHERITED_GRANDPARENT}

//
// Definition: EXPLICIT_ACCESS
// This structure is used to pass access control entry information into and out
// of the system using the API defined in this document.
// grfAccessPermissions - This contains the access permissions to assign for the
//                     trustee.  It is in the form of an NT access mask.
// grfAccessMode - This field defines how the permissions are to be applied for
//                 the trustee.
// grfInheritance - For containers, this field defines how the access control
//                  entry is/(is requested) to be inherited on
//                  objects/sub-containers created within the container.
// Trustee - This field contains the definition of the trustee account the
//           explicit access applies to.
//

type
  PEXPLICIT_ACCESS_A = ^EXPLICIT_ACCESS_A;
  {$EXTERNALSYM PEXPLICIT_ACCESS_A}
  _EXPLICIT_ACCESS_A = packed record
    grfAccessPermissions: DWORD;
    grfAccessMode: ACCESS_MODE;
    grfInheritance: DWORD;
    Trustee: TRUSTEE_A;
  end;
  {$EXTERNALSYM _EXPLICIT_ACCESS_A}
  EXPLICIT_ACCESS_A = _EXPLICIT_ACCESS_A;
  {$EXTERNALSYM EXPLICIT_ACCESS_A}
  EXPLICIT_ACCESSA = EXPLICIT_ACCESS_A;
  {$EXTERNALSYM EXPLICIT_ACCESSA}
  PEXPLICIT_ACCESSA = PEXPLICIT_ACCESS_A;
  {$EXTERNALSYM PEXPLICIT_ACCESSA}
  TExplicitAccessA = EXPLICIT_ACCESS_A;
  PExplicitAccessA = PEXPLICIT_ACCESS_A;

  PEXPLICIT_ACCESS_W = ^EXPLICIT_ACCESS_W;
  {$EXTERNALSYM PEXPLICIT_ACCESS_W}
  _EXPLICIT_ACCESS_W = packed record
    grfAccessPermissions: DWORD;
    grfAccessMode: ACCESS_MODE;
    grfInheritance: DWORD;
    Trustee: TRUSTEE_W;
  end;
  {$EXTERNALSYM _EXPLICIT_ACCESS_W}
  EXPLICIT_ACCESS_W = _EXPLICIT_ACCESS_W;
  {$EXTERNALSYM EXPLICIT_ACCESS_W}
  EXPLICIT_ACCESSW = EXPLICIT_ACCESS_W;
  {$EXTERNALSYM EXPLICIT_ACCESSW}
  PEXPLICIT_ACCESSW = PEXPLICIT_ACCESS_W;
  {$EXTERNALSYM PEXPLICIT_ACCESSW}
  TExplicitAccessW = EXPLICIT_ACCESS_W;
  PExplicitAccessW = PEXPLICIT_ACCESS_W;

{$IFDEF UNICODE}
  EXPLICIT_ACCESS_ = EXPLICIT_ACCESS_W;
  {$EXTERNALSYM EXPLICIT_ACCESS_}
  PEXPLICIT_ACCESS_ = PEXPLICIT_ACCESS_W;
  {$EXTERNALSYM PEXPLICIT_ACCESS_}
  EXPLICIT_ACCESS = EXPLICIT_ACCESSW;
  {$EXTERNALSYM EXPLICIT_ACCESS}
  PEXPLICIT_ACCESS = PEXPLICIT_ACCESSW;
  {$EXTERNALSYM PEXPLICIT_ACCESS}
  TExplicitAccess = TExplicitAccessW;
  PExplicitAccess = PExplicitAccessW;
{$ELSE}
  EXPLICIT_ACCESS_ = EXPLICIT_ACCESS_A;
  {$EXTERNALSYM EXPLICIT_ACCESS_}
  PEXPLICIT_ACCESS_ = PEXPLICIT_ACCESS_A;
  {$EXTERNALSYM PEXPLICIT_ACCESS_}
  EXPLICIT_ACCESS = EXPLICIT_ACCESSA;
  {$EXTERNALSYM EXPLICIT_ACCESS}
  PEXPLICIT_ACCESS = PEXPLICIT_ACCESSA;
  {$EXTERNALSYM PEXPLICIT_ACCESS}
  TExplicitAccess = TExplicitAccessA;
  PExplicitAccess = PExplicitAccessA;
{$ENDIF}

//------------------------------------------------------------------------------
//                              NT5 APIs
//------------------------------------------------------------------------------

//
// Default provider
//

const
  ACCCTRL_DEFAULT_PROVIDERA = 'Windows NT Access Provider';
  {$EXTERNALSYM ACCCTRL_DEFAULT_PROVIDERA}
  ACCCTRL_DEFAULT_PROVIDERW = 'Windows NT Access Provider';
  {$EXTERNALSYM ACCCTRL_DEFAULT_PROVIDERW}

{$IFDEF UNICODE}
  ACCCTRL_DEFAULT_PROVIDER = ACCCTRL_DEFAULT_PROVIDERW;
  {$EXTERNALSYM ACCCTRL_DEFAULT_PROVIDER}
{$ELSE}
  ACCCTRL_DEFAULT_PROVIDER = ACCCTRL_DEFAULT_PROVIDERA;
  {$EXTERNALSYM ACCCTRL_DEFAULT_PROVIDER}
{$ENDIF}

//
// Access rights
//

type
  ACCESS_RIGHTS = ULONG;
  {$EXTERNALSYM ACCESS_RIGHTS}
  PACCESS_RIGHTS = ^ACCESS_RIGHTS;
  {$EXTERNALSYM PACCESS_RIGHTS}

//
// Inheritance flags
//

  INHERIT_FLAGS = ULONG;
  {$EXTERNALSYM INHERIT_FLAGS}
  PINHERIT_FLAGS = ^INHERIT_FLAGS;
  {$EXTERNALSYM PINHERIT_FLAGS}

//
// Access / Audit structures
//

  PACTRL_ACCESS_ENTRYA = ^ACTRL_ACCESS_ENTRYA;
  {$EXTERNALSYM PACTRL_ACCESS_ENTRYA}
  _ACTRL_ACCESS_ENTRYA = packed record
    Trustee: TRUSTEE_A;
    fAccessFlags: ULONG;
    Access: ACCESS_RIGHTS;
    ProvSpecificAccess: ACCESS_RIGHTS;
    Inheritance: INHERIT_FLAGS;
    lpInheritProperty: LPSTR;
  end;
  {$EXTERNALSYM _ACTRL_ACCESS_ENTRYA}
  ACTRL_ACCESS_ENTRYA = _ACTRL_ACCESS_ENTRYA;
  {$EXTERNALSYM ACTRL_ACCESS_ENTRYA}
  TActrlAccessEntryA = ACTRL_ACCESS_ENTRYA;
  PActrlAccessEntryA = PACTRL_ACCESS_ENTRYA;

//
// Access / Audit structures
//

  PACTRL_ACCESS_ENTRYW = ^ACTRL_ACCESS_ENTRYW;
  {$EXTERNALSYM PACTRL_ACCESS_ENTRYW}
  _ACTRL_ACCESS_ENTRYW = packed record
    Trustee: TRUSTEE_W;
    fAccessFlags: ULONG;
    Access: ACCESS_RIGHTS;
    ProvSpecificAccess: ACCESS_RIGHTS;
    Inheritance: INHERIT_FLAGS;
    lpInheritProperty: LPWSTR;
  end;
  {$EXTERNALSYM _ACTRL_ACCESS_ENTRYW}
  ACTRL_ACCESS_ENTRYW = _ACTRL_ACCESS_ENTRYW;
  {$EXTERNALSYM ACTRL_ACCESS_ENTRYW}
  TActrlAccessEntryW = ACTRL_ACCESS_ENTRYW;
  PActrlAccessEntryW = PACTRL_ACCESS_ENTRYW;

{$IFDEF UNICODE}
  ACTRL_ACCESS_ENTRY = ACTRL_ACCESS_ENTRYW;
  {$EXTERNALSYM ACTRL_ACCESS_ENTRY}
  PACTRL_ACCESS_ENTRY = PACTRL_ACCESS_ENTRYW;
  {$EXTERNALSYM PACTRL_ACCESS_ENTRY}
  TActrlAccessEntry = TActrlAccessEntryW;
  PActrlAccessEntry = PActrlAccessEntryW;
{$ELSE}
  ACTRL_ACCESS_ENTRY = ACTRL_ACCESS_ENTRYA;
  {$EXTERNALSYM ACTRL_ACCESS_ENTRY}
  PACTRL_ACCESS_ENTRY = PACTRL_ACCESS_ENTRYA;
  {$EXTERNALSYM PACTRL_ACCESS_ENTRY}
  TActrlAccessEntry = TActrlAccessEntryA;
  PActrlAccessEntry = PActrlAccessEntryA;
{$ENDIF}

  PACTRL_ACCESS_ENTRY_LISTA = ^ACTRL_ACCESS_ENTRY_LISTA;
  {$EXTERNALSYM PACTRL_ACCESS_ENTRY_LISTA}
  _ACTRL_ACCESS_ENTRY_LISTA = packed record
    cEntries: ULONG;
    pAccessList: PACTRL_ACCESS_ENTRYA;
  end;
  {$EXTERNALSYM _ACTRL_ACCESS_ENTRY_LISTA}
  ACTRL_ACCESS_ENTRY_LISTA = _ACTRL_ACCESS_ENTRY_LISTA;
  {$EXTERNALSYM ACTRL_ACCESS_ENTRY_LISTA}
  TActrlAccessEntryListA = ACTRL_ACCESS_ENTRY_LISTA;
  PActrlAccessEntryListA = PACTRL_ACCESS_ENTRY_LISTA;

  PACTRL_ACCESS_ENTRY_LISTW = ^ACTRL_ACCESS_ENTRY_LISTW;
  {$EXTERNALSYM PACTRL_ACCESS_ENTRY_LISTW}
  _ACTRL_ACCESS_ENTRY_LISTW = packed record
    cEntries: ULONG;
    pAccessList: PACTRL_ACCESS_ENTRYW;
  end;
  {$EXTERNALSYM _ACTRL_ACCESS_ENTRY_LISTW}
  ACTRL_ACCESS_ENTRY_LISTW = _ACTRL_ACCESS_ENTRY_LISTW;
  {$EXTERNALSYM ACTRL_ACCESS_ENTRY_LISTW}
  TActrlAccessEntryListW = ACTRL_ACCESS_ENTRY_LISTW;
  PActrlAccessEntryListW = PACTRL_ACCESS_ENTRY_LISTW;

{$IFDEF UNICODE}
  ACTRL_ACCESS_ENTRY_LIST = ACTRL_ACCESS_ENTRY_LISTW;
  {$EXTERNALSYM ACTRL_ACCESS_ENTRY_LIST}
  PACTRL_ACCESS_ENTRY_LIST = PACTRL_ACCESS_ENTRY_LISTW;
  {$EXTERNALSYM PACTRL_ACCESS_ENTRY_LIST}
  TActrlAccessEntryList = TActrlAccessEntryListW;
  PActrlAccessEntryList = PActrlAccessEntryListW;
{$ELSE}
  ACTRL_ACCESS_ENTRY_LIST = ACTRL_ACCESS_ENTRY_LISTA;
  {$EXTERNALSYM ACTRL_ACCESS_ENTRY_LIST}
  PACTRL_ACCESS_ENTRY_LIST = PACTRL_ACCESS_ENTRY_LISTA;
  {$EXTERNALSYM PACTRL_ACCESS_ENTRY_LIST}
  TActrlAccessEntryList = TActrlAccessEntryListA;
  PActrlAccessEntryList = PActrlAccessEntryListA;
{$ENDIF}

  PACTRL_PROPERTY_ENTRYA = ^ACTRL_PROPERTY_ENTRYA;
  {$EXTERNALSYM PACTRL_PROPERTY_ENTRYA}
  _ACTRL_PROPERTY_ENTRYA = packed record
    lpProperty: LPSTR;
    pAccessEntryList: PACTRL_ACCESS_ENTRY_LISTA;
    fListFlags: ULONG;
  end;
  {$EXTERNALSYM _ACTRL_PROPERTY_ENTRYA}
  ACTRL_PROPERTY_ENTRYA = _ACTRL_PROPERTY_ENTRYA;
  {$EXTERNALSYM ACTRL_PROPERTY_ENTRYA}
  TActrlPropertyEntryA = ACTRL_PROPERTY_ENTRYA;
  PActrlPropertyEntryA = PACTRL_PROPERTY_ENTRYA;

  PACTRL_PROPERTY_ENTRYW = ^ACTRL_PROPERTY_ENTRYW;
  {$EXTERNALSYM PACTRL_PROPERTY_ENTRYW}
  _ACTRL_PROPERTY_ENTRYW = packed record
    lpProperty: LPWSTR;
    pAccessEntryList: PACTRL_ACCESS_ENTRY_LISTW;
    fListFlags: ULONG;
  end;
  {$EXTERNALSYM _ACTRL_PROPERTY_ENTRYW}
  ACTRL_PROPERTY_ENTRYW = _ACTRL_PROPERTY_ENTRYW;
  {$EXTERNALSYM ACTRL_PROPERTY_ENTRYW}
  TActrlPropertyEntryW = ACTRL_PROPERTY_ENTRYW;
  PActrlPropertyEntryW = PACTRL_PROPERTY_ENTRYW;

{$IFDEF UNICODE}
  ACTRL_PROPERTY_ENTRY = ACTRL_PROPERTY_ENTRYW;
  {$EXTERNALSYM ACTRL_PROPERTY_ENTRY}
  PACTRL_PROPERTY_ENTRY = PACTRL_PROPERTY_ENTRYW;
  {$EXTERNALSYM PACTRL_PROPERTY_ENTRY}
  TActrlPropertyEntry = TActrlPropertyEntryW;
  PActrlPropertyEntry = PActrlPropertyEntryW;
{$ELSE}
  ACTRL_PROPERTY_ENTRY = ACTRL_PROPERTY_ENTRYA;
  {$EXTERNALSYM ACTRL_PROPERTY_ENTRY}
  PACTRL_PROPERTY_ENTRY = PACTRL_PROPERTY_ENTRYA;
  {$EXTERNALSYM PACTRL_PROPERTY_ENTRY}
  TActrlPropertyEntry = TActrlPropertyEntryA;
  PActrlPropertyEntry = PActrlPropertyEntryA;
{$ENDIF}

  PActrlAlistA = ^TActrlAlistA;
  _ACTRL_ALISTA = packed record
    cEntries: ULONG;
    pPropertyAccessList: PACTRL_PROPERTY_ENTRYA;
  end;
  {$EXTERNALSYM _ACTRL_ALISTA}
  ACTRL_ACCESSA = _ACTRL_ALISTA;
  {$EXTERNALSYM ACTRL_ACCESSA}
  PACTRL_ACCESSA = ^_ACTRL_ALISTA;
  {$EXTERNALSYM PACTRL_ACCESSA}
  ACTRL_AUDITA = ACTRL_ACCESSA;
  {$EXTERNALSYM ACTRL_AUDITA}
  PACTRL_AUDITA = ^ACTRL_AUDITA;
  {$EXTERNALSYM PACTRL_AUDITA}
  TActrlAlistA = _ACTRL_ALISTA;

  PActrlAlistW = ^TActrlAlistW;
  _ACTRL_ALISTW = packed record
    cEntries: ULONG;
    pPropertyAccessList: PACTRL_PROPERTY_ENTRYW;
  end;
  {$EXTERNALSYM _ACTRL_ALISTW}
  ACTRL_ACCESSW = _ACTRL_ALISTW;
  {$EXTERNALSYM ACTRL_ACCESSW}
  PACTRL_ACCESSW = ^_ACTRL_ALISTW;
  {$EXTERNALSYM PACTRL_ACCESSW}
  ACTRL_AUDITW = ACTRL_ACCESSW;
  {$EXTERNALSYM ACTRL_AUDITW}
  PACTRL_AUDITW = ^ACTRL_AUDITW;
  {$EXTERNALSYM PACTRL_AUDITW}
  TActrlAlistW = _ACTRL_ALISTW;

{$IFDEF UNICODE}
  ACTRL_ACCESS = ACTRL_ACCESSW;
  {$EXTERNALSYM ACTRL_ACCESS}
  PACTRL_ACCESS = PACTRL_ACCESSW;
  {$EXTERNALSYM PACTRL_ACCESS}
  ACTRL_AUDIT = ACTRL_AUDITW;
  {$EXTERNALSYM ACTRL_AUDIT}
  PACTRL_AUDIT = PACTRL_AUDITW;
  {$EXTERNALSYM PACTRL_AUDIT}
  TActrlAlist = TActrlAlistW;
  PActrlAlist = PActrlAlistW;
{$ELSE}
  ACTRL_ACCESS = ACTRL_ACCESSA;
  {$EXTERNALSYM ACTRL_ACCESS}
  PACTRL_ACCESS = PACTRL_ACCESSA;
  {$EXTERNALSYM PACTRL_ACCESS}
  ACTRL_AUDIT = ACTRL_AUDITA;
  {$EXTERNALSYM ACTRL_AUDIT}
  PACTRL_AUDIT = PACTRL_AUDITA;
  {$EXTERNALSYM PACTRL_AUDIT}
  TActrlAlist = TActrlAlistA;
  PActrlAlist = PActrlAlistA;
{$ENDIF}

//
// TRUSTEE_ACCESS flags
//

const
  TRUSTEE_ACCESS_ALLOWED    = $00000001;
  {$EXTERNALSYM TRUSTEE_ACCESS_ALLOWED}
  TRUSTEE_ACCESS_READ       = $00000002;
  {$EXTERNALSYM TRUSTEE_ACCESS_READ}
  TRUSTEE_ACCESS_WRITE      = $00000004;
  {$EXTERNALSYM TRUSTEE_ACCESS_WRITE}

  TRUSTEE_ACCESS_EXPLICIT   = $00000001;
  {$EXTERNALSYM TRUSTEE_ACCESS_EXPLICIT}
  TRUSTEE_ACCESS_READ_WRITE = TRUSTEE_ACCESS_READ or TRUSTEE_ACCESS_WRITE;
  {$EXTERNALSYM TRUSTEE_ACCESS_READ_WRITE}

  TRUSTEE_ACCESS_ALL = DWORD($FFFFFFFF);
  {$EXTERNALSYM TRUSTEE_ACCESS_ALL}

type
  PTRUSTEE_ACCESSA = ^TRUSTEE_ACCESSA;
  {$EXTERNALSYM PTRUSTEE_ACCESSA}
  _TRUSTEE_ACCESSA = packed record
    lpProperty: LPSTR;
    Access: ACCESS_RIGHTS;
    fAccessFlags: ULONG;
    fReturnedAccess: ULONG;
  end;
  {$EXTERNALSYM _TRUSTEE_ACCESSA}
  TRUSTEE_ACCESSA = _TRUSTEE_ACCESSA;
  {$EXTERNALSYM TRUSTEE_ACCESSA}
  TTrusteeAccessA = TRUSTEE_ACCESSA;
  PTrusteeAccessA = PTRUSTEE_ACCESSA;

  PTRUSTEE_ACCESSW = ^TRUSTEE_ACCESSW;
  {$EXTERNALSYM PTRUSTEE_ACCESSW}
  _TRUSTEE_ACCESSW = packed record
    lpProperty: LPWSTR;
    Access: ACCESS_RIGHTS;
    fAccessFlags: ULONG;
    fReturnedAccess: ULONG;
  end;
  {$EXTERNALSYM _TRUSTEE_ACCESSW}
  TRUSTEE_ACCESSW = _TRUSTEE_ACCESSW;
  {$EXTERNALSYM TRUSTEE_ACCESSW}
  TTrusteeAccessW = TRUSTEE_ACCESSW;
  PTrusteeAccessW = PTRUSTEE_ACCESSW;

{$IFDEF UNICODE}
  TRUSTEE_ACCESS = TRUSTEE_ACCESSW;
  {$EXTERNALSYM TRUSTEE_ACCESS}
  PTRUSTEE_ACCESS = PTRUSTEE_ACCESSW;
  {$EXTERNALSYM PTRUSTEE_ACCESS}
  TTrusteeAccess = TTrusteeAccessW;
  PTrusteeAccess = PTrusteeAccessW;
{$ELSE}
  TRUSTEE_ACCESS = TRUSTEE_ACCESSA;
  {$EXTERNALSYM TRUSTEE_ACCESS}
  PTRUSTEE_ACCESS = PTRUSTEE_ACCESSA;
  {$EXTERNALSYM PTRUSTEE_ACCESS}
  TTrusteeAccess = TTrusteeAccessA;
  PTrusteeAccess = PTrusteeAccessA;
{$ENDIF}

//
// Generic permission values
//

const
  ACTRL_RESERVED = $00000000;
  {$EXTERNALSYM ACTRL_RESERVED}
  ACTRL_PERM_1   = $00000001;
  {$EXTERNALSYM ACTRL_PERM_1}
  ACTRL_PERM_2   = $00000002;
  {$EXTERNALSYM ACTRL_PERM_2}
  ACTRL_PERM_3   = $00000004;
  {$EXTERNALSYM ACTRL_PERM_3}
  ACTRL_PERM_4   = $00000008;
  {$EXTERNALSYM ACTRL_PERM_4}
  ACTRL_PERM_5   = $00000010;
  {$EXTERNALSYM ACTRL_PERM_5}
  ACTRL_PERM_6   = $00000020;
  {$EXTERNALSYM ACTRL_PERM_6}
  ACTRL_PERM_7   = $00000040;
  {$EXTERNALSYM ACTRL_PERM_7}
  ACTRL_PERM_8   = $00000080;
  {$EXTERNALSYM ACTRL_PERM_8}
  ACTRL_PERM_9   = $00000100;
  {$EXTERNALSYM ACTRL_PERM_9}
  ACTRL_PERM_10  = $00000200;
  {$EXTERNALSYM ACTRL_PERM_10}
  ACTRL_PERM_11  = $00000400;
  {$EXTERNALSYM ACTRL_PERM_11}
  ACTRL_PERM_12  = $00000800;
  {$EXTERNALSYM ACTRL_PERM_12}
  ACTRL_PERM_13  = $00001000;
  {$EXTERNALSYM ACTRL_PERM_13}
  ACTRL_PERM_14  = $00002000;
  {$EXTERNALSYM ACTRL_PERM_14}
  ACTRL_PERM_15  = $00004000;
  {$EXTERNALSYM ACTRL_PERM_15}
  ACTRL_PERM_16  = $00008000;
  {$EXTERNALSYM ACTRL_PERM_16}
  ACTRL_PERM_17  = $00010000;
  {$EXTERNALSYM ACTRL_PERM_17}
  ACTRL_PERM_18  = $00020000;
  {$EXTERNALSYM ACTRL_PERM_18}
  ACTRL_PERM_19  = $00040000;
  {$EXTERNALSYM ACTRL_PERM_19}
  ACTRL_PERM_20  = $00080000;
  {$EXTERNALSYM ACTRL_PERM_20}

//
// Access permissions
//

  ACTRL_ACCESS_ALLOWED = $00000001;
  {$EXTERNALSYM ACTRL_ACCESS_ALLOWED}
  ACTRL_ACCESS_DENIED  = $00000002;
  {$EXTERNALSYM ACTRL_ACCESS_DENIED}
  ACTRL_AUDIT_SUCCESS  = $00000004;
  {$EXTERNALSYM ACTRL_AUDIT_SUCCESS}
  ACTRL_AUDIT_FAILURE  = $00000008;
  {$EXTERNALSYM ACTRL_AUDIT_FAILURE}

//
// Property list flags
//

  ACTRL_ACCESS_PROTECTED = $00000001;
  {$EXTERNALSYM ACTRL_ACCESS_PROTECTED}

//
// Standard and object rights
//

  ACTRL_SYSTEM_ACCESS      = $04000000;
  {$EXTERNALSYM ACTRL_SYSTEM_ACCESS}
  ACTRL_DELETE             = $08000000;
  {$EXTERNALSYM ACTRL_DELETE}
  ACTRL_READ_CONTROL       = $10000000;
  {$EXTERNALSYM ACTRL_READ_CONTROL}
  ACTRL_CHANGE_ACCESS      = $20000000;
  {$EXTERNALSYM ACTRL_CHANGE_ACCESS}
  ACTRL_CHANGE_OWNER       = $40000000;
  {$EXTERNALSYM ACTRL_CHANGE_OWNER}
  ACTRL_SYNCHRONIZE        = DWORD($80000000);
  {$EXTERNALSYM ACTRL_SYNCHRONIZE}
  ACTRL_STD_RIGHTS_ALL     = DWORD($f8000000);
  {$EXTERNALSYM ACTRL_STD_RIGHTS_ALL}
  ACTRL_STD_RIGHT_REQUIRED = DWORD(ACTRL_STD_RIGHTS_ALL and not ACTRL_SYNCHRONIZE);
  {$EXTERNALSYM ACTRL_STD_RIGHT_REQUIRED}

  ACTRL_DS_OPEN           = ACTRL_RESERVED;
  {$EXTERNALSYM ACTRL_DS_OPEN}
  ACTRL_DS_CREATE_CHILD   = ACTRL_PERM_1;
  {$EXTERNALSYM ACTRL_DS_CREATE_CHILD}
  ACTRL_DS_DELETE_CHILD   = ACTRL_PERM_2;
  {$EXTERNALSYM ACTRL_DS_DELETE_CHILD}
  ACTRL_DS_LIST           = ACTRL_PERM_3;
  {$EXTERNALSYM ACTRL_DS_LIST}
  ACTRL_DS_SELF           = ACTRL_PERM_4;
  {$EXTERNALSYM ACTRL_DS_SELF}
  ACTRL_DS_READ_PROP      = ACTRL_PERM_5;
  {$EXTERNALSYM ACTRL_DS_READ_PROP}
  ACTRL_DS_WRITE_PROP     = ACTRL_PERM_6;
  {$EXTERNALSYM ACTRL_DS_WRITE_PROP}
  ACTRL_DS_DELETE_TREE    = ACTRL_PERM_7;
  {$EXTERNALSYM ACTRL_DS_DELETE_TREE}
  ACTRL_DS_LIST_OBJECT    = ACTRL_PERM_8;
  {$EXTERNALSYM ACTRL_DS_LIST_OBJECT}
  ACTRL_DS_CONTROL_ACCESS = ACTRL_PERM_9;
  {$EXTERNALSYM ACTRL_DS_CONTROL_ACCESS}

  ACTRL_FILE_READ           = ACTRL_PERM_1;
  {$EXTERNALSYM ACTRL_FILE_READ}
  ACTRL_FILE_WRITE          = ACTRL_PERM_2;
  {$EXTERNALSYM ACTRL_FILE_WRITE}
  ACTRL_FILE_APPEND         = ACTRL_PERM_3;
  {$EXTERNALSYM ACTRL_FILE_APPEND}
  ACTRL_FILE_READ_PROP      = ACTRL_PERM_4;
  {$EXTERNALSYM ACTRL_FILE_READ_PROP}
  ACTRL_FILE_WRITE_PROP     = ACTRL_PERM_5;
  {$EXTERNALSYM ACTRL_FILE_WRITE_PROP}
  ACTRL_FILE_EXECUTE        = ACTRL_PERM_6;
  {$EXTERNALSYM ACTRL_FILE_EXECUTE}
  ACTRL_FILE_READ_ATTRIB    = ACTRL_PERM_8;
  {$EXTERNALSYM ACTRL_FILE_READ_ATTRIB}
  ACTRL_FILE_WRITE_ATTRIB   = ACTRL_PERM_9;
  {$EXTERNALSYM ACTRL_FILE_WRITE_ATTRIB}
  ACTRL_FILE_CREATE_PIPE    = ACTRL_PERM_10;
  {$EXTERNALSYM ACTRL_FILE_CREATE_PIPE}
  ACTRL_DIR_LIST            = ACTRL_PERM_1;
  {$EXTERNALSYM ACTRL_DIR_LIST}
  ACTRL_DIR_CREATE_OBJECT   = ACTRL_PERM_2;
  {$EXTERNALSYM ACTRL_DIR_CREATE_OBJECT}
  ACTRL_DIR_CREATE_CHILD    = ACTRL_PERM_3;
  {$EXTERNALSYM ACTRL_DIR_CREATE_CHILD}
  ACTRL_DIR_DELETE_CHILD    = ACTRL_PERM_7;
  {$EXTERNALSYM ACTRL_DIR_DELETE_CHILD}
  ACTRL_DIR_TRAVERSE        = ACTRL_PERM_6;
  {$EXTERNALSYM ACTRL_DIR_TRAVERSE}
  ACTRL_KERNEL_TERMINATE    = ACTRL_PERM_1;
  {$EXTERNALSYM ACTRL_KERNEL_TERMINATE}
  ACTRL_KERNEL_THREAD       = ACTRL_PERM_2;
  {$EXTERNALSYM ACTRL_KERNEL_THREAD}
  ACTRL_KERNEL_VM           = ACTRL_PERM_3;
  {$EXTERNALSYM ACTRL_KERNEL_VM}
  ACTRL_KERNEL_VM_READ      = ACTRL_PERM_4;
  {$EXTERNALSYM ACTRL_KERNEL_VM_READ}
  ACTRL_KERNEL_VM_WRITE     = ACTRL_PERM_5;
  {$EXTERNALSYM ACTRL_KERNEL_VM_WRITE}
  ACTRL_KERNEL_DUP_HANDLE   = ACTRL_PERM_6;
  {$EXTERNALSYM ACTRL_KERNEL_DUP_HANDLE}
  ACTRL_KERNEL_PROCESS      = ACTRL_PERM_7;
  {$EXTERNALSYM ACTRL_KERNEL_PROCESS}
  ACTRL_KERNEL_SET_INFO     = ACTRL_PERM_8;
  {$EXTERNALSYM ACTRL_KERNEL_SET_INFO}
  ACTRL_KERNEL_GET_INFO     = ACTRL_PERM_9;
  {$EXTERNALSYM ACTRL_KERNEL_GET_INFO}
  ACTRL_KERNEL_CONTROL      = ACTRL_PERM_10;
  {$EXTERNALSYM ACTRL_KERNEL_CONTROL}
  ACTRL_KERNEL_ALERT        = ACTRL_PERM_11;
  {$EXTERNALSYM ACTRL_KERNEL_ALERT}
  ACTRL_KERNEL_GET_CONTEXT  = ACTRL_PERM_12;
  {$EXTERNALSYM ACTRL_KERNEL_GET_CONTEXT}
  ACTRL_KERNEL_SET_CONTEXT  = ACTRL_PERM_13;
  {$EXTERNALSYM ACTRL_KERNEL_SET_CONTEXT}
  ACTRL_KERNEL_TOKEN        = ACTRL_PERM_14;
  {$EXTERNALSYM ACTRL_KERNEL_TOKEN}
  ACTRL_KERNEL_IMPERSONATE  = ACTRL_PERM_15;
  {$EXTERNALSYM ACTRL_KERNEL_IMPERSONATE}
  ACTRL_KERNEL_DIMPERSONATE = ACTRL_PERM_16;
  {$EXTERNALSYM ACTRL_KERNEL_DIMPERSONATE}
  ACTRL_PRINT_SADMIN        = ACTRL_PERM_1;
  {$EXTERNALSYM ACTRL_PRINT_SADMIN}
  ACTRL_PRINT_SLIST         = ACTRL_PERM_2;
  {$EXTERNALSYM ACTRL_PRINT_SLIST}
  ACTRL_PRINT_PADMIN        = ACTRL_PERM_3;
  {$EXTERNALSYM ACTRL_PRINT_PADMIN}
  ACTRL_PRINT_PUSE          = ACTRL_PERM_4;
  {$EXTERNALSYM ACTRL_PRINT_PUSE}
  ACTRL_PRINT_JADMIN        = ACTRL_PERM_5;
  {$EXTERNALSYM ACTRL_PRINT_JADMIN}
  ACTRL_SVC_GET_INFO        = ACTRL_PERM_1;
  {$EXTERNALSYM ACTRL_SVC_GET_INFO}
  ACTRL_SVC_SET_INFO        = ACTRL_PERM_2;
  {$EXTERNALSYM ACTRL_SVC_SET_INFO}
  ACTRL_SVC_STATUS          = ACTRL_PERM_3;
  {$EXTERNALSYM ACTRL_SVC_STATUS}
  ACTRL_SVC_LIST            = ACTRL_PERM_4;
  {$EXTERNALSYM ACTRL_SVC_LIST}
  ACTRL_SVC_START           = ACTRL_PERM_5;
  {$EXTERNALSYM ACTRL_SVC_START}
  ACTRL_SVC_STOP            = ACTRL_PERM_6;
  {$EXTERNALSYM ACTRL_SVC_STOP}
  ACTRL_SVC_PAUSE           = ACTRL_PERM_7;
  {$EXTERNALSYM ACTRL_SVC_PAUSE}
  ACTRL_SVC_INTERROGATE     = ACTRL_PERM_8;
  {$EXTERNALSYM ACTRL_SVC_INTERROGATE}
  ACTRL_SVC_UCONTROL        = ACTRL_PERM_9;
  {$EXTERNALSYM ACTRL_SVC_UCONTROL}
  ACTRL_REG_QUERY           = ACTRL_PERM_1;
  {$EXTERNALSYM ACTRL_REG_QUERY}
  ACTRL_REG_SET             = ACTRL_PERM_2;
  {$EXTERNALSYM ACTRL_REG_SET}
  ACTRL_REG_CREATE_CHILD    = ACTRL_PERM_3;
  {$EXTERNALSYM ACTRL_REG_CREATE_CHILD}
  ACTRL_REG_LIST            = ACTRL_PERM_4;
  {$EXTERNALSYM ACTRL_REG_LIST}
  ACTRL_REG_NOTIFY          = ACTRL_PERM_5;
  {$EXTERNALSYM ACTRL_REG_NOTIFY}
  ACTRL_REG_LINK            = ACTRL_PERM_6;
  {$EXTERNALSYM ACTRL_REG_LINK}
  ACTRL_WIN_CLIPBRD         = ACTRL_PERM_1;
  {$EXTERNALSYM ACTRL_WIN_CLIPBRD}
  ACTRL_WIN_GLOBAL_ATOMS    = ACTRL_PERM_2;
  {$EXTERNALSYM ACTRL_WIN_GLOBAL_ATOMS}
  ACTRL_WIN_CREATE          = ACTRL_PERM_3;
  {$EXTERNALSYM ACTRL_WIN_CREATE}
  ACTRL_WIN_LIST_DESK       = ACTRL_PERM_4;
  {$EXTERNALSYM ACTRL_WIN_LIST_DESK}
  ACTRL_WIN_LIST            = ACTRL_PERM_5;
  {$EXTERNALSYM ACTRL_WIN_LIST}
  ACTRL_WIN_READ_ATTRIBS    = ACTRL_PERM_6;
  {$EXTERNALSYM ACTRL_WIN_READ_ATTRIBS}
  ACTRL_WIN_WRITE_ATTRIBS   = ACTRL_PERM_7;
  {$EXTERNALSYM ACTRL_WIN_WRITE_ATTRIBS}
  ACTRL_WIN_SCREEN          = ACTRL_PERM_8;
  {$EXTERNALSYM ACTRL_WIN_SCREEN}
  ACTRL_WIN_EXIT            = ACTRL_PERM_9;
  {$EXTERNALSYM ACTRL_WIN_EXIT}


type
  PACTRL_OVERLAPPED = ^ACTRL_OVERLAPPED;
  {$EXTERNALSYM PACTRL_OVERLAPPED}
  _ACTRL_OVERLAPPED = packed record
    //union {
    Provider: PVOID;
    //    ULONG Reserved1;
    //};
    Reserved2: ULONG;
    hEvent: HANDLE;
  end;
  {$EXTERNALSYM _ACTRL_OVERLAPPED}
  ACTRL_OVERLAPPED = _ACTRL_OVERLAPPED;
  {$EXTERNALSYM ACTRL_OVERLAPPED}
  TActrlOverlapped = ACTRL_OVERLAPPED;
  PActrlOverlapped = PACTRL_OVERLAPPED;

  PACTRL_ACCESS_INFOA = ^ACTRL_ACCESS_INFOA;
  {$EXTERNALSYM PACTRL_ACCESS_INFOA}
  _ACTRL_ACCESS_INFOA = packed record
    fAccessPermission: ULONG;
    lpAccessPermissionName: LPSTR;
  end;
  {$EXTERNALSYM _ACTRL_ACCESS_INFOA}
  ACTRL_ACCESS_INFOA = _ACTRL_ACCESS_INFOA;
  {$EXTERNALSYM ACTRL_ACCESS_INFOA}
  TActrlAccessInfoA = ACTRL_ACCESS_INFOA;
  PActrlAccessInfoA = PACTRL_ACCESS_INFOA;

  PACTRL_ACCESS_INFOW = ^ACTRL_ACCESS_INFOW;
  {$EXTERNALSYM PACTRL_ACCESS_INFOW}
  _ACTRL_ACCESS_INFOW = packed record
    fAccessPermission: ULONG;
    lpAccessPermissionName: LPWSTR;
  end;
  {$EXTERNALSYM _ACTRL_ACCESS_INFOW}
  ACTRL_ACCESS_INFOW = _ACTRL_ACCESS_INFOW;
  {$EXTERNALSYM ACTRL_ACCESS_INFOW}
  TActrlAccessInfoW = ACTRL_ACCESS_INFOW;
  PActrlAccessInfoW = PACTRL_ACCESS_INFOW;

{$IFDEF UNICODE}
  ACTRL_ACCESS_INFO = ACTRL_ACCESS_INFOW;
  {$EXTERNALSYM ACTRL_ACCESS_INFO}
  PACTRL_ACCESS_INFO = PACTRL_ACCESS_INFOW;
  {$EXTERNALSYM PACTRL_ACCESS_INFO}
  TActrlAccessInfo = TActrlAccessInfoW;
  PActrlAccessInfo = PActrlAccessInfoW;
{$ELSE}
  ACTRL_ACCESS_INFO = ACTRL_ACCESS_INFOA;
  {$EXTERNALSYM ACTRL_ACCESS_INFO}
  PACTRL_ACCESS_INFO = PACTRL_ACCESS_INFOA;
  {$EXTERNALSYM PACTRL_ACCESS_INFO}
  TActrlAccessInfo = TActrlAccessInfoA;
  PActrlAccessInfo = PActrlAccessInfoA;
{$ENDIF}

  PACTRL_CONTROL_INFOA = ^ACTRL_CONTROL_INFOA;
  {$EXTERNALSYM PACTRL_CONTROL_INFOA}
  _ACTRL_CONTROL_INFOA = packed record
    lpControlId: LPSTR;
    lpControlName: LPSTR;
  end;
  {$EXTERNALSYM _ACTRL_CONTROL_INFOA}
  ACTRL_CONTROL_INFOA = _ACTRL_CONTROL_INFOA;
  {$EXTERNALSYM ACTRL_CONTROL_INFOA}
  TActrlControlInfoA = ACTRL_CONTROL_INFOA;
  PActrlControlInfoA = PACTRL_CONTROL_INFOA;

  PACTRL_CONTROL_INFOW = ^ACTRL_CONTROL_INFOW;
  {$EXTERNALSYM PACTRL_CONTROL_INFOW}
  _ACTRL_CONTROL_INFOW = packed record
    lpControlId: LPWSTR;
    lpControlName: LPWSTR;
  end;
  {$EXTERNALSYM _ACTRL_CONTROL_INFOW}
  ACTRL_CONTROL_INFOW = _ACTRL_CONTROL_INFOW;
  {$EXTERNALSYM ACTRL_CONTROL_INFOW}
  TActrlControlInfoW = ACTRL_CONTROL_INFOW;
  PActrlControlInfoW = PACTRL_CONTROL_INFOW;

{$IFDEF UNICODE}
  ACTRL_CONTROL_INFO = ACTRL_CONTROL_INFOW;
  {$EXTERNALSYM ACTRL_CONTROL_INFO}
  PACTRL_CONTROL_INFO = PACTRL_CONTROL_INFOW;
  {$EXTERNALSYM PACTRL_CONTROL_INFO}
  TActrlControlInfo = TActrlControlInfoW;
  PActrlControlInfo = PActrlControlInfoW;
{$ELSE}
  ACTRL_CONTROL_INFO = ACTRL_CONTROL_INFOA;
  {$EXTERNALSYM ACTRL_CONTROL_INFO}
  PACTRL_CONTROL_INFO = PACTRL_CONTROL_INFOA;
  {$EXTERNALSYM PACTRL_CONTROL_INFO}
  TActrlControlInfo = TActrlControlInfoA;
  PActrlControlInfo = PActrlControlInfoA;
{$ENDIF}

const
  ACTRL_ACCESS_NO_OPTIONS              = $00000000;
  {$EXTERNALSYM ACTRL_ACCESS_NO_OPTIONS}
  ACTRL_ACCESS_SUPPORTS_OBJECT_ENTRIES = $00000001;
  {$EXTERNALSYM ACTRL_ACCESS_SUPPORTS_OBJECT_ENTRIES}

  ProgressInvokeNever = 1;        // Never invoke the progress function
  {$EXTERNALSYM ProgressInvokeNever}
  ProgressInvokeEveryObject = 2;  // Invoke for each object
  {$EXTERNALSYM ProgressInvokeEveryObject}
  ProgressInvokeOnError = 3;      // Invoke only for each error case
  {$EXTERNALSYM ProgressInvokeOnError}
  ProgressCancelOperation = 4;    // Stop propagation and return
  {$EXTERNALSYM ProgressCancelOperation}
  ProgressRetryOperation = 5;     // Retry operation on subtree
  {$EXTERNALSYM ProgressRetryOperation}

type
  PROG_INVOKE_SETTING = DWORD;
  {$EXTERNALSYM PROG_INVOKE_SETTING}
  PPROG_INVOKE_SETTING = ^PROG_INVOKE_SETTING;
  {$EXTERNALSYM PPROG_INVOKE_SETTING}
  TProgInvokeSetting = PROG_INVOKE_SETTING;
  PProgInvokeSetting = PPROG_INVOKE_SETTING;

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
  FN_PROGRESS = procedure (pObjectName: LPWSTR; Status: DWORD;
    var pInvokeSetting: PROG_INVOKE_SETTING; Args: PVOID; SecuritySet: BOOL); stdcall;
  {$EXTERNALSYM FN_PROGRESS}
  TFnProgress = FN_PROGRESS;

//
// New Object Type function pointers.  TBD.
// To support additional object resource managers generically, the
// resource manager must provide it's own functions for operations
// like:
// GetAncestorAcl(IN ObjName, IN GenerationGap, IN DaclOrSacl?, ...)
// GetAncestorName(...)
// FreeNameStructure(...)
//

type
  _FN_OBJECT_MGR_FUNCTIONS = record
    Placeholder: ULONG;
  end;
  {$EXTERNALSYM _FN_OBJECT_MGR_FUNCTIONS}
  FN_OBJECT_MGR_FUNCTS = _FN_OBJECT_MGR_FUNCTIONS;
  {$EXTERNALSYM FN_OBJECT_MGR_FUNCTS}
  PFN_OBJECT_MGR_FUNCTS = ^FN_OBJECT_MGR_FUNCTS;
  {$EXTERNALSYM PFN_OBJECT_MGR_FUNCTS}
  TFnObjectMgrFuncts = FN_OBJECT_MGR_FUNCTS;
  PFnObjectMgrFuncts = PFN_OBJECT_MGR_FUNCTS;  

//
// Name of ancestor and number of generations between
// ancestor and inheriting object.
//
// GenerationGap:
//     Name of ancestor from which ACE was inherited.
//     NULL for explicit ACE.
//
// AncestorName:
//     Number of levels (or generations) between the object and the ancestor.
//     Parent, gap=1.
//     Grandparent, gap=2.
//     Set to 0 for explicit ACE on object.
//

type
  _INHERITED_FROMA = record
    GenerationGap: LONG;
    AncestorName: LPSTR;
  end;
  {$EXTERNALSYM _INHERITED_FROMA}
  INHERITED_FROMA = _INHERITED_FROMA;
  {$EXTERNALSYM INHERITED_FROMA}
  PINHERITED_FROMA = ^INHERITED_FROMA;
  {$EXTERNALSYM PINHERITED_FROMA}
  TInheritedFromA = INHERITED_FROMA;
  PInheritedFromA = PINHERITED_FROMA;

  _INHERITED_FROMW = record
    GenerationGap: LONG;
    AncestorName: LPWSTR;
  end;
  {$EXTERNALSYM _INHERITED_FROMW}
  INHERITED_FROMW = _INHERITED_FROMW;
  {$EXTERNALSYM INHERITED_FROMW}
  PINHERITED_FROMW = ^INHERITED_FROMW;
  {$EXTERNALSYM PINHERITED_FROMW}
  TInheritedFromW = INHERITED_FROMW;
  PInheritedFromW = PINHERITED_FROMW;

{$IFDEF UNICODE}
  INHERITED_FROM = INHERITED_FROMW;
  {$EXTERNALSYM INHERITED_FROM}
  PINHERITED_FROM = PINHERITED_FROMW;
  {$EXTERNALSYM PINHERITED_FROM}
  TInheritedFrom = TInheritedFromW;
  PInheritedFrom = PInheritedFromW;
{$ELSE}
  INHERITED_FROM = INHERITED_FROMA;
  {$EXTERNALSYM INHERITED_FROM}
  PINHERITED_FROM = PINHERITED_FROMA;
  {$EXTERNALSYM PINHERITED_FROM}
  TInheritedFrom = TInheritedFromA;
  PInheritedFrom = PInheritedFromA;
{$ENDIF}

implementation

uses
  JwaWinBase;

function AccFree(hMem: HLOCAL): HLOCAL;
begin
  Result := LocalFree(hMem);
end;

end.
