{******************************************************************************}
{                                                       	               }
{ Windows Registry API interface Unit for Object Pascal                        }
{                                                       	               }
{ Portions created by Microsoft are Copyright (C) 1995-2001 Microsoft          }
{ Corporation. All Rights Reserved.                                            }
{ 								               }
{ The original file is: winreg.h, released June 2000. The original Pascal      }
{ code is: WinReg.pas, released December 2000. The initial developer of the    }
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

unit JwaWinReg;

{$WEAKPACKAGEUNIT}

{$HPPEMIT ''}
{$HPPEMIT '#include "WinReg.h"'}
{$HPPEMIT ''}

{$I WINDEFINES.INC}

interface

uses
  JwaReason, JwaWinBase, JwaWinNT, JwaWinType;

//
// Requested Key access mask type.
//

type
  REGSAM = ACCESS_MASK;
  {$EXTERNALSYM REGSAM}

//
// Reserved Key Handles.
//

const
  HKEY_CLASSES_ROOT     = HKEY(ULONG_PTR(LONG($80000000)));
  {$EXTERNALSYM HKEY_CLASSES_ROOT}
  HKEY_CURRENT_USER     = HKEY(ULONG_PTR(LONG($80000001)));
  {$EXTERNALSYM HKEY_CURRENT_USER}
  HKEY_LOCAL_MACHINE    = HKEY(ULONG_PTR(LONG($80000002)));
  {$EXTERNALSYM HKEY_LOCAL_MACHINE}
  HKEY_USERS            = HKEY(ULONG_PTR(LONG($80000003)));
  {$EXTERNALSYM HKEY_USERS}
  HKEY_PERFORMANCE_DATA = HKEY(ULONG_PTR(LONG($80000004)));
  {$EXTERNALSYM HKEY_PERFORMANCE_DATA}
  HKEY_PERFORMANCE_TEXT    = HKEY(ULONG_PTR(LONG($80000050)));
  {$EXTERNALSYM HKEY_PERFORMANCE_TEXT}
  HKEY_PERFORMANCE_NLSTEXT = HKEY(ULONG_PTR(LONG($80000060)));
  {$EXTERNALSYM HKEY_PERFORMANCE_NLSTEXT}
  HKEY_CURRENT_CONFIG   = HKEY(ULONG_PTR(LONG($80000005)));
  {$EXTERNALSYM HKEY_CURRENT_CONFIG}
  HKEY_DYN_DATA         = HKEY(ULONG_PTR(LONG($80000006)));
  {$EXTERNALSYM HKEY_DYN_DATA}

  PROVIDER_KEEPS_VALUE_LENGTH = $1;
  {$EXTERNALSYM PROVIDER_KEEPS_VALUE_LENGTH}

type
  val_context = record
    valuelen: Integer;       // the total length of this value
    value_context: LPVOID;   // provider's context
    val_buff_ptr: LPVOID;    // where in the ouput buffer the value is.
  end;
  {$EXTERNALSYM val_context}
  PVALCONTEXT = ^val_context;
  {$EXTERNALSYM PVALCONTEXT}
  TValContext = val_context;

  PVALUEA = record           // Provider supplied value/context.
    pv_valuename: LPSTR;     // The value name pointer
    pv_valuelen: Integer;
    pv_value_context: LPVOID;
    pv_type: DWORD;
  end;
  {$EXTERNALSYM PVALUEA}
  PPVALUEA = ^PVALUEA;
  {$EXTERNALSYM PPVALUEA}
  TPValueA = PVALUEA;

  PVALUEW = record           // Provider supplied value/context.
    pv_valuename: LPWSTR;    // The value name pointer
    pv_valuelen: Integer;
    pv_value_context: LPVOID;
    pv_type: DWORD;
  end;
  {$EXTERNALSYM PVALUEW}
  PPVALUEW = ^PVALUEW;
  {$EXTERNALSYM PPVALUEW}
  TPValueW = PVALUEW;

{$IFDEF UNICODE}
  PVALUE = PVALUEW;
  {$EXTERNALSYM PVALUE}
  PPVALUE = PPVALUEW;
  {$EXTERNALSYM PPVALUE}
  TPValue = TPValueW;
{$ELSE}
  PVALUE = PVALUEA;
  {$EXTERNALSYM PVALUE}
  PPVALUE = PPVALUEA;
  {$EXTERNALSYM PPVALUE}
  TPValue = TPValueA;
{$ENDIF}

  QUERYHANDLER = function (keycontext: LPVOID; val_list: PVALCONTEXT;
    num_vals: DWORD; outputbuffer: LPVOID; total_outlen: LPDWORD;
    input_blen: DWORD): DWORD; cdecl;
  {$EXTERNALSYM QUERYHANDLER}
  PQUERYHANDLER = ^QUERYHANDLER;
  {$EXTERNALSYM PQUERYHANDLER}
  TQueryHandler = QUERYHANDLER;

  provider_info = record
    pi_R0_1val: PQUERYHANDLER;
    pi_R0_allvals: PQUERYHANDLER;
    pi_R3_1val: PQUERYHANDLER;
    pi_R3_allvals: PQUERYHANDLER;
    pi_flags: DWORD;    // capability flags (none defined yet).
    pi_key_context: LPVOID;
  end;
  {$EXTERNALSYM provider_info}
  REG_PROVIDER = provider_info;
  {$EXTERNALSYM REG_PROVIDER}
  PPROVIDER = ^provider_info;
  {$EXTERNALSYM PPROVIDER}
  TProviderInfo = provider_info;
  PProviderInfo = ^provider_info;

  value_entA = record
    ve_valuename: LPSTR;
    ve_valuelen: DWORD;
    ve_valueptr: DWORD_PTR;
    ve_type: DWORD;
  end;
  {$EXTERNALSYM value_entA}
  VALENTA = value_entA;
  {$EXTERNALSYM VALENTA}
  PVALENTA = ^VALENTA;
  {$EXTERNALSYM PVALENTA}
  TValueEntA = value_entA;
  PValueEntA = ^value_entA;

  value_entW = record
    ve_valuename: LPWSTR;
    ve_valuelen: DWORD;
    ve_valueptr: DWORD_PTR;
    ve_type: DWORD;
  end;
  {$EXTERNALSYM value_entW}
  VALENTW = value_entW;
  {$EXTERNALSYM VALENTW}
  PVALENTW = ^VALENTW;
  {$EXTERNALSYM PVALENTW}
  TValueEntW = value_entW;
  PValueEntW = ^value_entW;

{$IFDEF UNICODE}
  VALENT = VALENTW;
  {$EXTERNALSYM VALENT}
  PVALENT = PVALENTW;
  {$EXTERNALSYM PVALENT}
  TValueEnt = TValueEntW;
  PValueEnt = PValueEntW;
{$ELSE}
  VALENT = VALENTA;
  {$EXTERNALSYM VALENT}
  PVALENT = PVALENTA;
  {$EXTERNALSYM PVALENT}
  TValueEnt = TValueEntA;
  PValueEnt = PValueEntA;
{$ENDIF}

//
// Default values for parameters that do not exist in the Win 3.1
// compatible APIs.
//

const
  WIN31_CLASS = nil;
  {$EXTERNALSYM WIN31_CLASS}

//
// API Prototypes.
//

function RegCloseKey(hKey: HKEY): LONG; stdcall;
{$EXTERNALSYM RegCloseKey}

function RegOverridePredefKey(hKey: HKEY; hNewHKey: HKEY): LONG; stdcall;
{$EXTERNALSYM RegOverridePredefKey}

function RegOpenUserClassesRoot(hToken: HANDLE; dwOptions: DWORD;
  samDesired: REGSAM; var phkResult: HKEY): LONG; stdcall;
{$EXTERNALSYM RegOpenUserClassesRoot}

function RegOpenCurrentUser(samDesired: REGSAM; var phkResult: HKEY): LONG; stdcall;
{$EXTERNALSYM RegOpenCurrentUser}

function RegDisablePredefinedCache: LONG; stdcall;
{$EXTERNALSYM RegDisablePredefinedCache}

function RegConnectRegistryA(lpMachineName: LPCSTR; hKey: HKEY;
  var phkResult: HKEY): LONG; stdcall;
{$EXTERNALSYM RegConnectRegistryA}
function RegConnectRegistryW(lpMachineName: LPCWSTR; hKey: HKEY;
  var phkResult: HKEY): LONG; stdcall;
{$EXTERNALSYM RegConnectRegistryW}

{$IFDEF UNICODE}
function RegConnectRegistry(lpMachineName: LPCWSTR; hKey: HKEY;
  var phkResult: HKEY): LONG; stdcall;
{$EXTERNALSYM RegConnectRegistry}
{$ELSE}
function RegConnectRegistry(lpMachineName: LPCSTR; hKey: HKEY;
  var phkResult: HKEY): LONG; stdcall;
{$EXTERNALSYM RegConnectRegistry}
{$ENDIF}

function RegCreateKeyA(hKey: HKEY; lpSubKey: LPCSTR; var phkResult: HKEY): LONG; stdcall;
{$EXTERNALSYM RegCreateKeyA}
function RegCreateKeyW(hKey: HKEY; lpSubKey: LPCWSTR; var phkResult: HKEY): LONG; stdcall;
{$EXTERNALSYM RegCreateKeyW}

{$IFDEF UNICODE}
function RegCreateKey(hKey: HKEY; lpSubKey: LPCWSTR; var phkResult: HKEY): LONG; stdcall;
{$EXTERNALSYM RegCreateKey}
{$ELSE}
function RegCreateKey(hKey: HKEY; lpSubKey: LPCSTR; var phkResult: HKEY): LONG; stdcall;
{$EXTERNALSYM RegCreateKey}
{$ENDIF}

function RegCreateKeyExA(hKey: HKEY; lpSubKey: LPCSTR; Reserved: DWORD;
  lpClass: LPSTR; dwOptions: DWORD; samDesired: REGSAM;
  lpSecurityAttributes: LPSECURITY_ATTRIBUTES; var phkResult: HKEY;
  lpdwDisposition: LPDWORD): LONG; stdcall;
{$EXTERNALSYM RegCreateKeyExA}
function RegCreateKeyExW(hKey: HKEY; lpSubKey: LPCWSTR; Reserved: DWORD;
  lpClass: LPWSTR; dwOptions: DWORD; samDesired: REGSAM;
  lpSecurityAttributes: LPSECURITY_ATTRIBUTES; var phkResult: HKEY;
  lpdwDisposition: LPDWORD): LONG; stdcall;
{$EXTERNALSYM RegCreateKeyExW}

{$IFDEF UNICODE}
function RegCreateKeyEx(hKey: HKEY; lpSubKey: LPCWSTR; Reserved: DWORD;
  lpClass: LPWSTR; dwOptions: DWORD; samDesired: REGSAM;
  lpSecurityAttributes: LPSECURITY_ATTRIBUTES; var phkResult: HKEY;
  lpdwDisposition: LPDWORD): LONG; stdcall;
{$EXTERNALSYM RegCreateKeyEx}
{$ELSE}
function RegCreateKeyEx(hKey: HKEY; lpSubKey: LPCSTR; Reserved: DWORD;
  lpClass: LPSTR; dwOptions: DWORD; samDesired: REGSAM;
  lpSecurityAttributes: LPSECURITY_ATTRIBUTES; var phkResult: HKEY;
  lpdwDisposition: LPDWORD): LONG; stdcall;
{$EXTERNALSYM RegCreateKeyEx}
{$ENDIF}

function RegDeleteKeyA(hKey: HKEY; lpSubKey: LPCSTR): LONG; stdcall;
{$EXTERNALSYM RegDeleteKeyA}
function RegDeleteKeyW(hKey: HKEY; lpSubKey: LPCWSTR): LONG; stdcall;
{$EXTERNALSYM RegDeleteKeyW}

{$IFDEF UNICODE}
function RegDeleteKey(hKey: HKEY; lpSubKey: LPCWSTR): LONG; stdcall;
{$EXTERNALSYM RegDeleteKey}
{$ELSE}
function RegDeleteKey(hKey: HKEY; lpSubKey: LPCSTR): LONG; stdcall;
{$EXTERNALSYM RegDeleteKey}
{$ENDIF}

function RegDeleteValueA(hKey: HKEY; lpValueName: LPCSTR): LONG; stdcall;
{$EXTERNALSYM RegDeleteValueA}
function RegDeleteValueW(hKey: HKEY; lpValueName: LPCWSTR): LONG; stdcall;
{$EXTERNALSYM RegDeleteValueW}

{$IFDEF UNICODE}
function RegDeleteValue(hKey: HKEY; lpValueName: LPCWSTR): LONG; stdcall;
{$EXTERNALSYM RegDeleteValue}
{$ELSE}
function RegDeleteValue(hKey: HKEY; lpValueName: LPCSTR): LONG; stdcall;
{$EXTERNALSYM RegDeleteValue}
{$ENDIF}

function RegEnumKeyA(hKey: HKEY; dwIndex: DWORD; lpName: LPSTR; cbName: DWORD): LONG; stdcall;
{$EXTERNALSYM RegEnumKeyA}
function RegEnumKeyW(hKey: HKEY; dwIndex: DWORD; lpName: LPWSTR; cbName: DWORD): LONG; stdcall;
{$EXTERNALSYM RegEnumKeyW}

{$IFDEF UNICODE}
function RegEnumKey(hKey: HKEY; dwIndex: DWORD; lpName: LPWSTR; cbName: DWORD): LONG; stdcall;
{$EXTERNALSYM RegEnumKey}
{$ELSE}
function RegEnumKey(hKey: HKEY; dwIndex: DWORD; lpName: LPSTR; cbName: DWORD): LONG; stdcall;
{$EXTERNALSYM RegEnumKey}
{$ENDIF}

function RegEnumKeyExA(hKey: HKEY; dwIndex: DWORD; lpName: LPSTR;
  var lpcbName: DWORD; lpReserved: LPDWORD; lpClass: LPSTR; lpcbClass: LPDWORD;
  lpftLastWriteTime: PFILETIME): LONG; stdcall;
{$EXTERNALSYM RegEnumKeyExA}
function RegEnumKeyExW(hKey: HKEY; dwIndex: DWORD; lpName: LPWSTR;
  var lpcbName: DWORD; lpReserved: LPDWORD; lpClass: LPWSTR; lpcbClass: LPDWORD;
  lpftLastWriteTime: PFILETIME): LONG; stdcall;
{$EXTERNALSYM RegEnumKeyExW}

{$IFDEF UNICODE}
function RegEnumKeyEx(hKey: HKEY; dwIndex: DWORD; lpName: LPWSTR;
  var lpcbName: LPDWORD; lpReserved: LPDWORD; lpClass: LPWSTR; lpcbClass: LPDWORD;
  lpftLastWriteTime: PFILETIME): LONG; stdcall;
{$EXTERNALSYM RegEnumKeyEx}
{$ELSE}
function RegEnumKeyEx(hKey: HKEY; dwIndex: DWORD; lpName: LPSTR;
  var lpcbName: DWORD; lpReserved: LPDWORD; lpClass: LPSTR; lpcbClass: LPDWORD;
  lpftLastWriteTime: PFILETIME): LONG; stdcall;
{$EXTERNALSYM RegEnumKeyEx}
{$ENDIF}

function RegEnumValueA(hKey: HKEY; dwIndex: DWORD; lpValueName: LPSTR;
  var lpcbValueName: DWORD; lpReserved, lpType: LPDWORD; lpData: LPBYTE;
  lpcbData: LPDWORD): LONG; stdcall;
{$EXTERNALSYM RegEnumValueA}
function RegEnumValueW(hKey: HKEY; dwIndex: DWORD; lpValueName: LPWSTR;
  var lpcbValueName: DWORD; lpReserved, lpType: LPDWORD; lpData: LPBYTE;
  lpcbData: LPDWORD): LONG; stdcall;
{$EXTERNALSYM RegEnumValueW}

{$IFDEF UNICODE}
function RegEnumValue(hKey: HKEY; dwIndex: DWORD; lpValueName: LPWSTR;
  var lpcbValueName: DWORD; lpReserved, lpType: LPDWORD; lpData: LPBYTE;
  lpcbData: LPDWORD): LONG; stdcall;
{$EXTERNALSYM RegEnumValue}
{$ELSE}
function RegEnumValue(hKey: HKEY; dwIndex: DWORD; lpValueName: LPSTR;
  var lpcbValueName: DWORD; lpReserved, lpType: LPDWORD; lpData: LPBYTE;
  lpcbData: LPDWORD): LONG; stdcall;
{$EXTERNALSYM RegEnumValue}
{$ENDIF}

function RegFlushKey(hKey: HKEY): LONG; stdcall;
{$EXTERNALSYM RegFlushKey}

function RegGetKeySecurity(hKey: HKEY; SecurityInformation: SECURITY_INFORMATION;
  pSecurityDescriptor: PSECURITY_DESCRIPTOR; var lpcbSecurityDescriptor: DWORD): LONG; stdcall;
{$EXTERNALSYM RegGetKeySecurity}

function RegLoadKeyA(hKey: HKEY; lpSubKey: LPCSTR; lpFile: LPCSTR): LONG; stdcall;
{$EXTERNALSYM RegLoadKeyA}
function RegLoadKeyW(hKey: HKEY; lpSubKey: LPCWSTR; lpFile: LPCWSTR): LONG; stdcall;
{$EXTERNALSYM RegLoadKeyW}

{$IFDEF UNICODE}
function RegLoadKey(hKey: HKEY; lpSubKey: LPCWSTR; lpFile: LPCWSTR): LONG; stdcall;
{$EXTERNALSYM RegLoadKey}
{$ELSE}
function RegLoadKey(hKey: HKEY; lpSubKey: LPCSTR; lpFile: LPCSTR): LONG; stdcall;
{$EXTERNALSYM RegLoadKey}
{$ENDIF}

function RegNotifyChangeKeyValue(hKey: HKEY; bWatchSubtree: BOOL;
  dwNotifyFilter: DWORD; hEvent: HANDLE; fAsynchronus: BOOL): LONG;
{$EXTERNALSYM RegNotifyChangeKeyValue}

function RegOpenKeyA(hKey: HKEY; lpSubKey: LPCSTR; var phkResult: HKEY): LONG; stdcall;
{$EXTERNALSYM RegOpenKeyA}
function RegOpenKeyW(hKey: HKEY; lpSubKey: LPCWSTR; var phkResult: HKEY): LONG; stdcall;
{$EXTERNALSYM RegOpenKeyW}

{$IFDEF UNICODE}
function RegOpenKey(hKey: HKEY; lpSubKey: LPCWSTR; var phkResult: HKEY): LONG; stdcall;
{$EXTERNALSYM RegOpenKey}
{$ELSE}
function RegOpenKey(hKey: HKEY; lpSubKey: LPCSTR; var phkResult: HKEY): LONG; stdcall;
{$EXTERNALSYM RegOpenKey}
{$ENDIF}

function RegOpenKeyExA(hKey: HKEY; lpSubKey: LPCSTR; ulOptions: DWORD;
  samDesired: REGSAM; var phkResult: HKEY): LONG; stdcall;
{$EXTERNALSYM RegOpenKeyExA}
function RegOpenKeyExW(hKey: HKEY; lpSubKey: LPCWSTR; ulOptions: DWORD;
  samDesired: REGSAM; var phkResult: HKEY): LONG; stdcall;
{$EXTERNALSYM RegOpenKeyExW}

{$IFDEF UNICODE}
function RegOpenKeyEx(hKey: HKEY; lpSubKey: LPCWSTR; ulOptions: DWORD;
  samDesired: REGSAM; var phkResult: HKEY): LONG; stdcall;
{$EXTERNALSYM RegOpenKeyEx}
{$ELSE}
function RegOpenKeyEx(hKey: HKEY; lpSubKey: LPCSTR; ulOptions: DWORD;
  samDesired: REGSAM; var phkResult: HKEY): LONG; stdcall;
{$EXTERNALSYM RegOpenKeyEx}
{$ENDIF}

function RegQueryInfoKeyA(hKey: HKEY; lpClass: LPSTR; lpcbClass, lpReserved,
  lpcSubKeys, lpcbMaxSubKeyLen, lpcbMaxClassLen, lpcValues, lpcbMaxValueNameLen,
  lpcbMaxValueLen, lpcbSecurityDescriptor: LPDWORD; lpftLastWriteTime: PFILETIME): LONG; stdcall;
{$EXTERNALSYM RegQueryInfoKeyA}
function RegQueryInfoKeyW(hKey: HKEY; lpClass: LPWSTR; lpcbClass, lpReserved,
  lpcSubKeys, lpcbMaxSubKeyLen, lpcbMaxClassLen, lpcValues, lpcbMaxValueNameLen,
  lpcbMaxValueLen, lpcbSecurityDescriptor: LPDWORD; lpftLastWriteTime: PFILETIME): LONG; stdcall;
{$EXTERNALSYM RegQueryInfoKeyW}

{$IFDEF UNICODE}
function RegQueryInfoKey(hKey: HKEY; lpClass: LPWSTR; lpcbClass, lpReserved,
  lpcSubKeys, lpcbMaxSubKeyLen, lpcbMaxClassLen, lpcValues, lpcbMaxValueNameLen,
  lpcbMaxValueLen, lpcbSecurityDescriptor: LPDWORD; lpftLastWriteTime: PFILETIME): LONG; stdcall;
{$EXTERNALSYM RegQueryInfoKey}
{$ELSE}
function RegQueryInfoKey(hKey: HKEY; lpClass: LPSTR; lpcbClass, lpReserved,
  lpcSubKeys, lpcbMaxSubKeyLen, lpcbMaxClassLen, lpcValues, lpcbMaxValueNameLen,
  lpcbMaxValueLen, lpcbSecurityDescriptor: LPDWORD; lpftLastWriteTime: PFILETIME): LONG; stdcall;
{$EXTERNALSYM RegQueryInfoKey}
{$ENDIF}

function RegQueryValueA(hKey: HKEY; lpSubKey: LPCSTR; lpValue: LPSTR;
  var lpcbValue: LONG): LONG; stdcall;
{$EXTERNALSYM RegQueryValueA}
function RegQueryValueW(hKey: HKEY; lpSubKey: LPCWSTR; lpValue: LPWSTR;
  var lpcbValue: LONG): LONG; stdcall;
{$EXTERNALSYM RegQueryValueW}

{$IFDEF UNICODE}
function RegQueryValue(hKey: HKEY; lpSubKey: LPCWSTR; lpValue: LPWSTR;
  var lpcbValue: LONG): LONG; stdcall;
{$EXTERNALSYM RegQueryValue}
{$ELSE}
function RegQueryValue(hKey: HKEY; lpSubKey: LPCSTR; lpValue: LPSTR;
  var lpcbValue: LONG): LONG; stdcall;
{$EXTERNALSYM RegQueryValue}
{$ENDIF}

function RegQueryMultipleValuesA(hKey: HKEY; val_list: PVALENTA; num_vals: DWORD;
  lpValueBuf: LPSTR; var ldwTotsize: DWORD): LONG; stdcall;
{$EXTERNALSYM RegQueryMultipleValuesA}
function RegQueryMultipleValuesW(hKey: HKEY; val_list: PVALENTW; num_vals: DWORD;
  lpValueBuf: LPWSTR; var ldwTotsize: DWORD): LONG; stdcall;
{$EXTERNALSYM RegQueryMultipleValuesW}

{$IFDEF UNICODE}
function RegQueryMultipleValues(hKey: HKEY; val_list: PVALENTW; num_vals: DWORD;
  lpValueBuf: LPWSTR; var ldwTotsize: DWORD): LONG; stdcall;
{$EXTERNALSYM RegQueryMultipleValues}
{$ELSE}
function RegQueryMultipleValues(hKey: HKEY; val_list: PVALENTA; num_vals: DWORD;
  lpValueBuf: LPSTR; var ldwTotsize: DWORD): LONG; stdcall;
{$EXTERNALSYM RegQueryMultipleValues}
{$ENDIF}

function RegQueryValueExA(hKey: HKEY; lpValueName: LPCSTR; lpReserved: LPDWORD;
  lpType: LPDWORD; lpData: LPBYTE; lpcbData: LPDWORD): LONG; stdcall;
{$EXTERNALSYM RegQueryValueExA}
function RegQueryValueExW(hKey: HKEY; lpValueName: LPCWSTR; lpReserved: LPDWORD;
  lpType: LPDWORD; lpData: LPBYTE; lpcbData: LPDWORD): LONG; stdcall;
{$EXTERNALSYM RegQueryValueExW}

{$IFDEF UNICODE}
function RegQueryValueEx(hKey: HKEY; lpValueName: LPCWSTR; lpReserved: LPDWORD;
  lpType: LPDWORD; lpData: LPBYTE; lpcbData: LPDWORD): LONG; stdcall;
{$EXTERNALSYM RegQueryValueEx}
{$ELSE}
function RegQueryValueEx(hKey: HKEY; lpValueName: LPCSTR; lpReserved: LPDWORD;
  lpType: LPDWORD; lpData: LPBYTE; lpcbData: LPDWORD): LONG; stdcall;
{$EXTERNALSYM RegQueryValueEx}
{$ENDIF}

function RegReplaceKeyA(hKey: HKEY; lpSubKey: LPCSTR; lpNewFile: LPCSTR;
  lpOldFile: LPCSTR): LONG; stdcall;
{$EXTERNALSYM RegReplaceKeyA}
function RegReplaceKeyW(hKey: HKEY; lpSubKey: LPCWSTR; lpNewFile: LPCWSTR;
  lpOldFile: LPCWSTR): LONG; stdcall;
{$EXTERNALSYM RegReplaceKeyW}

{$IFDEF UNICODE}
function RegReplaceKey(hKey: HKEY; lpSubKey: LPCWSTR; lpNewFile: LPCWSTR;
  lpOldFile: LPCWSTR): LONG; stdcall;
{$EXTERNALSYM RegReplaceKey}
{$ELSE}
function RegReplaceKey(hKey: HKEY; lpSubKey: LPCSTR; lpNewFile: LPCSTR;
  lpOldFile: LPCSTR): LONG; stdcall;
{$EXTERNALSYM RegReplaceKey}
{$ENDIF}

function RegRestoreKeyA(hKey: HKEY; lpFile: LPCSTR; dwFlags: DWORD): LONG; stdcall;
{$EXTERNALSYM RegRestoreKeyA}
function RegRestoreKeyW(hKey: HKEY; lpFile: LPCWSTR; dwFlags: DWORD): LONG; stdcall;
{$EXTERNALSYM RegRestoreKeyW}

{$IFDEF UNICODE}
function RegRestoreKey(hKey: HKEY; lpFile: LPCWSTR; dwFlags: DWORD): LONG; stdcall;
{$EXTERNALSYM RegRestoreKey}
{$ELSE}
function RegRestoreKey(hKey: HKEY; lpFile: LPCSTR; dwFlags: DWORD): LONG; stdcall;
{$EXTERNALSYM RegRestoreKey}
{$ENDIF}

function RegSaveKeyA(hKey: HKEY; lpFile: LPCSTR;
  lpSecurityAttributes: LPSECURITY_ATTRIBUTES): LONG; stdcall;
{$EXTERNALSYM RegSaveKeyA}
function RegSaveKeyW(hKey: HKEY; lpFile: LPCWSTR;
  lpSecurityAttributes: LPSECURITY_ATTRIBUTES): LONG; stdcall;
{$EXTERNALSYM RegSaveKeyW}

{$IFDEF UNICODE}
function RegSaveKey(hKey: HKEY; lpFile: LPCWSTR;
  lpSecurityAttributes: LPSECURITY_ATTRIBUTES): LONG; stdcall;
{$EXTERNALSYM RegSaveKey}
{$ELSE}
function RegSaveKey(hKey: HKEY; lpFile: LPCSTR;
  lpSecurityAttributes: LPSECURITY_ATTRIBUTES): LONG; stdcall;
{$EXTERNALSYM RegSaveKey}
{$ENDIF}

function RegSetKeySecurity(hKey: HKEY; SecurityInformation: SECURITY_INFORMATION;
  pSecurityDescriptor: PSECURITY_DESCRIPTOR): LONG; stdcall;
{$EXTERNALSYM RegSetKeySecurity}

function RegSetValueA(hKey: HKEY; lpSubKey: LPCSTR; dwType: DWORD;
  lpData: LPCSTR; cbData: DWORD): LONG; stdcall;
{$EXTERNALSYM RegSetValueA}
function RegSetValueW(hKey: HKEY; lpSubKey: LPCWSTR; dwType: DWORD;
  lpData: LPCWSTR; cbData: DWORD): LONG; stdcall;
{$EXTERNALSYM RegSetValueW}

{$IFDEF UNICODE}
function RegSetValue(hKey: HKEY; lpSubKey: LPCWSTR; dwType: DWORD;
  lpData: LPCWSTR; cbData: DWORD): LONG; stdcall;
{$EXTERNALSYM RegSetValue}
{$ELSE}
function RegSetValue(hKey: HKEY; lpSubKey: LPCSTR; dwType: DWORD;
  lpData: LPCSTR; cbData: DWORD): LONG; stdcall;
{$EXTERNALSYM RegSetValue}
{$ENDIF}

function RegSetValueExA(hKey: HKEY; lpValueName: LPCSTR; Reserved: DWORD;
  dwType: DWORD; lpData: LPBYTE; cbData: DWORD): LONG; stdcall;
{$EXTERNALSYM RegSetValueExA}
function RegSetValueExW(hKey: HKEY; lpValueName: LPCWSTR; Reserved: DWORD;
  dwType: DWORD; lpData: LPBYTE; cbData: DWORD): LONG; stdcall;
{$EXTERNALSYM RegSetValueExW}

{$IFDEF UNICODE}
function RegSetValueEx(hKey: HKEY; lpValueName: LPCWSTR; Reserved: DWORD;
  dwType: DWORD; lpData: LPBYTE; cbData: DWORD): LONG; stdcall;
{$EXTERNALSYM RegSetValueEx}
{$ELSE}
function RegSetValueEx(hKey: HKEY; lpValueName: LPCSTR; Reserved: DWORD;
  dwType: DWORD; lpData: LPBYTE; cbData: DWORD): LONG; stdcall;
{$EXTERNALSYM RegSetValueEx}
{$ENDIF}

function RegUnLoadKeyA(hKey: HKEY; lpSubKey: LPCSTR): LONG; stdcall;
{$EXTERNALSYM RegUnLoadKeyA}
function RegUnLoadKeyW(hKey: HKEY; lpSubKey: LPCWSTR): LONG; stdcall;
{$EXTERNALSYM RegUnLoadKeyW}

{$IFDEF UNICODE}
function RegUnLoadKey(hKey: HKEY; lpSubKey: LPCWSTR): LONG; stdcall;
{$EXTERNALSYM RegUnLoadKey}
{$ELSE}
function RegUnLoadKey(hKey: HKEY; lpSubKey: LPCSTR): LONG; stdcall;
{$EXTERNALSYM RegUnLoadKey}
{$ENDIF}

//
// Remoteable System Shutdown APIs
//

function InitiateSystemShutdownA(lpMachineName: LPSTR; lpMessage: LPSTR;
  dwTimeout: DWORD; bForceAppsClosed, bRebootAfterShutdown: BOOL): BOOL; stdcall;
{$EXTERNALSYM InitiateSystemShutdownA}
function InitiateSystemShutdownW(lpMachineName: LPWSTR; lpMessage: LPWSTR;
  dwTimeout: DWORD; bForceAppsClosed, bRebootAfterShutdown: BOOL): BOOL; stdcall;
{$EXTERNALSYM InitiateSystemShutdownW}

{$IFDEF UNICODE}
function InitiateSystemShutdown(lpMachineName: LPWSTR; lpMessage: LPWSTR;
  dwTimeout: DWORD; bForceAppsClosed, bRebootAfterShutdown: BOOL): BOOL; stdcall;
{$EXTERNALSYM InitiateSystemShutdown}
{$ELSE}
function InitiateSystemShutdown(lpMachineName: LPSTR; lpMessage: LPSTR;
  dwTimeout: DWORD; bForceAppsClosed, bRebootAfterShutdown: BOOL): BOOL; stdcall;
{$EXTERNALSYM InitiateSystemShutdown}
{$ENDIF}

function AbortSystemShutdownA(lpMachineName: LPSTR): BOOL; stdcall;
{$EXTERNALSYM AbortSystemShutdownA}
function AbortSystemShutdownW(lpMachineName: LPWSTR): BOOL; stdcall;
{$EXTERNALSYM AbortSystemShutdownW}

{$IFDEF UNICODE}
function AbortSystemShutdown(lpMachineName: LPWSTR): BOOL; stdcall;
{$EXTERNALSYM AbortSystemShutdown}
{$ELSE}
function AbortSystemShutdown(lpMachineName: LPSTR): BOOL; stdcall;
{$EXTERNALSYM AbortSystemShutdown}
{$ENDIF}

//
// defines for InitiateSystemShutdownEx reason codes
//

const
  REASON_SWINSTALL    = SHTDN_REASON_MAJOR_SOFTWARE or SHTDN_REASON_MINOR_INSTALLATION;
  {$EXTERNALSYM REASON_SWINSTALL}
  REASON_HWINSTALL    = SHTDN_REASON_MAJOR_HARDWARE or SHTDN_REASON_MINOR_INSTALLATION;
  {$EXTERNALSYM REASON_HWINSTALL}
  REASON_SERVICEHANG  = SHTDN_REASON_MAJOR_SOFTWARE or SHTDN_REASON_MINOR_HUNG;
  {$EXTERNALSYM REASON_SERVICEHANG}
  REASON_UNSTABLE     = SHTDN_REASON_MAJOR_SYSTEM or SHTDN_REASON_MINOR_UNSTABLE;
  {$EXTERNALSYM REASON_UNSTABLE}
  REASON_SWHWRECONF   = SHTDN_REASON_MAJOR_SOFTWARE or SHTDN_REASON_MINOR_RECONFIG;
  {$EXTERNALSYM REASON_SWHWRECONF}
  REASON_OTHER        = SHTDN_REASON_MAJOR_OTHER or SHTDN_REASON_MINOR_OTHER;
  {$EXTERNALSYM REASON_OTHER}
  REASON_UNKNOWN      = SHTDN_REASON_UNKNOWN;
  {$EXTERNALSYM REASON_UNKNOWN}
  REASON_LEGACY_API   = SHTDN_REASON_LEGACY_API;
  {$EXTERNALSYM REASON_LEGACY_API}
  REASON_PLANNED_FLAG = SHTDN_REASON_FLAG_PLANNED;
  {$EXTERNALSYM REASON_PLANNED_FLAG}

//
// MAX Shutdown TimeOut == 10 Years in seconds
//

  MAX_SHUTDOWN_TIMEOUT = (10*365*24*60*60);
  {$EXTERNALSYM MAX_SHUTDOWN_TIMEOUT}

function InitiateSystemShutdownExA(lpMachineName: LPSTR; lpMessage: LPSTR;
  dwTimeout: DWORD; bForceAppsClosed, bRebootAfterShutdown: BOOL; dwReason: DWORD): BOOL; stdcall;
{$EXTERNALSYM InitiateSystemShutdownExA}
function InitiateSystemShutdownExW(lpMachineName: LPWSTR; lpMessage: LPWSTR;
  dwTimeout: DWORD; bForceAppsClosed, bRebootAfterShutdown: BOOL; dwReason: DWORD): BOOL; stdcall;
{$EXTERNALSYM InitiateSystemShutdownExW}

{$IFDEF UNICODE}
function InitiateSystemShutdownEx(lpMachineName: LPWSTR; lpMessage: LPWSTR;
  dwTimeout: DWORD; bForceAppsClosed, bRebootAfterShutdown: BOOL; dwReason: DWORD): BOOL; stdcall;
{$EXTERNALSYM InitiateSystemShutdownEx}
{$ELSE}
function InitiateSystemShutdownEx(lpMachineName: LPSTR; lpMessage: LPSTR;
  dwTimeout: DWORD; bForceAppsClosed, bRebootAfterShutdown: BOOL; dwReason: DWORD): BOOL; stdcall;
{$EXTERNALSYM InitiateSystemShutdownEx}
{$ENDIF}

function RegSaveKeyExA(hKey: HKEY; lpFile: LPCSTR;
  lpSecurityAttributes: LPSECURITY_ATTRIBUTES; Flags: DWORD): LONG; stdcall;
{$EXTERNALSYM RegSaveKeyExA}
function RegSaveKeyExW(hKey: HKEY; lpFile: LPCWSTR;
  lpSecurityAttributes: LPSECURITY_ATTRIBUTES; Flags: DWORD): LONG; stdcall;
{$EXTERNALSYM RegSaveKeyExW}

{$IFDEF UNICODE}
function RegSaveKeyEx(hKey: HKEY; lpFile: LPCWSTR;
  lpSecurityAttributes: LPSECURITY_ATTRIBUTES; Flags: DWORD): LONG; stdcall;
{$EXTERNALSYM RegSaveKeyEx}
{$ELSE}
function RegSaveKeyEx(hKey: HKEY; lpFile: LPCSTR;
  lpSecurityAttributes: LPSECURITY_ATTRIBUTES; Flags: DWORD): LONG; stdcall;
{$EXTERNALSYM RegSaveKeyEx}
{$ENDIF}

function Wow64Win32ApiEntry(dwFuncNumber, dwFlag, dwRes: DWORD): LONG; stdcall;
{$EXTERNALSYM Wow64Win32ApiEntry}

implementation

const
  advapi32 = 'advapi32.dll';


{$IFDEF DYNAMIC_LINK}
var
  _RegCloseKey: Pointer;

function RegCloseKey;
begin
  GetProcedureAddress(_RegCloseKey, advapi32, 'RegCloseKey');
  asm
    mov esp, ebp
    pop ebp
    jmp [_RegCloseKey]
  end;
end;
{$ELSE}
function RegCloseKey; external advapi32 name 'RegCloseKey';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _RegOverridePredefKey: Pointer;

function RegOverridePredefKey;
begin
  GetProcedureAddress(_RegOverridePredefKey, advapi32, 'RegOverridePredefKey');
  asm
    mov esp, ebp
    pop ebp
    jmp [_RegOverridePredefKey]
  end;
end;
{$ELSE}
function RegOverridePredefKey; external advapi32 name 'RegOverridePredefKey';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _RegOpenUserClassesRoot: Pointer;

function RegOpenUserClassesRoot;
begin
  GetProcedureAddress(_RegOpenUserClassesRoot, advapi32, 'RegOpenUserClassesRoot');
  asm
    mov esp, ebp
    pop ebp
    jmp [_RegOpenUserClassesRoot]
  end;
end;
{$ELSE}
function RegOpenUserClassesRoot; external advapi32 name 'RegOpenUserClassesRoot';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _RegOpenCurrentUser: Pointer;

function RegOpenCurrentUser;
begin
  GetProcedureAddress(_RegOpenCurrentUser, advapi32, 'RegOpenCurrentUser');
  asm
    mov esp, ebp
    pop ebp
    jmp [_RegOpenCurrentUser]
  end;
end;
{$ELSE}
function RegOpenCurrentUser; external advapi32 name 'RegOpenCurrentUser';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _RegDisablePredefinedCache: Pointer;

function RegDisablePredefinedCache;
begin
  GetProcedureAddress(_RegDisablePredefinedCache, advapi32, 'RegDisablePredefinedCache');
  asm
    mov esp, ebp
    pop ebp
    jmp [_RegDisablePredefinedCache]
  end;
end;
{$ELSE}
function RegDisablePredefinedCache; external advapi32 name 'RegDisablePredefinedCache';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _RegConnectRegistryA: Pointer;

function RegConnectRegistryA;
begin
  GetProcedureAddress(_RegConnectRegistryA, advapi32, 'RegConnectRegistryA');
  asm
    mov esp, ebp
    pop ebp
    jmp [_RegConnectRegistryA]
  end;
end;
{$ELSE}
function RegConnectRegistryA; external advapi32 name 'RegConnectRegistryA';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _RegConnectRegistryW: Pointer;

function RegConnectRegistryW;
begin
  GetProcedureAddress(_RegConnectRegistryW, advapi32, 'RegConnectRegistryW');
  asm
    mov esp, ebp
    pop ebp
    jmp [_RegConnectRegistryW]
  end;
end;
{$ELSE}
function RegConnectRegistryW; external advapi32 name 'RegConnectRegistryW';
{$ENDIF DYNAMIC_LINK}
{$IFDEF UNICODE}

{$IFDEF DYNAMIC_LINK}
var
  _RegConnectRegistry: Pointer;

function RegConnectRegistry;
begin
  GetProcedureAddress(_RegConnectRegistry, advapi32, 'RegConnectRegistryW');
  asm
    mov esp, ebp
    pop ebp
    jmp [_RegConnectRegistry]
  end;
end;
{$ELSE}
function RegConnectRegistry; external advapi32 name 'RegConnectRegistryW';
{$ENDIF DYNAMIC_LINK}
{$ELSE}

{$IFDEF DYNAMIC_LINK}
var
  _RegConnectRegistry: Pointer;

function RegConnectRegistry;
begin
  GetProcedureAddress(_RegConnectRegistry, advapi32, 'RegConnectRegistryA');
  asm
    mov esp, ebp
    pop ebp
    jmp [_RegConnectRegistry]
  end;
end;
{$ELSE}
function RegConnectRegistry; external advapi32 name 'RegConnectRegistryA';
{$ENDIF DYNAMIC_LINK}
{$ENDIF}

{$IFDEF DYNAMIC_LINK}
var
  _RegCreateKeyA: Pointer;

function RegCreateKeyA;
begin
  GetProcedureAddress(_RegCreateKeyA, advapi32, 'RegCreateKeyA');
  asm
    mov esp, ebp
    pop ebp
    jmp [_RegCreateKeyA]
  end;
end;
{$ELSE}
function RegCreateKeyA; external advapi32 name 'RegCreateKeyA';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _RegCreateKeyW: Pointer;

function RegCreateKeyW;
begin
  GetProcedureAddress(_RegCreateKeyW, advapi32, 'RegCreateKeyW');
  asm
    mov esp, ebp
    pop ebp
    jmp [_RegCreateKeyW]
  end;
end;
{$ELSE}
function RegCreateKeyW; external advapi32 name 'RegCreateKeyW';
{$ENDIF DYNAMIC_LINK}
{$IFDEF UNICODE}

{$IFDEF DYNAMIC_LINK}
var
  _RegCreateKey: Pointer;

function RegCreateKey;
begin
  GetProcedureAddress(_RegCreateKey, advapi32, 'RegCreateKeyW');
  asm
    mov esp, ebp
    pop ebp
    jmp [_RegCreateKey]
  end;
end;
{$ELSE}
function RegCreateKey; external advapi32 name 'RegCreateKeyW';
{$ENDIF DYNAMIC_LINK}
{$ELSE}

{$IFDEF DYNAMIC_LINK}
var
  _RegCreateKey: Pointer;

function RegCreateKey;
begin
  GetProcedureAddress(_RegCreateKey, advapi32, 'RegCreateKeyA');
  asm
    mov esp, ebp
    pop ebp
    jmp [_RegCreateKey]
  end;
end;
{$ELSE}
function RegCreateKey; external advapi32 name 'RegCreateKeyA';
{$ENDIF DYNAMIC_LINK}
{$ENDIF}

{$IFDEF DYNAMIC_LINK}
var
  _RegCreateKeyExA: Pointer;

function RegCreateKeyExA;
begin
  GetProcedureAddress(_RegCreateKeyExA, advapi32, 'RegCreateKeyExA');
  asm
    mov esp, ebp
    pop ebp
    jmp [_RegCreateKeyExA]
  end;
end;
{$ELSE}
function RegCreateKeyExA; external advapi32 name 'RegCreateKeyExA';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _RegCreateKeyExW: Pointer;

function RegCreateKeyExW;
begin
  GetProcedureAddress(_RegCreateKeyExW, advapi32, 'RegCreateKeyExW');
  asm
    mov esp, ebp
    pop ebp
    jmp [_RegCreateKeyExW]
  end;
end;
{$ELSE}
function RegCreateKeyExW; external advapi32 name 'RegCreateKeyExW';
{$ENDIF DYNAMIC_LINK}
{$IFDEF UNICODE}

{$IFDEF DYNAMIC_LINK}
var
  _RegCreateKeyEx: Pointer;

function RegCreateKeyEx;
begin
  GetProcedureAddress(_RegCreateKeyEx, advapi32, 'RegCreateKeyExW');
  asm
    mov esp, ebp
    pop ebp
    jmp [_RegCreateKeyEx]
  end;
end;
{$ELSE}
function RegCreateKeyEx; external advapi32 name 'RegCreateKeyExW';
{$ENDIF DYNAMIC_LINK}
{$ELSE}

{$IFDEF DYNAMIC_LINK}
var
  _RegCreateKeyEx: Pointer;

function RegCreateKeyEx;
begin
  GetProcedureAddress(_RegCreateKeyEx, advapi32, 'RegCreateKeyExA');
  asm
    mov esp, ebp
    pop ebp
    jmp [_RegCreateKeyEx]
  end;
end;
{$ELSE}
function RegCreateKeyEx; external advapi32 name 'RegCreateKeyExA';
{$ENDIF DYNAMIC_LINK}
{$ENDIF}

{$IFDEF DYNAMIC_LINK}
var
  _RegDeleteKeyA: Pointer;

function RegDeleteKeyA;
begin
  GetProcedureAddress(_RegDeleteKeyA, advapi32, 'RegDeleteKeyA');
  asm
    mov esp, ebp
    pop ebp
    jmp [_RegDeleteKeyA]
  end;
end;
{$ELSE}
function RegDeleteKeyA; external advapi32 name 'RegDeleteKeyA';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _RegDeleteKeyW: Pointer;

function RegDeleteKeyW;
begin
  GetProcedureAddress(_RegDeleteKeyW, advapi32, 'RegDeleteKeyW');
  asm
    mov esp, ebp
    pop ebp
    jmp [_RegDeleteKeyW]
  end;
end;
{$ELSE}
function RegDeleteKeyW; external advapi32 name 'RegDeleteKeyW';
{$ENDIF DYNAMIC_LINK}
{$IFDEF UNICODE}

{$IFDEF DYNAMIC_LINK}
var
  _RegDeleteKey: Pointer;

function RegDeleteKey;
begin
  GetProcedureAddress(_RegDeleteKey, advapi32, 'RegDeleteKeyW');
  asm
    mov esp, ebp
    pop ebp
    jmp [_RegDeleteKey]
  end;
end;
{$ELSE}
function RegDeleteKey; external advapi32 name 'RegDeleteKeyW';
{$ENDIF DYNAMIC_LINK}
{$ELSE}

{$IFDEF DYNAMIC_LINK}
var
  _RegDeleteKey: Pointer;

function RegDeleteKey;
begin
  GetProcedureAddress(_RegDeleteKey, advapi32, 'RegDeleteKeyA');
  asm
    mov esp, ebp
    pop ebp
    jmp [_RegDeleteKey]
  end;
end;
{$ELSE}
function RegDeleteKey; external advapi32 name 'RegDeleteKeyA';
{$ENDIF DYNAMIC_LINK}
{$ENDIF}

{$IFDEF DYNAMIC_LINK}
var
  _RegDeleteValueA: Pointer;

function RegDeleteValueA;
begin
  GetProcedureAddress(_RegDeleteValueA, advapi32, 'RegDeleteValueA');
  asm
    mov esp, ebp
    pop ebp
    jmp [_RegDeleteValueA]
  end;
end;
{$ELSE}
function RegDeleteValueA; external advapi32 name 'RegDeleteValueA';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _RegDeleteValueW: Pointer;

function RegDeleteValueW;
begin
  GetProcedureAddress(_RegDeleteValueW, advapi32, 'RegDeleteValueW');
  asm
    mov esp, ebp
    pop ebp
    jmp [_RegDeleteValueW]
  end;
end;
{$ELSE}
function RegDeleteValueW; external advapi32 name 'RegDeleteValueW';
{$ENDIF DYNAMIC_LINK}
{$IFDEF UNICODE}

{$IFDEF DYNAMIC_LINK}
var
  _RegDeleteValue: Pointer;

function RegDeleteValue;
begin
  GetProcedureAddress(_RegDeleteValue, advapi32, 'RegDeleteValueW');
  asm
    mov esp, ebp
    pop ebp
    jmp [_RegDeleteValue]
  end;
end;
{$ELSE}
function RegDeleteValue; external advapi32 name 'RegDeleteValueW';
{$ENDIF DYNAMIC_LINK}
{$ELSE}

{$IFDEF DYNAMIC_LINK}
var
  _RegDeleteValue: Pointer;

function RegDeleteValue;
begin
  GetProcedureAddress(_RegDeleteValue, advapi32, 'RegDeleteValueA');
  asm
    mov esp, ebp
    pop ebp
    jmp [_RegDeleteValue]
  end;
end;
{$ELSE}
function RegDeleteValue; external advapi32 name 'RegDeleteValueA';
{$ENDIF DYNAMIC_LINK}
{$ENDIF}

{$IFDEF DYNAMIC_LINK}
var
  _RegEnumKeyA: Pointer;

function RegEnumKeyA;
begin
  GetProcedureAddress(_RegEnumKeyA, advapi32, 'RegEnumKeyA');
  asm
    mov esp, ebp
    pop ebp
    jmp [_RegEnumKeyA]
  end;
end;
{$ELSE}
function RegEnumKeyA; external advapi32 name 'RegEnumKeyA';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _RegEnumKeyW: Pointer;

function RegEnumKeyW;
begin
  GetProcedureAddress(_RegEnumKeyW, advapi32, 'RegEnumKeyW');
  asm
    mov esp, ebp
    pop ebp
    jmp [_RegEnumKeyW]
  end;
end;
{$ELSE}
function RegEnumKeyW; external advapi32 name 'RegEnumKeyW';
{$ENDIF DYNAMIC_LINK}
{$IFDEF UNICODE}

{$IFDEF DYNAMIC_LINK}
var
  _RegEnumKey: Pointer;

function RegEnumKey;
begin
  GetProcedureAddress(_RegEnumKey, advapi32, 'RegEnumKeyW');
  asm
    mov esp, ebp
    pop ebp
    jmp [_RegEnumKey]
  end;
end;
{$ELSE}
function RegEnumKey; external advapi32 name 'RegEnumKeyW';
{$ENDIF DYNAMIC_LINK}
{$ELSE}

{$IFDEF DYNAMIC_LINK}
var
  _RegEnumKey: Pointer;

function RegEnumKey;
begin
  GetProcedureAddress(_RegEnumKey, advapi32, 'RegEnumKeyA');
  asm
    mov esp, ebp
    pop ebp
    jmp [_RegEnumKey]
  end;
end;
{$ELSE}
function RegEnumKey; external advapi32 name 'RegEnumKeyA';
{$ENDIF DYNAMIC_LINK}
{$ENDIF}

{$IFDEF DYNAMIC_LINK}
var
  _RegEnumKeyExA: Pointer;

function RegEnumKeyExA;
begin
  GetProcedureAddress(_RegEnumKeyExA, advapi32, 'RegEnumKeyExA');
  asm
    mov esp, ebp
    pop ebp
    jmp [_RegEnumKeyExA]
  end;
end;
{$ELSE}
function RegEnumKeyExA; external advapi32 name 'RegEnumKeyExA';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _RegEnumKeyExW: Pointer;

function RegEnumKeyExW;
begin
  GetProcedureAddress(_RegEnumKeyExW, advapi32, 'RegEnumKeyExW');
  asm
    mov esp, ebp
    pop ebp
    jmp [_RegEnumKeyExW]
  end;
end;
{$ELSE}
function RegEnumKeyExW; external advapi32 name 'RegEnumKeyExW';
{$ENDIF DYNAMIC_LINK}
{$IFDEF UNICODE}

{$IFDEF DYNAMIC_LINK}
var
  _RegEnumKeyEx: Pointer;

function RegEnumKeyEx;
begin
  GetProcedureAddress(_RegEnumKeyEx, advapi32, 'RegEnumKeyExW');
  asm
    mov esp, ebp
    pop ebp
    jmp [_RegEnumKeyEx]
  end;
end;
{$ELSE}
function RegEnumKeyEx; external advapi32 name 'RegEnumKeyExW';
{$ENDIF DYNAMIC_LINK}
{$ELSE}

{$IFDEF DYNAMIC_LINK}
var
  _RegEnumKeyEx: Pointer;

function RegEnumKeyEx;
begin
  GetProcedureAddress(_RegEnumKeyEx, advapi32, 'RegEnumKeyExA');
  asm
    mov esp, ebp
    pop ebp
    jmp [_RegEnumKeyEx]
  end;
end;
{$ELSE}
function RegEnumKeyEx; external advapi32 name 'RegEnumKeyExA';
{$ENDIF DYNAMIC_LINK}
{$ENDIF}

{$IFDEF DYNAMIC_LINK}
var
  _RegEnumValueA: Pointer;

function RegEnumValueA;
begin
  GetProcedureAddress(_RegEnumValueA, advapi32, 'RegEnumValueA');
  asm
    mov esp, ebp
    pop ebp
    jmp [_RegEnumValueA]
  end;
end;
{$ELSE}
function RegEnumValueA; external advapi32 name 'RegEnumValueA';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _RegEnumValueW: Pointer;

function RegEnumValueW;
begin
  GetProcedureAddress(_RegEnumValueW, advapi32, 'RegEnumValueW');
  asm
    mov esp, ebp
    pop ebp
    jmp [_RegEnumValueW]
  end;
end;
{$ELSE}
function RegEnumValueW; external advapi32 name 'RegEnumValueW';
{$ENDIF DYNAMIC_LINK}
{$IFDEF UNICODE}

{$IFDEF DYNAMIC_LINK}
var
  _RegEnumValue: Pointer;

function RegEnumValue;
begin
  GetProcedureAddress(_RegEnumValue, advapi32, 'RegEnumValueW');
  asm
    mov esp, ebp
    pop ebp
    jmp [_RegEnumValue]
  end;
end;
{$ELSE}
function RegEnumValue; external advapi32 name 'RegEnumValueW';
{$ENDIF DYNAMIC_LINK}
{$ELSE}

{$IFDEF DYNAMIC_LINK}
var
  _RegEnumValue: Pointer;

function RegEnumValue;
begin
  GetProcedureAddress(_RegEnumValue, advapi32, 'RegEnumValueA');
  asm
    mov esp, ebp
    pop ebp
    jmp [_RegEnumValue]
  end;
end;
{$ELSE}
function RegEnumValue; external advapi32 name 'RegEnumValueA';
{$ENDIF DYNAMIC_LINK}
{$ENDIF}

{$IFDEF DYNAMIC_LINK}
var
  _RegFlushKey: Pointer;

function RegFlushKey;
begin
  GetProcedureAddress(_RegFlushKey, advapi32, 'RegFlushKey');
  asm
    mov esp, ebp
    pop ebp
    jmp [_RegFlushKey]
  end;
end;
{$ELSE}
function RegFlushKey; external advapi32 name 'RegFlushKey';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _RegGetKeySecurity: Pointer;

function RegGetKeySecurity;
begin
  GetProcedureAddress(_RegGetKeySecurity, advapi32, 'RegGetKeySecurity');
  asm
    mov esp, ebp
    pop ebp
    jmp [_RegGetKeySecurity]
  end;
end;
{$ELSE}
function RegGetKeySecurity; external advapi32 name 'RegGetKeySecurity';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _RegLoadKeyA: Pointer;

function RegLoadKeyA;
begin
  GetProcedureAddress(_RegLoadKeyA, advapi32, 'RegLoadKeyA');
  asm
    mov esp, ebp
    pop ebp
    jmp [_RegLoadKeyA]
  end;
end;
{$ELSE}
function RegLoadKeyA; external advapi32 name 'RegLoadKeyA';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _RegLoadKeyW: Pointer;

function RegLoadKeyW;
begin
  GetProcedureAddress(_RegLoadKeyW, advapi32, 'RegLoadKeyW');
  asm
    mov esp, ebp
    pop ebp
    jmp [_RegLoadKeyW]
  end;
end;
{$ELSE}
function RegLoadKeyW; external advapi32 name 'RegLoadKeyW';
{$ENDIF DYNAMIC_LINK}
{$IFDEF UNICODE}

{$IFDEF DYNAMIC_LINK}
var
  _RegLoadKey: Pointer;

function RegLoadKey;
begin
  GetProcedureAddress(_RegLoadKey, advapi32, 'RegLoadKeyW');
  asm
    mov esp, ebp
    pop ebp
    jmp [_RegLoadKey]
  end;
end;
{$ELSE}
function RegLoadKey; external advapi32 name 'RegLoadKeyW';
{$ENDIF DYNAMIC_LINK}
{$ELSE}

{$IFDEF DYNAMIC_LINK}
var
  _RegLoadKey: Pointer;

function RegLoadKey;
begin
  GetProcedureAddress(_RegLoadKey, advapi32, 'RegLoadKeyA');
  asm
    mov esp, ebp
    pop ebp
    jmp [_RegLoadKey]
  end;
end;
{$ELSE}
function RegLoadKey; external advapi32 name 'RegLoadKeyA';
{$ENDIF DYNAMIC_LINK}
{$ENDIF}

type
  TRegNotifyChangeKeyValue = function (hKey: HKEY; bWatchSubtree: LongBool; dwNotifyFilter: DWORD; hEvent: HANDLE; fAsynchronus: LongBool): LONG; stdcall;

var
  _RegNotifyChangeKeyValue: Pointer;

function RegNotifyChangeKeyValue(hKey: HKEY; bWatchSubtree: LongBool; dwNotifyFilter: DWORD; hEvent: HANDLE; fAsynchronus: LongBool): LONG;
begin
  GetProcedureAddress(_RegNotifyChangeKeyValue, advapi32, 'RegNotifyChangeKeyValue');
  if bWatchSubTree then
    Result := TRegNotifyChangeKeyValue(_RegNotifyChangeKeyValue)(hKey, LongBool(1), dwNotifyFilter, hEvent, fAsynchronus)
  else
    Result := TRegNotifyChangeKeyValue(_RegNotifyChangeKeyValue)(hKey, LongBool(0), dwNotifyFilter, hEvent, fAsynchronus);
end;

{$IFDEF DYNAMIC_LINK}
var
  _RegOpenKeyA: Pointer;

function RegOpenKeyA;
begin
  GetProcedureAddress(_RegOpenKeyA, advapi32, 'RegOpenKeyA');
  asm
    mov esp, ebp
    pop ebp
    jmp [_RegOpenKeyA]
  end;
end;
{$ELSE}
function RegOpenKeyA; external advapi32 name 'RegOpenKeyA';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _RegOpenKeyW: Pointer;

function RegOpenKeyW;
begin
  GetProcedureAddress(_RegOpenKeyW, advapi32, 'RegOpenKeyW');
  asm
    mov esp, ebp
    pop ebp
    jmp [_RegOpenKeyW]
  end;
end;
{$ELSE}
function RegOpenKeyW; external advapi32 name 'RegOpenKeyW';
{$ENDIF DYNAMIC_LINK}
{$IFDEF UNICODE}

{$IFDEF DYNAMIC_LINK}
var
  _RegOpenKey: Pointer;

function RegOpenKey;
begin
  GetProcedureAddress(_RegOpenKey, advapi32, 'RegOpenKeyW');
  asm
    mov esp, ebp
    pop ebp
    jmp [_RegOpenKey]
  end;
end;
{$ELSE}
function RegOpenKey; external advapi32 name 'RegOpenKeyW';
{$ENDIF DYNAMIC_LINK}
{$ELSE}

{$IFDEF DYNAMIC_LINK}
var
  _RegOpenKey: Pointer;

function RegOpenKey;
begin
  GetProcedureAddress(_RegOpenKey, advapi32, 'RegOpenKeyA');
  asm
    mov esp, ebp
    pop ebp
    jmp [_RegOpenKey]
  end;
end;
{$ELSE}
function RegOpenKey; external advapi32 name 'RegOpenKeyA';
{$ENDIF DYNAMIC_LINK}
{$ENDIF}

{$IFDEF DYNAMIC_LINK}
var
  _RegOpenKeyExA: Pointer;

function RegOpenKeyExA;
begin
  GetProcedureAddress(_RegOpenKeyExA, advapi32, 'RegOpenKeyExA');
  asm
    mov esp, ebp
    pop ebp
    jmp [_RegOpenKeyExA]
  end;
end;
{$ELSE}
function RegOpenKeyExA; external advapi32 name 'RegOpenKeyExA';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _RegOpenKeyExW: Pointer;

function RegOpenKeyExW;
begin
  GetProcedureAddress(_RegOpenKeyExW, advapi32, 'RegOpenKeyExW');
  asm
    mov esp, ebp
    pop ebp
    jmp [_RegOpenKeyExW]
  end;
end;
{$ELSE}
function RegOpenKeyExW; external advapi32 name 'RegOpenKeyExW';
{$ENDIF DYNAMIC_LINK}
{$IFDEF UNICODE}

{$IFDEF DYNAMIC_LINK}
var
  _RegOpenKeyEx: Pointer;

function RegOpenKeyEx;
begin
  GetProcedureAddress(_RegOpenKeyEx, advapi32, 'RegOpenKeyExW');
  asm
    mov esp, ebp
    pop ebp
    jmp [_RegOpenKeyEx]
  end;
end;
{$ELSE}
function RegOpenKeyEx; external advapi32 name 'RegOpenKeyExW';
{$ENDIF DYNAMIC_LINK}
{$ELSE}

{$IFDEF DYNAMIC_LINK}
var
  _RegOpenKeyEx: Pointer;

function RegOpenKeyEx;
begin
  GetProcedureAddress(_RegOpenKeyEx, advapi32, 'RegOpenKeyExA');
  asm
    mov esp, ebp
    pop ebp
    jmp [_RegOpenKeyEx]
  end;
end;
{$ELSE}
function RegOpenKeyEx; external advapi32 name 'RegOpenKeyExA';
{$ENDIF DYNAMIC_LINK}
{$ENDIF}

{$IFDEF DYNAMIC_LINK}
var
  _RegQueryInfoKeyA: Pointer;

function RegQueryInfoKeyA;
begin
  GetProcedureAddress(_RegQueryInfoKeyA, advapi32, 'RegQueryInfoKeyA');
  asm
    mov esp, ebp
    pop ebp
    jmp [_RegQueryInfoKeyA]
  end;
end;
{$ELSE}
function RegQueryInfoKeyA; external advapi32 name 'RegQueryInfoKeyA';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _RegQueryInfoKeyW: Pointer;

function RegQueryInfoKeyW;
begin
  GetProcedureAddress(_RegQueryInfoKeyW, advapi32, 'RegQueryInfoKeyW');
  asm
    mov esp, ebp
    pop ebp
    jmp [_RegQueryInfoKeyW]
  end;
end;
{$ELSE}
function RegQueryInfoKeyW; external advapi32 name 'RegQueryInfoKeyW';
{$ENDIF DYNAMIC_LINK}
{$IFDEF UNICODE}

{$IFDEF DYNAMIC_LINK}
var
  _RegQueryInfoKey: Pointer;

function RegQueryInfoKey;
begin
  GetProcedureAddress(_RegQueryInfoKey, advapi32, 'RegQueryInfoKeyW');
  asm
    mov esp, ebp
    pop ebp
    jmp [_RegQueryInfoKey]
  end;
end;
{$ELSE}
function RegQueryInfoKey; external advapi32 name 'RegQueryInfoKeyW';
{$ENDIF DYNAMIC_LINK}
{$ELSE}

{$IFDEF DYNAMIC_LINK}
var
  _RegQueryInfoKey: Pointer;

function RegQueryInfoKey;
begin
  GetProcedureAddress(_RegQueryInfoKey, advapi32, 'RegQueryInfoKeyA');
  asm
    mov esp, ebp
    pop ebp
    jmp [_RegQueryInfoKey]
  end;
end;
{$ELSE}
function RegQueryInfoKey; external advapi32 name 'RegQueryInfoKeyA';
{$ENDIF DYNAMIC_LINK}
{$ENDIF}

{$IFDEF DYNAMIC_LINK}
var
  _RegQueryValueA: Pointer;

function RegQueryValueA;
begin
  GetProcedureAddress(_RegQueryValueA, advapi32, 'RegQueryValueA');
  asm
    mov esp, ebp
    pop ebp
    jmp [_RegQueryValueA]
  end;
end;
{$ELSE}
function RegQueryValueA; external advapi32 name 'RegQueryValueA';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _RegQueryValueW: Pointer;

function RegQueryValueW;
begin
  GetProcedureAddress(_RegQueryValueW, advapi32, 'RegQueryValueW');
  asm
    mov esp, ebp
    pop ebp
    jmp [_RegQueryValueW]
  end;
end;
{$ELSE}
function RegQueryValueW; external advapi32 name 'RegQueryValueW';
{$ENDIF DYNAMIC_LINK}
{$IFDEF UNICODE}

{$IFDEF DYNAMIC_LINK}
var
  _RegQueryValue: Pointer;

function RegQueryValue;
begin
  GetProcedureAddress(_RegQueryValue, advapi32, 'RegQueryValueW');
  asm
    mov esp, ebp
    pop ebp
    jmp [_RegQueryValue]
  end;
end;
{$ELSE}
function RegQueryValue; external advapi32 name 'RegQueryValueW';
{$ENDIF DYNAMIC_LINK}
{$ELSE}

{$IFDEF DYNAMIC_LINK}
var
  _RegQueryValue: Pointer;

function RegQueryValue;
begin
  GetProcedureAddress(_RegQueryValue, advapi32, 'RegQueryValueA');
  asm
    mov esp, ebp
    pop ebp
    jmp [_RegQueryValue]
  end;
end;
{$ELSE}
function RegQueryValue; external advapi32 name 'RegQueryValueA';
{$ENDIF DYNAMIC_LINK}
{$ENDIF}

{$IFDEF DYNAMIC_LINK}
var
  _RegQueryMultipleValuesA: Pointer;

function RegQueryMultipleValuesA;
begin
  GetProcedureAddress(_RegQueryMultipleValuesA, advapi32, 'RegQueryMultipleValuesA');
  asm
    mov esp, ebp
    pop ebp
    jmp [_RegQueryMultipleValuesA]
  end;
end;
{$ELSE}
function RegQueryMultipleValuesA; external advapi32 name 'RegQueryMultipleValuesA';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _RegQueryMultipleValuesW: Pointer;

function RegQueryMultipleValuesW;
begin
  GetProcedureAddress(_RegQueryMultipleValuesW, advapi32, 'RegQueryMultipleValuesW');
  asm
    mov esp, ebp
    pop ebp
    jmp [_RegQueryMultipleValuesW]
  end;
end;
{$ELSE}
function RegQueryMultipleValuesW; external advapi32 name 'RegQueryMultipleValuesW';
{$ENDIF DYNAMIC_LINK}
{$IFDEF UNICODE}

{$IFDEF DYNAMIC_LINK}
var
  _RegQueryMultipleValues: Pointer;

function RegQueryMultipleValues;
begin
  GetProcedureAddress(_RegQueryMultipleValues, advapi32, 'RegQueryMultipleValuesW');
  asm
    mov esp, ebp
    pop ebp
    jmp [_RegQueryMultipleValues]
  end;
end;
{$ELSE}
function RegQueryMultipleValues; external advapi32 name 'RegQueryMultipleValuesW';
{$ENDIF DYNAMIC_LINK}
{$ELSE}

{$IFDEF DYNAMIC_LINK}
var
  _RegQueryMultipleValues: Pointer;

function RegQueryMultipleValues;
begin
  GetProcedureAddress(_RegQueryMultipleValues, advapi32, 'RegQueryMultipleValuesA');
  asm
    mov esp, ebp
    pop ebp
    jmp [_RegQueryMultipleValues]
  end;
end;
{$ELSE}
function RegQueryMultipleValues; external advapi32 name 'RegQueryMultipleValuesA';
{$ENDIF DYNAMIC_LINK}
{$ENDIF}

{$IFDEF DYNAMIC_LINK}
var
  _RegQueryValueExA: Pointer;

function RegQueryValueExA;
begin
  GetProcedureAddress(_RegQueryValueExA, advapi32, 'RegQueryValueExA');
  asm
    mov esp, ebp
    pop ebp
    jmp [_RegQueryValueExA]
  end;
end;
{$ELSE}
function RegQueryValueExA; external advapi32 name 'RegQueryValueExA';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _RegQueryValueExW: Pointer;

function RegQueryValueExW;
begin
  GetProcedureAddress(_RegQueryValueExW, advapi32, 'RegQueryValueExW');
  asm
    mov esp, ebp
    pop ebp
    jmp [_RegQueryValueExW]
  end;
end;
{$ELSE}
function RegQueryValueExW; external advapi32 name 'RegQueryValueExW';
{$ENDIF DYNAMIC_LINK}
{$IFDEF UNICODE}

{$IFDEF DYNAMIC_LINK}
var
  _RegQueryValueEx: Pointer;

function RegQueryValueEx;
begin
  GetProcedureAddress(_RegQueryValueEx, advapi32, 'RegQueryValueExW');
  asm
    mov esp, ebp
    pop ebp
    jmp [_RegQueryValueEx]
  end;
end;
{$ELSE}
function RegQueryValueEx; external advapi32 name 'RegQueryValueExW';
{$ENDIF DYNAMIC_LINK}
{$ELSE}

{$IFDEF DYNAMIC_LINK}
var
  _RegQueryValueEx: Pointer;

function RegQueryValueEx;
begin
  GetProcedureAddress(_RegQueryValueEx, advapi32, 'RegQueryValueExA');
  asm
    mov esp, ebp
    pop ebp
    jmp [_RegQueryValueEx]
  end;
end;
{$ELSE}
function RegQueryValueEx; external advapi32 name 'RegQueryValueExA';
{$ENDIF DYNAMIC_LINK}
{$ENDIF}

{$IFDEF DYNAMIC_LINK}
var
  _RegReplaceKeyA: Pointer;

function RegReplaceKeyA;
begin
  GetProcedureAddress(_RegReplaceKeyA, advapi32, 'RegReplaceKeyA');
  asm
    mov esp, ebp
    pop ebp
    jmp [_RegReplaceKeyA]
  end;
end;
{$ELSE}
function RegReplaceKeyA; external advapi32 name 'RegReplaceKeyA';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _RegReplaceKeyW: Pointer;

function RegReplaceKeyW;
begin
  GetProcedureAddress(_RegReplaceKeyW, advapi32, 'RegReplaceKeyW');
  asm
    mov esp, ebp
    pop ebp
    jmp [_RegReplaceKeyW]
  end;
end;
{$ELSE}
function RegReplaceKeyW; external advapi32 name 'RegReplaceKeyW';
{$ENDIF DYNAMIC_LINK}
{$IFDEF UNICODE}

{$IFDEF DYNAMIC_LINK}
var
  _RegReplaceKey: Pointer;

function RegReplaceKey;
begin
  GetProcedureAddress(_RegReplaceKey, advapi32, 'RegReplaceKeyW');
  asm
    mov esp, ebp
    pop ebp
    jmp [_RegReplaceKey]
  end;
end;
{$ELSE}
function RegReplaceKey; external advapi32 name 'RegReplaceKeyW';
{$ENDIF DYNAMIC_LINK}
{$ELSE}

{$IFDEF DYNAMIC_LINK}
var
  _RegReplaceKey: Pointer;

function RegReplaceKey;
begin
  GetProcedureAddress(_RegReplaceKey, advapi32, 'RegReplaceKeyA');
  asm
    mov esp, ebp
    pop ebp
    jmp [_RegReplaceKey]
  end;
end;
{$ELSE}
function RegReplaceKey; external advapi32 name 'RegReplaceKeyA';
{$ENDIF DYNAMIC_LINK}
{$ENDIF}

{$IFDEF DYNAMIC_LINK}
var
  _RegRestoreKeyA: Pointer;

function RegRestoreKeyA;
begin
  GetProcedureAddress(_RegRestoreKeyA, advapi32, 'RegRestoreKeyA');
  asm
    mov esp, ebp
    pop ebp
    jmp [_RegRestoreKeyA]
  end;
end;
{$ELSE}
function RegRestoreKeyA; external advapi32 name 'RegRestoreKeyA';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _RegRestoreKeyW: Pointer;

function RegRestoreKeyW;
begin
  GetProcedureAddress(_RegRestoreKeyW, advapi32, 'RegRestoreKeyW');
  asm
    mov esp, ebp
    pop ebp
    jmp [_RegRestoreKeyW]
  end;
end;
{$ELSE}
function RegRestoreKeyW; external advapi32 name 'RegRestoreKeyW';
{$ENDIF DYNAMIC_LINK}
{$IFDEF UNICODE}

{$IFDEF DYNAMIC_LINK}
var
  _RegRestoreKey: Pointer;

function RegRestoreKey;
begin
  GetProcedureAddress(_RegRestoreKey, advapi32, 'RegRestoreKeyW');
  asm
    mov esp, ebp
    pop ebp
    jmp [_RegRestoreKey]
  end;
end;
{$ELSE}
function RegRestoreKey; external advapi32 name 'RegRestoreKeyW';
{$ENDIF DYNAMIC_LINK}
{$ELSE}

{$IFDEF DYNAMIC_LINK}
var
  _RegRestoreKey: Pointer;

function RegRestoreKey;
begin
  GetProcedureAddress(_RegRestoreKey, advapi32, 'RegRestoreKeyA');
  asm
    mov esp, ebp
    pop ebp
    jmp [_RegRestoreKey]
  end;
end;
{$ELSE}
function RegRestoreKey; external advapi32 name 'RegRestoreKeyA';
{$ENDIF DYNAMIC_LINK}
{$ENDIF}

{$IFDEF DYNAMIC_LINK}
var
  _RegSaveKeyA: Pointer;

function RegSaveKeyA;
begin
  GetProcedureAddress(_RegSaveKeyA, advapi32, 'RegSaveKeyA');
  asm
    mov esp, ebp
    pop ebp
    jmp [_RegSaveKeyA]
  end;
end;
{$ELSE}
function RegSaveKeyA; external advapi32 name 'RegSaveKeyA';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _RegSaveKeyW: Pointer;

function RegSaveKeyW;
begin
  GetProcedureAddress(_RegSaveKeyW, advapi32, 'RegSaveKeyW');
  asm
    mov esp, ebp
    pop ebp
    jmp [_RegSaveKeyW]
  end;
end;
{$ELSE}
function RegSaveKeyW; external advapi32 name 'RegSaveKeyW';
{$ENDIF DYNAMIC_LINK}
{$IFDEF UNICODE}

{$IFDEF DYNAMIC_LINK}
var
  _RegSaveKey: Pointer;

function RegSaveKey;
begin
  GetProcedureAddress(_RegSaveKey, advapi32, 'RegSaveKeyW');
  asm
    mov esp, ebp
    pop ebp
    jmp [_RegSaveKey]
  end;
end;
{$ELSE}
function RegSaveKey; external advapi32 name 'RegSaveKeyW';
{$ENDIF DYNAMIC_LINK}
{$ELSE}

{$IFDEF DYNAMIC_LINK}
var
  _RegSaveKey: Pointer;

function RegSaveKey;
begin
  GetProcedureAddress(_RegSaveKey, advapi32, 'RegSaveKeyA');
  asm
    mov esp, ebp
    pop ebp
    jmp [_RegSaveKey]
  end;
end;
{$ELSE}
function RegSaveKey; external advapi32 name 'RegSaveKeyA';
{$ENDIF DYNAMIC_LINK}
{$ENDIF}

{$IFDEF DYNAMIC_LINK}
var
  _RegSetKeySecurity: Pointer;

function RegSetKeySecurity;
begin
  GetProcedureAddress(_RegSetKeySecurity, advapi32, 'RegSetKeySecurity');
  asm
    mov esp, ebp
    pop ebp
    jmp [_RegSetKeySecurity]
  end;
end;
{$ELSE}
function RegSetKeySecurity; external advapi32 name 'RegSetKeySecurity';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _RegSetValueA: Pointer;

function RegSetValueA;
begin
  GetProcedureAddress(_RegSetValueA, advapi32, 'RegSetValueA');
  asm
    mov esp, ebp
    pop ebp
    jmp [_RegSetValueA]
  end;
end;
{$ELSE}
function RegSetValueA; external advapi32 name 'RegSetValueA';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _RegSetValueW: Pointer;

function RegSetValueW;
begin
  GetProcedureAddress(_RegSetValueW, advapi32, 'RegSetValueW');
  asm
    mov esp, ebp
    pop ebp
    jmp [_RegSetValueW]
  end;
end;
{$ELSE}
function RegSetValueW; external advapi32 name 'RegSetValueW';
{$ENDIF DYNAMIC_LINK}
{$IFDEF UNICODE}

{$IFDEF DYNAMIC_LINK}
var
  _RegSetValue: Pointer;

function RegSetValue;
begin
  GetProcedureAddress(_RegSetValue, advapi32, 'RegSetValueW');
  asm
    mov esp, ebp
    pop ebp
    jmp [_RegSetValue]
  end;
end;
{$ELSE}
function RegSetValue; external advapi32 name 'RegSetValueW';
{$ENDIF DYNAMIC_LINK}
{$ELSE}

{$IFDEF DYNAMIC_LINK}
var
  _RegSetValue: Pointer;

function RegSetValue;
begin
  GetProcedureAddress(_RegSetValue, advapi32, 'RegSetValueA');
  asm
    mov esp, ebp
    pop ebp
    jmp [_RegSetValue]
  end;
end;
{$ELSE}
function RegSetValue; external advapi32 name 'RegSetValueA';
{$ENDIF DYNAMIC_LINK}
{$ENDIF}

{$IFDEF DYNAMIC_LINK}
var
  _RegSetValueExA: Pointer;

function RegSetValueExA;
begin
  GetProcedureAddress(_RegSetValueExA, advapi32, 'RegSetValueExA');
  asm
    mov esp, ebp
    pop ebp
    jmp [_RegSetValueExA]
  end;
end;
{$ELSE}
function RegSetValueExA; external advapi32 name 'RegSetValueExA';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _RegSetValueExW: Pointer;

function RegSetValueExW;
begin
  GetProcedureAddress(_RegSetValueExW, advapi32, 'RegSetValueExW');
  asm
    mov esp, ebp
    pop ebp
    jmp [_RegSetValueExW]
  end;
end;
{$ELSE}
function RegSetValueExW; external advapi32 name 'RegSetValueExW';
{$ENDIF DYNAMIC_LINK}
{$IFDEF UNICODE}

{$IFDEF DYNAMIC_LINK}
var
  _RegSetValueEx: Pointer;

function RegSetValueEx;
begin
  GetProcedureAddress(_RegSetValueEx, advapi32, 'RegSetValueExW');
  asm
    mov esp, ebp
    pop ebp
    jmp [_RegSetValueEx]
  end;
end;
{$ELSE}
function RegSetValueEx; external advapi32 name 'RegSetValueExW';
{$ENDIF DYNAMIC_LINK}
{$ELSE}

{$IFDEF DYNAMIC_LINK}
var
  _RegSetValueEx: Pointer;

function RegSetValueEx;
begin
  GetProcedureAddress(_RegSetValueEx, advapi32, 'RegSetValueExA');
  asm
    mov esp, ebp
    pop ebp
    jmp [_RegSetValueEx]
  end;
end;
{$ELSE}
function RegSetValueEx; external advapi32 name 'RegSetValueExA';
{$ENDIF DYNAMIC_LINK}
{$ENDIF}

{$IFDEF DYNAMIC_LINK}
var
  _RegUnLoadKeyA: Pointer;

function RegUnLoadKeyA;
begin
  GetProcedureAddress(_RegUnLoadKeyA, advapi32, 'RegUnLoadKeyA');
  asm
    mov esp, ebp
    pop ebp
    jmp [_RegUnLoadKeyA]
  end;
end;
{$ELSE}
function RegUnLoadKeyA; external advapi32 name 'RegUnLoadKeyA';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _RegUnLoadKeyW: Pointer;

function RegUnLoadKeyW;
begin
  GetProcedureAddress(_RegUnLoadKeyW, advapi32, 'RegUnLoadKeyW');
  asm
    mov esp, ebp
    pop ebp
    jmp [_RegUnLoadKeyW]
  end;
end;
{$ELSE}
function RegUnLoadKeyW; external advapi32 name 'RegUnLoadKeyW';
{$ENDIF DYNAMIC_LINK}
{$IFDEF UNICODE}

{$IFDEF DYNAMIC_LINK}
var
  _RegUnLoadKey: Pointer;

function RegUnLoadKey;
begin
  GetProcedureAddress(_RegUnLoadKey, advapi32, 'RegUnLoadKeyW');
  asm
    mov esp, ebp
    pop ebp
    jmp [_RegUnLoadKey]
  end;
end;
{$ELSE}
function RegUnLoadKey; external advapi32 name 'RegUnLoadKeyW';
{$ENDIF DYNAMIC_LINK}
{$ELSE}

{$IFDEF DYNAMIC_LINK}
var
  _RegUnLoadKey: Pointer;

function RegUnLoadKey;
begin
  GetProcedureAddress(_RegUnLoadKey, advapi32, 'RegUnLoadKeyA');
  asm
    mov esp, ebp
    pop ebp
    jmp [_RegUnLoadKey]
  end;
end;
{$ELSE}
function RegUnLoadKey; external advapi32 name 'RegUnLoadKeyA';
{$ENDIF DYNAMIC_LINK}
{$ENDIF}

{$IFDEF DYNAMIC_LINK}
var
  _InitiateSystemShutdownA: Pointer;

function InitiateSystemShutdownA;
begin
  GetProcedureAddress(_InitiateSystemShutdownA, advapi32, 'InitiateSystemShutdownA');
  asm
    mov esp, ebp
    pop ebp
    jmp [_InitiateSystemShutdownA]
  end;
end;
{$ELSE}
function InitiateSystemShutdownA; external advapi32 name 'InitiateSystemShutdownA';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _InitiateSystemShutdownW: Pointer;

function InitiateSystemShutdownW;
begin
  GetProcedureAddress(_InitiateSystemShutdownW, advapi32, 'InitiateSystemShutdownW');
  asm
    mov esp, ebp
    pop ebp
    jmp [_InitiateSystemShutdownW]
  end;
end;
{$ELSE}
function InitiateSystemShutdownW; external advapi32 name 'InitiateSystemShutdownW';
{$ENDIF DYNAMIC_LINK}
{$IFDEF UNICODE}

{$IFDEF DYNAMIC_LINK}
var
  _InitiateSystemShutdown: Pointer;

function InitiateSystemShutdown;
begin
  GetProcedureAddress(_InitiateSystemShutdown, advapi32, 'InitiateSystemShutdownW');
  asm
    mov esp, ebp
    pop ebp
    jmp [_InitiateSystemShutdown]
  end;
end;
{$ELSE}
function InitiateSystemShutdown; external advapi32 name 'InitiateSystemShutdownW';
{$ENDIF DYNAMIC_LINK}
{$ELSE}

{$IFDEF DYNAMIC_LINK}
var
  _InitiateSystemShutdown: Pointer;

function InitiateSystemShutdown;
begin
  GetProcedureAddress(_InitiateSystemShutdown, advapi32, 'InitiateSystemShutdownA');
  asm
    mov esp, ebp
    pop ebp
    jmp [_InitiateSystemShutdown]
  end;
end;
{$ELSE}
function InitiateSystemShutdown; external advapi32 name 'InitiateSystemShutdownA';
{$ENDIF DYNAMIC_LINK}
{$ENDIF}

{$IFDEF DYNAMIC_LINK}
var
  _AbortSystemShutdownA: Pointer;

function AbortSystemShutdownA;
begin
  GetProcedureAddress(_AbortSystemShutdownA, advapi32, 'AbortSystemShutdownA');
  asm
    mov esp, ebp
    pop ebp
    jmp [_AbortSystemShutdownA]
  end;
end;
{$ELSE}
function AbortSystemShutdownA; external advapi32 name 'AbortSystemShutdownA';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _AbortSystemShutdownW: Pointer;

function AbortSystemShutdownW;
begin
  GetProcedureAddress(_AbortSystemShutdownW, advapi32, 'AbortSystemShutdownW');
  asm
    mov esp, ebp
    pop ebp
    jmp [_AbortSystemShutdownW]
  end;
end;
{$ELSE}
function AbortSystemShutdownW; external advapi32 name 'AbortSystemShutdownW';
{$ENDIF DYNAMIC_LINK}
{$IFDEF UNICODE}

{$IFDEF DYNAMIC_LINK}
var
  _AbortSystemShutdown: Pointer;

function AbortSystemShutdown;
begin
  GetProcedureAddress(_AbortSystemShutdown, advapi32, 'AbortSystemShutdownW');
  asm
    mov esp, ebp
    pop ebp
    jmp [_AbortSystemShutdown]
  end;
end;
{$ELSE}
function AbortSystemShutdown; external advapi32 name 'AbortSystemShutdownW';
{$ENDIF DYNAMIC_LINK}
{$ELSE}

{$IFDEF DYNAMIC_LINK}
var
  _AbortSystemShutdown: Pointer;

function AbortSystemShutdown;
begin
  GetProcedureAddress(_AbortSystemShutdown, advapi32, 'AbortSystemShutdownA');
  asm
    mov esp, ebp
    pop ebp
    jmp [_AbortSystemShutdown]
  end;
end;
{$ELSE}
function AbortSystemShutdown; external advapi32 name 'AbortSystemShutdownA';
{$ENDIF DYNAMIC_LINK}
{$ENDIF}

{$IFDEF DYNAMIC_LINK}
var
  _InitiateSystemShutdownExA: Pointer;

function InitiateSystemShutdownExA;
begin
  GetProcedureAddress(_InitiateSystemShutdownExA, advapi32, 'InitiateSystemShutdownExA');
  asm
    mov esp, ebp
    pop ebp
    jmp [_InitiateSystemShutdownExA]
  end;
end;
{$ELSE}
function InitiateSystemShutdownExA; external advapi32 name 'InitiateSystemShutdownExA';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _InitiateSystemShutdownExW: Pointer;

function InitiateSystemShutdownExW;
begin
  GetProcedureAddress(_InitiateSystemShutdownExW, advapi32, 'InitiateSystemShutdownExW');
  asm
    mov esp, ebp
    pop ebp
    jmp [_InitiateSystemShutdownExW]
  end;
end;
{$ELSE}
function InitiateSystemShutdownExW; external advapi32 name 'InitiateSystemShutdownExW';
{$ENDIF DYNAMIC_LINK}
{$IFDEF UNICODE}

{$IFDEF DYNAMIC_LINK}
var
  _InitiateSystemShutdownEx: Pointer;

function InitiateSystemShutdownEx;
begin
  GetProcedureAddress(_InitiateSystemShutdownEx, advapi32, 'InitiateSystemShutdownExW');
  asm
    mov esp, ebp
    pop ebp
    jmp [_InitiateSystemShutdownEx]
  end;
end;
{$ELSE}
function InitiateSystemShutdownEx; external advapi32 name 'InitiateSystemShutdownExW';
{$ENDIF DYNAMIC_LINK}
{$ELSE}

{$IFDEF DYNAMIC_LINK}
var
  _InitiateSystemShutdownEx: Pointer;

function InitiateSystemShutdownEx;
begin
  GetProcedureAddress(_InitiateSystemShutdownEx, advapi32, 'InitiateSystemShutdownExA');
  asm
    mov esp, ebp
    pop ebp
    jmp [_InitiateSystemShutdownEx]
  end;
end;
{$ELSE}
function InitiateSystemShutdownEx; external advapi32 name 'InitiateSystemShutdownExA';
{$ENDIF DYNAMIC_LINK}
{$ENDIF}

{$IFDEF DYNAMIC_LINK}
var
  _RegSaveKeyExA: Pointer;

function RegSaveKeyExA;
begin
  GetProcedureAddress(_RegSaveKeyExA, advapi32, 'RegSaveKeyExA');
  asm
    mov esp, ebp
    pop ebp
    jmp [_RegSaveKeyExA]
  end;
end;
{$ELSE}
function RegSaveKeyExA; external advapi32 name 'RegSaveKeyExA';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _RegSaveKeyExW: Pointer;

function RegSaveKeyExW;
begin
  GetProcedureAddress(_RegSaveKeyExW, advapi32, 'RegSaveKeyExW');
  asm
    mov esp, ebp
    pop ebp
    jmp [_RegSaveKeyExW]
  end;
end;
{$ELSE}
function RegSaveKeyExW; external advapi32 name 'RegSaveKeyExW';
{$ENDIF DYNAMIC_LINK}
{$IFDEF UNICODE}

{$IFDEF DYNAMIC_LINK}
var
  _RegSaveKeyEx: Pointer;

function RegSaveKeyEx;
begin
  GetProcedureAddress(_RegSaveKeyEx, advapi32, 'RegSaveKeyExW');
  asm
    mov esp, ebp
    pop ebp
    jmp [_RegSaveKeyEx]
  end;
end;
{$ELSE}
function RegSaveKeyEx; external advapi32 name 'RegSaveKeyExW';
{$ENDIF DYNAMIC_LINK}
{$ELSE}

{$IFDEF DYNAMIC_LINK}
var
  _RegSaveKeyEx: Pointer;

function RegSaveKeyEx;
begin
  GetProcedureAddress(_RegSaveKeyEx, advapi32, 'RegSaveKeyExA');
  asm
    mov esp, ebp
    pop ebp
    jmp [_RegSaveKeyEx]
  end;
end;
{$ELSE}
function RegSaveKeyEx; external advapi32 name 'RegSaveKeyExA';
{$ENDIF DYNAMIC_LINK}
{$ENDIF}

{$IFDEF DYNAMIC_LINK}
var
  _Wow64Win32ApiEntry: Pointer;

function Wow64Win32ApiEntry;
begin
  GetProcedureAddress(_Wow64Win32ApiEntry, advapi32, 'Wow64Win32ApiEntry');
  asm
    mov esp, ebp
    pop ebp
    jmp [_Wow64Win32ApiEntry]
  end;
end;
{$ELSE}
function Wow64Win32ApiEntry; external advapi32 name 'Wow64Win32ApiEntry';
{$ENDIF DYNAMIC_LINK}

end.
