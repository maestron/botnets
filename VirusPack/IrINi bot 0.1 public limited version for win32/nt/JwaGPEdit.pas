{******************************************************************************}
{                                                       	               }
{ Group Policy API interface Unit for Object Pascal                            }
{                                                       	               }
{ Portions created by Microsoft are Copyright (C) 1995-2001 Microsoft          }
{ Corporation. All Rights Reserved.                                            }
{ 								               }
{ The original file is: gpedit.h, released June 2000. The original Pascal      }
{ code is: GPEdit.pas, released December 2000. The initial developer of the    }
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

unit JwaGPEdit;

{$WEAKPACKAGEUNIT}

{$HPPEMIT ''}
{$HPPEMIT '#include "GPEdit.h"'}
{$HPPEMIT ''}

{$I WINDEFINES.INC}

interface

uses
  ActiveX {TODO}, JwaPrSht, JwaWinType;

type
  LPOLESTR = POleStr;
  {$NODEFINE LPOLESTR}

//-----------------------------------------------------------------------------
//
// GPEDIT.H - Definitions and prototypes for Group Policy
//
// Copyright 1997-1999, Microsoft Corporation
//
//-----------------------------------------------------------------------------

//
// Terminology
//
// Group Policy Editor  -  The tool to view a Group Policy Object.
//
// Group Policy Object  -  A collection of administrator defined policies.
//                         Each Group Policy Object (GPO) has both file system
//                         and Active Directory storage available to it.
//
// IGPEInformation      -  The interface MMC Snapin Extensions use to
//                         talk to the Group Policy Editor.
//
// IGroupPolicyObject   -  The interface used to create/edit a GPO directly
//                         without going through the Group Policy Editor
//


//
// Group Policy Editor MMC SnapIn GUID
//
// {8FC0B734-A0E1-11d1-A7D3-0000F87571E3}

const
  CLSID_GPESnapIn: TGUID = (
    D1:$8fc0b734; D2:$a0e1; D3:$11d1; D4:($a7, $d3, $0, $0, $f8, $75, $71, $e3));
  {$EXTERNALSYM CLSID_GPESnapIn}


//
// Group Policy Editor node ids
//

//
// Computer Configuration\Windows Settings
// {8FC0B737-A0E1-11d1-A7D3-0000F87571E3}
//

  NODEID_Machine: TGUID = (
    D1:$8fc0b737; D2:$a0e1; D3:$11d1; D4:($a7, $d3, $0, $0, $f8, $75, $71, $e3));
  {$EXTERNALSYM NODEID_Machine}

//
// Computer Configuration\Software Settings
// {8FC0B73A-A0E1-11d1-A7D3-0000F87571E3}
//

  NODEID_MachineSWSettings: TGUID = (
    D1:$8fc0b73a; D2:$a0e1; D3:$11d1; D4:($a7, $d3, $0, $0, $f8, $75, $71, $e3));
  {$EXTERNALSYM NODEID_MachineSWSettings}

//
// User Configuration\Windows Settings
// {8FC0B738-A0E1-11d1-A7D3-0000F87571E3}
//

  NODEID_User: TGUID = (
    D1:$8fc0b738; D2:$a0e1; D3:$11d1; D4:($a7, $d3, $0, $0, $f8, $75, $71, $e3));
  {$EXTERNALSYM NODEID_User}

//
// User Configuration\Software Settings
// {8FC0B73C-A0E1-11d1-A7D3-0000F87571E3}
//

  NODEID_UserSWSettings: TGUID = (
    D1:$8fc0b73c; D2:$a0e1; D3:$11d1; D4:($a7, $d3, $0, $0, $f8, $75, $71, $e3));
  {$EXTERNALSYM NODEID_UserSWSettings}

//
// IGPEInformation interface id
//
// {8FC0B735-A0E1-11d1-A7D3-0000F87571E3}

  IID_IGPEInformation: TGUID = (
    D1:$8fc0b735; D2:$a0e1; D3:$11d1; D4:($a7, $d3, $0, $0, $f8, $75, $71, $e3));
  {$EXTERNALSYM IID_IGPEInformation}

//
// Group Policy Object class id
//
// {EA502722-A23D-11d1-A7D3-0000F87571E3}

  CLSID_GroupPolicyObject: TGUID = (
    D1:$ea502722; D2:$a23d; D3:$11d1; D4:($a7, $d3, $0, $0, $f8, $75, $71, $e3));
  {$EXTERNALSYM CLSID_GroupPolicyObject}

//
// Group Policy Object interface id
//
// {EA502723-A23D-11d1-A7D3-0000F87571E3}

  IID_IGroupPolicyObject: TGUID = (
    D1:$ea502723; D2:$a23d; D3:$11d1; D4:($a7, $d3, $0, $0, $f8, $75, $71, $e3));
  {$EXTERNALSYM IID_IGroupPolicyObject}

//
// GUID that identifies the registry extension
//

  REGISTRY_EXTENSION_GUID: TGUID = (
    D1:$35378EAC; D2:$683F; D3:$11D2; D4:($A8, $9A, $00, $C0, $4F, $BB, $CF, $A2));
  {$EXTERNALSYM IID_IGroupPolicyObject}

//========================================================================================
//
// Resultant Set of Policy node ids
//
//========================================================================================

//
// Resultant Set of Policy MMC SnapIn GUID
//
// {6DC3804B-7212-458D-ADB0-9A07E2AE1FA2}

  CLSID_RSOPSnapIn: TGUID = (
    D1:$6dc3804b; D2:$7212; D3:$458d; D4:($ad, $b0, $9a, $07, $e2, $ae, $1f, $a2));
  {$EXTERNALSYM CLSID_RSOPSnapIn}

//
// Computer Configuration\Windows Settings
// {BD4C1A2E-0B7A-4A62-A6B0-C0577539C97E}
//

  NODEID_RSOPMachine: TGUID = (
    D1:$bd4c1a2e; D2:$0b7a; D3:$4a62; D4:($a6, $b0, $c0, $57, $75, $39, $c9, $7e));
  {$EXTERNALSYM NODEID_RSOPMachine}

//
// Computer Configuration\Software Settings
// {6A76273E-EB8E-45DB-94C5-25663A5f2C1A}
//

  NODEID_RSOPMachineSWSettings: TGUID = (
    D1:$6a76273e; D2:$eb8e; D3:$45db; D4:($94, $c5, $25, $66, $3a, $5f, $2c, $1a));
  {$EXTERNALSYM NODEID_RSOPMachineSWSettings}

//
// User Configuration\Windows Settings
// {AB87364F-0CEC-4CD8-9BF8-898F34628FB8}
//

  NODEID_RSOPUser: TGUID = (
    D1:$ab87364f; D2:$0cec; D3:$4cd8; D4:($9b, $f8, $89, $8f, $34, $62, $8f, $b8));
  {$EXTERNALSYM NODEID_RSOPUser}

//
// User Configuration\Software Settings
// {E52C5CE3-FD27-4402-84DE-D9A5F2858910}
//

  NODEID_RSOPUserSWSettings: TGUID = (
    D1:$e52c5ce3; D2:$fd27; D3:$4402; D4:($84, $de, $d9, $a5, $f2, $85, $89, $10));
  {$EXTERNALSYM NODEID_RSOPUserSWSettings}

//
// IRSOPInformation interface id
//
// {9A5A81B5-D9C7-49EF-9D11-DDF50968C48D}

  IID_IRSOPInformation: TGUID = (
    D1:$9a5a81b5; D2:$d9c7; D3:$49ef; D4:($9d, $11, $dd, $f5, $09, $68, $c4, $8d));
  {$EXTERNALSYM IID_IRSOPInformation}

// #include <objbase.h>

//
// Group Policy Object Section flags
//

const
  GPO_SECTION_ROOT                = 0;  // Root
  {$EXTERNALSYM GPO_SECTION_ROOT}
  GPO_SECTION_USER                = 1;  // User
  {$EXTERNALSYM GPO_SECTION_USER}
  GPO_SECTION_MACHINE             = 2;  // Machine
  {$EXTERNALSYM GPO_SECTION_MACHINE}

//
// Group Policy Object types
//

type
  _GROUP_POLICY_OBJECT_TYPE = (
    GPOTypeLocal,                         // GPO on the local machine
    GPOTypeRemote,                        // GPO on a remote machine
    GPOTypeDS);                           // GPO in the Active Directory
  {$EXTERNALSYM _GROUP_POLICY_OBJECT_TYPE}
  GROUP_POLICY_OBJECT_TYPE = _GROUP_POLICY_OBJECT_TYPE;
  {$EXTERNALSYM GROUP_POLICY_OBJECT_TYPE}
  PGROUP_POLICY_OBJECT_TYPE = ^GROUP_POLICY_OBJECT_TYPE;
  {$EXTERNALSYM PGROUP_POLICY_OBJECT_TYPE}
  TGroupPolicyObjectType = GROUP_POLICY_OBJECT_TYPE;
  PGroupPolicyObjectType = PGROUP_POLICY_OBJECT_TYPE;

//
// Group Policy Hint types
//

  _GROUP_POLICY_HINT_TYPE = (
    GPHintUnknown,                          // No link information available
    GPHintMachine,                          // GPO linked to a machine (local or remote)
    GPHintSite,                             // GPO linked to a site
    GPHintDomain,                           // GPO linked to a domain
    GPHintOrganizationalUnit);              // GPO linked to a organizational unit
  {$EXTERNALSYM _GROUP_POLICY_HINT_TYPE}
  GROUP_POLICY_HINT_TYPE = _GROUP_POLICY_HINT_TYPE;
  {$EXTERNALSYM GROUP_POLICY_HINT_TYPE}
  PGROUP_POLICY_HINT_TYPE = ^GROUP_POLICY_HINT_TYPE;
  {$EXTERNALSYM PGROUP_POLICY_HINT_TYPE}
  TGroupPolicyHintType = GROUP_POLICY_HINT_TYPE;
  PGroupPolicyHintType = PGROUP_POLICY_HINT_TYPE;

  IGPEInformation = interface (IUnknown)
  ['{8FC0B735-A0E1-11d1-A7D3-0000F87571E3}']

    // *** IGPEInformation methods ***

    //
    // Returns the unique Group Policy Object name (a GUID)
    //
    // pszName contains the name on return
    // cchMaxLength is the max number of characters that can be stored in pszName
    //

    function GetName(pszName: LPOLESTR; cchMaxLength: Integer): HRESULT; stdcall;

    //
    // Returns the friendly display name for this Group Policy Object
    //
    // pszName contains the name on return
    // cchMaxLength is the max number of characters that can be stored in pszName
    //

    function GetDisplayName(pszName: LPOLESTR; cchMaxLength: Integer): HRESULT; stdcall;

    //
    // Returns a registry key handle for the requested section.  The returned
    // key is the root of the registry, not the Policies subkey.  To set / read
    // a value in the Policies subkey, you will need to call RegOpenKeyEx to
    // open Software\Policies subkey first.
    //
    // The handle has been opened with ALL ACCESS rights.  Call RegCloseKey
    // on the handle when finished.
    //
    // dwSection is either GPO_SECTION_USER or GPO_SECTION_MACHINE
    // hKey contains the registry key on return
    //

    function GetRegistryKey(dwSection: DWORD; var hKey: HKEY): HRESULT; stdcall;

    //
    // Returns the Active Directory path to the root of the request section.
    // The path is in ADSI name format.
    //
    // dwSection is one of the GPO_SECTION_* flags
    // pszPath contains the path on return
    // cchMaxPath is the max number of characters that can be stored in pszPath
    //

    function GetDSPath(dwSection: DWORD; pszPath: LPOLESTR; cchMaxPath: Integer): HRESULT; stdcall;

    //
    // Returns the UNC path to the root of the requested section.
    //
    // dwSection is one of the GPO_SECTION_* flags
    // pszPath contains the path on return
    // cchMaxPath is the number of characters that can be stored in pszPath.
    //

    function GetFileSysPath(dwSection: DWORD; pszPath: LPOLESTR; cchMaxPath: Integer): HRESULT; stdcall;

    //
    // Returns the user preferences (options)
    //
    // Currently, there are no options defined.  This is reserved for future use.
    //
    // dwOptions receives a bitmask value
    //

    function GetOptions(var dwOptions: DWORD): HRESULT; stdcall;

    //
    // Returns the type of GPO being edited.
    //
    // The three types are:  a GPO in the Active Directory, the GPO on the local machine,
    // and the GPO on a remote machine.
    //
    // Machine GPOs only have file system storage (no Active Directory storage available).
    // If GetDSPath is called for a machine GPO, the function will succeed
    // and the returned buffer will be the empty string ""
    //
    // Active Directory GPOs have both file system and Active Directory storage available to them.
    //
    // gpoType receives one of the type flags listed above.
    //

    function GetType(var gpoType: GROUP_POLICY_OBJECT_TYPE): HRESULT; stdcall;

    //
    // Returns the type of Active Directory object (or machine) that could be linked to
    // this GPO
    //
    // This is a hint api only.  The GPE does not know which Active Directory objects are
    // linked to a particular GPO, but it can offer a hint based upon how the
    // user started the GPE.
    //
    // Use this method with great caution.  Some extensions might want to
    // customize their user interface based upon the scoping for this GPO,
    // but it is easy to offer the wrong namespace.  Best advice is to
    // always offer your full user interface, but if you choose to use this
    // method, always offer your full user interface if you recieve the
    // unknown hint back.
    //
    // gpHint receives one of the hint flags listed above.
    //

    function GetHint(var gpHint: GROUP_POLICY_HINT_TYPE): HRESULT; stdcall;

    //
    // Informs the Group Policy Editor that policy settings have changed.
    // Extensions MUST call this methold every time a change is made
    // to a Group Policy Object.
    //
    // bMachine specifies if machine or user policy has changed.
    // bAdd specifies whether this is an add or delete.
    // pGuidExtension is the guid or unique name of extension that
    //    will process this GPO.
    // pGuidSnapin is the guid or unique name of snapin that is making
    //    this call
    //

    function PolicyChanged(bMachine, bAdd: BOOL; const pGuidExtension, pGuidSnapin: GUID): HRESULT; stdcall;

  end;
  {$EXTERNALSYM IGPEInformation}

  LPGPEINFORMATION = ^IGPEInformation;
  {$EXTERNALSYM LPGPEINFORMATION}

//
// Group Policy Object open / creation flags
//

const
  GPO_OPEN_LOAD_REGISTRY     = $00000001;  // Load the registry files
  {$EXTERNALSYM GPO_OPEN_LOAD_REGISTRY}
  GPO_OPEN_READ_ONLY         = $00000002;  // Open the GPO as read only
  {$EXTERNALSYM GPO_OPEN_READ_ONLY}

//
// Group Policy Object option flags
//

const
  GPO_OPTION_DISABLE_USER    = $00000001;  // The user portion of this GPO is disabled
  {$EXTERNALSYM GPO_OPTION_DISABLE_USER}
  GPO_OPTION_DISABLE_MACHINE = $00000002;  // The machine portion of this GPO is disabled
  {$EXTERNALSYM GPO_OPTION_DISABLE_MACHINE}

type
  IGroupPolicyObject = interface (IUnknown)
  ['{EA502723-A23D-11d1-A7D3-0000F87571E3}']

    // *** IGroupPolicyObject methods ***

    //
    // Creates a new GPO in the Active Directory with the given friendly name
    // and opens it via OpenDSGPO().  If pszDomainName contains a domain
    // controller name, the GPO will be created on that DC.  If it does not
    // specify a domain controller name, the method will select a DC on
    // the callers behalf.
    //
    // pszDomainName contains the ADSI path of the domain root
    // pszDisplayName contains the friendly display name
    // dwFlags is a bitmask of GPO open / creation flags listed above
    //

    function New(pszDomainName, pszDisplayName: LPOLESTR; dwFlags: DWORD): HRESULT; stdcall;

    //
    // Opens the specified Group Policy Object in the Active Directory
    // based upon the passed in flags.  If pszPath contains a domain
    // controller name, the GPO will be opened on that DC.  If it does
    // not contain a domain controller name, the method will select a
    // DC on the callers behalf.  If the registry is not loaded,
    // GetRegistryKey() will return E_FAIL.
    //
    // pszPath contains the ADSI path to the GPO to open
    // dwFlags is a bitmask of GPO open / creation flags listed above
    //

    function OpenDSGPO(pszPath: LPOLESTR; dwFlags: DWORD): HRESULT; stdcall;

    //
    // Opens the default Group Policy Object on this machine with the
    // dwFlags options listed above.  If the registry is not loaded,
    // GetRegistryKey() will return E_FAIL.
    //
    // dwFlags is a bitmask of GPO open / creation flags listed above
    //

    function OpenLocalMachineGPO(dwFlags: DWORD): HRESULT; stdcall;

    //
    // Opens the default Group Policy Object on a remote machine with the
    // dwFlags options listed above.  If the registry is not loaded,
    // GetRegistryKey() will return E_FAIL.
    //
    // pszComputerName contains the machine name in \\machine format
    // dwFlags is a bitmask of GPO open / creation flags listed above
    //

    function OpenRemoteMachineGPO(pszComputerName: LPOLESTR; dwFlags: DWORD): HRESULT; stdcall;

    //
    // Flushes the registry settings to disk and updates the revision
    // number of the GPO.
    //
    // bMachine specifies if machine or user should be saved.
    // bAdd specifies whether this is an add or delete.
    // pGuidExtension is the guid or unique name of extension that
    //    will process this GPO.
    // pGuid is a guid
    //

    function Save(bMachine, bAdd: BOOL; const pGuidExtension, pGuid: GUID): HRESULT; stdcall;

    //
    // Deletes this Group Policy Object.
    //
    // After calling this method, no other methods are valid to call
    // since the data will have been deleted.
    //

    function Delete: HRESULT; stdcall;

    //
    // Returns the unique Group Policy Object name
    //
    // For Active Directory policy objects, this is a GUID
    // For the local policy object, it is the string "Local"
    // For remote policy objects, it is the computername
    //
    // pszName contains the name on return
    // cchMaxLength is the max number of characters that can be stored in pszName
    //

    function GetName(pszName: LPOLESTR; cchMaxLength: Integer): HRESULT; stdcall;

    //
    // Returns the friendly display name for this Group Policy Object
    //
    // pszName contains the name on return
    // cchMaxLength is the max number of characters that can be stored in pszName
    //

    function GetDisplayName(pszName: LPOLESTR; cchMaxLength: Integer): HRESULT; stdcall;

    //
    // Sets the friendly display name for this Group Policy Object
    //
    // pszName is the new display name
    //

    function SetDisplayName(pszName: LPOLESTR): HRESULT; stdcall;

    //
    // Returns the path to the Group Policy Object
    //
    //
    // If the GPO is an Active Directory object, the path is in ADSI name format.
    // If the GPO is a machine object, it is a file system path
    //
    // pszPath contains the path on return
    // cchMaxPath is the max number of characters that can be stored in pszPath
    //

    function GetPath(pszPath: LPOLESTR; cchMaxPath: Integer): HRESULT; stdcall;

    //
    // Returns the Active Directory path to the root of the request section.
    // The path is in DN name format.
    //
    // dwSection is one of the GPO_SECTION_* flags
    // pszPath contains the path on return
    // cchMaxPath is the max number of characters that can be stored in pszPath
    //

    function GetDSPath(dwSection: DWORD; pszPath: LPOLESTR; cchMaxPath: Integer): HRESULT; stdcall;

    //
    // Returns the UNC path to the root of the requested section.
    //
    // dwSection is one of the GPO_SECTION_* flags
    // pszPath contains the path on return
    // cchMaxPath is the number of characters that can be stored in pszPath.
    //

    function GetFileSysPath(dwSection: DWORD; pszPath: LPOLESTR; cchMaxPath: Integer): HRESULT; stdcall;

    //
    // Returns a registry key handle for the requested section.  The returned
    // key is the root of the registry, not the Policies subkey.  To set / read
    // a value in the Policies subkey, you will need to call RegOpenKeyEx to
    // open Software\Policies subkey first.
    //
    // The handle has been opened with ALL ACCESS rights.  Call RegCloseKey
    // on the handle when finished.
    //
    // If the GPO was loaded / created without the registry being loaded
    // this method will return E_FAIL.
    //
    // dwSection is either GPO_SECTION_USER or GPO_SECTION_MACHINE
    // hKey contains the registry key on return
    //

    function GetRegistryKey(dwSection: DWORD; var hKey: HKEY): HRESULT; stdcall;

    //
    // Returns any options for this Group Policy Object
    //
    // dwOptions receives the GPO_OPTION_* flags
    //

    function GetOptions(var dwOptions: DWORD): HRESULT; stdcall;

    //
    // Sets any options for this Group Policy Object
    //
    // This method sets any options for this GPO.  To change
    // an option, that flag must be set in the mask field.
    // If the flag is in the mask field, then the dwOptions
    // field is read for the current state.
    //
    // For example:  to disable the GPO, make this call
    //
    //    SetOptions (GPO_OPTION_DISABLED, GPO_OPTION_DISABLED);
    //
    // dwOptions specifies one or more GPO_OPTION_* flags
    // dwMask specificies which of the dwOptions to change
    //

    function SetOptions(dwOptions, dwMask: DWORD): HRESULT; stdcall;

    //
    // Returns the type of GPO being edited.
    //
    // The three types are:  a GPO in the Active Directory, the GPO on the local machine,
    // and the GPO on a remote machine.
    //
    // Machine GPOs only have file system storage (no Active Directory storage available).
    // If GetDSPath is called for a machine GPO, the function will succeed
    // and the returned buffer will be the empty string ""
    //
    // Active Directory GPOs have both file system and Active Directory storage available to them.
    //
    // gpoType receives one of the type flags
    //

    function GetType(var gpoType: GROUP_POLICY_OBJECT_TYPE): HRESULT; stdcall;

    //
    // Returns the machine name of the remote GPO
    //
    // This method returns the name passed to OpenRemoteMachineGPO.
    //
    // pszName contains the name on return
    // cchMaxLength is the max number of characters that can be stored in pszName
    //

    function GetMachineName(pszName: LPOLESTR; cchMaxLength: Integer): HRESULT; stdcall;

    //
    // Returns an array of property sheet pages and the number of pages
    // in the array
    //
    // Note, this method will allocate memory for the array with
    // LocalAlloc.  When finished, the caller should free the array
    // with LocalFree
    //
    // hPages address of the pointer for the array of property sheet pages
    // uPageCount receives the number of pages in the array
    //

    function GetPropertySheetPages(var hPages: PHPROPSHEETPAGE; var uPageCount: UINT): HRESULT; stdcall;
    
  end;
  {$EXTERNALSYM IGroupPolicyObject}

  LPGROUPPOLICYOBJECT = ^IGroupPolicyObject;
  {$EXTERNALSYM LPGROUPPOLICYOBJECT}

//
// RSOP flags
//

const
  RSOP_INFO_FLAG_DIAGNOSTIC_MODE = $00000001; // Running in diagnostic mode vs planning mode
  {$EXTERNALSYM RSOP_INFO_FLAG_DIAGNOSTIC_MODE}

type
  IRSOPInformation = interface (IUnknown)
  ['{9A5A81B5-D9C7-49EF-9D11-DDF50968C48D}']

    // *** IRSOPInformation methods ***

    //
    // Returns the namespace for the RSOP data
    //
    // dwSection is either GPO_SECTION_USER or GPO_SECTION_MACHINE
    // pszName contains the namespace on return
    // cchMaxLength is the max number of characters that can be stored in pszName
    //

    function GetNamespace(dwSection: DWORD; pszName: LPOLESTR; cchMaxLength: Integer): HRESULT; stdcall;

    //
    // Returns information about the RSOP session
    //
    // pdwFlags points to a DWORD which contains the flags on return
    //

    function GetFlags(var pdwFlags: DWORD): HRESULT; stdcall;

    //
    // Returns the event log text for a specific entry
    //
    // lpEventSource - event log source name
    // lpEventLogName - event log name
    // lpEventTime - event log time in WMI datetime format
    // dwEventID - event ID
    // lpText - Receives a pointer to a buffer containing the text.
    //          The caller should free this buffer with CoTaskMemFree.
    //

    function GetEventLogEntryText(pszEventSource, pszEventLogName, pszEventTime: LPOLESTR;
      dwEventID: DWORD; out ppszText: LPOLESTR): HRESULT; stdcall;

  end;
  {$EXTERNALSYM IRSOPInformation}

  LPRSOPINFORMATION = IRSOPInformation;
  {$EXTERNALSYM LPRSOPINFORMATION}

//=============================================================================
//
// CreateGPOLink
//
// Creates a link to a GPO for the specified Site, Domain, or Organizational Unit
//
// lpGPO         - ADSI path to the GPO
// lpContainer   - ADSI path to the Site, Domain, or Organizational Unit
// fHighPriority - Create the link as the highest or lowest priority
//
// Returns:  S_OK if successful
//
//=============================================================================

function CreateGPOLink(lpGPO, lpContainer: LPOLESTR; fHighPriority: BOOL): HRESULT; stdcall;
{$EXTERNALSYM CreateGPOLink}


//=============================================================================
//
// DeleteGPOLink
//
// Deletes a link to a GPO for the specified Site, Domain, or Organizational Unit
//
// lpGPO         - ADSI path to the GPO
// lpContainer   - ADSI path to the Site, Domain, or Organizational Unit
//
// Returns:  S_OK if successful
//
//=============================================================================

function DeleteGPOLink(lpGPO, lpContainer: LPOLESTR): HRESULT; stdcall;
{$EXTERNALSYM DeleteGPOLink}

//=============================================================================
//
// DeleteAllGPOLinks
//
// Deletes all GPO links for the specified Site, Domain, or Organizational Unit
//
// lpContainer   - ADSI path to the Site, Domain, or Organizational Unit
//
// Returns:  S_OK if successful
//
//=============================================================================

function DeleteAllGPOLinks(lpContainer: LPOLESTR): HRESULT; stdcall;
{$EXTERNALSYM DeleteAllGPOLinks}

//=============================================================================
//
// BrowseForGPO
//
// Displays the GPO browser dialog
//
// lpBrowseInfo   - Address of a GPOBROWSEINFO structure
//
// Returns:  S_OK if successful
//
//=============================================================================

//
// Flags passed in the dwFlags field of the GPOBROWSEINFO structure
//

const
  GPO_BROWSE_DISABLENEW          = $00000001;   // Disables the New GPO functionality on all pages except "All"
  {$EXTERNALSYM GPO_BROWSE_DISABLENEW}
  GPO_BROWSE_NOCOMPUTERS         = $00000002;   // Removes the Computers tab
  {$EXTERNALSYM GPO_BROWSE_NOCOMPUTERS}
  GPO_BROWSE_NODSGPOS            = $00000004;   // Removes the Domain/OU and Sites tabs
  {$EXTERNALSYM GPO_BROWSE_NODSGPOS}
  GPO_BROWSE_OPENBUTTON          = $00000008;   // Change the Ok button to say Open
  {$EXTERNALSYM GPO_BROWSE_OPENBUTTON}
  GPO_BROWSE_INITTOALL           = $00000010;   // Initialize the dialog focused on the All pane
  {$EXTERNALSYM GPO_BROWSE_INITTOALL}

type
  tag_GPOBROWSEINFO = record
    dwSize: DWORD;                      // [in] Initialized to the size of this structure
    dwFlags: DWORD;                     // [in] Flags defined above
    hwndOwner: HWND;                    // [in] Parent window handle (can be NULL)
    lpTitle: LPOLESTR;                  // [in] Title bar text.  If NULL, "Browse for a Group Policy Object" will be the default text
    lpInitialOU: LPOLESTR;              // [in] Initial Domain/Organizational Unit to open focus on
    lpDSPath: LPOLESTR;                 // [in/out] Pointer to the buffer that receives the Active Directory GPO path
    dwDSPathSize: DWORD;                // [in] Size in characters of buffer given in lpDSPath
    lpName: LPOLESTR;                   // [in/out] Pointer to a buffer that receives either the computer name or
                                        //          the friendly name of the GPO (can be NULL)
    dwNameSize: DWORD;                  // [in] Size in characters of buffer given in lpName
    gpoType: GROUP_POLICY_OBJECT_TYPE;  // [out] Specifies the type of GPO
    gpoHint: GROUP_POLICY_HINT_TYPE;    // [out] Specifies a hint of the GPO association
  end;
  {$EXTERNALSYM tag_GPOBROWSEINFO}
  GPOBROWSEINFO = tag_GPOBROWSEINFO;
  {$EXTERNALSYM GPOBROWSEINFO}
  LPGPOBROWSEINFO = ^GPOBROWSEINFO;
  TGpoBrowseInfo = GPOBROWSEINFO;
  PGpoBrowseInfo = LPGPOBROWSEINFO;

function BrowseForGPO(var lpBrowseInfo: GPOBROWSEINFO): HRESULT; stdcall;
{$EXTERNALSYM BrowseForGPO}

//=============================================================================
//
// ImportRSoPData
//
// Imports a data file generated by ExportRSoPData
//
// lpNameSpace   - Namespace to place the data in
// lpFileName    - Filename containing the data
//
// Returns:  S_OK if successful
//
// Notes:    The namespace specified in lpNameSpace must exist prior to calling
//           this function.
//
//=============================================================================

function ImportRSoPData(lpNameSpace, lpFileName: LPOLESTR): HRESULT; stdcall;
{$EXTERNALSYM ImportRSoPData}

//=============================================================================
//
// ExportRSoPData
//
// Exports a WBEM namespace containing RSoP information to a data file.
// This data file can be imported to a WBEM namespace using ImportRSoPData.
//
// lpNameSpace   - Namespace to read the data from
// lpFileName    - Filename to receive the data
//
// Returns:  S_OK if successful
//
// Notes:    This function should be called twice.  Once for the user data
//           and once for the computer data.
//
//=============================================================================

function ExportRSoPData(lpNameSpace, lpFileName: LPOLESTR): HRESULT; stdcall;
{$EXTERNALSYM ExportRSoPData}

implementation

const
  gpeditlib = 'gpedit.dll';


{$IFDEF DYNAMIC_LINK}
var
  _CreateGPOLink: Pointer;

function CreateGPOLink;
begin
  GetProcedureAddress(_CreateGPOLink, gpeditlib, 'CreateGPOLink');
  asm
    mov esp, ebp
    pop ebp
    jmp [_CreateGPOLink]
  end;
end;
{$ELSE}
function CreateGPOLink; external gpeditlib name 'CreateGPOLink';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _DeleteGPOLink: Pointer;

function DeleteGPOLink;
begin
  GetProcedureAddress(_DeleteGPOLink, gpeditlib, 'DeleteGPOLink');
  asm
    mov esp, ebp
    pop ebp
    jmp [_DeleteGPOLink]
  end;
end;
{$ELSE}
function DeleteGPOLink; external gpeditlib name 'DeleteGPOLink';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _DeleteAllGPOLinks: Pointer;

function DeleteAllGPOLinks;
begin
  GetProcedureAddress(_DeleteAllGPOLinks, gpeditlib, 'DeleteAllGPOLinks');
  asm
    mov esp, ebp
    pop ebp
    jmp [_DeleteAllGPOLinks]
  end;
end;
{$ELSE}
function DeleteAllGPOLinks; external gpeditlib name 'DeleteAllGPOLinks';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _BrowseForGPO: Pointer;

function BrowseForGPO;
begin
  GetProcedureAddress(_BrowseForGPO, gpeditlib, 'BrowseForGPO');
  asm
    mov esp, ebp
    pop ebp
    jmp [_BrowseForGPO]
  end;
end;
{$ELSE}
function BrowseForGPO; external gpeditlib name 'BrowseForGPO';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _ImportRSoPData: Pointer;

function ImportRSoPData;
begin
  GetProcedureAddress(_ImportRSoPData, gpeditlib, 'ImportRSoPData');
  asm
    mov esp, ebp
    pop ebp
    jmp [_ImportRSoPData]
  end;
end;
{$ELSE}
function ImportRSoPData; external gpeditlib name 'ImportRSoPData';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _ExportRSoPData: Pointer;

function ExportRSoPData;
begin
  GetProcedureAddress(_ExportRSoPData, gpeditlib, 'ExportRSoPData');
  asm
    mov esp, ebp
    pop ebp
    jmp [_ExportRSoPData]
  end;
end;
{$ELSE}
function ExportRSoPData; external gpeditlib name 'ExportRSoPData';
{$ENDIF DYNAMIC_LINK}

end.
