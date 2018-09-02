{******************************************************************************}
{                                                       	               }
{ Hooking mechanism to receive system events interface Unit for Object Pascal  }
{                                                       	               }
{ Portions created by Microsoft are Copyright (C) 1995-2001 Microsoft          }
{ Corporation. All Rights Reserved.                                            }
{ 								               }
{ The original file is: winable.h, released June 2000. The original Pascal     }
{ code is: WinAble.pas, released December 2000. The initial developer of the   }
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

unit JwaWinAble;

{$WEAKPACKAGEUNIT}

{$HPPEMIT ''}
{$HPPEMIT '#include "WinAble.h"'}
{$HPPEMIT ''}

{$I WINDEFINES.INC}

interface

uses
  JwaWinType;

//
// This gets GUI information out of context.  If you pass in a NULL thread ID,
// we will get the 'global' information, using the foreground thread.  This
// is guaranteed to be the real active window, focus window, etc.  Yes, you
// could do it yourself by calling GetForegorundWindow, getting the thread ID
// of that window via GetWindowThreadProcessId, then passing the ID into
// GetGUIThreadInfo().  However, that takes three calls and aside from being
// a pain, anything could happen in the middle.  So passing in NULL gets
// you stuff in one call and hence also works right.
//

type
  LPGUITHREADINFO = ^GUITHREADINFO;
  {$EXTERNALSYM LPGUITHREADINFO}
  tagGUITHREADINFO = record
    cbSize: DWORD;
    flags: DWORD;
    hwndActive: HWND;
    hwndFocus: HWND;
    hwndCapture: HWND;
    hwndMenuOwner: HWND;
    hwndMoveSize: HWND;
    hwndCaret: HWND;
    rcCaret: RECT;
  end;
  {$EXTERNALSYM tagGUITHREADINFO}
  GUITHREADINFO = tagGUITHREADINFO;
  {$EXTERNALSYM GUITHREADINFO}
  TGuiThreadInfo = GUITHREADINFO;
  PGuiThreadInfo = LPGUITHREADINFO;

const
  GUI_CARETBLINKING  = $00000001;
  {$EXTERNALSYM GUI_CARETBLINKING}
  GUI_INMOVESIZE     = $00000002;
  {$EXTERNALSYM GUI_INMOVESIZE}
  GUI_INMENUMODE     = $00000004;
  {$EXTERNALSYM GUI_INMENUMODE}
  GUI_SYSTEMMENUMODE = $00000008;
  {$EXTERNALSYM GUI_SYSTEMMENUMODE}
  GUI_POPUPMENUMODE  = $00000010;
  {$EXTERNALSYM GUI_POPUPMENUMODE}

function GetGUIThreadInfo(idThread: DWORD; var lpgui: GUITHREADINFO): BOOL; stdcall;
{$EXTERNALSYM GetGUIThreadInfo}

function GetWindowModuleFileNameW(hwnd: HWND; lpFileName: LPWSTR; cchFileName: UINT): UINT; stdcall;
{$EXTERNALSYM GetWindowModuleFileNameW}
function GetWindowModuleFileNameA(hwnd: HWND; lpFileName: LPSTR; cchFileName: UINT): UINT; stdcall;
{$EXTERNALSYM GetWindowModuleFileNameA}

{$IFDEF UNICODE}
function GetWindowModuleFileName(hwnd: HWND; lpFileName: LPWSTR; cchFileName: UINT): UINT; stdcall;
{$EXTERNALSYM GetWindowModuleFileName}
{$ELSE}
function GetWindowModuleFileName(hwnd: HWND; lpFileName: LPSTR; cchFileName: UINT): UINT; stdcall;
{$EXTERNALSYM GetWindowModuleFileName}
{$ENDIF}

//
// This returns FALSE if the caller doesn't have permissions to do this
// esp. if someone else is dorking with input.  I.E., if some other thread
// disabled input, and thread 2 tries to diable/enable it, the call will
// fail since thread 1 has the cookie.
//

function BlockInput(fBlockIt: BOOL): BOOL; stdcall;
{$EXTERNALSYM BlockInput}

//
// Note that the dwFlags field uses the same flags as keybd_event and
// mouse_event, depending on what type of input this is.
//

type
  LPMOUSEINPUT = ^MOUSEINPUT;
  {$EXTERNALSYM LPMOUSEINPUT}
  PMOUSEINPUT = ^MOUSEINPUT;
  {$EXTERNALSYM PMOUSEINPUT}
  tagMOUSEINPUT = record
    dx: LONG;
    dy: LONG;
    mouseData: DWORD;
    dwFlags: DWORD;
    time: DWORD;
    dwExtraInfo: DWORD;
  end;
  {$EXTERNALSYM tagMOUSEINPUT}
  MOUSEINPUT = tagMOUSEINPUT;
  {$EXTERNALSYM MOUSEINPUT}
  TMouseInput = MOUSEINPUT;

  LPKEYBDINPUT = ^KEYBDINPUT;
  {$EXTERNALSYM LPKEYBDINPUT}
  PKEYBDINPUT = ^KEYBDINPUT;
  {$EXTERNALSYM PKEYBDINPUT}
  tagKEYBDINPUT = record
    wVk: WORD;
    wScan: WORD;
    dwFlags: DWORD;
    time: DWORD;
    dwExtraInfo: DWORD;
  end;
  {$EXTERNALSYM tagKEYBDINPUT}
  KEYBDINPUT = tagKEYBDINPUT;
  {$EXTERNALSYM KEYBDINPUT}
  TKeybdInput = KEYBDINPUT;

  LPHARDWAREINPUT = ^HARDWAREINPUT;
  {$EXTERNALSYM LPHARDWAREINPUT}
  PHARDWAREINPUT = ^HARDWAREINPUT;
  {$EXTERNALSYM PHARDWAREINPUT}
  tagHARDWAREINPUT = record
    uMsg: DWORD;
    wParamL: WORD;
    wParamH: WORD;
    dwExtraInfo: DWORD;
  end;
  {$EXTERNALSYM tagHARDWAREINPUT}
  HARDWAREINPUT = tagHARDWAREINPUT;
  {$EXTERNALSYM HARDWAREINPUT}
  THardwareInput = HARDWAREINPUT;

const
  INPUT_MOUSE    = 0;
  {$EXTERNALSYM INPUT_MOUSE}
  INPUT_KEYBOARD = 1;
  {$EXTERNALSYM INPUT_KEYBOARD}
  INPUT_HARDWARE = 2;
  {$EXTERNALSYM INPUT_HARDWARE}

type
  LPINPUT = ^INPUT;
  {$EXTERNALSYM LPINPUT}
  PINPUT = ^INPUT;
  {$EXTERNALSYM PINPUT}
  tagINPUT = record
    type_: DWORD;
    case Integer of
      0: (mi: MOUSEINPUT);
      1: (ki: KEYBDINPUT);
      2: (hi: HARDWAREINPUT);
  end;
  {$EXTERNALSYM tagINPUT}
  INPUT = tagINPUT;
  {$EXTERNALSYM INPUT}
  TInput = INPUT;

//
// This returns the number of inputs played back.  It will disable input
// first, play back as many as possible, then reenable input.  In the middle
// it will pulse the RIT to make sure that the fixed input queue doesn't
// fill up.
//

function SendInput(cInputs: UINT; pInputs: LPINPUT; cbSize: Integer): UINT; stdcall;
{$EXTERNALSYM SendInput}

const
  CCHILDREN_FRAME = 7;
  {$EXTERNALSYM CCHILDREN_FRAME}

//
// This generates a notification that anyone watching for it will get.
// This call is superfast if nobody is hooking anything.
//

procedure NotifyWinEvent(event: DWORD; hwnd: HWND; idObject, idChild: LONG); stdcall;
{$EXTERNALSYM NotifyWinEvent}

//
// hwnd + idObject can be used with OLEACC.DLL's OleGetObjectFromWindow()
// to get an interface pointer to the container.  indexChild is the item
// within the container in question.  Setup a VARIANT with vt VT_I4 and 
// lVal the indexChild and pass that in to all methods.  Then you 
// are raring to go.
//

//
// Common object IDs (cookies, only for sending WM_GETOBJECT to get at the
// thing in question).  Positive IDs are reserved for apps (app specific),
// negative IDs are system things and are global, 0 means "just little old
// me".
//

const
  CHILDID_SELF = 0;
  {$EXTERNALSYM CHILDID_SELF}

// Reserved IDs for system objects

  OBJID_WINDOW   = DWORD($00000000);
  {$EXTERNALSYM OBJID_WINDOW}
  OBJID_SYSMENU  = DWORD($FFFFFFFF);
  {$EXTERNALSYM OBJID_SYSMENU}
  OBJID_TITLEBAR = DWORD($FFFFFFFE);
  {$EXTERNALSYM OBJID_TITLEBAR}
  OBJID_MENU     = DWORD($FFFFFFFD);
  {$EXTERNALSYM OBJID_MENU}
  OBJID_CLIENT   = DWORD($FFFFFFFC);
  {$EXTERNALSYM OBJID_CLIENT}
  OBJID_VSCROLL  = DWORD($FFFFFFFB);
  {$EXTERNALSYM OBJID_VSCROLL}
  OBJID_HSCROLL  = DWORD($FFFFFFFA);
  {$EXTERNALSYM OBJID_HSCROLL}
  OBJID_SIZEGRIP = DWORD($FFFFFFF9);
  {$EXTERNALSYM OBJID_SIZEGRIP}
  OBJID_CARET    = DWORD($FFFFFFF8);
  {$EXTERNALSYM OBJID_CARET}
  OBJID_CURSOR   = DWORD($FFFFFFF7);
  {$EXTERNALSYM OBJID_CURSOR}
  OBJID_ALERT    = DWORD($FFFFFFF6);
  {$EXTERNALSYM OBJID_ALERT}
  OBJID_SOUND    = DWORD($FFFFFFF5);
  {$EXTERNALSYM OBJID_SOUND}

//
// System Alerts (indexChild of system ALERT notification)
//

  ALERT_SYSTEM_INFORMATIONAL = 1; // MB_INFORMATION
  {$EXTERNALSYM ALERT_SYSTEM_INFORMATIONAL}
  ALERT_SYSTEM_WARNING       = 2; // MB_WARNING
  {$EXTERNALSYM ALERT_SYSTEM_WARNING}
  ALERT_SYSTEM_ERROR         = 3; // MB_ERROR
  {$EXTERNALSYM ALERT_SYSTEM_ERROR}
  ALERT_SYSTEM_QUERY         = 4; // MB_QUESTION
  {$EXTERNALSYM ALERT_SYSTEM_QUERY}
  ALERT_SYSTEM_CRITICAL      = 5; // HardSysErrBox
  {$EXTERNALSYM ALERT_SYSTEM_CRITICAL}
  CALERT_SYSTEM              = 6;
  {$EXTERNALSYM CALERT_SYSTEM}

type
  HWINEVENTHOOK = DWORD;
  {$EXTERNALSYM HWINEVENTHOOK}

  WINEVENTPROC = procedure (
    hEvent: HWINEVENTHOOK;
    event: DWORD;
    hwnd: HWND;
    idObject: LONG;
    idChild: LONG;
    idEventThread: DWORD;
    dwmsEventTime: DWORD); stdcall;
  {$EXTERNALSYM WINEVENTPROC}
  TWinEventProc = WINEVENTPROC;

const
  WINEVENT_OUTOFCONTEXT   = $0000; // Events are ASYNC
  {$EXTERNALSYM WINEVENT_OUTOFCONTEXT}
  WINEVENT_SKIPOWNTHREAD  = $0001; // Don't call back for events on installer's thread
  {$EXTERNALSYM WINEVENT_SKIPOWNTHREAD}
  WINEVENT_SKIPOWNPROCESS = $0002; // Don't call back for events on installer's process
  {$EXTERNALSYM WINEVENT_SKIPOWNPROCESS}
  WINEVENT_INCONTEXT      = $0004; // Events are SYNC, this causes your dll to be injected into every process
  {$EXTERNALSYM WINEVENT_INCONTEXT}
  WINEVENT_32BITCALLER    = $8000; // ;Internal
  {$EXTERNALSYM WINEVENT_32BITCALLER}
  WINEVENT_VALID          = $8007; // ;Internal
  {$EXTERNALSYM WINEVENT_VALID}

function SetWinEventHook(eventMin, eventMax: DWORD; hmodWinEventProc: HMODULE;
  lpfnWinEventProc: WINEVENTPROC; idProcess, idThread, dwFlags: DWORD): HWINEVENTHOOK; stdcall;
{$EXTERNALSYM SetWinEventHook}

//
// Returns zero on failure, or a DWORD ID if success.  We will clean up any
// event hooks installed by the current process when it goes away, if it
// hasn't cleaned the hooks up itself.  But to dynamically unhook, call
// UnhookWinEvents().
//

function UnhookWinEvent(hEvent: HWINEVENTHOOK): BOOL; stdcall;
{$EXTERNALSYM UnhookWinEvent}

//
// If idProcess isn't zero but idThread is, will hook all threads in that
//      process.
// If idThread isn't zero but idProcess is, will hook idThread only.
// If both are zero, will hook everything
//


//
// EVENT DEFINITION
//

const
  EVENT_MIN = $00000001;
  {$EXTERNALSYM EVENT_MIN}
  EVENT_MAX = $7FFFFFFF;
  {$EXTERNALSYM EVENT_MAX}

//
//  EVENT_SYSTEM_SOUND
//  Sent when a sound is played.  Currently nothing is generating this, we
//  are going to be cleaning up the SOUNDSENTRY feature in the control panel
//  and will use this at that time.  Applications implementing WinEvents
//  are perfectly welcome to use it.  Clients of IAccessible* will simply
//  turn around and get back a non-visual object that describes the sound.
//

  EVENT_SYSTEM_SOUND = $0001;
  {$EXTERNALSYM EVENT_SYSTEM_SOUND}

//
// EVENT_SYSTEM_ALERT
// Sent when an alert needs to be given to the user.  MessageBoxes generate
// alerts for example.
//

  EVENT_SYSTEM_ALERT = $0002;
  {$EXTERNALSYM EVENT_SYSTEM_ALERT}

//
// EVENT_SYSTEM_FOREGROUND
// Sent when the foreground (active) window changes, even if it is changing
// to another window in the same thread as the previous one.
//

  EVENT_SYSTEM_FOREGROUND = $0003;
  {$EXTERNALSYM EVENT_SYSTEM_FOREGROUND}

//
// EVENT_SYSTEM_MENUSTART
// EVENT_SYSTEM_MENUEND
// Sent when entering into and leaving from menu mode (system, app bar, and
// track popups).
//

  EVENT_SYSTEM_MENUSTART = $0004;
  {$EXTERNALSYM EVENT_SYSTEM_MENUSTART}
  EVENT_SYSTEM_MENUEND   = $0005;
  {$EXTERNALSYM EVENT_SYSTEM_MENUEND}

//
// EVENT_SYSTEM_MENUPOPUPSTART
// EVENT_SYSTEM_MENUPOPUPEND
// Sent when a menu popup comes up and just before it is taken down.  Note
// that for a call to TrackPopupMenu(), a client will see EVENT_SYSTEM_MENUSTART
// followed almost immediately by EVENT_SYSTEM_MENUPOPUPSTART for the popup
// being shown.
//

  EVENT_SYSTEM_MENUPOPUPSTART = $0006;
  {$EXTERNALSYM EVENT_SYSTEM_MENUPOPUPSTART}
  EVENT_SYSTEM_MENUPOPUPEND   = $0007;
  {$EXTERNALSYM EVENT_SYSTEM_MENUPOPUPEND}

//
// EVENT_SYSTEM_CAPTURESTART
// EVENT_SYSTEM_CAPTUREEND
// Sent when a window takes the capture and releases the capture.
//

  EVENT_SYSTEM_CAPTURESTART = $0008;
  {$EXTERNALSYM EVENT_SYSTEM_CAPTURESTART}
  EVENT_SYSTEM_CAPTUREEND   = $0009;
  {$EXTERNALSYM EVENT_SYSTEM_CAPTUREEND}

//
// EVENT_SYSTEM_MOVESIZESTART
// EVENT_SYSTEM_MOVESIZEEND
// Sent when a window enters and leaves move-size dragging mode.
//

  EVENT_SYSTEM_MOVESIZESTART = $000A;
  {$EXTERNALSYM EVENT_SYSTEM_MOVESIZESTART}
  EVENT_SYSTEM_MOVESIZEEND   = $000B;
  {$EXTERNALSYM EVENT_SYSTEM_MOVESIZEEND}

//
// EVENT_SYSTEM_CONTEXTHELPSTART
// EVENT_SYSTEM_CONTEXTHELPEND
// Sent when a window enters and leaves context sensitive help mode.
//

  EVENT_SYSTEM_CONTEXTHELPSTART = $000C;
  {$EXTERNALSYM EVENT_SYSTEM_CONTEXTHELPSTART}
  EVENT_SYSTEM_CONTEXTHELPEND   = $000D;
  {$EXTERNALSYM EVENT_SYSTEM_CONTEXTHELPEND}

//
// EVENT_SYSTEM_DRAGDROPSTART
// EVENT_SYSTEM_DRAGDROPEND
// Sent when a window enters and leaves drag drop mode.  Note that it is up
// to apps and OLE to generate this, since the system doesn't know.  Like
// EVENT_SYSTEM_SOUND, it will be a while before this is prevalent.
//

  EVENT_SYSTEM_DRAGDROPSTART = $000E;
  {$EXTERNALSYM EVENT_SYSTEM_DRAGDROPSTART}
  EVENT_SYSTEM_DRAGDROPEND   = $000F;
  {$EXTERNALSYM EVENT_SYSTEM_DRAGDROPEND}

//
// EVENT_SYSTEM_DIALOGSTART
// EVENT_SYSTEM_DIALOGEND
// Sent when a dialog comes up and just before it goes away.
//

  EVENT_SYSTEM_DIALOGSTART = $0010;
  {$EXTERNALSYM EVENT_SYSTEM_DIALOGSTART}
  EVENT_SYSTEM_DIALOGEND   = $0011;
  {$EXTERNALSYM EVENT_SYSTEM_DIALOGEND}

//
// EVENT_SYSTEM_SCROLLINGSTART
// EVENT_SYSTEM_SCROLLINGEND
// Sent when beginning and ending the tracking of a scrollbar in a window,
// and also for scrollbar controls.
//

  EVENT_SYSTEM_SCROLLINGSTART = $0012;
  {$EXTERNALSYM EVENT_SYSTEM_SCROLLINGSTART}
  EVENT_SYSTEM_SCROLLINGEND   = $0013;
  {$EXTERNALSYM EVENT_SYSTEM_SCROLLINGEND}

//
// EVENT_SYSTEM_SWITCHSTART
// EVENT_SYSTEM_SWITCHEND
// Sent when beginning and ending alt-tab mode with the switch window.
//

  EVENT_SYSTEM_SWITCHSTART = $0014;
  {$EXTERNALSYM EVENT_SYSTEM_SWITCHSTART}
  EVENT_SYSTEM_SWITCHEND   = $0015;
  {$EXTERNALSYM EVENT_SYSTEM_SWITCHEND}

//
// EVENT_SYSTEM_MINIMIZESTART
// EVENT_SYSTEM_MINIMIZEEND
// Sent when a window minimizes and just before it restores.
//

  EVENT_SYSTEM_MINIMIZESTART = $0016;
  {$EXTERNALSYM EVENT_SYSTEM_MINIMIZESTART}
  EVENT_SYSTEM_MINIMIZEEND   = $0017;
  {$EXTERNALSYM EVENT_SYSTEM_MINIMIZEEND}

//
// Object events
//
// The system AND apps generate these.  The system generates these for 
// real windows.  Apps generate these for objects within their window which
// act like a separate control, e.g. an item in a list view.
//
// For all events, if you want detailed accessibility information, callers
// should
//      * Call AccessibleObjectFromWindow() with the hwnd, idObject parameters
//          of the event, and IID_IAccessible as the REFIID, to get back an 
//          IAccessible* to talk to
//      * Initialize and fill in a VARIANT as VT_I4 with lVal the idChild
//          parameter of the event.
//      * If idChild isn't zero, call get_accChild() in the container to see
//          if the child is an object in its own right.  If so, you will get
//          back an IDispatch* object for the child.  You should release the
//          parent, and call QueryInterface() on the child object to get its
//          IAccessible*.  Then you talk directly to the child.  Otherwise,
//          if get_accChild() returns you nothing, you should continue to
//          use the child VARIANT.  You will ask the container for the properties
//          of the child identified by the VARIANT.  In other words, the
//          child in this case is accessible but not a full-blown object.
//          Like a button on a titlebar which is 'small' and has no children.
//          

//

  EVENT_OBJECT_CREATE  = $8000; // hwnd + ID + idChild is created item
  {$EXTERNALSYM EVENT_OBJECT_CREATE}
  EVENT_OBJECT_DESTROY = $8001; // hwnd + ID + idChild is destroyed item
  {$EXTERNALSYM EVENT_OBJECT_DESTROY}
  EVENT_OBJECT_SHOW    = $8002; // hwnd + ID + idChild is shown item
  {$EXTERNALSYM EVENT_OBJECT_SHOW}
  EVENT_OBJECT_HIDE    = $8003; // hwnd + ID + idChild is hidden item
  {$EXTERNALSYM EVENT_OBJECT_HIDE}
  EVENT_OBJECT_REORDER = $8004; // hwnd + ID + idChild is parent of zordering children
  {$EXTERNALSYM EVENT_OBJECT_REORDER}

//
// NOTE:
// Minimize the number of notifications!  
//
// When you are hiding a parent object, obviously all child objects are no 
// longer visible on screen.  They still have the same "visible" status, 
// but are not truly visible.  Hence do not send HIDE notifications for the
// children also.  One implies all.  The same goes for SHOW.
//

  EVENT_OBJECT_FOCUS           = $8005; // hwnd + ID + idChild is focused item
  {$EXTERNALSYM EVENT_OBJECT_FOCUS}
  EVENT_OBJECT_SELECTION       = $8006; // hwnd + ID + idChild is selected item (if only one), or idChild is OBJID_WINDOW if complex
  {$EXTERNALSYM EVENT_OBJECT_SELECTION}
  EVENT_OBJECT_SELECTIONADD    = $8007; // hwnd + ID + idChild is item added
  {$EXTERNALSYM EVENT_OBJECT_SELECTIONADD}
  EVENT_OBJECT_SELECTIONREMOVE = $8008; // hwnd + ID + idChild is item removed
  {$EXTERNALSYM EVENT_OBJECT_SELECTIONREMOVE}
  EVENT_OBJECT_SELECTIONWITHIN = $8009; // hwnd + ID + idChild is parent of changed selected items
  {$EXTERNALSYM EVENT_OBJECT_SELECTIONWITHIN}

//
// NOTES:
// There is only one "focused" child item in a parent.  This is the place
// keystrokes are going at a given moment.  Hence only send a notification 
// about where the NEW focus is going.  A NEW item getting the focus already 
// implies that the OLD item is losing it.
//
// SELECTION however can be multiple.  Hence the different SELECTION
// notifications.  Here's when to use each:
//
// (1) Send a SELECTION notification in the simple single selection
//     case (like the focus) when the item with the selection is
//     merely moving to a different item within a container.  hwnd + ID
//     is the container control, idChildItem is the new child with the
//     selection.
//
// (2) Send a SELECTIONADD notification when a new item has simply been added 
//     to the selection within a container.  This is appropriate when the
//     number of newly selected items is very small.  hwnd + ID is the
//     container control, idChildItem is the new child added to the selection.
//
// (3) Send a SELECTIONREMOVE notification when a new item has simply been
//     removed from the selection within a container.  This is appropriate
//     when the number of newly selected items is very small, just like
//     SELECTIONADD.  hwnd + ID is the container control, idChildItem is the
//     new child removed from the selection.
//
// (4) Send a SELECTIONWITHIN notification when the selected items within a
//     control have changed substantially.  Rather than propagate a large
//     number of changes to reflect removal for some items, addition of
//     others, just tell somebody who cares that a lot happened.  It will
//     be faster an easier for somebody watching to just turn around and
//     query the container control what the new bunch of selected items
//     are.
//

  EVENT_OBJECT_STATECHANGE    = $800A; // hwnd + ID + idChild is item w/ state change
  {$EXTERNALSYM EVENT_OBJECT_STATECHANGE}
  EVENT_OBJECT_LOCATIONCHANGE = $800B; // hwnd + ID + idChild is moved/sized item
  {$EXTERNALSYM EVENT_OBJECT_LOCATIONCHANGE}

  EVENT_OBJECT_NAMECHANGE        = $800C; // hwnd + ID + idChild is item w/ name change
  {$EXTERNALSYM EVENT_OBJECT_NAMECHANGE}
  EVENT_OBJECT_DESCRIPTIONCHANGE = $800D; // hwnd + ID + idChild is item w/ desc change
  {$EXTERNALSYM EVENT_OBJECT_DESCRIPTIONCHANGE}
  EVENT_OBJECT_VALUECHANGE       = $800E; // hwnd + ID + idChild is item w/ value change
  {$EXTERNALSYM EVENT_OBJECT_VALUECHANGE}
  EVENT_OBJECT_PARENTCHANGE      = $800F; // hwnd + ID + idChild is item w/ new parent
  {$EXTERNALSYM EVENT_OBJECT_PARENTCHANGE}
  EVENT_OBJECT_HELPCHANGE        = $8010; // hwnd + ID + idChild is item w/ help change
  {$EXTERNALSYM EVENT_OBJECT_HELPCHANGE}
  EVENT_OBJECT_DEFACTIONCHANGE   = $8011; // hwnd + ID + idChild is item w/ def action change
  {$EXTERNALSYM EVENT_OBJECT_DEFACTIONCHANGE}
  EVENT_OBJECT_ACCELERATORCHANGE = $8012; // hwnd + ID + idChild is item w/ keybd accel change
  {$EXTERNALSYM EVENT_OBJECT_ACCELERATORCHANGE}

implementation

const
  user32 = 'user32.dll';


{$IFDEF DYNAMIC_LINK}
var
  _GetGUIThreadInfo: Pointer;

function GetGUIThreadInfo;
begin
  GetProcedureAddress(_GetGUIThreadInfo, user32, 'GetGUIThreadInfo');
  asm
    mov esp, ebp
    pop ebp
    jmp [_GetGUIThreadInfo]
  end;
end;
{$ELSE}
function GetGUIThreadInfo; external user32 name 'GetGUIThreadInfo';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _GetWindowModuleFileNameW: Pointer;

function GetWindowModuleFileNameW;
begin
  GetProcedureAddress(_GetWindowModuleFileNameW, user32, 'GetWindowModuleFileNameW');
  asm
    mov esp, ebp
    pop ebp
    jmp [_GetWindowModuleFileNameW]
  end;
end;
{$ELSE}
function GetWindowModuleFileNameW; external user32 name 'GetWindowModuleFileNameW';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _GetWindowModuleFileNameA: Pointer;

function GetWindowModuleFileNameA;
begin
  GetProcedureAddress(_GetWindowModuleFileNameA, user32, 'GetWindowModuleFileNameA');
  asm
    mov esp, ebp
    pop ebp
    jmp [_GetWindowModuleFileNameA]
  end;
end;
{$ELSE}
function GetWindowModuleFileNameA; external user32 name 'GetWindowModuleFileNameA';
{$ENDIF DYNAMIC_LINK}
{$IFDEF UNICODE}

{$IFDEF DYNAMIC_LINK}
var
  _GetWindowModuleFileName: Pointer;

function GetWindowModuleFileName;
begin
  GetProcedureAddress(_GetWindowModuleFileName, user32, 'GetWindowModuleFileNameW');
  asm
    mov esp, ebp
    pop ebp
    jmp [_GetWindowModuleFileName]
  end;
end;
{$ELSE}
function GetWindowModuleFileName; external user32 name 'GetWindowModuleFileNameW';
{$ENDIF DYNAMIC_LINK}
{$ELSE}

{$IFDEF DYNAMIC_LINK}
var
  _GetWindowModuleFileName: Pointer;

function GetWindowModuleFileName;
begin
  GetProcedureAddress(_GetWindowModuleFileName, user32, 'GetWindowModuleFileNameA');
  asm
    mov esp, ebp
    pop ebp
    jmp [_GetWindowModuleFileName]
  end;
end;
{$ELSE}
function GetWindowModuleFileName; external user32 name 'GetWindowModuleFileNameA';
{$ENDIF DYNAMIC_LINK}
{$ENDIF}

{$IFDEF DYNAMIC_LINK}
var
  _BlockInput: Pointer;

function BlockInput;
begin
  GetProcedureAddress(_BlockInput, user32, 'BlockInput');
  asm
    mov esp, ebp
    pop ebp
    jmp [_BlockInput]
  end;
end;
{$ELSE}
function BlockInput; external user32 name 'BlockInput';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _SendInput: Pointer;

function SendInput;
begin
  GetProcedureAddress(_SendInput, user32, 'SendInput');
  asm
    mov esp, ebp
    pop ebp
    jmp [_SendInput]
  end;
end;
{$ELSE}
function SendInput; external user32 name 'SendInput';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _NotifyWinEvent: Pointer;

procedure NotifyWinEvent;
begin
  GetProcedureAddress(_NotifyWinEvent, user32, 'NotifyWinEvent');
  asm
    mov esp, ebp
    pop ebp
    jmp [_NotifyWinEvent]
  end;
end;
{$ELSE}
procedure NotifyWinEvent; external user32 name 'NotifyWinEvent';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _SetWinEventHook: Pointer;

function SetWinEventHook;
begin
  GetProcedureAddress(_SetWinEventHook, user32, 'SetWinEventHook');
  asm
    mov esp, ebp
    pop ebp
    jmp [_SetWinEventHook]
  end;
end;
{$ELSE}
function SetWinEventHook; external user32 name 'SetWinEventHook';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _UnhookWinEvent: Pointer;

function UnhookWinEvent;
begin
  GetProcedureAddress(_UnhookWinEvent, user32, 'UnhookWinEvent');
  asm
    mov esp, ebp
    pop ebp
    jmp [_UnhookWinEvent]
  end;
end;
{$ELSE}
function UnhookWinEvent; external user32 name 'UnhookWinEvent';
{$ENDIF DYNAMIC_LINK}

end.
