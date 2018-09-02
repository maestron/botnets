{******************************************************************************}
{                                                       	               }
{ Net Shell API interface Unit for Object Pascal                               }
{                                                       	               }
{ Portions created by Microsoft are Copyright (C) 1995-2001 Microsoft          }
{ Corporation. All Rights Reserved.                                            }
{ 								               }
{ The original file is: netsh.h, released August 2001. The original Pascal     }
{ code is: NetSh.pas, released December 2001. The initial developer of the     }
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

unit JwaNetSh;

{$WEAKPACKAGEUNIT}

{$HPPEMIT ''}
{$HPPEMIT '#include "netsh.h"'}
{$HPPEMIT ''}

{$I WINDEFINES.INC}

interface

uses
  JwaWinNT, JwaWinType;

// This file contains definitions which are needed by all NetSh helper DLLs.

//
// Error codes
//

const
  NETSH_ERROR_BASE                 = 15000;
  {$EXTERNALSYM NETSH_ERROR_BASE}
  ERROR_NO_ENTRIES                 = (NETSH_ERROR_BASE + 0);
  {$EXTERNALSYM ERROR_NO_ENTRIES}
  ERROR_INVALID_SYNTAX             = (NETSH_ERROR_BASE + 1);
  {$EXTERNALSYM ERROR_INVALID_SYNTAX}
  ERROR_PROTOCOL_NOT_IN_TRANSPORT  = (NETSH_ERROR_BASE + 2);
  {$EXTERNALSYM ERROR_PROTOCOL_NOT_IN_TRANSPORT}
  ERROR_NO_CHANGE                  = (NETSH_ERROR_BASE + 3);
  {$EXTERNALSYM ERROR_NO_CHANGE}
  ERROR_CMD_NOT_FOUND              = (NETSH_ERROR_BASE + 4);
  {$EXTERNALSYM ERROR_CMD_NOT_FOUND}
  ERROR_ENTRY_PT_NOT_FOUND         = (NETSH_ERROR_BASE + 5);
  {$EXTERNALSYM ERROR_ENTRY_PT_NOT_FOUND}
  ERROR_DLL_LOAD_FAILED            = (NETSH_ERROR_BASE + 6);
  {$EXTERNALSYM ERROR_DLL_LOAD_FAILED}
  ERROR_INIT_DISPLAY               = (NETSH_ERROR_BASE + 7);
  {$EXTERNALSYM ERROR_INIT_DISPLAY}
  ERROR_TAG_ALREADY_PRESENT        = (NETSH_ERROR_BASE + 8);
  {$EXTERNALSYM ERROR_TAG_ALREADY_PRESENT}
  ERROR_INVALID_OPTION_TAG         = (NETSH_ERROR_BASE + 9);
  {$EXTERNALSYM ERROR_INVALID_OPTION_TAG}
  ERROR_NO_TAG                     = (NETSH_ERROR_BASE + 10);
  {$EXTERNALSYM ERROR_NO_TAG}
  ERROR_MISSING_OPTION             = (NETSH_ERROR_BASE + 11);
  {$EXTERNALSYM ERROR_MISSING_OPTION}
  ERROR_TRANSPORT_NOT_PRESENT      = (NETSH_ERROR_BASE + 12);
  {$EXTERNALSYM ERROR_TRANSPORT_NOT_PRESENT}
  ERROR_SHOW_USAGE                 = (NETSH_ERROR_BASE + 13);
  {$EXTERNALSYM ERROR_SHOW_USAGE}
  ERROR_INVALID_OPTION_VALUE       = (NETSH_ERROR_BASE + 14);
  {$EXTERNALSYM ERROR_INVALID_OPTION_VALUE}
  ERROR_OKAY                       = (NETSH_ERROR_BASE + 15);
  {$EXTERNALSYM ERROR_OKAY}
  ERROR_CONTINUE_IN_PARENT_CONTEXT = (NETSH_ERROR_BASE + 16);
  {$EXTERNALSYM ERROR_CONTINUE_IN_PARENT_CONTEXT}
  ERROR_SUPPRESS_OUTPUT            = (NETSH_ERROR_BASE + 17);
  {$EXTERNALSYM ERROR_SUPPRESS_OUTPUT}
  ERROR_HELPER_ALREADY_REGISTERED  = (NETSH_ERROR_BASE + 18);
  {$EXTERNALSYM ERROR_HELPER_ALREADY_REGISTERED}
  ERROR_CONTEXT_ALREADY_REGISTERED = (NETSH_ERROR_BASE + 19);
  {$EXTERNALSYM ERROR_CONTEXT_ALREADY_REGISTERED}
  NETSH_ERROR_END                  = ERROR_CONTEXT_ALREADY_REGISTERED;
  {$EXTERNALSYM NETSH_ERROR_END}

// Flags

type
  NS_CMD_FLAGS = DWORD;
  {$EXTERNALSYM NS_CMD_FLAGS}
  TNsCmdFlags = NS_CMD_FLAGS;

const
  CMD_FLAG_PRIVATE     = $01; // not valid in sub-contexts
  {$EXTERNALSYM CMD_FLAG_PRIVATE}
  CMD_FLAG_INTERACTIVE = $02; // not valid from outside netsh
  {$EXTERNALSYM CMD_FLAG_INTERACTIVE}
  CMD_FLAG_LOCAL       = $08; // not valid from a remote machine
  {$EXTERNALSYM CMD_FLAG_LOCAL}
  CMD_FLAG_ONLINE      = $10; // not valid in offline/non-commit mode
  {$EXTERNALSYM CMD_FLAG_ONLINE}
  CMD_FLAG_HIDDEN      = $20; // hide from help but allow execution
  {$EXTERNALSYM CMD_FLAG_HIDDEN}
  CMD_FLAG_LIMIT_MASK  = $ffff;
  {$EXTERNALSYM CMD_FLAG_LIMIT_MASK}
  CMD_FLAG_PRIORITY    = DWORD($80000000); // ulPriority field is used*/
  {$EXTERNALSYM CMD_FLAG_PRIORITY}

type
  NS_REQS = (
    NS_REQ_ZERO,
    NS_REQ_PRESENT,
    NS_REQ_ALLOW_MULTIPLE,
    NS_REQ_ONE_OR_MORE);
  {$EXTERNALSYM NS_REQS}
 TNsReqs = NS_REQS;

  NS_EVENTS = DWORD;
  {$EXTERNALSYM NS_EVENTS}
  TNsEvents = NS_EVENTS;

const
  NS_EVENT_LOOP       = $00010000;
  {$EXTERNALSYM NS_EVENT_LOOP}
  NS_EVENT_LAST_N     = $00000001;
  {$EXTERNALSYM NS_EVENT_LAST_N}
  NS_EVENT_LAST_SECS  = $00000002;
  {$EXTERNALSYM NS_EVENT_LAST_SECS}
  NS_EVENT_FROM_N     = $00000004;
  {$EXTERNALSYM NS_EVENT_FROM_N}
  NS_EVENT_FROM_START = $00000008;
  {$EXTERNALSYM NS_EVENT_FROM_START}

type
  NS_MODE_CHANGE = (
    NETSH_COMMIT,
    NETSH_UNCOMMIT,
    NETSH_FLUSH,
    NETSH_COMMIT_STATE,
    NETSH_SAVE);
  {$EXTERNALSYM NS_MODE_CHANGE}
  TNsModeChange = NS_MODE_CHANGE;

const
  NS_GET_EVENT_IDS_FN_NAME = 'GetEventIds';
  {$EXTERNALSYM NS_GET_EVENT_IDS_FN_NAME}

// todo where is MAX_DLL_NAME
//  MAX_NAME_LEN = MAX_DLL_NAME;
//  {$EXTERNALSYM MAX_NAME_LEN}

  NETSH_VERSION_50 = $0005000;
  {$EXTERNALSYM NETSH_VERSION_50}

  NETSH_ARG_DELIMITER = WideString('=');
  {$EXTERNALSYM NETSH_ARG_DELIMITER}
  NETSH_CMD_DELIMITER = WideString(' ');
  {$EXTERNALSYM NETSH_CMD_DELIMITER}

  NETSH_MAX_TOKEN_LENGTH     = 64;
  {$EXTERNALSYM NETSH_MAX_TOKEN_LENGTH}
  NETSH_MAX_CMD_TOKEN_LENGTH = 128;
  {$EXTERNALSYM NETSH_MAX_CMD_TOKEN_LENGTH}

  NETSH_ROOT_GUID: TGUID = (
    D1: 0; D2: 0; D3: 0; D4: (0, 0, 0, 0, 0, 0, 0, 0));
  {$EXTERNALSYM NETSH_ROOT_GUID}

  DEFAULT_CONTEXT_PRIORITY = 100;
  {$EXTERNALSYM DEFAULT_CONTEXT_PRIORITY}

type
  PTOKEN_VALUE = ^TOKEN_VALUE;
  {$EXTERNALSYM PTOKEN_VALUE}
  _TOKEN_VALUE = record
    pwszToken: LPCWSTR; // literal token string
    dwValue: DWORD;     // ID of info string
  end;
  {$EXTERNALSYM _TOKEN_VALUE}
  TOKEN_VALUE = _TOKEN_VALUE;
  {$EXTERNALSYM TOKEN_VALUE}
  TTokenValue = TOKEN_VALUE;
  PTokenValue = PTOKEN_VALUE;

// Macros

(* TODO
#define CREATE_CMD_ENTRY(t,f)            {CMD_##t, f, HLP_##t, HLP_##t##_EX, CMD_FLAG_PRIVATE, NULL}
#define CREATE_CMD_ENTRY_EX(t,f,i)       {CMD_##t, f, HLP_##t, HLP_##t##_EX, i, NULL}
#define CREATE_CMD_ENTRY_EX_VER(t,f,i,v) {CMD_##t, f, HLP_##t, HLP_##t##_EX, i, v}

#define CREATE_CMD_GROUP_ENTRY(t,s)            {CMD_##t, HLP_##t, sizeof(s)/sizeof(CMD_ENTRY), 0, s, NULL }
#define CREATE_CMD_GROUP_ENTRY_EX(t,s,i)	   {CMD_##t, HLP_##t, sizeof(s)/sizeof(CMD_ENTRY), i, s, NULL }
#define CREATE_CMD_GROUP_ENTRY_EX_VER(t,s,i,v) {CMD_##t, HLP_##t, sizeof(s)/sizeof(CMD_ENTRY), i, s, v }

#define NUM_TOKENS_IN_TABLE(TokenArray) sizeof(TokenArray)/sizeof(TOKEN_VALUE)
#define NUM_TAGS_IN_TABLE(TagsArray)    sizeof(TagsArray)/sizeof(TAG_TYPE)
*)

// Callbacks

type
  NS_CONTEXT_COMMIT_FN = function (dwAction: DWORD): DWORD; stdcall;
  {$EXTERNALSYM NS_CONTEXT_COMMIT_FN}
  PNS_CONTEXT_COMMIT_FN = ^NS_CONTEXT_COMMIT_FN;
  {$EXTERNALSYM PNS_CONTEXT_COMMIT_FN}
  TNsContextCommitFn = NS_CONTEXT_COMMIT_FN;
  PNsContextCommitFn = PNS_CONTEXT_COMMIT_FN;

  NS_CONTEXT_CONNECT_FN = function (pwszMachine: LPCWSTR): DWORD; stdcall;
  {$EXTERNALSYM NS_CONTEXT_CONNECT_FN}
  PNS_CONTEXT_CONNECT_FN = ^NS_CONTEXT_CONNECT_FN;
  {$EXTERNALSYM PNS_CONTEXT_CONNECT_FN}
  TNsContextConnextFn = NS_CONTEXT_CONNECT_FN;
  PNsContextConnextFn = PNS_CONTEXT_CONNECT_FN;  

  NS_CONTEXT_DUMP_FN = function (pwszRouter: LPCWSTR; var ppwcArguments: LPWSTR; dwArgCount: DWORD; pvData: LPCVOID): DWORD; stdcall;
  {$EXTERNALSYM NS_CONTEXT_DUMP_FN}
  PNS_CONTEXT_DUMP_FN = ^NS_CONTEXT_DUMP_FN;
  {$EXTERNALSYM PNS_CONTEXT_DUMP_FN}
  TNsContextDumpFn = NS_CONTEXT_DUMP_FN;
  PNsContextDumpFn = PNS_CONTEXT_DUMP_FN;

  NS_DLL_STOP_FN = function (dwReserved: DWORD): DWORD; stdcall;
  {$EXTERNALSYM NS_DLL_STOP_FN}
  PNS_DLL_STOP_FN = ^NS_DLL_STOP_FN;
  {$EXTERNALSYM PNS_DLL_STOP_FN}
  TNsDllStopFn = NS_DLL_STOP_FN;
  PNsDllStopFn = PNS_DLL_STOP_FN;
    
  NS_HELPER_START_FN = function (const pguidParent: TGUID; dwVersion: DWORD): DWORD; stdcall;
  {$EXTERNALSYM NS_HELPER_START_FN}
  PNS_HELPER_START_FN = NS_HELPER_START_FN;
  {$EXTERNALSYM PNS_HELPER_START_FN}
  TNsHelperStartFn = NS_HELPER_START_FN;
  PNsHelperStartFn = PNS_HELPER_START_FN;

  NS_HELPER_STOP_FN = function (dwReserved: DWORD): DWORD; stdcall;
  {$EXTERNALSYM NS_HELPER_STOP_FN}
  PNS_HELPER_STOP_FN = ^NS_HELPER_STOP_FN;
  {$EXTERNALSYM PNS_HELPER_STOP_FN}
  TNsHelperStopFn = NS_HELPER_STOP_FN;
  PNsHelperStopFn = PNS_HELPER_STOP_FN;

  FN_HANDLE_CMD = function (pwszMachine: LPCWSTR; var ppwcArguments: LPWSTR; dwCurrentIndex, dwArgCount,
    dwFlags: DWORD; pvData: LPCVOID; var pbDone: BOOL): DWORD; stdcall;
  {$EXTERNALSYM FN_HANDLE_CMD}
  PFN_HANDLE_CMD = ^FN_HANDLE_CMD;
  {$EXTERNALSYM PFN_HANDLE_CMD}
  TFnHandleCmd = FN_HANDLE_CMD;
  PFnHandleCmd = PFN_HANDLE_CMD;

  NS_OSVERSIONCHECK = function (CIMOSType, CIMOSProductSuite: UINT; CIMOSVersion, CIMOSBuildNumber, CIMServicePackMajorVersion,
    CIMServicePackMinorVersion: LPCWSTR; CIMProcessorArchitecture: UINT; dwReserved: DWORD): BOOL; stdcall;
  {$EXTERNALSYM NS_OSVERSIONCHECK}
  PNS_OSVERSIONCHECK = ^NS_OSVERSIONCHECK;
  {$EXTERNALSYM PNS_OSVERSIONCHECK}
  TNsOSVersionCheck = NS_OSVERSIONCHECK;
  PNsOSVersionCheck = PNS_OSVERSIONCHECK;  

// Structures

  _NS_HELPER_ATTRIBUTES = record
    Union: record
    case Integer of
      0: (
        dwVersion: DWORD;
        dwReserved: DWORD);
      1: (
        _ullAlign: ULONGLONG);
    end;
    guidHelper: TGUID;                        // GUID associated with the helper
    pfnStart: PNS_HELPER_START_FN;            // Function to start this helper
    pfnStop: PNS_HELPER_STOP_FN;              // Function to stop this helper
  end;
  {$EXTERNALSYM _NS_HELPER_ATTRIBUTES}
  NS_HELPER_ATTRIBUTES = _NS_HELPER_ATTRIBUTES;
  {$EXTERNALSYM NS_HELPER_ATTRIBUTES}
  PNS_HELPER_ATTRIBUTES = ^NS_HELPER_ATTRIBUTES;
  {$EXTERNALSYM PNS_HELPER_ATTRIBUTES}
  TNsHelperAttributes = NS_HELPER_ATTRIBUTES;
  PNsHelperAttributes = PNS_HELPER_ATTRIBUTES;

  PCMD_ENTRY = ^CMD_ENTRY;
  {$EXTERNALSYM PCMD_ENTRY}
  _CMD_ENTRY = record
    pwszCmdToken: LPCWSTR; // The token for the command
    pfnCmdHandler: PFN_HANDLE_CMD; // The function which handles this command
    dwShortCmdHelpToken: DWORD; // The short help message
    dwCmdHlpToken: DWORD; // The message to display if the only thing after the command is a help token (HELP, /?, -?, ?)
    dwFlags: DWORD; // Flags (see CMD_FLAGS_xxx above)
    pOsVersionCheck: PNS_OSVERSIONCHECK; // Check for the version of the OS this command can run against
  end;
  {$EXTERNALSYM _CMD_ENTRY}
  CMD_ENTRY = _CMD_ENTRY;
  {$EXTERNALSYM CMD_ENTRY}
  TCmdEntry = CMD_ENTRY;
  PCmdEntry = PCMD_ENTRY;

  PCMD_GROUP_ENTRY = ^CMD_GROUP_ENTRY;
  {$EXTERNALSYM PCMD_GROUP_ENTRY}
  _CMD_GROUP_ENTRY = record
    pwszCmdGroupToken: LPCWSTR; // The token for the command verb
    dwShortCmdHelpToken: DWORD; // The message to display in a command listing.
    ulCmdGroupSize: ULONG; // The number of entries in the cmd table
    dwFlags: DWORD; // Flags (see CMD_FLAG_xxx)
    pCmdGroup: PCMD_ENTRY; // The command table
    pOsVersionCheck: PNS_OSVERSIONCHECK; // Check for the version of the OS this command can run against
  end;
  {$EXTERNALSYM _CMD_GROUP_ENTRY}
  CMD_GROUP_ENTRY = _CMD_GROUP_ENTRY;
  {$EXTERNALSYM CMD_GROUP_ENTRY}
  TCmdGroupEntry = CMD_GROUP_ENTRY;
  PCmdGroupEntry = PCMD_GROUP_ENTRY;

  _NS_CONTEXT_ATTRIBUTES = record
    Union: record
    case Integer of
      0: (
        dwVersion: DWORD;
        dwReserved: DWORD);
      1: (
        _ullAlign: ULONGLONG);
    end;
    pwszContext: LPWSTR;          // Name of the context
    guidHelper: TGUID;            // GUID of the helper servicing this context
    dwFlags: DWORD;               // Flags limiting when context is available. (See CMD_FLAG_xxx)
    ulPriority: ULONG;            // Priority field is only relevant if CMD_FLAG_PRIORITY is set in dwFlags
    ulNumTopCmds: ULONG;          // Number of top-level commands
    pTopCmds: PCMD_ENTRY;         // Array of top-level commands
    ulNumGroups: ULONG;           // Number of command groups
    pCmdGroups: PCMD_GROUP_ENTRY; // Array of command groups

    pfnCommitFn: PNS_CONTEXT_COMMIT_FN;
    pfnDumpFn: PNS_CONTEXT_DUMP_FN;
    pfnConnectFn: PNS_CONTEXT_CONNECT_FN;
    pReserved: PVOID;
    pfnOsVersionCheck: PNS_OSVERSIONCHECK;
  end;
  {$EXTERNALSYM _NS_CONTEXT_ATTRIBUTES}
  NS_CONTEXT_ATTRIBUTES = _NS_CONTEXT_ATTRIBUTES;
  {$EXTERNALSYM NS_CONTEXT_ATTRIBUTES}
  PNS_CONTEXT_ATTRIBUTES = ^NS_CONTEXT_ATTRIBUTES;
  {$EXTERNALSYM PNS_CONTEXT_ATTRIBUTES}
  TNsContextAttributes = NS_CONTEXT_ATTRIBUTES;
  PNsContextAttributes = PNS_CONTEXT_ATTRIBUTES;  

  PCNS_CONTEXT_ATTRIBUTES = ^_NS_CONTEXT_ATTRIBUTES;
  {$EXTERNALSYM PCNS_CONTEXT_ATTRIBUTES}

  PTAG_TYPE = ^TAG_TYPE;
  {$EXTERNALSYM PTAG_TYPE}
  _TAG_TYPE = record
    pwszTag: LPCWSTR;  // tag string
    dwRequired: DWORD; // required or not
    bPresent: BOOL;    // present or not
  end;
  {$EXTERNALSYM _TAG_TYPE}
  TAG_TYPE = _TAG_TYPE;
  {$EXTERNALSYM TAG_TYPE}
  TTagType = TAG_TYPE;
  PTagType = PTAG_TYPE;

type
  NS_DLL_INIT_FN = function (dwNetshVersion: DWORD; pReserved: PVOID): DWORD; stdcall;
  {$EXTERNALSYM NS_DLL_INIT_FN}
  PNS_DLL_INIT_FN = ^NS_DLL_INIT_FN;
  {$EXTERNALSYM PNS_DLL_INIT_FN}
  TNdDllInitFn = NS_DLL_INIT_FN;
  PNdDllInitFn = PNS_DLL_INIT_FN;

// Exports

function GetHostMachineInfo(var puiCIMOSType, puiCIMOSProductSuite: UINT; pszCIMOSVersion, pszCIMOSBuildNumber,
  pszCIMServicePackMajorVersion, pszCIMServicePackMinorVersion: LPWSTR; var puiCIMProcessorArchitecture: UINT): DWORD; stdcall;
{$EXTERNALSYM GetHostMachineInfo}
function MatchEnumTag(hModule: HANDLE; pwcArg: LPCWSTR; dwNumArg: DWORD; pEnumTable: PTOKEN_VALUE; pdwValue: PDWORD): DWORD; stdcall;
{$EXTERNALSYM MatchEnumTag}
function MatchToken(pwszUserToken, pwszCmdToken: LPCWSTR): BOOL; stdcall;
{$EXTERNALSYM MatchToken}
function PreprocessCommand(hModule: HANDLE; var ppwcArguments: LPWSTR; dwCurrentIndex, dwArgCount: DWORD; pttTags: PTAG_TYPE;
  dwTagCount, dwMinArgs, dwMaxArgs: DWORD; var pdwTagType: DWORD): DWORD; stdcall;
{$EXTERNALSYM PreprocessCommand}

(* TODO
DWORD PrintError(
    IN  HANDLE  hModule, OPTIONAL
    IN  DWORD   dwErrId,
    ...
    );

DWORD PrintMessageFromModule(
    IN  HANDLE  hModule,
    IN  DWORD   dwMsgId,
    ...
    );

DWORD PrintMessage(
    IN  LPCWSTR  pwszFormat,
    ...
    );
*)

function RegisterContext(pChildContext: PNS_CONTEXT_ATTRIBUTES): DWORD; stdcall;
{$EXTERNALSYM RegisterContext}
function RegisterHelper(const pguidParentContext: TGUID; pfnRegisterSubContext: PNS_HELPER_ATTRIBUTES): DWORD; stdcall;
{$EXTERNALSYM RegisterHelper}

implementation

const
  netsh = 'netsh.exe'; 


{$IFDEF DYNAMIC_LINK}
var
  _GetHostMachineInfo: Pointer;

function GetHostMachineInfo;
begin
  GetProcedureAddress(_GetHostMachineInfo, netsh, 'GetHostMachineInfo');
  asm
    mov esp, ebp
    pop ebp
    jmp [_GetHostMachineInfo]
  end;
end;
{$ELSE}
function GetHostMachineInfo; external netsh name 'GetHostMachineInfo';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _MatchEnumTag: Pointer;

function MatchEnumTag;
begin
  GetProcedureAddress(_MatchEnumTag, netsh, 'MatchEnumTag');
  asm
    mov esp, ebp
    pop ebp
    jmp [_MatchEnumTag]
  end;
end;
{$ELSE}
function MatchEnumTag; external netsh name 'MatchEnumTag';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _MatchToken: Pointer;

function MatchToken;
begin
  GetProcedureAddress(_MatchToken, netsh, 'MatchToken');
  asm
    mov esp, ebp
    pop ebp
    jmp [_MatchToken]
  end;
end;
{$ELSE}
function MatchToken; external netsh name 'MatchToken';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _PreprocessCommand: Pointer;

function PreprocessCommand;
begin
  GetProcedureAddress(_PreprocessCommand, netsh, 'PreprocessCommand');
  asm
    mov esp, ebp
    pop ebp
    jmp [_PreprocessCommand]
  end;
end;
{$ELSE}
function PreprocessCommand; external netsh name 'PreprocessCommand';
{$ENDIF DYNAMIC_LINK}


{$IFDEF DYNAMIC_LINK}
var
  _RegisterContext: Pointer;

function RegisterContext;
begin
  GetProcedureAddress(_RegisterContext, netsh, 'RegisterContext');
  asm
    mov esp, ebp
    pop ebp
    jmp [_RegisterContext]
  end;
end;
{$ELSE}
function RegisterContext; external netsh name 'RegisterContext';
{$ENDIF DYNAMIC_LINK}


{$IFDEF DYNAMIC_LINK}
var
  _RegisterHelper: Pointer;

function RegisterHelper;
begin
  GetProcedureAddress(_RegisterHelper, netsh, 'RegisterHelper');
  asm
    mov esp, ebp
    pop ebp
    jmp [_RegisterHelper]
  end;
end;
{$ELSE}
function RegisterHelper; external netsh name 'RegisterHelper';
{$ENDIF DYNAMIC_LINK}

end.
