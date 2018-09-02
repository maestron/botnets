{******************************************************************************}
{                                                       	               }
{ Microsoft Task Scheduler API interface Unit for Object Pascal                }
{                                                       	               }
{ Portions created by Microsoft are Copyright (C) 1995-2001 Microsoft          }
{ Corporation. All Rights Reserved.                                            }
{ 								               }
{ The original file is: mstask.h, released August 2001. The original Pascal    }
{ code is: MsTask.pas, released October 2001. The initial developer of the     }
{ Pascal code is Marcel van Brakel (brakelm@chello.nl).                        }
{                                                                              }
{ Portions created by Marcel van Brakel are Copyright (C) 1999-2001            }
{ Marcel van Brakel. All Rights Reserved.                                      }
{ 								               }
{ Contributor(s): Sunish Issac  (sunish@nettaxi.com)                           }
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

unit JwaMsTask;

{$WEAKPACKAGEUNIT}

{$HPPEMIT ''}
{$HPPEMIT '#include "mstask.h"'}
{$HPPEMIT ''}

{$I WINDEFINES.INC}

interface

uses
  JwaWinBase, JwaWinType, CommCtrl {TODO};

const
  TASK_SUNDAY = ($1);
  {$EXTERNALSYM TASK_SUNDAY}
  TASK_MONDAY = ($2);
  {$EXTERNALSYM TASK_MONDAY}
  TASK_TUESDAY = ($4);
  {$EXTERNALSYM TASK_TUESDAY}
  TASK_WEDNESDAY = ($8);
  {$EXTERNALSYM TASK_WEDNESDAY}
  TASK_THURSDAY = ($10);
  {$EXTERNALSYM TASK_THURSDAY}
  TASK_FRIDAY = ($20);
  {$EXTERNALSYM TASK_FRIDAY}
  TASK_SATURDAY = ($40);
  {$EXTERNALSYM TASK_SATURDAY}
  TASK_FIRST_WEEK = (1);
  {$EXTERNALSYM TASK_FIRST_WEEK}
  TASK_SECOND_WEEK = (2);
  {$EXTERNALSYM TASK_SECOND_WEEK}
  TASK_THIRD_WEEK = (3);
  {$EXTERNALSYM TASK_THIRD_WEEK}
  TASK_FOURTH_WEEK = (4);
  {$EXTERNALSYM TASK_FOURTH_WEEK}
  TASK_LAST_WEEK = (5);
  {$EXTERNALSYM TASK_LAST_WEEK}
  TASK_JANUARY = ($1);
  {$EXTERNALSYM TASK_JANUARY}
  TASK_FEBRUARY = ($2);
  {$EXTERNALSYM TASK_FEBRUARY}
  TASK_MARCH = ($4);
  {$EXTERNALSYM TASK_MARCH}
  TASK_APRIL = ($8);
  {$EXTERNALSYM TASK_APRIL}
  TASK_MAY = ($10);
  {$EXTERNALSYM TASK_MAY}
  TASK_JUNE = ($20);
  {$EXTERNALSYM TASK_JUNE}
  TASK_JULY = ($40);
  {$EXTERNALSYM TASK_JULY}
  TASK_AUGUST = ($80);
  {$EXTERNALSYM TASK_AUGUST}
  TASK_SEPTEMBER = ($100);
  {$EXTERNALSYM TASK_SEPTEMBER}
  TASK_OCTOBER = ($200);
  {$EXTERNALSYM TASK_OCTOBER}
  TASK_NOVEMBER = ($400);
  {$EXTERNALSYM TASK_NOVEMBER}
  TASK_DECEMBER = ($800);
  {$EXTERNALSYM TASK_DECEMBER}

  TASK_FLAG_INTERACTIVE = ($1);
  {$EXTERNALSYM TASK_FLAG_INTERACTIVE}
  TASK_FLAG_DELETE_WHEN_DONE = ($2);
  {$EXTERNALSYM TASK_FLAG_DELETE_WHEN_DONE}
  TASK_FLAG_DISABLED = ($4);
  {$EXTERNALSYM TASK_FLAG_DISABLED}
  TASK_FLAG_START_ONLY_IF_IDLE = ($10);
  {$EXTERNALSYM TASK_FLAG_START_ONLY_IF_IDLE}
  TASK_FLAG_KILL_ON_IDLE_END = ($20);
  {$EXTERNALSYM TASK_FLAG_KILL_ON_IDLE_END}
  TASK_FLAG_DONT_START_IF_ON_BATTERIES = ($40);
  {$EXTERNALSYM TASK_FLAG_DONT_START_IF_ON_BATTERIES}
  TASK_FLAG_KILL_IF_GOING_ON_BATTERIES = ($80);
  {$EXTERNALSYM TASK_FLAG_KILL_IF_GOING_ON_BATTERIES}
  TASK_FLAG_RUN_ONLY_IF_DOCKED = ($100);
  {$EXTERNALSYM TASK_FLAG_RUN_ONLY_IF_DOCKED}
  TASK_FLAG_HIDDEN = ($200);
  {$EXTERNALSYM TASK_FLAG_HIDDEN}
  TASK_FLAG_RUN_IF_CONNECTED_TO_INTERNET = ($400);
  {$EXTERNALSYM TASK_FLAG_RUN_IF_CONNECTED_TO_INTERNET}
  TASK_FLAG_RESTART_ON_IDLE_RESUME = ($800);
  {$EXTERNALSYM TASK_FLAG_RESTART_ON_IDLE_RESUME}
  TASK_FLAG_SYSTEM_REQUIRED = ($1000);
  {$EXTERNALSYM TASK_FLAG_SYSTEM_REQUIRED}
  TASK_FLAG_RUN_ONLY_IF_LOGGED_ON = ($2000);
  {$EXTERNALSYM TASK_FLAG_RUN_ONLY_IF_LOGGED_ON}

  TASK_TRIGGER_FLAG_HAS_END_DATE = ($1);
  {$EXTERNALSYM TASK_TRIGGER_FLAG_HAS_END_DATE}
  TASK_TRIGGER_FLAG_KILL_AT_DURATION_END = ($2);
  {$EXTERNALSYM TASK_TRIGGER_FLAG_KILL_AT_DURATION_END}
  TASK_TRIGGER_FLAG_DISABLED = ($4);
  {$EXTERNALSYM TASK_TRIGGER_FLAG_DISABLED}

  TASK_MAX_RUN_TIMES = (1440);
  {$EXTERNALSYM TASK_MAX_RUN_TIMES}

type
  PTaskTriggerType = ^TTaskTriggerType;
  _TASK_TRIGGER_TYPE = (
    TASK_TIME_TRIGGER_ONCE,
    TASK_TIME_TRIGGER_DAILY,
    TASK_TIME_TRIGGER_WEEKLY,
    TASK_TIME_TRIGGER_MONTHLYDATE,
    TASK_TIME_TRIGGER_MONTHLYDOW,
    TASK_EVENT_TRIGGER_ON_IDLE,
    TASK_EVENT_TRIGGER_AT_SYSTEMSTART,
    TASK_EVENT_TRIGGER_AT_LOGON);
  TASK_TRIGGER_TYPE = _TASK_TRIGGER_TYPE;
  {$EXTERNALSYM TASK_TRIGGER_TYPE}
  {$EXTERNALSYM _TASK_TRIGGER_TYPE}
  PTASK_TRIGGER_TYPE = ^_TASK_TRIGGER_TYPE;
  {$EXTERNALSYM PTASK_TRIGGER_TYPE}
  TTaskTriggerType = _TASK_TRIGGER_TYPE;

  PDaily = ^TDaily;
  _DAILY = record
    DaysInterval: WORD;
  end;
  {$EXTERNALSYM _DAILY}
  TDaily = _DAILY;

  PWeekly = ^TWeekly;
  _WEEKLY = record
    WeeksInterval: WORD;
    rgfDaysOfTheWeek: WORD;
  end;
  {$EXTERNALSYM _WEEKLY}
  TWeekly = _WEEKLY;

  PMonthlyDate = ^TMonthlyDate;
  _MONTHLYDATE = record
    rgfDays: DWORD;
    rgfMonths: WORD;
  end;
  {$EXTERNALSYM _MONTHLYDATE}
  TMonthlyDate = _MONTHLYDATE;

  PMonthlyDow = ^TMonthlyDow;
  _MONTHLYDOW = record
    wWhichWeek: WORD;
    rgfDaysOfTheWeek: WORD;
    rgfMonths: WORD;
  end;
  {$EXTERNALSYM _MONTHLYDOW}
  TMonthlyDow = _MONTHLYDOW;

  PTriggerTypeUnion = ^TTriggerTypeUnion;
  _TRIGGER_TYPE_UNION = record
    case Integer of
      0: (Daily: TDaily);
      1: (Weekly: TWeekly);
      2: (MonthlyDate: TMonthlyDate);
      3: (MonthlyDOW: TMonthlyDow);
  end;
  {$EXTERNALSYM _TRIGGER_TYPE_UNION}
  TRIGGER_TYPE_UNION = _TRIGGER_TYPE_UNION;
  {$EXTERNALSYM TRIGGER_TYPE_UNION}
  TTriggerTypeUnion = _TRIGGER_TYPE_UNION;

  PTaskTrigger = ^TTaskTrigger;
  _TASK_TRIGGER = record
    cbTriggerSize: WORD;
    Reserved1: WORD;
    wBeginYear: WORD;
    wBeginMonth: WORD;
    wBeginDay: WORD;
    wEndYear: WORD;
    wEndMonth: WORD;
    wEndDay: WORD;
    wStartHour: WORD;
    wStartMinute: WORD;
    MinutesDuration: DWORD;
    MinutesInterval: DWORD;
    rgFlags: DWORD;
    TriggerType: TTaskTriggerType;
    Type_: TTriggerTypeUnion;
    Reserved2: WORD;
    wRandomMinutesInterval: WORD;
  end;
  {$EXTERNALSYM _TASK_TRIGGER}
  TASK_TRIGGER = _TASK_TRIGGER;
  {$EXTERNALSYM TASK_TRIGGER}
  PTASK_TRIGGER = ^TASK_TRIGGER;
  {$EXTERNALSYM PTASK_TRIGGER}
  TTaskTrigger = _TASK_TRIGGER;

const
  IID_ITaskTrigger: TGUID = '{148BD52B-A2AB-11CE-B11F-00AA00530503}';
  {$EXTERNALSYM IID_ITaskTrigger}

// interface ITaskTrigger

type
  ITaskTrigger = interface (IUnknown)
    ['{148BD52B-A2AB-11CE-B11F-00AA00530503}']
    function SetTrigger(const pTrigger: PTaskTrigger): HRESULT; stdcall;
    function GetTrigger(pTrigger: PTaskTrigger): HRESULT; stdcall;
    function GetTriggerString(var ppwszTrigger: LPWSTR): HRESULT; stdcall;
  end;
  {$EXTERNALSYM ITaskTrigger}

const
  IID_IScheduledWorkItem: TGUID = '{A6B952F0-A4B1-11D0-997D-00AA006887EC}';
  {$EXTERNALSYM IID_IScheduledWorkItem}

// interface IScheduledWorkItem

type
  IScheduledWorkItem = interface (IUnknown)
    ['{A6B952F0-A4B1-11D0-997D-00AA006887EC}']
    function CreateTrigger(out piNewTrigger: Word; out ppTrigger: ITaskTrigger): HRESULT; stdcall;
    function DeleteTrigger(iTrigger: Word): HRESULT; stdcall;
    function GetTriggerCount(out pwCount: Word): HRESULT; stdcall;
    function GetTrigger(iTrigger: Word; var ppTrigger: ITaskTrigger): HRESULT; stdcall;
    function GetTriggerString(iTrigger: Word; out ppwszTrigger: PWideChar): HRESULT; stdcall;
    function GetRunTimes(const pstBegin: LPSYSTEMTIME; const pstEnd: LPSYSTEMTIME;
      var pCount: Word; out rgstTaskTimes: LPSYSTEMTIME): HRESULT; stdcall;
    function GetNextRunTime(var pstNextRun: SYSTEMTIME): HRESULT; stdcall;
    function SetIdleWait(wIdleMinutes: Word; wDeadlineMinutes: Word): HRESULT; stdcall;
    function GetIdleWait(out pwIdleMinutes: Word; out pwDeadlineMinutes: Word): HRESULT; stdcall;
    function Run: HRESULT; stdcall;
    function Terminate: HRESULT; stdcall;
    function EditWorkItem(hParent: HWND; dwReserved: DWORD): HRESULT; stdcall;
    function GetMostRecentRunTime(out pstLastRun: TSystemTime): HRESULT; stdcall;
    function GetStatus(out phrStatus: HRESULT): HRESULT stdcall;
    function GetExitCode(out pdwExitCode: DWORD): HRESULT stdcall;
    function SetComment(pwszComment: LPCWSTR): HRESULT stdcall;
    function GetComment(out ppwszComment: LPWSTR): HRESULT stdcall;
    function SetCreator(pwszCreator: LPCWSTR): HRESULT; stdcall;
    function GetCreator(out ppwszCreator: LPWSTR): HRESULT; stdcall;
    function SetWorkItemData(cbData: Word; var rgbData: Byte): HRESULT; stdcall;
    function GetWorkItemData(out pcbData: Word; out prgbData: Byte): HRESULT; stdcall;
    function SetErrorRetryCount(wRetryCount: Word): HRESULT; stdcall;
    function GetErrorRetryCount(out pwRetryCount: Word): HRESULT; stdcall;
    function SetErrorRetryInterval(wRetryInterval: Word): HRESULT; stdcall;
    function GetErrorRetryInterval(out pwRetryInterval: Word): HRESULT; stdcall;
    function SetFlags(dwFlags: DWORD): HRESULT; stdcall;
    function GetFlags(out pdwFlags: DWORD): HRESULT; stdcall;
    function SetAccountInformation(pwszAccountName: LPCWSTR; pwszPassword: LPCWSTR): HRESULT; stdcall;
    function GetAccountInformation(out ppwszAccountName: LPWSTR): HRESULT; stdcall;
  end;
  {$EXTERNALSYM IScheduledWorkItem}

const
  IID_ITask: TGUID = '{148BD524-A2AB-11CE-B11F-00AA00530503}';
  {$EXTERNALSYM IID_ITask}

// interface ITask

type
  ITask = interface (IScheduledWorkItem)
    ['{148BD524-A2AB-11CE-B11F-00AA00530503}']
    function SetApplicationName(pwszApplicationName: LPCWSTR): HRESULT; stdcall;
    function GetApplicationName(out ppwszApplicationName: LPWSTR): HRESULT; stdcall;
    function SetParameters(pwszParameters: LPCWSTR): HRESULT; stdcall;
    function GetParameters(out ppwszParameters: LPWSTR): HRESULT; stdcall;
    function SetWorkingDirectory(pwszWorkingDirectory: LPCWSTR): HRESULT; stdcall;
    function GetWorkingDirectory(out ppwszWorkingDirectory: LPWSTR): HRESULT; stdcall;
    function SetPriority(dwPriority: DWORD): HRESULT; stdcall;
    function GetPriority(out pdwPriority: DWORD): HRESULT; stdcall;
    function SetTaskFlags(dwFlags: DWORD): HRESULT; stdcall;
    function GetTaskFlags(out pdwFlags: DWORD): HRESULT; stdcall;
    function SetMaxRunTime(dwMaxRunTimeMS: DWORD): HRESULT; stdcall;
    function GetMaxRunTime(out pdwMaxRunTimeMS: DWORD): HRESULT; stdcall;
  end;
  {$EXTERNALSYM ITask}

const
  IID_IEnumWorkItems: TGUID = '{148BD528-A2AB-11CE-B11F-00AA00530503}';
  {$EXTERNALSYM IID_IEnumWorkItems}

// interface IEnumWorkItems

type
  IEnumWorkItems = interface (IUnknown)
    ['{148BD528-A2AB-11CE-B11F-00AA00530503}']
    function Next(celt: ULONG; out rgpwszNames: LPLPWSTR; out pceltFetched: ULONG): HRESULT; stdcall;
    function Skip(celt: ULONG): HRESULT; stdcall;
    function Reset: HRESULT; stdcall;
    function Clone(out ppEnumWorkItems: IEnumWorkItems): HRESULT; stdcall;
  end;
  {$EXTERNALSYM IEnumWorkItems}

const
  IID_ITaskScheduler: TGUID = '{148BD527-A2AB-11CE-B11F-00AA00530503}';
  {$EXTERNALSYM IID_ITaskScheduler}

// interface ITaskScheduler

type
  ITaskScheduler = interface (IUnknown)
    ['{148BD527-A2AB-11CE-B11F-00AA00530503}']
    function SetTargetComputer(pwszComputer: LPCWSTR): HRESULT; stdcall;
    function GetTargetComputer(out ppwszComputer: LPWSTR): HRESULT; stdcall;
    function Enum(out ppEnumWorkItems: IEnumWorkItems): HRESULT; stdcall;
    function Activate(pwszName: PWideChar; var riid: TGUID; out ppUnk: IUnknown): HRESULT; stdcall;
    function Delete(pwszName: LPCWSTR): HRESULT; stdcall;
    function NewWorkItem(pwszTaskName: PWideChar; var rclsid: TGUID; var riid: TGUID; out ppUnk: IUnknown): HRESULT; stdcall;
    function AddWorkItem(pwszTaskName: LPCWSTR; var pWorkItem: IScheduledWorkItem): HRESULT; stdcall;
    function IsOfType(pwszName: LPCWSTR; var riid: TGUID): HRESULT; stdcall;
  end;
  {$EXTERNALSYM ITaskScheduler}

const
  CLSID_CTask: TGuid = '{148BD520-A2AB-11CE-B11F-00AA00530503}';
  {$EXTERNALSYM CLSID_CTask}

  CLSID_CTaskScheduler: TGuid = '{148BD52A-A2AB-11CE-B11F-00AA00530503}';
  {$EXTERNALSYM CLSID_CTaskScheduler}

type
  PTaskPage = ^TTaskPage;
  _TASKPAGE = (
    TASKPAGE_TASK,
    TASKPAGE_SCHEDULE,
    TASKPAGE_SETTINGS);
  {$EXTERNALSYM _TASKPAGE}
  TASKPAGE = _TASKPAGE;
  {$EXTERNALSYM TASKPAGE}
  TTaskPage = _TASKPAGE;

const
  IID_IProvideTaskPage: TGuid = '{4086658a-cbbb-11cf-b604-00c04fd8d565}';
  {$EXTERNALSYM IID_IProvideTaskPage}

// interface IProvideTaskPage

type
  IProvideTaskPage = interface (IUnknown)
    ['{4086658A-CBBB-11CF-B604-00C04FD8D565}']
    function GetPage(tpType: TTaskPage; fPersistChanges: BOOL; var phPage: HPropSheetPage): HRESULT; stdcall;
  end;
  {$EXTERNALSYM IProvideTaskPage}

const
  ISchedulingAgent = ITaskScheduler;
  {$EXTERNALSYM ISchedulingAgent}
  IEnumTasks = IEnumWorkItems;
  {$EXTERNALSYM IEnumTasks}
  //IID_ISchedulingAgent   = IID_ITaskScheduler;
  IID_ISchedulingAgent: TGUID = '{148BD527-A2AB-11CE-B11F-00AA00530503}';
  {$EXTERNALSYM IID_ISchedulingAgent}
  //CLSID_CSchedulingAgent = CLSID_CTaskScheduler;
  CLSID_CSchedulingAgent: TGuid = '{148BD52A-A2AB-11CE-B11F-00AA00530503}';
  {$EXTERNALSYM CLSID_CSchedulingAgent}


//added to use save option without ole2 - not there in original source of mstask.h

  {$EXTERNALSYM IID_IPersistFile}
  IID_IPersistFile: TGUID = (
    D1: $0000010B; D2: $0000; D3: $0000; D4: ($C0, $00, $00, $00, $00, $00, $00, $46));

implementation

end.

