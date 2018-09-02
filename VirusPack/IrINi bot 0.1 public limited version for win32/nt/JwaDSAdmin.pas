{******************************************************************************}
{                                                       	               }
{ Directory Services Admin API interface Unit for Object Pascal                }
{                                                       	               }
{ Portions created by Microsoft are Copyright (C) 1995-2001 Microsoft          }
{ Corporation. All Rights Reserved.                                            }
{ 								               }
{ The original file is: dsadmin.h, released June 2000. The original Pascal     }
{ code is: dsadmin.pas, released December 2000. The initial developer of the   }
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

unit JwaDSAdmin;

{$WEAKPACKAGEUNIT}

{$HPPEMIT ''}
{$HPPEMIT '#include "dsadmin.h"'}
{$HPPEMIT ''}

{$I WINDEFINES.INC}

interface

uses
  ActiveX {TODO}, JwaAdsTLB, JwaPrSht, JwaWinType;

//
// CoClass for the Object creation dialog object
//
// {E301A009-F901-11d2-82B9-00C04F68928B}

const
  CLSID_DsAdminCreateObj: TGUID = (
    D1:$e301a009; D2:$f901; D3:$11d2; D4:($82, $b9, $0, $c0, $4f, $68, $92, $8b));
  {$EXTERNALSYM CLSID_DsAdminCreateObj}

//
// Interface GUIDs
//

// {53554A38-F902-11d2-82B9-00C04F68928B}

  IID_IDsAdminCreateObj: TGUID = (
    D1:$53554a38; D2:$f902; D3:$11d2; D4:($82, $b9, $0, $c0, $4f, $68, $92, $8b));
  {$EXTERNALSYM IID_IDsAdminCreateObj}

// {F2573587-E6FC-11d2-82AF-00C04F68928B}

  IID_IDsAdminNewObj: TGUID = (
    D1:$f2573587; D2:$e6fc; D3:$11d2; D4:($82, $af, $0, $c0, $4f, $68, $92, $8b));
  {$EXTERNALSYM IID_IDsAdminNewObj}

// {BE2B487E-F904-11d2-82B9-00C04F68928B}

  IID_IDsAdminNewObjPrimarySite: TGUID = (
    D1:$be2b487e; D2:$f904; D3:$11d2; D4:($82, $b9, $0, $c0, $4f, $68, $92, $8b));
  {$EXTERNALSYM IID_IDsAdminNewObjPrimarySite}


// {6088EAE2-E7BF-11d2-82AF-00C04F68928B}

  IID_IDsAdminNewObjExt: TGUID = (
    D1:$6088eae2; D2:$e7bf; D3:$11d2; D4:($82, $af, $0, $c0, $4f, $68, $92, $8b));
  {$EXTERNALSYM IID_IDsAdminNewObjExt}

// {E4A2B8B3-5A18-11d2-97C1-00A0C9A06D2D}

  IID_IDsAdminNotifyHandler: TGUID = (
    D1:$e4a2b8b3; D2:$5a18; D3:$11d2; D4:($97, $c1, $0, $a0, $c9, $a0, $6d, $2d));
  {$EXTERNALSYM IID_IDsAdminNotifyHandler}

// ----------------------------------------------------------------------------
// 
// Interface: IDsAdminCreateObj
//  
// Implemented by the object (implemented by the system) CLSID_DsAdminCreateObj
//
// Used by: any client needing to invoke the creation UI
//

type
  IDsAdminCreateObj = interface (IUnknown)
  ['{53554A38-F902-11d2-82B9-00C04F68928B}']
    function Initialize(pADsContainerObj: IADsContainer; pADsCopySource: IADS;
      lpszClassName: LPCWSTR): HRESULT; stdcall;
    function CreateModal(hwndParent: HWND; out ppADsObj: IADS): HRESULT; stdcall;
  end;
  {$EXTERNALSYM IDsAdminCreateObj}

//---------------------------------------------------------------------------
//
// Interface: IDsAdminNewObj
// 
// Implemented by: DS Admin
//
// Used by: creation extension in proc server (both primary and regular)
//

  IDsAdminNewObj = interface (IUnknown)
  ['{F2573587-E6FC-11d2-82AF-00C04F68928B}']
    function SetButtons(nCurrIndex: ULONG; bValid: BOOL): HRESULT; stdcall;
    function GetPageCounts(var pnTotal, pnStartIndex: LONG): HRESULT; stdcall;
  end;
  {$EXTERNALSYM IDsAdminNewObj}

//---------------------------------------------------------------------------
//
// Interface: IDsAdminNewObjPrimarySite
// 
// Implemented by: DS Admin
//
// Used by: creation extension in proc server (primary only)
//

  IDsAdminNewObjPrimarySite = interface (IUnknown)
  ['{BE2B487E-F904-11d2-82B9-00C04F68928B}']
    function CreateNew(pszName: LPCWSTR): HRESULT; stdcall;
    function Commit: HRESULT; stdcall;
  end;
  {$EXTERNALSYM IDsAdminNewObjPrimarySite}

//
// struct passed to IDsAdminNewObjExt::Initialize()
//
// it contains information regarding UI look
//

  LPDSA_NEWOBJ_DISPINFO = ^DSA_NEWOBJ_DISPINFO;
  {$EXTERNALSYM LPDSA_NEWOBJ_DISPINFO}
  DSA_NEWOBJ_DISPINFO = record
    dwSize: DWORD;               // size of struct, for versioning
    hObjClassIcon: HICON;        // class icon for the object to be created
    lpszWizTitle: LPWSTR;        // title of the wizard
    lpszContDisplayName: LPWSTR; // container display name (canonical name)
  end;
  {$EXTERNALSYM DSA_NEWOBJ_DISPINFO}
  TDsaNewObjDispInfo = DSA_NEWOBJ_DISPINFO;
  PDsaNewObjDispInfo = LPDSA_NEWOBJ_DISPINFO;

//
// context flags passed to IDsAdminNewObjExt::OnError() and to IDsAdminNewObjExt::WriteData()
//

const
  DSA_NEWOBJ_CTX_PRECOMMIT  = $00000001; // before SetInfo()
  {$EXTERNALSYM DSA_NEWOBJ_CTX_PRECOMMIT}
  DSA_NEWOBJ_CTX_COMMIT     = $00000002; // SetInfo(), commit phase
  {$EXTERNALSYM DSA_NEWOBJ_CTX_COMMIT}
  DSA_NEWOBJ_CTX_POSTCOMMIT = $00000003; // after SetInfo()
  {$EXTERNALSYM DSA_NEWOBJ_CTX_POSTCOMMIT}
  DSA_NEWOBJ_CTX_CLEANUP    = $00000004; // on post commit fail
  {$EXTERNALSYM DSA_NEWOBJ_CTX_CLEANUP}

//---------------------------------------------------------------------------
//
// Interface: IDsAdminNewObjExt
//
// Implemented by: creation extension in proc server (both primary and regular)
//
// Used by: DS Admin
//

type
  IDsAdminNewObjExt = interface (IUnknown)
  ['{6088EAE2-E7BF-11d2-82AF-00C04F68928B}']
    function Initialize(pADsContainerObj: IADsContainer; pADsCopySource: IADs;
      lpszClassName: LPCWSTR; pDsAdminNewObj: IDsAdminNewObj;
      const pDispInfo: DSA_NEWOBJ_DISPINFO): HRESULT; stdcall;
    function AddPages(lpfnAddPage: LPFNADDPROPSHEETPAGE; lParam: LPARAM): HRESULT; stdcall;
    function SetObject(pADsObj: IADs): HRESULT; stdcall;
    function WriteData(hWnd: HWND; uContext: ULONG): HRESULT; stdcall;
    function OnError(hWnd: HWND; hr: HRESULT; uContext: ULONG): HRESULT; stdcall;
    function GetSummaryInfo(out pBstrText: WideString): HRESULT; stdcall;
  end;
  {$EXTERNALSYM IDsAdminNewObjExt}

//
// Notification opcodes for IDsAdminNotifyHandler
//

const
  DSA_NOTIFY_DEL  = $00000001; // delete
  {$EXTERNALSYM DSA_NOTIFY_DEL}
  DSA_NOTIFY_REN  = $00000002; // rename
  {$EXTERNALSYM DSA_NOTIFY_REN}
  DSA_NOTIFY_MOV  = $00000004; // move
  {$EXTERNALSYM DSA_NOTIFY_MOV}
  DSA_NOTIFY_PROP = $00000008; // property change
  {$EXTERNALSYM DSA_NOTIFY_PROP}

  DSA_NOTIFY_ALL = (DSA_NOTIFY_DEL or DSA_NOTIFY_REN or DSA_NOTIFY_MOV or
    DSA_NOTIFY_PROP);
  {$EXTERNALSYM DSA_NOTIFY_ALL}

//
// flags to handle additional data
//

  DSA_NOTIFY_FLAG_ADDITIONAL_DATA       = $00000002; // process additional extension data?
  {$EXTERNALSYM DSA_NOTIFY_FLAG_ADDITIONAL_DATA}
  DSA_NOTIFY_FLAG_FORCE_ADDITIONAL_DATA = $00000001; // operation forced
  {$EXTERNALSYM DSA_NOTIFY_FLAG_FORCE_ADDITIONAL_DATA}

//---------------------------------------------------------------------------
//
// Interface: IDsAdminNotifyHandler
// 
// Implemented by: notification handler in proc server
//
// Used by: DS Admin
//

type
  IDsAdminNotifyHandler = interface (IUnknown)
  ['{E4A2B8B3-5A18-11d2-97C1-00A0C9A06D2D}']
    function Initialize(pExtraInfo: IDataObject; puEventFlags: PULONG): HRESULT; stdcall;
    function Begin_(uEvent: ULONG; pArg1, pArg2: IDataObject; puFlags: ULONG;
      out pBstr: WideString): HRESULT; stdcall;
    function Notify(nItem: ULONG; uFlags: ULONG): HRESULT; stdcall;
    function End_: HRESULT; stdcall;
  end;
  {$EXTERNALSYM IDsAdminNotifyHandler}

implementation

end.
