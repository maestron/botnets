{******************************************************************************}
{                                                       	               }
{ Registry Key Definitions API interface Unit for Object Pascal                }
{                                                       	               }
{ Portions created by Microsoft are Copyright (C) 1995-2001 Microsoft          }
{ Corporation. All Rights Reserved.                                            }
{ 								               }
{ The original file is: regstr.h, released June 2000. The original Pascal      }
{ code is: RegStr.pas, released December 2000. The initial developer of the    }
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

unit JwaRegStr;

{$WEAKPACKAGEUNIT}

{$HPPEMIT ''}
{$HPPEMIT '#include "regstr.h"'}
{$HPPEMIT ''}

{$I WINDEFINES.INC}

interface

{.$DEFINE NEC_98}
{.$DEFINE _KERNEL_PNPI_}

uses
  JwaWinType;

const

// Public registry key names

  REGSTR_KEY_CLASS       = 'Class'; // under LOCAL_MACHINE
  {$EXTERNALSYM REGSTR_KEY_CLASS}
  REGSTR_KEY_CONFIG      = 'Config'; // under LOCAL_MACHINE
  {$EXTERNALSYM REGSTR_KEY_CONFIG}
  REGSTR_KEY_ENUM        = 'Enum'; // under LOCAL_MACHINE
  {$EXTERNALSYM REGSTR_KEY_ENUM}
  REGSTR_KEY_ROOTENUM    = 'Root'; // child of ENUM
  {$EXTERNALSYM REGSTR_KEY_ROOTENUM}
  REGSTR_KEY_BIOSENUM    = 'BIOS'; // child of ENUM
  {$EXTERNALSYM REGSTR_KEY_BIOSENUM}
  REGSTR_KEY_ACPIENUM    = 'ACPI'; // child of ENUM
  {$EXTERNALSYM REGSTR_KEY_ACPIENUM}
  REGSTR_KEY_PCMCIAENUM  = 'PCMCIA'; // child of ENUM
  {$EXTERNALSYM REGSTR_KEY_PCMCIAENUM}
  REGSTR_KEY_PCIENUM     = 'PCI'; // child of ENUM
  {$EXTERNALSYM REGSTR_KEY_PCIENUM}
  REGSTR_KEY_VPOWERDENUM = 'VPOWERD'; // child of ENUM
  {$EXTERNALSYM REGSTR_KEY_VPOWERDENUM}
{$IFNDEF NEC_98}
  REGSTR_KEY_ISAENUM  = 'ISAPnP'; // child of ENUM
  {$EXTERNALSYM REGSTR_KEY_ISAENUM}
  REGSTR_KEY_EISAENUM = 'EISA'; // child of ENUM
  {$EXTERNALSYM REGSTR_KEY_EISAENUM}
{$ELSE}
  REGSTR_KEY_ISAENUM  = 'C98PnP'; // child of ENUM
  {$EXTERNALSYM REGSTR_KEY_ISAENUM}
  REGSTR_KEY_EISAENUM = 'NESA'; // child of ENUM
  {$EXTERNALSYM REGSTR_KEY_EISAENUM}
{$ENDIF}
  REGSTR_KEY_LOGCONFIG   = 'LogConfig'; // child of enum\<enumerator>\<deviceid>\<instanceid>
  {$EXTERNALSYM REGSTR_KEY_LOGCONFIG}
  REGSTR_KEY_SYSTEMBOARD = '*PNP0C01'; // child of enum\root
  {$EXTERNALSYM REGSTR_KEY_SYSTEMBOARD}
  REGSTR_KEY_APM         = '*PNP0C05'; // child of enum\root
  {$EXTERNALSYM REGSTR_KEY_APM}

  REGSTR_KEY_INIUPDATE = 'IniUpdate';
  {$EXTERNALSYM REGSTR_KEY_INIUPDATE}
  REG_KEY_INSTDEV      = 'Installed'; // child of hklm\class\classname (Win98-only)
  {$EXTERNALSYM REG_KEY_INSTDEV}

  REGSTR_KEY_DOSOPTCDROM = 'CD-ROM';
  {$EXTERNALSYM REGSTR_KEY_DOSOPTCDROM}
  REGSTR_KEY_DOSOPTMOUSE = 'MOUSE';
  {$EXTERNALSYM REGSTR_KEY_DOSOPTMOUSE}

  REGSTR_KEY_KNOWNDOCKINGSTATES = 'Hardware Profiles';
  {$EXTERNALSYM REGSTR_KEY_KNOWNDOCKINGSTATES}
  REGSTR_KEY_DEVICEPARAMETERS   = 'Device Parameters';
  {$EXTERNALSYM REGSTR_KEY_DEVICEPARAMETERS}

// Public registry paths

  REGSTR_DEFAULT_INSTANCE          = '0000';
  {$EXTERNALSYM REGSTR_DEFAULT_INSTANCE}
  REGSTR_PATH_MOTHERBOARD          = REGSTR_KEY_SYSTEMBOARD + '\' + REGSTR_DEFAULT_INSTANCE;
  {$EXTERNALSYM REGSTR_PATH_MOTHERBOARD}
  REGSTR_PATH_SETUP                = 'Software\Microsoft\Windows\CurrentVersion';
  {$EXTERNALSYM REGSTR_PATH_SETUP}
  REGSTR_PATH_DRIVERSIGN           = 'Software\Microsoft\Driver Signing';
  {$EXTERNALSYM REGSTR_PATH_DRIVERSIGN}
  REGSTR_PATH_NONDRIVERSIGN        = 'Software\Microsoft\Non-Driver Signing';
  {$EXTERNALSYM REGSTR_PATH_NONDRIVERSIGN}
  REGSTR_PATH_DRIVERSIGN_POLICY    = 'Software\Policies\Microsoft\Windows NT\Driver Signing';
  {$EXTERNALSYM REGSTR_PATH_DRIVERSIGN_POLICY}
  REGSTR_PATH_NONDRIVERSIGN_POLICY = 'Software\Policies\Microsoft\Windows NT\Non-Driver Signing';
  {$EXTERNALSYM REGSTR_PATH_NONDRIVERSIGN_POLICY}
  REGSTR_PATH_PIFCONVERT           = 'Software\Microsoft\Windows\CurrentVersion\PIFConvert';
  {$EXTERNALSYM REGSTR_PATH_PIFCONVERT}
  REGSTR_PATH_MSDOSOPTS            = 'Software\Microsoft\Windows\CurrentVersion\MS-DOSOptions';
  {$EXTERNALSYM REGSTR_PATH_MSDOSOPTS}
  REGSTR_PATH_NOSUGGMSDOS          = 'Software\Microsoft\Windows\CurrentVersion\NoMSDOSWarn';
  {$EXTERNALSYM REGSTR_PATH_NOSUGGMSDOS}
  REGSTR_PATH_NEWDOSBOX            = 'Software\Microsoft\Windows\CurrentVersion\MS-DOSSpecialConfig';
  {$EXTERNALSYM REGSTR_PATH_NEWDOSBOX}
  REGSTR_PATH_RUNONCE              = 'Software\Microsoft\Windows\CurrentVersion\RunOnce';
  {$EXTERNALSYM REGSTR_PATH_RUNONCE}
  REGSTR_PATH_RUNONCEEX            = 'Software\Microsoft\Windows\CurrentVersion\RunOnceEx';
  {$EXTERNALSYM REGSTR_PATH_RUNONCEEX}
  REGSTR_PATH_RUN                  = 'Software\Microsoft\Windows\CurrentVersion\Run';
  {$EXTERNALSYM REGSTR_PATH_RUN}
  REGSTR_PATH_RUNSERVICESONCE      = 'Software\Microsoft\Windows\CurrentVersion\RunServicesOnce';
  {$EXTERNALSYM REGSTR_PATH_RUNSERVICESONCE}
  REGSTR_PATH_RUNSERVICES          = 'Software\Microsoft\Windows\CurrentVersion\RunServices';
  {$EXTERNALSYM REGSTR_PATH_RUNSERVICES}
  REGSTR_PATH_EXPLORER             = 'Software\Microsoft\Windows\CurrentVersion\Explorer';
  {$EXTERNALSYM REGSTR_PATH_EXPLORER}
  REGSTR_PATH_DETECT               = 'Software\Microsoft\Windows\CurrentVersion\Detect';
  {$EXTERNALSYM REGSTR_PATH_DETECT}
  REGSTR_PATH_APPPATHS             = 'Software\Microsoft\Windows\CurrentVersion\App Paths';
  {$EXTERNALSYM REGSTR_PATH_APPPATHS}
  REGSTR_PATH_UNINSTALL            = 'Software\Microsoft\Windows\CurrentVersion\Uninstall';
  {$EXTERNALSYM REGSTR_PATH_UNINSTALL}
  REGSTR_PATH_REALMODENET          = 'Software\Microsoft\Windows\CurrentVersion\Network\Real Mode Net';
  {$EXTERNALSYM REGSTR_PATH_REALMODENET}
  REGSTR_PATH_NETEQUIV             = 'Software\Microsoft\Windows\CurrentVersion\Network\Equivalent';
  {$EXTERNALSYM REGSTR_PATH_NETEQUIV}
  REGSTR_PATH_CVNETWORK            = 'Software\Microsoft\Windows\CurrentVersion\Network';
  {$EXTERNALSYM REGSTR_PATH_CVNETWORK}
  REGSTR_PATH_WMI_SECURITY         = 'System\CurrentControlSet\Control\Wmi\Security';
  {$EXTERNALSYM REGSTR_PATH_WMI_SECURITY}
  REGSTR_PATH_RELIABILITY          = 'Software\Microsoft\Windows\CurrentVersion\Reliability';
  {$EXTERNALSYM REGSTR_PATH_RELIABILITY}
  REGSTR_PATH_RELIABILITY_POLICY   = TEXT('Software\Policies\Microsoft\Windows NT\Reliability');
  {$EXTERNALSYM REGSTR_PATH_RELIABILITY_POLICY}
  REGSTR_PATH_RELIABILITY_POLICY_SHUTDOWNREASONUI = TEXT('ShutdownReasonUI');
  {$EXTERNALSYM REGSTR_PATH_RELIABILITY_POLICY_SHUTDOWNREASONUI}
  REGSTR_PATH_RELIABILITY_POLICY_SNAPSHOT         = TEXT('Snapshot');
  {$EXTERNALSYM REGSTR_PATH_RELIABILITY_POLICY_SNAPSHOT}
  REGSTR_PATH_RELIABILITY_POLICY_REPORTSNAPSHOT   = TEXT('ReportSnapshot');
  {$EXTERNALSYM REGSTR_PATH_RELIABILITY_POLICY_REPORTSNAPSHOT}
  REGSTR_PATH_REINSTALL            = 'SOFTWARE\Microsoft\Windows\CurrentVersion\Reinstall';
  {$EXTERNALSYM REGSTR_PATH_REINSTALL}
  REGSTR_PATH_NT_CURRENTVERSION    = 'Software\Microsoft\Windows NT\CurrentVersion';
  {$EXTERNALSYM REGSTR_PATH_NT_CURRENTVERSION}

  REGSTR_PATH_VOLUMECACHE = 'Software\Microsoft\Windows\CurrentVersion\Explorer\VolumeCaches';
  {$EXTERNALSYM REGSTR_PATH_VOLUMECACHE}
  REGSTR_VAL_DISPLAY      = 'display';
  {$EXTERNALSYM REGSTR_VAL_DISPLAY}

  REGSTR_PATH_IDCONFIGDB             = 'System\CurrentControlSet\Control\IDConfigDB';
  {$EXTERNALSYM REGSTR_PATH_IDCONFIGDB}
  REGSTR_PATH_CRITICALDEVICEDATABASE = 'System\CurrentControlSet\Control\CriticalDeviceDatabase';
  {$EXTERNALSYM REGSTR_PATH_CRITICALDEVICEDATABASE}
  REGSTR_PATH_CLASS                  = 'System\CurrentControlSet\Services\Class';
  {$EXTERNALSYM REGSTR_PATH_CLASS}
  REGSTR_PATH_DISPLAYSETTINGS        = 'Display\Settings';
  {$EXTERNALSYM REGSTR_PATH_DISPLAYSETTINGS}
  REGSTR_PATH_FONTS                  = 'Display\Fonts';
  {$EXTERNALSYM REGSTR_PATH_FONTS}
  REGSTR_PATH_ENUM                   = 'Enum';
  {$EXTERNALSYM REGSTR_PATH_ENUM}
  REGSTR_PATH_ROOT                   = 'Enum\Root';
  {$EXTERNALSYM REGSTR_PATH_ROOT}

  REGSTR_PATH_CURRENTCONTROLSET = 'System\CurrentControlSet';
  {$EXTERNALSYM REGSTR_PATH_CURRENTCONTROLSET}
  REGSTR_PATH_SYSTEMENUM        = 'System\CurrentControlSet\Enum';
  {$EXTERNALSYM REGSTR_PATH_SYSTEMENUM}
  REGSTR_PATH_HWPROFILES        = 'System\CurrentControlSet\Hardware Profiles';
  {$EXTERNALSYM REGSTR_PATH_HWPROFILES}
  REGSTR_PATH_HWPROFILESCURRENT = 'System\CurrentControlSet\Hardware Profiles\Current';
  {$EXTERNALSYM REGSTR_PATH_HWPROFILESCURRENT}
  REGSTR_PATH_CLASS_NT          = 'System\CurrentControlSet\Control\Class';
  {$EXTERNALSYM REGSTR_PATH_CLASS_NT}
  REGSTR_PATH_PER_HW_ID_STORAGE = 'Software\Microsoft\Windows NT\CurrentVersion\PerHwIdStorage';
  {$EXTERNALSYM REGSTR_PATH_PER_HW_ID_STORAGE}

  REGSTR_PATH_DEVICE_CLASSES = 'System\CurrentControlSet\Control\DeviceClasses';
  {$EXTERNALSYM REGSTR_PATH_DEVICE_CLASSES}

  REGSTR_PATH_CODEVICEINSTALLERS = 'System\CurrentControlSet\Control\CoDeviceInstallers';
  {$EXTERNALSYM REGSTR_PATH_CODEVICEINSTALLERS}
  REGSTR_PATH_BUSINFORMATION     = 'System\CurrentControlSet\Control\PnP\BusInformation';
  {$EXTERNALSYM REGSTR_PATH_BUSINFORMATION}

  REGSTR_PATH_SERVICES  = 'System\CurrentControlSet\Services';
  {$EXTERNALSYM REGSTR_PATH_SERVICES}
  REGSTR_PATH_VXD       = 'System\CurrentControlSet\Services\VxD';
  {$EXTERNALSYM REGSTR_PATH_VXD}
  REGSTR_PATH_IOS       = 'System\CurrentControlSet\Services\VxD\IOS';
  {$EXTERNALSYM REGSTR_PATH_IOS}
  REGSTR_PATH_VMM       = 'System\CurrentControlSet\Services\VxD\VMM';
  {$EXTERNALSYM REGSTR_PATH_VMM}
  REGSTR_PATH_VPOWERD   = 'System\CurrentControlSet\Services\VxD\VPOWERD';
  {$EXTERNALSYM REGSTR_PATH_VPOWERD}
  REGSTR_PATH_VNETSUP   = 'System\CurrentControlSet\Services\VxD\VNETSUP';
  {$EXTERNALSYM REGSTR_PATH_VNETSUP}
  REGSTR_PATH_NWREDIR   = 'System\CurrentControlSet\Services\VxD\NWREDIR';
  {$EXTERNALSYM REGSTR_PATH_NWREDIR}
  REGSTR_PATH_NCPSERVER = 'System\CurrentControlSet\Services\NcpServer\Parameters';
  {$EXTERNALSYM REGSTR_PATH_NCPSERVER}
  REGSTR_PATH_VCOMM     = 'System\CurrentControlSet\Services\VxD\VCOMM';
  {$EXTERNALSYM REGSTR_PATH_VCOMM}

  REGSTR_PATH_IOARB   = 'System\CurrentControlSet\Services\Arbitrators\IOArb';
  {$EXTERNALSYM REGSTR_PATH_IOARB}
  REGSTR_PATH_ADDRARB = 'System\CurrentControlSet\Services\Arbitrators\AddrArb';
  {$EXTERNALSYM REGSTR_PATH_ADDRARB}
  REGSTR_PATH_DMAARB  = 'System\CurrentControlSet\Services\Arbitrators\DMAArb';
  {$EXTERNALSYM REGSTR_PATH_DMAARB}
  REGSTR_PATH_IRQARB  = 'System\CurrentControlSet\Services\Arbitrators\IRQArb';
  {$EXTERNALSYM REGSTR_PATH_IRQARB}

  REGSTR_PATH_CODEPAGE              = 'System\CurrentControlSet\Control\Nls\Codepage';
  {$EXTERNALSYM REGSTR_PATH_CODEPAGE}
  REGSTR_PATH_FILESYSTEM            = 'System\CurrentControlSet\Control\FileSystem';
  {$EXTERNALSYM REGSTR_PATH_FILESYSTEM}
  REGSTR_PATH_FILESYSTEM_NOVOLTRACK = 'System\CurrentControlSet\Control\FileSystem\NoVolTrack';
  {$EXTERNALSYM REGSTR_PATH_FILESYSTEM_NOVOLTRACK}
  REGSTR_PATH_CDFS                  = 'System\CurrentControlSet\Control\FileSystem\CDFS';
  {$EXTERNALSYM REGSTR_PATH_CDFS}
  REGSTR_PATH_WINBOOT               = 'System\CurrentControlSet\Control\WinBoot';
  {$EXTERNALSYM REGSTR_PATH_WINBOOT}
  REGSTR_PATH_INSTALLEDFILES        = 'System\CurrentControlSet\Control\InstalledFiles';
  {$EXTERNALSYM REGSTR_PATH_INSTALLEDFILES}
  REGSTR_PATH_VMM32FILES            = 'System\CurrentControlSet\Control\VMM32Files';
  {$EXTERNALSYM REGSTR_PATH_VMM32FILES}

//
// Reasonable Limit for Values Names
//

  REGSTR_MAX_VALUE_LENGTH = 256;
  {$EXTERNALSYM REGSTR_MAX_VALUE_LENGTH}

//
// Values used by user mode Pnp Manager
//

  REGSTR_KEY_DEVICE_PROPERTIES          = 'Properties';
  {$EXTERNALSYM REGSTR_KEY_DEVICE_PROPERTIES}
  REGSTR_VAL_SLOTNUMBER                 = 'SlotNumber';
  {$EXTERNALSYM REGSTR_VAL_SLOTNUMBER}
  REGSTR_VAL_ATTACHEDCOMPONENTS         = 'AttachedComponents';
  {$EXTERNALSYM REGSTR_VAL_ATTACHEDCOMPONENTS}
  REGSTR_VAL_BASEDEVICEPATH             = 'BaseDevicePath';
  {$EXTERNALSYM REGSTR_VAL_BASEDEVICEPATH}
  REGSTR_VAL_SYSTEMBUSNUMBER            = 'SystemBusNumber';
  {$EXTERNALSYM REGSTR_VAL_SYSTEMBUSNUMBER}
  REGSTR_VAL_BUSDATATYPE                = 'BusDataType';
  {$EXTERNALSYM REGSTR_VAL_BUSDATATYPE}
  REGSTR_VAL_INTERFACETYPE              = 'InterfaceType';
  {$EXTERNALSYM REGSTR_VAL_INTERFACETYPE}
  REGSTR_VAL_SERVICE                    = 'Service';
  {$EXTERNALSYM REGSTR_VAL_SERVICE}
  REGSTR_VAL_DETECTSIGNATURE            = 'DetectSignature';
  {$EXTERNALSYM REGSTR_VAL_DETECTSIGNATURE}
  REGSTR_VAL_CLASSGUID                  = 'ClassGUID';
  {$EXTERNALSYM REGSTR_VAL_CLASSGUID}
  REGSTR_VAL_INSTANCEIDENTIFIER         = 'InstanceIdentifier';
  {$EXTERNALSYM REGSTR_VAL_INSTANCEIDENTIFIER}
  REGSTR_VAL_DUPLICATEOF                = 'DuplicateOf';
  {$EXTERNALSYM REGSTR_VAL_DUPLICATEOF}
  REGSTR_VAL_STATUSFLAGS                = 'StatusFlags';
  {$EXTERNALSYM REGSTR_VAL_STATUSFLAGS}
  REGSTR_VAL_DISABLECOUNT               = 'DisableCount';
  {$EXTERNALSYM REGSTR_VAL_DISABLECOUNT}
  REGSTR_VAL_UNKNOWNPROBLEMS            = 'UnknownProblem';
  {$EXTERNALSYM REGSTR_VAL_UNKNOWNPROBLEMS}
  REGSTR_VAL_DOCKSTATE                  = 'DockState';
  {$EXTERNALSYM REGSTR_VAL_DOCKSTATE}
  REGSTR_VAL_PREFERENCEORDER            = 'PreferenceOrder';
  {$EXTERNALSYM REGSTR_VAL_PREFERENCEORDER}
  REGSTR_VAL_USERWAITINTERVAL           = 'UserWaitInterval';
  {$EXTERNALSYM REGSTR_VAL_USERWAITINTERVAL}
  REGSTR_VAL_DEVICE_INSTANCE            = 'DeviceInstance';
  {$EXTERNALSYM REGSTR_VAL_DEVICE_INSTANCE}
  REGSTR_VAL_SYMBOLIC_LINK              = 'SymbolicLink';
  {$EXTERNALSYM REGSTR_VAL_SYMBOLIC_LINK}
  REGSTR_VAL_DEFAULT                    = 'Default';
  {$EXTERNALSYM REGSTR_VAL_DEFAULT}
  REGSTR_VAL_LOWERFILTERS               = 'LowerFilters';
  {$EXTERNALSYM REGSTR_VAL_LOWERFILTERS}
  REGSTR_VAL_UPPERFILTERS               = 'UpperFilters';
  {$EXTERNALSYM REGSTR_VAL_UPPERFILTERS}
  REGSTR_VAL_LOCATION_INFORMATION       = 'LocationInformation';
  {$EXTERNALSYM REGSTR_VAL_LOCATION_INFORMATION}
  REGSTR_VAL_UI_NUMBER                  = 'UINumber';
  {$EXTERNALSYM REGSTR_VAL_UI_NUMBER}
  REGSTR_VAL_UI_NUMBER_DESC_FORMAT      = 'UINumberDescFormat';
  {$EXTERNALSYM REGSTR_VAL_UI_NUMBER_DESC_FORMAT}
  REGSTR_VAL_CAPABILITIES               = 'Capabilities';
  {$EXTERNALSYM REGSTR_VAL_CAPABILITIES}
  REGSTR_VAL_DEVICE_TYPE                = 'DeviceType';
  {$EXTERNALSYM REGSTR_VAL_DEVICE_TYPE}
  REGSTR_VAL_DEVICE_CHARACTERISTICS     = 'DeviceCharacteristics';
  {$EXTERNALSYM REGSTR_VAL_DEVICE_CHARACTERISTICS}
  REGSTR_VAL_DEVICE_SECURITY_DESCRIPTOR = 'Security';
  {$EXTERNALSYM REGSTR_VAL_DEVICE_SECURITY_DESCRIPTOR}
  REGSTR_VAL_DEVICE_EXCLUSIVE           = 'Exclusive';
  {$EXTERNALSYM REGSTR_VAL_DEVICE_EXCLUSIVE}
  REGSTR_VAL_RESOURCE_PICKER_TAGS       = 'ResourcePickerTags';
  {$EXTERNALSYM REGSTR_VAL_RESOURCE_PICKER_TAGS}
  REGSTR_VAL_RESOURCE_PICKER_EXCEPTIONS = 'ResourcePickerExceptions';
  {$EXTERNALSYM REGSTR_VAL_RESOURCE_PICKER_EXCEPTIONS}
  REGSTR_VAL_CUSTOM_PROPERTY_CACHE_DATE = 'CustomPropertyCacheDate';
  {$EXTERNALSYM REGSTR_VAL_CUSTOM_PROPERTY_CACHE_DATE}
  REGSTR_VAL_CUSTOM_PROPERTY_HW_ID_KEY  = 'CustomPropertyHwIdKey';
  {$EXTERNALSYM REGSTR_VAL_CUSTOM_PROPERTY_HW_ID_KEY}
  REGSTR_VAL_LAST_UPDATE_TIME           = 'LastUpdateTime';
  {$EXTERNALSYM REGSTR_VAL_LAST_UPDATE_TIME}

//
// Values used by kernel mode Pnp Manager
//

  REGSTR_VALUE_DEVICE_OBJECT_NAME   = 'DeviceObjectName';
  {$EXTERNALSYM REGSTR_VALUE_DEVICE_OBJECT_NAME}
  REGSTR_VALUE_DEVICE_SYMBOLIC_NAME = 'DeviceSymbolicName';
  {$EXTERNALSYM REGSTR_VALUE_DEVICE_SYMBOLIC_NAME}
  REGSTR_VAL_EJECT_PRIORITY         = 'EjectPriority';

//
// Values used by both kernel-mode and user-mode PnP Managers
//

  REGSTR_KEY_CONTROL              = 'Control';
  {$EXTERNALSYM REGSTR_KEY_CONTROL}
  REGSTR_VAL_ACTIVESERVICE        = 'ActiveService';
  {$EXTERNALSYM REGSTR_VAL_ACTIVESERVICE}
  REGSTR_VAL_LINKED               = 'Linked';
  {$EXTERNALSYM REGSTR_VAL_LINKED}
  REGSTR_VAL_PHYSICALDEVICEOBJECT = 'PhysicalDeviceObject';
  {$EXTERNALSYM REGSTR_VAL_PHYSICALDEVICEOBJECT}
  REGSTR_VAL_REMOVAL_POLICY       = 'RemovalPolicy';
  {$EXTERNALSYM REGSTR_VAL_REMOVAL_POLICY}

//
// Values under REGSTR_PATH_NT_CURRENTVERSION
//

  REGSTR_VAL_CURRENT_VERSION    = 'CurrentVersion';
  {$EXTERNALSYM REGSTR_VAL_CURRENT_VERSION}
  REGSTR_VAL_CURRENT_BUILD      = 'CurrentBuildNumber';
  {$EXTERNALSYM REGSTR_VAL_CURRENT_BUILD}
  REGSTR_VAL_CURRENT_CSDVERSION = 'CSDVersion';
  {$EXTERNALSYM REGSTR_VAL_CURRENT_CSDVERSION}
  REGSTR_VAL_CURRENT_TYPE       = 'CurrentType';
  {$EXTERNALSYM REGSTR_VAL_CURRENT_TYPE}

//
// Values under REGSTR_PATH_DISPLAYSETTINGS
//

  REGSTR_VAL_BITSPERPIXEL = 'BitsPerPixel';
  {$EXTERNALSYM REGSTR_VAL_BITSPERPIXEL}
  REGSTR_VAL_RESOLUTION   = 'Resolution';
  {$EXTERNALSYM REGSTR_VAL_RESOLUTION}
  REGSTR_VAL_DPILOGICALX  = 'DPILogicalX';
  {$EXTERNALSYM REGSTR_VAL_DPILOGICALX}
  REGSTR_VAL_DPILOGICALY  = 'DPILogicalY';
  {$EXTERNALSYM REGSTR_VAL_DPILOGICALY}
  REGSTR_VAL_DPIPHYSICALX = 'DPIPhysicalX';
  {$EXTERNALSYM REGSTR_VAL_DPIPHYSICALX}
  REGSTR_VAL_DPIPHYSICALY = 'DPIPhysicalY';
  {$EXTERNALSYM REGSTR_VAL_DPIPHYSICALY}
  REGSTR_VAL_REFRESHRATE  = 'RefreshRate';
  {$EXTERNALSYM REGSTR_VAL_REFRESHRATE}
  REGSTR_VAL_DISPLAYFLAGS = 'DisplayFlags';
  {$EXTERNALSYM REGSTR_VAL_DISPLAYFLAGS}


// under HKEY_CURRENT_USER

  REGSTR_PATH_CONTROLPANEL = 'Control Panel';
  {$EXTERNALSYM REGSTR_PATH_CONTROLPANEL}

// under HKEY_LOCAL_MACHINE

  REGSTR_PATH_CONTROLSFOLDER = 'Software\Microsoft\Windows\CurrentVersion\Controls Folder';
  {$EXTERNALSYM REGSTR_PATH_CONTROLSFOLDER}

//
// Entries under REGSTR_PATH_CODEPAGE
//

  REGSTR_VAL_DOSCP = 'OEMCP';
  {$EXTERNALSYM REGSTR_VAL_DOSCP}
  REGSTR_VAL_WINCP = 'ACP';
  {$EXTERNALSYM REGSTR_VAL_WINCP}

  REGSTR_PATH_DYNA_ENUM = 'Config Manager\Enum';
  {$EXTERNALSYM REGSTR_PATH_DYNA_ENUM}

//
// Entries under REGSTR_PATH_DYNA_ENUM
//

  REGSTR_VAL_HARDWARE_KEY = 'HardWareKey';
  {$EXTERNALSYM REGSTR_VAL_HARDWARE_KEY}
  REGSTR_VAL_ALLOCATION   = 'Allocation';
  {$EXTERNALSYM REGSTR_VAL_ALLOCATION}
  REGSTR_VAL_PROBLEM      = 'Problem';
  {$EXTERNALSYM REGSTR_VAL_PROBLEM}
  REGSTR_VAL_STATUS       = 'Status';
  {$EXTERNALSYM REGSTR_VAL_STATUS}

//
//  Used by address arbitrator
//

  REGSTR_VAL_DONTUSEMEM = 'DontAllocLastMem';
  {$EXTERNALSYM REGSTR_VAL_DONTUSEMEM}

//
//  Entries under REGSTR_PATH_SETUP
//

  REGSTR_VAL_SYSTEMROOT      = 'SystemRoot';
  {$EXTERNALSYM REGSTR_VAL_SYSTEMROOT}
  REGSTR_VAL_BOOTCOUNT       = 'BootCount';
  {$EXTERNALSYM REGSTR_VAL_BOOTCOUNT}
  REGSTR_VAL_REALNETSTART    = 'RealNetStart';
  {$EXTERNALSYM REGSTR_VAL_REALNETSTART}
  REGSTR_VAL_MEDIA           = 'MediaPath';
  {$EXTERNALSYM REGSTR_VAL_MEDIA}
  REGSTR_VAL_CONFIG          = 'ConfigPath';
  {$EXTERNALSYM REGSTR_VAL_CONFIG}
  REGSTR_VAL_DEVICEPATH      = 'DevicePath'; // default search path for .INFs
  {$EXTERNALSYM REGSTR_VAL_DEVICEPATH}
  REGSTR_VAL_SRCPATH         = 'SourcePath'; // last source files path during setup.
  {$EXTERNALSYM REGSTR_VAL_SRCPATH}
  REGSTR_VAL_SVCPAKSRCPATH   = 'ServicePackSourcePath'; // last service pack source path
  {$EXTERNALSYM REGSTR_VAL_SVCPAKSRCPATH}
  REGSTR_VAL_DRIVERCACHEPATH = 'DriverCachePath'; // location of driver cache
  {$EXTERNALSYM REGSTR_VAL_DRIVERCACHEPATH}

  REGSTR_VAL_OLDWINDIR            = 'OldWinDir'; // old windows location
  {$EXTERNALSYM REGSTR_VAL_OLDWINDIR}
  REGSTR_VAL_SETUPFLAGS           = 'SetupFlags'; // flags that setup passes on after install.
  {$EXTERNALSYM REGSTR_VAL_SETUPFLAGS}
  REGSTR_VAL_REGOWNER             = 'RegisteredOwner';
  {$EXTERNALSYM REGSTR_VAL_REGOWNER}
  REGSTR_VAL_REGORGANIZATION      = 'RegisteredOrganization';
  {$EXTERNALSYM REGSTR_VAL_REGORGANIZATION}
  REGSTR_VAL_LICENSINGINFO        = 'LicensingInfo';
  {$EXTERNALSYM REGSTR_VAL_LICENSINGINFO}
  REGSTR_VAL_OLDMSDOSVER          = 'OldMSDOSVer'; // will be DOS ver < 7 (when Setup run)
  {$EXTERNALSYM REGSTR_VAL_OLDMSDOSVER}
  REGSTR_VAL_FIRSTINSTALLDATETIME = 'FirstInstallDateTime'; // will Win 95 install date-time
  {$EXTERNALSYM REGSTR_VAL_FIRSTINSTALLDATETIME}

  REGSTR_VAL_INSTALLTYPE = 'InstallType';
  {$EXTERNALSYM REGSTR_VAL_INSTALLTYPE}

  //  Values for InstallType

  IT_COMPACT         = $0000;
  {$EXTERNALSYM IT_COMPACT}
  IT_TYPICAL         = $0001;
  {$EXTERNALSYM IT_TYPICAL}
  IT_PORTABLE        = $0002;
  {$EXTERNALSYM IT_PORTABLE}
  IT_CUSTOM          = $0003;
  {$EXTERNALSYM IT_CUSTOM}

  REGSTR_VAL_WRAPPER = 'Wrapper';
  {$EXTERNALSYM REGSTR_VAL_WRAPPER}

  REGSTR_VAL_LASTALIVEINTERVAL = 'TimeStampInterval';
  {$EXTERNALSYM REGSTR_VAL_LASTALIVEINTERVAL}
  REGSTR_VAL_LASTALIVESTAMP    = 'LastAliveStamp';
  {$EXTERNALSYM REGSTR_VAL_LASTALIVESTAMP}
  REGSTR_VAL_LASTALIVEUPTIME   =  TEXT('LastAliveUptime');
  {$EXTERNALSYM REGSTR_VAL_LASTALIVEUPTIME}
  REGSTR_VAL_SHUTDOWNREASON    = 'ShutdownReason';
  {$EXTERNALSYM REGSTR_VAL_SHUTDOWNREASON}
  REGSTR_VAL_SHUTDOWNREASON_CODE        = 'ShutdownReasonCode';
  {$EXTERNALSYM REGSTR_VAL_SHUTDOWNREASON_CODE}
  REGSTR_VAL_SHUTDOWNREASON_COMMENT     = 'ShutdownReasonComment';
  {$EXTERNALSYM REGSTR_VAL_SHUTDOWNREASON_COMMENT}
  REGSTR_VAL_SHUTDOWNREASON_PROCESS     = 'ShutdownReasonProcess';
  {$EXTERNALSYM REGSTR_VAL_SHUTDOWNREASON_PROCESS}
  REGSTR_VAL_SHUTDOWNREASON_USERNAME    = 'ShutdownReasonUserName';
  {$EXTERNALSYM REGSTR_VAL_SHUTDOWNREASON_USERNAME}
  REGSTR_VAL_SHOWREASONUI               = 'ShutdownReasonUI';
  {$EXTERNALSYM REGSTR_VAL_SHOWREASONUI}
  REGSTR_VAL_SHUTDOWN_IGNORE_PREDEFINED = 'ShutdownIgnorePredefinedReasons';
  {$EXTERNALSYM REGSTR_VAL_SHUTDOWN_IGNORE_PREDEFINED}
  REGSTR_VAL_SHUTDOWN_STATE_SNAPSHOT = 'ShutdownStateSnapshot';
  {$EXTERNALSYM REGSTR_VAL_SHUTDOWN_STATE_SNAPSHOT}

  REGSTR_KEY_SETUP      = '\Setup';
  {$EXTERNALSYM REGSTR_KEY_SETUP}
  REGSTR_VAL_BOOTDIR    = 'BootDir';
  {$EXTERNALSYM REGSTR_VAL_BOOTDIR}
  REGSTR_VAL_WINBOOTDIR = 'WinbootDir';
  {$EXTERNALSYM REGSTR_VAL_WINBOOTDIR}
  REGSTR_VAL_WINDIR     = 'WinDir';
  {$EXTERNALSYM REGSTR_VAL_WINDIR}

  REGSTR_VAL_APPINSTPATH = 'AppInstallPath'; // Used by install wizard
  {$EXTERNALSYM REGSTR_VAL_APPINSTPATH}

// Values for international startup disk

  REGSTR_PATH_EBD = REGSTR_PATH_SETUP + REGSTR_KEY_SETUP + '\EBD';
  {$EXTERNALSYM REGSTR_PATH_EBD}

// Keys under REGSTR_KEY_EBD

  REGSTR_KEY_EBDFILESLOCAL          = 'EBDFilesLocale';
  {$EXTERNALSYM REGSTR_KEY_EBDFILESLOCAL}
  REGSTR_KEY_EBDFILESKEYBOARD       = 'EBDFilesKeyboard';
  {$EXTERNALSYM REGSTR_KEY_EBDFILESKEYBOARD}
  REGSTR_KEY_EBDAUTOEXECBATLOCAL    = 'EBDAutoexecBatLocale';
  {$EXTERNALSYM REGSTR_KEY_EBDAUTOEXECBATLOCAL}
  REGSTR_KEY_EBDAUTOEXECBATKEYBOARD = 'EBDAutoexecBatKeyboard';
  {$EXTERNALSYM REGSTR_KEY_EBDAUTOEXECBATKEYBOARD}
  REGSTR_KEY_EBDCONFIGSYSLOCAL      = 'EBDConfigSysLocale';
  {$EXTERNALSYM REGSTR_KEY_EBDCONFIGSYSLOCAL}
  REGSTR_KEY_EBDCONFIGSYSKEYBOARD   = 'EBDConfigSysKeyboard';
  {$EXTERNALSYM REGSTR_KEY_EBDCONFIGSYSKEYBOARD}


// Values under REGSTR_PATH_DRIVERSIGN and REGSTR_PATH_NONDRIVERSIGN

  REGSTR_VAL_POLICY = 'Policy';
  {$EXTERNALSYM REGSTR_VAL_POLICY}

// Values under REGSTR_PATH_DRIVERSIGN_POLICY and REGSTR_PATH_NONDRIVERSIGN_POLICY

  REGSTR_VAL_BEHAVIOR_ON_FAILED_VERIFY = 'BehaviorOnFailedVerify';
  {$EXTERNALSYM REGSTR_VAL_BEHAVIOR_ON_FAILED_VERIFY}

// Types of driver signing policies (apply to both preference and policy values
// defined above)

  DRIVERSIGN_NONE     = $00000000;
  {$EXTERNALSYM DRIVERSIGN_NONE}
  DRIVERSIGN_WARNING  = $00000001;
  {$EXTERNALSYM DRIVERSIGN_WARNING}
  DRIVERSIGN_BLOCKING = $00000002;
  {$EXTERNALSYM DRIVERSIGN_BLOCKING}

//
//  Entries under REGSTR_PATH_PIFCONVERT
//

  REGSTR_VAL_MSDOSMODE        = 'MSDOSMode';
  {$EXTERNALSYM REGSTR_VAL_MSDOSMODE}
  REGSTR_VAL_MSDOSMODEDISCARD = 'Discard';
  {$EXTERNALSYM REGSTR_VAL_MSDOSMODEDISCARD}

//
//  Entries under REGSTR_PATH_MSDOSOPTS (global settings)
//

  REGSTR_VAL_DOSOPTGLOBALFLAGS = 'GlobalFlags';
  {$EXTERNALSYM REGSTR_VAL_DOSOPTGLOBALFLAGS}

//  Flags for GlobalFlags

  DOSOPTGF_DEFCLEAN = $00000001; // Default action is clean config
  {$EXTERNALSYM DOSOPTGF_DEFCLEAN}

//
//  Entries under REGSTR_PATH_MSDOSOPTS \ OptionSubkey
//

  REGSTR_VAL_DOSOPTFLAGS  = 'Flags';
  {$EXTERNALSYM REGSTR_VAL_DOSOPTFLAGS}
  REGSTR_VAL_OPTORDER     = 'Order';
  {$EXTERNALSYM REGSTR_VAL_OPTORDER}
  REGSTR_VAL_CONFIGSYS    = 'Config.Sys';
  {$EXTERNALSYM REGSTR_VAL_CONFIGSYS}
  REGSTR_VAL_AUTOEXEC     = 'Autoexec.Bat';
  {$EXTERNALSYM REGSTR_VAL_AUTOEXEC}
  REGSTR_VAL_STDDOSOPTION = 'StdOption';
  {$EXTERNALSYM REGSTR_VAL_STDDOSOPTION}
  REGSTR_VAL_DOSOPTTIP    = 'TipText';
  {$EXTERNALSYM REGSTR_VAL_DOSOPTTIP}

//  Flags for DOSOPTFLAGS

  DOSOPTF_DEFAULT     = $00000001; // Default enabled for clean config
  {$EXTERNALSYM DOSOPTF_DEFAULT}
  DOSOPTF_SUPPORTED   = $00000002; // Option actually supported
  {$EXTERNALSYM DOSOPTF_SUPPORTED}
  DOSOPTF_ALWAYSUSE   = $00000004; // Always use this option
  {$EXTERNALSYM DOSOPTF_ALWAYSUSE}
  DOSOPTF_USESPMODE   = $00000008; // Option puts machine in Prot Mode
  {$EXTERNALSYM DOSOPTF_USESPMODE}
  DOSOPTF_PROVIDESUMB = $00000010; // Can load drivers high
  {$EXTERNALSYM DOSOPTF_PROVIDESUMB}
  DOSOPTF_NEEDSETUP   = $00000020; // Need to configure option
  {$EXTERNALSYM DOSOPTF_NEEDSETUP}
  DOSOPTF_INDOSSTART  = $00000040; // Suppored by DOSSTART.BAT
  {$EXTERNALSYM DOSOPTF_INDOSSTART}
  DOSOPTF_MULTIPLE    = $00000080; // Load multiple configuration lines
  {$EXTERNALSYM DOSOPTF_MULTIPLE}

//
//  Flags returned by SUGetSetSetupFlags and in the registry
//

  SUF_FIRSTTIME  = $00000001; // First boot into Win95.
  {$EXTERNALSYM SUF_FIRSTTIME}
  SUF_EXPRESS    = $00000002; // User Setup via express mode (vs customize).
  {$EXTERNALSYM SUF_EXPRESS}
  SUF_BATCHINF   = $00000004; // Setup using batch file (MSBATCH.INF).
  {$EXTERNALSYM SUF_BATCHINF}
  SUF_CLEAN      = $00000008; // Setup was done to a clean directory.
  {$EXTERNALSYM SUF_CLEAN}
  SUF_INSETUP    = $00000010; // You're in Setup.
  {$EXTERNALSYM SUF_INSETUP}
  SUF_NETSETUP   = $00000020; // Doing a net (workstation) setup.
  {$EXTERNALSYM SUF_NETSETUP}
  SUF_NETHDBOOT  = $00000040; // Workstation boots from local harddrive
  {$EXTERNALSYM SUF_NETHDBOOT}
  SUF_NETRPLBOOT = $00000080; // Workstation boots via RPL (vs floppy)
  {$EXTERNALSYM SUF_NETRPLBOOT}
  SUF_SBSCOPYOK  = $00000100; // Can copy to LDID_SHARED (SBS)
  {$EXTERNALSYM SUF_SBSCOPYOK}

//
//  Entries under REGSTR_PATH_VMM
//

  REGSTR_VAL_DOSPAGER  = 'DOSPager';
  {$EXTERNALSYM REGSTR_VAL_DOSPAGER}
  REGSTR_VAL_VXDGROUPS = 'VXDGroups';
  {$EXTERNALSYM REGSTR_VAL_VXDGROUPS}

//
//  Entries under REGSTR_PATH_VPOWERD
//

  REGSTR_VAL_VPOWERDFLAGS   = 'Flags';
  {$EXTERNALSYM REGSTR_VAL_VPOWERDFLAGS}
  VPDF_DISABLEPWRMGMT       = $00000001; // Don't load device
  {$EXTERNALSYM VPDF_DISABLEPWRMGMT}
  VPDF_FORCEAPM10MODE       = $00000002; // Always go into 1.0 mode
  {$EXTERNALSYM VPDF_FORCEAPM10MODE}
  VPDF_SKIPINTELSLCHECK     = $00000004; // Don't detect Intel SL chipset
  {$EXTERNALSYM VPDF_SKIPINTELSLCHECK}
  VPDF_DISABLEPWRSTATUSPOLL = $00000008; // Don't poll power status
  {$EXTERNALSYM VPDF_DISABLEPWRSTATUSPOLL}
  VPDF_DISABLERINGRESUME    = $00000010; // Don't let the modem wake the machine (APM 1.2 only)
  {$EXTERNALSYM VPDF_DISABLERINGRESUME}
  VPDF_SHOWMULTIBATT        = $00000020; // Show all batteries checkbox in power control panel
  {$EXTERNALSYM VPDF_SHOWMULTIBATT}

//
// Entries under REGSTR_PATH_BUSINFORMATION
//

  BIF_SHOWSIMILARDRIVERS     = $00000001;  // Show similar drivers instead of all class drivers in UI.
  {$EXTERNALSYM BIF_SHOWSIMILARDRIVERS}
  BIF_RAWDEVICENEEDSDRIVER   = $00000002;  // RAW device needs a driver installed.
  {$EXTERNALSYM BIF_RAWDEVICENEEDSDRIVER}

//
//  Entries under REGSTR_PATH_VNETSUP
//

  REGSTR_VAL_WORKGROUP    = 'Workgroup';
  {$EXTERNALSYM REGSTR_VAL_WORKGROUP}
  REGSTR_VAL_DIRECTHOST   = 'DirectHost';
  {$EXTERNALSYM REGSTR_VAL_DIRECTHOST}
  REGSTR_VAL_FILESHARING  = 'FileSharing';
  {$EXTERNALSYM REGSTR_VAL_FILESHARING}
  REGSTR_VAL_PRINTSHARING = 'PrintSharing';
  {$EXTERNALSYM REGSTR_VAL_PRINTSHARING}

//
//  Entries under REGSTR_PATH_NWREDIR
//

  REGSTR_VAL_FIRSTNETDRIVE     = 'FirstNetworkDrive';
  {$EXTERNALSYM REGSTR_VAL_FIRSTNETDRIVE}
  REGSTR_VAL_MAXCONNECTIONS    = 'MaxConnections';
  {$EXTERNALSYM REGSTR_VAL_MAXCONNECTIONS}
  REGSTR_VAL_APISUPPORT        = 'APISupport';
  {$EXTERNALSYM REGSTR_VAL_APISUPPORT}
  REGSTR_VAL_MAXRETRY          = 'MaxRetry';
  {$EXTERNALSYM REGSTR_VAL_MAXRETRY}
  REGSTR_VAL_MINRETRY          = 'MinRetry';
  {$EXTERNALSYM REGSTR_VAL_MINRETRY}
  REGSTR_VAL_SUPPORTLFN        = 'SupportLFN';
  {$EXTERNALSYM REGSTR_VAL_SUPPORTLFN}
  REGSTR_VAL_SUPPORTBURST      = 'SupportBurst';
  {$EXTERNALSYM REGSTR_VAL_SUPPORTBURST}
  REGSTR_VAL_SUPPORTTUNNELLING = 'SupportTunnelling';
  {$EXTERNALSYM REGSTR_VAL_SUPPORTTUNNELLING}
  REGSTR_VAL_FULLTRACE         = 'FullTrace';
  {$EXTERNALSYM REGSTR_VAL_FULLTRACE}
  REGSTR_VAL_READCACHING       = 'ReadCaching';
  {$EXTERNALSYM REGSTR_VAL_READCACHING}
  REGSTR_VAL_SHOWDOTS          = 'ShowDots';
  {$EXTERNALSYM REGSTR_VAL_SHOWDOTS}
  REGSTR_VAL_GAPTIME           = 'GapTime';
  {$EXTERNALSYM REGSTR_VAL_GAPTIME}
  REGSTR_VAL_SEARCHMODE        = 'SearchMode';
  {$EXTERNALSYM REGSTR_VAL_SEARCHMODE}
  REGSTR_VAL_SHELLVERSION      = 'ShellVersion';
  {$EXTERNALSYM REGSTR_VAL_SHELLVERSION}
  REGSTR_VAL_MAXLIP            = 'MaxLIP';
  {$EXTERNALSYM REGSTR_VAL_MAXLIP}
  REGSTR_VAL_PRESERVECASE      = 'PreserveCase';
  {$EXTERNALSYM REGSTR_VAL_PRESERVECASE}
  REGSTR_VAL_OPTIMIZESFN       = 'OptimizeSFN';
  {$EXTERNALSYM REGSTR_VAL_OPTIMIZESFN}

//
//  Entries under REGSTR_PATH_NCPSERVER
//

  REGSTR_VAL_NCP_BROWSEMASTER    = 'BrowseMaster';
  {$EXTERNALSYM REGSTR_VAL_NCP_BROWSEMASTER}
  REGSTR_VAL_NCP_USEPEERBROWSING = 'Use_PeerBrowsing';
  {$EXTERNALSYM REGSTR_VAL_NCP_USEPEERBROWSING}
  REGSTR_VAL_NCP_USESAP          = 'Use_Sap';
  {$EXTERNALSYM REGSTR_VAL_NCP_USESAP}

//
// Entries under REGSTR_PATH_VCOMM
//

  REGSTR_VAL_PCCARD_POWER = 'EnablePowerManagement';
  {$EXTERNALSYM REGSTR_VAL_PCCARD_POWER}

//
//  Entries under REGSTR_PATH_FILESYSTEM
//

  REGSTR_VAL_WIN31FILESYSTEM      = 'Win31FileSystem';
  {$EXTERNALSYM REGSTR_VAL_WIN31FILESYSTEM}
  REGSTR_VAL_PRESERVELONGNAMES    = 'PreserveLongNames';
  {$EXTERNALSYM REGSTR_VAL_PRESERVELONGNAMES}
  REGSTR_VAL_DRIVEWRITEBEHIND     = 'DriveWriteBehind';
  {$EXTERNALSYM REGSTR_VAL_DRIVEWRITEBEHIND}
  REGSTR_VAL_ASYNCFILECOMMIT      = 'AsyncFileCommit';
  {$EXTERNALSYM REGSTR_VAL_ASYNCFILECOMMIT}
  REGSTR_VAL_PATHCACHECOUNT       = 'PathCache';
  {$EXTERNALSYM REGSTR_VAL_PATHCACHECOUNT}
  REGSTR_VAL_NAMECACHECOUNT       = 'NameCache';
  {$EXTERNALSYM REGSTR_VAL_NAMECACHECOUNT}
  REGSTR_VAL_CONTIGFILEALLOC      = 'ContigFileAllocSize';
  {$EXTERNALSYM REGSTR_VAL_CONTIGFILEALLOC}
  REGSTR_VAL_FREESPACERATIO       = 'FreeSpaceRatio';
  {$EXTERNALSYM REGSTR_VAL_FREESPACERATIO}
  REGSTR_VAL_VOLIDLETIMEOUT       = 'VolumeIdleTimeout';
  {$EXTERNALSYM REGSTR_VAL_VOLIDLETIMEOUT}
  REGSTR_VAL_BUFFIDLETIMEOUT      = 'BufferIdleTimeout';
  {$EXTERNALSYM REGSTR_VAL_BUFFIDLETIMEOUT}
  REGSTR_VAL_BUFFAGETIMEOUT       = 'BufferAgeTimeout';
  {$EXTERNALSYM REGSTR_VAL_BUFFAGETIMEOUT}
  REGSTR_VAL_NAMENUMERICTAIL      = 'NameNumericTail';
  {$EXTERNALSYM REGSTR_VAL_NAMENUMERICTAIL}
  REGSTR_VAL_READAHEADTHRESHOLD   = 'ReadAheadThreshold';
  {$EXTERNALSYM REGSTR_VAL_READAHEADTHRESHOLD}
  REGSTR_VAL_DOUBLEBUFFER         = 'DoubleBuffer';
  {$EXTERNALSYM REGSTR_VAL_DOUBLEBUFFER}
  REGSTR_VAL_SOFTCOMPATMODE       = 'SoftCompatMode';
  {$EXTERNALSYM REGSTR_VAL_SOFTCOMPATMODE}
  REGSTR_VAL_DRIVESPINDOWN        = 'DriveSpinDown';
  {$EXTERNALSYM REGSTR_VAL_DRIVESPINDOWN}
  REGSTR_VAL_FORCEPMIO            = 'ForcePMIO';
  {$EXTERNALSYM REGSTR_VAL_FORCEPMIO}
  REGSTR_VAL_FORCERMIO            = 'ForceRMIO';
  {$EXTERNALSYM REGSTR_VAL_FORCERMIO}
  REGSTR_VAL_LASTBOOTPMDRVS       = 'LastBootPMDrvs';
  {$EXTERNALSYM REGSTR_VAL_LASTBOOTPMDRVS}
  REGSTR_VAL_ACSPINDOWNPREVIOUS   = 'ACSpinDownPrevious';
  {$EXTERNALSYM REGSTR_VAL_ACSPINDOWNPREVIOUS}
  REGSTR_VAL_BATSPINDOWNPREVIOUS  = 'BatSpinDownPrevious';
  {$EXTERNALSYM REGSTR_VAL_BATSPINDOWNPREVIOUS}
  REGSTR_VAL_VIRTUALHDIRQ         = 'VirtualHDIRQ';
  {$EXTERNALSYM REGSTR_VAL_VIRTUALHDIRQ}
  REGSTR_VAL_SRVNAMECACHECOUNT    = 'ServerNameCacheMax';
  {$EXTERNALSYM REGSTR_VAL_SRVNAMECACHECOUNT}
  REGSTR_VAL_SRVNAMECACHE         = 'ServerNameCache';
  {$EXTERNALSYM REGSTR_VAL_SRVNAMECACHE}
  REGSTR_VAL_SRVNAMECACHENETPROV  = 'ServerNameCacheNumNets';
  {$EXTERNALSYM REGSTR_VAL_SRVNAMECACHENETPROV}
  REGSTR_VAL_AUTOMOUNT            = 'AutoMountDrives';
  {$EXTERNALSYM REGSTR_VAL_AUTOMOUNT}
  REGSTR_VAL_COMPRESSIONMETHOD    = 'CompressionAlgorithm';
  {$EXTERNALSYM REGSTR_VAL_COMPRESSIONMETHOD}
  REGSTR_VAL_COMPRESSIONTHRESHOLD = 'CompressionThreshold';
  {$EXTERNALSYM REGSTR_VAL_COMPRESSIONTHRESHOLD}
  REGSTR_VAL_ACDRIVESPINDOWN      = 'ACDriveSpinDown';
  {$EXTERNALSYM REGSTR_VAL_ACDRIVESPINDOWN}
  REGSTR_VAL_BATDRIVESPINDOWN     = 'BatDriveSpinDown';
  {$EXTERNALSYM REGSTR_VAL_BATDRIVESPINDOWN}

//
//      Entries under REGSTR_PATH_FILESYSTEM_NOVOLTRACK
//
//      A sub-key under which a variable number of variable length structures are stored.
//
//      Each structure contains an offset followed by a number of pattern bytes.
//      The pattern in each structure is compared at the specified offset within
//      the boot record at the time a volume is mounted.  If any pattern in this
//      set of patterns matches a pattern already in the boot record, VFAT will not
//      write a volume tracking serial number in the OEM_SerialNum field of the
//      boot record on the volume being mounted.
//

//
//  Entries under REGSTR_PATH_CDFS
//

  REGSTR_VAL_CDCACHESIZE    = 'CacheSize'; // Number of 2K cache sectors
  {$EXTERNALSYM REGSTR_VAL_CDCACHESIZE}
  REGSTR_VAL_CDPREFETCH     = 'Prefetch'; // Number of 2K cache sectors for prefetching
  {$EXTERNALSYM REGSTR_VAL_CDPREFETCH}
  REGSTR_VAL_CDPREFETCHTAIL = 'PrefetchTail'; // Number of LRU1 prefetch sectors
  {$EXTERNALSYM REGSTR_VAL_CDPREFETCHTAIL}
  REGSTR_VAL_CDRAWCACHE     = 'RawCache'; // Number of 2352-byte cache sectors
  {$EXTERNALSYM REGSTR_VAL_CDRAWCACHE}
  REGSTR_VAL_CDEXTERRORS    = 'ExtendedErrors'; // Return extended error codes
  {$EXTERNALSYM REGSTR_VAL_CDEXTERRORS}
  REGSTR_VAL_CDSVDSENSE     = 'SVDSense'; // 0=PVD, 1=Kanji, 2=Unicode
  {$EXTERNALSYM REGSTR_VAL_CDSVDSENSE}
  REGSTR_VAL_CDSHOWVERSIONS = 'ShowVersions'; // Show file version numbers
  {$EXTERNALSYM REGSTR_VAL_CDSHOWVERSIONS}
  REGSTR_VAL_CDCOMPATNAMES  = 'MSCDEXCompatNames'; // Disable Numeric Tails on long file names
  {$EXTERNALSYM REGSTR_VAL_CDCOMPATNAMES}
  REGSTR_VAL_CDNOREADAHEAD  = 'NoReadAhead'; // Disable Read Ahead if set to 1
  {$EXTERNALSYM REGSTR_VAL_CDNOREADAHEAD}

//
//      define values for IOS devices
//

  REGSTR_VAL_SCSI = 'SCSI\';
  {$EXTERNALSYM REGSTR_VAL_SCSI}
  REGSTR_VAL_ESDI = 'ESDI\';
  {$EXTERNALSYM REGSTR_VAL_ESDI}
  REGSTR_VAL_FLOP = 'FLOP\';
  {$EXTERNALSYM REGSTR_VAL_FLOP}

//
// define defs for IOS device types and values for IOS devices
//

  REGSTR_VAL_DISK    = 'GenDisk';
  {$EXTERNALSYM REGSTR_VAL_DISK}
  REGSTR_VAL_CDROM   = 'GenCD';
  {$EXTERNALSYM REGSTR_VAL_CDROM}
  REGSTR_VAL_TAPE    = 'TAPE';
  {$EXTERNALSYM REGSTR_VAL_TAPE}
  REGSTR_VAL_SCANNER = 'SCANNER';
  {$EXTERNALSYM REGSTR_VAL_SCANNER}
  REGSTR_VAL_FLOPPY  = 'FLOPPY';
  {$EXTERNALSYM REGSTR_VAL_FLOPPY}

  REGSTR_VAL_SCSITID      = 'SCSITargetID';
  {$EXTERNALSYM REGSTR_VAL_SCSITID}
  REGSTR_VAL_SCSILUN      = 'SCSILUN';
  {$EXTERNALSYM REGSTR_VAL_SCSILUN}
  REGSTR_VAL_REVLEVEL     = 'RevisionLevel';
  {$EXTERNALSYM REGSTR_VAL_REVLEVEL}
  REGSTR_VAL_PRODUCTID    = 'ProductId';
  {$EXTERNALSYM REGSTR_VAL_PRODUCTID}
  REGSTR_VAL_PRODUCTTYPE  = 'ProductType';
  {$EXTERNALSYM REGSTR_VAL_PRODUCTTYPE}
  REGSTR_VAL_DEVTYPE      = 'DeviceType';
  {$EXTERNALSYM REGSTR_VAL_DEVTYPE}
  REGSTR_VAL_REMOVABLE    = 'Removable';
  {$EXTERNALSYM REGSTR_VAL_REMOVABLE}
  REGSTR_VAL_CURDRVLET    = 'CurrentDriveLetterAssignment';
  {$EXTERNALSYM REGSTR_VAL_CURDRVLET}
  REGSTR_VAL_USRDRVLET    = 'UserDriveLetterAssignment';
  {$EXTERNALSYM REGSTR_VAL_USRDRVLET}
  REGSTR_VAL_SYNCDATAXFER = 'SyncDataXfer';
  {$EXTERNALSYM REGSTR_VAL_SYNCDATAXFER}
  REGSTR_VAL_AUTOINSNOTE  = 'AutoInsertNotification';
  {$EXTERNALSYM REGSTR_VAL_AUTOINSNOTE}
  REGSTR_VAL_DISCONNECT   = 'Disconnect';
  {$EXTERNALSYM REGSTR_VAL_DISCONNECT}
  REGSTR_VAL_INT13        = 'Int13';
  {$EXTERNALSYM REGSTR_VAL_INT13}
  REGSTR_VAL_PMODE_INT13  = 'PModeInt13';
  {$EXTERNALSYM REGSTR_VAL_PMODE_INT13}
  REGSTR_VAL_USERSETTINGS = 'AdapterSettings';
  {$EXTERNALSYM REGSTR_VAL_USERSETTINGS}
  REGSTR_VAL_NOIDE        = 'NoIDE';
  {$EXTERNALSYM REGSTR_VAL_NOIDE}

// The foll. clase name definitions should be the same as in dirkdrv.inx and
// cdrom.inx

  REGSTR_VAL_DISKCLASSNAME  = 'DiskDrive';
  {$EXTERNALSYM REGSTR_VAL_DISKCLASSNAME}
  REGSTR_VAL_CDROMCLASSNAME = 'CDROM';
  {$EXTERNALSYM REGSTR_VAL_CDROMCLASSNAME}

// The foll. value determines whether a port driver should be force loaded
// or not.

  REGSTR_VAL_FORCELOAD = 'ForceLoadPD';
  {$EXTERNALSYM REGSTR_VAL_FORCELOAD}

// The foll. value determines whether or not the FIFO is used on the Floppy
// controller.

  REGSTR_VAL_FORCEFIFO = 'ForceFIFO';
  {$EXTERNALSYM REGSTR_VAL_FORCEFIFO}
  REGSTR_VAL_FORCECL   = 'ForceChangeLine';
  {$EXTERNALSYM REGSTR_VAL_FORCECL}

//
// Generic CLASS Entries
//

  REGSTR_VAL_NOUSECLASS     = 'NoUseClass'; // Don't include this class in PnP functions
  {$EXTERNALSYM REGSTR_VAL_NOUSECLASS}
  REGSTR_VAL_NOINSTALLCLASS = 'NoInstallClass'; // Don't include this class in New Device Wizard
  {$EXTERNALSYM REGSTR_VAL_NOINSTALLCLASS}
  REGSTR_VAL_NODISPLAYCLASS = 'NoDisplayClass'; // Don't include this class in Device Manager
  {$EXTERNALSYM REGSTR_VAL_NODISPLAYCLASS}
  REGSTR_VAL_SILENTINSTALL  = 'SilentInstall'; // Always Silent Install devices of this class.
  {$EXTERNALSYM REGSTR_VAL_SILENTINSTALL}

//
//  Class Names
//

  REGSTR_KEY_PCMCIA_CLASS   = 'PCMCIA'; // child of PATH_CLASS
  {$EXTERNALSYM REGSTR_KEY_PCMCIA_CLASS}
  REGSTR_KEY_SCSI_CLASS     = 'SCSIAdapter';
  {$EXTERNALSYM REGSTR_KEY_SCSI_CLASS}
  REGSTR_KEY_PORTS_CLASS    = 'ports';
  {$EXTERNALSYM REGSTR_KEY_PORTS_CLASS}
  REGSTR_KEY_MEDIA_CLASS    = 'MEDIA';
  {$EXTERNALSYM REGSTR_KEY_MEDIA_CLASS}
  REGSTR_KEY_DISPLAY_CLASS  = 'Display';
  {$EXTERNALSYM REGSTR_KEY_DISPLAY_CLASS}
  REGSTR_KEY_KEYBOARD_CLASS = 'Keyboard';
  {$EXTERNALSYM REGSTR_KEY_KEYBOARD_CLASS}
  REGSTR_KEY_MOUSE_CLASS    = 'Mouse';
  {$EXTERNALSYM REGSTR_KEY_MOUSE_CLASS}
  REGSTR_KEY_MONITOR_CLASS  = 'Monitor';
  {$EXTERNALSYM REGSTR_KEY_MONITOR_CLASS}
  REGSTR_KEY_MODEM_CLASS    = 'Modem';
  {$EXTERNALSYM REGSTR_KEY_MODEM_CLASS}

//
//  Values under PATH_CLASS\PCMCIA
//

  REGSTR_VAL_PCMCIA_OPT   = 'Options';
  {$EXTERNALSYM REGSTR_VAL_PCMCIA_OPT}
  PCMCIA_OPT_HAVE_SOCKET  = $00000001;
  {$EXTERNALSYM PCMCIA_OPT_HAVE_SOCKET}
  //PCMCIA_OPT_ENABLED      = $00000002;
  //{$EXTERNALSYM PCMCIA_OPT_ENABLED}
  PCMCIA_OPT_AUTOMEM      = $00000004;
  {$EXTERNALSYM PCMCIA_OPT_AUTOMEM}
  PCMCIA_OPT_NO_SOUND     = $00000008;
  {$EXTERNALSYM PCMCIA_OPT_NO_SOUND}
  PCMCIA_OPT_NO_AUDIO     = $00000010;
  {$EXTERNALSYM PCMCIA_OPT_NO_AUDIO}
  PCMCIA_OPT_NO_APMREMOVE = $00000020;
  {$EXTERNALSYM PCMCIA_OPT_NO_APMREMOVE}

  REGSTR_VAL_PCMCIA_MEM = 'Memory'; // Card services shared mem range
  {$EXTERNALSYM REGSTR_VAL_PCMCIA_MEM}
  PCMCIA_DEF_MEMBEGIN   = $000C0000; // default 0xC0000 - 0x00FFFFFF
  {$EXTERNALSYM PCMCIA_DEF_MEMBEGIN}
  PCMCIA_DEF_MEMEND     = $00FFFFFF; // (0 - 16meg)
  {$EXTERNALSYM PCMCIA_DEF_MEMEND}
  PCMCIA_DEF_MEMLEN     = $00001000; // default 4k window
  {$EXTERNALSYM PCMCIA_DEF_MEMLEN}

  REGSTR_VAL_PCMCIA_ALLOC = 'AllocMemWin'; // PCCard alloced memory Window
  {$EXTERNALSYM REGSTR_VAL_PCMCIA_ALLOC}
  REGSTR_VAL_PCMCIA_ATAD  = 'ATADelay'; // ATA device config start delay
  {$EXTERNALSYM REGSTR_VAL_PCMCIA_ATAD}

  REGSTR_VAL_PCMCIA_SIZ = 'MinRegionSize'; // Minimum region size
  {$EXTERNALSYM REGSTR_VAL_PCMCIA_SIZ}
  PCMCIA_DEF_MIN_REGION = $00010000; // 64K minimum region size
  {$EXTERNALSYM PCMCIA_DEF_MIN_REGION}

// Values in LPTENUM keys

  REGSTR_VAL_P1284MDL = 'Model';
  {$EXTERNALSYM REGSTR_VAL_P1284MDL}
  REGSTR_VAL_P1284MFG = 'Manufacturer';
  {$EXTERNALSYM REGSTR_VAL_P1284MFG}

//
//  Values under PATH_CLASS\ISAPNP
//

  REGSTR_VAL_ISAPNP              = 'ISAPNP'; // ISAPNP VxD name
  {$EXTERNALSYM REGSTR_VAL_ISAPNP}
  REGSTR_VAL_ISAPNP_RDP_OVERRIDE = 'RDPOverRide'; // ReadDataPort OverRide
  {$EXTERNALSYM REGSTR_VAL_ISAPNP_RDP_OVERRIDE}

//
//  Values under PATH_CLASS\PCI
//

  REGSTR_VAL_PCI               = 'PCI'; // PCI VxD name
  {$EXTERNALSYM REGSTR_VAL_PCI}
  REGSTR_PCI_OPTIONS           = 'Options'; // Possible PCI options
  {$EXTERNALSYM REGSTR_PCI_OPTIONS}
  REGSTR_PCI_DUAL_IDE          = 'PCIDualIDE'; // Dual IDE flag
  {$EXTERNALSYM REGSTR_PCI_DUAL_IDE}
  PCI_OPTIONS_USE_BIOS         = $00000001;
  {$EXTERNALSYM PCI_OPTIONS_USE_BIOS}
  PCI_OPTIONS_USE_IRQ_STEERING = $00000002;
  {$EXTERNALSYM PCI_OPTIONS_USE_IRQ_STEERING}

//
//  Values under PATH_CLASS\AGPxxxx
//
//  note:  These flags affect standard AGP capabilities,
//         and are set in agplib
//

  AGP_FLAG_NO_1X_RATE             = $00000001;
  {$EXTERNALSYM AGP_FLAG_NO_1X_RATE}
  AGP_FLAG_NO_2X_RATE             = $00000002;
  {$EXTERNALSYM AGP_FLAG_NO_2X_RATE}
  AGP_FLAG_NO_4X_RATE             = $00000004;
  {$EXTERNALSYM AGP_FLAG_NO_4X_RATE}
  AGP_FLAG_NO_8X_RATE             = $00000008;
  {$EXTERNALSYM AGP_FLAG_NO_8X_RATE}
  AGP_FLAG_REVERSE_INITIALIZATION = $00000080;
  {$EXTERNALSYM AGP_FLAG_REVERSE_INITIALIZATION}

  AGP_FLAG_NO_SBA_ENABLE          = $00000100;
  {$EXTERNALSYM AGP_FLAG_NO_SBA_ENABLE}

//
// AGP flags > AGP_SPECIAL_TARGET are platform specific
//

  AGP_FLAG_SPECIAL_TARGET         = $000FFFFF;
  {$EXTERNALSYM AGP_FLAG_SPECIAL_TARGET}
  AGP_FLAG_SPECIAL_RESERVE        = $000F0000;
  {$EXTERNALSYM AGP_FLAG_SPECIAL_RESERVE}

//
// Detection related values
//

  REGSTR_KEY_CRASHES             = 'Crashes'; // key of REGSTR_PATH_DETECT
  {$EXTERNALSYM REGSTR_KEY_CRASHES}
  REGSTR_KEY_DANGERS             = 'Dangers'; // key of REGSTR_PATH_DETECT
  {$EXTERNALSYM REGSTR_KEY_DANGERS}
  REGSTR_KEY_DETMODVARS          = 'DetModVars'; // key of REGSTR_PATH_DETECT
  {$EXTERNALSYM REGSTR_KEY_DETMODVARS}
  REGSTR_KEY_NDISINFO            = 'NDISInfo'; // key of netcard hw entry
  {$EXTERNALSYM REGSTR_KEY_NDISINFO}
  REGSTR_VAL_PROTINIPATH         = 'ProtIniPath'; // protocol.ini path
  {$EXTERNALSYM REGSTR_VAL_PROTINIPATH}
  REGSTR_VAL_RESOURCES           = 'Resources'; // resources of crash func.
  {$EXTERNALSYM REGSTR_VAL_RESOURCES}
  REGSTR_VAL_CRASHFUNCS          = 'CrashFuncs'; // detfunc caused the crash
  {$EXTERNALSYM REGSTR_VAL_CRASHFUNCS}
  REGSTR_VAL_CLASS               = 'Class'; // device class
  {$EXTERNALSYM REGSTR_VAL_CLASS}
  REGSTR_VAL_DEVDESC             = 'DeviceDesc'; // device description
  {$EXTERNALSYM REGSTR_VAL_DEVDESC}
  REGSTR_VAL_BOOTCONFIG          = 'BootConfig'; // detected configuration
  {$EXTERNALSYM REGSTR_VAL_BOOTCONFIG}
  REGSTR_VAL_DETFUNC             = 'DetFunc'; // specifies detect mod/func.
  {$EXTERNALSYM REGSTR_VAL_DETFUNC}
  REGSTR_VAL_DETFLAGS            = 'DetFlags'; // detection flags
  {$EXTERNALSYM REGSTR_VAL_DETFLAGS}
  REGSTR_VAL_COMPATIBLEIDS       = 'CompatibleIDs'; // value of enum\dev\inst
  {$EXTERNALSYM REGSTR_VAL_COMPATIBLEIDS}
  REGSTR_VAL_DETCONFIG           = 'DetConfig'; // detected configuration
  {$EXTERNALSYM REGSTR_VAL_DETCONFIG}
  REGSTR_VAL_VERIFYKEY           = 'VerifyKey'; // key used in verify mode
  {$EXTERNALSYM REGSTR_VAL_VERIFYKEY}
  REGSTR_VAL_COMINFO             = 'ComInfo'; // com info. for serial mouse
  {$EXTERNALSYM REGSTR_VAL_COMINFO}
  REGSTR_VAL_INFNAME             = 'InfName'; // INF filename
  {$EXTERNALSYM REGSTR_VAL_INFNAME}
  REGSTR_VAL_CARDSPECIFIC        = 'CardSpecific'; // Netcard specific info (WORD)
  {$EXTERNALSYM REGSTR_VAL_CARDSPECIFIC}
  REGSTR_VAL_NETOSTYPE           = 'NetOSType'; // NetOS type associate w/ card
  {$EXTERNALSYM REGSTR_VAL_NETOSTYPE}
  REGSTR_DATA_NETOS_NDIS         = 'NDIS'; // Data of REGSTR_VAL_NETOSTYPE
  {$EXTERNALSYM REGSTR_DATA_NETOS_NDIS}
  REGSTR_DATA_NETOS_ODI          = 'ODI'; // Data of REGSTR_VAL_NETOSTYPE
  {$EXTERNALSYM REGSTR_DATA_NETOS_ODI}
  REGSTR_DATA_NETOS_IPX          = 'IPX'; // Data of REGSTR_VAL_NETOSTYPE
  {$EXTERNALSYM REGSTR_DATA_NETOS_IPX}
  REGSTR_VAL_MFG                 = 'Mfg';
  {$EXTERNALSYM REGSTR_VAL_MFG}
  REGSTR_VAL_SCAN_ONLY_FIRST     = 'ScanOnlyFirstDrive'; // used with IDE driver
  {$EXTERNALSYM REGSTR_VAL_SCAN_ONLY_FIRST}
  REGSTR_VAL_SHARE_IRQ           = 'ForceIRQSharing'; // used with IDE driver
  {$EXTERNALSYM REGSTR_VAL_SHARE_IRQ}
  REGSTR_VAL_NONSTANDARD_ATAPI   = 'NonStandardATAPI'; // used with IDE driver
  {$EXTERNALSYM REGSTR_VAL_NONSTANDARD_ATAPI}
  REGSTR_VAL_IDE_FORCE_SERIALIZE = 'ForceSerialization'; // used with IDE driver
  {$EXTERNALSYM REGSTR_VAL_IDE_FORCE_SERIALIZE}
  REGSTR_VAL_MAX_HCID_LEN        = 1024; // Maximum hardware/compat ID len
  {$EXTERNALSYM REGSTR_VAL_MAX_HCID_LEN}
  REGSTR_VAL_HWREV               = 'HWRevision';
  {$EXTERNALSYM REGSTR_VAL_HWREV}
  REGSTR_VAL_ENABLEINTS          = 'EnableInts';
  {$EXTERNALSYM REGSTR_VAL_ENABLEINTS}

//
// Bit values of REGSTR_VAL_DETFLAGS
//

  REGDF_NOTDETIO        = $00000001; // cannot detect I/O resource
  {$EXTERNALSYM REGDF_NOTDETIO}
  REGDF_NOTDETMEM       = $00000002; // cannot detect mem resource
  {$EXTERNALSYM REGDF_NOTDETMEM}
  REGDF_NOTDETIRQ       = $00000004; // cannot detect IRQ resource
  {$EXTERNALSYM REGDF_NOTDETIRQ}
  REGDF_NOTDETDMA       = $00000008; // cannot detect DMA resource
  {$EXTERNALSYM REGDF_NOTDETDMA}
  REGDF_NOTDETALL       = (REGDF_NOTDETIO or REGDF_NOTDETMEM or REGDF_NOTDETIRQ or REGDF_NOTDETDMA);
  {$EXTERNALSYM REGDF_NOTDETALL}
  REGDF_NEEDFULLCONFIG  = $00000010; // stop devnode if lack resource
  {$EXTERNALSYM REGDF_NEEDFULLCONFIG}
  REGDF_GENFORCEDCONFIG = $00000020; // also generate forceconfig
  {$EXTERNALSYM REGDF_GENFORCEDCONFIG}
  REGDF_NODETCONFIG     = $00008000; // don't write detconfig to reg.
  {$EXTERNALSYM REGDF_NODETCONFIG}
  REGDF_CONFLICTIO      = $00010000; // I/O res. in conflict
  {$EXTERNALSYM REGDF_CONFLICTIO}
  REGDF_CONFLICTMEM     = $00020000; // mem res. in conflict
  {$EXTERNALSYM REGDF_CONFLICTMEM}
  REGDF_CONFLICTIRQ     = $00040000; // IRQ res. in conflict
  {$EXTERNALSYM REGDF_CONFLICTIRQ}
  REGDF_CONFLICTDMA     = $00080000; // DMA res. in conflict
  {$EXTERNALSYM REGDF_CONFLICTDMA}
  REGDF_CONFLICTALL     = (REGDF_CONFLICTIO or REGDF_CONFLICTMEM or REGDF_CONFLICTIRQ or REGDF_CONFLICTDMA);
  {$EXTERNALSYM REGDF_CONFLICTALL}
  REGDF_MAPIRQ2TO9      = $00100000; // IRQ2 has been mapped to 9
  {$EXTERNALSYM REGDF_MAPIRQ2TO9}
  REGDF_NOTVERIFIED     = DWORD($80000000); // previous device unverified
  {$EXTERNALSYM REGDF_NOTVERIFIED}

//
//  Values in REGSTR_KEY_SYSTEMBOARD
//

  REGSTR_VAL_APMBIOSVER         = 'APMBiosVer';
  {$EXTERNALSYM REGSTR_VAL_APMBIOSVER}
  REGSTR_VAL_APMFLAGS           = 'APMFlags';
  {$EXTERNALSYM REGSTR_VAL_APMFLAGS}
  REGSTR_VAL_SLSUPPORT          = 'SLSupport';
  {$EXTERNALSYM REGSTR_VAL_SLSUPPORT}
  REGSTR_VAL_MACHINETYPE        = 'MachineType';
  {$EXTERNALSYM REGSTR_VAL_MACHINETYPE}
  REGSTR_VAL_SETUPMACHINETYPE   = 'SetupMachineType';
  {$EXTERNALSYM REGSTR_VAL_SETUPMACHINETYPE}
  REGSTR_MACHTYPE_UNKNOWN       = 'Unknown';
  {$EXTERNALSYM REGSTR_MACHTYPE_UNKNOWN}
  REGSTR_MACHTYPE_IBMPC         = 'IBM PC';
  {$EXTERNALSYM REGSTR_MACHTYPE_IBMPC}
  REGSTR_MACHTYPE_IBMPCJR       = 'IBM PCjr';
  {$EXTERNALSYM REGSTR_MACHTYPE_IBMPCJR}
  REGSTR_MACHTYPE_IBMPCCONV     = 'IBM PC Convertible';
  {$EXTERNALSYM REGSTR_MACHTYPE_IBMPCCONV}
  REGSTR_MACHTYPE_IBMPCXT       = 'IBM PC/XT';
  {$EXTERNALSYM REGSTR_MACHTYPE_IBMPCXT}
  REGSTR_MACHTYPE_IBMPCXT_286   = 'IBM PC/XT 286';
  {$EXTERNALSYM REGSTR_MACHTYPE_IBMPCXT_286}
  REGSTR_MACHTYPE_IBMPCAT       = 'IBM PC/AT';
  {$EXTERNALSYM REGSTR_MACHTYPE_IBMPCAT}
  REGSTR_MACHTYPE_IBMPS2_25     = 'IBM PS/2-25';
  {$EXTERNALSYM REGSTR_MACHTYPE_IBMPS2_25}
  REGSTR_MACHTYPE_IBMPS2_30_286 = 'IBM PS/2-30 286';
  {$EXTERNALSYM REGSTR_MACHTYPE_IBMPS2_30_286}
  REGSTR_MACHTYPE_IBMPS2_30     = 'IBM PS/2-30';
  {$EXTERNALSYM REGSTR_MACHTYPE_IBMPS2_30}
  REGSTR_MACHTYPE_IBMPS2_50     = 'IBM PS/2-50';
  {$EXTERNALSYM REGSTR_MACHTYPE_IBMPS2_50}
  REGSTR_MACHTYPE_IBMPS2_50Z    = 'IBM PS/2-50Z';
  {$EXTERNALSYM REGSTR_MACHTYPE_IBMPS2_50Z}
  REGSTR_MACHTYPE_IBMPS2_55SX   = 'IBM PS/2-55SX';
  {$EXTERNALSYM REGSTR_MACHTYPE_IBMPS2_55SX}
  REGSTR_MACHTYPE_IBMPS2_60     = 'IBM PS/2-60';
  {$EXTERNALSYM REGSTR_MACHTYPE_IBMPS2_60}
  REGSTR_MACHTYPE_IBMPS2_65SX   = 'IBM PS/2-65SX';
  {$EXTERNALSYM REGSTR_MACHTYPE_IBMPS2_65SX}
  REGSTR_MACHTYPE_IBMPS2_70     = 'IBM PS/2-70';
  {$EXTERNALSYM REGSTR_MACHTYPE_IBMPS2_70}
  REGSTR_MACHTYPE_IBMPS2_P70    = 'IBM PS/2-P70';
  {$EXTERNALSYM REGSTR_MACHTYPE_IBMPS2_P70}
  REGSTR_MACHTYPE_IBMPS2_70_80  = 'IBM PS/2-70/80';
  {$EXTERNALSYM REGSTR_MACHTYPE_IBMPS2_70_80}
  REGSTR_MACHTYPE_IBMPS2_80     = 'IBM PS/2-80';
  {$EXTERNALSYM REGSTR_MACHTYPE_IBMPS2_80}
  REGSTR_MACHTYPE_IBMPS2_90     = 'IBM PS/2-90';
  {$EXTERNALSYM REGSTR_MACHTYPE_IBMPS2_90}
  REGSTR_MACHTYPE_IBMPS1        = 'IBM PS/1';
  {$EXTERNALSYM REGSTR_MACHTYPE_IBMPS1}
  REGSTR_MACHTYPE_PHOENIX_PCAT  = 'Phoenix PC/AT Compatible';
  {$EXTERNALSYM REGSTR_MACHTYPE_PHOENIX_PCAT}
  REGSTR_MACHTYPE_HP_VECTRA     = 'HP Vectra';
  {$EXTERNALSYM REGSTR_MACHTYPE_HP_VECTRA}
  REGSTR_MACHTYPE_ATT_PC        = 'ATandT PC';
  {$EXTERNALSYM REGSTR_MACHTYPE_ATT_PC}
  REGSTR_MACHTYPE_ZENITH_PC     = 'Zenith PC';
  {$EXTERNALSYM REGSTR_MACHTYPE_ZENITH_PC}

  REGSTR_VAL_APMMENUSUSPEND = 'APMMenuSuspend';
  {$EXTERNALSYM REGSTR_VAL_APMMENUSUSPEND}
  APMMENUSUSPEND_DISABLED   = 0; // always disabled
  {$EXTERNALSYM APMMENUSUSPEND_DISABLED}
  APMMENUSUSPEND_ENABLED    = 1; // always enabled
  {$EXTERNALSYM APMMENUSUSPEND_ENABLED}
  APMMENUSUSPEND_UNDOCKED   = 2; // enabled undocked
  {$EXTERNALSYM APMMENUSUSPEND_UNDOCKED}
  APMMENUSUSPEND_NOCHANGE   = $80; // bitflag - cannot change setting via UI
  {$EXTERNALSYM APMMENUSUSPEND_NOCHANGE}

  REGSTR_VAL_APMACTIMEOUT  = 'APMACTimeout';
  {$EXTERNALSYM REGSTR_VAL_APMACTIMEOUT}
  REGSTR_VAL_APMBATTIMEOUT = 'APMBatTimeout';
  {$EXTERNALSYM REGSTR_VAL_APMBATTIMEOUT}
  APMTIMEOUT_DISABLED      = 0;
  {$EXTERNALSYM APMTIMEOUT_DISABLED}

  REGSTR_VAL_APMSHUTDOWNPOWER = 'APMShutDownPower';
  {$EXTERNALSYM REGSTR_VAL_APMSHUTDOWNPOWER}

  REGSTR_VAL_BUSTYPE        = 'BusType';
  {$EXTERNALSYM REGSTR_VAL_BUSTYPE}
  REGSTR_VAL_CPU            = 'CPU';
  {$EXTERNALSYM REGSTR_VAL_CPU}
  REGSTR_VAL_NDP            = 'NDP';
  {$EXTERNALSYM REGSTR_VAL_NDP}
  REGSTR_VAL_PNPBIOSVER     = 'PnPBIOSVer';
  {$EXTERNALSYM REGSTR_VAL_PNPBIOSVER}
  REGSTR_VAL_PNPSTRUCOFFSET = 'PnPStrucOffset';
  {$EXTERNALSYM REGSTR_VAL_PNPSTRUCOFFSET}
  REGSTR_VAL_PCIBIOSVER     = 'PCIBIOSVer';
  {$EXTERNALSYM REGSTR_VAL_PCIBIOSVER}
  REGSTR_VAL_HWMECHANISM    = 'HWMechanism';
  {$EXTERNALSYM REGSTR_VAL_HWMECHANISM}
  REGSTR_VAL_LASTPCIBUSNUM  = 'LastPCIBusNum';
  {$EXTERNALSYM REGSTR_VAL_LASTPCIBUSNUM}
  REGSTR_VAL_CONVMEM        = 'ConvMem';
  {$EXTERNALSYM REGSTR_VAL_CONVMEM}
  REGSTR_VAL_EXTMEM         = 'ExtMem';
  {$EXTERNALSYM REGSTR_VAL_EXTMEM}
  REGSTR_VAL_COMPUTERNAME   = 'ComputerName';
  {$EXTERNALSYM REGSTR_VAL_COMPUTERNAME}
  REGSTR_VAL_BIOSNAME       = 'BIOSName';
  {$EXTERNALSYM REGSTR_VAL_BIOSNAME}
  REGSTR_VAL_BIOSVERSION    = 'BIOSVersion';
  {$EXTERNALSYM REGSTR_VAL_BIOSVERSION}
  REGSTR_VAL_BIOSDATE       = 'BIOSDate';
  {$EXTERNALSYM REGSTR_VAL_BIOSDATE}
  REGSTR_VAL_MODEL          = 'Model';
  {$EXTERNALSYM REGSTR_VAL_MODEL}
  REGSTR_VAL_SUBMODEL       = 'Submodel';
  {$EXTERNALSYM REGSTR_VAL_SUBMODEL}
  REGSTR_VAL_REVISION       = 'Revision';
  {$EXTERNALSYM REGSTR_VAL_REVISION}

//
//  Values used in the LPT(ECP) device entry
//

  REGSTR_VAL_FIFODEPTH      = 'FIFODepth';
  {$EXTERNALSYM REGSTR_VAL_FIFODEPTH}
  REGSTR_VAL_RDINTTHRESHOLD = 'RDIntThreshold';
  {$EXTERNALSYM REGSTR_VAL_RDINTTHRESHOLD}
  REGSTR_VAL_WRINTTHRESHOLD = 'WRIntThreshold';
  {$EXTERNALSYM REGSTR_VAL_WRINTTHRESHOLD}

//used in enum\xxx\<devname>\<instname>

  REGSTR_VAL_PRIORITY      = 'Priority';
  {$EXTERNALSYM REGSTR_VAL_PRIORITY}
  REGSTR_VAL_DRIVER        = 'Driver';
  {$EXTERNALSYM REGSTR_VAL_DRIVER}
  REGSTR_VAL_FUNCDESC      = 'FunctionDesc';
  {$EXTERNALSYM REGSTR_VAL_FUNCDESC}
  REGSTR_VAL_FORCEDCONFIG  = 'ForcedConfig';
  {$EXTERNALSYM REGSTR_VAL_FORCEDCONFIG}
  REGSTR_VAL_CONFIGFLAGS   = 'ConfigFlags'; // (binary ULONG)
  {$EXTERNALSYM REGSTR_VAL_CONFIGFLAGS}
  REGSTR_VAL_CSCONFIGFLAGS = 'CSConfigFlags'; // (binary ULONG)
  {$EXTERNALSYM REGSTR_VAL_CSCONFIGFLAGS}

  CONFIGFLAG_DISABLED            = $00000001; // Set if disabled
  {$EXTERNALSYM CONFIGFLAG_DISABLED}
  CONFIGFLAG_REMOVED             = $00000002; // Set if a present hardware enum device deleted
  {$EXTERNALSYM CONFIGFLAG_REMOVED}
  CONFIGFLAG_MANUAL_INSTALL      = $00000004; // Set if the devnode was manually installed
  {$EXTERNALSYM CONFIGFLAG_MANUAL_INSTALL}
  CONFIGFLAG_IGNORE_BOOT_LC      = $00000008; // Set if skip the boot config
  {$EXTERNALSYM CONFIGFLAG_IGNORE_BOOT_LC}
  CONFIGFLAG_NET_BOOT            = $00000010; // Load this devnode when in net boot
  {$EXTERNALSYM CONFIGFLAG_NET_BOOT}
  CONFIGFLAG_REINSTALL           = $00000020; // Redo install
  {$EXTERNALSYM CONFIGFLAG_REINSTALL}
  CONFIGFLAG_FAILEDINSTALL       = $00000040; // Failed the install
  {$EXTERNALSYM CONFIGFLAG_FAILEDINSTALL}
  CONFIGFLAG_CANTSTOPACHILD      = $00000080; // Can't stop/remove a single child
  {$EXTERNALSYM CONFIGFLAG_CANTSTOPACHILD}
  CONFIGFLAG_OKREMOVEROM         = $00000100; // Can remove even if rom.
  {$EXTERNALSYM CONFIGFLAG_OKREMOVEROM}
  CONFIGFLAG_NOREMOVEEXIT        = $00000200; // Don't remove at exit.
  {$EXTERNALSYM CONFIGFLAG_NOREMOVEEXIT}
  CONFIGFLAG_FINISH_INSTALL      = $00000400; // Complete install for devnode running 'raw'
  {$EXTERNALSYM CONFIGFLAG_FINISH_INSTALL}
  CONFIGFLAG_NEEDS_FORCED_CONFIG = $00000800; // This devnode requires a forced config
  {$EXTERNALSYM CONFIGFLAG_NEEDS_FORCED_CONFIG}
  CONFIGFLAG_NETBOOT_CARD = $00001000; // This is the remote boot network card
  {$EXTERNALSYM CONFIGFLAG_NETBOOT_CARD}
  CONFIGFLAG_PARTIAL_LOG_CONF    = $00002000; // This device has a partial logconfig
  {$EXTERNALSYM CONFIGFLAG_PARTIAL_LOG_CONF}
  CONFIGFLAG_SUPPRESS_SURPRISE   = $00004000; // Set if unsafe removals should be ignored
  {$EXTERNALSYM CONFIGFLAG_SUPPRESS_SURPRISE}
  CONFIGFLAG_VERIFY_HARDWARE     = $00008000; // Set if hardware should be tested for logo failures
  {$EXTERNALSYM CONFIGFLAG_VERIFY_HARDWARE}

  CSCONFIGFLAG_BITS          = $00000007; // OR of below bits
  {$EXTERNALSYM CSCONFIGFLAG_BITS}
  CSCONFIGFLAG_DISABLED      = $00000001; // Set if
  {$EXTERNALSYM CSCONFIGFLAG_DISABLED}
  CSCONFIGFLAG_DO_NOT_CREATE = $00000002; // Set if
  {$EXTERNALSYM CSCONFIGFLAG_DO_NOT_CREATE}
  CSCONFIGFLAG_DO_NOT_START  = $00000004; // Set if
  {$EXTERNALSYM CSCONFIGFLAG_DO_NOT_START}

  DMSTATEFLAG_APPLYTOALL = $00000001; // Set if Apply To All check box is checked
  {$EXTERNALSYM DMSTATEFLAG_APPLYTOALL}

//
// Special devnodes name
//

  REGSTR_VAL_ROOT_DEVNODE     = 'HTREE\ROOT\0';
  {$EXTERNALSYM REGSTR_VAL_ROOT_DEVNODE}
  REGSTR_VAL_RESERVED_DEVNODE = 'HTREE\RESERVED\0';
  {$EXTERNALSYM REGSTR_VAL_RESERVED_DEVNODE}
  REGSTR_PATH_READDATAPORT    = REGSTR_KEY_ISAENUM + '\ReadDataPort\0';
  {$EXTERNALSYM REGSTR_PATH_READDATAPORT}

//
// Multifunction definitions
//
  REGSTR_PATH_MULTI_FUNCTION           = 'MF';
  {$EXTERNALSYM REGSTR_PATH_MULTI_FUNCTION}
  REGSTR_VAL_RESOURCE_MAP              = 'ResourceMap';
  {$EXTERNALSYM REGSTR_VAL_RESOURCE_MAP}
  REGSTR_PATH_CHILD_PREFIX             = 'Child';
  {$EXTERNALSYM REGSTR_PATH_CHILD_PREFIX}
  NUM_RESOURCE_MAP                     = 256;
  {$EXTERNALSYM NUM_RESOURCE_MAP}
  REGSTR_VAL_MF_FLAGS                  = 'MFFlags';
  {$EXTERNALSYM REGSTR_VAL_MF_FLAGS}
  MF_FLAGS_EVEN_IF_NO_RESOURCE         = $00000001;
  {$EXTERNALSYM MF_FLAGS_EVEN_IF_NO_RESOURCE}
  MF_FLAGS_NO_CREATE_IF_NO_RESOURCE    = $00000002;
  {$EXTERNALSYM MF_FLAGS_NO_CREATE_IF_NO_RESOURCE}
  MF_FLAGS_FILL_IN_UNKNOWN_RESOURCE    = $00000004;
  {$EXTERNALSYM MF_FLAGS_FILL_IN_UNKNOWN_RESOURCE}
  MF_FLAGS_CREATE_BUT_NO_SHOW_DISABLED = $00000008;
  {$EXTERNALSYM MF_FLAGS_CREATE_BUT_NO_SHOW_DISABLED}

//
// EISA multi functions add-on
//

{$IFNDEF NEC_98}
  REGSTR_VAL_EISA_RANGES         = 'EISARanges';
  {$EXTERNALSYM REGSTR_VAL_EISA_RANGES}
  REGSTR_VAL_EISA_FUNCTIONS      = 'EISAFunctions';
  {$EXTERNALSYM REGSTR_VAL_EISA_FUNCTIONS}
  REGSTR_VAL_EISA_FUNCTIONS_MASK = 'EISAFunctionsMask';
  {$EXTERNALSYM REGSTR_VAL_EISA_FUNCTIONS_MASK}
  REGSTR_VAL_EISA_FLAGS          = 'EISAFlags';
  {$EXTERNALSYM REGSTR_VAL_EISA_FLAGS}
  REGSTR_VAL_EISA_SIMULATE_INT15 = 'EISASimulateInt15';
  {$EXTERNALSYM REGSTR_VAL_EISA_SIMULATE_INT15}
{$ELSE}
  REGSTR_VAL_EISA_RANGES         = 'NESARanges';
  {$EXTERNALSYM REGSTR_VAL_EISA_RANGES}
  REGSTR_VAL_EISA_FUNCTIONS      = 'NESAFunctions';
  {$EXTERNALSYM REGSTR_VAL_EISA_FUNCTIONS}
  REGSTR_VAL_EISA_FUNCTIONS_MASK = 'NESAFunctionsMask';
  {$EXTERNALSYM REGSTR_VAL_EISA_FUNCTIONS_MASK}
  REGSTR_VAL_EISA_FLAGS          = 'NESAFlags';
  {$EXTERNALSYM REGSTR_VAL_EISA_FLAGS}
  REGSTR_VAL_EISA_SIMULATE_INT15 = 'NESASimulateInt15';
  {$EXTERNALSYM REGSTR_VAL_EISA_SIMULATE_INT15}
{$ENDIF}
  EISAFLAG_NO_IO_MERGE   = $00000001;
  {$EXTERNALSYM EISAFLAG_NO_IO_MERGE}
  EISAFLAG_SLOT_IO_FIRST = $00000002;
  {$EXTERNALSYM EISAFLAG_SLOT_IO_FIRST}
  EISA_NO_MAX_FUNCTION   = $FF;
  {$EXTERNALSYM EISA_NO_MAX_FUNCTION}
  NUM_EISA_RANGES        = 4;
  {$EXTERNALSYM NUM_EISA_RANGES}

//
//  Driver entries
//

  REGSTR_VAL_DRVDESC            = 'DriverDesc'; // value of enum\dev\inst\DRV
  {$EXTERNALSYM REGSTR_VAL_DRVDESC}
  REGSTR_VAL_DEVLOADER          = 'DevLoader'; // value of DRV
  {$EXTERNALSYM REGSTR_VAL_DEVLOADER}
  REGSTR_VAL_STATICVXD          = 'StaticVxD'; // value of DRV
  {$EXTERNALSYM REGSTR_VAL_STATICVXD}
  REGSTR_VAL_PROPERTIES         = 'Properties'; // value of DRV
  {$EXTERNALSYM REGSTR_VAL_PROPERTIES}
  REGSTR_VAL_MANUFACTURER       = 'Manufacturer';
  {$EXTERNALSYM REGSTR_VAL_MANUFACTURER}
  REGSTR_VAL_EXISTS             = 'Exists'; // value of HCC\HW\ENUM\ROOT\dev\inst
  {$EXTERNALSYM REGSTR_VAL_EXISTS}
  REGSTR_VAL_CMENUMFLAGS        = 'CMEnumFlags'; // (binary ULONG)
  {$EXTERNALSYM REGSTR_VAL_CMENUMFLAGS}
  REGSTR_VAL_CMDRIVFLAGS        = 'CMDrivFlags'; // (binary ULONG)
  {$EXTERNALSYM REGSTR_VAL_CMDRIVFLAGS}
  REGSTR_VAL_ENUMERATOR         = 'Enumerator'; // value of DRV
  {$EXTERNALSYM REGSTR_VAL_ENUMERATOR}
  REGSTR_VAL_DEVICEDRIVER       = 'DeviceDriver'; // value of DRV
  {$EXTERNALSYM REGSTR_VAL_DEVICEDRIVER}
  REGSTR_VAL_PORTNAME           = 'PortName'; // VCOMM uses this for it's port names
  {$EXTERNALSYM REGSTR_VAL_PORTNAME}
  REGSTR_VAL_INFPATH            = 'InfPath';
  {$EXTERNALSYM REGSTR_VAL_INFPATH}
  REGSTR_VAL_INFSECTION         = 'InfSection';
  {$EXTERNALSYM REGSTR_VAL_INFSECTION}
  REGSTR_VAL_INFSECTIONEXT      = 'InfSectionExt';
  {$EXTERNALSYM REGSTR_VAL_INFSECTIONEXT}
  REGSTR_VAL_POLLING            = 'Polling'; // SCSI specific
  {$EXTERNALSYM REGSTR_VAL_POLLING}
  REGSTR_VAL_DONTLOADIFCONFLICT = 'DontLoadIfConflict'; // SCSI specific
  {$EXTERNALSYM REGSTR_VAL_DONTLOADIFCONFLICT}
  REGSTR_VAL_PORTSUBCLASS       = 'PortSubClass';
  {$EXTERNALSYM REGSTR_VAL_PORTSUBCLASS}
  REGSTR_VAL_NETCLEAN           = 'NetClean'; // Driver required for NetClean boot
  {$EXTERNALSYM REGSTR_VAL_NETCLEAN}
  REGSTR_VAL_IDE_NO_SERIALIZE   = 'IDENoSerialize'; // IDE specific
  {$EXTERNALSYM REGSTR_VAL_IDE_NO_SERIALIZE}
  REGSTR_VAL_NOCMOSORFDPT       = 'NoCMOSorFDPT'; // IDE specific
  {$EXTERNALSYM REGSTR_VAL_NOCMOSORFDPT}
  REGSTR_VAL_COMVERIFYBASE      = 'COMVerifyBase'; // VCD specific
  {$EXTERNALSYM REGSTR_VAL_COMVERIFYBASE}
  REGSTR_VAL_MATCHINGDEVID      = 'MatchingDeviceId';
  {$EXTERNALSYM REGSTR_VAL_MATCHINGDEVID}
  REGSTR_VAL_DRIVERDATE         = 'DriverDate'; // value of DRV
  {$EXTERNALSYM REGSTR_VAL_DRIVERDATE}
  REGSTR_VAL_DRIVERDATEDATA     = 'DriverDateData'; // value of DRV
  {$EXTERNALSYM REGSTR_VAL_DRIVERDATEDATA}
  REGSTR_VAL_DRIVERVERSION      = 'DriverVersion'; // value of DRV
  {$EXTERNALSYM REGSTR_VAL_DRIVERVERSION}
  REGSTR_VAL_LOCATION_INFORMATION_OVERRIDE = 'LocationInformationOverride';  // value of DRV
  {$EXTERNALSYM REGSTR_VAL_LOCATION_INFORMATION_OVERRIDE}

//
//  Driver keys
//

  REGSTR_KEY_OVERRIDE = 'Override'; // key under the software section
  {$EXTERNALSYM REGSTR_KEY_OVERRIDE}

//used by CONFIGMG

  REGSTR_VAL_CONFIGMG          = 'CONFIGMG'; // Config Manager VxD name
  {$EXTERNALSYM REGSTR_VAL_CONFIGMG}
  REGSTR_VAL_SYSDM             = 'SysDM'; // The device installer DLL
  {$EXTERNALSYM REGSTR_VAL_SYSDM}
  REGSTR_VAL_SYSDMFUNC         = 'SysDMFunc'; // The device installer DLL function
  {$EXTERNALSYM REGSTR_VAL_SYSDMFUNC}
  REGSTR_VAL_PRIVATE           = 'Private'; // The private library
  {$EXTERNALSYM REGSTR_VAL_PRIVATE}
  REGSTR_VAL_PRIVATEFUNC       = 'PrivateFunc'; // The private library function
  {$EXTERNALSYM REGSTR_VAL_PRIVATEFUNC}
  REGSTR_VAL_DETECT            = 'Detect'; // The detection library
  {$EXTERNALSYM REGSTR_VAL_DETECT}
  REGSTR_VAL_DETECTFUNC        = 'DetectFunc'; // The detection library function
  {$EXTERNALSYM REGSTR_VAL_DETECTFUNC}
  REGSTR_VAL_ASKFORCONFIG      = 'AskForConfig'; // The AskForConfig library
  {$EXTERNALSYM REGSTR_VAL_ASKFORCONFIG}
  REGSTR_VAL_ASKFORCONFIGFUNC  = 'AskForConfigFunc'; // The AskForConfig library function
  {$EXTERNALSYM REGSTR_VAL_ASKFORCONFIGFUNC}
  REGSTR_VAL_WAITFORUNDOCK     = 'WaitForUndock'; // The WaitForUndock library
  {$EXTERNALSYM REGSTR_VAL_WAITFORUNDOCK}
  REGSTR_VAL_WAITFORUNDOCKFUNC = 'WaitForUndockFunc'; // The WaitForUndock library function
  {$EXTERNALSYM REGSTR_VAL_WAITFORUNDOCKFUNC}
  REGSTR_VAL_REMOVEROMOKAY     = 'RemoveRomOkay'; // The RemoveRomOkay library
  {$EXTERNALSYM REGSTR_VAL_REMOVEROMOKAY}
  REGSTR_VAL_REMOVEROMOKAYFUNC = 'RemoveRomOkayFunc'; // The RemoveRomOkay library function
  {$EXTERNALSYM REGSTR_VAL_REMOVEROMOKAYFUNC}

//used in IDCONFIGDB

  REGSTR_VAL_CURCONFIG      = 'CurrentConfig'; // value of idconfigdb
  {$EXTERNALSYM REGSTR_VAL_CURCONFIG}
  REGSTR_VAL_FRIENDLYNAME   = 'FriendlyName'; // value of idconfigdb
  {$EXTERNALSYM REGSTR_VAL_FRIENDLYNAME}
  REGSTR_VAL_CURRENTCONFIG  = 'CurrentConfig'; // value of idconfigdb
  {$EXTERNALSYM REGSTR_VAL_CURRENTCONFIG}
  REGSTR_VAL_MAP            = 'Map'; // value of idconfigdb
  {$EXTERNALSYM REGSTR_VAL_MAP}
  REGSTR_VAL_ID             = 'CurrentID'; // value of idconfigdb
  {$EXTERNALSYM REGSTR_VAL_ID}
  REGSTR_VAL_DOCKED         = 'CurrentDockedState'; // value of idconfigdb
  {$EXTERNALSYM REGSTR_VAL_DOCKED}
  REGSTR_VAL_CHECKSUM       = 'CurrentChecksum'; // value of idconfigdb
  {$EXTERNALSYM REGSTR_VAL_CHECKSUM}
  REGSTR_VAL_HWDETECT       = 'HardwareDetect'; // value of idconfigdb
  {$EXTERNALSYM REGSTR_VAL_HWDETECT}
  REGSTR_VAL_INHIBITRESULTS = 'InhibitResults'; // value of idconfigdb
  {$EXTERNALSYM REGSTR_VAL_INHIBITRESULTS}

//used in HKEY_CURRENT_CONFIG

  REGSTR_VAL_PROFILEFLAGS = 'ProfileFlags'; // value of HKEY_CURRENT_CONFIG
  {$EXTERNALSYM REGSTR_VAL_PROFILEFLAGS}

//used in PCMCIA

  REGSTR_KEY_PCMCIA     = 'PCMCIA\'; // PCMCIA dev ID prefix
  {$EXTERNALSYM REGSTR_KEY_PCMCIA}
  REGSTR_KEY_PCUNKNOWN  = 'UNKNOWN_MANUFACTURER'; // PCMCIA dev ID manuf
  {$EXTERNALSYM REGSTR_KEY_PCUNKNOWN}
  REGSTR_VAL_PCSSDRIVER = 'Driver'; // value of DRV
  {$EXTERNALSYM REGSTR_VAL_PCSSDRIVER}
  REGSTR_KEY_PCMTD      = 'MTD-'; // MTD dev ID component
  {$EXTERNALSYM REGSTR_KEY_PCMTD}
  REGSTR_VAL_PCMTDRIVER = 'MTD'; // value of Mem Tech DRV
  {$EXTERNALSYM REGSTR_VAL_PCMTDRIVER}

//used in hardware\enum\dev\inst by Device Installer

  REGSTR_VAL_HARDWAREID = 'HardwareID'; // value of enum\dev\inst
  {$EXTERNALSYM REGSTR_VAL_HARDWAREID}

//value names under class brach REGSTR_KEY_CLASS + class name
// and for the drivers REGSTR_KEY_CLASS\classname\xxxx

  REGSTR_VAL_INSTALLER          = 'Installer'; // 16-bit class installer module/entry point
  {$EXTERNALSYM REGSTR_VAL_INSTALLER}
  REGSTR_VAL_INSTALLER_32       = 'Installer32'; // 32-bit class installer module/entry point
  {$EXTERNALSYM REGSTR_VAL_INSTALLER_32}
  REGSTR_VAL_INSICON            = 'Icon'; // value of class\name
  {$EXTERNALSYM REGSTR_VAL_INSICON}
  REGSTR_VAL_ENUMPROPPAGES      = 'EnumPropPages'; // For Class/Device Properties (16-bit)
  {$EXTERNALSYM REGSTR_VAL_ENUMPROPPAGES}
  REGSTR_VAL_ENUMPROPPAGES_32   = 'EnumPropPages32'; // For Class/Device Properties (32-bit)
  {$EXTERNALSYM REGSTR_VAL_ENUMPROPPAGES_32}
  REGSTR_VAL_BASICPROPERTIES    = 'BasicProperties'; // For CPL basic Properties (16-bit)
  {$EXTERNALSYM REGSTR_VAL_BASICPROPERTIES}
  REGSTR_VAL_BASICPROPERTIES_32 = 'BasicProperties32'; // For CPL basic Properties (32-bit)
  {$EXTERNALSYM REGSTR_VAL_BASICPROPERTIES_32}
  REGSTR_VAL_COINSTALLERS_32    = 'CoInstallers32'; // Device-specific co-installer multi-sz list (32-bit)
  {$EXTERNALSYM REGSTR_VAL_COINSTALLERS_32}
  REGSTR_VAL_PRIVATEPROBLEM     = 'PrivateProblem'; // For Handling Private Problems
  {$EXTERNALSYM REGSTR_VAL_PRIVATEPROBLEM}

// names used for display driver set information

  REGSTR_KEY_CURRENT = 'Current'; // current mode information
  {$EXTERNALSYM REGSTR_KEY_CURRENT}
  REGSTR_KEY_DEFAULT = 'Default'; // default configuration
  {$EXTERNALSYM REGSTR_KEY_DEFAULT}
  REGSTR_KEY_MODES   = 'Modes'; // modes subtree
  {$EXTERNALSYM REGSTR_KEY_MODES}

  REGSTR_VAL_MODE        = 'Mode'; // default mode
  {$EXTERNALSYM REGSTR_VAL_MODE}
  REGSTR_VAL_BPP         = 'BPP'; // bits per pixel
  {$EXTERNALSYM REGSTR_VAL_BPP}
  REGSTR_VAL_HRES        = 'HRes'; // horizontal resolution
  {$EXTERNALSYM REGSTR_VAL_HRES}
  REGSTR_VAL_VRES        = 'VRes'; // vertical resolution
  {$EXTERNALSYM REGSTR_VAL_VRES}
  REGSTR_VAL_FONTSIZE    = 'FontSize'; // used in default or override
  {$EXTERNALSYM REGSTR_VAL_FONTSIZE}
  REGSTR_VAL_DRV         = 'drv'; // the driver file
  {$EXTERNALSYM REGSTR_VAL_DRV}
  REGSTR_VAL_GRB         = 'grb'; // the grabber file
  {$EXTERNALSYM REGSTR_VAL_GRB}
  REGSTR_VAL_VDD         = 'vdd'; // vdds used here
  {$EXTERNALSYM REGSTR_VAL_VDD}
  REGSTR_VAL_VER         = 'Ver';
  {$EXTERNALSYM REGSTR_VAL_VER}
  REGSTR_VAL_MAXRES      = 'MaxResolution'; // max res for monitors
  {$EXTERNALSYM REGSTR_VAL_MAXRES}
  REGSTR_VAL_DPMS        = 'DPMS'; // DPMS enabled
  {$EXTERNALSYM REGSTR_VAL_DPMS}
  REGSTR_VAL_RESUMERESET = 'ResumeReset'; // need reset on resume
  {$EXTERNALSYM REGSTR_VAL_RESUMERESET}

  REGSTR_VAL_DESCRIPTION = 'Description';
  {$EXTERNALSYM REGSTR_VAL_DESCRIPTION}

// keys in fontsize tree

  REGSTR_KEY_SYSTEM = 'System'; // entries for system.ini
  {$EXTERNALSYM REGSTR_KEY_SYSTEM}
  REGSTR_KEY_USER   = 'User'; // entries for win.ini
  {$EXTERNALSYM REGSTR_KEY_USER}
  REGSTR_VAL_DPI    = 'dpi'; // dpi of fontsize
  {$EXTERNALSYM REGSTR_VAL_DPI}

//
// Used by PCIC socket services
//

  REGSTR_VAL_PCICOPTIONS = 'PCICOptions'; // Binary DWORD.  IRQ mask in
  {$EXTERNALSYM REGSTR_VAL_PCICOPTIONS}
                                                // low word.  # skts in high
{$IFNDEF NEC_98}
  PCIC_DEFAULT_IRQMASK = $4EB8; // Default IRQ masks
  {$EXTERNALSYM PCIC_DEFAULT_IRQMASK}
{$ELSE}
  PCIC_DEFAULT_IRQMASK = $1468; // Default IRQ masks
  {$EXTERNALSYM PCIC_DEFAULT_IRQMASK}
{$ENDIF}
  PCIC_DEFAULT_NUMSOCKETS = 0; // 0 = Automatic detection
  {$EXTERNALSYM PCIC_DEFAULT_NUMSOCKETS}
  REGSTR_VAL_PCICIRQMAP   = 'PCICIRQMap'; // Binary 16 byte IRQ map table
  {$EXTERNALSYM REGSTR_VAL_PCICIRQMAP}

// names used for control panel entries

  REGSTR_PATH_APPEARANCE  = 'Control Panel\Appearance';
  {$EXTERNALSYM REGSTR_PATH_APPEARANCE}
  REGSTR_PATH_LOOKSCHEMES = 'Control Panel\Appearance\Schemes';
  {$EXTERNALSYM REGSTR_PATH_LOOKSCHEMES}
  REGSTR_VAL_CUSTOMCOLORS = 'CustomColors';
  {$EXTERNALSYM REGSTR_VAL_CUSTOMCOLORS}

  REGSTR_PATH_SCREENSAVE      = 'Control Panel\Desktop';
  {$EXTERNALSYM REGSTR_PATH_SCREENSAVE}
  REGSTR_VALUE_USESCRPASSWORD = 'ScreenSaveUsePassword';
  {$EXTERNALSYM REGSTR_VALUE_USESCRPASSWORD}
  REGSTR_VALUE_SCRPASSWORD    = 'ScreenSave_Data';
  {$EXTERNALSYM REGSTR_VALUE_SCRPASSWORD}

  REGSTR_VALUE_LOWPOWERTIMEOUT = 'ScreenSaveLowPowerTimeout';
  {$EXTERNALSYM REGSTR_VALUE_LOWPOWERTIMEOUT}
  REGSTR_VALUE_POWEROFFTIMEOUT = 'ScreenSavePowerOffTimeout';
  {$EXTERNALSYM REGSTR_VALUE_POWEROFFTIMEOUT}
  REGSTR_VALUE_LOWPOWERACTIVE  = 'ScreenSaveLowPowerActive';
  {$EXTERNALSYM REGSTR_VALUE_LOWPOWERACTIVE}
  REGSTR_VALUE_POWEROFFACTIVE  = 'ScreenSavePowerOffActive';
  {$EXTERNALSYM REGSTR_VALUE_POWEROFFACTIVE}

// used for Windows applets

  REGSTR_PATH_WINDOWSAPPLETS = 'Software\Microsoft\Windows\CurrentVersion\Applets';
  {$EXTERNALSYM REGSTR_PATH_WINDOWSAPPLETS}

//
// system tray.  Flag values defined in systrap.h
//

  REGSTR_PATH_SYSTRAY           = 'Software\Microsoft\Windows\CurrentVersion\Applets\SysTray';
  {$EXTERNALSYM REGSTR_PATH_SYSTRAY}
  REGSTR_VAL_SYSTRAYSVCS        = 'Services';
  {$EXTERNALSYM REGSTR_VAL_SYSTRAYSVCS}
  REGSTR_VAL_SYSTRAYBATFLAGS    = 'PowerFlags';
  {$EXTERNALSYM REGSTR_VAL_SYSTRAYBATFLAGS}
  REGSTR_VAL_SYSTRAYPCCARDFLAGS = 'PCMCIAFlags';
  {$EXTERNALSYM REGSTR_VAL_SYSTRAYPCCARDFLAGS}

//
// Used by system networking components to store per-user values.
// All keys here are under HKCU.
//

  REGSTR_PATH_NETWORK_USERSETTINGS = 'Network';
  {$EXTERNALSYM REGSTR_PATH_NETWORK_USERSETTINGS}

  REGSTR_KEY_NETWORK_PERSISTENT = '\Persistent';
  {$EXTERNALSYM REGSTR_KEY_NETWORK_PERSISTENT}
  REGSTR_KEY_NETWORK_RECENT     = '\Recent';
  {$EXTERNALSYM REGSTR_KEY_NETWORK_RECENT}
  REGSTR_VAL_REMOTE_PATH        = 'RemotePath';
  {$EXTERNALSYM REGSTR_VAL_REMOTE_PATH}
  REGSTR_VAL_USER_NAME          = 'UserName';
  {$EXTERNALSYM REGSTR_VAL_USER_NAME}
  REGSTR_VAL_PROVIDER_NAME      = 'ProviderName';
  {$EXTERNALSYM REGSTR_VAL_PROVIDER_NAME}
  REGSTR_VAL_CONNECTION_TYPE    = 'ConnectionType';
  {$EXTERNALSYM REGSTR_VAL_CONNECTION_TYPE}
  REGSTR_VAL_UPGRADE            = 'Upgrade';
  {$EXTERNALSYM REGSTR_VAL_UPGRADE}

  REGSTR_KEY_LOGON           = '\Logon';
  {$EXTERNALSYM REGSTR_KEY_LOGON}
  REGSTR_VAL_MUSTBEVALIDATED = 'MustBeValidated';
  {$EXTERNALSYM REGSTR_VAL_MUSTBEVALIDATED}
  REGSTR_VAL_RUNLOGINSCRIPT  = 'ProcessLoginScript';
  {$EXTERNALSYM REGSTR_VAL_RUNLOGINSCRIPT}

//
// NetworkProvider entries. These entries are under
// REGSTR_PATH_SERVICES\xxx\NetworkProvider
//

  REGSTR_KEY_NETWORKPROVIDER  = '\NetworkProvider';
  {$EXTERNALSYM REGSTR_KEY_NETWORKPROVIDER}
  REGSTR_PATH_NW32NETPROVIDER = REGSTR_PATH_SERVICES + '\NWNP32' + REGSTR_KEY_NETWORKPROVIDER;
  {$EXTERNALSYM REGSTR_PATH_NW32NETPROVIDER}
  REGSTR_PATH_MS32NETPROVIDER = REGSTR_PATH_SERVICES + '\MSNP32' + REGSTR_KEY_NETWORKPROVIDER;
  {$EXTERNALSYM REGSTR_PATH_MS32NETPROVIDER}
  REGSTR_VAL_AUTHENT_AGENT    = 'AuthenticatingAgent';
  {$EXTERNALSYM REGSTR_VAL_AUTHENT_AGENT}

//
// Entries under REGSTR_PATH_REALMODENET
//

  REGSTR_VAL_PREFREDIR     = 'PreferredRedir';
  {$EXTERNALSYM REGSTR_VAL_PREFREDIR}
  REGSTR_VAL_AUTOSTART     = 'AutoStart';
  {$EXTERNALSYM REGSTR_VAL_AUTOSTART}
  REGSTR_VAL_AUTOLOGON     = 'AutoLogon';
  {$EXTERNALSYM REGSTR_VAL_AUTOLOGON}
  REGSTR_VAL_NETCARD       = 'Netcard';
  {$EXTERNALSYM REGSTR_VAL_NETCARD}
  REGSTR_VAL_TRANSPORT     = 'Transport';
  {$EXTERNALSYM REGSTR_VAL_TRANSPORT}
  REGSTR_VAL_DYNAMIC       = 'Dynamic';
  {$EXTERNALSYM REGSTR_VAL_DYNAMIC}
  REGSTR_VAL_TRANSITION    = 'Transition';
  {$EXTERNALSYM REGSTR_VAL_TRANSITION}
  REGSTR_VAL_STATICDRIVE   = 'StaticDrive';
  {$EXTERNALSYM REGSTR_VAL_STATICDRIVE}
  REGSTR_VAL_LOADHI        = 'LoadHi';
  {$EXTERNALSYM REGSTR_VAL_LOADHI}
  REGSTR_VAL_LOADRMDRIVERS = 'LoadRMDrivers';
  {$EXTERNALSYM REGSTR_VAL_LOADRMDRIVERS}
  REGSTR_VAL_SETUPN        = 'SetupN';
  {$EXTERNALSYM REGSTR_VAL_SETUPN}
  REGSTR_VAL_SETUPNPATH    = 'SetupNPath';
  {$EXTERNALSYM REGSTR_VAL_SETUPNPATH}

//
// Entries under REGSTR_PATH_CVNETWORK
//

  REGSTR_VAL_WRKGRP_FORCEMAPPING = 'WrkgrpForceMapping';
  {$EXTERNALSYM REGSTR_VAL_WRKGRP_FORCEMAPPING}
  REGSTR_VAL_WRKGRP_REQUIRED     = 'WrkgrpRequired';
  {$EXTERNALSYM REGSTR_VAL_WRKGRP_REQUIRED}

//
// NT-compatible place where the name of the currently logged-on user is stored.
//

  REGSTR_PATH_CURRENT_CONTROL_SET = 'System\CurrentControlSet\Control';
  {$EXTERNALSYM REGSTR_PATH_CURRENT_CONTROL_SET}
  REGSTR_VAL_CURRENT_USER         = 'Current User';
  {$EXTERNALSYM REGSTR_VAL_CURRENT_USER}

// section where password providers are installed (each provider has subkey under this key)

  REGSTR_PATH_PWDPROVIDER              = 'System\CurrentControlSet\Control\PwdProvider';
  {$EXTERNALSYM REGSTR_PATH_PWDPROVIDER}
  REGSTR_VAL_PWDPROVIDER_PATH          = 'ProviderPath';
  {$EXTERNALSYM REGSTR_VAL_PWDPROVIDER_PATH}
  REGSTR_VAL_PWDPROVIDER_DESC          = 'Description';
  {$EXTERNALSYM REGSTR_VAL_PWDPROVIDER_DESC}
  REGSTR_VAL_PWDPROVIDER_CHANGEPWD     = 'ChangePassword';
  {$EXTERNALSYM REGSTR_VAL_PWDPROVIDER_CHANGEPWD}
  REGSTR_VAL_PWDPROVIDER_CHANGEPWDHWND = 'ChangePasswordHwnd';
  {$EXTERNALSYM REGSTR_VAL_PWDPROVIDER_CHANGEPWDHWND}
  REGSTR_VAL_PWDPROVIDER_GETPWDSTATUS  = 'GetPasswordStatus';
  {$EXTERNALSYM REGSTR_VAL_PWDPROVIDER_GETPWDSTATUS}
  REGSTR_VAL_PWDPROVIDER_ISNP          = 'NetworkProvider';
  {$EXTERNALSYM REGSTR_VAL_PWDPROVIDER_ISNP}
  REGSTR_VAL_PWDPROVIDER_CHANGEORDER   = 'ChangeOrder';
  {$EXTERNALSYM REGSTR_VAL_PWDPROVIDER_CHANGEORDER}

//
// Used by administrator configuration tool and various components who enforce
// policies.
//

  REGSTR_PATH_POLICIES = 'Software\Microsoft\Windows\CurrentVersion\Policies';
  {$EXTERNALSYM REGSTR_PATH_POLICIES}

// used to control remote update of administrator policies

  REGSTR_PATH_UPDATE      = 'System\CurrentControlSet\Control\Update';
  {$EXTERNALSYM REGSTR_PATH_UPDATE}
  REGSTR_VALUE_ENABLE     = 'Enable';
  {$EXTERNALSYM REGSTR_VALUE_ENABLE}
  REGSTR_VALUE_VERBOSE    = 'Verbose';
  {$EXTERNALSYM REGSTR_VALUE_VERBOSE}
  REGSTR_VALUE_NETPATH    = 'NetworkPath';
  {$EXTERNALSYM REGSTR_VALUE_NETPATH}
  REGSTR_VALUE_DEFAULTLOC = 'UseDefaultNetLocation';
  {$EXTERNALSYM REGSTR_VALUE_DEFAULTLOC}

//
//      Entries under REGSTR_PATH_POLICIES
//

  REGSTR_KEY_NETWORK   = 'Network';
  {$EXTERNALSYM REGSTR_KEY_NETWORK}
  // already defined above
  // REGSTR_KEY_SYSTEM    = 'System';
  // {$EXTERNALSYM REGSTR_KEY_SYSTEM}
  REGSTR_KEY_PRINTERS  = 'Printers';
  {$EXTERNALSYM REGSTR_KEY_PRINTERS}
  REGSTR_KEY_WINOLDAPP = 'WinOldApp';
  {$EXTERNALSYM REGSTR_KEY_WINOLDAPP}

// (following are values REG_DWORD, legal values 0 or 1, treat as TEXT("0") if value not present)
// policies under NETWORK key

  REGSTR_VAL_NOFILESHARING            = 'NoFileSharing'; // TEXT("1") prevents server from loading
  {$EXTERNALSYM REGSTR_VAL_NOFILESHARING}
  REGSTR_VAL_NOPRINTSHARING           = 'NoPrintSharing';
  {$EXTERNALSYM REGSTR_VAL_NOPRINTSHARING}
  REGSTR_VAL_NOFILESHARINGCTRL        = 'NoFileSharingControl'; // TEXT("1") removes sharing ui
  {$EXTERNALSYM REGSTR_VAL_NOFILESHARINGCTRL}
  REGSTR_VAL_NOPRINTSHARINGCTRL       = 'NoPrintSharingControl';
  {$EXTERNALSYM REGSTR_VAL_NOPRINTSHARINGCTRL}
  REGSTR_VAL_HIDESHAREPWDS            = 'HideSharePwds'; // TEXT("1") hides share passwords with asterisks
  {$EXTERNALSYM REGSTR_VAL_HIDESHAREPWDS}
  REGSTR_VAL_DISABLEPWDCACHING        = 'DisablePwdCaching'; // TEXT("1") disables caching
  {$EXTERNALSYM REGSTR_VAL_DISABLEPWDCACHING}
  REGSTR_VAL_ALPHANUMPWDS             = 'AlphanumPwds'; // TEXT("1") forces alphanumeric passwords
  {$EXTERNALSYM REGSTR_VAL_ALPHANUMPWDS}
  REGSTR_VAL_NETSETUP_DISABLE         = 'NoNetSetup';
  {$EXTERNALSYM REGSTR_VAL_NETSETUP_DISABLE}
  REGSTR_VAL_NETSETUP_NOCONFIGPAGE    = 'NoNetSetupConfigPage';
  {$EXTERNALSYM REGSTR_VAL_NETSETUP_NOCONFIGPAGE}
  REGSTR_VAL_NETSETUP_NOIDPAGE        = 'NoNetSetupIDPage';
  {$EXTERNALSYM REGSTR_VAL_NETSETUP_NOIDPAGE}
  REGSTR_VAL_NETSETUP_NOSECURITYPAGE  = 'NoNetSetupSecurityPage';
  {$EXTERNALSYM REGSTR_VAL_NETSETUP_NOSECURITYPAGE}
  REGSTR_VAL_SYSTEMCPL_NOVIRTMEMPAGE  = 'NoVirtMemPage';
  {$EXTERNALSYM REGSTR_VAL_SYSTEMCPL_NOVIRTMEMPAGE}
  REGSTR_VAL_SYSTEMCPL_NODEVMGRPAGE   = 'NoDevMgrPage';
  {$EXTERNALSYM REGSTR_VAL_SYSTEMCPL_NODEVMGRPAGE}
  REGSTR_VAL_SYSTEMCPL_NOCONFIGPAGE   = 'NoConfigPage';
  {$EXTERNALSYM REGSTR_VAL_SYSTEMCPL_NOCONFIGPAGE}
  REGSTR_VAL_SYSTEMCPL_NOFILESYSPAGE  = 'NoFileSysPage';
  {$EXTERNALSYM REGSTR_VAL_SYSTEMCPL_NOFILESYSPAGE}
  REGSTR_VAL_DISPCPL_NODISPCPL        = 'NoDispCPL';
  {$EXTERNALSYM REGSTR_VAL_DISPCPL_NODISPCPL}
  REGSTR_VAL_DISPCPL_NOBACKGROUNDPAGE = 'NoDispBackgroundPage';
  {$EXTERNALSYM REGSTR_VAL_DISPCPL_NOBACKGROUNDPAGE}
  REGSTR_VAL_DISPCPL_NOSCRSAVPAGE     = 'NoDispScrSavPage';
  {$EXTERNALSYM REGSTR_VAL_DISPCPL_NOSCRSAVPAGE}
  REGSTR_VAL_DISPCPL_NOAPPEARANCEPAGE = 'NoDispAppearancePage';
  {$EXTERNALSYM REGSTR_VAL_DISPCPL_NOAPPEARANCEPAGE}
  REGSTR_VAL_DISPCPL_NOSETTINGSPAGE   = 'NoDispSettingsPage';
  {$EXTERNALSYM REGSTR_VAL_DISPCPL_NOSETTINGSPAGE}
  REGSTR_VAL_SECCPL_NOSECCPL          = 'NoSecCPL';
  {$EXTERNALSYM REGSTR_VAL_SECCPL_NOSECCPL}
  REGSTR_VAL_SECCPL_NOPWDPAGE         = 'NoPwdPage';
  {$EXTERNALSYM REGSTR_VAL_SECCPL_NOPWDPAGE}
  REGSTR_VAL_SECCPL_NOADMINPAGE       = 'NoAdminPage';
  {$EXTERNALSYM REGSTR_VAL_SECCPL_NOADMINPAGE}
  REGSTR_VAL_SECCPL_NOPROFILEPAGE     = 'NoProfilePage';
  {$EXTERNALSYM REGSTR_VAL_SECCPL_NOPROFILEPAGE}
  REGSTR_VAL_PRINTERS_HIDETABS        = 'NoPrinterTabs';
  {$EXTERNALSYM REGSTR_VAL_PRINTERS_HIDETABS}
  REGSTR_VAL_PRINTERS_NODELETE        = 'NoDeletePrinter';
  {$EXTERNALSYM REGSTR_VAL_PRINTERS_NODELETE}
  REGSTR_VAL_PRINTERS_NOADD           = 'NoAddPrinter';
  {$EXTERNALSYM REGSTR_VAL_PRINTERS_NOADD}
  REGSTR_VAL_WINOLDAPP_DISABLED       = 'Disabled';
  {$EXTERNALSYM REGSTR_VAL_WINOLDAPP_DISABLED}
  REGSTR_VAL_WINOLDAPP_NOREALMODE     = 'NoRealMode';
  {$EXTERNALSYM REGSTR_VAL_WINOLDAPP_NOREALMODE}
  REGSTR_VAL_NOENTIRENETWORK          = 'NoEntireNetwork';
  {$EXTERNALSYM REGSTR_VAL_NOENTIRENETWORK}
  REGSTR_VAL_NOWORKGROUPCONTENTS      = 'NoWorkgroupContents';
  {$EXTERNALSYM REGSTR_VAL_NOWORKGROUPCONTENTS}

// (following are values REG_DWORD, legal values 0 or 1, treat as TEXT("1") if value not present)
// policies under Policies\SYSTEM key
  REGSTR_VAL_UNDOCK_WITHOUT_LOGON     = 'UndockWithoutLogon';
  {$EXTERNALSYM REGSTR_VAL_UNDOCK_WITHOUT_LOGON}

// REG_DWORD, 0=off, otherwise value is minimum # of chars to allow in password

  REGSTR_VAL_MINPWDLEN = 'MinPwdLen';
  {$EXTERNALSYM REGSTR_VAL_MINPWDLEN}

// REG_DWORD, 0=off, otherwise value is # of days for pwd to expire

  REGSTR_VAL_PWDEXPIRATION = 'PwdExpiration';
  {$EXTERNALSYM REGSTR_VAL_PWDEXPIRATION}

  REGSTR_VAL_WIN31PROVIDER = 'Win31Provider'; // REG_SZ
  {$EXTERNALSYM REGSTR_VAL_WIN31PROVIDER}

// policies under SYSTEM key

  REGSTR_VAL_DISABLEREGTOOLS = 'DisableRegistryTools';
  {$EXTERNALSYM REGSTR_VAL_DISABLEREGTOOLS}

  REGSTR_PATH_WINLOGON          = 'Software\Microsoft\Windows\CurrentVersion\Winlogon';
  {$EXTERNALSYM REGSTR_PATH_WINLOGON}
  REGSTR_VAL_LEGALNOTICECAPTION = 'LegalNoticeCaption'; // REG_SZ
  {$EXTERNALSYM REGSTR_VAL_LEGALNOTICECAPTION}
  REGSTR_VAL_LEGALNOTICETEXT    = 'LegalNoticeText'; // REG_SZ
  {$EXTERNALSYM REGSTR_VAL_LEGALNOTICETEXT}
  REGSTR_VAL_DRIVE_SPINDOWN     = 'NoDispSpinDown';
  {$EXTERNALSYM REGSTR_VAL_DRIVE_SPINDOWN}

  REGSTR_VAL_RESTRICTRUN = 'RestrictRun';
  {$EXTERNALSYM REGSTR_VAL_RESTRICTRUN}

//
//  Entries in policy file.  (Won't be in local registry, only policy hive)

  REGSTR_KEY_POL_USERS         = 'Users';
  {$EXTERNALSYM REGSTR_KEY_POL_USERS}
  REGSTR_KEY_POL_COMPUTERS     = 'Computers';
  {$EXTERNALSYM REGSTR_KEY_POL_COMPUTERS}
  REGSTR_KEY_POL_USERGROUPS    = 'UserGroups';
  {$EXTERNALSYM REGSTR_KEY_POL_USERGROUPS}
  REGSTR_KEY_POL_DEFAULT       = '.default';
  {$EXTERNALSYM REGSTR_KEY_POL_DEFAULT}
  REGSTR_KEY_POL_USERGROUPDATA = 'GroupData\UserGroups\Priority';
  {$EXTERNALSYM REGSTR_KEY_POL_USERGROUPDATA}

//
//      Entries for time zone information under LOCAL_MACHINE
//

  REGSTR_PATH_TIMEZONE       = 'System\CurrentControlSet\Control\TimeZoneInformation';
  {$EXTERNALSYM REGSTR_PATH_TIMEZONE}
  REGSTR_VAL_TZBIAS          = 'Bias';
  {$EXTERNALSYM REGSTR_VAL_TZBIAS}
  REGSTR_VAL_TZDLTBIAS       = 'DaylightBias';
  {$EXTERNALSYM REGSTR_VAL_TZDLTBIAS}
  REGSTR_VAL_TZSTDBIAS       = 'StandardBias';
  {$EXTERNALSYM REGSTR_VAL_TZSTDBIAS}
  REGSTR_VAL_TZACTBIAS       = 'ActiveTimeBias';
  {$EXTERNALSYM REGSTR_VAL_TZACTBIAS}
  REGSTR_VAL_TZDLTFLAG       = 'DaylightFlag';
  {$EXTERNALSYM REGSTR_VAL_TZDLTFLAG}
  REGSTR_VAL_TZSTDSTART      = 'StandardStart';
  {$EXTERNALSYM REGSTR_VAL_TZSTDSTART}
  REGSTR_VAL_TZDLTSTART      = 'DaylightStart';
  {$EXTERNALSYM REGSTR_VAL_TZDLTSTART}
  REGSTR_VAL_TZDLTNAME       = 'DaylightName';
  {$EXTERNALSYM REGSTR_VAL_TZDLTNAME}
  REGSTR_VAL_TZSTDNAME       = 'StandardName';
  {$EXTERNALSYM REGSTR_VAL_TZSTDNAME}
  REGSTR_VAL_TZNOCHANGESTART = 'NoChangeStart';
  {$EXTERNALSYM REGSTR_VAL_TZNOCHANGESTART}
  REGSTR_VAL_TZNOCHANGEEND   = 'NoChangeEnd';
  {$EXTERNALSYM REGSTR_VAL_TZNOCHANGEEND}
  REGSTR_VAL_TZNOAUTOTIME    = 'DisableAutoDaylightTimeSet';
  {$EXTERNALSYM REGSTR_VAL_TZNOAUTOTIME}

//
//      Entries for floating point processor existence under LOCAL_MACHINE
//

  REGSTR_PATH_FLOATINGPOINTPROCESSOR  = 'HARDWARE\DESCRIPTION\System\FloatingPointProcessor';
  {$EXTERNALSYM REGSTR_PATH_FLOATINGPOINTPROCESSOR}
  REGSTR_PATH_FLOATINGPOINTPROCESSOR0 = 'HARDWARE\DESCRIPTION\System\FloatingPointProcessor\0';
  {$EXTERNALSYM REGSTR_PATH_FLOATINGPOINTPROCESSOR0}

//
//      Entries for computer name under LOCAL_MACHINE
//

  REGSTR_PATH_COMPUTRNAME = 'System\CurrentControlSet\Control\ComputerName\ComputerName';
  {$EXTERNALSYM REGSTR_PATH_COMPUTRNAME}
  REGSTR_VAL_COMPUTRNAME  = 'ComputerName';
  {$EXTERNALSYM REGSTR_VAL_COMPUTRNAME}

//      Entry so that we force a reboot on shutdown / single instance dos app

  REGSTR_PATH_SHUTDOWN       = 'System\CurrentControlSet\Control\Shutdown';
  {$EXTERNALSYM REGSTR_PATH_SHUTDOWN}
  REGSTR_VAL_FORCEREBOOT     = 'ForceReboot';
  {$EXTERNALSYM REGSTR_VAL_FORCEREBOOT}
  REGSTR_VAL_SETUPPROGRAMRAN = 'SetupProgramRan';
  {$EXTERNALSYM REGSTR_VAL_SETUPPROGRAMRAN}
  REGSTR_VAL_DOES_POLLING    = 'PollingSupportNeeded';
  {$EXTERNALSYM REGSTR_VAL_DOES_POLLING}

//
//      Entries for known system DLLs under LOCAL_MACHINE
//
//      The VAL keys here are the actual DLL names (FOO.DLL)
//

  REGSTR_PATH_KNOWNDLLS   = 'System\CurrentControlSet\Control\SessionManager\KnownDLLs';
  {$EXTERNALSYM REGSTR_PATH_KNOWNDLLS}
  REGSTR_PATH_KNOWN16DLLS = 'System\CurrentControlSet\Control\SessionManager\Known16DLLs';
  {$EXTERNALSYM REGSTR_PATH_KNOWN16DLLS}

//      Entries here for system dlls we need to version check in case overwritten

  REGSTR_PATH_CHECKVERDLLS = 'System\CurrentControlSet\Control\SessionManager\CheckVerDLLs';
  {$EXTERNALSYM REGSTR_PATH_CHECKVERDLLS}
  REGSTR_PATH_WARNVERDLLS  = 'System\CurrentControlSet\Control\SessionManager\WarnVerDLLs';
  {$EXTERNALSYM REGSTR_PATH_WARNVERDLLS}

//      Entries here for app ini files we (msgsrv32) need to hack

  REGSTR_PATH_HACKINIFILE = 'System\CurrentControlSet\Control\SessionManager\HackIniFiles';
  {$EXTERNALSYM REGSTR_PATH_HACKINIFILE}

//      Keys here for bad applications we want to warn the user about before running

  REGSTR_PATH_CHECKBADAPPS = 'System\CurrentControlSet\Control\SessionManager\CheckBadApps';
  {$EXTERNALSYM REGSTR_PATH_CHECKBADAPPS}

//      Keys here for applications we need to patch

  REGSTR_PATH_APPPATCH = 'System\CurrentControlSet\Control\SessionManager\AppPatches';
  {$EXTERNALSYM REGSTR_PATH_APPPATCH}

  REGSTR_PATH_CHECKBADAPPS400 = 'System\CurrentControlSet\Control\SessionManager\CheckBadApps400';
  {$EXTERNALSYM REGSTR_PATH_CHECKBADAPPS400}

  REGSTR_PATH_SHELLSERVICEOBJECT        = 'Software\Microsoft\Windows\CurrentVersion\ShellServiceObject';
  {$EXTERNALSYM REGSTR_PATH_SHELLSERVICEOBJECT}
  REGSTR_PATH_SHELLSERVICEOBJECTDELAYED = 'Software\Microsoft\Windows\CurrentVersion\ShellServiceObjectDelayLoad';
  {$EXTERNALSYM REGSTR_PATH_SHELLSERVICEOBJECTDELAYED}

//
//      Entries for known system VxDs under LOCAL_MACHINE
//
//      The VAL keys here are the full path names of VxDs (c:\app\vapp.vxd)
//      It is suggested that the keynames be the same as the module name of
//      the VxD.
//      This section is used to dyna-load VxDs with
//      CreateFile(\.\vxd_regstr_keyname).
//

  REGSTR_PATH_KNOWNVXDS = 'System\CurrentControlSet\Control\SessionManager\KnownVxDs';
  {$EXTERNALSYM REGSTR_PATH_KNOWNVXDS}

//
// Entries for values in uninstaller keys under REGSTR_PATH_UNINSTALL \ appname
//

  REGSTR_VAL_UNINSTALLER_DISPLAYNAME = 'DisplayName';
  {$EXTERNALSYM REGSTR_VAL_UNINSTALLER_DISPLAYNAME}
  REGSTR_VAL_UNINSTALLER_COMMANDLINE = 'UninstallString';
  {$EXTERNALSYM REGSTR_VAL_UNINSTALLER_COMMANDLINE}

//
// Entries for values in uninstaller keys under REGSTR_PATH_REINSTALL \ instanceid
//

  REGSTR_VAL_REINSTALL_DISPLAYNAME        = 'DisplayName';
  {$EXTERNALSYM REGSTR_VAL_REINSTALL_DISPLAYNAME}
  REGSTR_VAL_REINSTALL_STRING             = 'ReinstallString';
  {$EXTERNALSYM REGSTR_VAL_REINSTALL_STRING}
  REGSTR_VAL_REINSTALL_DEVICEINSTANCEIDS  = 'DeviceInstanceIds';
  {$EXTERNALSYM REGSTR_VAL_REINSTALL_DEVICEINSTANCEIDS}

//
//      Entries for known per user settings: Under HKEY_CURRENT_USER
//

  REGSTR_PATH_DESKTOP        = REGSTR_PATH_SCREENSAVE;
  {$EXTERNALSYM REGSTR_PATH_DESKTOP}
  REGSTR_PATH_MOUSE          = 'Control Panel\Mouse';
  {$EXTERNALSYM REGSTR_PATH_MOUSE}
  REGSTR_PATH_KEYBOARD       = 'Control Panel\Keyboard';
  {$EXTERNALSYM REGSTR_PATH_KEYBOARD}
  REGSTR_PATH_COLORS         = 'Control Panel\Colors';
  {$EXTERNALSYM REGSTR_PATH_COLORS}
  REGSTR_PATH_SOUND          = 'Control Panel\Sound';
  {$EXTERNALSYM REGSTR_PATH_SOUND}
  REGSTR_PATH_METRICS        = 'Control Panel\Desktop\WindowMetrics';
  {$EXTERNALSYM REGSTR_PATH_METRICS}
  REGSTR_PATH_ICONS          = 'Control Panel\Icons';
  {$EXTERNALSYM REGSTR_PATH_ICONS}
  REGSTR_PATH_CURSORS        = 'Control Panel\Cursors';
  {$EXTERNALSYM REGSTR_PATH_CURSORS}
  REGSTR_PATH_CHECKDISK      = 'Software\Microsoft\Windows\CurrentVersion\Applets\Check Drive';
  {$EXTERNALSYM REGSTR_PATH_CHECKDISK}
  REGSTR_PATH_CHECKDISKSET   = 'Settings';
  {$EXTERNALSYM REGSTR_PATH_CHECKDISKSET}
  REGSTR_PATH_CHECKDISKUDRVS = 'NoUnknownDDErrDrvs';
  {$EXTERNALSYM REGSTR_PATH_CHECKDISKUDRVS}

//
//  Entries under REGSTR_PATH_FAULT
//

  REGSTR_PATH_FAULT        = 'Software\Microsoft\Windows\CurrentVersion\Fault';
  {$EXTERNALSYM REGSTR_PATH_FAULT}
  REGSTR_VAL_FAULT_LOGFILE = 'LogFile';
  {$EXTERNALSYM REGSTR_VAL_FAULT_LOGFILE}

//
//  Entries under REGSTR_PATH_AEDEBUG
//

  REGSTR_PATH_AEDEBUG         = 'Software\Microsoft\Windows NT\CurrentVersion\AeDebug';
  {$EXTERNALSYM REGSTR_PATH_AEDEBUG}
  REGSTR_VAL_AEDEBUG_DEBUGGER = 'Debugger';
  {$EXTERNALSYM REGSTR_VAL_AEDEBUG_DEBUGGER}
  REGSTR_VAL_AEDEBUG_AUTO     = 'Auto';
  {$EXTERNALSYM REGSTR_VAL_AEDEBUG_AUTO}

//
//  Entries under REGSTR_PATH_GRPCONV
//

  REGSTR_PATH_GRPCONV = 'Software\Microsoft\Windows\CurrentVersion\GrpConv';
  {$EXTERNALSYM REGSTR_PATH_GRPCONV}

//
//  Entries under the RegItem key in a shell namespace
//

  REGSTR_VAL_REGITEMDELETEMESSAGE = 'Removal Message';
  {$EXTERNALSYM REGSTR_VAL_REGITEMDELETEMESSAGE}

//
//  Entries for the Drives Tools page
//
//  NOTE that these items are not recorded for removable drives. These
//  keys record X=DSKTLSYSTEMTIME where X is the drive letter. Since
//  these tools actually work on the disk in the drive, as opposed to
//  the drive itself, it is pointless to record them on a removable media
//  since if a different disk is inserted in the drive, the data is
//  meaningless.
//

  REGSTR_PATH_LASTCHECK    = 'Software\Microsoft\Windows\CurrentVersion\Explorer\LastCheck';
  {$EXTERNALSYM REGSTR_PATH_LASTCHECK}
  REGSTR_PATH_LASTOPTIMIZE = 'Software\Microsoft\Windows\CurrentVersion\Explorer\LastOptimize';
  {$EXTERNALSYM REGSTR_PATH_LASTOPTIMIZE}
  REGSTR_PATH_LASTBACKUP   = 'Software\Microsoft\Windows\CurrentVersion\Explorer\LastBackup';
  {$EXTERNALSYM REGSTR_PATH_LASTBACKUP}

//
// The above 3 keys record with the registry value of the drive letter
// a SYSTEMTIME structure
//

//
// Entries under HKEY_LOCAL_MACHINE for Check Drive specific stuff
//

  REGSTR_PATH_CHKLASTCHECK  = 'Software\Microsoft\Windows\CurrentVersion\Applets\Check Drive\LastCheck';
  {$EXTERNALSYM REGSTR_PATH_CHKLASTCHECK}
  REGSTR_PATH_CHKLASTSURFAN = 'Software\Microsoft\Windows\CurrentVersion\Applets\Check Drive\LastSurfaceAnalysis';
  {$EXTERNALSYM REGSTR_PATH_CHKLASTSURFAN}

//
// The above 2 keys record the following binary structure which is
// a system time structure with the addition of a result code field.
// Note that the time part of REGSTR_PATH_CHKLASTCHECK is effectively
// identical to REGSTR_PATH_LASTCHECK under the explorer key
//

type
  _DSKTLSYSTEMTIME = packed record
    wYear: WORD;
    wMonth: WORD;
    wDayOfWeek: WORD;
    wDay: WORD;
    wHour: WORD;
    wMinute: WORD;
    wSecond: WORD;
    wMilliseconds: WORD;
    wResult: WORD;
  end;
  {$EXTERNALSYM _DSKTLSYSTEMTIME}
  DSKTLSYSTEMTIME = _DSKTLSYSTEMTIME;
  {$EXTERNALSYM DSKTLSYSTEMTIME}
  PDSKTLSYSTEMTIME = ^DSKTLSYSTEMTIME;
  {$EXTERNALSYM PDSKTLSYSTEMTIME}
  LPDSKTLSYSTEMTIME = ^DSKTLSYSTEMTIME;
  {$EXTERNALSYM LPDSKTLSYSTEMTIME}
  TDsktlSystemTime = _DSKTLSYSTEMTIME;

//
// The following are defines for the wResult field
//

const
  DTRESULTOK  = 0;  // Operation was successful, no errors
  {$EXTERNALSYM DTRESULTOK}
  DTRESULTFIX = 1;  // Operation was successful, errors were found
  {$EXTERNALSYM DTRESULTFIX}
                    //   but all were fixed.
  DTRESULTPROB = 2; // Operation was not successful or errors
  {$EXTERNALSYM DTRESULTPROB}
                    //   were found and some or all were not fixed.
  DTRESULTPART = 3; // Operation was partially completed but was
  {$EXTERNALSYM DTRESULTPART}
                    //   terminated either by the user or an error.

//
//  Entries for persistent shares
//

  REGSTR_KEY_SHARES         = 'Software\Microsoft\Windows\CurrentVersion\Network\LanMan';
  {$EXTERNALSYM REGSTR_KEY_SHARES}
  REGSTR_VAL_SHARES_FLAGS   = 'Flags';
  {$EXTERNALSYM REGSTR_VAL_SHARES_FLAGS}
  REGSTR_VAL_SHARES_TYPE    = 'Type';
  {$EXTERNALSYM REGSTR_VAL_SHARES_TYPE}
  REGSTR_VAL_SHARES_PATH    = 'Path';
  {$EXTERNALSYM REGSTR_VAL_SHARES_PATH}
  REGSTR_VAL_SHARES_REMARK  = 'Remark';
  {$EXTERNALSYM REGSTR_VAL_SHARES_REMARK}
  REGSTR_VAL_SHARES_RW_PASS = 'Parm1';
  {$EXTERNALSYM REGSTR_VAL_SHARES_RW_PASS}
  REGSTR_VAL_SHARES_RO_PASS = 'Parm2';
  {$EXTERNALSYM REGSTR_VAL_SHARES_RO_PASS}

//
//      Entries for printer settings under LOCAL_MACHINE
//

  REGSTR_PATH_PRINT         = 'System\CurrentControlSet\Control\Print';
  {$EXTERNALSYM REGSTR_PATH_PRINT}
  REGSTR_PATH_PRINTERS      = 'System\CurrentControlSet\Control\Print\Printers';
  {$EXTERNALSYM REGSTR_PATH_PRINTERS}
  REGSTR_PATH_PROVIDERS     = 'System\CurrentControlSet\Control\Print\Providers';
  {$EXTERNALSYM REGSTR_PATH_PROVIDERS}
  REGSTR_PATH_MONITORS      = 'System\CurrentControlSet\Control\Print\Monitors';
  {$EXTERNALSYM REGSTR_PATH_MONITORS}
  REGSTR_PATH_ENVIRONMENTS  = 'System\CurrentControlSet\Control\Print\Environments';
  {$EXTERNALSYM REGSTR_PATH_ENVIRONMENTS}
  REGSTR_VAL_START_ON_BOOT  = 'StartOnBoot';
  {$EXTERNALSYM REGSTR_VAL_START_ON_BOOT}
  REGSTR_VAL_PRINTERS_MASK  = 'PrintersMask';
  {$EXTERNALSYM REGSTR_VAL_PRINTERS_MASK}
  REGSTR_VAL_DOS_SPOOL_MASK = 'DOSSpoolMask';
  {$EXTERNALSYM REGSTR_VAL_DOS_SPOOL_MASK}
  REGSTR_KEY_CURRENT_ENV    = '\Windows 4.0';
  {$EXTERNALSYM REGSTR_KEY_CURRENT_ENV}
  REGSTR_KEY_DRIVERS        = '\Drivers';
  {$EXTERNALSYM REGSTR_KEY_DRIVERS}
  REGSTR_KEY_PRINT_PROC     = '\Print Processors';
  {$EXTERNALSYM REGSTR_KEY_PRINT_PROC}

//
// Entries for MultiMedia under HKEY_CURRENT_USER
//

  REGSTR_PATH_EVENTLABELS      = 'AppEvents\EventLabels';
  {$EXTERNALSYM REGSTR_PATH_EVENTLABELS}
  REGSTR_PATH_SCHEMES          = 'AppEvents\Schemes';
  {$EXTERNALSYM REGSTR_PATH_SCHEMES}
  REGSTR_PATH_APPS             = REGSTR_PATH_SCHEMES + '\Apps';
  {$EXTERNALSYM REGSTR_PATH_APPS}
  REGSTR_PATH_APPS_DEFAULT     = REGSTR_PATH_SCHEMES + '\Apps\.Default';
  {$EXTERNALSYM REGSTR_PATH_APPS_DEFAULT}
  REGSTR_PATH_NAMES            = REGSTR_PATH_SCHEMES + '\Names';
  {$EXTERNALSYM REGSTR_PATH_NAMES}
  REGSTR_PATH_MULTIMEDIA       = REGSTR_PATH_SETUP + '\Multimedia';
  {$EXTERNALSYM REGSTR_PATH_MULTIMEDIA}
  REGSTR_PATH_MULTIMEDIA_AUDIO = 'Software\Microsoft\Multimedia\Audio';
  {$EXTERNALSYM REGSTR_PATH_MULTIMEDIA_AUDIO}
  REGSTR_PATH_MULTIMEDIA_AUDIO_IMAGES = REGSTR_PATH_MULTIMEDIA_AUDIO + '\Images';
  {$EXTERNALSYM REGSTR_PATH_MULTIMEDIA_AUDIO_IMAGES}

//
// Entries for MultiMedia under HKEY_LOCAL_MACHINE
//

  REGSTR_PATH_MEDIARESOURCES    = REGSTR_PATH_CURRENT_CONTROL_SET + '\MediaResources';
  {$EXTERNALSYM REGSTR_PATH_MEDIARESOURCES}
  REGSTR_PATH_MEDIAPROPERTIES   = REGSTR_PATH_CURRENT_CONTROL_SET + '\MediaProperties';
  {$EXTERNALSYM REGSTR_PATH_MEDIAPROPERTIES}
  REGSTR_PATH_PRIVATEPROPERTIES = REGSTR_PATH_MEDIAPROPERTIES + '\PrivateProperties';
  {$EXTERNALSYM REGSTR_PATH_PRIVATEPROPERTIES}
  REGSTR_PATH_PUBLICPROPERTIES  = REGSTR_PATH_MEDIAPROPERTIES + '\PublicProperties';
  {$EXTERNALSYM REGSTR_PATH_PUBLICPROPERTIES}

// joysticks

  REGSTR_PATH_JOYOEM     = REGSTR_PATH_PRIVATEPROPERTIES + '\Joystick\OEM';
  {$EXTERNALSYM REGSTR_PATH_JOYOEM}
  REGSTR_PATH_JOYCONFIG  = REGSTR_PATH_MEDIARESOURCES + '\Joystick';
  {$EXTERNALSYM REGSTR_PATH_JOYCONFIG}
  REGSTR_KEY_JOYCURR     = 'CurrentJoystickSettings';
  {$EXTERNALSYM REGSTR_KEY_JOYCURR}
  REGSTR_KEY_JOYSETTINGS = 'JoystickSettings';
  {$EXTERNALSYM REGSTR_KEY_JOYSETTINGS}

// joystick values found under REGSTR_PATH_JOYCONFIG

  REGSTR_VAL_JOYUSERVALUES = 'JoystickUserValues';
  {$EXTERNALSYM REGSTR_VAL_JOYUSERVALUES}
  REGSTR_VAL_JOYCALLOUT    = 'JoystickCallout';
  {$EXTERNALSYM REGSTR_VAL_JOYCALLOUT}

// joystick values found under REGSTR_KEY_JOYCURR and REGSTR_KEY_JOYSETTINGS

  REGSTR_VAL_JOYNCONFIG     = 'Joystick%dConfiguration';
  {$EXTERNALSYM REGSTR_VAL_JOYNCONFIG}
  REGSTR_VAL_JOYNOEMNAME    = 'Joystick%dOEMName';
  {$EXTERNALSYM REGSTR_VAL_JOYNOEMNAME}
  REGSTR_VAL_JOYNOEMCALLOUT = 'Joystick%dOEMCallout';
  {$EXTERNALSYM REGSTR_VAL_JOYNOEMCALLOUT}

// joystick values found under keys under REGSTR_PATH_JOYOEM

  REGSTR_VAL_JOYOEMCALLOUT        = 'OEMCallout';
  {$EXTERNALSYM REGSTR_VAL_JOYOEMCALLOUT}
  REGSTR_VAL_JOYOEMNAME           = 'OEMName';
  {$EXTERNALSYM REGSTR_VAL_JOYOEMNAME}
  REGSTR_VAL_JOYOEMDATA           = 'OEMData';
  {$EXTERNALSYM REGSTR_VAL_JOYOEMDATA}
  REGSTR_VAL_JOYOEMXYLABEL        = 'OEMXYLabel';
  {$EXTERNALSYM REGSTR_VAL_JOYOEMXYLABEL}
  REGSTR_VAL_JOYOEMZLABEL         = 'OEMZLabel';
  {$EXTERNALSYM REGSTR_VAL_JOYOEMZLABEL}
  REGSTR_VAL_JOYOEMRLABEL         = 'OEMRLabel';
  {$EXTERNALSYM REGSTR_VAL_JOYOEMRLABEL}
  REGSTR_VAL_JOYOEMPOVLABEL       = 'OEMPOVLabel';
  {$EXTERNALSYM REGSTR_VAL_JOYOEMPOVLABEL}
  REGSTR_VAL_JOYOEMULABEL         = 'OEMULabel';
  {$EXTERNALSYM REGSTR_VAL_JOYOEMULABEL}
  REGSTR_VAL_JOYOEMVLABEL         = 'OEMVLabel';
  {$EXTERNALSYM REGSTR_VAL_JOYOEMVLABEL}
  REGSTR_VAL_JOYOEMTESTMOVEDESC   = 'OEMTestMoveDesc';
  {$EXTERNALSYM REGSTR_VAL_JOYOEMTESTMOVEDESC}
  REGSTR_VAL_JOYOEMTESTBUTTONDESC = 'OEMTestButtonDesc';
  {$EXTERNALSYM REGSTR_VAL_JOYOEMTESTBUTTONDESC}
  REGSTR_VAL_JOYOEMTESTMOVECAP    = 'OEMTestMoveCap';
  {$EXTERNALSYM REGSTR_VAL_JOYOEMTESTMOVECAP}
  REGSTR_VAL_JOYOEMTESTBUTTONCAP  = 'OEMTestButtonCap';
  {$EXTERNALSYM REGSTR_VAL_JOYOEMTESTBUTTONCAP}
  REGSTR_VAL_JOYOEMTESTWINCAP     = 'OEMTestWinCap';
  {$EXTERNALSYM REGSTR_VAL_JOYOEMTESTWINCAP}
  REGSTR_VAL_JOYOEMCALCAP         = 'OEMCalCap';
  {$EXTERNALSYM REGSTR_VAL_JOYOEMCALCAP}
  REGSTR_VAL_JOYOEMCALWINCAP      = 'OEMCalWinCap';
  {$EXTERNALSYM REGSTR_VAL_JOYOEMCALWINCAP}
  REGSTR_VAL_JOYOEMCAL1           = 'OEMCal1';
  {$EXTERNALSYM REGSTR_VAL_JOYOEMCAL1}
  REGSTR_VAL_JOYOEMCAL2           = 'OEMCal2';
  {$EXTERNALSYM REGSTR_VAL_JOYOEMCAL2}
  REGSTR_VAL_JOYOEMCAL3           = 'OEMCal3';
  {$EXTERNALSYM REGSTR_VAL_JOYOEMCAL3}
  REGSTR_VAL_JOYOEMCAL4           = 'OEMCal4';
  {$EXTERNALSYM REGSTR_VAL_JOYOEMCAL4}
  REGSTR_VAL_JOYOEMCAL5           = 'OEMCal5';
  {$EXTERNALSYM REGSTR_VAL_JOYOEMCAL5}
  REGSTR_VAL_JOYOEMCAL6           = 'OEMCal6';
  {$EXTERNALSYM REGSTR_VAL_JOYOEMCAL6}
  REGSTR_VAL_JOYOEMCAL7           = 'OEMCal7';
  {$EXTERNALSYM REGSTR_VAL_JOYOEMCAL7}
  REGSTR_VAL_JOYOEMCAL8           = 'OEMCal8';
  {$EXTERNALSYM REGSTR_VAL_JOYOEMCAL8}
  REGSTR_VAL_JOYOEMCAL9           = 'OEMCal9';
  {$EXTERNALSYM REGSTR_VAL_JOYOEMCAL9}
  REGSTR_VAL_JOYOEMCAL10          = 'OEMCal10';
  {$EXTERNALSYM REGSTR_VAL_JOYOEMCAL10}
  REGSTR_VAL_JOYOEMCAL11          = 'OEMCal11';
  {$EXTERNALSYM REGSTR_VAL_JOYOEMCAL11}
  REGSTR_VAL_JOYOEMCAL12          = 'OEMCal12';
  {$EXTERNALSYM REGSTR_VAL_JOYOEMCAL12}

// Image values under REGSTR_PATH_MULTIMEDIA_AUDIO_IMAGES

  REGSTR_VAL_AUDIO_BITMAP = 'bitmap';
  {$EXTERNALSYM REGSTR_VAL_AUDIO_BITMAP}
  REGSTR_VAL_AUDIO_ICON   = 'icon';
  {$EXTERNALSYM REGSTR_VAL_AUDIO_ICON}

//
// Entries for Device Installer under HKEY_CURRENT_USER
//

  REGSTR_PATH_DEVICEINSTALLER = 'Software\Microsoft\Windows\CurrentVersion\Device Installer';
  {$EXTERNALSYM REGSTR_PATH_DEVICEINSTALLER}

// Device Installer values found under REGSTR_PATH_DEVICEINSTALLER

  REGSTR_VAL_SEARCHOPTIONS = 'SearchOptions';
  {$EXTERNALSYM REGSTR_VAL_SEARCHOPTIONS}

// BiosInfo defines.

{$IFNDEF _KERNEL_PNPI_}

  REGSTR_PATH_BIOSINFO = 'System\CurrentControlSet\Control\BiosInfo';
  {$EXTERNALSYM REGSTR_PATH_BIOSINFO}

{$ELSE}

  REGSTR_PATH_BIOSINFO = '\Registry\Machine\System\CurrentControlSet\Control\BiosInfo';
  {$EXTERNALSYM REGSTR_PATH_BIOSINFO}

{$ENDIF}

// Pci Irq Routing registry defines.

{$IFNDEF _KERNEL_PNPI_}

  REGSTR_PATH_PCIIR        = 'System\CurrentControlSet\Control\Pnp\PciIrqRouting';
  {$EXTERNALSYM REGSTR_PATH_PCIIR}
  REGSTR_VAL_OPTIONS       = 'Options';
  {$EXTERNALSYM REGSTR_VAL_OPTIONS}
  REGSTR_VAL_STAT          = 'Status';
  {$EXTERNALSYM REGSTR_VAL_STAT}
  REGSTR_VAL_TABLE_STAT    = 'TableStatus';
  {$EXTERNALSYM REGSTR_VAL_TABLE_STAT}
  REGSTR_VAL_MINIPORT_STAT = 'MiniportStatus';
  {$EXTERNALSYM REGSTR_VAL_MINIPORT_STAT}

{$ELSE}

  REGSTR_PATH_PCIIR        = '\Registry\Machine\System\CurrentControlSet\Control\Pnp\PciIrqRouting';
  {$EXTERNALSYM REGSTR_PATH_PCIIR}
  REGSTR_VAL_OPTIONS       = 'Options';
  {$EXTERNALSYM REGSTR_VAL_OPTIONS}
  REGSTR_VAL_STAT          = 'Status';
  {$EXTERNALSYM REGSTR_VAL_STAT}
  REGSTR_VAL_TABLE_STAT    = 'TableStatus';
  {$EXTERNALSYM REGSTR_VAL_TABLE_STAT}
  REGSTR_VAL_MINIPORT_STAT = 'MiniportStatus';
  {$EXTERNALSYM REGSTR_VAL_MINIPORT_STAT}

{$ENDIF}

// Pci Irq Routing Option values.

  PIR_OPTION_ENABLED  = $00000001;
  {$EXTERNALSYM PIR_OPTION_ENABLED}
  PIR_OPTION_REGISTRY = $00000002;
  {$EXTERNALSYM PIR_OPTION_REGISTRY}
  PIR_OPTION_MSSPEC   = $00000004;
  {$EXTERNALSYM PIR_OPTION_MSSPEC}
  PIR_OPTION_REALMODE = $00000008;
  {$EXTERNALSYM PIR_OPTION_REALMODE}
  PIR_OPTION_DEFAULT  = $0000000f;
  {$EXTERNALSYM PIR_OPTION_DEFAULT}

// Pci Irq Routing Status values.

  PIR_STATUS_ERROR    = $00000000;
  {$EXTERNALSYM PIR_STATUS_ERROR}
  PIR_STATUS_ENABLED  = $00000001;
  {$EXTERNALSYM PIR_STATUS_ENABLED}
  PIR_STATUS_DISABLED = $00000002;
  {$EXTERNALSYM PIR_STATUS_DISABLED}
  PIR_STATUS_MAX      = $00000003;
  {$EXTERNALSYM PIR_STATUS_MAX}

  PIR_STATUS_TABLE_REGISTRY = $00000000;
  {$EXTERNALSYM PIR_STATUS_TABLE_REGISTRY}
  PIR_STATUS_TABLE_MSSPEC   = $00000001;
  {$EXTERNALSYM PIR_STATUS_TABLE_MSSPEC}
  PIR_STATUS_TABLE_REALMODE = $00000002;
  {$EXTERNALSYM PIR_STATUS_TABLE_REALMODE}
  PIR_STATUS_TABLE_NONE     = $00000003;
  {$EXTERNALSYM PIR_STATUS_TABLE_NONE}
  PIR_STATUS_TABLE_ERROR    = $00000004;
  {$EXTERNALSYM PIR_STATUS_TABLE_ERROR}
  PIR_STATUS_TABLE_BAD      = $00000005;
  {$EXTERNALSYM PIR_STATUS_TABLE_BAD}
  PIR_STATUS_TABLE_SUCCESS  = $00000006;
  {$EXTERNALSYM PIR_STATUS_TABLE_SUCCESS}
  PIR_STATUS_TABLE_MAX      = $00000007;
  {$EXTERNALSYM PIR_STATUS_TABLE_MAX}

  PIR_STATUS_MINIPORT_NORMAL     = $00000000;
  {$EXTERNALSYM PIR_STATUS_MINIPORT_NORMAL}
  PIR_STATUS_MINIPORT_COMPATIBLE = $00000001;
  {$EXTERNALSYM PIR_STATUS_MINIPORT_COMPATIBLE}
  PIR_STATUS_MINIPORT_OVERRIDE   = $00000002;
  {$EXTERNALSYM PIR_STATUS_MINIPORT_OVERRIDE}
  PIR_STATUS_MINIPORT_NONE       = $00000003;
  {$EXTERNALSYM PIR_STATUS_MINIPORT_NONE}
  PIR_STATUS_MINIPORT_ERROR      = $00000004;
  {$EXTERNALSYM PIR_STATUS_MINIPORT_ERROR}
  PIR_STATUS_MINIPORT_NOKEY      = $00000005;
  {$EXTERNALSYM PIR_STATUS_MINIPORT_NOKEY}
  PIR_STATUS_MINIPORT_SUCCESS    = $00000006;
  {$EXTERNALSYM PIR_STATUS_MINIPORT_SUCCESS}
  PIR_STATUS_MINIPORT_INVALID    = $00000007;
  {$EXTERNALSYM PIR_STATUS_MINIPORT_INVALID}
  PIR_STATUS_MINIPORT_MAX        = $00000008;
  {$EXTERNALSYM PIR_STATUS_MINIPORT_MAX}

//
// entries for LastKnownGood
// each value name under this key is SubPath/File (note reversal of '\\' to '/')
// each value is an indication of post-processing to be done after files have been recovered
// LASTGOOD_OPERATION bits indicate the primary post-processing operation
// remaining bits may be used as flags (allocate flags from highest bits first)
// a value of 0 is the same as the value being omitted, ie, no post processing.
//

  REGSTR_PATH_LASTGOOD            = 'System\LastKnownGoodRecovery\LastGood';
  {$EXTERNALSYM REGSTR_PATH_LASTGOOD}
  REGSTR_PATH_LASTGOODTMP         = 'System\LastKnownGoodRecovery\LastGood.Tmp';
  {$EXTERNALSYM REGSTR_PATH_LASTGOODTMP}

  LASTGOOD_OPERATION              = $000000FF; // operation to perform
  {$EXTERNALSYM LASTGOOD_OPERATION}
  LASTGOOD_OPERATION_NOPOSTPROC   = $00000000; // no post-processing
  {$EXTERNALSYM LASTGOOD_OPERATION_NOPOSTPROC}
  LASTGOOD_OPERATION_DELETE       = $00000001; // Delete file during recovery
  {$EXTERNALSYM LASTGOOD_OPERATION_DELETE}

implementation

end.
