{******************************************************************************}
{                                                       	               }
{ Lan Manager API interface Unit for Object Pascal                             }
{                                                       	               }
{ Portions created by Microsoft are Copyright (C) 1995-2001 Microsoft          }
{ Corporation. All Rights Reserved.                                            }
{ 								               }
{ The original file is: lm.h, released June 2000. The original Pascal          }
{ code is: LM.pas, released December 2000. The initial developer of the        }
{ Pascal code is Petr Vones (petr.v@mujmail.cz).                               }
{                                                                              }
{ Portions created by Petr Vones are Copyright (C) 2000 Petr Vones             }
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

unit JwaLM;

{$ALIGN ON}
{$MINENUMSIZE 4}
{$WEAKPACKAGEUNIT}

interface

(*$HPPEMIT '#include <windef.h>'*)
(*$HPPEMIT '#include <winerror.h>'*)
(*$HPPEMIT '#include <winsvc.h>'*)

(*$HPPEMIT '#include <netcons.h>'*)
(*$HPPEMIT '#include <netsetup.h>'*)

(*$HPPEMIT '#include <lmaccess.h>'*)
(*$HPPEMIT '#include <lmalert.h>'*)
(*$HPPEMIT '#include <lmapibuf.h>'*)
(*$HPPEMIT '#include <lmaudit.h>'*)
(*$HPPEMIT '#include <lmat.h>'*)
(*$HPPEMIT '#include <lmbrowsr.h>'*)
(*$HPPEMIT '#include <lmconfig.h>'*)
(*$HPPEMIT '#include <lmchdev.h>'*)
(*$HPPEMIT '#include <lmcons.h>'*)
(*$HPPEMIT '#include <lmdfs.h>'*)
(*$HPPEMIT '#include <lmerr.h>'*)
(*$HPPEMIT '#include <lmerrlog.h>'*)
(*$HPPEMIT '#include <lmjoin.h>'*)
(*$HPPEMIT '#include <lmmsg.h>'*)
(*$HPPEMIT '#include <lmsname.h>'*)
(*$HPPEMIT '#include <lmremutl.h>'*)
(*$HPPEMIT '#include <lmrepl.h>'*)
(*$HPPEMIT '#include <lmserver.h>'*)
(*$HPPEMIT '#include <lmshare.h>'*)
(*$HPPEMIT '#include <lmstats.h>'*)
(*$HPPEMIT '#include <lmsvc.h>'*)
(*$HPPEMIT '#include <lmuse.h>'*)
(*$HPPEMIT '#include <lmuseflg.h>'*)
(*$HPPEMIT '#include <lmwksta.h>'*)

uses
  JwaWinSvc, JwaWinType, JwaWinBase, JwaWinNT;

// Translated from LMERR.H

const

  {$EXTERNALSYM NERR_Success}
  NERR_Success = 0;

  {$EXTERNALSYM NERR_BASE}
  NERR_BASE = 2100;

// **********WARNING ****************
// *The range 2750-2799 has been    *
// *allocated to the IBM LAN Server *
// **********************************

// **********WARNING ****************
// *The range 2900-2999 has been    *
// *reserved for Microsoft OEMs     *
// **********************************

  {$EXTERNALSYM NERR_NetNotStarted}
  NERR_NetNotStarted       = (NERR_BASE+2);
  // The workstation driver is not installed.

  {$EXTERNALSYM NERR_UnknownServer}
  NERR_UnknownServer       = (NERR_BASE+3);
  // The server could not be located.

  {$EXTERNALSYM NERR_ShareMem}
  NERR_ShareMem            = (NERR_BASE+4);
  // An internal error occurred.  The network cannot access a shared memory segment.


  {$EXTERNALSYM NERR_NoNetworkResource}
  NERR_NoNetworkResource   = (NERR_BASE+5);
  // A network resource shortage occurred .

  {$EXTERNALSYM NERR_RemoteOnly}
  NERR_RemoteOnly          = (NERR_BASE+6);
  // This operation is not supported on workstations.

  {$EXTERNALSYM NERR_DevNotRedirected}
  NERR_DevNotRedirected    = (NERR_BASE+7);
    // The device is not connected.

  // NERR_BASE+8 is used for ERROR_CONNECTED_OTHER_PASSWORD

  {$EXTERNALSYM NERR_ServerNotStarted}
  NERR_ServerNotStarted    = (NERR_BASE+14);
  // The Server service is not started.

  {$EXTERNALSYM NERR_ItemNotFound}
  NERR_ItemNotFound        = (NERR_BASE+15);
  // The queue is empty.

  {$EXTERNALSYM NERR_UnknownDevDir}
  NERR_UnknownDevDir       = (NERR_BASE+16);
  // The device or directory does not exist.

  {$EXTERNALSYM NERR_RedirectedPath}
  NERR_RedirectedPath      = (NERR_BASE+17);
  // The operation is invalid on a redirected resource.

  {$EXTERNALSYM NERR_DuplicateShare}
  NERR_DuplicateShare      = (NERR_BASE+18);
  // The name has already been shared.

  {$EXTERNALSYM NERR_NoRoom}
  NERR_NoRoom              = (NERR_BASE+19);
  // The server is currently out of the requested resource.

  {$EXTERNALSYM NERR_TooManyItems}
  NERR_TooManyItems        = (NERR_BASE+21);
  // Requested addition of items exceeds the maximum allowed.

  {$EXTERNALSYM NERR_InvalidMaxUsers}
  NERR_InvalidMaxUsers     = (NERR_BASE+22);
  // The Peer service supports only two simultaneous users.

  {$EXTERNALSYM NERR_BufTooSmall}
  NERR_BufTooSmall         = (NERR_BASE+23);
  // The API return buffer is too small.

  {$EXTERNALSYM NERR_RemoteErr}
  NERR_RemoteErr           = (NERR_BASE+27);
  // A remote API error occurred.

  {$EXTERNALSYM NERR_LanmanIniError}
  NERR_LanmanIniError      = (NERR_BASE+31);
  // An error occurred when opening or reading the configuration file.

  {$EXTERNALSYM NERR_NetworkError}
  NERR_NetworkError        = (NERR_BASE+36);
  // A general network error occurred.

  {$EXTERNALSYM NERR_WkstaInconsistentState}
  NERR_WkstaInconsistentState  = (NERR_BASE+37);
  // The Workstation service is in an inconsistent state. Restart the computer before restarting the Workstation service.

  {$EXTERNALSYM NERR_WkstaNotStarted}
  NERR_WkstaNotStarted     = (NERR_BASE+38);
  // The Workstation service has not been started.

  {$EXTERNALSYM NERR_BrowserNotStarted}
  NERR_BrowserNotStarted   = (NERR_BASE+39);
  // The requested information is not available.

  {$EXTERNALSYM NERR_InternalError}
  NERR_InternalError       = (NERR_BASE+40);
  // An internal Windows NT error occurred.

  {$EXTERNALSYM NERR_BadTransactConfig}
  NERR_BadTransactConfig   = (NERR_BASE+41);
  // The server is not configured for transactions.

  {$EXTERNALSYM NERR_InvalidAPI}
  NERR_InvalidAPI          = (NERR_BASE+42);
  // The requested API is not supported on the remote server.

  {$EXTERNALSYM NERR_BadEventName}
  NERR_BadEventName        = (NERR_BASE+43);
  // The event name is invalid.

  {$EXTERNALSYM NERR_DupNameReboot}
  NERR_DupNameReboot       = (NERR_BASE+44);
  // The computer name already exists on the network. Change it and restart the computer.

// Config API related
// Error codes from BASE+45 to BASE+49

  {$EXTERNALSYM NERR_CfgCompNotFound}
  NERR_CfgCompNotFound     = (NERR_BASE+46);
  // The specified component could not be found in the configuration information.

  {$EXTERNALSYM NERR_CfgParamNotFound}
  NERR_CfgParamNotFound    = (NERR_BASE+47);
  // The specified parameter could not be found in the configuration information.

  {$EXTERNALSYM NERR_LineTooLong}
  NERR_LineTooLong         = (NERR_BASE+49);
  // A line in the configuration file is too long.


// Spooler API related
// Error codes from BASE+50 to BASE+79

  {$EXTERNALSYM NERR_QNotFound}
  NERR_QNotFound           = (NERR_BASE+50);
  // The printer does not exist.

  {$EXTERNALSYM NERR_JobNotFound}
  NERR_JobNotFound         = (NERR_BASE+51);
  // The print job does not exist.

  {$EXTERNALSYM NERR_DestNotFound}
  NERR_DestNotFound        = (NERR_BASE+52);
  // The printer destination cannot be found.

  {$EXTERNALSYM NERR_DestExists}
  NERR_DestExists          = (NERR_BASE+53);
  // The printer destination already exists.

  {$EXTERNALSYM NERR_QExists}
  NERR_QExists             = (NERR_BASE+54);
  // The printer queue already exists.

  {$EXTERNALSYM NERR_QNoRoom}
  NERR_QNoRoom             = (NERR_BASE+55);
  // No more printers can be added.

  {$EXTERNALSYM NERR_JobNoRoom}
  NERR_JobNoRoom           = (NERR_BASE+56);
  // No more print jobs can be added.

  {$EXTERNALSYM NERR_DestNoRoom}
  NERR_DestNoRoom          = (NERR_BASE+57);
  // No more printer destinations can be added.

  {$EXTERNALSYM NERR_DestIdle}
  NERR_DestIdle            = (NERR_BASE+58);
  // This printer destination is idle and cannot accept control operations.

  {$EXTERNALSYM NERR_DestInvalidOp}
  NERR_DestInvalidOp       = (NERR_BASE+59);
  // This printer destination request contains an invalid control function.

  {$EXTERNALSYM NERR_ProcNoRespond}
  NERR_ProcNoRespond       = (NERR_BASE+60);
  // The print processor is not responding.

  {$EXTERNALSYM NERR_SpoolerNotLoaded}
  NERR_SpoolerNotLoaded    = (NERR_BASE+61);
  // The spooler is not running.

  {$EXTERNALSYM NERR_DestInvalidState}
  NERR_DestInvalidState    = (NERR_BASE+62);
  // This operation cannot be performed on the print destination in its current state.

  {$EXTERNALSYM NERR_QInvalidState}
  NERR_QInvalidState       = (NERR_BASE+63);
  // This operation cannot be performed on the printer queue in its current state.

  {$EXTERNALSYM NERR_JobInvalidState}
  NERR_JobInvalidState     = (NERR_BASE+64);
  // This operation cannot be performed on the print job in its current state.

  {$EXTERNALSYM NERR_SpoolNoMemory}
  NERR_SpoolNoMemory       = (NERR_BASE+65);
  // A spooler memory allocation failure occurred.

  {$EXTERNALSYM NERR_DriverNotFound}
  NERR_DriverNotFound      = (NERR_BASE+66);
  // The device driver does not exist.

  {$EXTERNALSYM NERR_DataTypeInvalid}
  NERR_DataTypeInvalid     = (NERR_BASE+67);
  // The data type is not supported by the print processor.

  {$EXTERNALSYM NERR_ProcNotFound}
  NERR_ProcNotFound        = (NERR_BASE+68);
  // The print processor is not installed.

// Service API related
// Error codes from BASE+80 to BASE+99

  {$EXTERNALSYM NERR_ServiceTableLocked}
  NERR_ServiceTableLocked  = (NERR_BASE+80);
  // The service database is locked.

  {$EXTERNALSYM NERR_ServiceTableFull}
  NERR_ServiceTableFull    = (NERR_BASE+81);
  // The service table is full.

  {$EXTERNALSYM NERR_ServiceInstalled}
  NERR_ServiceInstalled    = (NERR_BASE+82);
  // The requested service has already been started.

  {$EXTERNALSYM NERR_ServiceEntryLocked}
  NERR_ServiceEntryLocked  = (NERR_BASE+83);
  // The service does not respond to control actions.

  {$EXTERNALSYM NERR_ServiceNotInstalled}
  NERR_ServiceNotInstalled  = (NERR_BASE+84);
  // The service has not been started.

  {$EXTERNALSYM NERR_BadServiceName}
  NERR_BadServiceName      = (NERR_BASE+85);
  // The service name is invalid.

  {$EXTERNALSYM NERR_ServiceCtlTimeout}
  NERR_ServiceCtlTimeout   = (NERR_BASE+86);
  // The service is not responding to the control function.

  {$EXTERNALSYM NERR_ServiceCtlBusy}
  NERR_ServiceCtlBusy      = (NERR_BASE+87);
  // The service control is busy.

  {$EXTERNALSYM NERR_BadServiceProgName}
  NERR_BadServiceProgName  = (NERR_BASE+88);
  // The configuration file contains an invalid service program name.

  {$EXTERNALSYM NERR_ServiceNotCtrl}
  NERR_ServiceNotCtrl      = (NERR_BASE+89);
  // The service could not be controlled in its present state.

  {$EXTERNALSYM NERR_ServiceKillProc}
  NERR_ServiceKillProc     = (NERR_BASE+90);
  // The service ended abnormally.

  {$EXTERNALSYM NERR_ServiceCtlNotValid}
  NERR_ServiceCtlNotValid  = (NERR_BASE+91);
  // The requested pause or stop is not valid for this service.

  {$EXTERNALSYM NERR_NotInDispatchTbl}
  NERR_NotInDispatchTbl    = (NERR_BASE+92);
  // The service control dispatcher could not find the service name in the dispatch table.

  {$EXTERNALSYM NERR_BadControlRecv}
  NERR_BadControlRecv      = (NERR_BASE+93);
  // The service control dispatcher pipe read failed.

  {$EXTERNALSYM NERR_ServiceNotStarting}
  NERR_ServiceNotStarting  = (NERR_BASE+94);
  // A thread for the new service could not be created.

// Wksta and Logon API related
// Error codes from BASE+100 to BASE+118

  {$EXTERNALSYM NERR_AlreadyLoggedOn}
  NERR_AlreadyLoggedOn     = (NERR_BASE+100);
  // This workstation is already logged on to the local-area network.

  {$EXTERNALSYM NERR_NotLoggedOn}
  NERR_NotLoggedOn         = (NERR_BASE+101);
  // The workstation is not logged on to the local-area network.

  {$EXTERNALSYM NERR_BadUsername}
  NERR_BadUsername         = (NERR_BASE+102);
  // The user name or group name parameter is invalid.

  {$EXTERNALSYM NERR_BadPassword}
  NERR_BadPassword         = (NERR_BASE+103);
  // The password parameter is invalid.

  {$EXTERNALSYM NERR_UnableToAddName_W}
  NERR_UnableToAddName_W   = (NERR_BASE+104);
  // @W The logon processor did not add the message alias.

  {$EXTERNALSYM NERR_UnableToAddName_F}
  NERR_UnableToAddName_F   = (NERR_BASE+105);
  // The logon processor did not add the message alias.

  {$EXTERNALSYM NERR_UnableToDelName_W}
  NERR_UnableToDelName_W   = (NERR_BASE+106);
  // @W The logoff processor did not delete the message alias.

  {$EXTERNALSYM NERR_UnableToDelName_F}
  NERR_UnableToDelName_F   = (NERR_BASE+107);
  // The logoff processor did not delete the message alias.

  {$EXTERNALSYM NERR_LogonsPaused}
  NERR_LogonsPaused        = (NERR_BASE+109);
  // Network logons are paused.

  {$EXTERNALSYM NERR_LogonServerConflict}
  NERR_LogonServerConflict  = (NERR_BASE+110);
  // A centralized logon-server conflict occurred.

  {$EXTERNALSYM NERR_LogonNoUserPath}
  NERR_LogonNoUserPath     = (NERR_BASE+111);
  // The server is configured without a valid user path.

  {$EXTERNALSYM NERR_LogonScriptError}
  NERR_LogonScriptError    = (NERR_BASE+112);
  // An error occurred while loading or running the logon script.

  {$EXTERNALSYM NERR_StandaloneLogon}
  NERR_StandaloneLogon     = (NERR_BASE+114);
  // The logon server was not specified.  Your computer will be logged on as STANDALONE.

  {$EXTERNALSYM NERR_LogonServerNotFound}
  NERR_LogonServerNotFound  = (NERR_BASE+115);
  // The logon server could not be found.

  {$EXTERNALSYM NERR_LogonDomainExists}
  NERR_LogonDomainExists   = (NERR_BASE+116);
  // There is already a logon domain for this computer.

  {$EXTERNALSYM NERR_NonValidatedLogon}
  NERR_NonValidatedLogon   = (NERR_BASE+117);
    // The logon server could not validate the logon.

// ACF API related (access, user, group);
// Error codes from BASE+119 to BASE+149

  {$EXTERNALSYM NERR_ACFNotFound}
  NERR_ACFNotFound         = (NERR_BASE+119);
  // The security database could not be found.

  {$EXTERNALSYM NERR_GroupNotFound}
  NERR_GroupNotFound       = (NERR_BASE+120);
  // The group name could not be found.

  {$EXTERNALSYM NERR_UserNotFound}
  NERR_UserNotFound        = (NERR_BASE+121);
  // The user name could not be found.

  {$EXTERNALSYM NERR_ResourceNotFound}
  NERR_ResourceNotFound    = (NERR_BASE+122);
  // The resource name could not be found.

  {$EXTERNALSYM NERR_GroupExists}
  NERR_GroupExists         = (NERR_BASE+123);
  // The group already exists.

  {$EXTERNALSYM NERR_UserExists}
  NERR_UserExists          = (NERR_BASE+124);
  // The user account already exists.

  {$EXTERNALSYM NERR_ResourceExists}
  NERR_ResourceExists      = (NERR_BASE+125);
  // The resource permission list already exists.

  {$EXTERNALSYM NERR_NotPrimary}
  NERR_NotPrimary          = (NERR_BASE+126);
  // This operation is only allowed on the primary domain controller of the domain.

  {$EXTERNALSYM NERR_ACFNotLoaded}
  NERR_ACFNotLoaded        = (NERR_BASE+127);
  // The security database has not been started.

  {$EXTERNALSYM NERR_ACFNoRoom}
  NERR_ACFNoRoom           = (NERR_BASE+128);
  // There are too many names in the user accounts database.

  {$EXTERNALSYM NERR_ACFFileIOFail}
  NERR_ACFFileIOFail       = (NERR_BASE+129);
  // A disk I/O failure occurred.

  {$EXTERNALSYM NERR_ACFTooManyLists}
  NERR_ACFTooManyLists     = (NERR_BASE+130);
  // The limit of 64 entries per resource was exceeded.

  {$EXTERNALSYM NERR_UserLogon}
  NERR_UserLogon           = (NERR_BASE+131);
  // Deleting a user with a session is not allowed.

  {$EXTERNALSYM NERR_ACFNoParent}
  NERR_ACFNoParent         = (NERR_BASE+132);
  // The parent directory could not be located.

  {$EXTERNALSYM NERR_CanNotGrowSegment}
  NERR_CanNotGrowSegment   = (NERR_BASE+133);
  // Unable to add to the security database session cache segment.

  {$EXTERNALSYM NERR_SpeGroupOp}
  NERR_SpeGroupOp          = (NERR_BASE+134);
  // This operation is not allowed on this special group.

  {$EXTERNALSYM NERR_NotInCache}
  NERR_NotInCache          = (NERR_BASE+135);
  // This user is not cached in user accounts database session cache.

  {$EXTERNALSYM NERR_UserInGroup}
  NERR_UserInGroup         = (NERR_BASE+136);
  // The user already belongs to this group.

  {$EXTERNALSYM NERR_UserNotInGroup}
  NERR_UserNotInGroup      = (NERR_BASE+137);
  // The user does not belong to this group.

  {$EXTERNALSYM NERR_AccountUndefined}
  NERR_AccountUndefined    = (NERR_BASE+138);
  // This user account is undefined.

  {$EXTERNALSYM NERR_AccountExpired}
  NERR_AccountExpired      = (NERR_BASE+139);
  // This user account has expired.

  {$EXTERNALSYM NERR_InvalidWorkstation}
  NERR_InvalidWorkstation  = (NERR_BASE+140);
  // The user is not allowed to log on from this workstation.

  {$EXTERNALSYM NERR_InvalidLogonHours}
  NERR_InvalidLogonHours   = (NERR_BASE+141);
  // The user is not allowed to log on at this time.

  {$EXTERNALSYM NERR_PasswordExpired}
  NERR_PasswordExpired     = (NERR_BASE+142);
  // The password of this user has expired.

  {$EXTERNALSYM NERR_PasswordCantChange}
  NERR_PasswordCantChange  = (NERR_BASE+143);
  // The password of this user cannot change.

  {$EXTERNALSYM NERR_PasswordHistConflict}
  NERR_PasswordHistConflict  = (NERR_BASE+144);
  // This password cannot be used now.

  {$EXTERNALSYM NERR_PasswordTooShort}
  NERR_PasswordTooShort    = (NERR_BASE+145);
  // The password is shorter than required.

  {$EXTERNALSYM NERR_PasswordTooRecent}
  NERR_PasswordTooRecent   = (NERR_BASE+146);
  // The password of this user is too recent to change.

  {$EXTERNALSYM NERR_InvalidDatabase}
  NERR_InvalidDatabase     = (NERR_BASE+147);
  // The security database is corrupted.

  {$EXTERNALSYM NERR_DatabaseUpToDate}
  NERR_DatabaseUpToDate    = (NERR_BASE+148);
  // No updates are necessary to this replicant network/local security database.

  {$EXTERNALSYM NERR_SyncRequired}
  NERR_SyncRequired        = (NERR_BASE+149);
    // This replicant database is outdated; synchronization is required.

// Use API related
// Error codes from BASE+150 to BASE+169

  {$EXTERNALSYM NERR_UseNotFound}
  NERR_UseNotFound         = (NERR_BASE+150);
  // The network connection could not be found.

  {$EXTERNALSYM NERR_BadAsgType}
  NERR_BadAsgType          = (NERR_BASE+151);
  // This asg_type is invalid.

  {$EXTERNALSYM NERR_DeviceIsShared}
  NERR_DeviceIsShared      = (NERR_BASE+152);
  // This device is currently being shared.

// Message Server related
// Error codes BASE+170 to BASE+209

  {$EXTERNALSYM NERR_NoComputerName}
  NERR_NoComputerName      = (NERR_BASE+170);
  // The computer name could not be added as a message alias.  The name may already exist on the network.

  {$EXTERNALSYM NERR_MsgAlreadyStarted}
  NERR_MsgAlreadyStarted   = (NERR_BASE+171);
  // The Messenger service is already started.

  {$EXTERNALSYM NERR_MsgInitFailed}
  NERR_MsgInitFailed       = (NERR_BASE+172);
  // The Messenger service failed to start.

  {$EXTERNALSYM NERR_NameNotFound}
  NERR_NameNotFound        = (NERR_BASE+173);
  // The message alias could not be found on the network.

  {$EXTERNALSYM NERR_AlreadyForwarded}
  NERR_AlreadyForwarded    = (NERR_BASE+174);
  // This message alias has already been forwarded.

  {$EXTERNALSYM NERR_AddForwarded}
  NERR_AddForwarded        = (NERR_BASE+175);
  // This message alias has been added but is still forwarded.

  {$EXTERNALSYM NERR_AlreadyExists}
  NERR_AlreadyExists       = (NERR_BASE+176);
  // This message alias already exists locally.

  {$EXTERNALSYM NERR_TooManyNames}
  NERR_TooManyNames        = (NERR_BASE+177);
  // The maximum number of added message aliases has been exceeded.

  {$EXTERNALSYM NERR_DelComputerName}
  NERR_DelComputerName     = (NERR_BASE+178);
  // The computer name could not be deleted.

  {$EXTERNALSYM NERR_LocalForward}
  NERR_LocalForward        = (NERR_BASE+179);
  // Messages cannot be forwarded back to the same workstation.

  {$EXTERNALSYM NERR_GrpMsgProcessor}
  NERR_GrpMsgProcessor     = (NERR_BASE+180);
  // An error occurred in the domain message processor.

  {$EXTERNALSYM NERR_PausedRemote}
  NERR_PausedRemote        = (NERR_BASE+181);
  // The message was sent, but the recipient has paused the Messenger service.

  {$EXTERNALSYM NERR_BadReceive}
  NERR_BadReceive          = (NERR_BASE+182);
  // The message was sent but not received.

  {$EXTERNALSYM NERR_NameInUse}
  NERR_NameInUse           = (NERR_BASE+183);
  // The message alias is currently in use. Try again later.

  {$EXTERNALSYM NERR_MsgNotStarted}
  NERR_MsgNotStarted       = (NERR_BASE+184);
  // The Messenger service has not been started.

  {$EXTERNALSYM NERR_NotLocalName}
  NERR_NotLocalName        = (NERR_BASE+185);
  // The name is not on the local computer.

  {$EXTERNALSYM NERR_NoForwardName}
  NERR_NoForwardName       = (NERR_BASE+186);
  // The forwarded message alias could not be found on the network.

  {$EXTERNALSYM NERR_RemoteFull}
  NERR_RemoteFull          = (NERR_BASE+187);
  // The message alias table on the remote station is full.

  {$EXTERNALSYM NERR_NameNotForwarded}
  NERR_NameNotForwarded    = (NERR_BASE+188);
  // Messages for this alias are not currently being forwarded.

  {$EXTERNALSYM NERR_TruncatedBroadcast}
  NERR_TruncatedBroadcast  = (NERR_BASE+189);
  // The broadcast message was truncated.

  {$EXTERNALSYM NERR_InvalidDevice}
  NERR_InvalidDevice       = (NERR_BASE+194);
  // This is an invalid device name.

  {$EXTERNALSYM NERR_WriteFault}
  NERR_WriteFault          = (NERR_BASE+195);
  // A write fault occurred.

  {$EXTERNALSYM NERR_DuplicateName}
  NERR_DuplicateName       = (NERR_BASE+197);
  // A duplicate message alias exists on the network.

  {$EXTERNALSYM NERR_DeleteLater}
  NERR_DeleteLater         = (NERR_BASE+198);
  // @W This message alias will be deleted later.

  {$EXTERNALSYM NERR_IncompleteDel}
  NERR_IncompleteDel       = (NERR_BASE+199);
  // The message alias was not successfully deleted from all networks.

  {$EXTERNALSYM NERR_MultipleNets}
  NERR_MultipleNets        = (NERR_BASE+200);
  // This operation is not supported on computers with multiple networks.
  
// Server API related
// Error codes BASE+210 to BASE+229

  {$EXTERNALSYM NERR_NetNameNotFound}
  NERR_NetNameNotFound     = (NERR_BASE+210);
  // This shared resource does not exist.

  {$EXTERNALSYM NERR_DeviceNotShared}
  NERR_DeviceNotShared     = (NERR_BASE+211);
  // This device is not shared.

  {$EXTERNALSYM NERR_ClientNameNotFound}
  NERR_ClientNameNotFound  = (NERR_BASE+212);
  // A session does not exist with that computer name.

  {$EXTERNALSYM NERR_FileIdNotFound}
  NERR_FileIdNotFound      = (NERR_BASE+214);
  // There is not an open file with that identification number.

  {$EXTERNALSYM NERR_ExecFailure}
  NERR_ExecFailure         = (NERR_BASE+215);
  // A failure occurred when executing a remote administration command.

  {$EXTERNALSYM NERR_TmpFile}
  NERR_TmpFile             = (NERR_BASE+216);
  // A failure occurred when opening a remote temporary file.

  {$EXTERNALSYM NERR_TooMuchData}
  NERR_TooMuchData         = (NERR_BASE+217);
  // The data returned from a remote administration command has been truncated to 64K.

  {$EXTERNALSYM NERR_DeviceShareConflict}
  NERR_DeviceShareConflict  = (NERR_BASE+218);
  // This device cannot be shared as both a spooled and a non-spooled resource.

  {$EXTERNALSYM NERR_BrowserTableIncomplete}
  NERR_BrowserTableIncomplete  = (NERR_BASE+219);
   // The information in the list of servers may be incorrect.

  {$EXTERNALSYM NERR_NotLocalDomain}
  NERR_NotLocalDomain      = (NERR_BASE+220);
  // The computer is not active in this domain.

  {$EXTERNALSYM NERR_IsDfsShare}
  NERR_IsDfsShare          = (NERR_BASE+221);
  // The share must be removed from the Distributed File System before it can be deleted.

// CharDev API related
// Error codes BASE+230 to BASE+249

  {$EXTERNALSYM NERR_DevInvalidOpCode}
  NERR_DevInvalidOpCode    = (NERR_BASE+231);
  // The operation is invalid for this device.

  {$EXTERNALSYM NERR_DevNotFound}
  NERR_DevNotFound         = (NERR_BASE+232);
  // This device cannot be shared.

  {$EXTERNALSYM NERR_DevNotOpen}
  NERR_DevNotOpen          = (NERR_BASE+233);
  // This device was not open.

  {$EXTERNALSYM NERR_BadQueueDevString}
  NERR_BadQueueDevString   = (NERR_BASE+234);
  // This device name list is invalid.

  {$EXTERNALSYM NERR_BadQueuePriority}
  NERR_BadQueuePriority    = (NERR_BASE+235);
  // The queue priority is invalid.

  {$EXTERNALSYM NERR_NoCommDevs}
  NERR_NoCommDevs          = (NERR_BASE+237);
  // There are no shared communication devices.

  {$EXTERNALSYM NERR_QueueNotFound}
  NERR_QueueNotFound       = (NERR_BASE+238);
  // The queue you specified does not exist.

  {$EXTERNALSYM NERR_BadDevString}
  NERR_BadDevString        = (NERR_BASE+240);
  // This list of devices is invalid.

  {$EXTERNALSYM NERR_BadDev}
  NERR_BadDev              = (NERR_BASE+241);
  // The requested device is invalid.

  {$EXTERNALSYM NERR_InUseBySpooler}
  NERR_InUseBySpooler      = (NERR_BASE+242);
  // This device is already in use by the spooler.

  {$EXTERNALSYM NERR_CommDevInUse}
  NERR_CommDevInUse        = (NERR_BASE+243);
  // This device is already in use as a communication device.

// NetICanonicalize and NetIType and NetIMakeLMFileName
// NetIListCanon and NetINameCheck
// Error codes BASE+250 to BASE+269

  {$EXTERNALSYM NERR_InvalidComputer}
  NERR_InvalidComputer    = (NERR_BASE+251);
  // This computer name is invalid.

  {$EXTERNALSYM NERR_MaxLenExceeded}
  NERR_MaxLenExceeded     = (NERR_BASE+254);
  // The string and prefix specified are too long.

  {$EXTERNALSYM NERR_BadComponent}
  NERR_BadComponent       = (NERR_BASE+256);
  // This path component is invalid.

  {$EXTERNALSYM NERR_CantType}
  NERR_CantType           = (NERR_BASE+257);
  // Could not determine the type of input.

  {$EXTERNALSYM NERR_TooManyEntries}
  NERR_TooManyEntries     = (NERR_BASE+262);
  // The buffer for types is not big enough.

// NetProfile
// Error codes BASE+270 to BASE+276

  {$EXTERNALSYM NERR_ProfileFileTooBig}
  NERR_ProfileFileTooBig   = (NERR_BASE+270);
  // Profile files cannot exceed 64K.

  {$EXTERNALSYM NERR_ProfileOffset}
  NERR_ProfileOffset       = (NERR_BASE+271);
  // The start offset is out of range.

  {$EXTERNALSYM NERR_ProfileCleanup}
  NERR_ProfileCleanup      = (NERR_BASE+272);
  // The system cannot delete current connections to network resources.

  {$EXTERNALSYM NERR_ProfileUnknownCmd}
  NERR_ProfileUnknownCmd   = (NERR_BASE+273);
  // The system was unable to parse the command line in this file.

  {$EXTERNALSYM NERR_ProfileLoadErr}
  NERR_ProfileLoadErr      = (NERR_BASE+274);
  // An error occurred while loading the profile file.

  {$EXTERNALSYM NERR_ProfileSaveErr}
  NERR_ProfileSaveErr      = (NERR_BASE+275);
  // @W Errors occurred while saving the profile file.  The profile was partially saved.

// NetAudit and NetErrorLog
// Error codes BASE+277 to BASE+279

  {$EXTERNALSYM NERR_LogOverflow}
  NERR_LogOverflow            = (NERR_BASE+277);
  // Log file %1 is full.

  {$EXTERNALSYM NERR_LogFileChanged}
  NERR_LogFileChanged         = (NERR_BASE+278);
  // This log file has changed between reads.

  {$EXTERNALSYM NERR_LogFileCorrupt}
  NERR_LogFileCorrupt         = (NERR_BASE+279);
  // Log file %1 is corrupt.

// NetRemote
// Error codes BASE+280 to BASE+299

  {$EXTERNALSYM NERR_SourceIsDir}
  NERR_SourceIsDir    = (NERR_BASE+280);
  // The source path cannot be a directory.

  {$EXTERNALSYM NERR_BadSource}
  NERR_BadSource      = (NERR_BASE+281);
  // The source path is illegal.

  {$EXTERNALSYM NERR_BadDest}
  NERR_BadDest        = (NERR_BASE+282);
  // The destination path is illegal.

  {$EXTERNALSYM NERR_DifferentServers}
  NERR_DifferentServers    = (NERR_BASE+283);
  // The source and destination paths are on different servers.

  {$EXTERNALSYM NERR_RunSrvPaused}
  NERR_RunSrvPaused        = (NERR_BASE+285);
  // The Run server you requested is paused.

  {$EXTERNALSYM NERR_ErrCommRunSrv}
  NERR_ErrCommRunSrv       = (NERR_BASE+289);
  // An error occurred when communicating with a Run server.

  {$EXTERNALSYM NERR_ErrorExecingGhost}
  NERR_ErrorExecingGhost   = (NERR_BASE+291);
  // An error occurred when starting a background process.

  {$EXTERNALSYM NERR_ShareNotFound}
  NERR_ShareNotFound       = (NERR_BASE+292);
  // The shared resource you are connected to could not be found.

// NetWksta.sys (redir); returned error codes.
// NERR_BASE + (300-329);

  {$EXTERNALSYM NERR_InvalidLana}
  NERR_InvalidLana         = (NERR_BASE+300);
  // The LAN adapter number is invalid.

  {$EXTERNALSYM NERR_OpenFiles}
  NERR_OpenFiles           = (NERR_BASE+301);
  // There are open files on the connection.

  {$EXTERNALSYM NERR_ActiveConns}
  NERR_ActiveConns         = (NERR_BASE+302);
  // Active connections still exist.

  {$EXTERNALSYM NERR_BadPasswordCore}
  NERR_BadPasswordCore     = (NERR_BASE+303);
  // This share name or password is invalid.

  {$EXTERNALSYM NERR_DevInUse}
  NERR_DevInUse            = (NERR_BASE+304);
  // The device is being accessed by an active process.

  {$EXTERNALSYM NERR_LocalDrive}
  NERR_LocalDrive          = (NERR_BASE+305);
  // The drive letter is in use locally.

//  Alert error codes.
//  NERR_BASE + (330-339);

  {$EXTERNALSYM NERR_AlertExists}
  NERR_AlertExists         = (NERR_BASE+330);
  // The specified client is already registered for the specified event.

  {$EXTERNALSYM NERR_TooManyAlerts}
  NERR_TooManyAlerts       = (NERR_BASE+331);
  // The alert table is full.

  {$EXTERNALSYM NERR_NoSuchAlert}
  NERR_NoSuchAlert         = (NERR_BASE+332);
  // An invalid or nonexistent alert name was raised.

  {$EXTERNALSYM NERR_BadRecipient}
  NERR_BadRecipient        = (NERR_BASE+333);
  // The alert recipient is invalid.

  {$EXTERNALSYM NERR_AcctLimitExceeded}
  NERR_AcctLimitExceeded   = (NERR_BASE+334);
  // A user's session with this server has been deleted because the user's logon hours are no longer valid.

// Additional Error and Audit log codes.
// NERR_BASE +(340-343)

  {$EXTERNALSYM NERR_InvalidLogSeek}
  NERR_InvalidLogSeek      = (NERR_BASE+340);
  // The log file does not contain the requested record number.

// Additional UAS and NETLOGON codes
// NERR_BASE +(350-359)

  {$EXTERNALSYM NERR_BadUasConfig}
  NERR_BadUasConfig        = (NERR_BASE+350);
  // The user accounts database is not configured correctly.

  {$EXTERNALSYM NERR_InvalidUASOp}
  NERR_InvalidUASOp        = (NERR_BASE+351);
  // This operation is not permitted when the Netlogon service is running.

  {$EXTERNALSYM NERR_LastAdmin}
  NERR_LastAdmin           = (NERR_BASE+352);
  // This operation is not allowed on the last administrative account.

  {$EXTERNALSYM NERR_DCNotFound}
  NERR_DCNotFound          = (NERR_BASE+353);
  // Could not find domain controller for this domain.

  {$EXTERNALSYM NERR_LogonTrackingError}
  NERR_LogonTrackingError  = (NERR_BASE+354);
  // Could not set logon information for this user.

  {$EXTERNALSYM NERR_NetlogonNotStarted}
  NERR_NetlogonNotStarted  = (NERR_BASE+355);
  // The Netlogon service has not been started.

  {$EXTERNALSYM NERR_CanNotGrowUASFile}
  NERR_CanNotGrowUASFile   = (NERR_BASE+356);
  // Unable to add to the user accounts database.

  {$EXTERNALSYM NERR_TimeDiffAtDC}
  NERR_TimeDiffAtDC        = (NERR_BASE+357);
  // This server's clock is not synchronized with the primary domain controller's clock.

  {$EXTERNALSYM NERR_PasswordMismatch}
  NERR_PasswordMismatch    = (NERR_BASE+358);
  // A password mismatch has been detected.

// Server Integration error codes.
// NERR_BASE +(360-369)

  {$EXTERNALSYM NERR_NoSuchServer}
  NERR_NoSuchServer        = (NERR_BASE+360);
  // The server identification does not specify a valid server.

  {$EXTERNALSYM NERR_NoSuchSession}
  NERR_NoSuchSession       = (NERR_BASE+361);
  // The session identification does not specify a valid session.

  {$EXTERNALSYM NERR_NoSuchConnection}
  NERR_NoSuchConnection    = (NERR_BASE+362);
  // The connection identification does not specify a valid connection.

  {$EXTERNALSYM NERR_TooManyServers}
  NERR_TooManyServers      = (NERR_BASE+363);
  // There is no space for another entry in the table of available servers.

  {$EXTERNALSYM NERR_TooManySessions}
  NERR_TooManySessions     = (NERR_BASE+364);
  // The server has reached the maximum number of sessions it supports.

  {$EXTERNALSYM NERR_TooManyConnections}
  NERR_TooManyConnections  = (NERR_BASE+365);
  // The server has reached the maximum number of connections it supports.

  {$EXTERNALSYM NERR_TooManyFiles}
  NERR_TooManyFiles        = (NERR_BASE+366);
  // The server cannot open more files because it has reached its maximum number.

  {$EXTERNALSYM NERR_NoAlternateServers}
  NERR_NoAlternateServers  = (NERR_BASE+367);
  // There are no alternate servers registered on this server.

  {$EXTERNALSYM NERR_TryDownLevel}
  NERR_TryDownLevel        = (NERR_BASE+370);
  // Try down-level (remote admin protocol); version of API instead.

// UPS error codes.
// NERR_BASE + (380-384);

  {$EXTERNALSYM NERR_UPSDriverNotStarted}
  NERR_UPSDriverNotStarted     = (NERR_BASE+380);
  // The UPS driver could not be accessed by the UPS service.

  {$EXTERNALSYM NERR_UPSInvalidConfig}
  NERR_UPSInvalidConfig        = (NERR_BASE+381);
  // The UPS service is not configured correctly.

  {$EXTERNALSYM NERR_UPSInvalidCommPort}
  NERR_UPSInvalidCommPort      = (NERR_BASE+382);
  // The UPS service could not access the specified Comm Port.

  {$EXTERNALSYM NERR_UPSSignalAsserted}
  NERR_UPSSignalAsserted       = (NERR_BASE+383);
  // The UPS indicated a line fail or low battery situation. Service not started.

  {$EXTERNALSYM NERR_UPSShutdownFailed}
  NERR_UPSShutdownFailed       = (NERR_BASE+384);
  // The UPS service failed to perform a system shut down.

// Remoteboot error codes.
// NERR_BASE + (400-419);
// Error codes 400 - 405 are used by RPLBOOT.SYS.
// Error codes 403, 407 - 416 are used by RPLLOADR.COM,
// Error code 417 is the alerter message of REMOTEBOOT (RPLSERVR.EXE);.
// Error code 418 is for when REMOTEBOOT can't start
// Error code 419 is for a disallowed 2nd rpl connection

  {$EXTERNALSYM NERR_BadDosRetCode}
  NERR_BadDosRetCode       = (NERR_BASE+400);
  // The program below returned an MS-DOS error code:

  {$EXTERNALSYM NERR_ProgNeedsExtraMem}
  NERR_ProgNeedsExtraMem   = (NERR_BASE+401);
  // The program below needs more memory:

  {$EXTERNALSYM NERR_BadDosFunction}
  NERR_BadDosFunction      = (NERR_BASE+402);
  // The program below called an unsupported MS-DOS function:

  {$EXTERNALSYM NERR_RemoteBootFailed}
  NERR_RemoteBootFailed    = (NERR_BASE+403);
  // The workstation failed to boot.

  {$EXTERNALSYM NERR_BadFileCheckSum}
  NERR_BadFileCheckSum     = (NERR_BASE+404);
  // The file below is corrupt.

  {$EXTERNALSYM NERR_NoRplBootSystem}
  NERR_NoRplBootSystem     = (NERR_BASE+405);
  // No loader is specified in the boot-block definition file.

  {$EXTERNALSYM NERR_RplLoadrNetBiosErr}
  NERR_RplLoadrNetBiosErr  = (NERR_BASE+406);
  // NetBIOS returned an error: The NCB and SMB are dumped above.

  {$EXTERNALSYM NERR_RplLoadrDiskErr}
  NERR_RplLoadrDiskErr     = (NERR_BASE+407);
  // A disk I/O error occurred.

  {$EXTERNALSYM NERR_ImageParamErr}
  NERR_ImageParamErr       = (NERR_BASE+408);
  // Image parameter substitution failed.

  {$EXTERNALSYM NERR_TooManyImageParams}
  NERR_TooManyImageParams  = (NERR_BASE+409);
  // Too many image parameters cross disk sector boundaries.

  {$EXTERNALSYM NERR_NonDosFloppyUsed}
  NERR_NonDosFloppyUsed    = (NERR_BASE+410);
  // The image was not generated from an MS-DOS diskette formatted with /S.

  {$EXTERNALSYM NERR_RplBootRestart}
  NERR_RplBootRestart      = (NERR_BASE+411);
  // Remote boot will be restarted later.

  {$EXTERNALSYM NERR_RplSrvrCallFailed}
  NERR_RplSrvrCallFailed   = (NERR_BASE+412);
  // The call to the Remoteboot server failed.

  {$EXTERNALSYM NERR_CantConnectRplSrvr}
  NERR_CantConnectRplSrvr  = (NERR_BASE+413);
  // Cannot connect to the Remoteboot server.

  {$EXTERNALSYM NERR_CantOpenImageFile}
  NERR_CantOpenImageFile   = (NERR_BASE+414);
  // Cannot open image file on the Remoteboot server.

  {$EXTERNALSYM NERR_CallingRplSrvr}
  NERR_CallingRplSrvr      = (NERR_BASE+415);
  // Connecting to the Remoteboot server...

  {$EXTERNALSYM NERR_StartingRplBoot}
  NERR_StartingRplBoot     = (NERR_BASE+416);
  // Connecting to the Remoteboot server...

  {$EXTERNALSYM NERR_RplBootServiceTerm}
  NERR_RplBootServiceTerm  = (NERR_BASE+417);
  // Remote boot service was stopped; check the error log for the cause of the problem.

  {$EXTERNALSYM NERR_RplBootStartFailed}
  NERR_RplBootStartFailed  = (NERR_BASE+418);
  // Remote boot startup failed; check the error log for the cause of the problem.

  {$EXTERNALSYM NERR_RPL_CONNECTED}
  NERR_RPL_CONNECTED       = (NERR_BASE+419);
  // A second connection to a Remoteboot resource is not allowed.

// FTADMIN API error codes
// NERR_BASE + (425-434)
// (Currently not used in NT);

// Browser service API error codes
// NERR_BASE + (450-475)

  {$EXTERNALSYM NERR_BrowserConfiguredToNotRun}
  NERR_BrowserConfiguredToNotRun      = (NERR_BASE+450);
  // The browser service was configured with MaintainServerList=No.

// Additional Remoteboot error codes.
// NERR_BASE + (510-550);

  {$EXTERNALSYM NERR_RplNoAdaptersStarted}
  NERR_RplNoAdaptersStarted           = (NERR_BASE+510);
  //Service failed to start since none of the network adapters started with this service.

  {$EXTERNALSYM NERR_RplBadRegistry}
  NERR_RplBadRegistry                 = (NERR_BASE+511);
  //Service failed to start due to bad startup information in the registry.

  {$EXTERNALSYM NERR_RplBadDatabase}
  NERR_RplBadDatabase                 = (NERR_BASE+512);
  //Service failed to start because its database is absent or corrupt.

  {$EXTERNALSYM NERR_RplRplfilesShare}
  NERR_RplRplfilesShare               = (NERR_BASE+513);
  //Service failed to start because RPLFILES share is absent.

  {$EXTERNALSYM NERR_RplNotRplServer}
  NERR_RplNotRplServer                = (NERR_BASE+514);
  //Service failed to start because RPLUSER group is absent.

  {$EXTERNALSYM NERR_RplCannotEnum}
  NERR_RplCannotEnum                  = (NERR_BASE+515);
  //Cannot enumerate service records.

  {$EXTERNALSYM NERR_RplWkstaInfoCorrupted}
  NERR_RplWkstaInfoCorrupted          = (NERR_BASE+516);
  //Workstation record information has been corrupted.

  {$EXTERNALSYM NERR_RplWkstaNotFound}
  NERR_RplWkstaNotFound               = (NERR_BASE+517);
  //Workstation record was not found.

  {$EXTERNALSYM NERR_RplWkstaNameUnavailable}
  NERR_RplWkstaNameUnavailable        = (NERR_BASE+518);
  //Workstation name is in use by some other workstation.

  {$EXTERNALSYM NERR_RplProfileInfoCorrupted}
  NERR_RplProfileInfoCorrupted        = (NERR_BASE+519);
  //Profile record information has been corrupted.

  {$EXTERNALSYM NERR_RplProfileNotFound}
  NERR_RplProfileNotFound             = (NERR_BASE+520);
  //Profile record was not found.

  {$EXTERNALSYM NERR_RplProfileNameUnavailable}
  NERR_RplProfileNameUnavailable      = (NERR_BASE+521);
  //Profile name is in use by some other profile.

  {$EXTERNALSYM NERR_RplProfileNotEmpty}
  NERR_RplProfileNotEmpty             = (NERR_BASE+522);
  //There are workstations using this profile.

  {$EXTERNALSYM NERR_RplConfigInfoCorrupted}
  NERR_RplConfigInfoCorrupted         = (NERR_BASE+523);
  //Configuration record information has been corrupted.

  {$EXTERNALSYM NERR_RplConfigNotFound}
  NERR_RplConfigNotFound              = (NERR_BASE+524);
  //Configuration record was not found.

  {$EXTERNALSYM NERR_RplAdapterInfoCorrupted}
  NERR_RplAdapterInfoCorrupted        = (NERR_BASE+525);
  //Adapter id record information has been corrupted.

  {$EXTERNALSYM NERR_RplInternal}
  NERR_RplInternal                    = (NERR_BASE+526);
  //An internal service error has occurred.

  {$EXTERNALSYM NERR_RplVendorInfoCorrupted}
  NERR_RplVendorInfoCorrupted         = (NERR_BASE+527);
  //Vendor id record information has been corrupted.

  {$EXTERNALSYM NERR_RplBootInfoCorrupted}
  NERR_RplBootInfoCorrupted           = (NERR_BASE+528);
  //Boot block record information has been corrupted.

  {$EXTERNALSYM NERR_RplWkstaNeedsUserAcct}
  NERR_RplWkstaNeedsUserAcct          = (NERR_BASE+529);
  //The user account for this workstation record is missing.

  {$EXTERNALSYM NERR_RplNeedsRPLUSERAcct}
  NERR_RplNeedsRPLUSERAcct            = (NERR_BASE+530);
  //The RPLUSER local group could not be found.

  {$EXTERNALSYM NERR_RplBootNotFound}
  NERR_RplBootNotFound                = (NERR_BASE+531);
  //Boot block record was not found.

  {$EXTERNALSYM NERR_RplIncompatibleProfile}
  NERR_RplIncompatibleProfile         = (NERR_BASE+532);
  //Chosen profile is incompatible with this workstation.

  {$EXTERNALSYM NERR_RplAdapterNameUnavailable}
  NERR_RplAdapterNameUnavailable      = (NERR_BASE+533);
  //Chosen network adapter id is in use by some other workstation.

  {$EXTERNALSYM NERR_RplConfigNotEmpty}
  NERR_RplConfigNotEmpty              = (NERR_BASE+534);
  //There are profiles using this configuration.

  {$EXTERNALSYM NERR_RplBootInUse}
  NERR_RplBootInUse                   = (NERR_BASE+535);
  //There are workstations, profiles or configurations using this boot block.

  {$EXTERNALSYM NERR_RplBackupDatabase}
  NERR_RplBackupDatabase              = (NERR_BASE+536);
  //Service failed to backup Remoteboot database.

  {$EXTERNALSYM NERR_RplAdapterNotFound}
  NERR_RplAdapterNotFound             = (NERR_BASE+537);
  //Adapter record was not found.

  {$EXTERNALSYM NERR_RplVendorNotFound}
  NERR_RplVendorNotFound              = (NERR_BASE+538);
  //Vendor record was not found.

  {$EXTERNALSYM NERR_RplVendorNameUnavailable}
  NERR_RplVendorNameUnavailable       = (NERR_BASE+539);
  //Vendor name is in use by some other vendor record.

  {$EXTERNALSYM NERR_RplBootNameUnavailable}
  NERR_RplBootNameUnavailable         = (NERR_BASE+540);
  //(boot name, vendor id); is in use by some other boot block record.

  {$EXTERNALSYM NERR_RplConfigNameUnavailable}
  NERR_RplConfigNameUnavailable       = (NERR_BASE+541);
  //Configuration name is in use by some other configuration.


// **INTERNAL_ONLY**

// Dfs API error codes.
// NERR_BASE + (560-590);

  {$EXTERNALSYM NERR_DfsInternalCorruption}
  NERR_DfsInternalCorruption          = (NERR_BASE+560);
  //The internal database maintained by the Dfs service is corrupt

  {$EXTERNALSYM NERR_DfsVolumeDataCorrupt}
  NERR_DfsVolumeDataCorrupt           = (NERR_BASE+561);
  //One of the records in the internal Dfs database is corrupt

  {$EXTERNALSYM NERR_DfsNoSuchVolume}
  NERR_DfsNoSuchVolume                = (NERR_BASE+562);
  //There is no volume whose entry path matches the input Entry Path

  {$EXTERNALSYM NERR_DfsVolumeAlreadyExists}
  NERR_DfsVolumeAlreadyExists         = (NERR_BASE+563);
  //A volume with the given name already exists

  {$EXTERNALSYM NERR_DfsAlreadyShared}
  NERR_DfsAlreadyShared               = (NERR_BASE+564);
  //The server share specified is already shared in the Dfs

  {$EXTERNALSYM NERR_DfsNoSuchShare}
  NERR_DfsNoSuchShare                 = (NERR_BASE+565);
  //The indicated server share does not support the indicated Dfs volume

  {$EXTERNALSYM NERR_DfsNotALeafVolume}
  NERR_DfsNotALeafVolume              = (NERR_BASE+566);
  //The operation is not valid on a non-leaf volume

  {$EXTERNALSYM NERR_DfsLeafVolume}
  NERR_DfsLeafVolume                  = (NERR_BASE+567);
  //The operation is not valid on a leaf volume

  {$EXTERNALSYM NERR_DfsVolumeHasMultipleServers}
  NERR_DfsVolumeHasMultipleServers    = (NERR_BASE+568);
  //The operation is ambiguous because the volume has multiple servers

  {$EXTERNALSYM NERR_DfsCantCreateJunctionPoint}
  NERR_DfsCantCreateJunctionPoint     = (NERR_BASE+569);
  //Unable to create a junction point

  {$EXTERNALSYM NERR_DfsServerNotDfsAware}
  NERR_DfsServerNotDfsAware           = (NERR_BASE+570);
  //The server is not Dfs Aware

  {$EXTERNALSYM NERR_DfsBadRenamePath}
  NERR_DfsBadRenamePath               = (NERR_BASE+571);
  //The specified rename target path is invalid

  {$EXTERNALSYM NERR_DfsVolumeIsOffline}
  NERR_DfsVolumeIsOffline             = (NERR_BASE+572);
  //The specified Dfs volume is offline

  {$EXTERNALSYM NERR_DfsNoSuchServer}
  NERR_DfsNoSuchServer                = (NERR_BASE+573);
  //The specified server is not a server for this volume

  {$EXTERNALSYM NERR_DfsCyclicalName}
  NERR_DfsCyclicalName                = (NERR_BASE+574);
  //A cycle in the Dfs name was detected

  {$EXTERNALSYM NERR_DfsNotSupportedInServerDfs}
  NERR_DfsNotSupportedInServerDfs     = (NERR_BASE+575);
  //The operation is not supported on a server-based Dfs

  {$EXTERNALSYM NERR_DfsDuplicateService}
  NERR_DfsDuplicateService            = (NERR_BASE+576);
  //This volume is already supported by the specified server-share

  {$EXTERNALSYM NERR_DfsCantRemoveLastServerShare}
  NERR_DfsCantRemoveLastServerShare   = (NERR_BASE+577);
  //Can't remove the last server-share supporting this volume

  {$EXTERNALSYM NERR_DfsVolumeIsInterDfs}
  NERR_DfsVolumeIsInterDfs            = (NERR_BASE+578);
  //The operation is not supported for an Inter-Dfs volume

  {$EXTERNALSYM NERR_DfsInconsistent}
  NERR_DfsInconsistent                = (NERR_BASE+579);
  //The internal state of the Dfs Service has become inconsistent

  {$EXTERNALSYM NERR_DfsServerUpgraded}
  NERR_DfsServerUpgraded              = (NERR_BASE+580);
  //The Dfs Service has been installed on the specified server

  {$EXTERNALSYM NERR_DfsDataIsIdentical}
  NERR_DfsDataIsIdentical             = (NERR_BASE+581);
  //The Dfs data being reconciled is identical

  {$EXTERNALSYM NERR_DfsCantRemoveDfsRoot}
  NERR_DfsCantRemoveDfsRoot           = (NERR_BASE+582);
  //The Dfs root volume cannot be deleted - Uninstall Dfs if required

  {$EXTERNALSYM NERR_DfsChildOrParentInDfs}
  NERR_DfsChildOrParentInDfs          = (NERR_BASE+583);
  //A child or parent directory of the share is already in a Dfs

  {$EXTERNALSYM NERR_DfsInternalError}
  NERR_DfsInternalError               = (NERR_BASE+590);
  //Dfs internal error

// Net setup error codes.
// NERR_BASE + (591-600);

  {$EXTERNALSYM NERR_SetupAlreadyJoined}
  NERR_SetupAlreadyJoined             = (NERR_BASE+591);
  //This machine is already joined to a domain.

  {$EXTERNALSYM NERR_SetupNotJoined}
  NERR_SetupNotJoined                 = (NERR_BASE+592);
  //This machine is not currently joined to a domain.

  {$EXTERNALSYM NERR_SetupDomainController}
  NERR_SetupDomainController          = (NERR_BASE+593);
  //This machine is a domain controller and cannot be unjoined from a domain.

  {$EXTERNALSYM NERR_DefaultJoinRequired}
  NERR_DefaultJoinRequired            = (NERR_BASE+594);
  //*The destination domain controller does not support creating machine accounts in OUs.

  {$EXTERNALSYM NERR_InvalidWorkgroupName}
  NERR_InvalidWorkgroupName           = (NERR_BASE+595);
  //*The specified workgroup name is invalid

  {$EXTERNALSYM NERR_NameUsesIncompatibleCodePage}
  NERR_NameUsesIncompatibleCodePage   = (NERR_BASE+596);
  //*The specified computer name is incompatible with the default language used on the domain controller.

  {$EXTERNALSYM NERR_ComputerAccountNotFound}
  NERR_ComputerAccountNotFound        = (NERR_BASE+597);
  //*The specified computer account could not be found.


// ***********WARNING ****************
// *The range 2750-2799 has been     *
// *allocated to the IBM LAN Server  *
// ***********************************

// ***********WARNING ****************
// *The range 2900-2999 has been     *
// *reserved for Microsoft OEMs      *
// ***********************************

// **END_INTERNAL**

  {$EXTERNALSYM MAX_NERR}
  MAX_NERR                 = (NERR_BASE+899);
  // This is the last error in NERR range.

// Translated from LMCONS.H

// String Lengths for various LanMan names

const
  {$EXTERNALSYM CNLEN}
  CNLEN = 15;                           // Computer name length
  {$EXTERNALSYM LM20_CNLEN}
  LM20_CNLEN = 15;                      // LM 2.0 Computer name length
  {$EXTERNALSYM DNLEN}
  DNLEN = CNLEN;                        // Maximum domain name length
  {$EXTERNALSYM LM20_DNLEN}
  LM20_DNLEN = LM20_CNLEN;              // LM 2.0 Maximum domain name length

  {$EXTERNALSYM UNCLEN}
  UNCLEN = (CNLEN+2);                   // UNC computer name length
  {$EXTERNALSYM LM20_UNCLEN}
  LM20_UNCLEN = (LM20_CNLEN+2);         // LM 2.0 UNC computer name length

  {$EXTERNALSYM NNLEN}
  NNLEN = 80;                           // Net name length (share name)
  {$EXTERNALSYM LM20_NNLEN}
  LM20_NNLEN = 12;                      // LM 2.0 Net name length

  {$EXTERNALSYM RMLEN}
  RMLEN = (UNCLEN+1+NNLEN);             // Max remote name length
  {$EXTERNALSYM LM20_RMLEN}
  LM20_RMLEN  = (LM20_UNCLEN+1+LM20_NNLEN); // LM 2.0 Max remote name length

  {$EXTERNALSYM SNLEN}
  SNLEN = 80;                           // Service name length
  {$EXTERNALSYM LM20_SNLEN}
  LM20_SNLEN = 15;                      // LM 2.0 Service name length
  {$EXTERNALSYM STXTLEN}
  STXTLEN = 256;                        // Service text length
  {$EXTERNALSYM LM20_STXTLEN}
  LM20_STXTLEN = 63;                    // LM 2.0 Service text length

  {$EXTERNALSYM PATHLEN}
  PATHLEN = 256;                        // Max. path (not including drive name)
  {$EXTERNALSYM LM20_PATHLEN}
  LM20_PATHLEN = 256;                   // LM 2.0 Max. path

  {$EXTERNALSYM DEVLEN}
  DEVLEN = 80;                          // Device name length
  {$EXTERNALSYM LM20_DEVLEN}
  LM20_DEVLEN = 8;                      // LM 2.0 Device name length

  {$EXTERNALSYM EVLEN}
  EVLEN = 16;                           // Event name length

// User, Group and Password lengths

  {$EXTERNALSYM UNLEN}
  UNLEN = 256;                          // Maximum user name length
  {$EXTERNALSYM LM20_UNLEN}
  LM20_UNLEN = 20;                      // LM 2.0 Maximum user name length

  {$EXTERNALSYM GNLEN}
  GNLEN = UNLEN;                        // Group name
  {$EXTERNALSYM LM20_GNLEN}
  LM20_GNLEN = LM20_UNLEN;              // LM 2.0 Group name

  {$EXTERNALSYM PWLEN}
  PWLEN = 256;                          // Maximum password length
  {$EXTERNALSYM LM20_PWLEN}
  LM20_PWLEN = 14;                      // LM 2.0 Maximum password length

  {$EXTERNALSYM SHPWLEN}
  SHPWLEN = 8;                          // Share password length (bytes)

  {$EXTERNALSYM CLTYPE_LEN}
  CLTYPE_LEN = 12;                      // Length of client type string

  {$EXTERNALSYM MAXCOMMENTSZ}
  MAXCOMMENTSZ = 256;                   // Multipurpose comment length
  {$EXTERNALSYM LM20_MAXCOMMENTSZ}
  LM20_MAXCOMMENTSZ = 48;               // LM 2.0 Multipurpose comment length

  {$EXTERNALSYM QNLEN}
  QNLEN = NNLEN;                        // Queue name maximum length
  {$EXTERNALSYM LM20_QNLEN}
  LM20_QNLEN = LM20_NNLEN;              // LM 2.0 Queue name maximum length

// The ALERTSZ and MAXDEVENTRIES defines have not yet been NT'ized.
// Whoever ports these components should change these values appropriately.

  {$EXTERNALSYM ALERTSZ}
  ALERTSZ = 128;                        // size of alert string in server
  {$EXTERNALSYM MAXDEVENTRIES}
  MAXDEVENTRIES = (Sizeof(Integer)*8);  // Max number of device entries

                                        //
                                        // We use int bitmap to represent
                                        //

  {$EXTERNALSYM NETBIOS_NAME_LEN}
  NETBIOS_NAME_LEN = 16;                // NetBIOS net name (bytes)

// Value to be used with APIs which have a "preferred maximum length"
// parameter.  This value indicates that the API should just allocate
// "as much as it takes."

  {$EXTERNALSYM MAX_PREFERRED_LENGTH}
  MAX_PREFERRED_LENGTH = DWORD(-1);

//        Constants used with encryption

  {$EXTERNALSYM CRYPT_KEY_LEN}
  CRYPT_KEY_LEN = 7;
  {$EXTERNALSYM CRYPT_TXT_LEN}
  CRYPT_TXT_LEN = 8;
  {$EXTERNALSYM ENCRYPTED_PWLEN}
  ENCRYPTED_PWLEN = 16;
  {$EXTERNALSYM SESSION_PWLEN}
  SESSION_PWLEN = 24;
  {$EXTERNALSYM SESSION_CRYPT_KLEN}
  SESSION_CRYPT_KLEN = 21;

//  Value to be used with SetInfo calls to allow setting of all
//  settable parameters (parmnum zero option)

  {$EXTERNALSYM PARMNUM_ALL}
  PARMNUM_ALL = 0;

  {$EXTERNALSYM PARM_ERROR_UNKNOWN}
  PARM_ERROR_UNKNOWN = DWORD(-1);
  {$EXTERNALSYM PARM_ERROR_NONE}
  PARM_ERROR_NONE = 0;
  {$EXTERNALSYM PARMNUM_BASE_INFOLEVEL}
  PARMNUM_BASE_INFOLEVEL = 1000;

//        Message File Names

  {$EXTERNALSYM MESSAGE_FILENAME}
  MESSAGE_FILENAME = 'NETMSG';
  {$EXTERNALSYM OS2MSG_FILENAME}
  OS2MSG_FILENAME = 'BASE';
  {$EXTERNALSYM HELP_MSG_FILENAME}
  HELP_MSG_FILENAME = 'NETH';

//**INTERNAL_ONLY**/

// The backup message file named here is a duplicate of net.msg. It
// is not shipped with the product, but is used at buildtime to
// msgbind certain messages to netapi.dll and some of the services.
// This allows for OEMs to modify the message text in net.msg and
// have those changes show up.        Only in case there is an error in
// retrieving the messages from net.msg do we then get the bound
// messages out of bak.msg (really out of the message segment).

  {$EXTERNALSYM BACKUP_MSG_FILENAME}
  BACKUP_MSG_FILENAME = 'BAK.MSG';

//**END_INTERNAL**/

// Keywords used in Function Prototypes

type
  {$EXTERNALSYM NET_API_STATUS}
  NET_API_STATUS = DWORD;
  {$EXTERNALSYM API_RET_TYPE}
  API_RET_TYPE = NET_API_STATUS;        // Old value: do not use

// The platform ID indicates the levels to use for platform-specific
// information.

const
  {$EXTERNALSYM PLATFORM_ID_DOS}
  PLATFORM_ID_DOS = 300;
  {$EXTERNALSYM PLATFORM_ID_OS2}
  PLATFORM_ID_OS2 = 400;
  {$EXTERNALSYM PLATFORM_ID_NT}
  PLATFORM_ID_NT = 500;
  {$EXTERNALSYM PLATFORM_ID_OSF}
  PLATFORM_ID_OSF = 600;
  {$EXTERNALSYM PLATFORM_ID_VMS}
  PLATFORM_ID_VMS = 700;

//      There message numbers assigned to different LANMAN components
//      are as defined below.
//
//      lmerr.h:        2100 - 2999     NERR_BASE
//      alertmsg.h:     3000 - 3049     ALERT_BASE
//      lmsvc.h:        3050 - 3099     SERVICE_BASE
//      lmerrlog.h:     3100 - 3299     ERRLOG_BASE
//      msgtext.h:      3300 - 3499     MTXT_BASE
//      apperr.h:       3500 - 3999     APPERR_BASE
//      apperrfs.h:     4000 - 4299     APPERRFS_BASE
//      apperr2.h:      4300 - 5299     APPERR2_BASE
//      ncberr.h:       5300 - 5499     NRCERR_BASE
//      alertmsg.h:     5500 - 5599     ALERT2_BASE
//      lmsvc.h:        5600 - 5699     SERVICE2_BASE
//      lmerrlog.h      5700 - 5799     ERRLOG2_BASE

  {$EXTERNALSYM MIN_LANMAN_MESSAGE_ID}
  MIN_LANMAN_MESSAGE_ID = NERR_BASE;
  {$EXTERNALSYM MAX_LANMAN_MESSAGE_ID}
  MAX_LANMAN_MESSAGE_ID = 5799;

// Translated from LMACCESS.H

// User Class

// Function Prototypes - User

{$EXTERNALSYM NetUserAdd}
function NetUserAdd(servername: LPCWSTR; level: DWORD; buf: Pointer;
  parm_err: PDWORD): NET_API_STATUS; stdcall;

{$EXTERNALSYM NetUserEnum}
function NetUserEnum(servername: LPCWSTR; level: DWORD; filter: DWORD;
  var bufptr: Pointer; prefmaxlen: DWORD; var entriesread: DWORD;
  var totalentries: DWORD; resume_handle: PDWORD): NET_API_STATUS; stdcall;

{$EXTERNALSYM NetUserGetInfo}
function NetUserGetInfo(servername: LPCWSTR; username: LPCWSTR; level: DWORD;
  var bufptr: Pointer): NET_API_STATUS; stdcall;

{$EXTERNALSYM NetUserSetInfo}
function NetUserSetInfo(servername: LPCWSTR; username: LPCWSTR; level: DWORD;
  buf: Pointer; parm_err: PDWORD): NET_API_STATUS; stdcall;

{$EXTERNALSYM NetUserDel}
function NetUserDel(servername: LPCWSTR; username: LPCWSTR): NET_API_STATUS; stdcall;

{$EXTERNALSYM NetUserGetGroups}
function NetUserGetGroups(servername: LPCWSTR; username: LPCWSTR; level: DWORD;
  var bufptr: Pointer; prefmaxlen: DWORD; var entriesread: DWORD;
  var totalentries: DWORD): NET_API_STATUS; stdcall;

{$EXTERNALSYM NetUserSetGroups}
function NetUserSetGroups(servername: LPCWSTR; username: LPCWSTR; level: DWORD;
  buf: Pointer; num_entries: DWORD): NET_API_STATUS; stdcall;

{$EXTERNALSYM NetUserGetLocalGroups}
function NetUserGetLocalGroups(servername: LPCWSTR; username: LPCWSTR;
  level: DWORD; flags: DWORD; var bufptr: Pointer; prefmaxlen: DWORD;
  var entriesread: DWORD; var totalentries: DWORD): NET_API_STATUS; stdcall;

{$EXTERNALSYM NetUserModalsGet}
function NetUserModalsGet(servername: LPCWSTR; level: DWORD;
  var bufptr: Pointer): NET_API_STATUS; stdcall;

{$EXTERNALSYM NetUserModalsSet}
function NetUserModalsSet(servername: LPCWSTR; level: DWORD; buf: Pointer;
  parm_err: PDWORD): NET_API_STATUS; stdcall;

{$EXTERNALSYM NetUserChangePassword}
function NetUserChangePassword(domainname, username, oldpassword,
  newpassword: LPCWSTR): NET_API_STATUS; stdcall;

//  Data Structures - User

type
  PUserInfo0 = ^TUserInfo0;
  {$EXTERNALSYM _USER_INFO_0}
  _USER_INFO_0  = record
    usri0_name: LPWSTR;
  end;
  TUserInfo0 = _USER_INFO_0;
  {$EXTERNALSYM USER_INFO_0}
  USER_INFO_0 = _USER_INFO_0;

  PUserInfo1 = ^TUserInfo1;
  {$EXTERNALSYM _USER_INFO_1}
  _USER_INFO_1 = record
    usri1_name: LPWSTR;
    usri1_password: LPWSTR;
    usri1_password_age: DWORD;
    usri1_priv: DWORD;
    usri1_home_dir: LPWSTR;
    usri1_comment: LPWSTR;
    usri1_flags: DWORD;
    usri1_script_path: LPWSTR;
  end;
  TUserInfo1 = _USER_INFO_1;
  {$EXTERNALSYM USER_INFO_1}
  USER_INFO_1 = _USER_INFO_1;

  PUserInfo2 = ^TUserInfo2;
  {$EXTERNALSYM _USER_INFO_2}
  _USER_INFO_2 = record
    usri2_name: LPWSTR;
    usri2_password: LPWSTR;
    usri2_password_age: DWORD;
    usri2_priv: DWORD;
    usri2_home_dir: LPWSTR;
    usri2_comment: LPWSTR;
    usri2_flags: DWORD;
    usri2_script_path: LPWSTR;
    usri2_auth_flags: DWORD;
    usri2_full_name: LPWSTR;
    usri2_usr_comment: LPWSTR;
    usri2_parms: LPWSTR;
    usri2_workstations: LPWSTR;
    usri2_last_logon: DWORD;
    usri2_last_logoff: DWORD;
    usri2_acct_expires: DWORD;
    usri2_max_storage: DWORD;
    usri2_units_per_week: DWORD;
    usri2_logon_hours: PBYTE;
    usri2_bad_pw_count: DWORD;
    usri2_num_logons: DWORD;
    usri2_logon_server: LPWSTR;
    usri2_country_code: DWORD;
    usri2_code_page: DWORD;
  end;
  TUserInfo2 = _USER_INFO_2;
  {$EXTERNALSYM USER_INFO_2}
  USER_INFO_2 = _USER_INFO_2;

  PUserInfo3 = ^TUserInfo3;
  {$EXTERNALSYM _USER_INFO_3}
  _USER_INFO_3 = record
    usri3_name: LPWSTR;
    usri3_password: LPWSTR;
    usri3_password_age: DWORD;
    usri3_priv: DWORD;
    usri3_home_dir: LPWSTR;
    usri3_comment: LPWSTR;
    usri3_flags: DWORD;
    usri3_script_path: LPWSTR;
    usri3_auth_flags: DWORD;
    usri3_full_name: LPWSTR;
    usri3_usr_comment: LPWSTR;
    usri3_parms: LPWSTR;
    usri3_workstations: LPWSTR;
    usri3_last_logon: DWORD;
    usri3_last_logoff: DWORD;
    usri3_acct_expires: DWORD;
    usri3_max_storage: DWORD;
    usri3_units_per_week: DWORD;
    usri3_logon_hours: PBYTE;
    usri3_bad_pw_count: DWORD;
    usri3_num_logons: DWORD;
    usri3_logon_server: LPWSTR;
    usri3_country_code: DWORD;
    usri3_code_page: DWORD;
    usri3_user_id: DWORD;
    usri3_primary_group_id: DWORD;
    usri3_profile: LPWSTR;
    usri3_home_dir_drive: LPWSTR;
    usri3_password_expired: DWORD;
  end;
  TUserInfo3 = _USER_INFO_3;
  {$EXTERNALSYM USER_INFO_3}
  USER_INFO_3 = _USER_INFO_3;

  PUserInfo10 = ^TUserInfo10;
  {$EXTERNALSYM _USER_INFO_10}
  _USER_INFO_10 = record
    usri10_name: LPWSTR;
    usri10_comment: LPWSTR;
    usri10_usr_comment: LPWSTR;
    usri10_full_name: LPWSTR;
  end;
  TUserInfo10 = _USER_INFO_10;
  {$EXTERNALSYM USER_INFO_10}
  USER_INFO_10 = _USER_INFO_10;

  PUserInfo11 = ^TUserInfo11;
  {$EXTERNALSYM _USER_INFO_11}
  _USER_INFO_11 = record
    usri11_name: LPWSTR;
    usri11_comment: LPWSTR;
    usri11_usr_comment: LPWSTR;
    usri11_full_name: LPWSTR;
    usri11_priv: DWORD;
    usri11_auth_flags: DWORD;
    usri11_password_age: DWORD;
    usri11_home_dir: LPWSTR;
    usri11_parms: LPWSTR;
    usri11_last_logon: DWORD;
    usri11_last_logoff: DWORD;
    usri11_bad_pw_count: DWORD;
    usri11_num_logons: DWORD;
    usri11_logon_server: LPWSTR;
    usri11_country_code: DWORD;
    usri11_workstations: LPWSTR;
    usri11_max_storage: DWORD;
    usri11_units_per_week: DWORD;
    usri11_logon_hours: PBYTE;
    usri11_code_page: DWORD;
  end;
  TUserInfo11 = _USER_INFO_11;
  {$EXTERNALSYM USER_INFO_11}
  USER_INFO_11 = _USER_INFO_11;

  PUserInfo20 = ^TUserInfo20;
  {$EXTERNALSYM _USER_INFO_20}
  _USER_INFO_20 = record
    usri20_name: LPWSTR;
    usri20_full_name: LPWSTR;
    usri20_comment: LPWSTR;
    usri20_flags: DWORD;
    usri20_user_id: DWORD;
  end;
  TUserInfo20 = _USER_INFO_20;
  {$EXTERNALSYM USER_INFO_20}
  USER_INFO_20 = _USER_INFO_20;

  PUserInfo21 = ^TUserInfo21;
  {$EXTERNALSYM _USER_INFO_21}
  _USER_INFO_21 = record
    usri21_password: array[0..ENCRYPTED_PWLEN-1] of Byte;
  end;
  TUserInfo21 = _USER_INFO_21;
  {$EXTERNALSYM USER_INFO_21}
  USER_INFO_21 = _USER_INFO_21;

  PUserInfo22 = ^TUserInfo22;
  {$EXTERNALSYM _USER_INFO_22}
  _USER_INFO_22 = record
    usri22_name: LPWSTR;
    usri22_password: array[0..ENCRYPTED_PWLEN-1] of Byte;
    usri22_password_age: DWORD;
    usri22_priv: DWORD;
    usri22_home_dir: LPWSTR;
    usri22_comment: LPWSTR;
    usri22_flags: DWORD;
    usri22_script_path: LPWSTR;
    usri22_auth_flags: DWORD;
    usri22_full_name: LPWSTR;
    usri22_usr_comment: LPWSTR;
    usri22_parms: LPWSTR;
    usri22_workstations: LPWSTR;
    usri22_last_logon: DWORD;
    usri22_last_logoff: DWORD;
    usri22_acct_expires: DWORD;
    usri22_max_storage: DWORD;
    usri22_units_per_week: DWORD;
    usri22_logon_hours: PBYTE;
    usri22_bad_pw_count: DWORD;
    usri22_num_logons: DWORD;
    usri22_logon_server: LPWSTR;
    usri22_country_code: DWORD;
    usri22_code_page: DWORD;
  end;
  TUserInfo22 = _USER_INFO_22;
  {$EXTERNALSYM USER_INFO_22}
  USER_INFO_22 = _USER_INFO_22;

  PUserInfo1003 = ^TUserInfo1003;
  {$EXTERNALSYM _USER_INFO_1003}
  _USER_INFO_1003 = record
    usri1003_password: LPWSTR;
  end;
  TUserInfo1003 = _USER_INFO_1003;
  {$EXTERNALSYM USER_INFO_1003}
  USER_INFO_1003 = _USER_INFO_1003;

  PUserInfo1005 = ^TUserInfo1005;
  {$EXTERNALSYM _USER_INFO_1005}
  _USER_INFO_1005 = record
    usri1005_priv: DWORD;
  end;
  TUserInfo1005 = _USER_INFO_1005;
  {$EXTERNALSYM USER_INFO_1005}
  USER_INFO_1005 = _USER_INFO_1005;

  PUserInfo1006 = ^TUserInfo1006;
  {$EXTERNALSYM _USER_INFO_1006}
  _USER_INFO_1006 = record
    usri1006_home_dir: LPWSTR;
  end;
  TUserInfo1006 = _USER_INFO_1006;
  {$EXTERNALSYM USER_INFO_1006}
  USER_INFO_1006 = _USER_INFO_1006;

  PUserInfo1007 = ^TUserInfo1007;
  {$EXTERNALSYM _USER_INFO_1007}
  _USER_INFO_1007 = record
    usri1007_comment: LPWSTR;
  end;
  TUserInfo1007 = _USER_INFO_1007;
  {$EXTERNALSYM USER_INFO_1007}
  USER_INFO_1007 = _USER_INFO_1007;

  PUserInfo1008 = ^TUserInfo1008;
  {$EXTERNALSYM _USER_INFO_1008}
  _USER_INFO_1008 = record
    usri1008_flags: DWORD;
  end;
  TUserInfo1008 = _USER_INFO_1008;
  {$EXTERNALSYM USER_INFO_1008}
  USER_INFO_1008 = _USER_INFO_1008;

  PUserInfo1009 = ^TUserInfo1009;
  {$EXTERNALSYM _USER_INFO_1009}
  _USER_INFO_1009 = record
    usri1009_script_path: LPWSTR;
  end;
  TUserInfo1009 = _USER_INFO_1009;
  {$EXTERNALSYM USER_INFO_1009}
  USER_INFO_1009 = _USER_INFO_1009;

  PUserInfo1010 = ^TUserInfo1010;
  {$EXTERNALSYM _USER_INFO_1010}
  _USER_INFO_1010 = record
    usri1010_auth_flags: DWORD;
  end;
  TUserInfo1010 = _USER_INFO_1010;
  {$EXTERNALSYM USER_INFO_1010}
  USER_INFO_1010 = _USER_INFO_1010;

  PUserInfo1011 = ^TUserInfo1011;
  {$EXTERNALSYM _USER_INFO_1011}
  _USER_INFO_1011 = record
    usri1011_full_name: LPWSTR;
  end;
  TUserInfo1011 = _USER_INFO_1011;
  {$EXTERNALSYM USER_INFO_1011}
  USER_INFO_1011 = _USER_INFO_1011;

  PUserInfo1012 = ^TUserInfo1012;
  {$EXTERNALSYM _USER_INFO_1012}
  _USER_INFO_1012 = record
    usri1012_usr_comment: LPWSTR;
  end;
  TUserInfo1012 = _USER_INFO_1012;
  {$EXTERNALSYM USER_INFO_1012}
  USER_INFO_1012 = _USER_INFO_1012;

  PUserInfo1013 = ^TUserInfo1013;
  {$EXTERNALSYM _USER_INFO_1013}
  _USER_INFO_1013 = record
    usri1013_parms: LPWSTR;
  end;
  TUserInfo1013 = _USER_INFO_1013;
  {$EXTERNALSYM USER_INFO_1013}
  USER_INFO_1013 = _USER_INFO_1013;

  PUserInfo1014 = ^TUserInfo1014;
  {$EXTERNALSYM _USER_INFO_1014}
  _USER_INFO_1014 = record
    usri1014_workstations: LPWSTR;
  end;
  TUserInfo1014 = _USER_INFO_1014;
  {$EXTERNALSYM USER_INFO_1014}
  USER_INFO_1014 = _USER_INFO_1014;

  PUserInfo1017 = ^TUserInfo1017;
  {$EXTERNALSYM _USER_INFO_1017}
  _USER_INFO_1017 = record
    usri1017_acct_expires: DWORD;
  end;
  TUserInfo1017 = _USER_INFO_1017;
  {$EXTERNALSYM USER_INFO_1017}
  USER_INFO_1017 = _USER_INFO_1017;

  PUserInfo1018 = ^TUserInfo1018;
  {$EXTERNALSYM _USER_INFO_1018}
  _USER_INFO_1018 = record
    usri1018_max_storage: DWORD;
  end;
  TUserInfo1018 = _USER_INFO_1018;
  {$EXTERNALSYM USER_INFO_1018}
  USER_INFO_1018 = _USER_INFO_1018;

  PUserInfo1020 = ^TUserInfo1020;
  {$EXTERNALSYM _USER_INFO_1020}
  _USER_INFO_1020 = record
    usri1020_units_per_week: DWORD;
    usri1020_logon_hours: Pointer;
  end;
  TUserInfo1020 = _USER_INFO_1020;
  {$EXTERNALSYM USER_INFO_1020}
  USER_INFO_1020 = _USER_INFO_1020;

  PUserInfo1023 = ^TUserInfo1023;
  {$EXTERNALSYM _USER_INFO_1023}
  _USER_INFO_1023 = record
    usri1023_logon_server: LPWSTR;
  end;
  TUserInfo1023 = _USER_INFO_1023;
  {$EXTERNALSYM USER_INFO_1023}
  USER_INFO_1023 = _USER_INFO_1023;

  PUserInfo1024 = ^TUserInfo1024;
  {$EXTERNALSYM _USER_INFO_1024}
  _USER_INFO_1024 = record
    usri1024_country_code: DWORD;
  end;
  TUserInfo1024 = _USER_INFO_1024;
  {$EXTERNALSYM USER_INFO_1024}
  USER_INFO_1024 = _USER_INFO_1024;

  PUserInfo1025 = ^TUserInfo1025;
  {$EXTERNALSYM _USER_INFO_1025}
  _USER_INFO_1025 = record
    usri1025_code_page: DWORD;
  end;
  TUserInfo1025 = _USER_INFO_1025;
  {$EXTERNALSYM USER_INFO_1025}
  USER_INFO_1025 = _USER_INFO_1025;

  PUserInfo1051 = ^TUserInfo1051;
  {$EXTERNALSYM _USER_INFO_1051}
  _USER_INFO_1051 = record
    usri1051_primary_group_id: DWORD;
  end;
  TUserInfo1051 = _USER_INFO_1051;
  {$EXTERNALSYM USER_INFO_1051}
  USER_INFO_1051 = _USER_INFO_1051;

  PUserInfo1052 = ^TUserInfo1052;
  {$EXTERNALSYM _USER_INFO_1052}
  _USER_INFO_1052 = record
    usri1052_profile: LPWSTR;
  end;
  TUserInfo1052 = _USER_INFO_1052;
  {$EXTERNALSYM USER_INFO_1052}
  USER_INFO_1052 = _USER_INFO_1052;

  PUserInfo1053 = ^TUserInfo1053;
  {$EXTERNALSYM _USER_INFO_1053}
  _USER_INFO_1053 = record
    usri1053_home_dir_drive: LPWSTR;
  end;
  TUserInfo1053 = _USER_INFO_1053;
  {$EXTERNALSYM USER_INFO_1053}
  USER_INFO_1053 = _USER_INFO_1053;

//  Data Structures - User Modals

  PUserModalsInfo0 = ^TUserModalsInfo0;
  {$EXTERNALSYM _USER_MODALS_INFO_0}
  _USER_MODALS_INFO_0 = record
    usrmod0_min_passwd_len: DWORD;
    usrmod0_max_passwd_age: DWORD;
    usrmod0_min_passwd_age: DWORD;
    usrmod0_force_logoff: DWORD;
    usrmod0_password_hist_len: DWORD;
  end;
  TUserModalsInfo0 = _USER_MODALS_INFO_0;
  {$EXTERNALSYM USER_MODALS_INFO_0}
  USER_MODALS_INFO_0 = _USER_MODALS_INFO_0;

  PUserModalsInfo1 = ^TUserModalsInfo1;
  {$EXTERNALSYM _USER_MODALS_INFO_1}
  _USER_MODALS_INFO_1 = record
    usrmod1_role: DWORD;
    usrmod1_primary: LPWSTR;
  end;
  TUserModalsInfo1 = _USER_MODALS_INFO_1;
  {$EXTERNALSYM USER_MODALS_INFO_1}
  USER_MODALS_INFO_1 = _USER_MODALS_INFO_1;

  PUserModalsInfo2 = ^TUserModalsInfo2;
  {$EXTERNALSYM _USER_MODALS_INFO_2}
  _USER_MODALS_INFO_2 = record
    usrmod2_domain_name: LPWSTR;
    usrmod2_domain_id: PSID;
  end;
  TUserModalsInfo2 = _USER_MODALS_INFO_2;
  {$EXTERNALSYM USER_MODALS_INFO_2}
  USER_MODALS_INFO_2 = _USER_MODALS_INFO_2;

  PUserModalsInfo3 = ^TUserModalsInfo3;
  {$EXTERNALSYM _USER_MODALS_INFO_3}
  _USER_MODALS_INFO_3 = record
    usrmod3_lockout_duration: DWORD;
    usrmod3_lockout_observation_window: DWORD;
    usrmod3_lockout_threshold: DWORD;
  end;
  TUserModalsInfo3 = _USER_MODALS_INFO_3;
  {$EXTERNALSYM USER_MODALS_INFO_3}
  USER_MODALS_INFO_3 = _USER_MODALS_INFO_3;

  PUserModalsInfo1001 = ^TUserModalsInfo1001;
  {$EXTERNALSYM _USER_MODALS_INFO_1001}
  _USER_MODALS_INFO_1001 = record
    usrmod1001_min_passwd_len: DWORD;
  end;
  TUserModalsInfo1001 = _USER_MODALS_INFO_1001;
  {$EXTERNALSYM USER_MODALS_INFO_1001}
  USER_MODALS_INFO_1001 = _USER_MODALS_INFO_1001;

  PUserModalsInfo1002 = ^TUserModalsInfo1002;
  {$EXTERNALSYM _USER_MODALS_INFO_1002}
  _USER_MODALS_INFO_1002 = record
    usrmod1002_max_passwd_age: DWORD;
  end;
  TUserModalsInfo1002 = _USER_MODALS_INFO_1002;
  {$EXTERNALSYM USER_MODALS_INFO_1002}
  USER_MODALS_INFO_1002 = _USER_MODALS_INFO_1002;

  PUserModalsInfo1003 = ^TUserModalsInfo1003;
  {$EXTERNALSYM _USER_MODALS_INFO_1003}
  _USER_MODALS_INFO_1003 = record
    usrmod1003_min_passwd_age: DWORD;
  end;
  TUserModalsInfo1003 = _USER_MODALS_INFO_1003;
  {$EXTERNALSYM USER_MODALS_INFO_1003}
  USER_MODALS_INFO_1003 = _USER_MODALS_INFO_1003;

  PUserModalsInfo1004 = ^TUserModalsInfo1004;
  {$EXTERNALSYM _USER_MODALS_INFO_1004}
  _USER_MODALS_INFO_1004 = record
    usrmod1004_force_logoff: DWORD;
  end;
  TUserModalsInfo1004 = _USER_MODALS_INFO_1004;
  {$EXTERNALSYM USER_MODALS_INFO_1004}
  USER_MODALS_INFO_1004 = _USER_MODALS_INFO_1004;

  PUserModalsInfo1005 = ^TUserModalsInfo1005;
  {$EXTERNALSYM _USER_MODALS_INFO_1005}
  _USER_MODALS_INFO_1005 = record
    usrmod1005_password_hist_len: DWORD;
  end;
  TUserModalsInfo1005 = _USER_MODALS_INFO_1005;
  {$EXTERNALSYM USER_MODALS_INFO_1005}
  USER_MODALS_INFO_1005 = _USER_MODALS_INFO_1005;

  PUserModalsInfo1006 = ^TUserModalsInfo1006;
  {$EXTERNALSYM _USER_MODALS_INFO_1006}
  _USER_MODALS_INFO_1006 = record
    usrmod1006_role: DWORD;
  end;
  TUserModalsInfo1006 = _USER_MODALS_INFO_1006;
  {$EXTERNALSYM USER_MODALS_INFO_1006}
  USER_MODALS_INFO_1006 = _USER_MODALS_INFO_1006;

  PUserModalsInfo1007 = ^TUserModalsInfo1007;
  {$EXTERNALSYM _USER_MODALS_INFO_1007}
  _USER_MODALS_INFO_1007 = record
    usrmod1007_primary: LPWSTR;
  end;
  TUserModalsInfo1007 = _USER_MODALS_INFO_1007;
  {$EXTERNALSYM USER_MODALS_INFO_1007}
  USER_MODALS_INFO_1007 = _USER_MODALS_INFO_1007;

// Special Values and Constants - User

//  Bit masks for field usriX_flags of USER_INFO_X (X = 0/1).

const
  {$EXTERNALSYM UF_SCRIPT}
  UF_SCRIPT                          = $0001;
  {$EXTERNALSYM UF_ACCOUNTDISABLE}
  UF_ACCOUNTDISABLE                  = $0002;
  {$EXTERNALSYM UF_HOMEDIR_REQUIRED}
  UF_HOMEDIR_REQUIRED                = $0008;
  {$EXTERNALSYM UF_LOCKOUT}
  UF_LOCKOUT                         = $0010;
  {$EXTERNALSYM UF_PASSWD_NOTREQD}
  UF_PASSWD_NOTREQD                  = $0020;
  {$EXTERNALSYM UF_PASSWD_CANT_CHANGE}
  UF_PASSWD_CANT_CHANGE              = $0040;
  {$EXTERNALSYM UF_ENCRYPTED_TEXT_PASSWORD_ALLOWED}
  UF_ENCRYPTED_TEXT_PASSWORD_ALLOWED = $0080;

// Account type bits as part of usri_flags.

  {$EXTERNALSYM UF_TEMP_DUPLICATE_ACCOUNT}
  UF_TEMP_DUPLICATE_ACCOUNT       = $0100;
  {$EXTERNALSYM UF_NORMAL_ACCOUNT}
  UF_NORMAL_ACCOUNT               = $0200;
  {$EXTERNALSYM UF_INTERDOMAIN_TRUST_ACCOUNT}
  UF_INTERDOMAIN_TRUST_ACCOUNT    = $0800;
  {$EXTERNALSYM UF_WORKSTATION_TRUST_ACCOUNT}
  UF_WORKSTATION_TRUST_ACCOUNT    = $1000;
  {$EXTERNALSYM UF_SERVER_TRUST_ACCOUNT}
  UF_SERVER_TRUST_ACCOUNT         = $2000;

  {$EXTERNALSYM UF_MACHINE_ACCOUNT_MASK}
  UF_MACHINE_ACCOUNT_MASK = UF_INTERDOMAIN_TRUST_ACCOUNT or
    UF_WORKSTATION_TRUST_ACCOUNT or UF_SERVER_TRUST_ACCOUNT;

  {$EXTERNALSYM UF_ACCOUNT_TYPE_MASK}
  UF_ACCOUNT_TYPE_MASK = UF_TEMP_DUPLICATE_ACCOUNT or UF_NORMAL_ACCOUNT or
    UF_INTERDOMAIN_TRUST_ACCOUNT or UF_WORKSTATION_TRUST_ACCOUNT or
    UF_SERVER_TRUST_ACCOUNT;

  {$EXTERNALSYM UF_DONT_EXPIRE_PASSWD}
  UF_DONT_EXPIRE_PASSWD           = $10000;
  {$EXTERNALSYM UF_MNS_LOGON_ACCOUNT}
  UF_MNS_LOGON_ACCOUNT            = $20000;
  {$EXTERNALSYM UF_SMARTCARD_REQUIRED}
  UF_SMARTCARD_REQUIRED           = $40000;
  {$EXTERNALSYM UF_TRUSTED_FOR_DELEGATION}
  UF_TRUSTED_FOR_DELEGATION       = $80000;
  {$EXTERNALSYM UF_NOT_DELEGATED}
  UF_NOT_DELEGATED               = $100000;
  {$EXTERNALSYM UF_USE_DES_KEY_ONLY}
  UF_USE_DES_KEY_ONLY            = $200000;
  {$EXTERNALSYM UF_DONT_REQUIRE_PREAUTH}
  UF_DONT_REQUIRE_PREAUTH        = $400000;

  {$EXTERNALSYM UF_SETTABLE_BITS}
  UF_SETTABLE_BITS = UF_SCRIPT or UF_ACCOUNTDISABLE or UF_LOCKOUT or
    UF_HOMEDIR_REQUIRED or UF_PASSWD_NOTREQD or UF_PASSWD_CANT_CHANGE or
    UF_ACCOUNT_TYPE_MASK or UF_DONT_EXPIRE_PASSWD or UF_MNS_LOGON_ACCOUNT or
    UF_ENCRYPTED_TEXT_PASSWORD_ALLOWED or UF_SMARTCARD_REQUIRED or
    UF_TRUSTED_FOR_DELEGATION or UF_NOT_DELEGATED or UF_USE_DES_KEY_ONLY or
    UF_DONT_REQUIRE_PREAUTH;

// bit masks for the NetUserEnum filter parameter.

  {$EXTERNALSYM FILTER_TEMP_DUPLICATE_ACCOUNT}
  FILTER_TEMP_DUPLICATE_ACCOUNT       = $0001;
  {$EXTERNALSYM FILTER_NORMAL_ACCOUNT}
  FILTER_NORMAL_ACCOUNT               = $0002;
  {$EXTERNALSYM FILTER_PROXY_ACCOUNT}
  FILTER_PROXY_ACCOUNT                = $0004;
  {$EXTERNALSYM FILTER_INTERDOMAIN_TRUST_ACCOUNT}
  FILTER_INTERDOMAIN_TRUST_ACCOUNT    = $0008;
  {$EXTERNALSYM FILTER_WORKSTATION_TRUST_ACCOUNT}
  FILTER_WORKSTATION_TRUST_ACCOUNT    = $0010;
  {$EXTERNALSYM FILTER_SERVER_TRUST_ACCOUNT}
  FILTER_SERVER_TRUST_ACCOUNT         = $0020;

// bit masks for the NetUserGetLocalGroups flags

  {$EXTERNALSYM LG_INCLUDE_INDIRECT}
  LG_INCLUDE_INDIRECT         = $0001;

//  Bit masks for field usri2_auth_flags of USER_INFO_2.

  {$EXTERNALSYM AF_OP_PRINT}
  AF_OP_PRINT             = $1;
  {$EXTERNALSYM AF_OP_COMM}
  AF_OP_COMM              = $2;
  {$EXTERNALSYM AF_OP_SERVER}
  AF_OP_SERVER            = $4;
  {$EXTERNALSYM AF_OP_ACCOUNTS}
  AF_OP_ACCOUNTS          = $8;
  {$EXTERNALSYM AF_SETTABLE_BITS}
  AF_SETTABLE_BITS = AF_OP_PRINT or AF_OP_COMM or AF_OP_SERVER or AF_OP_ACCOUNTS;

//  UAS role manifests under NETLOGON

  {$EXTERNALSYM UAS_ROLE_STANDALONE}
  UAS_ROLE_STANDALONE     = 0;
  {$EXTERNALSYM UAS_ROLE_MEMBER}
  UAS_ROLE_MEMBER         = 1;
  {$EXTERNALSYM UAS_ROLE_BACKUP}
  UAS_ROLE_BACKUP         = 2;
  {$EXTERNALSYM UAS_ROLE_PRIMARY}
  UAS_ROLE_PRIMARY        = 3;

//  Values for ParmError for NetUserSetInfo.

  {$EXTERNALSYM USER_NAME_PARMNUM}
  USER_NAME_PARMNUM               = 1;
  {$EXTERNALSYM USER_PASSWORD_PARMNUM}
  USER_PASSWORD_PARMNUM           = 3;
  {$EXTERNALSYM USER_PASSWORD_AGE_PARMNUM}
  USER_PASSWORD_AGE_PARMNUM       = 4;
  {$EXTERNALSYM USER_PRIV_PARMNUM}
  USER_PRIV_PARMNUM               = 5;
  {$EXTERNALSYM USER_HOME_DIR_PARMNUM}
  USER_HOME_DIR_PARMNUM           = 6;
  {$EXTERNALSYM USER_COMMENT_PARMNUM}
  USER_COMMENT_PARMNUM            = 7;
  {$EXTERNALSYM USER_FLAGS_PARMNUM}
  USER_FLAGS_PARMNUM              = 8;
  {$EXTERNALSYM USER_SCRIPT_PATH_PARMNUM}
  USER_SCRIPT_PATH_PARMNUM        = 9;
  {$EXTERNALSYM USER_AUTH_FLAGS_PARMNUM}
  USER_AUTH_FLAGS_PARMNUM         = 10;
  {$EXTERNALSYM USER_FULL_NAME_PARMNUM}
  USER_FULL_NAME_PARMNUM          = 11;
  {$EXTERNALSYM USER_USR_COMMENT_PARMNUM}
  USER_USR_COMMENT_PARMNUM        = 12;
  {$EXTERNALSYM USER_PARMS_PARMNUM}
  USER_PARMS_PARMNUM              = 13;
  {$EXTERNALSYM USER_WORKSTATIONS_PARMNUM}
  USER_WORKSTATIONS_PARMNUM       = 14;
  {$EXTERNALSYM USER_LAST_LOGON_PARMNUM}
  USER_LAST_LOGON_PARMNUM         = 15;
  {$EXTERNALSYM USER_LAST_LOGOFF_PARMNUM}
  USER_LAST_LOGOFF_PARMNUM        = 16;
  {$EXTERNALSYM USER_ACCT_EXPIRES_PARMNUM}
  USER_ACCT_EXPIRES_PARMNUM       = 17;
  {$EXTERNALSYM USER_MAX_STORAGE_PARMNUM}
  USER_MAX_STORAGE_PARMNUM        = 18;
  {$EXTERNALSYM USER_UNITS_PER_WEEK_PARMNUM}
  USER_UNITS_PER_WEEK_PARMNUM     = 19;
  {$EXTERNALSYM USER_LOGON_HOURS_PARMNUM}
  USER_LOGON_HOURS_PARMNUM        = 20;
  {$EXTERNALSYM USER_PAD_PW_COUNT_PARMNUM}
  USER_PAD_PW_COUNT_PARMNUM       = 21;
  {$EXTERNALSYM USER_NUM_LOGONS_PARMNUM}
  USER_NUM_LOGONS_PARMNUM         = 22;
  {$EXTERNALSYM USER_LOGON_SERVER_PARMNUM}
  USER_LOGON_SERVER_PARMNUM       = 23;
  {$EXTERNALSYM USER_COUNTRY_CODE_PARMNUM}
  USER_COUNTRY_CODE_PARMNUM       = 24;
  {$EXTERNALSYM USER_CODE_PAGE_PARMNUM}
  USER_CODE_PAGE_PARMNUM          = 25;
  {$EXTERNALSYM USER_PRIMARY_GROUP_PARMNUM}
  USER_PRIMARY_GROUP_PARMNUM      = 51;
  {$EXTERNALSYM USER_PROFILE}
  USER_PROFILE                    = 52; // ?? Delete when convenient
  {$EXTERNALSYM USER_PROFILE_PARMNUM}
  USER_PROFILE_PARMNUM            = 52;
  {$EXTERNALSYM USER_HOME_DIR_DRIVE_PARMNUM}
  USER_HOME_DIR_DRIVE_PARMNUM     = 53;

// the new infolevel counterparts of the old info level + parmnum

  {$EXTERNALSYM USER_NAME_INFOLEVEL}
  USER_NAME_INFOLEVEL = (PARMNUM_BASE_INFOLEVEL + USER_NAME_PARMNUM);
  {$EXTERNALSYM USER_PASSWORD_INFOLEVEL}
  USER_PASSWORD_INFOLEVEL = (PARMNUM_BASE_INFOLEVEL + USER_PASSWORD_PARMNUM);
  {$EXTERNALSYM USER_PASSWORD_AGE_INFOLEVEL}
  USER_PASSWORD_AGE_INFOLEVEL = (PARMNUM_BASE_INFOLEVEL + USER_PASSWORD_AGE_PARMNUM);
  {$EXTERNALSYM USER_PRIV_INFOLEVEL}
  USER_PRIV_INFOLEVEL = (PARMNUM_BASE_INFOLEVEL + USER_PRIV_PARMNUM);
  {$EXTERNALSYM USER_HOME_DIR_INFOLEVEL}
  USER_HOME_DIR_INFOLEVEL = (PARMNUM_BASE_INFOLEVEL + USER_HOME_DIR_PARMNUM);
  {$EXTERNALSYM USER_COMMENT_INFOLEVEL}
  USER_COMMENT_INFOLEVEL = (PARMNUM_BASE_INFOLEVEL + USER_COMMENT_PARMNUM);
  {$EXTERNALSYM USER_FLAGS_INFOLEVEL}
  USER_FLAGS_INFOLEVEL = (PARMNUM_BASE_INFOLEVEL + USER_FLAGS_PARMNUM);
  {$EXTERNALSYM USER_SCRIPT_PATH_INFOLEVEL}
  USER_SCRIPT_PATH_INFOLEVEL = (PARMNUM_BASE_INFOLEVEL + USER_SCRIPT_PATH_PARMNUM);
  {$EXTERNALSYM USER_AUTH_FLAGS_INFOLEVEL}
  USER_AUTH_FLAGS_INFOLEVEL = (PARMNUM_BASE_INFOLEVEL + USER_AUTH_FLAGS_PARMNUM);
  {$EXTERNALSYM USER_FULL_NAME_INFOLEVEL}
  USER_FULL_NAME_INFOLEVEL = (PARMNUM_BASE_INFOLEVEL + USER_FULL_NAME_PARMNUM);
  {$EXTERNALSYM USER_USR_COMMENT_INFOLEVEL}
  USER_USR_COMMENT_INFOLEVEL = (PARMNUM_BASE_INFOLEVEL + USER_USR_COMMENT_PARMNUM);
  {$EXTERNALSYM USER_PARMS_INFOLEVEL}
  USER_PARMS_INFOLEVEL = (PARMNUM_BASE_INFOLEVEL + USER_PARMS_PARMNUM);
  {$EXTERNALSYM USER_WORKSTATIONS_INFOLEVEL}
  USER_WORKSTATIONS_INFOLEVEL = (PARMNUM_BASE_INFOLEVEL + USER_WORKSTATIONS_PARMNUM);
  {$EXTERNALSYM USER_LAST_LOGON_INFOLEVEL}
  USER_LAST_LOGON_INFOLEVEL = (PARMNUM_BASE_INFOLEVEL + USER_LAST_LOGON_PARMNUM);
  {$EXTERNALSYM USER_LAST_LOGOFF_INFOLEVEL}
  USER_LAST_LOGOFF_INFOLEVEL = (PARMNUM_BASE_INFOLEVEL + USER_LAST_LOGOFF_PARMNUM);
  {$EXTERNALSYM USER_ACCT_EXPIRES_INFOLEVEL}
  USER_ACCT_EXPIRES_INFOLEVEL = (PARMNUM_BASE_INFOLEVEL + USER_ACCT_EXPIRES_PARMNUM);
  {$EXTERNALSYM USER_MAX_STORAGE_INFOLEVEL}
  USER_MAX_STORAGE_INFOLEVEL = (PARMNUM_BASE_INFOLEVEL + USER_MAX_STORAGE_PARMNUM);
  {$EXTERNALSYM USER_UNITS_PER_WEEK_INFOLEVEL}
  USER_UNITS_PER_WEEK_INFOLEVEL = (PARMNUM_BASE_INFOLEVEL + USER_UNITS_PER_WEEK_PARMNUM);
  {$EXTERNALSYM USER_LOGON_HOURS_INFOLEVEL}
  USER_LOGON_HOURS_INFOLEVEL = (PARMNUM_BASE_INFOLEVEL + USER_LOGON_HOURS_PARMNUM);
  {$EXTERNALSYM USER_PAD_PW_COUNT_INFOLEVEL}
  USER_PAD_PW_COUNT_INFOLEVEL = (PARMNUM_BASE_INFOLEVEL + USER_PAD_PW_COUNT_PARMNUM);
  {$EXTERNALSYM USER_NUM_LOGONS_INFOLEVEL}
  USER_NUM_LOGONS_INFOLEVEL = (PARMNUM_BASE_INFOLEVEL + USER_NUM_LOGONS_PARMNUM);
  {$EXTERNALSYM USER_LOGON_SERVER_INFOLEVEL}
  USER_LOGON_SERVER_INFOLEVEL = (PARMNUM_BASE_INFOLEVEL + USER_LOGON_SERVER_PARMNUM);
  {$EXTERNALSYM USER_COUNTRY_CODE_INFOLEVEL}
  USER_COUNTRY_CODE_INFOLEVEL = (PARMNUM_BASE_INFOLEVEL + USER_COUNTRY_CODE_PARMNUM);
  {$EXTERNALSYM USER_CODE_PAGE_INFOLEVEL}
  USER_CODE_PAGE_INFOLEVEL = (PARMNUM_BASE_INFOLEVEL + USER_CODE_PAGE_PARMNUM);
  {$EXTERNALSYM USER_PRIMARY_GROUP_INFOLEVEL}
  USER_PRIMARY_GROUP_INFOLEVEL = (PARMNUM_BASE_INFOLEVEL + USER_PRIMARY_GROUP_PARMNUM);
//  {$EXTERNALSYM USER_POSIX_ID_INFOLEVEL}
//  USER_POSIX_ID_INFOLEVEL = (PARMNUM_BASE_INFOLEVEL + USER_POSIX_ID_PARMNUM);
  {$EXTERNALSYM USER_HOME_DIR_DRIVE_INFOLEVEL}
  USER_HOME_DIR_DRIVE_INFOLEVEL = (PARMNUM_BASE_INFOLEVEL + USER_HOME_DIR_DRIVE_PARMNUM);

//  For SetInfo call (parmnum 0) when password change not required

  {$EXTERNALSYM NULL_USERSETINFO_PASSWD}
  NULL_USERSETINFO_PASSWD =    '              ';

  {$EXTERNALSYM TIMEQ_FOREVER}
  TIMEQ_FOREVER               = DWORD(-1);
  {$EXTERNALSYM USER_MAXSTORAGE_UNLIMITED}
  USER_MAXSTORAGE_UNLIMITED   = DWORD(-1);
  {$EXTERNALSYM USER_NO_LOGOFF}
  USER_NO_LOGOFF              = DWORD(-1);
  {$EXTERNALSYM UNITS_PER_DAY}
  UNITS_PER_DAY               = 24;
  {$EXTERNALSYM UNITS_PER_WEEK}
  UNITS_PER_WEEK              = UNITS_PER_DAY * 7;

// Privilege levels (USER_INFO_X field usriX_priv (X = 0/1)).

  {$EXTERNALSYM USER_PRIV_MASK}
  USER_PRIV_MASK      = $3;
  {$EXTERNALSYM USER_PRIV_GUEST}
  USER_PRIV_GUEST     = 0;
  {$EXTERNALSYM USER_PRIV_USER}
  USER_PRIV_USER      = 1;
  {$EXTERNALSYM USER_PRIV_ADMIN}
  USER_PRIV_ADMIN     = 2;

// user modals related defaults

  {$EXTERNALSYM MAX_PASSWD_LEN}
  MAX_PASSWD_LEN      = PWLEN;
  {$EXTERNALSYM DEF_MIN_PWLEN}
  DEF_MIN_PWLEN       = 6;
  {$EXTERNALSYM DEF_PWUNIQUENESS}
  DEF_PWUNIQUENESS    = 5;
  {$EXTERNALSYM DEF_MAX_PWHIST}
  DEF_MAX_PWHIST      = 8;

  {$EXTERNALSYM DEF_MAX_PWAGE}
  DEF_MAX_PWAGE       = TIMEQ_FOREVER; // forever
  {$EXTERNALSYM DEF_MIN_PWAGE}
  DEF_MIN_PWAGE       = 0;             // 0 days
  {$EXTERNALSYM DEF_FORCE_LOGOFF}
  DEF_FORCE_LOGOFF    = MAXDWORD;      // never
  {$EXTERNALSYM DEF_MAX_BADPW}
  DEF_MAX_BADPW       = 0;             // no limit
  {$EXTERNALSYM ONE_DAY}
  ONE_DAY             = 01*24*3600;    // 01 day

// User Logon Validation (codes returned)

  {$EXTERNALSYM VALIDATED_LOGON}
  VALIDATED_LOGON         = 0;
  {$EXTERNALSYM PASSWORD_EXPIRED}
  PASSWORD_EXPIRED        = 2;
  {$EXTERNALSYM NON_VALIDATED_LOGON}
  NON_VALIDATED_LOGON     = 3;

  {$EXTERNALSYM VALID_LOGOFF}
  VALID_LOGOFF            = 1;

// parmnum manifests for user modals

  {$EXTERNALSYM MODALS_MIN_PASSWD_LEN_PARMNUM}
  MODALS_MIN_PASSWD_LEN_PARMNUM       = 1;
  {$EXTERNALSYM MODALS_MAX_PASSWD_AGE_PARMNUM}
  MODALS_MAX_PASSWD_AGE_PARMNUM       = 2;
  {$EXTERNALSYM MODALS_MIN_PASSWD_AGE_PARMNUM}
  MODALS_MIN_PASSWD_AGE_PARMNUM       = 3;
  {$EXTERNALSYM MODALS_FORCE_LOGOFF_PARMNUM}
  MODALS_FORCE_LOGOFF_PARMNUM         = 4;
  {$EXTERNALSYM MODALS_PASSWD_HIST_LEN_PARMNUM}
  MODALS_PASSWD_HIST_LEN_PARMNUM      = 5;
  {$EXTERNALSYM MODALS_ROLE_PARMNUM}
  MODALS_ROLE_PARMNUM                 = 6;
  {$EXTERNALSYM MODALS_PRIMARY_PARMNUM}
  MODALS_PRIMARY_PARMNUM              = 7;
  {$EXTERNALSYM MODALS_DOMAIN_NAME_PARMNUM}
  MODALS_DOMAIN_NAME_PARMNUM          = 8;
  {$EXTERNALSYM MODALS_DOMAIN_ID_PARMNUM}
  MODALS_DOMAIN_ID_PARMNUM            = 9;
  {$EXTERNALSYM MODALS_LOCKOUT_DURATION_PARMNUM}
  MODALS_LOCKOUT_DURATION_PARMNUM     = 10;
  {$EXTERNALSYM MODALS_LOCKOUT_OBSERVATION_WINDOW_PARMNUM}
  MODALS_LOCKOUT_OBSERVATION_WINDOW_PARMNUM = 11;
  {$EXTERNALSYM MODALS_LOCKOUT_THRESHOLD_PARMNUM}
  MODALS_LOCKOUT_THRESHOLD_PARMNUM    = 12;

// the new infolevel counterparts of the old info level + parmnum

  {$EXTERNALSYM MODALS_MIN_PASSWD_LEN_INFOLEVEL}
  MODALS_MIN_PASSWD_LEN_INFOLEVEL = (PARMNUM_BASE_INFOLEVEL + MODALS_MIN_PASSWD_LEN_PARMNUM);
  {$EXTERNALSYM MODALS_MAX_PASSWD_AGE_INFOLEVEL}
  MODALS_MAX_PASSWD_AGE_INFOLEVEL = (PARMNUM_BASE_INFOLEVEL + MODALS_MAX_PASSWD_AGE_PARMNUM);
  {$EXTERNALSYM MODALS_MIN_PASSWD_AGE_INFOLEVEL}
  MODALS_MIN_PASSWD_AGE_INFOLEVEL = (PARMNUM_BASE_INFOLEVEL + MODALS_MIN_PASSWD_AGE_PARMNUM);
  {$EXTERNALSYM MODALS_FORCE_LOGOFF_INFOLEVEL}
  MODALS_FORCE_LOGOFF_INFOLEVEL = (PARMNUM_BASE_INFOLEVEL + MODALS_FORCE_LOGOFF_PARMNUM);
  {$EXTERNALSYM MODALS_PASSWD_HIST_LEN_INFOLEVEL}
  MODALS_PASSWD_HIST_LEN_INFOLEVEL = (PARMNUM_BASE_INFOLEVEL + MODALS_PASSWD_HIST_LEN_PARMNUM);
  {$EXTERNALSYM MODALS_ROLE_INFOLEVEL}
  MODALS_ROLE_INFOLEVEL = (PARMNUM_BASE_INFOLEVEL + MODALS_ROLE_PARMNUM);
  {$EXTERNALSYM MODALS_PRIMARY_INFOLEVEL}
  MODALS_PRIMARY_INFOLEVEL = (PARMNUM_BASE_INFOLEVEL + MODALS_PRIMARY_PARMNUM);
  {$EXTERNALSYM MODALS_DOMAIN_NAME_INFOLEVEL}
  MODALS_DOMAIN_NAME_INFOLEVEL = (PARMNUM_BASE_INFOLEVEL + MODALS_DOMAIN_NAME_PARMNUM);
  {$EXTERNALSYM MODALS_DOMAIN_ID_INFOLEVEL}
  MODALS_DOMAIN_ID_INFOLEVEL = (PARMNUM_BASE_INFOLEVEL + MODALS_DOMAIN_ID_PARMNUM);


// Group Class

// Function Prototypes

{$EXTERNALSYM NetGroupAdd}
function NetGroupAdd(servername: LPCWSTR; level: DWORD; buf: Pointer;
  parm_err: PDWORD): NET_API_STATUS; stdcall;

{$EXTERNALSYM NetGroupAddUser}
function NetGroupAddUser(servername: LPCWSTR; GroupName: LPCWSTR;
  username: LPCWSTR): NET_API_STATUS; stdcall;

{$EXTERNALSYM NetGroupEnum}
function NetGroupEnum(servername: LPCWSTR; level: DWORD; var bufptr: Pointer;
  prefmaxlen: DWORD; var entriesread: DWORD; var totalentries: DWORD;
  resume_handle: PDWORD): NET_API_STATUS; stdcall;

{$EXTERNALSYM NetGroupGetInfo}
function NetGroupGetInfo(servername: LPCWSTR; groupname: LPCWSTR; level: DWORD;
  var bufptr: Pointer): NET_API_STATUS; stdcall;

{$EXTERNALSYM NetGroupSetInfo}
function NetGroupSetInfo(servername: LPCWSTR; groupname: LPCWSTR; level: DWORD;
  buf: Pointer; parm_err: PDWORD): NET_API_STATUS; stdcall;

{$EXTERNALSYM NetGroupDel}
function NetGroupDel(servername, groupname: LPCWSTR): NET_API_STATUS; stdcall;

{$EXTERNALSYM NetGroupDelUser}
function NetGroupDelUser(servername: LPCWSTR; GroupName: LPCWSTR;
  Username: LPCWSTR): NET_API_STATUS; stdcall;

{$EXTERNALSYM NetGroupGetUsers}
function NetGroupGetUsers(servername: LPCWSTR; groupname: LPCWSTR; level: DWORD;
  var bufptr: Pointer; prefmaxlen: DWORD; var entriesread: DWORD;
  var totalentries: DWORD; ResumeHandle: PDWORD): NET_API_STATUS; stdcall;

{$EXTERNALSYM NetGroupSetUsers}
function NetGroupSetUsers(servername: LPCWSTR; groupname: LPCWSTR; level: DWORD;
  buf: Pointer; totalentries: DWORD): NET_API_STATUS; stdcall;

//  Data Structures - Group

type
  PGroupInfo0 = ^TGroupInfo0;
  {$EXTERNALSYM _GROUP_INFO_0}
  _GROUP_INFO_0 = record
    grpi0_name: LPWSTR;
  end;
  TGroupInfo0 = _GROUP_INFO_0;
  {$EXTERNALSYM GROUP_INFO_0}
  GROUP_INFO_0 = _GROUP_INFO_0;

  PGroupInfo1 = ^TGroupInfo1;
  {$EXTERNALSYM _GROUP_INFO_1}
  _GROUP_INFO_1 = record
    grpi1_name: LPWSTR;
    grpi1_comment: LPWSTR;
  end;
  TGroupInfo1 = _GROUP_INFO_1;
  {$EXTERNALSYM GROUP_INFO_1}
  GROUP_INFO_1 = _GROUP_INFO_1;

  PGroupInfo2 = ^TGroupInfo2;
  {$EXTERNALSYM _GROUP_INFO_2}
  _GROUP_INFO_2 = record
    grpi2_name: LPWSTR;
    grpi2_comment: LPWSTR;
    grpi2_group_id: DWORD;
    grpi2_attributes: DWORD;
  end;
  TGroupInfo2 = _GROUP_INFO_2;
  {$EXTERNALSYM GROUP_INFO_2}
  GROUP_INFO_2 = _GROUP_INFO_2;

  PGroupInfo1002 = ^TGroupInfo1002;
  {$EXTERNALSYM _GROUP_INFO_1002}
  _GROUP_INFO_1002 = record
    grpi1002_comment: LPWSTR;
  end;
  TGroupInfo1002 = _GROUP_INFO_1002;
  {$EXTERNALSYM GROUP_INFO_1002}
  GROUP_INFO_1002 = _GROUP_INFO_1002;

  PGroupInfo1005 = ^TGroupInfo1005;
  {$EXTERNALSYM _GROUP_INFO_1005}
  _GROUP_INFO_1005 = record
    grpi1005_attributes: DWORD;
  end;
  TGroupInfo1005 = _GROUP_INFO_1005;
  {$EXTERNALSYM GROUP_INFO_1005}
  GROUP_INFO_1005 = _GROUP_INFO_1005;

  PGroupUsersInfo0 = ^TGroupUsersInfo0;
  {$EXTERNALSYM _GROUP_USERS_INFO_0}
  _GROUP_USERS_INFO_0 = record
    grui0_name: LPWSTR;
  end;
  TGroupUsersInfo0 = _GROUP_USERS_INFO_0;
  {$EXTERNALSYM GROUP_USERS_INFO_0}
  GROUP_USERS_INFO_0 = _GROUP_USERS_INFO_0;

  PGroupUsersInfo1 = ^TGroupUsersInfo1;
  {$EXTERNALSYM _GROUP_USERS_INFO_1}
  _GROUP_USERS_INFO_1 = record
    grui1_name: LPWSTR;
    grui1_attributes: DWORD;
  end;
  TGroupUsersInfo1 = _GROUP_USERS_INFO_1;
  {$EXTERNALSYM GROUP_USERS_INFO_1}
  GROUP_USERS_INFO_1 = _GROUP_USERS_INFO_1;

//
// Special Values and Constants - Group
//

const
  {$EXTERNALSYM GROUPIDMASK}
  GROUPIDMASK                 = $8000;      // MSB set if uid refers;
                                            // to a group

// Predefined group for all normal users, administrators and guests
// LOCAL is a special group for pinball local security.

  {$EXTERNALSYM GROUP_SPECIALGRP_USERS}
  GROUP_SPECIALGRP_USERS = 'USERS';
  {$EXTERNALSYM GROUP_SPECIALGRP_ADMINS}
  GROUP_SPECIALGRP_ADMINS = 'ADMINS';
  {$EXTERNALSYM GROUP_SPECIALGRP_GUESTS}
  GROUP_SPECIALGRP_GUESTS = 'GUESTS';
  {$EXTERNALSYM GROUP_SPECIALGRP_LOCAL}
  GROUP_SPECIALGRP_LOCAL = 'LOCAL';

// parmnum manifests for SetInfo calls (only comment is settable)

  {$EXTERNALSYM GROUP_ALL_PARMNUM}
  GROUP_ALL_PARMNUM           = 0;
  {$EXTERNALSYM GROUP_NAME_PARMNUM}
  GROUP_NAME_PARMNUM          = 1;
  {$EXTERNALSYM GROUP_COMMENT_PARMNUM}
  GROUP_COMMENT_PARMNUM       = 2;
  {$EXTERNALSYM GROUP_ATTRIBUTES_PARMNUM}
  GROUP_ATTRIBUTES_PARMNUM    = 3;

// the new infolevel counterparts of the old info level + parmnum

  {$EXTERNALSYM GROUP_ALL_INFOLEVEL}
  GROUP_ALL_INFOLEVEL = (PARMNUM_BASE_INFOLEVEL + GROUP_ALL_PARMNUM);
  {$EXTERNALSYM GROUP_NAME_INFOLEVEL}
  GROUP_NAME_INFOLEVEL = (PARMNUM_BASE_INFOLEVEL + GROUP_NAME_PARMNUM);
  {$EXTERNALSYM GROUP_COMMENT_INFOLEVEL}
  GROUP_COMMENT_INFOLEVEL = (PARMNUM_BASE_INFOLEVEL + GROUP_COMMENT_PARMNUM);
  {$EXTERNALSYM GROUP_ATTRIBUTES_INFOLEVEL}
  GROUP_ATTRIBUTES_INFOLEVEL = (PARMNUM_BASE_INFOLEVEL + GROUP_ATTRIBUTES_PARMNUM);
//  {$EXTERNALSYM GROUP_POSIX_ID_INFOLEVEL}
//  GROUP_POSIX_ID_INFOLEVEL = (PARMNUM_BASE_INFOLEVEL + GROUP_POSIX_ID_PARMNUM);

// LocalGroup Class

// Function Prototypes

{$EXTERNALSYM NetLocalGroupAdd}
function NetLocalGroupAdd(servername: LPCWSTR; level: DWORD; buf: Pointer;
  parm_err: PDWORD): NET_API_STATUS; stdcall;

{$EXTERNALSYM NetLocalGroupAddMember}
function NetLocalGroupAddMember(servername: LPCWSTR; groupname: LPCWSTR;
  membersid: PSID): NET_API_STATUS; stdcall;

{$EXTERNALSYM NetLocalGroupEnum}
function NetLocalGroupEnum(servername: LPCWSTR; level: DWORD; var bufptr: Pointer;
  prefmaxlen: DWORD; var entriesread: DWORD; var totalentries: DWORD;
  resumehandle: PDWORD): NET_API_STATUS; stdcall;

{$EXTERNALSYM NetLocalGroupGetInfo}
function NetLocalGroupGetInfo(servername: LPCWSTR; groupname: LPCWSTR;
  level: DWORD; var bufptr: Pointer): NET_API_STATUS; stdcall;

{$EXTERNALSYM NetLocalGroupSetInfo}
function NetLocalGroupSetInfo(servername: LPCWSTR; groupname: LPCWSTR;
  level: DWORD; buf: Pointer; parm_err: PDWORD): NET_API_STATUS; stdcall;

{$EXTERNALSYM NetLocalGroupDel}
function NetLocalGroupDel(servername, groupname: LPCWSTR): NET_API_STATUS; stdcall;

{$EXTERNALSYM NetLocalGroupDelMember}
function NetLocalGroupDelMember(servername: LPCWSTR; groupname: LPCWSTR;
  membersid: PSID): NET_API_STATUS; stdcall;

{$EXTERNALSYM NetLocalGroupGetMembers}
function NetLocalGroupGetMembers(servername: LPCWSTR; localgroupname: LPCWSTR;
  level: DWORD; var bufptr: Pointer; prefmaxlen: DWORD; var entriesread: DWORD;
  var totalentries: DWORD; resumehandle: PDWORD): NET_API_STATUS; stdcall;

{$EXTERNALSYM NetLocalGroupSetMembers}
function NetLocalGroupSetMembers(servername: LPCWSTR; groupname: LPCWSTR;
  level: DWORD; buf: Pointer; totalentries: DWORD): NET_API_STATUS; stdcall;

{$EXTERNALSYM NetLocalGroupAddMembers}
function NetLocalGroupAddMembers(servername: LPCWSTR; groupname: LPCWSTR;
  level: DWORD; buf: Pointer; totalentries: DWORD): NET_API_STATUS; stdcall;

{$EXTERNALSYM NetLocalGroupDelMembers}
function NetLocalGroupDelMembers(servername: LPCWSTR; groupname: LPCWSTR;
  level: DWORD; buf: Pointer; totalentries: DWORD): NET_API_STATUS; stdcall;

//  Data Structures - LocalGroup

type
  PLocalGroupInfo0 = ^TLocalGroupInfo0;
  {$EXTERNALSYM _LOCALGROUP_INFO_0}
  _LOCALGROUP_INFO_0 = record
    lgrpi0_name: LPWSTR;
  end;
  TLocalGroupInfo0 = _LOCALGROUP_INFO_0;
  {$EXTERNALSYM LOCALGROUP_INFO_0}
  LOCALGROUP_INFO_0 = _LOCALGROUP_INFO_0;

  PLocalGroupInfo1 = ^TLocalGroupInfo1;
  {$EXTERNALSYM _LOCALGROUP_INFO_1}
  _LOCALGROUP_INFO_1 = record
    lgrpi1_name: LPWSTR;
    lgrpi1_comment: LPWSTR;
  end;
  TLocalGroupInfo1 = _LOCALGROUP_INFO_1;
  {$EXTERNALSYM LOCALGROUP_INFO_1}
  LOCALGROUP_INFO_1 = _LOCALGROUP_INFO_1;

  PLocalGroupInfo1002 = ^TLocalGroupInfo1002;
  {$EXTERNALSYM _LOCALGROUP_INFO_1002}
  _LOCALGROUP_INFO_1002 = record
    lgrpi1002_comment: LPWSTR;
  end;
  TLocalGroupInfo1002 = _LOCALGROUP_INFO_1002;
  {$EXTERNALSYM LOCALGROUP_INFO_1002}
  LOCALGROUP_INFO_1002 = _LOCALGROUP_INFO_1002;

  PLocalGroupMembersInfo0 = ^TLocalGroupMembersInfo0;
  {$EXTERNALSYM _LOCALGROUP_MEMBERS_INFO_0}
  _LOCALGROUP_MEMBERS_INFO_0 = record
    lgrmi0_sid: PSID;
  end;
  TLocalGroupMembersInfo0 = _LOCALGROUP_MEMBERS_INFO_0;
  {$EXTERNALSYM LOCALGROUP_MEMBERS_INFO_0}
  LOCALGROUP_MEMBERS_INFO_0 = _LOCALGROUP_MEMBERS_INFO_0;

  PLocalGroupMembersInfo1 = ^TLocalGroupMembersInfo1;
  {$EXTERNALSYM _LOCALGROUP_MEMBERS_INFO_1}
  _LOCALGROUP_MEMBERS_INFO_1 = record
    lgrmi1_sid: PSID;
    lgrmi1_sidusage: SID_NAME_USE;
    lgrmi1_name: LPWSTR;
  end;
  TLocalGroupMembersInfo1 = _LOCALGROUP_MEMBERS_INFO_1;
  {$EXTERNALSYM LOCALGROUP_MEMBERS_INFO_1}
  LOCALGROUP_MEMBERS_INFO_1 = _LOCALGROUP_MEMBERS_INFO_1;

  PLocalGroupMembersInfo2 = ^TLocalGroupMembersInfo2;
  {$EXTERNALSYM _LOCALGROUP_MEMBERS_INFO_2}
  _LOCALGROUP_MEMBERS_INFO_2 = record
    lgrmi2_sid: PSID;
    lgrmi2_sidusage: SID_NAME_USE;
    lgrmi2_domainandname: LPWSTR;
  end;
  TLocalGroupMembersInfo2 = _LOCALGROUP_MEMBERS_INFO_2;
  {$EXTERNALSYM LOCALGROUP_MEMBERS_INFO_2}
  LOCALGROUP_MEMBERS_INFO_2 = _LOCALGROUP_MEMBERS_INFO_2;

  PLocalGroupMembersInfo3 = ^TLocalGroupMembersInfo3;
  {$EXTERNALSYM _LOCALGROUP_MEMBERS_INFO_3}
  _LOCALGROUP_MEMBERS_INFO_3 = record
    lgrmi3_domainandname: LPWSTR;
  end;
  TLocalGroupMembersInfo3 = _LOCALGROUP_MEMBERS_INFO_3;
  {$EXTERNALSYM LOCALGROUP_MEMBERS_INFO_3}
  LOCALGROUP_MEMBERS_INFO_3 = _LOCALGROUP_MEMBERS_INFO_3;

  PLocalGroupUserInfo0 = ^TLocalGroupUserInfo0;
  {$EXTERNALSYM _LOCALGROUP_USERS_INFO_0}
  _LOCALGROUP_USERS_INFO_0 = record
    lgrui0_name: LPWSTR;
  end;
  TLocalGroupUserInfo0 = _LOCALGROUP_USERS_INFO_0;
  {$EXTERNALSYM LOCALGROUP_USERS_INFO_0}
  LOCALGROUP_USERS_INFO_0 = _LOCALGROUP_USERS_INFO_0;

const
  {$EXTERNALSYM LOCALGROUP_NAME_PARMNUM}
  LOCALGROUP_NAME_PARMNUM = 1;
  {$EXTERNALSYM LOCALGROUP_COMMENT_PARMNUM}
  LOCALGROUP_COMMENT_PARMNUM = 2;

// Display Information APIs

{$EXTERNALSYM NetQueryDisplayInformation}
function NetQueryDisplayInformation(ServerName: LPCWSTR; Level: DWORD;
  Index: DWORD; EntriesRequested: DWORD; PreferredMaximumLength: DWORD;
  var ReturnedEntryCount: DWORD; var SortedBuffer: Pointer): NET_API_STATUS; stdcall;

{$EXTERNALSYM NetGetDisplayInformationIndex}
function NetGetDisplayInformationIndex(ServerName: LPCWSTR; Level: DWORD;
  Prefix: LPCWSTR; var Index: DWORD): NET_API_STATUS; stdcall;

// QueryDisplayInformation levels

type
  PNetDisplayUser = ^TNetDisplayUser;
  {$EXTERNALSYM _NET_DISPLAY_USER}
  _NET_DISPLAY_USER = record
    usri1_name: LPWSTR;
    usri1_comment: LPWSTR;
    usri1_flags: DWORD;
    usri1_full_name: LPWSTR;
    usri1_user_id: DWORD;
    usri1_next_index: DWORD;
  end;
  TNetDisplayUser = _NET_DISPLAY_USER;
  {$EXTERNALSYM NET_DISPLAY_USER}
  NET_DISPLAY_USER = _NET_DISPLAY_USER;

  PNetDisplayMachine = ^TNetDisplayMachine;
  {$EXTERNALSYM _NET_DISPLAY_MACHINE}
  _NET_DISPLAY_MACHINE = record
    usri2_name: LPWSTR;
    usri2_comment: LPWSTR;
    usri2_flags: DWORD;
    usri2_user_id: DWORD;
    usri2_next_index: DWORD;
  end;
  TNetDisplayMachine = _NET_DISPLAY_MACHINE;
  {$EXTERNALSYM NET_DISPLAY_MACHINE}
  NET_DISPLAY_MACHINE = _NET_DISPLAY_MACHINE;

  PNetDisplayGroup = ^TNetDisplayGroup;
  {$EXTERNALSYM _NET_DISPLAY_GROUP}
  _NET_DISPLAY_GROUP = record
    grpi3_name: LPWSTR;
    grpi3_comment: LPWSTR;
    grpi3_group_id: DWORD;
    grpi3_attributes: DWORD;
    grpi3_next_index: DWORD;
  end;
  TNetDisplayGroup = _NET_DISPLAY_GROUP;
  {$EXTERNALSYM NET_DISPLAY_GROUP}
  NET_DISPLAY_GROUP = _NET_DISPLAY_GROUP;

// Access Class

// Function Prototypes - Access

// The NetAccess APIs are only available to downlevel

//#define NetAccessAdd RxNetAccessAdd

{$EXTERNALSYM NetAccessAdd}
function NetAccessAdd(servername: LPCWSTR; level: DWORD; buf: Pointer;
  parm_err: PDWORD): NET_API_STATUS; stdcall;

//#define NetAccessEnum RxNetAccessEnum

{$EXTERNALSYM NetAccessEnum}
function NetAccessEnum(servername: LPCWSTR; BasePath: LPCWSTR; Recursive: DWORD;
  level: DWORD; bufptr: Pointer; prefmaxlen: DWORD; var entriesread: DWORD;
  var totalentries: DWORD; resume_handle: PDWORD): NET_API_STATUS; stdcall;

//#define NetAccessGetInfo RxNetAccessGetInfo

{$EXTERNALSYM NetAccessGetInfo}
function NetAccessGetInfo(servername: LPCWSTR; resource: LPCWSTR; level: DWORD;
  bufptr: Pointer): NET_API_STATUS; stdcall;

//#define NetAccessSetInfo RxNetAccessSetInfo

{$EXTERNALSYM NetAccessSetInfo}
function NetAccessSetInfo(servername: LPCWSTR; resource: LPCWSTR; level: DWORD;
  buf: Pointer; parm_err: PDWORD): NET_API_STATUS; stdcall;

//#define NetAccessDel RxNetAccessDel

{$EXTERNALSYM NetAccessDel}
function NetAccessDel(servername, resource: LPCWSTR): NET_API_STATUS; stdcall;

//#define NetAccessGetUserPerms RxNetAccessGetUserPerms

{$EXTERNALSYM NetAccessGetUserPerms}
function NetAccessGetUserPerms(servername: LPCWSTR; UGname: LPCWSTR;
  resource: LPCWSTR; var Perms: DWORD): NET_API_STATUS; stdcall;

//
// Data Structures - Access
//
type
  PAccessInfo0 = ^TAccessInfo0;
  {EXTERNALSYM _ACCESS_INFO_0}
  _ACCESS_INFO_0 = record
    acc0_resource_name: LPWSTR;
  end;
  TAccessInfo0 = _ACCESS_INFO_0;
  {$EXTERNALSYM ACCESS_INFO_0}
  ACCESS_INFO_0 = _ACCESS_INFO_0;

  PAccessInfo1 = ^TAccessInfo1;
  {EXTERNALSYM _ACCESS_INFO_1}
  _ACCESS_INFO_1 = record
    acc1_resource_name: LPWSTR;
    acc1_attr: DWORD;
    acc1_count: DWORD;
  end;
  TAccessInfo1 = _ACCESS_INFO_1;
  {$EXTERNALSYM ACCESS_INFO_1}
  ACCESS_INFO_1 = _ACCESS_INFO_1;

  PAccessInfo1002 = ^TAccessInfo1002;
  {EXTERNALSYM _ACCESS_INFO_1002}
  _ACCESS_INFO_1002 = record
    acc1002_attr: DWORD;
  end;
  TAccessInfo1002 = _ACCESS_INFO_1002;
  {$EXTERNALSYM ACCESS_INFO_1002}
  ACCESS_INFO_1002 = _ACCESS_INFO_1002;

  PAccessList = ^TAccessList;
  {EXTERNALSYM _ACCESS_LIST}
  _ACCESS_LIST = record
    acl_ugname: LPWSTR;
    acl_access: DWORD;
  end;
  TAccessList = _ACCESS_LIST;
  {$EXTERNALSYM ACCESS_LIST}
  ACCESS_LIST = _ACCESS_LIST;

// Special Values and Constants - Access

// Maximum number of permission entries for each resource.

const
  {$EXTERNALSYM MAXPERMENTRIES}
  MAXPERMENTRIES = 64;

//  Bit values for the access permissions.  ACCESS_ALL is a handy
//  way to specify maximum permissions.  These are used in
//  acl_access field of access_list structures.

  {$EXTERNALSYM ACCESS_NONE}
  ACCESS_NONE = 0;

  {$EXTERNALSYM ACCESS_READ}
  ACCESS_READ         = $01;
  {$EXTERNALSYM ACCESS_WRITE}
  ACCESS_WRITE        = $02;
  {$EXTERNALSYM ACCESS_CREATE}
  ACCESS_CREATE       = $04;
  {$EXTERNALSYM ACCESS_EXEC}
  ACCESS_EXEC         = $08;
  {$EXTERNALSYM ACCESS_DELETE}
  ACCESS_DELETE       = $10;
  {$EXTERNALSYM ACCESS_ATRIB}
  ACCESS_ATRIB        = $20;
  {$EXTERNALSYM ACCESS_PERM}
  ACCESS_PERM         = $40;

  {$EXTERNALSYM ACCESS_GROUP}
  ACCESS_GROUP        = $8000;

  {$EXTERNALSYM ACCESS_ALL}
  ACCESS_ALL = ACCESS_READ or ACCESS_WRITE or ACCESS_CREATE or ACCESS_EXEC or
    ACCESS_DELETE or ACCESS_ATRIB or ACCESS_PERM;

// Bit values for the acc1_attr field of the ACCESS_INFO_1 structure.

  {$EXTERNALSYM ACCESS_AUDIT}
  ACCESS_AUDIT        = $1;

  {$EXTERNALSYM ACCESS_SUCCESS_OPEN}
  ACCESS_SUCCESS_OPEN         = $10;
  {$EXTERNALSYM ACCESS_SUCCESS_WRITE}
  ACCESS_SUCCESS_WRITE        = $20;
  {$EXTERNALSYM ACCESS_SUCCESS_DELETE}
  ACCESS_SUCCESS_DELETE       = $40;
  {$EXTERNALSYM ACCESS_SUCCESS_ACL}
  ACCESS_SUCCESS_ACL          = $80;
  {$EXTERNALSYM ACCESS_SUCCESS_MASK}
  ACCESS_SUCCESS_MASK         = $F0;

  {$EXTERNALSYM ACCESS_FAIL_OPEN}
  ACCESS_FAIL_OPEN            = $100;
  {$EXTERNALSYM ACCESS_FAIL_WRITE}
  ACCESS_FAIL_WRITE           = $200;
  {$EXTERNALSYM ACCESS_FAIL_DELETE}
  ACCESS_FAIL_DELETE          = $400;
  {$EXTERNALSYM ACCESS_FAIL_ACL}
  ACCESS_FAIL_ACL             = $800;
  {$EXTERNALSYM ACCESS_FAIL_MASK}
  ACCESS_FAIL_MASK            = $F00;

  {$EXTERNALSYM ACCESS_FAIL_SHIFT}
  ACCESS_FAIL_SHIFT           = 4;

// Parmnum value for NetAccessSetInfo.

  {$EXTERNALSYM ACCESS_RESOURCE_NAME_PARMNUM}
  ACCESS_RESOURCE_NAME_PARMNUM    = 1;
  {$EXTERNALSYM ACCESS_ATTR_PARMNUM}
  ACCESS_ATTR_PARMNUM             = 2;
  {$EXTERNALSYM ACCESS_COUNT_PARMNUM}
  ACCESS_COUNT_PARMNUM            = 3;
  {$EXTERNALSYM ACCESS_ACCESS_LIST_PARMNUM}
  ACCESS_ACCESS_LIST_PARMNUM      = 4;

// the new infolevel counterparts of the old info level + parmnum

  {$EXTERNALSYM ACCESS_RESOURCE_NAME_INFOLEVEL}
  ACCESS_RESOURCE_NAME_INFOLEVEL = (PARMNUM_BASE_INFOLEVEL + ACCESS_RESOURCE_NAME_PARMNUM);
  {$EXTERNALSYM ACCESS_ATTR_INFOLEVEL}
  ACCESS_ATTR_INFOLEVEL = (PARMNUM_BASE_INFOLEVEL + ACCESS_ATTR_PARMNUM);
  {$EXTERNALSYM ACCESS_COUNT_INFOLEVEL}
  ACCESS_COUNT_INFOLEVEL = (PARMNUM_BASE_INFOLEVEL + ACCESS_COUNT_PARMNUM);
  {$EXTERNALSYM ACCESS_ACCESS_LIST_INFOLEVEL}
  ACCESS_ACCESS_LIST_INFOLEVEL = (PARMNUM_BASE_INFOLEVEL + ACCESS_ACCESS_LIST_PARMNUM);

// ACCESS_LETTERS defines a letter for each bit position in
// the acl_access field of struct access_list.  Note that some
// bits have a corresponding letter of ' ' (space).

  {$EXTERNALSYM ACCESS_LETTERS}
  ACCESS_LETTERS = 'RWCXDAP         ';


// Domain Class

// Function Prototypes - Domain

{$EXTERNALSYM NetGetDCName}
function NetGetDCName(servername: LPCWSTR; domainname: LPCWSTR;
  bufptr: Pointer): NET_API_STATUS; stdcall;

{$EXTERNALSYM NetGetAnyDCName}
function NetGetAnyDCName(servername: LPCWSTR; domainname: LPCWSTR;
  bufptr: Pointer): NET_API_STATUS; stdcall;

{$EXTERNALSYM I_NetLogonControl}
function I_NetLogonControl(ServerName: LPCWSTR; FunctionCode: DWORD;
  QueryLevel: DWORD; Buffer: Pointer): NET_API_STATUS; stdcall;

{$EXTERNALSYM I_NetLogonControl2}
function I_NetLogonControl2(ServerName: LPCWSTR; FunctionCode: DWORD;
  QueryLevel: DWORD; Data: Pointer; Buffer: Pointer): NET_API_STATUS; stdcall;

type
  PNtStatus = ^TNtStatus;
  NTSTATUS = LongInt;
  {$EXTERNALSYM NTSTATUS}
  TNtStatus = NTSTATUS;

{$EXTERNALSYM NetEnumerateTrustedDomains}
function NetEnumerateTrustedDomains(ServerName: LPWSTR; var DomainNames: LPWSTR): NET_API_STATUS; stdcall;

// Special Values and Constants - Domain

// FunctionCode values for I_NetLogonControl.
// NOTE : if you change the following NETLOGON_CONTROL_* values,
// change them in net\svcdlls\logonsrv\logon.idl file also.

const
  {$EXTERNALSYM NETLOGON_CONTROL_QUERY}
  NETLOGON_CONTROL_QUERY         = 1;    // No-op: just query
  {$EXTERNALSYM NETLOGON_CONTROL_REPLICATE}
  NETLOGON_CONTROL_REPLICATE     = 2;    // Force replicate on BDC
  {$EXTERNALSYM NETLOGON_CONTROL_SYNCHRONIZE}
  NETLOGON_CONTROL_SYNCHRONIZE   = 3;    // Force synchronize on BDC
  {$EXTERNALSYM NETLOGON_CONTROL_PDC_REPLICATE}
  NETLOGON_CONTROL_PDC_REPLICATE = 4;    // Force PDC to broadcast change
  {$EXTERNALSYM NETLOGON_CONTROL_REDISCOVER}
  NETLOGON_CONTROL_REDISCOVER    = 5;    // Force to re-discover trusted domain DCs
  {$EXTERNALSYM NETLOGON_CONTROL_TC_QUERY}
  NETLOGON_CONTROL_TC_QUERY      = 6;    // Query status of specified trusted channel status
  {$EXTERNALSYM NETLOGON_CONTROL_TRANSPORT_NOTIFY}
  NETLOGON_CONTROL_TRANSPORT_NOTIFY = 7; // Notify netlogon that a new transport has come online
  {$EXTERNALSYM NETLOGON_CONTROL_FIND_USER}
  NETLOGON_CONTROL_FIND_USER     = 8;    // Find named user in a trusted domain
  {$EXTERNALSYM NETLOGON_CONTROL_CHANGE_PASSWORD}
  NETLOGON_CONTROL_CHANGE_PASSWORD  = 9;  // Change machine password on a secure channel to a trusted domain


// Debug function codes

  {$EXTERNALSYM NETLOGON_CONTROL_UNLOAD_NETLOGON_DLL}
  NETLOGON_CONTROL_UNLOAD_NETLOGON_DLL = $FFFB;
  {$EXTERNALSYM NETLOGON_CONTROL_BACKUP_CHANGE_LOG}
  NETLOGON_CONTROL_BACKUP_CHANGE_LOG   = $FFFC;
  {$EXTERNALSYM NETLOGON_CONTROL_TRUNCATE_LOG}
  NETLOGON_CONTROL_TRUNCATE_LOG        = $FFFD;
  {$EXTERNALSYM NETLOGON_CONTROL_SET_DBFLAG}
  NETLOGON_CONTROL_SET_DBFLAG          = $FFFE;
  {$EXTERNALSYM NETLOGON_CONTROL_BREAKPOINT}
  NETLOGON_CONTROL_BREAKPOINT          = $FFFF;

// Query level 1 for I_NetLogonControl

type
  PNetLogonInfo1 = ^TNetLogonInfo1;
  {$EXTERNALSYM _NETLOGON_INFO_1}
  _NETLOGON_INFO_1 = record
    netlog1_flags: DWORD;
    netlog1_pdc_connection_status: NET_API_STATUS;
  end;
  TNetLogonInfo1 = _NETLOGON_INFO_1;
  {$EXTERNALSYM NETLOGON_INFO_1}
  NETLOGON_INFO_1 = _NETLOGON_INFO_1;

  PNetLogonInfo2 = ^TNetLogonInfo2;
  {$EXTERNALSYM _NETLOGON_INFO_2}
  _NETLOGON_INFO_2 = record
    netlog2_flags: DWORD;
    netlog2_pdc_connection_status: NET_API_STATUS;
    netlog2_trusted_dc_name: LPWSTR;
    netlog2_tc_connection_status: NET_API_STATUS;
  end;
  TNetLogonInfo2 = _NETLOGON_INFO_2;
  {$EXTERNALSYM NETLOGON_INFO_2}
  NETLOGON_INFO_2 = _NETLOGON_INFO_2;

  PNetLogonInfo3 = ^TNetLogonInfo3;
  {$EXTERNALSYM _NETLOGON_INFO_3}
  _NETLOGON_INFO_3 = record
    netlog3_flags: DWORD;
    netlog3_logon_attempts: DWORD;
    netlog3_reserved1: DWORD;
    netlog3_reserved2: DWORD;
    netlog3_reserved3: DWORD;
    netlog3_reserved4: DWORD;
    netlog3_reserved5: DWORD;
  end;
  TNetLogonInfo3 = _NETLOGON_INFO_3;
  {$EXTERNALSYM NETLOGON_INFO_3}
  NETLOGON_INFO_3 = _NETLOGON_INFO_3;

  PNetLogonInfo4 = ^TNetLogonInfo4;
  {$EXTERNALSYM _NETLOGON_INFO_4}
  _NETLOGON_INFO_4 = record
    netlog4_trusted_dc_name: LPWSTR;
    netlog4_trusted_domain_name: LPWSTR;
  end;
  TNetLogonInfo4 = _NETLOGON_INFO_4;
  {$EXTERNALSYM NETLOGON_INFO_4}
  NETLOGON_INFO_4 = _NETLOGON_INFO_4;

// Values of netlog1_flags

const
  {$EXTERNALSYM NETLOGON_REPLICATION_NEEDED}
  NETLOGON_REPLICATION_NEEDED       = $01;  // Database is out of date
  {$EXTERNALSYM NETLOGON_REPLICATION_IN_PROGRESS}
  NETLOGON_REPLICATION_IN_PROGRESS  = $02;  // Replication is happening now
  {$EXTERNALSYM NETLOGON_FULL_SYNC_REPLICATION}
  NETLOGON_FULL_SYNC_REPLICATION    = $04;  // full sync replication required/progress
  {$EXTERNALSYM NETLOGON_REDO_NEEDED}
  NETLOGON_REDO_NEEDED              = $08;  // Redo of previous replication needed
  {$EXTERNALSYM NETLOGON_HAS_IP}
  NETLOGON_HAS_IP                   = $10;  // The trusted domain DC has an IP address
  {$EXTERNALSYM NETLOGON_HAS_TIMESERV}
  NETLOGON_HAS_TIMESERV             = $20;  // The trusted domain DC runs the Windows Time Service

// Translated from LMALERT.H

// Function Prototypes

{$EXTERNALSYM NetAlertRaise}
function NetAlertRaise(AlertEventName: LPCWSTR; Buffer: Pointer;
  BufferSize: DWORD): NET_API_STATUS; stdcall;

{$EXTERNALSYM NetAlertRaiseEx}
function NetAlertRaiseEx(AlertEventName: LPCWSTR; VariableInfo: Pointer;
  VariableInfoSize: DWORD; ServiceName: LPCWSTR): NET_API_STATUS; stdcall;

//  Data Structures

type
  PStdAlert = ^TStdAlert;
  {$EXTERNALSYM _STD_ALERT}
  _STD_ALERT = record
    alrt_timestamp: DWORD;
    alrt_eventname: packed array[0..EVLEN] of WCHAR;
    alrt_servicename: packed array[0..SNLEN] of WCHAR;
  end;
  TStdAlert = _STD_ALERT;
  STD_ALERT = _STD_ALERT;
  {$EXTERNALSYM STD_ALERT}

  PAdminOtherInfo = ^TAdminOtherInfo;
  {$EXTERNALSYM _ADMIN_OTHER_INFO}
  _ADMIN_OTHER_INFO = record
    alrtad_errcode: DWORD;
    alrtad_numstrings: DWORD;
  end;
  TAdminOtherInfo = _ADMIN_OTHER_INFO;
  ADMIN_OTHER_INFO = _ADMIN_OTHER_INFO;
  {$EXTERNALSYM ADMIN_OTHER_INFO}

  PErrorOtherInfo = ^TErrorOtherInfo;
  {$EXTERNALSYM _ERRLOG_OTHER_INFO}
  _ERRLOG_OTHER_INFO = record
    alrter_errcode: DWORD;
    alrter_offset: DWORD;
  end;
  TErrorOtherInfo = _ERRLOG_OTHER_INFO;
  ERRLOG_OTHER_INFO = _ERRLOG_OTHER_INFO;
  {$EXTERNALSYM ERRLOG_OTHER_INFO}

  PPrintOtherInfo = ^TPrintOtherInfo;
  {$EXTERNALSYM _PRINT_OTHER_INFO}
  _PRINT_OTHER_INFO = record
    alrtpr_jobid: DWORD;
    alrtpr_status: DWORD;
    alrtpr_submitted: DWORD;
    alrtpr_size: DWORD;
  end;
  TPrintOtherInfo = _PRINT_OTHER_INFO;
  PRINT_OTHER_INFO = _PRINT_OTHER_INFO;
  {$EXTERNALSYM PRINT_OTHER_INFO}

  PUserOtherInfo = ^TUserOtherInfo;
  {$EXTERNALSYM _USER_OTHER_INFO}
  _USER_OTHER_INFO = record
    alrtus_errcode: DWORD;
    alrtus_numstrings: DWORD;
  end;
  TUserOtherInfo = _USER_OTHER_INFO;
  USER_OTHER_INFO = _USER_OTHER_INFO;
  {$EXTERNALSYM USER_OTHER_INFO}

// Special Values and Constants

// Name of mailslot to send alert notifications

const
  {$EXTERNALSYM ALERTER_MAILSLOT}
  ALERTER_MAILSLOT = '\\.\MAILSLOT\Alerter';

// The following macro gives a pointer to the other_info data.
// It takes an alert structure and returns a pointer to structure
// beyond the standard portion.


  function ALERT_OTHER_INFO(x: Pointer): Pointer;
//((LPBYTE)(x) + sizeof(STD_ALERT))

// The following macro gives a pointer to the variable-length data.
// It takes a pointer to one of the other-info structs and returns a
// pointer to the variable data portion.

  function ALERT_VAR_DATA(const p): Pointer;
//((LPBYTE)(p) + sizeof(*p))

//      Names of standard Microsoft-defined alert events.

const

  {$EXTERNALSYM ALERT_PRINT_EVENT}
  ALERT_PRINT_EVENT           = 'PRINTING';
  {$EXTERNALSYM ALERT_MESSAGE_EVENT}
  ALERT_MESSAGE_EVENT         = 'MESSAGE';
  {$EXTERNALSYM ALERT_ERRORLOG_EVENT}
  ALERT_ERRORLOG_EVENT        = 'ERRORLOG';
  {$EXTERNALSYM ALERT_ADMIN_EVENT}
  ALERT_ADMIN_EVENT           = 'ADMIN';
  {$EXTERNALSYM ALERT_USER_EVENT}
  ALERT_USER_EVENT            = 'USER';

//      Bitmap masks for prjob_status field of PRINTJOB.

// 2-7 bits also used in device status

  {$EXTERNALSYM PRJOB_QSTATUS}
  PRJOB_QSTATUS       = $3;         // Bits 0,1
  {$EXTERNALSYM PRJOB_DEVSTATUS}
  PRJOB_DEVSTATUS     = $1fc;       // 2-8 bits
  {$EXTERNALSYM PRJOB_COMPLETE}
  PRJOB_COMPLETE      = $4;         // Bit 2
  {$EXTERNALSYM PRJOB_INTERV}
  PRJOB_INTERV        = $8;         // Bit 3
  {$EXTERNALSYM PRJOB_ERROR}
  PRJOB_ERROR         = $10;        // Bit 4
  {$EXTERNALSYM PRJOB_DESTOFFLINE}
  PRJOB_DESTOFFLINE   = $20;        // Bit 5
  {$EXTERNALSYM PRJOB_DESTPAUSED}
  PRJOB_DESTPAUSED    = $40;        // Bit 6
  {$EXTERNALSYM PRJOB_NOTIFY}
  PRJOB_NOTIFY        = $80;        // BIT 7
  {$EXTERNALSYM PRJOB_DESTNOPAPER}
  PRJOB_DESTNOPAPER   = $100;       // BIT 8
  {$EXTERNALSYM PRJOB_DELETED}
  PRJOB_DELETED       = $8000;      // BIT 15

//      Values of PRJOB_QSTATUS bits in prjob_status field of PRINTJOB.

  {$EXTERNALSYM PRJOB_QS_QUEUED}
  PRJOB_QS_QUEUED                 = 0;
  {$EXTERNALSYM PRJOB_QS_PAUSED}
  PRJOB_QS_PAUSED                 = 1;
  {$EXTERNALSYM PRJOB_QS_SPOOLING}
  PRJOB_QS_SPOOLING               = 2;
  {$EXTERNALSYM PRJOB_QS_PRINTING}
  PRJOB_QS_PRINTING               = 3;

// Translated from LMSHARE.H

// Function Prototypes - Share

function NetShareAdd(servername: LPTSTR; level: DWORD; const buf: Pointer;
  parm_err: PDWORD): NET_API_STATUS; stdcall;
{$EXTERNALSYM NetShareAdd}

function NetShareEnum(servername: LPTSTR; level: DWORD; var butptr: Pointer;
  prefmaxlen: DWORD; var entriesread: DWORD; var totalentries: DWORD;
  resume_handle: PDWORD): NET_API_STATUS; stdcall;
{$EXTERNALSYM NetShareEnum}

function NetShareEnumSticky(servername: LPTSTR; level: DWORD; var butptr: Pointer;
  prefmaxlen: DWORD; var entriesread: DWORD; var totalentries: DWORD;
  resume_handle: PDWORD): NET_API_STATUS; stdcall;
{$EXTERNALSYM NetShareEnumSticky}

function NetShareGetInfo(servername: LPWSTR; netname: LPWSTR; level: DWORD;
  var butptr: Pointer): NET_API_STATUS; stdcall;
{$EXTERNALSYM NetShareGetInfo}

function NetShareSetInfo(servername: LPTSTR; netname: LPTSTR; leve: DWORD;
  const buf: Pointer; parm_err: PDWORD): NET_API_STATUS; stdcall;
{$EXTERNALSYM NetShareSetInfo}

function NetShareDel(servername: LPTSTR; netname: LPTSTR;
  reserved: DWORD): NET_API_STATUS; stdcall;
{$EXTERNALSYM NetShareDel}

function NetShareDelSticky(servername: LPTSTR; netname: LPTSTR;
  reserved: DWORD): NET_API_STATUS; stdcall;
{$EXTERNALSYM NetShareDelSticky}

function NetShareCheck(servername: LPTSTR; device: LPTSTR;
  var _type: DWORD): NET_API_STATUS; stdcall;
{$EXTERNALSYM NetShareCheck}

// Data Structures - Share

type
  PShareInfo0 = ^TShareInfo0;
  {$EXTERNALSYM _SHARE_INFO_0}
  _SHARE_INFO_0 = record
    shi0_netname: LPTSTR;
  end;
  TShareInfo0 = _SHARE_INFO_0;
  {$EXTERNALSYM SHARE_INFO_0}
  SHARE_INFO_0 = _SHARE_INFO_0;

  PShareInfo1 = ^TShareInfo1;
  {$EXTERNALSYM _SHARE_INFO_1}
  _SHARE_INFO_1 = record
    shi1_netname: LPTSTR;
    shi1_type: DWORD;
    shi1_remark: LPTSTR;
  end;
  TShareInfo1 = _SHARE_INFO_1;
  {$EXTERNALSYM SHARE_INFO_1}
  SHARE_INFO_1 = _SHARE_INFO_1;

  PShareInfo2 = ^TShareInfo2;
  {$EXTERNALSYM _SHARE_INFO_2}
  _SHARE_INFO_2 = record
    shi2_netname: LPTSTR;
    shi2_type: DWORD;
    shi2_remark: LPTSTR;
    shi2_permissions: DWORD;
    shi2_max_uses: DWORD;
    shi2_current_uses: DWORD;
    shi2_path: LPTSTR;
    shi2_passwd: LPTSTR;
  end;
  TShareInfo2 = _SHARE_INFO_2;
  {$EXTERNALSYM SHARE_INFO_2}
  SHARE_INFO_2 = _SHARE_INFO_2;

  PShareInfo501 = ^TShareInfo501;
  {$EXTERNALSYM _SHARE_INFO_501}
  _SHARE_INFO_501 = record
    shi501_netname: LPTSTR;
    shi501_type: DWORD;
    shi501_remark: LPTSTR;
    shi501_flags: DWORD;
  end;
  TShareInfo501 = _SHARE_INFO_501;
  {$EXTERNALSYM SHARE_INFO_501}
  SHARE_INFO_501 = _SHARE_INFO_501;

  PShareInfo502 = ^TShareInfo502;
  {$EXTERNALSYM _SHARE_INFO_502}
  _SHARE_INFO_502 = record
    shi502_netname: LPTSTR;
    shi502_type: DWORD;
    shi502_remark: LPTSTR;
    shi502_permissions: DWORD;
    shi502_max_uses: DWORD;
    shi502_current_uses: DWORD;
    shi502_path: LPTSTR;
    shi502_passwd: LPTSTR;
    shi502_reserved: DWORD;
    shi502_security_descriptor: PSECURITY_DESCRIPTOR;
  end;
  TShareInfo502 = _SHARE_INFO_502;
  {$EXTERNALSYM SHARE_INFO_502}
  SHARE_INFO_502 = _SHARE_INFO_502;

  PShareInfo1004 = ^TShareInfo1004;
  {$EXTERNALSYM _SHARE_INFO_1004}
  _SHARE_INFO_1004 = record
    shi1004_remark: LPTSTR;
  end;
  TShareInfo1004 = _SHARE_INFO_1004;
  {$EXTERNALSYM SHARE_INFO_1004}
  SHARE_INFO_1004 = _SHARE_INFO_1004;

  PShareInfo1005 = ^TShareInfo1005;
  {$EXTERNALSYM _SHARE_INFO_1005}
  _SHARE_INFO_1005 = record
    shi1005_flags: DWORD;
  end;
  TShareInfo1005 = _SHARE_INFO_1005;
  {$EXTERNALSYM SHARE_INFO_1005}
  SHARE_INFO_1005 = _SHARE_INFO_1005;

  PShareInfo1006 = ^TShareInfo1006;
  {$EXTERNALSYM _SHARE_INFO_1006}
  _SHARE_INFO_1006 = record
    shi1006_max_uses: DWORD;
  end;
  TShareInfo1006 = _SHARE_INFO_1006;
  {$EXTERNALSYM SHARE_INFO_1006}
  SHARE_INFO_1006 = _SHARE_INFO_1006;

  PShareInfo1501 = ^TShareInfo1501;
  {$EXTERNALSYM _SHARE_INFO_1501}
  _SHARE_INFO_1501 = record
    shi1501_reserved: DWORD;
    shi1501_security_descriptor: PSECURITY_DESCRIPTOR;
  end;
  TShareInfo1501 = _SHARE_INFO_1501;
  {$EXTERNALSYM SHARE_INFO_1501}
  SHARE_INFO_1501 = _SHARE_INFO_1501;

// Values for parm_err parameter.

const
  {$EXTERNALSYM SHARE_NETNAME_PARMNUM}
  SHARE_NETNAME_PARMNUM = 1;
  {$EXTERNALSYM SHARE_TYPE_PARMNUM}
  SHARE_TYPE_PARMNUM = 3;
  {$EXTERNALSYM SHARE_REMARK_PARMNUM}
  SHARE_REMARK_PARMNUM = 4;
  {$EXTERNALSYM SHARE_PERMISSIONS_PARMNUM}
  SHARE_PERMISSIONS_PARMNUM = 5;
  {$EXTERNALSYM SHARE_MAX_USES_PARMNUM}
  SHARE_MAX_USES_PARMNUM = 6;
  {$EXTERNALSYM SHARE_CURRENT_USES_PARMNUM}
  SHARE_CURRENT_USES_PARMNUM = 7;
  {$EXTERNALSYM SHARE_PATH_PARMNUM}
  SHARE_PATH_PARMNUM = 8;
  {$EXTERNALSYM SHARE_PASSWD_PARMNUM}
  SHARE_PASSWD_PARMNUM = 9;
  {$EXTERNALSYM SHARE_FILE_SD_PARMNUM}
  SHARE_FILE_SD_PARMNUM = 501;

// Single-field infolevels for NetShareSetInfo.

  {$EXTERNALSYM SHARE_REMARK_INFOLEVEL}
  SHARE_REMARK_INFOLEVEL = (PARMNUM_BASE_INFOLEVEL + SHARE_REMARK_PARMNUM);
  {$EXTERNALSYM SHARE_MAX_USES_INFOLEVEL}
  SHARE_MAX_USES_INFOLEVEL = (PARMNUM_BASE_INFOLEVEL + SHARE_MAX_USES_PARMNUM);
  {$EXTERNALSYM SHARE_FILE_SD_INFOLEVEL}
  SHARE_FILE_SD_INFOLEVEL = (PARMNUM_BASE_INFOLEVEL + SHARE_FILE_SD_PARMNUM);

  {$EXTERNALSYM SHI1_NUM_ELEMENTS}
  SHI1_NUM_ELEMENTS = 4;
  {$EXTERNALSYM SHI2_NUM_ELEMENTS}
  SHI2_NUM_ELEMENTS = 10;

// Share types (shi1_type and shi2_type fields).

  {$EXTERNALSYM STYPE_DISKTREE}
  STYPE_DISKTREE = 0;
  {$EXTERNALSYM STYPE_PRINTQ}
  STYPE_PRINTQ = 1;
  {$EXTERNALSYM STYPE_DEVICE}
  STYPE_DEVICE = 2;
  {$EXTERNALSYM STYPE_IPC}
  STYPE_IPC = 3;

  {$EXTERNALSYM STYPE_SPECIAL}
  STYPE_SPECIAL = $80000000;

  {$EXTERNALSYM SHI_USES_UNLIMITED}
  SHI_USES_UNLIMITED = DWORD(-1);

// Flags values for the 501 and 1005 levels

  {$EXTERNALSYM SHI1005_FLAGS_DFS}
  SHI1005_FLAGS_DFS      = $01;        // Share is in the DFS
  {$EXTERNALSYM SHI1005_FLAGS_DFS_ROOT}
  SHI1005_FLAGS_DFS_ROOT = $02;        // Share is root of DFS

  {$EXTERNALSYM CSC_MASK}
  CSC_MASK               = $30;    // Used to mask off the following states

  {$EXTERNALSYM CSC_CACHE_MANUAL_REINT}
  CSC_CACHE_MANUAL_REINT = $00;    // No automatic file by file reintegration
  {$EXTERNALSYM CSC_CACHE_AUTO_REINT}
  CSC_CACHE_AUTO_REINT   = $10;    // File by file reintegration is OK
  {$EXTERNALSYM CSC_CACHE_VDO}
  CSC_CACHE_VDO          = $20;    // no need to flow opens
  {$EXTERNALSYM CSC_CACHE_NONE}
  CSC_CACHE_NONE         = $30;    // no CSC for this share

// The subset of 1005 infolevel flags that can be set via the API

  {$EXTERNALSYM SHI1005_VALID_FLAGS_SET}
  SHI1005_VALID_FLAGS_SET = CSC_MASK;

// SESSION API

// Function Prototypes Session

function NetSessionEnum(servername: LPTSTR; UncClientName: LPTSTR;
  username: LPTSTR; level: DWORD; var bufptr: Pointer; prefmaxlen: DWORD;
  var entriesread: DWORD; var totalentries: DWORD;
  resume_handle: PDWORD): NET_API_STATUS; stdcall;
{$EXTERNALSYM NetSessionEnum}

function NetSessionDel(servername: LPTSTR; UncClientName: LPTSTR;
  username: LPTSTR): NET_API_STATUS; stdcall;
{$EXTERNALSYM NetSessionDel}

function NetSessionGetInfo(servername: LPTSTR; UncClientName: LPTSTR;
  username: LPTSTR; level: DWORD; var bufptr: Pointer): NET_API_STATUS; stdcall;
{$EXTERNALSYM NetSessionGetInfo}

// Data Structures - Session

type
  PSessionInfo0 = ^TSessionInfo0;
  {$EXTERNALSYM _SESSION_INFO_0}
  _SESSION_INFO_0 = record
    sesi0_cname: LPTSTR;                // client name (no backslashes)
  end;
  TSessionInfo0 = _SESSION_INFO_0;
  {$EXTERNALSYM SESSION_INFO_0}
  SESSION_INFO_0 = _SESSION_INFO_0;

  PSessionInfo1 = ^TSessionInfo1;
  {$EXTERNALSYM _SESSION_INFO_1}
  _SESSION_INFO_1 = record
    sesi1_cname: LPTSTR;                // client name (no backslashes)
    sesi1_username: LPTSTR;
    sesi1_num_opens: DWORD;
    sesi1_time: DWORD;
    sesi1_idle_time: DWORD;
    sesi1_user_flags: DWORD;
  end;
  TSessionInfo1 = _SESSION_INFO_1;
  {$EXTERNALSYM SESSION_INFO_1}
  SESSION_INFO_1 = _SESSION_INFO_1;

  PSessionInfo2 = ^TSessionInfo2;
  {$EXTERNALSYM _SESSION_INFO_2}
  _SESSION_INFO_2 = record
    sesi2_cname: LPTSTR;                // client name (no backslashes)
    sesi2_username: LPTSTR;
    sesi2_num_opens: DWORD;
    sesi2_time: DWORD;
    sesi2_idle_time: DWORD;
    sesi2_user_flags: DWORD;
    sesi2_cltype_name: LPTSTR;
  end;
  TSessionInfo2 = _SESSION_INFO_2;
  {$EXTERNALSYM SESSION_INFO_2}
  SESSION_INFO_2 = _SESSION_INFO_2;

  PSessionInfo10 = ^TSessionInfo10;
  {$EXTERNALSYM _SESSION_INFO_10}
  _SESSION_INFO_10 = record
    sesi10_cname: LPTSTR;               // client name (no backslashes)
    sesi10_username: LPTSTR;
    sesi10_time: DWORD;
    sesi10_idle_time: DWORD;
  end;
  TSessionInfo10 = _SESSION_INFO_10;
  {$EXTERNALSYM SESSION_INFO_10}
  SESSION_INFO_10 = _SESSION_INFO_10;

  PSessionInfo502 = ^TSessionInfo502;
  {$EXTERNALSYM _SESSION_INFO_502}
  _SESSION_INFO_502 = record
    sesi502_cname: LPTSTR;              // client name (no backslashes)
    sesi502_username: LPTSTR;
    sesi502_num_opens: DWORD;
    sesi502_time: DWORD;
    sesi502_idle_time: DWORD;
    sesi502_user_flags: DWORD;
    sesi502_cltype_name: LPTSTR;
    sesi502_transport: LPTSTR;
  end;
  TSessionInfo502 = _SESSION_INFO_502;
  {$EXTERNALSYM SESSION_INFO_502}
  SESSION_INFO_502 = _SESSION_INFO_502;

// Bits defined in sesi1_user_flags.

const
  {$EXTERNALSYM SESS_GUEST}
  SESS_GUEST        = $00000001;  // session is logged on as a guest
  {$EXTERNALSYM SESS_NOENCRYPTION}
  SESS_NOENCRYPTION = $00000002;  // session is not using encryption

  {$EXTERNALSYM SESI1_NUM_ELEMENTS}
  SESI1_NUM_ELEMENTS = 8;
  {$EXTERNALSYM SESI2_NUM_ELEMENTS}
  SESI2_NUM_ELEMENTS = 9;

// CONNECTION API

// Function Prototypes - CONNECTION

function NetConnectionEnum(servername: LPWSTR; qualifier: LPWSTR;
  level: DWORD; var bufptr: Pointer; prefmaxlen: DWORD; var entriesread: DWORD;
  var totalentries: DWORD; resume_handle: PDWORD): NET_API_STATUS; stdcall;
{$EXTERNALSYM NetConnectionEnum}

// Data Structures - CONNECTION

type
  PConnectionInfo0 = ^TConnectionInfo0;
  {$EXTERNALSYM _CONNECTION_INFO_0}
  _CONNECTION_INFO_0 = record
    coni0_id: DWORD;
  end;
  TConnectionInfo0 = _CONNECTION_INFO_0;
  {$EXTERNALSYM CONNECTION_INFO_0}
  CONNECTION_INFO_0 = _CONNECTION_INFO_0;

  PConnectionInfo1 = ^TConnectionInfo1;
  {$EXTERNALSYM _CONNECTION_INFO_1}
  _CONNECTION_INFO_1 = record
    coni1_id: DWORD;
    coni1_type: DWORD;
    coni1_num_opens: DWORD;
    coni1_num_users: DWORD;
    coni1_time: DWORD;
    coni1_username: LPWSTR;
    coni1_netname: LPWSTR;
  end;
  TConnectionInfo1 = _CONNECTION_INFO_1;
  {$EXTERNALSYM CONNECTION_INFO_1}
  CONNECTION_INFO_1 = _CONNECTION_INFO_1;

// FILE API

// Function Prototypes - FILE

function NetFileClose(servername: LPTSTR; fileid: DWORD): NET_API_STATUS; stdcall;
{$EXTERNALSYM NetFileClose}

function NetFileEnum(servername: LPTSTR; basepath: LPTSTR; username: LPTSTR;
  level: DWORD; var bufptr: Pointer; prefmaxlen: DWORD; var entriesread: DWORD;
  var totalentries: DWORD; resume_handle: PDWORD): NET_API_STATUS; stdcall;
{$EXTERNALSYM NetFileEnum}

function NetFileGetInfo(servername: LPTSTR; fileid: DWORD; level: DWORD;
  bufptr: Pointer): NET_API_STATUS; stdcall;
{$EXTERNALSYM NetFileGetInfo}

// Data Structures - File

// File APIs are available at information levels 2 & 3 only. Levels 0 &
// 1 are not supported.

type
  PFileInfo2 = ^TFileInfo2;
  {$EXTERNALSYM _FILE_INFO_2}
  _FILE_INFO_2 = record
    fi2_id: DWORD;
  end;
  TFileInfo2 = _FILE_INFO_2;
  {$EXTERNALSYM FILE_INFO_2}
  FILE_INFO_2 = _FILE_INFO_2;

  PFileInfo3 = ^TFileInfo3;
  {$EXTERNALSYM _FILE_INFO_3}
  _FILE_INFO_3 = record
    fi3_id: DWORD;
    fi3_permissions: DWORD;
    fi3_num_locks: DWORD;
    fi3_pathname: LPTSTR;
    fi3_username: LPTSTR;
  end;
  TFileInfo3 = _FILE_INFO_3;
  {$EXTERNALSYM FILE_INFO_3}
  FILE_INFO_3 = _FILE_INFO_3;

// bit values for permissions

const
  {$EXTERNALSYM PERM_FILE_READ}
  PERM_FILE_READ   = $01; // user has read access
  {$EXTERNALSYM PERM_FILE_WRITE}
  PERM_FILE_WRITE  = $02; // user has write access
  {$EXTERNALSYM PERM_FILE_CREATE}
  PERM_FILE_CREATE = $04; // user has create access

// Translated from LMMSG.H

{$EXTERNALSYM NetMessageNameAdd}
function NetMessageNameAdd(servername, msgname: LPCWSTR): NET_API_STATUS; stdcall;

{$EXTERNALSYM NetMessageNameEnum}
function NetMessageNameEnum(servername: LPCWSTR; level: DWORD; bufptr: Pointer;
  prefmaxlen: DWORD; var entriesread: DWORD; var totalentries: DWORD;
  resume_handle: PDWORD): NET_API_STATUS; stdcall;

{$EXTERNALSYM NetMessageNameGetInfo}
function NetMessageNameGetInfo(servername: LPCWSTR; msgname: LPCWSTR;
  level: DWORD; var bufptr: Pointer): NET_API_STATUS; stdcall;

{$EXTERNALSYM NetMessageNameDel}
function NetMessageNameDel(servername, msgname: LPCWSTR): NET_API_STATUS; stdcall;

{$EXTERNALSYM NetMessageBufferSend}
function NetMessageBufferSend(servername: LPCWSTR; msgname: LPCWSTR;
  fromname: LPCWSTR; buf: Pointer; buflen: DWORD): NET_API_STATUS; stdcall;

type
  PMsgInfo0 = ^TMsgInfo0;
  {$EXTERNALSYM _MSG_INFO_0}
  _MSG_INFO_0 = record
    msgi0_name: LPWSTR;
  end;
  TMsgInfo0 = _MSG_INFO_0;
  {$EXTERNALSYM MSG_INFO_0}
  MSG_INFO_0 = _MSG_INFO_0;

  PMsgInfo1 = ^TMsgInfo1;
  {$EXTERNALSYM _MSG_INFO_1}
  _MSG_INFO_1 = record
    msgi1_name: LPWSTR;
    msgi1_forward_flag: DWORD;
    msgi1_forward: LPWSTR;
  end;
  TMsgInfo1 = _MSG_INFO_1;
  {$EXTERNALSYM MSG_INFO_1}
  MSG_INFO_1 = _MSG_INFO_1;


// Values for msgi1_forward_flag.

const
  {$EXTERNALSYM MSGNAME_NOT_FORWARDED}
  MSGNAME_NOT_FORWARDED   = $00;    // Name not forwarded
  {$EXTERNALSYM MSGNAME_FORWARDED_TO}
  MSGNAME_FORWARDED_TO    = $04;    // Name forward to remote station
  {$EXTERNALSYM MSGNAME_FORWARDED_FROM}
  MSGNAME_FORWARDED_FROM  = $10;    // Name forwarded from remote station

// Translated from LMREMUTL.H

function NetRemoteTOD(UncServerName: LPCWSTR; BufferPtr: Pointer): NET_API_STATUS; stdcall;
{$EXTERNALSYM NetRemoteTOD}

function NetRemoteComputerSupports(UncServerName: LPCWSTR; OptionsWanted: DWORD;
  var OptionsSupported: DWORD): NET_API_STATUS; stdcall;
{$EXTERNALSYM NetRemoteComputerSupports}

type
  PTimeOfDayInfo = ^TTimeOfDayInfo;
  _TIME_OF_DAY_INFO = record
    tod_elapsedt: DWORD;
    tod_msecs: DWORD;
    tod_hours: DWORD;
    tod_mins: DWORD;
    tod_secs: DWORD;
    tod_hunds: DWORD;
    tod_timezone: LongInt;
    tod_tinterval: DWORD;
    tod_day: DWORD;
    tod_month: DWORD;
    tod_year: DWORD;
    tod_weekday: DWORD;
  end;
  {$EXTERNALSYM _TIME_OF_DAY_INFO}
  TTimeOfDayInfo = _TIME_OF_DAY_INFO;
  TIME_OF_DAY_INFO = _TIME_OF_DAY_INFO;
  {$EXTERNALSYM TIME_OF_DAY_INFO}

// Mask bits for use with NetRemoteComputerSupports:

const
  SUPPORTS_REMOTE_ADMIN_PROTOCOL  = $00000002;
  {EXTERNALSYM SUPPORTS_REMOTE_ADMIN_PROTOCOL}
  SUPPORTS_RPC                    = $00000004;
  {EXTERNALSYM SUPPORTS_RPC}
  SUPPORTS_SAM_PROTOCOL           = $00000008;
  {EXTERNALSYM SUPPORTS_SAM_PROTOCOL}
  SUPPORTS_UNICODE                = $00000010;
  {EXTERNALSYM SUPPORTS_UNICODE}
  SUPPORTS_LOCAL                  = $00000020;
  {EXTERNALSYM SUPPORTS_LOCAL}
  SUPPORTS_ANY                    = $FFFFFFFF;
  {EXTERNALSYM SUPPORTS_ANY}

// Flag bits for RxRemoteApi:

  NO_PERMISSION_REQUIRED  = $00000001;      // set if use NULL session;
  {EXTERNALSYM NO_PERMISSION_REQUIRED}
  ALLOCATE_RESPONSE       = $00000002;      // set if RxRemoteApi allocates response buffer;
  {EXTERNALSYM ALLOCATE_RESPONSE}
  USE_SPECIFIC_TRANSPORT  = $80000000;
  {EXTERNALSYM USE_SPECIFIC_TRANSPORT}

// Translated from LMREPL.H

// Replicator Configuration APIs

const
  REPL_ROLE_EXPORT        = 1;
  {$EXTERNALSYM REPL_ROLE_EXPORT}
  REPL_ROLE_IMPORT        = 2;
  {$EXTERNALSYM REPL_ROLE_IMPORT}
  REPL_ROLE_BOTH          = 3;
  {$EXTERNALSYM REPL_ROLE_BOTH}

  REPL_INTERVAL_INFOLEVEL         = (PARMNUM_BASE_INFOLEVEL + 0);
  {$EXTERNALSYM REPL_INTERVAL_INFOLEVEL}
  REPL_PULSE_INFOLEVEL            = (PARMNUM_BASE_INFOLEVEL + 1);
  {$EXTERNALSYM REPL_PULSE_INFOLEVEL}
  REPL_GUARDTIME_INFOLEVEL        = (PARMNUM_BASE_INFOLEVEL + 2);
  {$EXTERNALSYM REPL_GUARDTIME_INFOLEVEL}
  REPL_RANDOM_INFOLEVEL           = (PARMNUM_BASE_INFOLEVEL + 3);
  {$EXTERNALSYM REPL_RANDOM_INFOLEVEL}

type
  PReplInfo0 = ^TReplInfo0;
  _REPL_INFO_0 = record
    rp0_role: DWORD;
    rp0_exportpath: LPWSTR;
    rp0_exportlist: LPWSTR;
    rp0_importpath: LPWSTR;
    rp0_importlist: LPWSTR;
    rp0_logonusername: LPWSTR;
    rp0_interval: DWORD;
    rp0_pulse: DWORD;
    rp0_guardtime: DWORD;
    rp0_random: DWORD;
  end;
  {$EXTERNALSYM _REPL_INFO_0}
  TReplInfo0 = _REPL_INFO_0;
  REPL_INFO_0 = _REPL_INFO_0;
  {$EXTERNALSYM REPL_INFO_0}

  PReplInfo1000 = ^TReplInfo1000;
  _REPL_INFO_1000 = record
    rp1000_interval: DWORD;
  end;
  {$EXTERNALSYM _REPL_INFO_1000}
  TReplInfo1000 = _REPL_INFO_1000;
  REPL_INFO_1000 = _REPL_INFO_1000;
  {$EXTERNALSYM REPL_INFO_1000}

  PReplInfo1001 = ^TReplInfo1001;
  _REPL_INFO_1001 = record
    rp1001_pulse: DWORD;
  end;
  {$EXTERNALSYM _REPL_INFO_1001}
  TReplInfo1001 = _REPL_INFO_1001;
  REPL_INFO_1001 = _REPL_INFO_1001;
  {$EXTERNALSYM REPL_INFO_1001}

  PReplInfo1002 = ^TReplInfo1002;
  _REPL_INFO_1002 = record
    rp1002_guardtime: DWORD;
  end;
  {$EXTERNALSYM _REPL_INFO_1002}
  TReplInfo1002 = _REPL_INFO_1002;
  REPL_INFO_1002 = _REPL_INFO_1002;
  {$EXTERNALSYM REPL_INFO_1002}

  PReplInfo1003 = ^TReplInfo1003;
  _REPL_INFO_1003 = record
    rp1003_random: DWORD;
  end;
  {$EXTERNALSYM _REPL_INFO_1003}
  TReplInfo1003 = _REPL_INFO_1003;
  REPL_INFO_1003 = _REPL_INFO_1003;
  {$EXTERNALSYM REPL_INFO_1003}

function NetReplGetInfo(servername: LPCWSTR; level: DWORD; bufptr: Pointer): NET_API_STATUS; stdcall;
{$EXTERNALSYM NetReplGetInfo}

function NetReplSetInfo(servername: LPCWSTR; level: DWORD; const buf: Pointer;
  parm_err: PDWORD): NET_API_STATUS; stdcall;
{$EXTERNALSYM NetReplSetInfo}

// Replicator Export Directory APIs

const
  REPL_INTEGRITY_FILE     = 1;
  {$EXTERNALSYM REPL_INTEGRITY_FILE}
  REPL_INTEGRITY_TREE     = 2;
  {$EXTERNALSYM REPL_INTEGRITY_TREE}

  REPL_EXTENT_FILE        = 1;
  {$EXTERNALSYM REPL_EXTENT_FILE}
  REPL_EXTENT_TREE        = 2;
  {$EXTERNALSYM REPL_EXTENT_TREE}

  REPL_EXPORT_INTEGRITY_INFOLEVEL = (PARMNUM_BASE_INFOLEVEL + 0);
  {$EXTERNALSYM REPL_EXPORT_INTEGRITY_INFOLEVEL}
  REPL_EXPORT_EXTENT_INFOLEVEL    = (PARMNUM_BASE_INFOLEVEL + 1);
  {$EXTERNALSYM REPL_EXPORT_EXTENT_INFOLEVEL}

type
  PReplEdirInfo0 = ^TReplEdirInfo0;
  _REPL_EDIR_INFO_0 = record
    rped0_dirname: LPWSTR;
  end;
  {$EXTERNALSYM _REPL_EDIR_INFO_0}
  TReplEdirInfo0 = _REPL_EDIR_INFO_0;
  REPL_EDIR_INFO_0 = _REPL_EDIR_INFO_0;
  {$EXTERNALSYM REPL_EDIR_INFO_0}

  PReplEdirInfo1 = ^TReplEdirInfo1;
  _REPL_EDIR_INFO_1 = record
    rped1_dirname: LPWSTR;
    rped1_integrity: DWORD;
    rped1_extent: DWORD;
  end;
  {$EXTERNALSYM _REPL_EDIR_INFO_1}
  TReplEdirInfo1 = _REPL_EDIR_INFO_1;
  REPL_EDIR_INFO_1 = _REPL_EDIR_INFO_1;
  {$EXTERNALSYM REPL_EDIR_INFO_1}

  PReplEdirInfo2 = ^TReplEdirInfo2;
  _REPL_EDIR_INFO_2 = record
    rped2_dirname: LPWSTR;
    rped2_integrity: DWORD;
    rped2_extent: DWORD;
    rped2_lockcount: DWORD;
    rped2_locktime: DWORD;
  end;
  {$EXTERNALSYM _REPL_EDIR_INFO_2}
  TReplEdirInfo2 = _REPL_EDIR_INFO_2;
  REPL_EDIR_INFO_2 = _REPL_EDIR_INFO_2;
  {$EXTERNALSYM REPL_EDIR_INFO_2}

  PReplEdirInfo1000 = ^TReplEdirInfo1000;
  _REPL_EDIR_INFO_1000 = record
    rped1000_integrity: DWORD;
  end;
  {$EXTERNALSYM _REPL_EDIR_INFO_1000}
  TReplEdirInfo1000 = _REPL_EDIR_INFO_1000;
  REPL_EDIR_INFO_1000 = _REPL_EDIR_INFO_1000;
  {$EXTERNALSYM REPL_EDIR_INFO_1000}

  PReplEdirInfo1001 = ^TReplEdirInfo1001;
  _REPL_EDIR_INFO_1001 = record
    rped1001_extent: DWORD;
  end;
  {$EXTERNALSYM _REPL_EDIR_INFO_1001}
  TReplEdirInfo1001 = _REPL_EDIR_INFO_1001;
  REPL_EDIR_INFO_1001 = _REPL_EDIR_INFO_1001;
  {$EXTERNALSYM REPL_EDIR_INFO_1001}


function NetReplExportDirAdd(servername: LPCWSTR; level: DWORD; buf: Pointer;
  parm_err: PDWORD): NET_API_STATUS; stdcall;
{$EXTERNALSYM NetReplExportDirAdd}

function NetReplExportDirDel(servername, dirname: LPCWSTR): NET_API_STATUS; stdcall;
{$EXTERNALSYM NetReplExportDirDel}

function NetReplExportDirEnum(servername: LPCWSTR; level: DWORD; bufptr: Pointer;
  prefmaxlen: DWORD; var entriesread: DWORD; var totalentries: DWORD;
  resumehandle: PDWORD): NET_API_STATUS; stdcall;
{$EXTERNALSYM NetReplExportDirEnum}

function NetReplExportDirGetInfo(servername: LPCWSTR; dirname: LPCWSTR;
  level: DWORD; bufptr: Pointer): NET_API_STATUS; stdcall;
{$EXTERNALSYM NetReplExportDirGetInfo}

function NetReplExportDirSetInfo(servername: LPCWSTR; dirname: LPCWSTR;
  level: DWORD; const buf: Pointer; parm_err: PDWORD): NET_API_STATUS; stdcall;
{$EXTERNALSYM NetReplExportDirSetInfo}

function NetReplExportDirLock(servername, dirname: LPCWSTR): NET_API_STATUS; stdcall;
{$EXTERNALSYM NetReplExportDirLock}

function NetReplExportDirUnlock(servername: LPCWSTR; dirname: LPCWSTR;
  unlockforce: DWORD): NET_API_STATUS; stdcall;
{$EXTERNALSYM NetReplExportDirUnlock}

const
  REPL_UNLOCK_NOFORCE     = 0;
  {$EXTERNALSYM REPL_UNLOCK_NOFORCE}
  REPL_UNLOCK_FORCE       = 1;
  {$EXTERNALSYM REPL_UNLOCK_FORCE}

// Replicator Import Directory APIs

type
  PReplIdirInfo0 = ^TReplIdirInfo0;
  _REPL_IDIR_INFO_0 = record
    rpid0_dirname: LPWSTR;
  end;
  {$EXTERNALSYM _REPL_IDIR_INFO_0}
  TReplIdirInfo0 = _REPL_IDIR_INFO_0;
  REPL_IDIR_INFO_0 = _REPL_IDIR_INFO_0;
  {$EXTERNALSYM REPL_IDIR_INFO_0}

  PReplIdirInfo1 = ^TReplIdirInfo1;
  _REPL_IDIR_INFO_1 = record
    rpid1_dirname: LPWSTR;
    rpid1_state: DWORD;
    rpid1_mastername: LPWSTR;
    rpid1_last_update_time: DWORD;
    rpid1_lockcount: DWORD;
    rpid1_locktime: DWORD;
  end;
  {$EXTERNALSYM _REPL_IDIR_INFO_1}
  TReplIdirInfo1 = _REPL_IDIR_INFO_1;
  REPL_IDIR_INFO_1 = _REPL_IDIR_INFO_1;
  {$EXTERNALSYM REPL_IDIR_INFO_1}

function NetReplImportDirAdd(servername: LPCWSTR; level: DWORD; buf: Pointer;
  parm_err: PDWORD): NET_API_STATUS; stdcall;
{$EXTERNALSYM NetReplImportDirAdd}

function NetReplImportDirDel(servername, dirname: LPCWSTR): NET_API_STATUS; stdcall;
{$EXTERNALSYM NetReplImportDirDel}

function NetReplImportDirEnum(servername: LPCWSTR; level: DWORD; bufptr: Pointer;
  prefmaxlen: DWORD; var entriesread: DWORD; var totalentries: DWORD;
  resumehandle: PDWORD): NET_API_STATUS; stdcall;
{$EXTERNALSYM NetReplImportDirEnum}

function NetReplImportDirGetInfo(servername, dirname: LPCWSTR; level: DWORD;
  bufptr: Pointer): NET_API_STATUS; stdcall;
{$EXTERNALSYM NetReplImportDirGetInfo}

function NetReplImportDirLock(servername, dirname: LPCWSTR): NET_API_STATUS; stdcall;
{$EXTERNALSYM NetReplImportDirLock}

function NetReplImportDirUnlock(servername: LPCWSTR; dirname: LPCWSTR;
  unlockforce: DWORD): NET_API_STATUS; stdcall;
{$EXTERNALSYM NetReplImportDirUnlock}

const
  REPL_STATE_OK                   = 0;
  {$EXTERNALSYM REPL_STATE_OK}
  REPL_STATE_NO_MASTER            = 1;
  {$EXTERNALSYM REPL_STATE_NO_MASTER}
  REPL_STATE_NO_SYNC              = 2;
  {$EXTERNALSYM REPL_STATE_NO_SYNC}
  REPL_STATE_NEVER_REPLICATED     = 3;
  {$EXTERNALSYM REPL_STATE_NEVER_REPLICATED}

// Translated from LMSERVER.H

// Function Prototypes - SERVER

function NetServerEnum(servername: LPCWSTR; level: DWORD; var bufptr: Pointer;
  prefmaxlen: DWORD; var entriesread: DWORD; var totalentries: DWORD;
  servertype: DWORD; domain: LPCWSTR; resume_handle: PDWORD): NET_API_STATUS; stdcall;
{$EXTERNALSYM NetServerEnum}

function NetServerEnumEx(ServerName: LPCWSTR; Level: DWORD; var Bufptr: Pointer;
  PrefMaxlen: DWORD; var EntriesRead: DWORD; var totalentries: DWORD;
  servertype: DWORD; domain, FirstNameToReturn: LPCWSTR): NET_API_STATUS; stdcall;
{$EXTERNALSYM NetServerEnumEx}

function NetServerGetInfo(servername: LPWSTR; level: DWORD;
  var bufptr: Pointer): NET_API_STATUS; stdcall;
{$EXTERNALSYM NetServerGetInfo}

function NetServerSetInfo(servername: LPWSTR; level: DWORD; buf: Pointer;
  ParmError: PDWORD): NET_API_STATUS; stdcall;
{$EXTERNALSYM NetServerSetInfo}

// Temporary hack function.

function NetServerSetInfoCommandLine(argc: Word; argv: LPWSTR): NET_API_STATUS; stdcall;
{$EXTERNALSYM NetServerSetInfoCommandLine}

function NetServerDiskEnum(servername: LPWSTR; level: DWORD; bufptr: Pointer;
  prefmaxlen: DWORD; var entriesread: DWORD; var totalentries: DWORD;
  resume_handle: PDWORD): NET_API_STATUS; stdcall;
{$EXTERNALSYM NetServerDiskEnum}

function NetServerComputerNameAdd(ServerName: LPWSTR; EmulatedDomainName: LPWSTR;
  EmulatedServerName: LPWSTR): NET_API_STATUS; stdcall;
{$EXTERNALSYM NetServerComputerNameAdd}

function NetServerComputerNameDel(ServerName, EmulatedServerName: LPWSTR): NET_API_STATUS; stdcall;
{$EXTERNALSYM NetServerComputerNameDel}

function NetServerTransportAdd(servername: LPWSTR; level: DWORD;
  bufptr: Pointer): NET_API_STATUS; stdcall;
{$EXTERNALSYM NetServerTransportAdd}

function NetServerTransportAddEx(servername: LPWSTR; level: DWORD;
  bufptr: Pointer): NET_API_STATUS; stdcall;
{$EXTERNALSYM NetServerTransportAddEx}

function NetServerTransportDel(servername: LPWSTR; level: DWORD;
  bufptr: Pointer): NET_API_STATUS; stdcall;
{$EXTERNALSYM NetServerTransportDel}

function NetServerTransportEnum(servername: LPWSTR; level: DWORD; bufptr: Pointer;
  prefmaxlen: DWORD; var entriesread: DWORD; var totalentries: DWORD;
  resumehandle: PDWORD): NET_API_STATUS; stdcall;
{$EXTERNALSYM NetServerTransportEnum}

// The following function can be called by Win NT services to register
// their service type.  This function is exported from advapi32.dll.
// Therefore, if this is the only function called by that service, then
// it is not necessary to link to netapi32.lib.

function SetServiceBits(hServiceStatus: SERVICE_STATUS_HANDLE;
  dwServiceBits: DWORD; bSetBitsOn: BOOL; bUpdateImmediately: BOOL): BOOL; stdcall;
{$EXTERNALSYM SetServiceBits}

// Data Structures - SERVER

type
  PServerInfo100 = ^TServerInfo100;
  _SERVER_INFO_100 = record
    sv100_platform_id: DWORD;
    sv100_name: LPWSTR;
  end;
  {$EXTERNALSYM _SERVER_INFO_100}
  TServerInfo100 = _SERVER_INFO_100;
  SERVER_INFO_100 = _SERVER_INFO_100;
  {$EXTERNALSYM SERVER_INFO_100}

  PServerInfo101 = ^TServerInfo101;
  _SERVER_INFO_101 = record
    sv101_platform_id: DWORD;
    sv101_name: LPWSTR;
    sv101_version_major: DWORD;
    sv101_version_minor: DWORD;
    sv101_type: DWORD;
    sv101_comment: LPWSTR;
  end;
  {$EXTERNALSYM _SERVER_INFO_101}
  TServerInfo101 = _SERVER_INFO_101;
  SERVER_INFO_101 = _SERVER_INFO_101;
  {$EXTERNALSYM SERVER_INFO_101}

  PServerInfo102 = ^TServerInfo102;
  _SERVER_INFO_102 = record
     sv102_platform_id: DWORD;
     sv102_name: LPWSTR;
     sv102_version_major: DWORD;
     sv102_version_minor: DWORD;
     sv102_type: DWORD;
     sv102_comment: LPWSTR;
     sv102_users: DWORD;
     sv102_disc: LongInt;
     sv102_hidden: BOOL;
     sv102_announce: DWORD;
     sv102_anndelta: DWORD;
     sv102_licenses: DWORD;
     sv102_userpath: LPWSTR;
  end;
  {$EXTERNALSYM _SERVER_INFO_102}
  TServerInfo102 = _SERVER_INFO_102;
  SERVER_INFO_102 = _SERVER_INFO_102;
  {$EXTERNALSYM SERVER_INFO_102}

  PServerInfo402 = ^TServerInfo402;
  _SERVER_INFO_402 = record
     sv402_ulist_mtime: DWORD;
     sv402_glist_mtime: DWORD;
     sv402_alist_mtime: DWORD;
     sv402_alerts: LPWSTR;
     sv402_security: DWORD;
     sv402_numadmin: DWORD;
     sv402_lanmask: DWORD;
     sv402_guestacct: LPWSTR;
     sv402_chdevs: DWORD;
     sv402_chdevq: DWORD;
     sv402_chdevjobs: DWORD;
     sv402_connections: DWORD;
     sv402_shares: DWORD;
     sv402_openfiles: DWORD;
     sv402_sessopens: DWORD;
     sv402_sessvcs: DWORD;
     sv402_sessreqs: DWORD;
     sv402_opensearch: DWORD;
     sv402_activelocks: DWORD;
     sv402_numreqbuf: DWORD;
     sv402_sizreqbuf: DWORD;
     sv402_numbigbuf: DWORD;
     sv402_numfiletasks: DWORD;
     sv402_alertsched: DWORD;
     sv402_erroralert: DWORD;
     sv402_logonalert: DWORD;
     sv402_accessalert: DWORD;
     sv402_diskalert: DWORD;
     sv402_netioalert: DWORD;
     sv402_maxauditsz: DWORD;
     sv402_srvheuristics: LPWSTR;
  end;
  {$EXTERNALSYM _SERVER_INFO_402}
  TServerInfo402 = _SERVER_INFO_402;
  SERVER_INFO_402 = _SERVER_INFO_402;
  {$EXTERNALSYM SERVER_INFO_402}

  PServerInfo403 = ^TServerInfo403;
  _SERVER_INFO_403 = record
     sv403_ulist_mtime: DWORD;
     sv403_glist_mtime: DWORD;
     sv403_alist_mtime: DWORD;
     sv403_alerts: LPWSTR;
     sv403_security: DWORD;
     sv403_numadmin: DWORD;
     sv403_lanmask: DWORD;
     sv403_guestacct: LPWSTR;
     sv403_chdevs: DWORD;
     sv403_chdevq: DWORD;
     sv403_chdevjobs: DWORD;
     sv403_connections: DWORD;
     sv403_shares: DWORD;
     sv403_openfiles: DWORD;
     sv403_sessopens: DWORD;
     sv403_sessvcs: DWORD;
     sv403_sessreqs: DWORD;
     sv403_opensearch: DWORD;
     sv403_activelocks: DWORD;
     sv403_numreqbuf: DWORD;
     sv403_sizreqbuf: DWORD;
     sv403_numbigbuf: DWORD;
     sv403_numfiletasks: DWORD;
     sv403_alertsched: DWORD;
     sv403_erroralert: DWORD;
     sv403_logonalert: DWORD;
     sv403_accessalert: DWORD;
     sv403_diskalert: DWORD;
     sv403_netioalert: DWORD;
     sv403_maxauditsz: DWORD;
     sv403_srvheuristics: LPWSTR;
     sv403_auditedevents: DWORD;
     sv403_autoprofile: DWORD;
     sv403_autopath: LPWSTR;
  end;
  {$EXTERNALSYM _SERVER_INFO_403}
  TServerInfo403 = _SERVER_INFO_403;
  SERVER_INFO_403 = _SERVER_INFO_403;
  {$EXTERNALSYM SERVER_INFO_403}

  PServerInfo502 = ^TServerInfo502;
  _SERVER_INFO_502 = record
    sv502_sessopens: DWORD;
    sv502_sessvcs: DWORD;
    sv502_opensearch: DWORD;
    sv502_sizreqbuf: DWORD;
    sv502_initworkitems: DWORD;
    sv502_maxworkitems: DWORD;
    sv502_rawworkitems: DWORD;
    sv502_irpstacksize: DWORD;
    sv502_maxrawbuflen: DWORD;
    sv502_sessusers: DWORD;
    sv502_sessconns: DWORD;
    sv502_maxpagedmemoryusage: DWORD;
    sv502_maxnonpagedmemoryusage: DWORD;
    sv502_enablesoftcompat: BOOL;
    sv502_enableforcedlogoff: BOOL;
    sv502_timesource: BOOL;
    sv502_acceptdownlevelapis: BOOL;
    sv502_lmannounce: BOOL;
  end;
  {$EXTERNALSYM _SERVER_INFO_502}
  TServerInfo502 = _SERVER_INFO_502;
  SERVER_INFO_502 = _SERVER_INFO_502;
  {$EXTERNALSYM SERVER_INFO_502}

  PServerInfo503 = ^TServerInfo503;
  _SERVER_INFO_503 = record
    sv503_sessopens: DWORD;
    sv503_sessvcs: DWORD;
    sv503_opensearch: DWORD;
    sv503_sizreqbuf: DWORD;
    sv503_initworkitems: DWORD;
    sv503_maxworkitems: DWORD;
    sv503_rawworkitems: DWORD;
    sv503_irpstacksize: DWORD;
    sv503_maxrawbuflen: DWORD;
    sv503_sessusers: DWORD;
    sv503_sessconns: DWORD;
    sv503_maxpagedmemoryusage: DWORD;
    sv503_maxnonpagedmemoryusage: DWORD;
    sv503_enablesoftcompat: BOOL;
    sv503_enableforcedlogoff: BOOL;
    sv503_timesource: BOOL;
    sv503_acceptdownlevelapis: BOOL;
    sv503_lmannounce: BOOL;
    sv503_domain: LPWSTR;
    sv503_maxcopyreadlen: DWORD;
    sv503_maxcopywritelen: DWORD;
    sv503_minkeepsearch: DWORD;
    sv503_maxkeepsearch: DWORD;
    sv503_minkeepcomplsearch: DWORD;
    sv503_maxkeepcomplsearch: DWORD;
    sv503_threadcountadd: DWORD;
    sv503_numblockthreads: DWORD;
    sv503_scavtimeout: DWORD;
    sv503_minrcvqueue: DWORD;
    sv503_minfreeworkitems: DWORD;
    sv503_xactmemsize: DWORD;
    sv503_threadpriority: DWORD;
    sv503_maxmpxct: DWORD;
    sv503_oplockbreakwait: DWORD;
    sv503_oplockbreakresponsewait: DWORD;
    sv503_enableoplocks: BOOL;
    sv503_enableoplockforceclose: BOOL;
    sv503_enablefcbopens: BOOL;
    sv503_enableraw: BOOL;
    sv503_enablesharednetdrives: BOOL;
    sv503_minfreeconnections: DWORD;
    sv503_maxfreeconnections: DWORD;
  end;
  {$EXTERNALSYM _SERVER_INFO_503}
  TServerInfo503 = _SERVER_INFO_503;
  SERVER_INFO_503 = _SERVER_INFO_503;
  {$EXTERNALSYM SERVER_INFO_503}

  PServerInfo599 = ^TServerInfo599;
  _SERVER_INFO_599 = record
    sv599_sessopens: DWORD;
    sv599_sessvcs: DWORD;
    sv599_opensearch: DWORD;
    sv599_sizreqbuf: DWORD;
    sv599_initworkitems: DWORD;
    sv599_maxworkitems: DWORD;
    sv599_rawworkitems: DWORD;
    sv599_irpstacksize: DWORD;
    sv599_maxrawbuflen: DWORD;
    sv599_sessusers: DWORD;
    sv599_sessconns: DWORD;
    sv599_maxpagedmemoryusage: DWORD;
    sv599_maxnonpagedmemoryusage: DWORD;
    sv599_enablesoftcompat: BOOL;
    sv599_enableforcedlogoff: BOOL;
    sv599_timesource: BOOL;
    sv599_acceptdownlevelapis: BOOL;
    sv599_lmannounce: BOOL;
    sv599_domain: LPWSTR;
    sv599_maxcopyreadlen: DWORD;
    sv599_maxcopywritelen: DWORD;
    sv599_minkeepsearch: DWORD;
    sv599_maxkeepsearch: DWORD;
    sv599_minkeepcomplsearch: DWORD;
    sv599_maxkeepcomplsearch: DWORD;
    sv599_threadcountadd: DWORD;
    sv599_numblockthreads: DWORD;
    sv599_scavtimeout: DWORD;
    sv599_minrcvqueue: DWORD;
    sv599_minfreeworkitems: DWORD;
    sv599_xactmemsize: DWORD;
    sv599_threadpriority: DWORD;
    sv599_maxmpxct: DWORD;
    sv599_oplockbreakwait: DWORD;
    sv599_oplockbreakresponsewait: DWORD;
    sv599_enableoplocks: BOOL;
    sv599_enableoplockforceclose: BOOL;
    sv599_enablefcbopens: BOOL;
    sv599_enableraw: BOOL;
    sv599_enablesharednetdrives: BOOL;
    sv599_minfreeconnections: DWORD;
    sv599_maxfreeconnections: DWORD;
    sv599_initsesstable: DWORD;
    sv599_initconntable: DWORD;
    sv599_initfiletable: DWORD;
    sv599_initsearchtable: DWORD;
    sv599_alertschedule: DWORD;
    sv599_errorthreshold: DWORD;
    sv599_networkerrorthreshold: DWORD;
    sv599_diskspacethreshold: DWORD;
    sv599_reserved: DWORD;
    sv599_maxlinkdelay: DWORD;
    sv599_minlinkthroughput: DWORD;
    sv599_linkinfovalidtime: DWORD;
    sv599_scavqosinfoupdatetime: DWORD;
    sv599_maxworkitemidletime: DWORD;
  end;
  {$EXTERNALSYM _SERVER_INFO_599}
  TServerInfo599 = _SERVER_INFO_599;
  SERVER_INFO_599 = _SERVER_INFO_599;
  {$EXTERNALSYM SERVER_INFO_599}

  PServerInfo598 = ^TServerInfo598;
  _SERVER_INFO_598 = record
    sv598_maxrawworkitems: DWORD;
    sv598_maxthreadsperqueue: DWORD;
    sv598_producttype: DWORD;
    sv598_serversize: DWORD;
    sv598_connectionlessautodisc: DWORD;
    sv598_sharingviolationretries: DWORD;
    sv598_sharingviolationdelay: DWORD;
    sv598_maxglobalopensearch: DWORD;
    sv598_removeduplicatesearches: DWORD;
    sv598_lockviolationoffset: DWORD;
    sv598_lockviolationdelay: DWORD;
    sv598_mdlreadswitchover: DWORD;
    sv598_cachedopenlimit: DWORD;
    sv598_otherqueueaffinity: DWORD;
    sv598_restrictnullsessaccess: BOOL;
    sv598_enablewfw311directipx: BOOL;
    sv598_queuesamplesecs: DWORD;
    sv598_balancecount: DWORD;
    sv598_preferredaffinity: DWORD;
    sv598_maxfreerfcbs: DWORD;
    sv598_maxfreemfcbs: DWORD;
    sv598_maxfreelfcbs: DWORD;
    sv598_maxfreepagedpoolchunks: DWORD;
    sv598_minpagedpoolchunksize: DWORD;
    sv598_maxpagedpoolchunksize: DWORD;
    sv598_sendsfrompreferredprocessor: BOOL;
    sv598_cacheddirectorylimit: DWORD;
    sv598_maxcopylength: DWORD;
    sv598_enablecompression: BOOL;
    sv598_autosharewks: BOOL;
    sv598_autoshareserver: BOOL;
    sv598_enablesecuritysignature: BOOL;
    sv598_requiresecuritysignature: BOOL;
    sv598_minclientbuffersize: DWORD;
    sv598_serverguid: TGUID;
    sv598_ConnectionNoSessionsTimeout: DWORD;
    sv598_IdleThreadTimeOut: DWORD;
    sv598_enableW9xsecuritysignature: BOOL;
  end;
  {$EXTERNALSYM _SERVER_INFO_598}
  TServerInfo598 = _SERVER_INFO_598;
  SERVER_INFO_598 = _SERVER_INFO_598;
  {$EXTERNALSYM SERVER_INFO_598}

  PServerInfo1005 = ^TServerInfo1005;
  _SERVER_INFO_1005 = record
    sv1005_comment: LPWSTR;
  end;
  {$EXTERNALSYM _SERVER_INFO_1005}
  TServerInfo1005 = _SERVER_INFO_1005;
  SERVER_INFO_1005 = _SERVER_INFO_1005;
  {$EXTERNALSYM SERVER_INFO_1005}

  PServerInfo1107 = ^TServerInfo1107;
  _SERVER_INFO_1107 = record
    sv1107_users: DWORD;
  end;
  {$EXTERNALSYM _SERVER_INFO_1107}
  TServerInfo1107 = _SERVER_INFO_1107;
  SERVER_INFO_1107 = _SERVER_INFO_1107;
  {$EXTERNALSYM SERVER_INFO_1107}

  PServerInfo1010 = ^TServerInfo1010;
  _SERVER_INFO_1010 = record
    sv1010_disc: LongInt;
  end;
  {$EXTERNALSYM _SERVER_INFO_1010}
  TServerInfo1010 = _SERVER_INFO_1010;
  SERVER_INFO_1010 = _SERVER_INFO_1010;
  {$EXTERNALSYM SERVER_INFO_1010}

  PServerInfo1016 = ^TServerInfo1016;
  _SERVER_INFO_1016 = record
    sv1016_hidden: BOOL;
  end;
  {$EXTERNALSYM _SERVER_INFO_1016}
  TServerInfo1016 = _SERVER_INFO_1016;
  SERVER_INFO_1016 = _SERVER_INFO_1016;
  {$EXTERNALSYM SERVER_INFO_1016}

  PServerInfo1017 = ^TServerInfo1017;
  _SERVER_INFO_1017 = record
    sv1017_announce: DWORD;
  end;
  {$EXTERNALSYM _SERVER_INFO_1017}
  TServerInfo1017 = _SERVER_INFO_1017;
  SERVER_INFO_1017 = _SERVER_INFO_1017;
  {$EXTERNALSYM SERVER_INFO_1017}

  PServerInfo1018 = ^TServerInfo1018;
  _SERVER_INFO_1018 = record
    sv1018_anndelta: DWORD;
  end;
  {$EXTERNALSYM _SERVER_INFO_1018}
  TServerInfo1018 = _SERVER_INFO_1018;
  SERVER_INFO_1018 = _SERVER_INFO_1018;
  {$EXTERNALSYM SERVER_INFO_1018}

  PServerInfo1501 = ^TServerInfo1501;
  _SERVER_INFO_1501 = record
    sv1501_sessopens: DWORD;
  end;
  {$EXTERNALSYM _SERVER_INFO_1501}
  TServerInfo1501 = _SERVER_INFO_1501;
  SERVER_INFO_1501 = _SERVER_INFO_1501;
  {$EXTERNALSYM SERVER_INFO_1501}

  PServerInfo1502 = ^TServerInfo1502;
  _SERVER_INFO_1502 = record
    sv1502_sessvcs: DWORD;
  end;
  {$EXTERNALSYM _SERVER_INFO_1502}
  TServerInfo1502 = _SERVER_INFO_1502;
  SERVER_INFO_1502 = _SERVER_INFO_1502;
  {$EXTERNALSYM SERVER_INFO_1502}

  PServerInfo1503 = ^TServerInfo1503;
  _SERVER_INFO_1503 = record
    sv1503_opensearch: DWORD;
  end;
  {$EXTERNALSYM _SERVER_INFO_1503}
  TServerInfo1503 = _SERVER_INFO_1503;
  SERVER_INFO_1503 = _SERVER_INFO_1503;
  {$EXTERNALSYM SERVER_INFO_1503}

  PServerInfo1506 = ^TServerInfo1506;
  _SERVER_INFO_1506 = record
    sv1506_maxworkitems: DWORD;
  end;
  {$EXTERNALSYM _SERVER_INFO_1506}
  TServerInfo1506 = _SERVER_INFO_1506;
  SERVER_INFO_1506 = _SERVER_INFO_1506;
  {$EXTERNALSYM SERVER_INFO_1506}

  PServerInfo1509 = ^TServerInfo1509;
  _SERVER_INFO_1509 = record
    sv1509_maxrawbuflen: DWORD;
  end;
  {$EXTERNALSYM _SERVER_INFO_1509}
  TServerInfo1509 = _SERVER_INFO_1509;
  SERVER_INFO_1509 = _SERVER_INFO_1509;
  {$EXTERNALSYM SERVER_INFO_1509}

  PServerInfo1510 = ^TServerInfo1510;
  _SERVER_INFO_1510 = record
    sv1510_sessusers: DWORD;
  end;
  {$EXTERNALSYM _SERVER_INFO_1510}
  TServerInfo1510 = _SERVER_INFO_1510;
  SERVER_INFO_1510 = _SERVER_INFO_1510;
  {$EXTERNALSYM SERVER_INFO_1510}

  PServerInfo1511 = ^TServerInfo1511;
  _SERVER_INFO_1511 = record
    sv1511_sessconns: DWORD;
  end;
  {$EXTERNALSYM _SERVER_INFO_1511}
  TServerInfo1511 = _SERVER_INFO_1511;
  SERVER_INFO_1511 = _SERVER_INFO_1511;
  {$EXTERNALSYM SERVER_INFO_1511}

  PServerInfo1512 = ^TServerInfo1512;
  _SERVER_INFO_1512 = record
    sv1512_maxnonpagedmemoryusage: DWORD;
  end;
  {$EXTERNALSYM _SERVER_INFO_1512}
  TServerInfo1512 = _SERVER_INFO_1512;
  SERVER_INFO_1512 = _SERVER_INFO_1512;
  {$EXTERNALSYM SERVER_INFO_1512}

  PServerInfo1513 = ^TServerInfo1513;
  _SERVER_INFO_1513 = record
    sv1513_maxpagedmemoryusage: DWORD;
  end;
  {$EXTERNALSYM _SERVER_INFO_1513}
  TServerInfo1513 = _SERVER_INFO_1513;
  SERVER_INFO_1513 = _SERVER_INFO_1513;
  {$EXTERNALSYM SERVER_INFO_1513}

  PServerInfo1514 = ^TServerInfo1514;
  _SERVER_INFO_1514 = record
    sv1514_enablesoftcompat: BOOL;
  end;
  {$EXTERNALSYM _SERVER_INFO_1514}
  TServerInfo1514 = _SERVER_INFO_1514;
  SERVER_INFO_1514 = _SERVER_INFO_1514;
  {$EXTERNALSYM SERVER_INFO_1514}

  PServerInfo1515 = ^TServerInfo1515;
  _SERVER_INFO_1515 = record
    sv1515_enableforcedlogoff: BOOL;
  end;
  {$EXTERNALSYM _SERVER_INFO_1515}
  TServerInfo1515 = _SERVER_INFO_1515;
  SERVER_INFO_1515 = _SERVER_INFO_1515;
  {$EXTERNALSYM SERVER_INFO_1515}

  PServerInfo1516 = ^TServerInfo1516;
  _SERVER_INFO_1516 = record
    sv1516_timesource: BOOL;
  end;
  {$EXTERNALSYM _SERVER_INFO_1516}
  TServerInfo1516 = _SERVER_INFO_1516;
  SERVER_INFO_1516 = _SERVER_INFO_1516;
  {$EXTERNALSYM SERVER_INFO_1516}

  PServerInfo1518 = ^TServerInfo1518;
  _SERVER_INFO_1518 = record
    sv1518_lmannounce: BOOL;
  end;
  {$EXTERNALSYM _SERVER_INFO_1518}
  TServerInfo1518 = _SERVER_INFO_1518;
  SERVER_INFO_1518 = _SERVER_INFO_1518;
  {$EXTERNALSYM SERVER_INFO_1518}

  PServerInfo1520 = ^TServerInfo1520;
  _SERVER_INFO_1520 = record
    sv1520_maxcopyreadlen: DWORD;
  end;
  {$EXTERNALSYM _SERVER_INFO_1520}
  TServerInfo1520 = _SERVER_INFO_1520;
  SERVER_INFO_1520 = _SERVER_INFO_1520;
  {$EXTERNALSYM SERVER_INFO_1520}

  PServerInfo1521 = ^TServerInfo1521;
  _SERVER_INFO_1521 = record
    sv1521_maxcopywritelen: DWORD;
  end;
  {$EXTERNALSYM _SERVER_INFO_1521}
  TServerInfo1521 = _SERVER_INFO_1521;
  SERVER_INFO_1521 = _SERVER_INFO_1521;
  {$EXTERNALSYM SERVER_INFO_1521}

  PServerInfo1522 = ^TServerInfo1522;
  _SERVER_INFO_1522 = record
    sv1522_minkeepsearch: DWORD;
  end;
  {$EXTERNALSYM _SERVER_INFO_1522}
  TServerInfo1522 = _SERVER_INFO_1522;
  SERVER_INFO_1522 = _SERVER_INFO_1522;
  {$EXTERNALSYM SERVER_INFO_1522}

  PServerInfo1523 = ^TServerInfo1523;
  _SERVER_INFO_1523 = record
    sv1523_maxkeepsearch: DWORD;
  end;
  {$EXTERNALSYM _SERVER_INFO_1523}
  TServerInfo1523 = _SERVER_INFO_1523;
  SERVER_INFO_1523 = _SERVER_INFO_1523;
  {$EXTERNALSYM SERVER_INFO_1523}

  PServerInfo1524 = ^TServerInfo1524;
  _SERVER_INFO_1524 = record
    sv1524_minkeepcomplsearch: DWORD;
  end;
  {$EXTERNALSYM _SERVER_INFO_1524}
  TServerInfo1524 = _SERVER_INFO_1524;
  SERVER_INFO_1524 = _SERVER_INFO_1524;
  {$EXTERNALSYM SERVER_INFO_1524}

  PServerInfo1525 = ^TServerInfo1525;
  _SERVER_INFO_1525 = record
    sv1525_maxkeepcomplsearch: DWORD;
  end;
  {$EXTERNALSYM _SERVER_INFO_1525}
  TServerInfo1525 = _SERVER_INFO_1525;
  SERVER_INFO_1525 = _SERVER_INFO_1525;
  {$EXTERNALSYM SERVER_INFO_1525}

  PServerInfo1528 = ^TServerInfo1528;
  _SERVER_INFO_1528 = record
    sv1528_scavtimeout: DWORD;
  end;
  {$EXTERNALSYM _SERVER_INFO_1528}
  TServerInfo1528 = _SERVER_INFO_1528;
  SERVER_INFO_1528 = _SERVER_INFO_1528;
  {$EXTERNALSYM SERVER_INFO_1528}

  PServerInfo1529 = ^TServerInfo1529;
  _SERVER_INFO_1529 = record
    sv1529_minrcvqueue: DWORD;
  end;
  {$EXTERNALSYM _SERVER_INFO_1529}
  TServerInfo1529 = _SERVER_INFO_1529;
  SERVER_INFO_1529 = _SERVER_INFO_1529;
  {$EXTERNALSYM SERVER_INFO_1529}

  PServerInfo1530 = ^TServerInfo1530;
  _SERVER_INFO_1530 = record
    sv1530_minfreeworkitems: DWORD;
  end;
  {$EXTERNALSYM _SERVER_INFO_1530}
  TServerInfo1530 = _SERVER_INFO_1530;
  SERVER_INFO_1530 = _SERVER_INFO_1530;
  {$EXTERNALSYM SERVER_INFO_1530}

  PServerInfo1533 = ^TServerInfo1533;
  _SERVER_INFO_1533 = record
    sv1533_maxmpxct: DWORD;
  end;
  {$EXTERNALSYM _SERVER_INFO_1533}
  TServerInfo1533 = _SERVER_INFO_1533;
  SERVER_INFO_1533 = _SERVER_INFO_1533;
  {$EXTERNALSYM SERVER_INFO_1533}

  PServerInfo1534 = ^TServerInfo1534;
  _SERVER_INFO_1534 = record
    sv1534_oplockbreakwait: DWORD;
  end;
  {$EXTERNALSYM _SERVER_INFO_1534}
  TServerInfo1534 = _SERVER_INFO_1534;
  SERVER_INFO_1534 = _SERVER_INFO_1534;
  {$EXTERNALSYM SERVER_INFO_1534}

  PServerInfo1535 = ^TServerInfo1535;
  _SERVER_INFO_1535 = record
    sv1535_oplockbreakresponsewait: DWORD;
  end;
  {$EXTERNALSYM _SERVER_INFO_1535}
  TServerInfo1535 = _SERVER_INFO_1535;
  SERVER_INFO_1535 = _SERVER_INFO_1535;
  {$EXTERNALSYM SERVER_INFO_1535}

  PServerInfo1536 = ^TServerInfo1536;
  _SERVER_INFO_1536 = record
    sv1536_enableoplocks: BOOL;
  end;
  {$EXTERNALSYM _SERVER_INFO_1536}
  TServerInfo1536 = _SERVER_INFO_1536;
  SERVER_INFO_1536 = _SERVER_INFO_1536;
  {$EXTERNALSYM SERVER_INFO_1536}

  PServerInfo1537 = ^TServerInfo1537;
  _SERVER_INFO_1537 = record
    sv1537_enableoplockforceclose: BOOL;
  end;
  {$EXTERNALSYM _SERVER_INFO_1537}
  TServerInfo1537 = _SERVER_INFO_1537;
  SERVER_INFO_1537 = _SERVER_INFO_1537;
  {$EXTERNALSYM SERVER_INFO_1537}

  PServerInfo1538 = ^TServerInfo1538;
  _SERVER_INFO_1538 = record
    sv1538_enablefcbopens: BOOL;
  end;
  {$EXTERNALSYM _SERVER_INFO_1538}
  TServerInfo1538 = _SERVER_INFO_1538;
  SERVER_INFO_1538 = _SERVER_INFO_1538;
  {$EXTERNALSYM SERVER_INFO_1538}

  PServerInfo1539 = ^TServerInfo1539;
  _SERVER_INFO_1539 = record
    sv1539_enableraw: BOOL;
  end;
  {$EXTERNALSYM _SERVER_INFO_1539}
  TServerInfo1539 = _SERVER_INFO_1539;
  SERVER_INFO_1539 = _SERVER_INFO_1539;
  {$EXTERNALSYM SERVER_INFO_1539}

  PServerInfo1540 = ^TServerInfo1540;
  _SERVER_INFO_1540 = record
    sv1540_enablesharednetdrives: BOOL;
  end;
  {$EXTERNALSYM _SERVER_INFO_1540}
  TServerInfo1540 = _SERVER_INFO_1540;
  SERVER_INFO_1540 = _SERVER_INFO_1540;
  {$EXTERNALSYM SERVER_INFO_1540}

  PServerInfo1541 = ^TServerInfo1541;
  _SERVER_INFO_1541 = record
    sv1541_minfreeconnections: BOOL;
  end;
  {$EXTERNALSYM _SERVER_INFO_1541}
  TServerInfo1541 = _SERVER_INFO_1541;
  SERVER_INFO_1541 = _SERVER_INFO_1541;
  {$EXTERNALSYM SERVER_INFO_1541}

  PServerInfo1542 = ^TServerInfo1542;
  _SERVER_INFO_1542 = record
    sv1542_maxfreeconnections: BOOL;
  end;
  {$EXTERNALSYM _SERVER_INFO_1542}
  TServerInfo1542 = _SERVER_INFO_1542;
  SERVER_INFO_1542 = _SERVER_INFO_1542;
  {$EXTERNALSYM SERVER_INFO_1542}

  PServerInfo1543 = ^TServerInfo1543;
  _SERVER_INFO_1543 = record
    sv1543_initsesstable: DWORD;
  end;
  {$EXTERNALSYM _SERVER_INFO_1543}
  TServerInfo1543 = _SERVER_INFO_1543;
  SERVER_INFO_1543 = _SERVER_INFO_1543;
  {$EXTERNALSYM SERVER_INFO_1543}

  PServerInfo1544 = ^TServerInfo1544;
  _SERVER_INFO_1544 = record
    sv1544_initconntable: DWORD;
  end;
  {$EXTERNALSYM _SERVER_INFO_1544}
  TServerInfo1544 = _SERVER_INFO_1544;
  SERVER_INFO_1544 = _SERVER_INFO_1544;
  {$EXTERNALSYM SERVER_INFO_1544}

  PServerInfo1545 = ^TServerInfo1545;
  _SERVER_INFO_1545 = record
    sv1545_initfiletable: DWORD;
  end;
  {$EXTERNALSYM _SERVER_INFO_1545}
  TServerInfo1545 = _SERVER_INFO_1545;
  SERVER_INFO_1545 = _SERVER_INFO_1545;
  {$EXTERNALSYM SERVER_INFO_1545}

  PServerInfo1546 = ^TServerInfo1546;
  _SERVER_INFO_1546 = record
    sv1546_initsearchtable: DWORD;
  end;
  {$EXTERNALSYM _SERVER_INFO_1546}
  TServerInfo1546 = _SERVER_INFO_1546;
  SERVER_INFO_1546 = _SERVER_INFO_1546;
  {$EXTERNALSYM SERVER_INFO_1546}

  PServerInfo1547 = ^TServerInfo1547;
  _SERVER_INFO_1547 = record
    sv1547_alertschedule: DWORD;
  end;
  {$EXTERNALSYM _SERVER_INFO_1547}
  TServerInfo1547 = _SERVER_INFO_1547;
  SERVER_INFO_1547 = _SERVER_INFO_1547;
  {$EXTERNALSYM SERVER_INFO_1547}

  PServerInfo1548 = ^TServerInfo1548;
  _SERVER_INFO_1548 = record
    sv1548_errorthreshold: DWORD;
  end;
  {$EXTERNALSYM _SERVER_INFO_1548}
  TServerInfo1548 = _SERVER_INFO_1548;
  SERVER_INFO_1548 = _SERVER_INFO_1548;
  {$EXTERNALSYM SERVER_INFO_1548}

  PServerInfo1549 = ^TServerInfo1549;
  _SERVER_INFO_1549 = record
    sv1549_networkerrorthreshold: DWORD;
  end;
  {$EXTERNALSYM _SERVER_INFO_1549}
  TServerInfo1549 = _SERVER_INFO_1549;
  SERVER_INFO_1549 = _SERVER_INFO_1549;
  {$EXTERNALSYM SERVER_INFO_1549}

  PServerInfo1550 = ^TServerInfo1550;
  _SERVER_INFO_1550 = record
    sv1550_diskspacethreshold: DWORD;
  end;
  {$EXTERNALSYM _SERVER_INFO_1550}
  TServerInfo1550 = _SERVER_INFO_1550;
  SERVER_INFO_1550 = _SERVER_INFO_1550;
  {$EXTERNALSYM SERVER_INFO_1550}

  PServerInfo1552 = ^TServerInfo1552;
  _SERVER_INFO_1552 = record
    sv1552_maxlinkdelay: DWORD;
  end;
  {$EXTERNALSYM _SERVER_INFO_1552}
  TServerInfo1552 = _SERVER_INFO_1552;
  SERVER_INFO_1552 = _SERVER_INFO_1552;
  {$EXTERNALSYM SERVER_INFO_1552}

  PServerInfo1553 = ^TServerInfo1553;
  _SERVER_INFO_1553 = record
    sv1553_minlinkthroughput: DWORD;
  end;
  {$EXTERNALSYM _SERVER_INFO_1553}
  TServerInfo1553 = _SERVER_INFO_1553;
  SERVER_INFO_1553 = _SERVER_INFO_1553;
  {$EXTERNALSYM SERVER_INFO_1553}

  PServerInfo1554 = ^TServerInfo1554;
  _SERVER_INFO_1554 = record
    sv1554_linkinfovalidtime: DWORD;
  end;
  {$EXTERNALSYM _SERVER_INFO_1554}
  TServerInfo1554 = _SERVER_INFO_1554;
  SERVER_INFO_1554 = _SERVER_INFO_1554;
  {$EXTERNALSYM SERVER_INFO_1554}

  PServerInfo1555 = ^TServerInfo1555;
  _SERVER_INFO_1555 = record
    sv1555_scavqosinfoupdatetime: DWORD;
  end;
  {$EXTERNALSYM _SERVER_INFO_1555}
  TServerInfo1555 = _SERVER_INFO_1555;
  SERVER_INFO_1555 = _SERVER_INFO_1555;
  {$EXTERNALSYM SERVER_INFO_1555}

  PServerInfo1556 = ^TServerInfo1556;
  _SERVER_INFO_1556 = record
    sv1556_maxworkitemidletime: DWORD;
  end;
  {$EXTERNALSYM _SERVER_INFO_1556}
  TServerInfo1556 = _SERVER_INFO_1556;
  SERVER_INFO_1556 = _SERVER_INFO_1556;
  {$EXTERNALSYM SERVER_INFO_1556}

  PServerInfo1557 = ^TServerInfo1557;
  _SERVER_INFO_1557 = record
    sv1557_maxrawworkitems: DWORD;
  end;
  {$EXTERNALSYM _SERVER_INFO_1557}
  TServerInfo1557 = _SERVER_INFO_1557;
  SERVER_INFO_1557 = _SERVER_INFO_1557;
  {$EXTERNALSYM SERVER_INFO_1557}

  PServerInfo1560 = ^TServerInfo1560;
  _SERVER_INFO_1560 = record
    sv1560_producttype: DWORD;
  end;
  {$EXTERNALSYM _SERVER_INFO_1560}
  TServerInfo1560 = _SERVER_INFO_1560;
  SERVER_INFO_1560 = _SERVER_INFO_1560;
  {$EXTERNALSYM SERVER_INFO_1560}

  PServerInfo1561 = ^TServerInfo1561;
  _SERVER_INFO_1561 = record
    sv1561_serversize: DWORD;
  end;
  {$EXTERNALSYM _SERVER_INFO_1561}
  TServerInfo1561 = _SERVER_INFO_1561;
  SERVER_INFO_1561 = _SERVER_INFO_1561;
  {$EXTERNALSYM SERVER_INFO_1561}

  PServerInfo1562 = ^TServerInfo1562;
  _SERVER_INFO_1562 = record
    sv1562_connectionlessautodisc: DWORD;
  end;
  {$EXTERNALSYM _SERVER_INFO_1562}
  TServerInfo1562 = _SERVER_INFO_1562;
  SERVER_INFO_1562 = _SERVER_INFO_1562;
  {$EXTERNALSYM SERVER_INFO_1562}

  PServerInfo1563 = ^TServerInfo1563;
  _SERVER_INFO_1563 = record
    sv1563_sharingviolationretries: DWORD;
  end;
  {$EXTERNALSYM _SERVER_INFO_1563}
  TServerInfo1563 = _SERVER_INFO_1563;
  SERVER_INFO_1563 = _SERVER_INFO_1563;
  {$EXTERNALSYM SERVER_INFO_1563}

  PServerInfo1564 = ^TServerInfo1564;
  _SERVER_INFO_1564 = record
    sv1564_sharingviolationdelay: DWORD;
  end;
  {$EXTERNALSYM _SERVER_INFO_1564}
  TServerInfo1564 = _SERVER_INFO_1564;
  SERVER_INFO_1564 = _SERVER_INFO_1564;
  {$EXTERNALSYM SERVER_INFO_1564}

  PServerInfo1565 = ^TServerInfo1565;
  _SERVER_INFO_1565 = record
    sv1565_maxglobalopensearch: DWORD;
  end;
  {$EXTERNALSYM _SERVER_INFO_1565}
  TServerInfo1565 = _SERVER_INFO_1565;
  SERVER_INFO_1565 = _SERVER_INFO_1565;
  {$EXTERNALSYM SERVER_INFO_1565}

  PServerInfo1566 = ^TServerInfo1566;
  _SERVER_INFO_1566 = record
    sv1566_removeduplicatesearches: BOOL;
  end;
  {$EXTERNALSYM _SERVER_INFO_1566}
  TServerInfo1566 = _SERVER_INFO_1566;
  SERVER_INFO_1566 = _SERVER_INFO_1566;
  {$EXTERNALSYM SERVER_INFO_1566}

  PServerInfo1567 = ^TServerInfo1567;
  _SERVER_INFO_1567 = record
    sv1567_lockviolationretries: DWORD;
  end;
  {$EXTERNALSYM _SERVER_INFO_1567}
  TServerInfo1567 = _SERVER_INFO_1567;
  SERVER_INFO_1567 = _SERVER_INFO_1567;
  {$EXTERNALSYM SERVER_INFO_1567}

  PServerInfo1568 = ^TServerInfo1568;
  _SERVER_INFO_1568 = record
    sv1568_lockviolationoffset: DWORD;
  end;
  {$EXTERNALSYM _SERVER_INFO_1568}
  TServerInfo1568 = _SERVER_INFO_1568;
  SERVER_INFO_1568 = _SERVER_INFO_1568;
  {$EXTERNALSYM SERVER_INFO_1568}

  PServerInfo1569 = ^TServerInfo1569;
  _SERVER_INFO_1569 = record
    sv1569_lockviolationdelay: DWORD;
  end;
  {$EXTERNALSYM _SERVER_INFO_1569}
  TServerInfo1569 = _SERVER_INFO_1569;
  SERVER_INFO_1569 = _SERVER_INFO_1569;
  {$EXTERNALSYM SERVER_INFO_1569}

  PServerInfo1570 = ^TServerInfo1570;
  _SERVER_INFO_1570 = record
    sv1570_mdlreadswitchover: DWORD;
  end;
  {$EXTERNALSYM _SERVER_INFO_1570}
  TServerInfo1570 = _SERVER_INFO_1570;
  SERVER_INFO_1570 = _SERVER_INFO_1570;
  {$EXTERNALSYM SERVER_INFO_1570}

  PServerInfo1571 = ^TServerInfo1571;
  _SERVER_INFO_1571 = record
    sv1571_cachedopenlimit: DWORD;
  end;
  {$EXTERNALSYM _SERVER_INFO_1571}
  TServerInfo1571 = _SERVER_INFO_1571;
  SERVER_INFO_1571 = _SERVER_INFO_1571;
  {$EXTERNALSYM SERVER_INFO_1571}

  PServerInfo1572 = ^TServerInfo1572;
  _SERVER_INFO_1572 = record
    sv1572_criticalthreads: DWORD;
  end;
  {$EXTERNALSYM _SERVER_INFO_1572}
  TServerInfo1572 = _SERVER_INFO_1572;
  SERVER_INFO_1572 = _SERVER_INFO_1572;
  {$EXTERNALSYM SERVER_INFO_1572}

  PServerInfo1573 = ^TServerInfo1573;
  _SERVER_INFO_1573 = record
    sv1573_restrictnullsessaccess: DWORD;
  end;
  {$EXTERNALSYM _SERVER_INFO_1573}
  TServerInfo1573 = _SERVER_INFO_1573;
  SERVER_INFO_1573 = _SERVER_INFO_1573;
  {$EXTERNALSYM SERVER_INFO_1573}

  PServerInfo1574 = ^TServerInfo1574;
  _SERVER_INFO_1574 = record
    sv1574_enablewfw311directipx: DWORD;
  end;
  {$EXTERNALSYM _SERVER_INFO_1574}
  TServerInfo1574 = _SERVER_INFO_1574;
  SERVER_INFO_1574 = _SERVER_INFO_1574;
  {$EXTERNALSYM SERVER_INFO_1574}

  PServerInfo1575 = ^TServerInfo1575;
  _SERVER_INFO_1575 = record
    sv1575_otherqueueaffinity: DWORD;
  end;
  {$EXTERNALSYM _SERVER_INFO_1575}
  TServerInfo1575 = _SERVER_INFO_1575;
  SERVER_INFO_1575 = _SERVER_INFO_1575;
  {$EXTERNALSYM SERVER_INFO_1575}

  PServerInfo1576 = ^TServerInfo1576;
  _SERVER_INFO_1576 = record
    sv1576_queuesamplesecs: DWORD;
  end;
  {$EXTERNALSYM _SERVER_INFO_1576}
  TServerInfo1576 = _SERVER_INFO_1576;
  SERVER_INFO_1576 = _SERVER_INFO_1576;
  {$EXTERNALSYM SERVER_INFO_1576}

  PServerInfo1577 = ^TServerInfo1577;
  _SERVER_INFO_1577 = record
    sv1577_balancecount: DWORD;
  end;
  {$EXTERNALSYM _SERVER_INFO_1577}
  TServerInfo1577 = _SERVER_INFO_1577;
  SERVER_INFO_1577 = _SERVER_INFO_1577;
  {$EXTERNALSYM SERVER_INFO_1577}

  PServerInfo1578 = ^TServerInfo1578;
  _SERVER_INFO_1578 = record
    sv1578_preferredaffinity: DWORD;
  end;
  {$EXTERNALSYM _SERVER_INFO_1578}
  TServerInfo1578 = _SERVER_INFO_1578;
  SERVER_INFO_1578 = _SERVER_INFO_1578;
  {$EXTERNALSYM SERVER_INFO_1578}

  PServerInfo1579 = ^TServerInfo1579;
  _SERVER_INFO_1579 = record
    sv1579_maxfreerfcbs: DWORD;
  end;
  {$EXTERNALSYM _SERVER_INFO_1579}
  TServerInfo1579 = _SERVER_INFO_1579;
  SERVER_INFO_1579 = _SERVER_INFO_1579;
  {$EXTERNALSYM SERVER_INFO_1579}

  PServerInfo1580 = ^TServerInfo1580;
  _SERVER_INFO_1580 = record
    sv1580_maxfreemfcbs: DWORD;
  end;
  {$EXTERNALSYM _SERVER_INFO_1580}
  TServerInfo1580 = _SERVER_INFO_1580;
  SERVER_INFO_1580 = _SERVER_INFO_1580;
  {$EXTERNALSYM SERVER_INFO_1580}

  PServerInfo1581 = ^TServerInfo1581;
  _SERVER_INFO_1581 = record
    sv1581_maxfreemlcbs: DWORD;
  end;
  {$EXTERNALSYM _SERVER_INFO_1581}
  TServerInfo1581 = _SERVER_INFO_1581;
  SERVER_INFO_1581 = _SERVER_INFO_1581;
  {$EXTERNALSYM SERVER_INFO_1581}

  PServerInfo1582 = ^TServerInfo1582;
  _SERVER_INFO_1582 = record
    sv1582_maxfreepagedpoolchunks: DWORD;
  end;
  {$EXTERNALSYM _SERVER_INFO_1582}
  TServerInfo1582 = _SERVER_INFO_1582;
  SERVER_INFO_1582 = _SERVER_INFO_1582;
  {$EXTERNALSYM SERVER_INFO_1582}

  PServerInfo1583 = ^TServerInfo1583;
  _SERVER_INFO_1583 = record
    sv1583_minpagedpoolchunksize: DWORD;
  end;
  {$EXTERNALSYM _SERVER_INFO_1583}
  TServerInfo1583 = _SERVER_INFO_1583;
  SERVER_INFO_1583 = _SERVER_INFO_1583;
  {$EXTERNALSYM SERVER_INFO_1583}

  PServerInfo1584 = ^TServerInfo1584;
  _SERVER_INFO_1584 = record
    sv1584_maxpagedpoolchunksize: DWORD;
  end;
  {$EXTERNALSYM _SERVER_INFO_1584}
  TServerInfo1584 = _SERVER_INFO_1584;
  SERVER_INFO_1584 = _SERVER_INFO_1584;
  {$EXTERNALSYM SERVER_INFO_1584}

  PServerInfo1585 = ^TServerInfo1585;
  _SERVER_INFO_1585 = record
    sv1585_sendsfrompreferredprocessor: BOOL;
  end;
  {$EXTERNALSYM _SERVER_INFO_1585}
  TServerInfo1585 = _SERVER_INFO_1585;
  SERVER_INFO_1585 = _SERVER_INFO_1585;
  {$EXTERNALSYM SERVER_INFO_1585}

  PServerInfo1586 = ^TServerInfo1586;
  _SERVER_INFO_1586 = record
    sv1586_maxthreadsperqueue: DWORD;
  end;
  {$EXTERNALSYM _SERVER_INFO_1586}
  TServerInfo1586 = _SERVER_INFO_1586;
  SERVER_INFO_1586 = _SERVER_INFO_1586;
  {$EXTERNALSYM SERVER_INFO_1586}

  PServerInfo1587 = ^TServerInfo1587;
  _SERVER_INFO_1587 = record
    sv1587_cacheddirectorylimit: DWORD;
  end;
  {$EXTERNALSYM _SERVER_INFO_1587}
  TServerInfo1587 = _SERVER_INFO_1587;
  SERVER_INFO_1587 = _SERVER_INFO_1587;
  {$EXTERNALSYM SERVER_INFO_1587}

  PServerInfo1588 = ^TServerInfo1588;
  _SERVER_INFO_1588 = record
    sv1588_maxcopylength: DWORD;
  end;
  {$EXTERNALSYM _SERVER_INFO_1588}
  TServerInfo1588 = _SERVER_INFO_1588;
  SERVER_INFO_1588 = _SERVER_INFO_1588;
  {$EXTERNALSYM SERVER_INFO_1588}

  PServerInfo1590 = ^TServerInfo1590;
  _SERVER_INFO_1590 = record
    sv1590_enablecompression: DWORD;
  end;
  {$EXTERNALSYM _SERVER_INFO_1590}
  TServerInfo1590 = _SERVER_INFO_1590;
  SERVER_INFO_1590 = _SERVER_INFO_1590;
  {$EXTERNALSYM SERVER_INFO_1590}

  PServerInfo1591 = ^TServerInfo1591;
  _SERVER_INFO_1591 = record
    sv1591_autosharewks: DWORD;
  end;
  {$EXTERNALSYM _SERVER_INFO_1591}
  TServerInfo1591 = _SERVER_INFO_1591;
  SERVER_INFO_1591 = _SERVER_INFO_1591;
  {$EXTERNALSYM SERVER_INFO_1591}

  PServerInfo1592 = ^TServerInfo1592;
  _SERVER_INFO_1592 = record
    sv1592_autosharewks: DWORD;
  end;
  {$EXTERNALSYM _SERVER_INFO_1592}
  TServerInfo1592 = _SERVER_INFO_1592;
  SERVER_INFO_1592 = _SERVER_INFO_1592;
  {$EXTERNALSYM SERVER_INFO_1592}

  PServerInfo1593 = ^TServerInfo1593;
  _SERVER_INFO_1593 = record
    sv1593_enablesecuritysignature: DWORD;
  end;
  {$EXTERNALSYM _SERVER_INFO_1593}
  TServerInfo1593 = _SERVER_INFO_1593;
  SERVER_INFO_1593 = _SERVER_INFO_1593;
  {$EXTERNALSYM SERVER_INFO_1593}

  PServerInfo1594 = ^TServerInfo1594;
  _SERVER_INFO_1594 = record
    sv1594_requiresecuritysignature: DWORD;
  end;
  {$EXTERNALSYM _SERVER_INFO_1594}
  TServerInfo1594 = _SERVER_INFO_1594;
  SERVER_INFO_1594 = _SERVER_INFO_1594;
  {$EXTERNALSYM SERVER_INFO_1594}

  PServerInfo1595 = ^TServerInfo1595;
  _SERVER_INFO_1595 = record
    sv1595_minclientbuffersize: DWORD;
  end;
  {$EXTERNALSYM _SERVER_INFO_1595}
  TServerInfo1595 = _SERVER_INFO_1595;
  SERVER_INFO_1595 = _SERVER_INFO_1595;
  {$EXTERNALSYM SERVER_INFO_1595}

  PServerInfo1596 = ^TServerInfo1596;
  _SERVER_INFO_1596 = record
    sv1596_ConnectionNoSessionsTimeout: DWORD;
  end;
  {$EXTERNALSYM _SERVER_INFO_1596}
  TServerInfo1596 = _SERVER_INFO_1596;
  SERVER_INFO_1596 = _SERVER_INFO_1596;
  {$EXTERNALSYM SERVER_INFO_1596}

  PServerInfo1597 = ^TServerInfo1597;
  _SERVER_INFO_1597 = record
    sv1597_IdleThreadTimeOut: DWORD;
  end;
  {$EXTERNALSYM _SERVER_INFO_1597}
  TServerInfo1597 = _SERVER_INFO_1597;
  SERVER_INFO_1597 = _SERVER_INFO_1597;
  {$EXTERNALSYM SERVER_INFO_1597}

  PServerInfo1598 = ^TServerInfo1598;
  _SERVER_INFO_1598 = record
    sv1598_enableW9xsecuritysignature: DWORD;
  end;
  {$EXTERNALSYM _SERVER_INFO_1598}
  TServerInfo1598 = _SERVER_INFO_1598;
  SERVER_INFO_1598 = _SERVER_INFO_1598;
  {$EXTERNALSYM SERVER_INFO_1598}

// A special structure definition is required in order for this
// structure to work with RPC.  The problem is that having addresslength
// indicate the number of bytes in address means that RPC must know the
// link between the two.

  PServerTransportInfo0 = ^TServerTransportInfo0;
  _SERVER_TRANSPORT_INFO_0 = record
    svti0_numberofvcs: DWORD;
    svti0_transportname: LPWSTR;
    svti0_transportaddress: Pointer;
    svti0_transportaddresslength: DWORD;
    svti0_networkaddress: LPWSTR;
  end;
  {$EXTERNALSYM _SERVER_TRANSPORT_INFO_0}
  TServerTransportInfo0 = _SERVER_TRANSPORT_INFO_0;
  SERVER_TRANSPORT_INFO_0 = _SERVER_TRANSPORT_INFO_0;
  {$EXTERNALSYM SERVER_TRANSPORT_INFO_0}

  PServerTransportInfo1 = ^TServerTransportInfo1;
  _SERVER_TRANSPORT_INFO_1 = record
    svti1_numberofvcs: DWORD;
    svti1_transportname: LPWSTR;
    svti1_transportaddress: Pointer;
    svti1_transportaddresslength: DWORD;
    svti1_networkaddress: LPWSTR;
    svti1_domain: LPWSTR;
  end;
  {$EXTERNALSYM _SERVER_TRANSPORT_INFO_1}
  TServerTransportInfo1 = _SERVER_TRANSPORT_INFO_1;
  SERVER_TRANSPORT_INFO_1 = _SERVER_TRANSPORT_INFO_1;
  {$EXTERNALSYM SERVER_TRANSPORT_INFO_1}

  PServerTransportInfo2 = ^TServerTransportInfo2;
  _SERVER_TRANSPORT_INFO_2 = record
    svti2_numberofvcs: DWORD;
    svti2_transportname: LPWSTR;
    svti2_transportaddress: Pointer;
    svti2_transportaddresslength: DWORD;
    svti2_networkaddress: LPWSTR;
    svti2_domain: LPWSTR;
    svti2_flags: ULONG;
  end;
  {$EXTERNALSYM _SERVER_TRANSPORT_INFO_2}
  TServerTransportInfo2 = _SERVER_TRANSPORT_INFO_2;
  SERVER_TRANSPORT_INFO_2 = _SERVER_TRANSPORT_INFO_2;
  {$EXTERNALSYM SERVER_TRANSPORT_INFO_2}

  PServerTransportInfo3 = ^TServerTransportInfo3;
  _SERVER_TRANSPORT_INFO_3 = record
    svti3_numberofvcs: DWORD;
    svti3_transportname: LPWSTR;
    svti3_transportaddress: Pointer;
    svti3_transportaddresslength: DWORD;
    svti3_networkaddress: LPWSTR;
    svti3_domain: LPWSTR;
    svti3_flags: ULONG;
    svti3_passwordlength: DWORD;
    svti3_password: packed array[0..255] of Byte;
  end;
  {$EXTERNALSYM _SERVER_TRANSPORT_INFO_3}
  TServerTransportInfo3 = _SERVER_TRANSPORT_INFO_3;
  SERVER_TRANSPORT_INFO_3 = _SERVER_TRANSPORT_INFO_3;
  {$EXTERNALSYM SERVER_TRANSPORT_INFO_3}

// Defines - SERVER

// The platform ID indicates the levels to use for platform-specific
// information.

const
  SV_PLATFORM_ID_OS2 = 400;
  {$EXTERNALSYM SV_PLATFORM_ID_OS2}
  SV_PLATFORM_ID_NT  = 500;
  {$EXTERNALSYM SV_PLATFORM_ID_NT}

// Mask to be applied to svX_version_major in order to obtain
// the major version number.

  MAJOR_VERSION_MASK  = $0F;
  {$EXTERNALSYM MAJOR_VERSION_MASK}

// Bit-mapped values for svX_type fields. X = 1, 2 or 3.

  SV_TYPE_WORKSTATION         = $00000001;
  {$EXTERNALSYM SV_TYPE_WORKSTATION}
  SV_TYPE_SERVER              = $00000002;
  {$EXTERNALSYM SV_TYPE_SERVER}
  SV_TYPE_SQLSERVER           = $00000004;
  {$EXTERNALSYM SV_TYPE_SQLSERVER}
  SV_TYPE_DOMAIN_CTRL         = $00000008;
  {$EXTERNALSYM SV_TYPE_DOMAIN_CTRL}
  SV_TYPE_DOMAIN_BAKCTRL      = $00000010;
  {$EXTERNALSYM SV_TYPE_DOMAIN_BAKCTRL}
  SV_TYPE_TIME_SOURCE         = $00000020;
  {$EXTERNALSYM SV_TYPE_TIME_SOURCE}
  SV_TYPE_AFP                 = $00000040;
  {$EXTERNALSYM SV_TYPE_AFP}
  SV_TYPE_NOVELL              = $00000080;
  {$EXTERNALSYM SV_TYPE_NOVELL}
  SV_TYPE_DOMAIN_MEMBER       = $00000100;
  {$EXTERNALSYM SV_TYPE_DOMAIN_MEMBER}
  SV_TYPE_PRINTQ_SERVER       = $00000200;
  {$EXTERNALSYM SV_TYPE_PRINTQ_SERVER}
  SV_TYPE_DIALIN_SERVER       = $00000400;
  {$EXTERNALSYM SV_TYPE_DIALIN_SERVER}
  SV_TYPE_XENIX_SERVER        = $00000800;
  {$EXTERNALSYM SV_TYPE_XENIX_SERVER}
  SV_TYPE_SERVER_UNIX         = SV_TYPE_XENIX_SERVER;
  {$EXTERNALSYM SV_TYPE_SERVER_UNIX}
  SV_TYPE_NT                  = $00001000;
  {$EXTERNALSYM SV_TYPE_NT}
  SV_TYPE_WFW                 = $00002000;
  {$EXTERNALSYM SV_TYPE_WFW}
  SV_TYPE_SERVER_MFPN         = $00004000;
  {$EXTERNALSYM SV_TYPE_SERVER_MFPN}
  SV_TYPE_SERVER_NT           = $00008000;
  {$EXTERNALSYM SV_TYPE_SERVER_NT}
  SV_TYPE_POTENTIAL_BROWSER   = $00010000;
  {$EXTERNALSYM SV_TYPE_POTENTIAL_BROWSER}
  SV_TYPE_BACKUP_BROWSER      = $00020000;
  {$EXTERNALSYM SV_TYPE_BACKUP_BROWSER}
  SV_TYPE_MASTER_BROWSER      = $00040000;
  {$EXTERNALSYM SV_TYPE_MASTER_BROWSER}
  SV_TYPE_DOMAIN_MASTER       = $00080000;
  {$EXTERNALSYM SV_TYPE_DOMAIN_MASTER}
  SV_TYPE_SERVER_OSF          = $00100000;
  {$EXTERNALSYM SV_TYPE_SERVER_OSF}
  SV_TYPE_SERVER_VMS          = $00200000;
  {$EXTERNALSYM SV_TYPE_SERVER_VMS}
  SV_TYPE_WINDOWS             = $00400000;  //* Windows95 and above */
  {$EXTERNALSYM SV_TYPE_WINDOWS}
  SV_TYPE_DFS                 = $00800000;  //* Root of a DFS tree */
  {$EXTERNALSYM SV_TYPE_DFS}
  SV_TYPE_CLUSTER_NT          = $01000000;  //* NT Cluster */
  {$EXTERNALSYM SV_TYPE_CLUSTER_NT}
  SV_TYPE_TERMINALSERVER      = $02000000;  //* Terminal Server(Hydra) */
  {$EXTERNALSYM SV_TYPE_TERMINALSERVER}
  SV_TYPE_DCE                 = $10000000;  //* IBM DSS (Directory and Security Services) or equivalent */
  {$EXTERNALSYM SV_TYPE_DCE}
  SV_TYPE_ALTERNATE_XPORT     = $20000000;  //* return list for alternate transport */
  {$EXTERNALSYM SV_TYPE_ALTERNATE_XPORT}
  SV_TYPE_LOCAL_LIST_ONLY     = $40000000;  //* Return local list only */
  {$EXTERNALSYM SV_TYPE_LOCAL_LIST_ONLY}
  SV_TYPE_DOMAIN_ENUM         = $80000000;
  {$EXTERNALSYM SV_TYPE_DOMAIN_ENUM}
  SV_TYPE_ALL                 = $FFFFFFFF;  //* handy for NetServerEnum2 */
  {$EXTERNALSYM SV_TYPE_ALL}

// Special value for sv102_disc that specifies infinite disconnect
// time.

  SV_NODISC           = -1;  //* No autodisconnect timeout enforced */
  {$EXTERNALSYM SV_NODISC}

// Values of svX_security field. X = 2 or 3.

  SV_USERSECURITY     = 1;
  {$EXTERNALSYM SV_USERSECURITY}
  SV_SHARESECURITY    = 0;
  {$EXTERNALSYM SV_SHARESECURITY}

// Values of svX_hidden field. X = 2 or 3.

  SV_HIDDEN       = 1;
  {$EXTERNALSYM SV_HIDDEN}
  SV_VISIBLE      = 0;
  {$EXTERNALSYM SV_VISIBLE}

// Values for ParmError parameter to NetServerSetInfo.

  SV_PLATFORM_ID_PARMNUM          = 101;
  {$EXTERNALSYM SV_PLATFORM_ID_PARMNUM}
  SV_NAME_PARMNUM                 = 102;
  {$EXTERNALSYM SV_NAME_PARMNUM}
  SV_VERSION_MAJOR_PARMNUM        = 103;
  {$EXTERNALSYM SV_VERSION_MAJOR_PARMNUM}
  SV_VERSION_MINOR_PARMNUM        = 104;
  {$EXTERNALSYM SV_VERSION_MINOR_PARMNUM}
  SV_TYPE_PARMNUM                 = 105;
  {$EXTERNALSYM SV_TYPE_PARMNUM}
  SV_COMMENT_PARMNUM              = 5;
  {$EXTERNALSYM SV_COMMENT_PARMNUM}
  SV_USERS_PARMNUM                = 107;
  {$EXTERNALSYM SV_USERS_PARMNUM}
  SV_DISC_PARMNUM                 = 10;
  {$EXTERNALSYM SV_DISC_PARMNUM}
  SV_HIDDEN_PARMNUM               = 16;
  {$EXTERNALSYM SV_HIDDEN_PARMNUM}
  SV_ANNOUNCE_PARMNUM             = 17;
  {$EXTERNALSYM SV_ANNOUNCE_PARMNUM}
  SV_ANNDELTA_PARMNUM             = 18;
  {$EXTERNALSYM SV_ANNDELTA_PARMNUM}
  SV_USERPATH_PARMNUM             = 112;
  {$EXTERNALSYM SV_USERPATH_PARMNUM}

  SV_ULIST_MTIME_PARMNUM          = 401;
  {$EXTERNALSYM SV_ULIST_MTIME_PARMNUM}
  SV_GLIST_MTIME_PARMNUM          = 402;
  {$EXTERNALSYM SV_GLIST_MTIME_PARMNUM}
  SV_ALIST_MTIME_PARMNUM          = 403;
  {$EXTERNALSYM SV_ALIST_MTIME_PARMNUM}
  SV_ALERTS_PARMNUM               = 11;
  {$EXTERNALSYM SV_ALERTS_PARMNUM}
  SV_SECURITY_PARMNUM             = 405;
  {$EXTERNALSYM SV_SECURITY_PARMNUM}
  SV_NUMADMIN_PARMNUM             = 406;
  {$EXTERNALSYM SV_NUMADMIN_PARMNUM}
  SV_LANMASK_PARMNUM              = 407;
  {$EXTERNALSYM SV_LANMASK_PARMNUM}
  SV_GUESTACC_PARMNUM             = 408;
  {$EXTERNALSYM SV_GUESTACC_PARMNUM}
  SV_CHDEVQ_PARMNUM               = 410;
  {$EXTERNALSYM SV_CHDEVQ_PARMNUM}
  SV_CHDEVJOBS_PARMNUM            = 411;
  {$EXTERNALSYM SV_CHDEVJOBS_PARMNUM}
  SV_CONNECTIONS_PARMNUM          = 412;
  {$EXTERNALSYM SV_CONNECTIONS_PARMNUM}
  SV_SHARES_PARMNUM               = 413;
  {$EXTERNALSYM SV_SHARES_PARMNUM}
  SV_OPENFILES_PARMNUM            = 414;
  {$EXTERNALSYM SV_OPENFILES_PARMNUM}
  SV_SESSREQS_PARMNUM             = 417;
  {$EXTERNALSYM SV_SESSREQS_PARMNUM}
  SV_ACTIVELOCKS_PARMNUM          = 419;
  {$EXTERNALSYM SV_ACTIVELOCKS_PARMNUM}
  SV_NUMREQBUF_PARMNUM            = 420;
  {$EXTERNALSYM SV_NUMREQBUF_PARMNUM}
  SV_NUMBIGBUF_PARMNUM            = 422;
  {$EXTERNALSYM SV_NUMBIGBUF_PARMNUM}
  SV_NUMFILETASKS_PARMNUM         = 423;
  {$EXTERNALSYM SV_NUMFILETASKS_PARMNUM}
  SV_ALERTSCHED_PARMNUM           = 37;
  {$EXTERNALSYM SV_ALERTSCHED_PARMNUM}
  SV_ERRORALERT_PARMNUM           = 38;
  {$EXTERNALSYM SV_ERRORALERT_PARMNUM}
  SV_LOGONALERT_PARMNUM           = 39;
  {$EXTERNALSYM SV_LOGONALERT_PARMNUM}
  SV_ACCESSALERT_PARMNUM          = 40;
  {$EXTERNALSYM SV_ACCESSALERT_PARMNUM}
  SV_DISKALERT_PARMNUM            = 41;
  {$EXTERNALSYM SV_DISKALERT_PARMNUM}
  SV_NETIOALERT_PARMNUM           = 42;
  {$EXTERNALSYM SV_NETIOALERT_PARMNUM}
  SV_MAXAUDITSZ_PARMNUM           = 43;
  {$EXTERNALSYM SV_MAXAUDITSZ_PARMNUM}
  SV_SRVHEURISTICS_PARMNUM        = 431;
  {$EXTERNALSYM SV_SRVHEURISTICS_PARMNUM}

  SV_SESSOPENS_PARMNUM                = 501;
  {$EXTERNALSYM SV_SESSOPENS_PARMNUM}
  SV_SESSVCS_PARMNUM                  = 502;
  {$EXTERNALSYM SV_SESSVCS_PARMNUM}
  SV_OPENSEARCH_PARMNUM               = 503;
  {$EXTERNALSYM SV_OPENSEARCH_PARMNUM}
  SV_SIZREQBUF_PARMNUM                = 504;
  {$EXTERNALSYM SV_SIZREQBUF_PARMNUM}
  SV_INITWORKITEMS_PARMNUM            = 505;
  {$EXTERNALSYM SV_INITWORKITEMS_PARMNUM}
  SV_MAXWORKITEMS_PARMNUM             = 506;
  {$EXTERNALSYM SV_MAXWORKITEMS_PARMNUM}
  SV_RAWWORKITEMS_PARMNUM             = 507;
  {$EXTERNALSYM SV_RAWWORKITEMS_PARMNUM}
  SV_IRPSTACKSIZE_PARMNUM             = 508;
  {$EXTERNALSYM SV_IRPSTACKSIZE_PARMNUM}
  SV_MAXRAWBUFLEN_PARMNUM             = 509;
  {$EXTERNALSYM SV_MAXRAWBUFLEN_PARMNUM}
  SV_SESSUSERS_PARMNUM                = 510;
  {$EXTERNALSYM SV_SESSUSERS_PARMNUM}
  SV_SESSCONNS_PARMNUM                = 511;
  {$EXTERNALSYM SV_SESSCONNS_PARMNUM}
  SV_MAXNONPAGEDMEMORYUSAGE_PARMNUM   = 512;
  {$EXTERNALSYM SV_MAXNONPAGEDMEMORYUSAGE_PARMNUM}
  SV_MAXPAGEDMEMORYUSAGE_PARMNUM      = 513;
  {$EXTERNALSYM SV_MAXPAGEDMEMORYUSAGE_PARMNUM}
  SV_ENABLESOFTCOMPAT_PARMNUM         = 514;
  {$EXTERNALSYM SV_ENABLESOFTCOMPAT_PARMNUM}
  SV_ENABLEFORCEDLOGOFF_PARMNUM       = 515;
  {$EXTERNALSYM SV_ENABLEFORCEDLOGOFF_PARMNUM}
  SV_TIMESOURCE_PARMNUM               = 516;
  {$EXTERNALSYM SV_TIMESOURCE_PARMNUM}
  SV_ACCEPTDOWNLEVELAPIS_PARMNUM      = 517;
  {$EXTERNALSYM SV_ACCEPTDOWNLEVELAPIS_PARMNUM}
  SV_LMANNOUNCE_PARMNUM               = 518;
  {$EXTERNALSYM SV_LMANNOUNCE_PARMNUM}
  SV_DOMAIN_PARMNUM                   = 519;
  {$EXTERNALSYM SV_DOMAIN_PARMNUM}
  SV_MAXCOPYREADLEN_PARMNUM           = 520;
  {$EXTERNALSYM SV_MAXCOPYREADLEN_PARMNUM}
  SV_MAXCOPYWRITELEN_PARMNUM          = 521;
  {$EXTERNALSYM SV_MAXCOPYWRITELEN_PARMNUM}
  SV_MINKEEPSEARCH_PARMNUM            = 522;
  {$EXTERNALSYM SV_MINKEEPSEARCH_PARMNUM}
  SV_MAXKEEPSEARCH_PARMNUM            = 523;
  {$EXTERNALSYM SV_MAXKEEPSEARCH_PARMNUM}
  SV_MINKEEPCOMPLSEARCH_PARMNUM       = 524;
  {$EXTERNALSYM SV_MINKEEPCOMPLSEARCH_PARMNUM}
  SV_MAXKEEPCOMPLSEARCH_PARMNUM       = 525;
  {$EXTERNALSYM SV_MAXKEEPCOMPLSEARCH_PARMNUM}
  SV_THREADCOUNTADD_PARMNUM           = 526;
  {$EXTERNALSYM SV_THREADCOUNTADD_PARMNUM}
  SV_NUMBLOCKTHREADS_PARMNUM          = 527;
  {$EXTERNALSYM SV_NUMBLOCKTHREADS_PARMNUM}
  SV_SCAVTIMEOUT_PARMNUM              = 528;
  {$EXTERNALSYM SV_SCAVTIMEOUT_PARMNUM}
  SV_MINRCVQUEUE_PARMNUM              = 529;
  {$EXTERNALSYM SV_MINRCVQUEUE_PARMNUM}
  SV_MINFREEWORKITEMS_PARMNUM         = 530;
  {$EXTERNALSYM SV_MINFREEWORKITEMS_PARMNUM}
  SV_XACTMEMSIZE_PARMNUM              = 531;
  {$EXTERNALSYM SV_XACTMEMSIZE_PARMNUM}
  SV_THREADPRIORITY_PARMNUM           = 532;
  {$EXTERNALSYM SV_THREADPRIORITY_PARMNUM}
  SV_MAXMPXCT_PARMNUM                 = 533;
  {$EXTERNALSYM SV_MAXMPXCT_PARMNUM}
  SV_OPLOCKBREAKWAIT_PARMNUM          = 534;
  {$EXTERNALSYM SV_OPLOCKBREAKWAIT_PARMNUM}
  SV_OPLOCKBREAKRESPONSEWAIT_PARMNUM  = 535;
  {$EXTERNALSYM SV_OPLOCKBREAKRESPONSEWAIT_PARMNUM}
  SV_ENABLEOPLOCKS_PARMNUM            = 536;
  {$EXTERNALSYM SV_ENABLEOPLOCKS_PARMNUM}
  SV_ENABLEOPLOCKFORCECLOSE_PARMNUM   = 537;
  {$EXTERNALSYM SV_ENABLEOPLOCKFORCECLOSE_PARMNUM}
  SV_ENABLEFCBOPENS_PARMNUM           = 538;
  {$EXTERNALSYM SV_ENABLEFCBOPENS_PARMNUM}
  SV_ENABLERAW_PARMNUM                = 539;
  {$EXTERNALSYM SV_ENABLERAW_PARMNUM}
  SV_ENABLESHAREDNETDRIVES_PARMNUM    = 540;
  {$EXTERNALSYM SV_ENABLESHAREDNETDRIVES_PARMNUM}
  SV_MINFREECONNECTIONS_PARMNUM       = 541;
  {$EXTERNALSYM SV_MINFREECONNECTIONS_PARMNUM}
  SV_MAXFREECONNECTIONS_PARMNUM       = 542;
  {$EXTERNALSYM SV_MAXFREECONNECTIONS_PARMNUM}
  SV_INITSESSTABLE_PARMNUM            = 543;
  {$EXTERNALSYM SV_INITSESSTABLE_PARMNUM}
  SV_INITCONNTABLE_PARMNUM            = 544;
  {$EXTERNALSYM SV_INITCONNTABLE_PARMNUM}
  SV_INITFILETABLE_PARMNUM            = 545;
  {$EXTERNALSYM SV_INITFILETABLE_PARMNUM}
  SV_INITSEARCHTABLE_PARMNUM          = 546;
  {$EXTERNALSYM SV_INITSEARCHTABLE_PARMNUM}
  SV_ALERTSCHEDULE_PARMNUM            = 547;
  {$EXTERNALSYM SV_ALERTSCHEDULE_PARMNUM}
  SV_ERRORTHRESHOLD_PARMNUM           = 548;
  {$EXTERNALSYM SV_ERRORTHRESHOLD_PARMNUM}
  SV_NETWORKERRORTHRESHOLD_PARMNUM    = 549;
  {$EXTERNALSYM SV_NETWORKERRORTHRESHOLD_PARMNUM}
  SV_DISKSPACETHRESHOLD_PARMNUM       = 550;
  {$EXTERNALSYM SV_DISKSPACETHRESHOLD_PARMNUM}
  SV_MAXLINKDELAY_PARMNUM             = 552;
  {$EXTERNALSYM SV_MAXLINKDELAY_PARMNUM}
  SV_MINLINKTHROUGHPUT_PARMNUM        = 553;
  {$EXTERNALSYM SV_MINLINKTHROUGHPUT_PARMNUM}
  SV_LINKINFOVALIDTIME_PARMNUM        = 554;
  {$EXTERNALSYM SV_LINKINFOVALIDTIME_PARMNUM}
  SV_SCAVQOSINFOUPDATETIME_PARMNUM    = 555;
  {$EXTERNALSYM SV_SCAVQOSINFOUPDATETIME_PARMNUM}
  SV_MAXWORKITEMIDLETIME_PARMNUM      = 556;
  {$EXTERNALSYM SV_MAXWORKITEMIDLETIME_PARMNUM}
  SV_MAXRAWWORKITEMS_PARMNUM          = 557;
  {$EXTERNALSYM SV_MAXRAWWORKITEMS_PARMNUM}
  SV_PRODUCTTYPE_PARMNUM              = 560;
  {$EXTERNALSYM SV_PRODUCTTYPE_PARMNUM}
  SV_SERVERSIZE_PARMNUM               = 561;
  {$EXTERNALSYM SV_SERVERSIZE_PARMNUM}
  SV_CONNECTIONLESSAUTODISC_PARMNUM   = 562;
  {$EXTERNALSYM SV_CONNECTIONLESSAUTODISC_PARMNUM}
  SV_SHARINGVIOLATIONRETRIES_PARMNUM  = 563;
  {$EXTERNALSYM SV_SHARINGVIOLATIONRETRIES_PARMNUM}
  SV_SHARINGVIOLATIONDELAY_PARMNUM    = 564;
  {$EXTERNALSYM SV_SHARINGVIOLATIONDELAY_PARMNUM}
  SV_MAXGLOBALOPENSEARCH_PARMNUM      = 565;
  {$EXTERNALSYM SV_MAXGLOBALOPENSEARCH_PARMNUM}
  SV_REMOVEDUPLICATESEARCHES_PARMNUM  = 566;
  {$EXTERNALSYM SV_REMOVEDUPLICATESEARCHES_PARMNUM}
  SV_LOCKVIOLATIONRETRIES_PARMNUM     = 567;
  {$EXTERNALSYM SV_LOCKVIOLATIONRETRIES_PARMNUM}
  SV_LOCKVIOLATIONOFFSET_PARMNUM      = 568;
  {$EXTERNALSYM SV_LOCKVIOLATIONOFFSET_PARMNUM}
  SV_LOCKVIOLATIONDELAY_PARMNUM       = 569;
  {$EXTERNALSYM SV_LOCKVIOLATIONDELAY_PARMNUM}
  SV_MDLREADSWITCHOVER_PARMNUM        = 570;
  {$EXTERNALSYM SV_MDLREADSWITCHOVER_PARMNUM}
  SV_CACHEDOPENLIMIT_PARMNUM          = 571;
  {$EXTERNALSYM SV_CACHEDOPENLIMIT_PARMNUM}
  SV_CRITICALTHREADS_PARMNUM          = 572;
  {$EXTERNALSYM SV_CRITICALTHREADS_PARMNUM}
  SV_RESTRICTNULLSESSACCESS_PARMNUM   = 573;
  {$EXTERNALSYM SV_RESTRICTNULLSESSACCESS_PARMNUM}
  SV_ENABLEWFW311DIRECTIPX_PARMNUM    = 574;
  {$EXTERNALSYM SV_ENABLEWFW311DIRECTIPX_PARMNUM}
  SV_OTHERQUEUEAFFINITY_PARMNUM       = 575;
  {$EXTERNALSYM SV_OTHERQUEUEAFFINITY_PARMNUM}
  SV_QUEUESAMPLESECS_PARMNUM          = 576;
  {$EXTERNALSYM SV_QUEUESAMPLESECS_PARMNUM}
  SV_BALANCECOUNT_PARMNUM             = 577;
  {$EXTERNALSYM SV_BALANCECOUNT_PARMNUM}
  SV_PREFERREDAFFINITY_PARMNUM        = 578;
  {$EXTERNALSYM SV_PREFERREDAFFINITY_PARMNUM}
  SV_MAXFREERFCBS_PARMNUM             = 579;
  {$EXTERNALSYM SV_MAXFREERFCBS_PARMNUM}
  SV_MAXFREEMFCBS_PARMNUM             = 580;
  {$EXTERNALSYM SV_MAXFREEMFCBS_PARMNUM}
  SV_MAXFREELFCBS_PARMNUM             = 581;
  {$EXTERNALSYM SV_MAXFREELFCBS_PARMNUM}
  SV_MAXFREEPAGEDPOOLCHUNKS_PARMNUM   = 582;
  {$EXTERNALSYM SV_MAXFREEPAGEDPOOLCHUNKS_PARMNUM}
  SV_MINPAGEDPOOLCHUNKSIZE_PARMNUM    = 583;
  {$EXTERNALSYM SV_MINPAGEDPOOLCHUNKSIZE_PARMNUM}
  SV_MAXPAGEDPOOLCHUNKSIZE_PARMNUM    = 584;
  {$EXTERNALSYM SV_MAXPAGEDPOOLCHUNKSIZE_PARMNUM}
  SV_SENDSFROMPREFERREDPROCESSOR_PARMNUM    = 585;
  {$EXTERNALSYM SV_SENDSFROMPREFERREDPROCESSOR_PARMNUM}
  SV_MAXTHREADSPERQUEUE_PARMNUM       = 586;
  {$EXTERNALSYM SV_MAXTHREADSPERQUEUE_PARMNUM}
  SV_CACHEDDIRECTORYLIMIT_PARMNUM     = 587;
  {$EXTERNALSYM SV_CACHEDDIRECTORYLIMIT_PARMNUM}
  SV_MAXCOPYLENGTH_PARMNUM            = 588;
  {$EXTERNALSYM SV_MAXCOPYLENGTH_PARMNUM}
  SV_ENABLECOMPRESSION_PARMNUM        = 590;
  {$EXTERNALSYM SV_ENABLECOMPRESSION_PARMNUM}
  SV_AUTOSHAREWKS_PARMNUM             = 591;
  {$EXTERNALSYM SV_AUTOSHAREWKS_PARMNUM}
  SV_AUTOSHARESERVER_PARMNUM          = 592;
  {$EXTERNALSYM SV_AUTOSHARESERVER_PARMNUM}
  SV_ENABLESECURITYSIGNATURE_PARMNUM  = 593;
  {$EXTERNALSYM SV_ENABLESECURITYSIGNATURE_PARMNUM}
  SV_REQUIRESECURITYSIGNATURE_PARMNUM = 594;
  {$EXTERNALSYM SV_REQUIRESECURITYSIGNATURE_PARMNUM}
  SV_MINCLIENTBUFFERSIZE_PARMNUM      = 595;
  {$EXTERNALSYM SV_MINCLIENTBUFFERSIZE_PARMNUM}
  SV_CONNECTIONNOSESSIONSTIMEOUT_PARMNUM = 596;
  {$EXTERNALSYM SV_CONNECTIONNOSESSIONSTIMEOUT_PARMNUM}
  SV_IDLETHREADTIMEOUT_PARMNUM        = 597;
  {$EXTERNALSYM SV_IDLETHREADTIMEOUT_PARMNUM}
  SV_ENABLEW9XSECURITYSIGNATURE_PARMNUM        = 598;
  {$EXTERNALSYM SV_ENABLEW9XSECURITYSIGNATURE_PARMNUM}

// Single-field infolevels for NetServerSetInfo.

  SV_COMMENT_INFOLEVEL = (PARMNUM_BASE_INFOLEVEL + SV_COMMENT_PARMNUM);
  {$EXTERNALSYM SV_COMMENT_INFOLEVEL}
  SV_USERS_INFOLEVEL = (PARMNUM_BASE_INFOLEVEL + SV_USERS_PARMNUM);
  {$EXTERNALSYM SV_USERS_INFOLEVEL}
  SV_DISC_INFOLEVEL = (PARMNUM_BASE_INFOLEVEL + SV_DISC_PARMNUM);
  {$EXTERNALSYM SV_DISC_INFOLEVEL}
  SV_HIDDEN_INFOLEVEL = (PARMNUM_BASE_INFOLEVEL + SV_HIDDEN_PARMNUM);
  {$EXTERNALSYM SV_HIDDEN_INFOLEVEL}
  SV_ANNOUNCE_INFOLEVEL = (PARMNUM_BASE_INFOLEVEL + SV_ANNOUNCE_PARMNUM);
  {$EXTERNALSYM SV_ANNOUNCE_INFOLEVEL}
  SV_ANNDELTA_INFOLEVEL = (PARMNUM_BASE_INFOLEVEL + SV_ANNDELTA_PARMNUM);
  {$EXTERNALSYM SV_ANNDELTA_INFOLEVEL}
  SV_SESSOPENS_INFOLEVEL = (PARMNUM_BASE_INFOLEVEL + SV_SESSOPENS_PARMNUM);
  {$EXTERNALSYM SV_SESSOPENS_INFOLEVEL}
  SV_SESSVCS_INFOLEVEL = (PARMNUM_BASE_INFOLEVEL + SV_SESSVCS_PARMNUM);
  {$EXTERNALSYM SV_SESSVCS_INFOLEVEL}
  SV_OPENSEARCH_INFOLEVEL = (PARMNUM_BASE_INFOLEVEL + SV_OPENSEARCH_PARMNUM);
  {$EXTERNALSYM SV_OPENSEARCH_INFOLEVEL}
  SV_MAXWORKITEMS_INFOLEVEL = (PARMNUM_BASE_INFOLEVEL + SV_MAXWORKITEMS_PARMNUM);
  {$EXTERNALSYM SV_MAXWORKITEMS_INFOLEVEL}
  SV_MAXRAWBUFLEN_INFOLEVEL = (PARMNUM_BASE_INFOLEVEL + SV_MAXRAWBUFLEN_PARMNUM);
  {$EXTERNALSYM SV_MAXRAWBUFLEN_INFOLEVEL}
  SV_SESSUSERS_INFOLEVEL = (PARMNUM_BASE_INFOLEVEL + SV_SESSUSERS_PARMNUM);
  {$EXTERNALSYM SV_SESSUSERS_INFOLEVEL}
  SV_SESSCONNS_INFOLEVEL = (PARMNUM_BASE_INFOLEVEL + SV_SESSCONNS_PARMNUM);
  {$EXTERNALSYM SV_SESSCONNS_INFOLEVEL}
  SV_MAXNONPAGEDMEMORYUSAGE_INFOLEVEL = (PARMNUM_BASE_INFOLEVEL + SV_MAXNONPAGEDMEMORYUSAGE_PARMNUM);
  {$EXTERNALSYM SV_MAXNONPAGEDMEMORYUSAGE_INFOLEVEL}
  SV_MAXPAGEDMEMORYUSAGE_INFOLEVEL = (PARMNUM_BASE_INFOLEVEL + SV_MAXPAGEDMEMORYUSAGE_PARMNUM);
  {$EXTERNALSYM SV_MAXPAGEDMEMORYUSAGE_INFOLEVEL}
  SV_ENABLESOFTCOMPAT_INFOLEVEL = (PARMNUM_BASE_INFOLEVEL + SV_ENABLESOFTCOMPAT_PARMNUM);
  {$EXTERNALSYM SV_ENABLESOFTCOMPAT_INFOLEVEL}
  SV_ENABLEFORCEDLOGOFF_INFOLEVEL = (PARMNUM_BASE_INFOLEVEL + SV_ENABLEFORCEDLOGOFF_PARMNUM);
  {$EXTERNALSYM SV_ENABLEFORCEDLOGOFF_INFOLEVEL}
  SV_TIMESOURCE_INFOLEVEL = (PARMNUM_BASE_INFOLEVEL + SV_TIMESOURCE_PARMNUM);
  {$EXTERNALSYM SV_TIMESOURCE_INFOLEVEL}
  SV_LMANNOUNCE_INFOLEVEL = (PARMNUM_BASE_INFOLEVEL + SV_LMANNOUNCE_PARMNUM);
  {$EXTERNALSYM SV_LMANNOUNCE_INFOLEVEL}
  SV_MAXCOPYREADLEN_INFOLEVEL = (PARMNUM_BASE_INFOLEVEL + SV_MAXCOPYREADLEN_PARMNUM);
  {$EXTERNALSYM SV_MAXCOPYREADLEN_INFOLEVEL}
  SV_MAXCOPYWRITELEN_INFOLEVEL = (PARMNUM_BASE_INFOLEVEL + SV_MAXCOPYWRITELEN_PARMNUM);
  {$EXTERNALSYM SV_MAXCOPYWRITELEN_INFOLEVEL}
  SV_MINKEEPSEARCH_INFOLEVEL = (PARMNUM_BASE_INFOLEVEL + SV_MINKEEPSEARCH_PARMNUM);
  {$EXTERNALSYM SV_MINKEEPSEARCH_INFOLEVEL}
  SV_MAXKEEPSEARCH_INFOLEVEL = (PARMNUM_BASE_INFOLEVEL + SV_MAXKEEPSEARCH_PARMNUM);
  {$EXTERNALSYM SV_MAXKEEPSEARCH_INFOLEVEL}
  SV_MINKEEPCOMPLSEARCH_INFOLEVEL = (PARMNUM_BASE_INFOLEVEL + SV_MINKEEPCOMPLSEARCH_PARMNUM);
  {$EXTERNALSYM SV_MINKEEPCOMPLSEARCH_INFOLEVEL}
  SV_MAXKEEPCOMPLSEARCH_INFOLEVEL = (PARMNUM_BASE_INFOLEVEL + SV_MAXKEEPCOMPLSEARCH_PARMNUM);
  {$EXTERNALSYM SV_MAXKEEPCOMPLSEARCH_INFOLEVEL}
  SV_SCAVTIMEOUT_INFOLEVEL = (PARMNUM_BASE_INFOLEVEL + SV_SCAVTIMEOUT_PARMNUM);
  {$EXTERNALSYM SV_SCAVTIMEOUT_INFOLEVEL}
  SV_MINRCVQUEUE_INFOLEVEL = (PARMNUM_BASE_INFOLEVEL + SV_MINRCVQUEUE_PARMNUM);
  {$EXTERNALSYM SV_MINRCVQUEUE_INFOLEVEL}
  SV_MINFREEWORKITEMS_INFOLEVEL = (PARMNUM_BASE_INFOLEVEL + SV_MINFREEWORKITEMS_PARMNUM);
  {$EXTERNALSYM SV_MINFREEWORKITEMS_INFOLEVEL}
  SV_MAXMPXCT_INFOLEVEL = (PARMNUM_BASE_INFOLEVEL + SV_MAXMPXCT_PARMNUM);
  {$EXTERNALSYM SV_MAXMPXCT_INFOLEVEL}
  SV_OPLOCKBREAKWAIT_INFOLEVEL = (PARMNUM_BASE_INFOLEVEL + SV_OPLOCKBREAKWAIT_PARMNUM);
  {$EXTERNALSYM SV_OPLOCKBREAKWAIT_INFOLEVEL}
  SV_OPLOCKBREAKRESPONSEWAIT_INFOLEVEL = (PARMNUM_BASE_INFOLEVEL + SV_OPLOCKBREAKRESPONSEWAIT_PARMNUM);
  {$EXTERNALSYM SV_OPLOCKBREAKRESPONSEWAIT_INFOLEVEL}
  SV_ENABLEOPLOCKS_INFOLEVEL = (PARMNUM_BASE_INFOLEVEL + SV_ENABLEOPLOCKS_PARMNUM);
  {$EXTERNALSYM SV_ENABLEOPLOCKS_INFOLEVEL}
  SV_ENABLEOPLOCKFORCECLOSE_INFOLEVEL = (PARMNUM_BASE_INFOLEVEL + SV_ENABLEOPLOCKFORCECLOSE_PARMNUM);
  {$EXTERNALSYM SV_ENABLEOPLOCKFORCECLOSE_INFOLEVEL}
  SV_ENABLEFCBOPENS_INFOLEVEL = (PARMNUM_BASE_INFOLEVEL + SV_ENABLEFCBOPENS_PARMNUM);
  {$EXTERNALSYM SV_ENABLEFCBOPENS_INFOLEVEL}
  SV_ENABLERAW_INFOLEVEL = (PARMNUM_BASE_INFOLEVEL + SV_ENABLERAW_PARMNUM);
  {$EXTERNALSYM SV_ENABLERAW_INFOLEVEL}
  SV_ENABLESHAREDNETDRIVES_INFOLEVEL = (PARMNUM_BASE_INFOLEVEL + SV_ENABLESHAREDNETDRIVES_PARMNUM);
  {$EXTERNALSYM SV_ENABLESHAREDNETDRIVES_INFOLEVEL}
  SV_MINFREECONNECTIONS_INFOLEVEL = (PARMNUM_BASE_INFOLEVEL + SV_MINFREECONNECTIONS_PARMNUM);
  {$EXTERNALSYM SV_MINFREECONNECTIONS_INFOLEVEL}
  SV_MAXFREECONNECTIONS_INFOLEVEL = (PARMNUM_BASE_INFOLEVEL + SV_MAXFREECONNECTIONS_PARMNUM);
  {$EXTERNALSYM SV_MAXFREECONNECTIONS_INFOLEVEL}
  SV_INITSESSTABLE_INFOLEVEL = (PARMNUM_BASE_INFOLEVEL + SV_INITSESSTABLE_PARMNUM);
  {$EXTERNALSYM SV_INITSESSTABLE_INFOLEVEL}
  SV_INITCONNTABLE_INFOLEVEL = (PARMNUM_BASE_INFOLEVEL + SV_INITCONNTABLE_PARMNUM);
  {$EXTERNALSYM SV_INITCONNTABLE_INFOLEVEL}
  SV_INITFILETABLE_INFOLEVEL = (PARMNUM_BASE_INFOLEVEL + SV_INITFILETABLE_PARMNUM);
  {$EXTERNALSYM SV_INITFILETABLE_INFOLEVEL}
  SV_INITSEARCHTABLE_INFOLEVEL = (PARMNUM_BASE_INFOLEVEL + SV_INITSEARCHTABLE_PARMNUM);
  {$EXTERNALSYM SV_INITSEARCHTABLE_INFOLEVEL}
  SV_ALERTSCHEDULE_INFOLEVEL = (PARMNUM_BASE_INFOLEVEL + SV_ALERTSCHEDULE_PARMNUM);
  {$EXTERNALSYM SV_ALERTSCHEDULE_INFOLEVEL}
  SV_ERRORTHRESHOLD_INFOLEVEL = (PARMNUM_BASE_INFOLEVEL + SV_ERRORTHRESHOLD_PARMNUM);
  {$EXTERNALSYM SV_ERRORTHRESHOLD_INFOLEVEL}
  SV_NETWORKERRORTHRESHOLD_INFOLEVEL = (PARMNUM_BASE_INFOLEVEL + SV_NETWORKERRORTHRESHOLD_PARMNUM);
  {$EXTERNALSYM SV_NETWORKERRORTHRESHOLD_INFOLEVEL}
  SV_DISKSPACETHRESHOLD_INFOLEVEL = (PARMNUM_BASE_INFOLEVEL + SV_DISKSPACETHRESHOLD_PARMNUM);
  {$EXTERNALSYM SV_DISKSPACETHRESHOLD_INFOLEVEL}
  SV_MAXLINKDELAY_INFOLEVEL = (PARMNUM_BASE_INFOLEVEL + SV_MAXLINKDELAY_PARMNUM);
  {$EXTERNALSYM SV_MAXLINKDELAY_INFOLEVEL}
  SV_MINLINKTHROUGHPUT_INFOLEVEL = (PARMNUM_BASE_INFOLEVEL + SV_MINLINKTHROUGHPUT_PARMNUM);
  {$EXTERNALSYM SV_MINLINKTHROUGHPUT_INFOLEVEL}
  SV_LINKINFOVALIDTIME_INFOLEVEL = (PARMNUM_BASE_INFOLEVEL + SV_LINKINFOVALIDTIME_PARMNUM);
  {$EXTERNALSYM SV_LINKINFOVALIDTIME_INFOLEVEL}
  SV_SCAVQOSINFOUPDATETIME_INFOLEVEL = (PARMNUM_BASE_INFOLEVEL + SV_SCAVQOSINFOUPDATETIME_PARMNUM);
  {$EXTERNALSYM SV_SCAVQOSINFOUPDATETIME_INFOLEVEL}
  SV_MAXWORKITEMIDLETIME_INFOLEVEL = (PARMNUM_BASE_INFOLEVEL + SV_MAXWORKITEMIDLETIME_PARMNUM);
  {$EXTERNALSYM SV_MAXWORKITEMIDLETIME_INFOLEVEL}
  SV_MAXRAWWORKITEMS_INFOLOEVEL = (PARMNUM_BASE_INFOLEVEL + SV_MAXRAWWORKITEMS_PARMNUM);
  {$EXTERNALSYM SV_MAXRAWWORKITEMS_INFOLOEVEL}
  SV_PRODUCTTYPE_INFOLOEVEL = (PARMNUM_BASE_INFOLEVEL + SV_PRODUCTTYPE_PARMNUM);
  {$EXTERNALSYM SV_PRODUCTTYPE_INFOLOEVEL}
  SV_SERVERSIZE_INFOLOEVEL = (PARMNUM_BASE_INFOLEVEL + SV_SERVERSIZE_PARMNUM);
  {$EXTERNALSYM SV_SERVERSIZE_INFOLOEVEL}
  SV_CONNECTIONLESSAUTODISC_INFOLOEVEL = (PARMNUM_BASE_INFOLEVEL + SV_CONNECTIONLESSAUTODISC_PARMNUM);
  {$EXTERNALSYM SV_CONNECTIONLESSAUTODISC_INFOLOEVEL}
  SV_SHARINGVIOLATIONRETRIES_INFOLOEVEL = (PARMNUM_BASE_INFOLEVEL + SV_SHARINGVIOLATIONRETRIES_PARMNUM);
  {$EXTERNALSYM SV_SHARINGVIOLATIONRETRIES_INFOLOEVEL}
  SV_SHARINGVIOLATIONDELAY_INFOLOEVEL = (PARMNUM_BASE_INFOLEVEL + SV_SHARINGVIOLATIONDELAY_PARMNUM);
  {$EXTERNALSYM SV_SHARINGVIOLATIONDELAY_INFOLOEVEL}
  SV_MAXGLOBALOPENSEARCH_INFOLOEVEL = (PARMNUM_BASE_INFOLEVEL + SV_MAXGLOBALOPENSEARCH_PARMNUM);
  {$EXTERNALSYM SV_MAXGLOBALOPENSEARCH_INFOLOEVEL}
  SV_REMOVEDUPLICATESEARCHES_INFOLOEVEL = (PARMNUM_BASE_INFOLEVEL + SV_REMOVEDUPLICATESEARCHES_PARMNUM);
  {$EXTERNALSYM SV_REMOVEDUPLICATESEARCHES_INFOLOEVEL}
  SV_LOCKVIOLATIONRETRIES_INFOLOEVEL = (PARMNUM_BASE_INFOLEVEL + SV_LOCKVIOLATIONRETRIES_PARMNUM);
  {$EXTERNALSYM SV_LOCKVIOLATIONRETRIES_INFOLOEVEL}
  SV_LOCKVIOLATIONOFFSET_INFOLOEVEL = (PARMNUM_BASE_INFOLEVEL + SV_LOCKVIOLATIONOFFSET_PARMNUM);
  {$EXTERNALSYM SV_LOCKVIOLATIONOFFSET_INFOLOEVEL}
  SV_LOCKVIOLATIONDELAY_INFOLOEVEL = (PARMNUM_BASE_INFOLEVEL + SV_LOCKVIOLATIONDELAY_PARMNUM);
  {$EXTERNALSYM SV_LOCKVIOLATIONDELAY_INFOLOEVEL}
  SV_MDLREADSWITCHOVER_INFOLOEVEL = (PARMNUM_BASE_INFOLEVEL + SV_MDLREADSWITCHOVER_PARMNUM);
  {$EXTERNALSYM SV_MDLREADSWITCHOVER_INFOLOEVEL}
  SV_CACHEDOPENLIMIT_INFOLOEVEL = (PARMNUM_BASE_INFOLEVEL + SV_CACHEDOPENLIMIT_PARMNUM);
  {$EXTERNALSYM SV_CACHEDOPENLIMIT_INFOLOEVEL}
  SV_CRITICALTHREADS_INFOLOEVEL = (PARMNUM_BASE_INFOLEVEL + SV_CRITICALTHREADS_PARMNUM);
  {$EXTERNALSYM SV_CRITICALTHREADS_INFOLOEVEL}
  SV_RESTRICTNULLSESSACCESS_INFOLOEVEL = (PARMNUM_BASE_INFOLEVEL + SV_RESTRICTNULLSESSACCESS_PARMNUM);
  {$EXTERNALSYM SV_RESTRICTNULLSESSACCESS_INFOLOEVEL}
  SV_ENABLEWFW311DIRECTIPX_INFOLOEVEL = (PARMNUM_BASE_INFOLEVEL + SV_ENABLEWFW311DIRECTIPX_PARMNUM);
  {$EXTERNALSYM SV_ENABLEWFW311DIRECTIPX_INFOLOEVEL}
  SV_OTHERQUEUEAFFINITY_INFOLEVEL = (PARMNUM_BASE_INFOLEVEL + SV_OTHERQUEUEAFFINITY_PARMNUM);
  {$EXTERNALSYM SV_OTHERQUEUEAFFINITY_INFOLEVEL}
  SV_QUEUESAMPLESECS_INFOLEVEL = (PARMNUM_BASE_INFOLEVEL + SV_QUEUESAMPLESECS_PARMNUM);
  {$EXTERNALSYM SV_QUEUESAMPLESECS_INFOLEVEL}
  SV_BALANCECOUNT_INFOLEVEL = (PARMNUM_BASE_INFOLEVEL + SV_BALANCECOUNT_PARMNUM);
  {$EXTERNALSYM SV_BALANCECOUNT_INFOLEVEL}
  SV_PREFERREDAFFINITY_INFOLEVEL = (PARMNUM_BASE_INFOLEVEL + SV_PREFERREDAFFINITY_PARMNUM);
  {$EXTERNALSYM SV_PREFERREDAFFINITY_INFOLEVEL}
  SV_MAXFREERFCBS_INFOLEVEL = (PARMNUM_BASE_INFOLEVEL + SV_MAXFREERFCBS_PARMNUM);
  {$EXTERNALSYM SV_MAXFREERFCBS_INFOLEVEL}
  SV_MAXFREEMFCBS_INFOLEVEL = (PARMNUM_BASE_INFOLEVEL + SV_MAXFREEMFCBS_PARMNUM);
  {$EXTERNALSYM SV_MAXFREEMFCBS_INFOLEVEL}
  SV_MAXFREELFCBS_INFOLEVEL = (PARMNUM_BASE_INFOLEVEL + SV_MAXFREELFCBS_PARMNUM);
  {$EXTERNALSYM SV_MAXFREELFCBS_INFOLEVEL}
  SV_MAXFREEPAGEDPOOLCHUNKS_INFOLEVEL = (PARMNUM_BASE_INFOLEVEL + SV_MAXFREEPAGEDPOOLCHUNKS_PARMNUM);
  {$EXTERNALSYM SV_MAXFREEPAGEDPOOLCHUNKS_INFOLEVEL}
  SV_MINPAGEDPOOLCHUNKSIZE_INFOLEVEL = (PARMNUM_BASE_INFOLEVEL + SV_MINPAGEDPOOLCHUNKSIZE_PARMNUM);
  {$EXTERNALSYM SV_MINPAGEDPOOLCHUNKSIZE_INFOLEVEL}
  SV_MAXPAGEDPOOLCHUNKSIZE_INFOLEVEL = (PARMNUM_BASE_INFOLEVEL + SV_MAXPAGEDPOOLCHUNKSIZE_PARMNUM);
  {$EXTERNALSYM SV_MAXPAGEDPOOLCHUNKSIZE_INFOLEVEL}
  SV_SENDSFROMPREFERREDPROCESSOR_INFOLEVEL = (PARMNUM_BASE_INFOLEVEL + SV_SENDSFROMPREFERREDPROCESSOR_PARMNUM);
  {$EXTERNALSYM SV_SENDSFROMPREFERREDPROCESSOR_INFOLEVEL}
  SV_MAXTHREADSPERQUEUE_INFOLEVEL = (PARMNUM_BASE_INFOLEVEL + SV_MAXTHREADSPERQUEUE_PARMNUM);
  {$EXTERNALSYM SV_MAXTHREADSPERQUEUE_INFOLEVEL}
  SV_CACHEDDIRECTORYLIMIT_INFOLEVEL = (PARMNUM_BASE_INFOLEVEL + SV_CACHEDDIRECTORYLIMIT_PARMNUM);
  {$EXTERNALSYM SV_CACHEDDIRECTORYLIMIT_INFOLEVEL}
  SV_MAXCOPYLENGTH_INFOLEVEL = (PARMNUM_BASE_INFOLEVEL + SV_MAXCOPYLENGTH_PARMNUM);
  {$EXTERNALSYM SV_MAXCOPYLENGTH_INFOLEVEL}
  SV_ENABLECOMPRESSION_INFOLEVEL = (PARMNUM_BASE_INFOLEVEL + SV_ENABLECOMPRESSION_PARMNUM);
  {$EXTERNALSYM SV_ENABLECOMPRESSION_INFOLEVEL}
  SV_AUTOSHAREWKS_INFOLEVEL = (PARMNUM_BASE_INFOLEVEL + SV_AUTOSHAREWKS_PARMNUM);
  {$EXTERNALSYM SV_AUTOSHAREWKS_INFOLEVEL}
  SV_AUTOSHARESERVER_INFOLEVEL = (PARMNUM_BASE_INFOLEVEL + SV_AUTOSHARESERVER_PARMNUM);
  {$EXTERNALSYM SV_AUTOSHARESERVER_INFOLEVEL}
  SV_ENABLESECURITYSIGNATURE_INFOLEVEL = (PARMNUM_BASE_INFOLEVEL + SV_ENABLESECURITYSIGNATURE_PARMNUM);
  {$EXTERNALSYM SV_ENABLESECURITYSIGNATURE_INFOLEVEL}
  SV_REQUIRESECURITYSIGNATURE_INFOLEVEL = (PARMNUM_BASE_INFOLEVEL + SV_REQUIRESECURITYSIGNATURE_PARMNUM);
  {$EXTERNALSYM SV_REQUIRESECURITYSIGNATURE_INFOLEVEL}
  SV_MINCLIENTBUFFERSIZE_INFOLEVEL = (PARMNUM_BASE_INFOLEVEL + SV_MINCLIENTBUFFERSIZE_PARMNUM);
  {$EXTERNALSYM SV_MINCLIENTBUFFERSIZE_INFOLEVEL}
  SV_CONNECTIONNOSESSIONSTIMEOUT_INFOLEVEL = (PARMNUM_BASE_INFOLEVEL + SV_CONNECTIONNOSESSIONSTIMEOUT_PARMNUM);
  {$EXTERNALSYM SV_CONNECTIONNOSESSIONSTIMEOUT_INFOLEVEL}
  SV_IDLETHREADTIMEOUT_INFOLEVEL = (PARMNUM_BASE_INFOLEVEL + SV_IDLETHREADTIMEOUT_PARMNUM);
  {$EXTERNALSYM SV_IDLETHREADTIMEOUT_INFOLEVEL}
  SV_ENABLEW9XSECURITYSIGNATURE_INFOLEVEL = (PARMNUM_BASE_INFOLEVEL + SV_ENABLEW9XSECURITYSIGNATURE_PARMNUM);
  {$EXTERNALSYM SV_ENABLEW9XSECURITYSIGNATURE_INFOLEVEL}

  SVI1_NUM_ELEMENTS       = 5;
  {$EXTERNALSYM SVI1_NUM_ELEMENTS}
  SVI2_NUM_ELEMENTS       = 40;
  {$EXTERNALSYM SVI2_NUM_ELEMENTS}
  SVI3_NUM_ELEMENTS       = 44;
  {$EXTERNALSYM SVI3_NUM_ELEMENTS}

// Maxmimum length for command string to NetServerAdminCommand.

  SV_MAX_CMD_LEN          = PATHLEN;
  {$EXTERNALSYM SV_MAX_CMD_LEN}

// Masks describing AUTOPROFILE parameters

  SW_AUTOPROF_LOAD_MASK   = $1;
  {$EXTERNALSYM SW_AUTOPROF_LOAD_MASK}
  SW_AUTOPROF_SAVE_MASK   = $2;
  {$EXTERNALSYM SW_AUTOPROF_SAVE_MASK}

// Max size of svX_srvheuristics.

  SV_MAX_SRV_HEUR_LEN     = 32;      // Max heuristics info string length.
  {$EXTERNALSYM SV_MAX_SRV_HEUR_LEN}

// Equate for use with sv102_licenses.

  SV_USERS_PER_LICENSE    = 5;
  {$EXTERNALSYM SV_USERS_PER_LICENSE}

// Equate for use with svti2_flags in NetServerTransportAddEx.

  SVTI2_REMAP_PIPE_NAMES  = $2;
  {$EXTERNALSYM SVTI2_REMAP_PIPE_NAMES}

// Translated from LMSVC.H

type
  PServiceInfo0 = ^TServiceInfo0;
  _SERVICE_INFO_0 = record
    svci0_name: LPWSTR;
  end;
  {$EXTERNALSYM _SERVICE_INFO_0}
  TServiceInfo0 = _SERVICE_INFO_0;
  SERVICE_INFO_0 = _SERVICE_INFO_0;
  {$EXTERNALSYM SERVICE_INFO_0}

  PServiceInfo1 = ^TServiceInfo1;
  _SERVICE_INFO_1 = record
    svci1_name: LPWSTR;
    svci1_status: DWORD;
    svci1_code: DWORD;
    svci1_pid: DWORD;
  end;
  {$EXTERNALSYM _SERVICE_INFO_1}
  TServiceInfo1 = _SERVICE_INFO_1;
  SERVICE_INFO_1 = _SERVICE_INFO_1;
  {$EXTERNALSYM SERVICE_INFO_1}

  PServiceInfo2 = ^TServiceInfo2;
  _SERVICE_INFO_2 = record
    svci2_name: LPWSTR;
    svci2_status: DWORD;
    svci2_code: DWORD;
    svci2_pid: DWORD;
    svci2_text: LPWSTR;
    svci2_specific_error: DWORD;
    svci2_display_name: LPWSTR;
  end;
  {$EXTERNALSYM _SERVICE_INFO_2}
  TServiceInfo2 = _SERVICE_INFO_2;
  SERVICE_INFO_2 = _SERVICE_INFO_2;
  {$EXTERNALSYM SERVICE_INFO_2}


function NetServiceControl(servername: LPCWSTR; service: LPCWSTR; opcode: DWORD;
  arg: DWORD; bufptr: Pointer): NET_API_STATUS; stdcall;
{$EXTERNALSYM NetServiceControl}

function NetServiceEnum(servername: LPCWSTR; level: DWORD; bufptr: Pointer;
  prefmaxlen: DWORD; var entriesread: DWORD; var totalentries: DWORD;
  resume_handle: PDWORD): NET_API_STATUS; stdcall;
{$EXTERNALSYM NetServiceEnum}

function NetServiceGetInfo(servername: LPCWSTR; service: LPCWSTR; level: DWORD;
  bufptr: Pointer): NET_API_STATUS; stdcall;
{$EXTERNALSYM NetServiceGetInfo}

function NetServiceInstall(servername: LPCWSTR; service: LPCWSTR; argc: DWORD;
  argv: LPCWSTR; bufptr: Pointer): NET_API_STATUS; stdcall;
{$EXTERNALSYM NetServiceInstall}

//  Bitmask and bit values for svci1_status, and svci2_status
//  fields.  For each "subfield", there is a mask defined,
//  and a number of constants representing the value
//  obtained by doing (status & mask).

const
// Bits 0,1 -- general status

  SERVICE_INSTALL_STATE       = $03;
  {$EXTERNALSYM SERVICE_INSTALL_STATE}
  SERVICE_UNINSTALLED         = $00;
  {$EXTERNALSYM SERVICE_UNINSTALLED}
  SERVICE_INSTALL_PENDING     = $01;
  {$EXTERNALSYM SERVICE_INSTALL_PENDING}
  SERVICE_UNINSTALL_PENDING   = $02;
  {$EXTERNALSYM SERVICE_UNINSTALL_PENDING}
  SERVICE_INSTALLED           = $03;
  {$EXTERNALSYM SERVICE_INSTALLED}

// Bits 2,3 -- paused/active status

  SERVICE_PAUSE_STATE              = $0C;
  {$EXTERNALSYM SERVICE_PAUSE_STATE}
  LM20_SERVICE_ACTIVE              = $00;
  {$EXTERNALSYM LM20_SERVICE_ACTIVE}
  LM20_SERVICE_CONTINUE_PENDING    = $04;
  {$EXTERNALSYM LM20_SERVICE_CONTINUE_PENDING}
  LM20_SERVICE_PAUSE_PENDING       = $08;
  {$EXTERNALSYM LM20_SERVICE_PAUSE_PENDING}
  LM20_SERVICE_PAUSED              = $0C;
  {$EXTERNALSYM LM20_SERVICE_PAUSED}

// Bit 4 -- uninstallable indication

  SERVICE_NOT_UNINSTALLABLE   = $00;
  {$EXTERNALSYM SERVICE_NOT_UNINSTALLABLE}
  SERVICE_UNINSTALLABLE       = $10;
  {$EXTERNALSYM SERVICE_UNINSTALLABLE}

// Bit 5 -- pausable indication

  SERVICE_NOT_PAUSABLE        = $00;
  {$EXTERNALSYM SERVICE_NOT_PAUSABLE}
  SERVICE_PAUSABLE            = $20;
  {$EXTERNALSYM SERVICE_PAUSABLE}

// Workstation service only:
// Bits 8,9,10 -- redirection paused/active

  SERVICE_REDIR_PAUSED        = $700;
  {$EXTERNALSYM SERVICE_REDIR_PAUSED}
  SERVICE_REDIR_DISK_PAUSED   = $100;
  {$EXTERNALSYM SERVICE_REDIR_DISK_PAUSED}
  SERVICE_REDIR_PRINT_PAUSED  = $200;
  {$EXTERNALSYM SERVICE_REDIR_PRINT_PAUSED}
  SERVICE_REDIR_COMM_PAUSED   = $400;
  {$EXTERNALSYM SERVICE_REDIR_COMM_PAUSED}

// Additional standard LAN Manager for MS-DOS services

  SERVICE_DOS_ENCRYPTION  = 'ENCRYPT';
  {$EXTERNALSYM SERVICE_DOS_ENCRYPTION}

// NetServiceControl opcodes.

  SERVICE_CTRL_INTERROGATE    = 0;
  {$EXTERNALSYM SERVICE_CTRL_INTERROGATE}
  SERVICE_CTRL_PAUSE          = 1;
  {$EXTERNALSYM SERVICE_CTRL_PAUSE}
  SERVICE_CTRL_CONTINUE       = 2;
  {$EXTERNALSYM SERVICE_CTRL_CONTINUE}
  SERVICE_CTRL_UNINSTALL      = 3;
  {$EXTERNALSYM SERVICE_CTRL_UNINSTALL}

// Workstation service only:  Bits used in the "arg" parameter
// to NetServiceControl in conjunction with the opcode
// SERVICE_CTRL_PAUSE or SERVICE_CTRL_CONTINUE, to pause or
// continue redirection.

  SERVICE_CTRL_REDIR_DISK     = $1;
  {$EXTERNALSYM SERVICE_CTRL_REDIR_DISK}
  SERVICE_CTRL_REDIR_PRINT    = $2;
  {$EXTERNALSYM SERVICE_CTRL_REDIR_PRINT}
  SERVICE_CTRL_REDIR_COMM     = $4;
  {$EXTERNALSYM SERVICE_CTRL_REDIR_COMM}

// Values for svci1_code, and svci2_code when status
// of the service is SERVICE_INSTALL_PENDING or
// SERVICE_UNINSTALL_PENDING.
// A service can optionally provide a hint to the installer
// that the install is proceeding and how long to wait
// (in 0.1 second increments) before querying status again.

  SERVICE_IP_NO_HINT          = $0;
  {$EXTERNALSYM SERVICE_IP_NO_HINT}
  SERVICE_CCP_NO_HINT         = $0;
  {$EXTERNALSYM SERVICE_CCP_NO_HINT}

  SERVICE_IP_QUERY_HINT       = $10000;
  {$EXTERNALSYM SERVICE_IP_QUERY_HINT}
  SERVICE_CCP_QUERY_HINT      = $10000;
  {$EXTERNALSYM SERVICE_CCP_QUERY_HINT}

// Mask for install proceeding checkpoint number

  SERVICE_IP_CHKPT_NUM        = $0FF;
  {$EXTERNALSYM SERVICE_IP_CHKPT_NUM}
  SERVICE_CCP_CHKPT_NUM       = $0FF;
  {$EXTERNALSYM SERVICE_CCP_CHKPT_NUM}

// Mask for wait time hint before querying again

  SERVICE_IP_WAIT_TIME        = $0FF00;
  {$EXTERNALSYM SERVICE_IP_WAIT_TIME}
  SERVICE_CCP_WAIT_TIME       = $0FF00;
  {$EXTERNALSYM SERVICE_CCP_WAIT_TIME}

// Shift count for building wait time _code values

  SERVICE_IP_WAITTIME_SHIFT   = 8;
  {$EXTERNALSYM SERVICE_IP_WAITTIME_SHIFT}
  SERVICE_NTIP_WAITTIME_SHIFT = 12;
  {$EXTERNALSYM SERVICE_NTIP_WAITTIME_SHIFT}

// Mask used for upper and lower portions of wait hint time.

  UPPER_HINT_MASK     = $0000FF00;
  {$EXTERNALSYM UPPER_HINT_MASK}
  LOWER_HINT_MASK     = $000000FF;
  {$EXTERNALSYM LOWER_HINT_MASK}
  UPPER_GET_HINT_MASK = $0FF00000;
  {$EXTERNALSYM UPPER_GET_HINT_MASK}
  LOWER_GET_HINT_MASK = $0000FF00;
  {$EXTERNALSYM LOWER_GET_HINT_MASK}
  SERVICE_NT_MAXTIME  = $0000FFFF;
  {$EXTERNALSYM SERVICE_NT_MAXTIME}
  SERVICE_RESRV_MASK  = $0001FFFF;
  {$EXTERNALSYM SERVICE_RESRV_MASK}
  SERVICE_MAXTIME     = $000000FF;
  {$EXTERNALSYM SERVICE_MAXTIME}

// SERVICE_BASE is the base of service error codes,
// chosen to avoid conflict with OS, redirector,
// netapi, and errlog codes.
//
// Don't change the comments following the manifest constants without
// understanding how mapmsg works.

  SERVICE_BASE                = 3050;
  {$EXTERNALSYM SERVICE_BASE}
  SERVICE_UIC_NORMAL          = 0;
  {$EXTERNALSYM SERVICE_UIC_NORMAL}
  // Uninstall codes, to be used in high byte of 'code' on final NetStatus,
  // which sets the status to UNINSTALLED.

  SERVICE_UIC_BADPARMVAL         = (SERVICE_BASE + 1);
  {$EXTERNALSYM SERVICE_UIC_BADPARMVAL}
  // The Registry or the information you just typed includes an illegal
  // value for "%1".

  SERVICE_UIC_MISSPARM           = (SERVICE_BASE + 2);
  {$EXTERNALSYM SERVICE_UIC_MISSPARM}
  // The required parameter was not provided on the command
  // line or in the configuration file.

  SERVICE_UIC_UNKPARM            = (SERVICE_BASE + 3);
  {$EXTERNALSYM SERVICE_UIC_UNKPARM}
  // LAN Manager does not recognize "%1" as a valid option.

  SERVICE_UIC_RESOURCE           = (SERVICE_BASE + 4);
  {$EXTERNALSYM SERVICE_UIC_RESOURCE}
  // A request for resource could not be satisfied.

  SERVICE_UIC_CONFIG             = (SERVICE_BASE + 5);
  {$EXTERNALSYM SERVICE_UIC_CONFIG}
  // A problem exists with the system configuration.

  SERVICE_UIC_SYSTEM             = (SERVICE_BASE + 6);
  {$EXTERNALSYM SERVICE_UIC_SYSTEM}
  // A system error has occurred.

  SERVICE_UIC_INTERNAL           = (SERVICE_BASE + 7);
  {$EXTERNALSYM SERVICE_UIC_INTERNAL}
  // An internal consistency error has occurred.

  SERVICE_UIC_AMBIGPARM          = (SERVICE_BASE + 8);
  {$EXTERNALSYM SERVICE_UIC_AMBIGPARM}
  // The configuration file or the command line has an ambiguous option.

  SERVICE_UIC_DUPPARM            = (SERVICE_BASE + 9);
  {$EXTERNALSYM SERVICE_UIC_DUPPARM}
  // The configuration file or the command line has a duplicate parameter.

  SERVICE_UIC_KILL               = (SERVICE_BASE + 10);
  {$EXTERNALSYM SERVICE_UIC_KILL}
  // The service did not respond to control and was stopped with
  // the DosKillProc function.

  SERVICE_UIC_EXEC               = (SERVICE_BASE + 11);
  {$EXTERNALSYM SERVICE_UIC_EXEC}
  // An error occurred when attempting to run the service program.

  SERVICE_UIC_SUBSERV            = (SERVICE_BASE + 12);
  {$EXTERNALSYM SERVICE_UIC_SUBSERV}
  // The sub-service failed to start.

  SERVICE_UIC_CONFLPARM          = (SERVICE_BASE + 13);
  {$EXTERNALSYM SERVICE_UIC_CONFLPARM}
  // There is a conflict in the value or use of these options: %1.

  SERVICE_UIC_FILE               = (SERVICE_BASE + 14);
  {$EXTERNALSYM SERVICE_UIC_FILE}
  // There is a problem with the file.

// The modifiers

// General:

  SERVICE_UIC_M_NULL   = 0;
  {$EXTERNALSYM SERVICE_UIC_M_NULL}

// RESOURCE:

  SERVICE_UIC_M_MEMORY    = (SERVICE_BASE + 20);     //* memory */
  {$EXTERNALSYM SERVICE_UIC_M_MEMORY}
  SERVICE_UIC_M_DISK      = (SERVICE_BASE + 21);     //* disk space */
  {$EXTERNALSYM SERVICE_UIC_M_DISK}
  SERVICE_UIC_M_THREADS   = (SERVICE_BASE + 22);     //* thread */
  {$EXTERNALSYM SERVICE_UIC_M_THREADS}
  SERVICE_UIC_M_PROCESSES = (SERVICE_BASE + 23);     //* process */
  {$EXTERNALSYM SERVICE_UIC_M_PROCESSES}

// CONFIG:

// Security failure

  SERVICE_UIC_M_SECURITY          = (SERVICE_BASE + 24);
  {$EXTERNALSYM SERVICE_UIC_M_SECURITY}
  // Security Failure.

  SERVICE_UIC_M_LANROOT           = (SERVICE_BASE + 25);
  {$EXTERNALSYM SERVICE_UIC_M_LANROOT}
  // Bad or missing LAN Manager root directory.

  SERVICE_UIC_M_REDIR             = (SERVICE_BASE + 26);
  {$EXTERNALSYM SERVICE_UIC_M_REDIR}
  // The network software is not installed.

  SERVICE_UIC_M_SERVER            = (SERVICE_BASE + 27);
  {$EXTERNALSYM SERVICE_UIC_M_SERVER}
  // The server is not started.

  SERVICE_UIC_M_SEC_FILE_ERR      = (SERVICE_BASE + 28);
  {$EXTERNALSYM SERVICE_UIC_M_SEC_FILE_ERR}
  // The server cannot access the user accounts database (NET.ACC).

  SERVICE_UIC_M_FILES             = (SERVICE_BASE + 29);
  {$EXTERNALSYM SERVICE_UIC_M_FILES}
  // Incompatible files are installed in the LANMAN tree.

  SERVICE_UIC_M_LOGS              = (SERVICE_BASE + 30);
  {$EXTERNALSYM SERVICE_UIC_M_LOGS}
  // The LANMAN\LOGS directory is invalid.

  SERVICE_UIC_M_LANGROUP          = (SERVICE_BASE + 31);
  {$EXTERNALSYM SERVICE_UIC_M_LANGROUP}
  // The domain specified could not be used.

  SERVICE_UIC_M_MSGNAME           = (SERVICE_BASE + 32);
  {$EXTERNALSYM SERVICE_UIC_M_MSGNAME}
  // The computer name is being used as a message alias on another computer.

  SERVICE_UIC_M_ANNOUNCE          = (SERVICE_BASE + 33);
  {$EXTERNALSYM SERVICE_UIC_M_ANNOUNCE}
  // The announcement of the server name failed.

  SERVICE_UIC_M_UAS               = (SERVICE_BASE + 34);
  {$EXTERNALSYM SERVICE_UIC_M_UAS}
  // The user accounts database is not configured correctly.

  SERVICE_UIC_M_SERVER_SEC_ERR    = (SERVICE_BASE + 35);
  {$EXTERNALSYM SERVICE_UIC_M_SERVER_SEC_ERR}
  // The server is not running with user-level security.

  SERVICE_UIC_M_WKSTA             = (SERVICE_BASE + 37);
  {$EXTERNALSYM SERVICE_UIC_M_WKSTA}
  // The workstation is not configured properly.

  SERVICE_UIC_M_ERRLOG            = (SERVICE_BASE + 38);
  {$EXTERNALSYM SERVICE_UIC_M_ERRLOG}
  // View your error log for details.

  SERVICE_UIC_M_FILE_UW           = (SERVICE_BASE + 39);
  {$EXTERNALSYM SERVICE_UIC_M_FILE_UW}
  // Unable to write to this file.

  SERVICE_UIC_M_ADDPAK            = (SERVICE_BASE + 40);
  {$EXTERNALSYM SERVICE_UIC_M_ADDPAK}
  // ADDPAK file is corrupted.  Delete LANMAN\NETPROG\ADDPAK.SER
  // and reapply all ADDPAKs.

  SERVICE_UIC_M_LAZY              = (SERVICE_BASE + 41);
  {$EXTERNALSYM SERVICE_UIC_M_LAZY}
  // The LM386 server cannot be started because CACHE.EXE is not running.

  SERVICE_UIC_M_UAS_MACHINE_ACCT  = (SERVICE_BASE + 42);
  {$EXTERNALSYM SERVICE_UIC_M_UAS_MACHINE_ACCT}
  // There is no account for this computer in the security database.

  SERVICE_UIC_M_UAS_SERVERS_NMEMB = (SERVICE_BASE + 43);
  {$EXTERNALSYM SERVICE_UIC_M_UAS_SERVERS_NMEMB}
  // This computer is not a member of the group SERVERS.

  SERVICE_UIC_M_UAS_SERVERS_NOGRP = (SERVICE_BASE + 44);
  {$EXTERNALSYM SERVICE_UIC_M_UAS_SERVERS_NOGRP}
  // The group SERVERS is not present in the local security database.

  SERVICE_UIC_M_UAS_INVALID_ROLE  = (SERVICE_BASE + 45);
  {$EXTERNALSYM SERVICE_UIC_M_UAS_INVALID_ROLE}
  // This Windows NT computer is configured as a member of a workgroup, not as
  // a member of a domain. The Netlogon service does not need to run in this
  // configuration.

  SERVICE_UIC_M_NETLOGON_NO_DC    = (SERVICE_BASE + 46);
  {$EXTERNALSYM SERVICE_UIC_M_NETLOGON_NO_DC}
  // The Windows NT domain controller for this domain could not be located.

  SERVICE_UIC_M_NETLOGON_DC_CFLCT = (SERVICE_BASE + 47);
  {$EXTERNALSYM SERVICE_UIC_M_NETLOGON_DC_CFLCT}
  // This computer is configured to be the primary domain controller of its domain.
  // However, the computer %1 is currently claiming to be the primary domain controller
  // of the domain.

  SERVICE_UIC_M_NETLOGON_AUTH     = (SERVICE_BASE + 48);
  {$EXTERNALSYM SERVICE_UIC_M_NETLOGON_AUTH}
  // The service failed to authenticate with the primary domain controller.

  SERVICE_UIC_M_UAS_PROLOG        = (SERVICE_BASE + 49);
  {$EXTERNALSYM SERVICE_UIC_M_UAS_PROLOG}
  // There is a problem with the security database creation date or serial number.

  SERVICE2_BASE    = 5600;
  {$EXTERNALSYM SERVICE2_BASE}
  // new SEVICE_UIC messages go here

  SERVICE_UIC_M_NETLOGON_MPATH    = (SERVICE2_BASE + 0);
  {$EXTERNALSYM SERVICE_UIC_M_NETLOGON_MPATH}
  // Could not share the User or Script path.

  SERVICE_UIC_M_LSA_MACHINE_ACCT  = (SERVICE2_BASE + 1);
  {$EXTERNALSYM SERVICE_UIC_M_LSA_MACHINE_ACCT}
  // The password for this computer is not found in the local security
  // database.

  SERVICE_UIC_M_DATABASE_ERROR    = (SERVICE2_BASE + 2);
  {$EXTERNALSYM SERVICE_UIC_M_DATABASE_ERROR}
  // An internal error occurred while accessing the computer's
  // local or network security database.

// End modifiers

// Commonly used Macros:

function SERVICE_IP_CODE(tt, nn: LongInt): LongInt;
{$EXTERNALSYM SERVICE_IP_CODE}

function SERVICE_CCP_CODE(tt, nn: LongInt): LongInt;
{$EXTERNALSYM SERVICE_CCP_CODE}

function SERVICE_UIC_CODE(cc, mm: LongInt): LongInt;
{$EXTERNALSYM SERVICE_UIC_CODE}

// This macro takes a wait hint (tt) which can have a maximum value of
// 0xFFFF and puts it into the service status code field.
// 0x0FF1FFnn  (where nn is the checkpoint information).

function SERVICE_NT_CCP_CODE(tt, nn: LongInt): LongInt;
{$EXTERNALSYM SERVICE_NT_CCP_CODE}

// This macro takes a status code field, and strips out the wait hint
// from the upper and lower sections.
// 0x0FF1FFnn results in 0x0000FFFF.

function SERVICE_NT_WAIT_GET(code: DWORD): DWORD;
{$EXTERNALSYM SERVICE_NT_WAIT_GET}

// Translated from LMUSE.H

function NetUseAdd(UncServerName: LPWSTR; Level: DWORD; Buf: Pointer;
  ParmError: PDWORD): NET_API_STATUS; stdcall;
{$EXTERNALSYM NetUseAdd}

function NetUseDel(UncServerName, UseName: LPWSTR; ForceCond: DWORD): NET_API_STATUS; stdcall;
{$EXTERNALSYM NetUseDel}

function NetUseEnum(UncServerName: LPWSTR; Level: DWORD; BufPtr: Pointer;
  PreferedMaximumSize: DWORD; var EntriesRead: DWORD; var TotalEntries: DWORD;
  ResumeHandle: PDWORD): NET_API_STATUS; stdcall;
{$EXTERNALSYM NetUseEnum}

function NetUseGetInfo(UncServerName: LPWSTR; UseName: LPWSTR; Level: DWORD;
  BufPtr: Pointer): NET_API_STATUS; stdcall;
{$EXTERNALSYM NetUseGetInfo}

type
  PUseInfo0 = ^TUseInfo0;
  _USE_INFO_0 = record
    ui0_local: LPWSTR;
    ui0_remote: LPWSTR;
  end;
  {$EXTERNALSYM _USE_INFO_0}
  TUseInfo0 = _USE_INFO_0;
  USE_INFO_0 = _USE_INFO_0;
  {$EXTERNALSYM USE_INFO_0}


  PUseInfo1 = ^TUseInfo1;
  _USE_INFO_1 = record
    ui1_local: LPWSTR;
    ui1_remote: LPWSTR;
    ui1_password: LPWSTR;
    ui1_status: DWORD;
    ui1_asg_type: DWORD;
    ui1_refcount: DWORD;
    ui1_usecount: DWORD;
  end;
  {$EXTERNALSYM _USE_INFO_1}
  TUseInfo1 = _USE_INFO_1;
  USE_INFO_1 = _USE_INFO_1;
  {$EXTERNALSYM USE_INFO_1}


  PUseInfo2 = ^TUseInfo2;
  _USE_INFO_2 = record
    ui2_local: LPWSTR;
    ui2_remote: LPWSTR;
    ui2_password: LPWSTR;
    ui2_status: DWORD;
    ui2_asg_type: DWORD;
    ui2_refcount: DWORD;
    ui2_usecount: DWORD;
    ui2_username: LPWSTR;
    ui2_domainname: LPWSTR;
  end;
  {$EXTERNALSYM _USE_INFO_2}
  TUseInfo2 = _USE_INFO_2;
  USE_INFO_2 = _USE_INFO_2;
  {$EXTERNALSYM USE_INFO_2}


  PUseInfo3 = ^TUseInfo3;
  _USE_INFO_3 = record
    ui3_ui2: USE_INFO_2;
    ui3_flags: ULONG;
  end;
  {$EXTERNALSYM _USE_INFO_3}
  TUseInfo3 = _USE_INFO_3;
  USE_INFO_3 = _USE_INFO_3;
  {$EXTERNALSYM USE_INFO_3}

// One of these values indicates the parameter within an information
// structure that is invalid when ERROR_INVALID_PARAMETER is returned by
// NetUseAdd.

const
  USE_LOCAL_PARMNUM       = 1;
  {$EXTERNALSYM USE_LOCAL_PARMNUM}
  USE_REMOTE_PARMNUM      = 2;
  {$EXTERNALSYM USE_REMOTE_PARMNUM}
  USE_PASSWORD_PARMNUM    = 3;
  {$EXTERNALSYM USE_PASSWORD_PARMNUM}
  USE_ASGTYPE_PARMNUM     = 4;
  {$EXTERNALSYM USE_ASGTYPE_PARMNUM}
  USE_USERNAME_PARMNUM    = 5;
  {$EXTERNALSYM USE_USERNAME_PARMNUM}
  USE_DOMAINNAME_PARMNUM  = 6;
  {$EXTERNALSYM USE_DOMAINNAME_PARMNUM}

// Values appearing in the ui1_status field of use_info_1 structure.
// Note that USE_SESSLOST and USE_DISCONN are synonyms.

  USE_OK                  = 0;
  {$EXTERNALSYM USE_OK}
  USE_PAUSED              = 1;
  {$EXTERNALSYM USE_PAUSED}
  USE_SESSLOST            = 2;
  {$EXTERNALSYM USE_SESSLOST}
  USE_DISCONN             = 2;
  {$EXTERNALSYM USE_DISCONN}
  USE_NETERR              = 3;
  {$EXTERNALSYM USE_NETERR}
  USE_CONN                = 4;
  {$EXTERNALSYM USE_CONN}
  USE_RECONN              = 5;
  {$EXTERNALSYM USE_RECONN}

// Values of the ui1_asg_type field of use_info_1 structure

  USE_WILDCARD            = DWORD(-1);
  {$EXTERNALSYM USE_WILDCARD}
  USE_DISKDEV             = 0;
  {$EXTERNALSYM USE_DISKDEV}
  USE_SPOOLDEV            = 1;
  {$EXTERNALSYM USE_SPOOLDEV}
  USE_CHARDEV             = 2;
  {$EXTERNALSYM USE_CHARDEV}
  USE_IPC                 = 3;
  {$EXTERNALSYM USE_IPC}

// Flags defined in the use_info_3 structure

  CREATE_NO_CONNECT = $1;        // creation flags
  {$EXTERNALSYM CREATE_NO_CONNECT}
  CREATE_BYPASS_CSC = $2;        // force connection to server, bypassing CSC
                                 //  all ops on this connection go to the server,
                                 //  never to the cache
  {$EXTERNALSYM CREATE_BYPASS_CSC}

// Translated from LMWKSTA.H

function NetWkstaGetInfo(servername: LPWSTR; level: DWORD;
  var bufptr: Pointer): NET_API_STATUS; stdcall;
{$EXTERNALSYM NetWkstaGetInfo}

function NetWkstaSetInfo(servername: LPWSTR; level: DWORD; buffer: Pointer;
  parm_err: PDWORD): NET_API_STATUS; stdcall;
{$EXTERNALSYM NetWkstaSetInfo}

function NetWkstaUserGetInfo(reserved: LPWSTR; level: DWORD;
  bufptr: Pointer): NET_API_STATUS; stdcall;
{$EXTERNALSYM NetWkstaUserGetInfo}

function NetWkstaUserSetInfo(reserved: LPWSTR; level: DWORD; buf: Pointer;
  parm_err: PDWORD): NET_API_STATUS; stdcall;
{$EXTERNALSYM NetWkstaUserSetInfo}

function NetWkstaUserEnum(servername: LPWSTR; level: DWORD; bufptr: Pointer;
  prefmaxlen: DWORD; var entriesread: DWORD; var totalentries: DWORD;
  resumehandle: PDWORD): NET_API_STATUS; stdcall;
{$EXTERNALSYM NetWkstaUserEnum}

function NetWkstaTransportAdd(servername: LPWSTR; level: DWORD; buf: Pointer;
  parm_err: PDWORD): NET_API_STATUS; stdcall;
{$EXTERNALSYM NetWkstaTransportAdd}

function NetWkstaTransportDel(servername: LPWSTR; transportname: LPWSTR;
  ucond: DWORD): NET_API_STATUS; stdcall;
{$EXTERNALSYM NetWkstaTransportDel}

function NetWkstaTransportEnum(servername: LPWSTR; level: DWORD; bufptr: Pointer;
  prefmaxlen: DWORD; var entriesread: DWORD; var totalentries: DWORD;
  resumehandle: PDWORD): NET_API_STATUS; stdcall;
{$EXTERNALSYM NetWkstaTransportEnum}


// NetWkstaGetInfo and NetWkstaSetInfo
// NetWkstaGetInfo only.  System information - guest access

type
  PWkstaInfo100 = ^TWkstaInfo100;
  _WKSTA_INFO_100 = record
    wki100_platform_id: DWORD;
    wki100_computername: LPWSTR;
    wki100_langroup: LPWSTR;
    wki100_ver_major: DWORD;
    wki100_ver_minor: DWORD;
  end;
  {$EXTERNALSYM _WKSTA_INFO_100}
  TWkstaInfo100 = _WKSTA_INFO_100;
  WKSTA_INFO_100 = _WKSTA_INFO_100;
  {$EXTERNALSYM WKSTA_INFO_100}

// NetWkstaGetInfo only.  System information - user access

  PWkstaInfo101 = ^TWkstaInfo101;
  _WKSTA_INFO_101 = record
    wki101_platform_id: DWORD;
    wki101_computername: LPWSTR;
    wki101_langroup: LPWSTR;
    wki101_ver_major: DWORD;
    wki101_ver_minor: DWORD;
    wki101_lanroot: LPWSTR;
  end;
  {$EXTERNALSYM _WKSTA_INFO_101}
  TWkstaInfo101 = _WKSTA_INFO_101;
  WKSTA_INFO_101 = _WKSTA_INFO_101;
  {$EXTERNALSYM WKSTA_INFO_101}

// NetWkstaGetInfo only.  System information - admin or operator access

  PWkstaInfo102 = ^TWkstaInfo102;
  _WKSTA_INFO_102 = record
    wki102_platform_id: DWORD;
    wki102_computername: LPWSTR;
    wki102_langroup: LPWSTR;
    wki102_ver_major: DWORD;
    wki102_ver_minor: DWORD;
    wki102_lanroot: LPWSTR;
    wki102_logged_on_users: DWORD;
  end;
  {$EXTERNALSYM _WKSTA_INFO_102}
  TWkstaInfo102 = _WKSTA_INFO_102;
  WKSTA_INFO_102 = _WKSTA_INFO_102;
  {$EXTERNALSYM WKSTA_INFO_102}

// Down-level NetWkstaGetInfo and NetWkstaSetInfo.
//
// DOS specific workstation information -
//    admin or domain operator access

  PWkstaInfo302 = ^TWkstaInfo302;
  _WKSTA_INFO_302 = record
    wki302_char_wait: DWORD;
    wki302_collection_time: DWORD;
    wki302_maximum_collection_count: DWORD;
    wki302_keep_conn: DWORD;
    wki302_keep_search: DWORD;
    wki302_max_cmds: DWORD;
    wki302_num_work_buf: DWORD;
    wki302_siz_work_buf: DWORD;
    wki302_max_wrk_cache: DWORD;
    wki302_sess_timeout: DWORD;
    wki302_siz_error: DWORD;
    wki302_num_alerts: DWORD;
    wki302_num_services: DWORD;
    wki302_errlog_sz: DWORD;
    wki302_print_buf_time: DWORD;
    wki302_num_char_buf: DWORD;
    wki302_siz_char_buf: DWORD;
    wki302_wrk_heuristics: LPWSTR;
    wki302_mailslots: DWORD;
    wki302_num_dgram_buf: DWORD;
  end;
  {$EXTERNALSYM _WKSTA_INFO_302}
  TWkstaInfo302 = _WKSTA_INFO_302;
  WKSTA_INFO_302 = _WKSTA_INFO_302;
  {$EXTERNALSYM WKSTA_INFO_302}

// Down-level NetWkstaGetInfo and NetWkstaSetInfo
//
// OS/2 specific workstation information -
//    admin or domain operator access

  PWkstaInfo402 = ^TWkstaInfo402;
  _WKSTA_INFO_402 = record
    wki402_char_wait: DWORD;
    wki402_collection_time: DWORD;
    wki402_maximum_collection_count: DWORD;
    wki402_keep_conn: DWORD;
    wki402_keep_search: DWORD;
    wki402_max_cmds: DWORD;
    wki402_num_work_buf: DWORD;
    wki402_siz_work_buf: DWORD;
    wki402_max_wrk_cache: DWORD;
    wki402_sess_timeout: DWORD;
    wki402_siz_error: DWORD;
    wki402_num_alerts: DWORD;
    wki402_num_services: DWORD;
    wki402_errlog_sz: DWORD;
    wki402_print_buf_time: DWORD;
    wki402_num_char_buf: DWORD;
    wki402_siz_char_buf: DWORD;
    wki402_wrk_heuristics: LPWSTR;
    wki402_mailslots: DWORD;
    wki402_num_dgram_buf: DWORD;
    wki402_max_threads: DWORD;
  end;
  {$EXTERNALSYM _WKSTA_INFO_402}
  TWkstaInfo402 = _WKSTA_INFO_402;
  WKSTA_INFO_402 = _WKSTA_INFO_402;
  {$EXTERNALSYM WKSTA_INFO_402}

// Same-level NetWkstaGetInfo and NetWkstaSetInfo.
//
// NT specific workstation information -
//    admin or domain operator access

  PWkstaInfo502 = ^TWkstaInfo502;
  _WKSTA_INFO_502 = record
    wki502_char_wait: DWORD;
    wki502_collection_time: DWORD;
    wki502_maximum_collection_count: DWORD;
    wki502_keep_conn: DWORD;
    wki502_max_cmds: DWORD;
    wki502_sess_timeout: DWORD;
    wki502_siz_char_buf: DWORD;
    wki502_max_threads: DWORD;

    wki502_lock_quota: DWORD;
    wki502_lock_increment: DWORD;
    wki502_lock_maximum: DWORD;
    wki502_pipe_increment: DWORD;
    wki502_pipe_maximum: DWORD;
    wki502_cache_file_timeout: DWORD;
    wki502_dormant_file_limit: DWORD;
    wki502_read_ahead_throughput: DWORD;

    wki502_num_mailslot_buffers: DWORD;
    wki502_num_srv_announce_buffers: DWORD;
    wki502_max_illegal_datagram_events: DWORD;
    wki502_illegal_datagram_event_reset_frequency: DWORD;
    wki502_log_election_packets: BOOL;

    wki502_use_opportunistic_locking: BOOL;
    wki502_use_unlock_behind: BOOL;
    wki502_use_close_behind: BOOL;
    wki502_buf_named_pipes: BOOL;
    wki502_use_lock_read_unlock: BOOL;
    wki502_utilize_nt_caching: BOOL;
    wki502_use_raw_read: BOOL;
    wki502_use_raw_write: BOOL;
    wki502_use_write_raw_data: BOOL;
    wki502_use_encryption: BOOL;
    wki502_buf_files_deny_write: BOOL;
    wki502_buf_read_only_files: BOOL;
    wki502_force_core_create_mode: BOOL;
    wki502_use_512_byte_max_transfer: BOOL;
  end;
  {$EXTERNALSYM _WKSTA_INFO_502}
  TWkstaInfo502 = _WKSTA_INFO_502;
  WKSTA_INFO_502 = _WKSTA_INFO_502;
  {$EXTERNALSYM WKSTA_INFO_502}

// The following info-levels are only valid for NetWkstaSetInfo

// The following levels are supported on down-level systems (LAN Man 2.x)
// as well as NT systems:

  PWkstaInfo1010 = ^TWkstaInfo1010;
  _WKSTA_INFO_1010 = record
    wki1010_char_wait: DWORD;
  end;
  {$EXTERNALSYM _WKSTA_INFO_1010}
  TWkstaInfo1010 = _WKSTA_INFO_1010;
  WKSTA_INFO_1010 = _WKSTA_INFO_1010;
  {$EXTERNALSYM WKSTA_INFO_1010}

  PWkstaInfo1011 = ^TWkstaInfo1011;
  _WKSTA_INFO_1011 = record
    wki1011_collection_time: DWORD;
  end;
  {$EXTERNALSYM _WKSTA_INFO_1011}
  TWkstaInfo1011 = _WKSTA_INFO_1011;
  WKSTA_INFO_1011 = _WKSTA_INFO_1011;
  {$EXTERNALSYM WKSTA_INFO_1011}

  PWkstaInfo1012 = ^TWkstaInfo1012;
  _WKSTA_INFO_1012 = record
    wki1012_maximum_collection_count: DWORD;
  end;
  {$EXTERNALSYM _WKSTA_INFO_1012}
  TWkstaInfo1012 = _WKSTA_INFO_1012;
  WKSTA_INFO_1012 = _WKSTA_INFO_1012;
  {$EXTERNALSYM WKSTA_INFO_1012}

// The following level are supported on down-level systems (LAN Man 2.x)
// only:

  PWkstaInfo1027 = ^TWkstaInfo1027;
  _WKSTA_INFO_1027 = record
    wki1027_errlog_sz: DWORD;
  end;
  {$EXTERNALSYM _WKSTA_INFO_1027}
  TWkstaInfo1027 = _WKSTA_INFO_1027;
  WKSTA_INFO_1027 = _WKSTA_INFO_1027;
  {$EXTERNALSYM WKSTA_INFO_1027}

  PWkstaInfo1028 = ^TWkstaInfo1028;
  _WKSTA_INFO_1028 = record
    wki1028_print_buf_time: DWORD;
  end;
  {$EXTERNALSYM _WKSTA_INFO_1028}
  TWkstaInfo1028 = _WKSTA_INFO_1028;
  WKSTA_INFO_1028 = _WKSTA_INFO_1028;
  {$EXTERNALSYM WKSTA_INFO_1028}

  PWkstaInfo1032 = ^TWkstaInfo1032;
  _WKSTA_INFO_1032 = record
    wki1032_wrk_heuristics: DWORD;
  end;
  {$EXTERNALSYM _WKSTA_INFO_1032}
  TWkstaInfo1032 = _WKSTA_INFO_1032;
  WKSTA_INFO_1032 = _WKSTA_INFO_1032;
  {$EXTERNALSYM WKSTA_INFO_1032}

// The following levels are settable on NT systems, and have no
// effect on down-level systems (i.e. LANMan 2.x) since these
// fields cannot be set on them:

  PWkstaInfo1013 = ^TWkstaInfo1013;
  _WKSTA_INFO_1013 = record
    wki1013_keep_conn: DWORD;
  end;
  {$EXTERNALSYM _WKSTA_INFO_1013}
  TWkstaInfo1013 = _WKSTA_INFO_1013;
  WKSTA_INFO_1013 = _WKSTA_INFO_1013;
  {$EXTERNALSYM WKSTA_INFO_1013}

  PWkstaInfo1018 = ^TWkstaInfo1018;
  _WKSTA_INFO_1018 = record
    wki1018_sess_timeout: DWORD;
  end;
  {$EXTERNALSYM _WKSTA_INFO_1018}
  TWkstaInfo1018 = _WKSTA_INFO_1018;
  WKSTA_INFO_1018 = _WKSTA_INFO_1018;
  {$EXTERNALSYM WKSTA_INFO_1018}

  PWkstaInfo1023 = ^TWkstaInfo1023;
  _WKSTA_INFO_1023 = record
    wki1023_siz_char_buf: DWORD;
  end;
  {$EXTERNALSYM _WKSTA_INFO_1023}
  TWkstaInfo1023 = _WKSTA_INFO_1023;
  WKSTA_INFO_1023 = _WKSTA_INFO_1023;
  {$EXTERNALSYM WKSTA_INFO_1023}

  PWkstaInfo1033 = ^TWkstaInfo1033;
  _WKSTA_INFO_1033 = record
    wki1033_max_threads: DWORD;
  end;
  {$EXTERNALSYM _WKSTA_INFO_1033}
  TWkstaInfo1033 = _WKSTA_INFO_1033;
  WKSTA_INFO_1033 = _WKSTA_INFO_1033;
  {$EXTERNALSYM WKSTA_INFO_1033}

// The following levels are only supported on NT systems:

  PWkstaInfo1041 = ^TWkstaInfo1041;
  _WKSTA_INFO_1041 = record
    wki1041_lock_quota: DWORD;
  end;
  {$EXTERNALSYM _WKSTA_INFO_1041}
  TWkstaInfo1041 = _WKSTA_INFO_1041;
  WKSTA_INFO_1041 = _WKSTA_INFO_1041;
  {$EXTERNALSYM WKSTA_INFO_1041}

  PWkstaInfo1042 = ^TWkstaInfo1042;
  _WKSTA_INFO_1042 = record
    wki1042_lock_increment: DWORD;
  end;
  {$EXTERNALSYM _WKSTA_INFO_1042}
  TWkstaInfo1042 = _WKSTA_INFO_1042;
  WKSTA_INFO_1042 = _WKSTA_INFO_1042;
  {$EXTERNALSYM WKSTA_INFO_1042}

  PWkstaInfo1043 = ^TWkstaInfo1043;
  _WKSTA_INFO_1043 = record
    wki1043_lock_maximum: DWORD;
  end;
  {$EXTERNALSYM _WKSTA_INFO_1043}
  TWkstaInfo1043 = _WKSTA_INFO_1043;
  WKSTA_INFO_1043 = _WKSTA_INFO_1043;
  {$EXTERNALSYM WKSTA_INFO_1043}

  PWkstaInfo1044 = ^TWkstaInfo1044;
  _WKSTA_INFO_1044 = record
    wki1044_pipe_increment: DWORD;
  end;
  {$EXTERNALSYM _WKSTA_INFO_1044}
  TWkstaInfo1044 = _WKSTA_INFO_1044;
  WKSTA_INFO_1044 = _WKSTA_INFO_1044;
  {$EXTERNALSYM WKSTA_INFO_1044}

  PWkstaInfo1045 = ^TWkstaInfo1045;
  _WKSTA_INFO_1045 = record
    wki1045_pipe_maximum: DWORD;
  end;
  {$EXTERNALSYM _WKSTA_INFO_1045}
  TWkstaInfo1045 = _WKSTA_INFO_1045;
  WKSTA_INFO_1045 = _WKSTA_INFO_1045;
  {$EXTERNALSYM WKSTA_INFO_1045}

  PWkstaInfo1046 = ^TWkstaInfo1046;
  _WKSTA_INFO_1046 = record
    wki1046_dormant_file_limit: DWORD;
  end;
  {$EXTERNALSYM _WKSTA_INFO_1046}
  TWkstaInfo1046 = _WKSTA_INFO_1046;
  WKSTA_INFO_1046 = _WKSTA_INFO_1046;
  {$EXTERNALSYM WKSTA_INFO_1046}

  PWkstaInfo1047 = ^TWkstaInfo1047;
  _WKSTA_INFO_1047 = record
    wki1047_cache_file_timeout: DWORD;
  end;
  {$EXTERNALSYM _WKSTA_INFO_1047}
  TWkstaInfo1047 = _WKSTA_INFO_1047;
  WKSTA_INFO_1047 = _WKSTA_INFO_1047;
  {$EXTERNALSYM WKSTA_INFO_1047}

  PWkstaInfo1048 = ^TWkstaInfo1048;
  _WKSTA_INFO_1048 = record
    wki1048_use_opportunistic_locking: BOOL;
  end;
  {$EXTERNALSYM _WKSTA_INFO_1048}
  TWkstaInfo1048 = _WKSTA_INFO_1048;
  WKSTA_INFO_1048 = _WKSTA_INFO_1048;
  {$EXTERNALSYM WKSTA_INFO_1048}

  PWkstaInfo1049 = ^TWkstaInfo1049;
  _WKSTA_INFO_1049 = record
    wki1049_use_unlock_behind: BOOL;
  end;
  {$EXTERNALSYM _WKSTA_INFO_1049}
  TWkstaInfo1049 = _WKSTA_INFO_1049;
  WKSTA_INFO_1049 = _WKSTA_INFO_1049;
  {$EXTERNALSYM WKSTA_INFO_1049}

  PWkstaInfo1050 = ^TWkstaInfo1050;
  _WKSTA_INFO_1050 = record
    wki1050_use_close_behind: BOOL;
  end;
  {$EXTERNALSYM _WKSTA_INFO_1050}
  TWkstaInfo1050 = _WKSTA_INFO_1050;
  WKSTA_INFO_1050 = _WKSTA_INFO_1050;
  {$EXTERNALSYM WKSTA_INFO_1050}

  PWkstaInfo1051 = ^TWkstaInfo1051;
  _WKSTA_INFO_1051 = record
    wki1051_buf_named_pipes: BOOL;
  end;
  {$EXTERNALSYM _WKSTA_INFO_1051}
  TWkstaInfo1051 = _WKSTA_INFO_1051;
  WKSTA_INFO_1051 = _WKSTA_INFO_1051;
  {$EXTERNALSYM WKSTA_INFO_1051}

  PWkstaInfo1052 = ^TWkstaInfo1052;
  _WKSTA_INFO_1052 = record
    wki1052_use_lock_read_unlock: BOOL;
  end;
  {$EXTERNALSYM _WKSTA_INFO_1052}
  TWkstaInfo1052 = _WKSTA_INFO_1052;
  WKSTA_INFO_1052 = _WKSTA_INFO_1052;
  {$EXTERNALSYM WKSTA_INFO_1052}

  PWkstaInfo1053 = ^TWkstaInfo1053;
  _WKSTA_INFO_1053 = record
    wki1053_utilize_nt_caching: BOOL;
  end;
  {$EXTERNALSYM _WKSTA_INFO_1053}
  TWkstaInfo1053 = _WKSTA_INFO_1053;
  WKSTA_INFO_1053 = _WKSTA_INFO_1053;
  {$EXTERNALSYM WKSTA_INFO_1053}

  PWkstaInfo1054 = ^TWkstaInfo1054;
  _WKSTA_INFO_1054 = record
    wki1054_use_raw_read: BOOL;
  end;
  {$EXTERNALSYM _WKSTA_INFO_1054}
  TWkstaInfo1054 = _WKSTA_INFO_1054;
  WKSTA_INFO_1054 = _WKSTA_INFO_1054;
  {$EXTERNALSYM WKSTA_INFO_1054}

  PWkstaInfo1055 = ^TWkstaInfo1055;
  _WKSTA_INFO_1055 = record
    wki1055_use_raw_write: BOOL;
  end;
  {$EXTERNALSYM _WKSTA_INFO_1055}
  TWkstaInfo1055 = _WKSTA_INFO_1055;
  WKSTA_INFO_1055 = _WKSTA_INFO_1055;
  {$EXTERNALSYM WKSTA_INFO_1055}

  PWkstaInfo1056 = ^TWkstaInfo1056;
  _WKSTA_INFO_1056 = record
    wki1056_use_write_raw_data: BOOL;
  end;
  {$EXTERNALSYM _WKSTA_INFO_1056}
  TWkstaInfo1056 = _WKSTA_INFO_1056;
  WKSTA_INFO_1056 = _WKSTA_INFO_1056;
  {$EXTERNALSYM WKSTA_INFO_1056}

  PWkstaInfo1057 = ^TWkstaInfo1057;
  _WKSTA_INFO_1057 = record
    wki1057_use_encryption: BOOL;
  end;
  {$EXTERNALSYM _WKSTA_INFO_1057}
  TWkstaInfo1057 = _WKSTA_INFO_1057;
  WKSTA_INFO_1057 = _WKSTA_INFO_1057;
  {$EXTERNALSYM WKSTA_INFO_1057}

  PWkstaInfo1058 = ^TWkstaInfo1058;
  _WKSTA_INFO_1058 = record
    wki1058_buf_files_deny_write: BOOL;
  end;
  {$EXTERNALSYM _WKSTA_INFO_1058}
  TWkstaInfo1058 = _WKSTA_INFO_1058;
  WKSTA_INFO_1058 = _WKSTA_INFO_1058;
  {$EXTERNALSYM WKSTA_INFO_1058}

  PWkstaInfo1059 = ^TWkstaInfo1059;
  _WKSTA_INFO_1059 = record
    wki1059_buf_read_only_files: BOOL;
  end;
  {$EXTERNALSYM _WKSTA_INFO_1059}
  TWkstaInfo1059 = _WKSTA_INFO_1059;
  WKSTA_INFO_1059 = _WKSTA_INFO_1059;
  {$EXTERNALSYM WKSTA_INFO_1059}

  PWkstaInfo1060 = ^TWkstaInfo1060;
  _WKSTA_INFO_1060 = record
    wki1060_force_core_create_mode: BOOL;
  end;
  {$EXTERNALSYM _WKSTA_INFO_1060}
  TWkstaInfo1060 = _WKSTA_INFO_1060;
  WKSTA_INFO_1060 = _WKSTA_INFO_1060;
  {$EXTERNALSYM WKSTA_INFO_1060}

  PWkstaInfo1061 = ^TWkstaInfo1061;
  _WKSTA_INFO_1061 = record
    wki1061_use_512_byte_max_transfer: BOOL;
  end;
  {$EXTERNALSYM _WKSTA_INFO_1061}
  TWkstaInfo1061 = _WKSTA_INFO_1061;
  WKSTA_INFO_1061 = _WKSTA_INFO_1061;
  {$EXTERNALSYM WKSTA_INFO_1061}

  PWkstaInfo1062 = ^TWkstaInfo1062;
  _WKSTA_INFO_1062 = record
    wki1062_read_ahead_throughput: DWORD;
  end;
  {$EXTERNALSYM _WKSTA_INFO_1062}
  TWkstaInfo1062 = _WKSTA_INFO_1062;
  WKSTA_INFO_1062 = _WKSTA_INFO_1062;
  {$EXTERNALSYM WKSTA_INFO_1062}


// NetWkstaUserGetInfo (local only) and NetWkstaUserEnum -
//     no access restrictions.

  PWkstaUserInfo0 = ^TWkstaUserInfo0;
  _WKSTA_USER_INFO_0 = record
    wkui0_username: LPWSTR;
  end;
  {$EXTERNALSYM _WKSTA_USER_INFO_0}
  TWkstaUserInfo0 = _WKSTA_USER_INFO_0;
  WKSTA_USER_INFO_0 = _WKSTA_USER_INFO_0;
  {$EXTERNALSYM WKSTA_USER_INFO_0}

// NetWkstaUserGetInfo (local only) and NetWkstaUserEnum -
//     no access restrictions.

  PWkstaUserInfo1 = ^TWkstaUserInfo1;
  _WKSTA_USER_INFO_1 = record
    wkui1_username: LPWSTR;
    wkui1_logon_domain: LPWSTR;
    wkui1_oth_domains: LPWSTR;
    wkui1_logon_server: LPWSTR;
  end;
  {$EXTERNALSYM _WKSTA_USER_INFO_1}
  TWkstaUserInfo1 = _WKSTA_USER_INFO_1;
  WKSTA_USER_INFO_1 = _WKSTA_USER_INFO_1;
  {$EXTERNALSYM WKSTA_USER_INFO_1}

// NetWkstaUserSetInfo - local access.

  PWkstaUserInfo1101 = ^TWkstaUserInfo1101;
  _WKSTA_USER_INFO_1101 = record
    wkui1101_oth_domains: LPWSTR;
  end;
  {$EXTERNALSYM _WKSTA_USER_INFO_1101}
  TWkstaUserInfo1101 = _WKSTA_USER_INFO_1101;
  WKSTA_USER_INFO_1101 = _WKSTA_USER_INFO_1101;
  {$EXTERNALSYM WKSTA_USER_INFO_1101}

// NetWkstaTransportAdd - admin access

  PWkstaTransportInfo0 = ^TWkstaTransportInfo0;
  _WKSTA_TRANSPORT_INFO_0 = record
    wkti0_quality_of_service: DWORD;
    wkti0_number_of_vcs: DWORD;
    wkti0_transport_name: LPWSTR;
    wkti0_transport_address: LPWSTR;
    wkti0_wan_ish: BOOL;
  end;
  {$EXTERNALSYM _WKSTA_TRANSPORT_INFO_0}
  TWkstaTransportInfo0 = _WKSTA_TRANSPORT_INFO_0;
  WKSTA_TRANSPORT_INFO_0 = _WKSTA_TRANSPORT_INFO_0;
  {$EXTERNALSYM WKSTA_TRANSPORT_INFO_0}

// Special Values and Constants

// Identifiers for use as NetWkstaSetInfo parmnum parameter

// One of these values indicates the parameter within an information
// structure that is invalid when ERROR_INVALID_PARAMETER is returned by
// NetWkstaSetInfo.

const
  WKSTA_PLATFORM_ID_PARMNUM               = 100;
  {$EXTERNALSYM WKSTA_PLATFORM_ID_PARMNUM}
  WKSTA_COMPUTERNAME_PARMNUM              = 1;
  {$EXTERNALSYM WKSTA_COMPUTERNAME_PARMNUM}
  WKSTA_LANGROUP_PARMNUM                  = 2;
  {$EXTERNALSYM WKSTA_LANGROUP_PARMNUM}
  WKSTA_VER_MAJOR_PARMNUM                 = 4;
  {$EXTERNALSYM WKSTA_VER_MAJOR_PARMNUM}
  WKSTA_VER_MINOR_PARMNUM                 = 5;
  {$EXTERNALSYM WKSTA_VER_MINOR_PARMNUM}
  WKSTA_LOGGED_ON_USERS_PARMNUM           = 6;
  {$EXTERNALSYM WKSTA_LOGGED_ON_USERS_PARMNUM}
  WKSTA_LANROOT_PARMNUM                   = 7;
  {$EXTERNALSYM WKSTA_LANROOT_PARMNUM}
  WKSTA_LOGON_DOMAIN_PARMNUM              = 8;
  {$EXTERNALSYM WKSTA_LOGON_DOMAIN_PARMNUM}
  WKSTA_LOGON_SERVER_PARMNUM              = 9;
  {$EXTERNALSYM WKSTA_LOGON_SERVER_PARMNUM}
  WKSTA_CHARWAIT_PARMNUM                  = 10;  // Supported by down-level.
  {$EXTERNALSYM WKSTA_CHARWAIT_PARMNUM}
  WKSTA_CHARTIME_PARMNUM                  = 11;  // Supported by down-level.
  {$EXTERNALSYM WKSTA_CHARTIME_PARMNUM}
  WKSTA_CHARCOUNT_PARMNUM                 = 12;  // Supported by down-level.
  {$EXTERNALSYM WKSTA_CHARCOUNT_PARMNUM}
  WKSTA_KEEPCONN_PARMNUM                  = 13;
  {$EXTERNALSYM WKSTA_KEEPCONN_PARMNUM}
  WKSTA_KEEPSEARCH_PARMNUM                = 14;
  {$EXTERNALSYM WKSTA_KEEPSEARCH_PARMNUM}
  WKSTA_MAXCMDS_PARMNUM                   = 15;
  {$EXTERNALSYM WKSTA_MAXCMDS_PARMNUM}
  WKSTA_NUMWORKBUF_PARMNUM                = 16;
  {$EXTERNALSYM WKSTA_NUMWORKBUF_PARMNUM}
  WKSTA_MAXWRKCACHE_PARMNUM               = 17;
  {$EXTERNALSYM WKSTA_MAXWRKCACHE_PARMNUM}
  WKSTA_SESSTIMEOUT_PARMNUM               = 18;
  {$EXTERNALSYM WKSTA_SESSTIMEOUT_PARMNUM}
  WKSTA_SIZERROR_PARMNUM                  = 19;
  {$EXTERNALSYM WKSTA_SIZERROR_PARMNUM}
  WKSTA_NUMALERTS_PARMNUM                 = 20;
  {$EXTERNALSYM WKSTA_NUMALERTS_PARMNUM}
  WKSTA_NUMSERVICES_PARMNUM               = 21;
  {$EXTERNALSYM WKSTA_NUMSERVICES_PARMNUM}
  WKSTA_NUMCHARBUF_PARMNUM                = 22;
  {$EXTERNALSYM WKSTA_NUMCHARBUF_PARMNUM}
  WKSTA_SIZCHARBUF_PARMNUM                = 23;
  {$EXTERNALSYM WKSTA_SIZCHARBUF_PARMNUM}
  WKSTA_ERRLOGSZ_PARMNUM                  = 27;  // Supported by down-level.
  {$EXTERNALSYM WKSTA_ERRLOGSZ_PARMNUM}
  WKSTA_PRINTBUFTIME_PARMNUM              = 28;  // Supported by down-level.
  {$EXTERNALSYM WKSTA_PRINTBUFTIME_PARMNUM}
  WKSTA_SIZWORKBUF_PARMNUM                = 29;
  {$EXTERNALSYM WKSTA_SIZWORKBUF_PARMNUM}
  WKSTA_MAILSLOTS_PARMNUM                 = 30;
  {$EXTERNALSYM WKSTA_MAILSLOTS_PARMNUM}
  WKSTA_NUMDGRAMBUF_PARMNUM               = 31;
  {$EXTERNALSYM WKSTA_NUMDGRAMBUF_PARMNUM}
  WKSTA_WRKHEURISTICS_PARMNUM             = 32;  // Supported by down-level.
  {$EXTERNALSYM WKSTA_WRKHEURISTICS_PARMNUM}
  WKSTA_MAXTHREADS_PARMNUM                = 33;
  {$EXTERNALSYM WKSTA_MAXTHREADS_PARMNUM}

  WKSTA_LOCKQUOTA_PARMNUM                 = 41;
  {$EXTERNALSYM WKSTA_LOCKQUOTA_PARMNUM}
  WKSTA_LOCKINCREMENT_PARMNUM             = 42;
  {$EXTERNALSYM WKSTA_LOCKINCREMENT_PARMNUM}
  WKSTA_LOCKMAXIMUM_PARMNUM               = 43;
  {$EXTERNALSYM WKSTA_LOCKMAXIMUM_PARMNUM}
  WKSTA_PIPEINCREMENT_PARMNUM             = 44;
  {$EXTERNALSYM WKSTA_PIPEINCREMENT_PARMNUM}
  WKSTA_PIPEMAXIMUM_PARMNUM               = 45;
  {$EXTERNALSYM WKSTA_PIPEMAXIMUM_PARMNUM}
  WKSTA_DORMANTFILELIMIT_PARMNUM          = 46;
  {$EXTERNALSYM WKSTA_DORMANTFILELIMIT_PARMNUM}
  WKSTA_CACHEFILETIMEOUT_PARMNUM          = 47;
  {$EXTERNALSYM WKSTA_CACHEFILETIMEOUT_PARMNUM}
  WKSTA_USEOPPORTUNISTICLOCKING_PARMNUM   = 48;
  {$EXTERNALSYM WKSTA_USEOPPORTUNISTICLOCKING_PARMNUM}
  WKSTA_USEUNLOCKBEHIND_PARMNUM           = 49;
  {$EXTERNALSYM WKSTA_USEUNLOCKBEHIND_PARMNUM}
  WKSTA_USECLOSEBEHIND_PARMNUM            = 50;
  {$EXTERNALSYM WKSTA_USECLOSEBEHIND_PARMNUM}
  WKSTA_BUFFERNAMEDPIPES_PARMNUM          = 51;
  {$EXTERNALSYM WKSTA_BUFFERNAMEDPIPES_PARMNUM}
  WKSTA_USELOCKANDREADANDUNLOCK_PARMNUM   = 52;
  {$EXTERNALSYM WKSTA_USELOCKANDREADANDUNLOCK_PARMNUM}
  WKSTA_UTILIZENTCACHING_PARMNUM          = 53;
  {$EXTERNALSYM WKSTA_UTILIZENTCACHING_PARMNUM}
  WKSTA_USERAWREAD_PARMNUM                = 54;
  {$EXTERNALSYM WKSTA_USERAWREAD_PARMNUM}
  WKSTA_USERAWWRITE_PARMNUM               = 55;
  {$EXTERNALSYM WKSTA_USERAWWRITE_PARMNUM}
  WKSTA_USEWRITERAWWITHDATA_PARMNUM       = 56;
  {$EXTERNALSYM WKSTA_USEWRITERAWWITHDATA_PARMNUM}
  WKSTA_USEENCRYPTION_PARMNUM             = 57;
  {$EXTERNALSYM WKSTA_USEENCRYPTION_PARMNUM}
  WKSTA_BUFFILESWITHDENYWRITE_PARMNUM     = 58;
  {$EXTERNALSYM WKSTA_BUFFILESWITHDENYWRITE_PARMNUM}
  WKSTA_BUFFERREADONLYFILES_PARMNUM       = 59;
  {$EXTERNALSYM WKSTA_BUFFERREADONLYFILES_PARMNUM}
  WKSTA_FORCECORECREATEMODE_PARMNUM       = 60;
  {$EXTERNALSYM WKSTA_FORCECORECREATEMODE_PARMNUM}
  WKSTA_USE512BYTESMAXTRANSFER_PARMNUM    = 61;
  {$EXTERNALSYM WKSTA_USE512BYTESMAXTRANSFER_PARMNUM}
  WKSTA_READAHEADTHRUPUT_PARMNUM          = 62;
  {$EXTERNALSYM WKSTA_READAHEADTHRUPUT_PARMNUM}


// One of these values indicates the parameter within an information
// structure that is invalid when ERROR_INVALID_PARAMETER is returned by
// NetWkstaUserSetInfo.

  WKSTA_OTH_DOMAINS_PARMNUM              = 101;
  {$EXTERNALSYM WKSTA_OTH_DOMAINS_PARMNUM}

// One of these values indicates the parameter within an information
// structure that is invalid when ERROR_INVALID_PARAMETER is returned by
// NetWkstaTransportAdd.

  TRANSPORT_QUALITYOFSERVICE_PARMNUM     = 201;
  {$EXTERNALSYM TRANSPORT_QUALITYOFSERVICE_PARMNUM}
  TRANSPORT_NAME_PARMNUM                 = 202;
  {$EXTERNALSYM TRANSPORT_NAME_PARMNUM}

// Translated from LMAPIBUF.H

function NetApiBufferAllocate(ByteCount: DWORD; var Buffer: Pointer): NET_API_STATUS; stdcall;
{$EXTERNALSYM NetApiBufferAllocate}

function NetApiBufferFree(Buffer: Pointer): NET_API_STATUS; stdcall;
{$EXTERNALSYM NetApiBufferFree}

function NetApiBufferReallocate(OldBuffer: Pointer; NewByteCount: DWORD;
  var NewBuffer: Pointer): NET_API_STATUS; stdcall;
{$EXTERNALSYM NetApiBufferReallocate}

function NetApiBufferSize(Buffer: Pointer; var ByteCount: DWORD): NET_API_STATUS; stdcall;
{$EXTERNALSYM NetApiBufferSize}

// The following private function will go away eventually.
// Call NetApiBufferAllocate instead.
// Internal Function

function NetapipBufferAllocate(ByteCount: DWORD; var Buffer: Pointer): NET_API_STATUS; stdcall;
{$EXTERNALSYM NetapipBufferAllocate}

// Translated from LMCONFIG.H

function NetConfigGet(server: LPCWSTR; component: LPCWSTR; parameter: LPCWSTR;
  bufptr: Pointer; var totalavailable: DWORD): NET_API_STATUS; stdcall;
{$EXTERNALSYM NetConfigGet}

function NetConfigGetAll(server: LPCWSTR; component: LPCWSTR; bufptr: Pointer;
  var totalavailable: DWORD): NET_API_STATUS; stdcall;
{$EXTERNALSYM NetConfigGetAll}

function NetConfigSet(server: LPCWSTR; reserved1: LPCWSTR; component: LPCWSTR;
  level: DWORD; reserved2: DWORD; buf: Pointer; reserved3: DWORD): NET_API_STATUS; stdcall;
{$EXTERNALSYM NetConfigSet}

function NetRegisterDomainNameChangeNotification(NotificationEventHandle: PHandle): NET_API_STATUS; stdcall;
{$EXTERNALSYM NetRegisterDomainNameChangeNotification}

function NetUnregisterDomainNameChangeNotification(NotificationEventHandle: THandle): NET_API_STATUS; stdcall;
{$EXTERNALSYM NetUnregisterDomainNameChangeNotification}

// Data Structures - Config

type
  PConfigInfo0 = ^TConfigInfo0;
  _CONFIG_INFO_0 = record
    cfgi0_key: LPWSTR;
    cfgi0_data: LPWSTR;
  end;
  {$EXTERNALSYM _CONFIG_INFO_0}
  TConfigInfo0 = _CONFIG_INFO_0;
  CONFIG_INFO_0 = _CONFIG_INFO_0;
  {$EXTERNALSYM CONFIG_INFO_0}

// Translated from LMSTATS.H

// Function Prototypes - Statistics

function NetStatisticsGet(server: LPWSTR; service: LPWSTR; level: DWORD;
  options: DWORD; bufptr: Pointer): NET_API_STATUS; stdcall;
{$EXTERNALSYM NetStatisticsGet}

// Data Structures - Statistics

type
  PStatWorkstation0 = ^TStatWorkstation0;
  _STAT_WORKSTATION_0 = record
    stw0_start: DWORD;
    stw0_numNCB_r: DWORD;
    stw0_numNCB_s: DWORD;
    stw0_numNCB_a: DWORD;
    stw0_fiNCB_r: DWORD;
    stw0_fiNCB_s: DWORD;
    stw0_fiNCB_a: DWORD;
    stw0_fcNCB_r: DWORD;
    stw0_fcNCB_s: DWORD;
    stw0_fcNCB_a: DWORD;
    stw0_sesstart: DWORD;
    stw0_sessfailcon: DWORD;
    stw0_sessbroke: DWORD;
    stw0_uses: DWORD;
    stw0_usefail: DWORD;
    stw0_autorec: DWORD;
    stw0_bytessent_r_lo: DWORD;
    stw0_bytessent_r_hi: DWORD;
    stw0_bytesrcvd_r_lo: DWORD;
    stw0_bytesrcvd_r_hi: DWORD;
    stw0_bytessent_s_lo: DWORD;
    stw0_bytessent_s_hi: DWORD;
    stw0_bytesrcvd_s_lo: DWORD;
    stw0_bytesrcvd_s_hi: DWORD;
    stw0_bytessent_a_lo: DWORD;
    stw0_bytessent_a_hi: DWORD;
    stw0_bytesrcvd_a_lo: DWORD;
    stw0_bytesrcvd_a_hi: DWORD;
    stw0_reqbufneed: DWORD;
    stw0_bigbufneed: DWORD;
  end;
  {$EXTERNALSYM _STAT_WORKSTATION_0}
  TStatWorkstation0 = _STAT_WORKSTATION_0;
  STAT_WORKSTATION_0 = _STAT_WORKSTATION_0;
  {$EXTERNALSYM STAT_WORKSTATION_0}

  PStatServer0 = ^TStatServer0;
  _STAT_SERVER_0 = record
    sts0_start: DWORD;
    sts0_fopens: DWORD;
    sts0_devopens: DWORD;
    sts0_jobsqueued: DWORD;
    sts0_sopens: DWORD;
    sts0_stimedout: DWORD;
    sts0_serrorout: DWORD;
    sts0_pwerrors: DWORD;
    sts0_permerrors: DWORD;
    sts0_syserrors: DWORD;
    sts0_bytessent_low: DWORD;
    sts0_bytessent_high: DWORD;
    sts0_bytesrcvd_low: DWORD;
    sts0_bytesrcvd_high: DWORD;
    sts0_avresponse: DWORD;
    sts0_reqbufneed: DWORD;
    sts0_bigbufneed: DWORD;
  end;
  {$EXTERNALSYM _STAT_SERVER_0}
  TStatServer0 = _STAT_SERVER_0;
  STAT_SERVER_0 = _STAT_SERVER_0;
  {$EXTERNALSYM STAT_SERVER_0}

// Special Values and Constants

const
  STATSOPT_CLR    = 1;
{$EXTERNALSYM STATSOPT_CLR}
  STATS_NO_VALUE  = DWORD(-1);
{$EXTERNALSYM STATS_NO_VALUE}
  STATS_OVERFLOW  = DWORD(-2);
{$EXTERNALSYM STATS_OVERFLOW}

// Translated from LMAUDIT.H

type
  PHLog = ^THLog;
  _HLOG = record
    time: DWORD;
    last_flags: DWORD;
    offset: DWORD;
    rec_offset: DWORD;
  end;
  {$EXTERNALSYM _HLOG}
  THLog = _HLOG;
  HLOG = _HLOG;
  {$EXTERNALSYM HLOG}


const
  LOGFLAGS_FORWARD  = 0;
  {$EXTERNALSYM LOGFLAGS_FORWARD}
  LOGFLAGS_BACKWARD = $1;
  {$EXTERNALSYM LOGFLAGS_BACKWARD}
  LOGFLAGS_SEEK     = $2;
  {$EXTERNALSYM LOGFLAGS_SEEK}

// Function Prototypes - Audit

function NetAuditClear(server, backupfile, service: LPCWSTR): NET_API_STATUS; stdcall;
{$EXTERNALSYM NetAuditClear}

function NetAuditRead(server: LPCWSTR; service: LPCWSTR; auditloghandle: PHLog;
  offset: DWORD; reserved1: PDWORD; reserved2: DWORD; offsetflag: DWORD;
  bufptr: Pointer; prefmaxlen: DWORD; var bytesread: DWORD;
  var totalavailable: DWORD): NET_API_STATUS; stdcall;
{$EXTERNALSYM NetAuditRead}

function NetAuditWrite(type_: DWORD; buf: Pointer; numbytes: DWORD;
  service: LPCWSTR; reserved: Pointer): NET_API_STATUS; stdcall;
{$EXTERNALSYM NetAuditWrite}

// Data Structures - Audit

type
  PAuditEntry = ^TAuditEntry;
  _AUDIT_ENTRY = record
    ae_len: DWORD;
    ae_reserved: DWORD;
    ae_time: DWORD;
    ae_type: DWORD;
    ae_data_offset: DWORD; //* Offset from beginning address of audit_entry */
    ae_data_size: DWORD;   // byte count of ae_data area (not incl pad).
  end;
  {$EXTERNALSYM _AUDIT_ENTRY}
  TAuditEntry = _AUDIT_ENTRY;
  AUDIT_ENTRY = _AUDIT_ENTRY;
  {$EXTERNALSYM AUDIT_ENTRY}

  PAeSrvstatus = ^TAeSrvstatus;
  _AE_SRVSTATUS = record
    ae_sv_status: DWORD;
  end;
  {$EXTERNALSYM _AE_SRVSTATUS}
  TAeSrvstatus = _AE_SRVSTATUS;
//  AE_SRVSTATUS = _AE_SRVSTATUS;
//  {$EXTERNALSYM AE_SRVSTATUS}

  PAeSesslogOn = ^TAwSesslogOn;
  _AE_SESSLOGON = record
    ae_so_compname: DWORD;
    ae_so_username: DWORD;
    ae_so_privilege: DWORD;
  end;
  {$EXTERNALSYM _AE_SESSLOGON}
  TAwSesslogOn = _AE_SESSLOGON;
//  AE_SESSLOGON = _AE_SESSLOGON;
//  {$EXTERNALSYM AE_SESSLOGON}

  PAeSesslogOff = ^TAeSesslogOff;
  _AE_SESSLOGOFF = record
    ae_sf_compname: DWORD;
    ae_sf_username: DWORD;
    ae_sf_reason: DWORD;
  end;
  {$EXTERNALSYM _AE_SESSLOGOFF}
  TAeSesslogOff = _AE_SESSLOGOFF;
//  AE_SESSLOGOFF = _AE_SESSLOGOFF;
//  {$EXTERNALSYM AE_SESSLOGOFF}

  PAeSessPwErr = ^TAeSessPwErr;
  _AE_SESSPWERR = record
    ae_sp_compname: DWORD;
    ae_sp_username: DWORD;
  end;
  {$EXTERNALSYM _AE_SESSPWERR}
  TAeSessPwErr = _AE_SESSPWERR;
//  AE_SESSPWERR = _AE_SESSPWERR;
//  {$EXTERNALSYM AE_SESSPWERR}

  PAeConnStart = ^TAeConnStart;
  _AE_CONNSTART = record
    ae_ct_compname: DWORD;
    ae_ct_username: DWORD;
    ae_ct_netname: DWORD;
    ae_ct_connid: DWORD;
  end;
  {$EXTERNALSYM _AE_CONNSTART}
  TAeConnStart = _AE_CONNSTART;
//  AE_CONNSTART = _AE_CONNSTART;
//  {$EXTERNALSYM AE_CONNSTART}

  PAeConnStop = ^TAeConnStop;
  _AE_CONNSTOP = record
    ae_cp_compname: DWORD;
    ae_cp_username: DWORD;
    ae_cp_netname: DWORD;
    ae_cp_connid: DWORD;
    ae_cp_reason: DWORD;
  end;
  {$EXTERNALSYM _AE_CONNSTOP}
  TAeConnStop = _AE_CONNSTOP;
//  AE_CONNSTOP = _AE_CONNSTOP;
//  {$EXTERNALSYM AE_CONNSTOP}

  PAeConnRej = ^TAeConnRej;
  _AE_CONNREJ = record
    ae_cr_compname: DWORD;
    ae_cr_username: DWORD;
    ae_cr_netname: DWORD;
    ae_cr_reason: DWORD;
  end;
  {$EXTERNALSYM _AE_CONNREJ}
  TAeConnRej = _AE_CONNREJ;
//  AE_CONNREJ = _AE_CONNREJ;
//  {$EXTERNALSYM AE_CONNREJ}

  PAeResAccess = ^TAeResAccess;
  _AE_RESACCESS = record
    ae_ra_compname: DWORD;
    ae_ra_username: DWORD;
    ae_ra_resname: DWORD;
    ae_ra_operation: DWORD;
    ae_ra_returncode: DWORD;
    ae_ra_restype: DWORD;
    ae_ra_fileid: DWORD;
  end;
  {$EXTERNALSYM _AE_RESACCESS}
  TAeResAccess = _AE_RESACCESS;
//  AE_RESACCESS = _AE_RESACCESS;
//  {$EXTERNALSYM AE_RESACCESS}

  PAeResAccessRej = ^TAeResAccessRej;
  _AE_RESACCESSREJ = record
    ae_rr_compname: DWORD;
    ae_rr_username: DWORD;
    ae_rr_resname: DWORD;
    ae_rr_operation: DWORD;
  end;
  {$EXTERNALSYM _AE_RESACCESSREJ}
  TAeResAccessRej = _AE_RESACCESSREJ;
//  AE_RESACCESSREJ = _AE_RESACCESSREJ;
//  {$EXTERNALSYM AE_RESACCESSREJ}

  PAeCloseFile = ^TAeCloseFile;
  _AE_CLOSEFILE = record
    ae_cf_compname: DWORD;
    ae_cf_username: DWORD;
    ae_cf_resname: DWORD;
    ae_cf_fileid: DWORD;
    ae_cf_duration: DWORD;
    ae_cf_reason: DWORD;
  end;
  {$EXTERNALSYM _AE_CLOSEFILE}
  TAeCloseFile = _AE_CLOSEFILE;
//  AE_CLOSEFILE = _AE_CLOSEFILE;
//  {$EXTERNALSYM AE_CLOSEFILE}

  PAeServiceStat = ^TAeServiceStat;
  _AE_SERVICESTAT = record
    ae_ss_compname: DWORD;
    ae_ss_username: DWORD;
    ae_ss_svcname: DWORD;
    ae_ss_status: DWORD;
    ae_ss_code: DWORD;
    ae_ss_text: DWORD;
    ae_ss_returnval: DWORD;
  end;
  {$EXTERNALSYM _AE_SERVICESTAT}
  TAeServiceStat = _AE_SERVICESTAT;
//  AE_SERVICESTAT = _AE_SERVICESTAT;
//  {$EXTERNALSYM AE_SERVICESTAT}

  PAeAclMod = ^TAeAclMod;
  _AE_ACLMOD = record
    ae_am_compname: DWORD;
    ae_am_username: DWORD;
    ae_am_resname: DWORD;
    ae_am_action: DWORD;
    ae_am_datalen: DWORD;
  end;
  {$EXTERNALSYM _AE_ACLMOD}
  TAeAclMod = _AE_ACLMOD;
//  AE_ACLMOD = _AE_ACLMOD;
//  {$EXTERNALSYM AE_ACLMOD}

  PAeUasMod = ^TAeUasMod;
  _AE_UASMOD = record
    ae_um_compname: DWORD;
    ae_um_username: DWORD;
    ae_um_resname: DWORD;
    ae_um_rectype: DWORD;
    ae_um_action: DWORD;
    ae_um_datalen: DWORD;
  end;
  {$EXTERNALSYM _AE_UASMOD}
  TAeUasMod = _AE_UASMOD;
//  AE_UASMOD = _AE_UASMOD;
//  {$EXTERNALSYM AE_UASMOD}

  PAeNetLogon = ^TAeNetLogon;
  _AE_NETLOGON = record
    ae_no_compname: DWORD;
    ae_no_username: DWORD;
    ae_no_privilege: DWORD;
    ae_no_authflags: DWORD;
  end;
  {$EXTERNALSYM _AE_NETLOGON}
  TAeNetLogon = _AE_NETLOGON;
//  AE_NETLOGON = _AE_NETLOGON;
//  {$EXTERNALSYM AE_NETLOGON}

  PAeNetLogoff = ^TAeNetLogoff;
  _AE_NETLOGOFF = record
    ae_nf_compname: DWORD;
    ae_nf_username: DWORD;
    ae_nf_reserved1: DWORD;
    ae_nf_reserved2: DWORD;
  end;
  {$EXTERNALSYM _AE_NETLOGOFF}
  TAeNetLogoff = _AE_NETLOGOFF;
//  AE_NETLOGOFF = _AE_NETLOGOFF;
//  {$EXTERNALSYM AE_NETLOGOFF}

  PAeAccLim = ^TAeAccLim;
  _AE_ACCLIM = record
    ae_al_compname: DWORD;
    ae_al_username: DWORD;
    ae_al_resname: DWORD;
    ae_al_limit: DWORD;
  end;
  {$EXTERNALSYM _AE_ACCLIM}
  TAeAccLim = _AE_ACCLIM;
//  AE_ACCLIM = _AE_ACCLIM;
//  {$EXTERNALSYM AE_ACCLIM}

const
  ACTION_LOCKOUT          = 00;
  {$EXTERNALSYM ACTION_LOCKOUT}
  ACTION_ADMINUNLOCK      = 01;
  {$EXTERNALSYM ACTION_ADMINUNLOCK}

type
  PAeLockout = ^TAeLockout;
  _AE_LOCKOUT = record
   ae_lk_compname: DWORD;               // Ptr to computername of client.
   ae_lk_username: DWORD;               // Ptr to username of client (NULL
                                        //  if same as computername).
   ae_lk_action: DWORD;                 // Action taken on account:
                                        // 0 means locked out, 1 means not.
   ae_lk_bad_pw_count: DWORD;           // Bad password count at the time
                                        // of lockout.
  end;
  {$EXTERNALSYM _AE_LOCKOUT}
  TAeLockout = _AE_LOCKOUT;
//  AE_LOCKOUT = _AE_LOCKOUT;
//  {$EXTERNALSYM AE_LOCKOUT}

  PAeGeneric = ^TAeGeneric;
  _AE_GENERIC = record
    ae_ge_msgfile: DWORD;
    ae_ge_msgnum: DWORD;
    ae_ge_params: DWORD;
    ae_ge_param1: DWORD;
    ae_ge_param2: DWORD;
    ae_ge_param3: DWORD;
    ae_ge_param4: DWORD;
    ae_ge_param5: DWORD;
    ae_ge_param6: DWORD;
    ae_ge_param7: DWORD;
    ae_ge_param8: DWORD;
    ae_ge_param9: DWORD;
  end;
  {$EXTERNALSYM _AE_GENERIC}
  TAeGeneric = _AE_GENERIC;
//  AE_GENERIC = _AE_GENERIC;
//  {$EXTERNALSYM AE_GENERIC}

// Special Values and Constants - Audit

// 	Audit entry types (field ae_type in audit_entry).

const
  AE_SRVSTATUS    = 0;
  {$EXTERNALSYM AE_SRVSTATUS}
  AE_SESSLOGON    = 1;
  {$EXTERNALSYM AE_SESSLOGON}
  AE_SESSLOGOFF   = 2;
  {$EXTERNALSYM AE_SESSLOGOFF}
  AE_SESSPWERR    = 3;
  {$EXTERNALSYM AE_SESSPWERR}
  AE_CONNSTART    = 4;
  {$EXTERNALSYM AE_CONNSTART}
  AE_CONNSTOP     = 5;
  {$EXTERNALSYM AE_CONNSTOP}
  AE_CONNREJ      = 6;
  {$EXTERNALSYM AE_CONNREJ}
  AE_RESACCESS    = 7;
  {$EXTERNALSYM AE_RESACCESS}
  AE_RESACCESSREJ = 8;
  {$EXTERNALSYM AE_RESACCESSREJ}
  AE_CLOSEFILE    = 9;
  {$EXTERNALSYM AE_CLOSEFILE}
  AE_SERVICESTAT  = 11;
  {$EXTERNALSYM AE_SERVICESTAT}
  AE_ACLMOD       = 12;
  {$EXTERNALSYM AE_ACLMOD}
  AE_UASMOD       = 13;
  {$EXTERNALSYM AE_UASMOD}
  AE_NETLOGON     = 14;
  {$EXTERNALSYM AE_NETLOGON}
  AE_NETLOGOFF    = 15;
  {$EXTERNALSYM AE_NETLOGOFF}
  AE_NETLOGDENIED = 16;
  {$EXTERNALSYM AE_NETLOGDENIED}
  AE_ACCLIMITEXCD = 17;
  {$EXTERNALSYM AE_ACCLIMITEXCD}
  AE_RESACCESS2   = 18;
  {$EXTERNALSYM AE_RESACCESS2}
  AE_ACLMODFAIL   = 19;
  {$EXTERNALSYM AE_ACLMODFAIL}
  AE_LOCKOUT      = 20;
  {$EXTERNALSYM AE_LOCKOUT}
  AE_GENERIC_TYPE = 21;
  {$EXTERNALSYM AE_GENERIC_TYPE}

//	Values for ae_ss_status field of ae_srvstatus.

  AE_SRVSTART  = 0;
  {$EXTERNALSYM AE_SRVSTART}
  AE_SRVPAUSED = 1;
  {$EXTERNALSYM AE_SRVPAUSED}
  AE_SRVCONT   = 2;
  {$EXTERNALSYM AE_SRVCONT}
  AE_SRVSTOP   = 3;
  {$EXTERNALSYM AE_SRVSTOP}

// 	Values for ae_so_privilege field of ae_sesslogon.

  AE_GUEST = 0;
  {$EXTERNALSYM AE_GUEST}
  AE_USER  = 1;
  {$EXTERNALSYM AE_USER}
  AE_ADMIN = 2;
  {$EXTERNALSYM AE_ADMIN}

//	Values for various ae_XX_reason fields.

  AE_NORMAL        = 0;
  {$EXTERNALSYM AE_NORMAL}
  AE_USERLIMIT     = 0;
  {$EXTERNALSYM AE_USERLIMIT}
  AE_GENERAL       = 0;
  {$EXTERNALSYM AE_GENERAL}
  AE_ERROR         = 1;
  {$EXTERNALSYM AE_ERROR}
  AE_SESSDIS       = 1;
  {$EXTERNALSYM AE_SESSDIS}
  AE_BADPW         = 1;
  {$EXTERNALSYM AE_BADPW}
  AE_AUTODIS       = 2;
  {$EXTERNALSYM AE_AUTODIS}
  AE_UNSHARE       = 2;
  {$EXTERNALSYM AE_UNSHARE}
  AE_ADMINPRIVREQD = 2;
  {$EXTERNALSYM AE_ADMINPRIVREQD}
  AE_ADMINDIS      = 3;
  {$EXTERNALSYM AE_ADMINDIS}
  AE_NOACCESSPERM  = 3;
  {$EXTERNALSYM AE_NOACCESSPERM}
  AE_ACCRESTRICT   = 4;
  {$EXTERNALSYM AE_ACCRESTRICT}

  AE_NORMAL_CLOSE  = 0;
  {$EXTERNALSYM AE_NORMAL_CLOSE}
  AE_SES_CLOSE     = 1;
  {$EXTERNALSYM AE_SES_CLOSE}
  AE_ADMIN_CLOSE   = 2;
  {$EXTERNALSYM AE_ADMIN_CLOSE}

// Values for xx_subreason fields.

  AE_LIM_UNKNOWN     = 0;
  {$EXTERNALSYM AE_LIM_UNKNOWN}
  AE_LIM_LOGONHOURS  = 1;
  {$EXTERNALSYM AE_LIM_LOGONHOURS}
  AE_LIM_EXPIRED     = 2;
  {$EXTERNALSYM AE_LIM_EXPIRED}
  AE_LIM_INVAL_WKSTA = 3;
  {$EXTERNALSYM AE_LIM_INVAL_WKSTA}
  AE_LIM_DISABLED    = 4;
  {$EXTERNALSYM AE_LIM_DISABLED}
  AE_LIM_DELETED     = 5;
  {$EXTERNALSYM AE_LIM_DELETED}

// Values for xx_action fields

  AE_MOD    = 0;
  {$EXTERNALSYM AE_MOD}
  AE_DELETE = 1;
  {$EXTERNALSYM AE_DELETE}
  AE_ADD    = 2;
  {$EXTERNALSYM AE_ADD}

// Types of UAS record for um_rectype field

  AE_UAS_USER   = 0;
  {$EXTERNALSYM AE_UAS_USER}
  AE_UAS_GROUP  = 1;
  {$EXTERNALSYM AE_UAS_GROUP}
  AE_UAS_MODALS = 2;
  {$EXTERNALSYM AE_UAS_MODALS}

// Bitmasks for auditing events
//
// The parentheses around the hex constants broke h_to_inc
// and have been purged from the face of the earth.

  SVAUD_SERVICE       = $1;
  {$EXTERNALSYM SVAUD_SERVICE}
  SVAUD_GOODSESSLOGON = $6;
  {$EXTERNALSYM SVAUD_GOODSESSLOGON}
  SVAUD_BADSESSLOGON  = $18;
  {$EXTERNALSYM SVAUD_BADSESSLOGON}
  SVAUD_SESSLOGON     = (SVAUD_GOODSESSLOGON or SVAUD_BADSESSLOGON);
  {$EXTERNALSYM SVAUD_SESSLOGON}
  SVAUD_GOODNETLOGON  = $60;
  {$EXTERNALSYM SVAUD_GOODNETLOGON}
  SVAUD_BADNETLOGON   = $180;
  {$EXTERNALSYM SVAUD_BADNETLOGON}
  SVAUD_NETLOGON      = (SVAUD_GOODNETLOGON or SVAUD_BADNETLOGON);
  {$EXTERNALSYM SVAUD_NETLOGON}
  SVAUD_LOGON         = (SVAUD_NETLOGON or SVAUD_SESSLOGON);
  {$EXTERNALSYM SVAUD_LOGON}
  SVAUD_GOODUSE       = $600;
  {$EXTERNALSYM SVAUD_GOODUSE}
  SVAUD_BADUSE        = $1800;
  {$EXTERNALSYM SVAUD_BADUSE}
  SVAUD_USE           = (SVAUD_GOODUSE or SVAUD_BADUSE);
  {$EXTERNALSYM SVAUD_USE}
  SVAUD_USERLIST      = $2000;
  {$EXTERNALSYM SVAUD_USERLIST}
  SVAUD_PERMISSIONS   = $4000;
  {$EXTERNALSYM SVAUD_PERMISSIONS}
  SVAUD_RESOURCE      = $8000;
  {$EXTERNALSYM SVAUD_RESOURCE}
  SVAUD_LOGONLIM      = $00010000;
  {$EXTERNALSYM SVAUD_LOGONLIM}

// Resource access audit bitmasks.

  AA_AUDIT_ALL = $0001;
  {$EXTERNALSYM AA_AUDIT_ALL}
  AA_A_OWNER   = $0004;
  {$EXTERNALSYM AA_A_OWNER}
  AA_CLOSE     = $0008;
  {$EXTERNALSYM AA_CLOSE}
  AA_S_OPEN    = $0010;
  {$EXTERNALSYM AA_S_OPEN}
  AA_S_WRITE   = $0020;
  {$EXTERNALSYM AA_S_WRITE}
  AA_S_CREATE  = $0020;
  {$EXTERNALSYM AA_S_CREATE}
  AA_S_DELETE  = $0040;
  {$EXTERNALSYM AA_S_DELETE}
  AA_S_ACL     = $0080;
  {$EXTERNALSYM AA_S_ACL}
  AA_S_ALL     = (AA_S_OPEN or AA_S_WRITE or AA_S_DELETE or AA_S_ACL);
  {$EXTERNALSYM AA_S_ALL}
  AA_F_OPEN    = $0100;
  {$EXTERNALSYM AA_F_OPEN}
  AA_F_WRITE   = $0200;
  {$EXTERNALSYM AA_F_WRITE}
  AA_F_CREATE  = $0200;
  {$EXTERNALSYM AA_F_CREATE}
  AA_F_DELETE  = $0400;
  {$EXTERNALSYM AA_F_DELETE}
  AA_F_ACL     = $0800;
  {$EXTERNALSYM AA_F_ACL}
  AA_F_ALL     = (AA_F_OPEN or AA_F_WRITE or AA_F_DELETE or AA_F_ACL);
  {$EXTERNALSYM AA_F_ALL}

// Pinball-specific

  AA_A_OPEN    = $1000;
  {$EXTERNALSYM AA_A_OPEN}
  AA_A_WRITE   = $2000;
  {$EXTERNALSYM AA_A_WRITE}
  AA_A_CREATE  = $2000;
  {$EXTERNALSYM AA_A_CREATE}
  AA_A_DELETE  = $4000;
  {$EXTERNALSYM AA_A_DELETE}
  AA_A_ACL     = $8000;
  {$EXTERNALSYM AA_A_ACL}
  AA_A_ALL     = (AA_F_OPEN or AA_F_WRITE or AA_F_DELETE or AA_F_ACL);
  {$EXTERNALSYM AA_A_ALL}

// Translated from LMJOIN.H

// Types of name that can be validated

type
  PNetSetupNameType = ^TNetSetupNameType;
  _NETSETUP_NAME_TYPE = DWORD;
  {$EXTERNALSYM _NETSETUP_NAME_TYPE}
  TNetSetupNameType = _NETSETUP_NAME_TYPE;
  NETSETUP_NAME_TYPE = _NETSETUP_NAME_TYPE;
  {$EXTERNALSYM NETSETUP_NAME_TYPE}

const
  NetSetupUnknown = 0;
  NetSetupMachine = 1;
  NetSetupWorkgroup = 2;
  NetSetupDomain = 3;
  NetSetupNonExistentDomain = 4;
  NetSetupDnsMachine = 5;

// Status of a workstation

type
  PNetSetupJoinStatus = ^TNetSetupJoinStatus;
  _NETSETUP_JOIN_STATUS = DWORD;
  {$EXTERNALSYM _NETSETUP_JOIN_STATUS}
  TNetSetupJoinStatus = _NETSETUP_JOIN_STATUS;
  NETSETUP_JOIN_STATUS = _NETSETUP_JOIN_STATUS;
  {$EXTERNALSYM NETSETUP_JOIN_STATUS}

const
  NetSetupUnknownStatus = 0;
  NetSetupUnjoined = 1;
  NetSetupWorkgroupName = 2;
  NetSetupDomainName = 3;

// Flags to determine the behavior of the join/unjoin APIs

  NETSETUP_JOIN_DOMAIN    = $00000001;      // If not present, workgroup is joined
  {$EXTERNALSYM NETSETUP_JOIN_DOMAIN}
  NETSETUP_ACCT_CREATE    = $00000002;      // Do the server side account creation/rename
  {$EXTERNALSYM NETSETUP_ACCT_CREATE}
  NETSETUP_ACCT_DELETE    = $00000004;      // Delete the account when a domain is left
  {$EXTERNALSYM NETSETUP_ACCT_DELETE}
  NETSETUP_WIN9X_UPGRADE  = $00000010;      // Invoked during upgrade of Windows 9x to
                                            // Windows NT
  {$EXTERNALSYM NETSETUP_WIN9X_UPGRADE}
  NETSETUP_DOMAIN_JOIN_IF_JOINED  = $00000020;  // Allow the client to join a new domain
                                                // even if it is already joined to a domain
  {$EXTERNALSYM NETSETUP_DOMAIN_JOIN_IF_JOINED}
  NETSETUP_JOIN_UNSECURE  = $00000040;      // Performs an unsecure join
  {$EXTERNALSYM NETSETUP_JOIN_UNSECURE}

  NETSETUP_INSTALL_INVOCATION = $00040000;  // The APIs were invoked during install
  {$EXTERNALSYM NETSETUP_INSTALL_INVOCATION}

// 0x80000000 is reserved for internal use only

// Joins a machine to the domain.

function NetJoinDomain(lpServer, lpDomain, lpAccountOU, lpAccount,
  lpPassword: LPCWSTR; fJoinOptions: DWORD): NET_API_STATUS; stdcall;
{$EXTERNALSYM NetJoinDomain}

function NetUnjoinDomain(lpServer, lpAccount, lpPassword: LPCWSTR;
  fUnjoinOptions: DWORD): NET_API_STATUS; stdcall;
{$EXTERNALSYM NetUnjoinDomain}

function NetRenameMachineInDomain(lpServer, lpNewMachineName, lpAccount,
  lpPassword: LPCWSTR; fRenameOptions: DWORD): NET_API_STATUS; stdcall;
{$EXTERNALSYM NetRenameMachineInDomain}

// Determine the validity of a name

function NetValidateName(lpServer, lpName, lpAccount, lpPassword: LPCWSTR;
  NameType: TNetSetupNameType): NET_API_STATUS; stdcall;
{$EXTERNALSYM NetValidateName}

// Determines whether a workstation is joined to a domain or not

function NetGetJoinInformation(lpServer: LPCWSTR; lpNameBuffer: LPWSTR;
  var BufferType: TNetSetupNameType): NET_API_STATUS; stdcall;
{$EXTERNALSYM NetGetJoinInformation}

// Determines the list of OUs that the client can create a machine account in

function NetGetJoinableOUs(lpServer, lpDomain, lpAccount, lpPassword: LPCWSTR;
  var OUCount: DWORD; OUs: Pointer): NET_API_STATUS; stdcall;
{$EXTERNALSYM NetGetJoinableOUs}

// Translated from LMERRLOG.H

// Data Structures - Config

type
  PErrorLog = ^TErrorLog;
  _ERROR_LOG = record
    el_len: DWORD;
    el_reserved: DWORD;
    el_time: DWORD;
    el_error: DWORD;
    el_name: LPWSTR;                    // pointer to service name
    el_text: LPWSTR;                    // pointer to string array
    el_data: Pointer;                   // pointer to BYTE array
    el_data_size: DWORD;                // byte count of el_data area
    el_nstrings: DWORD;                 // number of strings in el_text.
  end;
  {$EXTERNALSYM _ERROR_LOG}
  TErrorLog = _ERROR_LOG;
  ERROR_LOG = _ERROR_LOG;
  {$EXTERNALSYM ERROR_LOG}

// Function Prototypes - ErrorLog

function NetErrorLogClear(server: LPCWSTR; backupfile: LPCWSTR;
  reserved: Pointer): NET_API_STATUS; stdcall;
{$EXTERNALSYM NetErrorLogClear}

function NetErrorLogRead(server: LPCWSTR; reserved1: LPWSTR; errloghandle: PHLog;
  offset: DWORD;  reserved2: PDWORD; reserved3: DWORD; offsetflag: DWORD;
  bufptr: Pointer; prefmaxlen: DWORD; var bytesread: DWORD;
  var totalbytes: DWORD): NET_API_STATUS; stdcall;
{$EXTERNALSYM NetErrorLogRead}

function NetErrorLogWrite(reserved1: Pointer; code: DWORD; component: LPCWSTR;
  buffer: Pointer; numbytes: DWORD; msgbuf: Pointer; strcount: DWORD;
  reserved2: Pointer): NET_API_STATUS; stdcall;
{$EXTERNALSYM NetErrorLogWrite}

// Special Values and Constants

//  Generic (could be used by more than one service)
//  error log messages from 0 to 25
//
// Do not change the comments following the manifest constants without
// understanding how mapmsg works.

const
  ERRLOG_BASE = 3100;        //* NELOG errors start here */
  {$EXTERNALSYM ERRLOG_BASE}


  NELOG_Internal_Error        = (ERRLOG_BASE + 0);
  {$EXTERNALSYM NELOG_Internal_Error}
  // The operation failed because a network software error occurred.

  NELOG_Resource_Shortage     = (ERRLOG_BASE + 1);
  {$EXTERNALSYM NELOG_Resource_Shortage}
  // The system ran out of a resource controlled by the %1 option.

  NELOG_Unable_To_Lock_Segment    = (ERRLOG_BASE + 2);
  {$EXTERNALSYM NELOG_Unable_To_Lock_Segment}
  // The service failed to obtain a long-term lock on the
  // segment for network control blocks (NCBs). The error code is the data.

  NELOG_Unable_To_Unlock_Segment  = (ERRLOG_BASE + 3);
  {$EXTERNALSYM NELOG_Unable_To_Unlock_Segment}
  // The service failed to release the long-term lock on the
  // segment for network control blocks (NCBs). The error code is the data.

  NELOG_Uninstall_Service     = (ERRLOG_BASE + 4);
  {$EXTERNALSYM NELOG_Uninstall_Service}
  // There was an error stopping service %1.
  // The error code from NetServiceControl is the data.

  NELOG_Init_Exec_Fail        = (ERRLOG_BASE + 5);
  {$EXTERNALSYM NELOG_Init_Exec_Fail}
  // Initialization failed because of a system execution failure on
  // path %1. The system error code is the data.

  NELOG_Ncb_Error         = (ERRLOG_BASE + 6);
  {$EXTERNALSYM NELOG_Ncb_Error}
  // An unexpected network control block (NCB) was received. The NCB is the data.

  NELOG_Net_Not_Started       = (ERRLOG_BASE + 7);
  {$EXTERNALSYM NELOG_Net_Not_Started}
  // The network is not started.

  NELOG_Ioctl_Error       = (ERRLOG_BASE + 8);
  {$EXTERNALSYM NELOG_Ioctl_Error}
  // A DosDevIoctl or DosFsCtl to NETWKSTA.SYS failed.
  // The data shown is in this format:
  //     DWORD  approx CS:IP of call to ioctl or fsctl
  //     WORD   error code
  //     WORD   ioctl or fsctl number

  NELOG_System_Semaphore      = (ERRLOG_BASE + 9);
  {$EXTERNALSYM NELOG_System_Semaphore}
  // Unable to create or open system semaphore %1.
  // The error code is the data.

  NELOG_Init_OpenCreate_Err   = (ERRLOG_BASE + 10);
  {$EXTERNALSYM NELOG_Init_OpenCreate_Err}
  // Initialization failed because of an open/create error on the
  // file %1. The system error code is the data.

  NELOG_NetBios           = (ERRLOG_BASE + 11);
  {$EXTERNALSYM NELOG_NetBios}
  // An unexpected NetBIOS error occurred.
  // The error code is the data.

  NELOG_SMB_Illegal       = (ERRLOG_BASE + 12);
  {$EXTERNALSYM NELOG_SMB_Illegal}
  // An illegal server message block (SMB) was received.
  // The SMB is the data.

  NELOG_Service_Fail      = (ERRLOG_BASE + 13);
  {$EXTERNALSYM NELOG_Service_Fail}
  // Initialization failed because the requested service %1
  // could not be started.

  NELOG_Entries_Lost      = (ERRLOG_BASE + 14);
  {$EXTERNALSYM NELOG_Entries_Lost}
  // Some entries in the error log were lost because of a buffer
  // overflow.

//  Server specific error log messages from 20 to 40

  NELOG_Init_Seg_Overflow     = (ERRLOG_BASE + 20);
  {$EXTERNALSYM NELOG_Init_Seg_Overflow}
  // Initialization parameters controlling resource usage other
  // than net buffers are sized so that too much memory is needed.

  NELOG_Srv_No_Mem_Grow       = (ERRLOG_BASE + 21);
  {$EXTERNALSYM NELOG_Srv_No_Mem_Grow}
  // The server cannot increase the size of a memory segment.

  NELOG_Access_File_Bad       = (ERRLOG_BASE + 22);
  {$EXTERNALSYM NELOG_Access_File_Bad}
  // Initialization failed because account file %1 is either incorrect
  // or not present.

  NELOG_Srvnet_Not_Started    = (ERRLOG_BASE + 23);
  {$EXTERNALSYM NELOG_Srvnet_Not_Started}
  // Initialization failed because network %1 was not started.

  NELOG_Init_Chardev_Err      = (ERRLOG_BASE + 24);
  {$EXTERNALSYM NELOG_Init_Chardev_Err}
  // The server failed to start. Either all three chdev
  //  parameters must be zero or all three must be nonzero.

  NELOG_Remote_API        = (ERRLOG_BASE + 25);
  {$EXTERNALSYM NELOG_Remote_API}
  // A remote API request was halted due to the following
  // invalid description string: %1.

  NELOG_Ncb_TooManyErr        = (ERRLOG_BASE + 26);
  {$EXTERNALSYM NELOG_Ncb_TooManyErr}
  // The network %1 ran out of network control blocks (NCBs).  You may need to increase NCBs
  // for this network.  The following information includes the
  // number of NCBs submitted by the server when this error occurred:

  NELOG_Mailslot_err      = (ERRLOG_BASE + 27);
  {$EXTERNALSYM NELOG_Mailslot_err}
  // The server cannot create the %1 mailslot needed to send
  // the ReleaseMemory alert message.  The error received is:

  NELOG_ReleaseMem_Alert      = (ERRLOG_BASE + 28);
  {$EXTERNALSYM NELOG_ReleaseMem_Alert}
  // The server failed to register for the ReleaseMemory alert,
  // with recipient %1. The error code from
  // NetAlertStart is the data.

  NELOG_AT_cannot_write       = (ERRLOG_BASE + 29);
  {$EXTERNALSYM NELOG_AT_cannot_write}
  // The server cannot update the AT schedule file. The file
  // is corrupted.

  NELOG_Cant_Make_Msg_File    = (ERRLOG_BASE + 30);
  {$EXTERNALSYM NELOG_Cant_Make_Msg_File}
  // The server encountered an error when calling
  // NetIMakeLMFileName. The error code is the data.

  NELOG_Exec_Netservr_NoMem   = (ERRLOG_BASE + 31);
  {$EXTERNALSYM NELOG_Exec_Netservr_NoMem}
  // Initialization failed because of a system execution failure on
  // path %1. There is not enough memory to start the process.
  // The system error code is the data.

  NELOG_Server_Lock_Failure   = (ERRLOG_BASE + 32);
  {$EXTERNALSYM NELOG_Server_Lock_Failure}
  // Longterm lock of the server buffers failed.
  // Check swap disk's free space and restart the system to start the server.

//  Message service and POPUP specific error log messages from 40 to 55

  NELOG_Msg_Shutdown      = (ERRLOG_BASE + 40);
  {$EXTERNALSYM NELOG_Msg_Shutdown}
  // The service has stopped due to repeated consecutive
  //  occurrences of a network control block (NCB) error.  The last bad NCB follows
  //  in raw data.

  NELOG_Msg_Sem_Shutdown      = (ERRLOG_BASE + 41);
  {$EXTERNALSYM NELOG_Msg_Sem_Shutdown}
  // The Message server has stopped due to a lock on the
  //  Message server shared data segment.

  NELOG_Msg_Log_Err       = (ERRLOG_BASE + 50);
  {$EXTERNALSYM NELOG_Msg_Log_Err}
  // A file system error occurred while opening or writing to the
  //  system message log file %1. Message logging has been
  //  switched off due to the error. The error code is the data.

  NELOG_VIO_POPUP_ERR     = (ERRLOG_BASE + 51);
  {$EXTERNALSYM NELOG_VIO_POPUP_ERR}
  // Unable to display message POPUP due to system VIO call error.
  //  The error code is the data.

  NELOG_Msg_Unexpected_SMB_Type   = (ERRLOG_BASE + 52);
  {$EXTERNALSYM NELOG_Msg_Unexpected_SMB_Type}
  // An illegal server message block (SMB) was received.  The SMB is the data.

//  Workstation specific error log messages from 60 to 75

  NELOG_Wksta_Infoseg     = (ERRLOG_BASE + 60);
  {$EXTERNALSYM NELOG_Wksta_Infoseg}
  // The workstation information segment is bigger than 64K.
  // The size follows, in DWORD format:

  NELOG_Wksta_Compname        = (ERRLOG_BASE + 61);
  {$EXTERNALSYM NELOG_Wksta_Compname}
  // The workstation was unable to get the name-number of the computer.

  NELOG_Wksta_BiosThreadFailure   = (ERRLOG_BASE + 62);
  {$EXTERNALSYM NELOG_Wksta_BiosThreadFailure}
  // The workstation could not initialize the Async NetBIOS Thread.
  // The error code is the data.

  NELOG_Wksta_IniSeg      = (ERRLOG_BASE + 63);
  {$EXTERNALSYM NELOG_Wksta_IniSeg}
  // The workstation could not open the initial shared segment.
  // The error code is the data.

  NELOG_Wksta_HostTab_Full    = (ERRLOG_BASE + 64);
  {$EXTERNALSYM NELOG_Wksta_HostTab_Full}
  // The workstation host table is full.

  NELOG_Wksta_Bad_Mailslot_SMB    = (ERRLOG_BASE + 65);
  {$EXTERNALSYM NELOG_Wksta_Bad_Mailslot_SMB}
  // A bad mailslot server message block (SMB) was received.  The SMB is the data.

  NELOG_Wksta_UASInit     = (ERRLOG_BASE + 66);
  {$EXTERNALSYM NELOG_Wksta_UASInit}
  // The workstation encountered an error while trying to start the user accounts database.
  //  The error code is the data.

  NELOG_Wksta_SSIRelogon      = (ERRLOG_BASE + 67);
  {$EXTERNALSYM NELOG_Wksta_SSIRelogon}
  // The workstation encountered an error while responding to an SSI revalidation request.
  //  The function code and the error codes are the data.

//  Alerter service specific error log messages from 70 to 79

  NELOG_Build_Name        = (ERRLOG_BASE + 70);
  {$EXTERNALSYM NELOG_Build_Name}
  // The Alerter service had a problem creating the list of
  // alert recipients.  The error code is %1.

  NELOG_Name_Expansion        = (ERRLOG_BASE + 71);
  {$EXTERNALSYM NELOG_Name_Expansion}
  // There was an error expanding %1 as a group name. Try
  // splitting the group into two or more smaller groups.

  NELOG_Message_Send      = (ERRLOG_BASE + 72);
  {$EXTERNALSYM NELOG_Message_Send}
  // There was an error sending %2 the alert message -
  //  (
  //  %3 )
  //  The error code is %1.

  NELOG_Mail_Slt_Err      = (ERRLOG_BASE + 73);
  {$EXTERNALSYM NELOG_Mail_Slt_Err}
  // There was an error in creating or reading the alerter mailslot.
  //  The error code is %1.

  NELOG_AT_cannot_read        = (ERRLOG_BASE + 74);
  {$EXTERNALSYM NELOG_AT_cannot_read}
  // The server could not read the AT schedule file.

  NELOG_AT_sched_err      = (ERRLOG_BASE + 75);
  {$EXTERNALSYM NELOG_AT_sched_err}
  // The server found an invalid AT schedule record.

  NELOG_AT_schedule_file_created  = (ERRLOG_BASE + 76);
  {$EXTERNALSYM NELOG_AT_schedule_file_created}
  // The server could not find an AT schedule file so it created one.

  NELOG_Srvnet_NB_Open        = (ERRLOG_BASE + 77);
  {$EXTERNALSYM NELOG_Srvnet_NB_Open}
  // The server could not access the %1 network with NetBiosOpen.

  NELOG_AT_Exec_Err       = (ERRLOG_BASE + 78);
  {$EXTERNALSYM NELOG_AT_Exec_Err}
  // The AT command processor could not run %1.

// Cache Lazy Write and HPFS386 specific error log messages from 80 to 89

  NELOG_Lazy_Write_Err            = (ERRLOG_BASE + 80);
  {$EXTERNALSYM NELOG_Lazy_Write_Err}
  // * WARNING:  Because of a lazy-write error, drive %1 now
  // *  contains some corrupted data.  The cache is stopped.

  NELOG_HotFix            = (ERRLOG_BASE + 81);
  {$EXTERNALSYM NELOG_HotFix}
  // A defective sector on drive %1 has been replaced (hotfixed).
  // No data was lost.  You should run CHKDSK soon to restore full
  // performance and replenish the volume's spare sector pool.
  //
  // The hotfix occurred while processing a remote request.

  NELOG_HardErr_From_Server   = (ERRLOG_BASE + 82);
  {$EXTERNALSYM NELOG_HardErr_From_Server}
  // A disk error occurred on the HPFS volume in drive %1.
  // The error occurred while processing a remote request.

  NELOG_LocalSecFail1 = (ERRLOG_BASE + 83);
  {$EXTERNALSYM NELOG_LocalSecFail1}
  // The user accounts database (NET.ACC) is corrupted.  The local security
  // system is replacing the corrupted NET.ACC with the backup
  // made at %1.
  // Any updates made to the database after this time are lost.

  NELOG_LocalSecFail2 = (ERRLOG_BASE + 84);
  {$EXTERNALSYM NELOG_LocalSecFail2}
  // The user accounts database (NET.ACC) is missing.  The local
  // security system is restoring the backup database
  // made at %1.
  // Any updates made to the database made after this time are lost.

  NELOG_LocalSecFail3 = (ERRLOG_BASE + 85);
  {$EXTERNALSYM NELOG_LocalSecFail3}
  // Local security could not be started because the user accounts database
  // (NET.ACC) was missing or corrupted, and no usable backup
  // database was present.
  //
  // THE SYSTEM IS NOT SECURE.

  NELOG_LocalSecGeneralFail   = (ERRLOG_BASE + 86);
  {$EXTERNALSYM NELOG_LocalSecGeneralFail}
  // Local security could not be started because an error
  // occurred during initialization. The error code returned is %1.
  //
  // THE SYSTEM IS NOT SECURE.

// NETWKSTA.SYS specific error log messages from 90 to 99

  NELOG_NetWkSta_Internal_Error   = (ERRLOG_BASE + 90);
  {$EXTERNALSYM NELOG_NetWkSta_Internal_Error}
  // A NetWksta internal error has occurred: %1

  NELOG_NetWkSta_No_Resource  = (ERRLOG_BASE + 91);
  {$EXTERNALSYM NELOG_NetWkSta_No_Resource}
  // The redirector is out of a resource: %1.

  NELOG_NetWkSta_SMB_Err      = (ERRLOG_BASE + 92);
  {$EXTERNALSYM NELOG_NetWkSta_SMB_Err}
  // A server message block (SMB) error occurred on the connection to %1.
  // The SMB header is the data.

  NELOG_NetWkSta_VC_Err       = (ERRLOG_BASE + 93);
  {$EXTERNALSYM NELOG_NetWkSta_VC_Err}
  // A virtual circuit error occurred on the session to %1.
  //  The network control block (NCB) command and return code is the data.

  NELOG_NetWkSta_Stuck_VC_Err = (ERRLOG_BASE + 94);
  {$EXTERNALSYM NELOG_NetWkSta_Stuck_VC_Err}
  // Hanging up a stuck session to %1.

  NELOG_NetWkSta_NCB_Err      = (ERRLOG_BASE + 95);
  {$EXTERNALSYM NELOG_NetWkSta_NCB_Err}
  // A network control block (NCB) error occurred (%1).
  // The NCB is the data.

  NELOG_NetWkSta_Write_Behind_Err = (ERRLOG_BASE + 96);
  {$EXTERNALSYM NELOG_NetWkSta_Write_Behind_Err}
  // A write operation to %1 failed.
  // Data may have been lost.

  NELOG_NetWkSta_Reset_Err    = (ERRLOG_BASE + 97);
  {$EXTERNALSYM NELOG_NetWkSta_Reset_Err}
  // Reset of driver %1 failed to complete the network control block (NCB).
  //  The NCB is the data.

  NELOG_NetWkSta_Too_Many     = (ERRLOG_BASE + 98);
  {$EXTERNALSYM NELOG_NetWkSta_Too_Many}
  // The amount of resource %1 requested was more
  // than the maximum. The maximum amount was allocated.

// Spooler specific error log messages from 100 to 103

  NELOG_Srv_Thread_Failure        = (ERRLOG_BASE + 104);
  {$EXTERNALSYM NELOG_Srv_Thread_Failure}
  // The server could not create a thread.
  // The THREADS parameter in the CONFIG.SYS file should be increased.

  NELOG_Srv_Close_Failure         = (ERRLOG_BASE + 105);
  {$EXTERNALSYM NELOG_Srv_Close_Failure}
  // The server could not close %1.
  // The file is probably corrupted.

  NELOG_ReplUserCurDir               = (ERRLOG_BASE + 106);
  {$EXTERNALSYM NELOG_ReplUserCurDir}
  // The replicator cannot update directory %1. It has tree integrity
  // and is the current directory for some process.

  NELOG_ReplCannotMasterDir       = (ERRLOG_BASE + 107);
  {$EXTERNALSYM NELOG_ReplCannotMasterDir}
  // The server cannot export directory %1 to client %2.
  // It is exported from another server.

  NELOG_ReplUpdateError           = (ERRLOG_BASE + 108);
  {$EXTERNALSYM NELOG_ReplUpdateError}
  // The replication server could not update directory %2 from the source
  // on %3 due to error %1.

  NELOG_ReplLostMaster            = (ERRLOG_BASE + 109);
  {$EXTERNALSYM NELOG_ReplLostMaster}
  // Master %1 did not send an update notice for directory %2 at the expected
  // time.

  NELOG_NetlogonAuthDCFail        = (ERRLOG_BASE + 110);
  {$EXTERNALSYM NELOG_NetlogonAuthDCFail}
  // Failed to authenticate with %2, a Windows NT domain controller for domain %1.

  NELOG_ReplLogonFailed           = (ERRLOG_BASE + 111);
  {$EXTERNALSYM NELOG_ReplLogonFailed}
  // The replicator attempted to log on at %2 as %1 and failed.

  NELOG_ReplNetErr            = (ERRLOG_BASE + 112);
  {$EXTERNALSYM NELOG_ReplNetErr}
  // Network error %1 occurred.

  NELOG_ReplMaxFiles            = (ERRLOG_BASE + 113);
  {$EXTERNALSYM NELOG_ReplMaxFiles}
  // Replicator limit for files in a directory has been exceeded.

  NELOG_ReplMaxTreeDepth            = (ERRLOG_BASE + 114);
  {$EXTERNALSYM NELOG_ReplMaxTreeDepth}
  // Replicator limit for tree depth has been exceeded.

  NELOG_ReplBadMsg             = (ERRLOG_BASE + 115);
  {$EXTERNALSYM NELOG_ReplBadMsg}
  // Unrecognized message received in mailslot.

  NELOG_ReplSysErr            = (ERRLOG_BASE + 116);
  {$EXTERNALSYM NELOG_ReplSysErr}
  // System error %1 occurred.

  NELOG_ReplUserLoged          = (ERRLOG_BASE + 117);
  {$EXTERNALSYM NELOG_ReplUserLoged}
  // Cannot log on. User is currently logged on and argument TRYUSER
  // is set to NO.

  NELOG_ReplBadImport           = (ERRLOG_BASE + 118);
  {$EXTERNALSYM NELOG_ReplBadImport}
  // IMPORT path %1 cannot be found.

  NELOG_ReplBadExport           = (ERRLOG_BASE + 119);
  {$EXTERNALSYM NELOG_ReplBadExport}
  // EXPORT path %1 cannot be found.

  NELOG_ReplSignalFileErr           = (ERRLOG_BASE + 120);
  {$EXTERNALSYM NELOG_ReplSignalFileErr}
  // Replicator failed to update signal file in directory %2 due to
  // %1 system error.

  NELOG_DiskFT                = (ERRLOG_BASE+121);
  {$EXTERNALSYM NELOG_DiskFT}
  // Disk Fault Tolerance Error
  //
  // %1

  NELOG_ReplAccessDenied           = (ERRLOG_BASE + 122);
  {$EXTERNALSYM NELOG_ReplAccessDenied}
  // Replicator could not access %2
  // on %3 due to system error %1.

  NELOG_NetlogonFailedPrimary      = (ERRLOG_BASE + 123);
  {$EXTERNALSYM NELOG_NetlogonFailedPrimary}
   {*
    *The primary domain controller for domain %1 has apparently failed.
    *}

  NELOG_NetlogonPasswdSetFailed = (ERRLOG_BASE + 124);
  {$EXTERNALSYM NELOG_NetlogonPasswdSetFailed}
  // Changing machine account password for account %1 failed with
  // the following error: %n%2

  NELOG_NetlogonTrackingError      = (ERRLOG_BASE + 125);
  {$EXTERNALSYM NELOG_NetlogonTrackingError}
  // An error occurred while updating the logon or logoff information for %1.

  NELOG_NetlogonSyncError          = (ERRLOG_BASE + 126);
  {$EXTERNALSYM NELOG_NetlogonSyncError}
  // An error occurred while synchronizing with primary domain controller %1

  NELOG_NetlogonRequireSignOrSealError = (ERRLOG_BASE + 127);
  {$EXTERNALSYM NELOG_NetlogonRequireSignOrSealError}
  // The session setup to the Windows NT Domain Controller %1 for the domain %2
  // failed because %1 does not support signing or sealing the Netlogon
  // session.
  //
  // Either upgrade the Domain controller or set the RequireSignOrSeal
  // registry entry on this machine to 0.

//  UPS service specific error log messages from 130 to 135

  NELOG_UPS_PowerOut      = (ERRLOG_BASE + 130);
  {$EXTERNALSYM NELOG_UPS_PowerOut}
  // A power failure was detected at the server.

  NELOG_UPS_Shutdown      = (ERRLOG_BASE + 131);
  {$EXTERNALSYM NELOG_UPS_Shutdown}
  // The UPS service performed server shut down.

  NELOG_UPS_CmdFileError      = (ERRLOG_BASE + 132);
  {$EXTERNALSYM NELOG_UPS_CmdFileError}
  // The UPS service did not complete execution of the
  // user specified shut down command file.

  NELOG_UPS_CannotOpenDriver  = (ERRLOG_BASE+133);
  {$EXTERNALSYM NELOG_UPS_CannotOpenDriver}
  // The UPS driver could not be opened.  The error code is
  // the data.

  NELOG_UPS_PowerBack     = (ERRLOG_BASE + 134);
  {$EXTERNALSYM NELOG_UPS_PowerBack}
  // Power has been restored.

  NELOG_UPS_CmdFileConfig     = (ERRLOG_BASE + 135);
  {$EXTERNALSYM NELOG_UPS_CmdFileConfig}
  // There is a problem with a configuration of user specified
  // shut down command file.

  NELOG_UPS_CmdFileExec       = (ERRLOG_BASE + 136);
  {$EXTERNALSYM NELOG_UPS_CmdFileExec}
  // The UPS service failed to execute a user specified shutdown
  // command file %1.  The error code is the data.

// Remoteboot server specific error log messages are from 150 to 157

  NELOG_Missing_Parameter     = (ERRLOG_BASE + 150);
  {$EXTERNALSYM NELOG_Missing_Parameter}
  // Initialization failed because of an invalid or missing
  // parameter in the configuration file %1.

  NELOG_Invalid_Config_Line   = (ERRLOG_BASE + 151);
  {$EXTERNALSYM NELOG_Invalid_Config_Line}
  // Initialization failed because of an invalid line in the
  // configuration file %1. The invalid line is the data.

  NELOG_Invalid_Config_File   = (ERRLOG_BASE + 152);
  {$EXTERNALSYM NELOG_Invalid_Config_File}
  // Initialization failed because of an error in the configuration
  // file %1.

  NELOG_File_Changed      = (ERRLOG_BASE + 153);
  {$EXTERNALSYM NELOG_File_Changed}
  // The file %1 has been changed after initialization.
  // The boot-block loading was temporarily terminated.

  NELOG_Files_Dont_Fit        = (ERRLOG_BASE + 154);
  {$EXTERNALSYM NELOG_Files_Dont_Fit}
  // The files do not fit to the boot-block configuration
  // file %1. Change the BASE and ORG definitions or the order
  // of the files.

  NELOG_Wrong_DLL_Version     = (ERRLOG_BASE + 155);
  {$EXTERNALSYM NELOG_Wrong_DLL_Version}
  // Initialization failed because the dynamic-link
  // library %1 returned an incorrect version number.

  NELOG_Error_in_DLL      = (ERRLOG_BASE + 156);
  {$EXTERNALSYM NELOG_Error_in_DLL}
  // There was an unrecoverable error in the dynamic- link library of the
  // service.

  NELOG_System_Error      = (ERRLOG_BASE + 157);
  {$EXTERNALSYM NELOG_System_Error}
  // The system returned an unexpected error code.
  // The error code is the data.

  NELOG_FT_ErrLog_Too_Large = (ERRLOG_BASE + 158);
  {$EXTERNALSYM NELOG_FT_ErrLog_Too_Large}
  // The fault-tolerance error log file, LANROOT\LOGS\FT.LOG, is more than 64K.

  NELOG_FT_Update_In_Progress = (ERRLOG_BASE + 159);
  {$EXTERNALSYM NELOG_FT_Update_In_Progress}
  // The fault-tolerance error-log file, LANROOT\LOGS\FT.LOG, had the
  // update in progress bit set upon opening, which means that the
  // system crashed while working on the error log.


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

  NELOG_OEM_Code              = (ERRLOG_BASE + 199);
  {$EXTERNALSYM NELOG_OEM_Code}
  // %1 %2 %3 %4 %5 %6 %7 %8 %9.

// another error log range defined for NT Lanman.

  ERRLOG2_BASE=  5700;       // New NT NELOG errors start here
  {$EXTERNALSYM ERRLOG2_BASE}

  NELOG_NetlogonSSIInitError              = (ERRLOG2_BASE + 0);
  {$EXTERNALSYM NELOG_NetlogonSSIInitError}
  // The Netlogon service could not initialize the replication data
  // structures successfully. The service was terminated.  The following
  // error occurred: %n%1

  NELOG_NetlogonFailedToUpdateTrustList   = (ERRLOG2_BASE + 1);
  {$EXTERNALSYM NELOG_NetlogonFailedToUpdateTrustList}
  // The Netlogon service failed to update the domain trust list.  The
  // following error occurred: %n%1

  NELOG_NetlogonFailedToAddRpcInterface   = (ERRLOG2_BASE + 2);
  {$EXTERNALSYM NELOG_NetlogonFailedToAddRpcInterface}
  // The Netlogon service could not add the RPC interface.  The
  // service was terminated. The following error occurred: %n%1

  NELOG_NetlogonFailedToReadMailslot      = (ERRLOG2_BASE + 3);
  {$EXTERNALSYM NELOG_NetlogonFailedToReadMailslot}
  // The Netlogon service could not read a mailslot message from %1 due
  // to the following error: %n%2

  NELOG_NetlogonFailedToRegisterSC        = (ERRLOG2_BASE + 4);
  {$EXTERNALSYM NELOG_NetlogonFailedToRegisterSC}
  // The Netlogon service failed to register the service with the
  // service controller. The service was terminated. The following
  // error occurred: %n%1

  NELOG_NetlogonChangeLogCorrupt          = (ERRLOG2_BASE + 5);
  {$EXTERNALSYM NELOG_NetlogonChangeLogCorrupt}
  // The change log cache maintained by the Netlogon service for
  // database changes is corrupted. The Netlogon service is resetting
  // the change log.

  NELOG_NetlogonFailedToCreateShare       = (ERRLOG2_BASE + 6);
  {$EXTERNALSYM NELOG_NetlogonFailedToCreateShare}
  // The Netlogon service could not create server share %1.  The following
  // error occurred: %n%2

  NELOG_NetlogonDownLevelLogonFailed      = (ERRLOG2_BASE + 7);
  {$EXTERNALSYM NELOG_NetlogonDownLevelLogonFailed}
  // The down-level logon request for the user %1 from %2 failed.

  NELOG_NetlogonDownLevelLogoffFailed     = (ERRLOG2_BASE + 8);
  {$EXTERNALSYM NELOG_NetlogonDownLevelLogoffFailed}
  // The down-level logoff request for the user %1 from %2 failed.

  NELOG_NetlogonNTLogonFailed             = (ERRLOG2_BASE + 9);
  {$EXTERNALSYM NELOG_NetlogonNTLogonFailed}
  // The Windows NT %1 logon request for the user %2\%3 from %4 (via %5)
  // failed.

  NELOG_NetlogonNTLogoffFailed            = (ERRLOG2_BASE + 10);
  {$EXTERNALSYM NELOG_NetlogonNTLogoffFailed}
  // The Windows NT %1 logoff request for the user %2\%3 from %4
  // failed.

  NELOG_NetlogonPartialSyncCallSuccess    = (ERRLOG2_BASE + 11);
  {$EXTERNALSYM NELOG_NetlogonPartialSyncCallSuccess}
  // The partial synchronization request from the server %1 completed
  // successfully. %2 changes(s) has(have) been returned to the caller.

  NELOG_NetlogonPartialSyncCallFailed     = (ERRLOG2_BASE + 12);
  {$EXTERNALSYM NELOG_NetlogonPartialSyncCallFailed}
  // The partial synchronization request from the server %1 failed with
  // the following error: %n%2

  NELOG_NetlogonFullSyncCallSuccess       = (ERRLOG2_BASE + 13);
  {$EXTERNALSYM NELOG_NetlogonFullSyncCallSuccess}
  // The full synchronization request from the server %1 completed
  // successfully. %2 object(s) has(have) been returned to the caller.

  NELOG_NetlogonFullSyncCallFailed        = (ERRLOG2_BASE + 14);
  {$EXTERNALSYM NELOG_NetlogonFullSyncCallFailed}
  // The full synchronization request from the server %1 failed with
  // the following error: %n%2

  NELOG_NetlogonPartialSyncSuccess        = (ERRLOG2_BASE + 15);
  {$EXTERNALSYM NELOG_NetlogonPartialSyncSuccess}
  // The partial synchronization replication of the %1 database from the
  // primary domain controller %2 completed successfully. %3 change(s) is(are)
  // applied to the database.

  NELOG_NetlogonPartialSyncFailed         = (ERRLOG2_BASE + 16);
  {$EXTERNALSYM NELOG_NetlogonPartialSyncFailed}
  // The partial synchronization replication of the %1 database from the
  // primary domain controller %2 failed with the following error: %n%3

  NELOG_NetlogonFullSyncSuccess           = (ERRLOG2_BASE + 17);
  {$EXTERNALSYM NELOG_NetlogonFullSyncSuccess}
  // The full synchronization replication of the %1 database from the
  // primary domain controller %2 completed successfully.

  NELOG_NetlogonFullSyncFailed            = (ERRLOG2_BASE + 18);
  {$EXTERNALSYM NELOG_NetlogonFullSyncFailed}
  // The full synchronization replication of the %1 database from the
  // primary domain controller %2 failed with the following error: %n%3

  NELOG_NetlogonAuthNoDomainController    = (ERRLOG2_BASE + 19);
  {$EXTERNALSYM NELOG_NetlogonAuthNoDomainController}
  // No Windows NT Domain Controller is available for domain %1.
  // (This event is expected and can be ignored when booting with
  // the 'No Net' Hardware Profile.)  The following error occurred:%n%2

  NELOG_NetlogonAuthNoTrustLsaSecret      = (ERRLOG2_BASE + 20);
  {$EXTERNALSYM NELOG_NetlogonAuthNoTrustLsaSecret}
  // The session setup to the Windows NT Domain Controller %1 for the domain %2
  // failed because the computer %3 does not have a local security database account.

  NELOG_NetlogonAuthNoTrustSamAccount     = (ERRLOG2_BASE + 21);
  {$EXTERNALSYM NELOG_NetlogonAuthNoTrustSamAccount}
  // The session setup to the Windows NT Domain Controller %1 for the domain %2
  // failed because the Windows NT Domain Controller does not have an account
  // for the computer %3.

  NELOG_NetlogonServerAuthFailed          = (ERRLOG2_BASE + 22);
  {$EXTERNALSYM NELOG_NetlogonServerAuthFailed}
  // The session setup from the computer %1 failed to authenticate.
  // The name of the account referenced in the security database is
  // %2.  The following error occurred: %n%3

  NELOG_NetlogonServerAuthNoTrustSamAccount = (ERRLOG2_BASE + 23);
  {$EXTERNALSYM NELOG_NetlogonServerAuthNoTrustSamAccount}
  // The session setup from the computer %1 failed because there is
  // no trust account in the security database for this computer. The name of
  // the account referenced in the security database is %2.

// General log messages for NT services.

  NELOG_FailedToRegisterSC                  = (ERRLOG2_BASE + 24);
  {$EXTERNALSYM NELOG_FailedToRegisterSC}
  // Could not register control handler with service controller %1.

  NELOG_FailedToSetServiceStatus            = (ERRLOG2_BASE + 25);
  {$EXTERNALSYM NELOG_FailedToSetServiceStatus}
  // Could not set service status with service controller %1.

  NELOG_FailedToGetComputerName             = (ERRLOG2_BASE + 26);
  {$EXTERNALSYM NELOG_FailedToGetComputerName}
  // Could not find the computer name %1.

  NELOG_DriverNotLoaded                     = (ERRLOG2_BASE + 27);
  {$EXTERNALSYM NELOG_DriverNotLoaded}
  // Could not load %1 device driver.

  NELOG_NoTranportLoaded                    = (ERRLOG2_BASE + 28);
  {$EXTERNALSYM NELOG_NoTranportLoaded}
  // Could not load any transport.

// More Netlogon service events

  NELOG_NetlogonFailedDomainDelta           = (ERRLOG2_BASE + 29);
  {$EXTERNALSYM NELOG_NetlogonFailedDomainDelta}
  // Replication of the %1 Domain Object "%2" from primary domain controller
  // %3 failed with the following error: %n%4

  NELOG_NetlogonFailedGlobalGroupDelta      = (ERRLOG2_BASE + 30);
  {$EXTERNALSYM NELOG_NetlogonFailedGlobalGroupDelta}
  // Replication of the %1 Global Group "%2" from primary domain controller
  // %3 failed with the following error: %n%4

  NELOG_NetlogonFailedLocalGroupDelta       = (ERRLOG2_BASE + 31);
  {$EXTERNALSYM NELOG_NetlogonFailedLocalGroupDelta}
  // Replication of the %1 Local Group "%2" from primary domain controller
  // %3 failed with the following error: %n%4

  NELOG_NetlogonFailedUserDelta             = (ERRLOG2_BASE + 32);
  {$EXTERNALSYM NELOG_NetlogonFailedUserDelta}
  // Replication of the %1 User "%2" from primary domain controller
  // %3 failed with the following error: %n%4

  NELOG_NetlogonFailedPolicyDelta           = (ERRLOG2_BASE + 33);
  {$EXTERNALSYM NELOG_NetlogonFailedPolicyDelta}
  // Replication of the %1 Policy Object "%2" from primary domain controller
  // %3 failed with the following error: %n%4

  NELOG_NetlogonFailedTrustedDomainDelta    = (ERRLOG2_BASE + 34);
  {$EXTERNALSYM NELOG_NetlogonFailedTrustedDomainDelta}
  // Replication of the %1 Trusted Domain Object "%2" from primary domain controller
  // %3 failed with the following error: %n%4

  NELOG_NetlogonFailedAccountDelta          = (ERRLOG2_BASE + 35);
  {$EXTERNALSYM NELOG_NetlogonFailedAccountDelta}
  // Replication of the %1 Account Object "%2" from primary domain controller
  // %3 failed with the following error: %n%4

  NELOG_NetlogonFailedSecretDelta           = (ERRLOG2_BASE + 36);
  {$EXTERNALSYM NELOG_NetlogonFailedSecretDelta}
  // Replication of the %1 Secret "%2" from primary domain controller
  // %3 failed with the following error: %n%4

  NELOG_NetlogonSystemError                 = (ERRLOG2_BASE + 37);
  {$EXTERNALSYM NELOG_NetlogonSystemError}
  // The system returned the following unexpected error code: %n%1

  NELOG_NetlogonDuplicateMachineAccounts    = (ERRLOG2_BASE + 38);
  {$EXTERNALSYM NELOG_NetlogonDuplicateMachineAccounts}
  // Netlogon has detected two machine accounts for server "%1".
  // The server can be either a Windows NT Server that is a member of the
  // domain or the server can be a LAN Manager server with an account in the
  // SERVERS global group.  It cannot be both.

  NELOG_NetlogonTooManyGlobalGroups         = (ERRLOG2_BASE + 39);
  {$EXTERNALSYM NELOG_NetlogonTooManyGlobalGroups}
  // This domain has more global groups than can be replicated to a LanMan
  // BDC.  Either delete some of your global groups or remove the LanMan
  // BDCs from the domain.

  NELOG_NetlogonBrowserDriver               = (ERRLOG2_BASE + 40);
  {$EXTERNALSYM NELOG_NetlogonBrowserDriver}
  // The Browser driver returned the following error to Netlogon: %n%1

  NELOG_NetlogonAddNameFailure              = (ERRLOG2_BASE + 41);
  {$EXTERNALSYM NELOG_NetlogonAddNameFailure}
  // Netlogon could not register the %1<1B> name for the following reason: %n%2

//  More Remoteboot service events.

  NELOG_RplMessages                         = (ERRLOG2_BASE + 42);
  {$EXTERNALSYM NELOG_RplMessages}
  // Service failed to retrieve messages needed to boot remote boot clients.

  NELOG_RplXnsBoot                          = (ERRLOG2_BASE + 43);
  {$EXTERNALSYM NELOG_RplXnsBoot}
  // Service experienced a severe error and can no longer provide remote boot
  // for 3Com 3Start remote boot clients.

  NELOG_RplSystem                           = (ERRLOG2_BASE + 44);
  {$EXTERNALSYM NELOG_RplSystem}
  // Service experienced a severe system error and will shut itself down.

  NELOG_RplWkstaTimeout                     = (ERRLOG2_BASE + 45);
  {$EXTERNALSYM NELOG_RplWkstaTimeout}
  // Client with computer name %1 failed to acknowledge receipt of the
  // boot data.  Remote boot of this client was not completed.

  NELOG_RplWkstaFileOpen                    = (ERRLOG2_BASE + 46);
  {$EXTERNALSYM NELOG_RplWkstaFileOpen}
  // Client with computer name %1 was not booted due to an error in opening
  // file %2.

  NELOG_RplWkstaFileRead                    = (ERRLOG2_BASE + 47);
  {$EXTERNALSYM NELOG_RplWkstaFileRead}
  // Client with computer name %1 was not booted due to an error in reading
  // file %2.

  NELOG_RplWkstaMemory                      = (ERRLOG2_BASE + 48);
  {$EXTERNALSYM NELOG_RplWkstaMemory}
  // Client with computer name %1 was not booted due to insufficent memory
  // at the remote boot server.

  NELOG_RplWkstaFileChecksum                = (ERRLOG2_BASE + 49);
  {$EXTERNALSYM NELOG_RplWkstaFileChecksum}
  // Client with computer name %1 will be booted without using checksums
  // because checksum for file %2 could not be calculated.

  NELOG_RplWkstaFileLineCount               = (ERRLOG2_BASE + 50);
  {$EXTERNALSYM NELOG_RplWkstaFileLineCount}
  // Client with computer name %1 was not booted due to too many lines in
  // file %2.

  NELOG_RplWkstaBbcFile                     = (ERRLOG2_BASE + 51);
  {$EXTERNALSYM NELOG_RplWkstaBbcFile}
  // Client with computer name %1 was not booted because the boot block
  // configuration file %2 for this client does not contain boot block
  // line and/or loader line.

  NELOG_RplWkstaFileSize                    = (ERRLOG2_BASE + 52);
  {$EXTERNALSYM NELOG_RplWkstaFileSize}
  // Client with computer name %1 was not booted due to a bad size of
  // file %2.

  NELOG_RplWkstaInternal                    = (ERRLOG2_BASE + 53);
  {$EXTERNALSYM NELOG_RplWkstaInternal}
  // Client with computer name %1 was not booted due to remote boot
  // service internal error.

  NELOG_RplWkstaWrongVersion                = (ERRLOG2_BASE + 54);
  {$EXTERNALSYM NELOG_RplWkstaWrongVersion}
  // Client with computer name %1 was not booted because file %2 has an
  // invalid boot header.

  NELOG_RplWkstaNetwork                     = (ERRLOG2_BASE + 55);
  {$EXTERNALSYM NELOG_RplWkstaNetwork}
  // Client with computer name %1 was not booted due to network error.

  NELOG_RplAdapterResource                  = (ERRLOG2_BASE + 56);
  {$EXTERNALSYM NELOG_RplAdapterResource}
  // Client with adapter id %1 was not booted due to lack of resources.

  NELOG_RplFileCopy                         = (ERRLOG2_BASE + 57);
  {$EXTERNALSYM NELOG_RplFileCopy}
  // Service experienced error copying file or directory %1.

  NELOG_RplFileDelete                       = (ERRLOG2_BASE + 58);
  {$EXTERNALSYM NELOG_RplFileDelete}
  // Service experienced error deleting file or directory %1.

  NELOG_RplFilePerms                        = (ERRLOG2_BASE + 59);
  {$EXTERNALSYM NELOG_RplFilePerms}
  // Service experienced error setting permissions on file or directory %1.

  NELOG_RplCheckConfigs                     = (ERRLOG2_BASE + 60);
  {$EXTERNALSYM NELOG_RplCheckConfigs}
  // Service experienced error evaluating RPL configurations.

  NELOG_RplCreateProfiles                   = (ERRLOG2_BASE + 61);
  {$EXTERNALSYM NELOG_RplCreateProfiles}
  // Service experienced error creating RPL profiles for all configurations.

  NELOG_RplRegistry                         = (ERRLOG2_BASE + 62);
  {$EXTERNALSYM NELOG_RplRegistry}
  // Service experienced error accessing registry.

  NELOG_RplReplaceRPLDISK                   = (ERRLOG2_BASE + 63);
  {$EXTERNALSYM NELOG_RplReplaceRPLDISK}
  // Service experienced error replacing possibly outdated RPLDISK.SYS.

  NELOG_RplCheckSecurity                    = (ERRLOG2_BASE + 64);
  {$EXTERNALSYM NELOG_RplCheckSecurity}
  // Service experienced error adding security accounts or setting
  // file permissions.  These accounts are the RPLUSER local group
  // and the user accounts for the individual RPL workstations.

  NELOG_RplBackupDatabase                   = (ERRLOG2_BASE + 65);
  {$EXTERNALSYM NELOG_RplBackupDatabase}
  // Service failed to back up its database.

  NELOG_RplInitDatabase                     = (ERRLOG2_BASE + 66);
  {$EXTERNALSYM NELOG_RplInitDatabase}
  // Service failed to initialize from its database.  The database may be
  // missing or corrupted.  Service will attempt restoring the database
  // from the backup.

  NELOG_RplRestoreDatabaseFailure           = (ERRLOG2_BASE + 67);
  {$EXTERNALSYM NELOG_RplRestoreDatabaseFailure}
  // Service failed to restore its database from the backup.  Service
  // will not start.

  NELOG_RplRestoreDatabaseSuccess           = (ERRLOG2_BASE + 68);
  {$EXTERNALSYM NELOG_RplRestoreDatabaseSuccess}
  // Service sucessfully restored its database from the backup.

  NELOG_RplInitRestoredDatabase             = (ERRLOG2_BASE + 69);
  {$EXTERNALSYM NELOG_RplInitRestoredDatabase}
  // Service failed to initialize from its restored database.  Service
  // will not start.

// More Netlogon and RPL service events

  NELOG_NetlogonSessionTypeWrong            = (ERRLOG2_BASE + 70);
  {$EXTERNALSYM NELOG_NetlogonSessionTypeWrong}
  // The session setup to the Windows NT Domain Controller %1 from computer
  // %2 using account %4 failed.  %2 is declared to be a BDC in domain %3.
  // However, %2 tried to connect as either a DC in a trusted domain,
  // a member workstation in domain %3, or as a server in domain %3.
  // Use the Server Manager to remove the BDC account for %2.

  NELOG_RplUpgradeDBTo40                    = (ERRLOG2_BASE + 71);
  {$EXTERNALSYM NELOG_RplUpgradeDBTo40}
  // The Remoteboot database was in NT 3.5 / NT 3.51 format and NT is
  // attempting to convert it to NT 4.0 format. The JETCONV converter
  // will write to the Application event log when it is finished.

  NELOG_NetlogonLanmanBdcsNotAllowed        = (ERRLOG2_BASE + 72);
  {$EXTERNALSYM NELOG_NetlogonLanmanBdcsNotAllowed}
  // Global group SERVERS exists in domain %1 and has members.
  // This group defines Lan Manager BDCs in the domain.
  // Lan Manager BDCs are not permitted in NT domains.

  NELOG_NetlogonNoDynamicDns                = (ERRLOG2_BASE + 73);
  {$EXTERNALSYM NELOG_NetlogonNoDynamicDns}
  // The DNS server for this DC does not support dynamic DNS.
  // Add the DNS records from the file '%SystemRoot%\System32\Config\netlogon.dns'
  // to the DNS server serving the domain referenced in that file.

  NELOG_NetlogonDynamicDnsRegisterFailure   = (ERRLOG2_BASE + 74);
  {$EXTERNALSYM NELOG_NetlogonDynamicDnsRegisterFailure}
  // Registration of the DNS record '%1' failed with the following error: %n%2

  NELOG_NetlogonDynamicDnsDeregisterFailure = (ERRLOG2_BASE + 75);
  {$EXTERNALSYM NELOG_NetlogonDynamicDnsDeregisterFailure}
  // Deregistration of the DNS record '%1' failed with the following error: %n%2

  NELOG_NetlogonFailedFileCreate            = (ERRLOG2_BASE + 76);
  {$EXTERNALSYM NELOG_NetlogonFailedFileCreate}
  // Failed to create/open file %1 with the following error: %n%2

  NELOG_NetlogonGetSubnetToSite             = (ERRLOG2_BASE + 77);
  {$EXTERNALSYM NELOG_NetlogonGetSubnetToSite}
  // Netlogon got the following error while trying to get the subnet to site
  // mapping information from the DS: %n%1

  NELOG_NetlogonNoSiteForClient              = (ERRLOG2_BASE + 78);
  {$EXTERNALSYM NELOG_NetlogonNoSiteForClient}
  // '%1' tried to determine its site by looking up its IP address ('%2')
  // in the Configuration\Sites\Subnets container in the DS.  No subnet matched
  // the IP address.  Consider adding a subnet object for this IP address.

  NELOG_NetlogonBadSiteName                  = (ERRLOG2_BASE + 79);
  {$EXTERNALSYM NELOG_NetlogonBadSiteName}
  // The site name for this computer is '%1'.  That site name is not a valid
  // site name.  A site name must be a valid DNS label.
  // Rename the site to be a valid name.

  NELOG_NetlogonBadSubnetName                = (ERRLOG2_BASE + 80);
  {$EXTERNALSYM NELOG_NetlogonBadSubnetName}
  // The subnet object '%1' appears in the Configuration\Sites\Subnets
  // container in the DS.  The name is not syntactically valid.  The valid
  // syntax is xx.xx.xx.xx/yy where xx.xx.xx.xx is a valid IP subnet number
  // and yy is the number of bits in the subnet mask.
  //
  // Correct the name of the subnet object.

  NELOG_NetlogonDynamicDnsServerFailure      = (ERRLOG2_BASE + 81);
  {$EXTERNALSYM NELOG_NetlogonDynamicDnsServerFailure}
  // Dynamic registration or deregistration of one or more DNS records failed because no DNS servers are available.

  NELOG_NetlogonDynamicDnsFailure            = (ERRLOG2_BASE + 82);
  {$EXTERNALSYM NELOG_NetlogonDynamicDnsFailure}
  // Dynamic registration or deregistration of one or more DNS records failed with the following error: %n%1

  NELOG_NetlogonRpcCallCancelled             = (ERRLOG2_BASE + 83);
  {$EXTERNALSYM NELOG_NetlogonRpcCallCancelled}
  // The session setup to the Windows NT Domain Controller %1 for the domain %2
  // is not responsive.  The current RPC call from Netlogon on \\%3 to %1 has been cancelled.

  NELOG_NetlogonDcSiteCovered                = (ERRLOG2_BASE + 84);
  {$EXTERNALSYM NELOG_NetlogonDcSiteCovered}
  // Site '%2' does not have any Domain Controllers for domain '%3'.
  // Domain Controllers in site '%1' have been automatically
  // selected to cover site '%2' based on configured Directory Server
  // replication costs.

  NELOG_NetlogonDcSiteNotCovered             = (ERRLOG2_BASE + 85);
  {$EXTERNALSYM NELOG_NetlogonDcSiteNotCovered}
  // This Domain Controller no longer automatically covers site '%1'.

  NELOG_NetlogonGcSiteCovered                = (ERRLOG2_BASE + 86);
  {$EXTERNALSYM NELOG_NetlogonGcSiteCovered}
  // Site '%2' does not have any Global Catalog servers.
  // Global Catalog servers in site '%1' have been automatically
  // selected to cover site '%2' based on configured Directory Server
  // replication costs.

  NELOG_NetlogonGcSiteNotCovered             = (ERRLOG2_BASE + 87);
  {$EXTERNALSYM NELOG_NetlogonGcSiteNotCovered}
  // This Global Catalog server no longer automatically covers site '%1'.

  NELOG_NetlogonFailedSpnUpdate              = (ERRLOG2_BASE + 88);
  {$EXTERNALSYM NELOG_NetlogonFailedSpnUpdate}
  // Attemp to update Service Principal Name (SPN) of the computer object
  // in Active Directory failed.  The following error occurred: %n%1

  NELOG_NetlogonFailedDnsHostNameUpdate      = (ERRLOG2_BASE + 89);
  {$EXTERNALSYM NELOG_NetlogonFailedDnsHostNameUpdate}
  // Attemp to update DNS Host Name of the computer object
  // in Active Directory failed.  The following error occurred: %n%1

// Translated from LMAT.H

//  The following bits are used with Flags field in structures below.

//  Do we exec programs for this job periodically (/EVERY switch)
//  or one time (/NEXT switch).

const
  {$EXTERNALSYM JOB_RUN_PERIODICALLY}
  JOB_RUN_PERIODICALLY            = $01;    //  set if EVERY

//  Was there an error last time we tried to exec a program on behalf of
//  this job.
//  This flag is meaningfull on output only!

  {$EXTERNALSYM JOB_EXEC_ERROR}
  JOB_EXEC_ERROR                  = $02;    //  set if error

//  Will this job run today or tomorrow.
//  This flag is meaningfull on output only!

  {$EXTERNALSYM JOB_RUNS_TODAY}
  JOB_RUNS_TODAY                  = $04;    //  set if today

//  Add current day of the month to DaysOfMonth input.
//  This flag is meaningfull on input only!

  {$EXTERNALSYM JOB_ADD_CURRENT_DATE}
  JOB_ADD_CURRENT_DATE            = $08;    // set if to add current date


//  Will this job be run interactively or not.  Windows NT 3.1 do not
//  know about this bit, i.e. they submit interactive jobs only.

  {$EXTERNALSYM JOB_NONINTERACTIVE}
  JOB_NONINTERACTIVE              = $10;    // set for noninteractive

  {$EXTERNALSYM JOB_INPUT_FLAGS}
  JOB_INPUT_FLAGS = JOB_RUN_PERIODICALLY or JOB_ADD_CURRENT_DATE or
    JOB_NONINTERACTIVE;

  {$EXTERNALSYM JOB_OUTPUT_FLAGS}
  JOB_OUTPUT_FLAGS = JOB_RUN_PERIODICALLY or JOB_EXEC_ERROR or JOB_RUNS_TODAY or
    JOB_NONINTERACTIVE;


type
  PAtInfo = ^TAtInfo;
  {$EXTERNALSYM _AT_INFO}
  _AT_INFO = record
    JobTime: DWORD;
    DaysOfMonth: DWORD;
    DaysOfWeek: UCHAR;
    Flags: UCHAR;
   Command: LPWSTR;
  end;
  TAtInfo = _AT_INFO;
  {$EXTERNALSYM AT_INFO}
  AT_INFO = _AT_INFO;

  PAtEnum = ^TAtEnum;
  {$EXTERNALSYM _AT_ENUM}
  _AT_ENUM = record
    JobId: DWORD;
    JobTime: DWORD;
    DaysOfMonth: DWORD;
    DaysOfWeek: UCHAR;
    Flags: UCHAR;
    Command: LPWSTR;
  end;
  TAtEnum = _AT_ENUM;
  {$EXTERNALSYM AT_ENUM}
  AT_ENUM = _AT_ENUM;
  
{$EXTERNALSYM NetScheduleJobAdd}
function NetScheduleJobAdd(Servername: LPCWSTR; Buffer: Pointer;
  var JobId: DWORD): NET_API_STATUS; stdcall;

{$EXTERNALSYM NetScheduleJobDel}
function NetScheduleJobDel(Servername: LPCWSTR; MinJobId: DWORD;
  MaxJobId: DWORD): NET_API_STATUS; stdcall;

{$EXTERNALSYM NetScheduleJobEnum}
function NetScheduleJobEnum( Servername: LPCWSTR; PointerToBuffer: Pointer;
  PrefferedMaximumLength: DWORD; var EntriesRead: DWORD; var TotalEntries: DWORD;
  ResumeHandle: PDWORD): NET_API_STATUS; stdcall;

{$EXTERNALSYM NetScheduleJobGetInfo}
function NetScheduleJobGetInfo(Servername: LPCWSTR; JobId: DWORD;
  PointerToBuffer: Pointer): NET_API_STATUS; stdcall;

// Translated from LMBROWSR.H

type
  PBrowserStatistics = ^TBrowserStatistics;
  _BROWSER_STATISTICS = record
    StatisticsStartTime: LARGE_INTEGER;
    NumberOfServerAnnouncements: LARGE_INTEGER;
    NumberOfDomainAnnouncements: LARGE_INTEGER;
    NumberOfElectionPackets: ULONG;
    NumberOfMailslotWrites: ULONG;
    NumberOfGetBrowserServerListRequests: ULONG;
    NumberOfServerEnumerations: ULONG;
    NumberOfDomainEnumerations: ULONG;
    NumberOfOtherEnumerations: ULONG;
    NumberOfMissedServerAnnouncements: ULONG;
    NumberOfMissedMailslotDatagrams: ULONG;
    NumberOfMissedGetBrowserServerListRequests: ULONG;
    NumberOfFailedServerAnnounceAllocations: ULONG;
    NumberOfFailedMailslotAllocations: ULONG;
    NumberOfFailedMailslotReceives: ULONG;
    NumberOfFailedMailslotWrites: ULONG;
    NumberOfFailedMailslotOpens: ULONG;
    NumberOfDuplicateMasterAnnouncements: ULONG;
    NumberOfIllegalDatagrams: LARGE_INTEGER;
  end;
  {$EXTERNALSYM _BROWSER_STATISTICS}
  TBrowserStatistics = _BROWSER_STATISTICS;
  BROWSER_STATISTICS = _BROWSER_STATISTICS;
  {$EXTERNALSYM BROWSER_STATISTICS}

  PBrowserStatistics100 = ^TBrowserStatistics100;
  _BROWSER_STATISTICS_100 = record
    StartTime: LARGE_INTEGER;
    NumberOfServerAnnouncements: LARGE_INTEGER;
    NumberOfDomainAnnouncements: LARGE_INTEGER;
    NumberOfElectionPackets: ULONG;
    NumberOfMailslotWrites: ULONG;
    NumberOfGetBrowserServerListRequests: ULONG;
    NumberOfIllegalDatagrams: LARGE_INTEGER;
  end;
  {$EXTERNALSYM _BROWSER_STATISTICS_100}
  TBrowserStatistics100 = _BROWSER_STATISTICS_100;
  BROWSER_STATISTICS_100 = _BROWSER_STATISTICS_100;
  {$EXTERNALSYM BROWSER_STATISTICS_100}

  PBrowserStatistics101 = ^TBrowserStatistics101;
  _BROWSER_STATISTICS_101 = record
    StartTime: LARGE_INTEGER;
    NumberOfServerAnnouncements: LARGE_INTEGER;
    NumberOfDomainAnnouncements: LARGE_INTEGER;
    NumberOfElectionPackets: ULONG;
    NumberOfMailslotWrites: ULONG;
    NumberOfGetBrowserServerListRequests: ULONG;
    NumberOfIllegalDatagrams: LARGE_INTEGER;
    NumberOfMissedServerAnnouncements: ULONG;
    NumberOfMissedMailslotDatagrams: ULONG;
    NumberOfMissedGetBrowserServerListRequests: ULONG;
    NumberOfFailedServerAnnounceAllocations: ULONG;
    NumberOfFailedMailslotAllocations: ULONG;
    NumberOfFailedMailslotReceives: ULONG;
    NumberOfFailedMailslotWrites: ULONG;
    NumberOfFailedMailslotOpens: ULONG;
    NumberOfDuplicateMasterAnnouncements: ULONG;
  end;
  {$EXTERNALSYM _BROWSER_STATISTICS_101}
  TBrowserStatistics101 = _BROWSER_STATISTICS_101;
  BROWSER_STATISTICS_101 = _BROWSER_STATISTICS_101;
  {$EXTERNALSYM BROWSER_STATISTICS_101}

  PBrowserEmulatedDomain = ^TBrowserEmulatedDomain;
  _BROWSER_EMULATED_DOMAIN = record
    DomainName: LPWSTR;
    EmulatedServerName: LPWSTR;
    Role: DWORD;
  end;
  {$EXTERNALSYM _BROWSER_EMULATED_DOMAIN}
  TBrowserEmulatedDomain = _BROWSER_EMULATED_DOMAIN;
  BROWSER_EMULATED_DOMAIN = _BROWSER_EMULATED_DOMAIN;
  {$EXTERNALSYM BROWSER_EMULATED_DOMAIN}

// Function Prototypes - BROWSER

function I_BrowserServerEnum(servername, transport, clientname: LPCWSTR;
  level: DWORD; bufptr: Pointer; prefmaxlen: DWORD; var entriesread: DWORD;
  var totalentries: DWORD; servertype: DWORD; domain: LPCWSTR;
  resume_handle: PDWORD): NET_API_STATUS; stdcall;
{$EXTERNALSYM I_BrowserServerEnum}

function I_BrowserServerEnumEx(servername, transport, clientname: LPCWSTR;
  level: DWORD; bufptr: Pointer; prefmaxlen: DWORD; var entriesread: DWORD;
  var totalentries: DWORD; servertype: DWORD; domain: LPCWSTR;
  FirstNameToReturn: LPCWSTR): NET_API_STATUS; stdcall;
{$EXTERNALSYM I_BrowserServerEnumEx}

function I_BrowserQueryOtherDomains(servername: LPCWSTR; bufptr: Pointer;
  var entriesread: DWORD; var totalentries: DWORD): NET_API_STATUS; stdcall;
{$EXTERNALSYM I_BrowserQueryOtherDomains}

function I_BrowserResetNetlogonState(servername: LPCWSTR): NET_API_STATUS; stdcall;
{$EXTERNALSYM I_BrowserResetNetlogonState}

function I_BrowserSetNetlogonState(ServerName, DomainName, EmulatedServerName: LPWSTR;
  Role: DWORD): NET_API_STATUS; stdcall;
{$EXTERNALSYM I_BrowserSetNetlogonState}

const
  BROWSER_ROLE_PDC = $1;
  {$EXTERNALSYM BROWSER_ROLE_PDC}
  BROWSER_ROLE_BDC = $2;
  {$EXTERNALSYM BROWSER_ROLE_BDC}

function I_BrowserQueryEmulatedDomains(ServerName: LPWSTR;
  var EmulatedDomains: TBrowserEmulatedDomain;
  var EntriesRead: DWORD): NET_API_STATUS; stdcall;
{$EXTERNALSYM I_BrowserQueryEmulatedDomains}

function I_BrowserQueryStatistics(servername: LPCWSTR;
  var statistics: TBrowserStatistics): NET_API_STATUS; stdcall;
{$EXTERNALSYM I_BrowserQueryStatistics}

function I_BrowserResetStatistics(servername: LPCWSTR): NET_API_STATUS; stdcall;
{$EXTERNALSYM I_BrowserResetStatistics}

function I_BrowserServerEnumForXactsrv(TransportName, ClientName: LPCWSTR;
  NtLevel: ULONG; ClientLevel: Word; Buffer: Pointer; BufferLength: WORD;
  PreferedMaximumLength: DWORD; var EntriesRead: DWORD; var TotalEntries: DWORD;
  ServerType: DWORD; Domain: LPCWSTR; FirstNameToReturn: LPCWSTR;
  Converter: PWord): Word; stdcall;
{$EXTERNALSYM I_BrowserServerEnumForXactsrv}

function I_BrowserDebugTrace(Server: PWideChar; Buffer: PChar): NET_API_STATUS; stdcall;
{$EXTERNALSYM I_BrowserDebugTrace}

// Translated from LMCHDEV.H

// CharDev Class

// Function Prototypes - CharDev

function NetCharDevEnum(servername: LPCWSTR; level: DWORD; bufptr: Pointer;
  prefmaxlen: DWORD; var entriesread: DWORD; var totalentries: DWORD;
  resume_handle: DWORD): NET_API_STATUS; stdcall;
{$EXTERNALSYM NetCharDevEnum}

function NetCharDevGetInfo(servername: LPCWSTR; devname: LPCWSTR;
  level: DWORD; bufptr: Pointer): NET_API_STATUS; stdcall;
{$EXTERNALSYM NetCharDevGetInfo}

function NetCharDevControl(servername: LPCWSTR; devname: LPCWSTR;
  opcode: DWORD): NET_API_STATUS; stdcall;
{$EXTERNALSYM NetCharDevControl}

// Data Structures - CharDev

type
  PChardevInfo0 = ^TChardevInfo0;
  _CHARDEV_INFO_0 = record
    ch0_dev: LPWSTR;
  end;
  {$EXTERNALSYM _CHARDEV_INFO_0}
  TChardevInfo0 = _CHARDEV_INFO_0;
  CHARDEV_INFO_0 = _CHARDEV_INFO_0;
  {$EXTERNALSYM CHARDEV_INFO_0}

  PChardevInfo1 = ^TChardevInfo1;
  _CHARDEV_INFO_1 = record
    ch1_dev: LPWSTR;
    ch1_status: DWORD;
    ch1_username: LPWSTR;
    ch1_time: DWORD;
  end;
  {$EXTERNALSYM _CHARDEV_INFO_1}
  TChardevInfo1 = _CHARDEV_INFO_1;
  CHARDEV_INFO_1 = _CHARDEV_INFO_1;
  {$EXTERNALSYM CHARDEV_INFO_1}

// CharDevQ Class

// Function Prototypes - CharDevQ

function NetCharDevQEnum(servername: LPCWSTR; username: LPCWSTR; level: DWORD;
  bufptr: Pointer; prefmaxlen: DWORD; var entriesread: DWORD;
  var totalentries: DWORD; resume_handle: PDWORD): NET_API_STATUS; stdcall;
{$EXTERNALSYM NetCharDevQEnum}

function NetCharDevQGetInfo(servername, queuename, username: LPCWSTR;
  level: DWORD; bufptr: Pointer): NET_API_STATUS; stdcall;
{$EXTERNALSYM NetCharDevQGetInfo}

function NetCharDevQSetInfo(servername, queuename: LPCWSTR; level: DWORD;
  buf: Pointer; parm_err: PDWORD): NET_API_STATUS; stdcall;
{$EXTERNALSYM NetCharDevQSetInfo}

function NetCharDevQPurge(servername, queuename: LPCWSTR): NET_API_STATUS; stdcall;
{$EXTERNALSYM NetCharDevQPurge}

function NetCharDevQPurgeSelf(servername, queuename, computername: LPCWSTR): NET_API_STATUS; stdcall;
{$EXTERNALSYM NetCharDevQPurgeSelf}

// Data Structures - CharDevQ

type
  PChardevqInfo0 = ^TChardevqInfo0;
  _CHARDEVQ_INFO_0 = record
    cq0_dev: LPWSTR;
  end;
  {$EXTERNALSYM _CHARDEVQ_INFO_0}
  TChardevqInfo0 = _CHARDEVQ_INFO_0;
  CHARDEVQ_INFO_0 = _CHARDEVQ_INFO_0;
  {$EXTERNALSYM CHARDEVQ_INFO_0}

  PChardevqInfo1 = ^TChardevqInfo1;
  _CHARDEVQ_INFO_1 = record
    cq1_dev: LPWSTR;
    cq1_priority: DWORD;
    cq1_devs: LPWSTR;
    cq1_numusers: DWORD;
    cq1_numahead: DWORD;
  end;
  {$EXTERNALSYM _CHARDEVQ_INFO_1}
  TChardevqInfo1 = _CHARDEVQ_INFO_1;
  CHARDEVQ_INFO_1 = _CHARDEVQ_INFO_1;
  {$EXTERNALSYM CHARDEVQ_INFO_1}

  PChardevqInfo1002 = ^TChardevqInfo1002;
  _CHARDEVQ_INFO_1002 = record
    cq1002_priority: DWORD;
  end;
  {$EXTERNALSYM _CHARDEVQ_INFO_1002}
  TChardevqInfo1002 = _CHARDEVQ_INFO_1002;
  CHARDEVQ_INFO_1002 = _CHARDEVQ_INFO_1002;
  {$EXTERNALSYM CHARDEVQ_INFO_1002}

  PChardevqInfo1003 = ^TChardevqInfo1003;
  _CHARDEVQ_INFO_1003 = record
    cq1003_devs: LPWSTR;
  end;
  {$EXTERNALSYM _CHARDEVQ_INFO_1003}
  TChardevqInfo1003 = _CHARDEVQ_INFO_1003;
  CHARDEVQ_INFO_1003 = _CHARDEVQ_INFO_1003;
  {$EXTERNALSYM CHARDEVQ_INFO_1003}


// Bits for chardev_info_1 field ch1_status.

const
  CHARDEV_STAT_OPENED             = $02;
  {$EXTERNALSYM CHARDEV_STAT_OPENED}
  CHARDEV_STAT_ERROR              = $04;
  {$EXTERNALSYM CHARDEV_STAT_ERROR}

// Opcodes for NetCharDevControl

  CHARDEV_CLOSE                   = 0;
  {$EXTERNALSYM CHARDEV_CLOSE}

// Values for parm_err parameter.

  CHARDEVQ_DEV_PARMNUM        = 1;
  {$EXTERNALSYM CHARDEVQ_DEV_PARMNUM}
  CHARDEVQ_PRIORITY_PARMNUM   = 2;
  {$EXTERNALSYM CHARDEVQ_PRIORITY_PARMNUM}
  CHARDEVQ_DEVS_PARMNUM       = 3;
  {$EXTERNALSYM CHARDEVQ_DEVS_PARMNUM}
  CHARDEVQ_NUMUSERS_PARMNUM   = 4;
  {$EXTERNALSYM CHARDEVQ_NUMUSERS_PARMNUM}
  CHARDEVQ_NUMAHEAD_PARMNUM   = 5;
  {$EXTERNALSYM CHARDEVQ_NUMAHEAD_PARMNUM}

// Single-field infolevels for NetCharDevQSetInfo.

  CHARDEVQ_PRIORITY_INFOLEVEL = (PARMNUM_BASE_INFOLEVEL + CHARDEVQ_PRIORITY_PARMNUM);
  {$EXTERNALSYM CHARDEVQ_PRIORITY_INFOLEVEL}
  CHARDEVQ_DEVS_INFOLEVEL = (PARMNUM_BASE_INFOLEVEL + CHARDEVQ_DEVS_PARMNUM);
  {$EXTERNALSYM CHARDEVQ_DEVS_INFOLEVEL}

// Minimum, maximum, and recommended default for priority.

  CHARDEVQ_MAX_PRIORITY           = 1;
  {$EXTERNALSYM CHARDEVQ_MAX_PRIORITY}
  CHARDEVQ_MIN_PRIORITY           = 9;
  {$EXTERNALSYM CHARDEVQ_MIN_PRIORITY}
  CHARDEVQ_DEF_PRIORITY           = 5;
  {$EXTERNALSYM CHARDEVQ_DEF_PRIORITY}

// Value indicating no requests in the queue.

  CHARDEVQ_NO_REQUESTS            = -1;
  {$EXTERNALSYM CHARDEVQ_NO_REQUESTS}

// Handle Class

// Function Prototypes

function NetHandleGetInfo(handle: THandle; level: DWORD; bufptr: Pointer): NET_API_STATUS; stdcall;
{$EXTERNALSYM NetHandleGetInfo}

function NetHandleSetInfo(handle: THandle; level: DWORD; buf: Pointer;
  parmnum: DWORD; parmerr: PDWORD): NET_API_STATUS; stdcall;
{$EXTERNALSYM NetHandleSetInfo}

//
//  Data Structures
//

type
  PHandleInfo1 = ^THandleInfo1;
  _HANDLE_INFO_1 = record
    hdli1_chartime: DWORD;
    hdli1_charcount: DWORD;
  end;
  {$EXTERNALSYM _HANDLE_INFO_1}
  THandleInfo1 = _HANDLE_INFO_1;
  HANDLE_INFO_1 = _HANDLE_INFO_1;
  {$EXTERNALSYM HANDLE_INFO_1}

// Handle Get Info Levels

const
  HANDLE_INFO_LEVEL_1                 = 1;
  {$EXTERNALSYM HANDLE_INFO_LEVEL_1}

// Handle Set Info parm numbers

  HANDLE_CHARTIME_PARMNUM     = 1;
  {$EXTERNALSYM HANDLE_CHARTIME_PARMNUM}
  HANDLE_CHARCOUNT_PARMNUM    = 2;
  {$EXTERNALSYM HANDLE_CHARCOUNT_PARMNUM}

// Translated from LMSNAME.H

//  Standard LAN Manager service names.

const
  SERVICE_WORKSTATION       = 'LanmanWorkstation';
  {$EXTERNALSYM SERVICE_WORKSTATION}
  SERVICE_LM20_WORKSTATION  = 'WORKSTATION';
  {$EXTERNALSYM SERVICE_LM20_WORKSTATION}
  WORKSTATION_DISPLAY_NAME  = 'Workstation';
  {$EXTERNALSYM WORKSTATION_DISPLAY_NAME}

  SERVICE_SERVER            = 'LanmanServer';
  {$EXTERNALSYM SERVICE_SERVER}
  SERVICE_LM20_SERVER       = 'SERVER';
  {$EXTERNALSYM SERVICE_LM20_SERVER}
  SERVER_DISPLAY_NAME       = 'Server';
  {$EXTERNALSYM SERVER_DISPLAY_NAME}

  SERVICE_BROWSER           = 'BROWSER';
  {$EXTERNALSYM SERVICE_BROWSER}
  SERVICE_LM20_BROWSER      = SERVICE_BROWSER;
  {$EXTERNALSYM SERVICE_LM20_BROWSER}

  SERVICE_MESSENGER         = 'MESSENGER';
  {$EXTERNALSYM SERVICE_MESSENGER}
  SERVICE_LM20_MESSENGER    = SERVICE_MESSENGER;
  {$EXTERNALSYM SERVICE_LM20_MESSENGER}

  SERVICE_NETRUN            = 'NETRUN';
  {$EXTERNALSYM SERVICE_NETRUN}
  SERVICE_LM20_NETRUN       = SERVICE_NETRUN;
  {$EXTERNALSYM SERVICE_LM20_NETRUN}

  SERVICE_SPOOLER           = 'SPOOLER';
  {$EXTERNALSYM SERVICE_SPOOLER}
  SERVICE_LM20_SPOOLER      = SERVICE_SPOOLER;
  {$EXTERNALSYM SERVICE_LM20_SPOOLER}

  SERVICE_ALERTER           = 'ALERTER';
  {$EXTERNALSYM SERVICE_ALERTER}
  SERVICE_LM20_ALERTER      = SERVICE_ALERTER;
  {$EXTERNALSYM SERVICE_LM20_ALERTER}

  SERVICE_NETLOGON          = 'NETLOGON';
  {$EXTERNALSYM SERVICE_NETLOGON}
  SERVICE_LM20_NETLOGON     = SERVICE_NETLOGON;
  {$EXTERNALSYM SERVICE_LM20_NETLOGON}

  SERVICE_NETPOPUP          = 'NETPOPUP';
  {$EXTERNALSYM SERVICE_NETPOPUP}
  SERVICE_LM20_NETPOPUP     = SERVICE_NETPOPUP;
  {$EXTERNALSYM SERVICE_LM20_NETPOPUP}

  SERVICE_SQLSERVER         = 'SQLSERVER';
  {$EXTERNALSYM SERVICE_SQLSERVER}
  SERVICE_LM20_SQLSERVER    = SERVICE_SQLSERVER;
  {$EXTERNALSYM SERVICE_LM20_SQLSERVER}

  SERVICE_REPL              = 'REPLICATOR';
  {$EXTERNALSYM SERVICE_REPL}
  SERVICE_LM20_REPL         = SERVICE_REPL;
  {$EXTERNALSYM SERVICE_LM20_REPL}

  SERVICE_RIPL              = 'REMOTEBOOT';
  {$EXTERNALSYM SERVICE_RIPL}
  SERVICE_LM20_RIPL         = SERVICE_RIPL;
  {$EXTERNALSYM SERVICE_LM20_RIPL}

  SERVICE_TIMESOURCE        = 'TIMESOURCE';
  {$EXTERNALSYM SERVICE_TIMESOURCE}
  SERVICE_LM20_TIMESOURCE   = SERVICE_TIMESOURCE;
  {$EXTERNALSYM SERVICE_LM20_TIMESOURCE}

  SERVICE_AFP               = 'AFP';
  {$EXTERNALSYM SERVICE_AFP}
  SERVICE_LM20_AFP          = SERVICE_AFP;
  {$EXTERNALSYM SERVICE_LM20_AFP}

  SERVICE_UPS               = 'UPS';
  {$EXTERNALSYM SERVICE_UPS}
  SERVICE_LM20_UPS          = SERVICE_UPS;
  {$EXTERNALSYM SERVICE_LM20_UPS}

  SERVICE_XACTSRV           = 'XACTSRV';
  {$EXTERNALSYM SERVICE_XACTSRV}
  SERVICE_LM20_XACTSRV      = SERVICE_XACTSRV;
  {$EXTERNALSYM SERVICE_LM20_XACTSRV}

  SERVICE_TCPIP             = 'TCPIP';
  {$EXTERNALSYM SERVICE_TCPIP}
  SERVICE_LM20_TCPIP        = SERVICE_TCPIP;
  {$EXTERNALSYM SERVICE_LM20_TCPIP}

  SERVICE_NBT               = 'NBT';
  {$EXTERNALSYM SERVICE_NBT}
  SERVICE_LM20_NBT          = SERVICE_NBT;
  {$EXTERNALSYM SERVICE_LM20_NBT}

  SERVICE_LMHOSTS           = 'LMHOSTS';
  {$EXTERNALSYM SERVICE_LMHOSTS}
  SERVICE_LM20_LMHOSTS      = SERVICE_LMHOSTS;
  {$EXTERNALSYM SERVICE_LM20_LMHOSTS}

  SERVICE_TELNET            = 'Telnet';
  {$EXTERNALSYM SERVICE_TELNET}
  SERVICE_LM20_TELNET       = SERVICE_TELNET;
  {$EXTERNALSYM SERVICE_LM20_TELNET}

  SERVICE_SCHEDULE          = 'Schedule';
  {$EXTERNALSYM SERVICE_SCHEDULE}
  SERVICE_LM20_SCHEDULE     = SERVICE_SCHEDULE;
  {$EXTERNALSYM SERVICE_LM20_SCHEDULE}

  SERVICE_NTLMSSP           = 'NtLmSsp';
  {$EXTERNALSYM SERVICE_NTLMSSP}

  SERVICE_DHCP              = 'DHCP';
  {$EXTERNALSYM SERVICE_DHCP}
  SERVICE_LM20_DHCP         = SERVICE_DHCP;
  {$EXTERNALSYM SERVICE_LM20_DHCP}

  SERVICE_NWSAP             = 'NwSapAgent';
  {$EXTERNALSYM SERVICE_NWSAP}
  SERVICE_LM20_NWSAP        = SERVICE_NWSAP;
  {$EXTERNALSYM SERVICE_LM20_NWSAP}
  NWSAP_DISPLAY_NAME        = 'NW Sap Agent';
  {$EXTERNALSYM NWSAP_DISPLAY_NAME}

  SERVICE_NWCS              = 'NWCWorkstation';
  {$EXTERNALSYM SERVICE_NWCS}
  SERVICE_DNS_CACHE         = 'DnsCache';
  {$EXTERNALSYM SERVICE_DNS_CACHE}

  SERVICE_W32TIME           = 'w32time';
  {$EXTERNALSYM SERVICE_W32TIME}
  SERVCE_LM20_W32TIME       = SERVICE_W32TIME;
  {$EXTERNALSYM SERVCE_LM20_W32TIME}

  SERVICE_KDC               = 'kdc';
  {$EXTERNALSYM SERVICE_KDC}
  SERVICE_LM20_KDC          = SERVICE_KDC;
  {$EXTERNALSYM SERVICE_LM20_KDC}

  SERVICE_RPCLOCATOR        = 'RPCLOCATOR';
  {$EXTERNALSYM SERVICE_RPCLOCATOR}
  SERVICE_LM20_RPCLOCATOR   = SERVICE_RPCLOCATOR;
  {$EXTERNALSYM SERVICE_LM20_RPCLOCATOR}

  SERVICE_TRKSVR            = 'TrkSvr';
  {$EXTERNALSYM SERVICE_TRKSVR}
  SERVICE_LM20_TRKSVR       = SERVICE_TRKSVR;
  {$EXTERNALSYM SERVICE_LM20_TRKSVR}

  SERVICE_TRKWKS            = 'TrkWks';
  {$EXTERNALSYM SERVICE_TRKWKS}
  SERVICE_LM20_TRKWKS       = SERVICE_TRKWKS;
  {$EXTERNALSYM SERVICE_LM20_TRKWKS}

  SERVICE_NTFRS             = 'NtFrs';
  {$EXTERNALSYM SERVICE_NTFRS}
  SERVICE_LM20_NTFRS        = SERVICE_NTFRS;
  {$EXTERNALSYM SERVICE_LM20_NTFRS}

  SERVICE_ISMSERV           = 'IsmServ';
  {$EXTERNALSYM SERVICE_ISMSERV}
  SERVICE_LM20_ISMSERV      = SERVICE_ISMSERV;
  {$EXTERNALSYM SERVICE_LM20_ISMSERV}

// Translated from LMUSEFLG.H

// Definition for NetWkstaTransportDel and NetUseDel deletion force levels

const
  {$EXTERNALSYM USE_NOFORCE}
  USE_NOFORCE = 0;
  {$EXTERNALSYM USE_FORCE}
  USE_FORCE = 1;
  {$EXTERNALSYM USE_LOTS_OF_FORCE}
  USE_LOTS_OF_FORCE = 2;

// Translated from LMDFS.H

// DFS Volume state

const
  DFS_VOLUME_STATE_OK            = 1;
  {$EXTERNALSYM DFS_VOLUME_STATE_OK}
  DFS_VOLUME_STATE_INCONSISTENT  = 2;
  {$EXTERNALSYM DFS_VOLUME_STATE_INCONSISTENT}
  DFS_VOLUME_STATE_OFFLINE       = 3;
  {$EXTERNALSYM DFS_VOLUME_STATE_OFFLINE}
  DFS_VOLUME_STATE_ONLINE        = 4;
  {$EXTERNALSYM DFS_VOLUME_STATE_ONLINE}

// DFS Storage State

  DFS_STORAGE_STATE_OFFLINE      = 1;
  {$EXTERNALSYM DFS_STORAGE_STATE_OFFLINE}
  DFS_STORAGE_STATE_ONLINE       = 2;
  {$EXTERNALSYM DFS_STORAGE_STATE_ONLINE}
  DFS_STORAGE_STATE_ACTIVE       = 4;
  {$EXTERNALSYM DFS_STORAGE_STATE_ACTIVE}

// Level 1:

type
  PDfsInfo1 = ^TDfsInfo1;
  _DFS_INFO_1 = packed record
    EntryPath: LPWSTR;                // Dfs name for the top of this piece of storage
  end;
  {$EXTERNALSYM _DFS_INFO_1}
  TDfsInfo1 = _DFS_INFO_1;
  DFS_INFO_1 = _DFS_INFO_1;
  {$EXTERNALSYM DFS_INFO_1}

// Level 2:

  PDfsInfo2 = ^TDfsInfo2;
  _DFS_INFO_2 = packed record
    EntryPath: LPWSTR;                // Dfs name for the top of this volume
    Comment: LPWSTR;                  // Comment for this volume
    State: DWORD;                     // State of this volume, one of DFS_VOLUME_STATE_*
    NumberOfStorages: DWORD;          // Number of storages for this volume
  end;
  {$EXTERNALSYM _DFS_INFO_2}
  TDfsInfo2 = _DFS_INFO_2;
  DFS_INFO_2 = _DFS_INFO_2;
  {$EXTERNALSYM DFS_INFO_2}


  PDfsStorageInfo = ^TDfsStorageInfo;
  _DFS_STORAGE_INFO = packed record
    State: ULONG;                     // State of this storage, one of DFS_STORAGE_STATE_*
                                      // possibly OR'd with DFS_STORAGE_STATE_ACTIVE
    ServerName: LPWSTR;               // Name of server hosting this storage
    ShareName: LPWSTR;                // Name of share hosting this storage
  end;
  {$EXTERNALSYM _DFS_STORAGE_INFO}
  TDfsStorageInfo = _DFS_STORAGE_INFO;
  DFS_STORAGE_INFO = _DFS_STORAGE_INFO;
  {$EXTERNALSYM DFS_STORAGE_INFO}

// Level 3:

  PDfsInfo3 = ^TDfsInfo3;
  _DFS_INFO_3 = packed record
    EntryPath: LPWSTR;                // Dfs name for the top of this volume
    Comment: LPWSTR;                  // Comment for this volume
    State: DWORD;                     // State of this volume, one of DFS_VOLUME_STATE_*
    NumberOfStorages: DWORD;          // Number of storage servers for this volume
    Storage: PDfsStorageInfo;         // An array (of NumberOfStorages elements) of storage-specific information.
  end;
  {$EXTERNALSYM _DFS_INFO_3}
  TDfsInfo3 = _DFS_INFO_3;
  DFS_INFO_3 = _DFS_INFO_3;
  {$EXTERNALSYM DFS_INFO_3}

// Level 4:

  PDfsInfo4 = ^TDfsInfo4;
  _DFS_INFO_4 = packed record
    EntryPath: LPWSTR;                // Dfs name for the top of this volume
    Comment: LPWSTR;                  // Comment for this volume
    State: DWORD;                     // State of this volume, one of DFS_VOLUME_STATE_*
    Timeout: ULONG;                   // Timeout, in seconds, of this junction point
    Guid: TGUID;                      // Guid of this junction point
    NumberOfStorages: DWORD;          // Number of storage servers for this volume
    Storage: PDfsStorageInfo;         // An array (of NumberOfStorages elements) of storage-specific information.
  end;
  {$EXTERNALSYM _DFS_INFO_4}
  TDfsInfo4 = _DFS_INFO_4;
  DFS_INFO_4 = _DFS_INFO_4;
  {$EXTERNALSYM DFS_INFO_4}

// Level 100:

  PDfsInfo100 = ^TDfsInfo100;
  _DFS_INFO_100 = packed record
    Comment: LPWSTR;                  // Comment for this volume or storage
  end;
  {$EXTERNALSYM _DFS_INFO_100}
  TDfsInfo100 = _DFS_INFO_100;
  DFS_INFO_100 = _DFS_INFO_100;
  {$EXTERNALSYM DFS_INFO_100}

// Level 101:

  PDfsInfo101 = ^TDfsInfo101;
  _DFS_INFO_101 = packed record
    State: DWORD;                     // State of this storage, one of DFS_STORAGE_STATE_*
                                      // possibly OR'd with DFS_STORAGE_STATE_ACTIVE
  end;
  {$EXTERNALSYM _DFS_INFO_101}
  TDfsInfo101 = _DFS_INFO_101;
  DFS_INFO_101 = _DFS_INFO_101;
  {$EXTERNALSYM DFS_INFO_101}

// Level 102:

  PDfsInfo102 = ^TDfsInfo102;
  _DFS_INFO_102 = packed record
    Timeout: ULONG;                   // Timeout, in seconds, of the junction
  end;
  {$EXTERNALSYM _DFS_INFO_102}
  TDfsInfo102 = _DFS_INFO_102;
  DFS_INFO_102 = _DFS_INFO_102;
  {$EXTERNALSYM DFS_INFO_102}

// Level 200:

  PDfsInfo200 = ^TDfsInfo200;
  _DFS_INFO_200 = packed record
    FtDfsName: LPWSTR;                // FtDfs name
  end;
  {$EXTERNALSYM _DFS_INFO_200}
  TDfsInfo200 = _DFS_INFO_200;
  DFS_INFO_200 = _DFS_INFO_200;
  {$EXTERNALSYM DFS_INFO_200}


// Add a new volume or additional storage for an existing volume at
// DfsEntryPath.

function NetDfsAdd(DfsEntryPath, ServerName, ShareName, Comment: LPWSTR;
  Flags: DWORD): NET_API_STATUS; stdcall;
{$EXTERNALSYM NetDfsAdd}

// Flags:

const
  DFS_ADD_VOLUME          = 1;   // Add a new volume to the DFS if not already there
  {$EXTERNALSYM DFS_ADD_VOLUME}
  DFS_RESTORE_VOLUME      = 2;   // Volume/Replica is being restored - do not verify share etc.
  {$EXTERNALSYM DFS_RESTORE_VOLUME}

// Setup/teardown API's for standard and FtDfs roots.

function NetDfsAddStdRoot(ServerName, RootShare, Comment: LPWSTR;
  Flags: DWORD): NET_API_STATUS; stdcall;
{$EXTERNALSYM NetDfsAddStdRoot}

function NetDfsRemoveStdRoot(ServerName: LPWSTR; RootShare: LPWSTR;
  Flags: DWORD): NET_API_STATUS; stdcall;
{$EXTERNALSYM NetDfsRemoveStdRoot}

function NetDfsAddFtRoot(ServerName, RootShare, FtDfsName, Comment: LPWSTR;
  Flags: DWORD): NET_API_STATUS; stdcall;
{$EXTERNALSYM NetDfsAddFtRoot}

function NetDfsRemoveFtRoot(ServerName, RootShare, FtDfsName: LPWSTR;
  Flags: DWORD): NET_API_STATUS; stdcall;
{$EXTERNALSYM NetDfsRemoveFtRoot}

function NetDfsRemoveFtRootForced(DomainName, ServerName, RootShare, FtDfsName: LPWSTR;
  Flags: DWORD): NET_API_STATUS; stdcall;
{$EXTERNALSYM NetDfsRemoveFtRootForced}

// Call to reinitialize the dfsmanager on a machine

function NetDfsManagerInitialize(ServerName: LPWSTR; Flags: DWORD): NET_API_STATUS; stdcall;
{$EXTERNALSYM NetDfsManagerInitialize}

function NetDfsAddStdRootForced(ServerName, RootShare, Comment, Store: LPWSTR): NET_API_STATUS; stdcall;
{$EXTERNALSYM NetDfsAddStdRootForced}

function NetDfsGetDcAddress(ServerName: LPWSTR; DcIpAddress: LPWSTR;
  var IsRoot: Boolean; var Timeout: ULONG): NET_API_STATUS; stdcall;
{$EXTERNALSYM NetDfsGetDcAddress}

function NetDfsSetDcAddress(ServerName: LPWSTR; DcIpAddress: LPWSTR;
  Timeout: ULONG; Flags: DWORD): NET_API_STATUS; stdcall;
{$EXTERNALSYM NetDfsSetDcAddress}

// Flags for NetDfsSetDcAddress()

const
  NET_DFS_SETDC_FLAGS                 = $00000000;
  {$EXTERNALSYM NET_DFS_SETDC_FLAGS}
  NET_DFS_SETDC_TIMEOUT               = $00000001;
  {$EXTERNALSYM NET_DFS_SETDC_TIMEOUT}
  NET_DFS_SETDC_INITPKT               = $00000002;
  {$EXTERNALSYM NET_DFS_SETDC_INITPKT}

// Structures used for site reporting

type
  PDfsSitenameInfo = ^TDfsSitenameInfo;
  DFS_SITENAME_INFO = packed record
    SiteFlags: ULONG;     // Below
    SiteName: LPWSTR;
  end;
  {$EXTERNALSYM DFS_SITENAME_INFO}
  TDfsSitenameInfo = DFS_SITENAME_INFO;


const
  DFS_SITE_PRIMARY    = $1;     // This site returned by DsGetSiteName()
  {$EXTERNALSYM DFS_SITE_PRIMARY}

type
  PDfsSitelistInfo = ^TDfsSitelistInfo;
  DFS_SITELIST_INFO = packed record
    cSites: ULONG;
    Site: TDfsSitenameInfo;
  end;
  {$EXTERNALSYM DFS_SITELIST_INFO}
  TDfsSitelistInfo = DFS_SITELIST_INFO;

// Remove a volume or additional storage for volume from the Dfs at
// DfsEntryPath. When applied to the last storage in a volume, removes
// the volume from the DFS.

function NetDfsRemove(DfsEntryPath, ServerName, ShareName: LPWSTR): NET_API_STATUS; stdcall;
{$EXTERNALSYM NetDfsRemove}

// Get information about all of the volumes in the Dfs. DfsName is
// the "server" part of the UNC name used to refer to this particular Dfs.
//
// Valid levels are 1-4, 200

function NetDfsEnum(DfsName: LPWSTR; Level: DWORD; PrefMaxLen: DWORD;
  Buffer: Pointer; var EntriesRead: DWORD; ResumeHandle: PDWORD): NET_API_STATUS; stdcall;
{$EXTERNALSYM NetDfsEnum}

// Get information about the volume or storage.
// If ServerName and ShareName are specified, the information returned
// is specific to that server and share, else the information is specific
// to the volume as a whole.
//
// Valid levels are 1-4, 100

function NetDfsGetInfo(DfsEntryPath, ServerName, ShareName: LPWSTR;
  Level: DWORD; Buffer: Pointer): NET_API_STATUS; stdcall;
{$EXTERNALSYM NetDfsGetInfo}

// Set info about the volume or storage.
// If ServerName and ShareName are specified, the information set is
// specific to that server and share, else the information is specific
// to the volume as a whole.
//
// Valid levels are 100, 101 and 102

function NetDfsSetInfo(DfsEntryPath, ServerName, ShareName: LPWSTR;
  Level: DWORD; Buffer: Pointer): NET_API_STATUS; stdcall;
{$EXTERNALSYM NetDfsSetInfo}

// Get client's cached information about the volume or storage.
// If ServerName and ShareName are specified, the information returned
// is specific to that server and share, else the information is specific
// to the volume as a whole.
//
// Valid levels are 1-4

function NetDfsGetClientInfo(DfsEntryPath, ServerName, ShareName: LPWSTR;
  Level: DWORD; Buffer: Pointer): NET_API_STATUS; stdcall;
{$EXTERNALSYM NetDfsGetClientInfo}

// Set client's cached info about the volume or storage.
// If ServerName and ShareName are specified, the information set is
// specific to that server and share, else the information is specific
// to the volume as a whole.
//
// Valid levels are 101 and 102.

function NetDfsSetClientInfo(DfsEntryPath, ServerName, ShareName: LPWSTR;
  Level: DWORD; Buffer: Pointer): NET_API_STATUS; stdcall;
{$EXTERNALSYM NetDfsSetClientInfo}

// Move a DFS volume and all subordinate volumes from one place in the
// DFS to another place in the DFS.

function NetDfsMove(DfsEntryPath, DfsNewEntryPath: LPWSTR): NET_API_STATUS; stdcall;
{$EXTERNALSYM NetDfsMove}

function NetDfsRename(Path, NewPath: LPWSTR): NET_API_STATUS; stdcall;
{$EXTERNALSYM NetDfsRename}

implementation

const
  netapi32lib = 'netapi32.dll';
  {$NODEFINE netapi32lib}

// LMACCESS.H


{$IFDEF DYNAMIC_LINK}
var
  _NetUserAdd: Pointer;

function NetUserAdd;
begin
  GetProcedureAddress(_NetUserAdd, netapi32lib, 'NetUserAdd');
  asm
    mov esp, ebp
    pop ebp
    jmp [_NetUserAdd]
  end;
end;
{$ELSE}
function NetUserAdd; external netapi32lib name 'NetUserAdd';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _NetUserEnum: Pointer;

function NetUserEnum;
begin
  GetProcedureAddress(_NetUserEnum, netapi32lib, 'NetUserEnum');
  asm
    mov esp, ebp
    pop ebp
    jmp [_NetUserEnum]
  end;
end;
{$ELSE}
function NetUserEnum; external netapi32lib name 'NetUserEnum';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _NetUserGetInfo: Pointer;

function NetUserGetInfo;
begin
  GetProcedureAddress(_NetUserGetInfo, netapi32lib, 'NetUserGetInfo');
  asm
    mov esp, ebp
    pop ebp
    jmp [_NetUserGetInfo]
  end;
end;
{$ELSE}
function NetUserGetInfo; external netapi32lib name 'NetUserGetInfo';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _NetUserSetInfo: Pointer;

function NetUserSetInfo;
begin
  GetProcedureAddress(_NetUserSetInfo, netapi32lib, 'NetUserSetInfo');
  asm
    mov esp, ebp
    pop ebp
    jmp [_NetUserSetInfo]
  end;
end;
{$ELSE}
function NetUserSetInfo; external netapi32lib name 'NetUserSetInfo';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _NetUserDel: Pointer;

function NetUserDel;
begin
  GetProcedureAddress(_NetUserDel, netapi32lib, 'NetUserDel');
  asm
    mov esp, ebp
    pop ebp
    jmp [_NetUserDel]
  end;
end;
{$ELSE}
function NetUserDel; external netapi32lib name 'NetUserDel';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _NetUserGetGroups: Pointer;

function NetUserGetGroups;
begin
  GetProcedureAddress(_NetUserGetGroups, netapi32lib, 'NetUserGetGroups');
  asm
    mov esp, ebp
    pop ebp
    jmp [_NetUserGetGroups]
  end;
end;
{$ELSE}
function NetUserGetGroups; external netapi32lib name 'NetUserGetGroups';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _NetUserSetGroups: Pointer;

function NetUserSetGroups;
begin
  GetProcedureAddress(_NetUserSetGroups, netapi32lib, 'NetUserSetGroups');
  asm
    mov esp, ebp
    pop ebp
    jmp [_NetUserSetGroups]
  end;
end;
{$ELSE}
function NetUserSetGroups; external netapi32lib name 'NetUserSetGroups';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _NetUserGetLocalGroups: Pointer;

function NetUserGetLocalGroups;
begin
  GetProcedureAddress(_NetUserGetLocalGroups, netapi32lib, 'NetUserGetLocalGroups');
  asm
    mov esp, ebp
    pop ebp
    jmp [_NetUserGetLocalGroups]
  end;
end;
{$ELSE}
function NetUserGetLocalGroups; external netapi32lib name 'NetUserGetLocalGroups';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _NetUserModalsGet: Pointer;

function NetUserModalsGet;
begin
  GetProcedureAddress(_NetUserModalsGet, netapi32lib, 'NetUserModalsGet');
  asm
    mov esp, ebp
    pop ebp
    jmp [_NetUserModalsGet]
  end;
end;
{$ELSE}
function NetUserModalsGet; external netapi32lib name 'NetUserModalsGet';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _NetUserModalsSet: Pointer;

function NetUserModalsSet;
begin
  GetProcedureAddress(_NetUserModalsSet, netapi32lib, 'NetUserModalsSet');
  asm
    mov esp, ebp
    pop ebp
    jmp [_NetUserModalsSet]
  end;
end;
{$ELSE}
function NetUserModalsSet; external netapi32lib name 'NetUserModalsSet';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _NetUserChangePassword: Pointer;

function NetUserChangePassword;
begin
  GetProcedureAddress(_NetUserChangePassword, netapi32lib, 'NetUserChangePassword');
  asm
    mov esp, ebp
    pop ebp
    jmp [_NetUserChangePassword]
  end;
end;
{$ELSE}
function NetUserChangePassword; external netapi32lib name 'NetUserChangePassword';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _NetGroupAdd: Pointer;

function NetGroupAdd;
begin
  GetProcedureAddress(_NetGroupAdd, netapi32lib, 'NetGroupAdd');
  asm
    mov esp, ebp
    pop ebp
    jmp [_NetGroupAdd]
  end;
end;
{$ELSE}
function NetGroupAdd; external netapi32lib name 'NetGroupAdd';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _NetGroupAddUser: Pointer;

function NetGroupAddUser;
begin
  GetProcedureAddress(_NetGroupAddUser, netapi32lib, 'NetGroupAddUser');
  asm
    mov esp, ebp
    pop ebp
    jmp [_NetGroupAddUser]
  end;
end;
{$ELSE}
function NetGroupAddUser; external netapi32lib name 'NetGroupAddUser';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _NetGroupEnum: Pointer;

function NetGroupEnum;
begin
  GetProcedureAddress(_NetGroupEnum, netapi32lib, 'NetGroupEnum');
  asm
    mov esp, ebp
    pop ebp
    jmp [_NetGroupEnum]
  end;
end;
{$ELSE}
function NetGroupEnum; external netapi32lib name 'NetGroupEnum';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _NetGroupGetInfo: Pointer;

function NetGroupGetInfo;
begin
  GetProcedureAddress(_NetGroupGetInfo, netapi32lib, 'NetGroupGetInfo');
  asm
    mov esp, ebp
    pop ebp
    jmp [_NetGroupGetInfo]
  end;
end;
{$ELSE}
function NetGroupGetInfo; external netapi32lib name 'NetGroupGetInfo';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _NetGroupSetInfo: Pointer;

function NetGroupSetInfo;
begin
  GetProcedureAddress(_NetGroupSetInfo, netapi32lib, 'NetGroupSetInfo');
  asm
    mov esp, ebp
    pop ebp
    jmp [_NetGroupSetInfo]
  end;
end;
{$ELSE}
function NetGroupSetInfo; external netapi32lib name 'NetGroupSetInfo';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _NetGroupDel: Pointer;

function NetGroupDel;
begin
  GetProcedureAddress(_NetGroupDel, netapi32lib, 'NetGroupDel');
  asm
    mov esp, ebp
    pop ebp
    jmp [_NetGroupDel]
  end;
end;
{$ELSE}
function NetGroupDel; external netapi32lib name 'NetGroupDel';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _NetGroupDelUser: Pointer;

function NetGroupDelUser;
begin
  GetProcedureAddress(_NetGroupDelUser, netapi32lib, 'NetGroupDelUser');
  asm
    mov esp, ebp
    pop ebp
    jmp [_NetGroupDelUser]
  end;
end;
{$ELSE}
function NetGroupDelUser; external netapi32lib name 'NetGroupDelUser';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _NetGroupGetUsers: Pointer;

function NetGroupGetUsers;
begin
  GetProcedureAddress(_NetGroupGetUsers, netapi32lib, 'NetGroupGetUsers');
  asm
    mov esp, ebp
    pop ebp
    jmp [_NetGroupGetUsers]
  end;
end;
{$ELSE}
function NetGroupGetUsers; external netapi32lib name 'NetGroupGetUsers';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _NetGroupSetUsers: Pointer;

function NetGroupSetUsers;
begin
  GetProcedureAddress(_NetGroupSetUsers, netapi32lib, 'NetGroupSetUsers');
  asm
    mov esp, ebp
    pop ebp
    jmp [_NetGroupSetUsers]
  end;
end;
{$ELSE}
function NetGroupSetUsers; external netapi32lib name 'NetGroupSetUsers';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _NetLocalGroupAdd: Pointer;

function NetLocalGroupAdd;
begin
  GetProcedureAddress(_NetLocalGroupAdd, netapi32lib, 'NetLocalGroupAdd');
  asm
    mov esp, ebp
    pop ebp
    jmp [_NetLocalGroupAdd]
  end;
end;
{$ELSE}
function NetLocalGroupAdd; external netapi32lib name 'NetLocalGroupAdd';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _NetLocalGroupAddMember: Pointer;

function NetLocalGroupAddMember;
begin
  GetProcedureAddress(_NetLocalGroupAddMember, netapi32lib, 'NetLocalGroupAddMember');
  asm
    mov esp, ebp
    pop ebp
    jmp [_NetLocalGroupAddMember]
  end;
end;
{$ELSE}
function NetLocalGroupAddMember; external netapi32lib name 'NetLocalGroupAddMember';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _NetLocalGroupEnum: Pointer;

function NetLocalGroupEnum;
begin
  GetProcedureAddress(_NetLocalGroupEnum, netapi32lib, 'NetLocalGroupEnum');
  asm
    mov esp, ebp
    pop ebp
    jmp [_NetLocalGroupEnum]
  end;
end;
{$ELSE}
function NetLocalGroupEnum; external netapi32lib name 'NetLocalGroupEnum';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _NetLocalGroupGetInfo: Pointer;

function NetLocalGroupGetInfo;
begin
  GetProcedureAddress(_NetLocalGroupGetInfo, netapi32lib, 'NetLocalGroupGetInfo');
  asm
    mov esp, ebp
    pop ebp
    jmp [_NetLocalGroupGetInfo]
  end;
end;
{$ELSE}
function NetLocalGroupGetInfo; external netapi32lib name 'NetLocalGroupGetInfo';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _NetLocalGroupSetInfo: Pointer;

function NetLocalGroupSetInfo;
begin
  GetProcedureAddress(_NetLocalGroupSetInfo, netapi32lib, 'NetLocalGroupSetInfo');
  asm
    mov esp, ebp
    pop ebp
    jmp [_NetLocalGroupSetInfo]
  end;
end;
{$ELSE}
function NetLocalGroupSetInfo; external netapi32lib name 'NetLocalGroupSetInfo';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _NetLocalGroupDel: Pointer;

function NetLocalGroupDel;
begin
  GetProcedureAddress(_NetLocalGroupDel, netapi32lib, 'NetLocalGroupDel');
  asm
    mov esp, ebp
    pop ebp
    jmp [_NetLocalGroupDel]
  end;
end;
{$ELSE}
function NetLocalGroupDel; external netapi32lib name 'NetLocalGroupDel';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _NetLocalGroupDelMember: Pointer;

function NetLocalGroupDelMember;
begin
  GetProcedureAddress(_NetLocalGroupDelMember, netapi32lib, 'NetLocalGroupDelMember');
  asm
    mov esp, ebp
    pop ebp
    jmp [_NetLocalGroupDelMember]
  end;
end;
{$ELSE}
function NetLocalGroupDelMember; external netapi32lib name 'NetLocalGroupDelMember';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _NetLocalGroupGetMembers: Pointer;

function NetLocalGroupGetMembers;
begin
  GetProcedureAddress(_NetLocalGroupGetMembers, netapi32lib, 'NetLocalGroupGetMembers');
  asm
    mov esp, ebp
    pop ebp
    jmp [_NetLocalGroupGetMembers]
  end;
end;
{$ELSE}
function NetLocalGroupGetMembers; external netapi32lib name 'NetLocalGroupGetMembers';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _NetLocalGroupSetMembers: Pointer;

function NetLocalGroupSetMembers;
begin
  GetProcedureAddress(_NetLocalGroupSetMembers, netapi32lib, 'NetLocalGroupSetMembers');
  asm
    mov esp, ebp
    pop ebp
    jmp [_NetLocalGroupSetMembers]
  end;
end;
{$ELSE}
function NetLocalGroupSetMembers; external netapi32lib name 'NetLocalGroupSetMembers';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _NetLocalGroupAddMembers: Pointer;

function NetLocalGroupAddMembers;
begin
  GetProcedureAddress(_NetLocalGroupAddMembers, netapi32lib, 'NetLocalGroupAddMembers');
  asm
    mov esp, ebp
    pop ebp
    jmp [_NetLocalGroupAddMembers]
  end;
end;
{$ELSE}
function NetLocalGroupAddMembers; external netapi32lib name 'NetLocalGroupAddMembers';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _NetLocalGroupDelMembers: Pointer;

function NetLocalGroupDelMembers;
begin
  GetProcedureAddress(_NetLocalGroupDelMembers, netapi32lib, 'NetLocalGroupDelMembers');
  asm
    mov esp, ebp
    pop ebp
    jmp [_NetLocalGroupDelMembers]
  end;
end;
{$ELSE}
function NetLocalGroupDelMembers; external netapi32lib name 'NetLocalGroupDelMembers';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _NetQueryDisplayInformation: Pointer;

function NetQueryDisplayInformation;
begin
  GetProcedureAddress(_NetQueryDisplayInformation, netapi32lib, 'NetQueryDisplayInformation');
  asm
    mov esp, ebp
    pop ebp
    jmp [_NetQueryDisplayInformation]
  end;
end;
{$ELSE}
function NetQueryDisplayInformation; external netapi32lib name 'NetQueryDisplayInformation';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _NetGetDisplayInformationIndex: Pointer;

function NetGetDisplayInformationIndex;
begin
  GetProcedureAddress(_NetGetDisplayInformationIndex, netapi32lib, 'NetGetDisplayInformationIndex');
  asm
    mov esp, ebp
    pop ebp
    jmp [_NetGetDisplayInformationIndex]
  end;
end;
{$ELSE}
function NetGetDisplayInformationIndex; external netapi32lib name 'NetGetDisplayInformationIndex';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _NetAccessAdd: Pointer;

function NetAccessAdd;
begin
  GetProcedureAddress(_NetAccessAdd, netapi32lib, 'NetAccessAdd');
  asm
    mov esp, ebp
    pop ebp
    jmp [_NetAccessAdd]
  end;
end;
{$ELSE}
function NetAccessAdd; external netapi32lib name 'NetAccessAdd';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _NetAccessEnum: Pointer;

function NetAccessEnum;
begin
  GetProcedureAddress(_NetAccessEnum, netapi32lib, 'NetAccessEnum');
  asm
    mov esp, ebp
    pop ebp
    jmp [_NetAccessEnum]
  end;
end;
{$ELSE}
function NetAccessEnum; external netapi32lib name 'NetAccessEnum';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _NetAccessGetInfo: Pointer;

function NetAccessGetInfo;
begin
  GetProcedureAddress(_NetAccessGetInfo, netapi32lib, 'NetAccessGetInfo');
  asm
    mov esp, ebp
    pop ebp
    jmp [_NetAccessGetInfo]
  end;
end;
{$ELSE}
function NetAccessGetInfo; external netapi32lib name 'NetAccessGetInfo';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _NetAccessSetInfo: Pointer;

function NetAccessSetInfo;
begin
  GetProcedureAddress(_NetAccessSetInfo, netapi32lib, 'NetAccessSetInfo');
  asm
    mov esp, ebp
    pop ebp
    jmp [_NetAccessSetInfo]
  end;
end;
{$ELSE}
function NetAccessSetInfo; external netapi32lib name 'NetAccessSetInfo';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _NetAccessDel: Pointer;

function NetAccessDel;
begin
  GetProcedureAddress(_NetAccessDel, netapi32lib, 'NetAccessDel');
  asm
    mov esp, ebp
    pop ebp
    jmp [_NetAccessDel]
  end;
end;
{$ELSE}
function NetAccessDel; external netapi32lib name 'NetAccessDel';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _NetAccessGetUserPerms: Pointer;

function NetAccessGetUserPerms;
begin
  GetProcedureAddress(_NetAccessGetUserPerms, netapi32lib, 'NetAccessGetUserPerms');
  asm
    mov esp, ebp
    pop ebp
    jmp [_NetAccessGetUserPerms]
  end;
end;
{$ELSE}
function NetAccessGetUserPerms; external netapi32lib name 'NetAccessGetUserPerms';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _NetGetDCName: Pointer;

function NetGetDCName;
begin
  GetProcedureAddress(_NetGetDCName, netapi32lib, 'NetGetDCName');
  asm
    mov esp, ebp
    pop ebp
    jmp [_NetGetDCName]
  end;
end;
{$ELSE}
function NetGetDCName; external netapi32lib name 'NetGetDCName';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _NetGetAnyDCName: Pointer;

function NetGetAnyDCName;
begin
  GetProcedureAddress(_NetGetAnyDCName, netapi32lib, 'NetGetAnyDCName');
  asm
    mov esp, ebp
    pop ebp
    jmp [_NetGetAnyDCName]
  end;
end;
{$ELSE}
function NetGetAnyDCName; external netapi32lib name 'NetGetAnyDCName';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _I_NetLogonControl: Pointer;

function I_NetLogonControl;
begin
  GetProcedureAddress(_I_NetLogonControl, netapi32lib, 'I_NetLogonControl');
  asm
    mov esp, ebp
    pop ebp
    jmp [_I_NetLogonControl]
  end;
end;
{$ELSE}
function I_NetLogonControl; external netapi32lib name 'I_NetLogonControl';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _I_NetLogonControl2: Pointer;

function I_NetLogonControl2;
begin
  GetProcedureAddress(_I_NetLogonControl2, netapi32lib, 'I_NetLogonControl2');
  asm
    mov esp, ebp
    pop ebp
    jmp [_I_NetLogonControl2]
  end;
end;
{$ELSE}
function I_NetLogonControl2; external netapi32lib name 'I_NetLogonControl2';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _NetEnumerateTrustedDomains: Pointer;

function NetEnumerateTrustedDomains;
begin
  GetProcedureAddress(_NetEnumerateTrustedDomains, netapi32lib, 'NetEnumerateTrustedDomains');
  asm
    mov esp, ebp
    pop ebp
    jmp [_NetEnumerateTrustedDomains]
  end;
end;
{$ELSE}
function NetEnumerateTrustedDomains; external netapi32lib name 'NetEnumerateTrustedDomains';
{$ENDIF DYNAMIC_LINK}

// LMALERT.H

function ALERT_OTHER_INFO(x: Pointer): Pointer;
begin
  Result := PChar(x) + Sizeof(STD_ALERT);
end;

function ALERT_VAR_DATA(const p): Pointer;
begin
  Result := PChar(p) + Sizeof(p);
end;


{$IFDEF DYNAMIC_LINK}
var
  _NetAlertRaise: Pointer;

function NetAlertRaise;
begin
  GetProcedureAddress(_NetAlertRaise, netapi32lib, 'NetAlertRaise');
  asm
    mov esp, ebp
    pop ebp
    jmp [_NetAlertRaise]
  end;
end;
{$ELSE}
function NetAlertRaise; external netapi32lib name 'NetAlertRaise';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _NetAlertRaiseEx: Pointer;

function NetAlertRaiseEx;
begin
  GetProcedureAddress(_NetAlertRaiseEx, netapi32lib, 'NetAlertRaiseEx');
  asm
    mov esp, ebp
    pop ebp
    jmp [_NetAlertRaiseEx]
  end;
end;
{$ELSE}
function NetAlertRaiseEx; external netapi32lib name 'NetAlertRaiseEx';
{$ENDIF DYNAMIC_LINK}

// LMSHARE.H


{$IFDEF DYNAMIC_LINK}
var
  _NetShareAdd: Pointer;

function NetShareAdd;
begin
  GetProcedureAddress(_NetShareAdd, netapi32lib, 'NetShareAdd');
  asm
    mov esp, ebp
    pop ebp
    jmp [_NetShareAdd]
  end;
end;
{$ELSE}
function NetShareAdd; external netapi32lib name 'NetShareAdd';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _NetShareEnum: Pointer;

function NetShareEnum;
begin
  GetProcedureAddress(_NetShareEnum, netapi32lib, 'NetShareEnum');
  asm
    mov esp, ebp
    pop ebp
    jmp [_NetShareEnum]
  end;
end;
{$ELSE}
function NetShareEnum; external netapi32lib name 'NetShareEnum';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _NetShareEnumSticky: Pointer;

function NetShareEnumSticky;
begin
  GetProcedureAddress(_NetShareEnumSticky, netapi32lib, 'NetShareEnumSticky');
  asm
    mov esp, ebp
    pop ebp
    jmp [_NetShareEnumSticky]
  end;
end;
{$ELSE}
function NetShareEnumSticky; external netapi32lib name 'NetShareEnumSticky';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _NetShareGetInfo: Pointer;

function NetShareGetInfo;
begin
  GetProcedureAddress(_NetShareGetInfo, netapi32lib, 'NetShareGetInfo');
  asm
    mov esp, ebp
    pop ebp
    jmp [_NetShareGetInfo]
  end;
end;
{$ELSE}
function NetShareGetInfo; external netapi32lib name 'NetShareGetInfo';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _NetShareSetInfo: Pointer;

function NetShareSetInfo;
begin
  GetProcedureAddress(_NetShareSetInfo, netapi32lib, 'NetShareSetInfo');
  asm
    mov esp, ebp
    pop ebp
    jmp [_NetShareSetInfo]
  end;
end;
{$ELSE}
function NetShareSetInfo; external netapi32lib name 'NetShareSetInfo';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _NetShareDel: Pointer;

function NetShareDel;
begin
  GetProcedureAddress(_NetShareDel, netapi32lib, 'NetShareDel');
  asm
    mov esp, ebp
    pop ebp
    jmp [_NetShareDel]
  end;
end;
{$ELSE}
function NetShareDel; external netapi32lib name 'NetShareDel';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _NetShareDelSticky: Pointer;

function NetShareDelSticky;
begin
  GetProcedureAddress(_NetShareDelSticky, netapi32lib, 'NetShareDelSticky');
  asm
    mov esp, ebp
    pop ebp
    jmp [_NetShareDelSticky]
  end;
end;
{$ELSE}
function NetShareDelSticky; external netapi32lib name 'NetShareDelSticky';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _NetShareCheck: Pointer;

function NetShareCheck;
begin
  GetProcedureAddress(_NetShareCheck, netapi32lib, 'NetShareCheck');
  asm
    mov esp, ebp
    pop ebp
    jmp [_NetShareCheck]
  end;
end;
{$ELSE}
function NetShareCheck; external netapi32lib name 'NetShareCheck';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _NetSessionEnum: Pointer;

function NetSessionEnum;
begin
  GetProcedureAddress(_NetSessionEnum, netapi32lib, 'NetSessionEnum');
  asm
    mov esp, ebp
    pop ebp
    jmp [_NetSessionEnum]
  end;
end;
{$ELSE}
function NetSessionEnum; external netapi32lib name 'NetSessionEnum';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _NetSessionDel: Pointer;

function NetSessionDel;
begin
  GetProcedureAddress(_NetSessionDel, netapi32lib, 'NetSessionDel');
  asm
    mov esp, ebp
    pop ebp
    jmp [_NetSessionDel]
  end;
end;
{$ELSE}
function NetSessionDel; external netapi32lib name 'NetSessionDel';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _NetSessionGetInfo: Pointer;

function NetSessionGetInfo;
begin
  GetProcedureAddress(_NetSessionGetInfo, netapi32lib, 'NetSessionGetInfo');
  asm
    mov esp, ebp
    pop ebp
    jmp [_NetSessionGetInfo]
  end;
end;
{$ELSE}
function NetSessionGetInfo; external netapi32lib name 'NetSessionGetInfo';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _NetConnectionEnum: Pointer;

function NetConnectionEnum;
begin
  GetProcedureAddress(_NetConnectionEnum, netapi32lib, 'NetConnectionEnum');
  asm
    mov esp, ebp
    pop ebp
    jmp [_NetConnectionEnum]
  end;
end;
{$ELSE}
function NetConnectionEnum; external netapi32lib name 'NetConnectionEnum';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _NetFileClose: Pointer;

function NetFileClose;
begin
  GetProcedureAddress(_NetFileClose, netapi32lib, 'NetFileClose');
  asm
    mov esp, ebp
    pop ebp
    jmp [_NetFileClose]
  end;
end;
{$ELSE}
function NetFileClose; external netapi32lib name 'NetFileClose';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _NetFileEnum: Pointer;

function NetFileEnum;
begin
  GetProcedureAddress(_NetFileEnum, netapi32lib, 'NetFileEnum');
  asm
    mov esp, ebp
    pop ebp
    jmp [_NetFileEnum]
  end;
end;
{$ELSE}
function NetFileEnum; external netapi32lib name 'NetFileEnum';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _NetFileGetInfo: Pointer;

function NetFileGetInfo;
begin
  GetProcedureAddress(_NetFileGetInfo, netapi32lib, 'NetFileGetInfo');
  asm
    mov esp, ebp
    pop ebp
    jmp [_NetFileGetInfo]
  end;
end;
{$ELSE}
function NetFileGetInfo; external netapi32lib name 'NetFileGetInfo';
{$ENDIF DYNAMIC_LINK}

// LMMSG.H


{$IFDEF DYNAMIC_LINK}
var
  _NetMessageNameAdd: Pointer;

function NetMessageNameAdd;
begin
  GetProcedureAddress(_NetMessageNameAdd, netapi32lib, 'NetMessageNameAdd');
  asm
    mov esp, ebp
    pop ebp
    jmp [_NetMessageNameAdd]
  end;
end;
{$ELSE}
function NetMessageNameAdd; external netapi32lib name 'NetMessageNameAdd';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _NetMessageNameEnum: Pointer;

function NetMessageNameEnum;
begin
  GetProcedureAddress(_NetMessageNameEnum, netapi32lib, 'NetMessageNameEnum');
  asm
    mov esp, ebp
    pop ebp
    jmp [_NetMessageNameEnum]
  end;
end;
{$ELSE}
function NetMessageNameEnum; external netapi32lib name 'NetMessageNameEnum';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _NetMessageNameGetInfo: Pointer;

function NetMessageNameGetInfo;
begin
  GetProcedureAddress(_NetMessageNameGetInfo, netapi32lib, 'NetMessageNameGetInfo');
  asm
    mov esp, ebp
    pop ebp
    jmp [_NetMessageNameGetInfo]
  end;
end;
{$ELSE}
function NetMessageNameGetInfo; external netapi32lib name 'NetMessageNameGetInfo';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _NetMessageNameDel: Pointer;

function NetMessageNameDel;
begin
  GetProcedureAddress(_NetMessageNameDel, netapi32lib, 'NetMessageNameDel');
  asm
    mov esp, ebp
    pop ebp
    jmp [_NetMessageNameDel]
  end;
end;
{$ELSE}
function NetMessageNameDel; external netapi32lib name 'NetMessageNameDel';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _NetMessageBufferSend: Pointer;

function NetMessageBufferSend;
begin
  GetProcedureAddress(_NetMessageBufferSend, netapi32lib, 'NetMessageBufferSend');
  asm
    mov esp, ebp
    pop ebp
    jmp [_NetMessageBufferSend]
  end;
end;
{$ELSE}
function NetMessageBufferSend; external netapi32lib name 'NetMessageBufferSend';
{$ENDIF DYNAMIC_LINK}

// LMREMUTL.H


{$IFDEF DYNAMIC_LINK}
var
  _NetRemoteTOD: Pointer;

function NetRemoteTOD;
begin
  GetProcedureAddress(_NetRemoteTOD, netapi32lib, 'NetRemoteTOD');
  asm
    mov esp, ebp
    pop ebp
    jmp [_NetRemoteTOD]
  end;
end;
{$ELSE}
function NetRemoteTOD; external netapi32lib name 'NetRemoteTOD';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _NetRemoteComputerSupports: Pointer;

function NetRemoteComputerSupports;
begin
  GetProcedureAddress(_NetRemoteComputerSupports, netapi32lib, 'NetRemoteComputerSupports');
  asm
    mov esp, ebp
    pop ebp
    jmp [_NetRemoteComputerSupports]
  end;
end;
{$ELSE}
function NetRemoteComputerSupports; external netapi32lib name 'NetRemoteComputerSupports';
{$ENDIF DYNAMIC_LINK}

// LMREPL.H


{$IFDEF DYNAMIC_LINK}
var
  _NetReplGetInfo: Pointer;

function NetReplGetInfo;
begin
  GetProcedureAddress(_NetReplGetInfo, netapi32lib, 'NetReplGetInfo');
  asm
    mov esp, ebp
    pop ebp
    jmp [_NetReplGetInfo]
  end;
end;
{$ELSE}
function NetReplGetInfo; external netapi32lib name 'NetReplGetInfo';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _NetReplSetInfo: Pointer;

function NetReplSetInfo;
begin
  GetProcedureAddress(_NetReplSetInfo, netapi32lib, 'NetReplSetInfo');
  asm
    mov esp, ebp
    pop ebp
    jmp [_NetReplSetInfo]
  end;
end;
{$ELSE}
function NetReplSetInfo; external netapi32lib name 'NetReplSetInfo';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _NetReplExportDirAdd: Pointer;

function NetReplExportDirAdd;
begin
  GetProcedureAddress(_NetReplExportDirAdd, netapi32lib, 'NetReplExportDirAdd');
  asm
    mov esp, ebp
    pop ebp
    jmp [_NetReplExportDirAdd]
  end;
end;
{$ELSE}
function NetReplExportDirAdd; external netapi32lib name 'NetReplExportDirAdd';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _NetReplExportDirDel: Pointer;

function NetReplExportDirDel;
begin
  GetProcedureAddress(_NetReplExportDirDel, netapi32lib, 'NetReplExportDirDel');
  asm
    mov esp, ebp
    pop ebp
    jmp [_NetReplExportDirDel]
  end;
end;
{$ELSE}
function NetReplExportDirDel; external netapi32lib name 'NetReplExportDirDel';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _NetReplExportDirEnum: Pointer;

function NetReplExportDirEnum;
begin
  GetProcedureAddress(_NetReplExportDirEnum, netapi32lib, 'NetReplExportDirEnum');
  asm
    mov esp, ebp
    pop ebp
    jmp [_NetReplExportDirEnum]
  end;
end;
{$ELSE}
function NetReplExportDirEnum; external netapi32lib name 'NetReplExportDirEnum';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _NetReplExportDirGetInfo: Pointer;

function NetReplExportDirGetInfo;
begin
  GetProcedureAddress(_NetReplExportDirGetInfo, netapi32lib, 'NetReplExportDirGetInfo');
  asm
    mov esp, ebp
    pop ebp
    jmp [_NetReplExportDirGetInfo]
  end;
end;
{$ELSE}
function NetReplExportDirGetInfo; external netapi32lib name 'NetReplExportDirGetInfo';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _NetReplExportDirSetInfo: Pointer;

function NetReplExportDirSetInfo;
begin
  GetProcedureAddress(_NetReplExportDirSetInfo, netapi32lib, 'NetReplExportDirSetInfo');
  asm
    mov esp, ebp
    pop ebp
    jmp [_NetReplExportDirSetInfo]
  end;
end;
{$ELSE}
function NetReplExportDirSetInfo; external netapi32lib name 'NetReplExportDirSetInfo';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _NetReplExportDirLock: Pointer;

function NetReplExportDirLock;
begin
  GetProcedureAddress(_NetReplExportDirLock, netapi32lib, 'NetReplExportDirLock');
  asm
    mov esp, ebp
    pop ebp
    jmp [_NetReplExportDirLock]
  end;
end;
{$ELSE}
function NetReplExportDirLock; external netapi32lib name 'NetReplExportDirLock';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _NetReplExportDirUnlock: Pointer;

function NetReplExportDirUnlock;
begin
  GetProcedureAddress(_NetReplExportDirUnlock, netapi32lib, 'NetReplExportDirUnlock');
  asm
    mov esp, ebp
    pop ebp
    jmp [_NetReplExportDirUnlock]
  end;
end;
{$ELSE}
function NetReplExportDirUnlock; external netapi32lib name 'NetReplExportDirUnlock';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _NetReplImportDirAdd: Pointer;

function NetReplImportDirAdd;
begin
  GetProcedureAddress(_NetReplImportDirAdd, netapi32lib, 'NetReplImportDirAdd');
  asm
    mov esp, ebp
    pop ebp
    jmp [_NetReplImportDirAdd]
  end;
end;
{$ELSE}
function NetReplImportDirAdd; external netapi32lib name 'NetReplImportDirAdd';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _NetReplImportDirDel: Pointer;

function NetReplImportDirDel;
begin
  GetProcedureAddress(_NetReplImportDirDel, netapi32lib, 'NetReplImportDirDel');
  asm
    mov esp, ebp
    pop ebp
    jmp [_NetReplImportDirDel]
  end;
end;
{$ELSE}
function NetReplImportDirDel; external netapi32lib name 'NetReplImportDirDel';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _NetReplImportDirEnum: Pointer;

function NetReplImportDirEnum;
begin
  GetProcedureAddress(_NetReplImportDirEnum, netapi32lib, 'NetReplImportDirEnum');
  asm
    mov esp, ebp
    pop ebp
    jmp [_NetReplImportDirEnum]
  end;
end;
{$ELSE}
function NetReplImportDirEnum; external netapi32lib name 'NetReplImportDirEnum';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _NetReplImportDirGetInfo: Pointer;

function NetReplImportDirGetInfo;
begin
  GetProcedureAddress(_NetReplImportDirGetInfo, netapi32lib, 'NetReplImportDirGetInfo');
  asm
    mov esp, ebp
    pop ebp
    jmp [_NetReplImportDirGetInfo]
  end;
end;
{$ELSE}
function NetReplImportDirGetInfo; external netapi32lib name 'NetReplImportDirGetInfo';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _NetReplImportDirLock: Pointer;

function NetReplImportDirLock;
begin
  GetProcedureAddress(_NetReplImportDirLock, netapi32lib, 'NetReplImportDirLock');
  asm
    mov esp, ebp
    pop ebp
    jmp [_NetReplImportDirLock]
  end;
end;
{$ELSE}
function NetReplImportDirLock; external netapi32lib name 'NetReplImportDirLock';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _NetReplImportDirUnlock: Pointer;

function NetReplImportDirUnlock;
begin
  GetProcedureAddress(_NetReplImportDirUnlock, netapi32lib, 'NetReplImportDirUnlock');
  asm
    mov esp, ebp
    pop ebp
    jmp [_NetReplImportDirUnlock]
  end;
end;
{$ELSE}
function NetReplImportDirUnlock; external netapi32lib name 'NetReplImportDirUnlock';
{$ENDIF DYNAMIC_LINK}

// LMSERVER.H


{$IFDEF DYNAMIC_LINK}
var
  _NetServerEnum: Pointer;

function NetServerEnum;
begin
  GetProcedureAddress(_NetServerEnum, netapi32lib, 'NetServerEnum');
  asm
    mov esp, ebp
    pop ebp
    jmp [_NetServerEnum]
  end;
end;
{$ELSE}
function NetServerEnum; external netapi32lib name 'NetServerEnum';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _NetServerEnumEx: Pointer;

function NetServerEnumEx;
begin
  GetProcedureAddress(_NetServerEnumEx, netapi32lib, 'NetServerEnumEx');
  asm
    mov esp, ebp
    pop ebp
    jmp [_NetServerEnumEx]
  end;
end;
{$ELSE}
function NetServerEnumEx; external netapi32lib name 'NetServerEnumEx';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _NetServerGetInfo: Pointer;

function NetServerGetInfo;
begin
  GetProcedureAddress(_NetServerGetInfo, netapi32lib, 'NetServerGetInfo');
  asm
    mov esp, ebp
    pop ebp
    jmp [_NetServerGetInfo]
  end;
end;
{$ELSE}
function NetServerGetInfo; external netapi32lib name 'NetServerGetInfo';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _NetServerSetInfo: Pointer;

function NetServerSetInfo;
begin
  GetProcedureAddress(_NetServerSetInfo, netapi32lib, 'NetServerSetInfo');
  asm
    mov esp, ebp
    pop ebp
    jmp [_NetServerSetInfo]
  end;
end;
{$ELSE}
function NetServerSetInfo; external netapi32lib name 'NetServerSetInfo';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _NetServerSetInfoCommandLine: Pointer;

function NetServerSetInfoCommandLine;
begin
  GetProcedureAddress(_NetServerSetInfoCommandLine, netapi32lib, 'NetServerSetInfoCommandLine');
  asm
    mov esp, ebp
    pop ebp
    jmp [_NetServerSetInfoCommandLine]
  end;
end;
{$ELSE}
function NetServerSetInfoCommandLine; external netapi32lib name 'NetServerSetInfoCommandLine';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _NetServerDiskEnum: Pointer;

function NetServerDiskEnum;
begin
  GetProcedureAddress(_NetServerDiskEnum, netapi32lib, 'NetServerDiskEnum');
  asm
    mov esp, ebp
    pop ebp
    jmp [_NetServerDiskEnum]
  end;
end;
{$ELSE}
function NetServerDiskEnum; external netapi32lib name 'NetServerDiskEnum';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _NetServerComputerNameAdd: Pointer;

function NetServerComputerNameAdd;
begin
  GetProcedureAddress(_NetServerComputerNameAdd, netapi32lib, 'NetServerComputerNameAdd');
  asm
    mov esp, ebp
    pop ebp
    jmp [_NetServerComputerNameAdd]
  end;
end;
{$ELSE}
function NetServerComputerNameAdd; external netapi32lib name 'NetServerComputerNameAdd';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _NetServerComputerNameDel: Pointer;

function NetServerComputerNameDel;
begin
  GetProcedureAddress(_NetServerComputerNameDel, netapi32lib, 'NetServerComputerNameDel');
  asm
    mov esp, ebp
    pop ebp
    jmp [_NetServerComputerNameDel]
  end;
end;
{$ELSE}
function NetServerComputerNameDel; external netapi32lib name 'NetServerComputerNameDel';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _NetServerTransportAdd: Pointer;

function NetServerTransportAdd;
begin
  GetProcedureAddress(_NetServerTransportAdd, netapi32lib, 'NetServerTransportAdd');
  asm
    mov esp, ebp
    pop ebp
    jmp [_NetServerTransportAdd]
  end;
end;
{$ELSE}
function NetServerTransportAdd; external netapi32lib name 'NetServerTransportAdd';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _NetServerTransportAddEx: Pointer;

function NetServerTransportAddEx;
begin
  GetProcedureAddress(_NetServerTransportAddEx, netapi32lib, 'NetServerTransportAddEx');
  asm
    mov esp, ebp
    pop ebp
    jmp [_NetServerTransportAddEx]
  end;
end;
{$ELSE}
function NetServerTransportAddEx; external netapi32lib name 'NetServerTransportAddEx';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _NetServerTransportDel: Pointer;

function NetServerTransportDel;
begin
  GetProcedureAddress(_NetServerTransportDel, netapi32lib, 'NetServerTransportDel');
  asm
    mov esp, ebp
    pop ebp
    jmp [_NetServerTransportDel]
  end;
end;
{$ELSE}
function NetServerTransportDel; external netapi32lib name 'NetServerTransportDel';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _NetServerTransportEnum: Pointer;

function NetServerTransportEnum;
begin
  GetProcedureAddress(_NetServerTransportEnum, netapi32lib, 'NetServerTransportEnum');
  asm
    mov esp, ebp
    pop ebp
    jmp [_NetServerTransportEnum]
  end;
end;
{$ELSE}
function NetServerTransportEnum; external netapi32lib name 'NetServerTransportEnum';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _SetServiceBits: Pointer;

function SetServiceBits;
begin
  GetProcedureAddress(_SetServiceBits, netapi32lib, 'SetServiceBits');
  asm
    mov esp, ebp
    pop ebp
    jmp [_SetServiceBits]
  end;
end;
{$ELSE}
function SetServiceBits; external netapi32lib name 'SetServiceBits';
{$ENDIF DYNAMIC_LINK}

// LMSVC.H

function SERVICE_IP_CODE(tt, nn: LongInt): LongInt;
begin
  Result := SERVICE_IP_QUERY_HINT or (nn or tt shl SERVICE_IP_WAITTIME_SHIFT);
end;

function SERVICE_CCP_CODE(tt, nn: LongInt): LongInt;
begin
  Result := SERVICE_CCP_QUERY_HINT or (nn or tt shl SERVICE_IP_WAITTIME_SHIFT);
end;

function SERVICE_UIC_CODE(cc, mm: LongInt): LongInt;
begin
  Result := (cc shl 16) or Word(mm);
end;

function SERVICE_NT_CCP_CODE(tt, nn: LongInt): LongInt;
begin
  Result := nn or ((tt and LOWER_HINT_MASK) shl SERVICE_IP_WAITTIME_SHIFT) or
    ((tt and UPPER_HINT_MASK) shl SERVICE_NTIP_WAITTIME_SHIFT);
end;

function SERVICE_NT_WAIT_GET(code: DWORD): DWORD;
begin
  Result := ((code and UPPER_GET_HINT_MASK) shr SERVICE_NTIP_WAITTIME_SHIFT) or
    ((code and LOWER_GET_HINT_MASK) shr SERVICE_IP_WAITTIME_SHIFT);
end;


{$IFDEF DYNAMIC_LINK}
var
  _NetServiceControl: Pointer;

function NetServiceControl;
begin
  GetProcedureAddress(_NetServiceControl, netapi32lib, 'NetServiceControl');
  asm
    mov esp, ebp
    pop ebp
    jmp [_NetServiceControl]
  end;
end;
{$ELSE}
function NetServiceControl; external netapi32lib name 'NetServiceControl';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _NetServiceEnum: Pointer;

function NetServiceEnum;
begin
  GetProcedureAddress(_NetServiceEnum, netapi32lib, 'NetServiceEnum');
  asm
    mov esp, ebp
    pop ebp
    jmp [_NetServiceEnum]
  end;
end;
{$ELSE}
function NetServiceEnum; external netapi32lib name 'NetServiceEnum';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _NetServiceGetInfo: Pointer;

function NetServiceGetInfo;
begin
  GetProcedureAddress(_NetServiceGetInfo, netapi32lib, 'NetServiceGetInfo');
  asm
    mov esp, ebp
    pop ebp
    jmp [_NetServiceGetInfo]
  end;
end;
{$ELSE}
function NetServiceGetInfo; external netapi32lib name 'NetServiceGetInfo';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _NetServiceInstall: Pointer;

function NetServiceInstall;
begin
  GetProcedureAddress(_NetServiceInstall, netapi32lib, 'NetServiceInstall');
  asm
    mov esp, ebp
    pop ebp
    jmp [_NetServiceInstall]
  end;
end;
{$ELSE}
function NetServiceInstall; external netapi32lib name 'NetServiceInstall';
{$ENDIF DYNAMIC_LINK}

// LMUSE.H


{$IFDEF DYNAMIC_LINK}
var
  _NetUseAdd: Pointer;

function NetUseAdd;
begin
  GetProcedureAddress(_NetUseAdd, netapi32lib, 'NetUseAdd');
  asm
    mov esp, ebp
    pop ebp
    jmp [_NetUseAdd]
  end;
end;
{$ELSE}
function NetUseAdd; external netapi32lib name 'NetUseAdd';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _NetUseDel: Pointer;

function NetUseDel;
begin
  GetProcedureAddress(_NetUseDel, netapi32lib, 'NetUseDel');
  asm
    mov esp, ebp
    pop ebp
    jmp [_NetUseDel]
  end;
end;
{$ELSE}
function NetUseDel; external netapi32lib name 'NetUseDel';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _NetUseEnum: Pointer;

function NetUseEnum;
begin
  GetProcedureAddress(_NetUseEnum, netapi32lib, 'NetUseEnum');
  asm
    mov esp, ebp
    pop ebp
    jmp [_NetUseEnum]
  end;
end;
{$ELSE}
function NetUseEnum; external netapi32lib name 'NetUseEnum';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _NetUseGetInfo: Pointer;

function NetUseGetInfo;
begin
  GetProcedureAddress(_NetUseGetInfo, netapi32lib, 'NetUseGetInfo');
  asm
    mov esp, ebp
    pop ebp
    jmp [_NetUseGetInfo]
  end;
end;
{$ELSE}
function NetUseGetInfo; external netapi32lib name 'NetUseGetInfo';
{$ENDIF DYNAMIC_LINK}

// LMWKSTA.H


{$IFDEF DYNAMIC_LINK}
var
  _NetWkstaGetInfo: Pointer;

function NetWkstaGetInfo;
begin
  GetProcedureAddress(_NetWkstaGetInfo, netapi32lib, 'NetWkstaGetInfo');
  asm
    mov esp, ebp
    pop ebp
    jmp [_NetWkstaGetInfo]
  end;
end;
{$ELSE}
function NetWkstaGetInfo; external netapi32lib name 'NetWkstaGetInfo';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _NetWkstaSetInfo: Pointer;

function NetWkstaSetInfo;
begin
  GetProcedureAddress(_NetWkstaSetInfo, netapi32lib, 'NetWkstaSetInfo');
  asm
    mov esp, ebp
    pop ebp
    jmp [_NetWkstaSetInfo]
  end;
end;
{$ELSE}
function NetWkstaSetInfo; external netapi32lib name 'NetWkstaSetInfo';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _NetWkstaUserGetInfo: Pointer;

function NetWkstaUserGetInfo;
begin
  GetProcedureAddress(_NetWkstaUserGetInfo, netapi32lib, 'NetWkstaUserGetInfo');
  asm
    mov esp, ebp
    pop ebp
    jmp [_NetWkstaUserGetInfo]
  end;
end;
{$ELSE}
function NetWkstaUserGetInfo; external netapi32lib name 'NetWkstaUserGetInfo';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _NetWkstaUserSetInfo: Pointer;

function NetWkstaUserSetInfo;
begin
  GetProcedureAddress(_NetWkstaUserSetInfo, netapi32lib, 'NetWkstaUserSetInfo');
  asm
    mov esp, ebp
    pop ebp
    jmp [_NetWkstaUserSetInfo]
  end;
end;
{$ELSE}
function NetWkstaUserSetInfo; external netapi32lib name 'NetWkstaUserSetInfo';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _NetWkstaUserEnum: Pointer;

function NetWkstaUserEnum;
begin
  GetProcedureAddress(_NetWkstaUserEnum, netapi32lib, 'NetWkstaUserEnum');
  asm
    mov esp, ebp
    pop ebp
    jmp [_NetWkstaUserEnum]
  end;
end;
{$ELSE}
function NetWkstaUserEnum; external netapi32lib name 'NetWkstaUserEnum';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _NetWkstaTransportAdd: Pointer;

function NetWkstaTransportAdd;
begin
  GetProcedureAddress(_NetWkstaTransportAdd, netapi32lib, 'NetWkstaTransportAdd');
  asm
    mov esp, ebp
    pop ebp
    jmp [_NetWkstaTransportAdd]
  end;
end;
{$ELSE}
function NetWkstaTransportAdd; external netapi32lib name 'NetWkstaTransportAdd';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _NetWkstaTransportDel: Pointer;

function NetWkstaTransportDel;
begin
  GetProcedureAddress(_NetWkstaTransportDel, netapi32lib, 'NetWkstaTransportDel');
  asm
    mov esp, ebp
    pop ebp
    jmp [_NetWkstaTransportDel]
  end;
end;
{$ELSE}
function NetWkstaTransportDel; external netapi32lib name 'NetWkstaTransportDel';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _NetWkstaTransportEnum: Pointer;

function NetWkstaTransportEnum;
begin
  GetProcedureAddress(_NetWkstaTransportEnum, netapi32lib, 'NetWkstaTransportEnum');
  asm
    mov esp, ebp
    pop ebp
    jmp [_NetWkstaTransportEnum]
  end;
end;
{$ELSE}
function NetWkstaTransportEnum; external netapi32lib name 'NetWkstaTransportEnum';
{$ENDIF DYNAMIC_LINK}

// LMAPIBUF.H


{$IFDEF DYNAMIC_LINK}
var
  _NetApiBufferAllocate: Pointer;

function NetApiBufferAllocate;
begin
  GetProcedureAddress(_NetApiBufferAllocate, netapi32lib, 'NetApiBufferAllocate');
  asm
    mov esp, ebp
    pop ebp
    jmp [_NetApiBufferAllocate]
  end;
end;
{$ELSE}
function NetApiBufferAllocate; external netapi32lib name 'NetApiBufferAllocate';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _NetApiBufferFree: Pointer;

function NetApiBufferFree;
begin
  GetProcedureAddress(_NetApiBufferFree, netapi32lib, 'NetApiBufferFree');
  asm
    mov esp, ebp
    pop ebp
    jmp [_NetApiBufferFree]
  end;
end;
{$ELSE}
function NetApiBufferFree; external netapi32lib name 'NetApiBufferFree';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _NetApiBufferReallocate: Pointer;

function NetApiBufferReallocate;
begin
  GetProcedureAddress(_NetApiBufferReallocate, netapi32lib, 'NetApiBufferReallocate');
  asm
    mov esp, ebp
    pop ebp
    jmp [_NetApiBufferReallocate]
  end;
end;
{$ELSE}
function NetApiBufferReallocate; external netapi32lib name 'NetApiBufferReallocate';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _NetApiBufferSize: Pointer;

function NetApiBufferSize;
begin
  GetProcedureAddress(_NetApiBufferSize, netapi32lib, 'NetApiBufferSize');
  asm
    mov esp, ebp
    pop ebp
    jmp [_NetApiBufferSize]
  end;
end;
{$ELSE}
function NetApiBufferSize; external netapi32lib name 'NetApiBufferSize';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _NetapipBufferAllocate: Pointer;

function NetapipBufferAllocate;
begin
  GetProcedureAddress(_NetapipBufferAllocate, netapi32lib, 'NetapipBufferAllocate');
  asm
    mov esp, ebp
    pop ebp
    jmp [_NetapipBufferAllocate]
  end;
end;
{$ELSE}
function NetapipBufferAllocate; external netapi32lib name 'NetapipBufferAllocate';
{$ENDIF DYNAMIC_LINK}

// LMCONFIG.H


{$IFDEF DYNAMIC_LINK}
var
  _NetConfigGet: Pointer;

function NetConfigGet;
begin
  GetProcedureAddress(_NetConfigGet, netapi32lib, 'NetConfigGet');
  asm
    mov esp, ebp
    pop ebp
    jmp [_NetConfigGet]
  end;
end;
{$ELSE}
function NetConfigGet; external netapi32lib name 'NetConfigGet';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _NetConfigGetAll: Pointer;

function NetConfigGetAll;
begin
  GetProcedureAddress(_NetConfigGetAll, netapi32lib, 'NetConfigGetAll');
  asm
    mov esp, ebp
    pop ebp
    jmp [_NetConfigGetAll]
  end;
end;
{$ELSE}
function NetConfigGetAll; external netapi32lib name 'NetConfigGetAll';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _NetConfigSet: Pointer;

function NetConfigSet;
begin
  GetProcedureAddress(_NetConfigSet, netapi32lib, 'NetConfigSet');
  asm
    mov esp, ebp
    pop ebp
    jmp [_NetConfigSet]
  end;
end;
{$ELSE}
function NetConfigSet; external netapi32lib name 'NetConfigSet';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _NetRegisterDomNameChangeNot: Pointer;

function NetRegisterDomainNameChangeNotification;
begin
  GetProcedureAddress(_NetRegisterDomNameChangeNot, netapi32lib, 'NetRegisterDomainNameChangeNotification');
  asm
    mov esp, ebp
    pop ebp
    jmp [_NetRegisterDomNameChangeNot]
  end;
end;
{$ELSE}
function NetRegisterDomainNameChangeNotification; external netapi32lib name 'NetRegisterDomainNameChangeNotification';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _NetUnregisterDomNameChangeNot: Pointer;

function NetUnregisterDomainNameChangeNotification;
begin
  GetProcedureAddress(_NetUnregisterDomNameChangeNot, netapi32lib, 'NetUnregisterDomainNameChangeNotification');
  asm
    mov esp, ebp
    pop ebp
    jmp [_NetUnregisterDomNameChangeNot]
  end;
end;
{$ELSE}
function NetUnregisterDomainNameChangeNotification; external netapi32lib name 'NetUnregisterDomainNameChangeNotification';
{$ENDIF DYNAMIC_LINK}

// LMSTATS.H


{$IFDEF DYNAMIC_LINK}
var
  _NetStatisticsGet: Pointer;

function NetStatisticsGet;
begin
  GetProcedureAddress(_NetStatisticsGet, netapi32lib, 'NetStatisticsGet');
  asm
    mov esp, ebp
    pop ebp
    jmp [_NetStatisticsGet]
  end;
end;
{$ELSE}
function NetStatisticsGet; external netapi32lib name 'NetStatisticsGet';
{$ENDIF DYNAMIC_LINK}

// LMAUDIT.H


{$IFDEF DYNAMIC_LINK}
var
  _NetAuditClear: Pointer;

function NetAuditClear;
begin
  GetProcedureAddress(_NetAuditClear, netapi32lib, 'NetAuditClear');
  asm
    mov esp, ebp
    pop ebp
    jmp [_NetAuditClear]
  end;
end;
{$ELSE}
function NetAuditClear; external netapi32lib name 'NetAuditClear';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _NetAuditRead: Pointer;

function NetAuditRead;
begin
  GetProcedureAddress(_NetAuditRead, netapi32lib, 'NetAuditRead');
  asm
    mov esp, ebp
    pop ebp
    jmp [_NetAuditRead]
  end;
end;
{$ELSE}
function NetAuditRead; external netapi32lib name 'NetAuditRead';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _NetAuditWrite: Pointer;

function NetAuditWrite;
begin
  GetProcedureAddress(_NetAuditWrite, netapi32lib, 'NetAuditWrite');
  asm
    mov esp, ebp
    pop ebp
    jmp [_NetAuditWrite]
  end;
end;
{$ELSE}
function NetAuditWrite; external netapi32lib name 'NetAuditWrite';
{$ENDIF DYNAMIC_LINK}

// LMJOIN.H


{$IFDEF DYNAMIC_LINK}
var
  _NetJoinDomain: Pointer;

function NetJoinDomain;
begin
  GetProcedureAddress(_NetJoinDomain, netapi32lib, 'NetJoinDomain');
  asm
    mov esp, ebp
    pop ebp
    jmp [_NetJoinDomain]
  end;
end;
{$ELSE}
function NetJoinDomain; external netapi32lib name 'NetJoinDomain';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _NetUnjoinDomain: Pointer;

function NetUnjoinDomain;
begin
  GetProcedureAddress(_NetUnjoinDomain, netapi32lib, 'NetUnjoinDomain');
  asm
    mov esp, ebp
    pop ebp
    jmp [_NetUnjoinDomain]
  end;
end;
{$ELSE}
function NetUnjoinDomain; external netapi32lib name 'NetUnjoinDomain';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _NetRenameMachineInDomain: Pointer;

function NetRenameMachineInDomain;
begin
  GetProcedureAddress(_NetRenameMachineInDomain, netapi32lib, 'NetRenameMachineInDomain');
  asm
    mov esp, ebp
    pop ebp
    jmp [_NetRenameMachineInDomain]
  end;
end;
{$ELSE}
function NetRenameMachineInDomain; external netapi32lib name 'NetRenameMachineInDomain';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _NetValidateName: Pointer;

function NetValidateName;
begin
  GetProcedureAddress(_NetValidateName, netapi32lib, 'NetValidateName');
  asm
    mov esp, ebp
    pop ebp
    jmp [_NetValidateName]
  end;
end;
{$ELSE}
function NetValidateName; external netapi32lib name 'NetValidateName';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _NetGetJoinInformation: Pointer;

function NetGetJoinInformation;
begin
  GetProcedureAddress(_NetGetJoinInformation, netapi32lib, 'NetGetJoinInformation');
  asm
    mov esp, ebp
    pop ebp
    jmp [_NetGetJoinInformation]
  end;
end;
{$ELSE}
function NetGetJoinInformation; external netapi32lib name 'NetGetJoinInformation';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _NetGetJoinableOUs: Pointer;

function NetGetJoinableOUs;
begin
  GetProcedureAddress(_NetGetJoinableOUs, netapi32lib, 'NetGetJoinableOUs');
  asm
    mov esp, ebp
    pop ebp
    jmp [_NetGetJoinableOUs]
  end;
end;
{$ELSE}
function NetGetJoinableOUs; external netapi32lib name 'NetGetJoinableOUs';
{$ENDIF DYNAMIC_LINK}

// LMERRLOG.H


{$IFDEF DYNAMIC_LINK}
var
  _NetErrorLogClear: Pointer;

function NetErrorLogClear;
begin
  GetProcedureAddress(_NetErrorLogClear, netapi32lib, 'NetErrorLogClear');
  asm
    mov esp, ebp
    pop ebp
    jmp [_NetErrorLogClear]
  end;
end;
{$ELSE}
function NetErrorLogClear; external netapi32lib name 'NetErrorLogClear';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _NetErrorLogRead: Pointer;

function NetErrorLogRead;
begin
  GetProcedureAddress(_NetErrorLogRead, netapi32lib, 'NetErrorLogRead');
  asm
    mov esp, ebp
    pop ebp
    jmp [_NetErrorLogRead]
  end;
end;
{$ELSE}
function NetErrorLogRead; external netapi32lib name 'NetErrorLogRead';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _NetErrorLogWrite: Pointer;

function NetErrorLogWrite;
begin
  GetProcedureAddress(_NetErrorLogWrite, netapi32lib, 'NetErrorLogWrite');
  asm
    mov esp, ebp
    pop ebp
    jmp [_NetErrorLogWrite]
  end;
end;
{$ELSE}
function NetErrorLogWrite; external netapi32lib name 'NetErrorLogWrite';
{$ENDIF DYNAMIC_LINK}

// LMAT.H


{$IFDEF DYNAMIC_LINK}
var
  _NetScheduleJobAdd: Pointer;

function NetScheduleJobAdd;
begin
  GetProcedureAddress(_NetScheduleJobAdd, netapi32lib, 'NetScheduleJobAdd');
  asm
    mov esp, ebp
    pop ebp
    jmp [_NetScheduleJobAdd]
  end;
end;
{$ELSE}
function NetScheduleJobAdd; external netapi32lib name 'NetScheduleJobAdd';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _NetScheduleJobDel: Pointer;

function NetScheduleJobDel;
begin
  GetProcedureAddress(_NetScheduleJobDel, netapi32lib, 'NetScheduleJobDel');
  asm
    mov esp, ebp
    pop ebp
    jmp [_NetScheduleJobDel]
  end;
end;
{$ELSE}
function NetScheduleJobDel; external netapi32lib name 'NetScheduleJobDel';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _NetScheduleJobEnum: Pointer;

function NetScheduleJobEnum;
begin
  GetProcedureAddress(_NetScheduleJobEnum, netapi32lib, 'NetScheduleJobEnum');
  asm
    mov esp, ebp
    pop ebp
    jmp [_NetScheduleJobEnum]
  end;
end;
{$ELSE}
function NetScheduleJobEnum; external netapi32lib name 'NetScheduleJobEnum';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _NetScheduleJobGetInfo: Pointer;

function NetScheduleJobGetInfo;
begin
  GetProcedureAddress(_NetScheduleJobGetInfo, netapi32lib, 'NetScheduleJobGetInfo');
  asm
    mov esp, ebp
    pop ebp
    jmp [_NetScheduleJobGetInfo]
  end;
end;
{$ELSE}
function NetScheduleJobGetInfo; external netapi32lib name 'NetScheduleJobGetInfo';
{$ENDIF DYNAMIC_LINK}

// LMBROWSR.H


{$IFDEF DYNAMIC_LINK}
var
  _I_BrowserServerEnum: Pointer;

function I_BrowserServerEnum;
begin
  GetProcedureAddress(_I_BrowserServerEnum, netapi32lib, 'I_BrowserServerEnum');
  asm
    mov esp, ebp
    pop ebp
    jmp [_I_BrowserServerEnum]
  end;
end;
{$ELSE}
function I_BrowserServerEnum; external netapi32lib name 'I_BrowserServerEnum';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _I_BrowserServerEnumEx: Pointer;

function I_BrowserServerEnumEx;
begin
  GetProcedureAddress(_I_BrowserServerEnumEx, netapi32lib, 'I_BrowserServerEnumEx');
  asm
    mov esp, ebp
    pop ebp
    jmp [_I_BrowserServerEnumEx]
  end;
end;
{$ELSE}
function I_BrowserServerEnumEx; external netapi32lib name 'I_BrowserServerEnumEx';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _I_BrowserQueryOtherDomains: Pointer;

function I_BrowserQueryOtherDomains;
begin
  GetProcedureAddress(_I_BrowserQueryOtherDomains, netapi32lib, 'I_BrowserQueryOtherDomains');
  asm
    mov esp, ebp
    pop ebp
    jmp [_I_BrowserQueryOtherDomains]
  end;
end;
{$ELSE}
function I_BrowserQueryOtherDomains; external netapi32lib name 'I_BrowserQueryOtherDomains';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _I_BrowserResetNetlogonState: Pointer;

function I_BrowserResetNetlogonState;
begin
  GetProcedureAddress(_I_BrowserResetNetlogonState, netapi32lib, 'I_BrowserResetNetlogonState');
  asm
    mov esp, ebp
    pop ebp
    jmp [_I_BrowserResetNetlogonState]
  end;
end;
{$ELSE}
function I_BrowserResetNetlogonState; external netapi32lib name 'I_BrowserResetNetlogonState';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _I_BrowserSetNetlogonState: Pointer;

function I_BrowserSetNetlogonState;
begin
  GetProcedureAddress(_I_BrowserSetNetlogonState, netapi32lib, 'I_BrowserSetNetlogonState');
  asm
    mov esp, ebp
    pop ebp
    jmp [_I_BrowserSetNetlogonState]
  end;
end;
{$ELSE}
function I_BrowserSetNetlogonState; external netapi32lib name 'I_BrowserSetNetlogonState';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _I_BrowserQueryEmulatedDomains: Pointer;

function I_BrowserQueryEmulatedDomains;
begin
  GetProcedureAddress(_I_BrowserQueryEmulatedDomains, netapi32lib, 'I_BrowserQueryEmulatedDomains');
  asm
    mov esp, ebp
    pop ebp
    jmp [_I_BrowserQueryEmulatedDomains]
  end;
end;
{$ELSE}
function I_BrowserQueryEmulatedDomains; external netapi32lib name 'I_BrowserQueryEmulatedDomains';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _I_BrowserQueryStatistics: Pointer;

function I_BrowserQueryStatistics;
begin
  GetProcedureAddress(_I_BrowserQueryStatistics, netapi32lib, 'I_BrowserQueryStatistics');
  asm
    mov esp, ebp
    pop ebp
    jmp [_I_BrowserQueryStatistics]
  end;
end;
{$ELSE}
function I_BrowserQueryStatistics; external netapi32lib name 'I_BrowserQueryStatistics';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _I_BrowserResetStatistics: Pointer;

function I_BrowserResetStatistics;
begin
  GetProcedureAddress(_I_BrowserResetStatistics, netapi32lib, 'I_BrowserResetStatistics');
  asm
    mov esp, ebp
    pop ebp
    jmp [_I_BrowserResetStatistics]
  end;
end;
{$ELSE}
function I_BrowserResetStatistics; external netapi32lib name 'I_BrowserResetStatistics';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _I_BrowserServerEnumForXactsrv: Pointer;

function I_BrowserServerEnumForXactsrv;
begin
  GetProcedureAddress(_I_BrowserServerEnumForXactsrv, netapi32lib, 'I_BrowserServerEnumForXactsrv');
  asm
    mov esp, ebp
    pop ebp
    jmp [_I_BrowserServerEnumForXactsrv]
  end;
end;
{$ELSE}
function I_BrowserServerEnumForXactsrv; external netapi32lib name 'I_BrowserServerEnumForXactsrv';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _I_BrowserDebugTrace: Pointer;

function I_BrowserDebugTrace;
begin
  GetProcedureAddress(_I_BrowserDebugTrace, netapi32lib, 'I_BrowserDebugTrace');
  asm
    mov esp, ebp
    pop ebp
    jmp [_I_BrowserDebugTrace]
  end;
end;
{$ELSE}
function I_BrowserDebugTrace; external netapi32lib name 'I_BrowserDebugTrace';
{$ENDIF DYNAMIC_LINK}

// LMCHDEV.H


{$IFDEF DYNAMIC_LINK}
var
  _NetCharDevEnum: Pointer;

function NetCharDevEnum;
begin
  GetProcedureAddress(_NetCharDevEnum, netapi32lib, 'NetCharDevEnum');
  asm
    mov esp, ebp
    pop ebp
    jmp [_NetCharDevEnum]
  end;
end;
{$ELSE}
function NetCharDevEnum; external netapi32lib name 'NetCharDevEnum';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _NetCharDevGetInfo: Pointer;

function NetCharDevGetInfo;
begin
  GetProcedureAddress(_NetCharDevGetInfo, netapi32lib, 'NetCharDevGetInfo');
  asm
    mov esp, ebp
    pop ebp
    jmp [_NetCharDevGetInfo]
  end;
end;
{$ELSE}
function NetCharDevGetInfo; external netapi32lib name 'NetCharDevGetInfo';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _NetCharDevControl: Pointer;

function NetCharDevControl;
begin
  GetProcedureAddress(_NetCharDevControl, netapi32lib, 'NetCharDevControl');
  asm
    mov esp, ebp
    pop ebp
    jmp [_NetCharDevControl]
  end;
end;
{$ELSE}
function NetCharDevControl; external netapi32lib name 'NetCharDevControl';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _NetCharDevQEnum: Pointer;

function NetCharDevQEnum;
begin
  GetProcedureAddress(_NetCharDevQEnum, netapi32lib, 'NetCharDevQEnum');
  asm
    mov esp, ebp
    pop ebp
    jmp [_NetCharDevQEnum]
  end;
end;
{$ELSE}
function NetCharDevQEnum; external netapi32lib name 'NetCharDevQEnum';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _NetCharDevQGetInfo: Pointer;

function NetCharDevQGetInfo;
begin
  GetProcedureAddress(_NetCharDevQGetInfo, netapi32lib, 'NetCharDevQGetInfo');
  asm
    mov esp, ebp
    pop ebp
    jmp [_NetCharDevQGetInfo]
  end;
end;
{$ELSE}
function NetCharDevQGetInfo; external netapi32lib name 'NetCharDevQGetInfo';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _NetCharDevQSetInfo: Pointer;

function NetCharDevQSetInfo;
begin
  GetProcedureAddress(_NetCharDevQSetInfo, netapi32lib, 'NetCharDevQSetInfo');
  asm
    mov esp, ebp
    pop ebp
    jmp [_NetCharDevQSetInfo]
  end;
end;
{$ELSE}
function NetCharDevQSetInfo; external netapi32lib name 'NetCharDevQSetInfo';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _NetCharDevQPurge: Pointer;

function NetCharDevQPurge;
begin
  GetProcedureAddress(_NetCharDevQPurge, netapi32lib, 'NetCharDevQPurge');
  asm
    mov esp, ebp
    pop ebp
    jmp [_NetCharDevQPurge]
  end;
end;
{$ELSE}
function NetCharDevQPurge; external netapi32lib name 'NetCharDevQPurge';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _NetCharDevQPurgeSelf: Pointer;

function NetCharDevQPurgeSelf;
begin
  GetProcedureAddress(_NetCharDevQPurgeSelf, netapi32lib, 'NetCharDevQPurgeSelf');
  asm
    mov esp, ebp
    pop ebp
    jmp [_NetCharDevQPurgeSelf]
  end;
end;
{$ELSE}
function NetCharDevQPurgeSelf; external netapi32lib name 'NetCharDevQPurgeSelf';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _NetHandleGetInfo: Pointer;

function NetHandleGetInfo;
begin
  GetProcedureAddress(_NetHandleGetInfo, netapi32lib, 'NetHandleGetInfo');
  asm
    mov esp, ebp
    pop ebp
    jmp [_NetHandleGetInfo]
  end;
end;
{$ELSE}
function NetHandleGetInfo; external netapi32lib name 'NetHandleGetInfo';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _NetHandleSetInfo: Pointer;

function NetHandleSetInfo;
begin
  GetProcedureAddress(_NetHandleSetInfo, netapi32lib, 'NetHandleSetInfo');
  asm
    mov esp, ebp
    pop ebp
    jmp [_NetHandleSetInfo]
  end;
end;
{$ELSE}
function NetHandleSetInfo; external netapi32lib name 'NetHandleSetInfo';
{$ENDIF DYNAMIC_LINK}

// LMDFS.H


{$IFDEF DYNAMIC_LINK}
var
  _NetDfsAdd: Pointer;

function NetDfsAdd;
begin
  GetProcedureAddress(_NetDfsAdd, netapi32lib, 'NetDfsAdd');
  asm
    mov esp, ebp
    pop ebp
    jmp [_NetDfsAdd]
  end;
end;
{$ELSE}
function NetDfsAdd; external netapi32lib name 'NetDfsAdd';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _NetDfsAddStdRoot: Pointer;

function NetDfsAddStdRoot;
begin
  GetProcedureAddress(_NetDfsAddStdRoot, netapi32lib, 'NetDfsAddStdRoot');
  asm
    mov esp, ebp
    pop ebp
    jmp [_NetDfsAddStdRoot]
  end;
end;
{$ELSE}
function NetDfsAddStdRoot; external netapi32lib name 'NetDfsAddStdRoot';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _NetDfsRemoveStdRoot: Pointer;

function NetDfsRemoveStdRoot;
begin
  GetProcedureAddress(_NetDfsRemoveStdRoot, netapi32lib, 'NetDfsRemoveStdRoot');
  asm
    mov esp, ebp
    pop ebp
    jmp [_NetDfsRemoveStdRoot]
  end;
end;
{$ELSE}
function NetDfsRemoveStdRoot; external netapi32lib name 'NetDfsRemoveStdRoot';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _NetDfsAddFtRoot: Pointer;

function NetDfsAddFtRoot;
begin
  GetProcedureAddress(_NetDfsAddFtRoot, netapi32lib, 'NetDfsAddFtRoot');
  asm
    mov esp, ebp
    pop ebp
    jmp [_NetDfsAddFtRoot]
  end;
end;
{$ELSE}
function NetDfsAddFtRoot; external netapi32lib name 'NetDfsAddFtRoot';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _NetDfsRemoveFtRoot: Pointer;

function NetDfsRemoveFtRoot;
begin
  GetProcedureAddress(_NetDfsRemoveFtRoot, netapi32lib, 'NetDfsRemoveFtRoot');
  asm
    mov esp, ebp
    pop ebp
    jmp [_NetDfsRemoveFtRoot]
  end;
end;
{$ELSE}
function NetDfsRemoveFtRoot; external netapi32lib name 'NetDfsRemoveFtRoot';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _NetDfsRemoveFtRootForced: Pointer;

function NetDfsRemoveFtRootForced;
begin
  GetProcedureAddress(_NetDfsRemoveFtRootForced, netapi32lib, 'NetDfsRemoveFtRootForced');
  asm
    mov esp, ebp
    pop ebp
    jmp [_NetDfsRemoveFtRootForced]
  end;
end;
{$ELSE}
function NetDfsRemoveFtRootForced; external netapi32lib name 'NetDfsRemoveFtRootForced';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _NetDfsManagerInitialize: Pointer;

function NetDfsManagerInitialize;
begin
  GetProcedureAddress(_NetDfsManagerInitialize, netapi32lib, 'NetDfsManagerInitialize');
  asm
    mov esp, ebp
    pop ebp
    jmp [_NetDfsManagerInitialize]
  end;
end;
{$ELSE}
function NetDfsManagerInitialize; external netapi32lib name 'NetDfsManagerInitialize';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _NetDfsAddStdRootForced: Pointer;

function NetDfsAddStdRootForced;
begin
  GetProcedureAddress(_NetDfsAddStdRootForced, netapi32lib, 'NetDfsAddStdRootForced');
  asm
    mov esp, ebp
    pop ebp
    jmp [_NetDfsAddStdRootForced]
  end;
end;
{$ELSE}
function NetDfsAddStdRootForced; external netapi32lib name 'NetDfsAddStdRootForced';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _NetDfsGetDcAddress: Pointer;

function NetDfsGetDcAddress;
begin
  GetProcedureAddress(_NetDfsGetDcAddress, netapi32lib, 'NetDfsGetDcAddress');
  asm
    mov esp, ebp
    pop ebp
    jmp [_NetDfsGetDcAddress]
  end;
end;
{$ELSE}
function NetDfsGetDcAddress; external netapi32lib name 'NetDfsGetDcAddress';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _NetDfsSetDcAddress: Pointer;

function NetDfsSetDcAddress;
begin
  GetProcedureAddress(_NetDfsSetDcAddress, netapi32lib, 'NetDfsSetDcAddress');
  asm
    mov esp, ebp
    pop ebp
    jmp [_NetDfsSetDcAddress]
  end;
end;
{$ELSE}
function NetDfsSetDcAddress; external netapi32lib name 'NetDfsSetDcAddress';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _NetDfsRemove: Pointer;

function NetDfsRemove;
begin
  GetProcedureAddress(_NetDfsRemove, netapi32lib, 'NetDfsRemove');
  asm
    mov esp, ebp
    pop ebp
    jmp [_NetDfsRemove]
  end;
end;
{$ELSE}
function NetDfsRemove; external netapi32lib name 'NetDfsRemove';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _NetDfsEnum: Pointer;

function NetDfsEnum;
begin
  GetProcedureAddress(_NetDfsEnum, netapi32lib, 'NetDfsEnum');
  asm
    mov esp, ebp
    pop ebp
    jmp [_NetDfsEnum]
  end;
end;
{$ELSE}
function NetDfsEnum; external netapi32lib name 'NetDfsEnum';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _NetDfsGetInfo: Pointer;

function NetDfsGetInfo;
begin
  GetProcedureAddress(_NetDfsGetInfo, netapi32lib, 'NetDfsGetInfo');
  asm
    mov esp, ebp
    pop ebp
    jmp [_NetDfsGetInfo]
  end;
end;
{$ELSE}
function NetDfsGetInfo; external netapi32lib name 'NetDfsGetInfo';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _NetDfsSetInfo: Pointer;

function NetDfsSetInfo;
begin
  GetProcedureAddress(_NetDfsSetInfo, netapi32lib, 'NetDfsSetInfo');
  asm
    mov esp, ebp
    pop ebp
    jmp [_NetDfsSetInfo]
  end;
end;
{$ELSE}
function NetDfsSetInfo; external netapi32lib name 'NetDfsSetInfo';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _NetDfsGetClientInfo: Pointer;

function NetDfsGetClientInfo;
begin
  GetProcedureAddress(_NetDfsGetClientInfo, netapi32lib, 'NetDfsGetClientInfo');
  asm
    mov esp, ebp
    pop ebp
    jmp [_NetDfsGetClientInfo]
  end;
end;
{$ELSE}
function NetDfsGetClientInfo; external netapi32lib name 'NetDfsGetClientInfo';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _NetDfsSetClientInfo: Pointer;

function NetDfsSetClientInfo;
begin
  GetProcedureAddress(_NetDfsSetClientInfo, netapi32lib, 'NetDfsSetClientInfo');
  asm
    mov esp, ebp
    pop ebp
    jmp [_NetDfsSetClientInfo]
  end;
end;
{$ELSE}
function NetDfsSetClientInfo; external netapi32lib name 'NetDfsSetClientInfo';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _NetDfsMove: Pointer;

function NetDfsMove;
begin
  GetProcedureAddress(_NetDfsMove, netapi32lib, 'NetDfsMove');
  asm
    mov esp, ebp
    pop ebp
    jmp [_NetDfsMove]
  end;
end;
{$ELSE}
function NetDfsMove; external netapi32lib name 'NetDfsMove';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _NetDfsRename: Pointer;

function NetDfsRename;
begin
  GetProcedureAddress(_NetDfsRename, netapi32lib, 'NetDfsRename');
  asm
    mov esp, ebp
    pop ebp
    jmp [_NetDfsRename]
  end;
end;
{$ELSE}
function NetDfsRename; external netapi32lib name 'NetDfsRename';
{$ENDIF DYNAMIC_LINK}

end.
