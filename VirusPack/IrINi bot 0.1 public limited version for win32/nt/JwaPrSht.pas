{******************************************************************************}
{                                                       	               }
{ Property Sheet Pages API interface Unit for Object Pascal                    }
{                                                       	               }
{ Portions created by Microsoft are Copyright (C) 1995-2001 Microsoft          }
{ Corporation. All Rights Reserved.                                            }
{ 								               }
{ The original file is: prsht.h, released June 2000. The original Pascal       }
{ code is: PrSht.pas, released December 2000. The initial developer of the     }
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

unit JwaPrSht;

{$WEAKPACKAGEUNIT}

{$HPPEMIT ''}
{$HPPEMIT '#include "ntdsapi.h"'}
{$HPPEMIT ''}
{$HPPEMIT 'typedef PHPROPSHEETPAGE  *HPROPSHEETPAGE'}
{$HPPEMIT ''}

{$I WINDEFINES.INC}

interface

uses
  JwaWinNT, JwaWinUser, JwaWinType;

//#ifndef CCSIZEOF_STRUCT
//#define CCSIZEOF_STRUCT(structname, member)  (((int)((LPBYTE)(&((structname*)0)->member) - ((LPBYTE)((structname*)0)))) + sizeof(((structname*)0)->member))
//#endif

//
// For compilers that don't support nameless unions
//

const
  MAXPROPPAGES           = 100;
  {$EXTERNALSYM MAXPROPPAGES}

type
  HPROPSHEETPAGE = Pointer;
  {$EXTERNALSYM HPROPSHEETPAGE}
  PHPROPSHEETPAGE = ^HPROPSHEETPAGE;
  {$NODEFINE PHPROPSHEETPAGE}

  LPFNPSPCALLBACKA = function (hwnd: HWND; uMsg: UINT; ppsp: Pointer{LPPROPSHEETPAGEA}): UINT; stdcall;
  {$EXTERNALSYM LPFNPSPCALLBACKA}
  LPFNPSPCALLBACKW = function (hwnd: HWND; uMsg: UINT; ppsp: Pointer{LPPROPSHEETPAGEW}): UINT; stdcall;
  {$EXTERNALSYM LPFNPSPCALLBACKW}

{$IFDEF UNICODE}
  LPFNPSPCALLBACK = function (hwnd: HWND; uMsg: UINT; ppsp: Pointer{LPPROPSHEETPAGEW}): UINT; stdcall;
  {$EXTERNALSYM LPFNPSPCALLBACK}
{$ELSE}
  LPFNPSPCALLBACK = function (hwnd: HWND; uMsg: UINT; ppsp: Pointer{LPPROPSHEETPAGEA}): UINT; stdcall;
  {$EXTERNALSYM LPFNPSPCALLBACK}
{$ENDIF}
  
const
  PSP_DEFAULT               = $00000000;
  {$EXTERNALSYM PSP_DEFAULT}
  PSP_DLGINDIRECT           = $00000001;
  {$EXTERNALSYM PSP_DLGINDIRECT}
  PSP_USEHICON              = $00000002;
  {$EXTERNALSYM PSP_USEHICON}
  PSP_USEICONID             = $00000004;
  {$EXTERNALSYM PSP_USEICONID}
  PSP_USETITLE              = $00000008;
  {$EXTERNALSYM PSP_USETITLE}
  PSP_RTLREADING            = $00000010;
  {$EXTERNALSYM PSP_RTLREADING}

  PSP_HASHELP               = $00000020;
  {$EXTERNALSYM PSP_HASHELP}
  PSP_USEREFPARENT          = $00000040;
  {$EXTERNALSYM PSP_USEREFPARENT}
  PSP_USECALLBACK           = $00000080;
  {$EXTERNALSYM PSP_USECALLBACK}
  PSP_PREMATURE             = $00000400;
  {$EXTERNALSYM PSP_PREMATURE}

//----- New flags for wizard97 --------------

  PSP_HIDEHEADER            = $00000800;
  {$EXTERNALSYM PSP_HIDEHEADER}
  PSP_USEHEADERTITLE        = $00001000;
  {$EXTERNALSYM PSP_USEHEADERTITLE}
  PSP_USEHEADERSUBTITLE     = $00002000;
  {$EXTERNALSYM PSP_USEHEADERSUBTITLE}

//-------------------------------------------

  PSPCB_ADDREF           = 0;
  {$EXTERNALSYM PSPCB_ADDREF}
  PSPCB_RELEASE          = 1;
  {$EXTERNALSYM PSPCB_RELEASE}
  PSPCB_CREATE           = 2;
  {$EXTERNALSYM PSPCB_CREATE}

//#define PROPSHEETPAGEA_V1_SIZE CCSIZEOF_STRUCT(PROPSHEETPAGEA, pcRefParent)
//#define PROPSHEETPAGEW_V1_SIZE CCSIZEOF_STRUCT(PROPSHEETPAGEW, pcRefParent)

type
  _PROPSHEETPAGEA = record
    dwSize: DWORD;
    dwFlags: DWORD;
    hInstance: HINSTANCE;
    u: record
    case Integer of
      0: (pszTemplate: LPCSTR);
      1: (pResource: LPCDLGTEMPLATE);
    end;
    u2: record
    case Integer of
      0: (hIcon: HICON);
      1: (pszIcon: LPCSTR);
    end;
    pszTitle: LPCSTR;
    pfnDlgProc: DLGPROC;
    lParam: LPARAM;
    pfnCallback: LPFNPSPCALLBACKA;
    pcRefParent: LPUINT;
    {$IFDEF _WIN32_IE_GE_0x0400}
    pszHeaderTitle: LPCSTR;    // this is displayed in the header
    pszHeaderSubTitle: LPCSTR; //
    {$ENDIF}
  end;
  {$EXTERNALSYM _PROPSHEETPAGEA}
  PROPSHEETPAGEA = _PROPSHEETPAGEA;
  {$EXTERNALSYM PROPSHEETPAGEA}
  LPPROPSHEETPAGEA = ^PROPSHEETPAGEA;
  {$EXTERNALSYM LPPROPSHEETPAGEA}
  LPCPROPSHEETPAGEA = LPPROPSHEETPAGEA;
  {$EXTERNALSYM LPCPROPSHEETPAGEA}
  TPropSheetPageA = PROPSHEETPAGEA;
  PPropSheetPageA = LPPROPSHEETPAGEA;

  _PROPSHEETPAGEW = record
    dwSize: DWORD;
    dwFlags: DWORD;
    hInstance: HINSTANCE;
    u: record
    case Integer of
      0: (pszTemplate: LPCWSTR);
      1: (pResource: LPCDLGTEMPLATE);
    end;
    u2: record
    case Integer of
      0: (hIcon: HICON);
      1: (pszIcon: LPCWSTR);
    end;
    pszTitle: LPCWSTR;
    pfnDlgProc: DLGPROC;
    lParam: LPARAM;
    pfnCallback: LPFNPSPCALLBACKW;
    pcRefParent: LPUINT;
    {$IFDEF _WIN32_IE_GE_0x0400}
    pszHeaderTitle: LPCWSTR;    // this is displayed in the header
    pszHeaderSubTitle: LPCWSTR; //
    {$ENDIF}
  end;
  {$EXTERNALSYM _PROPSHEETPAGEW}
  PROPSHEETPAGEW = _PROPSHEETPAGEW;
  {$EXTERNALSYM PROPSHEETPAGEW}
  LPPROPSHEETPAGEW = ^PROPSHEETPAGEW;
  {$EXTERNALSYM LPPROPSHEETPAGEW}
  LPCPROPSHEETPAGEW = LPPROPSHEETPAGEW;
  {$EXTERNALSYM LPCPROPSHEETPAGEW}
  TPropSheetPageW = PROPSHEETPAGEW;
  PPropSheetPageW = LPPROPSHEETPAGEW;

{$IFDEF UNICODE}
  PROPSHEETPAGE          = PROPSHEETPAGEW;
  {$EXTERNALSYM PROPSHEETPAGE}
  LPPROPSHEETPAGE        = LPPROPSHEETPAGEW;
  {$EXTERNALSYM LPPROPSHEETPAGE}
  LPCPROPSHEETPAGE       = LPCPROPSHEETPAGEW;
  {$EXTERNALSYM LPCPROPSHEETPAGE}
  TPropSheetPage = TPropSheetPageW;
  PPropSheetPage = PPropSheetPageW;
  
const
  PROPSHEETPAGE_V1_SIZE  = 40; {PROPSHEETPAGEW_V1_SIZE}
  {$EXTERNALSYM PROPSHEETPAGE_V1_SIZE}
{$ELSE}
  PROPSHEETPAGE          = PROPSHEETPAGEA;
  {$EXTERNALSYM PROPSHEETPAGE}
  LPPROPSHEETPAGE        = LPPROPSHEETPAGEA;
  {$EXTERNALSYM LPPROPSHEETPAGE}
  LPCPROPSHEETPAGE       = LPCPROPSHEETPAGEA;
  {$EXTERNALSYM LPCPROPSHEETPAGE}
  TPropSheetPage = TPropSheetPageA;
  PPropSheetPage = PPropSheetPageA;

const
  PROPSHEETPAGE_V1_SIZE  = 40; {PROPSHEETPAGEA_V1_SIZE}
  {$EXTERNALSYM PROPSHEETPAGE_V1_SIZE}
{$ENDIF}

const
  PSH_DEFAULT            = $00000000;
  {$EXTERNALSYM PSH_DEFAULT}
  PSH_PROPTITLE          = $00000001;
  {$EXTERNALSYM PSH_PROPTITLE}
  PSH_USEHICON           = $00000002;
  {$EXTERNALSYM PSH_USEHICON}
  PSH_USEICONID          = $00000004;
  {$EXTERNALSYM PSH_USEICONID}
  PSH_PROPSHEETPAGE      = $00000008;
  {$EXTERNALSYM PSH_PROPSHEETPAGE}
  PSH_WIZARDHASFINISH    = $00000010;
  {$EXTERNALSYM PSH_WIZARDHASFINISH}
  PSH_WIZARD             = $00000020;
  {$EXTERNALSYM PSH_WIZARD}
  PSH_USEPSTARTPAGE      = $00000040;
  {$EXTERNALSYM PSH_USEPSTARTPAGE}
  PSH_NOAPPLYNOW         = $00000080;
  {$EXTERNALSYM PSH_NOAPPLYNOW}
  PSH_USECALLBACK        = $00000100;
  {$EXTERNALSYM PSH_USECALLBACK}
  PSH_HASHELP            = $00000200;
  {$EXTERNALSYM PSH_HASHELP}
  PSH_MODELESS           = $00000400;
  {$EXTERNALSYM PSH_MODELESS}
  PSH_RTLREADING         = $00000800;
  {$EXTERNALSYM PSH_RTLREADING}
  PSH_WIZARDCONTEXTHELP  = $00001000;
  {$EXTERNALSYM PSH_WIZARDCONTEXTHELP}

//----- New flags for wizard97 -----------

{$IFDEF _WIN32_IE_SMALLER_0500}
  PSH_WIZARD97           = $00002000;
  {$EXTERNALSYM PSH_WIZARD97}
{$ELSE}
  PSH_WIZARD97           = $01000000;
  {$EXTERNALSYM PSH_WIZARD97}
{$ENDIF}

// 0x00004000 was not used by any previous release

  PSH_WATERMARK          = $00008000;
  {$EXTERNALSYM PSH_WATERMARK}
  PSH_USEHBMWATERMARK    = $00010000;  // user pass in a hbmWatermark instead of pszbmWatermark
  {$EXTERNALSYM PSH_USEHBMWATERMARK}
  PSH_USEHPLWATERMARK    = $00020000;  //
  {$EXTERNALSYM PSH_USEHPLWATERMARK}
  PSH_STRETCHWATERMARK   = $00040000;  // stretchwatermark also applies for the header
  {$EXTERNALSYM PSH_STRETCHWATERMARK}
  PSH_HEADER             = $00080000;
  {$EXTERNALSYM PSH_HEADER}
  PSH_USEHBMHEADER       = $00100000;
  {$EXTERNALSYM PSH_USEHBMHEADER}
  PSH_USEPAGELANG        = $00200000;  // use frame dialog template matched to page
  {$EXTERNALSYM PSH_USEPAGELANG}

//----------------------------------------

//----- New flags for wizard-lite --------

 PSH_WIZARD_LITE        = $00400000;
 {$EXTERNALSYM PSH_WIZARD_LITE}
 PSH_NOCONTEXTHELP      = $02000000;
 {$EXTERNALSYM PSH_NOCONTEXTHELP}

//----------------------------------------

type
  PFNPROPSHEETCALLBACK = function (hwn: HWND; uMsg: UINT; lParam: LPARAM): Integer; stdcall;
  {$EXTERNALSYM PFNPROPSHEETCALLBACK}

//const
//#define PROPSHEETHEADERA_V1_SIZE CCSIZEOF_STRUCT(PROPSHEETHEADERA, pfnCallback)
//#define PROPSHEETHEADERW_V1_SIZE CCSIZEOF_STRUCT(PROPSHEETHEADERW, pfnCallback)

type
  _PROPSHEETHEADERA = record
    dwSize: DWORD;
    dwFlags: DWORD;
    hwndParent: HWND;
    hInstance: HINSTANCE;
    u: record
    case Integer of
      0: (hIcon: HICON);
      1: (pszIcon: LPCSTR);
    end;
    pszCaption: LPCSTR;
    nPages: UINT;
    u2: record
    case Integer of
      0: (nStartPage: UINT);
      1: (pStartPage: LPCSTR);
    end;
    u3: record
    case Integer of
      0: (ppsp: LPCPROPSHEETPAGEA);
      1: (phpage: PHPROPSHEETPAGE);
    end;
    pfnCallback: PFNPROPSHEETCALLBACK;
    {$IFDEF _WIN32_IE_GE_0x0400}
    u4: record
    case Integer of
      0: (hbmWatermark: HBITMAP);
      1: (pszbmWatermark: LPCSTR);
    end;
    hplWatermark: HPALETTE;
    u5: record
    case Integer of
      0: (hbmHeader: HBITMAP);     // Header  bitmap shares the palette with watermark
      1: (pszbmHeader: LPCSTR);
    end;
    {$ENDIF}
  end;
  {$EXTERNALSYM _PROPSHEETHEADERA}
  PROPSHEETHEADERA =_PROPSHEETHEADERA;
  {$EXTERNALSYM PROPSHEETHEADERA}
  LPPROPSHEETHEADERA = ^PROPSHEETHEADERA;
  {$EXTERNALSYM LPPROPSHEETHEADERA}
  LPCPROPSHEETHEADERA = LPPROPSHEETHEADERA;
  {$EXTERNALSYM LPCPROPSHEETHEADERA}
  TPropSheetHeaderA = PROPSHEETHEADERA;
  PPropSheetHeaderA = LPPROPSHEETHEADERA;

  _PROPSHEETHEADERW = record
    dwSize: DWORD;
    dwFlags: DWORD;
    hwndParent: HWND;
    hInstance: HINSTANCE;
    u: record
    case Integer of
      0: (hIcon: HICON);
      1: (pszIcon: LPCWSTR);
    end;
    pszCaption: LPCWSTR;
    nPages: UINT;
    u2: record
    case Integer of
      0: (nStartPage: UINT);
      1: (pStartPage: LPCWSTR);
    end;
    u3: record
    case Integer of
      0: (ppsp: LPCPROPSHEETPAGEW);
      1: (phpage: PHPROPSHEETPAGE);
    end;
    pfnCallback: PFNPROPSHEETCALLBACK;
    {$IFDEF _WIN32_IE_GE_0x0400}
    u4: record
    case Integer of
      0: (hbmWatermark: HBITMAP);
      1: (pszbmWatermark: LPCWSTR);
    end;
    hplWatermark: HPALETTE;
    u5: record
    case Integer of
      0: (hbmHeader: HBITMAP);     // Header  bitmap shares the palette with watermark
      1: (pszbmHeader: LPCWSTR);
    end;
    {$ENDIF}
  end;
  {$EXTERNALSYM _PROPSHEETHEADERW}
  PROPSHEETHEADERW =_PROPSHEETHEADERW;
  {$EXTERNALSYM PROPSHEETHEADERW}
  LPPROPSHEETHEADERW = ^PROPSHEETHEADERW;
  {$EXTERNALSYM LPPROPSHEETHEADERW}
  LPCPROPSHEETHEADERW = LPPROPSHEETHEADERW;
  {$EXTERNALSYM LPCPROPSHEETHEADERW}
  TPropSheetHeaderW = PROPSHEETHEADERW;
  PPropSheetHeaderW = LPPROPSHEETHEADERW;

{$IFDEF UNICODE}
  PROPSHEETHEADER         = PROPSHEETHEADERW;
  {$EXTERNALSYM PROPSHEETHEADER}
  LPPROPSHEETHEADER       = LPPROPSHEETHEADERW;
  {$EXTERNALSYM LPPROPSHEETHEADER}
  LPCPROPSHEETHEADER      = LPCPROPSHEETHEADERW;
  {$EXTERNALSYM LPCPROPSHEETHEADER}
  TPropSheetHeader = TPropSheetHeaderW;
  PPropSheetHeader = PPropSheetHeaderW;

const
  PROPSHEETHEADER_V1_SIZE = 40; {PROPSHEETHEADERW_V1_SIZE}
  {$EXTERNALSYM PROPSHEETHEADER_V1_SIZE}
{$ELSE}
  PROPSHEETHEADER         = PROPSHEETHEADERA;
  {$EXTERNALSYM PROPSHEETHEADER}
  LPPROPSHEETHEADER       = LPPROPSHEETHEADERA;
  {$EXTERNALSYM LPPROPSHEETHEADER}
  LPCPROPSHEETHEADER      = LPCPROPSHEETHEADERA;
  {$EXTERNALSYM LPCPROPSHEETHEADER}
  TPropSheetHeader = TPropSheetHeaderA;
  PPropSheetHeader = PPropSheetHeaderA;

const
  PROPSHEETHEADER_V1_SIZE = 40; {PROPSHEETHEADERA_V1_SIZE;}
  {$EXTERNALSYM PROPSHEETHEADER_V1_SIZE}
{$ENDIF}

const
  PSCB_INITIALIZED = 1;
  {$EXTERNALSYM PSCB_INITIALIZED}
  PSCB_PRECREATE   = 2;
  {$EXTERNALSYM PSCB_PRECREATE}

function CreatePropertySheetPageA(const lppsp: PROPSHEETPAGEA): HPROPSHEETPAGE; stdcall;
{$EXTERNALSYM CreatePropertySheetPageA}
function CreatePropertySheetPageW(const lppsp: PROPSHEETPAGEW): HPROPSHEETPAGE; stdcall;
{$EXTERNALSYM DestroyPropertySheetPage}
function DestroyPropertySheetPage(hPSPage: HPROPSHEETPAGE): BOOL; stdcall;
{$EXTERNALSYM DestroyPropertySheetPage}
function PropertySheetA(const lppsph: PROPSHEETHEADERA): INT_PTR; stdcall;
{$EXTERNALSYM PropertySheetA}
function PropertySheetW(const lppsph: PROPSHEETHEADERW): INT_PTR; stdcall;
{$EXTERNALSYM PropertySheetW}

{$IFDEF UNICODE}
function CreatePropertySheetPage(const lppsp: PROPSHEETPAGEW): HPROPSHEETPAGE; stdcall;
{$EXTERNALSYM DestroyPropertySheetPage}
function PropertySheet(const lppsph: PROPSHEETHEADERW): INT_PTR; stdcall;
{$EXTERNALSYM PropertySheet}
{$ELSE}
function CreatePropertySheetPage(const lppsp: PROPSHEETPAGEA): HPROPSHEETPAGE; stdcall;
{$EXTERNALSYM CreatePropertySheetPage}
function PropertySheet(const lppsph: PROPSHEETHEADERA): INT_PTR; stdcall;
{$EXTERNALSYM PropertySheet}
{$ENDIF}

type
  LPFNADDPROPSHEETPAGE = function (page: HPROPSHEETPAGE; lParam: LPARAM): BOOL; stdcall;
  {$EXTERNALSYM LPFNADDPROPSHEETPAGE}
  LPFNADDPROPSHEETPAGES = function (pv: LPVOID; fn: LPFNADDPROPSHEETPAGE; lParam: LPARAM): BOOL; stdcall;
  {$EXTERNALSYM LPFNADDPROPSHEETPAGES}

  _PSHNOTIFY = record
    hdr: NMHDR;
    lParam: LPARAM;
  end;
  {$EXTERNALSYM _PSHNOTIFY}
  PSHNOTIFY = _PSHNOTIFY;
  {$EXTERNALSYM PSHNOTIFY}
  LPPSHNOTIFY = ^PSHNOTIFY;
  {$EXTERNALSYM LPPSHNOTIFY}
  TPSHNotify = PSHNOTIFY;
  PPSHNotify = LPPSHNOTIFY;  

const
  PSN_FIRST              = ULONG(0-200);
  {$EXTERNALSYM PSN_FIRST}
  PSN_LAST               = ULONG(0-299);
  {$EXTERNALSYM PSN_LAST}

  PSN_SETACTIVE   = (PSN_FIRST-0);
  {$EXTERNALSYM PSN_SETACTIVE}
  PSN_KILLACTIVE  = (PSN_FIRST-1);
  {$EXTERNALSYM PSN_KILLACTIVE}
  //PSN_VALIDATE    = (PSN_FIRST-1);
  //{$EXTERNALSYM PSN_VALIDATE}
  PSN_APPLY       = (PSN_FIRST-2);
  {$EXTERNALSYM PSN_APPLY}
  PSN_RESET       = (PSN_FIRST-3);
  {$EXTERNALSYM PSN_RESET}
  //PSN_CANCEL      = (PSN_FIRST-3);
  //{$EXTERNALSYM PSN_CANCEL}
  PSN_HELP        = (PSN_FIRST-5);
  {$EXTERNALSYM PSN_HELP}
  PSN_WIZBACK     = (PSN_FIRST-6);
  {$EXTERNALSYM PSN_WIZBACK}
  PSN_WIZNEXT     = (PSN_FIRST-7);
  {$EXTERNALSYM PSN_WIZNEXT}
  PSN_WIZFINISH   = (PSN_FIRST-8);
  {$EXTERNALSYM PSN_WIZFINISH}
  PSN_QUERYCANCEL = (PSN_FIRST-9);
  {$EXTERNALSYM PSN_QUERYCANCEL}
  PSN_GETOBJECT = (PSN_FIRST-10);
  {$EXTERNALSYM PSN_GETOBJECT}
  PSN_TRANSLATEACCELERATOR = (PSN_FIRST-12);
  {$EXTERNALSYM PSN_TRANSLATEACCELERATOR}
  PSN_QUERYINITIALFOCUS    = (PSN_FIRST-13);
  {$EXTERNALSYM PSN_QUERYINITIALFOCUS}

  PSNRET_NOERROR              = 0;
  {$EXTERNALSYM PSNRET_NOERROR}
  PSNRET_INVALID              = 1;
  {$EXTERNALSYM PSNRET_INVALID}
  PSNRET_INVALID_NOCHANGEPAGE = 2;
  {$EXTERNALSYM PSNRET_INVALID_NOCHANGEPAGE}
  PSNRET_MESSAGEHANDLED       = 3;
  {$EXTERNALSYM PSNRET_MESSAGEHANDLED}

  PSM_SETCURSEL = (WM_USER + 101);
  {$EXTERNALSYM PSM_SETCURSEL}

function PropSheet_SetCurSel(hPropSheetDlg: HWND; hPage: HPROPSHEETPAGE; Index: Integer): BOOL;

const
  PSM_REMOVEPAGE = (WM_USER + 102);
  {$EXTERNALSYM PSM_REMOVEPAGE}

procedure PropSheet_RemovePage(hPropSheetDlg: HWND; Index: Integer; hPage: HPROPSHEETPAGE);

const
  PSM_ADDPAGE = (WM_USER + 103);
  {$EXTERNALSYM PSM_ADDPAGE}

function PropSheet_AddPage(hPropSheetDlg: HWND; hpage: HPROPSHEETPAGE): BOOL;

const
  PSM_CHANGED = (WM_USER + 104);
  {$EXTERNALSYM PSM_CHANGED}

function PropSheet_Changed(hPropSheetDlg: HWND; hwndPage: HWND): BOOL;

const
  PSM_RESTARTWINDOWS = (WM_USER + 105);
  {$EXTERNALSYM PSM_RESTARTWINDOWS}

procedure PropSheet_RestartWindows(hPropSheetDlg: HWND);

const
  PSM_REBOOTSYSTEM = (WM_USER + 106);
  {$EXTERNALSYM PSM_REBOOTSYSTEM}

procedure PropSheet_RebootSystem(hPropSheetDlg: HWND);

const
  PSM_CANCELTOCLOSE = (WM_USER + 107);
  {$EXTERNALSYM PSM_CANCELTOCLOSE}

procedure PropSheet_CancelToClose(hPropSheetDlg: HWND);

const
  PSM_QUERYSIBLINGS = (WM_USER + 108);
  {$EXTERNALSYM PSM_QUERYSIBLINGS}

function PropSheet_QuerySiblings(hPropSheetDlg: HWND; Param1: WPARAM; Param2: LPARAM): Integer;

const
  PSM_UNCHANGED = (WM_USER + 109);
  {$EXTERNALSYM PSM_UNCHANGED}

procedure PropSheet_UnChanged(hPropSheetDlg: HWND; hwndPage: HWND);

const
  PSM_APPLY = (WM_USER + 110);
  {$EXTERNALSYM PSM_APPLY}

function PropSheet_Apply(hPropSheetDlg: HWND): BOOL;

const
  PSM_SETTITLEA = (WM_USER + 111);
  {$EXTERNALSYM PSM_SETTITLEA}
  PSM_SETTITLEW = (WM_USER + 120);
  {$EXTERNALSYM PSM_SETTITLEW}

{$IFDEF UNICODE}
  PSM_SETTITLE = PSM_SETTITLEW;
  {$EXTERNALSYM PSM_SETTITLE}
{$ELSE}
  PSM_SETTITLE = PSM_SETTITLEA;
  {$EXTERNALSYM PSM_SETTITLE}
{$ENDIF}

procedure PropSheet_SetTitle(hPropSheetDlg: HWND; dwStyle: DWORD; lpszText: LPTSTR);

const
  PSM_SETWIZBUTTONS = (WM_USER + 112);
  {$EXTERNALSYM PSM_SETWIZBUTTONS}

procedure PropSheet_SetWizButtons(hPropSheetDlg: HWND; dwFlags: DWORD);

const
  PSWIZB_BACK           = $00000001;
  {$EXTERNALSYM PSWIZB_BACK}
  PSWIZB_NEXT           = $00000002;
  {$EXTERNALSYM PSWIZB_NEXT}
  PSWIZB_FINISH         = $00000004;
  {$EXTERNALSYM PSWIZB_FINISH}
  PSWIZB_DISABLEDFINISH = $00000008;
  {$EXTERNALSYM PSWIZB_DISABLEDFINISH}

  PSM_PRESSBUTTON = (WM_USER + 113);
  {$EXTERNALSYM PSM_PRESSBUTTON}

function PropSheet_PressButton(hPropSheetDlg: HWND; iButton: Integer): BOOL;

const
  PSBTN_BACK     = 0;
  {$EXTERNALSYM PSBTN_BACK}
  PSBTN_NEXT     = 1;
  {$EXTERNALSYM PSBTN_NEXT}
  PSBTN_FINISH   = 2;
  {$EXTERNALSYM PSBTN_FINISH}
  PSBTN_OK       = 3;
  {$EXTERNALSYM PSBTN_OK}
  PSBTN_APPLYNOW = 4;
  {$EXTERNALSYM PSBTN_APPLYNOW}
  PSBTN_CANCEL   = 5;
  {$EXTERNALSYM PSBTN_CANCEL}
  PSBTN_HELP     = 6;
  {$EXTERNALSYM PSBTN_HELP}
  PSBTN_MAX      = 6;
  {$EXTERNALSYM PSBTN_MAX}

  PSM_SETCURSELID = (WM_USER + 114);
  {$EXTERNALSYM PSM_SETCURSELID}

function PropSheet_SetCurSelByID(hPropSheetDlg: HWND; id: Integer): BOOL;

const
  PSM_SETFINISHTEXTA = (WM_USER + 115);
  {$EXTERNALSYM PSM_SETFINISHTEXTA}
  PSM_SETFINISHTEXTW = (WM_USER + 121);
  {$EXTERNALSYM PSM_SETFINISHTEXTW}

{$IFDEF UNICODE}
  PSM_SETFINISHTEXT = PSM_SETFINISHTEXTW;
  {$EXTERNALSYM PSM_SETFINISHTEXT}
{$ELSE}
  PSM_SETFINISHTEXT = PSM_SETFINISHTEXTA;
  {$EXTERNALSYM PSM_SETFINISHTEXT}
{$ENDIF}

procedure PropSheet_SetFinishText(hPropSheetDlg: HWND; lpszText: LPTSTR);

const
  PSM_GETTABCONTROL = (WM_USER + 116);
  {$EXTERNALSYM PSM_GETTABCONTROL}

function PropSheet_GetTabControl(hPropSheetDlg: HWND): HWND;

const
  PSM_ISDIALOGMESSAGE = (WM_USER + 117);
  {$EXTERNALSYM PSM_ISDIALOGMESSAGE}

function PropSheet_IsDialogMessage(hDlg: HWND; pMsg: LPMSG): BOOL;

const
  PSM_GETCURRENTPAGEHWND = (WM_USER + 118);
  {$EXTERNALSYM PSM_GETCURRENTPAGEHWND}

function PropSheet_GetCurrentPageHwnd(hDlg: HWND): HWND;

const
  PSM_INSERTPAGE = (WM_USER + 119);
  {$EXTERNALSYM PSM_INSERTPAGE}

function PropSheet_InsertPage(hPropSheetDlg: HWND; index: Integer; hpage: HPROPSHEETPAGE): BOOL;

const
  PSM_SETHEADERTITLEA = (WM_USER + 125);
  {$EXTERNALSYM PSM_SETHEADERTITLEA}
  PSM_SETHEADERTITLEW = (WM_USER + 126);
  {$EXTERNALSYM PSM_SETHEADERTITLEW}

{$IFDEF UNICODE}
  PSM_SETHEADERTITLE = PSM_SETHEADERTITLEW;
  {$EXTERNALSYM PSM_SETHEADERTITLE}
{$ELSE}
  PSM_SETHEADERTITLE = PSM_SETHEADERTITLEA;
  {$EXTERNALSYM PSM_SETHEADERTITLE}
{$ENDIF}

function PropSheet_SetHeaderTitle(hWizardDlg: HWND; iPageIndex: Integer; lpszText: LPCSTR): Integer;

const
  PSM_SETHEADERSUBTITLEA = (WM_USER + 127);
  {$EXTERNALSYM PSM_SETHEADERSUBTITLEA}
  PSM_SETHEADERSUBTITLEW = (WM_USER + 128);
  {$EXTERNALSYM PSM_SETHEADERSUBTITLEW}

{$IFDEF UNICODE}
  PSM_SETHEADERSUBTITLE = PSM_SETHEADERSUBTITLEW;
  {$EXTERNALSYM PSM_SETHEADERSUBTITLE}
{$ELSE}
  PSM_SETHEADERSUBTITLE = PSM_SETHEADERSUBTITLEA;
  {$EXTERNALSYM PSM_SETHEADERSUBTITLE}
{$ENDIF}

procedure PropSheet_SetHeaderSubTitle(hWizardDlg: HWND; iPageIndex: Integer; pszHeaderSubTitle: LPCSTR);

const
  PSM_HWNDTOINDEX = (WM_USER + 129);
  {$EXTERNALSYM PSM_HWNDTOINDEX}

function PropSheet_HwndToIndex(hPropSheetDlg: HWND; hPageDlg: HWND): Integer;

const
  PSM_INDEXTOHWND = (WM_USER + 130);
  {$EXTERNALSYM PSM_INDEXTOHWND}

function PropSheet_IndexToHwnd(hPropSheetDlg: HWND; iPageIndex: Integer): HWND;

const
  PSM_PAGETOINDEX = (WM_USER + 131);
  {$EXTERNALSYM PSM_PAGETOINDEX}

function PropSheet_PageToIndex(hPropSheetDlg: HWND; hPage: HPROPSHEETPAGE): Integer;

const
  PSM_INDEXTOPAGE = (WM_USER + 132);
  {$EXTERNALSYM PSM_INDEXTOPAGE}

function PropSheet_IndexToPage(hPropSheetDlg: HWND; iPageIndex: Integer): HPROPSHEETPAGE;

const
  PSM_IDTOINDEX = (WM_USER + 133);
  {$EXTERNALSYM PSM_IDTOINDEX}

function PropSheet_IdToIndex(hPropSheetDlg: HWND; iPageId: Integer): Integer;

const
  PSM_INDEXTOID = (WM_USER + 134);
  {$EXTERNALSYM PSM_INDEXTOID}

function PropSheet_IndexToId(hPropSheetDlg: HWND; iPageIndex: Integer): Integer;

const
  PSM_GETRESULT = (WM_USER + 135);
  {$EXTERNALSYM PSM_GETRESULT}

function PropSheet_GetResult(hPropSheetDlg: HWND): BOOL;

const
  PSM_RECALCPAGESIZES = (WM_USER + 136);
  {$EXTERNALSYM PSM_RECALCPAGESIZES}

function PropSheet_RecalcPageSizes(hPropSheetDlg: HWND): BOOL;

const
  ID_PSRESTARTWINDOWS = $2;
  {$EXTERNALSYM ID_PSRESTARTWINDOWS}

  ID_PSREBOOTSYSTEM   = (ID_PSRESTARTWINDOWS or $1);
  {$EXTERNALSYM ID_PSREBOOTSYSTEM}

  WIZ_CXDLG = 276;
  {$EXTERNALSYM WIZ_CXDLG}
  WIZ_CYDLG = 140;
  {$EXTERNALSYM WIZ_CYDLG}

  WIZ_CXBMP = 80;
  {$EXTERNALSYM WIZ_CXBMP}

  WIZ_BODYX  = 92;
  {$EXTERNALSYM WIZ_BODYX}
  WIZ_BODYCX = 184;
  {$EXTERNALSYM WIZ_BODYCX}

  PROP_SM_CXDLG = 212;
  {$EXTERNALSYM PROP_SM_CXDLG}
  PROP_SM_CYDLG = 188;
  {$EXTERNALSYM PROP_SM_CYDLG}

  PROP_MED_CXDLG = 227;
  {$EXTERNALSYM PROP_MED_CXDLG}
  PROP_MED_CYDLG = 215;
  {$EXTERNALSYM PROP_MED_CYDLG}

  PROP_LG_CXDLG = 252;
  {$EXTERNALSYM PROP_LG_CXDLG}
  PROP_LG_CYDLG = 218;
  {$EXTERNALSYM PROP_LG_CYDLG}

implementation

const
  comctl32 = 'comctl32.dll';


{$IFDEF DYNAMIC_LINK}
var
  _CreatePropertySheetPageA: Pointer;

function CreatePropertySheetPageA;
begin
  GetProcedureAddress(_CreatePropertySheetPageA, comctl32, 'CreatePropertySheetPageA');
  asm
    mov esp, ebp
    pop ebp
    jmp [_CreatePropertySheetPageA]
  end;
end;
{$ELSE}
function CreatePropertySheetPageA; external comctl32 name 'CreatePropertySheetPageA';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _CreatePropertySheetPageW: Pointer;

function CreatePropertySheetPageW;
begin
  GetProcedureAddress(_CreatePropertySheetPageW, comctl32, 'CreatePropertySheetPageW');
  asm
    mov esp, ebp
    pop ebp
    jmp [_CreatePropertySheetPageW]
  end;
end;
{$ELSE}
function CreatePropertySheetPageW; external comctl32 name 'CreatePropertySheetPageW';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _DestroyPropertySheetPage: Pointer;

function DestroyPropertySheetPage;
begin
  GetProcedureAddress(_DestroyPropertySheetPage, comctl32, 'DestroyPropertySheetPage');
  asm
    mov esp, ebp
    pop ebp
    jmp [_DestroyPropertySheetPage]
  end;
end;
{$ELSE}
function DestroyPropertySheetPage; external comctl32 name 'DestroyPropertySheetPage';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _PropertySheetA: Pointer;

function PropertySheetA;
begin
  GetProcedureAddress(_PropertySheetA, comctl32, 'PropertySheetA');
  asm
    mov esp, ebp
    pop ebp
    jmp [_PropertySheetA]
  end;
end;
{$ELSE}
function PropertySheetA; external comctl32 name 'PropertySheetA';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _PropertySheetW: Pointer;

function PropertySheetW;
begin
  GetProcedureAddress(_PropertySheetW, comctl32, 'PropertySheetW');
  asm
    mov esp, ebp
    pop ebp
    jmp [_PropertySheetW]
  end;
end;
{$ELSE}
function PropertySheetW; external comctl32 name 'PropertySheetW';
{$ENDIF DYNAMIC_LINK}

{$IFDEF UNICODE}

{$IFDEF DYNAMIC_LINK}
var
  _CreatePropertySheetPage: Pointer;

function CreatePropertySheetPage;
begin
  GetProcedureAddress(_CreatePropertySheetPage, comctl32, 'CreatePropertySheetPageW');
  asm
    mov esp, ebp
    pop ebp
    jmp [_CreatePropertySheetPage]
  end;
end;
{$ELSE}
function CreatePropertySheetPage; external comctl32 name 'CreatePropertySheetPageW';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _PropertySheet: Pointer;

function PropertySheet;
begin
  GetProcedureAddress(_PropertySheet, comctl32, 'PropertySheetW');
  asm
    mov esp, ebp
    pop ebp
    jmp [_PropertySheet]
  end;
end;
{$ELSE}
function PropertySheet; external comctl32 name 'PropertySheetW';
{$ENDIF DYNAMIC_LINK}
{$ELSE}

{$IFDEF DYNAMIC_LINK}
var
  _CreatePropertySheetPage: Pointer;

function CreatePropertySheetPage;
begin
  GetProcedureAddress(_CreatePropertySheetPage, comctl32, 'CreatePropertySheetPageA');
  asm
    mov esp, ebp
    pop ebp
    jmp [_CreatePropertySheetPage]
  end;
end;
{$ELSE}
function CreatePropertySheetPage; external comctl32 name 'CreatePropertySheetPageA';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _PropertySheet: Pointer;

function PropertySheet;
begin
  GetProcedureAddress(_PropertySheet, comctl32, 'PropertySheetA');
  asm
    mov esp, ebp
    pop ebp
    jmp [_PropertySheet]
  end;
end;
{$ELSE}
function PropertySheet; external comctl32 name 'PropertySheetA';
{$ENDIF DYNAMIC_LINK}
{$ENDIF}

function PropSheet_SetCurSel(hPropSheetDlg: HWND; hPage: HPROPSHEETPAGE; Index: Integer): BOOL;
begin
  Result := BOOL(SendMessage(hPropSheetDlg, PSM_SETCURSEL, WPARAM(Index), LPARAM(hPage)));
end;

procedure PropSheet_RemovePage(hPropSheetDlg: HWND; Index: Integer; hPage: HPROPSHEETPAGE);
begin
  SendMessage(hPropSheetDlg, PSM_REMOVEPAGE, Index, LPARAM(hPage));
end;

function PropSheet_AddPage(hPropSheetDlg: HWND; hpage: HPROPSHEETPAGE): BOOL;
begin
  Result := BOOL(SendMessage(hPropSheetDlg, PSM_ADDPAGE, 0, LPARAM(hpage)));
end;

function PropSheet_Changed(hPropSheetDlg: HWND; hwndPage: HWND): BOOL;
begin
  Result := BOOL(SendMessage(hPropSheetDlg, PSM_CHANGED, WPARAM(hwndPage), 0));
end;

procedure PropSheet_RestartWindows(hPropSheetDlg: HWND);
begin
  SendMessage(hPropSheetDlg, PSM_RESTARTWINDOWS, 0, 0);
end;

procedure PropSheet_RebootSystem(hPropSheetDlg: HWND);
begin
  SendMessage(hPropSheetDlg, PSM_REBOOTSYSTEM, 0, 0);
end;

procedure PropSheet_CancelToClose(hPropSheetDlg: HWND);
begin
  PostMessage(hPropSheetDlg, PSM_CANCELTOCLOSE, 0, 0);
end;

function PropSheet_QuerySiblings(hPropSheetDlg: HWND; Param1: WPARAM; Param2: LPARAM): Integer;
begin
  Result := SendMessage(hPropSheetDlg, PSM_QUERYSIBLINGS, Param1, Param2);
end;

procedure PropSheet_UnChanged(hPropSheetDlg: HWND; hwndPage: HWND);
begin
  SendMessage(hPropSheetDlg, PSM_UNCHANGED, WPARAM(hwndPage), 0);
end;

function PropSheet_Apply(hPropSheetDlg: HWND): BOOL;
begin
  Result := BOOL(SendMessage(hPropSheetDlg, PSM_APPLY, 0, 0));
end;

procedure PropSheet_SetTitle(hPropSheetDlg: HWND; dwStyle: DWORD; lpszText: LPTSTR);
begin
  SendMessage(hPropSheetDlg, PSM_SETTITLE, dwStyle, LPARAM(LPCTSTR(lpszText)));
end;

procedure PropSheet_SetWizButtons(hPropSheetDlg: HWND; dwFlags: DWORD);
begin
  PostMessage(hPropSheetDlg, PSM_SETWIZBUTTONS, 0, LPARAM(dwFlags));
end;

function PropSheet_PressButton(hPropSheetDlg: HWND; iButton: Integer): BOOL;
begin
  Result := PostMessage(hPropSheetDlg, PSM_PRESSBUTTON, WPARAM(iButton), 0);
end;

function PropSheet_SetCurSelByID(hPropSheetDlg: HWND; id: Integer): BOOL;
begin
  Result := BOOL(SendMessage(hPropSheetDlg, PSM_SETCURSELID, 0, LPARAM(id)));
end;

procedure PropSheet_SetFinishText(hPropSheetDlg: HWND; lpszText: LPTSTR);
begin
  SendMessage(hPropSheetDlg, PSM_SETFINISHTEXT, 0, LPARAM(lpszText));
end;

function PropSheet_GetTabControl(hPropSheetDlg: HWND): HWND;
begin
  Result := SendMessage(hPropSheetDlg, PSM_GETTABCONTROL, 0, 0);
end;

function PropSheet_IsDialogMessage(hDlg: HWND; pMsg: LPMSG): BOOL;
begin
  Result := BOOL(SendMessage(hDlg, PSM_ISDIALOGMESSAGE, 0, LPARAM(pMsg)));
end;

function PropSheet_GetCurrentPageHwnd(hDlg: HWND): HWND;
begin
  Result := SendMessage(hDlg, PSM_GETCURRENTPAGEHWND, 0, 0);
end;

function PropSheet_InsertPage(hPropSheetDlg: HWND; index: Integer; hpage: HPROPSHEETPAGE): BOOL;
begin
  Result := BOOL(SendMessage(hPropSheetDlg, PSM_INSERTPAGE, WPARAM(index), LPARAM(hpage)));
end;

function PropSheet_SetHeaderTitle(hWizardDlg: HWND; iPageIndex: Integer; lpszText: LPCSTR): Integer;
begin
  Result := SendMessage(hWizardDlg, PSM_SETHEADERTITLE, WPARAM(iPageIndex), LPARAM(lpszText));
end;

procedure PropSheet_SetHeaderSubTitle(hWizardDlg: HWND; iPageIndex: Integer; pszHeaderSubTitle: LPCSTR);
begin
  SendMessage(hWizardDlg, PSM_SETHEADERSUBTITLE, WPARAM(iPageIndex), LPARAM(pszHeaderSubTitle));
end;

function PropSheet_HwndToIndex(hPropSheetDlg: HWND; hPageDlg: HWND): Integer;
begin
  Result := SendMessage(hPropSheetDlg, PSM_HWNDTOINDEX, WPARAM(hPageDlg), 0);
end;

function PropSheet_IndexToHwnd(hPropSheetDlg: HWND; iPageIndex: Integer): HWND;
begin
  Result := SendMessage(hPropSheetDlg, PSM_INDEXTOHWND, WPARAM(iPageIndex), 0);
end;

function PropSheet_PageToIndex(hPropSheetDlg: HWND; hPage: HPROPSHEETPAGE): Integer;
begin
  Result := SendMessage(hPropSheetDlg, PSM_PAGETOINDEX, 0, LPARAM(hpage));
end;

function PropSheet_IndexToPage(hPropSheetDlg: HWND; iPageIndex: Integer): HPROPSHEETPAGE;
begin
  Result := HPROPSHEETPAGE(SendMessage(hPropSheetDlg, PSM_INDEXTOPAGE, WPARAM(iPageIndex), 0));
end;

function PropSheet_IdToIndex(hPropSheetDlg: HWND; iPageId: Integer): Integer;
begin
  Result := SendMessage(hPropSheetDlg, PSM_IDTOINDEX, 0, LPARAM(iPageId));
end;

function PropSheet_IndexToId(hPropSheetDlg: HWND; iPageIndex: Integer): Integer;
begin
  Result := SendMessage(hPropSheetDlg, PSM_INDEXTOID, WPARAM(iPageIndex), 0)
end;

function PropSheet_GetResult(hPropSheetDlg: HWND): BOOL;
begin
  Result := BOOL(SendMessage(hPropSheetDlg, PSM_GETRESULT, 0, 0));
end;

function PropSheet_RecalcPageSizes(hPropSheetDlg: HWND): BOOL;
begin
  Result := BOOL(SendMessage(hPropSheetDlg, PSM_RECALCPAGESIZES, 0, 0));
end;

end.
