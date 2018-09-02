{******************************************************************************}
{                                                       	               }
{ Active Directory Status Codes  API interface Unit for Object Pascal          }
{                                                       	               }
{ Portions created by Microsoft are Copyright (C) 1995-2001 Microsoft          }
{ Corporation. All Rights Reserved.                                            }
{ 								               }
{ The original file is: adssts.h, released June 2000. The original Pascal      }
{ code is: AdsSts.pas, released December 2000. The initial developer of the    }
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

unit JwaAdssts;

{$WEAKPACKAGEUNIT}

{$HPPEMIT ''}
{$HPPEMIT '#include "adssts.h"'}
{$HPPEMIT ''}

{$I WINDEFINES.INC}

interface

uses
  JwaWinNT;

//  Contents:   Status Codes for ADS objects

const
  ADS_PRINTER_PAUSED            = $00000001;
  {$EXTERNALSYM ADS_PRINTER_PAUSED}
  ADS_PRINTER_PENDING_DELETION  = $00000002;
  {$EXTERNALSYM ADS_PRINTER_PENDING_DELETION}
  ADS_PRINTER_ERROR             = $00000003;
  {$EXTERNALSYM ADS_PRINTER_ERROR}
  ADS_PRINTER_PAPER_JAM         = $00000004;
  {$EXTERNALSYM ADS_PRINTER_PAPER_JAM}
  ADS_PRINTER_PAPER_OUT         = $00000005;
  {$EXTERNALSYM ADS_PRINTER_PAPER_OUT}
  ADS_PRINTER_MANUAL_FEED       = $00000006;
  {$EXTERNALSYM ADS_PRINTER_MANUAL_FEED}
  ADS_PRINTER_PAPER_PROBLEM     = $00000007;
  {$EXTERNALSYM ADS_PRINTER_PAPER_PROBLEM}
  ADS_PRINTER_OFFLINE           = $00000008;
  {$EXTERNALSYM ADS_PRINTER_OFFLINE}
  ADS_PRINTER_IO_ACTIVE         = $00000100;
  {$EXTERNALSYM ADS_PRINTER_IO_ACTIVE}
  ADS_PRINTER_BUSY              = $00000200;
  {$EXTERNALSYM ADS_PRINTER_BUSY}
  ADS_PRINTER_PRINTING          = $00000400;
  {$EXTERNALSYM ADS_PRINTER_PRINTING}
  ADS_PRINTER_OUTPUT_BIN_FULL   = $00000800;
  {$EXTERNALSYM ADS_PRINTER_OUTPUT_BIN_FULL}
  ADS_PRINTER_NOT_AVAILABLE     = $00001000;
  {$EXTERNALSYM ADS_PRINTER_NOT_AVAILABLE}
  ADS_PRINTER_WAITING           = $00002000;
  {$EXTERNALSYM ADS_PRINTER_WAITING}
  ADS_PRINTER_PROCESSING        = $00004000;
  {$EXTERNALSYM ADS_PRINTER_PROCESSING}
  ADS_PRINTER_INITIALIZING      = $00008000;
  {$EXTERNALSYM ADS_PRINTER_INITIALIZING}
  ADS_PRINTER_WARMING_UP        = $00010000;
  {$EXTERNALSYM ADS_PRINTER_WARMING_UP}
  ADS_PRINTER_TONER_LOW         = $00020000;
  {$EXTERNALSYM ADS_PRINTER_TONER_LOW}
  ADS_PRINTER_NO_TONER          = $00040000;
  {$EXTERNALSYM ADS_PRINTER_NO_TONER}
  ADS_PRINTER_PAGE_PUNT         = $00080000;
  {$EXTERNALSYM ADS_PRINTER_PAGE_PUNT}
  ADS_PRINTER_USER_INTERVENTION = $00100000;
  {$EXTERNALSYM ADS_PRINTER_USER_INTERVENTION}
  ADS_PRINTER_OUT_OF_MEMORY     = $00200000;
  {$EXTERNALSYM ADS_PRINTER_OUT_OF_MEMORY}
  ADS_PRINTER_DOOR_OPEN         = $00400000;
  {$EXTERNALSYM ADS_PRINTER_DOOR_OPEN}
  ADS_PRINTER_SERVER_UNKNOWN    = $00800000;
  {$EXTERNALSYM ADS_PRINTER_SERVER_UNKNOWN}
  ADS_PRINTER_POWER_SAVE        = $01000000;
  {$EXTERNALSYM ADS_PRINTER_POWER_SAVE}

//
// job status values
//

  ADS_JOB_PAUSED   = $00000001;
  {$EXTERNALSYM ADS_JOB_PAUSED}
  ADS_JOB_ERROR    = $00000002;
  {$EXTERNALSYM ADS_JOB_ERROR}
  ADS_JOB_DELETING = $00000004;
  {$EXTERNALSYM ADS_JOB_DELETING}
  ADS_JOB_SPOOLING = $00000008;
  {$EXTERNALSYM ADS_JOB_SPOOLING}
  ADS_JOB_PRINTING = $00000010;
  {$EXTERNALSYM ADS_JOB_PRINTING}
  ADS_JOB_OFFLINE  = $00000020;
  {$EXTERNALSYM ADS_JOB_OFFLINE}
  ADS_JOB_PAPEROUT = $00000040;
  {$EXTERNALSYM ADS_JOB_PAPEROUT}
  ADS_JOB_PRINTED  = $00000080;
  {$EXTERNALSYM ADS_JOB_PRINTED}
  ADS_JOB_DELETED  = $00000100;
  {$EXTERNALSYM ADS_JOB_DELETED}

//
// service status values
//

  ADS_SERVICE_STOPPED          = $00000001;
  {$EXTERNALSYM ADS_SERVICE_STOPPED}
  ADS_SERVICE_START_PENDING	   = $00000002;
  {$EXTERNALSYM ADS_SERVICE_START_PENDING	}
  ADS_SERVICE_STOP_PENDING     = $00000003;
  {$EXTERNALSYM ADS_SERVICE_STOP_PENDING}
  ADS_SERVICE_RUNNING	         = $00000004;
  {$EXTERNALSYM ADS_SERVICE_RUNNING	}
  ADS_SERVICE_CONTINUE_PENDING = $00000005;
  {$EXTERNALSYM ADS_SERVICE_CONTINUE_PENDING}
  ADS_SERVICE_PAUSE_PENDING	   = $00000006;
  {$EXTERNALSYM ADS_SERVICE_PAUSE_PENDING	}
  ADS_SERVICE_PAUSED           = $00000007;
  {$EXTERNALSYM ADS_SERVICE_PAUSED}
  ADS_SERVICE_ERROR            = $00000008;
  {$EXTERNALSYM ADS_SERVICE_ERROR}

//---------------------------------------------------------------------

//
// Service Type Valid Values
//

  ADS_SERVICE_OWN_PROCESS        = $00000010;
  {$EXTERNALSYM ADS_SERVICE_OWN_PROCESS}
  ADS_SERVICE_SHARE_PROCESS      = $00000020;
  {$EXTERNALSYM ADS_SERVICE_SHARE_PROCESS}
  ADS_SERVICE_KERNEL_DRIVER      = $00000001;
  {$EXTERNALSYM ADS_SERVICE_KERNEL_DRIVER}
  ADS_SERVICE_FILE_SYSTEM_DRIVER = $00000002;
  {$EXTERNALSYM ADS_SERVICE_FILE_SYSTEM_DRIVER}

//
// Start Type Valid Values
//

  ADS_SERVICE_BOOT_START   = SERVICE_BOOT_START;
  {$EXTERNALSYM ADS_SERVICE_BOOT_START}
  ADS_SERVICE_SYSTEM_START = SERVICE_SYSTEM_START;
  {$EXTERNALSYM ADS_SERVICE_SYSTEM_START}
  ADS_SERVICE_AUTO_START   = SERVICE_AUTO_START;
  {$EXTERNALSYM ADS_SERVICE_AUTO_START}
  ADS_SERVICE_DEMAND_START = SERVICE_DEMAND_START;
  {$EXTERNALSYM ADS_SERVICE_DEMAND_START}
  ADS_SERVICE_DISABLED     = SERVICE_DISABLED;
  {$EXTERNALSYM ADS_SERVICE_DISABLED}

//
// Error Control Values
//

  ADS_SERVICE_ERROR_IGNORE   = 0;
  {$EXTERNALSYM ADS_SERVICE_ERROR_IGNORE}
  ADS_SERVICE_ERROR_NORMAL   = 1;
  {$EXTERNALSYM ADS_SERVICE_ERROR_NORMAL}
  ADS_SERVICE_ERROR_SEVERE   = 2;
  {$EXTERNALSYM ADS_SERVICE_ERROR_SEVERE}
  ADS_SERVICE_ERROR_CRITICAL = 3;
  {$EXTERNALSYM ADS_SERVICE_ERROR_CRITICAL}

implementation

end.
