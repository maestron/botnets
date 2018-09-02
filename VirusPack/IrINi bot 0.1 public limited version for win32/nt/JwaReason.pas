{******************************************************************************}
{                                                       	               }
{ Windows Shutdown Reason Codes interface Unit for Object Pascal               }
{                                                       	               }
{ Portions created by Microsoft are Copyright (C) 1995-2001 Microsoft          }
{ Corporation. All Rights Reserved.                                            }
{ 								               }
{ The original file is: reason.h, released June 2000. The original Pascal      }
{ code is: Reason.pas, released December 2000. The initial developer of the    }
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

unit JwaReason;

{$WEAKPACKAGEUNIT}

{$HPPEMIT ''}
{$HPPEMIT '#include "WinReg.h"'}
{$HPPEMIT ''}

{$I WINDEFINES.INC}

interface

uses
  JwaWinType;

// Reason flags

// Flags used by the various UIs.

const
  SHTDN_REASON_FLAG_COMMENT_REQUIRED          = $01000000;
  {$EXTERNALSYM SHTDN_REASON_FLAG_COMMENT_REQUIRED}
  SHTDN_REASON_FLAG_DIRTY_PROBLEM_ID_REQUIRED = $02000000;
  {$EXTERNALSYM SHTDN_REASON_FLAG_DIRTY_PROBLEM_ID_REQUIRED}
  SHTDN_REASON_FLAG_CLEAN_UI                  = $04000000;
  {$EXTERNALSYM SHTDN_REASON_FLAG_CLEAN_UI}
  SHTDN_REASON_FLAG_DIRTY_UI                  = $08000000;
  {$EXTERNALSYM SHTDN_REASON_FLAG_DIRTY_UI}

// Flags that end up in the event log code.

  SHTDN_REASON_FLAG_USER_DEFINED = $40000000;
  {$EXTERNALSYM SHTDN_REASON_FLAG_USER_DEFINED}
  SHTDN_REASON_FLAG_PLANNED      = DWORD($80000000);
  {$EXTERNALSYM SHTDN_REASON_FLAG_PLANNED}

// Microsoft major reasons.

  SHTDN_REASON_MAJOR_OTHER           = $00000000;
  {$EXTERNALSYM SHTDN_REASON_MAJOR_OTHER}
  SHTDN_REASON_MAJOR_NONE            = $00000000;
  {$EXTERNALSYM SHTDN_REASON_MAJOR_NONE}
  SHTDN_REASON_MAJOR_HARDWARE        = $00010000;
  {$EXTERNALSYM SHTDN_REASON_MAJOR_HARDWARE}
  SHTDN_REASON_MAJOR_OPERATINGSYSTEM = $00020000;
  {$EXTERNALSYM SHTDN_REASON_MAJOR_OPERATINGSYSTEM}
  SHTDN_REASON_MAJOR_SOFTWARE        = $00030000;
  {$EXTERNALSYM SHTDN_REASON_MAJOR_SOFTWARE}
  SHTDN_REASON_MAJOR_APPLICATION     = $00040000;
  {$EXTERNALSYM SHTDN_REASON_MAJOR_APPLICATION}
  SHTDN_REASON_MAJOR_SYSTEM          = $00050000;
  {$EXTERNALSYM SHTDN_REASON_MAJOR_SYSTEM}
  SHTDN_REASON_MAJOR_POWER           = $00060000;
  {$EXTERNALSYM SHTDN_REASON_MAJOR_POWER}
  SHTDN_REASON_MAJOR_LEGACY_API      = $00070000;
  {$EXTERNALSYM SHTDN_REASON_MAJOR_LEGACY_API}

// Microsoft minor reasons.

  SHTDN_REASON_MINOR_OTHER           = $00000000;
  {$EXTERNALSYM SHTDN_REASON_MINOR_OTHER}
  SHTDN_REASON_MINOR_NONE            = $000000ff;
  {$EXTERNALSYM SHTDN_REASON_MINOR_NONE}
  SHTDN_REASON_MINOR_MAINTENANCE     = $00000001;
  {$EXTERNALSYM SHTDN_REASON_MINOR_MAINTENANCE}
  SHTDN_REASON_MINOR_INSTALLATION    = $00000002;
  {$EXTERNALSYM SHTDN_REASON_MINOR_INSTALLATION}
  SHTDN_REASON_MINOR_UPGRADE         = $00000003;
  {$EXTERNALSYM SHTDN_REASON_MINOR_UPGRADE}
  SHTDN_REASON_MINOR_RECONFIG        = $00000004;
  {$EXTERNALSYM SHTDN_REASON_MINOR_RECONFIG}
  SHTDN_REASON_MINOR_HUNG            = $00000005;
  {$EXTERNALSYM SHTDN_REASON_MINOR_HUNG}
  SHTDN_REASON_MINOR_UNSTABLE        = $00000006;
  {$EXTERNALSYM SHTDN_REASON_MINOR_UNSTABLE}
  SHTDN_REASON_MINOR_DISK            = $00000007;
  {$EXTERNALSYM SHTDN_REASON_MINOR_DISK}
  SHTDN_REASON_MINOR_PROCESSOR       = $00000008;
  {$EXTERNALSYM SHTDN_REASON_MINOR_PROCESSOR}
  SHTDN_REASON_MINOR_NETWORKCARD     = $00000009;
  {$EXTERNALSYM SHTDN_REASON_MINOR_NETWORKCARD}
  SHTDN_REASON_MINOR_POWER_SUPPLY    = $0000000a;
  {$EXTERNALSYM SHTDN_REASON_MINOR_POWER_SUPPLY}
  SHTDN_REASON_MINOR_CORDUNPLUGGED   = $0000000b;
  {$EXTERNALSYM SHTDN_REASON_MINOR_CORDUNPLUGGED}
  SHTDN_REASON_MINOR_ENVIRONMENT     = $0000000c;
  {$EXTERNALSYM SHTDN_REASON_MINOR_ENVIRONMENT}
  SHTDN_REASON_MINOR_HARDWARE_DRIVER = $0000000d;
  {$EXTERNALSYM SHTDN_REASON_MINOR_HARDWARE_DRIVER}
  SHTDN_REASON_MINOR_OTHERDRIVER     = $0000000e;
  {$EXTERNALSYM SHTDN_REASON_MINOR_OTHERDRIVER}
  SHTDN_REASON_MINOR_BLUESCREEN      = $0000000F;
  {$EXTERNALSYM SHTDN_REASON_MINOR_BLUESCREEN}
  SHTDN_REASON_MINOR_SERVICEPACK           = $00000010;
  {$EXTERNALSYM SHTDN_REASON_MINOR_SERVICEPACK}
  SHTDN_REASON_MINOR_HOTFIX                = $00000011;
  {$EXTERNALSYM SHTDN_REASON_MINOR_HOTFIX}
  SHTDN_REASON_MINOR_SECURITYFIX           = $00000012;
  {$EXTERNALSYM SHTDN_REASON_MINOR_SECURITYFIX}
  SHTDN_REASON_MINOR_SECURITY              = $00000013;
  {$EXTERNALSYM SHTDN_REASON_MINOR_SECURITY}
  SHTDN_REASON_MINOR_NETWORK_CONNECTIVITY  = $00000014;
  {$EXTERNALSYM SHTDN_REASON_MINOR_NETWORK_CONNECTIVITY}
  SHTDN_REASON_MINOR_WMI                   = $00000015;
  {$EXTERNALSYM SHTDN_REASON_MINOR_WMI}
  SHTDN_REASON_MINOR_SERVICEPACK_UNINSTALL = $00000016;
  {$EXTERNALSYM SHTDN_REASON_MINOR_SERVICEPACK_UNINSTALL}
  SHTDN_REASON_MINOR_HOTFIX_UNINSTALL      = $00000017;
  {$EXTERNALSYM SHTDN_REASON_MINOR_HOTFIX_UNINSTALL}
  SHTDN_REASON_MINOR_SECURITYFIX_UNINSTALL = $00000018;
  {$EXTERNALSYM SHTDN_REASON_MINOR_SECURITYFIX_UNINSTALL}
  SHTDN_REASON_MINOR_MMC                   = $00000019;
  {$EXTERNALSYM SHTDN_REASON_MINOR_MMC}
  SHTDN_REASON_MINOR_TERMSRV               = $00000020;
  {$EXTERNALSYM SHTDN_REASON_MINOR_TERMSRV}
  SHTDN_REASON_MINOR_DC_PROMOTION          = $00000021;
  {$EXTERNALSYM SHTDN_REASON_MINOR_DC_PROMOTION}
  SHTDN_REASON_MINOR_DC_DEMOTION           = $00000022;
  {$EXTERNALSYM SHTDN_REASON_MINOR_DC_DEMOTION}

  SHTDN_REASON_UNKNOWN = SHTDN_REASON_MINOR_NONE;
  {$EXTERNALSYM SHTDN_REASON_UNKNOWN}
  SHTDN_REASON_LEGACY_API = (SHTDN_REASON_MAJOR_LEGACY_API or SHTDN_REASON_FLAG_PLANNED);
  {$EXTERNALSYM SHTDN_REASON_LEGACY_API}

// This mask cuts out UI flags.

  SHTDN_REASON_VALID_BIT_MASK = DWORD($c0ffffff);
  {$EXTERNALSYM SHTDN_REASON_VALID_BIT_MASK}

// Convenience flags.

  PCLEANUI = (SHTDN_REASON_FLAG_PLANNED or SHTDN_REASON_FLAG_CLEAN_UI);
  {$EXTERNALSYM PCLEANUI}
  UCLEANUI = (SHTDN_REASON_FLAG_CLEAN_UI);
  {$EXTERNALSYM UCLEANUI}
  PDIRTYUI = (SHTDN_REASON_FLAG_PLANNED or SHTDN_REASON_FLAG_DIRTY_UI);
  {$EXTERNALSYM PDIRTYUI}
  UDIRTYUI = (SHTDN_REASON_FLAG_DIRTY_UI);
  {$EXTERNALSYM UDIRTYUI}

(*
 * Maximum character lengths for reason name, description, problem id, and
 * comment respectively.
 *)

  MAX_REASON_NAME_LEN    = 64;
  {$EXTERNALSYM MAX_REASON_NAME_LEN}
  MAX_REASON_DESC_LEN    = 256;
  {$EXTERNALSYM MAX_REASON_DESC_LEN}
  MAX_REASON_BUGID_LEN   = 32;
  {$EXTERNALSYM MAX_REASON_BUGID_LEN}
  MAX_REASON_COMMENT_LEN = 512;
  {$EXTERNALSYM MAX_REASON_COMMENT_LEN}
  SHUTDOWN_TYPE_LEN      = 32;
  {$EXTERNALSYM SHUTDOWN_TYPE_LEN}

(*
 *	S.E.T. policy value
 *
 *)

  POLICY_SHOWREASONUI_NEVER	      = 0;
  {$EXTERNALSYM POLICY_SHOWREASONUI_NEVER}
  POLICY_SHOWREASONUI_ALWAYS	      = 1;
  {$EXTERNALSYM POLICY_SHOWREASONUI_ALWAYS}
  POLICY_SHOWREASONUI_WORKSTATIONONLY =	2;
  {$EXTERNALSYM POLICY_SHOWREASONUI_WORKSTATIONONLY}
  POLICY_SHOWREASONUI_SERVERONLY      = 3;
  {$EXTERNALSYM POLICY_SHOWREASONUI_SERVERONLY}

(*
 * Snapshot policy values
 *)

  SNAPSHOT_POLICY_NEVER           = 0;
  {$EXTERNALSYM SNAPSHOT_POLICY_NEVER}
  SNAPSHOT_POLICY_ALWAYS          = 1;
  {$EXTERNALSYM SNAPSHOT_POLICY_ALWAYS}
  SNAPSHOT_POLICY_UNPLANNED       = 2;
  {$EXTERNALSYM SNAPSHOT_POLICY_UNPLANNED}

(*
 * Maximue user defined reasons
 *)

  MAX_NUM_REASONS = 256;
  {$EXTERNALSYM MAX_NUM_REASONS}

implementation

end.
