{******************************************************************************}
{                                                       	               }
{ Terminal Services API interface Unit for Object Pascal                       }
{                                                       	               }
{ Portions created by Microsoft are Copyright (C) 1995-2001 Microsoft          }
{ Corporation. All Rights Reserved.                                            }
{ 								               }
{ The original file is: wtsapi32.h, released June 2000. The original Pascal    }
{ code is: WtsApi32.pas, released December 2000. The initial developer of the  }
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

unit JwaWtsApi32;

interface

uses
  JwaWinNT, JwaWinType;

//   Windows Terminal Server public APIs
//
//   Copyright 1995-1999, Citrix Systems Inc.
//   Copyright (c) 1997-1999  Microsoft Corporation

//==============================================================================
// Defines
//==============================================================================

//
//  Specifies the current server
//

const
  WTS_CURRENT_SERVER        = HANDLE(0);
  {$EXTERNALSYM WTS_CURRENT_SERVER}
  WTS_CURRENT_SERVER_HANDLE = HANDLE(0);
  {$EXTERNALSYM WTS_CURRENT_SERVER_HANDLE}
  WTS_CURRENT_SERVER_NAME   = '';
  {$EXTERNALSYM WTS_CURRENT_SERVER_NAME}

//
//  Specifies the current session (SessionId)
//

  WTS_CURRENT_SESSION = DWORD(-1);
  {$EXTERNALSYM WTS_CURRENT_SESSION}

//
//  Possible pResponse values from WTSSendMessage()
//

  IDTIMEOUT = 32000;
  {$EXTERNALSYM IDTIMEOUT}
  IDASYNC   = 32001;
  {$EXTERNALSYM IDASYNC}

//
//  Shutdown flags
//

  WTS_WSD_LOGOFF = $00000001;           // log off all users except
  {$EXTERNALSYM WTS_WSD_LOGOFF}         // current user; deletes
                                        // WinStations (a reboot is
                                        // required to recreate the
                                        // WinStations)
  WTS_WSD_SHUTDOWN = $00000002;         // shutdown system
  {$EXTERNALSYM WTS_WSD_SHUTDOWN}
  WTS_WSD_REBOOT   = $00000004;         // shutdown and reboot
  {$EXTERNALSYM WTS_WSD_REBOOT}
  WTS_WSD_POWEROFF = $00000008;         // shutdown and power off (on
  {$EXTERNALSYM WTS_WSD_POWEROFF}
                                        // machines that support power
                                        // off through software)
  WTS_WSD_FASTREBOOT = $00000010;       // reboot without logging users
  {$EXTERNALSYM WTS_WSD_FASTREBOOT}     // off or shutting down

//==============================================================================
// WTS_CONNECTSTATE_CLASS - Session connect state
//==============================================================================

type
  _WTS_CONNECTSTATE_CLASS = (
    WTSActive,              // User logged on to WinStation
    WTSConnected,           // WinStation connected to client
    WTSConnectQuery,        // In the process of connecting to client
    WTSShadow,              // Shadowing another WinStation
    WTSDisconnected,        // WinStation logged on without client
    WTSIdle,                // Waiting for client to connect
    WTSListen,              // WinStation is listening for connection
    WTSReset,               // WinStation is being reset
    WTSDown,                // WinStation is down due to error
    WTSInit);               // WinStation in initialization
  {$EXTERNALSYM _WTS_CONNECTSTATE_CLASS}
  WTS_CONNECTSTATE_CLASS = _WTS_CONNECTSTATE_CLASS;
  {$EXTERNALSYM WTS_CONNECTSTATE_CLASS}
  TWtsConnectStateClass = WTS_CONNECTSTATE_CLASS;

//==============================================================================
// WTS_SERVER_INFO - returned by WTSEnumerateServers (version 1)
//==============================================================================

//
//  WTSEnumerateServers() returns two variables: pServerInfo and Count.
//  The latter is the number of WTS_SERVER_INFO structures contained in
//  the former.  In order to read each server, iterate i from 0 to
//  Count-1 and reference the server name as
//  pServerInfo[i].pServerName; for example:
//
//  for ( i=0; i < Count; i++ ) {
//      _tprintf( TEXT("%s "), pServerInfo[i].pServerName );
//  }
//
//  The memory returned looks like the following.  P is a pServerInfo
//  pointer, and D is the string data for that pServerInfo:
//
//  P1 P2 P3 P4 ... Pn D1 D2 D3 D4 ... Dn
//
//  This makes it easier to iterate the servers, using code similar to
//  the above.
//

type
  PWTS_SERVER_INFOW = ^WTS_SERVER_INFOW;
  {$EXTERNALSYM PWTS_SERVER_INFOW}
  _WTS_SERVER_INFOW = record
    pServerName: LPWSTR; // server name
  end;
  {$EXTERNALSYM _WTS_SERVER_INFOW}
  WTS_SERVER_INFOW = _WTS_SERVER_INFOW;
  {$EXTERNALSYM WTS_SERVER_INFOW}
  TWtsServerInfoW = WTS_SERVER_INFOW;
  PWtsServerInfoW = PWTS_SERVER_INFOW;

  PWTS_SERVER_INFOA = ^WTS_SERVER_INFOA;
  {$EXTERNALSYM PWTS_SERVER_INFOA}
  _WTS_SERVER_INFOA = record
    pServerName: LPSTR; // server name
  end;
  {$EXTERNALSYM _WTS_SERVER_INFOA}
  WTS_SERVER_INFOA = _WTS_SERVER_INFOA;
  {$EXTERNALSYM WTS_SERVER_INFOA}
  TWtsServerInfoA = WTS_SERVER_INFOA;
  PWtsServerInfoA = PWTS_SERVER_INFOA;

{$IFDEF UNICODE}
  WTS_SERVER_INFO = WTS_SERVER_INFOW;
  {$EXTERNALSYM WTS_SERVER_INFO}
  PWTS_SERVER_INFO = PWTS_SERVER_INFOW;
  {$EXTERNALSYM PWTS_SERVER_INFO}
  TWtsServerInfo = TWtsServerInfoW;
  PWtsServerInfo = PWtsServerInfoW;
{$ELSE}
  WTS_SERVER_INFO = WTS_SERVER_INFOA;
  {$EXTERNALSYM WTS_SERVER_INFO}
  PWTS_SERVER_INFO = PWTS_SERVER_INFOA;
  {$EXTERNALSYM PWTS_SERVER_INFO}
  TWtsServerInfo = TWtsServerInfoA;
  PWtsServerInfo = PWtsServerInfoA;
{$ENDIF}

//==============================================================================
// WTS_SESSION_INFO - returned by WTSEnumerateSessions (version 1)
//==============================================================================

//
//  WTSEnumerateSessions() returns data in a similar format to the above
//  WTSEnumerateServers().  It returns two variables: pSessionInfo and
//  Count.  The latter is the number of WTS_SESSION_INFO structures
//  contained in the former.  Iteration is similar, except that there
//  are three parts to each entry, so it would look like this:
//
//  for ( i=0; i < Count; i++ ) {
//      _tprintf( TEXT("%-5u  %-20s  %u\n"),
//                pSessionInfo[i].SessionId,
//                pSessionInfo[i].pWinStationName,
//                pSessionInfo[i].State );
//  }
//
//  The memory returned is also segmented as the above, with all the
//  structures allocated at the start and the string data at the end.
//  We'll use S for the SessionId, P for the pWinStationName pointer
//  and D for the string data, and C for the connect State:
//
//  S1 P1 C1 S2 P2 C2 S3 P3 C3 S4 P4 C4 ... Sn Pn Cn D1 D2 D3 D4 ... Dn
//
//  As above, this makes it easier to iterate the sessions.
//

type
  PWTS_SESSION_INFOW = ^WTS_SESSION_INFOW;
  {$EXTERNALSYM PWTS_SESSION_INFOW}
  _WTS_SESSION_INFOW = record
    SessionId: DWORD;              // session id
    pWinStationName: LPWSTR;       // name of WinStation this session is connected to
    State: WTS_CONNECTSTATE_CLASS; // connection state (see enum)
  end;
  {$EXTERNALSYM _WTS_SESSION_INFOW}
  WTS_SESSION_INFOW = _WTS_SESSION_INFOW;
  {$EXTERNALSYM WTS_SESSION_INFOW}
  TWtsSessionInfoW = WTS_SESSION_INFOW;
  PWtsSessionInfoW = PWTS_SESSION_INFOW;

  PWTS_SESSION_INFOA = ^WTS_SESSION_INFOA;
  {$EXTERNALSYM PWTS_SESSION_INFOA}
  _WTS_SESSION_INFOA = record
    SessionId: DWORD;              // session id
    pWinStationName: LPSTR;        // name of WinStation this session is connected to
    State: WTS_CONNECTSTATE_CLASS; // connection state (see enum)
  end;
  {$EXTERNALSYM _WTS_SESSION_INFOA}
  WTS_SESSION_INFOA = _WTS_SESSION_INFOA;
  {$EXTERNALSYM WTS_SESSION_INFOA}
  TWtsSessionInfoA = WTS_SESSION_INFOA;
  PWtsSessionInfoA = PWTS_SESSION_INFOA;

{$IFDEF UNICODE}
  WTS_SESSION_INFO = WTS_SESSION_INFOW;
  PWTS_SESSION_INFO = PWTS_SESSION_INFOW;
  TWtsSessionInfo = TWtsSessionInfoW;
  PWtsSessionInfo = PWtsSessionInfoW;
{$ELSE}
  WTS_SESSION_INFO = WTS_SESSION_INFOA;
  PWTS_SESSION_INFO = PWTS_SESSION_INFOA;
  TWtsSessionInfo = TWtsSessionInfoA;
  PWtsSessionInfo = PWtsSessionInfoA;
{$ENDIF}

//==============================================================================
// WTS_PROCESS_INFO - returned by WTSEnumerateProcesses (version 1)
//==============================================================================

//
//  WTSEnumerateProcesses() also returns data similar to
//  WTSEnumerateServers().  It returns two variables: pProcessInfo and
//  Count.  The latter is the number of WTS_PROCESS_INFO structures
//  contained in the former.  Iteration is similar, except that there
//  are four parts to each entry, so it would look like this:
//
//  for ( i=0; i < Count; i++ ) {
//      GetUserNameFromSid( pProcessInfo[i].pUserSid, UserName,
//                          sizeof(UserName) );
//      _tprintf( TEXT("%-5u  %-20s  %-5u  %s\n"),
//              pProcessInfo[i].SessionId,
//              UserName,
//              pProcessInfo[i].ProcessId,
//              pProcessInfo[i].pProcessName );
//  }
//
//  The memory returned is also segmented as the above, with all the
//  structures allocated at the start and the string data at the end.
//  We'll use S for the SessionId, R for the ProcessId, P for the
//  pProcessName pointer and D for the string data, and U for pUserSid:
//
//  S1 R1 P1 U1 S2 R2 P2 U2 S3 R3 P3 U3 ... Sn Rn Pn Un D1 D2 D3 ... Dn
//
//  As above, this makes it easier to iterate the processes.
//

type
  PWTS_PROCESS_INFOW = ^WTS_PROCESS_INFOW;
  {$EXTERNALSYM PWTS_PROCESS_INFOW}
  _WTS_PROCESS_INFOW = record
    SessionId: DWORD;     // session id
    ProcessId: DWORD;     // process id
    pProcessName: LPWSTR; // name of process
    pUserSid: PSID;       // user's SID
  end;
  {$EXTERNALSYM _WTS_PROCESS_INFOW}
  WTS_PROCESS_INFOW = _WTS_PROCESS_INFOW;
  {$EXTERNALSYM WTS_PROCESS_INFOW}
  TWtsProcessInfoW = WTS_PROCESS_INFOW;
  PWtsProcessInfoW = PWTS_PROCESS_INFOW;

  PWTS_PROCESS_INFOA = ^WTS_PROCESS_INFOA;
  {$EXTERNALSYM PWTS_PROCESS_INFOA}
  _WTS_PROCESS_INFOA = record
    SessionId: DWORD;    // session id
    ProcessId: DWORD;    // process id
    pProcessName: LPSTR; // name of process
    pUserSid: PSID;      // user's SID
  end;
  {$EXTERNALSYM _WTS_PROCESS_INFOA}
  WTS_PROCESS_INFOA = _WTS_PROCESS_INFOA;
  {$EXTERNALSYM WTS_PROCESS_INFOA}
  TWtsProcessInfoA = WTS_PROCESS_INFOA;
  PWtsProcessInfoA = PWTS_PROCESS_INFOA;

{$IFDEF UNICODE}
  WTS_PROCESS_INFO = WTS_PROCESS_INFOW;
  {$EXTERNALSYM WTS_PROCESS_INFO}
  PWTS_PROCESS_INFO = PWTS_PROCESS_INFOW;
  {$EXTERNALSYM PWTS_PROCESS_INFO}
  TWtsProcessInfo = TWtsProcessInfoW;
  PWtsProcessInfo = PWtsProcessInfoW;
{$ELSE}
  WTS_PROCESS_INFO = WTS_PROCESS_INFOA;
  {$EXTERNALSYM WTS_PROCESS_INFO}
  PWTS_PROCESS_INFO = PWTS_PROCESS_INFOA;
  {$EXTERNALSYM PWTS_PROCESS_INFO}
  TWtsProcessInfo = TWtsProcessInfoA;
  PWtsProcessInfo = PWtsProcessInfoA;
{$ENDIF}

//==============================================================================
// WTS_INFO_CLASS - WTSQuerySessionInformation
// (See additional typedefs for more info on structures)
//==============================================================================

const
  WTS_PROTOCOL_TYPE_CONSOLE = 0; // Console
  {$EXTERNALSYM WTS_PROTOCOL_TYPE_CONSOLE}
  WTS_PROTOCOL_TYPE_ICA     = 1; // ICA Protocol
  {$EXTERNALSYM WTS_PROTOCOL_TYPE_ICA}
  WTS_PROTOCOL_TYPE_RDP     = 2; // RDP Protocol
  {$EXTERNALSYM WTS_PROTOCOL_TYPE_RDP}

type
  _WTS_INFO_CLASS = (
    WTSInitialProgram,
    WTSApplicationName,
    WTSWorkingDirectory,
    WTSOEMId,
    WTSSessionId,
    WTSUserName,
    WTSWinStationName,
    WTSDomainName,
    WTSConnectState,
    WTSClientBuildNumber,
    WTSClientName,
    WTSClientDirectory,
    WTSClientProductId,
    WTSClientHardwareId,
    WTSClientAddress,
    WTSClientDisplay,
    WTSClientProtocolType);
  {$EXTERNALSYM _WTS_INFO_CLASS}
  WTS_INFO_CLASS = _WTS_INFO_CLASS;
  TWtsInfoClass = WTS_INFO_CLASS;

//==============================================================================
// WTSQuerySessionInformation - (WTSClientAddress)
//==============================================================================

type
  PWTS_CLIENT_ADDRESS = ^WTS_CLIENT_ADDRESS;
  {$EXTERNALSYM PWTS_CLIENT_ADDRESS}
  _WTS_CLIENT_ADDRESS = record
    AddressFamily: DWORD;           // AF_INET, AF_IPX, AF_NETBIOS, AF_UNSPEC
    Address: array [0..19] of BYTE; // client network address
  end;
  {$EXTERNALSYM _WTS_CLIENT_ADDRESS}
  WTS_CLIENT_ADDRESS = _WTS_CLIENT_ADDRESS;
  {$EXTERNALSYM WTS_CLIENT_ADDRESS}
  TWtsClientAddress = WTS_CLIENT_ADDRESS;
  PWtsClientAddress = PWTS_CLIENT_ADDRESS;

//==============================================================================
// WTSQuerySessionInformation - (WTSClientDisplay)
//==============================================================================

type
  PWTS_CLIENT_DISPLAY = ^WTS_CLIENT_DISPLAY;
  {$EXTERNALSYM PWTS_CLIENT_DISPLAY}
  _WTS_CLIENT_DISPLAY = record
    HorizontalResolution: DWORD; // horizontal dimensions, in pixels
    VerticalResolution: DWORD;   // vertical dimensions, in pixels
    ColorDepth: DWORD;           // 1=16, 2=256, 4=64K, 8=16M
  end;
  {$EXTERNALSYM _WTS_CLIENT_DISPLAY}
  WTS_CLIENT_DISPLAY = _WTS_CLIENT_DISPLAY;
  {$EXTERNALSYM WTS_CLIENT_DISPLAY}
  TWtsClientDisplay = WTS_CLIENT_DISPLAY;
  PWtsClientDisplay = PWTS_CLIENT_DISPLAY;

//==============================================================================
// WTS_CONFIG_CLASS - WTSQueryUserConfig/WTSSetUserConfig
//==============================================================================

type
  _WTS_CONFIG_CLASS = (
    //Initial program settings
    WTSUserConfigInitialProgram,         	// string returned/expected
    WTSUserConfigWorkingDirectory,       	// string returned/expected
    WTSUserConfigfInheritInitialProgram, 	// DWORD returned/expected
    //
    WTSUserConfigfAllowLogonTerminalServer, 	//DWORD returned/expected
    //Timeout settings
    WTSUserConfigTimeoutSettingsConnections, 	//DWORD returned/expected
    WTSUserConfigTimeoutSettingsDisconnections, //DWORD returned/expected
    WTSUserConfigTimeoutSettingsIdle, 	        //DWORD returned/expected
    //Client device settings
    WTSUserConfigfDeviceClientDrives,  		//DWORD returned/expected
    WTSUserConfigfDeviceClientPrinters,         //DWORD returned/expected
    WTSUserConfigfDeviceClientDefaultPrinter,   //DWORD returned/expected
    //Connection settings
    WTSUserConfigBrokenTimeoutSettings,         //DWORD returned/expected
    WTSUserConfigReconnectSettings,             //DWORD returned/expected
    //Modem settings
    WTSUserConfigModemCallbackSettings,         //DWORD returned/expected
    WTSUserConfigModemCallbackPhoneNumber,      // string returned/expected
    //Shadow settings
    WTSUserConfigShadowingSettings,             //DWORD returned/expected
    //User Profile settings
    WTSUserConfigTerminalServerProfilePath,     // string returned/expected
    //Terminal Server home directory
    WTSUserConfigTerminalServerHomeDir,         // string returned/expected
    WTSUserConfigTerminalServerHomeDirDrive,    // string returned/expected
    WTSUserConfigfTerminalServerRemoteHomeDir); // DWORD 0:LOCAL 1:REMOTE
  {$EXTERNALSYM _WTS_CONFIG_CLASS}
  WTS_CONFIG_CLASS = _WTS_CONFIG_CLASS;
  TWtsConfigClass = WTS_CONFIG_CLASS;

{$IFDEF FALSE}

// There we're remove in June 2001 PSDK (pre-release)

  PWTS_USER_CONFIG_SET_NWSERVERW = ^WTS_USER_CONFIG_SET_NWSERVERW;
  {$EXTERNALSYM PWTS_USER_CONFIG_SET_NWSERVERW}
  _WTS_USER_CONFIG_SET_NWSERVERW = record
    pNWServerName: LPWSTR;
    pNWDomainAdminName: LPWSTR;
    pNWDomainAdminPassword: LPWSTR;
  end;
  {$EXTERNALSYM _WTS_USER_CONFIG_SET_NWSERVERW}
  WTS_USER_CONFIG_SET_NWSERVERW = _WTS_USER_CONFIG_SET_NWSERVERW;
  {$EXTERNALSYM WTS_USER_CONFIG_SET_NWSERVERW}
  TWtsUserConfigSetNwserverW = WTS_USER_CONFIG_SET_NWSERVERW;
  PWtsUserConfigSetNwserverW = PWTS_USER_CONFIG_SET_NWSERVERW;

  PWTS_USER_CONFIG_SET_NWSERVERA = ^WTS_USER_CONFIG_SET_NWSERVERA;
  {$EXTERNALSYM PWTS_USER_CONFIG_SET_NWSERVERA}
  _WTS_USER_CONFIG_SET_NWSERVERA = record
    pNWServerName: LPSTR;
    pNWDomainAdminName: LPSTR;
    pNWDomainAdminPassword: LPSTR;
  end;
  {$EXTERNALSYM _WTS_USER_CONFIG_SET_NWSERVERA}
  WTS_USER_CONFIG_SET_NWSERVERA = _WTS_USER_CONFIG_SET_NWSERVERA;
  {$EXTERNALSYM WTS_USER_CONFIG_SET_NWSERVERA}
  TWtsUserConfigSetNwserverA = WTS_USER_CONFIG_SET_NWSERVERA;
  PWtsUserConfigSetNwserverA = PWTS_USER_CONFIG_SET_NWSERVERA;

{$IFDEF UNICODE}
  WTS_USER_CONFIG_SET_NWSERVER  = WTS_USER_CONFIG_SET_NWSERVERW;
  {$EXTERNALSYM WTS_USER_CONFIG_SET_NWSERVER}
  PWTS_USER_CONFIG_SET_NWSERVER = PWTS_USER_CONFIG_SET_NWSERVERW;
  {$EXTERNALSYM PWTS_USER_CONFIG_SET_NWSERVER}
  TWtsUserConfigSetNwserver = TWtsUserConfigSetNwserverW;
  PWtsUserConfigSetNwserver = PWtsUserConfigSetNwserverW;
{$ELSE}
  WTS_USER_CONFIG_SET_NWSERVER  = WTS_USER_CONFIG_SET_NWSERVERA;
  {$EXTERNALSYM WTS_USER_CONFIG_SET_NWSERVER}
  PWTS_USER_CONFIG_SET_NWSERVER = PWTS_USER_CONFIG_SET_NWSERVERA;
  {$EXTERNALSYM PWTS_USER_CONFIG_SET_NWSERVER}
  TWtsUserConfigSetNwserver = TWtsUserConfigSetNwserverA;
  PWtsUserConfigSetNwserver = PWtsUserConfigSetNwserverA;
{$ENDIF}
{$ENDIF}

//==============================================================================
// WTS_EVENT - Event flags for WTSWaitSystemEvent
//==============================================================================

const
  WTS_EVENT_NONE        = $00000000; // return no event
  {$EXTERNALSYM WTS_EVENT_NONE}
  WTS_EVENT_CREATE      = $00000001; // new WinStation created
  {$EXTERNALSYM WTS_EVENT_CREATE}
  WTS_EVENT_DELETE      = $00000002; // existing WinStation deleted
  {$EXTERNALSYM WTS_EVENT_DELETE}
  WTS_EVENT_RENAME      = $00000004; // existing WinStation renamed
  {$EXTERNALSYM WTS_EVENT_RENAME}
  WTS_EVENT_CONNECT     = $00000008; // WinStation connect to client
  {$EXTERNALSYM WTS_EVENT_CONNECT}
  WTS_EVENT_DISCONNECT  = $00000010; // WinStation logged on without client
  {$EXTERNALSYM WTS_EVENT_DISCONNECT}
  WTS_EVENT_LOGON       = $00000020; // user logged on to existing WinStation
  {$EXTERNALSYM WTS_EVENT_LOGON}
  WTS_EVENT_LOGOFF      = $00000040; // user logged off from existing WinStation
  {$EXTERNALSYM WTS_EVENT_LOGOFF}
  WTS_EVENT_STATECHANGE = $00000080; // WinStation state change
  {$EXTERNALSYM WTS_EVENT_STATECHANGE}
  WTS_EVENT_LICENSE     = $00000100; // license state change
  {$EXTERNALSYM WTS_EVENT_LICENSE}
  WTS_EVENT_ALL         = $7fffffff; // wait for all event types
  {$EXTERNALSYM WTS_EVENT_ALL}
  WTS_EVENT_FLUSH       = DWORD($80000000); // unblock all waiters
  {$EXTERNALSYM WTS_EVENT_FLUSH}

//==============================================================================
// WTS_VIRTUAL_CLASS - WTSVirtualChannelQuery
//==============================================================================

type
  _WTS_VIRTUAL_CLASS = (WTSVirtualClientData, WTSVirtualFileHandle);  
  {$EXTERNALSYM _WTS_VIRTUAL_CLASS}
  WTS_VIRTUAL_CLASS = _WTS_VIRTUAL_CLASS;
  {$EXTERNALSYM WTS_VIRTUAL_CLASS}
  TWtsVirtualClass = WTS_VIRTUAL_CLASS;

//==============================================================================
// Windows Terminal Server public APIs
//==============================================================================

function WTSEnumerateServersA(pDomainName: LPSTR; Reserved, Version: DWORD;
  var ppServerInfo: PWTS_SERVER_INFOA; var pCount: DWORD): BOOL; stdcall;
{$EXTERNALSYM WTSEnumerateServersA}
function WTSEnumerateServersW(pDomainName: LPWSTR; Reserved, Version: DWORD;
  var ppServerInfo: PWTS_SERVER_INFOW; var pCount: DWORD): BOOL; stdcall;
{$EXTERNALSYM WTSEnumerateServersW}

{$IFDEF UNICODE}
function WTSEnumerateServers(pDomainName: LPWSTR; Reserved, Version: DWORD;
  var ppServerInfo: PWTS_SERVER_INFOW; var pCount: DWORD): BOOL; stdcall;
{$EXTERNALSYM WTSEnumerateServers}
{$ELSE}
function WTSEnumerateServers(pDomainName: LPSTR; Reserved, Version: DWORD;
  var ppServerInfo: PWTS_SERVER_INFOA; var pCount: DWORD): BOOL; stdcall;
{$EXTERNALSYM WTSEnumerateServers}
{$ENDIF}

//------------------------------------------------------------------------------

function WTSOpenServerA(pServerName: LPSTR): HANDLE; stdcall;
{$EXTERNALSYM WTSOpenServerA}
function WTSOpenServerW(pServerName: LPWSTR): HANDLE; stdcall;
{$EXTERNALSYM WTSOpenServerW}

{$IFDEF UNICODE}
function WTSOpenServer(pServerName: LPWSTR): HANDLE; stdcall;
{$EXTERNALSYM WTSOpenServer}
{$ELSE}
function WTSOpenServer(pServerName: LPSTR): HANDLE; stdcall;
{$EXTERNALSYM WTSOpenServer}
{$ENDIF}

//------------------------------------------------------------------------------

procedure WTSCloseServer(hServer: HANDLE); stdcall;
{$EXTERNALSYM WTSCloseServer}

//------------------------------------------------------------------------------

function WTSEnumerateSessionsA(hServer: HANDLE; Reserved: DWORD; Version: DWORD;
  var ppSessionInfo: PWTS_SESSION_INFOA; var pCount: DWORD): BOOL; stdcall;
{$EXTERNALSYM WTSEnumerateSessionsA}
function WTSEnumerateSessionsW(hServer: HANDLE; Reserved: DWORD; Version: DWORD;
  var ppSessionInfo: PWTS_SESSION_INFOW; var pCount: DWORD): BOOL; stdcall;
{$EXTERNALSYM WTSEnumerateSessionsW}

{$IFDEF UNICODE}
function WTSEnumerateSessions(hServer: HANDLE; Reserved: DWORD; Version: DWORD;
  var ppSessionInfo: PWTS_SESSION_INFOW; var pCount: DWORD): BOOL; stdcall;
{$EXTERNALSYM WTSEnumerateSessions}
{$ELSE}
function WTSEnumerateSessions(hServer: HANDLE; Reserved: DWORD; Version: DWORD;
  var ppSessionInfo: PWTS_SESSION_INFOA; var pCount: DWORD): BOOL; stdcall;
{$EXTERNALSYM WTSEnumerateSessions}
{$ENDIF}

//------------------------------------------------------------------------------

function WTSEnumerateProcessesA(hServer: HANDLE; Reserved: DWORD; Version: DWORD;
  var ppProcessInfo: PWTS_PROCESS_INFOA; var pCount: DWORD): BOOL; stdcall;
{$EXTERNALSYM WTSEnumerateProcessesA}
function WTSEnumerateProcessesW(hServer: HANDLE; Reserved: DWORD; Version: DWORD;
  var ppProcessInfo: PWTS_PROCESS_INFOW; var pCount: DWORD): BOOL; stdcall;
{$EXTERNALSYM WTSEnumerateProcessesW}

{$IFDEF UNICODE}
function WTSEnumerateProcesses(hServer: HANDLE; Reserved: DWORD; Version: DWORD;
  var ppProcessInfo: PWTS_PROCESS_INFOW; var pCount: DWORD): BOOL; stdcall;
{$EXTERNALSYM WTSEnumerateProcesses}
{$ELSE}
function WTSEnumerateProcesses(hServer: HANDLE; Reserved: DWORD; Version: DWORD;
  var ppProcessInfo: PWTS_PROCESS_INFOA; var pCount: DWORD): BOOL; stdcall;
{$EXTERNALSYM WTSEnumerateProcesses}
{$ENDIF}

//------------------------------------------------------------------------------

function WTSTerminateProcess(hServer: HANDLE; ProcessId, ExitCode: DWORD): BOOL; stdcall;
{$EXTERNALSYM WTSTerminateProcess}

//------------------------------------------------------------------------------

function WTSQuerySessionInformationA(hServer: HANDLE; SessionId: DWORD;
  WTSInfoClass: WTS_INFO_CLASS; var ppBuffer: Pointer; var pBytesReturned: DWORD): BOOL; stdcall;
{$EXTERNALSYM WTSQuerySessionInformationA}
function WTSQuerySessionInformationW(hServer: HANDLE; SessionId: DWORD;
  WTSInfoClass: WTS_INFO_CLASS; var ppBuffer: Pointer; var pBytesReturned: DWORD): BOOL; stdcall;
{$EXTERNALSYM WTSQuerySessionInformationW}

{$IFDEF UNICODE}
function WTSQuerySessionInformation(hServer: HANDLE; SessionId: DWORD;
  WTSInfoClass: WTS_INFO_CLASS; var ppBuffer: Pointer; var pBytesReturned: DWORD): BOOL; stdcall;
{$EXTERNALSYM WTSQuerySessionInformation}
{$ELSE}
function WTSQuerySessionInformation(hServer: HANDLE; SessionId: DWORD;
  WTSInfoClass: WTS_INFO_CLASS; var ppBuffer: Pointer; var pBytesReturned: DWORD): BOOL; stdcall;
{$EXTERNALSYM WTSQuerySessionInformation}
{$ENDIF}

//------------------------------------------------------------------------------

function WTSQueryUserConfigA(pServerName, pUserName: LPSTR; WTSConfigClass: WTS_CONFIG_CLASS;
  var ppBuffer: Pointer; var pBytesReturned: DWORD): BOOL; stdcall;
{$EXTERNALSYM WTSQueryUserConfigA}
function WTSQueryUserConfigW(pServerName, pUserName: LPWSTR; WTSConfigClass: WTS_CONFIG_CLASS;
  var ppBuffer: Pointer; var pBytesReturned: DWORD): BOOL; stdcall;
{$EXTERNALSYM WTSQueryUserConfigW}

{$IFDEF UNICODE}
function WTSQueryUserConfig(pServerName, pUserName: LPWSTR; WTSConfigClass: WTS_CONFIG_CLASS;
  var ppBuffer: Pointer; var pBytesReturned: DWORD): BOOL; stdcall;
{$EXTERNALSYM WTSQueryUserConfig}
{$ELSE}
function WTSQueryUserConfig(pServerName, pUserName: LPSTR; WTSConfigClass: WTS_CONFIG_CLASS;
  var ppBuffer: Pointer; var pBytesReturned: DWORD): BOOL; stdcall;
{$EXTERNALSYM WTSQueryUserConfig}
{$ENDIF}

//------------------------------------------------------------------------------

function WTSSetUserConfigA(pServerName, pUserName: LPSTR; WTSConfigClass: WTS_CONFIG_CLASS;
  pBuffer: LPSTR; DataLength: DWORD): BOOL; stdcall;
{$EXTERNALSYM WTSSetUserConfigA}
function WTSSetUserConfigW(pServerName, pUserName: LPWSTR; WTSConfigClass: WTS_CONFIG_CLASS;
  pBuffer: LPWSTR; DataLength: DWORD): BOOL; stdcall;
{$EXTERNALSYM WTSSetUserConfigW}

{$IFDEF UNICODE}
function WTSSetUserConfig(pServerName, pUserName: LPWSTR; WTSConfigClass: WTS_CONFIG_CLASS;
  pBuffer: LPWSTR; DataLength: DWORD): BOOL; stdcall;
{$EXTERNALSYM WTSSetUserConfig}
{$ELSE}
function WTSSetUserConfig(pServerName, pUserName: LPSTR; WTSConfigClass: WTS_CONFIG_CLASS;
  pBuffer: LPSTR; DataLength: DWORD): BOOL; stdcall;
{$EXTERNALSYM WTSSetUserConfig}
{$ENDIF}

//------------------------------------------------------------------------------

function WTSSendMessageA(hServer: HANDLE; SessionId: DWORD; pTitle: LPSTR;
  TitleLength: DWORD; pMessage: LPSTR; MessageLength: DWORD; Style: DWORD;
  Timeout: DWORD; var pResponse: DWORD; bWait: BOOL): BOOL; stdcall;
{$EXTERNALSYM WTSSendMessageA}
function WTSSendMessageW(hServer: HANDLE; SessionId: DWORD; pTitle: LPWSTR;
  TitleLength: DWORD; pMessage: LPWSTR; MessageLength: DWORD; Style: DWORD;
  Timeout: DWORD; var pResponse: DWORD; bWait: BOOL): BOOL; stdcall;
{$EXTERNALSYM WTSSendMessageW}

{$IFDEF UNICODE}
function WTSSendMessage(hServer: HANDLE; SessionId: DWORD; pTitle: LPWSTR;
  TitleLength: DWORD; pMessage: LPWSTR; MessageLength: DWORD; Style: DWORD;
  Timeout: DWORD; var pResponse: DWORD; bWait: BOOL): BOOL; stdcall;
{$EXTERNALSYM WTSSendMessage}
{$ELSE}
function WTSSendMessage(hServer: HANDLE; SessionId: DWORD; pTitle: LPSTR;
  TitleLength: DWORD; pMessage: LPSTR; MessageLength: DWORD; Style: DWORD;
  Timeout: DWORD; var pResponse: DWORD; bWait: BOOL): BOOL; stdcall;
{$EXTERNALSYM WTSSendMessage}
{$ENDIF}

//------------------------------------------------------------------------------

function WTSDisconnectSession(hServer: HANDLE; SessionId: DWORD; bWait: BOOL): BOOL; stdcall;
{$EXTERNALSYM WTSDisconnectSession}

//------------------------------------------------------------------------------

function WTSLogoffSession(hServer: HANDLE; SessionId: DWORD; bWait: BOOL): BOOL; stdcall;
{$EXTERNALSYM WTSLogoffSession}

//------------------------------------------------------------------------------

function WTSShutdownSystem(hServer: HANDLE; ShutdownFlag: DWORD): BOOL; stdcall;
{$EXTERNALSYM WTSShutdownSystem}

//------------------------------------------------------------------------------

function WTSWaitSystemEvent(hServer: HANDLE; EventMask: DWORD;
  var pEventFlags: DWORD): BOOL; stdcall;
{$EXTERNALSYM WTSWaitSystemEvent}

//------------------------------------------------------------------------------

function WTSVirtualChannelOpen(hServer: HANDLE; SessionId: DWORD;
  pVirtualName: LPSTR): HANDLE; stdcall;
{$EXTERNALSYM WTSVirtualChannelOpen}

function WTSVirtualChannelClose(hChannelHandle: HANDLE): BOOL; stdcall;
{$EXTERNALSYM WTSVirtualChannelClose}

function WTSVirtualChannelRead(hChannelHandle: HANDLE; TimeOut: ULONG;
  Buffer: PCHAR; BufferSize: ULONG; var pBytesRead: ULONG): BOOL; stdcall;
{$EXTERNALSYM WTSVirtualChannelRead}

function WTSVirtualChannelWrite(hChannelHandle: HANDLE; Buffer: PCHAR;
  Length: ULONG; var pBytesWritten: ULONG): BOOL; stdcall;
{$EXTERNALSYM WTSVirtualChannelWrite}

function WTSVirtualChannelPurgeInput(hChannelHandle: HANDLE): BOOL; stdcall;
{$EXTERNALSYM WTSVirtualChannelPurgeInput}

function WTSVirtualChannelPurgeOutput(hChannelHandle: HANDLE): BOOL; stdcall;
{$EXTERNALSYM WTSVirtualChannelPurgeOutput}

function WTSVirtualChannelQuery(hChannelHandle: HANDLE; VirtualClass: WTS_VIRTUAL_CLASS;
  ppBuffer: PVOID; var pBytesReturned: DWORD): BOOL; stdcall;
{$EXTERNALSYM WTSVirtualChannelQuery}

//------------------------------------------------------------------------------

procedure WTSFreeMemory(pMemory: PVOID); stdcall;
{$EXTERNALSYM WTSFreeMemory}

// Flags for Console Notification

const
  NOTIFY_FOR_ALL_SESSIONS = 1;
  {$EXTERNALSYM NOTIFY_FOR_ALL_SESSIONS}
  NOTIFY_FOR_THIS_SESSION = 0;
  {$EXTERNALSYM NOTIFY_FOR_THIS_SESSION}

function WTSRegisterSessionNotification(hWnd: HWND; dwFlags: DWORD): BOOL; stdcall;
{$EXTERNALSYM WTSRegisterSessionNotification}

function WTSUnRegisterSessionNotification(hWnd: HWND): BOOL; stdcall;
{$EXTERNALSYM WTSUnRegisterSessionNotification}

function WTSQueryUserToken(SessionId: ULONG; var phToken: HANDLE): BOOL; stdcall;
{$EXTERNALSYM WTSQueryUserToken}

implementation

const
  wtsapi = 'wtsapi32.dll';


{$IFDEF DYNAMIC_LINK}
var
  _WTSEnumerateServersA: Pointer;

function WTSEnumerateServersA;
begin
  GetProcedureAddress(_WTSEnumerateServersA, wtsapi, 'WTSEnumerateServersA');
  asm
    mov esp, ebp
    pop ebp
    jmp [_WTSEnumerateServersA]
  end;
end;
{$ELSE}
function WTSEnumerateServersA; external wtsapi name 'WTSEnumerateServersA';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _WTSEnumerateServersW: Pointer;

function WTSEnumerateServersW;
begin
  GetProcedureAddress(_WTSEnumerateServersW, wtsapi, 'WTSEnumerateServersW');
  asm
    mov esp, ebp
    pop ebp
    jmp [_WTSEnumerateServersW]
  end;
end;
{$ELSE}
function WTSEnumerateServersW; external wtsapi name 'WTSEnumerateServersW';
{$ENDIF DYNAMIC_LINK}
{$IFDEF UNICODE}

{$IFDEF DYNAMIC_LINK}
var
  _WTSEnumerateServers: Pointer;

function WTSEnumerateServers;
begin
  GetProcedureAddress(_WTSEnumerateServers, wtsapi, 'WTSEnumerateServersW');
  asm
    mov esp, ebp
    pop ebp
    jmp [_WTSEnumerateServers]
  end;
end;
{$ELSE}
function WTSEnumerateServers; external wtsapi name 'WTSEnumerateServersW';
{$ENDIF DYNAMIC_LINK}
{$ELSE}

{$IFDEF DYNAMIC_LINK}
var
  _WTSEnumerateServers: Pointer;

function WTSEnumerateServers;
begin
  GetProcedureAddress(_WTSEnumerateServers, wtsapi, 'WTSEnumerateServersA');
  asm
    mov esp, ebp
    pop ebp
    jmp [_WTSEnumerateServers]
  end;
end;
{$ELSE}
function WTSEnumerateServers; external wtsapi name 'WTSEnumerateServersA';
{$ENDIF DYNAMIC_LINK}
{$ENDIF}

{$IFDEF DYNAMIC_LINK}
var
  _WTSOpenServerA: Pointer;

function WTSOpenServerA;
begin
  GetProcedureAddress(_WTSOpenServerA, wtsapi, 'WTSOpenServerA');
  asm
    mov esp, ebp
    pop ebp
    jmp [_WTSOpenServerA]
  end;
end;
{$ELSE}
function WTSOpenServerA; external wtsapi name 'WTSOpenServerA';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _WTSOpenServerW: Pointer;

function WTSOpenServerW;
begin
  GetProcedureAddress(_WTSOpenServerW, wtsapi, 'WTSOpenServerW');
  asm
    mov esp, ebp
    pop ebp
    jmp [_WTSOpenServerW]
  end;
end;
{$ELSE}
function WTSOpenServerW; external wtsapi name 'WTSOpenServerW';
{$ENDIF DYNAMIC_LINK}
{$IFDEF UNICODE}

{$IFDEF DYNAMIC_LINK}
var
  _WTSOpenServer: Pointer;

function WTSOpenServer;
begin
  GetProcedureAddress(_WTSOpenServer, wtsapi, 'WTSOpenServerW');
  asm
    mov esp, ebp
    pop ebp
    jmp [_WTSOpenServer]
  end;
end;
{$ELSE}
function WTSOpenServer; external wtsapi name 'WTSOpenServerW';
{$ENDIF DYNAMIC_LINK}
{$ELSE}

{$IFDEF DYNAMIC_LINK}
var
  _WTSOpenServer: Pointer;

function WTSOpenServer;
begin
  GetProcedureAddress(_WTSOpenServer, wtsapi, 'WTSOpenServerA');
  asm
    mov esp, ebp
    pop ebp
    jmp [_WTSOpenServer]
  end;
end;
{$ELSE}
function WTSOpenServer; external wtsapi name 'WTSOpenServerA';
{$ENDIF DYNAMIC_LINK}
{$ENDIF}

{$IFDEF DYNAMIC_LINK}
var
  _WTSCloseServer: Pointer;

procedure WTSCloseServer;
begin
  GetProcedureAddress(_WTSCloseServer, wtsapi, 'WTSCloseServer');
  asm
    mov esp, ebp
    pop ebp
    jmp [_WTSCloseServer]
  end;
end;
{$ELSE}
procedure WTSCloseServer; external wtsapi name 'WTSCloseServer';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _WTSEnumerateSessionsA: Pointer;

function WTSEnumerateSessionsA;
begin
  GetProcedureAddress(_WTSEnumerateSessionsA, wtsapi, 'WTSEnumerateSessionsA');
  asm
    mov esp, ebp
    pop ebp
    jmp [_WTSEnumerateSessionsA]
  end;
end;
{$ELSE}
function WTSEnumerateSessionsA; external wtsapi name 'WTSEnumerateSessionsA';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _WTSEnumerateSessionsW: Pointer;

function WTSEnumerateSessionsW;
begin
  GetProcedureAddress(_WTSEnumerateSessionsW, wtsapi, 'WTSEnumerateSessionsW');
  asm
    mov esp, ebp
    pop ebp
    jmp [_WTSEnumerateSessionsW]
  end;
end;
{$ELSE}
function WTSEnumerateSessionsW; external wtsapi name 'WTSEnumerateSessionsW';
{$ENDIF DYNAMIC_LINK}
{$IFDEF UNICODE}

{$IFDEF DYNAMIC_LINK}
var
  _WTSEnumerateSessions: Pointer;

function WTSEnumerateSessions;
begin
  GetProcedureAddress(_WTSEnumerateSessions, wtsapi, 'WTSEnumerateSessionsW');
  asm
    mov esp, ebp
    pop ebp
    jmp [_WTSEnumerateSessions]
  end;
end;
{$ELSE}
function WTSEnumerateSessions; external wtsapi name 'WTSEnumerateSessionsW';
{$ENDIF DYNAMIC_LINK}
{$ELSE}

{$IFDEF DYNAMIC_LINK}
var
  _WTSEnumerateSessions: Pointer;

function WTSEnumerateSessions;
begin
  GetProcedureAddress(_WTSEnumerateSessions, wtsapi, 'WTSEnumerateSessionsA');
  asm
    mov esp, ebp
    pop ebp
    jmp [_WTSEnumerateSessions]
  end;
end;
{$ELSE}
function WTSEnumerateSessions; external wtsapi name 'WTSEnumerateSessionsA';
{$ENDIF DYNAMIC_LINK}
{$ENDIF}

{$IFDEF DYNAMIC_LINK}
var
  _WTSEnumerateProcessesA: Pointer;

function WTSEnumerateProcessesA;
begin
  GetProcedureAddress(_WTSEnumerateProcessesA, wtsapi, 'WTSEnumerateProcessesA');
  asm
    mov esp, ebp
    pop ebp
    jmp [_WTSEnumerateProcessesA]
  end;
end;
{$ELSE}
function WTSEnumerateProcessesA; external wtsapi name 'WTSEnumerateProcessesA';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _WTSEnumerateProcessesW: Pointer;

function WTSEnumerateProcessesW;
begin
  GetProcedureAddress(_WTSEnumerateProcessesW, wtsapi, 'WTSEnumerateProcessesW');
  asm
    mov esp, ebp
    pop ebp
    jmp [_WTSEnumerateProcessesW]
  end;
end;
{$ELSE}
function WTSEnumerateProcessesW; external wtsapi name 'WTSEnumerateProcessesW';
{$ENDIF DYNAMIC_LINK}
{$IFDEF UNICODE}

{$IFDEF DYNAMIC_LINK}
var
  _WTSEnumerateProcesses: Pointer;

function WTSEnumerateProcesses;
begin
  GetProcedureAddress(_WTSEnumerateProcesses, wtsapi, 'WTSEnumerateProcessesW');
  asm
    mov esp, ebp
    pop ebp
    jmp [_WTSEnumerateProcesses]
  end;
end;
{$ELSE}
function WTSEnumerateProcesses; external wtsapi name 'WTSEnumerateProcessesW';
{$ENDIF DYNAMIC_LINK}
{$ELSE}

{$IFDEF DYNAMIC_LINK}
var
  _WTSEnumerateProcesses: Pointer;

function WTSEnumerateProcesses;
begin
  GetProcedureAddress(_WTSEnumerateProcesses, wtsapi, 'WTSEnumerateProcessesA');
  asm
    mov esp, ebp
    pop ebp
    jmp [_WTSEnumerateProcesses]
  end;
end;
{$ELSE}
function WTSEnumerateProcesses; external wtsapi name 'WTSEnumerateProcessesA';
{$ENDIF DYNAMIC_LINK}
{$ENDIF}

{$IFDEF DYNAMIC_LINK}
var
  _WTSTerminateProcess: Pointer;

function WTSTerminateProcess;
begin
  GetProcedureAddress(_WTSTerminateProcess, wtsapi, 'WTSTerminateProcess');
  asm
    mov esp, ebp
    pop ebp
    jmp [_WTSTerminateProcess]
  end;
end;
{$ELSE}
function WTSTerminateProcess; external wtsapi name 'WTSTerminateProcess';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _WTSQuerySessionInformationA: Pointer;

function WTSQuerySessionInformationA;
begin
  GetProcedureAddress(_WTSQuerySessionInformationA, wtsapi, 'WTSQuerySessionInformationA');
  asm
    mov esp, ebp
    pop ebp
    jmp [_WTSQuerySessionInformationA]
  end;
end;
{$ELSE}
function WTSQuerySessionInformationA; external wtsapi name 'WTSQuerySessionInformationA';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _WTSQuerySessionInformationW: Pointer;

function WTSQuerySessionInformationW;
begin
  GetProcedureAddress(_WTSQuerySessionInformationW, wtsapi, 'WTSQuerySessionInformationW');
  asm
    mov esp, ebp
    pop ebp
    jmp [_WTSQuerySessionInformationW]
  end;
end;
{$ELSE}
function WTSQuerySessionInformationW; external wtsapi name 'WTSQuerySessionInformationW';
{$ENDIF DYNAMIC_LINK}
{$IFDEF UNICODE}

{$IFDEF DYNAMIC_LINK}
var
  _WTSQuerySessionInformation: Pointer;

function WTSQuerySessionInformation;
begin
  GetProcedureAddress(_WTSQuerySessionInformation, wtsapi, 'WTSQuerySessionInformationW');
  asm
    mov esp, ebp
    pop ebp
    jmp [_WTSQuerySessionInformation]
  end;
end;
{$ELSE}
function WTSQuerySessionInformation; external wtsapi name 'WTSQuerySessionInformationW';
{$ENDIF DYNAMIC_LINK}
{$ELSE}

{$IFDEF DYNAMIC_LINK}
var
  _WTSQuerySessionInformation: Pointer;

function WTSQuerySessionInformation;
begin
  GetProcedureAddress(_WTSQuerySessionInformation, wtsapi, 'WTSQuerySessionInformationA');
  asm
    mov esp, ebp
    pop ebp
    jmp [_WTSQuerySessionInformation]
  end;
end;
{$ELSE}
function WTSQuerySessionInformation; external wtsapi name 'WTSQuerySessionInformationA';
{$ENDIF DYNAMIC_LINK}
{$ENDIF}

{$IFDEF DYNAMIC_LINK}
var
  _WTSQueryUserConfigA: Pointer;

function WTSQueryUserConfigA;
begin
  GetProcedureAddress(_WTSQueryUserConfigA, wtsapi, 'WTSQueryUserConfigA');
  asm
    mov esp, ebp
    pop ebp
    jmp [_WTSQueryUserConfigA]
  end;
end;
{$ELSE}
function WTSQueryUserConfigA; external wtsapi name 'WTSQueryUserConfigA';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _WTSQueryUserConfigW: Pointer;

function WTSQueryUserConfigW;
begin
  GetProcedureAddress(_WTSQueryUserConfigW, wtsapi, 'WTSQueryUserConfigW');
  asm
    mov esp, ebp
    pop ebp
    jmp [_WTSQueryUserConfigW]
  end;
end;
{$ELSE}
function WTSQueryUserConfigW; external wtsapi name 'WTSQueryUserConfigW';
{$ENDIF DYNAMIC_LINK}
{$IFDEF UNICODE}

{$IFDEF DYNAMIC_LINK}
var
  _WTSQueryUserConfig: Pointer;

function WTSQueryUserConfig;
begin
  GetProcedureAddress(_WTSQueryUserConfig, wtsapi, 'WTSQueryUserConfigW');
  asm
    mov esp, ebp
    pop ebp
    jmp [_WTSQueryUserConfig]
  end;
end;
{$ELSE}
function WTSQueryUserConfig; external wtsapi name 'WTSQueryUserConfigW';
{$ENDIF DYNAMIC_LINK}
{$ELSE}

{$IFDEF DYNAMIC_LINK}
var
  _WTSQueryUserConfig: Pointer;

function WTSQueryUserConfig;
begin
  GetProcedureAddress(_WTSQueryUserConfig, wtsapi, 'WTSQueryUserConfigA');
  asm
    mov esp, ebp
    pop ebp
    jmp [_WTSQueryUserConfig]
  end;
end;
{$ELSE}
function WTSQueryUserConfig; external wtsapi name 'WTSQueryUserConfigA';
{$ENDIF DYNAMIC_LINK}
{$ENDIF}

{$IFDEF DYNAMIC_LINK}
var
  _WTSSetUserConfigA: Pointer;

function WTSSetUserConfigA;
begin
  GetProcedureAddress(_WTSSetUserConfigA, wtsapi, 'WTSSetUserConfigA');
  asm
    mov esp, ebp
    pop ebp
    jmp [_WTSSetUserConfigA]
  end;
end;
{$ELSE}
function WTSSetUserConfigA; external wtsapi name 'WTSSetUserConfigA';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _WTSSetUserConfigW: Pointer;

function WTSSetUserConfigW;
begin
  GetProcedureAddress(_WTSSetUserConfigW, wtsapi, 'WTSSetUserConfigW');
  asm
    mov esp, ebp
    pop ebp
    jmp [_WTSSetUserConfigW]
  end;
end;
{$ELSE}
function WTSSetUserConfigW; external wtsapi name 'WTSSetUserConfigW';
{$ENDIF DYNAMIC_LINK}
{$IFDEF UNICODE}

{$IFDEF DYNAMIC_LINK}
var
  _WTSSetUserConfig: Pointer;

function WTSSetUserConfig;
begin
  GetProcedureAddress(_WTSSetUserConfig, wtsapi, 'WTSSetUserConfigW');
  asm
    mov esp, ebp
    pop ebp
    jmp [_WTSSetUserConfig]
  end;
end;
{$ELSE}
function WTSSetUserConfig; external wtsapi name 'WTSSetUserConfigW';
{$ENDIF DYNAMIC_LINK}
{$ELSE}

{$IFDEF DYNAMIC_LINK}
var
  _WTSSetUserConfig: Pointer;

function WTSSetUserConfig;
begin
  GetProcedureAddress(_WTSSetUserConfig, wtsapi, 'WTSSetUserConfigA');
  asm
    mov esp, ebp
    pop ebp
    jmp [_WTSSetUserConfig]
  end;
end;
{$ELSE}
function WTSSetUserConfig; external wtsapi name 'WTSSetUserConfigA';
{$ENDIF DYNAMIC_LINK}
{$ENDIF}

{$IFDEF DYNAMIC_LINK}
var
  _WTSSendMessageA: Pointer;

function WTSSendMessageA;
begin
  GetProcedureAddress(_WTSSendMessageA, wtsapi, 'WTSSendMessageA');
  asm
    mov esp, ebp
    pop ebp
    jmp [_WTSSendMessageA]
  end;
end;
{$ELSE}
function WTSSendMessageA; external wtsapi name 'WTSSendMessageA';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _WTSSendMessageW: Pointer;

function WTSSendMessageW;
begin
  GetProcedureAddress(_WTSSendMessageW, wtsapi, 'WTSSendMessageW');
  asm
    mov esp, ebp
    pop ebp
    jmp [_WTSSendMessageW]
  end;
end;
{$ELSE}
function WTSSendMessageW; external wtsapi name 'WTSSendMessageW';
{$ENDIF DYNAMIC_LINK}
{$IFDEF UNICODE}

{$IFDEF DYNAMIC_LINK}
var
  _WTSSendMessage: Pointer;

function WTSSendMessage;
begin
  GetProcedureAddress(_WTSSendMessage, wtsapi, 'WTSSendMessageW');
  asm
    mov esp, ebp
    pop ebp
    jmp [_WTSSendMessage]
  end;
end;
{$ELSE}
function WTSSendMessage; external wtsapi name 'WTSSendMessageW';
{$ENDIF DYNAMIC_LINK}
{$ELSE}

{$IFDEF DYNAMIC_LINK}
var
  _WTSSendMessage: Pointer;

function WTSSendMessage;
begin
  GetProcedureAddress(_WTSSendMessage, wtsapi, 'WTSSendMessageA');
  asm
    mov esp, ebp
    pop ebp
    jmp [_WTSSendMessage]
  end;
end;
{$ELSE}
function WTSSendMessage; external wtsapi name 'WTSSendMessageA';
{$ENDIF DYNAMIC_LINK}
{$ENDIF}

{$IFDEF DYNAMIC_LINK}
var
  _WTSDisconnectSession: Pointer;

function WTSDisconnectSession;
begin
  GetProcedureAddress(_WTSDisconnectSession, wtsapi, 'WTSDisconnectSession');
  asm
    mov esp, ebp
    pop ebp
    jmp [_WTSDisconnectSession]
  end;
end;
{$ELSE}
function WTSDisconnectSession; external wtsapi name 'WTSDisconnectSession';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _WTSLogoffSession: Pointer;

function WTSLogoffSession;
begin
  GetProcedureAddress(_WTSLogoffSession, wtsapi, 'WTSLogoffSession');
  asm
    mov esp, ebp
    pop ebp
    jmp [_WTSLogoffSession]
  end;
end;
{$ELSE}
function WTSLogoffSession; external wtsapi name 'WTSLogoffSession';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _WTSShutdownSystem: Pointer;

function WTSShutdownSystem;
begin
  GetProcedureAddress(_WTSShutdownSystem, wtsapi, 'WTSShutdownSystem');
  asm
    mov esp, ebp
    pop ebp
    jmp [_WTSShutdownSystem]
  end;
end;
{$ELSE}
function WTSShutdownSystem; external wtsapi name 'WTSShutdownSystem';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _WTSWaitSystemEvent: Pointer;

function WTSWaitSystemEvent;
begin
  GetProcedureAddress(_WTSWaitSystemEvent, wtsapi, 'WTSWaitSystemEvent');
  asm
    mov esp, ebp
    pop ebp
    jmp [_WTSWaitSystemEvent]
  end;
end;
{$ELSE}
function WTSWaitSystemEvent; external wtsapi name 'WTSWaitSystemEvent';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _WTSVirtualChannelOpen: Pointer;

function WTSVirtualChannelOpen;
begin
  GetProcedureAddress(_WTSVirtualChannelOpen, wtsapi, 'WTSVirtualChannelOpen');
  asm
    mov esp, ebp
    pop ebp
    jmp [_WTSVirtualChannelOpen]
  end;
end;
{$ELSE}
function WTSVirtualChannelOpen; external wtsapi name 'WTSVirtualChannelOpen';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _WTSVirtualChannelClose: Pointer;

function WTSVirtualChannelClose;
begin
  GetProcedureAddress(_WTSVirtualChannelClose, wtsapi, 'WTSVirtualChannelClose');
  asm
    mov esp, ebp
    pop ebp
    jmp [_WTSVirtualChannelClose]
  end;
end;
{$ELSE}
function WTSVirtualChannelClose; external wtsapi name 'WTSVirtualChannelClose';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _WTSVirtualChannelRead: Pointer;

function WTSVirtualChannelRead;
begin
  GetProcedureAddress(_WTSVirtualChannelRead, wtsapi, 'WTSVirtualChannelRead');
  asm
    mov esp, ebp
    pop ebp
    jmp [_WTSVirtualChannelRead]
  end;
end;
{$ELSE}
function WTSVirtualChannelRead; external wtsapi name 'WTSVirtualChannelRead';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _WTSVirtualChannelWrite: Pointer;

function WTSVirtualChannelWrite;
begin
  GetProcedureAddress(_WTSVirtualChannelWrite, wtsapi, 'WTSVirtualChannelWrite');
  asm
    mov esp, ebp
    pop ebp
    jmp [_WTSVirtualChannelWrite]
  end;
end;
{$ELSE}
function WTSVirtualChannelWrite; external wtsapi name 'WTSVirtualChannelWrite';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _WTSVirtualChannelPurgeInput: Pointer;

function WTSVirtualChannelPurgeInput;
begin
  GetProcedureAddress(_WTSVirtualChannelPurgeInput, wtsapi, 'WTSVirtualChannelPurgeInput');
  asm
    mov esp, ebp
    pop ebp
    jmp [_WTSVirtualChannelPurgeInput]
  end;
end;
{$ELSE}
function WTSVirtualChannelPurgeInput; external wtsapi name 'WTSVirtualChannelPurgeInput';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _WTSVirtualChannelPurgeOutput: Pointer;

function WTSVirtualChannelPurgeOutput;
begin
  GetProcedureAddress(_WTSVirtualChannelPurgeOutput, wtsapi, 'WTSVirtualChannelPurgeOutput');
  asm
    mov esp, ebp
    pop ebp
    jmp [_WTSVirtualChannelPurgeOutput]
  end;
end;
{$ELSE}
function WTSVirtualChannelPurgeOutput; external wtsapi name 'WTSVirtualChannelPurgeOutput';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _WTSVirtualChannelQuery: Pointer;

function WTSVirtualChannelQuery;
begin
  GetProcedureAddress(_WTSVirtualChannelQuery, wtsapi, 'WTSVirtualChannelQuery');
  asm
    mov esp, ebp
    pop ebp
    jmp [_WTSVirtualChannelQuery]
  end;
end;
{$ELSE}
function WTSVirtualChannelQuery; external wtsapi name 'WTSVirtualChannelQuery';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _WTSFreeMemory: Pointer;

procedure WTSFreeMemory;
begin
  GetProcedureAddress(_WTSFreeMemory, wtsapi, 'WTSFreeMemory');
  asm
    mov esp, ebp
    pop ebp
    jmp [_WTSFreeMemory]
  end;
end;
{$ELSE}
procedure WTSFreeMemory; external wtsapi name 'WTSFreeMemory';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _WTSRegisterSessionNotification: Pointer;

function WTSRegisterSessionNotification;
begin
  GetProcedureAddress(_WTSRegisterSessionNotification, wtsapi, 'WTSRegisterSessionNotification');
  asm
    mov esp, ebp
    pop ebp
    jmp [_WTSRegisterSessionNotification]
  end;
end;
{$ELSE}
function WTSRegisterSessionNotification; external wtsapi name 'WTSRegisterSessionNotification';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _WTSUnRegisterSessionNot: Pointer;

function WTSUnRegisterSessionNotification;
begin
  GetProcedureAddress(_WTSUnRegisterSessionNot, wtsapi, 'WTSUnRegisterSessionNotification');
  asm
    mov esp, ebp
    pop ebp
    jmp [_WTSUnRegisterSessionNot]
  end;
end;
{$ELSE}
function WTSUnRegisterSessionNotification; external wtsapi name 'WTSUnRegisterSessionNotification';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _WTSQueryUserToken: Pointer;

function WTSQueryUserToken;
begin
  GetProcedureAddress(_WTSQueryUserToken, wtsapi, 'WTSQueryUserToken');
  asm
    mov esp, ebp
    pop ebp
    jmp [_WTSQueryUserToken]
  end;
end;
{$ELSE}
function WTSQueryUserToken; external wtsapi name 'WTSQueryUserToken';
{$ENDIF DYNAMIC_LINK}

end.
