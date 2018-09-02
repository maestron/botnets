{******************************************************************************}
{                                                       	               }
{ Background Intelligent Transfer Service API interface Unit for Object Pascal }
{                                                       	               }
{ Portions created by Microsoft are Copyright (C) 1995-2001 Microsoft          }
{ Corporation. All Rights Reserved.                                            }
{ 								               }
{ The original file is: bits.h, released August 2001. The original Pascal      }
{ code is: Bits.pas, released October 2001. The initial developer of the       }
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

unit JwaBits;

{$WEAKPACKAGEUNIT}

{$HPPEMIT ''}
{$HPPEMIT '#include "bits.h"'}
{$HPPEMIT ''}

{$I WINDEFINES.INC}

interface

uses
  JwaWinBase, JwaWinType, JwaBitsMsg;

const
  BG_SIZE_UNKNOWN = Int64(-1);
  {$EXTERNALSYM BG_SIZE_UNKNOWN}

//
// =============================
// Marshalled interfaces
// =============================

type
  _BG_FILE_PROGRESS = record
    BytesTotal: UINT64;
    BytesTransferred: UINT64;
    Completed: BOOL;
  end;
  {$EXTERNALSYM _BG_FILE_PROGRESS}
  BG_FILE_PROGRESS = _BG_FILE_PROGRESS;
  {$EXTERNALSYM BG_FILE_PROGRESS}
  TBgFileProgress = BG_FILE_PROGRESS;
  PBgFileProgress = ^BG_FILE_PROGRESS;

const
  IID_IBackgroundCopyFile: TGUID = '{01B7BD23-FB88-4A77-8490-5891D3E4653A}';
  {$EXTERNALSYM IID_IBackgroundCopyFile}

type
  IBackgroundCopyFile = interface (IUnknown)
  ['{01b7bd23-fb88-4a77-8490-5891d3e4653a}']
    function GetRemoteName(out pVal: LPWSTR): HRESULT; stdcall;
    function GetLocalName(out pVal: LPWSTR): HRESULT; stdcall;
    function GetProgress(out pVal: BG_FILE_PROGRESS): HRESULT; stdcall;
  end;
  {$EXTERNALSYM IBackgroundCopyFile}

//--------------------------------------------------------------------
//

const
  IID_IEnumBackgroundCopyFiles: TGUID = '{CA51E165-C365-424C-8D41-24AAA4FF3C40}';
  {$EXTERNALSYM IID_IEnumBackgroundCopyFiles}

type
  IEnumBackgroundCopyFiles = interface (IUnknown)
  ['{ca51e165-c365-424c-8d41-24aaa4ff3c40}']
    function Next(celt: ULONG; out rgelt: IBackgroundCopyFile;  pceltFetched: PULONG): HRESULT; stdcall;
    function Skip(celt: ULONG): HRESULT; stdcall;
    function Reset: HRESULT; stdcall;
    function Clone(out ppenum: IEnumBackgroundCopyFiles): HRESULT; stdcall;
    function GetCount(out puCount: ULONG): HRESULT; stdcall;
  end;
  {$EXTERNALSYM IEnumBackgroundCopyFiles}

//--------------------------------------------------------------------
//

type
  BG_ERROR_CONTEXT = (
    BG_ERROR_CONTEXT_NONE,
    BG_ERROR_CONTEXT_UNKNOWN,
    BG_ERROR_CONTEXT_GENERAL_QUEUE_MANAGER,
    BG_ERROR_CONTEXT_QUEUE_MANAGER_NOTIFICATION,
    BG_ERROR_CONTEXT_LOCAL_FILE,
    BG_ERROR_CONTEXT_REMOTE_FILE,
    BG_ERROR_CONTEXT_GENERAL_TRANSPORT,
    BG_ERROR_CONTEXT_REMOTE_APPLICATION);
  {$EXTERNALSYM BG_ERROR_CONTEXT}
  TBgErrorContext = BG_ERROR_CONTEXT;

const
  IID_IBackgroundCopyError: TGUID = '{19C613A0-FCB8-4F28-81AE-897C3D078F81}';
  {$EXTERNALSYM IID_IBackgroundCopyError}

type
  IBackgroundCopyError = interface (IUnknown)
  ['{19c613a0-fcb8-4f28-81ae-897c3d078f81}']
    function GetError(out pContext: BG_ERROR_CONTEXT; out pCode: HRESULT): HRESULT; stdcall;
    // Returns BG_E_FILE_NOT_AVAILABLE if no file is available
    function GetFile(out ppVal: IBackgroundCopyFile): HRESULT; stdcall;
    // Return a human readable description of the error.
    // Use CoTaskMemFree to free the description.
    function GetErrorDescription(LanguageId: DWORD; out pErrorDescription: LPWSTR): HRESULT; stdcall;
    // Return a human readable description of the error context.
    // Use CoTaskMemFree to free the description.
    function GetErrorContextDescription(LanguageId: DWORD; out pContextDescription: LPWSTR): HRESULT; stdcall;
    // Returns BG_E_PROTOCOL_NOT_AVAILABLE if no protocol is available
    function GetProtocol(out pProtocol: LPWSTR): HRESULT; stdcall;
  end;
  {$EXTERNALSYM IBackgroundCopyError}

// ==============================================
// Job Interface

type
  _BG_FILE_INFO = record
    RemoteName: LPWSTR;
    LocalName: LPWSTR;
  end;
  {$EXTERNALSYM _BG_FILE_INFO}
  BG_FILE_INFO = _BG_FILE_INFO;
  {$EXTERNALSYM BG_FILE_INFO}
  TBgFileInfo = BG_FILE_INFO;
  PBgFileInfo = ^BG_FILE_INFO;

  _BG_JOB_PROGRESS = record
    BytesTotal: UINT64;
    BytesTransferred: UINT64;
    FilesTotal: ULONG;
    FilesTransferred: ULONG;
  end;
  {$EXTERNALSYM _BG_JOB_PROGRESS}
  BG_JOB_PROGRESS = _BG_JOB_PROGRESS;
  {$EXTERNALSYM BG_JOB_PROGRESS}
  TBgJobProgress = BG_JOB_PROGRESS;
  PBgJobProgress = ^BG_JOB_PROGRESS;

  _BG_JOB_TIMES = record
    CreationTime: FILETIME;
    ModificationTime: FILETIME;
    TransferCompletionTime: FILETIME;
  end;
  {$EXTERNALSYM _BG_JOB_TIMES}
  BG_JOB_TIMES = _BG_JOB_TIMES;
  {$EXTERNALSYM BG_JOB_TIMES}
  TBgJobTimes = BG_JOB_TIMES;
  PBgJobTimes = ^BG_JOB_TIMES;

  BG_JOB_PRIORITY = (
    BG_JOB_PRIORITY_FOREGROUND,
    BG_JOB_PRIORITY_HIGH,
    BG_JOB_PRIORITY_NORMAL,
    BG_JOB_PRIORITY_LOW);
  {$EXTERNALSYM BG_JOB_PRIORITY}
  TBgJobPriority = BG_JOB_PRIORITY;
  PBgJobPriority = ^BG_JOB_PRIORITY;

  BG_JOB_STATE = (
    BG_JOB_STATE_QUEUED,
    BG_JOB_STATE_CONNECTING,
    BG_JOB_STATE_TRANSFERRING,
    BG_JOB_STATE_SUSPENDED,
    BG_JOB_STATE_ERROR,
    BG_JOB_STATE_TRANSIENT_ERROR,
    BG_JOB_STATE_TRANSFERRED,
    BG_JOB_STATE_ACKNOWLEDGED,
    BG_JOB_STATE_CANCELLED);
  {$EXTERNALSYM BG_JOB_STATE}
  TBgJobState = BG_JOB_STATE;
  PBgJobState = ^BG_JOB_STATE;  

  BG_JOB_TYPE = (
    BG_JOB_TYPE_DOWNLOAD,
    BG_JOB_TYPE_UPLOAD,
    BG_JOB_TYPE_UPLOAD_REPLY);
  {$EXTERNALSYM BG_JOB_TYPE}
  TBgJobType = BG_JOB_TYPE;

  BG_JOB_PROXY_USAGE = (
    BG_JOB_PROXY_USAGE_PRECONFIG,
    BG_JOB_PROXY_USAGE_NO_PROXY,
    BG_JOB_PROXY_USAGE_OVERRIDE);
  {$EXTERNALSYM BG_JOB_PROXY_USAGE}
  TBgJobProxyUsage = BG_JOB_PROXY_USAGE;
  PBgJobProxyUsage = ^BG_JOB_PROXY_USAGE;

const
  IID_IBackgroundCopyJob: TGUID = '{37668D37-507E-4160-9316-26306D150B12}';
  {$EXTERNALSYM IID_IBackgroundCopyJob}

type
  IBackgroundCopyJob = interface (IUnknown)
  ['{37668d37-507e-4160-9316-26306d150b12}']

    //--------------------------------------------------------------------

    //
    // Returns E_INVALIDARG if one of the filesets has
    //      - local name is blank
    //      - local name contains invalid characters
    //      - remote name is blank
    //      - remote name has invalid format
    //
    // Returns CO_E_NOT_SUPPORTED if
    //      - remote URL contains unsupported protocol
    //
    function AddFileSet(cFileCount: ULONG; pFileSet: PBgFileInfo): HRESULT; stdcall;

    function AddFile(RemoteUrl, LocalName: LPCWSTR): HRESULT; stdcall;

    //
    // Gets an enumerator object for all files in the job.
    //
    function EnumFiles(out pEnum: IEnumBackgroundCopyFiles): HRESULT; stdcall;

    //
    // Pause all activity on the job.  The service will take no action until one of
    // Resume(), Cancel(), Complete() is called.
    //
    // if already suspended, just returns S_OK.
    //
    function Suspend: HRESULT; stdcall;

    //
    // Enable downloading for this job.  Job properties cannot be modified
    // after Resume() until the app calls Suspend().
    //
    // if already running, just returns S_OK.
    //
    function Resume: HRESULT; stdcall;

    //
    // Permanently stop the job.  The service will delete the job metadata and downloaded files.
    //
    // If already cancelled or resumed, returns ???
    //
    function Cancel: HRESULT; stdcall;

    //
    // Acknowledges receipt of the job-complete notification.  The service will delete
    // the job metadata and leave the downloaded files.
    //
    function Complete: HRESULT; stdcall;

    //--------------------------------------------------------------------

    function GetId(out pVal: GUID): HRESULT; stdcall;

    function GetType(out pVal: BG_JOB_TYPE): HRESULT; stdcall;

    function GetProgress(out pVal: BG_JOB_PROGRESS): HRESULT; stdcall;

    function GetTimes(out pVal: BG_JOB_TIMES): HRESULT; stdcall;

    function GetState(out pVal: BG_JOB_STATE): HRESULT; stdcall;

    function GetError(out ppError: IBackgroundCopyError): HRESULT; stdcall;

    //
    // The owner of the job, represented as a string.
    // Only the owner and admins are allowed to see or change the job.
    //
    function GetOwner(out pVal: LPWSTR): HRESULT; stdcall;

    //
    // name of the job, suitable for display in UI
    //
    function SetDisplayName(Val: LPCWSTR): HRESULT; stdcall;
    function GetDisplayName(out pVal: LPWSTR): HRESULT; stdcall;

    //
    // a field for use by the app
    //
    function SetDescription(Val: LPCWSTR): HRESULT; stdcall;
    function GetDescription(out pVal: LPWSTR): HRESULT; stdcall;

    //
    // the priority of the job in the queue.
    // default = PRIORITY_NORMAL
    // values not in BG_JOB_PRIORITY return E_NOTIMPL.
    //
    function SetPriority(Val: BG_JOB_PRIORITY): HRESULT; stdcall;
    function GetPriority(out pVal: BG_JOB_PRIORITY): HRESULT; stdcall;

    //
    // ignores extra flags?
    //
    function SetNotifyFlags(Val: ULONG): HRESULT; stdcall;
    function GetNotifyFlags(out pVal: ULONG): HRESULT; stdcall;

    // interface pointer that implements the IBackgroundCallback interface for notifications.
    // If the pointer becomes invalid, the service will try to create a new notification object
    // with the notify CLSID.
    function SetNotifyInterface(Val: IUnknown): HRESULT; stdcall;
    function GetNotifyInterface(out pVal: IUnknown): HRESULT; stdcall;

    function SetMinimumRetryDelay(Seconds: ULONG): HRESULT; stdcall;
    function GetMinimumRetryDelay(out Seconds: ULONG): HRESULT; stdcall;

    function SetNoProgressTimeout(Seconds: ULONG): HRESULT; stdcall;
    function GetNoProgressTimeout(out Seconds: ULONG): HRESULT; stdcall;

    function GetErrorCount(out Errors: ULONG): HRESULT; stdcall;

    function SetProxySettings(ProxyUsage: BG_JOB_PROXY_USAGE; ProxyList, ProxyBypassList: PWCHAR): HRESULT; stdcall;

    function GetProxySettings(pProxyUsage: BG_JOB_PROXY_USAGE; pProxyList, pProxyBypassList: LPWSTR): HRESULT; stdcall;

    function TakeOwnership(): HRESULT; stdcall;
  end;
  {$EXTERNALSYM IBackgroundCopyJob}

// ==============================================
// IEnumJobs Interface
//     This interface allows enumerating the jobs under a Job

const
  IID_IEnumBackgroundCopyJobs: TGUID = '{1AF4F612-3B71-466F-8F58-7B6F73AC57AD}';
  {$EXTERNALSYM IID_IEnumBackgroundCopyJobs}

type
  IEnumBackgroundCopyJobs = interface (IUnknown)
  ['{1af4f612-3b71-466f-8f58-7b6f73ac57ad}']
    function Next(celt: ULONG; out rgelt: IBackgroundCopyJob; pceltFetched: PULONG): HRESULT; stdcall;
    function Skip(celt: ULONG): HRESULT; stdcall;
    function Reset: HRESULT; stdcall;
    function Clone(out ppenum: IEnumBackgroundCopyJobs): HRESULT; stdcall;
    function GetCount(out puCount: ULONG): HRESULT; stdcall;
  end;
  {$EXTERNALSYM IEnumBackgroundCopyJobs}

const
  BG_NOTIFY_JOB_TRANSFERRED   = $0001;
  {$EXTERNALSYM BG_NOTIFY_JOB_TRANSFERRED}
  BG_NOTIFY_JOB_ERROR         = $0002;
  {$EXTERNALSYM BG_NOTIFY_JOB_ERROR}
  BG_NOTIFY_DISABLE           = $0004;
  {$EXTERNALSYM BG_NOTIFY_DISABLE}
  BG_NOTIFY_JOB_MODIFICATION  = $0008;
  {$EXTERNALSYM BG_NOTIFY_JOB_MODIFICATION}

// ==============================================
// IBackgroundCallback Interface
//     This interface is implemented by the client and is used by the queue manager
//     to supply progress information to the client.

const
  IID_IBackgroundCopyCallback: TGUID = '{97EA99C7-0186-4AD4-8DF9-C5B4E0ED6B22}';
  {$EXTERNALSYM IID_IBackgroundCopyCallback}

type
  IBackgroundCopyCallback = interface (IUnknown)
  ['{97ea99c7-0186-4ad4-8df9-c5b4e0ed6b22}']
    //
    // A job has transferred successfully.
    //
    function JobTransferred(pJob: IBackgroundCopyJob): HRESULT; stdcall;

    //
    // An error occurred, and the service has suspended the job.
    // Fix the error and resume the job.
    // Get error details by calling (*pFailingJob)->GetStatus().
    //
    function JobError(pJob: IBackgroundCopyJob; pError: IBackgroundCopyError): HRESULT; stdcall;

    //
    // The job has been modified.   Intendended for user interfaces.
    //
    function JobModification(pJob: IBackgroundCopyJob; dwReserved: DWORD): HRESULT; stdcall;

  end;
  {$EXTERNALSYM IBackgroundCopyCallback}

//
// IBackgroundCopyManager is the "root" interface to the background file copy component.
//

const
  BG_JOB_ENUM_ALL_USERS = $0001;
  {$EXTERNALSYM BG_JOB_ENUM_ALL_USERS}

  IID_IBackgroundCopyManager: TGUID = '{5CE34C0D-0DC9-4C1F-897C-DAA1B78CEE7C}';
  {$EXTERNALSYM IID_IBackgroundCopyManager}

type
  IBackgroundCopyManager = interface (IUnknown)
  ['{5ce34c0d-0dc9-4c1f-897c-daa1b78cee7c}']
    function CreateJob(DisplayName: LPCWSTR; Type_: BG_JOB_TYPE; out pJobId: GUID; out ppJob: IBackgroundCopyJob): HRESULT; stdcall;
    function GetJob(const jobID: GUID; out ppJob: IBackgroundCopyJob): HRESULT; stdcall;

    //
    // Without this flag, jobs not owned by the caller are excluded from the enumeration.
    // With this flag, those jobs are included.  Only works if the caller is an administrator.
    //
    function EnumJobs(dwFlags: DWORD; out ppEnum: IEnumBackgroundCopyJobs): HRESULT; stdcall;
    function GetErrorDescription(hResult: HRESULT; LanguageId: DWORD; out pErrorDescription: LPWSTR): HRESULT; stdcall;
 end;
 {$EXTERNALSYM IBackgroundCopyManager}

//---------------------------------------------------------------------------

const
  LIBID_BackgroundCopyManager: GUID = '{4991d34b-80a1-4291-83b6-3328366b9097}';
  {$EXTERNALSYM LIBID_BackgroundCopyManager}
  CLSID_BackgroundCopyManager: GUID = '{4991d34b-80a1-4291-83b6-3328366b9097}';
  {$EXTERNALSYM CLSID_BackgroundCopyManager}

implementation

end.
