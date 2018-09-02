{******************************************************************************}
{                                                       	               }
{ WinLogon API interface Unit for Object Pascal                                }
{                                                       	               }
{ Portions created by Microsoft are Copyright (C) 1995-2001 Microsoft          }
{ Corporation. All Rights Reserved.                                            }
{ 								               }
{ The original file is: winwlx.h, released June 2000. The original Pascal      }
{ code is: WinWlx.pas, released December 2000. The initial developer of the    }
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

unit JwaWinWlx;

{$WEAKPACKAGEUNIT}

{$HPPEMIT ''}
{$HPPEMIT '#include "WinWlx.h"'}
{$HPPEMIT ''}

{$I WINDEFINES.INC}

interface

uses
  JwaWinType, JwaWinUser, JwaWinNT;

//    WLX == WinLogon eXtension
//
//    This file contains definitions, data types, and routine prototypes
//    necessary to produce a replacement Graphical Identification aNd
//    Authentication (GINA) DLL for Winlogon.

/////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////
//
// Revisions of Winlogon API available for use by GINAs
// Version is two parts: Major revision and minor revision.
// Major revision is the upper 16-bits, minor is the lower
// 16-bits.
//

const
  WLX_VERSION_1_0     = ($00010000);
  {$EXTERNALSYM WLX_VERSION_1_0}
  WLX_VERSION_1_1     = ($00010001);
  {$EXTERNALSYM WLX_VERSION_1_1}
  WLX_VERSION_1_2     = ($00010002);
  {$EXTERNALSYM WLX_VERSION_1_2}
  WLX_VERSION_1_3     = ($00010003);
  {$EXTERNALSYM WLX_VERSION_1_3}
  WLX_VERSION_1_4     = ($00010004);
  {$EXTERNALSYM WLX_VERSION_1_4}
  WLX_CURRENT_VERSION = (WLX_VERSION_1_4);
  {$EXTERNALSYM WLX_CURRENT_VERSION}

/////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////
//
// Secure attention sequence types
// These values are passed to routines that have a dwSasType
// parameter.
//
//  ALL VALUES FROM 0 TO 127 ARE RESERVED FOR MICROSOFT DEFINITION.
//  VALUES ABOVE 127 ARE RESERVED FOR CUSTOMER DEFINITION.
//
//      CTRL_ALT_DEL - used to indicate that the standard ctrl-alt-del
//          secure attention sequence has been entered.
//
//      SCRNSVR_TIMEOUT - used to indicate that keyboard/mouse inactivity
//          has lead to a screensaver activation.  It is up to the GINA
//          DLL whether this constitutes a workstation locking event.
//
//      SCRNSVR_ACTIVITY - used to indicate that keyboard or mouse
//          activity occured while a secure screensaver was active.
//
//      SC_INSERT - used to indicate that a smart card has been inserted
//          to a compatible device
//
//      SC_REMOVE - used to indicate that a smart card has been removed
//          from a compatible device
//

  WLX_SAS_TYPE_TIMEOUT          = (0);
  {$EXTERNALSYM WLX_SAS_TYPE_TIMEOUT}
  WLX_SAS_TYPE_CTRL_ALT_DEL     = (1);
  {$EXTERNALSYM WLX_SAS_TYPE_CTRL_ALT_DEL}
  WLX_SAS_TYPE_SCRNSVR_TIMEOUT  = (2);
  {$EXTERNALSYM WLX_SAS_TYPE_SCRNSVR_TIMEOUT}
  WLX_SAS_TYPE_SCRNSVR_ACTIVITY = (3);
  {$EXTERNALSYM WLX_SAS_TYPE_SCRNSVR_ACTIVITY}
  WLX_SAS_TYPE_USER_LOGOFF      = (4);
  {$EXTERNALSYM WLX_SAS_TYPE_USER_LOGOFF}
  WLX_SAS_TYPE_SC_INSERT        = (5);
  {$EXTERNALSYM WLX_SAS_TYPE_SC_INSERT}
  WLX_SAS_TYPE_SC_REMOVE        = (6);
  {$EXTERNALSYM WLX_SAS_TYPE_SC_REMOVE}
  WLX_SAS_TYPE_AUTHENTICATED    = (7);
  {$EXTERNALSYM WLX_SAS_TYPE_AUTHENTICATED}
  WLX_SAS_TYPE_SC_FIRST_READER_ARRIVED = (8);
  {$EXTERNALSYM WLX_SAS_TYPE_SC_FIRST_READER_ARRIVED}
  WLX_SAS_TYPE_SC_LAST_READER_REMOVED  = (9);
  {$EXTERNALSYM WLX_SAS_TYPE_SC_LAST_READER_REMOVED}
  WLX_SAS_TYPE_SWITCHUSER       = (10);
  {$EXTERNALSYM WLX_SAS_TYPE_SWITCHUSER}
  WLX_SAS_TYPE_MAX_MSFT_VALUE   = (127);
  {$EXTERNALSYM WLX_SAS_TYPE_MAX_MSFT_VALUE}

//
// This structure is available through WlxGetOption, and is
// passed as the lParam for any S/C SAS notices sent to windows
//

type
  PWLX_SC_NOTIFICATION_INFO = ^WLX_SC_NOTIFICATION_INFO;
  {$EXTERNALSYM PWLX_SC_NOTIFICATION_INFO}
  _WLX_SC_NOTIFICATION_INFO = record
    pszCard: PWSTR;
    pszReader: PWSTR;
    pszContainer: PWSTR;
    pszCryptoProvider: PWSTR;
  end;
  {$EXTERNALSYM _WLX_SC_NOTIFICATION_INFO}
  WLX_SC_NOTIFICATION_INFO = _WLX_SC_NOTIFICATION_INFO;
  {$EXTERNALSYM WLX_SC_NOTIFICATION_INFO}
  TWlxScNotificationInfo = WLX_SC_NOTIFICATION_INFO;
  PWlxScNotificationInfo = PWLX_SC_NOTIFICATION_INFO;

/////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////
//
// Upon successful logon, the GINA DLL may specify any of the following
// options to Winlogon (via the dwOptions parameter of the WlxLoggedOutSas()
// api).  When set, these options specify:
//
//      NO_PROFILE - Winlogon must NOT load a profile for the logged
//                   on user.  Either the GINA DLL will take care of
//                   this activity, or the user does not need a profile.
//

const
  WLX_LOGON_OPT_NO_PROFILE = ($00000001);
  {$EXTERNALSYM WLX_LOGON_OPT_NO_PROFILE}

/////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////
//
// GINA DLLs are expected to return account information to Winlogon
// following a successful logon.  This information allows Winlogon
// to support profile loading and supplemental network providers.
//
// To allow different sets of profile information to be returned
// by GINAs over time, the first DWORD of each profile structure
// is expected to contain a type-identifier.  The following constants
// are the defined profile type identifiers.
//

//
// Standard profile is V2_0
//

  WLX_PROFILE_TYPE_V1_0 = (1);
  {$EXTERNALSYM WLX_PROFILE_TYPE_V1_0}
  WLX_PROFILE_TYPE_V2_0 = (2);
  {$EXTERNALSYM WLX_PROFILE_TYPE_V2_0}

/////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////
//
// WlxLoggedOnSas() and WlxWkstaLockedSas() return an action
// value to Winlogon directing Winlogon to either remain unchanged
// or to perform some action (such as force-log the user off).
// These are the values that may be returned.  Note, however, that
// not all of the values may be returned by both of these api.  See
// the description of each api to see which values are expected from
// each.
//
//  LOGON              - User has logged on
//  NONE               - Don't change the state of the window station.
//  LOCK_WKSTA         - Lock the workstation, wait for next SAS.
//  LOGOFF             - Log the user off of the workstation.
//  SHUTDOWN           - Log the user off and shutdown the machine.
//  PWD_CHANGED        - Indicates that the user changed their password.  Notify network providers.
//  TASKLIST           - Invoke the task list.
//  UNLOCK_WKSTA       - Unlock the workstation.
//  FORCE_LOGOFF       - Forcibly log the user off.
//  SHUTDOWN_POWER_OFF - Turn off machine after shutting down.
//  SHUTDOWN_REBOOT    - Reboot machine after shutting down.
//  SHUTDOWN_SLEEP     - Put the machine to sleep
//  SHUTDOWN_SLEEP2    - Put the machine to sleep and disable wakeup events
//  SHUTDOWN_HIBERNATE - Hibernate the machine
//  RECONNECTED        - Session was reconnected to an earlier session
//

  WLX_SAS_ACTION_LOGON                = (1);
  {$EXTERNALSYM WLX_SAS_ACTION_LOGON}
  WLX_SAS_ACTION_NONE                 = (2);
  {$EXTERNALSYM WLX_SAS_ACTION_NONE}
  WLX_SAS_ACTION_LOCK_WKSTA           = (3);
  {$EXTERNALSYM WLX_SAS_ACTION_LOCK_WKSTA}
  WLX_SAS_ACTION_LOGOFF               = (4);
  {$EXTERNALSYM WLX_SAS_ACTION_LOGOFF}
  WLX_SAS_ACTION_SHUTDOWN             = (5);
  {$EXTERNALSYM WLX_SAS_ACTION_SHUTDOWN}
  WLX_SAS_ACTION_PWD_CHANGED          = (6);
  {$EXTERNALSYM WLX_SAS_ACTION_PWD_CHANGED}
  WLX_SAS_ACTION_TASKLIST             = (7);
  {$EXTERNALSYM WLX_SAS_ACTION_TASKLIST}
  WLX_SAS_ACTION_UNLOCK_WKSTA         = (8);
  {$EXTERNALSYM WLX_SAS_ACTION_UNLOCK_WKSTA}
  WLX_SAS_ACTION_FORCE_LOGOFF         = (9);
  {$EXTERNALSYM WLX_SAS_ACTION_FORCE_LOGOFF}
  WLX_SAS_ACTION_SHUTDOWN_POWER_OFF   = (10);
  {$EXTERNALSYM WLX_SAS_ACTION_SHUTDOWN_POWER_OFF}
  WLX_SAS_ACTION_SHUTDOWN_REBOOT      = (11);
  {$EXTERNALSYM WLX_SAS_ACTION_SHUTDOWN_REBOOT}
  WLX_SAS_ACTION_SHUTDOWN_SLEEP       = (12);
  {$EXTERNALSYM WLX_SAS_ACTION_SHUTDOWN_SLEEP}
  WLX_SAS_ACTION_SHUTDOWN_SLEEP2      = (13);
  {$EXTERNALSYM WLX_SAS_ACTION_SHUTDOWN_SLEEP2}
  WLX_SAS_ACTION_SHUTDOWN_HIBERNATE   = (14);
  {$EXTERNALSYM WLX_SAS_ACTION_SHUTDOWN_HIBERNATE}
  WLX_SAS_ACTION_RECONNECTED          = (15);
  {$EXTERNALSYM WLX_SAS_ACTION_RECONNECTED}
  WLX_SAS_ACTION_DELAYED_FORCE_LOGOFF = (16);
  {$EXTERNALSYM WLX_SAS_ACTION_DELAYED_FORCE_LOGOFF}
  WLX_SAS_ACTION_SWITCH_CONSOLE       = (17);
  {$EXTERNALSYM WLX_SAS_ACTION_SWITCH_CONSOLE}

////////////////////////////////////////////////////////////////////////
//                                                                    //
//  Window Messages                                                   //
//                                                                    //
////////////////////////////////////////////////////////////////////////

//
// The WM_SAS is defined as follows
//
//  The wParam parameter has the SAS Type (above)

  WLX_WM_SAS = (WM_USER + 601);
  {$EXTERNALSYM WLX_WM_SAS}

//
// Dialog return values
//
// These may be returned by dialogs started by a GINA dll.
//

  WLX_DLG_SAS                  = 101;
  {$EXTERNALSYM WLX_DLG_SAS}
  WLX_DLG_INPUT_TIMEOUT        = 102; // Input (keys, etc) timed out
  {$EXTERNALSYM WLX_DLG_INPUT_TIMEOUT}
  WLX_DLG_SCREEN_SAVER_TIMEOUT = 103; // Screen Saver activated
  {$EXTERNALSYM WLX_DLG_SCREEN_SAVER_TIMEOUT}
  WLX_DLG_USER_LOGOFF          = 104; // User logged off
  {$EXTERNALSYM WLX_DLG_USER_LOGOFF}

/////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////
//
// The WLX_PROFILE_* structure is returned from a GINA DLL
// following authentication.  This information is used by Winlogon
// to support supplemental Network Providers and to load the
// newly logged-on user's profile.
//
// Winlogon is responsible for freeing both the profile structure
// and the fields within the structure that are marked as separately
// deallocatable.
//

type
  PWLX_PROFILE_V1_0 = ^WLX_PROFILE_V1_0;
  {$EXTERNALSYM PWLX_PROFILE_V1_0}
  _WLX_PROFILE_V1_0 = record
    //
    // This field identifies the type of profile being returned by a
    // GINA DLL.  Profile types are defined with the prefix
    // WLX_PROFILE_TYPE_xxx.  It allows Winlogon to typecast the
    // structure so the remainder of the structure may be referenced.
    //
    dwType: DWORD;
    //
    // pathname of profile to load for user.
    //
    // The buffer pointed to by this field must be separately allocated.
    // Winlogon will free the buffer when it is no longer needed.
    //
    //
    pszProfile: PWSTR;
  end;
  {$EXTERNALSYM _WLX_PROFILE_V1_0}
  WLX_PROFILE_V1_0 = _WLX_PROFILE_V1_0;
  {$EXTERNALSYM WLX_PROFILE_V1_0}
  TWlxProfileV1_0 = WLX_PROFILE_V1_0;
  PWlxProfileV1_0 = PWLX_PROFILE_V1_0;

  PWLX_PROFILE_V2_0 = ^WLX_PROFILE_V2_0;
  {$EXTERNALSYM PWLX_PROFILE_V2_0}
  _WLX_PROFILE_V2_0 = record
    //
    // This field identifies the type of profile being returned by a
    // GINA DLL.  Profile types are defined with the prefix
    // WLX_PROFILE_TYPE_xxx.  It allows Winlogon to typecast the
    // structure so the remainder of the structure may be referenced.
    //
    dwType: DWORD;
    //
    // pathname of profile to load for user.
    //
    // This parameter can be NULL.  If so, the user has a local
    // profile only.
    //
    // The buffer pointed to by this field must be separately allocated.
    // Winlogon will free the buffer when it is no longer needed.
    //
    //
    pszProfile: PWSTR;
    //
    // pathname of policy to load for user.
    //
    // This parameter can be NULL which prevents network wide policy
    // from being applied.
    //
    // The buffer pointed to by this field must be separately allocated.
    // Winlogon will free the buffer when it is no longer needed.
    //
    //
    pszPolicy: PWSTR;
    //
    // pathname of network default user profile
    //
    // This parameter can be NULL, which causes the Default User
    // profile on the local machine to be used.
    //
    // The buffer pointed to by this field must be separately allocated.
    // Winlogon will free the buffer when it is no longer needed.
    //
    //
    pszNetworkDefaultUserProfile: PWSTR;
    //
    // name of the server which validated the user account
    //
    // This is used to enumerate globals groups the user belongs
    // to for policy support.  This parameter can be NULL.
    //
    // The buffer pointed to by this field must be separately allocated.
    // Winlogon will free the buffer when it is no longer needed.
    //
    //
    pszServerName: PWSTR;
    //
    // pointer to a series of null terminated environment variables
    //
    // envname=environment variable value
    //   - or -
    // envname=%OtherVar%\more text
    //
    // Each environment variable is NULL terminated with the last
    // environment variable double NULL terminated.  These variables
    // are set into the user's initial environment.  The environment
    // variable value can contain other environment variables wrapped
    // in "%" signs. This parameter can be NULL.
    //
    // The buffer pointed to by this field must be separately allocated.
    // Winlogon will free the buffer when it is no longer needed.
    //
    //
    pszEnvironment: PWSTR;
  end;
  {$EXTERNALSYM _WLX_PROFILE_V2_0}
  WLX_PROFILE_V2_0 = _WLX_PROFILE_V2_0;
  {$EXTERNALSYM WLX_PROFILE_V2_0}
  TWlxProfileV2_0 = WLX_PROFILE_V2_0;
  PWlxProfileV2_0 = PWLX_PROFILE_V2_0;

/////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////
//
// The WLX_NPR_NOTIFICATION_INFO structure is returned
// from a GINA DLL following successful authentication.
// This information is used by Winlogon to provide
// identification and authentication information already
// collected to network providers.  Winlogon is
// responsible for freeing both the main structure and all
// string and other buffers pointed to from within the
// structure.
//

  PWLX_MPR_NOTIFY_INFO = ^WLX_MPR_NOTIFY_INFO;
  {$EXTERNALSYM PWLX_MPR_NOTIFY_INFO}
  _WLX_MPR_NOTIFY_INFO = record
    //
    // The name of the account logged onto (e.g. REDMOND\Joe).
    // The string pointed to by this field must be separately
    // allocated and will be separately deallocated by Winlogon.
    //
    pszUserName: PWSTR;
    //
    // The string pointed to by this field must be separately
    // allocated and will be separately deallocated by Winlogon.
    //
    pszDomain: PWSTR;
    //
    // Cleartext password of the user account.  If the OldPassword
    // field is non-null, then this field contains the new password
    // in a password change operation.  The string pointed to by
    // this field must be separately allocated and will be seperately
    // deallocated by Winlogon.
    //
    pszPassword: PWSTR;
    //
    // Cleartext old password of the user account whose password
    // has just been changed.  The Password field contains the new
    // password.  The string pointed to by this field must be
    // separately allocated and will be separately deallocated by
    // Winlogon.
    //
    pszOldPassword: PWSTR;
  end;
  {$EXTERNALSYM _WLX_MPR_NOTIFY_INFO}
  WLX_MPR_NOTIFY_INFO = _WLX_MPR_NOTIFY_INFO;
  {$EXTERNALSYM WLX_MPR_NOTIFY_INFO}
  TWlxMprNotifyInfo = WLX_MPR_NOTIFY_INFO;
  PWlxMprNotifyInfo = PWLX_MPR_NOTIFY_INFO;

/////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////
//
// WLX_TERMINAL_SERVICES_DATA is used by the GINA during a
// WlxQueryTerminalServicesData() callback into WinLogon from the
// WlxLoggedOutSAS() context, after the user name and domain are known.
// This structure relates to TS user configuration information which is
// retrieved from the Domain Controller and SAM database. Having WinLogon
// pass this information means the GINA does not need to do the same
// off-machines lookups again.
//

const
  WLX_DIRECTORY_LENGTH = 256;
  {$EXTERNALSYM WLX_DIRECTORY_LENGTH}

type
  PWLX_TERMINAL_SERVICES_DATA = ^WLX_TERMINAL_SERVICES_DATA;
  {$EXTERNALSYM PWLX_TERMINAL_SERVICES_DATA}
  _WLX_TERMINAL_SERVICES_DATA = record
    //
    // TS profile path, overrides the standard profile path.
    //
    ProfilePath: array [0..WLX_DIRECTORY_LENGTH] of WCHAR;
    //
    // TS home directory, overrides standard home directory.
    //
    HomeDir: array [0..WLX_DIRECTORY_LENGTH] of WCHAR;
    //
    // TS home directory drive, overrides standard drive.
    //
    HomeDirDrive: array [0..3] of WCHAR;
  end;
  {$EXTERNALSYM _WLX_TERMINAL_SERVICES_DATA}
  WLX_TERMINAL_SERVICES_DATA = _WLX_TERMINAL_SERVICES_DATA;
  {$EXTERNALSYM WLX_TERMINAL_SERVICES_DATA}
  TWlxTerminalServicesData = WLX_TERMINAL_SERVICES_DATA;
  PWlxTerminalServicesData = PWLX_TERMINAL_SERVICES_DATA;

/////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////
//
// The WLX_CLIENT_CREDENTIALS_INFO structure is returned
// from winlogon from the WlxQueryClientCredentials() call.
//
// This allows a network client WinStation to pass client
// credentials for automatic logon.
//
// The MSGINA DLL is responsible for freeing the memory
// and substrings with LocalFree().
//

const
  WLX_CREDENTIAL_TYPE_V1_0 = (1);
  {$EXTERNALSYM WLX_CREDENTIAL_TYPE_V1_0}
  WLX_CREDENTIAL_TYPE_V2_0 = (2);
  {$EXTERNALSYM WLX_CREDENTIAL_TYPE_V2_0}

type
  PWLX_CLIENT_CREDENTIALS_INFO_V1_0 = ^WLX_CLIENT_CREDENTIALS_INFO_V1_0;
  {$EXTERNALSYM PWLX_CLIENT_CREDENTIALS_INFO_V1_0}
  _WLX_CLIENT_CREDENTIALS_INFO = record
    //
    // This field identifies the type of credentials structure being allocated
    // by GINA DLL.  Credential types are defined with the prefix
    // WLX_CREDENTIAL_TYPE_xxx.  It allows Winlogon to typecast the
    // structure so the remainder of the structure may be referenced.
    //
    dwType: DWORD;
    pszUserName: PWSTR;
    pszDomain: PWSTR;
    pszPassword: PWSTR;
    //
    // This field forces a prompt for the password. This
    // is due to an administrator override.
    //
    // This allows the distinguishing of autologon
    // with no password.
    //
    fPromptForPassword: BOOL;
  end;
  {$EXTERNALSYM _WLX_CLIENT_CREDENTIALS_INFO}
  WLX_CLIENT_CREDENTIALS_INFO_V1_0 = _WLX_CLIENT_CREDENTIALS_INFO;
  {$EXTERNALSYM WLX_CLIENT_CREDENTIALS_INFO_V1_0}
  TWlxClientCredentialsInfoV1_0 = WLX_CLIENT_CREDENTIALS_INFO_V1_0;
  PWlxClientCredentialsInfoV1_0 = PWLX_CLIENT_CREDENTIALS_INFO_V1_0;

  _WLX_CLIENT_CREDENTIALS_INFO_V2_0 = record
    dwType: DWORD;
    pszUserName: PWSTR;
    pszDomain: PWSTR;
    pszPassword: PWSTR;
    fPromptForPassword: BOOL;
    //
    // This field tells winlogon to disconnect/abort the logon attempt if the
    // provided password is incorrect, or if it should reprompt (current
    // behavior)
    //
    fDisconnectOnLogonFailure: BOOL;
  end;
  {$EXTERNALSYM _WLX_CLIENT_CREDENTIALS_INFO_V2_0}
  WLX_CLIENT_CREDENTIALS_INFO_V2_0 = _WLX_CLIENT_CREDENTIALS_INFO_V2_0;
  {$EXTERNALSYM WLX_CLIENT_CREDENTIALS_INFO_V2_0}
  PWLX_CLIENT_CREDENTIALS_INFO_V2_0 = ^WLX_CLIENT_CREDENTIALS_INFO_V2_0;
  {$EXTERNALSYM PWLX_CLIENT_CREDENTIALS_INFO_V2_0}
  TWlxClientCredentialsInfoV2_0 = WLX_CLIENT_CREDENTIALS_INFO_V2_0;
  PWlxClientCredentialsInfoV2_0 = PWLX_CLIENT_CREDENTIALS_INFO_V2_0;  

/////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////
//
// The WLX_CONSOLESWITCH_CREDENTIALS_INFO structure is returned
// from gina in response to WlxGetConsoleSwitchCredentials calls.

// This structure is also returned from winlogon in response to
// to WlxQueryConsoleSwitchCredentials call
//
// This is used to implement single session Terminal Server. A remote
// session winlogon calls WlxGetConsoleSwitchCredentials to get the token
// and other info of the logged on user from msgina. This info is then passed to
// the console session winlogon to autologon the user on the console session.
// The gina on console session calls WlxQueryConsoleSwitchCredentials to get
// this info from winlogon and logs on the user.
//
// The caller is responsible for freeing the memory
// and substrings with LocalFree().
//

const
  WLX_CONSOLESWITCHCREDENTIAL_TYPE_V1_0 = (1);
  {$EXTERNALSYM WLX_CONSOLESWITCHCREDENTIAL_TYPE_V1_0}

type
  _WLX_CONSOLESWITCH_CREDENTIALS_INFO_V1_0 = record

    //
    // This field identifies the type of credentials structure being allocated
    // Credential types are defined with the prefix
    // WLX_CONSOLESWITCHCREDENTIAL_TYPE_xxx.  It allows Winlogon to typecast the
    // structure so the remainder of the structure may be referenced.
    //

    dwType: DWORD;

    UserToken: HANDLE;
    LogonId: LUID;
    Quotas: QUOTA_LIMITS;
    UserName: PWSTR;
    Domain: PWSTR;
    LogonTime: LARGE_INTEGER;
    SmartCardLogon: BOOL;
    ProfileLength: ULONG;

    //
    // From MSV1_0_INTERACTIVE_PROFILE
    //
    MessageType: DWORD;
    LogonCount: USHORT;
    BadPasswordCount: USHORT;
    ProfileLogonTime: LARGE_INTEGER;
    LogoffTime: LARGE_INTEGER;
    KickOffTime: LARGE_INTEGER;
    PasswordLastSet: LARGE_INTEGER;
    PasswordCanChange: LARGE_INTEGER;
    PasswordMustChange: LARGE_INTEGER;
    LogonScript: PWSTR;
    HomeDirectory: PWSTR;
    FullName: PWSTR;
    ProfilePath: PWSTR;
    HomeDirectoryDrive: PWSTR;
    LogonServer: PWSTR;
    UserFlags: ULONG;
    PrivateDataLen: ULONG;
    PrivateData: PBYTE;
  end;
  {$EXTERNALSYM _WLX_CONSOLESWITCH_CREDENTIALS_INFO_V1_0}
  WLX_CONSOLESWITCH_CREDENTIALS_INFO_V1_0 = _WLX_CONSOLESWITCH_CREDENTIALS_INFO_V1_0;
  {$EXTERNALSYM WLX_CONSOLESWITCH_CREDENTIALS_INFO_V1_0}
  PWLX_CONSOLESWITCH_CREDENTIALS_INFO_V1_0 = ^WLX_CONSOLESWITCH_CREDENTIALS_INFO_V1_0;
  {$EXTERNALSYM PWLX_CONSOLESWITCH_CREDENTIALS_INFO_V1_0}
  TWlxConsoleSwitchCredentialsInfoV1_0 = WLX_CONSOLESWITCH_CREDENTIALS_INFO_V1_0;
  PWlxConsoleSwitchCredentialsInfoV1_0 = PWLX_CONSOLESWITCH_CREDENTIALS_INFO_V1_0;  

////////////////////////////////////////////////////////////////////////
//                                                                    //
//  Services that replacement GINAs   ** MUST ** provide              //
//                                                                    //
////////////////////////////////////////////////////////////////////////

{$IFDEF IMPORT_MS_GINA}

{$IFDEF MSGINA1_0}

function WlxNegotiate(dwWinlogonVersion: DWORD; var pdwDllVersion: WORD): BOOL; stdcall;
{$EXTERNALSYM WlxNegotiate}

function WlxInitialize(lpWinsta: LPWSTR; hWlx: HANDLE; pvReserved: PVOID;
  pWinlogonFunctions: PVOID; var pWlxContext: PVOID): BOOL; stdcall;
{$EXTERNALSYM WlxInitialize}

procedure WlxDisplaySASNotice(pWlxContext: PVOID); stdcall;
{$EXTERNALSYM WlxDisplaySASNotice}

function WlxLoggedOutSAS(pWlxContext: PVOID; dwSasType: DWORD;
  var pAuthenticationId: LUID; var pLogonSid: SID; var pdwOptions: DWORD;
  var phToken: HANDLE; var pNprNotifyInfo: WLX_MPR_NOTIFY_INFO;
  var pProfile: PVOID): Integer; stdcall;
{$EXTERNALSYM WlxLoggedOutSAS}

function WlxActivateUserShell(pWlxContext: PVOID; pszDesktopName: PWSTR;
  pszMprLogonScript: PWSTR; pEnvironment: PVOID): BOOL; stdcall;
{$EXTERNALSYM WlxActivateUserShell}

function WlxLoggedOnSAS(pWlxContext: PVOID; dwSasType: DWORD; pReserved: PVOID): Integer; stdcall;
{$EXTERNALSYM WlxLoggedOnSAS}

procedure WlxDisplayLockedNotice(pWlxContext: PVOID); stdcall;
{$EXTERNALSYM WlxDisplayLockedNotice}

function WlxWkstaLockedSAS(pWlxContext: PVOID; dwSasType: DWORD): Integer; stdcall;
{$EXTERNALSYM WlxWkstaLockedSAS}

function WlxIsLockOk(pWlxContext: PVOID): BOOL; stdcall;
{$EXTERNALSYM WlxIsLockOk}

function WlxIsLogoffOk(pWlxContext: PVOID): BOOL; stdcall;
{$EXTERNALSYM WlxIsLogoffOk}

procedure WlxLogoff(pWlxContext: PVOID); stdcall;
{$EXTERNALSYM WlxLogoff}

procedure WlxShutdown(pWlxContext: PVOID; ShutdownType: DWORD); stdcall;
{$EXTERNALSYM WlxShutdown}

{$ENDIF}

{$IFDEF MSGINA1_1}

function WlxScreenSaverNotify(pWlxContext: PVOID; var pSecure: BOOL): BOOL; stdcall;
{$EXTERNALSYM WlxScreenSaverNotify}

function WlxStartApplication(pWlxContext: PVOID; pszDesktopName: PWSTR;
  pEnvironment: PVOID; pszCmdLine: PWSTR): BOOL; stdcall;
{$EXTERNALSYM WlxStartApplication}

{$ENDIF}

{$IFDEF MSGINA1_3}

function WlxNetworkProviderLoad(pWlxContext: PVOID;
  var pNprNotifyInfo: WLX_MPR_NOTIFY_INFO): BOOL; stdcall;
{$EXTERNALSYM WlxNetworkProviderLoad}

const
  STATUSMSG_OPTION_NOANIMATION   = $00000001;
  {$EXTERNALSYM STATUSMSG_OPTION_NOANIMATION}
  STATUSMSG_OPTION_SETFOREGROUND = $00000002;
  {$EXTERNALSYM STATUSMSG_OPTION_SETFOREGROUND}

function WlxDisplayStatusMessage(pWlxContext: PVOID; hDesktop: HDESK;
  dwOptions: DWORD; pTitle: PWSTR; pMessage: PWSTR): BOOL; stdcall;
{$EXTERNALSYM WlxDisplayStatusMessage}

function WlxGetStatusMessage(pWlxContext: PVOID; var pdwOptions: DWORD;
  pMessage: PWSTR; dwBufferSize: DWORD): BOOL; stdcall;
{$EXTERNALSYM WlxGetStatusMessage}

function WlxRemoveStatusMessage(pWlxContext: PVOID): BOOL; stdcall;
{$EXTERNALSYM WlxRemoveStatusMessage}

{$ENDIF}

{$IFDEF MSGINA1_4}

function WlxGetConsoleSwitchCredentials(pWlxContext, pCredInfo: PVOID): BOOL; stdcall;
{$EXTERNALSYM WlxGetConsoleSwitchCredentials}

procedure WlxReconnectNotify(pWlxContext: PVOID); stdcall;
{$EXTERNALSYM WlxReconnectNotify}

procedure WlxDisconnectNotify(pWlxContext: PVOID); stdcall;
{$EXTERNALSYM WlxDisconnectNotify}

{$ENDIF}

{$ENDIF IMPORT_MS_GINA}

////////////////////////////////////////////////////////////////////////
//                                                                    //
//  Services that Winlogon provides                                   //
//                                                                    //
////////////////////////////////////////////////////////////////////////

type
  PWLX_DESKTOP = ^WLX_DESKTOP;
  {$EXTERNALSYM PWLX_DESKTOP}
  _WLX_DESKTOP = record
    Size: DWORD;
    Flags: DWORD;
    hDesktop: HDESK;
    pszDesktopName: PWSTR;
  end;
  {$EXTERNALSYM _WLX_DESKTOP}
  WLX_DESKTOP = _WLX_DESKTOP;
  {$EXTERNALSYM WLX_DESKTOP}
  TWlxDesktop = WLX_DESKTOP;
  PWlxDesktop = PWLX_DESKTOP;

const
  WLX_DESKTOP_NAME   = $00000001; // Name present
  {$EXTERNALSYM WLX_DESKTOP_NAME}
  WLX_DESKTOP_HANDLE = $00000002; // Handle present
  {$EXTERNALSYM WLX_DESKTOP_HANDLE}

type
  PWLX_USE_CTRL_ALT_DEL = procedure (hWlx: HANDLE); stdcall;
  {$EXTERNALSYM PWLX_USE_CTRL_ALT_DEL}
  PWLX_SET_CONTEXT_POINTER = procedure (hWlx: HANDLE; pWlxContext: PVOID); stdcall;
  {$EXTERNALSYM PWLX_SET_CONTEXT_POINTER}
  PWLX_SAS_NOTIFY = procedure (hWlx: HANDLE; dwSasType: DWORD); stdcall;
  {$EXTERNALSYM PWLX_SAS_NOTIFY}
  PWLX_SET_TIMEOUT = function (hWlx: HANDLE; Timeout: DWORD): BOOL; stdcall;
  {$EXTERNALSYM PWLX_SET_TIMEOUT}
  PWLX_ASSIGN_SHELL_PROTECTION = function (hWlx, hToken, hProcess, hThread: HANDLE): Integer; stdcall;
  {$EXTERNALSYM PWLX_ASSIGN_SHELL_PROTECTION}
  PWLX_MESSAGE_BOX = function (hWlx: HANDLE; hwndOwner: HWND; lpszText,
    lpszTitle: LPWSTR; fuStyle: UINT): Integer; stdcall;
  {$EXTERNALSYM PWLX_MESSAGE_BOX}
  PWLX_DIALOG_BOX = function (hWlx, hInst: HANDLE; lpszTemplate: LPWSTR;
    hwndOwner: HWND; dlgprc: DLGPROC): Integer; stdcall;
  {$EXTERNALSYM PWLX_DIALOG_BOX}
  PWLX_DIALOG_BOX_INDIRECT = function (hWlx, hInst: HANDLE;
    hDialogTemplate: LPCDLGTEMPLATE; hwndOwner: HWND; dlgprc: DLGPROC): Integer; stdcall;
  {$EXTERNALSYM PWLX_DIALOG_BOX_INDIRECT}
  PWLX_DIALOG_BOX_PARAM = function (hWlx, hInst: HANDLE; lpszTemplate: LPWSTR;
    hwndOwner: HWND; dlgprc: DLGPROC; dwInitParam: LPARAM): Integer; stdcall;
  {$EXTERNALSYM PWLX_DIALOG_BOX_PARAM}
  PWLX_DIALOG_BOX_INDIRECT_PARAM = function (hWlx, hInst: HANDLE;
    hDialogTemplate: LPCDLGTEMPLATE; hwndOwner: HWND; dlgprc: DLGPROC;
    dwInitParam: LPARAM): Integer; stdcall;
  {$EXTERNALSYM PWLX_DIALOG_BOX_INDIRECT_PARAM}
  PWLX_SWITCH_DESKTOP_TO_USER = function (hWlx: HANDLE): Integer; stdcall;
  {$EXTERNALSYM PWLX_SWITCH_DESKTOP_TO_USER}
  PWLX_SWITCH_DESKTOP_TO_WINLOGON = function (hWlx: HANDLE): Integer; stdcall;
  {$EXTERNALSYM PWLX_SWITCH_DESKTOP_TO_WINLOGON}
  PWLX_CHANGE_PASSWORD_NOTIFY = function (hWlx: HANDLE;
    var pMprInfo: WLX_MPR_NOTIFY_INFO; dwChangeInfo: DWORD): Integer; stdcall;
  {$EXTERNALSYM PWLX_CHANGE_PASSWORD_NOTIFY}
  PWLX_GET_SOURCE_DESKTOP = function (hWlx: HANDLE; var ppDesktop: PWLX_DESKTOP): BOOL; stdcall;
  {$EXTERNALSYM PWLX_GET_SOURCE_DESKTOP}
  PWLX_SET_RETURN_DESKTOP = function (hWlx: HANDLE; const pDesktop: WLX_DESKTOP): BOOL; stdcall;
  {$EXTERNALSYM PWLX_SET_RETURN_DESKTOP}
  PWLX_CREATE_USER_DESKTOP = function (hWlx, hToken: HANDLE; Flags: DWORD;
    pszDesktopName: PWSTR; var ppDesktop: PWLX_DESKTOP): BOOL; stdcall;
  {$EXTERNALSYM PWLX_CREATE_USER_DESKTOP}

const
  WLX_CREATE_INSTANCE_ONLY = $00000001;
  {$EXTERNALSYM WLX_CREATE_INSTANCE_ONLY}
  WLX_CREATE_USER          = $00000002;
  {$EXTERNALSYM WLX_CREATE_USER}

type
  PWLX_CHANGE_PASSWORD_NOTIFY_EX = function (hWlx: HANDLE;
    const pMprInfo: WLX_MPR_NOTIFY_INFO; dwChangeInfo: DWORD;
    ProviderName: PWSTR; Reserved: PVOID): Integer; stdcall;
  {$EXTERNALSYM PWLX_CHANGE_PASSWORD_NOTIFY_EX}
  PWLX_CLOSE_USER_DESKTOP = function (hWlx: HANDLE; const pDesktop: WLX_DESKTOP;
    hToken: HANDLE): BOOL; stdcall;
  {$EXTERNALSYM PWLX_CLOSE_USER_DESKTOP}
  PWLX_SET_OPTION = function (hWlx: HANDLE; Option: DWORD; Value: ULONG_PTR;
    var OldValue: ULONG_PTR): BOOL; stdcall;
  {$EXTERNALSYM PWLX_SET_OPTION}
  PWLX_GET_OPTION = function (hWlx: HANDLE; Option: DWORD; var Value: ULONG_PTR): BOOL; stdcall;
  {$EXTERNALSYM PWLX_GET_OPTION}
  PWLX_WIN31_MIGRATE = procedure (hWlx: HANDLE); stdcall;
  {$EXTERNALSYM PWLX_WIN31_MIGRATE}
  PWLX_QUERY_CLIENT_CREDENTIALS = function (var pCred: WLX_CLIENT_CREDENTIALS_INFO_V1_0): BOOL; stdcall;
  {$EXTERNALSYM PWLX_QUERY_CLIENT_CREDENTIALS}
  PWLX_QUERY_IC_CREDENTIALS = function (var pCred: WLX_CLIENT_CREDENTIALS_INFO_V1_0): BOOL; stdcall;
  {$EXTERNALSYM PWLX_QUERY_IC_CREDENTIALS}
  PWLX_QUERY_TS_LOGON_CREDENTIALS = function (pCred: PWLX_CLIENT_CREDENTIALS_INFO_V2_0): BOOL; stdcall;
  {$EXTERNALSYM PWLX_QUERY_TS_LOGON_CREDENTIALS}
  PWLX_DISCONNECT = function : BOOL; stdcall;
  {$EXTERNALSYM PWLX_DISCONNECT}
  PWLX_QUERY_TERMINAL_SERVICES_DATA = function (hWlx: HANDLE;
    var pTSData: WLX_TERMINAL_SERVICES_DATA; UserName, Domain: PWCHAR): DWORD; stdcall;
  {$EXTERNALSYM PWLX_DISCONNECT}
  PWLX_QUERY_CONSOLESWITCH_CREDENTIALS = function (pCred: PWLX_CONSOLESWITCH_CREDENTIALS_INFO_V1_0): DWORD; stdcall;
  {$EXTERNALSYM PWLX_QUERY_CONSOLESWITCH_CREDENTIALS}

//
// Options that can be get or set:
//

const
  WLX_OPTION_USE_CTRL_ALT_DEL  = $00000001;
  {$EXTERNALSYM WLX_OPTION_USE_CTRL_ALT_DEL}
  WLX_OPTION_CONTEXT_POINTER   = $00000002;
  {$EXTERNALSYM WLX_OPTION_CONTEXT_POINTER}
  WLX_OPTION_USE_SMART_CARD    = $00000003;
  {$EXTERNALSYM WLX_OPTION_USE_SMART_CARD}
  WLX_OPTION_FORCE_LOGOFF_TIME = $00000004;
  {$EXTERNALSYM WLX_OPTION_FORCE_LOGOFF_TIME}
  WLX_OPTION_IGNORE_AUTO_LOGON = $00000008;
  {$EXTERNALSYM WLX_OPTION_IGNORE_AUTO_LOGON}
  WLX_OPTION_NO_SWITCH_ON_SAS  = $00000009;
  {$EXTERNALSYM WLX_OPTION_NO_SWITCH_ON_SAS}

//
// Options that can be queried only:
//

  WLX_OPTION_SMART_CARD_PRESENT  = $00010001;
  {$EXTERNALSYM WLX_OPTION_SMART_CARD_PRESENT}
  WLX_OPTION_SMART_CARD_INFO     = $00010002;
  {$EXTERNALSYM WLX_OPTION_SMART_CARD_INFO}
  WLX_OPTION_DISPATCH_TABLE_SIZE = $00010003;
  {$EXTERNALSYM WLX_OPTION_DISPATCH_TABLE_SIZE}

////////////////////////////////////////////////////////////////////////
//                                                                    //
//  Function dispatch tables.                                         //
//  One of the following tables will be passed to the GINA DLL        //
//  in the WlxInitialize() call during initialization.                //
//                                                                    //
////////////////////////////////////////////////////////////////////////

type
  PWLX_DISPATCH_VERSION_1_0 = ^WLX_DISPATCH_VERSION_1_0;
  {$EXTERNALSYM PWLX_DISPATCH_VERSION_1_0}
  _WLX_DISPATCH_VERSION_1_0 = record
    WlxUseCtrlAltDel: PWLX_USE_CTRL_ALT_DEL;
    WlxSetContextPointer: PWLX_SET_CONTEXT_POINTER;
    WlxSasNotify: PWLX_SAS_NOTIFY;
    WlxSetTimeout: PWLX_SET_TIMEOUT;
    WlxAssignShellProtection: PWLX_ASSIGN_SHELL_PROTECTION;
    WlxMessageBox: PWLX_MESSAGE_BOX;
    WlxDialogBox: PWLX_DIALOG_BOX;
    WlxDialogBoxParam: PWLX_DIALOG_BOX_PARAM;
    WlxDialogBoxIndirect: PWLX_DIALOG_BOX_INDIRECT;
    WlxDialogBoxIndirectParam: PWLX_DIALOG_BOX_INDIRECT_PARAM;
    WlxSwitchDesktopToUser: PWLX_SWITCH_DESKTOP_TO_USER;
    WlxSwitchDesktopToWinlogon: PWLX_SWITCH_DESKTOP_TO_WINLOGON;
    WlxChangePasswordNotify: PWLX_CHANGE_PASSWORD_NOTIFY;
  end;
  {$EXTERNALSYM _WLX_DISPATCH_VERSION_1_0}
  WLX_DISPATCH_VERSION_1_0 = _WLX_DISPATCH_VERSION_1_0;
  {$EXTERNALSYM WLX_DISPATCH_VERSION_1_0}
  TWlxDispatchVersion1_0 = WLX_DISPATCH_VERSION_1_0;
  PWlxDispatchVersion1_0 = PWLX_DISPATCH_VERSION_1_0;

  PWLX_DISPATCH_VERSION_1_1 = ^WLX_DISPATCH_VERSION_1_1;
  {$EXTERNALSYM PWLX_DISPATCH_VERSION_1_1}
  _WLX_DISPATCH_VERSION_1_1 = record
    WlxUseCtrlAltDel: PWLX_USE_CTRL_ALT_DEL;
    WlxSetContextPointer: PWLX_SET_CONTEXT_POINTER;
    WlxSasNotify: PWLX_SAS_NOTIFY;
    WlxSetTimeout: PWLX_SET_TIMEOUT;
    WlxAssignShellProtection: PWLX_ASSIGN_SHELL_PROTECTION;
    WlxMessageBox: PWLX_MESSAGE_BOX;
    WlxDialogBox: PWLX_DIALOG_BOX;
    WlxDialogBoxParam: PWLX_DIALOG_BOX_PARAM;
    WlxDialogBoxIndirect: PWLX_DIALOG_BOX_INDIRECT;
    WlxDialogBoxIndirectParam: PWLX_DIALOG_BOX_INDIRECT_PARAM;
    WlxSwitchDesktopToUser: PWLX_SWITCH_DESKTOP_TO_USER;
    WlxSwitchDesktopToWinlogon: PWLX_SWITCH_DESKTOP_TO_WINLOGON;
    WlxChangePasswordNotify: PWLX_CHANGE_PASSWORD_NOTIFY;
    WlxGetSourceDesktop: PWLX_GET_SOURCE_DESKTOP;
    WlxSetReturnDesktop: PWLX_SET_RETURN_DESKTOP;
    WlxCreateUserDesktop: PWLX_CREATE_USER_DESKTOP;
    WlxChangePasswordNotifyEx: PWLX_CHANGE_PASSWORD_NOTIFY_EX;
  end;
  {$EXTERNALSYM _WLX_DISPATCH_VERSION_1_1}
  WLX_DISPATCH_VERSION_1_1 = _WLX_DISPATCH_VERSION_1_1;
  {$EXTERNALSYM WLX_DISPATCH_VERSION_1_1}
  TWlxDispatchVersion1_1 = WLX_DISPATCH_VERSION_1_1;
  PWlxDispatchVersion1_1 = PWLX_DISPATCH_VERSION_1_1;

  PWLX_DISPATCH_VERSION_1_2 = ^WLX_DISPATCH_VERSION_1_2;
  {$EXTERNALSYM PWLX_DISPATCH_VERSION_1_2}
  _WLX_DISPATCH_VERSION_1_2 = record
    WlxUseCtrlAltDel: PWLX_USE_CTRL_ALT_DEL;
    WlxSetContextPointer: PWLX_SET_CONTEXT_POINTER;
    WlxSasNotify: PWLX_SAS_NOTIFY;
    WlxSetTimeout: PWLX_SET_TIMEOUT;
    WlxAssignShellProtection: PWLX_ASSIGN_SHELL_PROTECTION;
    WlxMessageBox: PWLX_MESSAGE_BOX;
    WlxDialogBox: PWLX_DIALOG_BOX;
    WlxDialogBoxParam: PWLX_DIALOG_BOX_PARAM;
    WlxDialogBoxIndirect: PWLX_DIALOG_BOX_INDIRECT;
    WlxDialogBoxIndirectParam: PWLX_DIALOG_BOX_INDIRECT_PARAM;
    WlxSwitchDesktopToUser: PWLX_SWITCH_DESKTOP_TO_USER;
    WlxSwitchDesktopToWinlogon: PWLX_SWITCH_DESKTOP_TO_WINLOGON;
    WlxChangePasswordNotify: PWLX_CHANGE_PASSWORD_NOTIFY;
    WlxGetSourceDesktop: PWLX_GET_SOURCE_DESKTOP;
    WlxSetReturnDesktop: PWLX_SET_RETURN_DESKTOP;
    WlxCreateUserDesktop: PWLX_CREATE_USER_DESKTOP;
    WlxChangePasswordNotifyEx: PWLX_CHANGE_PASSWORD_NOTIFY_EX;
    WlxCloseUserDesktop : PWLX_CLOSE_USER_DESKTOP;
  end;
  {$EXTERNALSYM _WLX_DISPATCH_VERSION_1_2}
  WLX_DISPATCH_VERSION_1_2 = _WLX_DISPATCH_VERSION_1_2;
  {$EXTERNALSYM WLX_DISPATCH_VERSION_1_2}
  TWlxDispatchVersion1_2 = WLX_DISPATCH_VERSION_1_2;
  PWlxDispatchVersion1_2 = PWLX_DISPATCH_VERSION_1_2;

  PWLX_DISPATCH_VERSION_1_3 = ^WLX_DISPATCH_VERSION_1_3;
  {$EXTERNALSYM PWLX_DISPATCH_VERSION_1_3}
  _WLX_DISPATCH_VERSION_1_3 = record
    WlxUseCtrlAltDel: PWLX_USE_CTRL_ALT_DEL;
    WlxSetContextPointer: PWLX_SET_CONTEXT_POINTER;
    WlxSasNotify: PWLX_SAS_NOTIFY;
    WlxSetTimeout: PWLX_SET_TIMEOUT;
    WlxAssignShellProtection: PWLX_ASSIGN_SHELL_PROTECTION;
    WlxMessageBox: PWLX_MESSAGE_BOX;
    WlxDialogBox: PWLX_DIALOG_BOX;
    WlxDialogBoxParam: PWLX_DIALOG_BOX_PARAM;
    WlxDialogBoxIndirect: PWLX_DIALOG_BOX_INDIRECT;
    WlxDialogBoxIndirectParam: PWLX_DIALOG_BOX_INDIRECT_PARAM;
    WlxSwitchDesktopToUser: PWLX_SWITCH_DESKTOP_TO_USER;
    WlxSwitchDesktopToWinlogon: PWLX_SWITCH_DESKTOP_TO_WINLOGON;
    WlxChangePasswordNotify: PWLX_CHANGE_PASSWORD_NOTIFY;
    WlxGetSourceDesktop: PWLX_GET_SOURCE_DESKTOP;
    WlxSetReturnDesktop: PWLX_SET_RETURN_DESKTOP;
    WlxCreateUserDesktop: PWLX_CREATE_USER_DESKTOP;
    WlxChangePasswordNotifyEx: PWLX_CHANGE_PASSWORD_NOTIFY_EX;
    WlxCloseUserDesktop : PWLX_CLOSE_USER_DESKTOP;
    WlxSetOption: PWLX_SET_OPTION;
    WlxGetOption: PWLX_GET_OPTION;
    WlxWin31Migrate: PWLX_WIN31_MIGRATE;
    WlxQueryClientCredentials: PWLX_QUERY_CLIENT_CREDENTIALS;
    WlxQueryInetConnectorCredentials: PWLX_QUERY_IC_CREDENTIALS;
    WlxDisconnect: PWLX_DISCONNECT;
    WlxQueryTerminalServicesData: PWLX_QUERY_TERMINAL_SERVICES_DATA;
  end;
  {$EXTERNALSYM _WLX_DISPATCH_VERSION_1_3}
  WLX_DISPATCH_VERSION_1_3 = _WLX_DISPATCH_VERSION_1_3;
  {$EXTERNALSYM WLX_DISPATCH_VERSION_1_3}
  TWlxDispatchVersion1_3 = WLX_DISPATCH_VERSION_1_3;
  PWlxDispatchVersion1_3 = PWLX_DISPATCH_VERSION_1_3;

  PWLX_DISPATCH_VERSION_1_4 = ^WLX_DISPATCH_VERSION_1_4;
  {$EXTERNALSYM PWLX_DISPATCH_VERSION_1_4}
  _WLX_DISPATCH_VERSION_1_4 = record
    WlxUseCtrlAltDel: PWLX_USE_CTRL_ALT_DEL;
    WlxSetContextPointer: PWLX_SET_CONTEXT_POINTER;
    WlxSasNotify: PWLX_SAS_NOTIFY;
    WlxSetTimeout: PWLX_SET_TIMEOUT;
    WlxAssignShellProtection: PWLX_ASSIGN_SHELL_PROTECTION;
    WlxMessageBox: PWLX_MESSAGE_BOX;
    WlxDialogBox: PWLX_DIALOG_BOX;
    WlxDialogBoxParam: PWLX_DIALOG_BOX_PARAM;
    WlxDialogBoxIndirect: PWLX_DIALOG_BOX_INDIRECT;
    WlxDialogBoxIndirectParam: PWLX_DIALOG_BOX_INDIRECT_PARAM;
    WlxSwitchDesktopToUser: PWLX_SWITCH_DESKTOP_TO_USER;
    WlxSwitchDesktopToWinlogon: PWLX_SWITCH_DESKTOP_TO_WINLOGON;
    WlxChangePasswordNotify: PWLX_CHANGE_PASSWORD_NOTIFY;
    WlxGetSourceDesktop: PWLX_GET_SOURCE_DESKTOP;
    WlxSetReturnDesktop: PWLX_SET_RETURN_DESKTOP;
    WlxCreateUserDesktop: PWLX_CREATE_USER_DESKTOP;
    WlxChangePasswordNotifyEx: PWLX_CHANGE_PASSWORD_NOTIFY_EX;
    WlxCloseUserDesktop : PWLX_CLOSE_USER_DESKTOP;
    WlxSetOption: PWLX_SET_OPTION;
    WlxGetOption: PWLX_GET_OPTION;
    WlxWin31Migrate: PWLX_WIN31_MIGRATE;
    WlxQueryClientCredentials: PWLX_QUERY_CLIENT_CREDENTIALS;
    WlxQueryInetConnectorCredentials: PWLX_QUERY_IC_CREDENTIALS;
    WlxDisconnect: PWLX_DISCONNECT;
    WlxQueryTerminalServicesData: PWLX_QUERY_TERMINAL_SERVICES_DATA;
    WlxQueryConsoleSwitchCredentials: PWLX_QUERY_CONSOLESWITCH_CREDENTIALS;
    WlxQueryTsLogonCredentials: PWLX_QUERY_TS_LOGON_CREDENTIALS;
  end;
  {$EXTERNALSYM _WLX_DISPATCH_VERSION_1_4}
  WLX_DISPATCH_VERSION_1_4 = _WLX_DISPATCH_VERSION_1_4;
  {$EXTERNALSYM WLX_DISPATCH_VERSION_1_4}
  TWlxDispatchVersion1_4 = WLX_DISPATCH_VERSION_1_4;
  PWlxDispatchVersion1_4 = PWLX_DISPATCH_VERSION_1_4;

//
// Non-GINA notification DLLs
//

  PFNMSGECALLBACK = function (bVerbose: BOOL; lpMessage: LPWSTR): DWORD; stdcall;
  {$EXTERNALSYM PFNMSGECALLBACK}
  TFnMsgeCallback = PFNMSGECALLBACK;

  PWLX_NOTIFICATION_INFO = ^WLX_NOTIFICATION_INFO;
  {$EXTERNALSYM PWLX_NOTIFICATION_INFO}
  _WLX_NOTIFICATION_INFO = record
    Size: ULONG;
    Flags: ULONG;
    UserName: PWSTR;
    Domain: PWSTR;
    WindowStation: PWSTR;
    hToken: HANDLE;
    hDesktop: HDESK;
    pStatusCallback: PFNMSGECALLBACK;
  end;
  {$EXTERNALSYM _WLX_NOTIFICATION_INFO}
  WLX_NOTIFICATION_INFO = _WLX_NOTIFICATION_INFO;
  {$EXTERNALSYM WLX_NOTIFICATION_INFO}
  TWlxNotificationInfo = WLX_NOTIFICATION_INFO;
  PWlxNotificationInfo = PWLX_NOTIFICATION_INFO;

implementation

{$IFDEF IMPORT_MS_GINA}

const
  msgina = 'msgina.dll';

{$IFDEF MSGINA1_0}


{$IFDEF DYNAMIC_LINK}
var
  _WlxNegotiate: Pointer;

function WlxNegotiate;
begin
  GetProcedureAddress(_WlxNegotiate, msgina, 'WlxNegotiate');
  asm
    mov esp, ebp
    pop ebp
    jmp [_WlxNegotiate]
  end;
end;
{$ELSE}
function WlxNegotiate; external msgina name 'WlxNegotiate';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _WlxInitialize: Pointer;

function WlxInitialize;
begin
  GetProcedureAddress(_WlxInitialize, msgina, 'WlxInitialize');
  asm
    mov esp, ebp
    pop ebp
    jmp [_WlxInitialize]
  end;
end;
{$ELSE}
function WlxInitialize; external msgina name 'WlxInitialize';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _WlxDisplaySASNotice: Pointer;

procedure WlxDisplaySASNotice;
begin
  GetProcedureAddress(_WlxDisplaySASNotice, msgina, 'WlxDisplaySASNotice');
  asm
    mov esp, ebp
    pop ebp
    jmp [_WlxDisplaySASNotice]
  end;
end;
{$ELSE}
procedure WlxDisplaySASNotice; external msgina name 'WlxDisplaySASNotice';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _WlxLoggedOutSAS: Pointer;

function WlxLoggedOutSAS;
begin
  GetProcedureAddress(_WlxLoggedOutSAS, msgina, 'WlxLoggedOutSAS');
  asm
    mov esp, ebp
    pop ebp
    jmp [_WlxLoggedOutSAS]
  end;
end;
{$ELSE}
function WlxLoggedOutSAS; external msgina name 'WlxLoggedOutSAS';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _WlxActivateUserShell: Pointer;

function WlxActivateUserShell;
begin
  GetProcedureAddress(_WlxActivateUserShell, msgina, 'WlxActivateUserShell');
  asm
    mov esp, ebp
    pop ebp
    jmp [_WlxActivateUserShell]
  end;
end;
{$ELSE}
function WlxActivateUserShell; external msgina name 'WlxActivateUserShell';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _WlxLoggedOnSAS: Pointer;

function WlxLoggedOnSAS;
begin
  GetProcedureAddress(_WlxLoggedOnSAS, msgina, 'WlxLoggedOnSAS');
  asm
    mov esp, ebp
    pop ebp
    jmp [_WlxLoggedOnSAS]
  end;
end;
{$ELSE}
function WlxLoggedOnSAS; external msgina name 'WlxLoggedOnSAS';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _WlxDisplayLockedNotice: Pointer;

procedure WlxDisplayLockedNotice;
begin
  GetProcedureAddress(_WlxDisplayLockedNotice, msgina, 'WlxDisplayLockedNotice');
  asm
    mov esp, ebp
    pop ebp
    jmp [_WlxDisplayLockedNotice]
  end;
end;
{$ELSE}
procedure WlxDisplayLockedNotice; external msgina name 'WlxDisplayLockedNotice';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _WlxWkstaLockedSAS: Pointer;

function WlxWkstaLockedSAS;
begin
  GetProcedureAddress(_WlxWkstaLockedSAS, msgina, 'WlxWkstaLockedSAS');
  asm
    mov esp, ebp
    pop ebp
    jmp [_WlxWkstaLockedSAS]
  end;
end;
{$ELSE}
function WlxWkstaLockedSAS; external msgina name 'WlxWkstaLockedSAS';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _WlxIsLockOk: Pointer;

function WlxIsLockOk;
begin
  GetProcedureAddress(_WlxIsLockOk, msgina, 'WlxIsLockOk');
  asm
    mov esp, ebp
    pop ebp
    jmp [_WlxIsLockOk]
  end;
end;
{$ELSE}
function WlxIsLockOk; external msgina name 'WlxIsLockOk';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _WlxIsLogoffOk: Pointer;

function WlxIsLogoffOk;
begin
  GetProcedureAddress(_WlxIsLogoffOk, msgina, 'WlxIsLogoffOk');
  asm
    mov esp, ebp
    pop ebp
    jmp [_WlxIsLogoffOk]
  end;
end;
{$ELSE}
function WlxIsLogoffOk; external msgina name 'WlxIsLogoffOk';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _WlxLogoff: Pointer;

procedure WlxLogoff;
begin
  GetProcedureAddress(_WlxLogoff, msgina, 'WlxLogoff');
  asm
    mov esp, ebp
    pop ebp
    jmp [_WlxLogoff]
  end;
end;
{$ELSE}
procedure WlxLogoff; external msgina name 'WlxLogoff';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _WlxShutdown: Pointer;

procedure WlxShutdown;
begin
  GetProcedureAddress(_WlxShutdown, msgina, 'WlxShutdown');
  asm
    mov esp, ebp
    pop ebp
    jmp [_WlxShutdown]
  end;
end;
{$ELSE}
procedure WlxShutdown; external msgina name 'WlxShutdown';
{$ENDIF DYNAMIC_LINK}

{$ENDIF}

{$IFDEF MSGINA1_1}


{$IFDEF DYNAMIC_LINK}
var
  _WlxScreenSaverNotify: Pointer;

function WlxScreenSaverNotify;
begin
  GetProcedureAddress(_WlxScreenSaverNotify, msgina, 'WlxScreenSaverNotify');
  asm
    mov esp, ebp
    pop ebp
    jmp [_WlxScreenSaverNotify]
  end;
end;
{$ELSE}
function WlxScreenSaverNotify; external msgina name 'WlxScreenSaverNotify';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _WlxStartApplication: Pointer;

function WlxStartApplication;
begin
  GetProcedureAddress(_WlxStartApplication, msgina, 'WlxStartApplication');
  asm
    mov esp, ebp
    pop ebp
    jmp [_WlxStartApplication]
  end;
end;
{$ELSE}
function WlxStartApplication; external msgina name 'WlxStartApplication';
{$ENDIF DYNAMIC_LINK}

{$ENDIF}

{$IFDEF MSGINA1_3}


{$IFDEF DYNAMIC_LINK}
var
  _WlxNetworkProviderLoad: Pointer;

function WlxNetworkProviderLoad;
begin
  GetProcedureAddress(_WlxNetworkProviderLoad, msgina, 'WlxNetworkProviderLoad');
  asm
    mov esp, ebp
    pop ebp
    jmp [_WlxNetworkProviderLoad]
  end;
end;
{$ELSE}
function WlxNetworkProviderLoad; external msgina name 'WlxNetworkProviderLoad';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _WlxDisplayStatusMessage: Pointer;

function WlxDisplayStatusMessage;
begin
  GetProcedureAddress(_WlxDisplayStatusMessage, msgina, 'WlxDisplayStatusMessage');
  asm
    mov esp, ebp
    pop ebp
    jmp [_WlxDisplayStatusMessage]
  end;
end;
{$ELSE}
function WlxDisplayStatusMessage; external msgina name 'WlxDisplayStatusMessage';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _WlxGetStatusMessage: Pointer;

function WlxGetStatusMessage;
begin
  GetProcedureAddress(_WlxGetStatusMessage, msgina, 'WlxGetStatusMessage');
  asm
    mov esp, ebp
    pop ebp
    jmp [_WlxGetStatusMessage]
  end;
end;
{$ELSE}
function WlxGetStatusMessage; external msgina name 'WlxGetStatusMessage';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _WlxRemoveStatusMessage: Pointer;

function WlxRemoveStatusMessage;
begin
  GetProcedureAddress(_WlxRemoveStatusMessage, msgina, 'WlxRemoveStatusMessage');
  asm
    mov esp, ebp
    pop ebp
    jmp [_WlxRemoveStatusMessage]
  end;
end;
{$ELSE}
function WlxRemoveStatusMessage; external msgina name 'WlxRemoveStatusMessage';
{$ENDIF DYNAMIC_LINK}

{$ENDIF}

{$IFDEF MSGINA1_3}


{$IFDEF DYNAMIC_LINK}
var
  _WlxGetConsoleSwitchCredentials: Pointer;

function WlxGetConsoleSwitchCredentials;
begin
  GetProcedureAddress(_WlxGetConsoleSwitchCredentials, msgina, 'WlxGetConsoleSwitchCredentials');
  asm
    mov esp, ebp
    pop ebp
    jmp [_WlxGetConsoleSwitchCredentials]
  end;
end;
{$ELSE}
function WlxGetConsoleSwitchCredentials; external msgina name 'WlxGetConsoleSwitchCredentials';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _WlxReconnectNotify: Pointer;

procedure WlxReconnectNotify;
begin
  GetProcedureAddress(_WlxReconnectNotify, msgina, 'WlxReconnectNotify');
  asm
    mov esp, ebp
    pop ebp
    jmp [_WlxReconnectNotify]
  end;
end;
{$ELSE}
procedure WlxReconnectNotify; external msgina name 'WlxReconnectNotify';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _WlxDisconnectNotify: Pointer;

procedure WlxDisconnectNotify;
begin
  GetProcedureAddress(_WlxDisconnectNotify, msgina, 'WlxDisconnectNotify');
  asm
    mov esp, ebp
    pop ebp
    jmp [_WlxDisconnectNotify]
  end;
end;
{$ELSE}
procedure WlxDisconnectNotify; external msgina name 'WlxDisconnectNotify';
{$ENDIF DYNAMIC_LINK}

{$ENDIF}

{$ENDIF IMPORT_MS_GINA}

end.

