{******************************************************************************}
{                                                       	               }
{ NT Bug Codes API interface Unit for Object Pascal                            }
{                                                       	               }
{ Portions created by Microsoft are Copyright (C) 1995-2001 Microsoft          }
{ Corporation. All Rights Reserved.                                            }
{ 								               }
{ The original file is: bugcodes.h, released June 2000. The original Pascal    }
{ code is: BugCodes.pas, released December 2000. The initial developer of the  }
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

unit JwaBugCodes;

{$WEAKPACKAGEUNIT}

{$HPPEMIT ''}
{$HPPEMIT '#include "bugcodes.h"'}
{$HPPEMIT ''}

{$I WINDEFINES.INC}

interface

uses
  JwaWinType;

{$I WINDEFINES.INC}

//
//  Values are 32 bit values layed out as follows:
//
//   3 3 2 2 2 2 2 2 2 2 2 2 1 1 1 1 1 1 1 1 1 1
//   1 0 9 8 7 6 5 4 3 2 1 0 9 8 7 6 5 4 3 2 1 0 9 8 7 6 5 4 3 2 1 0
//  +---+-+-+-----------------------+-------------------------------+
//  |Sev|C|R|     Facility          |               Code            |
//  +---+-+-+-----------------------+-------------------------------+
//
//  where
//
//      Sev - is the severity code
//
//          00 - Success
//          01 - Informational
//          10 - Warning
//          11 - Error
//
//      C - is the Customer code flag
//
//      R - is a reserved bit
//
//      Facility - is the facility code
//
//      Code - is the facility's status code
//
//
// Define the facility codes
//


//
// Define the severity codes
//

const

//
// MessageId: APC_INDEX_MISMATCH
//
// MessageText:
//
//  APC_INDEX_MISMATCH
//

  APC_INDEX_MISMATCH = ULONG($00000001);
  {$EXTERNALSYM APC_INDEX_MISMATCH}

//
// MessageId: DEVICE_QUEUE_NOT_BUSY
//
// MessageText:
//
//  DEVICE_QUEUE_NOT_BUSY
//

  DEVICE_QUEUE_NOT_BUSY = ULONG($00000002);
  {$EXTERNALSYM DEVICE_QUEUE_NOT_BUSY}

//
// MessageId: INVALID_AFFINITY_SET
//
// MessageText:
//
//  INVALID_AFFINITY_SET
//

  INVALID_AFFINITY_SET = ULONG($00000003);
  {$EXTERNALSYM INVALID_AFFINITY_SET}

//
// MessageId: INVALID_DATA_ACCESS_TRAP
//
// MessageText:
//
//  INVALID_DATA_ACCESS_TRAP
//

  INVALID_DATA_ACCESS_TRAP = ULONG($00000004);
  {$EXTERNALSYM INVALID_DATA_ACCESS_TRAP}

//
// MessageId: INVALID_PROCESS_ATTACH_ATTEMPT
//
// MessageText:
//
//  INVALID_PROCESS_ATTACH_ATTEMPT
//

  INVALID_PROCESS_ATTACH_ATTEMPT = ULONG($00000005);
  {$EXTERNALSYM INVALID_PROCESS_ATTACH_ATTEMPT}

//
// MessageId: INVALID_PROCESS_DETACH_ATTEMPT
//
// MessageText:
//
//  INVALID_PROCESS_DETACH_ATTEMPT
//

  INVALID_PROCESS_DETACH_ATTEMPT = ULONG($00000006);
  {$EXTERNALSYM INVALID_PROCESS_DETACH_ATTEMPT}

//
// MessageId: INVALID_SOFTWARE_INTERRUPT
//
// MessageText:
//
//  INVALID_SOFTWARE_INTERRUPT
//

  INVALID_SOFTWARE_INTERRUPT = ULONG($00000007);
  {$EXTERNALSYM INVALID_SOFTWARE_INTERRUPT}

//
// MessageId: IRQL_NOT_DISPATCH_LEVEL
//
// MessageText:
//
//  IRQL_NOT_DISPATCH_LEVEL
//

  IRQL_NOT_DISPATCH_LEVEL = ULONG($00000008);
  {$EXTERNALSYM IRQL_NOT_DISPATCH_LEVEL}

//
// MessageId: IRQL_NOT_GREATER_OR_EQUAL
//
// MessageText:
//
//  IRQL_NOT_GREATER_OR_EQUAL
//

  IRQL_NOT_GREATER_OR_EQUAL = ULONG($00000009);
  {$EXTERNALSYM IRQL_NOT_GREATER_OR_EQUAL}

//
// MessageId: IRQL_NOT_LESS_OR_EQUAL
//
// MessageText:
//
//  IRQL_NOT_LESS_OR_EQUAL
//

  IRQL_NOT_LESS_OR_EQUAL = ULONG($0000000A);
  {$EXTERNALSYM IRQL_NOT_LESS_OR_EQUAL}

//
// MessageId: NO_EXCEPTION_HANDLING_SUPPORT
//
// MessageText:
//
//  NO_EXCEPTION_HANDLING_SUPPORT
//

  NO_EXCEPTION_HANDLING_SUPPORT = ULONG($0000000B);
  {$EXTERNALSYM NO_EXCEPTION_HANDLING_SUPPORT}

//
// MessageId: MAXIMUM_WAIT_OBJECTS_EXCEEDED
//
// MessageText:
//
//  MAXIMUM_WAIT_OBJECTS_EXCEEDED
//

  MAXIMUM_WAIT_OBJECTS_EXCEEDED = ULONG($0000000C);
  {$EXTERNALSYM MAXIMUM_WAIT_OBJECTS_EXCEEDED}

//
// MessageId: MUTEX_LEVEL_NUMBER_VIOLATION
//
// MessageText:
//
//  MUTEX_LEVEL_NUMBER_VIOLATION
//

  MUTEX_LEVEL_NUMBER_VIOLATION = ULONG($0000000D);
  {$EXTERNALSYM MUTEX_LEVEL_NUMBER_VIOLATION}

//
// MessageId: NO_USER_MODE_CONTEXT
//
// MessageText:
//
//  NO_USER_MODE_CONTEXT
//

  NO_USER_MODE_CONTEXT = ULONG($0000000E);
  {$EXTERNALSYM NO_USER_MODE_CONTEXT}

//
// MessageId: SPIN_LOCK_ALREADY_OWNED
//
// MessageText:
//
//  SPIN_LOCK_ALREADY_OWNED
//

  SPIN_LOCK_ALREADY_OWNED = ULONG($0000000F);
  {$EXTERNALSYM SPIN_LOCK_ALREADY_OWNED}

//
// MessageId: SPIN_LOCK_NOT_OWNED
//
// MessageText:
//
//  SPIN_LOCK_NOT_OWNED
//

  SPIN_LOCK_NOT_OWNED = ULONG($00000010);
  {$EXTERNALSYM SPIN_LOCK_NOT_OWNED}

//
// MessageId: THREAD_NOT_MUTEX_OWNER
//
// MessageText:
//
//  THREAD_NOT_MUTEX_OWNER
//

  THREAD_NOT_MUTEX_OWNER = ULONG($00000011);
  {$EXTERNALSYM THREAD_NOT_MUTEX_OWNER}

//
// MessageId: TRAP_CAUSE_UNKNOWN
//
// MessageText:
//
//  TRAP_CAUSE_UNKNOWN
//

  TRAP_CAUSE_UNKNOWN = ULONG($00000012);
  {$EXTERNALSYM TRAP_CAUSE_UNKNOWN}

//
// MessageId: EMPTY_THREAD_REAPER_LIST
//
// MessageText:
//
//  EMPTY_THREAD_REAPER_LIST
//

  EMPTY_THREAD_REAPER_LIST = ULONG($00000013);
  {$EXTERNALSYM EMPTY_THREAD_REAPER_LIST}

//
// MessageId: CREATE_DELETE_LOCK_NOT_LOCKED
//
// MessageText:
//
//  CREATE_DELETE_LOCK_NOT_LOCKED
//

  CREATE_DELETE_LOCK_NOT_LOCKED = ULONG($00000014);
  {$EXTERNALSYM CREATE_DELETE_LOCK_NOT_LOCKED}

//
// MessageId: LAST_CHANCE_CALLED_FROM_KMODE
//
// MessageText:
//
//  LAST_CHANCE_CALLED_FROM_KMODE
//

  LAST_CHANCE_CALLED_FROM_KMODE = ULONG($00000015);
  {$EXTERNALSYM LAST_CHANCE_CALLED_FROM_KMODE}

//
// MessageId: CID_HANDLE_CREATION
//
// MessageText:
//
//  CID_HANDLE_CREATION
//

  CID_HANDLE_CREATION = ULONG($00000016);
  {$EXTERNALSYM CID_HANDLE_CREATION}

//
// MessageId: CID_HANDLE_DELETION
//
// MessageText:
//
//  CID_HANDLE_DELETION
//

  CID_HANDLE_DELETION = ULONG($00000017);
  {$EXTERNALSYM CID_HANDLE_DELETION}

//
// MessageId: REFERENCE_BY_POINTER
//
// MessageText:
//
//  REFERENCE_BY_POINTER
//

  REFERENCE_BY_POINTER = ULONG($00000018);
  {$EXTERNALSYM REFERENCE_BY_POINTER}

//
// MessageId: BAD_POOL_HEADER
//
// MessageText:
//
//  BAD_POOL_HEADER
//

  BAD_POOL_HEADER = ULONG($00000019);
  {$EXTERNALSYM BAD_POOL_HEADER}

//
// MessageId: MEMORY_MANAGEMENT
//
// MessageText:
//
//  MEMORY_MANAGEMENT
//

  MEMORY_MANAGEMENT = ULONG($0000001A);
  {$EXTERNALSYM MEMORY_MANAGEMENT}

//
// MessageId: PFN_SHARE_COUNT
//
// MessageText:
//
//  PFN_SHARE_COUNT
//

  PFN_SHARE_COUNT = ULONG($0000001B);
  {$EXTERNALSYM PFN_SHARE_COUNT}

//
// MessageId: PFN_REFERENCE_COUNT
//
// MessageText:
//
//  PFN_REFERENCE_COUNT
//

  PFN_REFERENCE_COUNT = ULONG($0000001C);
  {$EXTERNALSYM PFN_REFERENCE_COUNT}

//
// MessageId: NO_SPIN_LOCK_AVAILABLE
//
// MessageText:
//
//  NO_SPIN_LOCK_AVAILABLE
//

  NO_SPIN_LOCK_AVAILABLE = ULONG($0000001D);
  {$EXTERNALSYM NO_SPIN_LOCK_AVAILABLE}

//
// MessageId: KMODE_EXCEPTION_NOT_HANDLED
//
// MessageText:
//
//  KMODE_EXCEPTION_NOT_HANDLED
//

  KMODE_EXCEPTION_NOT_HANDLED = ULONG($0000001E);
  {$EXTERNALSYM KMODE_EXCEPTION_NOT_HANDLED}

//
// MessageId: SHARED_RESOURCE_CONV_ERROR
//
// MessageText:
//
//  SHARED_RESOURCE_CONV_ERROR
//

  SHARED_RESOURCE_CONV_ERROR = ULONG($0000001F);
  {$EXTERNALSYM SHARED_RESOURCE_CONV_ERROR}

//
// MessageId: KERNEL_APC_PENDING_DURING_EXIT
//
// MessageText:
//
//  KERNEL_APC_PENDING_DURING_EXIT
//

  KERNEL_APC_PENDING_DURING_EXIT = ULONG($00000020);
  {$EXTERNALSYM KERNEL_APC_PENDING_DURING_EXIT}

//
// MessageId: QUOTA_UNDERFLOW
//
// MessageText:
//
//  QUOTA_UNDERFLOW
//

  QUOTA_UNDERFLOW = ULONG($00000021);
  {$EXTERNALSYM QUOTA_UNDERFLOW}

//
// MessageId: FILE_SYSTEM
//
// MessageText:
//
//  FILE_SYSTEM
//

  FILE_SYSTEM = ULONG($00000022);
  {$EXTERNALSYM FILE_SYSTEM}

//
// MessageId: FAT_FILE_SYSTEM
//
// MessageText:
//
//  FAT_FILE_SYSTEM
//

  FAT_FILE_SYSTEM = ULONG($00000023);
  {$EXTERNALSYM FAT_FILE_SYSTEM}

//
// MessageId: NTFS_FILE_SYSTEM
//
// MessageText:
//
//  NTFS_FILE_SYSTEM
//

  NTFS_FILE_SYSTEM = ULONG($00000024);
  {$EXTERNALSYM NTFS_FILE_SYSTEM}

//
// MessageId: NPFS_FILE_SYSTEM
//
// MessageText:
//
//  NPFS_FILE_SYSTEM
//

  NPFS_FILE_SYSTEM = ULONG($00000025);
  {$EXTERNALSYM NPFS_FILE_SYSTEM}

//
// MessageId: CDFS_FILE_SYSTEM
//
// MessageText:
//
//  CDFS_FILE_SYSTEM
//

  CDFS_FILE_SYSTEM = ULONG($00000026);
  {$EXTERNALSYM CDFS_FILE_SYSTEM}

//
// MessageId: RDR_FILE_SYSTEM
//
// MessageText:
//
//  RDR_FILE_SYSTEM
//

  RDR_FILE_SYSTEM = ULONG($00000027);
  {$EXTERNALSYM RDR_FILE_SYSTEM}

//
// MessageId: CORRUPT_ACCESS_TOKEN
//
// MessageText:
//
//  CORRUPT_ACCESS_TOKEN
//

  CORRUPT_ACCESS_TOKEN = ULONG($00000028);
  {$EXTERNALSYM CORRUPT_ACCESS_TOKEN}

//
// MessageId: SECURITY_SYSTEM
//
// MessageText:
//
//  SECURITY_SYSTEM
//

  SECURITY_SYSTEM = ULONG($00000029);
  {$EXTERNALSYM SECURITY_SYSTEM}

//
// MessageId: INCONSISTENT_IRP
//
// MessageText:
//
//  INCONSISTENT_IRP
//

  INCONSISTENT_IRP = ULONG($0000002A);
  {$EXTERNALSYM INCONSISTENT_IRP}

//
// MessageId: PANIC_STACK_SWITCH
//
// MessageText:
//
//  PANIC_STACK_SWITCH
//

  PANIC_STACK_SWITCH = ULONG($0000002B);
  {$EXTERNALSYM PANIC_STACK_SWITCH}

//
// MessageId: PORT_DRIVER_INTERNAL
//
// MessageText:
//
//  PORT_DRIVER_INTERNAL
//

  PORT_DRIVER_INTERNAL = ULONG($0000002C);
  {$EXTERNALSYM PORT_DRIVER_INTERNAL}

//
// MessageId: SCSI_DISK_DRIVER_INTERNAL
//
// MessageText:
//
//  SCSI_DISK_DRIVER_INTERNAL
//

  SCSI_DISK_DRIVER_INTERNAL = ULONG($0000002D);
  {$EXTERNALSYM SCSI_DISK_DRIVER_INTERNAL}

//
// MessageId: DATA_BUS_ERROR
//
// MessageText:
//
//  DATA_BUS_ERROR
//

  DATA_BUS_ERROR = ULONG($0000002E);
  {$EXTERNALSYM DATA_BUS_ERROR}

//
// MessageId: INSTRUCTION_BUS_ERROR
//
// MessageText:
//
//  INSTRUCTION_BUS_ERROR
//

  INSTRUCTION_BUS_ERROR = ULONG($0000002F);
  {$EXTERNALSYM INSTRUCTION_BUS_ERROR}

//
// MessageId: SET_OF_INVALID_CONTEXT
//
// MessageText:
//
//  SET_OF_INVALID_CONTEXT
//

  SET_OF_INVALID_CONTEXT = ULONG($00000030);
  {$EXTERNALSYM SET_OF_INVALID_CONTEXT}

//
// MessageId: PHASE0_INITIALIZATION_FAILED
//
// MessageText:
//
//  PHASE0_INITIALIZATION_FAILED
//

  PHASE0_INITIALIZATION_FAILED = ULONG($00000031);
  {$EXTERNALSYM PHASE0_INITIALIZATION_FAILED}

//
// MessageId: PHASE1_INITIALIZATION_FAILED
//
// MessageText:
//
//  PHASE1_INITIALIZATION_FAILED
//

  PHASE1_INITIALIZATION_FAILED = ULONG($00000032);
  {$EXTERNALSYM PHASE1_INITIALIZATION_FAILED}

//
// MessageId: UNEXPECTED_INITIALIZATION_CALL
//
// MessageText:
//
//  UNEXPECTED_INITIALIZATION_CALL
//

  UNEXPECTED_INITIALIZATION_CALL = ULONG($00000033);
  {$EXTERNALSYM UNEXPECTED_INITIALIZATION_CALL}

//
// MessageId: CACHE_MANAGER
//
// MessageText:
//
//  CACHE_MANAGER
//

  CACHE_MANAGER = ULONG($00000034);
  {$EXTERNALSYM CACHE_MANAGER}

//
// MessageId: NO_MORE_IRP_STACK_LOCATIONS
//
// MessageText:
//
//  NO_MORE_IRP_STACK_LOCATIONS
//

  NO_MORE_IRP_STACK_LOCATIONS = ULONG($00000035);
  {$EXTERNALSYM NO_MORE_IRP_STACK_LOCATIONS}

//
// MessageId: DEVICE_REFERENCE_COUNT_NOT_ZERO
//
// MessageText:
//
//  DEVICE_REFERENCE_COUNT_NOT_ZERO
//

  DEVICE_REFERENCE_COUNT_NOT_ZERO = ULONG($00000036);
  {$EXTERNALSYM DEVICE_REFERENCE_COUNT_NOT_ZERO}

//
// MessageId: FLOPPY_INTERNAL_ERROR
//
// MessageText:
//
//  FLOPPY_INTERNAL_ERROR
//

  FLOPPY_INTERNAL_ERROR = ULONG($00000037);
  {$EXTERNALSYM FLOPPY_INTERNAL_ERROR}

//
// MessageId: SERIAL_DRIVER_INTERNAL
//
// MessageText:
//
//  SERIAL_DRIVER_INTERNAL
//

  SERIAL_DRIVER_INTERNAL = ULONG($00000038);
  {$EXTERNALSYM SERIAL_DRIVER_INTERNAL}

//
// MessageId: SYSTEM_EXIT_OWNED_MUTEX
//
// MessageText:
//
//  SYSTEM_EXIT_OWNED_MUTEX
//

  SYSTEM_EXIT_OWNED_MUTEX = ULONG($00000039);
  {$EXTERNALSYM SYSTEM_EXIT_OWNED_MUTEX}

//
// MessageId: SYSTEM_UNWIND_PREVIOUS_USER
//
// MessageText:
//
//  SYSTEM_UNWIND_PREVIOUS_USER
//

  SYSTEM_UNWIND_PREVIOUS_USER = ULONG($0000003A);
  {$EXTERNALSYM SYSTEM_UNWIND_PREVIOUS_USER}

//
// MessageId: SYSTEM_SERVICE_EXCEPTION
//
// MessageText:
//
//  SYSTEM_SERVICE_EXCEPTION
//

  SYSTEM_SERVICE_EXCEPTION = ULONG($0000003B);
  {$EXTERNALSYM SYSTEM_SERVICE_EXCEPTION}

//
// MessageId: INTERRUPT_UNWIND_ATTEMPTED
//
// MessageText:
//
//  INTERRUPT_UNWIND_ATTEMPTED
//

  INTERRUPT_UNWIND_ATTEMPTED = ULONG($0000003C);
  {$EXTERNALSYM INTERRUPT_UNWIND_ATTEMPTED}

//
// MessageId: INTERRUPT_EXCEPTION_NOT_HANDLED
//
// MessageText:
//
//  INTERRUPT_EXCEPTION_NOT_HANDLED
//

  INTERRUPT_EXCEPTION_NOT_HANDLED = ULONG($0000003D);
  {$EXTERNALSYM INTERRUPT_EXCEPTION_NOT_HANDLED}

//
// MessageId: MULTIPROCESSOR_CONFIGURATION_NOT_SUPPORTED
//
// MessageText:
//
//  MULTIPROCESSOR_CONFIGURATION_NOT_SUPPORTED
//

  MULTIPROCESSOR_CONFIGURATION_NOT_SUPPORTED = ULONG($0000003E);
  {$EXTERNALSYM MULTIPROCESSOR_CONFIGURATION_NOT_SUPPORTED}

//
// MessageId: NO_MORE_SYSTEM_PTES
//
// MessageText:
//
//  NO_MORE_SYSTEM_PTES
//

  NO_MORE_SYSTEM_PTES = ULONG($0000003F);
  {$EXTERNALSYM NO_MORE_SYSTEM_PTES}

//
// MessageId: TARGET_MDL_TOO_SMALL
//
// MessageText:
//
//  TARGET_MDL_TOO_SMALL
//

  TARGET_MDL_TOO_SMALL = ULONG($00000040);
  {$EXTERNALSYM TARGET_MDL_TOO_SMALL}

//
// MessageId: MUST_SUCCEED_POOL_EMPTY
//
// MessageText:
//
//  MUST_SUCCEED_POOL_EMPTY
//

  MUST_SUCCEED_POOL_EMPTY = ULONG($00000041);
  {$EXTERNALSYM MUST_SUCCEED_POOL_EMPTY}

//
// MessageId: ATDISK_DRIVER_INTERNAL
//
// MessageText:
//
//  ATDISK_DRIVER_INTERNAL
//

  ATDISK_DRIVER_INTERNAL = ULONG($00000042);
  {$EXTERNALSYM ATDISK_DRIVER_INTERNAL}

//
// MessageId: NO_SUCH_PARTITION
//
// MessageText:
//
//  NO_SUCH_PARTITION
//

  NO_SUCH_PARTITION = ULONG($00000043);
  {$EXTERNALSYM NO_SUCH_PARTITION}

//
// MessageId: MULTIPLE_IRP_COMPLETE_REQUESTS
//
// MessageText:
//
//  MULTIPLE_IRP_COMPLETE_REQUESTS
//

  MULTIPLE_IRP_COMPLETE_REQUESTS = ULONG($00000044);
  {$EXTERNALSYM MULTIPLE_IRP_COMPLETE_REQUESTS}

//
// MessageId: INSUFFICIENT_SYSTEM_MAP_REGS
//
// MessageText:
//
//  INSUFFICIENT_SYSTEM_MAP_REGS
//

  INSUFFICIENT_SYSTEM_MAP_REGS = ULONG($00000045);
  {$EXTERNALSYM INSUFFICIENT_SYSTEM_MAP_REGS}

//
// MessageId: DEREF_UNKNOWN_LOGON_SESSION
//
// MessageText:
//
//  DEREF_UNKNOWN_LOGON_SESSION
//

  DEREF_UNKNOWN_LOGON_SESSION = ULONG($00000046);
  {$EXTERNALSYM DEREF_UNKNOWN_LOGON_SESSION}

//
// MessageId: REF_UNKNOWN_LOGON_SESSION
//
// MessageText:
//
//  REF_UNKNOWN_LOGON_SESSION
//

  REF_UNKNOWN_LOGON_SESSION = ULONG($00000047);
  {$EXTERNALSYM REF_UNKNOWN_LOGON_SESSION}

//
// MessageId: CANCEL_STATE_IN_COMPLETED_IRP
//
// MessageText:
//
//  CANCEL_STATE_IN_COMPLETED_IRP
//

  CANCEL_STATE_IN_COMPLETED_IRP = ULONG($00000048);
  {$EXTERNALSYM CANCEL_STATE_IN_COMPLETED_IRP}

//
// MessageId: PAGE_FAULT_WITH_INTERRUPTS_OFF
//
// MessageText:
//
//  PAGE_FAULT_WITH_INTERRUPTS_OFF
//

  PAGE_FAULT_WITH_INTERRUPTS_OFF = ULONG($00000049);
  {$EXTERNALSYM PAGE_FAULT_WITH_INTERRUPTS_OFF}

//
// MessageId: IRQL_GT_ZERO_AT_SYSTEM_SERVICE
//
// MessageText:
//
//  IRQL_GT_ZERO_AT_SYSTEM_SERVICE
//

  IRQL_GT_ZERO_AT_SYSTEM_SERVICE = ULONG($0000004A);
  {$EXTERNALSYM IRQL_GT_ZERO_AT_SYSTEM_SERVICE}

//
// MessageId: STREAMS_INTERNAL_ERROR
//
// MessageText:
//
//  STREAMS_INTERNAL_ERROR
//

  STREAMS_INTERNAL_ERROR = ULONG($0000004B);
  {$EXTERNALSYM STREAMS_INTERNAL_ERROR}

//
// MessageId: FATAL_UNHANDLED_HARD_ERROR
//
// MessageText:
//
//  FATAL_UNHANDLED_HARD_ERROR
//

  FATAL_UNHANDLED_HARD_ERROR = ULONG($0000004C);
  {$EXTERNALSYM FATAL_UNHANDLED_HARD_ERROR}

//
// MessageId: NO_PAGES_AVAILABLE
//
// MessageText:
//
//  NO_PAGES_AVAILABLE
//

  NO_PAGES_AVAILABLE = ULONG($0000004D);
  {$EXTERNALSYM NO_PAGES_AVAILABLE}

//
// MessageId: PFN_LIST_CORRUPT
//
// MessageText:
//
//  PFN_LIST_CORRUPT
//

  PFN_LIST_CORRUPT = ULONG($0000004E);
  {$EXTERNALSYM PFN_LIST_CORRUPT}

//
// MessageId: NDIS_INTERNAL_ERROR
//
// MessageText:
//
//  NDIS_INTERNAL_ERROR
//

  NDIS_INTERNAL_ERROR = ULONG($0000004F);
  {$EXTERNALSYM NDIS_INTERNAL_ERROR}

//
// MessageId: PAGE_FAULT_IN_NONPAGED_AREA
//
// MessageText:
//
//  PAGE_FAULT_IN_NONPAGED_AREA
//

  PAGE_FAULT_IN_NONPAGED_AREA = ULONG($00000050);
  {$EXTERNALSYM PAGE_FAULT_IN_NONPAGED_AREA}

//
// MessageId: REGISTRY_ERROR
//
// MessageText:
//
//  REGISTRY_ERROR
//

  REGISTRY_ERROR = ULONG($00000051);
  {$EXTERNALSYM REGISTRY_ERROR}

//
// MessageId: MAILSLOT_FILE_SYSTEM
//
// MessageText:
//
//  MAILSLOT_FILE_SYSTEM
//

  MAILSLOT_FILE_SYSTEM = ULONG($00000052);
  {$EXTERNALSYM MAILSLOT_FILE_SYSTEM}

//
// MessageId: NO_BOOT_DEVICE
//
// MessageText:
//
//  NO_BOOT_DEVICE
//

  NO_BOOT_DEVICE = ULONG($00000053);
  {$EXTERNALSYM NO_BOOT_DEVICE}

//
// MessageId: LM_SERVER_INTERNAL_ERROR
//
// MessageText:
//
//  LM_SERVER_INTERNAL_ERROR
//

  LM_SERVER_INTERNAL_ERROR = ULONG($00000054);
  {$EXTERNALSYM LM_SERVER_INTERNAL_ERROR}

//
// MessageId: DATA_COHERENCY_EXCEPTION
//
// MessageText:
//
//  DATA_COHERENCY_EXCEPTION
//

  DATA_COHERENCY_EXCEPTION = ULONG($00000055);
  {$EXTERNALSYM DATA_COHERENCY_EXCEPTION}

//
// MessageId: INSTRUCTION_COHERENCY_EXCEPTION
//
// MessageText:
//
//  INSTRUCTION_COHERENCY_EXCEPTION
//

  INSTRUCTION_COHERENCY_EXCEPTION = ULONG($00000056);
  {$EXTERNALSYM INSTRUCTION_COHERENCY_EXCEPTION}

//
// MessageId: XNS_INTERNAL_ERROR
//
// MessageText:
//
//  XNS_INTERNAL_ERROR
//

  XNS_INTERNAL_ERROR = ULONG($00000057);
  {$EXTERNALSYM XNS_INTERNAL_ERROR}

//
// MessageId: FTDISK_INTERNAL_ERROR
//
// MessageText:
//
//  FTDISK_INTERNAL_ERROR
//

  FTDISK_INTERNAL_ERROR = ULONG($00000058);
  {$EXTERNALSYM FTDISK_INTERNAL_ERROR}

//
// MessageId: PINBALL_FILE_SYSTEM
//
// MessageText:
//
//  PINBALL_FILE_SYSTEM
//

  PINBALL_FILE_SYSTEM = ULONG($00000059);
  {$EXTERNALSYM PINBALL_FILE_SYSTEM}

//
// MessageId: CRITICAL_SERVICE_FAILED
//
// MessageText:
//
//  CRITICAL_SERVICE_FAILED
//

  CRITICAL_SERVICE_FAILED = ULONG($0000005A);
  {$EXTERNALSYM CRITICAL_SERVICE_FAILED}

//
// MessageId: SET_ENV_VAR_FAILED
//
// MessageText:
//
//  SET_ENV_VAR_FAILED
//

  SET_ENV_VAR_FAILED = ULONG($0000005B);
  {$EXTERNALSYM SET_ENV_VAR_FAILED}

//
// MessageId: HAL_INITIALIZATION_FAILED
//
// MessageText:
//
//  HAL_INITIALIZATION_FAILED
//

  HAL_INITIALIZATION_FAILED = ULONG($0000005C);
  {$EXTERNALSYM HAL_INITIALIZATION_FAILED}

//
// MessageId: UNSUPPORTED_PROCESSOR
//
// MessageText:
//
//  UNSUPPORTED_PROCESSOR
//

  UNSUPPORTED_PROCESSOR = ULONG($0000005D);
  {$EXTERNALSYM UNSUPPORTED_PROCESSOR}

//
// MessageId: OBJECT_INITIALIZATION_FAILED
//
// MessageText:
//
//  OBJECT_INITIALIZATION_FAILED
//

  OBJECT_INITIALIZATION_FAILED = ULONG($0000005E);
  {$EXTERNALSYM OBJECT_INITIALIZATION_FAILED}

//
// MessageId: SECURITY_INITIALIZATION_FAILED
//
// MessageText:
//
//  SECURITY_INITIALIZATION_FAILED
//

  SECURITY_INITIALIZATION_FAILED = ULONG($0000005F);
  {$EXTERNALSYM SECURITY_INITIALIZATION_FAILED}

//
// MessageId: PROCESS_INITIALIZATION_FAILED
//
// MessageText:
//
//  PROCESS_INITIALIZATION_FAILED
//

  PROCESS_INITIALIZATION_FAILED = ULONG($00000060);
  {$EXTERNALSYM PROCESS_INITIALIZATION_FAILED}

//
// MessageId: HAL1_INITIALIZATION_FAILED
//
// MessageText:
//
//  HAL1_INITIALIZATION_FAILED
//

  HAL1_INITIALIZATION_FAILED = ULONG($00000061);
  {$EXTERNALSYM HAL1_INITIALIZATION_FAILED}

//
// MessageId: OBJECT1_INITIALIZATION_FAILED
//
// MessageText:
//
//  OBJECT1_INITIALIZATION_FAILED
//

  OBJECT1_INITIALIZATION_FAILED = ULONG($00000062);
  {$EXTERNALSYM OBJECT1_INITIALIZATION_FAILED}

//
// MessageId: SECURITY1_INITIALIZATION_FAILED
//
// MessageText:
//
//  SECURITY1_INITIALIZATION_FAILED
//

  SECURITY1_INITIALIZATION_FAILED = ULONG($00000063);
  {$EXTERNALSYM SECURITY1_INITIALIZATION_FAILED}

//
// MessageId: SYMBOLIC_INITIALIZATION_FAILED
//
// MessageText:
//
//  SYMBOLIC_INITIALIZATION_FAILED
//

  SYMBOLIC_INITIALIZATION_FAILED = ULONG($00000064);
  {$EXTERNALSYM SYMBOLIC_INITIALIZATION_FAILED}

//
// MessageId: MEMORY1_INITIALIZATION_FAILED
//
// MessageText:
//
//  MEMORY1_INITIALIZATION_FAILED
//

  MEMORY1_INITIALIZATION_FAILED = ULONG($00000065);
  {$EXTERNALSYM MEMORY1_INITIALIZATION_FAILED}

//
// MessageId: CACHE_INITIALIZATION_FAILED
//
// MessageText:
//
//  CACHE_INITIALIZATION_FAILED
//

  CACHE_INITIALIZATION_FAILED = ULONG($00000066);
  {$EXTERNALSYM CACHE_INITIALIZATION_FAILED}

//
// MessageId: CONFIG_INITIALIZATION_FAILED
//
// MessageText:
//
//  CONFIG_INITIALIZATION_FAILED
//

  CONFIG_INITIALIZATION_FAILED = ULONG($00000067);
  {$EXTERNALSYM CONFIG_INITIALIZATION_FAILED}

//
// MessageId: FILE_INITIALIZATION_FAILED
//
// MessageText:
//
//  FILE_INITIALIZATION_FAILED
//

  FILE_INITIALIZATION_FAILED = ULONG($00000068);
  {$EXTERNALSYM FILE_INITIALIZATION_FAILED}

//
// MessageId: IO1_INITIALIZATION_FAILED
//
// MessageText:
//
//  IO1_INITIALIZATION_FAILED
//

  IO1_INITIALIZATION_FAILED = ULONG($00000069);
  {$EXTERNALSYM IO1_INITIALIZATION_FAILED}

//
// MessageId: LPC_INITIALIZATION_FAILED
//
// MessageText:
//
//  LPC_INITIALIZATION_FAILED
//

  LPC_INITIALIZATION_FAILED = ULONG($0000006A);
  {$EXTERNALSYM LPC_INITIALIZATION_FAILED}

//
// MessageId: PROCESS1_INITIALIZATION_FAILED
//
// MessageText:
//
//  PROCESS1_INITIALIZATION_FAILED
//

  PROCESS1_INITIALIZATION_FAILED = ULONG($0000006B);
  {$EXTERNALSYM PROCESS1_INITIALIZATION_FAILED}

//
// MessageId: REFMON_INITIALIZATION_FAILED
//
// MessageText:
//
//  REFMON_INITIALIZATION_FAILED
//

  REFMON_INITIALIZATION_FAILED = ULONG($0000006C);
  {$EXTERNALSYM REFMON_INITIALIZATION_FAILED}

//
// MessageId: SESSION1_INITIALIZATION_FAILED
//
// MessageText:
//
//  SESSION1_INITIALIZATION_FAILED
//

  SESSION1_INITIALIZATION_FAILED = ULONG($0000006D);
  {$EXTERNALSYM SESSION1_INITIALIZATION_FAILED}

//
// MessageId: SESSION2_INITIALIZATION_FAILED
//
// MessageText:
//
//  SESSION2_INITIALIZATION_FAILED
//

  SESSION2_INITIALIZATION_FAILED = ULONG($0000006E);
  {$EXTERNALSYM SESSION2_INITIALIZATION_FAILED}

//
// MessageId: SESSION3_INITIALIZATION_FAILED
//
// MessageText:
//
//  SESSION3_INITIALIZATION_FAILED
//

  SESSION3_INITIALIZATION_FAILED = ULONG($0000006F);
  {$EXTERNALSYM SESSION3_INITIALIZATION_FAILED}

//
// MessageId: SESSION4_INITIALIZATION_FAILED
//
// MessageText:
//
//  SESSION4_INITIALIZATION_FAILED
//

  SESSION4_INITIALIZATION_FAILED = ULONG($00000070);
  {$EXTERNALSYM SESSION4_INITIALIZATION_FAILED}

//
// MessageId: SESSION5_INITIALIZATION_FAILED
//
// MessageText:
//
//  SESSION5_INITIALIZATION_FAILED
//

  SESSION5_INITIALIZATION_FAILED = ULONG($00000071);
  {$EXTERNALSYM SESSION5_INITIALIZATION_FAILED}

//
// MessageId: ASSIGN_DRIVE_LETTERS_FAILED
//
// MessageText:
//
//  ASSIGN_DRIVE_LETTERS_FAILED
//

  ASSIGN_DRIVE_LETTERS_FAILED = ULONG($00000072);
  {$EXTERNALSYM ASSIGN_DRIVE_LETTERS_FAILED}

//
// MessageId: CONFIG_LIST_FAILED
//
// MessageText:
//
//  CONFIG_LIST_FAILED
//

  CONFIG_LIST_FAILED = ULONG($00000073);
  {$EXTERNALSYM CONFIG_LIST_FAILED}

//
// MessageId: BAD_SYSTEM_CONFIG_INFO
//
// MessageText:
//
//  BAD_SYSTEM_CONFIG_INFO
//

  BAD_SYSTEM_CONFIG_INFO = ULONG($00000074);
  {$EXTERNALSYM BAD_SYSTEM_CONFIG_INFO}

//
// MessageId: CANNOT_WRITE_CONFIGURATION
//
// MessageText:
//
//  CANNOT_WRITE_CONFIGURATION
//

  CANNOT_WRITE_CONFIGURATION = ULONG($00000075);
  {$EXTERNALSYM CANNOT_WRITE_CONFIGURATION}

//
// MessageId: PROCESS_HAS_LOCKED_PAGES
//
// MessageText:
//
//  PROCESS_HAS_LOCKED_PAGES
//

  PROCESS_HAS_LOCKED_PAGES = ULONG($00000076);
  {$EXTERNALSYM PROCESS_HAS_LOCKED_PAGES}

//
// MessageId: KERNEL_STACK_INPAGE_ERROR
//
// MessageText:
//
//  KERNEL_STACK_INPAGE_ERROR
//

  KERNEL_STACK_INPAGE_ERROR = ULONG($00000077);
  {$EXTERNALSYM KERNEL_STACK_INPAGE_ERROR}

//
// MessageId: PHASE0_EXCEPTION
//
// MessageText:
//
//  PHASE0_EXCEPTION
//

  PHASE0_EXCEPTION = ULONG($00000078);
  {$EXTERNALSYM PHASE0_EXCEPTION}

//
// MessageId: MISMATCHED_HAL
//
// MessageText:
//
//  Mismatched kernel and hal image.
//

  MISMATCHED_HAL = ULONG($00000079);
  {$EXTERNALSYM MISMATCHED_HAL}

//
// MessageId: KERNEL_DATA_INPAGE_ERROR
//
// MessageText:
//
//  KERNEL_DATA_INPAGE_ERROR
//

  KERNEL_DATA_INPAGE_ERROR = ULONG($0000007A);
  {$EXTERNALSYM KERNEL_DATA_INPAGE_ERROR}

//
// MessageId: INACCESSIBLE_BOOT_DEVICE
//
// MessageText:
//
//  INACCESSIBLE_BOOT_DEVICE
//

  INACCESSIBLE_BOOT_DEVICE = ULONG($0000007B);
  {$EXTERNALSYM INACCESSIBLE_BOOT_DEVICE}

//
// MessageId: BUGCODE_PSS_MESSAGE
//
// MessageText:
//
//  If this is the first time you've seen this Stop error screen,
//  restart your computer. If this screen appears again, follow
//  these steps:
//  
//  Check to make sure any new hardware or software is properly installed.
//  If this is a new installation, ask your hardware or software manufacturer
//  for any Windows 2000 updates you might need.
//  
//  If problems continue, disable or remove any newly installed hardware
//  or software. Disable BIOS memory options such as caching or shadowing.
//  If you need to use Safe Mode to remove or disable components, restart
//  your computer, press F8 to select Advanced Startup Options, and then
//  select Safe Mode.
//  
//  Refer to your Getting Started manual for more information on
//  troubleshooting Stop errors.
//

  BUGCODE_PSS_MESSAGE = ULONG($0000007C);
  {$EXTERNALSYM BUGCODE_PSS_MESSAGE}

//
// MessageId: INSTALL_MORE_MEMORY
//
// MessageText:
//
//  INSTALL_MORE_MEMORY
//

  INSTALL_MORE_MEMORY = ULONG($0000007D);
  {$EXTERNALSYM INSTALL_MORE_MEMORY}

//
// MessageId: WINDOWS_NT_BANNER
//
// MessageText:
//
//  Microsoft (R) Windows 2000 (R) Version %hs (Build %u%hs)
//

  WINDOWS_NT_BANNER = ULONG($4000007E);
  {$EXTERNALSYM WINDOWS_NT_BANNER}

//
// MessageId: UNEXPECTED_KERNEL_MODE_TRAP
//
// MessageText:
//
//  UNEXPECTED_KERNEL_MODE_TRAP
//

  UNEXPECTED_KERNEL_MODE_TRAP = ULONG($0000007F);
  {$EXTERNALSYM UNEXPECTED_KERNEL_MODE_TRAP}

//
// MessageId: NMI_HARDWARE_FAILURE
//
// MessageText:
//
//  Hardware malfunction.
//

  NMI_HARDWARE_FAILURE = ULONG($00000080);
  {$EXTERNALSYM NMI_HARDWARE_FAILURE}

//
// MessageId: SPIN_LOCK_INIT_FAILURE
//
// MessageText:
//
//  SPIN_LOCK_INIT_FAILURE
//

  SPIN_LOCK_INIT_FAILURE = ULONG($00000081);
  {$EXTERNALSYM SPIN_LOCK_INIT_FAILURE}

//
// MessageId: DFS_FILE_SYSTEM
//
// MessageText:
//
//  DFS_FILE_SYSTEM
//

  DFS_FILE_SYSTEM = ULONG($00000082);
  {$EXTERNALSYM DFS_FILE_SYSTEM}

//
// MessageId: OFS_FILE_SYSTEM
//
// MessageText:
//
//  OFS_FILE_SYSTEM
//

  OFS_FILE_SYSTEM = ULONG($00000083);
  {$EXTERNALSYM OFS_FILE_SYSTEM}

//
// MessageId: RECOM_DRIVER
//
// MessageText:
//
//  RECOM_DRIVER
//

  RECOM_DRIVER = ULONG($00000084);
  {$EXTERNALSYM RECOM_DRIVER}

//
// MessageId: SETUP_FAILURE
//
// MessageText:
//
//  SETUP_FAILURE
//

  SETUP_FAILURE = ULONG($00000085);
  {$EXTERNALSYM SETUP_FAILURE}

//
// MessageId: AUDIT_FAILURE
//
// MessageText:
//
//  Audit attempt has failed.
//

  AUDIT_FAILURE = ULONG($00000086);
  {$EXTERNALSYM AUDIT_FAILURE}

//
// MessageId: WINDOWS_NT_CSD_STRING
//
// MessageText:
//
//  Service Pack
//

  WINDOWS_NT_CSD_STRING = ULONG($40000087);
  {$EXTERNALSYM WINDOWS_NT_CSD_STRING}

//
// MessageId: WINDOWS_NT_INFO_STRING
//
// MessageText:
//
//  %u System Processor [%u MB Memory] %Z
//

  WINDOWS_NT_INFO_STRING = ULONG($40000088);
  {$EXTERNALSYM WINDOWS_NT_INFO_STRING}

//
// MessageId: WINDOWS_NT_MP_STRING
//
// MessageText:
//
//  MultiProcessor Kernel
//

  WINDOWS_NT_MP_STRING = ULONG($40000089);
  {$EXTERNALSYM WINDOWS_NT_MP_STRING}

//
// MessageId: THREAD_TERMINATE_HELD_MUTEX
//
// MessageText:
//
//  A kernel thread terminated while holding a mutex
//

  THREAD_TERMINATE_HELD_MUTEX = ULONG($4000008A);
  {$EXTERNALSYM THREAD_TERMINATE_HELD_MUTEX}

//
// MessageId: MBR_CHECKSUM_MISMATCH
//
// MessageText:
//
//  This system may be infected with a virus.
//

  MBR_CHECKSUM_MISMATCH = ULONG($0000008B);
  {$EXTERNALSYM MBR_CHECKSUM_MISMATCH}

//
// MessageId: BUGCODE_PSS_CRASH_INIT
//
// MessageText:
//
//  Beginning dump of physical memory
//

  BUGCODE_PSS_CRASH_INIT = ULONG($0000008C);
  {$EXTERNALSYM BUGCODE_PSS_CRASH_INIT}

//
// MessageId: BUGCODE_PSS_CRASH_PROGRESS
//
// MessageText:
//
//  Dumping physical memory to disk
//

  BUGCODE_PSS_CRASH_PROGRESS = ULONG($0000008D);
  {$EXTERNALSYM BUGCODE_PSS_CRASH_PROGRESS}

//
// MessageId: BUGCODE_PSS_CRASH_DONE
//
// MessageText:
//
//  Physical memory dump complete. Contact your system administrator or
//  technical support group.
//

  BUGCODE_PSS_CRASH_DONE = ULONG($0000008E);
  {$EXTERNALSYM BUGCODE_PSS_CRASH_DONE}

//
// MessageId: PP0_INITIALIZATION_FAILED
//
// MessageText:
//
//  PP0_INITIALIZATION_FAILED
//

  PP0_INITIALIZATION_FAILED = ULONG($0000008F);
  {$EXTERNALSYM PP0_INITIALIZATION_FAILED}

//
// MessageId: PP1_INITIALIZATION_FAILED
//
// MessageText:
//
//  PP1_INITIALIZATION_FAILED
//

  PP1_INITIALIZATION_FAILED = ULONG($00000090);
  {$EXTERNALSYM PP1_INITIALIZATION_FAILED}

//
// MessageId: WIN32K_INIT_OR_RIT_FAILURE
//
// MessageText:
//
//  WIN32K_INIT_OR_RIT_FAILURE
//

  WIN32K_INIT_OR_RIT_FAILURE = ULONG($00000091);
  {$EXTERNALSYM WIN32K_INIT_OR_RIT_FAILURE}

//
// MessageId: UP_DRIVER_ON_MP_SYSTEM
//
// MessageText:
//
//  UP_DRIVER_ON_MP_SYSTEM
//

  UP_DRIVER_ON_MP_SYSTEM = ULONG($00000092);
  {$EXTERNALSYM UP_DRIVER_ON_MP_SYSTEM}

//
// MessageId: INVALID_KERNEL_HANDLE
//
// MessageText:
//
//  INVALID_KERNEL_HANDLE
//

  INVALID_KERNEL_HANDLE = ULONG($00000093);
  {$EXTERNALSYM INVALID_KERNEL_HANDLE}

//
// MessageId: KERNEL_STACK_LOCKED_AT_EXIT
//
// MessageText:
//
//  KERNEL_STACK_LOCKED_AT_EXIT
//

  KERNEL_STACK_LOCKED_AT_EXIT = ULONG($00000094);
  {$EXTERNALSYM KERNEL_STACK_LOCKED_AT_EXIT}

//
// MessageId: PNP_INTERNAL_ERROR
//
// MessageText:
//
//  PNP_INTERNAL_ERROR
//

  PNP_INTERNAL_ERROR = ULONG($00000095);
  {$EXTERNALSYM PNP_INTERNAL_ERROR}

//
// MessageId: INVALID_WORK_QUEUE_ITEM
//
// MessageText:
//
//  INVALID_WORK_QUEUE_ITEM
//

  INVALID_WORK_QUEUE_ITEM = ULONG($00000096);
  {$EXTERNALSYM INVALID_WORK_QUEUE_ITEM}

//
// MessageId: BOUND_IMAGE_UNSUPPORTED
//
// MessageText:
//
//  BOUND_IMAGE_UNSUPPORTED
//

  BOUND_IMAGE_UNSUPPORTED = ULONG($00000097);
  {$EXTERNALSYM BOUND_IMAGE_UNSUPPORTED}

//
// MessageId: END_OF_NT_EVALUATION_PERIOD
//
// MessageText:
//
//  END_OF_NT_EVALUATION_PERIOD
//

  END_OF_NT_EVALUATION_PERIOD = ULONG($00000098);
  {$EXTERNALSYM END_OF_NT_EVALUATION_PERIOD}

//
// MessageId: INVALID_REGION_OR_SEGMENT
//
// MessageText:
//
//  INVALID_REGION_OR_SEGMENT
//

  INVALID_REGION_OR_SEGMENT = ULONG($00000099);
  {$EXTERNALSYM INVALID_REGION_OR_SEGMENT}

//
// MessageId: SYSTEM_LICENSE_VIOLATION
//
// MessageText:
//
//  SYSTEM_LICENSE_VIOLATION
//

  SYSTEM_LICENSE_VIOLATION = ULONG($0000009A);
  {$EXTERNALSYM SYSTEM_LICENSE_VIOLATION}

//
// MessageId: UDFS_FILE_SYSTEM
//
// MessageText:
//
//  UDFS_FILE_SYSTEM
//

  UDFS_FILE_SYSTEM = ULONG($0000009B);
  {$EXTERNALSYM UDFS_FILE_SYSTEM}

//
// MessageId: MACHINE_CHECK_EXCEPTION
//
// MessageText:
//
//  MACHINE_CHECK_EXCEPTION
//

  MACHINE_CHECK_EXCEPTION = ULONG($0000009C);
  {$EXTERNALSYM MACHINE_CHECK_EXCEPTION}

//
// MessageId: WINDOWS_NT_INFO_STRING_PLURAL
//
// MessageText:
//
//  %u System Processors [%u MB Memory] %Z
//

  WINDOWS_NT_INFO_STRING_PLURAL = ULONG($4000009D);
  {$EXTERNALSYM WINDOWS_NT_INFO_STRING_PLURAL}

//
// MessageId: WINDOWS_NT_RC_STRING
//
// MessageText:
//
//  RC
//

  WINDOWS_NT_RC_STRING = ULONG($4000009E);
  {$EXTERNALSYM WINDOWS_NT_RC_STRING}

//
// MessageId: DRIVER_POWER_STATE_FAILURE
//
// MessageText:
//
//  DRIVER_POWER_STATE_FAILURE
//

  DRIVER_POWER_STATE_FAILURE = ULONG($0000009F);
  {$EXTERNALSYM DRIVER_POWER_STATE_FAILURE}

//
// MessageId: INTERNAL_POWER_ERROR
//
// MessageText:
//
//  INTERNAL_POWER_ERROR
//

  INTERNAL_POWER_ERROR = ULONG($000000A0);
  {$EXTERNALSYM INTERNAL_POWER_ERROR}

//
// MessageId: PCI_BUS_DRIVER_INTERNAL
//
// MessageText:
//
//  Inconsistency detected in the PCI Bus driver's internal structures.
//

  PCI_BUS_DRIVER_INTERNAL = ULONG($000000A1);
  {$EXTERNALSYM PCI_BUS_DRIVER_INTERNAL}

//
// MessageId: MEMORY_IMAGE_CORRUPT
//
// MessageText:
//
//  A CRC check on the memory range has failed
//

  MEMORY_IMAGE_CORRUPT = ULONG($000000A2);
  {$EXTERNALSYM MEMORY_IMAGE_CORRUPT}

//
// MessageId: ACPI_DRIVER_INTERNAL
//
// MessageText:
//
//  ACPI_DRIVER_INTERNAL
//

  ACPI_DRIVER_INTERNAL = ULONG($000000A3);
  {$EXTERNALSYM ACPI_DRIVER_INTERNAL}

//
// MessageId: CNSS_FILE_SYSTEM_FILTER
//
// MessageText:
//
//  Internal inconsistency while representing
//  Ntfs Structured Storage as a DOCFILE.
//

  CNSS_FILE_SYSTEM_FILTER = ULONG($000000A4);
  {$EXTERNALSYM CNSS_FILE_SYSTEM_FILTER}

//
// MessageId: ACPI_BIOS_ERROR
//
// MessageText:
//
//  The ACPI BIOS in this system is not fully compliant with the ACPI 
//  specification. Please read the README.TXT for possible workarounds.  You
//  can also contact your system's manufacturer for an updated BIOS, or visit
//  http://www.hardware-update.com to see if a new BIOS is available.  
//

  ACPI_BIOS_ERROR = ULONG($000000A5);
  {$EXTERNALSYM ACPI_BIOS_ERROR}

//
// MessageId: FP_EMULATION_ERROR
//
// MessageText:
//
//  FP_EMULATION_ERROR
//

  FP_EMULATION_ERROR = ULONG($000000A6);
  {$EXTERNALSYM FP_EMULATION_ERROR}

//
// MessageId: BAD_EXHANDLE
//
// MessageText:
//
//  BAD_EXHANDLE
//

  BAD_EXHANDLE = ULONG($000000A7);
  {$EXTERNALSYM BAD_EXHANDLE}

//
// MessageId: BOOTING_IN_SAFEMODE_MINIMAL
//
// MessageText:
//
//  The system is booting in safemode - Minimal Services
//

  BOOTING_IN_SAFEMODE_MINIMAL = ULONG($000000A8);
  {$EXTERNALSYM BOOTING_IN_SAFEMODE_MINIMAL}

//
// MessageId: BOOTING_IN_SAFEMODE_NETWORK
//
// MessageText:
//
//  The system is booting in safemode - Minimal Services with Network
//

  BOOTING_IN_SAFEMODE_NETWORK = ULONG($000000A9);
  {$EXTERNALSYM BOOTING_IN_SAFEMODE_NETWORK}

//
// MessageId: BOOTING_IN_SAFEMODE_DSREPAIR
//
// MessageText:
//
//  The system is booting in safemode - Directory Services Repair
//

  BOOTING_IN_SAFEMODE_DSREPAIR = ULONG($000000AA);
  {$EXTERNALSYM BOOTING_IN_SAFEMODE_DSREPAIR}

//
// MessageId: SESSION_HAS_VALID_POOL_ON_EXIT
//
// MessageText:
//
//  SESSION_HAS_VALID_POOL_ON_EXIT
//

  SESSION_HAS_VALID_POOL_ON_EXIT = ULONG($000000AB);
  {$EXTERNALSYM SESSION_HAS_VALID_POOL_ON_EXIT}

//
// MessageId: HAL_MEMORY_ALLOCATION
//
// MessageText:
//
//  Allocate from NonPaged Pool failed for a HAL critical allocation.
//

  HAL_MEMORY_ALLOCATION = ULONG($000000AC);
  {$EXTERNALSYM HAL_MEMORY_ALLOCATION}

//
// MessageId: BUGCODE_PSS_MESSAGE_A
//
// MessageText:
//
//  If this is the first time you've seen this Stop error screen,
//  restart your computer. If this screen appears again, follow
//  these steps:
//  
//  Check to make sure any new hardware or software is properly installed.
//  If this is a new installation, ask your hardware or software manufacturer
//  for any Windows 2000 updates you might need.
//  
//  If problems continue, disable or remove any newly installed hardware
//  or software. Disable BIOS memory options such as caching or shadowing.
//  Check your hard drive to make sure it is properly configured and
//  terminated. If you need to use Safe Mode to remove or disable components,
//  restart your computer, press F8 to select Advanced Startup Options,
//  and then select Safe Mode.
//  
//  Refer to your Getting Started manual for more information on
//  troubleshooting Stop errors.
//

  BUGCODE_PSS_MESSAGE_A = ULONG($000000AD);
  {$EXTERNALSYM BUGCODE_PSS_MESSAGE_A}

//
// MessageId: BUGCODE_PSS_MESSAGE_1E
//
// MessageText:
//
//  If this is the first time you've seen this Stop error screen,
//  restart your computer. If this screen appears again, follow
//  these steps:
//  
//  Check to be sure you have adequate disk space. If a driver is
//  identified in the Stop message, disable the driver or check
//  with the manufacturer for driver updates. Try changing video
//  adapters.
//  
//  Check with your hardware vendor for any BIOS updates. Disable
//  BIOS memory options such as caching or shadowing. If you need
//  to use Safe Mode to remove or disable components, restart your
//  computer, press F8 to select Advanced Startup Options, and then
//  select Safe Mode.
//  
//  Refer to your Getting Started manual for more information on
//  troubleshooting Stop errors.
//

  BUGCODE_PSS_MESSAGE_1E = ULONG($000000AE);
  {$EXTERNALSYM BUGCODE_PSS_MESSAGE_1E}

//
// MessageId: BUGCODE_PSS_MESSAGE_23
//
// MessageText:
//
//  If this is the first time you've seen this Stop error screen,
//  restart your computer. If this screen appears again, follow
//  these steps:
//  
//  Disable or uninstall any anti-virus, disk defragmentation
//  or backup utilities. Check your hard drive configuration,
//  and check for any updated drivers. Run CHKDSK /F to check
//  for hard drive corruption, and then restart your computer.
//  
//  Refer to your Getting Started manual for more information on
//  troubleshooting Stop errors.
//

  BUGCODE_PSS_MESSAGE_23 = ULONG($000000AF);
  {$EXTERNALSYM BUGCODE_PSS_MESSAGE_23}

//
// MessageId: BUGCODE_PSS_MESSAGE_2E
//
// MessageText:
//
//  If this is the first time you've seen this Stop error screen,
//  restart your computer. If this screen appears again, follow
//  these steps:
//  
//  Run system diagnostics supplied by your hardware manufacturer.
//  In particular, run a memory check, and check for faulty or
//  mismatched memory. Try changing video adapters.
//  
//  Check with your hardware vendor for any BIOS updates. Disable
//  BIOS memory options such as caching or shadowing. If you need
//  to use Safe Mode to remove or disable components, restart your
//  computer, press F8 to select Advanced Startup Options, and then
//  select Safe Mode.
//  
//  Refer to your Getting Started manual for more information on
//  troubleshooting Stop errors.
//

  BUGCODE_PSS_MESSAGE_2E = ULONG($000000B0);
  {$EXTERNALSYM BUGCODE_PSS_MESSAGE_2E}

//
// MessageId: BUGCODE_PSS_MESSAGE_3F
//
// MessageText:
//
//  If this is the first time you've seen this Stop error screen,
//  restart your computer. If this screen appears again, follow
//  these steps:
//  
//  Remove any recently installed software including backup
//  utilities or disk-intensive applications.
//  
//  If you need to use Safe Mode to remove or disable components,
//  restart your computer, press F8 to select Advanced Startup
//  Options, and then select Safe Mode.
//  
//  Refer to your Getting Started manual for more information on
//  troubleshooting Stop errors.
//

  BUGCODE_PSS_MESSAGE_3F = ULONG($000000B1);
  {$EXTERNALSYM BUGCODE_PSS_MESSAGE_3F}

//
// MessageId: BUGCODE_PSS_MESSAGE_7B
//
// MessageText:
//
//  If this is the first time you've seen this Stop error screen,
//  restart your computer. If this screen appears again, follow
//  these steps:
//  
//  Check for viruses on your computer. Remove any newly installed
//  hard drives or hard drive controllers. Check your hard drive
//  to make sure it is properly configured and terminated.
//  Run CHKDSK /F to check for hard drive corruption, and then
//  restart your computer.
//  
//  Refer to your Getting Started manual for more information on
//  troubleshooting Stop errors.
//

  BUGCODE_PSS_MESSAGE_7B = ULONG($000000B2);
  {$EXTERNALSYM BUGCODE_PSS_MESSAGE_7B}

//
// MessageId: BUGCODE_PSS_MESSAGE_7F
//
// MessageText:
//
//  If this is the first time you've seen this Stop error screen,
//  restart your computer. If this screen appears again, follow
//  these steps:
//  
//  Run a system diagnostic utility supplied by your hardware manufacturer.
//  In particular, run a memory check, and check for faulty or mismatched
//  memory. Try changing video adapters.
//  
//  Disable or remove any newly installed hardware and drivers. Disable or
//  remove any newly installed software. If you need to use Safe Mode to
//  remove or disable components, restart your computer, press F8 to select
//  Advanced Startup Options, and then select Safe Mode.
//  
//  Refer to your Getting Started manual for more information on
//  troubleshooting Stop errors.
//

  BUGCODE_PSS_MESSAGE_7F = ULONG($000000B3);
  {$EXTERNALSYM BUGCODE_PSS_MESSAGE_7F}

//
// MessageId: VIDEO_DRIVER_INIT_FAILURE
//
// MessageText:
//
//  The video driver failed to initialize
//

  VIDEO_DRIVER_INIT_FAILURE = ULONG($000000B4);
  {$EXTERNALSYM VIDEO_DRIVER_INIT_FAILURE}

//
// MessageId: BOOTLOG_LOADED
//
// MessageText:
//
//  Loaded driver
//

  BOOTLOG_LOADED = ULONG($000000B5);
  {$EXTERNALSYM BOOTLOG_LOADED}

//
// MessageId: BOOTLOG_NOT_LOADED
//
// MessageText:
//
//  Did not load driver
//

  BOOTLOG_NOT_LOADED = ULONG($000000B6);
  {$EXTERNALSYM BOOTLOG_NOT_LOADED}

//
// MessageId: BOOTLOG_ENABLED
//
// MessageText:
//
//  Boot Logging Enabled
//

  BOOTLOG_ENABLED = ULONG($000000B7);
  {$EXTERNALSYM BOOTLOG_ENABLED}

//
// MessageId: ATTEMPTED_SWITCH_FROM_DPC
//
// MessageText:
//
//  A wait operation, attach process, or yield was attempted from a DPC routine.
//

  ATTEMPTED_SWITCH_FROM_DPC = ULONG($000000B8);
  {$EXTERNALSYM ATTEMPTED_SWITCH_FROM_DPC}

//
// MessageId: CHIPSET_DETECTED_ERROR
//
// MessageText:
//
//  A parity error in the system memory or I/O system was detected.
//

  CHIPSET_DETECTED_ERROR = ULONG($000000B9);
  {$EXTERNALSYM CHIPSET_DETECTED_ERROR}

//
// MessageId: SESSION_HAS_VALID_VIEWS_ON_EXIT
//
// MessageText:
//
//  SESSION_HAS_VALID_VIEWS_ON_EXIT
//

  SESSION_HAS_VALID_VIEWS_ON_EXIT = ULONG($000000BA);
  {$EXTERNALSYM SESSION_HAS_VALID_VIEWS_ON_EXIT}

//
// MessageId: NETWORK_BOOT_INITIALIZATION_FAILED
//
// MessageText:
//
//  An initialization failure occurred while attempting to boot from the network.
//

  NETWORK_BOOT_INITIALIZATION_FAILED = ULONG($000000BB);
  {$EXTERNALSYM NETWORK_BOOT_INITIALIZATION_FAILED}

//
// MessageId: NETWORK_BOOT_DUPLICATE_ADDRESS
//
// MessageText:
//
//  A duplicate IP address was assigned to this machine while attempting to
//  boot from the network.
//

  NETWORK_BOOT_DUPLICATE_ADDRESS = ULONG($000000BC);
  {$EXTERNALSYM NETWORK_BOOT_DUPLICATE_ADDRESS}

//
// MessageId: INVALID_HIBERNATED_STATE
//
// MessageText:
//
//  The hibernated memory image does not match the current hardware configuration.
//

  INVALID_HIBERNATED_STATE = ULONG($000000BD);
  {$EXTERNALSYM INVALID_HIBERNATED_STATE}

//
// MessageId: ATTEMPTED_WRITE_TO_READONLY_MEMORY
//
// MessageText:
//
//  An attempt was made to write to read-only memory.
//

  ATTEMPTED_WRITE_TO_READONLY_MEMORY = ULONG($000000BE);
  {$EXTERNALSYM ATTEMPTED_WRITE_TO_READONLY_MEMORY}

//
// MessageId: MUTEX_ALREADY_OWNED
//
// MessageText:
//
//  MUTEX_ALREADY_OWNED
//

  MUTEX_ALREADY_OWNED = ULONG($000000BF);
  {$EXTERNALSYM MUTEX_ALREADY_OWNED}

//
// MessageId: PCI_CONFIG_SPACE_ACCESS_FAILURE
//
// MessageText:
//
//  An attempt to access PCI configuration space failed.
//

  PCI_CONFIG_SPACE_ACCESS_FAILURE = ULONG($000000C0);
  {$EXTERNALSYM PCI_CONFIG_SPACE_ACCESS_FAILURE}

//
// MessageId: SPECIAL_POOL_DETECTED_MEMORY_CORRUPTION
//
// MessageText:
//
//  SPECIAL_POOL_DETECTED_MEMORY_CORRUPTION
//

  SPECIAL_POOL_DETECTED_MEMORY_CORRUPTION = ULONG($000000C1);
  {$EXTERNALSYM SPECIAL_POOL_DETECTED_MEMORY_CORRUPTION}

//
// MessageId: BAD_POOL_CALLER
//
// MessageText:
//
//  BAD_POOL_CALLER
//

  BAD_POOL_CALLER = ULONG($000000C2);
  {$EXTERNALSYM BAD_POOL_CALLER}

//
// MessageId: BUGCODE_PSS_MESSAGE_SIGNATURE
//
// MessageText:
//
//  
//  A system file that is owned by Windows 2000 was replaced by an application
//  running on your system.  The operating system detected this and tried to
//  verify the validity of the file's signature.  The operating system found that
//  the file signature is not valid and put the original, correct file back
//  so that your operating system will continue to function properly.
//

  BUGCODE_PSS_MESSAGE_SIGNATURE = ULONG($000000C3);
  {$EXTERNALSYM BUGCODE_PSS_MESSAGE_SIGNATURE}

//
// MessageId: DRIVER_VERIFIER_DETECTED_VIOLATION
//
// MessageText:
//
//  
//  A device driver attempting to corrupt the system has been caught.
//  The faulty driver currently on the kernel stack must be replaced
//  with a working version.
//

  DRIVER_VERIFIER_DETECTED_VIOLATION = ULONG($000000C4);
  {$EXTERNALSYM DRIVER_VERIFIER_DETECTED_VIOLATION}

//
// MessageId: DRIVER_CORRUPTED_EXPOOL
//
// MessageText:
//
//  
//  A device driver has corrupted the executive memory pool.
//  
//  If this is the first time you've seen this Stop error screen,
//  restart your computer. If this screen appears again, follow
//  these steps:
//  
//  Check to make sure any new hardware or software is properly installed.
//  If this is a new installation, ask your hardware or software manufacturer
//  for any Windows 2000 updates you might need.
//  
//  Run the driver verifier against any new (or suspect) drivers.
//  If that doesn't reveal the corrupting driver, try enabling special pool.
//  Both of these features are intended to catch the corruption at an earlier
//  point where the offending driver can be identified.
//  
//  If you need to use Safe Mode to remove or disable components,
//  restart your computer, press F8 to select Advanced Startup Options,
//  and then select Safe Mode.
//  
//  Refer to your Getting Started manual for more information on
//  troubleshooting Stop errors.
//

  DRIVER_CORRUPTED_EXPOOL = ULONG($000000C5);
  {$EXTERNALSYM DRIVER_CORRUPTED_EXPOOL}

//
// MessageId: DRIVER_CAUGHT_MODIFYING_FREED_POOL
//
// MessageText:
//
//  
//  A device driver attempting to corrupt the system has been caught.
//  The faulty driver currently on the kernel stack must be replaced
//  with a working version.
//

  DRIVER_CAUGHT_MODIFYING_FREED_POOL = ULONG($000000C6);
  {$EXTERNALSYM DRIVER_CAUGHT_MODIFYING_FREED_POOL}

//
// MessageId: TIMER_OR_DPC_INVALID
//
// MessageText:
//
//  
//  A kernel timer or DPC was found in memory which must not contain such
//  items.  Usually this is memory being freed.  This is usually caused by
//  a device driver that has not cleaned up properly before freeing memory.
//

  TIMER_OR_DPC_INVALID = ULONG($000000C7);
  {$EXTERNALSYM TIMER_OR_DPC_INVALID}

//
// MessageId: IRQL_UNEXPECTED_VALUE
//
// MessageText:
//
//  
//  The processor's IRQL is not valid for the currently executing context.
//  This is a software error condition and is usually caused by a device
//  driver changing IRQL and not restoring it to its previous value when
//  it has finished its task.
//

  IRQL_UNEXPECTED_VALUE = ULONG($000000C8);
  {$EXTERNALSYM IRQL_UNEXPECTED_VALUE}

//
// MessageId: DRIVER_VERIFIER_IOMANAGER_VIOLATION
//
// MessageText:
//
//  
//  The IO manager has detected a violation by a driver that is being verified.
//  The faulty driver that is being verified must be debugged and
//  replaced with a working version.
//

  DRIVER_VERIFIER_IOMANAGER_VIOLATION = ULONG($000000C9);
  {$EXTERNALSYM DRIVER_VERIFIER_IOMANAGER_VIOLATION}

//
// MessageId: PNP_DETECTED_FATAL_ERROR
//
// MessageText:
//
//  
//  Plug and Play detected an error most likely caused by a faulty driver.
//

  PNP_DETECTED_FATAL_ERROR = ULONG($000000CA);
  {$EXTERNALSYM PNP_DETECTED_FATAL_ERROR}

//
// MessageId: DRIVER_LEFT_LOCKED_PAGES_IN_PROCESS
//
// MessageText:
//
//  DRIVER_LEFT_LOCKED_PAGES_IN_PROCESS
//

  DRIVER_LEFT_LOCKED_PAGES_IN_PROCESS = ULONG($000000CB);
  {$EXTERNALSYM DRIVER_LEFT_LOCKED_PAGES_IN_PROCESS}

//
// MessageId: PAGE_FAULT_IN_FREED_SPECIAL_POOL
//
// MessageText:
//
//  
//  The system is attempting to access memory after it has been freed.
//  This usually indicates a system-driver synchronization issue.
//

  PAGE_FAULT_IN_FREED_SPECIAL_POOL = ULONG($000000CC);
  {$EXTERNALSYM PAGE_FAULT_IN_FREED_SPECIAL_POOL}

//
// MessageId: PAGE_FAULT_BEYOND_END_OF_ALLOCATION
//
// MessageText:
//
//  
//  The system is attempting to access memory beyond the end of the allocation.
//  This usually indicates a system-driver synchronization issue.
//

  PAGE_FAULT_BEYOND_END_OF_ALLOCATION = ULONG($000000CD);
  {$EXTERNALSYM PAGE_FAULT_BEYOND_END_OF_ALLOCATION}

//
// MessageId: DRIVER_UNLOADED_WITHOUT_CANCELLING_PENDING_OPERATIONS
//
// MessageText:
//
//  DRIVER_UNLOADED_WITHOUT_CANCELLING_PENDING_OPERATIONS
//

  DRIVER_UNLOADED_WITHOUT_CANCELLING_PENDING_OPERATIONS = ULONG($000000CE);
  {$EXTERNALSYM DRIVER_UNLOADED_WITHOUT_CANCELLING_PENDING_OPERATIONS}

//
// MessageId: TERMINAL_SERVER_DRIVER_MADE_INCORRECT_MEMORY_REFERENCE
//
// MessageText:
//
//  TERMINAL_SERVER_DRIVER_MADE_INCORRECT_MEMORY_REFERENCE
//

  TERMINAL_SERVER_DRIVER_MADE_INCORRECT_MEMORY_REFERENCE = ULONG($000000CF);
  {$EXTERNALSYM TERMINAL_SERVER_DRIVER_MADE_INCORRECT_MEMORY_REFERENCE}

//
// MessageId: DRIVER_CORRUPTED_MMPOOL
//
// MessageText:
//
//  
//  A device driver has corrupted the system memory management pool.
//  
//  If this is the first time you've seen this Stop error screen,
//  restart your computer. If this screen appears again, follow
//  these steps:
//  
//  Check to make sure any new hardware or software is properly installed.
//  If this is a new installation, ask your hardware or software manufacturer
//  for any Windows 2000 updates you might need.
//  
//  Run the driver verifier against any new (or suspect) drivers.
//  If that doesn't reveal the corrupting driver, try enabling special pool.
//  Both of these features are intended to catch the corruption at an earlier
//  point where the offending driver can be identified.
//  
//  If you need to use Safe Mode to remove or disable components,
//  restart your computer, press F8 to select Advanced Startup Options,
//  and then select Safe Mode.
//  
//  Refer to your Getting Started manual for more information on
//  troubleshooting Stop errors.
//

  DRIVER_CORRUPTED_MMPOOL = ULONG($000000D0);
  {$EXTERNALSYM DRIVER_CORRUPTED_MMPOOL}

//
// MessageId: DRIVER_IRQL_NOT_LESS_OR_EQUAL
//
// MessageText:
//
//  DRIVER_IRQL_NOT_LESS_OR_EQUAL
//

  DRIVER_IRQL_NOT_LESS_OR_EQUAL = ULONG($000000D1);
  {$EXTERNALSYM DRIVER_IRQL_NOT_LESS_OR_EQUAL}

//
// MessageId: BUGCODE_ID_DRIVER
//
// MessageText:
//
//  This driver may be at fault :
//

  BUGCODE_ID_DRIVER = ULONG($000000D2);
  {$EXTERNALSYM BUGCODE_ID_DRIVER}

//
// MessageId: DRIVER_PORTION_MUST_BE_NONPAGED
//
// MessageText:
//
//  The driver mistakenly marked a part of it's image pagable instead of nonpagable.
//

  DRIVER_PORTION_MUST_BE_NONPAGED = ULONG($000000D3);
  {$EXTERNALSYM DRIVER_PORTION_MUST_BE_NONPAGED}

//
// MessageId: SYSTEM_SCAN_AT_RAISED_IRQL_CAUGHT_IMPROPER_DRIVER_UNLOAD
//
// MessageText:
//
//  The driver unloaded without cancelling pending operations.
//

  SYSTEM_SCAN_AT_RAISED_IRQL_CAUGHT_IMPROPER_DRIVER_UNLOAD = ULONG($000000D4);
  {$EXTERNALSYM SYSTEM_SCAN_AT_RAISED_IRQL_CAUGHT_IMPROPER_DRIVER_UNLOAD}

//
// MessageId: DRIVER_PAGE_FAULT_IN_FREED_SPECIAL_POOL
//
// MessageText:
//
//  
//  The driver is attempting to access memory after it has been freed.
//

  DRIVER_PAGE_FAULT_IN_FREED_SPECIAL_POOL = ULONG($000000D5);
  {$EXTERNALSYM DRIVER_PAGE_FAULT_IN_FREED_SPECIAL_POOL}

//
// MessageId: DRIVER_PAGE_FAULT_BEYOND_END_OF_ALLOCATION
//
// MessageText:
//
//  
//  The driver is attempting to access memory beyond the end of the allocation.
//

  DRIVER_PAGE_FAULT_BEYOND_END_OF_ALLOCATION = ULONG($000000D6);
  {$EXTERNALSYM DRIVER_PAGE_FAULT_BEYOND_END_OF_ALLOCATION}

//
// MessageId: DRIVER_UNMAPPING_INVALID_VIEW
//
// MessageText:
//
//  
//  The driver is attempting to unmap an invalid memory address.
//

  DRIVER_UNMAPPING_INVALID_VIEW = ULONG($000000D7);
  {$EXTERNALSYM DRIVER_UNMAPPING_INVALID_VIEW}

//
// MessageId: DRIVER_USED_EXCESSIVE_PTES
//
// MessageText:
//
//  
//  The driver has used an excessive number of system PTEs.
//

  DRIVER_USED_EXCESSIVE_PTES = ULONG($000000D8);
  {$EXTERNALSYM DRIVER_USED_EXCESSIVE_PTES}

//
// MessageId: LOCKED_PAGES_TRACKER_CORRUPTION
//
// MessageText:
//
//  
//  The driver is corrupting the locked pages tracking structures.
//

  LOCKED_PAGES_TRACKER_CORRUPTION = ULONG($000000D9);
  {$EXTERNALSYM LOCKED_PAGES_TRACKER_CORRUPTION}

//
// MessageId: SYSTEM_PTE_MISUSE
//
// MessageText:
//
//  
//  The driver is mismanaging system PTEs.
//

  SYSTEM_PTE_MISUSE = ULONG($000000DA);
  {$EXTERNALSYM SYSTEM_PTE_MISUSE}

//
// MessageId: DRIVER_CORRUPTED_SYSPTES
//
// MessageText:
//
//  
//  A driver has corrupted the memory management system PTEs.
//

  DRIVER_CORRUPTED_SYSPTES = ULONG($000000DB);
  {$EXTERNALSYM DRIVER_CORRUPTED_SYSPTES}

//
// MessageId: DRIVER_INVALID_STACK_ACCESS
//
// MessageText:
//
//  
//  A driver accessed a stack address that lies below the current stack pointer
//  of the stack's thread.
//

  DRIVER_INVALID_STACK_ACCESS = ULONG($000000DC);
  {$EXTERNALSYM DRIVER_INVALID_STACK_ACCESS}

//
// MessageId: BUGCODE_PSS_MESSAGE_A5
//
// MessageText:
//
//  
//  The BIOS in this system is not fully ACPI compliant.  Please contact your
//  system vendor or visit http://www.hardware-update.com for an updated BIOS.  
//  If you are unable to obtain an updated BIOS or the latest BIOS supplied by 
//  your vendor is not ACPI compliant, you can turn off ACPI mode during text 
//  mode setup.  To do this, simply press the F7 key when you are prompted to 
//  install storage drivers.  The system will not notify you that the F7 key 
//  was pressed - it will silently disable ACPI and allow you to continue 
//  your installation.
//

  BUGCODE_PSS_MESSAGE_A5 = ULONG($000000DD);
  {$EXTERNALSYM BUGCODE_PSS_MESSAGE_A5}

//
// MessageId: POOL_CORRUPTION_IN_FILE_AREA
//
// MessageText:
//
//  
//  A driver corrupted pool memory used for holding pages destined for disk.
//

  POOL_CORRUPTION_IN_FILE_AREA = ULONG($000000DE);
  {$EXTERNALSYM POOL_CORRUPTION_IN_FILE_AREA}

//
// MessageId: HARDWARE_PROFILE_UNDOCKED_STRING
//
// MessageText:
//
//  Undocked Profile
//

  HARDWARE_PROFILE_UNDOCKED_STRING = ULONG($40010001);
  {$EXTERNALSYM HARDWARE_PROFILE_UNDOCKED_STRING}

//
// MessageId: HARDWARE_PROFILE_DOCKED_STRING
//
// MessageText:
//
//  Docked Profile
//

  HARDWARE_PROFILE_DOCKED_STRING = ULONG($40010002);
  {$EXTERNALSYM HARDWARE_PROFILE_DOCKED_STRING}

//
// MessageId: HARDWARE_PROFILE_UNKNOWN_STRING
//
// MessageText:
//
//  Profile
//

  HARDWARE_PROFILE_UNKNOWN_STRING = ULONG($40010003);
  {$EXTERNALSYM HARDWARE_PROFILE_UNKNOWN_STRING}

//
// MessageId: IMPERSONATING_WORKER_THREAD
//
// MessageText:
//
//  
//  A worker thread is impersonating another process. The work item forgot to
//  disable impersonation before it returned.
//

  IMPERSONATING_WORKER_THREAD = ULONG($000000DF);
  {$EXTERNALSYM IMPERSONATING_WORKER_THREAD}

//
// MessageId: ACPI_BIOS_FATAL_ERROR
//
// MessageText:
//
//  
//  Your computer (BIOS) has reported that a component in your system is faulty and
//  has prevented Windows from operating.  You can determine which component is
//  faulty by running the diagnostic disk or tool that came with your computer.
//  
//  If you do not have this tool, you must contact your system vendor and report
//  this error message to them.  They will be able to assist you in correcting this
//  hardware problem thereby allowing Windows to operate.
//

  ACPI_BIOS_FATAL_ERROR = ULONG($000000E0);
  {$EXTERNALSYM ACPI_BIOS_FATAL_ERROR}

//
// MessageId: WORKER_THREAD_RETURNED_AT_BAD_IRQL
//
// MessageText:
//
//  WORKER_THREAD_RETURNED_AT_BAD_IRQL
//

  WORKER_THREAD_RETURNED_AT_BAD_IRQL = ULONG($000000E1);
  {$EXTERNALSYM WORKER_THREAD_RETURNED_AT_BAD_IRQL}

//
// MessageId: MANUALLY_INITIATED_CRASH
//
// MessageText:
//
//  
//  The end-user manually generated the crashdump.
//

  MANUALLY_INITIATED_CRASH = ULONG($000000E2);
  {$EXTERNALSYM MANUALLY_INITIATED_CRASH}

//
// MessageId: RESOURCE_NOT_OWNED
//
// MessageText:
//
//  
//  A thread tried to release a resource it did not own.
//

  RESOURCE_NOT_OWNED = ULONG($000000E3);
  {$EXTERNALSYM RESOURCE_NOT_OWNED}

//
// MessageId: WORKER_INVALID
//
// MessageText:
//
//  
//  A executive worker item was found in memory which must not contain such
//  items.  Usually this is memory being freed.  This is usually caused by
//  a device driver that has not cleaned up properly before freeing memory.
//

  WORKER_INVALID = ULONG($000000E4);
  {$EXTERNALSYM WORKER_INVALID}

implementation

end.
