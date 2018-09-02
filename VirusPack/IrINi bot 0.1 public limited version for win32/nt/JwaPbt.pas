{******************************************************************************}
{                                                       	               }
{ Power Event Message Definitions API interface Unit for Object Pascal         }
{                                                       	               }
{ Portions created by Microsoft are Copyright (C) 1995-2001 Microsoft          }
{ Corporation. All Rights Reserved.                                            }
{ 								               }
{ The original file is: pbt.h, released June 2000. The original Pascal         }
{ code is: Pbt.pas, released December 2000. The initial developer of the       }
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

unit JwaPbt;

{$WEAKPACKAGEUNIT}

{$HPPEMIT ''}
{$HPPEMIT '#include "pbt.h"'}
{$HPPEMIT ''}

{$I WINDEFINES.INC}

interface

const
  WM_POWERBROADCAST             = $0218;
  {$EXTERNALSYM WM_POWERBROADCAST}

  PBT_APMQUERYSUSPEND           = $0000;
  {$EXTERNALSYM PBT_APMQUERYSUSPEND}
  PBT_APMQUERYSTANDBY           = $0001;
  {$EXTERNALSYM PBT_APMQUERYSTANDBY}

  PBT_APMQUERYSUSPENDFAILED     = $0002;
  {$EXTERNALSYM PBT_APMQUERYSUSPENDFAILED}
  PBT_APMQUERYSTANDBYFAILED     = $0003;
  {$EXTERNALSYM PBT_APMQUERYSTANDBYFAILED}

  PBT_APMSUSPEND                = $0004;
  {$EXTERNALSYM PBT_APMSUSPEND}
  PBT_APMSTANDBY                = $0005;
  {$EXTERNALSYM PBT_APMSTANDBY}

  PBT_APMRESUMECRITICAL         = $0006;
  {$EXTERNALSYM PBT_APMRESUMECRITICAL}
  PBT_APMRESUMESUSPEND          = $0007;
  {$EXTERNALSYM PBT_APMRESUMESUSPEND}
  PBT_APMRESUMESTANDBY          = $0008;
  {$EXTERNALSYM PBT_APMRESUMESTANDBY}

  PBTF_APMRESUMEFROMFAILURE     = $00000001;
  {$EXTERNALSYM PBTF_APMRESUMEFROMFAILURE}

  PBT_APMBATTERYLOW             = $0009;
  {$EXTERNALSYM PBT_APMBATTERYLOW}
  PBT_APMPOWERSTATUSCHANGE      = $000A;
  {$EXTERNALSYM PBT_APMPOWERSTATUSCHANGE}

  PBT_APMOEMEVENT               = $000B;
  {$EXTERNALSYM PBT_APMOEMEVENT}
  PBT_APMRESUMEAUTOMATIC        = $0012;
  {$EXTERNALSYM PBT_APMRESUMEAUTOMATIC}

implementation

end.
