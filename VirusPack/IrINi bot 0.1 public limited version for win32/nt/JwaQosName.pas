{******************************************************************************}
{                                                       	               }
{ Winsock2 QOS Template Names  API interface Unit for Object Pascal            }
{                                                       	               }
{ Portions created by Microsoft are Copyright (C) 1995-2001 Microsoft          }
{ Corporation. All Rights Reserved.                                            }
{ 								               }
{ The original file is: qosname.h, released June 2000. The original Pascal     }
{ code is: QosName.pas, released December 2000. The initial developer of the   }
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

unit JwaQosName;

{$WEAKPACKAGEUNIT}

{$HPPEMIT ''}
{$HPPEMIT '#include "qosname.h"'}
{$HPPEMIT ''}

{$I WINDEFINES.INC}

interface

uses
{$IFDEF STANDALONE}
  JwaWinTypes,
{$ELSE}
  Windows,
{$ENDIF}
  JwaWinSock2;

// Built-in QoS Templates

const
  QT_1       = 'G711';
  {$EXTERNALSYM QT_1}
  QT_2       = 'G723.1';
  {$EXTERNALSYM QT_2}
  QT_3       = 'G729';
  {$EXTERNALSYM QT_3}
  QT_4       = 'H263QCIF';
  {$EXTERNALSYM QT_4}
  QT_5       = 'H263CIF';
  {$EXTERNALSYM QT_5}
  QT_6       = 'H261QCIF';
  {$EXTERNALSYM QT_6}
  QT_7       = 'H261CIF';
  {$EXTERNALSYM QT_7}
  QT_8       = 'GSM6.10';
  {$EXTERNALSYM QT_8}

  WSCINSTALL_QOS_TEMPLATE    = 'WSCInstallQOSTemplate';
  {$EXTERNALSYM WSCINSTALL_QOS_TEMPLATE}
  WSCREMOVE_QOS_TEMPLATE     = 'WSCRemoveQOSTemplate';
  {$EXTERNALSYM WSCREMOVE_QOS_TEMPLATE}
  WPUGET_QOS_TEMPLATE        = 'WPUGetQOSTemplate';
  {$EXTERNALSYM WPUGET_QOS_TEMPLATE}

type
  WSC_INSTALL_QOS_TEMPLATE = function (Guid: PGUID; QosName: LPWSABUF; Qos: LPQOS): BOOL; stdcall;
  {$EXTERNALSYM WSC_INSTALL_QOS_TEMPLATE}
  TWscInstallQosTemplate = WSC_INSTALL_QOS_TEMPLATE;

  WSC_REMOVE_QOS_TEMPLATE = function (Guid: PGUID; QosName: LPWSABUF): BOOL; stdcall;
  {$EXTERNALSYM WSC_REMOVE_QOS_TEMPLATE}
  TWscRemoveQosTemplate = WSC_REMOVE_QOS_TEMPLATE;

  WPU_GET_QOS_TEMPLATE = function (Guid: PGUID; QosName: LPWSABUF; Qos: LPQOS): BOOL; stdcall;
  {$EXTERNALSYM WPU_GET_QOS_TEMPLATE}
  TWpuGetQosTemplate = WPU_GET_QOS_TEMPLATE;

implementation

end.
