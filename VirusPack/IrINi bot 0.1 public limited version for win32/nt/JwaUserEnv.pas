{******************************************************************************}
{                                                       	               }
{ User Profile API interface Unit for Object Pascal                            }
{                                                       	               }
{ Portions created by Microsoft are Copyright (C) 1995-2001 Microsoft          }
{ Corporation. All Rights Reserved.                                            }
{ 								               }
{ The original file is: userenv.h, released June 2000. The original Pascal     }
{ code is: UserEnv.pas, released December 2000. The initial developer of the   }
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

unit JwaUserEnv;

{$WEAKPACKAGEUNIT}

{$HPPEMIT ''}
{$HPPEMIT '#include "userenv.h"'}
{$HPPEMIT ''}
{$HPPEMIT 'typedef PGROUP_POLICY_OBJECTA *PPGROUP_POLICY_OBJECTA'}
{$HPPEMIT 'typedef PGROUP_POLICY_OBJECTW *PPGROUP_POLICY_OBJECTW'}
{$HPPEMIT ''}
{$HPPEMIT 'typedef #ifdef UNICODE'}
{$HPPEMIT 'typedef PPGROUP_POLICY_OBJECTW PPGROUP_POLICY_OBJECT'}
{$HPPEMIT 'typedef #else'}
{$HPPEMIT 'typedef PPGROUP_POLICY_OBJECTA PPGROUP_POLICY_OBJECT'}
{$HPPEMIT 'typedef #endif'}
{$HPPEMIT ''}

{$I WINDEFINES.INC}

interface

uses
  JwaProfInfo, {WbemCli, }JwaWinType, JWaWinBase, JwaWinNT;

{ TODO Convert WbemCli.h => Import TypeLibrary? }

type
  IWbemServices = Pointer;
  IWbemClassObject = Pointer;
  PSafeArray = Pointer;

{ /TODO }

//=============================================================================
//
// LoadUserProfile
//
// Loads the specified user's profile.
//
// Most applications should not need to use this function.  It's used
// when a user has logged onto the system or a service starts in a named
// user account.
//
// hToken        - Token for the user, returned from LogonUser()
// lpProfileInfo - Address of a PROFILEINFO structure
//
// Returns:  TRUE if successful
//           FALSE if not.  Call GetLastError() for more details
//
// Note:  The caller of this function must have admin privileges on the machine.
//
//        Upon successful return, the hProfile member of the PROFILEINFO
//        structure is a registry key handle opened to the root
//        of the user's hive.  It has been opened with full access. If
//        you need to read or write to the user's registry file, use
//        this key instead of HKEY_CURRENT_USER.  Do not close this
//        handle.  Instead pass it to UnloadUserProfile to close
//        the handle.
//
//=============================================================================

//
// Flags that can be set in the dwFlags field
//

const
  PI_NOUI        = $00000001; // Prevents displaying of messages
  {$EXTERNALSYM PI_NOUI}
  PI_APPLYPOLICY = $00000002; // Apply NT4 style policy
  {$EXTERNALSYM PI_APPLYPOLICY}

function LoadUserProfileA(hToken: HANDLE; var lpProfileInfo: PROFILEINFOA): BOOL; stdcall;
{$EXTERNALSYM LoadUserProfileA}
function LoadUserProfileW(hToken: HANDLE; var lpProfileInfo: PROFILEINFOW): BOOL; stdcall;
{$EXTERNALSYM LoadUserProfileW}

{$IFDEF UNICODE}
function LoadUserProfile(hToken: HANDLE; var lpProfileInfo: PROFILEINFO): BOOL; stdcall;
{$EXTERNALSYM LoadUserProfile}
{$ELSE}
function LoadUserProfile(hToken: HANDLE; var lpProfileInfo: PROFILEINFO): BOOL; stdcall;
{$EXTERNALSYM LoadUserProfile}
{$ENDIF}

//=============================================================================
//
// UnloadUserProfile
//
// Unloads a user's profile that was loaded by LoadUserProfile()
//
// hToken        -  Token for the user, returned from LogonUser()
// hProfile      -  hProfile member of the PROFILEINFO structure
//
// Returns:  TRUE if successful
//           FALSE if not.  Call GetLastError() for more details
//
// Note:     The caller of this function must have admin privileges on the machine.
//
//=============================================================================

function UnloadUserProfile(hToken: HANDLE; hProfile: HANDLE): BOOL; stdcall;
{$EXTERNALSYM UnloadUserProfile}

//=============================================================================
//
// GetProfilesDirectory
//
// Returns the path to the root of where all user profiles are stored.
//
// lpProfilesDir  -  Receives the path
// lpcchSize      -  Size of lpProfilesDir
//
// Returns:  TRUE if successful
//           FALSE if not.  Call GetLastError() for more details
//
// Note:     If lpProfilesDir is not large enough, the function will fail,
//           and lpcchSize will contain the necessary buffer size.
//
// Example return value: C:\Documents and Settings
//
//=============================================================================

function GetProfilesDirectoryA(lpProfilesDir: LPSTR; var lpcchSize: DWORD): BOOL; stdcall;
{$EXTERNALSYM GetProfilesDirectoryA}
function GetProfilesDirectoryW(lpProfilesDir: LPWSTR; var lpcchSize: DWORD): BOOL; stdcall;
{$EXTERNALSYM GetProfilesDirectoryW}

{$IFDEF UNICODE}
function GetProfilesDirectory(lpProfilesDir: LPWSTR; var lpcchSize: DWORD): BOOL; stdcall;
{$EXTERNALSYM GetProfilesDirectory}
{$ELSE}
function GetProfilesDirectory(lpProfilesDir: LPSTR; var lpcchSize: DWORD): BOOL; stdcall;
{$EXTERNALSYM GetProfilesDirectory}
{$ENDIF}

//=============================================================================
//
//  GetProfileType()
//
//  Returns the type of the profile that is loaded for a user.
//
//  dwFlags   - Returns the profile flags
//
//  Return:     TRUE if successful
//              FALSE if an error occurs. Call GetLastError for more details
//
//  Comments:   if profile is not already loaded the function will return an error.
//              The caller needs to have access to HKLM part of the registry.
//              (exists by default)
//
//=============================================================================

//
// Flags that can be set in the dwFlags field
//

const
  PT_TEMPORARY = $00000001; // A profile has been allocated that will be deleted at logoff.
  {$EXTERNALSYM PT_TEMPORARY}
  PT_ROAMING   = $00000002; // The loaded profile is a roaming profile.
  {$EXTERNALSYM PT_ROAMING}
  PT_MANDATORY = $00000004; // The loaded profile is mandatory.
  {$EXTERNALSYM PT_MANDATORY}

function GetProfileType(var dwFlags: DWORD): BOOL; stdcall;
{$EXTERNALSYM GetProfileType}

//=============================================================================
//
//  DeleteProfile()
//
//  Deletes the profile and all other user related settings from the machine
//
//  lpSidString    - String form of the user sid.
//  lpProfilePath  - ProfilePath (if Null, lookup in the registry)
//  lpComputerName - Computer Name from which profile has to be deleted
//
//  Return:     TRUE if successful
//              FALSE if an error occurs. Call GetLastError for more details
//
//  Comments:   Deletes the profile directory, registry and appmgmt stuff
//=============================================================================

function DeleteProfileA(lpSidString: LPCSTR; lpProfilePath: LPCSTR;
  lpComputerName: LPCSTR): BOOL; stdcall;
{$EXTERNALSYM DeleteProfileA}
function DeleteProfileW(lpSidString: LPCWSTR; lpProfilePath: LPCWSTR;
  lpComputerName: LPCWSTR): BOOL; stdcall;
{$EXTERNALSYM DeleteProfileW}

{$IFDEF UNICODE}
function DeleteProfile(lpSidString: LPCWSTR; lpProfilePath: LPCWSTR;
  lpComputerName: LPCWSTR): BOOL; stdcall;
{$EXTERNALSYM DeleteProfile}
{$ELSE}
function DeleteProfile(lpSidString: LPCSTR; lpProfilePath: LPCSTR;
  lpComputerName: LPCSTR): BOOL; stdcall;
{$EXTERNALSYM DeleteProfile}
{$ENDIF}

//=============================================================================
//
// GetDefaultUserProfilesDirectory
//
// Returns the path to the root of the default user profile
//
// lpProfileDir   -  Receives the path
// lpcchSize      -  Size of lpProfileDir
//
// Returns:  TRUE if successful
//           FALSE if not.  Call GetLastError() for more details
//
// Note:     If lpProfileDir is not large enough, the function will fail,
//           and lpcchSize will contain the necessary buffer size.
//
// Example return value: C:\Documents and Settings\Default User
//
//=============================================================================

function GetDefaultUserProfileDirectoryA(lpProfileDir: LPSTR; var lpcchSize: DWORD): BOOL; stdcall;
{$EXTERNALSYM GetDefaultUserProfileDirectoryA}
function GetDefaultUserProfileDirectoryW(lpProfileDir: LPWSTR; var lpcchSize: DWORD): BOOL; stdcall;
{$EXTERNALSYM GetDefaultUserProfileDirectoryW}

{$IFDEF UNICODE}
function GetDefaultUserProfileDirectory(lpProfileDir: LPWSTR; var lpcchSize: DWORD): BOOL; stdcall;
{$EXTERNALSYM GetDefaultUserProfileDirectory}
{$ELSE}
function GetDefaultUserProfileDirectory(lpProfileDir: LPSTR; var lpcchSize: DWORD): BOOL; stdcall;
{$EXTERNALSYM GetDefaultUserProfileDirectory}
{$ENDIF}

//=============================================================================
//
// GetAllUsersProfilesDirectory
//
// Returns the path to the root of the All Users profile
//
// lpProfileDir   -  Receives the path
// lpcchSize      -  Size of lpProfileDir
//
// Returns:  TRUE if successful
//           FALSE if not.  Call GetLastError() for more details
//
// Note:     If lpProfileDir is not large enough, the function will fail,
//           and lpcchSize will contain the necessary buffer size.
//
// Example return value: C:\Documents and Settings\All Users
//
//=============================================================================

function GetAllUsersProfileDirectoryA(lpProfileDir: LPSTR; var lpcchSize: DWORD): BOOL; stdcall;
{$EXTERNALSYM GetAllUsersProfileDirectoryA}
function GetAllUsersProfileDirectoryW(lpProfileDir: LPWSTR; var lpcchSize: DWORD): BOOL; stdcall;
{$EXTERNALSYM GetAllUsersProfileDirectoryW}

{$IFDEF UNICODE}
function GetAllUsersProfileDirectory(lpProfileDir: LPWSTR; var lpcchSize: DWORD): BOOL; stdcall;
{$EXTERNALSYM GetAllUsersProfileDirectory}
{$ELSE}
function GetAllUsersProfileDirectory(lpProfileDir: LPSTR; var lpcchSize: DWORD): BOOL; stdcall;
{$EXTERNALSYM GetAllUsersProfileDirectory}
{$ENDIF}

//=============================================================================
//
// GetUserProfileDirectory
//
// Returns the path to the root of the requested user's profile
//
// hToken         -  User's token returned from LogonUser()
// lpProfileDir   -  Receives the path
// lpcchSize      -  Size of lpProfileDir
//
// Returns:  TRUE if successful
//           FALSE if not.  Call GetLastError() for more details
//
// Note:     If lpProfileDir is not large enough, the function will fail,
//           and lpcchSize will contain the necessary buffer size.
//
// Example return value: C:\Documents and Settings\Joe
//
//=============================================================================

function GetUserProfileDirectoryA(hToken: HANDLE; lpProfileDir: LPSTR;
  var lpcchSize: DWORD): BOOL; stdcall;
{$EXTERNALSYM GetUserProfileDirectoryA}
function GetUserProfileDirectoryW(hToken: HANDLE; lpProfileDir: LPWSTR;
  var lpcchSize: DWORD): BOOL; stdcall;
{$EXTERNALSYM GetUserProfileDirectoryW}

{$IFDEF UNICODE}
function GetUserProfileDirectory(hToken: HANDLE; lpProfileDir: LPWSTR;
  var lpcchSize: DWORD): BOOL; stdcall;
{$EXTERNALSYM GetUserProfileDirectory}
{$ELSE}
function GetUserProfileDirectory(hToken: HANDLE; lpProfileDir: LPSTR;
  var lpcchSize: DWORD): BOOL; stdcall;
{$EXTERNALSYM GetUserProfileDirectory}
{$ENDIF}

//=============================================================================
//
// CreateEnvironmentBlock
//
// Returns the environment variables for the specified user.  This block
// can then be passed to CreateProcessAsUser().
//
// lpEnvironment  -  Receives a pointer to the new environment block
// hToken         -  User's token returned from LogonUser() (optional, can be NULL)
// bInherit       -  Inherit from the current process's environment block
//                   or start from a clean state.
//
// Returns:  TRUE if successful
//           FALSE if not.  Call GetLastError() for more details
//
// Note:     If hToken is NULL, the returned environment block will contain
//           system variables only.
//
//           Call DestroyEnvironmentBlock to free the buffer when finished.
//
//           If this block is passed to CreateProcessAsUser, the
//           CREATE_UNICODE_ENVIRONMENT flag must also be set.
//
//=============================================================================

function CreateEnvironmentBlock(lpEnvironment: LPLPVOID; hToken: HANDLE;
  bInherit: BOOL): BOOL; stdcall;
{$EXTERNALSYM CreateEnvironmentBlock}

//=============================================================================
//
// DestroyEnvironmentBlock
//
// Frees environment variables created by CreateEnvironmentBlock
//
// lpEnvironment  -  A pointer to the environment block
//
// Returns:  TRUE if successful
//           FALSE if not.  Call GetLastError() for more details
//
//=============================================================================

function DestroyEnvironmentBlock(lpEnvironment: LPVOID): BOOL; stdcall;
{$EXTERNALSYM DestroyEnvironmentBlock}

//=============================================================================
//
// ExpandEnvironmentStringsForUser
//
// Expands the source string using the environment block for the
// specified user.  If hToken is null, the system environment block
// will be used (no user environment variables).
//
// hToken         -  User's token returned from LogonUser() (optional, can be NULL)
// lpSrc          -  Pointer to the string with environment variables
// lpDest         -  Buffer that receives the expanded string
// dwSize         -  Size of lpDest in characters (max chars)
//
// Returns:  TRUE if successful
//           FALSE if not.  Call GetLastError() for more details
//
// Note:     If the user profile for hToken is not loaded, this api will fail.
//
//=============================================================================

function ExpandEnvironmentStringsForUserA(hToken: HANDLE; lpSrc: LPCSTR;
  lpDest: LPSTR; dwSize: DWORD): BOOL; stdcall;
{$EXTERNALSYM ExpandEnvironmentStringsForUserA}
function ExpandEnvironmentStringsForUserW(hToken: HANDLE; lpSrc: LPCWSTR;
  lpDest: LPWSTR; dwSize: DWORD): BOOL; stdcall;
{$EXTERNALSYM ExpandEnvironmentStringsForUserW}

{$IFDEF UNICODE}
function ExpandEnvironmentStringsForUser(hToken: HANDLE; lpSrc: LPCWSTR;
  lpDest: LPWSTR; dwSize: DWORD): BOOL; stdcall;
{$EXTERNALSYM ExpandEnvironmentStringsForUser}
{$ELSE}
function ExpandEnvironmentStringsForUser(hToken: HANDLE; lpSrc: LPCSTR;
  lpDest: LPSTR; dwSize: DWORD): BOOL; stdcall;
{$EXTERNALSYM ExpandEnvironmentStringsForUser}
{$ENDIF}

//=============================================================================
//
// RefreshPolicy()
//
// Causes group policy to be applied immediately on the client machine
//
// bMachine  -  Refresh machine or user policy
//
// Returns:  TRUE if successful
//           FALSE if not.  Call GetLastError() for more details
//
//=============================================================================

function RefreshPolicy(bMachine: BOOL): BOOL; stdcall;
{$EXTERNALSYM RefreshPolicy}

//=============================================================================
//
// RefreshPolicyEx()
//
// Causes group policy to be applied immediately on the client machine.
//
// bMachine  -  Refresh machine or user policy
// dwOptions -  Option specifying the kind of refresh that needs to be done.
//
// Returns:  TRUE if successful
//           FALSE if not.  Call GetLastError() for more details
//
//=============================================================================

const
  RP_FORCE = 1; // Refresh policies without any optimisations.
  {$EXTERNALSYM RP_FORCE}

function RefreshPolicyEx(bMachine: BOOL; dwOptions: DWORD): BOOL; stdcall;
{$EXTERNALSYM RefreshPolicyEx}

//=============================================================================
//
// EnterCriticalPolicySection
//
// Pauses the background application of group policy to allow safe
// reading of the registry.  Applications that need to read multiple
// policy entries and ensure that the values are not changed while reading
// them should use this function.
//
// The maximum amount of time an application can hold a critical section
// is 10 minutes.  After 10 minutes, policy can be applied again.
//
// bMachine -  Pause machine or user policy
//
// Returns:  Handle if successful
//           NULL if not.  Call GetLastError() for more details
//
// Note 1:  The handle returned should be passed to LeaveCriticalPolicySection
// when finished.  Do not close this handle, LeaveCriticalPolicySection
// will do that.
//
// Note 2:  If both user and machine critical sections need to be acquired then
// they should be done in this order: first acquire user critical section and
// then acquire machine critical section.
//
//=============================================================================

function EnterCriticalPolicySection(bMachine: BOOL): HANDLE; stdcall;
{$EXTERNALSYM EnterCriticalPolicySection}

//=============================================================================
//
// LeaveCriticalPolicySection
//
// Resumes the background application of group policy.  See
// EnterCriticalPolicySection for more details.
//
// hSection - Handle returned from EnterCriticalPolicySection
//
// Returns:  TRUE if successful
//           FALSE if not.  Call GetLastError() for more details
//
// Note:  This function will close the handle.
//
//=============================================================================

function LeaveCriticalPolicySection(hSection: HANDLE): BOOL; stdcall;
{$EXTERNALSYM LeaveCriticalPolicySection}

//=============================================================================
//
// RegisterGPNotification
//
// Entry point for registering for Group Policy change notification.
//
// Parameters: hEvent     -   Event to be notified, by calling SetEvent(hEvent)
//             bMachine   -   If true, then register machine policy notification
//                                     else register user policy notification
//
// Returns:    True if successful
//             False if error occurs
//
// Notes:      Group Policy Notifications.  There are 2 ways an application can
//             be notify when Group Policy is finished being applied.
//
//             1) Using the RegisterGPNotifcation function and waiting for the
//                event to be signalled.
//
//             2) A WM_SETTINGCHANGE message is broadcast to all desktops.
//                wParam - 1 if machine policy was applied, 0 if user policy was applied.
//                lParam - Points to the string "Policy"
//
//=============================================================================

function RegisterGPNotification(hEvent: HANDLE; bMachine: BOOL): BOOL; stdcall;
{$EXTERNALSYM RegisterGPNotification}

//=============================================================================
//
// UnregisterGPNotification
//
// Removes registration for a Group Policy change notification.
//
// Parameters: hEvent    -   Event to be removed
//
// Returns:    True if successful
//             False if error occurs
//
//=============================================================================

function UnregisterGPNotification(hEvent: HANDLE): BOOL; stdcall;
{$EXTERNALSYM UnregisterGPNotification}

//=============================================================================
//
// GPOptions flags
//
// These are the flags found in the GPOptions property of a DS object
//
// For a given DS object (Site, Domain, OU), the GPOptions property
// contains options that effect all the GPOs link to this SDOU.
//
// This is a DWORD type
//
//=============================================================================

const
  GPC_BLOCK_POLICY = $00000001; // Block all non-forced policy from above
  {$EXTERNALSYM GPC_BLOCK_POLICY}

//=============================================================================
//
// GPLink flags
//
// These are the flags found on the GPLink property of a DS object after
// the GPO path.
//
// For a given DS object (Site, Domain, OU), the GPLink property will
// be in this text format
//
// [LDAP://CN={E615A0E3-C4F1-11D1-A3A7-00AA00615092},CN=Policies,CN=System,DC=mydomain,DC=Microsoft,DC=Com;1]
//
// The GUID is the GPO name, and the number following the LDAP path are the options
// for that link from this DS object.  Note, there can be multiple GPOs
// each in their own square brackets in a prioritized list.
//
//=============================================================================

//
// Options for a GPO link
//

const
  GPO_FLAG_DISABLE = $00000001; // This GPO is disabled
  {$EXTERNALSYM GPO_FLAG_DISABLE}
  GPO_FLAG_FORCE   = $00000002; // Don't override the settings in
  {$EXTERNALSYM GPO_FLAG_FORCE} // this GPO with settings from a GPO below it.

//=============================================================================
//
// GetGPOList
//
//
// Queries for the list of Group Policy Objects for the specified
// user or machine.  This function will return a link list
// of Group Policy Objects.  Call FreeGPOList to free the list.
//
// Note, most applications will not need to call this function.
// This will primarily be used by services acting on behalf of
// another user or machine.  The caller of this function will
// need to look in each GPO for their specific policy
//
// This function can be called in two different ways.  Either the hToken for
// a user or machine can be supplied and the correct name and domain
// controller name will be generated, or hToken is NULL and the caller
// must supply the name and the domain controller name.
//
// Calling this function with an hToken ensures the list of Group Policy
// Objects is correct for the user or machine since security access checking
// can be perfomed.  If hToken is not supplied, the security of the caller
// is used instead which means that list may or may not be 100% correct
// for the intended user / machine.  However, this is the fastest way
// to call this function.
//
// hToken           - User or machine token, if NULL, lpName and lpHostName must be supplied
// lpName           - User or machine name in DN format, if hToken is supplied, this must be NULL
// lpHostName       - Domain DN name or domain controller name. If hToken is supplied, this must be NULL
// lpComputerName   - Computer name to use to determine site location.  If NULL,
//                    the local computer is used as the reference. Format:  \\machinename
// dwFlags          - Flags field.  See flags definition below
// pGPOList         - Address of a pointer which receives the link list of GPOs
//
//
// Returns:  TRUE if successful
//           FALSE if not.  Use GetLastError() for more details.
//
// Examples:
//
// Here's how this function will typically be called for
// looking up the list of GPOs for a user:
//
//      LPGROUP_POLICY_OBJECT  pGPOList;
//
//      if (GetGPOList (hToken, NULL, NULL, NULL, 0, &pGPOList))
//      {
//          // do processing here...
//          FreeGPOList (pGPOList);
//      }
//
//
// Here's how this function will typically be called for
// looking up the list of GPOs for a machine:
//
//      LPGROUP_POLICY_OBJECT  pGPOList;
//
//      if (GetGPOList (NULL, lpMachineName, lpHostName, lpMachineName,
//                      GPO_LIST_FLAG_MACHINE, &pGPOList))
//      {
//          // do processing here...
//          FreeGPOList (pGPOList);
//      }
//
//=============================================================================

//
// Each Group Policy Object is associated (linked) with a site, domain,
// organizational unit, or machine.
//

type
  _GPO_LINK = (
    GPLinkUnknown,                         // No link information available
    GPLinkMachine,                         // GPO linked to a machine (local or remote)
    GPLinkSite,                            // GPO linked to a site
    GPLinkDomain,                          // GPO linked to a domain
    GPLinkOrganizationalUnit);             // GPO linked to a organizational unit
  {$EXTERNALSYM _GPO_LINK}
  GPO_LINK = _GPO_LINK;
  {$EXTERNALSYM GPO_LINK}
  PGPO_LINK = ^GPO_LINK;
  {$EXTERNALSYM PGPO_LINK}
  TGpoLink = GPO_LINK;
  PGpoLink = PGPO_LINK;

  PGROUP_POLICY_OBJECTA = ^GROUP_POLICY_OBJECTA;
  {$EXTERNALSYM PGROUP_POLICY_OBJECTA}
  _GROUP_POLICY_OBJECTA = record
    dwOptions: DWORD;             // See GPLink option flags above
    dwVersion: DWORD;             // Revision number of the GPO
    lpDSPath: LPSTR;              // Path to the Active Directory portion of the GPO
    lpFileSysPath: LPSTR;         // Path to the file system portion of the GPO
    lpDisplayName: LPSTR;         // Friendly display name
    szGPOName: array [0..49] of CHAR; // Unique name
    GPOLink: GPO_LINK;            // Link information
    lParam: LPARAM;               // Free space for the caller to store GPO specific information
    pNext: PGROUP_POLICY_OBJECTA; // Next GPO in the list
    pPrev: PGROUP_POLICY_OBJECTA; // Previous GPO in the list
    lpExtensions: LPSTR;          // Extensions that are relevant for this GPO
    lParam2: LPARAM;              // Free space for the caller to store GPO specific information
    lpLink: LPSTR;                // Path to the Active Directory site, domain, or organizational unit this GPO is linked to
                                  // If this is the local GPO, this points to the word "Local"
  end;
  {$EXTERNALSYM _GROUP_POLICY_OBJECTA}
  GROUP_POLICY_OBJECTA = _GROUP_POLICY_OBJECTA;
  {$EXTERNALSYM GROUP_POLICY_OBJECTA}
  TGroupPolicyObjectA = GROUP_POLICY_OBJECTA;
  PGroupPolicyObjectA = PGROUP_POLICY_OBJECTA;

  PGROUP_POLICY_OBJECTW = ^GROUP_POLICY_OBJECTW;
  {$EXTERNALSYM PGROUP_POLICY_OBJECTW}
  _GROUP_POLICY_OBJECTW = record
    dwOptions: DWORD;             // See GPLink option flags above
    dwVersion: DWORD;             // Revision number of the GPO
    lpDSPath: LPWSTR;             // Path to the Active Directory portion of the GPO
    lpFileSysPath: LPWSTR;        // Path to the file system portion of the GPO
    lpDisplayName: LPWSTR;        // Friendly display name
    szGPOName: array [0..49] of WCHAR; // Unique name
    GPOLink: GPO_LINK;            // Link information
    lParam: LPARAM;               // Free space for the caller to store GPO specific information
    pNext: PGROUP_POLICY_OBJECTW; // Next GPO in the list
    pPrev: PGROUP_POLICY_OBJECTW; // Previous GPO in the list
    lpExtensions: LPWSTR;         // Extensions that are relevant for this GPO
    lParam2: LPARAM;              // Free space for the caller to store GPO specific information
    lpLink: LPWSTR;               // Path to the Active Directory site, domain, or organizational unit this GPO is linked to
                                  // If this is the local GPO, this points to the word "Local"
  end;
  {$EXTERNALSYM _GROUP_POLICY_OBJECTW}
  GROUP_POLICY_OBJECTW = _GROUP_POLICY_OBJECTW;
  {$EXTERNALSYM GROUP_POLICY_OBJECTW}
  TGroupPolicyObjectW = GROUP_POLICY_OBJECTW;
  PGroupPolicyObjectW = PGROUP_POLICY_OBJECTW;

  PPGROUP_POLICY_OBJECTA = ^PGROUP_POLICY_OBJECTA;
  {$NODEFINE PPGROUP_POLICY_OBJECTA}
  PPGROUP_POLICY_OBJECTW = ^PGROUP_POLICY_OBJECTW;
  {$NODEFINE PPGROUP_POLICY_OBJECTW}

{$IFDEF UNICODE}
  GROUP_POLICY_OBJECT = GROUP_POLICY_OBJECTW;
  {$EXTERNALSYM GROUP_POLICY_OBJECT}
  PGROUP_POLICY_OBJECT = PGROUP_POLICY_OBJECTW;
  {$EXTERNALSYM PGROUP_POLICY_OBJECT}
  PPGROUP_POLICY_OBJECT = PPGROUP_POLICY_OBJECTW;
  {$NODEFINE PPGROUP_POLICY_OBJECT}
  TGroupPolicyObject = TGroupPolicyObjectW;
  PGroupPolicyObject = PGroupPolicyObjectW;
{$ELSE}
  GROUP_POLICY_OBJECT = GROUP_POLICY_OBJECTA;
  {$EXTERNALSYM GROUP_POLICY_OBJECT}
  PGROUP_POLICY_OBJECT = PGROUP_POLICY_OBJECTA;
  {$EXTERNALSYM PGROUP_POLICY_OBJECT}
  PPGROUP_POLICY_OBJECT = PPGROUP_POLICY_OBJECTA;
  {$NODEFINE PPGROUP_POLICY_OBJECT}
  TGroupPolicyObject = TGroupPolicyObjectA;
  PGroupPolicyObject = PGroupPolicyObjectA;
{$ENDIF}

//
// dwFlags for GetGPOList()
//

const
  GPO_LIST_FLAG_MACHINE  = $00000001; // Return machine policy information
  {$EXTERNALSYM GPO_LIST_FLAG_MACHINE}
  GPO_LIST_FLAG_SITEONLY = $00000002; // Return site policy information only
  {$EXTERNALSYM GPO_LIST_FLAG_SITEONLY}

function GetGPOListA(hToken: HANDLE; lpName: LPCSTR; lpHostName: LPCSTR;
  lpComputerName: LPCSTR; dwFlags: DWORD; pGPOList: PPGROUP_POLICY_OBJECTA): BOOL; stdcall;
{$EXTERNALSYM GetGPOListA}
function GetGPOListW(hToken: HANDLE; lpName: LPCWSTR; lpHostName: LPCWSTR;
  lpComputerName: LPCWSTR; dwFlags: DWORD; pGPOList: PPGROUP_POLICY_OBJECTW): BOOL; stdcall;
{$EXTERNALSYM GetGPOListW}

{$IFDEF UNICODE}
function GetGPOList(hToken: HANDLE; lpName: LPCWSTR; lpHostName: LPCWSTR;
  lpComputerName: LPCWSTR; dwFlags: DWORD; pGPOList: PPGROUP_POLICY_OBJECT): BOOL; stdcall;
{$EXTERNALSYM GetGPOList}
{$ELSE}
function GetGPOList(hToken: HANDLE; lpName: LPCSTR; lpHostName: LPCSTR;
lpComputerName: LPCSTR; dwFlags: DWORD; pGPOList: PPGROUP_POLICY_OBJECT): BOOL; stdcall;
{$EXTERNALSYM GetGPOList}
{$ENDIF}

//=============================================================================
//
// FreeGPOList
//
//
// Frees the linked list returned from GetGPOList
//
// pGPOList - Pointer to the linked list of GPOs
//
//
// Returns:  TRUE if successful
//           FALSE if not
//
//=============================================================================

function FreeGPOListA(pGPOList: PGROUP_POLICY_OBJECTA): BOOL; stdcall;
{$EXTERNALSYM FreeGPOListA}
function FreeGPOListW(pGPOList: PGROUP_POLICY_OBJECTW): BOOL; stdcall;
{$EXTERNALSYM FreeGPOListW}

{$IFDEF UNICODE}
function FreeGPOList(pGPOList: PGROUP_POLICY_OBJECT): BOOL; stdcall;
{$EXTERNALSYM FreeGPOList}
{$ELSE}
function FreeGPOList(pGPOList: PGROUP_POLICY_OBJECT): BOOL; stdcall;
{$EXTERNALSYM FreeGPOList}
{$ENDIF}

//=============================================================================
//
// GetAppliedGPOList
//
// Queries for the list of applied Group Policy Objects for the specified
// user or machine and specified client side extension. This function will return
// a linked listof Group Policy Objects.  Call FreeGPOList to free the list.
//
// dwFlags          - User or machine policy, if it is GPO_LIST_FLAG_MACHINE then
//                    return machine policy information
// pMachineName     - Name of remote computer in the form \\computername. If null
//                    then local computer is used.
// pSidUser         - Security id of user (relevant for user policy). If pMachineName is
//                    null and pSidUser is null then it means current logged on user.
//                    If pMachine is null and pSidUser is non-null then it means user
//                    represented by pSidUser on local machine. If pMachineName is non-null
//                    then and if dwFlags specifies user policy, then pSidUser must be
//                    non-null.
// pGuidExtension   - Guid of the specified extension
// ppGPOList        - Address of a pointer which receives the link list of GPOs
//
// The return value is a Win32 error code. ERROR_SUCCESS means the GetAppliedGPOList
// function completed successfully. Otherwise it indicates that the function failed.
//
//=============================================================================

function GetAppliedGPOListA(dwFlags: DWORD; pMachineName: LPCSTR; pSidUser: PSID;
  pGuidExtension: LPGUID; ppGPOList: PPGROUP_POLICY_OBJECTA): DWORD; stdcall;
{$EXTERNALSYM GetAppliedGPOListA}
function GetAppliedGPOListW(dwFlags: DWORD; pMachineName: LPCWSTR; pSidUser: PSID;
  pGuidExtension: LPGUID; ppGPOList: PPGROUP_POLICY_OBJECTW): DWORD; stdcall;
{$EXTERNALSYM GetAppliedGPOListW}

{$IFDEF UNICODE}
function GetAppliedGPOList(dwFlags: DWORD; pMachineName: LPCWSTR; pSidUser: PSID;
  pGuidExtension: LPGUID; ppGPOList: PPGROUP_POLICY_OBJECT): DWORD; stdcall;
{$EXTERNALSYM GetAppliedGPOList}
{$ELSE}
function GetAppliedGPOList(dwFlags: DWORD; pMachineName: LPCSTR; pSidUser: PSID;
  pGuidExtension: LPGUID; ppGPOList: PPGROUP_POLICY_OBJECT): DWORD; stdcall;
{$EXTERNALSYM GetAppliedGPOList}
{$ENDIF}

//=============================================================================
//
// Group Policy Object client side extension support
//
// Flags, data structures and function prototype
//
// To register your extension, create a subkey under this key
//
// Software\Microsoft\Windows NT\CurrentVersion\Winlogon\GPExtensions
//
// The subkey needs to be a guid so that it is unique. The noname value of the subkey
// can be the friendly name of the extension. Then add these values:
//
//     DllName                      REG_EXPAND_SZ  Path to your DLL
//     ProcessGroupPolicy           REG_SZ       Function name (see PFNPROCESSGROUPPOLICY prototype). This
//                                                 is obsolete, it has been superseded by ProcessGroupPolicyEx.
//                                                 It's here for backward compatibility reasons only.
//     ProcessGroupPolicyEx         REG_SZ       Function name (see PFNPROCESSGROUPPOLICYEX prototype)
//     GenerateGroupPolicy          REG_SZ       Function name for Rsop (see PFNGENERATEGROUPPOLICY prototype)
//     NoMachinePolicy              REG_DWORD    True, if extension does not have to be called when
//                                                 machine policies are being processed.
//     NoUserPolicy                 REG_DWORD    True, if extension does not have to be called when
//                                                 user policies are being processed.
//     NoSlowLink                   REG_DWORD    True, if extension does not have to be called on a slow link
//     NoBackgroundPolicy           REG_DWORD    True, if extension does not have to be called 
//                                                 for background policy processing.
//     NoGPOListChanges             REG_DWORD    True, if extension does not have to be called when
//                                                 there are no changes between cached and current GPO lists.
//     PerUserLocalSettings         REG_DWORD    True, if user policies have to be cached on a per user and
//                                                 per machine basis.
//     RequiresSuccessfulRegistry   REG_DWORD    True, if extension should be called only if registry extension
//                                                 was successfully processed.
//     EnableAsynchronousProcessing REG_DWORD    True, if registry extension will complete its processing
//                                                 asynchronously.
//     NotifyLinkTransition         REG_DWORD    True, if extension should be called when a change in link
//                                                 speed is detected between previous policy application and
//                                                 current policy application.
//
// The return value is a Win32 error code. ERROR_SUCCESS means the ProcessGroupPolicy
// function completed successfully. If return value is ERROR_OVERRIDE_NOCHANGES then it
// means that the extension will be called the next time even if NoGPOListChanges is set
// and there are no changes to the GPO list. Any other return value indicates that the
// ProcessGroupPolicy or ProcessGroupPolicyEx function failed.
//
//=============================================================================

const
  GP_DLLNAME                       = 'DllName';
  {$EXTERNALSYM GP_DLLNAME}
  GP_ENABLEASYNCHRONOUSPROCESSING  = 'EnableAsynchronousProcessing';
  {$EXTERNALSYM GP_ENABLEASYNCHRONOUSPROCESSING}
  GP_MAXNOGPOLISTCHANGESINTERVAL   = 'MaxNoGPOListChangesInterval';
  {$EXTERNALSYM GP_MAXNOGPOLISTCHANGESINTERVAL}
  GP_NOBACKGROUNDPOLICY            = 'NoBackgroundPolicy';
  {$EXTERNALSYM GP_NOBACKGROUNDPOLICY}
  GP_NOGPOLISTCHANGES              = 'NoGPOListChanges';
  {$EXTERNALSYM GP_NOGPOLISTCHANGES}
  GP_NOMACHINEPOLICY               = 'NoMachinePolicy';
  {$EXTERNALSYM GP_NOMACHINEPOLICY}
  GP_NOSLOWLINK                    = 'NoSlowLink';
  {$EXTERNALSYM GP_NOSLOWLINK}
  GP_NOTIFYLINKTRANSITION          = 'NotifyLinkTransition';
  {$EXTERNALSYM GP_NOTIFYLINKTRANSITION}
  GP_NOUSERPOLICY                  = 'NoUserPolicy';
  {$EXTERNALSYM GP_NOUSERPOLICY}
  GP_PERUSERLOCALSETTINGS          = 'PerUserLocalSettings';
  {$EXTERNALSYM GP_PERUSERLOCALSETTINGS}
  GP_PROCESSGROUPPOLICY            = 'ProcessGroupPolicy';
  {$EXTERNALSYM GP_PROCESSGROUPPOLICY}
  GP_REQUIRESSUCCESSFULREGISTRY    = 'RequiresSuccessfulRegistry';
  {$EXTERNALSYM GP_REQUIRESSUCCESSFULREGISTRY}

  GPO_INFO_FLAG_MACHINE        = $00000001;   // Apply machine policy rather than user policy
  {$EXTERNALSYM GPO_INFO_FLAG_MACHINE}
  GPO_INFO_FLAG_BACKGROUND     = $00000010;   // Background refresh of policy (ok to do slow stuff)
  {$EXTERNALSYM GPO_INFO_FLAG_BACKGROUND}
  GPO_INFO_FLAG_SLOWLINK       = $00000020;   // Policy is being applied across a slow link
  {$EXTERNALSYM GPO_INFO_FLAG_SLOWLINK}
  GPO_INFO_FLAG_VERBOSE        = $00000040;   // Verbose output to the eventlog
  {$EXTERNALSYM GPO_INFO_FLAG_VERBOSE}
  GPO_INFO_FLAG_NOCHANGES      = $00000080;   // No changes were detected to the Group Policy Objects
  {$EXTERNALSYM GPO_INFO_FLAG_NOCHANGES}
  GPO_INFO_FLAG_LINKTRANSITION = $00000100;   // A change in link speed was detected between previous policy
  {$EXTERNALSYM GPO_INFO_FLAG_LINKTRANSITION} // application and current policy application

  GPO_INFO_FLAG_LOGRSOP_TRANSITION = $00000200;   // A Change in Rsop Logging was detected between previous policy
  {$EXTERNALSYM GPO_INFO_FLAG_LOGRSOP_TRANSITION} // application and current policy application, (new intf only)

  GPO_INFO_FLAG_FORCED_REFRESH     = $00000400;  // Forced Refresh is being applied. redo policies.
  {$EXTERNALSYM GPO_INFO_FLAG_FORCED_REFRESH}
  GPO_INFO_FLAG_SAFEMODE_BOOT      = $00000800;  // windows safe mode boot flag
  {$EXTERNALSYM GPO_INFO_FLAG_SAFEMODE_BOOT}
  GPO_INFO_FLAG_ASYNC_FOREGROUND   = $00001000;  // Asynchronous foreground refresh of policy
  {$EXTERNALSYM GPO_INFO_FLAG_ASYNC_FOREGROUND}
  GPO_INFO_FLAG_REPORT             = $00002000;  // Report all settings for one GPO rather than the resultant settings across multiple GPOs
  {$EXTERNALSYM GPO_INFO_FLAG_REPORT}

type
  ASYNCCOMPLETIONHANDLE = UINT_PTR;
  {$EXTERNALSYM ASYNCCOMPLETIONHANDLE}

  PFNSTATUSMESSAGECALLBACK = function (bVerbose: BOOL; lpMessage: LPWSTR): DWORD; stdcall;
  {$EXTERNALSYM PFNSTATUSMESSAGECALLBACK}

  PFNPROCESSGROUPPOLICY = function (
    dwFlags: DWORD;                              // GPO_INFO_FLAGS
    hToken: HANDLE;                              // User or machine token
    hKeyRoot: HKEY;                              // Root of registry
    pDeletedGPOList: PGROUP_POLICY_OBJECT;       // Linked list of deleted GPOs
    pChangedGPOList: PGROUP_POLICY_OBJECT;       // Linked list of changed GPOs
    pHandle: ASYNCCOMPLETIONHANDLE;              // For asynchronous completion
    pbAbort: LPBOOL;                             // If true, then abort GPO processing
    pStatusCallback: PFNSTATUSMESSAGECALLBACK    // Callback function for displaying status messages
    ): DWORD; stdcall;                           // Note, this can be NULL
  {$EXTERNALSYM PFNPROCESSGROUPPOLICY}

  PFNPROCESSGROUPPOLICYEX = function (
    dwFlags: DWORD;                              // GPO_INFO_FLAGS
    hToken: HANDLE;                              // User or machine token
    hKeyRoot: HKEY;                              // Root of registry
    pDeletedGPOList: PGROUP_POLICY_OBJECT;       // Linked list of deleted GPOs
    pChangedGPOList: PGROUP_POLICY_OBJECT;       // Linked list of changed GPOs
    pHandle: ASYNCCOMPLETIONHANDLE;              // For asynchronous completion
    pbAbort: PBOOL;                              // If true, then abort GPO processing
    pStatusCallback: PFNSTATUSMESSAGECALLBACK;   // Callback function for displaying status messages
                                                 // Note, this can be NULL
    pWbemServices: IWbemServices;                // Pointer to namespace to log diagnostic mode data
                                                 // Note, this will be NULL when Rsop logging is disabled
    var pRsopStatus: HRESULT                     // RSOP Logging succeeded or not.
    ): DWORD; stdcall;
  {$EXTERNALSYM PFNPROCESSGROUPPOLICYEX}

  PRSOPTOKEN = PVOID;
  {$EXTERNALSYM PRSOPTOKEN}

  _RSOP_TARGET = record
    pwszAccountName: PWCHAR;                   // Account name
    pwszNewSOM: PWCHAR;                        // New domain or OU location for account
    psaSecurityGroups: PSafeArray;             // New security groups
    pRsopToken: PRSOPTOKEN;                    // Rsop token for use with Rsop security Api's
    pGPOList: PGROUP_POLICY_OBJECT;            // Linked list of GPOs
    pWbemServices: IWbemServices;              // Pointer to namespace to log planning mode data
  end;
  {$EXTERNALSYM _RSOP_TARGET}
  RSOP_TARGET = _RSOP_TARGET;
  {$EXTERNALSYM RSOP_TARGET}
  PRSOP_TARGET = ^RSOP_TARGET;
  {$EXTERNALSYM PRSOP_TARGET}
  TRsopTarget = RSOP_TARGET;
  PRsopTarget = PRSOP_TARGET;  

  PFNGENERATEGROUPPOLICY = function (
    dwFlags: DWORD;                              // GPO_INFO_FLAGS
    var pbAbort: BOOL;                           // If true, then abort GPO processing
    pwszSite: PWCHAR;                            // Site the target computer is in
    pComputerTarget: PRSOP_TARGET;               // Computer target info, can be null
    pUserTarget: PRSOP_TARGET                    // User target info, can be null
    ): DWORD; stdcall;
  {$EXTERNALSYM PFNGENERATEGROUPPOLICY}

//
// GUID that identifies the registry extension
//

const
  REGISTRY_EXTENSION_GUID: GUID = (
    D1: $35378EAC; D2:$683F; D3:$11D2; D4:($A8, $9A, $00, $C0, $4F, $BB, $CF, $A2));
  {$EXTERNALSYM REGISTRY_EXTENSION_GUID}

//=============================================================================
//
// Group Policy Object client side asynchronous extension processing
//
// extensionId    - Unique guid identifying the extension
// pAsyncHandle   - Asynchronous completion handle that was passed to extension in
//                  ProcessGroupPolicy call
// dwStatus       - Completion status of asynchronous processing
//
// The return value is a Win32 error code. ERROR_SUCCESS means the ProcessGroupPolicyCompleted
// function completed successfully. Otherwise it indicates that the function failed.
//
//=============================================================================

type
  REFGPEXTENSIONID = LPGUID;
  {$EXTERNALSYM REFGPEXTENSIONID}

function ProcessGroupPolicyCompleted(extensionId: REFGPEXTENSIONID;
  pAsyncHandle: ASYNCCOMPLETIONHANDLE; dwStatus: DWORD): DWORD; stdcall;
{$EXTERNALSYM ProcessGroupPolicyCompleted}

//=============================================================================
//
// Group Policy Object client side asynchronous extension processing
//
// extensionId    - Unique guid identifying the extension
// pAsyncHandle   - Asynchronous completion handle that was passed to extension in
//                  ProcessGroupPolicy call
// dwStatus       - Completion status of asynchronous processing
// RsopStatus     - RSoP Logging status
//
// The return value is a Win32 error code. ERROR_SUCCESS means the ProcessGroupPolicyCompleted
// function completed successfully. Otherwise it indicates that the function failed.
//
//=============================================================================

function ProcessGroupPolicyCompletedEx(extensionId: REFGPEXTENSIONID; pAsyncHandle: ASYNCCOMPLETIONHANDLE;
  dwStatus: DWORD; RsopStatus: HRESULT): DWORD; stdcall;
{$EXTERNALSYM ProcessGroupPolicyCompletedEx}

//=============================================================================
//
// Function:    RsopAccessCheckByType
//
// Description: Determines whether the security descriptor pointed to by pSecurityDescriptor
//                              grants the set of access rights specified in dwDesiredAccessMask
//                              to the client identified by the RSOPTOKEN pointed to by pRsopToken.
//
// pSecurityDescriptor  - Security Descriptor on the object
// pPrincipalSelfSid    - Principal Sid
// pRsopToken           - Pointer to a valid RSOPTOKEN against which access needs to be checked
// dwDesiredAccessMask  - Mask of requested generic and/or standard and or specific access rights
// pObjectTypeList      - Object Type List
// ObjectTypeListLength - Object Type List Length
// pGenericMapping      - Generic Mapping
// pPrivilegeSet        - privilege set
// pdwPrivilegeSetLength- privilege set length
// pdwGrantedAccessMask	- On success, if pbAccessStatus is true, it contains
//                                         the mask of standard and specific rights granted.
//                                         If pbAccessStatus is false, it is set to 0.
//                                         On failure, it is not modified.
// pbAccessStatus       - On success, indicates wether the requested set
//                                    of access rights was granted.
//                                    On failure, it is not modified
//
// Returns S_OK on success or appropriate error code.
// For additional details, look at the documentation of AccessCheckByType
//=============================================================================

function RsopAccessCheckByType(pSecurityDescriptor: PSECURITY_DESCRIPTOR; pPrincipalSelfSid: PSID;
  pRsopToken: PRSOPTOKEN; dwDesiredAccessMask: DWORD; pObjectTypeList: POBJECT_TYPE_LIST;
  ObjectTypeListLength: DWORD; pGenericMapping: PGENERIC_MAPPING; pPrivilegeSet: PPRIVILEGE_SET;
  pdwPrivilegeSetLength: LPDWORD; pdwGrantedAccessMask: LPDWORD; pbAccessStatus: LPBOOL): HRESULT; stdcall;
{$EXTERNALSYM RsopAccessCheckByType}

//=============================================================================
//
// Function:    RsopFileAccessCheck
//
// Description: Determines whether the security descriptor on the file grants the set of file access
//                              rights specified in dwDesiredAccessMask
//                              to the client identified by the RSOPTOKEN pointed to by pRsopToken.
//
// pszFileName          - Name of an existing filename
// pRsopToken           - Pointer to a valid RSOPTOKEN against which access needs to be checked
// dwDesiredAccessMask  - Mask of requested generic and/or standard and or specific access rights
// pdwGrantedAccessMask	- On success, if pbAccessStatus is true, it contains
//                                         the mask of standard and specific rights granted.
//                                         If pbAccessStatus is false, it is set to 0.
//                                         On failure, it is not modified.
// pbAccessStatus       - On success, indicates wether the requested set
//                                    of access rights was granted.
//                                    On failure, it is not modified
//
// Returns S_OK on success or appropriate error code
//=============================================================================

function RsopFileAccessCheck(pszFileName: LPWSTR; pRsopToken: PRSOPTOKEN; dwDesiredAccessMask: DWORD;
  pdwGrantedAccessMask: LPDWORD; pbAccessStatus: LPBOOL): HRESULT; stdcall;
{$EXTERNALSYM RsopFileAccessCheck}

type
  _SETTINGSTATUS = (
    RSOPUnspecified,
    RSOPApplied,
    RSOPIgnored,
    RSOPFailed,
    RSOPSubsettingFailed);
  {$EXTERNALSYM _SETTINGSTATUS}
  SETTINGSTATUS = _SETTINGSTATUS;
  {$EXTERNALSYM SETTINGSTATUS}
  TSettingStatus = SETTINGSTATUS;

//=============================================================================
//
//  POLICYSETTINGSTATUSINFO
//
//  Describes the instance of RSOP_PolicySettingStatus
//
//  szKey               - OPTIONAL, if NULL, the key is generated on the fly
//  szEventSource       - name of the source generation event log messages
//  szEventLogName      - name of the event log database where the messages are logged
//  dwEventID           - event log message ID
//  status              - status of the policy setting
//  timeLogged          - time at which the event log message was logged
//
//=============================================================================

type
  _POLICYSETTINGSTATUSINFO = record
    szKey: LPWSTR;
    szEventSource: LPWSTR;
    szEventLogName: LPWSTR;
    dwEventID: DWORD;
    dwErrorCode: DWORD;
    status: SETTINGSTATUS;
    timeLogged: SYSTEMTIME;
  end;
  {$EXTERNALSYM _POLICYSETTINGSTATUSINFO}
  POLICYSETTINGSTATUSINFO = _POLICYSETTINGSTATUSINFO;
  {$EXTERNALSYM POLICYSETTINGSTATUSINFO}
  LPPOLICYSETTINGSTATUSINFO = ^POLICYSETTINGSTATUSINFO;
  {$EXTERNALSYM LPPOLICYSETTINGSTATUSINFO}
  TPolicySettingStatusInfo = POLICYSETTINGSTATUSINFO;
  PPolicySettingStatusInfo = LPPOLICYSETTINGSTATUSINFO;

//=============================================================================
//
//  RsopSetPolicySettingStatus
//
//  Creates an instance of RSOP_PolicySettingStatus and RSOP_PolicySettingLink
//  and links RSOP_PolicySettingStatus to RSOP_PolicySetting
//
//  dwFlags             - flags
//  pServices           - RSOP namespace
//  pSettingInstance    - instance of RSOP_PolicySetting or its children
//  nInfo               - number of PolicySettingStatusInfo
//  pStatus             - array of PolicySettingStatusInfo
//
//  Return:     S_OK if successful, HRESULT otherwise
//
//=============================================================================

function RsopSetPolicySettingStatus(dwFlags: DWORD; pServices: IWbemServices;
  pSettingInstance: IWbemClassObject; nInfo: DWORD;
  pStatus: LPPOLICYSETTINGSTATUSINFO): HRESULT; stdcall;
{$EXTERNALSYM RsopSetPolicySettingStatus}

//=============================================================================
//
//  RsopResetPolicySettingStatus
//
//  Unlinks RSOP_PolicySettingStatus from RSOP_PolicySetting,
//  deletes the instance of RSOP_PolicySettingStatus and RSOP_PolicySettingLink
//  and optionally deletes the instance of RSOP_PolicySetting
//
//  dwFlags             - flags
//  pServices           - RSOP namespace
//  pSettingInstance    - instance of RSOP_PolicySetting or its children
//
//  Return:     S_OK if successful, HRESULT otherwise
//
//=============================================================================

function RsopResetPolicySettingStatus(dwFlags: DWORD; pServices: IWbemServices;
  pSettingInstance: IWbemClassObject): HRESULT; stdcall;
{$EXTERNALSYM RsopResetPolicySettingStatus}

//=============================================================================
//
// Flags for RSoP WMI providers
//
//=============================================================================

// planning mode provider flags

const
  FLAG_NO_GPO_FILTER     = DWORD($80000000);  // GPOs are not filtered, implies FLAG_NO_CSE_INVOKE
  {$EXTERNALSYM FLAG_NO_GPO_FILTER}
  FLAG_NO_CSE_INVOKE     = $40000000;  // only GP processing done for planning mode
  {$EXTERNALSYM FLAG_NO_CSE_INVOKE}
  FLAG_ASSUME_SLOW_LINK  = $20000000;  // planning mode RSoP assumes slow link
  {$EXTERNALSYM FLAG_ASSUME_SLOW_LINK}
  FLAG_LOOPBACK_MERGE    = $10000000;  // planning mode RSoP assumes merge loop back
  {$EXTERNALSYM FLAG_LOOPBACK_MERGE}
  FLAG_LOOPBACK_REPLACE  = $08000000;  // planning mode RSoP assumes replace loop back
  {$EXTERNALSYM FLAG_LOOPBACK_REPLACE}

  FLAG_ASSUME_USER_WQLFILTER_TRUE  = $04000000;  // planning mode RSoP assumes all comp filters to be true
  {$EXTERNALSYM FLAG_ASSUME_USER_WQLFILTER_TRUE}
  FLAG_ASSUME_COMP_WQLFILTER_TRUE  = $02000000;  // planning mode RSoP assumes all user filters to be true
  {$EXTERNALSYM FLAG_ASSUME_COMP_WQLFILTER_TRUE}

  FLAG_PLANNING_MODE               = $01000000;  // flag that indicates that a given namespace was created
  {$EXTERNALSYM FLAG_PLANNING_MODE}              // for planning mode. This flag cannot be passed in but the
					         // relevant subnamespace will be marked with this flag

// diagnostic mode provider flags

  FLAG_NO_USER                     = $00000001;  // Don't get any user data
  {$EXTERNALSYM FLAG_NO_USER}
  FLAG_NO_COMPUTER                 = $00000002;  // Don't get any machine data
  {$EXTERNALSYM FLAG_NO_COMPUTER}
  FLAG_FORCE_CREATENAMESPACE       = $00000004;  // Delete and recreate the namespace for this snapshot.
  {$EXTERNALSYM FLAG_FORCE_CREATENAMESPACE}

//=============================================================================
//
// Extended Errors returned by RSoP WMI Providers
//
//=============================================================================

// User accessing the rsop provider doesn't have access to user data.

  RSOP_USER_ACCESS_DENIED = $00000001;
  {$EXTERNALSYM RSOP_USER_ACCESS_DENIED}

// User accessing the rsop provider doesn't have access to computer data.

  RSOP_COMPUTER_ACCESS_DENIED = $00000002;
  {$EXTERNALSYM RSOP_COMPUTER_ACCESS_DENIED}

// This user is an interactive non admin user, the temp snapshot namespace already exists
// and the FLAG_FORCE_CREATENAMESPACE was not passed in

  RSOP_TEMPNAMESPACE_EXISTS = $00000004;
  {$EXTERNALSYM RSOP_TEMPNAMESPACE_EXISTS}

implementation

const
  userenvlib = 'userenv.dll';


{$IFDEF DYNAMIC_LINK}
var
  _LoadUserProfileA: Pointer;

function LoadUserProfileA;
begin
  GetProcedureAddress(_LoadUserProfileA, userenvlib, 'LoadUserProfileA');
  asm
    mov esp, ebp
    pop ebp
    jmp [_LoadUserProfileA]
  end;
end;
{$ELSE}
function LoadUserProfileA; external userenvlib name 'LoadUserProfileA';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _LoadUserProfileW: Pointer;

function LoadUserProfileW;
begin
  GetProcedureAddress(_LoadUserProfileW, userenvlib, 'LoadUserProfileW');
  asm
    mov esp, ebp
    pop ebp
    jmp [_LoadUserProfileW]
  end;
end;
{$ELSE}
function LoadUserProfileW; external userenvlib name 'LoadUserProfileW';
{$ENDIF DYNAMIC_LINK}
{$IFDEF UNICODE}

{$IFDEF DYNAMIC_LINK}
var
  _LoadUserProfile: Pointer;

function LoadUserProfile;
begin
  GetProcedureAddress(_LoadUserProfile, userenvlib, 'LoadUserProfileW');
  asm
    mov esp, ebp
    pop ebp
    jmp [_LoadUserProfile]
  end;
end;
{$ELSE}
function LoadUserProfile; external userenvlib name 'LoadUserProfileW';
{$ENDIF DYNAMIC_LINK}
{$ELSE}

{$IFDEF DYNAMIC_LINK}
var
  _LoadUserProfile: Pointer;

function LoadUserProfile;
begin
  GetProcedureAddress(_LoadUserProfile, userenvlib, 'LoadUserProfileA');
  asm
    mov esp, ebp
    pop ebp
    jmp [_LoadUserProfile]
  end;
end;
{$ELSE}
function LoadUserProfile; external userenvlib name 'LoadUserProfileA';
{$ENDIF DYNAMIC_LINK}
{$ENDIF}

{$IFDEF DYNAMIC_LINK}
var
  _UnloadUserProfile: Pointer;

function UnloadUserProfile;
begin
  GetProcedureAddress(_UnloadUserProfile, userenvlib, 'UnloadUserProfile');
  asm
    mov esp, ebp
    pop ebp
    jmp [_UnloadUserProfile]
  end;
end;
{$ELSE}
function UnloadUserProfile; external userenvlib name 'UnloadUserProfile';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _GetProfilesDirectoryA: Pointer;

function GetProfilesDirectoryA;
begin
  GetProcedureAddress(_GetProfilesDirectoryA, userenvlib, 'GetProfilesDirectoryA');
  asm
    mov esp, ebp
    pop ebp
    jmp [_GetProfilesDirectoryA]
  end;
end;
{$ELSE}
function GetProfilesDirectoryA; external userenvlib name 'GetProfilesDirectoryA';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _GetProfilesDirectoryW: Pointer;

function GetProfilesDirectoryW;
begin
  GetProcedureAddress(_GetProfilesDirectoryW, userenvlib, 'GetProfilesDirectoryW');
  asm
    mov esp, ebp
    pop ebp
    jmp [_GetProfilesDirectoryW]
  end;
end;
{$ELSE}
function GetProfilesDirectoryW; external userenvlib name 'GetProfilesDirectoryW';
{$ENDIF DYNAMIC_LINK}
{$IFDEF UNICODE}

{$IFDEF DYNAMIC_LINK}
var
  _GetProfilesDirectory: Pointer;

function GetProfilesDirectory;
begin
  GetProcedureAddress(_GetProfilesDirectory, userenvlib, 'GetProfilesDirectoryW');
  asm
    mov esp, ebp
    pop ebp
    jmp [_GetProfilesDirectory]
  end;
end;
{$ELSE}
function GetProfilesDirectory; external userenvlib name 'GetProfilesDirectoryW';
{$ENDIF DYNAMIC_LINK}
{$ELSE}

{$IFDEF DYNAMIC_LINK}
var
  _GetProfilesDirectory: Pointer;

function GetProfilesDirectory;
begin
  GetProcedureAddress(_GetProfilesDirectory, userenvlib, 'GetProfilesDirectoryA');
  asm
    mov esp, ebp
    pop ebp
    jmp [_GetProfilesDirectory]
  end;
end;
{$ELSE}
function GetProfilesDirectory; external userenvlib name 'GetProfilesDirectoryA';
{$ENDIF DYNAMIC_LINK}
{$ENDIF}

{$IFDEF DYNAMIC_LINK}
var
  _GetProfileType: Pointer;

function GetProfileType;
begin
  GetProcedureAddress(_GetProfileType, userenvlib, 'GetProfileType');
  asm
    mov esp, ebp
    pop ebp
    jmp [_GetProfileType]
  end;
end;
{$ELSE}
function GetProfileType; external userenvlib name 'GetProfileType';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _DeleteProfileA: Pointer;

function DeleteProfileA;
begin
  GetProcedureAddress(_DeleteProfileA, userenvlib, 'DeleteProfileA');
  asm
    mov esp, ebp
    pop ebp
    jmp [_DeleteProfileA]
  end;
end;
{$ELSE}
function DeleteProfileA; external userenvlib name 'DeleteProfileA';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _DeleteProfileW: Pointer;

function DeleteProfileW;
begin
  GetProcedureAddress(_DeleteProfileW, userenvlib, 'DeleteProfileW');
  asm
    mov esp, ebp
    pop ebp
    jmp [_DeleteProfileW]
  end;
end;
{$ELSE}
function DeleteProfileW; external userenvlib name 'DeleteProfileW';
{$ENDIF DYNAMIC_LINK}
{$IFDEF UNICODE}

{$IFDEF DYNAMIC_LINK}
var
  _DeleteProfile: Pointer;

function DeleteProfile;
begin
  GetProcedureAddress(_DeleteProfile, userenvlib, 'DeleteProfileW');
  asm
    mov esp, ebp
    pop ebp
    jmp [_DeleteProfile]
  end;
end;
{$ELSE}
function DeleteProfile; external userenvlib name 'DeleteProfileW';
{$ENDIF DYNAMIC_LINK}
{$ELSE}

{$IFDEF DYNAMIC_LINK}
var
  _DeleteProfile: Pointer;

function DeleteProfile;
begin
  GetProcedureAddress(_DeleteProfile, userenvlib, 'DeleteProfileA');
  asm
    mov esp, ebp
    pop ebp
    jmp [_DeleteProfile]
  end;
end;
{$ELSE}
function DeleteProfile; external userenvlib name 'DeleteProfileA';
{$ENDIF DYNAMIC_LINK}
{$ENDIF}

{$IFDEF DYNAMIC_LINK}
var
  _GetDefaultUserProfileDirectoryA: Pointer;

function GetDefaultUserProfileDirectoryA;
begin
  GetProcedureAddress(_GetDefaultUserProfileDirectoryA, userenvlib, 'GetDefaultUserProfileDirectoryA');
  asm
    mov esp, ebp
    pop ebp
    jmp [_GetDefaultUserProfileDirectoryA]
  end;
end;
{$ELSE}
function GetDefaultUserProfileDirectoryA; external userenvlib name 'GetDefaultUserProfileDirectoryA';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _GetDefaultUserProfileDirectoryW: Pointer;

function GetDefaultUserProfileDirectoryW;
begin
  GetProcedureAddress(_GetDefaultUserProfileDirectoryW, userenvlib, 'GetDefaultUserProfileDirectoryW');
  asm
    mov esp, ebp
    pop ebp
    jmp [_GetDefaultUserProfileDirectoryW]
  end;
end;
{$ELSE}
function GetDefaultUserProfileDirectoryW; external userenvlib name 'GetDefaultUserProfileDirectoryW';
{$ENDIF DYNAMIC_LINK}
{$IFDEF UNICODE}

{$IFDEF DYNAMIC_LINK}
var
  _GetDefaultUserProfileDirectory: Pointer;

function GetDefaultUserProfileDirectory;
begin
  GetProcedureAddress(_GetDefaultUserProfileDirectory, userenvlib, 'GetDefaultUserProfileDirectoryW');
  asm
    mov esp, ebp
    pop ebp
    jmp [_GetDefaultUserProfileDirectory]
  end;
end;
{$ELSE}
function GetDefaultUserProfileDirectory; external userenvlib name 'GetDefaultUserProfileDirectoryW';
{$ENDIF DYNAMIC_LINK}
{$ELSE}

{$IFDEF DYNAMIC_LINK}
var
  _GetDefaultUserProfileDirectory: Pointer;

function GetDefaultUserProfileDirectory;
begin
  GetProcedureAddress(_GetDefaultUserProfileDirectory, userenvlib, 'GetDefaultUserProfileDirectoryA');
  asm
    mov esp, ebp
    pop ebp
    jmp [_GetDefaultUserProfileDirectory]
  end;
end;
{$ELSE}
function GetDefaultUserProfileDirectory; external userenvlib name 'GetDefaultUserProfileDirectoryA';
{$ENDIF DYNAMIC_LINK}
{$ENDIF}

{$IFDEF DYNAMIC_LINK}
var
  _GetAllUsersProfileDirectoryA: Pointer;

function GetAllUsersProfileDirectoryA;
begin
  GetProcedureAddress(_GetAllUsersProfileDirectoryA, userenvlib, 'GetAllUsersProfileDirectoryA');
  asm
    mov esp, ebp
    pop ebp
    jmp [_GetAllUsersProfileDirectoryA]
  end;
end;
{$ELSE}
function GetAllUsersProfileDirectoryA; external userenvlib name 'GetAllUsersProfileDirectoryA';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _GetAllUsersProfileDirectoryW: Pointer;

function GetAllUsersProfileDirectoryW;
begin
  GetProcedureAddress(_GetAllUsersProfileDirectoryW, userenvlib, 'GetAllUsersProfileDirectoryW');
  asm
    mov esp, ebp
    pop ebp
    jmp [_GetAllUsersProfileDirectoryW]
  end;
end;
{$ELSE}
function GetAllUsersProfileDirectoryW; external userenvlib name 'GetAllUsersProfileDirectoryW';
{$ENDIF DYNAMIC_LINK}
{$IFDEF UNICODE}

{$IFDEF DYNAMIC_LINK}
var
  _GetAllUsersProfileDirectory: Pointer;

function GetAllUsersProfileDirectory;
begin
  GetProcedureAddress(_GetAllUsersProfileDirectory, userenvlib, 'GetAllUsersProfileDirectoryW');
  asm
    mov esp, ebp
    pop ebp
    jmp [_GetAllUsersProfileDirectory]
  end;
end;
{$ELSE}
function GetAllUsersProfileDirectory; external userenvlib name 'GetAllUsersProfileDirectoryW';
{$ENDIF DYNAMIC_LINK}
{$ELSE}

{$IFDEF DYNAMIC_LINK}
var
  _GetAllUsersProfileDirectory: Pointer;

function GetAllUsersProfileDirectory;
begin
  GetProcedureAddress(_GetAllUsersProfileDirectory, userenvlib, 'GetAllUsersProfileDirectoryA');
  asm
    mov esp, ebp
    pop ebp
    jmp [_GetAllUsersProfileDirectory]
  end;
end;
{$ELSE}
function GetAllUsersProfileDirectory; external userenvlib name 'GetAllUsersProfileDirectoryA';
{$ENDIF DYNAMIC_LINK}
{$ENDIF}

{$IFDEF DYNAMIC_LINK}
var
  _GetUserProfileDirectoryA: Pointer;

function GetUserProfileDirectoryA;
begin
  GetProcedureAddress(_GetUserProfileDirectoryA, userenvlib, 'GetUserProfileDirectoryA');
  asm
    mov esp, ebp
    pop ebp
    jmp [_GetUserProfileDirectoryA]
  end;
end;
{$ELSE}
function GetUserProfileDirectoryA; external userenvlib name 'GetUserProfileDirectoryA';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _GetUserProfileDirectoryW: Pointer;

function GetUserProfileDirectoryW;
begin
  GetProcedureAddress(_GetUserProfileDirectoryW, userenvlib, 'GetUserProfileDirectoryW');
  asm
    mov esp, ebp
    pop ebp
    jmp [_GetUserProfileDirectoryW]
  end;
end;
{$ELSE}
function GetUserProfileDirectoryW; external userenvlib name 'GetUserProfileDirectoryW';
{$ENDIF DYNAMIC_LINK}
{$IFDEF UNICODE}

{$IFDEF DYNAMIC_LINK}
var
  _GetUserProfileDirectory: Pointer;

function GetUserProfileDirectory;
begin
  GetProcedureAddress(_GetUserProfileDirectory, userenvlib, 'GetUserProfileDirectoryW');
  asm
    mov esp, ebp
    pop ebp
    jmp [_GetUserProfileDirectory]
  end;
end;
{$ELSE}
function GetUserProfileDirectory; external userenvlib name 'GetUserProfileDirectoryW';
{$ENDIF DYNAMIC_LINK}
{$ELSE}

{$IFDEF DYNAMIC_LINK}
var
  _GetUserProfileDirectory: Pointer;

function GetUserProfileDirectory;
begin
  GetProcedureAddress(_GetUserProfileDirectory, userenvlib, 'GetUserProfileDirectoryA');
  asm
    mov esp, ebp
    pop ebp
    jmp [_GetUserProfileDirectory]
  end;
end;
{$ELSE}
function GetUserProfileDirectory; external userenvlib name 'GetUserProfileDirectoryA';
{$ENDIF DYNAMIC_LINK}
{$ENDIF}

{$IFDEF DYNAMIC_LINK}
var
  _CreateEnvironmentBlock: Pointer;

function CreateEnvironmentBlock;
begin
  GetProcedureAddress(_CreateEnvironmentBlock, userenvlib, 'CreateEnvironmentBlock');
  asm
    mov esp, ebp
    pop ebp
    jmp [_CreateEnvironmentBlock]
  end;
end;
{$ELSE}
function CreateEnvironmentBlock; external userenvlib name 'CreateEnvironmentBlock';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _DestroyEnvironmentBlock: Pointer;

function DestroyEnvironmentBlock;
begin
  GetProcedureAddress(_DestroyEnvironmentBlock, userenvlib, 'DestroyEnvironmentBlock');
  asm
    mov esp, ebp
    pop ebp
    jmp [_DestroyEnvironmentBlock]
  end;
end;
{$ELSE}
function DestroyEnvironmentBlock; external userenvlib name 'DestroyEnvironmentBlock';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _ExpandEnvStringsForUserA: Pointer;

function ExpandEnvironmentStringsForUserA;
begin
  GetProcedureAddress(_ExpandEnvStringsForUserA, userenvlib, 'ExpandEnvironmentStringsForUserA');
  asm
    mov esp, ebp
    pop ebp
    jmp [_ExpandEnvStringsForUserA]
  end;
end;
{$ELSE}
function ExpandEnvironmentStringsForUserA; external userenvlib name 'ExpandEnvironmentStringsForUserA';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _ExpandEnvStringsForUserW: Pointer;

function ExpandEnvironmentStringsForUserW;
begin
  GetProcedureAddress(_ExpandEnvStringsForUserW, userenvlib, 'ExpandEnvironmentStringsForUserW');
  asm
    mov esp, ebp
    pop ebp
    jmp [_ExpandEnvStringsForUserW]
  end;
end;
{$ELSE}
function ExpandEnvironmentStringsForUserW; external userenvlib name 'ExpandEnvironmentStringsForUserW';
{$ENDIF DYNAMIC_LINK}
{$IFDEF UNICODE}

{$IFDEF DYNAMIC_LINK}
var
  _ExpandEnvironmentStringsForUser: Pointer;

function ExpandEnvironmentStringsForUser;
begin
  GetProcedureAddress(_ExpandEnvironmentStringsForUser, userenvlib, 'ExpandEnvironmentStringsForUserW');
  asm
    mov esp, ebp
    pop ebp
    jmp [_ExpandEnvironmentStringsForUser]
  end;
end;
{$ELSE}
function ExpandEnvironmentStringsForUser; external userenvlib name 'ExpandEnvironmentStringsForUserW';
{$ENDIF DYNAMIC_LINK}
{$ELSE}

{$IFDEF DYNAMIC_LINK}
var
  _ExpandEnvironmentStringsForUser: Pointer;

function ExpandEnvironmentStringsForUser;
begin
  GetProcedureAddress(_ExpandEnvironmentStringsForUser, userenvlib, 'ExpandEnvironmentStringsForUserA');
  asm
    mov esp, ebp
    pop ebp
    jmp [_ExpandEnvironmentStringsForUser]
  end;
end;
{$ELSE}
function ExpandEnvironmentStringsForUser; external userenvlib name 'ExpandEnvironmentStringsForUserA';
{$ENDIF DYNAMIC_LINK}
{$ENDIF}

{$IFDEF DYNAMIC_LINK}
var
  _RefreshPolicy: Pointer;

function RefreshPolicy;
begin
  GetProcedureAddress(_RefreshPolicy, userenvlib, 'RefreshPolicy');
  asm
    mov esp, ebp
    pop ebp
    jmp [_RefreshPolicy]
  end;
end;
{$ELSE}
function RefreshPolicy; external userenvlib name 'RefreshPolicy';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _RefreshPolicyEx: Pointer;

function RefreshPolicyEx;
begin
  GetProcedureAddress(_RefreshPolicyEx, userenvlib, 'RefreshPolicyEx');
  asm
    mov esp, ebp
    pop ebp
    jmp [_RefreshPolicyEx]
  end;
end;
{$ELSE}
function RefreshPolicyEx; external userenvlib name 'RefreshPolicyEx';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _EnterCriticalPolicySection: Pointer;

function EnterCriticalPolicySection;
begin
  GetProcedureAddress(_EnterCriticalPolicySection, userenvlib, 'EnterCriticalPolicySection');
  asm
    mov esp, ebp
    pop ebp
    jmp [_EnterCriticalPolicySection]
  end;
end;
{$ELSE}
function EnterCriticalPolicySection; external userenvlib name 'EnterCriticalPolicySection';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _LeaveCriticalPolicySection: Pointer;

function LeaveCriticalPolicySection;
begin
  GetProcedureAddress(_LeaveCriticalPolicySection, userenvlib, 'LeaveCriticalPolicySection');
  asm
    mov esp, ebp
    pop ebp
    jmp [_LeaveCriticalPolicySection]
  end;
end;
{$ELSE}
function LeaveCriticalPolicySection; external userenvlib name 'LeaveCriticalPolicySection';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _RegisterGPNotification: Pointer;

function RegisterGPNotification;
begin
  GetProcedureAddress(_RegisterGPNotification, userenvlib, 'RegisterGPNotification');
  asm
    mov esp, ebp
    pop ebp
    jmp [_RegisterGPNotification]
  end;
end;
{$ELSE}
function RegisterGPNotification; external userenvlib name 'RegisterGPNotification';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _UnregisterGPNotification: Pointer;

function UnregisterGPNotification;
begin
  GetProcedureAddress(_UnregisterGPNotification, userenvlib, 'UnregisterGPNotification');
  asm
    mov esp, ebp
    pop ebp
    jmp [_UnregisterGPNotification]
  end;
end;
{$ELSE}
function UnregisterGPNotification; external userenvlib name 'UnregisterGPNotification';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _GetGPOListA: Pointer;

function GetGPOListA;
begin
  GetProcedureAddress(_GetGPOListA, userenvlib, 'GetGPOListA');
  asm
    mov esp, ebp
    pop ebp
    jmp [_GetGPOListA]
  end;
end;
{$ELSE}
function GetGPOListA; external userenvlib name 'GetGPOListA';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _GetGPOListW: Pointer;

function GetGPOListW;
begin
  GetProcedureAddress(_GetGPOListW, userenvlib, 'GetGPOListW');
  asm
    mov esp, ebp
    pop ebp
    jmp [_GetGPOListW]
  end;
end;
{$ELSE}
function GetGPOListW; external userenvlib name 'GetGPOListW';
{$ENDIF DYNAMIC_LINK}
{$IFDEF UNICODE}

{$IFDEF DYNAMIC_LINK}
var
  _GetGPOList: Pointer;

function GetGPOList;
begin
  GetProcedureAddress(_GetGPOList, userenvlib, 'GetGPOListW');
  asm
    mov esp, ebp
    pop ebp
    jmp [_GetGPOList]
  end;
end;
{$ELSE}
function GetGPOList; external userenvlib name 'GetGPOListW';
{$ENDIF DYNAMIC_LINK}
{$ELSE}

{$IFDEF DYNAMIC_LINK}
var
  _GetGPOList: Pointer;

function GetGPOList;
begin
  GetProcedureAddress(_GetGPOList, userenvlib, 'GetGPOListA');
  asm
    mov esp, ebp
    pop ebp
    jmp [_GetGPOList]
  end;
end;
{$ELSE}
function GetGPOList; external userenvlib name 'GetGPOListA';
{$ENDIF DYNAMIC_LINK}
{$ENDIF}

{$IFDEF DYNAMIC_LINK}
var
  _FreeGPOListA: Pointer;

function FreeGPOListA;
begin
  GetProcedureAddress(_FreeGPOListA, userenvlib, 'FreeGPOListA');
  asm
    mov esp, ebp
    pop ebp
    jmp [_FreeGPOListA]
  end;
end;
{$ELSE}
function FreeGPOListA; external userenvlib name 'FreeGPOListA';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _FreeGPOListW: Pointer;

function FreeGPOListW;
begin
  GetProcedureAddress(_FreeGPOListW, userenvlib, 'FreeGPOListW');
  asm
    mov esp, ebp
    pop ebp
    jmp [_FreeGPOListW]
  end;
end;
{$ELSE}
function FreeGPOListW; external userenvlib name 'FreeGPOListW';
{$ENDIF DYNAMIC_LINK}
{$IFDEF UNICODE}

{$IFDEF DYNAMIC_LINK}
var
  _FreeGPOList: Pointer;

function FreeGPOList;
begin
  GetProcedureAddress(_FreeGPOList, userenvlib, 'FreeGPOListW');
  asm
    mov esp, ebp
    pop ebp
    jmp [_FreeGPOList]
  end;
end;
{$ELSE}
function FreeGPOList; external userenvlib name 'FreeGPOListW';
{$ENDIF DYNAMIC_LINK}
{$ELSE}

{$IFDEF DYNAMIC_LINK}
var
  _FreeGPOList: Pointer;

function FreeGPOList;
begin
  GetProcedureAddress(_FreeGPOList, userenvlib, 'FreeGPOListA');
  asm
    mov esp, ebp
    pop ebp
    jmp [_FreeGPOList]
  end;
end;
{$ELSE}
function FreeGPOList; external userenvlib name 'FreeGPOListA';
{$ENDIF DYNAMIC_LINK}
{$ENDIF}

{$IFDEF DYNAMIC_LINK}
var
  _GetAppliedGPOListA: Pointer;

function GetAppliedGPOListA;
begin
  GetProcedureAddress(_GetAppliedGPOListA, userenvlib, 'GetAppliedGPOListA');
  asm
    mov esp, ebp
    pop ebp
    jmp [_GetAppliedGPOListA]
  end;
end;
{$ELSE}
function GetAppliedGPOListA; external userenvlib name 'GetAppliedGPOListA';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _GetAppliedGPOListW: Pointer;

function GetAppliedGPOListW;
begin
  GetProcedureAddress(_GetAppliedGPOListW, userenvlib, 'GetAppliedGPOListW');
  asm
    mov esp, ebp
    pop ebp
    jmp [_GetAppliedGPOListW]
  end;
end;
{$ELSE}
function GetAppliedGPOListW; external userenvlib name 'GetAppliedGPOListW';
{$ENDIF DYNAMIC_LINK}
{$IFDEF UNICODE}

{$IFDEF DYNAMIC_LINK}
var
  _GetAppliedGPOList: Pointer;

function GetAppliedGPOList;
begin
  GetProcedureAddress(_GetAppliedGPOList, userenvlib, 'GetAppliedGPOListW');
  asm
    mov esp, ebp
    pop ebp
    jmp [_GetAppliedGPOList]
  end;
end;
{$ELSE}
function GetAppliedGPOList; external userenvlib name 'GetAppliedGPOListW';
{$ENDIF DYNAMIC_LINK}
{$ELSE}

{$IFDEF DYNAMIC_LINK}
var
  _GetAppliedGPOList: Pointer;

function GetAppliedGPOList;
begin
  GetProcedureAddress(_GetAppliedGPOList, userenvlib, 'GetAppliedGPOListA');
  asm
    mov esp, ebp
    pop ebp
    jmp [_GetAppliedGPOList]
  end;
end;
{$ELSE}
function GetAppliedGPOList; external userenvlib name 'GetAppliedGPOListA';
{$ENDIF DYNAMIC_LINK}
{$ENDIF}

{$IFDEF DYNAMIC_LINK}
var
  _ProcessGroupPolicyCompleted: Pointer;

function ProcessGroupPolicyCompleted;
begin
  GetProcedureAddress(_ProcessGroupPolicyCompleted, userenvlib, 'ProcessGroupPolicyCompleted');
  asm
    mov esp, ebp
    pop ebp
    jmp [_ProcessGroupPolicyCompleted]
  end;
end;
{$ELSE}
function ProcessGroupPolicyCompleted; external userenvlib name 'ProcessGroupPolicyCompleted';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _ProcessGroupPolicyCompletedEx: Pointer;

function ProcessGroupPolicyCompletedEx;
begin
  GetProcedureAddress(_ProcessGroupPolicyCompletedEx, userenvlib, 'ProcessGroupPolicyCompletedEx');
  asm
    mov esp, ebp
    pop ebp
    jmp [_ProcessGroupPolicyCompletedEx]
  end;
end;
{$ELSE}
function ProcessGroupPolicyCompletedEx; external userenvlib name 'ProcessGroupPolicyCompletedEx';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _RsopAccessCheckByType: Pointer;

function RsopAccessCheckByType;
begin
  GetProcedureAddress(_RsopAccessCheckByType, userenvlib, 'RsopAccessCheckByType');
  asm
    mov esp, ebp
    pop ebp
    jmp [_RsopAccessCheckByType]
  end;
end;
{$ELSE}
function RsopAccessCheckByType; external userenvlib name 'RsopAccessCheckByType';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _RsopFileAccessCheck: Pointer;

function RsopFileAccessCheck;
begin
  GetProcedureAddress(_RsopFileAccessCheck, userenvlib, 'RsopFileAccessCheck');
  asm
    mov esp, ebp
    pop ebp
    jmp [_RsopFileAccessCheck]
  end;
end;
{$ELSE}
function RsopFileAccessCheck; external userenvlib name 'RsopFileAccessCheck';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _RsopSetPolicySettingStatus: Pointer;

function RsopSetPolicySettingStatus;
begin
  GetProcedureAddress(_RsopSetPolicySettingStatus, userenvlib, 'RsopSetPolicySettingStatus');
  asm
    mov esp, ebp
    pop ebp
    jmp [_RsopSetPolicySettingStatus]
  end;
end;
{$ELSE}
function RsopSetPolicySettingStatus; external userenvlib name 'RsopSetPolicySettingStatus';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _RsopResetPolicySettingStatus: Pointer;

function RsopResetPolicySettingStatus;
begin
  GetProcedureAddress(_RsopResetPolicySettingStatus, userenvlib, 'RsopResetPolicySettingStatus');
  asm
    mov esp, ebp
    pop ebp
    jmp [_RsopResetPolicySettingStatus]
  end;
end;
{$ELSE}
function RsopResetPolicySettingStatus; external userenvlib name 'RsopResetPolicySettingStatus';
{$ENDIF DYNAMIC_LINK}

end.

