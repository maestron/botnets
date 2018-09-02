{******************************************************************************}
{                                                       	               }
{ Web Publishing Wizzard Error Codes API interface Unit for Object Pascal      }
{                                                       	               }
{ Portions created by Microsoft are Copyright (C) 1995-2001 Microsoft          }
{ Corporation. All Rights Reserved.                                            }
{ 								               }
{ The original file is: wpwizmsg.h, released June 2000. The original Pascal    }
{ code is: WPWizMsg.pas, released December 2000. The initial developer of the  }
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

unit JwaWPWizMsg;

{$WEAKPACKAGEUNIT}

{$HPPEMIT ''}
{$HPPEMIT '#include "wpwizmsg.h"'}
{$HPPEMIT ''}

{$I WINDEFINES.INC}

interface

uses
  JwaWinType;

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


//
// Define the severity codes
//


//
// MessageId: WPWIZ_ERROR_FIRST
//
// MessageText:
//
//  Web Publishing Wizard first error message.
//

const
  WPWIZ_ERROR_FIRST = DWORD($40042000);
  {$EXTERNALSYM WPWIZ_ERROR_FIRST}

//
// MessageId: WPWIZ_ERROR_UNKNOWN
//
// MessageText:
//
//  An unknown error occurred in the Web Publishing Wizard.
//

  WPWIZ_ERROR_UNKNOWN = DWORD($C0042001);
  {$EXTERNALSYM WPWIZ_ERROR_UNKNOWN}

//
// MessageId: WPWIZ_ERROR_PROV_QI
//
// MessageText:
//
//  The Web Publishing Wizard was unable to determine the version number of your service provider.
//

  WPWIZ_ERROR_PROV_QI = DWORD($C0042002);
  {$EXTERNALSYM WPWIZ_ERROR_PROV_QI}

//
// MessageId: WPWIZ_ERROR_INIT_FAILED
//
// MessageText:
//
//  An error occurred while attempting to start the Web Publishing Wizard.
//

  WPWIZ_ERROR_INIT_FAILED = DWORD($C0042003);
  {$EXTERNALSYM WPWIZ_ERROR_INIT_FAILED}

//
// MessageId: WPWIZ_ERROR_COCREATE_WEBPOST
//
// MessageText:
//
//  The Web Publishing Wizard is not installed correctly. Please uninstall and then reinstall the wizard.
//

  WPWIZ_ERROR_COCREATE_WEBPOST = DWORD($C0042004);
  {$EXTERNALSYM WPWIZ_ERROR_COCREATE_WEBPOST}

//
// MessageId: WPWIZ_ERROR_NO_PROVIDERS
//
// MessageText:
//
//  The Web Publishing Wizard could not run because there are no service providers installed.
//

  WPWIZ_ERROR_NO_PROVIDERS = DWORD($C0042005);
  {$EXTERNALSYM WPWIZ_ERROR_NO_PROVIDERS}

//
// MessageId: WPWIZ_ERROR_STATE_PTR
//
// MessageText:
//
//  An internal error (0x2006) occurred in the Web Publishing Wizard.
//

  WPWIZ_ERROR_STATE_PTR = DWORD($C0042006);
  {$EXTERNALSYM WPWIZ_ERROR_STATE_PTR}

//
// MessageId: WPWIZ_ERROR_WEBPOST_PTR
//
// MessageText:
//
//  An internal error (0x2007) occurred in the Web Publishing Wizard.
//

  WPWIZ_ERROR_WEBPOST_PTR = DWORD($C0042007);
  {$EXTERNALSYM WPWIZ_ERROR_WEBPOST_PTR}

//
// MessageId: WPWIZ_ERROR_FILE_NOT_FOUND
//
// MessageText:
//
//  The file(s) you selected to publish could not be found.
//

  WPWIZ_ERROR_FILE_NOT_FOUND = DWORD($C0042008);
  {$EXTERNALSYM WPWIZ_ERROR_FILE_NOT_FOUND}

//
// MessageId: WPWIZ_ERROR_PROPSHEET_ERROR
//
// MessageText:
//
//  An error occurred in the user interface of the Web Publishing Wizard.
//

  WPWIZ_ERROR_PROPSHEET_ERROR = DWORD($C0042009);
  {$EXTERNALSYM WPWIZ_ERROR_PROPSHEET_ERROR}

//
// MessageId: WPWIZ_ERROR_OUTOFMEMORY
//
// MessageText:
//
//  The Web Publishing Wizard has run out of memory. Please close other running applications before continuing.
//

  WPWIZ_ERROR_OUTOFMEMORY = DWORD($C004200A);
  {$EXTERNALSYM WPWIZ_ERROR_OUTOFMEMORY}

//
// MessageId: WPWIZ_ERROR_LAST
//
// MessageText:
//
//  Web Publishing Wizard last error message.
//

  WPWIZ_ERROR_LAST = DWORD($400420FF);
  {$EXTERNALSYM WPWIZ_ERROR_LAST}

implementation

end.
