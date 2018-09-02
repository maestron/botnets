{
  Delphi translation of the Microsoft ODBC API headers, ODBC version 3.51
  Version 3.023, 2004-11-08

  Copyright (c) 2001-2004 Edward Benson

  This library is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public
  License as published by the Free Software Foundation; either
  version 2.1 of the License, or (at your option) any later version.

  This library is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
  See the GNU Lesser General Public License for more details.
}
unit OdbcApi;
{$B-}

//**************************************************************************
//
// ODBC API 3.51
//
// I have merged all the relevant header files into this one file,
// and removed all version specific IFDEFs assuming VERSION 3.51
//   sqltypes.h
//   sql.h
//   sqlext.h
//   sqlucode.h
//   sqltrace.h
//
//
// Initial translation done using
// HeadConv 4.0 (c) 2000 by Bob Swart (aka Dr.Bob - www.drbob42.com)
// Final Delphi-Jedi (Darth) command-line units edition
//
// Created   26-Jun-2001  By Edward Benson
// Modified  28-Nov-2001  By Edward Benson - Minor changes - DbxOodbc v 1.01
// Modified  05-Dec-2001  By Edward Benson - Minor changes - DbxOodbc v 1.02
// Modified  06-Dec-2001  By Edward Benson - Support Kylix - DbxOodbc v 1.03
// Modified  22-Jun-2002  By Edward Benson - UL to ULONG   - DbxOodbc v 1.05
// Modified  01-Nov-2002  By Edward Benson - DbxOodbc v 2.01
//   Bojnourdi Kaikavous
//     Support Linux (MSWINDOWS=stdcall Linux=cdecl)
//   Vadim Lopushansky
//     $B-
//   Edward Benson
//     Change const xUL to ULONG(x) (former no longer valid for Delphi 6 SP 1)
//     Various API calls corrected for Delphi
//     Support Borland C++ Builder
// Modified  2002-04-04   Edward Benson    - DbxOodbc v 2.05
//     Type names reformatted to Delphi standard
// Modified  2002-04-16   Edward Benson    - DbxOodbc v 2.06
//     Added non-overlaoded versions of SqlColAttribute, SQLGetInfo
//
//   Edward Benson
//     Borland C++ Builder
//     To avoid linker errors with BCB, you must add ODBC32.LIB to your project.
//     You can create ODBC32.LIB yourself using IMPLIB utility (Import Library)
//     IMPLIB ODBC32.LIB C:\WINNT\SYSTEM32\ODBC32.DLL
//     or use the ODBC32.LIB that I created.
//     But don't forget to also add it to your project.
//
// Modified  2004-05-31   Vadim V. Lopushansky - DbxOodbc v 3.000
//
//
//**************************************************************************

{$INCLUDE DbxOpenOdbc.inc} // <-: define option "DynamicOdbcImport".

interface

uses
  SysUtils, SysConst, SyncObjs {$IFNDEF LINUX}, Windows{$ENDIF};

//##########################################################################
// sqltypes.h interface section starts here
// (N.B. no implementation section for sqltypes.h)
//##########################################################################

//******************************************************************
// SQLTYPES.H - This file defines the types used in ODBC
//
// (C) Copyright 1995-1998 By Microsoft Corp.
//
// Created 04/10/95 for 2.50 specification
// Updated 12/11/95 for 3.00 specification
//********************************************************************

// Introduced for convenience
type
  TSqlState = array[0..5] of AnsiChar;
  PSqlState = PAnsiChar;

const
  ODBCVER = $0351;

  // API declaration data types
type
{$EXTERNALSYM SQLCHAR}
  SqlChar = Byte;
  PSqlChar = ^SqlChar;
{$EXTERNALSYM SQLSCHAR}
  SqlSChar = Char;
{$EXTERNALSYM SQLDATE}
  SqlDate = Byte; // ??? Defined in DBXpress SQLDATE = Longint;
{$EXTERNALSYM SQLDECIMAL}
  SqlDecimal = Byte;
{$EXTERNALSYM SQLDOUBLE}
  SqlDouble = Double;
{$EXTERNALSYM SQLFLOAT}
  SqlFloat = Double;
{$EXTERNALSYM SQLINTEGER}
  SqlInteger = Longint;
  PSqlInteger = ^SqlInteger;
{$EXTERNALSYM SQLNUMERIC}
  SqlNumeric = Byte;
{$EXTERNALSYM SQLPOINTER}
  SqlPointer = Pointer;
  PSqlPointer = ^SqlPointer;
{$EXTERNALSYM SQLREAL}
  SqlReal = Single;
{$EXTERNALSYM SQLSMALLINT}
  SqlSmallint = Smallint;
  PSqlSmallint = ^SqlSmallint;
{$EXTERNALSYM SQLUSMALLINT}
  SqlUSmallint = Word;
  PSqlUSmallint = ^SqlUSmallint;
{$EXTERNALSYM SQLTIME}
  SqlTime = Byte; // ??? Defined in DBXpress SQLTIME = Longint;
{$EXTERNALSYM SQLTIMESTAMP}
  SqlTimestamp = Byte;
{$EXTERNALSYM SQLVARCHAR}
  SqlVarchar = Byte;

  // function return type
{$EXTERNALSYM SQLRETURN}
  SqlReturn = SqlSmallint;

  // SQL Handle types
{$EXTERNALSYM SQLHANDLE}
  SqlHandle = Pointer;
  PSqlHandle = ^SqlHandle;
{$EXTERNALSYM SQLHENV}
  SqlHEnv = Pointer;
  PSqlHEnv = ^SqlHEnv;
{$EXTERNALSYM SQLHDBC}
  SqlHDbc = Pointer;
  PSqlHDbc = ^SqlHDbc;
{$EXTERNALSYM SQLHSTMT}
  SqlHStmt = Pointer;
  PSqlHStmt = ^SqlHStmt;
{$EXTERNALSYM SQLHDESC}
  SqlHDesc = Pointer;
  PSqlHDesc = ^SqlHDesc;

  // SQL portable types
{$EXTERNALSYM UCHAR}
  UChar = Byte;
{$EXTERNALSYM SCHAR}
  SChar = Char;
{$EXTERNALSYM SDWORD}
  SDword = Longint;
{$EXTERNALSYM SWORD}
  SWord = Smallint;
{$EXTERNALSYM UDWORD}
  UDword = Longint;
{$EXTERNALSYM UWORD}
  UWord = Word;
  PUWord = ^UWord;
{$EXTERNALSYM SQLUINTEGER}
  SqlUInteger = UDword;
  PSqlUInteger = ^SqlUInteger;
{$EXTERNALSYM SLONG}
  SLong = Longint;
{$EXTERNALSYM SSHORT}
  SShort = Smallint;
{$EXTERNALSYM ULONG}
  ULong = Longint;
{$EXTERNALSYM USHORT}
  UShort = Word;
{$EXTERNALSYM SDOUBLE}
  SDouble = Double;
{$EXTERNALSYM LDOUBLE}
  LDouble = Double;
{$EXTERNALSYM SFLOAT}
  SFloat = Single;
{$EXTERNALSYM PTR}
  Ptr = Pointer;

{$EXTERNALSYM HENV}
  HEnv = Pointer;
{$EXTERNALSYM HDBC}
  HDbc = Pointer;
{$EXTERNALSYM HSTMT}
  HStmt = Pointer;

{$EXTERNALSYM RETCODE}
  Retcode = Smallint;

{$EXTERNALSYM SQLHWND}
  //  SQLHWND = HWND;
  SqlHWnd = Longword;

  // transfer types for DATE, TIME, TIMESTAMP
{$EXTERNALSYM tagDATE_STRUCT}
  tagDATE_STRUCT = packed record
    Year: SqlSmallint;
    Month: SqlUSmallint;
    Day: SqlUSmallint;
  end;
  PSqlDateStruct = ^TSqlDateStruct;
  TSqlDateStruct = tagDATE_STRUCT;
{$EXTERNALSYM SQL_DATE_STRUCT}
  SQL_DATE_STRUCT = tagDATE_STRUCT;

{$EXTERNALSYM tagTIME_STRUCT}
  tagTIME_STRUCT = packed record
    Hour: SqlUSmallint;
    Minute: SqlUSmallint;
    Second: SqlUSmallint;
  end;
  PSqlTimeStruct = ^TSqlTimeStruct;
  TSqlTimeStruct = tagTIME_STRUCT;
{$EXTERNALSYM SQL_TIME_STRUCT}
  SQL_TIME_STRUCT = tagTIME_STRUCT;

{$EXTERNALSYM tagTIMESTAMP_STRUCT}
  tagTIMESTAMP_STRUCT = packed record
    Year: SqlSmallint;
    Month: SqlUSmallint;
    Day: SqlUSmallint;
    Hour: SqlUSmallint;
    Minute: SqlUSmallint;
    Second: SqlUSmallint;
    Fraction: SqlUInteger;
  end;

{$EXTERNALSYM SQL_TIMESTAMP_STRUCT}
  SQL_TIMESTAMP_STRUCT = tagTIMESTAMP_STRUCT;
  POdbcTimestamp = ^TOdbcTimestamp;
  TOdbcTimestamp = tagTIMESTAMP_STRUCT;

  // enumerations for DATETIME_INTERVAL_SUBCODE values for interval data types
  // these values are from SQL-92
{$EXTERNALSYM SQLINTERVAL}
  SqlInterval = (
    SQL_IS_DUMMY {placeholder for 0},
    SQL_IS_YEAR {= 1},
    SQL_IS_MONTH {= 2},
    SQL_IS_DAY {= 3},
    SQL_IS_HOUR {= 4},
    SQL_IS_MINUTE {= 5},
    SQL_IS_SECOND {= 6},
    SQL_IS_YEAR_TO_MONTH {= 7},
    SQL_IS_DAY_TO_HOUR {= 8},
    SQL_IS_DAY_TO_MINUTE {= 9},
    SQL_IS_DAY_TO_SECOND {= 10},
    SQL_IS_HOUR_TO_MINUTE {= 11},
    SQL_IS_HOUR_TO_SECOND {= 12},
    SQL_IS_MINUTE_TO_SECOND {= 13});
  ESqlInterval = SqlInterval;

{$EXTERNALSYM tagSQL_YEAR_MONTH}
  tagSQL_YEAR_MONTH = packed record
    Year: SqlUInteger;
    Month: SqlUInteger;
  end;
  TSqlYearMonth = tagSQL_YEAR_MONTH;

{$EXTERNALSYM tagSQL_DAY_SECOND}
  tagSQL_DAY_SECOND = packed record
    Day: SqlUInteger;
    Hour: SqlUInteger;
    Minute: SqlUInteger;
    Second: SqlUInteger;
    Fraction: SqlUInteger;
  end;
  TSqlDaySecond = tagSQL_DAY_SECOND;

{$EXTERNALSYM tagSQL_INTERVAL_STRUCT}
  tagSQL_INTERVAL_STRUCT = packed record
    interval_type: SqlInterval;
    interval_sign: SqlSmallint;
    case ESqlInterval of
      SQL_IS_YEAR_TO_MONTH: (YearMonth: TSqlYearMonth);
      SQL_IS_DAY_TO_SECOND: (DaySecond: TSqlDaySecond);
  end;
  TSqlInterval = tagSQL_INTERVAL_STRUCT;

{$EXTERNALSYM ODBCINT64}
  OdbcInt64 = Int64;
{$EXTERNALSYM SQLBIGINT}
  SqlBigint = OdbcInt64;
{$EXTERNALSYM SQLUBIGINT}
  SqlUBigint = OdbcInt64;

  // internal representation of numeric data type
const
{$EXTERNALSYM SQL_MAX_NUMERIC_LEN}
  SQL_MAX_NUMERIC_LEN = 16;

type
{$EXTERNALSYM tagSQL_NUMERIC_STRUCT}
  tagSQL_NUMERIC_STRUCT = packed record
    Precision: SqlChar;
    Scale: SqlSChar;
    Sign: SqlChar; {= 1 if positive, 0 if negative }
    Val: array[0..SQL_MAX_NUMERIC_LEN - 1] of SqlChar;
  end;

{$EXTERNALSYM SQLGUID}
  SqlGuid = TGUID;

{$EXTERNALSYM BOOKMARK}
  Bookmark = Longint;

  //  SQLWCHAR = Word;
{$EXTERNALSYM SQLWCHAR}
  SqlWChar = WideChar; { WideCharacter - word-sized Unicode character }
  PSqlWChar = ^SqlWChar;

{$EXTERNALSYM SQLTCHAR}
{$IFDEF UNICODE}
  SqlTChar = SqlWChar;
{$ELSE}
  SqlTChar = SqlChar;
{$ENDIF} {UNICODE}

  //##########################################################################
  // sqltypes.h interface section ends here
  // (no implemetation section for sqltypes.h)
  //##########################################################################

  //##########################################################################
  // sql.h interface part starts here
  //##########################################################################

  //****************************************************************
  // SQL.H - This is the the main include for ODBC Core functions.
  //
  // preconditions:
  // INCLUDE "windows.h"
  //
  // (C) Copyright 1990 - 1998 By Microsoft Corp.
  //
  // Updated 5/12/93 for 2.00 specification
  // Updated 5/23/94 for 2.01 specification
  // Updated 11/10/94 for 2.10 specification
  // Updated 04/10/95 for 2.50 specification
  // Updated 6/6/95 for 3.00 specification
  // Updated 10/22/97 for 3.51 specification
  //********************************************************************

  // All version-specific IFDEFs removed, and assume ODBC Version 3.51

const
  // special length/indicator values
  SQL_NULL_DATA = (-1); //??? Defined in DBXpress: SQL_NULL_DATA = 100;
  SQL_DATA_AT_EXEC = (-2);

  // return values from functions
  SQL_SUCCESS = 0; //??? Defined in DBXpress: SQL_SUCCESS = $0000;
  SQL_SUCCESS_WITH_INFO = 1;
  SQL_NO_DATA = 100;
  SQL_ERROR = (-1); //??? Defined in DBXpress: SQL_ERROR = -1;
  SQL_INVALID_HANDLE = (-2);
  SQL_STILL_EXECUTING = 2;
  SQL_NEED_DATA = 99;

  // MACRO
  // test for SQL_SUCCESS or SQL_SUCCESS_WITH_INFO
function SQL_SUCCEEDED(const rc: SqlReturn): Boolean;

const
  // flags for null-terminated string
  SQL_NTS = (-3);
  SQL_NTSL = (-3);

  // maximum message length
  SQL_MAX_MESSAGE_LENGTH = 512;

  // date/time length constants
  SQL_DATE_LEN = 10;
  SQL_TIME_LEN = 8; // add P+1 if precision is nonzero
  SQL_TIMESTAMP_LEN = 19; // add P+1 if precision is nonzero

  // handle type identifiers
  SQL_HANDLE_ENV = 1;
  SQL_HANDLE_DBC = 2;
  SQL_HANDLE_STMT = 3;
  SQL_HANDLE_DESC = 4;

  // environment attribute
  SQL_ATTR_OUTPUT_NTS = 10001;

  // connection attributes
  SQL_ATTR_AUTO_IPD = 10001;
  SQL_ATTR_METADATA_ID = 10014;

  // statement attributes
  SQL_ATTR_APP_ROW_DESC = 10010;
  SQL_ATTR_APP_PARAM_DESC = 10011;
  SQL_ATTR_IMP_ROW_DESC = 10012;
  SQL_ATTR_IMP_PARAM_DESC = 10013;
  SQL_ATTR_CURSOR_SCROLLABLE = (-1);
  SQL_ATTR_CURSOR_SENSITIVITY = (-2);

  // SQL_ATTR_CURSOR_SCROLLABLE values
  SQL_NONSCROLLABLE = 0;
  SQL_SCROLLABLE = 1;

  // identifiers of fields in the SQL descriptor
  SQL_DESC_COUNT = 1001;
  SQL_DESC_TYPE = 1002;
  SQL_DESC_LENGTH = 1003;
  SQL_DESC_OCTET_LENGTH_PTR = 1004;
  SQL_DESC_PRECISION = 1005;
  SQL_DESC_SCALE = 1006;
  SQL_DESC_DATETIME_INTERVAL_CODE = 1007;
  SQL_DESC_NULLABLE = 1008;
  SQL_DESC_INDICATOR_PTR = 1009;
  SQL_DESC_DATA_PTR = 1010;
  SQL_DESC_NAME = 1011;
  SQL_DESC_UNNAMED = 1012;
  SQL_DESC_OCTET_LENGTH = 1013;
  SQL_DESC_ALLOC_TYPE = 1099;

  // identifiers of fields in the diagnostics area*
  SQL_DIAG_RETURNCODE = 1;
  SQL_DIAG_NUMBER = 2;
  SQL_DIAG_ROW_COUNT = 3;
  SQL_DIAG_SQLSTATE = 4;
  SQL_DIAG_NATIVE = 5;
  SQL_DIAG_MESSAGE_TEXT = 6;
  SQL_DIAG_DYNAMIC_FUNCTION = 7;
  SQL_DIAG_CLASS_ORIGIN = 8;
  SQL_DIAG_SUBCLASS_ORIGIN = 9;
  SQL_DIAG_CONNECTION_NAME = 10;
  SQL_DIAG_SERVER_NAME = 11;
  SQL_DIAG_DYNAMIC_FUNCTION_CODE = 12;

  // dynamic function codes
  SQL_DIAG_ALTER_DOMAIN = 3;
  SQL_DIAG_ALTER_TABLE = 4;
  SQL_DIAG_CALL = 7;
  SQL_DIAG_CREATE_ASSERTION = 6;
  SQL_DIAG_CREATE_CHARACTER_SET = 8;
  SQL_DIAG_CREATE_COLLATION = 10;
  SQL_DIAG_CREATE_DOMAIN = 23;
  SQL_DIAG_CREATE_INDEX = (-1);
  SQL_DIAG_CREATE_SCHEMA = 64;
  SQL_DIAG_CREATE_TABLE = 77;
  SQL_DIAG_CREATE_TRANSLATION = 79;
  SQL_DIAG_CREATE_VIEW = 84;
  SQL_DIAG_DELETE_WHERE = 19;
  SQL_DIAG_DROP_ASSERTION = 24;
  SQL_DIAG_DROP_CHARACTER_SET = 25;
  SQL_DIAG_DROP_COLLATION = 26;
  SQL_DIAG_DROP_DOMAIN = 27;
  SQL_DIAG_DROP_INDEX = (-2);
  SQL_DIAG_DROP_SCHEMA = 31;
  SQL_DIAG_DROP_TABLE = 32;
  SQL_DIAG_DROP_TRANSLATION = 33;
  SQL_DIAG_DROP_VIEW = 36;
  SQL_DIAG_DYNAMIC_DELETE_CURSOR = 38;
  SQL_DIAG_DYNAMIC_UPDATE_CURSOR = 81;
  SQL_DIAG_GRANT = 48;
  SQL_DIAG_INSERT = 50;
  SQL_DIAG_REVOKE = 59;
  SQL_DIAG_SELECT_CURSOR = 85;
  SQL_DIAG_UNKNOWN_STATEMENT = 0;
  SQL_DIAG_UPDATE_WHERE = 82;

  // SQL data type codes
  SQL_UNKNOWN_TYPE = 0;
  SQL_CHAR = 1;
  SQL_NUMERIC = 2;
  SQL_DECIMAL = 3;
  SQL_INTEGER = 4;
  SQL_SMALLINT = 5;
  SQL_FLOAT = 6;
  SQL_REAL = 7;
  SQL_DOUBLE = 8;
  SQL_DATETIME = 9;
  SQL_VARCHAR = 12;

  // One-parameter shortcuts for date/time data types
  SQL_TYPE_DATE = 91;
  SQL_TYPE_TIME = 92;
  SQL_TYPE_TIMESTAMP = 93;

  // Statement attribute values for cursor sensitivity
  SQL_UNSPECIFIED = 0;
  SQL_INSENSITIVE = 1;
  SQL_SENSITIVE = 2;

  // GetTypeInfo() request for all data types
  SQL_ALL_TYPES = 0;

  // Default conversion code for SQLBindCol(), SQLBindParam() and SQLGetData()
  SQL_DEFAULT = 99;

  // SQLGetData() code indicating that the application row descriptor
  // specifies the data type
  SQL_ARD_TYPE = (-99);

  // SQL date/time type subcodes
  SQL_CODE_DATE = 1;
  SQL_CODE_TIME = 2;
  SQL_CODE_TIMESTAMP = 3;

  // CLI option values
  SQL_FALSE = 0;
  SQL_TRUE = 1;

  // values of NULLABLE field in descriptor
  SQL_NO_NULLS = 0;
  SQL_NULLABLE = 1;

  // Value returned by SQLGetTypeInfo() to denote that it is
  // not known whether or not a data type supports null values.
  SQL_NULLABLE_UNKNOWN = 2;

  // Values returned by SQLGetTypeInfo() to show WHERE clause supported
  SQL_PRED_NONE = 0;
const
  SQL_PRED_CHAR = 1;
const
  SQL_PRED_BASIC = 2;

  // values of UNNAMED field in descriptor
  SQL_NAMED = 0;
  SQL_UNNAMED = 1;

  // values of ALLOC_TYPE field in descriptor
  SQL_DESC_ALLOC_AUTO = 1;
  SQL_DESC_ALLOC_USER = 2;

  // FreeStmt() options
  SQL_CLOSE = 0;
  SQL_DROP = 1;
  SQL_UNBIND = 2;
  SQL_RESET_PARAMS = 3;

  // Codes used for FetchOrientation in SQLFetchScroll(), and in SQLDataSources()
  SQL_FETCH_NEXT = 1;
  SQL_FETCH_FIRST = 2;

  // Other codes used for FetchOrientation in SQLFetchScroll()
  SQL_FETCH_LAST = 3;
  SQL_FETCH_PRIOR = 4;
  SQL_FETCH_ABSOLUTE = 5;
  SQL_FETCH_RELATIVE = 6;

  // SQLEndTran() options
  SQL_COMMIT = 0;
  SQL_ROLLBACK = 1;

  // null handles returned by SQLAllocHandle()
  SQL_NULL_HENV = SqlHandle(0);
  SQL_NULL_HDBC = SqlHandle(0);
  SQL_NULL_HSTMT = SqlHandle(0);
  SQL_NULL_HDESC = SqlHandle(0);

  // null handle used in place of parent handle when allocating HENV
  SQL_NULL_HANDLE = SqlHandle(0);

  // Values that may appear in the result set of SQLSpecialColumns()
  SQL_SCOPE_CURROW = 0;
  SQL_SCOPE_TRANSACTION = 1;
  SQL_SCOPE_SESSION = 2;
  SQL_PC_UNKNOWN = 0;
  SQL_PC_NON_PSEUDO = 1;
  SQL_PC_PSEUDO = 2;

  // Reserved value for the IdentifierType argument of SQLSpecialColumns()
  SQL_ROW_IDENTIFIER = 1;

  // Reserved values for UNIQUE argument of SQLStatistics()
  SQL_INDEX_UNIQUE = 0;
  SQL_INDEX_ALL = 1;

  // Values that may appear in the result set of SQLStatistics()
  SQL_INDEX_CLUSTERED = 1;
  SQL_INDEX_HASHED = 2;
  SQL_INDEX_OTHER = 3;

  // SQLGetFunctions() values to identify ODBC APIs
  SQL_API_SQLALLOCCONNECT = 1;
  SQL_API_SQLALLOCENV = 2;
  SQL_API_SQLALLOCHANDLE = 1001;
  SQL_API_SQLALLOCSTMT = 3;
  SQL_API_SQLBINDCOL = 4;
  SQL_API_SQLBINDPARAM = 1002;
  SQL_API_SQLCANCEL = 5;
  SQL_API_SQLCLOSECURSOR = 1003;
  SQL_API_SQLCOLATTRIBUTE = 6;
  SQL_API_SQLCOLUMNS = 40;
  SQL_API_SQLCONNECT = 7;
  SQL_API_SQLCOPYDESC = 1004;
  SQL_API_SQLDATASOURCES = 57;
  SQL_API_SQLDESCRIBECOL = 8;
  SQL_API_SQLDISCONNECT = 9;
  SQL_API_SQLENDTRAN = 1005;
  SQL_API_SQLERROR = 10;
  SQL_API_SQLEXECDIRECT = 11;
  SQL_API_SQLEXECUTE = 12;
  SQL_API_SQLFETCH = 13;
  SQL_API_SQLFETCHSCROLL = 1021;
  SQL_API_SQLFREECONNECT = 14;
  SQL_API_SQLFREEENV = 15;
  SQL_API_SQLFREEHANDLE = 1006;
  SQL_API_SQLFREESTMT = 16;
  SQL_API_SQLGETCONNECTATTR = 1007;
  SQL_API_SQLGETCONNECTOPTION = 42;
  SQL_API_SQLGETCURSORNAME = 17;
  SQL_API_SQLGETDATA = 43;
  SQL_API_SQLGETDESCFIELD = 1008;
  SQL_API_SQLGETDESCREC = 1009;
  SQL_API_SQLGETDIAGFIELD = 1010;
  SQL_API_SQLGETDIAGREC = 1011;
  SQL_API_SQLGETENVATTR = 1012;
  SQL_API_SQLGETFUNCTIONS = 44;
  SQL_API_SQLGETINFO = 45;
  SQL_API_SQLGETSTMTATTR = 1014;
  SQL_API_SQLGETSTMTOPTION = 46;
  SQL_API_SQLGETTYPEINFO = 47;
  SQL_API_SQLNUMRESULTCOLS = 18;
  SQL_API_SQLPARAMDATA = 48;
  SQL_API_SQLPREPARE = 19;
  SQL_API_SQLPUTDATA = 49;
  SQL_API_SQLROWCOUNT = 20;
  SQL_API_SQLSETCONNECTATTR = 1016;
  SQL_API_SQLSETCONNECTOPTION = 50;
  SQL_API_SQLSETCURSORNAME = 21;
  SQL_API_SQLSETDESCFIELD = 1017;
  SQL_API_SQLSETDESCREC = 1018;
  SQL_API_SQLSETENVATTR = 1019;
  SQL_API_SQLSETPARAM = 22;
  SQL_API_SQLSETSTMTATTR = 1020;
  SQL_API_SQLSETSTMTOPTION = 51;
  SQL_API_SQLSPECIALCOLUMNS = 52;
  SQL_API_SQLSTATISTICS = 53;
  SQL_API_SQLTABLES = 54;
  SQL_API_SQLTRANSACT = 23;

  // Information requested by SQLGetInfo()
  SQL_MAX_DRIVER_CONNECTIONS = 0;
  SQL_MAXIMUM_DRIVER_CONNECTIONS = SQL_MAX_DRIVER_CONNECTIONS;
  SQL_MAX_CONCURRENT_ACTIVITIES = 1;
  SQL_MAXIMUM_CONCURRENT_ACTIVITIES = SQL_MAX_CONCURRENT_ACTIVITIES;
  SQL_DATA_SOURCE_NAME = 2;
  SQL_FETCH_DIRECTION = 8;
  SQL_SERVER_NAME = 13;
  SQL_SEARCH_PATTERN_ESCAPE = 14;
  SQL_DBMS_NAME = 17;
  SQL_DBMS_VER = 18;
  SQL_ACCESSIBLE_TABLES = 19;
  SQL_ACCESSIBLE_PROCEDURES = 20;
  SQL_CURSOR_COMMIT_BEHAVIOR = 23;
  SQL_DATA_SOURCE_READ_ONLY = 25;
  SQL_DEFAULT_TXN_ISOLATION = 26;
  SQL_IDENTIFIER_CASE = 28;
  SQL_IDENTIFIER_QUOTE_CHAR = 29;
  SQL_MAX_COLUMN_NAME_LEN = 30;
  SQL_MAXIMUM_COLUMN_NAME_LENGTH = SQL_MAX_COLUMN_NAME_LEN;
  SQL_MAX_CURSOR_NAME_LEN = 31;
  SQL_MAXIMUM_CURSOR_NAME_LENGTH = SQL_MAX_CURSOR_NAME_LEN;
  SQL_MAX_SCHEMA_NAME_LEN = 32;
  SQL_MAXIMUM_SCHEMA_NAME_LENGTH = SQL_MAX_SCHEMA_NAME_LEN;
  SQL_MAX_CATALOG_NAME_LEN = 34;
  SQL_MAXIMUM_CATALOG_NAME_LENGTH = SQL_MAX_CATALOG_NAME_LEN;
  SQL_MAX_TABLE_NAME_LEN = 35;
  SQL_SCROLL_CONCURRENCY = 43;
  SQL_TXN_CAPABLE = 46;
  SQL_TRANSACTION_CAPABLE = SQL_TXN_CAPABLE;
  SQL_USER_NAME = 47;
  SQL_TXN_ISOLATION_OPTION = 72;
  SQL_TRANSACTION_ISOLATION_OPTION = SQL_TXN_ISOLATION_OPTION;
  SQL_INTEGRITY = 73;
  SQL_GETDATA_EXTENSIONS = 81;
  SQL_NULL_COLLATION = 85;
  SQL_ALTER_TABLE = 86;
  SQL_ORDER_BY_COLUMNS_IN_SELECT = 90;
  SQL_SPECIAL_CHARACTERS = 94;
  SQL_MAX_COLUMNS_IN_GROUP_BY = 97;
  SQL_MAXIMUM_COLUMNS_IN_GROUP_BY = SQL_MAX_COLUMNS_IN_GROUP_BY;
  SQL_MAX_COLUMNS_IN_INDEX = 98;
  SQL_MAXIMUM_COLUMNS_IN_INDEX = SQL_MAX_COLUMNS_IN_INDEX;
  SQL_MAX_COLUMNS_IN_ORDER_BY = 99;
  SQL_MAXIMUM_COLUMNS_IN_ORDER_BY = SQL_MAX_COLUMNS_IN_ORDER_BY;
  SQL_MAX_COLUMNS_IN_SELECT = 100;
  SQL_MAXIMUM_COLUMNS_IN_SELECT = SQL_MAX_COLUMNS_IN_SELECT;
  SQL_MAX_COLUMNS_IN_TABLE = 101;
  SQL_MAX_INDEX_SIZE = 102;
  SQL_MAXIMUM_INDEX_SIZE = SQL_MAX_INDEX_SIZE;
  SQL_MAX_ROW_SIZE = 104;
  SQL_MAXIMUM_ROW_SIZE = SQL_MAX_ROW_SIZE;
  SQL_MAX_STATEMENT_LEN = 105;
  SQL_MAXIMUM_STATEMENT_LENGTH = SQL_MAX_STATEMENT_LEN;
  SQL_MAX_TABLES_IN_SELECT = 106;
  SQL_MAXIMUM_TABLES_IN_SELECT = SQL_MAX_TABLES_IN_SELECT;
  SQL_MAX_USER_NAME_LEN = 107;
  SQL_MAXIMUM_USER_NAME_LENGTH = SQL_MAX_USER_NAME_LEN;
  SQL_OJ_CAPABILITIES = 115;
  SQL_OUTER_JOIN_CAPABILITIES = SQL_OJ_CAPABILITIES;
  SQL_XOPEN_CLI_YEAR = 10000;
  SQL_CURSOR_SENSITIVITY = 10001;
  SQL_DESCRIBE_PARAMETER = 10002;
  SQL_CATALOG_NAME = 10003;
  SQL_COLLATION_SEQ = 10004;
  SQL_MAX_IDENTIFIER_LEN = 10005;
  SQL_MAXIMUM_IDENTIFIER_LENGTH = SQL_MAX_IDENTIFIER_LEN;

  // SQL_ALTER_TABLE bitmasks
  SQL_AT_ADD_COLUMN = $00000001;
  SQL_AT_DROP_COLUMN = $00000002;
  SQL_AT_ADD_CONSTRAINT = $00000008;

  // The following bitmasks are ODBC extensions and defined in sqlext.h
  SQL_AT_COLUMN_SINGLE = $00000020;
  SQL_AT_ADD_COLUMN_DEFAULT = $00000040;
  SQL_AT_ADD_COLUMN_COLLATION = $00000080;
  SQL_AT_SET_COLUMN_DEFAULT = $00000100;
  SQL_AT_DROP_COLUMN_DEFAULT = $00000200;
  SQL_AT_DROP_COLUMN_CASCADE = $00000400;
  SQL_AT_DROP_COLUMN_RESTRICT = $00000800;
  SQL_AT_ADD_TABLE_CONSTRAINT = $00001000;
  SQL_AT_DROP_TABLE_CONSTRAINT_CASCADE = $00002000;
  SQL_AT_DROP_TABLE_CONSTRAINT_RESTRICT = $00004000;
  SQL_AT_CONSTRAINT_NAME_DEFINITION = $00008000;
  SQL_AT_CONSTRAINT_INITIALLY_DEFERRED = $00010000;
  SQL_AT_CONSTRAINT_INITIALLY_IMMEDIATE = $00020000;
  SQL_AT_CONSTRAINT_DEFERRABLE = $00040000;
  SQL_AT_CONSTRAINT_NON_DEFERRABLE = $00080000;

  // SQL_ASYNC_MODE values
  SQL_AM_NONE = 0;
  SQL_AM_CONNECTION = 1;
  SQL_AM_STATEMENT = 2;

  // SQL_CURSOR_COMMIT_BEHAVIOR values
  SQL_CB_DELETE = 0;
  SQL_CB_CLOSE = 1;
  SQL_CB_PRESERVE = 2;

  // SQL_FETCH_DIRECTION bitmasks
  SQL_FD_FETCH_NEXT = $00000001;
  SQL_FD_FETCH_FIRST = $00000002;
  SQL_FD_FETCH_LAST = $00000004;
  SQL_FD_FETCH_PRIOR = $00000008;
  SQL_FD_FETCH_ABSOLUTE = $00000010;
  SQL_FD_FETCH_RELATIVE = $00000020;

  // SQL_GETDATA_EXTENSIONS bitmasks
  SQL_GD_ANY_COLUMN = $00000001;
  SQL_GD_ANY_ORDER = $00000002;

  // SQL_IDENTIFIER_CASE values
  SQL_IC_UPPER = 1;
  SQL_IC_LOWER = 2;
  SQL_IC_SENSITIVE = 3;
  SQL_IC_MIXED = 4;

  // SQL_OJ_CAPABILITIES bitmasks
  // NB: this means 'outer join', not what you may be thinking
  SQL_OJ_LEFT = $00000001;
  SQL_OJ_RIGHT = $00000002;
  SQL_OJ_FULL = $00000004;
  SQL_OJ_NESTED = $00000008;
  SQL_OJ_NOT_ORDERED = $00000010;
  SQL_OJ_INNER = $00000020;
  SQL_OJ_ALL_COMPARISON_OPS = $00000040;

  // SQL_SCROLL_CONCURRENCY bitmasks
  SQL_SCCO_READ_ONLY = $00000001;
  SQL_SCCO_LOCK = $00000002;
  SQL_SCCO_OPT_ROWVER = $00000004;
  SQL_SCCO_OPT_VALUES = $00000008;

  // SQL_TXN_CAPABLE values
  SQL_TC_NONE = 0;
  SQL_TC_DML = 1;
  SQL_TC_ALL = 2;
  SQL_TC_DDL_COMMIT = 3;
  SQL_TC_DDL_IGNORE = 4;

  // SQL_TXN_ISOLATION_OPTION bitmasks
  SQL_TXN_READ_UNCOMMITTED = $00000001;
  SQL_TRANSACTION_READ_UNCOMMITTED = SQL_TXN_READ_UNCOMMITTED;
  SQL_TXN_READ_COMMITTED = $00000002;
  SQL_TRANSACTION_READ_COMMITTED = SQL_TXN_READ_COMMITTED;
  SQL_TXN_REPEATABLE_READ = $00000004;
  SQL_TRANSACTION_REPEATABLE_READ = SQL_TXN_REPEATABLE_READ;
  SQL_TXN_SERIALIZABLE = $00000008;
  SQL_TRANSACTION_SERIALIZABLE = SQL_TXN_SERIALIZABLE;

  // SQL_NULL_COLLATION values
  SQL_NC_HIGH = 0;
  SQL_NC_LOW = 1;

{$IFDEF DynamicOdbcImport}
type
  TSQLAllocConnect = function(
{$ELSE}
function SQLAllocConnect(
{$ENDIF}
  EnvironmentHandle: SqlHEnv;
  var ConnectionHandle: SqlHDbc
  ): SqlReturn{$IFDEF MSWINDOWS} stdcall{$ELSE} cdecl{$ENDIF};

{$IFDEF DynamicOdbcImport}
TSQLAllocEnv = function(
{$ELSE}
function SQLAllocEnv(
{$ENDIF}
  var EnvironmentHandle: SqlHEnv
  ): SqlReturn{$IFDEF MSWINDOWS} stdcall{$ELSE} cdecl{$ENDIF};

{$IFDEF DynamicOdbcImport}
TSQLAllocHandle = function(
{$ELSE}
function SQLAllocHandle(
{$ENDIF}
  HandleType: SqlSmallint;
  InputHandle: SqlHandle;
  var OutputHandle: SqlHandle
  ): SqlReturn{$IFDEF MSWINDOWS} stdcall{$ELSE} cdecl{$ENDIF};

{$IFDEF DynamicOdbcImport}
type
  TSQLAllocStmt = function(
{$ELSE}
function SQLAllocStmt(
{$ENDIF}
  ConnectionHandle: SqlHDbc;
  var StatementHandle: SqlHStmt
  ): SqlReturn{$IFDEF MSWINDOWS} stdcall{$ELSE} cdecl{$ENDIF};

{$IFDEF DynamicOdbcImport}
TSQLBindCol = function(
{$ELSE}
function SQLBindCol(
{$ENDIF}
  StatementHandle: SqlHStmt;
  ColumnNumber: SqlUSmallint;
  TargetType: SqlSmallint;
  TargetValue: SqlPointer;
  BufferLength: SqlInteger;
  StrLen_or_Ind: PSqlInteger
  ): SqlReturn{$IFDEF MSWINDOWS} stdcall{$ELSE} cdecl{$ENDIF};

{$IFDEF DynamicOdbcImport}
TSQLBindParam = function(
{$ELSE}
function SQLBindParam(
{$ENDIF}
  StatementHandle: SqlHStmt;
  ParameterNumber: SqlUSmallint;
  ValueType: SqlSmallint;
  ParameterType: SqlSmallint;
  LengthPrecision: SqlUInteger;
  ParameterScale: SqlSmallint;
  ParameterValue: SqlPointer;
  var StrLen_or_Ind: SqlInteger
  ): SqlReturn{$IFDEF MSWINDOWS} stdcall{$ELSE} cdecl{$ENDIF};

{$IFDEF DynamicOdbcImport}
TSQLCancel = function(
{$ELSE}
function SQLCancel(
{$ENDIF}
  StatementHandle: SqlHStmt
  ): SqlReturn{$IFDEF MSWINDOWS} stdcall{$ELSE} cdecl{$ENDIF};

{$IFDEF DynamicOdbcImport}
TSQLCloseCursor = function(
{$ELSE}
function SQLCloseCursor(
{$ENDIF}
  StatementHandle: SqlHStmt
  ): SqlReturn{$IFDEF MSWINDOWS} stdcall{$ELSE} cdecl{$ENDIF};

// SQLColAttribute is overloaded

{$IFDEF DynamicOdbcImport}
TSQLColAttribute = function(
{$ELSE}
function SQLColAttribute(
{$ENDIF}
  StatementHandle: SqlHStmt;
  ColumnNumber: SqlUSmallint;
  FieldIdentifier: SqlUSmallint;
  CharacterAttribute: SqlPointer;
  BufferLength: SqlSmallint;
  StringLength: pSqlSmallint;
  NumericAttributePtr: SqlPointer
  ): SqlReturn{$IFDEF MSWINDOWS} stdcall{$ELSE} cdecl{$ENDIF};

{$IFDEF DynamicOdbcImport}
TSQLColAttributeString = function(
{$ELSE}
function SQLColAttributeString(
{$ENDIF}
// Overloaded version for String attributes
  StatementHandle: SqlHStmt;
  ColumnNumber: SqlUSmallint;
  FieldIdentifier: SqlUSmallint;
  CharacterAttribute: SqlPointer;
  BufferLength: SqlSmallint;
  var StringLength: SqlSmallint;
  NumericAttribute: SqlPointer
  ): SqlReturn{$IFDEF MSWINDOWS} stdcall{$ELSE} cdecl{$ENDIF};

{$IFDEF DynamicOdbcImport}
TSQLColAttributeInt = function(
{$ELSE}
function SQLColAttributeInt(
{$ENDIF}
// Overloaded version for Integer attributes
  StatementHandle: SqlHStmt;
  ColumnNumber: SqlUSmallint;
  FieldIdentifier: SqlUSmallint;
  CharacterAttribute: SqlPointer;
  BufferLength: SqlSmallint;
  StringLength: pSqlSmallint;
  var NumericAttribute: SqlInteger
  ): SqlReturn{$IFDEF MSWINDOWS} stdcall{$ELSE} cdecl{$ENDIF};

{$IFDEF DynamicOdbcImport}
TSQLColumns = function(
{$ELSE}
function SQLColumns(
{$ENDIF}
  StatementHandle: SqlHStmt;
  CatalogName: PAnsiChar;
  NameLength1: SqlSmallint;
  SchemaName: PAnsiChar;
  NameLength2: SqlSmallint;
  TableName: PAnsiChar;
  NameLength3: SqlSmallint;
  ColumnName: PAnsiChar;
  NameLength4: SqlSmallint
  ): SqlReturn{$IFDEF MSWINDOWS} stdcall{$ELSE} cdecl{$ENDIF};

{$IFDEF DynamicOdbcImport}
TSQLConnect = function(
{$ELSE}
function SQLConnect(
{$ENDIF}
  ConnectionHandle: SqlHDbc;
  ServerName: PAnsiChar;
  NameLength1: SqlSmallint;
  UserName: PAnsiChar;
  NameLength2: SqlSmallint;
  Authentication: PAnsiChar;
  NameLength3: SqlSmallint
  ): SqlReturn{$IFDEF MSWINDOWS} stdcall{$ELSE} cdecl{$ENDIF};

{$IFDEF DynamicOdbcImport}
TSQLCopyDesc = function(
{$ELSE}
function SQLCopyDesc(
{$ENDIF}
  SourceDescHandle: SqlHDesc;
  TargetDescHandle: SqlHDesc
  ): SqlReturn{$IFDEF MSWINDOWS} stdcall{$ELSE} cdecl{$ENDIF};

{$IFDEF DynamicOdbcImport}
TSQLDataSources = function(
{$ELSE}
function SQLDataSources(
{$ENDIF}
  EnvironmentHandle: SqlHEnv;
  Direction: SqlUSmallint;
  var ServerName: SqlChar;
  BufferLength1: SqlSmallint;
  var NameLength1: SqlSmallint;
  var Description: SqlChar;
  BufferLength2: SqlSmallint;
  var NameLength2: SqlSmallint
  ): SqlReturn{$IFDEF MSWINDOWS} stdcall{$ELSE} cdecl{$ENDIF};

{$IFDEF DynamicOdbcImport}
TSQLDescribeCol = function(
{$ELSE}
function SQLDescribeCol(
{$ENDIF}
  StatementHandle: SqlHStmt;
  ColumnNumber: SqlUSmallint;
  ColumnName: PAnsiChar;
  BufferLength: SqlSmallint;
  var NameLength: SqlSmallint;
  var DataType: SqlSmallint;
  var ColumnSize: SqlUInteger;
  var DecimalDigits: SqlSmallint;
  var Nullable: SqlSmallint
  ): SqlReturn{$IFDEF MSWINDOWS} stdcall{$ELSE} cdecl{$ENDIF};

{$IFDEF DynamicOdbcImport}
TSQLDisconnect = function(
{$ELSE}
function SQLDisconnect(
{$ENDIF}
  ConnectionHandle: SqlHDbc
  ): SqlReturn{$IFDEF MSWINDOWS} stdcall{$ELSE} cdecl{$ENDIF};

{$IFDEF DynamicOdbcImport}
TSQLEndTran = function(
{$ELSE}
function SQLEndTran(
{$ENDIF}
  HandleType: SqlSmallint;
  Handle: SqlHandle;
  CompletionType: SqlSmallint
  ): SqlReturn{$IFDEF MSWINDOWS} stdcall{$ELSE} cdecl{$ENDIF};

{$IFDEF DynamicOdbcImport}
TSQLError = function(
{$ELSE}
function SQLError(
{$ENDIF}
  EnvironmentHandle: SqlHEnv;
  ConnectionHandle: SqlHDbc;
  StatementHandle: SqlHStmt;
  var Sqlstate: SqlChar;
  var NativeError: SqlInteger;
  var MessageText: SqlChar;
  BufferLength: SqlSmallint;
  var TextLength: SqlSmallint
  ): SqlReturn{$IFDEF MSWINDOWS} stdcall{$ELSE} cdecl{$ENDIF};

{$IFDEF DynamicOdbcImport}
TSQLExecDirect = function(
{$ELSE}
function SQLExecDirect(
{$ENDIF}
  StatementHandle: SqlHStmt;
  StatementText: PAnsiChar;
  TextLength: SqlInteger
  ): SqlReturn{$IFDEF MSWINDOWS} stdcall{$ELSE} cdecl{$ENDIF};

{$IFDEF DynamicOdbcImport}
TSQLExecute = function(
{$ELSE}
function SQLExecute(
{$ENDIF}
  StatementHandle: SqlHStmt
  ): SqlReturn{$IFDEF MSWINDOWS} stdcall{$ELSE} cdecl{$ENDIF};

{$IFDEF DynamicOdbcImport}
TSQLFetch = function(
{$ELSE}
function SQLFetch(
{$ENDIF}
  StatementHandle: SqlHStmt
  ): SqlReturn{$IFDEF MSWINDOWS} stdcall{$ELSE} cdecl{$ENDIF};

{$IFDEF DynamicOdbcImport}
TSQLFetchScroll = function(
{$ELSE}
function SQLFetchScroll(
{$ENDIF}
  StatementHandle: SqlHStmt;
  FetchOrientation: SqlSmallint;
  FetchOffset: SqlInteger
  ): SqlReturn{$IFDEF MSWINDOWS} stdcall{$ELSE} cdecl{$ENDIF};

{$IFDEF DynamicOdbcImport}
TSQLFreeConnect = function(
{$ELSE}
function SQLFreeConnect(
{$ENDIF}
  ConnectionHandle: SqlHDbc
  ): SqlReturn{$IFDEF MSWINDOWS} stdcall{$ELSE} cdecl{$ENDIF};

{$IFDEF DynamicOdbcImport}
TSQLFreeEnv = function(
{$ELSE}
function SQLFreeEnv(
{$ENDIF}
  EnvironmentHandle: SqlHEnv
  ): SqlReturn{$IFDEF MSWINDOWS} stdcall{$ELSE} cdecl{$ENDIF};

{$IFDEF DynamicOdbcImport}
TSQLFreeHandle = function(
{$ELSE}
function SQLFreeHandle(
{$ENDIF}
  HandleType: SqlSmallint;
  Handle: SqlHandle
  ): SqlReturn{$IFDEF MSWINDOWS} stdcall{$ELSE} cdecl{$ENDIF};

{$IFDEF DynamicOdbcImport}
TSQLFreeStmt = function(
{$ELSE}
function SQLFreeStmt(
{$ENDIF}
  StatementHandle: SqlHStmt;
  Option: SqlUSmallint
  ): SqlReturn{$IFDEF MSWINDOWS} stdcall{$ELSE} cdecl{$ENDIF};

// SQLGetConnectAttr is overloaded. See OBDC API doc:
// "Depending on the value of Attribute,
//  ValuePtr will be a 32-bit unsigned integer value
//  or will point to a null-terminated character string.

{$IFDEF DynamicOdbcImport}
TSQLGetConnectAttr = function(
{$ELSE}
function SQLGetConnectAttr(
{$ENDIF}
  ConnectionHandle: SqlHDbc;
  Attribute: SqlInteger;
  ValuePtr: SqlPointer;
  BufferLength: SqlInteger;
  pStringLength: PSqlInteger
  ): SqlReturn{$IFDEF MSWINDOWS} stdcall{$ELSE} cdecl{$ENDIF};

{$IFDEF DynamicOdbcImport}
TSQLGetConnectOption = function(
{$ELSE}
function SQLGetConnectOption(
{$ENDIF}
  ConnectionHandle: SqlHDbc;
  Option: SqlUSmallint;
  Value: SqlPointer
  ): SqlReturn{$IFDEF MSWINDOWS} stdcall{$ELSE} cdecl{$ENDIF};

{$IFDEF DynamicOdbcImport}
TSQLGetCursorName = function(
{$ELSE}
function SQLGetCursorName(
{$ENDIF}
  StatementHandle: SqlHStmt;
  CursorName: PAnsiChar;
  BufferLength: SqlSmallint;
  var NameLength: SqlSmallint
  ): SqlReturn{$IFDEF MSWINDOWS} stdcall{$ELSE} cdecl{$ENDIF};

{$IFDEF DynamicOdbcImport}
TSQLGetData = function(
{$ELSE}
function SQLGetData(
{$ENDIF}
  StatementHandle: SqlHStmt;
  ColumnNumber: SqlUSmallint;
  TargetType: SqlSmallint;
  TargetValue: SqlPointer;
  BufferLength: SqlInteger;
  StrLen_or_Ind: PSqlInteger
  ): SqlReturn{$IFDEF MSWINDOWS} stdcall{$ELSE} cdecl{$ENDIF};

{$IFDEF DynamicOdbcImport}
TSQLGetDescField = function(
{$ELSE}
function SQLGetDescField(
{$ENDIF}
  DescriptorHandle: SqlHDesc;
  RecNumber: SqlSmallint;
  FieldIdentifier: SqlSmallint;
  Value: SqlPointer;
  BufferLength: SqlInteger;
  var StringLength: SqlInteger
  ): SqlReturn{$IFDEF MSWINDOWS} stdcall{$ELSE} cdecl{$ENDIF};

{$IFDEF DynamicOdbcImport}
TSQLGetDescRec = function(
{$ELSE}
function SQLGetDescRec(
{$ENDIF}
  DescriptorHandle: SqlHDesc;
  RecNumber: SqlSmallint;
  var Name: SqlChar;
  BufferLength: SqlSmallint;
  var StringLength: SqlSmallint;
  var _Type: SqlSmallint;
  var SubType: SqlSmallint;
  var Length: SqlInteger;
  var Precision: SqlSmallint;
  var Scale: SqlSmallint;
  var Nullable: SqlSmallint
  ): SqlReturn{$IFDEF MSWINDOWS} stdcall{$ELSE} cdecl{$ENDIF};

{$IFDEF DynamicOdbcImport}
TSQLGetDiagField = function(
{$ELSE}
function SQLGetDiagField(
{$ENDIF}
  HandleType: SqlSmallint;
  Handle: SqlHandle;
  RecNumber: SqlSmallint;
  DiagIdentifier: SqlSmallint;
  DiagInfo: SqlPointer;
  BufferLength: SqlSmallint;
  var StringLength: SqlSmallint
  ): SqlReturn{$IFDEF MSWINDOWS} stdcall{$ELSE} cdecl{$ENDIF};

{$IFDEF DynamicOdbcImport}
TSQLGetDiagRec = function(
{$ELSE}
function SQLGetDiagRec(
{$ENDIF}
  HandleType: SqlSmallint;
  Handle: SqlHandle;
  RecNumber: SqlSmallint;
  Sqlstate: PAnsiChar; // pointer to 5 character buffer
  var NativeError: SqlInteger;
  MessageText: PAnsiChar;
  BufferLength: SqlSmallint;
  var TextLength: SqlSmallint
  ): SqlReturn{$IFDEF MSWINDOWS} stdcall{$ELSE} cdecl{$ENDIF};

{$IFDEF DynamicOdbcImport}
TSQLGetEnvAttr = function(
{$ELSE}
function SQLGetEnvAttr(
{$ENDIF}
  EnvironmentHandle: SqlHEnv;
  Attribute: SqlInteger;
  Value: SqlPointer;
  BufferLength: SqlInteger;
  var StringLength: SqlInteger
  ): SqlReturn{$IFDEF MSWINDOWS} stdcall{$ELSE} cdecl{$ENDIF};

{$IFDEF DynamicOdbcImport}
TSQLGetFunctions = function(
{$ELSE}
function SQLGetFunctions(
{$ENDIF}
  ConnectionHandle: SqlHDbc;
  FunctionId: SqlUSmallint;
  var Supported: SqlUSmallint
  ): SqlReturn{$IFDEF MSWINDOWS} stdcall{$ELSE} cdecl{$ENDIF};

// SQLGetInfo is overloaded. See OBDC API doc:
//   "Depending on the InfoType requested,
//   the information returned will be one of the following:
//     a null-terminated character string,
//     an SQLUSMALLINT value,
//     an SQLUINTEGER bitmask,
//     an SQLUINTEGER flag,
//     or a SQLUINTEGER binary value."

{$IFNDEF DynamicOdbcImport}
function SQLFunctionSupported(ConnectionHandle: SqlHDbc; FunctionId: SqlUSmallint): Boolean;
{$ENDIF}

{$IFDEF DynamicOdbcImport}
TSQLGetInfo = function(
{$ELSE}
function SQLGetInfo(
{$ENDIF}
  ConnectionHandle: SqlHDbc;
  InfoType: SqlUSmallint;
  InfoValuePtr: SqlPointer;
  BufferLength: SqlSmallint;
  StringLengthPtr: SqlPointer
  ): SqlReturn{$IFDEF MSWINDOWS} stdcall{$ELSE} cdecl{$ENDIF};

{$IFDEF DynamicOdbcImport}
TSQLGetInfoString = function(
{$ELSE}
function SQLGetInfoString(
{$ENDIF}
  ConnectionHandle: SqlHDbc;
  InfoType: SqlUSmallint;
  InfoValueString: PAnsiChar; // PWideChar when calling SQLGetInfoW
  BufferLength: SqlSmallint;
  var StringLength: SqlSmallint
  ): SqlReturn{$IFDEF MSWINDOWS} stdcall{$ELSE} cdecl{$ENDIF};

{$IFDEF DynamicOdbcImport}
TSQLGetInfoSmallint = function(
{$ELSE}
function SQLGetInfoSmallint(
{$ENDIF}
  ConnectionHandle: SqlHDbc;
  InfoType: SqlUSmallint;
  var InfoValue: SqlUSmallint;
  Ignored1: SqlSmallint;
  Ignored2: Pointer
  ): SqlReturn{$IFDEF MSWINDOWS} stdcall{$ELSE} cdecl{$ENDIF};

{$IFDEF DynamicOdbcImport}
TSQLGetInfoInt = function(
{$ELSE}
function SQLGetInfoInt(
{$ENDIF}
  ConnectionHandle: SqlHDbc;
  InfoType: SqlUSmallint;
  var InfoValue: SqlUInteger;
  Ignored1: SqlSmallint;
  Ignored2: Pointer
  ): SqlReturn{$IFDEF MSWINDOWS} stdcall{$ELSE} cdecl{$ENDIF};

{$IFDEF DynamicOdbcImport}
TSQLGetStmtAttr = function(
{$ELSE}
function SQLGetStmtAttr(
{$ENDIF}
  StatementHandle: SqlHStmt;
  Attribute: SqlInteger;
  Value: SqlPointer;
  BufferLength: SqlInteger;
  StringLength: PSqlInteger
  ): SqlReturn{$IFDEF MSWINDOWS} stdcall{$ELSE} cdecl{$ENDIF};

{$IFDEF DynamicOdbcImport}
TSQLGetStmtOption = function(
{$ELSE}
function SQLGetStmtOption(
{$ENDIF}
  StatementHandle: SqlHStmt;
  Option: SqlUSmallint;
  Value: SqlPointer
  ): SqlReturn{$IFDEF MSWINDOWS} stdcall{$ELSE} cdecl{$ENDIF};

{$IFDEF DynamicOdbcImport}
TSQLGetTypeInfo = function(
{$ELSE}
function SQLGetTypeInfo(
{$ENDIF}
  StatementHandle: SqlHStmt;
  DataType: SqlSmallint
  ): SqlReturn{$IFDEF MSWINDOWS} stdcall{$ELSE} cdecl{$ENDIF};

{$IFDEF DynamicOdbcImport}
TSQLNumResultCols = function(
{$ELSE}
function SQLNumResultCols(
{$ENDIF}
  StatementHandle: SqlHStmt;
  var ColumnCount: SqlSmallint
  ): SqlReturn{$IFDEF MSWINDOWS} stdcall{$ELSE} cdecl{$ENDIF};

{$IFDEF DynamicOdbcImport}
TSQLParamData = function(
{$ELSE}
function SQLParamData(
{$ENDIF}
  StatementHandle: SqlHStmt;
  var Value: SqlPointer
  ): SqlReturn{$IFDEF MSWINDOWS} stdcall{$ELSE} cdecl{$ENDIF};

{$IFDEF DynamicOdbcImport}
TSQLPrepare = function(
{$ELSE}
function SQLPrepare(
{$ENDIF}
  StatementHandle: SqlHStmt;
  StatementText: PAnsiChar;
  TextLength: SqlInteger
  ): SqlReturn{$IFDEF MSWINDOWS} stdcall{$ELSE} cdecl{$ENDIF};

{$IFDEF DynamicOdbcImport}
TSQLPutData = function(
{$ELSE}
function SQLPutData(
{$ENDIF}
  StatementHandle: SqlHStmt;
  Data: SqlPointer;
  StrLen_or_Ind: SqlInteger
  ): SqlReturn{$IFDEF MSWINDOWS} stdcall{$ELSE} cdecl{$ENDIF};

{$IFDEF DynamicOdbcImport}
TSQLRowCount = function(
{$ELSE}
function SQLRowCount(
{$ENDIF}
  StatementHandle: SqlHStmt;
  var RowCount: SqlInteger
  ): SqlReturn{$IFDEF MSWINDOWS} stdcall{$ELSE} cdecl{$ENDIF};

{$IFDEF DynamicOdbcImport}
TSQLSetConnectAttr = function(
{$ELSE}
function SQLSetConnectAttr(
{$ENDIF}
  ConnectionHandle: SqlHDbc;
  Attribute: SqlInteger;
  ValuePtr: SqlPointer;
  StringLength: SqlInteger
  ): SqlReturn{$IFDEF MSWINDOWS} stdcall{$ELSE} cdecl{$ENDIF};

{$IFDEF DynamicOdbcImport}
TSQLSetConnectOption = function(
{$ELSE}
function SQLSetConnectOption(
{$ENDIF}
  ConnectionHandle: SqlHDbc;
  Option: SqlUSmallint;
  Value: SqlUInteger
  ): SqlReturn{$IFDEF MSWINDOWS} stdcall{$ELSE} cdecl{$ENDIF};

{$IFDEF DynamicOdbcImport}
TSQLSetCursorName = function(
{$ELSE}
function SQLSetCursorName(
{$ENDIF}
  StatementHandle: SqlHStmt;
  CursorName: PAnsiChar;
  NameLength: SqlSmallint
  ): SqlReturn{$IFDEF MSWINDOWS} stdcall{$ELSE} cdecl{$ENDIF};

{$IFDEF DynamicOdbcImport}
TSQLSetDescField = function(
{$ELSE}
function SQLSetDescField(
{$ENDIF}
  DescriptorHandle: SqlHDesc;
  RecNumber: SqlSmallint;
  FieldIdentifier: SqlSmallint;
  Value: SqlPointer;
  BufferLength: SqlInteger
  ): SqlReturn{$IFDEF MSWINDOWS} stdcall{$ELSE} cdecl{$ENDIF};

{$IFDEF DynamicOdbcImport}
TSQLSetDescRec = function(
{$ELSE}
function SQLSetDescRec(
{$ENDIF}
  DescriptorHandle: SqlHDesc;
  RecNumber: SqlSmallint;
  _Type: SqlSmallint;
  SubType: SqlSmallint;
  Length: SqlInteger;
  Precision: SqlSmallint;
  Scale: SqlSmallint;
  Data: SqlPointer;
  var StringLength: SqlInteger;
  var Indicator: SqlInteger
  ): SqlReturn{$IFDEF MSWINDOWS} stdcall{$ELSE} cdecl{$ENDIF};

// SQLSetEnvAttr is overloaded. See OBDC API doc:
//   "Depending on the value of Attribute,
//   value will be a 32-bit integer value
//   or point to a null-terminated character string."

{$IFDEF DynamicOdbcImport}
TSQLSetEnvAttr = function(
{$ELSE}
function SQLSetEnvAttr(
{$ENDIF}
  EnvironmentHandle: SqlHEnv;
  Attribute: SqlInteger;
  ValuePtr: Pointer;
  StringLength: SqlInteger
  ): SqlReturn{$IFDEF MSWINDOWS} stdcall{$ELSE} cdecl{$ENDIF};

{$IFDEF DynamicOdbcImport}
TSQLSetParam = function(
{$ELSE}
function SQLSetParam(
{$ENDIF}
  StatementHandle: SqlHStmt;
  ParameterNumber: SqlUSmallint;
  ValueType: SqlSmallint;
  ParameterType: SqlSmallint;
  LengthPrecision: SqlUInteger;
  ParameterScale: SqlSmallint;
  ParameterValue: SqlPointer;
  var StrLen_or_Ind: SqlInteger
  ): SqlReturn{$IFDEF MSWINDOWS} stdcall{$ELSE} cdecl{$ENDIF};

{$IFDEF DynamicOdbcImport}
TSQLSetStmtAttr = function(
{$ELSE}
function SQLSetStmtAttr(
{$ENDIF}
  StatementHandle: SqlHStmt;
  Attribute: SqlInteger;
  Value: SqlPointer;
  StringLength: SqlInteger
  ): SqlReturn{$IFDEF MSWINDOWS} stdcall{$ELSE} cdecl{$ENDIF};

{$IFDEF DynamicOdbcImport}
TSQLSetStmtOption = function(
{$ELSE}
function SQLSetStmtOption(
{$ENDIF}
  StatementHandle: SqlHStmt;
  Option: SqlUSmallint;
  Value: SqlUInteger
  ): SqlReturn{$IFDEF MSWINDOWS} stdcall{$ELSE} cdecl{$ENDIF};

{$IFDEF DynamicOdbcImport}
TSQLSpecialColumns = function(
{$ELSE}
function SQLSpecialColumns(
{$ENDIF}
  StatementHandle: SqlHStmt;
  IdentifierType: SqlUSmallint;
  CatalogName: PAnsiChar;
  NameLength1: SqlSmallint;
  SchemaName: PAnsiChar;
  NameLength2: SqlSmallint;
  TableName: PAnsiChar;
  NameLength3: SqlSmallint;
  Scope: SqlUSmallint;
  Nullable: SqlUSmallint
  ): SqlReturn{$IFDEF MSWINDOWS} stdcall{$ELSE} cdecl{$ENDIF};

{$IFDEF DynamicOdbcImport}
TSQLStatistics = function(
{$ELSE}
function SQLStatistics(
{$ENDIF}
  StatementHandle: SqlHStmt;
  CatalogName: PAnsiChar;
  NameLength1: SqlSmallint;
  SchemaName: PAnsiChar;
  NameLength2: SqlSmallint;
  TableName: PAnsiChar;
  NameLength3: SqlSmallint;
  Unique: SqlUSmallint;
  Reserved: SqlUSmallint
  ): SqlReturn{$IFDEF MSWINDOWS} stdcall{$ELSE} cdecl{$ENDIF};

{$IFDEF DynamicOdbcImport}
TSQLTables = function(
{$ELSE}
function SQLTables(
{$ENDIF}
  StatementHandle: SqlHStmt;
  CatalogName: PAnsiChar;
  NameLength1: SqlSmallint;
  SchemaName: PAnsiChar;
  NameLength2: SqlSmallint;
  TableName: PAnsiChar;
  NameLength3: SqlSmallint;
  TableType: PAnsiChar;
  NameLength4: SqlSmallint
  ): SqlReturn{$IFDEF MSWINDOWS} stdcall{$ELSE} cdecl{$ENDIF};

{$IFDEF DynamicOdbcImport}
TSQLTransact = function(
{$ELSE}
function SQLTransact(
{$ENDIF}
  EnvironmentHandle: SqlHEnv;
  ConnectionHandle: SqlHDbc;
  CompletionType: SqlUSmallint
  ): SqlReturn{$IFDEF MSWINDOWS} stdcall{$ELSE} cdecl{$ENDIF};

//##########################################################################
// sql.h interface part ends here
//##########################################################################

//##########################################################################
// sqlext.h interface part starts here
//##########################################################################

//****************************************************************
// SQLEXT.H - This is the include for applications using
// the Microsoft SQL Extensions
//
// (C) Copyright 1990 - 1998 By Microsoft Corp.
//
// Updated 05/12/93 for 2.00 specification
// Updated 05/23/94 for 2.01 specification
// Updated 10/27/94 for 2.10 specification
// Updated 04/10/95 for 2.50 specification
// Updated 07/25/95 for 3.00 specification
// Updated 01/12/96 for 3.00 preliminary release
// Updated 10/22/97 for 3.51 specification
//********************************************************************

// copied from sqlucode.h
const
  SQL_WCHAR = (-8);
  SQL_WVARCHAR = (-9);
  SQL_WLONGVARCHAR = (-10);
  SQL_C_WCHAR = SQL_WCHAR;

  // generally useful constants
const
  SQL_SPEC_MAJOR = 3; // Major version of specification
  SQL_SPEC_MINOR = 51; // Minor version of specification
  SQL_SPEC_STRING = '03.51'; // String constant for version

  SQL_SQLSTATE_SIZE = 5; // size of SQLSTATE
  SQL_MAX_DSN_LENGTH = 32; // maximum data source name size

  SQL_MAX_OPTION_STRING_LENGTH = 256;

  // return code SQL_NO_DATA_FOUND is the same as SQL_NO_DATA*
  SQL_NO_DATA_FOUND = SQL_NO_DATA;

  // an env handle type
  SQL_HANDLE_SENV = 5;

  // env attribute
  SQL_ATTR_ODBC_VERSION = 200;
  SQL_ATTR_CONNECTION_POOLING = 201;
  SQL_ATTR_CP_MATCH = 202;

  // values for SQL_ATTR_CONNECTION_POOLING
  SQL_CP_OFF = ULong(0);
  SQL_CP_ONE_PER_DRIVER = ULong(1);
  SQL_CP_ONE_PER_HENV = ULong(2);
  SQL_CP_DEFAULT = SQL_CP_OFF;

  // values for SQL_ATTR_CP_MATCH
  SQL_CP_STRICT_MATCH = ULong(0);
  SQL_CP_RELAXED_MATCH = ULong(1);
  SQL_CP_MATCH_DEFAULT = SQL_CP_STRICT_MATCH;

  // values for SQL_ATTR_ODBC_VERSION
  SQL_OV_ODBC2 = ULong(2);
  SQL_OV_ODBC3 = ULong(3);

  // connection attributes
  SQL_ACCESS_MODE = 101;
  SQL_AUTOCOMMIT = 102;
  SQL_LOGIN_TIMEOUT = 103;
  SQL_OPT_TRACE = 104;
  SQL_OPT_TRACEFILE = 105;
  SQL_TRANSLATE_DLL = 106;
  SQL_TRANSLATE_OPTION = 107;
  SQL_TXN_ISOLATION = 108;
  SQL_CURRENT_QUALIFIER = 109;
  SQL_ODBC_CURSORS = 110;
  SQL_QUIET_MODE = 111;
  SQL_PACKET_SIZE = 112;

  // connection attributes with new names
  SQL_ATTR_ACCESS_MODE = SQL_ACCESS_MODE;
  SQL_ATTR_AUTOCOMMIT = SQL_AUTOCOMMIT;
  SQL_ATTR_CONNECTION_TIMEOUT = 113;
  SQL_ATTR_CURRENT_CATALOG = SQL_CURRENT_QUALIFIER;
  SQL_ATTR_DISCONNECT_BEHAVIOR = 114;
  SQL_ATTR_ENLIST_IN_DTC = 1207;
  SQL_ATTR_ENLIST_IN_XA = 1208;
  SQL_ATTR_LOGIN_TIMEOUT = SQL_LOGIN_TIMEOUT;
  SQL_ATTR_ODBC_CURSORS = SQL_ODBC_CURSORS;
  SQL_ATTR_PACKET_SIZE = SQL_PACKET_SIZE;
  SQL_ATTR_QUIET_MODE = SQL_QUIET_MODE;
  SQL_ATTR_TRACE = SQL_OPT_TRACE;
  SQL_ATTR_TRACEFILE = SQL_OPT_TRACEFILE;
  SQL_ATTR_TRANSLATE_LIB = SQL_TRANSLATE_DLL;
  SQL_ATTR_TRANSLATE_OPTION = SQL_TRANSLATE_OPTION;
  SQL_ATTR_TXN_ISOLATION = SQL_TXN_ISOLATION;
  SQL_ATTR_CONNECTION_DEAD = 1209; // GetConnectAttr only

  { ODBC Driver Manager sets this connection attribute to a unicode driver
    (which supports SQLConnectW) when the application is an ANSI application
    (which calls SQLConnect, SQLDriverConnect, or SQLBrowseConnect).
    This is SetConnectAttr only and application does not set this attribute
    This attribute was introduced because some unicode driver's some APIs may
    need to behave differently on ANSI or Unicode applications. A unicode
    driver, which has same behavior for both ANSI or Unicode applications,
    should return SQL_ERROR when the driver manager sets this connection
    attribute. When a unicode driver returns SQL_SUCCESS on this attribute,
    the driver manager treates ANSI and Unicode connections differently in
    connection pooling. }
  SQL_ATTR_ANSI_APP = 115;

  // SQL_CONNECT_OPT_DRVR_START is not meaningful for 3.0 driver
  SQL_CONNECT_OPT_DRVR_START = 1000;
  SQL_CONN_OPT_MAX = SQL_PACKET_SIZE;
  SQL_CONN_OPT_MIN = SQL_ACCESS_MODE;

  // SQL_ACCESS_MODE options
  SQL_MODE_READ_WRITE = ULong(0);
  SQL_MODE_READ_ONLY = ULong(1);
  SQL_MODE_DEFAULT = SQL_MODE_READ_WRITE;

  // SQL_AUTOCOMMIT options
  SQL_AUTOCOMMIT_OFF = ULong(0);
  SQL_AUTOCOMMIT_ON = ULong(1);
  SQL_AUTOCOMMIT_DEFAULT = SQL_AUTOCOMMIT_ON;

  // SQL_LOGIN_TIMEOUT options
  SQL_LOGIN_TIMEOUT_DEFAULT = ULong(15);

  // SQL_OPT_TRACE options
  SQL_OPT_TRACE_OFF = ULong(0);
  SQL_OPT_TRACE_ON = ULong(1);
  SQL_OPT_TRACE_DEFAULT = SQL_OPT_TRACE_OFF;
  SQL_OPT_TRACE_FILE_DEFAULT = '\\SQL.LOG';

  // SQL_ODBC_CURSORS options
  SQL_CUR_USE_IF_NEEDED = ULong(0);
  SQL_CUR_USE_ODBC = ULong(1);
  SQL_CUR_USE_DRIVER = ULong(2);
  SQL_CUR_DEFAULT = SQL_CUR_USE_DRIVER;

  // values for SQL_ATTR_DISCONNECT_BEHAVIOR
  SQL_DB_RETURN_TO_POOL = ULong(0);
  SQL_DB_DISCONNECT = ULong(1);
  SQL_DB_DEFAULT = SQL_DB_RETURN_TO_POOL;

  // values for SQL_ATTR_ENLIST_IN_DTC
  SQL_DTC_DONE = 0;

  // values for SQL_ATTR_CONNECTION_DEAD
  SQL_CD_TRUE = 1; // Connection is closed/dead
  SQL_CD_FALSE = 0; // Connection is open/available

  // values for SQL_ATTR_ANSI_APP
  SQL_AA_TRUE = 1; // the application is an ANSI app
  SQL_AA_FALSE = 0; // the application is a Unicode app

  // statement attributes
  SQL_QUERY_TIMEOUT = 0;
  SQL_MAX_ROWS = 1;
  SQL_NOSCAN = 2;
  SQL_MAX_LENGTH = 3;
  SQL_ASYNC_ENABLE = 4; // same as SQL_ATTR_ASYNC_ENABLE
  SQL_BIND_TYPE = 5;
  SQL_CURSOR_TYPE = 6;
  SQL_CONCURRENCY = 7;
  SQL_KEYSET_SIZE = 8;
  SQL_ROWSET_SIZE = 9;
  SQL_SIMULATE_CURSOR = 10;
  SQL_RETRIEVE_DATA = 11;
  SQL_USE_BOOKMARKS = 12;
  SQL_GET_BOOKMARK = 13; // GetStmtOption Only
  SQL_ROW_NUMBER = 14; // GetStmtOption Only

  SQL_ATTR_ASYNC_ENABLE = 4;
  SQL_ATTR_CONCURRENCY = SQL_CONCURRENCY;
  SQL_ATTR_CURSOR_TYPE = SQL_CURSOR_TYPE;
  SQL_ATTR_ENABLE_AUTO_IPD = 15;
  SQL_ATTR_FETCH_BOOKMARK_PTR = 16;
  SQL_ATTR_KEYSET_SIZE = SQL_KEYSET_SIZE;
  SQL_ATTR_MAX_LENGTH = SQL_MAX_LENGTH;
  SQL_ATTR_MAX_ROWS = SQL_MAX_ROWS;
  SQL_ATTR_NOSCAN = SQL_NOSCAN;
  SQL_ATTR_PARAM_BIND_OFFSET_PTR = 17;
  SQL_ATTR_PARAM_BIND_TYPE = 18;
  SQL_ATTR_PARAM_OPERATION_PTR = 19;
  SQL_ATTR_PARAM_STATUS_PTR = 20;
  SQL_ATTR_PARAMS_PROCESSED_PTR = 21;
  SQL_ATTR_PARAMSET_SIZE = 22;
  SQL_ATTR_QUERY_TIMEOUT = SQL_QUERY_TIMEOUT;
  SQL_ATTR_RETRIEVE_DATA = SQL_RETRIEVE_DATA;
  SQL_ATTR_ROW_BIND_OFFSET_PTR = 23;
  SQL_ATTR_ROW_BIND_TYPE = SQL_BIND_TYPE;
  SQL_ATTR_ROW_NUMBER = SQL_ROW_NUMBER; // GetStmtAttr
  SQL_ATTR_ROW_OPERATION_PTR = 24;
  SQL_ATTR_ROW_STATUS_PTR = 25;
  SQL_ATTR_ROWS_FETCHED_PTR = 26;
  SQL_ATTR_ROW_ARRAY_SIZE = 27;
  SQL_ATTR_SIMULATE_CURSOR = SQL_SIMULATE_CURSOR;
  SQL_ATTR_USE_BOOKMARKS = SQL_USE_BOOKMARKS;

  SQL_STMT_OPT_MAX = SQL_ROW_NUMBER;
  SQL_STMT_OPT_MIN = SQL_QUERY_TIMEOUT;


  //=====================================
  // This block moved to here from below because of dependent decarations

  // SQLColAttributes defines
  SQL_COLUMN_COUNT = 0;
  SQL_COLUMN_NAME = 1;
  SQL_COLUMN_TYPE = 2;
  SQL_COLUMN_LENGTH = 3;
  SQL_COLUMN_PRECISION = 4;
  SQL_COLUMN_SCALE = 5;
  SQL_COLUMN_DISPLAY_SIZE = 6;
  SQL_COLUMN_NULLABLE = 7;
  SQL_COLUMN_UNSIGNED = 8;
  SQL_COLUMN_MONEY = 9;
  SQL_COLUMN_UPDATABLE = 10;
  SQL_COLUMN_AUTO_INCREMENT = 11;
  SQL_COLUMN_CASE_SENSITIVE = 12;
  SQL_COLUMN_SEARCHABLE = 13;
  SQL_COLUMN_TYPE_NAME = 14;
  SQL_COLUMN_TABLE_NAME = 15;
  SQL_COLUMN_OWNER_NAME = 16;
  SQL_COLUMN_QUALIFIER_NAME = 17;
  SQL_COLUMN_LABEL = 18;

  SQL_COLATT_OPT_MAX = SQL_COLUMN_LABEL;
  SQL_COLATT_OPT_MIN = SQL_COLUMN_COUNT;

  // SQLColAttributes subdefines for SQL_COLUMN_UPDATABLE
  SQL_ATTR_READONLY = 0;
  SQL_ATTR_WRITE = 1;
  SQL_ATTR_READWRITE_UNKNOWN = 2;

  // SQLColAttributes subdefines for SQL_COLUMN_SEARCHABLE
  // These are also used by SQLGetInfo
  SQL_UNSEARCHABLE = 0;
  SQL_LIKE_ONLY = 1;
  SQL_ALL_EXCEPT_LIKE = 2;
  SQL_SEARCHABLE = 3;
  SQL_PRED_SEARCHABLE = SQL_SEARCHABLE;

  // Special return values for SQLGetData
  SQL_NO_TOTAL = (-4);
  // End of move
  //=====================================

  // New defines for SEARCHABLE column in SQLGetTypeInfo
  SQL_COL_PRED_CHAR = SQL_LIKE_ONLY;
  SQL_COL_PRED_BASIC = SQL_ALL_EXCEPT_LIKE;

  // whether an attribute is a pointer or not
  SQL_IS_POINTER = (-4);

  SQL_IS_UINTEGER = (-5);
  SQL_IS_INTEGER = (-6);
  SQL_IS_USMALLINT = (-7);
  SQL_IS_SMALLINT = (-8);

  // the value of SQL_ATTR_PARAM_BIND_TYPE
  SQL_PARAM_BIND_BY_COLUMN = ULong(0);
  SQL_PARAM_BIND_TYPE_DEFAULT = SQL_PARAM_BIND_BY_COLUMN;

  // SQL_QUERY_TIMEOUT options
  SQL_QUERY_TIMEOUT_DEFAULT = ULong(0);

  // SQL_MAX_ROWS options
  SQL_MAX_ROWS_DEFAULT = ULong(0);

  // SQL_NOSCAN options
  SQL_NOSCAN_OFF = ULong(0); // 1.0 FALSE
  SQL_NOSCAN_ON = ULong(1); // 1.0 TRUE
  SQL_NOSCAN_DEFAULT = SQL_NOSCAN_OFF;

  // SQL_MAX_LENGTH options
  SQL_MAX_LENGTH_DEFAULT = ULong(0);

  // values for SQL_ATTR_ASYNC_ENABLE
  SQL_ASYNC_ENABLE_OFF = ULong(0);
  SQL_ASYNC_ENABLE_ON = ULong(1);
  SQL_ASYNC_ENABLE_DEFAULT = SQL_ASYNC_ENABLE_OFF;

  // SQL_BIND_TYPE options
  SQL_BIND_BY_COLUMN = ULong(0);
  SQL_BIND_TYPE_DEFAULT = SQL_BIND_BY_COLUMN; // Default value

  // SQL_CONCURRENCY options
  SQL_CONCUR_READ_ONLY = 1;
  SQL_CONCUR_LOCK = 2;
  SQL_CONCUR_ROWVER = 3;
  SQL_CONCUR_VALUES = 4;
  SQL_CONCUR_DEFAULT = SQL_CONCUR_READ_ONLY; // Default value

  // SQL_CURSOR_TYPE options
  SQL_CURSOR_FORWARD_ONLY = ULong(0);
  SQL_CURSOR_KEYSET_DRIVEN = ULong(1);
  SQL_CURSOR_DYNAMIC = ULong(2);
  SQL_CURSOR_STATIC = ULong(3);
  SQL_CURSOR_TYPE_DEFAULT = SQL_CURSOR_FORWARD_ONLY; // Default value

  // SQL_ROWSET_SIZE options
  SQL_ROWSET_SIZE_DEFAULT = ULong(1);

  // SQL_KEYSET_SIZE options
  SQL_KEYSET_SIZE_DEFAULT = ULong(0);

  // SQL_SIMULATE_CURSOR options
  SQL_SC_NON_UNIQUE = ULong(0);
  SQL_SC_TRY_UNIQUE = ULong(1);
  SQL_SC_UNIQUE = ULong(2);

  // SQL_RETRIEVE_DATA options
  SQL_RD_OFF = ULong(0);
  SQL_RD_ON = ULong(1);
  SQL_RD_DEFAULT = SQL_RD_ON;

  // SQL_USE_BOOKMARKS options
  SQL_UB_OFF = ULong(0);
  SQL_UB_ON = ULong(1);
  SQL_UB_DEFAULT = SQL_UB_OFF;

  // New values for SQL_USE_BOOKMARKS attribute
  SQL_UB_FIXED = SQL_UB_ON;
  SQL_UB_VARIABLE = ULong(2);

  // extended descriptor field
  SQL_DESC_ARRAY_SIZE = 20;
  SQL_DESC_ARRAY_STATUS_PTR = 21;
  SQL_DESC_AUTO_UNIQUE_VALUE = SQL_COLUMN_AUTO_INCREMENT;
  SQL_DESC_BASE_COLUMN_NAME = 22;
  SQL_DESC_BASE_TABLE_NAME = 23;
  SQL_DESC_BIND_OFFSET_PTR = 24;
  SQL_DESC_BIND_TYPE = 25;
  SQL_DESC_CASE_SENSITIVE = SQL_COLUMN_CASE_SENSITIVE;
  SQL_DESC_CATALOG_NAME = SQL_COLUMN_QUALIFIER_NAME;
  SQL_DESC_CONCISE_TYPE = SQL_COLUMN_TYPE;
  SQL_DESC_DATETIME_INTERVAL_PRECISION = 26;
  SQL_DESC_DISPLAY_SIZE = SQL_COLUMN_DISPLAY_SIZE;
  SQL_DESC_FIXED_PREC_SCALE = SQL_COLUMN_MONEY;
  SQL_DESC_LABEL = SQL_COLUMN_LABEL;
  SQL_DESC_LITERAL_PREFIX = 27;
  SQL_DESC_LITERAL_SUFFIX = 28;
  SQL_DESC_LOCAL_TYPE_NAME = 29;
  SQL_DESC_MAXIMUM_SCALE = 30;
  SQL_DESC_MINIMUM_SCALE = 31;
  SQL_DESC_NUM_PREC_RADIX = 32;
  SQL_DESC_PARAMETER_TYPE = 33;
  SQL_DESC_ROWS_PROCESSED_PTR = 34;
  SQL_DESC_ROWVER = 35;
  SQL_DESC_SCHEMA_NAME = SQL_COLUMN_OWNER_NAME;
  SQL_DESC_SEARCHABLE = SQL_COLUMN_SEARCHABLE;
  SQL_DESC_TYPE_NAME = SQL_COLUMN_TYPE_NAME;
  SQL_DESC_TABLE_NAME = SQL_COLUMN_TABLE_NAME;
  SQL_DESC_UNSIGNED = SQL_COLUMN_UNSIGNED;
  SQL_DESC_UPDATABLE = SQL_COLUMN_UPDATABLE;

  // defines for diagnostics fields
  SQL_DIAG_CURSOR_ROW_COUNT = (-1249);
  SQL_DIAG_ROW_NUMBER = (-1248);
  SQL_DIAG_COLUMN_NUMBER = (-1247);

  // SQL extended datatypes
  SQL_DATE = 9;
  SQL_INTERVAL = 10;
  SQL_TIME = 10;
  SQL_TIMESTAMP = 11;
  SQL_LONGVARCHAR = (-1);
  SQL_BINARY = (-2);
  SQL_VARBINARY = (-3);
  SQL_LONGVARBINARY = (-4);
  SQL_BIGINT = (-5);
  SQL_TINYINT = (-6);
  SQL_BIT = (-7);
  SQL_GUID = (-11);

  // interval code
  SQL_CODE_YEAR = 1;
  SQL_CODE_MONTH = 2;
  SQL_CODE_DAY = 3;
  SQL_CODE_HOUR = 4;
  SQL_CODE_MINUTE = 5;
  SQL_CODE_SECOND = 6;
  SQL_CODE_YEAR_TO_MONTH = 7;
  SQL_CODE_DAY_TO_HOUR = 8;
  SQL_CODE_DAY_TO_MINUTE = 9;
  SQL_CODE_DAY_TO_SECOND = 10;
  SQL_CODE_HOUR_TO_MINUTE = 11;
  SQL_CODE_HOUR_TO_SECOND = 12;
  SQL_CODE_MINUTE_TO_SECOND = 13;

  SQL_INTERVAL_YEAR = (100 + SQL_CODE_YEAR);
  SQL_INTERVAL_MONTH = (100 + SQL_CODE_MONTH);
  SQL_INTERVAL_DAY = (100 + SQL_CODE_DAY);
  SQL_INTERVAL_HOUR = (100 + SQL_CODE_HOUR);
  SQL_INTERVAL_MINUTE = (100 + SQL_CODE_MINUTE);
  SQL_INTERVAL_SECOND = (100 + SQL_CODE_SECOND);
  SQL_INTERVAL_YEAR_TO_MONTH = (100 + SQL_CODE_YEAR_TO_MONTH);
  SQL_INTERVAL_DAY_TO_HOUR = (100 + SQL_CODE_DAY_TO_HOUR);
  SQL_INTERVAL_DAY_TO_MINUTE = (100 + SQL_CODE_DAY_TO_MINUTE);
  SQL_INTERVAL_DAY_TO_SECOND = (100 + SQL_CODE_DAY_TO_SECOND);
  SQL_INTERVAL_HOUR_TO_MINUTE = (100 + SQL_CODE_HOUR_TO_MINUTE);
  SQL_INTERVAL_HOUR_TO_SECOND = (100 + SQL_CODE_HOUR_TO_SECOND);
  SQL_INTERVAL_MINUTE_TO_SECOND = (100 + SQL_CODE_MINUTE_TO_SECOND);

  SQL_UNICODE = SQL_WCHAR;
  SQL_UNICODE_VARCHAR = SQL_WVARCHAR;
  SQL_UNICODE_LONGVARCHAR = SQL_WLONGVARCHAR;
  SQL_UNICODE_CHAR = SQL_WCHAR;

  // C datatype to SQL datatype mapping SQL types
  // -------------------
  SQL_C_CHAR = SQL_CHAR; // CHAR, VARCHAR, DECIMAL, NUMERIC
  SQL_C_LONG = SQL_INTEGER; // INTEGER
  SQL_C_SHORT = SQL_SMALLINT; // SMALLINT
  SQL_C_FLOAT = SQL_REAL; // REAL
  SQL_C_DOUBLE = SQL_DOUBLE; // FLOAT, DOUBLE
  SQL_C_NUMERIC = SQL_NUMERIC;
  SQL_C_DEFAULT = 99;
  SQL_SIGNED_OFFSET = (-20);
  SQL_UNSIGNED_OFFSET = (-22);

  // C datatype to SQL datatype mapping
  SQL_C_DATE = SQL_DATE;
  SQL_C_TIME = SQL_TIME;
  SQL_C_TIMESTAMP = SQL_TIMESTAMP;
  SQL_C_TYPE_DATE = SQL_TYPE_DATE;
  SQL_C_TYPE_TIME = SQL_TYPE_TIME;
  SQL_C_TYPE_TIMESTAMP = SQL_TYPE_TIMESTAMP;
  SQL_C_INTERVAL_YEAR = SQL_INTERVAL_YEAR;
  SQL_C_INTERVAL_MONTH = SQL_INTERVAL_MONTH;
  SQL_C_INTERVAL_DAY = SQL_INTERVAL_DAY;
  SQL_C_INTERVAL_HOUR = SQL_INTERVAL_HOUR;
  SQL_C_INTERVAL_MINUTE = SQL_INTERVAL_MINUTE;
  SQL_C_INTERVAL_SECOND = SQL_INTERVAL_SECOND;
  SQL_C_INTERVAL_YEAR_TO_MONTH = SQL_INTERVAL_YEAR_TO_MONTH;
  SQL_C_INTERVAL_DAY_TO_HOUR = SQL_INTERVAL_DAY_TO_HOUR;
  SQL_C_INTERVAL_DAY_TO_MINUTE = SQL_INTERVAL_DAY_TO_MINUTE;
  SQL_C_INTERVAL_DAY_TO_SECOND = SQL_INTERVAL_DAY_TO_SECOND;
  SQL_C_INTERVAL_HOUR_TO_MINUTE = SQL_INTERVAL_HOUR_TO_MINUTE;
  SQL_C_INTERVAL_HOUR_TO_SECOND = SQL_INTERVAL_HOUR_TO_SECOND;
  SQL_C_INTERVAL_MINUTE_TO_SECOND = SQL_INTERVAL_MINUTE_TO_SECOND;
  SQL_C_BINARY = SQL_BINARY;
  SQL_C_BIT = SQL_BIT;
  SQL_C_SBIGINT = (SQL_BIGINT + SQL_SIGNED_OFFSET); // SIGNED BIGINT
  SQL_C_UBIGINT = (SQL_BIGINT + SQL_UNSIGNED_OFFSET); // UNSIGNED BIGINT
  SQL_C_TINYINT = SQL_TINYINT;
  SQL_C_SLONG = (SQL_C_LONG + SQL_SIGNED_OFFSET); // SIGNED INTEGER
  SQL_C_SSHORT = (SQL_C_SHORT + SQL_SIGNED_OFFSET); // SIGNED SMALLINT
  SQL_C_STINYINT = (SQL_TINYINT + SQL_SIGNED_OFFSET); // SIGNED TINYINT
  SQL_C_ULONG = (SQL_C_LONG + SQL_UNSIGNED_OFFSET); // UNSIGNED INTEGER
  SQL_C_USHORT = (SQL_C_SHORT + SQL_UNSIGNED_OFFSET); // UNSIGNED SMALLINT
  SQL_C_UTINYINT = (SQL_TINYINT + SQL_UNSIGNED_OFFSET); // UNSIGNED TINYINT
  SQL_C_BOOKMARK = SQL_C_ULONG; // BOOKMARK
  SQL_C_GUID = SQL_GUID;

  SQL_TYPE_NULL = 0;
  SQL_C_VARBOOKMARK = SQL_C_BINARY;

  // define for SQL_DIAG_ROW_NUMBER and SQL_DIAG_COLUMN_NUMBER
  SQL_NO_ROW_NUMBER = (-1);
  SQL_NO_COLUMN_NUMBER = (-1);
  SQL_ROW_NUMBER_UNKNOWN = (-2);
  SQL_COLUMN_NUMBER_UNKNOWN = (-2);

  // SQLBindParameter extensions
  SQL_DEFAULT_PARAM = (-5);
  SQL_IGNORE = (-6);
  SQL_COLUMN_IGNORE = SQL_IGNORE;
  SQL_LEN_DATA_AT_EXEC_OFFSET = (-100);

{$IFNDEF DynamicOdbcImport}
function SQL_LEN_DATA_AT_EXEC(length: Integer): Integer;
{$ENDIF}

const
  // binary length for driver specific attributes
  SQL_LEN_BINARY_ATTR_OFFSET = (-100);

{$IFNDEF DynamicOdbcImport}
function SQL_LEN_BINARY_ATTR(length: Integer): Integer;
{$ENDIF}

const
  //=====================================
  // SQLBindParameter block moved to here because of dependent decarations

  // Defines for SQLBindParameter and
  // SQLProcedureColumns (returned in the result set)
  SQL_PARAM_TYPE_UNKNOWN = 0;
  SQL_PARAM_INPUT = 1;
  SQL_PARAM_INPUT_OUTPUT = 2;
  SQL_RESULT_COL = 3;
  SQL_PARAM_OUTPUT = 4;
  SQL_RETURN_VALUE = 5;
  // End of moved block
  //=====================================

  // Defines used by Driver Manager when mapping SQLSetParam to SQLBindParameter
  SQL_PARAM_TYPE_DEFAULT = SQL_PARAM_INPUT_OUTPUT;
  SQL_SETPARAM_VALUE_MAX = (-1);

  // SQLColAttributes block
  // WAS ORIGINALLY HERE
  // Moved above because of dependent declarations

  //*******************************************
  // SQLGetFunctions: additional values for
  // fFunction to represent functions that
  // are not in the X/Open spec.
  //*******************************************

  SQL_API_SQLALLOCHANDLESTD = 73;
  SQL_API_SQLBULKOPERATIONS = 24;
  SQL_API_SQLBINDPARAMETER = 72;
  SQL_API_SQLBROWSECONNECT = 55;
  SQL_API_SQLCOLATTRIBUTES = 6;
  SQL_API_SQLCOLUMNPRIVILEGES = 56;
  SQL_API_SQLDESCRIBEPARAM = 58;
  SQL_API_SQLDRIVERCONNECT = 41;
  SQL_API_SQLDRIVERS = 71;
  SQL_API_SQLEXTENDEDFETCH = 59;
  SQL_API_SQLFOREIGNKEYS = 60;
  SQL_API_SQLMORERESULTS = 61;
  SQL_API_SQLNATIVESQL = 62;
  SQL_API_SQLNUMPARAMS = 63;
  SQL_API_SQLPARAMOPTIONS = 64;
  SQL_API_SQLPRIMARYKEYS = 65;
  SQL_API_SQLPROCEDURECOLUMNS = 66;
  SQL_API_SQLPROCEDURES = 67;
  SQL_API_SQLSETPOS = 68;
  SQL_API_SQLSETSCROLLOPTIONS = 69;
  SQL_API_SQLTABLEPRIVILEGES = 70;

  //--------------------------------------------
  // SQL_API_ALL_FUNCTIONS returns an array
  // of 'booleans' representing whether a
  // function is implemented by the driver.
  //
  // CAUTION: Only functions defined in ODBC
  // version 2.0 and earlier are returned, the
  // new high-range function numbers defined by
  // X/Open break this scheme. See the new
  // method -- SQL_API_ODBC3_ALL_FUNCTIONS
  //--------------------------------------------

  SQL_API_ALL_FUNCTIONS = 0; // See CAUTION above

  //----------------------------------------------
  // 2.X drivers export a dummy function with
  // ordinal number SQL_API_LOADBYORDINAL to speed
  // loading under the windows operating system.
  //
  // CAUTION: Loading by ordinal is not supported
  // for 3.0 and above drivers.
  //----------------------------------------------

  SQL_API_LOADBYORDINAL = 199; // See CAUTION above

  //----------------------------------------------
  // SQL_API_ODBC3_ALL_FUNCTIONS
  // This returns a bitmap, which allows us to*
  // handle the higher-valued function numbers.
  // Use SQL_FUNC_EXISTS(bitmap,function_number)
  // to determine if the function exists.
  //----------------------------------------------

  SQL_API_ODBC3_ALL_FUNCTIONS = 999;
  SQL_API_ODBC3_ALL_FUNCTIONS_SIZE = 250; // array of 250 words

{$IFNDEF DynamicOdbcImport}
function SQL_FUNC_EXISTS(pfExists: PUWord; uwAPI: UWord): SqlInteger;
{$ENDIF}

const
  //***********************************************
  // Extended definitions for SQLGetInfo
  //***********************************************

  //---------------------------------
  // Values in ODBC 2.0 that are not
  // in the X/Open spec
  //---------------------------------
  SQL_INFO_FIRST = 0;
  SQL_ACTIVE_CONNECTIONS = 0; // MAX_DRIVER_CONNECTIONS
  SQL_ACTIVE_STATEMENTS = 1; // MAX_CONCURRENT_ACTIVITIES
  SQL_DRIVER_HDBC = 3;
  SQL_DRIVER_HENV = 4;
  SQL_DRIVER_HSTMT = 5;
  SQL_DRIVER_NAME = 6;
  SQL_DRIVER_VER = 7;
  SQL_ODBC_API_CONFORMANCE = 9;
  SQL_ODBC_VER = 10;
  SQL_ROW_UPDATES = 11;
  SQL_ODBC_SAG_CLI_CONFORMANCE = 12;
  SQL_ODBC_SQL_CONFORMANCE = 15;
  SQL_PROCEDURES = 21;
  SQL_CONCAT_NULL_BEHAVIOR = 22;
  SQL_CURSOR_ROLLBACK_BEHAVIOR = 24;
  SQL_EXPRESSIONS_IN_ORDERBY = 27;
  SQL_MAX_OWNER_NAME_LEN = 32; // MAX_SCHEMA_NAME_LEN
  SQL_MAX_PROCEDURE_NAME_LEN = 33;
  SQL_MAX_QUALIFIER_NAME_LEN = 34; // MAX_CATALOG_NAME_LEN
  SQL_MULT_RESULT_SETS = 36;
  SQL_MULTIPLE_ACTIVE_TXN = 37;
  SQL_OUTER_JOINS = 38;
  SQL_OWNER_TERM = 39;
  SQL_PROCEDURE_TERM = 40;
  SQL_QUALIFIER_NAME_SEPARATOR = 41;
  SQL_QUALIFIER_TERM = 42;
  SQL_SCROLL_OPTIONS = 44;
  SQL_TABLE_TERM = 45;
  SQL_CONVERT_FUNCTIONS = 48;
  SQL_NUMERIC_FUNCTIONS = 49;
  SQL_STRING_FUNCTIONS = 50;
  SQL_SYSTEM_FUNCTIONS = 51;
  SQL_TIMEDATE_FUNCTIONS = 52;
  SQL_CONVERT_BIGINT = 53;
  SQL_CONVERT_BINARY = 54;
  SQL_CONVERT_BIT = 55;
  SQL_CONVERT_CHAR = 56;
  SQL_CONVERT_DATE = 57;
  SQL_CONVERT_DECIMAL = 58;
  SQL_CONVERT_DOUBLE = 59;
  SQL_CONVERT_FLOAT = 60;
  SQL_CONVERT_INTEGER = 61;
  SQL_CONVERT_LONGVARCHAR = 62;
  SQL_CONVERT_NUMERIC = 63;
  SQL_CONVERT_REAL = 64;
  SQL_CONVERT_SMALLINT = 65;
  SQL_CONVERT_TIME = 66;
  SQL_CONVERT_TIMESTAMP = 67;
  SQL_CONVERT_TINYINT = 68;
  SQL_CONVERT_VARBINARY = 69;
  SQL_CONVERT_VARCHAR = 70;
  SQL_CONVERT_LONGVARBINARY = 71;
  SQL_ODBC_SQL_OPT_IEF = 73; // SQL_INTEGRITY
  SQL_CORRELATION_NAME = 74;
  SQL_NON_NULLABLE_COLUMNS = 75;
  SQL_DRIVER_HLIB = 76;
  SQL_DRIVER_ODBC_VER = 77;
  SQL_LOCK_TYPES = 78;
  SQL_POS_OPERATIONS = 79;
  SQL_POSITIONED_STATEMENTS = 80;
  SQL_BOOKMARK_PERSISTENCE = 82;
  SQL_STATIC_SENSITIVITY = 83;
  SQL_FILE_USAGE = 84;
  SQL_COLUMN_ALIAS = 87;
  SQL_GROUP_BY = 88;
  SQL_KEYWORDS = 89;
  SQL_OWNER_USAGE = 91;
  SQL_QUALIFIER_USAGE = 92;
  SQL_QUOTED_IDENTIFIER_CASE = 93;
  SQL_SUBQUERIES = 95;
  SQL_UNION = 96;
  SQL_MAX_ROW_SIZE_INCLUDES_LONG = 103;
  SQL_MAX_CHAR_LITERAL_LEN = 108;
  SQL_TIMEDATE_ADD_INTERVALS = 109;
  SQL_TIMEDATE_DIFF_INTERVALS = 110;
  SQL_NEED_LONG_DATA_LEN = 111;
  SQL_MAX_BINARY_LITERAL_LEN = 112;
  SQL_LIKE_ESCAPE_CLAUSE = 113;
  SQL_QUALIFIER_LOCATION = 114;

  //-----------------------------------------------
  // ODBC 3.0 SQLGetInfo values that are not part
  // of the X/Open standard at this time. X/Open
  // standard values are in sql.h.
  //-----------------------------------------------

  SQL_ACTIVE_ENVIRONMENTS = 116;
  SQL_ALTER_DOMAIN = 117;
  SQL_SQL_CONFORMANCE = 118;
  SQL_DATETIME_LITERALS = 119;
  SQL_ASYNC_MODE = 10021; // new X/Open spec
  SQL_BATCH_ROW_COUNT = 120;
  SQL_BATCH_SUPPORT = 121;
  SQL_CATALOG_LOCATION = SQL_QUALIFIER_LOCATION;
  SQL_CATALOG_NAME_SEPARATOR = SQL_QUALIFIER_NAME_SEPARATOR;
  SQL_CATALOG_TERM = SQL_QUALIFIER_TERM;
  SQL_CATALOG_USAGE = SQL_QUALIFIER_USAGE;
  SQL_CONVERT_WCHAR = 122;
  SQL_CONVERT_INTERVAL_DAY_TIME = 123;
  SQL_CONVERT_INTERVAL_YEAR_MONTH = 124;
  SQL_CONVERT_WLONGVARCHAR = 125;
  SQL_CONVERT_WVARCHAR = 126;
  SQL_CREATE_ASSERTION = 127;
  SQL_CREATE_CHARACTER_SET = 128;
  SQL_CREATE_COLLATION = 129;
  SQL_CREATE_DOMAIN = 130;
  SQL_CREATE_SCHEMA = 131;
  SQL_CREATE_TABLE = 132;
  SQL_CREATE_TRANSLATION = 133;
  SQL_CREATE_VIEW = 134;
  SQL_DRIVER_HDESC = 135;
  SQL_DROP_ASSERTION = 136;
  SQL_DROP_CHARACTER_SET = 137;
  SQL_DROP_COLLATION = 138;
  SQL_DROP_DOMAIN = 139;
  SQL_DROP_SCHEMA = 140;
  SQL_DROP_TABLE = 141;
  SQL_DROP_TRANSLATION = 142;
  SQL_DROP_VIEW = 143;
  SQL_DYNAMIC_CURSOR_ATTRIBUTES1 = 144;
  SQL_DYNAMIC_CURSOR_ATTRIBUTES2 = 145;
  SQL_FORWARD_ONLY_CURSOR_ATTRIBUTES1 = 146;
  SQL_FORWARD_ONLY_CURSOR_ATTRIBUTES2 = 147;
  SQL_INDEX_KEYWORDS = 148;
  SQL_INFO_SCHEMA_VIEWS = 149;
  SQL_KEYSET_CURSOR_ATTRIBUTES1 = 150;
  SQL_KEYSET_CURSOR_ATTRIBUTES2 = 151;
  SQL_MAX_ASYNC_CONCURRENT_STATEMENTS = 10022; // new X/Open spec
  SQL_ODBC_INTERFACE_CONFORMANCE = 152;
  SQL_PARAM_ARRAY_ROW_COUNTS = 153;
  SQL_PARAM_ARRAY_SELECTS = 154;
  SQL_SCHEMA_TERM = SQL_OWNER_TERM;
  SQL_SCHEMA_USAGE = SQL_OWNER_USAGE;
  SQL_SQL92_DATETIME_FUNCTIONS = 155;
  SQL_SQL92_FOREIGN_KEY_DELETE_RULE = 156;
  SQL_SQL92_FOREIGN_KEY_UPDATE_RULE = 157;
  SQL_SQL92_GRANT = 158;
  SQL_SQL92_NUMERIC_VALUE_FUNCTIONS = 159;
  SQL_SQL92_PREDICATES = 160;
  SQL_SQL92_RELATIONAL_JOIN_OPERATORS = 161;
  SQL_SQL92_REVOKE = 162;
  SQL_SQL92_ROW_VALUE_CONSTRUCTOR = 163;
  SQL_SQL92_STRING_FUNCTIONS = 164;
  SQL_SQL92_VALUE_EXPRESSIONS = 165;
  SQL_STANDARD_CLI_CONFORMANCE = 166;
  SQL_STATIC_CURSOR_ATTRIBUTES1 = 167;
  SQL_STATIC_CURSOR_ATTRIBUTES2 = 168;
  SQL_AGGREGATE_FUNCTIONS = 169;
  SQL_DDL_INDEX = 170;
  SQL_DM_VER = 171;
  SQL_INSERT_STATEMENT = 172;
  SQL_CONVERT_GUID = 173;
  SQL_UNION_STATEMENT = SQL_UNION;

  SQL_DTC_TRANSITION_COST = 1750;

  // SQL_ALTER_TABLE bitmasks
  // the following bitmasks are defined in sql.h
  {
    SQL_AT_ADD_COLUMN = $00000001;
    SQL_AT_DROP_COLUMN = $00000002;
    SQL_AT_ADD_CONSTRAINT = $00000008;
  //= ODBC 3
    SQL_AT_ADD_COLUMN_SINGLE = $00000020;
    SQL_AT_ADD_COLUMN_DEFAULT = $00000040;
    SQL_AT_ADD_COLUMN_COLLATION = $00000080;
    SQL_AT_SET_COLUMN_DEFAULT = $00000100;
    SQL_AT_DROP_COLUMN_DEFAULT = $00000200;
    SQL_AT_DROP_COLUMN_CASCADE = $00000400;
    SQL_AT_DROP_COLUMN_RESTRICT = $00000800;
    SQL_AT_ADD_TABLE_CONSTRAINT = $00001000;
    SQL_AT_DROP_TABLE_CONSTRAINT_CASCADE = $00002000;
    SQL_AT_DROP_TABLE_CONSTRAINT_RESTRICT = $00004000;
    SQL_AT_CONSTRAINT_NAME_DEFINITION = $00008000;
    SQL_AT_CONSTRAINT_INITIALLY_DEFERRED = $00010000;
    SQL_AT_CONSTRAINT_INITIALLY_IMMEDIATE = $00020000;
    SQL_AT_CONSTRAINT_DEFERRABLE = $00040000;
    SQL_AT_CONSTRAINT_NON_DEFERRABLE = $00080000;
  }
  // SQL_CONVERT_* return value bitmasks
  SQL_CVT_CHAR = $00000001;
  SQL_CVT_NUMERIC = $00000002;
  SQL_CVT_DECIMAL = $00000004;
  SQL_CVT_INTEGER = $00000008;
  SQL_CVT_SMALLINT = $00000010;
  SQL_CVT_FLOAT = $00000020;
  SQL_CVT_REAL = $00000040;
  SQL_CVT_DOUBLE = $00000080;
  SQL_CVT_VARCHAR = $00000100;
  SQL_CVT_LONGVARCHAR = $00000200;
  SQL_CVT_BINARY = $00000400;
  SQL_CVT_VARBINARY = $00000800;
  SQL_CVT_BIT = $00001000;
  SQL_CVT_TINYINT = $00002000;
  SQL_CVT_BIGINT = $00004000;
  SQL_CVT_DATE = $00008000;
  SQL_CVT_TIME = $00010000;
  SQL_CVT_TIMESTAMP = $00020000;
  SQL_CVT_LONGVARBINARY = $00040000;
  SQL_CVT_INTERVAL_YEAR_MONTH = $00080000;
  SQL_CVT_INTERVAL_DAY_TIME = $00100000;
  SQL_CVT_WCHAR = $00200000;
  SQL_CVT_WLONGVARCHAR = $00400000;
  SQL_CVT_WVARCHAR = $00800000;
  SQL_CVT_GUID = $01000000;

  // SQL_CONVERT_FUNCTIONS functions
  SQL_FN_CVT_CONVERT = $00000001;
  SQL_FN_CVT_CAST = $00000002;

  // SQL_STRING_FUNCTIONS functions
  SQL_FN_STR_CONCAT = $00000001;
  SQL_FN_STR_INSERT = $00000002;
  SQL_FN_STR_LEFT = $00000004;
  SQL_FN_STR_LTRIM = $00000008;
  SQL_FN_STR_LENGTH = $00000010;
  SQL_FN_STR_LOCATE = $00000020;
  SQL_FN_STR_LCASE = $00000040;
  SQL_FN_STR_REPEAT = $00000080;
  SQL_FN_STR_REPLACE = $00000100;
  SQL_FN_STR_RIGHT = $00000200;
  SQL_FN_STR_RTRIM = $00000400;
  SQL_FN_STR_SUBSTRING = $00000800;
  SQL_FN_STR_UCASE = $00001000;
  SQL_FN_STR_ASCII = $00002000;
  SQL_FN_STR_CHAR = $00004000;
  SQL_FN_STR_DIFFERENCE = $00008000;
  SQL_FN_STR_LOCATE_2 = $00010000;
  SQL_FN_STR_SOUNDEX = $00020000;
  SQL_FN_STR_SPACE = $00040000;
  SQL_FN_STR_BIT_LENGTH = $00080000;
  SQL_FN_STR_CHAR_LENGTH = $00100000;
  SQL_FN_STR_CHARACTER_LENGTH = $00200000;
  SQL_FN_STR_OCTET_LENGTH = $00400000;
  SQL_FN_STR_POSITION = $00800000;

  // SQL_SQL92_STRING_FUNCTIONS
  SQL_SSF_CONVERT = $00000001;
  SQL_SSF_LOWER = $00000002;
  SQL_SSF_UPPER = $00000004;
  SQL_SSF_SUBSTRING = $00000008;
  SQL_SSF_TRANSLATE = $00000010;
  SQL_SSF_TRIM_BOTH = $00000020;
  SQL_SSF_TRIM_LEADING = $00000040;
  SQL_SSF_TRIM_TRAILING = $00000080;

  // SQL_NUMERIC_FUNCTIONS functions
  SQL_FN_NUM_ABS = $00000001;
  SQL_FN_NUM_ACOS = $00000002;
  SQL_FN_NUM_ASIN = $00000004;
  SQL_FN_NUM_ATAN = $00000008;
  SQL_FN_NUM_ATAN2 = $00000010;
  SQL_FN_NUM_CEILING = $00000020;
  SQL_FN_NUM_COS = $00000040;
  SQL_FN_NUM_COT = $00000080;
  SQL_FN_NUM_EXP = $00000100;
  SQL_FN_NUM_FLOOR = $00000200;
  SQL_FN_NUM_LOG = $00000400;
  SQL_FN_NUM_MOD = $00000800;
  SQL_FN_NUM_SIGN = $00001000;
  SQL_FN_NUM_SIN = $00002000;
  SQL_FN_NUM_SQRT = $00004000;
  SQL_FN_NUM_TAN = $00008000;
  SQL_FN_NUM_PI = $00010000;
  SQL_FN_NUM_RAND = $00020000;
  SQL_FN_NUM_DEGREES = $00040000;
  SQL_FN_NUM_LOG10 = $00080000;
  SQL_FN_NUM_POWER = $00100000;
  SQL_FN_NUM_RADIANS = $00200000;
  SQL_FN_NUM_ROUND = $00400000;
  SQL_FN_NUM_TRUNCATE = $00800000;

  // SQL_SQL92_NUMERIC_VALUE_FUNCTIONS
  SQL_SNVF_BIT_LENGTH = $00000001;
  SQL_SNVF_CHAR_LENGTH = $00000002;
  SQL_SNVF_CHARACTER_LENGTH = $00000004;
  SQL_SNVF_EXTRACT = $00000008;
  SQL_SNVF_OCTET_LENGTH = $00000010;
  SQL_SNVF_POSITION = $00000020;

  // SQL_TIMEDATE_FUNCTIONS functions
  SQL_FN_TD_NOW = $00000001;
  SQL_FN_TD_CURDATE = $00000002;
  SQL_FN_TD_DAYOFMONTH = $00000004;
  SQL_FN_TD_DAYOFWEEK = $00000008;
  SQL_FN_TD_DAYOFYEAR = $00000010;
  SQL_FN_TD_MONTH = $00000020;
  SQL_FN_TD_QUARTER = $00000040;
  SQL_FN_TD_WEEK = $00000080;
  SQL_FN_TD_YEAR = $00000100;
  SQL_FN_TD_CURTIME = $00000200;
  SQL_FN_TD_HOUR = $00000400;
  SQL_FN_TD_MINUTE = $00000800;
  SQL_FN_TD_SECOND = $00001000;
  SQL_FN_TD_TIMESTAMPADD = $00002000;
  SQL_FN_TD_TIMESTAMPDIFF = $00004000;
  SQL_FN_TD_DAYNAME = $00008000;
  SQL_FN_TD_MONTHNAME = $00010000;
  SQL_FN_TD_CURRENT_DATE = $00020000;
  SQL_FN_TD_CURRENT_TIME = $00040000;
  SQL_FN_TD_CURRENT_TIMESTAMP = $00080000;
  SQL_FN_TD_EXTRACT = $00100000;

  // SQL_SQL92_DATETIME_FUNCTIONS
  SQL_SDF_CURRENT_DATE = $00000001;
  SQL_SDF_CURRENT_TIME = $00000002;
  SQL_SDF_CURRENT_TIMESTAMP = $00000004;

  // SQL_SYSTEM_FUNCTIONS functions
  SQL_FN_SYS_USERNAME = $00000001;
  SQL_FN_SYS_DBNAME = $00000002;
  SQL_FN_SYS_IFNULL = $00000004;

  // SQL_TIMEDATE_ADD_INTERVALS and SQL_TIMEDATE_DIFF_INTERVALS functions
  SQL_FN_TSI_FRAC_SECOND = $00000001;
  SQL_FN_TSI_SECOND = $00000002;
  SQL_FN_TSI_MINUTE = $00000004;
  SQL_FN_TSI_HOUR = $00000008;
  SQL_FN_TSI_DAY = $00000010;
  SQL_FN_TSI_WEEK = $00000020;
  SQL_FN_TSI_MONTH = $00000040;
  SQL_FN_TSI_QUARTER = $00000080;
  SQL_FN_TSI_YEAR = $00000100;

  // bitmasks for SQL_DYNAMIC_CURSOR_ATTRIBUTES1,
  //- SQL_FORWARD_ONLY_CURSOR_ATTRIBUTES1,
  //- SQL_KEYSET_CURSOR_ATTRIBUTES1, and SQL_STATIC_CURSOR_ATTRIBUTES1
  //=

  // supported SQLFetchScroll FetchOrientation's
  SQL_CA1_NEXT = $00000001;
  SQL_CA1_ABSOLUTE = $00000002;
  SQL_CA1_RELATIVE = $00000004;
  SQL_CA1_BOOKMARK = $00000008;

  // supported SQLSetPos LockType's
  SQL_CA1_LOCK_NO_CHANGE = $00000040;
  SQL_CA1_LOCK_EXCLUSIVE = $00000080;
  SQL_CA1_LOCK_UNLOCK = $00000100;

  // supported SQLSetPos Operations
  SQL_CA1_POS_POSITION = $00000200;
  SQL_CA1_POS_UPDATE = $00000400;
  SQL_CA1_POS_DELETE = $00000800;
  SQL_CA1_POS_REFRESH = $00001000;

  // positioned updates and deletes
  SQL_CA1_POSITIONED_UPDATE = $00002000;
  SQL_CA1_POSITIONED_DELETE = $00004000;
  SQL_CA1_SELECT_FOR_UPDATE = $00008000;

  // supported SQLBulkOperations operations
  SQL_CA1_BULK_ADD = $00010000;
  SQL_CA1_BULK_UPDATE_BY_BOOKMARK = $00020000;
  SQL_CA1_BULK_DELETE_BY_BOOKMARK = $00040000;
  SQL_CA1_BULK_FETCH_BY_BOOKMARK = $00080000;

  // bitmasks for SQL_DYNAMIC_CURSOR_ATTRIBUTES2,
  //- SQL_FORWARD_ONLY_CURSOR_ATTRIBUTES2,
  //- SQL_KEYSET_CURSOR_ATTRIBUTES2, and SQL_STATIC_CURSOR_ATTRIBUTES2
  //=

  // supported values for SQL_ATTR_SCROLL_CONCURRENCY
  SQL_CA2_READ_ONLY_CONCURRENCY = $00000001;
  SQL_CA2_LOCK_CONCURRENCY = $00000002;
  SQL_CA2_OPT_ROWVER_CONCURRENCY = $00000004;
  SQL_CA2_OPT_VALUES_CONCURRENCY = $00000008;

  // sensitivity of the cursor to its own inserts, deletes, and updates
  SQL_CA2_SENSITIVITY_ADDITIONS = $00000010;
  SQL_CA2_SENSITIVITY_DELETIONS = $00000020;
  SQL_CA2_SENSITIVITY_UPDATES = $00000040;

  // semantics of SQL_ATTR_MAX_ROWS
  SQL_CA2_MAX_ROWS_SELECT = $00000080;
  SQL_CA2_MAX_ROWS_INSERT = $00000100;
  SQL_CA2_MAX_ROWS_DELETE = $00000200;
  SQL_CA2_MAX_ROWS_UPDATE = $00000400;
  SQL_CA2_MAX_ROWS_CATALOG = $00000800;
  SQL_CA2_MAX_ROWS_AFFECTS_ALL = (SQL_CA2_MAX_ROWS_SELECT or
    SQL_CA2_MAX_ROWS_INSERT or SQL_CA2_MAX_ROWS_DELETE or
    SQL_CA2_MAX_ROWS_UPDATE or SQL_CA2_MAX_ROWS_CATALOG);

  // semantics of SQL_DIAG_CURSOR_ROW_COUNT
  SQL_CA2_CRC_EXACT = $00001000;
  SQL_CA2_CRC_APPROXIMATE = $00002000;

  // the kinds of positioned statements that can be simulated
  SQL_CA2_SIMULATE_NON_UNIQUE = $00004000;
  SQL_CA2_SIMULATE_TRY_UNIQUE = $00008000;
  SQL_CA2_SIMULATE_UNIQUE = $00010000;

  // SQL_ODBC_API_CONFORMANCE values
  SQL_OAC_NONE = $0000;
  SQL_OAC_LEVEL1 = $0001;
  SQL_OAC_LEVEL2 = $0002;

  // SQL_ODBC_SAG_CLI_CONFORMANCE values
  SQL_OSCC_NOT_COMPLIANT = $0000;
  SQL_OSCC_COMPLIANT = $0001;

  // SQL_ODBC_SQL_CONFORMANCE values
  SQL_OSC_MINIMUM = $0000;
  SQL_OSC_CORE = $0001;
  SQL_OSC_EXTENDED = $0002;

  // SQL_CONCAT_NULL_BEHAVIOR values
  SQL_CB_NULL = $0000;
  SQL_CB_NON_NULL = $0001;

  // SQL_SCROLL_OPTIONS masks
  SQL_SO_FORWARD_ONLY = $00000001;
  SQL_SO_KEYSET_DRIVEN = $00000002;
  SQL_SO_DYNAMIC = $00000004;
  SQL_SO_MIXED = $00000008;
  SQL_SO_STATIC = $00000010;

  // SQL_FETCH_DIRECTION masks
  SQL_FD_FETCH_RESUME = $00000040; // SQL_FETCH_RESUME is no longer supported
  SQL_FD_FETCH_BOOKMARK = $00000080;

  // SQL_TXN_ISOLATION_OPTION masks
  SQL_TXN_VERSIONING = $00000010; // SQL_TXN_VERSIONING is no longer supported

  // SQL_CORRELATION_NAME values
  SQL_CN_NONE = $0000;
  SQL_CN_DIFFERENT = $0001;
  SQL_CN_ANY = $0002;

  // SQL_NON_NULLABLE_COLUMNS values
  SQL_NNC_NULL = $0000;
  SQL_NNC_NON_NULL = $0001;

  // SQL_NULL_COLLATION values
  SQL_NC_START = $0002;
  SQL_NC_END = $0004;

  // SQL_FILE_USAGE values
  SQL_FILE_NOT_SUPPORTED = $0000;
  SQL_FILE_TABLE = $0001;
  SQL_FILE_QUALIFIER = $0002;
  SQL_FILE_CATALOG = SQL_FILE_QUALIFIER; // ODBC 3.0

  // SQL_GETDATA_EXTENSIONS values
  SQL_GD_BLOCK = $00000004;
  SQL_GD_BOUND = $00000008;

  // SQL_POSITIONED_STATEMENTS masks
  SQL_PS_POSITIONED_DELETE = $00000001;
  SQL_PS_POSITIONED_UPDATE = $00000002;
  SQL_PS_SELECT_FOR_UPDATE = $00000004;

  // SQL_GROUP_BY values
  SQL_GB_NOT_SUPPORTED = $0000;
  SQL_GB_GROUP_BY_EQUALS_SELECT = $0001;
  SQL_GB_GROUP_BY_CONTAINS_SELECT = $0002;
  SQL_GB_NO_RELATION = $0003;
  SQL_GB_COLLATE = $0004;

  // SQL_OWNER_USAGE masks
  SQL_OU_DML_STATEMENTS = $00000001;
  SQL_OU_PROCEDURE_INVOCATION = $00000002;
  SQL_OU_TABLE_DEFINITION = $00000004;
  SQL_OU_INDEX_DEFINITION = $00000008;
  SQL_OU_PRIVILEGE_DEFINITION = $00000010;

  // SQL_SCHEMA_USAGE masks
  SQL_SU_DML_STATEMENTS = SQL_OU_DML_STATEMENTS;
  SQL_SU_PROCEDURE_INVOCATION = SQL_OU_PROCEDURE_INVOCATION;
  SQL_SU_TABLE_DEFINITION = SQL_OU_TABLE_DEFINITION;
  SQL_SU_INDEX_DEFINITION = SQL_OU_INDEX_DEFINITION;
  SQL_SU_PRIVILEGE_DEFINITION = SQL_OU_PRIVILEGE_DEFINITION;

  // SQL_QUALIFIER_USAGE masks
  SQL_QU_DML_STATEMENTS = $00000001;
  SQL_QU_PROCEDURE_INVOCATION = $00000002;
  SQL_QU_TABLE_DEFINITION = $00000004;
  SQL_QU_INDEX_DEFINITION = $00000008;
  SQL_QU_PRIVILEGE_DEFINITION = $00000010;

  // SQL_CATALOG_USAGE masks
  SQL_CU_DML_STATEMENTS = SQL_QU_DML_STATEMENTS;
  SQL_CU_PROCEDURE_INVOCATION = SQL_QU_PROCEDURE_INVOCATION;
  SQL_CU_TABLE_DEFINITION = SQL_QU_TABLE_DEFINITION;
  SQL_CU_INDEX_DEFINITION = SQL_QU_INDEX_DEFINITION;
  SQL_CU_PRIVILEGE_DEFINITION = SQL_QU_PRIVILEGE_DEFINITION;

  // SQL_SUBQUERIES masks
  SQL_SQ_COMPARISON = $00000001;
  SQL_SQ_EXISTS = $00000002;
  SQL_SQ_IN = $00000004;
  SQL_SQ_QUANTIFIED = $00000008;
  SQL_SQ_CORRELATED_SUBQUERIES = $00000010;

  // SQL_UNION masks
  SQL_U_UNION = $00000001;
  SQL_U_UNION_ALL = $00000002;

  // SQL_BOOKMARK_PERSISTENCE values
  SQL_BP_CLOSE = $00000001;
  SQL_BP_DELETE = $00000002;
  SQL_BP_DROP = $00000004;
  SQL_BP_TRANSACTION = $00000008;
  SQL_BP_UPDATE = $00000010;
  SQL_BP_OTHER_HSTMT = $00000020;
  SQL_BP_SCROLL = $00000040;

  // SQL_STATIC_SENSITIVITY values
  SQL_SS_ADDITIONS = $00000001;
  SQL_SS_DELETIONS = $00000002;
  SQL_SS_UPDATES = $00000004;

  // SQL_VIEW values
  SQL_CV_CREATE_VIEW = $00000001;
  SQL_CV_CHECK_OPTION = $00000002;
  SQL_CV_CASCADED = $00000004;
  SQL_CV_LOCAL = $00000008;

  // SQL_LOCK_TYPES masks
  SQL_LCK_NO_CHANGE = $00000001;
  SQL_LCK_EXCLUSIVE = $00000002;
  SQL_LCK_UNLOCK = $00000004;

  // SQL_POS_OPERATIONS masks
  SQL_POS_POSITION = $00000001;
  SQL_POS_REFRESH = $00000002;
  SQL_POS_UPDATE = $00000004;
  SQL_POS_DELETE = $00000008;
  SQL_POS_ADD = $00000010;

  // SQL_QUALIFIER_LOCATION values
  SQL_QL_START = $0001;
  SQL_QL_END = $0002;

  // Here start return values for ODBC 3.0 SQLGetInfo

  // SQL_AGGREGATE_FUNCTIONS bitmasks
  SQL_AF_AVG = $00000001;
  SQL_AF_COUNT = $00000002;
  SQL_AF_MAX = $00000004;
  SQL_AF_MIN = $00000008;
  SQL_AF_SUM = $00000010;
  SQL_AF_DISTINCT = $00000020;
  SQL_AF_ALL = $00000040;

  // SQL_SQL_CONFORMANCE bit masks
  SQL_SC_SQL92_ENTRY = $00000001;
  SQL_SC_FIPS127_2_TRANSITIONAL = $00000002;
  SQL_SC_SQL92_INTERMEDIATE = $00000004;
  SQL_SC_SQL92_FULL = $00000008;

  // SQL_DATETIME_LITERALS masks
  SQL_DL_SQL92_DATE = $00000001;
  SQL_DL_SQL92_TIME = $00000002;
  SQL_DL_SQL92_TIMESTAMP = $00000004;
  SQL_DL_SQL92_INTERVAL_YEAR = $00000008;
  SQL_DL_SQL92_INTERVAL_MONTH = $00000010;
  SQL_DL_SQL92_INTERVAL_DAY = $00000020;
  SQL_DL_SQL92_INTERVAL_HOUR = $00000040;
  SQL_DL_SQL92_INTERVAL_MINUTE = $00000080;
  SQL_DL_SQL92_INTERVAL_SECOND = $00000100;
  SQL_DL_SQL92_INTERVAL_YEAR_TO_MONTH = $00000200;
  SQL_DL_SQL92_INTERVAL_DAY_TO_HOUR = $00000400;
  SQL_DL_SQL92_INTERVAL_DAY_TO_MINUTE = $00000800;
  SQL_DL_SQL92_INTERVAL_DAY_TO_SECOND = $00001000;
  SQL_DL_SQL92_INTERVAL_HOUR_TO_MINUTE = $00002000;
  SQL_DL_SQL92_INTERVAL_HOUR_TO_SECOND = $00004000;
  SQL_DL_SQL92_INTERVAL_MINUTE_TO_SECOND = $00008000;

  // SQL_CATALOG_LOCATION values
  SQL_CL_START = SQL_QL_START;
  SQL_CL_END = SQL_QL_END;

  // values for SQL_BATCH_ROW_COUNT
  SQL_BRC_PROCEDURES = $0000001;
  SQL_BRC_EXPLICIT = $0000002;
  SQL_BRC_ROLLED_UP = $0000004;

  // bitmasks for SQL_BATCH_SUPPORT
  SQL_BS_SELECT_EXPLICIT = $00000001;
  SQL_BS_ROW_COUNT_EXPLICIT = $00000002;
  SQL_BS_SELECT_PROC = $00000004;
  SQL_BS_ROW_COUNT_PROC = $00000008;

  // Values for SQL_PARAM_ARRAY_ROW_COUNTS getinfo
  SQL_PARC_BATCH = 1;
  SQL_PARC_NO_BATCH = 2;

  // values for SQL_PARAM_ARRAY_SELECTS
  SQL_PAS_BATCH = 1;
  SQL_PAS_NO_BATCH = 2;
  SQL_PAS_NO_SELECT = 3;

  // Bitmasks for SQL_INDEX_KEYWORDS
  SQL_IK_NONE = $00000000;
  SQL_IK_ASC = $00000001;
  SQL_IK_DESC = $00000002;
  SQL_IK_ALL = (SQL_IK_ASC or SQL_IK_DESC);

  // Bitmasks for SQL_INFO_SCHEMA_VIEWS
  SQL_ISV_ASSERTIONS = $00000001;
  SQL_ISV_CHARACTER_SETS = $00000002;
  SQL_ISV_CHECK_CONSTRAINTS = $00000004;
  SQL_ISV_COLLATIONS = $00000008;
  SQL_ISV_COLUMN_DOMAIN_USAGE = $00000010;
  SQL_ISV_COLUMN_PRIVILEGES = $00000020;
  SQL_ISV_COLUMNS = $00000040;
  SQL_ISV_CONSTRAINT_COLUMN_USAGE = $00000080;
  SQL_ISV_CONSTRAINT_TABLE_USAGE = $00000100;
  SQL_ISV_DOMAIN_CONSTRAINTS = $00000200;
  SQL_ISV_DOMAINS = $00000400;
  SQL_ISV_KEY_COLUMN_USAGE = $00000800;
  SQL_ISV_REFERENTIAL_CONSTRAINTS = $00001000;
  SQL_ISV_SCHEMATA = $00002000;
  SQL_ISV_SQL_LANGUAGES = $00004000;
  SQL_ISV_TABLE_CONSTRAINTS = $00008000;
  SQL_ISV_TABLE_PRIVILEGES = $00010000;
  SQL_ISV_TABLES = $00020000;
  SQL_ISV_TRANSLATIONS = $00040000;
  SQL_ISV_USAGE_PRIVILEGES = $00080000;
  SQL_ISV_VIEW_COLUMN_USAGE = $00100000;
  SQL_ISV_VIEW_TABLE_USAGE = $00200000;
  SQL_ISV_VIEWS = $00400000;

  // Bitmasks for SQL_ASYNC_MODE
  // Already declared in sql.h
  {
    SQL_AM_NONE = 0;
    SQL_AM_CONNECTION = 1;
    SQL_AM_STATEMENT = 2;
  }

  // Bitmasks for SQL_ALTER_DOMAIN
  SQL_AD_CONSTRAINT_NAME_DEFINITION = $00000001;
  SQL_AD_ADD_DOMAIN_CONSTRAINT = $00000002;
  SQL_AD_DROP_DOMAIN_CONSTRAINT = $00000004;
  SQL_AD_ADD_DOMAIN_DEFAULT = $00000008;
  SQL_AD_DROP_DOMAIN_DEFAULT = $00000010;
  SQL_AD_ADD_CONSTRAINT_INITIALLY_DEFERRED = $00000020;
  SQL_AD_ADD_CONSTRAINT_INITIALLY_IMMEDIATE = $00000040;
  SQL_AD_ADD_CONSTRAINT_DEFERRABLE = $00000080;
  SQL_AD_ADD_CONSTRAINT_NON_DEFERRABLE = $00000100;

  // SQL_CREATE_SCHEMA bitmasks
  SQL_CS_CREATE_SCHEMA = $00000001;
  SQL_CS_AUTHORIZATION = $00000002;
  SQL_CS_DEFAULT_CHARACTER_SET = $00000004;

  // SQL_CREATE_TRANSLATION bitmasks
  SQL_CTR_CREATE_TRANSLATION = $00000001;

  // SQL_CREATE_ASSERTION bitmasks
  SQL_CA_CREATE_ASSERTION = $00000001;
  SQL_CA_CONSTRAINT_INITIALLY_DEFERRED = $00000010;
  SQL_CA_CONSTRAINT_INITIALLY_IMMEDIATE = $00000020;
  SQL_CA_CONSTRAINT_DEFERRABLE = $00000040;
  SQL_CA_CONSTRAINT_NON_DEFERRABLE = $00000080;

  // SQL_CREATE_CHARACTER_SET bitmasks
  SQL_CCS_CREATE_CHARACTER_SET = $00000001;
  SQL_CCS_COLLATE_CLAUSE = $00000002;
  SQL_CCS_LIMITED_COLLATION = $00000004;

  // SQL_CREATE_COLLATION bitmasks
  SQL_CCOL_CREATE_COLLATION = $00000001;

  // SQL_CREATE_DOMAIN bitmasks
  SQL_CDO_CREATE_DOMAIN = $00000001;
  SQL_CDO_DEFAULT = $00000002;
  SQL_CDO_CONSTRAINT = $00000004;
  SQL_CDO_COLLATION = $00000008;
  SQL_CDO_CONSTRAINT_NAME_DEFINITION = $00000010;
  SQL_CDO_CONSTRAINT_INITIALLY_DEFERRED = $00000020;
  SQL_CDO_CONSTRAINT_INITIALLY_IMMEDIATE = $00000040;
  SQL_CDO_CONSTRAINT_DEFERRABLE = $00000080;
  SQL_CDO_CONSTRAINT_NON_DEFERRABLE = $00000100;

  // SQL_CREATE_TABLE bitmasks
  SQL_CT_CREATE_TABLE = $00000001;
  SQL_CT_COMMIT_PRESERVE = $00000002;
  SQL_CT_COMMIT_DELETE = $00000004;
  SQL_CT_GLOBAL_TEMPORARY = $00000008;
  SQL_CT_LOCAL_TEMPORARY = $00000010;
  SQL_CT_CONSTRAINT_INITIALLY_DEFERRED = $00000020;
  SQL_CT_CONSTRAINT_INITIALLY_IMMEDIATE = $00000040;
  SQL_CT_CONSTRAINT_DEFERRABLE = $00000080;
  SQL_CT_CONSTRAINT_NON_DEFERRABLE = $00000100;
  SQL_CT_COLUMN_CONSTRAINT = $00000200;
  SQL_CT_COLUMN_DEFAULT = $00000400;
  SQL_CT_COLUMN_COLLATION = $00000800;
  SQL_CT_TABLE_CONSTRAINT = $00001000;
  SQL_CT_CONSTRAINT_NAME_DEFINITION = $00002000;

  // SQL_DDL_INDEX bitmasks
  SQL_DI_CREATE_INDEX = $00000001;
  SQL_DI_DROP_INDEX = $00000002;

  // SQL_DROP_COLLATION bitmasks
  SQL_DC_DROP_COLLATION = $00000001;

  // SQL_DROP_DOMAIN bitmasks
  SQL_DD_DROP_DOMAIN = $00000001;
  SQL_DD_RESTRICT = $00000002;
  SQL_DD_CASCADE = $00000004;

  // SQL_DROP_SCHEMA bitmasks
  SQL_DS_DROP_SCHEMA = $00000001;
  SQL_DS_RESTRICT = $00000002;
  SQL_DS_CASCADE = $00000004;

  // SQL_DROP_CHARACTER_SET bitmasks
  SQL_DCS_DROP_CHARACTER_SET = $00000001;

  // SQL_DROP_ASSERTION bitmasks
  SQL_DA_DROP_ASSERTION = $00000001;

  // SQL_DROP_TABLE bitmasks
  SQL_DT_DROP_TABLE = $00000001;
  SQL_DT_RESTRICT = $00000002;
  SQL_DT_CASCADE = $00000004;

  // SQL_DROP_TRANSLATION bitmasks
  SQL_DTR_DROP_TRANSLATION = $00000001;

  // SQL_DROP_VIEW bitmasks
  SQL_DV_DROP_VIEW = $00000001;
  SQL_DV_RESTRICT = $00000002;
  SQL_DV_CASCADE = $00000004;

  // SQL_INSERT_STATEMENT bitmasks
  SQL_IS_INSERT_LITERALS = $00000001;
  SQL_IS_INSERT_SEARCHED = $00000002;
  SQL_IS_SELECT_INTO = $00000004;

  // SQL_ODBC_INTERFACE_CONFORMANCE values
  SQL_OIC_CORE = ULong(1);
  SQL_OIC_LEVEL1 = ULong(2);
  SQL_OIC_LEVEL2 = ULong(3);

  // SQL_SQL92_FOREIGN_KEY_DELETE_RULE bitmasks
  SQL_SFKD_CASCADE = $00000001;
  SQL_SFKD_NO_ACTION = $00000002;
  SQL_SFKD_SET_DEFAULT = $00000004;
  SQL_SFKD_SET_NULL = $00000008;

  // SQL_SQL92_FOREIGN_KEY_UPDATE_RULE bitmasks
  SQL_SFKU_CASCADE = $00000001;
  SQL_SFKU_NO_ACTION = $00000002;
  SQL_SFKU_SET_DEFAULT = $00000004;
  SQL_SFKU_SET_NULL = $00000008;

  // SQL_SQL92_GRANT bitmasks
  SQL_SG_USAGE_ON_DOMAIN = $00000001;
  SQL_SG_USAGE_ON_CHARACTER_SET = $00000002;
  SQL_SG_USAGE_ON_COLLATION = $00000004;
  SQL_SG_USAGE_ON_TRANSLATION = $00000008;
  SQL_SG_WITH_GRANT_OPTION = $00000010;
  SQL_SG_DELETE_TABLE = $00000020;
  SQL_SG_INSERT_TABLE = $00000040;
  SQL_SG_INSERT_COLUMN = $00000080;
  SQL_SG_REFERENCES_TABLE = $00000100;
  SQL_SG_REFERENCES_COLUMN = $00000200;
  SQL_SG_SELECT_TABLE = $00000400;
  SQL_SG_UPDATE_TABLE = $00000800;
  SQL_SG_UPDATE_COLUMN = $00001000;

  // SQL_SQL92_PREDICATES bitmasks
  SQL_SP_EXISTS = $00000001;
  SQL_SP_ISNOTNULL = $00000002;
  SQL_SP_ISNULL = $00000004;
  SQL_SP_MATCH_FULL = $00000008;
  SQL_SP_MATCH_PARTIAL = $00000010;
  SQL_SP_MATCH_UNIQUE_FULL = $00000020;
  SQL_SP_MATCH_UNIQUE_PARTIAL = $00000040;
  SQL_SP_OVERLAPS = $00000080;
  SQL_SP_UNIQUE = $00000100;
  SQL_SP_LIKE = $00000200;
  SQL_SP_IN = $00000400;
  SQL_SP_BETWEEN = $00000800;
  SQL_SP_COMPARISON = $00001000;
  SQL_SP_QUANTIFIED_COMPARISON = $00002000;

  // SQL_SQL92_RELATIONAL_JOIN_OPERATORS bitmasks
  SQL_SRJO_CORRESPONDING_CLAUSE = $00000001;
  SQL_SRJO_CROSS_JOIN = $00000002;
  SQL_SRJO_EXCEPT_JOIN = $00000004;
  SQL_SRJO_FULL_OUTER_JOIN = $00000008;
  SQL_SRJO_INNER_JOIN = $00000010;
  SQL_SRJO_INTERSECT_JOIN = $00000020;
  SQL_SRJO_LEFT_OUTER_JOIN = $00000040;
  SQL_SRJO_NATURAL_JOIN = $00000080;
  SQL_SRJO_RIGHT_OUTER_JOIN = $00000100;
  SQL_SRJO_UNION_JOIN = $00000200;

  // SQL_SQL92_REVOKE bitmasks
  SQL_SR_USAGE_ON_DOMAIN = $00000001;
  SQL_SR_USAGE_ON_CHARACTER_SET = $00000002;
  SQL_SR_USAGE_ON_COLLATION = $00000004;
  SQL_SR_USAGE_ON_TRANSLATION = $00000008;
  SQL_SR_GRANT_OPTION_FOR = $00000010;
  SQL_SR_CASCADE = $00000020;
  SQL_SR_RESTRICT = $00000040;
  SQL_SR_DELETE_TABLE = $00000080;
  SQL_SR_INSERT_TABLE = $00000100;
  SQL_SR_INSERT_COLUMN = $00000200;
  SQL_SR_REFERENCES_TABLE = $00000400;
  SQL_SR_REFERENCES_COLUMN = $00000800;
  SQL_SR_SELECT_TABLE = $00001000;
  SQL_SR_UPDATE_TABLE = $00002000;
  SQL_SR_UPDATE_COLUMN = $00004000;

  // SQL_SQL92_ROW_VALUE_CONSTRUCTOR bitmasks
  SQL_SRVC_VALUE_EXPRESSION = $00000001;
  SQL_SRVC_NULL = $00000002;
  SQL_SRVC_DEFAULT = $00000004;
  SQL_SRVC_ROW_SUBQUERY = $00000008;

  // SQL_SQL92_VALUE_EXPRESSIONS bitmasks
  SQL_SVE_CASE = $00000001;
  SQL_SVE_CAST = $00000002;
  SQL_SVE_COALESCE = $00000004;
  SQL_SVE_NULLIF = $00000008;

  // SQL_STANDARD_CLI_CONFORMANCE bitmasks
  SQL_SCC_XOPEN_CLI_VERSION1 = $00000001;
  SQL_SCC_ISO92_CLI = $00000002;

  // SQL_UNION_STATEMENT bitmasks
  SQL_US_UNION = SQL_U_UNION;
  SQL_US_UNION_ALL = SQL_U_UNION_ALL;

  // SQL_DTC_TRANSITION_COST bitmasks
  SQL_DTC_ENLIST_EXPENSIVE = $00000001;
  SQL_DTC_UNENLIST_EXPENSIVE = $00000002;

  // additional SQLDataSources fetch directions
  SQL_FETCH_FIRST_USER = 31;
  SQL_FETCH_FIRST_SYSTEM = 32;

  // Defines for SQLSetPos
  SQL_ENTIRE_ROWSET = 0;

  // Operations in SQLSetPos
  SQL_POSITION = 0; // 1.0 FALSE
  SQL_REFRESH = 1; // 1.0 TRUE
  SQL_UPDATE = 2;
  SQL_DELETE = 3;

  // Operations in SQLBulkOperations
  SQL_ADD = 4;
  SQL_SETPOS_MAX_OPTION_VALUE = SQL_ADD;
  SQL_UPDATE_BY_BOOKMARK = 5;
  SQL_DELETE_BY_BOOKMARK = 6;
  SQL_FETCH_BY_BOOKMARK = 7;

  // Lock options in SQLSetPos
  SQL_LOCK_NO_CHANGE = 0; // 1.0 FALSE
  SQL_LOCK_EXCLUSIVE = 1; // 1.0 TRUE
  SQL_LOCK_UNLOCK = 2;

  SQL_SETPOS_MAX_LOCK_VALUE = SQL_LOCK_UNLOCK;

  // Macros for SQLSetPos
{$IFNDEF DynamicOdbcImport}
function SQL_POSITION_TO(HStmt: SqlHStmt; irow: SqlUSmallint): SqlReturn;
function SQL_LOCK_RECORD(HStmt: SqlHStmt; irow, fLock: SqlUSmallint): SqlReturn;
function SQL_REFRESH_RECORD(HStmt: SqlHStmt; irow, fLock: SqlUSmallint): SqlReturn;
function SQL_UPDATE_RECORD(HStmt: SqlHStmt; irow: SqlUSmallint): SqlReturn;
function SQL_DELETE_RECORD(HStmt: SqlHStmt; irow: SqlUSmallint): SqlReturn;
function SQL_ADD_RECORD(HStmt: SqlHStmt; irow: SqlUSmallint): SqlReturn;
{$ENDIF}

const

  // Column types and scopes in SQLSpecialColumns.
  SQL_BEST_ROWID = 1;
  SQL_ROWVER = 2;

  // Defines for SQLSpecialColumns (returned in the result set
  //= SQL_PC_UNKNOWN and SQL_PC_PSEUDO are defined in sql.h
  SQL_PC_NOT_PSEUDO = 1;

  // Defines for SQLStatistics
  SQL_QUICK = 0;
  SQL_ENSURE = 1;

  // Defines for SQLStatistics (returned in the result set)
  //-SQL_INDEX_CLUSTERED, SQL_INDEX_HASHED, and SQL_INDEX_OTHER are
  //=defined in sql.h
  SQL_TABLE_STAT = 0;

  // Defines for SQLTables
  SQL_ALL_CATALOGS = '%';
  SQL_ALL_SCHEMAS = '%';
  SQL_ALL_TABLE_TYPES = '%';

  // Options for SQLDriverConnect
  SQL_DRIVER_NOPROMPT = 0;
  SQL_DRIVER_COMPLETE = 1;
  SQL_DRIVER_PROMPT = 2;
  SQL_DRIVER_COMPLETE_REQUIRED = 3;

{$IFDEF DynamicOdbcImport}
type
  TSQLDriverConnect = function(
{$ELSE}
function SQLDriverConnect(
{$ENDIF}
  HDbc: SqlHDbc;
  hwnd: SqlHWnd;
  szConnStrIn: PAnsiChar;
  cbConnStrIn: SqlSmallint;
  szConnStrOut: PAnsiChar;
  cbConnStrOutMax: SqlSmallint;
  var pcbConnStrOut: SqlSmallint;
  fDriverCompletion: SqlUSmallint
  ): SqlReturn{$IFDEF MSWINDOWS} stdcall{$ELSE} cdecl{$ENDIF};

// Level 2 Functions

// SQLExtendedFetch "fFetchType" values
const
  SQL_FETCH_BOOKMARK = 8;

  // SQLExtendedFetch "rgfRowStatus" element values
  SQL_ROW_SUCCESS = 0;
  SQL_ROW_DELETED = 1;
  SQL_ROW_UPDATED = 2;
  SQL_ROW_NOROW = 3;
  SQL_ROW_ADDED = 4;
  SQL_ROW_ERROR = 5;
  SQL_ROW_SUCCESS_WITH_INFO = 6;
  SQL_ROW_PROCEED = 0;
  SQL_ROW_IGNORE = 1;

  // value for SQL_DESC_ARRAY_STATUS_PTR
  SQL_PARAM_SUCCESS = 0;
  SQL_PARAM_SUCCESS_WITH_INFO = 6;
  SQL_PARAM_ERROR = 5;
  SQL_PARAM_UNUSED = 7;
  SQL_PARAM_DIAG_UNAVAILABLE = 1;
  SQL_PARAM_PROCEED = 0;
  SQL_PARAM_IGNORE = 1;

  // Defines for SQLForeignKeys (UPDATE_RULE and DELETE_RULE)
  SQL_CASCADE = 0;
  SQL_RESTRICT = 1;
  SQL_SET_NULL = 2;
  SQL_NO_ACTION = 3;
  SQL_SET_DEFAULT = 4;

  // Note that the following are in a different column of SQLForeignKeys than
  // the previous #defines.   These are for DEFERRABILITY.
  SQL_INITIALLY_DEFERRED = 5;
  SQL_INITIALLY_IMMEDIATE = 6;
  SQL_NOT_DEFERRABLE = 7;

  // SQLBindParameter block
  // WAS ORIGINALLY HERE
  // Moved above because of dependent declarations

  // Defines for SQLProcedures (returned in the result set)
  SQL_PT_UNKNOWN = 0;
  SQL_PT_PROCEDURE = 1;
  SQL_PT_FUNCTION = 2;

  // This define is too large for RC
  SQL_ODBC_KEYWORDS =
    'ABSOLUTE,ACTION,ADA,ADD,ALL,ALLOCATE,ALTER,AND,ANY,ARE,AS,' +
    'ASC,ASSERTION,AT,AUTHORIZATION,AVG,' +
    'BEGIN,BETWEEN,BIT,BIT_LENGTH,BOTH,BY,CASCADE,CASCADED,CASE,CAST,CATALOG,' +
    'CHAR,CHAR_LENGTH,CHARACTER,CHARACTER_LENGTH,CHECK,CLOSE,COALESCE,' +
    'COLLATE,COLLATION,COLUMN,COMMIT,CONNECT,CONNECTION,CONSTRAINT,' +
    'CONSTRAINTS,CONTINUE,CONVERT,CORRESPONDING,COUNT,CREATE,CROSS,CURRENT,' +
    'CURRENT_DATE,CURRENT_TIME,CURRENT_TIMESTAMP,CURRENT_USER,CURSOR,' +
    'DATE,DAY,DEALLOCATE,DEC,DECIMAL,DECLARE,DEFAULT,DEFERRABLE,' +
    'DEFERRED,DELETE,DESC,DESCRIBE,DESCRIPTOR,DIAGNOSTICS,DISCONNECT,' +
    'DISTINCT,DOMAIN,DOUBLE,DROP,' +
    'ELSE,END,END-EXEC,ESCAPE,EXCEPT,EXCEPTION,EXEC,EXECUTE,' +
    'EXISTS,EXTERNAL,EXTRACT,' +
    'FALSE,FETCH,FIRST,FLOAT,FOR,FOREIGN,FORTRAN,FOUND,FROM,FULL,' +
    'GET,GLOBAL,GO,GOTO,GRANT,GROUP,HAVING,HOUR,' +
    'IDENTITY,IMMEDIATE,IN,INCLUDE,INDEX,INDICATOR,INITIALLY,INNER,' +
    'INPUT,INSENSITIVE,INSERT,INT,INTEGER,INTERSECT,INTERVAL,INTO,IS,ISOLATION,' +
    'JOIN,KEY,LANGUAGE,LAST,LEADING,LEFT,LEVEL,LIKE,LOCAL,LOWER,' +
    'MATCH,MAX,MIN,MINUTE,MODULE,MONTH,' +
    'NAMES,NATIONAL,NATURAL,NCHAR,NEXT,NO,NONE,NOT,NULL,NULLIF,NUMERIC,' +
    'OCTET_LENGTH,OF,ON,ONLY,OPEN,OPTION,OR,ORDER,OUTER,OUTPUT,OVERLAPS,' +
    'PAD,PARTIAL,PASCAL,PLI,POSITION,PRECISION,PREPARE,PRESERVE,' +
    'PRIMARY,PRIOR,PRIVILEGES,PROCEDURE,PUBLIC,' +
    'READ,REAL,REFERENCES,RELATIVE,RESTRICT,REVOKE,RIGHT,ROLLBACK,ROWS' +
    'SCHEMA,SCROLL,SECOND,SECTION,SELECT,SESSION,SESSION_USER,SET,SIZE,' +
    'SMALLINT,SOME,SPACE,SQL,SQLCA,SQLCODE,SQLERROR,SQLSTATE,SQLWARNING,' +
    'SUBSTRING,SUM,SYSTEM_USER,' +
    'TABLE,TEMPORARY,THEN,TIME,TIMESTAMP,TIMEZONE_HOUR,TIMEZONE_MINUTE,' +
    'TO,TRAILING,TRANSACTION,TRANSLATE,TRANSLATION,TRIM,TRUE,' +
    'UNION,UNIQUE,UNKNOWN,UPDATE,UPPER,USAGE,USER,USING,' +
    'VALUE,VALUES,VARCHAR,VARYING,VIEW,WHEN,WHENEVER,WHERE,WITH,WORK,WRITE,' +
    'YEAR,ZONE';

{$IFDEF DynamicOdbcImport}
type
  TSQLBrowseConnect = function(
{$ELSE}
function SQLBrowseConnect(
{$ENDIF}
  HDbc: SqlHDbc;
  var szConnStrIn: SqlChar;
  cbConnStrIn: SqlSmallint;
  var szConnStrOut: SqlChar;
  cbConnStrOutMax: SqlSmallint;
  var pcbConnStrOut: SqlSmallint
  ): SqlReturn{$IFDEF MSWINDOWS} stdcall{$ELSE} cdecl{$ENDIF};

{$IFDEF DynamicOdbcImport}
TSQLBulkOperations = function(
{$ELSE}
function SQLBulkOperations(
{$ENDIF}
  StatementHandle: SqlHStmt;
  Operation: SqlSmallint
  ): SqlReturn{$IFDEF MSWINDOWS} stdcall{$ELSE} cdecl{$ENDIF};

{$IFDEF DynamicOdbcImport}
TSQLColAttributes = function(
{$ELSE}
function SQLColAttributes(
{$ENDIF}
  HStmt: SqlHStmt;
  icol: SqlUSmallint;
  fDescType: SqlUSmallint;
  rgbDesc: SqlPointer;
  cbDescMax: SqlSmallint;
  var pcbDesc: SqlSmallint;
  var pfDesc: SqlInteger
  ): SqlReturn{$IFDEF MSWINDOWS} stdcall{$ELSE} cdecl{$ENDIF};

{$IFDEF DynamicOdbcImport}
TSQLColumnPrivileges = function(
{$ELSE}
function SQLColumnPrivileges(
{$ENDIF}
  HStmt: SqlHStmt;
  var szCatalogName: SqlChar;
  cbCatalogName: SqlSmallint;
  var szSchemaName: SqlChar;
  cbSchemaName: SqlSmallint;
  var szTableName: SqlChar;
  cbTableName: SqlSmallint;
  var szColumnName: SqlChar;
  cbColumnName: SqlSmallint
  ): SqlReturn{$IFDEF MSWINDOWS} stdcall{$ELSE} cdecl{$ENDIF};

{$IFDEF DynamicOdbcImport}
TSQLDescribeParam = function(
{$ELSE}
function SQLDescribeParam(
{$ENDIF}
  HStmt: SqlHStmt;
  ipar: SqlUSmallint;
  var pfSqlType: SqlSmallint;
  var pcbParamDef: SqlUInteger;
  var pibScale: SqlSmallint;
  var pfNullable: SqlSmallint
  ): SqlReturn{$IFDEF MSWINDOWS} stdcall{$ELSE} cdecl{$ENDIF};

{$IFDEF DynamicOdbcImport}
TSQLExtendedFetch = function(
{$ELSE}
function SQLExtendedFetch(
{$ENDIF}
  HStmt: SqlHStmt;
  fFetchType: SqlUSmallint;
  irow: SqlInteger;
  var pcrow: SqlUInteger;
  var rgfRowStatus: SqlUSmallint
  ): SqlReturn{$IFDEF MSWINDOWS} stdcall{$ELSE} cdecl{$ENDIF};

{$IFDEF DynamicOdbcImport}
TSQLForeignKeys = function(
{$ELSE}
function SQLForeignKeys(
{$ENDIF}
  HStmt: SqlHStmt;
  var szPkCatalogName: SqlChar;
  cbPkCatalogName: SqlSmallint;
  var szPkSchemaName: SqlChar;
  cbPkSchemaName: SqlSmallint;
  var szPkTableName: SqlChar;
  cbPkTableName: SqlSmallint;
  var szFkCatalogName: SqlChar;
  cbFkCatalogName: SqlSmallint;
  var szFkSchemaName: SqlChar;
  cbFkSchemaName: SqlSmallint;
  var szFkTableName: SqlChar;
  cbFkTableName: SqlSmallint
  ): SqlReturn{$IFDEF MSWINDOWS} stdcall{$ELSE} cdecl{$ENDIF};

{$IFDEF DynamicOdbcImport}
TSQLMoreResults = function(
{$ELSE}
function SQLMoreResults(
{$ENDIF}
  HStmt: SqlHStmt
  ): SqlReturn{$IFDEF MSWINDOWS} stdcall{$ELSE} cdecl{$ENDIF};

{$IFDEF DynamicOdbcImport}
TSQLNativeSql = function(
{$ELSE}
function SQLNativeSql(
{$ENDIF}
  HDbc: SqlHDbc;
  var szSqlStrIn: SqlChar;
  cbSqlStrIn: SqlInteger;
  var szSqlStr: SqlChar;
  cbSqlStrMax: SqlInteger;
  var pcbSqlStr: SqlInteger
  ): SqlReturn{$IFDEF MSWINDOWS} stdcall{$ELSE} cdecl{$ENDIF};

{$IFDEF DynamicOdbcImport}
TSQLNumParams = function(
{$ELSE}
function SQLNumParams(
{$ENDIF}
  HStmt: SqlHStmt;
  var pcpar: SqlSmallint
  ): SqlReturn{$IFDEF MSWINDOWS} stdcall{$ELSE} cdecl{$ENDIF};

{$IFDEF DynamicOdbcImport}
TSQLParamOptions = function(
{$ELSE}
function SQLParamOptions(
{$ENDIF}
  HStmt: SqlHStmt;
  crow: SqlUInteger;
  var pirow: SqlUInteger
  ): SqlReturn{$IFDEF MSWINDOWS} stdcall{$ELSE} cdecl{$ENDIF};

{$IFDEF DynamicOdbcImport}
TSQLPrimaryKeys = function(
{$ELSE}
function SQLPrimaryKeys(
{$ENDIF}
  HStmt: SqlHStmt;
  szCatalogName: PAnsiChar;
  cbCatalogName: SqlSmallint;
  szSchemaName: PAnsiChar;
  cbSchemaName: SqlSmallint;
  szTableName: PAnsiChar;
  cbTableName: SqlSmallint
  ): SqlReturn{$IFDEF MSWINDOWS} stdcall{$ELSE} cdecl{$ENDIF};

{$IFDEF DynamicOdbcImport}
TSQLProcedureColumns = function(
{$ELSE}
function SQLProcedureColumns(
{$ENDIF}
  HStmt: SqlHStmt;
  szCatalogName: PAnsiChar;
  cbCatalogName: SqlSmallint;
  szSchemaName: PAnsiChar;
  cbSchemaName: SqlSmallint;
  szProcName: PAnsiChar;
  cbProcName: SqlSmallint;
  szColumnName: PAnsiChar;
  cbColumnName: SqlSmallint
  ): SqlReturn{$IFDEF MSWINDOWS} stdcall{$ELSE} cdecl{$ENDIF};

{$IFDEF DynamicOdbcImport}
TSQLProcedures = function(
{$ELSE}
function SQLProcedures(
{$ENDIF}
  HStmt: SqlHStmt;
  szCatalogName: PAnsiChar;
  cbCatalogName: SqlSmallint;
  szSchemaName: PAnsiChar;
  cbSchemaName: SqlSmallint;
  szProcName: PAnsiChar;
  cbProcName: SqlSmallint
  ): SqlReturn{$IFDEF MSWINDOWS} stdcall{$ELSE} cdecl{$ENDIF};

{$IFDEF DynamicOdbcImport}
TSQLSetPos = function(
{$ELSE}
function SQLSetPos(
{$ENDIF}
  HStmt: SqlHStmt;
  irow: SqlUSmallint;
  fOption: SqlUSmallint;
  fLock: SqlUSmallint
  ): SqlReturn{$IFDEF MSWINDOWS} stdcall{$ELSE} cdecl{$ENDIF};

{$IFDEF DynamicOdbcImport}
TSQLTablePrivileges = function(
{$ELSE}
function SQLTablePrivileges(
{$ENDIF}
  HStmt: SqlHStmt;
  var szCatalogName: SqlChar;
  cbCatalogName: SqlSmallint;
  var szSchemaName: SqlChar;
  cbSchemaName: SqlSmallint;
  var szTableName: SqlChar;
  cbTableName: SqlSmallint
  ): SqlReturn{$IFDEF MSWINDOWS} stdcall{$ELSE} cdecl{$ENDIF};

{$IFDEF DynamicOdbcImport}
TSQLDrivers = function(
{$ELSE}
function SQLDrivers(
{$ENDIF}
  HEnv: SqlHEnv;
  fDirection: SqlUSmallint;
  szDriverDesc: PAnsiChar;
  cbDriverDescMax: SqlSmallint;
  var pcbDriverDesc: SqlSmallint;
  szDriverAttributes: PAnsiChar;
  cbDrvrAttrMax: SqlSmallint;
  var pcbDrvrAttr: SqlSmallint
  ): SqlReturn{$IFDEF MSWINDOWS} stdcall{$ELSE} cdecl{$ENDIF};

{$IFDEF DynamicOdbcImport}
TSQLBindParameter = function(
{$ELSE}
function SQLBindParameter(
{$ENDIF}
  HStmt: SqlHStmt;
  ipar: SqlUSmallint;
  fParamType: SqlSmallint;
  fCType: SqlSmallint;
  fSqlType: SqlSmallint;
  cbColDef: SqlUInteger;
  ibScale: SqlSmallint;
  rgbValue: SqlPointer;
  cbValueMax: SqlInteger;
  pcbValue: PSqlInteger
  ): SqlReturn{$IFDEF MSWINDOWS} stdcall{$ELSE} cdecl{$ENDIF};

//---------------------------------------------------------
// SQLAllocHandleStd is implemented to make SQLAllocHandle
// compatible with X/Open standard. an application should
// not call SQLAllocHandleStd directly
//---------------------------------------------------------

// Internal type subcodes (ODBC_STD, ie X/OPEN)
const
  SQL_YEAR = SQL_CODE_YEAR;
  SQL_MONTH = SQL_CODE_MONTH;
  SQL_DAY = SQL_CODE_DAY;
  SQL_HOUR = SQL_CODE_HOUR;
  SQL_MINUTE = SQL_CODE_MINUTE;
  SQL_SECOND = SQL_CODE_SECOND;
  SQL_YEAR_TO_MONTH = SQL_CODE_YEAR_TO_MONTH;
  SQL_DAY_TO_HOUR = SQL_CODE_DAY_TO_HOUR;
  SQL_DAY_TO_MINUTE = SQL_CODE_DAY_TO_MINUTE;
  SQL_DAY_TO_SECOND = SQL_CODE_DAY_TO_SECOND;
  SQL_HOUR_TO_MINUTE = SQL_CODE_HOUR_TO_MINUTE;
  SQL_HOUR_TO_SECOND = SQL_CODE_HOUR_TO_SECOND;
  SQL_MINUTE_TO_SECOND = SQL_CODE_MINUTE_TO_SECOND;

{$IFDEF DynamicOdbcImport}
type
  TSQLAllocHandleStd = function(
{$ELSE}
function SQLAllocHandleStd(
{$ENDIF}
  fHandleType: SqlSmallint;
  hInput: SqlHandle;
  var phOutput: SqlHandle
  ): SqlReturn{$IFDEF MSWINDOWS} stdcall{$ELSE} cdecl{$ENDIF};

// Deprecated defines from prior versions of ODBC
const
  SQL_DATABASE_NAME = 16; // Use SQLGetConnectOption/SQL_CURRENT_QUALIFIER
  SQL_FD_FETCH_PREV = SQL_FD_FETCH_PRIOR;
  SQL_FETCH_PREV = SQL_FETCH_PRIOR;
  SQL_CONCUR_TIMESTAMP = SQL_CONCUR_ROWVER;
  SQL_SCCO_OPT_TIMESTAMP = SQL_SCCO_OPT_ROWVER;
  SQL_CC_DELETE = SQL_CB_DELETE;
  SQL_CR_DELETE = SQL_CB_DELETE;
  SQL_CC_CLOSE = SQL_CB_CLOSE;
  SQL_CR_CLOSE = SQL_CB_CLOSE;
  SQL_CC_PRESERVE = SQL_CB_PRESERVE;
  SQL_CR_PRESERVE = SQL_CB_PRESERVE;
  // SQL_FETCH_RESUME is not supported by 2.0+ drivers
  SQL_FETCH_RESUME = 7;
  SQL_SCROLL_FORWARD_ONLY = 0; //-SQL_CURSOR_FORWARD_ONLY
  SQL_SCROLL_KEYSET_DRIVEN = (-1); //-SQL_CURSOR_KEYSET_DRIVEN
  SQL_SCROLL_DYNAMIC = (-2); //-SQL_CURSOR_DYNAMIC
  SQL_SCROLL_STATIC = (-3); //*-SQL_CURSOR_STATIC

  // Deprecated functions from prior versions of ODBC
{$IFDEF DynamicOdbcImport}
type
  TSQLSetScrollOptions = function(
{$ELSE}
function SQLSetScrollOptions(
{$ENDIF}
  // Use SQLSetStmtOptions
  HStmt: SqlHStmt;
  fConcurrency: SqlUSmallint;
  crowKeyset: SqlInteger;
  crowRowset: SqlUSmallint
  ): SqlReturn{$IFDEF MSWINDOWS} stdcall{$ELSE} cdecl{$ENDIF};

// Tracing section

const
  TRACE_VERSION = 1000; // Version of trace API

{$IFDEF DynamicOdbcImport}
type
  TTraceOpenLogFile = function(
{$ELSE}
function TraceOpenLogFile(
{$ENDIF}
  var _1: WideChar;
  var _2: WideChar;
  _3: Longint
  ): Retcode{$IFDEF MSWINDOWS} stdcall{$ELSE} cdecl{$ENDIF};

{$IFDEF DynamicOdbcImport}
type
  TTraceCloseLogFile = function:
{$ELSE}
function TraceCloseLogFile:
{$ENDIF}
  Retcode{$IFDEF MSWINDOWS} stdcall{$ELSE} cdecl{$ENDIF};

{$IFDEF DynamicOdbcImport}
type
  TTraceReturn = procedure(
{$ELSE}
procedure TraceReturn(
{$ENDIF}
  _1: Retcode;
  _2: Retcode){$IFDEF MSWINDOWS} stdcall{$ELSE} cdecl{$ENDIF};

{$IFDEF DynamicOdbcImport}
type
  TTraceVersion = function:
{$ELSE}
function TraceVersion:
{$ENDIF}
  Longint{$IFDEF MSWINDOWS} stdcall{$ELSE} cdecl{$ENDIF};

// Functions for Visual Studio Analyzer
// to turn on/off tracing or VS events,
// call TraceVSControl by setting or clearing the following bits
const
  TRACE_ON = $00000001;
  TRACE_VS_EVENT_ON = $00000002;

{$IFDEF DynamicOdbcImport}
type
  TTraceVSControl = function(
{$ELSE}
function TraceVSControl(
{$ENDIF}
  _1: Longint): Retcode{$IFDEF MSWINDOWS} stdcall{$ELSE} cdecl{$ENDIF};

// Functions for setting the connection pooling failure detection code
// The "TryWait" value is the time (in seconds) that the DM will wait
// between detecting that a connection is dead (using
// SQL_ATTR_CONNECTION_DEAD) and retrying the connection. During that
// interval, connection requests will get "The server appears to be
// dead" error returns.

{$IFDEF DynamicOdbcImport}
type
  TODBCSetTryWaitValue = function(
{$ELSE}
function ODBCSetTryWaitValue(
{$ENDIF}
  dwValue: Longint): LongBool{$IFDEF MSWINDOWS} stdcall{$ELSE}cdecl{$ENDIF};//= In seconds

{$IFDEF DynamicOdbcImport}
type
  TODBCGetTryWaitValue = function:
{$ELSE}
function ODBCGetTryWaitValue:
{$ENDIF}
  Longint{$IFDEF MSWINDOWS} stdcall{$ELSE} cdecl{$ENDIF};//= In Milliseconds(!)

// the flags in ODBC_VS_ARGS
const
  ODBC_VS_FLAG_UNICODE_ARG = $00000001; // the argument is unicode
  ODBC_VS_FLAG_UNICODE_COR = $00000002; // the correlation is unicode
  ODBC_VS_FLAG_RETCODE = $00000004; // RetCode field is set
  ODBC_VS_FLAG_STOP = $00000008; // Stop firing visual studio analyzer events

type
  tagODBC_VS_ARGS = packed record
    PGuidEvent: PGUID; // the GUID for event
    dwFlags: Longword; // flags for the call
    case Integer of
      0: (wszArg: PWideChar;
        szArg: PChar;
        Retcode: Retcode);
      1: (wszCorrelation: PWideChar;
        szCorrelation: PChar;
        RetCode2: Retcode);
  end;

  ODBC_VS_ARGS = tagODBC_VS_ARGS;
  PODBC_VS_ARGS = ^ODBC_VS_ARGS;

{$IFDEF DynamicOdbcImport}
type
  TFireVSDebugEvent = procedure(
{$ELSE}
procedure FireVSDebugEvent(
{$ENDIF}
  var Args: ODBC_VS_ARGS);{$IFDEF MSWINDOWS}stdcall{$ELSE}cdecl{$ENDIF};


//##########################################################################
// sqlext.h interface part ends here
//##########################################################################

{$IFDEF DynamicOdbcImport}
const
  OdbcApi_NotImplemented_OdbcName = 0;
  OdbcApi_NotImplemented_OdbcTrac = 1;
  OdbcApi_NotImplemented_OdbcInst = 2;
{$ENDIF}

type

{$IFDEF _iOdbcApi_}
  // forward declarations:
  IOdbcApi = interface;
  TOdbcApiIntfImpl = class;
{$ENDIF IFDEF _iOdbcApi_}

{$IFDEF DynamicOdbcImport}

  EOdbcApi = class(Exception);
  EOdbcApiNotImplemented = class(EOdbcApi);

  {$hints off}
  TOdbcApiProxy = class
  private
    fModuleName: string;
    fApiRefCount: Integer;
    fLockLib: Boolean;
    fSystemODBCManager: Boolean;
    hModuleApi: HMODULE;
    fModuleNameTrac: string;
    hModuleApiTrac: HMODULE;
    fModuleNameInst: string;
    hModuleApiInst: HMODULE;
    fOdbcDriverLevel: Integer;
    {$IFDEF _iOdbcApi_}
    fOdbcApiImpl: TOdbcApiIntfImpl;
    fOdbcApiIntf: IOdbcApi;
    {$ENDIF}
    procedure NotImplemented(const sFuncName: string;
      iLevel: Integer = OdbcApi_NotImplemented_OdbcName);
    procedure SetOdbcDriverLevel(aOdbcDriverLevel: Integer);
    procedure BeginLock;
    procedure EndLock;
  public
    destructor Destroy; override;
    function GetOdbcApiIntf: IUnknown;
    property SystemODBCManager: Boolean read fSystemODBCManager default False;
    property OdbcDriverLevel: Integer read fOdbcDriverLevel write SetOdbcDriverLevel;
  public
  // ODBC32DLL
    // sql.h
    SQLAllocConnectA: TSQLAllocConnect;
    SQLAllocEnvA: TSQLAllocEnv;
    SQLAllocHandleA: TSQLAllocHandle;
    SQLAllocStmtA: TSQLAllocStmt;
    SQLBindColA: TSQLBindCol;
    SQLBindParamA: TSQLBindParam;
    SQLCancelA: TSQLCancel;
    SQLCloseCursorA: TSQLCloseCursor;
    SQLColAttributeA: TSQLColAttribute;
    SQLColumnsA: TSQLColumns;
    SQLConnectA: TSQLConnect;
    SQLCopyDescA: TSQLCopyDesc;
    SQLDataSourcesA: TSQLDataSources;
    SQLDescribeColA: TSQLDescribeCol;
    SQLDisconnectA: TSQLDisconnect;
    SQLEndTranA: TSQLEndTran;
    SQLErrorA: TSQLError;
    SQLExecDirectA: TSQLExecDirect;
    SQLExecuteA: TSQLExecute;
    SQLFetchA: TSQLFetch;
    SQLFetchScrollA: TSQLFetchScroll;
    SQLFreeConnectA: TSQLFreeConnect;
    SQLFreeEnvA: TSQLFreeEnv;
    SQLFreeHandleA: TSQLFreeHandle;
    SQLFreeStmtA: TSQLFreeStmt;
    SQLGetConnectAttrA: TSQLGetConnectAttr;
    SQLGetConnectOptionA: TSQLGetConnectOption;
    SQLGetCursorNameA: TSQLGetCursorName;
    SQLGetDataA: TSQLGetData;
    SQLGetDescFieldA: TSQLGetDescField;
    SQLGetDescRecA: TSQLGetDescRec;
    SQLGetDiagFieldA: TSQLGetDiagField;
    SQLGetDiagRecA: TSQLGetDiagRec;
    SQLGetEnvAttrA: TSQLGetEnvAttr;
    SQLGetFunctionsA: TSQLGetFunctions;
    SQLGetInfoA: TSQLGetInfo;
    SQLGetStmtAttrA: TSQLGetStmtAttr;
    SQLGetStmtOptionA: TSQLGetStmtOption;
    SQLGetTypeInfoA: TSQLGetTypeInfo;
    SQLNumResultColsA: TSQLNumResultCols;
    SQLParamDataA: TSQLParamData;
    SQLPrepareA: TSQLPrepare;
    SQLPutDataA: TSQLPutData;
    SQLRowCountA: TSQLRowCount;
    SQLSetConnectAttrA: TSQLSetConnectAttr;
    SQLSetConnectOptionA: TSQLSetConnectOption;
    SQLSetCursorNameA: TSQLSetCursorName;
    SQLSetDescFieldA: TSQLSetDescField;
    SQLSetDescRecA: TSQLSetDescRec;
    SQLSetEnvAttrA: TSQLSetEnvAttr;
    SQLSetParamA: TSQLSetParam;
    SQLSetStmtAttrA: TSQLSetStmtAttr;
    SQLSetStmtOptionA: TSQLSetStmtOption;
    SQLSpecialColumnsA: TSQLSpecialColumns;
    SQLStatisticsA: TSQLStatistics;
    SQLTablesA: TSQLTables;
    SQLTransactA: TSQLTransact;
    // sqlext.h
    SQLDriverConnectA: TSQLDriverConnect;
    SQLBrowseConnectA: TSQLBrowseConnect;
    SQLBulkOperationsA: TSQLBulkOperations;
    SQLColAttributesA: TSQLColAttributes;
    SQLColumnPrivilegesA: TSQLColumnPrivileges;
    SQLDescribeParamA: TSQLDescribeParam;
    SQLExtendedFetchA: TSQLExtendedFetch;
    SQLForeignKeysA: TSQLForeignKeys;
    SQLMoreResultsA: TSQLMoreResults;
    SQLNativeSqlA: TSQLNativeSql;
    SQLNumParamsA: TSQLNumParams;
    SQLParamOptionsA: TSQLParamOptions;
    SQLPrimaryKeysA: TSQLPrimaryKeys;
    SQLProcedureColumnsA: TSQLProcedureColumns;
    SQLProceduresA: TSQLProcedures;
    SQLSetPosA: TSQLSetPos;
    SQLTablePrivilegesA: TSQLTablePrivileges;
    SQLDriversA: TSQLDrivers;
    SQLBindParameterA: TSQLBindParameter;
    SQLAllocHandleStdA: TSQLAllocHandleStd;
    SQLSetScrollOptionsA: TSQLSetScrollOptions;
  //ODBCTRAC
    TraceOpenLogFileA: TTraceOpenLogFile;
    TraceCloseLogFileA: TTraceCloseLogFile;
    TraceReturnA: TTraceReturn;
    TraceVersionA: TTraceVersion;
    TraceVSControlA: TTraceVSControl;
    FireVSDebugEventA: TFireVSDebugEvent;
  //ODBCINST
    ODBCSetTryWaitValueA: TODBCSetTryWaitValue;
    ODBCGetTryWaitValueA: TODBCGetTryWaitValue;
  // ODBC32DLL
    // sql.h
    SQLColAttributeW: TSQLColAttribute;
    SQLColumnsW: TSQLColumns;
    SQLConnectW: TSQLConnect;
    SQLDataSourcesW: TSQLDataSources;
    SQLDescribeColW: TSQLDescribeCol;
    SQLErrorW: TSQLError;
    SQLExecDirectW: TSQLExecDirect;
    SQLGetConnectAttrW: TSQLGetConnectAttr;
    SQLGetConnectOptionW: TSQLGetConnectOption;
    SQLGetCursorNameW: TSQLGetCursorName;
    SQLGetDescFieldW: TSQLGetDescField;
    SQLGetDescRecW: TSQLGetDescRec;
    SQLGetDiagFieldW: TSQLGetDiagField;
    SQLGetDiagRecW: TSQLGetDiagRec;
    SQLGetInfoW: TSQLGetInfo;
    SQLGetStmtAttrW: TSQLGetStmtAttr;
    SQLGetTypeInfoW: TSQLGetTypeInfo;
    SQLPrepareW: TSQLPrepare;
    SQLRowCountW: TSQLRowCount;
    SQLSetConnectAttrW: TSQLSetConnectAttr;
    SQLSetConnectOptionW: TSQLSetConnectOption;
    SQLSetCursorNameW: TSQLSetCursorName;
    SQLSetDescFieldW: TSQLSetDescField;
    SQLSetStmtAttrW: TSQLSetStmtAttr;
    SQLSpecialColumnsW: TSQLSpecialColumns;
    SQLStatisticsW: TSQLStatistics;
    SQLTablesW: TSQLTables;
    // sqlext.h
    SQLDriverConnectW: TSQLDriverConnect;
    SQLBrowseConnectW: TSQLBrowseConnect;
    SQLColAttributesW: TSQLColAttributes;
    SQLColumnPrivilegesW: TSQLColumnPrivileges;
    SQLForeignKeysW: TSQLForeignKeys;
    SQLNativeSqlW: TSQLNativeSql;
    SQLPrimaryKeysW: TSQLPrimaryKeys;
    SQLProcedureColumnsW: TSQLProcedureColumns;
    SQLProceduresW: TSQLProcedures;
    SQLTablePrivilegesW: TSQLTablePrivileges;
    SQLDriversW: TSQLDrivers;
    SQLSetScrollOptionsW: TSQLSetScrollOptions;
   { iOdbcApi }
   // MACROs
    class function SQL_LEN_DATA_AT_EXEC(length: Integer): Integer;
    class function SQL_LEN_BINARY_ATTR(length: Integer): Integer;
    class function SQL_FUNC_EXISTS(pfExists: PUWord; uwAPI: UWord): SqlInteger;
    function SQL_POSITION_TO(HStmt: SqlHStmt; irow: SqlUSmallint): SqlReturn;
    function SQL_LOCK_RECORD(HStmt: SqlHStmt; irow, fLock: SqlUSmallint): SqlReturn;
    function SQL_REFRESH_RECORD(HStmt: SqlHStmt; irow, fLock: SqlUSmallint): SqlReturn;
    function SQL_UPDATE_RECORD(HStmt: SqlHStmt; irow: SqlUSmallint): SqlReturn;
    function SQL_DELETE_RECORD(HStmt: SqlHStmt; irow: SqlUSmallint): SqlReturn;
    function SQL_ADD_RECORD(HStmt: SqlHStmt; irow: SqlUSmallint): SqlReturn;
    function SQLFunctionSupported(ConnectionHandle: SqlHDbc; FunctionId: SqlUSmallint): Boolean;
  // ODBC32DLL
    // sql.h
    function SQLAllocConnect(  EnvironmentHandle: SqlHEnv;
      var ConnectionHandle: SqlHDbc
      ): SqlReturn;
    function SQLAllocEnv(
      var EnvironmentHandle: SqlHEnv
      ): SqlReturn;
    function SQLAllocHandle(
      HandleType: SqlSmallint;
      InputHandle: SqlHandle;
      var OutputHandle: SqlHandle
      ): SqlReturn;
    function SQLAllocStmt(
      ConnectionHandle: SqlHDbc;
      var StatementHandle: SqlHStmt
      ): SqlReturn;
    function SQLBindCol(
      StatementHandle: SqlHStmt;
      ColumnNumber: SqlUSmallint;
      TargetType: SqlSmallint;
      TargetValue: SqlPointer;
      BufferLength: SqlInteger;
      StrLen_or_Ind: PSqlInteger
      ): SqlReturn;
    function SQLBindParam(
      StatementHandle: SqlHStmt;
      ParameterNumber: SqlUSmallint;
      ValueType: SqlSmallint;
      ParameterType: SqlSmallint;
      LengthPrecision: SqlUInteger;
      ParameterScale: SqlSmallint;
      ParameterValue: SqlPointer;
      var StrLen_or_Ind: SqlInteger
      ): SqlReturn;
    function SQLCancel(
      StatementHandle: SqlHStmt
      ): SqlReturn;
    function SQLCloseCursor(
      StatementHandle: SqlHStmt
      ): SqlReturn;
    function SQLColAttribute(
      StatementHandle: SqlHStmt;
      ColumnNumber: SqlUSmallint;
      FieldIdentifier: SqlUSmallint;
      CharacterAttribute: SqlPointer;
      BufferLength: SqlSmallint;
      StringLength: pSqlSmallint;
      NumericAttributePtr: SqlPointer
      ): SqlReturn;
    function SQLColAttributeString(
      StatementHandle: SqlHStmt;
      ColumnNumber: SqlUSmallint;
      FieldIdentifier: SqlUSmallint;
      CharacterAttribute: SqlPointer;
      BufferLength: SqlSmallint;
      var StringLength: SqlSmallint;
      NumericAttribute: SqlPointer
      ): SqlReturn;
    function SQLColAttributeInt(
      StatementHandle: SqlHStmt;
      ColumnNumber: SqlUSmallint;
      FieldIdentifier: SqlUSmallint;
      CharacterAttribute: SqlPointer;
      BufferLength: SqlSmallint;
      StringLength: pSqlSmallint;
      var NumericAttribute: SqlInteger
      ): SqlReturn;
    function SQLColumns(
      StatementHandle: SqlHStmt;
      CatalogName: PAnsiChar;
      NameLength1: SqlSmallint;
      SchemaName: PAnsiChar;
      NameLength2: SqlSmallint;
      TableName: PAnsiChar;
      NameLength3: SqlSmallint;
      ColumnName: PAnsiChar;
      NameLength4: SqlSmallint
      ): SqlReturn;
    function SQLConnect(
      ConnectionHandle: SqlHDbc;
      ServerName: PAnsiChar;
      NameLength1: SqlSmallint;
      UserName: PAnsiChar;
      NameLength2: SqlSmallint;
      Authentication: PAnsiChar;
      NameLength3: SqlSmallint
      ): SqlReturn;
    function SQLCopyDesc(
      SourceDescHandle: SqlHDesc;
      TargetDescHandle: SqlHDesc
      ): SqlReturn;
    function SQLDataSources(
      EnvironmentHandle: SqlHEnv;
      Direction: SqlUSmallint;
      var ServerName: SqlChar;
      BufferLength1: SqlSmallint;
      var NameLength1: SqlSmallint;
      var Description: SqlChar;
      BufferLength2: SqlSmallint;
      var NameLength2: SqlSmallint
      ): SqlReturn;
    function SQLDescribeCol(
      StatementHandle: SqlHStmt;
      ColumnNumber: SqlUSmallint;
      ColumnName: PAnsiChar;
      BufferLength: SqlSmallint;
      var NameLength: SqlSmallint;
      var DataType: SqlSmallint;
      var ColumnSize: SqlUInteger;
      var DecimalDigits: SqlSmallint;
      var Nullable: SqlSmallint
      ): SqlReturn;
    function SQLDisconnect(
      ConnectionHandle: SqlHDbc
      ): SqlReturn;
    function SQLEndTran(
      HandleType: SqlSmallint;
      Handle: SqlHandle;
      CompletionType: SqlSmallint
      ): SqlReturn;
    function SQLError(
      EnvironmentHandle: SqlHEnv;
      ConnectionHandle: SqlHDbc;
      StatementHandle: SqlHStmt;
      var Sqlstate: SqlChar;
      var NativeError: SqlInteger;
      var MessageText: SqlChar;
      BufferLength: SqlSmallint;
      var TextLength: SqlSmallint
      ): SqlReturn;
    function SQLExecDirect(
      StatementHandle: SqlHStmt;
      StatementText: PAnsiChar;
      TextLength: SqlInteger
      ): SqlReturn;
    function SQLExecute(
      StatementHandle: SqlHStmt
      ): SqlReturn;
    function SQLFetch(
      StatementHandle: SqlHStmt
      ): SqlReturn;
    function SQLFetchScroll(
      StatementHandle: SqlHStmt;
      FetchOrientation: SqlSmallint;
      FetchOffset: SqlInteger
      ): SqlReturn;
    function SQLFreeConnect(
      ConnectionHandle: SqlHDbc
      ): SqlReturn;
    function SQLFreeEnv(
      EnvironmentHandle: SqlHEnv
      ): SqlReturn;
    function SQLFreeHandle(
      HandleType: SqlSmallint;
      Handle: SqlHandle
      ): SqlReturn;
    function SQLFreeStmt(
      StatementHandle: SqlHStmt;
      Option: SqlUSmallint
      ): SqlReturn;
    function SQLGetConnectAttr(
      ConnectionHandle: SqlHDbc;
      Attribute: SqlInteger;
      ValuePtr: SqlPointer;
      BufferLength: SqlInteger;
      pStringLength: PSqlInteger
      ): SqlReturn;
    function SQLGetConnectOption(
      ConnectionHandle: SqlHDbc;
      Option: SqlUSmallint;
      Value: SqlPointer
      ): SqlReturn;
    function SQLGetCursorName(
      StatementHandle: SqlHStmt;
      CursorName: PAnsiChar;
      BufferLength: SqlSmallint;
      var NameLength: SqlSmallint
      ): SqlReturn;
    function SQLGetData(
      StatementHandle: SqlHStmt;
      ColumnNumber: SqlUSmallint;
      TargetType: SqlSmallint;
      TargetValue: SqlPointer;
      BufferLength: SqlInteger;
      StrLen_or_Ind: PSqlInteger
      ): SqlReturn;
    function SQLGetDescField(
      DescriptorHandle: SqlHDesc;
      RecNumber: SqlSmallint;
      FieldIdentifier: SqlSmallint;
      Value: SqlPointer;
      BufferLength: SqlInteger;
      var StringLength: SqlInteger
      ): SqlReturn;
    function SQLGetDescRec(
      DescriptorHandle: SqlHDesc;
      RecNumber: SqlSmallint;
      var Name: SqlChar;
      BufferLength: SqlSmallint;
      var StringLength: SqlSmallint;
      var _Type: SqlSmallint;
      var SubType: SqlSmallint;
      var Length: SqlInteger;
      var Precision: SqlSmallint;
      var Scale: SqlSmallint;
      var Nullable: SqlSmallint
      ): SqlReturn;
    function SQLGetDiagField(
      HandleType: SqlSmallint;
      Handle: SqlHandle;
      RecNumber: SqlSmallint;
      DiagIdentifier: SqlSmallint;
      DiagInfo: SqlPointer;
      BufferLength: SqlSmallint;
      var StringLength: SqlSmallint
      ): SqlReturn;
    function SQLGetDiagRec(
      HandleType: SqlSmallint;
      Handle: SqlHandle;
      RecNumber: SqlSmallint;
      Sqlstate: PAnsiChar; // pointer to 5 character buffer
      var NativeError: SqlInteger;
      MessageText: PAnsiChar;
      BufferLength: SqlSmallint;
      var TextLength: SqlSmallint
      ): SqlReturn;
    function SQLGetEnvAttr(
      EnvironmentHandle: SqlHEnv;
      Attribute: SqlInteger;
      Value: SqlPointer;
      BufferLength: SqlInteger;
      var StringLength: SqlInteger
      ): SqlReturn;
    function SQLGetFunctions(
      ConnectionHandle: SqlHDbc;
      FunctionId: SqlUSmallint;
      var Supported: SqlUSmallint
      ): SqlReturn;
    function SQLGetInfo(
      ConnectionHandle: SqlHDbc;
      InfoType: SqlUSmallint;
      InfoValuePtr: SqlPointer;
      BufferLength: SqlSmallint;
      StringLengthPtr: SqlPointer
      ): SqlReturn;
    function SQLGetInfoString(
      ConnectionHandle: SqlHDbc;
      InfoType: SqlUSmallint;
      InfoValueString: PAnsiChar; // PWideChar when calling SQLGetInfoW
      BufferLength: SqlSmallint;
      var StringLength: SqlSmallint
      ): SqlReturn;
    function SQLGetInfoSmallint(
      ConnectionHandle: SqlHDbc;
      InfoType: SqlUSmallint;
      var InfoValue: SqlUSmallint;
      Ignored1: SqlSmallint;
      Ignored2: Pointer
      ): SqlReturn;
    function SQLGetInfoInt(
      ConnectionHandle: SqlHDbc;
      InfoType: SqlUSmallint;
      var InfoValue: SqlUInteger;
      Ignored1: SqlSmallint;
      Ignored2: Pointer
      ): SqlReturn;
    function SQLGetStmtAttr(
      StatementHandle: SqlHStmt;
      Attribute: SqlInteger;
      Value: SqlPointer;
      BufferLength: SqlInteger;
      StringLength: PSqlInteger
      ): SqlReturn;
    function SQLGetStmtOption(
      StatementHandle: SqlHStmt;
      Option: SqlUSmallint;
      Value: SqlPointer
      ): SqlReturn;
    function SQLGetTypeInfo(
      StatementHandle: SqlHStmt;
      DataType: SqlSmallint
      ): SqlReturn;
    function SQLNumResultCols(
      StatementHandle: SqlHStmt;
      var ColumnCount: SqlSmallint
      ): SqlReturn;
    function SQLParamData(
      StatementHandle: SqlHStmt;
      var Value: SqlPointer
      ): SqlReturn;
    function SQLPrepare(
      StatementHandle: SqlHStmt;
      StatementText: PAnsiChar;
      TextLength: SqlInteger
      ): SqlReturn;
    function SQLPutData(
      StatementHandle: SqlHStmt;
      Data: SqlPointer;
      StrLen_or_Ind: SqlInteger
      ): SqlReturn;
    function SQLRowCount(
      StatementHandle: SqlHStmt;
      var RowCount: SqlInteger
      ): SqlReturn;
    function SQLSetConnectAttr(
      ConnectionHandle: SqlHDbc;
      Attribute: SqlInteger;
      ValuePtr: SqlPointer;
      StringLength: SqlInteger
      ): SqlReturn;
    function SQLSetConnectOption(
      ConnectionHandle: SqlHDbc;
      Option: SqlUSmallint;
      Value: SqlUInteger
      ): SqlReturn;
    function SQLSetCursorName(
      StatementHandle: SqlHStmt;
      CursorName: PAnsiChar;
      NameLength: SqlSmallint
      ): SqlReturn;
    function SQLSetDescField(
      DescriptorHandle: SqlHDesc;
      RecNumber: SqlSmallint;
      FieldIdentifier: SqlSmallint;
      Value: SqlPointer;
      BufferLength: SqlInteger
      ): SqlReturn;
    function SQLSetDescRec(
      DescriptorHandle: SqlHDesc;
      RecNumber: SqlSmallint;
      _Type: SqlSmallint;
      SubType: SqlSmallint;
      Length: SqlInteger;
      Precision: SqlSmallint;
      Scale: SqlSmallint;
      Data: SqlPointer;
      var StringLength: SqlInteger;
      var Indicator: SqlInteger
      ): SqlReturn;
    function SQLSetEnvAttr(
      EnvironmentHandle: SqlHEnv;
      Attribute: SqlInteger;
      ValuePtr: Pointer;
      StringLength: SqlInteger
      ): SqlReturn;
    function SQLSetParam(
      StatementHandle: SqlHStmt;
      ParameterNumber: SqlUSmallint;
      ValueType: SqlSmallint;
      ParameterType: SqlSmallint;
      LengthPrecision: SqlUInteger;
      ParameterScale: SqlSmallint;
      ParameterValue: SqlPointer;
      var StrLen_or_Ind: SqlInteger
      ): SqlReturn;
    function SQLSetStmtAttr(
      StatementHandle: SqlHStmt;
      Attribute: SqlInteger;
      Value: SqlPointer;
      StringLength: SqlInteger
      ): SqlReturn;
    function SQLSetStmtOption(
      StatementHandle: SqlHStmt;
      Option: SqlUSmallint;
      Value: SqlUInteger
      ): SqlReturn;
    function SQLSpecialColumns(
      StatementHandle: SqlHStmt;
      IdentifierType: SqlUSmallint;
      CatalogName: PAnsiChar;
      NameLength1: SqlSmallint;
      SchemaName: PAnsiChar;
      NameLength2: SqlSmallint;
      TableName: PAnsiChar;
      NameLength3: SqlSmallint;
      Scope: SqlUSmallint;
      Nullable: SqlUSmallint
      ): SqlReturn;
    function SQLStatistics(
      StatementHandle: SqlHStmt;
      CatalogName: PAnsiChar;
      NameLength1: SqlSmallint;
      SchemaName: PAnsiChar;
      NameLength2: SqlSmallint;
      TableName: PAnsiChar;
      NameLength3: SqlSmallint;
      Unique: SqlUSmallint;
      Reserved: SqlUSmallint
      ): SqlReturn;
    function SQLTables(
      StatementHandle: SqlHStmt;
      CatalogName: PAnsiChar;
      NameLength1: SqlSmallint;
      SchemaName: PAnsiChar;
      NameLength2: SqlSmallint;
      TableName: PAnsiChar;
      NameLength3: SqlSmallint;
      TableType: PAnsiChar;
      NameLength4: SqlSmallint
      ): SqlReturn;
    function SQLTransact(
      EnvironmentHandle: SqlHEnv;
      ConnectionHandle: SqlHDbc;
      CompletionType: SqlUSmallint
      ): SqlReturn;
    // sqlext.h
    function SQLDriverConnect(
      HDbc: SqlHDbc;
      hwnd: SqlHWnd;
      szConnStrIn: PAnsiChar;
      cbConnStrIn: SqlSmallint;
      szConnStrOut: PAnsiChar;
      cbConnStrOutMax: SqlSmallint;
      var pcbConnStrOut: SqlSmallint;
      fDriverCompletion: SqlUSmallint
      ): SqlReturn;
    function SQLBrowseConnect(
      HDbc: SqlHDbc;
      var szConnStrIn: SqlChar;
      cbConnStrIn: SqlSmallint;
      var szConnStrOut: SqlChar;
      cbConnStrOutMax: SqlSmallint;
      var pcbConnStrOut: SqlSmallint
      ): SqlReturn;
    function SQLBulkOperations(
      StatementHandle: SqlHStmt;
      Operation: SqlSmallint
      ): SqlReturn;
    function SQLColAttributes(
      HStmt: SqlHStmt;
      icol: SqlUSmallint;
      fDescType: SqlUSmallint;
      rgbDesc: SqlPointer;
      cbDescMax: SqlSmallint;
      var pcbDesc: SqlSmallint;
      var pfDesc: SqlInteger
      ): SqlReturn;
    function SQLColumnPrivileges(
      HStmt: SqlHStmt;
      var szCatalogName: SqlChar;
      cbCatalogName: SqlSmallint;
      var szSchemaName: SqlChar;
      cbSchemaName: SqlSmallint;
      var szTableName: SqlChar;
      cbTableName: SqlSmallint;
      var szColumnName: SqlChar;
      cbColumnName: SqlSmallint
      ): SqlReturn;
    function SQLDescribeParam(
      HStmt: SqlHStmt;
      ipar: SqlUSmallint;
      var pfSqlType: SqlSmallint;
      var pcbParamDef: SqlUInteger;
      var pibScale: SqlSmallint;
      var pfNullable: SqlSmallint
      ): SqlReturn;
    function SQLExtendedFetch(
      HStmt: SqlHStmt;
      fFetchType: SqlUSmallint;
      irow: SqlInteger;
      var pcrow: SqlUInteger;
      var rgfRowStatus: SqlUSmallint
      ): SqlReturn;
    function SQLForeignKeys(
      HStmt: SqlHStmt;
      var szPkCatalogName: SqlChar;
      cbPkCatalogName: SqlSmallint;
      var szPkSchemaName: SqlChar;
      cbPkSchemaName: SqlSmallint;
      var szPkTableName: SqlChar;
      cbPkTableName: SqlSmallint;
      var szFkCatalogName: SqlChar;
      cbFkCatalogName: SqlSmallint;
      var szFkSchemaName: SqlChar;
      cbFkSchemaName: SqlSmallint;
      var szFkTableName: SqlChar;
      cbFkTableName: SqlSmallint
      ): SqlReturn;
    function SQLMoreResults(
      HStmt: SqlHStmt
      ): SqlReturn;
    function SQLNativeSql(
      HDbc: SqlHDbc;
      var szSqlStrIn: SqlChar;
      cbSqlStrIn: SqlInteger;
      var szSqlStr: SqlChar;
      cbSqlStrMax: SqlInteger;
      var pcbSqlStr: SqlInteger
      ): SqlReturn;
    function SQLNumParams(
      HStmt: SqlHStmt;
      var pcpar: SqlSmallint
      ): SqlReturn;
    function SQLParamOptions(
      HStmt: SqlHStmt;
      crow: SqlUInteger;
      var pirow: SqlUInteger
      ): SqlReturn;
    function SQLPrimaryKeys(
      HStmt: SqlHStmt;
      szCatalogName: PAnsiChar;
      cbCatalogName: SqlSmallint;
      szSchemaName: PAnsiChar;
      cbSchemaName: SqlSmallint;
      szTableName: PAnsiChar;
      cbTableName: SqlSmallint
      ): SqlReturn;
    function SQLProcedureColumns(
      HStmt: SqlHStmt;
      szCatalogName: PAnsiChar;
      cbCatalogName: SqlSmallint;
      szSchemaName: PAnsiChar;
      cbSchemaName: SqlSmallint;
      szProcName: PAnsiChar;
      cbProcName: SqlSmallint;
      szColumnName: PAnsiChar;
      cbColumnName: SqlSmallint
      ): SqlReturn;
    function SQLProcedures(
      HStmt: SqlHStmt;
      szCatalogName: PAnsiChar;
      cbCatalogName: SqlSmallint;
      szSchemaName: PAnsiChar;
      cbSchemaName: SqlSmallint;
      szProcName: PAnsiChar;
      cbProcName: SqlSmallint
      ): SqlReturn;
    function SQLSetPos(
      HStmt: SqlHStmt;
      irow: SqlUSmallint;
      fOption: SqlUSmallint;
      fLock: SqlUSmallint
      ): SqlReturn;
    function SQLTablePrivileges(
      HStmt: SqlHStmt;
      var szCatalogName: SqlChar;
      cbCatalogName: SqlSmallint;
      var szSchemaName: SqlChar;
      cbSchemaName: SqlSmallint;
      var szTableName: SqlChar;
      cbTableName: SqlSmallint
      ): SqlReturn;
    function SQLDrivers(
      HEnv: SqlHEnv;
      fDirection: SqlUSmallint;
      szDriverDesc: PAnsiChar;
      cbDriverDescMax: SqlSmallint;
      var pcbDriverDesc: SqlSmallint;
      szDriverAttributes: PAnsiChar;
      cbDrvrAttrMax: SqlSmallint;
      var pcbDrvrAttr: SqlSmallint
      ): SqlReturn;
    function SQLBindParameter(
      HStmt: SqlHStmt;
      ipar: SqlUSmallint;
      fParamType: SqlSmallint;
      fCType: SqlSmallint;
      fSqlType: SqlSmallint;
      cbColDef: SqlUInteger;
      ibScale: SqlSmallint;
      rgbValue: SqlPointer;
      cbValueMax: SqlInteger;
      pcbValue: PSqlInteger
      ): SqlReturn;
    function SQLAllocHandleStd(
      fHandleType: SqlSmallint;
      hInput: SqlHandle;
      var phOutput: SqlHandle
      ): SqlReturn;
    function SQLSetScrollOptions( // Use SQLSetStmtOptions
      HStmt: SqlHStmt;
      fConcurrency: SqlUSmallint;
      crowKeyset: SqlInteger;
      crowRowset: SqlUSmallint
      ): SqlReturn;
    //ODBCTRAC
    function TraceOpenLogFile(
      var _1: WideChar;
      var _2: WideChar;
      _3: Longint
      ): Retcode;
    function TraceCloseLogFile: Retcode;
    procedure TraceReturn(
      _1: Retcode;
      _2: Retcode);
    function TraceVersion: Longint;
    function TraceVSControl(_1: Longint): Retcode;
    procedure FireVSDebugEvent(var Args: ODBC_VS_ARGS);
    //ODBCINST
    function ODBCSetTryWaitValue(dwValue: Longint): LongBool;
    function ODBCGetTryWaitValue: Longint;
  end;
  {$hints on}
{$ELSE}
  TOdbcApiProxy = class
  private
    fApiRefCount: Integer;
    fSystemODBCManager: Boolean;
    fOdbcDriverLevel: Integer;
    fLockObj: TCriticalSection;
    {$IFDEF _iOdbcApi_}
    fOdbcApiImpl: TOdbcApiIntfImpl;
    fOdbcApiIntf: IOdbcApi;
    {$ENDIF}
    procedure SetOdbcDriverLevel(aOdbcDriverLevel: Integer);
    procedure BeginLock;
    procedure EndLock;
  public
    constructor Create;
    destructor Destroy; override;
    function GetOdbcApiIntf: IUnknown;
    property SystemODBCManager: Boolean read fSystemODBCManager default True;
    property OdbcDriverLevel: Integer read fOdbcDriverLevel write SetOdbcDriverLevel;
  end;
{$ENDIF IFDEF DynamicOdbcImport}

{$IFDEF _iOdbcApi_}

  IOdbcApi = interface
    ['{6DA86068-0BC3-4BFC-B9FC-FF8FEC5CD106}']
   // MACROs
    function SQL_LEN_DATA_AT_EXEC(length: Integer): Integer;
    function SQL_LEN_BINARY_ATTR(length: Integer): Integer;
    function SQL_FUNC_EXISTS(pfExists: PUWord; uwAPI: UWord): SqlInteger;
    function SQL_POSITION_TO(HStmt: SqlHStmt; irow: SqlUSmallint): SqlReturn;
    function SQL_LOCK_RECORD(HStmt: SqlHStmt; irow, fLock: SqlUSmallint): SqlReturn;
    function SQL_REFRESH_RECORD(HStmt: SqlHStmt; irow, fLock: SqlUSmallint): SqlReturn;
    function SQL_UPDATE_RECORD(HStmt: SqlHStmt; irow: SqlUSmallint): SqlReturn;
    function SQL_DELETE_RECORD(HStmt: SqlHStmt; irow: SqlUSmallint): SqlReturn;
    function SQL_ADD_RECORD(HStmt: SqlHStmt; irow: SqlUSmallint): SqlReturn;
    function SQLFunctionSupported(ConnectionHandle: SqlHDbc; FunctionId: SqlUSmallint): Boolean;
  // ODBC32DLL
    // sql.h
    function SQLAllocConnect(  EnvironmentHandle: SqlHEnv;
      var ConnectionHandle: SqlHDbc
      ): SqlReturn;
    function SQLAllocEnv(
      var EnvironmentHandle: SqlHEnv
      ): SqlReturn;
    function SQLAllocHandle(
      HandleType: SqlSmallint;
      InputHandle: SqlHandle;
      var OutputHandle: SqlHandle
      ): SqlReturn;
    function SQLAllocStmt(
      ConnectionHandle: SqlHDbc;
      var StatementHandle: SqlHStmt
      ): SqlReturn;
    function SQLBindCol(
      StatementHandle: SqlHStmt;
      ColumnNumber: SqlUSmallint;
      TargetType: SqlSmallint;
      TargetValue: SqlPointer;
      BufferLength: SqlInteger;
      StrLen_or_Ind: PSqlInteger
      ): SqlReturn;
    function SQLBindParam(
      StatementHandle: SqlHStmt;
      ParameterNumber: SqlUSmallint;
      ValueType: SqlSmallint;
      ParameterType: SqlSmallint;
      LengthPrecision: SqlUInteger;
      ParameterScale: SqlSmallint;
      ParameterValue: SqlPointer;
      var StrLen_or_Ind: SqlInteger
      ): SqlReturn;
    function SQLCancel(
      StatementHandle: SqlHStmt
      ): SqlReturn;
    function SQLCloseCursor(
      StatementHandle: SqlHStmt
      ): SqlReturn;
    function SQLColAttribute(
      StatementHandle: SqlHStmt;
      ColumnNumber: SqlUSmallint;
      FieldIdentifier: SqlUSmallint;
      CharacterAttribute: SqlPointer;
      BufferLength: SqlSmallint;
      StringLength: pSqlSmallint;
      NumericAttributePtr: SqlPointer
      ): SqlReturn;
    function SQLColAttributeString(
      StatementHandle: SqlHStmt;
      ColumnNumber: SqlUSmallint;
      FieldIdentifier: SqlUSmallint;
      CharacterAttribute: SqlPointer;
      BufferLength: SqlSmallint;
      var StringLength: SqlSmallint;
      NumericAttribute: SqlPointer
      ): SqlReturn;
    function SQLColAttributeInt(
      StatementHandle: SqlHStmt;
      ColumnNumber: SqlUSmallint;
      FieldIdentifier: SqlUSmallint;
      CharacterAttribute: SqlPointer;
      BufferLength: SqlSmallint;
      StringLength: pSqlSmallint;
      var NumericAttribute: SqlInteger
      ): SqlReturn;
    function SQLColumns(
      StatementHandle: SqlHStmt;
      CatalogName: PAnsiChar;
      NameLength1: SqlSmallint;
      SchemaName: PAnsiChar;
      NameLength2: SqlSmallint;
      TableName: PAnsiChar;
      NameLength3: SqlSmallint;
      ColumnName: PAnsiChar;
      NameLength4: SqlSmallint
      ): SqlReturn;
    function SQLConnect(
      ConnectionHandle: SqlHDbc;
      ServerName: PAnsiChar;
      NameLength1: SqlSmallint;
      UserName: PAnsiChar;
      NameLength2: SqlSmallint;
      Authentication: PAnsiChar;
      NameLength3: SqlSmallint
      ): SqlReturn;
    function SQLCopyDesc(
      SourceDescHandle: SqlHDesc;
      TargetDescHandle: SqlHDesc
      ): SqlReturn;
    function SQLDataSources(
      EnvironmentHandle: SqlHEnv;
      Direction: SqlUSmallint;
      var ServerName: SqlChar;
      BufferLength1: SqlSmallint;
      var NameLength1: SqlSmallint;
      var Description: SqlChar;
      BufferLength2: SqlSmallint;
      var NameLength2: SqlSmallint
      ): SqlReturn;
    function SQLDescribeCol(
      StatementHandle: SqlHStmt;
      ColumnNumber: SqlUSmallint;
      ColumnName: PAnsiChar;
      BufferLength: SqlSmallint;
      var NameLength: SqlSmallint;
      var DataType: SqlSmallint;
      var ColumnSize: SqlUInteger;
      var DecimalDigits: SqlSmallint;
      var Nullable: SqlSmallint
      ): SqlReturn;
    function SQLDisconnect(
      ConnectionHandle: SqlHDbc
      ): SqlReturn;
    function SQLEndTran(
      HandleType: SqlSmallint;
      Handle: SqlHandle;
      CompletionType: SqlSmallint
      ): SqlReturn;
    function SQLError(
      EnvironmentHandle: SqlHEnv;
      ConnectionHandle: SqlHDbc;
      StatementHandle: SqlHStmt;
      var Sqlstate: SqlChar;
      var NativeError: SqlInteger;
      var MessageText: SqlChar;
      BufferLength: SqlSmallint;
      var TextLength: SqlSmallint
      ): SqlReturn;
    function SQLExecDirect(
      StatementHandle: SqlHStmt;
      StatementText: PAnsiChar;
      TextLength: SqlInteger
      ): SqlReturn;
    function SQLExecute(
      StatementHandle: SqlHStmt
      ): SqlReturn;
    function SQLFetch(
      StatementHandle: SqlHStmt
      ): SqlReturn;
    function SQLFetchScroll(
      StatementHandle: SqlHStmt;
      FetchOrientation: SqlSmallint;
      FetchOffset: SqlInteger
      ): SqlReturn;
    function SQLFreeConnect(
      ConnectionHandle: SqlHDbc
      ): SqlReturn;
    function SQLFreeEnv(
      EnvironmentHandle: SqlHEnv
      ): SqlReturn;
    function SQLFreeHandle(
      HandleType: SqlSmallint;
      Handle: SqlHandle
      ): SqlReturn;
    function SQLFreeStmt(
      StatementHandle: SqlHStmt;
      Option: SqlUSmallint
      ): SqlReturn;
    function SQLGetConnectAttr(
      ConnectionHandle: SqlHDbc;
      Attribute: SqlInteger;
      ValuePtr: SqlPointer;
      BufferLength: SqlInteger;
      pStringLength: PSqlInteger
      ): SqlReturn;
    function SQLGetConnectOption(
      ConnectionHandle: SqlHDbc;
      Option: SqlUSmallint;
      Value: SqlPointer
      ): SqlReturn;
    function SQLGetCursorName(
      StatementHandle: SqlHStmt;
      CursorName: PAnsiChar;
      BufferLength: SqlSmallint;
      var NameLength: SqlSmallint
      ): SqlReturn;
    function SQLGetData(
      StatementHandle: SqlHStmt;
      ColumnNumber: SqlUSmallint;
      TargetType: SqlSmallint;
      TargetValue: SqlPointer;
      BufferLength: SqlInteger;
      StrLen_or_Ind: PSqlInteger
      ): SqlReturn;
    function SQLGetDescField(
      DescriptorHandle: SqlHDesc;
      RecNumber: SqlSmallint;
      FieldIdentifier: SqlSmallint;
      Value: SqlPointer;
      BufferLength: SqlInteger;
      var StringLength: SqlInteger
      ): SqlReturn;
    function SQLGetDescRec(
      DescriptorHandle: SqlHDesc;
      RecNumber: SqlSmallint;
      var Name: SqlChar;
      BufferLength: SqlSmallint;
      var StringLength: SqlSmallint;
      var _Type: SqlSmallint;
      var SubType: SqlSmallint;
      var Length: SqlInteger;
      var Precision: SqlSmallint;
      var Scale: SqlSmallint;
      var Nullable: SqlSmallint
      ): SqlReturn;
    function SQLGetDiagField(
      HandleType: SqlSmallint;
      Handle: SqlHandle;
      RecNumber: SqlSmallint;
      DiagIdentifier: SqlSmallint;
      DiagInfo: SqlPointer;
      BufferLength: SqlSmallint;
      var StringLength: SqlSmallint
      ): SqlReturn;
    function SQLGetDiagRec(
      HandleType: SqlSmallint;
      Handle: SqlHandle;
      RecNumber: SqlSmallint;
      Sqlstate: PAnsiChar; // pointer to 5 character buffer
      var NativeError: SqlInteger;
      MessageText: PAnsiChar;
      BufferLength: SqlSmallint;
      var TextLength: SqlSmallint
      ): SqlReturn;
    function SQLGetEnvAttr(
      EnvironmentHandle: SqlHEnv;
      Attribute: SqlInteger;
      Value: SqlPointer;
      BufferLength: SqlInteger;
      var StringLength: SqlInteger
      ): SqlReturn;
    function SQLGetFunctions(
      ConnectionHandle: SqlHDbc;
      FunctionId: SqlUSmallint;
      var Supported: SqlUSmallint
      ): SqlReturn;
    function SQLGetInfo(
      ConnectionHandle: SqlHDbc;
      InfoType: SqlUSmallint;
      InfoValuePtr: SqlPointer;
      BufferLength: SqlSmallint;
      StringLengthPtr: SqlPointer
      ): SqlReturn;
    function SQLGetInfoString(
      ConnectionHandle: SqlHDbc;
      InfoType: SqlUSmallint;
      InfoValueString: PAnsiChar; // PWideChar when calling SQLGetInfoW
      BufferLength: SqlSmallint;
      var StringLength: SqlSmallint
      ): SqlReturn;
    function SQLGetInfoSmallint(
      ConnectionHandle: SqlHDbc;
      InfoType: SqlUSmallint;
      var InfoValue: SqlUSmallint;
      Ignored1: SqlSmallint;
      Ignored2: Pointer
      ): SqlReturn;
    function SQLGetInfoInt(
      ConnectionHandle: SqlHDbc;
      InfoType: SqlUSmallint;
      var InfoValue: SqlUInteger;
      Ignored1: SqlSmallint;
      Ignored2: Pointer
      ): SqlReturn;
    function SQLGetStmtAttr(
      StatementHandle: SqlHStmt;
      Attribute: SqlInteger;
      Value: SqlPointer;
      BufferLength: SqlInteger;
      StringLength: PSqlInteger
      ): SqlReturn;
    function SQLGetStmtOption(
      StatementHandle: SqlHStmt;
      Option: SqlUSmallint;
      Value: SqlPointer
      ): SqlReturn;
    function SQLGetTypeInfo(
      StatementHandle: SqlHStmt;
      DataType: SqlSmallint
      ): SqlReturn;
    function SQLNumResultCols(
      StatementHandle: SqlHStmt;
      var ColumnCount: SqlSmallint
      ): SqlReturn;
    function SQLParamData(
      StatementHandle: SqlHStmt;
      var Value: SqlPointer
      ): SqlReturn;
    function SQLPrepare(
      StatementHandle: SqlHStmt;
      StatementText: PAnsiChar;
      TextLength: SqlInteger
      ): SqlReturn;
    function SQLPutData(
      StatementHandle: SqlHStmt;
      Data: SqlPointer;
      StrLen_or_Ind: SqlInteger
      ): SqlReturn;
    function SQLRowCount(
      StatementHandle: SqlHStmt;
      var RowCount: SqlInteger
      ): SqlReturn;
    function SQLSetConnectAttr(
      ConnectionHandle: SqlHDbc;
      Attribute: SqlInteger;
      ValuePtr: SqlPointer;
      StringLength: SqlInteger
      ): SqlReturn;
    function SQLSetConnectOption(
      ConnectionHandle: SqlHDbc;
      Option: SqlUSmallint;
      Value: SqlUInteger
      ): SqlReturn;
    function SQLSetCursorName(
      StatementHandle: SqlHStmt;
      CursorName: PAnsiChar;
      NameLength: SqlSmallint
      ): SqlReturn;
    function SQLSetDescField(
      DescriptorHandle: SqlHDesc;
      RecNumber: SqlSmallint;
      FieldIdentifier: SqlSmallint;
      Value: SqlPointer;
      BufferLength: SqlInteger
      ): SqlReturn;
    function SQLSetDescRec(
      DescriptorHandle: SqlHDesc;
      RecNumber: SqlSmallint;
      _Type: SqlSmallint;
      SubType: SqlSmallint;
      Length: SqlInteger;
      Precision: SqlSmallint;
      Scale: SqlSmallint;
      Data: SqlPointer;
      var StringLength: SqlInteger;
      var Indicator: SqlInteger
      ): SqlReturn;
    function SQLSetEnvAttr(
      EnvironmentHandle: SqlHEnv;
      Attribute: SqlInteger;
      ValuePtr: Pointer;
      StringLength: SqlInteger
      ): SqlReturn;
    function SQLSetParam(
      StatementHandle: SqlHStmt;
      ParameterNumber: SqlUSmallint;
      ValueType: SqlSmallint;
      ParameterType: SqlSmallint;
      LengthPrecision: SqlUInteger;
      ParameterScale: SqlSmallint;
      ParameterValue: SqlPointer;
      var StrLen_or_Ind: SqlInteger
      ): SqlReturn;
    function SQLSetStmtAttr(
      StatementHandle: SqlHStmt;
      Attribute: SqlInteger;
      Value: SqlPointer;
      StringLength: SqlInteger
      ): SqlReturn;
    function SQLSetStmtOption(
      StatementHandle: SqlHStmt;
      Option: SqlUSmallint;
      Value: SqlUInteger
      ): SqlReturn;
    function SQLSpecialColumns(
      StatementHandle: SqlHStmt;
      IdentifierType: SqlUSmallint;
      CatalogName: PAnsiChar;
      NameLength1: SqlSmallint;
      SchemaName: PAnsiChar;
      NameLength2: SqlSmallint;
      TableName: PAnsiChar;
      NameLength3: SqlSmallint;
      Scope: SqlUSmallint;
      Nullable: SqlUSmallint
      ): SqlReturn;
    function SQLStatistics(
      StatementHandle: SqlHStmt;
      CatalogName: PAnsiChar;
      NameLength1: SqlSmallint;
      SchemaName: PAnsiChar;
      NameLength2: SqlSmallint;
      TableName: PAnsiChar;
      NameLength3: SqlSmallint;
      Unique: SqlUSmallint;
      Reserved: SqlUSmallint
      ): SqlReturn;
    function SQLTables(
      StatementHandle: SqlHStmt;
      CatalogName: PAnsiChar;
      NameLength1: SqlSmallint;
      SchemaName: PAnsiChar;
      NameLength2: SqlSmallint;
      TableName: PAnsiChar;
      NameLength3: SqlSmallint;
      TableType: PAnsiChar;
      NameLength4: SqlSmallint
      ): SqlReturn;
    function SQLTransact(
      EnvironmentHandle: SqlHEnv;
      ConnectionHandle: SqlHDbc;
      CompletionType: SqlUSmallint
      ): SqlReturn;
    // sqlext.h
    function SQLDriverConnect(
      HDbc: SqlHDbc;
      hwnd: SqlHWnd;
      szConnStrIn: PAnsiChar;
      cbConnStrIn: SqlSmallint;
      szConnStrOut: PAnsiChar;
      cbConnStrOutMax: SqlSmallint;
      var pcbConnStrOut: SqlSmallint;
      fDriverCompletion: SqlUSmallint
      ): SqlReturn;
    function SQLBrowseConnect(
      HDbc: SqlHDbc;
      var szConnStrIn: SqlChar;
      cbConnStrIn: SqlSmallint;
      var szConnStrOut: SqlChar;
      cbConnStrOutMax: SqlSmallint;
      var pcbConnStrOut: SqlSmallint
      ): SqlReturn;
    function SQLBulkOperations(
      StatementHandle: SqlHStmt;
      Operation: SqlSmallint
      ): SqlReturn;
    function SQLColAttributes(
      HStmt: SqlHStmt;
      icol: SqlUSmallint;
      fDescType: SqlUSmallint;
      rgbDesc: SqlPointer;
      cbDescMax: SqlSmallint;
      var pcbDesc: SqlSmallint;
      var pfDesc: SqlInteger
      ): SqlReturn;
    function SQLColumnPrivileges(
      HStmt: SqlHStmt;
      var szCatalogName: SqlChar;
      cbCatalogName: SqlSmallint;
      var szSchemaName: SqlChar;
      cbSchemaName: SqlSmallint;
      var szTableName: SqlChar;
      cbTableName: SqlSmallint;
      var szColumnName: SqlChar;
      cbColumnName: SqlSmallint
      ): SqlReturn;
    function SQLDescribeParam(
      HStmt: SqlHStmt;
      ipar: SqlUSmallint;
      var pfSqlType: SqlSmallint;
      var pcbParamDef: SqlUInteger;
      var pibScale: SqlSmallint;
      var pfNullable: SqlSmallint
      ): SqlReturn;
    function SQLExtendedFetch(
      HStmt: SqlHStmt;
      fFetchType: SqlUSmallint;
      irow: SqlInteger;
      var pcrow: SqlUInteger;
      var rgfRowStatus: SqlUSmallint
      ): SqlReturn;
    function SQLForeignKeys(
      HStmt: SqlHStmt;
      var szPkCatalogName: SqlChar;
      cbPkCatalogName: SqlSmallint;
      var szPkSchemaName: SqlChar;
      cbPkSchemaName: SqlSmallint;
      var szPkTableName: SqlChar;
      cbPkTableName: SqlSmallint;
      var szFkCatalogName: SqlChar;
      cbFkCatalogName: SqlSmallint;
      var szFkSchemaName: SqlChar;
      cbFkSchemaName: SqlSmallint;
      var szFkTableName: SqlChar;
      cbFkTableName: SqlSmallint
      ): SqlReturn;
    function SQLMoreResults(
      HStmt: SqlHStmt
      ): SqlReturn;
    function SQLNativeSql(
      HDbc: SqlHDbc;
      var szSqlStrIn: SqlChar;
      cbSqlStrIn: SqlInteger;
      var szSqlStr: SqlChar;
      cbSqlStrMax: SqlInteger;
      var pcbSqlStr: SqlInteger
      ): SqlReturn;
    function SQLNumParams(
      HStmt: SqlHStmt;
      var pcpar: SqlSmallint
      ): SqlReturn;
    function SQLParamOptions(
      HStmt: SqlHStmt;
      crow: SqlUInteger;
      var pirow: SqlUInteger
      ): SqlReturn;
    function SQLPrimaryKeys(
      HStmt: SqlHStmt;
      szCatalogName: PAnsiChar;
      cbCatalogName: SqlSmallint;
      szSchemaName: PAnsiChar;
      cbSchemaName: SqlSmallint;
      szTableName: PAnsiChar;
      cbTableName: SqlSmallint
      ): SqlReturn;
    function SQLProcedureColumns(
      HStmt: SqlHStmt;
      szCatalogName: PAnsiChar;
      cbCatalogName: SqlSmallint;
      szSchemaName: PAnsiChar;
      cbSchemaName: SqlSmallint;
      szProcName: PAnsiChar;
      cbProcName: SqlSmallint;
      szColumnName: PAnsiChar;
      cbColumnName: SqlSmallint
      ): SqlReturn;
    function SQLProcedures(
      HStmt: SqlHStmt;
      szCatalogName: PAnsiChar;
      cbCatalogName: SqlSmallint;
      szSchemaName: PAnsiChar;
      cbSchemaName: SqlSmallint;
      szProcName: PAnsiChar;
      cbProcName: SqlSmallint
      ): SqlReturn;
    function SQLSetPos(
      HStmt: SqlHStmt;
      irow: SqlUSmallint;
      fOption: SqlUSmallint;
      fLock: SqlUSmallint
      ): SqlReturn;
    function SQLTablePrivileges(
      HStmt: SqlHStmt;
      var szCatalogName: SqlChar;
      cbCatalogName: SqlSmallint;
      var szSchemaName: SqlChar;
      cbSchemaName: SqlSmallint;
      var szTableName: SqlChar;
      cbTableName: SqlSmallint
      ): SqlReturn;
    function SQLDrivers(
      HEnv: SqlHEnv;
      fDirection: SqlUSmallint;
      szDriverDesc: PAnsiChar;
      cbDriverDescMax: SqlSmallint;
      var pcbDriverDesc: SqlSmallint;
      szDriverAttributes: PAnsiChar;
      cbDrvrAttrMax: SqlSmallint;
      var pcbDrvrAttr: SqlSmallint
      ): SqlReturn;
    function SQLBindParameter(
      HStmt: SqlHStmt;
      ipar: SqlUSmallint;
      fParamType: SqlSmallint;
      fCType: SqlSmallint;
      fSqlType: SqlSmallint;
      cbColDef: SqlUInteger;
      ibScale: SqlSmallint;
      rgbValue: SqlPointer;
      cbValueMax: SqlInteger;
      pcbValue: PSqlInteger
      ): SqlReturn;
    function SQLAllocHandleStd(
      fHandleType: SqlSmallint;
      hInput: SqlHandle;
      var phOutput: SqlHandle
      ): SqlReturn;
    function SQLSetScrollOptions( // Use SQLSetStmtOptions
      HStmt: SqlHStmt;
      fConcurrency: SqlUSmallint;
      crowKeyset: SqlInteger;
      crowRowset: SqlUSmallint
      ): SqlReturn;
    //ODBCTRAC
    function TraceOpenLogFile(
      var _1: WideChar;
      var _2: WideChar;
      _3: Longint
      ): Retcode;
    function TraceCloseLogFile: Retcode;
    procedure TraceReturn(
      _1: Retcode;
      _2: Retcode);
    function TraceVersion: Longint;
    function TraceVSControl(_1: Longint): Retcode;
    procedure FireVSDebugEvent(var Args: ODBC_VS_ARGS);
    //ODBCINST
    function ODBCSetTryWaitValue(dwValue: Longint): LongBool;
    function ODBCGetTryWaitValue: Longint;
  end;

  TOdbcApiIntfImpl = class(TInterfacedObject, IOdbcApi)
  private
    fOdbcApiProxy: TOdbcApiProxy;
    {$IFDEF DynamicOdbcImport}
    procedure CheckAvailableProxy;
    {$ENDIF}
  { IOdbcApi }
  protected
   // MACROs
    function SQL_LEN_DATA_AT_EXEC(length: Integer): Integer;
    function SQL_LEN_BINARY_ATTR(length: Integer): Integer;
    function SQL_FUNC_EXISTS(pfExists: PUWord; uwAPI: UWord): SqlInteger;
    function SQL_POSITION_TO(HStmt: SqlHStmt; irow: SqlUSmallint): SqlReturn;
    function SQL_LOCK_RECORD(HStmt: SqlHStmt; irow, fLock: SqlUSmallint): SqlReturn;
    function SQL_REFRESH_RECORD(HStmt: SqlHStmt; irow, fLock: SqlUSmallint): SqlReturn;
    function SQL_UPDATE_RECORD(HStmt: SqlHStmt; irow: SqlUSmallint): SqlReturn;
    function SQL_DELETE_RECORD(HStmt: SqlHStmt; irow: SqlUSmallint): SqlReturn;
    function SQL_ADD_RECORD(HStmt: SqlHStmt; irow: SqlUSmallint): SqlReturn;
    function SQLFunctionSupported(ConnectionHandle: SqlHDbc; FunctionId: SqlUSmallint): Boolean;
  // ODBC32DLL
    // sql.h
    function SQLAllocConnect(  EnvironmentHandle: SqlHEnv;
      var ConnectionHandle: SqlHDbc
      ): SqlReturn;
    function SQLAllocEnv(
      var EnvironmentHandle: SqlHEnv
      ): SqlReturn;
    function SQLAllocHandle(
      HandleType: SqlSmallint;
      InputHandle: SqlHandle;
      var OutputHandle: SqlHandle
      ): SqlReturn;
    function SQLAllocStmt(
      ConnectionHandle: SqlHDbc;
      var StatementHandle: SqlHStmt
      ): SqlReturn;
    function SQLBindCol(
      StatementHandle: SqlHStmt;
      ColumnNumber: SqlUSmallint;
      TargetType: SqlSmallint;
      TargetValue: SqlPointer;
      BufferLength: SqlInteger;
      StrLen_or_Ind: PSqlInteger
      ): SqlReturn;
    function SQLBindParam(
      StatementHandle: SqlHStmt;
      ParameterNumber: SqlUSmallint;
      ValueType: SqlSmallint;
      ParameterType: SqlSmallint;
      LengthPrecision: SqlUInteger;
      ParameterScale: SqlSmallint;
      ParameterValue: SqlPointer;
      var StrLen_or_Ind: SqlInteger
      ): SqlReturn;
    function SQLCancel(
      StatementHandle: SqlHStmt
      ): SqlReturn;
    function SQLCloseCursor(
      StatementHandle: SqlHStmt
      ): SqlReturn;
    function SQLColAttribute(
      StatementHandle: SqlHStmt;
      ColumnNumber: SqlUSmallint;
      FieldIdentifier: SqlUSmallint;
      CharacterAttribute: SqlPointer;
      BufferLength: SqlSmallint;
      StringLength: pSqlSmallint;
      NumericAttributePtr: SqlPointer
      ): SqlReturn;
    function SQLColAttributeString(
      StatementHandle: SqlHStmt;
      ColumnNumber: SqlUSmallint;
      FieldIdentifier: SqlUSmallint;
      CharacterAttribute: SqlPointer;
      BufferLength: SqlSmallint;
      var StringLength: SqlSmallint;
      NumericAttribute: SqlPointer
      ): SqlReturn;
    function SQLColAttributeInt(
      StatementHandle: SqlHStmt;
      ColumnNumber: SqlUSmallint;
      FieldIdentifier: SqlUSmallint;
      CharacterAttribute: SqlPointer;
      BufferLength: SqlSmallint;
      StringLength: pSqlSmallint;
      var NumericAttribute: SqlInteger
      ): SqlReturn;
    function SQLColumns(
      StatementHandle: SqlHStmt;
      CatalogName: PAnsiChar;
      NameLength1: SqlSmallint;
      SchemaName: PAnsiChar;
      NameLength2: SqlSmallint;
      TableName: PAnsiChar;
      NameLength3: SqlSmallint;
      ColumnName: PAnsiChar;
      NameLength4: SqlSmallint
      ): SqlReturn;
    function SQLConnect(
      ConnectionHandle: SqlHDbc;
      ServerName: PAnsiChar;
      NameLength1: SqlSmallint;
      UserName: PAnsiChar;
      NameLength2: SqlSmallint;
      Authentication: PAnsiChar;
      NameLength3: SqlSmallint
      ): SqlReturn;
    function SQLCopyDesc(
      SourceDescHandle: SqlHDesc;
      TargetDescHandle: SqlHDesc
      ): SqlReturn;
    function SQLDataSources(
      EnvironmentHandle: SqlHEnv;
      Direction: SqlUSmallint;
      var ServerName: SqlChar;
      BufferLength1: SqlSmallint;
      var NameLength1: SqlSmallint;
      var Description: SqlChar;
      BufferLength2: SqlSmallint;
      var NameLength2: SqlSmallint
      ): SqlReturn;
    function SQLDescribeCol(
      StatementHandle: SqlHStmt;
      ColumnNumber: SqlUSmallint;
      ColumnName: PAnsiChar;
      BufferLength: SqlSmallint;
      var NameLength: SqlSmallint;
      var DataType: SqlSmallint;
      var ColumnSize: SqlUInteger;
      var DecimalDigits: SqlSmallint;
      var Nullable: SqlSmallint
      ): SqlReturn;
    function SQLDisconnect(
      ConnectionHandle: SqlHDbc
      ): SqlReturn;
    function SQLEndTran(
      HandleType: SqlSmallint;
      Handle: SqlHandle;
      CompletionType: SqlSmallint
      ): SqlReturn;
    function SQLError(
      EnvironmentHandle: SqlHEnv;
      ConnectionHandle: SqlHDbc;
      StatementHandle: SqlHStmt;
      var Sqlstate: SqlChar;
      var NativeError: SqlInteger;
      var MessageText: SqlChar;
      BufferLength: SqlSmallint;
      var TextLength: SqlSmallint
      ): SqlReturn;
    function SQLExecDirect(
      StatementHandle: SqlHStmt;
      StatementText: PAnsiChar;
      TextLength: SqlInteger
      ): SqlReturn;
    function SQLExecute(
      StatementHandle: SqlHStmt
      ): SqlReturn;
    function SQLFetch(
      StatementHandle: SqlHStmt
      ): SqlReturn;
    function SQLFetchScroll(
      StatementHandle: SqlHStmt;
      FetchOrientation: SqlSmallint;
      FetchOffset: SqlInteger
      ): SqlReturn;
    function SQLFreeConnect(
      ConnectionHandle: SqlHDbc
      ): SqlReturn;
    function SQLFreeEnv(
      EnvironmentHandle: SqlHEnv
      ): SqlReturn;
    function SQLFreeHandle(
      HandleType: SqlSmallint;
      Handle: SqlHandle
      ): SqlReturn;
    function SQLFreeStmt(
      StatementHandle: SqlHStmt;
      Option: SqlUSmallint
      ): SqlReturn;
    function SQLGetConnectAttr(
      ConnectionHandle: SqlHDbc;
      Attribute: SqlInteger;
      ValuePtr: SqlPointer;
      BufferLength: SqlInteger;
      pStringLength: PSqlInteger
      ): SqlReturn;
    function SQLGetConnectOption(
      ConnectionHandle: SqlHDbc;
      Option: SqlUSmallint;
      Value: SqlPointer
      ): SqlReturn;
    function SQLGetCursorName(
      StatementHandle: SqlHStmt;
      CursorName: PAnsiChar;
      BufferLength: SqlSmallint;
      var NameLength: SqlSmallint
      ): SqlReturn;
    function SQLGetData(
      StatementHandle: SqlHStmt;
      ColumnNumber: SqlUSmallint;
      TargetType: SqlSmallint;
      TargetValue: SqlPointer;
      BufferLength: SqlInteger;
      StrLen_or_Ind: PSqlInteger
      ): SqlReturn;
    function SQLGetDescField(
      DescriptorHandle: SqlHDesc;
      RecNumber: SqlSmallint;
      FieldIdentifier: SqlSmallint;
      Value: SqlPointer;
      BufferLength: SqlInteger;
      var StringLength: SqlInteger
      ): SqlReturn;
    function SQLGetDescRec(
      DescriptorHandle: SqlHDesc;
      RecNumber: SqlSmallint;
      var Name: SqlChar;
      BufferLength: SqlSmallint;
      var StringLength: SqlSmallint;
      var _Type: SqlSmallint;
      var SubType: SqlSmallint;
      var Length: SqlInteger;
      var Precision: SqlSmallint;
      var Scale: SqlSmallint;
      var Nullable: SqlSmallint
      ): SqlReturn;
    function SQLGetDiagField(
      HandleType: SqlSmallint;
      Handle: SqlHandle;
      RecNumber: SqlSmallint;
      DiagIdentifier: SqlSmallint;
      DiagInfo: SqlPointer;
      BufferLength: SqlSmallint;
      var StringLength: SqlSmallint
      ): SqlReturn;
    function SQLGetDiagRec(
      HandleType: SqlSmallint;
      Handle: SqlHandle;
      RecNumber: SqlSmallint;
      Sqlstate: PAnsiChar; // pointer to 5 character buffer
      var NativeError: SqlInteger;
      MessageText: PAnsiChar;
      BufferLength: SqlSmallint;
      var TextLength: SqlSmallint
      ): SqlReturn;
    function SQLGetEnvAttr(
      EnvironmentHandle: SqlHEnv;
      Attribute: SqlInteger;
      Value: SqlPointer;
      BufferLength: SqlInteger;
      var StringLength: SqlInteger
      ): SqlReturn;
    function SQLGetFunctions(
      ConnectionHandle: SqlHDbc;
      FunctionId: SqlUSmallint;
      var Supported: SqlUSmallint
      ): SqlReturn;
    function SQLGetInfo(
      ConnectionHandle: SqlHDbc;
      InfoType: SqlUSmallint;
      InfoValuePtr: SqlPointer;
      BufferLength: SqlSmallint;
      StringLengthPtr: SqlPointer
      ): SqlReturn;
    function SQLGetInfoString(
      ConnectionHandle: SqlHDbc;
      InfoType: SqlUSmallint;
      InfoValueString: PAnsiChar; // PWideChar when calling SQLGetInfoW
      BufferLength: SqlSmallint;
      var StringLength: SqlSmallint
      ): SqlReturn;
    function SQLGetInfoSmallint(
      ConnectionHandle: SqlHDbc;
      InfoType: SqlUSmallint;
      var InfoValue: SqlUSmallint;
      Ignored1: SqlSmallint;
      Ignored2: Pointer
      ): SqlReturn;
    function SQLGetInfoInt(
      ConnectionHandle: SqlHDbc;
      InfoType: SqlUSmallint;
      var InfoValue: SqlUInteger;
      Ignored1: SqlSmallint;
      Ignored2: Pointer
      ): SqlReturn;
    function SQLGetStmtAttr(
      StatementHandle: SqlHStmt;
      Attribute: SqlInteger;
      Value: SqlPointer;
      BufferLength: SqlInteger;
      StringLength: PSqlInteger
      ): SqlReturn;
    function SQLGetStmtOption(
      StatementHandle: SqlHStmt;
      Option: SqlUSmallint;
      Value: SqlPointer
      ): SqlReturn;
    function SQLGetTypeInfo(
      StatementHandle: SqlHStmt;
      DataType: SqlSmallint
      ): SqlReturn;
    function SQLNumResultCols(
      StatementHandle: SqlHStmt;
      var ColumnCount: SqlSmallint
      ): SqlReturn;
    function SQLParamData(
      StatementHandle: SqlHStmt;
      var Value: SqlPointer
      ): SqlReturn;
    function SQLPrepare(
      StatementHandle: SqlHStmt;
      StatementText: PAnsiChar;
      TextLength: SqlInteger
      ): SqlReturn;
    function SQLPutData(
      StatementHandle: SqlHStmt;
      Data: SqlPointer;
      StrLen_or_Ind: SqlInteger
      ): SqlReturn;
    function SQLRowCount(
      StatementHandle: SqlHStmt;
      var RowCount: SqlInteger
      ): SqlReturn;
    function SQLSetConnectAttr(
      ConnectionHandle: SqlHDbc;
      Attribute: SqlInteger;
      ValuePtr: SqlPointer;
      StringLength: SqlInteger
      ): SqlReturn;
    function SQLSetConnectOption(
      ConnectionHandle: SqlHDbc;
      Option: SqlUSmallint;
      Value: SqlUInteger
      ): SqlReturn;
    function SQLSetCursorName(
      StatementHandle: SqlHStmt;
      CursorName: PAnsiChar;
      NameLength: SqlSmallint
      ): SqlReturn;
    function SQLSetDescField(
      DescriptorHandle: SqlHDesc;
      RecNumber: SqlSmallint;
      FieldIdentifier: SqlSmallint;
      Value: SqlPointer;
      BufferLength: SqlInteger
      ): SqlReturn;
    function SQLSetDescRec(
      DescriptorHandle: SqlHDesc;
      RecNumber: SqlSmallint;
      _Type: SqlSmallint;
      SubType: SqlSmallint;
      Length: SqlInteger;
      Precision: SqlSmallint;
      Scale: SqlSmallint;
      Data: SqlPointer;
      var StringLength: SqlInteger;
      var Indicator: SqlInteger
      ): SqlReturn;
    function SQLSetEnvAttr(
      EnvironmentHandle: SqlHEnv;
      Attribute: SqlInteger;
      ValuePtr: Pointer;
      StringLength: SqlInteger
      ): SqlReturn;
    function SQLSetParam(
      StatementHandle: SqlHStmt;
      ParameterNumber: SqlUSmallint;
      ValueType: SqlSmallint;
      ParameterType: SqlSmallint;
      LengthPrecision: SqlUInteger;
      ParameterScale: SqlSmallint;
      ParameterValue: SqlPointer;
      var StrLen_or_Ind: SqlInteger
      ): SqlReturn;
    function SQLSetStmtAttr(
      StatementHandle: SqlHStmt;
      Attribute: SqlInteger;
      Value: SqlPointer;
      StringLength: SqlInteger
      ): SqlReturn;
    function SQLSetStmtOption(
      StatementHandle: SqlHStmt;
      Option: SqlUSmallint;
      Value: SqlUInteger
      ): SqlReturn;
    function SQLSpecialColumns(
      StatementHandle: SqlHStmt;
      IdentifierType: SqlUSmallint;
      CatalogName: PAnsiChar;
      NameLength1: SqlSmallint;
      SchemaName: PAnsiChar;
      NameLength2: SqlSmallint;
      TableName: PAnsiChar;
      NameLength3: SqlSmallint;
      Scope: SqlUSmallint;
      Nullable: SqlUSmallint
      ): SqlReturn;
    function SQLStatistics(
      StatementHandle: SqlHStmt;
      CatalogName: PAnsiChar;
      NameLength1: SqlSmallint;
      SchemaName: PAnsiChar;
      NameLength2: SqlSmallint;
      TableName: PAnsiChar;
      NameLength3: SqlSmallint;
      Unique: SqlUSmallint;
      Reserved: SqlUSmallint
      ): SqlReturn;
    function SQLTables(
      StatementHandle: SqlHStmt;
      CatalogName: PAnsiChar;
      NameLength1: SqlSmallint;
      SchemaName: PAnsiChar;
      NameLength2: SqlSmallint;
      TableName: PAnsiChar;
      NameLength3: SqlSmallint;
      TableType: PAnsiChar;
      NameLength4: SqlSmallint
      ): SqlReturn;
    function SQLTransact(
      EnvironmentHandle: SqlHEnv;
      ConnectionHandle: SqlHDbc;
      CompletionType: SqlUSmallint
      ): SqlReturn;
    // sqlext.h
    function SQLDriverConnect(
      HDbc: SqlHDbc;
      hwnd: SqlHWnd;
      szConnStrIn: PAnsiChar;
      cbConnStrIn: SqlSmallint;
      szConnStrOut: PAnsiChar;
      cbConnStrOutMax: SqlSmallint;
      var pcbConnStrOut: SqlSmallint;
      fDriverCompletion: SqlUSmallint
      ): SqlReturn;
    function SQLBrowseConnect(
      HDbc: SqlHDbc;
      var szConnStrIn: SqlChar;
      cbConnStrIn: SqlSmallint;
      var szConnStrOut: SqlChar;
      cbConnStrOutMax: SqlSmallint;
      var pcbConnStrOut: SqlSmallint
      ): SqlReturn;
    function SQLBulkOperations(
      StatementHandle: SqlHStmt;
      Operation: SqlSmallint
      ): SqlReturn;
    function SQLColAttributes(
      HStmt: SqlHStmt;
      icol: SqlUSmallint;
      fDescType: SqlUSmallint;
      rgbDesc: SqlPointer;
      cbDescMax: SqlSmallint;
      var pcbDesc: SqlSmallint;
      var pfDesc: SqlInteger
      ): SqlReturn;
    function SQLColumnPrivileges(
      HStmt: SqlHStmt;
      var szCatalogName: SqlChar;
      cbCatalogName: SqlSmallint;
      var szSchemaName: SqlChar;
      cbSchemaName: SqlSmallint;
      var szTableName: SqlChar;
      cbTableName: SqlSmallint;
      var szColumnName: SqlChar;
      cbColumnName: SqlSmallint
      ): SqlReturn;
    function SQLDescribeParam(
      HStmt: SqlHStmt;
      ipar: SqlUSmallint;
      var pfSqlType: SqlSmallint;
      var pcbParamDef: SqlUInteger;
      var pibScale: SqlSmallint;
      var pfNullable: SqlSmallint
      ): SqlReturn;
    function SQLExtendedFetch(
      HStmt: SqlHStmt;
      fFetchType: SqlUSmallint;
      irow: SqlInteger;
      var pcrow: SqlUInteger;
      var rgfRowStatus: SqlUSmallint
      ): SqlReturn;
    function SQLForeignKeys(
      HStmt: SqlHStmt;
      var szPkCatalogName: SqlChar;
      cbPkCatalogName: SqlSmallint;
      var szPkSchemaName: SqlChar;
      cbPkSchemaName: SqlSmallint;
      var szPkTableName: SqlChar;
      cbPkTableName: SqlSmallint;
      var szFkCatalogName: SqlChar;
      cbFkCatalogName: SqlSmallint;
      var szFkSchemaName: SqlChar;
      cbFkSchemaName: SqlSmallint;
      var szFkTableName: SqlChar;
      cbFkTableName: SqlSmallint
      ): SqlReturn;
    function SQLMoreResults(
      HStmt: SqlHStmt
      ): SqlReturn;
    function SQLNativeSql(
      HDbc: SqlHDbc;
      var szSqlStrIn: SqlChar;
      cbSqlStrIn: SqlInteger;
      var szSqlStr: SqlChar;
      cbSqlStrMax: SqlInteger;
      var pcbSqlStr: SqlInteger
      ): SqlReturn;
    function SQLNumParams(
      HStmt: SqlHStmt;
      var pcpar: SqlSmallint
      ): SqlReturn;
    function SQLParamOptions(
      HStmt: SqlHStmt;
      crow: SqlUInteger;
      var pirow: SqlUInteger
      ): SqlReturn;
    function SQLPrimaryKeys(
      HStmt: SqlHStmt;
      szCatalogName: PAnsiChar;
      cbCatalogName: SqlSmallint;
      szSchemaName: PAnsiChar;
      cbSchemaName: SqlSmallint;
      szTableName: PAnsiChar;
      cbTableName: SqlSmallint
      ): SqlReturn;
    function SQLProcedureColumns(
      HStmt: SqlHStmt;
      szCatalogName: PAnsiChar;
      cbCatalogName: SqlSmallint;
      szSchemaName: PAnsiChar;
      cbSchemaName: SqlSmallint;
      szProcName: PAnsiChar;
      cbProcName: SqlSmallint;
      szColumnName: PAnsiChar;
      cbColumnName: SqlSmallint
      ): SqlReturn;
    function SQLProcedures(
      HStmt: SqlHStmt;
      szCatalogName: PAnsiChar;
      cbCatalogName: SqlSmallint;
      szSchemaName: PAnsiChar;
      cbSchemaName: SqlSmallint;
      szProcName: PAnsiChar;
      cbProcName: SqlSmallint
      ): SqlReturn;
    function SQLSetPos(
      HStmt: SqlHStmt;
      irow: SqlUSmallint;
      fOption: SqlUSmallint;
      fLock: SqlUSmallint
      ): SqlReturn;
    function SQLTablePrivileges(
      HStmt: SqlHStmt;
      var szCatalogName: SqlChar;
      cbCatalogName: SqlSmallint;
      var szSchemaName: SqlChar;
      cbSchemaName: SqlSmallint;
      var szTableName: SqlChar;
      cbTableName: SqlSmallint
      ): SqlReturn;
    function SQLDrivers(
      HEnv: SqlHEnv;
      fDirection: SqlUSmallint;
      szDriverDesc: PAnsiChar;
      cbDriverDescMax: SqlSmallint;
      var pcbDriverDesc: SqlSmallint;
      szDriverAttributes: PAnsiChar;
      cbDrvrAttrMax: SqlSmallint;
      var pcbDrvrAttr: SqlSmallint
      ): SqlReturn;
    function SQLBindParameter(
      HStmt: SqlHStmt;
      ipar: SqlUSmallint;
      fParamType: SqlSmallint;
      fCType: SqlSmallint;
      fSqlType: SqlSmallint;
      cbColDef: SqlUInteger;
      ibScale: SqlSmallint;
      rgbValue: SqlPointer;
      cbValueMax: SqlInteger;
      pcbValue: PSqlInteger
      ): SqlReturn;
    function SQLAllocHandleStd(
      fHandleType: SqlSmallint;
      hInput: SqlHandle;
      var phOutput: SqlHandle
      ): SqlReturn;
    function SQLSetScrollOptions( // Use SQLSetStmtOptions
      HStmt: SqlHStmt;
      fConcurrency: SqlUSmallint;
      crowKeyset: SqlInteger;
      crowRowset: SqlUSmallint
      ): SqlReturn;
    //ODBCTRAC
    function TraceOpenLogFile(
      var _1: WideChar;
      var _2: WideChar;
      _3: Longint
      ): Retcode;
    function TraceCloseLogFile: Retcode;
    procedure TraceReturn(
      _1: Retcode;
      _2: Retcode);
    function TraceVersion: Longint;
    function TraceVSControl(_1: Longint): Retcode;
    procedure FireVSDebugEvent(var Args: ODBC_VS_ARGS);
    //ODBCINST
    function ODBCSetTryWaitValue(dwValue: Longint): LongBool;
    function ODBCGetTryWaitValue: Longint;
  end;

{$ENDIF IFDEF _iOdbcApi_}

function LoadOdbcDriverManager(LibraryName: PChar): TOdbcApiProxy;
procedure UnLoadOdbcDriverManager(OdbcApi: TOdbcApiProxy);

// Extensions to ODBC API:

const
  // IBM DB2 extensions to ODBC API:
    SQL_IBMDB2_LONGDATA_COMPAT = 1253;
    SQL_IBMDB2_LD_COMPAT_NO = 0;
    SQL_IBMDB2_LD_COMPAT_YES = 1;

  // INFORMIX extensions to ODBC API (see in INFORMIX CLIENT SDK: "INFXCLI.H"):

    // For extended errors:

    SQL_INFX_ADIAG_ISAM_ERROR = 13;
    SQL_INFX_ADIAG_XA_ERROR   = 14;

    // Ajay added till here:
    //-----------------------------------------------------------------------
    { START -- Q+E Software's SQLSetStmtOption extensions (1040 to 1139)
      defines here for backwards compatibility: }
    SQL_INFX_STMTOPT_START = 1040;
    // Get the rowid for the last row inserted:
    SQL_INFX_GET_ROWID = (SQL_INFX_STMTOPT_START+8);
    // Get the value for the serial column in the last row inserted:
    SQL_INFX_GET_SERIAL_VALUE = (SQL_INFX_STMTOPT_START+9);
    { END -- Q+E Software's SQLSetStmtOption extensions (1040 to 1139) }
    //-----------------------------------------------------------------------

    //    Informix extensions:

    // Informix Column Attributes Flags Definitions:
    INFX_FDNULLABLE     = $0001; // null allowed in field
    INFX_FDDISTINCT     = $0002; // distinct of all
    INFX_FDDISTLVARCHAR = $0004; // distinct of SQLLVARCHAR
    INFX_FDDISTBOOLEAN  = $0008; // distinct of SQLBOOL
    INFX_FDDISTSIMP     = $0010; // distinct of simple type
    INFX_FDCSTTYPE      = $0020; // constructor type
    INFX_FDNAMED        = $0040; // named row type

    //#define ISNULLABLE( flags ) ( flags & INFX_FDNULLABLE ? 1 : 0)
    //#define ISDISTINCT( flags ) ( flags & INFX_FDDISTINCT ? 1 : 0)

    // Informix Type Estensions:
    SQL_INFX_UDT_FIXED     = (-100);
    SQL_INFX_UDT_VARYING   = (-101);
    SQL_INFX_UDT_BLOB      = (-102);
    SQL_INFX_UDT_CLOB      = (-103);
    SQL_INFX_UDT_LVARCHAR  = (-104);
    SQL_INFX_RC_ROW        = (-105);
    SQL_INFX_RC_COLLECTION = (-106);
    SQL_INFX_RC_LIST       = (-107);
    SQL_INFX_RC_SET        = (-108);
    SQL_INFX_RC_MULTISET   = (-109);
    SQL_INFX_UNSUPPORTED   = (-110);

    // typedef void * HINFX_RC; // row & collection handle

    // Informix Connect Attributes Extensions:
    SQL_INFX_OPT_LONGID                  = 2251;
    SQL_INFX_ATTR_LONGID                 = SQL_INFX_OPT_LONGID;
    SQL_INFX_ATTR_LEAVE_TRAILING_SPACES  = 2252;
    SQL_INFX_ATTR_DEFAULT_UDT_FETCH_TYPE = 2253;
    SQL_INFX_ATTR_ENABLE_SCROLL_CURSORS  = 2254;
    SQL_INFX_ATTR_ENABLE_INSERT_CURSORS  = 2255;
    SQL_INFX_ATTR_OPTIMIZE_AUTOCOMMIT    = 2256;
    SQL_INFX_ATTR_ODBC_TYPES_ONLY        = 2257;
    SQL_INFX_ATTR_FETCH_BUFFER_SIZE      = 2258;
    SQL_INFX_ATTR_OPTOFC                 = 2259;
    SQL_INFX_ATTR_OPTMSG                 = 2260;
    SQL_INFX_ATTR_REPORT_KEYSET_CURSORS  = 2261;
    SQL_INFX_ATTR_LO_AUTOMATIC           = 2262;  // Report Standard ODBC Types" Can  be
      // placed in ODBC Connection String options: "ODTYP=1".
      // When SQL_INFX_ATTR_LO_AUTOMATIC = SQL_FALSE then ODBC Driver return the next
      // code for LOB fields: SQL_INFX_UDT_BLOB, SQL_INFX_UDT_CLOB, ...
      // Access is possible through old api: ifx_lo. For more details see:
      // http://www-3.ibm.com/software/data/informix/pubs/library/notes/relnotes/odb0331r31.htm
      // For "Data Direct Informix Wire Protocol ODBC Driver" informix LOB types mapped to standatd ODBC Types:
      // http://www.datadirect-technologies.com/download/docs/odbc64/ODBC64REF/Rinf_wp.html
    SQL_INFX_ATTR_AUTO_FREE              = 2263;
    SQL_INFX_ATTR_DEFERRED_PREPARE       = 2265;
    // Informix Descriptor Extensions:
    SQL_INFX_ATTR_FLAGS                   = 1900; // UDWORD
    SQL_INFX_ATTR_EXTENDED_TYPE_CODE      = 1901; // UDWORD
    SQL_INFX_ATTR_EXTENDED_TYPE_NAME      = 1902; // UCHAR ptr
    SQL_INFX_ATTR_EXTENDED_TYPE_OWNER     = 1903; // UCHAR ptr
    SQL_INFX_ATTR_EXTENDED_TYPE_ALIGNMENT = 1904; // UDWORD
    SQL_INFX_ATTR_SOURCE_TYPE_CODE        = 1905; // UDWORD

    // Informix Statement Attributes Extensions:
    SQL_INFX_VMB_CHAR_LEN               = 2325;
    SQL_INFX_ATTR_VMB_CHAR_LEN     = SQL_INFX_VMB_CHAR_LEN;
    SQL_INFX_ATTR_MAX_FET_ARR_SIZE = 2326;

    // Informix fOption, SQL_VMB_CHAR_LEN vParam:
    SQL_INFX_VMB_CHAR_EXACT    = 0;
    SQL_INFX_VMB_CHAR_ESTIMATE = 1;

    // Informix row/collection traversal constants:
    SQL_INFX_RC_NEXT     = 1;
    SQL_INFX_RC_PRIOR    = 2;
    SQL_INFX_RC_FIRST    = 3;
    SQL_INFX_RC_LAST     = 4;
    SQL_INFX_RC_ABSOLUTE = 5;
    SQL_INFX_RC_RELATIVE = 6;
    SQL_INFX_RC_CURRENT  = 7;

    {*******************************************************************************
     * Large Object (LO) related structures
     *
     * LO_SPEC: Large object spec structure
     * It is used for creating smartblobs. The user may examin and/or set certain
     * fields of LO_SPEC by using ifx_lo_spec[set|get]_* accessor functions.
     *
     * LO_PTR: Large object pointer structure
     * Identifies the LO and provides ancillary, security-related information.
     *
     * LO_STAT: Large object stat structure
     * It is used in querying attribtes of smartblobs. The user may examin fields
     * herein by using ifx_lo_stat[set|get]_* accessor functions.
     *
     * These structures are opaque to the user. Accessor functions are provided
     * for these structures.
     ******************************************************************************}

    // Informix GetInfo Extensions to obtain length of LO related structures:
    SQL_INFX_LO_SPEC_LENGTH = 2250; // UWORD
    SQL_INFX_LO_PTR_LENGTH  = 2251; // UWORD
    SQL_INFX_LO_STAT_LENGTH = 2252; // UWORD

    {******************************************************************************
     * LO Open flags: (see documentation for further explanation)
     *
     * INFX_LO_APPEND   - Positions the seek position to end-of-file + 1. By itself,
     *               it is equivalent to write only mode followed by a seek to the
     *               end of large object. Read opeartions will fail.
     *               You can OR the LO_APPEND flag with another access mode.
     * INFX_LO_WRONLY   - Only write operations are valid on the data.
     * INFX_LO_RDONLY   - Only read operations are valid on the data.
     * INFX_LO_RDWR     - Both read and write operations are valid on the data.
     *
     * INFX_LO_RANDOM   - If set overrides optimizer decision. Indicates that I/O is
     *               random and that the system should not read-ahead.
     * INFX_LO_SEQUENTIAL - If set overrides optimizer decision. Indicates that
     *               reads are sequential in either forward or reverse direction.
     *
     * INFX_LO_FORWARD  - Only used for sequential access. Indicates that the sequential
     *               access will be in a forward direction, i.e. from low offset
     *               to higher offset.
     * INFX_LO_REVERSE  - Only used for sequential access. Indicates that the sequential
     *               access will be in a reverse direction.
     *
     * INFX_LO_BUFFER   - If set overrides optimizer decision. I/O goes through the
     *               buffer pool.
     * INFX_LO_NOBUFFER - If set then I/O does not use the buffer pool.
     ******************************************************************************}

    INFX_LO_APPEND       = $1;
    INFX_LO_WRONLY       = $2;
    INFX_LO_RDONLY       = $4;     // default
    INFX_LO_RDWR         = $8;

    INFX_LO_RANDOM       = $20;    // default is determined by optimizer
    INFX_LO_SEQUENTIAL   = $40;    // default is determined by optimizer

    INFX_LO_FORWARD      = $80;    // default
    INFX_LO_REVERSE      = $100;

    INFX_LO_BUFFER       = $200;   // default is determined by optimizer
    INFX_LO_NOBUFFER     = $400;   // default is determined by optimizer

    INFX_LO_DIRTY_READ   = $10;
    INFX_LO_NODIRTY_READ = $800;

    {*******************************************************************************
     * LO create-time flags:
     *
     * Bitmask - Set/Get via ifx_lo_specset_flags() on LO_SPEC.
     ******************************************************************************}

    INFX_LO_ATTR_LOG                    = $01;
    INFX_LO_ATTR_NOLOG                  = $02;
    INFX_LO_ATTR_DELAY_LOG              = $04;
    INFX_LO_ATTR_KEEP_LASTACCESS_TIME   = $08;
    INFX_LO_ATTR_NOKEEP_LASTACCESS_TIME = $10;
    INFX_LO_ATTR_HIGH_INTEG             = $20;
    INFX_LO_ATTR_MODERATE_INTEG         = $40;

    {*******************************************************************************
     * Symbolic constants for the "lseek" routine
     ******************************************************************************}

    INFX_LO_SEEK_SET = 0;   // Set curr. pos. to "offset"
    INFX_LO_SEEK_CUR = 1;   // Set curr. pos. to current + "offset"
    INFX_LO_SEEK_END = 2;   // Set curr. pos. to EOF + "offset"

    {*******************************************************************************
     * Intersolv specific infoTypes for SQLGetInfo
     ******************************************************************************}

    SQL_INFX_RESERVED_WORDS           = 1011;
    SQL_INFX_PSEUDO_COLUMNS           = 11012;
    SQL_INFX_FROM_RESERVED_WORDS      = 11013;
    SQL_INFX_WHERE_CLAUSE_TERMINATORS = 11014;
    SQL_INFX_COLUMN_FIRST_CHARS       = 11015;
    SQL_INFX_COLUMN_MIDDLE_CHARS      = 11016;
    SQL_INFX_TABLE_FIRST_CHARS        = 11018;
    SQL_INFX_TABLE_MIDDLE_CHARS       = 11019;
    SQL_INFX_FAST_SPECIAL_COLUMNS     = 11021;
    SQL_INFX_ACCESS_CONFLICTS         = 11022;
    SQL_INFX_LOCKING_SYNTAX           = 11023;
    SQL_INFX_LOCKING_DURATION         = 11024;
    SQL_INFX_RECORD_OPERATIONS        = 11025;
    SQL_INFX_QUALIFIER_SYNTAX         = 11026;

  // MSSQL extensions to ODBC API:
    SQL_MSSQL_VARIANT = (-150); // map to SQL_VARCHAR/fldZSTRING

implementation

//##########################################################################
// sql.h implementation part starts here
//##########################################################################


{$IFNDEF LINUX}
uses
  Registry;
{$ENDIF}

const
{$IFDEF MSWINDOWS}
  ODBC32DLL = 'odbc32.dll';
{$ELSE}
  ODBC32DLL = 'libodbc.so';
{$ENDIF}

  // Macro: test for SQL_SUCCESS or SQL_SUCCESS_WITH_INFO

function SQL_SUCCEEDED(const rc: SqlReturn): Boolean;
begin
  Result := (rc and (not 1)) = 0;
end;

{$IFNDEF DynamicOdbcImport}

function SQLAllocConnect;
  {$IFDEF MSWINDOWS} stdcall{$ELSE} cdecl{$ENDIF}; external ODBC32DLL;

function SQLAllocEnv;
  {$IFDEF MSWINDOWS} stdcall{$ELSE} cdecl{$ENDIF}; external ODBC32DLL;

function SQLAllocHandle;
  {$IFDEF MSWINDOWS} stdcall{$ELSE} cdecl{$ENDIF}; external ODBC32DLL;

function SQLAllocStmt;
  {$IFDEF MSWINDOWS} stdcall{$ELSE} cdecl{$ENDIF}; external ODBC32DLL;

function SQLBindCol;
  {$IFDEF MSWINDOWS} stdcall{$ELSE} cdecl{$ENDIF}; external ODBC32DLL;

function SQLBindParam;
  {$IFDEF MSWINDOWS} stdcall{$ELSE} cdecl{$ENDIF}; external ODBC32DLL;

function SQLCancel;
  {$IFDEF MSWINDOWS} stdcall{$ELSE} cdecl{$ENDIF}; external ODBC32DLL;

function SQLCloseCursor;
  {$IFDEF MSWINDOWS} stdcall{$ELSE} cdecl{$ENDIF}; external ODBC32DLL;

// SQLColAttribute is overloaded
function SQLColAttribute;
  {$IFDEF MSWINDOWS} stdcall{$ELSE} cdecl{$ENDIF}; external ODBC32DLL;
function SQLColAttributeString;
  {$IFDEF MSWINDOWS} stdcall{$ELSE} cdecl{$ENDIF}; external ODBC32DLL name 'SQLColAttribute';
function SQLColAttributeInt;
  {$IFDEF MSWINDOWS} stdcall{$ELSE} cdecl{$ENDIF}; external ODBC32DLL name 'SQLColAttribute';

function SQLColumns;
  {$IFDEF MSWINDOWS} stdcall{$ELSE} cdecl{$ENDIF}; external ODBC32DLL;

function SQLConnect;
  {$IFDEF MSWINDOWS} stdcall{$ELSE} cdecl{$ENDIF}; external ODBC32DLL;

function SQLCopyDesc;
  {$IFDEF MSWINDOWS} stdcall{$ELSE} cdecl{$ENDIF}; external ODBC32DLL;

function SQLDataSources;
  {$IFDEF MSWINDOWS} stdcall{$ELSE} cdecl{$ENDIF}; external ODBC32DLL;

function SQLDescribeCol;
  {$IFDEF MSWINDOWS} stdcall{$ELSE} cdecl{$ENDIF}; external ODBC32DLL;

function SQLDisconnect;
  {$IFDEF MSWINDOWS} stdcall{$ELSE} cdecl{$ENDIF}; external ODBC32DLL;

function SQLEndTran;
  {$IFDEF MSWINDOWS} stdcall{$ELSE} cdecl{$ENDIF}; external ODBC32DLL;

function SQLError;
  {$IFDEF MSWINDOWS} stdcall{$ELSE} cdecl{$ENDIF}; external ODBC32DLL;

function SQLExecDirect;
  {$IFDEF MSWINDOWS} stdcall{$ELSE} cdecl{$ENDIF}; external ODBC32DLL;

function SQLExecute;
  {$IFDEF MSWINDOWS} stdcall{$ELSE} cdecl{$ENDIF}; external ODBC32DLL;

function SQLFetch;
  {$IFDEF MSWINDOWS} stdcall{$ELSE} cdecl{$ENDIF}; external ODBC32DLL;

function SQLFetchScroll;
  {$IFDEF MSWINDOWS} stdcall{$ELSE} cdecl{$ENDIF}; external ODBC32DLL;

function SQLFreeConnect;
  {$IFDEF MSWINDOWS} stdcall{$ELSE} cdecl{$ENDIF}; external ODBC32DLL;

function SQLFreeEnv;
  {$IFDEF MSWINDOWS} stdcall{$ELSE} cdecl{$ENDIF}; external ODBC32DLL;

function SQLFreeHandle;
  {$IFDEF MSWINDOWS} stdcall{$ELSE} cdecl{$ENDIF}; external ODBC32DLL;

function SQLFreeStmt;
  {$IFDEF MSWINDOWS} stdcall{$ELSE} cdecl{$ENDIF}; external ODBC32DLL;

function SQLGetConnectAttr;
  {$IFDEF MSWINDOWS} stdcall{$ELSE} cdecl{$ENDIF}; external ODBC32DLL;

function SQLGetConnectOption;
  {$IFDEF MSWINDOWS} stdcall{$ELSE} cdecl{$ENDIF}; external ODBC32DLL;

function SQLGetCursorName;
  {$IFDEF MSWINDOWS} stdcall{$ELSE} cdecl{$ENDIF}; external ODBC32DLL;

function SQLGetData;
  {$IFDEF MSWINDOWS} stdcall{$ELSE} cdecl{$ENDIF}; external ODBC32DLL;

function SQLGetDescField;
  {$IFDEF MSWINDOWS} stdcall{$ELSE} cdecl{$ENDIF}; external ODBC32DLL;

function SQLGetDescRec;
  {$IFDEF MSWINDOWS} stdcall{$ELSE} cdecl{$ENDIF}; external ODBC32DLL;

function SQLGetDiagField;
  {$IFDEF MSWINDOWS} stdcall{$ELSE} cdecl{$ENDIF}; external ODBC32DLL;

function SQLGetDiagRec;
  {$IFDEF MSWINDOWS} stdcall{$ELSE} cdecl{$ENDIF}; external ODBC32DLL;

function SQLGetEnvAttr;
  {$IFDEF MSWINDOWS} stdcall{$ELSE} cdecl{$ENDIF}; external ODBC32DLL;

function SQLGetFunctions;
  {$IFDEF MSWINDOWS} stdcall{$ELSE} cdecl{$ENDIF}; external ODBC32DLL;

// SQLGetInfo is overloaded
function SQLGetInfo;
  {$IFDEF MSWINDOWS} stdcall{$ELSE} cdecl{$ENDIF}; external ODBC32DLL;
function SQLGetInfoString;
  {$IFDEF MSWINDOWS} stdcall{$ELSE} cdecl{$ENDIF}; external ODBC32DLL name 'SQLGetInfo';
function SQLGetInfoSmallint;
//  {$IFDEF MSWINDOWS} stdcall{$ELSE} cdecl{$ENDIF}; external ODBC32DLL name 'SQLGetInfo';
begin
  Result := SQLGetInfo(ConnectionHandle,
    InfoType, @InfoValue,
    {Ignored1=}SizeOf(SqlUInteger), {Ignored2=}nil);
end;
function SQLGetInfoInt;
//  {$IFDEF MSWINDOWS} stdcall{$ELSE} cdecl{$ENDIF}; external ODBC32DLL name 'SQLGetInfo';
begin
  Result := SQLGetInfo(ConnectionHandle,
    InfoType, @InfoValue,
    {Ignored1=}SizeOf(SqlUSmallint), {Ignored2=}nil);
end;

function SQLGetStmtAttr;
  {$IFDEF MSWINDOWS} stdcall{$ELSE} cdecl{$ENDIF}; external ODBC32DLL;

function SQLGetStmtOption;
  {$IFDEF MSWINDOWS} stdcall{$ELSE} cdecl{$ENDIF}; external ODBC32DLL;

function SQLGetTypeInfo;
  {$IFDEF MSWINDOWS} stdcall{$ELSE} cdecl{$ENDIF}; external ODBC32DLL;

function SQLNumResultCols;
  {$IFDEF MSWINDOWS} stdcall{$ELSE} cdecl{$ENDIF}; external ODBC32DLL;

function SQLParamData;
  {$IFDEF MSWINDOWS} stdcall{$ELSE} cdecl{$ENDIF}; external ODBC32DLL;

function SQLPrepare;
  {$IFDEF MSWINDOWS} stdcall{$ELSE} cdecl{$ENDIF}; external ODBC32DLL;

function SQLPutData;
  {$IFDEF MSWINDOWS} stdcall{$ELSE} cdecl{$ENDIF}; external ODBC32DLL;

function SQLRowCount;
  {$IFDEF MSWINDOWS} stdcall{$ELSE} cdecl{$ENDIF}; external ODBC32DLL;

function SQLSetConnectAttr;
  {$IFDEF MSWINDOWS} stdcall{$ELSE} cdecl{$ENDIF}; external ODBC32DLL;

function SQLSetConnectOption;
  {$IFDEF MSWINDOWS} stdcall{$ELSE} cdecl{$ENDIF}; external ODBC32DLL;

function SQLSetCursorName;
  {$IFDEF MSWINDOWS} stdcall{$ELSE} cdecl{$ENDIF}; external ODBC32DLL;

function SQLSetDescField;
  {$IFDEF MSWINDOWS} stdcall{$ELSE} cdecl{$ENDIF}; external ODBC32DLL;

function SQLSetDescRec;
  {$IFDEF MSWINDOWS} stdcall{$ELSE} cdecl{$ENDIF}; external ODBC32DLL;

function SQLSetEnvAttr;
  {$IFDEF MSWINDOWS} stdcall{$ELSE} cdecl{$ENDIF}; external ODBC32DLL;

function SQLSetParam;
  {$IFDEF MSWINDOWS} stdcall{$ELSE} cdecl{$ENDIF}; external ODBC32DLL;

function SQLSetStmtAttr;
  {$IFDEF MSWINDOWS} stdcall{$ELSE} cdecl{$ENDIF}; external ODBC32DLL;

function SQLSetStmtOption;
  {$IFDEF MSWINDOWS} stdcall{$ELSE} cdecl{$ENDIF}; external ODBC32DLL;

function SQLSpecialColumns;
  {$IFDEF MSWINDOWS} stdcall{$ELSE} cdecl{$ENDIF}; external ODBC32DLL;

function SQLStatistics;
  {$IFDEF MSWINDOWS} stdcall{$ELSE} cdecl{$ENDIF}; external ODBC32DLL;

function SQLTables;
  {$IFDEF MSWINDOWS} stdcall{$ELSE} cdecl{$ENDIF}; external ODBC32DLL;

function SQLTransact;
  {$IFDEF MSWINDOWS} stdcall{$ELSE} cdecl{$ENDIF}; external ODBC32DLL;

{$ENDIF IFNDEF DynamicOdbcImport}

//##########################################################################
// sql.h implementation part ends here
//##########################################################################

//##########################################################################
// sqlext.h implementation part starts here
//##########################################################################

const
  ODBCTRAC = 'odbctrac.dll';
  ODBCINST = {$IFDEF MSWINDOWS} 'odbcinst.dll'{$ELSE} 'libodbcinst.so'{$ENDIF};

{$IFNDEF DynamicOdbcImport}

// MACROs

function SQL_LEN_DATA_AT_EXEC(length: Integer): Integer;
begin
  result := -(length) + SQL_LEN_DATA_AT_EXEC_OFFSET;
end;

function SQL_LEN_BINARY_ATTR(length: Integer): Integer;
begin
  result := -(length) + SQL_LEN_BINARY_ATTR_OFFSET;
end;

function SQL_FUNC_EXISTS(pfExists: PUWord; uwAPI: UWord): SqlInteger;
begin
  Inc(pfExists, uwAPI shr 4);
  if (pfExists^ and (1 shl (uwAPI and $000F))) <> 0 then
    result := SQL_TRUE
  else
    result := SQL_FALSE;
end;

function SQL_POSITION_TO(HStmt: SqlHStmt; irow: SqlUSmallint): SqlReturn;
begin
  result := SQLSetPos(HStmt, irow, SQL_POSITION, SQL_LOCK_NO_CHANGE);
end;

function SQL_LOCK_RECORD(HStmt: SqlHStmt; irow, fLock: SqlUSmallint): SqlReturn;
begin
  result := SQLSetPos(HStmt, irow, SQL_POSITION, fLock);
end;

function SQL_REFRESH_RECORD(HStmt: SqlHStmt; irow, fLock: SqlUSmallint): SqlReturn;
begin
  result := SQLSetPos(HStmt, irow, SQL_REFRESH, fLock);
end;

function SQL_UPDATE_RECORD(HStmt: SqlHStmt; irow: SqlUSmallint): SqlReturn;
begin
  result := SQLSetPos(HStmt, irow, SQL_UPDATE, SQL_LOCK_NO_CHANGE);
end;

function SQL_DELETE_RECORD(HStmt: SqlHStmt; irow: SqlUSmallint): SqlReturn;
begin
  result := SQLSetPos(HStmt, irow, SQL_DELETE, SQL_LOCK_NO_CHANGE);
end;

function SQL_ADD_RECORD(HStmt: SqlHStmt; irow: SqlUSmallint): SqlReturn;
begin
  result := SQLSetPos(HStmt, irow, SQL_ADD, SQL_LOCK_NO_CHANGE);
end;

function SQLFunctionSupported(ConnectionHandle: SqlHDbc; FunctionId: SqlUSmallint): Boolean;
var
  vSupported: SqlUSmallint;
begin
  if SQLGetFunctions(ConnectionHandle, FunctionId, vSupported) = SQL_SUCCESS then
    Result := vSupported = SQL_TRUE
  else
    Result := False;
end;

{$ENDIF IFNDEF DynamicOdbcImport}

{$IFNDEF DynamicOdbcImport}

function SQLAllocHandleStd;
  {$IFDEF MSWINDOWS} stdcall{$ELSE} cdecl{$ENDIF}; external ODBC32DLL;

function SQLBindParameter;
  {$IFDEF MSWINDOWS} stdcall{$ELSE} cdecl{$ENDIF}; external ODBC32DLL;

function SQLBrowseConnect;
  {$IFDEF MSWINDOWS} stdcall{$ELSE} cdecl{$ENDIF}; external ODBC32DLL;

function SQLBulkOperations;
  {$IFDEF MSWINDOWS} stdcall{$ELSE} cdecl{$ENDIF}; external ODBC32DLL;

function SQLColAttributes;
  {$IFDEF MSWINDOWS} stdcall{$ELSE} cdecl{$ENDIF}; external ODBC32DLL;

function SQLColumnPrivileges;
  {$IFDEF MSWINDOWS} stdcall{$ELSE} cdecl{$ENDIF}; external ODBC32DLL;

function SQLDescribeParam;
  {$IFDEF MSWINDOWS} stdcall{$ELSE} cdecl{$ENDIF}; external ODBC32DLL;

function SQLDriverConnect;
  {$IFDEF MSWINDOWS} stdcall{$ELSE} cdecl{$ENDIF}; external ODBC32DLL;

function SQLDrivers;
  {$IFDEF MSWINDOWS} stdcall{$ELSE} cdecl{$ENDIF}; external ODBC32DLL;

function SQLExtendedFetch;
  {$IFDEF MSWINDOWS} stdcall{$ELSE} cdecl{$ENDIF}; external ODBC32DLL;

function SQLForeignKeys;
  {$IFDEF MSWINDOWS} stdcall{$ELSE} cdecl{$ENDIF}; external ODBC32DLL;

function SQLMoreResults;
  {$IFDEF MSWINDOWS} stdcall{$ELSE} cdecl{$ENDIF}; external ODBC32DLL;

function SQLNativeSql;
  {$IFDEF MSWINDOWS} stdcall{$ELSE} cdecl{$ENDIF}; external ODBC32DLL;

function SQLNumParams;
  {$IFDEF MSWINDOWS} stdcall{$ELSE} cdecl{$ENDIF}; external ODBC32DLL;

function SQLParamOptions;
  {$IFDEF MSWINDOWS} stdcall{$ELSE} cdecl{$ENDIF}; external ODBC32DLL;

function SQLPrimaryKeys;
  {$IFDEF MSWINDOWS} stdcall{$ELSE} cdecl{$ENDIF}; external ODBC32DLL;

function SQLProcedureColumns;
  {$IFDEF MSWINDOWS} stdcall{$ELSE} cdecl{$ENDIF}; external ODBC32DLL;

function SQLProcedures;
  {$IFDEF MSWINDOWS} stdcall{$ELSE} cdecl{$ENDIF}; external ODBC32DLL;

function SQLSetPos;
  {$IFDEF MSWINDOWS} stdcall{$ELSE} cdecl{$ENDIF}; external ODBC32DLL;

function SQLSetScrollOptions;
  {$IFDEF MSWINDOWS} stdcall{$ELSE} cdecl{$ENDIF}; external ODBC32DLL;

function SQLTablePrivileges;
  {$IFDEF MSWINDOWS} stdcall{$ELSE} cdecl{$ENDIF}; external ODBC32DLL;

function TraceOpenLogFile;
  {$IFDEF MSWINDOWS} stdcall{$ELSE} cdecl{$ENDIF}; external ODBCTRAC;

function TraceCloseLogFile;
  {$IFDEF MSWINDOWS} stdcall{$ELSE} cdecl{$ENDIF}; external ODBCTRAC;

procedure TraceReturn;
  {$IFDEF MSWINDOWS} stdcall{$ELSE} cdecl{$ENDIF}; external ODBCTRAC;

function TraceVersion;
  {$IFDEF MSWINDOWS} stdcall{$ELSE} cdecl{$ENDIF}; external ODBCTRAC;

function TraceVSControl;
  {$IFDEF MSWINDOWS} stdcall{$ELSE} cdecl{$ENDIF}; external ODBCTRAC;

procedure FireVSDebugEvent;
  {$IFDEF MSWINDOWS} stdcall{$ELSE} cdecl{$ENDIF}; external ODBCTRAC;

function ODBCGetTryWaitValue;
  {$IFDEF MSWINDOWS} stdcall{$ELSE} cdecl{$ENDIF}; external ODBCINST;

function ODBCSetTryWaitValue;
  {$IFDEF MSWINDOWS} stdcall{$ELSE} cdecl{$ENDIF}; external ODBCINST;

{$ENDIF IFNDEF DynamicOdbcImport}

//##########################################################################
// sqlext.h implementation part ends here
//##########################################################################

{$IFNDEF DynamicOdbcImport}
var
  fOdbcApi: TOdbcApiProxy;

function LoadOdbcDriverManager(LibraryName: PChar): TOdbcApiProxy;
begin
  Result := fOdbcApi;
  InterlockedIncrement(fOdbcApi.fApiRefCount);
end;

procedure UnLoadOdbcDriverManager;
begin
  InterlockedDecrement(fOdbcApi.fApiRefCount);
end;

{ TOdbcApiProxy }

constructor TOdbcApiProxy.Create;
begin
  inherited;
  fSystemODBCManager := True;
  fOdbcDriverLevel := -1;
  fLockObj := TCriticalSection.Create;
end;

destructor TOdbcApiProxy.Destroy;
begin
  {$IFDEF _iOdbcApi_}
  if Assigned(fOdbcApiImpl) then
  begin
    fOdbcApiImpl.fOdbcApiProxy := nil;
    fOdbcApiImpl := nil;
    fOdbcApiIntf := nil; // _Release
  end;
  {$ENDIF}
  fLockObj.Free;
  inherited Destroy;
end;

procedure TOdbcApiProxy.BeginLock;
begin
  fLockObj.Acquire;
end;

procedure TOdbcApiProxy.EndLock;
begin
  fLockObj.Release;
end;

{$ELSE IFNDEF DynamicOdbcImport}

type

{ TStringHash }

  PPHashItem = ^PHashItem;
  PHashItem = ^THashItem;
  THashItem = record
    Next: PHashItem;
    Key: string;
    Value: TObject;
  end;

  TStringHash = class
  private
    fBuckets: array of PHashItem;
    fLockObj: TCriticalSection;
  protected
    function Find(const Key: string): PPHashItem;
    function HashOf(const Key: string): Cardinal; virtual;
  public
    constructor Create(Size: Cardinal = 64);
    destructor Destroy; override;
    procedure BeginLock;
    procedure EndLock;
    function Add(const Key: string; Value: TObject): PHashItem;
    procedure Clear(bDestroyValues: Boolean = True);
    procedure Remove(const Key: string; bDestroyValues: Boolean = True); overload;
    function ValueOf(const Key: string): TObject; overload;
  end;

constructor TStringHash.Create(Size: Cardinal);
begin
  inherited Create;
  SetLength(fBuckets, Size);
  fLockObj := TCriticalSection.Create;
end;

destructor TStringHash.Destroy;
begin
  Clear(True);
  fLockObj.Free;
  inherited Destroy;
end;

procedure TStringHash.Clear(bDestroyValues: Boolean = True);
var
  I: Integer;
  P, N: PHashItem;
begin
  for I := 0 to Length(fBuckets) - 1 do
  begin
    P := fBuckets[I];
    while P <> nil do
    begin
      N := P^.Next;
      if bDestroyValues and Assigned(P.Value) then
        FreeAndNil(P.Value);
      Dispose(P);
      P := N;
    end;
    fBuckets[I] := nil;
  end;
end;

function TStringHash.HashOf(const Key: string): Cardinal;
var
  I: Integer;
begin
  Result := 0;
  for I := 1 to Length(Key) do
    Result := ((Result shl 2) or (Result shr (SizeOf(Result) * 8 - 2))) xor
      Ord(Key[I]);
end;

function TStringHash.Add(const Key: string; Value: TObject): PHashItem;
var
  Hash: Integer;
  Bucket: PHashItem;
begin
  Hash := HashOf(Key) mod Cardinal(Length(fBuckets));
  New(Bucket);
  Bucket^.Key := Key;
  Bucket^.Value := Value;
  Bucket^.Next := fBuckets[Hash];
  fBuckets[Hash] := Bucket;

  Result := Bucket;
end;

procedure TStringHash.Remove(const Key: string; bDestroyValues: Boolean = True);
var
  P: PHashItem;
  Prev: PPHashItem;
begin
  Prev := Find(Key);
  P := Prev^;
  if P <> nil then
  begin
    Prev^ := P^.Next;
    if bDestroyValues and Assigned(P.Value) then
      FreeAndNil(P.Value);
    Dispose(P);
  end;
end;

function TStringHash.ValueOf(const Key: string): TObject;
var
  P: PHashItem;
begin
  P := Find(Key)^;
  if P <> nil then
    Result := P^.Value
  else
    Result := nil;
end;

function TStringHash.Find(const Key: string): PPHashItem;
var
  Hash: Integer;
begin
  Hash := HashOf(Key) mod Cardinal(Length(fBuckets));
  Result := @fBuckets[Hash];
  while Result^ <> nil do
  begin
    if Result^.Key = Key then
      Exit
    else
      Result := @Result^.Next;
  end;
end;

procedure TStringHash.BeginLock;
begin
  fLockObj.Acquire;
end;

procedure TStringHash.EndLock;
begin
  fLockObj.Release;
end;

var
  fOdbcApiCache: TStringHash;

{
  LibraryName format: [SqlAttrOdbcVersion:][LibraryPath]OdbcDriverLibraryName

  examples:
    'odbc32.dll'
    '2:odbc32.dll'
    '1:odbc32.dll'
    '2:OT2K_32.DLL'
    '2:C:\TEST\OTERRO\ODBC\OT2K_32.DLL'
}

function LoadOdbcDriverManager(LibraryName: PChar): TOdbcApiProxy;
var
  sLibNames, sLib: string;
  iPos, iLengthLibNames, iTmp: integer;
  vHModule: HMODULE;
  {$IFNDEF LINUX}
  sBuff, sEnv: string;
  iLenBuff: integer;
  {$ENDIF}
  //iLastOSError: integer;
  //Error: EOSError;
  vOdbcDriverLevel: integer;
const
  cLibsSeparator = ';';
  cSqlAttrOdbcVerSeparator = ':';

  function ExtractNextLibName: string;
  var
    i: integer;
  begin
    i := iPos;
    while ( (i <= iLengthLibNames) and (sLibNames[i] <> cLibsSeparator) ) do
      inc(i);
    Result := LowerCase(Trim(Copy(sLibNames, iPos, i - iPos)));
    if ( (i <= iLengthLibNames) and (sLibNames[i] = cLibsSeparator) ) then
      inc(i);
    iPos := i;
  end;

  function GetProcAddressEx(Module: HMODULE; const sProcName: String; PtrA: PPointer;
    PtrW: PPointer = nil): Boolean;
  begin
    PtrA^ := GetProcAddress(Module, PChar(sProcName));
    if Assigned(PtrW) then
      PtrW^ := GetProcAddress(Module, PChar(sProcName+'W'));
    Result := Assigned(PtrA^) or (Assigned(PtrW) and Assigned(PtrW^));
  end;

begin
  Result := nil;
  sLibNames := Trim(StrPas(LibraryName));
  if sLibNames = '' then
    //raise EOdbcApi.Create('Not defined Api Library.');
    sLibNames := ODBC32DLL;
  vHModule := 0;
  //iLastOSError := 0;
  vOdbcDriverLevel := -1;
  fOdbcApiCache.BeginLock;
  try
    {
     Alternative API LIBs.
      Example for INFORMIX:
        'ICLIT09B.DLL;ICLIT09A.DLL;ICLIT09BW.DLL;ICLIT09AW.DLL'
    }
    iLengthLibNames := Length(sLibNames);
    vHModule := 0;
    iPos := 1;
    repeat
      sLib := ExtractNextLibName;
      if sLib = '' then
        continue;
      Result := TOdbcApiProxy(fOdbcApiCache.ValueOf(sLib));
      if Result <> nil then
      begin
        inc(Result.fApiRefCount);
        exit;
      end;

      // read odbc SQL_ATTR_ODBC_VERSION
      iTmp := Pos(cSqlAttrOdbcVerSeparator, sLib);
      if (iTmp > 0) and (iTmp < Length(sLib)) then
      begin
        vOdbcDriverLevel := StrToIntDef(Copy(sLib, 1, iTmp-1), -1);
        if vOdbcDriverLevel > 0 then
          sLib := Copy(sLib, iTmp+1, Length(sLib)-iTmp)
        else
          vOdbcDriverLevel := -1;
      end
      else
        vOdbcDriverLevel := -1;

      {$IFNDEF LINUX}
       sEnv := LowerCase(ExtractFilePath(sLib));
       if sEnv = '.' then
         sEnv := '';
       if (sEnv <> '') and (sEnv[Length(sEnv)]='\') then
         SetLength(sEnv, Length(sEnv)-1);
       if (Win32Platform = VER_PLATFORM_WIN32_NT) // Windows Me/98/95:  GetEnvironmentVariableW is supported by the Microsoft Layer for Unicode.
         and (sEnv <> '')
       then
       begin
         SetLength(sBuff, 32767);
         iLenBuff := GetEnvironmentVariable('PATH', PAnsiChar(sBuff), Length(sBuff));
         if iLenBuff > 0 then
         begin
           SetLength(sBuff, iLenBuff);
           sBuff := LowerCase(sBuff);
           if pos(sEnv, sBuff) <= 0 then
           begin
             sBuff := sEnv + ';' + sBuff;

             // For Idapi Driver 'PBIDP13.DLL' need add path to BDE library 'idapi32.dll'.
             sEnv := ExtractFileName(sLib);
             if (Length(sEnv)>9) and
               (StrLComp(PAnsiChar(sEnv), 'pbidp', 5) = 0) and ( ExtractFileExt(sEnv) = '.dll')
               and ( StrToIntDef( Copy(sEnv, 6, Length(sEnv)-5-4), -1) > 0 ) then
             begin
               with TRegistry.Create(KEY_READ) do
               begin
                 try
                   RootKey := HKEY_LOCAL_MACHINE;
                   if OpenKey('SOFTWARE\Borland\Database Engine', False) and
                     ValueExists('DLLPATH') then
                   begin
                     sEnv := ReadString('DLLPATH');
                     if (sEnv<>'') and (sEnv[Length(sEnv)]='\') then
                       SetLength(sEnv, Length(sEnv)-1);
                     if sEnv <> '' then
                     begin
                       if (Pos(LowerCase(sEnv)+#1, sBuff+#1)=0)
                         and (Pos(LowerCase(sEnv)+';', sBuff+';')=0)
                         and (Pos(LowerCase(sEnv)+'\.', sBuff+'\.')=0)
                       then
                         sBuff := sBuff + ';' + sEnv;
                     end;
                   end;
                   CloseKey;
                 finally
                   Free;
                 end;
               end;
             end;
             SetEnvironmentVariable('PATH', PAnsiChar(sBuff));
           end;
         end;
       end;
      {$ENDIF}
      //SetLastError(0);
      vHModule := SafeLoadLibrary(sLib);
      if vHModule <> 0 then
      begin
        {iLastOSError := GetLastError();
        if iLastOSError <> 0 then
        begin
          FreeLibrary(vHModule);
          vHModule := 0;
        end
        else{}
        begin
          //iLastOSError := 0;
          break;
        end;
      end;
    until iPos > iLengthLibNames;


    // Check LastOSError: It is necessary in those cases when the driver is installed incorrectly.
    {if iLastOSError <> 0 then
    begin
      Error := EOSError.CreateResFmt(@SOSError, [iLastOSError,
        SysErrorMessage(iLastOSError)]);
      Error.ErrorCode := iLastOSError;
      raise Error;
    end;{}

    if (vHModule = 0) then
    begin
      //raise EOdbcApi.Create('Not found any Api Library "' + sLibNames + '"');
      exit;
    end;

    Result := TOdbcApiProxy.Create;
    with Result do
    try
      if vOdbcDriverLevel < 0 then
        fOdbcApiCache.Add(sLib, Result)
      else
        fOdbcApiCache.Add(IntToStr(vOdbcDriverLevel) + cSqlAttrOdbcVerSeparator + sLib, Result);

      hModuleApi := vHModule;
      vHModule := 0;
      fApiRefCount := 1;
      fModuleName := sLib;

      // Load API Procedures Addresses:

      // ODBC32DLL
        // sql.h
        GetProcAddressEx(hModuleApi, 'SQLAllocHandle', @@SQLAllocHandleA);
        if not Assigned(SQLAllocHandleA) then
        begin
          GetProcAddressEx(hModuleApi, 'SQLAllocConnect', @@SQLAllocConnectA);  // ODBC 2
          GetProcAddressEx(hModuleApi, 'SQLAllocEnv', @@SQLAllocEnvA);        // ODBC 2
          GetProcAddressEx(hModuleApi, 'SQLAllocStmt', @@SQLAllocStmtA);      // ODBC 2
        end;
        GetProcAddressEx(hModuleApi, 'SQLBindCol', @@SQLBindColA);
        GetProcAddressEx(hModuleApi, 'SQLBindParam', @@SQLBindParamA);
        GetProcAddressEx(hModuleApi, 'SQLCancel', @@SQLCancelA);
        GetProcAddressEx(hModuleApi, 'SQLCloseCursor', @@SQLCloseCursorA);
        GetProcAddressEx(hModuleApi, 'SQLColAttribute', @@SQLColAttributeA, @@SQLColAttributeW);
        GetProcAddressEx(hModuleApi, 'SQLColumns', @@SQLColumnsA, @@SQLColumnsW);
        GetProcAddressEx(hModuleApi, 'SQLConnect', @@SQLConnectA, @@SQLConnectW);
        GetProcAddressEx(hModuleApi, 'SQLCopyDesc', @@SQLCopyDescA);
        GetProcAddressEx(hModuleApi, 'SQLDataSources', @@SQLDataSourcesA, @@SQLDataSourcesW);
        GetProcAddressEx(hModuleApi, 'SQLDescribeCol', @@SQLDescribeColA, @@SQLDescribeColW);
        GetProcAddressEx(hModuleApi, 'SQLDisconnect', @@SQLDisconnectA);
        GetProcAddressEx(hModuleApi, 'SQLEndTran', @@SQLEndTranA);
        GetProcAddressEx(hModuleApi, 'SQLError', @@SQLErrorA, @@SQLErrorW);
        GetProcAddressEx(hModuleApi, 'SQLExecDirect', @@SQLExecDirectA, @@SQLExecDirectW);
        GetProcAddressEx(hModuleApi, 'SQLExecute', @@SQLExecuteA);
        GetProcAddressEx(hModuleApi, 'SQLFetch', @@SQLFetchA);
        GetProcAddressEx(hModuleApi, 'SQLFetchScroll', @@SQLFetchScrollA);
        GetProcAddressEx(hModuleApi, 'SQLFreeConnect', @@SQLFreeConnectA);
        GetProcAddressEx(hModuleApi, 'SQLFreeEnv', @@SQLFreeEnvA);
        GetProcAddressEx(hModuleApi, 'SQLFreeHandle', @@SQLFreeHandleA);
        GetProcAddressEx(hModuleApi, 'SQLFreeStmt', @@SQLFreeStmtA);
        GetProcAddressEx(hModuleApi, 'SQLGetConnectAttr', @@SQLGetConnectAttrA, @@SQLGetConnectAttrW);
        GetProcAddressEx(hModuleApi, 'SQLGetConnectOption', @@SQLGetConnectOptionA, @@SQLGetConnectOptionW);
        GetProcAddressEx(hModuleApi, 'SQLGetCursorName', @@SQLGetCursorNameA, @@SQLGetCursorNameW);
        GetProcAddressEx(hModuleApi, 'SQLGetData', @@SQLGetDataA);
        GetProcAddressEx(hModuleApi, 'SQLGetDescField', @@SQLGetDescFieldA, @@SQLGetDescFieldW);
        GetProcAddressEx(hModuleApi, 'SQLGetDescRec', @@SQLGetDescRecA, @@SQLGetDescRecW);
        GetProcAddressEx(hModuleApi, 'SQLGetDiagField', @@SQLGetDiagFieldA, @@SQLGetDiagFieldW);
        GetProcAddressEx(hModuleApi, 'SQLGetDiagRec', @@SQLGetDiagRecA, @@SQLGetDiagRecW);
        GetProcAddressEx(hModuleApi, 'SQLGetEnvAttr', @@SQLGetEnvAttrA);
        GetProcAddressEx(hModuleApi, 'SQLGetFunctions', @@SQLGetFunctionsA);
        GetProcAddressEx(hModuleApi, 'SQLGetInfo', @@SQLGetInfoA, @@SQLGetInfoW);
        GetProcAddressEx(hModuleApi, 'SQLGetStmtAttr', @@SQLGetStmtAttrA, @@SQLGetStmtAttrW);
        GetProcAddressEx(hModuleApi, 'SQLGetStmtOption', @@SQLGetStmtOptionA);
        GetProcAddressEx(hModuleApi, 'SQLGetTypeInfo', @@SQLGetTypeInfoA, @@SQLGetTypeInfoW);
        GetProcAddressEx(hModuleApi, 'SQLNumResultCols', @@SQLNumResultColsA);
        GetProcAddressEx(hModuleApi, 'SQLParamData', @@SQLParamDataA);
        GetProcAddressEx(hModuleApi, 'SQLPrepare', @@SQLPrepareA, @@SQLPrepareW);
        GetProcAddressEx(hModuleApi, 'SQLPutData', @@SQLPutDataA);
        GetProcAddressEx(hModuleApi, 'SQLRowCount', @@SQLRowCountA, @@SQLRowCountW);
        GetProcAddressEx(hModuleApi, 'SQLSetConnectAttr', @@SQLSetConnectAttrA, @@SQLSetConnectAttrW);
        GetProcAddressEx(hModuleApi, 'SQLSetConnectOption', @@SQLSetConnectOptionA, @@SQLSetConnectOptionW);
        GetProcAddressEx(hModuleApi, 'SQLSetCursorName', @@SQLSetCursorNameA, @@SQLSetCursorNameW);
        GetProcAddressEx(hModuleApi, 'SQLSetDescField', @@SQLSetDescFieldA, @@SQLSetDescFieldW);
        GetProcAddressEx(hModuleApi, 'SQLSetDescRec', @@SQLSetDescRecA);
        GetProcAddressEx(hModuleApi, 'SQLSetEnvAttr', @@SQLSetEnvAttrA);
        GetProcAddressEx(hModuleApi, 'SQLSetParam', @@SQLSetParamA);
        GetProcAddressEx(hModuleApi, 'SQLSetStmtAttr', @@SQLSetStmtAttrA, @@SQLSetStmtAttrW);
        GetProcAddressEx(hModuleApi, 'SQLSetStmtOption', @@SQLSetStmtOptionA);
        GetProcAddressEx(hModuleApi, 'SQLSpecialColumns', @@SQLSpecialColumnsA, @@SQLSpecialColumnsW);
        GetProcAddressEx(hModuleApi, 'SQLStatistics', @@SQLStatisticsA, @@SQLStatisticsW);
        GetProcAddressEx(hModuleApi, 'SQLTables', @@SQLTablesA, @@SQLTablesW);
        GetProcAddressEx(hModuleApi, 'SQLTransact', @@SQLTransactA);
        // sqlext.h
        GetProcAddressEx(hModuleApi, 'SQLDriverConnect', @@SQLDriverConnectA, @@SQLDriverConnectW);
        GetProcAddressEx(hModuleApi, 'SQLBrowseConnect', @@SQLBrowseConnectA, @@SQLBrowseConnectW);
        GetProcAddressEx(hModuleApi, 'SQLBulkOperations', @@SQLBulkOperationsA);
        GetProcAddressEx(hModuleApi, 'SQLColAttributes', @@SQLColAttributesA, @@SQLColAttributesW);
        GetProcAddressEx(hModuleApi, 'SQLColumnPrivileges', @@SQLColumnPrivilegesA, @@SQLColumnPrivilegesW);
        GetProcAddressEx(hModuleApi, 'SQLDescribeParam', @@SQLDescribeParamA);
        GetProcAddressEx(hModuleApi, 'SQLExtendedFetch', @@SQLExtendedFetchA);
        GetProcAddressEx(hModuleApi, 'SQLForeignKeys', @@SQLForeignKeysA, @@SQLForeignKeysW);
        GetProcAddressEx(hModuleApi, 'SQLMoreResults', @@SQLMoreResultsA);
        GetProcAddressEx(hModuleApi, 'SQLNativeSql', @@SQLNativeSqlA, @@SQLNativeSqlW);
        GetProcAddressEx(hModuleApi, 'SQLNumParams', @@SQLNumParamsA);
        GetProcAddressEx(hModuleApi, 'SQLParamOptions', @@SQLParamOptionsA);
        GetProcAddressEx(hModuleApi, 'SQLPrimaryKeys', @@SQLPrimaryKeysA, @@SQLPrimaryKeysW);
        GetProcAddressEx(hModuleApi, 'SQLProcedureColumns', @@SQLProcedureColumnsA, @@SQLProcedureColumnsW);
        GetProcAddressEx(hModuleApi, 'SQLProcedures', @@SQLProceduresA, @@SQLProceduresW);
        GetProcAddressEx(hModuleApi, 'SQLSetPos', @@SQLSetPosA);
        GetProcAddressEx(hModuleApi, 'SQLTablePrivileges', @@SQLTablePrivilegesA, @@SQLTablePrivilegesW);
        GetProcAddressEx(hModuleApi, 'SQLDrivers', @@SQLDriversA, @@SQLDriversW);
        GetProcAddressEx(hModuleApi, 'SQLBindParameter', @@SQLBindParameterA);
        GetProcAddressEx(hModuleApi, 'SQLAllocHandleStd', @@SQLAllocHandleStdA);
        GetProcAddressEx(hModuleApi, 'SQLSetScrollOptions', @@SQLSetScrollOptionsA, @@SQLSetScrollOptionsW);

        fSystemODBCManager := CompareText(fModuleName, ODBC32DLL) = 0;

        if fSystemODBCManager then
        begin
          fLockLib := True;
          //ODBCTRAC
          hModuleApiTrac := SafeLoadLibrary(ODBCTRAC);
          fModuleNameTrac := ODBCTRAC;
          if hModuleApiTrac <> 0 then
          begin
            GetProcAddressEx(hModuleApiTrac, 'TraceOpenLogFile', @@TraceOpenLogFileA);
            GetProcAddressEx(hModuleApiTrac, 'TraceCloseLogFile', @@TraceCloseLogFileA);
            GetProcAddressEx(hModuleApiTrac, 'TraceReturn', @@TraceReturnA);
            GetProcAddressEx(hModuleApiTrac, 'TraceVersion', @@TraceVersionA);
            GetProcAddressEx(hModuleApiTrac, 'TraceVSControl', @@TraceVSControlA);
            GetProcAddressEx(hModuleApiTrac, 'FireVSDebugEvent', @@FireVSDebugEventA);
          end;
          //ODBCINST
          hModuleApiInst := SafeLoadLibrary(ODBCInst);
          fModuleNameInst := ODBCInst;
          if hModuleApiInst <> 0 then
          begin
            GetProcAddressEx(hModuleApiInst, 'ODBCSetTryWaitValue', @@ODBCSetTryWaitValueA);
            GetProcAddressEx(hModuleApiInst, 'ODBCGetTryWaitValue', @@ODBCGetTryWaitValueA);
          end;
        end;

        // INFORMIX ODBC DRIVER BUG for "SQLDescribeColA()":
          // ODBC Direct mode (Informix ODBC Driver Without a Driver Manager) error:
          // Error in "SQLDescribeColA()", but work fine for "SQLDescribeColW()".
          // Driver library:
          //   "iclit09b.dll", version; "3.81.00.11267".
          //  or
          //   "iclit09bw.dll", version: "3.80.00.10841"
        {begin:fix}
          if // ( not fOwnerDbxDriver.fOdbcApi.SystemODBCManager ) and
            Assigned(SQLDescribeColA) and Assigned(SQLDescribeColW)
            and
            (Pos(#1+sLib+#1,
              // windows libs:
                #1'iclit09b.dll'#1'iclit09a.dll'#1'iclit09bw.dll'#1'iclit09aw.dll'+
              // linux libs:
                // multithreaded library
                #1'iclit09b.so'#1'iclit09a.so'#1'iclit09bw.so'#1'iclit09aw.so'+
                #1'libthcli.so'#1'libifdrm.so'+
                #1'idmrs09b.so'#1'idmrs09a.so'#1'idmrs09bw.so'#1'idmrs09aw.so'+
                // nonthreaded library
                #1'iclis09b.so'#1'iclis09a.so'#1'iclis09bw.so'#1'iclis09aw.so'+
                #1'libifcli.so'+
                #1 ) > 0
            )
          then
            @SQLDescribeColA := nil;
        {end.}

        if (not Assigned(SQLAllocHandleA)) or (not Assigned(SQLSetEnvAttrA)) then
          fOdbcDriverLevel := 2
        else
        if not fSystemODBCManager then
          fOdbcDriverLevel := -1
        else
          fOdbcDriverLevel := 3;

        if (vOdbcDriverLevel > 0)
          and ((fOdbcDriverLevel <0 ) or (vOdbcDriverLevel < fOdbcDriverLevel))
        then
          fOdbcDriverLevel := vOdbcDriverLevel;

    except
      on e:Exception do
      begin
        FreeAndNil(Result);
        raise;
      end;
    end;
  finally
    fOdbcApiCache.EndLock;
    if vHModule <> 0 then
      FreeLibrary(vHModule);
  end;
end;

procedure UnLoadOdbcDriverManager(OdbcApi: TOdbcApiProxy);
begin
  if OdbcApi = nil then
    exit;
  fOdbcApiCache.BeginLock;
  with OdbcApi do
  try
    dec(fApiRefCount);
    // Remove odbc api cache.
    {$IFDEF UnloadApiCache}
    if (not fLockLib) and (fApiRefCount <= 0) then
      fOdbcApiCache.Remove(fModuleName, True);
    {$ENDIF}
  finally
    fOdbcApiCache.EndLock;
  end;
end;

{ TOdbcApiProxy }

destructor TOdbcApiProxy.Destroy;
begin
  {$IFDEF _iOdbcApi_}
  if Assigned(fOdbcApiImpl) then
  begin
    fOdbcApiImpl.fOdbcApiProxy := nil;
    fOdbcApiImpl := nil;
    fOdbcApiIntf := nil; // _Release
  end;
  {$ENDIF}
  if hModuleApi <> 0 then
    FreeLibrary(hModuleApi);
  if hModuleApiTrac <> 0 then
    FreeLibrary(hModuleApiTrac);
  if hModuleApiInst <> 0 then
    FreeLibrary(hModuleApiInst);
  inherited;
end;

procedure TOdbcApiProxy.NotImplemented(const sFuncName: string;
  iLevel: Integer = OdbcApi_NotImplemented_OdbcName);
var
  sLib: String;
begin
  case iLevel of
    OdbcApi_NotImplemented_OdbcName:
      sLib := fModuleName;
    OdbcApi_NotImplemented_OdbcTrac:
      sLib := fModuleNameTrac;
    OdbcApi_NotImplemented_OdbcInst:
      sLib := fModuleNameInst;
    else
      sLib := '';
  end;
  raise EOdbcApiNotImplemented.Create('Not implemented the ODBC API function "' + sFuncName +
    '" in library "' + sLib +'"' );
end;

procedure TOdbcApiProxy.BeginLock;
begin
  fOdbcApiCache.BeginLock;
end;

procedure TOdbcApiProxy.EndLock;
begin
  fOdbcApiCache.EndLock;
end;

function TOdbcApiProxy.SQLAllocConnect(EnvironmentHandle: SqlHEnv;
  var ConnectionHandle: SqlHDbc): SqlReturn;
begin
  if Assigned(SQLAllocConnectA) then
    Result := SQLAllocConnectA(EnvironmentHandle, ConnectionHandle)
  else
    Result := SQLAllocHandle(SQL_HANDLE_DBC, EnvironmentHandle, ConnectionHandle);
end;

function TOdbcApiProxy.SQLAllocEnv(
  var EnvironmentHandle: SqlHEnv): SqlReturn;
begin
  EnvironmentHandle := SQL_NULL_HANDLE;
  if Assigned(SQLAllocEnvA) then
    Result := SQLAllocEnvA(EnvironmentHandle)
  else
    Result := SQLAllocHandle( SQL_HANDLE_ENV, SQL_NULL_HANDLE, SqlHandle(EnvironmentHandle) );
end;

function TOdbcApiProxy.SQLAllocHandleStd(fHandleType: SqlSmallint;
  hInput: SqlHandle; var phOutput: SqlHandle): SqlReturn;
begin
  Result := SQL_ERROR;
  if Assigned(SQLAllocHandleStdA) then
    Result := SQLAllocHandleStdA(fHandleType, hInput, phOutput)
  else
    NotImplemented('SQLAllocHandleStd');
end;

function TOdbcApiProxy.SQLAllocHandle(HandleType: SqlSmallint;
  InputHandle: SqlHandle; var OutputHandle: SqlHandle): SqlReturn;
begin
  Result := SQL_ERROR;
  if Assigned(SQLAllocHandleA) then
    Result := SQLAllocHandleA(HandleType, InputHandle, OutputHandle)
  else
  begin
    case HandleType of
      SQL_HANDLE_ENV:
        if Assigned(SQLAllocEnvA) then
        begin
          Result := SQLAllocEnvA(OutputHandle);
          exit;
        end;
      SQL_HANDLE_DBC:
        if Assigned(SQLAllocConnectA) then
        begin
          Result := SQLAllocConnectA(InputHandle, OutputHandle);
          exit;
        end;
      SQL_HANDLE_STMT:
        if Assigned(SQLAllocStmtA) then
        begin
          Result := SQLAllocStmtA(InputHandle, OutputHandle);
          exit;
        end;
      {SQL_HANDLE_DESC:
        begin
          //return SQL_ERROR, SQLSTATE HY092 ("Invalid attribute/option identifier")
        end;}
    end;
    NotImplemented('SQLAllocHandle');
  end;
end;

function TOdbcApiProxy.SQLAllocStmt(ConnectionHandle: SqlHDbc;
  var StatementHandle: SqlHStmt): SqlReturn;
begin
  if Assigned(SQLAllocStmtA) then
    Result := SQLAllocStmtA(ConnectionHandle, StatementHandle)
  else
    Result := SQLAllocHandle(SQL_HANDLE_STMT, ConnectionHandle, StatementHandle);
end;

function TOdbcApiProxy.SQLBindCol(StatementHandle: SqlHStmt;
  ColumnNumber: SqlUSmallint; TargetType: SqlSmallint;
  TargetValue: SqlPointer; BufferLength: SqlInteger;
  StrLen_or_Ind: PSqlInteger): SqlReturn;
begin
  Result := SQL_ERROR;
  if Assigned(SQLBindColA) then
    Result := SQLBindColA(StatementHandle, ColumnNumber, TargetType, TargetValue,
      BufferLength, StrLen_or_Ind)
  else
    NotImplemented('SQLBindCol');
end;

function TOdbcApiProxy.SQLBindParam(StatementHandle: SqlHStmt;
  ParameterNumber: SqlUSmallint; ValueType, ParameterType: SqlSmallint;
  LengthPrecision: SqlUInteger; ParameterScale: SqlSmallint;
  ParameterValue: SqlPointer; var StrLen_or_Ind: SqlInteger): SqlReturn;
begin
  Result := SQL_ERROR;
  if Assigned(SQLBindParamA) then
    Result := SQLBindParamA(StatementHandle, ParameterNumber, ValueType, ParameterType,
      LengthPrecision, ParameterScale, ParameterValue, StrLen_or_Ind)
  else
    NotImplemented('SQLBindParam');
end;

function TOdbcApiProxy.SQLBindParameter(HStmt: SqlHStmt;
  ipar: SqlUSmallint; fParamType, fCType, fSqlType: SqlSmallint;
  cbColDef: SqlUInteger; ibScale: SqlSmallint; rgbValue: SqlPointer;
  cbValueMax: SqlInteger; pcbValue: PSqlInteger): SqlReturn;
begin
  Result := SQL_ERROR;
  if Assigned(SQLBindParameterA) then
    Result := SQLBindParameterA(HStmt, ipar, fParamType, fCType, fSqlType, cbColDef,
      ibScale, rgbValue, cbValueMax, pcbValue)
  else
    NotImplemented('SQLBindParameter');
end;

function TOdbcApiProxy.SQLBrowseConnect(HDbc: SqlHDbc;
  var szConnStrIn: SqlChar; cbConnStrIn: SqlSmallint;
  var szConnStrOut: SqlChar; cbConnStrOutMax: SqlSmallint;
  var pcbConnStrOut: SqlSmallint): SqlReturn;
var
  wszConnStrIn, wszConnStrOut: WideString;
  sConnStrOut: string;
begin
  Result := SQL_ERROR;
  if Assigned(SQLBrowseConnectA) then
    Result := SQLBrowseConnectA(HDbc, szConnStrIn, cbConnStrIn, szConnStrOut,
      cbConnStrOutMax, pcbConnStrOut)
  else
  if Assigned(SQLBrowseConnectW) then
  begin
    wszConnStrIn := StrPas(PAnsiChar(@szConnStrIn));
    cbConnStrIn := Length(wszConnStrIn)+1;
    SetLength(wszConnStrOut, cbConnStrOutMax * 4);
    pcbConnStrOut := 0;

    Result := SQLBrowseConnectW(HDbc, PSqlChar(PWideChar(wszConnStrIn))^, cbConnStrIn,
      PSqlChar(PWideChar(wszConnStrOut))^, cbConnStrOutMax, pcbConnStrOut);
    if {(Result in [SQL_SUCCESS, SQL_SUCCESS_WITH_INFO]) and} (pcbConnStrOut >= 0) then
    begin
      SetLength(wszConnStrOut, pcbConnStrOut);
      sConnStrOut := wszConnStrOut;
      if Length(sConnStrOut) >= cbConnStrOutMax then
        SetLength(sConnStrOut, cbConnStrOutMax-1);
      StrCopy(PAnsiChar(@szConnStrOut), PAnsiChar(sConnStrOut));
    end;
  end
  else
    NotImplemented('SQLBrowseConnect');
end;

function TOdbcApiProxy.SQLBulkOperations(StatementHandle: SqlHStmt;
  Operation: SqlSmallint): SqlReturn;
begin
  Result := SQL_ERROR;
  if Assigned(SQLBulkOperationsA) then
    Result := SQLBulkOperationsA(StatementHandle, Operation)
  else
    NotImplemented('SQLBulkOperations');
end;

function TOdbcApiProxy.SQLCancel(
  StatementHandle: SqlHStmt): SqlReturn;
begin
  Result := SQL_ERROR;
  if Assigned(SQLCancelA) then
    Result := SQLCancelA(StatementHandle)
  else
    NotImplemented('SQLCancel');
end;

function TOdbcApiProxy.SQLCloseCursor(
  StatementHandle: SqlHStmt): SqlReturn;
begin
  Result := SQL_ERROR;
  if Assigned(SQLCloseCursorA) then
    Result := SQLCloseCursorA(StatementHandle)
  else
  if Assigned(SQLFreeStmtA) then
    Result := SQLFreeStmt(StatementHandle, SQL_CLOSE)
  else
    NotImplemented('SQLCloseCursor');
end;

function TOdbcApiProxy.SQLColAttribute(StatementHandle: SqlHStmt;
  ColumnNumber, FieldIdentifier: SqlUSmallint;
  CharacterAttribute: SqlPointer; BufferLength: SqlSmallint;
  StringLength: pSqlSmallint; NumericAttributePtr: SqlPointer): SqlReturn;
var
  wszCharacterAttribute: WideString;
  sCharacterAttribute: string;
  vCharacterAttribute: SqlPointer;
  bHandleWS: Boolean;
  // SQLColAttributes:
  pcbDesc: SqlSmallint;
  pfDesc: SqlInteger;
begin
  Result := SQL_ERROR;
  if Assigned(SQLColAttributeA) then
    Result := SQLColAttributeA(StatementHandle, ColumnNumber, FieldIdentifier,
      CharacterAttribute, BufferLength, StringLength, NumericAttributePtr)
  else
  if Assigned(SQLColAttributeW) then
  begin
    bHandleWS := (BufferLength = SQL_NTS{> 0}) and Assigned(CharacterAttribute) and Assigned(StringLength);
    if bHandleWS then
    begin
      SetLength(wszCharacterAttribute, BufferLength * 4);
      vCharacterAttribute := PWideChar(wszCharacterAttribute);
      StringLength^ := 0;
    end
    else
      vCharacterAttribute := CharacterAttribute;

    Result := SQLColAttributeW(StatementHandle, ColumnNumber, FieldIdentifier,
      vCharacterAttribute, BufferLength, StringLength, NumericAttributePtr);

    if {(Result in [SQL_SUCCESS, SQL_SUCCESS_WITH_INFO]) and} bHandleWS and (StringLength^ >= 0) then
    begin
      SetLength(wszCharacterAttribute, StringLength^);
      sCharacterAttribute := wszCharacterAttribute;
      if Length(sCharacterAttribute) >= BufferLength then
        SetLength(sCharacterAttribute, BufferLength-1);
      StrCopy(PAnsiChar(CharacterAttribute), PAnsiChar(sCharacterAttribute));
    end;
  end
  else
  if Assigned(SQLColAttributesA) or Assigned(SQLColAttributesW) then
  begin
    pcbDesc := 0;
    pfDesc := 0;
    Result := SQLColAttributes(StatementHandle, ColumnNumber,
      FieldIdentifier, CharacterAttribute, BufferLength,
      pcbDesc, pfDesc);
    if Assigned(StringLength) then
      StringLength^ := pcbDesc;
    if Assigned(NumericAttributePtr) then
      Move(pfDesc, NumericAttributePtr, pcbDesc);
  end
  else
    NotImplemented('SQLColAttribute');
end;

function TOdbcApiProxy.SQLColAttributeInt(StatementHandle: SqlHStmt;
  ColumnNumber, FieldIdentifier: SqlUSmallint;
  CharacterAttribute: SqlPointer; BufferLength: SqlSmallint;
  StringLength: pSqlSmallint; var NumericAttribute: SqlInteger): SqlReturn;
begin
  Result := SQLColAttribute(StatementHandle,
    ColumnNumber, FieldIdentifier,
    CharacterAttribute, BufferLength,
    StringLength, @NumericAttribute);
end;

function TOdbcApiProxy.SQLColAttributeString(
  StatementHandle: SqlHStmt; ColumnNumber, FieldIdentifier: SqlUSmallint;
  CharacterAttribute: SqlPointer; BufferLength: SqlSmallint;
  var StringLength: SqlSmallint; NumericAttribute: SqlPointer): SqlReturn;
begin
  Result := SQLColAttribute(StatementHandle,
    ColumnNumber, FieldIdentifier,
    CharacterAttribute, BufferLength,
    @StringLength, NumericAttribute);
end;

function TOdbcApiProxy.SQLColAttributes(HStmt: SqlHStmt; icol,
  fDescType: SqlUSmallint; rgbDesc: SqlPointer; cbDescMax: SqlSmallint;
  var pcbDesc: SqlSmallint; var pfDesc: SqlInteger): SqlReturn;
var
  wszDesc: WideString;
  sDesc: string;
  bHandleWS: Boolean;
  vDesc: SqlPointer;
begin
  Result := SQL_ERROR;
  if Assigned(SQLColAttributesA) then
    Result := SQLColAttributesA(HStmt, icol, fDescType, rgbDesc, cbDescMax, pcbDesc, pfDesc)
  else
  if Assigned(SQLColAttributesW) then
  begin
    bHandleWS := Assigned(rgbDesc) and ( (cbDescMax>0) {or (cbDescMax = SQL_NTS){ :<-??? });
    if bHandleWS then
    begin
     SetLength(wszDesc, cbDescMax*2);
     FillChar( PWideChar(wszDesc)^, cbDescMax*4, #0);
     vDesc := PWideChar(wszDesc);
     pcbDesc := 0;
    end
    else
      vDesc := rgbDesc;
    Result := SQLColAttributesW(HStmt, icol, fDescType, vDesc, cbDescMax, pcbDesc, pfDesc);
    if {(Result in [SQL_SUCCESS, SQL_SUCCESS_WITH_INFO]) and} bHandleWS and (pcbDesc >= 0) then
    begin
      SetLength(wszDesc, pcbDesc);
      sDesc := wszDesc;
      if Length(sDesc) >= cbDescMax then
        SetLength(sDesc, cbDescMax-1);
      StrCopy(PAnsiChar(rgbDesc), PAnsiChar(sDesc));
    end;
  end
  else
    NotImplemented('QLColAttributes');
end;

function TOdbcApiProxy.SQLColumnPrivileges(HStmt: SqlHStmt;
  var szCatalogName: SqlChar; cbCatalogName: SqlSmallint;
  var szSchemaName: SqlChar; cbSchemaName: SqlSmallint;
  var szTableName: SqlChar; cbTableName: SqlSmallint;
  var szColumnName: SqlChar; cbColumnName: SqlSmallint): SqlReturn;
var
  wszCatalogName, wszSchemaName, wszTableName, wszColumnName :WideString;
begin
  Result := SQL_ERROR;
  if Assigned(SQLColumnPrivilegesA) then
    Result := SQLColumnPrivilegesA(HStmt,
      szCatalogName, cbCatalogName,
      szSchemaName, cbSchemaName,
      szTableName, cbTableName,
      szColumnName, cbColumnName)
  else
  if Assigned(SQLColumnPrivilegesW) then
  begin
    wszCatalogName := StrPas(PAnsiChar(@szCatalogName));
      //cbCatalogName := SQL_NTS; // or Length(wszCatalogName) + 1;{???: +1}
    wszSchemaName := StrPas(PAnsiChar(@szSchemaName));
      //cbSchemaName := Length(wszSchemaName) + 1;
    wszTableName := StrPas(PAnsiChar(@szTableName));
      //cbTableName := Length(wszTableName) + 1;
    wszColumnName := StrPas(PAnsiChar(@szColumnName));
      //cbColumnName := Length(wszColumnName) + 1;

    Result := SQLColumnPrivilegesW(HStmt,
      PSqlChar(PWideChar(wszCatalogName))^, cbCatalogName,
      PSqlChar(PWideChar(wszSchemaName))^, cbSchemaName,
      PSqlChar(PWideChar(wszTableName))^, cbTableName,
      PSqlChar(PWideChar(wszColumnName))^, cbColumnName);
  end
  else
    NotImplemented('SQLColumnPrivileges');
end;

function TOdbcApiProxy.SQLColumns(StatementHandle: SqlHStmt;
  CatalogName: PAnsiChar; NameLength1: SqlSmallint; SchemaName: PAnsiChar;
  NameLength2: SqlSmallint; TableName: PAnsiChar; NameLength3: SqlSmallint;
  ColumnName: PAnsiChar; NameLength4: SqlSmallint): SqlReturn;
var
  wszCatalogName, wszSchemaName, wszTableName, wszColumnName: WideString;
begin
  Result := SQL_ERROR;
  if Assigned(SQLColumnsA) then
    Result := SQLColumnsA(StatementHandle,
      CatalogName, NameLength1,
      SchemaName, NameLength2,
      TableName, NameLength3,
      ColumnName, NameLength4)
  else
  if Assigned(SQLColumnsW) then
  begin
    if Assigned(CatalogName) then
    begin
      wszCatalogName := StrPas(CatalogName);
      //NameLength1 := SQL_NTS; // or Length(wszCatalogName) +1;
      CatalogName := PAnsiChar(PWideChar(wszCatalogName));
    end
    else
      NameLength1 := 0;
    if Assigned(SchemaName) then
    begin
      wszSchemaName := StrPas(SchemaName);
      //NameLength2 := Length(wszSchemaName) + 1;
      SchemaName := PAnsiChar(PWideChar(wszSchemaName));
    end
    else
      NameLength2 := 0;
    if Assigned(TableName) then
    begin
      wszTableName := StrPas(TableName);
      //NameLength3 := Length(wszTableName) + 1;
      TableName := PAnsiChar(PWideChar(wszTableName));
    end
    else
      NameLength3 := 0;
    if Assigned(ColumnName) then
    begin
      wszColumnName := StrPas(ColumnName);
      //NameLength4 := Length(wszColumnName) + 1;
      ColumnName := PAnsiChar(PWideChar(wszColumnName));
    end
    else
      NameLength4 := 0;
    Result := SQLColumnsW(StatementHandle,
      CatalogName, NameLength1,
      SchemaName, NameLength2,
      TableName, NameLength3,
      ColumnName, NameLength4);
  end
  else
    NotImplemented('SQLColumns');
end;

function TOdbcApiProxy.SQLConnect(ConnectionHandle: SqlHDbc;
  ServerName: PAnsiChar; NameLength1: SqlSmallint; UserName: PAnsiChar;
  NameLength2: SqlSmallint; Authentication: PAnsiChar;
  NameLength3: SqlSmallint): SqlReturn;
var
  wszServerName, wszUserName, wszAuthentication: WideString;
begin
  Result := SQL_ERROR;
  if Assigned(SQLConnectA) then
    Result := SQLConnectA(ConnectionHandle,
      ServerName, NameLength1,
      UserName, NameLength2,
      Authentication, NameLength3)
  else
  if Assigned(SQLConnectW) then
  begin
    if Assigned(ServerName) then
    begin
      wszServerName := StrPas(ServerName);
      //NameLength1 := SQL_NTS; // or Length(wszServerName) +1;
      ServerName := PAnsiChar(PWideChar(wszServerName));
    end
    else
      NameLength1 := 0;
    if Assigned(UserName) then
    begin
      wszUserName := StrPas(UserName);
      //NameLength2 := Length(wszUserName) +1;
      UserName := PAnsiChar(PWideChar(wszUserName));
    end
    else
      NameLength2 := 0;
    if Assigned(Authentication) then
    begin
      wszAuthentication := StrPas(Authentication);
      //NameLength3 := Length(wszAuthentication) +1;
      Authentication := PAnsiChar(PWideChar(wszAuthentication));
    end
    else
      NameLength3 := 0;

    Result := SQLConnectW(ConnectionHandle,
      ServerName, NameLength1,
      UserName, NameLength2,
      Authentication, NameLength3);
  end
  else
    NotImplemented('SQLConnect');
end;

function TOdbcApiProxy.SQLCopyDesc(SourceDescHandle,
  TargetDescHandle: SqlHDesc): SqlReturn;
begin
  Result := SQL_ERROR;
  if Assigned(SQLCopyDescA) then
    Result := SQLCopyDescA(SourceDescHandle, TargetDescHandle)
  else
    NotImplemented('SQLCopyDesc');
end;

function TOdbcApiProxy.SQLDataSources(EnvironmentHandle: SqlHEnv;
  Direction: SqlUSmallint; var ServerName: SqlChar;
  BufferLength1: SqlSmallint; var NameLength1: SqlSmallint;
  var Description: SqlChar; BufferLength2: SqlSmallint;
  var NameLength2: SqlSmallint): SqlReturn;
var
  wszServerName, wszDescription: WideString;
  sServerName, sDescription: string;
begin
  Result := SQL_ERROR;
  if Assigned(SQLDataSourcesA) then
    Result := SQLDataSourcesA(EnvironmentHandle, Direction,
      ServerName, BufferLength1, NameLength1,
      Description, BufferLength2, NameLength2)
  else
  if Assigned(SQLDataSourcesW) then
  begin
    if BufferLength1 > 0 {= SQL_NTS} then
    begin
      SetLength(wszServerName, BufferLength1);
      NameLength1 := 0;
    end;
    if BufferLength1 > 0 {= SQL_NTS} then
    begin
      SetLength(wszDescription, BufferLength2);
      NameLength2 := 0;
    end;

    Result := SQLDataSourcesW(EnvironmentHandle, Direction,
      ServerName, BufferLength1, NameLength1,
      Description, BufferLength2, NameLength2);

    //if not (Result in [SQL_SUCCESS, SQL_SUCCESS_WITH_INFO]) then exit;

    if BufferLength1 > 0 {= SQL_NTS} then
    begin
      SetLength(wszServerName, NameLength1);
      sServerName := wszServerName;
      if Length(sServerName) >= BufferLength1 then
        SetLength(sServerName, BufferLength1-1);
      StrCopy( PAnsiChar(@ServerName), PAnsiChar(sServerName));
    end;
    if BufferLength1 > 0 {= SQL_NTS} then
    begin
      SetLength(wszDescription, NameLength2);
      sDescription := wszDescription;
      if Length(sDescription) >= BufferLength2 then
        SetLength(sDescription, BufferLength2-1);
      StrCopy( PAnsiChar(@Description), PAnsiChar(sDescription));
    end;

  end
  else
    NotImplemented('SQLDataSources');
end;

function TOdbcApiProxy.SQLDescribeCol(StatementHandle: SqlHStmt;
  ColumnNumber: SqlUSmallint;
  ColumnName: PAnsiChar;
  BufferLength: SqlSmallint; var NameLength, DataType: SqlSmallint;
  var ColumnSize: SqlUInteger; var DecimalDigits,
  Nullable: SqlSmallint): SqlReturn;
var
  wszColumnName: WideString;
  sColumnName: string;
begin
  Result := SQL_ERROR;
  if Assigned(SQLDescribeColA) then
    Result := SQLDescribeColA(StatementHandle, ColumnNumber,
      ColumnName, BufferLength, NameLength,
      DataType, ColumnSize, DecimalDigits, Nullable)
  else
  if Assigned(SQLDescribeColW) then
  begin
    if BufferLength < 0 then
      BufferLength := 0;
    SetLength(wszColumnName, BufferLength);
    if BufferLength > 0 then
      FillChar(PWideChar(wszColumnName)^, BufferLength*2, #0);
    NameLength := 0;
    Result := SQLDescribeColW(StatementHandle, ColumnNumber,
      PAnsiChar(PWideChar(wszColumnName)), BufferLength, NameLength,
      DataType, ColumnSize, DecimalDigits, Nullable);
    if {(Result in [SQL_SUCCESS, SQL_SUCCESS_WITH_INFO]) and}
      (NameLength >= 0) {and (ColumnName<>nil)} then
    begin
      SetLength(wszColumnName, NameLength);
      sColumnName := wszColumnName;
      if Length(sColumnName) >= BufferLength then
        SetLength(sColumnName, BufferLength-1);
      StrCopy(ColumnName, PAnsiChar(sColumnName));
    end;
  end
  else
    NotImplemented('SQLDescribeCol');
end;

function TOdbcApiProxy.SQLDescribeParam(HStmt: SqlHStmt;
  ipar: SqlUSmallint; var pfSqlType: SqlSmallint;
  var pcbParamDef: SqlUInteger; var pibScale,
  pfNullable: SqlSmallint): SqlReturn;
begin
  Result := SQL_ERROR;
  if Assigned(SQLDescribeParamA) then
    Result := SQLDescribeParamA(HStmt, ipar, pfSqlType, pcbParamDef, pibScale, pfNullable)
  else
    NotImplemented('SQLDescribeParam');
end;

function TOdbcApiProxy.SQLDisconnect(
  ConnectionHandle: SqlHDbc): SqlReturn;
begin
  Result := SQL_ERROR;
  if Assigned(SQLDisconnectA) then
    Result := SQLDisconnectA(ConnectionHandle)
  else
    NotImplemented('SQLDisconnect');
end;

function TOdbcApiProxy.SQLDriverConnect(HDbc: SqlHDbc;
  hwnd: SqlHWnd; szConnStrIn: PAnsiChar; cbConnStrIn: SqlSmallint;
  szConnStrOut: PAnsiChar; cbConnStrOutMax: SqlSmallint;
  var pcbConnStrOut: SqlSmallint;
  fDriverCompletion: SqlUSmallint): SqlReturn;
var
  wszConnStrIn, wszConnStrOut: WideString;
  sConnStrOut: string;
begin
  Result := SQL_ERROR;
  if Assigned(SQLDriverConnectA) then
    Result := SQLDriverConnectA(HDbc,hwnd, szConnStrIn, cbConnStrIn, szConnStrOut,
      cbConnStrOutMax, pcbConnStrOut, fDriverCompletion)
  else
  if Assigned(SQLDriverConnectW) then
  begin
    if Assigned(szConnStrIn) then
    begin
      wszConnStrIn := StrPas(szConnStrIn);
      cbConnStrIn := Length(wszConnStrIn);
    end
    else
    begin
      wszConnStrIn := '';
      cbConnStrIn := 0;
    end;
    SetLength(wszConnStrOut, cbConnStrOutMax * 4);
    Result := SQLDriverConnectW(HDbc,hwnd, PAnsiChar(PWideChar(wszConnStrIn)), cbConnStrIn,
      PAnsiChar(PWideChar(wszConnStrOut)), cbConnStrOutMax, pcbConnStrOut, fDriverCompletion);
    if {(Result in [SQL_SUCCESS, SQL_SUCCESS_WITH_INFO]) and}
      Assigned(szConnStrOut) and (pcbConnStrOut > 0) then
    begin
      SetLength(wszConnStrOut, pcbConnStrOut);
      sConnStrOut := wszConnStrOut;
      if Length(sConnStrOut) >= cbConnStrOutMax then
        SetLength(sConnStrOut, cbConnStrOutMax-1);
      StrCopy(szConnStrOut, PAnsiChar(sConnStrOut));
    end;
  end
  else
    NotImplemented('SQLDriverConnect');
end;

function TOdbcApiProxy.SQLDrivers(HEnv: SqlHEnv;
  fDirection: SqlUSmallint; szDriverDesc: PAnsiChar;
  cbDriverDescMax: SqlSmallint; var pcbDriverDesc: SqlSmallint;
  szDriverAttributes: PAnsiChar; cbDrvrAttrMax: SqlSmallint;
  var pcbDrvrAttr: SqlSmallint): SqlReturn;
var
  wszDriverDesc, wszDriverAttributes: WideString;
  sDriverDesc, sDriverAttributes: string;
begin
  Result := SQL_ERROR;
  if Assigned(SQLDriversA) then
    Result := SQLDriversA(HEnv, fDirection,
      szDriverDesc, cbDriverDescMax, pcbDriverDesc,
      szDriverAttributes, cbDrvrAttrMax, pcbDrvrAttr)
  else
  if Assigned(SQLDriversW) then
  begin
    if cbDriverDescMax < 0 then
      cbDriverDescMax := 0;
    SetLength(wszDriverDesc, cbDriverDescMax);
    if cbDriverDescMax > 0 then
      FillChar(PWideChar(wszDriverDesc)^, cbDriverDescMax*2, #0);
    pcbDriverDesc := 0;

    if cbDrvrAttrMax < 0 then
      cbDrvrAttrMax := 0;
    SetLength(wszDriverAttributes, cbDrvrAttrMax);
    if cbDrvrAttrMax > 0 then
      FillChar(PWideChar(wszDriverAttributes)^, cbDrvrAttrMax*2, #0);
    pcbDrvrAttr := 0;

    Result := SQLDriversW(HEnv, fDirection,
      PAnsiChar(PWideChar(wszDriverDesc)), cbDriverDescMax, pcbDriverDesc,
      PAnsiChar(PWideChar(wszDriverAttributes)), cbDrvrAttrMax, pcbDrvrAttr);

    //if not (Result in [SQL_SUCCESS, SQL_SUCCESS_WITH_INFO]) then exit;

    if Assigned(szDriverDesc) and (pcbDriverDesc >= 0)then
    begin
      SetLength(wszDriverDesc, pcbDriverDesc);
      sDriverDesc := wszDriverDesc;
      if Length(sDriverDesc) >= cbDriverDescMax then
        SetLength(sDriverDesc, cbDriverDescMax-1);
      StrCopy(szDriverDesc, PAnsiChar(sDriverDesc));
    end;

    if Assigned(szDriverAttributes) and (pcbDrvrAttr >= 0) then
    begin
      SetLength(wszDriverAttributes, pcbDrvrAttr);
      sDriverAttributes := wszDriverAttributes;
      if Length(sDriverAttributes) >= cbDrvrAttrMax then
        SetLength(sDriverAttributes, cbDrvrAttrMax-1);
      StrCopy(szDriverAttributes, PAnsiChar(sDriverAttributes));
    end;
  end
  else
    NotImplemented('SQLDrivers');
end;

function TOdbcApiProxy.SQLEndTran(HandleType: SqlSmallint;
  Handle: SqlHandle; CompletionType: SqlSmallint): SqlReturn;
begin
  Result := SQL_ERROR;
  if Assigned(SQLEndTranA) then
    Result := SQLEndTranA(HandleType, Handle, CompletionType)
  else
  if Assigned(SQLTransactA) then
  begin
    if HandleType = SQL_HANDLE_DBC then
      Result := SQLTransact(SQl_NULL_HANDLE, Handle, CompletionType)
    else
    if HandleType = SQL_HANDLE_ENV then
      Result := SQLTransact(Handle, SQl_NULL_HANDLE, CompletionType)
    else
      NotImplemented('SQLEndTran');
  end
  else
    NotImplemented('SQLEndTran');
end;

function TOdbcApiProxy.SQLError(EnvironmentHandle: SqlHEnv;
  ConnectionHandle: SqlHDbc; StatementHandle: SqlHStmt;
  var Sqlstate: SqlChar; var NativeError: SqlInteger;
  var MessageText: SqlChar; BufferLength: SqlSmallint;
  var TextLength: SqlSmallint): SqlReturn;
var
  wszSqlState, wszMessageText: WideString;
  sSqlState, sMessageText: string;
begin
  Result := SQL_ERROR;
  if Assigned(SQLErrorA) then
    Result := SQLErrorA(EnvironmentHandle, ConnectionHandle, StatementHandle,
      SqlState, NativeError,
      MessageText, BufferLength, TextLength)
  else
  if Assigned(SQLErrorW) then
  begin
    SetLength(wszSqlState, SizeOf(TSqlState)-1);
    FillChar(PWideChar(wszSqlState)^, Length(wszSqlState)*2-2, '0');
    if BufferLength < 0 then
      BufferLength := 0;
    SetLength(wszMessageText, BufferLength*4);
    if BufferLength > 0 then
      FillChar(PWideChar(wszMessageText)^, Length(wszSqlState), #0);
    TextLength := 0;

    Result := SQLErrorW(EnvironmentHandle, ConnectionHandle, StatementHandle,
      PSqlChar(PWideChar(wszSqlState))^, NativeError,
      PSqlChar(PWideChar(wszMessageText))^, BufferLength, TextLength);

    if {(Result in [SQL_SUCCESS, SQL_SUCCESS_WITH_INFO]) and} (TextLength >= 0) then
    begin
      sSqlState := wszSqlState;
      sMessageText := wszMessageText;
      StrCopy(PAnsiChar(@SqlState), PAnsiChar(sSqlState));
      StrCopy(PAnsiChar(@MessageText), PAnsiChar(sMessageText));
    end;
  end
  else
    NotImplemented('SQLError');
end;

function TOdbcApiProxy.SQLExecDirect(StatementHandle: SqlHStmt;
  StatementText: PAnsiChar; TextLength: SqlInteger): SqlReturn;
var
  wszStatementText: WideString;
begin
  Result := SQL_ERROR;
  if Assigned(SQLExecDirectA) then
    Result := SQLExecDirectA(StatementHandle, StatementText, TextLength)
  else
  if Assigned(SQLExecDirectW) then
  begin
    wszStatementText := StrPas(StatementText);
    Result := SQLExecDirectW(StatementHandle, PAnsiChar(PWideChar(wszStatementText)), TextLength);
  end
  else
    NotImplemented('SQLExecDirect');
end;

function TOdbcApiProxy.SQLExecute(
  StatementHandle: SqlHStmt): SqlReturn;
begin
  Result := SQL_ERROR;
  if Assigned(SQLExecuteA) then
    Result := SQLExecuteA(StatementHandle)
  else
    NotImplemented('SQLExecute');
end;

function TOdbcApiProxy.SQLExtendedFetch(HStmt: SqlHStmt;
  fFetchType: SqlUSmallint; irow: SqlInteger; var pcrow: SqlUInteger;
  var rgfRowStatus: SqlUSmallint): SqlReturn;
begin
  Result := SQL_ERROR;
  if Assigned(SQLExtendedFetchA) then
    Result := SQLExtendedFetchA(HStmt, fFetchType, irow, pcrow, rgfRowStatus)
  else
    NotImplemented('SQLExtendedFetch');
end;

function TOdbcApiProxy.SQLFetch(
  StatementHandle: SqlHStmt): SqlReturn;
begin
  Result := SQL_ERROR;
  if Assigned(SQLFetchA) then
    Result := SQLFetchA(StatementHandle)
  else
    NotImplemented('SQLFetch');
end;

function TOdbcApiProxy.SQLFetchScroll(StatementHandle: SqlHStmt;
  FetchOrientation: SqlSmallint; FetchOffset: SqlInteger): SqlReturn;
begin
  Result := SQL_ERROR;
  if Assigned(SQLFetchScrollA) then
    Result := SQLFetchScroll(StatementHandle, FetchOrientation, FetchOffset)
  else
    NotImplemented('SQLFetchScroll');
end;

function TOdbcApiProxy.SQLForeignKeys(HStmt: SqlHStmt;
  var szPkCatalogName: SqlChar; cbPkCatalogName: SqlSmallint;
  var szPkSchemaName: SqlChar; cbPkSchemaName: SqlSmallint;
  var szPkTableName: SqlChar; cbPkTableName: SqlSmallint;
  var szFkCatalogName: SqlChar; cbFkCatalogName: SqlSmallint;
  var szFkSchemaName: SqlChar; cbFkSchemaName: SqlSmallint;
  var szFkTableName: SqlChar; cbFkTableName: SqlSmallint): SqlReturn;
var
  wszPkCatalogName, wszPkSchemaName, wszPkTableName,
  wszFkCatalogName, wszFkSchemaName, wszFkTableName: WideString;
begin
  Result := SQL_ERROR;
  if Assigned(SQLForeignKeysA) then
    Result := SQLForeignKeysA(HStmt,
      szPkCatalogName, cbPkCatalogName,
      szPkSchemaName, cbPkSchemaName,
      szPkTableName, cbPkTableName,
      szFkCatalogName, cbFkCatalogName,
      szFkSchemaName, cbFkSchemaName,
      szFkTableName, cbFkTableName)
  else
  if Assigned(SQLForeignKeysW) then
  begin
    wszPkCatalogName := StrPas(PAnsiChar(@szPkCatalogName));
    wszPkSchemaName := StrPas(PAnsiChar(@szPkSchemaName));
    wszPkTableName := StrPas(PAnsiChar(@szPkTableName));
    wszFkCatalogName := StrPas(PAnsiChar(@szFkCatalogName));
    wszFkSchemaName := StrPas(PAnsiChar(@szFkSchemaName));
    wszFkTableName := StrPas(PAnsiChar(@szFkTableName));

    Result := SQLForeignKeysW(HStmt,
      PSqlChar(PWideChar(wszPkCatalogName))^, cbPkCatalogName,
      PSqlChar(PWideChar(wszPkSchemaName))^, cbPkSchemaName,
      PSqlChar(PWideChar(wszPkTableName))^, cbPkTableName,
      PSqlChar(PWideChar(wszFkCatalogName))^, cbFkCatalogName,
      PSqlChar(PWideChar(wszFkSchemaName))^, cbFkSchemaName,
      PSqlChar(PWideChar(wszFkTableName))^, cbFkTableName)
  end
  else
    NotImplemented('SQLForeignKeys');
end;

function TOdbcApiProxy.SQLFreeConnect(
  ConnectionHandle: SqlHDbc): SqlReturn;
begin
  Result := SQL_ERROR;
  if Assigned(SQLFreeConnectA) then
    Result := SQLFreeConnectA(ConnectionHandle)
  else
    NotImplemented('SQLFreeConnect');
end;

function TOdbcApiProxy.SQLFreeEnv(
  EnvironmentHandle: SqlHEnv): SqlReturn;
begin
  Result := SQL_ERROR;
  if Assigned(SQLFreeEnvA) then
    Result := SQLFreeEnvA(EnvironmentHandle)
  else
    NotImplemented('SQLFreeEnv');
end;

function TOdbcApiProxy.SQLFreeHandle(HandleType: SqlSmallint;
  Handle: SqlHandle): SqlReturn;
  procedure DoSQLFreeHandle();
  begin
    if Assigned(SQLFreeHandleA) then
      Result := SQLFreeHandleA(HandleType, Handle)
    else
    begin
      case HandleType of
        SQL_HANDLE_ENV:
          Result := SQLFreeEnv(Handle);
        SQL_HANDLE_DBC:
          Result := SQLFreeConnect(Handle);
        SQL_HANDLE_STMT:
          Result := SQLFreeStmt(Handle, SQL_DROP);
        else
          NotImplemented('SQLFreeHandle');
      end;
    end;
  end;
begin
  Result := SQL_ERROR;
  if (HandleType = SQL_HANDLE_ENV) and (fOdbcDriverLevel < 3) and (not fSystemODBCManager) then
  begin
    BeginLock;
    try
      if ( fApiRefCount < 2 ) then
        DoSQLFreeHandle();
      // We cannot trace a situation when there are connections through ODBC manager or other driver.
      // Therefore always we return success:
      Result := SQL_SUCCESS;
    finally
      EndLock;
    end;
  end
  else
    DoSQLFreeHandle();
end;

function TOdbcApiProxy.SQLFreeStmt(StatementHandle: SqlHStmt;
  Option: SqlUSmallint): SqlReturn;
begin
  Result := SQL_ERROR;
  if Assigned(SQLFreeStmtA) then
    Result := SQLFreeStmtA(StatementHandle, Option)
  else
    NotImplemented('SQLFreeStmt');
end;

function TOdbcApiProxy.SQLGetConnectAttr(ConnectionHandle: SqlHDbc;
  Attribute: SqlInteger; ValuePtr: SqlPointer; BufferLength: SqlInteger;
  pStringLength: PSqlInteger): SqlReturn;
var
  vValuePtr: SqlPointer;
  bHandleWS: Boolean;
  wszValuePtr: WideString;
  sValuePtr: string;
begin
  Result := SQL_ERROR;
  if Assigned(SQLGetConnectAttrA) then
    Result := SQLGetConnectAttrA(ConnectionHandle, Attribute,
      ValuePtr, BufferLength, pStringLength)
  else
  if Assigned(SQLGetConnectAttrW) then
  begin
    bHandleWS := (pStringLength<>nil) and (ValuePtr<>nil) and (BufferLength>0);
    if bHandleWS then
    begin
      SetLength(wszValuePtr, BufferLength);
      FillChar(PWideChar(wszValuePtr)^, BufferLength*2, #0);
      vValuePtr := SqlPointer(PWideChar(wszValuePtr));
      pStringLength^ := 0;
    end
    else
      vValuePtr := ValuePtr;

    Result := SQLGetConnectAttrW(ConnectionHandle, Attribute,
      vValuePtr, BufferLength, pStringLength);

    if bHandleWS then
    begin
      SetLength(wszValuePtr, pStringLength^);
      sValuePtr := wszValuePtr;
      if Length(sValuePtr) >= BufferLength then
        SetLength(sValuePtr, BufferLength-1);
      StrCopy( PAnsiChar(ValuePtr), PAnsiChar(sValuePtr));
    end;
  end
  else
  if Assigned(SQLGetConnectOptionA) or Assigned(SQLGetConnectOptionW) then
  begin
    bHandleWS := Assigned(ValuePtr) and Assigned(pStringLength) and
      (BufferLength < SQL_MAX_OPTION_STRING_LENGTH) and
      ( Attribute in [SQL_ATTR_CURRENT_CATALOG, SQL_ATTR_TRACEFILE, SQL_ATTR_TRANSLATE_LIB] );
    if bHandleWS then
    begin
      SetLength(sValuePtr, SQL_MAX_OPTION_STRING_LENGTH + 1);
      FillChar(sValuePtr[1], Length(sValuePtr), #0);
      vValuePtr := PAnsiChar(sValuePtr);
    end
    else
      vValuePtr := ValuePtr;
    Result := SQLGetConnectOption(ConnectionHandle, Attribute, vValuePtr);
    if bHandleWS then
      StrLCopy( ValuePtr, vValuePtr, BufferLength);
  end
  else
    NotImplemented('SQLGetConnectAttr');
end;

function TOdbcApiProxy.SQLGetConnectOption(
  ConnectionHandle: SqlHDbc; Option: SqlUSmallint;
  Value: SqlPointer): SqlReturn;
begin
  Result := SQL_ERROR;
  if Assigned(SQLGetConnectOptionA) then
    Result := SQLGetConnectOptionA(ConnectionHandle, Option, Value)
  else
  if Assigned(SQLGetConnectOptionW) then
    Result := SQLGetConnectOptionW(ConnectionHandle, Option, Value)
  else
  if Assigned(SQLGetConnectAttrA) or Assigned(SQLGetConnectAttrW) then
  begin
    case Option of
      // Env
      SQL_ATTR_OUTPUT_NTS,
      SQL_ATTR_ODBC_VERSION,
      SQL_ATTR_CONNECTION_POOLING,
      SQL_ATTR_CP_MATCH,
      // Con
      SQL_ATTR_CURRENT_CATALOG,
      SQL_ATTR_TRACEFILE,
      SQL_ATTR_TRANSLATE_LIB:
        Result := SQLGetConnectAttr(ConnectionHandle, Option, Value, SQL_MAX_OPTION_STRING_LENGTH, nil)
      else
        Result := SQLGetConnectAttr(ConnectionHandle, Option, Value, 0, nil);
    end;//of: case
  end
  else
    NotImplemented('SQLGetConnectOption');
end;

function TOdbcApiProxy.SQLGetCursorName(StatementHandle: SqlHStmt;
  CursorName: PAnsiChar; BufferLength: SqlSmallint;
  var NameLength: SqlSmallint): SqlReturn;
var
  wszCursorName: WideString;
  sCursorName: string;
  bHandleWS: Boolean;
begin
  Result := SQL_ERROR;
  if Assigned(SQLGetCursorNameA) then
    Result := SQLGetCursorNameA(StatementHandle,
      CursorName, BufferLength, NameLength)
  else
  if Assigned(SQLGetCursorNameW) then
  begin
    bHandleWS := (CursorName<>nil) and (BufferLength > 0 {=SQL_NTS});
    if bHandleWS then
    begin
      SetLength(wszCursorName, BufferLength);
      FillChar(PWideChar(wszCursorName)^, BufferLength*2, #0);
      NameLength := 0;
    end
    else
      wszCursorName := '';

    Result := SQLGetCursorNameW(StatementHandle,
      PAnsiChar(PWideChar(wszCursorName)), BufferLength, NameLength);

    if bHandleWS then
    begin
      SetLength(wszCursorName, NameLength);
      sCursorName := wszCursorName;
      StrCopy(CursorName, PAnsiChar(sCursorName));
    end;
  end
  else
    NotImplemented('SQLGetCursorName');
end;

function TOdbcApiProxy.SQLGetData(StatementHandle: SqlHStmt;
  ColumnNumber: SqlUSmallint; TargetType: SqlSmallint;
  TargetValue: SqlPointer; BufferLength: SqlInteger;
  StrLen_or_Ind: PSqlInteger): SqlReturn;
begin
  Result := SQL_ERROR;
  if Assigned(SQLGetDataA) then
    Result := SQLGetDataA(StatementHandle, ColumnNumber, TargetType, TargetValue,
      BufferLength, StrLen_or_Ind)
  else
    NotImplemented('SQLGetData');
end;

function TOdbcApiProxy.SQLGetDescField(DescriptorHandle: SqlHDesc;
  RecNumber, FieldIdentifier: SqlSmallint; Value: SqlPointer;
  BufferLength: SqlInteger; var StringLength: SqlInteger): SqlReturn;
var
  bHandleWS: Boolean;
  wszValue: WideString;
  sValue: string;
  vValue: SqlPointer;
begin
  Result := SQL_ERROR;
  if Assigned(SQLGetDescFieldA) then
    Result := SQLGetDescFieldA(DescriptorHandle, RecNumber, FieldIdentifier,
      Value, BufferLength, StringLength)
  else
  if Assigned(SQLGetDescFieldW) then
  begin
    bHandleWS := (Value<>nil) and (BufferLength > 0 {=SQL_NTS});
    if bHandleWS then
    begin
      SetLength(wszValue, BufferLength);
      FillChar( PWideChar(wszValue)^, BufferLength*2, #0);
      StringLength := 0;
      vValue := PWideChar(wszValue);
    end
    else
      vValue := Value;

    Result := SQLGetDescFieldW(DescriptorHandle, RecNumber, FieldIdentifier,
      vValue, BufferLength, StringLength);

    if {(Result in [SQL_SUCCESS, SQL_SUCCESS_WITH_INFO]) and} bHandleWS and (StringLength >= 0) then
    begin
      SetLength(wszValue, StringLength);
      sValue := wszValue;
      if Length(sValue) >= BufferLength then
        SetLength(sValue, BufferLength);
      StrCopy(PAnsiChar(Value), PAnsiChar(sValue));
    end;
  end
  else
    NotImplemented('SQLGetDescField');
end;

function TOdbcApiProxy.SQLGetDescRec(DescriptorHandle: SqlHDesc;
  RecNumber: SqlSmallint; var Name: SqlChar; BufferLength: SqlSmallint;
  var StringLength, _Type, SubType: SqlSmallint; var Length: SqlInteger;
  var Precision, Scale, Nullable: SqlSmallint): SqlReturn;
var
  wszName: WideString;
  sName: string;
begin
  Result := SQL_ERROR;
  if Assigned(SQLGetDescRecA) then
    Result := SQLGetDescRecA(DescriptorHandle, RecNumber,
      Name, BufferLength, StringLength,
      _Type, SubType,
      Length, Precision, Scale, Nullable)
  else
  if Assigned(SQLGetDescRecW) then
  begin
    if BufferLength > 0 {=SQL_NTS} then
    begin
      SetLength(wszName, BufferLength);
      FillChar( PWideChar(wszName)^, BufferLength*2, #0);
    end
    else
    begin
      wszName := '';
      BufferLength := 0;
    end;
    StringLength := 0;

    Result := SQLGetDescRecW(DescriptorHandle, RecNumber,
      PSqlChar(PWideChar(wszName))^, BufferLength, StringLength,
      _Type, SubType,
      Length, Precision, Scale, Nullable);

    if {(Result in [SQL_SUCCESS, SQL_SUCCESS_WITH_INFO]) and} (StringLength >= 0) then
    begin
      SetLength(wszName, StringLength);
      sName := wszName;
      StrCopy( PAnsiChar(@Name), PAnsiChar(sName));
    end;
  end
  else
    NotImplemented('SQLGetDescRec');
end;

function TOdbcApiProxy.SQLGetDiagField(HandleType: SqlSmallint;
  Handle: SqlHandle; RecNumber, DiagIdentifier: SqlSmallint;
  DiagInfo: SqlPointer; BufferLength: SqlSmallint;
  var StringLength: SqlSmallint): SqlReturn;
var
  wszDiagInfo: WideString;
  sDiagInfo: string;
begin
  Result := SQL_ERROR;
  if Assigned(SQLGetDiagFieldA) then
    Result := SQLGetDiagFieldA(HandleType, Handle, RecNumber, DiagIdentifier,
      DiagInfo, BufferLength, StringLength)
  else
  if Assigned(SQLGetDiagFieldW) then
  begin
    if BufferLength > 0 {=SQL_NTS} then
    begin
      SetLength(wszDiagInfo, BufferLength);
      FillChar( PWideChar(wszDiagInfo)^, BufferLength*2, #0);
    end
    else
    begin
      wszDiagInfo := '';
      BufferLength := 0;
    end;
    StringLength := 0;

    Result := SQLGetDiagFieldW(HandleType, Handle, RecNumber, DiagIdentifier,
      DiagInfo, BufferLength, StringLength);

    if {(Result in [SQL_SUCCESS, SQL_SUCCESS_WITH_INFO]) and} (StringLength >= 0) then
    begin
      SetLength(wszDiagInfo, StringLength);
      sDiagInfo := wszDiagInfo;
      StrCopy( PAnsiChar(DiagInfo), PAnsiChar(sDiagInfo));
    end;
  end
  else
    NotImplemented('SQLGetDiagField');
end;

function TOdbcApiProxy.SQLGetDiagRec(HandleType: SqlSmallint;
  Handle: SqlHandle; RecNumber: SqlSmallint; SqlState: PAnsiChar;
  var NativeError: SqlInteger; MessageText: PAnsiChar;
  BufferLength: SqlSmallint; var TextLength: SqlSmallint): SqlReturn;
var
  wszSqlState, wszMessageText: WideString;
  sSqlState, sMessageText: string;
begin
  Result := SQL_ERROR;
  if Assigned(SQLGetDiagRecA) then
    Result := SQLGetDiagRecA(HandleType, Handle, RecNumber,
    SqlState, NativeError,
    MessageText, BufferLength, TextLength)
  else
  if Assigned(SQLGetDiagRecW) then
  begin
    SetLength(wszSqlState, SizeOf(TSqlState)-1);
    FillChar(PWideChar(wszSqlState)^, Length(wszSqlState)*2-2, '0');
    if BufferLength < 0 then
      BufferLength := 0;
    SetLength(wszMessageText, BufferLength*4);
    if BufferLength > 0 then
      FillChar(PWideChar(wszMessageText)^, Length(wszSqlState), #0);
    TextLength := 0;

    Result := SQLGetDiagRecW(HandleType, Handle, RecNumber,
      PAnsiChar(PWideChar(wszSqlState)), NativeError,
      PAnsiChar(PWideChar(wszMessageText)), BufferLength*4, TextLength);

    if {(Result in [SQL_SUCCESS, SQL_SUCCESS_WITH_INFO]) and} (TextLength >= 0) then
    begin
      sSqlState := wszSqlState;
      sMessageText := wszMessageText;
      StrCopy(SqlState, PAnsiChar(sSqlState));
      StrCopy(MessageText, PAnsiChar(sMessageText));
    end;
  end
  else
    NotImplemented('SQLGetDiagRec');
end;

function TOdbcApiProxy.SQLGetEnvAttr(EnvironmentHandle: SqlHEnv;
  Attribute: SqlInteger; Value: SqlPointer; BufferLength: SqlInteger;
  var StringLength: SqlInteger): SqlReturn;
begin
  Result := SQL_ERROR;
  if Assigned(SQLGetEnvAttrA) then
    Result := SQLGetEnvAttrA(EnvironmentHandle, Attribute, Value, BufferLength, StringLength)
  else
    NotImplemented('SQLGetEnvAttr');
end;

function TOdbcApiProxy.SQLFunctionSupported(ConnectionHandle: SqlHDbc; FunctionId: SqlUSmallint): Boolean;
var
  vSupported: SqlUSmallint;
begin
  if SQLGetFunctions(ConnectionHandle, FunctionId, vSupported) = SQL_SUCCESS then
    Result := vSupported = SQL_TRUE
  else
    Result := False;
end;

function TOdbcApiProxy.SQLGetFunctions(ConnectionHandle: SqlHDbc;
  FunctionId: SqlUSmallint; var Supported: SqlUSmallint): SqlReturn;
begin
  if Assigned(SQLGetFunctionsA) then
    Result := SQLGetFunctionsA(ConnectionHandle, FunctionId, Supported)
  else
    Result := SQL_ERROR;

  //  Not implemented "SQLGetFunctions()" in "MERANT 3.60 32-BIT dBASEFile (*.dbf)".

  if (Result <> SQL_SUCCESS)
    or (Supported = SQL_FALSE) // *** Fixed: MSSQL Driver "sqlsrv32.dll, ver: 2000.81.9030.04":
                               //     Driver d`nt set parameter "Supported".
  then
  begin
    Result := SQL_SUCCESS;
    Supported := SQL_FALSE;
    case FunctionId of
      SQL_API_SQLALLOCCONNECT:
        begin
          if Assigned(SQLAllocConnectA) then
            Supported := SQL_TRUE;
        end;
      SQL_API_SQLALLOCENV:
        begin
          if Assigned(SQLAllocEnvA) then
            Supported := SQL_TRUE;
        end;
      SQL_API_SQLALLOCHANDLE:
        begin
          if Assigned(SQLAllocHandleA) then
            Supported := SQL_TRUE;
        end;
      SQL_API_SQLALLOCSTMT:
        begin
          if Assigned(SQLAllocStmtA) then
            Supported := SQL_TRUE;
        end;
      SQL_API_SQLBINDCOL:
        begin
          if Assigned(SQLBindColA) then
            Supported := SQL_TRUE;
        end;
      SQL_API_SQLBINDPARAM:
        begin
          if Assigned(SQLBindParamA) then
            Supported := SQL_TRUE;
        end;
      SQL_API_SQLCANCEL:
        begin
          if Assigned(SQLCancelA) then
            Supported := SQL_TRUE;
        end;
      SQL_API_SQLCLOSECURSOR:
        begin
          if Assigned(SQLCloseCursorA) then
            Supported := SQL_TRUE;
        end;
      SQL_API_SQLCOLATTRIBUTE:
        begin
          if Assigned(SQLColAttributeA) or Assigned(SQLColAttributeW) then
            Supported := SQL_TRUE;
        end;
      SQL_API_SQLCOLUMNS:
        begin
          if Assigned(SQLColumnsA) or Assigned(SQLColumnsW) then
            Supported := SQL_TRUE;
        end;
      SQL_API_SQLCONNECT:
        begin
          if Assigned(SQLConnectA) or Assigned(SQLConnectW) then
            Supported := SQL_TRUE;
        end;
      SQL_API_SQLCOPYDESC:
        begin
          if Assigned(SQLCopyDescA) then
            Supported := SQL_TRUE;
        end;
      SQL_API_SQLDATASOURCES:
        begin
          if Assigned(SQLDataSourcesA) or Assigned(SQLDataSourcesW) then
            Supported := SQL_TRUE;
        end;
      SQL_API_SQLDESCRIBECOL:
        begin
          if Assigned(SQLDescribeColA) or Assigned(SQLDescribeColW) then
            Supported := SQL_TRUE;
        end;
      SQL_API_SQLDISCONNECT:
        begin
          if Assigned(SQLDisconnectA) then
            Supported := SQL_TRUE;
        end;
      SQL_API_SQLENDTRAN:
        begin
          if Assigned(SQLEndTranA) then
            Supported := SQL_TRUE;
        end;
      SQL_API_SQLERROR:
        begin
          if Assigned(SQLErrorA) or Assigned(SQLErrorW) then
            Supported := SQL_TRUE;
        end;
      SQL_API_SQLEXECDIRECT:
        begin
          if Assigned(SQLExecDirectA) or Assigned(SQLExecDirectW) then
            Supported := SQL_TRUE;
        end;
      SQL_API_SQLEXECUTE:
        begin
          if Assigned(SQLEXECUTEA) then
            Supported := SQL_TRUE;
        end;
      SQL_API_SQLFETCH:
        begin
          if Assigned(SQLFETCHA) then
            Supported := SQL_TRUE;
        end;
      SQL_API_SQLFETCHSCROLL:
        begin
          if Assigned(SQLFETCHSCROLLA) then
            Supported := SQL_TRUE;
        end;
      SQL_API_SQLFREECONNECT:
        begin
          if Assigned(SQLFREECONNECTA) then
            Supported := SQL_TRUE;
        end;
      SQL_API_SQLFREEENV:
        begin
          if Assigned(SQLFREEENVA) then
            Supported := SQL_TRUE;
        end;
      SQL_API_SQLFREEHANDLE:
        begin
          if Assigned(SQLFREEHANDLEA) then
            Supported := SQL_TRUE;
        end;
      SQL_API_SQLFREESTMT:
        begin
          if Assigned(SQLFREESTMTA) then
            Supported := SQL_TRUE;
        end;
      SQL_API_SQLGETCONNECTATTR:
        begin
          if Assigned(SQLGETCONNECTATTRA) or Assigned(SQLGETCONNECTATTRW) then
            Supported := SQL_TRUE;
        end;
      SQL_API_SQLGETCONNECTOPTION:
        begin
          if Assigned(SQLGETCONNECTOPTIONA) or Assigned(SQLGETCONNECTOPTIONW) then
            Supported := SQL_TRUE;
        end;
      SQL_API_SQLGETCURSORNAME:
        begin
          if Assigned(SQLGETCURSORNAMEA) or Assigned(SQLGETCURSORNAMEW) then
            Supported := SQL_TRUE;
        end;
      SQL_API_SQLGETDATA:
        begin
          if Assigned(SQLGETDATAA) then
            Supported := SQL_TRUE;
        end;
      SQL_API_SQLGETDESCFIELD:
        begin
          if Assigned(SQLGETDESCFIELDA) or Assigned(SQLGETDESCFIELDW) then
            Supported := SQL_TRUE;
        end;
      SQL_API_SQLGETDESCREC:
        begin
          if Assigned(SQLGETDESCRECA) or Assigned(SQLGETDESCRECW) then
            Supported := SQL_TRUE;
        end;
      SQL_API_SQLGETDIAGFIELD:
        begin
          if Assigned(SQLGETDIAGFIELDA) or Assigned(SQLGETDIAGFIELDW) then
            Supported := SQL_TRUE;
        end;
      SQL_API_SQLGETDIAGREC:
        begin
          if Assigned(SQLGETDIAGRECA) or Assigned(SQLGETDIAGRECW) then
            Supported := SQL_TRUE;
        end;
      SQL_API_SQLGETENVATTR:
        begin
          if Assigned(SQLGETENVATTRA) then
            Supported := SQL_TRUE;
        end;
      SQL_API_SQLGETFUNCTIONS:
        begin
          if Assigned(SQLGETFUNCTIONSA) then
            Supported := SQL_TRUE;
        end;
      SQL_API_SQLGETINFO:
        begin
          if Assigned(SQLGETINFOA) or Assigned(SQLGETINFOW) then
            Supported := SQL_TRUE;
        end;
      SQL_API_SQLGETSTMTATTR:
        begin
          if Assigned(SQLGETSTMTATTRA) or Assigned(SQLGETSTMTATTRW) then
            Supported := SQL_TRUE;
        end;
      SQL_API_SQLGETSTMTOPTION:
        begin
          if Assigned(SQLGETSTMTOPTIONA) then
            Supported := SQL_TRUE;
        end;
      SQL_API_SQLGETTYPEINFO:
        begin
          if Assigned(SQLGETTYPEINFOA) or Assigned(SQLGETTYPEINFOW) then
            Supported := SQL_TRUE;
        end;
      SQL_API_SQLNUMRESULTCOLS:
        begin
          if Assigned(SQLNUMRESULTCOLSA) then
            Supported := SQL_TRUE;
        end;
      SQL_API_SQLPARAMDATA:
        begin
          if Assigned(SQLPARAMDATAA) then
            Supported := SQL_TRUE;
        end;
      SQL_API_SQLPREPARE:
        begin
          if Assigned(SQLPREPAREA) or Assigned(SQLPREPAREW) then
            Supported := SQL_TRUE;
        end;
      SQL_API_SQLPUTDATA:
        begin
          if Assigned(SQLPUTDATAA) then
            Supported := SQL_TRUE;
        end;
      SQL_API_SQLROWCOUNT:
        begin
          if Assigned(SQLROWCOUNTA) or Assigned(SQLROWCOUNTW) then
            Supported := SQL_TRUE;
        end;
      SQL_API_SQLSETCONNECTATTR:
        begin
          if Assigned(SQLSETCONNECTATTRA) or Assigned(SQLSETCONNECTATTRW) then
            Supported := SQL_TRUE;
        end;
      SQL_API_SQLSETCONNECTOPTION:
        begin
          if Assigned(SQLSETCONNECTOPTIONA) or Assigned(SQLSETCONNECTOPTIONW) then
            Supported := SQL_TRUE;
        end;
      SQL_API_SQLSETCURSORNAME:
        begin
          if Assigned(SQLSETCURSORNAMEA) or Assigned(SQLSETCURSORNAMEW) then
            Supported := SQL_TRUE;
        end;
      SQL_API_SQLSETDESCFIELD:
        begin
          if Assigned(SQLSETDESCFIELDA) or Assigned(SQLSETDESCFIELDW) then
            Supported := SQL_TRUE;
        end;
      SQL_API_SQLSETDESCREC:
        begin
          if Assigned(SQLSETDESCRECA) then
            Supported := SQL_TRUE;
        end;
      SQL_API_SQLSETENVATTR:
        begin
          if Assigned(SQLSETENVATTRA) then
            Supported := SQL_TRUE;
        end;
      SQL_API_SQLSETPARAM:
        begin
          if Assigned(SQLSETPARAMA) then
            Supported := SQL_TRUE;
        end;
      SQL_API_SQLSETSTMTATTR:
        begin
          if Assigned(SQLSETSTMTATTRA) or Assigned(SQLSETSTMTATTRW) then
            Supported := SQL_TRUE;
        end;
      SQL_API_SQLSETSTMTOPTION:
        begin
          if Assigned(SQLSETSTMTOPTIONA) then
            Supported := SQL_TRUE;
        end;
      SQL_API_SQLSPECIALCOLUMNS:
        begin
          if Assigned(SQLSPECIALCOLUMNSA) or Assigned(SQLSPECIALCOLUMNSW) then
            Supported := SQL_TRUE;
        end;
      SQL_API_SQLSTATISTICS:
        begin
          if Assigned(SQLStatisticsA) or Assigned(SQLStatisticsW) then
            Supported := SQL_TRUE;
        end;
      SQL_API_SQLTABLES:
        begin
          if Assigned(SQLTABLESA) or Assigned(SQLTABLESW) then
            Supported := SQL_TRUE;
        end;
      SQL_API_SQLTRANSACT:
        begin
          if Assigned(SQLTRANSACTA) then
            Supported := SQL_TRUE;
        end;
    // sqlext.h
      SQL_API_SQLALLOCHANDLESTD:
        begin
          if Assigned(SQLALLOCHANDLESTDA) then
            Supported := SQL_TRUE;
        end;
      SQL_API_SQLBULKOPERATIONS:
        begin
          if Assigned(SQLBULKOPERATIONSA) then
            Supported := SQL_TRUE;
        end;
      SQL_API_SQLBINDPARAMETER:
        begin
          if Assigned(SQLBINDPARAMETERA) then
            Supported := SQL_TRUE;
        end;
      SQL_API_SQLBROWSECONNECT:
        begin
          if Assigned(SQLBROWSECONNECTA) or Assigned(SQLBROWSECONNECTW) then
            Supported := SQL_TRUE;
        end;
      //SQL_API_SQLCOLATTRIBUTES = SQL_API_SQLCOLATTRIBUTE
      SQL_API_SQLCOLUMNPRIVILEGES:
        begin
          if Assigned(SQLCOLUMNPRIVILEGESA) or Assigned(SQLCOLUMNPRIVILEGESW) then
            Supported := SQL_TRUE;
        end;
      SQL_API_SQLDESCRIBEPARAM:
        begin
          if Assigned(SQLDESCRIBEPARAMA) then
            Supported := SQL_TRUE;
        end;
      SQL_API_SQLDRIVERCONNECT:
        begin
          if Assigned(SQLDRIVERCONNECTA) or Assigned(SQLDRIVERCONNECTW) then
            Supported := SQL_TRUE;
        end;
      SQL_API_SQLDRIVERS:
        begin
          if Assigned(SQLDRIVERSA) or Assigned(SQLDRIVERSW) then
            Supported := SQL_TRUE;
        end;
      SQL_API_SQLEXTENDEDFETCH:
        begin
          if Assigned(SQLEXTENDEDFETCHA) then
            Supported := SQL_TRUE;
        end;
      SQL_API_SQLFOREIGNKEYS:
        begin
          if Assigned(SQLFOREIGNKEYSA) or Assigned(SQLFOREIGNKEYSW) then
            Supported := SQL_TRUE;
        end;
      SQL_API_SQLMORERESULTS:
        begin
          if Assigned(SQLMORERESULTSA) then
            Supported := SQL_TRUE;
        end;
      SQL_API_SQLNATIVESQL:
        begin
          if Assigned(SQLNATIVESQLA) or Assigned(SQLNATIVESQLW) then
            Supported := SQL_TRUE;
        end;
      SQL_API_SQLNUMPARAMS:
        begin
          if Assigned(SQLNUMPARAMSA) then
            Supported := SQL_TRUE;
        end;
      SQL_API_SQLPARAMOPTIONS:
        begin
          if Assigned(SQLPARAMOPTIONSA) then
            Supported := SQL_TRUE;
        end;
      SQL_API_SQLPRIMARYKEYS:
        begin
          if Assigned(SQLPrimaryKeysA) or Assigned(SQLPrimaryKeysW) then
            Supported := SQL_TRUE;
        end;
      SQL_API_SQLPROCEDURECOLUMNS:
        begin
          if Assigned(SQLPROCEDURECOLUMNSA) or Assigned(SQLPROCEDURECOLUMNSW) then
            Supported := SQL_TRUE;
        end;
      SQL_API_SQLPROCEDURES:
        begin
          if Assigned(SQLPROCEDURESA) or Assigned(SQLPROCEDURESW) then
            Supported := SQL_TRUE;
        end;
      SQL_API_SQLSETPOS:
        begin
          if Assigned(SQLSETPOSA) then
            Supported := SQL_TRUE;
        end;
      SQL_API_SQLSETSCROLLOPTIONS:
        begin
          if Assigned(SQLSETSCROLLOPTIONSA) or Assigned(SQLSETSCROLLOPTIONSW) then
            Supported := SQL_TRUE;
        end;
      SQL_API_SQLTABLEPRIVILEGES:
        begin
          if Assigned(SQLTABLEPRIVILEGESA) or Assigned(SQLTABLEPRIVILEGESW) then
            Supported := SQL_TRUE;
        end;
    end;
  end;
end;

function TOdbcApiProxy.SQLGetInfo(ConnectionHandle: SqlHDbc;
  InfoType: SqlUSmallint; InfoValuePtr: SqlPointer;
  BufferLength: SqlSmallint; StringLengthPtr: SqlPointer): SqlReturn;
var
  bHandleWS: Boolean;
  wszInfoValuePtr: WideString;
  sInfoValuePtr: string;
  vInfoValuePtr: SqlPointer;
begin
  Result := SQL_ERROR;
  if Assigned(SQLGetInfoA) then
    Result := SQLGetInfoA(ConnectionHandle, InfoType, InfoValuePtr, BufferLength, StringLengthPtr)
  else
  if Assigned(SQLGetInfoW) then
  begin
    bHandleWS := Assigned(StringLengthPtr) and Assigned(InfoValuePtr);// and (BufferLength > 0);
    if bHandleWS then
    begin
      if BufferLength <= 0 then
        BufferLength := 0
      else
        BufferLength := BufferLength * 2;
      SetLength(wszInfoValuePtr, BufferLength);
      if BufferLength > 0 then
        FillChar(PWideChar(wszInfoValuePtr)^, BufferLength, #0);
      //if Assigned(StringLengthPtr) then
      PSqlSmallint(StringLengthPtr)^ := 0;
      vInfoValuePtr := PWideChar(wszInfoValuePtr);
    end
    else
      vInfoValuePtr := InfoValuePtr;

    Result := SQLGetInfoW(ConnectionHandle, InfoType, vInfoValuePtr,
      BufferLength, StringLengthPtr);

    if {(Result in [SQL_SUCCESS, SQL_SUCCESS_WITH_INFO]) and}
      bHandleWS and (PSqlSmallint(StringLengthPtr)^ > 0) then
    begin
      SetLength(wszInfoValuePtr, PSqlSmallint(StringLengthPtr)^ div SizeOf(WideChar));
      sInfoValuePtr := wszInfoValuePtr;
      if Length(sInfoValuePtr) >= BufferLength then
        SetLength(sInfoValuePtr, BufferLength-1);
      StrCopy(PAnsiChar(InfoValuePtr), PAnsiChar(sInfoValuePtr));
    end;
  end
  else
    NotImplemented('SQLGetInfo');
end;

function TOdbcApiProxy.SQLGetInfoInt(ConnectionHandle: SqlHDbc;
  InfoType: SqlUSmallint; var InfoValue: SqlUInteger;
  Ignored1: SqlSmallint; Ignored2: Pointer): SqlReturn;
begin
  Result := SQLGetInfo(ConnectionHandle,
    InfoType, @InfoValue,
    {Ignored1=}SizeOf(SqlUInteger), {Ignored2=}nil);
end;

function TOdbcApiProxy.SQLGetInfoSmallint(ConnectionHandle: SqlHDbc;
  InfoType: SqlUSmallint; var InfoValue: SqlUSmallint;
  Ignored1: SqlSmallint; Ignored2: Pointer): SqlReturn;
begin
  Result := SQLGetInfo(ConnectionHandle,
    InfoType, @InfoValue,
    {Ignored1=}SizeOf(SqlUSmallint), {Ignored2=}nil);
end;

function TOdbcApiProxy.SQLGetInfoString(ConnectionHandle: SqlHDbc;
  InfoType: SqlUSmallint; InfoValueString: PAnsiChar;
  BufferLength: SqlSmallint; var StringLength: SqlSmallint): SqlReturn;
begin
  Result := SQLGetInfo(ConnectionHandle,
    InfoType, InfoValueString,
    BufferLength, @StringLength);
end;

function TOdbcApiProxy.SQLGetStmtAttr(StatementHandle: SqlHStmt;
  Attribute: SqlInteger; Value: SqlPointer; BufferLength: SqlInteger;
  StringLength: PSqlInteger): SqlReturn;
var
  wszValue: WideString;
  sValue: string;
  bHandleWS: Boolean;
  vValue: SqlPointer;
begin
  Result := SQL_ERROR;
  if Assigned(SQLGetStmtAttrA) then
    Result := SQLGetStmtAttrA(StatementHandle, Attribute,
      Value, BufferLength, StringLength)
  else
  if Assigned(SQLGetStmtAttrW) then
  begin
    bHandleWS := (Value<>nil) and (BufferLength>0) and (StringLength <> nil);
    if bHandleWS then
    begin
      SetLength(wszValue, BufferLength);
      FillChar(PWideChar(wszValue)^, BufferLength*2, #0);
      StringLength^ := 0;
      vValue := PWideChar(wszValue);
    end
    else
      vValue := Value;

    Result := SQLGetStmtAttrW(StatementHandle, Attribute,
      vValue, BufferLength, StringLength);

    if {(Result in [SQL_SUCCESS, SQL_SUCCESS_WITH_INFO]) and}
      bHandleWS and (StringLength^ >= 0) then
    begin
      SetLength(wszValue, StringLength^);
      sValue := wszValue;
      if Length(sValue) >= BufferLength then
        SetLength(sValue, BufferLength-1);
      StrCopy(PAnsiChar(Value), PAnsiChar(sValue));
    end;
  end
  else
  case Attribute of
    SQL_ATTR_QUERY_TIMEOUT:
      begin
        SQLUINTEGER(Value^) := 0;
        Result := SQL_SUCCESS;
      end;
    else
      NotImplemented('SQLGetStmtAttr');
  end;//of case
end;

function TOdbcApiProxy.SQLGetStmtOption(StatementHandle: SqlHStmt;
  Option: SqlUSmallint; Value: SqlPointer): SqlReturn;
begin
  Result := SQL_ERROR;
  if Assigned(SQLGetStmtOptionA) then
    Result := SQLGetStmtOptionA(StatementHandle, Option, Value)
  else
    NotImplemented('SQLGetStmtOption');
end;

function TOdbcApiProxy.SQLGetTypeInfo(StatementHandle: SqlHStmt;
  DataType: SqlSmallint): SqlReturn;
begin
  Result := SQL_ERROR;
  if Assigned(SQLGetTypeInfoA) then
    Result := SQLGetTypeInfoA(StatementHandle, DataType)
  else
  if Assigned(SQLGetTypeInfoW) then
    Result := SQLGetTypeInfoW(StatementHandle, DataType)
  else
    NotImplemented('SQLGetTypeInfo');
end;

function TOdbcApiProxy.SQLMoreResults(HStmt: SqlHStmt): SqlReturn;
begin
  Result := SQL_ERROR;
  if Assigned(SQLMoreResultsA) then
    Result := SQLMoreResultsA(HStmt)
  else
    NotImplemented('SQLMoreResults');
end;

function TOdbcApiProxy.SQLNativeSql(HDbc: SqlHDbc;
  var szSqlStrIn: SqlChar; cbSqlStrIn: SqlInteger; var szSqlStr: SqlChar;
  cbSqlStrMax: SqlInteger; var pcbSqlStr: SqlInteger): SqlReturn;
var
  wszSqlStrIn, wszSqlStr: WideString;
  sSqlStr: string;
begin
  Result := SQL_ERROR;
  if Assigned(SQLNativeSqlA) then
    Result := SQLNativeSqlA(HDbc,
      szSqlStrIn, cbSqlStrIn,
      szSqlStr, cbSqlStrMax, pcbSqlStr)
  else
  if Assigned(SQLNativeSqlW) then
  begin
    wszSqlStrIn := StrPas(PAnsiChar(@szSqlStrIn));
    if cbSqlStrMax > 0 then
    begin
      SetLength(wszSqlStr, cbSqlStrMax);
      FillChar( PWideChar(wszSqlStr)^, cbSqlStrMax*2, #0);
    end
    else
      wszSqlStr := '';
    pcbSqlStr := 0;

    Result := SQLNativeSqlW(HDbc,
      PSqlChar(PWideChar(wszSqlStrIn))^, cbSqlStrIn,
      PSqlChar(PWideChar(wszSqlStr))^, cbSqlStrMax, pcbSqlStr);

    if {(Result in [SQL_SUCCESS, SQL_SUCCESS_WITH_INFO]) and}  (pcbSqlStr >= 0) then
    begin
      SetLength(wszSqlStr, pcbSqlStr);
      sSqlStr := wszSqlStr;
      StrCopy( PAnsiChar(@szSqlStr), PAnsiChar(sSqlStr));
    end;
  end
  else
    NotImplemented('SQLNativeSql');
end;

function TOdbcApiProxy.SQLNumParams(HStmt: SqlHStmt;
  var pcpar: SqlSmallint): SqlReturn;
begin
  Result := SQL_ERROR;
  if Assigned(SQLNumParamsA) then
    Result := SQLNumParamsA(HStmt, pcpar)
  else
    NotImplemented('SQLNumParams');
end;

function TOdbcApiProxy.SQLNumResultCols(StatementHandle: SqlHStmt;
  var ColumnCount: SqlSmallint): SqlReturn;
begin
  Result := SQL_ERROR;
  if Assigned(SQLNumResultColsA) then
    Result := SQLNumResultColsA(StatementHandle, ColumnCount)
  else
    NotImplemented('SQLNumResultCols');
end;

function TOdbcApiProxy.SQLParamData(StatementHandle: SqlHStmt;
  var Value: SqlPointer): SqlReturn;
begin
  Result := SQL_ERROR;
  if Assigned(SQLParamDataA) then
    Result := SQLParamDataA(StatementHandle, Value)
  else
    NotImplemented('SQLParamData');
end;

function TOdbcApiProxy.SQLParamOptions(HStmt: SqlHStmt;
  crow: SqlUInteger; var pirow: SqlUInteger): SqlReturn;
begin
  Result := SQL_ERROR;
  if Assigned(SQLParamOptionsA) then
    Result := SQLParamOptionsA(HStmt, crow, pirow)
  else
    NotImplemented('SQLParamOptions');
end;

function TOdbcApiProxy.SQLPrepare(StatementHandle: SqlHStmt;
  StatementText: PAnsiChar; TextLength: SqlInteger): SqlReturn;
var
  wszStatementText: WideString;
begin
  Result := SQL_ERROR;
  if Assigned(SQLPrepareA) then
    Result := SQLPrepareA(StatementHandle, StatementText, TextLength)
  else
  if Assigned(SQLPrepareW) then
  begin
    wszStatementText := StrPas(StatementText);
    Result := SQLPrepareW(StatementHandle, PAnsiChar(PWideChar(wszStatementText)), TextLength);
  end
  else
    NotImplemented('SQLPrepare');
end;

function TOdbcApiProxy.SQLPrimaryKeys(HStmt: SqlHStmt;
  szCatalogName: PAnsiChar; cbCatalogName: SqlSmallint;
  szSchemaName: PAnsiChar; cbSchemaName: SqlSmallint;
  szTableName: PAnsiChar; cbTableName: SqlSmallint): SqlReturn;
var
  wszCatalogName, wszSchemaName, wszTableName: WideString;
begin
  Result := SQL_ERROR;
  if Assigned(SQLPrimaryKeysA) then
    Result := SQLPrimaryKeysA(HStmt,
      szCatalogName, cbCatalogName,
      szSchemaName, cbSchemaName,
      szTableName, cbTableName)
  else
  if Assigned(SQLPrimaryKeysW) then
  begin
    if Assigned(szCatalogName) then
    begin
      wszCatalogName := StrPas(szCatalogName);
      szCatalogName := PAnsiChar(PWideChar(wszCatalogName));
    end;
    if Assigned(szSchemaName) then
    begin
      wszSchemaName := StrPas(szSchemaName);
      szSchemaName := PAnsiChar(PWideChar(wszSchemaName));
    end;
    if Assigned(szTableName) then
    begin
      wszTableName := StrPas(szTableName);
      szTableName := PAnsiChar(PWideChar(wszTableName));
    end;

    Result := SQLPrimaryKeysW(HStmt,
      szCatalogName, cbCatalogName,
      szSchemaName, cbSchemaName,
      szTableName, cbTableName);
  end
  else
    NotImplemented('SQLPrimaryKeys');
end;

function TOdbcApiProxy.SQLProcedureColumns(HStmt: SqlHStmt;
  szCatalogName: PAnsiChar; cbCatalogName: SqlSmallint;
  szSchemaName: PAnsiChar; cbSchemaName: SqlSmallint;
  szProcName: PAnsiChar; cbProcName: SqlSmallint; szColumnName: PAnsiChar;
  cbColumnName: SqlSmallint): SqlReturn;
var
  wszCatalogName, wszSchemaName, wszProcName, wszColumnName: WideString;
begin
  Result := SQL_ERROR;
  if Assigned(SQLProcedureColumnsA) then
    Result := SQLProcedureColumnsA(HStmt,
      szCatalogName, cbCatalogName,
      szSchemaName, cbSchemaName,
      szProcName, cbProcName,
      szColumnName, cbColumnName)
  else
  if Assigned(SQLProcedureColumnsW) then
  begin
    if Assigned(szCatalogName) then
    begin
      wszCatalogName := StrPas(szCatalogName);
      szCatalogName := PAnsiChar(PWideChar(wszCatalogName));
    end;

    if Assigned(szSchemaName) then
    begin
      wszSchemaName := StrPas(szSchemaName);
      szSchemaName := PAnsiChar(PWideChar(wszSchemaName));
    end;

    if Assigned(szProcName) then
    begin
      wszProcName := StrPas(szProcName);
      szProcName := PAnsiChar(PWideChar(wszProcName));
    end;

    if Assigned(szColumnName) then
    begin
      wszColumnName := StrPas(szColumnName);
      szColumnName := PAnsiChar(PWideChar(wszColumnName));
    end;

    Result := SQLProcedureColumnsW(HStmt,
      szCatalogName, cbCatalogName,
      szSchemaName, cbSchemaName,
      szProcName, cbProcName,
      szColumnName, cbColumnName);
  end
  else
    NotImplemented('SQLProcedureColumns');
end;

function TOdbcApiProxy.SQLProcedures(HStmt: SqlHStmt;
  szCatalogName: PAnsiChar; cbCatalogName: SqlSmallint;
  szSchemaName: PAnsiChar; cbSchemaName: SqlSmallint;
  szProcName: PAnsiChar; cbProcName: SqlSmallint): SqlReturn;
var
  wszCatalogName, wszSchemaName, wszProcName: WideString;
begin
  Result := SQL_ERROR;
  if Assigned(SQLProceduresA) then
    Result := SQLProceduresA(HStmt,
      szCatalogName, cbCatalogName,
      szSchemaName, cbSchemaName,
      szProcName, cbProcName)
  else
  if Assigned(SQLProceduresW) then
  begin
    if Assigned(szCatalogName) then
    begin
      wszCatalogName := StrPas(szCatalogName);
      szCatalogName := PAnsiChar(PWideChar(wszCatalogName));
    end;
    if Assigned(szSchemaName) then
    begin
      wszSchemaName := StrPas(szSchemaName);
      szSchemaName := PAnsiChar(PWideChar(wszSchemaName));
    end;
    if Assigned(szProcName) then
    begin
      wszProcName := StrPas(szProcName);
      szProcName := PAnsiChar(PWideChar(wszProcName));
    end;

    Result := SQLProceduresW(HStmt,
      szCatalogName, cbCatalogName,
      szSchemaName, cbSchemaName,
      szProcName, cbProcName);
  end
  else
    NotImplemented('SQLProcedures');
end;

function TOdbcApiProxy.SQLPutData(StatementHandle: SqlHStmt;
  Data: SqlPointer; StrLen_or_Ind: SqlInteger): SqlReturn;
begin
  Result := SQL_ERROR;
  if Assigned(SQLPutDataA) then
    Result := SQLPutDataA(StatementHandle, Data, StrLen_or_Ind)
  else
    NotImplemented('SQLPutData');
end;

function TOdbcApiProxy.SQLRowCount(StatementHandle: SqlHStmt;
  var RowCount: SqlInteger): SqlReturn;
begin
  Result := SQL_ERROR;
  if Assigned(SQLRowCountA) then
    Result := SQLRowCountA(StatementHandle, RowCount)
  else
    NotImplemented('SQLRowCount');
end;

function TOdbcApiProxy.SQLSetConnectAttr(ConnectionHandle: SqlHDbc;
  Attribute: SqlInteger; ValuePtr: SqlPointer;
  StringLength: SqlInteger): SqlReturn;
var
  wszValuePtr: WideString;
  bHandleWS: Boolean;
begin
  Result := SQL_ERROR;
  if Assigned(SQLSetConnectAttrA) then
    Result := SQLSetConnectAttrA(ConnectionHandle, Attribute, ValuePtr, StringLength)
  else
  if Assigned(SQLSetConnectAttrW) then
  begin
    bHandleWS := (StringLength = SQL_NTS) or (StringLength>0) and (ValuePtr<>nil);
    if bHandleWS then
    begin
      wszValuePtr := StrPas(PAnsiChar(ValuePtr));
      ValuePtr := SqlPointer(PWideChar(wszValuePtr));
      StringLength := SQL_NTS;
    end;
    Result := SQLSetConnectAttrW(ConnectionHandle, Attribute, ValuePtr, StringLength);
  end
  else
  if Assigned(SQLSetConnectOptionA) or Assigned(SQLSetConnectOptionW) then
  begin
    Result := SQLSetConnectOption(ConnectionHandle, Attribute, SqlUInteger(ValuePtr) );
  end
  else
    NotImplemented('SQLSetConnectAttr');
end;

function TOdbcApiProxy.SQLSetConnectOption(
  ConnectionHandle: SqlHDbc; Option: SqlUSmallint;
  Value: SqlUInteger): SqlReturn;
begin
  Result := SQL_ERROR;
  if Assigned(SQLSetConnectOptionA) then
    Result := SQLSetConnectOptionA(ConnectionHandle, Option, Value)
  else
  if Assigned(SQLSetConnectOptionW) then
    Result := SQLSetConnectOptionW(ConnectionHandle, Option, Value)
  else
    NotImplemented('SQLSetConnectOption');
end;

function TOdbcApiProxy.SQLSetCursorName(StatementHandle: SqlHStmt;
  CursorName: PAnsiChar; NameLength: SqlSmallint): SqlReturn;
var
  wszCursorName: WideString;
begin
  Result := SQL_ERROR;
  if Assigned(SQLSetCursorNameA) then
    Result := SQLSetCursorNameA(StatementHandle, CursorName, NameLength)
  else
  if Assigned(SQLSetCursorNameW) then
  begin
    if Assigned(CursorName) then
    begin
      wszCursorName := StrPas(CursorName);
      CursorName := PAnsiChar(PWideChar(wszCursorName));
    end;
    Result := SQLSetCursorNameW(StatementHandle, CursorName, NameLength);
  end
  else
    NotImplemented('SQLSetCursorName');
end;

function TOdbcApiProxy.SQLSetDescField(DescriptorHandle: SqlHDesc;
  RecNumber, FieldIdentifier: SqlSmallint; Value: SqlPointer;
  BufferLength: SqlInteger): SqlReturn;
var
  wszValue: WideString;
begin
  Result := SQL_ERROR;
  if Assigned(SQLSetDescFieldA) then
    Result := SQLSetDescFieldA(DescriptorHandle, RecNumber, FieldIdentifier, Value, BufferLength)
  else
  if Assigned(SQLSetDescFieldW) then
  begin
    if Assigned(Value) then
    begin
      wszValue := StrPas(PAnsiChar(Value));
      Value := SqlPointer(PWideChar(wszValue));
    end;
    Result := SQLSetDescFieldW(DescriptorHandle, RecNumber, FieldIdentifier, Value, BufferLength);
  end
  else
    NotImplemented('SQLSetDescField');
end;

function TOdbcApiProxy.SQLSetDescRec(DescriptorHandle: SqlHDesc;
  RecNumber, _Type, SubType: SqlSmallint; Length: SqlInteger; Precision,
  Scale: SqlSmallint; Data: SqlPointer; var StringLength,
  Indicator: SqlInteger): SqlReturn;
begin
  Result := SQL_ERROR;
  if Assigned(SQLSetDescRecA) then
    Result := SQLSetDescRecA(DescriptorHandle, RecNumber, _Type, SubType, Length,
      Precision, Scale, Data, StringLength, Indicator)
  else
    NotImplemented('SQLSetDescRec');
end;

function TOdbcApiProxy.SQLSetEnvAttr(EnvironmentHandle: SqlHEnv;
  Attribute: SqlInteger; ValuePtr: Pointer;
  StringLength: SqlInteger): SqlReturn;
begin
  Result := SQL_ERROR;
  if Assigned(SQLSetEnvAttrA) then
    Result := SQLSetEnvAttrA(EnvironmentHandle, Attribute, ValuePtr, StringLength)
  else
    NotImplemented('SQLSetEnvAttr');
end;

function TOdbcApiProxy.SQLSetParam(StatementHandle: SqlHStmt;
  ParameterNumber: SqlUSmallint; ValueType, ParameterType: SqlSmallint;
  LengthPrecision: SqlUInteger; ParameterScale: SqlSmallint;
  ParameterValue: SqlPointer; var StrLen_or_Ind: SqlInteger): SqlReturn;
begin
  Result := SQL_ERROR;
  if Assigned(SQLSetParamA) then
    Result := SQLSetParamA(StatementHandle, ParameterNumber, ValueType, ParameterType,
      LengthPrecision, ParameterScale, ParameterValue, StrLen_or_Ind)
  else
    NotImplemented('SQLSetParam');
end;

function TOdbcApiProxy.SQLSetPos(HStmt: SqlHStmt; irow, fOption,
  fLock: SqlUSmallint): SqlReturn;
begin
  Result := SQL_ERROR;
  if Assigned(SQLSetPosA) then
    Result := SQLSetPosA(HStmt, irow, fOption, fLock)
  else
    NotImplemented('SQLSetPos');
end;

function TOdbcApiProxy.SQLSetScrollOptions(HStmt: SqlHStmt;
  fConcurrency: SqlUSmallint; crowKeyset: SqlInteger;
  crowRowset: SqlUSmallint): SqlReturn;
begin
  Result := SQL_ERROR;
  if Assigned(SQLSetScrollOptionsA) then
    Result := SQLSetScrollOptionsA(HStmt, fConcurrency, crowKeyset, crowRowset)
  else
    NotImplemented('SQLSetScrollOptions');
end;

function TOdbcApiProxy.SQLSetStmtAttr(StatementHandle: SqlHStmt;
  Attribute: SqlInteger; Value: SqlPointer;
  StringLength: SqlInteger): SqlReturn;
var
  bHandleWS: Boolean;
  wszValue: WideString;
  vValue: SqlPointer;
begin
  Result := SQL_ERROR;
  if Assigned(SQLSetStmtAttrA) then
    Result := SQLSetStmtAttrA(StatementHandle, Attribute, Value, StringLength)
  else
  if Assigned(SQLSetStmtAttrW) then
  begin
    bHandleWS := (StringLength > 0) and Assigned(Value);
    if bHandleWS then
    begin
      wszValue := StrPas(PAnsiChar(Value));
      vValue := PWideChar(wszValue);
    end
    else
      vValue := Value;
    Result := SQLSetStmtAttrW(StatementHandle, Attribute, vValue, StringLength);
  end
  else
  if Assigned(SQLSetStmtOptionA) then
  begin
    {if not (
      (Attribute >= SQL_STMT_OPT_MIN) and (Attribute <= SQL_STMT_OPT_MAX)
      or
      (Attribute >= SQL_CONNECT_OPT_DRVR_START)
    ) then
    }
    begin
      case Attribute of
        SQL_ATTR_USE_BOOKMARKS:
          begin
            Value := SQLPointer(SQL_UB_FIXED);
          end;
      end;//of: case
      Result := SQLSetStmtOption(StatementHandle, Attribute, SqlUInteger(Value));
    end;
  end
  else
    NotImplemented('SQLSetStmtAttr');
end;

function TOdbcApiProxy.SQLSetStmtOption(StatementHandle: SqlHStmt;
  Option: SqlUSmallint; Value: SqlUInteger): SqlReturn;
begin
  Result := SQL_ERROR;
  if Assigned(SQLSetStmtOptionA) then
    Result := SQLSetStmtOptionA(StatementHandle, Option, Value)
  else
    NotImplemented('SQLSetStmtOption');
end;

function TOdbcApiProxy.SQLSpecialColumns(StatementHandle: SqlHStmt;
  IdentifierType: SqlUSmallint; CatalogName: PAnsiChar;
  NameLength1: SqlSmallint; SchemaName: PAnsiChar;
  NameLength2: SqlSmallint; TableName: PAnsiChar; NameLength3: SqlSmallint;
  Scope, Nullable: SqlUSmallint): SqlReturn;
var
  wszCatalogName, wszSchemaName, wszTableName: WideString;
begin
  Result := SQL_ERROR;
  if Assigned(SQLSpecialColumnsA) then
    Result := SQLSpecialColumnsA(StatementHandle, IdentifierType,
      CatalogName, NameLength1,
      SchemaName, NameLength2,
      TableName, NameLength3,
      Scope, Nullable)
  else
  if Assigned(SQLSpecialColumnsW) then
  begin
    if Assigned(CatalogName) then
    begin
      wszCatalogName := StrPas(CatalogName);
      //NameLength1 := SQL_NTS;
      CatalogName := PAnsiChar(PWideChar(wszCatalogName));
    end;
    if Assigned(SchemaName) then
    begin
      wszSchemaName := StrPas(SchemaName);
      //NameLength2 := SQL_NTS;
      SchemaName := PAnsiChar(PWideChar(wszSchemaName));
    end;
    if Assigned(TableName) then
    begin
      wszTableName := StrPas(TableName);
      //NameLength3 := SQL_NTS;
      TableName := PAnsiChar(PWideChar(wszTableName));
    end;

    Result := SQLSpecialColumnsW(StatementHandle, IdentifierType,
      CatalogName, NameLength1,
      SchemaName, NameLength2,
      TableName, NameLength3,
      Scope, Nullable);
  end
  else
    NotImplemented('SQLSpecialColumns');
end;

function TOdbcApiProxy.SQLStatistics(StatementHandle: SqlHStmt;
  CatalogName: PAnsiChar; NameLength1: SqlSmallint; SchemaName: PAnsiChar;
  NameLength2: SqlSmallint; TableName: PAnsiChar; NameLength3: SqlSmallint;
  Unique, Reserved: SqlUSmallint): SqlReturn;
var
  wszCatalogName, wszSchemaName, wszTableName: WideString;
begin
  Result := SQL_ERROR;
  if Assigned(SQLStatisticsA) then
    Result := SQLStatisticsA(StatementHandle,
      CatalogName, NameLength1,
      SchemaName, NameLength2,
      TableName, NameLength3,
      Unique, Reserved)
  else
  if Assigned(SQLStatisticsW) then
  begin
    if CatalogName <> nil then
    begin
      wszCatalogName := StrPas(CatalogName);
      NameLength1 := SQL_NTS;//Length(wszCatalogName);
      CatalogName := PAnsiChar(PWideChar(wszCatalogName));
    end
    else
      NameLength1 := 0;
    if Assigned(SchemaName) then
    begin
      wszSchemaName := StrPas(SchemaName);
      NameLength2 := SQL_NTS;//Length(wszSchemaName);
      SchemaName := PAnsiChar(PWideChar(wszSchemaName));
    end
    else
      NameLength2 := 0;
    if Assigned(TableName) then
    begin
      wszTableName := StrPas(TableName);
      NameLength3 := SQL_NTS;//Length(wszTableName);
      TableName := PAnsiChar(PWideChar(wszTableName));
    end
    else
      NameLength3 := 0;

    Result := SQLStatisticsW(StatementHandle,
      CatalogName, NameLength1,
      SchemaName, NameLength2,
      TableName, NameLength3,
      Unique, Reserved)
  end
  else
    NotImplemented('SQLStatistics');
end;

function TOdbcApiProxy.SQLTablePrivileges(HStmt: SqlHStmt;
  var szCatalogName: SqlChar; cbCatalogName: SqlSmallint;
  var szSchemaName: SqlChar; cbSchemaName: SqlSmallint;
  var szTableName: SqlChar; cbTableName: SqlSmallint): SqlReturn;
var
  wszCatalogName, wszSchemaName, wszTableName: WideString;
begin
  Result := SQL_ERROR;
  if Assigned(SQLTablePrivilegesA) then
    Result := SQLTablePrivilegesA(HStmt,
      szCatalogName, cbCatalogName,
      szSchemaName, cbSchemaName,
      szTableName, cbTableName)
  else
  if Assigned(SQLTablePrivilegesW) then
  begin
    wszCatalogName := StrPas(PAnsiChar(@szCatalogName));
    //cbCatalogName := SQL_NTS;
    szCatalogName := PSqlChar(PWideChar(wszCatalogName))^;

    wszSchemaName := StrPas(PAnsiChar(@szSchemaName));
    //cbSchemaName := SQL_NTS;
    szSchemaName := PSqlChar(PWideChar(wszSchemaName))^;

    wszTableName := StrPas(PAnsiChar(@szTableName));
    //cbTableName := SQL_NTS;
    szTableName := PSqlChar(PWideChar(wszTableName))^;

    Result := SQLTablePrivilegesW(HStmt,
      szCatalogName, cbCatalogName,
      szSchemaName, cbSchemaName,
      szTableName, cbTableName);
  end
  else
    NotImplemented('SQLTablePrivileges');
end;

function TOdbcApiProxy.SQLTables(StatementHandle: SqlHStmt;
  CatalogName: PAnsiChar; NameLength1: SqlSmallint; SchemaName: PAnsiChar;
  NameLength2: SqlSmallint; TableName: PAnsiChar; NameLength3: SqlSmallint;
  TableType: PAnsiChar; NameLength4: SqlSmallint): SqlReturn;
var
  wszCatalogName, wszSchemaName, wszTableName, wszTableType: WideString;
begin
  Result := SQL_ERROR;
  if Assigned(SQLTablesA) then
    Result := SQLTablesA(StatementHandle,
      CatalogName, NameLength1,
      SchemaName, NameLength2,
      TableName, NameLength3,
      TableType, NameLength4)
  else
  if Assigned(SQLTablesW) then
  begin
    if CatalogName <> nil then
    begin
      wszCatalogName := StrPas(CatalogName);
      NameLength1 := SQL_NTS;//Length(wszCatalogName);
      CatalogName := PAnsiChar(PWideChar(wszCatalogName));
    end
    else
      NameLength1 := 0;
    if Assigned(SchemaName) then
    begin
      wszSchemaName := StrPas(SchemaName);
      NameLength2 := SQL_NTS;//Length(wszSchemaName);
      SchemaName := PAnsiChar(PWideChar(wszSchemaName));
    end
    else
      NameLength2 := 0;
    if Assigned(TableName) then
    begin
      wszTableName := StrPas(TableName);
      NameLength3 := SQL_NTS;//Length(wszTableName);
      TableName := PAnsiChar(PWideChar(wszTableName));
    end
    else
      NameLength3 := 0;
    if Assigned(TableType) then
    begin
      wszTableType := StrPas(TableType);
      NameLength4 := SQL_NTS;//Length(wszTableType);
      TableType := PAnsiChar(PWideChar(wszTableType));
    end
    else
      NameLength4 := 0;

    Result := SQLTablesW(StatementHandle,
      CatalogName, NameLength1,
      SchemaName, NameLength2,
      TableName, NameLength3,
      TableType, NameLength4);
  end
  else
    NotImplemented('SQLTables');
end;

function TOdbcApiProxy.SQLTransact(EnvironmentHandle: SqlHEnv;
  ConnectionHandle: SqlHDbc; CompletionType: SqlUSmallint): SqlReturn;
begin
  Result := SQL_ERROR;
  if Assigned(SQLTransactA) then
    Result := SQLTransactA(EnvironmentHandle, ConnectionHandle, CompletionType)
  else
    NotImplemented('SQLTransact');
end;

// ODBCTrac

function TOdbcApiProxy.TraceCloseLogFile: Retcode;
begin
  Result := SQL_ERROR;
  if Assigned(TraceCloseLogFileA) then
    Result := TraceCloseLogFileA()
  else
    NotImplemented('TraceCloseLogFile', OdbcApi_NotImplemented_OdbcTrac);
end;

function TOdbcApiProxy.TraceOpenLogFile(var _1, _2: WideChar;
  _3: Integer): Retcode;
begin
  Result := SQL_ERROR;
  if Assigned(TraceOpenLogFileA) then
    Result := TraceOpenLogFileA(_1, _2, _3)
  else
    NotImplemented('TraceOpenLogFile', OdbcApi_NotImplemented_OdbcTrac);
end;

procedure TOdbcApiProxy.TraceReturn(_1, _2: Retcode);
begin
  if Assigned(TraceReturnA) then
    TraceReturnA(_1, _2)
  else
    NotImplemented('TraceReturn', OdbcApi_NotImplemented_OdbcTrac);
end;

function TOdbcApiProxy.TraceVersion: Longint;
begin
  Result := SQL_ERROR;
  if Assigned(TraceVersionA) then
    Result := TraceVersionA()
  else
    NotImplemented('TraceVersion', OdbcApi_NotImplemented_OdbcTrac);
end;

function TOdbcApiProxy.TraceVSControl(_1: Integer): Retcode;
begin
  Result := SQL_ERROR;
  if Assigned(TraceVSControlA) then
    Result := TraceVSControlA(_1)
  else
    NotImplemented('TraceVSControl', OdbcApi_NotImplemented_OdbcTrac);
end;

procedure TOdbcApiProxy.FireVSDebugEvent(var Args: ODBC_VS_ARGS);
begin
  if Assigned(FireVSDebugEventA) then
    FireVSDebugEventA(Args)
  else
    NotImplemented('FireVSDebugEvent', OdbcApi_NotImplemented_OdbcTrac);
end;

// ODBCInst

function TOdbcApiProxy.ODBCGetTryWaitValue: Longint;
begin
  Result := SQL_ERROR;
  if Assigned(ODBCGetTryWaitValueA) then
    Result := ODBCGetTryWaitValueA
  else
    NotImplemented('ODBCGetTryWaitValue', OdbcApi_NotImplemented_OdbcInst);
end;

function TOdbcApiProxy.ODBCSetTryWaitValue(
  dwValue: Integer): LongBool;
begin
  Result := False;
  if Assigned(ODBCSetTryWaitValueA) then
    Result := ODBCSetTryWaitValueA(dwValue)
  else
    NotImplemented('ODBCSetTryWaitValue', OdbcApi_NotImplemented_OdbcInst);
end;

// MACROs

function TOdbcApiProxy.SQL_ADD_RECORD(HStmt: SqlHStmt; irow: SqlUSmallint): SqlReturn;
begin
  Result := SQLSetPos(HStmt, irow, SQL_ADD, SQL_LOCK_NO_CHANGE);
end;

function TOdbcApiProxy.SQL_DELETE_RECORD(HStmt: SqlHStmt;
  irow: SqlUSmallint): SqlReturn;
begin
  Result := SQLSetPos(HStmt, irow, SQL_DELETE, SQL_LOCK_NO_CHANGE);
end;

class function TOdbcApiProxy.SQL_FUNC_EXISTS(pfExists: PUWord; uwAPI: UWord): SqlInteger;
begin
  Inc(pfExists, uwAPI shr 4);
  if (pfExists^ and (1 shl (uwAPI and $000F))) <> 0 then
    Result := SQL_TRUE
  else
    Result := SQL_FALSE;
end;

class function TOdbcApiProxy.SQL_LEN_BINARY_ATTR(length: Integer): Integer;
begin
  Result := -(length) + SQL_LEN_BINARY_ATTR_OFFSET;
end;

class function TOdbcApiProxy.SQL_LEN_DATA_AT_EXEC(length: Integer): Integer;
begin
  Result := -(length) + SQL_LEN_DATA_AT_EXEC_OFFSET;
end;

function TOdbcApiProxy.SQL_LOCK_RECORD(HStmt: SqlHStmt; irow, fLock: SqlUSmallint): SqlReturn;
begin
  Result := SQLSetPos(HStmt, irow, SQL_POSITION, fLock);
end;

function TOdbcApiProxy.SQL_POSITION_TO(HStmt: SqlHStmt; irow: SqlUSmallint): SqlReturn;
begin
  Result := SQLSetPos(HStmt, irow, SQL_POSITION, SQL_LOCK_NO_CHANGE);
end;

function TOdbcApiProxy.SQL_REFRESH_RECORD(HStmt: SqlHStmt; irow, fLock: SqlUSmallint): SqlReturn;
begin
  Result := SQLSetPos(HStmt, irow, SQL_REFRESH, fLock);
end;

function TOdbcApiProxy.SQL_UPDATE_RECORD(HStmt: SqlHStmt; irow: SqlUSmallint): SqlReturn;
begin
  Result := SQLSetPos(HStmt, irow, SQL_UPDATE, SQL_LOCK_NO_CHANGE);
end;

{$ENDIF IFNDEF DynamicOdbcImport}

procedure TOdbcApiProxy.SetOdbcDriverLevel(aOdbcDriverLevel: Integer);
begin
  if not fSystemODBCManager then
  begin
    if (not fSystemODBCManager)
      and (
        (fOdbcDriverLevel < 0)
        or
        (aOdbcDriverLevel < fOdbcDriverLevel)
      ) then
    begin
      BeginLock;
      try
        fOdbcDriverLevel := aOdbcDriverLevel;
      finally
        EndLock;
      end;
    end;
  end
  else
  begin
    if (fOdbcDriverLevel < 0) then
    begin
      BeginLock;
      try
        fOdbcDriverLevel := aOdbcDriverLevel;
      finally
        EndLock;
      end;
    end;
  end;
end;

function TOdbcApiProxy.GetOdbcApiIntf: IUnknown;
begin
  {$IFDEF _iOdbcApi_}
  if fOdbcApiImpl = nil then
  begin
    fOdbcApiImpl := TOdbcApiIntfImpl.Create;
    fOdbcApiImpl.fOdbcApiProxy := Self;

    fOdbcApiIntf := fOdbcApiImpl;
  end;
    Result := fOdbcApiIntf;
  {$ELSE}
    Result := nil;
  {$ENDIF}
end;

{$IFDEF _iOdbcApi_}

{ TOdbcApiIntfImpl }

{$IFDEF DynamicOdbcImport}
procedure TOdbcApiIntfImpl.CheckAvailableProxy;
begin
  {$IFDEF DynamicOdbcImport}
    if fOdbcApiProxy = nil then
      raise EOdbcApi.Create('Linked OdbcApiProxy has been destroyed');
  {$ELSE}
  {$ENDIF}
end;
{$ENDIF}

procedure TOdbcApiIntfImpl.FireVSDebugEvent(var Args: ODBC_VS_ARGS);
begin
  {$IFDEF DynamicOdbcImport}
    CheckAvailableProxy;
    fOdbcApiProxy.FireVSDebugEvent(Args);
  {$ELSE}
    OdbcApi.FireVSDebugEvent(Args);
  {$ENDIF}
end;

function TOdbcApiIntfImpl.ODBCGetTryWaitValue: Longint;
begin
  {$IFDEF DynamicOdbcImport}
    CheckAvailableProxy;
    Result := fOdbcApiProxy.ODBCGetTryWaitValue;
  {$ELSE}
    Result := OdbcApi.ODBCGetTryWaitValue;
  {$ENDIF}
end;

function TOdbcApiIntfImpl.ODBCSetTryWaitValue(dwValue: Integer): LongBool;
begin
  {$IFDEF DynamicOdbcImport}
    CheckAvailableProxy;
    Result := fOdbcApiProxy.ODBCSetTryWaitValue(dwValue);
  {$ELSE}
    Result := OdbcApi.ODBCSetTryWaitValue(dwValue);
  {$ENDIF}
end;

function TOdbcApiIntfImpl.SQL_ADD_RECORD(HStmt: SqlHStmt;
  irow: SqlUSmallint): SqlReturn;
begin
  {$IFDEF DynamicOdbcImport}
    CheckAvailableProxy;
    Result := fOdbcApiProxy.SQL_ADD_RECORD(HStmt, irow);
  {$ELSE}
    Result := OdbcApi.SQL_ADD_RECORD(HStmt, irow);
  {$ENDIF}
end;

function TOdbcApiIntfImpl.SQL_DELETE_RECORD(HStmt: SqlHStmt;
  irow: SqlUSmallint): SqlReturn;
begin
  {$IFDEF DynamicOdbcImport}
    CheckAvailableProxy;
    Result := fOdbcApiProxy.SQL_DELETE_RECORD(HStmt, irow);
  {$ELSE}
    Result := OdbcApi.SQL_DELETE_RECORD(HStmt, irow);
  {$ENDIF}
end;

function TOdbcApiIntfImpl.SQL_FUNC_EXISTS(pfExists: PUWord;
  uwAPI: UWord): SqlInteger;
begin
  {$IFDEF DynamicOdbcImport}
    CheckAvailableProxy;
    Result := fOdbcApiProxy.SQL_FUNC_EXISTS(pfExists, uwAPI);
  {$ELSE}
    Result := OdbcApi.SQL_FUNC_EXISTS(pfExists, uwAPI);
  {$ENDIF}
end;

function TOdbcApiIntfImpl.SQL_LEN_BINARY_ATTR(length: Integer): Integer;
begin
  {$IFDEF DynamicOdbcImport}
    CheckAvailableProxy;
    Result := fOdbcApiProxy.SQL_LEN_BINARY_ATTR(length);
  {$ELSE}
    Result := OdbcApi.SQL_LEN_BINARY_ATTR(length);
  {$ENDIF}
end;

function TOdbcApiIntfImpl.SQL_LEN_DATA_AT_EXEC(length: Integer): Integer;
begin
  {$IFDEF DynamicOdbcImport}
    CheckAvailableProxy;
    Result := fOdbcApiProxy.SQL_LEN_DATA_AT_EXEC(length);
  {$ELSE}
    Result := OdbcApi.SQL_LEN_DATA_AT_EXEC(length);
  {$ENDIF}
end;

function TOdbcApiIntfImpl.SQL_LOCK_RECORD(HStmt: SqlHStmt; irow,
  fLock: SqlUSmallint): SqlReturn;
begin
  {$IFDEF DynamicOdbcImport}
    CheckAvailableProxy;
    Result := fOdbcApiProxy.SQL_LOCK_RECORD(HStmt, irow, fLock);
  {$ELSE}
    Result := OdbcApi.SQL_LOCK_RECORD(HStmt, irow, fLock);
  {$ENDIF}
end;

function TOdbcApiIntfImpl.SQL_POSITION_TO(HStmt: SqlHStmt;
  irow: SqlUSmallint): SqlReturn;
begin
  {$IFDEF DynamicOdbcImport}
    CheckAvailableProxy;
    Result := fOdbcApiProxy.SQL_POSITION_TO(HStmt, irow);
  {$ELSE}
    Result := OdbcApi.SQL_POSITION_TO(HStmt, irow);
  {$ENDIF}
end;

function TOdbcApiIntfImpl.SQL_REFRESH_RECORD(HStmt: SqlHStmt; irow,
  fLock: SqlUSmallint): SqlReturn;
begin
  {$IFDEF DynamicOdbcImport}
    CheckAvailableProxy;
    Result := fOdbcApiProxy.SQL_REFRESH_RECORD(HStmt, irow, fLock);
  {$ELSE}
    Result := OdbcApi.SQL_REFRESH_RECORD(HStmt, irow, fLock);
  {$ENDIF}
end;

function TOdbcApiIntfImpl.SQL_UPDATE_RECORD(HStmt: SqlHStmt;
  irow: SqlUSmallint): SqlReturn;
begin
  {$IFDEF DynamicOdbcImport}
    CheckAvailableProxy;
    Result := fOdbcApiProxy.SQL_UPDATE_RECORD(HStmt, irow);
  {$ELSE}
    Result := OdbcApi.SQL_UPDATE_RECORD(HStmt, irow);
  {$ENDIF}
end;

function TOdbcApiIntfImpl.SQLAllocConnect(EnvironmentHandle: SqlHEnv;
  var ConnectionHandle: SqlHDbc): SqlReturn;
begin
  {$IFDEF DynamicOdbcImport}
    CheckAvailableProxy;
    Result := fOdbcApiProxy.SQLAllocConnect(EnvironmentHandle, ConnectionHandle);
  {$ELSE}
    Result := OdbcApi.SQLAllocConnect(EnvironmentHandle, ConnectionHandle);
  {$ENDIF}
end;

function TOdbcApiIntfImpl.SQLAllocEnv(var EnvironmentHandle: SqlHEnv): SqlReturn;
begin
  {$IFDEF DynamicOdbcImport}
    CheckAvailableProxy;
    Result := fOdbcApiProxy.SQLAllocEnv(EnvironmentHandle);
  {$ELSE}
    Result := OdbcApi.SQLAllocEnv(EnvironmentHandle);
  {$ENDIF}
end;

function TOdbcApiIntfImpl.SQLAllocHandle(HandleType: SqlSmallint;
  InputHandle: SqlHandle; var OutputHandle: SqlHandle): SqlReturn;
begin
  {$IFDEF DynamicOdbcImport}
    CheckAvailableProxy;
    Result := fOdbcApiProxy.SQLAllocHandle(HandleType, InputHandle, OutputHandle);
  {$ELSE}
    Result := OdbcApi.SQLAllocHandle(HandleType, InputHandle, OutputHandle);
  {$ENDIF}
end;

function TOdbcApiIntfImpl.SQLAllocHandleStd(fHandleType: SqlSmallint;
  hInput: SqlHandle; var phOutput: SqlHandle): SqlReturn;
begin
  {$IFDEF DynamicOdbcImport}
    CheckAvailableProxy;
    Result := fOdbcApiProxy.SQLAllocHandleStd(fHandleType, hInput, phOutput);
  {$ELSE}
    Result := OdbcApi.SQLAllocHandleStd(fHandleType, hInput, phOutput);
  {$ENDIF}
end;

function TOdbcApiIntfImpl.SQLAllocStmt(ConnectionHandle: SqlHDbc;
  var StatementHandle: SqlHStmt): SqlReturn;
begin
  {$IFDEF DynamicOdbcImport}
    CheckAvailableProxy;
    Result := fOdbcApiProxy.SQLAllocStmt(ConnectionHandle, StatementHandle);
  {$ELSE}
    Result := OdbcApi.SQLAllocStmt(ConnectionHandle, StatementHandle);
  {$ENDIF}
end;

function TOdbcApiIntfImpl.SQLBindCol(StatementHandle: SqlHStmt;
  ColumnNumber: SqlUSmallint; TargetType: SqlSmallint;
  TargetValue: SqlPointer; BufferLength: SqlInteger;
  StrLen_or_Ind: PSqlInteger): SqlReturn;
begin
  {$IFDEF DynamicOdbcImport}
    CheckAvailableProxy;
    Result := fOdbcApiProxy.SQLBindCol(StatementHandle, ColumnNumber, TargetType, TargetValue,
      BufferLength, StrLen_or_Ind);
  {$ELSE}
    Result := OdbcApi.SQLBindCol(StatementHandle, ColumnNumber, TargetType, TargetValue,
      BufferLength, StrLen_or_Ind);
  {$ENDIF}
end;

function TOdbcApiIntfImpl.SQLBindParam(StatementHandle: SqlHStmt;
  ParameterNumber: SqlUSmallint; ValueType, ParameterType: SqlSmallint;
  LengthPrecision: SqlUInteger; ParameterScale: SqlSmallint;
  ParameterValue: SqlPointer; var StrLen_or_Ind: SqlInteger): SqlReturn;
begin
  {$IFDEF DynamicOdbcImport}
    CheckAvailableProxy;
    Result := fOdbcApiProxy.SQLBindParam(StatementHandle, ParameterNumber, ValueType,
      ParameterType, LengthPrecision, ParameterScale, ParameterValue, StrLen_or_Ind);
  {$ELSE}
    Result := OdbcApi.SQLBindParam(StatementHandle, ParameterNumber, ValueType,
      ParameterType, LengthPrecision, ParameterScale, ParameterValue, StrLen_or_Ind);
  {$ENDIF}
end;

function TOdbcApiIntfImpl.SQLBindParameter(HStmt: SqlHStmt;
  ipar: SqlUSmallint; fParamType, fCType, fSqlType: SqlSmallint;
  cbColDef: SqlUInteger; ibScale: SqlSmallint; rgbValue: SqlPointer;
  cbValueMax: SqlInteger; pcbValue: PSqlInteger): SqlReturn;
begin
  {$IFDEF DynamicOdbcImport}
    CheckAvailableProxy;
    Result := fOdbcApiProxy.SQLBindParameter(HStmt, ipar, fParamType, fCType, fSqlType,
      cbColDef, ibScale, rgbValue, cbValueMax, pcbValue);
  {$ELSE}
    Result := OdbcApi.SQLBindParameter(HStmt, ipar, fParamType, fCType, fSqlType,
      cbColDef, ibScale, rgbValue, cbValueMax, pcbValue);
  {$ENDIF}
end;

function TOdbcApiIntfImpl.SQLBrowseConnect(HDbc: SqlHDbc;
  var szConnStrIn: SqlChar; cbConnStrIn: SqlSmallint;
  var szConnStrOut: SqlChar; cbConnStrOutMax: SqlSmallint;
  var pcbConnStrOut: SqlSmallint): SqlReturn;
begin
  {$IFDEF DynamicOdbcImport}
    CheckAvailableProxy;
    Result := fOdbcApiProxy.SQLBrowseConnect(HDbc, szConnStrIn, cbConnStrIn, szConnStrOut,
      cbConnStrOutMax, pcbConnStrOut);
  {$ELSE}
    Result := OdbcApi.SQLBrowseConnect(HDbc, szConnStrIn, cbConnStrIn, szConnStrOut,
      cbConnStrOutMax, pcbConnStrOut);
  {$ENDIF}
end;

function TOdbcApiIntfImpl.SQLBulkOperations(StatementHandle: SqlHStmt;
  Operation: SqlSmallint): SqlReturn;
begin
  {$IFDEF DynamicOdbcImport}
    CheckAvailableProxy;
    Result := fOdbcApiProxy.SQLBulkOperations(StatementHandle, Operation);
  {$ELSE}
    Result := OdbcApi.SQLBulkOperations(StatementHandle, Operation);
  {$ENDIF}
end;

function TOdbcApiIntfImpl.SQLCancel(StatementHandle: SqlHStmt): SqlReturn;
begin
  {$IFDEF DynamicOdbcImport}
    CheckAvailableProxy;
    Result := fOdbcApiProxy.SQLCancel(StatementHandle);
  {$ELSE}
    Result := OdbcApi.SQLCancel(StatementHandle);
  {$ENDIF}
end;

function TOdbcApiIntfImpl.SQLCloseCursor(StatementHandle: SqlHStmt): SqlReturn;
begin
  {$IFDEF DynamicOdbcImport}
    CheckAvailableProxy;
    Result := fOdbcApiProxy.SQLCloseCursor(StatementHandle);
  {$ELSE}
    Result := OdbcApi.SQLCloseCursor(StatementHandle);
  {$ENDIF}
end;

function TOdbcApiIntfImpl.SQLColAttribute(StatementHandle: SqlHStmt;
  ColumnNumber, FieldIdentifier: SqlUSmallint;
  CharacterAttribute: SqlPointer; BufferLength: SqlSmallint;
  StringLength: pSqlSmallint; NumericAttributePtr: SqlPointer): SqlReturn;
begin
  {$IFDEF DynamicOdbcImport}
    CheckAvailableProxy;
    Result := fOdbcApiProxy.SQLColAttribute(StatementHandle, ColumnNumber, FieldIdentifier,
      CharacterAttribute, BufferLength, StringLength, NumericAttributePtr);
  {$ELSE}
    Result := OdbcApi.SQLColAttribute(StatementHandle, ColumnNumber, FieldIdentifier,
      CharacterAttribute, BufferLength, StringLength, NumericAttributePtr);
  {$ENDIF}
end;

function TOdbcApiIntfImpl.SQLColAttributeInt(StatementHandle: SqlHStmt;
  ColumnNumber, FieldIdentifier: SqlUSmallint;
  CharacterAttribute: SqlPointer; BufferLength: SqlSmallint;
  StringLength: pSqlSmallint; var NumericAttribute: SqlInteger): SqlReturn;
begin
  {$IFDEF DynamicOdbcImport}
    CheckAvailableProxy;
    Result := fOdbcApiProxy.SQLColAttributeInt(StatementHandle, ColumnNumber, FieldIdentifier,
      CharacterAttribute, BufferLength, StringLength, NumericAttribute);
  {$ELSE}
    Result := OdbcApi.SQLColAttributeInt(StatementHandle, ColumnNumber, FieldIdentifier,
      CharacterAttribute, BufferLength, StringLength, NumericAttribute);
  {$ENDIF}
end;

function TOdbcApiIntfImpl.SQLColAttributes(HStmt: SqlHStmt; icol,
  fDescType: SqlUSmallint; rgbDesc: SqlPointer; cbDescMax: SqlSmallint;
  var pcbDesc: SqlSmallint; var pfDesc: SqlInteger): SqlReturn;
begin
  {$IFDEF DynamicOdbcImport}
    CheckAvailableProxy;
    Result := fOdbcApiProxy.SQLColAttributes(HStmt, icol, fDescType, rgbDesc, cbDescMax,
      pcbDesc, pfDesc);
  {$ELSE}
    Result := OdbcApi.SQLColAttributes(HStmt, icol, fDescType, rgbDesc, cbDescMax,
      pcbDesc, pfDesc);
  {$ENDIF}
end;

function TOdbcApiIntfImpl.SQLColAttributeString(StatementHandle: SqlHStmt;
  ColumnNumber, FieldIdentifier: SqlUSmallint;
  CharacterAttribute: SqlPointer; BufferLength: SqlSmallint;
  var StringLength: SqlSmallint; NumericAttribute: SqlPointer): SqlReturn;
begin
  {$IFDEF DynamicOdbcImport}
    CheckAvailableProxy;
    Result := fOdbcApiProxy.SQLColAttributeString(StatementHandle, ColumnNumber, FieldIdentifier,
      CharacterAttribute, BufferLength, StringLength, NumericAttribute);
  {$ELSE}
    Result := OdbcApi.SQLColAttributeString(StatementHandle, ColumnNumber, FieldIdentifier,
      CharacterAttribute, BufferLength, StringLength, NumericAttribute);
  {$ENDIF}
end;

function TOdbcApiIntfImpl.SQLColumnPrivileges(HStmt: SqlHStmt;
  var szCatalogName: SqlChar; cbCatalogName: SqlSmallint;
  var szSchemaName: SqlChar; cbSchemaName: SqlSmallint;
  var szTableName: SqlChar; cbTableName: SqlSmallint;
  var szColumnName: SqlChar; cbColumnName: SqlSmallint): SqlReturn;
begin
  {$IFDEF DynamicOdbcImport}
    CheckAvailableProxy;
    Result := fOdbcApiProxy.SQLColumnPrivileges(HStmt, szCatalogName, cbCatalogName,
      szSchemaName, cbSchemaName, szTableName, cbTableName, szColumnName, cbColumnName);
  {$ELSE}
    Result := OdbcApi.SQLColumnPrivileges(HStmt, szCatalogName, cbCatalogName,
      szSchemaName, cbSchemaName, szTableName, cbTableName, szColumnName, cbColumnName);
  {$ENDIF}
end;

function TOdbcApiIntfImpl.SQLColumns(StatementHandle: SqlHStmt;
  CatalogName: PAnsiChar; NameLength1: SqlSmallint; SchemaName: PAnsiChar;
  NameLength2: SqlSmallint; TableName: PAnsiChar; NameLength3: SqlSmallint;
  ColumnName: PAnsiChar; NameLength4: SqlSmallint): SqlReturn;
begin
  {$IFDEF DynamicOdbcImport}
    CheckAvailableProxy;
    Result := fOdbcApiProxy.SQLColumns(StatementHandle, CatalogName, NameLength1, SchemaName,
      NameLength2, TableName, NameLength3, ColumnName, NameLength4);
  {$ELSE}
    Result := OdbcApi.SQLColumns(StatementHandle, CatalogName, NameLength1, SchemaName,
      NameLength2, TableName, NameLength3, ColumnName, NameLength4);
  {$ENDIF}
end;

function TOdbcApiIntfImpl.SQLConnect(ConnectionHandle: SqlHDbc;
  ServerName: PAnsiChar; NameLength1: SqlSmallint; UserName: PAnsiChar;
  NameLength2: SqlSmallint; Authentication: PAnsiChar;
  NameLength3: SqlSmallint): SqlReturn;
begin
  {$IFDEF DynamicOdbcImport}
    CheckAvailableProxy;
    Result := fOdbcApiProxy.SQLConnect(ConnectionHandle, ServerName, NameLength1, UserName,
      NameLength2, Authentication, NameLength3);
  {$ELSE}
    Result := OdbcApi.SQLConnect(ConnectionHandle, ServerName, NameLength1, UserName,
      NameLength2, Authentication, NameLength3);
  {$ENDIF}
end;

function TOdbcApiIntfImpl.SQLCopyDesc(SourceDescHandle,
  TargetDescHandle: SqlHDesc): SqlReturn;
begin
  {$IFDEF DynamicOdbcImport}
    CheckAvailableProxy;
    Result := fOdbcApiProxy.SQLCopyDesc(SourceDescHandle, TargetDescHandle);
  {$ELSE}
    Result := OdbcApi.SQLCopyDesc(SourceDescHandle, TargetDescHandle);
  {$ENDIF}
end;

function TOdbcApiIntfImpl.SQLDataSources(EnvironmentHandle: SqlHEnv;
  Direction: SqlUSmallint; var ServerName: SqlChar;
  BufferLength1: SqlSmallint; var NameLength1: SqlSmallint;
  var Description: SqlChar; BufferLength2: SqlSmallint;
  var NameLength2: SqlSmallint): SqlReturn;
begin
  {$IFDEF DynamicOdbcImport}
    CheckAvailableProxy;
    Result := fOdbcApiProxy.SQLDataSources(EnvironmentHandle, Direction, ServerName, BufferLength1,
      NameLength1, Description, BufferLength2, NameLength2);
  {$ELSE}
    Result := OdbcApi.SQLDataSources(EnvironmentHandle, Direction, ServerName, BufferLength1,
      NameLength1, Description, BufferLength2, NameLength2);
  {$ENDIF}
end;

function TOdbcApiIntfImpl.SQLDescribeCol(StatementHandle: SqlHStmt;
  ColumnNumber: SqlUSmallint; ColumnName: PAnsiChar;
  BufferLength: SqlSmallint; var NameLength, DataType: SqlSmallint;
  var ColumnSize: SqlUInteger; var DecimalDigits,
  Nullable: SqlSmallint): SqlReturn;
begin
  {$IFDEF DynamicOdbcImport}
    CheckAvailableProxy;
    Result := fOdbcApiProxy.SQLDescribeCol(StatementHandle, ColumnNumber, ColumnName,
      BufferLength, NameLength, DataType, ColumnSize, DecimalDigits, Nullable);
  {$ELSE}
    Result := OdbcApi.SQLDescribeCol(StatementHandle, ColumnNumber, ColumnName,
      BufferLength, NameLength, DataType, ColumnSize, DecimalDigits, Nullable);
  {$ENDIF}
end;

function TOdbcApiIntfImpl.SQLDescribeParam(HStmt: SqlHStmt;
  ipar: SqlUSmallint; var pfSqlType: SqlSmallint;
  var pcbParamDef: SqlUInteger; var pibScale,
  pfNullable: SqlSmallint): SqlReturn;
begin
  {$IFDEF DynamicOdbcImport}
    CheckAvailableProxy;
    Result := fOdbcApiProxy.SQLDescribeParam(HStmt, ipar, pfSqlType, pcbParamDef,
      pibScale, pfNullable);
  {$ELSE}
    Result := OdbcApi.SQLDescribeParam(HStmt, ipar, pfSqlType, pcbParamDef,
      pibScale, pfNullable);
  {$ENDIF}
end;

function TOdbcApiIntfImpl.SQLDisconnect(ConnectionHandle: SqlHDbc): SqlReturn;
begin
  {$IFDEF DynamicOdbcImport}
    CheckAvailableProxy;
    Result := fOdbcApiProxy.SQLDisconnect(ConnectionHandle);
  {$ELSE}
    Result := OdbcApi.SQLDisconnect(ConnectionHandle);
  {$ENDIF}
end;

function TOdbcApiIntfImpl.SQLDriverConnect(HDbc: SqlHDbc; hwnd: SqlHWnd;
  szConnStrIn: PAnsiChar; cbConnStrIn: SqlSmallint;
  szConnStrOut: PAnsiChar; cbConnStrOutMax: SqlSmallint;
  var pcbConnStrOut: SqlSmallint;
  fDriverCompletion: SqlUSmallint): SqlReturn;
begin
  {$IFDEF DynamicOdbcImport}
    CheckAvailableProxy;
    Result := fOdbcApiProxy.SQLDriverConnect(HDbc, hwnd, szConnStrIn, cbConnStrIn,
      szConnStrOut, cbConnStrOutMax, pcbConnStrOut, fDriverCompletion);
  {$ELSE}
    Result := OdbcApi.SQLDriverConnect(HDbc, hwnd, szConnStrIn, cbConnStrIn,
      szConnStrOut, cbConnStrOutMax, pcbConnStrOut, fDriverCompletion);
  {$ENDIF}
end;

function TOdbcApiIntfImpl.SQLDrivers(HEnv: SqlHEnv;
  fDirection: SqlUSmallint; szDriverDesc: PAnsiChar;
  cbDriverDescMax: SqlSmallint; var pcbDriverDesc: SqlSmallint;
  szDriverAttributes: PAnsiChar; cbDrvrAttrMax: SqlSmallint;
  var pcbDrvrAttr: SqlSmallint): SqlReturn;
begin
  {$IFDEF DynamicOdbcImport}
    CheckAvailableProxy;
    Result := fOdbcApiProxy.SQLDrivers(HEnv, fDirection, szDriverDesc, cbDriverDescMax,
      pcbDriverDesc, szDriverAttributes, cbDrvrAttrMax, pcbDrvrAttr);
  {$ELSE}
    Result := OdbcApi.SQLDrivers(HEnv, fDirection, szDriverDesc, cbDriverDescMax,
      pcbDriverDesc, szDriverAttributes, cbDrvrAttrMax, pcbDrvrAttr);
  {$ENDIF}
end;

function TOdbcApiIntfImpl.SQLEndTran(HandleType: SqlSmallint;
  Handle: SqlHandle; CompletionType: SqlSmallint): SqlReturn;
begin
  {$IFDEF DynamicOdbcImport}
    CheckAvailableProxy;
    Result := fOdbcApiProxy.SQLEndTran(HandleType, Handle, CompletionType);
  {$ELSE}
    Result := OdbcApi.SQLEndTran(HandleType, Handle, CompletionType);
  {$ENDIF}
end;

function TOdbcApiIntfImpl.SQLError(EnvironmentHandle: SqlHEnv;
  ConnectionHandle: SqlHDbc; StatementHandle: SqlHStmt;
  var Sqlstate: SqlChar; var NativeError: SqlInteger;
  var MessageText: SqlChar; BufferLength: SqlSmallint;
  var TextLength: SqlSmallint): SqlReturn;
begin
  {$IFDEF DynamicOdbcImport}
    CheckAvailableProxy;
    Result := fOdbcApiProxy.SQLError(EnvironmentHandle, ConnectionHandle, StatementHandle,
      Sqlstate, NativeError, MessageText, BufferLength, TextLength);
  {$ELSE}
    Result := OdbcApi.SQLError(EnvironmentHandle, ConnectionHandle, StatementHandle,
      Sqlstate, NativeError, MessageText, BufferLength, TextLength);
  {$ENDIF}
end;

function TOdbcApiIntfImpl.SQLExecDirect(StatementHandle: SqlHStmt;
  StatementText: PAnsiChar; TextLength: SqlInteger): SqlReturn;
begin
  {$IFDEF DynamicOdbcImport}
    CheckAvailableProxy;
    Result := fOdbcApiProxy.SQLExecDirect(StatementHandle, StatementText, TextLength);
  {$ELSE}
    Result := OdbcApi.SQLExecDirect(StatementHandle, StatementText, TextLength);
  {$ENDIF}
end;

function TOdbcApiIntfImpl.SQLExecute(StatementHandle: SqlHStmt): SqlReturn;
begin
  {$IFDEF DynamicOdbcImport}
    CheckAvailableProxy;
    Result := fOdbcApiProxy.SQLExecute(StatementHandle);
  {$ELSE}
    Result := OdbcApi.SQLExecute(StatementHandle);
  {$ENDIF}
end;

function TOdbcApiIntfImpl.SQLExtendedFetch(HStmt: SqlHStmt;
  fFetchType: SqlUSmallint; irow: SqlInteger; var pcrow: SqlUInteger;
  var rgfRowStatus: SqlUSmallint): SqlReturn;
begin
  {$IFDEF DynamicOdbcImport}
    CheckAvailableProxy;
    Result := fOdbcApiProxy.SQLExtendedFetch(HStmt, fFetchType, irow, pcrow, rgfRowStatus);
  {$ELSE}
    Result := OdbcApi.SQLExtendedFetch(HStmt, fFetchType, irow, pcrow, rgfRowStatus);
  {$ENDIF}
end;

function TOdbcApiIntfImpl.SQLFetch(StatementHandle: SqlHStmt): SqlReturn;
begin
  {$IFDEF DynamicOdbcImport}
    CheckAvailableProxy;
    Result := fOdbcApiProxy.SQLFetch(StatementHandle);
  {$ELSE}
    Result := OdbcApi.SQLFetch(StatementHandle);
  {$ENDIF}
end;

function TOdbcApiIntfImpl.SQLFetchScroll(StatementHandle: SqlHStmt;
  FetchOrientation: SqlSmallint; FetchOffset: SqlInteger): SqlReturn;
begin
  {$IFDEF DynamicOdbcImport}
    CheckAvailableProxy;
    Result := fOdbcApiProxy.SQLFetchScroll(StatementHandle, FetchOrientation, FetchOffset);
  {$ELSE}
    Result := OdbcApi.SQLFetchScroll(StatementHandle, FetchOrientation, FetchOffset);
  {$ENDIF}
end;

function TOdbcApiIntfImpl.SQLForeignKeys(HStmt: SqlHStmt;
  var szPkCatalogName: SqlChar; cbPkCatalogName: SqlSmallint;
  var szPkSchemaName: SqlChar; cbPkSchemaName: SqlSmallint;
  var szPkTableName: SqlChar; cbPkTableName: SqlSmallint;
  var szFkCatalogName: SqlChar; cbFkCatalogName: SqlSmallint;
  var szFkSchemaName: SqlChar; cbFkSchemaName: SqlSmallint;
  var szFkTableName: SqlChar; cbFkTableName: SqlSmallint): SqlReturn;
begin
  {$IFDEF DynamicOdbcImport}
    CheckAvailableProxy;
    Result := fOdbcApiProxy.SQLForeignKeys(HStmt, szPkCatalogName, cbPkCatalogName,
      szPkSchemaName, cbPkSchemaName, szPkTableName, cbPkTableName, szFkCatalogName,
      cbFkCatalogName, szFkSchemaName, cbFkSchemaName, szFkTableName, cbFkTableName);
  {$ELSE}
    Result := OdbcApi.SQLForeignKeys(HStmt, szPkCatalogName, cbPkCatalogName,
      szPkSchemaName, cbPkSchemaName, szPkTableName, cbPkTableName, szFkCatalogName,
      cbFkCatalogName, szFkSchemaName, cbFkSchemaName, szFkTableName, cbFkTableName);
  {$ENDIF}
end;

function TOdbcApiIntfImpl.SQLFreeConnect(ConnectionHandle: SqlHDbc): SqlReturn;
begin
  {$IFDEF DynamicOdbcImport}
    CheckAvailableProxy;
    Result := fOdbcApiProxy.SQLFreeConnect(ConnectionHandle);
  {$ELSE}
    Result := OdbcApi.SQLFreeConnect(ConnectionHandle);
  {$ENDIF}
end;

function TOdbcApiIntfImpl.SQLFreeEnv(EnvironmentHandle: SqlHEnv): SqlReturn;
begin
  {$IFDEF DynamicOdbcImport}
    CheckAvailableProxy;
    Result := fOdbcApiProxy.SQLFreeEnv(EnvironmentHandle);
  {$ELSE}
    Result := OdbcApi.SQLFreeEnv(EnvironmentHandle);
  {$ENDIF}
end;

function TOdbcApiIntfImpl.SQLFreeHandle(HandleType: SqlSmallint; Handle: SqlHandle): SqlReturn;
begin
  {$IFDEF DynamicOdbcImport}
    CheckAvailableProxy;
    Result := fOdbcApiProxy.SQLFreeHandle(HandleType, Handle);
  {$ELSE}
    Result := OdbcApi.SQLFreeHandle(HandleType, Handle);
  {$ENDIF}
end;

function TOdbcApiIntfImpl.SQLFreeStmt(StatementHandle: SqlHStmt; Option: SqlUSmallint): SqlReturn;
begin
  {$IFDEF DynamicOdbcImport}
    CheckAvailableProxy;
    Result := fOdbcApiProxy.SQLFreeStmt(StatementHandle, Option);
  {$ELSE}
    Result := OdbcApi.SQLFreeStmt(StatementHandle, Option);
  {$ENDIF}
end;

function TOdbcApiIntfImpl.SQLFunctionSupported(ConnectionHandle: SqlHDbc;
  FunctionId: SqlUSmallint): Boolean;
begin
  {$IFDEF DynamicOdbcImport}
    CheckAvailableProxy;
    Result := fOdbcApiProxy.SQLFunctionSupported(ConnectionHandle, FunctionId);
  {$ELSE}
    Result := OdbcApi.SQLFunctionSupported(ConnectionHandle, FunctionId);
  {$ENDIF}
end;

function TOdbcApiIntfImpl.SQLGetConnectAttr(ConnectionHandle: SqlHDbc;
  Attribute: SqlInteger; ValuePtr: SqlPointer; BufferLength: SqlInteger;
  pStringLength: PSqlInteger): SqlReturn;
begin
  {$IFDEF DynamicOdbcImport}
    CheckAvailableProxy;
    Result := fOdbcApiProxy.SQLGetConnectAttr(ConnectionHandle, Attribute, ValuePtr,
      BufferLength, pStringLength);
  {$ELSE}
    Result := OdbcApi.SQLGetConnectAttr(ConnectionHandle, Attribute, ValuePtr,
      BufferLength, pStringLength);
  {$ENDIF}
end;

function TOdbcApiIntfImpl.SQLGetConnectOption(ConnectionHandle: SqlHDbc;
  Option: SqlUSmallint; Value: SqlPointer): SqlReturn;
begin
  {$IFDEF DynamicOdbcImport}
    CheckAvailableProxy;
    Result := fOdbcApiProxy.SQLGetConnectOption(ConnectionHandle, Option, Value);
  {$ELSE}
    Result := OdbcApi.SQLGetConnectOption(ConnectionHandle, Option, Value);
  {$ENDIF}
end;

function TOdbcApiIntfImpl.SQLGetCursorName(StatementHandle: SqlHStmt;
  CursorName: PAnsiChar; BufferLength: SqlSmallint;
  var NameLength: SqlSmallint): SqlReturn;
begin
  {$IFDEF DynamicOdbcImport}
    CheckAvailableProxy;
    Result := fOdbcApiProxy.SQLGetCursorName(StatementHandle, CursorName, BufferLength, NameLength);
  {$ELSE}
    Result := OdbcApi.SQLGetCursorName(StatementHandle, CursorName, BufferLength, NameLength);
  {$ENDIF}
end;

function TOdbcApiIntfImpl.SQLGetData(StatementHandle: SqlHStmt;
  ColumnNumber: SqlUSmallint; TargetType: SqlSmallint;
  TargetValue: SqlPointer; BufferLength: SqlInteger;
  StrLen_or_Ind: PSqlInteger): SqlReturn;
begin
  {$IFDEF DynamicOdbcImport}
    CheckAvailableProxy;
    Result := fOdbcApiProxy.SQLGetData(StatementHandle, ColumnNumber, TargetType, TargetValue,
      BufferLength, StrLen_or_Ind);
  {$ELSE}
    Result := OdbcApi.SQLGetData(StatementHandle, ColumnNumber, TargetType, TargetValue,
      BufferLength, StrLen_or_Ind);
  {$ENDIF}
end;

function TOdbcApiIntfImpl.SQLGetDescField(DescriptorHandle: SqlHDesc;
  RecNumber, FieldIdentifier: SqlSmallint; Value: SqlPointer;
  BufferLength: SqlInteger; var StringLength: SqlInteger): SqlReturn;
begin
  {$IFDEF DynamicOdbcImport}
    CheckAvailableProxy;
    Result := fOdbcApiProxy.SQLGetDescField(DescriptorHandle, RecNumber, FieldIdentifier,
      Value, BufferLength, StringLength);
  {$ELSE}
    Result := OdbcApi.SQLGetDescField(DescriptorHandle, RecNumber, FieldIdentifier,
      Value, BufferLength, StringLength);
  {$ENDIF}
end;

function TOdbcApiIntfImpl.SQLGetDescRec(DescriptorHandle: SqlHDesc;
  RecNumber: SqlSmallint; var Name: SqlChar; BufferLength: SqlSmallint;
  var StringLength, _Type, SubType: SqlSmallint; var Length: SqlInteger;
  var Precision, Scale, Nullable: SqlSmallint): SqlReturn;
begin
  {$IFDEF DynamicOdbcImport}
    CheckAvailableProxy;
    Result := fOdbcApiProxy.SQLGetDescRec(DescriptorHandle, RecNumber, Name, BufferLength,
      StringLength, _Type, SubType, Length, Precision, Scale, Nullable);
  {$ELSE}
    Result := OdbcApi.SQLGetDescRec(DescriptorHandle, RecNumber, Name, BufferLength,
      StringLength, _Type, SubType, Length, Precision, Scale, Nullable);
  {$ENDIF}
end;

function TOdbcApiIntfImpl.SQLGetDiagField(HandleType: SqlSmallint;
  Handle: SqlHandle; RecNumber, DiagIdentifier: SqlSmallint;
  DiagInfo: SqlPointer; BufferLength: SqlSmallint;
  var StringLength: SqlSmallint): SqlReturn;
begin
  {$IFDEF DynamicOdbcImport}
    CheckAvailableProxy;
    Result := fOdbcApiProxy.SQLGetDiagField(HandleType, Handle, RecNumber, DiagIdentifier,
      DiagInfo, BufferLength, StringLength);
  {$ELSE}
    Result := OdbcApi.SQLGetDiagField(HandleType, Handle, RecNumber, DiagIdentifier,
      DiagInfo, BufferLength, StringLength);
  {$ENDIF}
end;

function TOdbcApiIntfImpl.SQLGetDiagRec(HandleType: SqlSmallint;
  Handle: SqlHandle; RecNumber: SqlSmallint; Sqlstate: PAnsiChar;
  var NativeError: SqlInteger; MessageText: PAnsiChar;
  BufferLength: SqlSmallint; var TextLength: SqlSmallint): SqlReturn;
begin
  {$IFDEF DynamicOdbcImport}
    CheckAvailableProxy;
    Result := fOdbcApiProxy.SQLGetDiagRec(HandleType, Handle, RecNumber, Sqlstate,
      NativeError, MessageText, BufferLength, TextLength);
  {$ELSE}
    Result := OdbcApi.SQLGetDiagRec(HandleType, Handle, RecNumber, Sqlstate,
      NativeError, MessageText, BufferLength, TextLength);
  {$ENDIF}
end;

function TOdbcApiIntfImpl.SQLGetEnvAttr(EnvironmentHandle: SqlHEnv;
  Attribute: SqlInteger; Value: SqlPointer; BufferLength: SqlInteger;
  var StringLength: SqlInteger): SqlReturn;
begin
  {$IFDEF DynamicOdbcImport}
    CheckAvailableProxy;
    Result := fOdbcApiProxy.SQLGetEnvAttr(EnvironmentHandle, Attribute, Value, BufferLength,
      StringLength);
  {$ELSE}
    Result := OdbcApi.SQLGetEnvAttr(EnvironmentHandle, Attribute, Value, BufferLength,
      StringLength);
  {$ENDIF}
end;

function TOdbcApiIntfImpl.SQLGetFunctions(ConnectionHandle: SqlHDbc;
  FunctionId: SqlUSmallint; var Supported: SqlUSmallint): SqlReturn;
begin
  {$IFDEF DynamicOdbcImport}
    CheckAvailableProxy;
    Result := fOdbcApiProxy.SQLGetFunctions(ConnectionHandle, FunctionId, Supported);
  {$ELSE}
    Result := OdbcApi.SQLGetFunctions(ConnectionHandle, FunctionId, Supported);
  {$ENDIF}
end;

function TOdbcApiIntfImpl.SQLGetInfo(ConnectionHandle: SqlHDbc;
  InfoType: SqlUSmallint; InfoValuePtr: SqlPointer;
  BufferLength: SqlSmallint; StringLengthPtr: SqlPointer): SqlReturn;
begin
  {$IFDEF DynamicOdbcImport}
    CheckAvailableProxy;
    Result := fOdbcApiProxy.SQLGetInfo(ConnectionHandle, InfoType, InfoValuePtr, BufferLength,
      StringLengthPtr);
  {$ELSE}
    Result := OdbcApi.SQLGetInfo(ConnectionHandle, InfoType, InfoValuePtr, BufferLength,
      StringLengthPtr);
  {$ENDIF}
end;

function TOdbcApiIntfImpl.SQLGetInfoInt(ConnectionHandle: SqlHDbc;
  InfoType: SqlUSmallint; var InfoValue: SqlUInteger;
  Ignored1: SqlSmallint; Ignored2: Pointer): SqlReturn;
begin
  {$IFDEF DynamicOdbcImport}
    CheckAvailableProxy;
    Result := fOdbcApiProxy.SQLGetInfoInt(ConnectionHandle, InfoType, InfoValue,
      Ignored1, Ignored2);
  {$ELSE}
    Result := OdbcApi.SQLGetInfoInt(ConnectionHandle, InfoType, InfoValue,
      Ignored1, Ignored2);
  {$ENDIF}
end;

function TOdbcApiIntfImpl.SQLGetInfoSmallint(ConnectionHandle: SqlHDbc;
  InfoType: SqlUSmallint; var InfoValue: SqlUSmallint;
  Ignored1: SqlSmallint; Ignored2: Pointer): SqlReturn;
begin
  {$IFDEF DynamicOdbcImport}
    CheckAvailableProxy;
    Result := fOdbcApiProxy.SQLGetInfoSmallint(ConnectionHandle, InfoType, InfoValue,
      Ignored1, Ignored2);
  {$ELSE}
    Result := OdbcApi.SQLGetInfoSmallint(ConnectionHandle, InfoType, InfoValue,
      Ignored1, Ignored2);
  {$ENDIF}
end;

function TOdbcApiIntfImpl.SQLGetInfoString(ConnectionHandle: SqlHDbc;
  InfoType: SqlUSmallint; InfoValueString: PAnsiChar;
  BufferLength: SqlSmallint; var StringLength: SqlSmallint): SqlReturn;
begin
  {$IFDEF DynamicOdbcImport}
    CheckAvailableProxy;
    Result := fOdbcApiProxy.SQLGetInfoString(ConnectionHandle, InfoType, InfoValueString,
      BufferLength, StringLength);
  {$ELSE}
    Result := OdbcApi.SQLGetInfoString(ConnectionHandle, InfoType, InfoValueString,
      BufferLength, StringLength);
  {$ENDIF}
end;

function TOdbcApiIntfImpl.SQLGetStmtAttr(StatementHandle: SqlHStmt;
  Attribute: SqlInteger; Value: SqlPointer; BufferLength: SqlInteger;
  StringLength: PSqlInteger): SqlReturn;
begin
  {$IFDEF DynamicOdbcImport}
    CheckAvailableProxy;
    Result := fOdbcApiProxy.SQLGetStmtAttr(StatementHandle, Attribute, Value,
      BufferLength, StringLength);
  {$ELSE}
    Result := OdbcApi.SQLGetStmtAttr(StatementHandle, Attribute, Value,
      BufferLength, StringLength);
  {$ENDIF}
end;

function TOdbcApiIntfImpl.SQLGetStmtOption(StatementHandle: SqlHStmt;
  Option: SqlUSmallint; Value: SqlPointer): SqlReturn;
begin
  {$IFDEF DynamicOdbcImport}
    CheckAvailableProxy;
    Result := fOdbcApiProxy.SQLGetStmtOption(StatementHandle, Option, Value);
  {$ELSE}
    Result := OdbcApi.SQLGetStmtOption(StatementHandle, Option, Value);
  {$ENDIF}
end;

function TOdbcApiIntfImpl.SQLGetTypeInfo(StatementHandle: SqlHStmt;
  DataType: SqlSmallint): SqlReturn;
begin
  {$IFDEF DynamicOdbcImport}
    CheckAvailableProxy;
    Result := fOdbcApiProxy.SQLGetTypeInfo(StatementHandle, DataType);
  {$ELSE}
    Result := OdbcApi.SQLGetTypeInfo(StatementHandle, DataType);
  {$ENDIF}
end;

function TOdbcApiIntfImpl.SQLMoreResults(HStmt: SqlHStmt): SqlReturn;
begin
  {$IFDEF DynamicOdbcImport}
    CheckAvailableProxy;
    Result := fOdbcApiProxy.SQLMoreResults(HStmt);
  {$ELSE}
    Result := OdbcApi.SQLMoreResults(HStmt);
  {$ENDIF}
end;

function TOdbcApiIntfImpl.SQLNativeSql(HDbc: SqlHDbc;
  var szSqlStrIn: SqlChar; cbSqlStrIn: SqlInteger; var szSqlStr: SqlChar;
  cbSqlStrMax: SqlInteger; var pcbSqlStr: SqlInteger): SqlReturn;
begin
  {$IFDEF DynamicOdbcImport}
    CheckAvailableProxy;
    Result := fOdbcApiProxy.SQLNativeSql(HDbc, szSqlStrIn, cbSqlStrIn, szSqlStr,
      cbSqlStrMax, pcbSqlStr);
  {$ELSE}
    Result := OdbcApi.SQLNativeSql(HDbc, szSqlStrIn, cbSqlStrIn, szSqlStr,
      cbSqlStrMax, pcbSqlStr);
  {$ENDIF}
end;

function TOdbcApiIntfImpl.SQLNumParams(HStmt: SqlHStmt;
  var pcpar: SqlSmallint): SqlReturn;
begin
  {$IFDEF DynamicOdbcImport}
    CheckAvailableProxy;
    Result := fOdbcApiProxy.SQLNumParams(HStmt, pcpar);
  {$ELSE}
    Result := OdbcApi.SQLNumParams(HStmt, pcpar);
  {$ENDIF}
end;

function TOdbcApiIntfImpl.SQLNumResultCols(StatementHandle: SqlHStmt;
  var ColumnCount: SqlSmallint): SqlReturn;
begin
  {$IFDEF DynamicOdbcImport}
    CheckAvailableProxy;
    Result := fOdbcApiProxy.SQLNumResultCols(StatementHandle, ColumnCount);
  {$ELSE}
    Result := OdbcApi.SQLNumResultCols(StatementHandle, ColumnCount);
  {$ENDIF}
end;

function TOdbcApiIntfImpl.SQLParamData(StatementHandle: SqlHStmt;
  var Value: SqlPointer): SqlReturn;
begin
  {$IFDEF DynamicOdbcImport}
    CheckAvailableProxy;
    Result := fOdbcApiProxy.SQLParamData(StatementHandle, Value);
  {$ELSE}
    Result := OdbcApi.SQLParamData(StatementHandle, Value);
  {$ENDIF}
end;

function TOdbcApiIntfImpl.SQLParamOptions(HStmt: SqlHStmt;
  crow: SqlUInteger; var pirow: SqlUInteger): SqlReturn;
begin
  {$IFDEF DynamicOdbcImport}
    CheckAvailableProxy;
    Result := fOdbcApiProxy.SQLParamOptions(HStmt, crow, pirow);
  {$ELSE}
    Result := OdbcApi.SQLParamOptions(HStmt, crow, pirow);
  {$ENDIF}
end;

function TOdbcApiIntfImpl.SQLPrepare(StatementHandle: SqlHStmt;
  StatementText: PAnsiChar; TextLength: SqlInteger): SqlReturn;
begin
  {$IFDEF DynamicOdbcImport}
    CheckAvailableProxy;
    Result := fOdbcApiProxy.SQLPrepare(StatementHandle, StatementText, TextLength);
  {$ELSE}
    Result := OdbcApi.SQLPrepare(StatementHandle, StatementText, TextLength);
  {$ENDIF}
end;

function TOdbcApiIntfImpl.SQLPrimaryKeys(HStmt: SqlHStmt;
  szCatalogName: PAnsiChar; cbCatalogName: SqlSmallint;
  szSchemaName: PAnsiChar; cbSchemaName: SqlSmallint;
  szTableName: PAnsiChar; cbTableName: SqlSmallint): SqlReturn;
begin
  {$IFDEF DynamicOdbcImport}
    CheckAvailableProxy;
    Result := fOdbcApiProxy.SQLPrimaryKeys(HStmt, szCatalogName, cbCatalogName, szSchemaName,
      cbSchemaName, szTableName, cbTableName);
  {$ELSE}
    Result := OdbcApi.SQLPrimaryKeys(HStmt, szCatalogName, cbCatalogName, szSchemaName,
      cbSchemaName, szTableName, cbTableName);
  {$ENDIF}
end;

function TOdbcApiIntfImpl.SQLProcedureColumns(HStmt: SqlHStmt;
  szCatalogName: PAnsiChar; cbCatalogName: SqlSmallint;
  szSchemaName: PAnsiChar; cbSchemaName: SqlSmallint;
  szProcName: PAnsiChar; cbProcName: SqlSmallint; szColumnName: PAnsiChar;
  cbColumnName: SqlSmallint): SqlReturn;
begin
  {$IFDEF DynamicOdbcImport}
    CheckAvailableProxy;
    Result := fOdbcApiProxy.SQLProcedureColumns(HStmt, szCatalogName, cbCatalogName,
      szSchemaName, cbSchemaName, szProcName, cbProcName, szColumnName, cbColumnName);
  {$ELSE}
    Result := OdbcApi.SQLProcedureColumns(HStmt, szCatalogName, cbCatalogName,
      szSchemaName, cbSchemaName, szProcName, cbProcName, szColumnName, cbColumnName);
  {$ENDIF}
end;

function TOdbcApiIntfImpl.SQLProcedures(HStmt: SqlHStmt;
  szCatalogName: PAnsiChar; cbCatalogName: SqlSmallint;
  szSchemaName: PAnsiChar; cbSchemaName: SqlSmallint;
  szProcName: PAnsiChar; cbProcName: SqlSmallint): SqlReturn;
begin
  {$IFDEF DynamicOdbcImport}
    CheckAvailableProxy;
    Result := fOdbcApiProxy.SQLProcedures(HStmt, szCatalogName, cbCatalogName, szSchemaName,
      cbSchemaName, szProcName, cbProcName);
  {$ELSE}
    Result := OdbcApi.SQLProcedures(HStmt, szCatalogName, cbCatalogName, szSchemaName,
      cbSchemaName, szProcName, cbProcName);
  {$ENDIF}
end;

function TOdbcApiIntfImpl.SQLPutData(StatementHandle: SqlHStmt;
  Data: SqlPointer; StrLen_or_Ind: SqlInteger): SqlReturn;
begin
  {$IFDEF DynamicOdbcImport}
    CheckAvailableProxy;
    Result := fOdbcApiProxy.SQLPutData(StatementHandle, Data, StrLen_or_Ind);
  {$ELSE}
    Result := OdbcApi.SQLPutData(StatementHandle, Data, StrLen_or_Ind);
  {$ENDIF}
end;

function TOdbcApiIntfImpl.SQLRowCount(StatementHandle: SqlHStmt;
  var RowCount: SqlInteger): SqlReturn;
begin
  {$IFDEF DynamicOdbcImport}
    CheckAvailableProxy;
    Result := fOdbcApiProxy.SQLRowCount(StatementHandle, RowCount);
  {$ELSE}
    Result := OdbcApi.SQLRowCount(StatementHandle, RowCount);
  {$ENDIF}
end;

function TOdbcApiIntfImpl.SQLSetConnectAttr(ConnectionHandle: SqlHDbc;
  Attribute: SqlInteger; ValuePtr: SqlPointer;
  StringLength: SqlInteger): SqlReturn;
begin
  {$IFDEF DynamicOdbcImport}
    CheckAvailableProxy;
    Result := fOdbcApiProxy.SQLSetConnectAttr(ConnectionHandle, Attribute, ValuePtr, StringLength);
  {$ELSE}
    Result := OdbcApi.SQLSetConnectAttr(ConnectionHandle, Attribute, ValuePtr, StringLength);
  {$ENDIF}
end;

function TOdbcApiIntfImpl.SQLSetConnectOption(ConnectionHandle: SqlHDbc;
  Option: SqlUSmallint; Value: SqlUInteger): SqlReturn;
begin
  {$IFDEF DynamicOdbcImport}
    CheckAvailableProxy;
    Result := fOdbcApiProxy.SQLSetConnectOption(ConnectionHandle, Option, Value);
  {$ELSE}
    Result := OdbcApi.SQLSetConnectOption(ConnectionHandle, Option, Value);
  {$ENDIF}
end;

function TOdbcApiIntfImpl.SQLSetCursorName(StatementHandle: SqlHStmt;
  CursorName: PAnsiChar; NameLength: SqlSmallint): SqlReturn;
begin
  {$IFDEF DynamicOdbcImport}
    CheckAvailableProxy;
    Result := fOdbcApiProxy.SQLSetCursorName(StatementHandle, CursorName, NameLength);
  {$ELSE}
    Result := OdbcApi.SQLSetCursorName(StatementHandle, CursorName, NameLength);
  {$ENDIF}
end;

function TOdbcApiIntfImpl.SQLSetDescField(DescriptorHandle: SqlHDesc;
  RecNumber, FieldIdentifier: SqlSmallint; Value: SqlPointer;
  BufferLength: SqlInteger): SqlReturn;
begin
  {$IFDEF DynamicOdbcImport}
    CheckAvailableProxy;
    Result := fOdbcApiProxy.SQLSetDescField(DescriptorHandle, RecNumber, FieldIdentifier,
      Value, BufferLength);
  {$ELSE}
    Result := OdbcApi.SQLSetDescField(DescriptorHandle, RecNumber, FieldIdentifier,
      Value, BufferLength);
  {$ENDIF}
end;

function TOdbcApiIntfImpl.SQLSetDescRec(DescriptorHandle: SqlHDesc;
  RecNumber, _Type, SubType: SqlSmallint; Length: SqlInteger; Precision,
  Scale: SqlSmallint; Data: SqlPointer; var StringLength,
  Indicator: SqlInteger): SqlReturn;
begin
  {$IFDEF DynamicOdbcImport}
    CheckAvailableProxy;
    Result := fOdbcApiProxy.SQLSetDescRec(DescriptorHandle, RecNumber, _Type, SubType, Length,
      Precision, Scale, Data, StringLength, Indicator);
  {$ELSE}
    Result := OdbcApi.SQLSetDescRec(DescriptorHandle, RecNumber, _Type, SubType, Length,
      Precision, Scale, Data, StringLength, Indicator);
  {$ENDIF}
end;

function TOdbcApiIntfImpl.SQLSetEnvAttr(EnvironmentHandle: SqlHEnv;
  Attribute: SqlInteger; ValuePtr: Pointer;
  StringLength: SqlInteger): SqlReturn;
begin
  {$IFDEF DynamicOdbcImport}
    CheckAvailableProxy;
    Result := fOdbcApiProxy.SQLSetEnvAttr(EnvironmentHandle, Attribute, ValuePtr, StringLength);
  {$ELSE}
    Result := OdbcApi.SQLSetEnvAttr(EnvironmentHandle, Attribute, ValuePtr, StringLength);
  {$ENDIF}
end;

function TOdbcApiIntfImpl.SQLSetParam(StatementHandle: SqlHStmt;
  ParameterNumber: SqlUSmallint; ValueType, ParameterType: SqlSmallint;
  LengthPrecision: SqlUInteger; ParameterScale: SqlSmallint;
  ParameterValue: SqlPointer; var StrLen_or_Ind: SqlInteger): SqlReturn;
begin
  {$IFDEF DynamicOdbcImport}
    CheckAvailableProxy;
    Result := fOdbcApiProxy.SQLSetParam(StatementHandle, ParameterNumber, ValueType, ParameterType,
      LengthPrecision, ParameterScale, ParameterValue, StrLen_or_Ind);
  {$ELSE}
    Result := OdbcApi.SQLSetParam(StatementHandle, ParameterNumber, ValueType, ParameterType,
      LengthPrecision, ParameterScale, ParameterValue, StrLen_or_Ind);
  {$ENDIF}
end;

function TOdbcApiIntfImpl.SQLSetPos(HStmt: SqlHStmt; irow, fOption,
  fLock: SqlUSmallint): SqlReturn;
begin
  {$IFDEF DynamicOdbcImport}
    CheckAvailableProxy;
    Result := fOdbcApiProxy.SQLSetPos(HStmt, irow, fOption, fLock);
  {$ELSE}
    Result := OdbcApi.SQLSetPos(HStmt, irow, fOption, fLock);
  {$ENDIF}
end;

function TOdbcApiIntfImpl.SQLSetScrollOptions(HStmt: SqlHStmt;
  fConcurrency: SqlUSmallint; crowKeyset: SqlInteger;
  crowRowset: SqlUSmallint): SqlReturn;
begin
  {$IFDEF DynamicOdbcImport}
    CheckAvailableProxy;
    Result := fOdbcApiProxy.SQLSetScrollOptions(HStmt, fConcurrency, crowKeyset, crowRowset);
  {$ELSE}
    Result := OdbcApi.SQLSetScrollOptions(HStmt, fConcurrency, crowKeyset, crowRowset);
  {$ENDIF}
end;

function TOdbcApiIntfImpl.SQLSetStmtAttr(StatementHandle: SqlHStmt;
  Attribute: SqlInteger; Value: SqlPointer;
  StringLength: SqlInteger): SqlReturn;
begin
  {$IFDEF DynamicOdbcImport}
    CheckAvailableProxy;
    Result := fOdbcApiProxy.SQLSetStmtAttr(StatementHandle, Attribute, Value, StringLength);
  {$ELSE}
    Result := OdbcApi.SQLSetStmtAttr(StatementHandle, Attribute, Value, StringLength);
  {$ENDIF}
end;

function TOdbcApiIntfImpl.SQLSetStmtOption(StatementHandle: SqlHStmt;
  Option: SqlUSmallint; Value: SqlUInteger): SqlReturn;
begin
  {$IFDEF DynamicOdbcImport}
    CheckAvailableProxy;
    Result := fOdbcApiProxy.SQLSetStmtOption(StatementHandle, Option, Value);
  {$ELSE}
    Result := OdbcApi.SQLSetStmtOption(StatementHandle, Option, Value);
  {$ENDIF}
end;

function TOdbcApiIntfImpl.SQLSpecialColumns(StatementHandle: SqlHStmt;
  IdentifierType: SqlUSmallint; CatalogName: PAnsiChar;
  NameLength1: SqlSmallint; SchemaName: PAnsiChar;
  NameLength2: SqlSmallint; TableName: PAnsiChar; NameLength3: SqlSmallint;
  Scope, Nullable: SqlUSmallint): SqlReturn;
begin
  {$IFDEF DynamicOdbcImport}
    CheckAvailableProxy;
    Result := fOdbcApiProxy.SQLSpecialColumns(StatementHandle, IdentifierType, CatalogName,
      NameLength1, SchemaName, NameLength2, TableName, NameLength3, Scope, Nullable);
  {$ELSE}
    Result := OdbcApi.SQLSpecialColumns(StatementHandle, IdentifierType, CatalogName,
      NameLength1, SchemaName, NameLength2, TableName, NameLength3, Scope, Nullable);
  {$ENDIF}
end;

function TOdbcApiIntfImpl.SQLStatistics(StatementHandle: SqlHStmt;
  CatalogName: PAnsiChar; NameLength1: SqlSmallint; SchemaName: PAnsiChar;
  NameLength2: SqlSmallint; TableName: PAnsiChar; NameLength3: SqlSmallint;
  Unique, Reserved: SqlUSmallint): SqlReturn;
begin
  {$IFDEF DynamicOdbcImport}
    CheckAvailableProxy;
    Result := fOdbcApiProxy.SQLStatistics(StatementHandle, CatalogName, NameLength1,
      SchemaName, NameLength2, TableName, NameLength3, Unique, Reserved);
  {$ELSE}
    Result := OdbcApi.SQLStatistics(StatementHandle, CatalogName, NameLength1,
      SchemaName, NameLength2, TableName, NameLength3, Unique, Reserved);
  {$ENDIF}
end;

function TOdbcApiIntfImpl.SQLTablePrivileges(HStmt: SqlHStmt;
  var szCatalogName: SqlChar; cbCatalogName: SqlSmallint;
  var szSchemaName: SqlChar; cbSchemaName: SqlSmallint;
  var szTableName: SqlChar; cbTableName: SqlSmallint): SqlReturn;
begin
  {$IFDEF DynamicOdbcImport}
    CheckAvailableProxy;
    Result := fOdbcApiProxy.SQLTablePrivileges(HStmt, szCatalogName, cbCatalogName, szSchemaName,
      cbSchemaName, szTableName, cbTableName);
  {$ELSE}
    Result := OdbcApi.SQLTablePrivileges(HStmt, szCatalogName, cbCatalogName, szSchemaName,
      cbSchemaName, szTableName, cbTableName);
  {$ENDIF}
end;

function TOdbcApiIntfImpl.SQLTables(StatementHandle: SqlHStmt;
  CatalogName: PAnsiChar; NameLength1: SqlSmallint; SchemaName: PAnsiChar;
  NameLength2: SqlSmallint; TableName: PAnsiChar; NameLength3: SqlSmallint;
  TableType: PAnsiChar; NameLength4: SqlSmallint): SqlReturn;
begin
  {$IFDEF DynamicOdbcImport}
    CheckAvailableProxy;
    Result := fOdbcApiProxy.SQLTables(StatementHandle, CatalogName, NameLength1, SchemaName,
      NameLength2, TableName, NameLength3, TableType, NameLength4);
  {$ELSE}
    Result := OdbcApi.SQLTables(StatementHandle, CatalogName, NameLength1, SchemaName,
      NameLength2, TableName, NameLength3, TableType, NameLength4);
  {$ENDIF}
end;

function TOdbcApiIntfImpl.SQLTransact(EnvironmentHandle: SqlHEnv;
  ConnectionHandle: SqlHDbc; CompletionType: SqlUSmallint): SqlReturn;
begin
  {$IFDEF DynamicOdbcImport}
    CheckAvailableProxy;
    Result := fOdbcApiProxy.SQLTransact(EnvironmentHandle, ConnectionHandle, CompletionType);
  {$ELSE}
    Result := OdbcApi.SQLTransact(EnvironmentHandle, ConnectionHandle, CompletionType);
  {$ENDIF}
end;

function TOdbcApiIntfImpl.TraceCloseLogFile: Retcode;
begin
  {$IFDEF DynamicOdbcImport}
    CheckAvailableProxy;
    Result := fOdbcApiProxy.TraceCloseLogFile;
  {$ELSE}
    Result := OdbcApi.TraceCloseLogFile;
  {$ENDIF}
end;

function TOdbcApiIntfImpl.TraceOpenLogFile(var _1, _2: WideChar; _3: Integer): Retcode;
begin
  {$IFDEF DynamicOdbcImport}
    CheckAvailableProxy;
    Result := fOdbcApiProxy.TraceOpenLogFile(_1, _2, _3);
  {$ELSE}
    Result := OdbcApi.TraceOpenLogFile(_1, _2, _3);
  {$ENDIF}
end;

procedure TOdbcApiIntfImpl.TraceReturn(_1, _2: Retcode);
begin
  {$IFDEF DynamicOdbcImport}
    CheckAvailableProxy;
    fOdbcApiProxy.TraceReturn(_1, _2);
  {$ELSE}
    OdbcApi.TraceReturn(_1, _2);
  {$ENDIF}
end;

function TOdbcApiIntfImpl.TraceVersion: Longint;
begin
  {$IFDEF DynamicOdbcImport}
    CheckAvailableProxy;
    Result := fOdbcApiProxy.TraceVersion;
  {$ELSE}
    Result := OdbcApi.TraceVersion;
  {$ENDIF}
end;

function TOdbcApiIntfImpl.TraceVSControl(_1: Integer): Retcode;
begin
  {$IFDEF DynamicOdbcImport}
    CheckAvailableProxy;
    Result := fOdbcApiProxy.TraceVSControl(_1);
  {$ELSE}
    Result := OdbcApi.TraceVSControl(_1);
  {$ENDIF}
end;

{$ENDIF IFDEF _iOdbcApi_}

initialization
  {$IFDEF DynamicOdbcImport}
  fOdbcApiCache := TStringHash.Create;
  {$ELSE}
  fOdbcApi := TOdbcApiProxy.Create;
  {$ENDIF}

finalization
  {$IFDEF DynamicOdbcImport}
  fOdbcApiCache.Free;
  {$ELSE}
  fOdbcApi.Free;
  {$ENDIF}

end.
