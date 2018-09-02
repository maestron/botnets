{******************************************************************************}
{                                                       	               }
{ Multimedia Systems Media Control API interface Unit for Object Pascal        }
{                                                       	               }
{ Portions created by Microsoft are Copyright (C) 1995-2001 Microsoft          }
{ Corporation. All Rights Reserved.                                            }
{ 								               }
{ The original file is: MciAvi.h, released June 2000. The original Pascal      }
{ code is: MciAvi.pas, released December 2000. The initial developer of the    }
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

unit JwaMciAvi;

{$WEAKPACKAGEUNIT}

{$HPPEMIT ''}
{$HPPEMIT '#include "MciAvi.h"'}
{$HPPEMIT ''}

{$I WINDEFINES.INC}

interface

(*
** These three flags apply to the 'play' command:
**	play <alias> window		Play in normal window
**	play <alias> fullscreen		Play in 320x240 full-screen mode
**	play <alias> fullscreen by 2	Play fullscreen, zoomed by 2
*)

const
  MCI_MCIAVI_PLAY_WINDOW     = $01000000;
  {$EXTERNALSYM MCI_MCIAVI_PLAY_WINDOW}
  MCI_MCIAVI_PLAY_FULLSCREEN = $02000000;
  {$EXTERNALSYM MCI_MCIAVI_PLAY_FULLSCREEN}
  MCI_MCIAVI_PLAY_FULLBY2    = $04000000;
  {$EXTERNALSYM MCI_MCIAVI_PLAY_FULLBY2}

(*
** Debugging constants for AVI diagnostics
*)

(*
** Returns number of frames not drawn during last play.  If this number
** is more than a small fraction of the number of frames that should have
** been displayed, things aren't looking good.
*)

  MCI_AVI_STATUS_FRAMES_SKIPPED = $8001;
  {$EXTERNALSYM MCI_AVI_STATUS_FRAMES_SKIPPED}

(*
** Returns a number representing how well the last AVI play worked.
** A result of 1000 indicates that the AVI sequence took the amount
** of time to play that it should have; a result of 2000, for instance,
** would indicate that a 5-second AVI sequence took 10 seconds to play,
** implying that the audio and video were badly broken up.
*)

  MCI_AVI_STATUS_LAST_PLAY_SPEED = $8002;
  {$EXTERNALSYM MCI_AVI_STATUS_LAST_PLAY_SPEED}

(*
** Returns the number of times that the audio definitely broke up.
** (We count one for every time we're about to write some audio data
** to the driver, and we notice that it's already played all of the
** data we have.
*)

  MCI_AVI_STATUS_AUDIO_BREAKS = $8003;
  {$EXTERNALSYM MCI_AVI_STATUS_AUDIO_BREAKS}

  MCI_AVI_SETVIDEO_DRAW_PROCEDURE = $8000;
  {$EXTERNALSYM MCI_AVI_SETVIDEO_DRAW_PROCEDURE}

  MCI_AVI_SETVIDEO_PALETTE_COLOR = $8100;
  {$EXTERNALSYM MCI_AVI_SETVIDEO_PALETTE_COLOR}

(*
** This constant specifies that the "halftone" palette should be
** used, rather than the default palette.
*)

  MCI_AVI_SETVIDEO_PALETTE_HALFTONE = $0000FFFF;
  {$EXTERNALSYM MCI_AVI_SETVIDEO_PALETTE_HALFTONE}

(*
**	Custom error return values
*)

  // TODO FROM MMSysytem.h

  MCIERR_BASE               = 256;
  MCIERR_CUSTOM_DRIVER_BASE = (MCIERR_BASE + 256);

  MCIERR_AVI_OLDAVIFORMAT       = (MCIERR_CUSTOM_DRIVER_BASE + 100);
  {$EXTERNALSYM MCIERR_AVI_OLDAVIFORMAT}
  MCIERR_AVI_NOTINTERLEAVED     = (MCIERR_CUSTOM_DRIVER_BASE + 101);
  {$EXTERNALSYM MCIERR_AVI_NOTINTERLEAVED}
  MCIERR_AVI_NODISPDIB          = (MCIERR_CUSTOM_DRIVER_BASE + 102);
  {$EXTERNALSYM MCIERR_AVI_NODISPDIB}
  MCIERR_AVI_CANTPLAYFULLSCREEN = (MCIERR_CUSTOM_DRIVER_BASE + 103);
  {$EXTERNALSYM MCIERR_AVI_CANTPLAYFULLSCREEN}
  MCIERR_AVI_TOOBIGFORVGA       = (MCIERR_CUSTOM_DRIVER_BASE + 104);
  {$EXTERNALSYM MCIERR_AVI_TOOBIGFORVGA}
  MCIERR_AVI_NOCOMPRESSOR       = (MCIERR_CUSTOM_DRIVER_BASE + 105);
  {$EXTERNALSYM MCIERR_AVI_NOCOMPRESSOR}
  MCIERR_AVI_DISPLAYERROR       = (MCIERR_CUSTOM_DRIVER_BASE + 106);
  {$EXTERNALSYM MCIERR_AVI_DISPLAYERROR}
  MCIERR_AVI_AUDIOERROR         = (MCIERR_CUSTOM_DRIVER_BASE + 107);
  {$EXTERNALSYM MCIERR_AVI_AUDIOERROR}
  MCIERR_AVI_BADPALETTE         = (MCIERR_CUSTOM_DRIVER_BASE + 108);
  {$EXTERNALSYM MCIERR_AVI_BADPALETTE}

implementation

end.
