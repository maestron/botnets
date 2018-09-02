{******************************************************************************}
{                                                       	               }
{ GUID Definitions for HTML Viewer object API interface Unit for Object Pascal }
{                                                       	               }
{ Portions created by Microsoft are Copyright (C) 1995-2001 Microsoft          }
{ Corporation. All Rights Reserved.                                            }
{ 								               }
{ The original file is: htmlguid.h, released November 2002. The original Pascal}
{ code is: HtmlGuid.pas, released March 2002. The initial developer of the     }
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

unit JwaHtmlGuid;

{$WEAKPACKAGEUNIT}

{$HPPEMIT ''}
{$HPPEMIT '#include "htmlguid.h"'}
{$HPPEMIT ''}

{$I WINDEFINES.INC}

interface

const
// GUID for HTML viewer is: {25336920-03F9-11cf-8FD0-00AA00686F13}
  CLSID_HTMLViewer: TGUID = (D1:$25336920; D2:$3f9; D3:$11cf; D4:($8f, $d0, $0, $aa, $0, $68, $6f, $13));
  {$EXTERNALSYM CLSID_HTMLViewer}

// GUID for BSCB proxy is: {25336922-03F9-11cf-8FD0-00AA00686F13}
  CLSID_HTMLBSCBProxy: TGUID = (D1:$25336922; D2:$3f9; D3:$11cf; D4:($8f, $d0, $0, $aa, $0, $68, $6f, $13));
  {$EXTERNALSYM CLSID_HTMLBSCBProxy}

// The GUID used to identify the TypeLib of the HTML Page
// {71BC8840-60BB-11cf-8B97-00AA00476DA6}
  GUID_PageTL: TGUID = (D1:$71bc8840; D2:$60bb; D3:$11cf; D4:($8b, $97, $0, $aa, $0, $47, $6d, $a6));
  {$EXTERNALSYM GUID_PageTL}

// The GUID used to identify the Primary dispinterface of the HTML Page
// {71BC8841-60BB-11cf-8B97-00AA00476DA6}
  IID_PageProps: TGUID = (D1:$71bc8841; D2:$60bb; D3:$11cf; D4:($8b, $97, $0, $aa, $0, $47, $6d, $a6));
  {$EXTERNALSYM IID_PageProps}

// The GUID used to identify the Event dispinterface of the HTML Page
// The page events are currently commented out but will be added later
// so I grabbed a guid for the events now.
// {71BC8842-60BB-11cf-8B97-00AA00476DA6}
  IID_PageEvents: TGUID = (D1:$71bc8842; D2:$60bb; D3:$11cf; D4:($8b, $97, $0, $aa, $0, $47, $6d, $a6));
  {$EXTERNALSYM IID_PageEvents}

// The GUID used to identify the coclass of the HTML Page
// {71BC8843-60BB-11cf-8B97-00AA00476DA6}
  CLSID_Page: TGUID = (D1:$71bc8843; D2:$60bb; D3:$11cf; D4:($8b, $97, $0, $aa, $0, $47, $6d, $a6));
  {$EXTERNALSYM CLSID_Page}

implementation

end.
