{******************************************************************************}
{                                                       	               }
{ BlueTooth API interface Unit for Object Pascal                               }
{                                                       	               }
{ Portions created by Microsoft are Copyright (C) 1995-2001 Microsoft          }
{ Corporation. All Rights Reserved.                                            }
{ 								               }
{ Portions created by Marcel van Brakel are Copyright (C) 1999-2001            }
{ Marcel van Brakel. All Rights Reserved.                                      }
{ 								               }
{ Contributors: John Penman       			                       }
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

// todo externalsym/dynamiclinking

unit JwaBluetoothAPIs;

{$WEAKPACKAGEUNIT}

{$HPPEMIT ''}
{$HPPEMIT '#include "bluetoothapis.h"'}
{$HPPEMIT ''}

{$I WINDEFINES.INC}

interface

uses
  JwaWinType, JwaWinBase, JwaBthSdpDef;

const
  BLUETOOTH_MAX_NAME_SIZE            = (248);
  BLUETOOTH_MAX_PASSKEY_SIZE         = (16);
  BLUETOOTH_MAX_PASSKEY_BUFFER_SIZE  = (BLUETOOTH_MAX_PASSKEY_SIZE + 1);

// ***************************************************************************
//
//  Bluetooth Address
//
// ***************************************************************************

type
  BTH_ADDR = Int64;

  _BLUETOOTH_ADDRESS = record
    case Integer of
      0: (ullLong: BTH_ADDR);       //  easier to compare again BLUETOOTH_NULL_ADDRESS
      1: (rgBytes: array [0..5] of Byte);   //  easier to format when broken out
  end;
  BLUETOOTH_ADDRESS = _BLUETOOTH_ADDRESS;
  TBlueToothAddress = BLUETOOTH_ADDRESS;
  PBlueToothAddress = ^BLUETOOTH_ADDRESS;

const
  BLUETOOTH_NULL_ADDRESS: TBlueToothAddress = (ullLong: 0;);

// ***************************************************************************
//
//  Radio Enumeration
//
//  Description:
//      This group of APIs enumerates the installed Bluetooth radios.
//
//  Sample Usage:
//      HANDLE hRadio;
//      BLUETOOTH_FIND_RADIO_PARAMS btfrp = { sizeof(btfrp) };
//
//      HBLUETOOTH_RADIO_FIND hFind = BluetoothFindFirstRadio( &btfrp, &hRadio );
//      if ( NULL != hFind )
//      {
//          do
//          {
//              //
//              //  TODO: Do something with the radio handle.
//              //
//
//              CloseHandle( hRadio );
//
//          } while( BluetoothFindNextRadio( hFind, &hRadio ) );
//
//          BluetoothFindRadioClose( hFind );
//      }
//
// ***************************************************************************

type
  _BLUETOOTH_FIND_RADIO_PARAMS = record
    dwSize: DWORD;             //  IN  sizeof this structure
  end;
  BLUETOOTH_FIND_RADIO_PARAMS = _BLUETOOTH_FIND_RADIO_PARAMS;
  TBlueToothFindRadioParams = BLUETOOTH_FIND_RADIO_PARAMS;
  PBlueToothFindRadioParams = ^BLUETOOTH_FIND_RADIO_PARAMS;  

  HBLUETOOTH_RADIO_FIND = THandle;

//
//  Description:
//      Begins the enumeration of local Bluetooth radios.
//
//  Parameters:
//      pbtfrp
//          A pointer to a BLUETOOTH_FIND_RADIO_PARAMS structure. The dwSize 
//          member of this structure must match the sizeof the of the structure.
//
//      phRadio
//          A pointer where the first radio HANDLE enumerated will be returned.
//
//  Return Values:
//      NULL
//          Error opening radios or no devices found. Use GetLastError() for
//          more info.
//
//          ERROR_INVALID_PARAMETER
//              pbtfrp parameter is NULL.
//
//          ERROR_REVISION_MISMATCH
//              The pbtfrp structure is not the right length.
//
//          ERROR_OUTOFMEMORY
//              Out of memory.
//
//          other Win32 errors.
//
//      any other
//          Success. The return handle is valid and phRadio points to a valid handle.
//

function BluetoothFindFirstRadio(const pbtfrp: BLUETOOTH_FIND_RADIO_PARAMS; var phRadio: THandle): HBLUETOOTH_RADIO_FIND; stdcall;

//
//  Description:
//      Finds the next installed Bluetooth radio.
//
//  Parameters:
//      hFind
//          The handle returned by BluetoothFindFirstRadio().
//
//      phRadio
//          A pointer where the next radio HANDLE enumerated will be returned.
//
//  Return Values:
//      TRUE
//          Next device succesfully found. pHandleOut points to valid handle.
//
//      FALSE
//          No device found. pHandleOut points to an invalid handle. Call
//          GetLastError() for more details.
//
//          ERROR_INVALID_HANDLE
//              The handle is NULL.
//
//          ERROR_NO_MORE_ITEMS
//              No more radios found.
//
//          ERROR_OUTOFMEMORY
//              Out of memory.
//
//          other Win32 errors
//

function BluetoothFindNextRadio(hFind: HBLUETOOTH_RADIO_FIND; var phRadio: THandle): BOOL; stdcall;

//
//  Description:
//      Closes the enumeration handle.
//
//  Parameters
//      hFind
//          The handle returned by BluetoothFindFirstRadio().
//
//  Return Values:
//      TRUE
//          Handle succesfully closed.
//
//      FALSE
//          Failure. Check GetLastError() for details.
//
//          ERROR_INVALID_HANDLE
//              The handle is NULL.
//

function BluetoothFindRadioClose(hFind: HBLUETOOTH_RADIO_FIND): BOOL; stdcall;

// ***************************************************************************
//
//  Radio Information
//
// ***************************************************************************

type
  _BLUETOOTH_RADIO_INFO = record
    dwSize: DWORD;                               // Size, in bytes, of this entire data structure
    address: BLUETOOTH_ADDRESS;                  // Address of the local radio
    szName: array [0..BLUETOOTH_MAX_NAME_SIZE - 1] of WideChar;    // Name of the local radio
    ulClassofDevice: ULONG;                      // Class of device for the local radio
    lmpSubversion: Word;                       // lmpSubversion, manufacturer specifc.
    manufacturer: Word;                        // Manufacturer of the radio, BTH_MFG_Xxx value.  For the most up to date
                                                // list, goto the Bluetooth specification website and get the Bluetooth
                                                // assigned numbers document.
  end;
  BLUETOOTH_RADIO_INFO = _BLUETOOTH_RADIO_INFO;
  PBLUETOOTH_RADIO_INFO = ^BLUETOOTH_RADIO_INFO;
  TBlueToothRadioFind = BLUETOOTH_RADIO_INFO;
  PBlueToothRadioFind = PBLUETOOTH_RADIO_INFO;

//
//  Description:
//      Retrieves the information about the radio represented by the handle.
//
//  Parameters:
//      hRadio
//          Handle to a local radio retrieved through BluetoothFindFirstRadio()
//          et al or SetupDiEnumerateDeviceInterfaces()
//
//      pRadioInfo
//          Radio information to be filled in. The dwSize member must match the 
//          size of the structure.
//
//  Return Values:
//      ERROR_SUCCESS
//          The information was retrieved successfully.
//
//      ERROR_INVALID_PARAMETER
//          pRadioInfo or hRadio is NULL.
//
//      ERROR_REVISION_MISMATCH
//          pRadioInfo->dwSize is invalid.
//
//      other Win32 error codes.
//

function BluetoothGetRadioInfo(hRadio: THandle; var pRadioInfo: BLUETOOTH_RADIO_INFO): DWORD; stdcall;

// ***************************************************************************
//
//  Device Information Stuctures
//
// ***************************************************************************

type
  _BLUETOOTH_DEVICE_INFO = record
    dwSize: DWORD;                             //  size, in bytes, of this structure - must be the sizeof(BLUETOOTH_DEVICE_INFO)
    Address: BLUETOOTH_ADDRESS;                  //  Bluetooth address
    ulClassofDevice: ULONG;                    //  Bluetooth "Class of Device"
    fConnected: BOOL;                         //  Device connected/in use
    fRemembered: BOOL;                        //  Device remembered
    fAuthenticated: BOOL;                     //  Device authenticated/paired/bonded
    stLastSeen: SYSTEMTIME;                     //  Last time the device was seen
    stLastUsed: SYSTEMTIME;                     //  Last time the device was used for other than RNR, inquiry, or SDP
    szName: array [0..BLUETOOTH_MAX_NAME_SIZE - 1] of WideChar;  //  Name of the device
  end;
  BLUETOOTH_DEVICE_INFO = _BLUETOOTH_DEVICE_INFO;
  PBLUETOOTH_DEVICE_INFO = BLUETOOTH_DEVICE_INFO;
  TBlueToothDeviceInfo = BLUETOOTH_DEVICE_INFO;
  PBlueToothDeviceInfo = PBLUETOOTH_DEVICE_INFO;

// ***************************************************************************
//
//  Device Enumeration
//
//  Description:
//      Enumerates the Bluetooth devices. The types of returned device depends
//      on the flags set in the BLUETOOTH_DEVICE_SEARCH_PARAMS (see structure
//      definition for details).
//
//  Sample Usage:
//      HBLUETOOTH_DEVICE_FIND hFind;
//      BLUETOOTH_DEVICE_SEARCH_PARAMS btsp = { sizeof(btsp) };
//      BLUETOOTH_DEVICE_INFO btdi = { sizeof(btdi) };
//
//      btsp.fReturnAuthenticated = TRUE;
//      btsp.fReturnRemembered    = TRUE;
//
//      hFind = BluetoothFindFirstDevice( &btsp, &btdi );
//      if ( NULL != hFind )
//      {
//          do
//          {
//              //
//              //  TODO:   Do something useful with the device info.
//              //
//
//          } while( BluetoothFindNextDevice( hFind, &btdi ) );
//
//          BluetoothFindDeviceClose( hFind );
//      }
//
// ***************************************************************************

type
  _BLUETOOTH_DEVICE_SEARCH_PARAMS = record
    dwSize: DWORD;                 //  IN  sizeof this structure

    fReturnAuthenticated: BOOL;   //  IN  return authenticated devices
    fReturnRemembered: BOOL;      //  IN  return remembered devices
    fReturnUnknown: BOOL;         //  IN  return unknown devices
    fReturnConnected: BOOL;       //  IN  return connected devices

    fIssueInquiry: BOOL;          //  IN  issue a new inquiry
    cTimeoutMultiplier: UCHAR;     //  IN  timeout for the inquiry

    hRadio: THandle;                 //  IN  handle to radio to enumerate - NULL == all radios will be searched
  end;
  BLUETOOTH_DEVICE_SEARCH_PARAMS = _BLUETOOTH_DEVICE_SEARCH_PARAMS;
  TBlueToothDeviceSearchParams = BLUETOOTH_DEVICE_SEARCH_PARAMS;

  HBLUETOOTH_DEVICE_FIND = THandle;

//
//  Description:
//      Begins the enumeration of Bluetooth devices.
//
//  Parameters:
//      pbtsp
//          A pointer to a BLUETOOTH_DEVICE_SEARCH_PARAMS structure. This
//          structure contains the flags and inputs used to conduct the search.
//          See BLUETOOTH_DEVICE_SEARCH_PARAMS for details.
//
//      pbtdi
//          A pointer to a BLUETOOTH_DEVICE_INFO structure to return information
//          about the first Bluetooth device found. Note that the dwSize member
//          of the structure must be the sizeof(BLUETOOTH_DEVICE_INFO) before
//          calling because the APIs hast to know the size of the buffer being
//          past in. The dwSize member must also match the exact 
//          sizeof(BLUETOOTH_DEVICE_INFO) or the call will fail.
//
//  Return Values:
//      NULL
//          Error opening radios or not devices found. Use GetLastError for more info.
//
//          ERROR_INVALID_PARAMETER
//              pbtsp parameter or pbtdi parameter is NULL.
//
//          ERROR_REVISION_MISMATCH
//              The pbtfrp structure is not the right length.
//
//          other Win32 errors
//
//      any other value
//          Success. The return handle is valid and pbtdi points to valid data.
//

function BluetoothFindFirstDevice(const pbtsp: BLUETOOTH_DEVICE_SEARCH_PARAMS; var pbtdi: BLUETOOTH_DEVICE_INFO): HBLUETOOTH_DEVICE_FIND; stdcall;

//
//  Description:
//      Finds the next Bluetooth device in the enumeration.
//
//  Parameters:
//      hFind
//          The handle returned from BluetoothFindFirstDevice().
//
//      pbtdi
//          A pointer to a BLUETOOTH_DEVICE_INFO structure to return information
//          about the first Bluetooth device found. Note that the dwSize member
//          of the structure must be the sizeof(BLUETOOTH_DEVICE_INFO) before
//          calling because the APIs hast to know the size of the buffer being
//          past in. The dwSize member must also match the exact
//          sizeof(BLUETOOTH_DEVICE_INFO) or the call will fail.
//
//  Return Values:
//      TRUE
//          Next device succesfully found. pHandleOut points to valid handle.
//
//      FALSE
//          No device found. pHandleOut points to an invalid handle. Call
//          GetLastError() for more details.
//
//          ERROR_INVALID_HANDLE
//              The handle is NULL.
//
//          ERROR_NO_MORE_ITEMS
//              No more radios found.
//
//          ERROR_OUTOFMEMORY
//              Out of memory.
//
//          other Win32 errors
//

function BluetoothFindNextDevice(hFind: HBLUETOOTH_DEVICE_FIND; var pbtdi: BLUETOOTH_DEVICE_INFO): BOOL; stdcall;

//
//  Description:
//      Closes the enumeration handle.
//
//  Parameters:
//      hFind
//          The handle returned from BluetoothFindFirstDevice().
//
//  Return Values:
//      TRUE
//          Handle succesfully closed.
//
//      FALSE
//          Failure. Check GetLastError() for details.
//
//          ERROR_INVALID_HANDLE
//              The handle is NULL.
//

function BluetoothFindDeviceClose(hFind: HBLUETOOTH_DEVICE_FIND): BOOL; stdcall;

//
//  Description:
//      Retrieves information about a remote device.
//
//      Fill in the dwSize and the Address members of the pbtdi structure
//      being passed in. On success, the rest of the members will be filled
//      out with the information that the system knows.
//
//  Parameters:
//      hRadio
//          Handle to a local radio retrieved through BluetoothFindFirstRadio()
//          et al or SetupDiEnumerateDeviceInterfaces()
//
//      pbtdi
//          A pointer to a BLUETOOTH_DEVICE_INFO structure to return information
//          about the first Bluetooth device found. The dwSize member of the
//          structure must be the sizeof the structure in bytes. The Address
//          member must be filled out with the Bluetooth address of the remote
//          device.
//
//  Return Values:
//      ERROR_SUCCESS
//          Success. Information returned.
//
//      ERROR_REVISION_MISMATCH
//          The size of the BLUETOOTH_DEVICE_INFO isn't compatible. Check
//          the dwSize member of the BLUETOOTH_DEVICE_INFO structure you
//          passed in.
//
//      ERROR_NOT_FOUND
//          The radio is not known by the system or the Address field of
//          the BLUETOOTH_DEVICE_INFO structure is all zeros.
//
//      ERROR_INVALID_PARAMETER
//          pbtdi is NULL.
//
//      other error codes
//

function BluetoothGetDeviceInfo(hRadio: THandle; var pbtdi: BLUETOOTH_DEVICE_INFO): DWORD; stdcall;

//
//  Description:
//      Updates the computer local cache about the device.
//
//  Parameters:
//      pbtdi
//          A pointer to the BLUETOOTH_DEVICE_INFO structure to be updated.
//          The following members must be valid:
//              dwSize
//                  Must match the size of the structure.
//              Address
//                  Must be a previously found radio address.
//              szName
//                  New name to be stored.
//
//  Return Values:
//      ERROR_SUCCESS
//          The device information was updated successfully.
//
//      ERROR_INVALID_PARAMETER
//          pbtdi is NULL.
//
//      ERROR_REVISION_MISMATCH
//          pbtdi->dwSize is invalid.
//
//      other Win32 error codes.
//

function BluetoothUpdateDeviceRecord(var pbtdi: BLUETOOTH_DEVICE_INFO): DWORD; stdcall;

//
//  Description:
//      Delete the authentication (aka "bond") between the computer and the
//      device. Also purges any cached information about the device.
//
//  Return Values:
//      ERROR_SUCCESS
//          The device was removed successfully.
//
//      ERROR_NOT_FOUND
//          The device was not found. If no Bluetooth radio is installed,
//          the devices could not be enumerated or removed.
//

function BluetoothRemoveDevice(var pAddress: BLUETOOTH_ADDRESS): DWORD; stdcall;

// ***************************************************************************
//
//  Device Picker Dialog
//
//  Description:
//      Invokes a common dialog for selecting Bluetooth devices. The list
//      of devices displayed to the user is determined by the flags and
//      settings the caller specifies in the BLUETOOTH_SELECT_DEVICE_PARAMS
//      (see structure definition for more details).
//
//      If BluetoothSelectDevices() returns TRUE, the caller must call
//      BluetoothSelectDevicesFree() or memory will be leaked within the
//      process.
//
//  Sample Usage:
//
//      BLUETOOTH_SELECT_DEVICE_PARAMS btsdp = { sizeof(btsdp) };
//
//      btsdp.hwndParent = hDlg;
//      btsdp.fShowUnknown = TRUE;
//      btsdp.fAddNewDeviceWizard = TRUE;
//
//      BOOL b = BluetoothSelectDevices( &btsdp );
//      if ( b )
//      {
//          BLUETOOTH_DEVICE_INFO * pbtdi = btsdp.pDevices;
//          for ( ULONG cDevice = 0; cDevice < btsdp.cNumDevices; cDevice ++ )
//          {
//              if ( pbtdi->fAuthenticated || pbtdi->fRemembered )
//              {
//                  //
//                  //  TODO:   Do something usefull with the device info
//                  //
//              }
//
//              pbtdi = (BLUETOOTH_DEVICE_INFO *) ((LPBYTE)pbtdi + pbtdi->dwSize);
//          }
//
//          BluetoothSelectDevicesFree( &btsdp );
//      }
//
// ***************************************************************************

type
  _BLUETOOTH_COD_PAIRS = record
    ulCODMask: ULONG;                          //  ClassOfDevice mask to compare
    pcszDescription: LPWSTR;                    //  Descriptive string of mask
  end;
  BLUETOOTH_COD_PAIRS = _BLUETOOTH_COD_PAIRS;
  TBlueToothCodPairs = BLUETOOTH_COD_PAIRS;
  PBlueToothCodPairs = ^BLUETOOTH_COD_PAIRS;

  PFN_DEVICE_CALLBACK = function (pvParam: Pointer; pDevice: PBLUETOOTH_DEVICE_INFO): BOOL; stdcall;

  _BLUETOOTH_SELECT_DEVICE_PARAMS = record
    dwSize: DWORD;                             //  IN  sizeof this structure

    cNumOfClasses: ULONG;                      //  IN  Number in prgClassOfDevice - if ZERO search for all devices
    prgClassOfDevices: PBlueToothCodPairs;    //  IN  Array of CODs to find.

    pszInfo: LPWSTR;                            //  IN  If not NULL, sets the "information" text

    hwndParent: HWND;                         //  IN  parent window - NULL == no parent

    fForceAuthentication: BOOL;               //  IN  If TRUE, authenication will be forced before returning
    fShowAuthenticated: BOOL;                 //  IN  If TRUE, authenticated devices will be shown in the picker
    fShowRemembered: BOOL;                    //  IN  If TRUE, remembered devices will be shown in the picker
    fShowUnknown: BOOL;                       //  IN  If TRUE, unknown devices that are not authenticated or "remember" will be shown.

    fAddNewDeviceWizard: BOOL;                //  IN  If TRUE, invokes the add new device wizard.
    fSkipServicesPage: BOOL;                  //  IN  If TRUE, skips the "Services" page in the wizard.

    pfnDeviceCallback: PFN_DEVICE_CALLBACK;      //  IN  If non-NULL, a callback that will be called for each device. If the
                                                //      the callback returns TRUE, the item will be added. If the callback is
                                                //      is FALSE, the item will not be shown.
    pvParam: Pointer;                            //  IN  Parameter to be passed to pfnDeviceCallback as the pvParam.

    cNumDevices: DWORD;                        //  IN  number calles wants - ZERO == no limit.
                                                //  OUT the number of devices returned.

    pDevices: PBLUETOOTH_DEVICE_INFO;           //  OUT pointer to an array for BLUETOOTH_DEVICE_INFOs.
                                                //      call BluetoothSelectDevicesFree() to free
  end;
  BLUETOOTH_SELECT_DEVICE_PARAMS = _BLUETOOTH_SELECT_DEVICE_PARAMS;
  TBlueToothSelectDeviceParams = BLUETOOTH_SELECT_DEVICE_PARAMS;
  PBlueToothSelectDeviceParams = ^BLUETOOTH_SELECT_DEVICE_PARAMS;

//
//  Description:
//      (See header above)
//
//  Return Values:
//      TRUE
//          User selected a device. pbtsdp->pDevices points to valid data.
//          Caller should check the fAuthenticated && fRemembered flags to
//          determine which devices we successfuly authenticated or valid
//          selections by the user.
//
//          Use BluetoothSelectDevicesFree() to free the nessecary data
//          such as pDevices only if this function returns TRUE.
//
//      FALSE
//          No valid data returned. Call GetLastError() for possible details
//          of the failure. If GLE() is:
//
//          ERROR_CANCELLED
//              The user cancelled  the request.
//
//          ERROR_INVALID_PARAMETER
//              The pbtsdp is NULL.
//
//          ERROR_REVISION_MISMATCH
//              The structure passed in as pbtsdp is of an unknown size.
//
//          other WIN32 errors
//

function BluetoothSelectDevices(pbtsdp: PBlueToothSelectDeviceParams): BOOL; stdcall;

//
//  Description:
//      This function should only be called if BluetoothSelectDevices() returns
//      TRUE. This function will free any memory and resource returned by the
//      BluetoothSelectDevices() in the BLUETOOTH_SELECT_DEVICE_PARAMS
//      structure.
//
//  Return Values:
//      TRUE
//          Success.
//
//      FALSE
//          Nothing to free.
//

function BluetoothSelectDevicesFree(pbtsdp: PBlueToothSelectDeviceParams): BOOL; stdcall;

// ***************************************************************************
//
//  Device Property Sheet
//
// ***************************************************************************

//
//  Description:
//      Invokes the CPLs device info property sheet.
//
//  Parameters:
//      hwndParent
//          HWND to parent the property sheet.
//
//      pbtdi
//          A pointer to a BLUETOOTH_DEVICE_INFO structure of the device
//          to be displayed.
//
//  Return Values:
//      TRUE
//          The property page was successfully displayed.
//
//      FALSE
//          Failure. The property page was not displayed. Check GetLastError
//          for more details.
//

function BluetoothDisplayDeviceProperties(hwndParent: HWND; pbtdi: PBLUETOOTH_DEVICE_INFO): BOOL; stdcall;


// ***************************************************************************
//
//  Radio Authentication
//
// ***************************************************************************

//
//  Description:
//      Sends an authentication request to a remote device. 
//
//      There are two modes of operation. "Wizard mode" and "Blind mode."
//
//      "Wizard mode" is invoked when the pszPasskey is NULL. This will cause
//      the "Bluetooth Connection Wizard" to be invoked. The user will be
//      prompted to enter a passkey during the wizard after which the
//      authentication request will be sent. The user will see the success
//      or failure of the authentication attempt. The user will also be
//      given the oppurtunity to try to fix a failed authentication.
//
//      "Blind mode" is invoked when the pszPasskey is non-NULL. This will
//      cause the computer to send a authentication request to the remote
//      device. No UI is ever displayed. The Bluetooth status code will be
//      mapped to a Win32 Error code.
//
//  Parameters:
//
//      hwndParent
//          The window to parent the authentication wizard. If NULL, the 
//          wizard will be parented off the desktop.
//
//      hRadio
//          A valid local radio handle or NULL. If NULL, then all radios will
//          be tired. If any of the radios succeed, then the call will
//          succeed.
//
//      pbtdi
//          BLUETOOTH_DEVICE_INFO record of the device to be authenticated.
//
//      pszPasskey
//          PIN to be used to authenticate the device.  If NULL, then UI is
//          displayed and the user steps through the authentication process.
//          If not NULL, no UI is shown.  The passkey is NOT NULL terminated.
//
//      ulPasskeyLength
//          Length of szPassKey in bytes. The length must be less than or 
//          equal to BLUETOOTH_MAX_PASSKEY_SIZE * sizeof(WCHAR).
//
//  Return Values:
//
//      ERROR_SUCCESS
//          Success.
//
//      ERROR_CANCELLED
//          User aborted the operation.
//
//      ERROR_INVALID_PARAMETER
//          The device structure in pbtdi is invalid.
//
//      ERROR_NO_MORE_ITEMS
//          The device in pbtdi is already been marked as authenticated.
//
//      other WIN32 error
//          Failure. Return value is the error code.
//
//      For "Blind mode," here is the current mapping of Bluetooth status
//      code to Win32 error codes:
//
//          { BTH_ERROR_SUCCESS,                ERROR_SUCCESS },
//          { BTH_ERROR_NO_CONNECTION,          ERROR_DEVICE_NOT_CONNECTED },
//          { BTH_ERROR_PAGE_TIMEOUT,           WAIT_TIMEOUT },
//          { BTH_ERROR_HARDWARE_FAILURE,       ERROR_GEN_FAILURE },
//          { BTH_ERROR_AUTHENTICATION_FAILURE, ERROR_NOT_AUTHENTICATED },
//          { BTH_ERROR_MEMORY_FULL,            ERROR_NOT_ENOUGH_MEMORY },
//          { BTH_ERROR_CONNECTION_TIMEOUT,     WAIT_TIMEOUT },
//          { BTH_ERROR_LMP_RESPONSE_TIMEOUT,   WAIT_TIMEOUT },
//          { BTH_ERROR_MAX_NUMBER_OF_CONNECTIONS, ERROR_REQ_NOT_ACCEP },
//          { BTH_ERROR_PAIRING_NOT_ALLOWED,    ERROR_ACCESS_DENIED },
//          { BTH_ERROR_UNSPECIFIED_ERROR,      ERROR_NOT_READY },
//          { BTH_ERROR_LOCAL_HOST_TERMINATED_CONNECTION, ERROR_VC_DISCONNECTED },
//

function BluetoothAuthenticateDevice(
    hwndParent: HWND;
    hRadio: THandle;
    pbtbi: PBLUETOOTH_DEVICE_INFO;
    pszPasskey: PWideChar;
    ulPasskeyLength: ULONG): DWORD; stdcall;

//
//  Description:
//      Allows the caller to prompt for multiple devices to be authenticated
//      within a single instance of the "Bluetooth Connection Wizard."
//
//  Parameters:
//
//      hwndParent
//          The window to parent the authentication wizard. If NULL, the 
//          wizard will be parented off the desktop.
//
//      hRadio
//          A valid local radio handle or NULL. If NULL, then all radios will
//          be tired. If any of the radios succeed, then the call will
//          succeed.
//
//      cDevices
//          Number of devices in the rgbtdi array.
//
//      rgbtdi
//          An array BLUETOOTH_DEVICE_INFO records of the devices to be
//          authenticated.
//
//  Return Values:
//
//      ERROR_SUCCESS
//          Success. Check the fAuthenticate flag on each of the devices.
//
//      ERROR_CANCELLED
//          User aborted the operation. Check the fAuthenticate flags on 
//          each device to determine if any of the devices were authenticated
//          before the user cancelled the operation.
//
//      ERROR_INVALID_PARAMETER
//          One of the items in the array of devices is invalid.
//
//      ERROR_NO_MORE_ITEMS
//          All the devices in the array of devices are already been marked as
//          being authenticated.
//
//      other WIN32 error
//          Failure. Return value is the error code.
//

function BluetoothAuthenticateMultipleDevices(
    hwndParent: HWND;
    hRadio: THandle;
    cDevices: DWORD;
    pbtdi: PBLUETOOTH_DEVICE_INFO): DWORD; stdcall;

// ***************************************************************************
//
//  Bluetooth Services
//
// ***************************************************************************

const
  BLUETOOTH_SERVICE_DISABLE  = $00;
  BLUETOOTH_SERVICE_ENABLE   = $01;
  BLUETOOTH_SERVICE_MASK     = BLUETOOTH_SERVICE_ENABLE or BLUETOOTH_SERVICE_DISABLE;

//
//  Description:
//      Enables/disables the services for a particular device.
//
//      The system maintains a mapping of service guids to supported drivers for
//      Bluetooth-enabled devices. Enabling a service installs the corresponding
//      device driver. Disabling a service removes the corresponding device driver.
//
//      If a non-supported service is enabled, a driver will not be installed.
//
//  Parameters
//      hRadio
//          Handle of the local Bluetooth radio device.
//
//      pbtdi
//          Pointer to a BLUETOOTH_DEVICE_INFO record.
//
//      pGuidService
//          The service GUID on the remote device.
//
//      dwServiceFlags
//          Flags to adjust the service.
//              BLUETOOTH_SERVICE_DISABLE   -   disable the service
//              BLUETOOTH_SERVICE_ENABLE    -   enables the service
//
//  Return Values:
//      ERROR_SUCCESS
//          The call was successful.
//
//      ERROR_INVALID_PARAMETER
//          dwServiceFlags are invalid.
//
//      ERROR_SERVICE_DOES_NOT_EXIST
//          The GUID in pGuidService is not supported.
//
//      other WIN32 error
//          The call failed.
//

function BluetoothSetServiceState(
    hRadio: THandle;
    pbtdi: PBLUETOOTH_DEVICE_INFO;
    const pGuidService: TGUID;
    dwServiceFlags: DWORD): DWORD; stdcall;

//
//  Description:
//      Enumerates the services guids enabled on a particular device. If hRadio
//      is NULL, all device will be searched for the device and all the services 
//      enabled will be returned.
//
//  Parameters:
//      hRadio
//          Handle of the local Bluetooth radio device. If NULL, it will search
//          all the radios for the address in the pbtdi.
//
//      pbtdi
//          Pointer to a BLUETOOTH_DEVICE_INFO record.
//
//      pcService
//          On input, the number of records pointed to by pGuidServices.
//          On output, the number of valid records return in pGuidServices.
//
//      pGuidServices
//          Pointer to memory that is at least *pcService in length.
//
//  Return Values:
//      ERROR_SUCCESS
//          The call succeeded. pGuidServices is valid.
//
//      ERROR_MORE_DATA
//          The call succeeded. pGuidService contains an incomplete list of
//          enabled service GUIDs.
//
//      other WIN32 errors
//          The call failed.
//

function BluetoothEnumerateInstalledServices(
    hRadio: THandle;
    pbtdi: PBLUETOOTH_DEVICE_INFO;
    var pcServices: DWORD;
    pGuidServices: PGUID): DWORD; stdcall;

//
//  Description:
//      Change the discovery state of the local radio(s).
//      If hRadio is NULL, all the radios will be set.
//
//      Use BluetoothIsDiscoverable() to determine the radios current state.
//
//      The system ensures that a discoverable system is connectable, thus
//      the radio must allow incoming connections (see 
//      BluetoothEnableIncomingConnections) prior to making a radio 
//      discoverable. Failure to do so will result in this call failing
//      (returns FALSE).
//
//  Parameters:
//      hRadio
//          If not NULL, changes the state of a specific radio.
//          If NULL, the API will interate through all the radios.
//
//      fEnabled
//          If FALSE, discovery will be disabled.
//
//  Return Values
//      TRUE
//          State was successfully changed. If the caller specified NULL for
//          hRadio, at least of the radios accepted the state change.
//
//      FALSE
//          State was not changed. If the caller specified NULL for hRadio, all
//          of the radios did not accept the state change.
//

function BluetoothEnableDiscovery(hRadio: THandle; fEnabled: BOOL): BOOL; stdcall;

//
//  Description:
//      Determines if the Bluetooth radios are discoverable. If there are 
//      multiple radios, the first one to say it is discoverable will cause 
//      this function to return TRUE.
//
//  Parameters:
//      hRadio
//          Handle of the radio to check. If NULL, it will check all local
//          radios.
//
//  Return Values:
//      TRUE
//          A least one radio is discoverable.
//
//      FALSE
//          No radios are discoverable.
//

function BluetoothIsDiscoverable(hRadio: THandle): BOOL; stdcall;

//
//  Description:
//      Enables/disables the state of a radio to accept incoming connections.
//      If hRadio is NULL, all the radios will be set.
//
//      Use BluetoothIsConnectable() to determine the radios current state.
//
//      The system enforces that a radio that is not connectable is not
//      discoverable too. The radio must be made non-discoverable (see 
//      BluetoothEnableDiscovery) prior to making a radio non-connectionable. 
//      Failure to do so will result in this call failing (returns FALSE).
//
//  Parameters:
//      hRadio
//          If not NULL, changes the state of a specific radio.
//          If NULL, the API will interate through all the radios.
//
//      fEnabled
//          If FALSE, incoming connection will be disabled.
//
//  Return Values
//      TRUE
//          State was successfully changed. If the caller specified NULL for
//          hRadio, at least of the radios accepted the state change.
//
//      FALSE
//          State was not changed. If the caller specified NULL for hRadio, all
//          of the radios did not accept the state change.
//

function BluetoothEnableIncomingConnections(hRadio: THandle; fEnabled: BOOL): BOOL; stdcall;

//
//  Description:
//      Determines if the Bluetooth radios are connectable. If there are 
//      multiple radios, the first one to say it is connectable will cause 
//      this function to return TRUE.
//
//  Parameters:
//      hRadio
//          Handle of the radio to check. If NULL, it will check all local
//          radios.
//
//  Return Values:
//      TRUE
//          A least one radio is allowing incoming connections.
//
//      FALSE
//          No radios are allowing incoming connections.
//

function BluetoothIsConnectable(hRadio: THandle): BOOL; stdcall;

// ***************************************************************************
//
//  Authentication Registration
//
// ***************************************************************************

type
  HBLUETOOTH_AUTHENTICATION_REGISTRATION = THandle;

  PFN_AUTHENTICATION_CALLBACK = function (pvParam: Pointer; pDevice: PBLUETOOTH_DEVICE_INFO): BOOL; stdcall;

//
//  Description:
//      Registers a callback function to be called when a particular device
//      requests authentication. The request is sent to the last application
//      that requested authentication for a particular device.
//
//  Parameters:
//      pbtdi
//          A pointer to a BLUETOOTH_DEVICE_INFO structure. The Bluetooth
//          address will be used for comparision.
//
//      phRegHandle
//          A pointer to where the registration HANDLE value will be 
//          stored. Call BluetoothUnregisterAuthentication() to close
//          the handle.
//
//      pfnCallback
//          The function that will be called when the authentication event
//          occurs. This function should match PFN_AUTHENTICATION_CALLBACK's
//          prototype.
//
//      pvParam
//          Optional parameter to be past through to the callback function.
//          This can be anything the application was to define.
//
//  Return Values:
//      ERROR_SUCCESS
//          Success. A valid registration handle was returned.
//
//      ERROR_OUTOFMEMORY
//          Out of memory.
//
//      other Win32 error.
//          Failure. The registration handle is invalid.
//

function BluetoothRegisterForAuthentication(
    pbtdi: PBLUETOOTH_DEVICE_INFO;
    var phRegHandle: HBLUETOOTH_AUTHENTICATION_REGISTRATION;
    pfnCallback: PFN_AUTHENTICATION_CALLBACK;
    pvParam: Pointer): DWORD; stdcall;

//
//  Description:
//      Unregisters an authentication callback and closes the handle. See 
//      BluetoothRegisterForAuthentication() for more information about
//      authentication registration.
//
//  Parameters:
//      hRegHandle
//          Handle returned by BluetoothRegisterForAuthentication().
//
//  Return Value:
//      TRUE
//          The handle was successfully closed.
//
//      FALSE
//          The handle was not successfully closed. Check GetLastError for
//          more details.
//
//          ERROR_INVALID_HANDLE
//              The handle is NULL.
//
//          other Win32 errors.
//

function BluetoothUnregisterAuthentication(hRegHandle: HBLUETOOTH_AUTHENTICATION_REGISTRATION): BOOL; stdcall;

//
//  Description:
//      This function should be called after receiving an authentication request
//      to send the passkey response.
//
//  Parameters:
//
//      hRadio
//          Optional handle to the local radio. If NULL, the function will try
//          each radio until one succeeds.
//
//      pbtdi
//          A pointer to a BLUETOOTH_DEVICE_INFO structure describing the device
//          being authenticated. This can be the same structure passed to the 
//          callback function.
//
//      pszPasskey
//          A pointer to UNICODE zero-terminated string of the passkey response
//          that should be sent back to the authenticating device.
//
//  Return Values:
//      ERROR_SUCESS
//          The device accepted the passkey response. The device is authenticated.
//
//      ERROR_CANCELED
//          The device denied the passkey reponse. This also will returned if there
//          is a communications problem with the local radio.
//
//      E_FAIL
//          The device returned a failure code during authentication.
//
//      other Win32 error codes
//

function BluetoothSendAuthenticationResponse(
    hRadio: THandle;
    pbtdi: PBLUETOOTH_DEVICE_INFO;
    pszPasskey: LPWSTR): DWORD; stdcall;

// ***************************************************************************
//
//  SDP Parsing Functions
//
// ***************************************************************************

type
  TSpdElementDataString = record
    // raw string buffer, may not be encoded as ANSI, use
    // BluetoothSdpGetString to convert the value if it is described
    // by the base language attribute ID list
    value: PBYTE;
    // raw length of the string, may not be NULL terminuated
    length: ULONG;
  end;

  TSpdElementDataUrl = record
    value: PBYTE;
    length: ULONG;
  end;

  // type == SDP_TYPE_SEQUENCE
  TSpdElementDataSequence = record
    // raw sequence, starts at sequence element header
    value: PBYTE;
    // raw sequence length
    length: ULONG;
  end;

  // type == SDP_TYPE_ALTERNATIVE
  TSpdElementDataAlternative = record
    // raw alternative, starts at alternative element header
    value: PBYTE;
    // raw alternative length
    length: ULONG;
  end;

  _SDP_ELEMENT_DATA = record
    //
    // Enumeration of SDP element types.  Generic element types will have a
    // specificType value other then SDP_ST_NONE.  The generic types are:
    // o SDP_TYPE_UINT
    // o SDP_TYPE_INT
    // o SDP_TYPE_UUID
    //
    type_: SDP_TYPE;

    //
    // Specific types for the generic SDP element types.
    //
    specificType: SDP_SPECIFICTYPE;

    //
    // Union of all possible data types.  type and specificType will indicate
    // which field is valid.  For types which do not have a valid specificType,
    // specific type will be SDP_ST_NONE.
    //
    case Integer of
        // type == SDP_TYPE_INT
        0: (int128: SDP_LARGE_INTEGER_16);        // specificType == SDP_ST_INT128
        1: (int64: LONGLONG);                     // specificType == SDP_ST_INT64
        2: (int32: Integer);                         // specificType == SDP_ST_INT32
        3: (int16: SHORT);                        // specificType == SDP_ST_INT16
        4: (int8: CHAR);                          // specificType == SDP_ST_INT8

        // type == SDP_TYPE_UINT
        5: (uint128: SDP_ULARGE_INTEGER_16);      // specificType == SDP_ST_UINT128
        6: (uint64: Int64);                   // specificType == SDP_ST_UINT64
        7: (uint32: ULONG);                       // specificType == SDP_ST_UINT32
        8: (uint16: Word);                      // specificType == SDP_ST_UINT16
        9: (uint8: UCHAR);                        // specificType == SDP_ST_UINT8

        // type == SDP_TYPE_BOOLEAN
        10: (booleanVal: UCHAR);

        // type == SDP_TYPE_UUID
        11: (uuid128: TGUID);                       // specificType == SDP_ST_UUID128
        12: (uuid32: ULONG);                       // specificType == SDP_ST_UUID32
        13: (uuid16: Word);                      // specificType == SDP_ST_UUID32

        // type == SDP_TYPE_STRING
        14: (string_: TSpdElementDataString);
        // type == SDP_TYPE_URL
        15: (url: TSpdElementDataUrl);

        // type == SDP_TYPE_SEQUENCE
        16: (sequence: TSpdElementDataSequence);

        // type == SDP_TYPE_ALTERNATIVE
        17: (alternative: TSpdElementDataAlternative);
  end;
  SDP_ELEMENT_DATA = _SDP_ELEMENT_DATA;
  PSDP_ELEMENT_DATA = ^SDP_ELEMENT_DATA;
  TSdpElementData = SDP_ELEMENT_DATA;
  PSdpElementData = PSDP_ELEMENT_DATA;  

//
// Description:
//      Retrieves and parses the element found at pSdpStream
//
// Parameters:
//      IN pSdpStream
//          pointer to valid SDP stream
//
//      IN cbSdpStreamLength
//          length of pSdpStream in bytes
//
//      OUT pData
//          pointer to be filled in with the data of the SDP element at the
//          beginning of pSdpStream
//
// Return Values:
//      ERROR_INVALID_PARAMETER
//          one of required parameters is NULL or the pSdpStream is invalid
//
//      ERROR_SUCCESS
//          the sdp element was parsed correctly
//

function BluetoothSdpGetElementData(
    pSdpStream: PBYTE;
    cbSdpStreamLength: ULONG;
    pData: PSDP_ELEMENT_DATA): DWORD; stdcall;

type
  HBLUETOOTH_CONTAINER_ELEMENT = THandle;

//
// Description:
//      Iterates over a container stream, returning each elemetn contained with
//      in the container element at the beginning of pContainerStream
//
// Parameters:
//      IN pContainerStream
//          pointer to valid SDP stream whose first element is either a sequence
//          or alternative
//
//      IN cbContainerlength
//          length in bytes of pContainerStream
//
//      IN OUT pElement
//          Value used to keep track of location within the stream.  The first
//          time this function is called for a particular container, *pElement
//          should equal NULL.  Upon subsequent calls, the value should be
//          unmodified.
//
//      OUT pData
//          pointer to be filled in with the data of the SDP element at the
//          current element of pContainerStream
//
//  Return Values:
//      ERROR_SUCCESS
//          The call succeeded, pData contains the data
//
//      ERROR_NO_MORE_ITEMS
//          There are no more items in the list, the caller should cease calling
//          BluetoothSdpGetContainerElementData for this container.
//
//      ERROR_INVALID_PARAMETER
//          A required pointer is NULL or the container is not a valid SDP
//          stream
//
// Usage example:
//
// HBLUETOOTH_CONTAINER_ELEMENT element;
// SDP_ELEMENT_DATA data;
// ULONG result;
//
// element = NULL;
//
// while (TRUE) {
//      result = BluetoothSdpGetContainerElementData(
//          pContainer, ulContainerLength, &element, &data);
//
//      if (result == ERROR_NO_MORE_ITEMS) {
//          // We are done
//          break;
//      }
//      else if (result != ERROR_SUCCESS) {
//          // error
//      }
//
//      // do something with data ...
// }
//
//

function BluetoothSdpGetContainerElementData(
    pContainerStream: PBYTE;
    cbContainerLength: ULONG;
    var pElement: HBLUETOOTH_CONTAINER_ELEMENT;
    pData: PSDP_ELEMENT_DATA): DWORD; stdcall;

//
// Description:
//      Retrieves the attribute value for the given attribute ID.  pRecordStream
//      must be an SDP stream that is formatted as an SDP record, a SEQUENCE
//      containing UINT16 + element pairs.
//
// Parameters:
//      IN pRecordStream
//          pointer to a valid SDP stream which is formatted as a singl SDP
//          record
//
//      IN cbRecordlnegh
//          length of pRecordStream in bytes
//
//      IN usAttributeId
//          the attribute ID to search for.  see bthdef.h for SDP_ATTRIB_Xxx
//          values.
//
//      OUT pAttributeData
//          pointer that will contain the attribute ID's value
//
// Return Values:
//      ERRROR_SUCCESS
//          Call succeeded, pAttributeData contains the attribute value
//
//      ERROR_INVALID_PARAMETER
//          One of the required pointers was NULL, pRecordStream was not a valid
//          SDP stream, or pRecordStream was not a properly formatted SDP record
//
//      ERROR_FILE_NOT_FOUND
//          usAttributeId was not found in the record
//
// Usage:
//
// ULONG result;
// SDP_DATA_ELEMENT data;
//
// result = BluetoothSdpGetAttributeValue(
//      pRecordStream, cbRecordLength, SDP_ATTRIB_RECORD_HANDLE, &data);
// if (result == ERROR_SUCCESS) {
//      printf("record handle is 0x%x\n", data.data.uint32);
// }
//

function BluetoothSdpGetAttributeValue(
    pRecordStream: PBYTE;
    cbRecordLength: ULONG;
    usAttributeId: Word;
    pAttributeData: PSDP_ELEMENT_DATA): DWORD; stdcall;

//
// These three fields correspond one to one with the triplets defined in the
// SDP specification for the language base attribute ID list.
//

type
  _SDP_STRING_TYPE_DATA = record
    //
    // How the string is encoded according to ISO 639:1988 (E/F): "Code
    // for the representation of names of languages".
    //
    encoding: Word;

    //
    // MIBE number from IANA database
    //
    mibeNum: Word;

    //
    // The base attribute where the string is to be found in the record
    //
    attributeId: Word;
  end;
  SDP_STRING_TYPE_DATA = _SDP_STRING_TYPE_DATA;
  PSDP_STRING_TYPE_DATA = ^SDP_STRING_TYPE_DATA;
  TSdpStringTypeData = SDP_STRING_TYPE_DATA;
  PSdpStringTypeData = PSDP_STRING_TYPE_DATA;  

//
// Description:
//      Converts a raw string embedded in the SDP record into a UNICODE string
//
// Parameters:
//      IN pRecordStream
//          a valid SDP stream which is formatted as an SDP record
//
//      IN cbRecordLength
//          length of pRecordStream in bytes
//
//      IN pStringData
//          if NULL, then the calling thread's locale will be used to search
//          for a matching string in the SDP record.  If not NUL, the mibeNum
//          and attributeId will be used to find the string to convert.
//
//      IN usStringOffset
//          the SDP string type offset to convert.  usStringOffset is added to
//          the base attribute id of the string.   SDP specification defined
//          offsets are: STRING_NAME_OFFSET, STRING_DESCRIPTION_OFFSET, and
//          STRING_PROVIDER_NAME_OFFSET (found in bthdef.h).
//
//      OUT pszString
//          if NULL, pcchStringLength will be filled in with the required number
//          of characters (not bytes) to retrieve the converted string.
//
//      IN OUT pcchStringLength
//          Upon input, if pszString is not NULL, will contain the length of
//          pszString in characters.  Upon output, it will contain either the
//          number of required characters including NULL if an error is returned
//          or the number of characters written to pszString (including NULL).
//
//  Return Values:
//      ERROR_SUCCES
//          Call was successful and pszString contains the converted string
//
//      ERROR_MORE_DATA
//          pszString was NULL or too small to contain the converted string,
//          pccxhStringLength contains the required length in characters
//
//      ERROR_INVALID_DATA
//          Could not perform the conversion
//
//      ERROR_NO_SYSTEM_RESOURCES
//          Could not allocate memory internally to perform the conversion
//
//      ERROR_INVALID_PARAMETER
//          One of the rquired pointers was NULL, pRecordStream was not a valid
//          SDP stream, pRecordStream was not a properly formatted record, or
//          the desired attribute + offset was not a string.
//
//      Other HRESULTs returned by COM
//

function BluetoothSdpGetString(
    pRecordStream: PBYTE;
    cbRecordLength: ULONG;
    pStringData: PSDP_STRING_TYPE_DATA;
    usStringOffset: Word;
    pszString: PWideChar;
    pcchStringLength: PULONG): DWORD; stdcall;

// ***************************************************************************
//
//  Raw Attribute  Enumeration
//
// ***************************************************************************

type
  PFN_BLUETOOTH_ENUM_ATTRIBUTES_CALLBACK = function (
    uAttribId: ULONG;
    pValueStream: PBYTE;
    cbStreamSize: ULONG;
    pvParam: Pointer): BOOL; stdcall;

//
//  Description:
//      Enumerates through the SDP record stream calling the Callback function
//      for each attribute in the record. If the Callback function returns
//      FALSE, the enumeration is stopped.
//
//  Return Values:
//      TRUE
//          Success! Something was enumerated.
//
//      FALSE
//          Failure. GetLastError() could be one of the following:
//
//          ERROR_INVALID_PARAMETER
//              pSDPStream or pfnCallback is NULL.
//
//          ERROR_INVALID_DATA
//              The SDP stream is corrupt.
//
//          other Win32 errors.
//

function BluetoothSdpEnumAttributes(
    pSDPStream: PBYTE;
    cbStreamSize: ULONG;
    pfnCallback: PFN_BLUETOOTH_ENUM_ATTRIBUTES_CALLBACK;
    pvParam: Pointer): BOOL; stdcall;

function BluetoothEnumAttributes(
    pSDPStream: PBYTE;
    cbStreamSize: ULONG;
    pfnCallback: PFN_BLUETOOTH_ENUM_ATTRIBUTES_CALLBACK;
    pvParam: Pointer): BOOL;

implementation

const
  btapi = 'irprops.dll'; // wild quess!! todo

function BluetoothFindFirstRadio; external btapi name 'BluetoothFindFirstRadio';
function BluetoothFindNextRadio; external btapi name 'BluetoothFindNextRadio';
function BluetoothFindRadioClose; external btapi name 'BluetoothFindRadioClose';
function BluetoothGetRadioInfo; external btapi name 'BluetoothGetRadioInfo';
function BluetoothFindFirstDevice; external btapi name 'BluetoothFindFirstDevice';
function BluetoothFindNextDevice; external btapi name 'BluetoothFindNextDevice';
function BluetoothFindDeviceClose; external btapi name 'BluetoothFindDeviceClose';
function BluetoothGetDeviceInfo; external btapi name 'BluetoothGetDeviceInfo';
function BluetoothUpdateDeviceRecord; external btapi name 'BluetoothUpdateDeviceRecord';
function BluetoothRemoveDevice; external btapi name 'BluetoothRemoveDevice';
function BluetoothSelectDevices; external btapi name 'BluetoothSelectDevices';
function BluetoothSelectDevicesFree; external btapi name 'BluetoothSelectDevicesFree';
function BluetoothDisplayDeviceProperties; external btapi name 'BluetoothDisplayDeviceProperties';
function BluetoothAuthenticateDevice; external btapi name 'BluetoothAuthenticateDevice';
function BluetoothAuthenticateMultipleDevices; external btapi name 'BluetoothAuthenticateMultipleDevices';
function BluetoothSetServiceState; external btapi name 'BluetoothSetServiceState';
function BluetoothEnumerateInstalledServices; external btapi name 'BluetoothEnumerateInstalledServices';
function BluetoothEnableDiscovery; external btapi name 'BluetoothEnableDiscovery';
function BluetoothIsDiscoverable; external btapi name 'BluetoothIsDiscoverable';
function BluetoothEnableIncomingConnections; external btapi name 'BluetoothEnableIncomingConnections';
function BluetoothIsConnectable; external btapi name 'BluetoothIsConnectable';
function BluetoothRegisterForAuthentication; external btapi name 'BluetoothRegisterForAuthentication';
function BluetoothUnregisterAuthentication; external btapi name 'BluetoothUnregisterAuthentication';
function BluetoothSendAuthenticationResponse; external btapi name 'BluetoothSendAuthenticationResponse';
function BluetoothSdpGetElementData; external btapi name 'BluetoothSdpGetElementData';
function BluetoothSdpGetContainerElementData; external btapi name 'BluetoothSdpGetContainerElementData';
function BluetoothSdpGetAttributeValue; external btapi name 'BluetoothSdpGetAttributeValue';
function BluetoothSdpGetString; external btapi name 'BluetoothSdpGetString';
function BluetoothSdpEnumAttributes; external btapi name 'BluetoothSdpEnumAttributes';

function BluetoothEnumAttributes(
    pSDPStream: PBYTE;
    cbStreamSize: ULONG;
    pfnCallback: PFN_BLUETOOTH_ENUM_ATTRIBUTES_CALLBACK;
    pvParam: Pointer): BOOL;
begin
  Result := BluetoothSdpEnumAttributes(pSDPStream, cbStreamSize, pfnCallback, pvParam);
end;

end.
