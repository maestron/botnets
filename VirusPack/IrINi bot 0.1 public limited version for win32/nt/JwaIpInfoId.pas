{******************************************************************************}
{                                                       	               }
{ Router Manager Protocol IDs API interface Unit for Object Pascal             }
{                                                       	               }
{ Portions created by Microsoft are Copyright (C) 1995-2001 Microsoft          }
{ Corporation. All Rights Reserved.                                            }
{ 								               }
{ The original file is: ipinfoid.h, released November 2002. The original Pascal}
{ code is: IpInfoId.pas, released March 2002. The initial developer of the     }
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

unit JwaIpInfoId;

{$WEAKPACKAGEUNIT}

{$HPPEMIT ''}
{$HPPEMIT '#include "ipinfoid.h"'}
{$HPPEMIT ''}

{$I WINDEFINES.INC}

interface

uses
  JwaWinType;

const
  IP_ROUTER_MANAGER_VERSION = 1;
  {$EXTERNALSYM IP_ROUTER_MANAGER_VERSION}

//////////////////////////////////////////////////////////////////////////////
//                                                                          //
// These are the ids used for different information types supported by      //
// IP Router Manager. These ids live in the same space as the IP Routing    //
// Protocol IDs, so any addition to them must be done with care             //
//                                                                          //
//////////////////////////////////////////////////////////////////////////////

  IP_GENERAL_INFO_BASE = DWORD($ffff0000);
  {$EXTERNALSYM IP_GENERAL_INFO_BASE}

  IP_IN_FILTER_INFO        = IP_GENERAL_INFO_BASE + 1;
  {$EXTERNALSYM IP_IN_FILTER_INFO}
  IP_OUT_FILTER_INFO       = IP_GENERAL_INFO_BASE + 2;
  {$EXTERNALSYM IP_OUT_FILTER_INFO}
  IP_GLOBAL_INFO           = IP_GENERAL_INFO_BASE + 3;
  {$EXTERNALSYM IP_GLOBAL_INFO}
  IP_INTERFACE_STATUS_INFO = IP_GENERAL_INFO_BASE + 4;
  {$EXTERNALSYM IP_INTERFACE_STATUS_INFO}
  IP_ROUTE_INFO            = IP_GENERAL_INFO_BASE + 5;
  {$EXTERNALSYM IP_ROUTE_INFO}
  IP_PROT_PRIORITY_INFO    = IP_GENERAL_INFO_BASE + 6;
  {$EXTERNALSYM IP_PROT_PRIORITY_INFO}
  IP_ROUTER_DISC_INFO      = IP_GENERAL_INFO_BASE + 7;
  {$EXTERNALSYM IP_ROUTER_DISC_INFO}

// N.B. Unused ID available at IP_GENERAL_INFO_BASE + 8.

  IP_DEMAND_DIAL_FILTER_INFO = IP_GENERAL_INFO_BASE + 9;
  {$EXTERNALSYM IP_DEMAND_DIAL_FILTER_INFO}
  IP_MCAST_HEARBEAT_INFO     = IP_GENERAL_INFO_BASE + 10;
  {$EXTERNALSYM IP_MCAST_HEARBEAT_INFO}
  IP_MCAST_BOUNDARY_INFO     = IP_GENERAL_INFO_BASE + 11;
  {$EXTERNALSYM IP_MCAST_BOUNDARY_INFO}
  IP_IPINIP_CFG_INFO         = IP_GENERAL_INFO_BASE + 12;
  {$EXTERNALSYM IP_IPINIP_CFG_INFO}
  IP_IFFILTER_INFO           = IP_GENERAL_INFO_BASE + 13;
  {$EXTERNALSYM IP_IFFILTER_INFO}
  IP_MCAST_LIMIT_INFO        = IP_GENERAL_INFO_BASE + 14;
  {$EXTERNALSYM IP_MCAST_LIMIT_INFO}

//////////////////////////////////////////////////////////////////////////////
//                                                                          //
// The following IDS are defined in routprot.h and given here for           //
// informational purposes only                                              //
//                                                                          //
// #define IP_OTHER         1                                               //
// #define IP_LOCAL         2                                               //
// #define IP_NETMGMT       3                                               //
// #define IP_ICMP          4                                               //
// #define IP_EGP           5                                               //
// #define IP_GGP           6                                               //
// #define IP_HELLO         7                                               //
// #define IP_RIP           8                                               //
// #define IP_IS_IS         9                                               //
// #define IP_ES_IS         10                                              //
// #define IP_CISCO         11                                              //
// #define IP_BBN           12                                              //
// #define IP_OSPF          13                                              //
// #define IP_BGP           14                                              //
//                                                                          //
// #define IP_BOOTP         9999                                            //
// #define IPRTRMGR_PID     10000                                           //
// #define IP_NT_AUTOSTATIC 10002                                           //
//                                                                          //
//////////////////////////////////////////////////////////////////////////////

implementation

end.
