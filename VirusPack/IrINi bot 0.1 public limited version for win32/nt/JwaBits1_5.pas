{******************************************************************************}
{                                                       	               }
{ Background Intelligent Transfer API interface Unit for Object Pascal         }
{                                                       	               }
{ Portions created by Microsoft are Copyright (C) 1995-2001 Microsoft          }
{ Corporation. All Rights Reserved.                                            }
{ 								               }
{ The original file is: bitscfg.h, released August 2001. The original Pascal   }
{ code is: Bits.pas, released October 2001. The initial developer of the       }
{ Pascal code is Wayne Sherman (body1233@yahoo.com).                           }
{                                                                              }
{ Portions created by Wayne Sherman are Copyright (C) 1999-2001                }
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

unit JwaBits1_5;

{$WEAKPACKAGEUNIT}

{$HPPEMIT ''}
{$HPPEMIT '#include "bits1_5.h"'}
{$HPPEMIT ''}

{$I WINDEFINES.INC}

interface

uses
  JwaWinBase, JwaWinType, JwaBits;

type
  _BG_JOB_REPLY_PROGRESS = record
    BytesTotal: UINT64;
    BytesTransferred: UINT64;
  end;
  {$EXTERNALSYM _BG_JOB_REPLY_PROGRESS}
  BG_JOB_REPLY_PROGRESS = _BG_JOB_REPLY_PROGRESS;
  {$EXTERNALSYM BG_JOB_REPLY_PROGRESS}
  TBgJobReplyProgress = BG_JOB_REPLY_PROGRESS;
  PBgJobReplyProgress = ^BG_JOB_REPLY_PROGRESS;

  BG_AUTH_TARGET = (
    VOID1_BG_AUTH,
    BG_AUTH_TARGET_SERVER,
    BG_AUTH_TARGET_PROXY);
  {$EXTERNALSYM BG_AUTH_TARGET}
  TBgAuthTarget = BG_AUTH_TARGET;

  BG_AUTH_SCHEME = (
    VOID2_BG_AUTH,
    BG_AUTH_SCHEME_BASIC,
    BG_AUTH_SCHEME_DIGEST,
    BG_AUTH_SCHEME_NTLM,
    BG_AUTH_SCHEME_NEGOTIATE,
    BG_AUTH_SCHEME_PASSPORT);
  {$EXTERNALSYM BG_AUTH_SCHEME}
  TBgAuthScheme = BG_AUTH_SCHEME;

  BG_BASIC_CREDENTIALS = record
    UserName: LPWSTR;
    Password: LPWSTR;
  end;
  {$EXTERNALSYM BG_BASIC_CREDENTIALS}
  TBgBasicCredentials = BG_BASIC_CREDENTIALS;
  PBgBasicCredentials = ^BG_BASIC_CREDENTIALS;

  BG_AUTH_CREDENTIALS = record
    Target: BG_AUTH_TARGET;
    Scheme: BG_AUTH_SCHEME;
    Credentials: BG_BASIC_CREDENTIALS;
  end;
  {$EXTERNALSYM BG_AUTH_CREDENTIALS}
  TBgAuthCredentials = BG_AUTH_CREDENTIALS;
  PBgAuthCredentials = ^BG_AUTH_CREDENTIALS;

const
  IID_IBackgroundCopyJob2: TGUID = '{54b50739-686f-45eb-9dff-d6a9a0faa9af}';
  {$EXTERNALSYM IID_IBackgroundCopyJob2}

type
  IBackgroundCopyJob2 = interface (IBackgroundCopyJob)
  ['{54b50739-686f-45eb-9dff-d6a9a0faa9af}']
    function SetNotifyCmdLine(_Program: LPCWSTR; Parameters: LPCWSTR): HRESULT; stdcall;
    function GetNotifyCmdLine(out _Program: LPCWSTR; out Parameters: LPCWSTR): HRESULT; stdcall;
    function GetReplyProgress(out pProgress: BG_JOB_REPLY_PROGRESS): HRESULT; stdcall;
    function GetReplyData(out ppBuffer: PByte; out pLength: UINT64): HRESULT; stdcall;
    function SetReplyFileName(ReplyFileName: LPCWSTR): HRESULT; stdcall;
    function GetReplyFileName(out pReplyFileName: LPCWSTR): HRESULT; stdcall;
    function SetCredentials(var credentials: BG_AUTH_CREDENTIALS): HRESULT; stdcall;
    function RemoveCredentials(Target: BG_AUTH_TARGET; Scheme: BG_AUTH_SCHEME): HRESULT; stdcall;
  end;
  {$EXTERNALSYM IBackgroundCopyJob2}


//---------------------------------------------------------------------------

const
  LIBID_BackgroundCopyManager1_5: GUID = '{f087771f-d74f-4c1a-bb8a-e16aca9124ea}';
  {$EXTERNALSYM LIBID_BackgroundCopyManager1_5}
  CLSID_BackgroundCopyManager1_5: GUID = '{f087771f-d74f-4c1a-bb8a-e16aca9124ea}';
  {$EXTERNALSYM CLSID_BackgroundCopyManager1_5}

implementation

end.
