{******************************************************************************}
{                                                       	               }
{ Win32 color dialog API interface Unit for Object Pascal                      }
{                                                       	               }
{ Portions created by Microsoft are Copyright (C) 1995-2001 Microsoft          }
{ Corporation. All Rights Reserved.                                            }
{ 								               }
{ The original file is: colordlg.h, released June 2000. The original Pascal    }
{ code is: ColorDlg.pas, released December 2000. The initial developer of the  }
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

unit JwaColorDlg;

{$WEAKPACKAGEUNIT}

{$HPPEMIT ''}
{$HPPEMIT '#include "colordlg.h"'}
{$HPPEMIT ''}

{$I WINDEFINES.INC}

interface

//
//  Constant Declarations.
//

const
  DLG_COLOR = 10;
  {$EXTERNALSYM DLG_COLOR}

  COLOR_HUESCROLL = 700; // color dialog
  {$EXTERNALSYM COLOR_HUESCROLL}
  COLOR_SATSCROLL = 701;
  {$EXTERNALSYM COLOR_SATSCROLL}
  COLOR_LUMSCROLL = 702;
  {$EXTERNALSYM COLOR_LUMSCROLL}
  COLOR_HUE       = 703;
  {$EXTERNALSYM COLOR_HUE}
  COLOR_SAT       = 704;
  {$EXTERNALSYM COLOR_SAT}
  COLOR_LUM       = 705;
  {$EXTERNALSYM COLOR_LUM}
  COLOR_RED       = 706;
  {$EXTERNALSYM COLOR_RED}
  COLOR_GREEN     = 707;
  {$EXTERNALSYM COLOR_GREEN}
  COLOR_BLUE      = 708;
  {$EXTERNALSYM COLOR_BLUE}
  COLOR_CURRENT   = 709;
  {$EXTERNALSYM COLOR_CURRENT}
  COLOR_RAINBOW   = 710;
  {$EXTERNALSYM COLOR_RAINBOW}
  COLOR_SAVE      = 711;
  {$EXTERNALSYM COLOR_SAVE}
  COLOR_ADD       = 712;
  {$EXTERNALSYM COLOR_ADD}
  COLOR_SOLID     = 713;
  {$EXTERNALSYM COLOR_SOLID}
  COLOR_TUNE      = 714;
  {$EXTERNALSYM COLOR_TUNE}
  COLOR_SCHEMES   = 715;
  {$EXTERNALSYM COLOR_SCHEMES}
  COLOR_ELEMENT   = 716;
  {$EXTERNALSYM COLOR_ELEMENT}
  COLOR_SAMPLES   = 717;
  {$EXTERNALSYM COLOR_SAMPLES}
  COLOR_PALETTE   = 718;
  {$EXTERNALSYM COLOR_PALETTE}
  COLOR_MIX       = 719;
  {$EXTERNALSYM COLOR_MIX}
  COLOR_BOX1      = 720;
  {$EXTERNALSYM COLOR_BOX1}
  COLOR_CUSTOM1   = 721;
  {$EXTERNALSYM COLOR_CUSTOM1}

  COLOR_HUEACCEL   = 723;
  {$EXTERNALSYM COLOR_HUEACCEL}
  COLOR_SATACCEL   = 724;
  {$EXTERNALSYM COLOR_SATACCEL}
  COLOR_LUMACCEL   = 725;
  {$EXTERNALSYM COLOR_LUMACCEL}
  COLOR_REDACCEL   = 726;
  {$EXTERNALSYM COLOR_REDACCEL}
  COLOR_GREENACCEL = 727;
  {$EXTERNALSYM COLOR_GREENACCEL}
  COLOR_BLUEACCEL  = 728;
  {$EXTERNALSYM COLOR_BLUEACCEL}

  COLOR_SOLID_LEFT  = 730;
  {$EXTERNALSYM COLOR_SOLID_LEFT}
  COLOR_SOLID_RIGHT = 731;
  {$EXTERNALSYM COLOR_SOLID_RIGHT}

  NUM_BASIC_COLORS  = 48;
  {$EXTERNALSYM NUM_BASIC_COLORS}
  NUM_CUSTOM_COLORS = 16;
  {$EXTERNALSYM NUM_CUSTOM_COLORS}

implementation

end.
