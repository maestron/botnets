{******************************************************************************}
{                                                       	               }
{ Security Descriptor Definition Language API interface Unit for Object Pascal }
{                                                       	               }
{ Portions created by Microsoft are Copyright (C) 1995-2001 Microsoft          }
{ Corporation. All Rights Reserved.                                            }
{ 								               }
{ The original file is: sddl.h, released June 2000. The original Pascal        }
{ code is: Sddl.pas, released December 2000. The initial developer of the      }
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

unit JwaSddl;

{$WEAKPACKAGEUNIT}

{$HPPEMIT ''}
{$HPPEMIT '#include "sddl.h"'}
{$HPPEMIT ''}

{$I WINDEFINES.INC}

interface

uses
  JwaWinNT, JwaWinType;

//
// SDDL Version information
//

const
  SDDL_REVISION_1 = 1;
  {$EXTERNALSYM SDDL_REVISION_1}
  SDDL_REVISION   = SDDL_REVISION_1;
  {$EXTERNALSYM SDDL_REVISION}

//
// SDDL Component tags
//

  SDDL_OWNER = 'O'; // Owner tag
  {$EXTERNALSYM SDDL_OWNER}
  SDDL_GROUP = 'G'; // Group tag
  {$EXTERNALSYM SDDL_GROUP}
  SDDL_DACL  = 'D'; // DACL tag
  {$EXTERNALSYM SDDL_DACL}
  SDDL_SACL  = 'S'; // SACL tag
  {$EXTERNALSYM SDDL_SACL}

//
// SDDL Security descriptor controls
//

  SDDL_PROTECTED        = 'P'; // DACL or SACL Protected
  {$EXTERNALSYM SDDL_PROTECTED}
  SDDL_AUTO_INHERIT_REQ = 'AR'; // Auto inherit request
  {$EXTERNALSYM SDDL_AUTO_INHERIT_REQ}
  SDDL_AUTO_INHERITED   = 'AI'; // DACL/SACL are auto inherited
  {$EXTERNALSYM SDDL_AUTO_INHERITED}

//
// SDDL Ace types
//

  SDDL_ACCESS_ALLOWED        = 'A'; // Access allowed
  {$EXTERNALSYM SDDL_ACCESS_ALLOWED}
  SDDL_ACCESS_DENIED         = 'D'; // Access denied
  {$EXTERNALSYM SDDL_ACCESS_DENIED}
  SDDL_OBJECT_ACCESS_ALLOWED = 'OA'; // Object access allowed
  {$EXTERNALSYM SDDL_OBJECT_ACCESS_ALLOWED}
  SDDL_OBJECT_ACCESS_DENIED  = 'OD'; // Object access denied
  {$EXTERNALSYM SDDL_OBJECT_ACCESS_DENIED}
  SDDL_AUDIT                 = 'AU'; // Audit
  {$EXTERNALSYM SDDL_AUDIT}
  SDDL_ALARM                 = 'AL'; // Alarm
  {$EXTERNALSYM SDDL_ALARM}
  SDDL_OBJECT_AUDIT          = 'OU'; // Object audit
  {$EXTERNALSYM SDDL_OBJECT_AUDIT}
  SDDL_OBJECT_ALARM          = 'OL'; // Object alarm
  {$EXTERNALSYM SDDL_OBJECT_ALARM}

//
// SDDL Ace flags
//

  SDDL_CONTAINER_INHERIT = 'CI'; // Container inherit
  {$EXTERNALSYM SDDL_CONTAINER_INHERIT}
  SDDL_OBJECT_INHERIT    = 'OI'; // Object inherit
  {$EXTERNALSYM SDDL_OBJECT_INHERIT}
  SDDL_NO_PROPAGATE      = 'NP'; // Inherit no propagate
  {$EXTERNALSYM SDDL_NO_PROPAGATE}
  SDDL_INHERIT_ONLY      = 'IO'; // Inherit only
  {$EXTERNALSYM SDDL_INHERIT_ONLY}
  SDDL_INHERITED         = 'ID'; // Inherited
  {$EXTERNALSYM SDDL_INHERITED}
  SDDL_AUDIT_SUCCESS     = 'SA'; // Audit success
  {$EXTERNALSYM SDDL_AUDIT_SUCCESS}
  SDDL_AUDIT_FAILURE     = 'FA'; // Audit failure
  {$EXTERNALSYM SDDL_AUDIT_FAILURE}

//
// SDDL Rights
//

  SDDL_READ_PROPERTY   = 'RP';
  {$EXTERNALSYM SDDL_READ_PROPERTY}
  SDDL_WRITE_PROPERTY  = 'WP';
  {$EXTERNALSYM SDDL_WRITE_PROPERTY}
  SDDL_CREATE_CHILD    = 'CC';
  {$EXTERNALSYM SDDL_CREATE_CHILD}
  SDDL_DELETE_CHILD    = 'DC';
  {$EXTERNALSYM SDDL_DELETE_CHILD}
  SDDL_LIST_CHILDREN   = 'LC';
  {$EXTERNALSYM SDDL_LIST_CHILDREN}
  SDDL_SELF_WRITE      = 'SW';
  {$EXTERNALSYM SDDL_SELF_WRITE}
  SDDL_LIST_OBJECT     = 'LO';
  {$EXTERNALSYM SDDL_LIST_OBJECT}
  SDDL_DELETE_TREE     = 'DT';
  {$EXTERNALSYM SDDL_DELETE_TREE}
  SDDL_CONTROL_ACCESS  = 'CR';
  {$EXTERNALSYM SDDL_CONTROL_ACCESS}
  SDDL_READ_CONTROL    = 'RC';
  {$EXTERNALSYM SDDL_READ_CONTROL}
  SDDL_WRITE_DAC       = 'WD';
  {$EXTERNALSYM SDDL_WRITE_DAC}
  SDDL_WRITE_OWNER     = 'WO';
  {$EXTERNALSYM SDDL_WRITE_OWNER}
  SDDL_STANDARD_DELETE = 'SD';
  {$EXTERNALSYM SDDL_STANDARD_DELETE}
  SDDL_GENERIC_ALL     = 'GA';
  {$EXTERNALSYM SDDL_GENERIC_ALL}
  SDDL_GENERIC_READ    = 'GR';
  {$EXTERNALSYM SDDL_GENERIC_READ}
  SDDL_GENERIC_WRITE   = 'GW';
  {$EXTERNALSYM SDDL_GENERIC_WRITE}
  SDDL_GENERIC_EXECUTE = 'GX';
  {$EXTERNALSYM SDDL_GENERIC_EXECUTE}
  SDDL_FILE_ALL        = 'FA';
  {$EXTERNALSYM SDDL_FILE_ALL}
  SDDL_FILE_READ       = 'FR';
  {$EXTERNALSYM SDDL_FILE_READ}
  SDDL_FILE_WRITE      = 'FW';
  {$EXTERNALSYM SDDL_FILE_WRITE}
  SDDL_FILE_EXECUTE    = 'FX';
  {$EXTERNALSYM SDDL_FILE_EXECUTE}
  SDDL_KEY_ALL         = 'KA';
  {$EXTERNALSYM SDDL_KEY_ALL}
  SDDL_KEY_READ        = 'KR';
  {$EXTERNALSYM SDDL_KEY_READ}
  SDDL_KEY_WRITE       = 'KW';
  {$EXTERNALSYM SDDL_KEY_WRITE}
  SDDL_KEY_EXECUTE     = 'KX';
  {$EXTERNALSYM SDDL_KEY_EXECUTE}

//
// SDDL User alias max size
//      - currently, upto two supported eg. "DA"
//      - modify this if more WCHARs need to be there in future e.g. "DAX"
//

  SDDL_ALIAS_SIZE = 2;
  {$EXTERNALSYM SDDL_ALIAS_SIZE}

//
// SDDL User aliases
//

  SDDL_DOMAIN_ADMINISTRATORS         = 'DA'; // Domain admins
  {$EXTERNALSYM SDDL_DOMAIN_ADMINISTRATORS}
  SDDL_DOMAIN_GUESTS                 = 'DG'; // Domain guests
  {$EXTERNALSYM SDDL_DOMAIN_GUESTS}
  SDDL_DOMAIN_USERS                  = 'DU'; // Domain users
  {$EXTERNALSYM SDDL_DOMAIN_USERS}
  SDDL_ENTERPRISE_DOMAIN_CONTROLLERS = 'ED'; // Enterprise domain controllers
  {$EXTERNALSYM SDDL_ENTERPRISE_DOMAIN_CONTROLLERS}
  SDDL_DOMAIN_DOMAIN_CONTROLLERS     = 'DD'; // Domain domain controllers
  {$EXTERNALSYM SDDL_DOMAIN_DOMAIN_CONTROLLERS}
  SDDL_DOMAIN_COMPUTERS              = 'DC'; // Domain computers
  {$EXTERNALSYM SDDL_DOMAIN_COMPUTERS}
  SDDL_BUILTIN_ADMINISTRATORS        = 'BA'; // Builtin (local ) administrators
  {$EXTERNALSYM SDDL_BUILTIN_ADMINISTRATORS}
  SDDL_BUILTIN_GUESTS                = 'BG'; // Builtin (local ) guests
  {$EXTERNALSYM SDDL_BUILTIN_GUESTS}
  SDDL_BUILTIN_USERS                 = 'BU'; // Builtin (local ) users
  {$EXTERNALSYM SDDL_BUILTIN_USERS}
  SDDL_LOCAL_ADMIN                   = 'LA'; // Local administrator account
  {$EXTERNALSYM SDDL_LOCAL_ADMIN}
  SDDL_LOCAL_GUEST                   = 'LG'; // Local group account
  {$EXTERNALSYM SDDL_LOCAL_GUEST}
  SDDL_ACCOUNT_OPERATORS             = 'AO'; // Account operators
  {$EXTERNALSYM SDDL_ACCOUNT_OPERATORS}
  SDDL_BACKUP_OPERATORS              = 'BO'; // Backup operators
  {$EXTERNALSYM SDDL_BACKUP_OPERATORS}
  SDDL_PRINTER_OPERATORS             = 'PO'; // Printer operators
  {$EXTERNALSYM SDDL_PRINTER_OPERATORS}
  SDDL_SERVER_OPERATORS              = 'SO'; // Server operators
  {$EXTERNALSYM SDDL_SERVER_OPERATORS}
  SDDL_AUTHENTICATED_USERS           = 'AU'; // Authenticated users
  {$EXTERNALSYM SDDL_AUTHENTICATED_USERS}
  SDDL_PERSONAL_SELF                 = 'PS'; // Personal self
  {$EXTERNALSYM SDDL_PERSONAL_SELF}
  SDDL_CREATOR_OWNER                 = 'CO'; // Creator owner
  {$EXTERNALSYM SDDL_CREATOR_OWNER}
  SDDL_CREATOR_GROUP                 = 'CG'; // Creator group
  {$EXTERNALSYM SDDL_CREATOR_GROUP}
  SDDL_LOCAL_SYSTEM                  = 'SY'; // Local system
  {$EXTERNALSYM SDDL_LOCAL_SYSTEM}
  SDDL_POWER_USERS                   = 'PU'; // Power users
  {$EXTERNALSYM SDDL_POWER_USERS}
  SDDL_EVERYONE                      = 'WD'; // Everyone ( World )
  {$EXTERNALSYM SDDL_EVERYONE}
  SDDL_REPLICATOR                    = 'RE'; // Replicator
  {$EXTERNALSYM SDDL_REPLICATOR}
  SDDL_INTERACTIVE                   = 'IU'; // Interactive logon user
  {$EXTERNALSYM SDDL_INTERACTIVE}
  SDDL_NETWORK                       = 'NU'; // Nework logon user
  {$EXTERNALSYM SDDL_NETWORK}
  SDDL_SERVICE                       = 'SU'; // Service logon user
  {$EXTERNALSYM SDDL_SERVICE}
  SDDL_RESTRICTED_CODE               = 'RC'; // Restricted code
  {$EXTERNALSYM SDDL_RESTRICTED_CODE}
  SDDL_ANONYMOUS                     = 'AN'; // Anonymous Logon
  {$EXTERNALSYM SDDL_ANONYMOUS}
  SDDL_SCHEMA_ADMINISTRATORS         = 'SA'; // Schema Administrators
  {$EXTERNALSYM SDDL_SCHEMA_ADMINISTRATORS}
  SDDL_CERT_SERV_ADMINISTRATORS      = 'CA'; // Certificate Server Administrators
  {$EXTERNALSYM SDDL_CERT_SERV_ADMINISTRATORS}
  SDDL_RAS_SERVERS                   = 'RS'; // RAS servers group
  {$EXTERNALSYM SDDL_RAS_SERVERS}
  SDDL_ENTERPRISE_ADMINS             = 'EA'; // Enterprise administrators
  {$EXTERNALSYM SDDL_ENTERPRISE_ADMINS}
  SDDL_GROUP_POLICY_ADMINS           = 'PA'; // Group Policy administrators
  {$EXTERNALSYM SDDL_GROUP_POLICY_ADMINS}
  SDDL_ALIAS_PREW2KCOMPACC           = 'RU'; // alias to allow previous windows 2000
  {$EXTERNALSYM SDDL_ALIAS_PREW2KCOMPACC}
  SDDL_LOCAL_SERVICE                 = 'LS'; // Local service account (for services)
  {$EXTERNALSYM SDDL_LOCAL_SERVICE}
  SDDL_NETWORK_SERVICE               = 'NS'; // Network service account (for services)
  {$EXTERNALSYM SDDL_NETWORK_SERVICE}
  SDDL_REMOTE_DESKTOP                = 'RD'; // Remote desktop users (for terminal server)
  {$EXTERNALSYM SDDL_REMOTE_DESKTOP}
  SDDL_NETWORK_CONFIGURATION_OPS     = 'NO'; // Network configuration operators ( to manage configuration of networking features)
  {$EXTERNALSYM SDDL_NETWORK_CONFIGURATION_OPS}
  SDDL_PERFMON_USERS                 = 'MU'; // Performance Monitor Users
  {$EXTERNALSYM SDDL_PERFMON_USERS}
  SDDL_PERFLOG_USERS                 = 'LU'; // Performance Log Users
  {$EXTERNALSYM SDDL_PERFLOG_USERS}

//
// SDDL Seperators - character version
//

  SDDL_SEPERATORC   = ';';
  {$EXTERNALSYM SDDL_SEPERATORC}
  SDDL_DELIMINATORC = ':';
  {$EXTERNALSYM SDDL_DELIMINATORC}
  SDDL_ACE_BEGINC   = '(';
  {$EXTERNALSYM SDDL_ACE_BEGINC}
  SDDL_ACE_ENDC     = ')';
  {$EXTERNALSYM SDDL_ACE_ENDC}

//
// SDDL Seperators - string version
//

  SDDL_SEPERATOR   = ';';
  {$EXTERNALSYM SDDL_SEPERATOR}
  SDDL_DELIMINATOR = ':';
  {$EXTERNALSYM SDDL_DELIMINATOR}
  SDDL_ACE_BEGIN   = '(';
  {$EXTERNALSYM SDDL_ACE_BEGIN}
  SDDL_ACE_END     = ')';
  {$EXTERNALSYM SDDL_ACE_END}

function ConvertSidToStringSidA(Sid: PSID; var StringSid: LPSTR): BOOL; stdcall;
{$EXTERNALSYM ConvertSidToStringSidA}
function ConvertSidToStringSidW(Sid: PSID; var StringSid: LPWSTR): BOOL; stdcall;
{$EXTERNALSYM ConvertSidToStringSidW}

{$IFDEF UNICODE}
function ConvertSidToStringSid(Sid: PSID; var StringSid: LPWSTR): BOOL; stdcall;
{$EXTERNALSYM ConvertSidToStringSid}
{$ELSE}
function ConvertSidToStringSid(Sid: PSID; var StringSid: LPSTR): BOOL; stdcall;
{$EXTERNALSYM ConvertSidToStringSid}
{$ENDIF}

function ConvertStringSidToSidA(StringSid: LPCSTR; var Sid: PSID): BOOL; stdcall;
{$EXTERNALSYM ConvertStringSidToSidA}
function ConvertStringSidToSidW(StringSid: LPCWSTR; var Sid: PSID): BOOL; stdcall;
{$EXTERNALSYM ConvertStringSidToSidW}

{$IFDEF UNICODE}
function ConvertStringSidToSid(StringSid: LPCWSTR; var Sid: PSID): BOOL; stdcall;
{$EXTERNALSYM ConvertStringSidToSid}
{$ELSE}
function ConvertStringSidToSid(StringSid: LPCSTR; var Sid: PSID): BOOL; stdcall;
{$EXTERNALSYM ConvertStringSidToSid}
{$ENDIF}

function ConvertStringSecurityDescriptorToSecurityDescriptorA(StringSecurityDescriptor: LPCSTR;
  StringSDRevision: DWORD; var SecurityDescriptor: PSECURITY_DESCRIPTOR;
  SecurityDescriptorSize: PULONG): BOOL; stdcall;
{$EXTERNALSYM ConvertStringSecurityDescriptorToSecurityDescriptorA}
function ConvertStringSecurityDescriptorToSecurityDescriptorW(StringSecurityDescriptor: LPCWSTR;
  StringSDRevision: DWORD; var SecurityDescriptor: PSECURITY_DESCRIPTOR;
  SecurityDescriptorSize: PULONG): BOOL; stdcall;
{$EXTERNALSYM ConvertStringSecurityDescriptorToSecurityDescriptorW}

{$IFDEF UNICODE}
function ConvertStringSecurityDescriptorToSecurityDescriptor(StringSecurityDescriptor: LPCWSTR;
  StringSDRevision: DWORD; var SecurityDescriptor: PSECURITY_DESCRIPTOR;
  SecurityDescriptorSize: PULONG): BOOL; stdcall;
{$EXTERNALSYM ConvertStringSecurityDescriptorToSecurityDescriptor}
{$ELSE}
function ConvertStringSecurityDescriptorToSecurityDescriptor(StringSecurityDescriptor: LPCSTR;
  StringSDRevision: DWORD; var SecurityDescriptor: PSECURITY_DESCRIPTOR;
  SecurityDescriptorSize: PULONG): BOOL; stdcall;
{$EXTERNALSYM ConvertStringSecurityDescriptorToSecurityDescriptor}
{$ENDIF}

function ConvertSecurityDescriptorToStringSecurityDescriptorA(
  SecurityDescriptor: PSECURITY_DESCRIPTOR; RequestedStringSDRevision: DWORD;
  SecurityInformation: SECURITY_INFORMATION; var StringSecurityDescriptor: LPSTR;
  StringSecurityDescriptorLen: PULONG): BOOL; stdcall;
{$EXTERNALSYM ConvertSecurityDescriptorToStringSecurityDescriptorA}
function ConvertSecurityDescriptorToStringSecurityDescriptorW(
  SecurityDescriptor: PSECURITY_DESCRIPTOR; RequestedStringSDRevision: DWORD;
  SecurityInformation: SECURITY_INFORMATION; var StringSecurityDescriptor: LPWSTR;
  StringSecurityDescriptorLen: PULONG): BOOL; stdcall;
{$EXTERNALSYM ConvertSecurityDescriptorToStringSecurityDescriptorW}

{$IFDEF UNICODE}
function ConvertSecurityDescriptorToStringSecurityDescriptor(
  SecurityDescriptor: PSECURITY_DESCRIPTOR; RequestedStringSDRevision: DWORD;
  SecurityInformation: SECURITY_INFORMATION; var StringSecurityDescriptor: LPWSTR;
  StringSecurityDescriptorLen: PULONG): BOOL; stdcall;
{$EXTERNALSYM ConvertSecurityDescriptorToStringSecurityDescriptor}
{$ELSE}
function ConvertSecurityDescriptorToStringSecurityDescriptor(
  SecurityDescriptor: PSECURITY_DESCRIPTOR; RequestedStringSDRevision: DWORD;
  SecurityInformation: SECURITY_INFORMATION; var StringSecurityDescriptor: LPSTR;
  StringSecurityDescriptorLen: PULONG): BOOL; stdcall;
{$EXTERNALSYM ConvertSecurityDescriptorToStringSecurityDescriptor}
{$ENDIF}

implementation

const
  advapi32 = 'advapi32.dll';


{$IFDEF DYNAMIC_LINK}
var
  _ConvertSidToStringSidA: Pointer;

function ConvertSidToStringSidA;
begin
  GetProcedureAddress(_ConvertSidToStringSidA, advapi32, 'ConvertSidToStringSidA');
  asm
    mov esp, ebp
    pop ebp
    jmp [_ConvertSidToStringSidA]
  end;
end;
{$ELSE}
function ConvertSidToStringSidA; external advapi32 name 'ConvertSidToStringSidA';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _ConvertSidToStringSidW: Pointer;

function ConvertSidToStringSidW;
begin
  GetProcedureAddress(_ConvertSidToStringSidW, advapi32, 'ConvertSidToStringSidW');
  asm
    mov esp, ebp
    pop ebp
    jmp [_ConvertSidToStringSidW]
  end;
end;
{$ELSE}
function ConvertSidToStringSidW; external advapi32 name 'ConvertSidToStringSidW';
{$ENDIF DYNAMIC_LINK}
{$IFDEF UNICODE}

{$IFDEF DYNAMIC_LINK}
var
  _ConvertSidToStringSid: Pointer;

function ConvertSidToStringSid;
begin
  GetProcedureAddress(_ConvertSidToStringSid, advapi32, 'ConvertSidToStringSidW');
  asm
    mov esp, ebp
    pop ebp
    jmp [_ConvertSidToStringSid]
  end;
end;
{$ELSE}
function ConvertSidToStringSid; external advapi32 name 'ConvertSidToStringSidW';
{$ENDIF DYNAMIC_LINK}
{$ELSE}

{$IFDEF DYNAMIC_LINK}
var
  _ConvertSidToStringSid: Pointer;

function ConvertSidToStringSid;
begin
  GetProcedureAddress(_ConvertSidToStringSid, advapi32, 'ConvertSidToStringSidA');
  asm
    mov esp, ebp
    pop ebp
    jmp [_ConvertSidToStringSid]
  end;
end;
{$ELSE}
function ConvertSidToStringSid; external advapi32 name 'ConvertSidToStringSidA';
{$ENDIF DYNAMIC_LINK}
{$ENDIF}

{$IFDEF DYNAMIC_LINK}
var
  _ConvertStringSidToSidA: Pointer;

function ConvertStringSidToSidA;
begin
  GetProcedureAddress(_ConvertStringSidToSidA, advapi32, 'ConvertStringSidToSidA');
  asm
    mov esp, ebp
    pop ebp
    jmp [_ConvertStringSidToSidA]
  end;
end;
{$ELSE}
function ConvertStringSidToSidA; external advapi32 name 'ConvertStringSidToSidA';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _ConvertStringSidToSidW: Pointer;

function ConvertStringSidToSidW;
begin
  GetProcedureAddress(_ConvertStringSidToSidW, advapi32, 'ConvertStringSidToSidW');
  asm
    mov esp, ebp
    pop ebp
    jmp [_ConvertStringSidToSidW]
  end;
end;
{$ELSE}
function ConvertStringSidToSidW; external advapi32 name 'ConvertStringSidToSidW';
{$ENDIF DYNAMIC_LINK}
{$IFDEF UNICODE}

{$IFDEF DYNAMIC_LINK}
var
  _ConvertStringSidToSid: Pointer;

function ConvertStringSidToSid;
begin
  GetProcedureAddress(_ConvertStringSidToSid, advapi32, 'ConvertStringSidToSidW');
  asm
    mov esp, ebp
    pop ebp
    jmp [_ConvertStringSidToSid]
  end;
end;
{$ELSE}
function ConvertStringSidToSid; external advapi32 name 'ConvertStringSidToSidW';
{$ENDIF DYNAMIC_LINK}
{$ELSE}

{$IFDEF DYNAMIC_LINK}
var
  _ConvertStringSidToSid: Pointer;

function ConvertStringSidToSid;
begin
  GetProcedureAddress(_ConvertStringSidToSid, advapi32, 'ConvertStringSidToSidA');
  asm
    mov esp, ebp
    pop ebp
    jmp [_ConvertStringSidToSid]
  end;
end;
{$ELSE}
function ConvertStringSidToSid; external advapi32 name 'ConvertStringSidToSidA';
{$ENDIF DYNAMIC_LINK}
{$ENDIF}

{$IFDEF DYNAMIC_LINK}
var
  _ConvStrSecDescrToSecDescrA: Pointer;

function ConvertStringSecurityDescriptorToSecurityDescriptorA;
begin
  GetProcedureAddress(_ConvStrSecDescrToSecDescrA, advapi32, 'ConvertStringSecurityDescriptorToSecurityDescriptorA');
  asm
    mov esp, ebp
    pop ebp
    jmp [_ConvStrSecDescrToSecDescrA]
  end;
end;
{$ELSE}
function ConvertStringSecurityDescriptorToSecurityDescriptorA; external advapi32 name 'ConvertStringSecurityDescriptorToSecurityDescriptorA';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _ConvStrSecDescrToSecDescrW: Pointer;

function ConvertStringSecurityDescriptorToSecurityDescriptorW;
begin
  GetProcedureAddress(_ConvStrSecDescrToSecDescrW, advapi32, 'ConvertStringSecurityDescriptorToSecurityDescriptorW');
  asm
    mov esp, ebp
    pop ebp
    jmp [_ConvStrSecDescrToSecDescrW]
  end;
end;
{$ELSE}
function ConvertStringSecurityDescriptorToSecurityDescriptorW; external advapi32 name 'ConvertStringSecurityDescriptorToSecurityDescriptorW';
{$ENDIF DYNAMIC_LINK}
{$IFDEF UNICODE}

{$IFDEF DYNAMIC_LINK}
var
  _ConvStrSecDescrToSecDescr: Pointer;

function ConvertStringSecurityDescriptorToSecurityDescriptor;
begin
  GetProcedureAddress(_ConvStrSecDescrToSecDescr, advapi32, 'ConvertStringSecurityDescriptorToSecurityDescriptorW');
  asm
    mov esp, ebp
    pop ebp
    jmp [_ConvStrSecDescrToSecDescr]
  end;
end;
{$ELSE}
function ConvertStringSecurityDescriptorToSecurityDescriptor; external advapi32 name 'ConvertStringSecurityDescriptorToSecurityDescriptorW';
{$ENDIF DYNAMIC_LINK}
{$ELSE}

{$IFDEF DYNAMIC_LINK}
var
  _ConvStrSecDescrToSecDescr: Pointer;

function ConvertStringSecurityDescriptorToSecurityDescriptor;
begin
  GetProcedureAddress(_ConvStrSecDescrToSecDescr, advapi32, 'ConvertStringSecurityDescriptorToSecurityDescriptorA');
  asm
    mov esp, ebp
    pop ebp
    jmp [_ConvStrSecDescrToSecDescr]
  end;
end;
{$ELSE}
function ConvertStringSecurityDescriptorToSecurityDescriptor; external advapi32 name 'ConvertStringSecurityDescriptorToSecurityDescriptorA';
{$ENDIF DYNAMIC_LINK}
{$ENDIF}

{$IFDEF DYNAMIC_LINK}
var
  _ConvSecDescrToStrSecDescrA: Pointer;

function ConvertSecurityDescriptorToStringSecurityDescriptorA;
begin
  GetProcedureAddress(_ConvSecDescrToStrSecDescrA, advapi32, 'ConvertSecurityDescriptorToStringSecurityDescriptorA');
  asm
    mov esp, ebp
    pop ebp
    jmp [_ConvSecDescrToStrSecDescrA]
  end;
end;
{$ELSE}
function ConvertSecurityDescriptorToStringSecurityDescriptorA; external advapi32 name 'ConvertSecurityDescriptorToStringSecurityDescriptorA';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _ConvSecDescrToStrSecDescrW: Pointer;

function ConvertSecurityDescriptorToStringSecurityDescriptorW;
begin
  GetProcedureAddress(_ConvSecDescrToStrSecDescrW, advapi32, 'ConvertSecurityDescriptorToStringSecurityDescriptorW');
  asm
    mov esp, ebp
    pop ebp
    jmp [_ConvSecDescrToStrSecDescrW]
  end;
end;
{$ELSE}
function ConvertSecurityDescriptorToStringSecurityDescriptorW; external advapi32 name 'ConvertSecurityDescriptorToStringSecurityDescriptorW';
{$ENDIF DYNAMIC_LINK}
{$IFDEF UNICODE}

{$IFDEF DYNAMIC_LINK}
var
  _ConvSecDescrToStrSecDescr: Pointer;

function ConvertSecurityDescriptorToStringSecurityDescriptor;
begin
  GetProcedureAddress(_ConvSecDescrToStrSecDescr, advapi32, 'ConvertSecurityDescriptorToStringSecurityDescriptorW');
  asm
    mov esp, ebp
    pop ebp
    jmp [_ConvSecDescrToStrSecDescr]
  end;
end;
{$ELSE}
function ConvertSecurityDescriptorToStringSecurityDescriptor; external advapi32 name 'ConvertSecurityDescriptorToStringSecurityDescriptorW';
{$ENDIF DYNAMIC_LINK}
{$ELSE}

{$IFDEF DYNAMIC_LINK}
var
  _ConvSecDescrToStrSecDescr: Pointer;

function ConvertSecurityDescriptorToStringSecurityDescriptor;
begin
  GetProcedureAddress(_ConvSecDescrToStrSecDescr, advapi32, 'ConvertSecurityDescriptorToStringSecurityDescriptorA');
  asm
    mov esp, ebp
    pop ebp
    jmp [_ConvSecDescrToStrSecDescr]
  end;
end;
{$ELSE}
function ConvertSecurityDescriptorToStringSecurityDescriptor; external advapi32 name 'ConvertSecurityDescriptorToStringSecurityDescriptorA';
{$ENDIF DYNAMIC_LINK}
{$ENDIF}

end.
