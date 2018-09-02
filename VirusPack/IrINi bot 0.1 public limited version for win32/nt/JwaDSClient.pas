{******************************************************************************}
{                                                       	               }
{ Active Directory Display API interface Unit for Object Pascal                }
{                                                       	               }
{ Portions created by Microsoft are Copyright (C) 1995-2001 Microsoft          }
{ Corporation. All Rights Reserved.                                            }
{ 								               }
{ The original file is: dsclient.h, released June 2000. The original Pascal    }
{ code is: DsClient.pas, released December 2000. The initial developer of the  }
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

unit JwaDSClient;

{$WEAKPACKAGEUNIT}

{$HPPEMIT ''}
{$HPPEMIT '#include "dsclient.h"'}
{$HPPEMIT ''}

{$I WINDEFINES.INC}

interface

uses
  JwaAdsTLB, JwaWinType;

//---------------------------------------------------------------------------//
// CLSIDs exposed for the dsclient.
//---------------------------------------------------------------------------//

// this CLSID is used to signal that the DSOBJECTNAMEs structure originated
// for the Microsoft DS.

const
  CLSID_MicrosoftDS: TGUID = (
    D1:$fe1290f0; D2:$cfbd; D3:$11cf; D4:($a3, $30, $0, $aa, $0, $c1, $6e, $65));
  {$EXTERNALSYM CLSID_MicrosoftDS}

  //CLSID_DsFolder: = CLSID_MicrosoftDS;
  CLSID_DsFolder: TGUID = (
    D1:$fe1290f0; D2:$cfbd; D3:$11cf; D4:($a3, $30, $0, $aa, $0, $c1, $6e, $65));
  {$EXTERNALSYM CLSID_DsFolder}

// this is the CLSID used by clients to get the IShellExtInit, IPropSheetExt
// and IContextMenus exposed from dsuiext.dll.

  CLSID_DsPropertyPages: TGUID = (
    D1:$d45d530; D2:$764b; D3:$11d0; D4:($a1, $ca, $0, $aa, $0, $c1, $6e, $65));
  {$EXTERNALSYM CLSID_DsPropertyPages}

  CLSID_DsDomainTreeBrowser: TGUID = (
    D1:$1698790a; D2:$e2b4; D3:$11d0; D4:($b0, $b1, $00, $c0, $4f, $d8, $dc, $a6));
  {$EXTERNALSYM CLSID_DsDomainTreeBrowser}
  IID_IDsBrowseDomainTree: TGUID = (
    D1:$7cabcf1e; D2:$78f5; D3:$11d2; D4:($96, $c, $0, $c0, $4f, $a3, $1a, $86));
  {$EXTERNALSYM IID_IDsBrowseDomainTree}

  CLSID_DsDisplaySpecifier: TGUID = (
    D1:$1ab4a8c0; D2:$6a0b; D3:$11d2; D4:($ad, $49, $0, $c0, $4f, $a3, $1a, $86));
  {$EXTERNALSYM CLSID_DsDisplaySpecifier}
  //IID_IDsDisplaySpecifier = CLSID_DsDisplaySpecifier;
  IID_IDsDisplaySpecifier: TGUID = (
    D1:$1ab4a8c0; D2:$6a0b; D3:$11d2; D4:($ad, $49, $0, $c0, $4f, $a3, $1a, $86));
  {$EXTERNALSYM IID_IDsDisplaySpecifier}

  CLSID_DsFolderProperties: TGUID = (
    D1:$9e51e0d0; D2:$6e0f; D3:$11d2; D4:($96, $1, $0, $c0, $4f, $a3, $1a, $86));
  {$EXTERNALSYM CLSID_DsFolderProperties}
  //IID_IDsFolderProperties = CLSID_DsFolderProperties;
  IID_IDsFolderProperties: TGUID = (
    D1:$9e51e0d0; D2:$6e0f; D3:$11d2; D4:($96, $1, $0, $c0, $4f, $a3, $1a, $86));
  {$EXTERNALSYM IID_IDsFolderProperties}

// #include "activeds.h"

//---------------------------------------------------------------------------//
// Clipboard formats used within DSUI
//---------------------------------------------------------------------------//

//
// CF_DSOBJECTS
// ------------
//  This clipboard format defines the seleciton for an DS IShellFolder to the
//  shell extensions.   All strings are stored as BSTR's, and an offset == 0 
//  is used to indicate that the string is not present.
// 

const
  DSOBJECT_ISCONTAINER   = $00000001; // = 1 => object is a container
  {$EXTERNALSYM DSOBJECT_ISCONTAINER}
  DSOBJECT_READONLYPAGES = DWORD($80000000); // = 1 => read only pages
  {$EXTERNALSYM DSOBJECT_READONLYPAGES}

  DSPROVIDER_UNUSED_0 = $00000001;
  {$EXTERNALSYM DSPROVIDER_UNUSED_0}
  DSPROVIDER_UNUSED_1 = $00000002;
  {$EXTERNALSYM DSPROVIDER_UNUSED_1}
  DSPROVIDER_UNUSED_2 = $00000004;
  {$EXTERNALSYM DSPROVIDER_UNUSED_2}
  DSPROVIDER_UNUSED_3 = $00000008;
  {$EXTERNALSYM DSPROVIDER_UNUSED_3}
  DSPROVIDER_ADVANCED = $00000010; // = 1 => advanced mode
  {$EXTERNALSYM DSPROVIDER_ADVANCED}

  CFSTR_DSOBJECTNAMES = 'DsObjectNames';
  {$EXTERNALSYM CFSTR_DSOBJECTNAMES}

type
  LPDSOBJECT = ^DSOBJECT;
  {$EXTERNALSYM LPDSOBJECT}
  DSOBJECT = record
    dwFlags: DWORD; // item flags
    dwProviderFlags: DWORD; // flags for item provider
    offsetName: DWORD; // offset to ADS path of the object
    offsetClass: DWORD; // offset to object class name / == 0 not known
  end;
  {$EXTERNALSYM DSOBJECT}
  TDsObject = DSOBJECT;
  PDsObject = LPDSOBJECT;

  LPDSOBJECTNAMES = ^DSOBJECTNAMES;
  {$EXTERNALSYM LPDSOBJECTNAMES}
  DSOBJECTNAMES = record
    clsidNamespace: CLSID; // namespace identifier (indicates which namespace selection from)
    cItems: UINT; // number of objects
    aObjects: array [0..0] of DSOBJECT; // array of objects
  end;
  {$EXTERNALSYM DSOBJECTNAMES}
  TDsObjectNames = DSOBJECTNAMES;
  PDsObjectNames = LPDSOBJECTNAMES;

//
// CF_DSDISPLAYSPECOPTIONS
// -----------------------
//  When invoking an object referenced by a display specifier (context menu, property
//  page, etc) we call the IShellExtInit interface passing a IDataObject.  This data
//  object supports the CF_DSDISPLAYSPECOPTIONS format to give out configuration
//  informaiton about admin/shell invocation.
//
//  When interacting with dsuiext.dll the interfaces uses this clipboard format
//  to determine which display specifier attributes to address (admin/shell)
//  and pick up the values accordingly.  If no format is suppoted then
//  dsuiext.dll defaults to shell.
//

const
  CFSTR_DS_DISPLAY_SPEC_OPTIONS = 'DsDisplaySpecOptions';
  {$EXTERNALSYM CFSTR_DS_DISPLAY_SPEC_OPTIONS}
  CFSTR_DSDISPLAYSPECOPTIONS = CFSTR_DS_DISPLAY_SPEC_OPTIONS;
  {$EXTERNALSYM CFSTR_DSDISPLAYSPECOPTIONS}

type
  LPDSDISPLAYSPECOPTIONS = ^DSDISPLAYSPECOPTIONS;
  {$EXTERNALSYM LPDSDISPLAYSPECOPTIONS}
  _DSDISPLAYSPECOPTIONS = record
    dwSize: DWORD; // size of struct, for versioning
    dwFlags: DWORD; // invocation flags
    offsetAttribPrefix: DWORD; // offset to attribute prefix string.
    offsetUserName: DWORD; // offset to UNICODE user name
    offsetPassword: DWORD; // offset to UNICODE password
    offsetServer: DWORD;
    offsetServerConfigPath: DWORD;
  end;
  {$EXTERNALSYM _DSDISPLAYSPECOPTIONS}
  DSDISPLAYSPECOPTIONS = _DSDISPLAYSPECOPTIONS;
  {$EXTERNALSYM DSDISPLAYSPECOPTIONS}
  TDsDisplaySpecOptions = DSDISPLAYSPECOPTIONS;
  PDsDisplaySpecOptions = LPDSDISPLAYSPECOPTIONS;

const
  DS_PROP_SHELL_PREFIX = 'shell';
  {$EXTERNALSYM DS_PROP_SHELL_PREFIX}
  DS_PROP_ADMIN_PREFIX = 'admin';
  {$EXTERNALSYM DS_PROP_ADMIN_PREFIX}

  DSDSOF_HASUSERANDSERVERINFO = $00000001; // = 1 => user name/password are valid
  {$EXTERNALSYM DSDSOF_HASUSERANDSERVERINFO}
  DSDSOF_SIMPLEAUTHENTICATE   = $00000002; // = 1 => don't use secure authentication to DS
  {$EXTERNALSYM DSDSOF_SIMPLEAUTHENTICATE}
  DSDSOF_DONTSIGNSEAL         = $00000004; // = 1 => don't sign+seal when opening DS objects
  {$EXTERNALSYM DSDSOF_DONTSIGNSEAL}
  DSDSOF_DSAVAILABLE          = $40000000; // = 1 => ignore DS available checks
  {$EXTERNALSYM DSDSOF_DSAVAILABLE}

//
// CF_DSPROPERTYPAGEINFO
// ---------------------
//  When the property pages for an object are being displayed the parsed
//  display specifier string is passed to the page object via the IDataObject
//  in the following clipboard format.
//
//  Within the display specifier for a property page, the format for a
//  Win32 extension is "n,{clsid}[,bla...]" we take the "bla" section and
//  pass it down.
// 

  CFSTR_DSPROPERTYPAGEINFO = 'DsPropPageInfo';
  {$EXTERNALSYM CFSTR_DSPROPERTYPAGEINFO}

type
  LPDSPROPERTYPAGEINFO = ^DSPROPERTYPAGEINFO;
  {$EXTERNALSYM LPDSPROPERTYPAGEINFO}
  DSPROPERTYPAGEINFO = record
    offsetString: DWORD; // offset to UNICODE string
  end;
  {$EXTERNALSYM DSPROPERTYPAGEINFO}
  TDsPropertyPageInfo = DSPROPERTYPAGEINFO;
  PDsPropertyPageInfo = LPDSPROPERTYPAGEINFO;

//
// To sync property pages and the admin tools this message is broadcast
//

const
  DSPROP_ATTRCHANGED_MSG = 'DsPropAttrChanged';
  {$EXTERNALSYM DSPROP_ATTRCHANGED_MSG}

//---------------------------------------------------------------------------//


//---------------------------------------------------------------------------//
//
// IDsBrowseDomainTree
// ===================
//  This interface returns a list of the domains from a given computer name
//  (or the current computer name if none is specified).
//
//  NOTES:
//    1) The structure returned by ::GetDomains should be free'd using
//       FreeDomains.
//
//    2) ::BrowseTo allocates a string on exit, this is allocated using
//       CoTaskMemAlloc, and therefore should be free'd using CoTaskMemFree.
//
//---------------------------------------------------------------------------//

  DBDTF_RETURNFQDN         = $00000001; // if not set, pszNCName will be blank
  {$EXTERNALSYM DBDTF_RETURNFQDN}
  DBDTF_RETURNMIXEDDOMAINS = $00000002; // set it if you want downlevel trust domains too
  {$EXTERNALSYM DBDTF_RETURNMIXEDDOMAINS}
  DBDTF_RETURNEXTERNAL     = $00000004; // set it if you want external trust domains too
  {$EXTERNALSYM DBDTF_RETURNEXTERNAL}
  DBDTF_RETURNINBOUND      = $00000008; // set it if you want trusting domains
  {$EXTERNALSYM DBDTF_RETURNINBOUND}
  DBDTF_RETURNINOUTBOUND   = $00000010; // set it if you want both trusted and trusting domains
  {$EXTERNALSYM DBDTF_RETURNINOUTBOUND}

type
  PDOMAINDESC = ^DOMAINDESC;
  {$EXTERNALSYM PDOMAINDESC}
  _DOMAINDESC = record
    pszName: LPWSTR; // domain name (if no dns, use netbios)
    pszPath: LPWSTR; // set to blank
    pszNCName: LPWSTR; // FQDN, e.g.,DC=mydomain,DC=microsoft,DC=com
    pszTrustParent: LPWSTR; // parent domain name (if no dns, use netbios)
    pszObjectClass: LPWSTR; // Object class of the domain object referenced
    ulFlags: ULONG; // Flags, from DS_TRUSTED_DOMAINS.Flags
    fDownLevel: BOOL; // == 1 if downlevel domain
    pdChildList: PDOMAINDESC; // Children of this node
    pdNextSibling: PDOMAINDESC; // Siblings of this node
  end;
  {$EXTERNALSYM _DOMAINDESC}
  DOMAINDESC = _DOMAINDESC;
  {$EXTERNALSYM DOMAINDESC}
  TDomainDesc = DOMAINDESC;

  PDOMAIN_TREE = ^DOMAIN_TREE;
  {$EXTERNALSYM PDOMAIN_TREE}
  DOMAIN_TREE = record
    dsSize: DWORD;
    dwCount: DWORD;
    aDomains: array [0..1 - 1] of DOMAINDESC;
  end;
  {$EXTERNALSYM DOMAIN_TREE}
  DOMAINTREE = DOMAIN_TREE;
  {$EXTERNALSYM DOMAINTREE}
  TDomainTree = DOMAIN_TREE;
  PDomainTree = PDOMAIN_TREE;
  
  IDsBrowseDomainTree = interface (IUnknown)
  ['{7cabcf1e-78f5-11d2-960c-00c04fa31a86}']
    function BrowseTo(hwndParent: HWND; var ppszTargetPath: LPWSTR;
      dwFlags: DWORD): HRESULT; stdcall;
    function GetDomains(var ppDomainTree: PDOMAIN_TREE;
      dwFlags: DWORD): HRESULT; stdcall;
    function FreeDomains(var ppDomainTree: PDOMAIN_TREE): HRESULT; stdcall;
    function FlushCachedDomains: HRESULT; stdcall;
    function SetComputer(pszComputerName, pszUserName,
      pszPassword: LPCWSTR): HRESULT; stdcall;
  end;
  {$EXTERNALSYM IDsBrowseDomainTree}

//---------------------------------------------------------------------------//


//---------------------------------------------------------------------------//
//
// IDsDisplaySpecifier
// ===================
//  This interface gives client UI access to the display specifiers for 
//  specific attributes.
//
//---------------------------------------------------------------------------//

//
// IDsDisplaySpecifier::SetServer flags
//

const
  DSSSF_SIMPLEAUTHENTICATE = $00000001; // = 1 => don't use secure authentication to DS
  {$EXTERNALSYM DSSSF_SIMPLEAUTHENTICATE}
  DSSSF_DONTSIGNSEAL       = $00000002; // = 1 => don't use sign+seal when opening objects in the DS
  {$EXTERNALSYM DSSSF_DONTSIGNSEAL}
  DSSSF_DSAVAILABLE        = DWORD($80000000); // = 1 => ignore DS available checks
  {$EXTERNALSYM DSSSF_DSAVAILABLE}

//
// Flags for IDsDisplaySpecifier::GetIcon / GetIconLocation
//

  DSGIF_ISNORMAL           = $0000000; // = icon is in normal state (default)
  {$EXTERNALSYM DSGIF_ISNORMAL}
  DSGIF_ISOPEN             = $0000001; // = icon is in open state
  {$EXTERNALSYM DSGIF_ISOPEN}
  DSGIF_ISDISABLED         = $0000002; // = icon is in a disabled state
  {$EXTERNALSYM DSGIF_ISDISABLED}
  DSGIF_ISMASK             = $000000f;
  {$EXTERNALSYM DSGIF_ISMASK}
  DSGIF_GETDEFAULTICON     = $0000010; // = 1 => if no icon then get default (from shell32.dll)
  {$EXTERNALSYM DSGIF_GETDEFAULTICON}
  DSGIF_DEFAULTISCONTAINER = $0000020; // = 1 => if returning default icon, return it as a container
  {$EXTERNALSYM DSGIF_DEFAULTISCONTAINER}

//
// Flags for IDsDisplaySpecifier::IsClassContainer
//

  DSICCF_IGNORETREATASLEAF = $00000001; // = 1 => igore the "treatAsLeaf" and use only schema information
  {$EXTERNALSYM DSICCF_IGNORETREATASLEAF}

//
// Callback function used for IDsDisplaySpecifier::EnumClassAttributes
//

  DSECAF_NOTLISTED = $00000001; // = 1 => hide from the field drop down in the query UI
  {$EXTERNALSYM DSECAF_NOTLISTED}

type
  LPDSENUMATTRIBUTES = function (lParam: LPARAM; pszAttributeName: LPCWSTR;
    pszDisplayName: LPCWSTR; dwFlags: DWORD): HRESULT; stdcall;
  {$EXTERNALSYM LPDSENUMATTRIBUTES}
  TDsEnumAttributes = LPDSENUMATTRIBUTES;  

//
// IDsDisplaySpecifier::GetClassCreationInfo information
//

const
  DSCCIF_HASWIZARDDIALOG      = $00000001; // = 1 => return the wizard dialog CLSID
  {$EXTERNALSYM DSCCIF_HASWIZARDDIALOG}
  DSCCIF_HASWIZARDPRIMARYPAGE = $00000002; // = 1 => returning a primary wizard dlg CLSID
  {$EXTERNALSYM DSCCIF_HASWIZARDPRIMARYPAGE}

type
  LPDSCLASSCREATIONINFO = ^DSCLASSCREATIONINFO;
  {$EXTERNALSYM LPDSCLASSCREATIONINFO}
  DSCLASSCREATIONINFO = record
    dwFlags: DWORD;
    clsidWizardDialog: CLSID;
    clsidWizardPrimaryPage: CLSID;
    cWizardExtensions: DWORD; // how many extension CLSIDs?
    aWizardExtensions: array [0..0] of CLSID;
  end;
  {$EXTERNALSYM DSCLASSCREATIONINFO}
  TDsClassCreationInfo = DSCLASSCREATIONINFO;
  PDsClassCreationInfo = LPDSCLASSCREATIONINFO;

//
// IDsDisplaySpecifier - a COM object for interacting with display specifiers
//

  IDsDisplaySpecifier = interface (IUnknown)
  ['{1ab4a8c0-6a0b-11d2-ad49-00c04fa31a86}']
    function SetServer(pszServer, pszUserName, pszPassword: LPCWSTR;
      dwFlags: DWORD): HRESULT; stdcall;
    function SetLanguageID(langid: LANGID): HRESULT; stdcall;
    function GetDisplaySpecifier(pszObjectClass: LPCWSTR; riid: LPGUID;
      var ppv: Pointer): HRESULT; stdcall;
    function GetIconLocation(pszObjectClass: LPCWSTR; dwFlags: DWORD;
      pszBuffer: LPWSTR; cchBuffer: Integer; var presid: Integer): HRESULT; stdcall;
    function GetIcon(pszObjectClass: LPCWSTR; dwFlags: DWORD;
      cxIcon, cyIcon: Integer): HICON; stdcall;
    function GetFriendlyClassName(pszObjectClass: LPCWSTR; pszBuffer: LPWSTR;
      cchBuffer: Integer): HRESULT; stdcall;
    function GetFriendlyAttributeName(pszObjectClass, pszAttributeName,
      pszBuffer: LPCWSTR; cchBuffer: UINT): HRESULT; stdcall;
    function IsClassContainer(pszObjectClass, pszADsPath: LPCWSTR;
      dwFlags: DWORD): BOOL; stdcall;
    function GetClassCreationInfo(pszObjectClass: LPCWSTR;
      var ppdscci: LPDSCLASSCREATIONINFO): HRESULT; stdcall;
    function EnumClassAttributes(pszObjectClass: LPCWSTR;
      pcbEnum: LPDSENUMATTRIBUTES; lParam: LPARAM): HRESULT; stdcall;
    function GetAttributeADsType(pszAttributeName: LPCWSTR): ADSTYPEENUM; stdcall;
  end;
  {$EXTERNALSYM IDsDisplaySpecifier}

//---------------------------------------------------------------------------//
//
// DsBrowseForContainer
// --------------------
//  Provides a container browser similar to the SHBrowseForFolder, except
//  targetting the DS.
//
// In:
//  pInfo -> DSBROWSEINFO structure
//
// Out:
//  == IDOK/IDCANCEL depending on buttons, -1 if error
//
//---------------------------------------------------------------------------//

type
  BFFCALLBACK = function (hwnd: HWND; msg: UINT;
    lpData, lParam: LPARAM): Integer; stdcall;
  {$NODEFINE BFFCALLBACK}
  TBffCallback = BFFCALLBACK;

  PDSBROWSEINFOW = ^DSBROWSEINFOW;
  DSBROWSEINFOW = record
    cbStruct: DWORD; // size of structure in bytes
    hwndOwner: HWND; // dialog owner
    pszCaption: LPCWSTR; // dialog caption text (can be NULL)
    pszTitle: LPCWSTR; // displayed above the tree view control (can be NULL)
    pszRoot: LPCWSTR; // ADS path to root (NULL == root of DS namespace)
    pszPath: LPWSTR; // [in/out] initial selection & returned path (required)
    cchPath: ULONG; // size of pszPath buffer in characters
    dwFlags: DWORD;
    pfnCallback: BFFCALLBACK; // callback function (see SHBrowseForFolder)
    lParam: LPARAM; // passed to pfnCallback as lpUserData
    dwReturnFormat: DWORD; // ADS_FORMAT_* (default is ADS_FORMAT_X500_NO_SERVER)
    pUserName: LPCWSTR; // Username and Password to authenticate against DS with
    pPassword: LPCWSTR;
    pszObjectClass: LPWSTR; // UNICODE string for the object class
    cchObjectClass: ULONG;
  end;
  {$EXTERNALSYM DSBROWSEINFOW}
  TDsBrowseInfoW = DSBROWSEINFOW;

  PDSBROWSEINFOA = ^DSBROWSEINFOA;
  DSBROWSEINFOA = record
    cbStruct: DWORD;
    hwndOwner: HWND;
    pszCaption: LPCSTR;
    pszTitle: LPCSTR;
    pszRoot: LPCWSTR; // ADS paths are always UNICODE
    pszPath: LPWSTR; // ditto
    cchPath: ULONG;
    dwFlags: DWORD;
    pfnCallback: BFFCALLBACK;
    lParam: LPARAM;
    dwReturnFormat: DWORD;
    pUserName: LPCWSTR; // Username and Password to authenticate against DS with
    pPassword: LPCWSTR;
    pszObjectClass: LPWSTR; // object class of the selected object
    cchObjectClass: ULONG;
  end;
  {$EXTERNALSYM DSBROWSEINFOA}
  TDsBrowseInfoA = DSBROWSEINFOA;

{$IFDEF UNICODE}
  DSBROWSEINFO = DSBROWSEINFOW;
  {$EXTERNALSYM DSBROWSEINFO}
  PDSBROWSEINFO = PDSBROWSEINFOW;
  {$EXTERNALSYM PDSBROWSEINFO}
  TDsBrowseInfo = TDsBrowseInfoW;
{$ELSE}
  DSBROWSEINFO = DSBROWSEINFOA;
  {$EXTERNALSYM DSBROWSEINFO}
  PDSBROWSEINFO = PDSBROWSEINFOA;
  {$EXTERNALSYM PDSBROWSEINFO}
  TDsBrowseInfo = TDsBrowseInfoA;
{$ENDIF}

// DSBROWSEINFO flags

const
  DSBI_NOBUTTONS          = $00000001; // NOT TVS_HASBUTTONS
  {$EXTERNALSYM DSBI_NOBUTTONS}
  DSBI_NOLINES            = $00000002; // NOT TVS_HASLINES
  {$EXTERNALSYM DSBI_NOLINES}
  DSBI_NOLINESATROOT      = $00000004; // NOT TVS_LINESATROOT
  {$EXTERNALSYM DSBI_NOLINESATROOT}
  DSBI_CHECKBOXES         = $00000100; // TVS_CHECKBOXES
  {$EXTERNALSYM DSBI_CHECKBOXES}
  DSBI_NOROOT             = $00010000; // don't include pszRoot in tree (its children become top level nodes)
  {$EXTERNALSYM DSBI_NOROOT}
  DSBI_INCLUDEHIDDEN      = $00020000; // display hidden objects
  {$EXTERNALSYM DSBI_INCLUDEHIDDEN}
  DSBI_EXPANDONOPEN       = $00040000; // expand to the path specified in pszPath when opening the dialog
  {$EXTERNALSYM DSBI_EXPANDONOPEN}
  DSBI_ENTIREDIRECTORY    = $00090000; // browse the entire directory (defaults to having DSBI_NOROOT set)
  {$EXTERNALSYM DSBI_ENTIREDIRECTORY}
  DSBI_RETURN_FORMAT      = $00100000; // dwReturnFormat field is valid
  {$EXTERNALSYM DSBI_RETURN_FORMAT}
  DSBI_HASCREDENTIALS     = $00200000; // pUserName & pPassword are valid
  {$EXTERNALSYM DSBI_HASCREDENTIALS}
  DSBI_IGNORETREATASLEAF  = $00400000; // ignore the treat as leaf flag when calling IsClassContainer
  {$EXTERNALSYM DSBI_IGNORETREATASLEAF}
  DSBI_SIMPLEAUTHENTICATE = $00800000; // don't use secure authentication to DS
  {$EXTERNALSYM DSBI_SIMPLEAUTHENTICATE}
  DSBI_RETURNOBJECTCLASS  = $01000000; // return object class of selected object
  {$EXTERNALSYM DSBI_RETURNOBJECTCLASS}
  DSBI_DONTSIGNSEAL       = $02000000; // don't sign+seal communication with DS
  {$EXTERNALSYM DSBI_DONTSIGNSEAL}

  DSB_MAX_DISPLAYNAME_CHARS = 64;
  {$EXTERNALSYM DSB_MAX_DISPLAYNAME_CHARS}

type
  PDSBITEMW = ^DSBITEMW;
  DSBITEMW = record
    cbStruct: DWORD;
    pszADsPath: LPCWSTR; // ADS paths are always Unicode
    pszClass: LPCWSTR; // ADS properties are always Unicode
    dwMask: DWORD;
    dwState: DWORD;
    dwStateMask: DWORD;
    szDisplayName: array [0..DSB_MAX_DISPLAYNAME_CHARS - 1] of WCHAR;
    szIconLocation: array [0..MAX_PATH - 1] of WCHAR;
    iIconResID: Integer;
  end;
  {$EXTERNALSYM DSBITEMW}
  TDsBItemW = DSBITEMW;

  PDSBITEMA = ^DSBITEMA;
  DSBITEMA = record
    cbStruct: DWORD;
    pszADsPath: LPCWSTR; // ADS paths are always Unicode
    pszClass: LPCWSTR; // ADS properties are always Unicode
    dwMask: DWORD;
    dwState: DWORD;
    dwStateMask: DWORD;
    szDisplayName: array [0..DSB_MAX_DISPLAYNAME_CHARS - 1] of CHAR;
    szIconLocation: array [0..MAX_PATH - 1] of CHAR;
    iIconResID: Integer;
  end;
  {$EXTERNALSYM DSBITEMA}
  TDsBItemA = DSBITEMA;

{$IFDEF UNICODE}
  DSBITEM = DSBITEMW;
  {$EXTERNALSYM DSBITEM}
  PDSBITEM = PDSBITEMW;
  {$EXTERNALSYM PDSBITEM}
  TDsBItem = TDsBItemW;
{$ELSE}
  DSBITEM = DSBITEMA;
  {$EXTERNALSYM DSBITEM}
  PDSBITEM = PDSBITEMA;
  {$EXTERNALSYM PDSBITEM}
  TDsBItem = TDsBItemA;
{$ENDIF}

// DSBITEM mask flags

const
  DSBF_STATE        = $00000001;
  {$EXTERNALSYM DSBF_STATE}
  DSBF_ICONLOCATION = $00000002;
  {$EXTERNALSYM DSBF_ICONLOCATION}
  DSBF_DISPLAYNAME  = $00000004;
  {$EXTERNALSYM DSBF_DISPLAYNAME}

// DSBITEM state flags

  DSBS_CHECKED = $00000001;
  {$EXTERNALSYM DSBS_CHECKED}
  DSBS_HIDDEN  = $00000002;
  {$EXTERNALSYM DSBS_HIDDEN}
  DSBS_ROOT    = $00000004;
  {$EXTERNALSYM DSBS_ROOT}

//
// this message is sent to the callback to see if it wants to insert or modify
// the item that is about to be inserted into the view.
//

  DSBM_QUERYINSERTW = 100; // lParam = PDSBITEMW (state, icon & name may be modified). Return TRUE if handled.
  {$EXTERNALSYM DSBM_QUERYINSERTW}
  DSBM_QUERYINSERTA = 101; // lParam = PDSBITEMA (state, icon & name may be modified). Return TRUE if handled.
  {$EXTERNALSYM DSBM_QUERYINSERTA}

{$IFDEF UNICODE}
  DSBM_QUERYINSERT = DSBM_QUERYINSERTW;
  {$EXTERNALSYM DSBM_QUERYINSERT}
{$ELSE}
  DSBM_QUERYINSERT = DSBM_QUERYINSERTA;
  {$EXTERNALSYM DSBM_QUERYINSERT}
{$ENDIF}

//
// Called before we change the state of the icon (on tree collapse/expand)
//

  DSBM_CHANGEIMAGESTATE = 102; // lParam = adspath.  Return TRUE/FALSE top allow/disallow
  {$EXTERNALSYM DSBM_CHANGEIMAGESTATE}

//
// The dialog receives a WM_HELP
//

  DSBM_HELP = 103; // lParam == LPHELPINFO structure
  {$EXTERNALSYM DSBM_HELP}

//
// The dialog receives a WM_CONTEXTMENU, DSBID_xxx are the control ID's for this
// dialog so that you can display suitable help.
//

  DSBM_CONTEXTMENU = 104; // lParam == window handle to retrieve help for
  {$EXTERNALSYM DSBM_CONTEXTMENU}

//
// These are the control IDs for the controls in the dialog.   The callback can use
// these to modify the contents of the dialog as required.
//

  DSBID_BANNER        = 256;
  {$EXTERNALSYM DSBID_BANNER}
  DSBID_CONTAINERLIST = 257;
  {$EXTERNALSYM DSBID_CONTAINERLIST}

//
// API exported for browsing for containers.
//

function DsBrowseForContainerW(const pInfo: DSBROWSEINFOW): Integer; stdcall;
{$EXTERNALSYM DsBrowseForContainerW}
function DsBrowseForContainerA(const pInfo: DSBROWSEINFOA): Integer; stdcall;
{$EXTERNALSYM DsBrowseForContainerA}

{$IFDEF UNICODE}
function DsBrowseForContainer(const pInfo: DSBROWSEINFOW): Integer; stdcall;
{$EXTERNALSYM DsBrowseForContainer}
{$ELSE}
function DsBrowseForContainer(const pInfo: DSBROWSEINFOA): Integer; stdcall;
{$EXTERNALSYM DsBrowseForContainer}
{$ENDIF}

//BUGBUG: these are here to keep old clients building - remove soon

function DsGetIcon(dwFlags: DWORD; pszObjectClass: LPWSTR;
  cxImage, cyImage: Integer): HICON; stdcall;
{$EXTERNALSYM DsGetIcon}
procedure DsGetFriendlyClassName(pszObjectClass, pszBuffer: LPWSTR;
  cchBuffer: UINT); stdcall;
{$EXTERNALSYM DsGetFriendlyClassName}

implementation

const
  dsuiext = 'dsuiext.dll';


{$IFDEF DYNAMIC_LINK}
var
  _DsBrowseForContainerW: Pointer;

function DsBrowseForContainerW;
begin
  GetProcedureAddress(_DsBrowseForContainerW, dsuiext, 'DsBrowseForContainerW');
  asm
    mov esp, ebp
    pop ebp
    jmp [_DsBrowseForContainerW]
  end;
end;
{$ELSE}
function DsBrowseForContainerW; external dsuiext name 'DsBrowseForContainerW';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _DsBrowseForContainerA: Pointer;

function DsBrowseForContainerA;
begin
  GetProcedureAddress(_DsBrowseForContainerA, dsuiext, 'DsBrowseForContainerA');
  asm
    mov esp, ebp
    pop ebp
    jmp [_DsBrowseForContainerA]
  end;
end;
{$ELSE}
function DsBrowseForContainerA; external dsuiext name 'DsBrowseForContainerA';
{$ENDIF DYNAMIC_LINK}
{$IFDEF UNICODE}

{$IFDEF DYNAMIC_LINK}
var
  _DsBrowseForContainer: Pointer;

function DsBrowseForContainer;
begin
  GetProcedureAddress(_DsBrowseForContainer, dsuiext, 'DsBrowseForContainerW');
  asm
    mov esp, ebp
    pop ebp
    jmp [_DsBrowseForContainer]
  end;
end;
{$ELSE}
function DsBrowseForContainer; external dsuiext name 'DsBrowseForContainerW';
{$ENDIF DYNAMIC_LINK}
{$ELSE}

{$IFDEF DYNAMIC_LINK}
var
  _DsBrowseForContainer: Pointer;

function DsBrowseForContainer;
begin
  GetProcedureAddress(_DsBrowseForContainer, dsuiext, 'DsBrowseForContainerA');
  asm
    mov esp, ebp
    pop ebp
    jmp [_DsBrowseForContainer]
  end;
end;
{$ELSE}
function DsBrowseForContainer; external dsuiext name 'DsBrowseForContainerA';
{$ENDIF DYNAMIC_LINK}
{$ENDIF}


{$IFDEF DYNAMIC_LINK}
var
  _DsGetIcon: Pointer;

function DsGetIcon;
begin
  GetProcedureAddress(_DsGetIcon, dsuiext, 'DsGetIcon');
  asm
    mov esp, ebp
    pop ebp
    jmp [_DsGetIcon]
  end;
end;
{$ELSE}
function DsGetIcon; external dsuiext name 'DsGetIcon';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _DsGetFriendlyClassName: Pointer;

procedure DsGetFriendlyClassName;
begin
  GetProcedureAddress(_DsGetFriendlyClassName, dsuiext, 'DsGetFriendlyClassName');
  asm
    mov esp, ebp
    pop ebp
    jmp [_DsGetFriendlyClassName]
  end;
end;
{$ELSE}
procedure DsGetFriendlyClassName; external dsuiext name 'DsGetFriendlyClassName';
{$ENDIF DYNAMIC_LINK}

end.
