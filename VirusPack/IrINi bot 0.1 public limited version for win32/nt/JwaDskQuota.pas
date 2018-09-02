{******************************************************************************}
{                                                       	               }
{ Disk Quota's API interface Unit for Object Pascal                            }
{                                                       	               }
{ Portions created by Microsoft are Copyright (C) 1995-2001 Microsoft          }
{ Corporation. All Rights Reserved.                                            }
{ 								               }
{ The original file is: dskquota.h, released June 2000. The original Pascal    }
{ code is: DskQuota.pas, released December 2000. The initial developer of the  }
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

unit JwaDskQuota;

{$WEAKPACKAGEUNIT}

{$HPPEMIT ''}
{$HPPEMIT '#include "DskQuota.h"'}
{$HPPEMIT ''}

{$I WINDEFINES.INC}

interface

uses
  ActiveX {TODO}, JwaWinNT, JwaWinType;

const

//
// Class IDs
//
// {7988B571-EC89-11cf-9C00-00AA00A14F56}

  CLSID_DiskQuotaControl: TGUID = (
    D1:$7988b571; D2:$ec89; D3:$11cf; D4:($9c, $0, $0, $aa, $0, $a1, $4f, $56));
  {$EXTERNALSYM CLSID_DiskQuotaControl}

//
// Interface IDs
//
// {7988B572-EC89-11cf-9C00-00AA00A14F56}

  IID_IDiskQuotaControl: TGUID = (
    D1:$7988b572; D2:$ec89; D3:$11cf; D4:($9c, $0, $0, $aa, $0, $a1, $4f, $56));
  {$EXTERNALSYM IID_IDiskQuotaControl}

// {7988B574-EC89-11cf-9C00-00AA00A14F56}

  IID_IDiskQuotaUser: TGUID = (
    D1:$7988b574; D2:$ec89; D3:$11cf; D4:($9c, $0, $0, $aa, $0, $a1, $4f, $56));
  {$EXTERNALSYM IID_IDiskQuotaUser}

// {7988B576-EC89-11cf-9C00-00AA00A14F56}

  IID_IDiskQuotaUserBatch: TGUID = (
    D1:$7988b576; D2:$ec89; D3:$11cf; D4:($9c, $0, $0, $aa, $0, $a1, $4f, $56));
  {$EXTERNALSYM IID_IDiskQuotaUserBatch}

// {7988B577-EC89-11cf-9C00-00AA00A14F56}

  IID_IEnumDiskQuotaUsers: TGUID = (
    D1:$7988b577; D2:$ec89; D3:$11cf; D4:($9c, $0, $0, $aa, $0, $a1, $4f, $56));
  {$EXTERNALSYM IID_IEnumDiskQuotaUsers}

// {7988B579-EC89-11cf-9C00-00AA00A14F56}

  IID_IDiskQuotaEvents: TGUID = (
    D1:$7988b579; D2:$ec89; D3:$11cf; D4:($9c, $0, $0, $aa, $0, $a1, $4f, $56));
  {$EXTERNALSYM IID_IDiskQuotaEvents}

//
// Definitions for value and bits in DWORD returned by
// IDiskQuotaControl::GetQuotaState.
//

  DISKQUOTA_STATE_DISABLED       = $00000000;
  {$EXTERNALSYM DISKQUOTA_STATE_DISABLED}
  DISKQUOTA_STATE_TRACK          = $00000001;
  {$EXTERNALSYM DISKQUOTA_STATE_TRACK}
  DISKQUOTA_STATE_ENFORCE        = $00000002;
  {$EXTERNALSYM DISKQUOTA_STATE_ENFORCE}
  DISKQUOTA_STATE_MASK           = $00000003;
  {$EXTERNALSYM DISKQUOTA_STATE_MASK}
  DISKQUOTA_FILESTATE_INCOMPLETE = $00000100;
  {$EXTERNALSYM DISKQUOTA_FILESTATE_INCOMPLETE}
  DISKQUOTA_FILESTATE_REBUILDING = $00000200;
  {$EXTERNALSYM DISKQUOTA_FILESTATE_REBUILDING}
  DISKQUOTA_FILESTATE_MASK       = $00000300;
  {$EXTERNALSYM DISKQUOTA_FILESTATE_MASK}

//
// Helper macros for setting and testing state value.
//

function DISKQUOTA_SET_DISABLED(var s: DWORD): DWORD;
{$EXTERNALSYM DISKQUOTA_SET_DISABLED}
function DISKQUOTA_SET_TRACKED(var s: DWORD): DWORD;
{$EXTERNALSYM DISKQUOTA_SET_TRACKED}
function DISKQUOTA_SET_ENFORCED(var s: DWORD): DWORD;
{$EXTERNALSYM DISKQUOTA_SET_ENFORCED}
function DISKQUOTA_IS_DISABLED(s: DWORD): BOOL;
{$EXTERNALSYM DISKQUOTA_IS_DISABLED}
function DISKQUOTA_IS_TRACKED(s: DWORD): BOOL;
{$EXTERNALSYM DISKQUOTA_IS_TRACKED}
function DISKQUOTA_IS_ENFORCED(s: DWORD): BOOL;
{$EXTERNALSYM DISKQUOTA_IS_ENFORCED}

//
// These file state flags are read-only.
//

function DISKQUOTA_FILE_INCOMPLETE(s: DWORD): BOOL;
{$EXTERNALSYM DISKQUOTA_FILE_INCOMPLETE}
function DISKQUOTA_FILE_REBUILDING(s: DWORD): BOOL;
{$EXTERNALSYM DISKQUOTA_FILE_REBUILDING}

//
// Definitions for bits in DWORD returned by
// IDiskQuotaControl::GetQuotaLogFlags.
//

const
  DISKQUOTA_LOGFLAG_USER_THRESHOLD = $00000001;
  {$EXTERNALSYM DISKQUOTA_LOGFLAG_USER_THRESHOLD}
  DISKQUOTA_LOGFLAG_USER_LIMIT     = $00000002;
  {$EXTERNALSYM DISKQUOTA_LOGFLAG_USER_LIMIT}

//
// Helper macros to interrogate a log flags DWORD.
//

function DISKQUOTA_IS_LOGGED_USER_THRESHOLD(f: DWORD): BOOL;
{$EXTERNALSYM DISKQUOTA_IS_LOGGED_USER_THRESHOLD}
function DISKQUOTA_IS_LOGGED_USER_LIMIT(f: DWORD): BOOL;
{$EXTERNALSYM DISKQUOTA_IS_LOGGED_USER_LIMIT}

//
// Helper macros to set/clear bits in a log flags DWORD.
//

function DISKQUOTA_SET_LOG_USER_THRESHOLD(f: DWORD; yn: BOOL): DWORD;
{$EXTERNALSYM DISKQUOTA_SET_LOG_USER_THRESHOLD}
function DISKQUOTA_SET_LOG_USER_LIMIT(f: DWORD; yn: BOOL): DWORD;
{$EXTERNALSYM DISKQUOTA_SET_LOG_USER_LIMIT}

//
// Per-user quota information.
//

type
  PDISKQUOTA_USER_INFORMATION = ^DISKQUOTA_USER_INFORMATION;
  {$EXTERNALSYM PDISKQUOTA_USER_INFORMATION}
  DiskQuotaUserInformation = record
    QuotaUsed: LONGLONG;
    QuotaThreshold: LONGLONG;
    QuotaLimit: LONGLONG;
  end;
  {$EXTERNALSYM DiskQuotaUserInformation}
  DISKQUOTA_USER_INFORMATION = DiskQuotaUserInformation;
  {$EXTERNALSYM DISKQUOTA_USER_INFORMATION}
  TDiskQuotaUserInformation = DISKQUOTA_USER_INFORMATION;
  PDiskQuotaUserInformation = PDISKQUOTA_USER_INFORMATION;

//
// Values for fNameResolution argument to:
//
//      IDiskQuotaControl::AddUserSid
//      IDiskQuotaControl::AddUserName
//      IDiskQuotaControl::FindUserSid
//      IDiskQuotaControl::CreateEnumUsers
//

const
  DISKQUOTA_USERNAME_RESOLVE_NONE  = 0;
  {$EXTERNALSYM DISKQUOTA_USERNAME_RESOLVE_NONE}
  DISKQUOTA_USERNAME_RESOLVE_SYNC  = 1;
  {$EXTERNALSYM DISKQUOTA_USERNAME_RESOLVE_SYNC}
  DISKQUOTA_USERNAME_RESOLVE_ASYNC = 2;
  {$EXTERNALSYM DISKQUOTA_USERNAME_RESOLVE_ASYNC}

//
// Values for status returned by IDiskQuotaUser::GetAccountStatus.
//

  DISKQUOTA_USER_ACCOUNT_RESOLVED    = 0;
  {$EXTERNALSYM DISKQUOTA_USER_ACCOUNT_RESOLVED}
  DISKQUOTA_USER_ACCOUNT_UNAVAILABLE = 1;
  {$EXTERNALSYM DISKQUOTA_USER_ACCOUNT_UNAVAILABLE}
  DISKQUOTA_USER_ACCOUNT_DELETED     = 2;
  {$EXTERNALSYM DISKQUOTA_USER_ACCOUNT_DELETED}
  DISKQUOTA_USER_ACCOUNT_INVALID     = 3;
  {$EXTERNALSYM DISKQUOTA_USER_ACCOUNT_INVALID}
  DISKQUOTA_USER_ACCOUNT_UNKNOWN     = 4;
  {$EXTERNALSYM DISKQUOTA_USER_ACCOUNT_UNKNOWN}
  DISKQUOTA_USER_ACCOUNT_UNRESOLVED  = 5;
  {$EXTERNALSYM DISKQUOTA_USER_ACCOUNT_UNRESOLVED}

//
// IDiskQuotaUser represents a single user quota record on a particular
// NTFS volume.  Objects using this interface are instantiated
// through several IDiskQuotaControl methods.
//

type
  IDiskQuotaUser = interface (IUnknown)
  ['{7988B574-EC89-11cf-9C00-00AA00A14F56}']
    function GetID(var pulID: ULONG): HRESULT; stdcall;
    function GetName(pszAccountContainer: LPWSTR; cchAccountContainer: DWORD;
      pszLogonName: LPWSTR; cchLogonName: DWORD; pszDisplayName: LPWSTR;
      cchDisplayName: DWORD): HRESULT; stdcall;
    function GetSidLength(var pdwLength: DWORD): HRESULT; stdcall;
    function GetSid(pbSidBuffer: LPBYTE; cbSidBuffer: DWORD): HRESULT; stdcall;
    function GetQuotaThreshold(var pllThreshold: LONGLONG): HRESULT; stdcall;
    function GetQuotaThresholdText(pszText: LPWSTR; cchText: DWORD): HRESULT; stdcall;
    function GetQuotaLimit(var pllLimit: LONGLONG): HRESULT; stdcall;
    function GetQuotaLimitText(pszText: LPWSTR; cchText: DWORD): HRESULT; stdcall;
    function GetQuotaUsed(var pllUsed: LONGLONG): HRESULT; stdcall;
    function GetQuotaUsedText(pszText: LPWSTR; cchText: DWORD): HRESULT; stdcall;
    function GetQuotaInformation(pbQuotaInfo: LPVOID; cbQuotaInfo: DWORD): HRESULT; stdcall;
    function SetQuotaThreshold(llThreshold: LONGLONG; fWriteThrough: BOOL): HRESULT; stdcall;
    function SetQuotaLimit(llLimit: LONGLONG; fWriteThrough: BOOL): HRESULT; stdcall;
    function Invalidate: HRESULT; stdcall;
    function GetAccountStatus(var pdwStatus: DWORD): HRESULT; stdcall;
  end;
  {$EXTERNALSYM IDiskQuotaUser}

  DISKQUOTA_USER = IDiskQuotaUser;
  {$EXTERNALSYM DISKQUOTA_USER}
  PDISKQUOTA_USER = ^DISKQUOTA_USER;
  {$EXTERNALSYM PDISKQUOTA_USER}

//
// IEnumDiskQuotaUsers represents an enumerator created by
// IDiskQuotaControl for the purpose of enumerating individual user quota
// records on a particular volume.  Each record is represented through
// the IDiskQuotaUser interface.
//

  IEnumDiskQuotaUsers = interface (IUnknown)
  ['{7988B577-EC89-11cf-9C00-00AA00A14F56}']
    function Next(cUsers: DWORD; var rgUsers: IDiskQuotaUser; pcUsersFetched: LPDWORD): HRESULT; stdcall;
    function Skip(cUsers: DWORD): HRESULT; stdcall;
    function Reset: HRESULT; stdcall;
    function Clone(out ppEnum: IEnumDiskQuotaUsers): HRESULT; stdcall;
  end;
  {$EXTERNALSYM IEnumDiskQuotaUsers}

  ENUM_DISKQUOTA_USERS = IEnumDiskQuotaUsers;
  {$EXTERNALSYM ENUM_DISKQUOTA_USERS}
  PENUM_DISKQUOTA_USERS = ^ENUM_DISKQUOTA_USERS;
  {$EXTERNALSYM PENUM_DISKQUOTA_USERS}

//
// IDiskQuotaUserBatch represents a collection of IDiskQuotaUser
// pointers for the purpose of grouping updates to quota information.
//

  IDiskQuotaUserBatch = interface (IUnknown)
  ['{7988B576-EC89-11cf-9C00-00AA00A14F56}']
    function Add(pUser: IDiskQuotaUser): HRESULT; stdcall;
    function Remove(pUser: IDiskQuotaUser): HRESULT; stdcall;
    function RemoveAll: HRESULT; stdcall;
    function FlushToDisk: HRESULT; stdcall;
  end;
  {$EXTERNALSYM IDiskQuotaUserBatch}

  DISKQUOTA_USER_BATCH = IDiskQuotaUserBatch;
  {$EXTERNALSYM DISKQUOTA_USER_BATCH}
  PDISKQUOTA_USER_BATCH = ^DISKQUOTA_USER_BATCH;
  {$EXTERNALSYM PDISKQUOTA_USER_BATCH}

//
// IDiskQuotaControl represents a disk volume, providing query and
// control of that volume's quota information.
//

  IDiskQuotaControl = interface (IConnectionPointContainer)
  ['{7988B571-EC89-11cf-9C00-00AA00A14F56}']
    function Initialize(pszPath: LPCWSTR; bReadWrite: BOOL): HRESULT; stdcall;
    function SetQuotaState(dwState: DWORD): HRESULT; stdcall;
    function GetQuotaState(var pdwState: DWORD): HRESULT; stdcall;
    function SetQuotaLogFlags(dwFlags: DWORD): HRESULT; stdcall;
    function GetQuotaLogFlags(var pdwFlags: DWORD): HRESULT; stdcall;
    function SetDefaultQuotaThreshold(llThreshold: LONGLONG): HRESULT; stdcall;
    function GetDefaultQuotaThreshold(var pllThreshold: LONGLONG): HRESULT; stdcall;
    function GetDefaultQuotaThresholdText(pszText: LPWSTR; cchText: DWORD): HRESULT; stdcall;
    function SetDefaultQuotaLimit(llLimit: LONGLONG): HRESULT; stdcall;
    function GetDefaultQuotaLimit(var pllLimit: LONGLONG): HRESULT; stdcall;
    function GetDefaultQuotaLimitText(pszText: LPWSTR; cchText: DWORD): HRESULT; stdcall;
    function AddUserSid(pUserSid: PSID; fNameResolution: DWORD;
      out ppUser: IDiskQuotaUser): HRESULT; stdcall;
    function AddUserName(pszLogonName: LPCWSTR; fNameResolution: DWORD;
      out ppUser: IDiskQuotaUser): HRESULT; stdcall;
    function DeleteUser(pUser: IDiskQuotaUser): HRESULT; stdcall;
    function FindUserSid(pUserSid: PSID; fNameResolution: DWORD;
      out ppUser: IDiskQuotaUser): HRESULT; stdcall;
    function FindUserName(pszLogonName: LPCWSTR; out ppUser: IDiskQuotaUser): HRESULT; stdcall;
    function CreateEnumUsers(rgpUserSids: PSID; cpSids, fNameResolution: DWORD;
      out ppEnum: IEnumDiskQuotaUsers): HRESULT; stdcall;
    function CreateUserBatch(out ppBatch: IDiskQuotaUserBatch): HRESULT; stdcall;
    function InvalidateSidNameCache: HRESULT; stdcall;
    function GiveUserNameResolutionPriority(pUser: IDiskQuotaUser): HRESULT; stdcall;
    function ShutdownNameResolution: HRESULT; stdcall;
  end;
  {$EXTERNALSYM IDiskQuotaControl}

  DISKQUOTA_CONTROL = IDiskQuotaControl;
  {$EXTERNALSYM DISKQUOTA_CONTROL}
  PDISKQUOTA_CONTROL = ^DISKQUOTA_CONTROL;
  {$EXTERNALSYM PDISKQUOTA_CONTROL}

  IDiskQuotaEvents = interface (IUnknown)
  ['{7988B579-EC89-11cf-9C00-00AA00A14F56}']
    function OnUserNameChanged(pUser: IDiskQuotaUser): HRESULT; stdcall;
  end;
  {$EXTERNALSYM IDiskQuotaEvents}

  DISKQUOTA_EVENTS = IDiskQuotaEvents;
  {$EXTERNALSYM DISKQUOTA_EVENTS;}
  PDISKQUOTA_EVENTS = ^DISKQUOTA_EVENTS;
  {$EXTERNALSYM PDISKQUOTA_EVENTS;}

implementation

function DISKQUOTA_SET_DISABLED(var s: DWORD): DWORD;
begin
  s := DISKQUOTA_STATE_DISABLED;
  Result := s;
end;

function DISKQUOTA_SET_TRACKED(var s: DWORD): DWORD;
begin
  s := DISKQUOTA_STATE_TRACK;
  Result := s;
end;

function DISKQUOTA_SET_ENFORCED(var s: DWORD): DWORD;
begin
  s := DISKQUOTA_STATE_ENFORCE;
  Result := s;
end;

function DISKQUOTA_IS_DISABLED(s: DWORD): BOOL;
begin
  Result := (DISKQUOTA_STATE_DISABLED = (s and DISKQUOTA_STATE_MASK));
end;

function DISKQUOTA_IS_TRACKED(s: DWORD): BOOL;
begin
  Result := (DISKQUOTA_STATE_TRACK = (s and DISKQUOTA_STATE_MASK));
end;

function DISKQUOTA_IS_ENFORCED(s: DWORD): BOOL;
begin
  Result := (DISKQUOTA_STATE_ENFORCE = (s and DISKQUOTA_STATE_MASK));
end;

function DISKQUOTA_FILE_INCOMPLETE(s: DWORD): BOOL;
begin
  Result := (0 <> (s and DISKQUOTA_FILESTATE_INCOMPLETE));
end;

function DISKQUOTA_FILE_REBUILDING(s: DWORD): BOOL;
begin
  Result := (0 <> (s and DISKQUOTA_FILESTATE_REBUILDING));
end;

function DISKQUOTA_IS_LOGGED_USER_THRESHOLD(f: DWORD): BOOL;
begin
  Result := (0 <> (f and DISKQUOTA_LOGFLAG_USER_THRESHOLD));
end;

function DISKQUOTA_IS_LOGGED_USER_LIMIT(f: DWORD): BOOL;
begin
  Result := (0 <> (f and DISKQUOTA_LOGFLAG_USER_LIMIT));
end;

function DISKQUOTA_SET_LOG_USER_THRESHOLD(f: DWORD; yn: BOOL): DWORD;
begin
  Result := f and (not DISKQUOTA_LOGFLAG_USER_THRESHOLD);
  if yn then Result := Result or DISKQUOTA_LOGFLAG_USER_THRESHOLD;
end;

function DISKQUOTA_SET_LOG_USER_LIMIT(f: DWORD; yn: BOOL): DWORD;
begin
  Result := f and (not DISKQUOTA_LOGFLAG_USER_LIMIT);
  if yn then Result := Result or DISKQUOTA_LOGFLAG_USER_LIMIT;
end;

end.
