{******************************************************************************}
{                                                       	               }
{ NT LDAP API interface Unit for Object Pascal                                 }
{                                                       	               }
{ Portions created by Microsoft are Copyright (C) 1995-2001 Microsoft          }
{ Corporation. All Rights Reserved.                                            }
{ 								               }
{ The original file is: ntldap.h, released June 2000. The original Pascal      }
{ code is: NtLDAP.pas, released December 2000. The initial developer of the    }
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

unit JwaNtLDAP;

{$WEAKPACKAGEUNIT}

{$HPPEMIT ''}
{$HPPEMIT '#include "ntldap.h"'}
{$HPPEMIT ''}

{$I WINDEFINES.INC}

interface

//
//
// Server controls section
//

//
// Permissive Modify Control.  No Data.
//

const
  LDAP_SERVER_PERMISSIVE_MODIFY_OID   = '1.2.840.113556.1.4.1413';
  {$EXTERNALSYM LDAP_SERVER_PERMISSIVE_MODIFY_OID}
  LDAP_SERVER_PERMISSIVE_MODIFY_OID_W = '1.2.840.113556.1.4.1413';
  {$EXTERNALSYM LDAP_SERVER_PERMISSIVE_MODIFY_OID_W}

//
// Show Deleted Control.  No Data.
//

  LDAP_SERVER_SHOW_DELETED_OID   = '1.2.840.113556.1.4.417';
  {$EXTERNALSYM LDAP_SERVER_SHOW_DELETED_OID}
  LDAP_SERVER_SHOW_DELETED_OID_W = '1.2.840.113556.1.4.417';
  {$EXTERNALSYM LDAP_SERVER_SHOW_DELETED_OID_W}

//
// Cross Domain Move Control. Data as follows
//      SEQUENCE {
//          Name OCTET STRING
//      }
//

  LDAP_SERVER_CROSSDOM_MOVE_TARGET_OID   = '1.2.840.113556.1.4.521';
  {$EXTERNALSYM LDAP_SERVER_CROSSDOM_MOVE_TARGET_OID}
  LDAP_SERVER_CROSSDOM_MOVE_TARGET_OID_W = '1.2.840.113556.1.4.521';
  {$EXTERNALSYM LDAP_SERVER_CROSSDOM_MOVE_TARGET_OID_W}

//
// Notification. No Data.
//

  LDAP_SERVER_NOTIFICATION_OID   = '1.2.840.113556.1.4.528';
  {$EXTERNALSYM LDAP_SERVER_NOTIFICATION_OID}
  LDAP_SERVER_NOTIFICATION_OID_W = '1.2.840.113556.1.4.528';
  {$EXTERNALSYM LDAP_SERVER_NOTIFICATION_OID_W}

//
// Lazy Commit. No Data.
//

  LDAP_SERVER_LAZY_COMMIT_OID   = '1.2.840.113556.1.4.619';
  {$EXTERNALSYM LDAP_SERVER_LAZY_COMMIT_OID}
  LDAP_SERVER_LAZY_COMMIT_OID_W = '1.2.840.113556.1.4.619';
  {$EXTERNALSYM LDAP_SERVER_LAZY_COMMIT_OID_W}

//
// Security Descriptor Flag. Data as follows
//      SEQUENCE {
//          Flags INTEGER
//      }
//

  LDAP_SERVER_SD_FLAGS_OID   = '1.2.840.113556.1.4.801';
  {$EXTERNALSYM LDAP_SERVER_SD_FLAGS_OID}
  LDAP_SERVER_SD_FLAGS_OID_W = '1.2.840.113556.1.4.801';
  {$EXTERNALSYM LDAP_SERVER_SD_FLAGS_OID_W}

//
// Tree Delete. No Data.
//

  LDAP_SERVER_TREE_DELETE_OID   = '1.2.840.113556.1.4.805';
  {$EXTERNALSYM LDAP_SERVER_TREE_DELETE_OID}
  LDAP_SERVER_TREE_DELETE_OID_W = '1.2.840.113556.1.4.805';
  {$EXTERNALSYM LDAP_SERVER_TREE_DELETE_OID_W}

//
// DirSync operation. Data as follows
//      SEQUENCE {
//          Flags   INTEGER
//          Size    INTEGER
//          Cookie  OCTET STRING
//      }
//

  LDAP_SERVER_DIRSYNC_OID   = '1.2.840.113556.1.4.841';
  {$EXTERNALSYM LDAP_SERVER_DIRSYNC_OID}
  LDAP_SERVER_DIRSYNC_OID_W = '1.2.840.113556.1.4.841';
  {$EXTERNALSYM LDAP_SERVER_DIRSYNC_OID_W}

//
// Return extended DNs. No Data.
//

  LDAP_SERVER_EXTENDED_DN_OID   = '1.2.840.113556.1.4.529';
  {$EXTERNALSYM LDAP_SERVER_EXTENDED_DN_OID}
  LDAP_SERVER_EXTENDED_DN_OID_W = '1.2.840.113556.1.4.529';
  {$EXTERNALSYM LDAP_SERVER_EXTENDED_DN_OID_W}

//
// Tell DC which server to verify with that a DN exist. Data as follows
//      SEQUENCE {
//          Flags   INTEGER,
//          ServerName OCTET STRING     // unicode server string
//      }
//

  LDAP_SERVER_VERIFY_NAME_OID   = '1.2.840.113556.1.4.1338';
  {$EXTERNALSYM LDAP_SERVER_VERIFY_NAME_OID}
  LDAP_SERVER_VERIFY_NAME_OID_W = '1.2.840.113556.1.4.1338';
  {$EXTERNALSYM LDAP_SERVER_VERIFY_NAME_OID_W}

//
// Tells server not to generate referrals
//

  LDAP_SERVER_DOMAIN_SCOPE_OID   = '1.2.840.113556.1.4.1339';
  {$EXTERNALSYM LDAP_SERVER_DOMAIN_SCOPE_OID}
  LDAP_SERVER_DOMAIN_SCOPE_OID_W = '1.2.840.113556.1.4.1339';
  {$EXTERNALSYM LDAP_SERVER_DOMAIN_SCOPE_OID_W}

//
// Server Search Options. Allows the client to pass in flags to control
// various search behaviours. Data as follows
//      SEQUENCE {
//          Flags   INTEGER
//      }
//

  LDAP_SERVER_SEARCH_OPTIONS_OID   = '1.2.840.113556.1.4.1340';
  {$EXTERNALSYM LDAP_SERVER_SEARCH_OPTIONS_OID}
  LDAP_SERVER_SEARCH_OPTIONS_OID_W = '1.2.840.113556.1.4.1340';
  {$EXTERNALSYM LDAP_SERVER_SEARCH_OPTIONS_OID_W}

//
// search option flags
//

  SERVER_SEARCH_FLAG_DOMAIN_SCOPE = $1; // no referrals generated
  {$EXTERNALSYM SERVER_SEARCH_FLAG_DOMAIN_SCOPE}
  SERVER_SEARCH_FLAG_PHANTOM_ROOT = $2; // search all NCs subordinate to search base
  {$EXTERNALSYM SERVER_SEARCH_FLAG_PHANTOM_ROOT}

//
// End of Server controls
//

//
//
// Operational Attributes
//

  LDAP_OPATT_BECOME_DOM_MASTER   = 'becomeDomainMaster';
  {$EXTERNALSYM LDAP_OPATT_BECOME_DOM_MASTER}
  LDAP_OPATT_BECOME_DOM_MASTER_W = 'becomeDomainMaster';
  {$EXTERNALSYM LDAP_OPATT_BECOME_DOM_MASTER_W}

  LDAP_OPATT_BECOME_RID_MASTER   = 'becomeRidMaster';
  {$EXTERNALSYM LDAP_OPATT_BECOME_RID_MASTER}
  LDAP_OPATT_BECOME_RID_MASTER_W = 'becomeRidMaster';
  {$EXTERNALSYM LDAP_OPATT_BECOME_RID_MASTER_W}

  LDAP_OPATT_BECOME_SCHEMA_MASTER   = 'becomeSchemaMaster';
  {$EXTERNALSYM LDAP_OPATT_BECOME_SCHEMA_MASTER}
  LDAP_OPATT_BECOME_SCHEMA_MASTER_W = 'becomeSchemaMaster';
  {$EXTERNALSYM LDAP_OPATT_BECOME_SCHEMA_MASTER_W}

  LDAP_OPATT_RECALC_HIERARCHY   = 'recalcHierarchy';
  {$EXTERNALSYM LDAP_OPATT_RECALC_HIERARCHY}
  LDAP_OPATT_RECALC_HIERARCHY_W = 'recalcHierarchy';
  {$EXTERNALSYM LDAP_OPATT_RECALC_HIERARCHY_W}

  LDAP_OPATT_SCHEMA_UPDATE_NOW   = 'schemaUpdateNow';
  {$EXTERNALSYM LDAP_OPATT_SCHEMA_UPDATE_NOW}
  LDAP_OPATT_SCHEMA_UPDATE_NOW_W = 'schemaUpdateNow';
  {$EXTERNALSYM LDAP_OPATT_SCHEMA_UPDATE_NOW_W}

  LDAP_OPATT_BECOME_PDC   = 'becomePdc';
  {$EXTERNALSYM LDAP_OPATT_BECOME_PDC}
  LDAP_OPATT_BECOME_PDC_W = 'becomePdc';
  {$EXTERNALSYM LDAP_OPATT_BECOME_PDC_W}

  LDAP_OPATT_FIXUP_INHERITANCE   = 'fixupInheritance';
  {$EXTERNALSYM LDAP_OPATT_FIXUP_INHERITANCE}
  LDAP_OPATT_FIXUP_INHERITANCE_W = 'fixupInheritance';
  {$EXTERNALSYM LDAP_OPATT_FIXUP_INHERITANCE_W}

  LDAP_OPATT_INVALIDATE_RID_POOL   = 'invalidateRidPool';
  {$EXTERNALSYM LDAP_OPATT_INVALIDATE_RID_POOL}
  LDAP_OPATT_INVALIDATE_RID_POOL_W = 'invalidateRidPool';
  {$EXTERNALSYM LDAP_OPATT_INVALIDATE_RID_POOL_W}

  LDAP_OPATT_ABANDON_REPL   = 'abandonReplication';
  {$EXTERNALSYM LDAP_OPATT_ABANDON_REPL}
  LDAP_OPATT_ABANDON_REPL_W = 'abandonReplication';
  {$EXTERNALSYM LDAP_OPATT_ABANDON_REPL_W}

  LDAP_OPATT_DO_GARBAGE_COLLECTION   = 'doGarbageCollection';
  {$EXTERNALSYM LDAP_OPATT_DO_GARBAGE_COLLECTION}
  LDAP_OPATT_DO_GARBAGE_COLLECTION_W = 'doGarbageCollection';
  {$EXTERNALSYM LDAP_OPATT_DO_GARBAGE_COLLECTION_W}

//
//  Root DSE Attributes
//

  LDAP_OPATT_SUBSCHEMA_SUBENTRY   = 'subschemaSubentry';
  {$EXTERNALSYM LDAP_OPATT_SUBSCHEMA_SUBENTRY}
  LDAP_OPATT_SUBSCHEMA_SUBENTRY_W = 'subschemaSubentry';
  {$EXTERNALSYM LDAP_OPATT_SUBSCHEMA_SUBENTRY_W}

  LDAP_OPATT_CURRENT_TIME   = 'currentTime';
  {$EXTERNALSYM LDAP_OPATT_CURRENT_TIME}
  LDAP_OPATT_CURRENT_TIME_W = 'currentTime';
  {$EXTERNALSYM LDAP_OPATT_CURRENT_TIME_W}

  LDAP_OPATT_SERVER_NAME   = 'serverName';
  {$EXTERNALSYM LDAP_OPATT_SERVER_NAME}
  LDAP_OPATT_SERVER_NAME_W = 'serverName';
  {$EXTERNALSYM LDAP_OPATT_SERVER_NAME_W}

  LDAP_OPATT_NAMING_CONTEXTS   = 'namingContexts';
  {$EXTERNALSYM LDAP_OPATT_NAMING_CONTEXTS}
  LDAP_OPATT_NAMING_CONTEXTS_W = 'namingContexts';
  {$EXTERNALSYM LDAP_OPATT_NAMING_CONTEXTS_W}

  LDAP_OPATT_DEFAULT_NAMING_CONTEXT   = 'defaultNamingContext';
  {$EXTERNALSYM LDAP_OPATT_DEFAULT_NAMING_CONTEXT}
  LDAP_OPATT_DEFAULT_NAMING_CONTEXT_W = 'defaultNamingContext';
  {$EXTERNALSYM LDAP_OPATT_DEFAULT_NAMING_CONTEXT_W}

  LDAP_OPATT_SUPPORTED_CONTROL   = 'supportedControl';
  {$EXTERNALSYM LDAP_OPATT_SUPPORTED_CONTROL}
  LDAP_OPATT_SUPPORTED_CONTROL_W = 'supportedControl';
  {$EXTERNALSYM LDAP_OPATT_SUPPORTED_CONTROL_W}

  LDAP_OPATT_HIGHEST_COMMITTED_USN   = 'highestCommitedUSN';
  {$EXTERNALSYM LDAP_OPATT_HIGHEST_COMMITTED_USN}
  LDAP_OPATT_HIGHEST_COMMITTED_USN_W = 'highestCommitedUSN';
  {$EXTERNALSYM LDAP_OPATT_HIGHEST_COMMITTED_USN_W}

  LDAP_OPATT_SUPPORTED_LDAP_VERSION   = 'supportedLDAPVersion';
  {$EXTERNALSYM LDAP_OPATT_SUPPORTED_LDAP_VERSION}
  LDAP_OPATT_SUPPORTED_LDAP_VERSION_W = 'supportedLDAPVersion';
  {$EXTERNALSYM LDAP_OPATT_SUPPORTED_LDAP_VERSION_W}

  LDAP_OPATT_SUPPORTED_LDAP_POLICIES   = 'supportedLDAPPolicies';
  {$EXTERNALSYM LDAP_OPATT_SUPPORTED_LDAP_POLICIES}
  LDAP_OPATT_SUPPORTED_LDAP_POLICIES_W = 'supportedLDAPPolicies';
  {$EXTERNALSYM LDAP_OPATT_SUPPORTED_LDAP_POLICIES_W}

  LDAP_OPATT_SCHEMA_NAMING_CONTEXT   = 'schemaNamingContext';
  {$EXTERNALSYM LDAP_OPATT_SCHEMA_NAMING_CONTEXT}
  LDAP_OPATT_SCHEMA_NAMING_CONTEXT_W = 'schemaNamingContext';
  {$EXTERNALSYM LDAP_OPATT_SCHEMA_NAMING_CONTEXT_W}

  LDAP_OPATT_CONFIG_NAMING_CONTEXT   = 'configurationNamingContext';
  {$EXTERNALSYM LDAP_OPATT_CONFIG_NAMING_CONTEXT}
  LDAP_OPATT_CONFIG_NAMING_CONTEXT_W = 'configurationNamingContext';
  {$EXTERNALSYM LDAP_OPATT_CONFIG_NAMING_CONTEXT_W}

  LDAP_OPATT_ROOT_DOMAIN_NAMING_CONTEXT   = 'rootDomainNamingContext';
  {$EXTERNALSYM LDAP_OPATT_ROOT_DOMAIN_NAMING_CONTEXT}
  LDAP_OPATT_ROOT_DOMAIN_NAMING_CONTEXT_W = 'rootDomainNamingContext';
  {$EXTERNALSYM LDAP_OPATT_ROOT_DOMAIN_NAMING_CONTEXT_W}

  LDAP_OPATT_SUPPORTED_SASL_MECHANISM   = 'supportedSASLMechanisms';
  {$EXTERNALSYM LDAP_OPATT_SUPPORTED_SASL_MECHANISM}
  LDAP_OPATT_SUPPORTED_SASL_MECHANISM_W = 'supportedSASLMechanisms';
  {$EXTERNALSYM LDAP_OPATT_SUPPORTED_SASL_MECHANISM_W}

  LDAP_OPATT_DNS_HOST_NAME   = 'dnsHostName';
  {$EXTERNALSYM LDAP_OPATT_DNS_HOST_NAME}
  LDAP_OPATT_DNS_HOST_NAME_W = 'dnsHostName';
  {$EXTERNALSYM LDAP_OPATT_DNS_HOST_NAME_W}

  LDAP_OPATT_LDAP_SERVICE_NAME   = 'ldapServiceName';
  {$EXTERNALSYM LDAP_OPATT_LDAP_SERVICE_NAME}
  LDAP_OPATT_LDAP_SERVICE_NAME_W = 'ldapServiceName';
  {$EXTERNALSYM LDAP_OPATT_LDAP_SERVICE_NAME_W}

  LDAP_OPATT_DS_SERVICE_NAME   = 'dsServiceName';
  {$EXTERNALSYM LDAP_OPATT_DS_SERVICE_NAME}
  LDAP_OPATT_DS_SERVICE_NAME_W = 'dsServiceName';
  {$EXTERNALSYM LDAP_OPATT_DS_SERVICE_NAME_W}

  LDAP_OPATT_SUPPORTED_CAPABILITIES   = 'supportedCapabilities';
  {$EXTERNALSYM LDAP_OPATT_SUPPORTED_CAPABILITIES}
  LDAP_OPATT_SUPPORTED_CAPABILITIES_W = 'supportedCapabilities';
  {$EXTERNALSYM LDAP_OPATT_SUPPORTED_CAPABILITIES_W}

//
// End of Operational attributes
//



//
//
// Server Capabilities
//

//
// NT5 Active Directory
//

  LDAP_CAP_ACTIVE_DIRECTORY_OID   = '1.2.840.113556.1.4.800';
  {$EXTERNALSYM LDAP_CAP_ACTIVE_DIRECTORY_OID}
  LDAP_CAP_ACTIVE_DIRECTORY_OID_W = '1.2.840.113556.1.4.800';
  {$EXTERNALSYM LDAP_CAP_ACTIVE_DIRECTORY_OID_W}

//
//  End of capabilities
//


//
//
// Matching Rules
//

//
// BIT AND
//

  LDAP_MATCHING_RULE_BIT_AND   = '1.2.840.113556.1.4.803';
  {$EXTERNALSYM LDAP_MATCHING_RULE_BIT_AND}
  LDAP_MATCHING_RULE_BIT_AND_W = '1.2.840.113556.1.4.803';
  {$EXTERNALSYM LDAP_MATCHING_RULE_BIT_AND_W}

//
// BIT OR
//

  LDAP_MATCHING_RULE_BIT_OR   = '1.2.840.113556.1.4.804';
  {$EXTERNALSYM LDAP_MATCHING_RULE_BIT_OR}
  LDAP_MATCHING_RULE_BIT_OR_W = '1.2.840.113556.1.4.804';
  {$EXTERNALSYM LDAP_MATCHING_RULE_BIT_OR_W}

implementation

end.
