{******************************************************************************}
{                                                       	               }
{ ICommonQuery API interface Unit for Object Pascal                            }
{                                                       	               }
{ Portions created by Microsoft are Copyright (C) 1995-2001 Microsoft          }
{ Corporation. All Rights Reserved.                                            }
{ 								               }
{ The original file is: cmnquery.h, released November 2001. The original Pascal}
{ code is: CmnQuery.pas, released March 2002. The initial developer of the     }
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

unit JwaCmnQuery;

{$WEAKPACKAGEUNIT}

{$HPPEMIT ''}
{$HPPEMIT '#include "cmnquery.h"'}
{$HPPEMIT ''}

{$I WINDEFINES.INC}

interface

uses
  ActiveX, // IPersist todo objidl, ocidl
  JwaWinUser, JwaWinType;

const
  IID_IQueryForm: TGUID = (D1:$8cfcee30; D2:$39bd; D3:$11d0; D4:($b8, $d1, $0, $a0, $24, $ab, $2d, $bb));
  {$EXTERNALSYM IID_IQueryForm}
  IID_IPersistQuery: TGUID = (D1:$1a3114b8; D2:$a62e; D3:$11d0; D4:($a6, $c5, $0, $a0, $c9, $06, $af, $45));
  {$EXTERNALSYM IID_IPersistQuery}

  CLSID_CommonQuery: TGUID = (D1:$83bc5ec0; D2:$6f2a; D3:$11d0; D4:($a1, $c4, $0, $aa, $00, $c1, $6e, $65));
  {$EXTERNALSYM CLSID_CommonQuery}
  IID_ICommonQuery: TGUID = (D1:$ab50dec0; D2:$6f1d; D3:$11d0; D4:($a1, $c4, $0, $aa, $00, $c1, $6e, $65));
  {$EXTERNALSYM IID_ICommonQuery}

//-----------------------------------------------------------------------------
// IQueryForm
//-----------------------------------------------------------------------------

//
// A query form object is registered under the query handlers CLSID,
// a list is stored in the registry:
//
//  HKCR\CLSID\{CLSID query handler}\Forms
//
// For each form object there are server values which can be defined:
//
//  Flags           = flags for the form object:
//                      QUERYFORM_CHANGESFORMLIST
//                      QUERYFORM_CHANGESOPTFORMLIST
//
//  CLSID           = string containing the CLSID of the InProc server to invoke
//                    to get the IQueryFormObject.
//
//  Forms           = a sub key containing the CLSIDs for the forms registered
//                    by IQueryForm::AddForms (or modified by ::AddPages), if
//                    the flags are 0, then we scan this list looking for a match
//                    for the default form specified.
//

  QUERYFORM_CHANGESFORMLIST    = $000000001;
  {$EXTERNALSYM QUERYFORM_CHANGESFORMLIST}
  QUERYFORM_CHANGESOPTFORMLIST = $000000002;
  {$EXTERNALSYM QUERYFORM_CHANGESOPTFORMLIST}

//
// Query Forms
// ===========
//  Query forms are registered and have query pages added to them, a form without
//  pages is not displayed.  Each form has a unique CLSID to allow it to be
//  selected by invoking the query dialog.
//

  CQFF_NOGLOBALPAGES = $0000001; // = 1 => doesn't have global pages added
  {$EXTERNALSYM CQFF_NOGLOBALPAGES}
  CQFF_ISOPTIONAL    = $0000002; // = 1 => form is hidden, unless optional forms requested
  {$EXTERNALSYM CQFF_ISOPTIONAL}

type
  CQFORM = record
    cbStruct: DWORD;
    dwFlags: DWORD;
    clsid: CLSID;
    hIcon: HICON;
    pszTitle: LPCWSTR;
  end;
  {$EXTERNALSYM CQFORM}
  LPCQFORM = ^CQFORM;
  {$EXTERNALSYM LPCQFORM}
  TCQForm = CQFORM;
  PCQForm = LPCQFORM;

  LPCQADDFORMSPROC = function (lParam: LPARAM; pForm: LPCQFORM): HRESULT; stdcall;
  {$EXTERNALSYM LPCQADDFORMSPROC}

//
// Query Form Pages
// ================
//  When a query form has been registered the caller can then add pages to it,
//  any form can have pages appended.
//

  _cqpage = record
    cbStruct: DWORD;
    dwFlags: DWORD;
    pPageProc: Pointer{LPCQPAGEPROC};
    hInstance: HINSTANCE;
    idPageName: Integer;
    idPageTemplate: Integer;
    pDlgProc: DLGPROC;
    lParam: LPARAM;
  end;
  {$EXTERNALSYM _cqpage}
  CQPAGE = _cqpage;
  {$EXTERNALSYM CQPAGE}
  LPCQPAGE = ^CQPAGE;
  {$EXTERNALSYM LPCQPAGE}
  TCQPage = CQPAGE;
  PCQPage = LPCQPAGE;

  LPCQADDPAGESPROC = function (lParam: LPARAM; const clsidForm: CLSID; pPage: LPCQPAGE): HRESULT; stdcall;
  {$EXTERNALSYM LPCQADDPAGESPROC}
  LPCQPAGEPROC = function (pPage: LPCQPAGE; hwnd: HWND; uMsg: UINT; wParam: WPARAM; lParam: LPARAM): HRESULT; stdcall;
  {$EXTERNALSYM LPCQPAGEPROC}

//
// IQueryForm interfaces
//

  IQueryForm = interface (IUnknown)
  ['{8cfcee30-39bd-11d0-b8d1-00a024ab2dbb}']
    function Initialize(hkForm: HKEY): HRESULT; stdcall;
    function AddForms(pAddFormsProc: LPCQADDPAGESPROC; lParam: LPARAM): HRESULT; stdcall;
    function AddPages(pAddPagesProc: LPCQADDPAGESPROC; lParam: LPARAM): HRESULT; stdcall;
  end;
  {$EXTERNALSYM IQueryForm}

//
// Messages for pages
//

const
  CQPM_INITIALIZE           = $00000001;
  {$EXTERNALSYM CQPM_INITIALIZE}
  CQPM_RELEASE              = $00000002;
  {$EXTERNALSYM CQPM_RELEASE}
  CQPM_ENABLE               = $00000003; // wParam = TRUE/FALSE (enable, disable), lParam = 0
  {$EXTERNALSYM CQPM_ENABLE}
  CQPM_GETPARAMETERS        = $00000005; // wParam = 0, lParam = -> receives the LocalAlloc
  {$EXTERNALSYM CQPM_GETPARAMETERS}
  CQPM_CLEARFORM            = $00000006; // wParam, lParam = 0
  {$EXTERNALSYM CQPM_CLEARFORM}
  CQPM_PERSIST              = $00000007; // wParam = fRead, lParam -> IPersistQuery
  {$EXTERNALSYM CQPM_PERSIST}
  CQPM_HELP                 = $00000008; // wParam = 0, lParam -> LPHELPINFO
  {$EXTERNALSYM CQPM_HELP}
  CQPM_SETDEFAULTPARAMETERS = $00000009; // wParam = 0, lParam -> OPENQUERYWINDOW
  {$EXTERNALSYM CQPM_SETDEFAULTPARAMETERS}

  CQPM_HANDLERSPECIFIC      = $10000000;
  {$EXTERNALSYM CQPM_HANDLERSPECIFIC}

//-----------------------------------------------------------------------------
// IPersistQuery
//-----------------------------------------------------------------------------

// IPersistQuery interface

type
  IPersistQuery = interface (IPersist)
  ['{1a3114b8-a62e-11d0-a6c5-00a0c906af45}']
    function WriteString(pSection, pValueName, pValue: LPCWSTR): HRESULT; stdcall;
    function ReadString(pSection, pValueName, pBuffer: LPWSTR; cchBuffer: Integer): HRESULT; stdcall;
    function WriteInt(pSection, pValueName: LPCWSTR; value: Integer): HRESULT; stdcall;
    function ReadInt(pSection, pValueName: LPCWSTR; pValue: LPINT): HRESULT; stdcall;
    function WriteStruct(pSection, pValueName: LPCWSTR; pStruct: LPVOID; cbStruct: DWORD): HRESULT; stdcall;
    function ReadStruct(pSection, pValueName: LPCWSTR; pStruct: LPVOID; cbStruct: DWORD): HRESULT; stdcall;
    function Clear: HRESULT; stdcall;
  end;
  {$EXTERNALSYM IPersistQuery}

//-----------------------------------------------------------------------------
// ICommonQuery
//-----------------------------------------------------------------------------

const
  OQWF_OKCANCEL           = $00000001; // = 1 => Provide OK/Cancel buttons
  {$EXTERNALSYM OQWF_OKCANCEL}
  OQWF_DEFAULTFORM        = $00000002; // = 1 => clsidDefaultQueryForm is valid
  {$EXTERNALSYM OQWF_DEFAULTFORM}
  OQWF_SINGLESELECT       = $00000004; // = 1 => view to have single selection (depends on viewer)
  {$EXTERNALSYM OQWF_SINGLESELECT}
  OQWF_LOADQUERY          = $00000008; // = 1 => use the IPersistQuery to load the given query
  {$EXTERNALSYM OQWF_LOADQUERY}
  OQWF_REMOVESCOPES       = $00000010; // = 1 => remove scope picker from dialog
  {$EXTERNALSYM OQWF_REMOVESCOPES}
  OQWF_REMOVEFORMS        = $00000020; // = 1 => remove form picker from dialog
  {$EXTERNALSYM OQWF_REMOVEFORMS}
  OQWF_ISSUEONOPEN        = $00000040; // = 1 => issue query on opening the dialog
  {$EXTERNALSYM OQWF_ISSUEONOPEN}
  OQWF_SHOWOPTIONAL       = $00000080; // = 1 => list optional forms by default
  {$EXTERNALSYM OQWF_SHOWOPTIONAL}
  OQWF_SAVEQUERYONOK      = $00000200; // = 1 => use the IPersistQuery to write the query on close
  {$EXTERNALSYM OQWF_SAVEQUERYONOK}
  OQWF_HIDEMENUS          = $00000400; // = 1 => no menu bar displayed
  {$EXTERNALSYM OQWF_HIDEMENUS}
  OQWF_HIDESEARCHUI       = $00000800; // = 1 => dialog is filter, therefore start, stop, new search etc
  {$EXTERNALSYM OQWF_HIDESEARCHUI}

  OQWF_PARAMISPROPERTYBAG = DWORD($80000000); // = 1 => the form parameters ptr is an IPropertyBag (ppbFormParameters)
  {$EXTERNALSYM OQWF_PARAMISPROPERTYBAG}

type
  OPENQUERYWINDOW = record
    cbStruct: DWORD;                   // structure size
    dwFlags: DWORD;                    // flags (OQFW_*)
    clsidHandler: CLSID;               // clsid of handler we are using
    pHandlerParameters: LPVOID;        // handler specific structure for initialization
    clsidDefaultForm: CLSID;           // default form to be selected (if OQF_DEFAULTFORM == 1 )
    pPersistQuery: IPersistQuery;      // IPersistQuery used for loading queries
    //mvb IPropertyBag is an interface which needs finalization and therefor can't be present in a variant record
    //case Integer of
    //  0: (pFormParameters: Pointer);
    //  1: (ppbFormParameters: IPropertyBag);
    case Integer of
      0: (pFormParameters: Pointer);
      1: (ppbFormParameters: Pointer);
  end;
  {$EXTERNALSYM OPENQUERYWINDOW}
  LPOPENQUERYWINDOW = ^OPENQUERYWINDOW;
  {$EXTERNALSYM LPOPENQUERYWINDOW}
  TOpenQueryWindow = OPENQUERYWINDOW;
  POpenQueryWindow = LPOPENQUERYWINDOW;

// ICommonQuery

  ICommonQuery = interface (IUnknown)
  ['{ab50dec0-6f1d-11d0-a1c4-00aa00c16e65}']
    function OpenQueryWindow(hwndParent: HWND; pQueryWnd: LPOPENQUERYWINDOW; out ppDataObject: IDataObject): HRESULT; stdcall;
  end;
  {$EXTERNALSYM ICommonQuery}

implementation

end.
