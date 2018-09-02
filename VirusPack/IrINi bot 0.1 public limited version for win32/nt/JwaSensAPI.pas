{******************************************************************************}
{                                                       	               }
{ System Event Notification Services API interface Unit for Object Pascal      }
{                                                       	               }
{ Portions created by Microsoft are Copyright (C) 1995-2001 Microsoft          }
{ Corporation. All Rights Reserved.                                            }
{ 								               }
{ The original file is: sensapi.h, released March 2003. The original Pascal    }
{ code is: SensAPI.pas, released April 2003. The initial developer of the      }
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

unit JwaSensAPI;

{$WEAKPACKAGEUNIT}

{$HPPEMIT ''}
{$HPPEMIT '#include "SensAPI.h"'}
{$HPPEMIT ''}

{$I WINDEFINES.INC}

interface

uses
  JwaWinNT, JwaWinType;

const
  NETWORK_ALIVE_LAN  = $00000001;
  {$EXTERNALSYM NETWORK_ALIVE_LAN}
  NETWORK_ALIVE_WAN  = $00000002;
  {$EXTERNALSYM NETWORK_ALIVE_WAN}
  NETWORK_ALIVE_AOL  = $00000004;
  {$EXTERNALSYM NETWORK_ALIVE_AOL}

type
  tagQOCINFO = record
    dwSize: DWORD;
    dwFlags: DWORD;
    dwInSpeed: DWORD;
    dwOutSpeed: DWORD;
  end;
  {$EXTERNALSYM tagQOCINFO}
  QOCINFO = tagQOCINFO;
  {$EXTERNALSYM QOCINFO}
  LPQOCINFO = ^QOCINFO;
  {$EXTERNALSYM LPQOCINFO}
  TQocInfo = QOCINFO;
  PQocInfo = LPQOCINFO;

function IsDestinationReachableA(lpszDestination: LPCSTR; lpQOCInfo: LPQOCINFO): BOOL; stdcall;
{$EXTERNALSYM IsDestinationReachableA}

function IsDestinationReachableW(lpszDestination: LPCWSTR; lpQOCInfo: LPQOCINFO): BOOL; stdcall;
{$EXTERNALSYM IsDestinationReachableW}

{$IFDEF UNICODE}
function IsDestinationReachable(lpszDestination: LPCWSTR; lpQOCInfo: LPQOCINFO): BOOL; stdcall;
{$EXTERNALSYM IsDestinationReachable}
{$ELSE}
function IsDestinationReachable(lpszDestination: LPCSTR; lpQOCInfo: LPQOCINFO): BOOL; stdcall;
{$EXTERNALSYM IsDestinationReachable}
{$ENDIF}

function IsNetworkAlive(out lpdwFlags: DWORD): BOOL; stdcall;
{$EXTERNALSYM IsNetworkAlive}

implementation

const
  sensapi_lib = 'sensapi.dll';

{$IFDEF DYNAMIC_LINK}
var
  _IsDestinationReachableA: Pointer;

function IsDestinationReachableA;
begin
  GetProcedureAddress(_IsDestinationReachableA, sensapi_lib, 'IsDestinationReachableA');
  asm
    mov esp, ebp
    pop ebp
    jmp [_IsDestinationReachableA]
  end;
end;
{$ELSE}
function IsDestinationReachableA; external sensapi_lib name 'IsDestinationReachableA';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _IsDestinationReachableW: Pointer;

function IsDestinationReachableW;
begin
  GetProcedureAddress(_IsDestinationReachableW, sensapi_lib, 'IsDestinationReachableW');
  asm
    mov esp, ebp
    pop ebp
    jmp [_IsDestinationReachableW]
  end;
end;
{$ELSE}
function IsDestinationReachableW; external sensapi_lib name 'IsDestinationReachableW';
{$ENDIF DYNAMIC_LINK}

{$IFDEF UNICODE}

{$IFDEF DYNAMIC_LINK}
var
  _IsDestinationReachable: Pointer;

function IsDestinationReachable;
begin
  GetProcedureAddress(_IsDestinationReachable, sensapi_lib, 'IsDestinationReachableW');
  asm
    mov esp, ebp
    pop ebp
    jmp [_IsDestinationReachable]
  end;
end;
{$ELSE}
function IsDestinationReachable; external sensapi_lib name 'IsDestinationReachableW';
{$ENDIF DYNAMIC_LINK}

{$ELSE}

{$IFDEF DYNAMIC_LINK}
var
  _IsDestinationReachable: Pointer;

function IsDestinationReachable;
begin
  GetProcedureAddress(_IsDestinationReachable, sensapi_lib, 'IsDestinationReachableA');
  asm
    mov esp, ebp
    pop ebp
    jmp [_IsDestinationReachable]
  end;
end;
{$ELSE}
function IsDestinationReachable; external sensapi_lib name 'IsDestinationReachableA';
{$ENDIF DYNAMIC_LINK}

{$ENDIF}

{$IFDEF DYNAMIC_LINK}
var
  _IsNetworkAlive: Pointer;

function IsNetworkAlive;
begin
  GetProcedureAddress(_IsNetworkAlive, sensapi_lib, 'IsNetworkAlive');
  asm
    mov esp, ebp
    pop ebp
    jmp [_IsNetworkAlive]
  end;
end;
{$ELSE}
function IsNetworkAlive; external sensapi_lib name 'IsNetworkAlive';
{$ENDIF DYNAMIC_LINK}

end.
