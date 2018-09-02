{******************************************************************************}
{                                                       	               }
{ IO Events API interface Unit for Object Pascal                               }
{                                                       	               }
{ Portions created by Microsoft are Copyright (C) 1995-2001 Microsoft          }
{ Corporation. All Rights Reserved.                                            }
{ 								               }
{ The original file is: Ioevent.h, released June 2000. The original Pascal     }
{ code is: IoEvent.pas, released December 2000. The initial developer of the   }
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

unit JwaIoEvent;

{$WEAKPACKAGEUNIT}

{$HPPEMIT ''}
{$HPPEMIT '#include "Ioevent.h"'}
{$HPPEMIT ''}

{$I WINDEFINES.INC}

interface

uses
  JwaWinType;

//
//  Label change event.  This event is signalled upon successful completion
//  of a label change.  There is no additional data.
//

const
  GUID_IO_VOLUME_CHANGE: TGUID = (D1:$7373654a; D2:$812a; D3:$11d0; D4:($be, $c7, $08, $00, $2b, $e2, $09, $2f));
  {$EXTERNALSYM  GUID_IO_VOLUME_CHANGE}

//
//  Volume dismount event.  This event is signalled when an attempt is made to
//  dismount a volume.  There is no additional data.  Note that this will not
//  necessarily be preceded by a GUID_IO_VOLUME_LOCK notification.
//

  GUID_IO_VOLUME_DISMOUNT: TGUID = (D1:$d16a55e8; D2:$1059; D3:$11d2; D4:($8f, $fd, $00, $a0, $c9, $a0, $6d, $32));
  {$EXTERNALSYM GUID_IO_VOLUME_DISMOUNT}

//
//  Volume dismount failed event.  This event is signalled when a volume dismount fails.
//  There is no additional data.
//

  GUID_IO_VOLUME_DISMOUNT_FAILED: TGUID = (D1:$e3c5b178; D2:$105d; D3:$11d2; D4:($8f, $fd, $00, $a0, $c9, $a0, $6d, $32));
  {$EXTERNALSYM GUID_IO_VOLUME_DISMOUNT_FAILED}

//
//  Volume mount event.  This event is signalled when a volume mount occurs.
//  There is no additional data.
//

  GUID_IO_VOLUME_MOUNT: TGUID = (D1:$b5804878; D2:$1a96; D3:$11d2; D4:($8f, $fd, $00, $a0, $c9, $a0, $6d, $32));
  {$EXTERNALSYM GUID_IO_VOLUME_MOUNT}

//
//  Volume lock event.  This event is signalled when an attempt is made to
//  lock a volume.  There is no additional data.
//

  GUID_IO_VOLUME_LOCK: TGUID = (D1:$50708874; D2:$c9af; D3:$11d1; D4:($8f, $ef, $00, $a0, $c9, $a0, $6d, $32));
  {$EXTERNALSYM GUID_IO_VOLUME_LOCK}

//
//  Volume lock failed event.  This event is signalled when an attempt is made to
//  lock a volume, but it fails.  There is no additional data.
//

  GUID_IO_VOLUME_LOCK_FAILED: TGUID = (D1:$ae2eed10; D2:$0ba8; D3:$11d2; D4:($8f, $fb, $00, $a0, $c9, $a0, $6d, $32));
  {$EXTERNALSYM GUID_IO_VOLUME_LOCK_FAILED}


//
//  Volume unlock event.  This event is signalled when an attempt is made to
//  unlock a volume.  There is no additional data.
//

  GUID_IO_VOLUME_UNLOCK: TGUID = (D1:$9a8c3d68; D2:$d0cb; D3:$11d1; D4:($8f, $ef, $00, $a0, $c9, $a0, $6d, $32));
  {$EXTERNALSYM GUID_IO_VOLUME_UNLOCK}


//
//  Volume name change.  This event is signalled when the list of persistent
//  names (like drive letters) for a volume changes.  There is no additional
//  data.
//

  GUID_IO_VOLUME_NAME_CHANGE: TGUID = (D1:$2de97f83; D2:$4c06; D3:$11d2; D4:($a5, $32, $0, $60, $97, $13, $5, $5a));
  {$EXTERNALSYM GUID_IO_VOLUME_NAME_CHANGE}


//
//  Volume physical configuration change.  This event is signalled when the
//  physical makeup or current physical state of the volume changes.
//

  GUID_IO_VOLUME_PHYSICAL_CONFIGURATION_CHANGE: TGUID = (D1:$2de97f84; D2:$4c06; D3:$11d2; D4:($a5, $32, $0, $60, $97, $13, $5, $5a));
  {$EXTERNALSYM GUID_IO_VOLUME_PHYSICAL_CONFIGURATION_CHANGE}


//
//  Volume device interface.  This is a device interface GUID that appears
//  when the device object associated with a volume is created and disappears
//  when the device object associated with the volume is destroyed.
//

  GUID_IO_VOLUME_DEVICE_INTERFACE: TGUID = (D1:$53f5630d; D2:$b6bf; D3:$11d0; D4:($94, $f2, $00, $a0, $c9, $1e, $fb, $8b));
  {$EXTERNALSYM GUID_IO_VOLUME_DEVICE_INTERFACE}

//
//  Sent when the removable media is changed (added, removed) from a device
//  (such as a CDROM, tape, changer, etc).
//
//  The additional data is a DWORD representing the data event.
//

  GUID_IO_MEDIA_ARRIVAL: TGUID = (D1:$d07433c0; D2:$a98e; D3:$11d2; D4:($91, $7a, $00, $a0, $c9, $06, $8f, $f3));
  {$EXTERNALSYM GUID_IO_MEDIA_ARRIVAL}
  GUID_IO_MEDIA_REMOVAL: TGUID = (D1:$d07433c1; D2:$a98e; D3:$11d2; D4:($91, $7a, $00, $a0, $c9, $06, $8f, $f3));
  {$EXTERNALSYM GUID_IO_MEDIA_REMOVAL}

//
// Sent when the media is returning that it is not ready right now, but will
// be ready soon. This can be because the drive has spun down to save power
// or because new media has been inserted but is not ready for access yet.
//

  GUID_IO_DEVICE_BECOMING_READY: TGUID = (D1:$d07433f0; D2:$a98e; D3:$11d2; D4:($91, $7a, $00, $a0, $c9, $06, $8f, $f3));
  {$EXTERNALSYM GUID_IO_DEVICE_BECOMING_READY}

type
  _DEVICE_EVENT_BECOMING_READY = record
    Version: ULONG;
    Reason: ULONG;
    Estimated100msToReady: ULONG;
  end;
  {$EXTERNALSYM _DEVICE_EVENT_BECOMING_READY}
  DEVICE_EVENT_BECOMING_READY = _DEVICE_EVENT_BECOMING_READY;
  {$EXTERNALSYM DEVICE_EVENT_BECOMING_READY}
  PDEVICE_EVENT_BECOMING_READY = ^DEVICE_EVENT_BECOMING_READY;
  {$EXTERNALSYM PDEVICE_EVENT_BECOMING_READY}
  TDeviceEventBecomingReady = DEVICE_EVENT_BECOMING_READY;
  PDeviceEventBecomingReady = PDEVICE_EVENT_BECOMING_READY;

//
// Sent when the user presses the eject button on the front of the drive,
// or when other buttons on the front are pressed via GESN command polling
// (GESN support to be added)
//

const
  GUID_IO_DEVICE_EXTERNAL_REQUEST: TGUID = (D1:$d07433d0; D2:$a98e; D3:$11d2; D4:($91, $7a, $00, $a0, $c9, $06, $8f, $f3));
  {$EXTERNALSYM GUID_IO_DEVICE_EXTERNAL_REQUEST}
  GUID_IO_MEDIA_EJECT_REQUEST: TGUID = (D1:$d07433d1; D2:$a98e; D3:$11d2; D4:($91, $7a, $00, $a0, $c9, $06, $8f, $f3));
  {$EXTERNALSYM GUID_IO_MEDIA_EJECT_REQUEST}

type
  PDEVICE_EVENT_EXTERNAL_REQUEST = ^DEVICE_EVENT_EXTERNAL_REQUEST;
  {$EXTERNALSYM PDEVICE_EVENT_EXTERNAL_REQUEST}
  _DEVICE_EVENT_EXTERNAL_REQUEST = record
    Version: ULONG;
    DeviceClass: ULONG; // 0 == MMC Storage Devices
    ButtonStatus: USHORT; // 1 == down, 2 == up
    Request: USHORT;
    SystemTime: LARGE_INTEGER; // for time-related info
  end;
  {$EXTERNALSYM _DEVICE_EVENT_EXTERNAL_REQUEST}
  DEVICE_EVENT_EXTERNAL_REQUEST = _DEVICE_EVENT_EXTERNAL_REQUEST;
  {$EXTERNALSYM DEVICE_EVENT_EXTERNAL_REQUEST}
  TDeviceEventExternalRequest = DEVICE_EVENT_EXTERNAL_REQUEST;
  PDeviceEventExternalRequest = PDEVICE_EVENT_EXTERNAL_REQUEST;

//
// Sent when a tape drive requires cleaning
//

const
  GUID_IO_DRIVE_REQUIRES_CLEANING: TGUID = (D1:$7207877c; D2:$90ed; D3:$44e5; D4:($a0, $0, $81, $42, $8d, $4c, $79, $bb));
  {$EXTERNALSYM GUID_IO_DRIVE_REQUIRES_CLEANING}

//
// Sent when a tape is erased
//

  GUID_IO_TAPE_ERASE: TGUID = (D1:$852d11eb; D2:$4bb8; D3:$4507; D4:($9d, $9b, $41, $7c, $c2, $b1, $b4, $38));
  {$EXTERNALSYM GUID_IO_TAPE_ERASE}

type
  _DEVICE_EVENT_GENERIC_DATA = record
    EventNumber: ULONG;
  end;
  {$EXTERNALSYM _DEVICE_EVENT_GENERIC_DATA}
  DEVICE_EVENT_GENERIC_DATA = _DEVICE_EVENT_GENERIC_DATA;
  {$EXTERNALSYM DEVICE_EVENT_GENERIC_DATA}
  PDEVICE_EVENT_GENERIC_DATA = ^DEVICE_EVENT_GENERIC_DATA;
  {$EXTERNALSYM PDEVICE_EVENT_GENERIC_DATA}
  TDeviceEventGenericData = DEVICE_EVENT_GENERIC_DATA;
  PDeviceEventGenericData = PDEVICE_EVENT_GENERIC_DATA;

//
//  Represents any asynchronous notification coming from a device driver whose
//  notification protocol is RBC
//  Additional data is provided

const
  GUID_DEVICE_EVENT_RBC: TGUID = (D1:$d0744792; D2:$a98e; D3:$11d2; D4:($91, $7a, $00, $a0, $c9, $06, $8f, $f3));
  {$EXTERNALSYM GUID_DEVICE_EVENT_RBC}

type
  _DEVICE_EVENT_RBC_DATA = record
    EventNumber: ULONG;
    SenseQualifier: UCHAR;
    SenseCode: UCHAR;
    SenseKey: UCHAR;
    Reserved: UCHAR;
    Information: ULONG;
  end;
  {$EXTERNALSYM _DEVICE_EVENT_RBC_DATA}
  DEVICE_EVENT_RBC_DATA = _DEVICE_EVENT_RBC_DATA;
  {$EXTERNALSYM DEVICE_EVENT_RBC_DATA}
  PDEVICE_EVENT_RBC_DATA = ^DEVICE_EVENT_RBC_DATA;
  {$EXTERNALSYM PDEVICE_EVENT_RBC_DATA}
  TDeviceEventRbcData = DEVICE_EVENT_RBC_DATA;
  PDeviceEventRbcData = PDEVICE_EVENT_RBC_DATA;

//
//  A clone of this disk has just arrived in the system.
//

const
  GUID_IO_DISK_CLONE_ARRIVAL: TGUID = (D1:$6a61885b; D2:$7c39; D3:$43dd; D4:($9b, $56, $b8, $ac, $22, $a5, $49, $aa));
  {$EXTERNALSYM GUID_IO_DISK_CLONE_ARRIVAL}

type
  _GUID_IO_DISK_CLONE_ARRIVAL_INFORMATION = record
    DiskNumber: ULONG; // The disk number of the new disk arriving in the system.
  end;
  {$EXTERNALSYM _GUID_IO_DISK_CLONE_ARRIVAL_INFORMATION}
  GUID_IO_DISK_CLONE_ARRIVAL_INFORMATION = _GUID_IO_DISK_CLONE_ARRIVAL_INFORMATION;
  {$EXTERNALSYM GUID_IO_DISK_CLONE_ARRIVAL_INFORMATION}
  PGUID_IO_DISK_CLONE_ARRIVAL_INFORMATION = ^GUID_IO_DISK_CLONE_ARRIVAL_INFORMATION;
  {$EXTERNALSYM PGUID_IO_DISK_CLONE_ARRIVAL_INFORMATION}
  TGuidIoDiskCloneArrivalInformation = GUID_IO_DISK_CLONE_ARRIVAL_INFORMATION;
  PGuidIoDiskCloneArrivalInformation = PGUID_IO_DISK_CLONE_ARRIVAL_INFORMATION;

//
// The disk layout has changed
//

const
  GUID_IO_DISK_LAYOUT_CHANGE: TGUID = (D1:$11dff54c; D2:$8469; D3:$41f9; D4:($b3, $de, $ef, $83, $64, $87, $c5, $4a));
  {$EXTERNALSYM GUID_IO_DISK_LAYOUT_CHANGE}

implementation

end.
