{******************************************************************************}
{                                                       	               }
{ WMI Structure Definitions API interface Unit for Object Pascal               }
{                                                       	               }
{ Portions created by Microsoft are Copyright (C) 1995-2001 Microsoft          }
{ Corporation. All Rights Reserved.                                            }
{ 								               }
{ The original file is: wmistr.h, released November 2002. The original Pascal  }
{ code is: WmiStr.pas, released April 2002. The initial developer of the       }
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

unit JwaWmiStr;

{$WEAKPACKAGEUNIT}

{$HPPEMIT ''}
{$HPPEMIT '#include "wmistr.h"'}
{$HPPEMIT ''}

{$I WINDEFINES.INC}

interface

uses
  JwaWinType, JwaWinNT;

//
// WNODE definition

type
  _WNODE_HEADER = record
    BufferSize: ULONG;        // Size of entire buffer inclusive of this ULONG
    ProviderId: ULONG;    // Provider Id of driver returning this buffer
    U1: record
    case Integer of
      0: (
        HistoricalContext: ULONG64);  // Logger use
      1: (
        Version: ULONG;           // Reserved
        Linkage: ULONG);          // Linkage field reserved for WMI
    end;
    u2: record
    case Integer of
      0: (CountLost: ULONG);         // Reserved
      1: (KernelHandle: HANDLE);     // Kernel handle for data block
      2: (TimeStamp: LARGE_INTEGER); // Timestamp as returned in units of 100ns
                                     // since 1/1/1601
    end;
    Guid: GUID;                  // Guid for data block returned with results
    ClientContext: ULONG;
    Flags: ULONG;             // Flags, see below
  end;
  {$EXTERNALSYM _WNODE_HEADER}
  WNODE_HEADER = _WNODE_HEADER;
  {$EXTERNALSYM WNODE_HEADER}
  PWNODE_HEADER = ^WNODE_HEADER;
  {$EXTERNALSYM PWNODE_HEADER}
  TWNodeHeader = WNODE_HEADER;
  PWNodeHeader = PWNODE_HEADER;

//
// WNODE_HEADER flags are defined as follows

const
  WNODE_FLAG_ALL_DATA        = $00000001; // set for WNODE_ALL_DATA
  {$EXTERNALSYM WNODE_FLAG_ALL_DATA}
  WNODE_FLAG_SINGLE_INSTANCE = $00000002; // set for WNODE_SINGLE_INSTANCE
  {$EXTERNALSYM WNODE_FLAG_SINGLE_INSTANCE}
  WNODE_FLAG_SINGLE_ITEM     = $00000004; // set for WNODE_SINGLE_ITEM
  {$EXTERNALSYM WNODE_FLAG_SINGLE_ITEM}
  WNODE_FLAG_EVENT_ITEM      = $00000008; // set for WNODE_EVENT_ITEM
  {$EXTERNALSYM WNODE_FLAG_EVENT_ITEM}

                                              // Set if data block size is
                                              // identical for all instances
                                              // (used with  WNODE_ALL_DATA
                                              // only)
  WNODE_FLAG_FIXED_INSTANCE_SIZE = $00000010;
  {$EXTERNALSYM WNODE_FLAG_FIXED_INSTANCE_SIZE}

  WNODE_FLAG_TOO_SMALL = $00000020; // set for WNODE_TOO_SMALL
  {$EXTERNALSYM WNODE_FLAG_TOO_SMALL}

                                 // Set when a data provider returns a
                                 // WNODE_ALL_DATA in which the number of
                                 // instances and their names returned
                                 // are identical to those returned from the
                                 // previous WNODE_ALL_DATA query. Only data
                                 // blocks registered with dynamic instance
                                 // names should use this flag.

  WNODE_FLAG_INSTANCES_SAME = $00000040;
  {$EXTERNALSYM WNODE_FLAG_INSTANCES_SAME}

                                 // Instance names are not specified in
                                 // WNODE_ALL_DATA; values specified at
                                 // registration are used instead. Always
                                 // set for guids registered with static
                                 // instance names

  WNODE_FLAG_STATIC_INSTANCE_NAMES = $00000080;
  {$EXTERNALSYM WNODE_FLAG_STATIC_INSTANCE_NAMES}

  WNODE_FLAG_INTERNAL = $00000100; // Used internally by WMI
  {$EXTERNALSYM WNODE_FLAG_INTERNAL}

                                 // timestamp should not be modified by
                                 // a historical logger

  WNODE_FLAG_USE_TIMESTAMP = $00000200;
  {$EXTERNALSYM WNODE_FLAG_USE_TIMESTAMP}
  WNODE_FLAG_PERSIST_EVENT = $00000400;
  {$EXTERNALSYM WNODE_FLAG_PERSIST_EVENT}

  WNODE_FLAG_EVENT_REFERENCE = $00002000;
  {$EXTERNALSYM WNODE_FLAG_EVENT_REFERENCE}

// Set if Instance names are ansi. Only set when returning from
// WMIQuerySingleInstanceA and WMIQueryAllDataA

  WNODE_FLAG_ANSI_INSTANCENAMES = $00004000;
  {$EXTERNALSYM WNODE_FLAG_ANSI_INSTANCENAMES}

// Set if WNODE is a method call

  WNODE_FLAG_METHOD_ITEM = $00008000;
  {$EXTERNALSYM WNODE_FLAG_METHOD_ITEM}

// Set if instance names originated from a PDO

  WNODE_FLAG_PDO_INSTANCE_NAMES = $00010000;
  {$EXTERNALSYM WNODE_FLAG_PDO_INSTANCE_NAMES}

// The second byte, except the first bit is used exclusively for tracing

  WNODE_FLAG_TRACED_GUID = $00020000; // denotes a trace
  {$EXTERNALSYM WNODE_FLAG_TRACED_GUID}

  WNODE_FLAG_LOG_WNODE = $00040000; // request to log Wnode
  {$EXTERNALSYM WNODE_FLAG_LOG_WNODE}

  WNODE_FLAG_USE_GUID_PTR = $00080000; // Guid is actually a pointer
  {$EXTERNALSYM WNODE_FLAG_USE_GUID_PTR}

  WNODE_FLAG_USE_MOF_PTR = $00100000; // MOF data are dereferenced
  {$EXTERNALSYM WNODE_FLAG_USE_MOF_PTR}

  WNODE_FLAG_NO_HEADER = $00200000; // Trace without header
  {$EXTERNALSYM WNODE_FLAG_NO_HEADER}

// Set for events that are WNODE_EVENT_REFERENCE
// Mask for event severity level. Level 0xff is the most severe type of event

  WNODE_FLAG_SEVERITY_MASK = DWORD($ff000000);
  {$EXTERNALSYM WNODE_FLAG_SEVERITY_MASK}

//
// This structure is used within the WNODE_ALL_DATA when the data blocks
// for the different instances are different lengths. If the data blocks
// for the different instances are identical lengths then
// WNODE_FLAG_FIXED_INSTANCE_SIZE should be set and FixedInstanceSize
// set to the common data block size.

type
  OFFSETINSTANCEDATAANDLENGTH = record
    OffsetInstanceData: ULONG; // Offset from beginning of WNODE_ALL_DATA
    // to Data block for instance
    LengthInstanceData: ULONG; // Length of data block for instance
  end;
  {$EXTERNALSYM OFFSETINSTANCEDATAANDLENGTH}
  POFFSETINSTANCEDATAANDLENGTH = ^OFFSETINSTANCEDATAANDLENGTH;
  {$EXTERNALSYM POFFSETINSTANCEDATAANDLENGTH}
  TOffsetInstanceDataAndLength = OFFSETINSTANCEDATAANDLENGTH;

  PWNODE_ALL_DATA = ^WNODE_ALL_DATA;
  {$EXTERNALSYM PWNODE_ALL_DATA}
  tagWNODE_ALL_DATA = record
    WnodeHeader: WNODE_HEADER;
    DataBlockOffset: ULONG; // Offset from begin of WNODE to first data block
    InstanceCount: ULONG; // Count of instances whose data follows.
    // Offset to an array of offsets to the instance names
    OffsetInstanceNameOffsets: ULONG;
    // If WNODE_FLAG_FIXED_INSTANCE_SIZE is set in Flags then
    // FixedInstanceSize specifies the size of each data block. In this case
    // there is one ULONG followed by the data blocks.
    // If WNODE_FLAG_FIXED_INSTANCE_SIZE is not set
    // then OffsetInstanceDataAndLength
    // is an array of OFFSETINSTANCEDATAANDLENGTH that specifies the
    // offsets and lengths of the data blocks for each instance.
    case Integer of
      0: (FixedInstanceSize: ULONG);
      1: (OffsetInstanceDataAndLength: POFFSETINSTANCEDATAANDLENGTH);
      // [InstanceCount]

    // padding so that first data block begins on a 8 byte boundry
    // data blocks and instance names for all instances
  end;
  {$EXTERNALSYM tagWNODE_ALL_DATA}
  WNODE_ALL_DATA = tagWNODE_ALL_DATA;
  {$EXTERNALSYM WNODE_ALL_DATA}
  TWNodeAllData = WNODE_ALL_DATA;
  PWNodeAllData = PWNODE_ALL_DATA;


  PWNODE_SINGLE_INSTANCE = ^WNODE_SINGLE_INSTANCE;
  {$EXTERNALSYM PWNODE_SINGLE_INSTANCE}
  tagWNODE_SINGLE_INSTANCE = record
    WnodeHeader: _WNODE_HEADER;
    // Offset from beginning of WNODE_SINGLE_INSTANCE
    // to instance name. Use when
    // WNODE_FLAG_STATIC_INSTANCE_NAMES is reset
    // (Dynamic instance names)
    OffsetInstanceName: ULONG;
    // Instance index when
    // WNODE_FLAG_STATIC_INSTANCE_NAME is set
    InstanceIndex: ULONG; // (Static Instance Names)
    DataBlockOffset: ULONG; // offset from beginning of WNODE to data block
    SizeDataBlock: ULONG; // Size of data block for instance
    VariableData: PUCHAR;
    // instance names and padding so data block begins on 8 byte boundry
    // data block
  end;
  {$EXTERNALSYM tagWNODE_SINGLE_INSTANCE}
  WNODE_SINGLE_INSTANCE = tagWNODE_SINGLE_INSTANCE;
  {$EXTERNALSYM WNODE_SINGLE_INSTANCE}
  TWNodeSingleInstance = WNODE_SINGLE_INSTANCE;
  PWNodeSingleInstance = PWNODE_SINGLE_INSTANCE;


  PWNODE_SINGLE_ITEM = ^WNODE_SINGLE_ITEM;
  {$EXTERNALSYM PWNODE_SINGLE_ITEM}
  tagWNODE_SINGLE_ITEM = record
    WnodeHeader: WNODE_HEADER;
    // Offset from beginning of WNODE_SINGLE_INSTANCE
    // to instance name. Examine when
    // WNODE_FLAG_STATIC_INSTANCE_NAME is reset
    // (Dynamic instance names)
    OffsetInstanceName: ULONG;
    // Instance index when
    // WNODE_FLAG_STATIC_INSTANCE_NAME
    InstanceIndex: ULONG; // set (Static Instance Names)
    ItemId: ULONG; // Item Id for data item being set
    DataBlockOffset: ULONG; // offset from WNODE begin to data item value
    SizeDataItem: ULONG; // Size of data item
    VariableData: PUCHAR;
    // instance names and padding so data value begins on 8 byte boundry
    // data item value
  end;
  {$EXTERNALSYM tagWNODE_SINGLE_ITEM}
  WNODE_SINGLE_ITEM = tagWNODE_SINGLE_ITEM;
  {$EXTERNALSYM WNODE_SINGLE_ITEM}
  TWNodeSingleItem = WNODE_SINGLE_ITEM;
  PWNodeSingleItem = PWNODE_SINGLE_ITEM;

  PWNODE_METHOD_ITEM = ^WNODE_METHOD_ITEM;
  {$EXTERNALSYM PWNODE_METHOD_ITEM}
  tagWNODE_METHOD_ITEM = record
    WnodeHeader: WNODE_HEADER;
    // Offset from beginning of WNODE_METHOD_ITEM
    // to instance name. Examine when
    // WNODE_FLAG_STATIC_INSTANCE_NAME is reset
    // (Dynamic instance names)
    OffsetInstanceName: ULONG;
    // Instance index when
    // WNODE_FLAG_STATIC_INSTANCE_NAME
    InstanceIndex: ULONG; // set (Static Instance Names)
    MethodId: ULONG; // Method id of method being called
    DataBlockOffset: ULONG; // On Entry: offset from WNODE to input data
    // On Return: offset from WNODE to input and
    //            output data blocks
    SizeDataBlock: ULONG; // On Entry: Size of input data, 0 if no input
    //           data
    // On Return: Size of output data, 0 if no output
    //            data
    VariableData: PUCHAR;
    // instance names and padding so data value begins on 8 byte boundry
    // data item value
  end;
  {$EXTERNALSYM tagWNODE_METHOD_ITEM}
  WNODE_METHOD_ITEM = tagWNODE_METHOD_ITEM;
  {$EXTERNALSYM WNODE_METHOD_ITEM}
  TWNodeMethodItem = WNODE_METHOD_ITEM;
  PWNodeMethodItem = PWNODE_METHOD_ITEM;

  PWNODE_EVENT_ITEM = ^WNODE_EVENT_ITEM;
  {$EXTERNALSYM PWNODE_EVENT_ITEM}
  tagWNODE_EVENT_ITEM = record
    WnodeHeader: WNODE_HEADER;
    // Different data could be here depending upon the flags set in the
    // WNODE_HEADER above. If the WNODE_FLAG_ALL_DATA flag is set then the
    // contents of a WNODE_ALL_DATA  (excluding WNODE_HEADER) is here. If the
    // WNODE_FLAG_SINGLE_INSTANCE flag is set then a WNODE_SINGLE_INSTANCE
    // (excluding WNODE_HEADER) is here. Lastly if the  WNODE_FLAG_SINGLE_ITEM
    // flag is set then a WNODE_SINGLE_ITEM (excluding WNODE_HEADER) is here.
  end;
  {$EXTERNALSYM tagWNODE_EVENT_ITEM}
  WNODE_EVENT_ITEM = tagWNODE_EVENT_ITEM;
  {$EXTERNALSYM WNODE_EVENT_ITEM}
  TWNodeEventItem = WNODE_EVENT_ITEM;
  PWNodeEventItem = PWNODE_EVENT_ITEM;

//
// If a KM data provider needs to fire an event that is larger than the
// maximum size that WMI allows then it should fire a WNODE_EVENT_REFERENCE
// that specifies which guid and instance name to query for the actual data
// that should be part of the event.

  PWNODE_EVENT_REFERENCE = ^WNODE_EVENT_REFERENCE;
  {$EXTERNALSYM PWNODE_EVENT_REFERENCE}
  tagWNODE_EVENT_REFERENCE = record
    WnodeHeader: _WNODE_HEADER;
    TargetGuid: GUID;
    TargetDataBlockSize: ULONG;
    case Integer of
      0: (TargetInstanceIndex: ULONG);
      1: (TargetInstanceName: PWCHAR);
  end;
  {$EXTERNALSYM tagWNODE_EVENT_REFERENCE}
  WNODE_EVENT_REFERENCE = tagWNODE_EVENT_REFERENCE;
  {$EXTERNALSYM WNODE_EVENT_REFERENCE}
  TWNodeEventReference = WNODE_EVENT_REFERENCE;
  PWNodeEventReference = PWNODE_EVENT_REFERENCE;

  PWNODE_TOO_SMALL = ^WNODE_TOO_SMALL;
  {$EXTERNALSYM PWNODE_TOO_SMALL}
  tagWNODE_TOO_SMALL = record
    WnodeHeader: _WNODE_HEADER;
    SizeNeeded: ULONG; // Size needed to build WNODE result
  end;
  {$EXTERNALSYM tagWNODE_TOO_SMALL}
  WNODE_TOO_SMALL = tagWNODE_TOO_SMALL;
  {$EXTERNALSYM WNODE_TOO_SMALL}
  TWNodeTooSmall = WNODE_TOO_SMALL;
  PWNodeTooSmall = PWNODE_TOO_SMALL;

  WMIREGGUIDW = record
    Guid: GUID;             // Guid of data block being registered or updated
    Flags: ULONG;         // Flags

    InstanceCount: ULONG; // Count of static instances names for the guid

    case Integer of
                     // If WMIREG_FLAG_INSTANCE_LIST then this has the offset
                     // to a list of InstanceCount counted UNICODE
                     // strings placed end to end.
      0: (InstanceNameList: ULONG);

                     // If WMIREG_FLAG_INSTANCE_BASENAME then this has the
                     // offset to a single counted UNICODE string that
                     // has the basename for the instance names.

      1: (BaseNameOffset: ULONG);

                     // If WMIREG_FLAG_INSTANCE_PDO is set then InstanceInfo
                     // has the PDO whose device instance path will
                     // become the instance name
      2: (Pdo: ULONG_PTR);

                     // If WMIREG_FLAG_INSTANCE_REFERENCE then this points to
                     // a WMIREGINSTANCEREF structure.

      3: (InstanceInfo: ULONG_PTR);// Offset from beginning of the WMIREGINFO structure to
  end;
  {$EXTERNALSYM WMIREGGUIDW}
  PWMIREGGUIDW = ^WMIREGGUIDW;
  {$EXTERNALSYM PWMIREGGUIDW}
  TWmiRegGuidW = WMIREGGUIDW;

  WMIREGGUID = WMIREGGUIDW;
  {$EXTERNALSYM WMIREGGUID}
  PWMIREGGUID = PWMIREGGUIDW;
  {$EXTERNALSYM PWMIREGGUID}
  TWmiRegGuid = WMIREGGUID;
  
// Set if collection must be enabled for the guid before the data provider
// can be queried for data.

const
  WMIREG_FLAG_EXPENSIVE = $00000001;
  {$EXTERNALSYM WMIREG_FLAG_EXPENSIVE}

// Set if instance names for this guid are specified in a static list within
// the WMIREGINFO
  WMIREG_FLAG_INSTANCE_LIST = $00000004;
  {$EXTERNALSYM WMIREG_FLAG_INSTANCE_LIST}

// Set if instance names are to be static and generated by WMI using a
// base name in the WMIREGINFO and an index

  WMIREG_FLAG_INSTANCE_BASENAME = $00000008;
  {$EXTERNALSYM WMIREG_FLAG_INSTANCE_BASENAME}

// Set if WMI should do automatic mapping of a PDO to device instance name
// as the instance name for the guid. This flag should only be used by
// kernel mode data providers.

  WMIREG_FLAG_INSTANCE_PDO = $00000020;
  {$EXTERNALSYM WMIREG_FLAG_INSTANCE_PDO}

// Note the flags WMIREG_FLAG_INSTANCE_LIST, WMIREG_FLAG_INSTANCE_BASENAME,
// WMIREG_FLAG_INSTANCE_REFERENCE and WMIREG_FLAG_INSTANCE_PDO are mutually
// exclusive.

//
// These flags are only valid in a response to WMI_GUID_REGUPDATE

  WMIREG_FLAG_REMOVE_GUID = $00010000; // Remove support for  guid
  {$EXTERNALSYM WMIREG_FLAG_REMOVE_GUID}
  WMIREG_FLAG_RESERVED1   = $00020000; // Reserved by WMI
  {$EXTERNALSYM WMIREG_FLAG_RESERVED1}
  WMIREG_FLAG_RESERVED2   = $00040000; // Reserved by WMI
  {$EXTERNALSYM WMIREG_FLAG_RESERVED2}

// Set if guid is one that is written to trace log.
// This guid cannot be queried directly via WMI, but must be read using
// logger apis.

  WMIREG_FLAG_TRACED_GUID = $00080000;
  {$EXTERNALSYM WMIREG_FLAG_TRACED_GUID}

//
// Only those Trace Guids that have this bit set can receive
// Enable/Disable Notifications.
//

  WMIREG_FLAG_TRACE_CONTROL_GUID = $00001000;
  {$EXTERNALSYM WMIREG_FLAG_TRACE_CONTROL_GUID}

//
// Set if the guid is only used for firing events. Guids that can be queried
// and that fire events should not have this bit set.

  WMIREG_FLAG_EVENT_ONLY_GUID = $00000040;
  {$EXTERNALSYM WMIREG_FLAG_EVENT_ONLY_GUID}

type
  WMIREGINFOW =  record
    // Size of entire WMIREGINFO structure including this ULONG
    // and any static instance names that follow
    BufferSize: ULONG;

    NextWmiRegInfo: ULONG;         // Offset to next WMIREGINFO structure

    RegistryPath: ULONG; // Offset from beginning of WMIREGINFO structure to a
                         // counted Unicode string containing
                         // the driver registry path (under HKLM\CCS\Services)
                         // This must be filled only by kernel mode data
			 // providers

    // Offset from beginning of WMIREGINFO structure to a
    // counted Unicode string containing
    // the name of resource in driver file containing MOF info
    MofResourceName: ULONG;

    // Count of WMIREGGUID structures immediately following

    GuidCount: ULONG;
    WmiRegGuid: PWMIREGGUIDW;  // array of GuidCount WMIREGGUID structures
    // Variable length data including :
    //     Instance Names
  end;
  {$EXTERNALSYM WMIREGINFOW}
  PWMIREGINFOW = ^WMIREGINFOW;
  {$EXTERNALSYM PWMIREGINFOW}
  TWmiRegInfoW = WMIREGINFOW;

  WMIREGINFO = WMIREGINFOW;
  {$EXTERNALSYM WMIREGINFOW}
  PWMIREGINFO = PWMIREGINFOW;
  {$EXTERNALSYM PWMIREGINFOW}
  TWmiRegInfo = WMIREGINFOW;

//
// WMI request codes

  WMIDPREQUESTCODE = (
    WMI_GET_ALL_DATA,
    WMI_GET_SINGLE_INSTANCE,
    WMI_SET_SINGLE_INSTANCE,
    WMI_SET_SINGLE_ITEM,
    WMI_ENABLE_EVENTS,
    WMI_DISABLE_EVENTS,
    WMI_ENABLE_COLLECTION,
    WMI_DISABLE_COLLECTION,
    WMI_REGINFO,
    WMI_EXECUTE_METHOD);
  {$EXTERNALSYM WMIDPREQUESTCODE}
  TWmiDpRequestCode = WMIDPREQUESTCODE;

//
// WMI guid objects have the following rights
// WMIGUID_QUERY
// WMIGUID_SET
// WMIGUID_NOTIFICATION
// WMIGUID_READ_DESCRIPTION
// WMIGUID_EXECUTE
// TRACELOG_CREATE_REALTIME
// TRACELOG_CREATE_ONDISK
// TRACELOG_GUID_ENABLE
// TRACELOG_ACCESS_KERNEL_LOGGER
// TRACELOG_CREATE_INPROC
// TRACELOG_ACCESS_REALTIME

//
// GuidTypes
//
//#ifndef _WMIKM_

const
  WMI_GUIDTYPE_TRACECONTROL = 0;
  {$EXTERNALSYM WMI_GUIDTYPE_TRACECONTROL}
  WMI_GUIDTYPE_TRACE        = 1;
  {$EXTERNALSYM WMI_GUIDTYPE_TRACE}
  WMI_GUIDTYPE_DATA         = 2;
  {$EXTERNALSYM WMI_GUIDTYPE_DATA}
  WMI_GUIDTYPE_EVENT        = 3;
  {$EXTERNALSYM WMI_GUIDTYPE_EVENT}

//#endif

//
// Specific rights for WMI guid objects. These are available from 0x0001 to
// 0xffff (ie up to 16 rights)
//

  WMIGUID_QUERY                 = $0001;
  {$EXTERNALSYM WMIGUID_QUERY}
  WMIGUID_SET                   = $0002;
  {$EXTERNALSYM WMIGUID_SET}
  WMIGUID_NOTIFICATION          = $0004;
  {$EXTERNALSYM WMIGUID_NOTIFICATION}
  WMIGUID_READ_DESCRIPTION      = $0008;
  {$EXTERNALSYM WMIGUID_READ_DESCRIPTION}
  WMIGUID_EXECUTE               = $0010;
  {$EXTERNALSYM WMIGUID_EXECUTE}
  TRACELOG_CREATE_REALTIME      = $0020;
  {$EXTERNALSYM TRACELOG_CREATE_REALTIME}
  TRACELOG_CREATE_ONDISK        = $0040;
  {$EXTERNALSYM TRACELOG_CREATE_ONDISK}
  TRACELOG_GUID_ENABLE          = $0080;
  {$EXTERNALSYM TRACELOG_GUID_ENABLE}
  TRACELOG_ACCESS_KERNEL_LOGGER = $0100;
  {$EXTERNALSYM TRACELOG_ACCESS_KERNEL_LOGGER}
  TRACELOG_CREATE_INPROC        = $0200;
  {$EXTERNALSYM TRACELOG_CREATE_INPROC}
  TRACELOG_ACCESS_REALTIME      = $0400;
  {$EXTERNALSYM TRACELOG_ACCESS_REALTIME}
  TRACELOG_REGISTER_GUIDS       = $0800;
  {$EXTERNALSYM TRACELOG_REGISTER_GUIDS}

  WMIGUID_ALL_ACCESS = (
    STANDARD_RIGHTS_READ or
    SYNCHRONIZE or
    WMIGUID_QUERY or
    WMIGUID_SET or
    WMIGUID_NOTIFICATION or
    WMIGUID_READ_DESCRIPTION or
    WMIGUID_EXECUTE or
    TRACELOG_CREATE_REALTIME or
    TRACELOG_CREATE_ONDISK or
    TRACELOG_GUID_ENABLE or
    TRACELOG_ACCESS_KERNEL_LOGGER or
    TRACELOG_CREATE_INPROC or
    TRACELOG_ACCESS_REALTIME or
    TRACELOG_REGISTER_GUIDS);
  {$EXTERNALSYM WMIGUID_ALL_ACCESS}

  WMI_GLOBAL_LOGGER_ID = $0001;
  {$EXTERNALSYM WMI_GLOBAL_LOGGER_ID}

implementation

end.
