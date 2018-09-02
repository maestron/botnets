{******************************************************************************}
{                                                       	               }
{ Web Publishing Error Codes API interface Unit for Object Pascal              }
{                                                       	               }
{ Portions created by Microsoft are Copyright (C) 1995-2001 Microsoft          }
{ Corporation. All Rights Reserved.                                            }
{ 								               }
{ The original file is: wpapimsg.h, released June 2000. The original Pascal    }
{ code is: WPApiMsg.pas, released December 2000. The initial developer of the  }
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

unit JwaWPApiMsg;

{$WEAKPACKAGEUNIT}

{$HPPEMIT ''}
{$HPPEMIT '#include "wpapimsg.h"'}
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
// MessageId: WEBPOST_ERROR_FIRST
//
// MessageText:
//
//  Web Publishing Wizard first error message.
//

const
  WEBPOST_ERROR_FIRST = DWORD($40042100);
  {$EXTERNALSYM WEBPOST_ERROR_FIRST}

//
// MessageId: WEBPOST_ERROR_UNKNOWN
//
// MessageText:
//
//  An unknown error occurred in the Web Publishing Wizard.
//

  WEBPOST_ERROR_UNKNOWN = DWORD($C0042101);
  {$EXTERNALSYM WEBPOST_ERROR_UNKNOWN}

//
// MessageId: WEBPOST_ERROR_PROVCLSID_UNKNOWN
//
// MessageText:
//
//  The Web Publishing Wizard could not locate the service provider used to transfer files to your Web server.
//

  WEBPOST_ERROR_PROVCLSID_UNKNOWN = DWORD($C0042102);
  {$EXTERNALSYM WEBPOST_ERROR_PROVCLSID_UNKNOWN}

//
// MessageId: WEBPOST_ERROR_SITE_CORRUPT
//
// MessageText:
//
//  The Web Publishing Wizard could not retrieve all of the required information about your Web server.
//

  WEBPOST_ERROR_SITE_CORRUPT = DWORD($C0042103);
  {$EXTERNALSYM WEBPOST_ERROR_SITE_CORRUPT}

//
// MessageId: WEBPOST_ERROR_PROV_CORRUPT
//
// MessageText:
//
//  The Web Publishing Wizard could not retrieve all of the required information about this service provider.
//

  WEBPOST_ERROR_PROV_CORRUPT = DWORD($C0042104);
  {$EXTERNALSYM WEBPOST_ERROR_PROV_CORRUPT}

//
// MessageId: WEBPOST_ERROR_PROV_DLL
//
// MessageText:
//
//  The Web Publishing Wizard could not locate the file(s) for the requested service provider.
//

  WEBPOST_ERROR_PROV_DLL = DWORD($C0042105);
  {$EXTERNALSYM WEBPOST_ERROR_PROV_DLL}

//
// MessageId: WEBPOST_ERROR_PROV_EP
//
// MessageText:
//
//  The file(s) for the requested service provider are either corrupt or outdated.
//

  WEBPOST_ERROR_PROV_EP = DWORD($C0042106);
  {$EXTERNALSYM WEBPOST_ERROR_PROV_EP}

//
// MessageId: WEBPOST_ERROR_INIT_FAILED
//
// MessageText:
//
//  An error occurred while attempting to start the Web Publishing Wizard.
//

  WEBPOST_ERROR_INIT_FAILED = DWORD($C0042107);
  {$EXTERNALSYM WEBPOST_ERROR_INIT_FAILED}

//
// MessageId: WEBPOST_ERROR_LIST_SITES
//
// MessageText:
//
//  An error occurred while the Web Publishing Wizard was enumerating the Web servers to which you have previously published.
//

  WEBPOST_ERROR_LIST_SITES = DWORD($C0042108);
  {$EXTERNALSYM WEBPOST_ERROR_LIST_SITES}

//
// MessageId: WEBPOST_ERROR_SITE_EXISTS
//
// MessageText:
//
//  The Web Publishing Wizard could not use the requested descriptive name for your Web server because another Web server already uses the name.
//

  WEBPOST_ERROR_SITE_EXISTS = DWORD($C0042109);
  {$EXTERNALSYM WEBPOST_ERROR_SITE_EXISTS}

//
// MessageId: WEBPOST_ERROR_CREATE_SITE
//
// MessageText:
//
//  An error occurred while the Web Publishing Wizard was saving information about your Web server.
//

  WEBPOST_ERROR_CREATE_SITE = DWORD($C004210A);
  {$EXTERNALSYM WEBPOST_ERROR_CREATE_SITE}

//
// MessageId: WEBPOST_ERROR_SITE_DOESNOTEXIST
//
// MessageText:
//
//  Your computer does not contain any information about the Web server you have selected.
//

  WEBPOST_ERROR_SITE_DOESNOTEXIST = DWORD($C004210B);
  {$EXTERNALSYM WEBPOST_ERROR_SITE_DOESNOTEXIST}

//
// MessageId: WEBPOST_ERROR_DELETE_SITE
//
// MessageText:
//
//  An error occurred while the Web Publishing Wizard was deleting information about your Web server.
//

  WEBPOST_ERROR_DELETE_SITE = DWORD($C004210C);
  {$EXTERNALSYM WEBPOST_ERROR_DELETE_SITE}

//
// MessageId: WEBPOST_ERROR_ENUM_PROVS
//
// MessageText:
//
//  An error occurred while the Web Publishing Wizard was enumerating the service providers on this system.
//

  WEBPOST_ERROR_ENUM_PROVS = DWORD($C004210D);
  {$EXTERNALSYM WEBPOST_ERROR_ENUM_PROVS}

//
// MessageId: WEBPOST_ERROR_PROV_QI
//
// MessageText:
//
//  The Web Publishing Wizard was unable to determine the version number of your service provider.
//

  WEBPOST_ERROR_PROV_QI = DWORD($C004210E);
  {$EXTERNALSYM WEBPOST_ERROR_PROV_QI}

//
// MessageId: WEBPOST_ERROR_POST_FILES
//
// MessageText:
//
//  An error occurred while the Web Publishing Wizard was attempting to publish your files.
//

  WEBPOST_ERROR_POST_FILES = DWORD($C004210F);
  {$EXTERNALSYM WEBPOST_ERROR_POST_FILES}

//
// MessageId: WEBPOST_ERROR_COCREATE_WIZARD
//
// MessageText:
//
//  The Web Publishing Wizard is not installed correctly. Please uninstall and then reinstall the wizard.
//

  WEBPOST_ERROR_COCREATE_WIZARD = DWORD($C0042110);
  {$EXTERNALSYM WEBPOST_ERROR_COCREATE_WIZARD}

//
// MessageId: WEBPOST_ERROR_POSTINFO_REQUIRED
//
// MessageText:
//
//  Your service provider requires that a PostInfo file be located on the server. No PostInfo file could be located.
//

  WEBPOST_ERROR_POSTINFO_REQUIRED = DWORD($C0042111);
  {$EXTERNALSYM WEBPOST_ERROR_POSTINFO_REQUIRED}

//
// MessageId: WEBPOST_ERROR_AUTOBIND_FAILED
//
// MessageText:
//
//  The service provider could not be automatically selected for your Web server.
//

  WEBPOST_ERROR_AUTOBIND_FAILED = DWORD($C0042112);
  {$EXTERNALSYM WEBPOST_ERROR_AUTOBIND_FAILED}

//
// MessageId: WEBPOST_ERROR_BAD_PROV_PTR
//
// MessageText:
//
//  The Web Publishing Wizard was not able to obtain a valid pointer to the requested service provider.
//

  WEBPOST_ERROR_BAD_PROV_PTR = DWORD($C0042113);
  {$EXTERNALSYM WEBPOST_ERROR_BAD_PROV_PTR}

//
// MessageId: WEBPOST_ERROR_PROV_NOT_IN_POSTINFO
//
// MessageText:
//
//  The Web server you selected does not indicate support for the service provider you selected.
//

  WEBPOST_ERROR_PROV_NOT_IN_POSTINFO = DWORD($80042114);
  {$EXTERNALSYM WEBPOST_ERROR_PROV_NOT_IN_POSTINFO}

//
// MessageId: WEBPOST_ERROR_EXTENDED_ERROR
//
// MessageText:
//
//  Web Publishing Wizard extended error.
//

  WEBPOST_ERROR_EXTENDED_ERROR = DWORD($C0042116);
  {$EXTERNALSYM WEBPOST_ERROR_EXTENDED_ERROR}

//
// MessageId: WEBPOST_ERROR_NO_EXT_ERR_INFO
//
// MessageText:
//
//  An extended error occurred in the Web Publishing Wizard, but the error message could not be retrieved.
//

  WEBPOST_ERROR_NO_EXT_ERR_INFO = DWORD($C0042117);
  {$EXTERNALSYM WEBPOST_ERROR_NO_EXT_ERR_INFO}

//
// MessageId: WEBPOST_ERROR_INVALID_POSTINFO
//
// MessageText:
//
//  The PostInfo file on the server is invalid.
//

  WEBPOST_ERROR_INVALID_POSTINFO = DWORD($40042118);
  {$EXTERNALSYM WEBPOST_ERROR_INVALID_POSTINFO}

//
// MessageId: WEBPOST_ERROR_NO_POSTINFO
//
// MessageText:
//
//  There is no PostInfo file on the server.
//

  WEBPOST_ERROR_NO_POSTINFO = DWORD($40042119);
  {$EXTERNALSYM WEBPOST_ERROR_NO_POSTINFO}

//
// MessageId: WEBPOST_ERROR_HTTP_GET_FAILED
//
// MessageText:
//
//  The Web Publishing Wizard was not able to retrieve the first file published using an HTTP connection.
//

  WEBPOST_ERROR_HTTP_GET_FAILED = DWORD($4004211A);
  {$EXTERNALSYM WEBPOST_ERROR_HTTP_GET_FAILED}

//
// MessageId: WEBPOST_ERROR_LAST
//
// MessageText:
//
//  Web Publishing Wizard last error message.
//

  WEBPOST_ERROR_LAST = DWORD($400421FF);
  {$EXTERNALSYM WEBPOST_ERROR_LAST}

implementation

end.
