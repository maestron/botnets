{******************************************************************************}
{                                                       	               }
{ Windows Installer API interface Unit for Object Pascal                       }
{                                                       	               }
{ Portions created by Microsoft are Copyright (C) 1995-2001 Microsoft          }
{ Corporation. All Rights Reserved.                                            }
{ 								               }
{ The original file is: msiquery.h, released June 2000. The original Pascal    }
{ code is: MsiQuery.pas, released June 2001. The initial developer of the      }
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

unit JwaMsiQuery;

{$WEAKPACKAGEUNIT}

{$HPPEMIT ''}
{$HPPEMIT '#include "msiquery.h"'}
{$HPPEMIT ''}

{$I WINDEFINES.INC}

interface

uses
  JwaMsi, JwaWinBase, JwaWinType;

(*****************************************************************************\
*                                                                             *
* MsiQuery.h - Interface to running installer for custom actions and tools    *
*                                                                             *
* Version 1.0 - 1.2                                                           *
*                                                                             *
* NOTES:  All buffers sizes are TCHAR count, null included only on input      *
*         Return argument pointers may be null if not interested in value     *
*         Returned handles of all types must be closed: MsiCloseHandle(h)     *
*         Functions with UINT return type return a system error code          *
*         Designated functions will set or clear the last error record,       *
*         which is then accessible with MsiGetLastErrorRecord. However,       *
*         the following argument errors do not register an error record:      *
*         ERROR_INVALID_HANDLE, ERROR_INVALID_PARAMETER, ERROR_MORE_DATA.     *
*                                                                             *
* Copyright (c) 1999-2000, Microsoft Corp.      All rights reserved.          *
*                                                                             *
\*****************************************************************************)

const
  MSI_NULL_INTEGER = DWORD($80000000);  // integer value reserved for null
  {$EXTERNALSYM MSI_NULL_INTEGER}

// MsiOpenDatabase persist predefine values, otherwise output database path is used

  MSIDBOPEN_READONLY     = LPCTSTR(0);  // database open read-only, no persistent changes
  {$EXTERNALSYM MSIDBOPEN_READONLY}
  MSIDBOPEN_TRANSACT     = LPCTSTR(1);  // database read/write in transaction mode
  {$EXTERNALSYM MSIDBOPEN_TRANSACT}
  MSIDBOPEN_DIRECT       = LPCTSTR(2);  // database direct read/write without transaction
  {$EXTERNALSYM MSIDBOPEN_DIRECT}
  MSIDBOPEN_CREATE       = LPCTSTR(3);  // create new database, transact mode read/write
  {$EXTERNALSYM MSIDBOPEN_CREATE}
  MSIDBOPEN_CREATEDIRECT = LPCTSTR(4);  // create new database, direct mode read/write
  {$EXTERNALSYM MSIDBOPEN_CREATEDIRECT}

  {$IFDEF UNICODE}
  MSIDBOPEN_PATCHFILE    = 32 div SizeOf(WideChar); // add flag to indicate patch file
  {$ELSE}
  MSIDBOPEN_PATCHFILE    = 32 div SizeOf(AnsiChar); // add flag to indicate patch file  
  {$ENDIF}

  MSIDBSTATE_ERROR    = DWORD(-1);  // invalid database handle
  {$EXTERNALSYM MSIDBSTATE_ERROR}
  MSIDBSTATE_READ     =  0;  // database open read-only, no persistent changes
  {$EXTERNALSYM MSIDBSTATE_READ}
  MSIDBSTATE_WRITE    =  1;  // database readable and updatable
  {$EXTERNALSYM MSIDBSTATE_WRITE}

type
  MSIDBSTATE = DWORD;
  {$EXTERNALSYM MSIDBSTATE}
  TMsiDbState = MSIDBSTATE;

const
  MSIMODIFY_SEEK             = DWORD(-1);  // reposition to current record primary key
  {$EXTERNALSYM MSIMODIFY_SEEK}
  MSIMODIFY_REFRESH          = 0;  // refetch current record data
  {$EXTERNALSYM MSIMODIFY_REFRESH}
  MSIMODIFY_INSERT           = 1;  // insert new record, fails if matching key exists
  {$EXTERNALSYM MSIMODIFY_INSERT}
  MSIMODIFY_UPDATE           = 2;  // update existing non-key data of fetched record
  {$EXTERNALSYM MSIMODIFY_UPDATE}
  MSIMODIFY_ASSIGN           = 3;  // insert record, replacing any existing record
  {$EXTERNALSYM MSIMODIFY_ASSIGN}
  MSIMODIFY_REPLACE          = 4;  // update record, delete old if primary key edit
  {$EXTERNALSYM MSIMODIFY_REPLACE}
  MSIMODIFY_MERGE            = 5;  // fails if record with duplicate key not identical
  {$EXTERNALSYM MSIMODIFY_MERGE}
  MSIMODIFY_DELETE           = 6;  // remove row referenced by this record from table
  {$EXTERNALSYM MSIMODIFY_DELETE}
  MSIMODIFY_INSERT_TEMPORARY = 7;  // insert a temporary record
  {$EXTERNALSYM MSIMODIFY_INSERT_TEMPORARY}
  MSIMODIFY_VALIDATE         = 8;  // validate a fetched record
  {$EXTERNALSYM MSIMODIFY_VALIDATE}
  MSIMODIFY_VALIDATE_NEW     = 9;  // validate a new record
  {$EXTERNALSYM MSIMODIFY_VALIDATE_NEW}
  MSIMODIFY_VALIDATE_FIELD   = 10; // validate field(s) of an incomplete record
  {$EXTERNALSYM MSIMODIFY_VALIDATE_FIELD}
  MSIMODIFY_VALIDATE_DELETE  = 11; // validate before deleting record
  {$EXTERNALSYM MSIMODIFY_VALIDATE_DELETE}

type
  MSIMODIFY = DWORD;
  {$EXTERNALSYM MSIMODIFY}
  TMsiModify = MSIMODIFY;

const
  MSICOLINFO_NAMES = 0;  // return column names
  {$EXTERNALSYM MSICOLINFO_NAMES}
  MSICOLINFO_TYPES = 1;  // return column definitions, datatype code followed by width
  {$EXTERNALSYM MSICOLINFO_TYPES}

type
  MSICOLINFO = DWORD;
  {$EXTERNALSYM MSICOLINFO}
  TMsiColInfo = MSICOLINFO;

const
  MSICONDITION_FALSE = 0;  // expression evaluates to False
  {$EXTERNALSYM MSICONDITION_FALSE}
  MSICONDITION_TRUE  = 1;  // expression evaluates to True
  {$EXTERNALSYM MSICONDITION_TRUE}
  MSICONDITION_NONE  = 2;  // no expression present
  {$EXTERNALSYM MSICONDITION_NONE}
  MSICONDITION_ERROR = 3;  // syntax error in expression
  {$EXTERNALSYM MSICONDITION_ERROR}

type
  MSICONDITION = DWORD;
  {$EXTERNALSYM MSICONDITION}
  TMsiCondition = MSICONDITION;

const
  MSICOSTTREE_SELFONLY = 0;
  {$EXTERNALSYM MSICOSTTREE_SELFONLY}
  MSICOSTTREE_CHILDREN = 1;
  {$EXTERNALSYM MSICOSTTREE_CHILDREN}
  MSICOSTTREE_PARENTS  = 2;
  {$EXTERNALSYM MSICOSTTREE_PARENTS}
  MSICOSTTREE_RESERVED = 3;	// Reserved for future use
  {$EXTERNALSYM MSICOSTTREE_RESERVED}

type
  MSICOSTTREE = DWORD;
  {$EXTERNALSYM MSICOSTTREE}
  TMsiCostTree = MSICOSTTREE;

const
  MSIDBERROR_INVALIDARG        = DWORD(-3); //  invalid argument
  {$EXTERNALSYM MSIDBERROR_INVALIDARG}
  MSIDBERROR_MOREDATA          = DWORD(-2); //  buffer too small
  {$EXTERNALSYM MSIDBERROR_MOREDATA}
  MSIDBERROR_FUNCTIONERROR     = DWORD(-1); //  function error
  {$EXTERNALSYM MSIDBERROR_FUNCTIONERROR}
  MSIDBERROR_NOERROR           = 0;  //  no error
  {$EXTERNALSYM MSIDBERROR_NOERROR}
  MSIDBERROR_DUPLICATEKEY      = 1;  //  new record duplicates primary keys of existing record in table
  {$EXTERNALSYM MSIDBERROR_DUPLICATEKEY}
  MSIDBERROR_REQUIRED          = 2;  //  non-nullable column, no null values allowed
  {$EXTERNALSYM MSIDBERROR_REQUIRED}
  MSIDBERROR_BADLINK           = 3;  //  corresponding record in foreign table not found
  {$EXTERNALSYM MSIDBERROR_BADLINK}
  MSIDBERROR_OVERFLOW          = 4;  //  data greater than maximum value allowed
  {$EXTERNALSYM MSIDBERROR_OVERFLOW}
  MSIDBERROR_UNDERFLOW         = 5;  //  data less than minimum value allowed
  {$EXTERNALSYM MSIDBERROR_UNDERFLOW}
  MSIDBERROR_NOTINSET          = 6;  //  data not a member of the values permitted in the set
  {$EXTERNALSYM MSIDBERROR_NOTINSET}
  MSIDBERROR_BADVERSION        = 7;  //  invalid version string
  {$EXTERNALSYM MSIDBERROR_BADVERSION}
  MSIDBERROR_BADCASE           = 8;  //  invalid case, must be all upper-case or all lower-case
  {$EXTERNALSYM MSIDBERROR_BADCASE}
  MSIDBERROR_BADGUID           = 9;  //  invalid GUID
  {$EXTERNALSYM MSIDBERROR_BADGUID}
  MSIDBERROR_BADWILDCARD       = 10; //  invalid wildcardfilename or use of wildcards
  {$EXTERNALSYM MSIDBERROR_BADWILDCARD}
  MSIDBERROR_BADIDENTIFIER     = 11; //  bad identifier
  {$EXTERNALSYM MSIDBERROR_BADIDENTIFIER}
  MSIDBERROR_BADLANGUAGE       = 12; //  bad language Id(s)
  {$EXTERNALSYM MSIDBERROR_BADLANGUAGE}
  MSIDBERROR_BADFILENAME       = 13; //  bad filename
  {$EXTERNALSYM MSIDBERROR_BADFILENAME}
  MSIDBERROR_BADPATH           = 14; //  bad path
  {$EXTERNALSYM MSIDBERROR_BADPATH}
  MSIDBERROR_BADCONDITION      = 15; //  bad conditional statement
  {$EXTERNALSYM MSIDBERROR_BADCONDITION}
  MSIDBERROR_BADFORMATTED      = 16; //  bad format string
  {$EXTERNALSYM MSIDBERROR_BADFORMATTED}
  MSIDBERROR_BADTEMPLATE       = 17; //  bad template string
  {$EXTERNALSYM MSIDBERROR_BADTEMPLATE}
  MSIDBERROR_BADDEFAULTDIR     = 18; //  bad string in DefaultDir column of Directory table
  {$EXTERNALSYM MSIDBERROR_BADDEFAULTDIR}
  MSIDBERROR_BADREGPATH        = 19; //  bad registry path string
  {$EXTERNALSYM MSIDBERROR_BADREGPATH}
  MSIDBERROR_BADCUSTOMSOURCE   = 20; //  bad string in CustomSource column of CustomAction table
  {$EXTERNALSYM MSIDBERROR_BADCUSTOMSOURCE}
  MSIDBERROR_BADPROPERTY       = 21; //  bad property string
  {$EXTERNALSYM MSIDBERROR_BADPROPERTY}
  MSIDBERROR_MISSINGDATA       = 22; //  _Validation table missing reference to column
  {$EXTERNALSYM MSIDBERROR_MISSINGDATA}
  MSIDBERROR_BADCATEGORY       = 23; //  Category column of _Validation table for column is invalid
  {$EXTERNALSYM MSIDBERROR_BADCATEGORY}
  MSIDBERROR_BADKEYTABLE       = 24; //  table in KeyTable column of _Validation table could not be found/loaded
  {$EXTERNALSYM MSIDBERROR_BADKEYTABLE}
  MSIDBERROR_BADMAXMINVALUES   = 25; //  value in MaxValue column of _Validation table is less than value in MinValue column
  {$EXTERNALSYM MSIDBERROR_BADMAXMINVALUES}
  MSIDBERROR_BADCABINET        = 26; //  bad cabinet name
  {$EXTERNALSYM MSIDBERROR_BADCABINET}
  MSIDBERROR_BADSHORTCUT       = 27; //  bad shortcut target
  {$EXTERNALSYM MSIDBERROR_BADSHORTCUT}
  MSIDBERROR_STRINGOVERFLOW    = 28; //  string overflow (greater than length allowed in column def)
  {$EXTERNALSYM MSIDBERROR_STRINGOVERFLOW}
  MSIDBERROR_BADLOCALIZEATTRIB = 29; //  invalid localization attribute (primary keys cannot be localized)
  {$EXTERNALSYM MSIDBERROR_BADLOCALIZEATTRIB}

type
  MSIDBERROR = DWORD;
  {$EXTERNALSYM MSIDBERROR}
  TMsiDbError = MSIDBERROR;

const
  MSIRUNMODE_ADMIN           =  0; // admin mode install, else product install
  {$EXTERNALSYM MSIRUNMODE_ADMIN}
  MSIRUNMODE_ADVERTISE       =  1; // installing advertisements, else installing or updating product
  {$EXTERNALSYM MSIRUNMODE_ADVERTISE}
  MSIRUNMODE_MAINTENANCE     =  2; // modifying an existing installation, else new installation
  {$EXTERNALSYM MSIRUNMODE_MAINTENANCE}
  MSIRUNMODE_ROLLBACKENABLED =  3; // rollback is enabled
  {$EXTERNALSYM MSIRUNMODE_ROLLBACKENABLED}
  MSIRUNMODE_LOGENABLED      =  4; // log file active, enabled prior to install session
  {$EXTERNALSYM MSIRUNMODE_LOGENABLED}
  MSIRUNMODE_OPERATIONS      =  5; // spooling execute operations, else in determination phase
  {$EXTERNALSYM MSIRUNMODE_OPERATIONS}
  MSIRUNMODE_REBOOTATEND     =  6; // reboot needed after successful installation (settable)
  {$EXTERNALSYM MSIRUNMODE_REBOOTATEND}
  MSIRUNMODE_REBOOTNOW       =  7; // reboot needed to continue installation (settable)
  {$EXTERNALSYM MSIRUNMODE_REBOOTNOW}
  MSIRUNMODE_CABINET         =  8; // installing files from cabinets and files using Media table
  {$EXTERNALSYM MSIRUNMODE_CABINET}
  MSIRUNMODE_SOURCESHORTNAMES=  9; // source LongFileNames suppressed via PID_MSISOURCE summary property
  {$EXTERNALSYM MSIRUNMODE_SOURCESHORTNAMES}
  MSIRUNMODE_TARGETSHORTNAMES= 10; // target LongFileNames suppressed via SHORTFILENAMES property
  {$EXTERNALSYM MSIRUNMODE_TARGETSHORTNAMES}
  MSIRUNMODE_RESERVED11      = 11; // future use
  {$EXTERNALSYM MSIRUNMODE_RESERVED11}
  MSIRUNMODE_WINDOWS9X       = 12; // operating systems is Windows9?, else Windows NT
  {$EXTERNALSYM MSIRUNMODE_WINDOWS9X}
  MSIRUNMODE_ZAWENABLED      = 13; // operating system supports demand installation
  {$EXTERNALSYM MSIRUNMODE_ZAWENABLED}
  MSIRUNMODE_RESERVED14      = 14; // future use
  {$EXTERNALSYM MSIRUNMODE_RESERVED14}
  MSIRUNMODE_RESERVED15      = 15; // future use
  {$EXTERNALSYM MSIRUNMODE_RESERVED15}
  MSIRUNMODE_SCHEDULED       = 16; // custom action call from install script execution
  {$EXTERNALSYM MSIRUNMODE_SCHEDULED}
  MSIRUNMODE_ROLLBACK        = 17; // custom action call from rollback execution script
  {$EXTERNALSYM MSIRUNMODE_ROLLBACK}
  MSIRUNMODE_COMMIT          = 18; // custom action call from commit execution script
  {$EXTERNALSYM MSIRUNMODE_COMMIT}

type
  MSIRUNMODE = DWORD;
  {$EXTERNALSYM MSIRUNMODE}
  TMsiRunMode = MSIRUNMODE;

const
  INSTALLMESSAGE_TYPEMASK = DWORD($FF000000);  // mask for type code
  {$EXTERNALSYM INSTALLMESSAGE_TYPEMASK}

// Note: INSTALLMESSAGE_ERROR, INSTALLMESSAGE_WARNING, INSTALLMESSAGE_USER are to or'd
// with a message box style to indicate the buttons to display and return:
// MB_OK,MB_OKCANCEL,MB_ABORTRETRYIGNORE,MB_YESNOCANCEL,MB_YESNO,MB_RETRYCANCEL
// the default button (MB_DEFBUTTON1 is normal default):
// MB_DEFBUTTON1, MB_DEFBUTTON2, MB_DEFBUTTON3
// and optionally an icon style:
// MB_ICONERROR, MB_ICONQUESTION, MB_ICONWARNING, MB_ICONINFORMATION

const
  MSITRANSFORM_ERROR_ADDEXISTINGROW   = $00000001;
  {$EXTERNALSYM MSITRANSFORM_ERROR_ADDEXISTINGROW}
  MSITRANSFORM_ERROR_DELMISSINGROW    = $00000002;
  {$EXTERNALSYM MSITRANSFORM_ERROR_DELMISSINGROW}
  MSITRANSFORM_ERROR_ADDEXISTINGTABLE = $00000004;
  {$EXTERNALSYM MSITRANSFORM_ERROR_ADDEXISTINGTABLE}
  MSITRANSFORM_ERROR_DELMISSINGTABLE  = $00000008;
  {$EXTERNALSYM MSITRANSFORM_ERROR_DELMISSINGTABLE}
  MSITRANSFORM_ERROR_UPDATEMISSINGROW = $00000010;
  {$EXTERNALSYM MSITRANSFORM_ERROR_UPDATEMISSINGROW}
  MSITRANSFORM_ERROR_CHANGECODEPAGE   = $00000020;
  {$EXTERNALSYM MSITRANSFORM_ERROR_CHANGECODEPAGE}
  MSITRANSFORM_ERROR_VIEWTRANSFORM    = $00000100;
  {$EXTERNALSYM MSITRANSFORM_ERROR_VIEWTRANSFORM}

type
  MSITRANSFORM_ERROR = DWORD;
  {$EXTERNALSYM MSITRANSFORM_ERROR}
  TMsiTransformError = MSITRANSFORM_ERROR;

const
  MSITRANSFORM_VALIDATE_LANGUAGE                   = $00000001;
  {$EXTERNALSYM MSITRANSFORM_VALIDATE_LANGUAGE}
  MSITRANSFORM_VALIDATE_PRODUCT                    = $00000002;
  {$EXTERNALSYM MSITRANSFORM_VALIDATE_PRODUCT}
  MSITRANSFORM_VALIDATE_PLATFORM                   = $00000004;
  {$EXTERNALSYM MSITRANSFORM_VALIDATE_PLATFORM}
  MSITRANSFORM_VALIDATE_MAJORVERSION               = $00000008;
  {$EXTERNALSYM MSITRANSFORM_VALIDATE_MAJORVERSION}
  MSITRANSFORM_VALIDATE_MINORVERSION               = $00000010;
  {$EXTERNALSYM MSITRANSFORM_VALIDATE_MINORVERSION}
  MSITRANSFORM_VALIDATE_UPDATEVERSION              = $00000020;
  {$EXTERNALSYM MSITRANSFORM_VALIDATE_UPDATEVERSION}
  MSITRANSFORM_VALIDATE_NEWLESSBASEVERSION         = $00000040;
  {$EXTERNALSYM MSITRANSFORM_VALIDATE_NEWLESSBASEVERSION}
  MSITRANSFORM_VALIDATE_NEWLESSEQUALBASEVERSION    = $00000080;
  {$EXTERNALSYM MSITRANSFORM_VALIDATE_NEWLESSEQUALBASEVERSION}
  MSITRANSFORM_VALIDATE_NEWEQUALBASEVERSION        = $00000100;
  {$EXTERNALSYM MSITRANSFORM_VALIDATE_NEWEQUALBASEVERSION}
  MSITRANSFORM_VALIDATE_NEWGREATEREQUALBASEVERSION = $00000200;
  {$EXTERNALSYM MSITRANSFORM_VALIDATE_NEWGREATEREQUALBASEVERSION}
  MSITRANSFORM_VALIDATE_NEWGREATERBASEVERSION      = $00000400;
  {$EXTERNALSYM MSITRANSFORM_VALIDATE_NEWGREATERBASEVERSION}
  MSITRANSFORM_VALIDATE_UPGRADECODE                = $00000800;
  {$EXTERNALSYM MSITRANSFORM_VALIDATE_UPGRADECODE}

type
  MSITRANSFORM_VALIDATE = DWORD;
  {$EXTERNALSYM MSITRANSFORM_VALIDATE}
  TMsiTransformValidate = MSITRANSFORM_VALIDATE;

// -----------------------------------------------------------------------------
// Installer database access functions
// -----------------------------------------------------------------------------

// Prepare a database query, creating a view object
// Returns ERROR_SUCCESS if successful, and the view handle is returned,
// else ERROR_INVALID_HANDLE, ERROR_INVALID_HANDLE_STATE, ERROR_BAD_QUERY_SYNTAX, ERROR_GEN_FAILURE
// Execution of this function sets the error record, accessible via MsiGetLastErrorRecord

function MsiDatabaseOpenViewA(hDatabase: MSIHANDLE; szQuery: LPCSTR; var phView: MSIHANDLE): UINT; stdcall;
{$EXTERNALSYM MsiDatabaseOpenViewA}
function MsiDatabaseOpenViewW(hDatabase: MSIHANDLE; szQuery: LPCWSTR; var phView: MSIHANDLE): UINT; stdcall;
{$EXTERNALSYM MsiDatabaseOpenViewW}

{$IFDEF UNICODE}
function MsiDatabaseOpenView(hDatabase: MSIHANDLE; szQuery: LPCWSTR; var phView: MSIHANDLE): UINT; stdcall;
{$EXTERNALSYM MsiDatabaseOpenView}
{$ELSE}
function MsiDatabaseOpenView(hDatabase: MSIHANDLE; szQuery: LPCSTR; var phView: MSIHANDLE): UINT; stdcall;
{$EXTERNALSYM MsiDatabaseOpenView}
{$ENDIF}

// Returns the MSIDBERROR enum and name of the column corresponding to the error
// Similar to a GetLastError function, but for the view. NOT the same as MsiGetLastErrorRecord
// Returns errors of MsiViewModify.

function MsiViewGetErrorA(hView: MSIHANDLE; szColumnNameBuffer: LPSTR;
  var pcchBuf: DWORD): MSIDBERROR; stdcall;
{$EXTERNALSYM MsiViewGetErrorA}
function MsiViewGetErrorW(hView: MSIHANDLE; szColumnNameBuffer: LPWSTR;
  var pcchBuf: DWORD): MSIDBERROR; stdcall;
{$EXTERNALSYM MsiViewGetErrorW}

{$IFDEF UNICODE}
function MsiViewGetError(hView: MSIHANDLE; szColumnNameBuffer: LPWSTR;
  var pcchBuf: DWORD): MSIDBERROR; stdcall;
{$EXTERNALSYM MsiViewGetError}
{$ELSE}
function MsiViewGetError(hView: MSIHANDLE; szColumnNameBuffer: LPSTR;
  var pcchBuf: DWORD): MSIDBERROR; stdcall;
{$EXTERNALSYM MsiViewGetError}
{$ENDIF}

// Exectute the view query, supplying parameters as required
// Returns ERROR_SUCCESS, ERROR_INVALID_HANDLE, ERROR_INVALID_HANDLE_STATE, ERROR_GEN_FAILURE
// Execution of this function sets the error record, accessible via MsiGetLastErrorRecord

function MsiViewExecute(hView: MSIHANDLE; hRecord: MSIHANDLE): UINT; stdcall;
{$EXTERNALSYM MsiViewExecute}

// Fetch the next sequential record from the view
// Result is ERROR_SUCCESS if a row is found, and its handle is returned
// else ERROR_NO_MORE_ITEMS if no records remain, and a null handle is returned
// else result is error: ERROR_INVALID_HANDLE_STATE, ERROR_INVALID_HANDLE, ERROR_GEN_FAILURE

function MsiViewFetch(hView: MSIHANDLE; var phRecord: MSIHANDLE): UINT; stdcall;
{$EXTERNALSYM MsiViewFetch}

// Modify a database record, parameters must match types in query columns
// Returns ERROR_SUCCESS, ERROR_INVALID_HANDLE, ERROR_INVALID_HANDLE_STATE, ERROR_GEN_FAILURE, ERROR_ACCESS_DENIED
// Execution of this function sets the error record, accessible via MsiGetLastErrorRecord

function MsiViewModify(hView: MSIHANDLE; eModifyMode: MSIMODIFY; hRecord: MSIHANDLE): UINT; stdcall;
{$EXTERNALSYM MsiViewModify}

// Return the column names or specifications for the current view
// Returns ERROR_SUCCESS, ERROR_INVALID_HANDLE, ERROR_INVALID_PARAMETER, or ERROR_INVALID_HANDLE_STATE

function MsiViewGetColumnInfo(hView: MSIHANDLE; eColumnInfo: MSICOLINFO;
  var phRecord: MSIHANDLE): UINT; stdcall;
{$EXTERNALSYM MsiViewGetColumnInfo}

// Release the result set for an executed view, to allow re-execution
// Only needs to be called if not all records have been fetched
// Returns ERROR_SUCCESS, ERROR_INVALID_HANDLE, ERROR_INVALID_HANDLE_STATE

function MsiViewClose(hView: MSIHANDLE): UINT; stdcall;
{$EXTERNALSYM MsiViewClose}

// Return a record containing the names of all primary key columns for a given table
// Returns an MSIHANDLE for a record containing the name of each column.
// The field count of the record corresponds to the number of primary key columns.
// Field [0] of the record contains the table name.
// Returns ERROR_SUCCESS, ERROR_INVALID_HANDLE, ERROR_INVALID_TABLE

function MsiDatabaseGetPrimaryKeysA(hDatabase: MSIHANDLE; szTableName: LPCSTR;
  var phRecord: MSIHANDLE): UINT; stdcall;
{$EXTERNALSYM MsiDatabaseGetPrimaryKeysA}
function MsiDatabaseGetPrimaryKeysW(hDatabase: MSIHANDLE; szTableName: LPCWSTR;
  var phRecord: MSIHANDLE): UINT; stdcall;
{$EXTERNALSYM MsiDatabaseGetPrimaryKeysW}

{$IFDEF UNICODE}
function MsiDatabaseGetPrimaryKeys(hDatabase: MSIHANDLE; szTableName: LPCWSTR;
  var phRecord: MSIHANDLE): UINT; stdcall;
{$EXTERNALSYM MsiDatabaseGetPrimaryKeys}
{$ELSE}
function MsiDatabaseGetPrimaryKeys(hDatabase: MSIHANDLE; szTableName: LPCSTR;
  var phRecord: MSIHANDLE): UINT; stdcall;
{$EXTERNALSYM MsiDatabaseGetPrimaryKeys}
{$ENDIF}

// Return an enum defining the state of the table (temporary, unknown, or persistent).
// Returns MSICONDITION_ERROR, MSICONDITION_FALSE, MSICONDITION_TRUE, MSICONDITION_NONE

function MsiDatabaseIsTablePersistentA(hDatabase: MSIHANDLE; szTableName: LPCSTR): MSICONDITION; stdcall;
{$EXTERNALSYM MsiDatabaseIsTablePersistentA}
function MsiDatabaseIsTablePersistentW(hDatabase: MSIHANDLE; szTableName: LPCWSTR): MSICONDITION; stdcall;
{$EXTERNALSYM MsiDatabaseIsTablePersistentW}

{$IFDEF UNICODE}
function MsiDatabaseIsTablePersistent(hDatabase: MSIHANDLE; szTableName: LPCWSTR): MSICONDITION; stdcall;
{$EXTERNALSYM MsiDatabaseIsTablePersistent}
{$ELSE}
function MsiDatabaseIsTablePersistent(hDatabase: MSIHANDLE; szTableName: LPCSTR): MSICONDITION; stdcall;
{$EXTERNALSYM MsiDatabaseIsTablePersistent}
{$ENDIF}

// --------------------------------------------------------------------------
// Summary information stream management functions
// --------------------------------------------------------------------------

// Integer Property IDs:    1, 14, 15, 16, 19
// DateTime Property IDs:   10, 11, 12, 13
// Text Property IDs:       2, 3, 4, 5, 6, 7, 8, 9, 18
// Unsupported Propery IDs: 0 (PID_DICTIONARY), 17 (PID_THUMBNAIL)

// Obtain a handle for the _SummaryInformation stream for an MSI database
// Execution of this function sets the error record, accessible via MsiGetLastErrorRecord

function MsiGetSummaryInformationA(hDatabase: MSIHANDLE; szDatabasePath: LPCSTR;
  uiUpdateCount: UINT; var phSummaryInfo: MSIHANDLE): UINT; stdcall;
{$EXTERNALSYM MsiGetSummaryInformationA}
function MsiGetSummaryInformationW(hDatabase: MSIHANDLE; szDatabasePath: LPCWSTR;
  uiUpdateCount: UINT; var phSummaryInfo: MSIHANDLE): UINT; stdcall;
{$EXTERNALSYM MsiGetSummaryInformationW}

{$IFDEF UNICODE}
function MsiGetSummaryInformation(hDatabase: MSIHANDLE; szDatabasePath: LPCWSTR;
  uiUpdateCount: UINT; var phSummaryInfo: MSIHANDLE): UINT; stdcall;
{$EXTERNALSYM MsiGetSummaryInformation}
{$ELSE}
function MsiGetSummaryInformation(hDatabase: MSIHANDLE; szDatabasePath: LPCSTR;
  uiUpdateCount: UINT; var phSummaryInfo: MSIHANDLE): UINT; stdcall;
{$EXTERNALSYM MsiGetSummaryInformation}
{$ENDIF}

// Obtain the number of existing properties in the SummaryInformation stream

function MsiSummaryInfoGetPropertyCount(hSummaryInfo: MSIHANDLE; var puiPropertyCount: UINT): UINT; stdcall;
{$EXTERNALSYM MsiSummaryInfoGetPropertyCount}

// Set a single summary information property
// Returns ERROR_SUCCESS, ERROR_INVALID_HANDLE, ERROR_UNKNOWN_PROPERTY

function MsiSummaryInfoSetPropertyA(hSummaryInfo: MSIHANDLE; uiProperty: UINT;
  uiDataType: UINT; iValue: Integer; const pftValue: FILETIME; szValue: LPCSTR): UINT; stdcall;
{$EXTERNALSYM MsiSummaryInfoSetPropertyA}
function MsiSummaryInfoSetPropertyW(hSummaryInfo: MSIHANDLE; uiProperty: UINT;
  uiDataType: UINT; iValue: Integer; const pftValue: FILETIME; szValue: LPCWSTR): UINT; stdcall;
{$EXTERNALSYM MsiSummaryInfoSetPropertyW}

{$IFDEF UNICODE}
function MsiSummaryInfoSetProperty(hSummaryInfo: MSIHANDLE; uiProperty: UINT;
  uiDataType: UINT; iValue: Integer; const pftValue: FILETIME; szValue: LPCWSTR): UINT; stdcall;
{$EXTERNALSYM MsiSummaryInfoSetProperty}
{$ELSE}
function MsiSummaryInfoSetProperty(hSummaryInfo: MSIHANDLE; uiProperty: UINT;
  uiDataType: UINT; iValue: Integer; const pftValue: FILETIME; szValue: LPCSTR): UINT; stdcall;
{$EXTERNALSYM MsiSummaryInfoSetProperty}
{$ENDIF}

// Get a single property from the summary information
// Returns ERROR_SUCCESS, ERROR_INVALID_HANDLE, ERROR_UNKNOWN_PROPERTY

function MsiSummaryInfoGetPropertyA(hSummaryInfo: MSIHANDLE; uiProperty: UINT;
  var puiDataType: UINT; var piValue: Integer; var pftValue: FILETIME; szValueBuf: LPSTR;
  var pcchValueBuf: DWORD): UINT; stdcall;
{$EXTERNALSYM MsiSummaryInfoGetPropertyA}
function MsiSummaryInfoGetPropertyW(hSummaryInfo: MSIHANDLE; uiProperty: UINT;
  var puiDataType: UINT; var piValue: Integer; var pftValue: FILETIME; szValueBuf: LPWSTR;
  var pcchValueBuf: DWORD): UINT; stdcall;
{$EXTERNALSYM MsiSummaryInfoGetPropertyW}

{$IFDEF UNICODE}
function MsiSummaryInfoGetProperty(hSummaryInfo: MSIHANDLE; uiProperty: UINT;
  var puiDataType: UINT; var piValue: Integer; var pftValue: FILETIME; szValueBuf: LPWSTR;
  var pcchValueBuf: DWORD): UINT; stdcall;
{$EXTERNALSYM MsiSummaryInfoGetProperty}
{$ELSE}
function MsiSummaryInfoGetProperty(hSummaryInfo: MSIHANDLE; uiProperty: UINT;
  var puiDataType: UINT; var piValue: Integer; var pftValue: FILETIME; szValueBuf: LPSTR;
  var pcchValueBuf: DWORD): UINT; stdcall;
{$EXTERNALSYM MsiSummaryInfoGetProperty}
{$ENDIF}

// Write back changed information to summary information stream

function MsiSummaryInfoPersist(hSummaryInfo: MSIHANDLE): UINT; stdcall;
{$EXTERNALSYM MsiSummaryInfoPersist}

// --------------------------------------------------------------------------
// Installer database management functions - not used by custom actions
// --------------------------------------------------------------------------

// Open an installer database, specifying the persistance mode, which is a pointer.
// Predefined persist values are reserved pointer values, requiring pointer arithmetic.
// Execution of this function sets the error record, accessible via MsiGetLastErrorRecord

function MsiOpenDatabaseA(szDatabasePath: LPCSTR; szPersist: LPCSTR;
  var phDatabase: MSIHANDLE): UINT; stdcall;
{$EXTERNALSYM MsiOpenDatabaseA}
function MsiOpenDatabaseW(szDatabasePath: LPCWSTR; szPersist: LPCWSTR;
  var phDatabase: MSIHANDLE): UINT; stdcall;
{$EXTERNALSYM MsiOpenDatabaseW}

{$IFDEF UNICODE}
function MsiOpenDatabase(szDatabasePath: LPCWSTR; szPersist: LPCWSTR;
  var phDatabase: MSIHANDLE): UINT; stdcall;
{$EXTERNALSYM MsiOpenDatabase}
{$ELSE}
function MsiOpenDatabase(szDatabasePath: LPCSTR; szPersist: LPCSTR;
  var phDatabase: MSIHANDLE): UINT; stdcall;
{$EXTERNALSYM MsiOpenDatabase}
{$ENDIF}

// Import an MSI text archive table into an open database
// Execution of this function sets the error record, accessible via MsiGetLastErrorRecord

function MsiDatabaseImportA(hDatabase: MSIHANDLE; szFolderPath: LPCSTR;
  szFileName: LPCSTR): UINT; stdcall;
{$EXTERNALSYM MsiDatabaseImportA}
function MsiDatabaseImportW(hDatabase: MSIHANDLE; szFolderPath: LPCWSTR;
  szFileName: LPCWSTR): UINT; stdcall;
{$EXTERNALSYM MsiDatabaseImportW}

{$IFDEF UNICODE}
function MsiDatabaseImport(hDatabase: MSIHANDLE; szFolderPath: LPCWSTR;
  szFileName: LPCWSTR): UINT; stdcall;
{$EXTERNALSYM MsiDatabaseImport}
{$ELSE}
function MsiDatabaseImport(hDatabase: MSIHANDLE; szFolderPath: LPCSTR;
  szFileName: LPCSTR): UINT; stdcall;
{$EXTERNALSYM MsiDatabaseImport}
{$ENDIF}

// Export an MSI table from an open database to a text archive file
// Execution of this function sets the error record, accessible via MsiGetLastErrorRecord

function MsiDatabaseExportA(hDatabase: MSIHANDLE; szTableName: LPCSTR;
  szFolderPath: LPCSTR; szFileName: LPCSTR): UINT; stdcall;
{$EXTERNALSYM MsiDatabaseExportA}
function MsiDatabaseExportW(hDatabase: MSIHANDLE; szTableName: LPCWSTR;
  szFolderPath: LPCWSTR; szFileName: LPCWSTR): UINT; stdcall;
{$EXTERNALSYM MsiDatabaseExportW}

{$IFDEF UNICODE}
function MsiDatabaseExport(hDatabase: MSIHANDLE; szTableName: LPCWSTR;
  szFolderPath: LPCWSTR; szFileName: LPCWSTR): UINT; stdcall;
{$EXTERNALSYM MsiDatabaseExport}
{$ELSE}
function MsiDatabaseExport(hDatabase: MSIHANDLE; szTableName: LPCSTR;
  szFolderPath: LPCSTR; szFileName: LPCSTR): UINT; stdcall;
{$EXTERNALSYM MsiDatabaseExport}
{$ENDIF}

// Merge two database together, allowing duplicate rows
// Execution of this function sets the error record, accessible via MsiGetLastErrorRecord

function MsiDatabaseMergeA(hDatabase: MSIHANDLE; hDatabaseMerge: MSIHANDLE;
  szTableName: LPCSTR): UINT; stdcall;
{$EXTERNALSYM MsiDatabaseMergeA}
function MsiDatabaseMergeW(hDatabase: MSIHANDLE; hDatabaseMerge: MSIHANDLE;
  szTableName: LPCWSTR): UINT; stdcall;
{$EXTERNALSYM MsiDatabaseMergeW}

{$IFDEF UNICODE}
function MsiDatabaseMerge(hDatabase: MSIHANDLE; hDatabaseMerge: MSIHANDLE;
  szTableName: LPCWSTR): UINT; stdcall;
{$EXTERNALSYM MsiDatabaseMerge}
{$ELSE}
function MsiDatabaseMerge(hDatabase: MSIHANDLE; hDatabaseMerge: MSIHANDLE;
  szTableName: LPCSTR): UINT; stdcall;
{$EXTERNALSYM MsiDatabaseMerge}
{$ENDIF}

// Generate a transform file of differences between two databases
// Execution of this function sets the error record, accessible via MsiGetLastErrorRecord

function MsiDatabaseGenerateTransformA(hDatabase: MSIHANDLE; hDatabaseReference: MSIHANDLE;
  szTransformFile: LPCSTR; iReserved1: Integer; iReserved2: Integer): UINT; stdcall;
{$EXTERNALSYM MsiDatabaseGenerateTransformA}
function MsiDatabaseGenerateTransformW(hDatabase: MSIHANDLE; hDatabaseReference: MSIHANDLE;
  szTransformFile: LPCWSTR; iReserved1: Integer; iReserved2: Integer): UINT; stdcall;
{$EXTERNALSYM MsiDatabaseGenerateTransformW}

{$IFDEF UNICODE}
function MsiDatabaseGenerateTransform(hDatabase: MSIHANDLE; hDatabaseReference: MSIHANDLE;
  szTransformFile: LPCWSTR; iReserved1: Integer; iReserved2: Integer): UINT; stdcall;
{$EXTERNALSYM MsiDatabaseGenerateTransform}
{$ELSE}
function MsiDatabaseGenerateTransform(hDatabase: MSIHANDLE; hDatabaseReference: MSIHANDLE;
  szTransformFile: LPCSTR; iReserved1: Integer; iReserved2: Integer): UINT; stdcall;
{$EXTERNALSYM MsiDatabaseGenerateTransform}
{$ENDIF}

// Apply a transform file containing database difference
// Execution of this function sets the error record, accessible via MsiGetLastErrorRecord

function MsiDatabaseApplyTransformA(hDatabase: MSIHANDLE; szTransformFile: LPCSTR;
  iErrorConditions: Integer): UINT; stdcall;
{$EXTERNALSYM MsiDatabaseApplyTransformA}
function MsiDatabaseApplyTransformW(hDatabase: MSIHANDLE; szTransformFile: LPCWSTR;
  iErrorConditions: Integer): UINT; stdcall;
{$EXTERNALSYM MsiDatabaseApplyTransformW}

{$IFDEF UNICODE}
function MsiDatabaseApplyTransform(hDatabase: MSIHANDLE; szTransformFile: LPCWSTR;
  iErrorConditions: Integer): UINT; stdcall;
{$EXTERNALSYM MsiDatabaseApplyTransform}
{$ELSE}
function MsiDatabaseApplyTransform(hDatabase: MSIHANDLE; szTransformFile: LPCSTR;
  iErrorConditions: Integer): UINT; stdcall;
{$EXTERNALSYM MsiDatabaseApplyTransform}
{$ENDIF}

// Create summary information of existing transform to include validation and error conditions
// Execution of this function sets the error record, accessible via MsiGetLastErrorRecord

function MsiCreateTransformSummaryInfoA(hDatabase: MSIHANDLE; hDatabaseReference: MSIHANDLE;
  szTransformFile: LPCSTR; iErrorConditions: Integer; iValidation: Integer): UINT; stdcall;
{$EXTERNALSYM MsiCreateTransformSummaryInfoA}
function MsiCreateTransformSummaryInfoW(hDatabase: MSIHANDLE; hDatabaseReference: MSIHANDLE;
  szTransformFile: LPCWSTR; iErrorConditions: Integer; iValidation: Integer): UINT; stdcall;
{$EXTERNALSYM MsiCreateTransformSummaryInfoW}

{$IFDEF UNICODE}
function MsiCreateTransformSummaryInfo(hDatabase: MSIHANDLE; hDatabaseReference: MSIHANDLE;
  szTransformFile: LPCWSTR; iErrorConditions: Integer; iValidation: Integer): UINT; stdcall;
{$EXTERNALSYM MsiCreateTransformSummaryInfo}
{$ELSE}
function MsiCreateTransformSummaryInfo(hDatabase: MSIHANDLE; hDatabaseReference: MSIHANDLE;
  szTransformFile: LPCSTR; iErrorConditions: Integer; iValidation: Integer): UINT; stdcall;
{$EXTERNALSYM MsiCreateTransformSummaryInfo}
{$ENDIF}

// Write out all persistent table data, ignored if database opened read-only
// Execution of this function sets the error record, accessible via MsiGetLastErrorRecord

function MsiDatabaseCommit(hDatabase: MSIHANDLE): UINT; stdcall;
{$EXTERNALSYM MsiDatabaseCommit}

// Return the update state of a database

function MsiGetDatabaseState(hDatabase: MSIHANDLE): MSIDBSTATE; stdcall;
{$EXTERNALSYM MsiGetDatabaseState}

// --------------------------------------------------------------------------
// Record object functions
// --------------------------------------------------------------------------

// Create a new record object with the requested number of fields
// Field 0, not included in count, is used for format strings and op codes
// All fields are initialized to null
// Returns a handle to the created record, or 0 if memory could not be allocated

function MsiCreateRecord(cParams: UINT): MSIHANDLE; stdcall;
{$EXTERNALSYM MsiCreateRecord}

// Report whether a record field is NULL
// Returns TRUE if the field is null or does not exist
// Returns FALSE if the field contains data, or the handle is invalid

function MsiRecordIsNull(hRecord: MSIHANDLE; iField: UINT): BOOL; stdcall;
{$EXTERNALSYM MsiRecordIsNull}

// Return the length of a record field
// Returns 0 if field is NULL or non-existent
// Returns sizeof(Integer) if integer data
// Returns character count if string data (not counting null terminator)
// Returns bytes count if stream data

function MsiRecordDataSize(hRecord: MSIHANDLE; iField: UINT): UINT; stdcall;
{$EXTERNALSYM MsiRecordDataSize}

// Set a record field to an integer value
// Returns ERROR_SUCCESS, ERROR_INVALID_HANDLE, ERROR_INVALID_FIELD

function MsiRecordSetInteger(hRecord: MSIHANDLE; iField: UINT; iValue: Integer): UINT; stdcall;
{$EXTERNALSYM MsiRecordSetInteger}

// Copy a string into the designated field
// A null string pointer and an empty string both set the field to null
// Returns ERROR_SUCCESS, ERROR_INVALID_HANDLE, ERROR_INVALID_FIELD

function MsiRecordSetStringA(hRecord: MSIHANDLE; iField: UINT; szValue: LPCSTR): UINT; stdcall;
{$EXTERNALSYM MsiRecordSetStringA}
function MsiRecordSetStringW(hRecord: MSIHANDLE; iField: UINT; szValue: LPCWSTR): UINT; stdcall;
{$EXTERNALSYM MsiRecordSetStringW}

{$IFDEF UNICODE}
function MsiRecordSetString(hRecord: MSIHANDLE; iField: UINT; szValue: LPCWSTR): UINT; stdcall;
{$EXTERNALSYM MsiRecordSetString}
{$ELSE}
function MsiRecordSetString(hRecord: MSIHANDLE; iField: UINT; szValue: LPCSTR): UINT; stdcall;
{$EXTERNALSYM MsiRecordSetString}
{$ENDIF}

// Return the integer value from a record field
// Returns the value MSI_NULL_INTEGER if the field is null
// or if the field is a string that cannot be converted to an integer

function MsiRecordGetInteger(hRecord: MSIHANDLE; iField: UINT): Integer; stdcall;
{$EXTERNALSYM MsiRecordGetInteger}

// Return the string value of a record field
// Integer fields will be converted to a string
// Null and non-existent fields will report a value of 0
// Fields containing stream data will return ERROR_INVALID_DATATYPE
// Returns ERROR_SUCCESS, ERROR_MORE_DATA,
//         ERROR_INVALID_HANDLE, ERROR_INVALID_FIELD, ERROR_BAD_ARGUMENTS

function MsiRecordGetStringA(hRecord: MSIHANDLE; iField: UINT; szValueBuf: LPSTR;
  var pcchValueBuf: DWORD): UINT; stdcall;
{$EXTERNALSYM MsiRecordGetStringA}
function MsiRecordGetStringW(hRecord: MSIHANDLE; iField: UINT; szValueBuf: LPWSTR;
  var pcchValueBuf: DWORD): UINT; stdcall;
{$EXTERNALSYM MsiRecordGetStringW}

{$IFDEF UNICODE}
function MsiRecordGetString(hRecord: MSIHANDLE; iField: UINT; szValueBuf: LPWSTR;
  var pcchValueBuf: DWORD): UINT; stdcall;
{$EXTERNALSYM MsiRecordGetString}
{$ELSE}
function MsiRecordGetString(hRecord: MSIHANDLE; iField: UINT; szValueBuf: LPSTR;
  var pcchValueBuf: DWORD): UINT; stdcall;
{$EXTERNALSYM MsiRecordGetString}
{$ENDIF}

// Returns the number of fields allocated in the record
// Does not count field 0, used for formatting and op codes

function MsiRecordGetFieldCount(hRecord: MSIHANDLE): UINT; stdcall;
{$EXTERNALSYM MsiRecordGetFieldCount}

// Set a record stream field from a file
// The contents of the specified file will be read into a stream object
// The stream will be persisted if the record is inserted into the database
// Execution of this function sets the error record, accessible via MsiGetLastErrorRecord

function MsiRecordSetStreamA(hRecord: MSIHANDLE; iField: UINT; szFilePath: LPCSTR): UINT; stdcall;
{$EXTERNALSYM MsiRecordSetStreamA}
function MsiRecordSetStreamW(hRecord: MSIHANDLE; iField: UINT; szFilePath: LPCWSTR): UINT; stdcall;
{$EXTERNALSYM MsiRecordSetStreamW}

{$IFDEF UNICODE}
function MsiRecordSetStream(hRecord: MSIHANDLE; iField: UINT; szFilePath: LPCWSTR): UINT; stdcall;
{$EXTERNALSYM MsiRecordSetStream}
{$ELSE}
function MsiRecordSetStream(hRecord: MSIHANDLE; iField: UINT; szFilePath: LPCSTR): UINT; stdcall;
{$EXTERNALSYM MsiRecordSetStream}
{$ENDIF}

// Read bytes from a record stream field into a buffer
// Must set the in/out argument to the requested byte count to read
// The number of bytes transferred is returned through the argument
// If no more bytes are available, ERROR_SUCCESS is still returned

function MsiRecordReadStream(hRecord: MSIHANDLE; iField: UINT; szDataBuf: PChar;
  var pcbDataBuf: DWORD): UINT; stdcall;
{$EXTERNALSYM MsiRecordReadStream}

// Clears all data fields in a record to NULL

function MsiRecordClearData(hRecord: MSIHANDLE): UINT; stdcall;
{$EXTERNALSYM MsiRecordClearData}

// --------------------------------------------------------------------------
// Functions to access a running installation, called from custom actions
// The install handle is the single argument passed to custom actions
// --------------------------------------------------------------------------

// Return a handle to the database currently in use by this installer instance

function MsiGetActiveDatabase(hInstall: MSIHANDLE): MSIHANDLE; stdcall;
{$EXTERNALSYM MsiGetActiveDatabase}

// Set the value for an installer property
// If the property is not defined, it will be created
// If the value is null or an empty string, the property will be removed
// Returns ERROR_SUCCESS, ERROR_INVALID_HANDLE, ERROR_BAD_ARGUMENTS

function MsiSetPropertyA(hInstall: MSIHANDLE; szName: LPCSTR; szValue: LPCSTR): UINT; stdcall;
{$EXTERNALSYM MsiSetPropertyA}
function MsiSetPropertyW(hInstall: MSIHANDLE; szName: LPCWSTR; szValue: LPCWSTR): UINT; stdcall;
{$EXTERNALSYM MsiSetPropertyW}

{$IFDEF UNICODE}
function MsiSetProperty(hInstall: MSIHANDLE; szName: LPCWSTR; szValue: LPCWSTR): UINT; stdcall;
{$EXTERNALSYM MsiSetProperty}
{$ELSE}
function MsiSetProperty(hInstall: MSIHANDLE; szName: LPCSTR; szValue: LPCSTR): UINT; stdcall;
{$EXTERNALSYM MsiSetProperty}
{$ENDIF}

// Get the value for an installer property
// If the property is not defined, it is equivalent to a 0-length value, not error
// Returns ERROR_SUCCESS, ERROR_MORE_DATA, ERROR_INVALID_HANDLE, ERROR_BAD_ARGUMENTS

function MsiGetPropertyA(hInstall: MSIHANDLE; szName: LPCSTR; szValueBuf: LPSTR;
  var pcchValueBuf: DWORD): UINT; stdcall;
{$EXTERNALSYM MsiGetPropertyA}
function MsiGetPropertyW(hInstall: MSIHANDLE; szName: LPCWSTR; szValueBuf: LPWSTR;
  var pcchValueBuf: DWORD): UINT; stdcall;
{$EXTERNALSYM MsiGetPropertyW}

{$IFDEF UNICODE}
function MsiGetProperty(hInstall: MSIHANDLE; szName: LPCWSTR; szValueBuf: LPWSTR;
  var pcchValueBuf: DWORD): UINT; stdcall;
{$EXTERNALSYM MsiGetProperty}
{$ELSE}
function MsiGetProperty(hInstall: MSIHANDLE; szName: LPCSTR; szValueBuf: LPSTR;
  var pcchValueBuf: DWORD): UINT; stdcall;
{$EXTERNALSYM MsiGetProperty}
{$ENDIF}

// Return the numeric language for the currently running install
// Returns 0 if an install not running

function MsiGetLanguage(hInstall: MSIHANDLE): LANGID; stdcall;
{$EXTERNALSYM MsiGetLanguage}

// Return one of the boolean internal installer states
// Returns FALSE if the handle is not active or if the mode is not implemented

function MsiGetMode(hInstall: MSIHANDLE; eRunMode: MSIRUNMODE): BOOL; stdcall;
{$EXTERNALSYM MsiGetMode}

// Set an internal install session boolean mode - Note: most modes are read-only
// Returns ERROR_SUCCESS if the mode can be set to the desired state
// Returns ERROR_ACCESS_DENIED if the mode is not settable
// Returns ERROR_INVALID_HANDLE if the handle is not an active install session

function MsiSetMode(hInstall: MSIHANDLE; eRunMode: MSIRUNMODE; fState: BOOL): UINT; stdcall;
{$EXTERNALSYM MsiSetMode}

// Format record data using a format string containing field markers and/or properties
// Record field 0 must contain the format string
// Other fields must contain data that may be referenced by the format string.

function MsiFormatRecordA(hInstall: MSIHANDLE; hRecord: MSIHANDLE; szResultBuf: LPSTR;
  var pcchResultBuf: DWORD): UINT; stdcall;
{$EXTERNALSYM MsiFormatRecordA}
function MsiFormatRecordW(hInstall: MSIHANDLE; hRecord: MSIHANDLE; szResultBuf: LPWSTR;
  var pcchResultBuf: DWORD): UINT; stdcall;
{$EXTERNALSYM MsiFormatRecordW}

{$IFDEF UNICODE}
function MsiFormatRecord(hInstall: MSIHANDLE; hRecord: MSIHANDLE; szResultBuf: LPWSTR;
  var pcchResultBuf: DWORD): UINT; stdcall;
{$EXTERNALSYM MsiFormatRecord}
{$ELSE}
function MsiFormatRecord(hInstall: MSIHANDLE; hRecord: MSIHANDLE; szResultBuf: LPSTR;
  var pcchResultBuf: DWORD): UINT; stdcall;
{$EXTERNALSYM MsiFormatRecord}
{$ENDIF}

// Execute another action, either built-in, custom, or UI wizard
// Returns ERROR_FUNCTION_NOT_CALLED if action not found
// Returns ERROR_SUCCESS if action completed succesfully
// Returns ERROR_INSTALL_USEREXIT if user cancelled during action
// Returns ERROR_INSTALL_FAILURE if action failed
// Returns ERROR_INSTALL_SUSPEND if user suspended installation
// Returns ERROR_MORE_DATA if action wishes to skip remaining actions
// Returns ERROR_INVALID_HANDLE_STATE if install session not active
// Returns ERROR_INVALID_DATA if failure calling custom action
// Returns ERROR_INVALID_HANDLE or ERROR_INVALID_PARAMETER if arguments invalid

function MsiDoActionA(hInstall: MSIHANDLE; szAction: LPCSTR): UINT; stdcall;
{$EXTERNALSYM MsiDoActionA}
function MsiDoActionW(hInstall: MSIHANDLE; szAction: LPCWSTR): UINT; stdcall;
{$EXTERNALSYM MsiDoActionW}

{$IFDEF UNICODE}
function MsiDoAction(hInstall: MSIHANDLE; szAction: LPCWSTR): UINT; stdcall;
{$EXTERNALSYM MsiDoAction}
{$ELSE}
function MsiDoAction(hInstall: MSIHANDLE; szAction: LPCSTR): UINT; stdcall;
{$EXTERNALSYM MsiDoAction}
{$ENDIF}

// Execute another action sequence, as descibed in the specified table
// Returns the same error codes as MsiDoAction

function MsiSequenceA(hInstall: MSIHANDLE; szTable: LPCSTR; iSequenceMode: Integer): UINT; stdcall;
{$EXTERNALSYM MsiSequenceA}
function MsiSequenceW(hInstall: MSIHANDLE; szTable: LPCWSTR; iSequenceMode: Integer): UINT; stdcall;
{$EXTERNALSYM MsiSequenceW}

{$IFDEF UNICODE}
function MsiSequence(hInstall: MSIHANDLE; szTable: LPCWSTR; iSequenceMode: Integer): UINT; stdcall;
{$EXTERNALSYM MsiSequence}
{$ELSE}
function MsiSequence(hInstall: MSIHANDLE; szTable: LPCSTR; iSequenceMode: Integer): UINT; stdcall;
{$EXTERNALSYM MsiSequence}
{$ENDIF}

// Send an error record to the installer for processing.
// If field 0 (template) is not set, field 1 must be set to the error code,
//   corresponding the the error message in the Error database table,
//   and the message will be formatted using the template from the Error table
//   before passing it to the UI handler for display.
// Returns Win32 button codes: IDOK IDCANCEL IDABORT IDRETRY IDIGNORE IDYES IDNO
//   or 0 if no action taken, or -1 if invalid argument or handle

function MsiProcessMessage(hInstall: MSIHANDLE; eMessageType: INSTALLMESSAGE;
  hRecord: MSIHANDLE): Integer; stdcall;
{$EXTERNALSYM MsiProcessMessage}

// Evaluate a conditional expression containing property names and values

function MsiEvaluateConditionA(hInstall: MSIHANDLE; szCondition: LPCSTR): MSICONDITION; stdcall;
{$EXTERNALSYM MsiEvaluateConditionA}
function MsiEvaluateConditionW(hInstall: MSIHANDLE; szCondition: LPCWSTR): MSICONDITION; stdcall;
{$EXTERNALSYM MsiEvaluateConditionW}

{$IFDEF UNICODE}
function MsiEvaluateCondition(hInstall: MSIHANDLE; szCondition: LPCWSTR): MSICONDITION; stdcall;
{$EXTERNALSYM MsiEvaluateCondition}
{$ELSE}
function MsiEvaluateCondition(hInstall: MSIHANDLE; szCondition: LPCSTR): MSICONDITION; stdcall;
{$EXTERNALSYM MsiEvaluateCondition}
{$ENDIF}

// Get the installed state and requested action state of a feature
// Execution of this function sets the error record, accessible via MsiGetLastErrorRecord

function MsiGetFeatureStateA(hInstall: MSIHANDLE; szFeature: LPCSTR;
  var piInstalled: INSTALLSTATE; var piAction: INSTALLSTATE): UINT; stdcall;
{$EXTERNALSYM MsiGetFeatureStateA}
function MsiGetFeatureStateW(hInstall: MSIHANDLE; szFeature: LPCWSTR;
  var piInstalled: INSTALLSTATE; var piAction: INSTALLSTATE): UINT; stdcall;
{$EXTERNALSYM MsiGetFeatureStateW}

{$IFDEF UNICODE}
function MsiGetFeatureState(hInstall: MSIHANDLE; szFeature: LPCWSTR;
  var piInstalled: INSTALLSTATE; var piAction: INSTALLSTATE): UINT; stdcall;
{$EXTERNALSYM MsiGetFeatureState}
{$ELSE}
function MsiGetFeatureState(hInstall: MSIHANDLE; szFeature: LPCSTR;
  var piInstalled: INSTALLSTATE; var piAction: INSTALLSTATE): UINT; stdcall;
{$EXTERNALSYM MsiGetFeatureState}
{$ENDIF}

// Request a feature to be set to a specified state
// Execution of this function sets the error record, accessible via MsiGetLastErrorRecord

function MsiSetFeatureStateA(hInstall: MSIHANDLE; szFeature: LPCSTR;
  iState: INSTALLSTATE): UINT; stdcall;
{$EXTERNALSYM MsiSetFeatureStateA}
function MsiSetFeatureStateW(hInstall: MSIHANDLE; szFeature: LPCWSTR;
  iState: INSTALLSTATE): UINT; stdcall;
{$EXTERNALSYM MsiSetFeatureStateW}

{$IFDEF UNICODE}
function MsiSetFeatureState(hInstall: MSIHANDLE; szFeature: LPCWSTR;
  iState: INSTALLSTATE): UINT; stdcall;
{$EXTERNALSYM MsiSetFeatureState}
{$ELSE}
function MsiSetFeatureState(hInstall: MSIHANDLE; szFeature: LPCSTR;
  iState: INSTALLSTATE): UINT; stdcall;
{$EXTERNALSYM MsiSetFeatureState}
{$ENDIF}

// Set the attribute bits of a specified feature at runtime.
// Execution of this function sets the error record, accessible via MsiGetLastErrorRecord

function MsiSetFeatureAttributesA(hInstall: MSIHANDLE; szFeature: LPCSTR;
  dwAttributes: DWORD): UINT; stdcall;
{$EXTERNALSYM MsiSetFeatureAttributesA}
function MsiSetFeatureAttributesW(hInstall: MSIHANDLE; szFeature: LPCWSTR;
  dwAttributes: DWORD): UINT; stdcall;
{$EXTERNALSYM MsiSetFeatureAttributesW}

{$IFDEF UNICODE}
function MsiSetFeatureAttributes(hInstall: MSIHANDLE; szFeature: LPCWSTR;
  dwAttributes: DWORD): UINT; stdcall;
{$EXTERNALSYM MsiSetFeatureAttributes}
{$ELSE}
function MsiSetFeatureAttributes(hInstall: MSIHANDLE; szFeature: LPCSTR;
  dwAttributes: DWORD): UINT; stdcall;
{$EXTERNALSYM MsiSetFeatureAttributes}
{$ENDIF}

// Get the installed state and requested action state of a component
// Execution of this function sets the error record, accessible via MsiGetLastErrorRecord

function MsiGetComponentStateA(hInstall: MSIHANDLE; szComponent: LPCSTR;
  var piInstalled: INSTALLSTATE; var piAction: INSTALLSTATE): UINT; stdcall;
{$EXTERNALSYM MsiGetComponentStateA}
function MsiGetComponentStateW(hInstall: MSIHANDLE; szComponent: LPCWSTR;
  var piInstalled: INSTALLSTATE; var piAction: INSTALLSTATE): UINT; stdcall;
{$EXTERNALSYM MsiGetComponentStateW}

{$IFDEF UNICODE}
function MsiGetComponentState(hInstall: MSIHANDLE; szComponent: LPCWSTR;
  var piInstalled: INSTALLSTATE; var piAction: INSTALLSTATE): UINT; stdcall;
{$EXTERNALSYM MsiGetComponentState}
{$ELSE}
function MsiGetComponentState(hInstall: MSIHANDLE; szComponent: LPCSTR;
  var piInstalled: INSTALLSTATE; var piAction: INSTALLSTATE): UINT; stdcall;
{$EXTERNALSYM MsiGetComponentState}
{$ENDIF}

// Request a component to be set to a specified state
// Execution of this function sets the error record, accessible via MsiGetLastErrorRecord

function MsiSetComponentStateA(hInstall: MSIHANDLE; szComponent: LPCSTR;
  iState: INSTALLSTATE): UINT; stdcall;
{$EXTERNALSYM MsiSetComponentStateA}
function MsiSetComponentStateW(hInstall: MSIHANDLE; szComponent: LPCWSTR;
  iState: INSTALLSTATE): UINT; stdcall;
{$EXTERNALSYM MsiSetComponentStateW}

{$IFDEF UNICODE}
function MsiSetComponentState(hInstall: MSIHANDLE; szComponent: LPCWSTR;
  iState: INSTALLSTATE): UINT; stdcall;
{$EXTERNALSYM MsiSetComponentState}
{$ELSE}
function MsiSetComponentState(hInstall: MSIHANDLE; szComponent: LPCSTR;
  iState: INSTALLSTATE): UINT; stdcall;
{$EXTERNALSYM MsiSetComponentState}
{$ENDIF}

// Return the disk cost for a feature and related features
// Can specify either current feature state or proposed state
// Can specify extent of related features to cost
// Note that adding costs for several features may produce an
// excessively large cost due to shared components and parents.
// Execution of this function sets the error record, accessible via MsiGetLastErrorRecord

function MsiGetFeatureCostA(hInstall: MSIHANDLE; szFeature: LPCSTR;
  iCostTree: MSICOSTTREE; iState: INSTALLSTATE; var piCost: Integer): UINT; stdcall;
{$EXTERNALSYM MsiGetFeatureCostA}
function MsiGetFeatureCostW(hInstall: MSIHANDLE; szFeature: LPCWSTR;
  iCostTree: MSICOSTTREE; iState: INSTALLSTATE; var piCost: Integer): UINT; stdcall;
{$EXTERNALSYM MsiGetFeatureCostW}

{$IFDEF UNICODE}
function MsiGetFeatureCost(hInstall: MSIHANDLE; szFeature: LPCWSTR;
  iCostTree: MSICOSTTREE; iState: INSTALLSTATE; var piCost: Integer): UINT; stdcall;
{$EXTERNALSYM MsiGetFeatureCost}
{$ELSE}
function MsiGetFeatureCost(hInstall: MSIHANDLE; szFeature: LPCSTR;
  iCostTree: MSICOSTTREE; iState: INSTALLSTATE; var piCost: Integer): UINT; stdcall;
{$EXTERNALSYM MsiGetFeatureCost}
{$ENDIF}

// Enumerates the costs and temporary costs per drives for
// szComponent. If szComponent is set to NULL, it enumerates
// the above costs for the engine, per drives.
//
// The enumeration is 0-based, i.e. it returns the data for
// the first drive when called w/ dwIndex set to 0.
//
// Can specify either current feature state or proposed state.
//
// Execution of this function sets the error record, accessible
// via MsiGetLastErrorRecord.

function MsiEnumComponentCostsA(hInstall: MSIHANDLE; szComponent: LPCSTR; dwIndex: DWORD; iState: INSTALLSTATE;
  szDriveBuf: LPSTR; var pcchDriveBuf: DWORD; var piCost: INT; piTempCost: INT): UINT; stdcall;
{$EXTERNALSYM MsiEnumComponentCostsA}
function MsiEnumComponentCostsW(hInstall: MSIHANDLE; szComponent: LPCWSTR; dwIndex: DWORD; iState: INSTALLSTATE;
  szDriveBuf: LPWSTR; var pcchDriveBuf: DWORD; var piCost: INT; var piTempCost: INT): UINT; stdcall;
{$EXTERNALSYM MsiEnumComponentCostsW}

{$IFDEF UNICODE}
function MsiEnumComponentCosts(hInstall: MSIHANDLE; szComponent: LPCWSTR; dwIndex: DWORD; iState: INSTALLSTATE;
  szDriveBuf: LPWSTR; var pcchDriveBuf: DWORD; var piCost: INT; var piTempCost: INT): UINT; stdcall;
{$EXTERNALSYM MsiEnumComponentCosts}
{$ELSE}
function MsiEnumComponentCosts(hInstall: MSIHANDLE; szComponent: LPCSTR; dwIndex: DWORD; iState: INSTALLSTATE;
  szDriveBuf: LPSTR; var pcchDriveBuf: DWORD; var piCost: INT; piTempCost: INT): UINT; stdcall;
{$EXTERNALSYM MsiEnumComponentCosts}
{$ENDIF}

// Set the install level for a full product installation (not a feature request)
// Setting the value to 0 initialized components and features to the default level
// Execution of this function sets the error record, accessible via MsiGetLastErrorRecord

function MsiSetInstallLevel(hInstall: MSIHANDLE; iInstallLevel: Integer): UINT; stdcall;
{$EXTERNALSYM MsiSetInstallLevel}

// Get the valid install states for a feature, represented by bit flags
// For each valid install state, a bit is set of value: (1 << INSTALLSTATE)
// Execution of this function sets the error record, accessible via MsiGetLastErrorRecord

function MsiGetFeatureValidStatesA(hInstall: MSIHANDLE; szFeature: LPCSTR;
  var dwInstallStates: DWORD): UINT; stdcall;
{$EXTERNALSYM MsiGetFeatureValidStatesA}
function MsiGetFeatureValidStatesW(hInstall: MSIHANDLE; szFeature: LPCWSTR;
  var dwInstallStates: DWORD): UINT; stdcall;
{$EXTERNALSYM MsiGetFeatureValidStatesW}

{$IFDEF UNICODE}
function MsiGetFeatureValidStates(hInstall: MSIHANDLE; szFeature: LPCWSTR;
  var dwInstallStates: DWORD): UINT; stdcall;
{$EXTERNALSYM MsiGetFeatureValidStates}
{$ELSE}
function MsiGetFeatureValidStates(hInstall: MSIHANDLE; szFeature: LPCSTR;
  var dwInstallStates: DWORD): UINT; stdcall;
{$EXTERNALSYM MsiGetFeatureValidStates}
{$ENDIF}

// Return the full source path for a folder in the Directory table
// Execution of this function sets the error record, accessible via MsiGetLastErrorRecord

function MsiGetSourcePathA(hInstall: MSIHANDLE; szFolder: LPCSTR; szPathBuf: LPSTR;
  var pcchPathBuf: DWORD): UINT; stdcall;
{$EXTERNALSYM MsiGetSourcePathA}
function MsiGetSourcePathW(hInstall: MSIHANDLE; szFolder: LPCWSTR; szPathBuf: LPWSTR;
  var pcchPathBuf: DWORD): UINT; stdcall;
{$EXTERNALSYM MsiGetSourcePathW}

{$IFDEF UNICODE}
function MsiGetSourcePath(hInstall: MSIHANDLE; szFolder: LPCWSTR; szPathBuf: LPWSTR;
  var pcchPathBuf: DWORD): UINT; stdcall;
{$EXTERNALSYM MsiGetSourcePath}
{$ELSE}
function MsiGetSourcePath(hInstall: MSIHANDLE; szFolder: LPCSTR; szPathBuf: LPSTR;
  var pcchPathBuf: DWORD): UINT; stdcall;
{$EXTERNALSYM MsiGetSourcePath}
{$ENDIF}

// Return the full target path for a folder in the Directory table
// Execution of this function sets the error record, accessible via MsiGetLastErrorRecord

function MsiGetTargetPathA(hInstall: MSIHANDLE; szFolder: LPCSTR;
  szPathBuf: LPSTR; var pcchPathBuf: DWORD): UINT; stdcall;
{$EXTERNALSYM MsiGetTargetPathA}
function MsiGetTargetPathW(hInstall: MSIHANDLE; szFolder: LPCWSTR;
  szPathBuf: LPWSTR; var pcchPathBuf: DWORD): UINT; stdcall;
{$EXTERNALSYM MsiGetTargetPathW}

{$IFDEF UNICODE}
function MsiGetTargetPath(hInstall: MSIHANDLE; szFolder: LPCWSTR;
  szPathBuf: LPWSTR; var pcchPathBuf: DWORD): UINT; stdcall;
{$EXTERNALSYM MsiGetTargetPath}
{$ELSE}
function MsiGetTargetPath(hInstall: MSIHANDLE; szFolder: LPCSTR;
  szPathBuf: LPSTR; var pcchPathBuf: DWORD): UINT; stdcall;
{$EXTERNALSYM MsiGetTargetPath}
{$ENDIF}

// Set the full target path for a folder in the Directory table
// Execution of this function sets the error record, accessible via MsiGetLastErrorRecord

function MsiSetTargetPathA(hInstall: MSIHANDLE; szFolder: LPCSTR;
  szFolderPath: LPCSTR): UINT; stdcall;
{$EXTERNALSYM MsiSetTargetPathA}
function MsiSetTargetPathW(hInstall: MSIHANDLE; szFolder: LPCWSTR;
  szFolderPath: LPCWSTR): UINT; stdcall;
{$EXTERNALSYM MsiSetTargetPathW}

{$IFDEF UNICODE}
function MsiSetTargetPath(hInstall: MSIHANDLE; szFolder: LPCWSTR;
  szFolderPath: LPCWSTR): UINT; stdcall;
{$EXTERNALSYM MsiSetTargetPath}
{$ELSE}
function MsiSetTargetPath(hInstall: MSIHANDLE; szFolder: LPCSTR;
  szFolderPath: LPCSTR): UINT; stdcall;
{$EXTERNALSYM MsiSetTargetPath}
{$ENDIF}

// Check to see if sufficent disk space is present for the current installation
// Returns ERROR_SUCCESS, ERROR_DISK_FULL, ERROR_INVALID_HANDLE_STATE, or ERROR_INVALID_HANDLE

function MsiVerifyDiskSpace(hInstall: MSIHANDLE): UINT; stdcall;
{$EXTERNALSYM MsiVerifyDiskSpace}

// --------------------------------------------------------------------------
// Functions for rendering UI dialogs from the database representations.
// Purpose is for product development, not for use during installation.
// --------------------------------------------------------------------------

// Enable UI in preview mode to facilitate authoring of UI dialogs.
// The preview mode will end when the handle is closed.

function MsiEnableUIPreview(hDatabase: MSIHANDLE; var phPreview: MSIHANDLE): UINT; stdcall;
{$EXTERNALSYM MsiEnableUIPreview}

// Display any UI dialog as modeless and inactive.
// Supplying a null name will remove any current dialog.

function MsiPreviewDialogA(hPreview: MSIHANDLE; szDialogName: LPCSTR): UINT; stdcall;
{$EXTERNALSYM MsiPreviewDialogA}
function MsiPreviewDialogW(hPreview: MSIHANDLE; szDialogName: LPCWSTR): UINT; stdcall;
{$EXTERNALSYM MsiPreviewDialogW}

{$IFDEF UNICODE}
function MsiPreviewDialog(hPreview: MSIHANDLE; szDialogName: LPCWSTR): UINT; stdcall;
{$EXTERNALSYM MsiPreviewDialog}
{$ELSE}
function MsiPreviewDialog(hPreview: MSIHANDLE; szDialogName: LPCSTR): UINT; stdcall;
{$EXTERNALSYM MsiPreviewDialog}
{$ENDIF}

// Display a billboard within a host control in the displayed dialog.
// Supplying a null billboard name will remove any billboard displayed.

function MsiPreviewBillboardA(hPreview: MSIHANDLE; szControlName: LPCSTR;
  szBillboard: LPCSTR): UINT; stdcall;
{$EXTERNALSYM MsiPreviewBillboardA}
function MsiPreviewBillboardW(hPreview: MSIHANDLE; szControlName: LPCWSTR;
  szBillboard: LPCWSTR): UINT; stdcall;
{$EXTERNALSYM MsiPreviewBillboardW}

{$IFDEF UNICODE}
function MsiPreviewBillboard(hPreview: MSIHANDLE; szControlName: LPCWSTR;
  szBillboard: LPCWSTR): UINT; stdcall;
{$EXTERNALSYM MsiPreviewBillboard}
{$ELSE}
function MsiPreviewBillboard(hPreview: MSIHANDLE; szControlName: LPCSTR;
  szBillboard: LPCSTR): UINT; stdcall;
{$EXTERNALSYM MsiPreviewBillboard}
{$ENDIF}

// --------------------------------------------------------------------------
// Error handling not associated with any particular object
// --------------------------------------------------------------------------

// Return a record handle to the last function that generated an error record
// Only specified functions will set the error record, or clear it if success
// Field 1 of the record will contain the internal MSI error code
// Other fields will contain data specific to the particular error
// The error record is released internally after this function is executed

function MsiGetLastErrorRecord: MSIHANDLE; stdcall;
{$EXTERNALSYM MsiGetLastErrorRecord}

implementation

const
  msilib = 'msi.dll';


{$IFDEF DYNAMIC_LINK}
var
  _MsiDatabaseOpenViewA: Pointer;

function MsiDatabaseOpenViewA;
begin
  GetProcedureAddress(_MsiDatabaseOpenViewA, msilib, 'MsiDatabaseOpenViewA');
  asm
    mov esp, ebp
    pop ebp
    jmp [_MsiDatabaseOpenViewA]
  end;
end;
{$ELSE}
function MsiDatabaseOpenViewA; external msilib name 'MsiDatabaseOpenViewA';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _MsiDatabaseOpenViewW: Pointer;

function MsiDatabaseOpenViewW;
begin
  GetProcedureAddress(_MsiDatabaseOpenViewW, msilib, 'MsiDatabaseOpenViewW');
  asm
    mov esp, ebp
    pop ebp
    jmp [_MsiDatabaseOpenViewW]
  end;
end;
{$ELSE}
function MsiDatabaseOpenViewW; external msilib name 'MsiDatabaseOpenViewW';
{$ENDIF DYNAMIC_LINK}
{$IFDEF UNICODE}

{$IFDEF DYNAMIC_LINK}
var
  _MsiDatabaseOpenView: Pointer;

function MsiDatabaseOpenView;
begin
  GetProcedureAddress(_MsiDatabaseOpenView, msilib, 'MsiDatabaseOpenViewW');
  asm
    mov esp, ebp
    pop ebp
    jmp [_MsiDatabaseOpenView]
  end;
end;
{$ELSE}
function MsiDatabaseOpenView; external msilib name 'MsiDatabaseOpenViewW';
{$ENDIF DYNAMIC_LINK}
{$ELSE}

{$IFDEF DYNAMIC_LINK}
var
  _MsiDatabaseOpenView: Pointer;

function MsiDatabaseOpenView;
begin
  GetProcedureAddress(_MsiDatabaseOpenView, msilib, 'MsiDatabaseOpenViewA');
  asm
    mov esp, ebp
    pop ebp
    jmp [_MsiDatabaseOpenView]
  end;
end;
{$ELSE}
function MsiDatabaseOpenView; external msilib name 'MsiDatabaseOpenViewA';
{$ENDIF DYNAMIC_LINK}
{$ENDIF}

{$IFDEF DYNAMIC_LINK}
var
  _MsiViewGetErrorA: Pointer;

function MsiViewGetErrorA;
begin
  GetProcedureAddress(_MsiViewGetErrorA, msilib, 'MsiViewGetErrorA');
  asm
    mov esp, ebp
    pop ebp
    jmp [_MsiViewGetErrorA]
  end;
end;
{$ELSE}
function MsiViewGetErrorA; external msilib name 'MsiViewGetErrorA';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _MsiViewGetErrorW: Pointer;

function MsiViewGetErrorW;
begin
  GetProcedureAddress(_MsiViewGetErrorW, msilib, 'MsiViewGetErrorW');
  asm
    mov esp, ebp
    pop ebp
    jmp [_MsiViewGetErrorW]
  end;
end;
{$ELSE}
function MsiViewGetErrorW; external msilib name 'MsiViewGetErrorW';
{$ENDIF DYNAMIC_LINK}
{$IFDEF UNICODE}

{$IFDEF DYNAMIC_LINK}
var
  _MsiViewGetError: Pointer;

function MsiViewGetError;
begin
  GetProcedureAddress(_MsiViewGetError, msilib, 'MsiViewGetErrorW');
  asm
    mov esp, ebp
    pop ebp
    jmp [_MsiViewGetError]
  end;
end;
{$ELSE}
function MsiViewGetError; external msilib name 'MsiViewGetErrorW';
{$ENDIF DYNAMIC_LINK}
{$ELSE}

{$IFDEF DYNAMIC_LINK}
var
  _MsiViewGetError: Pointer;

function MsiViewGetError;
begin
  GetProcedureAddress(_MsiViewGetError, msilib, 'MsiViewGetErrorA');
  asm
    mov esp, ebp
    pop ebp
    jmp [_MsiViewGetError]
  end;
end;
{$ELSE}
function MsiViewGetError; external msilib name 'MsiViewGetErrorA';
{$ENDIF DYNAMIC_LINK}
{$ENDIF}

{$IFDEF DYNAMIC_LINK}
var
  _MsiViewExecute: Pointer;

function MsiViewExecute;
begin
  GetProcedureAddress(_MsiViewExecute, msilib, 'MsiViewExecute');
  asm
    mov esp, ebp
    pop ebp
    jmp [_MsiViewExecute]
  end;
end;
{$ELSE}
function MsiViewExecute; external msilib name 'MsiViewExecute';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _MsiViewFetch: Pointer;

function MsiViewFetch;
begin
  GetProcedureAddress(_MsiViewFetch, msilib, 'MsiViewFetch');
  asm
    mov esp, ebp
    pop ebp
    jmp [_MsiViewFetch]
  end;
end;
{$ELSE}
function MsiViewFetch; external msilib name 'MsiViewFetch';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _MsiViewModify: Pointer;

function MsiViewModify;
begin
  GetProcedureAddress(_MsiViewModify, msilib, 'MsiViewModify');
  asm
    mov esp, ebp
    pop ebp
    jmp [_MsiViewModify]
  end;
end;
{$ELSE}
function MsiViewModify; external msilib name 'MsiViewModify';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _MsiViewGetColumnInfo: Pointer;

function MsiViewGetColumnInfo;
begin
  GetProcedureAddress(_MsiViewGetColumnInfo, msilib, 'MsiViewGetColumnInfo');
  asm
    mov esp, ebp
    pop ebp
    jmp [_MsiViewGetColumnInfo]
  end;
end;
{$ELSE}
function MsiViewGetColumnInfo; external msilib name 'MsiViewGetColumnInfo';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _MsiViewClose: Pointer;

function MsiViewClose;
begin
  GetProcedureAddress(_MsiViewClose, msilib, 'MsiViewClose');
  asm
    mov esp, ebp
    pop ebp
    jmp [_MsiViewClose]
  end;
end;
{$ELSE}
function MsiViewClose; external msilib name 'MsiViewClose';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _MsiDatabaseGetPrimaryKeysA: Pointer;

function MsiDatabaseGetPrimaryKeysA;
begin
  GetProcedureAddress(_MsiDatabaseGetPrimaryKeysA, msilib, 'MsiDatabaseGetPrimaryKeysA');
  asm
    mov esp, ebp
    pop ebp
    jmp [_MsiDatabaseGetPrimaryKeysA]
  end;
end;
{$ELSE}
function MsiDatabaseGetPrimaryKeysA; external msilib name 'MsiDatabaseGetPrimaryKeysA';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _MsiDatabaseGetPrimaryKeysW: Pointer;

function MsiDatabaseGetPrimaryKeysW;
begin
  GetProcedureAddress(_MsiDatabaseGetPrimaryKeysW, msilib, 'MsiDatabaseGetPrimaryKeysW');
  asm
    mov esp, ebp
    pop ebp
    jmp [_MsiDatabaseGetPrimaryKeysW]
  end;
end;
{$ELSE}
function MsiDatabaseGetPrimaryKeysW; external msilib name 'MsiDatabaseGetPrimaryKeysW';
{$ENDIF DYNAMIC_LINK}
{$IFDEF UNICODE}

{$IFDEF DYNAMIC_LINK}
var
  _MsiDatabaseGetPrimaryKeys: Pointer;

function MsiDatabaseGetPrimaryKeys;
begin
  GetProcedureAddress(_MsiDatabaseGetPrimaryKeys, msilib, 'MsiDatabaseGetPrimaryKeysW');
  asm
    mov esp, ebp
    pop ebp
    jmp [_MsiDatabaseGetPrimaryKeys]
  end;
end;
{$ELSE}
function MsiDatabaseGetPrimaryKeys; external msilib name 'MsiDatabaseGetPrimaryKeysW';
{$ENDIF DYNAMIC_LINK}
{$ELSE}

{$IFDEF DYNAMIC_LINK}
var
  _MsiDatabaseGetPrimaryKeys: Pointer;

function MsiDatabaseGetPrimaryKeys;
begin
  GetProcedureAddress(_MsiDatabaseGetPrimaryKeys, msilib, 'MsiDatabaseGetPrimaryKeysA');
  asm
    mov esp, ebp
    pop ebp
    jmp [_MsiDatabaseGetPrimaryKeys]
  end;
end;
{$ELSE}
function MsiDatabaseGetPrimaryKeys; external msilib name 'MsiDatabaseGetPrimaryKeysA';
{$ENDIF DYNAMIC_LINK}
{$ENDIF}

{$IFDEF DYNAMIC_LINK}
var
  _MsiDatabaseIsTablePersistentA: Pointer;

function MsiDatabaseIsTablePersistentA;
begin
  GetProcedureAddress(_MsiDatabaseIsTablePersistentA, msilib, 'MsiDatabaseIsTablePersistentA');
  asm
    mov esp, ebp
    pop ebp
    jmp [_MsiDatabaseIsTablePersistentA]
  end;
end;
{$ELSE}
function MsiDatabaseIsTablePersistentA; external msilib name 'MsiDatabaseIsTablePersistentA';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _MsiDatabaseIsTablePersistentW: Pointer;

function MsiDatabaseIsTablePersistentW;
begin
  GetProcedureAddress(_MsiDatabaseIsTablePersistentW, msilib, 'MsiDatabaseIsTablePersistentW');
  asm
    mov esp, ebp
    pop ebp
    jmp [_MsiDatabaseIsTablePersistentW]
  end;
end;
{$ELSE}
function MsiDatabaseIsTablePersistentW; external msilib name 'MsiDatabaseIsTablePersistentW';
{$ENDIF DYNAMIC_LINK}
{$IFDEF UNICODE}

{$IFDEF DYNAMIC_LINK}
var
  _MsiDatabaseIsTablePersistent: Pointer;

function MsiDatabaseIsTablePersistent;
begin
  GetProcedureAddress(_MsiDatabaseIsTablePersistent, msilib, 'MsiDatabaseIsTablePersistentW');
  asm
    mov esp, ebp
    pop ebp
    jmp [_MsiDatabaseIsTablePersistent]
  end;
end;
{$ELSE}
function MsiDatabaseIsTablePersistent; external msilib name 'MsiDatabaseIsTablePersistentW';
{$ENDIF DYNAMIC_LINK}
{$ELSE}

{$IFDEF DYNAMIC_LINK}
var
  _MsiDatabaseIsTablePersistent: Pointer;

function MsiDatabaseIsTablePersistent;
begin
  GetProcedureAddress(_MsiDatabaseIsTablePersistent, msilib, 'MsiDatabaseIsTablePersistentA');
  asm
    mov esp, ebp
    pop ebp
    jmp [_MsiDatabaseIsTablePersistent]
  end;
end;
{$ELSE}
function MsiDatabaseIsTablePersistent; external msilib name 'MsiDatabaseIsTablePersistentA';
{$ENDIF DYNAMIC_LINK}
{$ENDIF}

{$IFDEF DYNAMIC_LINK}
var
  _MsiGetSummaryInformationA: Pointer;

function MsiGetSummaryInformationA;
begin
  GetProcedureAddress(_MsiGetSummaryInformationA, msilib, 'MsiGetSummaryInformationA');
  asm
    mov esp, ebp
    pop ebp
    jmp [_MsiGetSummaryInformationA]
  end;
end;
{$ELSE}
function MsiGetSummaryInformationA; external msilib name 'MsiGetSummaryInformationA';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _MsiGetSummaryInformationW: Pointer;

function MsiGetSummaryInformationW;
begin
  GetProcedureAddress(_MsiGetSummaryInformationW, msilib, 'MsiGetSummaryInformationW');
  asm
    mov esp, ebp
    pop ebp
    jmp [_MsiGetSummaryInformationW]
  end;
end;
{$ELSE}
function MsiGetSummaryInformationW; external msilib name 'MsiGetSummaryInformationW';
{$ENDIF DYNAMIC_LINK}
{$IFDEF UNICODE}

{$IFDEF DYNAMIC_LINK}
var
  _MsiGetSummaryInformation: Pointer;

function MsiGetSummaryInformation;
begin
  GetProcedureAddress(_MsiGetSummaryInformation, msilib, 'MsiGetSummaryInformationW');
  asm
    mov esp, ebp
    pop ebp
    jmp [_MsiGetSummaryInformation]
  end;
end;
{$ELSE}
function MsiGetSummaryInformation; external msilib name 'MsiGetSummaryInformationW';
{$ENDIF DYNAMIC_LINK}
{$ELSE}

{$IFDEF DYNAMIC_LINK}
var
  _MsiGetSummaryInformation: Pointer;

function MsiGetSummaryInformation;
begin
  GetProcedureAddress(_MsiGetSummaryInformation, msilib, 'MsiGetSummaryInformationA');
  asm
    mov esp, ebp
    pop ebp
    jmp [_MsiGetSummaryInformation]
  end;
end;
{$ELSE}
function MsiGetSummaryInformation; external msilib name 'MsiGetSummaryInformationA';
{$ENDIF DYNAMIC_LINK}
{$ENDIF}

{$IFDEF DYNAMIC_LINK}
var
  _MsiSummaryInfoGetPropertyCount: Pointer;

function MsiSummaryInfoGetPropertyCount;
begin
  GetProcedureAddress(_MsiSummaryInfoGetPropertyCount, msilib, 'MsiSummaryInfoGetPropertyCount');
  asm
    mov esp, ebp
    pop ebp
    jmp [_MsiSummaryInfoGetPropertyCount]
  end;
end;
{$ELSE}
function MsiSummaryInfoGetPropertyCount; external msilib name 'MsiSummaryInfoGetPropertyCount';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _MsiSummaryInfoSetPropertyA: Pointer;

function MsiSummaryInfoSetPropertyA;
begin
  GetProcedureAddress(_MsiSummaryInfoSetPropertyA, msilib, 'MsiSummaryInfoSetPropertyA');
  asm
    mov esp, ebp
    pop ebp
    jmp [_MsiSummaryInfoSetPropertyA]
  end;
end;
{$ELSE}
function MsiSummaryInfoSetPropertyA; external msilib name 'MsiSummaryInfoSetPropertyA';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _MsiSummaryInfoSetPropertyW: Pointer;

function MsiSummaryInfoSetPropertyW;
begin
  GetProcedureAddress(_MsiSummaryInfoSetPropertyW, msilib, 'MsiSummaryInfoSetPropertyW');
  asm
    mov esp, ebp
    pop ebp
    jmp [_MsiSummaryInfoSetPropertyW]
  end;
end;
{$ELSE}
function MsiSummaryInfoSetPropertyW; external msilib name 'MsiSummaryInfoSetPropertyW';
{$ENDIF DYNAMIC_LINK}
{$IFDEF UNICODE}

{$IFDEF DYNAMIC_LINK}
var
  _MsiSummaryInfoSetProperty: Pointer;

function MsiSummaryInfoSetProperty;
begin
  GetProcedureAddress(_MsiSummaryInfoSetProperty, msilib, 'MsiSummaryInfoSetPropertyW');
  asm
    mov esp, ebp
    pop ebp
    jmp [_MsiSummaryInfoSetProperty]
  end;
end;
{$ELSE}
function MsiSummaryInfoSetProperty; external msilib name 'MsiSummaryInfoSetPropertyW';
{$ENDIF DYNAMIC_LINK}
{$ELSE}

{$IFDEF DYNAMIC_LINK}
var
  _MsiSummaryInfoSetProperty: Pointer;

function MsiSummaryInfoSetProperty;
begin
  GetProcedureAddress(_MsiSummaryInfoSetProperty, msilib, 'MsiSummaryInfoSetPropertyA');
  asm
    mov esp, ebp
    pop ebp
    jmp [_MsiSummaryInfoSetProperty]
  end;
end;
{$ELSE}
function MsiSummaryInfoSetProperty; external msilib name 'MsiSummaryInfoSetPropertyA';
{$ENDIF DYNAMIC_LINK}
{$ENDIF}

{$IFDEF DYNAMIC_LINK}
var
  _MsiSummaryInfoGetPropertyA: Pointer;

function MsiSummaryInfoGetPropertyA;
begin
  GetProcedureAddress(_MsiSummaryInfoGetPropertyA, msilib, 'MsiSummaryInfoGetPropertyA');
  asm
    mov esp, ebp
    pop ebp
    jmp [_MsiSummaryInfoGetPropertyA]
  end;
end;
{$ELSE}
function MsiSummaryInfoGetPropertyA; external msilib name 'MsiSummaryInfoGetPropertyA';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _MsiSummaryInfoGetPropertyW: Pointer;

function MsiSummaryInfoGetPropertyW;
begin
  GetProcedureAddress(_MsiSummaryInfoGetPropertyW, msilib, 'MsiSummaryInfoGetPropertyW');
  asm
    mov esp, ebp
    pop ebp
    jmp [_MsiSummaryInfoGetPropertyW]
  end;
end;
{$ELSE}
function MsiSummaryInfoGetPropertyW; external msilib name 'MsiSummaryInfoGetPropertyW';
{$ENDIF DYNAMIC_LINK}
{$IFDEF UNICODE}

{$IFDEF DYNAMIC_LINK}
var
  _MsiSummaryInfoGetProperty: Pointer;

function MsiSummaryInfoGetProperty;
begin
  GetProcedureAddress(_MsiSummaryInfoGetProperty, msilib, 'MsiSummaryInfoGetPropertyW');
  asm
    mov esp, ebp
    pop ebp
    jmp [_MsiSummaryInfoGetProperty]
  end;
end;
{$ELSE}
function MsiSummaryInfoGetProperty; external msilib name 'MsiSummaryInfoGetPropertyW';
{$ENDIF DYNAMIC_LINK}
{$ELSE}

{$IFDEF DYNAMIC_LINK}
var
  _MsiSummaryInfoGetProperty: Pointer;

function MsiSummaryInfoGetProperty;
begin
  GetProcedureAddress(_MsiSummaryInfoGetProperty, msilib, 'MsiSummaryInfoGetPropertyA');
  asm
    mov esp, ebp
    pop ebp
    jmp [_MsiSummaryInfoGetProperty]
  end;
end;
{$ELSE}
function MsiSummaryInfoGetProperty; external msilib name 'MsiSummaryInfoGetPropertyA';
{$ENDIF DYNAMIC_LINK}
{$ENDIF}

{$IFDEF DYNAMIC_LINK}
var
  _MsiSummaryInfoPersist: Pointer;

function MsiSummaryInfoPersist;
begin
  GetProcedureAddress(_MsiSummaryInfoPersist, msilib, 'MsiSummaryInfoPersist');
  asm
    mov esp, ebp
    pop ebp
    jmp [_MsiSummaryInfoPersist]
  end;
end;
{$ELSE}
function MsiSummaryInfoPersist; external msilib name 'MsiSummaryInfoPersist';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _MsiOpenDatabaseA: Pointer;

function MsiOpenDatabaseA;
begin
  GetProcedureAddress(_MsiOpenDatabaseA, msilib, 'MsiOpenDatabaseA');
  asm
    mov esp, ebp
    pop ebp
    jmp [_MsiOpenDatabaseA]
  end;
end;
{$ELSE}
function MsiOpenDatabaseA; external msilib name 'MsiOpenDatabaseA';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _MsiOpenDatabaseW: Pointer;

function MsiOpenDatabaseW;
begin
  GetProcedureAddress(_MsiOpenDatabaseW, msilib, 'MsiOpenDatabaseW');
  asm
    mov esp, ebp
    pop ebp
    jmp [_MsiOpenDatabaseW]
  end;
end;
{$ELSE}
function MsiOpenDatabaseW; external msilib name 'MsiOpenDatabaseW';
{$ENDIF DYNAMIC_LINK}
{$IFDEF UNICODE}

{$IFDEF DYNAMIC_LINK}
var
  _MsiOpenDatabase: Pointer;

function MsiOpenDatabase;
begin
  GetProcedureAddress(_MsiOpenDatabase, msilib, 'MsiOpenDatabaseW');
  asm
    mov esp, ebp
    pop ebp
    jmp [_MsiOpenDatabase]
  end;
end;
{$ELSE}
function MsiOpenDatabase; external msilib name 'MsiOpenDatabaseW';
{$ENDIF DYNAMIC_LINK}
{$ELSE}

{$IFDEF DYNAMIC_LINK}
var
  _MsiOpenDatabase: Pointer;

function MsiOpenDatabase;
begin
  GetProcedureAddress(_MsiOpenDatabase, msilib, 'MsiOpenDatabaseA');
  asm
    mov esp, ebp
    pop ebp
    jmp [_MsiOpenDatabase]
  end;
end;
{$ELSE}
function MsiOpenDatabase; external msilib name 'MsiOpenDatabaseA';
{$ENDIF DYNAMIC_LINK}
{$ENDIF}

{$IFDEF DYNAMIC_LINK}
var
  _MsiDatabaseImportA: Pointer;

function MsiDatabaseImportA;
begin
  GetProcedureAddress(_MsiDatabaseImportA, msilib, 'MsiDatabaseImportA');
  asm
    mov esp, ebp
    pop ebp
    jmp [_MsiDatabaseImportA]
  end;
end;
{$ELSE}
function MsiDatabaseImportA; external msilib name 'MsiDatabaseImportA';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _MsiDatabaseImportW: Pointer;

function MsiDatabaseImportW;
begin
  GetProcedureAddress(_MsiDatabaseImportW, msilib, 'MsiDatabaseImportW');
  asm
    mov esp, ebp
    pop ebp
    jmp [_MsiDatabaseImportW]
  end;
end;
{$ELSE}
function MsiDatabaseImportW; external msilib name 'MsiDatabaseImportW';
{$ENDIF DYNAMIC_LINK}
{$IFDEF UNICODE}

{$IFDEF DYNAMIC_LINK}
var
  _MsiDatabaseImport: Pointer;

function MsiDatabaseImport;
begin
  GetProcedureAddress(_MsiDatabaseImport, msilib, 'MsiDatabaseImportW');
  asm
    mov esp, ebp
    pop ebp
    jmp [_MsiDatabaseImport]
  end;
end;
{$ELSE}
function MsiDatabaseImport; external msilib name 'MsiDatabaseImportW';
{$ENDIF DYNAMIC_LINK}
{$ELSE}

{$IFDEF DYNAMIC_LINK}
var
  _MsiDatabaseImport: Pointer;

function MsiDatabaseImport;
begin
  GetProcedureAddress(_MsiDatabaseImport, msilib, 'MsiDatabaseImportA');
  asm
    mov esp, ebp
    pop ebp
    jmp [_MsiDatabaseImport]
  end;
end;
{$ELSE}
function MsiDatabaseImport; external msilib name 'MsiDatabaseImportA';
{$ENDIF DYNAMIC_LINK}
{$ENDIF}

{$IFDEF DYNAMIC_LINK}
var
  _MsiDatabaseExportA: Pointer;

function MsiDatabaseExportA;
begin
  GetProcedureAddress(_MsiDatabaseExportA, msilib, 'MsiDatabaseExportA');
  asm
    mov esp, ebp
    pop ebp
    jmp [_MsiDatabaseExportA]
  end;
end;
{$ELSE}
function MsiDatabaseExportA; external msilib name 'MsiDatabaseExportA';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _MsiDatabaseExportW: Pointer;

function MsiDatabaseExportW;
begin
  GetProcedureAddress(_MsiDatabaseExportW, msilib, 'MsiDatabaseExportW');
  asm
    mov esp, ebp
    pop ebp
    jmp [_MsiDatabaseExportW]
  end;
end;
{$ELSE}
function MsiDatabaseExportW; external msilib name 'MsiDatabaseExportW';
{$ENDIF DYNAMIC_LINK}
{$IFDEF UNICODE}

{$IFDEF DYNAMIC_LINK}
var
  _MsiDatabaseExport: Pointer;

function MsiDatabaseExport;
begin
  GetProcedureAddress(_MsiDatabaseExport, msilib, 'MsiDatabaseExportW');
  asm
    mov esp, ebp
    pop ebp
    jmp [_MsiDatabaseExport]
  end;
end;
{$ELSE}
function MsiDatabaseExport; external msilib name 'MsiDatabaseExportW';
{$ENDIF DYNAMIC_LINK}
{$ELSE}

{$IFDEF DYNAMIC_LINK}
var
  _MsiDatabaseExport: Pointer;

function MsiDatabaseExport;
begin
  GetProcedureAddress(_MsiDatabaseExport, msilib, 'MsiDatabaseExportA');
  asm
    mov esp, ebp
    pop ebp
    jmp [_MsiDatabaseExport]
  end;
end;
{$ELSE}
function MsiDatabaseExport; external msilib name 'MsiDatabaseExportA';
{$ENDIF DYNAMIC_LINK}
{$ENDIF}

{$IFDEF DYNAMIC_LINK}
var
  _MsiDatabaseMergeA: Pointer;

function MsiDatabaseMergeA;
begin
  GetProcedureAddress(_MsiDatabaseMergeA, msilib, 'MsiDatabaseMergeA');
  asm
    mov esp, ebp
    pop ebp
    jmp [_MsiDatabaseMergeA]
  end;
end;
{$ELSE}
function MsiDatabaseMergeA; external msilib name 'MsiDatabaseMergeA';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _MsiDatabaseMergeW: Pointer;

function MsiDatabaseMergeW;
begin
  GetProcedureAddress(_MsiDatabaseMergeW, msilib, 'MsiDatabaseMergeW');
  asm
    mov esp, ebp
    pop ebp
    jmp [_MsiDatabaseMergeW]
  end;
end;
{$ELSE}
function MsiDatabaseMergeW; external msilib name 'MsiDatabaseMergeW';
{$ENDIF DYNAMIC_LINK}
{$IFDEF UNICODE}

{$IFDEF DYNAMIC_LINK}
var
  _MsiDatabaseMerge: Pointer;

function MsiDatabaseMerge;
begin
  GetProcedureAddress(_MsiDatabaseMerge, msilib, 'MsiDatabaseMergeW');
  asm
    mov esp, ebp
    pop ebp
    jmp [_MsiDatabaseMerge]
  end;
end;
{$ELSE}
function MsiDatabaseMerge; external msilib name 'MsiDatabaseMergeW';
{$ENDIF DYNAMIC_LINK}
{$ELSE}

{$IFDEF DYNAMIC_LINK}
var
  _MsiDatabaseMerge: Pointer;

function MsiDatabaseMerge;
begin
  GetProcedureAddress(_MsiDatabaseMerge, msilib, 'MsiDatabaseMergeA');
  asm
    mov esp, ebp
    pop ebp
    jmp [_MsiDatabaseMerge]
  end;
end;
{$ELSE}
function MsiDatabaseMerge; external msilib name 'MsiDatabaseMergeA';
{$ENDIF DYNAMIC_LINK}
{$ENDIF}

{$IFDEF DYNAMIC_LINK}
var
  _MsiDatabaseGenerateTransformA: Pointer;

function MsiDatabaseGenerateTransformA;
begin
  GetProcedureAddress(_MsiDatabaseGenerateTransformA, msilib, 'MsiDatabaseGenerateTransformA');
  asm
    mov esp, ebp
    pop ebp
    jmp [_MsiDatabaseGenerateTransformA]
  end;
end;
{$ELSE}
function MsiDatabaseGenerateTransformA; external msilib name 'MsiDatabaseGenerateTransformA';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _MsiDatabaseGenerateTransformW: Pointer;

function MsiDatabaseGenerateTransformW;
begin
  GetProcedureAddress(_MsiDatabaseGenerateTransformW, msilib, 'MsiDatabaseGenerateTransformW');
  asm
    mov esp, ebp
    pop ebp
    jmp [_MsiDatabaseGenerateTransformW]
  end;
end;
{$ELSE}
function MsiDatabaseGenerateTransformW; external msilib name 'MsiDatabaseGenerateTransformW';
{$ENDIF DYNAMIC_LINK}
{$IFDEF UNICODE}

{$IFDEF DYNAMIC_LINK}
var
  _MsiDatabaseGenerateTransform: Pointer;

function MsiDatabaseGenerateTransform;
begin
  GetProcedureAddress(_MsiDatabaseGenerateTransform, msilib, 'MsiDatabaseGenerateTransformW');
  asm
    mov esp, ebp
    pop ebp
    jmp [_MsiDatabaseGenerateTransform]
  end;
end;
{$ELSE}
function MsiDatabaseGenerateTransform; external msilib name 'MsiDatabaseGenerateTransformW';
{$ENDIF DYNAMIC_LINK}
{$ELSE}

{$IFDEF DYNAMIC_LINK}
var
  _MsiDatabaseGenerateTransform: Pointer;

function MsiDatabaseGenerateTransform;
begin
  GetProcedureAddress(_MsiDatabaseGenerateTransform, msilib, 'MsiDatabaseGenerateTransformA');
  asm
    mov esp, ebp
    pop ebp
    jmp [_MsiDatabaseGenerateTransform]
  end;
end;
{$ELSE}
function MsiDatabaseGenerateTransform; external msilib name 'MsiDatabaseGenerateTransformA';
{$ENDIF DYNAMIC_LINK}
{$ENDIF}

{$IFDEF DYNAMIC_LINK}
var
  _MsiDatabaseApplyTransformA: Pointer;

function MsiDatabaseApplyTransformA;
begin
  GetProcedureAddress(_MsiDatabaseApplyTransformA, msilib, 'MsiDatabaseApplyTransformA');
  asm
    mov esp, ebp
    pop ebp
    jmp [_MsiDatabaseApplyTransformA]
  end;
end;
{$ELSE}
function MsiDatabaseApplyTransformA; external msilib name 'MsiDatabaseApplyTransformA';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _MsiDatabaseApplyTransformW: Pointer;

function MsiDatabaseApplyTransformW;
begin
  GetProcedureAddress(_MsiDatabaseApplyTransformW, msilib, 'MsiDatabaseApplyTransformW');
  asm
    mov esp, ebp
    pop ebp
    jmp [_MsiDatabaseApplyTransformW]
  end;
end;
{$ELSE}
function MsiDatabaseApplyTransformW; external msilib name 'MsiDatabaseApplyTransformW';
{$ENDIF DYNAMIC_LINK}
{$IFDEF UNICODE}

{$IFDEF DYNAMIC_LINK}
var
  _MsiDatabaseApplyTransform: Pointer;

function MsiDatabaseApplyTransform;
begin
  GetProcedureAddress(_MsiDatabaseApplyTransform, msilib, 'MsiDatabaseApplyTransformW');
  asm
    mov esp, ebp
    pop ebp
    jmp [_MsiDatabaseApplyTransform]
  end;
end;
{$ELSE}
function MsiDatabaseApplyTransform; external msilib name 'MsiDatabaseApplyTransformW';
{$ENDIF DYNAMIC_LINK}
{$ELSE}

{$IFDEF DYNAMIC_LINK}
var
  _MsiDatabaseApplyTransform: Pointer;

function MsiDatabaseApplyTransform;
begin
  GetProcedureAddress(_MsiDatabaseApplyTransform, msilib, 'MsiDatabaseApplyTransformA');
  asm
    mov esp, ebp
    pop ebp
    jmp [_MsiDatabaseApplyTransform]
  end;
end;
{$ELSE}
function MsiDatabaseApplyTransform; external msilib name 'MsiDatabaseApplyTransformA';
{$ENDIF DYNAMIC_LINK}
{$ENDIF}

{$IFDEF DYNAMIC_LINK}
var
  _MsiCreateTransformSummaryInfoA: Pointer;

function MsiCreateTransformSummaryInfoA;
begin
  GetProcedureAddress(_MsiCreateTransformSummaryInfoA, msilib, 'MsiCreateTransformSummaryInfoA');
  asm
    mov esp, ebp
    pop ebp
    jmp [_MsiCreateTransformSummaryInfoA]
  end;
end;
{$ELSE}
function MsiCreateTransformSummaryInfoA; external msilib name 'MsiCreateTransformSummaryInfoA';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _MsiCreateTransformSummaryInfoW: Pointer;

function MsiCreateTransformSummaryInfoW;
begin
  GetProcedureAddress(_MsiCreateTransformSummaryInfoW, msilib, 'MsiCreateTransformSummaryInfoW');
  asm
    mov esp, ebp
    pop ebp
    jmp [_MsiCreateTransformSummaryInfoW]
  end;
end;
{$ELSE}
function MsiCreateTransformSummaryInfoW; external msilib name 'MsiCreateTransformSummaryInfoW';
{$ENDIF DYNAMIC_LINK}
{$IFDEF UNICODE}

{$IFDEF DYNAMIC_LINK}
var
  _MsiCreateTransformSummaryInfo: Pointer;

function MsiCreateTransformSummaryInfo;
begin
  GetProcedureAddress(_MsiCreateTransformSummaryInfo, msilib, 'MsiCreateTransformSummaryInfoW');
  asm
    mov esp, ebp
    pop ebp
    jmp [_MsiCreateTransformSummaryInfo]
  end;
end;
{$ELSE}
function MsiCreateTransformSummaryInfo; external msilib name 'MsiCreateTransformSummaryInfoW';
{$ENDIF DYNAMIC_LINK}
{$ELSE}

{$IFDEF DYNAMIC_LINK}
var
  _MsiCreateTransformSummaryInfo: Pointer;

function MsiCreateTransformSummaryInfo;
begin
  GetProcedureAddress(_MsiCreateTransformSummaryInfo, msilib, 'MsiCreateTransformSummaryInfoA');
  asm
    mov esp, ebp
    pop ebp
    jmp [_MsiCreateTransformSummaryInfo]
  end;
end;
{$ELSE}
function MsiCreateTransformSummaryInfo; external msilib name 'MsiCreateTransformSummaryInfoA';
{$ENDIF DYNAMIC_LINK}
{$ENDIF}

{$IFDEF DYNAMIC_LINK}
var
  _MsiDatabaseCommit: Pointer;

function MsiDatabaseCommit;
begin
  GetProcedureAddress(_MsiDatabaseCommit, msilib, 'MsiDatabaseCommit');
  asm
    mov esp, ebp
    pop ebp
    jmp [_MsiDatabaseCommit]
  end;
end;
{$ELSE}
function MsiDatabaseCommit; external msilib name 'MsiDatabaseCommit';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _MsiGetDatabaseState: Pointer;

function MsiGetDatabaseState;
begin
  GetProcedureAddress(_MsiGetDatabaseState, msilib, 'MsiGetDatabaseState');
  asm
    mov esp, ebp
    pop ebp
    jmp [_MsiGetDatabaseState]
  end;
end;
{$ELSE}
function MsiGetDatabaseState; external msilib name 'MsiGetDatabaseState';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _MsiCreateRecord: Pointer;

function MsiCreateRecord;
begin
  GetProcedureAddress(_MsiCreateRecord, msilib, 'MsiCreateRecord');
  asm
    mov esp, ebp
    pop ebp
    jmp [_MsiCreateRecord]
  end;
end;
{$ELSE}
function MsiCreateRecord; external msilib name 'MsiCreateRecord';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _MsiRecordIsNull: Pointer;

function MsiRecordIsNull;
begin
  GetProcedureAddress(_MsiRecordIsNull, msilib, 'MsiRecordIsNull');
  asm
    mov esp, ebp
    pop ebp
    jmp [_MsiRecordIsNull]
  end;
end;
{$ELSE}
function MsiRecordIsNull; external msilib name 'MsiRecordIsNull';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _MsiRecordDataSize: Pointer;

function MsiRecordDataSize;
begin
  GetProcedureAddress(_MsiRecordDataSize, msilib, 'MsiRecordDataSize');
  asm
    mov esp, ebp
    pop ebp
    jmp [_MsiRecordDataSize]
  end;
end;
{$ELSE}
function MsiRecordDataSize; external msilib name 'MsiRecordDataSize';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _MsiRecordSetInteger: Pointer;

function MsiRecordSetInteger;
begin
  GetProcedureAddress(_MsiRecordSetInteger, msilib, 'MsiRecordSetInteger');
  asm
    mov esp, ebp
    pop ebp
    jmp [_MsiRecordSetInteger]
  end;
end;
{$ELSE}
function MsiRecordSetInteger; external msilib name 'MsiRecordSetInteger';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _MsiRecordSetStringA: Pointer;

function MsiRecordSetStringA;
begin
  GetProcedureAddress(_MsiRecordSetStringA, msilib, 'MsiRecordSetStringA');
  asm
    mov esp, ebp
    pop ebp
    jmp [_MsiRecordSetStringA]
  end;
end;
{$ELSE}
function MsiRecordSetStringA; external msilib name 'MsiRecordSetStringA';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _MsiRecordSetStringW: Pointer;

function MsiRecordSetStringW;
begin
  GetProcedureAddress(_MsiRecordSetStringW, msilib, 'MsiRecordSetStringW');
  asm
    mov esp, ebp
    pop ebp
    jmp [_MsiRecordSetStringW]
  end;
end;
{$ELSE}
function MsiRecordSetStringW; external msilib name 'MsiRecordSetStringW';
{$ENDIF DYNAMIC_LINK}
{$IFDEF UNICODE}

{$IFDEF DYNAMIC_LINK}
var
  _MsiRecordSetString: Pointer;

function MsiRecordSetString;
begin
  GetProcedureAddress(_MsiRecordSetString, msilib, 'MsiRecordSetStringW');
  asm
    mov esp, ebp
    pop ebp
    jmp [_MsiRecordSetString]
  end;
end;
{$ELSE}
function MsiRecordSetString; external msilib name 'MsiRecordSetStringW';
{$ENDIF DYNAMIC_LINK}
{$ELSE}

{$IFDEF DYNAMIC_LINK}
var
  _MsiRecordSetString: Pointer;

function MsiRecordSetString;
begin
  GetProcedureAddress(_MsiRecordSetString, msilib, 'MsiRecordSetStringA');
  asm
    mov esp, ebp
    pop ebp
    jmp [_MsiRecordSetString]
  end;
end;
{$ELSE}
function MsiRecordSetString; external msilib name 'MsiRecordSetStringA';
{$ENDIF DYNAMIC_LINK}
{$ENDIF}

{$IFDEF DYNAMIC_LINK}
var
  _MsiRecordGetInteger: Pointer;

function MsiRecordGetInteger;
begin
  GetProcedureAddress(_MsiRecordGetInteger, msilib, 'MsiRecordGetInteger');
  asm
    mov esp, ebp
    pop ebp
    jmp [_MsiRecordGetInteger]
  end;
end;
{$ELSE}
function MsiRecordGetInteger; external msilib name 'MsiRecordGetInteger';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _MsiRecordGetStringA: Pointer;

function MsiRecordGetStringA;
begin
  GetProcedureAddress(_MsiRecordGetStringA, msilib, 'MsiRecordGetStringA');
  asm
    mov esp, ebp
    pop ebp
    jmp [_MsiRecordGetStringA]
  end;
end;
{$ELSE}
function MsiRecordGetStringA; external msilib name 'MsiRecordGetStringA';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _MsiRecordGetStringW: Pointer;

function MsiRecordGetStringW;
begin
  GetProcedureAddress(_MsiRecordGetStringW, msilib, 'MsiRecordGetStringW');
  asm
    mov esp, ebp
    pop ebp
    jmp [_MsiRecordGetStringW]
  end;
end;
{$ELSE}
function MsiRecordGetStringW; external msilib name 'MsiRecordGetStringW';
{$ENDIF DYNAMIC_LINK}
{$IFDEF UNICODE}

{$IFDEF DYNAMIC_LINK}
var
  _MsiRecordGetString: Pointer;

function MsiRecordGetString;
begin
  GetProcedureAddress(_MsiRecordGetString, msilib, 'MsiRecordGetStringW');
  asm
    mov esp, ebp
    pop ebp
    jmp [_MsiRecordGetString]
  end;
end;
{$ELSE}
function MsiRecordGetString; external msilib name 'MsiRecordGetStringW';
{$ENDIF DYNAMIC_LINK}
{$ELSE}

{$IFDEF DYNAMIC_LINK}
var
  _MsiRecordGetString: Pointer;

function MsiRecordGetString;
begin
  GetProcedureAddress(_MsiRecordGetString, msilib, 'MsiRecordGetStringA');
  asm
    mov esp, ebp
    pop ebp
    jmp [_MsiRecordGetString]
  end;
end;
{$ELSE}
function MsiRecordGetString; external msilib name 'MsiRecordGetStringA';
{$ENDIF DYNAMIC_LINK}
{$ENDIF}

{$IFDEF DYNAMIC_LINK}
var
  _MsiRecordGetFieldCount: Pointer;

function MsiRecordGetFieldCount;
begin
  GetProcedureAddress(_MsiRecordGetFieldCount, msilib, 'MsiRecordGetFieldCount');
  asm
    mov esp, ebp
    pop ebp
    jmp [_MsiRecordGetFieldCount]
  end;
end;
{$ELSE}
function MsiRecordGetFieldCount; external msilib name 'MsiRecordGetFieldCount';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _MsiRecordSetStreamA: Pointer;

function MsiRecordSetStreamA;
begin
  GetProcedureAddress(_MsiRecordSetStreamA, msilib, 'MsiRecordSetStreamA');
  asm
    mov esp, ebp
    pop ebp
    jmp [_MsiRecordSetStreamA]
  end;
end;
{$ELSE}
function MsiRecordSetStreamA; external msilib name 'MsiRecordSetStreamA';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _MsiRecordSetStreamW: Pointer;

function MsiRecordSetStreamW;
begin
  GetProcedureAddress(_MsiRecordSetStreamW, msilib, 'MsiRecordSetStreamW');
  asm
    mov esp, ebp
    pop ebp
    jmp [_MsiRecordSetStreamW]
  end;
end;
{$ELSE}
function MsiRecordSetStreamW; external msilib name 'MsiRecordSetStreamW';
{$ENDIF DYNAMIC_LINK}
{$IFDEF UNICODE}

{$IFDEF DYNAMIC_LINK}
var
  _MsiRecordSetStream: Pointer;

function MsiRecordSetStream;
begin
  GetProcedureAddress(_MsiRecordSetStream, msilib, 'MsiRecordSetStreamW');
  asm
    mov esp, ebp
    pop ebp
    jmp [_MsiRecordSetStream]
  end;
end;
{$ELSE}
function MsiRecordSetStream; external msilib name 'MsiRecordSetStreamW';
{$ENDIF DYNAMIC_LINK}
{$ELSE}

{$IFDEF DYNAMIC_LINK}
var
  _MsiRecordSetStream: Pointer;

function MsiRecordSetStream;
begin
  GetProcedureAddress(_MsiRecordSetStream, msilib, 'MsiRecordSetStreamA');
  asm
    mov esp, ebp
    pop ebp
    jmp [_MsiRecordSetStream]
  end;
end;
{$ELSE}
function MsiRecordSetStream; external msilib name 'MsiRecordSetStreamA';
{$ENDIF DYNAMIC_LINK}
{$ENDIF}

{$IFDEF DYNAMIC_LINK}
var
  _MsiRecordReadStream: Pointer;

function MsiRecordReadStream;
begin
  GetProcedureAddress(_MsiRecordReadStream, msilib, 'MsiRecordReadStream');
  asm
    mov esp, ebp
    pop ebp
    jmp [_MsiRecordReadStream]
  end;
end;
{$ELSE}
function MsiRecordReadStream; external msilib name 'MsiRecordReadStream';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _MsiRecordClearData: Pointer;

function MsiRecordClearData;
begin
  GetProcedureAddress(_MsiRecordClearData, msilib, 'MsiRecordClearData');
  asm
    mov esp, ebp
    pop ebp
    jmp [_MsiRecordClearData]
  end;
end;
{$ELSE}
function MsiRecordClearData; external msilib name 'MsiRecordClearData';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _MsiGetActiveDatabase: Pointer;

function MsiGetActiveDatabase;
begin
  GetProcedureAddress(_MsiGetActiveDatabase, msilib, 'MsiGetActiveDatabase');
  asm
    mov esp, ebp
    pop ebp
    jmp [_MsiGetActiveDatabase]
  end;
end;
{$ELSE}
function MsiGetActiveDatabase; external msilib name 'MsiGetActiveDatabase';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _MsiSetPropertyA: Pointer;

function MsiSetPropertyA;
begin
  GetProcedureAddress(_MsiSetPropertyA, msilib, 'MsiSetPropertyA');
  asm
    mov esp, ebp
    pop ebp
    jmp [_MsiSetPropertyA]
  end;
end;
{$ELSE}
function MsiSetPropertyA; external msilib name 'MsiSetPropertyA';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _MsiSetPropertyW: Pointer;

function MsiSetPropertyW;
begin
  GetProcedureAddress(_MsiSetPropertyW, msilib, 'MsiSetPropertyW');
  asm
    mov esp, ebp
    pop ebp
    jmp [_MsiSetPropertyW]
  end;
end;
{$ELSE}
function MsiSetPropertyW; external msilib name 'MsiSetPropertyW';
{$ENDIF DYNAMIC_LINK}
{$IFDEF UNICODE}

{$IFDEF DYNAMIC_LINK}
var
  _MsiSetProperty: Pointer;

function MsiSetProperty;
begin
  GetProcedureAddress(_MsiSetProperty, msilib, 'MsiSetPropertyW');
  asm
    mov esp, ebp
    pop ebp
    jmp [_MsiSetProperty]
  end;
end;
{$ELSE}
function MsiSetProperty; external msilib name 'MsiSetPropertyW';
{$ENDIF DYNAMIC_LINK}
{$ELSE}

{$IFDEF DYNAMIC_LINK}
var
  _MsiSetProperty: Pointer;

function MsiSetProperty;
begin
  GetProcedureAddress(_MsiSetProperty, msilib, 'MsiSetPropertyA');
  asm
    mov esp, ebp
    pop ebp
    jmp [_MsiSetProperty]
  end;
end;
{$ELSE}
function MsiSetProperty; external msilib name 'MsiSetPropertyA';
{$ENDIF DYNAMIC_LINK}
{$ENDIF}

{$IFDEF DYNAMIC_LINK}
var
  _MsiGetPropertyA: Pointer;

function MsiGetPropertyA;
begin
  GetProcedureAddress(_MsiGetPropertyA, msilib, 'MsiGetPropertyA');
  asm
    mov esp, ebp
    pop ebp
    jmp [_MsiGetPropertyA]
  end;
end;
{$ELSE}
function MsiGetPropertyA; external msilib name 'MsiGetPropertyA';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _MsiGetPropertyW: Pointer;

function MsiGetPropertyW;
begin
  GetProcedureAddress(_MsiGetPropertyW, msilib, 'MsiGetPropertyW');
  asm
    mov esp, ebp
    pop ebp
    jmp [_MsiGetPropertyW]
  end;
end;
{$ELSE}
function MsiGetPropertyW; external msilib name 'MsiGetPropertyW';
{$ENDIF DYNAMIC_LINK}
{$IFDEF UNICODE}

{$IFDEF DYNAMIC_LINK}
var
  _MsiGetProperty: Pointer;

function MsiGetProperty;
begin
  GetProcedureAddress(_MsiGetProperty, msilib, 'MsiGetPropertyW');
  asm
    mov esp, ebp
    pop ebp
    jmp [_MsiGetProperty]
  end;
end;
{$ELSE}
function MsiGetProperty; external msilib name 'MsiGetPropertyW';
{$ENDIF DYNAMIC_LINK}
{$ELSE}

{$IFDEF DYNAMIC_LINK}
var
  _MsiGetProperty: Pointer;

function MsiGetProperty;
begin
  GetProcedureAddress(_MsiGetProperty, msilib, 'MsiGetPropertyA');
  asm
    mov esp, ebp
    pop ebp
    jmp [_MsiGetProperty]
  end;
end;
{$ELSE}
function MsiGetProperty; external msilib name 'MsiGetPropertyA';
{$ENDIF DYNAMIC_LINK}
{$ENDIF}

{$IFDEF DYNAMIC_LINK}
var
  _MsiGetLanguage: Pointer;

function MsiGetLanguage;
begin
  GetProcedureAddress(_MsiGetLanguage, msilib, 'MsiGetLanguage');
  asm
    mov esp, ebp
    pop ebp
    jmp [_MsiGetLanguage]
  end;
end;
{$ELSE}
function MsiGetLanguage; external msilib name 'MsiGetLanguage';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _MsiGetMode: Pointer;

function MsiGetMode;
begin
  GetProcedureAddress(_MsiGetMode, msilib, 'MsiGetMode');
  asm
    mov esp, ebp
    pop ebp
    jmp [_MsiGetMode]
  end;
end;
{$ELSE}
function MsiGetMode; external msilib name 'MsiGetMode';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _MsiSetMode: Pointer;

function MsiSetMode;
begin
  GetProcedureAddress(_MsiSetMode, msilib, 'MsiSetMode');
  asm
    mov esp, ebp
    pop ebp
    jmp [_MsiSetMode]
  end;
end;
{$ELSE}
function MsiSetMode; external msilib name 'MsiSetMode';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _MsiFormatRecordA: Pointer;

function MsiFormatRecordA;
begin
  GetProcedureAddress(_MsiFormatRecordA, msilib, 'MsiFormatRecordA');
  asm
    mov esp, ebp
    pop ebp
    jmp [_MsiFormatRecordA]
  end;
end;
{$ELSE}
function MsiFormatRecordA; external msilib name 'MsiFormatRecordA';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _MsiFormatRecordW: Pointer;

function MsiFormatRecordW;
begin
  GetProcedureAddress(_MsiFormatRecordW, msilib, 'MsiFormatRecordW');
  asm
    mov esp, ebp
    pop ebp
    jmp [_MsiFormatRecordW]
  end;
end;
{$ELSE}
function MsiFormatRecordW; external msilib name 'MsiFormatRecordW';
{$ENDIF DYNAMIC_LINK}
{$IFDEF UNICODE}

{$IFDEF DYNAMIC_LINK}
var
  _MsiFormatRecord: Pointer;

function MsiFormatRecord;
begin
  GetProcedureAddress(_MsiFormatRecord, msilib, 'MsiFormatRecordW');
  asm
    mov esp, ebp
    pop ebp
    jmp [_MsiFormatRecord]
  end;
end;
{$ELSE}
function MsiFormatRecord; external msilib name 'MsiFormatRecordW';
{$ENDIF DYNAMIC_LINK}
{$ELSE}

{$IFDEF DYNAMIC_LINK}
var
  _MsiFormatRecord: Pointer;

function MsiFormatRecord;
begin
  GetProcedureAddress(_MsiFormatRecord, msilib, 'MsiFormatRecordA');
  asm
    mov esp, ebp
    pop ebp
    jmp [_MsiFormatRecord]
  end;
end;
{$ELSE}
function MsiFormatRecord; external msilib name 'MsiFormatRecordA';
{$ENDIF DYNAMIC_LINK}
{$ENDIF}

{$IFDEF DYNAMIC_LINK}
var
  _MsiDoActionA: Pointer;

function MsiDoActionA;
begin
  GetProcedureAddress(_MsiDoActionA, msilib, 'MsiDoActionA');
  asm
    mov esp, ebp
    pop ebp
    jmp [_MsiDoActionA]
  end;
end;
{$ELSE}
function MsiDoActionA; external msilib name 'MsiDoActionA';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _MsiDoActionW: Pointer;

function MsiDoActionW;
begin
  GetProcedureAddress(_MsiDoActionW, msilib, 'MsiDoActionW');
  asm
    mov esp, ebp
    pop ebp
    jmp [_MsiDoActionW]
  end;
end;
{$ELSE}
function MsiDoActionW; external msilib name 'MsiDoActionW';
{$ENDIF DYNAMIC_LINK}
{$IFDEF UNICODE}

{$IFDEF DYNAMIC_LINK}
var
  _MsiDoAction: Pointer;

function MsiDoAction;
begin
  GetProcedureAddress(_MsiDoAction, msilib, 'MsiDoActionW');
  asm
    mov esp, ebp
    pop ebp
    jmp [_MsiDoAction]
  end;
end;
{$ELSE}
function MsiDoAction; external msilib name 'MsiDoActionW';
{$ENDIF DYNAMIC_LINK}
{$ELSE}

{$IFDEF DYNAMIC_LINK}
var
  _MsiDoAction: Pointer;

function MsiDoAction;
begin
  GetProcedureAddress(_MsiDoAction, msilib, 'MsiDoActionA');
  asm
    mov esp, ebp
    pop ebp
    jmp [_MsiDoAction]
  end;
end;
{$ELSE}
function MsiDoAction; external msilib name 'MsiDoActionA';
{$ENDIF DYNAMIC_LINK}
{$ENDIF}

{$IFDEF DYNAMIC_LINK}
var
  _MsiSequenceA: Pointer;

function MsiSequenceA;
begin
  GetProcedureAddress(_MsiSequenceA, msilib, 'MsiSequenceA');
  asm
    mov esp, ebp
    pop ebp
    jmp [_MsiSequenceA]
  end;
end;
{$ELSE}
function MsiSequenceA; external msilib name 'MsiSequenceA';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _MsiSequenceW: Pointer;

function MsiSequenceW;
begin
  GetProcedureAddress(_MsiSequenceW, msilib, 'MsiSequenceW');
  asm
    mov esp, ebp
    pop ebp
    jmp [_MsiSequenceW]
  end;
end;
{$ELSE}
function MsiSequenceW; external msilib name 'MsiSequenceW';
{$ENDIF DYNAMIC_LINK}
{$IFDEF UNICODE}

{$IFDEF DYNAMIC_LINK}
var
  _MsiSequence: Pointer;

function MsiSequence;
begin
  GetProcedureAddress(_MsiSequence, msilib, 'MsiSequenceW');
  asm
    mov esp, ebp
    pop ebp
    jmp [_MsiSequence]
  end;
end;
{$ELSE}
function MsiSequence; external msilib name 'MsiSequenceW';
{$ENDIF DYNAMIC_LINK}
{$ELSE}

{$IFDEF DYNAMIC_LINK}
var
  _MsiSequence: Pointer;

function MsiSequence;
begin
  GetProcedureAddress(_MsiSequence, msilib, 'MsiSequenceA');
  asm
    mov esp, ebp
    pop ebp
    jmp [_MsiSequence]
  end;
end;
{$ELSE}
function MsiSequence; external msilib name 'MsiSequenceA';
{$ENDIF DYNAMIC_LINK}
{$ENDIF}

{$IFDEF DYNAMIC_LINK}
var
  _MsiProcessMessage: Pointer;

function MsiProcessMessage;
begin
  GetProcedureAddress(_MsiProcessMessage, msilib, 'MsiProcessMessage');
  asm
    mov esp, ebp
    pop ebp
    jmp [_MsiProcessMessage]
  end;
end;
{$ELSE}
function MsiProcessMessage; external msilib name 'MsiProcessMessage';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _MsiEvaluateConditionA: Pointer;

function MsiEvaluateConditionA;
begin
  GetProcedureAddress(_MsiEvaluateConditionA, msilib, 'MsiEvaluateConditionA');
  asm
    mov esp, ebp
    pop ebp
    jmp [_MsiEvaluateConditionA]
  end;
end;
{$ELSE}
function MsiEvaluateConditionA; external msilib name 'MsiEvaluateConditionA';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _MsiEvaluateConditionW: Pointer;

function MsiEvaluateConditionW;
begin
  GetProcedureAddress(_MsiEvaluateConditionW, msilib, 'MsiEvaluateConditionW');
  asm
    mov esp, ebp
    pop ebp
    jmp [_MsiEvaluateConditionW]
  end;
end;
{$ELSE}
function MsiEvaluateConditionW; external msilib name 'MsiEvaluateConditionW';
{$ENDIF DYNAMIC_LINK}
{$IFDEF UNICODE}

{$IFDEF DYNAMIC_LINK}
var
  _MsiEvaluateCondition: Pointer;

function MsiEvaluateCondition;
begin
  GetProcedureAddress(_MsiEvaluateCondition, msilib, 'MsiEvaluateConditionW');
  asm
    mov esp, ebp
    pop ebp
    jmp [_MsiEvaluateCondition]
  end;
end;
{$ELSE}
function MsiEvaluateCondition; external msilib name 'MsiEvaluateConditionW';
{$ENDIF DYNAMIC_LINK}
{$ELSE}

{$IFDEF DYNAMIC_LINK}
var
  _MsiEvaluateCondition: Pointer;

function MsiEvaluateCondition;
begin
  GetProcedureAddress(_MsiEvaluateCondition, msilib, 'MsiEvaluateConditionA');
  asm
    mov esp, ebp
    pop ebp
    jmp [_MsiEvaluateCondition]
  end;
end;
{$ELSE}
function MsiEvaluateCondition; external msilib name 'MsiEvaluateConditionA';
{$ENDIF DYNAMIC_LINK}
{$ENDIF}

{$IFDEF DYNAMIC_LINK}
var
  _MsiGetFeatureStateA: Pointer;

function MsiGetFeatureStateA;
begin
  GetProcedureAddress(_MsiGetFeatureStateA, msilib, 'MsiGetFeatureStateA');
  asm
    mov esp, ebp
    pop ebp
    jmp [_MsiGetFeatureStateA]
  end;
end;
{$ELSE}
function MsiGetFeatureStateA; external msilib name 'MsiGetFeatureStateA';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _MsiGetFeatureStateW: Pointer;

function MsiGetFeatureStateW;
begin
  GetProcedureAddress(_MsiGetFeatureStateW, msilib, 'MsiGetFeatureStateW');
  asm
    mov esp, ebp
    pop ebp
    jmp [_MsiGetFeatureStateW]
  end;
end;
{$ELSE}
function MsiGetFeatureStateW; external msilib name 'MsiGetFeatureStateW';
{$ENDIF DYNAMIC_LINK}
{$IFDEF UNICODE}

{$IFDEF DYNAMIC_LINK}
var
  _MsiGetFeatureState: Pointer;

function MsiGetFeatureState;
begin
  GetProcedureAddress(_MsiGetFeatureState, msilib, 'MsiGetFeatureStateW');
  asm
    mov esp, ebp
    pop ebp
    jmp [_MsiGetFeatureState]
  end;
end;
{$ELSE}
function MsiGetFeatureState; external msilib name 'MsiGetFeatureStateW';
{$ENDIF DYNAMIC_LINK}
{$ELSE}

{$IFDEF DYNAMIC_LINK}
var
  _MsiGetFeatureState: Pointer;

function MsiGetFeatureState;
begin
  GetProcedureAddress(_MsiGetFeatureState, msilib, 'MsiGetFeatureStateA');
  asm
    mov esp, ebp
    pop ebp
    jmp [_MsiGetFeatureState]
  end;
end;
{$ELSE}
function MsiGetFeatureState; external msilib name 'MsiGetFeatureStateA';
{$ENDIF DYNAMIC_LINK}
{$ENDIF}

{$IFDEF DYNAMIC_LINK}
var
  _MsiSetFeatureStateA: Pointer;

function MsiSetFeatureStateA;
begin
  GetProcedureAddress(_MsiSetFeatureStateA, msilib, 'MsiSetFeatureStateA');
  asm
    mov esp, ebp
    pop ebp
    jmp [_MsiSetFeatureStateA]
  end;
end;
{$ELSE}
function MsiSetFeatureStateA; external msilib name 'MsiSetFeatureStateA';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _MsiSetFeatureStateW: Pointer;

function MsiSetFeatureStateW;
begin
  GetProcedureAddress(_MsiSetFeatureStateW, msilib, 'MsiSetFeatureStateW');
  asm
    mov esp, ebp
    pop ebp
    jmp [_MsiSetFeatureStateW]
  end;
end;
{$ELSE}
function MsiSetFeatureStateW; external msilib name 'MsiSetFeatureStateW';
{$ENDIF DYNAMIC_LINK}
{$IFDEF UNICODE}

{$IFDEF DYNAMIC_LINK}
var
  _MsiSetFeatureState: Pointer;

function MsiSetFeatureState;
begin
  GetProcedureAddress(_MsiSetFeatureState, msilib, 'MsiSetFeatureStateW');
  asm
    mov esp, ebp
    pop ebp
    jmp [_MsiSetFeatureState]
  end;
end;
{$ELSE}
function MsiSetFeatureState; external msilib name 'MsiSetFeatureStateW';
{$ENDIF DYNAMIC_LINK}
{$ELSE}

{$IFDEF DYNAMIC_LINK}
var
  _MsiSetFeatureState: Pointer;

function MsiSetFeatureState;
begin
  GetProcedureAddress(_MsiSetFeatureState, msilib, 'MsiSetFeatureStateA');
  asm
    mov esp, ebp
    pop ebp
    jmp [_MsiSetFeatureState]
  end;
end;
{$ELSE}
function MsiSetFeatureState; external msilib name 'MsiSetFeatureStateA';
{$ENDIF DYNAMIC_LINK}
{$ENDIF}

{$IFDEF DYNAMIC_LINK}
var
  _MsiSetFeatureAttributesA: Pointer;

function MsiSetFeatureAttributesA;
begin
  GetProcedureAddress(_MsiSetFeatureAttributesA, msilib, 'MsiSetFeatureAttributesA');
  asm
    mov esp, ebp
    pop ebp
    jmp [_MsiSetFeatureAttributesA]
  end;
end;
{$ELSE}
function MsiSetFeatureAttributesA; external msilib name 'MsiSetFeatureAttributesA';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _MsiSetFeatureAttributesW: Pointer;

function MsiSetFeatureAttributesW;
begin
  GetProcedureAddress(_MsiSetFeatureAttributesW, msilib, 'MsiSetFeatureAttributesW');
  asm
    mov esp, ebp
    pop ebp
    jmp [_MsiSetFeatureAttributesW]
  end;
end;
{$ELSE}
function MsiSetFeatureAttributesW; external msilib name 'MsiSetFeatureAttributesW';
{$ENDIF DYNAMIC_LINK}
{$IFDEF UNICODE}

{$IFDEF DYNAMIC_LINK}
var
  _MsiSetFeatureAttributes: Pointer;

function MsiSetFeatureAttributes;
begin
  GetProcedureAddress(_MsiSetFeatureAttributes, msilib, 'MsiSetFeatureAttributesW');
  asm
    mov esp, ebp
    pop ebp
    jmp [_MsiSetFeatureAttributes]
  end;
end;
{$ELSE}
function MsiSetFeatureAttributes; external msilib name 'MsiSetFeatureAttributesW';
{$ENDIF DYNAMIC_LINK}
{$ELSE}

{$IFDEF DYNAMIC_LINK}
var
  _MsiSetFeatureAttributes: Pointer;

function MsiSetFeatureAttributes;
begin
  GetProcedureAddress(_MsiSetFeatureAttributes, msilib, 'MsiSetFeatureAttributesA');
  asm
    mov esp, ebp
    pop ebp
    jmp [_MsiSetFeatureAttributes]
  end;
end;
{$ELSE}
function MsiSetFeatureAttributes; external msilib name 'MsiSetFeatureAttributesA';
{$ENDIF DYNAMIC_LINK}
{$ENDIF}

{$IFDEF DYNAMIC_LINK}
var
  _MsiGetComponentStateA: Pointer;

function MsiGetComponentStateA;
begin
  GetProcedureAddress(_MsiGetComponentStateA, msilib, 'MsiGetComponentStateA');
  asm
    mov esp, ebp
    pop ebp
    jmp [_MsiGetComponentStateA]
  end;
end;
{$ELSE}
function MsiGetComponentStateA; external msilib name 'MsiGetComponentStateA';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _MsiGetComponentStateW: Pointer;

function MsiGetComponentStateW;
begin
  GetProcedureAddress(_MsiGetComponentStateW, msilib, 'MsiGetComponentStateW');
  asm
    mov esp, ebp
    pop ebp
    jmp [_MsiGetComponentStateW]
  end;
end;
{$ELSE}
function MsiGetComponentStateW; external msilib name 'MsiGetComponentStateW';
{$ENDIF DYNAMIC_LINK}
{$IFDEF UNICODE}

{$IFDEF DYNAMIC_LINK}
var
  _MsiGetComponentState: Pointer;

function MsiGetComponentState;
begin
  GetProcedureAddress(_MsiGetComponentState, msilib, 'MsiGetComponentStateW');
  asm
    mov esp, ebp
    pop ebp
    jmp [_MsiGetComponentState]
  end;
end;
{$ELSE}
function MsiGetComponentState; external msilib name 'MsiGetComponentStateW';
{$ENDIF DYNAMIC_LINK}
{$ELSE}

{$IFDEF DYNAMIC_LINK}
var
  _MsiGetComponentState: Pointer;

function MsiGetComponentState;
begin
  GetProcedureAddress(_MsiGetComponentState, msilib, 'MsiGetComponentStateA');
  asm
    mov esp, ebp
    pop ebp
    jmp [_MsiGetComponentState]
  end;
end;
{$ELSE}
function MsiGetComponentState; external msilib name 'MsiGetComponentStateA';
{$ENDIF DYNAMIC_LINK}
{$ENDIF}

{$IFDEF DYNAMIC_LINK}
var
  _MsiSetComponentStateA: Pointer;

function MsiSetComponentStateA;
begin
  GetProcedureAddress(_MsiSetComponentStateA, msilib, 'MsiSetComponentStateA');
  asm
    mov esp, ebp
    pop ebp
    jmp [_MsiSetComponentStateA]
  end;
end;
{$ELSE}
function MsiSetComponentStateA; external msilib name 'MsiSetComponentStateA';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _MsiSetComponentStateW: Pointer;

function MsiSetComponentStateW;
begin
  GetProcedureAddress(_MsiSetComponentStateW, msilib, 'MsiSetComponentStateW');
  asm
    mov esp, ebp
    pop ebp
    jmp [_MsiSetComponentStateW]
  end;
end;
{$ELSE}
function MsiSetComponentStateW; external msilib name 'MsiSetComponentStateW';
{$ENDIF DYNAMIC_LINK}
{$IFDEF UNICODE}

{$IFDEF DYNAMIC_LINK}
var
  _MsiSetComponentState: Pointer;

function MsiSetComponentState;
begin
  GetProcedureAddress(_MsiSetComponentState, msilib, 'MsiSetComponentStateW');
  asm
    mov esp, ebp
    pop ebp
    jmp [_MsiSetComponentState]
  end;
end;
{$ELSE}
function MsiSetComponentState; external msilib name 'MsiSetComponentStateW';
{$ENDIF DYNAMIC_LINK}
{$ELSE}

{$IFDEF DYNAMIC_LINK}
var
  _MsiSetComponentState: Pointer;

function MsiSetComponentState;
begin
  GetProcedureAddress(_MsiSetComponentState, msilib, 'MsiSetComponentStateA');
  asm
    mov esp, ebp
    pop ebp
    jmp [_MsiSetComponentState]
  end;
end;
{$ELSE}
function MsiSetComponentState; external msilib name 'MsiSetComponentStateA';
{$ENDIF DYNAMIC_LINK}
{$ENDIF}

{$IFDEF DYNAMIC_LINK}
var
  _MsiGetFeatureCostA: Pointer;

function MsiGetFeatureCostA;
begin
  GetProcedureAddress(_MsiGetFeatureCostA, msilib, 'MsiGetFeatureCostA');
  asm
    mov esp, ebp
    pop ebp
    jmp [_MsiGetFeatureCostA]
  end;
end;
{$ELSE}
function MsiGetFeatureCostA; external msilib name 'MsiGetFeatureCostA';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _MsiGetFeatureCostW: Pointer;

function MsiGetFeatureCostW;
begin
  GetProcedureAddress(_MsiGetFeatureCostW, msilib, 'MsiGetFeatureCostW');
  asm
    mov esp, ebp
    pop ebp
    jmp [_MsiGetFeatureCostW]
  end;
end;
{$ELSE}
function MsiGetFeatureCostW; external msilib name 'MsiGetFeatureCostW';
{$ENDIF DYNAMIC_LINK}
{$IFDEF UNICODE}

{$IFDEF DYNAMIC_LINK}
var
  _MsiGetFeatureCost: Pointer;

function MsiGetFeatureCost;
begin
  GetProcedureAddress(_MsiGetFeatureCost, msilib, 'MsiGetFeatureCostW');
  asm
    mov esp, ebp
    pop ebp
    jmp [_MsiGetFeatureCost]
  end;
end;
{$ELSE}
function MsiGetFeatureCost; external msilib name 'MsiGetFeatureCostW';
{$ENDIF DYNAMIC_LINK}
{$ELSE}

{$IFDEF DYNAMIC_LINK}
var
  _MsiGetFeatureCost: Pointer;

function MsiGetFeatureCost;
begin
  GetProcedureAddress(_MsiGetFeatureCost, msilib, 'MsiGetFeatureCostA');
  asm
    mov esp, ebp
    pop ebp
    jmp [_MsiGetFeatureCost]
  end;
end;
{$ELSE}
function MsiGetFeatureCost; external msilib name 'MsiGetFeatureCostA';
{$ENDIF DYNAMIC_LINK}
{$ENDIF}

{$IFDEF DYNAMIC_LINK}
var
  _MsiEnumComponentCostsA: Pointer;

function MsiEnumComponentCostsA;
begin
  GetProcedureAddress(_MsiEnumComponentCostsA, msilib, 'MsiEnumComponentCostsA');
  asm
    mov esp, ebp
    pop ebp
    jmp [_MsiEnumComponentCostsA]
  end;
end;
{$ELSE}
function MsiEnumComponentCostsA; external msilib name 'MsiEnumComponentCostsA';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _MsiEnumComponentCostsW: Pointer;

function MsiEnumComponentCostsW;
begin
  GetProcedureAddress(_MsiEnumComponentCostsW, msilib, 'MsiEnumComponentCostsW');
  asm
    mov esp, ebp
    pop ebp
    jmp [_MsiEnumComponentCostsW]
  end;
end;
{$ELSE}
function MsiEnumComponentCostsW; external msilib name 'MsiEnumComponentCostsW';
{$ENDIF DYNAMIC_LINK}
{$IFDEF UNICODE}

{$IFDEF DYNAMIC_LINK}
var
  _MsiEnumComponentCosts: Pointer;

function MsiEnumComponentCosts;
begin
  GetProcedureAddress(_MsiEnumComponentCosts, msilib, 'MsiEnumComponentCostsW');
  asm
    mov esp, ebp
    pop ebp
    jmp [_MsiEnumComponentCosts]
  end;
end;
{$ELSE}
function MsiEnumComponentCosts; external msilib name 'MsiEnumComponentCostsW';
{$ENDIF DYNAMIC_LINK}
{$ELSE}

{$IFDEF DYNAMIC_LINK}
var
  _MsiEnumComponentCosts: Pointer;

function MsiEnumComponentCosts;
begin
  GetProcedureAddress(_MsiEnumComponentCosts, msilib, 'MsiEnumComponentCostsA');
  asm
    mov esp, ebp
    pop ebp
    jmp [_MsiEnumComponentCosts]
  end;
end;
{$ELSE}
function MsiEnumComponentCosts; external msilib name 'MsiEnumComponentCostsA';
{$ENDIF DYNAMIC_LINK}
{$ENDIF}

{$IFDEF DYNAMIC_LINK}
var
  _MsiSetInstallLevel: Pointer;

function MsiSetInstallLevel;
begin
  GetProcedureAddress(_MsiSetInstallLevel, msilib, 'MsiSetInstallLevel');
  asm
    mov esp, ebp
    pop ebp
    jmp [_MsiSetInstallLevel]
  end;
end;
{$ELSE}
function MsiSetInstallLevel; external msilib name 'MsiSetInstallLevel';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _MsiGetFeatureValidStatesA: Pointer;

function MsiGetFeatureValidStatesA;
begin
  GetProcedureAddress(_MsiGetFeatureValidStatesA, msilib, 'MsiGetFeatureValidStatesA');
  asm
    mov esp, ebp
    pop ebp
    jmp [_MsiGetFeatureValidStatesA]
  end;
end;
{$ELSE}
function MsiGetFeatureValidStatesA; external msilib name 'MsiGetFeatureValidStatesA';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _MsiGetFeatureValidStatesW: Pointer;

function MsiGetFeatureValidStatesW;
begin
  GetProcedureAddress(_MsiGetFeatureValidStatesW, msilib, 'MsiGetFeatureValidStatesW');
  asm
    mov esp, ebp
    pop ebp
    jmp [_MsiGetFeatureValidStatesW]
  end;
end;
{$ELSE}
function MsiGetFeatureValidStatesW; external msilib name 'MsiGetFeatureValidStatesW';
{$ENDIF DYNAMIC_LINK}
{$IFDEF UNICODE}

{$IFDEF DYNAMIC_LINK}
var
  _MsiGetFeatureValidStates: Pointer;

function MsiGetFeatureValidStates;
begin
  GetProcedureAddress(_MsiGetFeatureValidStates, msilib, 'MsiGetFeatureValidStatesW');
  asm
    mov esp, ebp
    pop ebp
    jmp [_MsiGetFeatureValidStates]
  end;
end;
{$ELSE}
function MsiGetFeatureValidStates; external msilib name 'MsiGetFeatureValidStatesW';
{$ENDIF DYNAMIC_LINK}
{$ELSE}

{$IFDEF DYNAMIC_LINK}
var
  _MsiGetFeatureValidStates: Pointer;

function MsiGetFeatureValidStates;
begin
  GetProcedureAddress(_MsiGetFeatureValidStates, msilib, 'MsiGetFeatureValidStatesA');
  asm
    mov esp, ebp
    pop ebp
    jmp [_MsiGetFeatureValidStates]
  end;
end;
{$ELSE}
function MsiGetFeatureValidStates; external msilib name 'MsiGetFeatureValidStatesA';
{$ENDIF DYNAMIC_LINK}
{$ENDIF}

{$IFDEF DYNAMIC_LINK}
var
  _MsiGetSourcePathA: Pointer;

function MsiGetSourcePathA;
begin
  GetProcedureAddress(_MsiGetSourcePathA, msilib, 'MsiGetSourcePathA');
  asm
    mov esp, ebp
    pop ebp
    jmp [_MsiGetSourcePathA]
  end;
end;
{$ELSE}
function MsiGetSourcePathA; external msilib name 'MsiGetSourcePathA';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _MsiGetSourcePathW: Pointer;

function MsiGetSourcePathW;
begin
  GetProcedureAddress(_MsiGetSourcePathW, msilib, 'MsiGetSourcePathW');
  asm
    mov esp, ebp
    pop ebp
    jmp [_MsiGetSourcePathW]
  end;
end;
{$ELSE}
function MsiGetSourcePathW; external msilib name 'MsiGetSourcePathW';
{$ENDIF DYNAMIC_LINK}
{$IFDEF UNICODE}

{$IFDEF DYNAMIC_LINK}
var
  _MsiGetSourcePath: Pointer;

function MsiGetSourcePath;
begin
  GetProcedureAddress(_MsiGetSourcePath, msilib, 'MsiGetSourcePathW');
  asm
    mov esp, ebp
    pop ebp
    jmp [_MsiGetSourcePath]
  end;
end;
{$ELSE}
function MsiGetSourcePath; external msilib name 'MsiGetSourcePathW';
{$ENDIF DYNAMIC_LINK}
{$ELSE}

{$IFDEF DYNAMIC_LINK}
var
  _MsiGetSourcePath: Pointer;

function MsiGetSourcePath;
begin
  GetProcedureAddress(_MsiGetSourcePath, msilib, 'MsiGetSourcePathA');
  asm
    mov esp, ebp
    pop ebp
    jmp [_MsiGetSourcePath]
  end;
end;
{$ELSE}
function MsiGetSourcePath; external msilib name 'MsiGetSourcePathA';
{$ENDIF DYNAMIC_LINK}
{$ENDIF}

{$IFDEF DYNAMIC_LINK}
var
  _MsiGetTargetPathA: Pointer;

function MsiGetTargetPathA;
begin
  GetProcedureAddress(_MsiGetTargetPathA, msilib, 'MsiGetTargetPathA');
  asm
    mov esp, ebp
    pop ebp
    jmp [_MsiGetTargetPathA]
  end;
end;
{$ELSE}
function MsiGetTargetPathA; external msilib name 'MsiGetTargetPathA';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _MsiGetTargetPathW: Pointer;

function MsiGetTargetPathW;
begin
  GetProcedureAddress(_MsiGetTargetPathW, msilib, 'MsiGetTargetPathW');
  asm
    mov esp, ebp
    pop ebp
    jmp [_MsiGetTargetPathW]
  end;
end;
{$ELSE}
function MsiGetTargetPathW; external msilib name 'MsiGetTargetPathW';
{$ENDIF DYNAMIC_LINK}
{$IFDEF UNICODE}

{$IFDEF DYNAMIC_LINK}
var
  _MsiGetTargetPath: Pointer;

function MsiGetTargetPath;
begin
  GetProcedureAddress(_MsiGetTargetPath, msilib, 'MsiGetTargetPathW');
  asm
    mov esp, ebp
    pop ebp
    jmp [_MsiGetTargetPath]
  end;
end;
{$ELSE}
function MsiGetTargetPath; external msilib name 'MsiGetTargetPathW';
{$ENDIF DYNAMIC_LINK}
{$ELSE}

{$IFDEF DYNAMIC_LINK}
var
  _MsiGetTargetPath: Pointer;

function MsiGetTargetPath;
begin
  GetProcedureAddress(_MsiGetTargetPath, msilib, 'MsiGetTargetPathA');
  asm
    mov esp, ebp
    pop ebp
    jmp [_MsiGetTargetPath]
  end;
end;
{$ELSE}
function MsiGetTargetPath; external msilib name 'MsiGetTargetPathA';
{$ENDIF DYNAMIC_LINK}
{$ENDIF}

{$IFDEF DYNAMIC_LINK}
var
  _MsiSetTargetPathA: Pointer;

function MsiSetTargetPathA;
begin
  GetProcedureAddress(_MsiSetTargetPathA, msilib, 'MsiSetTargetPathA');
  asm
    mov esp, ebp
    pop ebp
    jmp [_MsiSetTargetPathA]
  end;
end;
{$ELSE}
function MsiSetTargetPathA; external msilib name 'MsiSetTargetPathA';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _MsiSetTargetPathW: Pointer;

function MsiSetTargetPathW;
begin
  GetProcedureAddress(_MsiSetTargetPathW, msilib, 'MsiSetTargetPathW');
  asm
    mov esp, ebp
    pop ebp
    jmp [_MsiSetTargetPathW]
  end;
end;
{$ELSE}
function MsiSetTargetPathW; external msilib name 'MsiSetTargetPathW';
{$ENDIF DYNAMIC_LINK}
{$IFDEF UNICODE}

{$IFDEF DYNAMIC_LINK}
var
  _MsiSetTargetPath: Pointer;

function MsiSetTargetPath;
begin
  GetProcedureAddress(_MsiSetTargetPath, msilib, 'MsiSetTargetPathW');
  asm
    mov esp, ebp
    pop ebp
    jmp [_MsiSetTargetPath]
  end;
end;
{$ELSE}
function MsiSetTargetPath; external msilib name 'MsiSetTargetPathW';
{$ENDIF DYNAMIC_LINK}
{$ELSE}

{$IFDEF DYNAMIC_LINK}
var
  _MsiSetTargetPath: Pointer;

function MsiSetTargetPath;
begin
  GetProcedureAddress(_MsiSetTargetPath, msilib, 'MsiSetTargetPathA');
  asm
    mov esp, ebp
    pop ebp
    jmp [_MsiSetTargetPath]
  end;
end;
{$ELSE}
function MsiSetTargetPath; external msilib name 'MsiSetTargetPathA';
{$ENDIF DYNAMIC_LINK}
{$ENDIF}

{$IFDEF DYNAMIC_LINK}
var
  _MsiVerifyDiskSpace: Pointer;

function MsiVerifyDiskSpace;
begin
  GetProcedureAddress(_MsiVerifyDiskSpace, msilib, 'MsiVerifyDiskSpace');
  asm
    mov esp, ebp
    pop ebp
    jmp [_MsiVerifyDiskSpace]
  end;
end;
{$ELSE}
function MsiVerifyDiskSpace; external msilib name 'MsiVerifyDiskSpace';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _MsiEnableUIPreview: Pointer;

function MsiEnableUIPreview;
begin
  GetProcedureAddress(_MsiEnableUIPreview, msilib, 'MsiEnableUIPreview');
  asm
    mov esp, ebp
    pop ebp
    jmp [_MsiEnableUIPreview]
  end;
end;
{$ELSE}
function MsiEnableUIPreview; external msilib name 'MsiEnableUIPreview';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _MsiPreviewDialogA: Pointer;

function MsiPreviewDialogA;
begin
  GetProcedureAddress(_MsiPreviewDialogA, msilib, 'MsiPreviewDialogA');
  asm
    mov esp, ebp
    pop ebp
    jmp [_MsiPreviewDialogA]
  end;
end;
{$ELSE}
function MsiPreviewDialogA; external msilib name 'MsiPreviewDialogA';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _MsiPreviewDialogW: Pointer;

function MsiPreviewDialogW;
begin
  GetProcedureAddress(_MsiPreviewDialogW, msilib, 'MsiPreviewDialogW');
  asm
    mov esp, ebp
    pop ebp
    jmp [_MsiPreviewDialogW]
  end;
end;
{$ELSE}
function MsiPreviewDialogW; external msilib name 'MsiPreviewDialogW';
{$ENDIF DYNAMIC_LINK}
{$IFDEF UNICODE}

{$IFDEF DYNAMIC_LINK}
var
  _MsiPreviewDialog: Pointer;

function MsiPreviewDialog;
begin
  GetProcedureAddress(_MsiPreviewDialog, msilib, 'MsiPreviewDialogW');
  asm
    mov esp, ebp
    pop ebp
    jmp [_MsiPreviewDialog]
  end;
end;
{$ELSE}
function MsiPreviewDialog; external msilib name 'MsiPreviewDialogW';
{$ENDIF DYNAMIC_LINK}
{$ELSE}

{$IFDEF DYNAMIC_LINK}
var
  _MsiPreviewDialog: Pointer;

function MsiPreviewDialog;
begin
  GetProcedureAddress(_MsiPreviewDialog, msilib, 'MsiPreviewDialogA');
  asm
    mov esp, ebp
    pop ebp
    jmp [_MsiPreviewDialog]
  end;
end;
{$ELSE}
function MsiPreviewDialog; external msilib name 'MsiPreviewDialogA';
{$ENDIF DYNAMIC_LINK}
{$ENDIF}

{$IFDEF DYNAMIC_LINK}
var
  _MsiPreviewBillboardA: Pointer;

function MsiPreviewBillboardA;
begin
  GetProcedureAddress(_MsiPreviewBillboardA, msilib, 'MsiPreviewBillboardA');
  asm
    mov esp, ebp
    pop ebp
    jmp [_MsiPreviewBillboardA]
  end;
end;
{$ELSE}
function MsiPreviewBillboardA; external msilib name 'MsiPreviewBillboardA';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _MsiPreviewBillboardW: Pointer;

function MsiPreviewBillboardW;
begin
  GetProcedureAddress(_MsiPreviewBillboardW, msilib, 'MsiPreviewBillboardW');
  asm
    mov esp, ebp
    pop ebp
    jmp [_MsiPreviewBillboardW]
  end;
end;
{$ELSE}
function MsiPreviewBillboardW; external msilib name 'MsiPreviewBillboardW';
{$ENDIF DYNAMIC_LINK}
{$IFDEF UNICODE}

{$IFDEF DYNAMIC_LINK}
var
  _MsiPreviewBillboard: Pointer;

function MsiPreviewBillboard;
begin
  GetProcedureAddress(_MsiPreviewBillboard, msilib, 'MsiPreviewBillboardW');
  asm
    mov esp, ebp
    pop ebp
    jmp [_MsiPreviewBillboard]
  end;
end;
{$ELSE}
function MsiPreviewBillboard; external msilib name 'MsiPreviewBillboardW';
{$ENDIF DYNAMIC_LINK}
{$ELSE}

{$IFDEF DYNAMIC_LINK}
var
  _MsiPreviewBillboard: Pointer;

function MsiPreviewBillboard;
begin
  GetProcedureAddress(_MsiPreviewBillboard, msilib, 'MsiPreviewBillboardA');
  asm
    mov esp, ebp
    pop ebp
    jmp [_MsiPreviewBillboard]
  end;
end;
{$ELSE}
function MsiPreviewBillboard; external msilib name 'MsiPreviewBillboardA';
{$ENDIF DYNAMIC_LINK}
{$ENDIF}

{$IFDEF DYNAMIC_LINK}
var
  _MsiGetLastErrorRecord: Pointer;

function MsiGetLastErrorRecord;
begin
  GetProcedureAddress(_MsiGetLastErrorRecord, msilib, 'MsiGetLastErrorRecord');
  asm
    mov esp, ebp
    pop ebp
    jmp [_MsiGetLastErrorRecord]
  end;
end;
{$ELSE}
function MsiGetLastErrorRecord; external msilib name 'MsiGetLastErrorRecord';
{$ENDIF DYNAMIC_LINK}

end.
