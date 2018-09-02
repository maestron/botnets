{******************************************************************************}
{                                                       	               }
{ Subauthentication packages API interface Unit for Object Pascal              }
{                                                       	               }
{ Portions created by Microsoft are Copyright (C) 1995-2001 Microsoft          }
{ Corporation. All Rights Reserved.                                            }
{ 								               }
{ The original file is: subauth.h, released June 2000. The original Pascal     }
{ code is: SubAuth.pas, released December 2000. The initial developer of the   }
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

unit JwaSubAuth;

{$WEAKPACKAGEUNIT}

{$HPPEMIT ''}
{$HPPEMIT '#include "subauth.h"'}
{$HPPEMIT ''}

{$I WINDEFINES.INC}

interface

uses
  JwaWinType;

type
  SAM_HANDLE = PVOID;
  {$EXTERNALSYM SAM_HANDLE}
  PSAM_HANDLE = ^SAM_HANDLE;
  {$EXTERNALSYM PSAM_HANDLE}

  POLD_LARGE_INTEGER = ^OLD_LARGE_INTEGER;
  {$EXTERNALSYM POLD_LARGE_INTEGER}
  _OLD_LARGE_INTEGER = record
    LowPart: ULONG;
    HighPart: LONG;
  end;
  {$EXTERNALSYM _OLD_LARGE_INTEGER}
  OLD_LARGE_INTEGER = _OLD_LARGE_INTEGER;
  {$EXTERNALSYM OLD_LARGE_INTEGER}
  TOldLargeInteger = OLD_LARGE_INTEGER;
  POldLargeInteger = POLD_LARGE_INTEGER;

//
// User account control flags...
//

const
  USER_ACCOUNT_DISABLED                = ($00000001);
  {$EXTERNALSYM USER_ACCOUNT_DISABLED}
  USER_HOME_DIRECTORY_REQUIRED         = ($00000002);
  {$EXTERNALSYM USER_HOME_DIRECTORY_REQUIRED}
  USER_PASSWORD_NOT_REQUIRED           = ($00000004);
  {$EXTERNALSYM USER_PASSWORD_NOT_REQUIRED}
  USER_TEMP_DUPLICATE_ACCOUNT          = ($00000008);
  {$EXTERNALSYM USER_TEMP_DUPLICATE_ACCOUNT}
  USER_NORMAL_ACCOUNT                  = ($00000010);
  {$EXTERNALSYM USER_NORMAL_ACCOUNT}
  USER_MNS_LOGON_ACCOUNT               = ($00000020);
  {$EXTERNALSYM USER_MNS_LOGON_ACCOUNT}
  USER_INTERDOMAIN_TRUST_ACCOUNT       = ($00000040);
  {$EXTERNALSYM USER_INTERDOMAIN_TRUST_ACCOUNT}
  USER_WORKSTATION_TRUST_ACCOUNT       = ($00000080);
  {$EXTERNALSYM USER_WORKSTATION_TRUST_ACCOUNT}
  USER_SERVER_TRUST_ACCOUNT            = ($00000100);
  {$EXTERNALSYM USER_SERVER_TRUST_ACCOUNT}
  USER_DONT_EXPIRE_PASSWORD            = ($00000200);
  {$EXTERNALSYM USER_DONT_EXPIRE_PASSWORD}
  USER_ACCOUNT_AUTO_LOCKED             = ($00000400);
  {$EXTERNALSYM USER_ACCOUNT_AUTO_LOCKED}
  USER_ENCRYPTED_TEXT_PASSWORD_ALLOWED = ($00000800);
  {$EXTERNALSYM USER_ENCRYPTED_TEXT_PASSWORD_ALLOWED}
  USER_SMARTCARD_REQUIRED              = ($00001000);
  {$EXTERNALSYM USER_SMARTCARD_REQUIRED}
  USER_TRUSTED_FOR_DELEGATION          = ($00002000);
  {$EXTERNALSYM USER_TRUSTED_FOR_DELEGATION}
  USER_NOT_DELEGATED                   = ($00004000);
  {$EXTERNALSYM USER_NOT_DELEGATED}
  USER_USE_DES_KEY_ONLY                = ($00008000);
  {$EXTERNALSYM USER_USE_DES_KEY_ONLY}
  USER_DONT_REQUIRE_PREAUTH            = ($00010000);
  {$EXTERNALSYM USER_DONT_REQUIRE_PREAUTH}
  USER_PASSWORD_EXPIRED                = ($00020000);
  {$EXTERNALSYM USER_PASSWORD_EXPIRED}
  USER_TRUSTED_TO_AUTHENTICATE_FOR_DELEGATION = ($00040000);
  {$EXTERNALSYM USER_TRUSTED_TO_AUTHENTICATE_FOR_DELEGATION}
  NEXT_FREE_ACCOUNT_CONTROL_BIT        = (USER_TRUSTED_TO_AUTHENTICATE_FOR_DELEGATION shl 1);
  {$EXTERNALSYM NEXT_FREE_ACCOUNT_CONTROL_BIT}

  USER_MACHINE_ACCOUNT_MASK = USER_INTERDOMAIN_TRUST_ACCOUNT or USER_WORKSTATION_TRUST_ACCOUNT or USER_SERVER_TRUST_ACCOUNT;
  {$EXTERNALSYM USER_MACHINE_ACCOUNT_MASK}
  USER_ACCOUNT_TYPE_MASK    = USER_TEMP_DUPLICATE_ACCOUNT or USER_NORMAL_ACCOUNT or USER_MACHINE_ACCOUNT_MASK;
  {$EXTERNALSYM USER_ACCOUNT_TYPE_MASK}

  USER_COMPUTED_ACCOUNT_CONTROL_BITS = USER_ACCOUNT_AUTO_LOCKED or USER_PASSWORD_EXPIRED;
  {$EXTERNALSYM USER_COMPUTED_ACCOUNT_CONTROL_BITS}

//
// Logon times may be expressed in day, hour, or minute granularity.
//
//              Days per week    = 7
//              Hours per week   = 168
//              Minutes per week = 10080
//

  SAM_DAYS_PER_WEEK    = (7);
  {$EXTERNALSYM SAM_DAYS_PER_WEEK}
  SAM_HOURS_PER_WEEK   = (24 * SAM_DAYS_PER_WEEK);
  {$EXTERNALSYM SAM_HOURS_PER_WEEK}
  SAM_MINUTES_PER_WEEK = (60 * SAM_HOURS_PER_WEEK);
  {$EXTERNALSYM SAM_MINUTES_PER_WEEK}

type
  PLOGON_HOURS = ^LOGON_HOURS;
  {$EXTERNALSYM PLOGON_HOURS}
  _LOGON_HOURS = record
    UnitsPerWeek: USHORT;
    //
    // UnitsPerWeek is the number of equal length time units the week is
    // divided into.  This value is used to compute the length of the bit
    // string in logon_hours.  Must be less than or equal to
    // SAM_UNITS_PER_WEEK (10080) for this release.
    //
    // LogonHours is a bit map of valid logon times.  Each bit represents
    // a unique division in a week.  The largest bit map supported is 1260
    // bytes (10080 bits), which represents minutes per week.  In this case
    // the first bit (bit 0, byte 0) is Sunday, 00:00:00 - 00-00:59; bit 1,
    // byte 0 is Sunday, 00:01:00 - 00:01:59, etc.  A NULL pointer means
    // DONT_CHANGE for SamSetInformationUser() calls.
    //
    LogonHours: PUCHAR;
  end;
  {$EXTERNALSYM _LOGON_HOURS}
  LOGON_HOURS = _LOGON_HOURS;
  {$EXTERNALSYM LOGON_HOURS}
  TLogonHours = LOGON_HOURS;
  PLogonHours = PLOGON_HOURS;

  PSR_SECURITY_DESCRIPTOR = ^SR_SECURITY_DESCRIPTOR;
  {$EXTERNALSYM PSR_SECURITY_DESCRIPTOR}
  _SR_SECURITY_DESCRIPTOR = record
    Length: ULONG;
    SecurityDescriptor: PUCHAR;
  end;
  {$EXTERNALSYM _SR_SECURITY_DESCRIPTOR}
  SR_SECURITY_DESCRIPTOR = _SR_SECURITY_DESCRIPTOR;
  {$EXTERNALSYM SR_SECURITY_DESCRIPTOR}
  TSrSecurityDescriptor = SR_SECURITY_DESCRIPTOR;
  PSrSecurityDescriptor = PSR_SECURITY_DESCRIPTOR;

// #include "pshpack4.h"

  PUSER_ALL_INFORMATION = ^USER_ALL_INFORMATION;
  {$EXTERNALSYM PUSER_ALL_INFORMATION}
  _USER_ALL_INFORMATION = record
    LastLogon: LARGE_INTEGER;
    LastLogoff: LARGE_INTEGER;
    PasswordLastSet: LARGE_INTEGER;
    AccountExpires: LARGE_INTEGER;
    PasswordCanChange: LARGE_INTEGER;
    PasswordMustChange: LARGE_INTEGER;
    UserName: UNICODE_STRING;
    FullName: UNICODE_STRING;
    HomeDirectory: UNICODE_STRING;
    HomeDirectoryDrive: UNICODE_STRING;
    ScriptPath: UNICODE_STRING;
    ProfilePath: UNICODE_STRING;
    AdminComment: UNICODE_STRING;
    WorkStations: UNICODE_STRING;
    UserComment: UNICODE_STRING;
    Parameters: UNICODE_STRING;
    LmPassword: UNICODE_STRING;
    NtPassword: UNICODE_STRING;
    PrivateData: UNICODE_STRING;
    SecurityDescriptor: SR_SECURITY_DESCRIPTOR;
    UserId: ULONG;
    PrimaryGroupId: ULONG;
    UserAccountControl: ULONG;
    WhichFields: ULONG;
    LogonHours: LOGON_HOURS;
    BadPasswordCount: USHORT;
    LogonCount: USHORT;
    CountryCode: USHORT;
    CodePage: USHORT;
    LmPasswordPresent: ByteBool;
    NtPasswordPresent: ByteBool;
    PasswordExpired: ByteBool;
    PrivateDataSensitive: ByteBool;
  end;
  {$EXTERNALSYM _USER_ALL_INFORMATION}
  USER_ALL_INFORMATION = _USER_ALL_INFORMATION;
  {$EXTERNALSYM USER_ALL_INFORMATION}
  TUserAllInformation = USER_ALL_INFORMATION;
  PUserAllInformation = PUSER_ALL_INFORMATION;

// #include "poppack.h"

const
  USER_ALL_PARAMETERS = $00200000;
  {$EXTERNALSYM USER_ALL_PARAMETERS}

  CLEAR_BLOCK_LENGTH = 8;
  {$EXTERNALSYM CLEAR_BLOCK_LENGTH}

type
  PCLEAR_BLOCK = ^CLEAR_BLOCK;
  {$EXTERNALSYM PCLEAR_BLOCK}
  _CLEAR_BLOCK = record
    data: array [0..CLEAR_BLOCK_LENGTH - 1] of CHAR;
  end;
  {$EXTERNALSYM _CLEAR_BLOCK}
  CLEAR_BLOCK = _CLEAR_BLOCK;
  {$EXTERNALSYM CLEAR_BLOCK}
  TClearBlock = CLEAR_BLOCK;
  PClearBlock = PCLEAR_BLOCK;

const
  CYPHER_BLOCK_LENGTH = 8;
  {$EXTERNALSYM CYPHER_BLOCK_LENGTH}

type
  PCYPHER_BLOCK = ^CYPHER_BLOCK;
  {$EXTERNALSYM PCYPHER_BLOCK}
  _CYPHER_BLOCK = record
    data: array [0..CYPHER_BLOCK_LENGTH - 1] of CHAR;
  end;
  {$EXTERNALSYM _CYPHER_BLOCK}
  CYPHER_BLOCK = _CYPHER_BLOCK;
  {$EXTERNALSYM CYPHER_BLOCK}
  TCypherBlock = CYPHER_BLOCK;
  PCypherBlock = PCYPHER_BLOCK;

  PLM_OWF_PASSWORD = ^LM_OWF_PASSWORD;
  {$EXTERNALSYM PLM_OWF_PASSWORD}
  _LM_OWF_PASSWORD = record
    data: array [0..1] of CYPHER_BLOCK;
  end;
  {$EXTERNALSYM _LM_OWF_PASSWORD}
  LM_OWF_PASSWORD = _LM_OWF_PASSWORD;
  {$EXTERNALSYM LM_OWF_PASSWORD}
  TLmOwfPassword = LM_OWF_PASSWORD;
  PLmOwfPassword = PLM_OWF_PASSWORD;

  LM_CHALLENGE = CLEAR_BLOCK;
  {$EXTERNALSYM LM_CHALLENGE}
  PLM_CHALLENGE = ^LM_CHALLENGE;
  {$EXTERNALSYM PLM_CHALLENGE}
  NT_OWF_PASSWORD = LM_OWF_PASSWORD;
  {$EXTERNALSYM NT_OWF_PASSWORD}
  PNT_OWF_PASSWORD = ^NT_OWF_PASSWORD;
  {$EXTERNALSYM PNT_OWF_PASSWORD}
  NT_CHALLENGE = LM_CHALLENGE;
  {$EXTERNALSYM NT_CHALLENGE}
  PNT_CHALLENGE = ^NT_CHALLENGE;
  {$EXTERNALSYM PNT_CHALLENGE}

const
  USER_SESSION_KEY_LENGTH = (CYPHER_BLOCK_LENGTH * 2);
  {$EXTERNALSYM USER_SESSION_KEY_LENGTH}

type
  PUSER_SESSION_KEY = ^USER_SESSION_KEY;
  {$EXTERNALSYM PUSER_SESSION_KEY}
  _USER_SESSION_KEY = record
    data: array [0..1] of CYPHER_BLOCK;
  end;
  {$EXTERNALSYM _USER_SESSION_KEY}
  USER_SESSION_KEY = _USER_SESSION_KEY;
  {$EXTERNALSYM USER_SESSION_KEY}
  TUserSessionKey = USER_SESSION_KEY;
  PUserSessionKey = PUSER_SESSION_KEY;

  _NETLOGON_LOGON_INFO_CLASS = (
    NetlogonFiller0,
    NetlogonInteractiveInformation,
    NetlogonNetworkInformation,
    NetlogonServiceInformation,
    NetlogonGenericInformation,
    NetlogonInteractiveTransitiveInformation,
    NetlogonNetworkTransitiveInformation,
    NetlogonServiceTransitiveInformation);
  {$EXTERNALSYM _NETLOGON_LOGON_INFO_CLASS}
  NETLOGON_LOGON_INFO_CLASS = _NETLOGON_LOGON_INFO_CLASS;
  {$EXTERNALSYM NETLOGON_LOGON_INFO_CLASS}

  PNETLOGON_LOGON_IDENTITY_INFO = ^NETLOGON_LOGON_IDENTITY_INFO;
  {$EXTERNALSYM PNETLOGON_LOGON_IDENTITY_INFO}
  _NETLOGON_LOGON_IDENTITY_INFO = record
    LogonDomainName: UNICODE_STRING;
    ParameterControl: ULONG;
    LogonId: OLD_LARGE_INTEGER;
    UserName: UNICODE_STRING;
    Workstation: UNICODE_STRING;
  end;
  {$EXTERNALSYM _NETLOGON_LOGON_IDENTITY_INFO}
  NETLOGON_LOGON_IDENTITY_INFO = _NETLOGON_LOGON_IDENTITY_INFO;
  {$EXTERNALSYM NETLOGON_LOGON_IDENTITY_INFO}
  TNetlogonLogonIdentityInfo = NETLOGON_LOGON_IDENTITY_INFO;
  PNetlogonLogonIdentityInfo = PNETLOGON_LOGON_IDENTITY_INFO;

  PNETLOGON_INTERACTIVE_INFO = ^NETLOGON_INTERACTIVE_INFO;
  {$EXTERNALSYM PNETLOGON_INTERACTIVE_INFO}
  _NETLOGON_INTERACTIVE_INFO = record
    Identity: NETLOGON_LOGON_IDENTITY_INFO;
    LmOwfPassword: LM_OWF_PASSWORD;
    NtOwfPassword: NT_OWF_PASSWORD;
  end;
  {$EXTERNALSYM _NETLOGON_INTERACTIVE_INFO}
  NETLOGON_INTERACTIVE_INFO = _NETLOGON_INTERACTIVE_INFO;
  {$EXTERNALSYM NETLOGON_INTERACTIVE_INFO}
  TNetlogonInteractiveInfo = NETLOGON_INTERACTIVE_INFO;
  PNetlogonInteractiveInfo = PNETLOGON_INTERACTIVE_INFO;

  PNETLOGON_SERVICE_INFO = ^NETLOGON_SERVICE_INFO;
  {$EXTERNALSYM PNETLOGON_SERVICE_INFO}
  _NETLOGON_SERVICE_INFO = record
    Identity: NETLOGON_LOGON_IDENTITY_INFO;
    LmOwfPassword: LM_OWF_PASSWORD;
    NtOwfPassword: NT_OWF_PASSWORD;
  end;
  {$EXTERNALSYM _NETLOGON_SERVICE_INFO}
  NETLOGON_SERVICE_INFO = _NETLOGON_SERVICE_INFO;
  {$EXTERNALSYM NETLOGON_SERVICE_INFO}
  TNetlogonServiceInfo = NETLOGON_SERVICE_INFO;
  PNetlogonServiceInfo = PNETLOGON_SERVICE_INFO;

  PNETLOGON_NETWORK_INFO = ^NETLOGON_NETWORK_INFO;
  {$EXTERNALSYM PNETLOGON_NETWORK_INFO}
  _NETLOGON_NETWORK_INFO = record
    Identity: NETLOGON_LOGON_IDENTITY_INFO;
    LmChallenge: LM_CHALLENGE;
    NtChallengeResponse: STRING;
    LmChallengeResponse: STRING;
  end;
  {$EXTERNALSYM _NETLOGON_NETWORK_INFO}
  NETLOGON_NETWORK_INFO = _NETLOGON_NETWORK_INFO;
  {$EXTERNALSYM NETLOGON_NETWORK_INFO}
  TNetlogonNetworkInfo = NETLOGON_NETWORK_INFO;
  PNetlogonNetworkInfo = PNETLOGON_NETWORK_INFO;

  PNETLOGON_GENERIC_INFO = ^NETLOGON_GENERIC_INFO;
  {$EXTERNALSYM PNETLOGON_GENERIC_INFO}
  _NETLOGON_GENERIC_INFO = record
    Identity: NETLOGON_LOGON_IDENTITY_INFO;
    PackageName: UNICODE_STRING;
    DataLength: ULONG;
    LogonData: PUCHAR;
  end;
  {$EXTERNALSYM _NETLOGON_GENERIC_INFO}
  NETLOGON_GENERIC_INFO = _NETLOGON_GENERIC_INFO;
  {$EXTERNALSYM NETLOGON_GENERIC_INFO}
  TNetlogonGenericInfo = NETLOGON_GENERIC_INFO;
  PNetlogonGenericInfo = PNETLOGON_GENERIC_INFO;

// Values for Flags

const
  MSV1_0_PASSTHRU    = $01;
  {$EXTERNALSYM MSV1_0_PASSTHRU}
  MSV1_0_GUEST_LOGON = $02;
  {$EXTERNALSYM MSV1_0_GUEST_LOGON}

//function Msv1_0SubAuthenticationRoutine(LogonLevel: NETLOGON_LOGON_INFO_CLASS;
//  LogonInformation: PVOID; Flags: ULONG; UserAll: PUSER_ALL_INFORMATION;
//  WhichFields, UserFlags: PULONG; Authoritative: PBOOLEAN; LogoffTime,
//  KickoffTime: PLARGE_INTEGER): NTSTATUS; stdcall;
//{$EXTERNALSYM Msv1_0SubAuthenticationRoutine}

type
  PMSV1_0_VALIDATION_INFO = ^MSV1_0_VALIDATION_INFO;
  {$EXTERNALSYM PMSV1_0_VALIDATION_INFO}
  _MSV1_0_VALIDATION_INFO = record
    LogoffTime: LARGE_INTEGER;
    KickoffTime: LARGE_INTEGER;
    LogonServer: UNICODE_STRING;
    LogonDomainName: UNICODE_STRING;
    SessionKey: USER_SESSION_KEY;
    Authoritative: ByteBool;
    UserFlags: ULONG;
    WhichFields: ULONG;
    UserId: ULONG;
  end;
  {$EXTERNALSYM _MSV1_0_VALIDATION_INFO}
  MSV1_0_VALIDATION_INFO = _MSV1_0_VALIDATION_INFO;
  {$EXTERNALSYM MSV1_0_VALIDATION_INFO}
  TMsv10ValidationInfo = MSV1_0_VALIDATION_INFO;
  PMsv10ValidationInfo = PMSV1_0_VALIDATION_INFO;

// values for WhichFields

const
  MSV1_0_VALIDATION_LOGOFF_TIME  = $00000001;
  {$EXTERNALSYM MSV1_0_VALIDATION_LOGOFF_TIME}
  MSV1_0_VALIDATION_KICKOFF_TIME = $00000002;
  {$EXTERNALSYM MSV1_0_VALIDATION_KICKOFF_TIME}
  MSV1_0_VALIDATION_LOGON_SERVER = $00000004;
  {$EXTERNALSYM MSV1_0_VALIDATION_LOGON_SERVER}
  MSV1_0_VALIDATION_LOGON_DOMAIN = $00000008;
  {$EXTERNALSYM MSV1_0_VALIDATION_LOGON_DOMAIN}
  MSV1_0_VALIDATION_SESSION_KEY  = $00000010;
  {$EXTERNALSYM MSV1_0_VALIDATION_SESSION_KEY}
  MSV1_0_VALIDATION_USER_FLAGS   = $00000020;
  {$EXTERNALSYM MSV1_0_VALIDATION_USER_FLAGS}
  MSV1_0_VALIDATION_USER_ID      = $00000040;
  {$EXTERNALSYM MSV1_0_VALIDATION_USER_ID}

// legal values for ActionsPerformed

  MSV1_0_SUBAUTH_ACCOUNT_DISABLED = $00000001;
  {$EXTERNALSYM MSV1_0_SUBAUTH_ACCOUNT_DISABLED}
  MSV1_0_SUBAUTH_PASSWORD         = $00000002;
  {$EXTERNALSYM MSV1_0_SUBAUTH_PASSWORD}
  MSV1_0_SUBAUTH_WORKSTATIONS     = $00000004;
  {$EXTERNALSYM MSV1_0_SUBAUTH_WORKSTATIONS}
  MSV1_0_SUBAUTH_LOGON_HOURS      = $00000008;
  {$EXTERNALSYM MSV1_0_SUBAUTH_LOGON_HOURS}
  MSV1_0_SUBAUTH_ACCOUNT_EXPIRY   = $00000010;
  {$EXTERNALSYM MSV1_0_SUBAUTH_ACCOUNT_EXPIRY}
  MSV1_0_SUBAUTH_PASSWORD_EXPIRY  = $00000020;
  {$EXTERNALSYM MSV1_0_SUBAUTH_PASSWORD_EXPIRY}
  MSV1_0_SUBAUTH_ACCOUNT_TYPE     = $00000040;
  {$EXTERNALSYM MSV1_0_SUBAUTH_ACCOUNT_TYPE}
  MSV1_0_SUBAUTH_LOCKOUT          = $00000080;
  {$EXTERNALSYM MSV1_0_SUBAUTH_LOCKOUT}

//function Msv1_0SubAuthenticationRoutineEx(LogonLevel: NETLOGON_LOGON_INFO_CLASS;
//  LogonInformation: PVOID; Flags: ULONG; UserAll: PUSER_ALL_INFORMATION;
//  UserHandle: SAM_HANDLE; ValidationInfo: PMSV1_0_VALIDATION_INFO;
//  ActionsPerformed: PULONG): NTSTATUS; stdcall;
//{$EXTERNALSYM Msv1_0SubAuthenticationRoutineEx}

//function Msv1_0SubAuthenticationRoutineGeneric(SubmitBuffer: PVOID;
//  SubmitBufferLength: ULONG; ReturnBufferLength: PULONG;
//  ReturnBuffer: PPVOID): NTSTATUS; stdcall;
//{$EXTERNALSYM Msv1_0SubAuthenticationRoutineGeneric}

//function Msv1_0SubAuthenticationFilter(LogonLevel: NETLOGON_LOGON_INFO_CLASS;
//  LogonInformation: PVOID; Flags: ULONG; UserAll: PUSER_ALL_INFORMATION;
//  WhichFields, UserFlags: PULONG; Authoritative: PBOOLEAN; LogoffTime,
//  KickoffTime: PLARGE_INTEGER): NTSTATUS; stdcall;
//{$EXTERNALSYM Msv1_0SubAuthenticationFilter}

const
  STATUS_SUCCESS                = NTSTATUS($00000000);
  {$EXTERNALSYM STATUS_SUCCESS}
  STATUS_INVALID_INFO_CLASS     = NTSTATUS($C0000003);
  {$EXTERNALSYM STATUS_INVALID_INFO_CLASS}
  STATUS_NO_SUCH_USER           = NTSTATUS($C0000064);
  {$EXTERNALSYM STATUS_NO_SUCH_USER}
  STATUS_WRONG_PASSWORD         = NTSTATUS($C000006A);
  {$EXTERNALSYM STATUS_WRONG_PASSWORD}
  STATUS_PASSWORD_RESTRICTION   = NTSTATUS($C000006C);
  {$EXTERNALSYM STATUS_PASSWORD_RESTRICTION}
  STATUS_LOGON_FAILURE          = NTSTATUS($C000006D);
  {$EXTERNALSYM STATUS_LOGON_FAILURE}
  STATUS_ACCOUNT_RESTRICTION    = NTSTATUS($C000006E);
  {$EXTERNALSYM STATUS_ACCOUNT_RESTRICTION}
  STATUS_INVALID_LOGON_HOURS    = NTSTATUS($C000006F);
  {$EXTERNALSYM STATUS_INVALID_LOGON_HOURS}
  STATUS_INVALID_WORKSTATION    = NTSTATUS($C0000070);
  {$EXTERNALSYM STATUS_INVALID_WORKSTATION}
  STATUS_PASSWORD_EXPIRED       = NTSTATUS($C0000071);
  {$EXTERNALSYM STATUS_PASSWORD_EXPIRED}
  STATUS_ACCOUNT_DISABLED       = NTSTATUS($C0000072);
  {$EXTERNALSYM STATUS_ACCOUNT_DISABLED}
  STATUS_INSUFFICIENT_RESOURCES = NTSTATUS($C000009A);
  {$EXTERNALSYM STATUS_INSUFFICIENT_RESOURCES}
  STATUS_ACCOUNT_EXPIRED        = NTSTATUS($C0000193);
  {$EXTERNALSYM STATUS_ACCOUNT_EXPIRED}
  STATUS_PASSWORD_MUST_CHANGE   = NTSTATUS($C0000224);
  {$EXTERNALSYM STATUS_PASSWORD_MUST_CHANGE}
  STATUS_ACCOUNT_LOCKED_OUT     = NTSTATUS($C0000234);
  {$EXTERNALSYM STATUS_ACCOUNT_LOCKED_OUT}

implementation

end.
