{******************************************************************************}
{                                                       	               }
{ Object Picker API interface Unit for Object Pascal                           }
{                                                       	               }
{ Portions created by Microsoft are Copyright (C) 1995-2001 Microsoft          }
{ Corporation. All Rights Reserved.                                            }
{ 								               }
{ The original file is: objsel.h, released June 2000. The original Pascal      }
{ code is: ObjSel.pas, released December 2000. The initial developer of the    }
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

unit JwaObjSel;

{$WEAKPACKAGEUNIT}

{$HPPEMIT ''}
{$HPPEMIT '#include "ObjSel.h"'}
{$HPPEMIT ''}

{$I WINDEFINES.INC}

interface

uses
  ActiveX {TODO}, JwaWinType;

//  Contents:   Object Picker Dialog public header

const
  //'{17d6ccd8-3b7b-11d2-b9e0-00c04fd8dbf7}'
  CLSID_DsObjectPicker: TGUID = (
    D1:$17d6ccd8; D2:$3b7b; D3:$11d2; D4:($b9,$e0,$00,$c0,$4f,$d8,$db,$f7));
  {$EXTERNALSYM CLSID_DsObjectPicker}

  IID_IDsObjectPicker: TGUID = (
    D1:$0c87e64e; D2:$3b7a; D3:$11d2; D4:($b9,$e0,$00,$c0,$4f,$d8,$db,$f7));
  {$EXTERNALSYM IID_IDsObjectPicker}

{
CLIPBOARD FORMATS
=================

CFSTR_DSOP_DS_SELECTION_LIST
    Returns an HGLOBAL for global memory containing a DS_SELECTION_LIST
    variable length structure.
}

const
  CFSTR_DSOP_DS_SELECTION_LIST = 'CFSTR_DSOP_DS_SELECTION_LIST';
  {$EXTERNALSYM CFSTR_DSOP_DS_SELECTION_LIST}

{
SCOPE TYPES
===========

A scope is an entry in the "Look In" dropdown list of the Object Picker
dialog.

When initializing the DS Object Picker, DSOP_SCOPE_TYPEs are used with
DSOP_SCOPE_INIT_INFO.flType member to specify which types of scopes the
DS Object Picker should put in the "Look In" list.

DSOP_SCOPE_TYPE_TARGET_COMPUTER
    Computer specified by DSOP_INIT_INFO.pwzTargetComputer, NULL is
    local computer.

DSOP_SCOPE_TYPE_UPLEVEL_JOINED_DOMAIN
    Uplevel domain to which target computer is joined.

DSOP_SCOPE_TYPE_DOWNLEVEL_JOINED_DOMAIN
    Downlevel domain to which target computer is joined.

DSOP_SCOPE_TYPE_ENTERPRISE_DOMAIN
    All domains in the enterprise to which the target computer belongs
    other than the JOINED_DOMAIN or USER_SPECIFIED_*_SCOPEs.

DSOP_SCOPE_TYPE_GLOBAL_CATALOG
    The Entire Directory scope.

DSOP_SCOPE_TYPE_EXTERNAL_UPLEVEL_DOMAIN
    All uplevel domains external to the enterprise but trusted by the
    domain to which the target computer is joined.

DSOP_SCOPE_TYPE_EXTERNAL_DOWNLEVEL_DOMAIN
    All downlevel domains external to the enterprise but trusted by the
    domain to which the target computer is joined.

DSOP_SCOPE_TYPE_WORKGROUP
    The workgroup of which TARGET_COMPUTER is a member.  Applies only if the
    TARGET_COMPUTER is not joined to a domain.

DSOP_SCOPE_TYPE_USER_ENTERED_UPLEVEL_SCOPE
DSOP_SCOPE_TYPE_USER_ENTERED_DOWNLEVEL_SCOPE
    Any uplevel or downlevel scope generated by processing user input.  If
    neither of these types is specified, user entries that do not refer to
    one of the scopes in the "Look In" control will be rejected.

}

const
  DSOP_SCOPE_TYPE_TARGET_COMPUTER              = $00000001;
  {$EXTERNALSYM DSOP_SCOPE_TYPE_TARGET_COMPUTER}
  DSOP_SCOPE_TYPE_UPLEVEL_JOINED_DOMAIN        = $00000002;
  {$EXTERNALSYM DSOP_SCOPE_TYPE_UPLEVEL_JOINED_DOMAIN}
  DSOP_SCOPE_TYPE_DOWNLEVEL_JOINED_DOMAIN      = $00000004;
  {$EXTERNALSYM DSOP_SCOPE_TYPE_DOWNLEVEL_JOINED_DOMAIN}
  DSOP_SCOPE_TYPE_ENTERPRISE_DOMAIN            = $00000008;
  {$EXTERNALSYM DSOP_SCOPE_TYPE_ENTERPRISE_DOMAIN}
  DSOP_SCOPE_TYPE_GLOBAL_CATALOG               = $00000010;
  {$EXTERNALSYM DSOP_SCOPE_TYPE_GLOBAL_CATALOG}
  DSOP_SCOPE_TYPE_EXTERNAL_UPLEVEL_DOMAIN      = $00000020;
  {$EXTERNALSYM DSOP_SCOPE_TYPE_EXTERNAL_UPLEVEL_DOMAIN}
  DSOP_SCOPE_TYPE_EXTERNAL_DOWNLEVEL_DOMAIN    = $00000040;
  {$EXTERNALSYM DSOP_SCOPE_TYPE_EXTERNAL_DOWNLEVEL_DOMAIN}
  DSOP_SCOPE_TYPE_WORKGROUP                    = $00000080;
  {$EXTERNALSYM DSOP_SCOPE_TYPE_WORKGROUP}
  DSOP_SCOPE_TYPE_USER_ENTERED_UPLEVEL_SCOPE   = $00000100;
  {$EXTERNALSYM DSOP_SCOPE_TYPE_USER_ENTERED_UPLEVEL_SCOPE}
  DSOP_SCOPE_TYPE_USER_ENTERED_DOWNLEVEL_SCOPE = $00000200;
  {$EXTERNALSYM DSOP_SCOPE_TYPE_USER_ENTERED_DOWNLEVEL_SCOPE}

{
DSOP_SCOPE_INIT_INFO flags
==========================

The flScope member can contain zero or more of the following flags:

DSOP_SCOPE_FLAG_STARTING_SCOPE
    The scope should be the first one selected in the Look In control after
    dialog initialization.  If more than one scope specifies this flag,
    the one which is chosen to be the starting scope is implementation
    dependant.

DSOP_SCOPE_FLAG_WANT_PROVIDER_WINNT
    ADs paths for objects selected from this scope should be converted to use
    the WinNT provider.

DSOP_SCOPE_FLAG_WANT_PROVIDER_LDAP
    ADs paths for objects selected from this scope should be converted to use
    the LDAP provider.

DSOP_SCOPE_FLAG_WANT_PROVIDER_GC
    ADs paths for objects selected from this scope should be converted to use
    the GC provider.

DSOP_SCOPE_FLAG_WANT_SID_PATH
    ADs paths for objects selected from this scope having an objectSid
    attribute should be converted to the form LDAP://<SID=x>, where x
    represents the hexidecimal digits of the objectSid attribute value.

DSOP_SCOPE_FLAG_WANT_DOWNLEVEL_BUILTIN_PATH
    ADs paths for downlevel well-known SID objects (for example,
    DSOP_DOWNLEVEL_FILTER_INTERACTIVE) are an empty string unless this flag is
    specified.  If it is, the paths will be of the form
    WinNT://NT AUTHORITY/Interactive or WinNT://Creator owner.

DSOP_SCOPE_FLAG_DEFAULT_FILTER_USERS
    If the scope filter contains the DSOP_FILTER_USERS or
    DSOP_DOWNLEVEL_FILTER_USERS flag, then check the Users checkbox by
    default in the Look For dialog.

DSOP_SCOPE_FLAG_DEFAULT_FILTER_GROUPS


DSOP_SCOPE_FLAG_DEFAULT_FILTER_COMPUTERS

DSOP_SCOPE_FLAG_DEFAULT_FILTER_CONTACTS
}

const
  DSOP_SCOPE_FLAG_STARTING_SCOPE              = $00000001;
  {$EXTERNALSYM DSOP_SCOPE_FLAG_STARTING_SCOPE}
  DSOP_SCOPE_FLAG_WANT_PROVIDER_WINNT         = $00000002;
  {$EXTERNALSYM DSOP_SCOPE_FLAG_WANT_PROVIDER_WINNT}
  DSOP_SCOPE_FLAG_WANT_PROVIDER_LDAP          = $00000004;
  {$EXTERNALSYM DSOP_SCOPE_FLAG_WANT_PROVIDER_LDAP}
  DSOP_SCOPE_FLAG_WANT_PROVIDER_GC            = $00000008;
  {$EXTERNALSYM DSOP_SCOPE_FLAG_WANT_PROVIDER_GC}
  DSOP_SCOPE_FLAG_WANT_SID_PATH               = $00000010;
  {$EXTERNALSYM DSOP_SCOPE_FLAG_WANT_SID_PATH}
  DSOP_SCOPE_FLAG_WANT_DOWNLEVEL_BUILTIN_PATH = $00000020;
  {$EXTERNALSYM DSOP_SCOPE_FLAG_WANT_DOWNLEVEL_BUILTIN_PATH}
  DSOP_SCOPE_FLAG_DEFAULT_FILTER_USERS        = $00000040;
  {$EXTERNALSYM DSOP_SCOPE_FLAG_DEFAULT_FILTER_USERS}
  DSOP_SCOPE_FLAG_DEFAULT_FILTER_GROUPS       = $00000080;
  {$EXTERNALSYM DSOP_SCOPE_FLAG_DEFAULT_FILTER_GROUPS}
  DSOP_SCOPE_FLAG_DEFAULT_FILTER_COMPUTERS    = $00000100;
  {$EXTERNALSYM DSOP_SCOPE_FLAG_DEFAULT_FILTER_COMPUTERS}
  DSOP_SCOPE_FLAG_DEFAULT_FILTER_CONTACTS     = $00000200;
  {$EXTERNALSYM DSOP_SCOPE_FLAG_DEFAULT_FILTER_CONTACTS}

{
The flMixedModeOnly/flNativeModeOnly member of an uplevel scope can
contain one or more of the following flags (at least one must be specified):

DSOP_FILTER_INCLUDE_ADVANCED_VIEW
    Include objects which have the attribute showInAdvancedViewOnly set to
    true.

DSOP_FILTER_USERS
    Include user objects.

DSOP_FILTER_BUILTIN_GROUPS
    Include group objects with a groupType value having the flag
    GROUP_TYPE_BUILTIN_LOCAL_GROUP.

DSOP_FILTER_WELL_KNOWN_PRINCIPALS
    Include the contents of the WellKnown Security Principals container.

DSOP_FILTER_UNIVERSAL_GROUPS_DL
    Include distribution list universal groups.

DSOP_FILTER_UNIVERSAL_GROUPS_SE
    Include security enabled universal groups.

DSOP_FILTER_GLOBAL_GROUPS_DL
    Include distribution list global groups.

DSOP_FILTER_GLOBAL_GROUPS_SE
    Include security enabled global groups.

DSOP_FILTER_DOMAIN_LOCAL_GROUPS_DL
    Include distribution list domain global groups.

DSOP_FILTER_DOMAIN_LOCAL_GROUPS_SE
    Include security enabled domain local groups.

DSOP_FILTER_CONTACTS
    Include contact objects.

DSOP_FILTER_COMPUTERS
    Include computer objects.
}

const
  DSOP_FILTER_INCLUDE_ADVANCED_VIEW  = $00000001;
  {$EXTERNALSYM DSOP_FILTER_INCLUDE_ADVANCED_VIEW}
  DSOP_FILTER_USERS                  = $00000002;
  {$EXTERNALSYM DSOP_FILTER_USERS}
  DSOP_FILTER_BUILTIN_GROUPS         = $00000004;
  {$EXTERNALSYM DSOP_FILTER_BUILTIN_GROUPS}
  DSOP_FILTER_WELL_KNOWN_PRINCIPALS  = $00000008;
  {$EXTERNALSYM DSOP_FILTER_WELL_KNOWN_PRINCIPALS}
  DSOP_FILTER_UNIVERSAL_GROUPS_DL    = $00000010;
  {$EXTERNALSYM DSOP_FILTER_UNIVERSAL_GROUPS_DL}
  DSOP_FILTER_UNIVERSAL_GROUPS_SE    = $00000020;
  {$EXTERNALSYM DSOP_FILTER_UNIVERSAL_GROUPS_SE}
  DSOP_FILTER_GLOBAL_GROUPS_DL       = $00000040;
  {$EXTERNALSYM DSOP_FILTER_GLOBAL_GROUPS_DL}
  DSOP_FILTER_GLOBAL_GROUPS_SE       = $00000080;
  {$EXTERNALSYM DSOP_FILTER_GLOBAL_GROUPS_SE}
  DSOP_FILTER_DOMAIN_LOCAL_GROUPS_DL = $00000100;
  {$EXTERNALSYM DSOP_FILTER_DOMAIN_LOCAL_GROUPS_DL}
  DSOP_FILTER_DOMAIN_LOCAL_GROUPS_SE = $00000200;
  {$EXTERNALSYM DSOP_FILTER_DOMAIN_LOCAL_GROUPS_SE}
  DSOP_FILTER_CONTACTS               = $00000400;
  {$EXTERNALSYM DSOP_FILTER_CONTACTS}
  DSOP_FILTER_COMPUTERS              = $00000800;
  {$EXTERNALSYM DSOP_FILTER_COMPUTERS}

{
The flFilter member of a downlevel scope can contain one or more of the
following flags:

DSOP_DOWNLEVEL_FILTER_USERS
    Include user objects.

DSOP_DOWNLEVEL_FILTER_LOCAL_GROUPS
    Include all local groups.

DSOP_DOWNLEVEL_FILTER_GLOBAL_GROUPS
    Include all global groups.

DSOP_DOWNLEVEL_FILTER_COMPUTERS
    Include computer objects

DSOP_DOWNLEVEL_FILTER_WORLD
    Include builtin security principal World (Everyone).

DSOP_DOWNLEVEL_FILTER_AUTHENTICATED_USER
    Include builtin security principal Authenticated User.

DSOP_DOWNLEVEL_FILTER_ANONYMOUS
    Include builtin security principal Anonymous.

DSOP_DOWNLEVEL_FILTER_BATCH
    Include builtin security principal Batch.

DSOP_DOWNLEVEL_FILTER_CREATOR_OWNER
    Include builtin security principal Creator Owner.

DSOP_DOWNLEVEL_FILTER_CREATOR_GROUP
    Include builtin security principal Creator Group.

DSOP_DOWNLEVEL_FILTER_DIALUP
    Include builtin security principal Dialup.

DSOP_DOWNLEVEL_FILTER_INTERACTIVE
    Include builtin security principal Interactive.

DSOP_DOWNLEVEL_FILTER_NETWORK
    Include builtin security principal Network.

DSOP_DOWNLEVEL_FILTER_SERVICE
    Include builtin security principal Service.

DSOP_DOWNLEVEL_FILTER_SYSTEM
    Include builtin security principal System.

DSOP_DOWNLEVEL_FILTER_EXCLUDE_BUILTIN_GROUPS
    Exclude local builtin groups returned by groups enumeration.

DSOP_DOWNLEVEL_FILTER_TERMINAL_SERVER
    Include builtin security principal Terminal Server.

DSOP_DOWNLEVEL_FILTER_LOCAL_SERVICE
    Include builtin security principal Local Service

DSOP_DOWNLEVEL_FILTER_NETWORK_SERVICE
    Include builtin security principal Network Service

DSOP_DOWNLEVEL_FILTER_ALL_WELLKNOWN_SIDS
    Include all builtin security principals.
}

const
  DSOP_DOWNLEVEL_FILTER_USERS                  = DWORD($80000001);
  {$EXTERNALSYM DSOP_DOWNLEVEL_FILTER_USERS}
  DSOP_DOWNLEVEL_FILTER_LOCAL_GROUPS           = DWORD($80000002);
  {$EXTERNALSYM DSOP_DOWNLEVEL_FILTER_LOCAL_GROUPS}
  DSOP_DOWNLEVEL_FILTER_GLOBAL_GROUPS          = DWORD($80000004);
  {$EXTERNALSYM DSOP_DOWNLEVEL_FILTER_GLOBAL_GROUPS}
  DSOP_DOWNLEVEL_FILTER_COMPUTERS              = DWORD($80000008);
  {$EXTERNALSYM DSOP_DOWNLEVEL_FILTER_COMPUTERS}
  DSOP_DOWNLEVEL_FILTER_WORLD                  = DWORD($80000010);
  {$EXTERNALSYM DSOP_DOWNLEVEL_FILTER_WORLD}
  DSOP_DOWNLEVEL_FILTER_AUTHENTICATED_USER     = DWORD($80000020);
  {$EXTERNALSYM DSOP_DOWNLEVEL_FILTER_AUTHENTICATED_USER}
  DSOP_DOWNLEVEL_FILTER_ANONYMOUS              = DWORD($80000040);
  {$EXTERNALSYM DSOP_DOWNLEVEL_FILTER_ANONYMOUS}
  DSOP_DOWNLEVEL_FILTER_BATCH                  = DWORD($80000080);
  {$EXTERNALSYM DSOP_DOWNLEVEL_FILTER_BATCH}
  DSOP_DOWNLEVEL_FILTER_CREATOR_OWNER          = DWORD($80000100);
  {$EXTERNALSYM DSOP_DOWNLEVEL_FILTER_CREATOR_OWNER}
  DSOP_DOWNLEVEL_FILTER_CREATOR_GROUP          = DWORD($80000200);
  {$EXTERNALSYM DSOP_DOWNLEVEL_FILTER_CREATOR_GROUP}
  DSOP_DOWNLEVEL_FILTER_DIALUP                 = DWORD($80000400);
  {$EXTERNALSYM DSOP_DOWNLEVEL_FILTER_DIALUP}
  DSOP_DOWNLEVEL_FILTER_INTERACTIVE            = DWORD($80000800);
  {$EXTERNALSYM DSOP_DOWNLEVEL_FILTER_INTERACTIVE}
  DSOP_DOWNLEVEL_FILTER_NETWORK                = DWORD($80001000);
  {$EXTERNALSYM DSOP_DOWNLEVEL_FILTER_NETWORK}
  DSOP_DOWNLEVEL_FILTER_SERVICE                = DWORD($80002000);
  {$EXTERNALSYM DSOP_DOWNLEVEL_FILTER_SERVICE}
  DSOP_DOWNLEVEL_FILTER_SYSTEM                 = DWORD($80004000);
  {$EXTERNALSYM DSOP_DOWNLEVEL_FILTER_SYSTEM}
  DSOP_DOWNLEVEL_FILTER_EXCLUDE_BUILTIN_GROUPS = DWORD($80008000);
  {$EXTERNALSYM DSOP_DOWNLEVEL_FILTER_EXCLUDE_BUILTIN_GROUPS}
  DSOP_DOWNLEVEL_FILTER_TERMINAL_SERVER        = DWORD($80010000);
  {$EXTERNALSYM DSOP_DOWNLEVEL_FILTER_TERMINAL_SERVER}
  DSOP_DOWNLEVEL_FILTER_ALL_WELLKNOWN_SIDS     = DWORD($80020000);
  {$EXTERNALSYM DSOP_DOWNLEVEL_FILTER_ALL_WELLKNOWN_SIDS}
  DSOP_DOWNLEVEL_FILTER_LOCAL_SERVICE          = DWORD($80040000);
  {$EXTERNALSYM DSOP_DOWNLEVEL_FILTER_LOCAL_SERVICE}
  DSOP_DOWNLEVEL_FILTER_NETWORK_SERVICE        = DWORD($80080000);
  {$EXTERNALSYM DSOP_DOWNLEVEL_FILTER_NETWORK_SERVICE}
  DSOP_DOWNLEVEL_FILTER_REMOTE_LOGON           = DWORD($80100000);
  {$EXTERNALSYM DSOP_DOWNLEVEL_FILTER_REMOTE_LOGON}

{
DSOP_UPLEVEL_FILTER_FLAGS
=========================

Contains the DSOP_FILTER_* flags for use with a DSOP_SCOPE_INIT_INFO
structure when the scope is uplevel (DS-aware).

flBothModes
    Flags to use for an uplevel scope, regardless of whether it is a
    mixed or native mode domain.

flMixedModeOnly
    Flags to use when an uplevel domain is in mixed mode.

flNativeModeOnly
    Flags to use when an uplevel domain is in native mode.


DSOP_FILTER_FLAGS
=================

Uplevel
    Contains flags to use for an uplevel scope.

flDownlevel
    Flags to use for a downlevel scope.
}

type
  _DSOP_UPLEVEL_FILTER_FLAGS = record
    flBothModes: ULONG;
    flMixedModeOnly: ULONG;
    flNativeModeOnly: ULONG;
  end;
  {$EXTERNALSYM _DSOP_UPLEVEL_FILTER_FLAGS}
  DSOP_UPLEVEL_FILTER_FLAGS = _DSOP_UPLEVEL_FILTER_FLAGS;
  {$EXTERNALSYM DSOP_UPLEVEL_FILTER_FLAGS}
  TDsOpUpLevelFilterFlags = DSOP_UPLEVEL_FILTER_FLAGS;
  PDsOpUpLevelFilterFlags = ^DSOP_UPLEVEL_FILTER_FLAGS;

  _DSOP_FILTER_FLAGS = record
    Uplevel: DSOP_UPLEVEL_FILTER_FLAGS;
    flDownlevel: ULONG;
  end;
  {$EXTERNALSYM _DSOP_FILTER_FLAGS}
  DSOP_FILTER_FLAGS = _DSOP_FILTER_FLAGS;
  {$EXTERNALSYM DSOP_FILTER_FLAGS}
  TDsOpFilterFlags = DSOP_FILTER_FLAGS;
  PDsOpFilterFlags = ^DSOP_FILTER_FLAGS;

{
DSOP_SCOPE_INIT_INFO
====================

Each DSOP_SCOPE_INIT_INFO structure in the array DSOP_INIT_INFO.aDsScopeInfos
describes a single scope or a group of scopes with the same settings.

cbSize
    Size, in bytes, of the entire structure.

flType
    DSOP_SCOPE_TYPE_* flags.  It is legal to combine multiple values via
    bitwise OR if all of the types of scopes combined in this way require
    the same settings.

flScope
    DSOP_SCOPE_ * flags.

FilterFlags
    DSOP_FILTER_* flags that indicate which types of objects should be
    presented to the user in this scope.

pwzDcName
    Name of the DC of a domain.  This member is used only if the flType
    member contains the flag DSOP_SCOPE_TYPE_JOINED_DOMAIN.  If that flag is
    not set, this member must be NULL.

pwzADsPath
    Currently not supported, must be NULL.

hr
    Filled with S_OK if the scope represented by this structure could be
    created, or an error message indicating why it could not.  If
    IDsObjectPicker::SetScopes returns a success code, this value will
    also be a success code.
}

type
  PDSOP_SCOPE_INIT_INFO = ^DSOP_SCOPE_INIT_INFO;
  {$EXTERNALSYM PDSOP_SCOPE_INIT_INFO}
  _DSOP_SCOPE_INIT_INFO = record
    cbSize: ULONG;
    flType: ULONG;
    flScope: ULONG;
    FilterFlags: DSOP_FILTER_FLAGS;
    pwzDcName: PWSTR;  // OPTIONAL
    pwzADsPath: PWSTR; // OPTIONAL
    hr: HRESULT;
  end;
  {$EXTERNALSYM _DSOP_SCOPE_INIT_INFO}
  DSOP_SCOPE_INIT_INFO = _DSOP_SCOPE_INIT_INFO;
  {$EXTERNALSYM DSOP_SCOPE_INIT_INFO}
  PCDSOP_SCOPE_INIT_INFO = PDSOP_SCOPE_INIT_INFO;
  {$EXTERNALSYM PCDSOP_SCOPE_INIT_INFO}
  TDsOpScopeInitInfo = DSOP_SCOPE_INIT_INFO;
  PDsOpScopeInitInfo = PDSOP_SCOPE_INIT_INFO;

{
DSOP_INIT_INFO flags
====================

The following flags may be set in DSOP_INIT_INFO.flOptions:

DSOP_FLAG_MULTISELECT
    Allow multiple selections.  If this flag is not set, the dialog will
    return zero or one objects.

DSOP_FLAG_SKIP_TARGET_COMPUTER_DC_CHECK
    If this flag is NOT set, then the DSOP_SCOPE_TYPE_TARGET_COMPUTER flag
    will be ignored if the target computer is a DC.  This flag has no effect
    unless DSOP_SCOPE_TYPE_TARGET_COMPUTER is specified.

}

const
  DSOP_FLAG_MULTISELECT                   = $00000001;
  {$EXTERNALSYM DSOP_FLAG_MULTISELECT}
  DSOP_FLAG_SKIP_TARGET_COMPUTER_DC_CHECK = $00000002;
  {$EXTERNALSYM DSOP_FLAG_SKIP_TARGET_COMPUTER_DC_CHECK}

{
DSOP_INIT_INFO
==============

Used to configure the DS Object Picker dialog.

cbSize
    Size, in bytes, of entire structure.

pwzTargetComputer
    Sets the computer associated with DSOP_SCOPE_TARGET_COMPUTER, and
    which is used to determine the joined domain and enterprise.
    If this value is NULL, the target computer is the local machine.

cDsScopeInfos
    Count of elements in aDsScopeInfos.  Must be at least 1, since
    the object picker cannot operate without at least one scope.

aDsScopeInfos
    Array of scope initialization structures.  Must be present and
    contain at least one element.

flOptions
    Various DS Object Picker flags (DSOP_FLAG_MULTISELECT).

cAttributesToFetch
    Count of elements in apwzAttributeNames.  Can be 0.

apwzAttributeNames
    Array of names of attributes to fetch for each object.  Ignored
    if cAttributesToFetch is 0.
}

type
  PDSOP_INIT_INFO = ^DSOP_INIT_INFO;
  {$EXTERNALSYM PDSOP_INIT_INFO}
  _DSOP_INIT_INFO = record
    cbSize: ULONG;
    pwzTargetComputer: PWSTR;
    cDsScopeInfos: ULONG;
    aDsScopeInfos: PDSOP_SCOPE_INIT_INFO;
    flOptions: ULONG;
    cAttributesToFetch: ULONG;
    apwzAttributeNames: LPLPWSTR;
  end;
  {$EXTERNALSYM _DSOP_INIT_INFO}
  DSOP_INIT_INFO = _DSOP_INIT_INFO;
  {$EXTERNALSYM DSOP_INIT_INFO}
  PCDSOP_INIT_INFO = PDSOP_INIT_INFO;
  {$EXTERNALSYM PCDSOP_INIT_INFO}
  TDsOpInitInfo = DSOP_INIT_INFO;
  PDsOpInitInfo = PDSOP_INIT_INFO;

{
DS_SELECTION
============
Describes an object selected by the user.

pwzName
    The object's RDN.

pwzADsPath
    The object's ADsPath.

pwzClass
    The object's class attribute value.

pwzUPN
    The object's userPrincipalName attribute value.

pvarFetchedAttributes
    An array of VARIANTs, one for each attribute fetched.

flScopeType
    A single DSOP_SCOPE_TYPE_* flag describing the type of the scope
    from which this object was selected.


DS_SELECTION_LIST
=================
Available as a clipboard format from the data object returned by
IDsObjectPicker::InvokeDialog.  Contains a list of objects that the user
selected.

cItems
    Number of elements in the aDsSelection array.

cFetchedAttributes
    Number of elements in each DSSELECTION.avarFetchedAttributes member.

aDsSelection
    Array of cItems DSSELECTION structures.
}

type
  PDS_SELECTION = ^DS_SELECTION;
  {$EXTERNALSYM PDS_SELECTION}
  _DS_SELECTION = record
    pwzName: PWSTR;
    pwzADsPath: PWSTR;
    pwzClass: PWSTR;
    pwzUPN: PWSTR;
    pvarFetchedAttributes: POleVariant; 
    flScopeType: ULONG;
  end;
  {$EXTERNALSYM _DS_SELECTION}
  DS_SELECTION = _DS_SELECTION;
  {$EXTERNALSYM DS_SELECTION}
  TDsSelection = DS_SELECTION;
  PDsSelection = PDS_SELECTION;

  PDS_SELECTION_LIST = ^DS_SELECTION_LIST;
  {$EXTERNALSYM PDS_SELECTION_LIST}
  _DS_SELECTION_LIST = record
    cItems: ULONG;
    cFetchedAttributes: ULONG;
    aDsSelection: array [0..ANYSIZE_ARRAY - 1] of DS_SELECTION;
  end;
  {$EXTERNALSYM _DS_SELECTION_LIST}
  DS_SELECTION_LIST = _DS_SELECTION_LIST;
  {$EXTERNALSYM DS_SELECTION_LIST}
  TDsSelectionList = DS_SELECTION_LIST;
  PDsSelectionList = PDS_SELECTION_LIST;

//
// Object Picker Interfaces
//

//
// The main interface to the DS Object Picker, used to initialize it,
// invoke the dialog, and return the user's selections.
//

type
  IDsObjectPicker = interface (IUnknown)
  ['{0c87e64e-3b7a-11d2-b9e0-00c04fd8dbf7}']
    // Sets scope, filter, etc. for use with next invocation of dialog
    function Initialize(const pInitInfo: DSOP_INIT_INFO): HRESULT; stdcall;
    // Creates the modal DS Object Picker dialog.
    function InvokeDialog(hwndParent: HWND; out ppdoSelections: IDataObject): HRESULT; stdcall;
  end;
  {$EXTERNALSYM IDsObjectPicker}

implementation

end.
