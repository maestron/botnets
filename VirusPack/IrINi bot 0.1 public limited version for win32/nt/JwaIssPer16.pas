{******************************************************************************}
{                                                       	               }
{ Security Package Error Codes API interface Unit for Object Pascal            }
{                                                       	               }
{ Portions created by Microsoft are Copyright (C) 1995-2001 Microsoft          }
{ Corporation. All Rights Reserved.                                            }
{ 								               }
{ The original file is: issper16.h, released June 2000. The original Pascal    }
{ code is: IssPer16.pas, released December 2000. The initial developer of the  }
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

unit JwaIssPer16;

{$WEAKPACKAGEUNIT}

{$HPPEMIT ''}
{$HPPEMIT '#include "issper16.h"'}
{$HPPEMIT ''}

{$I WINDEFINES.INC}

interface

uses
  JwaSSPI;

// Define the severities
//
//  Values are 32 bit values layed out as follows:
//
//   3 3 2 2 2 2 2 2 2 2 2 2 1 1 1 1 1 1 1 1 1 1
//   1 0 9 8 7 6 5 4 3 2 1 0 9 8 7 6 5 4 3 2 1 0 9 8 7 6 5 4 3 2 1 0
//  +---+-+-+-----------------------+-------------------------------+
//  |Sev|C|R|     Facility          |               Code            |
//  +---+-+-+-----------------------+-------------------------------+
//
//  where
//
//      Sev - is the severity code
//
//          00 - Success
//          01 - Informational
//          10 - Warning
//          11 - Error
//
//      C - is the Customer code flag
//
//      R - is a reserved bit
//
//      Facility - is the facility code
//
//      Code - is the facility's status code
//
//
// Define the facility codes
//

const
  FACILITY_SECURITY = $9;
  {$EXTERNALSYM FACILITY_SECURITY}
  FACILITY_NULL     = 0;
  {$EXTERNALSYM FACILITY_NULL}

//
// Define the severity codes
//

  STATUS_SEVERITY_SUCCESS = $0;
  {$EXTERNALSYM STATUS_SEVERITY_SUCCESS}
  STATUS_SEVERITY_COERROR = $2;
  {$EXTERNALSYM STATUS_SEVERITY_COERROR}

//
// MessageId: SEC_E_INSUFFICIENT_MEMORY
//
// MessageText:
//
//  Not enough memory is available to complete this request
//

  SEC_E_INSUFFICIENT_MEMORY = SECURITY_STATUS($1300);
  {$EXTERNALSYM SEC_E_INSUFFICIENT_MEMORY}

//
// MessageId: SEC_E_INVALID_HANDLE
//
// MessageText:
//
//  The handle specified is invalid
//

  SEC_E_INVALID_HANDLE = SECURITY_STATUS($1301);
  {$EXTERNALSYM SEC_E_INVALID_HANDLE}

//
// MessageId: SEC_E_UNSUPPORTED_FUNCTION
//
// MessageText:
//
//  The function requested is not supported
//

  SEC_E_UNSUPPORTED_FUNCTION = SECURITY_STATUS($1302);
  {$EXTERNALSYM SEC_E_UNSUPPORTED_FUNCTION}


//
// MessageId: SEC_E_TARGET_UNKNOWN
//
// MessageText:
//
//  The specified target is unknown or unreachable
//

  SEC_E_TARGET_UNKNOWN = SECURITY_STATUS($1303);
  {$EXTERNALSYM SEC_E_TARGET_UNKNOWN}

//
// MessageId: SEC_E_INTERNAL_ERROR
//
// MessageText:
//
//  The Local Security Authority cannot be contacted
//

  SEC_E_INTERNAL_ERROR = SECURITY_STATUS($1304);
  {$EXTERNALSYM SEC_E_INTERNAL_ERROR}

//
// MessageId: SEC_E_SECPKG_NOT_FOUND
//
// MessageText:
//
//  The requested security package does not exist
//

  SEC_E_SECPKG_NOT_FOUND = SECURITY_STATUS($1305);
  {$EXTERNALSYM SEC_E_SECPKG_NOT_FOUND}


//
// MessageId: SEC_E_NOT_OWNER
//
// MessageText:
//
//  The caller is not the owner of the desired credentials
//

  SEC_E_NOT_OWNER = SECURITY_STATUS($1306);
  {$EXTERNALSYM SEC_E_NOT_OWNER}

//
// MessageId: SEC_E_CANNOT_INSTALL
//
// MessageText:
//
//  The security package failed to initialize, and cannot be installed
//

  SEC_E_CANNOT_INSTALL = SECURITY_STATUS($1307);
  {$EXTERNALSYM SEC_E_CANNOT_INSTALL}

//
// MessageId: SEC_E_INVALID_TOKEN
//
// MessageText:
//
//  The token supplied to the function is invalid
//

  SEC_E_INVALID_TOKEN = SECURITY_STATUS($1308);
  {$EXTERNALSYM SEC_E_INVALID_TOKEN}

//
// MessageId: SEC_E_CANNOT_PACK
//
// MessageText:
//
//  The security package is not able to marshall the logon buffer,
//  so the logon attempt has failed
//

  SEC_E_CANNOT_PACK = SECURITY_STATUS($1309);
  {$EXTERNALSYM SEC_E_CANNOT_PACK}

//
// MessageId: SEC_E_QOP_NOT_SUPPORTED
//
// MessageText:
//
//  The per-message Quality of Protection is not supported by the
//  security package
//

  SEC_E_QOP_NOT_SUPPORTED = SECURITY_STATUS($130A);
  {$EXTERNALSYM SEC_E_QOP_NOT_SUPPORTED}

//
// MessageId: SEC_E_NO_IMPERSONATION
//
// MessageText:
//
//  The security context does not allow impersonation of the client
//

  SEC_E_NO_IMPERSONATION = SECURITY_STATUS($130B);
  {$EXTERNALSYM SEC_E_NO_IMPERSONATION}

//
// MessageId: SEC_E_LOGON_DENIED
//
// MessageText:
//
//  The logon attempt failed
//

  SEC_E_LOGON_DENIED = SECURITY_STATUS($130C);
  {$EXTERNALSYM SEC_E_LOGON_DENIED}

//
// MessageId: SEC_E_UNKNOWN_CREDENTIALS
//
// MessageText:
//
//  The credentials supplied to the package were not
//  recognized
//

  SEC_E_UNKNOWN_CREDENTIALS = SECURITY_STATUS($130D);
  {$EXTERNALSYM SEC_E_UNKNOWN_CREDENTIALS}

//
// MessageId: SEC_E_NO_CREDENTIALS
//
// MessageText:
//
//  No credentials are available in the security package
//

  SEC_E_NO_CREDENTIALS = SECURITY_STATUS($130E);
  {$EXTERNALSYM SEC_E_NO_CREDENTIALS}

//
// MessageId: SEC_E_MESSAGE_ALTERED
//
// MessageText:
//
//  The message supplied for verification has been altered
//

  SEC_E_MESSAGE_ALTERED = SECURITY_STATUS($130F);
  {$EXTERNALSYM SEC_E_MESSAGE_ALTERED}

//
// MessageId: SEC_E_OUT_OF_SEQUENCE
//
// MessageText:
//
//  The message supplied for verification is out of sequence
//

  SEC_E_OUT_OF_SEQUENCE = SECURITY_STATUS($1310);
  {$EXTERNALSYM SEC_E_OUT_OF_SEQUENCE}

//
// MessageId: SEC_E_NO_AUTHENTICATING_AUTHORITY
//
// MessageText:
//
//  No authority could be contacted for authentication.
//

  SEC_E_NO_AUTHENTICATING_AUTHORITY = SECURITY_STATUS($1311);
  {$EXTERNALSYM SEC_E_NO_AUTHENTICATING_AUTHORITY}

// MessageId: SEC_E_CONTEXT_EXPIRED
//
// MessageText:
//
//  The context has expired and can no longer be used.
//

  SEC_E_CONTEXT_EXPIRED = SECURITY_STATUS($1312);
  {$EXTERNALSYM SEC_E_CONTEXT_EXPIRED}

//
// MessageId: SEC_E_INCOMPLETE_MESSAGE
//
// MessageText:
//
//  The supplied message is incomplete.  The signature was not verified.
//

  SEC_E_INCOMPLETE_MESSAGE = SECURITY_STATUS($1313);
  {$EXTERNALSYM SEC_E_INCOMPLETE_MESSAGE}

//
// MessageId: SEC_I_CONTINUE_NEEDED
//
// MessageText:
//
//  The function completed successfully, but must be called
//  again to complete the context
//

  SEC_I_CONTINUE_NEEDED = SECURITY_STATUS($1012);
  {$EXTERNALSYM SEC_I_CONTINUE_NEEDED}

//
// MessageId: SEC_I_COMPLETE_NEEDED
//
// MessageText:
//
//  The function completed successfully, but CompleteToken
//  must be called
//

  SEC_I_COMPLETE_NEEDED = SECURITY_STATUS($1013);
  {$EXTERNALSYM SEC_I_COMPLETE_NEEDED}

//
// MessageId: SEC_I_COMPLETE_AND_CONTINUE
//
// MessageText:
//
//  The function completed successfully, but both CompleteToken
//  and this function must be called to complete the context
//

  SEC_I_COMPLETE_AND_CONTINUE = SECURITY_STATUS($1014);
  {$EXTERNALSYM SEC_I_COMPLETE_AND_CONTINUE}

//
// MessageId: SEC_I_LOCAL_LOGON
//
// MessageText:
//
//  The logon was completed, but no network authority was
//  available.  The logon was made using locally known information
//

  SEC_I_LOCAL_LOGON = SECURITY_STATUS($1015);
  {$EXTERNALSYM SEC_I_LOCAL_LOGON}

//
// MessageId: SEC_E_OK
//
// MessageText:
//
//  Call completed successfully
//

  SEC_E_OK = SECURITY_STATUS($0000);
  {$EXTERNALSYM SEC_E_OK}

//
// Older error names for backwards compatibility
//

  SEC_E_NOT_SUPPORTED = SEC_E_UNSUPPORTED_FUNCTION;
  {$EXTERNALSYM SEC_E_NOT_SUPPORTED}
  SEC_E_NO_SPM        = SEC_E_INTERNAL_ERROR;
  {$EXTERNALSYM SEC_E_NO_SPM}
  SEC_E_BAD_PKGID     = SEC_E_SECPKG_NOT_FOUND;
  {$EXTERNALSYM SEC_E_BAD_PKGID}

implementation

end.
