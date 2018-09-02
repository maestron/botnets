{******************************************************************************}
{                                                       	               }
{ Scheduler API interface Unit for Object Pascal                               }
{                                                       	               }
{ Portions created by Microsoft are Copyright (C) 1995-2001 Microsoft          }
{ Corporation. All Rights Reserved.                                            }
{ 								               }
{ The original file is: schedule.h, released June 2000. The original Pascal    }
{ code is: Schedule.pas, released December 2000. The initial developer of the  }
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

unit JwaSchedule;

{$WEAKPACKAGEUNIT}

{$HPPEMIT ''}
{$HPPEMIT '#include "schedule.h"'}
{$HPPEMIT ''}

{$I WINDEFINES.INC}

interface

uses
  JwaWinType;

//
// The DS and FRS use the same structure to represent different schedules.
// The DS uses a 15-minute polling schedule. FRS uses a 60-minute
// start/stop schedule. Hence, the schedule for the system volume is
// a special case because we only have the DS schedule to work from.
// We will work around this problem by treating the 15
// -minute polling schedule as a 60-minute start/stop schedule.
// Replication is enabled for any hour that has any of the four
// 15-minute bits set.
//
// When the ReplicationSchedule is not present the default is
// "always replicate."
//

//
// Only the interval schedule is currently implemented. Others are ignored.
//

const
  SCHEDULE_INTERVAL      = 0; // schedule as understood by NT5
  {$EXTERNALSYM SCHEDULE_INTERVAL}
  SCHEDULE_BANDWIDTH     = 1; // bandwidth as understood by NT5
  {$EXTERNALSYM SCHEDULE_BANDWIDTH}
  SCHEDULE_PRIORITY      = 2; // priority as understood by NT5
  {$EXTERNALSYM SCHEDULE_PRIORITY}

//
// Schedule Header
//
// Each schedule blob begins with n array of schedule headers that
// specify the number and type of schedules contained in the blob.
//

type
  PSCHEDULE_HEADER = ^SCHEDULE_HEADER;
  {$EXTERNALSYM PSCHEDULE_HEADER}
  _SCHEDULE_HEADER = record
    Type_: ULONG;       // one of the SCHEDULE_ ordinals
    Offset: ULONG;      // offset from start of schedule structure
  end;
  {$EXTERNALSYM _SCHEDULE_HEADER}
  SCHEDULE_HEADER = _SCHEDULE_HEADER;
  {$EXTERNALSYM SCHEDULE_HEADER}
  TScheduleHeader = SCHEDULE_HEADER;
  PScheduleHeader = PSCHEDULE_HEADER;

//
// Schedule
//

  PSCHEDULE = ^_SCHEDULE;
  {$EXTERNALSYM PSCHEDULE}
  _SCHEDULE = record
    Size: ULONG;           // inclusive size in bytes
    Bandwidth: ULONG;
    NumberOfSchedules: ULONG;
    Schedules: array [0..0] of SCHEDULE_HEADER;
  end;
  {$EXTERNALSYM _SCHEDULE}
  //SCHEDULE = _SCHEDULE;
  //{$EXTERNALSYM SCHEDULE}
  TSchedule = _SCHEDULE;

// The above structure is followed by the Data buffer and the
// SCHEDULE_HEADER contains offsets to refer to the appropriate
// parts in the data buffer.

const
  SCHEDULE_DATA_ENTRIES = (7 * 24);    // 7 days X 24 hours
  {$EXTERNALSYM SCHEDULE_DATA_ENTRIES}
  
implementation

end.
