{******************************************************************************}
{                                                       	               }
{ Battery class driver API interface Unit for Object Pascal                    }
{                                                       	               }
{ Portions created by Microsoft are Copyright (C) 1995-2001 Microsoft          }
{ Corporation. All Rights Reserved.                                            }
{ 								               }
{ The original file is: batclass.h, released June 2000. The original Pascal    }
{ code is: BatClass.pas, released December 2000. The initial developer of the  }
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

unit JwaBatClass;

{$WEAKPACKAGEUNIT}

{$HPPEMIT ''}
{$HPPEMIT '#include "BatClass.h"'}
{$HPPEMIT ''}

{$I WINDEFINES.INC}

interface

uses
  JwaWinIoctl, JwaWinType;

//
// Battery device GUID
//

const
  GUID_DEVICE_BATTERY: TGUID = (D1:$72631e54; D2:$78A4; D3:$11d0; D4:($bc, $f7, $00, $aa, $00, $b7, $b3, $2a));
  {$EXTERNALSYM GUID_DEVICE_BATTERY}
  BATTERY_STATUS_WMI_GUID: TGUID = (D1:$fc4670d1; D2:$ebbf; D3:$416e; D4:($87, $ce, $37, $4a, $4e, $bc, $11, $1a));
  {$EXTERNALSYM BATTERY_STATUS_WMI_GUID}
  BATTERY_RUNTIME_WMI_GUID: TGUID = (D1:$535a3767; D2:$1ac2; D3:$49bc; D4:($a0, $77, $3f, $7a, $02, $e4, $0a, $ec));
  {$EXTERNALSYM BATTERY_RUNTIME_WMI_GUID}
  BATTERY_TEMPERATURE_WMI_GUID: TGUID = (D1:$1a52a14d; D2:$adce; D3:$4a44; D4:($9a, $3e, $c8, $d8, $f1, $5f, $f2, $c2));
  {$EXTERNALSYM BATTERY_TEMPERATURE_WMI_GUID}
  BATTERY_FULL_CHARGED_CAPACITY_WMI_GUID: TGUID = (D1:$40b40565; D2:$96f7; D3:$4435; D4:($86, $94, $97, $e0, $e4, $39, $59, $05));
  {$EXTERNALSYM BATTERY_FULL_CHARGED_CAPACITY_WMI_GUID}
  BATTERY_CYCLE_COUNT_WMI_GUID: TGUID = (D1:$ef98db24; D2:$0014; D3:$4c25; D4:($a5, $0b, $c7, $24, $ae, $5c, $d3, $71));
  {$EXTERNALSYM BATTERY_CYCLE_COUNT_WMI_GUID}
  BATTERY_STATIC_DATA_WMI_GUID: TGUID = (D1:$05e1e463; D2:$e4e2; D3:$4ea9; D4:($80, $cb, $9b, $d4, $b3, $ca, $06, $55));
  {$EXTERNALSYM BATTERY_STATIC_DATA_WMI_GUID}
  BATTERY_STATUS_CHANGE_WMI_GUID: TGUID = (D1:$cddfa0c3; D2:$7c5b; D3:$4e43; D4:($a0, $34, $05, $9f, $a5, $b8, $43, $64));
  {$EXTERNALSYM BATTERY_STATUS_CHANGE_WMI_GUID}
  BATTERY_TAG_CHANGE_WMI_GUID: TGUID = (D1:$5e1f6e19; D2:$8786; D3:$4d23; D4:($94, $fc, $9e, $74, $6b, $d5, $d8, $88));
  {$EXTERNALSYM BATTERY_TAG_CHANGE_WMI_GUID}

//
// Battery driver interface
//
// IOCTL_BATTERY_QUERY_TAG
// IOCTL_BATTERY_QUERY_INFORMATION
// IOCTL_BATTERY_SET_INFORMATION
// IOCTL_BATTERY_QUERY_STATUS
//

//
// IOCTL_BATTERY_QUERY_TAG
//

  IOCTL_BATTERY_QUERY_TAG = (FILE_DEVICE_BATTERY shl 16) or (FILE_READ_ACCESS shl 14) or ($10 shl 2) or METHOD_BUFFERED;
  {$EXTERNALSYM IOCTL_BATTERY_QUERY_TAG}

  BATTERY_TAG_INVALID = 0;
  {$EXTERNALSYM BATTERY_TAG_INVALID}

//
// IOCTL_BATTERY_QUERY_INFORMATION
//

  IOCTL_BATTERY_QUERY_INFORMATION = (FILE_DEVICE_BATTERY shl 16) or (FILE_READ_ACCESS shl 14) or ($11 shl 2) or METHOD_BUFFERED;
  {$EXTERNALSYM IOCTL_BATTERY_QUERY_INFORMATION}

type
  BATTERY_QUERY_INFORMATION_LEVEL = (
    BatteryInformation,
    BatteryGranularityInformation,
    BatteryTemperature,
    BatteryEstimatedTime,
    BatteryDeviceName,
    BatteryManufactureDate,
    BatteryManufactureName,
    BatteryUniqueID,
    BatterySerialNumber);
  {$EXTERNALSYM BATTERY_QUERY_INFORMATION_LEVEL}
  TBatteryQueryInformationLevel = BATTERY_QUERY_INFORMATION_LEVEL;

  _BATTERY_QUERY_INFORMATION = record
    BatteryTag: ULONG;
    InformationLevel: BATTERY_QUERY_INFORMATION_LEVEL;
    AtRate: LONG;
  end;
  {$EXTERNALSYM _BATTERY_QUERY_INFORMATION}
  BATTERY_QUERY_INFORMATION = _BATTERY_QUERY_INFORMATION;
  {$EXTERNALSYM BATTERY_QUERY_INFORMATION}
  PBATTERY_QUERY_INFORMATION = ^BATTERY_QUERY_INFORMATION;
  {$EXTERNALSYM PBATTERY_QUERY_INFORMATION}
  TBatteryQueryInformation = BATTERY_QUERY_INFORMATION;
  PBatteryQueryInformation = PBATTERY_QUERY_INFORMATION;

//
// Format of data returned when
// BATTERY_INFORMATION_LEVEL = BatteryInformation
//

  _BATTERY_INFORMATION = record
    Capabilities: ULONG;
    Technology: UCHAR;
    Reserved: array [0..2] of UCHAR;
    Chemistry: array [0..3] of UCHAR;
    DesignedCapacity: ULONG;
    FullChargedCapacity: ULONG;
    DefaultAlert1: ULONG;
    DefaultAlert2: ULONG;
    CriticalBias: ULONG;
    CycleCount: ULONG;
  end;
  {$EXTERNALSYM _BATTERY_INFORMATION}
  BATTERY_INFORMATION = _BATTERY_INFORMATION;
  {$EXTERNALSYM BATTERY_INFORMATION}
  PBATTERY_INFORMATION = ^BATTERY_INFORMATION;
  {$EXTERNALSYM PBATTERY_INFORMATION}
  TBatteryInformation = BATTERY_INFORMATION;
  PBatteryInformation = PBATTERY_INFORMATION;

//
// BATTERY_INFORMATION.Capabilities flags
//

const
  BATTERY_SYSTEM_BATTERY          = DWORD($80000000);
  {$EXTERNALSYM BATTERY_SYSTEM_BATTERY}
  BATTERY_CAPACITY_RELATIVE       = $40000000;
  {$EXTERNALSYM BATTERY_CAPACITY_RELATIVE}
  BATTERY_IS_SHORT_TERM           = $20000000;
  {$EXTERNALSYM BATTERY_IS_SHORT_TERM}
  BATTERY_SET_CHARGE_SUPPORTED    = $00000001;
  {$EXTERNALSYM BATTERY_SET_CHARGE_SUPPORTED}
  BATTERY_SET_DISCHARGE_SUPPORTED = $00000002;
  {$EXTERNALSYM BATTERY_SET_DISCHARGE_SUPPORTED}
  BATTERY_SET_RESUME_SUPPORTED    = $00000004;
  {$EXTERNALSYM BATTERY_SET_RESUME_SUPPORTED}

//
// BATTERY_INFORMATION.XXXCapacity constants
//

  BATTERY_UNKNOWN_CAPACITY = DWORD($FFFFFFFF);
  {$EXTERNALSYM BATTERY_UNKNOWN_CAPACITY}

//
// BatteryEstimatedTime constant
//

  BATTERY_UNKNOWN_TIME = DWORD($FFFFFFFF);
  {$EXTERNALSYM BATTERY_UNKNOWN_TIME}

//
// Max battery driver BATTERY_QUERY_INFORMATION_LEVEL string storage
// size in bytes.
//

  MAX_BATTERY_STRING_SIZE = 128;
  {$EXTERNALSYM MAX_BATTERY_STRING_SIZE}

//
// Struct for accessing the packed date format in BatteryManufactureDate.
//

type
  _BATTERY_MANUFACTURE_DATE = record
    Day: UCHAR;
    Month: UCHAR;
    Year: USHORT;
  end;
  {$EXTERNALSYM _BATTERY_MANUFACTURE_DATE}
  BATTERY_MANUFACTURE_DATE = _BATTERY_MANUFACTURE_DATE;
  {$EXTERNALSYM BATTERY_MANUFACTURE_DATE}
  PBATTERY_MANUFACTURE_DATE = ^BATTERY_MANUFACTURE_DATE;
  {$EXTERNALSYM PBATTERY_MANUFACTURE_DATE}
  TBatteryManufactureDate = BATTERY_MANUFACTURE_DATE;
  PBatteryManufactureDate = PBATTERY_MANUFACTURE_DATE;

//
// IOCTL_BATTERY_SET_INFORMATION
//

const
  IOCTL_BATTERY_SET_INFORMATION = (FILE_DEVICE_BATTERY shl 16) or (FILE_WRITE_ACCESS shl 14) or ($12 shl 2) or METHOD_BUFFERED;
  {$EXTERNALSYM IOCTL_BATTERY_SET_INFORMATION}

type
  BATTERY_SET_INFORMATION_LEVEL = (
    BatteryCriticalBias,
    BatteryCharge,
    BatteryDischarge);
  {$EXTERNALSYM BATTERY_SET_INFORMATION_LEVEL}
  TBatterySetInformationLevel = BATTERY_SET_INFORMATION_LEVEL;

  _BATTERY_SET_INFORMATION = record
    BatteryTag: ULONG;
    InformationLevel: BATTERY_SET_INFORMATION_LEVEL;
    Buffer: array [0..0] of UCHAR;
  end;
  {$EXTERNALSYM _BATTERY_SET_INFORMATION}
  BATTERY_SET_INFORMATION = _BATTERY_SET_INFORMATION;
  {$EXTERNALSYM BATTERY_SET_INFORMATION}
  PBATTERY_SET_INFORMATION = ^BATTERY_SET_INFORMATION;
  {$EXTERNALSYM PBATTERY_SET_INFORMATION}
  TBatterySetInformation = BATTERY_SET_INFORMATION;
  PBatterySetInformation = PBATTERY_SET_INFORMATION;

//
// IOCTL_BATTERY_QUERY_STATUS
//

const
  IOCTL_BATTERY_QUERY_STATUS = (FILE_DEVICE_BATTERY shl 16) or (FILE_READ_ACCESS shl 14) or ($13 shl 2) or METHOD_BUFFERED;
  {$EXTERNALSYM IOCTL_BATTERY_QUERY_STATUS}

//
// Structure of input buffer to IOCTL_BATTERY_QUERY_STATUS
//

type
  _BATTERY_WAIT_STATUS = record
    BatteryTag: ULONG;
    Timeout: ULONG;
    PowerState: ULONG;
    LowCapacity: ULONG;
    HighCapacity: ULONG;
  end;
  {$EXTERNALSYM _BATTERY_WAIT_STATUS}
  BATTERY_WAIT_STATUS = _BATTERY_WAIT_STATUS;
  {$EXTERNALSYM BATTERY_WAIT_STATUS}
  PBATTERY_WAIT_STATUS = ^BATTERY_WAIT_STATUS;
  {$EXTERNALSYM PBATTERY_WAIT_STATUS}
  TBatteryWaitStatus = BATTERY_WAIT_STATUS;
  PBatteryWaitStatus = PBATTERY_WAIT_STATUS;

//
// Structure of output buffer from IOCTL_BATTERY_QUERY_STATUS
//

  _BATTERY_STATUS = record
    PowerState: ULONG;
    Capacity: ULONG;
    Voltage: ULONG;
    Rate: LONG;
  end;
  {$EXTERNALSYM _BATTERY_STATUS}
  BATTERY_STATUS = _BATTERY_STATUS;
  {$EXTERNALSYM BATTERY_STATUS}
  PBATTERY_STATUS = ^BATTERY_STATUS;
  {$EXTERNALSYM PBATTERY_STATUS}
  TBatteryStatus = BATTERY_STATUS;
  PBatteryStatus = PBATTERY_STATUS;

//
// BATTERY_STATUS.PowerState flags
//

const
  BATTERY_POWER_ON_LINE = $00000001;
  {$EXTERNALSYM BATTERY_POWER_ON_LINE}
  BATTERY_DISCHARGING   = $00000002;
  {$EXTERNALSYM BATTERY_DISCHARGING}
  BATTERY_CHARGING      = $00000004;
  {$EXTERNALSYM BATTERY_CHARGING}
  BATTERY_CRITICAL      = $00000008;
  {$EXTERNALSYM BATTERY_CRITICAL}

//
// BATTERY_STATUS Constant
// BATTERY_UNKNOWN_CAPACITY defined above for IOCTL_BATTERY_QUERY_INFORMATION
//

  BATTERY_UNKNOWN_VOLTAGE = DWORD($FFFFFFFF);
  {$EXTERNALSYM BATTERY_UNKNOWN_VOLTAGE}
  BATTERY_UNKNOWN_RATE    = DWORD($80000000);
  {$EXTERNALSYM BATTERY_UNKNOWN_RATE}

// mvb remainder of header file is kernel mode only

implementation

end.
