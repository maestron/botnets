{******************************************************************************}
{                                                       	               }
{ DC and Replication Management API interface Unit for Object Pascal           }
{                                                       	               }
{ Portions created by Microsoft are Copyright (C) 1995-2001 Microsoft          }
{ Corporation. All Rights Reserved.                                            }
{ 								               }
{ The original file is: ntdsapi.h, released June 2000. The original Pascal     }
{ code is: NtDsApi.pas, released December 2000. The initial developer of the   }
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

unit JwaNtDsApi;

{$WEAKPACKAGEUNIT}

{$HPPEMIT ''}
{$HPPEMIT '#include "ntdsapi.h"'}
{$HPPEMIT ''}
{$HPPEMIT 'typedef PDS_REPSYNCALL_ERRINFOW *PPDS_REPSYNCALL_ERRINFOW'}
{$HPPEMIT 'typedef PDS_REPSYNCALL_ERRINFOA *PPDS_REPSYNCALL_ERRINFOA'}
{$HPPEMIT '#ifdef UNICODE'}
{$HPPEMIT 'typedef PPDS_REPSYNCALL_ERRINFOW PPDS_REPSYNCALL_ERRINFO'}
{$HPPEMIT '#else'}
{$HPPEMIT 'typedef PPDS_REPSYNCALL_ERRINFOA PPDS_REPSYNCALL_ERRINFO'}
{$HPPEMIT '#endif'}
{$HPPEMIT ''}

{$I WINDEFINES.INC}

interface

uses
  JwaWinBase, JwaWinType, JwaWinNT, JwaWinNLS, JwaRpcDce, JwaSchedule;

//////////////////////////////////////////////////////////////////////////
//                                                                      //
// Data definitions                                                     //
//                                                                      //
//////////////////////////////////////////////////////////////////////////

// Following constants define the Active Directory Behavior
// Version numbers.

const
  DS_BEHAVIOR_WIN2000                          = 0;
  {$EXTERNALSYM DS_BEHAVIOR_WIN2000}
  DS_BEHAVIOR_WIN_DOT_NET_WITH_MIXED_DOMAINS   = 1;
  {$EXTERNALSYM DS_BEHAVIOR_WIN_DOT_NET_WITH_MIXED_DOMAINS}
  DS_BEHAVIOR_WIN_DOT_NET                      = 2;
  {$EXTERNALSYM DS_BEHAVIOR_WIN_DOT_NET}

  // (MAKELCID(MAKELANGID(LANG_ENGLISH, SUBLANG_ENGLISH_US), SORT_DEFAULT))
  DS_DEFAULT_LOCALE = DWORD((DWORD(SORT_DEFAULT) shl 16) or ((SUBLANG_ENGLISH_US shl 10) or LANG_ENGLISH));
  {$EXTERNALSYM DS_DEFAULT_LOCALE}

  DS_DEFAULT_LOCALE_COMPARE_FLAGS = (NORM_IGNORECASE or NORM_IGNOREKANATYPE or
    NORM_IGNORENONSPACE or NORM_IGNOREWIDTH or SORT_STRINGSORT);
  {$EXTERNALSYM DS_DEFAULT_LOCALE_COMPARE_FLAGS}

// When booted to DS mode, this event is signalled when the DS has completed
// its initial sync attempts.  The period of time between system startup and
// this event's state being set is indeterminate from the local service's
// standpoint.  In the meantime the contents of the DS should be considered
// incomplete / out-dated, and the machine will not be advertised as a domain
// controller to off-machine clients.  Other local services that rely on
// information published in the DS should avoid accessing (or at least
// relying on) the contents of the DS until this event is set.

  DS_SYNCED_EVENT_NAME   = 'NTDSInitialSyncsCompleted';
  {$EXTERNALSYM DS_SYNCED_EVENT_NAME}
  DS_SYNCED_EVENT_NAME_W = 'NTDSInitialSyncsCompleted';
  {$EXTERNALSYM DS_SYNCED_EVENT_NAME_W}

// Permissions bits used in security descriptors in the directory.

  ACTRL_DS_OPEN           = $00000000;
  {$EXTERNALSYM ACTRL_DS_OPEN}
  ACTRL_DS_CREATE_CHILD   = $00000001;
  {$EXTERNALSYM ACTRL_DS_CREATE_CHILD}
  ACTRL_DS_DELETE_CHILD   = $00000002;
  {$EXTERNALSYM ACTRL_DS_DELETE_CHILD}
  ACTRL_DS_LIST           = $00000004;
  {$EXTERNALSYM ACTRL_DS_LIST}
  ACTRL_DS_SELF           = $00000008;
  {$EXTERNALSYM ACTRL_DS_SELF}
  ACTRL_DS_READ_PROP      = $00000010;
  {$EXTERNALSYM ACTRL_DS_READ_PROP}
  ACTRL_DS_WRITE_PROP     = $00000020;
  {$EXTERNALSYM ACTRL_DS_WRITE_PROP}
  ACTRL_DS_DELETE_TREE    = $00000040;
  {$EXTERNALSYM ACTRL_DS_DELETE_TREE}
  ACTRL_DS_LIST_OBJECT    = $00000080;
  {$EXTERNALSYM ACTRL_DS_LIST_OBJECT}
  ACTRL_DS_CONTROL_ACCESS = $00000100;
  {$EXTERNALSYM ACTRL_DS_CONTROL_ACCESS}

// generic read

  DS_GENERIC_READ = STANDARD_RIGHTS_READ or ACTRL_DS_LIST or ACTRL_DS_READ_PROP or
    ACTRL_DS_LIST_OBJECT;
  {$EXTERNALSYM DS_GENERIC_READ}

// generic execute

  DS_GENERIC_EXECUTE = ((STANDARD_RIGHTS_EXECUTE) or (ACTRL_DS_LIST));
  {$EXTERNALSYM DS_GENERIC_EXECUTE}

// generic right

  DS_GENERIC_WRITE = ((STANDARD_RIGHTS_WRITE) or (ACTRL_DS_SELF) or
    (ACTRL_DS_WRITE_PROP));
  {$EXTERNALSYM DS_GENERIC_WRITE}

// generic all

  DS_GENERIC_ALL = ((STANDARD_RIGHTS_REQUIRED) or (ACTRL_DS_CREATE_CHILD) or
    (ACTRL_DS_DELETE_CHILD) or (ACTRL_DS_DELETE_TREE) or (ACTRL_DS_READ_PROP) or
    (ACTRL_DS_WRITE_PROP) or (ACTRL_DS_LIST) or (ACTRL_DS_LIST_OBJECT) or
    (ACTRL_DS_CONTROL_ACCESS) or (ACTRL_DS_SELF));
  {$EXTERNALSYM DS_GENERIC_ALL}

type
  DS_NAME_FORMAT = (
    // unknown name type
    DS_UNKNOWN_NAME,

    // eg: CN=User Name,OU=Users,DC=Example,DC=Microsoft,DC=Com
    DS_FQDN_1779_NAME,

    // eg: Exmaple\UserName
    // Domain-only version includes trailing '\\'.
    DS_NT4_ACCOUNT_NAME,

    // Probably "User Name" but could be something else.  I.e. The
    // display name is not necessarily the defining RDN.
    DS_DISPLAY_NAME,

    // obsolete - see #define later
    // DS_DOMAIN_SIMPLE_NAME,
    DS_STUB_4,

    // obsolete - see #define later
    // DS_ENTERPRISE_SIMPLE_NAME,
    DS_STUB_5,

    // String-ized GUID as returned by IIDFromString().
    // eg: {4fa050f0-f561-11cf-bdd9-00aa003a77b6}
    DS_UNIQUE_ID_NAME,

    // eg: example.microsoft.com/software/user name
    // Domain-only version includes trailing '/'.
    DS_CANONICAL_NAME,

    // eg: usern@example.microsoft.com
    DS_USER_PRINCIPAL_NAME,

    // Same as DS_CANONICAL_NAME except that rightmost '/' is
    // replaced with '\n' - even in domain-only case.
    // eg: example.microsoft.com/software\nuser name
    DS_CANONICAL_NAME_EX,

    // eg: www/www.microsoft.com@example.com - generalized service principal
    // names.
    DS_SERVICE_PRINCIPAL_NAME,

    // This is the string representation of a SID.  Invalid for formatDesired.
    // See sddl.h for SID binary <--> text conversion routines.
    // eg: S-1-5-21-397955417-626881126-188441444-501
    DS_SID_OR_SID_HISTORY_NAME,

    // Pseudo-name format so GetUserNameEx can return the DNS domain name to
    // a caller.  This level is not supported by the DS APIs.
    DS_DNS_DOMAIN_NAME);
  {$EXTERNALSYM DS_NAME_FORMAT}
  TDsNameFormat = DS_NAME_FORMAT;

// Map old name formats to closest new format so that old code builds
// against new headers w/o errors and still gets (almost) correct result.

const
  DS_DOMAIN_SIMPLE_NAME     = DS_USER_PRINCIPAL_NAME;
  {$EXTERNALSYM DS_DOMAIN_SIMPLE_NAME}
  DS_ENTERPRISE_SIMPLE_NAME = DS_USER_PRINCIPAL_NAME;
  {$EXTERNALSYM DS_ENTERPRISE_SIMPLE_NAME}

type
  DS_NAME_FLAGS = DWORD;
  {$EXTERNALSYM DS_NAME_FLAGS}
  TDsNameFlags = DS_NAME_FLAGS;

const
    DS_NAME_NO_FLAGS = $0;
    {$EXTERNALSYM DS_NAME_NO_FLAGS}

    // Perform a syntactical mapping at the client (if possible) without
    // going out on the wire.  Returns DS_NAME_ERROR_NO_SYNTACTICAL_MAPPING
    // if a purely syntactical mapping is not possible.
    DS_NAME_FLAG_SYNTACTICAL_ONLY = $1;
    {$EXTERNALSYM DS_NAME_FLAG_SYNTACTICAL_ONLY}

    // Force a trip to the DC for evaluation, even if this could be
    // locally cracked syntactically.
    DS_NAME_FLAG_EVAL_AT_DC = $2;
    {$EXTERNALSYM DS_NAME_FLAG_EVAL_AT_DC}

    // The call fails if the DC is not a GC
    DS_NAME_FLAG_GCVERIFY = $4;
    {$EXTERNALSYM DS_NAME_FLAG_GCVERIFY}

    // Enable cross forest trust referral
    DS_NAME_FLAG_TRUST_REFERRAL = $8;
    {$EXTERNALSYM DS_NAME_FLAG_TRUST_REFERRAL}

type
  DS_NAME_ERROR = (
    DS_NAME_NO_ERROR,

    // Generic processing error.
    DS_NAME_ERROR_RESOLVING,

    // Couldn't find the name at all - or perhaps caller doesn't have
    // rights to see it.
    DS_NAME_ERROR_NOT_FOUND,

    // Input name mapped to more than one output name.
    DS_NAME_ERROR_NOT_UNIQUE,

    // Input name found, but not the associated output format.
    // Can happen if object doesn't have all the required attributes.
    DS_NAME_ERROR_NO_MAPPING,

    // Unable to resolve entire name, but was able to determine which
    // domain object resides in.  Thus DS_NAME_RESULT_ITEM?.pDomain
    // is valid on return.
    DS_NAME_ERROR_DOMAIN_ONLY,

    // Unable to perform a purely syntactical mapping at the client
    // without going out on the wire.
    DS_NAME_ERROR_NO_SYNTACTICAL_MAPPING,

    // The name is from an external trusted forest.
    DS_NAME_ERROR_TRUST_REFERRAL);
  {$EXTERNALSYM DS_NAME_ERROR}
  TDsNameError = DS_NAME_ERROR;

const
  DS_NAME_LEGAL_FLAGS = (DS_NAME_FLAG_SYNTACTICAL_ONLY);
  {$EXTERNALSYM DS_NAME_LEGAL_FLAGS}

type
  DS_SPN_NAME_TYPE = (

    // "paulle-nec.ntwksta.ms.com"
    DS_SPN_DNS_HOST,

    // "cn=paulle-nec,ou=computers,dc=ntwksta,dc=ms,dc=com"
    DS_SPN_DN_HOST,

    // "paulle-nec"
    DS_SPN_NB_HOST,

    // "ntdev.ms.com"
    DS_SPN_DOMAIN,

    // "ntdev"
    DS_SPN_NB_DOMAIN,

    // "cn=anRpcService,cn=RPC Services,cn=system,dc=ms,dc=com"
    // "cn=aWsService,cn=Winsock Services,cn=system,dc=ms,dc=com"
    // "cn=aService,dc=itg,dc=ms,dc=com"
    // "www.ms.com", "ftp.ms.com", "ldap.ms.com"
    // "products.ms.com"
    DS_SPN_SERVICE);
  {$EXTERNALSYM DS_SPN_NAME_TYPE}
  TDsSpnNameType = DS_SPN_NAME_TYPE;

  DS_SPN_WRITE_OP = (
        DS_SPN_ADD_SPN_OP,          // add SPNs
        DS_SPN_REPLACE_SPN_OP,      // set all SPNs
        DS_SPN_DELETE_SPN_OP);      // Delete SPNs
  {$EXTERNALSYM DS_SPN_WRITE_OP}
  TDsSpnWriteOp = DS_SPN_WRITE_OP;

  PDS_NAME_RESULT_ITEMA = ^DS_NAME_RESULT_ITEMA;
  {$EXTERNALSYM PDS_NAME_RESULT_ITEMA}
  DS_NAME_RESULT_ITEMA = record
    status: DWORD;  // DS_NAME_ERROR
    pDomain: LPSTR; // DNS domain
    pName: LPSTR;   // name in requested format
  end;
  {$EXTERNALSYM DS_NAME_RESULT_ITEMA}
  TDsNameResultItemA = DS_NAME_RESULT_ITEMA;
  PDsNameResultItemA = PDS_NAME_RESULT_ITEMA;

  PDS_NAME_RESULTA = ^DS_NAME_RESULTA;
  {$EXTERNALSYM PDS_NAME_RESULTA}
  DS_NAME_RESULTA = record
    cItems: DWORD;                 // item count
    rItems: PDS_NAME_RESULT_ITEMA; // item array
  end;
  {$EXTERNALSYM DS_NAME_RESULTA}
  TDsNameResultA = DS_NAME_RESULTA;
  PDsNameResultA = PDS_NAME_RESULTA;

  PDS_NAME_RESULT_ITEMW = ^DS_NAME_RESULT_ITEMW;
  {$EXTERNALSYM PDS_NAME_RESULT_ITEMW}
  DS_NAME_RESULT_ITEMW = record
    status: DWORD;   // DS_NAME_ERROR
    pDomain: LPWSTR; // DNS domain
    pName: LPWSTR;   // name in requested format
  end;
  {$EXTERNALSYM DS_NAME_RESULT_ITEMW}
  TDsNameResultItemW = DS_NAME_RESULT_ITEMW;
  PDsNameResultItemW = PDS_NAME_RESULT_ITEMW;

  PDS_NAME_RESULTW = ^DS_NAME_RESULTW;
  {$EXTERNALSYM PDS_NAME_RESULTW}
  DS_NAME_RESULTW = record
    cItems: DWORD;                 // item count
    rItems: PDS_NAME_RESULT_ITEMW; // item array
  end;
  {$EXTERNALSYM DS_NAME_RESULTW}
  TDsNameResultW = DS_NAME_RESULTW;
  PDsNameResultW = PDS_NAME_RESULTW;

{$IFDEF UNICODE}
  DS_NAME_RESULT = DS_NAME_RESULTW;
  {$EXTERNALSYM DS_NAME_RESULT}
  PDS_NAME_RESULT = PDS_NAME_RESULTW;
  {$EXTERNALSYM PDS_NAME_RESULT}
  DS_NAME_RESULT_ITEM = DS_NAME_RESULT_ITEMW;
  {$EXTERNALSYM DS_NAME_RESULT_ITEM}
  PDS_NAME_RESULT_ITEM = PDS_NAME_RESULT_ITEMW;
  {$EXTERNALSYM PDS_NAME_RESULT_ITEM}
  TDsNameResult = TDsNameResultW;
  PDsNameResult = PDsNameResultW;
  TDsNameResultItem = TDsNameResultItemW;
  PDsNameResultItem = PDsNameResultItemW;
{$ELSE}
  DS_NAME_RESULT = DS_NAME_RESULTA;
  {$EXTERNALSYM DS_NAME_RESULT}
  PDS_NAME_RESULT = PDS_NAME_RESULTA;
  {$EXTERNALSYM PDS_NAME_RESULT}
  DS_NAME_RESULT_ITEM = DS_NAME_RESULT_ITEMA;
  {$EXTERNALSYM DS_NAME_RESULT_ITEM}
  PDS_NAME_RESULT_ITEM = PDS_NAME_RESULT_ITEMA;
  {$EXTERNALSYM PDS_NAME_RESULT_ITEM}
  TDsNameResult = TDsNameResultA;
  PDsNameResult = PDsNameResultA;
  TDsNameResultItem = TDsNameResultItemA;
  PDsNameResultItem = PDsNameResultItemA;
{$ENDIF}

// Public replication option flags

// ********************
// DsBindWithSpnEx flags
// ********************
// Allow the Bind to use delegate service level, so that you can
// do ntdsapi operations that require delegation, such as
// DsAddSidHistory, and DsReplicaSyncAll().  Most operations do
// not require DELEGATE so this flag should only be specified 
// if you need it, because if you bind to a rogue server with
// the DELEGATE flag, you'll allow the rogue server to use your
// credentials to connect back to a non-rogue server and perform
// operations other than you intended.

const
  NTDSAPI_BIND_ALLOW_DELEGATION	= ($00000001);
  {$EXTERNALSYM NTDSAPI_BIND_ALLOW_DELEGATION}

// ********************
// Replica Sync flags
// These flag values are used both as input to DsReplicaSync and
// as output from DsReplicaGetInfo, PENDING_OPS, DS_REPL_OPW.ulOptions
// ********************

// Perform this operation asynchronously.
// Required when using DS_REPSYNC_ALL_SOURCES

const
  DS_REPSYNC_ASYNCHRONOUS_OPERATION = $00000001;
  {$EXTERNALSYM DS_REPSYNC_ASYNCHRONOUS_OPERATION}

// Writeable replica.  Otherwise, read-only.

  DS_REPSYNC_WRITEABLE = $00000002;
  {$EXTERNALSYM DS_REPSYNC_WRITEABLE}

// This is a periodic sync request as scheduled by the admin.

  DS_REPSYNC_PERIODIC = $00000004;
  {$EXTERNALSYM DS_REPSYNC_PERIODIC}

// Use inter-site messaging

  DS_REPSYNC_INTERSITE_MESSAGING = $00000008;
  {$EXTERNALSYM DS_REPSYNC_INTERSITE_MESSAGING}

// Sync from all sources.

  DS_REPSYNC_ALL_SOURCES = $00000010;
  {$EXTERNALSYM DS_REPSYNC_ALL_SOURCES}

// Sync starting from scratch (i.e., at the first USN).

  DS_REPSYNC_FULL = $00000020;
  {$EXTERNALSYM DS_REPSYNC_FULL}

// This is a notification of an update that was marked urgent.

  DS_REPSYNC_URGENT = $00000040;
  {$EXTERNALSYM DS_REPSYNC_URGENT}

// Don't discard this synchronization request, even if a similar
// sync is pending.

  DS_REPSYNC_NO_DISCARD = $00000080;
  {$EXTERNALSYM DS_REPSYNC_NO_DISCARD}

// Sync even if link is currently disabled.

  DS_REPSYNC_FORCE = $00000100;
  {$EXTERNALSYM DS_REPSYNC_FORCE}

// Causes the source DSA to check if a reps-to is present for the local DSA
// (aka the destination). If not, one is added.  This ensures that
// source sends change notifications.

  DS_REPSYNC_ADD_REFERENCE = $00000200;
  {$EXTERNALSYM DS_REPSYNC_ADD_REFERENCE}

// A sync from this source has never completed (e.g., a new source).

  DS_REPSYNC_NEVER_COMPLETED = $00000400;
  {$EXTERNALSYM DS_REPSYNC_NEVER_COMPLETED}

// When this sync is complete, requests a sync in the opposite direction.

  DS_REPSYNC_TWO_WAY = $00000800;
  {$EXTERNALSYM DS_REPSYNC_TWO_WAY}

// Do not request change notifications from this source.
  DS_REPSYNC_NEVER_NOTIFY          = $00001000;
  {$EXTERNALSYM DS_REPSYNC_NEVER_NOTIFY}

// Sync the NC from this source when the DSA is started.
  DS_REPSYNC_INITIAL                = $00002000;
  {$EXTERNALSYM DS_REPSYNC_INITIAL}

// Use compression when replicating.  Saves message size (e.g., network
// bandwidth) at the expense of extra CPU overhead at both the source and
// destination servers.
  DS_REPSYNC_USE_COMPRESSION        = $00004000;
  {$EXTERNALSYM DS_REPSYNC_USE_COMPRESSION}

// Sync was abandoned for lack of updates
  DS_REPSYNC_ABANDONED              = $00008000;
  {$EXTERNALSYM DS_REPSYNC_ABANDONED}

// Initial sync in progress
  DS_REPSYNC_INITIAL_IN_PROGRESS    = $00010000;
  {$EXTERNALSYM DS_REPSYNC_INITIAL_IN_PROGRESS}

// Partial Attribute Set sync in progress
  DS_REPSYNC_PARTIAL_ATTRIBUTE_SET  = $00020000;
  {$EXTERNALSYM DS_REPSYNC_PARTIAL_ATTRIBUTE_SET}

// Sync is being retried
  DS_REPSYNC_REQUEUE                = $00040000;
  {$EXTERNALSYM DS_REPSYNC_REQUEUE}

// Sync is a notification request from a source
  DS_REPSYNC_NOTIFICATION           = $00080000;
  {$EXTERNALSYM DS_REPSYNC_NOTIFICATION}

// Sync is a special form which requests to establish contact
// now and do the rest of the sync later
  DS_REPSYNC_ASYNCHRONOUS_REPLICA   = $00100000;
  {$EXTERNALSYM DS_REPSYNC_ASYNCHRONOUS_REPLICA}

// Request critical objects only
  DS_REPSYNC_CRITICAL               = $00200000;
  {$EXTERNALSYM DS_REPSYNC_CRITICAL}

// A full synchronization is in progress
  DS_REPSYNC_FULL_IN_PROGRESS       = $00400000;
  {$EXTERNALSYM DS_REPSYNC_FULL_IN_PROGRESS}

// Synchronization request was previously preempted
  DS_REPSYNC_PREEMPTED              = $00800000;
  {$EXTERNALSYM DS_REPSYNC_PREEMPTED}

// ********************
// Replica Add flags
// ********************

// Perform this operation asynchronously.

  DS_REPADD_ASYNCHRONOUS_OPERATION = $00000001;
  {$EXTERNALSYM DS_REPADD_ASYNCHRONOUS_OPERATION}

// Create a writeable replica.  Otherwise, read-only.

  DS_REPADD_WRITEABLE = $00000002;
  {$EXTERNALSYM DS_REPADD_WRITEABLE}

// Sync the NC from this source when the DSA is started.

  DS_REPADD_INITIAL = $00000004;
  {$EXTERNALSYM DS_REPADD_INITIAL}

// Sync the NC from this source periodically, as defined by the
// schedule passed in the preptimesSync argument.

  DS_REPADD_PERIODIC = $00000008;
  {$EXTERNALSYM DS_REPADD_PERIODIC}

// Sync from the source DSA via an Intersite Messaging Service (ISM) transport
// (e.g., SMTP) rather than native DS RPC.

  DS_REPADD_INTERSITE_MESSAGING = $00000010;
  {$EXTERNALSYM DS_REPADD_INTERSITE_MESSAGING}

// Don't replicate the NC now -- just save enough state such that we
// know to replicate it later.

  DS_REPADD_ASYNCHRONOUS_REPLICA = $00000020;
  {$EXTERNALSYM DS_REPADD_ASYNCHRONOUS_REPLICA}

// Disable notification-based synchronization for the NC from this source.
// This is expected to be a temporary state; the similar flag
// DS_REPADD_NEVER_NOTIFY should be used if the disable is to be more permanent.

  DS_REPADD_DISABLE_NOTIFICATION = $00000040;
  {$EXTERNALSYM DS_REPADD_DISABLE_NOTIFICATION}

// Disable periodic synchronization for the NC from this source

  DS_REPADD_DISABLE_PERIODIC = $00000080;
  {$EXTERNALSYM DS_REPADD_DISABLE_PERIODIC}

// Use compression when replicating.  Saves message size (e.g., network
// bandwidth) at the expense of extra CPU overhead at both the source and
// destination servers.

  DS_REPADD_USE_COMPRESSION = $00000100;
  {$EXTERNALSYM DS_REPADD_USE_COMPRESSION}

// Do not request change notifications from this source.  When this flag is
// set, the source will not notify the destination when changes occur.
// Recommended for all intersite replication, which may occur over WAN links.
// This is expected to be a more or less permanent state; the similar flag
// DS_REPADD_DISABLE_NOTIFICATION should be used if notifications are to be
// disabled only temporarily.

  DS_REPADD_NEVER_NOTIFY = $00000200;
  {$EXTERNALSYM DS_REPADD_NEVER_NOTIFY}

// When this sync is complete, requests a sync in the opposite direction.
  DS_REPADD_TWO_WAY                  = $00000400;
  {$EXTERNALSYM DS_REPADD_TWO_WAY}

// Request critical objects only
// Critical only is only allowed while installing
// A critical only sync does not bring all objects in the partition. It
// replicates just the ones necessary for minimal directory operation.
// A normal, non-critical sync must be performed before the partition
// can be considered fully synchronized.
  DS_REPADD_CRITICAL                 = $00000800;
  {$EXTERNALSYM DS_REPADD_CRITICAL}

// ********************
// Replica Delete flags
// ********************

// Perform this operation asynchronously.

  DS_REPDEL_ASYNCHRONOUS_OPERATION = $00000001;
  {$EXTERNALSYM DS_REPDEL_ASYNCHRONOUS_OPERATION}

// The replica being deleted is writeable.

  DS_REPDEL_WRITEABLE = $00000002;
  {$EXTERNALSYM DS_REPDEL_WRITEABLE}

// Replica is a mail-based replica

  DS_REPDEL_INTERSITE_MESSAGING = $00000004;
  {$EXTERNALSYM DS_REPDEL_INTERSITE_MESSAGING}

// Ignore any error generated by contacting the source to tell it to scratch
// this server from its Reps-To for this NC.

  DS_REPDEL_IGNORE_ERRORS = $00000008;
  {$EXTERNALSYM DS_REPDEL_IGNORE_ERRORS}

// Do not contact the source telling it to scratch this server from its
// Rep-To for this NC.  Otherwise, if the link is RPC-based, the source will
// be contacted.

  DS_REPDEL_LOCAL_ONLY = $00000010;
  {$EXTERNALSYM DS_REPDEL_LOCAL_ONLY}

// Delete all the objects in the NC
// "No source" is incompatible with (and rejected for) writeable NCs.  This is
// valid only for read-only NCs, and then only if the NC has no source.  This
// can occur when the NC has been partially deleted (in which case the KCC
// periodically calls the delete API with the "no source" flag set).

  DS_REPDEL_NO_SOURCE = $00000020;
  {$EXTERNALSYM DS_REPDEL_NO_SOURCE}

// Allow deletion of read-only replica even if it sources
// other read-only replicas.

  DS_REPDEL_REF_OK = $00000040;
  {$EXTERNALSYM DS_REPDEL_REF_OK}

// ********************
// Replica Modify flags
// ********************

// Perform this operation asynchronously.

  DS_REPMOD_ASYNCHRONOUS_OPERATION = $00000001;
  {$EXTERNALSYM DS_REPMOD_ASYNCHRONOUS_OPERATION}

// The replica is writeable.

  DS_REPMOD_WRITEABLE = $00000002;
  {$EXTERNALSYM DS_REPMOD_WRITEABLE}

// ********************
// Replica Modify fields
// ********************

  DS_REPMOD_UPDATE_FLAGS     = $00000001;
  {$EXTERNALSYM DS_REPMOD_UPDATE_FLAGS}
  DS_REPMOD_UPDATE_ADDRESS   = $00000002;
  {$EXTERNALSYM DS_REPMOD_UPDATE_ADDRESS}
  DS_REPMOD_UPDATE_SCHEDULE  = $00000004;
  {$EXTERNALSYM DS_REPMOD_UPDATE_SCHEDULE}
  DS_REPMOD_UPDATE_RESULT    = $00000008;
  {$EXTERNALSYM DS_REPMOD_UPDATE_RESULT}
  DS_REPMOD_UPDATE_TRANSPORT = $00000010;
  {$EXTERNALSYM DS_REPMOD_UPDATE_TRANSPORT}

// ********************
// Update Refs fields
// ********************

// Perform this operation asynchronously.

  DS_REPUPD_ASYNCHRONOUS_OPERATION = $00000001;
  {$EXTERNALSYM DS_REPUPD_ASYNCHRONOUS_OPERATION}

// The replica being deleted is writeable.

  DS_REPUPD_WRITEABLE = $00000002;
  {$EXTERNALSYM DS_REPUPD_WRITEABLE}

// Add a reference

  DS_REPUPD_ADD_REFERENCE = $00000004;
  {$EXTERNALSYM DS_REPUPD_ADD_REFERENCE}

// Remove a reference

  DS_REPUPD_DELETE_REFERENCE = $00000008;
  {$EXTERNALSYM DS_REPUPD_DELETE_REFERENCE}

// ********************
//  NC Related Flags
// ********************
//
// Instance Type bits, specifies flags for NC head creation.
//

  DS_INSTANCETYPE_IS_NC_HEAD       = $00000001; // This if what to specify on an object to indicate it's an NC Head.
  {$EXTERNALSYM DS_INSTANCETYPE_IS_NC_HEAD}
  DS_INSTANCETYPE_NC_IS_WRITEABLE  = $00000004; // This is to indicate that the NC Head is writeable.
  {$EXTERNALSYM DS_INSTANCETYPE_NC_IS_WRITEABLE}
  DS_INSTANCETYPE_NC_COMING        = $00000010; // This is to indicate that this NC is still replicating in objects to this DC, and may not be a complete NC.
  {$EXTERNALSYM DS_INSTANCETYPE_NC_COMING}
  DS_INSTANCETYPE_NC_GOING         = $00000020; // This is to indicate that this NC is in the process of being removed from this DC, and may not be a complete NC.
  {$EXTERNALSYM DS_INSTANCETYPE_NC_GOING}

// ********************
//  xxx_OPT_xxx Flags
// ********************

// These macros define bit flags which can be set in the "options" attribute
// of objects of the specified object class.

// Bit flags valid for options attribute on NTDS-DSA objects.
//

  NTDSDSA_OPT_IS_GC                    = (1 shl 0); // DSA is a global catalog
  {$EXTERNALSYM NTDSDSA_OPT_IS_GC}
  NTDSDSA_OPT_DISABLE_INBOUND_REPL     = (1 shl 1); // disable inbound replication
  {$EXTERNALSYM NTDSDSA_OPT_DISABLE_INBOUND_REPL}
  NTDSDSA_OPT_DISABLE_OUTBOUND_REPL    = (1 shl 2); // disable outbound replication
  {$EXTERNALSYM NTDSDSA_OPT_DISABLE_OUTBOUND_REPL}
  NTDSDSA_OPT_DISABLE_NTDSCONN_XLATE   = (1 shl 3); // disable logical conn xlation
  {$EXTERNALSYM NTDSDSA_OPT_DISABLE_NTDSCONN_XLATE}


// Bit flags for options attribute on NTDS-Connection objects.
//
// The reasons that two bits are required to control notification are as follows.
// We must support existing connections with the old behavior and the UI does not
// create manual connections with the new bit set.
// The default for existing and manually created connections with bits 2 and 3
// clear must be the standard prior behavior: notification for intra-site and
// no notification for inter-site.
// We need a way to distinguish a old connection which desires the default
// notification rules, and a new connection for which we desire to explicitly
// control the notification state as passed down from a site link.  Thus we
// have a new bit to say we are overriding the default, and a new bit to indicate
// what the overridden default shall be.
//

  NTDSCONN_OPT_IS_GENERATED = (1 shl 0);  // object generated by DS, not admin
  {$EXTERNALSYM NTDSCONN_OPT_IS_GENERATED}
  NTDSCONN_OPT_TWOWAY_SYNC  = (1 shl 1);  // force sync in opposite direction at end of sync
  {$EXTERNALSYM NTDSCONN_OPT_TWOWAY_SYNC}
  NTDSCONN_OPT_OVERRIDE_NOTIFY_DEFAULT = (1 shl 2);  // Do not use defaults to determine notification
  {$EXTERNALSYM NTDSCONN_OPT_OVERRIDE_NOTIFY_DEFAULT}
  NTDSCONN_OPT_USE_NOTIFY   = (1 shl 3); // Does source notify destination
  {$EXTERNALSYM NTDSCONN_OPT_USE_NOTIFY}

// For intra-site connections, this bit has no meaning.
// For inter-site connections, this bit means:
//  0 - Compression of replication data enabled
//  1 - Compression of replication data disabled

  NTDSCONN_OPT_DISABLE_INTERSITE_COMPRESSION   = (1 shl 4);
  {$EXTERNALSYM NTDSCONN_OPT_DISABLE_INTERSITE_COMPRESSION}

// For connections whose IS_GENERATED bit is 0, this bit has no effect.
// For KCC-generated connections, this bit indicates that the schedule attribute
// is owned by the user and should not be touched by the KCC.

  NTDSCONN_OPT_USER_OWNED_SCHEDULE = (1 shl 5);
  {$EXTERNALSYM NTDSCONN_OPT_USER_OWNED_SCHEDULE}

//
// The high 4 bits of the options attribute are used by NTFRS to assign priority
// for inbound connections. Bit 31 is used to force FRS to ignore schedule during
// the initial sync. Bits 30 - 28 are used to specify a priority between 0-7.
//

  FRSCONN_PRIORITY_MASK		     = $70000000;
  {$EXTERNALSYM FRSCONN_PRIORITY_MASK}
  FRSCONN_MAX_PRIORITY		     = $8;
  {$EXTERNALSYM FRSCONN_MAX_PRIORITY}

  DSCONN_OPT_IGNORE_SCHEDULE_MASK = DWORD($80000000);
  {$EXTERNALSYM DSCONN_OPT_IGNORE_SCHEDULE_MASK}

function NTDSCONN_IGNORE_SCHEDULE(_options_: DWORD): DWORD;
{$EXTERNALSYM NTDSCONN_IGNORE_SCHEDULE}

function FRSCONN_GET_PRIORITY(_options_: DWORD): DWORD;
{$EXTERNALSYM FRSCONN_GET_PRIORITY}

// Bit flags for options attribute on NTDS-Site-Settings objects.
//

const
  NTDSSETTINGS_OPT_IS_AUTO_TOPOLOGY_DISABLED     = (1 shl 0); // automatic topology gen disabled
  {$EXTERNALSYM NTDSSETTINGS_OPT_IS_AUTO_TOPOLOGY_DISABLED}
  NTDSSETTINGS_OPT_IS_TOPL_CLEANUP_DISABLED      = (1 shl 1); // automatic topology cleanup disabled
  {$EXTERNALSYM NTDSSETTINGS_OPT_IS_TOPL_CLEANUP_DISABLED}
  NTDSSETTINGS_OPT_IS_TOPL_MIN_HOPS_DISABLED     = (1 shl 2); // automatic minimum hops topology disabled
  {$EXTERNALSYM NTDSSETTINGS_OPT_IS_TOPL_MIN_HOPS_DISABLED}
  NTDSSETTINGS_OPT_IS_TOPL_DETECT_STALE_DISABLED = (1 shl 3); // automatic stale server detection disabled
  {$EXTERNALSYM NTDSSETTINGS_OPT_IS_TOPL_DETECT_STALE_DISABLED}
  NTDSSETTINGS_OPT_IS_INTER_SITE_AUTO_TOPOLOGY_DISABLED = (1 shl 4); // automatic inter-site topology gen disabled
  {$EXTERNALSYM NTDSSETTINGS_OPT_IS_INTER_SITE_AUTO_TOPOLOGY_DISABLED}
  NTDSSETTINGS_OPT_IS_GROUP_CACHING_ENABLED      = (1 shl 5); // group memberships for users enabled
  {$EXTERNALSYM NTDSSETTINGS_OPT_IS_GROUP_CACHING_ENABLED}
  NTDSSETTINGS_OPT_FORCE_KCC_WHISTLER_BEHAVIOR   = (1 shl 6); // force KCC to operate in Whistler behavior mode
  {$EXTERNALSYM NTDSSETTINGS_OPT_FORCE_KCC_WHISTLER_BEHAVIOR}
  NTDSSETTINGS_OPT_FORCE_KCC_W2K_ELECTION        = (1 shl 7); // force KCC to use the Windows 2000 ISTG election algorithm
  {$EXTERNALSYM NTDSSETTINGS_OPT_FORCE_KCC_W2K_ELECTION}
  NTDSSETTINGS_OPT_IS_RAND_BH_SELECTION_DISABLED = (1 shl 8); // prevent the KCC from randomly picking a bridgehead when creating a connection
  {$EXTERNALSYM NTDSSETTINGS_OPT_IS_RAND_BH_SELECTION_DISABLED}
  NTDSSETTINGS_OPT_IS_SCHEDULE_HASHING_ENABLED   = (1 shl 9); // allow the KCC to use hashing when creating a replication schedule
  {$EXTERNALSYM NTDSSETTINGS_OPT_IS_SCHEDULE_HASHING_ENABLED}

// Bit flags for options attribute on Inter-Site-Transport objects
//
// Note, the sense of the flag should be such that the default state or
// behavior corresponds to the flag NOT being present. Put another way, the
// flag should state the OPPOSITE of the default
//
// default: schedules are significant

  NTDSTRANSPORT_OPT_IGNORE_SCHEDULES = (1 shl 0); // Schedules disabled
  {$EXTERNALSYM NTDSTRANSPORT_OPT_IGNORE_SCHEDULES}

// default: links transitive (bridges not required)

  NTDSTRANSPORT_OPT_BRIDGES_REQUIRED = (1 shl 1); // siteLink bridges are required
  {$EXTERNALSYM NTDSTRANSPORT_OPT_BRIDGES_REQUIRED}

// Bit flags for options attribute on site-Connection objects
//
// These are not realized in the DS, but are built up in the KCC

  NTDSSITECONN_OPT_USE_NOTIFY  = (1 shl 0); // Use notification on this link
  {$EXTERNALSYM NTDSSITECONN_OPT_USE_NOTIFY}
  NTDSSITECONN_OPT_TWOWAY_SYNC = (1 shl 1);  // force sync in opposite direction at end of sync
  {$EXTERNALSYM NTDSSITECONN_OPT_TWOWAY_SYNC}

// This bit means:
//  0 - Compression of replication data across this site connection enabled
//  1 - Compression of replication data across this site connection disabled

  NTDSSITECONN_OPT_DISABLE_COMPRESSION = (1 shl 2);
  {$EXTERNALSYM NTDSSITECONN_OPT_DISABLE_COMPRESSION}

// Bit flags for options attribute on site-Link objects
// Note that these options are AND-ed along a site-link path
//

  NTDSSITELINK_OPT_USE_NOTIFY  = (1 shl 0); // Use notification on this link
  {$EXTERNALSYM NTDSSITELINK_OPT_USE_NOTIFY}
  NTDSSITELINK_OPT_TWOWAY_SYNC = (1 shl 1);  // force sync in opposite direction at end of sync
  {$EXTERNALSYM NTDSSITELINK_OPT_TWOWAY_SYNC}

// This bit means:
//  0 - Compression of replication data across this site link enabled
//  1 - Compression of replication data across this site link disabled

  NTDSSITELINK_OPT_DISABLE_COMPRESSION = (1 shl 2);
  {$EXTERNALSYM NTDSSITELINK_OPT_DISABLE_COMPRESSION}

// ***********************
// Well Known Object Guids
// ***********************

  GUID_USERS_CONTAINER_A              = 'a9d1ca15768811d1aded00c04fd8d5cd';
  {$EXTERNALSYM GUID_USERS_CONTAINER_A}
  GUID_COMPUTRS_CONTAINER_A           = 'aa312825768811d1aded00c04fd8d5cd';
  {$EXTERNALSYM GUID_COMPUTRS_CONTAINER_A}
  GUID_SYSTEMS_CONTAINER_A            = 'ab1d30f3768811d1aded00c04fd8d5cd';
  {$EXTERNALSYM GUID_SYSTEMS_CONTAINER_A}
  GUID_DOMAIN_CONTROLLERS_CONTAINER_A = 'a361b2ffffd211d1aa4b00c04fd7d83a';
  {$EXTERNALSYM GUID_DOMAIN_CONTROLLERS_CONTAINER_A}
  GUID_INFRASTRUCTURE_CONTAINER_A     = '2fbac1870ade11d297c400c04fd8d5cd';
  {$EXTERNALSYM GUID_INFRASTRUCTURE_CONTAINER_A}
  GUID_DELETED_OBJECTS_CONTAINER_A    = '18e2ea80684f11d2b9aa00c04f79f805';
  {$EXTERNALSYM GUID_DELETED_OBJECTS_CONTAINER_A}
  GUID_LOSTANDFOUND_CONTAINER_A       = 'ab8153b7768811d1aded00c04fd8d5cd';
  {$EXTERNALSYM GUID_LOSTANDFOUND_CONTAINER_A}
  GUID_FOREIGNSECURITYPRINCIPALS_CONTAINER_A = '22b70c67d56e4efb91e9300fca3dc1aa';
  {$EXTERNALSYM GUID_FOREIGNSECURITYPRINCIPALS_CONTAINER_A}
  GUID_PROGRAM_DATA_CONTAINER_A       = '09460c08ae1e4a4ea0f64aee7daa1e5a';
  {$EXTERNALSYM GUID_PROGRAM_DATA_CONTAINER_A}
  GUID_MICROSOFT_PROGRAM_DATA_CONTAINER_A = 'f4be92a4c777485e878e9421d53087db';
  {$EXTERNALSYM GUID_MICROSOFT_PROGRAM_DATA_CONTAINER_A}

  GUID_USERS_CONTAINER_W              = WideString('a9d1ca15768811d1aded00c04fd8d5cd');
  {$EXTERNALSYM GUID_USERS_CONTAINER_W}
  GUID_COMPUTRS_CONTAINER_W           = WideString('aa312825768811d1aded00c04fd8d5cd');
  {$EXTERNALSYM GUID_COMPUTRS_CONTAINER_W}
  GUID_SYSTEMS_CONTAINER_W            = WideString('ab1d30f3768811d1aded00c04fd8d5cd');
  {$EXTERNALSYM GUID_SYSTEMS_CONTAINER_W}
  GUID_DOMAIN_CONTROLLERS_CONTAINER_W = WideString('a361b2ffffd211d1aa4b00c04fd7d83a');
  {$EXTERNALSYM GUID_DOMAIN_CONTROLLERS_CONTAINER_W}
  GUID_INFRASTRUCTURE_CONTAINER_W     = WideString('2fbac1870ade11d297c400c04fd8d5cd');
  {$EXTERNALSYM GUID_INFRASTRUCTURE_CONTAINER_W}
  GUID_DELETED_OBJECTS_CONTAINER_W    = WideString('18e2ea80684f11d2b9aa00c04f79f805');
  {$EXTERNALSYM GUID_DELETED_OBJECTS_CONTAINER_W}
  GUID_LOSTANDFOUND_CONTAINER_W       = WideString('ab8153b7768811d1aded00c04fd8d5cd');
  {$EXTERNALSYM GUID_LOSTANDFOUND_CONTAINER_W}
  GUID_FOREIGNSECURITYPRINCIPALS_CONTAINER_W = WideString('22b70c67d56e4efb91e9300fca3dc1aa');
  {$EXTERNALSYM GUID_FOREIGNSECURITYPRINCIPALS_CONTAINER_W}
  GUID_PROGRAM_DATA_CONTAINER_W       = WideString('09460c08ae1e4a4ea0f64aee7daa1e5a');
  {$EXTERNALSYM GUID_PROGRAM_DATA_CONTAINER_W}
  GUID_MICROSOFT_PROGRAM_DATA_CONTAINER_W = WideString('f4be92a4c777485e878e9421d53087db');
  {$EXTERNALSYM GUID_MICROSOFT_PROGRAM_DATA_CONTAINER_W}

  GUID_USERS_CONTAINER_BYTE              = '\xa9\xd1\xca\x15\x76\x88\x11\xd1\xad\xed\x00\xc0\x4f\xd8\xd5\xcd';
  {$EXTERNALSYM GUID_USERS_CONTAINER_BYTE}
  GUID_COMPUTRS_CONTAINER_BYTE           = '\xaa\x31\x28\x25\x76\x88\x11\xd1\xad\xed\x00\xc0\x4f\xd8\xd5\xcd';
  {$EXTERNALSYM GUID_COMPUTRS_CONTAINER_BYTE}
  GUID_SYSTEMS_CONTAINER_BYTE            = '\xab\x1d\x30\xf3\x76\x88\x11\xd1\xad\xed\x00\xc0\x4f\xd8\xd5\xcd';
  {$EXTERNALSYM GUID_SYSTEMS_CONTAINER_BYTE}
  GUID_DOMAIN_CONTROLLERS_CONTAINER_BYTE = '\xa3\x61\xb2\xff\xff\xd2\x11\xd1\xaa\x4b\x00\xc0\x4f\xd7\xd8\x3a';
  {$EXTERNALSYM GUID_DOMAIN_CONTROLLERS_CONTAINER_BYTE}
  GUID_INFRASTRUCTURE_CONTAINER_BYTE     = '\x2f\xba\xc1\x87\x0a\xde\x11\xd2\x97\xc4\x00\xc0\x4f\xd8\xd5\xcd';
  {$EXTERNALSYM GUID_INFRASTRUCTURE_CONTAINER_BYTE}
  GUID_DELETED_OBJECTS_CONTAINER_BYTE    = '\x18\xe2\xea\x80\x68\x4f\x11\xd2\xb9\xaa\x00\xc0\x4f\x79\xf8\x05';
  {$EXTERNALSYM GUID_DELETED_OBJECTS_CONTAINER_BYTE}
  GUID_LOSTANDFOUND_CONTAINER_BYTE       = '\xab\x81\x53\xb7\x76\x88\x11\xd1\xad\xed\x00\xc0\x4f\xd8\xd5\xcd';
  {$EXTERNALSYM GUID_LOSTANDFOUND_CONTAINER_BYTE}
  GUID_FOREIGNSECURITYPRINCIPALS_CONTAINER_BYTE = '\x22\xb7\x0c\x67\xd5\x6e\x4e\xfb\x91\xe9\x30\x0f\xca\x3d\xc1\xaa';
  {$EXTERNALSYM GUID_FOREIGNSECURITYPRINCIPALS_CONTAINER_BYTE}
  GUID_PROGRAM_DATA_CONTAINER_BYTE       = '\x09\x46\x0c\x08\xae\x1e\x4a\x4e\xa0\xf6\x4a\xee\x7d\xaa\x1e\x5a';
  {$EXTERNALSYM GUID_PROGRAM_DATA_CONTAINER_BYTE}
  GUID_MICROSOFT_PROGRAM_DATA_CONTAINER_BYTE = '\xf4\xbe\x92\xa4\xc7\x77\x48\x5e\x87\x8e\x94\x21\xd5\x30\x87\xdb';
  {$EXTERNALSYM GUID_MICROSOFT_PROGRAM_DATA_CONTAINER_BYTE}

type
  _DS_MANGLE_FOR = (
    DS_MANGLE_UNKNOWN,
    DS_MANGLE_OBJECT_RDN_FOR_DELETION,
    DS_MANGLE_OBJECT_RDN_FOR_NAME_CONFLICT);
  {$EXTERNALSYM _DS_MANGLE_FOR}
  DS_MANGLE_FOR = _DS_MANGLE_FOR;
  {$EXTERNALSYM DS_MANGLE_FOR}
  TDsMangleFor = DS_MANGLE_FOR;
  PDsMangleFor = ^DS_MANGLE_FOR;

//////////////////////////////////////////////////////////////////////////
//                                                                      //
// Prototypes                                                           //
//                                                                      //
//////////////////////////////////////////////////////////////////////////

// DSBind takes two optional input parameters which identify whether the
// caller found a domain controller themselves via DsGetDcName or whether
// a domain controller should be found using default parameters.
// Behavior of the possible combinations are outlined below.
//
// DomainControllerName(value), DnsDomainName(NULL)
//
//      The value for DomainControllerName is assumed to have been
//      obtained via DsGetDcName (i.e. Field with the same name in a
//      DOMAIN_CONTROLLER_INFO struct on return from DsGetDcName call.)
//      The client is bound to the domain controller at this name.
//      
//      Mutual authentication will be performed using an SPN of
//      LDAP/DomainControllerName provided DomainControllerName
//      is not a NETBIOS name or IP address - i.e. it must be a 
//      DNS host name.
//
// DomainControllerName(value), DnsDomainName(value)
//
//      DsBind will connect to the server identified by DomainControllerName.
//
//      Mutual authentication will be performed using an SPN of
//      LDAP/DomainControllerName/DnsDomainName provided neither value
//      is a NETBIOS names or IP address - i.e. they must be
//      valid DNS names.
//
// DomainControllerName(NULL), DnsDomainName(NULL)
//
//      DsBind will attempt to find to a global catalog and fail if one
//      can not be found.  
//
//      Mutual authentication will be performed using an SPN of
//      GC/DnsHostName/ForestName where DnsHostName and ForestName
//      represent the DomainControllerName and DnsForestName fields
//      respectively of the DOMAIN_CONTROLLER_INFO returned by the
//      DsGetDcName call used to find a global catalog.
//
// DomainControllerName(NULL), DnsDomainName(value)
//
//      DsBind will attempt to find a domain controller for the domain
//      identified by DnsDomainName and fail if one can not be found.
//
//      Mutual authentication will be performed using an SPN of
//      LDAP/DnsHostName/DnsDomainName where DnsDomainName is that
//      provided by the caller and DnsHostName is that returned by
//      DsGetDcName for the domain specified - provided DnsDomainName
//      is a valid DNS domain name - i.e. not a NETBIOS domain name.

function DsBindA(DomainControllerName: LPCSTR; DnsDomainName: LPCSTR;
  var phDS: HANDLE): DWORD; stdcall;
{$EXTERNALSYM DsBindA}
function DsBindW(DomainControllerName: LPCWSTR; DnsDomainName: LPCWSTR;
  var phDS: HANDLE): DWORD; stdcall;
{$EXTERNALSYM DsBindW}

{$IFDEF UNICODE}
function DsBind(DomainControllerName: LPCSTR; DnsDomainName: LPCSTR;
  var phDS: HANDLE): DWORD; stdcall;
{$EXTERNALSYM DsBind}
{$ELSE}
function DsBind(DomainControllerName: LPCWSTR; DnsDomainName: LPCWSTR;
  var phDS: HANDLE): DWORD; stdcall;
{$EXTERNALSYM DsBind}
{$ENDIF}

function DsBindWithCredA(DomainControllerName: LPCSTR; DnsDomainName: LPCSTR;
  AuthIdentity: RPC_AUTH_IDENTITY_HANDLE; var phDS: HANDLE): DWORD; stdcall;
{$EXTERNALSYM DsBindWithCredA}
function DsBindWithCredW(DomainControllerName: LPCWSTR; DnsDomainName: LPCWSTR;
  AuthIdentity: RPC_AUTH_IDENTITY_HANDLE; var phDS: HANDLE): DWORD; stdcall;
{$EXTERNALSYM DsBindWithCredW}

{$IFDEF UNICODE}
function DsBindWithCred(DomainControllerName: LPCWSTR; DnsDomainName: LPCWSTR;
  AuthIdentity: RPC_AUTH_IDENTITY_HANDLE; var phDS: HANDLE): DWORD; stdcall;
{$EXTERNALSYM DsBindWithCred}
{$ELSE}
function DsBindWithCred(DomainControllerName: LPCSTR; DnsDomainName: LPCSTR;
  AuthIdentity: RPC_AUTH_IDENTITY_HANDLE; var phDS: HANDLE): DWORD; stdcall;
{$EXTERNALSYM DsBindWithCred}
{$ENDIF}

//
// DsBindWithSpn{A|W} allows the caller to specify the service principal
// name (SPN) which will be used for mutual authentication against
// the destination server.  Do not provide an SPN if you are expecting
// DsBind to find a server for you as SPNs are machine specific and its
// unlikely the SPN you provide matches the server DsBind finds for you.
// Providing a NULL ServicePrincipalName argument results in behavior
// identical to DsBindWithCred{A|W}.
//

function DsBindWithSpnA(DomainControllerName: LPCSTR; DnsDomainName: LPCSTR;
  AuthIdentity: RPC_AUTH_IDENTITY_HANDLE; ServicePrincipalName: LPCSTR;
  var phDS: HANDLE): DWORD; stdcall;
{$EXTERNALSYM DsBindWithSpnA}
function DsBindWithSpnW(DomainControllerName: LPCWSTR; DnsDomainName: LPCWSTR;
  AuthIdentity: RPC_AUTH_IDENTITY_HANDLE; ServicePrincipalName: LPCWSTR;
  var phDS: HANDLE): DWORD; stdcall;
{$EXTERNALSYM DsBindWithSpnW}

{$IFDEF UNICODE}
function DsBindWithSpn(DomainControllerName: LPCWSTR; DnsDomainName: LPCWSTR;
  AuthIdentity: RPC_AUTH_IDENTITY_HANDLE; ServicePrincipalName: LPCWSTR;
  var phDS: HANDLE): DWORD; stdcall;
{$EXTERNALSYM DsBindWithSpn}
{$ELSE}
function DsBindWithSpn(DomainControllerName: LPCSTR; DnsDomainName: LPCSTR;
  AuthIdentity: RPC_AUTH_IDENTITY_HANDLE; ServicePrincipalName: LPCSTR;
  var phDS: HANDLE): DWORD; stdcall;
{$EXTERNALSYM DsBindWithSpn}
{$ENDIF}

//
// DsBindWithSpnEx{A|W} allows you all the options of the previous
// DsBindWithSpn(), plus the added benefit of specifying some optional
// Binding flags.  Currently if you pass NTDSAPI_BIND_ALLOW_DELEGATION,
// you will get the exact old behaviour.  If you can avoid it, you
// should not specify this flag, see flag above for details.
//

function DsBindWithSpnExW(DomainControllerName, DnsDomainName: LPCWSTR; AuthIdentity: RPC_AUTH_IDENTITY_HANDLE;
  ServicePrincipalName: LPCWSTR; BindFlags: DWORD; phDS: LPHANDLE): DWORD; stdcall;
{$EXTERNALSYM DsBindWithSpnExW}
function DsBindWithSpnExA(DomainControllerName, DnsDomainName: LPCSTR; AuthIdentity: RPC_AUTH_IDENTITY_HANDLE;
  ServicePrincipalName: LPCSTR; BindFlags: DWORD; phDS: LPHANDLE): DWORD; stdcall;
{$EXTERNALSYM DsBindWithSpnExA}

{$IFDEF UNICODE}
function DsBindWithSpnEx(DomainControllerName, DnsDomainName: LPCWSTR; AuthIdentity: RPC_AUTH_IDENTITY_HANDLE;
  ServicePrincipalName: LPCWSTR; BindFlags: DWORD; phDS: LPHANDLE): DWORD; stdcall;
{$EXTERNALSYM DsBindWithSpnEx}
{$ELSE}
function DsBindWithSpnEx(DomainControllerName, DnsDomainName: LPCSTR; AuthIdentity: RPC_AUTH_IDENTITY_HANDLE;
  ServicePrincipalName: LPCSTR; BindFlags: DWORD; phDS: LPHANDLE): DWORD; stdcall;
{$EXTERNALSYM DsBindWithSpnEx}
{$ENDIF}

//
// DsBindToISTG{A|W} allows the caller to bind to the server which
// holds the Inter-Site Topology Generator role in the specified site.
// The site name should be the RDN of a site.  If no site is specified,
// the function will try to bind to the ISTG in a nearby site.
//

function DsBindToISTGW(SiteName: LPCWSTR; phDS: LPHANDLE): DWORD; stdcall;
{$EXTERNALSYM DsBindToISTGW}
function DsBindToISTGA(SiteName: LPCSTR; phDS: LPHANDLE): DWORD; stdcall;
{$EXTERNALSYM DsBindToISTGA}

{$IFDEF UNICODE}
function DsBindToISTG(SiteName: LPCWSTR; phDS: LPHANDLE): DWORD; stdcall;
{$EXTERNALSYM DsBindToISTG}
{$ELSE}
function DsBindToISTG(SiteName: LPCSTR; phDS: LPHANDLE): DWORD; stdcall;
{$EXTERNALSYM DsBindToISTG}
{$ENDIF}

//
// DsBindingSetTimeout allows the caller to specify a timeout value
// which will be honored by all RPC calls using the specified binding
// handle. RPC calls which take longer the timeout value are canceled.
//

function DsBindingSetTimeout(hDS: HANDLE; cTimeoutSecs: ULONG): DWORD; stdcall;
{$EXTERNALSYM DsBindingSetTimeout}

//
// DsUnBind
//

function DsUnBindA(var phDS: HANDLE): DWORD; stdcall;
{$EXTERNALSYM DsUnBindA}
function DsUnBindW(var phDS: HANDLE): DWORD; stdcall;
{$EXTERNALSYM DsUnBindW}

{$IFDEF UNICODE}
function DsUnBind(var phDS: HANDLE): DWORD; stdcall;
{$EXTERNALSYM DsUnBind}
{$ELSE}
function DsUnBind(var phDS: HANDLE): DWORD; stdcall;
{$EXTERNALSYM DsUnBind}
{$ENDIF}

//
// DsMakePasswordCredentials
//
// This function constructs a credential structure which is suitable for input
// to the DsBindWithCredentials function, or the ldap_open function (winldap.h)
// The credential must be freed using DsFreeCredential.
//
// None of the input parameters may be present indicating a null, default
// credential.  Otherwise the username must be present.  If the domain or
// password are null, they default to empty strings.  The domain name may be
// null when the username is fully qualified, for example UPN format.
//

function DsMakePasswordCredentialsA(User: LPCSTR; Domain: LPCSTR;
  Password: LPCSTR; var pAuthIdentity: RPC_AUTH_IDENTITY_HANDLE): DWORD; stdcall;
{$EXTERNALSYM DsMakePasswordCredentialsA}
function DsMakePasswordCredentialsW(User: LPCWSTR; Domain: LPCWSTR;
  Password: LPCWSTR; var pAuthIdentity: RPC_AUTH_IDENTITY_HANDLE): DWORD; stdcall;
{$EXTERNALSYM DsMakePasswordCredentialsW}

{$IFDEF UNICODE}
function DsMakePasswordCredentials(User: LPCWSTR; Domain: LPCWSTR;
  Password: LPCWSTR; var pAuthIdentity: RPC_AUTH_IDENTITY_HANDLE): DWORD; stdcall;
{$EXTERNALSYM DsMakePasswordCredentials}
{$ELSE}
function DsMakePasswordCredentials(User: LPCSTR; Domain: LPCSTR;
  Password: LPCSTR; var pAuthIdentity: RPC_AUTH_IDENTITY_HANDLE): DWORD; stdcall;
{$EXTERNALSYM DsMakePasswordCredentials}
{$ENDIF}

procedure DsFreePasswordCredentials(AuthIdentity: RPC_AUTH_IDENTITY_HANDLE); stdcall;
{$EXTERNALSYM DsFreePasswordCredentials}

procedure DsFreePasswordCredentialsA(AuthIdentity: RPC_AUTH_IDENTITY_HANDLE); stdcall;
{$EXTERNALSYM DsFreePasswordCredentialsA}
procedure DsFreePasswordCredentialsW(AuthIdentity: RPC_AUTH_IDENTITY_HANDLE); stdcall;
{$EXTERNALSYM DsFreePasswordCredentialsW}

//
// DsCrackNames
//

function DsCrackNamesA(hDS: HANDLE; flags: DS_NAME_FLAGS;
  formatOffered: DS_NAME_FORMAT; formatDesired: DS_NAME_FORMAT; cNames: DWORD;
  rpNames: LPCSTR; var ppResult: PDS_NAME_RESULTA): DWORD; stdcall;
{$EXTERNALSYM DsCrackNamesA}
function DsCrackNamesW(hDS: HANDLE; flags: DS_NAME_FLAGS;
  formatOffered: DS_NAME_FORMAT; formatDesired: DS_NAME_FORMAT; cNames: DWORD;
  rpNames: LPCWSTR; var ppResult: PDS_NAME_RESULTW): DWORD; stdcall;
{$EXTERNALSYM DsCrackNamesW}

{$IFDEF UNICODE}
function DsCrackNames(hDS: HANDLE; flags: DS_NAME_FLAGS;
  formatOffered: DS_NAME_FORMAT; formatDesired: DS_NAME_FORMAT; cNames: DWORD;
  rpNames: LPCWSTR; var ppResult: PDS_NAME_RESULTW): DWORD; stdcall;
{$EXTERNALSYM DsCrackNames}
{$ELSE}
function DsCrackNames(hDS: HANDLE; flags: DS_NAME_FLAGS;
  formatOffered: DS_NAME_FORMAT; formatDesired: DS_NAME_FORMAT; cNames: DWORD;
  rpNames: LPCSTR; var ppResult: PDS_NAME_RESULTA): DWORD; stdcall;
{$EXTERNALSYM DsCrackNames}
{$ENDIF}

//
// DsFreeNameResult
//

procedure DsFreeNameResultA(pResult: PDS_NAME_RESULTA); stdcall;
{$EXTERNALSYM DsFreeNameResultA}
procedure DsFreeNameResultW(pResult: PDS_NAME_RESULTW); stdcall;
{$EXTERNALSYM DsFreeNameResultW}

{$IFDEF UNICODE}
procedure DsFreeNameResult(pResult: PDS_NAME_RESULTW); stdcall;
{$EXTERNALSYM DsFreeNameResult}
{$ELSE}
procedure DsFreeNameResult(pResult: PDS_NAME_RESULTA); stdcall;
{$EXTERNALSYM DsFreeNameResult}
{$ENDIF}

// ==========================================================
// DSMakeSpn -- client call to create SPN for a service to which it wants to
// authenticate.
// This name is then passed to "pszTargetName" of InitializeSecurityContext().
//
// Notes:
// If the service name is a DNS host name, or canonical DNS service name
// e.g. "www.ms.com", i.e., caller resolved with gethostbyname, then instance
// name should be NULL.
// Realm is host name minus first component, unless it is in the exception list
//
// If the service name is NetBIOS machine name, then instance name should be
// NULL
// Form must be <domain>\<machine>
// Realm will be <domain>
//
// If the service name is that of a replicated service, where each replica has
// its own account (e.g., with SRV records) then the caller must supply the
// instance name then realm name is same as ServiceName
//
// If the service name is a DN, then must also supply instance name
// (DN could be name of service object (incl RPC or Winsock), name of machine
// account, name of domain object)
// then realm name is domain part of the DN
//
// If the service name is NetBIOS domain name, then must also supply instance
// name; realm name is domain name
//
// If the service is named by an IP address -- then use referring service name
// as service name
//
//  ServiceClass - e.g. "http", "ftp", "ldap", GUID
//  ServiceName - DNS or DN; assumes we can compute domain from service name
//  InstanceName OPTIONAL- DNS name of host for instance of service
//  InstancePort - port number for instance (0 if default)
//  Referrer OPTIONAL- DNS name of host that gave this referral
//  pcSpnLength - in -- max length IN CHARACTERS of principal name;
//                out -- actual
//                Length includes terminator
//  pszSPN - server principal name
//
// If buffer is not large enough, ERROR_BUFFER_OVERFLOW is returned and the
// needed length is returned in pcSpnLength.
//
//

function DsMakeSpnA(ServiceClass: LPCSTR; ServiceName: LPCSTR;
  InstanceName: LPCSTR; InstancePort: USHORT; Referrer: LPCSTR;
  var pcSpnLength: DWORD; pszSpn: LPSTR): DWORD; stdcall;
{$EXTERNALSYM DsMakeSpnA}
function DsMakeSpnW(ServiceClass: LPCWSTR; ServiceName: LPCWSTR;
  InstanceName: LPCWSTR; InstancePort: USHORT; Referrer: LPCWSTR;
  var pcSpnLength: DWORD; pszSpn: LPWSTR): DWORD; stdcall;
{$EXTERNALSYM DsMakeSpnW}

{$IFDEF UNICODE}
function DsMakeSpn(ServiceClass: LPCWSTR; ServiceName: LPCWSTR;
  InstanceName: LPCWSTR; InstancePort: USHORT; Referrer: LPCWSTR;
  var pcSpnLength: DWORD; pszSpn: LPWSTR): DWORD; stdcall;
{$EXTERNALSYM DsMakeSpn}
{$ELSE}
function DsMakeSpn(ServiceClass: LPCSTR; ServiceName: LPCSTR;
  InstanceName: LPCSTR; InstancePort: USHORT; Referrer: LPCSTR;
  var pcSpnLength: DWORD; pszSpn: LPSTR): DWORD; stdcall;
{$EXTERNALSYM DsMakeSpn}
{$ENDIF}

// ==========================================================
// DsGetSPN -- server's call to gets SPNs for a service name by which it is
// known to clients. N.B.: there may be more than one name by which clients
// know it the SPNs are then passed to DsAddAccountSpn to register them in
// the DS
//
//      IN SpnNameType eType,
//      IN LPCTSTR ServiceClass,
// kind of service -- "http", "ldap", "ftp", etc.
//      IN LPCTSTR ServiceName OPTIONAL,
// name of service -- DN or DNS; not needed for host-based
//      IN USHORT InstancePort,
// port number (0 => default) for instances
//      IN USHORT cInstanceNames,
// count of extra instance names and ports (0=>use gethostbyname)
//      IN LPCTSTR InstanceNames[] OPTIONAL,
// extra instance names (not used for host names)
//      IN USHORT InstancePorts[] OPTIONAL,
// extra instance ports (0 => default)
//      IN OUT PULONG pcSpn,    // count of SPNs
//      IN OUT LPTSTR * prpszSPN[]
// a bunch of SPNs for this service; free with DsFreeSpnArray

function DsGetSpnA(ServiceType: DS_SPN_NAME_TYPE; ServiceClass: LPCSTR;
  ServiceName: LPCSTR; InstancePort: USHORT; cInstanceNames: USHORT;
  pInstanceNames: LPCSTR; pInstancePorts: PUSHORT; var pcSpn: DWORD;
  var prpszSpn: LPSTR): DWORD; stdcall;
{$EXTERNALSYM DsGetSpnA}
function DsGetSpnW(ServiceType: DS_SPN_NAME_TYPE; ServiceClass: LPCWSTR;
  ServiceName: LPCWSTR; InstancePort: USHORT; cInstanceNames: USHORT;
  pInstanceNames: LPCWSTR; pInstancePorts: PUSHORT; var pcSpn: DWORD;
  var prpszSpn: LPWSTR): DWORD; stdcall;
{$EXTERNALSYM DsGetSpnW}

{$IFDEF UNICODE}
function DsGetSpn(ServiceType: DS_SPN_NAME_TYPE; ServiceClass: LPCWSTR;
  ServiceName: LPCWSTR; InstancePort: USHORT; cInstanceNames: USHORT;
  pInstanceNames: LPCWSTR; pInstancePorts: PUSHORT; var pcSpn: DWORD;
  var prpszSpn: LPWSTR): DWORD; stdcall;
{$EXTERNALSYM DsGetSpn}
{$ELSE}
function DsGetSpn(ServiceType: DS_SPN_NAME_TYPE; ServiceClass: LPCSTR;
  ServiceName: LPCSTR; InstancePort: USHORT; cInstanceNames: USHORT;
  pInstanceNames: LPCSTR; pInstancePorts: PUSHORT; var pcSpn: DWORD;
  var prpszSpn: LPSTR): DWORD; stdcall;
{$EXTERNALSYM DsGetSpn}
{$ENDIF}

// ==========================================================
// DsFreeSpnArray() -- Free array returned by DsGetSpn{A,W}

procedure DsFreeSpnArrayA(cSpn: DWORD; rpszSpn: LPSTR); stdcall;
{$EXTERNALSYM DsFreeSpnArrayA}
procedure DsFreeSpnArrayW(cSpn: DWORD; rpszSpn: LPWSTR); stdcall;
{$EXTERNALSYM DsFreeSpnArrayW}

{$IFDEF UNICODE}
procedure DsFreeSpnArray(cSpn: DWORD; rpszSpn: LPWSTR); stdcall;
{$EXTERNALSYM DsFreeSpnArray}
{$ELSE}
procedure DsFreeSpnArray(cSpn: DWORD; rpszSpn: LPSTR); stdcall;
{$EXTERNALSYM DsFreeSpnArray}
{$ENDIF}

// ==========================================================
// DsCrackSpn() -- parse an SPN into the ServiceClass,
// ServiceName, and InstanceName (and InstancePort) pieces.
// An SPN is passed in, along with a pointer to the maximum length
// for each piece and a pointer to a buffer where each piece should go.
// On exit, the maximum lengths are updated to the actual length for each piece
// and the buffer contain the appropriate piece. The InstancePort is 0 if not
// present.
//
// DWORD DsCrackSpn(
//      IN LPTSTR pszSPN,               // the SPN to parse
//      IN OUT PUSHORT pcServiceClass,  // input -- max length of ServiceClass;
//                                         output -- actual length
//      OUT LPCTSTR ServiceClass,       // the ServiceClass part of the SPN
//      IN OUT PUSHORT pcServiceName,   // input -- max length of ServiceName;
//                                         output -- actual length
//      OUT LPCTSTR ServiceName,        // the ServiceName part of the SPN
//      IN OUT PUSHORT pcInstance,      // input -- max length of ServiceClass;
//                                         output -- actual length
//      OUT LPCTSTR InstanceName,  // the InstanceName part of the SPN
//      OUT PUSHORT InstancePort          // instance port
//
// Note: lengths are in characters; all string lengths include terminators
// All arguments except pszSpn are optional.
//

function DsCrackSpnA(pszSpn: LPCSTR; pcServiceClass: LPDWORD; ServiceClass: LPSTR;
  pcServiceName: LPDWORD; ServiceName: LPSTR; pcInstanceName: LPDWORD;
  InstanceName: LPSTR; pInstancePort: PUSHORT): DWORD; stdcall;
{$EXTERNALSYM DsCrackSpnA}
function DsCrackSpnW(pszSpn: LPCWSTR; pcServiceClass: LPDWORD; ServiceClass: LPWSTR;
  pcServiceName: LPDWORD; ServiceName: LPWSTR; pcInstanceName: LPDWORD;
  InstanceName: LPWSTR; pInstancePort: PUSHORT): DWORD; stdcall;
{$EXTERNALSYM DsCrackSpnW}

{$IFDEF UNICODE}
function DsCrackSpn(pszSpn: LPCWSTR; pcServiceClass: LPDWORD; ServiceClass: LPWSTR;
  pcServiceName: LPDWORD; ServiceName: LPWSTR; pcInstanceName: LPDWORD;
  InstanceName: LPWSTR; pInstancePort: PUSHORT): DWORD; stdcall;
{$EXTERNALSYM DsCrackSpn}
{$ELSE}
function DsCrackSpn(pszSpn: LPCSTR; pcServiceClass: LPDWORD; ServiceClass: LPSTR;
  pcServiceName: LPDWORD; ServiceName: LPSTR; pcInstanceName: LPDWORD;
  InstanceName: LPSTR; pInstancePort: PUSHORT): DWORD; stdcall;
{$EXTERNALSYM DsCrackSpn}
{$ENDIF}


// ==========================================================
// DsWriteAccountSpn -- set or add SPNs for an account object
// Usually done by service itself, or perhaps by an admin.
//
// This call is RPC'd to the DC where the account object is stored, so it can
// securely enforce policy on what SPNs are allowed on the account. Direct LDAP
// writes to the SPN property are not allowed -- all writes must come through
// this RPC call. (Reads via // LDAP are OK.)
//
// The account object can be a machine accout, or a service (user) account.
//
// If called by the service to register itself, it can most easily get
// the names by calling DsGetSpn with each of the names that
// clients can use to find the service.
//
// IN SpnWriteOp eOp,                   // set, add
// IN LPCTSTR   pszAccount,             // DN of account to which to add SPN
// IN int       cSPN,                   // count of SPNs to add to account
// IN LPCTSTR   rpszSPN[]               // SPNs to add to altSecID property

function DsWriteAccountSpnA(hDS: HANDLE; Operation: DS_SPN_WRITE_OP;
  pszAccount: LPCSTR; cSpn: DWORD; rpszSpn: LPCSTR): DWORD; stdcall;
{$EXTERNALSYM DsWriteAccountSpnA}
function DsWriteAccountSpnW(hDS: HANDLE; Operation: DS_SPN_WRITE_OP;
  pszAccount: LPCWSTR; cSpn: DWORD; rpszSpn: LPCWSTR): DWORD; stdcall;
{$EXTERNALSYM DsWriteAccountSpnW}

{$IFDEF UNICODE}
function DsWriteAccountSpn(hDS: HANDLE; Operation: DS_SPN_WRITE_OP;
  pszAccount: LPCWSTR; cSpn: DWORD; rpszSpn: LPCWSTR): DWORD; stdcall;
{$EXTERNALSYM DsWriteAccountSpn}
{$ELSE}
function DsWriteAccountSpn(hDS: HANDLE; Operation: DS_SPN_WRITE_OP;
  pszAccount: LPCSTR; cSpn: DWORD; rpszSpn: LPCSTR): DWORD; stdcall;
{$EXTERNALSYM DsWriteAccountSpn}
{$ENDIF}

{++

Routine Description:

Constructs a Service Principal Name suitable to identify the desired server.
The service class and part of a dns hostname must be supplied.

This routine is a simplified wrapper to DsMakeSpn.
The ServiceName is made canonical by resolving through DNS.
Guid-based dns names are not supported.

NOTE:
This routine is no longer recommended for use. In order to be secure, an SPN
should be constructed purely on the client without reliance on other services,
such as DNS, which may be spoofed.

The simplified SPN constructed looks like this:

ServiceClass / ServiceName / ServiceName

The instance name portion (2nd position) is always defaulted.  The port and
referrer fields are not used.

Arguments:

    ServiceClass - Class of service, defined by the service, can be any
        string unique to the service

    ServiceName - dns hostname, fully qualified or not
       Stringized IP address is also resolved if necessary

    pcSpnLength - IN, maximum length of buffer, in chars
                  OUT, space utilized, in chars, including terminator

    pszSpn - Buffer, atleast of length *pcSpnLength

Return Value:

    WINAPI - Win32 error code

--}

function DsClientMakeSpnForTargetServerA(ServiceClass: LPCSTR; ServiceName: LPCSTR;
  var pcSpnLength: DWORD; pszSpn: LPSTR): DWORD; stdcall;
{$EXTERNALSYM DsClientMakeSpnForTargetServerA}
function DsClientMakeSpnForTargetServerW(ServiceClass: LPCWSTR; ServiceName: LPCWSTR;
  var pcSpnLength: DWORD; pszSpn: LPWSTR): DWORD; stdcall;
{$EXTERNALSYM DsClientMakeSpnForTargetServerW}

{$IFDEF UNICODE}
function DsClientMakeSpnForTargetServer(ServiceClass: LPCWSTR; ServiceName: LPCWSTR;
  var pcSpnLength: DWORD; pszSpn: LPWSTR): DWORD; stdcall;
{$EXTERNALSYM DsClientMakeSpnForTargetServer}
{$ELSE}
function DsClientMakeSpnForTargetServer(ServiceClass: LPCSTR; ServiceName: LPCSTR;
  var pcSpnLength: DWORD; pszSpn: LPSTR): DWORD; stdcall;
{$EXTERNALSYM DsClientMakeSpnForTargetServer}
{$ENDIF}

{++
outine Description:

Register Service Principal Names for a server application.

This routine does the following:
1. Enumerates a list of server SPNs using DsGetSpn and the provided class
2. Determines the domain of the current user context
3. Determines the DN of the current user context if not supplied
4. Locates a domain controller
5. Binds to the domain controller
6. Uses DsWriteAccountSpn to write the SPNs on the named object DN
7. Unbinds

Construct server SPNs for this service, and write them to the right object.

If the userObjectDn is specified, the SPN is written to that object.

Otherwise the Dn is defaulted, to the user object, then computer.

Now, bind to the DS, and register the name on the object for the
user this service is running as.  So, if we're running as local
system, we'll register it on the computer object itself.  If we're
running as a domain user, we'll add the SPN to the user's object.

Arguments:

    Operation - What should be done with the values: add, replace or delete
    ServiceClass - Unique string identifying service
    UserObjectDN - Optional, dn of object to write SPN to

Return Value:

    WINAPI - Win32 error code

--}

function DsServerRegisterSpnA(Operation: DS_SPN_WRITE_OP; ServiceClass: LPCSTR;
  UserObjectDN: LPCSTR): DWORD; stdcall;
{$EXTERNALSYM DsServerRegisterSpnA}
function DsServerRegisterSpnW(Operation: DS_SPN_WRITE_OP; ServiceClass: LPCWSTR;
  UserObjectDN: LPCWSTR): DWORD; stdcall;
{$EXTERNALSYM DsServerRegisterSpnW}

{$IFDEF UNICODE}
function DsServerRegisterSpn(Operation: DS_SPN_WRITE_OP; ServiceClass: LPCWSTR;
  UserObjectDN: LPCWSTR): DWORD; stdcall;
{$EXTERNALSYM DsServerRegisterSpn}
{$ELSE}
function DsServerRegisterSpn(Operation: DS_SPN_WRITE_OP; ServiceClass: LPCSTR;
  UserObjectDN: LPCSTR): DWORD; stdcall;
{$EXTERNALSYM DsServerRegisterSpn}
{$ENDIF}

// DsReplicaSync.  The server that this call is executing on is called the
// destination.  The destination's naming context will be brought up to date
// with respect to a source system.  The source system is identified by the
// uuid.  The uuid is that of the source system's "NTDS Settings" object.
// The destination system must already be configured such that the source
// system is one of the systems from which it recieves replication data
// ("replication from"). This is usually done automatically by the KCC.
//
//  PARAMETERS:
//      pNC (DSNAME *)
//          Name of the NC to synchronize.
//      puuidSourceDRA (SZ)
//          objectGuid of DSA with which to synchronize the replica.
//      ulOptions (ULONG)
//          Bitwise OR of zero or more flags
//   RETURNS: WIN32 STATUS

function DsReplicaSyncA(hDS: HANDLE; NameContext: LPCSTR; pUuidDsaSrc: LPUUID;
  Options: ULONG): DWORD; stdcall;
{$EXTERNALSYM DsReplicaSyncA}
function DsReplicaSyncW(hDS: HANDLE; NameContext: LPCWSTR; pUuidDsaSrc: LPUUID;
  Options: ULONG): DWORD; stdcall;
{$EXTERNALSYM DsReplicaSyncW}

{$IFDEF UNICODE}
function DsReplicaSync(hDS: HANDLE; NameContext: LPCWSTR; pUuidDsaSrc: LPUUID;
  Options: ULONG): DWORD; stdcall;
{$EXTERNALSYM DsReplicaSync}
{$ELSE}
function DsReplicaSync(hDS: HANDLE; NameContext: LPCSTR; pUuidDsaSrc: LPUUID;
  Options: ULONG): DWORD; stdcall;
{$EXTERNALSYM DsReplicaSync}
{$ENDIF}

// DsReplicaAdd
//
{
Description:
   This call is executed on the destination.  It causes the destination to
   add a "replication from" reference to the indicated source system.

The source server is identified by string name, not uuid as with Sync.
The DsaSrcAddress parameter is the transport specific address of the source
DSA, usually its guid-based dns name.  The guid in the guid-based dns name is
the object-guid of that server's ntds-dsa (settings) object.

Arguments:

    pNC (IN) - NC for which to add the replica.

    pSourceDsaDN (IN) - DN of the source DSA's ntdsDsa object.  Required if
        ulOptions includes DS_REPADD_ASYNCHRONOUS_REPLICA; ignored otherwise.

    pTransportDN (IN) - DN of the interSiteTransport object representing the
        transport by which to communicate with the source server.  Required if
        ulOptions includes INTERSITE_MESSAGING; ignored otherwise.

    pszSourceDsaAddress (IN) - Transport-specific address of the source DSA.

    pSchedule (IN) - Schedule by which to replicate the NC from this
        source in the future.

    ulOptions (IN) - flags
    RETURNS: WIN32 STATUS
}

function DsReplicaAddA(hDS: HANDLE; NameContext: LPCSTR; SourceDsaDn: LPCSTR;
  TransportDn: LPCSTR; SourceDsaAddress: LPCSTR; pSchedule: PSCHEDULE;
  Options: DWORD): DWORD; stdcall;
{$EXTERNALSYM DsReplicaAddA}
function DsReplicaAddW(hDS: HANDLE; NameContext: LPCWSTR; SourceDsaDn: LPCWSTR;
  TransportDn: LPCWSTR; SourceDsaAddress: LPCWSTR; pSchedule: PSCHEDULE;
  Options: DWORD): DWORD; stdcall;
{$EXTERNALSYM DsReplicaAddW}

{$IFDEF UNICODE}
function DsReplicaAdd(hDS: HANDLE; NameContext: LPCWSTR; SourceDsaDn: LPCWSTR;
  TransportDn: LPCWSTR; SourceDsaAddress: LPCWSTR; pSchedule: PSCHEDULE;
  Options: DWORD): DWORD; stdcall;
{$EXTERNALSYM DsReplicaAdd}
{$ELSE}
function DsReplicaAdd(hDS: HANDLE; NameContext: LPCSTR; SourceDsaDn: LPCSTR;
  TransportDn: LPCSTR; SourceDsaAddress: LPCSTR; pSchedule: PSCHEDULE;
  Options: DWORD): DWORD; stdcall;
{$EXTERNALSYM DsReplicaAdd}
{$ENDIF}

// DsReplicaDel
//
// The server that this call is executing on is the destination.  The call
// causes the destination to remove a "replication from" reference to the
// indicated source server.
// The source server is identified by string name, not uuid as with Sync.
// The DsaSrc parameter is the transport specific address of the source DSA,
// usually its guid-based dns name.  The guid in the guid-based dns name is
// the object-guid of that server's ntds-dsa (settings) object.
// If you remove an NC from a given destination and specify the "no source"
// flag, then the entire replica will be removed from the DC.
//
//  PARAMETERS:
//      pNC (DSNAME *)
//          Name of the NC for which to delete a source.
//      pszSourceDRA (SZ)
//          DSA for which to delete the source.
//      ulOptions (ULONG)
//          Bitwise OR of zero or more flags
//
//
//   RETURNS: WIN32 STATUS

function DsReplicaDelA(hDS: HANDLE; NameContext: LPCSTR; DsaSrc: LPCSTR;
  Options: ULONG): DWORD; stdcall;
{$EXTERNALSYM DsReplicaDelA}
function DsReplicaDelW(hDS: HANDLE; NameContext: LPCWSTR; DsaSrc: LPCWSTR;
  Options: ULONG): DWORD; stdcall;
{$EXTERNALSYM DsReplicaDelW}

{$IFDEF UNICODE}
function DsReplicaDel(hDS: HANDLE; NameContext: LPCWSTR; DsaSrc: LPCWSTR;
  Options: ULONG): DWORD; stdcall;
{$EXTERNALSYM DsReplicaDel}
{$ELSE}
function DsReplicaDel(hDS: HANDLE; NameContext: LPCSTR; DsaSrc: LPCSTR;
  Options: ULONG): DWORD; stdcall;
{$EXTERNALSYM DsReplicaDel}
{$ENDIF}

// DsReplicaModify
//
//
//  Modify a source for a given naming context
//
//  The value must already exist.
//
//  Either the UUID or the address may be used to identify the current value.
//  If a UUID is specified, the UUID will be used for comparison.  Otherwise,
//  the address will be used for comparison.
//
//  PARAMETERS:
//      pNC (DSNAME *)
//          Name of the NC for which the Reps-From should be modified.
//      puuidSourceDRA (UUID *)
//          Guid of the DSA object for the source server. May be NULL if:
//            . ulModifyFields does not include DS_REPMOD_UPDATE_ADDRESS and
//            . pmtxSourceDRA is non-NULL.
//      puuidTransportObj (UUID *)
//          objectGuid of the transport by which replication is to be performed
//          Ignored if ulModifyFields does not include
//          DS_REPMOD_UPDATE_TRANSPORT.
//      pszSourceDRA (SZ)
//          DSA for which the reference should be added or deleted.  Ignored if
//          puuidSourceDRA is non-NULL and ulModifyFields does not include
//          DS_REPMOD_UPDATE_ADDRESS.
//      prtSchedule (REPLTIMES *)
//          Periodic replication schedule for this replica.  Ignored if
//          ulModifyFields does not include DS_REPMOD_UPDATE_SCHEDULE.
//      ulReplicaFlags (ULONG)
//          Flags to set for this replica.  Ignored if ulModifyFields does not
//          include DS_REPMOD_UPDATE_FLAGS.
//      ulModifyFields (ULONG)
//          Fields to update.  One or more of the following bit flags:
//              UPDATE_ADDRESS
//                  Update the MTX_ADDR associated with the referenced server.
//              UPDATE_SCHEDULE
//                  Update the periodic replication schedule associated with
//                  the replica.
//              UPDATE_FLAGS
//                  Update the flags associated with the replica.
//              UPDATE_TRANSPORT
//                  Update the transport associated with the replica.
//      ulOptions (ULONG)
//          Bitwise OR of zero or more of the following:
//              DS_REPMOD_ASYNCHRONOUS_OPERATION
//                  Perform this operation asynchronously.
//   RETURNS: WIN32 STATUS

function DsReplicaModifyA(hDS: HANDLE; NameContext: LPCSTR; pUuidSourceDsa: LPUUID;
  TransportDn: LPCSTR; SourceDsaAddress: LPCSTR; pSchedule: PSCHEDULE;
  ReplicaFlags: DWORD; ModifyFields: DWORD; Options: DWORD): DWORD; stdcall;
{$EXTERNALSYM DsReplicaModifyA}
function DsReplicaModifyW(hDS: HANDLE; NameContext: LPCWSTR; pUuidSourceDsa: LPUUID;
  TransportDn: LPCWSTR; SourceDsaAddress: LPCWSTR; pSchedule: PSCHEDULE;
  ReplicaFlags: DWORD; ModifyFields: DWORD; Options: DWORD): DWORD; stdcall;
{$EXTERNALSYM DsReplicaModifyW}

{$IFDEF UNICODE}
function DsReplicaModify(hDS: HANDLE; NameContext: LPCWSTR; pUuidSourceDsa: LPUUID;
  TransportDn: LPCWSTR; SourceDsaAddress: LPCWSTR; pSchedule: PSCHEDULE;
  ReplicaFlags: DWORD; ModifyFields: DWORD; Options: DWORD): DWORD; stdcall;
{$EXTERNALSYM DsReplicaModify}
{$ELSE}
function DsReplicaModify(hDS: HANDLE; NameContext: LPCSTR; pUuidSourceDsa: LPUUID;
  TransportDn: LPCSTR; SourceDsaAddress: LPCSTR; pSchedule: PSCHEDULE;
  ReplicaFlags: DWORD; ModifyFields: DWORD; Options: DWORD): DWORD; stdcall;
{$EXTERNALSYM DsReplicaModify}
{$ENDIF}

// DsReplicaUpdateRefs
//
// In this case, the RPC is being executed on the "source" of destination-sourc
// replication relationship.  This function tells the source that it no longer
// supplies replication information to the indicated destination system.
// Add or remove a target server from the Reps-To property on the given NC.
// Add/remove a reference given the DSNAME of the corresponding NTDS-DSA
// object.
//
//  PARAMETERS:
//      pNC (DSNAME *)
//          Name of the NC for which the Reps-To should be modified.
//      DsaDest (SZ)
//          Network address of DSA for which the reference should be added
//          or deleted.
//      pUuidDsaDest (UUID *)
//          objectGuid of the DSA object for which the reference should be 
//          added or deleted.
//      ulOptions (ULONG)
//          Bitwise OR of zero or more of the following:
//              DS_REPUPD_ASYNC_OP
//                  Perform this operation asynchronously.
//              DS_REPUPD_ADD_REFERENCE
//                  Add the given server to the Reps-To property.
//              DS_REPUPD_DEL_REFERENCE
//                  Remove the given server from the Reps-To property.
//          Note that ADD_REF and DEL_REF may be paired to perform
//          "add or update".
//
//   RETURNS: WIN32 STATUS

function DsReplicaUpdateRefsA(hDS: HANDLE; NameContext: LPCSTR; DsaDest: LPCSTR;
  pUuidDsaDest: LPUUID; Options: ULONG): DWORD; stdcall;
{$EXTERNALSYM DsReplicaUpdateRefsA}
function DsReplicaUpdateRefsW(hDS: HANDLE; NameContext: LPCWSTR; DsaDest: LPCWSTR;
  pUuidDsaDest: LPUUID; Options: ULONG): DWORD; stdcall;
{$EXTERNALSYM DsReplicaUpdateRefsW}

{$IFDEF UNICODE}
function DsReplicaUpdateRefs(hDS: HANDLE; NameContext: LPCWSTR; DsaDest: LPCWSTR;
  pUuidDsaDest: LPUUID; Options: ULONG): DWORD; stdcall;
{$EXTERNALSYM DsReplicaUpdateRefs}
{$ELSE}
function DsReplicaUpdateRefs(hDS: HANDLE; NameContext: LPCSTR; DsaDest: LPCSTR;
  pUuidDsaDest: LPUUID; Options: ULONG): DWORD; stdcall;
{$EXTERNALSYM DsReplicaUpdateRefs}
{$ENDIF}

// Friends of DsReplicaSyncAll

type
  DS_REPSYNCALL_ERROR = (
    DS_REPSYNCALL_WIN32_ERROR_CONTACTING_SERVER,
    DS_REPSYNCALL_WIN32_ERROR_REPLICATING,
    DS_REPSYNCALL_SERVER_UNREACHABLE);
  {$EXTERNALSYM DS_REPSYNCALL_ERROR}
  TDsReSynCallError = DS_REPSYNCALL_ERROR;

  DS_REPSYNCALL_EVENT = (
    DS_REPSYNCALL_EVENT_ERROR,
    DS_REPSYNCALL_EVENT_SYNC_STARTED,
    DS_REPSYNCALL_EVENT_SYNC_COMPLETED,
    DS_REPSYNCALL_EVENT_FINISHED);
  {$EXTERNALSYM DS_REPSYNCALL_EVENT}
  TDsReSynCallEvent = DS_REPSYNCALL_EVENT;

// Friends of DsReplicaSyncAll

  PDS_REPSYNCALL_SYNCA = ^DS_REPSYNCALL_SYNCA;
  {$EXTERNALSYM PDS_REPSYNCALL_SYNCA}
  DS_REPSYNCALL_SYNCA = record
    pszSrcId: LPSTR;
    pszDstId: LPSTR;
    pszNC: LPSTR;
    pguidSrc: LPGUID;
    pguidDst: LPGUID;
  end;
  {$EXTERNALSYM DS_REPSYNCALL_SYNCA}
  TDsRepsyncallSyncA = DS_REPSYNCALL_SYNCA;
  PDsRepsyncallSyncA = PDS_REPSYNCALL_SYNCA;

  PDS_REPSYNCALL_SYNCW = ^DS_REPSYNCALL_SYNCW;
  {$EXTERNALSYM PDS_REPSYNCALL_SYNCW}
  DS_REPSYNCALL_SYNCW = record
    pszSrcId: LPWSTR;
    pszDstId: LPWSTR;
    pszNC: LPWSTR;
    pguidSrc: LPGUID;
    pguidDst: LPGUID;
  end;
  {$EXTERNALSYM DS_REPSYNCALL_SYNCW}
  TDsRepsyncallSyncW = DS_REPSYNCALL_SYNCW;
  PDsRepsyncallSyncW = PDS_REPSYNCALL_SYNCW;

  PDS_REPSYNCALL_ERRINFOA = ^DS_REPSYNCALL_ERRINFOA;
  {$EXTERNALSYM PDS_REPSYNCALL_ERRINFOA}
  DS_REPSYNCALL_ERRINFOA = record
    pszSvrId: LPSTR;
    error: DS_REPSYNCALL_ERROR;
    dwWin32Err: DWORD;
    pszSrcId: LPSTR;
  end;
  {$EXTERNALSYM DS_REPSYNCALL_ERRINFOA}
  PPDS_REPSYNCALL_ERRINFOA = ^PDS_REPSYNCALL_ERRINFOA;
  {$NODEFINE PPDS_REPSYNCALL_ERRINFOA}
  TDsRepSynCallErrInfoA = DS_REPSYNCALL_ERRINFOA;
  PDsRepSynCallErrInfoA = PDS_REPSYNCALL_ERRINFOA;

  PDS_REPSYNCALL_ERRINFOW = ^DS_REPSYNCALL_ERRINFOW;
  {$EXTERNALSYM PDS_REPSYNCALL_ERRINFOW}
  DS_REPSYNCALL_ERRINFOW = record
    pszSvrId: LPWSTR;
    error: DS_REPSYNCALL_ERROR;
    dwWin32Err: DWORD;
    pszSrcId: LPWSTR;
  end;
  {$EXTERNALSYM DS_REPSYNCALL_ERRINFOW}
  PPDS_REPSYNCALL_ERRINFOW = ^PDS_REPSYNCALL_ERRINFOW;
  {$NODEFINE PPDS_REPSYNCALL_ERRINFOW}
  TDsRepSynCallErrInfoW = DS_REPSYNCALL_ERRINFOW;
  PDsRepSynCallErrInfoW = PDS_REPSYNCALL_ERRINFOW;

  PDS_REPSYNCALL_UPDATEA = ^DS_REPSYNCALL_UPDATEA;
  {$EXTERNALSYM PDS_REPSYNCALL_UPDATEA}
  DS_REPSYNCALL_UPDATEA = record
    event: DS_REPSYNCALL_EVENT;
    pErrInfo: PDS_REPSYNCALL_ERRINFOA;
    pSync: PDS_REPSYNCALL_SYNCA;
  end;
  {$EXTERNALSYM DS_REPSYNCALL_UPDATEA}
  TDsRepSynCallUpdateA = DS_REPSYNCALL_UPDATEA;
  PDsRepSynCallUpdateA = PDS_REPSYNCALL_UPDATEA;

  PDS_REPSYNCALL_UPDATEW = ^DS_REPSYNCALL_UPDATEW;
  {$EXTERNALSYM PDS_REPSYNCALL_UPDATEW}
  DS_REPSYNCALL_UPDATEW = record
    event: DS_REPSYNCALL_EVENT;
    pErrInfo: PDS_REPSYNCALL_ERRINFOW;
    pSync: PDS_REPSYNCALL_SYNCW;
  end;
  {$EXTERNALSYM DS_REPSYNCALL_UPDATEW}
  TDsRepSynCallUpdateW = DS_REPSYNCALL_UPDATEW;
  PDsRepSynCallUpdateW = PDS_REPSYNCALL_UPDATEW;

{$IFDEF UNICODE}
  DS_REPSYNCALL_SYNC = DS_REPSYNCALL_SYNCW;
  {$EXTERNALSYM DS_REPSYNCALL_SYNC}
  DS_REPSYNCALL_ERRINFO = DS_REPSYNCALL_ERRINFOW;
  {$EXTERNALSYM DS_REPSYNCALL_ERRINFO}
  PPDS_REPSYNCALL_ERRINFO = PPDS_REPSYNCALL_ERRINFOW;
  {$NODEFINE PPDS_REPSYNCALL_ERRINFO}
  DS_REPSYNCALL_UPDATE = DS_REPSYNCALL_UPDATEW;
  {$EXTERNALSYM DS_REPSYNCALL_UPDATE}
  PDS_REPSYNCALL_SYNC = PDS_REPSYNCALL_SYNCW;
  {$EXTERNALSYM PDS_REPSYNCALL_SYNC}
  PDS_REPSYNCALL_ERRINFO = PDS_REPSYNCALL_ERRINFOW;
  {$EXTERNALSYM PDS_REPSYNCALL_ERRINFO}
  PDS_REPSYNCALL_UPDATE = PDS_REPSYNCALL_UPDATEW;
  {$EXTERNALSYM PDS_REPSYNCALL_UPDATE}
  TDsRepSynCallSync = TDsRepSynCallSyncW;
  PDsRepSynCallSync = PDsRepSynCallSyncW;
  TDsRepSynCallErrInfo = TDsRepSynCallErrInfoW;
  PDsRepSynCallErrInfo = PDsRepSynCallErrInfoW;
  TDsRepSynCallUpdate = TDsRepSynCallUpdateW;
  PDsRepSynCallUpdate = PDsRepSynCallUpdateW;
{$ELSE}
  DS_REPSYNCALL_SYNC = DS_REPSYNCALL_SYNCA;
  {$EXTERNALSYM DS_REPSYNCALL_SYNC}
  DS_REPSYNCALL_ERRINFO = DS_REPSYNCALL_ERRINFOA;
  {$EXTERNALSYM DS_REPSYNCALL_ERRINFO}
  PPDS_REPSYNCALL_ERRINFO = PPDS_REPSYNCALL_ERRINFOA;
  {$NODEFINE PPDS_REPSYNCALL_ERRINFO}
  DS_REPSYNCALL_UPDATE = DS_REPSYNCALL_UPDATEA;
  {$EXTERNALSYM DS_REPSYNCALL_UPDATE}
  PDS_REPSYNCALL_SYNC = PDS_REPSYNCALL_SYNCA;
  {$EXTERNALSYM PDS_REPSYNCALL_SYNC}
  PDS_REPSYNCALL_ERRINFO = PDS_REPSYNCALL_ERRINFOA;
  {$EXTERNALSYM PDS_REPSYNCALL_ERRINFO}
  PDS_REPSYNCALL_UPDATE = PDS_REPSYNCALL_UPDATEA;
  {$EXTERNALSYM PDS_REPSYNCALL_UPDATE}
  TDsRepSynCallSync = TDsRepSynCallSyncA;
  PDsRepSynCallSync = PDsRepSynCallSyncA;
  TDsRepSynCallErrInfo = TDsRepSynCallErrInfoA;
  PDsRepSynCallErrInfo = PDsRepSynCallErrInfoA;
  TDsRepSynCallUpdate = TDsRepSynCallUpdateA;
  PDsRepSynCallUpdate = PDsRepSynCallUpdateA;
{$ENDIF}

// **********************
// Replica SyncAll flags
// **********************

const

// This option has no effect.

  DS_REPSYNCALL_NO_OPTIONS = $00000000;
  {$EXTERNALSYM DS_REPSYNCALL_NO_OPTIONS}

// Ordinarily, if a server cannot be contacted, DsReplicaSyncAll tries to
// route around it and replicate from as many servers as possible.  Enabling
// this option will cause DsReplicaSyncAll to generate a fatal error if any
// server cannot be contacted, or if any server is unreachable (due to a
// disconnected or broken topology.)

  DS_REPSYNCALL_ABORT_IF_SERVER_UNAVAILABLE = $00000001;
  {$EXTERNALSYM DS_REPSYNCALL_ABORT_IF_SERVER_UNAVAILABLE}

// This option disables transitive replication; syncs will only be performed
// with adjacent servers and no DsBind calls will be made.

  DS_REPSYNCALL_SYNC_ADJACENT_SERVERS_ONLY = $00000002;
  {$EXTERNALSYM DS_REPSYNCALL_SYNC_ADJACENT_SERVERS_ONLY}

// Ordinarily, when DsReplicaSyncAll encounters a non-fatal error, it returns
// the GUID DNS of the relevant server(s).  Enabling this option causes
// DsReplicaSyncAll to return the servers' DNs instead.

  DS_REPSYNCALL_ID_SERVERS_BY_DN = $00000004;
  {$EXTERNALSYM DS_REPSYNCALL_ID_SERVERS_BY_DN}

// This option disables all syncing.  The topology will still be analyzed and
// unavailable / unreachable servers will still be identified.

  DS_REPSYNCALL_DO_NOT_SYNC = $00000008;
  {$EXTERNALSYM DS_REPSYNCALL_DO_NOT_SYNC}

// Ordinarily, DsReplicaSyncAll attempts to bind to all servers before
// generating the topology.  If a server cannot be contacted, DsReplicaSyncAll
// excludes that server from the topology and tries to route around it.  If
// this option is enabled, checking will be bypassed and DsReplicaSyncAll will
// assume all servers are responding.  This will speed operation of
// DsReplicaSyncAll, but if some servers are not responding, some transitive
// replications may be blocked.

  DS_REPSYNCALL_SKIP_INITIAL_CHECK = $00000010;
  {$EXTERNALSYM DS_REPSYNCALL_SKIP_INITIAL_CHECK}

// Push mode. Push changes from the home server out to all partners using
// transitive replication.  This reverses the direction of replication, and
// the order of execution of the replication sets from the usual "pulling"
// mode of execution.

  DS_REPSYNCALL_PUSH_CHANGES_OUTWARD = $00000020;
  {$EXTERNALSYM DS_REPSYNCALL_PUSH_CHANGES_OUTWARD}

// Cross site boundaries.  By default, the only servers that are considered are
// those in the same site as the home system.  With this option, all servers in
// the enterprise, across all sites, are eligible.  They must be connected by
// a synchronous (RPC) transport, however.

  DS_REPSYNCALL_CROSS_SITE_BOUNDARIES = $00000040;
  {$EXTERNALSYM DS_REPSYNCALL_CROSS_SITE_BOUNDARIES}

// DsReplicaSyncAll.  Syncs the destination server with all other servers
// in the site.
//
//  PARAMETERS:
//	hDS		(IN) - A DS connection bound to the destination server.
//	pszNameContext	(IN) - The naming context to synchronize
//	ulFlags		(IN) - Bitwise OR of zero or more flags
//	pFnCallBack	(IN, OPTIONAL) - Callback function for message-passing.
//	pCallbackData	(IN, OPTIONAL) - A pointer that will be passed to the
//				first argument of the callback function.
//	pErrors		(OUT, OPTIONAL) - Pointer to a (PDS_REPSYNCALL_ERRINFO *)
//				object that will hold an array of error structures.

type
  TSynchUpdateProcA = function (pData: LPVOID; pUpdate: PDS_REPSYNCALL_UPDATEA): BOOL; stdcall;
  TSynchUpdateProcW = function (pData: LPVOID; pUpdate: PDS_REPSYNCALL_UPDATEW): BOOL; stdcall;

function DsReplicaSyncAllA(hDS: HANDLE; pszNameContext: LPCSTR; ulFlags: ULONG;
  pfnCallBack: TSynchUpdateProcA; pCallbackData: LPVOID;
  pErrors: PPDS_REPSYNCALL_ERRINFOA): DWORD; stdcall;
{$EXTERNALSYM DsReplicaSyncAllA}
function DsReplicaSyncAllW(hDS: HANDLE; pszNameContext: LPCWSTR; ulFlags: ULONG;
  pfnCallBackW: TSynchUpdateProcW; pCallbackData: LPVOID;
  pErrors: PPDS_REPSYNCALL_ERRINFOW): DWORD; stdcall;
{$EXTERNALSYM DsReplicaSyncAllW}

{$IFDEF UNICODE}
function DsReplicaSyncAll(hDS: HANDLE; pszNameContext: LPCWSTR; ulFlags: ULONG;
  pfnCallBackW: TSynchUpdateProcW; pCallbackData: LPVOID;
  pErrors: PPDS_REPSYNCALL_ERRINFOW): DWORD; stdcall;
{$EXTERNALSYM DsReplicaSyncAll}
{$ELSE}
function DsReplicaSyncAll(hDS: HANDLE; pszNameContext: LPCSTR; ulFlags: ULONG;
  pfnCallBack: TSynchUpdateProcA; pCallbackData: LPVOID;
  pErrors: PPDS_REPSYNCALL_ERRINFOA): DWORD; stdcall;
{$EXTERNALSYM DsReplicaSyncAll}
{$ENDIF}

function DsRemoveDsServerA(hDs: HANDLE; ServerDN: LPSTR; DomainDN: LPSTR;
  fLastDcInDomain: PBOOL; fCommit: BOOL): DWORD; stdcall;
{$EXTERNALSYM DsRemoveDsServerA}
function DsRemoveDsServerW(hDs: HANDLE; ServerDN: LPWSTR; DomainDN: LPWSTR;
  fLastDcInDomain: PBOOL; fCommit: BOOL): DWORD; stdcall;
{$EXTERNALSYM DsRemoveDsServerW}

{$IFDEF UNICODE}
function DsRemoveDsServer(hDs: HANDLE; ServerDN: LPWSTR; DomainDN: LPWSTR;
  fLastDcInDomain: PBOOL; fCommit: BOOL): DWORD; stdcall;
{$EXTERNALSYM DsRemoveDsServer}
{$ELSE}
function DsRemoveDsServer(hDs: HANDLE; ServerDN: LPSTR; DomainDN: LPSTR;
  fLastDcInDomain: PBOOL; fCommit: BOOL): DWORD; stdcall;
{$EXTERNALSYM DsRemoveDsServer}
{$ENDIF}

function DsRemoveDsDomainA(hDs: HANDLE; DomainDN: LPSTR): DWORD; stdcall;
{$EXTERNALSYM DsRemoveDsDomainA}
function DsRemoveDsDomainW(hDs: HANDLE; DomainDN: LPWSTR): DWORD; stdcall;
{$EXTERNALSYM DsRemoveDsDomainW}

{$IFDEF UNICODE}
function DsRemoveDsDomain(hDs: HANDLE; DomainDN: LPWSTR): DWORD; stdcall;
{$EXTERNALSYM DsRemoveDsDomain}
{$ELSE}
function DsRemoveDsDomain(hDs: HANDLE; DomainDN: LPSTR): DWORD; stdcall;
{$EXTERNALSYM DsRemoveDsDomain}
{$ENDIF}

function DsListSitesA(hDs: HANDLE; var ppSites: PDS_NAME_RESULTA): DWORD; stdcall;
{$EXTERNALSYM DsListSitesA}
function DsListSitesW(hDs: HANDLE; var ppSites: PDS_NAME_RESULTW): DWORD; stdcall;
{$EXTERNALSYM DsListSitesW}

{$IFDEF UNICODE}
function DsListSites(hDs: HANDLE; var ppSites: PDS_NAME_RESULTW): DWORD; stdcall;
{$EXTERNALSYM DsListSites}
{$ELSE}
function DsListSites(hDs: HANDLE; var ppSites: PDS_NAME_RESULTA): DWORD; stdcall;
{$EXTERNALSYM DsListSites}
{$ENDIF}

function DsListServersInSiteA(hDs: HANDLE; site: LPCSTR;
  var ppServers: PDS_NAME_RESULTA): DWORD; stdcall;
{$EXTERNALSYM DsListServersInSiteA}
function DsListServersInSiteW(hDs: HANDLE; site: LPCWSTR;
  var ppServers: PDS_NAME_RESULTW): DWORD; stdcall;
{$EXTERNALSYM DsListServersInSiteW}

{$IFDEF UNICODE}
function DsListServersInSite(hDs: HANDLE; site: LPCWSTR;
  var ppServers: PDS_NAME_RESULTW): DWORD; stdcall;
{$EXTERNALSYM DsListServersInSite}
{$ELSE}
function DsListServersInSite(hDs: HANDLE; site: LPCSTR;
  var ppServers: PDS_NAME_RESULTA): DWORD; stdcall;
{$EXTERNALSYM DsListServersInSite}
{$ENDIF}

function DsListDomainsInSiteA(hDs: HANDLE; site: LPCSTR;
  var ppDomains: PDS_NAME_RESULTA): DWORD; stdcall;
{$EXTERNALSYM DsListDomainsInSiteA}
function DsListDomainsInSiteW(hDs: HANDLE; site: LPCWSTR;
  var ppDomains: PDS_NAME_RESULTW): DWORD; stdcall;
{$EXTERNALSYM DsListDomainsInSiteW}

{$IFDEF UNICODE}
function DsListDomainsInSite(hDs: HANDLE; site: LPCWSTR;
  var ppDomains: PDS_NAME_RESULTW): DWORD; stdcall;
{$EXTERNALSYM DsListDomainsInSite}
{$ELSE}
function DsListDomainsInSite(hDs: HANDLE; site: LPCSTR;
  var ppDomains: PDS_NAME_RESULTA): DWORD; stdcall;
{$EXTERNALSYM DsListDomainsInSite}
{$ENDIF}

function DsListServersForDomainInSiteA(hDs: HANDLE; domain: LPCSTR; site: LPCSTR;
  var ppServers: PDS_NAME_RESULTA): DWORD; stdcall;
{$EXTERNALSYM DsListServersForDomainInSiteA}
function DsListServersForDomainInSiteW(hDs: HANDLE; domain: LPCWSTR; site: LPCWSTR;
  var ppServers: PDS_NAME_RESULTW): DWORD; stdcall;
{$EXTERNALSYM DsListServersForDomainInSiteW}

{$IFDEF UNICODE}
function DsListServersForDomainInSite(hDs: HANDLE; domain: LPCWSTR; site: LPCWSTR;
  var ppServers: PDS_NAME_RESULTW): DWORD; stdcall;
{$EXTERNALSYM DsListServersForDomainInSite}
{$ELSE}
function DsListServersForDomainInSite(hDs: HANDLE; domain: LPCSTR; site: LPCSTR;
  var ppServers: PDS_NAME_RESULTA): DWORD; stdcall;
{$EXTERNALSYM DsListServersForDomainInSite}
{$ENDIF}

// Define indices for DsListInfoForServer return data.  Check status
// for each field as a given value may not be present.

const
  DS_LIST_DSA_OBJECT_FOR_SERVER     = 0;
  {$EXTERNALSYM DS_LIST_DSA_OBJECT_FOR_SERVER}
  DS_LIST_DNS_HOST_NAME_FOR_SERVER  = 1;
  {$EXTERNALSYM DS_LIST_DNS_HOST_NAME_FOR_SERVER}
  DS_LIST_ACCOUNT_OBJECT_FOR_SERVER = 2;
  {$EXTERNALSYM DS_LIST_ACCOUNT_OBJECT_FOR_SERVER}

function DsListInfoForServerA(hDs: HANDLE; server: LPCSTR;
  var ppInfo: PDS_NAME_RESULTA): DWORD; stdcall;
{$EXTERNALSYM DsListInfoForServerA}
function DsListInfoForServerW(hDs: HANDLE; server: LPCWSTR;
  var ppInfo: PDS_NAME_RESULTW): DWORD; stdcall;
{$EXTERNALSYM DsListInfoForServerW}

{$IFDEF UNICODE}
function DsListInfoForServer(hDs: HANDLE; server: LPCWSTR;
  var ppInfo: PDS_NAME_RESULTW): DWORD; stdcall;
{$EXTERNALSYM DsListInfoForServer}
{$ELSE}
function DsListInfoForServer(hDs: HANDLE; server: LPCSTR;
  var ppInfo: PDS_NAME_RESULTA): DWORD; stdcall;
{$EXTERNALSYM DsListInfoForServer}
{$ENDIF}

// Define indices for DsListRoles return data.  Check status for
// each field as a given value may not be present.

const
  DS_ROLE_SCHEMA_OWNER         = 0;
  {$EXTERNALSYM DS_ROLE_SCHEMA_OWNER}
  DS_ROLE_DOMAIN_OWNER         = 1;
  {$EXTERNALSYM DS_ROLE_DOMAIN_OWNER}
  DS_ROLE_PDC_OWNER            = 2;
  {$EXTERNALSYM DS_ROLE_PDC_OWNER}
  DS_ROLE_RID_OWNER            = 3;
  {$EXTERNALSYM DS_ROLE_RID_OWNER}
  DS_ROLE_INFRASTRUCTURE_OWNER = 4;
  {$EXTERNALSYM DS_ROLE_INFRASTRUCTURE_OWNER}

function DsListRolesA(hDs: HANDLE; var ppRoles: PDS_NAME_RESULTA): DWORD; stdcall;
{$EXTERNALSYM DsListRolesA}
function DsListRolesW(hDs: HANDLE; var ppRoles: PDS_NAME_RESULTW): DWORD; stdcall;
{$EXTERNALSYM DsListRolesW}

{$IFDEF UNICODE}
function DsListRoles(hDs: HANDLE; var ppRoles: PDS_NAME_RESULTW): DWORD; stdcall;
{$EXTERNALSYM DsListRoles}
{$ELSE}
function DsListRoles(hDs: HANDLE; var ppRoles: PDS_NAME_RESULTA): DWORD; stdcall;
{$EXTERNALSYM DsListRoles}
{$ENDIF}

//
// DsQuerySitesByCost{A|W} allows the caller to determine the
// communication cost between the From Site and each of the sites
// in the list of To Sites. The costs are returned in the rgSiteInfo
// structure which must be freed with DsQuerySitesFree.
//
// The Site Names should all be passed as RDNs. For example, if the
// site's DN is "CN=Foo,CN=Sites,CN=Configuration,...", the RDN is
// simply "Foo".
//

type
  DS_SITE_COST_INFO = record
    errorCode: DWORD;
    cost: DWORD;
  end;
  {$EXTERNALSYM DS_SITE_COST_INFO}
  PDS_SITE_COST_INFO = ^DS_SITE_COST_INFO;
  {$EXTERNALSYM PDS_SITE_COST_INFO}
  TDsSiteCostInfo = DS_SITE_COST_INFO;
  PDsSiteCostInfo = PDS_SITE_COST_INFO;

function DsQuerySitesByCostW(hDS: HANDLE; pwszFromSite: LPWSTR; out rgwszToSites: LPWSTR; cToSites, dwFlags: DWORD;
  out prgSiteInfo: PDS_SITE_COST_INFO): DWORD; stdcall;
{$EXTERNALSYM DsQuerySitesByCostW}
function DsQuerySitesByCostA(hDS: HANDLE; pwszFromSite: LPSTR; out rgwszToSites: LPSTR; cToSites, dwFlags: DWORD;
  out prgSiteInfo: PDS_SITE_COST_INFO): DWORD; stdcall;
{$EXTERNALSYM DsQuerySitesByCostA}

{$IFDEF UNICODE}
function DsQuerySitesByCost(hDS: HANDLE; pwszFromSite: LPWSTR; out rgwszToSites: LPWSTR; cToSites, dwFlags: DWORD;
  out prgSiteInfo: PDS_SITE_COST_INFO): DWORD; stdcall;
{$EXTERNALSYM DsQuerySitesByCost}
{$ELSE}
function DsQuerySitesByCost(hDS: HANDLE; pwszFromSite: LPSTR; out rgwszToSites: LPSTR; cToSites, dwFlags: DWORD;
  out prgSiteInfo: PDS_SITE_COST_INFO): DWORD; stdcall;
{$EXTERNALSYM DsQuerySitesByCost}
{$ENDIF}

//
// DsQuerySitesByCost will free the site info array returned
// from DsQuerySitesByCost{A|W}.
//

procedure DsQuerySitesFree(rgSiteInfo: PDS_SITE_COST_INFO); stdcall;
{$EXTERNALSYM DsQuerySitesFree}


// Definitions required for DsMapSchemaGuid routines.

const
  DS_SCHEMA_GUID_NOT_FOUND     = 0;
  {$EXTERNALSYM DS_SCHEMA_GUID_NOT_FOUND}
  DS_SCHEMA_GUID_ATTR          = 1;
  {$EXTERNALSYM DS_SCHEMA_GUID_ATTR}
  DS_SCHEMA_GUID_ATTR_SET      = 2;
  {$EXTERNALSYM DS_SCHEMA_GUID_ATTR_SET}
  DS_SCHEMA_GUID_CLASS         = 3;
  {$EXTERNALSYM DS_SCHEMA_GUID_CLASS}
  DS_SCHEMA_GUID_CONTROL_RIGHT = 4;
  {$EXTERNALSYM DS_SCHEMA_GUID_CONTROL_RIGHT}

type
  PDS_SCHEMA_GUID_MAPA = ^DS_SCHEMA_GUID_MAPA;
  {$EXTERNALSYM PDS_SCHEMA_GUID_MAPA}
  DS_SCHEMA_GUID_MAPA = record
    guid: GUID;      // mapped GUID
    guidType: DWORD; // DS_SCHEMA_GUID_* value
    pName: LPSTR;    // might be NULL
  end;
  {$EXTERNALSYM DS_SCHEMA_GUID_MAPA}
  TDsSchemaGuidMapA = DS_SCHEMA_GUID_MAPA;
  PDsSchemaGuidMapA = PDS_SCHEMA_GUID_MAPA;

  PDS_SCHEMA_GUID_MAPW = ^DS_SCHEMA_GUID_MAPW;
  {$EXTERNALSYM PDS_SCHEMA_GUID_MAPW}
  DS_SCHEMA_GUID_MAPW = record
    guid: GUID;      // mapped GUID
    guidType: DWORD; // DS_SCHEMA_GUID_* value
    pName: LPWSTR;   // might be NULL
  end;
  {$EXTERNALSYM DS_SCHEMA_GUID_MAPW}
  TDsSchemaGuidMapW = DS_SCHEMA_GUID_MAPW;
  PDsSchemaGuidMapW = PDS_SCHEMA_GUID_MAPW;

function DsMapSchemaGuidsA(hDs: HANDLE; cGuids: DWORD; rGuids: PGUID;
  var ppGuidMap: PDS_SCHEMA_GUID_MAPA): DWORD; stdcall;
{$EXTERNALSYM DsMapSchemaGuidsA}
function DsMapSchemaGuidsW(hDs: HANDLE; cGuids: DWORD; rGuids: PGUID;
  var ppGuidMap: PDS_SCHEMA_GUID_MAPW): DWORD; stdcall;
{$EXTERNALSYM DsMapSchemaGuidsW}

procedure DsFreeSchemaGuidMapA(pGuidMap: PDS_SCHEMA_GUID_MAPA); stdcall;
{$EXTERNALSYM DsFreeSchemaGuidMapA}
procedure DsFreeSchemaGuidMapW(pGuidMap: PDS_SCHEMA_GUID_MAPW); stdcall;
{$EXTERNALSYM DsFreeSchemaGuidMapW}

{$IFDEF UNICODE}
function DsMapSchemaGuids(hDs: HANDLE; cGuids: DWORD; rGuids: PGUID;
  var ppGuidMap: PDS_SCHEMA_GUID_MAPW): DWORD; stdcall;
{$EXTERNALSYM DsMapSchemaGuids}
procedure DsFreeSchemaGuidMap(pGuidMap: PDS_SCHEMA_GUID_MAPW); stdcall;
{$EXTERNALSYM DsFreeSchemaGuidMap}
{$ELSE}
function DsMapSchemaGuids(hDs: HANDLE; cGuids: DWORD; rGuids: PGUID;
  var ppGuidMap: PDS_SCHEMA_GUID_MAPA): DWORD; stdcall;
{$EXTERNALSYM DsMapSchemaGuids}
procedure DsFreeSchemaGuidMap(pGuidMap: PDS_SCHEMA_GUID_MAPA); stdcall;
{$EXTERNALSYM DsFreeSchemaGuidMap}
{$ENDIF}

type
  PDS_DOMAIN_CONTROLLER_INFO_1A = ^DS_DOMAIN_CONTROLLER_INFO_1A;
  {$EXTERNALSYM PDS_DOMAIN_CONTROLLER_INFO_1A}
  DS_DOMAIN_CONTROLLER_INFO_1A = record
    NetbiosName: LPSTR; // might be NULL
    DnsHostName: LPSTR; // might be NULL
    SiteName: LPSTR; // might be NULL
    ComputerObjectName: LPSTR; // might be NULL
    ServerObjectName: LPSTR; // might be NULL
    fIsPdc: BOOL;
    fDsEnabled: BOOL;
  end;
  {$EXTERNALSYM DS_DOMAIN_CONTROLLER_INFO_1A}
  TDsDomainControllerInfo1A = DS_DOMAIN_CONTROLLER_INFO_1A;
  PDsDomainControllerInfo1A = PDS_DOMAIN_CONTROLLER_INFO_1A;

  PDS_DOMAIN_CONTROLLER_INFO_1W = ^DS_DOMAIN_CONTROLLER_INFO_1W;
  {$EXTERNALSYM PDS_DOMAIN_CONTROLLER_INFO_1W}
  DS_DOMAIN_CONTROLLER_INFO_1W = record
    NetbiosName: LPWSTR; // might be NULL
    DnsHostName: LPWSTR; // might be NULL
    SiteName: LPWSTR; // might be NULL
    ComputerObjectName: LPWSTR; // might be NULL
    ServerObjectName: LPWSTR; // might be NULL
    fIsPdc: BOOL;
    fDsEnabled: BOOL;
  end;
  {$EXTERNALSYM DS_DOMAIN_CONTROLLER_INFO_1W}
  TDsDomainControllerInfo1W = DS_DOMAIN_CONTROLLER_INFO_1W;
  PDsDomainControllerInfo1W = PDS_DOMAIN_CONTROLLER_INFO_1W;

  PDS_DOMAIN_CONTROLLER_INFO_2A = ^DS_DOMAIN_CONTROLLER_INFO_2A;
  {$EXTERNALSYM PDS_DOMAIN_CONTROLLER_INFO_2A}
  DS_DOMAIN_CONTROLLER_INFO_2A = record
    NetbiosName: LPSTR; // might be NULL
    DnsHostName: LPSTR; // might be NULL
    SiteName: LPSTR; // might be NULL
    SiteObjectName: LPSTR; // might be NULL
    ComputerObjectName: LPSTR; // might be NULL
    ServerObjectName: LPSTR; // might be NULL
    NtdsDsaObjectName: LPSTR; // might be NULL
    fIsPdc: BOOL;
    fDsEnabled: BOOL;
    fIsGc: BOOL;
    // Valid iff SiteObjectName non-NULL.
    SiteObjectGuid: GUID;
    // Valid iff ComputerObjectName non-NULL.
    ComputerObjectGuid: GUID;
    // Valid iff ServerObjectName non-NULL;
    ServerObjectGuid: GUID;
    // Valid iff fDsEnabled is TRUE.
    NtdsDsaObjectGuid: GUID;
  end;
  {$EXTERNALSYM DS_DOMAIN_CONTROLLER_INFO_2A}
  TDsDomainControllerInfo2A = DS_DOMAIN_CONTROLLER_INFO_2A;
  PDsDomainControllerInfo2A = PDS_DOMAIN_CONTROLLER_INFO_2A;

  PDS_DOMAIN_CONTROLLER_INFO_2W = ^DS_DOMAIN_CONTROLLER_INFO_2W;
  {$EXTERNALSYM PDS_DOMAIN_CONTROLLER_INFO_2W}
  DS_DOMAIN_CONTROLLER_INFO_2W = record
    NetbiosName: LPWSTR; // might be NULL
    DnsHostName: LPWSTR; // might be NULL
    SiteName: LPWSTR; // might be NULL
    SiteObjectName: LPWSTR; // might be NULL
    ComputerObjectName: LPWSTR; // might be NULL
    ServerObjectName: LPWSTR; // might be NULL
    NtdsDsaObjectName: LPWSTR; // might be NULL
    fIsPdc: BOOL;
    fDsEnabled: BOOL;
    fIsGc: BOOL;
    // Valid iff SiteObjectName non-NULL.
    SiteObjectGuid: GUID;
    // Valid iff ComputerObjectName non-NULL.
    ComputerObjectGuid: GUID;
    // Valid iff ServerObjectName non-NULL;
    ServerObjectGuid: GUID;
    // Valid iff fDsEnabled is TRUE.
    NtdsDsaObjectGuid: GUID;
  end;
  {$EXTERNALSYM DS_DOMAIN_CONTROLLER_INFO_2W}
  TDsDomainControllerInfo2W = DS_DOMAIN_CONTROLLER_INFO_2W;
  PDsDomainControllerInfo2W = PDS_DOMAIN_CONTROLLER_INFO_2W;

{$IFDEF UNICODE}
  DS_DOMAIN_CONTROLLER_INFO_1 = DS_DOMAIN_CONTROLLER_INFO_1W;
  {$EXTERNALSYM DS_DOMAIN_CONTROLLER_INFO_1}
  DS_DOMAIN_CONTROLLER_INFO_2 = DS_DOMAIN_CONTROLLER_INFO_2W;
  {$EXTERNALSYM DS_DOMAIN_CONTROLLER_INFO_2}
  PDS_DOMAIN_CONTROLLER_INFO_1 = PDS_DOMAIN_CONTROLLER_INFO_1W;
  {$EXTERNALSYM PDS_DOMAIN_CONTROLLER_INFO_1}
  PDS_DOMAIN_CONTROLLER_INFO_2 = PDS_DOMAIN_CONTROLLER_INFO_2W;
  {$EXTERNALSYM PDS_DOMAIN_CONTROLLER_INFO_2}
  TDsDomainControllerInfo1 = TDsDomainControllerInfo1W;
  PDsDomainControllerInfo1 = PDsDomainControllerInfo1W;
  TDsDomainControllerInfo2 = TDsDomainControllerInfo2W;
  PDsDomainControllerInfo2 = PDsDomainControllerInfo2W;
{$ELSE}
  DS_DOMAIN_CONTROLLER_INFO_1 = DS_DOMAIN_CONTROLLER_INFO_1A;
  {$EXTERNALSYM DS_DOMAIN_CONTROLLER_INFO_1}
  DS_DOMAIN_CONTROLLER_INFO_2 = DS_DOMAIN_CONTROLLER_INFO_2A;
  {$EXTERNALSYM DS_DOMAIN_CONTROLLER_INFO_2}
  PDS_DOMAIN_CONTROLLER_INFO_1 = PDS_DOMAIN_CONTROLLER_INFO_1A;
  {$EXTERNALSYM PDS_DOMAIN_CONTROLLER_INFO_1}
  PDS_DOMAIN_CONTROLLER_INFO_2 = PDS_DOMAIN_CONTROLLER_INFO_2A;
  {$EXTERNALSYM PDS_DOMAIN_CONTROLLER_INFO_2}
  TDsDomainControllerInfo1 = TDsDomainControllerInfo1A;
  PDsDomainControllerInfo1 = PDsDomainControllerInfo1A;
  TDsDomainControllerInfo2 = TDsDomainControllerInfo2A;
  PDsDomainControllerInfo2 = PDsDomainControllerInfo2A;
{$ENDIF}

// The following APIs strictly find domain controller account objects 
// in the DS and return information associated with them.  As such, they
// may return entries which correspond to domain controllers long since
// decommissioned, etc. and there is no guarantee that there exists a 
// physical domain controller at all.  Use DsGetDcName (dsgetdc.h) to find
// live domain controllers for a domain.

function DsGetDomainControllerInfoA(hDs: HANDLE; DomainName: LPCSTR;
  InfoLevel: DWORD; var pcOut: DWORD; ppInfo: PPVOID): DWORD; stdcall;
{$EXTERNALSYM DsGetDomainControllerInfoA}
function DsGetDomainControllerInfoW(hDs: HANDLE; DomainName: LPCWSTR;
  InfoLevel: DWORD; var pcOut: DWORD; ppInfo: PPVOID): DWORD; stdcall;
{$EXTERNALSYM DsGetDomainControllerInfoW}

{$IFDEF UNICODE}
function DsGetDomainControllerInfo(hDs: HANDLE; DomainName: LPCWSTR;
  InfoLevel: DWORD; var pcOut: DWORD; ppInfo: PPVOID): DWORD; stdcall;
{$EXTERNALSYM DsGetDomainControllerInfo}
{$ELSE}
function DsGetDomainControllerInfo(hDs: HANDLE; DomainName: LPCSTR;
  InfoLevel: DWORD; var pcOut: DWORD; ppInfo: PPVOID): DWORD; stdcall;
{$EXTERNALSYM DsGetDomainControllerInfo}
{$ENDIF}

procedure DsFreeDomainControllerInfoA(InfoLevel: DWORD; cInfo: DWORD;
  pInfo: PVOID); stdcall;
{$EXTERNALSYM DsFreeDomainControllerInfoA}
procedure DsFreeDomainControllerInfoW(InfoLevel: DWORD; cInfo: DWORD;
  pInfo: PVOID); stdcall;
{$EXTERNALSYM DsFreeDomainControllerInfoW}

{$IFDEF UNICODE}
procedure DsFreeDomainControllerInfo(InfoLevel: DWORD; cInfo: DWORD;
  pInfo: PVOID); stdcall;
{$EXTERNALSYM DsFreeDomainControllerInfo}
{$ELSE}
procedure DsFreeDomainControllerInfo(InfoLevel: DWORD; cInfo: DWORD;
  pInfo: PVOID); stdcall;
{$EXTERNALSYM DsFreeDomainControllerInfo}
{$ENDIF}

type

// Which task should be run?

  DS_KCC_TASKID = (DS_KCC_TASKID_UPDATE_TOPOLOGY);
  {$EXTERNALSYM DS_KCC_TASKID}
  TDsKccTaskId = DS_KCC_TASKID;

// Don't wait for completion of the task; queue it and return.

const
  DS_KCC_FLAG_ASYNC_OP   = (1 shl 0);
  {$EXTERNALSYM DS_KCC_FLAG_ASYNC_OP}

// Don't enqueue the task if another queued task will run soon.

  DS_KCC_FLAG_DAMPED     = (1 shl 1);
  {$EXTERNALSYM DS_KCC_FLAG_DAMPED}

function DsReplicaConsistencyCheck(hDS: HANDLE; TaskID: DS_KCC_TASKID;
  dwFlags: DWORD): DWORD; stdcall;
{$EXTERNALSYM DsReplicaConsistencyCheck}

function DsReplicaVerifyObjectsW(hDS: HANDLE; NameContext: LPCWSTR; const pUuidDsaSrc: UUID; ulOptions: ULONG): DWORD; stdcall;
{$EXTERNALSYM DsReplicaVerifyObjectsW}
function DsReplicaVerifyObjectsA(hDS: HANDLE; NameContext: LPCSTR; const pUuidDsaSrc: UUID; ulOptions: ULONG): DWORD; stdcall;
{$EXTERNALSYM DsReplicaVerifyObjectsA}

{$IFDEF UNICODE}
function DsReplicaVerifyObjects(hDS: HANDLE; NameContext: LPCWSTR; const pUuidDsaSrc: UUID; ulOptions: ULONG): DWORD; stdcall;
{$EXTERNALSYM DsReplicaVerifyObjects}
{$ELSE}
function DsReplicaVerifyObjects(hDS: HANDLE; NameContext: LPCSTR; const pUuidDsaSrc: UUID; ulOptions: ULONG): DWORD; stdcall;
{$EXTERNALSYM DsReplicaVerifyObjects}
{$ENDIF}

// Do not delete objects on DsReplicaVerifyObjects call

const
  DS_EXIST_ADVISORY_MODE = ($1);
  {$EXTERNALSYM DS_EXIST_ADVISORY_MODE}

type
  _DS_REPL_INFO_TYPE = (
    DS_REPL_INFO_NEIGHBORS,                  // returns DS_REPL_NEIGHBORS *
    DS_REPL_INFO_CURSORS_FOR_NC,             // returns DS_REPL_CURSORS *
    DS_REPL_INFO_METADATA_FOR_OBJ,           // returns DS_REPL_OBJECT_META_DATA *
    DS_REPL_INFO_KCC_DSA_CONNECT_FAILURES,   // both return
    DS_REPL_INFO_KCC_DSA_LINK_FAILURES,      //    DS_REPL_KCC_DSA_FAILURES *
    DS_REPL_INFO_PENDING_OPS,                // returns DS_REPL_PENDING_OPS *

    ////////////////////////////////////////////////////////////////////////////
    //
    //  The following info types are not supported by Windows 2000.  Calling
    //  DsReplicaGetInfo() with one of the types on a Windows 2000 client or
    //  where hDS is bound to a Windows 2000 DC will fail with
    //  ERROR_NOT_SUPPORTED.
    //

    DS_REPL_INFO_METADATA_FOR_ATTR_VALUE,   // returns DS_REPL_ATTR_VALUE_META_DATA *
    DS_REPL_INFO_CURSORS_2_FOR_NC,          // returns DS_REPL_CURSORS_2 *
    DS_REPL_INFO_CURSORS_3_FOR_NC,          // returns DS_REPL_CURSORS_3 *
    DS_REPL_INFO_METADATA_2_FOR_OBJ,        // returns DS_REPL_OBJECT_META_DATA_2 *
    DS_REPL_INFO_METADATA_2_FOR_ATTR_VALUE, // returns DS_REPL_ATTR_VALUE_META_DATA_2 *

    // <- insert new DS_REPL_INFO_* types here.

    DS_REPL_INFO_TYPE_MAX);
  {$EXTERNALSYM _DS_REPL_INFO_TYPE}
  DS_REPL_INFO_TYPE = _DS_REPL_INFO_TYPE;
  {$EXTERNALSYM DS_REPL_INFO_TYPE}
  TDsReplInfoType = DS_REPL_INFO_TYPE;

// Bit values for flags argument to DsReplicaGetInfo2

const
  DS_REPL_INFO_FLAG_IMPROVE_LINKED_ATTRS    =  $00000001;
  {$EXTERNALSYM DS_REPL_INFO_FLAG_IMPROVE_LINKED_ATTRS}

// Bit values for the dwReplicaFlags field of the DS_REPL_NEIGHBOR structure.

// Bit values for the dwReplicaFlags field of the DS_REPL_NEIGHBOR structure.
// Also used for the ulReplicaFlags argument to DsReplicaModify

  DS_REPL_NBR_WRITEABLE                     = ($00000010);
  {$EXTERNALSYM DS_REPL_NBR_WRITEABLE}
  DS_REPL_NBR_SYNC_ON_STARTUP               = ($00000020);
  {$EXTERNALSYM DS_REPL_NBR_SYNC_ON_STARTUP}
  DS_REPL_NBR_DO_SCHEDULED_SYNCS            = ($00000040);
  {$EXTERNALSYM DS_REPL_NBR_DO_SCHEDULED_SYNCS}
  DS_REPL_NBR_USE_ASYNC_INTERSITE_TRANSPORT = ($00000080);
  {$EXTERNALSYM DS_REPL_NBR_USE_ASYNC_INTERSITE_TRANSPORT}
  DS_REPL_NBR_TWO_WAY_SYNC                  = ($00000200);
  {$EXTERNALSYM DS_REPL_NBR_TWO_WAY_SYNC}
  DS_REPL_NBR_RETURN_OBJECT_PARENTS         = ($00000800);
  {$EXTERNALSYM DS_REPL_NBR_RETURN_OBJECT_PARENTS}
  DS_REPL_NBR_FULL_SYNC_IN_PROGRESS         = ($00010000);
  {$EXTERNALSYM DS_REPL_NBR_FULL_SYNC_IN_PROGRESS}
  DS_REPL_NBR_FULL_SYNC_NEXT_PACKET         = ($00020000);
  {$EXTERNALSYM DS_REPL_NBR_FULL_SYNC_NEXT_PACKET}
  DS_REPL_NBR_NEVER_SYNCED                  = ($00200000);
  {$EXTERNALSYM DS_REPL_NBR_NEVER_SYNCED}
  DS_REPL_NBR_PREEMPTED                     = ($01000000);
  {$EXTERNALSYM DS_REPL_NBR_PREEMPTED}
  DS_REPL_NBR_IGNORE_CHANGE_NOTIFICATIONS   = ($04000000);
  {$EXTERNALSYM DS_REPL_NBR_IGNORE_CHANGE_NOTIFICATIONS}
  DS_REPL_NBR_DISABLE_SCHEDULED_SYNC        = ($08000000);
  {$EXTERNALSYM DS_REPL_NBR_DISABLE_SCHEDULED_SYNC}
  DS_REPL_NBR_COMPRESS_CHANGES              = ($10000000);
  {$EXTERNALSYM DS_REPL_NBR_COMPRESS_CHANGES}
  DS_REPL_NBR_NO_CHANGE_NOTIFICATIONS       = ($20000000);
  {$EXTERNALSYM DS_REPL_NBR_NO_CHANGE_NOTIFICATIONS}
  DS_REPL_NBR_PARTIAL_ATTRIBUTE_SET         = ($40000000);
  {$EXTERNALSYM DS_REPL_NBR_PARTIAL_ATTRIBUTE_SET}

// This is the mask of replica flags that may be changed on the DsReplicaModify
// call using the ulReplicaFlags parameter. The other flags are protected
// system flags.  The previous values of the system flags must be read in
// advance and merged into the ulReplicaFlags parameter unchanged.

  DS_REPL_NBR_MODIFIABLE_MASK =
        DS_REPL_NBR_SYNC_ON_STARTUP or
        DS_REPL_NBR_DO_SCHEDULED_SYNCS or
        DS_REPL_NBR_TWO_WAY_SYNC or
        DS_REPL_NBR_IGNORE_CHANGE_NOTIFICATIONS or
        DS_REPL_NBR_DISABLE_SCHEDULED_SYNC or
        DS_REPL_NBR_COMPRESS_CHANGES or
        DS_REPL_NBR_NO_CHANGE_NOTIFICATIONS;
  {$EXTERNALSYM DS_REPL_NBR_MODIFIABLE_MASK}

type
  _DS_REPL_NEIGHBORW = record
    pszNamingContext: LPWSTR;
    pszSourceDsaDN: LPWSTR;
    pszSourceDsaAddress: LPWSTR;
    pszAsyncIntersiteTransportDN: LPWSTR;
    dwReplicaFlags: DWORD;
    dwReserved: DWORD; // alignment
    uuidNamingContextObjGuid: UUID;
    uuidSourceDsaObjGuid: UUID;
    uuidSourceDsaInvocationID: UUID;
    uuidAsyncIntersiteTransportObjGuid: UUID;
    usnLastObjChangeSynced: USN;
    usnAttributeFilter: USN;
    ftimeLastSyncSuccess: FILETIME;
    ftimeLastSyncAttempt: FILETIME;
    dwLastSyncResult: DWORD;
    cNumConsecutiveSyncFailures: DWORD;
  end;
  {$EXTERNALSYM _DS_REPL_NEIGHBORW}
  DS_REPL_NEIGHBORW = _DS_REPL_NEIGHBORW;
  {$EXTERNALSYM DS_REPL_NEIGHBORW}
  TDsReplNeighborW = DS_REPL_NEIGHBORW;
  PDsReplNeighborW = ^DS_REPL_NEIGHBORW;

// Fields can be added only to the end of this structure.

  _DS_REPL_NEIGHBORW_BLOB = record
    oszNamingContext: DWORD;
    oszSourceDsaDN: DWORD;
    oszSourceDsaAddress: DWORD;
    oszAsyncIntersiteTransportDN: DWORD;
    dwReplicaFlags: DWORD;
    dwReserved: DWORD;

    uuidNamingContextObjGuid: UUID;
    uuidSourceDsaObjGuid: UUID;
    uuidSourceDsaInvocationID: UUID;
    uuidAsyncIntersiteTransportObjGuid: UUID;

    usnLastObjChangeSynced: USN;
    usnAttributeFilter: USN;

    ftimeLastSyncSuccess: FILETIME;
    ftimeLastSyncAttempt: FILETIME;

    dwLastSyncResult: DWORD;
    cNumConsecutiveSyncFailures: DWORD;
  end;
  {$EXTERNALSYM _DS_REPL_NEIGHBORW_BLOB}
  DS_REPL_NEIGHBORW_BLOB = _DS_REPL_NEIGHBORW_BLOB;
  {$EXTERNALSYM DS_REPL_NEIGHBORW_BLOB}
  TDsReplNeighborwBlob = DS_REPL_NEIGHBORW_BLOB;
  PDsReplNeighborwBlob = ^DS_REPL_NEIGHBORW_BLOB;  

  _DS_REPL_NEIGHBORSW = record
    cNumNeighbors: DWORD;
    dwReserved: DWORD; // alignment
    rgNeighbor: array [0..0] of DS_REPL_NEIGHBORW;
  end;
  {$EXTERNALSYM _DS_REPL_NEIGHBORSW}
  DS_REPL_NEIGHBORSW = _DS_REPL_NEIGHBORSW;
  {$EXTERNALSYM DS_REPL_NEIGHBORSW}
  TDsReplNeighborsW = DS_REPL_NEIGHBORSW;
  PDsReplNeighborsW = ^DS_REPL_NEIGHBORSW;

  _DS_REPL_CURSOR = record
    uuidSourceDsaInvocationID: UUID;
    usnAttributeFilter: USN;
  end;
  {$EXTERNALSYM _DS_REPL_CURSOR}
  DS_REPL_CURSOR = _DS_REPL_CURSOR;
  {$EXTERNALSYM DS_REPL_CURSOR}
  TDsReplCursor = DS_REPL_CURSOR;
  PDsReplCursor = ^DS_REPL_CURSOR;

  _DS_REPL_CURSOR_2 = record
    uuidSourceDsaInvocationID: UUID;
    usnAttributeFilter: USN;
    ftimeLastSyncSuccess: FILETIME;
  end;
  {$EXTERNALSYM _DS_REPL_CURSOR_2}
  DS_REPL_CURSOR_2 = _DS_REPL_CURSOR_2;
  {$EXTERNALSYM DS_REPL_CURSOR_2}
  TDsReplCursor2 = DS_REPL_CURSOR_2;
  PDsReplCursor2 = ^DS_REPL_CURSOR_2;

  _DS_REPL_CURSOR_3W = record
    uuidSourceDsaInvocationID: UUID;
    usnAttributeFilter: USN;
    ftimeLastSyncSuccess: FILETIME;
    pszSourceDsaDN: LPWSTR;
  end;
  {$EXTERNALSYM _DS_REPL_CURSOR_3W}
  DS_REPL_CURSOR_3W = _DS_REPL_CURSOR_3W;
  {$EXTERNALSYM DS_REPL_CURSOR_3W}
  TDsReplCursow3W = DS_REPL_CURSOR_3W;
  PDsReplCursow3W = ^DS_REPL_CURSOR_3W;

// Fields can be added only to the end of this structure.

  _DS_REPL_CURSOR_BLOB = record
    uuidSourceDsaInvocationID: UUID;
    usnAttributeFilter: USN;
    ftimeLastSyncSuccess: FILETIME;
    oszSourceDsaDN: DWORD;
  end;
  {$EXTERNALSYM _DS_REPL_CURSOR_BLOB}
  DS_REPL_CURSOR_BLOB = _DS_REPL_CURSOR_BLOB;
  {$EXTERNALSYM DS_REPL_CURSOR_BLOB}
  TDsReplCursorBlob = DS_REPL_CURSOR_BLOB;
  PDsReplCursorBlob = ^DS_REPL_CURSOR_BLOB;  

  _DS_REPL_CURSORS = record
    cNumCursors: DWORD;
    dwReserved: DWORD; // alignment
    rgCursor: array [0..0] of DS_REPL_CURSOR;
  end;
  {$EXTERNALSYM _DS_REPL_CURSORS}
  DS_REPL_CURSORS = _DS_REPL_CURSORS;
  {$EXTERNALSYM DS_REPL_CURSORS}
  TDsReplCursors = DS_REPL_CURSORS;
  PDsReplCursors = ^DS_REPL_CURSORS;

  _DS_REPL_CURSORS_2 = record
    cNumCursors: DWORD;
    dwEnumerationContext: DWORD;
    // keep this 8 byte aligned
    rgCursor: array [0..0] of DS_REPL_CURSOR_2;
  end;
  {$EXTERNALSYM _DS_REPL_CURSORS_2}
  DS_REPL_CURSORS_2 = _DS_REPL_CURSORS_2;
  {$EXTERNALSYM DS_REPL_CURSORS_2}
  TDsReplCursors2 = DS_REPL_CURSORS_2;
  PDsReplCursors2 = ^DS_REPL_CURSORS_2;

  _DS_REPL_CURSORS_3W = record
    cNumCursors: DWORD;
    dwEnumerationContext: DWORD;
    // keep this 8 byte aligned
    rgCursor: array [0..0] of DS_REPL_CURSOR_3W;
  end;
  {$EXTERNALSYM _DS_REPL_CURSORS_3W}
  DS_REPL_CURSORS_3W = _DS_REPL_CURSORS_3W;
  {$EXTERNALSYM DS_REPL_CURSORS_3W}
  TDsReplCursors3W = DS_REPL_CURSORS_3W;
  PDsReplCursors3W = ^DS_REPL_CURSORS_3W;  

  _DS_REPL_ATTR_META_DATA = record
    pszAttributeName: LPWSTR;
    dwVersion: DWORD;
    ftimeLastOriginatingChange: FILETIME;
    uuidLastOriginatingDsaInvocationID: UUID;
    usnOriginatingChange: USN; // in the originating DSA's USN space
    usnLocalChange: USN; // in the local DSA's USN space
  end;
  {$EXTERNALSYM _DS_REPL_ATTR_META_DATA}
  DS_REPL_ATTR_META_DATA = _DS_REPL_ATTR_META_DATA;
  {$EXTERNALSYM DS_REPL_ATTR_META_DATA}
  TDsReplAttrMetaData = DS_REPL_ATTR_META_DATA;
  PDsReplAttrMetaData = ^DS_REPL_ATTR_META_DATA;

  _DS_REPL_ATTR_META_DATA_2 = record
    pszAttributeName: LPWSTR;
    dwVersion: DWORD;
    ftimeLastOriginatingChange: FILETIME;
    uuidLastOriginatingDsaInvocationID: UUID;
    usnOriginatingChange: USN;   // in the originating DSA's USN space
    usnLocalChange: USN;         // in the local DSA's USN space
    pszLastOriginatingDsaDN: LPWSTR;
  end;
  {$EXTERNALSYM _DS_REPL_ATTR_META_DATA_2}
  DS_REPL_ATTR_META_DATA_2 = _DS_REPL_ATTR_META_DATA_2;
  {$EXTERNALSYM DS_REPL_ATTR_META_DATA_2}
  TDsReplAttrMetaData2 = DS_REPL_ATTR_META_DATA_2;
  PDsReplAttrMetaData2 = ^DS_REPL_ATTR_META_DATA_2;

// Fields can be added only to the end of this structure.

  _DS_REPL_ATTR_META_DATA_BLOB = record
    oszAttributeName: DWORD;
    dwVersion: DWORD;
    ftimeLastOriginatingChange: FILETIME;
    uuidLastOriginatingDsaInvocationID: UUID;
    usnOriginatingChange: USN;   // in the originating DSA's USN space
    usnLocalChange: USN;         // in the local DSA's USN space
    oszLastOriginatingDsaDN: DWORD;
  end;
  {$EXTERNALSYM _DS_REPL_ATTR_META_DATA_BLOB}
  DS_REPL_ATTR_META_DATA_BLOB = _DS_REPL_ATTR_META_DATA_BLOB;
  {$EXTERNALSYM DS_REPL_ATTR_META_DATA_BLOB}
  TDsReplAttrMetaDataBlob = DS_REPL_ATTR_META_DATA_BLOB;
  PDsReplAttrMetaDataBlob = ^DS_REPL_ATTR_META_DATA_BLOB;  

  _DS_REPL_OBJ_META_DATA = record
    cNumEntries: DWORD;
    dwReserved: DWORD; // alignment
    rgMetaData: array [0..0] of DS_REPL_ATTR_META_DATA;
  end;
  {$EXTERNALSYM _DS_REPL_OBJ_META_DATA}
  DS_REPL_OBJ_META_DATA = _DS_REPL_OBJ_META_DATA;
  {$EXTERNALSYM DS_REPL_OBJ_META_DATA}
  TDsReplObjMetaData = DS_REPL_OBJ_META_DATA;
  PDsReplObjMetaData = ^DS_REPL_OBJ_META_DATA;

  _DS_REPL_OBJ_META_DATA_2 = record
    cNumEntries: DWORD;
    dwReserved: DWORD;             // alignment
    rgMetaData: array [0..0] of DS_REPL_ATTR_META_DATA_2;
  end;
  {$EXTERNALSYM _DS_REPL_OBJ_META_DATA_2}
  DS_REPL_OBJ_META_DATA_2 = _DS_REPL_OBJ_META_DATA_2;
  {$EXTERNALSYM DS_REPL_OBJ_META_DATA_2}
  TDsReplObjMetaData2 = DS_REPL_OBJ_META_DATA_2;
  PDsReplObjMetaData2 = ^DS_REPL_OBJ_META_DATA_2;  

  _DS_REPL_KCC_DSA_FAILUREW = record
    pszDsaDN: LPWSTR;
    uuidDsaObjGuid: UUID;
    ftimeFirstFailure: FILETIME;
    cNumFailures: DWORD;
    dwLastResult: DWORD; // Win32 error code
  end;
  {$EXTERNALSYM _DS_REPL_KCC_DSA_FAILUREW}
  DS_REPL_KCC_DSA_FAILUREW = _DS_REPL_KCC_DSA_FAILUREW;
  {$EXTERNALSYM DS_REPL_KCC_DSA_FAILUREW}
  TDsReplKccDsaFailureW = DS_REPL_KCC_DSA_FAILUREW;
  PDsReplKccDsaFailureW = ^DS_REPL_KCC_DSA_FAILUREW;

// Fields can be added only to the end of this structure.

  _DS_REPL_KCC_DSA_FAILUREW_BLOB = record
    oszDsaDN: DWORD;
    uuidDsaObjGuid: UUID;
    ftimeFirstFailure: FILETIME;
    cNumFailures: DWORD;
    dwLastResult: DWORD;   // Win32 error code
  end;
  {$EXTERNALSYM _DS_REPL_KCC_DSA_FAILUREW_BLOB}
  DS_REPL_KCC_DSA_FAILUREW_BLOB = _DS_REPL_KCC_DSA_FAILUREW_BLOB;
  {$EXTERNALSYM DS_REPL_KCC_DSA_FAILUREW_BLOB}
  TDsReplKccDsaFailureWBlob = DS_REPL_KCC_DSA_FAILUREW_BLOB;
  PDsReplKccDsaFailureWBlob = ^DS_REPL_KCC_DSA_FAILUREW_BLOB;  

  _DS_REPL_KCC_DSA_FAILURESW = record
    cNumEntries: DWORD;
    dwReserved: DWORD; // alignment
    rgDsaFailure: array [0..0] of DS_REPL_KCC_DSA_FAILUREW;
  end;
  {$EXTERNALSYM _DS_REPL_KCC_DSA_FAILURESW}
  DS_REPL_KCC_DSA_FAILURESW = _DS_REPL_KCC_DSA_FAILURESW;
  {$EXTERNALSYM DS_REPL_KCC_DSA_FAILURESW}
  TDsReplKccDsaFailuresW = DS_REPL_KCC_DSA_FAILURESW;
  PDsReplKccDsaFailuresW = ^DS_REPL_KCC_DSA_FAILURESW;

  _DS_REPL_OP_TYPE = (
    DS_REPL_OP_TYPE_SYNC,
    DS_REPL_OP_TYPE_ADD,
    DS_REPL_OP_TYPE_DELETE,
    DS_REPL_OP_TYPE_MODIFY,
    DS_REPL_OP_TYPE_UPDATE_REFS);
  {$EXTERNALSYM _DS_REPL_OP_TYPE}
  DS_REPL_OP_TYPE = _DS_REPL_OP_TYPE;
  {$EXTERNALSYM DS_REPL_OP_TYPE}

  _DS_REPL_OPW = record
    ftimeEnqueued: FILETIME; // time at which the operation was enqueued
    ulSerialNumber: ULONG; // ID of this sync; unique per machine per boot
    ulPriority: ULONG; // > priority, > urgency
    OpType: DS_REPL_OP_TYPE;
    ulOptions: ULONG; // Zero or more bits specific to OpType; e.g.,
    //  DS_REPADD_* for DS_REPL_OP_TYPE_ADD,
    //  DS_REPSYNC_* for DS_REPL_OP_TYPE_SYNC, etc.
    pszNamingContext: LPWSTR;
    pszDsaDN: LPWSTR;
    pszDsaAddress: LPWSTR;
    uuidNamingContextObjGuid: UUID;
    uuidDsaObjGuid: UUID;
  end;
  {$EXTERNALSYM _DS_REPL_OPW}
  DS_REPL_OPW = _DS_REPL_OPW;
  {$EXTERNALSYM DS_REPL_OPW}
  TDsReplOpW = DS_REPL_OPW;
  PDsReplOpW = ^DS_REPL_OPW;

// Fields can be added only to the end of this structure.

  _DS_REPL_OPW_BLOB = record
    ftimeEnqueued: FILETIME;  // time at which the operation was enqueued
    ulSerialNumber: ULONG; // ID of this sync; unique per machine per boot
    ulPriority: ULONG;     // > priority, > urgency
    OpType: DS_REPL_OP_TYPE;

    ulOptions: ULONG;      // Zero or more bits specific to OpType; e.g.,
                           //  DS_REPADD_* for DS_REPL_OP_TYPE_ADD,
                           //  DS_REPSYNC_* for DS_REPL_OP_TYPE_SYNC, etc.
    oszNamingContext: DWORD;
    oszDsaDN: DWORD;
    oszDsaAddress: DWORD;

    uuidNamingContextObjGuid: UUID;
    uuidDsaObjGuid: UUID;
  end;
  {$EXTERNALSYM _DS_REPL_OPW_BLOB}
  DS_REPL_OPW_BLOB = _DS_REPL_OPW_BLOB;
  {$EXTERNALSYM DS_REPL_OPW_BLOB}
  TDsReplOpwBlob = DS_REPL_OPW_BLOB;
  PDsReplOpwBlob = ^DS_REPL_OPW_BLOB;

  _DS_REPL_PENDING_OPSW = record
    ftimeCurrentOpStarted: FILETIME;
    cNumPendingOps: DWORD;
    rgPendingOp: array [0..0] of DS_REPL_OPW;
  end;
  {$EXTERNALSYM _DS_REPL_PENDING_OPSW}
  DS_REPL_PENDING_OPSW = _DS_REPL_PENDING_OPSW;
  {$EXTERNALSYM DS_REPL_PENDING_OPSW}
  TDsReplPendingOpsW = DS_REPL_PENDING_OPSW;
  PDsReplPendingOpsW = ^DS_REPL_PENDING_OPSW;

  _DS_REPL_VALUE_META_DATA = record
    pszAttributeName: LPWSTR;
    pszObjectDn: LPWSTR;
    cbData: DWORD;
    pbData: LPBYTE;
    ftimeDeleted: FILETIME;
    ftimeCreated: FILETIME;
    dwVersion: DWORD;
    ftimeLastOriginatingChange: FILETIME;
    uuidLastOriginatingDsaInvocationID: UUID;
    usnOriginatingChange: USN;   // in the originating DSA's USN space
    usnLocalChange: USN;         // in the local DSA's USN space
  end;
  {$EXTERNALSYM _DS_REPL_VALUE_META_DATA}
  DS_REPL_VALUE_META_DATA = _DS_REPL_VALUE_META_DATA;
  {$EXTERNALSYM DS_REPL_VALUE_META_DATA}
  TDsReplValueMetaData = DS_REPL_VALUE_META_DATA;
  PDsReplValueMetaData = ^DS_REPL_VALUE_META_DATA;  

  _DS_REPL_VALUE_META_DATA_2 = record
    pszAttributeName: LPWSTR;
    pszObjectDn: LPWSTR;
    cbData: DWORD;
    pbData: LPBYTE;
    ftimeDeleted: FILETIME;
    ftimeCreated: FILETIME;
    dwVersion: DWORD;
    ftimeLastOriginatingChange: FILETIME;
    uuidLastOriginatingDsaInvocationID: UUID;
    usnOriginatingChange: USN;   // in the originating DSA's USN space
    usnLocalChange: USN;         // in the local DSA's USN space
    pszLastOriginatingDsaDN: LPWSTR;
  end;
  {$EXTERNALSYM _DS_REPL_VALUE_META_DATA_2}
  DS_REPL_VALUE_META_DATA_2 = _DS_REPL_VALUE_META_DATA_2;
  {$EXTERNALSYM DS_REPL_VALUE_META_DATA_2}
  TDsReplValueMetaData2 = DS_REPL_VALUE_META_DATA_2;
  PDsReplValueMetaData2 = ^DS_REPL_VALUE_META_DATA_2;

// Fields can be added only to the end of this structure.

  _DS_REPL_VALUE_META_DATA_BLOB = record
    oszAttributeName: DWORD;
    oszObjectDn: DWORD;
    cbData: DWORD;
    obData: DWORD;
    ftimeDeleted: FILETIME;
    ftimeCreated: FILETIME;
    dwVersion: DWORD;
    ftimeLastOriginatingChange: FILETIME;
    uuidLastOriginatingDsaInvocationID: UUID;
    usnOriginatingChange: USN;   // in the originating DSA's USN space
    usnLocalChange: USN;         // in the local DSA's USN space
    oszLastOriginatingDsaDN: DWORD;
  end;
  {$EXTERNALSYM _DS_REPL_VALUE_META_DATA_BLOB}
  DS_REPL_VALUE_META_DATA_BLOB = _DS_REPL_VALUE_META_DATA_BLOB;
  {$EXTERNALSYM DS_REPL_VALUE_META_DATA_BLOB}
  TDsReplValueMetaDataBlob = DS_REPL_VALUE_META_DATA_BLOB;
  PsReplValueMetaDataBlob =  ^DS_REPL_VALUE_META_DATA_BLOB;
  
  _DS_REPL_ATTR_VALUE_META_DATA = record
    cNumEntries: DWORD;
    dwEnumerationContext: DWORD;
    rgMetaData: array [0..0] of DS_REPL_VALUE_META_DATA;
  end;
  {$EXTERNALSYM _DS_REPL_ATTR_VALUE_META_DATA}
  DS_REPL_ATTR_VALUE_META_DATA = _DS_REPL_ATTR_VALUE_META_DATA;
  {$EXTERNALSYM DS_REPL_ATTR_VALUE_META_DATA}
  TDsReplAttrValueMetaData = DS_REPL_ATTR_VALUE_META_DATA;
  PDsReplAttrValueMetaData = ^DS_REPL_ATTR_VALUE_META_DATA;

  _DS_REPL_ATTR_VALUE_META_DATA_2 = record
    cNumEntries: DWORD;
    dwEnumerationContext: DWORD;
    rgMetaData: array [0..0] of DS_REPL_VALUE_META_DATA_2;
  end;
  {$EXTERNALSYM _DS_REPL_ATTR_VALUE_META_DATA_2}
  DS_REPL_ATTR_VALUE_META_DATA_2 = _DS_REPL_ATTR_VALUE_META_DATA_2;
  {$EXTERNALSYM DS_REPL_ATTR_VALUE_META_DATA_2}
  TDsReplAttrValueMetaData2 = DS_REPL_ATTR_VALUE_META_DATA_2;
  PDsReplAttrValueMetaData2 = ^DS_REPL_ATTR_VALUE_META_DATA_2;  

  _DS_REPL_QUEUE_STATISTICSW = record
    ftimeCurrentOpStarted: FILETIME;
    cNumPendingOps: DWORD;
    ftimeOldestSync: FILETIME;
    ftimeOldestAdd: FILETIME;
    ftimeOldestMod: FILETIME;
    ftimeOldestDel: FILETIME;
    ftimeOldestUpdRefs: FILETIME;
  end;
  {$EXTERNALSYM _DS_REPL_QUEUE_STATISTICSW}
  DS_REPL_QUEUE_STATISTICSW = _DS_REPL_QUEUE_STATISTICSW;
  {$EXTERNALSYM DS_REPL_QUEUE_STATISTICSW}
  TDsReplQueueStatisticsW = DS_REPL_QUEUE_STATISTICSW;
  PDsReplQueueStatisticsW = ^DS_REPL_QUEUE_STATISTICSW;  

// Fields can be added only to the end of this structure.

  DS_REPL_QUEUE_STATISTICSW_BLOB = _DS_REPL_QUEUE_STATISTICSW;
  {$EXTERNALSYM DS_REPL_QUEUE_STATISTICSW_BLOB}
  TDsReplQueueStatisticsWBlob = DS_REPL_QUEUE_STATISTICSW_BLOB;

function DsReplicaGetInfoW(hDS: HANDLE; InfoType: DS_REPL_INFO_TYPE;
  pszObject: LPCWSTR; puuidForSourceDsaObjGuid: LPUUID; ppInfo: PPVOID): DWORD; stdcall;
{$EXTERNALSYM DsReplicaGetInfoW}

procedure DsReplicaFreeInfo(InfoType: DS_REPL_INFO_TYPE; pInfo: PVOID); stdcall;
{$EXTERNALSYM DsReplicaFreeInfo}

{$IFDEF UNICODE}

function DsReplicaGetInfo(hDS: HANDLE; InfoType: DS_REPL_INFO_TYPE;
  pszObject: LPCWSTR; puuidForSourceDsaObjGuid: LPUUID; ppInfo: PPVOID): DWORD; stdcall;
{$EXTERNALSYM DsReplicaGetInfo}

// This API is not supported by Windows 2000 clients or Windows 2000 DCs.

function DsReplicaGetInfo2W(hDS: HANDLE; InfoType: DS_REPL_INFO_TYPE; pszObject: LPCWSTR; const puuidForSourceDsaObjGuid: UUID; pszAttributeName,
  pszValue: LPCWSTR; dwFlags, dwEnumerationContext: DWORD; var ppInfo: LPVOID): DWORD; stdcall;
{$EXTERNALSYM DsReplicaGetInfo2W}

type
  DS_REPL_NEIGHBOR         = DS_REPL_NEIGHBORW;
  {$EXTERNALSYM DS_REPL_NEIGHBOR}
  DS_REPL_NEIGHBORS        = DS_REPL_NEIGHBORSW;
  {$EXTERNALSYM DS_REPL_NEIGHBORS}
  DS_REPL_CURSOR_3         = DS_REPL_CURSOR_3W;
  {$EXTERNALSYM DS_REPL_CURSOR_3}
  DS_REPL_CURSORS_3        = DS_REPL_CURSORS_3W;
  {$EXTERNALSYM DS_REPL_CURSORS_3}
  DS_REPL_KCC_DSA_FAILURES = DS_REPL_KCC_DSA_FAILURESW;
  {$EXTERNALSYM DS_REPL_KCC_DSA_FAILURES}
  DS_REPL_KCC_DSA_FAILURE  = DS_REPL_KCC_DSA_FAILUREW;
  {$EXTERNALSYM DS_REPL_KCC_DSA_FAILURE}
  DS_REPL_OP               = DS_REPL_OPW;
  {$EXTERNALSYM DS_REPL_OP}
  DS_REPL_PENDING_OPS      = DS_REPL_PENDING_OPSW;
  {$EXTERNALSYM DS_REPL_PENDING_OPS}
  TDsReplNeighbor = TDsReplNeighborW;
  TDsReplNeighbors = TDsReplNeighborsW;
  TDsReplCursors3 = TDsReplCursors3W;
  TDsReplKccDsaFailures = TDsReplKccDsaFailuresW;
  TDsReplKccDsaFailure = TDsReplKccDsaFailureW;
  TDsReplOp = TDsReplOpW;
  TDsReplPendingOps = TDsReplPendingOpsW;
{$ELSE}
// No ANSI equivalents currently supported.
{$ENDIF}

function DsAddSidHistoryA(hDS: HANDLE; Flags: DWORD; SrcDomain: LPCSTR;
  SrcPrincipal: LPCSTR; SrcDomainController: LPCSTR;
  SrcDomainCreds: RPC_AUTH_IDENTITY_HANDLE; DstDomain: LPCSTR;
  DstPrincipal: LPCSTR): DWORD; stdcall;
{$EXTERNALSYM DsAddSidHistoryA}
function DsAddSidHistoryW(hDS: HANDLE; Flags: DWORD; SrcDomain: LPCWSTR;
  SrcPrincipal: LPCWSTR; SrcDomainController: LPCWSTR;
  SrcDomainCreds: RPC_AUTH_IDENTITY_HANDLE; DstDomain: LPCWSTR;
  DstPrincipal: LPCWSTR): DWORD; stdcall;
{$EXTERNALSYM DsAddSidHistoryW}

{$IFDEF UNICODE}
function DsAddSidHistory(hDS: HANDLE; Flags: DWORD; SrcDomain: LPCWSTR;
  SrcPrincipal: LPCWSTR; SrcDomainController: LPCWSTR;
  SrcDomainCreds: RPC_AUTH_IDENTITY_HANDLE; DstDomain: LPCWSTR;
  DstPrincipal: LPCWSTR): DWORD; stdcall;
{$EXTERNALSYM DsAddSidHistory}
{$ELSE}
function DsAddSidHistory(hDS: HANDLE; Flags: DWORD; SrcDomain: LPCSTR;
  SrcPrincipal: LPCSTR; SrcDomainController: LPCSTR;
  SrcDomainCreds: RPC_AUTH_IDENTITY_HANDLE; DstDomain: LPCSTR;
  DstPrincipal: LPCSTR): DWORD; stdcall;
{$EXTERNALSYM DsAddSidHistory}
{$ENDIF}

// The DsInheritSecurityIdentity API adds the source principal's SID and
// SID history to the destination principal's SID history and then DELETES
// THE SOURCE PRINCIPAL.  Source and destination principal must be in the
// same domain.

function DsInheritSecurityIdentityA(hDS: HANDLE; Flags: DWORD;
  SrcPrincipal: LPCSTR; DstPrincipal: LPCSTR): DWORD; stdcall;
{$EXTERNALSYM DsInheritSecurityIdentityA}
function DsInheritSecurityIdentityW(hDS: HANDLE; Flags: DWORD;
  SrcPrincipal: LPCWSTR; DstPrincipal: LPCWSTR): DWORD; stdcall;
{$EXTERNALSYM DsInheritSecurityIdentityW}

{$IFDEF UNICODE}
function DsInheritSecurityIdentity(hDS: HANDLE; Flags: DWORD;
  SrcPrincipal: LPCWSTR; DstPrincipal: LPCWSTR): DWORD; stdcall;
{$EXTERNALSYM DsInheritSecurityIdentity}
{$ELSE}
function DsInheritSecurityIdentity(hDS: HANDLE; Flags: DWORD;
  SrcPrincipal: LPCSTR; DstPrincipal: LPCSTR): DWORD; stdcall;
{$EXTERNALSYM DsInheritSecurityIdentity}
{$ENDIF}

{ifndef MIDL_PASS
/*++
==========================================================
NTDSAPI
DWORD
WINAPI
DsQuoteRdnValue(
    IN     DWORD    cUnquotedRdnValueLength,
    IN     LPCTCH   psUnquotedRdnValue,
    IN OUT DWORD    *pcQuotedRdnValueLength,
    OUT    LPTCH    psQuotedRdnValue
    )
++

Description

    This client call converts an RDN value into a quoted RDN value if
    the RDN value contains characters that require quotes. The resultant
    RDN can be submitted as part of a DN to the DS using various APIs
    such as LDAP.

    No quotes are added if none are needed. In this case, the
    output RDN value will be the same as the input RDN value.

    The RDN is quoted in accordance with the specification "Lightweight
    Directory Access Protocol (v3): UTF-8 String Representation of
    Distinguished Names", RFC 2253.

    The input and output RDN values are *NOT* NULL terminated.

    The changes made by this call can be undone by calling
    DsUnquoteRdnValue().

Arguments:

    cUnquotedRdnValueLength - The length of psUnquotedRdnValue in chars.

    psUnquotedRdnValue - Unquoted RDN value.

    pcQuotedRdnValueeLength - IN, maximum length of psQuotedRdnValue, in chars
                        OUT ERROR_SUCCESS, chars utilized in psQuotedRdnValue
                        OUT ERROR_BUFFER_OVERFLOW, chars needed in psQuotedRdnValue

    psQuotedRdnValue - The resultant and perhaps quoted RDN value

Return Value:
    ERROR_SUCCESS
        If quotes or escapes were needed, then psQuotedRdnValue contains
        the quoted, escaped version of psUnquotedRdnValue. Otherwise,
        psQuotedRdnValue contains a copy of psUnquotedRdnValue. In either
        case, pcQuotedRdnValueLength contains the space utilized, in chars.

    ERROR_BUFFER_OVERFLOW
        psQuotedRdnValueLength contains the space needed, in chars,
        to hold psQuotedRdnValue.

    ERROR_INVALID_PARAMETER
        Invalid parameter.

    ERROR_NOT_ENOUGH_MEMORY
        Allocation error.

--}

function DsQuoteRdnValueA(cUnquotedRdnValueLength: DWORD;
  psUnquotedRdnValue: LPCCH; var pcQuotedRdnValueLength: DWORD;
  psQuotedRdnValue: LPCH): DWORD; stdcall;
{$EXTERNALSYM DsQuoteRdnValueA}
function DsQuoteRdnValueW(cUnquotedRdnValueLength: DWORD;
  psUnquotedRdnValue: LPCWCH; var pcQuotedRdnValueLength: DWORD;
  psQuotedRdnValue: LPWCH): DWORD; stdcall;
{$EXTERNALSYM DsQuoteRdnValueW}

{$IFDEF UNICODE}
function DsQuoteRdnValue(cUnquotedRdnValueLength: DWORD;
  psUnquotedRdnValue: LPCWCH; var pcQuotedRdnValueLength: DWORD;
  psQuotedRdnValue: LPWCH): DWORD; stdcall;
{$EXTERNALSYM DsQuoteRdnValue}
{$ELSE}
function DsQuoteRdnValue(cUnquotedRdnValueLength: DWORD;
  psUnquotedRdnValue: LPCCH; var pcQuotedRdnValueLength: DWORD;
  psQuotedRdnValue: LPCH): DWORD; stdcall;
{$EXTERNALSYM DsQuoteRdnValue}
{$ENDIF}

{++
==========================================================
NTDSAPI
DWORD
WINAPI
DsUnquoteRdnValue(
    IN     DWORD    cQuotedRdnValueLength,
    IN     LPCTCH   psQuotedRdnValue,
    IN OUT DWORD    *pcUnquotedRdnValueLength,
    OUT    LPTCH    psUnquotedRdnValue
    )

Description

    This client call converts a quoted RDN Value into an unquoted RDN
    Value. The resultant RDN value should *NOT* be submitted as part
    of a DN to the DS using various APIs such as LDAP.

    When psQuotedRdnValue is quoted:
        The leading and trailing quote are removed.

        Whitespace before the first quote is discarded.

        Whitespace trailing the last quote is discarded.

        Escapes are removed and the char following the escape is kept.

    The following actions are taken when psQuotedRdnValue is unquoted:

        Leading whitespace is discarded.

        Trailing whitespace is kept.

        Escaped non-special chars return an error.

        Unescaped special chars return an error.

        RDN values beginning with # (ignoring leading whitespace) are
        treated as a stringized BER value and converted accordingly.

        Escaped hex digits (\89) are converted into a binary byte (0x89).

        Escapes are removed from escaped special chars.

    The following actions are always taken:
        Escaped special chars are unescaped.

    The input and output RDN values are not NULL terminated.

Arguments:

    cQuotedRdnValueLength - The length of psQuotedRdnValue in chars.

    psQuotedRdnValue - RDN value that may be quoted and may be escaped.

    pcUnquotedRdnValueLength - IN, maximum length of psUnquotedRdnValue, in chars
                          OUT ERROR_SUCCESS, chars used in psUnquotedRdnValue
                          OUT ERROR_BUFFER_OVERFLOW, chars needed for psUnquotedRdnValue

    psUnquotedRdnValue - The resultant unquoted RDN value.

Return Value:
    ERROR_SUCCESS
        psUnquotedRdnValue contains the unquoted and unescaped version
        of psQuotedRdnValue. pcUnquotedRdnValueLength contains the space
        used, in chars.

    ERROR_BUFFER_OVERFLOW
        psUnquotedRdnValueLength contains the space needed, in chars,
        to hold psUnquotedRdnValue.

    ERROR_INVALID_PARAMETER
        Invalid parameter.

    ERROR_NOT_ENOUGH_MEMORY
        Allocation error.

--}

function DsUnquoteRdnValueA(cQuotedRdnValueLength: DWORD; psQuotedRdnValue: LPCCH;
  var pcUnquotedRdnValueLength: DWORD; psUnquotedRdnValue: LPCH): DWORD; stdcall;
{$EXTERNALSYM DsUnquoteRdnValueA}
function DsUnquoteRdnValueW(cQuotedRdnValueLength: DWORD; psQuotedRdnValue: LPCWCH;
  var pcUnquotedRdnValueLength: DWORD; psUnquotedRdnValue: LPWCH): DWORD; stdcall;
{$EXTERNALSYM DsUnquoteRdnValueW}

{$IFDEF UNICODE}
function DsUnquoteRdnValue(cQuotedRdnValueLength: DWORD; psQuotedRdnValue: LPCWCH;
  var pcUnquotedRdnValueLength: DWORD; psUnquotedRdnValue: LPWCH): DWORD; stdcall;
{$EXTERNALSYM DsUnquoteRdnValue}
{$ELSE}
function DsUnquoteRdnValue(cQuotedRdnValueLength: DWORD; psQuotedRdnValue: LPCCH;
  var pcUnquotedRdnValueLength: DWORD; psUnquotedRdnValue: LPCH): DWORD; stdcall;
{$EXTERNALSYM DsUnquoteRdnValue}
{$ENDIF}

(*++
==========================================================
NTDSAPI
DWORD
WINAPI
DsGetRdnW(
    IN OUT LPCWCH   *ppDN,
    IN OUT DWORD    *pcDN,
    OUT    LPCWCH   *ppKey,
    OUT    DWORD    *pcKey,
    OUT    LPCWCH   *ppVal,
    OUT    DWORD    *pcVal
    )

Description

    This client call accepts a DN with quoted RDNs and returns the address
    and length, in chars, of the key and value for the first RDN in the DN.
    The RDN value returned is still quoted. Use DsUnquoteRdnValue to unquote
    the value for display.

    This client call also returns the address and length of the rest of the
    DN. A subsequent call using the returned DN address and length will
    return information about the next RDN.

    The following loop processes each RDN in pDN:
        ccDN = wcslen(pDN)
        while (ccDN) {
            error = DsGetRdn(&pDN,
                             &ccDN,
                             &pKey,
                             &ccKey,
                             &pVal,
                             &ccVal);
            if (error != ERROR_SUCCESS) {
                process error;
                return;
            }
            if (ccKey) {
                process pKey;
            }
            if (ccVal) {
                process pVal;
            }
        }

    For example, given the DN "cn=bob,dc=com", the first call to DsGetRdnW
    returns the addresses for ",dc=com", "cn", and "bob" with respective
    lengths of 7, 2, and 3. A subsequent call with ",dc=com" returns "",
    "dc", and "com" with respective lengths 0, 2, and 3.

Arguments:
    ppDN
        IN : *ppDN points to a DN
        OUT: *ppDN points to the rest of the DN following the first RDN
    pcDN
        IN : *pcDN is the count of chars in the input *ppDN, not including
             any terminating NULL
        OUT: *pcDN is the count of chars in the output *ppDN, not including
             any terminating NULL
    ppKey
        OUT: Undefined if *pcKey is 0. Otherwise, *ppKey points to the first
             key in the DN
    pcKey
        OUT: *pcKey is the count of chars in *ppKey.

    ppVal
        OUT: Undefined if *pcVal is 0. Otherwise, *ppVal points to the first
             value in the DN
    pcVal
        OUT: *pcVal is the count of chars in *ppVal

Return Value:
    ERROR_SUCCESS
        If *pccDN is not 0, then *ppDN points to the rest of the DN following
        the first RDN. If *pccDN is 0, then *ppDN is undefined.

        If *pccKey is not 0, then *ppKey points to the first key in DN. If
        *pccKey is 0, then *ppKey is undefined.

        If *pccVal is not 0, then *ppVal points to the first value in DN. If
        *pccVal is 0, then *ppVal is undefined.

    ERROR_DS_NAME_UNPARSEABLE
        The first RDN in *ppDN could not be parsed. All output parameters
        are undefined.

    Any other error
        All output parameters are undefined.

--*)

function DsGetRdnW(var ppDN: LPCWCH; var pcDN: DWORD; var ppKey: LPCWCH; var pcKey: DWORD; var ppVal: LPCWCH; var pcVal: DWORD): DWORD; stdcall;
{$EXTERNALSYM DsGetRdnW}

(*++
==========================================================

NTDSAPI
BOOL
WINAPI
DsCrackUnquotedMangledRdnW(
     IN LPCWSTR pszRDN,
     IN DWORD cchRDN,
     OUT OPTIONAL GUID *pGuid,
     OUT OPTIONAL DS_MANGLE_FOR *peDsMangleFor
     );

Description

Determine whether the given RDN is in mangled form. If so, the mangled RDN
is decoded, and the guid and mangle type are returned.

The RDN should already be in unquoted form. See DsUnquoteRdnValue.

Arguments:

    pszRDN (IN) - Character string containing RDN. Termination is optional.

    cchRDN (IN) - Length of RDN excluding termination, if any

    pGuid (OUT, OPTIONAL) - Pointer to storage to receive decoded guid.
                            Only returned if RDN is mangled.

    peDsMangleFor (OUT, OPTIONAL) - Pointer to storage to receive mangle type.
                            Only returned if RDN is mangled

Return Value:

    BOOL - Whether the RDN is mangled or not

--*)

function DsCrackUnquotedMangledRdnW(pszRDN: LPCWSTR; cchRDN: DWORD; pGuid: LPGUID; peDsMangleFor: PDsMangleFor): BOOL; stdcall;
{$EXTERNALSYM DsCrackUnquotedMangledRdnW}
function DsCrackUnquotedMangledRdnA(pszRDN: LPCSTR; cchRDN: DWORD; pGuid: LPGUID; peDsMangleFor: PDsMangleFor): BOOL; stdcall;
{$EXTERNALSYM DsCrackUnquotedMangledRdnA}

{$IFDEF UNICODE}
function DsCrackUnquotedMangledRdn(pszRDN: LPCWSTR; cchRDN: DWORD; pGuid: LPGUID; peDsMangleFor: PDsMangleFor): BOOL; stdcall;
{$EXTERNALSYM DsCrackUnquotedMangledRdn}
{$ELSE}
function DsCrackUnquotedMangledRdn(pszRDN: LPCSTR; cchRDN: DWORD; pGuid: LPGUID; peDsMangleFor: PDsMangleFor): BOOL; stdcall;
{$EXTERNALSYM DsCrackUnquotedMangledRdn}
{$ENDIF}

(*++
==========================================================

NTDSAPI
BOOL
WINAPI
DsIsMangledRdnValueW(
    LPCWSTR pszRdn,
    DWORD cRdn,
    DS_MANGLE_FOR eDsMangleForDesired
    );

Description

    Determine if the given RDN Value is mangled, and of the given type. Note that
    the key portion of an RDN should not be supplied.

    The name may be quoted or unquoted.  This routine tries to unquote the value.  If
    the unquote operation fails, the routine proceeds to attempt the unmangle.

    A change was made in the default quoting behavior of DNs returned from the DS
    between Windows 2000 and Windows XP. This routine transparently handles RDNs with
    special characters in either form.

    The routine expects the value part of the RDN.

    If you have full DN, use DsIsMangledDn() below.

    To check for deleted name:
        DsIsMangledRdnValueW( rdn, rdnlen, DS_MANGLE_OBJECT_FOR_DELETION )
    To check for a conflicted name:
        DsIsMangledRdnValueW( rdn, rdnlen, DS_MANGLE_OBJECT_FOR_NAME_CONFLICT )

Arguments:

    pszRdn (IN) - RDN value character string. Termination is not required and
        is ignored.

    cRdn (IN) - Length of RDN value in characters excluding termination

    eDsMangleForDesired (IN) - Type of mangling to check for

Return Value:

    BOOL - True if the Rdn is mangled and is of the required type

--*)

function DsIsMangledRdnValueW(pszRdn: LPCWSTR; cRdn: DWORD; eDsMangleForDesired: DS_MANGLE_FOR): BOOL; stdcall;
{$EXTERNALSYM DsIsMangledRdnValueW}
function DsIsMangledRdnValueA(pszRdn: LPCSTR; cRdn: DWORD; eDsMangleForDesired: DS_MANGLE_FOR): BOOL; stdcall;
{$EXTERNALSYM DsIsMangledRdnValueA}

{$IFDEF UNICODE}
function DsIsMangledRdnValue(pszRdn: LPCWSTR; cRdn: DWORD; eDsMangleForDesired: DS_MANGLE_FOR): BOOL; stdcall;
{$EXTERNALSYM DsIsMangledRdnValue}
{$ELSE}
function DsIsMangledRdnValue(pszRdn: LPCSTR; cRdn: DWORD; eDsMangleForDesired: DS_MANGLE_FOR): BOOL; stdcall;
{$EXTERNALSYM DsIsMangledRdnValue}
{$ENDIF}

(*++
==========================================================

NTDSAPI
BOOL
WINAPI
DsIsMangledDnW(
    LPCWSTR pszDn,
    DS_MANGLE_FOR eDsMangleFor
    );

Description

    Determine if the first RDN in a quoted DN is a mangled name of given type.

    The DN must be suitable for input to DsGetRdn().

    To check for deleted name:
        DsIsMangledDnW( dn, DS_MANGLE_OBJECT_FOR_DELETION )
    To check for a conflicted name:
        DsIsMangledDnW( Dn, DS_MANGLE_OBJECT_FOR_NAME_CONFLICT )

Arguments:

    pszDn (IN) - Quoted Distinguished Name as returned by DS functions

    eDsMangleFor (IN) - Type of mangling to check for

Return Value:

    BOOL - True if first RDN is mangled and is of the given mangle type

--*)

function DsIsMangledDnA(pszDn: LPCSTR; eDsMangleFor: DS_MANGLE_FOR): BOOL; stdcall;
{$EXTERNALSYM DsIsMangledDnA}
function DsIsMangledDnW(pszDn: LPCWSTR; eDsMangleFor: DS_MANGLE_FOR): BOOL; stdcall;
{$EXTERNALSYM DsIsMangledDnW}

{$IFDEF UNICODE}
function DsIsMangledDn(pszDn: LPCWSTR; eDsMangleFor: DS_MANGLE_FOR): BOOL; stdcall;
{$EXTERNALSYM DsIsMangledDn}
{$ELSE}
function DsIsMangledDn(pszDn: LPCSTR; eDsMangleFor: DS_MANGLE_FOR): BOOL; stdcall;
{$EXTERNALSYM DsIsMangledDn}
{$ENDIF}

implementation

const
  ntdsapilib = 'ntdsapi.dll';

function NTDSCONN_IGNORE_SCHEDULE(_options_: DWORD): DWORD;
begin
  // todo NTDSCONN_OPT_IGNORE_SCHEDULE_MASK only defined in pre-release version
  Result := (_options_ and DWORD($80000000){NTDSCONN_OPT_IGNORE_SCHEDULE_MASK}) shr 31;
end;

function FRSCONN_GET_PRIORITY(_options_: DWORD): DWORD;
begin
  if ((_options_ and FRSCONN_PRIORITY_MASK) shr 28) <> 0 then
    Result := (_options_ and FRSCONN_PRIORITY_MASK) shr 28
  else
    Result := FRSCONN_MAX_PRIORITY;
end;

{$IFDEF DYNAMIC_LINK}
var
  _DsBindA: Pointer;

function DsBindA;
begin
  GetProcedureAddress(_DsBindA, ntdsapilib, 'DsBindA');
  asm
    mov esp, ebp
    pop ebp
    jmp [_DsBindA]
  end;
end;
{$ELSE}
function DsBindA; external ntdsapilib name 'DsBindA';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _DsBindW: Pointer;

function DsBindW;
begin
  GetProcedureAddress(_DsBindW, ntdsapilib, 'DsBindW');
  asm
    mov esp, ebp
    pop ebp
    jmp [_DsBindW]
  end;
end;
{$ELSE}
function DsBindW; external ntdsapilib name 'DsBindW';
{$ENDIF DYNAMIC_LINK}
{$IFDEF UNICODE}

{$IFDEF DYNAMIC_LINK}
var
  _DsBind: Pointer;

function DsBind;
begin
  GetProcedureAddress(_DsBind, ntdsapilib, 'DsBindW');
  asm
    mov esp, ebp
    pop ebp
    jmp [_DsBind]
  end;
end;
{$ELSE}
function DsBind; external ntdsapilib name 'DsBindW';
{$ENDIF DYNAMIC_LINK}
{$ELSE}

{$IFDEF DYNAMIC_LINK}
var
  _DsBind: Pointer;

function DsBind;
begin
  GetProcedureAddress(_DsBind, ntdsapilib, 'DsBindA');
  asm
    mov esp, ebp
    pop ebp
    jmp [_DsBind]
  end;
end;
{$ELSE}
function DsBind; external ntdsapilib name 'DsBindA';
{$ENDIF DYNAMIC_LINK}
{$ENDIF}

{$IFDEF DYNAMIC_LINK}
var
  _DsBindWithCredA: Pointer;

function DsBindWithCredA;
begin
  GetProcedureAddress(_DsBindWithCredA, ntdsapilib, 'DsBindWithCredA');
  asm
    mov esp, ebp
    pop ebp
    jmp [_DsBindWithCredA]
  end;
end;
{$ELSE}
function DsBindWithCredA; external ntdsapilib name 'DsBindWithCredA';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _DsBindWithCredW: Pointer;

function DsBindWithCredW;
begin
  GetProcedureAddress(_DsBindWithCredW, ntdsapilib, 'DsBindWithCredW');
  asm
    mov esp, ebp
    pop ebp
    jmp [_DsBindWithCredW]
  end;
end;
{$ELSE}
function DsBindWithCredW; external ntdsapilib name 'DsBindWithCredW';
{$ENDIF DYNAMIC_LINK}
{$IFDEF UNICODE}

{$IFDEF DYNAMIC_LINK}
var
  _DsBindWithCred: Pointer;

function DsBindWithCred;
begin
  GetProcedureAddress(_DsBindWithCred, ntdsapilib, 'DsBindWithCredW');
  asm
    mov esp, ebp
    pop ebp
    jmp [_DsBindWithCred]
  end;
end;
{$ELSE}
function DsBindWithCred; external ntdsapilib name 'DsBindWithCredW';
{$ENDIF DYNAMIC_LINK}
{$ELSE}

{$IFDEF DYNAMIC_LINK}
var
  _DsBindWithCred: Pointer;

function DsBindWithCred;
begin
  GetProcedureAddress(_DsBindWithCred, ntdsapilib, 'DsBindWithCredA');
  asm
    mov esp, ebp
    pop ebp
    jmp [_DsBindWithCred]
  end;
end;
{$ELSE}
function DsBindWithCred; external ntdsapilib name 'DsBindWithCredA';
{$ENDIF DYNAMIC_LINK}
{$ENDIF}

{$IFDEF DYNAMIC_LINK}
var
  _DsBindWithSpnA: Pointer;

function DsBindWithSpnA;
begin
  GetProcedureAddress(_DsBindWithSpnA, ntdsapilib, 'DsBindWithSpnA');
  asm
    mov esp, ebp
    pop ebp
    jmp [_DsBindWithSpnA]
  end;
end;
{$ELSE}
function DsBindWithSpnA; external ntdsapilib name 'DsBindWithSpnA';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _DsBindWithSpnW: Pointer;

function DsBindWithSpnW;
begin
  GetProcedureAddress(_DsBindWithSpnW, ntdsapilib, 'DsBindWithSpnW');
  asm
    mov esp, ebp
    pop ebp
    jmp [_DsBindWithSpnW]
  end;
end;
{$ELSE}
function DsBindWithSpnW; external ntdsapilib name 'DsBindWithSpnW';
{$ENDIF DYNAMIC_LINK}
{$IFDEF UNICODE}

{$IFDEF DYNAMIC_LINK}
var
  _DsBindWithSpn: Pointer;

function DsBindWithSpn;
begin
  GetProcedureAddress(_DsBindWithSpn, ntdsapilib, 'DsBindWithSpnW');
  asm
    mov esp, ebp
    pop ebp
    jmp [_DsBindWithSpn]
  end;
end;
{$ELSE}
function DsBindWithSpn; external ntdsapilib name 'DsBindWithSpnW';
{$ENDIF DYNAMIC_LINK}
{$ELSE}

{$IFDEF DYNAMIC_LINK}
var
  _DsBindWithSpn: Pointer;

function DsBindWithSpn;
begin
  GetProcedureAddress(_DsBindWithSpn, ntdsapilib, 'DsBindWithSpnA');
  asm
    mov esp, ebp
    pop ebp
    jmp [_DsBindWithSpn]
  end;
end;
{$ELSE}
function DsBindWithSpn; external ntdsapilib name 'DsBindWithSpnA';
{$ENDIF DYNAMIC_LINK}
{$ENDIF}

{$IFDEF DYNAMIC_LINK}
var
  _DsBindWithSpnExW: Pointer;

function DsBindWithSpnExW;
begin
  GetProcedureAddress(_DsBindWithSpnExW, ntdsapilib, 'DsBindWithSpnExW');
  asm
    mov esp, ebp
    pop ebp
    jmp [_DsBindWithSpnExW]
  end;
end;
{$ELSE}
function DsBindWithSpnExW; external ntdsapilib name 'DsBindWithSpnExW';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _DsBindWithSpnExA: Pointer;

function DsBindWithSpnExA;
begin
  GetProcedureAddress(_DsBindWithSpnExA, ntdsapilib, 'DsBindWithSpnExA');
  asm
    mov esp, ebp
    pop ebp
    jmp [_DsBindWithSpnExA]
  end;
end;
{$ELSE}
function DsBindWithSpnExA; external ntdsapilib name 'DsBindWithSpnExA';
{$ENDIF DYNAMIC_LINK}

{$IFDEF UNICODE}

{$IFDEF DYNAMIC_LINK}
var
  _DsBindWithSpnEx: Pointer;

function DsBindWithSpnEx;
begin
  GetProcedureAddress(_DsBindWithSpnEx, ntdsapilib, 'DsBindWithSpnExW');
  asm
    mov esp, ebp
    pop ebp
    jmp [_DsBindWithSpnEx]
  end;
end;
{$ELSE}
function DsBindWithSpnEx; external ntdsapilib name 'DsBindWithSpnExW';
{$ENDIF DYNAMIC_LINK}

{$ELSE}

{$IFDEF DYNAMIC_LINK}
var
  _DsBindWithSpnEx: Pointer;

function DsBindWithSpnEx;
begin
  GetProcedureAddress(_DsBindWithSpnEx, ntdsapilib, 'DsBindWithSpnExA');
  asm
    mov esp, ebp
    pop ebp
    jmp [_DsBindWithSpnEx]
  end;
end;
{$ELSE}
function DsBindWithSpnEx; external ntdsapilib name 'DsBindWithSpnExA';
{$ENDIF DYNAMIC_LINK}

{$ENDIF UNICODE}

{$IFDEF DYNAMIC_LINK}
var
  _DsBindToISTGW: Pointer;

function DsBindToISTGW;
begin
  GetProcedureAddress(_DsBindToISTGW, ntdsapilib, 'DsBindToISTGW');
  asm
    mov esp, ebp
    pop ebp
    jmp [_DsBindToISTGW]
  end;
end;
{$ELSE}
function DsBindToISTGW; external ntdsapilib name 'DsBindToISTGW';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _DsBindToISTGA: Pointer;

function DsBindToISTGA;
begin
  GetProcedureAddress(_DsBindToISTGA, ntdsapilib, 'DsBindToISTGA');
  asm
    mov esp, ebp
    pop ebp
    jmp [_DsBindToISTGA]
  end;
end;
{$ELSE}
function DsBindToISTGA; external ntdsapilib name 'DsBindToISTGA';
{$ENDIF DYNAMIC_LINK}

{$IFDEF UNICODE}

{$IFDEF DYNAMIC_LINK}
var
  _DsBindToISTG: Pointer;

function DsBindToISTG;
begin
  GetProcedureAddress(_DsBindToISTG, ntdsapilib, 'DsBindToISTGW');
  asm
    mov esp, ebp
    pop ebp
    jmp [_DsBindToISTG]
  end;
end;
{$ELSE}
function DsBindToISTG; external ntdsapilib name 'DsBindToISTGW';
{$ENDIF DYNAMIC_LINK}

{$ELSE}

{$IFDEF DYNAMIC_LINK}
var
  _DsBindToISTG: Pointer;

function DsBindToISTG;
begin
  GetProcedureAddress(_DsBindToISTG, ntdsapilib, 'DsBindToISTGA');
  asm
    mov esp, ebp
    pop ebp
    jmp [_DsBindToISTG]
  end;
end;
{$ELSE}
function DsBindToISTG; external ntdsapilib name 'DsBindToISTGA';
{$ENDIF DYNAMIC_LINK}

{$ENDIF UNICODE}

{$IFDEF DYNAMIC_LINK}
var
  _DsBindingSetTimeout: Pointer;

function DsBindingSetTimeout;
begin
  GetProcedureAddress(_DsBindingSetTimeout, ntdsapilib, 'DsBindingSetTimeout');
  asm
    mov esp, ebp
    pop ebp
    jmp [_DsBindingSetTimeout]
  end;
end;
{$ELSE}
function DsBindingSetTimeout; external ntdsapilib name 'DsBindingSetTimeout';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _DsUnBindA: Pointer;

function DsUnBindA;
begin
  GetProcedureAddress(_DsUnBindA, ntdsapilib, 'DsUnBindA');
  asm
    mov esp, ebp
    pop ebp
    jmp [_DsUnBindA]
  end;
end;
{$ELSE}
function DsUnBindA; external ntdsapilib name 'DsUnBindA';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _DsUnBindW: Pointer;

function DsUnBindW;
begin
  GetProcedureAddress(_DsUnBindW, ntdsapilib, 'DsUnBindW');
  asm
    mov esp, ebp
    pop ebp
    jmp [_DsUnBindW]
  end;
end;
{$ELSE}
function DsUnBindW; external ntdsapilib name 'DsUnBindW';
{$ENDIF DYNAMIC_LINK}
{$IFDEF UNICODE}

{$IFDEF DYNAMIC_LINK}
var
  _DsUnBind: Pointer;

function DsUnBind;
begin
  GetProcedureAddress(_DsUnBind, ntdsapilib, 'DsUnBindW');
  asm
    mov esp, ebp
    pop ebp
    jmp [_DsUnBind]
  end;
end;
{$ELSE}
function DsUnBind; external ntdsapilib name 'DsUnBindW';
{$ENDIF DYNAMIC_LINK}
{$ELSE}

{$IFDEF DYNAMIC_LINK}
var
  _DsUnBind: Pointer;

function DsUnBind;
begin
  GetProcedureAddress(_DsUnBind, ntdsapilib, 'DsUnBindA');
  asm
    mov esp, ebp
    pop ebp
    jmp [_DsUnBind]
  end;
end;
{$ELSE}
function DsUnBind; external ntdsapilib name 'DsUnBindA';
{$ENDIF DYNAMIC_LINK}
{$ENDIF}

{$IFDEF DYNAMIC_LINK}
var
  _DsMakePasswordCredentialsA: Pointer;

function DsMakePasswordCredentialsA;
begin
  GetProcedureAddress(_DsMakePasswordCredentialsA, ntdsapilib, 'DsMakePasswordCredentialsA');
  asm
    mov esp, ebp
    pop ebp
    jmp [_DsMakePasswordCredentialsA]
  end;
end;
{$ELSE}
function DsMakePasswordCredentialsA; external ntdsapilib name 'DsMakePasswordCredentialsA';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _DsMakePasswordCredentialsW: Pointer;

function DsMakePasswordCredentialsW;
begin
  GetProcedureAddress(_DsMakePasswordCredentialsW, ntdsapilib, 'DsMakePasswordCredentialsW');
  asm
    mov esp, ebp
    pop ebp
    jmp [_DsMakePasswordCredentialsW]
  end;
end;
{$ELSE}
function DsMakePasswordCredentialsW; external ntdsapilib name 'DsMakePasswordCredentialsW';
{$ENDIF DYNAMIC_LINK}
{$IFDEF UNICODE}

{$IFDEF DYNAMIC_LINK}
var
  _DsMakePasswordCredentials: Pointer;

function DsMakePasswordCredentials;
begin
  GetProcedureAddress(_DsMakePasswordCredentials, ntdsapilib, 'DsMakePasswordCredentialsW');
  asm
    mov esp, ebp
    pop ebp
    jmp [_DsMakePasswordCredentials]
  end;
end;
{$ELSE}
function DsMakePasswordCredentials; external ntdsapilib name 'DsMakePasswordCredentialsW';
{$ENDIF DYNAMIC_LINK}
{$ELSE}

{$IFDEF DYNAMIC_LINK}
var
  _DsMakePasswordCredentials: Pointer;

function DsMakePasswordCredentials;
begin
  GetProcedureAddress(_DsMakePasswordCredentials, ntdsapilib, 'DsMakePasswordCredentialsA');
  asm
    mov esp, ebp
    pop ebp
    jmp [_DsMakePasswordCredentials]
  end;
end;
{$ELSE}
function DsMakePasswordCredentials; external ntdsapilib name 'DsMakePasswordCredentialsA';
{$ENDIF DYNAMIC_LINK}
{$ENDIF}

{$IFDEF DYNAMIC_LINK}
var
  _DsFreePasswordCredentials: Pointer;

procedure DsFreePasswordCredentials;
begin
  GetProcedureAddress(_DsFreePasswordCredentials, ntdsapilib, 'DsFreePasswordCredentials');
  asm
    mov esp, ebp
    pop ebp
    jmp [_DsFreePasswordCredentials]
  end;
end;
{$ELSE}
procedure DsFreePasswordCredentials; external ntdsapilib name 'DsFreePasswordCredentials';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _DsFreePasswordCredentialsA: Pointer;

procedure DsFreePasswordCredentialsA;
begin
  GetProcedureAddress(_DsFreePasswordCredentialsA, ntdsapilib, 'DsFreePasswordCredentials');
  asm
    mov esp, ebp
    pop ebp
    jmp [_DsFreePasswordCredentialsA]
  end;
end;
{$ELSE}
procedure DsFreePasswordCredentialsA; external ntdsapilib name 'DsFreePasswordCredentials';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _DsFreePasswordCredentialsW: Pointer;

procedure DsFreePasswordCredentialsW;
begin
  GetProcedureAddress(_DsFreePasswordCredentialsW, ntdsapilib, 'DsFreePasswordCredentials');
  asm
    mov esp, ebp
    pop ebp
    jmp [_DsFreePasswordCredentialsW]
  end;
end;
{$ELSE}
procedure DsFreePasswordCredentialsW; external ntdsapilib name 'DsFreePasswordCredentials';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _DsCrackNamesA: Pointer;

function DsCrackNamesA;
begin
  GetProcedureAddress(_DsCrackNamesA, ntdsapilib, 'DsCrackNamesA');
  asm
    mov esp, ebp
    pop ebp
    jmp [_DsCrackNamesA]
  end;
end;
{$ELSE}
function DsCrackNamesA; external ntdsapilib name 'DsCrackNamesA';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _DsCrackNamesW: Pointer;

function DsCrackNamesW;
begin
  GetProcedureAddress(_DsCrackNamesW, ntdsapilib, 'DsCrackNamesW');
  asm
    mov esp, ebp
    pop ebp
    jmp [_DsCrackNamesW]
  end;
end;
{$ELSE}
function DsCrackNamesW; external ntdsapilib name 'DsCrackNamesW';
{$ENDIF DYNAMIC_LINK}
{$IFDEF UNICODE}

{$IFDEF DYNAMIC_LINK}
var
  _DsCrackNames: Pointer;

function DsCrackNames;
begin
  GetProcedureAddress(_DsCrackNames, ntdsapilib, 'DsCrackNamesW');
  asm
    mov esp, ebp
    pop ebp
    jmp [_DsCrackNames]
  end;
end;
{$ELSE}
function DsCrackNames; external ntdsapilib name 'DsCrackNamesW';
{$ENDIF DYNAMIC_LINK}
{$ELSE}

{$IFDEF DYNAMIC_LINK}
var
  _DsCrackNames: Pointer;

function DsCrackNames;
begin
  GetProcedureAddress(_DsCrackNames, ntdsapilib, 'DsCrackNamesA');
  asm
    mov esp, ebp
    pop ebp
    jmp [_DsCrackNames]
  end;
end;
{$ELSE}
function DsCrackNames; external ntdsapilib name 'DsCrackNamesA';
{$ENDIF DYNAMIC_LINK}
{$ENDIF}

{$IFDEF DYNAMIC_LINK}
var
  _DsFreeNameResultA: Pointer;

procedure DsFreeNameResultA;
begin
  GetProcedureAddress(_DsFreeNameResultA, ntdsapilib, 'DsFreeNameResultA');
  asm
    mov esp, ebp
    pop ebp
    jmp [_DsFreeNameResultA]
  end;
end;
{$ELSE}
procedure DsFreeNameResultA; external ntdsapilib name 'DsFreeNameResultA';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _DsFreeNameResultW: Pointer;

procedure DsFreeNameResultW;
begin
  GetProcedureAddress(_DsFreeNameResultW, ntdsapilib, 'DsFreeNameResultW');
  asm
    mov esp, ebp
    pop ebp
    jmp [_DsFreeNameResultW]
  end;
end;
{$ELSE}
procedure DsFreeNameResultW; external ntdsapilib name 'DsFreeNameResultW';
{$ENDIF DYNAMIC_LINK}
{$IFDEF UNICODE}

{$IFDEF DYNAMIC_LINK}
var
  _DsFreeNameResult: Pointer;

procedure DsFreeNameResult;
begin
  GetProcedureAddress(_DsFreeNameResult, ntdsapilib, 'DsFreeNameResultW');
  asm
    mov esp, ebp
    pop ebp
    jmp [_DsFreeNameResult]
  end;
end;
{$ELSE}
procedure DsFreeNameResult; external ntdsapilib name 'DsFreeNameResultW';
{$ENDIF DYNAMIC_LINK}
{$ELSE}

{$IFDEF DYNAMIC_LINK}
var
  _DsFreeNameResult: Pointer;

procedure DsFreeNameResult;
begin
  GetProcedureAddress(_DsFreeNameResult, ntdsapilib, 'DsFreeNameResultA');
  asm
    mov esp, ebp
    pop ebp
    jmp [_DsFreeNameResult]
  end;
end;
{$ELSE}
procedure DsFreeNameResult; external ntdsapilib name 'DsFreeNameResultA';
{$ENDIF DYNAMIC_LINK}
{$ENDIF}

{$IFDEF DYNAMIC_LINK}
var
  _DsMakeSpnA: Pointer;

function DsMakeSpnA;
begin
  GetProcedureAddress(_DsMakeSpnA, ntdsapilib, 'DsMakeSpnA');
  asm
    mov esp, ebp
    pop ebp
    jmp [_DsMakeSpnA]
  end;
end;
{$ELSE}
function DsMakeSpnA; external ntdsapilib name 'DsMakeSpnA';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _DsMakeSpnW: Pointer;

function DsMakeSpnW;
begin
  GetProcedureAddress(_DsMakeSpnW, ntdsapilib, 'DsMakeSpnW');
  asm
    mov esp, ebp
    pop ebp
    jmp [_DsMakeSpnW]
  end;
end;
{$ELSE}
function DsMakeSpnW; external ntdsapilib name 'DsMakeSpnW';
{$ENDIF DYNAMIC_LINK}
{$IFDEF UNICODE}

{$IFDEF DYNAMIC_LINK}
var
  _DsMakeSpn: Pointer;

function DsMakeSpn;
begin
  GetProcedureAddress(_DsMakeSpn, ntdsapilib, 'DsMakeSpnW');
  asm
    mov esp, ebp
    pop ebp
    jmp [_DsMakeSpn]
  end;
end;
{$ELSE}
function DsMakeSpn; external ntdsapilib name 'DsMakeSpnW';
{$ENDIF DYNAMIC_LINK}
{$ELSE}

{$IFDEF DYNAMIC_LINK}
var
  _DsMakeSpn: Pointer;

function DsMakeSpn;
begin
  GetProcedureAddress(_DsMakeSpn, ntdsapilib, 'DsMakeSpnA');
  asm
    mov esp, ebp
    pop ebp
    jmp [_DsMakeSpn]
  end;
end;
{$ELSE}
function DsMakeSpn; external ntdsapilib name 'DsMakeSpnA';
{$ENDIF DYNAMIC_LINK}
{$ENDIF}

{$IFDEF DYNAMIC_LINK}
var
  _DsGetSpnA: Pointer;

function DsGetSpnA;
begin
  GetProcedureAddress(_DsGetSpnA, ntdsapilib, 'DsGetSpnA');
  asm
    mov esp, ebp
    pop ebp
    jmp [_DsGetSpnA]
  end;
end;
{$ELSE}
function DsGetSpnA; external ntdsapilib name 'DsGetSpnA';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _DsGetSpnW: Pointer;

function DsGetSpnW;
begin
  GetProcedureAddress(_DsGetSpnW, ntdsapilib, 'DsGetSpnW');
  asm
    mov esp, ebp
    pop ebp
    jmp [_DsGetSpnW]
  end;
end;
{$ELSE}
function DsGetSpnW; external ntdsapilib name 'DsGetSpnW';
{$ENDIF DYNAMIC_LINK}
{$IFDEF UNICODE}

{$IFDEF DYNAMIC_LINK}
var
  _DsGetSpn: Pointer;

function DsGetSpn;
begin
  GetProcedureAddress(_DsGetSpn, ntdsapilib, 'DsGetSpnW');
  asm
    mov esp, ebp
    pop ebp
    jmp [_DsGetSpn]
  end;
end;
{$ELSE}
function DsGetSpn; external ntdsapilib name 'DsGetSpnW';
{$ENDIF DYNAMIC_LINK}
{$ELSE}

{$IFDEF DYNAMIC_LINK}
var
  _DsGetSpn: Pointer;

function DsGetSpn;
begin
  GetProcedureAddress(_DsGetSpn, ntdsapilib, 'DsGetSpnA');
  asm
    mov esp, ebp
    pop ebp
    jmp [_DsGetSpn]
  end;
end;
{$ELSE}
function DsGetSpn; external ntdsapilib name 'DsGetSpnA';
{$ENDIF DYNAMIC_LINK}
{$ENDIF}

{$IFDEF DYNAMIC_LINK}
var
  _DsFreeSpnArrayA: Pointer;

procedure DsFreeSpnArrayA;
begin
  GetProcedureAddress(_DsFreeSpnArrayA, ntdsapilib, 'DsFreeSpnArrayA');
  asm
    mov esp, ebp
    pop ebp
    jmp [_DsFreeSpnArrayA]
  end;
end;
{$ELSE}
procedure DsFreeSpnArrayA; external ntdsapilib name 'DsFreeSpnArrayA';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _DsFreeSpnArrayW: Pointer;

procedure DsFreeSpnArrayW;
begin
  GetProcedureAddress(_DsFreeSpnArrayW, ntdsapilib, 'DsFreeSpnArrayW');
  asm
    mov esp, ebp
    pop ebp
    jmp [_DsFreeSpnArrayW]
  end;
end;
{$ELSE}
procedure DsFreeSpnArrayW; external ntdsapilib name 'DsFreeSpnArrayW';
{$ENDIF DYNAMIC_LINK}
{$IFDEF UNICODE}

{$IFDEF DYNAMIC_LINK}
var
  _DsFreeSpnArray: Pointer;

procedure DsFreeSpnArray;
begin
  GetProcedureAddress(_DsFreeSpnArray, ntdsapilib, 'DsFreeSpnArrayW');
  asm
    mov esp, ebp
    pop ebp
    jmp [_DsFreeSpnArray]
  end;
end;
{$ELSE}
procedure DsFreeSpnArray; external ntdsapilib name 'DsFreeSpnArrayW';
{$ENDIF DYNAMIC_LINK}
{$ELSE}

{$IFDEF DYNAMIC_LINK}
var
  _DsFreeSpnArray: Pointer;

procedure DsFreeSpnArray;
begin
  GetProcedureAddress(_DsFreeSpnArray, ntdsapilib, 'DsFreeSpnArrayA');
  asm
    mov esp, ebp
    pop ebp
    jmp [_DsFreeSpnArray]
  end;
end;
{$ELSE}
procedure DsFreeSpnArray; external ntdsapilib name 'DsFreeSpnArrayA';
{$ENDIF DYNAMIC_LINK}
{$ENDIF}

{$IFDEF DYNAMIC_LINK}
var
  _DsCrackSpnA: Pointer;

function DsCrackSpnA;
begin
  GetProcedureAddress(_DsCrackSpnA, ntdsapilib, 'DsCrackSpnA');
  asm
    mov esp, ebp
    pop ebp
    jmp [_DsCrackSpnA]
  end;
end;
{$ELSE}
function DsCrackSpnA; external ntdsapilib name 'DsCrackSpnA';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _DsCrackSpnW: Pointer;

function DsCrackSpnW;
begin
  GetProcedureAddress(_DsCrackSpnW, ntdsapilib, 'DsCrackSpnW');
  asm
    mov esp, ebp
    pop ebp
    jmp [_DsCrackSpnW]
  end;
end;
{$ELSE}
function DsCrackSpnW; external ntdsapilib name 'DsCrackSpnW';
{$ENDIF DYNAMIC_LINK}
{$IFDEF UNICODE}

{$IFDEF DYNAMIC_LINK}
var
  _DsCrackSpn: Pointer;

function DsCrackSpn;
begin
  GetProcedureAddress(_DsCrackSpn, ntdsapilib, 'DsCrackSpnW');
  asm
    mov esp, ebp
    pop ebp
    jmp [_DsCrackSpn]
  end;
end;
{$ELSE}
function DsCrackSpn; external ntdsapilib name 'DsCrackSpnW';
{$ENDIF DYNAMIC_LINK}
{$ELSE}

{$IFDEF DYNAMIC_LINK}
var
  _DsCrackSpn: Pointer;

function DsCrackSpn;
begin
  GetProcedureAddress(_DsCrackSpn, ntdsapilib, 'DsCrackSpnA');
  asm
    mov esp, ebp
    pop ebp
    jmp [_DsCrackSpn]
  end;
end;
{$ELSE}
function DsCrackSpn; external ntdsapilib name 'DsCrackSpnA';
{$ENDIF DYNAMIC_LINK}
{$ENDIF}

{$IFDEF DYNAMIC_LINK}
var
  _DsWriteAccountSpnA: Pointer;

function DsWriteAccountSpnA;
begin
  GetProcedureAddress(_DsWriteAccountSpnA, ntdsapilib, 'DsWriteAccountSpnA');
  asm
    mov esp, ebp
    pop ebp
    jmp [_DsWriteAccountSpnA]
  end;
end;
{$ELSE}
function DsWriteAccountSpnA; external ntdsapilib name 'DsWriteAccountSpnA';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _DsWriteAccountSpnW: Pointer;

function DsWriteAccountSpnW;
begin
  GetProcedureAddress(_DsWriteAccountSpnW, ntdsapilib, 'DsWriteAccountSpnW');
  asm
    mov esp, ebp
    pop ebp
    jmp [_DsWriteAccountSpnW]
  end;
end;
{$ELSE}
function DsWriteAccountSpnW; external ntdsapilib name 'DsWriteAccountSpnW';
{$ENDIF DYNAMIC_LINK}
{$IFDEF UNICODE}

{$IFDEF DYNAMIC_LINK}
var
  _DsWriteAccountSpn: Pointer;

function DsWriteAccountSpn;
begin
  GetProcedureAddress(_DsWriteAccountSpn, ntdsapilib, 'DsWriteAccountSpnW');
  asm
    mov esp, ebp
    pop ebp
    jmp [_DsWriteAccountSpn]
  end;
end;
{$ELSE}
function DsWriteAccountSpn; external ntdsapilib name 'DsWriteAccountSpnW';
{$ENDIF DYNAMIC_LINK}
{$ELSE}

{$IFDEF DYNAMIC_LINK}
var
  _DsWriteAccountSpn: Pointer;

function DsWriteAccountSpn;
begin
  GetProcedureAddress(_DsWriteAccountSpn, ntdsapilib, 'DsWriteAccountSpnA');
  asm
    mov esp, ebp
    pop ebp
    jmp [_DsWriteAccountSpn]
  end;
end;
{$ELSE}
function DsWriteAccountSpn; external ntdsapilib name 'DsWriteAccountSpnA';
{$ENDIF DYNAMIC_LINK}
{$ENDIF}

{$IFDEF DYNAMIC_LINK}
var
  _DsClientMakeSpnForTargetServerA: Pointer;

function DsClientMakeSpnForTargetServerA;
begin
  GetProcedureAddress(_DsClientMakeSpnForTargetServerA, ntdsapilib, 'DsClientMakeSpnForTargetServerA');
  asm
    mov esp, ebp
    pop ebp
    jmp [_DsClientMakeSpnForTargetServerA]
  end;
end;
{$ELSE}
function DsClientMakeSpnForTargetServerA; external ntdsapilib name 'DsClientMakeSpnForTargetServerA';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _DsClientMakeSpnForTargetServerW: Pointer;

function DsClientMakeSpnForTargetServerW;
begin
  GetProcedureAddress(_DsClientMakeSpnForTargetServerW, ntdsapilib, 'DsClientMakeSpnForTargetServerW');
  asm
    mov esp, ebp
    pop ebp
    jmp [_DsClientMakeSpnForTargetServerW]
  end;
end;
{$ELSE}
function DsClientMakeSpnForTargetServerW; external ntdsapilib name 'DsClientMakeSpnForTargetServerW';
{$ENDIF DYNAMIC_LINK}
{$IFDEF UNICODE}

{$IFDEF DYNAMIC_LINK}
var
  _DsClientMakeSpnForTargetServer: Pointer;

function DsClientMakeSpnForTargetServer;
begin
  GetProcedureAddress(_DsClientMakeSpnForTargetServer, ntdsapilib, 'DsClientMakeSpnForTargetServerW');
  asm
    mov esp, ebp
    pop ebp
    jmp [_DsClientMakeSpnForTargetServer]
  end;
end;
{$ELSE}
function DsClientMakeSpnForTargetServer; external ntdsapilib name 'DsClientMakeSpnForTargetServerW';
{$ENDIF DYNAMIC_LINK}
{$ELSE}

{$IFDEF DYNAMIC_LINK}
var
  _DsClientMakeSpnForTargetServer: Pointer;

function DsClientMakeSpnForTargetServer;
begin
  GetProcedureAddress(_DsClientMakeSpnForTargetServer, ntdsapilib, 'DsClientMakeSpnForTargetServerA');
  asm
    mov esp, ebp
    pop ebp
    jmp [_DsClientMakeSpnForTargetServer]
  end;
end;
{$ELSE}
function DsClientMakeSpnForTargetServer; external ntdsapilib name 'DsClientMakeSpnForTargetServerA';
{$ENDIF DYNAMIC_LINK}
{$ENDIF}

{$IFDEF DYNAMIC_LINK}
var
  _DsServerRegisterSpnA: Pointer;

function DsServerRegisterSpnA;
begin
  GetProcedureAddress(_DsServerRegisterSpnA, ntdsapilib, 'DsServerRegisterSpnA');
  asm
    mov esp, ebp
    pop ebp
    jmp [_DsServerRegisterSpnA]
  end;
end;
{$ELSE}
function DsServerRegisterSpnA; external ntdsapilib name 'DsServerRegisterSpnA';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _DsServerRegisterSpnW: Pointer;

function DsServerRegisterSpnW;
begin
  GetProcedureAddress(_DsServerRegisterSpnW, ntdsapilib, 'DsServerRegisterSpnW');
  asm
    mov esp, ebp
    pop ebp
    jmp [_DsServerRegisterSpnW]
  end;
end;
{$ELSE}
function DsServerRegisterSpnW; external ntdsapilib name 'DsServerRegisterSpnW';
{$ENDIF DYNAMIC_LINK}
{$IFDEF UNICODE}

{$IFDEF DYNAMIC_LINK}
var
  _DsServerRegisterSpn: Pointer;

function DsServerRegisterSpn;
begin
  GetProcedureAddress(_DsServerRegisterSpn, ntdsapilib, 'DsServerRegisterSpnW');
  asm
    mov esp, ebp
    pop ebp
    jmp [_DsServerRegisterSpn]
  end;
end;
{$ELSE}
function DsServerRegisterSpn; external ntdsapilib name 'DsServerRegisterSpnW';
{$ENDIF DYNAMIC_LINK}
{$ELSE}

{$IFDEF DYNAMIC_LINK}
var
  _DsServerRegisterSpn: Pointer;

function DsServerRegisterSpn;
begin
  GetProcedureAddress(_DsServerRegisterSpn, ntdsapilib, 'DsServerRegisterSpnA');
  asm
    mov esp, ebp
    pop ebp
    jmp [_DsServerRegisterSpn]
  end;
end;
{$ELSE}
function DsServerRegisterSpn; external ntdsapilib name 'DsServerRegisterSpnA';
{$ENDIF DYNAMIC_LINK}
{$ENDIF}

{$IFDEF DYNAMIC_LINK}
var
  _DsReplicaSyncA: Pointer;

function DsReplicaSyncA;
begin
  GetProcedureAddress(_DsReplicaSyncA, ntdsapilib, 'DsReplicaSyncA');
  asm
    mov esp, ebp
    pop ebp
    jmp [_DsReplicaSyncA]
  end;
end;
{$ELSE}
function DsReplicaSyncA; external ntdsapilib name 'DsReplicaSyncA';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _DsReplicaSyncW: Pointer;

function DsReplicaSyncW;
begin
  GetProcedureAddress(_DsReplicaSyncW, ntdsapilib, 'DsReplicaSyncW');
  asm
    mov esp, ebp
    pop ebp
    jmp [_DsReplicaSyncW]
  end;
end;
{$ELSE}
function DsReplicaSyncW; external ntdsapilib name 'DsReplicaSyncW';
{$ENDIF DYNAMIC_LINK}
{$IFDEF UNICODE}

{$IFDEF DYNAMIC_LINK}
var
  _DsReplicaSync: Pointer;

function DsReplicaSync;
begin
  GetProcedureAddress(_DsReplicaSync, ntdsapilib, 'DsReplicaSyncW');
  asm
    mov esp, ebp
    pop ebp
    jmp [_DsReplicaSync]
  end;
end;
{$ELSE}
function DsReplicaSync; external ntdsapilib name 'DsReplicaSyncW';
{$ENDIF DYNAMIC_LINK}
{$ELSE}

{$IFDEF DYNAMIC_LINK}
var
  _DsReplicaSync: Pointer;

function DsReplicaSync;
begin
  GetProcedureAddress(_DsReplicaSync, ntdsapilib, 'DsReplicaSyncA');
  asm
    mov esp, ebp
    pop ebp
    jmp [_DsReplicaSync]
  end;
end;
{$ELSE}
function DsReplicaSync; external ntdsapilib name 'DsReplicaSyncA';
{$ENDIF DYNAMIC_LINK}
{$ENDIF}

{$IFDEF DYNAMIC_LINK}
var
  _DsReplicaAddA: Pointer;

function DsReplicaAddA;
begin
  GetProcedureAddress(_DsReplicaAddA, ntdsapilib, 'DsReplicaAddA');
  asm
    mov esp, ebp
    pop ebp
    jmp [_DsReplicaAddA]
  end;
end;
{$ELSE}
function DsReplicaAddA; external ntdsapilib name 'DsReplicaAddA';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _DsReplicaAddW: Pointer;

function DsReplicaAddW;
begin
  GetProcedureAddress(_DsReplicaAddW, ntdsapilib, 'DsReplicaAddW');
  asm
    mov esp, ebp
    pop ebp
    jmp [_DsReplicaAddW]
  end;
end;
{$ELSE}
function DsReplicaAddW; external ntdsapilib name 'DsReplicaAddW';
{$ENDIF DYNAMIC_LINK}
{$IFDEF UNICODE}

{$IFDEF DYNAMIC_LINK}
var
  _DsReplicaAdd: Pointer;

function DsReplicaAdd;
begin
  GetProcedureAddress(_DsReplicaAdd, ntdsapilib, 'DsReplicaAddW');
  asm
    mov esp, ebp
    pop ebp
    jmp [_DsReplicaAdd]
  end;
end;
{$ELSE}
function DsReplicaAdd; external ntdsapilib name 'DsReplicaAddW';
{$ENDIF DYNAMIC_LINK}
{$ELSE}

{$IFDEF DYNAMIC_LINK}
var
  _DsReplicaAdd: Pointer;

function DsReplicaAdd;
begin
  GetProcedureAddress(_DsReplicaAdd, ntdsapilib, 'DsReplicaAddA');
  asm
    mov esp, ebp
    pop ebp
    jmp [_DsReplicaAdd]
  end;
end;
{$ELSE}
function DsReplicaAdd; external ntdsapilib name 'DsReplicaAddA';
{$ENDIF DYNAMIC_LINK}
{$ENDIF}

{$IFDEF DYNAMIC_LINK}
var
  _DsReplicaDelA: Pointer;

function DsReplicaDelA;
begin
  GetProcedureAddress(_DsReplicaDelA, ntdsapilib, 'DsReplicaDelA');
  asm
    mov esp, ebp
    pop ebp
    jmp [_DsReplicaDelA]
  end;
end;
{$ELSE}
function DsReplicaDelA; external ntdsapilib name 'DsReplicaDelA';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _DsReplicaDelW: Pointer;

function DsReplicaDelW;
begin
  GetProcedureAddress(_DsReplicaDelW, ntdsapilib, 'DsReplicaDelW');
  asm
    mov esp, ebp
    pop ebp
    jmp [_DsReplicaDelW]
  end;
end;
{$ELSE}
function DsReplicaDelW; external ntdsapilib name 'DsReplicaDelW';
{$ENDIF DYNAMIC_LINK}
{$IFDEF UNICODE}

{$IFDEF DYNAMIC_LINK}
var
  _DsReplicaDel: Pointer;

function DsReplicaDel;
begin
  GetProcedureAddress(_DsReplicaDel, ntdsapilib, 'DsReplicaDelW');
  asm
    mov esp, ebp
    pop ebp
    jmp [_DsReplicaDel]
  end;
end;
{$ELSE}
function DsReplicaDel; external ntdsapilib name 'DsReplicaDelW';
{$ENDIF DYNAMIC_LINK}
{$ELSE}

{$IFDEF DYNAMIC_LINK}
var
  _DsReplicaDel: Pointer;

function DsReplicaDel;
begin
  GetProcedureAddress(_DsReplicaDel, ntdsapilib, 'DsReplicaDelA');
  asm
    mov esp, ebp
    pop ebp
    jmp [_DsReplicaDel]
  end;
end;
{$ELSE}
function DsReplicaDel; external ntdsapilib name 'DsReplicaDelA';
{$ENDIF DYNAMIC_LINK}
{$ENDIF}

{$IFDEF DYNAMIC_LINK}
var
  _DsReplicaModifyA: Pointer;

function DsReplicaModifyA;
begin
  GetProcedureAddress(_DsReplicaModifyA, ntdsapilib, 'DsReplicaModifyA');
  asm
    mov esp, ebp
    pop ebp
    jmp [_DsReplicaModifyA]
  end;
end;
{$ELSE}
function DsReplicaModifyA; external ntdsapilib name 'DsReplicaModifyA';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _DsReplicaModifyW: Pointer;

function DsReplicaModifyW;
begin
  GetProcedureAddress(_DsReplicaModifyW, ntdsapilib, 'DsReplicaModifyW');
  asm
    mov esp, ebp
    pop ebp
    jmp [_DsReplicaModifyW]
  end;
end;
{$ELSE}
function DsReplicaModifyW; external ntdsapilib name 'DsReplicaModifyW';
{$ENDIF DYNAMIC_LINK}
{$IFDEF UNICODE}

{$IFDEF DYNAMIC_LINK}
var
  _DsReplicaModify: Pointer;

function DsReplicaModify;
begin
  GetProcedureAddress(_DsReplicaModify, ntdsapilib, 'DsReplicaModifyW');
  asm
    mov esp, ebp
    pop ebp
    jmp [_DsReplicaModify]
  end;
end;
{$ELSE}
function DsReplicaModify; external ntdsapilib name 'DsReplicaModifyW';
{$ENDIF DYNAMIC_LINK}
{$ELSE}

{$IFDEF DYNAMIC_LINK}
var
  _DsReplicaModify: Pointer;

function DsReplicaModify;
begin
  GetProcedureAddress(_DsReplicaModify, ntdsapilib, 'DsReplicaModifyA');
  asm
    mov esp, ebp
    pop ebp
    jmp [_DsReplicaModify]
  end;
end;
{$ELSE}
function DsReplicaModify; external ntdsapilib name 'DsReplicaModifyA';
{$ENDIF DYNAMIC_LINK}
{$ENDIF}

{$IFDEF DYNAMIC_LINK}
var
  _DsReplicaUpdateRefsA: Pointer;

function DsReplicaUpdateRefsA;
begin
  GetProcedureAddress(_DsReplicaUpdateRefsA, ntdsapilib, 'DsReplicaUpdateRefsA');
  asm
    mov esp, ebp
    pop ebp
    jmp [_DsReplicaUpdateRefsA]
  end;
end;
{$ELSE}
function DsReplicaUpdateRefsA; external ntdsapilib name 'DsReplicaUpdateRefsA';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _DsReplicaUpdateRefsW: Pointer;

function DsReplicaUpdateRefsW;
begin
  GetProcedureAddress(_DsReplicaUpdateRefsW, ntdsapilib, 'DsReplicaUpdateRefsW');
  asm
    mov esp, ebp
    pop ebp
    jmp [_DsReplicaUpdateRefsW]
  end;
end;
{$ELSE}
function DsReplicaUpdateRefsW; external ntdsapilib name 'DsReplicaUpdateRefsW';
{$ENDIF DYNAMIC_LINK}
{$IFDEF UNICODE}

{$IFDEF DYNAMIC_LINK}
var
  _DsReplicaUpdateRefs: Pointer;

function DsReplicaUpdateRefs;
begin
  GetProcedureAddress(_DsReplicaUpdateRefs, ntdsapilib, 'DsReplicaUpdateRefsW');
  asm
    mov esp, ebp
    pop ebp
    jmp [_DsReplicaUpdateRefs]
  end;
end;
{$ELSE}
function DsReplicaUpdateRefs; external ntdsapilib name 'DsReplicaUpdateRefsW';
{$ENDIF DYNAMIC_LINK}
{$ELSE}

{$IFDEF DYNAMIC_LINK}
var
  _DsReplicaUpdateRefs: Pointer;

function DsReplicaUpdateRefs;
begin
  GetProcedureAddress(_DsReplicaUpdateRefs, ntdsapilib, 'DsReplicaUpdateRefsA');
  asm
    mov esp, ebp
    pop ebp
    jmp [_DsReplicaUpdateRefs]
  end;
end;
{$ELSE}
function DsReplicaUpdateRefs; external ntdsapilib name 'DsReplicaUpdateRefsA';
{$ENDIF DYNAMIC_LINK}
{$ENDIF}

{$IFDEF DYNAMIC_LINK}
var
  _DsReplicaSyncAllA: Pointer;

function DsReplicaSyncAllA;
begin
  GetProcedureAddress(_DsReplicaSyncAllA, ntdsapilib, 'DsReplicaSyncAllA');
  asm
    mov esp, ebp
    pop ebp
    jmp [_DsReplicaSyncAllA]
  end;
end;
{$ELSE}
function DsReplicaSyncAllA; external ntdsapilib name 'DsReplicaSyncAllA';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _DsReplicaSyncAllW: Pointer;

function DsReplicaSyncAllW;
begin
  GetProcedureAddress(_DsReplicaSyncAllW, ntdsapilib, 'DsReplicaSyncAllW');
  asm
    mov esp, ebp
    pop ebp
    jmp [_DsReplicaSyncAllW]
  end;
end;
{$ELSE}
function DsReplicaSyncAllW; external ntdsapilib name 'DsReplicaSyncAllW';
{$ENDIF DYNAMIC_LINK}
{$IFDEF UNICODE}

{$IFDEF DYNAMIC_LINK}
var
  _DsReplicaSyncAll: Pointer;

function DsReplicaSyncAll;
begin
  GetProcedureAddress(_DsReplicaSyncAll, ntdsapilib, 'DsReplicaSyncAllW');
  asm
    mov esp, ebp
    pop ebp
    jmp [_DsReplicaSyncAll]
  end;
end;
{$ELSE}
function DsReplicaSyncAll; external ntdsapilib name 'DsReplicaSyncAllW';
{$ENDIF DYNAMIC_LINK}
{$ELSE}

{$IFDEF DYNAMIC_LINK}
var
  _DsReplicaSyncAll: Pointer;

function DsReplicaSyncAll;
begin
  GetProcedureAddress(_DsReplicaSyncAll, ntdsapilib, 'DsReplicaSyncAllA');
  asm
    mov esp, ebp
    pop ebp
    jmp [_DsReplicaSyncAll]
  end;
end;
{$ELSE}
function DsReplicaSyncAll; external ntdsapilib name 'DsReplicaSyncAllA';
{$ENDIF DYNAMIC_LINK}
{$ENDIF}

{$IFDEF DYNAMIC_LINK}
var
  _DsRemoveDsServerA: Pointer;

function DsRemoveDsServerA;
begin
  GetProcedureAddress(_DsRemoveDsServerA, ntdsapilib, 'DsRemoveDsServerA');
  asm
    mov esp, ebp
    pop ebp
    jmp [_DsRemoveDsServerA]
  end;
end;
{$ELSE}
function DsRemoveDsServerA; external ntdsapilib name 'DsRemoveDsServerA';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _DsRemoveDsServerW: Pointer;

function DsRemoveDsServerW;
begin
  GetProcedureAddress(_DsRemoveDsServerW, ntdsapilib, 'DsRemoveDsServerW');
  asm
    mov esp, ebp
    pop ebp
    jmp [_DsRemoveDsServerW]
  end;
end;
{$ELSE}
function DsRemoveDsServerW; external ntdsapilib name 'DsRemoveDsServerW';
{$ENDIF DYNAMIC_LINK}
{$IFDEF UNICODE}

{$IFDEF DYNAMIC_LINK}
var
  _DsRemoveDsServer: Pointer;

function DsRemoveDsServer;
begin
  GetProcedureAddress(_DsRemoveDsServer, ntdsapilib, 'DsRemoveDsServerW');
  asm
    mov esp, ebp
    pop ebp
    jmp [_DsRemoveDsServer]
  end;
end;
{$ELSE}
function DsRemoveDsServer; external ntdsapilib name 'DsRemoveDsServerW';
{$ENDIF DYNAMIC_LINK}
{$ELSE}

{$IFDEF DYNAMIC_LINK}
var
  _DsRemoveDsServer: Pointer;

function DsRemoveDsServer;
begin
  GetProcedureAddress(_DsRemoveDsServer, ntdsapilib, 'DsRemoveDsServerA');
  asm
    mov esp, ebp
    pop ebp
    jmp [_DsRemoveDsServer]
  end;
end;
{$ELSE}
function DsRemoveDsServer; external ntdsapilib name 'DsRemoveDsServerA';
{$ENDIF DYNAMIC_LINK}
{$ENDIF}

{$IFDEF DYNAMIC_LINK}
var
  _DsRemoveDsDomainA: Pointer;

function DsRemoveDsDomainA;
begin
  GetProcedureAddress(_DsRemoveDsDomainA, ntdsapilib, 'DsRemoveDsDomainA');
  asm
    mov esp, ebp
    pop ebp
    jmp [_DsRemoveDsDomainA]
  end;
end;
{$ELSE}
function DsRemoveDsDomainA; external ntdsapilib name 'DsRemoveDsDomainA';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _DsRemoveDsDomainW: Pointer;

function DsRemoveDsDomainW;
begin
  GetProcedureAddress(_DsRemoveDsDomainW, ntdsapilib, 'DsRemoveDsDomainW');
  asm
    mov esp, ebp
    pop ebp
    jmp [_DsRemoveDsDomainW]
  end;
end;
{$ELSE}
function DsRemoveDsDomainW; external ntdsapilib name 'DsRemoveDsDomainW';
{$ENDIF DYNAMIC_LINK}
{$IFDEF UNICODE}

{$IFDEF DYNAMIC_LINK}
var
  _DsRemoveDsDomain: Pointer;

function DsRemoveDsDomain;
begin
  GetProcedureAddress(_DsRemoveDsDomain, ntdsapilib, 'DsRemoveDsDomainW');
  asm
    mov esp, ebp
    pop ebp
    jmp [_DsRemoveDsDomain]
  end;
end;
{$ELSE}
function DsRemoveDsDomain; external ntdsapilib name 'DsRemoveDsDomainW';
{$ENDIF DYNAMIC_LINK}
{$ELSE}

{$IFDEF DYNAMIC_LINK}
var
  _DsRemoveDsDomain: Pointer;

function DsRemoveDsDomain;
begin
  GetProcedureAddress(_DsRemoveDsDomain, ntdsapilib, 'DsRemoveDsDomainA');
  asm
    mov esp, ebp
    pop ebp
    jmp [_DsRemoveDsDomain]
  end;
end;
{$ELSE}
function DsRemoveDsDomain; external ntdsapilib name 'DsRemoveDsDomainA';
{$ENDIF DYNAMIC_LINK}
{$ENDIF}

{$IFDEF DYNAMIC_LINK}
var
  _DsListSitesA: Pointer;

function DsListSitesA;
begin
  GetProcedureAddress(_DsListSitesA, ntdsapilib, 'DsListSitesA');
  asm
    mov esp, ebp
    pop ebp
    jmp [_DsListSitesA]
  end;
end;
{$ELSE}
function DsListSitesA; external ntdsapilib name 'DsListSitesA';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _DsListSitesW: Pointer;

function DsListSitesW;
begin
  GetProcedureAddress(_DsListSitesW, ntdsapilib, 'DsListSitesW');
  asm
    mov esp, ebp
    pop ebp
    jmp [_DsListSitesW]
  end;
end;
{$ELSE}
function DsListSitesW; external ntdsapilib name 'DsListSitesW';
{$ENDIF DYNAMIC_LINK}
{$IFDEF UNICODE}

{$IFDEF DYNAMIC_LINK}
var
  _DsListSites: Pointer;

function DsListSites;
begin
  GetProcedureAddress(_DsListSites, ntdsapilib, 'DsListSitesW');
  asm
    mov esp, ebp
    pop ebp
    jmp [_DsListSites]
  end;
end;
{$ELSE}
function DsListSites; external ntdsapilib name 'DsListSitesW';
{$ENDIF DYNAMIC_LINK}
{$ELSE}

{$IFDEF DYNAMIC_LINK}
var
  _DsListSites: Pointer;

function DsListSites;
begin
  GetProcedureAddress(_DsListSites, ntdsapilib, 'DsListSitesA');
  asm
    mov esp, ebp
    pop ebp
    jmp [_DsListSites]
  end;
end;
{$ELSE}
function DsListSites; external ntdsapilib name 'DsListSitesA';
{$ENDIF DYNAMIC_LINK}
{$ENDIF}

{$IFDEF DYNAMIC_LINK}
var
  _DsListServersInSiteA: Pointer;

function DsListServersInSiteA;
begin
  GetProcedureAddress(_DsListServersInSiteA, ntdsapilib, 'DsListServersInSiteA');
  asm
    mov esp, ebp
    pop ebp
    jmp [_DsListServersInSiteA]
  end;
end;
{$ELSE}
function DsListServersInSiteA; external ntdsapilib name 'DsListServersInSiteA';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _DsListServersInSiteW: Pointer;

function DsListServersInSiteW;
begin
  GetProcedureAddress(_DsListServersInSiteW, ntdsapilib, 'DsListServersInSiteW');
  asm
    mov esp, ebp
    pop ebp
    jmp [_DsListServersInSiteW]
  end;
end;
{$ELSE}
function DsListServersInSiteW; external ntdsapilib name 'DsListServersInSiteW';
{$ENDIF DYNAMIC_LINK}
{$IFDEF UNICODE}

{$IFDEF DYNAMIC_LINK}
var
  _DsListServersInSite: Pointer;

function DsListServersInSite;
begin
  GetProcedureAddress(_DsListServersInSite, ntdsapilib, 'DsListServersInSiteW');
  asm
    mov esp, ebp
    pop ebp
    jmp [_DsListServersInSite]
  end;
end;
{$ELSE}
function DsListServersInSite; external ntdsapilib name 'DsListServersInSiteW';
{$ENDIF DYNAMIC_LINK}
{$ELSE}

{$IFDEF DYNAMIC_LINK}
var
  _DsListServersInSite: Pointer;

function DsListServersInSite;
begin
  GetProcedureAddress(_DsListServersInSite, ntdsapilib, 'DsListServersInSiteA');
  asm
    mov esp, ebp
    pop ebp
    jmp [_DsListServersInSite]
  end;
end;
{$ELSE}
function DsListServersInSite; external ntdsapilib name 'DsListServersInSiteA';
{$ENDIF DYNAMIC_LINK}
{$ENDIF}

{$IFDEF DYNAMIC_LINK}
var
  _DsListDomainsInSiteA: Pointer;

function DsListDomainsInSiteA;
begin
  GetProcedureAddress(_DsListDomainsInSiteA, ntdsapilib, 'DsListDomainsInSiteA');
  asm
    mov esp, ebp
    pop ebp
    jmp [_DsListDomainsInSiteA]
  end;
end;
{$ELSE}
function DsListDomainsInSiteA; external ntdsapilib name 'DsListDomainsInSiteA';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _DsListDomainsInSiteW: Pointer;

function DsListDomainsInSiteW;
begin
  GetProcedureAddress(_DsListDomainsInSiteW, ntdsapilib, 'DsListDomainsInSiteW');
  asm
    mov esp, ebp
    pop ebp
    jmp [_DsListDomainsInSiteW]
  end;
end;
{$ELSE}
function DsListDomainsInSiteW; external ntdsapilib name 'DsListDomainsInSiteW';
{$ENDIF DYNAMIC_LINK}
{$IFDEF UNICODE}

{$IFDEF DYNAMIC_LINK}
var
  _DsListDomainsInSite: Pointer;

function DsListDomainsInSite;
begin
  GetProcedureAddress(_DsListDomainsInSite, ntdsapilib, 'DsListDomainsInSiteW');
  asm
    mov esp, ebp
    pop ebp
    jmp [_DsListDomainsInSite]
  end;
end;
{$ELSE}
function DsListDomainsInSite; external ntdsapilib name 'DsListDomainsInSiteW';
{$ENDIF DYNAMIC_LINK}
{$ELSE}

{$IFDEF DYNAMIC_LINK}
var
  _DsListDomainsInSite: Pointer;

function DsListDomainsInSite;
begin
  GetProcedureAddress(_DsListDomainsInSite, ntdsapilib, 'DsListDomainsInSiteA');
  asm
    mov esp, ebp
    pop ebp
    jmp [_DsListDomainsInSite]
  end;
end;
{$ELSE}
function DsListDomainsInSite; external ntdsapilib name 'DsListDomainsInSiteA';
{$ENDIF DYNAMIC_LINK}
{$ENDIF}

{$IFDEF DYNAMIC_LINK}
var
  _DsListServersForDomainInSiteA: Pointer;

function DsListServersForDomainInSiteA;
begin
  GetProcedureAddress(_DsListServersForDomainInSiteA, ntdsapilib, 'DsListServersForDomainInSiteA');
  asm
    mov esp, ebp
    pop ebp
    jmp [_DsListServersForDomainInSiteA]
  end;
end;
{$ELSE}
function DsListServersForDomainInSiteA; external ntdsapilib name 'DsListServersForDomainInSiteA';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _DsListServersForDomainInSiteW: Pointer;

function DsListServersForDomainInSiteW;
begin
  GetProcedureAddress(_DsListServersForDomainInSiteW, ntdsapilib, 'DsListServersForDomainInSiteW');
  asm
    mov esp, ebp
    pop ebp
    jmp [_DsListServersForDomainInSiteW]
  end;
end;
{$ELSE}
function DsListServersForDomainInSiteW; external ntdsapilib name 'DsListServersForDomainInSiteW';
{$ENDIF DYNAMIC_LINK}
{$IFDEF UNICODE}

{$IFDEF DYNAMIC_LINK}
var
  _DsListServersForDomainInSite: Pointer;

function DsListServersForDomainInSite;
begin
  GetProcedureAddress(_DsListServersForDomainInSite, ntdsapilib, 'DsListServersForDomainInSiteW');
  asm
    mov esp, ebp
    pop ebp
    jmp [_DsListServersForDomainInSite]
  end;
end;
{$ELSE}
function DsListServersForDomainInSite; external ntdsapilib name 'DsListServersForDomainInSiteW';
{$ENDIF DYNAMIC_LINK}
{$ELSE}

{$IFDEF DYNAMIC_LINK}
var
  _DsListServersForDomainInSite: Pointer;

function DsListServersForDomainInSite;
begin
  GetProcedureAddress(_DsListServersForDomainInSite, ntdsapilib, 'DsListServersForDomainInSiteA');
  asm
    mov esp, ebp
    pop ebp
    jmp [_DsListServersForDomainInSite]
  end;
end;
{$ELSE}
function DsListServersForDomainInSite; external ntdsapilib name 'DsListServersForDomainInSiteA';
{$ENDIF DYNAMIC_LINK}
{$ENDIF}

{$IFDEF DYNAMIC_LINK}
var
  _DsListInfoForServerA: Pointer;

function DsListInfoForServerA;
begin
  GetProcedureAddress(_DsListInfoForServerA, ntdsapilib, 'DsListInfoForServerA');
  asm
    mov esp, ebp
    pop ebp
    jmp [_DsListInfoForServerA]
  end;
end;
{$ELSE}
function DsListInfoForServerA; external ntdsapilib name 'DsListInfoForServerA';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _DsListInfoForServerW: Pointer;

function DsListInfoForServerW;
begin
  GetProcedureAddress(_DsListInfoForServerW, ntdsapilib, 'DsListInfoForServerW');
  asm
    mov esp, ebp
    pop ebp
    jmp [_DsListInfoForServerW]
  end;
end;
{$ELSE}
function DsListInfoForServerW; external ntdsapilib name 'DsListInfoForServerW';
{$ENDIF DYNAMIC_LINK}
{$IFDEF UNICODE}

{$IFDEF DYNAMIC_LINK}
var
  _DsListInfoForServer: Pointer;

function DsListInfoForServer;
begin
  GetProcedureAddress(_DsListInfoForServer, ntdsapilib, 'DsListInfoForServerW');
  asm
    mov esp, ebp
    pop ebp
    jmp [_DsListInfoForServer]
  end;
end;
{$ELSE}
function DsListInfoForServer; external ntdsapilib name 'DsListInfoForServerW';
{$ENDIF DYNAMIC_LINK}
{$ELSE}

{$IFDEF DYNAMIC_LINK}
var
  _DsListInfoForServer: Pointer;

function DsListInfoForServer;
begin
  GetProcedureAddress(_DsListInfoForServer, ntdsapilib, 'DsListInfoForServerA');
  asm
    mov esp, ebp
    pop ebp
    jmp [_DsListInfoForServer]
  end;
end;
{$ELSE}
function DsListInfoForServer; external ntdsapilib name 'DsListInfoForServerA';
{$ENDIF DYNAMIC_LINK}
{$ENDIF}

{$IFDEF DYNAMIC_LINK}
var
  _DsListRolesA: Pointer;

function DsListRolesA;
begin
  GetProcedureAddress(_DsListRolesA, ntdsapilib, 'DsListRolesA');
  asm
    mov esp, ebp
    pop ebp
    jmp [_DsListRolesA]
  end;
end;
{$ELSE}
function DsListRolesA; external ntdsapilib name 'DsListRolesA';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _DsListRolesW: Pointer;

function DsListRolesW;
begin
  GetProcedureAddress(_DsListRolesW, ntdsapilib, 'DsListRolesW');
  asm
    mov esp, ebp
    pop ebp
    jmp [_DsListRolesW]
  end;
end;
{$ELSE}
function DsListRolesW; external ntdsapilib name 'DsListRolesW';
{$ENDIF DYNAMIC_LINK}
{$IFDEF UNICODE}

{$IFDEF DYNAMIC_LINK}
var
  _DsListRoles: Pointer;

function DsListRoles;
begin
  GetProcedureAddress(_DsListRoles, ntdsapilib, 'DsListRolesW');
  asm
    mov esp, ebp
    pop ebp
    jmp [_DsListRoles]
  end;
end;
{$ELSE}
function DsListRoles; external ntdsapilib name 'DsListRolesW';
{$ENDIF DYNAMIC_LINK}
{$ELSE}

{$IFDEF DYNAMIC_LINK}
var
  _DsListRoles: Pointer;

function DsListRoles;
begin
  GetProcedureAddress(_DsListRoles, ntdsapilib, 'DsListRolesA');
  asm
    mov esp, ebp
    pop ebp
    jmp [_DsListRoles]
  end;
end;
{$ELSE}
function DsListRoles; external ntdsapilib name 'DsListRolesA';
{$ENDIF DYNAMIC_LINK}
{$ENDIF}

{$IFDEF DYNAMIC_LINK}
var
  _DsQuerySitesByCostW: Pointer;

function DsQuerySitesByCostW;
begin
  GetProcedureAddress(_DsQuerySitesByCostW, ntdsapilib, 'DsQuerySitesByCostW');
  asm
    mov esp, ebp
    pop ebp
    jmp [_DsQuerySitesByCostW]
  end;
end;
{$ELSE}
function DsQuerySitesByCostW; external ntdsapilib name 'DsQuerySitesByCostW';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _DsQuerySitesByCostA: Pointer;

function DsQuerySitesByCostA;
begin
  GetProcedureAddress(_DsQuerySitesByCostA, ntdsapilib, 'DsQuerySitesByCostA');
  asm
    mov esp, ebp
    pop ebp
    jmp [_DsQuerySitesByCostA]
  end;
end;
{$ELSE}
function DsQuerySitesByCostA; external ntdsapilib name 'DsQuerySitesByCostA';
{$ENDIF DYNAMIC_LINK}

{$IFDEF UNICODE}

{$IFDEF DYNAMIC_LINK}
var
  _DsQuerySitesByCost: Pointer;

function DsQuerySitesByCost;
begin
  GetProcedureAddress(_DsQuerySitesByCost, ntdsapilib, 'DsQuerySitesByCostW');
  asm
    mov esp, ebp
    pop ebp
    jmp [_DsQuerySitesByCost]
  end;
end;
{$ELSE}
function DsQuerySitesByCost; external ntdsapilib name 'DsQuerySitesByCostW';
{$ENDIF DYNAMIC_LINK}

{$ELSE}

{$IFDEF DYNAMIC_LINK}
var
  _DsQuerySitesByCost: Pointer;

function DsQuerySitesByCost;
begin
  GetProcedureAddress(_DsQuerySitesByCost, ntdsapilib, 'DsQuerySitesByCostA');
  asm
    mov esp, ebp
    pop ebp
    jmp [_DsQuerySitesByCost]
  end;
end;
{$ELSE}
function DsQuerySitesByCost; external ntdsapilib name 'DsQuerySitesByCostA';
{$ENDIF DYNAMIC_LINK}

{$ENDIF}

{$IFDEF DYNAMIC_LINK}
var
  _DsQuerySitesFree: Pointer;

procedure DsQuerySitesFree;
begin
  GetProcedureAddress(_DsQuerySitesFree, ntdsapilib, 'DsQuerySitesFree');
  asm
    mov esp, ebp
    pop ebp
    jmp [_DsQuerySitesFree]
  end;
end;
{$ELSE}
procedure DsQuerySitesFree; external ntdsapilib name 'DsQuerySitesFree';
{$ENDIF DYNAMIC_LINK}


{$IFDEF DYNAMIC_LINK}
var
  _DsMapSchemaGuidsA: Pointer;

function DsMapSchemaGuidsA;
begin
  GetProcedureAddress(_DsMapSchemaGuidsA, ntdsapilib, 'DsMapSchemaGuidsA');
  asm
    mov esp, ebp
    pop ebp
    jmp [_DsMapSchemaGuidsA]
  end;
end;
{$ELSE}
function DsMapSchemaGuidsA; external ntdsapilib name 'DsMapSchemaGuidsA';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _DsMapSchemaGuidsW: Pointer;

function DsMapSchemaGuidsW;
begin
  GetProcedureAddress(_DsMapSchemaGuidsW, ntdsapilib, 'DsMapSchemaGuidsW');
  asm
    mov esp, ebp
    pop ebp
    jmp [_DsMapSchemaGuidsW]
  end;
end;
{$ELSE}
function DsMapSchemaGuidsW; external ntdsapilib name 'DsMapSchemaGuidsW';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _DsFreeSchemaGuidMapA: Pointer;

procedure DsFreeSchemaGuidMapA;
begin
  GetProcedureAddress(_DsFreeSchemaGuidMapA, ntdsapilib, 'DsFreeSchemaGuidMapA');
  asm
    mov esp, ebp
    pop ebp
    jmp [_DsFreeSchemaGuidMapA]
  end;
end;
{$ELSE}
procedure DsFreeSchemaGuidMapA; external ntdsapilib name 'DsFreeSchemaGuidMapA';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _DsFreeSchemaGuidMapW: Pointer;

procedure DsFreeSchemaGuidMapW;
begin
  GetProcedureAddress(_DsFreeSchemaGuidMapW, ntdsapilib, 'DsFreeSchemaGuidMapW');
  asm
    mov esp, ebp
    pop ebp
    jmp [_DsFreeSchemaGuidMapW]
  end;
end;
{$ELSE}
procedure DsFreeSchemaGuidMapW; external ntdsapilib name 'DsFreeSchemaGuidMapW';
{$ENDIF DYNAMIC_LINK}
{$IFDEF UNICODE}

{$IFDEF DYNAMIC_LINK}
var
  _DsMapSchemaGuids: Pointer;

function DsMapSchemaGuids;
begin
  GetProcedureAddress(_DsMapSchemaGuids, ntdsapilib, 'DsMapSchemaGuidsW');
  asm
    mov esp, ebp
    pop ebp
    jmp [_DsMapSchemaGuids]
  end;
end;
{$ELSE}
function DsMapSchemaGuids; external ntdsapilib name 'DsMapSchemaGuidsW';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _DsFreeSchemaGuidMap: Pointer;

procedure DsFreeSchemaGuidMap;
begin
  GetProcedureAddress(_DsFreeSchemaGuidMap, ntdsapilib, 'DsFreeSchemaGuidMapW');
  asm
    mov esp, ebp
    pop ebp
    jmp [_DsFreeSchemaGuidMap]
  end;
end;
{$ELSE}
procedure DsFreeSchemaGuidMap; external ntdsapilib name 'DsFreeSchemaGuidMapW';
{$ENDIF DYNAMIC_LINK}
{$ELSE}

{$IFDEF DYNAMIC_LINK}
var
  _DsMapSchemaGuids: Pointer;

function DsMapSchemaGuids;
begin
  GetProcedureAddress(_DsMapSchemaGuids, ntdsapilib, 'DsMapSchemaGuidsA');
  asm
    mov esp, ebp
    pop ebp
    jmp [_DsMapSchemaGuids]
  end;
end;
{$ELSE}
function DsMapSchemaGuids; external ntdsapilib name 'DsMapSchemaGuidsA';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _DsFreeSchemaGuidMap: Pointer;

procedure DsFreeSchemaGuidMap;
begin
  GetProcedureAddress(_DsFreeSchemaGuidMap, ntdsapilib, 'DsFreeSchemaGuidMapA');
  asm
    mov esp, ebp
    pop ebp
    jmp [_DsFreeSchemaGuidMap]
  end;
end;
{$ELSE}
procedure DsFreeSchemaGuidMap; external ntdsapilib name 'DsFreeSchemaGuidMapA';
{$ENDIF DYNAMIC_LINK}
{$ENDIF}

{$IFDEF DYNAMIC_LINK}
var
  _DsGetDomainControllerInfoA: Pointer;

function DsGetDomainControllerInfoA;
begin
  GetProcedureAddress(_DsGetDomainControllerInfoA, ntdsapilib, 'DsGetDomainControllerInfoA');
  asm
    mov esp, ebp
    pop ebp
    jmp [_DsGetDomainControllerInfoA]
  end;
end;
{$ELSE}
function DsGetDomainControllerInfoA; external ntdsapilib name 'DsGetDomainControllerInfoA';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _DsGetDomainControllerInfoW: Pointer;

function DsGetDomainControllerInfoW;
begin
  GetProcedureAddress(_DsGetDomainControllerInfoW, ntdsapilib, 'DsGetDomainControllerInfoW');
  asm
    mov esp, ebp
    pop ebp
    jmp [_DsGetDomainControllerInfoW]
  end;
end;
{$ELSE}
function DsGetDomainControllerInfoW; external ntdsapilib name 'DsGetDomainControllerInfoW';
{$ENDIF DYNAMIC_LINK}
{$IFDEF UNICODE}

{$IFDEF DYNAMIC_LINK}
var
  _DsGetDomainControllerInfo: Pointer;

function DsGetDomainControllerInfo;
begin
  GetProcedureAddress(_DsGetDomainControllerInfo, ntdsapilib, 'DsGetDomainControllerInfoW');
  asm
    mov esp, ebp
    pop ebp
    jmp [_DsGetDomainControllerInfo]
  end;
end;
{$ELSE}
function DsGetDomainControllerInfo; external ntdsapilib name 'DsGetDomainControllerInfoW';
{$ENDIF DYNAMIC_LINK}
{$ELSE}

{$IFDEF DYNAMIC_LINK}
var
  _DsGetDomainControllerInfo: Pointer;

function DsGetDomainControllerInfo;
begin
  GetProcedureAddress(_DsGetDomainControllerInfo, ntdsapilib, 'DsGetDomainControllerInfoA');
  asm
    mov esp, ebp
    pop ebp
    jmp [_DsGetDomainControllerInfo]
  end;
end;
{$ELSE}
function DsGetDomainControllerInfo; external ntdsapilib name 'DsGetDomainControllerInfoA';
{$ENDIF DYNAMIC_LINK}
{$ENDIF}

{$IFDEF DYNAMIC_LINK}
var
  _DsFreeDomainControllerInfoA: Pointer;

procedure DsFreeDomainControllerInfoA;
begin
  GetProcedureAddress(_DsFreeDomainControllerInfoA, ntdsapilib, 'DsFreeDomainControllerInfoA');
  asm
    mov esp, ebp
    pop ebp
    jmp [_DsFreeDomainControllerInfoA]
  end;
end;
{$ELSE}
procedure DsFreeDomainControllerInfoA; external ntdsapilib name 'DsFreeDomainControllerInfoA';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _DsFreeDomainControllerInfoW: Pointer;

procedure DsFreeDomainControllerInfoW;
begin
  GetProcedureAddress(_DsFreeDomainControllerInfoW, ntdsapilib, 'DsFreeDomainControllerInfoW');
  asm
    mov esp, ebp
    pop ebp
    jmp [_DsFreeDomainControllerInfoW]
  end;
end;
{$ELSE}
procedure DsFreeDomainControllerInfoW; external ntdsapilib name 'DsFreeDomainControllerInfoW';
{$ENDIF DYNAMIC_LINK}
{$IFDEF UNICODE}

{$IFDEF DYNAMIC_LINK}
var
  _DsFreeDomainControllerInfo: Pointer;

procedure DsFreeDomainControllerInfo;
begin
  GetProcedureAddress(_DsFreeDomainControllerInfo, ntdsapilib, 'DsFreeDomainControllerInfoW');
  asm
    mov esp, ebp
    pop ebp
    jmp [_DsFreeDomainControllerInfo]
  end;
end;
{$ELSE}
procedure DsFreeDomainControllerInfo; external ntdsapilib name 'DsFreeDomainControllerInfoW';
{$ENDIF DYNAMIC_LINK}
{$ELSE}

{$IFDEF DYNAMIC_LINK}
var
  _DsFreeDomainControllerInfo: Pointer;

procedure DsFreeDomainControllerInfo;
begin
  GetProcedureAddress(_DsFreeDomainControllerInfo, ntdsapilib, 'DsFreeDomainControllerInfoA');
  asm
    mov esp, ebp
    pop ebp
    jmp [_DsFreeDomainControllerInfo]
  end;
end;
{$ELSE}
procedure DsFreeDomainControllerInfo; external ntdsapilib name 'DsFreeDomainControllerInfoA';
{$ENDIF DYNAMIC_LINK}
{$ENDIF}

{$IFDEF DYNAMIC_LINK}
var
  _DsReplicaConsistencyCheck: Pointer;

function DsReplicaConsistencyCheck;
begin
  GetProcedureAddress(_DsReplicaConsistencyCheck, ntdsapilib, 'DsReplicaConsistencyCheck');
  asm
    mov esp, ebp
    pop ebp
    jmp [_DsReplicaConsistencyCheck]
  end;
end;
{$ELSE}
function DsReplicaConsistencyCheck; external ntdsapilib name 'DsReplicaConsistencyCheck';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _DsReplicaVerifyObjectsW: Pointer;

function DsReplicaVerifyObjectsW;
begin
  GetProcedureAddress(_DsReplicaVerifyObjectsW, ntdsapilib, 'DsReplicaVerifyObjectsW');
  asm
    mov esp, ebp
    pop ebp
    jmp [_DsReplicaVerifyObjectsW]
  end;
end;
{$ELSE}
function DsReplicaVerifyObjectsW; external ntdsapilib name 'DsReplicaVerifyObjectsW';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _DsReplicaVerifyObjectsA: Pointer;

function DsReplicaVerifyObjectsA;
begin
  GetProcedureAddress(_DsReplicaVerifyObjectsA, ntdsapilib, 'DsReplicaVerifyObjectsA');
  asm
    mov esp, ebp
    pop ebp
    jmp [_DsReplicaVerifyObjectsA]
  end;
end;
{$ELSE}
function DsReplicaVerifyObjectsA; external ntdsapilib name 'DsReplicaVerifyObjectsA';
{$ENDIF DYNAMIC_LINK}

{$IFDEF UNICODE}

{$IFDEF DYNAMIC_LINK}
var
  _DsReplicaVerifyObjects: Pointer;

function DsReplicaVerifyObjects;
begin
  GetProcedureAddress(_DsReplicaVerifyObjects, ntdsapilib, 'DsReplicaVerifyObjectsW');
  asm
    mov esp, ebp
    pop ebp
    jmp [_DsReplicaVerifyObjects]
  end;
end;
{$ELSE}
function DsReplicaVerifyObjects; external ntdsapilib name 'DsReplicaVerifyObjectsW';
{$ENDIF DYNAMIC_LINK}

{$ELSE}

{$IFDEF DYNAMIC_LINK}
var
  _DsReplicaVerifyObjects: Pointer;

function DsReplicaVerifyObjects;
begin
  GetProcedureAddress(_DsReplicaVerifyObjects, ntdsapilib, 'DsReplicaVerifyObjectsA');
  asm
    mov esp, ebp
    pop ebp
    jmp [_DsReplicaVerifyObjects]
  end;
end;
{$ELSE}
function DsReplicaVerifyObjects; external ntdsapilib name 'DsReplicaVerifyObjectsA';
{$ENDIF DYNAMIC_LINK}

{$ENDIF}

{$IFDEF DYNAMIC_LINK}
var
  _DsReplicaGetInfoW: Pointer;

function DsReplicaGetInfoW;
begin
  GetProcedureAddress(_DsReplicaGetInfoW, ntdsapilib, 'DsReplicaGetInfoW');
  asm
    mov esp, ebp
    pop ebp
    jmp [_DsReplicaGetInfoW]
  end;
end;
{$ELSE}
function DsReplicaGetInfoW; external ntdsapilib name 'DsReplicaGetInfoW';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _DsReplicaFreeInfo: Pointer;

procedure DsReplicaFreeInfo;
begin
  GetProcedureAddress(_DsReplicaFreeInfo, ntdsapilib, 'DsReplicaFreeInfo');
  asm
    mov esp, ebp
    pop ebp
    jmp [_DsReplicaFreeInfo]
  end;
end;
{$ELSE}
procedure DsReplicaFreeInfo; external ntdsapilib name 'DsReplicaFreeInfo';
{$ENDIF DYNAMIC_LINK}

{$IFDEF UNICODE}

{$IFDEF DYNAMIC_LINK}
var
  _DsReplicaGetInfo: Pointer;

function DsReplicaGetInfo;
begin
  GetProcedureAddress(_DsReplicaGetInfo, ntdsapilib, 'DsReplicaGetInfoW');
  asm
    mov esp, ebp
    pop ebp
    jmp [_DsReplicaGetInfo]
  end;
end;
{$ELSE}
function DsReplicaGetInfo; external ntdsapilib name 'DsReplicaGetInfoW';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _DsReplicaGetInfo2W: Pointer;

function DsReplicaGetInfo2W;
begin
  GetProcedureAddress(_DsReplicaGetInfo2W, ntdsapilib, 'DsReplicaGetInfo2W');
  asm
    mov esp, ebp
    pop ebp
    jmp [_DsReplicaGetInfo2W]
  end;
end;
{$ELSE}
function DsReplicaGetInfo2W; external ntdsapilib name 'DsReplicaGetInfo2W';
{$ENDIF DYNAMIC_LINK}

{$ENDIF UNICODE}

{$IFDEF DYNAMIC_LINK}
var
  _DsAddSidHistoryA: Pointer;

function DsAddSidHistoryA;
begin
  GetProcedureAddress(_DsAddSidHistoryA, ntdsapilib, 'DsAddSidHistoryA');
  asm
    mov esp, ebp
    pop ebp
    jmp [_DsAddSidHistoryA]
  end;
end;
{$ELSE}
function DsAddSidHistoryA; external ntdsapilib name 'DsAddSidHistoryA';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _DsAddSidHistoryW: Pointer;

function DsAddSidHistoryW;
begin
  GetProcedureAddress(_DsAddSidHistoryW, ntdsapilib, 'DsAddSidHistoryW');
  asm
    mov esp, ebp
    pop ebp
    jmp [_DsAddSidHistoryW]
  end;
end;
{$ELSE}
function DsAddSidHistoryW; external ntdsapilib name 'DsAddSidHistoryW';
{$ENDIF DYNAMIC_LINK}
{$IFDEF UNICODE}

{$IFDEF DYNAMIC_LINK}
var
  _DsAddSidHistory: Pointer;

function DsAddSidHistory;
begin
  GetProcedureAddress(_DsAddSidHistory, ntdsapilib, 'DsAddSidHistoryW');
  asm
    mov esp, ebp
    pop ebp
    jmp [_DsAddSidHistory]
  end;
end;
{$ELSE}
function DsAddSidHistory; external ntdsapilib name 'DsAddSidHistoryW';
{$ENDIF DYNAMIC_LINK}
{$ELSE}

{$IFDEF DYNAMIC_LINK}
var
  _DsAddSidHistory: Pointer;

function DsAddSidHistory;
begin
  GetProcedureAddress(_DsAddSidHistory, ntdsapilib, 'DsAddSidHistoryA');
  asm
    mov esp, ebp
    pop ebp
    jmp [_DsAddSidHistory]
  end;
end;
{$ELSE}
function DsAddSidHistory; external ntdsapilib name 'DsAddSidHistoryA';
{$ENDIF DYNAMIC_LINK}
{$ENDIF}

{$IFDEF DYNAMIC_LINK}
var
  _DsInheritSecurityIdentityA: Pointer;

function DsInheritSecurityIdentityA;
begin
  GetProcedureAddress(_DsInheritSecurityIdentityA, ntdsapilib, 'DsInheritSecurityIdentityA');
  asm
    mov esp, ebp
    pop ebp
    jmp [_DsInheritSecurityIdentityA]
  end;
end;
{$ELSE}
function DsInheritSecurityIdentityA; external ntdsapilib name 'DsInheritSecurityIdentityA';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _DsInheritSecurityIdentityW: Pointer;

function DsInheritSecurityIdentityW;
begin
  GetProcedureAddress(_DsInheritSecurityIdentityW, ntdsapilib, 'DsInheritSecurityIdentityW');
  asm
    mov esp, ebp
    pop ebp
    jmp [_DsInheritSecurityIdentityW]
  end;
end;
{$ELSE}
function DsInheritSecurityIdentityW; external ntdsapilib name 'DsInheritSecurityIdentityW';
{$ENDIF DYNAMIC_LINK}
{$IFDEF UNICODE}

{$IFDEF DYNAMIC_LINK}
var
  _DsInheritSecurityIdentity: Pointer;

function DsInheritSecurityIdentity;
begin
  GetProcedureAddress(_DsInheritSecurityIdentity, ntdsapilib, 'DsInheritSecurityIdentityW');
  asm
    mov esp, ebp
    pop ebp
    jmp [_DsInheritSecurityIdentity]
  end;
end;
{$ELSE}
function DsInheritSecurityIdentity; external ntdsapilib name 'DsInheritSecurityIdentityW';
{$ENDIF DYNAMIC_LINK}
{$ELSE}

{$IFDEF DYNAMIC_LINK}
var
  _DsInheritSecurityIdentity: Pointer;

function DsInheritSecurityIdentity;
begin
  GetProcedureAddress(_DsInheritSecurityIdentity, ntdsapilib, 'DsInheritSecurityIdentityA');
  asm
    mov esp, ebp
    pop ebp
    jmp [_DsInheritSecurityIdentity]
  end;
end;
{$ELSE}
function DsInheritSecurityIdentity; external ntdsapilib name 'DsInheritSecurityIdentityA';
{$ENDIF DYNAMIC_LINK}
{$ENDIF}

{$IFDEF DYNAMIC_LINK}
var
  _DsQuoteRdnValueA: Pointer;

function DsQuoteRdnValueA;
begin
  GetProcedureAddress(_DsQuoteRdnValueA, ntdsapilib, 'DsQuoteRdnValueA');
  asm
    mov esp, ebp
    pop ebp
    jmp [_DsQuoteRdnValueA]
  end;
end;
{$ELSE}
function DsQuoteRdnValueA; external ntdsapilib name 'DsQuoteRdnValueA';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _DsQuoteRdnValueW: Pointer;

function DsQuoteRdnValueW;
begin
  GetProcedureAddress(_DsQuoteRdnValueW, ntdsapilib, 'DsQuoteRdnValueW');
  asm
    mov esp, ebp
    pop ebp
    jmp [_DsQuoteRdnValueW]
  end;
end;
{$ELSE}
function DsQuoteRdnValueW; external ntdsapilib name 'DsQuoteRdnValueW';
{$ENDIF DYNAMIC_LINK}
{$IFDEF UNICODE}

{$IFDEF DYNAMIC_LINK}
var
  _DsQuoteRdnValue: Pointer;

function DsQuoteRdnValue;
begin
  GetProcedureAddress(_DsQuoteRdnValue, ntdsapilib, 'DsQuoteRdnValueW');
  asm
    mov esp, ebp
    pop ebp
    jmp [_DsQuoteRdnValue]
  end;
end;
{$ELSE}
function DsQuoteRdnValue; external ntdsapilib name 'DsQuoteRdnValueW';
{$ENDIF DYNAMIC_LINK}
{$ELSE}

{$IFDEF DYNAMIC_LINK}
var
  _DsQuoteRdnValue: Pointer;

function DsQuoteRdnValue;
begin
  GetProcedureAddress(_DsQuoteRdnValue, ntdsapilib, 'DsQuoteRdnValueA');
  asm
    mov esp, ebp
    pop ebp
    jmp [_DsQuoteRdnValue]
  end;
end;
{$ELSE}
function DsQuoteRdnValue; external ntdsapilib name 'DsQuoteRdnValueA';
{$ENDIF DYNAMIC_LINK}
{$ENDIF}

{$IFDEF DYNAMIC_LINK}
var
  _DsUnquoteRdnValueA: Pointer;

function DsUnquoteRdnValueA;
begin
  GetProcedureAddress(_DsUnquoteRdnValueA, ntdsapilib, 'DsUnquoteRdnValueA');
  asm
    mov esp, ebp
    pop ebp
    jmp [_DsUnquoteRdnValueA]
  end;
end;
{$ELSE}
function DsUnquoteRdnValueA; external ntdsapilib name 'DsUnquoteRdnValueA';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _DsUnquoteRdnValueW: Pointer;

function DsUnquoteRdnValueW;
begin
  GetProcedureAddress(_DsUnquoteRdnValueW, ntdsapilib, 'DsUnquoteRdnValueW');
  asm
    mov esp, ebp
    pop ebp
    jmp [_DsUnquoteRdnValueW]
  end;
end;
{$ELSE}
function DsUnquoteRdnValueW; external ntdsapilib name 'DsUnquoteRdnValueW';
{$ENDIF DYNAMIC_LINK}
{$IFDEF UNICODE}

{$IFDEF DYNAMIC_LINK}
var
  _DsUnquoteRdnValue: Pointer;

function DsUnquoteRdnValue;
begin
  GetProcedureAddress(_DsUnquoteRdnValue, ntdsapilib, 'DsUnquoteRdnValueW');
  asm
    mov esp, ebp
    pop ebp
    jmp [_DsUnquoteRdnValue]
  end;
end;
{$ELSE}
function DsUnquoteRdnValue; external ntdsapilib name 'DsUnquoteRdnValueW';
{$ENDIF DYNAMIC_LINK}
{$ELSE}

{$IFDEF DYNAMIC_LINK}
var
  _DsUnquoteRdnValue: Pointer;

function DsUnquoteRdnValue;
begin
  GetProcedureAddress(_DsUnquoteRdnValue, ntdsapilib, 'DsUnquoteRdnValueA');
  asm
    mov esp, ebp
    pop ebp
    jmp [_DsUnquoteRdnValue]
  end;
end;
{$ELSE}
function DsUnquoteRdnValue; external ntdsapilib name 'DsUnquoteRdnValueA';
{$ENDIF DYNAMIC_LINK}
{$ENDIF}

{$IFDEF DYNAMIC_LINK}
var
  _DsGetRdnW: Pointer;

function DsGetRdnW;
begin
  GetProcedureAddress(_DsGetRdnW, ntdsapilib, 'DsGetRdnW');
  asm
    mov esp, ebp
    pop ebp
    jmp [_DsGetRdnW]
  end;
end;
{$ELSE}
function DsGetRdnW; external ntdsapilib name 'DsGetRdnW';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _DsCrackUnquotedMangledRdnW: Pointer;

function DsCrackUnquotedMangledRdnW;
begin
  GetProcedureAddress(_DsCrackUnquotedMangledRdnW, ntdsapilib, 'DsCrackUnquotedMangledRdnW');
  asm
    mov esp, ebp
    pop ebp
    jmp [_DsCrackUnquotedMangledRdnW]
  end;
end;
{$ELSE}
function DsCrackUnquotedMangledRdnW; external ntdsapilib name 'DsCrackUnquotedMangledRdnW';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _DsCrackUnquotedMangledRdnA: Pointer;

function DsCrackUnquotedMangledRdnA;
begin
  GetProcedureAddress(_DsCrackUnquotedMangledRdnA, ntdsapilib, 'DsCrackUnquotedMangledRdnA');
  asm
    mov esp, ebp
    pop ebp
    jmp [_DsCrackUnquotedMangledRdnA]
  end;
end;
{$ELSE}
function DsCrackUnquotedMangledRdnA; external ntdsapilib name 'DsCrackUnquotedMangledRdnA';
{$ENDIF DYNAMIC_LINK}

{$IFDEF UNICODE}

{$IFDEF DYNAMIC_LINK}
var
  _DsCrackUnquotedMangledRdn: Pointer;

function DsCrackUnquotedMangledRdn;
begin
  GetProcedureAddress(_DsCrackUnquotedMangledRdn, ntdsapilib, 'DsCrackUnquotedMangledRdnW');
  asm
    mov esp, ebp
    pop ebp
    jmp [_DsCrackUnquotedMangledRdn]
  end;
end;
{$ELSE}
function DsCrackUnquotedMangledRdn; external ntdsapilib name 'DsCrackUnquotedMangledRdnW';
{$ENDIF DYNAMIC_LINK}

{$ELSE}

{$IFDEF DYNAMIC_LINK}
var
  _DsCrackUnquotedMangledRdn: Pointer;

function DsCrackUnquotedMangledRdn;
begin
  GetProcedureAddress(_DsCrackUnquotedMangledRdn, ntdsapilib, 'DsCrackUnquotedMangledRdnA');
  asm
    mov esp, ebp
    pop ebp
    jmp [_DsCrackUnquotedMangledRdn]
  end;
end;
{$ELSE}
function DsCrackUnquotedMangledRdn; external ntdsapilib name 'DsCrackUnquotedMangledRdnA';
{$ENDIF DYNAMIC_LINK}

{$ENDIF}

{$IFDEF DYNAMIC_LINK}
var
  _DsIsMangledRdnValueW: Pointer;

function DsIsMangledRdnValueW;
begin
  GetProcedureAddress(_DsIsMangledRdnValueW, ntdsapilib, 'DsIsMangledRdnValueW');
  asm
    mov esp, ebp
    pop ebp
    jmp [_DsIsMangledRdnValueW]
  end;
end;
{$ELSE}
function DsIsMangledRdnValueW; external ntdsapilib name 'DsIsMangledRdnValueW';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _DsIsMangledRdnValueA: Pointer;

function DsIsMangledRdnValueA;
begin
  GetProcedureAddress(_DsIsMangledRdnValueA, ntdsapilib, 'DsIsMangledRdnValueA');
  asm
    mov esp, ebp
    pop ebp
    jmp [_DsIsMangledRdnValueA]
  end;
end;
{$ELSE}
function DsIsMangledRdnValueA; external ntdsapilib name 'DsIsMangledRdnValueA';
{$ENDIF DYNAMIC_LINK}

{$IFDEF UNICODE}

{$IFDEF DYNAMIC_LINK}
var
  _DsIsMangledRdnValue: Pointer;

function DsIsMangledRdnValue;
begin
  GetProcedureAddress(_DsIsMangledRdnValue, ntdsapilib, 'DsIsMangledRdnValueW');
  asm
    mov esp, ebp
    pop ebp
    jmp [_DsIsMangledRdnValue]
  end;
end;
{$ELSE}
function DsIsMangledRdnValue; external ntdsapilib name 'DsIsMangledRdnValueW';
{$ENDIF DYNAMIC_LINK}

{$ELSE}

{$IFDEF DYNAMIC_LINK}
var
  _DsIsMangledRdnValue: Pointer;

function DsIsMangledRdnValue;
begin
  GetProcedureAddress(_DsIsMangledRdnValue, ntdsapilib, 'DsIsMangledRdnValueA');
  asm
    mov esp, ebp
    pop ebp
    jmp [_DsIsMangledRdnValue]
  end;
end;
{$ELSE}
function DsIsMangledRdnValue; external ntdsapilib name 'DsIsMangledRdnValueA';
{$ENDIF DYNAMIC_LINK}

{$ENDIF}

{$IFDEF DYNAMIC_LINK}
var
  _DsIsMangledDnA: Pointer;

function DsIsMangledDnA;
begin
  GetProcedureAddress(_DsIsMangledDnA, ntdsapilib, 'DsIsMangledDnA');
  asm
    mov esp, ebp
    pop ebp
    jmp [_DsIsMangledDnA]
  end;
end;
{$ELSE}
function DsIsMangledDnA; external ntdsapilib name 'DsIsMangledDnA';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _DsIsMangledDnW: Pointer;

function DsIsMangledDnW;
begin
  GetProcedureAddress(_DsIsMangledDnW, ntdsapilib, 'DsIsMangledDnW');
  asm
    mov esp, ebp
    pop ebp
    jmp [_DsIsMangledDnW]
  end;
end;
{$ELSE}
function DsIsMangledDnW; external ntdsapilib name 'DsIsMangledDnW';
{$ENDIF DYNAMIC_LINK}

{$IFDEF UNICODE}

{$IFDEF DYNAMIC_LINK}
var
  _DsIsMangledDn: Pointer;

function DsIsMangledDn;
begin
  GetProcedureAddress(_DsIsMangledDn, ntdsapilib, 'DsIsMangledDnW');
  asm
    mov esp, ebp
    pop ebp
    jmp [_DsIsMangledDn]
  end;
end;
{$ELSE}
function DsIsMangledDn; external ntdsapilib name 'DsIsMangledDnW';
{$ENDIF DYNAMIC_LINK}

{$ELSE}

{$IFDEF DYNAMIC_LINK}
var
  _DsIsMangledDn: Pointer;

function DsIsMangledDn;
begin
  GetProcedureAddress(_DsIsMangledDn, ntdsapilib, 'DsIsMangledDnA');
  asm
    mov esp, ebp
    pop ebp
    jmp [_DsIsMangledDn]
  end;
end;
{$ELSE}
function DsIsMangledDn; external ntdsapilib name 'DsIsMangledDnA';
{$ENDIF DYNAMIC_LINK}

{$ENDIF}

end.
