{******************************************************************************}
{                                                       	               }
{ Active Directory Property Pages API interface Unit for Object Pascal         }
{                                                       	               }
{ Portions created by Microsoft are Copyright (C) 1995-2001 Microsoft          }
{ Corporation. All Rights Reserved.                                            }
{ 								               }
{ The original file is: adsprop.h, released June 2000. The original Pascal     }
{ code is: AdsProp.pas, released December 2000. The initial developer of the   }
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

unit JwaAdsProp;

{$WEAKPACKAGEUNIT}

{$HPPEMIT ''}
{$HPPEMIT '#include "adsprop.h"'}
{$HPPEMIT ''}

{$I WINDEFINES.INC}

interface

uses
  ActiveX {TODO}, JwaAdsTLB, JwaWinUser, JwaWinType;

//  Windows NT Active Directory Service Property Pages
//
//  Contents:   Functions and definitions used in the creation of AD property
//              sheets.

const
  WM_ADSPROP_NOTIFY_PAGEINIT   = (WM_USER + 1101); // where LPARAM is the PADSPROPINITPARAMS pointer.
  {$EXTERNALSYM WM_ADSPROP_NOTIFY_PAGEINIT}
  WM_ADSPROP_NOTIFY_PAGEHWND   = (WM_USER + 1102); // where WPARAM => page's HWND and LPARAM => page's Title
  {$EXTERNALSYM WM_ADSPROP_NOTIFY_PAGEHWND}
  WM_ADSPROP_NOTIFY_CHANGE     = (WM_USER + 1103); // used to send a change notification to a parent sheet
  {$EXTERNALSYM WM_ADSPROP_NOTIFY_CHANGE}
  WM_ADSPROP_NOTIFY_APPLY      = (WM_USER + 1104); // pages send this to the notification object.
  {$EXTERNALSYM WM_ADSPROP_NOTIFY_APPLY}
  WM_ADSPROP_NOTIFY_SETFOCUS   = (WM_USER + 1105); // used internally by the notification object.
  {$EXTERNALSYM WM_ADSPROP_NOTIFY_SETFOCUS}
  WM_ADSPROP_NOTIFY_FOREGROUND = (WM_USER + 1106); // used internally by the notification object.
  {$EXTERNALSYM WM_ADSPROP_NOTIFY_FOREGROUND}
  WM_ADSPROP_NOTIFY_EXIT       = (WM_USER + 1107); // sent on page release
  {$EXTERNALSYM WM_ADSPROP_NOTIFY_EXIT}
  WM_ADSPROP_NOTIFY_ERROR      = (WM_USER + 1110); // used to send the notification object an error message
  {$EXTERNALSYM WM_ADSPROP_NOTIFY_ERROR}
  
//+----------------------------------------------------------------------------
//
//  Structure:  ADSPROPINITPARAMS
//
//  Usage:      Used to pass page initialization information to new pages from
//              the notify object.
//
//-----------------------------------------------------------------------------

type
  // imports of a type library sometimes are missing a few decls, these are just
  // a few of them to make this file compile at all. I really should do all of
  // them one day. TODO

  PADSVALUE = ^_adsvalue;
  {$EXTERNALSYM PADSVALUE}
  PADS_ATTR_INFO = ^_ads_attr_info;
  {$EXTERNALSYM PADS_ATTR_INFO}

  PADSPROPINITPARAMS = ^ADSPROPINITPARAMS;
  {$EXTERNALSYM PADSPROPINITPARAMS}
  _ADSPROPINITPARAMS = record
    dwSize: DWORD;            // Set this to the size of the struct.
    dwFlags: DWORD;           // Reserved for future use.
    hr: HRESULT;              // If this is non-zero, then the others
    pDsObj: IDirectoryObject; // should be ignored.
    pwzCN: LPWSTR;
    pWritableAttrs: PADS_ATTR_INFO;
  end;
  {$EXTERNALSYM _ADSPROPINITPARAMS}
  ADSPROPINITPARAMS = _ADSPROPINITPARAMS;
  {$EXTERNALSYM ADSPROPINITPARAMS}
  TAdsPropInitParams = ADSPROPINITPARAMS;

//+----------------------------------------------------------------------------
//
//  Structure:  ADSPROPERROR
//
//  Usage:      Used to pass page error information to the notify object
//
//-----------------------------------------------------------------------------

  _ADSPROPERROR = record
    hwndPage: HWND;         // The HWND of the page that had the error
    pszPageTitle: PWSTR;    // The title of the page that had the error
    pszObjPath: PWSTR;      // Path to the object that the error occurred on
    pszObjClass: PWSTR;     // Class of the object that the error occurred on    
    hr: HRESULT;            // If this is non-zero, then the others
                            // pszError will be ignored
    pszError: PWSTR;        // An error message.  Used only if hr is zero
  end;
  {$EXTERNALSYM _ADSPROPERROR}
  ADSPROPERROR = _ADSPROPERROR;
  {$EXTERNALSYM ADSPROPERROR}
  PADSPROPERROR = ^ADSPROPERROR;
  {$EXTERNALSYM PADSPROPERROR}
  TAdsPropError = ADSPROPERROR;

//+----------------------------------------------------------------------------
//
//  Function:   ADsPropCreateNotifyObj
//
//  Synopsis:   Checks to see if the notification window/object exists for this
//              sheet instance and if not creates it.
//
//  Arguments:  [pAppThdDataObj] - the unmarshalled data object pointer.
//              [pwzADsObjName]  - object path name.
//              [phNotifyObj]    - to return the notificion window handle.
//
//  Returns:    HRESULTs.
//
//-----------------------------------------------------------------------------

function ADsPropCreateNotifyObj(pAppThdDataObj: Pointer{LPDATAOBJECT};
  pwzADsObjName: PWSTR; var phNotifyObj: HWND): HRESULT; stdcall;
{$EXTERNALSYM ADsPropCreateNotifyObj}

//+----------------------------------------------------------------------------
//
//  Function:   ADsPropGetInitInfo
//
//  Synopsis:   Pages call this at their init time to retreive DS object info.
//
//  Arguments:  [hNotifyObj]  - the notificion window handle.
//              [pInitParams] - struct filled in with DS object info. This
//                              struct must be allocated by the caller before
//                              the call.
//
//  Returns:    FALSE if the notify window has gone away for some reason or
//              if the parameters are invalid.
//
//  Notes:      This call results in the sending of the
//              WM_ADSPROP_NOTIFY_PAGEINIT message to the notify window.
//              pInitParams->pWritableAttrs can be NULL if there are no
//              writable attributes.
//
//-----------------------------------------------------------------------------

function ADsPropGetInitInfo(hNotifyObj: HWND; pInitParams: PADSPROPINITPARAMS): BOOL; stdcall;
{$EXTERNALSYM ADsPropGetInitInfo}

//+----------------------------------------------------------------------------
//
//  Function:   ADsPropSetHwndWithTitle
//
//  Synopsis:   Pages call this at their dialog init time to send their hwnd
//              to the Notify object.
//
//  Arguments:  [hNotifyObj]  - the notificion window handle.
//              [hPage]       - the page's window handle.
//              [ptzTitle]    - the page's title
//
//  Returns:    FALSE if the notify window has gone away for some reason.
//
//  Notes:      Sends the WM_ADSPROP_NOTIFY_PAGEHWND message to the notify
//              window. Use this function instead of ADsPropSetHwnd for
//              multi-select property pages
//
//-----------------------------------------------------------------------------

function ADsPropSetHwndWithTitle(hNotifyObj, hPage: HWND; ptzTitle: PTSTR): BOOL; stdcall;
{$EXTERNALSYM ADsPropSetHwndWithTitle}

//+----------------------------------------------------------------------------
//
//  Function:   ADsPropSetHwnd
//
//  Synopsis:   Pages call this at their dialog init time to send their hwnd
//              to the Notify object.
//
//  Arguments:  [hNotifyObj]  - the notificion window handle.
//              [hPage]       - the page's window handle.
//              [ptzTitle]    - the page's title
//
//  Returns:    FALSE if the notify window has gone away for some reason.
//
//  Notes:      Sends the WM_ADSPROP_NOTIFY_PAGEHWND message to the notify
//              window.
//
//-----------------------------------------------------------------------------

function ADsPropSetHwnd(hNotifyObj: HWND; hPage: HWND): BOOL; stdcall;
{$EXTERNALSYM ADsPropSetHwnd}

//+----------------------------------------------------------------------------
//
//  function:   ADsPropCheckIfWritable
//
//  Synopsis:   See if the attribute is writable by checking if it is in
//              the allowedAttributesEffective array.
//
//  Arguments:  [pwzAttr]        - the attribute name.
//              [pWritableAttrs] - the array of writable attributes.
//
//  Returns:    FALSE if the attribute name is not found in the writable-attrs
//              array or if the array pointer is NULL.
//
//-----------------------------------------------------------------------------

function ADsPropCheckIfWritable(pwzAttr: PWSTR; pWritableAttrs: PADS_ATTR_INFO): BOOL; stdcall;
{$EXTERNALSYM ADsPropCheckIfWritable}

//+----------------------------------------------------------------------------
//
//  function:   ADsPropSendErrorMessage
//
//  Synopsis:   Adds an error message to a list which is presented when
//              ADsPropShowErrorDialog is called
//
//  Arguments:  [hNotifyObj]  - the notificion window handle.
//              [pError]      - the error structure
//
//  Returns:    FALSE if the notify window has gone away for some reason.
//
//-----------------------------------------------------------------------------

function ADsPropSendErrorMessage(hNotifyObj: HWND; pError: PADSPROPERROR): BOOL; stdcall;
{$EXTERNALSYM ADsPropSendErrorMessage}

//+----------------------------------------------------------------------------
//
//  function:   ADsPropShowErrorDialog
//
//  Synopsis:   Presents an error dialog with the error messages accumulated
//              through calls to ADsPropSendErrorMessage
//
//  Arguments:  [hNotifyObj]  - the notificion window handle.
//              [hPage]       - the property page window handle.
//
//  Returns:    FALSE if the notify window has gone away for some reason.
//
//-----------------------------------------------------------------------------

function ADsPropShowErrorDialog(hNotifyObj: HWND; hPage: HWND): BOOL; stdcall;
{$EXTERNALSYM ADsPropShowErrorDialog}

implementation

const
  dsprop = 'dsprop.dll';


{$IFDEF DYNAMIC_LINK}
var
  _ADsPropCreateNotifyObj: Pointer;

function ADsPropCreateNotifyObj;
begin
  GetProcedureAddress(_ADsPropCreateNotifyObj, dsprop, 'ADsPropCreateNotifyObj');
  asm
    mov esp, ebp
    pop ebp
    jmp [_ADsPropCreateNotifyObj]
  end;
end;
{$ELSE}
function ADsPropCreateNotifyObj; external dsprop name 'ADsPropCreateNotifyObj';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _ADsPropGetInitInfo: Pointer;

function ADsPropGetInitInfo;
begin
  GetProcedureAddress(_ADsPropGetInitInfo, dsprop, 'ADsPropGetInitInfo');
  asm
    mov esp, ebp
    pop ebp
    jmp [_ADsPropGetInitInfo]
  end;
end;
{$ELSE}
function ADsPropGetInitInfo; external dsprop name 'ADsPropGetInitInfo';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _ADsPropSetHwndWithTitle: Pointer;

function ADsPropSetHwndWithTitle;
begin
  GetProcedureAddress(_ADsPropSetHwndWithTitle, dsprop, 'ADsPropSetHwndWithTitle');
  asm
    mov esp, ebp
    pop ebp
    jmp [_ADsPropSetHwndWithTitle]
  end;
end;
{$ELSE}
function ADsPropSetHwndWithTitle; external dsprop name 'ADsPropSetHwndWithTitle';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _ADsPropSetHwnd: Pointer;

function ADsPropSetHwnd;
begin
  GetProcedureAddress(_ADsPropSetHwnd, dsprop, 'ADsPropSetHwnd');
  asm
    mov esp, ebp
    pop ebp
    jmp [_ADsPropSetHwnd]
  end;
end;
{$ELSE}
function ADsPropSetHwnd; external dsprop name 'ADsPropSetHwnd';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _ADsPropCheckIfWritable: Pointer;

function ADsPropCheckIfWritable;
begin
  GetProcedureAddress(_ADsPropCheckIfWritable, dsprop, 'ADsPropCheckIfWritable');
  asm
    mov esp, ebp
    pop ebp
    jmp [_ADsPropCheckIfWritable]
  end;
end;
{$ELSE}
function ADsPropCheckIfWritable; external dsprop name 'ADsPropCheckIfWritable';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _ADsPropSendErrorMessage: Pointer;

function ADsPropSendErrorMessage;
begin
  GetProcedureAddress(_ADsPropSendErrorMessage, dsprop, 'ADsPropSendErrorMessage');
  asm
    mov esp, ebp
    pop ebp
    jmp [_ADsPropSendErrorMessage]
  end;
end;
{$ELSE}
function ADsPropSendErrorMessage; external dsprop name 'ADsPropSendErrorMessage';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _ADsPropShowErrorDialog: Pointer;

function ADsPropShowErrorDialog;
begin
  GetProcedureAddress(_ADsPropShowErrorDialog, dsprop, 'ADsPropShowErrorDialog');
  asm
    mov esp, ebp
    pop ebp
    jmp [_ADsPropShowErrorDialog]
  end;
end;
{$ELSE}
function ADsPropShowErrorDialog; external dsprop name 'ADsPropShowErrorDialog';
{$ENDIF DYNAMIC_LINK}

end.
