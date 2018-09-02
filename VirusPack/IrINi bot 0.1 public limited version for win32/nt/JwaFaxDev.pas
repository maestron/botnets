{******************************************************************************}
{                                                       	               }
{ Fax Device Provider API interface unit for Object Pascal                     }
{                                                       	               }
{ Portions created by Microsoft are Copyright (C) 1995-2001 Microsoft          }
{ Corporation. All Rights Reserved.                                            }
{ 								               }
{ The original file is: faxdev.h, released November 2001. The original Pascal  }
{ code is: FaxDev.pas, released April 2002. The initial developer of the       }
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

unit JwaFaxDev;

{$WEAKPACKAGEUNIT}

{$HPPEMIT ''}
{$HPPEMIT '#include "faxdev.h"'}
{$HPPEMIT ''}

{$I WINDEFINES.INC}

interface

uses
  JwaWinType, JwaPrSht;

//
// FAX status constants
//

const
  FS_INITIALIZING     = $20000000;
  {$EXTERNALSYM FS_INITIALIZING}
  FS_DIALING          = $20000001;
  {$EXTERNALSYM FS_DIALING}
  FS_TRANSMITTING     = $20000002;
  {$EXTERNALSYM FS_TRANSMITTING}
  FS_RECEIVING        = $20000004;
  {$EXTERNALSYM FS_RECEIVING}
  FS_COMPLETED        = $20000008;
  {$EXTERNALSYM FS_COMPLETED}
  FS_HANDLED          = $20000010;
  {$EXTERNALSYM FS_HANDLED}
  FS_LINE_UNAVAILABLE = $20000020;
  {$EXTERNALSYM FS_LINE_UNAVAILABLE}
  FS_BUSY             = $20000040;
  {$EXTERNALSYM FS_BUSY}
  FS_NO_ANSWER        = $20000080;
  {$EXTERNALSYM FS_NO_ANSWER}
  FS_BAD_ADDRESS      = $20000100;
  {$EXTERNALSYM FS_BAD_ADDRESS}
  FS_NO_DIAL_TONE     = $20000200;
  {$EXTERNALSYM FS_NO_DIAL_TONE}
  FS_DISCONNECTED     = $20000400;
  {$EXTERNALSYM FS_DISCONNECTED}
  FS_FATAL_ERROR      = $20000800; 
  {$EXTERNALSYM FS_FATAL_ERROR}
  FS_NOT_FAX_CALL     = $20001000;
  {$EXTERNALSYM FS_NOT_FAX_CALL}
  FS_CALL_DELAYED     = $20002000;
  {$EXTERNALSYM FS_CALL_DELAYED}
  FS_CALL_BLACKLISTED = $20004000;
  {$EXTERNALSYM FS_CALL_BLACKLISTED}
  FS_USER_ABORT       = $20200000;
  {$EXTERNALSYM FS_USER_ABORT}
  FS_ANSWERED         = $20800000;
  {$EXTERNALSYM FS_ANSWERED}

//
// data structures
//

type
  HCALL = HANDLE; // todo from TAPI

  PFAX_SEND = ^FAX_SEND;
  {$EXTERNALSYM PFAX_SEND}
  _FAX_SEND = record
    SizeOfStruct: DWORD;
    FileName: LPWSTR;
    CallerName: LPWSTR;
    CallerNumber: LPWSTR;
    ReceiverName: LPWSTR;
    ReceiverNumber: LPWSTR;
    Branding: BOOL;
    CallHandle: HCALL;
    Reserved: array [0..2] of DWORD;
  end;
  {$EXTERNALSYM _FAX_SEND}
  FAX_SEND = _FAX_SEND;
  {$EXTERNALSYM FAX_SEND}
  TFaxSend = FAX_SEND;
  PFaxSend = PFAX_SEND;

  PFAX_RECEIVE = ^FAX_RECEIVE;
  {$EXTERNALSYM PFAX_RECEIVE}
  _FAX_RECEIVE = record
    SizeOfStruct: DWORD;
    FileName: LPWSTR;
    ReceiverName: LPWSTR;
    ReceiverNumber: LPWSTR;
    Reserved: array [0..3] of DWORD;
  end;
  {$EXTERNALSYM _FAX_RECEIVE}
  FAX_RECEIVE = _FAX_RECEIVE;
  {$EXTERNALSYM FAX_RECEIVE}
  TFaxReceive = FAX_RECEIVE;
  PFaxReceive = PFAX_RECEIVE;

  PFAX_DEV_STATUS = ^FAX_DEV_STATUS;
  {$EXTERNALSYM PFAX_DEV_STATUS}
  _FAX_DEV_STATUS = record
    SizeOfStruct: DWORD;
    StatusId: DWORD;
    StringId: DWORD;
    PageCount: DWORD;
    CSI: LPWSTR;
    CallerId: LPWSTR;
    RoutingInfo: LPWSTR;
    ErrorCode: DWORD;
    Reserved: array [0..2] of DWORD;
  end;
  {$EXTERNALSYM _FAX_DEV_STATUS}
  FAX_DEV_STATUS = _FAX_DEV_STATUS;
  {$EXTERNALSYM FAX_DEV_STATUS}
  TFaxDevStatus = FAX_DEV_STATUS;
  PFaxDevStatus = PFAX_DEV_STATUS;

  PFAX_SERVICE_CALLBACK = function (FaxHandle: HANDLE; DeviceId: DWORD; Param1, Param2, Param3: DWORD_PTR): BOOL; stdcall;
  {$EXTERNALSYM PFAX_SERVICE_CALLBACK}

  PFAX_LINECALLBACK = procedure (FaxHandle: HANDLE; hDevice, dwMessage: DWORD; dwInstance, wParam1, dwParam2, dwParam3: DWORD_PTR); stdcall;
  {$EXTERNALSYM PFAX_LINECALLBACK}

type
  PFAX_SEND_CALLBACK = function (FaxHandle: HANDLE; CallHandle: HCALL; Reserved1, Reserved2: DWORD): BOOL; stdcall;
  {$EXTERNALSYM PFAX_SEND_CALLBACK}

const
  FAXDEVRECEIVE_SIZE = 4096;
  {$EXTERNALSYM FAXDEVRECEIVE_SIZE}

const
  FAXDEVREPORTSTATUS_SIZE = 4096;
  {$EXTERNALSYM FAXDEVREPORTSTATUS_SIZE}

type
  HLINEAPP = HANDLE; // todo from TAPI
  HLINE = HANDLE; // todo form TAPI

  PFAXDEVINITIALIZE = function (LineAppHandle: HLINEAPP; HeapHandle: HANDLE; out LineCallbackFunction: PFAX_LINECALLBACK; FaxServiceCallback: PFAX_SERVICE_CALLBACK): BOOL; stdcall;
  {$EXTERNALSYM PFAXDEVINITIALIZE}
  PFAXDEVSHUTDOWN = function : HRESULT; stdcall;
  {$EXTERNALSYM PFAXDEVSHUTDOWN}
  PFAXDEVVIRTUALDEVICECREATION = function (DeviceCount: LPDWORD; DeviceNamePrefix: LPWSTR; DeviceIdPrefix: LPDWORD; CompletionPort: HANDLE; CompletionKey: ULONG_PTR): BOOL; stdcall;
  {$EXTERNALSYM PFAXDEVVIRTUALDEVICECREATION}
  PFAXDEVSTARTJOB = function (LineHandle: HLINE; DeviceId: DWORD; FaxHandle: PHANDLE; CompletionPortHandle: HANDLE; CompletionKey: ULONG_PTR): BOOL; stdcall;
  {$EXTERNALSYM PFAXDEVSTARTJOB}
  PFAXDEVENDJOB = function (FaxHandle: HANDLE): BOOL; stdcall;
  {$EXTERNALSYM PFAXDEVENDJOB}
  PFAXDEVSEND = function (FaxHandle: HANDLE; FaxSend: PFAX_SEND; FaxSendCallback: PFAX_SEND_CALLBACK): BOOL; stdcall;
  {$EXTERNALSYM PFAXDEVSEND}
  PFAXDEVRECEIVE = function (FaxHandle: HANDLE; CallHandle: HCALL; FaxReceive: PFAX_RECEIVE): BOOL; stdcall;
  {$EXTERNALSYM PFAXDEVRECEIVE}
  PFAXDEVREPORTSTATUS = function (FaxHandle: HANDLE; FaxStatus: PFAX_DEV_STATUS; FaxStatusSize: DWORD; FaxStatusSizeRequired: LPDWORD): BOOL; stdcall;
  {$EXTERNALSYM PFAXDEVREPORTSTATUS}
  PFAXDEVABORTOPERATION = function (FaxHandle: HANDLE): BOOL; stdcall;
  {$EXTERNALSYM PFAXDEVABORTOPERATION}
  PFAXDEVCONFIGURE = function (out PropSheetPage: HPROPSHEETPAGE): BOOL; stdcall;
  {$EXTERNALSYM PFAXDEVCONFIGURE}

implementation

end.
