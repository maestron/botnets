{******************************************************************************}
{                                                       	               }
{ Performance Monitoring API interface Unit for Object Pascal                  }
{                                                       	               }
{ Portions created by Microsoft are Copyright (C) 1995-2001 Microsoft          }
{ Corporation. All Rights Reserved.                                            }
{ 								               }
{ The original file is: winperf.h, released June 2000. The original Pascal     }
{ code is: WinPerf.pas, released December 2000. The initial developer of the   }
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

unit JwaWinPerf;

{$WEAKPACKAGEUNIT}

{$HPPEMIT ''}
{$HPPEMIT '#include "WinPerf.h"'}
{$HPPEMIT ''}

{$I WINDEFINES.INC}


interface

uses
  JwaWinBase, JwaWinType;

//  Header file for the Performance Monitor data.
//
//  This file contains the definitions of the data structures returned
//  by the Configuration Registry in response to a request for
//  performance data.  This file is used by both the Configuration
//  Registry and the Performance Monitor to define their interface.
//  The complete interface is described here, except for the name
//  of the node to query in the registry.  It is
//
//                 HKEY_PERFORMANCE_DATA.
//
//  By querying that node with a subkey of "Global" the caller will
//  retrieve the structures described here.
//
//  There is no need to RegOpenKey() the reserved handle HKEY_PERFORMANCE_DATA,
//  but the caller should RegCloseKey() the handle so that network transports
//  and drivers can be removed or installed (which cannot happen while
//  they are open for monitoring.)  Remote requests must first
//  RegConnectRegistry().

//  Data structure definitions.

//  In order for data to be returned through the Configuration Registry
//  in a system-independent fashion, it must be self-describing.

//  In the following, all offsets are in bytes.

//
//  Data is returned through the Configuration Registry in a
//  a data block which begins with a _PERF_DATA_BLOCK structure.
//

const
  PERF_DATA_VERSION  = 1;
  {$EXTERNALSYM PERF_DATA_VERSION}
  PERF_DATA_REVISION = 1;
  {$EXTERNALSYM PERF_DATA_REVISION}

type
  PPERF_DATA_BLOCK = ^PERF_DATA_BLOCK;
  {$EXTERNALSYM PPERF_DATA_BLOCK}
  _PERF_DATA_BLOCK = record
    Signature: array [0..3] of WCHAR;   // Signature: Unicode "PERF"
    LittleEndian: DWORD;                // 0 = Big Endian, 1 = Little Endian
    Version: DWORD;                     // Version of these data structures
                                        // starting at 1
    Revision: DWORD;                    // Revision of these data structures
                                        // starting at 0 for each Version
    TotalByteLength: DWORD;             // Total length of data block
    HeaderLength: DWORD;                // Length of this structure
    NumObjectTypes: DWORD;              // Number of types of objects
                                        // being reported
    DefaultObject: LONG;                // Object Title Index of default
                                        // object to display when data from
                                        // this system is retrieved (-1 =
                                        // none, but this is not expected to
                                        // be used)
    SystemTime: SYSTEMTIME;             // Time at the system under
                                        // measurement
    PerfTime: LARGE_INTEGER;            // Performance counter value
                                        // at the system under measurement
    PerfFreq: LARGE_INTEGER;            // Performance counter frequency
                                        // at the system under measurement
    PerfTime100nSec: LARGE_INTEGER;     // Performance counter time in 100 nsec
                                        // units at the system under measurement
    SystemNameLength: DWORD;            // Length of the system name
    SystemNameOffset: DWORD;            // Offset, from beginning of this
                                        // structure, to name of system
                                        // being measured
  end;
  {$EXTERNALSYM _PERF_DATA_BLOCK}
  PERF_DATA_BLOCK = _PERF_DATA_BLOCK;
  {$EXTERNALSYM PERF_DATA_BLOCK}
  TPerfDataBlock = PERF_DATA_BLOCK;
  PPerfDataBlock = PPERF_DATA_BLOCK;

//
//  The _PERF_DATA_BLOCK structure is followed by NumObjectTypes of
//  data sections, one for each type of object measured.  Each object
//  type section begins with a _PERF_OBJECT_TYPE structure.
//

  PPERF_OBJECT_TYPE = ^PERF_OBJECT_TYPE;
  {$EXTERNALSYM PPERF_OBJECT_TYPE}
  _PERF_OBJECT_TYPE = record
    TotalByteLength: DWORD;             // Length of this object definition
                                        // including this structure, the
                                        // counter definitions, and the
                                        // instance definitions and the
                                        // counter blocks for each instance:
                                        // This is the offset from this
                                        // structure to the next object, if
                                        // any
    DefinitionLength: DWORD;            // Length of object definition,
                                        // which includes this structure
                                        // and the counter definition
                                        // structures for this object: this
                                        // is the offset of the first
                                        // instance or of the counters
                                        // for this object if there is
                                        // no instance
    HeaderLength: DWORD;                // Length of this structure: this
                                        // is the offset to the first
                                        // counter definition for this
                                        // object
    ObjectNameTitleIndex: DWORD;        // Index to name in Title Database
    ObjectNameTitle: LPWSTR;            // Initially NULL, for use by
                                        // analysis program to point to
                                        // retrieved title string
    ObjectHelpTitleIndex: DWORD;        // Index to Help in Title Database
    ObjectHelpTitle: LPWSTR;            // Initially NULL, for use by
                                        // analysis program to point to
                                        // retrieved title string
    DetailLevel: DWORD;                 // Object level of detail (for
                                        // controlling display complexity);
                                        // will be min of detail levels
                                        // for all this object's counters
    NumCounters: DWORD;                 // Number of counters in each
                                        // counter block (one counter
                                        // block per instance)
    DefaultCounter: LONG;               // Default counter to display when
                                        // this object is selected, index
                                        // starting at 0 (-1 = none, but
                                        // this is not expected to be used)
    NumInstances: LONG;                 // Number of object instances
                                        // for which counters are being
                                        // returned from the system under
                                        // measurement. If the object defined
                                        // will never have any instance data
                                        // structures (PERF_INSTANCE_DEFINITION)
                                        // then this value should be -1, if the
                                        // object can have 0 or more instances,
                                        // but has none present, then this
                                        // should be 0, otherwise this field
                                        // contains the number of instances of
                                        // this counter.
    CodePage: DWORD;                    // 0 if instance strings are in
                                        // UNICODE, else the Code Page of
                                        // the instance names
    PerfTime: LARGE_INTEGER;            // Sample Time in "Object" units
    PerfFreq: LARGE_INTEGER;            // Frequency of "Object" units in
                                        // counts per second.
  end;
  {$EXTERNALSYM _PERF_OBJECT_TYPE}
  PERF_OBJECT_TYPE = _PERF_OBJECT_TYPE;
  {$EXTERNALSYM PERF_OBJECT_TYPE}
  TPerfObjectType = PERF_OBJECT_TYPE;
  PPerfObjectType = PPERF_OBJECT_TYPE;

const
  PERF_NO_INSTANCES = -1;               // no instances (see NumInstances above)
  {$EXTERNALSYM PERF_NO_INSTANCES}

//
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
//
//  PERF_COUNTER_DEFINITION.CounterType field values
//
//
//        Counter ID Field Definition:
//
//   3      2        2    2    2        1        1    1
//   1      8        4    2    0        6        2    0    8                0
//  +--------+--------+----+----+--------+--------+----+----+----------------+
//  |Display |Calculation  |Time|Counter |        |Ctr |Size|                |
//  |Flags   |Modifiers    |Base|SubType |Reserved|Type|Fld |   Reserved     |
//  +--------+--------+----+----+--------+--------+----+----+----------------+
//
//
//  The counter type is the "or" of the following values as described below
//
//  select one of the following to indicate the counter's data size
//

  PERF_SIZE_DWORD         = $00000000;
  {$EXTERNALSYM PERF_SIZE_DWORD}
  PERF_SIZE_LARGE         = $00000100;
  {$EXTERNALSYM PERF_SIZE_LARGE}
  PERF_SIZE_ZERO          = $00000200;      // for Zero Length Fields
  {$EXTERNALSYM PERF_SIZE_ZERO}
  PERF_SIZE_VARIABLE_LEN  = $00000300;      // length is in CounterLength Fields
                                            //  of Counter Definition struct
  {$EXTERNALSYM PERF_SIZE_VARIABLE_LEN}

//
//  select one of the following values to indicate the counter field usage
//

  PERF_TYPE_NUMBER        = $00000000;      // a number (not a counter)
  {$EXTERNALSYM PERF_TYPE_NUMBER}
  PERF_TYPE_COUNTER       = $00000400;      // an increasing numeric Value
  {$EXTERNALSYM PERF_TYPE_COUNTER}
  PERF_TYPE_TEXT          = $00000800;      // a text Fields
  {$EXTERNALSYM PERF_TYPE_TEXT}
  PERF_TYPE_ZERO          = $00000C00;      // displays a zero
  {$EXTERNALSYM PERF_TYPE_ZERO}

//
//  If the PERF_TYPE_NUMBER field was selected, then select one of the
//  following to describe the Number
//

  PERF_NUMBER_HEX         = $00000000;     // display as HEX Value
  {$EXTERNALSYM PERF_NUMBER_HEX}
  PERF_NUMBER_DECIMAL     = $00010000;     // display as a decimal integer
  {$EXTERNALSYM PERF_NUMBER_DECIMAL}
  PERF_NUMBER_DEC_1000    = $00020000;     // display as a decimal/1000
  {$EXTERNALSYM PERF_NUMBER_DEC_1000}

//
//  If the PERF_TYPE_COUNTER value was selected then select one of the
//  following to indicate the type of counter
//

  PERF_COUNTER_VALUE      = $00000000;     // display counter Value
  {$EXTERNALSYM PERF_COUNTER_VALUE}
  PERF_COUNTER_RATE       = $00010000;     // divide ctr / delta time
  {$EXTERNALSYM PERF_COUNTER_RATE}
  PERF_COUNTER_FRACTION   = $00020000;     // divide ctr / base
  {$EXTERNALSYM PERF_COUNTER_FRACTION}
  PERF_COUNTER_BASE       = $00030000;     // base value used in fractions
  {$EXTERNALSYM PERF_COUNTER_BASE}
  PERF_COUNTER_ELAPSED    = $00040000;     // subtract counter from current time
  {$EXTERNALSYM PERF_COUNTER_ELAPSED}
  PERF_COUNTER_QUEUELEN   = $00050000;     // Use Queuelen processing func.
  {$EXTERNALSYM PERF_COUNTER_QUEUELEN}
  PERF_COUNTER_HISTOGRAM  = $00060000;     // Counter begins or ends a histogram
  {$EXTERNALSYM PERF_COUNTER_HISTOGRAM}
  PERF_COUNTER_PRECISION  = $00070000;     // divide ctr / private clock
  {$EXTERNALSYM PERF_COUNTER_PRECISION}

//
//  If the PERF_TYPE_TEXT value was selected, then select one of the
//  following to indicate the type of TEXT data.
//

  PERF_TEXT_UNICODE       = $00000000;     // type of text in text Fields
  {$EXTERNALSYM PERF_TEXT_UNICODE}
  PERF_TEXT_ASCII         = $00010000;     // ASCII using the CodePage Fields
  {$EXTERNALSYM PERF_TEXT_ASCII}

//
//  Timer SubTypes
//

  PERF_TIMER_TICK         = $00000000;     // use system perf. freq for base
  {$EXTERNALSYM PERF_TIMER_TICK}
  PERF_TIMER_100NS        = $00100000;     // use 100 NS timer time base units
  {$EXTERNALSYM PERF_TIMER_100NS}
  PERF_OBJECT_TIMER       = $00200000;     // use the object timer freq
  {$EXTERNALSYM PERF_OBJECT_TIMER}

//
//  Any types that have calculations performed can use one or more of
//  the following calculation modification flags listed here
//

  PERF_DELTA_COUNTER      = $00400000;     // compute difference First
  {$EXTERNALSYM PERF_DELTA_COUNTER}
  PERF_DELTA_BASE         = $00800000;     // compute base diff as well
  {$EXTERNALSYM PERF_DELTA_BASE}
  PERF_INVERSE_COUNTER    = $01000000;     // show as 1.00-value (assumes:
  {$EXTERNALSYM PERF_INVERSE_COUNTER}
  PERF_MULTI_COUNTER      = $02000000;     // sum of multiple instances
  {$EXTERNALSYM PERF_MULTI_COUNTER}

//
//  Select one of the following values to indicate the display suffix (if any)
//

  PERF_DISPLAY_NO_SUFFIX  = $00000000;     // no suffix
  {$EXTERNALSYM PERF_DISPLAY_NO_SUFFIX}
  PERF_DISPLAY_PER_SEC    = $10000000;     // "/sec"
  {$EXTERNALSYM PERF_DISPLAY_PER_SEC}
  PERF_DISPLAY_PERCENT    = $20000000;     // "%"
  {$EXTERNALSYM PERF_DISPLAY_PERCENT}
  PERF_DISPLAY_SECONDS    = $30000000;     // "secs"
  {$EXTERNALSYM PERF_DISPLAY_SECONDS}
  PERF_DISPLAY_NOSHOW     = $40000000;     // value is not displayed
  {$EXTERNALSYM PERF_DISPLAY_NOSHOW}

//
//  Predefined counter types
//

// 32-bit Counter.  Divide delta by delta time.  Display suffix: "/sec"

  PERF_COUNTER_COUNTER =
            PERF_SIZE_DWORD or PERF_TYPE_COUNTER or PERF_COUNTER_RATE or
            PERF_TIMER_TICK or PERF_DELTA_COUNTER or PERF_DISPLAY_PER_SEC;
  {$EXTERNALSYM PERF_COUNTER_COUNTER}

// 64-bit Timer.  Divide delta by delta time.  Display suffix: "%"

  PERF_COUNTER_TIMER =
            PERF_SIZE_LARGE or PERF_TYPE_COUNTER or PERF_COUNTER_RATE or
            PERF_TIMER_TICK or PERF_DELTA_COUNTER or PERF_DISPLAY_PERCENT;
  {$EXTERNALSYM PERF_COUNTER_TIMER}

// Queue Length Space-Time Product. Divide delta by delta time. No Display Suffix.

  PERF_COUNTER_QUEUELEN_TYPE =
            PERF_SIZE_DWORD or PERF_TYPE_COUNTER or PERF_COUNTER_QUEUELEN or
            PERF_TIMER_TICK or PERF_DELTA_COUNTER or PERF_DISPLAY_NO_SUFFIX;
  {$EXTERNALSYM PERF_COUNTER_QUEUELEN_TYPE}

// Queue Length Space-Time Product. Divide delta by delta time. No Display Suffix.

  PERF_COUNTER_LARGE_QUEUELEN_TYPE =
            PERF_SIZE_LARGE or PERF_TYPE_COUNTER or PERF_COUNTER_QUEUELEN or
            PERF_TIMER_TICK or PERF_DELTA_COUNTER or PERF_DISPLAY_NO_SUFFIX;
  {$EXTERNALSYM PERF_COUNTER_LARGE_QUEUELEN_TYPE}

// Queue Length Space-Time Product using 100 Ns timebase.
// Divide delta by delta time. No Display Suffix.

  PERF_COUNTER_100NS_QUEUELEN_TYPE =
            PERF_SIZE_LARGE or PERF_TYPE_COUNTER or PERF_COUNTER_QUEUELEN or
            PERF_TIMER_100NS or PERF_DELTA_COUNTER or PERF_DISPLAY_NO_SUFFIX;
  {$EXTERNALSYM PERF_COUNTER_100NS_QUEUELEN_TYPE}

// Queue Length Space-Time Product using Object specific timebase.
// Divide delta by delta time. No Display Suffix.

  PERF_COUNTER_OBJ_TIME_QUEUELEN_TYPE =
            PERF_SIZE_LARGE or PERF_TYPE_COUNTER or PERF_COUNTER_QUEUELEN or
            PERF_OBJECT_TIMER or PERF_DELTA_COUNTER or PERF_DISPLAY_NO_SUFFIX;
  {$EXTERNALSYM PERF_COUNTER_OBJ_TIME_QUEUELEN_TYPE}

// 64-bit Counter.  Divide delta by delta time. Display Suffix: "/sec"

  PERF_COUNTER_BULK_COUNT =
            PERF_SIZE_LARGE or PERF_TYPE_COUNTER or PERF_COUNTER_RATE or
            PERF_TIMER_TICK or PERF_DELTA_COUNTER or PERF_DISPLAY_PER_SEC;
  {$EXTERNALSYM PERF_COUNTER_BULK_COUNT}

// Indicates the counter is not a  counter but rather Unicode text Display as text.

  PERF_COUNTER_TEXT =
            PERF_SIZE_VARIABLE_LEN or PERF_TYPE_TEXT or PERF_TEXT_UNICODE or
            PERF_DISPLAY_NO_SUFFIX;
  {$EXTERNALSYM PERF_COUNTER_TEXT}

// Indicates the data is a counter  which should not be
// time averaged on display (such as an error counter on a serial line)
// Display as is.  No Display Suffix.

  PERF_COUNTER_RAWCOUNT =
            PERF_SIZE_DWORD or PERF_TYPE_NUMBER or PERF_NUMBER_DECIMAL or
            PERF_DISPLAY_NO_SUFFIX;
  {$EXTERNALSYM PERF_COUNTER_RAWCOUNT}

// Same as PERF_COUNTER_RAWCOUNT except its size is a large integer

  PERF_COUNTER_LARGE_RAWCOUNT =
            PERF_SIZE_LARGE or PERF_TYPE_NUMBER or PERF_NUMBER_DECIMAL or
            PERF_DISPLAY_NO_SUFFIX;
  {$EXTERNALSYM PERF_COUNTER_LARGE_RAWCOUNT}

// Special case for RAWCOUNT that want to be displayed in hex
// Indicates the data is a counter  which should not be
// time averaged on display (such as an error counter on a serial line)
// Display as is.  No Display Suffix.

  PERF_COUNTER_RAWCOUNT_HEX =
            PERF_SIZE_DWORD or PERF_TYPE_NUMBER or PERF_NUMBER_HEX or
            PERF_DISPLAY_NO_SUFFIX;
  {$EXTERNALSYM PERF_COUNTER_RAWCOUNT_HEX}

// Same as PERF_COUNTER_RAWCOUNT_HEX except its size is a large integer

  PERF_COUNTER_LARGE_RAWCOUNT_HEX =
            PERF_SIZE_LARGE or PERF_TYPE_NUMBER or PERF_NUMBER_HEX or
            PERF_DISPLAY_NO_SUFFIX;
  {$EXTERNALSYM PERF_COUNTER_LARGE_RAWCOUNT_HEX}

// A count which is either 1 or 0 on each sampling interrupt (% busy)
// Divide delta by delta base. Display Suffix: "%"

  PERF_SAMPLE_FRACTION =
            PERF_SIZE_DWORD or PERF_TYPE_COUNTER or PERF_COUNTER_FRACTION or
            PERF_DELTA_COUNTER or PERF_DELTA_BASE or PERF_DISPLAY_PERCENT;
  {$EXTERNALSYM PERF_SAMPLE_FRACTION}

// A count which is sampled on each sampling interrupt (queue length)
// Divide delta by delta time. No Display Suffix.

  PERF_SAMPLE_COUNTER =
            PERF_SIZE_DWORD or PERF_TYPE_COUNTER or PERF_COUNTER_RATE or
            PERF_TIMER_TICK or PERF_DELTA_COUNTER or PERF_DISPLAY_NO_SUFFIX;
  {$EXTERNALSYM PERF_SAMPLE_COUNTER}

// A label: no data is associated with this counter (it has 0 length)
// Do not display.

  PERF_COUNTER_NODATA =
            PERF_SIZE_ZERO or PERF_DISPLAY_NOSHOW;
  {$EXTERNALSYM PERF_COUNTER_NODATA}

// 64-bit Timer inverse (e.g., idle is measured, but display busy %)
// Display 100 - delta divided by delta time.  Display suffix: "%"

  PERF_COUNTER_TIMER_INV =
            PERF_SIZE_LARGE or PERF_TYPE_COUNTER or PERF_COUNTER_RATE or
            PERF_TIMER_TICK or PERF_DELTA_COUNTER or PERF_INVERSE_COUNTER or
            PERF_DISPLAY_PERCENT;
  {$EXTERNALSYM PERF_COUNTER_TIMER_INV}

// The divisor for a sample, used with the previous counter to form a
// sampled %.  You must check for >0 before dividing by this!  This
// counter will directly follow the  numerator counter.  It should not
// be displayed to the user.

  PERF_SAMPLE_BASE =
            PERF_SIZE_DWORD or PERF_TYPE_COUNTER or PERF_COUNTER_BASE or
            PERF_DISPLAY_NOSHOW or
            $00000001;  // for compatibility with pre-beta versions
  {$EXTERNALSYM PERF_SAMPLE_BASE}

// A timer which, when divided by an average base, produces a time
// in seconds which is the average time of some operation.  This
// timer times total operations, and  the base is the number of opera-
// tions.  Display Suffix: "sec"

  PERF_AVERAGE_TIMER =
            PERF_SIZE_DWORD or PERF_TYPE_COUNTER or PERF_COUNTER_FRACTION or
            PERF_DISPLAY_SECONDS;
  {$EXTERNALSYM PERF_AVERAGE_TIMER}

// Used as the denominator in the computation of time or count
// averages.  Must directly follow the numerator counter.  Not dis-
// played to the user.

  PERF_AVERAGE_BASE =
            PERF_SIZE_DWORD or PERF_TYPE_COUNTER or PERF_COUNTER_BASE or
            PERF_DISPLAY_NOSHOW or
            $00000002;  // for compatibility with pre-beta versions
  {$EXTERNALSYM PERF_AVERAGE_BASE}

// A bulk count which, when divided (typically) by the number of
// operations, gives (typically) the number of bytes per operation.
// No Display Suffix.

  PERF_AVERAGE_BULK =
            PERF_SIZE_LARGE or PERF_TYPE_COUNTER or PERF_COUNTER_FRACTION  or
            PERF_DISPLAY_NOSHOW;
  {$EXTERNALSYM PERF_AVERAGE_BULK}

// 64-bit Timer in object specific units. Display delta divided by
// delta time as returned in the object type header structure.  Display suffix: "%"

  PERF_OBJ_TIME_TIMER =
            PERF_SIZE_LARGE or PERF_TYPE_COUNTER or PERF_COUNTER_RATE or
            PERF_OBJECT_TIMER or PERF_DELTA_COUNTER or PERF_DISPLAY_PERCENT;
  {$EXTERNALSYM PERF_OBJ_TIME_TIMER}

// 64-bit Timer in 100 nsec units. Display delta divided by
// delta time.  Display suffix: "%"

  PERF_100NSEC_TIMER =
            PERF_SIZE_LARGE or PERF_TYPE_COUNTER or PERF_COUNTER_RATE or
            PERF_TIMER_100NS or PERF_DELTA_COUNTER or PERF_DISPLAY_PERCENT;
  {$EXTERNALSYM PERF_100NSEC_TIMER}

// 64-bit Timer inverse (e.g., idle is measured, but display busy %)
// Display 100 - delta divided by delta time.  Display suffix: "%"

  PERF_100NSEC_TIMER_INV =
            PERF_SIZE_LARGE or PERF_TYPE_COUNTER or PERF_COUNTER_RATE or
            PERF_TIMER_100NS or PERF_DELTA_COUNTER or PERF_INVERSE_COUNTER  or
            PERF_DISPLAY_PERCENT;
  {$EXTERNALSYM PERF_100NSEC_TIMER_INV}

// 64-bit Timer.  Divide delta by delta time.  Display suffix: "%"
// Timer for multiple instances, so result can exceed 100%.

  PERF_COUNTER_MULTI_TIMER =
            PERF_SIZE_LARGE or PERF_TYPE_COUNTER or PERF_COUNTER_RATE or
            PERF_DELTA_COUNTER or PERF_TIMER_TICK or PERF_MULTI_COUNTER or
            PERF_DISPLAY_PERCENT;
  {$EXTERNALSYM PERF_COUNTER_MULTI_TIMER}

// 64-bit Timer inverse (e.g., idle is measured, but display busy %)
// Display 100 * _MULTI_BASE - delta divided by delta time.
// Display suffix: "%" Timer for multiple instances, so result
// can exceed 100%.  Followed by a counter of type _MULTI_BASE.

  PERF_COUNTER_MULTI_TIMER_INV =
            PERF_SIZE_LARGE or PERF_TYPE_COUNTER or PERF_COUNTER_RATE or
            PERF_DELTA_COUNTER or PERF_MULTI_COUNTER or PERF_TIMER_TICK or
            PERF_INVERSE_COUNTER or PERF_DISPLAY_PERCENT;
  {$EXTERNALSYM PERF_COUNTER_MULTI_TIMER_INV}

// Number of instances to which the preceding _MULTI_..._INV counter
// applies.  Used as a factor to get the percentage.

  PERF_COUNTER_MULTI_BASE =
            PERF_SIZE_LARGE or PERF_TYPE_COUNTER or PERF_COUNTER_BASE or
            PERF_MULTI_COUNTER or PERF_DISPLAY_NOSHOW;
  {$EXTERNALSYM PERF_COUNTER_MULTI_BASE}

// 64-bit Timer in 100 nsec units. Display delta divided by delta time.
// Display suffix: "%" Timer for multiple instances, so result can exceed 100%.

  PERF_100NSEC_MULTI_TIMER =
            PERF_SIZE_LARGE or PERF_TYPE_COUNTER or PERF_DELTA_COUNTER or
            PERF_COUNTER_RATE or PERF_TIMER_100NS or PERF_MULTI_COUNTER or
            PERF_DISPLAY_PERCENT;
  {$EXTERNALSYM PERF_100NSEC_MULTI_TIMER}

// 64-bit Timer inverse (e.g., idle is measured, but display busy %)
// Display 100 * _MULTI_BASE - delta divided by delta time.
// Display suffix: "%" Timer for multiple instances, so result
// can exceed 100%.  Followed by a counter of type _MULTI_BASE.

  PERF_100NSEC_MULTI_TIMER_INV =
            PERF_SIZE_LARGE or PERF_TYPE_COUNTER or PERF_DELTA_COUNTER or
            PERF_COUNTER_RATE or PERF_TIMER_100NS or PERF_MULTI_COUNTER or
            PERF_INVERSE_COUNTER or PERF_DISPLAY_PERCENT;
  {$EXTERNALSYM PERF_100NSEC_MULTI_TIMER_INV}

// Indicates the data is a fraction of the following counter  which
// should not be time averaged on display (such as free space over
// total space.) Display as is.  Display the quotient as "%".

  PERF_RAW_FRACTION =
            PERF_SIZE_DWORD or PERF_TYPE_COUNTER or PERF_COUNTER_FRACTION or
            PERF_DISPLAY_PERCENT;
  {$EXTERNALSYM PERF_RAW_FRACTION}

  PERF_LARGE_RAW_FRACTION =
            PERF_SIZE_LARGE or PERF_TYPE_COUNTER or PERF_COUNTER_FRACTION or
            PERF_DISPLAY_PERCENT;
  {$EXTERNALSYM PERF_LARGE_RAW_FRACTION}

// Indicates the data is a base for the preceding counter which should
// not be time averaged on display (such as free space over total space.)

  PERF_RAW_BASE =
            PERF_SIZE_DWORD or PERF_TYPE_COUNTER or PERF_COUNTER_BASE or
            PERF_DISPLAY_NOSHOW or
            $00000003;  // for compatibility with pre-beta versions
  {$EXTERNALSYM PERF_RAW_BASE}

  PERF_LARGE_RAW_BASE =
            PERF_SIZE_LARGE or PERF_TYPE_COUNTER or PERF_COUNTER_BASE or
            PERF_DISPLAY_NOSHOW;
  {$EXTERNALSYM PERF_LARGE_RAW_BASE}

// The data collected in this counter is actually the start time of the
// item being measured. For display, this data is subtracted from the
// sample time to yield the elapsed time as the difference between the two.
// In the definition below, the PerfTime field of the Object contains
// the sample time as indicated by the PERF_OBJECT_TIMER bit and the
// difference is scaled by the PerfFreq of the Object to convert the time
// units into seconds.

  PERF_ELAPSED_TIME =
            PERF_SIZE_LARGE or PERF_TYPE_COUNTER or PERF_COUNTER_ELAPSED or
            PERF_OBJECT_TIMER or PERF_DISPLAY_SECONDS;
  {$EXTERNALSYM PERF_ELAPSED_TIME}

//
//  The following counter type can be used with the preceding types to
//  define a range of values to be displayed in a histogram.
//

  PERF_COUNTER_HISTOGRAM_TYPE = $80000000; // Counter begins or ends a histogram
  {$EXTERNALSYM PERF_COUNTER_HISTOGRAM_TYPE}

//
//  This counter is used to display the difference from one sample
//  to the next. The counter value is a constantly increasing number
//  and the value displayed is the difference between the current
//  value and the previous value. Negative numbers are not allowed
//  which shouldn't be a problem as long as the counter value is
//  increasing or unchanged.
//

  PERF_COUNTER_DELTA =
            PERF_SIZE_DWORD or PERF_TYPE_COUNTER or PERF_COUNTER_VALUE or
            PERF_DELTA_COUNTER or PERF_DISPLAY_NO_SUFFIX;
  {$EXTERNALSYM PERF_COUNTER_DELTA}

  PERF_COUNTER_LARGE_DELTA =
            PERF_SIZE_LARGE or PERF_TYPE_COUNTER or PERF_COUNTER_VALUE or
            PERF_DELTA_COUNTER or PERF_DISPLAY_NO_SUFFIX;
  {$EXTERNALSYM PERF_COUNTER_LARGE_DELTA}

//
//  The precision counters are timers that consist of two counter values:
//      1) the count of elapsed time of the event being monitored
//      2) the "clock" time in the same units
//
//  the precition timers are used where the standard system timers are not
//  precise enough for accurate readings. It's assumed that the service
//  providing the data is also providing a timestamp at the same time which
//  will eliminate any error that may occur since some small and variable
//  time elapses between the time the system timestamp is captured and when
//  the data is collected from the performance DLL. Only in extreme cases
//  has this been observed to be problematic.
//
//  when using this type of timer, the definition of the
//      PERF_PRECISION_TIMESTAMP counter must immediately follow the
//      definition of the PERF_PRECISION_*_TIMER in the Object header
//
// The timer used has the same frequency as the System Performance Timer

  PERF_PRECISION_SYSTEM_TIMER =
        PERF_SIZE_LARGE or PERF_TYPE_COUNTER or PERF_COUNTER_PRECISION or
        PERF_TIMER_TICK or PERF_DELTA_COUNTER or PERF_DISPLAY_PERCENT;
  {$EXTERNALSYM PERF_PRECISION_SYSTEM_TIMER}

//
// The timer used has the same frequency as the 100 NanoSecond Timer

  PERF_PRECISION_100NS_TIMER =
        PERF_SIZE_LARGE or PERF_TYPE_COUNTER or PERF_COUNTER_PRECISION or
        PERF_TIMER_100NS or PERF_DELTA_COUNTER or PERF_DISPLAY_PERCENT;
  {$EXTERNALSYM PERF_PRECISION_100NS_TIMER}

//
// The timer used is of the frequency specified in the Object header's
//  PerfFreq field (PerfTime is ignored)

  PERF_PRECISION_OBJECT_TIMER =
        PERF_SIZE_LARGE or PERF_TYPE_COUNTER or PERF_COUNTER_PRECISION or
        PERF_OBJECT_TIMER or PERF_DELTA_COUNTER or PERF_DISPLAY_PERCENT;
  {$EXTERNALSYM PERF_PRECISION_OBJECT_TIMER}

//
// This is the timestamp to use in the computation of the timer specified
// in the previous description block

  PERF_PRECISION_TIMESTAMP = PERF_LARGE_RAW_BASE;
  {$EXTERNALSYM PERF_PRECISION_TIMESTAMP}

//
//  The following are used to determine the level of detail associated
//  with the counter.  The user will be setting the level of detail
//  that should be displayed at any given time.
//
//

  PERF_DETAIL_NOVICE         = 100; // The uninformed can understand it
  {$EXTERNALSYM PERF_DETAIL_NOVICE}
  PERF_DETAIL_ADVANCED       = 200; // For the advanced user
  {$EXTERNALSYM PERF_DETAIL_ADVANCED}
  PERF_DETAIL_EXPERT         = 300; // For the expert user
  {$EXTERNALSYM PERF_DETAIL_EXPERT}
  PERF_DETAIL_WIZARD         = 400; // For the system designer
  {$EXTERNALSYM PERF_DETAIL_WIZARD}

//
//
//  There is one of the following for each of the
//  PERF_OBJECT_TYPE.NumCounters.  The Unicode names in this structure MUST
//  come from a message file.
//
//

type
  PPERF_COUNTER_DEFINITION = ^PERF_COUNTER_DEFINITION;
  {$EXTERNALSYM PPERF_COUNTER_DEFINITION}
  _PERF_COUNTER_DEFINITION = record
    ByteLength: DWORD;                  // Length in bytes of this structure
    CounterNameTitleIndex: DWORD;       // Index of Counter name into
                                        // Title Database
    CounterNameTitle: LPWSTR;           // Initially NULL, for use by
                                        // analysis program to point to
                                        // retrieved title string
    CounterHelpTitleIndex: DWORD;       // Index of Counter Help into
                                        // Title Database
    CounterHelpTitle: LPWSTR;           // Initially NULL, for use by
                                        // analysis program to point to
                                        // retrieved title string
    DefaultScale: LONG;                 // Power of 10 by which to scale
                                        // chart line if vertical axis is 100
                                        // 0 ==> 1, 1 ==> 10, -1 ==>1/10, etc.
    DetailLevel: DWORD;                 // Counter level of detail (for
                                        // controlling display complexity)
    CounterType: DWORD;                 // Type of counter
    CounterSize: DWORD;                 // Size of counter in bytes
    CounterOffset: DWORD;               // Offset from the start of the
                                        // PERF_COUNTER_BLOCK to the first
                                        // byte of this counter
  end;
  {$EXTERNALSYM _PERF_COUNTER_DEFINITION}
  PERF_COUNTER_DEFINITION = _PERF_COUNTER_DEFINITION;
  {$EXTERNALSYM PERF_COUNTER_DEFINITION}
  TPerfCounterDefinition = PERF_COUNTER_DEFINITION;
  PPerfCounterDefinition = PPERF_COUNTER_DEFINITION;

//
//
//  If (PERF_DATA_BLOCK.NumInstances >= 0) then there will be
//  PERF_DATA_BLOCK.NumInstances of a (PERF_INSTANCE_DEFINITION
//  followed by a PERF_COUNTER_BLOCK followed by the counter data fields)
//  for each instance.
//
//  If (PERF_DATA_BLOCK.NumInstances < 0) then the counter definition
//  strucutre above will be followed by only a PERF_COUNTER_BLOCK and the
//  counter data for that COUNTER.
//

const
  PERF_NO_UNIQUE_ID = -1;
  {$EXTERNALSYM PERF_NO_UNIQUE_ID}

type
  PPERF_INSTANCE_DEFINITION = ^PERF_INSTANCE_DEFINITION;
  {$EXTERNALSYM PPERF_INSTANCE_DEFINITION}
  _PERF_INSTANCE_DEFINITION = record
    ByteLength: DWORD;                  // Length in bytes of this structure,
                                        // including the subsequent name
    ParentObjectTitleIndex: DWORD;      // Title Index to name of "parent"
                                        // object (e.g., if thread, then
                                        // process is parent object type);
                                        // if logical drive, the physical
                                        // drive is parent object type
    ParentObjectInstance: DWORD;        // Index to instance of parent object
                                        // type which is the parent of this
                                        // instance.
    UniqueID: LONG;                     // A unique ID used instead of
                                        // matching the name to identify
                                        // this instance, -1 = none
    NameOffset: DWORD;                  // Offset from beginning of
                                        // this struct to the Unicode name
                                        // of this instance
    NameLength: DWORD;                  // Length in bytes of name; 0 = none
                                        // this length includes the characters
                                        // in the string plus the size of the
                                        // terminating NULL char. It does not
                                        // include any additional pad bytes to
                                        // correct structure alignment
  end;
  {$EXTERNALSYM _PERF_INSTANCE_DEFINITION}
  PERF_INSTANCE_DEFINITION = _PERF_INSTANCE_DEFINITION;
  {$EXTERNALSYM PERF_INSTANCE_DEFINITION}
  TPerfInstanceDefinition = PERF_INSTANCE_DEFINITION;
  PPerfInstanceDefinition = PPERF_INSTANCE_DEFINITION;

//
//  If .ParentObjectName is 0, there
//  is no parent-child hierarchy for this object type.  Otherwise,
//   the .ParentObjectInstance is an index, starting at 0, into the
//  instances reported for the parent object type.  It is only
//  meaningful if .ParentObjectName is not 0.  The purpose of all this
//  is to permit reporting/summation of object instances like threads
//  within processes, and logical drives within physical drives.
//
//
//  The PERF_INSTANCE_DEFINITION will be followed by a PERF_COUNTER_BLOCK.
//

  PPERF_COUNTER_BLOCK = ^PERF_COUNTER_BLOCK;
  {$EXTERNALSYM PPERF_COUNTER_BLOCK}
  _PERF_COUNTER_BLOCK = record
    ByteLength: DWORD;                  // Length in bytes of this structure,
                                        // including the following counters
  end;
  {$EXTERNALSYM _PERF_COUNTER_BLOCK}
  PERF_COUNTER_BLOCK = _PERF_COUNTER_BLOCK;
  {$EXTERNALSYM PERF_COUNTER_BLOCK}
  TPerfCounterBlock = PERF_COUNTER_BLOCK;
  PPerfCounterBlock = PPERF_COUNTER_BLOCK;

//
//  The PERF_COUNTER_BLOCK is followed by PERF_OBJECT_TYPE.NumCounters
//  number of counters.
//

//
// Support for New Extensible API starting with NT 5.0
//

const
  PERF_QUERY_OBJECTS = DWORD($80000000);
  {$EXTERNALSYM PERF_QUERY_OBJECTS}
  PERF_QUERY_GLOBAL  = DWORD($80000001);
  {$EXTERNALSYM PERF_QUERY_GLOBAL}
  PERF_QUERY_COSTLY  = DWORD($80000002);
  {$EXTERNALSYM PERF_QUERY_COSTLY}

//
//  function typedefs for extensible counter function prototypes
//

type
  PM_OPEN_PROC = function (Arg1: LPWSTR): DWORD; stdcall;
  {$EXTERNALSYM PM_OPEN_PROC}
  PM_COLLECT_PROC = function (Arg1: LPWSTR; Arg2: Pointer; Arg3, Arg4: LPDWORD): DWORD; stdcall;
  {$EXTERNALSYM PM_COLLECT_PROC}
  PM_CLOSE_PROC = function: DWORD; stdcall;
  {$EXTERNALSYM PM_CLOSE_PROC}
  PM_QUERY_PROC = function (Arg1: LPDWORD; Arg2: Pointer; Arg3, Arg4: LPDWORD): DWORD; stdcall;
  {$EXTERNALSYM PM_QUERY_PROC}

const
  MAX_PERF_OBJECTS_IN_QUERY_FUNCTION = LONG(64);
  {$EXTERNALSYM MAX_PERF_OBJECTS_IN_QUERY_FUNCTION}

//
// The following are the possible values for
// HKLM\SOFTWARE\Microsoft\Windows NT\CurrentVersion\Perflib\EventLogLevel
// The default is WINPERF_LOG_NONE if the registry value is not defined.
// This should be adopted by all perfdlls to avoid flooding the application
// event log.
//

const
  WINPERF_LOG_NONE      = 0;          // No event reported
  {$EXTERNALSYM WINPERF_LOG_NONE}
  WINPERF_LOG_USER      = 1;          // Report only errors
  {$EXTERNALSYM WINPERF_LOG_USER}
  WINPERF_LOG_DEBUG     = 2;          // Report debug errors as well
  {$EXTERNALSYM WINPERF_LOG_DEBUG}
  WINPERF_LOG_VERBOSE   = 3;          // Report everything
  {$EXTERNALSYM WINPERF_LOG_VERBOSE}

implementation

end.
