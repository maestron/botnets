{******************************************************************************}
{                                                       	               }
{ Fax MMC Extension Components API interface unit for Object Pascal            }
{                                                       	               }
{ Portions created by Microsoft are Copyright (C) 1995-2001 Microsoft          }
{ Corporation. All Rights Reserved.                                            }
{ 								               }
{ The original file is: faxmmc.h, released November 2001. The original Pascal  }
{ code is: FaxMmc.pas, released April 2002. The initial developer of the       }
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

unit JwaFaxMmc;

{$WEAKPACKAGEUNIT}

{$HPPEMIT ''}
{$HPPEMIT '#include "faxmmc.h"'}
{$HPPEMIT ''}

{$I WINDEFINES.INC}

interface

uses
  JwaWinType;

type
  OLESTR = WideString; // todo 

const
  FAXSRV_DEVICE_NODETYPE_GUID_STR = OLESTR('{3115A19A-6251-46ac-9425-14782858B8C9}');
  {$EXTERNALSYM FAXSRV_DEVICE_NODETYPE_GUID_STR}
  FAXSRV_DEVICE_NODETYPE_GUID: TGUID = '{3115A19A-6251-46ac-9425-14782858B8C9}';
  {$EXTERNALSYM FAXSRV_DEVICE_NODETYPE_GUID}

  FAXSRV_DEVICE_PROVIDER_NODETYPE_GUID_STR = OLESTR('{BD38E2AC-B926-4161-8640-0F6956EE2BA3}');
  {$EXTERNALSYM FAXSRV_DEVICE_PROVIDER_NODETYPE_GUID_STR}
  FAXSRV_DEVICE_PROVIDER_NODETYPE_GUID: TGUID = '{BD38E2AC-B926-4161-8640-0F6956EE2BA3}';
  {$EXTERNALSYM FAXSRV_DEVICE_PROVIDER_NODETYPE_GUID}

  FAXSRV_ROUTING_METHOD_NODETYPE_GUID_STR = OLESTR('{220D2CB0-85A9-4a43-B6E8-9D66B44F1AF5}');
  {$EXTERNALSYM FAXSRV_ROUTING_METHOD_NODETYPE_GUID_STR}
  FAXSRV_ROUTING_METHOD_NODETYPE_GUID: TGUID = '{220D2CB0-85A9-4a43-B6E8-9D66B44F1AF5}';
  {$EXTERNALSYM FAXSRV_ROUTING_METHOD_NODETYPE_GUID}

  FAXSRV_MAX_GUID_LEN          = SizeOf(FAXSRV_DEVICE_NODETYPE_GUID_STR) div SizeOf(WCHAR);
  {$EXTERNALSYM FAXSRV_MAX_GUID_LEN}
  FAXSRV_MAX_SERVER_NAME       = MAX_PATH;
  {$EXTERNALSYM FAXSRV_MAX_SERVER_NAME}
  FAXSRV_MAX_ROUTEEXT_NAME_LEN = MAX_PATH;
  {$EXTERNALSYM FAXSRV_MAX_ROUTEEXT_NAME_LEN}

  CF_MSFAXSRV_DEVICE_ID           = TEXT('FAXSRV_DeviceID');
  {$EXTERNALSYM CF_MSFAXSRV_DEVICE_ID}
  CF_MSFAXSRV_FSP_GUID            = TEXT('FAXSRV_FSPGuid');
  {$EXTERNALSYM CF_MSFAXSRV_FSP_GUID}
  CF_MSFAXSRV_SERVER_NAME         = TEXT('FAXSRV_ServerName');
  {$EXTERNALSYM CF_MSFAXSRV_SERVER_NAME}
  CF_MSFAXSRV_ROUTEEXT_NAME       = TEXT('FAXSRV_RoutingExtName');
  {$EXTERNALSYM CF_MSFAXSRV_ROUTEEXT_NAME}
  CF_MSFAXSRV_ROUTING_METHOD_GUID = TEXT('FAXSRV_RoutingMethodGuid');
  {$EXTERNALSYM CF_MSFAXSRV_ROUTING_METHOD_GUID}

implementation

end.
