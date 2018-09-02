{******************************************************************************}
{                                                       	               }
{ System Event Notification Services API interface Unit for Object Pascal      }
{                                                       	               }
{ Portions created by Microsoft are Copyright (C) 1995-2001 Microsoft          }
{ Corporation. All Rights Reserved.                                            }
{ 								               }
{ The original file is: sens.h, released March 2003. The original Pascal       }
{ code is: Sens.pas, released April 2003. The initial developer of the         }
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

unit JwaSens;

{$WEAKPACKAGEUNIT}

{$HPPEMIT ''}
{$HPPEMIT '#include "Sens.h"'}
{$HPPEMIT ''}

{$I WINDEFINES.INC}

interface

//
// Constants
//

const
  CONNECTION_LAN  = $00000001;
  {$EXTERNALSYM CONNECTION_LAN}
  CONNECTION_WAN  = $00000002;
  {$EXTERNALSYM CONNECTION_WAN}
  CONNECTION_AOL  = $00000004;
  {$EXTERNALSYM CONNECTION_AOL}

//
// SENS Guids related to Event System
//

  SENSGUID_PUBLISHER: TGUID = '{5fee1bd6-5b9b-11d1-8dd2-00aa004abd5e}';
  {$EXTERNALSYM SENSGUID_PUBLISHER}
  SENSGUID_SUBSCRIBER_LCE: TGUID = '{d3938ab0-5b9d-11d1-8dd2-00aa004abd5e}';
  {$EXTERNALSYM SENSGUID_SUBSCRIBER_LCE}
  SENSGUID_SUBSCRIBER_WININET: TGUID = '{d3938ab5-5b9d-11d1-8dd2-00aa004abd5e}';
  {$EXTERNALSYM SENSGUID_SUBSCRIBER_WININET}

//
// Classes of Events published by SENS
//

  SENSGUID_EVENTCLASS_NETWORK: TGUID = '{d5978620-5b9f-11d1-8dd2-00aa004abd5e}';
  {$EXTERNALSYM SENSGUID_EVENTCLASS_NETWORK}
  SENSGUID_EVENTCLASS_LOGON: TGUID = '{d5978630-5b9f-11d1-8dd2-00aa004abd5e}';
  {$EXTERNALSYM SENSGUID_EVENTCLASS_LOGON}
  SENSGUID_EVENTCLASS_ONNOW: TGUID = '{d5978640-5b9f-11d1-8dd2-00aa004abd5e}';
  {$EXTERNALSYM SENSGUID_EVENTCLASS_ONNOW}
  SENSGUID_EVENTCLASS_LOGON2: TGUID = '{d5978650-5b9f-11d1-8dd2-00aa004abd5e}';
  {$EXTERNALSYM SENSGUID_EVENTCLASS_LOGON2}

implementation

end.
