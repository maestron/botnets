{******************************************************************************}
{                                                       	               }
{ LSA API interface Unit for Object Pascal                                     }
{                                                       	               }
{ Portions created by Microsoft are Copyright (C) 1995-2001 Microsoft          }
{ Corporation. All Rights Reserved.                                            }
{ 								               }
{ The original file is: ntsecapi.h, released June 2000. The original Pascal    }
{ code is: NtSecApi.pas, released December 2000. The initial developer of the  }
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

unit JwaNtSecApi;

{$WEAKPACKAGEUNIT}

{$HPPEMIT ''}
{$HPPEMIT '#include "ntsecapi.h"'}
{$HPPEMIT ''}

{$I WINDEFINES.INC}

interface

uses
  JwaWinType, JwaNtStatus, JwaWinNT;

//
// Security operation mode of the system is held in a control
// longword.
//

type
  LSA_OPERATIONAL_MODE = ULONG;
  {$EXTERNALSYM LSA_OPERATIONAL_MODE}
  PLSA_OPERATIONAL_MODE = ^LSA_OPERATIONAL_MODE;
  {$EXTERNALSYM PLSA_OPERATIONAL_MODE}

//
// The flags in the security operational mode are defined
// as:
//
//    PasswordProtected - Some level of authentication (such as
//        a password) must be provided by users before they are
//        allowed to use the system.  Once set, this value will
//        not be cleared without re-booting the system.
//
//    IndividualAccounts - Each user must identify an account to
//        logon to.  This flag is only meaningful if the
//        PasswordProtected flag is also set.  If this flag is
//        not set and the PasswordProtected flag is set, then all
//        users may logon to the same account.  Once set, this value
//        will not be cleared without re-booting the system.
//
//    MandatoryAccess - Indicates the system is running in a mandatory
//        access control mode (e.g., B-level as defined by the U.S.A's
//        Department of Defense's "Orange Book").  This is not utilized
//        in the current release of NT.  This flag is only meaningful
//        if both the PasswordProtected and IndividualAccounts flags are
//        set.  Once set, this value will not be cleared without
//        re-booting the system.
//
//    LogFull - Indicates the system has been brought up in a mode in
//        which if must perform security auditing, but its audit log
//        is full.  This may (should) restrict the operations that
//        can occur until the audit log is made not-full again.  THIS
//        VALUE MAY BE CLEARED WHILE THE SYSTEM IS RUNNING (I.E., WITHOUT
//        REBOOTING).
//
// If the PasswordProtected flag is not set, then the system is running
// without security, and user interface should be adjusted appropriately.
//

const
  LSA_MODE_PASSWORD_PROTECTED  = ($00000001);
  {$EXTERNALSYM LSA_MODE_PASSWORD_PROTECTED}
  LSA_MODE_INDIVIDUAL_ACCOUNTS = ($00000002);
  {$EXTERNALSYM LSA_MODE_INDIVIDUAL_ACCOUNTS}
  LSA_MODE_MANDATORY_ACCESS    = ($00000004);
  {$EXTERNALSYM LSA_MODE_MANDATORY_ACCESS}
  LSA_MODE_LOG_FULL            = ($00000008);
  {$EXTERNALSYM LSA_MODE_LOG_FULL}

//
// Used by a logon process to indicate what type of logon is being
// requested.
//

type
  _SECURITY_LOGON_TYPE = (
    seltFiller0, seltFiller1,
    Interactive,        // Interactively logged on (locally or remotely)
    Network,            // Accessing system via network
    Batch,              // Started via a batch queue
    Service,            // Service started by service controller
    Proxy,              // Proxy logon
    Unlock,             // Unlock workstation
    NetworkCleartext,   // Network logon with cleartext credentials
    NewCredentials,     // Clone caller, new default credentials
    RemoteInteractive,  // Remote, yet interactive.  Terminal server
    CachedInteractive,  // Try cached credentials without hitting the net.
    CachedRemoteInteractive, // Same as RemoteInteractive, this is used internally for auditing purpose
    CachedUnlock);        // Cached Unlock workstation
  {$EXTERNALSYM _SECURITY_LOGON_TYPE}
  SECURITY_LOGON_TYPE = _SECURITY_LOGON_TYPE;
  {$EXTERNALSYM SECURITY_LOGON_TYPE}
  PSECURITY_LOGON_TYPE = ^SECURITY_LOGON_TYPE;
  {$EXTERNALSYM PSECURITY_LOGON_TYPE}
  TSecurityLogonType = SECURITY_LOGON_TYPE;
  PSecurityLogonType = PSECURITY_LOGON_TYPE;

//
// Audit Event Categories
//
// The following are the built-in types or Categories of audit event.
// WARNING!  This structure is subject to expansion.  The user should not
// compute the number of elements of this type directly, but instead
// should obtain the count of elements by calling LsaQueryInformationPolicy()
// for the PolicyAuditEventsInformation class and extracting the count from
// the MaximumAuditEventCount field of the returned structure.
//

  _POLICY_AUDIT_EVENT_TYPE = (
    AuditCategorySystem,
    AuditCategoryLogon,
    AuditCategoryObjectAccess,
    AuditCategoryPrivilegeUse,
    AuditCategoryDetailedTracking,
    AuditCategoryPolicyChange,
    AuditCategoryAccountManagement,
    AuditCategoryDirectoryServiceAccess,
    AuditCategoryAccountLogon);
  {$EXTERNALSYM _POLICY_AUDIT_EVENT_TYPE}
  POLICY_AUDIT_EVENT_TYPE = _POLICY_AUDIT_EVENT_TYPE;
  {$EXTERNALSYM POLICY_AUDIT_EVENT_TYPE}
  PPOLICY_AUDIT_EVENT_TYPE = ^POLICY_AUDIT_EVENT_TYPE;
  {$EXTERNALSYM PPOLICY_AUDIT_EVENT_TYPE}
  TPolicyAuditEventType = POLICY_AUDIT_EVENT_TYPE;
  PPolicyAuditEventType = PPOLICY_AUDIT_EVENT_TYPE;  

//
// The following defines describe the auditing options for each
// event type
//

const

// Leave options specified for this event unchanged

  POLICY_AUDIT_EVENT_UNCHANGED = ($00000000);
  {$EXTERNALSYM POLICY_AUDIT_EVENT_UNCHANGED}

// Audit successful occurrences of events of this type

  POLICY_AUDIT_EVENT_SUCCESS = ($00000001);
  {$EXTERNALSYM POLICY_AUDIT_EVENT_SUCCESS}

// Audit failed attempts to cause an event of this type to occur

  POLICY_AUDIT_EVENT_FAILURE = ($00000002);
  {$EXTERNALSYM POLICY_AUDIT_EVENT_FAILURE}

  POLICY_AUDIT_EVENT_NONE    = ($00000004);
  {$EXTERNALSYM POLICY_AUDIT_EVENT_NONE}

// Mask of valid event auditing options

  POLICY_AUDIT_EVENT_MASK = (POLICY_AUDIT_EVENT_SUCCESS or POLICY_AUDIT_EVENT_FAILURE or
    POLICY_AUDIT_EVENT_UNCHANGED or POLICY_AUDIT_EVENT_NONE);
  {$EXTERNALSYM POLICY_AUDIT_EVENT_MASK}
  TPolicyAuditEventMask = POLICY_AUDIT_EVENT_MASK;

type
  PLSA_UNICODE_STRING = ^LSA_UNICODE_STRING;
  {$EXTERNALSYM PLSA_UNICODE_STRING}
  _LSA_UNICODE_STRING = record
    Length: USHORT;
    MaximumLength: USHORT;
    Buffer: PWSTR;
  end;
  {$EXTERNALSYM _LSA_UNICODE_STRING}
  LSA_UNICODE_STRING = _LSA_UNICODE_STRING;
  {$EXTERNALSYM LSA_UNICODE_STRING}
  TLsaUnicodeString = LSA_UNICODE_STRING;
  PLsaUnicodeString = PLSA_UNICODE_STRING;

  PLSA_STRING = ^LSA_STRING;
  {$EXTERNALSYM PLSA_STRING}
  _LSA_STRING = record
    Length: USHORT;
    MaximumLength: USHORT;
    Buffer: PCHAR;
  end;
  {$EXTERNALSYM _LSA_STRING}
  LSA_STRING = _LSA_STRING;
  {$EXTERNALSYM LSA_STRING}
  TLsaString = LSA_STRING;
  PLsaString = PLSA_STRING;

  PLSA_OBJECT_ATTRIBUTES = ^LSA_OBJECT_ATTRIBUTES;
  {$EXTERNALSYM PLSA_OBJECT_ATTRIBUTES}
  _LSA_OBJECT_ATTRIBUTES = record
    Length: ULONG;
    RootDirectory: HANDLE;
    ObjectName: PLSA_UNICODE_STRING;
    Attributes: ULONG;
    SecurityDescriptor: PVOID; // Points to type SECURITY_DESCRIPTOR
    SecurityQualityOfService: PVOID; // Points to type SECURITY_QUALITY_OF_SERVICE
  end;
  {$EXTERNALSYM _LSA_OBJECT_ATTRIBUTES}
  LSA_OBJECT_ATTRIBUTES = _LSA_OBJECT_ATTRIBUTES;
  {$EXTERNALSYM LSA_OBJECT_ATTRIBUTES}
  TLsaObjectAttributes = LSA_OBJECT_ATTRIBUTES;
  PLsaObjectAttributes = PLSA_OBJECT_ATTRIBUTES;

//
// Macro for determining whether an API succeeded.
//

function LSA_SUCCESS(Error: NTSTATUS): BOOL;
{$EXTERNALSYM LSA_SUCCESS}

function LsaRegisterLogonProcess(const LogonProcessName: LSA_STRING;
  var LsaHandle: HANDLE; SecurityMode: PLSA_OPERATIONAL_MODE): NTSTATUS; stdcall;
{$EXTERNALSYM LsaRegisterLogonProcess}

function LsaLogonUser(LsaHandle: HANDLE; const OriginName: LSA_STRING;
  LogonType: SECURITY_LOGON_TYPE; AuthenticationPackage: ULONG;
  AuthenticationInformation: PVOID; AuthenticationInformationLength: ULONG;
  LocalGroups: PTOKEN_GROUPS; SourceContext: PTOKEN_SOURCE;
  var ProfileBuffer: PVOID; var ProfileBufferLength: ULONG; var LogonId: LUID;
  var Token: HANDLE; var Quotas: QUOTA_LIMITS; var SubStatus: NTSTATUS): NTSTATUS; stdcall;
{$EXTERNALSYM LsaLogonUser}

function LsaLookupAuthenticationPackage(LsaHandle: HANDLE;
  const PackageName: LSA_STRING; var AuthenticationPackage: ULONG): NTSTATUS; stdcall;
{$EXTERNALSYM LsaLookupAuthenticationPackage}

function LsaFreeReturnBuffer(Buffer: PVOID): NTSTATUS; stdcall;
{$EXTERNALSYM LsaFreeReturnBuffer}

function LsaCallAuthenticationPackage(LsaHandle: HANDLE;
  AuthenticationPackage: ULONG; ProtocolSubmitBuffer: PVOID;
  SubmitBufferLength: ULONG; var ProtocolReturnBuffer: PVOID;
  var ReturnBufferLength: ULONG; var ProtocolStatus: NTSTATUS): NTSTATUS; stdcall;
{$EXTERNALSYM LsaCallAuthenticationPackage}

function LsaDeregisterLogonProcess(LsaHandle: HANDLE): NTSTATUS; stdcall;
{$EXTERNALSYM LsaDeregisterLogonProcess}

function LsaConnectUntrusted(var LsaHandle: HANDLE): NTSTATUS; stdcall;
{$EXTERNALSYM LsaConnectUntrusted}

////////////////////////////////////////////////////////////////////////////
//                                                                        //
// Local Security Policy Administration API datatypes and defines         //
//                                                                        //
////////////////////////////////////////////////////////////////////////////

//
// Access types for the Policy object
//

const
  POLICY_VIEW_LOCAL_INFORMATION   = $00000001;
  {$EXTERNALSYM POLICY_VIEW_LOCAL_INFORMATION}
  POLICY_VIEW_AUDIT_INFORMATION   = $00000002;
  {$EXTERNALSYM POLICY_VIEW_AUDIT_INFORMATION}
  POLICY_GET_PRIVATE_INFORMATION  = $00000004;
  {$EXTERNALSYM POLICY_GET_PRIVATE_INFORMATION}
  POLICY_TRUST_ADMIN              = $00000008;
  {$EXTERNALSYM POLICY_TRUST_ADMIN}
  POLICY_CREATE_ACCOUNT           = $00000010;
  {$EXTERNALSYM POLICY_CREATE_ACCOUNT}
  POLICY_CREATE_SECRET            = $00000020;
  {$EXTERNALSYM POLICY_CREATE_SECRET}
  POLICY_CREATE_PRIVILEGE         = $00000040;
  {$EXTERNALSYM POLICY_CREATE_PRIVILEGE}
  POLICY_SET_DEFAULT_QUOTA_LIMITS = $00000080;
  {$EXTERNALSYM POLICY_SET_DEFAULT_QUOTA_LIMITS}
  POLICY_SET_AUDIT_REQUIREMENTS   = $00000100;
  {$EXTERNALSYM POLICY_SET_AUDIT_REQUIREMENTS}
  POLICY_AUDIT_LOG_ADMIN          = $00000200;
  {$EXTERNALSYM POLICY_AUDIT_LOG_ADMIN}
  POLICY_SERVER_ADMIN             = $00000400;
  {$EXTERNALSYM POLICY_SERVER_ADMIN}
  POLICY_LOOKUP_NAMES             = $00000800;
  {$EXTERNALSYM POLICY_LOOKUP_NAMES}
  POLICY_NOTIFICATION             = $00001000;
  {$EXTERNALSYM POLICY_NOTIFICATION}

  POLICY_ALL_ACCESS =         (STANDARD_RIGHTS_REQUIRED         or
                               POLICY_VIEW_LOCAL_INFORMATION    or
                               POLICY_VIEW_AUDIT_INFORMATION    or
                               POLICY_GET_PRIVATE_INFORMATION   or
                               POLICY_TRUST_ADMIN               or
                               POLICY_CREATE_ACCOUNT            or
                               POLICY_CREATE_SECRET             or
                               POLICY_CREATE_PRIVILEGE          or
                               POLICY_SET_DEFAULT_QUOTA_LIMITS  or
                               POLICY_SET_AUDIT_REQUIREMENTS    or
                               POLICY_AUDIT_LOG_ADMIN           or
                               POLICY_SERVER_ADMIN              or
                               POLICY_LOOKUP_NAMES);
  {$EXTERNALSYM POLICY_ALL_ACCESS}

  POLICY_READ =               (STANDARD_RIGHTS_READ or
                               POLICY_VIEW_AUDIT_INFORMATION or
                               POLICY_GET_PRIVATE_INFORMATION);
  {$EXTERNALSYM POLICY_READ}

  POLICY_WRITE =              (STANDARD_RIGHTS_WRITE            or
                               POLICY_TRUST_ADMIN               or
                               POLICY_CREATE_ACCOUNT            or
                               POLICY_CREATE_SECRET             or
                               POLICY_CREATE_PRIVILEGE          or
                               POLICY_SET_DEFAULT_QUOTA_LIMITS  or
                               POLICY_SET_AUDIT_REQUIREMENTS    or
                               POLICY_AUDIT_LOG_ADMIN           or
                               POLICY_SERVER_ADMIN);
  {$EXTERNALSYM POLICY_WRITE}

  POLICY_EXECUTE =            (STANDARD_RIGHTS_EXECUTE          or
                               POLICY_VIEW_LOCAL_INFORMATION    or
                               POLICY_LOOKUP_NAMES);
  {$EXTERNALSYM POLICY_EXECUTE}

//
// Policy object specific data types.
//

//
// The following data type is used to identify a domain
//

type
  PLSA_TRUST_INFORMATION = ^LSA_TRUST_INFORMATION;
  {$EXTERNALSYM PLSA_TRUST_INFORMATION}
  _LSA_TRUST_INFORMATION = record
    Name: LSA_UNICODE_STRING;
    Sid: PSID;
  end;
  {$EXTERNALSYM _LSA_TRUST_INFORMATION}
  LSA_TRUST_INFORMATION = _LSA_TRUST_INFORMATION;
  {$EXTERNALSYM LSA_TRUST_INFORMATION}
  TLsaTrustInformation = LSA_TRUST_INFORMATION;
  PLsaTrustInformation = PLSA_TRUST_INFORMATION;

// where members have the following usage:
//
//     Name - The name of the domain.
//
//     Sid - A pointer to the Sid of the Domain
//

//
// The following data type is used in name and SID lookup services to
// describe the domains referenced in the lookup operation.
//

  PLSA_REFERENCED_DOMAIN_LIST = ^LSA_REFERENCED_DOMAIN_LIST;
  {$EXTERNALSYM PLSA_REFERENCED_DOMAIN_LIST}
  _LSA_REFERENCED_DOMAIN_LIST = record
    Entries: ULONG;
    Domains: PLSA_TRUST_INFORMATION;
  end;
  {$EXTERNALSYM _LSA_REFERENCED_DOMAIN_LIST}
  LSA_REFERENCED_DOMAIN_LIST = _LSA_REFERENCED_DOMAIN_LIST;
  {$EXTERNALSYM LSA_REFERENCED_DOMAIN_LIST}
  TLsaReferencedDomainList = LSA_REFERENCED_DOMAIN_LIST;
  PLsaReferencedDomainList = PLSA_REFERENCED_DOMAIN_LIST;

// where members have the following usage:
//
//     Entries - Is a count of the number of domains described in the
//         Domains array.
//
//     Domains - Is a pointer to an array of Entries LSA_TRUST_INFORMATION data
//         structures.
//


//
// The following data type is used in name to SID lookup services to describe
// the domains referenced in the lookup operation.
//

  PLSA_TRANSLATED_SID = ^LSA_TRANSLATED_SID;
  {$EXTERNALSYM PLSA_TRANSLATED_SID}
  _LSA_TRANSLATED_SID = record
    Use: SID_NAME_USE;
    RelativeId: ULONG;
    DomainIndex: LONG;
  end;
  {$EXTERNALSYM _LSA_TRANSLATED_SID}
  LSA_TRANSLATED_SID = _LSA_TRANSLATED_SID;
  {$EXTERNALSYM LSA_TRANSLATED_SID}
  TLsaTranslatedSid = LSA_TRANSLATED_SID;
  PLsaTranslatedSid = PLSA_TRANSLATED_SID;

// where members have the following usage:
//
//     Use - identifies the use of the SID.  If this value is SidUnknown or
//         SidInvalid, then the remainder of the record is not set and
//         should be ignored.
//
//     RelativeId - Contains the relative ID of the translated SID.  The
//         remainder of the SID (the prefix) is obtained using the
//         DomainIndex field.
//
//     DomainIndex - Is the index of an entry in a related
//         LSA_REFERENCED_DOMAIN_LIST data structure describing the
//         domain in which the account was found.
//
//         If there is no corresponding reference domain for an entry, then
//         this field will contain a negative value.
//

  _LSA_TRANSLATED_SID2 = record
    Use: SID_NAME_USE;
    Sid: PSID;
    DomainIndex: LONG;
    Flags: ULONG;
  end;
  {$EXTERNALSYM _LSA_TRANSLATED_SID2}
  LSA_TRANSLATED_SID2 = _LSA_TRANSLATED_SID2;
  {$EXTERNALSYM LSA_TRANSLATED_SID2}
  PLSA_TRANSLATED_SID2 = ^LSA_TRANSLATED_SID2;
  {$EXTERNALSYM PLSA_TRANSLATED_SID2}
  TLsaTranslatedSid2 = LSA_TRANSLATED_SID2;
  PLsaTranslatedSid2 = PLSA_TRANSLATED_SID2;  

// where members have the following usage:
//
//     Use - identifies the use of the SID.  If this value is SidUnknown or
//         SidInvalid, then the remainder of the record is not set and
//         should be ignored.
//
//     Sid - Contains the complete Sid of the tranlated SID
//
//     DomainIndex - Is the index of an entry in a related
//         LSA_REFERENCED_DOMAIN_LIST data structure describing the
//         domain in which the account was found.
//
//         If there is no corresponding reference domain for an entry, then
//         this field will contain a negative value.
//

//
// The following data type is used in SID to name lookup services to
// describe the domains referenced in the lookup operation.
//

  PLSA_TRANSLATED_NAME = ^LSA_TRANSLATED_NAME;
  {$EXTERNALSYM PLSA_TRANSLATED_NAME}
  _LSA_TRANSLATED_NAME = record
    Use: SID_NAME_USE;
    Name: LSA_UNICODE_STRING;
    DomainIndex: LONG;
  end;
  {$EXTERNALSYM _LSA_TRANSLATED_NAME}
  LSA_TRANSLATED_NAME = _LSA_TRANSLATED_NAME;
  {$EXTERNALSYM LSA_TRANSLATED_NAME}
  TLsaTranslatedName = LSA_TRANSLATED_NAME;
  PLsaTranslatedName = PLSA_TRANSLATED_NAME;

// where the members have the following usage:
//
//     Use - Identifies the use of the name.  If this value is SidUnknown
//         or SidInvalid, then the remainder of the record is not set and
//         should be ignored.  If this value is SidWellKnownGroup then the
//         Name field is invalid, but the DomainIndex field is not.
//
//     Name - Contains the isolated name of the translated SID.
//
//     DomainIndex - Is the index of an entry in a related
//         LSA_REFERENCED_DOMAIN_LIST data structure describing the domain
//         in which the account was found.
//
//         If there is no corresponding reference domain for an entry, then
//         this field will contain a negative value.
//


//
// The following data type is used to represent the role of the LSA
// server (primary or backup).
//

  _POLICY_LSA_SERVER_ROLE = (plsrFiller0, plsrFiller1, PolicyServerRoleBackup,
    PolicyServerRolePrimary);
  {$EXTERNALSYM _POLICY_LSA_SERVER_ROLE}
  POLICY_LSA_SERVER_ROLE = _POLICY_LSA_SERVER_ROLE;
  {$EXTERNALSYM POLICY_LSA_SERVER_ROLE}
  PPOLICY_LSA_SERVER_ROLE = ^POLICY_LSA_SERVER_ROLE;
  {$EXTERNALSYM PPOLICY_LSA_SERVER_ROLE}
  TPolicyLsaServerRole = POLICY_LSA_SERVER_ROLE;
  PPolicyLsaServerRole = PPOLICY_LSA_SERVER_ROLE;

//
// The following data type is used to specify the auditing options for
// an Audit Event Type.
//

  POLICY_AUDIT_EVENT_OPTIONS = ULONG;
  {$EXTERNALSYM POLICY_AUDIT_EVENT_OPTIONS}
  PPOLICY_AUDIT_EVENT_OPTIONS = ^POLICY_AUDIT_EVENT_OPTIONS;
  {$EXTERNALSYM PPOLICY_AUDIT_EVENT_OPTIONS}

// where the following flags can be set:
//
//     POLICY_AUDIT_EVENT_UNCHANGED - Leave existing auditing options
//         unchanged for events of this type.  This flag is only used for
//         set operations.  If this flag is set, then all other flags
//         are ignored.
//
//     POLICY_AUDIT_EVENT_NONE - Cancel all auditing options for events
//         of this type.  If this flag is set, the success/failure flags
//         are ignored.
//
//     POLICY_AUDIT_EVENT_SUCCESS - When auditing is enabled, audit all
//         successful occurrences of events of the given type.
//
//     POLICY_AUDIT_EVENT_FAILURE - When auditing is enabled, audit all
//         unsuccessful occurrences of events of the given type.
//

//
// The following data type defines the classes of Policy Information
// that may be queried/set.
//

type
  _POLICY_INFORMATION_CLASS = (
    picFiller0,
    PolicyAuditLogInformation,
    PolicyAuditEventsInformation,
    PolicyPrimaryDomainInformation,
    PolicyPdAccountInformation,
    PolicyAccountDomainInformation,
    PolicyLsaServerRoleInformation,
    PolicyReplicaSourceInformation,
    PolicyDefaultQuotaInformation,
    PolicyModificationInformation,
    PolicyAuditFullSetInformation,
    PolicyAuditFullQueryInformation,
    PolicyDnsDomainInformation,
    PolicyDnsDomainInformationInt);
  {$EXTERNALSYM _POLICY_INFORMATION_CLASS}
  POLICY_INFORMATION_CLASS = _POLICY_INFORMATION_CLASS;
  {$EXTERNALSYM POLICY_INFORMATION_CLASS}
  PPOLICY_INFORMATION_CLASS = ^POLICY_INFORMATION_CLASS;
  {$EXTERNALSYM PPOLICY_INFORMATION_CLASS}
  TPolicyInformationClass = POLICY_INFORMATION_CLASS;
  PPolicyInformationClass = PPOLICY_INFORMATION_CLASS;

//
// The following data type corresponds to the PolicyAuditLogInformation
// information class.  It is used to represent information relating to
// the Audit Log.
//
// This structure may be used in both query and set operations.  However,
// when used in set operations, some fields are ignored.
//

  PPOLICY_AUDIT_LOG_INFO = ^POLICY_AUDIT_LOG_INFO;
  {$EXTERNALSYM PPOLICY_AUDIT_LOG_INFO}
  _POLICY_AUDIT_LOG_INFO = record
    AuditLogPercentFull: ULONG;
    MaximumLogSize: ULONG;
    AuditRetentionPeriod: LARGE_INTEGER;
    AuditLogFullShutdownInProgress: ByteBool;
    TimeToShutdown: LARGE_INTEGER;
    NextAuditRecordId: ULONG;
  end;
  {$EXTERNALSYM _POLICY_AUDIT_LOG_INFO}
  POLICY_AUDIT_LOG_INFO = _POLICY_AUDIT_LOG_INFO;
  {$EXTERNALSYM POLICY_AUDIT_LOG_INFO}
  TPolicyAuditLogInfo = POLICY_AUDIT_LOG_INFO;
  PPolicyAuditLogInfo = PPOLICY_AUDIT_LOG_INFO;

// where the members have the following usage:
//
//     AuditLogPercentFull - Indicates the percentage of the Audit Log
//         currently being used.
//
//     MaximumLogSize - Specifies the maximum size of the Audit Log in
//         kilobytes.
//
//     AuditRetentionPeriod - Indicates the length of time that Audit
//         Records are to be retained.  Audit Records are discardable
//         if their timestamp predates the current time minus the
//         retention period.
//
//     AuditLogFullShutdownInProgress - Indicates whether or not a system
//         shutdown is being initiated due to the security Audit Log becoming
//         full.  This condition will only occur if the system is configured
//         to shutdown when the log becomes full.
//
//         TRUE indicates that a shutdown is in progress
//         FALSE indicates that a shutdown is not in progress.
//
//         Once a shutdown has been initiated, this flag will be set to
//         TRUE.  If an administrator is able to currect the situation
//         before the shutdown becomes irreversible, then this flag will
//         be reset to false.
//
//         This field is ignored for set operations.
//
//     TimeToShutdown - If the AuditLogFullShutdownInProgress flag is set,
//         then this field contains the time left before the shutdown
//         becomes irreversible.
//
//         This field is ignored for set operations.
//

//
// The following data type corresponds to the PolicyAuditEventsInformation
// information class.  It is used to represent information relating to
// the audit requirements.
//

  PPOLICY_AUDIT_EVENTS_INFO = ^POLICY_AUDIT_EVENTS_INFO;
  {$EXTERNALSYM PPOLICY_AUDIT_EVENTS_INFO}
  _POLICY_AUDIT_EVENTS_INFO = record
    AuditingMode: ByteBool;
    EventAuditingOptions: PPOLICY_AUDIT_EVENT_OPTIONS;
    MaximumAuditEventCount: ULONG;
  end;
  {$EXTERNALSYM _POLICY_AUDIT_EVENTS_INFO}
  POLICY_AUDIT_EVENTS_INFO = _POLICY_AUDIT_EVENTS_INFO;
  {$EXTERNALSYM POLICY_AUDIT_EVENTS_INFO}
  TPolicyAuditEventsInfo = POLICY_AUDIT_EVENTS_INFO;
  PPolicyAuditEventsInfo = PPOLICY_AUDIT_EVENTS_INFO;

// where the members have the following usage:
//
//     AuditingMode - A Boolean variable specifying the Auditing Mode value.
//         This value is interpreted as follows:
//
//         TRUE - Auditing is to be enabled (set operations) or is enabled
//             (query operations).  Audit Records will be generated according
//             to the Event Auditing Options in effect (see the
//             EventAuditingOptions field.
//
//         FALSE - Auditing is to be disabled (set operations) or is
//             disabled (query operations).  No Audit Records will be
//             generated.  Note that for set operations the Event Auditing
//             Options in effect will still be updated as specified by the
//             EventAuditingOptions field whether Auditing is enabled or
//             disabled.
//
//    EventAuditingOptions - Pointer to an array of Auditing Options
//        indexed by Audit Event Type.
//
//    MaximumAuditEventCount - Specifiesa count of the number of Audit
//        Event Types specified by the EventAuditingOptions parameter.  If
//        this count is less than the number of Audit Event Types supported
//        by the system, the Auditing Options for Event Types with IDs
//        higher than (MaximumAuditEventCount + 1) are left unchanged.
//


//
// The following structure corresponds to the PolicyAccountDomainInformation
// information class.
//

  PPOLICY_ACCOUNT_DOMAIN_INFO = ^POLICY_ACCOUNT_DOMAIN_INFO;
  {$EXTERNALSYM PPOLICY_ACCOUNT_DOMAIN_INFO}
  _POLICY_ACCOUNT_DOMAIN_INFO = record
    DomainName: LSA_UNICODE_STRING;
    DomainSid: PSID;
  end;
  {$EXTERNALSYM _POLICY_ACCOUNT_DOMAIN_INFO}
  POLICY_ACCOUNT_DOMAIN_INFO = _POLICY_ACCOUNT_DOMAIN_INFO;
  {$EXTERNALSYM POLICY_ACCOUNT_DOMAIN_INFO}
  TPolicyAccountDomainInfo = POLICY_ACCOUNT_DOMAIN_INFO;
  PPolicyAccountDomainInfo = PPOLICY_ACCOUNT_DOMAIN_INFO;

// where the members have the following usage:
//
//     DomainName - Is the name of the domain
//
//     DomainSid - Is the Sid of the domain
//


//
// The following structure corresponds to the PolicyPrimaryDomainInformation
// information class.
//

  PPOLICY_PRIMARY_DOMAIN_INFO = ^POLICY_PRIMARY_DOMAIN_INFO;
  {$EXTERNALSYM PPOLICY_PRIMARY_DOMAIN_INFO}
  _POLICY_PRIMARY_DOMAIN_INFO = record
    Name: LSA_UNICODE_STRING;
    Sid: PSID;
  end;
  {$EXTERNALSYM _POLICY_PRIMARY_DOMAIN_INFO}
  POLICY_PRIMARY_DOMAIN_INFO = _POLICY_PRIMARY_DOMAIN_INFO;
  {$EXTERNALSYM POLICY_PRIMARY_DOMAIN_INFO}
  TPolicyPrimaryDomainInfo = POLICY_PRIMARY_DOMAIN_INFO;
  PPolicyPrimaryDomainInfo = PPOLICY_PRIMARY_DOMAIN_INFO;

// where the members have the following usage:
//
//     Name - Is the name of the domain
//
//     Sid - Is the Sid of the domain
//


//
// The following structure corresponds to the PolicyDnsDomainInformation
// information class
//

  PPOLICY_DNS_DOMAIN_INFO = ^POLICY_DNS_DOMAIN_INFO;
  {$EXTERNALSYM PPOLICY_DNS_DOMAIN_INFO}
  _POLICY_DNS_DOMAIN_INFO = record
    Name: LSA_UNICODE_STRING;
    DnsDomainName: LSA_UNICODE_STRING;
    DnsForestName: LSA_UNICODE_STRING;
    DomainGuid: GUID;
    Sid: PSID;
  end;
  {$EXTERNALSYM _POLICY_DNS_DOMAIN_INFO}
  POLICY_DNS_DOMAIN_INFO = _POLICY_DNS_DOMAIN_INFO;
  {$EXTERNALSYM POLICY_DNS_DOMAIN_INFO}
  TPolicyDnsDomainInfo = POLICY_DNS_DOMAIN_INFO;
  PPolicyDnsDomainInfo = PPOLICY_DNS_DOMAIN_INFO;

// where the members have the following usage:
//
//      Name - Is the name of the Domain
//
//      DnsDomainName - Is the DNS name of the domain
//
//      DnsForestName - Is the DNS forest name of the domain
//
//      DomainGuid - Is the GUID of the domain
//
//      Sid - Is the Sid of the domain


//
// The following structure corresponds to the PolicyPdAccountInformation
// information class.  This structure may be used in Query operations
// only.
//

  PPOLICY_PD_ACCOUNT_INFO = ^POLICY_PD_ACCOUNT_INFO;
  {$EXTERNALSYM PPOLICY_PD_ACCOUNT_INFO}
  _POLICY_PD_ACCOUNT_INFO = record
    Name: LSA_UNICODE_STRING;
  end;
  {$EXTERNALSYM _POLICY_PD_ACCOUNT_INFO}
  POLICY_PD_ACCOUNT_INFO = _POLICY_PD_ACCOUNT_INFO;
  {$EXTERNALSYM POLICY_PD_ACCOUNT_INFO}
  TPolicyPdAccountInfo = POLICY_PD_ACCOUNT_INFO;
  PPolicyPdAccountInfo = PPOLICY_PD_ACCOUNT_INFO;

// where the members have the following usage:
//
//     Name - Is the name of an account in the domain that should be used
//         for authentication and name/ID lookup requests.
//


//
// The following structure corresponds to the PolicyLsaServerRoleInformation
// information class.
//

  PPOLICY_LSA_SERVER_ROLE_INFO = ^POLICY_LSA_SERVER_ROLE_INFO;
  {$EXTERNALSYM PPOLICY_LSA_SERVER_ROLE_INFO}
  _POLICY_LSA_SERVER_ROLE_INFO = record
    LsaServerRole: POLICY_LSA_SERVER_ROLE;
  end;
  {$EXTERNALSYM _POLICY_LSA_SERVER_ROLE_INFO}
  POLICY_LSA_SERVER_ROLE_INFO = _POLICY_LSA_SERVER_ROLE_INFO;
  {$EXTERNALSYM POLICY_LSA_SERVER_ROLE_INFO}
  TPolicyLsaServerRoleInfo = POLICY_LSA_SERVER_ROLE_INFO;
  PPolicyLsaServerRoleInfo = PPOLICY_LSA_SERVER_ROLE_INFO;

// where the fields have the following usage:
//
// TBS
//


//
// The following structure corresponds to the PolicyReplicaSourceInformation
// information class.
//

  PPOLICY_REPLICA_SOURCE_INFO = ^POLICY_REPLICA_SOURCE_INFO;
  {$EXTERNALSYM PPOLICY_REPLICA_SOURCE_INFO}
  _POLICY_REPLICA_SOURCE_INFO = record
    ReplicaSource: LSA_UNICODE_STRING;
    ReplicaAccountName: LSA_UNICODE_STRING;
  end;
  {$EXTERNALSYM _POLICY_REPLICA_SOURCE_INFO}
  POLICY_REPLICA_SOURCE_INFO = _POLICY_REPLICA_SOURCE_INFO;
  {$EXTERNALSYM POLICY_REPLICA_SOURCE_INFO}
  TPolicyReplicaSourceInfo = POLICY_REPLICA_SOURCE_INFO;
  PPolicyReplicaSourceInfo = PPOLICY_REPLICA_SOURCE_INFO;

//
// The following structure corresponds to the PolicyDefaultQuotaInformation
// information class.
//

  PPOLICY_DEFAULT_QUOTA_INFO = ^POLICY_DEFAULT_QUOTA_INFO;
  {$EXTERNALSYM PPOLICY_DEFAULT_QUOTA_INFO}
  _POLICY_DEFAULT_QUOTA_INFO = record
    QuotaLimits: QUOTA_LIMITS;
  end;
  {$EXTERNALSYM _POLICY_DEFAULT_QUOTA_INFO}
  POLICY_DEFAULT_QUOTA_INFO = _POLICY_DEFAULT_QUOTA_INFO;
  {$EXTERNALSYM POLICY_DEFAULT_QUOTA_INFO}
  TPolicyDefaultQuotaInfo = POLICY_DEFAULT_QUOTA_INFO;
  PPolicyDefaultQuotaInfo = PPOLICY_DEFAULT_QUOTA_INFO;

//
// The following structure corresponds to the PolicyModificationInformation
// information class.
//

  PPOLICY_MODIFICATION_INFO = ^POLICY_MODIFICATION_INFO;
  {$EXTERNALSYM PPOLICY_MODIFICATION_INFO}
  _POLICY_MODIFICATION_INFO = record
    ModifiedId: LARGE_INTEGER;
    DatabaseCreationTime: LARGE_INTEGER;
  end;
  {$EXTERNALSYM _POLICY_MODIFICATION_INFO}
  POLICY_MODIFICATION_INFO = _POLICY_MODIFICATION_INFO;
  {$EXTERNALSYM POLICY_MODIFICATION_INFO}
  TPolicyModificationInfo = POLICY_MODIFICATION_INFO;
  PPolicyModificationInfo = PPOLICY_MODIFICATION_INFO;

// where the members have the following usage:
//
//     ModifiedId - Is a 64-bit unsigned integer that is incremented each
//         time anything in the LSA database is modified.  This value is
//         only modified on Primary Domain Controllers.
//
//     DatabaseCreationTime - Is the date/time that the LSA Database was
//         created.  On Backup Domain Controllers, this value is replicated
//         from the Primary Domain Controller.
//

//
// The following structure type corresponds to the PolicyAuditFullSetInformation
// Information Class.
//

  PPOLICY_AUDIT_FULL_SET_INFO = ^POLICY_AUDIT_FULL_SET_INFO;
  {$EXTERNALSYM PPOLICY_AUDIT_FULL_SET_INFO}
  _POLICY_AUDIT_FULL_SET_INFO = record
    ShutDownOnFull: ByteBool;
  end;
  {$EXTERNALSYM _POLICY_AUDIT_FULL_SET_INFO}
  POLICY_AUDIT_FULL_SET_INFO = _POLICY_AUDIT_FULL_SET_INFO;
  {$EXTERNALSYM POLICY_AUDIT_FULL_SET_INFO}
  TPolicyAuditFullSetInfo = POLICY_AUDIT_FULL_SET_INFO;
  PPolicyAuditFullSetInfo = PPOLICY_AUDIT_FULL_SET_INFO;

//
// The following structure type corresponds to the PolicyAuditFullQueryInformation
// Information Class.
//

  PPOLICY_AUDIT_FULL_QUERY_INFO = ^POLICY_AUDIT_FULL_QUERY_INFO;
  {$EXTERNALSYM PPOLICY_AUDIT_FULL_QUERY_INFO}
  _POLICY_AUDIT_FULL_QUERY_INFO = record
    ShutDownOnFull: ByteBool;
    LogIsFull: ByteBool;
  end;
  {$EXTERNALSYM _POLICY_AUDIT_FULL_QUERY_INFO}
  POLICY_AUDIT_FULL_QUERY_INFO = _POLICY_AUDIT_FULL_QUERY_INFO;
  {$EXTERNALSYM POLICY_AUDIT_FULL_QUERY_INFO}
  TPolicyAuditFullQueryInfo = POLICY_AUDIT_FULL_QUERY_INFO;
  PPolicyAuditFullQueryInfo = PPOLICY_AUDIT_FULL_QUERY_INFO;

//
// The following data type defines the classes of Policy Information
// that may be queried/set that has domain wide effect.
//

  _POLICY_DOMAIN_INFORMATION_CLASS = (
    pdicFiller0,
    PolicyDomainQualityOfServiceInformation, // value was used in W2K; no longer supported
    PolicyDomainEfsInformation,
    PolicyDomainKerberosTicketInformation);
  {$EXTERNALSYM _POLICY_DOMAIN_INFORMATION_CLASS}
  POLICY_DOMAIN_INFORMATION_CLASS = _POLICY_DOMAIN_INFORMATION_CLASS;
  {$EXTERNALSYM POLICY_DOMAIN_INFORMATION_CLASS}
  PPOLICY_DOMAIN_INFORMATION_CLASS = ^POLICY_DOMAIN_INFORMATION_CLASS;
  {$EXTERNALSYM PPOLICY_DOMAIN_INFORMATION_CLASS}
  TPolicyDomainInformationClass = POLICY_DOMAIN_INFORMATION_CLASS;
  PPolicyDomainInformationClass = PPOLICY_DOMAIN_INFORMATION_CLASS;

type
  // mvb has dissapeared in november 2002 release!

  PPOLICY_DOMAIN_QUALITY_OF_SERVICE_INFO = ^POLICY_DOMAIN_QUALITY_OF_SERVICE_INFO;
  {$EXTERNALSYM PPOLICY_DOMAIN_QUALITY_OF_SERVICE_INFO}
  _POLICY_DOMAIN_QUALITY_OF_SERVICE_INFO = record
    QualityOfService: ULONG;
  end;
  {$EXTERNALSYM _POLICY_DOMAIN_QUALITY_OF_SERVICE_INFO}
  POLICY_DOMAIN_QUALITY_OF_SERVICE_INFO = _POLICY_DOMAIN_QUALITY_OF_SERVICE_INFO;
  {$EXTERNALSYM POLICY_DOMAIN_QUALITY_OF_SERVICE_INFO}
  TPolicyDomainQualityOfServiceInfo = POLICY_DOMAIN_QUALITY_OF_SERVICE_INFO;
  PPolicyDomainQualityOfServiceInfo = PPOLICY_DOMAIN_QUALITY_OF_SERVICE_INFO;

//
// where the members have the following usage:
//
//  QualityOfService - Determines what specific QOS actions a machine should take
//


//
// The following structure corresponds to the PolicyEfsInformation
// information class
//

  PPOLICY_DOMAIN_EFS_INFO = ^POLICY_DOMAIN_EFS_INFO;
  {$EXTERNALSYM PPOLICY_DOMAIN_EFS_INFO}
  _POLICY_DOMAIN_EFS_INFO = record
    InfoLength: ULONG;
    EfsBlob: PUCHAR;
  end;
  {$EXTERNALSYM _POLICY_DOMAIN_EFS_INFO}
  POLICY_DOMAIN_EFS_INFO = _POLICY_DOMAIN_EFS_INFO;
  {$EXTERNALSYM POLICY_DOMAIN_EFS_INFO}
  TPolicyDomainEfsInfo = POLICY_DOMAIN_EFS_INFO;
  PPolicyDomainEfsInfo = PPOLICY_DOMAIN_EFS_INFO;

// where the members have the following usage:
//
//      InfoLength - Length of the EFS Information blob
//
//      EfsBlob - Efs blob data
//


//
// The following structure corresponds to the PolicyDomainKerberosTicketInformation
// information class

const
  POLICY_KERBEROS_VALIDATE_CLIENT = $00000080;
  {$EXTERNALSYM POLICY_KERBEROS_VALIDATE_CLIENT}

type
  PPOLICY_DOMAIN_KERBEROS_TICKET_INFO = ^POLICY_DOMAIN_KERBEROS_TICKET_INFO;
  {$EXTERNALSYM PPOLICY_DOMAIN_KERBEROS_TICKET_INFO}
  _POLICY_DOMAIN_KERBEROS_TICKET_INFO = record
    AuthenticationOptions: ULONG;
    MaxServiceTicketAge: LARGE_INTEGER;
    MaxTicketAge: LARGE_INTEGER;
    MaxRenewAge: LARGE_INTEGER;
    MaxClockSkew: LARGE_INTEGER;
    Reserved: LARGE_INTEGER;
  end;
  {$EXTERNALSYM _POLICY_DOMAIN_KERBEROS_TICKET_INFO}
  POLICY_DOMAIN_KERBEROS_TICKET_INFO = _POLICY_DOMAIN_KERBEROS_TICKET_INFO;
  {$EXTERNALSYM POLICY_DOMAIN_KERBEROS_TICKET_INFO}
  TPolicyDomainKerberosTicketInfo = POLICY_DOMAIN_KERBEROS_TICKET_INFO;
  PPolicyDomainKerberosTicketInfo = PPOLICY_DOMAIN_KERBEROS_TICKET_INFO;

//
// where the members have the following usage
//
//      AuthenticationOptions -- allowed ticket options (POLICY_KERBEROS_* flags )
//
//      MaxServiceTicketAge   -- Maximum lifetime for a service ticket
//
//      MaxTicketAge -- Maximum lifetime for the initial ticket
//
//      MaxRenewAge -- Maximum cumulative age a renewable ticket can be with
//                     requring authentication
//
//      MaxClockSkew -- Maximum tolerance for synchronization of computer clocks
//
//      Reserved   --  Reserved


//
// The following data type defines the classes of Policy Information / Policy Domain Information
// that may be used to request notification
//

  _POLICY_NOTIFICATION_INFORMATION_CLASS = (
    pnicFiller0,
    PolicyNotifyAuditEventsInformation,
    PolicyNotifyAccountDomainInformation,
    PolicyNotifyServerRoleInformation,
    PolicyNotifyDnsDomainInformation,
    PolicyNotifyDomainEfsInformation,
    PolicyNotifyDomainKerberosTicketInformation,
    PolicyNotifyMachineAccountPasswordInformation);
  {$EXTERNALSYM _POLICY_NOTIFICATION_INFORMATION_CLASS}
  POLICY_NOTIFICATION_INFORMATION_CLASS = _POLICY_NOTIFICATION_INFORMATION_CLASS;
  {$EXTERNALSYM POLICY_NOTIFICATION_INFORMATION_CLASS}
  PPOLICY_NOTIFICATION_INFORMATION_CLASS = ^POLICY_NOTIFICATION_INFORMATION_CLASS;
  {$EXTERNALSYM PPOLICY_NOTIFICATION_INFORMATION_CLASS}
  TPolicyNotificationInformationClass = POLICY_NOTIFICATION_INFORMATION_CLASS;
  PPolicyNotificationInformationClass = PPOLICY_NOTIFICATION_INFORMATION_CLASS;  

//
// LSA RPC Context Handle (Opaque form).  Note that a Context Handle is
// always a pointer type unlike regular handles.
//

  LSA_HANDLE = PVOID;
  {$EXTERNALSYM LSA_HANDLE}
  PLSA_HANDLE = ^LSA_HANDLE;
  {$EXTERNALSYM PLSA_HANDLE}
  TLsaHandle = LSA_HANDLE;

//
// Trusted Domain Object specific data types
//

//
// This data type defines the following information classes that may be
// queried or set.
//

  _TRUSTED_INFORMATION_CLASS = (
    ticFiller0,
    TrustedDomainNameInformation,
    TrustedControllersInformation,
    TrustedPosixOffsetInformation,
    TrustedPasswordInformation,
    TrustedDomainInformationBasic,
    TrustedDomainInformationEx,
    TrustedDomainAuthInformation,
    TrustedDomainFullInformation,
    TrustedDomainAuthInformationInternal,
    TrustedDomainFullInformationInternal,
    TrustedDomainInformationEx2Internal,
    TrustedDomainFullInformation2Internal);
  {$EXTERNALSYM _TRUSTED_INFORMATION_CLASS}
  TRUSTED_INFORMATION_CLASS = _TRUSTED_INFORMATION_CLASS;
  {$EXTERNALSYM TRUSTED_INFORMATION_CLASS}
  PTRUSTED_INFORMATION_CLASS = ^TRUSTED_INFORMATION_CLASS;
  {$EXTERNALSYM PTRUSTED_INFORMATION_CLASS}
  TTrustedInfomationClass = TRUSTED_INFORMATION_CLASS;
  PTrustedInfomationClass = PTRUSTED_INFORMATION_CLASS;  

//
// The following data type corresponds to the TrustedDomainNameInformation
// information class.
//

  PTRUSTED_DOMAIN_NAME_INFO = ^TRUSTED_DOMAIN_NAME_INFO;
  {$EXTERNALSYM PTRUSTED_DOMAIN_NAME_INFO}
  _TRUSTED_DOMAIN_NAME_INFO = record
    Name: LSA_UNICODE_STRING;
  end;
  {$EXTERNALSYM _TRUSTED_DOMAIN_NAME_INFO}
  TRUSTED_DOMAIN_NAME_INFO = _TRUSTED_DOMAIN_NAME_INFO;
  {$EXTERNALSYM TRUSTED_DOMAIN_NAME_INFO}
  TTrustedDomainNameInfo = TRUSTED_DOMAIN_NAME_INFO;
  PTrustedDomainNameInfo = PTRUSTED_DOMAIN_NAME_INFO;

// where members have the following meaning:
//
// Name - The name of the Trusted Domain.
//

//
// The following data type corresponds to the TrustedControllersInformation
// information class.
//

  PTRUSTED_CONTROLLERS_INFO = ^TRUSTED_CONTROLLERS_INFO;
  {$EXTERNALSYM PTRUSTED_CONTROLLERS_INFO}
  _TRUSTED_CONTROLLERS_INFO = record
    Entries: ULONG;
    Names: PLSA_UNICODE_STRING;
  end;
  {$EXTERNALSYM _TRUSTED_CONTROLLERS_INFO}
  TRUSTED_CONTROLLERS_INFO = _TRUSTED_CONTROLLERS_INFO;
  {$EXTERNALSYM TRUSTED_CONTROLLERS_INFO}
  TTrustedControllersInfo = TRUSTED_CONTROLLERS_INFO;
  PTrustedControllersInfo = PTRUSTED_CONTROLLERS_INFO;

// where members have the following meaning:
//
// Entries - Indicate how mamy entries there are in the Names array.
//
// Names - Pointer to an array of LSA_UNICODE_STRING structures containing the
//     names of domain controllers of the domain.  This information may not
//     be accurate and should be used only as a hint.  The order of this
//     list is considered significant and will be maintained.
//
//     By convention, the first name in this list is assumed to be the
//     Primary Domain Controller of the domain.  If the Primary Domain
//     Controller is not known, the first name should be set to the NULL
//     string.
//


//
// The following data type corresponds to the TrustedPosixOffsetInformation
// information class.
//

  PTRUSTED_POSIX_OFFSET_INFO = ^TRUSTED_POSIX_OFFSET_INFO;
  {$EXTERNALSYM PTRUSTED_POSIX_OFFSET_INFO}
  _TRUSTED_POSIX_OFFSET_INFO = record
    Offset: ULONG;
  end;
  {$EXTERNALSYM _TRUSTED_POSIX_OFFSET_INFO}
  TRUSTED_POSIX_OFFSET_INFO = _TRUSTED_POSIX_OFFSET_INFO;
  {$EXTERNALSYM TRUSTED_POSIX_OFFSET_INFO}
  TTrustedPosixOffsetInfo = TRUSTED_POSIX_OFFSET_INFO;
  PTrustedPosixOffsetInfo = PTRUSTED_POSIX_OFFSET_INFO;

// where members have the following meaning:
//
// Offset - Is an offset to use for the generation of Posix user and group
//     IDs from SIDs.  The Posix ID corresponding to any particular SID is
//     generated by adding the RID of that SID to the Offset of the SID's
//     corresponding TrustedDomain object.
//

//
// The following data type corresponds to the TrustedPasswordInformation
// information class.
//

  PTRUSTED_PASSWORD_INFO = ^TRUSTED_PASSWORD_INFO;
  {$EXTERNALSYM PTRUSTED_PASSWORD_INFO}
  _TRUSTED_PASSWORD_INFO = record
    Password: LSA_UNICODE_STRING;
    OldPassword: LSA_UNICODE_STRING;
  end;
  {$EXTERNALSYM _TRUSTED_PASSWORD_INFO}
  TRUSTED_PASSWORD_INFO = _TRUSTED_PASSWORD_INFO;
  {$EXTERNALSYM TRUSTED_PASSWORD_INFO}
  TTrustedPasswordInfo = TRUSTED_PASSWORD_INFO;
  PTrustedPasswordInfo = PTRUSTED_PASSWORD_INFO;

  TRUSTED_DOMAIN_INFORMATION_BASIC = LSA_TRUST_INFORMATION;
  {$EXTERNALSYM TRUSTED_DOMAIN_INFORMATION_BASIC}
  PTRUSTED_DOMAIN_INFORMATION_BASIC = PLSA_TRUST_INFORMATION;
  {$EXTERNALSYM PTRUSTED_DOMAIN_INFORMATION_BASIC}
  TTrustedDomainInformationBasic = TRUSTED_DOMAIN_INFORMATION_BASIC;
  PTrustedDomainInformationBasic = PTRUSTED_DOMAIN_INFORMATION_BASIC;

//
// Direction of the trust
//

const
  TRUST_DIRECTION_DISABLED      = $00000000;
  {$EXTERNALSYM TRUST_DIRECTION_DISABLED}
  TRUST_DIRECTION_INBOUND       = $00000001;
  {$EXTERNALSYM TRUST_DIRECTION_INBOUND}
  TRUST_DIRECTION_OUTBOUND      = $00000002;
  {$EXTERNALSYM TRUST_DIRECTION_OUTBOUND}
  TRUST_DIRECTION_BIDIRECTIONAL = (TRUST_DIRECTION_INBOUND or TRUST_DIRECTION_OUTBOUND);
  {$EXTERNALSYM TRUST_DIRECTION_BIDIRECTIONAL}

  TRUST_TYPE_DOWNLEVEL = $00000001; // NT4 and before
  {$EXTERNALSYM TRUST_TYPE_DOWNLEVEL}
  TRUST_TYPE_UPLEVEL   = $00000002; // NT5
  {$EXTERNALSYM TRUST_TYPE_UPLEVEL}
  TRUST_TYPE_MIT       = $00000003; // Trust with a MIT Kerberos realm
  {$EXTERNALSYM TRUST_TYPE_MIT}
// TRUST_TYPE_DCE       = $00000004; // Trust with a DCE realm
// {$EXTERNALSYM TRUST_TYPE_DCE}
// Levels 0x5 - 0x000FFFFF reserved for future use
// Provider specific trust levels are from 0x00100000 to 0xFFF00000

  TRUST_ATTRIBUTE_NON_TRANSITIVE     = $00000001;  // Disallow transitivity
  {$EXTERNALSYM TRUST_ATTRIBUTE_NON_TRANSITIVE}
  TRUST_ATTRIBUTE_UPLEVEL_ONLY       = $00000002;  // Trust link only valid for uplevel client
  {$EXTERNALSYM TRUST_ATTRIBUTE_UPLEVEL_ONLY}
  TRUST_ATTRIBUTE_QUARANTINED_DOMAIN = $00000004;  // Used to quarantine domains
  {$EXTERNALSYM TRUST_ATTRIBUTE_QUARANTINED_DOMAIN}
  TRUST_ATTRIBUTE_FOREST_TRANSITIVE  = $00000008;  // This link may contain forest trust information
  {$EXTERNALSYM TRUST_ATTRIBUTE_FOREST_TRANSITIVE}
  TRUST_ATTRIBUTE_CROSS_ORGANIZATION = $00000010;  // This trust is to a domain/forest which is not part of this enterprise
  {$EXTERNALSYM TRUST_ATTRIBUTE_CROSS_ORGANIZATION}
  TRUST_ATTRIBUTE_WITHIN_FOREST      = $00000020;  // Trust is internal to this forest
  {$EXTERNALSYM TRUST_ATTRIBUTE_WITHIN_FOREST}
  TRUST_ATTRIBUTE_TREAT_AS_EXTERNAL  = $00000040;  // Trust is to be treated as external for trust boundary purposes
  {$EXTERNALSYM TRUST_ATTRIBUTE_TREAT_AS_EXTERNAL}

// Trust attributes 0x00000040 through 0x00200000 are reserved for future use
// Trust attributes 0x00400000 through 0x00800000 were used previously (up to W2K) and should not be re-used
// Trust attributes 0x01000000 through 0x80000000 are reserved for user

  TRUST_ATTRIBUTES_VALID = DWORD($FF03FFFF);
  {$EXTERNALSYM TRUST_ATTRIBUTES_VALID}
  TRUST_ATTRIBUTES_USER  = DWORD($FF000000);
  {$EXTERNALSYM TRUST_ATTRIBUTES_USER}

type
  PTRUSTED_DOMAIN_INFORMATION_EX = ^TRUSTED_DOMAIN_INFORMATION_EX;
  {$EXTERNALSYM PTRUSTED_DOMAIN_INFORMATION_EX}
  _TRUSTED_DOMAIN_INFORMATION_EX = record
    Name: LSA_UNICODE_STRING;
    FlatName: LSA_UNICODE_STRING;
    Sid: PSID;
    TrustDirection: ULONG;
    TrustType: ULONG;
    TrustAttributes: ULONG;
  end;
  {$EXTERNALSYM _TRUSTED_DOMAIN_INFORMATION_EX}
  TRUSTED_DOMAIN_INFORMATION_EX = _TRUSTED_DOMAIN_INFORMATION_EX;
  {$EXTERNALSYM TRUSTED_DOMAIN_INFORMATION_EX}
  TTrustedDomainInformationEx = TRUSTED_DOMAIN_INFORMATION_EX;
  PTrustedDomainInformationEx = PTRUSTED_DOMAIN_INFORMATION_EX;

  _TRUSTED_DOMAIN_INFORMATION_EX2 = record
    Name: LSA_UNICODE_STRING;
    FlatName: LSA_UNICODE_STRING;
    Sid: PSID;
    TrustDirection: ULONG;
    TrustType: ULONG;
    TrustAttributes: ULONG;
    ForestTrustLength: ULONG;
    ForestTrustInfo: PUCHAR;
  end;
  {$EXTERNALSYM _TRUSTED_DOMAIN_INFORMATION_EX2}
  TRUSTED_DOMAIN_INFORMATION_EX2 = _TRUSTED_DOMAIN_INFORMATION_EX2;
  {$EXTERNALSYM TRUSTED_DOMAIN_INFORMATION_EX2}
  PTRUSTED_DOMAIN_INFORMATION_EX2 = ^TRUSTED_DOMAIN_INFORMATION_EX2;
  {$EXTERNALSYM PTRUSTED_DOMAIN_INFORMATION_EX2}
  TTrustedDomainInformationEx2 = TRUSTED_DOMAIN_INFORMATION_EX2;
  PTrustedDomainInformationEx2 = PTRUSTED_DOMAIN_INFORMATION_EX2;

//
// Type of authentication information
//

const
  TRUST_AUTH_TYPE_NONE    = 0; // Ignore this entry
  {$EXTERNALSYM TRUST_AUTH_TYPE_NONE}
  TRUST_AUTH_TYPE_NT4OWF  = 1; // NT4 OWF password
  {$EXTERNALSYM TRUST_AUTH_TYPE_NT4OWF}
  TRUST_AUTH_TYPE_CLEAR   = 2; // Cleartext password
  {$EXTERNALSYM TRUST_AUTH_TYPE_CLEAR}
  TRUST_AUTH_TYPE_VERSION = 3; // Cleartext password version number
  {$EXTERNALSYM TRUST_AUTH_TYPE_VERSION}

type
  PLSA_AUTH_INFORMATION = ^LSA_AUTH_INFORMATION;
  {$EXTERNALSYM PLSA_AUTH_INFORMATION}
  _LSA_AUTH_INFORMATION = record
    LastUpdateTime: LARGE_INTEGER;
    AuthType: ULONG;
    AuthInfoLength: ULONG;
    AuthInfo: PUCHAR;
  end;
  {$EXTERNALSYM _LSA_AUTH_INFORMATION}
  LSA_AUTH_INFORMATION = _LSA_AUTH_INFORMATION;
  {$EXTERNALSYM LSA_AUTH_INFORMATION}
  TLsaAuthInformation = LSA_AUTH_INFORMATION;
  PLsaAuthInformation = PLSA_AUTH_INFORMATION;

  PTRUSTED_DOMAIN_AUTH_INFORMATION = ^TRUSTED_DOMAIN_AUTH_INFORMATION;
  {$EXTERNALSYM PTRUSTED_DOMAIN_AUTH_INFORMATION}
  _TRUSTED_DOMAIN_AUTH_INFORMATION = record
    IncomingAuthInfos: ULONG;
    IncomingAuthenticationInformation: PLSA_AUTH_INFORMATION;
    IncomingPreviousAuthenticationInformation: PLSA_AUTH_INFORMATION;
    OutgoingAuthInfos: ULONG;
    OutgoingAuthenticationInformation: PLSA_AUTH_INFORMATION;
    OutgoingPreviousAuthenticationInformation: PLSA_AUTH_INFORMATION;
  end;
  {$EXTERNALSYM _TRUSTED_DOMAIN_AUTH_INFORMATION}
  TRUSTED_DOMAIN_AUTH_INFORMATION = _TRUSTED_DOMAIN_AUTH_INFORMATION;
  {$EXTERNALSYM TRUSTED_DOMAIN_AUTH_INFORMATION}
  TTrustedDomainAuthInformation = TRUSTED_DOMAIN_AUTH_INFORMATION;
  PTrustedDomainAuthInformation = PTRUSTED_DOMAIN_AUTH_INFORMATION;

  PTRUSTED_DOMAIN_FULL_INFORMATION = ^TRUSTED_DOMAIN_FULL_INFORMATION;
  {$EXTERNALSYM PTRUSTED_DOMAIN_FULL_INFORMATION}
  _TRUSTED_DOMAIN_FULL_INFORMATION = record
    Information: TRUSTED_DOMAIN_INFORMATION_EX;
    PosixOffset: TRUSTED_POSIX_OFFSET_INFO;
    AuthInformation: TRUSTED_DOMAIN_AUTH_INFORMATION;
  end;
  {$EXTERNALSYM _TRUSTED_DOMAIN_FULL_INFORMATION}
  TRUSTED_DOMAIN_FULL_INFORMATION = _TRUSTED_DOMAIN_FULL_INFORMATION;
  {$EXTERNALSYM TRUSTED_DOMAIN_FULL_INFORMATION}
  TTrustedDomainFullInformation = TRUSTED_DOMAIN_FULL_INFORMATION;
  PTrustedDomainFullInformation = PTRUSTED_DOMAIN_FULL_INFORMATION;

  PTRUSTED_DOMAIN_FULL_INFORMATION2 = ^TRUSTED_DOMAIN_FULL_INFORMATION2;
  {$EXTERNALSYM PTRUSTED_DOMAIN_FULL_INFORMATION2}
  _TRUSTED_DOMAIN_FULL_INFORMATION2 = record
    Information: TRUSTED_DOMAIN_INFORMATION_EX2;
    PosixOffset: TRUSTED_POSIX_OFFSET_INFO;
    AuthInformation: TRUSTED_DOMAIN_AUTH_INFORMATION;
  end;
  {$EXTERNALSYM _TRUSTED_DOMAIN_FULL_INFORMATION2}
  TRUSTED_DOMAIN_FULL_INFORMATION2 = _TRUSTED_DOMAIN_FULL_INFORMATION2;
  {$EXTERNALSYM TRUSTED_DOMAIN_FULL_INFORMATION2}
  TTrustedDomainFullInformation2 = TRUSTED_DOMAIN_FULL_INFORMATION2;
  PTrustedDomainFullInformation2 = PTRUSTED_DOMAIN_FULL_INFORMATION2;

  LSA_FOREST_TRUST_RECORD_TYPE = (
    ForestTrustTopLevelName,
    ForestTrustTopLevelNameEx,
    ForestTrustDomainInfo);
  {$EXTERNALSYM LSA_FOREST_TRUST_RECORD_TYPE}
  TLsaForestTrustRecordType = LSA_FOREST_TRUST_RECORD_TYPE;

const
  ForestTrustRecordTypeLast = ForestTrustDomainInfo;
  {$EXTERNALSYM ForestTrustRecordTypeLast}

//
// Bottom 16 bits of the flags are reserved for disablement reasons
//

  LSA_FTRECORD_DISABLED_REASONS = $0000FFFF;
  {$EXTERNALSYM LSA_FTRECORD_DISABLED_REASONS}

//
// Reasons for a top-level name forest trust record to be disabled
//

  LSA_TLN_DISABLED_NEW      = $00000001;
  {$EXTERNALSYM LSA_TLN_DISABLED_NEW}
  LSA_TLN_DISABLED_ADMIN    = $00000002;
  {$EXTERNALSYM LSA_TLN_DISABLED_ADMIN}
  LSA_TLN_DISABLED_CONFLICT = $00000004;
  {$EXTERNALSYM LSA_TLN_DISABLED_CONFLICT}

//
// Reasons for a domain information forest trust record to be disabled
//

  LSA_SID_DISABLED_ADMIN    = $00000001;
  {$EXTERNALSYM LSA_SID_DISABLED_ADMIN}
  LSA_SID_DISABLED_CONFLICT = $00000002;
  {$EXTERNALSYM LSA_SID_DISABLED_CONFLICT}
  LSA_NB_DISABLED_ADMIN     = $00000004;
  {$EXTERNALSYM LSA_NB_DISABLED_ADMIN}
  LSA_NB_DISABLED_CONFLICT  = $00000008;
  {$EXTERNALSYM LSA_NB_DISABLED_CONFLICT}

type
  PLSA_FOREST_TRUST_DOMAIN_INFO = ^LSA_FOREST_TRUST_DOMAIN_INFO;
  {$EXTERNALSYM PLSA_FOREST_TRUST_DOMAIN_INFO}
  _LSA_FOREST_TRUST_DOMAIN_INFO = record
    Sid: PSID;
    DnsName: LSA_UNICODE_STRING;
    NetbiosName: LSA_UNICODE_STRING;
  end;
  {$EXTERNALSYM _LSA_FOREST_TRUST_DOMAIN_INFO}
  LSA_FOREST_TRUST_DOMAIN_INFO = _LSA_FOREST_TRUST_DOMAIN_INFO;
  {$EXTERNALSYM LSA_FOREST_TRUST_DOMAIN_INFO}
  TLsaForestTrustDomainInfo = LSA_FOREST_TRUST_DOMAIN_INFO;
  PLsaForestTrustDomainInfo = PLSA_FOREST_TRUST_DOMAIN_INFO;

//
//  To prevent huge data to be passed in, we should put a limit on LSA_FOREST_TRUST_BINARY_DATA.
//      128K is large enough that can't be reached in the near future, and small enough not to
//      cause memory problems.

const
  MAX_FOREST_TRUST_BINARY_DATA_SIZE = (128 * 1024);
  {$EXTERNALSYM MAX_FOREST_TRUST_BINARY_DATA_SIZE}

type
  PLSA_FOREST_TRUST_BINARY_DATA = ^LSA_FOREST_TRUST_BINARY_DATA;
  {$EXTERNALSYM PLSA_FOREST_TRUST_BINARY_DATA}
  _LSA_FOREST_TRUST_BINARY_DATA = record
    Length: ULONG;
    Buffer: PUCHAR;
  end;
  {$EXTERNALSYM _LSA_FOREST_TRUST_BINARY_DATA}
  LSA_FOREST_TRUST_BINARY_DATA = _LSA_FOREST_TRUST_BINARY_DATA;
  {$EXTERNALSYM LSA_FOREST_TRUST_BINARY_DATA}
  TLsaForestTrustBinaryData = LSA_FOREST_TRUST_BINARY_DATA;
  PLsaForestTrustBinaryData = PLSA_FOREST_TRUST_BINARY_DATA;

  PLSA_FOREST_TRUST_RECORD = ^LSA_FOREST_TRUST_RECORD;
  {$EXTERNALSYM PLSA_FOREST_TRUST_RECORD}
  _LSA_FOREST_TRUST_RECORD = record
    Flags: ULONG;
    ForestTrustType: LSA_FOREST_TRUST_RECORD_TYPE; // type of record
    Time: LARGE_INTEGER;
    case Integer of                                       // actual data
      0: (TopLevelName: LSA_UNICODE_STRING);
      1: (DomainInfo: LSA_FOREST_TRUST_DOMAIN_INFO);
      2: (Data: LSA_FOREST_TRUST_BINARY_DATA); // used for unrecognized types
    // } ForestTrustData;
  end;
  {$EXTERNALSYM _LSA_FOREST_TRUST_RECORD}
  LSA_FOREST_TRUST_RECORD = _LSA_FOREST_TRUST_RECORD;
  {$EXTERNALSYM LSA_FOREST_TRUST_RECORD}
  TLsaForestTrustRecord = LSA_FOREST_TRUST_RECORD;
  PLsaForestTrustRecord = PLSA_FOREST_TRUST_RECORD;

//
// To prevent forest trust blobs of large size, number of records must be
// smaller than MAX_RECORDS_IN_FOREST_TRUST_INFO
//

const
  MAX_RECORDS_IN_FOREST_TRUST_INFO = 4000;
  {$EXTERNALSYM MAX_RECORDS_IN_FOREST_TRUST_INFO}

type
  PLSA_FOREST_TRUST_INFORMATION = ^LSA_FOREST_TRUST_INFORMATION;
  {$EXTERNALSYM PLSA_FOREST_TRUST_INFORMATION}
  _LSA_FOREST_TRUST_INFORMATION = record
    RecordCount: ULONG;
    Entries: ^PLSA_FOREST_TRUST_RECORD;
  end;
  {$EXTERNALSYM _LSA_FOREST_TRUST_INFORMATION}
  LSA_FOREST_TRUST_INFORMATION = _LSA_FOREST_TRUST_INFORMATION;
  {$EXTERNALSYM LSA_FOREST_TRUST_INFORMATION}
  TLsaForestTrustInformation = LSA_FOREST_TRUST_INFORMATION;
  PLsaForestTrustInformation = PLSA_FOREST_TRUST_INFORMATION;

  LSA_FOREST_TRUST_COLLISION_RECORD_TYPE = (
    CollisionTdo,
    CollisionXref,
    CollisionOther);
  {$EXTERNALSYM LSA_FOREST_TRUST_COLLISION_RECORD_TYPE}
  TLsaForestTrustCollisionRecordType = LSA_FOREST_TRUST_COLLISION_RECORD_TYPE;

  PLSA_FOREST_TRUST_COLLISION_RECORD = ^LSA_FOREST_TRUST_COLLISION_RECORD;
  {$EXTERNALSYM PLSA_FOREST_TRUST_COLLISION_RECORD}
  _LSA_FOREST_TRUST_COLLISION_RECORD = record
    Index: ULONG;
    Type_: LSA_FOREST_TRUST_COLLISION_RECORD_TYPE;
    Flags: ULONG;
    Name: LSA_UNICODE_STRING;
  end;
  {$EXTERNALSYM _LSA_FOREST_TRUST_COLLISION_RECORD}
  LSA_FOREST_TRUST_COLLISION_RECORD = _LSA_FOREST_TRUST_COLLISION_RECORD;
  {$EXTERNALSYM LSA_FOREST_TRUST_COLLISION_RECORD}
  TLsaForestTrustCollisionRecord = LSA_FOREST_TRUST_COLLISION_RECORD;
  PLsaForestTrustCollisionRecord = PLSA_FOREST_TRUST_COLLISION_RECORD;

  PLSA_FOREST_TRUST_COLLISION_INFORMATION = ^LSA_FOREST_TRUST_COLLISION_INFORMATION;
  {$EXTERNALSYM PLSA_FOREST_TRUST_COLLISION_INFORMATION}
  _LSA_FOREST_TRUST_COLLISION_INFORMATION = record
    RecordCount: ULONG;
    Entries: ^PLSA_FOREST_TRUST_COLLISION_RECORD;
  end;
  {$EXTERNALSYM _LSA_FOREST_TRUST_COLLISION_INFORMATION}
  LSA_FOREST_TRUST_COLLISION_INFORMATION = _LSA_FOREST_TRUST_COLLISION_INFORMATION;
  {$EXTERNALSYM LSA_FOREST_TRUST_COLLISION_INFORMATION}
  TLsaForestTrustCollisionInformation = LSA_FOREST_TRUST_COLLISION_INFORMATION;
  PLsaForestTrustCollisionInformation = PLSA_FOREST_TRUST_COLLISION_INFORMATION;

//
// LSA Enumeration Context
//

  LSA_ENUMERATION_HANDLE = ULONG;
  {$EXTERNALSYM LSA_ENUMERATION_HANDLE}
  PLSA_ENUMERATION_HANDLE = LSA_ENUMERATION_HANDLE;
  {$EXTERNALSYM PLSA_ENUMERATION_HANDLE}

//
// LSA Enumeration Information
//

  PLSA_ENUMERATION_INFORMATION = ^LSA_ENUMERATION_INFORMATION;
  {$EXTERNALSYM PLSA_ENUMERATION_INFORMATION}
  _LSA_ENUMERATION_INFORMATION = record
    Sid: PSID;
  end;
  {$EXTERNALSYM _LSA_ENUMERATION_INFORMATION}
  LSA_ENUMERATION_INFORMATION = _LSA_ENUMERATION_INFORMATION;
  {$EXTERNALSYM LSA_ENUMERATION_INFORMATION}
  TLsaEnumerationInformation = LSA_ENUMERATION_INFORMATION;
  PLsaEnumerationInformation = PLSA_ENUMERATION_INFORMATION;

////////////////////////////////////////////////////////////////////////////
//                                                                        //
// Local Security Policy - Miscellaneous API function prototypes          //
//                                                                        //
////////////////////////////////////////////////////////////////////////////


function LsaFreeMemory(Buffer: PVOID): NTSTATUS; stdcall;
{$EXTERNALSYM LsaFreeMemory}

function LsaClose(ObjectHandle: LSA_HANDLE): NTSTATUS; stdcall;
{$EXTERNALSYM LsaClose}

type
  _SECURITY_LOGON_SESSION_DATA = record
    Size: ULONG;
    LogonId: LUID;
    UserName: LSA_UNICODE_STRING;
    LogonDomain: LSA_UNICODE_STRING;
    AuthenticationPackage: LSA_UNICODE_STRING;
    LogonType: SECURITY_LOGON_TYPE;
    Session: ULONG;
    Sid: PSID;
    LogonTime: LARGE_INTEGER;

    //
    // new for whistler:
    //

    LogonServer: LSA_UNICODE_STRING;
    DnsDomainName: LSA_UNICODE_STRING;
    Upn: LSA_UNICODE_STRING;
  end;
  {$EXTERNALSYM _SECURITY_LOGON_SESSION_DATA}
  SECURITY_LOGON_SESSION_DATA = _SECURITY_LOGON_SESSION_DATA;
  {$EXTERNALSYM SECURITY_LOGON_SESSION_DATA}
  PSECURITY_LOGON_SESSION_DATA = ^SECURITY_LOGON_SESSION_DATA;
  {$EXTERNALSYM PSECURITY_LOGON_SESSION_DATA}
  TSecurityLogonSessionData = SECURITY_LOGON_SESSION_DATA;
  PSecurityLogonSessionData = PSECURITY_LOGON_SESSION_DATA;


function LsaEnumerateLogonSessions(LogonSessionCount: PULONG; var LogonSessionList: PLUID): NTSTATUS; stdcall;
{$EXTERNALSYM LsaEnumerateLogonSessions}

function LsaGetLogonSessionData(LogonId: PLUID; var ppLogonSessionData: PSECURITY_LOGON_SESSION_DATA): NTSTATUS; stdcall;
{$EXTERNALSYM LsaGetLogonSessionData}

function LsaOpenPolicy(SystemName: PLSA_UNICODE_STRING;
  var ObjectAttributes: LSA_OBJECT_ATTRIBUTES; DesiredAccess: ACCESS_MASK;
  var PolicyHandle: LSA_HANDLE): NTSTATUS; stdcall;
{$EXTERNALSYM LsaOpenPolicy}

function LsaQueryInformationPolicy(PolicyHandle: LSA_HANDLE;
  InformationClass: POLICY_INFORMATION_CLASS; var Buffer: PVOID): NTSTATUS; stdcall;
{$EXTERNALSYM LsaQueryInformationPolicy}

function LsaSetInformationPolicy(PolicyHandle: LSA_HANDLE;
  InformationClass: POLICY_INFORMATION_CLASS; Buffer: PVOID): NTSTATUS; stdcall;
{$EXTERNALSYM LsaSetInformationPolicy}

function LsaQueryDomainInformationPolicy(PolicyHandle: LSA_HANDLE;
  InformationClass: POLICY_DOMAIN_INFORMATION_CLASS; Buffer: PPVOID): NTSTATUS; stdcall;
{$EXTERNALSYM LsaQueryDomainInformationPolicy}

function LsaSetDomainInformationPolicy(PolicyHandle: LSA_HANDLE;
  InformationClass: POLICY_DOMAIN_INFORMATION_CLASS; Buffer: PVOID): NTSTATUS; stdcall;
{$EXTERNALSYM LsaSetDomainInformationPolicy}

function LsaRegisterPolicyChangeNotification(InformationClass: POLICY_NOTIFICATION_INFORMATION_CLASS;
  NotificationEventHandle: HANDLE): NTSTATUS; stdcall;
{$EXTERNALSYM LsaRegisterPolicyChangeNotification}

function LsaUnregisterPolicyChangeNotification(InformationClass: POLICY_NOTIFICATION_INFORMATION_CLASS;
  NotificationEventHandle: HANDLE): NTSTATUS; stdcall;
{$EXTERNALSYM LsaUnregisterPolicyChangeNotification}

function LsaEnumerateTrustedDomains(PolicyHandle: LSA_HANDLE;
  var EnumerationContext: LSA_ENUMERATION_HANDLE; Buffer: PPVOID;
  PreferedMaximumLength: ULONG; var CountReturned: ULONG): NTSTATUS; stdcall;
{$EXTERNALSYM LsaEnumerateTrustedDomains}

function LsaLookupNames(PolicyHandle: LSA_HANDLE; Count: ULONG;
  Names: PLSA_UNICODE_STRING; var ReferencedDomains: PLSA_REFERENCED_DOMAIN_LIST;
  var Sids: PLSA_TRANSLATED_SID): NTSTATUS; stdcall;
{$EXTERNALSYM LsaLookupNames}

function LsaLookupNames2(PolicyHandle: LSA_HANDLE; Flags, Count: ULONG; Names: PLSA_UNICODE_STRING;
  var ReferencedDomains: PLSA_REFERENCED_DOMAIN_LIST; var Sids: PLSA_TRANSLATED_SID2): NTSTATUS; stdcall;
{$EXTERNALSYM LsaLookupNames2}

function LsaLookupSids(PolicyHandle: LSA_HANDLE; Count: ULONG; Sids: PPSID;
  var ReferencedDomains: PLSA_REFERENCED_DOMAIN_LIST;
  var Names: PLSA_TRANSLATED_NAME): NTSTATUS; stdcall;
{$EXTERNALSYM LsaLookupSids}

const
  SE_INTERACTIVE_LOGON_NAME      = 'SeInteractiveLogonRight';
  {$EXTERNALSYM SE_INTERACTIVE_LOGON_NAME}
  SE_NETWORK_LOGON_NAME          = 'SeNetworkLogonRight';
  {$EXTERNALSYM SE_NETWORK_LOGON_NAME}
  SE_BATCH_LOGON_NAME            = 'SeBatchLogonRight';
  {$EXTERNALSYM SE_BATCH_LOGON_NAME}
  SE_SERVICE_LOGON_NAME          = 'SeServiceLogonRight';
  {$EXTERNALSYM SE_SERVICE_LOGON_NAME}
  SE_DENY_INTERACTIVE_LOGON_NAME = 'SeDenyInteractiveLogonRight';
  {$EXTERNALSYM SE_DENY_INTERACTIVE_LOGON_NAME}
  SE_DENY_NETWORK_LOGON_NAME     = 'SeDenyNetworkLogonRight';
  {$EXTERNALSYM SE_DENY_NETWORK_LOGON_NAME}
  SE_DENY_BATCH_LOGON_NAME       = 'SeDenyBatchLogonRight';
  {$EXTERNALSYM SE_DENY_BATCH_LOGON_NAME}
  SE_DENY_SERVICE_LOGON_NAME     = 'SeDenyServiceLogonRight';
  {$EXTERNALSYM SE_DENY_SERVICE_LOGON_NAME}
  SE_REMOTE_INTERACTIVE_LOGON_NAME  = 'SeRemoteInteractiveLogonRight';
  {$EXTERNALSYM SE_REMOTE_INTERACTIVE_LOGON_NAME}
  SE_DENY_REMOTE_INTERACTIVE_LOGON_NAME = 'SeDenyRemoteInteractiveLogonRight';
  {$EXTERNALSYM SE_DENY_REMOTE_INTERACTIVE_LOGON_NAME}

//
// This new API returns all the accounts with a certain privilege
//

function LsaEnumerateAccountsWithUserRight(PolicyHandle: LSA_HANDLE;
  UserRights: PLSA_UNICODE_STRING; var EnumerationBuffer: PLSA_ENUMERATION_INFORMATION;
  var CountReturned: ULONG): NTSTATUS; stdcall;
{$EXTERNALSYM LsaEnumerateAccountsWithUserRight}

//
// These new APIs differ by taking a SID instead of requiring the caller
// to open the account first and passing in an account handle
//

function LsaEnumerateAccountRights(PolicyHandle: LSA_HANDLE; AccountSid: PSID;
  var UserRights: PLSA_UNICODE_STRING; var CountOfRights: ULONG): NTSTATUS; stdcall;
{$EXTERNALSYM LsaEnumerateAccountRights}

function LsaAddAccountRights(PolicyHandle: LSA_HANDLE; AccountSid: PSID;
  UserRights: PLSA_UNICODE_STRING; CountOfRights: ULONG): NTSTATUS; stdcall;
{$EXTERNALSYM LsaAddAccountRights}

function LsaRemoveAccountRights(PolicyHandle: LSA_HANDLE; AccountSid: PSID;
  AllRights: ByteBool; UserRights: PLSA_UNICODE_STRING; CountOfRights: ULONG): NTSTATUS; stdcall;
{$EXTERNALSYM LsaRemoveAccountRights}

///////////////////////////////////////////////////////////////////////////////
//                                                                           //
// Local Security Policy - Trusted Domain Object API function prototypes     //
//                                                                           //
///////////////////////////////////////////////////////////////////////////////

function LsaOpenTrustedDomainByName(PolicyHandle: LSA_HANDLE;
  const TrustedDomainName: LSA_UNICODE_STRING; DesiredAccess: ACCESS_MASK;
  var TrustedDomainHandle: LSA_HANDLE): NTSTATUS; stdcall;
{$EXTERNALSYM LsaOpenTrustedDomainByName}

function LsaQueryTrustedDomainInfo(PolicyHandle: LSA_HANDLE; TrustedDomainSid: PSID;
  InformationClass: TRUSTED_INFORMATION_CLASS; Buffer: PPVOID): NTSTATUS; stdcall;
{$EXTERNALSYM LsaQueryTrustedDomainInfo}

function LsaSetTrustedDomainInformation(PolicyHandle: LSA_HANDLE; TrustedDomainSid: PSID;
  InformationClass: TRUSTED_INFORMATION_CLASS; Buffer: PVOID): NTSTATUS; stdcall;
{$EXTERNALSYM LsaSetTrustedDomainInformation}

function LsaDeleteTrustedDomain(PolicyHandle: LSA_HANDLE; TrustedDomainSid: PSID): NTSTATUS; stdcall;
{$EXTERNALSYM LsaDeleteTrustedDomain}

function LsaQueryTrustedDomainInfoByName(PolicyHandle: LSA_HANDLE;
  const TrustedDomainName: LSA_UNICODE_STRING;
  InformationClass: TRUSTED_INFORMATION_CLASS; Buffer: PPVOID): NTSTATUS; stdcall;
{$EXTERNALSYM LsaQueryTrustedDomainInfoByName}

function LsaSetTrustedDomainInfoByName(PolicyHandle: LSA_HANDLE;
  const TrustedDomainName: LSA_UNICODE_STRING;
  InformationClass: TRUSTED_INFORMATION_CLASS; Buffer: PVOID): NTSTATUS; stdcall;
{$EXTERNALSYM LsaSetTrustedDomainInfoByName}

function LsaEnumerateTrustedDomainsEx(PolicyHandle: LSA_HANDLE;
  var EnumerationContext: LSA_ENUMERATION_HANDLE; Buffer: PPVOID;
  PreferedMaximumLength: ULONG; var CountReturned: ULONG): NTSTATUS; stdcall;
{$EXTERNALSYM LsaEnumerateTrustedDomainsEx}

function LsaCreateTrustedDomainEx(PolicyHandle: LSA_HANDLE;
  const TrustedDomainInformation: TRUSTED_DOMAIN_INFORMATION_EX;
  const AuthenticationInformation: TRUSTED_DOMAIN_AUTH_INFORMATION;
  DesiredAccess: ACCESS_MASK; var TrustedDomainHandle: LSA_HANDLE): NTSTATUS; stdcall;
{$EXTERNALSYM LsaCreateTrustedDomainEx}

function LsaQueryForestTrustInformation(PolicyHandle: LSA_HANDLE; TrustedDomainName: PLSA_UNICODE_STRING;
  var ForestTrustInfo: PLSA_FOREST_TRUST_INFORMATION): NTSTATUS; stdcall;
{$EXTERNALSYM LsaQueryForestTrustInformation}

function LsaSetForestTrustInformation(PolicyHandle: LSA_HANDLE; TrustedDomainName: PLSA_UNICODE_STRING;
  ForestTrustInfo: PLSA_FOREST_TRUST_INFORMATION; CheckOnly: BOOLEAN; var CollisionInfo: PLSA_FOREST_TRUST_COLLISION_INFORMATION): NTSTATUS; stdcall;
{$EXTERNALSYM LsaSetForestTrustInformation}

//{$DEFINE TESTING_MATCHING_ROUTINE}

{$IFDEF TESTING_MATCHING_ROUTINE}

function LsaForestTrustFindMatch(PolicyHandle: LSA_HANDLE; Type_: ULONG; Name: PLSA_UNICODE_STRING; var Match: PLSA_UNICODE_STRING): NTSTATUS; stdcall;
{$EXTERNALSYM LsaForestTrustFindMatch}

{$ENDIF}

//
// This API sets the workstation password (equivalent of setting/getting
// the SSI_SECRET_NAME secret)
//

function LsaStorePrivateData(PolicyHandle: LSA_HANDLE;
  const KeyName: LSA_UNICODE_STRING; PrivateData: PLSA_UNICODE_STRING): NTSTATUS; stdcall;
{$EXTERNALSYM LsaStorePrivateData}

function LsaRetrievePrivateData(PolicyHandle: LSA_HANDLE;
  const KeyName: LSA_UNICODE_STRING; var PrivateData: PLSA_UNICODE_STRING): NTSTATUS; stdcall;
{$EXTERNALSYM LsaRetrievePrivateData}

function LsaNtStatusToWinError(Status: NTSTATUS): ULONG; stdcall;
{$EXTERNALSYM LsaNtStatusToWinError}

(*#if 0
NTSTATUS
NTAPI
LsaLookupNamesEx(
    IN LSA_HANDLE PolicyHandle,
    IN ULONG Count,
    IN PLSA_NAME_LOOKUP_EX Names,
    OUT PLSA_TRANSLATED_SID_EX *TranslatedSids,
    IN ULONG LookupOptions,
    IN OUT PULONG MappedCount
    );

NTSTATUS
NTAPI
LsaLookupSidsEx(
    IN LSA_HANDLE PolicyHandle,
    IN ULONG Count,
    IN PLSA_SID_LOOKUP_EX Sids,
    OUT PLSA_TRANSLATED_NAME_EX *TranslatedNames,
    IN ULONG LookupOptions,
    IN OUT PULONG MappedCount
    );
#endif*)

//
// SPNEGO package stuff
//

type
  NEGOTIATE_MESSAGES = (NegEnumPackagePrefixes, NegGetCallerName, NegCallPackageMax);
  {$EXTERNALSYM NEGOTIATE_MESSAGES}

const
  NEGOTIATE_MAX_PREFIX = 32;
  {$EXTERNALSYM NEGOTIATE_MAX_PREFIX}

type
  PNEGOTIATE_PACKAGE_PREFIX = ^NEGOTIATE_PACKAGE_PREFIX;
  {$EXTERNALSYM PNEGOTIATE_PACKAGE_PREFIX}
  _NEGOTIATE_PACKAGE_PREFIX = record
    PackageId: ULONG_PTR;
    PackageDataA: PVOID;
    PackageDataW: PVOID;
    PrefixLen: ULONG_PTR;
    Prefix: array [0..NEGOTIATE_MAX_PREFIX - 1] of UCHAR;
  end;
  {$EXTERNALSYM _NEGOTIATE_PACKAGE_PREFIX}
  NEGOTIATE_PACKAGE_PREFIX = _NEGOTIATE_PACKAGE_PREFIX;
  {$EXTERNALSYM NEGOTIATE_PACKAGE_PREFIX}
  TNegotiatePackagePrefix = NEGOTIATE_PACKAGE_PREFIX;
  PNegotiatePackagePrefix = PNEGOTIATE_PACKAGE_PREFIX;

  PNEGOTIATE_PACKAGE_PREFIXES = ^NEGOTIATE_PACKAGE_PREFIXES;
  {$EXTERNALSYM PNEGOTIATE_PACKAGE_PREFIXES}
  _NEGOTIATE_PACKAGE_PREFIXES = record
    MessageType: ULONG;
    PrefixCount: ULONG;
    Offset: ULONG; // Offset to array of _PREFIX above
    Pad: ULONG;    // Align structure for 64-bit    
  end;
  {$EXTERNALSYM _NEGOTIATE_PACKAGE_PREFIXES}
  NEGOTIATE_PACKAGE_PREFIXES = _NEGOTIATE_PACKAGE_PREFIXES;
  {$EXTERNALSYM NEGOTIATE_PACKAGE_PREFIXES}
  TNegotiatePackagePrefixes = NEGOTIATE_PACKAGE_PREFIXES;
  PNegotiatePackagePrefixes = PNEGOTIATE_PACKAGE_PREFIXES;

  PNEGOTIATE_CALLER_NAME_REQUEST = ^NEGOTIATE_CALLER_NAME_REQUEST;
  {$EXTERNALSYM PNEGOTIATE_CALLER_NAME_REQUEST}
  _NEGOTIATE_CALLER_NAME_REQUEST = record
    MessageType: ULONG;
    LogonId: LUID;
  end;
  {$EXTERNALSYM _NEGOTIATE_CALLER_NAME_REQUEST}
  NEGOTIATE_CALLER_NAME_REQUEST = _NEGOTIATE_CALLER_NAME_REQUEST;
  {$EXTERNALSYM NEGOTIATE_CALLER_NAME_REQUEST}
  TNegotiateCallerNameRequest = NEGOTIATE_CALLER_NAME_REQUEST;
  PNegotiateCallerNameRequest = PNEGOTIATE_CALLER_NAME_REQUEST;

  PNEGOTIATE_CALLER_NAME_RESPONSE = ^NEGOTIATE_CALLER_NAME_RESPONSE;
  {$EXTERNALSYM PNEGOTIATE_CALLER_NAME_RESPONSE}
  _NEGOTIATE_CALLER_NAME_RESPONSE = record
    MessageType: ULONG;
    CallerName: PWSTR;
  end;
  {$EXTERNALSYM _NEGOTIATE_CALLER_NAME_RESPONSE}
  NEGOTIATE_CALLER_NAME_RESPONSE = _NEGOTIATE_CALLER_NAME_RESPONSE;
  {$EXTERNALSYM NEGOTIATE_CALLER_NAME_RESPONSE}
  TNegotiateCallerNameResponse = NEGOTIATE_CALLER_NAME_RESPONSE;
  PNegotiateCallerNameResponse = PNEGOTIATE_CALLER_NAME_RESPONSE;

type
  PDOMAIN_PASSWORD_INFORMATION = ^DOMAIN_PASSWORD_INFORMATION;
  {$EXTERNALSYM PDOMAIN_PASSWORD_INFORMATION}
  _DOMAIN_PASSWORD_INFORMATION = record
    MinPasswordLength: USHORT;
    PasswordHistoryLength: USHORT;
    PasswordProperties: ULONG;
    MaxPasswordAge: LARGE_INTEGER;
    MinPasswordAge: LARGE_INTEGER;
  end;
  {$EXTERNALSYM _DOMAIN_PASSWORD_INFORMATION}
  DOMAIN_PASSWORD_INFORMATION = _DOMAIN_PASSWORD_INFORMATION;
  {$EXTERNALSYM DOMAIN_PASSWORD_INFORMATION}
  TDomainPasswordInformation = DOMAIN_PASSWORD_INFORMATION;
  PDomainPasswordInformation = PDOMAIN_PASSWORD_INFORMATION;

//
// PasswordProperties flags
//

const
  DOMAIN_PASSWORD_COMPLEX         = $00000001;
  {$EXTERNALSYM DOMAIN_PASSWORD_COMPLEX}
  DOMAIN_PASSWORD_NO_ANON_CHANGE  = $00000002;
  {$EXTERNALSYM DOMAIN_PASSWORD_NO_ANON_CHANGE}
  DOMAIN_PASSWORD_NO_CLEAR_CHANGE = $00000004;
  {$EXTERNALSYM DOMAIN_PASSWORD_NO_CLEAR_CHANGE}
  DOMAIN_LOCKOUT_ADMINS           = $00000008;
  {$EXTERNALSYM DOMAIN_LOCKOUT_ADMINS}
  DOMAIN_PASSWORD_STORE_CLEARTEXT = $00000010;
  {$EXTERNALSYM DOMAIN_PASSWORD_STORE_CLEARTEXT}
  DOMAIN_REFUSE_PASSWORD_CHANGE   = $00000020;
  {$EXTERNALSYM DOMAIN_REFUSE_PASSWORD_CHANGE}

type
  PSAM_PASSWORD_NOTIFICATION_ROUTINE = function (UserName: PUNICODE_STRING;
    RelativeId: ULONG; NewPassword: PUNICODE_STRING): NTSTATUS; stdcall;
  {$EXTERNALSYM PSAM_PASSWORD_NOTIFICATION_ROUTINE}
  TSamPasswordNotificationRoutine = PSAM_PASSWORD_NOTIFICATION_ROUTINE;

const
  SAM_PASSWORD_CHANGE_NOTIFY_ROUTINE = 'PasswordChangeNotify';
  {$EXTERNALSYM SAM_PASSWORD_CHANGE_NOTIFY_ROUTINE}

type
  PSAM_INIT_NOTIFICATION_ROUTINE = function : ByteBool; stdcall;
  {$EXTERNALSYM PSAM_INIT_NOTIFICATION_ROUTINE}
  TSamInitNotificationRoutine = PSAM_INIT_NOTIFICATION_ROUTINE;

const
  SAM_INIT_NOTIFICATION_ROUTINE = 'InitializeChangeNotify';
  {$EXTERNALSYM SAM_INIT_NOTIFICATION_ROUTINE}

  SAM_PASSWORD_FILTER_ROUTINE = 'PasswordFilter';
  {$EXTERNALSYM SAM_PASSWORD_FILTER_ROUTINE}

type
  PSAM_PASSWORD_FILTER_ROUTINE = function (AccountName, FullName,
    Password: PUNICODE_STRING; SetOperation: ByteBool): ByteBool; stdcall;
  {$EXTERNALSYM PSAM_PASSWORD_FILTER_ROUTINE}
  TSamPasswordFilterRoutine = PSAM_PASSWORD_FILTER_ROUTINE;

/////////////////////////////////////////////////////////////////////////
//                                                                     //
// Name of the MSV1_0 authentication package                           //
//                                                                     //
/////////////////////////////////////////////////////////////////////////

const
  MSV1_0_PACKAGE_NAME         = 'MICROSOFT_AUTHENTICATION_PACKAGE_V1_0';
  {$EXTERNALSYM MSV1_0_PACKAGE_NAME}
  MSV1_0_PACKAGE_NAMEW        = WideString('MICROSOFT_AUTHENTICATION_PACKAGE_V1_0');
  {$EXTERNALSYM MSV1_0_PACKAGE_NAMEW}
  MSV1_0_PACKAGE_NAMEW_LENGTH = SizeOf(MSV1_0_PACKAGE_NAMEW) - SizeOf(WCHAR);
  {$EXTERNALSYM MSV1_0_PACKAGE_NAMEW_LENGTH}

//
// Location of MSV authentication package data
//

  MSV1_0_SUBAUTHENTICATION_KEY   = 'SYSTEM\\CurrentControlSet\\Control\\Lsa\\MSV1_0';
  {$EXTERNALSYM MSV1_0_SUBAUTHENTICATION_KEY}
  MSV1_0_SUBAUTHENTICATION_VALUE = 'Auth';
  {$EXTERNALSYM MSV1_0_SUBAUTHENTICATION_VALUE}

/////////////////////////////////////////////////////////////////////////
//                                                                     //
// Widely used MSV1_0 data types                                       //
//                                                                     //
/////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
//                                                                           //
//       LOGON      Related Data Structures
//
//                                                                           //
///////////////////////////////////////////////////////////////////////////////

//
// When a LsaLogonUser() call is dispatched to the MsV1_0 authentication
// package, the beginning of the AuthenticationInformation buffer is
// cast to a MSV1_0_LOGON_SUBMIT_TYPE to determine the type of logon
// being requested.  Similarly, upon return, the type of profile buffer
// can be determined by typecasting it to a MSV_1_0_PROFILE_BUFFER_TYPE.
//

//
//  MSV1.0 LsaLogonUser() submission message types.
//

type
  _MSV1_0_LOGON_SUBMIT_TYPE = (
    mlstFiller0, mlstFiller1,
    MsV1_0InteractiveLogon,
    MsV1_0Lm20Logon,
    MsV1_0NetworkLogon,
    MsV1_0SubAuthLogon,
    mlstFiller6,
    MsV1_0WorkstationUnlockLogon);
  {$EXTERNALSYM _MSV1_0_LOGON_SUBMIT_TYPE}
  MSV1_0_LOGON_SUBMIT_TYPE = _MSV1_0_LOGON_SUBMIT_TYPE;
  {$EXTERNALSYM MSV1_0_LOGON_SUBMIT_TYPE}
  PMSV1_0_LOGON_SUBMIT_TYPE = ^MSV1_0_LOGON_SUBMIT_TYPE;
  {$EXTERNALSYM PMSV1_0_LOGON_SUBMIT_TYPE}
  TMsv1_0LogonSubmitType = MSV1_0_LOGON_SUBMIT_TYPE;
  PMsv1_0LogonSubmitType = PMSV1_0_LOGON_SUBMIT_TYPE;

//
//  MSV1.0 LsaLogonUser() profile buffer types.
//

  _MSV1_0_PROFILE_BUFFER_TYPE = (
    mpbtFiller0, mpbtFiller1,
    MsV1_0InteractiveProfile,
    MsV1_0Lm20LogonProfile,
    MsV1_0SmartCardProfile);
  {$EXTERNALSYM _MSV1_0_PROFILE_BUFFER_TYPE}
  MSV1_0_PROFILE_BUFFER_TYPE = _MSV1_0_PROFILE_BUFFER_TYPE;
  {$EXTERNALSYM MSV1_0_PROFILE_BUFFER_TYPE}
  PMSV1_0_PROFILE_BUFFER_TYPE = ^MSV1_0_PROFILE_BUFFER_TYPE;
  {$EXTERNALSYM PMSV1_0_PROFILE_BUFFER_TYPE}
  TMsv1_0ProfileBufferType = MSV1_0_PROFILE_BUFFER_TYPE;
  PMsv1_0ProfileBufferType = PMSV1_0_PROFILE_BUFFER_TYPE;  

//
// MsV1_0InteractiveLogon
//
// The AuthenticationInformation buffer of an LsaLogonUser() call to
// perform an interactive logon contains the following data structure:
//

  PMSV1_0_INTERACTIVE_LOGON = ^MSV1_0_INTERACTIVE_LOGON;
  {$EXTERNALSYM PMSV1_0_INTERACTIVE_LOGON}
  _MSV1_0_INTERACTIVE_LOGON = record
    MessageType: MSV1_0_LOGON_SUBMIT_TYPE;
    LogonDomainName: UNICODE_STRING;
    UserName: UNICODE_STRING;
    Password: UNICODE_STRING;
  end;
  {$EXTERNALSYM _MSV1_0_INTERACTIVE_LOGON}
  MSV1_0_INTERACTIVE_LOGON = _MSV1_0_INTERACTIVE_LOGON;
  {$EXTERNALSYM MSV1_0_INTERACTIVE_LOGON}
  TMsv10InteractiveLogon = MSV1_0_INTERACTIVE_LOGON;
  PMsv10InteractiveLogon = PMSV1_0_INTERACTIVE_LOGON;

//
// Where:
//
//     MessageType - Contains the type of logon being requested.  This
//         field must be set to MsV1_0InteractiveLogon.
//
//     UserName - Is a string representing the user's account name.  The
//         name may be up to 255 characters long.  The name is treated case
//         insensitive.
//
//     Password - Is a string containing the user's cleartext password.
//         The password may be up to 255 characters long and contain any
//         UNICODE value.
//
//


//
// The ProfileBuffer returned upon a successful logon of this type
// contains the following data structure:
//

  PMSV1_0_INTERACTIVE_PROFILE = ^MSV1_0_INTERACTIVE_PROFILE;
  {$EXTERNALSYM PMSV1_0_INTERACTIVE_PROFILE}
  _MSV1_0_INTERACTIVE_PROFILE = record
    MessageType: MSV1_0_PROFILE_BUFFER_TYPE;
    LogonCount: USHORT;
    BadPasswordCount: USHORT;
    LogonTime: LARGE_INTEGER;
    LogoffTime: LARGE_INTEGER;
    KickOffTime: LARGE_INTEGER;
    PasswordLastSet: LARGE_INTEGER;
    PasswordCanChange: LARGE_INTEGER;
    PasswordMustChange: LARGE_INTEGER;
    LogonScript: UNICODE_STRING;
    HomeDirectory: UNICODE_STRING;
    FullName: UNICODE_STRING;
    ProfilePath: UNICODE_STRING;
    HomeDirectoryDrive: UNICODE_STRING;
    LogonServer: UNICODE_STRING;
    UserFlags: ULONG;
  end;
  {$EXTERNALSYM _MSV1_0_INTERACTIVE_PROFILE}
  MSV1_0_INTERACTIVE_PROFILE = _MSV1_0_INTERACTIVE_PROFILE;
  {$EXTERNALSYM MSV1_0_INTERACTIVE_PROFILE}
  TMsv10InteractiveProfile = MSV1_0_INTERACTIVE_PROFILE;
  PMsv10InteractiveProfile = PMSV1_0_INTERACTIVE_PROFILE;

//
// where:
//
//     MessageType - Identifies the type of profile data being returned.
//         Contains the type of logon being requested.  This field must
//         be set to MsV1_0InteractiveProfile.
//
//     LogonCount - Number of times the user is currently logged on.
//
//     BadPasswordCount - Number of times a bad password was applied to
//         the account since last successful logon.
//
//     LogonTime - Time when user last logged on.  This is an absolute
//         format NT standard time value.
//
//     LogoffTime - Time when user should log off.  This is an absolute
//         format NT standard time value.
//
//     KickOffTime - Time when system should force user logoff.  This is
//         an absolute format NT standard time value.
//
//     PasswordLastChanged - Time and date the password was last
//         changed.  This is an absolute format NT standard time
//         value.
//
//     PasswordCanChange - Time and date when the user can change the
//         password.  This is an absolute format NT time value.  To
//         prevent a password from ever changing, set this field to a
//         date very far into the future.
//
//     PasswordMustChange - Time and date when the user must change the
//         password.  If the user can never change the password, this
//         field is undefined.  This is an absolute format NT time
//         value.
//
//     LogonScript - The (relative) path to the account's logon
//         script.
//
//     HomeDirectory - The home directory for the user.
//


//
// MsV1_0Lm20Logon and MsV1_0NetworkLogon
//
// The AuthenticationInformation buffer of an LsaLogonUser() call to
// perform an network logon contains the following data structure:
//
// MsV1_0NetworkLogon logon differs from MsV1_0Lm20Logon in that the
// ParameterControl field exists.
//

const
  MSV1_0_CHALLENGE_LENGTH          = 8;
  {$EXTERNALSYM MSV1_0_CHALLENGE_LENGTH}
  MSV1_0_USER_SESSION_KEY_LENGTH   = 16;
  {$EXTERNALSYM MSV1_0_USER_SESSION_KEY_LENGTH}
  MSV1_0_LANMAN_SESSION_KEY_LENGTH = 8;
  {$EXTERNALSYM MSV1_0_LANMAN_SESSION_KEY_LENGTH}

//
// Values for ParameterControl.
//

  MSV1_0_CLEARTEXT_PASSWORD_ALLOWED = $02;
  {$EXTERNALSYM MSV1_0_CLEARTEXT_PASSWORD_ALLOWED}
  MSV1_0_UPDATE_LOGON_STATISTICS    = $04;
  {$EXTERNALSYM MSV1_0_UPDATE_LOGON_STATISTICS}
  MSV1_0_RETURN_USER_PARAMETERS     = $08;
  {$EXTERNALSYM MSV1_0_RETURN_USER_PARAMETERS}
  MSV1_0_DONT_TRY_GUEST_ACCOUNT     = $10;
  {$EXTERNALSYM MSV1_0_DONT_TRY_GUEST_ACCOUNT}
  MSV1_0_ALLOW_SERVER_TRUST_ACCOUNT = $20;
  {$EXTERNALSYM MSV1_0_ALLOW_SERVER_TRUST_ACCOUNT}
  MSV1_0_RETURN_PASSWORD_EXPIRY     = $40;
  {$EXTERNALSYM MSV1_0_RETURN_PASSWORD_EXPIRY}

// this next flag says that CaseInsensitiveChallengeResponse
//  (aka LmResponse) contains a client challenge in the first 8 bytes

  MSV1_0_USE_CLIENT_CHALLENGE            = $80;
  {$EXTERNALSYM MSV1_0_USE_CLIENT_CHALLENGE}
  MSV1_0_TRY_GUEST_ACCOUNT_ONLY          = $100;
  {$EXTERNALSYM MSV1_0_TRY_GUEST_ACCOUNT_ONLY}
  MSV1_0_RETURN_PROFILE_PATH             = $200;
  {$EXTERNALSYM MSV1_0_RETURN_PROFILE_PATH}
  MSV1_0_TRY_SPECIFIED_DOMAIN_ONLY       = $400;
  {$EXTERNALSYM MSV1_0_TRY_SPECIFIED_DOMAIN_ONLY}
  MSV1_0_ALLOW_WORKSTATION_TRUST_ACCOUNT = $800;
  {$EXTERNALSYM MSV1_0_ALLOW_WORKSTATION_TRUST_ACCOUNT}
  MSV1_0_DISABLE_PERSONAL_FALLBACK       = $00001000;
  {$EXTERNALSYM MSV1_0_DISABLE_PERSONAL_FALLBACK}
  MSV1_0_ALLOW_FORCE_GUEST	         = $00002000;
  {$EXTERNALSYM MSV1_0_ALLOW_FORCE_GUEST}
  MSV1_0_CLEARTEXT_PASSWORD_SUPPLIED     = $00004000;
  {$EXTERNALSYM MSV1_0_CLEARTEXT_PASSWORD_SUPPLIED}
  MSV1_0_USE_DOMAIN_FOR_ROUTING_ONLY     = $00008000;
  {$EXTERNALSYM MSV1_0_USE_DOMAIN_FOR_ROUTING_ONLY}
  MSV1_0_SUBAUTHENTICATION_DLL_EX        = $00100000;
  {$EXTERNALSYM MSV1_0_SUBAUTHENTICATION_DLL_EX}

//
// The high order byte is a value indicating the SubAuthentication DLL.
//  Zero indicates no SubAuthentication DLL.
//

  MSV1_0_SUBAUTHENTICATION_DLL       = DWORD($FF000000);
  {$EXTERNALSYM MSV1_0_SUBAUTHENTICATION_DLL}
  MSV1_0_SUBAUTHENTICATION_DLL_SHIFT = 24;
  {$EXTERNALSYM MSV1_0_SUBAUTHENTICATION_DLL_SHIFT}
  MSV1_0_MNS_LOGON                   = $01000000;
  {$EXTERNALSYM MSV1_0_MNS_LOGON}

//
// This is the list of subauthentication dlls used in MS
//

  MSV1_0_SUBAUTHENTICATION_DLL_RAS = 2;
  {$EXTERNALSYM MSV1_0_SUBAUTHENTICATION_DLL_RAS}
  MSV1_0_SUBAUTHENTICATION_DLL_IIS = 132;
  {$EXTERNALSYM MSV1_0_SUBAUTHENTICATION_DLL_IIS}

type
  PMSV1_0_LM20_LOGON = ^MSV1_0_LM20_LOGON;
  {$EXTERNALSYM PMSV1_0_LM20_LOGON}
  _MSV1_0_LM20_LOGON = record
    MessageType: MSV1_0_LOGON_SUBMIT_TYPE;
    LogonDomainName: UNICODE_STRING;
    UserName: UNICODE_STRING;
    Workstation: UNICODE_STRING;
    ChallengeToClient: array [0..MSV1_0_CHALLENGE_LENGTH - 1] of UCHAR;
    CaseSensitiveChallengeResponse: STRING;
    CaseInsensitiveChallengeResponse: STRING;
    ParameterControl: ULONG;
  end;
  {$EXTERNALSYM _MSV1_0_LM20_LOGON}
  MSV1_0_LM20_LOGON = _MSV1_0_LM20_LOGON;
  {$EXTERNALSYM MSV1_0_LM20_LOGON}
  TMsv10Lm20Logon = MSV1_0_LM20_LOGON;
  PMsv10Lm20Logon = PMSV1_0_LM20_LOGON;

//
// NT 5.0 SubAuth dlls can use this struct
//

  PMSV1_0_SUBAUTH_LOGON = ^MSV1_0_SUBAUTH_LOGON;
  {$EXTERNALSYM PMSV1_0_SUBAUTH_LOGON}
  _MSV1_0_SUBAUTH_LOGON = record
    MessageType: MSV1_0_LOGON_SUBMIT_TYPE;
    LogonDomainName: UNICODE_STRING;
    UserName: UNICODE_STRING;
    Workstation: UNICODE_STRING;
    ChallengeToClient: array [0..MSV1_0_CHALLENGE_LENGTH - 1] of UCHAR;
    AuthenticationInfo1: STRING;
    AuthenticationInfo2: STRING;
    ParameterControl: ULONG;
    SubAuthPackageId: ULONG;
  end;
  {$EXTERNALSYM _MSV1_0_SUBAUTH_LOGON}
  MSV1_0_SUBAUTH_LOGON = _MSV1_0_SUBAUTH_LOGON;
  {$EXTERNALSYM MSV1_0_SUBAUTH_LOGON}
  TMsv10SubauthLogon = MSV1_0_SUBAUTH_LOGON;
  PMsv10SubauthLogon = PMSV1_0_SUBAUTH_LOGON;

//
// Values for UserFlags.
//

const
  LOGON_GUEST                 = $01;
  {$EXTERNALSYM LOGON_GUEST}
  LOGON_NOENCRYPTION          = $02;
  {$EXTERNALSYM LOGON_NOENCRYPTION}
  LOGON_CACHED_ACCOUNT        = $04;
  {$EXTERNALSYM LOGON_CACHED_ACCOUNT}
  LOGON_USED_LM_PASSWORD      = $08;
  {$EXTERNALSYM LOGON_USED_LM_PASSWORD}
  LOGON_EXTRA_SIDS            = $20;
  {$EXTERNALSYM LOGON_EXTRA_SIDS}
  LOGON_SUBAUTH_SESSION_KEY   = $40;
  {$EXTERNALSYM LOGON_SUBAUTH_SESSION_KEY}
  LOGON_SERVER_TRUST_ACCOUNT  = $80;
  {$EXTERNALSYM LOGON_SERVER_TRUST_ACCOUNT}
  LOGON_NTLMV2_ENABLED        = $100; // says DC understands NTLMv2
  {$EXTERNALSYM LOGON_NTLMV2_ENABLED}
  LOGON_RESOURCE_GROUPS       = $200;
  {$EXTERNALSYM LOGON_RESOURCE_GROUPS}
  LOGON_PROFILE_PATH_RETURNED = $400;
  {$EXTERNALSYM LOGON_PROFILE_PATH_RETURNED}

//
// The high order byte is reserved for return by SubAuthentication DLLs.
//

  MSV1_0_SUBAUTHENTICATION_FLAGS = DWORD($FF000000);
  {$EXTERNALSYM MSV1_0_SUBAUTHENTICATION_FLAGS}

// Values returned by the MSV1_0_MNS_LOGON SubAuthentication DLL

  LOGON_GRACE_LOGON = $01000000;
  {$EXTERNALSYM LOGON_GRACE_LOGON}

type
  PMSV1_0_LM20_LOGON_PROFILE = ^MSV1_0_LM20_LOGON_PROFILE;
  {$EXTERNALSYM PMSV1_0_LM20_LOGON_PROFILE}
  _MSV1_0_LM20_LOGON_PROFILE = record
    MessageType: MSV1_0_PROFILE_BUFFER_TYPE;
    KickOffTime: LARGE_INTEGER;
    LogoffTime: LARGE_INTEGER;
    UserFlags: ULONG;
    UserSessionKey: array [0..MSV1_0_USER_SESSION_KEY_LENGTH - 1] of UCHAR;
    LogonDomainName: UNICODE_STRING;
    LanmanSessionKey: array [0..MSV1_0_LANMAN_SESSION_KEY_LENGTH - 1] of UCHAR;
    LogonServer: UNICODE_STRING;
    UserParameters: UNICODE_STRING;
  end;
  {$EXTERNALSYM _MSV1_0_LM20_LOGON_PROFILE}
  MSV1_0_LM20_LOGON_PROFILE = _MSV1_0_LM20_LOGON_PROFILE;
  {$EXTERNALSYM MSV1_0_LM20_LOGON_PROFILE}
  TMsv10Lm20LogonProfile = MSV1_0_LM20_LOGON_PROFILE;
  PMsv10Lm20LogonProfile = PMSV1_0_LM20_LOGON_PROFILE;

//
// Supplemental credentials structure used for passing credentials into
// MSV1_0 from other packages
//

const
  MSV1_0_OWF_PASSWORD_LENGTH = 16;
  {$EXTERNALSYM MSV1_0_OWF_PASSWORD_LENGTH}
  MSV1_0_CRED_LM_PRESENT     = $1;
  {$EXTERNALSYM MSV1_0_CRED_LM_PRESENT}
  MSV1_0_CRED_NT_PRESENT     = $2;
  {$EXTERNALSYM MSV1_0_CRED_NT_PRESENT}
  MSV1_0_CRED_VERSION        = 0;
  {$EXTERNALSYM MSV1_0_CRED_VERSION}

type
  PMSV1_0_SUPPLEMENTAL_CREDENTIAL = ^MSV1_0_SUPPLEMENTAL_CREDENTIAL;
  {$EXTERNALSYM PMSV1_0_SUPPLEMENTAL_CREDENTIAL}
  _MSV1_0_SUPPLEMENTAL_CREDENTIAL = record
    Version: ULONG;
    Flags: ULONG;
    LmPassword: array [0..MSV1_0_OWF_PASSWORD_LENGTH - 1] of UCHAR;
    NtPassword: array [0..MSV1_0_OWF_PASSWORD_LENGTH - 1] of UCHAR;
  end;
  {$EXTERNALSYM _MSV1_0_SUPPLEMENTAL_CREDENTIAL}
  MSV1_0_SUPPLEMENTAL_CREDENTIAL = _MSV1_0_SUPPLEMENTAL_CREDENTIAL;
  {$EXTERNALSYM MSV1_0_SUPPLEMENTAL_CREDENTIAL}
  TMsv10SupplementalCredential = MSV1_0_SUPPLEMENTAL_CREDENTIAL;
  PMsv10SupplementalCredential = PMSV1_0_SUPPLEMENTAL_CREDENTIAL;

//
// NTLM3 definitions.
//

const
  MSV1_0_NTLM3_RESPONSE_LENGTH = 16;
  {$EXTERNALSYM MSV1_0_NTLM3_RESPONSE_LENGTH}
  MSV1_0_NTLM3_OWF_LENGTH      = 16;
  {$EXTERNALSYM MSV1_0_NTLM3_OWF_LENGTH}

//
// this is the longest amount of time we'll allow challenge response
// pairs to be used. Note that this also has to allow for worst case clock skew
//

  MSV1_0_MAX_NTLM3_LIFE = 129600;     // 36 hours (in seconds)
  {$EXTERNALSYM MSV1_0_MAX_NTLM3_LIFE}
  MSV1_0_MAX_AVL_SIZE   = 64000;
  {$EXTERNALSYM MSV1_0_MAX_AVL_SIZE}

//
// MsvAvFlags bit values
//

  MSV1_0_AV_FLAG_FORCE_GUEST = $00000001;
  {$EXTERNALSYM MSV1_0_AV_FLAG_FORCE_GUEST}

// this is an MSV1_0 private data structure, defining the layout of an NTLM3 response, as sent by a
//  client in the NtChallengeResponse field of the NETLOGON_NETWORK_INFO structure. If can be differentiated
//  from an old style NT response by its length. This is crude, but it needs to pass through servers and
//  the servers' DCs that do not understand NTLM3 but that are willing to pass longer responses.

type
  PMSV1_0_NTLM3_RESPONSE = ^MSV1_0_NTLM3_RESPONSE;
  {$EXTERNALSYM PMSV1_0_NTLM3_RESPONSE}
  _MSV1_0_NTLM3_RESPONSE = record
    Response: array [0..MSV1_0_NTLM3_RESPONSE_LENGTH - 1] of UCHAR; // hash of OWF of password with all the following fields
    RespType: UCHAR; // id number of response; current is 1
    HiRespType: UCHAR; // highest id number understood by client
    Flags: USHORT; // reserved; must be sent as zero at this version
    MsgWord: ULONG; // 32 bit message from client to server (for use by auth protocol)
    TimeStamp: ULONGLONG; // time stamp when client generated response -- NT system time, quad part
    ChallengeFromClient: array [0..MSV1_0_CHALLENGE_LENGTH - 1] of UCHAR;
    AvPairsOff: ULONG; // offset to start of AvPairs (to allow future expansion)
    Buffer: array [0..0] of UCHAR; // start of buffer with AV pairs (or future stuff -- so use the offset)
  end;
  {$EXTERNALSYM _MSV1_0_NTLM3_RESPONSE}
  MSV1_0_NTLM3_RESPONSE = _MSV1_0_NTLM3_RESPONSE;
  {$EXTERNALSYM MSV1_0_NTLM3_RESPONSE}
  TMsv10Ntlm3Response = MSV1_0_NTLM3_RESPONSE;
  PMsv10Ntlm3Response = PMSV1_0_NTLM3_RESPONSE;

const
  MSV1_0_NTLM3_INPUT_LENGTH = (SizeOf(MSV1_0_NTLM3_RESPONSE) - MSV1_0_NTLM3_RESPONSE_LENGTH);
  {$EXTERNALSYM MSV1_0_NTLM3_INPUT_LENGTH}
  //todo MSV1_0_NTLM3_MIN_NT_RESPONSE_LENGTH = RTL_SIZEOF_THROUGH_FIELD(MSV1_0_NTLM3_RESPONSE, AvPairsOff)
  //{$EXTERNALSYM MSV1_0_NTLM3_MIN_NT_RESPONSE_LENGTH}

type
  MSV1_0_AVID = (
    MsvAvEOL,                 // end of list
    MsvAvNbComputerName,      // server's computer name -- NetBIOS
    MsvAvNbDomainName,        // server's domain name -- NetBIOS
    MsvAvDnsComputerName,     // server's computer name -- DNS
    MsvAvDnsDomainName,       // server's domain name -- DNS
    MsvAvDnsTreeName,         // server's tree name -- DNS
    MsvAvFlags);              // server's extended flags -- DWORD mask
  {$EXTERNALSYM MSV1_0_AVID}

  PMSV1_0_AV_PAIR = ^MSV1_0_AV_PAIR;
  {$EXTERNALSYM PMSV1_0_AV_PAIR}
  _MSV1_0_AV_PAIR = record
    AvId: USHORT;
    AvLen: USHORT;
    // Data is treated as byte array following structure
  end;
  {$EXTERNALSYM _MSV1_0_AV_PAIR}
  MSV1_0_AV_PAIR = _MSV1_0_AV_PAIR;
  {$EXTERNALSYM MSV1_0_AV_PAIR}
  TMsv10AvPair = MSV1_0_AV_PAIR;
  PMsv10AvPair = PMSV1_0_AV_PAIR;

///////////////////////////////////////////////////////////////////////////////
//                                                                           //
//       CALL PACKAGE Related Data Structures                                //
//                                                                           //
///////////////////////////////////////////////////////////////////////////////


//
//  MSV1.0 LsaCallAuthenticationPackage() submission and response
//  message types.
//

  _MSV1_0_PROTOCOL_MESSAGE_TYPE = (
    MsV1_0Lm20ChallengeRequest,              // Both submission and response
    MsV1_0Lm20GetChallengeResponse,          // Both submission and response
    MsV1_0EnumerateUsers,                    // Both submission and response
    MsV1_0GetUserInfo,                       // Both submission and response
    MsV1_0ReLogonUsers,                      // Submission only
    MsV1_0ChangePassword,                    // Both submission and response
    MsV1_0ChangeCachedPassword,              // Both submission and response
    MsV1_0GenericPassthrough,                // Both submission and response
    MsV1_0CacheLogon,                        // Submission only, no response
    MsV1_0SubAuth,                           // Both submission and response
    MsV1_0DeriveCredential,                  // Both submission and response
    MsV1_0CacheLookup,                       // Both submission and response
    MsV1_0SetProcessOption);                 // Submission only, no response
  {$EXTERNALSYM _MSV1_0_PROTOCOL_MESSAGE_TYPE}
  MSV1_0_PROTOCOL_MESSAGE_TYPE = _MSV1_0_PROTOCOL_MESSAGE_TYPE;
  {$EXTERNALSYM MSV1_0_PROTOCOL_MESSAGE_TYPE}
  PMSV1_0_PROTOCOL_MESSAGE_TYPE = ^MSV1_0_PROTOCOL_MESSAGE_TYPE;
  {$EXTERNALSYM PMSV1_0_PROTOCOL_MESSAGE_TYPE}
  TMsv1_0ProtocolMessageType = MSV1_0_PROTOCOL_MESSAGE_TYPE;
  PMsv1_0ProtocolMessageType = PMSV1_0_PROTOCOL_MESSAGE_TYPE;

  PMSV1_0_CHANGEPASSWORD_REQUEST = ^MSV1_0_CHANGEPASSWORD_REQUEST;
  {$EXTERNALSYM PMSV1_0_CHANGEPASSWORD_REQUEST}
  _MSV1_0_CHANGEPASSWORD_REQUEST = record
    MessageType: MSV1_0_PROTOCOL_MESSAGE_TYPE;
    DomainName: UNICODE_STRING;
    AccountName: UNICODE_STRING;
    OldPassword: UNICODE_STRING;
    NewPassword: UNICODE_STRING;
    Impersonating: ByteBool;
  end;
  {$EXTERNALSYM _MSV1_0_CHANGEPASSWORD_REQUEST}
  MSV1_0_CHANGEPASSWORD_REQUEST = _MSV1_0_CHANGEPASSWORD_REQUEST;
  {$EXTERNALSYM MSV1_0_CHANGEPASSWORD_REQUEST}
  TMsv10ChangepasswordRequest = MSV1_0_CHANGEPASSWORD_REQUEST;
  PMsv10ChangepasswordRequest = PMSV1_0_CHANGEPASSWORD_REQUEST;

  PMSV1_0_CHANGEPASSWORD_RESPONSE = ^MSV1_0_CHANGEPASSWORD_RESPONSE;
  {$EXTERNALSYM PMSV1_0_CHANGEPASSWORD_RESPONSE}
  _MSV1_0_CHANGEPASSWORD_RESPONSE = record
    MessageType: MSV1_0_PROTOCOL_MESSAGE_TYPE;
    PasswordInfoValid: ByteBool;
    DomainPasswordInfo: DOMAIN_PASSWORD_INFORMATION;
  end;
  {$EXTERNALSYM _MSV1_0_CHANGEPASSWORD_RESPONSE}
  MSV1_0_CHANGEPASSWORD_RESPONSE = _MSV1_0_CHANGEPASSWORD_RESPONSE;
  {$EXTERNALSYM MSV1_0_CHANGEPASSWORD_RESPONSE}
  TMsv10ChangepasswordResponse = MSV1_0_CHANGEPASSWORD_RESPONSE;
  PMsv10ChangepasswordResponse = PMSV1_0_CHANGEPASSWORD_RESPONSE;

//
// MsV1_0GenericPassthrough - for remoting a CallPackage to
// a domain controller on the specified domain
//

  _MSV1_0_PASSTHROUGH_REQUEST = record
    MessageType: MSV1_0_PROTOCOL_MESSAGE_TYPE;
    DomainName: UNICODE_STRING;
    PackageName: UNICODE_STRING;
    DataLength: ULONG;
    LogonData: PUCHAR;
    Pad: ULONG;
  end;
  {$EXTERNALSYM _MSV1_0_PASSTHROUGH_REQUEST}
  MSV1_0_PASSTHROUGH_REQUEST = _MSV1_0_PASSTHROUGH_REQUEST;
  {$EXTERNALSYM MSV1_0_PASSTHROUGH_REQUEST}
  PMSV1_0_PASSTHROUGH_REQUEST = ^MSV1_0_PASSTHROUGH_REQUEST;
  {$EXTERNALSYM PMSV1_0_PASSTHROUGH_REQUEST}
  TMsv10PassThroughRequest = MSV1_0_PASSTHROUGH_REQUEST;
  PMsv10PassThroughRequest = PMSV1_0_PASSTHROUGH_REQUEST;  

  _MSV1_0_PASSTHROUGH_RESPONSE = record
    MessageType: MSV1_0_PROTOCOL_MESSAGE_TYPE;
    Pad: ULONG;
    DataLength: ULONG;
    ValidationData: PUCHAR;
  end;
  {$EXTERNALSYM _MSV1_0_PASSTHROUGH_RESPONSE}
  MSV1_0_PASSTHROUGH_RESPONSE = _MSV1_0_PASSTHROUGH_RESPONSE;
  {$EXTERNALSYM MSV1_0_PASSTHROUGH_RESPONSE}
  PMSV1_0_PASSTHROUGH_RESPONSE = ^MSV1_0_PASSTHROUGH_RESPONSE;
  {$EXTERNALSYM PMSV1_0_PASSTHROUGH_RESPONSE}
  TMsv10PassThroughResponse = MSV1_0_PASSTHROUGH_RESPONSE;
  PMsv10PassThroughResponse = PMSV1_0_PASSTHROUGH_RESPONSE;

//
// MsV1_0SubAuthInfo submit buffer and response - for submitting a buffer to a
// specified Subauthentication Package during an LsaCallAuthenticationPackage().
// If this Subauthentication is to be done locally, then package this message
// in LsaCallAuthenticationPackage(). If this SubAuthentication needs to be done
// on the domain controller, then call LsaCallauthenticationPackage with the
// message type being MsV1_0GenericPassThrough and the LogonData in this struct
// should be a PMSV1_0_SUBAUTH_REQUEST
//

  PMSV1_0_SUBAUTH_REQUEST = ^MSV1_0_SUBAUTH_REQUEST;
  {$EXTERNALSYM PMSV1_0_SUBAUTH_REQUEST}
  _MSV1_0_SUBAUTH_REQUEST = record
    MessageType: MSV1_0_PROTOCOL_MESSAGE_TYPE;
    SubAuthPackageId: ULONG;
    SubAuthInfoLength: ULONG;
    SubAuthSubmitBuffer: PUCHAR;
  end;
  {$EXTERNALSYM _MSV1_0_SUBAUTH_REQUEST}
  MSV1_0_SUBAUTH_REQUEST = _MSV1_0_SUBAUTH_REQUEST;
  {$EXTERNALSYM MSV1_0_SUBAUTH_REQUEST}
  TMsv10SubauthRequest = MSV1_0_SUBAUTH_REQUEST;
  PMsv10SubauthRequest = PMSV1_0_SUBAUTH_REQUEST;

  PMSV1_0_SUBAUTH_RESPONSE = ^MSV1_0_SUBAUTH_RESPONSE;
  {$EXTERNALSYM PMSV1_0_SUBAUTH_RESPONSE}
  _MSV1_0_SUBAUTH_RESPONSE = record
    MessageType: MSV1_0_PROTOCOL_MESSAGE_TYPE;
    SubAuthInfoLength: ULONG;
    SubAuthReturnBuffer: PUCHAR;
  end;
  {$EXTERNALSYM _MSV1_0_SUBAUTH_RESPONSE}
  MSV1_0_SUBAUTH_RESPONSE = _MSV1_0_SUBAUTH_RESPONSE;
  {$EXTERNALSYM MSV1_0_SUBAUTH_RESPONSE}
  TMsv10SubauthResponse = MSV1_0_SUBAUTH_RESPONSE;
  PMsv10SubauthResponse = PMSV1_0_SUBAUTH_RESPONSE;

//
// Credential Derivation types for MsV1_0DeriveCredential Submit DeriveCredType
//

//
// Derive Credential using SHA-1 and Request buffer DeriveCredSubmitBuffer of
// length DeriveCredInfoLength mixing bytes.
// Response buffer DeriveCredReturnBuffer will contain SHA-1 hash of size
// A_SHA_DIGEST_LEN (20)
//

const
  MSV1_0_DERIVECRED_TYPE_SHA1 = 0;
  {$EXTERNALSYM MSV1_0_DERIVECRED_TYPE_SHA1}

//
// MsV1_0DeriveCredential submit buffer and response - for submitting a buffer
// an call to LsaCallAuthenticationPackage().
//

type
  PMSV1_0_DERIVECRED_REQUEST = ^MSV1_0_DERIVECRED_REQUEST;
  {$EXTERNALSYM PMSV1_0_DERIVECRED_REQUEST}
  _MSV1_0_DERIVECRED_REQUEST = record
    MessageType: MSV1_0_PROTOCOL_MESSAGE_TYPE;
    LogonId: LUID;
    DeriveCredType: ULONG;
    DeriveCredInfoLength: ULONG;
    DeriveCredSubmitBuffer: array [0..0] of UCHAR; // in-place array of length DeriveCredInfoLength
  end;
  {$EXTERNALSYM _MSV1_0_DERIVECRED_REQUEST}
  MSV1_0_DERIVECRED_REQUEST = _MSV1_0_DERIVECRED_REQUEST;
  {$EXTERNALSYM MSV1_0_DERIVECRED_REQUEST}
  TMsv10DeriveCredRequest = MSV1_0_DERIVECRED_REQUEST;
  PMsv10DeriveCredRequest = PMSV1_0_DERIVECRED_REQUEST;

  PMSV1_0_DERIVECRED_RESPONSE = ^MSV1_0_DERIVECRED_RESPONSE;
  {$EXTERNALSYM PMSV1_0_DERIVECRED_RESPONSE}
  _MSV1_0_DERIVECRED_RESPONSE = record
    MessageType: MSV1_0_PROTOCOL_MESSAGE_TYPE;
    DeriveCredInfoLength: ULONG;
    DeriveCredReturnBuffer: array [0..0] of UCHAR; // in-place array of length DeriveCredInfoLength
  end;
  {$EXTERNALSYM _MSV1_0_DERIVECRED_RESPONSE}
  MSV1_0_DERIVECRED_RESPONSE = _MSV1_0_DERIVECRED_RESPONSE;
  {$EXTERNALSYM MSV1_0_DERIVECRED_RESPONSE}
  TMsv10DeriveCredResponse = MSV1_0_DERIVECRED_RESPONSE;
  PMsv10DeriveCredResponse = PMSV1_0_DERIVECRED_RESPONSE;

// Revision of the Kerberos Protocol.  MS uses Version 5, Revision 6

const
  KERBEROS_VERSION  = 5;
  {$EXTERNALSYM KERBEROS_VERSION}
  KERBEROS_REVISION = 6;
  {$EXTERNALSYM KERBEROS_REVISION}

// Encryption Types:
// These encryption types are supported by the default MS KERBSUPP DLL
// as crypto systems.  Values over 127 are local values, and may be changed
// without notice.

  KERB_ETYPE_NULL        = 0;
  {$EXTERNALSYM KERB_ETYPE_NULL}
  KERB_ETYPE_DES_CBC_CRC = 1;
  {$EXTERNALSYM KERB_ETYPE_DES_CBC_CRC}
  KERB_ETYPE_DES_CBC_MD4 = 2;
  {$EXTERNALSYM KERB_ETYPE_DES_CBC_MD4}
  KERB_ETYPE_DES_CBC_MD5 = 3;
  {$EXTERNALSYM KERB_ETYPE_DES_CBC_MD5}

  KERB_ETYPE_RC4_MD4           = -128;
  {$EXTERNALSYM KERB_ETYPE_RC4_MD4}
  KERB_ETYPE_RC4_PLAIN2        = -129;
  {$EXTERNALSYM KERB_ETYPE_RC4_PLAIN2}
  KERB_ETYPE_RC4_LM            = -130;
  {$EXTERNALSYM KERB_ETYPE_RC4_LM}
  KERB_ETYPE_RC4_SHA           = -131;
  {$EXTERNALSYM KERB_ETYPE_RC4_SHA}
  KERB_ETYPE_DES_PLAIN         = -132;
  {$EXTERNALSYM KERB_ETYPE_DES_PLAIN}
  KERB_ETYPE_RC4_HMAC_OLD      = -133;
  {$EXTERNALSYM KERB_ETYPE_RC4_HMAC_OLD}
  KERB_ETYPE_RC4_PLAIN_OLD     = -134;
  {$EXTERNALSYM KERB_ETYPE_RC4_PLAIN_OLD}
  KERB_ETYPE_RC4_HMAC_OLD_EXP  = -135;
  {$EXTERNALSYM KERB_ETYPE_RC4_HMAC_OLD_EXP}
  KERB_ETYPE_RC4_PLAIN_OLD_EXP = -136;
  {$EXTERNALSYM KERB_ETYPE_RC4_PLAIN_OLD_EXP}
  KERB_ETYPE_RC4_PLAIN         = -140;
  {$EXTERNALSYM KERB_ETYPE_RC4_PLAIN}
  KERB_ETYPE_RC4_PLAIN_EXP     = -141;
  {$EXTERNALSYM KERB_ETYPE_RC4_PLAIN_EXP}

//
// Pkinit encryption types
//

  KERB_ETYPE_DSA_SHA1_CMS     = 9;
  {$EXTERNALSYM KERB_ETYPE_DSA_SHA1_CMS}
  KERB_ETYPE_RSA_MD5_CMS      = 10;
  {$EXTERNALSYM KERB_ETYPE_RSA_MD5_CMS}
  KERB_ETYPE_RSA_SHA1_CMS     = 11;
  {$EXTERNALSYM KERB_ETYPE_RSA_SHA1_CMS}
  KERB_ETYPE_RC2_CBC_ENV      = 12;
  {$EXTERNALSYM KERB_ETYPE_RC2_CBC_ENV}
  KERB_ETYPE_RSA_ENV          = 13;
  {$EXTERNALSYM KERB_ETYPE_RSA_ENV}
  KERB_ETYPE_RSA_ES_OEAP_ENV  = 14;
  {$EXTERNALSYM KERB_ETYPE_RSA_ES_OEAP_ENV}
  KERB_ETYPE_DES_EDE3_CBC_ENV = 15;
  {$EXTERNALSYM KERB_ETYPE_DES_EDE3_CBC_ENV}

//
// Deprecated
//

  KERB_ETYPE_DSA_SIGN     = 8;
  {$EXTERNALSYM KERB_ETYPE_DSA_SIGN}
  KERB_ETYPE_RSA_PRIV     = 9;
  {$EXTERNALSYM KERB_ETYPE_RSA_PRIV}
  KERB_ETYPE_RSA_PUB      = 10;
  {$EXTERNALSYM KERB_ETYPE_RSA_PUB}
  KERB_ETYPE_RSA_PUB_MD5  = 11;
  {$EXTERNALSYM KERB_ETYPE_RSA_PUB_MD5}
  KERB_ETYPE_RSA_PUB_SHA1 = 12;
  {$EXTERNALSYM KERB_ETYPE_RSA_PUB_SHA1}
  KERB_ETYPE_PKCS7_PUB    = 13;
  {$EXTERNALSYM KERB_ETYPE_PKCS7_PUB}

//
// Unsupported but defined types
//

  KERB_ETYPE_DES3_CBC_MD5       = 5;
  {$EXTERNALSYM KERB_ETYPE_DES3_CBC_MD5}
  KERB_ETYPE_DES3_CBC_SHA1      = 7;
  {$EXTERNALSYM KERB_ETYPE_DES3_CBC_SHA1}
  KERB_ETYPE_DES3_CBC_SHA1_KD   = 16;
  {$EXTERNALSYM KERB_ETYPE_DES3_CBC_SHA1_KD}

//
// In use types
//

  KERB_ETYPE_DES_CBC_MD5_NT  = 20;
  {$EXTERNALSYM KERB_ETYPE_DES_CBC_MD5_NT}
  KERB_ETYPE_RC4_HMAC_NT     = 23;
  {$EXTERNALSYM KERB_ETYPE_RC4_HMAC_NT}
  KERB_ETYPE_RC4_HMAC_NT_EXP = 24;
  {$EXTERNALSYM KERB_ETYPE_RC4_HMAC_NT_EXP}

// Checksum algorithms.
// These algorithms are keyed internally for our use.

  KERB_CHECKSUM_NONE        = 0;
  {$EXTERNALSYM KERB_CHECKSUM_NONE}
  KERB_CHECKSUM_CRC32       = 1;
  {$EXTERNALSYM KERB_CHECKSUM_CRC32}
  KERB_CHECKSUM_MD4         = 2;
  {$EXTERNALSYM KERB_CHECKSUM_MD4}
  KERB_CHECKSUM_KRB_DES_MAC = 4;
  {$EXTERNALSYM KERB_CHECKSUM_KRB_DES_MAC}
  KERB_CHECKSUM_KRB_DES_MAC_K = 5;
  {$EXTERNALSYM KERB_CHECKSUM_KRB_DES_MAC_K}  
  KERB_CHECKSUM_MD5         = 7;
  {$EXTERNALSYM KERB_CHECKSUM_MD5}
  KERB_CHECKSUM_MD5_DES     = 8;
  {$EXTERNALSYM KERB_CHECKSUM_MD5_DES}

  KERB_CHECKSUM_LM          = -130;
  {$EXTERNALSYM KERB_CHECKSUM_LM}
  KERB_CHECKSUM_SHA1        = -131;
  {$EXTERNALSYM KERB_CHECKSUM_SHA1}
  KERB_CHECKSUM_REAL_CRC32  = -132;
  {$EXTERNALSYM KERB_CHECKSUM_REAL_CRC32}
  KERB_CHECKSUM_DES_MAC     = -133;
  {$EXTERNALSYM KERB_CHECKSUM_DES_MAC}
  KERB_CHECKSUM_DES_MAC_MD5 = -134;
  {$EXTERNALSYM KERB_CHECKSUM_DES_MAC_MD5}
  KERB_CHECKSUM_MD25        = -135;
  {$EXTERNALSYM KERB_CHECKSUM_MD25}
  KERB_CHECKSUM_RC4_MD5     = -136;
  {$EXTERNALSYM KERB_CHECKSUM_RC4_MD5}
  KERB_CHECKSUM_MD5_HMAC    = -137; // used by netlogon
  {$EXTERNALSYM KERB_CHECKSUM_MD5_HMAC}
  KERB_CHECKSUM_HMAC_MD5    = -138; // used by Kerberos
  {$EXTERNALSYM KERB_CHECKSUM_HMAC_MD5}

  AUTH_REQ_ALLOW_FORWARDABLE     = $00000001;
  {$EXTERNALSYM AUTH_REQ_ALLOW_FORWARDABLE}
  AUTH_REQ_ALLOW_PROXIABLE       = $00000002;
  {$EXTERNALSYM AUTH_REQ_ALLOW_PROXIABLE}
  AUTH_REQ_ALLOW_POSTDATE        = $00000004;
  {$EXTERNALSYM AUTH_REQ_ALLOW_POSTDATE}
  AUTH_REQ_ALLOW_RENEWABLE       = $00000008;
  {$EXTERNALSYM AUTH_REQ_ALLOW_RENEWABLE}
  AUTH_REQ_ALLOW_NOADDRESS       = $00000010;
  {$EXTERNALSYM AUTH_REQ_ALLOW_NOADDRESS}
  AUTH_REQ_ALLOW_ENC_TKT_IN_SKEY = $00000020;
  {$EXTERNALSYM AUTH_REQ_ALLOW_ENC_TKT_IN_SKEY}
  AUTH_REQ_ALLOW_VALIDATE        = $00000040;
  {$EXTERNALSYM AUTH_REQ_ALLOW_VALIDATE}
  AUTH_REQ_VALIDATE_CLIENT       = $00000080;
  {$EXTERNALSYM AUTH_REQ_VALIDATE_CLIENT}
  AUTH_REQ_OK_AS_DELEGATE        = $00000100;
  {$EXTERNALSYM AUTH_REQ_OK_AS_DELEGATE}
  AUTH_REQ_PREAUTH_REQUIRED      = $00000200;
  {$EXTERNALSYM AUTH_REQ_PREAUTH_REQUIRED}
  AUTH_REQ_TRANSITIVE_TRUST      = $00000400;
  {$EXTERNALSYM AUTH_REQ_TRANSITIVE_TRUST}
  AUTH_REQ_ALLOW_S4U_DELEGATE    = $00000800;
  {$EXTERNALSYM AUTH_REQ_ALLOW_S4U_DELEGATE}

  AUTH_REQ_PER_USER_FLAGS        = (AUTH_REQ_ALLOW_FORWARDABLE or
                                    AUTH_REQ_ALLOW_PROXIABLE or
                                    AUTH_REQ_ALLOW_POSTDATE or
                                    AUTH_REQ_ALLOW_RENEWABLE or
                                    AUTH_REQ_ALLOW_VALIDATE);
  {$EXTERNALSYM AUTH_REQ_PER_USER_FLAGS}

//
// Ticket Flags:
//

  KERB_TICKET_FLAGS_reserved          = DWORD($80000000);
  {$EXTERNALSYM KERB_TICKET_FLAGS_reserved}
  KERB_TICKET_FLAGS_forwardable       = $40000000;
  {$EXTERNALSYM KERB_TICKET_FLAGS_forwardable}
  KERB_TICKET_FLAGS_forwarded         = $20000000;
  {$EXTERNALSYM KERB_TICKET_FLAGS_forwarded}
  KERB_TICKET_FLAGS_proxiable         = $10000000;
  {$EXTERNALSYM KERB_TICKET_FLAGS_proxiable}
  KERB_TICKET_FLAGS_proxy             = $08000000;
  {$EXTERNALSYM KERB_TICKET_FLAGS_proxy}
  KERB_TICKET_FLAGS_may_postdate      = $04000000;
  {$EXTERNALSYM KERB_TICKET_FLAGS_may_postdate}
  KERB_TICKET_FLAGS_postdated         = $02000000;
  {$EXTERNALSYM KERB_TICKET_FLAGS_postdated}
  KERB_TICKET_FLAGS_invalid           = $01000000;
  {$EXTERNALSYM KERB_TICKET_FLAGS_invalid}
  KERB_TICKET_FLAGS_renewable         = $00800000;
  {$EXTERNALSYM KERB_TICKET_FLAGS_renewable}
  KERB_TICKET_FLAGS_initial           = $00400000;
  {$EXTERNALSYM KERB_TICKET_FLAGS_initial}
  KERB_TICKET_FLAGS_pre_authent       = $00200000;
  {$EXTERNALSYM KERB_TICKET_FLAGS_pre_authent}
  KERB_TICKET_FLAGS_hw_authent        = $00100000;
  {$EXTERNALSYM KERB_TICKET_FLAGS_hw_authent}
  KERB_TICKET_FLAGS_ok_as_delegate    = $00040000;
  {$EXTERNALSYM KERB_TICKET_FLAGS_ok_as_delegate}
  KERB_TICKET_FLAGS_name_canonicalize = $00010000;
  {$EXTERNALSYM KERB_TICKET_FLAGS_name_canonicalize}
  KERB_TICKET_FLAGS_reserved1         = $00000001;
  {$EXTERNALSYM KERB_TICKET_FLAGS_reserved1}

//
// Name types
//

  KRB_NT_UNKNOWN              = 0; // Name type not known
  {$EXTERNALSYM KRB_NT_UNKNOWN}
  KRB_NT_PRINCIPAL            = 1; // Just the name of the principal as in DCE, or for users
  {$EXTERNALSYM KRB_NT_PRINCIPAL}
  KRB_NT_PRINCIPAL_AND_ID     = -131; // Name of the principal and its SID.
  {$EXTERNALSYM KRB_NT_PRINCIPAL_AND_ID}
  KRB_NT_SRV_INST             = 2; // Service and other unique instance (krbtgt)
  {$EXTERNALSYM KRB_NT_SRV_INST}
  KRB_NT_SRV_INST_AND_ID      = -132; // SPN and SID
  {$EXTERNALSYM KRB_NT_SRV_INST_AND_ID}
  KRB_NT_SRV_HST              = 3; // Service with host name as instance (telnet, rcommands)
  {$EXTERNALSYM KRB_NT_SRV_HST}
  KRB_NT_SRV_XHST             = 4; // Service with host as remaining components
  {$EXTERNALSYM KRB_NT_SRV_XHST}
  KRB_NT_UID                  = 5; // Unique ID
  {$EXTERNALSYM KRB_NT_UID}
  KRB_NT_ENTERPRISE_PRINCIPAL = 10; // UPN or SPN
  {$EXTERNALSYM KRB_NT_ENTERPRISE_PRINCIPAL}
  KRB_NT_ENT_PRINCIPAL_AND_ID = -130; // UPN and SID
  {$EXTERNALSYM KRB_NT_ENT_PRINCIPAL_AND_ID}

//
// MS extensions, negative according to the RFC
//

  KRB_NT_MS_PRINCIPAL = -128; // NT4 style name
  {$EXTERNALSYM KRB_NT_MS_PRINCIPAL}

  KRB_NT_MS_PRINCIPAL_AND_ID = -129; // nt4 style name with sid
  {$EXTERNALSYM KRB_NT_MS_PRINCIPAL_AND_ID}

// todo #define KERB_IS_MS_PRINCIPAL(_x_) (((_x_) <= KRB_NT_MS_PRINCIPAL) || ((_x_) >= KRB_NT_ENTERPRISE_PRINCIPAL))

  MICROSOFT_KERBEROS_NAME_A = 'Kerberos';
  {$EXTERNALSYM MICROSOFT_KERBEROS_NAME_A}
  MICROSOFT_KERBEROS_NAME_W = WideString('Kerberos');
  {$EXTERNALSYM MICROSOFT_KERBEROS_NAME_W}

{$IFDEF UNICODE}
  MICROSOFT_KERBEROS_NAME = MICROSOFT_KERBEROS_NAME_W;
  {$EXTERNALSYM MICROSOFT_KERBEROS_NAME}
{$ELSE}
  MICROSOFT_KERBEROS_NAME = MICROSOFT_KERBEROS_NAME_A;
  {$EXTERNALSYM MICROSOFT_KERBEROS_NAME}
{$ENDIF}


/////////////////////////////////////////////////////////////////////////
//
// Quality of protection parameters for MakeSignature / EncryptMessage
//
/////////////////////////////////////////////////////////////////////////

//
// This flag indicates to EncryptMessage that the message is not to actually
// be encrypted, but a header/trailer are to be produced.
//

  KERB_WRAP_NO_ENCRYPT = DWORD($80000001);
  {$EXTERNALSYM KERB_WRAP_NO_ENCRYPT}

/////////////////////////////////////////////////////////////////////////
//
// LsaLogonUser parameters
//
/////////////////////////////////////////////////////////////////////////

const
  KerbInteractiveLogon = 2;
  KerbSmartCardLogon = 6;
  KerbWorkstationUnlockLogon = 7;
  KerbSmartCardUnlockLogon = 8;
  KerbProxyLogon = 9;
  KerbTicketLogon = 10;
  KerbTicketUnlockLogon = 11;
  KerbS4ULogon = 12; 

type
  KERB_LOGON_SUBMIT_TYPE = DWORD;
  {$EXTERNALSYM KERB_LOGON_SUBMIT_TYPE}
  PKERB_LOGON_SUBMIT_TYPE = ^KERB_LOGON_SUBMIT_TYPE;
  {$EXTERNALSYM PKERB_LOGON_SUBMIT_TYPE}

  PKERB_INTERACTIVE_LOGON = ^KERB_INTERACTIVE_LOGON;
  {$EXTERNALSYM PKERB_INTERACTIVE_LOGON}
  _KERB_INTERACTIVE_LOGON = record
    MessageType: KERB_LOGON_SUBMIT_TYPE;
    LogonDomainName: UNICODE_STRING;
    UserName: UNICODE_STRING;
    Password: UNICODE_STRING;
  end;
  {$EXTERNALSYM _KERB_INTERACTIVE_LOGON}
  KERB_INTERACTIVE_LOGON = _KERB_INTERACTIVE_LOGON;
  {$EXTERNALSYM KERB_INTERACTIVE_LOGON}
  TKerbInteractiveLogon = KERB_INTERACTIVE_LOGON;
  PKerbInteractiveLogon = PKERB_INTERACTIVE_LOGON;

  PKERB_INTERACTIVE_UNLOCK_LOGON = ^KERB_INTERACTIVE_UNLOCK_LOGON;
  {$EXTERNALSYM PKERB_INTERACTIVE_UNLOCK_LOGON}
  _KERB_INTERACTIVE_UNLOCK_LOGON = record
    Logon: KERB_INTERACTIVE_LOGON;
    LogonId: LUID;
  end;
  {$EXTERNALSYM _KERB_INTERACTIVE_UNLOCK_LOGON}
  KERB_INTERACTIVE_UNLOCK_LOGON = _KERB_INTERACTIVE_UNLOCK_LOGON;
  {$EXTERNALSYM KERB_INTERACTIVE_UNLOCK_LOGON}
  TKerbInteractiveUnlockLogon = KERB_INTERACTIVE_UNLOCK_LOGON;
  PKerbInteractiveUnlockLogon = PKERB_INTERACTIVE_UNLOCK_LOGON;

  PKERB_SMART_CARD_LOGON = ^KERB_SMART_CARD_LOGON;
  {$EXTERNALSYM PKERB_SMART_CARD_LOGON}
  _KERB_SMART_CARD_LOGON = record
    MessageType: KERB_LOGON_SUBMIT_TYPE;
    Pin: UNICODE_STRING;
    CspDataLength: ULONG;
    CspData: PUCHAR;
  end;
  {$EXTERNALSYM _KERB_SMART_CARD_LOGON}
  KERB_SMART_CARD_LOGON = _KERB_SMART_CARD_LOGON;
  {$EXTERNALSYM KERB_SMART_CARD_LOGON}
  TKerbSmartCardLogon = KERB_SMART_CARD_LOGON;
  PKerbSmartCardLogon = PKERB_SMART_CARD_LOGON;

  PKERB_SMART_CARD_UNLOCK_LOGON = ^KERB_SMART_CARD_UNLOCK_LOGON;
  {$EXTERNALSYM PKERB_SMART_CARD_UNLOCK_LOGON}
  _KERB_SMART_CARD_UNLOCK_LOGON = record
    Logon: KERB_SMART_CARD_LOGON;
    LogonId: LUID;
  end;
  {$EXTERNALSYM _KERB_SMART_CARD_UNLOCK_LOGON}
  KERB_SMART_CARD_UNLOCK_LOGON = _KERB_SMART_CARD_UNLOCK_LOGON;
  {$EXTERNALSYM KERB_SMART_CARD_UNLOCK_LOGON}
  TKerbSmartCardUnlockLogon = KERB_SMART_CARD_UNLOCK_LOGON;
  PKerbSmartCardUnlockLogon = PKERB_SMART_CARD_UNLOCK_LOGON;

//
// Structure used for a ticket-only logon
//

  PKERB_TICKET_LOGON = ^KERB_TICKET_LOGON;
  {$EXTERNALSYM PKERB_TICKET_LOGON}
  _KERB_TICKET_LOGON = record
    MessageType: KERB_LOGON_SUBMIT_TYPE;
    Flags: ULONG;
    ServiceTicketLength: ULONG;
    TicketGrantingTicketLength: ULONG;
    ServiceTicket: PUCHAR; // REQUIRED: Service ticket "host"
    TicketGrantingTicket: PUCHAR; // OPTIONAL: User's encdoded in a KERB_CRED message, encrypted with session key from service ticket
  end;
  {$EXTERNALSYM _KERB_TICKET_LOGON}
  KERB_TICKET_LOGON = _KERB_TICKET_LOGON;
  {$EXTERNALSYM KERB_TICKET_LOGON}
  TKerbTicketLogon = KERB_TICKET_LOGON;
  PKerbTicketLogon = PKERB_TICKET_LOGON;

//
// Flags for the ticket logon flags field
//

const
  KERB_LOGON_FLAG_ALLOW_EXPIRED_TICKET = $1;
  {$EXTERNALSYM KERB_LOGON_FLAG_ALLOW_EXPIRED_TICKET}

type
  PKERB_TICKET_UNLOCK_LOGON = ^KERB_TICKET_UNLOCK_LOGON;
  {$EXTERNALSYM PKERB_TICKET_UNLOCK_LOGON}
  _KERB_TICKET_UNLOCK_LOGON = record
    Logon: KERB_TICKET_LOGON;
    LogonId: LUID;
  end;
  {$EXTERNALSYM _KERB_TICKET_UNLOCK_LOGON}
  KERB_TICKET_UNLOCK_LOGON = _KERB_TICKET_UNLOCK_LOGON;
  {$EXTERNALSYM KERB_TICKET_UNLOCK_LOGON}
  TKerbTicketUnlockLogon = KERB_TICKET_UNLOCK_LOGON;
  PKerbTicketUnlockLogon = PKERB_TICKET_UNLOCK_LOGON;

//
//  Used for S4U Client requests
//
//

  _KERB_S4U_LOGON = record
    MessageType: KERB_LOGON_SUBMIT_TYPE;
    Flags: ULONG;
    ClientUpn: UNICODE_STRING;   // REQUIRED: UPN for client
    ClientRealm: UNICODE_STRING; // Optional: Client Realm, if known
  end;
  {$EXTERNALSYM _KERB_S4U_LOGON}
  KERB_S4U_LOGON = _KERB_S4U_LOGON;
  {$EXTERNALSYM KERB_S4U_LOGON}
  PKERB_S4U_LOGON = ^KERB_S4U_LOGON;
  {$EXTERNALSYM PKERB_S4U_LOGON}
  TKerbS4ULogon = KERB_S4U_LOGON;
  PKerbS4ULogon = PKERB_S4U_LOGON;  

//
// Use the same profile structure as MSV1_0
//

type
  _KERB_PROFILE_BUFFER_TYPE = (
    kpbtFiller0, kpbtFiller1,
    KerbInteractiveProfile,
    kpbtFiller3,
    KerbSmartCardProfile,
    kpbtFiller5,
    KerbTicketProfile);
  {$EXTERNALSYM _KERB_PROFILE_BUFFER_TYPE}
  KERB_PROFILE_BUFFER_TYPE = _KERB_PROFILE_BUFFER_TYPE;
  {$EXTERNALSYM KERB_PROFILE_BUFFER_TYPE}
  PKERB_PROFILE_BUFFER_TYPE = ^KERB_PROFILE_BUFFER_TYPE;
  {$EXTERNALSYM PKERB_PROFILE_BUFFER_TYPE}
  TKerbProfileBufferType = KERB_PROFILE_BUFFER_TYPE;
  PKerbProfileBufferType = PKERB_PROFILE_BUFFER_TYPE;

  PKERB_INTERACTIVE_PROFILE = ^KERB_INTERACTIVE_PROFILE;
  {$EXTERNALSYM PKERB_INTERACTIVE_PROFILE}
  _KERB_INTERACTIVE_PROFILE = record
    MessageType: KERB_PROFILE_BUFFER_TYPE;
    LogonCount: USHORT;
    BadPasswordCount: USHORT;
    LogonTime: LARGE_INTEGER;
    LogoffTime: LARGE_INTEGER;
    KickOffTime: LARGE_INTEGER;
    PasswordLastSet: LARGE_INTEGER;
    PasswordCanChange: LARGE_INTEGER;
    PasswordMustChange: LARGE_INTEGER;
    LogonScript: UNICODE_STRING;
    HomeDirectory: UNICODE_STRING;
    FullName: UNICODE_STRING;
    ProfilePath: UNICODE_STRING;
    HomeDirectoryDrive: UNICODE_STRING;
    LogonServer: UNICODE_STRING;
    UserFlags: ULONG;
  end;
  {$EXTERNALSYM _KERB_INTERACTIVE_PROFILE}
  KERB_INTERACTIVE_PROFILE = _KERB_INTERACTIVE_PROFILE;
  {$EXTERNALSYM KERB_INTERACTIVE_PROFILE}
  TKerbInteractiveProfile = KERB_INTERACTIVE_PROFILE;
  PKerbInteractiveProfile = PKERB_INTERACTIVE_PROFILE;

//
// For smart card, we return a smart card profile, which is an interactive
// profile plus a certificate
//

  PKERB_SMART_CARD_PROFILE = ^KERB_SMART_CARD_PROFILE;
  {$EXTERNALSYM PKERB_SMART_CARD_PROFILE}
  _KERB_SMART_CARD_PROFILE = record
    Profile: KERB_INTERACTIVE_PROFILE;
    CertificateSize: ULONG;
    CertificateData: PUCHAR;
  end;
  {$EXTERNALSYM _KERB_SMART_CARD_PROFILE}
  KERB_SMART_CARD_PROFILE = _KERB_SMART_CARD_PROFILE;
  {$EXTERNALSYM KERB_SMART_CARD_PROFILE}
  TKerbSmartCardProfile = KERB_SMART_CARD_PROFILE;
  PKerbSmartCardProfile = PKERB_SMART_CARD_PROFILE;

//
// For a ticket logon profile, we return the session key from the ticket
//

  PKERB_CRYPTO_KEY = ^KERB_CRYPTO_KEY;
  {$EXTERNALSYM PKERB_CRYPTO_KEY}
  KERB_CRYPTO_KEY = record
    KeyType: LONG;
    Length: ULONG;
    Value: PUCHAR;
  end;
  {$EXTERNALSYM KERB_CRYPTO_KEY}
  TKerbCryptoKey = KERB_CRYPTO_KEY;
  PKerbCryptoKey = PKERB_CRYPTO_KEY;

  PKERB_TICKET_PROFILE = ^KERB_TICKET_PROFILE;
  {$EXTERNALSYM PKERB_TICKET_PROFILE}
  _KERB_TICKET_PROFILE = record
    Profile: KERB_INTERACTIVE_PROFILE;
    SessionKey: KERB_CRYPTO_KEY;
  end;
  {$EXTERNALSYM _KERB_TICKET_PROFILE}
  KERB_TICKET_PROFILE = _KERB_TICKET_PROFILE;
  {$EXTERNALSYM KERB_TICKET_PROFILE}
  TKerbTicketProfile = KERB_TICKET_PROFILE;
  PKerbTicketProfile = PKERB_TICKET_PROFILE;

  _KERB_PROTOCOL_MESSAGE_TYPE = (
    KerbDebugRequestMessage,
    KerbQueryTicketCacheMessage,
    KerbChangeMachinePasswordMessage,
    KerbVerifyPacMessage,
    KerbRetrieveTicketMessage,
    KerbUpdateAddressesMessage,
    KerbPurgeTicketCacheMessage,
    KerbChangePasswordMessage,
    KerbRetrieveEncodedTicketMessage,
    KerbDecryptDataMessage,
    KerbAddBindingCacheEntryMessage,
    KerbSetPasswordMessage,
    KerbSetPasswordExMessage,
    KerbVerifyCredentialsMessage,
    KerbQueryTicketCacheExMessage,
    KerbPurgeTicketCacheExMessage,
    KerbRefreshSmartcardCredentialsMessage,
    KerbAddExtraCredentialsMessage,
    KerbQuerySupplementalCredentialsMessage);
  {$EXTERNALSYM _KERB_PROTOCOL_MESSAGE_TYPE}
  KERB_PROTOCOL_MESSAGE_TYPE = _KERB_PROTOCOL_MESSAGE_TYPE;
  {$EXTERNALSYM KERB_PROTOCOL_MESSAGE_TYPE}
  PKERB_PROTOCOL_MESSAGE_TYPE = ^KERB_PROTOCOL_MESSAGE_TYPE;
  {$EXTERNALSYM PKERB_PROTOCOL_MESSAGE_TYPE}
  TKerbProtocolMessageType = KERB_PROTOCOL_MESSAGE_TYPE;
  PKerbProtocolMessageType = PKERB_PROTOCOL_MESSAGE_TYPE;  

//
// Used both for retrieving tickets and for querying ticket cache
//

  PKERB_QUERY_TKT_CACHE_REQUEST = ^KERB_QUERY_TKT_CACHE_REQUEST;
  {$EXTERNALSYM PKERB_QUERY_TKT_CACHE_REQUEST}
  _KERB_QUERY_TKT_CACHE_REQUEST = record
    MessageType: KERB_PROTOCOL_MESSAGE_TYPE;
    LogonId: LUID;
  end;
  {$EXTERNALSYM _KERB_QUERY_TKT_CACHE_REQUEST}
  KERB_QUERY_TKT_CACHE_REQUEST = _KERB_QUERY_TKT_CACHE_REQUEST;
  {$EXTERNALSYM KERB_QUERY_TKT_CACHE_REQUEST}
  TKerbQueryTktCacheRequest = KERB_QUERY_TKT_CACHE_REQUEST;
  PKerbQueryTktCacheRequest = PKERB_QUERY_TKT_CACHE_REQUEST;

  PKERB_TICKET_CACHE_INFO = ^KERB_TICKET_CACHE_INFO;
  {$EXTERNALSYM PKERB_TICKET_CACHE_INFO}
  _KERB_TICKET_CACHE_INFO = record
    ServerName: UNICODE_STRING;
    RealmName: UNICODE_STRING;
    StartTime: LARGE_INTEGER;
    EndTime: LARGE_INTEGER;
    RenewTime: LARGE_INTEGER;
    EncryptionType: LONG;
    TicketFlags: ULONG;
  end;
  {$EXTERNALSYM _KERB_TICKET_CACHE_INFO}
  KERB_TICKET_CACHE_INFO = _KERB_TICKET_CACHE_INFO;
  {$EXTERNALSYM KERB_TICKET_CACHE_INFO}
  TKerbTicketCacheInfo = KERB_TICKET_CACHE_INFO;
  PKerbTicketCacheInfo = PKERB_TICKET_CACHE_INFO;

  _KERB_TICKET_CACHE_INFO_EX = record
    ClientName: UNICODE_STRING;
    ClientRealm: UNICODE_STRING;
    ServerName: UNICODE_STRING;
    ServerRealm: UNICODE_STRING;
    StartTime: LARGE_INTEGER;
    EndTime: LARGE_INTEGER;
    RenewTime: LARGE_INTEGER;
    EncryptionType: LONG;
    TicketFlags: ULONG;
  end;
  {$EXTERNALSYM _KERB_TICKET_CACHE_INFO_EX}
  KERB_TICKET_CACHE_INFO_EX = _KERB_TICKET_CACHE_INFO_EX;
  {$EXTERNALSYM KERB_TICKET_CACHE_INFO_EX}
  PKERB_TICKET_CACHE_INFO_EX = ^KERB_TICKET_CACHE_INFO_EX;
  {$EXTERNALSYM PKERB_TICKET_CACHE_INFO_EX}
  TKerbTicketCacheInfoEx = KERB_TICKET_CACHE_INFO_EX;
  PKerbTicketCacheInfoEx = PKERB_TICKET_CACHE_INFO_EX;  

  PKERB_QUERY_TKT_CACHE_RESPONSE = ^KERB_QUERY_TKT_CACHE_RESPONSE;
  {$EXTERNALSYM PKERB_QUERY_TKT_CACHE_RESPONSE}
  _KERB_QUERY_TKT_CACHE_RESPONSE = record
    MessageType: KERB_PROTOCOL_MESSAGE_TYPE;
    CountOfTickets: ULONG;
    Tickets: array [0..ANYSIZE_ARRAY - 1] of KERB_TICKET_CACHE_INFO;
  end;
  {$EXTERNALSYM _KERB_QUERY_TKT_CACHE_RESPONSE}
  KERB_QUERY_TKT_CACHE_RESPONSE = _KERB_QUERY_TKT_CACHE_RESPONSE;
  {$EXTERNALSYM KERB_QUERY_TKT_CACHE_RESPONSE}
  TKerbQueryTktCacheResponse = KERB_QUERY_TKT_CACHE_RESPONSE;
  PKerbQueryTktCacheResponse = PKERB_QUERY_TKT_CACHE_RESPONSE;

  _KERB_QUERY_TKT_CACHE_EX_RESPONSE = record
    MessageType: KERB_PROTOCOL_MESSAGE_TYPE;
    CountOfTickets: ULONG;
    Tickets: array [0..ANYSIZE_ARRAY - 1] of KERB_TICKET_CACHE_INFO_EX;
  end;
  {$EXTERNALSYM _KERB_QUERY_TKT_CACHE_EX_RESPONSE}
  KERB_QUERY_TKT_CACHE_EX_RESPONSE = _KERB_QUERY_TKT_CACHE_EX_RESPONSE;
  {$EXTERNALSYM KERB_QUERY_TKT_CACHE_EX_RESPONSE}
  PKERB_QUERY_TKT_CACHE_EX_RESPONSE = ^KERB_QUERY_TKT_CACHE_EX_RESPONSE;
  {$EXTERNALSYM PKERB_QUERY_TKT_CACHE_EX_RESPONSE}
  TKerbQueryTktCacheExResponse = KERB_QUERY_TKT_CACHE_EX_RESPONSE;
  PKerbQueryTktCacheExResponse = PKERB_QUERY_TKT_CACHE_EX_RESPONSE;  

//
// Types for retrieving encoded ticket from the cache
//

  _SecHandle = record
    dwLower: ULONG_PTR;
    dwUpper: ULONG_PTR;
  end;
  {$EXTERNALSYM _SecHandle}
  SecHandle = _SecHandle;
  {$EXTERNALSYM SecHandle}
  PSecHandle = ^SecHandle;
  {$EXTERNALSYM PSecHandle}

// Ticket Flags

const
  KERB_USE_DEFAULT_TICKET_FLAGS = $0;
  {$EXTERNALSYM KERB_USE_DEFAULT_TICKET_FLAGS}

// CacheOptions

  KERB_RETRIEVE_TICKET_DEFAULT  = $0;
  {$EXTERNALSYM KERB_RETRIEVE_TICKET_DEFAULT}
  KERB_RETRIEVE_TICKET_DONT_USE_CACHE = $1;
  {$EXTERNALSYM KERB_RETRIEVE_TICKET_DONT_USE_CACHE}
  KERB_RETRIEVE_TICKET_USE_CACHE_ONLY = $2;
  {$EXTERNALSYM KERB_RETRIEVE_TICKET_USE_CACHE_ONLY}
  KERB_RETRIEVE_TICKET_USE_CREDHANDLE = $4;
  {$EXTERNALSYM KERB_RETRIEVE_TICKET_USE_CREDHANDLE}
  KERB_RETRIEVE_TICKET_AS_KERB_CRED   = $8;
  {$EXTERNALSYM KERB_RETRIEVE_TICKET_AS_KERB_CRED}
  KERB_RETRIEVE_TICKET_WITH_SEC_CRED  = $10;
  {$EXTERNALSYM KERB_RETRIEVE_TICKET_WITH_SEC_CRED}

// Encryption Type options

  KERB_ETYPE_DEFAULT = $0; // don't specify etype in tkt req.
  {$EXTERNALSYM KERB_ETYPE_DEFAULT}

type
  _KERB_AUTH_DATA = record
    Type_: ULONG;
    Length: ULONG;
    Data: PUCHAR;
  end;
  {$EXTERNALSYM _KERB_AUTH_DATA}
  KERB_AUTH_DATA = _KERB_AUTH_DATA;
  {$EXTERNALSYM KERB_AUTH_DATA}
  PKERB_AUTH_DATA = ^KERB_AUTH_DATA;
  {$EXTERNALSYM PKERB_AUTH_DATA}
  TKerbAuthData = KERB_AUTH_DATA;
  PKerbAuthData = PKERB_AUTH_DATA;

  _KERB_NET_ADDRESS = record
    Family: ULONG;
    Length: ULONG;
    Address: PCHAR;
  end;
  {$EXTERNALSYM _KERB_NET_ADDRESS}
  KERB_NET_ADDRESS = _KERB_NET_ADDRESS;
  {$EXTERNALSYM KERB_NET_ADDRESS}
  PKERB_NET_ADDRESS = ^KERB_NET_ADDRESS;
  {$EXTERNALSYM PKERB_NET_ADDRESS}
  TKerbNetAddress = KERB_NET_ADDRESS;
  PKerbNetAddress = PKERB_NET_ADDRESS;

  _KERB_NET_ADDRESSES = record
    Number: ULONG;
    Addresses: array [0..ANYSIZE_ARRAY - 1] of KERB_NET_ADDRESS;
  end;
  {$EXTERNALSYM _KERB_NET_ADDRESSES}
  KERB_NET_ADDRESSES = _KERB_NET_ADDRESSES;
  {$EXTERNALSYM KERB_NET_ADDRESSES}
  PKERB_NET_ADDRESSES = ^KERB_NET_ADDRESSES;
  {$EXTERNALSYM PKERB_NET_ADDRESSES}
  TKerbNetAddresses = KERB_NET_ADDRESSES;
  PKerbNetAddresses = PKERB_NET_ADDRESSES;  

//
// Types for the information about a ticket
//

type
  PKERB_EXTERNAL_NAME = ^KERB_EXTERNAL_NAME;
  {$EXTERNALSYM PKERB_EXTERNAL_NAME}
  _KERB_EXTERNAL_NAME = record
    NameType: SHORT;
    NameCount: USHORT;
    Names: array [0..ANYSIZE_ARRAY - 1] of UNICODE_STRING;
  end;
  {$EXTERNALSYM _KERB_EXTERNAL_NAME}
  KERB_EXTERNAL_NAME = _KERB_EXTERNAL_NAME;
  {$EXTERNALSYM KERB_EXTERNAL_NAME}
  TKerbExternalName = KERB_EXTERNAL_NAME;
  PKerbExternalName = PKERB_EXTERNAL_NAME;

  PKERB_EXTERNAL_TICKET = ^KERB_EXTERNAL_TICKET;
  {$EXTERNALSYM PKERB_EXTERNAL_TICKET}
  _KERB_EXTERNAL_TICKET = record
    ServiceName: PKERB_EXTERNAL_NAME;
    TargetName: PKERB_EXTERNAL_NAME;
    ClientName: PKERB_EXTERNAL_NAME;
    DomainName: UNICODE_STRING;
    TargetDomainName: UNICODE_STRING;  // contains ClientDomainName
    AltTargetDomainName: UNICODE_STRING;
    SessionKey: KERB_CRYPTO_KEY;
    TicketFlags: ULONG;
    Flags: ULONG;
    KeyExpirationTime: LARGE_INTEGER;
    StartTime: LARGE_INTEGER;
    EndTime: LARGE_INTEGER;
    RenewUntil: LARGE_INTEGER;
    TimeSkew: LARGE_INTEGER;
    EncodedTicketSize: ULONG;
    EncodedTicket: PUCHAR;
  end;
  {$EXTERNALSYM _KERB_EXTERNAL_TICKET}
  KERB_EXTERNAL_TICKET = _KERB_EXTERNAL_TICKET;
  {$EXTERNALSYM KERB_EXTERNAL_TICKET}
  TKerbExternalTicket = KERB_EXTERNAL_TICKET;
  PKerbExternalTicket = PKERB_EXTERNAL_TICKET;

  _KERB_RETRIEVE_TKT_REQUEST = record
    MessageType: KERB_PROTOCOL_MESSAGE_TYPE;
    LogonId: LUID;
    TargetName: UNICODE_STRING;
    TicketFlags: ULONG;
    CacheOptions: ULONG;
    EncryptionType: LONG;
    CredentialsHandle: SecHandle;
  end;
  {$EXTERNALSYM _KERB_RETRIEVE_TKT_REQUEST}
  KERB_RETRIEVE_TKT_REQUEST = _KERB_RETRIEVE_TKT_REQUEST;
  {$EXTERNALSYM KERB_RETRIEVE_TKT_REQUEST}
  PKERB_RETRIEVE_TKT_REQUEST = ^KERB_RETRIEVE_TKT_REQUEST;
  {$EXTERNALSYM PKERB_RETRIEVE_TKT_REQUEST}
  TKerbRetrieveTktRequest = KERB_RETRIEVE_TKT_REQUEST;
  PKerbRetrieveTktRequest = PKERB_RETRIEVE_TKT_REQUEST;

  PKERB_RETRIEVE_TKT_RESPONSE = ^KERB_RETRIEVE_TKT_RESPONSE;
  {$EXTERNALSYM PKERB_RETRIEVE_TKT_RESPONSE}
  _KERB_RETRIEVE_TKT_RESPONSE = record
    Ticket: KERB_EXTERNAL_TICKET;
  end;
  {$EXTERNALSYM _KERB_RETRIEVE_TKT_RESPONSE}
  KERB_RETRIEVE_TKT_RESPONSE = _KERB_RETRIEVE_TKT_RESPONSE;
  {$EXTERNALSYM KERB_RETRIEVE_TKT_RESPONSE}
  TKerbRetrieveTktResponse = KERB_RETRIEVE_TKT_RESPONSE;
  PKerbRetrieveTktResponse = PKERB_RETRIEVE_TKT_RESPONSE;

//
// Used to purge entries from the ticket cache
//

  PKERB_PURGE_TKT_CACHE_REQUEST = ^KERB_PURGE_TKT_CACHE_REQUEST;
  {$EXTERNALSYM PKERB_PURGE_TKT_CACHE_REQUEST}
  _KERB_PURGE_TKT_CACHE_REQUEST = record
    MessageType: KERB_PROTOCOL_MESSAGE_TYPE;
    LogonId: LUID;
    ServerName: UNICODE_STRING;
    RealmName: UNICODE_STRING;
  end;
  {$EXTERNALSYM _KERB_PURGE_TKT_CACHE_REQUEST}
  KERB_PURGE_TKT_CACHE_REQUEST = _KERB_PURGE_TKT_CACHE_REQUEST;
  {$EXTERNALSYM KERB_PURGE_TKT_CACHE_REQUEST}
  TKerbPurgeTktCacheRequest = KERB_PURGE_TKT_CACHE_REQUEST;
  PKerbPurgeTktCacheRequest = PKERB_PURGE_TKT_CACHE_REQUEST;

//
// Flags for purge requests
//

const
  KERB_PURGE_ALL_TICKETS = 1;
  {$EXTERNALSYM KERB_PURGE_ALL_TICKETS}

type
  _KERB_PURGE_TKT_CACHE_EX_REQUEST = record
    MessageType: KERB_PROTOCOL_MESSAGE_TYPE;
    LogonId: LUID;
    Flags: ULONG;
    TicketTemplate: KERB_TICKET_CACHE_INFO_EX;
  end;
  {$EXTERNALSYM _KERB_PURGE_TKT_CACHE_EX_REQUEST}
  KERB_PURGE_TKT_CACHE_EX_REQUEST = _KERB_PURGE_TKT_CACHE_EX_REQUEST;
  {$EXTERNALSYM KERB_PURGE_TKT_CACHE_EX_REQUEST}
  PKERB_PURGE_TKT_CACHE_EX_REQUEST = ^KERB_PURGE_TKT_CACHE_EX_REQUEST;
  {$EXTERNALSYM PKERB_PURGE_TKT_CACHE_EX_REQUEST}
  TKerbPurgeTktCacheExRequest = KERB_PURGE_TKT_CACHE_EX_REQUEST;
  PKerbPurgeTktCacheExRequest = PKERB_PURGE_TKT_CACHE_EX_REQUEST;

//
// KerbChangePassword
//
// KerbChangePassword changes the password on the KDC account plus
//  the password cache and logon credentials if applicable.
//
//

  PKERB_CHANGEPASSWORD_REQUEST = ^KERB_CHANGEPASSWORD_REQUEST;
  {$EXTERNALSYM PKERB_CHANGEPASSWORD_REQUEST}
  _KERB_CHANGEPASSWORD_REQUEST = record
    MessageType: KERB_PROTOCOL_MESSAGE_TYPE;
    DomainName: UNICODE_STRING;
    AccountName: UNICODE_STRING;
    OldPassword: UNICODE_STRING;
    NewPassword: UNICODE_STRING;
    Impersonating: ByteBool;
  end;
  {$EXTERNALSYM _KERB_CHANGEPASSWORD_REQUEST}
  KERB_CHANGEPASSWORD_REQUEST = _KERB_CHANGEPASSWORD_REQUEST;
  {$EXTERNALSYM KERB_CHANGEPASSWORD_REQUEST}
  TKerbChangepasswordRequest = KERB_CHANGEPASSWORD_REQUEST;
  PKerbChangepasswordRequest = PKERB_CHANGEPASSWORD_REQUEST;

//
// KerbSetPassword
//
// KerbSetPassword changes the password on the KDC account plus
//  the password cache and logon credentials if applicable.
//
//

  PKERB_SETPASSWORD_REQUEST = ^KERB_SETPASSWORD_REQUEST;
  {$EXTERNALSYM PKERB_SETPASSWORD_REQUEST}
  _KERB_SETPASSWORD_REQUEST = record
    MessageType: KERB_PROTOCOL_MESSAGE_TYPE;
    LogonId: LUID;
    CredentialsHandle: SecHandle;
    Flags: ULONG;
    DomainName: UNICODE_STRING;
    AccountName: UNICODE_STRING;
    Password: UNICODE_STRING;
  end;
  {$EXTERNALSYM _KERB_SETPASSWORD_REQUEST}
  KERB_SETPASSWORD_REQUEST = _KERB_SETPASSWORD_REQUEST;
  {$EXTERNALSYM KERB_SETPASSWORD_REQUEST}
  TKerbSetpasswordRequest = KERB_SETPASSWORD_REQUEST;
  PKerbSetpasswordRequest = PKERB_SETPASSWORD_REQUEST;

  _KERB_SETPASSWORD_EX_REQUEST = record
    MessageType: KERB_PROTOCOL_MESSAGE_TYPE;
    LogonId: LUID;
    CredentialsHandle: SecHandle;
    Flags: ULONG;
    AccountRealm: UNICODE_STRING;
    AccountName: UNICODE_STRING;
    Password: UNICODE_STRING;
    ClientRealm: UNICODE_STRING;
    ClientName: UNICODE_STRING;
    Impersonating: BOOLEAN;
    KdcAddress: UNICODE_STRING;
    KdcAddressType: ULONG;
  end;
  {$EXTERNALSYM _KERB_SETPASSWORD_EX_REQUEST}
  KERB_SETPASSWORD_EX_REQUEST = _KERB_SETPASSWORD_EX_REQUEST;
  {$EXTERNALSYM KERB_SETPASSWORD_EX_REQUEST}
  PKERB_SETPASSWORD_EX_REQUEST = ^KERB_SETPASSWORD_EX_REQUEST;
  {$EXTERNALSYM PKERB_SETPASSWORD_EX_REQUEST}
  TKerbSetPasswordExRequest = KERB_SETPASSWORD_EX_REQUEST;
  PKerbSetPasswordExRequest = PKERB_SETPASSWORD_EX_REQUEST;  

const
  DS_UNKNOWN_ADDRESS_TYPE     = 0; // anything *but* IP
  {$EXTERNALSYM DS_UNKNOWN_ADDRESS_TYPE}
  KERB_SETPASS_USE_LOGONID    = 1;
  {$EXTERNALSYM KERB_SETPASS_USE_LOGONID}
  KERB_SETPASS_USE_CREDHANDLE = 2;
  {$EXTERNALSYM KERB_SETPASS_USE_CREDHANDLE}

type
  PKERB_DECRYPT_REQUEST = ^KERB_DECRYPT_REQUEST;
  {$EXTERNALSYM PKERB_DECRYPT_REQUEST}
  _KERB_DECRYPT_REQUEST = record
    MessageType: KERB_PROTOCOL_MESSAGE_TYPE;
    LogonId: LUID;
    Flags: ULONG;
    CryptoType: LONG;
    KeyUsage: LONG;
    Key: KERB_CRYPTO_KEY; // optional
    EncryptedDataSize: ULONG;
    InitialVectorSize: ULONG;
    InitialVector: PUCHAR;
    EncryptedData: PUCHAR;
  end;
  {$EXTERNALSYM _KERB_DECRYPT_REQUEST}
  KERB_DECRYPT_REQUEST = _KERB_DECRYPT_REQUEST;
  {$EXTERNALSYM KERB_DECRYPT_REQUEST}
  TKerbDecryptRequest = KERB_DECRYPT_REQUEST;
  PKerbDecryptRequest = PKERB_DECRYPT_REQUEST;

//
// If set, use the primary key from the current logon session of the one provided in the LogonId field.
// Otherwise, use the Key in the KERB_DECRYPT_MESSAGE.

const
  KERB_DECRYPT_FLAG_DEFAULT_KEY = $00000001;
  {$EXTERNALSYM KERB_DECRYPT_FLAG_DEFAULT_KEY}

type
  PKERB_DECRYPT_RESPONSE = ^KERB_DECRYPT_RESPONSE;
  {$EXTERNALSYM PKERB_DECRYPT_RESPONSE}
  _KERB_DECRYPT_RESPONSE = record
    DecryptedData: array [0..ANYSIZE_ARRAY - 1] of UCHAR;
  end;
  {$EXTERNALSYM _KERB_DECRYPT_RESPONSE}
  KERB_DECRYPT_RESPONSE = _KERB_DECRYPT_RESPONSE;
  {$EXTERNALSYM KERB_DECRYPT_RESPONSE}
  TKerbDecryptResponse = KERB_DECRYPT_RESPONSE;
  PKerbDecryptResponse = PKERB_DECRYPT_RESPONSE;

//
// Request structure for adding a binding cache entry. TCB privilege
// is required for this operation.
//

  PKERB_ADD_BINDING_CACHE_ENTRY_REQUEST = ^KERB_ADD_BINDING_CACHE_ENTRY_REQUEST;
  {$EXTERNALSYM PKERB_ADD_BINDING_CACHE_ENTRY_REQUEST}
  _KERB_ADD_BINDING_CACHE_ENTRY_REQUEST = record
    MessageType: KERB_PROTOCOL_MESSAGE_TYPE;
    RealmName: UNICODE_STRING;
    KdcAddress: UNICODE_STRING;
    AddressType: ULONG; //dsgetdc.h DS_NETBIOS_ADDRESS||DS_INET_ADDRESS
  end;
  {$EXTERNALSYM _KERB_ADD_BINDING_CACHE_ENTRY_REQUEST}
  KERB_ADD_BINDING_CACHE_ENTRY_REQUEST = _KERB_ADD_BINDING_CACHE_ENTRY_REQUEST;
  {$EXTERNALSYM KERB_ADD_BINDING_CACHE_ENTRY_REQUEST}
  TKerbAddBindingCacheEntryRequest = KERB_ADD_BINDING_CACHE_ENTRY_REQUEST;
  PKerbAddBindingCacheEntryRequest = PKERB_ADD_BINDING_CACHE_ENTRY_REQUEST;

//
// Request structure for reacquiring smartcard credentials for a 
// given LUID.
// Requires TCB.
//

  _KERB_REFRESH_SCCRED_REQUEST = record
    MessageType: KERB_PROTOCOL_MESSAGE_TYPE;
    CredentialBlob: UNICODE_STRING;	 // optional
    LogonId: LUID;
    Flags: ULONG;
  end;
  {$EXTERNALSYM _KERB_REFRESH_SCCRED_REQUEST}
  KERB_REFRESH_SCCRED_REQUEST = _KERB_REFRESH_SCCRED_REQUEST;
  {$EXTERNALSYM KERB_REFRESH_SCCRED_REQUEST}
  PKERB_REFRESH_SCCRED_REQUEST = ^KERB_REFRESH_SCCRED_REQUEST;
  {$EXTERNALSYM PKERB_REFRESH_SCCRED_REQUEST}
  TKerbRefreshScCredRequest = KERB_REFRESH_SCCRED_REQUEST;
  PKerbRefreshScCredRequest = PKERB_REFRESH_SCCRED_REQUEST;  

//
// Flags for KERB_REFRESH_SCCRED_REQUEST
//
//	KERB_REFRESH_SCCRED_RELEASE
// 	Release the smartcard handle for LUID
//
//      KERB_REFRESH_SCCRED_GETTGT
//	Use the certificate hash in the blob to get a TGT for the logon 
//	session.
//

const
  KERB_REFRESH_SCCRED_RELEASE = $0;
  {$EXTERNALSYM KERB_REFRESH_SCCRED_RELEASE}
  KERB_REFRESH_SCCRED_GETTGT  = $1;
  {$EXTERNALSYM KERB_REFRESH_SCCRED_GETTGT}

//
// Request structure for adding extra Server credentials to a given
// logon session.  Only applicable during AcceptSecurityContext, and
// requires TCB to alter "other" creds
//

type
  _KERB_ADD_CREDENTIALS_REQUEST = record
    MessageType: KERB_PROTOCOL_MESSAGE_TYPE;
    UserName: UNICODE_STRING;
    DomainName: UNICODE_STRING;
    Password: UNICODE_STRING;
    LogonId: LUID; // optional
    Flags: ULONG;
  end;
  {$EXTERNALSYM _KERB_ADD_CREDENTIALS_REQUEST}
  KERB_ADD_CREDENTIALS_REQUEST = _KERB_ADD_CREDENTIALS_REQUEST;
  {$EXTERNALSYM KERB_ADD_CREDENTIALS_REQUEST}
  PKERB_ADD_CREDENTIALS_REQUEST = ^KERB_ADD_CREDENTIALS_REQUEST;
  {$EXTERNALSYM PKERB_ADD_CREDENTIALS_REQUEST}
  TKerbAddCredentialsRequest = KERB_ADD_CREDENTIALS_REQUEST;
  PKerbAddCredentialsRequest = PKERB_ADD_CREDENTIALS_REQUEST;

const
  KERB_REQUEST_ADD_CREDENTIAL     = 1;
  {$EXTERNALSYM KERB_REQUEST_ADD_CREDENTIAL}
  KERB_REQUEST_REPLACE_CREDENTIAL = 2;
  {$EXTERNALSYM KERB_REQUEST_REPLACE_CREDENTIAL}
  KERB_REQUEST_REMOVE_CREDENTIAL  = 4;
  {$EXTERNALSYM KERB_REQUEST_REMOVE_CREDENTIAL}

implementation

function LSA_SUCCESS(Error: NTSTATUS): BOOL;
begin
 Result := LONG(Error) > 0;
end;

const
  secur32 = 'secur32.dll';
  advapi32 = 'advapi32.dll';


{$IFDEF DYNAMIC_LINK}
var
  _LsaRegisterLogonProcess: Pointer;

function LsaRegisterLogonProcess;
begin
  GetProcedureAddress(_LsaRegisterLogonProcess, secur32, 'LsaRegisterLogonProcess');
  asm
    mov esp, ebp
    pop ebp
    jmp [_LsaRegisterLogonProcess]
  end;
end;
{$ELSE}
function LsaRegisterLogonProcess; external secur32 name 'LsaRegisterLogonProcess';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _LsaLogonUser: Pointer;

function LsaLogonUser;
begin
  GetProcedureAddress(_LsaLogonUser, secur32, 'LsaLogonUser');
  asm
    mov esp, ebp
    pop ebp
    jmp [_LsaLogonUser]
  end;
end;
{$ELSE}
function LsaLogonUser; external secur32 name 'LsaLogonUser';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _LsaLookupAuthenticationPackage: Pointer;

function LsaLookupAuthenticationPackage;
begin
  GetProcedureAddress(_LsaLookupAuthenticationPackage, secur32, 'LsaLookupAuthenticationPackage');
  asm
    mov esp, ebp
    pop ebp
    jmp [_LsaLookupAuthenticationPackage]
  end;
end;
{$ELSE}
function LsaLookupAuthenticationPackage; external secur32 name 'LsaLookupAuthenticationPackage';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _LsaFreeReturnBuffer: Pointer;

function LsaFreeReturnBuffer;
begin
  GetProcedureAddress(_LsaFreeReturnBuffer, secur32, 'LsaFreeReturnBuffer');
  asm
    mov esp, ebp
    pop ebp
    jmp [_LsaFreeReturnBuffer]
  end;
end;
{$ELSE}
function LsaFreeReturnBuffer; external secur32 name 'LsaFreeReturnBuffer';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _LsaCallAuthenticationPackage: Pointer;

function LsaCallAuthenticationPackage;
begin
  GetProcedureAddress(_LsaCallAuthenticationPackage, secur32, 'LsaCallAuthenticationPackage');
  asm
    mov esp, ebp
    pop ebp
    jmp [_LsaCallAuthenticationPackage]
  end;
end;
{$ELSE}
function LsaCallAuthenticationPackage; external secur32 name 'LsaCallAuthenticationPackage';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _LsaDeregisterLogonProcess: Pointer;

function LsaDeregisterLogonProcess;
begin
  GetProcedureAddress(_LsaDeregisterLogonProcess, secur32, 'LsaDeregisterLogonProcess');
  asm
    mov esp, ebp
    pop ebp
    jmp [_LsaDeregisterLogonProcess]
  end;
end;
{$ELSE}
function LsaDeregisterLogonProcess; external secur32 name 'LsaDeregisterLogonProcess';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _LsaConnectUntrusted: Pointer;

function LsaConnectUntrusted;
begin
  GetProcedureAddress(_LsaConnectUntrusted, secur32, 'LsaConnectUntrusted');
  asm
    mov esp, ebp
    pop ebp
    jmp [_LsaConnectUntrusted]
  end;
end;
{$ELSE}
function LsaConnectUntrusted; external secur32 name 'LsaConnectUntrusted';
{$ENDIF DYNAMIC_LINK}


{$IFDEF DYNAMIC_LINK}
var
  _LsaFreeMemory: Pointer;

function LsaFreeMemory;
begin
  GetProcedureAddress(_LsaFreeMemory, advapi32, 'LsaFreeMemory');
  asm
    mov esp, ebp
    pop ebp
    jmp [_LsaFreeMemory]
  end;
end;
{$ELSE}
function LsaFreeMemory; external advapi32 name 'LsaFreeMemory';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _LsaClose: Pointer;

function LsaClose;
begin
  GetProcedureAddress(_LsaClose, advapi32, 'LsaClose');
  asm
    mov esp, ebp
    pop ebp
    jmp [_LsaClose]
  end;
end;
{$ELSE}
function LsaClose; external advapi32 name 'LsaClose';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _LsaOpenPolicy: Pointer;

function LsaOpenPolicy;
begin
  GetProcedureAddress(_LsaOpenPolicy, advapi32, 'LsaOpenPolicy');
  asm
    mov esp, ebp
    pop ebp
    jmp [_LsaOpenPolicy]
  end;
end;
{$ELSE}
function LsaOpenPolicy; external advapi32 name 'LsaOpenPolicy';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _LsaEnumerateLogonSessions: Pointer;

function LsaEnumerateLogonSessions;
begin
  GetProcedureAddress(_LsaEnumerateLogonSessions, secur32, 'LsaEnumerateLogonSessions');
  asm
    mov esp, ebp
    pop ebp
    jmp [_LsaEnumerateLogonSessions]
  end;
end;
{$ELSE}
function LsaEnumerateLogonSessions; external secur32 name 'LsaEnumerateLogonSessions';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _LsaGetLogonSessionData: Pointer;

function LsaGetLogonSessionData;
begin
  GetProcedureAddress(_LsaGetLogonSessionData, secur32, 'LsaGetLogonSessionData');
  asm
    mov esp, ebp
    pop ebp
    jmp [_LsaGetLogonSessionData]
  end;
end;
{$ELSE}
function LsaGetLogonSessionData; external secur32 name 'LsaGetLogonSessionData';
{$ENDIF DYNAMIC_LINK}


{$IFDEF DYNAMIC_LINK}
var
  _LsaQueryInformationPolicy: Pointer;

function LsaQueryInformationPolicy;
begin
  GetProcedureAddress(_LsaQueryInformationPolicy, advapi32, 'LsaQueryInformationPolicy');
  asm
    mov esp, ebp
    pop ebp
    jmp [_LsaQueryInformationPolicy]
  end;
end;
{$ELSE}
function LsaQueryInformationPolicy; external advapi32 name 'LsaQueryInformationPolicy';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _LsaSetInformationPolicy: Pointer;

function LsaSetInformationPolicy;
begin
  GetProcedureAddress(_LsaSetInformationPolicy, advapi32, 'LsaSetInformationPolicy');
  asm
    mov esp, ebp
    pop ebp
    jmp [_LsaSetInformationPolicy]
  end;
end;
{$ELSE}
function LsaSetInformationPolicy; external advapi32 name 'LsaSetInformationPolicy';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _LsaQueryDomainInformationPolicy: Pointer;

function LsaQueryDomainInformationPolicy;
begin
  GetProcedureAddress(_LsaQueryDomainInformationPolicy, advapi32, 'LsaQueryDomainInformationPolicy');
  asm
    mov esp, ebp
    pop ebp
    jmp [_LsaQueryDomainInformationPolicy]
  end;
end;
{$ELSE}
function LsaQueryDomainInformationPolicy; external advapi32 name 'LsaQueryDomainInformationPolicy';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _LsaSetDomainInformationPolicy: Pointer;

function LsaSetDomainInformationPolicy;
begin
  GetProcedureAddress(_LsaSetDomainInformationPolicy, advapi32, 'LsaSetDomainInformationPolicy');
  asm
    mov esp, ebp
    pop ebp
    jmp [_LsaSetDomainInformationPolicy]
  end;
end;
{$ELSE}
function LsaSetDomainInformationPolicy; external advapi32 name 'LsaSetDomainInformationPolicy';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _LsaRegisterPolicyChangeNot: Pointer;

function LsaRegisterPolicyChangeNotification;
begin
  GetProcedureAddress(_LsaRegisterPolicyChangeNot, secur32, 'LsaRegisterPolicyChangeNotification');
  asm
    mov esp, ebp
    pop ebp
    jmp [_LsaRegisterPolicyChangeNot]
  end;
end;
{$ELSE}
function LsaRegisterPolicyChangeNotification; external secur32 name 'LsaRegisterPolicyChangeNotification';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _LsaUnregisterPolicyChangeNot: Pointer;

function LsaUnregisterPolicyChangeNotification;
begin
  GetProcedureAddress(_LsaUnregisterPolicyChangeNot, secur32, 'LsaUnregisterPolicyChangeNotification');
  asm
    mov esp, ebp
    pop ebp
    jmp [_LsaUnregisterPolicyChangeNot]
  end;
end;
{$ELSE}
function LsaUnregisterPolicyChangeNotification; external secur32 name 'LsaUnregisterPolicyChangeNotification';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _LsaEnumerateTrustedDomains: Pointer;

function LsaEnumerateTrustedDomains;
begin
  GetProcedureAddress(_LsaEnumerateTrustedDomains, advapi32, 'LsaEnumerateTrustedDomains');
  asm
    mov esp, ebp
    pop ebp
    jmp [_LsaEnumerateTrustedDomains]
  end;
end;
{$ELSE}
function LsaEnumerateTrustedDomains; external advapi32 name 'LsaEnumerateTrustedDomains';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _LsaLookupNames: Pointer;

function LsaLookupNames;
begin
  GetProcedureAddress(_LsaLookupNames, advapi32, 'LsaLookupNames');
  asm
    mov esp, ebp
    pop ebp
    jmp [_LsaLookupNames]
  end;
end;
{$ELSE}
function LsaLookupNames; external advapi32 name 'LsaLookupNames';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _LsaLookupNames2: Pointer;

function LsaLookupNames2;
begin
  GetProcedureAddress(_LsaLookupNames2, advapi32, 'LsaLookupNames2');
  asm
    mov esp, ebp
    pop ebp
    jmp [_LsaLookupNames2]
  end;
end;
{$ELSE}
function LsaLookupNames2; external advapi32 name 'LsaLookupNames2';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _LsaLookupSids: Pointer;

function LsaLookupSids;
begin
  GetProcedureAddress(_LsaLookupSids, advapi32, 'LsaLookupSids');
  asm
    mov esp, ebp
    pop ebp
    jmp [_LsaLookupSids]
  end;
end;
{$ELSE}
function LsaLookupSids; external advapi32 name 'LsaLookupSids';
{$ENDIF DYNAMIC_LINK}


{$IFDEF DYNAMIC_LINK}
var
  _LsaEnumAccountsWithUserRight: Pointer;

function LsaEnumerateAccountsWithUserRight;
begin
  GetProcedureAddress(_LsaEnumAccountsWithUserRight, advapi32, 'LsaEnumerateAccountsWithUserRight');
  asm
    mov esp, ebp
    pop ebp
    jmp [_LsaEnumAccountsWithUserRight]
  end;
end;
{$ELSE}
function LsaEnumerateAccountsWithUserRight; external advapi32 name 'LsaEnumerateAccountsWithUserRight';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _LsaEnumerateAccountRights: Pointer;

function LsaEnumerateAccountRights;
begin
  GetProcedureAddress(_LsaEnumerateAccountRights, advapi32, 'LsaEnumerateAccountRights');
  asm
    mov esp, ebp
    pop ebp
    jmp [_LsaEnumerateAccountRights]
  end;
end;
{$ELSE}
function LsaEnumerateAccountRights; external advapi32 name 'LsaEnumerateAccountRights';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _LsaAddAccountRights: Pointer;

function LsaAddAccountRights;
begin
  GetProcedureAddress(_LsaAddAccountRights, advapi32, 'LsaAddAccountRights');
  asm
    mov esp, ebp
    pop ebp
    jmp [_LsaAddAccountRights]
  end;
end;
{$ELSE}
function LsaAddAccountRights; external advapi32 name 'LsaAddAccountRights';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _LsaRemoveAccountRights: Pointer;

function LsaRemoveAccountRights;
begin
  GetProcedureAddress(_LsaRemoveAccountRights, advapi32, 'LsaRemoveAccountRights');
  asm
    mov esp, ebp
    pop ebp
    jmp [_LsaRemoveAccountRights]
  end;
end;
{$ELSE}
function LsaRemoveAccountRights; external advapi32 name 'LsaRemoveAccountRights';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _LsaOpenTrustedDomainByName: Pointer;

function LsaOpenTrustedDomainByName;
begin
  GetProcedureAddress(_LsaOpenTrustedDomainByName, advapi32, 'LsaOpenTrustedDomainByName');
  asm
    mov esp, ebp
    pop ebp
    jmp [_LsaOpenTrustedDomainByName]
  end;
end;
{$ELSE}
function LsaOpenTrustedDomainByName; external advapi32 name 'LsaOpenTrustedDomainByName';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _LsaQueryTrustedDomainInfo: Pointer;

function LsaQueryTrustedDomainInfo;
begin
  GetProcedureAddress(_LsaQueryTrustedDomainInfo, advapi32, 'LsaQueryTrustedDomainInfo');
  asm
    mov esp, ebp
    pop ebp
    jmp [_LsaQueryTrustedDomainInfo]
  end;
end;
{$ELSE}
function LsaQueryTrustedDomainInfo; external advapi32 name 'LsaQueryTrustedDomainInfo';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _LsaSetTrustedDomainInformation: Pointer;

function LsaSetTrustedDomainInformation;
begin
  GetProcedureAddress(_LsaSetTrustedDomainInformation, advapi32, 'LsaSetTrustedDomainInformation');
  asm
    mov esp, ebp
    pop ebp
    jmp [_LsaSetTrustedDomainInformation]
  end;
end;
{$ELSE}
function LsaSetTrustedDomainInformation; external advapi32 name 'LsaSetTrustedDomainInformation';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _LsaDeleteTrustedDomain: Pointer;

function LsaDeleteTrustedDomain;
begin
  GetProcedureAddress(_LsaDeleteTrustedDomain, advapi32, 'LsaDeleteTrustedDomain');
  asm
    mov esp, ebp
    pop ebp
    jmp [_LsaDeleteTrustedDomain]
  end;
end;
{$ELSE}
function LsaDeleteTrustedDomain; external advapi32 name 'LsaDeleteTrustedDomain';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _LsaQueryTrustedDomainInfoByName: Pointer;

function LsaQueryTrustedDomainInfoByName;
begin
  GetProcedureAddress(_LsaQueryTrustedDomainInfoByName, advapi32, 'LsaQueryTrustedDomainInfoByName');
  asm
    mov esp, ebp
    pop ebp
    jmp [_LsaQueryTrustedDomainInfoByName]
  end;
end;
{$ELSE}
function LsaQueryTrustedDomainInfoByName; external advapi32 name 'LsaQueryTrustedDomainInfoByName';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _LsaSetTrustedDomainInfoByName: Pointer;

function LsaSetTrustedDomainInfoByName;
begin
  GetProcedureAddress(_LsaSetTrustedDomainInfoByName, advapi32, 'LsaSetTrustedDomainInfoByName');
  asm
    mov esp, ebp
    pop ebp
    jmp [_LsaSetTrustedDomainInfoByName]
  end;
end;
{$ELSE}
function LsaSetTrustedDomainInfoByName; external advapi32 name 'LsaSetTrustedDomainInfoByName';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _LsaEnumerateTrustedDomainsEx: Pointer;

function LsaEnumerateTrustedDomainsEx;
begin
  GetProcedureAddress(_LsaEnumerateTrustedDomainsEx, advapi32, 'LsaEnumerateTrustedDomainsEx');
  asm
    mov esp, ebp
    pop ebp
    jmp [_LsaEnumerateTrustedDomainsEx]
  end;
end;
{$ELSE}
function LsaEnumerateTrustedDomainsEx; external advapi32 name 'LsaEnumerateTrustedDomainsEx';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _LsaCreateTrustedDomainEx: Pointer;

function LsaCreateTrustedDomainEx;
begin
  GetProcedureAddress(_LsaCreateTrustedDomainEx, advapi32, 'LsaCreateTrustedDomainEx');
  asm
    mov esp, ebp
    pop ebp
    jmp [_LsaCreateTrustedDomainEx]
  end;
end;
{$ELSE}
function LsaCreateTrustedDomainEx; external advapi32 name 'LsaCreateTrustedDomainEx';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _LsaQueryForestTrustInformation: Pointer;

function LsaQueryForestTrustInformation;
begin
  GetProcedureAddress(_LsaQueryForestTrustInformation, advapi32, 'LsaQueryForestTrustInformation');
  asm
    mov esp, ebp
    pop ebp
    jmp [_LsaQueryForestTrustInformation]
  end;
end;
{$ELSE}
function LsaQueryForestTrustInformation; external advapi32 name 'LsaQueryForestTrustInformation';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _LsaSetForestTrustInformation: Pointer;

function LsaSetForestTrustInformation;
begin
  GetProcedureAddress(_LsaSetForestTrustInformation, advapi32, 'LsaSetForestTrustInformation');
  asm
    mov esp, ebp
    pop ebp
    jmp [_LsaSetForestTrustInformation]
  end;
end;
{$ELSE}
function LsaSetForestTrustInformation; external advapi32 name 'LsaSetForestTrustInformation';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _LsaStorePrivateData: Pointer;

function LsaStorePrivateData;
begin
  GetProcedureAddress(_LsaStorePrivateData, advapi32, 'LsaStorePrivateData');
  asm
    mov esp, ebp
    pop ebp
    jmp [_LsaStorePrivateData]
  end;
end;
{$ELSE}
function LsaStorePrivateData; external advapi32 name 'LsaStorePrivateData';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _LsaRetrievePrivateData: Pointer;

function LsaRetrievePrivateData;
begin
  GetProcedureAddress(_LsaRetrievePrivateData, advapi32, 'LsaRetrievePrivateData');
  asm
    mov esp, ebp
    pop ebp
    jmp [_LsaRetrievePrivateData]
  end;
end;
{$ELSE}
function LsaRetrievePrivateData; external advapi32 name 'LsaRetrievePrivateData';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _LsaNtStatusToWinError: Pointer;

function LsaNtStatusToWinError;
begin
  GetProcedureAddress(_LsaNtStatusToWinError, advapi32, 'LsaNtStatusToWinError');
  asm
    mov esp, ebp
    pop ebp
    jmp [_LsaNtStatusToWinError]
  end;
end;
{$ELSE}
function LsaNtStatusToWinError; external advapi32 name 'LsaNtStatusToWinError';
{$ENDIF DYNAMIC_LINK}

end.
