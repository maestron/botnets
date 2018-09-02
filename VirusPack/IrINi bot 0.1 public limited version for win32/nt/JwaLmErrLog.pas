{******************************************************************************}
{                                                       	               }
{ Lan Manager Error Log API interface Unit for Object Pascal                   }
{                                                       	               }
{ Portions created by Microsoft are Copyright (C) 1995-2001 Microsoft          }
{ Corporation. All Rights Reserved.                                            }
{ 								               }
{ The original file is: lmerrlog.h, released November 2001. The original Pascal}
{ code is: LmErrLog.pas, released Februari 2002. The initial developer of the  }
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

unit JwaLmErrLog;

{$WEAKPACKAGEUNIT}

{$HPPEMIT ''}
{$HPPEMIT '#include "lmerrlog.h"'}
{$HPPEMIT ''}

{$I WINDEFINES.INC}

interface

uses
  JwaLmCons, JwaWinType;

//
// Data Structures - Config
//

type
  _ERROR_LOG = record
     el_len: DWORD;
     el_reserved: DWORD;
     el_time: DWORD;
     el_error: DWORD;
     el_name: LPWSTR;             // pointer to service name
     el_text: LPWSTR;             // pointer to string array
     el_data: LPBYTE;             // pointer to BYTE array
     el_data_size: DWORD;         // byte count of el_data area
     el_nstrings: DWORD;          // number of strings in el_text.
  end;
  {$EXTERNALSYM _ERROR_LOG}
  ERROR_LOG = _ERROR_LOG;
  {$EXTERNALSYM ERROR_LOG}
  PERROR_LOG = ^ERROR_LOG;
  {$EXTERNALSYM PERROR_LOG}
  LPERROR_LOG = ^ERROR_LOG;
  {$EXTERNALSYM LPERROR_LOG}
  TErrorLog = ERROR_LOG;
  PErrorLog = PERROR_LOG;

{$DEFINE REVISED_ERROR_LOG_STRUCT}

  _HLOG = record
     time: DWORD;
     last_flags: DWORD;
     offset: DWORD;
     rec_offset: DWORD;
  end;
  {$EXTERNALSYM _HLOG}
  HLOG = _HLOG;
  {$EXTERNALSYM HLOG}
  PHLOG = ^HLOG;
  {$EXTERNALSYM PHLOG}
  LPHLOG = ^HLOG;
  {$EXTERNALSYM LPHLOG}

const
  LOGFLAGS_FORWARD   = 0;
  {$EXTERNALSYM LOGFLAGS_FORWARD}
  LOGFLAGS_BACKWARD  = $1;
  {$EXTERNALSYM LOGFLAGS_BACKWARD}
  LOGFLAGS_SEEK      = $2;
  {$EXTERNALSYM LOGFLAGS_SEEK}

//
// Function Prototypes - ErrorLog
//

function NetErrorLogClear(server, backupfile: LPCWSTR; reserved: LPBYTE): NET_API_STATUS; stdcall;
{$EXTERNALSYM NetErrorLogClear}

function NetErrorLogRead(server: LPCWSTR; reserved1: LPWSTR; errloghandle: LPHLOG; offset: DWORD; reserved2: LPDWORD;
  reserved3, offsetflag: DWORD; var bufptr: LPBYTE; prefmaxlen: DWORD; bytesread, totalbytes: LPDWORD): NET_API_STATUS; stdcall;
{$EXTERNALSYM NetErrorLogRead}

function NetErrorLogWrite(reserved1: LPBYTE; code: DWORD; component: LPCWSTR; buffer: LPBYTE; numbytes: DWORD;
  msgbuf: LPBYTE; strcount: DWORD; reserved2: LPBYTE): NET_API_STATUS; stdcall;
{$EXTERNALSYM NetErrorLogWrite}

//
// Special Values and Constants
//


//
//  Generic (could be used by more than one service)
//   error log messages from 0 to 25
//
// Do not change the comments following the manifest constants without
// understanding how mapmsg works.
//

const
  ERRLOG_BASE = 3100;        { NELOG errors start here }
  {$EXTERNALSYM ERRLOG_BASE}


  NELOG_Internal_Error = (ERRLOG_BASE + 0);
  {$EXTERNALSYM NELOG_Internal_Error}

    {
    * The operation failed because a network software error occurred.
    }

  NELOG_Resource_Shortage = (ERRLOG_BASE + 1);
  {$EXTERNALSYM NELOG_Resource_Shortage}

    {
    * The system ran out of a resource controlled by the %1 option.
    }

  NELOG_Unable_To_Lock_Segment = (ERRLOG_BASE + 2);
  {$EXTERNALSYM NELOG_Unable_To_Lock_Segment}

    {
    * The service failed to obtain a long-term lock on the
    *  segment for network control blocks (NCBs). The error code is the data.
    }

  NELOG_Unable_To_Unlock_Segment = (ERRLOG_BASE + 3);
  {$EXTERNALSYM NELOG_Unable_To_Unlock_Segment}

    {
    * The service failed to release the long-term lock on the
    *  segment for network control blocks (NCBs). The error code is the data.
    }

  NELOG_Uninstall_Service = (ERRLOG_BASE + 4);
  {$EXTERNALSYM NELOG_Uninstall_Service}

    {
    * There was an error stopping service %1.
    *  The error code from NetServiceControl is the data.
    }

  NELOG_Init_Exec_Fail = (ERRLOG_BASE + 5);
  {$EXTERNALSYM NELOG_Init_Exec_Fail}

    {
    * Initialization failed because of a system execution failure on
    *  path %1. The system error code is the data.
    }

  NELOG_Ncb_Error = (ERRLOG_BASE + 6);
  {$EXTERNALSYM NELOG_Ncb_Error}

    {
    * An unexpected network control block (NCB) was received. The NCB is the data.
    }

  NELOG_Net_Not_Started = (ERRLOG_BASE + 7);
  {$EXTERNALSYM NELOG_Net_Not_Started}

    {
    * The network is not started.
    }

  NELOG_Ioctl_Error = (ERRLOG_BASE + 8);
  {$EXTERNALSYM NELOG_Ioctl_Error}

    {
    * A DosDevIoctl or DosFsCtl to NETWKSTA.SYS failed.
    * The data shown is in this format:
    *     DWORD  approx CS:IP of call to ioctl or fsctl
    *     WORD   error code
    *     WORD   ioctl or fsctl number
    }

  NELOG_System_Semaphore = (ERRLOG_BASE + 9);
  {$EXTERNALSYM NELOG_System_Semaphore}

    {
    * Unable to create or open system semaphore %1.
    *  The error code is the data.
    }

  NELOG_Init_OpenCreate_Err = (ERRLOG_BASE + 10);
  {$EXTERNALSYM NELOG_Init_OpenCreate_Err}

    {
    * Initialization failed because of an open/create error on the
    *  file %1. The system error code is the data.
    }

  NELOG_NetBios = (ERRLOG_BASE + 11);
  {$EXTERNALSYM NELOG_NetBios}

    {
    * An unexpected NetBIOS error occurred.
    *  The error code is the data.
    }

  NELOG_SMB_Illegal = (ERRLOG_BASE + 12);
  {$EXTERNALSYM NELOG_SMB_Illegal}

    {
    * An illegal server message block (SMB) was received.
    *  The SMB is the data.
    }

  NELOG_Service_Fail = (ERRLOG_BASE + 13);
  {$EXTERNALSYM NELOG_Service_Fail}

    {
    * Initialization failed because the requested service %1
    *  could not be started.
   }

  NELOG_Entries_Lost = (ERRLOG_BASE + 14);
  {$EXTERNALSYM NELOG_Entries_Lost}

    {
    * Some entries in the error log were lost because of a buffer
    * overflow.
    }


//
//  Server specific error log messages from 20 to 40
//

  NELOG_Init_Seg_Overflow = (ERRLOG_BASE + 20);
  {$EXTERNALSYM NELOG_Init_Seg_Overflow}

    {
    * Initialization parameters controlling resource usage other
    *  than net buffers are sized so that too much memory is needed.
    }

  NELOG_Srv_No_Mem_Grow = (ERRLOG_BASE + 21);
  {$EXTERNALSYM NELOG_Srv_No_Mem_Grow}

    {
    * The server cannot increase the size of a memory segment.
    }

  NELOG_Access_File_Bad = (ERRLOG_BASE + 22);
  {$EXTERNALSYM NELOG_Access_File_Bad}

    {
    * Initialization failed because account file %1 is either incorrect
    * or not present.
    }

  NELOG_Srvnet_Not_Started = (ERRLOG_BASE + 23);
  {$EXTERNALSYM NELOG_Srvnet_Not_Started}

    {
    * Initialization failed because network %1 was not started.
    }

  NELOG_Init_Chardev_Err = (ERRLOG_BASE + 24);
  {$EXTERNALSYM NELOG_Init_Chardev_Err}

    {
    * The server failed to start. Either all three chdev
    *  parameters must be zero or all three must be nonzero.
    }

  NELOG_Remote_API = (ERRLOG_BASE + 25);
  {$EXTERNALSYM NELOG_Remote_API}

    { A remote API request was halted due to the following
    * invalid description string: %1.
    }

  NELOG_Ncb_TooManyErr = (ERRLOG_BASE + 26);
  {$EXTERNALSYM NELOG_Ncb_TooManyErr}

    { The network %1 ran out of network control blocks (NCBs).  You may need to increase NCBs
    * for this network.  The following information includes the
    * number of NCBs submitted by the server when this error occurred:
    }

  NELOG_Mailslot_err = (ERRLOG_BASE + 27);
  {$EXTERNALSYM NELOG_Mailslot_err}

    { The server cannot create the %1 mailslot needed to send
    * the ReleaseMemory alert message.  The error received is:
    }

  NELOG_ReleaseMem_Alert = (ERRLOG_BASE + 28);
  {$EXTERNALSYM NELOG_ReleaseMem_Alert}

    { The server failed to register for the ReleaseMemory alert,
    * with recipient %1. The error code from
    * NetAlertStart is the data.
    }

  NELOG_AT_cannot_write = (ERRLOG_BASE + 29);
  {$EXTERNALSYM NELOG_AT_cannot_write}

    { The server cannot update the AT schedule file. The file
    * is corrupted.
    }

  NELOG_Cant_Make_Msg_File = (ERRLOG_BASE + 30);
  {$EXTERNALSYM NELOG_Cant_Make_Msg_File}

    { The server encountered an error when calling
    * NetIMakeLMFileName. The error code is the data.
    }

  NELOG_Exec_Netservr_NoMem = (ERRLOG_BASE + 31);
  {$EXTERNALSYM NELOG_Exec_Netservr_NoMem}

    { Initialization failed because of a system execution failure on
    * path %1. There is not enough memory to start the process.
    * The system error code is the data.
    }

  NELOG_Server_Lock_Failure = (ERRLOG_BASE + 32);
  {$EXTERNALSYM NELOG_Server_Lock_Failure}

    { Longterm lock of the server buffers failed.
    * Check swap disk's free space and restart the system to start the server.
    }

//
//  Message service and POPUP specific error log messages from 40 to 55
//

  NELOG_Msg_Shutdown = (ERRLOG_BASE + 40);
  {$EXTERNALSYM NELOG_Msg_Shutdown}

    {
    * The service has stopped due to repeated consecutive
    *  occurrences of a network control block (NCB) error.  The last bad NCB follows
    *  in raw data.
    }

  NELOG_Msg_Sem_Shutdown = (ERRLOG_BASE + 41);
  {$EXTERNALSYM NELOG_Msg_Sem_Shutdown}

    {
    * The Message server has stopped due to a lock on the
    *  Message server shared data segment.
    }

  NELOG_Msg_Log_Err = (ERRLOG_BASE + 50);
  {$EXTERNALSYM NELOG_Msg_Log_Err}

    {
    * A file system error occurred while opening or writing to the
    *  system message log file %1. Message logging has been
    *  switched off due to the error. The error code is the data.
    }



  NELOG_VIO_POPUP_ERR = (ERRLOG_BASE + 51);
  {$EXTERNALSYM NELOG_VIO_POPUP_ERR}

    {
    * Unable to display message POPUP due to system VIO call error.
    *  The error code is the data.
    }

  NELOG_Msg_Unexpected_SMB_Type = (ERRLOG_BASE + 52);
  {$EXTERNALSYM NELOG_Msg_Unexpected_SMB_Type}

    {
    * An illegal server message block (SMB) was received.  The SMB is the data.
    }

//
//  Workstation specific error log messages from 60 to 75
//


  NELOG_Wksta_Infoseg = (ERRLOG_BASE + 60);
  {$EXTERNALSYM NELOG_Wksta_Infoseg}

    {
    * The workstation information segment is bigger than 64K.
    *  The size follows, in DWORD format:
    }

  NELOG_Wksta_Compname = (ERRLOG_BASE + 61);
  {$EXTERNALSYM NELOG_Wksta_Compname}

    {
    * The workstation was unable to get the name-number of the computer.
    }

  NELOG_Wksta_BiosThreadFailure = (ERRLOG_BASE + 62);
  {$EXTERNALSYM NELOG_Wksta_BiosThreadFailure}

    {
    * The workstation could not initialize the Async NetBIOS Thread.
    *  The error code is the data.
    }

  NELOG_Wksta_IniSeg = (ERRLOG_BASE + 63);
  {$EXTERNALSYM NELOG_Wksta_IniSeg}

    {
    * The workstation could not open the initial shared segment.
    *  The error code is the data.
    }

  NELOG_Wksta_HostTab_Full = (ERRLOG_BASE + 64);
  {$EXTERNALSYM NELOG_Wksta_HostTab_Full}

    {
    * The workstation host table is full.
    }

  NELOG_Wksta_Bad_Mailslot_SMB = (ERRLOG_BASE + 65);
  {$EXTERNALSYM NELOG_Wksta_Bad_Mailslot_SMB}

    {
    * A bad mailslot server message block (SMB) was received.  The SMB is the data.
    }

  NELOG_Wksta_UASInit = (ERRLOG_BASE + 66);
  {$EXTERNALSYM NELOG_Wksta_UASInit}

    {
    * The workstation encountered an error while trying to start the user accounts database.
    *  The error code is the data.
    }

  NELOG_Wksta_SSIRelogon = (ERRLOG_BASE + 67);
  {$EXTERNALSYM NELOG_Wksta_SSIRelogon}

    {
    * The workstation encountered an error while responding to an SSI revalidation request.
    *  The function code and the error codes are the data.
    }

//
//  Alerter service specific error log messages from 70 to 79
//


  NELOG_Build_Name = (ERRLOG_BASE + 70);
  {$EXTERNALSYM NELOG_Build_Name}

    {
    * The Alerter service had a problem creating the list of
    * alert recipients.  The error code is %1.
    }

  NELOG_Name_Expansion = (ERRLOG_BASE + 71);
  {$EXTERNALSYM NELOG_Name_Expansion}

    {
    * There was an error expanding %1 as a group name. Try
    *  splitting the group into two or more smaller groups.
    }

  NELOG_Message_Send = (ERRLOG_BASE + 72);
  {$EXTERNALSYM NELOG_Message_Send}

    {
    * There was an error sending %2 the alert message -
    *  (
    *  %3 )
    *  The error code is %1.
    }

  NELOG_Mail_Slt_Err = (ERRLOG_BASE + 73);
  {$EXTERNALSYM NELOG_Mail_Slt_Err}

    {
    * There was an error in creating or reading the alerter mailslot.
    *  The error code is %1.
    }

  NELOG_AT_cannot_read = (ERRLOG_BASE + 74);
  {$EXTERNALSYM NELOG_AT_cannot_read}

    {
    * The server could not read the AT schedule file.
    }

  NELOG_AT_sched_err = (ERRLOG_BASE + 75);
  {$EXTERNALSYM NELOG_AT_sched_err}

    {
    * The server found an invalid AT schedule record.
    }

  NELOG_AT_schedule_file_created = (ERRLOG_BASE + 76);
  {$EXTERNALSYM NELOG_AT_schedule_file_created}

    {
    * The server could not find an AT schedule file so it created one.
    }

  NELOG_Srvnet_NB_Open = (ERRLOG_BASE + 77);
  {$EXTERNALSYM NELOG_Srvnet_NB_Open}

    {
    * The server could not access the %1 network with NetBiosOpen.
    }

  NELOG_AT_Exec_Err = (ERRLOG_BASE + 78);
  {$EXTERNALSYM NELOG_AT_Exec_Err}

    {
    * The AT command processor could not run %1.
   }

//
//      Cache Lazy Write and HPFS386 specific error log messages from 80 to 89
//

  NELOG_Lazy_Write_Err = (ERRLOG_BASE + 80);
  {$EXTERNALSYM NELOG_Lazy_Write_Err}

        {
        * WARNING:  Because of a lazy-write error, drive %1 now
        *  contains some corrupted data.  The cache is stopped.
        }

  NELOG_HotFix = (ERRLOG_BASE + 81);
  {$EXTERNALSYM NELOG_HotFix}

    {
    * A defective sector on drive %1 has been replaced (hotfixed).
    * No data was lost.  You should run CHKDSK soon to restore full
    * performance and replenish the volume's spare sector pool.
    *
    * The hotfix occurred while processing a remote request.
    }

  NELOG_HardErr_From_Server = (ERRLOG_BASE + 82);
  {$EXTERNALSYM NELOG_HardErr_From_Server}

    {
    * A disk error occurred on the HPFS volume in drive %1.
    * The error occurred while processing a remote request.
    }

  NELOG_LocalSecFail1 = (ERRLOG_BASE + 83);
  {$EXTERNALSYM NELOG_LocalSecFail1}

    {
    * The user accounts database (NET.ACC) is corrupted.  The local security
    * system is replacing the corrupted NET.ACC with the backup
    * made at %1.
    * Any updates made to the database after this time are lost.
    *
    }

  NELOG_LocalSecFail2 = (ERRLOG_BASE + 84);
  {$EXTERNALSYM NELOG_LocalSecFail2}

    {
    * The user accounts database (NET.ACC) is missing.  The local
    * security system is restoring the backup database
    * made at %1.
    * Any updates made to the database made after this time are lost.
    *
    }

  NELOG_LocalSecFail3 = (ERRLOG_BASE + 85);
  {$EXTERNALSYM NELOG_LocalSecFail3}

    {
    * Local security could not be started because the user accounts database
    * (NET.ACC) was missing or corrupted, and no usable backup
    * database was present.
    *
    * THE SYSTEM IS NOT SECURE.
    }

  NELOG_LocalSecGeneralFail = (ERRLOG_BASE + 86);
  {$EXTERNALSYM NELOG_LocalSecGeneralFail}

    {
    * Local security could not be started because an error
    * occurred during initialization. The error code returned is %1.
    *
    * THE SYSTEM IS NOT SECURE.
    *
    }

//
//  NETWKSTA.SYS specific error log messages from 90 to 99
//

  NELOG_NetWkSta_Internal_Error = (ERRLOG_BASE + 90);
  {$EXTERNALSYM NELOG_NetWkSta_Internal_Error}

    {
    * A NetWksta internal error has occurred:
    *  %1
    }

  NELOG_NetWkSta_No_Resource = (ERRLOG_BASE + 91);
  {$EXTERNALSYM NELOG_NetWkSta_No_Resource}

    {
    * The redirector is out of a resource: %1.
    }

  NELOG_NetWkSta_SMB_Err = (ERRLOG_BASE + 92);
  {$EXTERNALSYM NELOG_NetWkSta_SMB_Err}

    {
    * A server message block (SMB) error occurred on the connection to %1.
    *  The SMB header is the data.
    }

  NELOG_NetWkSta_VC_Err = (ERRLOG_BASE + 93);
  {$EXTERNALSYM NELOG_NetWkSta_VC_Err}

    {
    * A virtual circuit error occurred on the session to %1.
    *  The network control block (NCB) command and return code is the data.
    }

  NELOG_NetWkSta_Stuck_VC_Err = (ERRLOG_BASE + 94);
  {$EXTERNALSYM NELOG_NetWkSta_Stuck_VC_Err}

    {
    * Hanging up a stuck session to %1.
    }

  NELOG_NetWkSta_NCB_Err = (ERRLOG_BASE + 95);
  {$EXTERNALSYM NELOG_NetWkSta_NCB_Err}

    {
    * A network control block (NCB) error occurred (%1).
    *  The NCB is the data.
    }

  NELOG_NetWkSta_Write_Behind_Err = (ERRLOG_BASE + 96);
  {$EXTERNALSYM NELOG_NetWkSta_Write_Behind_Err}

    {
    * A write operation to %1 failed.
    *  Data may have been lost.
    }

  NELOG_NetWkSta_Reset_Err = (ERRLOG_BASE + 97);
  {$EXTERNALSYM NELOG_NetWkSta_Reset_Err}

    {
    * Reset of driver %1 failed to complete the network control block (NCB).
    *  The NCB is the data.
    }

  NELOG_NetWkSta_Too_Many = (ERRLOG_BASE + 98);
  {$EXTERNALSYM NELOG_NetWkSta_Too_Many}

    {
    * The amount of resource %1 requested was more
    *  than the maximum. The maximum amount was allocated.
    }

//
//  Spooler specific error log messages from 100 to 103
//

  NELOG_Srv_Thread_Failure = (ERRLOG_BASE + 104);
  {$EXTERNALSYM NELOG_Srv_Thread_Failure}

    {
    * The server could not create a thread.
    *  The THREADS parameter in the CONFIG.SYS file should be increased.
    }

  NELOG_Srv_Close_Failure = (ERRLOG_BASE + 105);
  {$EXTERNALSYM NELOG_Srv_Close_Failure}

    {
    * The server could not close %1.
    *  The file is probably corrupted.
    }

  NELOG_ReplUserCurDir = (ERRLOG_BASE + 106);
  {$EXTERNALSYM NELOG_ReplUserCurDir}

    {
    *The replicator cannot update directory %1. It has tree integrity
    * and is the current directory for some process.
    }

  NELOG_ReplCannotMasterDir = (ERRLOG_BASE + 107);
  {$EXTERNALSYM NELOG_ReplCannotMasterDir}

    {
    *The server cannot export directory %1 to client %2.
    * It is exported from another server.
    }

  NELOG_ReplUpdateError = (ERRLOG_BASE + 108);
  {$EXTERNALSYM NELOG_ReplUpdateError}

    {
    *The replication server could not update directory %2 from the source
    * on %3 due to error %1.
    }

  NELOG_ReplLostMaster = (ERRLOG_BASE + 109);
  {$EXTERNALSYM NELOG_ReplLostMaster}

    {
    *Master %1 did not send an update notice for directory %2 at the expected
    * time.
    }

  NELOG_NetlogonAuthDCFail = (ERRLOG_BASE + 110);
  {$EXTERNALSYM NELOG_NetlogonAuthDCFail}

    {
    *This computer could not authenticate with %2, a Windows domain controller
    * for domain %1, and therefore this computer might deny logon requests.
    * This inability to authenticate might be caused by another computer on the
    * same network using the same name or the password for this computer account
    * is not recognized. If this message appears again, contact your system
    * administrator.
    }

  NELOG_ReplLogonFailed = (ERRLOG_BASE + 111);
  {$EXTERNALSYM NELOG_ReplLogonFailed}

    {
    *The replicator attempted to log on at %2 as %1 and failed.
    }

  NELOG_ReplNetErr = (ERRLOG_BASE + 112);
  {$EXTERNALSYM NELOG_ReplNetErr}

    {
    *  Network error %1 occurred.
    }

  NELOG_ReplMaxFiles = (ERRLOG_BASE + 113);
  {$EXTERNALSYM NELOG_ReplMaxFiles}

    {
    *  Replicator limit for files in a directory has been exceeded.
    }


  NELOG_ReplMaxTreeDepth = (ERRLOG_BASE + 114);
  {$EXTERNALSYM NELOG_ReplMaxTreeDepth}

    {
    *  Replicator limit for tree depth has been exceeded.
    }

  NELOG_ReplBadMsg = (ERRLOG_BASE + 115);
  {$EXTERNALSYM NELOG_ReplBadMsg}

    {
    *  Unrecognized message received in mailslot.
    }

  NELOG_ReplSysErr = (ERRLOG_BASE + 116);
  {$EXTERNALSYM NELOG_ReplSysErr}

    {
    *  System error %1 occurred.
    }

  NELOG_ReplUserLoged = (ERRLOG_BASE + 117);
  {$EXTERNALSYM NELOG_ReplUserLoged}

    {
    *  Cannot log on. User is currently logged on and argument TRYUSER
    *  is set to NO.
    }

  NELOG_ReplBadImport = (ERRLOG_BASE + 118);
  {$EXTERNALSYM NELOG_ReplBadImport}

    {
    *  IMPORT path %1 cannot be found.
    }

  NELOG_ReplBadExport = (ERRLOG_BASE + 119);
  {$EXTERNALSYM NELOG_ReplBadExport}

    {
    *  EXPORT path %1 cannot be found.
    }

  NELOG_ReplSignalFileErr = (ERRLOG_BASE + 120);
  {$EXTERNALSYM NELOG_ReplSignalFileErr}

    {
    *  Replicator failed to update signal file in directory %2 due to
    *  %1 system error.
    }

  NELOG_DiskFT = (ERRLOG_BASE+121);
  {$EXTERNALSYM NELOG_DiskFT}

    {
    * Disk Fault Tolerance Error
    *
    * %1
    }

  NELOG_ReplAccessDenied = (ERRLOG_BASE + 122);
  {$EXTERNALSYM NELOG_ReplAccessDenied}

    {
    *  Replicator could not access %2
    *  on %3 due to system error %1.
    }

  NELOG_NetlogonFailedPrimary = (ERRLOG_BASE + 123);
  {$EXTERNALSYM NELOG_NetlogonFailedPrimary}

    {
    *The primary domain controller for domain %1 has apparently failed.
    }

  NELOG_NetlogonPasswdSetFailed = (ERRLOG_BASE + 124);
  {$EXTERNALSYM NELOG_NetlogonPasswdSetFailed}

    {
    * Changing machine account password for account %1 failed with
    * the following error: %n%2
    }

  NELOG_NetlogonTrackingError = (ERRLOG_BASE + 125);
  {$EXTERNALSYM NELOG_NetlogonTrackingError}

    {
    *An error occurred while updating the logon or logoff information for %1.
    }

  NELOG_NetlogonSyncError = (ERRLOG_BASE + 126);
  {$EXTERNALSYM NELOG_NetlogonSyncError}

    {
    *An error occurred while synchronizing with primary domain controller %1
    }

  NELOG_NetlogonRequireSignOrSealError = (ERRLOG_BASE + 127);
  {$EXTERNALSYM NELOG_NetlogonRequireSignOrSealError}

    {
    * The session setup to the Windows NT or Windows 2000 Domain Controller %1 for the domain %2
    * failed because %1 does not support signing or sealing the Netlogon
    * session.
    *
    * Either upgrade the Domain controller or set the RequireSignOrSeal
    * registry entry on this machine to 0.
    }

//
//  UPS service specific error log messages from 130 to 135
//

  NELOG_UPS_PowerOut = (ERRLOG_BASE + 130);
  {$EXTERNALSYM NELOG_UPS_PowerOut}

    {
    * A power failure was detected at the server.
    }

  NELOG_UPS_Shutdown = (ERRLOG_BASE + 131);
  {$EXTERNALSYM NELOG_UPS_Shutdown}

    {
    * The UPS service performed server shut down.
    }

  NELOG_UPS_CmdFileError = (ERRLOG_BASE + 132);
  {$EXTERNALSYM NELOG_UPS_CmdFileError}

    {
    * The UPS service did not complete execution of the
    * user specified shut down command file.
    }

  NELOG_UPS_CannotOpenDriver = (ERRLOG_BASE+133);
  {$EXTERNALSYM NELOG_UPS_CannotOpenDriver}

    {
    * The UPS driver could not be opened.  The error code is
    * the data.
    }

  NELOG_UPS_PowerBack = (ERRLOG_BASE + 134);
  {$EXTERNALSYM NELOG_UPS_PowerBack}

    {
    * Power has been restored.
    }

  NELOG_UPS_CmdFileConfig = (ERRLOG_BASE + 135);
  {$EXTERNALSYM NELOG_UPS_CmdFileConfig}

    {
    * There is a problem with a configuration of user specified
    * shut down command file.
    }

  NELOG_UPS_CmdFileExec = (ERRLOG_BASE + 136);
  {$EXTERNALSYM NELOG_UPS_CmdFileExec}

    {
    * The UPS service failed to execute a user specified shutdown
    * command file %1.  The error code is the data.
    }

//
//  Remoteboot server specific error log messages are from 150 to 157
//

  NELOG_Missing_Parameter = (ERRLOG_BASE + 150);
  {$EXTERNALSYM NELOG_Missing_Parameter}

    {
    * Initialization failed because of an invalid or missing
    *  parameter in the configuration file %1.
    }

  NELOG_Invalid_Config_Line = (ERRLOG_BASE + 151);
  {$EXTERNALSYM NELOG_Invalid_Config_Line}

    {
    * Initialization failed because of an invalid line in the
    *  configuration file %1. The invalid line is the data.
    }

  NELOG_Invalid_Config_File = (ERRLOG_BASE + 152);
  {$EXTERNALSYM NELOG_Invalid_Config_File}

    {
    * Initialization failed because of an error in the configuration
    *  file %1.
    }

  NELOG_File_Changed = (ERRLOG_BASE + 153);
  {$EXTERNALSYM NELOG_File_Changed}

    {
    * The file %1 has been changed after initialization.
    *  The boot-block loading was temporarily terminated.
    }

  NELOG_Files_Dont_Fit = (ERRLOG_BASE + 154);
  {$EXTERNALSYM NELOG_Files_Dont_Fit}

    {
    * The files do not fit to the boot-block configuration
    * file %1. Change the BASE and ORG definitions or the order
    * of the files.
    }

  NELOG_Wrong_DLL_Version = (ERRLOG_BASE + 155);
  {$EXTERNALSYM NELOG_Wrong_DLL_Version}

    {
    * Initialization failed because the dynamic-link
    *  library %1 returned an incorrect version number.
    }

  NELOG_Error_in_DLL = (ERRLOG_BASE + 156);
  {$EXTERNALSYM NELOG_Error_in_DLL}

    {
    * There was an unrecoverable error in the dynamic-
    *  link library of the service.
    }

  NELOG_System_Error = (ERRLOG_BASE + 157);
  {$EXTERNALSYM NELOG_System_Error}

    {
    * The system returned an unexpected error code.
    *  The error code is the data.
    }

  NELOG_FT_ErrLog_Too_Large = (ERRLOG_BASE + 158);
  {$EXTERNALSYM NELOG_FT_ErrLog_Too_Large}

    {
    * The fault-tolerance error log file, LANROOT\LOGS\FT.LOG,
    *  is more than 64K.
    }

  NELOG_FT_Update_In_Progress = (ERRLOG_BASE + 159);
  {$EXTERNALSYM NELOG_FT_Update_In_Progress}

    {
    * The fault-tolerance error-log file, LANROOT\LOGS\FT.LOG, had the
    * update in progress bit set upon opening, which means that the
    * system crashed while working on the error log.
    }

  NELOG_Joined_Domain = (ERRLOG_BASE + 160);
  {$EXTERNALSYM NELOG_Joined_Domain}

    {
    * This computer has been successfully joined to %1 '%2'.
    }

  NELOG_Joined_Workgroup = (ERRLOG_BASE + 161);
  {$EXTERNALSYM NELOG_Joined_Workgroup}

    (*
    * This computer has been successfully joined to workgroup '%1'.
    *)


//
// Microsoft has created a generic error log entry for OEMs to use to
// log errors from OEM value added services.  The code, which is the
// 2nd arg to NetErrorLogWrite, is 3299.  This value is manifest in
// NET/H/ERRLOG.H as NELOG_OEM_Code.  The text for error log entry
// NELOG_OEM_Code is:  "%1 %2 %3 %4 %5 %6 %7 %8 %9.".
//
// Microsoft suggests that OEMs use the insertion strings as follows:
// %1:  OEM System Name (e.g. 3+Open)
// %2:  OEM Service Name (e.g. 3+Mail)
// %3:  Severity level (e.g.  error, warning, etc.)
// %4:  OEM error log entry sub-identifier  (e.g. error code #)
// %5 - % 9:  Text.
//
// The call to NetErrorWrite must set nstrings = 9, and provide 9
// ASCIIZ strings.  If the caller does not have 9 insertion strings,
// provide null strings for the empty insertion strings.
//

  NELOG_OEM_Code = (ERRLOG_BASE + 199);
  {$EXTERNALSYM NELOG_OEM_Code}

    {
    * %1 %2 %3 %4 %5 %6 %7 %8 %9.
    }

//
// another error log range defined for NT Lanman.
//

  ERRLOG2_BASE = 5700        { New NT NELOG errors start here };
  {$EXTERNALSYM ERRLOG2_BASE}


  NELOG_NetlogonSSIInitError = (ERRLOG2_BASE + 0);
  {$EXTERNALSYM NELOG_NetlogonSSIInitError}

    {
     * The Netlogon service could not initialize the replication data
     * structures successfully. The service was terminated.  The following
     * error occurred: %n%1
     }

  NELOG_NetlogonFailedToUpdateTrustList = (ERRLOG2_BASE + 1);
  {$EXTERNALSYM NELOG_NetlogonFailedToUpdateTrustList}

    {
     * The Netlogon service failed to update the domain trust list.  The
     * following error occurred: %n%1
     }

  NELOG_NetlogonFailedToAddRpcInterface = (ERRLOG2_BASE + 2);
  {$EXTERNALSYM NELOG_NetlogonFailedToAddRpcInterface}

    {
     * The Netlogon service could not add the RPC interface.  The
     * service was terminated. The following error occurred: %n%1
     }

  NELOG_NetlogonFailedToReadMailslot = (ERRLOG2_BASE + 3);
  {$EXTERNALSYM NELOG_NetlogonFailedToReadMailslot}

    {
     * The Netlogon service could not read a mailslot message from %1 due
     * to the following error: %n%2
     }

  NELOG_NetlogonFailedToRegisterSC = (ERRLOG2_BASE + 4);
  {$EXTERNALSYM NELOG_NetlogonFailedToRegisterSC}

    (*
     * The Netlogon service failed to register the service with the
     * service controller. The service was terminated. The following
     * error occurred: %n%1
     *)

  NELOG_NetlogonChangeLogCorrupt = (ERRLOG2_BASE + 5);
  {$EXTERNALSYM NELOG_NetlogonChangeLogCorrupt}

    {
     * The change log cache maintained by the Netlogon service for %1
     * database changes is inconsistent. The Netlogon service is resetting
     * the change log.
     }

  NELOG_NetlogonFailedToCreateShare = (ERRLOG2_BASE + 6);
  {$EXTERNALSYM NELOG_NetlogonFailedToCreateShare}

    {
     * The Netlogon service could not create server share %1.  The following
     * error occurred: %n%2
     }

  NELOG_NetlogonDownLevelLogonFailed = (ERRLOG2_BASE + 7);
  {$EXTERNALSYM NELOG_NetlogonDownLevelLogonFailed}

    {
     * The down-level logon request for the user %1 from %2 failed.
     }

  NELOG_NetlogonDownLevelLogoffFailed = (ERRLOG2_BASE + 8);
  {$EXTERNALSYM NELOG_NetlogonDownLevelLogoffFailed}

    {
     * The down-level logoff request for the user %1 from %2 failed.
     }

  NELOG_NetlogonNTLogonFailed = (ERRLOG2_BASE + 9);
  {$EXTERNALSYM NELOG_NetlogonNTLogonFailed}

    {
     * The Windows NT or Windows 2000 %1 logon request for the user %2\%3 from %4 (via %5)
     * failed.
     }

  NELOG_NetlogonNTLogoffFailed = (ERRLOG2_BASE + 10);
  {$EXTERNALSYM NELOG_NetlogonNTLogoffFailed}

    {
     * The Windows NT or Windows 2000 %1 logoff request for the user %2\%3 from %4
     * failed.
     }

  NELOG_NetlogonPartialSyncCallSuccess = (ERRLOG2_BASE + 11);
  {$EXTERNALSYM NELOG_NetlogonPartialSyncCallSuccess}

    {
     * The partial synchronization request from the server %1 completed
     * successfully. %2 changes(s) has(have) been returned to the
     * caller.
     }

  NELOG_NetlogonPartialSyncCallFailed = (ERRLOG2_BASE + 12);
  {$EXTERNALSYM NELOG_NetlogonPartialSyncCallFailed}

    {
     * The partial synchronization request from the server %1 failed with
     * the following error: %n%2
     }

  NELOG_NetlogonFullSyncCallSuccess = (ERRLOG2_BASE + 13);
  {$EXTERNALSYM NELOG_NetlogonFullSyncCallSuccess}

    {
     * The full synchronization request from the server %1 completed
     * successfully. %2 object(s) has(have) been returned to
     * the caller.
     }

  NELOG_NetlogonFullSyncCallFailed = (ERRLOG2_BASE + 14);
  {$EXTERNALSYM NELOG_NetlogonFullSyncCallFailed}

    {
     * The full synchronization request from the server %1 failed with
     * the following error: %n%2
     }

  NELOG_NetlogonPartialSyncSuccess = (ERRLOG2_BASE + 15);
  {$EXTERNALSYM NELOG_NetlogonPartialSyncSuccess}

    {
     * The partial synchronization replication of the %1 database from the
     * primary domain controller %2 completed successfully. %3 change(s) is(are)
     * applied to the database.
     }


  NELOG_NetlogonPartialSyncFailed = (ERRLOG2_BASE + 16);
  {$EXTERNALSYM NELOG_NetlogonPartialSyncFailed}

    {
     * The partial synchronization replication of the %1 database from the
     * primary domain controller %2 failed with the following error: %n%3
     }

  NELOG_NetlogonFullSyncSuccess = (ERRLOG2_BASE + 17);
  {$EXTERNALSYM NELOG_NetlogonFullSyncSuccess}

    {
     * The full synchronization replication of the %1 database from the
     * primary domain controller %2 completed successfully.
     }


  NELOG_NetlogonFullSyncFailed = (ERRLOG2_BASE + 18);
  {$EXTERNALSYM NELOG_NetlogonFullSyncFailed}

    {
     * The full synchronization replication of the %1 database from the
     * primary domain controller %2 failed with the following error: %n%3
     }

  NELOG_NetlogonAuthNoDomainController = (ERRLOG2_BASE + 19);
  {$EXTERNALSYM NELOG_NetlogonAuthNoDomainController}

    {
     * This computer was not able to set up a secure session with a domain
     * controller in domain %1 due to the following: %n%2
     * %nThis may lead to authentication problems. Make sure that this
     * computer is connected to the network. If the problem persists,
     * please contact your domain administrator.
     *
     * %n%nADDITIONAL INFO
     * %nIf this computer is a domain controller for the specified domain, it
     * sets up the secure session to the primary domain controller emulator in the specified
     * domain. Otherwise, this computer sets up the secure session to any domain controller
     * in the specified domain.
     }

  NELOG_NetlogonAuthNoTrustLsaSecret = (ERRLOG2_BASE + 20);
  {$EXTERNALSYM NELOG_NetlogonAuthNoTrustLsaSecret}

    {
     * The session setup to the Windows NT or Windows 2000 Domain Controller %1 for the domain %2
     * failed because the computer %3 does not have a local security database account.
     }

  NELOG_NetlogonAuthNoTrustSamAccount = (ERRLOG2_BASE + 21);
  {$EXTERNALSYM NELOG_NetlogonAuthNoTrustSamAccount}

    {
     * The session setup to the Windows NT or Windows 2000 Domain Controller %1 for the domain %2
     * failed because the Domain Controller did not have an account %4
     * needed to set up the session by this computer %3.
     *
     * %n%nADDITIONAL DATA
     * %nIf this computer is a member of or a Domain Controller in the specified domain, the
     * aforementioned account is a computer account for this computer in the specified domain.
     * Otherwise, the account is an interdomain trust account with the specified domain.
     }

  NELOG_NetlogonServerAuthFailed = (ERRLOG2_BASE + 22);
  {$EXTERNALSYM NELOG_NetlogonServerAuthFailed}

    {
     * The session setup from the computer %1 failed to authenticate.
     * The name(s) of the account(s) referenced in the security database is
     * %2.  The following error occurred: %n%3
     }

  NELOG_NetlogonServerAuthNoTrustSamAccount = (ERRLOG2_BASE + 23);
  {$EXTERNALSYM NELOG_NetlogonServerAuthNoTrustSamAccount}

    {
     * The session setup from computer '%1' failed because the security database
     * does not contain a trust account '%2' referenced by the specified computer.
     *
     * %n%nUSER ACTION
     *
     * %nIf this is the first occurrence of this event for the specified computer
     * and account, this may be a transient issue that doesn't require any action
     * at this time. Otherwise, the following steps may be taken to resolve this problem:
     *
     * %n%nIf '%2' is a legitimate machine account for the computer '%1', then '%1'
     * should be rejoined to the domain.
     *
     * %n%nIf '%2' is a legitimate interdomain trust account, then the trust should
     * be recreated.
     *
     * %n%nOtherwise, assuming that '%2' is not a legitimate account, the following
     * action should be taken on '%1':
     *
     * %n%nIf '%1' is a Domain Controller, then the trust associated with '%2' should be deleted.
     *
     * %n%nIf '%1' is not a Domain Controller, it should be disjoined from the domain.
     }

//
// General log messages for NT services.
//

  NELOG_FailedToRegisterSC = (ERRLOG2_BASE + 24);
  {$EXTERNALSYM NELOG_FailedToRegisterSC}

    {
     * Could not register control handler with service controller %1.
     }

  NELOG_FailedToSetServiceStatus = (ERRLOG2_BASE + 25);
  {$EXTERNALSYM NELOG_FailedToSetServiceStatus}

    {
     * Could not set service status with service controller %1.
     }

  NELOG_FailedToGetComputerName = (ERRLOG2_BASE + 26);
  {$EXTERNALSYM NELOG_FailedToGetComputerName}

    {
     * Could not find the computer name %1.
     }

  NELOG_DriverNotLoaded = (ERRLOG2_BASE + 27);
  {$EXTERNALSYM NELOG_DriverNotLoaded}

    {
     * Could not load %1 device driver.
     }

  NELOG_NoTranportLoaded = (ERRLOG2_BASE + 28);
  {$EXTERNALSYM NELOG_NoTranportLoaded}

    {
     * Could not load any transport.
     }

//
// More Netlogon service events
//

  NELOG_NetlogonFailedDomainDelta = (ERRLOG2_BASE + 29);
  {$EXTERNALSYM NELOG_NetlogonFailedDomainDelta}

    {
     * Replication of the %1 Domain Object "%2" from primary domain controller
     * %3 failed with the following error: %n%4
     }

  NELOG_NetlogonFailedGlobalGroupDelta = (ERRLOG2_BASE + 30);
  {$EXTERNALSYM NELOG_NetlogonFailedGlobalGroupDelta}

    {
     * Replication of the %1 Global Group "%2" from primary domain controller
     * %3 failed with the following error: %n%4
     }

  NELOG_NetlogonFailedLocalGroupDelta = (ERRLOG2_BASE + 31);
  {$EXTERNALSYM NELOG_NetlogonFailedLocalGroupDelta}

    {
     * Replication of the %1 Local Group "%2" from primary domain controller
     * %3 failed with the following error: %n%4
     }

  NELOG_NetlogonFailedUserDelta = (ERRLOG2_BASE + 32);
  {$EXTERNALSYM NELOG_NetlogonFailedUserDelta}

    {
     * Replication of the %1 User "%2" from primary domain controller
     * %3 failed with the following error: %n%4
     }

  NELOG_NetlogonFailedPolicyDelta = (ERRLOG2_BASE + 33);
  {$EXTERNALSYM NELOG_NetlogonFailedPolicyDelta}

    {
     * Replication of the %1 Policy Object "%2" from primary domain controller
     * %3 failed with the following error: %n%4
     }

  NELOG_NetlogonFailedTrustedDomainDelta = (ERRLOG2_BASE + 34);
  {$EXTERNALSYM NELOG_NetlogonFailedTrustedDomainDelta}

    {
     * Replication of the %1 Trusted Domain Object "%2" from primary domain controller
     * %3 failed with the following error: %n%4
     }

  NELOG_NetlogonFailedAccountDelta = (ERRLOG2_BASE + 35);
  {$EXTERNALSYM NELOG_NetlogonFailedAccountDelta}

    {
     * Replication of the %1 Account Object "%2" from primary domain controller
     * %3 failed with the following error: %n%4
     }

  NELOG_NetlogonFailedSecretDelta = (ERRLOG2_BASE + 36);
  {$EXTERNALSYM NELOG_NetlogonFailedSecretDelta}

    {
     * Replication of the %1 Secret "%2" from primary domain controller
     * %3 failed with the following error: %n%4
     }

  NELOG_NetlogonSystemError = (ERRLOG2_BASE + 37);
  {$EXTERNALSYM NELOG_NetlogonSystemError}

    {
    * The system returned the following unexpected error code: %n%1
    }

  NELOG_NetlogonDuplicateMachineAccounts = (ERRLOG2_BASE + 38);
  {$EXTERNALSYM NELOG_NetlogonDuplicateMachineAccounts}

    {
    * Netlogon has detected two machine accounts for server "%1".
    * The server can be either a Windows 2000 Server that is a member of the
    * domain or the server can be a LAN Manager server with an account in the
    * SERVERS global group.  It cannot be both.
    }

  NELOG_NetlogonTooManyGlobalGroups = (ERRLOG2_BASE + 39);
  {$EXTERNALSYM NELOG_NetlogonTooManyGlobalGroups}

    {
    * This domain has more global groups than can be replicated to a LanMan
    * BDC.  Either delete some of your global groups or remove the LanMan
    * BDCs from the domain.
    }

  NELOG_NetlogonBrowserDriver = (ERRLOG2_BASE + 40);
  {$EXTERNALSYM NELOG_NetlogonBrowserDriver}

    {
    * The Browser driver returned the following error to Netlogon: %n%1
    }

  NELOG_NetlogonAddNameFailure = (ERRLOG2_BASE + 41);
  {$EXTERNALSYM NELOG_NetlogonAddNameFailure}

    {
    * Netlogon could not register the %1<1B> name for the following reason: %n%2
    }

//
//  More Remoteboot service events.
//
  NELOG_RplMessages = (ERRLOG2_BASE + 42);
  {$EXTERNALSYM NELOG_RplMessages}

    {
    * Service failed to retrieve messages needed to boot remote boot clients.
    }

  NELOG_RplXnsBoot = (ERRLOG2_BASE + 43);
  {$EXTERNALSYM NELOG_RplXnsBoot}

    {
    * Service experienced a severe error and can no longer provide remote boot
    * for 3Com 3Start remote boot clients.
    }

  NELOG_RplSystem = (ERRLOG2_BASE + 44);
  {$EXTERNALSYM NELOG_RplSystem}

    {
    * Service experienced a severe system error and will shut itself down.
    }

  NELOG_RplWkstaTimeout = (ERRLOG2_BASE + 45);
  {$EXTERNALSYM NELOG_RplWkstaTimeout}

    {
    * Client with computer name %1 failed to acknowledge receipt of the
    * boot data.  Remote boot of this client was not completed.
    }

  NELOG_RplWkstaFileOpen = (ERRLOG2_BASE + 46);
  {$EXTERNALSYM NELOG_RplWkstaFileOpen}

    {
    * Client with computer name %1 was not booted due to an error in opening
    * file %2.
    }

  NELOG_RplWkstaFileRead = (ERRLOG2_BASE + 47);
  {$EXTERNALSYM NELOG_RplWkstaFileRead}

    {
    * Client with computer name %1 was not booted due to an error in reading
    * file %2.
    }

  NELOG_RplWkstaMemory = (ERRLOG2_BASE + 48);
  {$EXTERNALSYM NELOG_RplWkstaMemory}

    {
    * Client with computer name %1 was not booted due to insufficient memory
    * at the remote boot server.
    }

  NELOG_RplWkstaFileChecksum = (ERRLOG2_BASE + 49);
  {$EXTERNALSYM NELOG_RplWkstaFileChecksum}

    {
    * Client with computer name %1 will be booted without using checksums
    * because checksum for file %2 could not be calculated.
    }

  NELOG_RplWkstaFileLineCount = (ERRLOG2_BASE + 50);
  {$EXTERNALSYM NELOG_RplWkstaFileLineCount}

    {
    * Client with computer name %1 was not booted due to too many lines in
    * file %2.
    }

  NELOG_RplWkstaBbcFile = (ERRLOG2_BASE + 51);
  {$EXTERNALSYM NELOG_RplWkstaBbcFile}

    {
    * Client with computer name %1 was not booted because the boot block
    * configuration file %2 for this client does not contain boot block
    * line and/or loader line.
    }

  NELOG_RplWkstaFileSize = (ERRLOG2_BASE + 52);
  {$EXTERNALSYM NELOG_RplWkstaFileSize}

    {
    * Client with computer name %1 was not booted due to a bad size of
    * file %2.
    }

  NELOG_RplWkstaInternal = (ERRLOG2_BASE + 53);
  {$EXTERNALSYM NELOG_RplWkstaInternal}

    {
    * Client with computer name %1 was not booted due to remote boot
    * service internal error.
    }

  NELOG_RplWkstaWrongVersion = (ERRLOG2_BASE + 54);
  {$EXTERNALSYM NELOG_RplWkstaWrongVersion}

    {
    * Client with computer name %1 was not booted because file %2 has an
    * invalid boot header.
    }

  NELOG_RplWkstaNetwork = (ERRLOG2_BASE + 55);
  {$EXTERNALSYM NELOG_RplWkstaNetwork}

    {
    * Client with computer name %1 was not booted due to network error.
    }

  NELOG_RplAdapterResource = (ERRLOG2_BASE + 56);
  {$EXTERNALSYM NELOG_RplAdapterResource}

    {
    * Client with adapter id %1 was not booted due to lack of resources.
    }

  NELOG_RplFileCopy = (ERRLOG2_BASE + 57);
  {$EXTERNALSYM NELOG_RplFileCopy}

    {
    * Service experienced error copying file or directory %1.
    }

  NELOG_RplFileDelete = (ERRLOG2_BASE + 58);
  {$EXTERNALSYM NELOG_RplFileDelete}

    {
    * Service experienced error deleting file or directory %1.
    }

  NELOG_RplFilePerms = (ERRLOG2_BASE + 59);
  {$EXTERNALSYM NELOG_RplFilePerms}

    {
    * Service experienced error setting permissions on file or directory %1.
    }
  NELOG_RplCheckConfigs = (ERRLOG2_BASE + 60);
  {$EXTERNALSYM NELOG_RplCheckConfigs}

    {
    * Service experienced error evaluating RPL configurations.
    }
  NELOG_RplCreateProfiles = (ERRLOG2_BASE + 61);
  {$EXTERNALSYM NELOG_RplCreateProfiles}

    {
    * Service experienced error creating RPL profiles for all configurations.
    }
  NELOG_RplRegistry = (ERRLOG2_BASE + 62);
  {$EXTERNALSYM NELOG_RplRegistry}

    {
    * Service experienced error accessing registry.
    }
  NELOG_RplReplaceRPLDISK = (ERRLOG2_BASE + 63);
  {$EXTERNALSYM NELOG_RplReplaceRPLDISK}

    {
    * Service experienced error replacing possibly outdated RPLDISK.SYS.
    }
  NELOG_RplCheckSecurity = (ERRLOG2_BASE + 64);
  {$EXTERNALSYM NELOG_RplCheckSecurity}

    {
    * Service experienced error adding security accounts or setting
    * file permissions.  These accounts are the RPLUSER local group
    * and the user accounts for the individual RPL workstations.
    }
  NELOG_RplBackupDatabase = (ERRLOG2_BASE + 65);
  {$EXTERNALSYM NELOG_RplBackupDatabase}

    {
    * Service failed to back up its database.
    }
  NELOG_RplInitDatabase = (ERRLOG2_BASE + 66);
  {$EXTERNALSYM NELOG_RplInitDatabase}

    {
    * Service failed to initialize from its database.  The database may be
    * missing or corrupted.  Service will attempt restoring the database
    * from the backup.
    }
  NELOG_RplRestoreDatabaseFailure = (ERRLOG2_BASE + 67);
  {$EXTERNALSYM NELOG_RplRestoreDatabaseFailure}

    {
    * Service failed to restore its database from the backup.  Service
    * will not start.
    }
  NELOG_RplRestoreDatabaseSuccess = (ERRLOG2_BASE + 68);
  {$EXTERNALSYM NELOG_RplRestoreDatabaseSuccess}

    {
    * Service successfully restored its database from the backup.
    }
  NELOG_RplInitRestoredDatabase = (ERRLOG2_BASE + 69);
  {$EXTERNALSYM NELOG_RplInitRestoredDatabase}

    {
    * Service failed to initialize from its restored database.  Service
    * will not start.
    }

//
// More Netlogon and RPL service events
//
  NELOG_NetlogonSessionTypeWrong = (ERRLOG2_BASE + 70);
  {$EXTERNALSYM NELOG_NetlogonSessionTypeWrong}

    {
     * The session setup to the Windows NT or Windows 2000 Domain Controller %1 from computer
     * %2 using account %4 failed.  %2 is declared to be a BDC in domain %3.
     * However, %2 tried to connect as either a DC in a trusted domain,
     * a member workstation in domain %3, or as a server in domain %3.
     * Use the Active Directory Users and Computers tool or Server Manager to remove the BDC account for %2.
     }
  NELOG_RplUpgradeDBTo40 = (ERRLOG2_BASE + 71);
  {$EXTERNALSYM NELOG_RplUpgradeDBTo40}

    {
    * The Remoteboot database was in NT 3.5 / NT 3.51 format and NT is
    * attempting to convert it to NT 4.0 format. The JETCONV converter
    * will write to the Application event log when it is finished.
    }
  NELOG_NetlogonLanmanBdcsNotAllowed = (ERRLOG2_BASE + 72);
  {$EXTERNALSYM NELOG_NetlogonLanmanBdcsNotAllowed}

    {
     * Global group SERVERS exists in domain %1 and has members.
     * This group defines Lan Manager BDCs in the domain.
     * Lan Manager BDCs are not permitted in NT domains.
     }
  NELOG_NetlogonNoDynamicDns = (ERRLOG2_BASE + 73);
  {$EXTERNALSYM NELOG_NetlogonNoDynamicDns}

    {
     * The following DNS server that is authoritative for the DNS domain controller
     * locator records of this domain controller does not support dynamic DNS updates:
     *
     * %n%nDNS server IP address: %1
     * %nReturned Response Code (RCODE): %2
     * %nReturned Status Code: %3
     *
     * %n%nUSER ACTION
     *
     * %nConfigure the DNS server to allow dynamic DNS updates or manually add the DNS
     * records from the file '%SystemRoot%\System32\Config\Netlogon.dns' to the DNS database.
     }

  NELOG_NetlogonDynamicDnsRegisterFailure = (ERRLOG2_BASE + 74);
  {$EXTERNALSYM NELOG_NetlogonDynamicDnsRegisterFailure}

    {
      *
      * The dynamic registration of the DNS record '%1' failed on the following DNS server:
      *
      * %n%nDNS server IP address: %3
      * %nReturned Response Code (RCODE): %4
      * %nReturned Status Code: %5
      *
      * %n%nFor computers and users to locate this domain controller, this record must be
      * registered in DNS.
      *
      * %n%nUSER ACTION
      *
      * %nDetermine what might have caused this failure, resolve the problem, and initiate
      * registration of the DNS records by the domain controller. To determine what might
      * have caused this failure, run DCDiag.exe. You can find this program on the Windows
      * Server 2003 installation CD in Support\Tools\support.cab. To learn more about
      * DCDiag.exe, see Help and Support Center. To initiate registration of the DNS records by
      * this domain controller, run 'nltest.exe /dsregdns' from the command prompt on the domain
      * controller or restart Net Logon service. Nltest.exe is available in the Microsoft Windows
      * Server Resource Kit CD. %n  Or, you can manually add this record to DNS, but it is not
      * recommended.
      *
      * %n%nADDITIONAL DATA
      * %nError Value: %2
      *
     }

  NELOG_NetlogonDynamicDnsDeregisterFailure = (ERRLOG2_BASE + 75);
  {$EXTERNALSYM NELOG_NetlogonDynamicDnsDeregisterFailure}

    {
      * The dynamic deletion of the DNS record '%1' failed on the following DNS server:
      *
      * %n%nDNS server IP address: %3
      * %nReturned Response Code (RCODE): %4
      * %nReturned Status Code: %5
      *
      * %n%nUSER ACTION
      *
      * %nTo prevent remote computers from connecting unnecessarily to the domain controller,
      * delete the record manually or troubleshoot the failure to dynamically delete the
      * record. To learn more about debugging DNS, see Help and Support Center.
      *
      * %n%nADDITIONAL DATA
      * %nError Value: %2
     }

  NELOG_NetlogonFailedFileCreate = (ERRLOG2_BASE + 76);
  {$EXTERNALSYM NELOG_NetlogonFailedFileCreate}

    {
     * Failed to create/open file %1 with the following error: %n%2
     }

  NELOG_NetlogonGetSubnetToSite = (ERRLOG2_BASE + 77);
  {$EXTERNALSYM NELOG_NetlogonGetSubnetToSite}

    {
     * Netlogon got the following error while trying to get the subnet to site
     * mapping information from the DS: %n%1
     }

  NELOG_NetlogonNoSiteForClient = (ERRLOG2_BASE + 78);
  {$EXTERNALSYM NELOG_NetlogonNoSiteForClient}

   {
    * '%1' tried to determine its site by looking up its IP address ('%2')
    * in the Configuration\Sites\Subnets container in the DS.  No subnet matched
    * the IP address.  Consider adding a subnet object for this IP address.
    }

  NELOG_NetlogonBadSiteName = (ERRLOG2_BASE + 79);
  {$EXTERNALSYM NELOG_NetlogonBadSiteName}

    {
     * The site name for this computer is '%1'.  That site name is not a valid
     * site name.  A site name must be a valid DNS label.
     * Rename the site to be a valid name.
     }

  NELOG_NetlogonBadSubnetName = (ERRLOG2_BASE + 80);
  {$EXTERNALSYM NELOG_NetlogonBadSubnetName}

    {
     * The subnet object '%1' appears in the Configuration\Sites\Subnets
     * container in the DS.  The name is not syntactically valid.  The valid
     * syntax is xx.xx.xx.xx/yy where xx.xx.xx.xx is a valid IP subnet number
     * and yy is the number of bits in the subnet mask.
     *
     * Correct the name of the subnet object.
     }

  NELOG_NetlogonDynamicDnsServerFailure = (ERRLOG2_BASE + 81);
  {$EXTERNALSYM NELOG_NetlogonDynamicDnsServerFailure}

    {
     * Dynamic registration or deletion of one or more DNS records associated with DNS
     * domain '%1' failed.  These records are used by other computers to locate this
     * server as a domain controller (if the specified domain is an Active Directory
     * domain) or as an LDAP server (if the specified domain is an application partition).
     *
     * %n%nPossible causes of failure include:
     *
     * %n- TCP/IP properties of the network connections of this computer contain wrong IP address(es) of the preferred and alternate DNS servers
     * %n- Specified preferred and alternate DNS servers are not running
     * %n- DNS server(s) primary for the records to be registered is not running
     * %n- Preferred or alternate DNS servers are configured with wrong root hints
     * %n- Parent DNS zone contains incorrect delegation to the child zone authoritative for the DNS records that failed registration
     *
     * %n%nUSER ACTION
     *
     * %nFix possible misconfiguration(s) specified above and initiate registration or deletion of
     * the DNS records by running 'nltest.exe /dsregdns' from the command prompt or by restarting
     * Net Logon service. Nltest.exe is available in the Microsoft Windows Server Resource Kit CD.
     }

  NELOG_NetlogonDynamicDnsFailure = (ERRLOG2_BASE + 82);
  {$EXTERNALSYM NELOG_NetlogonDynamicDnsFailure}

    {
     * Dynamic registration or deregistration of one or more DNS records failed with the following error: %n%1
     }

  NELOG_NetlogonRpcCallCancelled = (ERRLOG2_BASE + 83);
  {$EXTERNALSYM NELOG_NetlogonRpcCallCancelled}

    {
     * The session setup to the Windows NT or Windows 2000 Domain Controller %1 for the domain %2
     * is not responsive.  The current RPC call from Netlogon on \\%3 to %1 has been cancelled.
     }

  NELOG_NetlogonDcSiteCovered = (ERRLOG2_BASE + 84);
  {$EXTERNALSYM NELOG_NetlogonDcSiteCovered}

    {
     * Site '%2' does not have any Domain Controllers for domain '%3'.
     * Domain Controllers in site '%1' have been automatically
     * selected to cover site '%2' for domain '%3' based on configured
     * Directory Server replication costs.
     }

  NELOG_NetlogonDcSiteNotCovered = (ERRLOG2_BASE + 85);
  {$EXTERNALSYM NELOG_NetlogonDcSiteNotCovered}

    {
     * This Domain Controller no longer automatically covers site '%1' for domain '%2'.
     }

  NELOG_NetlogonGcSiteCovered = (ERRLOG2_BASE + 86);
  {$EXTERNALSYM NELOG_NetlogonGcSiteCovered}

    {
     * Site '%2' does not have any Global Catalog servers for forest '%3'.
     * Global Catalog servers in site '%1' have been automatically
     * selected to cover site '%2' for forest '%3' based on configured
     * Directory Server replication costs.
     }

  NELOG_NetlogonGcSiteNotCovered = (ERRLOG2_BASE + 87);
  {$EXTERNALSYM NELOG_NetlogonGcSiteNotCovered}

    {
     * This Global Catalog server no longer automatically covers site '%1' for forest '%2'.
     }

  NELOG_NetlogonFailedSpnUpdate = (ERRLOG2_BASE + 88);
  {$EXTERNALSYM NELOG_NetlogonFailedSpnUpdate}

    {
     * Attempt to update HOST Service Principal Names (SPNs) of the computer
     * object in Active Directory failed. The updated values were '%1' and '%2'.
     * The following error occurred: %n%3
     }

  NELOG_NetlogonFailedDnsHostNameUpdate = (ERRLOG2_BASE + 89);
  {$EXTERNALSYM NELOG_NetlogonFailedDnsHostNameUpdate}

    {
     * Attempt to update DNS Host Name of the computer object
     * in Active Directory failed. The updated value was '%1'.
     * The following error occurred: %n%2
     }

  NELOG_NetlogonAuthNoUplevelDomainController = (ERRLOG2_BASE + 90);
  {$EXTERNALSYM NELOG_NetlogonAuthNoUplevelDomainController}

    {
     * No suitable Domain Controller is available for domain %1.
     * An NT4 or older domain controller is available but it cannot
     * be used for authentication purposes in the Windows 2000 or newer
     * domain that this computer is a member of.
     * The following error occurred:%n%2
     }

  NELOG_NetlogonAuthDomainDowngraded = (ERRLOG2_BASE + 91);
  {$EXTERNALSYM NELOG_NetlogonAuthDomainDowngraded}

    {
     * The domain of this computer, %1 has been downgraded from Windows 2000
     * or newer to Windows NT4 or older. The computer cannot function properly
     * in this case for authentication purposes. This computer needs to rejoin
     * the domain.
     * The following error occurred:%n%2
     }

  NELOG_NetlogonNdncSiteCovered = (ERRLOG2_BASE + 92);
  {$EXTERNALSYM NELOG_NetlogonNdncSiteCovered}

    {
     * Site '%2' does not have any LDAP servers for non-domain NC '%3'.
     * LDAP servers in site '%1' have been automatically selected to
     * cover site '%2' for non-domain NC '%3' based on configured
     * Directory Server replication costs.
     }

  NELOG_NetlogonNdncSiteNotCovered = (ERRLOG2_BASE + 93);
  {$EXTERNALSYM NELOG_NetlogonNdncSiteNotCovered}

    {
     * This LDAP server no longer automatically covers site '%1' for non-domain NC '%2'.
     }

  NELOG_NetlogonDcOldSiteCovered = (ERRLOG2_BASE + 94);
  {$EXTERNALSYM NELOG_NetlogonDcOldSiteCovered}

    {
     * Site '%2' is no longer manually configured in the registry as
     * covered by this Domain Controller for domain '%3'. As a result,
     * site '%2' does not have any Domain Controllers for domain '%3'.
     * Domain Controllers in site '%1' have been automatically
     * selected to cover site '%2' for domain '%3' based on configured
     * Directory Server replication costs.
     }

  NELOG_NetlogonDcSiteNotCoveredAuto = (ERRLOG2_BASE + 95);
  {$EXTERNALSYM NELOG_NetlogonDcSiteNotCoveredAuto}

    {
     * This Domain Controller no longer automatically covers site '%1' for domain '%2'.
     * However, site '%1' is still (manually) covered by this Domain Controller for
     * domain '%2' since this site has been manually configured in the registry.
     }

  NELOG_NetlogonGcOldSiteCovered = (ERRLOG2_BASE + 96);
  {$EXTERNALSYM NELOG_NetlogonGcOldSiteCovered}

    {
     * Site '%2' is no longer manually configured in the registry as
     * covered by this Global Catalog server for forest '%3'. As a result,
     * site '%2' does not have any Global Catalog servers for forest '%3'.
     * Global Catalog servers in site '%1' have been automatically
     * selected to cover site '%2' for forest '%3' based on configured
     * Directory Server replication costs.
     }

  NELOG_NetlogonGcSiteNotCoveredAuto = (ERRLOG2_BASE + 97);
  {$EXTERNALSYM NELOG_NetlogonGcSiteNotCoveredAuto}

    {
     * This Global Catalog server no longer automatically covers site '%1' for forest '%2'.
     * However, site '%1' is still (manually) covered by this Global catalog for
     * forest '%2' since this site has been manually configured in the registry.
     }

  NELOG_NetlogonNdncOldSiteCovered = (ERRLOG2_BASE + 98);
  {$EXTERNALSYM NELOG_NetlogonNdncOldSiteCovered}

    {
     * Site '%2' is no longer manually configured in the registry as
     * covered by this LDAP server for non-domain NC '%3'. As a result,
     * site '%2' does not have any LDAP servers for non-domain NC '%3'.
     * LDAP servers in site '%1' have been automatically
     * selected to cover site '%2' for non-domain NC '%3' based on
     * configured Directory Server replication costs.
     }

  NELOG_NetlogonNdncSiteNotCoveredAuto = (ERRLOG2_BASE + 99);
  {$EXTERNALSYM NELOG_NetlogonNdncSiteNotCoveredAuto}

    {
     * This LDAP server no longer automatically covers site '%1' for non-domain NC '%2'.
     * However, site '%1' is still (manually) covered by this LDAP server for
     * non-domain NC '%2' since this site has been manually configured in the registry.
     }

  NELOG_NetlogonSpnMultipleSamAccountNames = (ERRLOG2_BASE + 100);
  {$EXTERNALSYM NELOG_NetlogonSpnMultipleSamAccountNames}

    {
     * Attempt to update DnsHostName and HOST Service Principal Name (SPN) attributes
     * of the computer object in Active Directory failed because the Domain Controller
     * '%1' had more than one account with the name '%2' corresponding to this computer.
     * Not having SPNs registered may result in authentication failures for this computer.
     * Contact your domain administrator who may need to manually resolve the account name
     * collision.
     }

  NELOG_NetlogonSpnCrackNamesFailure = (ERRLOG2_BASE + 101);
  {$EXTERNALSYM NELOG_NetlogonSpnCrackNamesFailure}

    {
     * Attempt to update DnsHostName and HOST Service Principal Name (SPN) attributes
     * of the computer object in Active Directory failed because this computer account
     * name, '%2' could not be mapped to the computer object on Domain Controller '%1'.
     * Not having SPNs registered may result in authentication failures for this computer.
     * Contact your domain administrator. The following technical information may be
     * useful for the resolution of this failure:%n
     * DsCrackNames status = 0x%3, crack error = 0x%4.
     }

  NELOG_NetlogonNoAddressToSiteMapping = (ERRLOG2_BASE + 102);
  {$EXTERNALSYM NELOG_NetlogonNoAddressToSiteMapping}

    {
     * None of the IP addresses (%2) of this Domain Controller map to the configured site '%1'.
     * While this may be a temporary situation due to IP address changes, it is generally
     * recommended that the IP address of the Domain Controller (accessible to machines in
     * its domain) maps to the Site which it services. If the above list of IP addresses is
     * stable, consider moving this server to a site (or create one if it does not already
     * exist) such that the above IP address maps to the selected site. This may require the
     * creation of a new subnet object (whose range includes the above IP address) which maps
     * to the selected site object.
     }

  NELOG_NetlogonInvalidGenericParameterValue = (ERRLOG2_BASE + 103);
  {$EXTERNALSYM NELOG_NetlogonInvalidGenericParameterValue}

    {
     * The following error occurred while reading a parameter '%2' in the
     * Netlogon %1 registry section:%n%3
     }

  NELOG_NetlogonInvalidDwordParameterValue = (ERRLOG2_BASE + 104);
  {$EXTERNALSYM NELOG_NetlogonInvalidDwordParameterValue}

    {
     * The Netlogon %1 registry key contains an invalid value 0x%2 for parameter '%3'.
     * The minimum and maximum values allowed for this parameter are 0x%4 and 0x%5, respectively.
     * The value of 0x%6 has been assigned to this parameter.
     }

  NELOG_NetlogonServerAuthFailedNoAccount = (ERRLOG2_BASE + 105);
  {$EXTERNALSYM NELOG_NetlogonServerAuthFailedNoAccount}

    {
     * The session setup from the computer %1 failed to authenticate.
     * The following error occurred: %n%2
     }

  NELOG_NetlogonNoDynamicDnsManual = (ERRLOG2_BASE + 106);
  {$EXTERNALSYM NELOG_NetlogonNoDynamicDnsManual}

    (*
     * Dynamic DNS updates have been manually disabled on this domain controller.
     *
     * %n%nUSER ACTION
     *
     * %nReconfigure this domain controller to use dynamic DNS updates or manually add the DNS
     * records from the file '%SystemRoot%\System32\Config\Netlogon.dns' to the DNS database.
     *)

  NELOG_NetlogonNoSiteForClients = (ERRLOG2_BASE + 107);
  {$EXTERNALSYM NELOG_NetlogonNoSiteForClients}

    {
     * During the past %1 hours there have been %2 connections to this Domain
     * Controller from client machines whose IP addresses don't map to any of
     * the existing sites in the enterprise. Those clients, therefore, have
     * undefined sites and may connect to any Domain Controller including
     * those that are in far distant locations from the clients. A client's site
     * is determined by the mapping of its subnet to one of the existing sites.
     * To move the above clients to one of the sites, please consider creating
     * subnet object(s) covering the above IP addresses with mapping to one of the
     * existing sites.  The names and IP addresses of the clients in question have
     * been logged on this computer in the following log file
     * '%SystemRoot%\debug\netlogon.log' and, potentially, in the log file
     * '%SystemRoot%\debug\netlogon.bak' created if the former log becomes full.
     * The log(s) may contain additional unrelated debugging information. To filter
     * out the needed information, please search for lines which contain text
     * 'NO_CLIENT_SITE:'. The first word after this string is the client name and
     * the second word is the client IP address. The maximum size of the log(s) is
     * controlled by the following registry DWORD value
     * 'HKEY_LOCAL_MACHINE\SYSTEM\CurrentControlSet\Services\Netlogon\Parameters\LogFileMaxSize';
     * the default is %3 bytes.  The current maximum size is %4 bytes.  To set a
     * different maximum size, create the above registry value and set the desired
     * maximum size in bytes.
     }

  NELOG_NetlogonDnsDeregAborted               = (ERRLOG2_BASE + 108);
  {$EXTERNALSYM NELOG_NetlogonDnsDeregAborted}

    (*
     * The deregistration of some DNS domain controller locator records was aborted
     * at the time of this domain controller demotion because the DNS deregistrations
     * took too long.
     *
     * %n%nUSER ACTION
     *
     * %nManually delete the DNS records listed in the file
     * '%SystemRoot%\System32\Config\Netlogon.dns' from the DNS database.
     *)

  NELOG_NetlogonRpcPortRequestFailure         = (ERRLOG2_BASE + 109);
  {$EXTERNALSYM NELOG_NetlogonRpcPortRequestFailure}

    (*
     * The NetLogon service on this domain controller has been configured to use port %1
     * for incoming RPC connections over TCP/IP from remote machines. However, the
     * following error occurred when Netlogon attempted to register this port with the RPC
     * endpoint mapper service: %n%2 %nThis will prevent the NetLogon service on remote
     * machines from connecting to this domain controller over TCP/IP that may result in
     * authentication problems.
     *
     * %n%nUSER ACTION
     *
     * %nThe specified port is configured via the Group Policy or via a registry value 'DcTcpipPort'
     * under the 'HKEY_LOCAL_MACHINE\SYSTEM\CurrentControlSet\Services\Netlogon\Parameters'
     * registry key; the value configured through the Group Policy takes precedence. If the
     * port specified is in error, reset it to a correct value. You can also remove this
     * configuration for the port in which case the port will be assigned dynamically by
     * the endpoint mapper at the time the NetLogon service on remote machines makes RPC connections
     * to this domain controller. After the misconfiguration is corrected, restart the NetLogon
     * service on this machine and verify that this event log no longer appears.
     *)

implementation


{$IFDEF DYNAMIC_LINK}
var
  _NetErrorLogClear: Pointer;

function NetErrorLogClear;
begin
  GetProcedureAddress(_NetErrorLogClear, netapi32, 'NetErrorLogClear');
  asm
    mov esp, ebp
    pop ebp
    jmp [_NetErrorLogClear]
  end;
end;
{$ELSE}
function NetErrorLogClear; external netapi32 name 'NetErrorLogClear';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _NetErrorLogRead: Pointer;

function NetErrorLogRead;
begin
  GetProcedureAddress(_NetErrorLogRead, netapi32, 'NetErrorLogRead');
  asm
    mov esp, ebp
    pop ebp
    jmp [_NetErrorLogRead]
  end;
end;
{$ELSE}
function NetErrorLogRead; external netapi32 name 'NetErrorLogRead';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _NetErrorLogWrite: Pointer;

function NetErrorLogWrite;
begin
  GetProcedureAddress(_NetErrorLogWrite, netapi32, 'NetErrorLogWrite');
  asm
    mov esp, ebp
    pop ebp
    jmp [_NetErrorLogWrite]
  end;
end;
{$ELSE}
function NetErrorLogWrite; external netapi32 name 'NetErrorLogWrite';
{$ENDIF DYNAMIC_LINK}

end.
