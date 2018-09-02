{******************************************************************************}
{                                                       	               }
{ Lan Manager DFS API interface Unit for Object Pascal                         }
{                                                       	               }
{ Portions created by Microsoft are Copyright (C) 1995-2001 Microsoft          }
{ Corporation. All Rights Reserved.                                            }
{ 								               }
{ The original file is: lmdfs.h, released November 2001. The original Pascal   }
{ code is: LmDfs.pas, released Februari 2002. The initial developer of the     }
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

unit JwaLmDFS;

{$WEAKPACKAGEUNIT}

{$HPPEMIT ''}
{$HPPEMIT '#include "lmdfs.h"'}
{$HPPEMIT ''}

{$I WINDEFINES.INC}

interface

uses
  JwaLmCons, JwaWinType;

//
// DFS Volume state
//

const
  DFS_VOLUME_STATES             = $F;
  {$EXTERNALSYM DFS_VOLUME_STATES}

  DFS_VOLUME_STATE_OK           = 1;
  {$EXTERNALSYM DFS_VOLUME_STATE_OK}
  DFS_VOLUME_STATE_INCONSISTENT = 2;
  {$EXTERNALSYM DFS_VOLUME_STATE_INCONSISTENT}
  DFS_VOLUME_STATE_OFFLINE      = 3;
  {$EXTERNALSYM DFS_VOLUME_STATE_OFFLINE}
  DFS_VOLUME_STATE_ONLINE       = 4;
  {$EXTERNALSYM DFS_VOLUME_STATE_ONLINE}

//
// These are valid for setting the volume state on the root
// These are available to force a resynchronize on the root
// volume or to put it in a standby mode.
//

  DFS_VOLUME_STATE_RESYNCHRONIZE = $10;
  {$EXTERNALSYM DFS_VOLUME_STATE_RESYNCHRONIZE}
  DFS_VOLUME_STATE_STANDBY       = $20;
  {$EXTERNALSYM DFS_VOLUME_STATE_STANDBY}

//
// These are valid on getting the volume state on the root
// These are available to determine the flavor of DFS
// A few bits are reserved to determine the flavor of the DFS root.
// To get the flavor, and the state with DFS_VOLUME_FLAVORS.
//
// (_state & DFS_VOLUME_FLAVORS) will tell you the flavor of the dfs root.
//
//

  DFS_VOLUME_FLAVORS = $0300;
  {$EXTERNALSYM DFS_VOLUME_FLAVORS}

  DFS_VOLUME_FLAVOR_UNUSED1    = $0000;
  {$EXTERNALSYM DFS_VOLUME_FLAVOR_UNUSED1}
  DFS_VOLUME_FLAVOR_STANDALONE = $0100;
  {$EXTERNALSYM DFS_VOLUME_FLAVOR_STANDALONE}
  DFS_VOLUME_FLAVOR_AD_BLOB    = $0200;
  {$EXTERNALSYM DFS_VOLUME_FLAVOR_AD_BLOB}
  DFS_STORAGE_FLAVOR_UNUSED2   = $0300;
  {$EXTERNALSYM DFS_STORAGE_FLAVOR_UNUSED2}

//
// DFS Storage State
//

  DFS_STORAGE_STATES        = $F;
  {$EXTERNALSYM DFS_STORAGE_STATES}
  DFS_STORAGE_STATE_OFFLINE = 1;
  {$EXTERNALSYM DFS_STORAGE_STATE_OFFLINE}
  DFS_STORAGE_STATE_ONLINE  = 2;
  {$EXTERNALSYM DFS_STORAGE_STATE_ONLINE}
  DFS_STORAGE_STATE_ACTIVE  = 4;
  {$EXTERNALSYM DFS_STORAGE_STATE_ACTIVE}

//
// Level 1:
//

type
  LPDFS_INFO_1 = ^DFS_INFO_1;
  {$EXTERNALSYM LPDFS_INFO_1}
  PDFS_INFO_1 = ^DFS_INFO_1;
  {$EXTERNALSYM PDFS_INFO_1}
  _DFS_INFO_1 = record
    EntryPath: LPWSTR; // Dfs name for the top of this piece of storage
  end;
  {$EXTERNALSYM _DFS_INFO_1}
  DFS_INFO_1 = _DFS_INFO_1;
  {$EXTERNALSYM DFS_INFO_1}
  TDfsInfo1 = DFS_INFO_1;
  PDfsInfo1 = PDFS_INFO_1;

//
// Level 2:
//

  LPDFS_INFO_2 = ^DFS_INFO_2;
  {$EXTERNALSYM LPDFS_INFO_2}
  PDFS_INFO_2 = ^DFS_INFO_2;
  {$EXTERNALSYM PDFS_INFO_2}
  _DFS_INFO_2 = record
    EntryPath: LPWSTR; // Dfs name for the top of this volume
    Comment: LPWSTR; // Comment for this volume
    State: DWORD; // State of this volume, one of DFS_VOLUME_STATE_*
    NumberOfStorages: DWORD; // Number of storages for this volume
  end;
  {$EXTERNALSYM _DFS_INFO_2}
  DFS_INFO_2 = _DFS_INFO_2;
  {$EXTERNALSYM DFS_INFO_2}
  TDfsInfo2 = DFS_INFO_2;
  PDfsInfo2 = PDFS_INFO_2;

  LPDFS_STORAGE_INFO = ^DFS_STORAGE_INFO;
  {$EXTERNALSYM LPDFS_STORAGE_INFO}
  PDFS_STORAGE_INFO = ^DFS_STORAGE_INFO;
  {$EXTERNALSYM PDFS_STORAGE_INFO}
  _DFS_STORAGE_INFO = record
    State: ULONG; // State of this storage, one of DFS_STORAGE_STATE_*
    // possibly OR'd with DFS_STORAGE_STATE_ACTIVE
    ServerName: LPWSTR; // Name of server hosting this storage
    ShareName: LPWSTR; // Name of share hosting this storage
  end;
  {$EXTERNALSYM _DFS_STORAGE_INFO}
  DFS_STORAGE_INFO = _DFS_STORAGE_INFO;
  {$EXTERNALSYM DFS_STORAGE_INFO}
  TDfsStorageInfo = DFS_STORAGE_INFO;
  PDfsStorageInfo = PDFS_STORAGE_INFO;

//
// Level 3:
//

  LPDFS_INFO_3 = ^DFS_INFO_3;
  {$EXTERNALSYM LPDFS_INFO_3}
  PDFS_INFO_3 = ^DFS_INFO_3;
  {$EXTERNALSYM PDFS_INFO_3}
  _DFS_INFO_3 = record
    EntryPath: LPWSTR; // Dfs name for the top of this volume
    Comment: LPWSTR; // Comment for this volume
    State: DWORD; // State of this volume, one of DFS_VOLUME_STATE_*
    NumberOfStorages: DWORD; // Number of storage servers for this volume
    Storage: LPDFS_STORAGE_INFO; // An array (of NumberOfStorages elements) of storage-specific information.
  end;
  {$EXTERNALSYM _DFS_INFO_3}
  DFS_INFO_3 = _DFS_INFO_3;
  {$EXTERNALSYM DFS_INFO_3}
  TDfsInfo3 = DFS_INFO_3;
  PDfsInfo3 = PDFS_INFO_3;

//
// Level 4:
//

  LPDFS_INFO_4 = ^DFS_INFO_4;
  {$EXTERNALSYM LPDFS_INFO_4}
  PDFS_INFO_4 = ^DFS_INFO_4;
  {$EXTERNALSYM PDFS_INFO_4}
  _DFS_INFO_4 = record
    EntryPath: LPWSTR; // Dfs name for the top of this volume
    Comment: LPWSTR; // Comment for this volume
    State: DWORD; // State of this volume, one of DFS_VOLUME_STATE_*
    Timeout: ULONG; // Timeout, in seconds, of this junction point
    Guid: GUID; // Guid of this junction point
    NumberOfStorages: DWORD; // Number of storage servers for this volume
    Storage: LPDFS_STORAGE_INFO; // An array (of NumberOfStorages elements) of storage-specific information.
  end;
  {$EXTERNALSYM _DFS_INFO_4}
  DFS_INFO_4 = _DFS_INFO_4;
  {$EXTERNALSYM DFS_INFO_4}
  TDfsInfo4 = DFS_INFO_4;
  PDfsInfo4 = PDFS_INFO_4;

//
// Level 100:
//

  LPDFS_INFO_100 = ^DFS_INFO_100;
  {$EXTERNALSYM LPDFS_INFO_100}
  PDFS_INFO_100 = ^DFS_INFO_100;
  {$EXTERNALSYM PDFS_INFO_100}
  _DFS_INFO_100 = record
    Comment: LPWSTR; // Comment for this volume or storage
  end;
  {$EXTERNALSYM _DFS_INFO_100}
  DFS_INFO_100 = _DFS_INFO_100;
  {$EXTERNALSYM DFS_INFO_100}
  TDfsInfo100 = DFS_INFO_100;
  PDfsInfo100 = PDFS_INFO_100;

//
// Level 101:
//

  LPDFS_INFO_101 = ^DFS_INFO_101;
  {$EXTERNALSYM LPDFS_INFO_101}
  PDFS_INFO_101 = ^DFS_INFO_101;
  {$EXTERNALSYM PDFS_INFO_101}
  _DFS_INFO_101 = record
    State: DWORD; // State of this storage, one of DFS_STORAGE_STATE_*
    // possibly OR'd with DFS_STORAGE_STATE_ACTIVE
  end;
  {$EXTERNALSYM _DFS_INFO_101}
  DFS_INFO_101 = _DFS_INFO_101;
  {$EXTERNALSYM DFS_INFO_101}
  TDfsInfo101 = DFS_INFO_101;
  PDfsInfo101 = PDFS_INFO_101;

//
// Level 102:
//

  LPDFS_INFO_102 = ^DFS_INFO_102;
  {$EXTERNALSYM LPDFS_INFO_102}
  PDFS_INFO_102 = ^DFS_INFO_102;
  {$EXTERNALSYM PDFS_INFO_102}
  _DFS_INFO_102 = record
    Timeout: ULONG; // Timeout, in seconds, of the junction
  end;
  {$EXTERNALSYM _DFS_INFO_102}
  DFS_INFO_102 = _DFS_INFO_102;
  {$EXTERNALSYM DFS_INFO_102}
  TDfsInfo102 = DFS_INFO_102;
  PDfsInfo102 = PDFS_INFO_102;

//
// Level 200:
//

  LPDFS_INFO_200 = ^DFS_INFO_200;
  {$EXTERNALSYM LPDFS_INFO_200}
  PDFS_INFO_200 = ^DFS_INFO_200;
  {$EXTERNALSYM PDFS_INFO_200}
  _DFS_INFO_200 = record
    FtDfsName: LPWSTR; // FtDfs name
  end;
  {$EXTERNALSYM _DFS_INFO_200}
  DFS_INFO_200 = _DFS_INFO_200;
  {$EXTERNALSYM DFS_INFO_200}
  TDfsInfo200 = DFS_INFO_200;
  PDfsInfo200 = PDFS_INFO_200;

//
// Level 300:
//

  LPDFS_INFO_300 = ^DFS_INFO_300;
  {$EXTERNALSYM LPDFS_INFO_300}
  PDFS_INFO_300 = ^DFS_INFO_300;
  {$EXTERNALSYM PDFS_INFO_300}
  _DFS_INFO_300 = record
    Flags: DWORD;
    DfsName: LPWSTR; // Dfs name
  end;
  {$EXTERNALSYM _DFS_INFO_300}
  DFS_INFO_300 = _DFS_INFO_300;
  {$EXTERNALSYM DFS_INFO_300}
  TDfsInfo300 = DFS_INFO_300;
  PDfsInfo300 = PDFS_INFO_300;

//
// Add a new volume or additional storage for an existing volume at
// DfsEntryPath.
//

function NetDfsAdd(DfsEntryPath, ServerName, ShareName, Comment: LPWSTR; Flags: DWORD): NET_API_STATUS; stdcall;
{$EXTERNALSYM NetDfsAdd}

//
// Flags:
//

const
  DFS_ADD_VOLUME     = 1; // Add a new volume to the DFS if not already there
  {$EXTERNALSYM DFS_ADD_VOLUME}
  DFS_RESTORE_VOLUME = 2; // Volume/Replica is being restored - do not verify share etc.
  {$EXTERNALSYM DFS_RESTORE_VOLUME}

//
// Setup/teardown API's for standard and FtDfs roots.
//

function NetDfsAddStdRoot(ServerName, RootShare, Comment: LPWSTR; Flags: DWORD): NET_API_STATUS; stdcall;
{$EXTERNALSYM NetDfsAddStdRoot}

function NetDfsRemoveStdRoot(ServerName, RootShare: LPWSTR; Flags: DWORD): NET_API_STATUS; stdcall;
{$EXTERNALSYM NetDfsRemoveStdRoot}

function NetDfsAddFtRoot(ServerName, RootShare, FtDfsName, Comment: LPWSTR; Flags: DWORD): NET_API_STATUS; stdcall;
{$EXTERNALSYM NetDfsAddFtRoot}

function NetDfsRemoveFtRoot(ServerName, RootShare, FtDfsName: LPWSTR; Flags: DWORD): NET_API_STATUS; stdcall;
{$EXTERNALSYM NetDfsRemoveFtRoot}

function NetDfsRemoveFtRootForced(DomainName, ServerName, RootShare, FtDfsName: LPWSTR; Flags: DWORD): NET_API_STATUS; stdcall;
{$EXTERNALSYM NetDfsRemoveFtRootForced}

//
// Call to reinitialize the dfsmanager on a machine
//

function NetDfsManagerInitialize(ServerName: LPWSTR; Flags: DWORD): NET_API_STATUS; stdcall;
{$EXTERNALSYM NetDfsManagerInitialize}

function NetDfsAddStdRootForced(ServerName, RootShare, Comment, Store: LPWSTR): NET_API_STATUS; stdcall;
{$EXTERNALSYM NetDfsAddStdRootForced}

function NetDfsGetDcAddress(ServerName: LPWSTR; var DcIpAddress: LPWSTR; var IsRoot: BOOLEAN; Timeout: PULONG): NET_API_STATUS; stdcall;
{$EXTERNALSYM NetDfsGetDcAddress}

//
// Flags for NetDfsSetDcAddress()
//

const
  NET_DFS_SETDC_FLAGS   = $00000000;
  {$EXTERNALSYM NET_DFS_SETDC_FLAGS}
  NET_DFS_SETDC_TIMEOUT = $00000001;
  {$EXTERNALSYM NET_DFS_SETDC_TIMEOUT}
  NET_DFS_SETDC_INITPKT = $00000002;
  {$EXTERNALSYM NET_DFS_SETDC_INITPKT}

//
// Structures used for site reporting
//

type
  LPDFS_SITENAME_INFO = ^DFS_SITENAME_INFO;
  {$EXTERNALSYM LPDFS_SITENAME_INFO}
  PDFS_SITENAME_INFO = ^DFS_SITENAME_INFO;
  {$EXTERNALSYM PDFS_SITENAME_INFO}
  DFS_SITENAME_INFO = record
    SiteFlags: ULONG; // Below
    SiteName: LPWSTR;
  end;
  {$EXTERNALSYM DFS_SITENAME_INFO}
  TDfsSiteNameInfo = DFS_SITENAME_INFO;
  PDfsSiteNameInfo = PDFS_SITENAME_INFO;

// SiteFlags

const
  DFS_SITE_PRIMARY = $1; // This site returned by DsGetSiteName()
  {$EXTERNALSYM DFS_SITE_PRIMARY}

type
  LPDFS_SITELIST_INFO = ^DFS_SITELIST_INFO;
  {$EXTERNALSYM LPDFS_SITELIST_INFO}
  PDFS_SITELIST_INFO = ^DFS_SITELIST_INFO;
  {$EXTERNALSYM PDFS_SITELIST_INFO}
  DFS_SITELIST_INFO = record
    cSites: ULONG;
    Site: array [0..0] of DFS_SITENAME_INFO;
  end;
  {$EXTERNALSYM DFS_SITELIST_INFO}
  TDfsSiteListInfo = DFS_SITELIST_INFO;
  PDfsSiteListInfo = PDFS_SITELIST_INFO;

//
// Remove a volume or additional storage for volume from the Dfs at
// DfsEntryPath. When applied to the last storage in a volume, removes
// the volume from the DFS.
//

function NetDfsRemove(DfsEntryPath, ServerName, ShareName: LPWSTR): NET_API_STATUS; stdcall;
{$EXTERNALSYM NetDfsRemove}

//
// Get information about all of the volumes in the Dfs. DfsName is
// the "server" part of the UNC name used to refer to this particular Dfs.
//
// Valid levels are 1-4, 200
//

function NetDfsEnum(DfsName: LPWSTR; Level, PrefMaxLen: DWORD; var Buffer: LPBYTE; EntriesRead, ResumeHandle: LPDWORD): NET_API_STATUS; stdcall;
{$EXTERNALSYM NetDfsEnum}

//
// Get information about the volume or storage.
// If ServerName and ShareName are specified, the information returned
// is specific to that server and share, else the information is specific
// to the volume as a whole.
//
// Valid levels are 1-4, 100
//

function NetDfsGetInfo(DfsEntryPath, ServerName, ShareName: LPWSTR; Level: DWORD; var Buffer: LPBYTE): NET_API_STATUS; stdcall;
{$EXTERNALSYM NetDfsGetInfo}

//
// Set info about the volume or storage.
// If ServerName and ShareName are specified, the information set is
// specific to that server and share, else the information is specific
// to the volume as a whole.
//
// Valid levels are 100, 101 and 102
//

function NetDfsSetInfo(DfsEntryPath, ServerName, ShareName: LPWSTR; Level: DWORD; Buffer: LPBYTE): NET_API_STATUS; stdcall;
{$EXTERNALSYM NetDfsSetInfo}

//
// Get client's cached information about the volume or storage.
// If ServerName and ShareName are specified, the information returned
// is specific to that server and share, else the information is specific
// to the volume as a whole.
//
// Valid levels are 1-4
//

function NetDfsGetClientInfo(DfsEntryPath, ServerName, ShareName: LPWSTR; Level: DWORD; var Buffer: LPBYTE): NET_API_STATUS; stdcall;
{$EXTERNALSYM NetDfsGetClientInfo}

//
// Set client's cached info about the volume or storage.
// If ServerName and ShareName are specified, the information set is
// specific to that server and share, else the information is specific
// to the volume as a whole.
//
// Valid levels are 101 and 102.
//

function NetDfsSetClientInfo(DfsEntryPath, ServerName, ShareName: LPWSTR; Level: DWORD; Buffer: LPBYTE): NET_API_STATUS; stdcall;
{$EXTERNALSYM NetDfsSetClientInfo}

//
// Move a DFS volume and all subordinate volumes from one place in the
// DFS to another place in the DFS.
//

function NetDfsMove(DfsEntryPath: LPWSTR; DfsNewEntryPath: LPWSTR): NET_API_STATUS; stdcall;
{$EXTERNALSYM NetDfsMove}

function NetDfsRename(Path: LPWSTR; NewPath: LPWSTR): NET_API_STATUS; stdcall;
{$EXTERNALSYM NetDfsRename}

implementation


{$IFDEF DYNAMIC_LINK}
var
  _NetDfsAdd: Pointer;

function NetDfsAdd;
begin
  GetProcedureAddress(_NetDfsAdd, netapi32, 'NetDfsAdd');
  asm
    mov esp, ebp
    pop ebp
    jmp [_NetDfsAdd]
  end;
end;
{$ELSE}
function NetDfsAdd; external netapi32 name 'NetDfsAdd';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _NetDfsAddStdRoot: Pointer;

function NetDfsAddStdRoot;
begin
  GetProcedureAddress(_NetDfsAddStdRoot, netapi32, 'NetDfsAddStdRoot');
  asm
    mov esp, ebp
    pop ebp
    jmp [_NetDfsAddStdRoot]
  end;
end;
{$ELSE}
function NetDfsAddStdRoot; external netapi32 name 'NetDfsAddStdRoot';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _NetDfsRemoveStdRoot: Pointer;

function NetDfsRemoveStdRoot;
begin
  GetProcedureAddress(_NetDfsRemoveStdRoot, netapi32, 'NetDfsRemoveStdRoot');
  asm
    mov esp, ebp
    pop ebp
    jmp [_NetDfsRemoveStdRoot]
  end;
end;
{$ELSE}
function NetDfsRemoveStdRoot; external netapi32 name 'NetDfsRemoveStdRoot';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _NetDfsAddFtRoot: Pointer;

function NetDfsAddFtRoot;
begin
  GetProcedureAddress(_NetDfsAddFtRoot, netapi32, 'NetDfsAddFtRoot');
  asm
    mov esp, ebp
    pop ebp
    jmp [_NetDfsAddFtRoot]
  end;
end;
{$ELSE}
function NetDfsAddFtRoot; external netapi32 name 'NetDfsAddFtRoot';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _NetDfsRemoveFtRoot: Pointer;

function NetDfsRemoveFtRoot;
begin
  GetProcedureAddress(_NetDfsRemoveFtRoot, netapi32, 'NetDfsRemoveFtRoot');
  asm
    mov esp, ebp
    pop ebp
    jmp [_NetDfsRemoveFtRoot]
  end;
end;
{$ELSE}
function NetDfsRemoveFtRoot; external netapi32 name 'NetDfsRemoveFtRoot';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _NetDfsRemoveFtRootForced: Pointer;

function NetDfsRemoveFtRootForced;
begin
  GetProcedureAddress(_NetDfsRemoveFtRootForced, netapi32, 'NetDfsRemoveFtRootForced');
  asm
    mov esp, ebp
    pop ebp
    jmp [_NetDfsRemoveFtRootForced]
  end;
end;
{$ELSE}
function NetDfsRemoveFtRootForced; external netapi32 name 'NetDfsRemoveFtRootForced';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _NetDfsManagerInitialize: Pointer;

function NetDfsManagerInitialize;
begin
  GetProcedureAddress(_NetDfsManagerInitialize, netapi32, 'NetDfsManagerInitialize');
  asm
    mov esp, ebp
    pop ebp
    jmp [_NetDfsManagerInitialize]
  end;
end;
{$ELSE}
function NetDfsManagerInitialize; external netapi32 name 'NetDfsManagerInitialize';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _NetDfsAddStdRootForced: Pointer;

function NetDfsAddStdRootForced;
begin
  GetProcedureAddress(_NetDfsAddStdRootForced, netapi32, 'NetDfsAddStdRootForced');
  asm
    mov esp, ebp
    pop ebp
    jmp [_NetDfsAddStdRootForced]
  end;
end;
{$ELSE}
function NetDfsAddStdRootForced; external netapi32 name 'NetDfsAddStdRootForced';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _NetDfsGetDcAddress: Pointer;

function NetDfsGetDcAddress;
begin
  GetProcedureAddress(_NetDfsGetDcAddress, netapi32, 'NetDfsGetDcAddress');
  asm
    mov esp, ebp
    pop ebp
    jmp [_NetDfsGetDcAddress]
  end;
end;
{$ELSE}
function NetDfsGetDcAddress; external netapi32 name 'NetDfsGetDcAddress';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _NetDfsRemove: Pointer;

function NetDfsRemove;
begin
  GetProcedureAddress(_NetDfsRemove, netapi32, 'NetDfsRemove');
  asm
    mov esp, ebp
    pop ebp
    jmp [_NetDfsRemove]
  end;
end;
{$ELSE}
function NetDfsRemove; external netapi32 name 'NetDfsRemove';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _NetDfsEnum: Pointer;

function NetDfsEnum;
begin
  GetProcedureAddress(_NetDfsEnum, netapi32, 'NetDfsEnum');
  asm
    mov esp, ebp
    pop ebp
    jmp [_NetDfsEnum]
  end;
end;
{$ELSE}
function NetDfsEnum; external netapi32 name 'NetDfsEnum';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _NetDfsGetInfo: Pointer;

function NetDfsGetInfo;
begin
  GetProcedureAddress(_NetDfsGetInfo, netapi32, 'NetDfsGetInfo');
  asm
    mov esp, ebp
    pop ebp
    jmp [_NetDfsGetInfo]
  end;
end;
{$ELSE}
function NetDfsGetInfo; external netapi32 name 'NetDfsGetInfo';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _NetDfsSetInfo: Pointer;

function NetDfsSetInfo;
begin
  GetProcedureAddress(_NetDfsSetInfo, netapi32, 'NetDfsSetInfo');
  asm
    mov esp, ebp
    pop ebp
    jmp [_NetDfsSetInfo]
  end;
end;
{$ELSE}
function NetDfsSetInfo; external netapi32 name 'NetDfsSetInfo';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _NetDfsGetClientInfo: Pointer;

function NetDfsGetClientInfo;
begin
  GetProcedureAddress(_NetDfsGetClientInfo, netapi32, 'NetDfsGetClientInfo');
  asm
    mov esp, ebp
    pop ebp
    jmp [_NetDfsGetClientInfo]
  end;
end;
{$ELSE}
function NetDfsGetClientInfo; external netapi32 name 'NetDfsGetClientInfo';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _NetDfsSetClientInfo: Pointer;

function NetDfsSetClientInfo;
begin
  GetProcedureAddress(_NetDfsSetClientInfo, netapi32, 'NetDfsSetClientInfo');
  asm
    mov esp, ebp
    pop ebp
    jmp [_NetDfsSetClientInfo]
  end;
end;
{$ELSE}
function NetDfsSetClientInfo; external netapi32 name 'NetDfsSetClientInfo';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _NetDfsMove: Pointer;

function NetDfsMove;
begin
  GetProcedureAddress(_NetDfsMove, netapi32, 'NetDfsMove');
  asm
    mov esp, ebp
    pop ebp
    jmp [_NetDfsMove]
  end;
end;
{$ELSE}
function NetDfsMove; external netapi32 name 'NetDfsMove';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _NetDfsRename: Pointer;

function NetDfsRename;
begin
  GetProcedureAddress(_NetDfsRename, netapi32, 'NetDfsRename');
  asm
    mov esp, ebp
    pop ebp
    jmp [_NetDfsRename]
  end;
end;
{$ELSE}
function NetDfsRename; external netapi32 name 'NetDfsRename';
{$ENDIF DYNAMIC_LINK}

end.
