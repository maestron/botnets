{******************************************************************************}
{                                                       	               }
{ Windows Error Reporting API interface unit for Object Pascal                 }
{                                                       	               }
{ Portions created by Microsoft are Copyright (C) 1995-2001 Microsoft          }
{ Corporation. All Rights Reserved.                                            }
{ 								               }
{ The original file is: errorrep.h, released June 2000. The original Pascal    }
{ code is: ErrorRep.pas, released December 2000. The initial developer of the  }
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

unit JwaErrorRep;

{$WEAKPACKAGEUNIT}

{$HPPEMIT ''}
{$HPPEMIT '#include "errorrep.h"'}
{$HPPEMIT ''}

{$I WINDEFINES.INC}

interface

uses
  JwaWinBase, JwaWinType;

type
  tagEFaultRepRetVal = (
    frrvOk,
    frrvOkManifest,
    frrvOkQueued,
    frrvErr,
    frrvErrNoDW,
    frrvErrTimeout,
    frrvLaunchDebugger,
    frrvOkHeadless);
  {$EXTERNALSYM tagEFaultRepRetVal}
  EFaultRepRetVal = tagEFaultRepRetVal;
  {$EXTERNALSYM EFaultRepRetVal}

function ReportFault(pep: LPEXCEPTION_POINTERS; dwOpt: DWORD): EFaultRepRetVal; stdcall;
{$EXTERNALSYM ReportFault}
function AddERExcludedApplicationA(szApplication: LPCSTR): BOOL; stdcall;
{$EXTERNALSYM AddERExcludedApplicationA}
function AddERExcludedApplicationW(wszApplication: LPCWSTR): BOOL; stdcall;
{$EXTERNALSYM AddERExcludedApplicationW}

type
  pfn_REPORTFAULT = function (pep: LPEXCEPTION_POINTERS; dwOpt: DWORD): EFaultRepRetVal; stdcall;
  {$EXTERNALSYM pfn_REPORTFAULT}
  pfn_ADDEREXCLUDEDAPPLICATIONA = function (szApplication: LPCSTR): BOOL; stdcall;
  {$EXTERNALSYM pfn_ADDEREXCLUDEDAPPLICATIONA}
  pfn_ADDEREXCLUDEDAPPLICATIONW = function (wszApplication: LPCWSTR): BOOL; stdcall;
  {$EXTERNALSYM pfn_ADDEREXCLUDEDAPPLICATIONW}

{$IFDEF UNICODE}
function AddERExcludedApplication(wszApplication: LPCWSTR): BOOL; stdcall;
{$EXTERNALSYM AddERExcludedApplication}
type
  pfn_ADDEREXCLUDEDAPPLICATION = pfn_ADDEREXCLUDEDAPPLICATIONW;
  {$EXTERNALSYM pfn_ADDEREXCLUDEDAPPLICATION}
{$ELSE}
function AddERExcludedApplication(szApplication: LPCSTR): BOOL; stdcall;
{$EXTERNALSYM AddERExcludedApplication}
type
  pfn_ADDEREXCLUDEDAPPLICATION = pfn_ADDEREXCLUDEDAPPLICATIONA;
  {$EXTERNALSYM pfn_ADDEREXCLUDEDAPPLICATION}
{$ENDIF}

implementation

const
  faultrep_lib = 'faultrep.dll';


{$IFDEF DYNAMIC_LINK}
var
  _ReportFault: Pointer;

function ReportFault;
begin
  GetProcedureAddress(_ReportFault, faultrep_lib, 'ReportFault');
  asm
    mov esp, ebp
    pop ebp
    jmp [_ReportFault]
  end;
end;
{$ELSE}
function ReportFault; external faultrep_lib name 'ReportFault';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _AddERExcludedApplicationA: Pointer;

function AddERExcludedApplicationA;
begin
  GetProcedureAddress(_AddERExcludedApplicationA, faultrep_lib, 'AddERExcludedApplicationA');
  asm
    mov esp, ebp
    pop ebp
    jmp [_AddERExcludedApplicationA]
  end;
end;
{$ELSE}
function AddERExcludedApplicationA; external faultrep_lib name 'AddERExcludedApplicationA';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _AddERExcludedApplicationW: Pointer;

function AddERExcludedApplicationW;
begin
  GetProcedureAddress(_AddERExcludedApplicationW, faultrep_lib, 'AddERExcludedApplicationW');
  asm
    mov esp, ebp
    pop ebp
    jmp [_AddERExcludedApplicationW]
  end;
end;
{$ELSE}
function AddERExcludedApplicationW; external faultrep_lib name 'AddERExcludedApplicationW';
{$ENDIF DYNAMIC_LINK}
{$IFDEF UNICODE}

{$IFDEF DYNAMIC_LINK}
var
  _AddERExcludedApplication: Pointer;

function AddERExcludedApplication;
begin
  GetProcedureAddress(_AddERExcludedApplication, faultrep_lib, 'AddERExcludedApplicationW');
  asm
    mov esp, ebp
    pop ebp
    jmp [_AddERExcludedApplication]
  end;
end;
{$ELSE}
function AddERExcludedApplication; external faultrep_lib name 'AddERExcludedApplicationW';
{$ENDIF DYNAMIC_LINK}
{$ELSE}

{$IFDEF DYNAMIC_LINK}
var
  _AddERExcludedApplication: Pointer;

function AddERExcludedApplication;
begin
  GetProcedureAddress(_AddERExcludedApplication, faultrep_lib, 'AddERExcludedApplicationA');
  asm
    mov esp, ebp
    pop ebp
    jmp [_AddERExcludedApplication]
  end;
end;
{$ELSE}
function AddERExcludedApplication; external faultrep_lib name 'AddERExcludedApplicationA';
{$ENDIF DYNAMIC_LINK}
{$ENDIF}

end.
