{******************************************************************************}
{                                                       	               }
{ Single-Instance Store API interface Unit for Object Pascal                   }
{                                                       	               }
{ Portions created by Microsoft are Copyright (C) 1995-2001 Microsoft          }
{ Corporation. All Rights Reserved.                                            }
{ 								               }
{ The original file is: sisbkup.h, released August 2001. The original Pascal   }
{ code is: SisBkUp.pas, released December 2001. The initial developer of the   }
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

unit JwaSisBkUp;

{$WEAKPACKAGEUNIT}

{$HPPEMIT ''}
{$HPPEMIT '#include "sisbkup.h"'}
{$HPPEMIT ''}

{$I WINDEFINES.INC}

interface

uses
  JwaWinNT, JwaWinType;

function SisCreateBackupStructure(volumeRoot: PWCHAR; var sisBackupStructure: PVOID; var commonStoreRootPathname: PWCHAR;
  countOfCommonStoreFilesToBackup: PULONG; var commonStoreFilesToBackup: PWCHAR): BOOL; stdcall;
{$EXTERNALSYM SisCreateBackupStructure}

function SisCSFilesToBackupForLink(sisBackupStructure, reparseData: PVOID; reparseDataSize: ULONG; thisFileContext: PVOID;
  matchingFileContext: PPVOID; countOfCommonStoreFilesToBackup: PULONG; var commonStoreFilesToBackup: PWCHAR): BOOL; stdcall;
{$EXTERNALSYM SisCSFilesToBackupForLink}

function SisFreeBackupStructure(sisBackupStructure: PVOID): BOOL; stdcall;
{$EXTERNALSYM SisFreeBackupStructure}

function SisCreateRestoreStructure(volumeRoot: PWCHAR; var sisRestoreStructure: PVOID; var commonStoreRootPathname: PWCHAR;
  countOfCommonStoreFilesToRestore: PULONG; var commonStoreFilesToRestore: PWCHAR): BOOL; stdcall;
{$EXTERNALSYM SisCreateRestoreStructure}

function SisRestoredLink(sisRestoreStructure: PVOID; restoredFileName: PWCHAR; reparseData: PVOID; reparseDataSize: ULONG;
  countOfCommonStoreFilesToRestore: PULONG; var commonStoreFilesToRestore: PWCHAR): BOOL; stdcall;
{$EXTERNALSYM SisRestoredLink}

function SisRestoredCommonStoreFile(sisRestoreStructure: PVOID; commonStoreFileName: PWCHAR): BOOL; stdcall;
{$EXTERNALSYM SisRestoredCommonStoreFile}

function SisFreeRestoreStructure(sisRestoreStructure: PVOID): BOOL; stdcall;
{$EXTERNALSYM SisFreeRestoreStructure}

function SisFreeAllocatedMemory(allocatedSpace: PVOID): BOOL; stdcall;
{$EXTERNALSYM SisFreeAllocatedMemory}

//
// SIS entry function typedefs
//

type
  PF_SISCREATEBACKUPSTRUCTURE = function (volumeRoot: PWCHAR; var sisBackupStructure: PVOID; var commonStoreRootPathname: PWCHAR;
    countOfCommonStoreFilesToBackup: PULONG; var commonStoreFilesToBackup: PWCHAR): BOOL; stdcall;
  {$EXTERNALSYM PF_SISCREATEBACKUPSTRUCTURE}
  TSisCreateBackupStructure = PF_SISCREATEBACKUPSTRUCTURE;

  PF_SISCSFILESTOBACKUPFORLINK = function (sisBackupStructure, reparseData: PVOID; reparseDataSize: ULONG; thisFileContext: PVOID;
    matchingFileContext: PPVOID; countOfCommonStoreFilesToBackup: PULONG; var commonStoreFilesToBackup: PWCHAR): BOOL; stdcall;
  {$EXTERNALSYM PF_SISCSFILESTOBACKUPFORLINK}
  TSisCSFilesToBackupForLink = PF_SISCSFILESTOBACKUPFORLINK;

  PF_SISFREEBACKUPSTRUCTURE = function (sisBackupStructure: PVOID): BOOL; stdcall;
  {$EXTERNALSYM PF_SISFREEBACKUPSTRUCTURE}
  TSusFreeBackupStructure = PF_SISFREEBACKUPSTRUCTURE;

  PF_SISCREATERESTORESTRUCTURE = function (volumeRoot: PWCHAR; var sisRestoreStructure: PVOID; var commonStoreRootPathname: PWCHAR;
    countOfCommonStoreFilesToRestore: PULONG; var commonStoreFilesToRestore: PWCHAR): BOOL; stdcall;
  {$EXTERNALSYM PF_SISCREATERESTORESTRUCTURE}
  TSisCreateRestoreStructure = PF_SISCREATERESTORESTRUCTURE;

  PF_SISRESTOREDLINK = function (sisRestoreStructure: PVOID; restoredFileName: PWCHAR; reparseData: PVOID; reparseDataSize: ULONG;
    countOfCommonStoreFilesToRestore: PULONG; var commonStoreFilesToRestore: PWCHAR): BOOL; stdcall;
  {$EXTERNALSYM PF_SISRESTOREDLINK}
  TSisRestoredLink = PF_SISRESTOREDLINK;

  PF_SISRESTOREDCOMMONSTOREFILE = function (sisRestoreStructure: PVOID; commonStoreFileName: PWCHAR): BOOL; stdcall;
  {$EXTERNALSYM PF_SISRESTOREDCOMMONSTOREFILE}
  TSisRestoredCommonStoreFile = PF_SISRESTOREDCOMMONSTOREFILE;

  PF_SISFREERESTORESTRUCTURE = function (sisRestoreStructure: PVOID): BOOL; stdcall;
  {$EXTERNALSYM PF_SISFREERESTORESTRUCTURE}
  TSisFreeRestoreStructure = PF_SISFREERESTORESTRUCTURE;

  PF_SISFREEALLOCATEDMEMORY = function (allocatedSpace: PVOID): BOOL; stdcall;
  {$EXTERNALSYM PF_SISFREEALLOCATEDMEMORY}
  TSisFreeAllocatedMemory = PF_SISFREEALLOCATEDMEMORY;

implementation

const
  sisbkup = 'sisbkup.dll';


{$IFDEF DYNAMIC_LINK}
var
  _SisCreateBackupStructure: Pointer;

function SisCreateBackupStructure;
begin
  GetProcedureAddress(_SisCreateBackupStructure, sisbkup, 'SisCreateBackupStructure');
  asm
    mov esp, ebp
    pop ebp
    jmp [_SisCreateBackupStructure]
  end;
end;
{$ELSE}
function SisCreateBackupStructure; external sisbkup name 'SisCreateBackupStructure';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _SisCSFilesToBackupForLink: Pointer;

function SisCSFilesToBackupForLink;
begin
  GetProcedureAddress(_SisCSFilesToBackupForLink, sisbkup, 'SisCSFilesToBackupForLink');
  asm
    mov esp, ebp
    pop ebp
    jmp [_SisCSFilesToBackupForLink]
  end;
end;
{$ELSE}
function SisCSFilesToBackupForLink; external sisbkup name 'SisCSFilesToBackupForLink';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _SisFreeBackupStructure: Pointer;

function SisFreeBackupStructure;
begin
  GetProcedureAddress(_SisFreeBackupStructure, sisbkup, 'SisFreeBackupStructure');
  asm
    mov esp, ebp
    pop ebp
    jmp [_SisFreeBackupStructure]
  end;
end;
{$ELSE}
function SisFreeBackupStructure; external sisbkup name 'SisFreeBackupStructure';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _SisCreateRestoreStructure: Pointer;

function SisCreateRestoreStructure;
begin
  GetProcedureAddress(_SisCreateRestoreStructure, sisbkup, 'SisCreateRestoreStructure');
  asm
    mov esp, ebp
    pop ebp
    jmp [_SisCreateRestoreStructure]
  end;
end;
{$ELSE}
function SisCreateRestoreStructure; external sisbkup name 'SisCreateRestoreStructure';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _SisRestoredLink: Pointer;

function SisRestoredLink;
begin
  GetProcedureAddress(_SisRestoredLink, sisbkup, 'SisRestoredLink');
  asm
    mov esp, ebp
    pop ebp
    jmp [_SisRestoredLink]
  end;
end;
{$ELSE}
function SisRestoredLink; external sisbkup name 'SisRestoredLink';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _SisRestoredCommonStoreFile: Pointer;

function SisRestoredCommonStoreFile;
begin
  GetProcedureAddress(_SisRestoredCommonStoreFile, sisbkup, 'SisRestoredCommonStoreFile');
  asm
    mov esp, ebp
    pop ebp
    jmp [_SisRestoredCommonStoreFile]
  end;
end;
{$ELSE}
function SisRestoredCommonStoreFile; external sisbkup name 'SisRestoredCommonStoreFile';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _SisFreeRestoreStructure: Pointer;

function SisFreeRestoreStructure;
begin
  GetProcedureAddress(_SisFreeRestoreStructure, sisbkup, 'SisFreeRestoreStructure');
  asm
    mov esp, ebp
    pop ebp
    jmp [_SisFreeRestoreStructure]
  end;
end;
{$ELSE}
function SisFreeRestoreStructure; external sisbkup name 'SisFreeRestoreStructure';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _SisFreeAllocatedMemory: Pointer;

function SisFreeAllocatedMemory;
begin
  GetProcedureAddress(_SisFreeAllocatedMemory, sisbkup, 'SisFreeAllocatedMemory');
  asm
    mov esp, ebp
    pop ebp
    jmp [_SisFreeAllocatedMemory]
  end;
end;
{$ELSE}
function SisFreeAllocatedMemory; external sisbkup name 'SisFreeAllocatedMemory';
{$ENDIF DYNAMIC_LINK}

end.
