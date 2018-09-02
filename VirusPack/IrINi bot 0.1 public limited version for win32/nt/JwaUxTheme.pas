{******************************************************************************}
{                                                       	               }
{ Visual Styles (Themes) API interface Unit for Object Pascal                  }
{                                                       	               }
{ Portions created by Microsoft are Copyright (C) 1995-2001 Microsoft          }
{ Corporation. All Rights Reserved.                                            }
{ 								               }
{ The original file is: uxtheme.h, released June 2001. The original Pascal     }
{ code is: UxTheme.pas, released July 2001. The initial developer of the       }
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

unit JwaUxTheme;

{$WEAKPACKAGEUNIT}

{$HPPEMIT ''}
{$HPPEMIT '#include "uxtheme.h"'}
{$HPPEMIT ''}

{$I WINDEFINES.INC}

interface

uses
  JwaWinType, JwaWinGDI;

type
  HIMAGELIST = HANDLE; // TODO TEMPORARY

type
  HTHEME = HANDLE;          // handle to a section of theme data for class
  {$EXTERNALSYM HTHEME}

//---------------------------------------------------------------------------
// NOTE: PartId's and StateId's used in the theme API are defined in the
//       hdr file <tmschema.h> using the TM_PART and TM_STATE macros.  For
//       example, "TM_PART(BP, PUSHBUTTON)" defines the PartId "BP_PUSHBUTTON".

//---------------------------------------------------------------------------
//  OpenThemeData()     - Open the theme data for the specified HWND and
//                        semi-colon separated list of class names.
//
//                        OpenThemeData() will try each class name, one at
//                        a time, and use the first matching theme info
//                        found.  If a match is found, a theme handle
//                        to the data is returned.  If no match is found,
//                        a "NULL" handle is returned.
//
//                        When the window is destroyed or a WM_THEMECHANGED
//                        msg is received, "CloseThemeData()" should be
//                        called to close the theme handle.
//
//  hwnd                - window handle of the control/window to be themed
//
//  pszClassList        - class name (or list of names) to match to theme data
//                        section.  if the list contains more than one name,
//                        the names are tested one at a time for a match.
//                        If a match is found, OpenThemeData() returns a
//                        theme handle associated with the matching class.
//                        This param is a list (instead of just a single
//                        class name) to provide the class an opportunity
//                        to get the "best" match between the class and
//                        the current theme.  For example, a button might
//                        pass L"OkButton, Button" if its ID=ID_OK.  If
//                        the current theme has an entry for OkButton,
//                        that will be used.  Otherwise, we fall back on
//                        the normal Button entry.
//---------------------------------------------------------------------------

function OpenThemeData(hwnd: HWND; pszClassList: LPCWSTR): HTHEME; stdcall;
{$EXTERNALSYM OpenThemeData}

//---------------------------------------------------------------------------
//  CloseTHemeData()    - closes the theme data handle.  This should be done
//                        when the window being themed is destroyed or
//                        whenever a WM_THEMECHANGED msg is received
//                        (followed by an attempt to create a new Theme data
//                        handle).
//
//  hTheme              - open theme data handle (returned from prior call
//                        to OpenThemeData() API).
//---------------------------------------------------------------------------

function CloseThemeData(hTheme: HTHEME): HRESULT; stdcall;
{$EXTERNALSYM CloseThemeData}

//---------------------------------------------------------------------------
//    functions for basic drawing support
//---------------------------------------------------------------------------
// The following methods are the theme-aware drawing services.
// Controls/Windows are defined in drawable "parts" by their author: a
// parent part and 0 or more child parts.  Each of the parts can be
// described in "states" (ex: disabled, hot, pressed).
//---------------------------------------------------------------------------
// For the list of all themed classes and the definition of all
// parts and states, see the file "tmschmea.h".
//---------------------------------------------------------------------------
// Each of the below methods takes a "iPartId" param to specify the
// part and a "iStateId" to specify the state of the part.
// "iStateId=0" refers to the root part.  "iPartId" = "0" refers to
// the root class.
//-----------------------------------------------------------------------
// Note: draw operations are always scaled to fit (and not to exceed)
// the specified "Rect".
//-----------------------------------------------------------------------

//------------------------------------------------------------------------
//  DrawThemeBackground()
//                      - draws the theme-specified border and fill for
//                        the "iPartId" and "iStateId".  This could be
//                        based on a bitmap file, a border and fill, or
//                        other image description.
//
//  hTheme              - theme data handle
//  hdc                 - HDC to draw into
//  iPartId             - part number to draw
//  iStateId            - state number (of the part) to draw
//  pRect               - defines the size/location of the part
//  pClipRect           - optional clipping rect (don't draw outside it)
//------------------------------------------------------------------------

function DrawThemeBackground(hTheme: HTHEME; hdc: HDC; iPartId, iStateId: Integer;
  const pRect: RECT; pClipRect: PRECT): HRESULT; stdcall;
{$EXTERNALSYM DrawThemeBackground}

//---------------------------------------------------------------------------
//----- DrawThemeText() flags ----

const
  DTT_GRAYED = $1;         // draw a grayed-out string
  {$EXTERNALSYM DTT_GRAYED}

//-------------------------------------------------------------------------
//  DrawThemeText()     - draws the text using the theme-specified
//                        color and font for the "iPartId" and
//                        "iStateId".
//
//  hTheme              - theme data handle
//  hdc                 - HDC to draw into
//  iPartId             - part number to draw
//  iStateId            - state number (of the part) to draw
//  pszText             - actual text to draw
//  dwCharCount         - number of chars to draw (-1 for all)
//  dwTextFlags         - same as DrawText() "uFormat" param
//  dwTextFlags2        - additional drawing options
//  pRect               - defines the size/location of the part
//-------------------------------------------------------------------------

function DrawThemeText(hTheme: HTHEME; hdc: HDC; iPartId, iStateId: Integer;
  pszText: LPCWSTR; iCharCount: Integer; dwTextFlags, dwTextFlags2: DWORD;
  const pRect: RECT): HRESULT; stdcall;
{$EXTERNALSYM DrawThemeText}

//-------------------------------------------------------------------------
//  GetThemeBackgroundContentRect()
//                      - gets the size of the content for the theme-defined
//                        background.  This is usually the area inside
//                        the borders or Margins.
//
//      hTheme          - theme data handle
//      hdc             - (optional) device content to be used for drawing
//      iPartId         - part number to draw
//      iStateId        - state number (of the part) to draw
//      pBoundingRect   - the outer RECT of the part being drawn
//      pContentRect    - RECT to receive the content area
//-------------------------------------------------------------------------

function GetThemeBackgroundContentRect(hTheme: HTHEME; hdc: HDC; iPartId, iStateId: Integer;
  const pBoundingRect: RECT; pContentRect: PRECT): HRESULT; stdcall;
{$EXTERNALSYM GetThemeBackgroundContentRect}

//-------------------------------------------------------------------------
//  GetThemeBackgroundExtent() - calculates the size/location of the theme-
//                               specified background based on the
//                               "pContentRect".
//
//      hTheme          - theme data handle
//      hdc             - (optional) device content to be used for drawing
//      iPartId         - part number to draw
//      iStateId        - state number (of the part) to draw
//      pContentRect    - RECT that defines the content area
//      pBoundingRect   - RECT to receive the overall size/location of part
//-------------------------------------------------------------------------

function GetThemeBackgroundExtent(hTheme: HTHEME; hdc: HDC; iPartId, iStateId: Integer;
  const pContentRect: RECT; var pExtentRect: RECT): HRESULT; stdcall;
{$EXTERNALSYM GetThemeBackgroundExtent}

//-------------------------------------------------------------------------

type
  THEMESIZE = (
    TS_MIN,             // minimum size
    TS_TRUE,            // size without stretching
    TS_DRAW);           // size that theme mgr will use to draw part
  {$EXTERNALSYM THEMESIZE}
  TThemeSize = THEMESIZE;

//-------------------------------------------------------------------------
//  GetThemePartSize() - returns the specified size of the theme part
//
//  hTheme              - theme data handle
//  hdc                 - HDC to select font into & measure against
//  iPartId             - part number to retrieve size for
//  iStateId            - state number (of the part)
//  prc                 - (optional) rect for part drawing destination
//  eSize               - the type of size to be retreived
//  psz                 - receives the specified size of the part
//-------------------------------------------------------------------------

function GetThemePartSize(hTheme: HTHEME; hdc: HDC; iPartId, iStateId: Integer;
  prc: PRECT; eSize: THEMESIZE; var psz: TSize): HRESULT; stdcall;
{$EXTERNALSYM GetThemePartSize}

//-------------------------------------------------------------------------
//  GetThemeTextExtent() - calculates the size/location of the specified
//                         text when rendered in the Theme Font.
//
//  hTheme              - theme data handle
//  hdc                 - HDC to select font & measure into
//  iPartId             - part number to draw
//  iStateId            - state number (of the part)
//  pszText             - the text to be measured
//  dwCharCount         - number of chars to draw (-1 for all)
//  dwTextFlags         - same as DrawText() "uFormat" param
//  pszBoundingRect     - optional: to control layout of text
//  pszExtentRect       - receives the RECT for text size/location
//-------------------------------------------------------------------------

function GetThemeTextExtent(hTheme: HTHEME; hdc: HDC; iPartId, iStateId: Integer;
  pszText: LPCWSTR; iCharCount: Integer; dwTextFlags: DWORD; pBoundingRect: PRECT;
  var pExtentRect: RECT): HRESULT; stdcall;
{$EXTERNALSYM GetThemeTextExtent}

//-------------------------------------------------------------------------
//  GetThemeTextMetrics()
//                      - returns info about the theme-specified font
//                        for the part/state passed in.
//
//  hTheme              - theme data handle
//  hdc                 - optional: HDC for screen context
//  iPartId             - part number to draw
//  iStateId            - state number (of the part)
//  ptm                 - receives the font info
//-------------------------------------------------------------------------

function GetThemeTextMetrics(hTheme: HTHEME; hdc: HDC; iPartId, iStateId: Integer;
  var ptm: TEXTMETRIC): HRESULT; stdcall;
{$EXTERNALSYM GetThemeTextMetrics}

//-------------------------------------------------------------------------
//  GetThemeBackgroundRegion()
//                      - computes the region for a regular or partially
//                        transparent theme-specified background that is
//                        bound by the specified "pRect".
//                        If the rectangle is empty, sets the HRGN to NULL
//                        and return S_FALSE.
//
//  hTheme              - theme data handle
//  hdc                 - optional HDC to draw into (DPI scaling)
//  iPartId             - part number to draw
//  iStateId            - state number (of the part)
//  pRect               - the RECT used to draw the part
//  pRegion             - receives handle to calculated region
//-------------------------------------------------------------------------

function GetThemeBackgroundRegion(hTheme: HTHEME; hdc: HDC; iPartId, iStateId: Integer;
  const pRect: RECT; var pRegion: HRGN): HRESULT; stdcall;
{$EXTERNALSYM GetThemeBackgroundRegion}

//-------------------------------------------------------------------------
//----- HitTestThemeBackground, HitTestThemeBackgroundRegion flags ----

//  Theme background segment hit test flag (default). possible return values are:
//  HTCLIENT: hit test succeeded in the middle background segment
//  HTTOP, HTLEFT, HTTOPLEFT, etc:  // hit test succeeded in the the respective theme background segment.

const
  HTTB_BACKGROUNDSEG         = $0000;
  {$EXTERNALSYM HTTB_BACKGROUNDSEG}

//  Fixed border hit test option.  possible return values are:
//  HTCLIENT: hit test succeeded in the middle background segment
//  HTBORDER: hit test succeeded in any other background segment

  HTTB_FIXEDBORDER           = $0002;  // Return code may be either HTCLIENT or HTBORDER.
  {$EXTERNALSYM HTTB_FIXEDBORDER}

//  Caption hit test option.  Possible return values are:
//  HTCAPTION: hit test succeeded in the top, top left, or top right background segments
//  HTNOWHERE or another return code, depending on absence or presence of accompanying flags, resp.

  HTTB_CAPTION               = $0004;
  {$EXTERNALSYM HTTB_CAPTION}

//  Resizing border hit test flags.  Possible return values are:
//  HTCLIENT: hit test succeeded in middle background segment
//  HTTOP, HTTOPLEFT, HTLEFT, HTRIGHT, etc:    hit test succeeded in the respective system resizing zone
//  HTBORDER: hit test failed in middle segment and resizing zones, but succeeded in a background border segment

  HTTB_RESIZINGBORDER_LEFT   = $0010; // Hit test left resizing border,
  {$EXTERNALSYM HTTB_RESIZINGBORDER_LEFT}
  HTTB_RESIZINGBORDER_TOP    = $0020; // Hit test top resizing border
  {$EXTERNALSYM HTTB_RESIZINGBORDER_TOP}
  HTTB_RESIZINGBORDER_RIGHT  = $0040; // Hit test right resizing border
  {$EXTERNALSYM HTTB_RESIZINGBORDER_RIGHT}
  HTTB_RESIZINGBORDER_BOTTOM = $0080; // Hit test bottom resizing border
  {$EXTERNALSYM HTTB_RESIZINGBORDER_BOTTOM}

  HTTB_RESIZINGBORDER        = (HTTB_RESIZINGBORDER_LEFT or HTTB_RESIZINGBORDER_TOP or
                                HTTB_RESIZINGBORDER_RIGHT or HTTB_RESIZINGBORDER_BOTTOM);
  {$EXTERNALSYM HTTB_RESIZINGBORDER}

// Resizing border is specified as a template, not just window edges.
// This option is mutually exclusive with HTTB_SYSTEMSIZINGWIDTH; HTTB_SIZINGTEMPLATE takes precedence

  HTTB_SIZINGTEMPLATE        = $0100;
  {$EXTERNALSYM HTTB_SIZINGTEMPLATE}

// Use system resizing border width rather than theme content margins.
// This option is mutually exclusive with HTTB_SIZINGTEMPLATE, which takes precedence.

  HTTB_SYSTEMSIZINGMARGINS   = $0200;
  {$EXTERNALSYM HTTB_SYSTEMSIZINGMARGINS}

//-------------------------------------------------------------------------
//  HitTestThemeBackground()
//                      - returns a HitTestCode (a subset of the values
//                        returned by WM_NCHITTEST) for the point "ptTest"
//                        within the theme-specified background
//                        (bound by pRect).  "pRect" and "ptTest" should
//                        both be in the same coordinate system
//                        (client, screen, etc).
//
//      hTheme          - theme data handle
//      hdc             - HDC to draw into
//      iPartId         - part number to test against
//      iStateId        - state number (of the part)
//      pRect           - the RECT used to draw the part
//      hrgn            - optional region to use; must be in same coordinates as
//                      -    pRect and pTest.
//      ptTest          - the hit point to be tested
//      dwOptions       - HTTB_xxx constants
//      pwHitTestCode   - receives the returned hit test code - one of:
//
//                        HTNOWHERE, HTLEFT, HTTOPLEFT, HTBOTTOMLEFT,
//                        HTRIGHT, HTTOPRIGHT, HTBOTTOMRIGHT,
//                        HTTOP, HTBOTTOM, HTCLIENT
//-------------------------------------------------------------------------

function HitTestThemeBackground(hTheme: HTHEME; hdc: HDC; iPartId, iStateId: Integer;
  dwOptions: DWORD; const pRect: RECT; hrgn: HRGN; ptTest: POINT; var pwHitTestCode: WORD): HRESULT; stdcall;
{$EXTERNALSYM HitTestThemeBackground}

//------------------------------------------------------------------------
//  DrawThemeEdge()     - Similar to the DrawEdge() API, but uses part colors
//                        and is high-DPI aware
//  hTheme              - theme data handle
//  hdc                 - HDC to draw into
//  iPartId             - part number to draw
//  iStateId            - state number of part
//  pDestRect           - the RECT used to draw the line(s)
//  uEdge               - Same as DrawEdge() API
//  uFlags              - Same as DrawEdge() API
//  pContentRect        - Receives the interior rect if (uFlags & BF_ADJUST)
//------------------------------------------------------------------------

function DrawThemeEdge(hTheme: HTHEME; hdc: HDC; iPartId, iStateId: Integer;
  const pDestRect: RECT; uEdge, uFlags: UINT; pContentRect: PRECT): HRESULT; stdcall;
{$EXTERNALSYM DrawThemeEdge}

//------------------------------------------------------------------------
//  DrawThemeIcon()     - draws an image within an imagelist based on
//                        a (possible) theme-defined effect.
//
//  hTheme              - theme data handle
//  hdc                 - HDC to draw into
//  iPartId             - part number to draw
//  iStateId            - state number of part
//  pRect               - the RECT to draw the image within
//  himl                - handle to IMAGELIST
//  iImageIndex         - index into IMAGELIST (which icon to draw)
//------------------------------------------------------------------------

function DrawThemeIcon(hTheme: HTHEME; hdc: HDC; iPartId, iStateId: Integer;
  const pRect: RECT; himl: HIMAGELIST; iImageIndex: Integer): HRESULT; stdcall;
{$EXTERNALSYM DrawThemeIcon}

//---------------------------------------------------------------------------
//  IsThemePartDefined() - returns TRUE if the theme has defined parameters
//                         for the specified "iPartId" and "iStateId".
//
//  hTheme              - theme data handle
//  iPartId             - part number to find definition for
//  iStateId            - state number of part
//---------------------------------------------------------------------------

function IsThemePartDefined(hTheme: HTHEME; iPartId, iStateId: Integer): BOOL; stdcall;
{$EXTERNALSYM IsThemePartDefined}

//---------------------------------------------------------------------------
//  IsThemeBackgroundPartiallyTransparent()
//                      - returns TRUE if the theme specified background for
//                        the part/state has transparent pieces or
//                        alpha-blended pieces.
//
//  hTheme              - theme data handle
//  iPartId             - part number
//  iStateId            - state number of part
//---------------------------------------------------------------------------

function IsThemeBackgroundPartiallyTransparent(hTheme: HTHEME; iPartId, iStateId: Integer): BOOL; stdcall;
{$EXTERNALSYM IsThemeBackgroundPartiallyTransparent}

//---------------------------------------------------------------------------
//    lower-level theme information services
//---------------------------------------------------------------------------
// The following methods are getter routines for each of the Theme Data types.
// Controls/Windows are defined in drawable "parts" by their author: a
// parent part and 0 or more child parts.  Each of the parts can be
// described in "states" (ex: disabled, hot, pressed).
//---------------------------------------------------------------------------
// Each of the below methods takes a "iPartId" param to specify the
// part and a "iStateId" to specify the state of the part.
// "iStateId=0" refers to the root part.  "iPartId" = "0" refers to
// the root class.
//-----------------------------------------------------------------------
// Each method also take a "iPropId" param because multiple instances of
// the same primitive type can be defined in the theme schema.
//-----------------------------------------------------------------------


//-----------------------------------------------------------------------
//  GetThemeColor()     - Get the value for the specified COLOR property
//
//  hTheme              - theme data handle
//  iPartId             - part number
//  iStateId            - state number of part
//  iPropId             - the property number to get the value for
//  pColor              - receives the value of the property
//-----------------------------------------------------------------------

function GetThemeColor(hTheme: HTHEME; iPartId, iStateId, iPropId: Integer;
  var pColor: COLORREF): HRESULT; stdcall;
{$EXTERNALSYM GetThemeColor}

//-----------------------------------------------------------------------
//  GetThemeMetric()    - Get the value for the specified metric/size
//                        property
//
//  hTheme              - theme data handle
//  hdc                 - (optional) hdc to be drawn into (DPI scaling)
//  iPartId             - part number
//  iStateId            - state number of part
//  iPropId             - the property number to get the value for
//  piVal               - receives the value of the property
//-----------------------------------------------------------------------

function GetThemeMetric(hTheme: HTHEME; hdc: HDC; iPartId, iStateId, iPropId: Integer;
  var piVal: Integer): HRESULT; stdcall;
{$EXTERNALSYM GetThemeMetric}

//-----------------------------------------------------------------------
//  GetThemeString()    - Get the value for the specified string property
//
//  hTheme              - theme data handle
//  iPartId             - part number
//  iStateId            - state number of part
//  iPropId             - the property number to get the value for
//  pszBuff             - receives the string property value
//  cchMaxBuffChars     - max. number of chars allowed in pszBuff
//-----------------------------------------------------------------------

function GetThemeString(hTheme: HTHEME; iPartId, iStateId, iPropId: Integer;
  pszBuff: LPWSTR; cchMaxBuffChars: Integer): HRESULT; stdcall;
{$EXTERNALSYM GetThemeString}

//-----------------------------------------------------------------------
//  GetThemeBool()      - Get the value for the specified BOOL property
//
//  hTheme              - theme data handle
//  iPartId             - part number
//  iStateId            - state number of part
//  iPropId             - the property number to get the value for
//  pfVal               - receives the value of the property
//-----------------------------------------------------------------------

function GetThemeBool(hTheme: HTHEME; iPartId, iStateId, iPropId: Integer;
  var pfVal: BOOL): HRESULT; stdcall;
{$EXTERNALSYM GetThemeBool}

//-----------------------------------------------------------------------
//  GetThemeInt()       - Get the value for the specified int property
//
//  hTheme              - theme data handle
//  iPartId             - part number
//  iStateId            - state number of part
//  iPropId             - the property number to get the value for
//  piVal               - receives the value of the property
//-----------------------------------------------------------------------

function GetThemeInt(hTheme: HTHEME; iPartId, iStateId, iPropId: Integer;
  var piVal: Integer): HRESULT; stdcall;
{$EXTERNALSYM GetThemeInt}

//-----------------------------------------------------------------------
//  GetThemeEnumValue() - Get the value for the specified ENUM property
//
//  hTheme              - theme data handle
//  iPartId             - part number
//  iStateId            - state number of part
//  iPropId             - the property number to get the value for
//  piVal               - receives the value of the enum (cast to int*)
//-----------------------------------------------------------------------

function GetThemeEnumValue(hTheme: HTHEME; iPartId, iStateId, iPropId: Integer;
  var piVal: Integer): HRESULT; stdcall;
{$EXTERNALSYM GetThemeEnumValue}

//-----------------------------------------------------------------------
//  GetThemePosition()  - Get the value for the specified position
//                        property
//
//  hTheme              - theme data handle
//  iPartId             - part number
//  iStateId            - state number of part
//  iPropId             - the property number to get the value for
//  pPoint              - receives the value of the position property
//-----------------------------------------------------------------------

function GetThemePosition(hTheme: HTHEME; iPartId, iStateId, iPropId: Integer;
  var pPoint: POINT): HRESULT; stdcall;
{$EXTERNALSYM GetThemePosition}

//-----------------------------------------------------------------------
//  GetThemeFont()      - Get the value for the specified font property
//
//  hTheme              - theme data handle
//  hdc                 - (optional) hdc to be drawn to (DPI scaling)
//  iPartId             - part number
//  iStateId            - state number of part
//  iPropId             - the property number to get the value for
//  pFont               - receives the value of the LOGFONT property
//                        (scaled for the current logical screen dpi)
//-----------------------------------------------------------------------

function GetThemeFont(hTheme: HTHEME; hdc: HDC; iPartId, iStateId, iPropId: Integer;
  var pFont: LOGFONT): HRESULT; stdcall;
{$EXTERNALSYM GetThemeFont}

//-----------------------------------------------------------------------
//  GetThemeRect()      - Get the value for the specified RECT property
//
//  hTheme              - theme data handle
//  iPartId             - part number
//  iStateId            - state number of part
//  iPropId             - the property number to get the value for
//  pRect               - receives the value of the RECT property
//-----------------------------------------------------------------------

function GetThemeRect(hTheme: HTHEME; iPartId, iStateId, iPropId: Integer;
  var pRect: RECT): HRESULT; stdcall;
{$EXTERNALSYM GetThemeRect}

//-----------------------------------------------------------------------

type
  _MARGINS = record
    cxLeftWidth: Integer;      // width of left border that retains its size
    cxRightWidth: Integer;     // width of right border that retains its size
    cyTopHeight: Integer;      // height of top border that retains its size
    cyBottomHeight: Integer;   // height of bottom border that retains its size
  end;
  {$EXTERNALSYM _MARGINS}
  MARGINS = _MARGINS;
  {$EXTERNALSYM MARGINS}
  PMARGINS = ^MARGINS;
  {$EXTERNALSYM PMARGINS}
  TMargins = MARGINS;

//-----------------------------------------------------------------------
//  GetThemeMargins()   - Get the value for the specified MARGINS property
//
//      hTheme          - theme data handle
//      hdc             - (optional) hdc to be used for drawing
//      iPartId         - part number
//      iStateId        - state number of part
//      iPropId         - the property number to get the value for
//      prc             - RECT for area to be drawn into
//      pMargins        - receives the value of the MARGINS property
//-----------------------------------------------------------------------

function GetThemeMargins(hTheme: HTHEME; hdc: HDC; iPartId, iStateId, iPropId: Integer;
  prc: PRECT; var pMargins: MARGINS): HRESULT; stdcall;
{$EXTERNALSYM GetThemeMargins}

//-----------------------------------------------------------------------

const
  MAX_INTLIST_COUNT = 10;
  {$EXTERNALSYM MAX_INTLIST_COUNT}

type
  _INTLIST = record
    iValueCount: Integer;      // number of values in iValues
    iValues: array [0..MAX_INTLIST_COUNT - 1] of Integer;
  end;
  {$EXTERNALSYM _INTLIST}
  INTLIST = _INTLIST;
  {$EXTERNALSYM INTLIST}
  PINTLIST = ^INTLIST;
  {$EXTERNALSYM PINTLIST}
  TIntList = INTLIST;

//-----------------------------------------------------------------------
//  GetThemeIntList()   - Get the value for the specified INTLIST struct
//
//      hTheme          - theme data handle
//      iPartId         - part number
//      iStateId        - state number of part
//      iPropId         - the property number to get the value for
//      pIntList        - receives the value of the INTLIST property
//-----------------------------------------------------------------------

function GetThemeIntList(hTheme: HTHEME; iPartId, iStateId, iPropId: Integer;
  var pIntList: INTLIST): HRESULT; stdcall;
{$EXTERNALSYM GetThemeIntList}

//-----------------------------------------------------------------------

type
  PROPERTYORIGIN = (
    PO_STATE,           // property was found in the state section
    PO_PART,            // property was found in the part section
    PO_CLASS,           // property was found in the class section
    PO_GLOBAL,          // property was found in [globals] section
    PO_NOTFOUND);       // property was not found
  {$EXTERNALSYM PROPERTYORIGIN}
  TPropertyOrigin = PROPERTYORIGIN;

//-----------------------------------------------------------------------
//  GetThemePropertyOrigin()
//                      - searches for the specified theme property
//                        and sets "pOrigin" to indicate where it was
//                        found (or not found)
//
//  hTheme              - theme data handle
//  iPartId             - part number
//  iStateId            - state number of part
//  iPropId             - the property number to search for
//  pOrigin             - receives the value of the property origin
//-----------------------------------------------------------------------

function GetThemePropertyOrigin(hTheme: HTHEME; iPartId, iStateId, iPropId: Integer;
  var pOrigin: PROPERTYORIGIN): HRESULT; stdcall;
{$EXTERNALSYM GetThemePropertyOrigin}

//---------------------------------------------------------------------------
//  SetWindowTheme()
//                      - redirects an existing Window to use a different
//                        section of the current theme information than its
//                        class normally asks for.
//
//  hwnd                - the handle of the window (cannot be NULL)
//
//  pszSubAppName       - app (group) name to use in place of the calling
//                        app's name.  If NULL, the actual calling app
//                        name will be used.
//
//  pszSubIdList        - semicolon separated list of class Id names to
//                        use in place of actual list passed by the
//                        window's class.  if NULL, the id list from the
//                        calling class is used.
//---------------------------------------------------------------------------
// The Theme Manager will remember the "pszSubAppName" and the
// "pszSubIdList" associations thru the lifetime of the window (even
// if themes are subsequently changed).  The window is sent a
// "WM_THEMECHANGED" msg at the end of this call, so that the new
// theme can be found and applied.
//---------------------------------------------------------------------------
// When "pszSubAppName" or "pszSubIdList" are NULL, the Theme Manager
// removes the previously remember association.  To turn off theme-ing for
// the specified window, you can pass an empty string (L"") so it
// won't match any section entries.
//---------------------------------------------------------------------------

function SetWindowTheme(hwnd: HWND; pszSubAppName: LPCWSTR; pszSubIdList: LPCWSTR): HRESULT; stdcall;
{$EXTERNALSYM SetWindowTheme}

//---------------------------------------------------------------------------
//  GetThemeFilename()  - Get the value for the specified FILENAME property.
//
//  hTheme              - theme data handle
//  iPartId             - part number
//  iStateId            - state number of part
//  iPropId             - the property number to search for
//  pszThemeFileName    - output buffer to receive the filename
//  cchMaxBuffChars     - the size of the return buffer, in chars
//---------------------------------------------------------------------------

function GetThemeFilename(hTheme: HTHEME; iPartId, iStateId, iPropId: Integer;
  pszThemeFileName: LPWSTR; cchMaxBuffChars: Integer): HRESULT; stdcall;
{$EXTERNALSYM GetThemeFilename}

//---------------------------------------------------------------------------
//  GetThemeSysColor()  - Get the value of the specified System color.
//
//  hTheme              - the theme data handle.  if non-NULL, will return
//                        color from [SysMetrics] section of theme.
//                        if NULL, will return the global system color.
//
//  iColorId            - the system color index defined in winuser.h
//---------------------------------------------------------------------------

function GetThemeSysColor(hTheme: HTHEME; iColorId: Integer): COLORREF; stdcall;
{$EXTERNALSYM GetThemeSysColor}

//---------------------------------------------------------------------------
//  GetThemeSysColorBrush()
//                      - Get the brush for the specified System color.
//
//  hTheme              - the theme data handle.  if non-NULL, will return
//                        brush matching color from [SysMetrics] section of
//                        theme.  if NULL, will return the brush matching
//                        global system color.
//
//  iColorId            - the system color index defined in winuser.h
//---------------------------------------------------------------------------

function GetThemeSysColorBrush(hTheme: HTHEME; iColorId: Integer): HBRUSH; stdcall;
{$EXTERNALSYM GetThemeSysColorBrush}

//---------------------------------------------------------------------------
//  GetThemeSysBool()   - Get the boolean value of specified System metric.
//
//  hTheme              - the theme data handle.  if non-NULL, will return
//                        BOOL from [SysMetrics] section of theme.
//                        if NULL, will return the specified system boolean.
//
//  iBoolId             - the TMT_XXX BOOL number (first BOOL
//                        is TMT_FLATMENUS)
//---------------------------------------------------------------------------

function GetThemeSysBool(hTheme: HTHEME; iBoolId: Integer): BOOL; stdcall;
{$EXTERNALSYM GetThemeSysBool}

//---------------------------------------------------------------------------
//  GetThemeSysSize()   - Get the value of the specified System size metric.
//                        (scaled for the current logical screen dpi)
//
//  hTheme              - the theme data handle.  if non-NULL, will return
//                        size from [SysMetrics] section of theme.
//                        if NULL, will return the global system metric.
//
//  iSizeId             - the following values are supported when
//                        hTheme is non-NULL:
//
//                          SM_CXBORDER   (border width)
//                          SM_CXVSCROLL  (scrollbar width)
//                          SM_CYHSCROLL  (scrollbar height)
//                          SM_CXSIZE     (caption width)
//                          SM_CYSIZE     (caption height)
//                          SM_CXSMSIZE   (small caption width)
//                          SM_CYSMSIZE   (small caption height)
//                          SM_CXMENUSIZE (menubar width)
//                          SM_CYMENUSIZE (menubar height)
//
//                        when hTheme is NULL, iSizeId is passed directly
//                        to the GetSystemMetrics() function
//---------------------------------------------------------------------------

function GetThemeSysSize(hTheme: HTHEME; iSizeId: Integer): Integer; stdcall;
{$EXTERNALSYM GetThemeSysSize}

//---------------------------------------------------------------------------
//  GetThemeSysFont()   - Get the LOGFONT for the specified System font.
//
//  hTheme              - the theme data handle.  if non-NULL, will return
//                        font from [SysMetrics] section of theme.
//                        if NULL, will return the specified system font.
//
//  iFontId             - the TMT_XXX font number (first font
//                        is TMT_CAPTIONFONT)
//
//  plf                 - ptr to LOGFONT to receive the font value.
//                        (scaled for the current logical screen dpi)
//---------------------------------------------------------------------------

function GetThemeSysFont(hTheme: HTHEME; iFontId: Integer; var plf: LOGFONT): HRESULT; stdcall;
{$EXTERNALSYM GetThemeSysFont}

//---------------------------------------------------------------------------
//  GetThemeSysString() - Get the value of specified System string metric.
//
//  hTheme              - the theme data handle (required)
//
//  iStringId           - must be one of the following values:
//
//                          TMT_CSSNAME
//                          TMT_XMLNAME
//
//  pszStringBuff       - the buffer to receive the string value
//
//  cchMaxStringChars   - max. number of chars that pszStringBuff can hold
//---------------------------------------------------------------------------

function GetThemeSysString(hTheme: HTHEME; iStringId: Integer;
  pszStringBuff: LPWSTR; cchMaxStringChars: Integer): HRESULT; stdcall;
{$EXTERNALSYM GetThemeSysString}

//---------------------------------------------------------------------------
//  GetThemeSysInt() - Get the value of specified System int.
//
//  hTheme              - the theme data handle (required)
//
//  iIntId              - must be one of the following values:
//
//                          TMT_DPIX
//                          TMT_DPIY
//                          TMT_MINCOLORDEPTH
//
//  piValue             - ptr to int to receive value
//---------------------------------------------------------------------------

function GetThemeSysInt(hTheme: HTHEME; iIntId: Integer; var piValue: Integer): HRESULT; stdcall;
{$EXTERNALSYM GetThemeSysInt}

//---------------------------------------------------------------------------
//  IsThemeActive()     - can be used to test if a system theme is active
//                        for the current user session.
//
//                        use the API "IsAppThemed()" to test if a theme is
//                        active for the calling process.
//---------------------------------------------------------------------------

function IsThemeActive: BOOL; stdcall;
{$EXTERNALSYM IsThemeActive}

//---------------------------------------------------------------------------
//  IsAppThemed()       - returns TRUE if a theme is active and available to
//                        the current process
//---------------------------------------------------------------------------

function IsAppThemed: BOOL; stdcall;
{$EXTERNALSYM IsAppThemed}

//---------------------------------------------------------------------------
//  GetWindowTheme()    - if window is themed, returns its most recent
//                        HTHEME from OpenThemeData() - otherwise, returns
//                        NULL.
//
//      hwnd            - the window to get the HTHEME of
//---------------------------------------------------------------------------

function GetWindowTheme(hwnd: HWND): HTHEME; stdcall;
{$EXTERNALSYM GetWindowTheme}

//---------------------------------------------------------------------------
//  EnableThemeDialogTexture()
//
//  - Enables/disables dialog background theme.  This method can be used to
//    tailor dialog compatibility with child windows and controls that
//    may or may not coordinate the rendering of their client area backgrounds
//    with that of their parent dialog in a manner that supports seamless
//    background texturing.
//
//      hdlg         - the window handle of the target dialog
//      dwFlags      - ETDT_ENABLE to enable the theme-defined dialog background texturing,
//                     ETDT_DISABLE to disable background texturing,
//                     ETDT_ENABLETAB to enable the theme-defined background
//                          texturing using the Tab texture
//---------------------------------------------------------------------------

const
  ETDT_DISABLE       = $00000001;
  {$EXTERNALSYM ETDT_DISABLE}
  ETDT_ENABLE        = $00000002;
  {$EXTERNALSYM ETDT_ENABLE}
  ETDT_USETABTEXTURE = $00000004;
  {$EXTERNALSYM ETDT_USETABTEXTURE}
  ETDT_ENABLETAB     = (ETDT_ENABLE or ETDT_USETABTEXTURE);
  {$EXTERNALSYM ETDT_ENABLETAB}

function EnableThemeDialogTexture(hwnd: HWND; dwFlags: DWORD): HRESULT; stdcall;
{$EXTERNALSYM EnableThemeDialogTexture}

//---------------------------------------------------------------------------
//  IsThemeDialogTextureEnabled()
//
//  - Reports whether the dialog supports background texturing.
//
//      hdlg         - the window handle of the target dialog
//---------------------------------------------------------------------------

function IsThemeDialogTextureEnabled(hwnd: HWND): BOOL; stdcall;
{$EXTERNALSYM IsThemeDialogTextureEnabled}

//---------------------------------------------------------------------------
//---- flags to control theming within an app ----

const
  STAP_ALLOW_NONCLIENT   = (1 shl 0);
  {$EXTERNALSYM STAP_ALLOW_NONCLIENT}
  STAP_ALLOW_CONTROLS    = (1 shl 1);
  {$EXTERNALSYM STAP_ALLOW_CONTROLS}
  STAP_ALLOW_WEBCONTENT  = (1 shl 2);
  {$EXTERNALSYM STAP_ALLOW_WEBCONTENT}

//---------------------------------------------------------------------------
//  GetThemeAppProperties()
//                      - returns the app property flags that control theming
//---------------------------------------------------------------------------

function GetThemeAppProperties: DWORD; stdcall;
{$EXTERNALSYM GetThemeAppProperties}

//---------------------------------------------------------------------------
//  SetThemeAppProperties()
//                      - sets the flags that control theming within the app
//
//      dwFlags         - the flag values to be set
//---------------------------------------------------------------------------

procedure SetThemeAppProperties(dwFlags: DWORD); stdcall;
{$EXTERNALSYM SetThemeAppProperties}

//---------------------------------------------------------------------------
//  GetCurrentThemeName()
//                      - Get the name of the current theme in-use.
//                        Optionally, return the ColorScheme name and the
//                        Size name of the theme.
//
//  pszThemeFileName    - receives the theme path & filename
//  cchMaxNameChars     - max chars allowed in pszNameBuff
//
//  pszColorBuff        - (optional) receives the canonical color scheme name
//                        (not the display name)
//  cchMaxColorChars    - max chars allowed in pszColorBuff
//
//  pszSizeBuff         - (optional) receives the canonical size name
//                        (not the display name)
//  cchMaxSizeChars     - max chars allowed in pszSizeBuff
//---------------------------------------------------------------------------

function GetCurrentThemeName(pszThemeFileName: LPWSTR; cchMaxNameChars: Integer; pszColorBuff: LPWSTR;
  cchMaxColorChars: Integer; pszSizeBuff: LPWSTR; cchMaxSizeChars: Integer): HRESULT; stdcall;
{$EXTERNALSYM GetCurrentThemeName}

//---------------------------------------------------------------------------
//  GetThemeDocumentationProperty()
//                      - Get the value for the specified property name from
//                        the [documentation] section of the themes.ini file
//                        for the specified theme.  If the property has been
//                        localized in the theme files string table, the
//                        localized version of the property value is returned.
//
//  pszThemeFileName    - filename of the theme file to query
//  pszPropertyName     - name of the string property to retreive a value for
//  pszValueBuff        - receives the property string value
//  cchMaxValChars      - max chars allowed in pszValueBuff
//---------------------------------------------------------------------------

const
  SZ_THDOCPROP_DISPLAYNAME               = WideString('DisplayName');
  {$EXTERNALSYM SZ_THDOCPROP_DISPLAYNAME}
  SZ_THDOCPROP_CANONICALNAME             = WideString('ThemeName');
  {$EXTERNALSYM SZ_THDOCPROP_CANONICALNAME}
  SZ_THDOCPROP_TOOLTIP                   = WideString('ToolTip');
  {$EXTERNALSYM SZ_THDOCPROP_TOOLTIP}
  SZ_THDOCPROP_AUTHOR                    = WideString('author');
  {$EXTERNALSYM SZ_THDOCPROP_AUTHOR}

function GetThemeDocumentationProperty(pszThemeName, pszPropertyName: LPCWSTR;
  pszValueBuff: LPWSTR; cchMaxValChars: Integer): HRESULT; stdcall;
{$EXTERNALSYM GetThemeDocumentationProperty}

//---------------------------------------------------------------------------
//  Theme API Error Handling
//
//      All functions in the Theme API not returning an HRESULT (THEMEAPI_)
//      use the WIN32 function "SetLastError()" to record any call failures.
//
//      To retreive the error code of the last failure on the
//      current thread for these type of API's, use the WIN32 function
//      "GetLastError()".
//
//      All Theme API error codes (HRESULT's and GetLastError() values)
//      should be normal win32 errors which can be formatted into
//      strings using the Win32 API FormatMessage().
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
// DrawThemeParentBackground()
//                      - used by partially-transparent or alpha-blended
//                        child controls to draw the part of their parent
//                        that they appear in front of.
//
//  hwnd                - handle of the child control

//  hdc                 - hdc of the child control

//  prc                 - (optional) rect that defines the area to be
//                        drawn (CHILD coordinates)
//---------------------------------------------------------------------------

function DrawThemeParentBackground(hwnd: HWND; hdc: HDC; prc: PRECT): HRESULT; stdcall;
{$EXTERNALSYM DrawThemeParentBackground}

//---------------------------------------------------------------------------
//  EnableTheming()     - enables or disables themeing for the current user
//                        in the current and future sessions.
//
//  fEnable             - if FALSE, disable theming & turn themes off.
//                      - if TRUE, enable themeing and, if user previously
//                        had a theme active, make it active now.
//---------------------------------------------------------------------------

function EnableTheming(fEnable: BOOL): HRESULT; stdcall;
{$EXTERNALSYM EnableTheming}

//------------------------------------------------------------------------
//---- bits used in dwFlags of DTBGOPTS ----

const
  DTBG_CLIPRECT       = $00000001;   // rcClip has been specified
  {$EXTERNALSYM DTBG_CLIPRECT}
  DTBG_DRAWSOLID      = $00000002;   // draw transparent/alpha images as solid
  {$EXTERNALSYM DTBG_DRAWSOLID}
  DTBG_OMITBORDER     = $00000004;   // don't draw border of part
  {$EXTERNALSYM DTBG_OMITBORDER}
  DTBG_OMITCONTENT    = $00000008;   // don't draw content area of part
  {$EXTERNALSYM DTBG_OMITCONTENT}

  DTBG_COMPUTINGREGION = $00000010;   // TRUE if calling to compute region
  {$EXTERNALSYM DTBG_COMPUTINGREGION}

  DTBG_MIRRORDC        = $00000020;       // assume the hdc is mirrorred and
                                          // flip images as appropriate (currently
                                          // only supported for bgtype=imagefile)
  {$EXTERNALSYM DTBG_MIRRORDC}

//------------------------------------------------------------------------

type
  _DTBGOPTS = record
    dwSize: DWORD;           // size of the struct
    dwFlags: DWORD;          // which options have been specified
    rcClip: RECT;            // clipping rectangle
  end;
  {$EXTERNALSYM _DTBGOPTS}
  DTBGOPTS = _DTBGOPTS;
  {$EXTERNALSYM DTBGOPTS}
  PDTBGOPTS = ^DTBGOPTS;
  TDtbgOpts = DTBGOPTS;

//------------------------------------------------------------------------
//  DrawThemeBackgroundEx()
//                      - draws the theme-specified border and fill for
//                        the "iPartId" and "iStateId".  This could be
//                        based on a bitmap file, a border and fill, or
//                        other image description.  NOTE: This will be
//                        merged back into DrawThemeBackground() after
//                        BETA 2.
//
//  hTheme              - theme data handle
//  hdc                 - HDC to draw into
//  iPartId             - part number to draw
//  iStateId            - state number (of the part) to draw
//  pRect               - defines the size/location of the part
//  pOptions            - ptr to optional params
//------------------------------------------------------------------------

function DrawThemeBackgroundEx(hTheme: HTHEME; hdc: HDC; iPartId, iStateId: Integer; pRect: LPRECT; pOptions: PDTBGOPTS): HRESULT; stdcall;
{$EXTERNALSYM DrawThemeBackgroundEx}


implementation

const
  themelib = 'uxtheme.dll';


{$IFDEF DYNAMIC_LINK}
var
  _OpenThemeData: Pointer;

function OpenThemeData;
begin
  GetProcedureAddress(_OpenThemeData, themelib, 'OpenThemeData');
  asm
    mov esp, ebp
    pop ebp
    jmp [_OpenThemeData]
  end;
end;
{$ELSE}
function OpenThemeData; external themelib name 'OpenThemeData';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _CloseThemeData: Pointer;

function CloseThemeData;
begin
  GetProcedureAddress(_CloseThemeData, themelib, 'CloseThemeData');
  asm
    mov esp, ebp
    pop ebp
    jmp [_CloseThemeData]
  end;
end;
{$ELSE}
function CloseThemeData; external themelib name 'CloseThemeData';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _DrawThemeBackground: Pointer;

function DrawThemeBackground;
begin
  GetProcedureAddress(_DrawThemeBackground, themelib, 'DrawThemeBackground');
  asm
    mov esp, ebp
    pop ebp
    jmp [_DrawThemeBackground]
  end;
end;
{$ELSE}
function DrawThemeBackground; external themelib name 'DrawThemeBackground';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _DrawThemeText: Pointer;

function DrawThemeText;
begin
  GetProcedureAddress(_DrawThemeText, themelib, 'DrawThemeText');
  asm
    mov esp, ebp
    pop ebp
    jmp [_DrawThemeText]
  end;
end;
{$ELSE}
function DrawThemeText; external themelib name 'DrawThemeText';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _GetThemeBackgroundContentRect: Pointer;

function GetThemeBackgroundContentRect;
begin
  GetProcedureAddress(_GetThemeBackgroundContentRect, themelib, 'GetThemeBackgroundContentRect');
  asm
    mov esp, ebp
    pop ebp
    jmp [_GetThemeBackgroundContentRect]
  end;
end;
{$ELSE}
function GetThemeBackgroundContentRect; external themelib name 'GetThemeBackgroundContentRect';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _GetThemeBackgroundExtent: Pointer;

function GetThemeBackgroundExtent;
begin
  GetProcedureAddress(_GetThemeBackgroundExtent, themelib, 'GetThemeBackgroundContentRect');
  asm
    mov esp, ebp
    pop ebp
    jmp [_GetThemeBackgroundExtent]
  end;
end;
{$ELSE}
function GetThemeBackgroundExtent; external themelib name 'GetThemeBackgroundContentRect';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _GetThemePartSize: Pointer;

function GetThemePartSize;
begin
  GetProcedureAddress(_GetThemePartSize, themelib, 'GetThemePartSize');
  asm
    mov esp, ebp
    pop ebp
    jmp [_GetThemePartSize]
  end;
end;
{$ELSE}
function GetThemePartSize; external themelib name 'GetThemePartSize';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _GetThemeTextExtent: Pointer;

function GetThemeTextExtent;
begin
  GetProcedureAddress(_GetThemeTextExtent, themelib, 'GetThemeTextExtent');
  asm
    mov esp, ebp
    pop ebp
    jmp [_GetThemeTextExtent]
  end;
end;
{$ELSE}
function GetThemeTextExtent; external themelib name 'GetThemeTextExtent';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _GetThemeTextMetrics: Pointer;

function GetThemeTextMetrics;
begin
  GetProcedureAddress(_GetThemeTextMetrics, themelib, 'GetThemeTextMetrics');
  asm
    mov esp, ebp
    pop ebp
    jmp [_GetThemeTextMetrics]
  end;
end;
{$ELSE}
function GetThemeTextMetrics; external themelib name 'GetThemeTextMetrics';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _GetThemeBackgroundRegion: Pointer;

function GetThemeBackgroundRegion;
begin
  GetProcedureAddress(_GetThemeBackgroundRegion, themelib, 'GetThemeBackgroundRegion');
  asm
    mov esp, ebp
    pop ebp
    jmp [_GetThemeBackgroundRegion]
  end;
end;
{$ELSE}
function GetThemeBackgroundRegion; external themelib name 'GetThemeBackgroundRegion';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _HitTestThemeBackground: Pointer;

function HitTestThemeBackground;
begin
  GetProcedureAddress(_HitTestThemeBackground, themelib, 'HitTestThemeBackground');
  asm
    mov esp, ebp
    pop ebp
    jmp [_HitTestThemeBackground]
  end;
end;
{$ELSE}
function HitTestThemeBackground; external themelib name 'HitTestThemeBackground';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _DrawThemeEdge: Pointer;

function DrawThemeEdge;
begin
  GetProcedureAddress(_DrawThemeEdge, themelib, 'DrawThemeEdge');
  asm
    mov esp, ebp
    pop ebp
    jmp [_DrawThemeEdge]
  end;
end;
{$ELSE}
function DrawThemeEdge; external themelib name 'DrawThemeEdge';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _DrawThemeIcon: Pointer;

function DrawThemeIcon;
begin
  GetProcedureAddress(_DrawThemeIcon, themelib, 'DrawThemeIcon');
  asm
    mov esp, ebp
    pop ebp
    jmp [_DrawThemeIcon]
  end;
end;
{$ELSE}
function DrawThemeIcon; external themelib name 'DrawThemeIcon';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _IsThemePartDefined: Pointer;

function IsThemePartDefined;
begin
  GetProcedureAddress(_IsThemePartDefined, themelib, 'IsThemePartDefined');
  asm
    mov esp, ebp
    pop ebp
    jmp [_IsThemePartDefined]
  end;
end;
{$ELSE}
function IsThemePartDefined; external themelib name 'IsThemePartDefined';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _IsThemeBackgroundPartialTrans: Pointer;

function IsThemeBackgroundPartiallyTransparent;
begin
  GetProcedureAddress(_IsThemeBackgroundPartialTrans, themelib, 'IsThemeBackgroundPartiallyTransparent');
  asm
    mov esp, ebp
    pop ebp
    jmp [_IsThemeBackgroundPartialTrans]
  end;
end;
{$ELSE}
function IsThemeBackgroundPartiallyTransparent; external themelib name 'IsThemeBackgroundPartiallyTransparent';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _GetThemeColor: Pointer;

function GetThemeColor;
begin
  GetProcedureAddress(_GetThemeColor, themelib, 'GetThemeColor');
  asm
    mov esp, ebp
    pop ebp
    jmp [_GetThemeColor]
  end;
end;
{$ELSE}
function GetThemeColor; external themelib name 'GetThemeColor';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _GetThemeMetric: Pointer;

function GetThemeMetric;
begin
  GetProcedureAddress(_GetThemeMetric, themelib, 'GetThemeMetric');
  asm
    mov esp, ebp
    pop ebp
    jmp [_GetThemeMetric]
  end;
end;
{$ELSE}
function GetThemeMetric; external themelib name 'GetThemeMetric';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _GetThemeString: Pointer;

function GetThemeString;
begin
  GetProcedureAddress(_GetThemeString, themelib, 'GetThemeString');
  asm
    mov esp, ebp
    pop ebp
    jmp [_GetThemeString]
  end;
end;
{$ELSE}
function GetThemeString; external themelib name 'GetThemeString';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _GetThemeBool: Pointer;

function GetThemeBool;
begin
  GetProcedureAddress(_GetThemeBool, themelib, 'GetThemeBool');
  asm
    mov esp, ebp
    pop ebp
    jmp [_GetThemeBool]
  end;
end;
{$ELSE}
function GetThemeBool; external themelib name 'GetThemeBool';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _GetThemeInt: Pointer;

function GetThemeInt;
begin
  GetProcedureAddress(_GetThemeInt, themelib, 'GetThemeInt');
  asm
    mov esp, ebp
    pop ebp
    jmp [_GetThemeInt]
  end;
end;
{$ELSE}
function GetThemeInt; external themelib name 'GetThemeInt';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _GetThemeEnumValue: Pointer;

function GetThemeEnumValue;
begin
  GetProcedureAddress(_GetThemeEnumValue, themelib, 'GetThemeEnumValue');
  asm
    mov esp, ebp
    pop ebp
    jmp [_GetThemeEnumValue]
  end;
end;
{$ELSE}
function GetThemeEnumValue; external themelib name 'GetThemeEnumValue';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _GetThemePosition: Pointer;

function GetThemePosition;
begin
  GetProcedureAddress(_GetThemePosition, themelib, 'GetThemePosition');
  asm
    mov esp, ebp
    pop ebp
    jmp [_GetThemePosition]
  end;
end;
{$ELSE}
function GetThemePosition; external themelib name 'GetThemePosition';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _GetThemeFont: Pointer;

function GetThemeFont;
begin
  GetProcedureAddress(_GetThemeFont, themelib, 'GetThemeFont');
  asm
    mov esp, ebp
    pop ebp
    jmp [_GetThemeFont]
  end;
end;
{$ELSE}
function GetThemeFont; external themelib name 'GetThemeFont';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _GetThemeRect: Pointer;

function GetThemeRect;
begin
  GetProcedureAddress(_GetThemeRect, themelib, 'GetThemeRect');
  asm
    mov esp, ebp
    pop ebp
    jmp [_GetThemeRect]
  end;
end;
{$ELSE}
function GetThemeRect; external themelib name 'GetThemeRect';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _GetThemeMargins: Pointer;

function GetThemeMargins;
begin
  GetProcedureAddress(_GetThemeMargins, themelib, 'GetThemeMargins');
  asm
    mov esp, ebp
    pop ebp
    jmp [_GetThemeMargins]
  end;
end;
{$ELSE}
function GetThemeMargins; external themelib name 'GetThemeMargins';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _GetThemeIntList: Pointer;

function GetThemeIntList;
begin
  GetProcedureAddress(_GetThemeIntList, themelib, 'GetThemeIntList');
  asm
    mov esp, ebp
    pop ebp
    jmp [_GetThemeIntList]
  end;
end;
{$ELSE}
function GetThemeIntList; external themelib name 'GetThemeIntList';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _GetThemePropertyOrigin: Pointer;

function GetThemePropertyOrigin;
begin
  GetProcedureAddress(_GetThemePropertyOrigin, themelib, 'GetThemePropertyOrigin');
  asm
    mov esp, ebp
    pop ebp
    jmp [_GetThemePropertyOrigin]
  end;
end;
{$ELSE}
function GetThemePropertyOrigin; external themelib name 'GetThemePropertyOrigin';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _SetWindowTheme: Pointer;

function SetWindowTheme;
begin
  GetProcedureAddress(_SetWindowTheme, themelib, 'SetWindowTheme');
  asm
    mov esp, ebp
    pop ebp
    jmp [_SetWindowTheme]
  end;
end;
{$ELSE}
function SetWindowTheme; external themelib name 'SetWindowTheme';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _GetThemeFilename: Pointer;

function GetThemeFilename;
begin
  GetProcedureAddress(_GetThemeFilename, themelib, 'GetThemeFilename');
  asm
    mov esp, ebp
    pop ebp
    jmp [_GetThemeFilename]
  end;
end;
{$ELSE}
function GetThemeFilename; external themelib name 'GetThemeFilename';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _GetThemeSysColor: Pointer;

function GetThemeSysColor;
begin
  GetProcedureAddress(_GetThemeSysColor, themelib, 'GetThemeSysColor');
  asm
    mov esp, ebp
    pop ebp
    jmp [_GetThemeSysColor]
  end;
end;
{$ELSE}
function GetThemeSysColor; external themelib name 'GetThemeSysColor';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _GetThemeSysColorBrush: Pointer;

function GetThemeSysColorBrush;
begin
  GetProcedureAddress(_GetThemeSysColorBrush, themelib, 'GetThemeSysColorBrush');
  asm
    mov esp, ebp
    pop ebp
    jmp [_GetThemeSysColorBrush]
  end;
end;
{$ELSE}
function GetThemeSysColorBrush; external themelib name 'GetThemeSysColorBrush';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _GetThemeSysBool: Pointer;

function GetThemeSysBool;
begin
  GetProcedureAddress(_GetThemeSysBool, themelib, 'GetThemeSysBool');
  asm
    mov esp, ebp
    pop ebp
    jmp [_GetThemeSysBool]
  end;
end;
{$ELSE}
function GetThemeSysBool; external themelib name 'GetThemeSysBool';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _GetThemeSysSize: Pointer;

function GetThemeSysSize;
begin
  GetProcedureAddress(_GetThemeSysSize, themelib, 'GetThemeSysSize');
  asm
    mov esp, ebp
    pop ebp
    jmp [_GetThemeSysSize]
  end;
end;
{$ELSE}
function GetThemeSysSize; external themelib name 'GetThemeSysSize';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _GetThemeSysFont: Pointer;

function GetThemeSysFont;
begin
  GetProcedureAddress(_GetThemeSysFont, themelib, 'GetThemeSysFont');
  asm
    mov esp, ebp
    pop ebp
    jmp [_GetThemeSysFont]
  end;
end;
{$ELSE}
function GetThemeSysFont; external themelib name 'GetThemeSysFont';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _GetThemeSysString: Pointer;

function GetThemeSysString;
begin
  GetProcedureAddress(_GetThemeSysString, themelib, 'GetThemeSysString');
  asm
    mov esp, ebp
    pop ebp
    jmp [_GetThemeSysString]
  end;
end;
{$ELSE}
function GetThemeSysString; external themelib name 'GetThemeSysString';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _GetThemeSysInt: Pointer;

function GetThemeSysInt;
begin
  GetProcedureAddress(_GetThemeSysInt, themelib, 'GetThemeSysInt');
  asm
    mov esp, ebp
    pop ebp
    jmp [_GetThemeSysInt]
  end;
end;
{$ELSE}
function GetThemeSysInt; external themelib name 'GetThemeSysInt';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _IsThemeActive: Pointer;

function IsThemeActive;
begin
  GetProcedureAddress(_IsThemeActive, themelib, 'IsThemeActive');
  asm
    mov esp, ebp
    pop ebp
    jmp [_IsThemeActive]
  end;
end;
{$ELSE}
function IsThemeActive; external themelib name 'IsThemeActive';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _IsAppThemed: Pointer;

function IsAppThemed;
begin
  GetProcedureAddress(_IsAppThemed, themelib, 'IsAppThemed');
  asm
    mov esp, ebp
    pop ebp
    jmp [_IsAppThemed]
  end;
end;
{$ELSE}
function IsAppThemed; external themelib name 'IsAppThemed';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _GetWindowTheme: Pointer;

function GetWindowTheme;
begin
  GetProcedureAddress(_GetWindowTheme, themelib, 'GetWindowTheme');
  asm
    mov esp, ebp
    pop ebp
    jmp [_GetWindowTheme]
  end;
end;
{$ELSE}
function GetWindowTheme; external themelib name 'GetWindowTheme';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _EnableThemeDialogTexture: Pointer;

function EnableThemeDialogTexture;
begin
  GetProcedureAddress(_EnableThemeDialogTexture, themelib, 'EnableThemeDialogTexture');
  asm
    mov esp, ebp
    pop ebp
    jmp [_EnableThemeDialogTexture]
  end;
end;
{$ELSE}
function EnableThemeDialogTexture; external themelib name 'EnableThemeDialogTexture';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _IsThemeDialogTextureEnabled: Pointer;

function IsThemeDialogTextureEnabled;
begin
  GetProcedureAddress(_IsThemeDialogTextureEnabled, themelib, 'IsThemeDialogTextureEnabled');
  asm
    mov esp, ebp
    pop ebp
    jmp [_IsThemeDialogTextureEnabled]
  end;
end;
{$ELSE}
function IsThemeDialogTextureEnabled; external themelib name 'IsThemeDialogTextureEnabled';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _GetThemeAppProperties: Pointer;

function GetThemeAppProperties;
begin
  GetProcedureAddress(_GetThemeAppProperties, themelib, 'GetThemeAppProperties');
  asm
    mov esp, ebp
    pop ebp
    jmp [_GetThemeAppProperties]
  end;
end;
{$ELSE}
function GetThemeAppProperties; external themelib name 'GetThemeAppProperties';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _SetThemeAppProperties: Pointer;

procedure SetThemeAppProperties;
begin
  GetProcedureAddress(_SetThemeAppProperties, themelib, 'SetThemeAppProperties');
  asm
    mov esp, ebp
    pop ebp
    jmp [_SetThemeAppProperties]
  end;
end;
{$ELSE}
procedure SetThemeAppProperties; external themelib name 'SetThemeAppProperties';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _GetCurrentThemeName: Pointer;

function GetCurrentThemeName;
begin
  GetProcedureAddress(_GetCurrentThemeName, themelib, 'GetCurrentThemeName');
  asm
    mov esp, ebp
    pop ebp
    jmp [_GetCurrentThemeName]
  end;
end;
{$ELSE}
function GetCurrentThemeName; external themelib name 'GetCurrentThemeName';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _GetThemeDocumentationProperty: Pointer;

function GetThemeDocumentationProperty;
begin
  GetProcedureAddress(_GetThemeDocumentationProperty, themelib, 'GetThemeDocumentationProperty');
  asm
    mov esp, ebp
    pop ebp
    jmp [_GetThemeDocumentationProperty]
  end;
end;
{$ELSE}
function GetThemeDocumentationProperty; external themelib name 'GetThemeDocumentationProperty';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _DrawThemeParentBackground: Pointer;

function DrawThemeParentBackground;
begin
  GetProcedureAddress(_DrawThemeParentBackground, themelib, 'DrawThemeParentBackground');
  asm
    mov esp, ebp
    pop ebp
    jmp [_DrawThemeParentBackground]
  end;
end;
{$ELSE}
function DrawThemeParentBackground; external themelib name 'DrawThemeParentBackground';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _EnableTheming: Pointer;

function EnableTheming;
begin
  GetProcedureAddress(_EnableTheming, themelib, 'EnableTheming');
  asm
    mov esp, ebp
    pop ebp
    jmp [_EnableTheming]
  end;
end;
{$ELSE}
function EnableTheming; external themelib name 'EnableTheming';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _DrawThemeBackgroundEx: Pointer;

function DrawThemeBackgroundEx;
begin
  GetProcedureAddress(_DrawThemeBackgroundEx, themelib, 'DrawThemeBackgroundEx');
  asm
    mov esp, ebp
    pop ebp
    jmp [_DrawThemeBackgroundEx]
  end;
end;
{$ELSE}
function DrawThemeBackgroundEx; external themelib name 'DrawThemeBackgroundEx';
{$ENDIF DYNAMIC_LINK}

end.
