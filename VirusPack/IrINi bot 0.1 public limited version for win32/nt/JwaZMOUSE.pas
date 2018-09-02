{******************************************************************************}
{                                                       	               }
{ Intellimouse API interface Unit for Object Pascal                            }
{                                                       	               }
{ Portions created by Microsoft are Copyright (C) 1995-2001 Microsoft          }
{ Corporation. All Rights Reserved.                                            }
{ 								               }
{ The original file is: zmouse.h, released June 2000. The original Pascal      }
{ code is: ZMOUSE.pas, released December 2000. The initial developer of the    }
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

unit JwaZMOUSE;

interface

uses
  JwaWinUser, JwaWinType;

{****************************************************************************
*                                                                           *
* ZMOUSE.H -- Include file for IntelliMouse(tm) 1.0                         *
*                                                                           *
* NOTE:  Zmouse.h contains #defines required when providing IntelliMouse    *
*        wheel support for Windows95 and NT3.51.  Wheel is supported        *
*        natively in WinNT4.0, please refer to the NT4.0 SDK for more info  *
*        on providing support for IntelliMouse in NT4.0.                    *
*                                                                           *
* Copyright (c) 1983-1996, Microsoft Corp. All rights reserved.             *
*                                                                           *
\***************************************************************************}


{**************************************************************************
	 Client Appplication (API) Defines for Wheel rolling
***************************************************************************}


// Apps need to call RegisterWindowMessage using the #define below to
// get the message number that is sent to the foreground window
// when a wheel roll occurs

const
{$IFDEF UNICODE}
  MSH_MOUSEWHEEL = WideString('MSWHEEL_ROLLMSG');
  {$EXTERNALSYM MSH_MOUSEWHEEL}
{$ELSE}
  MSH_MOUSEWHEEL = 'MSWHEEL_ROLLMSG';
  {$EXTERNALSYM MSH_MOUSEWHEEL}
{$ENDIF}

// wParam = wheel rotation expressed in multiples of WHEEL_DELTA
// lParam is the mouse coordinates

  WHEEL_DELTA    = 120;      // Default value for rolling one notch
  {$EXTERNALSYM WHEEL_DELTA}

  WM_MOUSEWHEEL  = WM_MOUSELAST + 1;  // message that will be supported by the OS
  {$EXTERNALSYM WM_MOUSEWHEEL}

{**************************************************************************
    Client Appplication (API) Defines for
	   *  determining if wheel support active
	   *  determining # of Scroll Lines
***************************************************************************}

// Class name for MSWHEEL.EXE's invisible window
// use FindWindow to get hwnd to MSWHEEL

{$IFDEF UNICODE}
  MOUSEZ_CLASSNAME  = WideString('MouseZ');           // wheel window class
  {$EXTERNALSYM MOUSEZ_CLASSNAME}
  MOUSEZ_TITLE      = WideString('Magellan MSWHEEL'); // wheel window title
  {$EXTERNALSYM MOUSEZ_TITLE}
{$ELSE}
  MOUSEZ_CLASSNAME  = 'MouseZ';           // wheel window class
  {$EXTERNALSYM MOUSEZ_CLASSNAME}
  MOUSEZ_TITLE      = 'Magellan MSWHEEL'; // wheel window title
  {$EXTERNALSYM MOUSEZ_TITLE}
{$ENDIF}

  MSH_WHEELMODULE_CLASS = MOUSEZ_CLASSNAME;
  {$EXTERNALSYM MSH_WHEELMODULE_CLASS}
  MSH_WHEELMODULE_TITLE = MOUSEZ_TITLE;
  {$EXTERNALSYM MSH_WHEELMODULE_TITLE}

// Apps need to call RegisterWindowMessage using the #defines 
// below to get the message numbers for:
// 1) the message that can be sent to the MSWHEEL window to
//    query if wheel support is active (MSH_WHEELSUPPORT)>
// 2) the message to query for the number of scroll lines 
//    (MSH_SCROLL_LINES)  
//
// To send a message to MSWheel window, use FindWindow with the #defines
// for CLASS and TITLE above.  If FindWindow fails to find the MSWHEEL
// window or the return from SendMessage is false, then Wheel support
// is not currently available.

{$IFDEF UNICODE}
  MSH_WHEELSUPPORT = WideString('MSH_WHEELSUPPORT_MSG');  // name of msg to send to query for wheel support
  {$EXTERNALSYM MSH_WHEELSUPPORT}
{$ELSE}
  MSH_WHEELSUPPORT = 'MSH_WHEELSUPPORT_MSG';  // name of msg to send to query for wheel support
  {$EXTERNALSYM MSH_WHEELSUPPORT}
{$ENDIF}

// MSH_WHEELSUPPORT
//    wParam - not used
//    lParam - not used
//    returns BOOL - TRUE if wheel support is active, FALSE otherwise


{$IFDEF UNICODE}
  MSH_SCROLL_LINES = WideString('MSH_SCROLL_LINES_MSG');
  {$EXTERNALSYM MSH_SCROLL_LINES}
{$ELSE}
  MSH_SCROLL_LINES = 'MSH_SCROLL_LINES_MSG';
  {$EXTERNALSYM MSH_SCROLL_LINES}
{$ENDIF}

// MSH_SCROLL_LINES
//    wParam - not used
//    lParam - not used
//    returns int  - number of lines to scroll on a wheel roll

  WHEEL_PAGESCROLL = UINT_MAX;   // signifies to scroll a page, also
                                 // defined in winuser.h in the NT4.0 SDK
  {$EXTERNALSYM WHEEL_PAGESCROLL}

  SPI_SETWHEELSCROLLLINES  = 105;      // Also defined in winuser.h in the
                                       // NT4.0 SDK, please see the NT4.0 SDK
                                       // documentation for NT4.0 implementation
                                       // specifics.
                                       // For Win95 and WinNT3.51,
                                       // Mswheel broadcasts the message
                                       // WM_SETTINGCHANGE (equivalent to
                                       // WM_WININICHANGE) when the scroll
                                       // lines has changed.  Applications
                                       // will recieve the WM_SETTINGCHANGE
                                       // message with the wParam set to
                                       // SPI_SETWHEELSCROLLLINES.  When
                                       // this message is recieved the application
                                       // should query Mswheel for the new
                                       // setting.
  {$EXTERNALSYM SPI_SETWHEELSCROLLLINES}

{*********************************************************************
* INLINE FUNCTION: HwndMsWheel
* Purpose : Get a reference to MSWheel Window, the registered messages,
*           wheel support active setting, and number of scrollLines
* Params  : PUINT puiMsh_MsgMouseWheel - address of UINT to contain returned registered wheel message
*           PUINT puiMsh_Msg3DSupport - address of UINT to contain wheel support registered message
*           PUINT puiMsh_MsgScrollLines - address of UINT to contain Scroll lines registered message
*           PBOOL pf3DSupport - address of BOOL to contain returned flag for wheel support active
*           PINT  piScrollLines - address of int to contain returned scroll lines
* Returns : HWND handle to the MsWheel window
* Note    : The return value for pf3DSupport and piScrollLines is dependant
*           on the POINT32 module.  If POINT32 module is not running then
*           the values returned for these parameters will be
*           FALSE and 3, respectively.
*********************************************************************}

function HwndMSWheel(var puiMsh_MsgMouseWheel, puiMsh_Msg3DSupport,
  puiMsh_MsgScrollLines: UINT; var pf3DSupport: BOOL;
  var piScrollLines: Integer): HWND;
{$EXTERNALSYM HwndMSWheel}

implementation

function HwndMSWheel(var puiMsh_MsgMouseWheel, puiMsh_Msg3DSupport,
  puiMsh_MsgScrollLines: UINT; var pf3DSupport: BOOL;
  var piScrollLines: Integer): HWND;
begin
  Result := FindWindow(MSH_WHEELMODULE_CLASS, MSH_WHEELMODULE_TITLE);
  puiMsh_MsgMouseWheel := RegisterWindowMessage(MSH_MOUSEWHEEL);
  puiMsh_Msg3DSupport := RegisterWindowMessage(MSH_WHEELSUPPORT);
  puiMsh_MsgScrollLines := RegisterWindowMessage(MSH_SCROLL_LINES);
  if (puiMsh_Msg3DSupport <> 0) and (Result <> 0) then
    pf3DSupport := BOOL(SendMessage(Result, puiMsh_Msg3DSupport, 0, 0))
  else
    pf3DSupport := False;  // default to FALSE
  if (puiMsh_MsgScrollLines <> 0)  and (Result <> 0) then
    piScrollLines := SendMessage(Result, puiMsh_MsgScrollLines, 0, 0)
  else
    piScrollLines := 3;  // default
end;

end.
