{******************************************************************************}
{                                                       	               }
{ Management Base Information API interface Unit for Object Pascal             }
{                                                       	               }
{ Portions created by Microsoft are Copyright (C) 1995-2001 Microsoft          }
{ Corporation. All Rights Reserved.                                            }
{ 								               }
{ The original file is: mprerror.h, released August 2001. The original Pascal  }
{ code is: MprError.pas, released September 2000. The initial developer of the }
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

unit JwaMprError;

{$WEAKPACKAGEUNIT}

{$HPPEMIT ''}
{$HPPEMIT '#include "mprerror.h"'}
{$HPPEMIT ''}

{$I WINDEFINES.INC}

interface

const
  ROUTEBASE = 900;
  {$EXTERNALSYM ROUTEBASE}
  SUCCESS   = 0;
  {$EXTERNALSYM SUCCESS}

  ERROR_ROUTER_STOPPED = (ROUTEBASE+0);
  {$EXTERNALSYM ERROR_ROUTER_STOPPED}

(*
 * The router is not running.%0
 *)

  ERROR_ALREADY_CONNECTED = (ROUTEBASE+1);
  {$EXTERNALSYM ERROR_ALREADY_CONNECTED}

(*
 * The interface is already connected.%0
 *)

  ERROR_UNKNOWN_PROTOCOL_ID = (ROUTEBASE+2);
  {$EXTERNALSYM ERROR_UNKNOWN_PROTOCOL_ID}

(*
 * The specified protocol identifier is not known to the router.%0
 *)

  ERROR_DDM_NOT_RUNNING = (ROUTEBASE+3);
  {$EXTERNALSYM ERROR_DDM_NOT_RUNNING}

(*
 * The Demand-dial Interface Manager is not running.%0
 *)

  ERROR_INTERFACE_ALREADY_EXISTS = (ROUTEBASE+4);
  {$EXTERNALSYM ERROR_INTERFACE_ALREADY_EXISTS}

(*
 * An interface with this name is already registered with the router.%0
 *)

  ERROR_NO_SUCH_INTERFACE = (ROUTEBASE+5);
  {$EXTERNALSYM ERROR_NO_SUCH_INTERFACE}

(*
 * An interface with this name is not registered with the router.%0
 *)

  ERROR_INTERFACE_NOT_CONNECTED = (ROUTEBASE+6);
  {$EXTERNALSYM ERROR_INTERFACE_NOT_CONNECTED}

(*
 * The interface is not connected.%0
 *)

  ERROR_PROTOCOL_STOP_PENDING = (ROUTEBASE+7);
  {$EXTERNALSYM ERROR_PROTOCOL_STOP_PENDING}

(*
 * The specified protocol is stopping.%0
 *)

  ERROR_INTERFACE_CONNECTED = (ROUTEBASE+8);
  {$EXTERNALSYM ERROR_INTERFACE_CONNECTED}

(*
 * The interface is connected and hence cannot be deleted.%0
 *)

  ERROR_NO_INTERFACE_CREDENTIALS_SET = (ROUTEBASE+9);
  {$EXTERNALSYM ERROR_NO_INTERFACE_CREDENTIALS_SET}

(*
 * The interface credentials have not been set.%0
 *)

  ERROR_ALREADY_CONNECTING = (ROUTEBASE+10);
  {$EXTERNALSYM ERROR_ALREADY_CONNECTING}

(*
 * This interface is already in the process of connecting.%0
 *)

  ERROR_UPDATE_IN_PROGRESS = (ROUTEBASE+11);
  {$EXTERNALSYM ERROR_UPDATE_IN_PROGRESS}

(*
 * An update of routing information on this interface is already in progress.%0
 *)

  ERROR_INTERFACE_CONFIGURATION = (ROUTEBASE+12);
  {$EXTERNALSYM ERROR_INTERFACE_CONFIGURATION}

(*
 * The interface confugration in invalid. There is already another interface that is connected to the same inteface on the remote router.%0
 *)

  ERROR_NOT_CLIENT_PORT = (ROUTEBASE+13);
  {$EXTERNALSYM ERROR_NOT_CLIENT_PORT}

(*
 * A Remote Access Client attempted to connect over a port that was reserved for Routers only.%0
 *)

  ERROR_NOT_ROUTER_PORT = (ROUTEBASE+14);
  {$EXTERNALSYM ERROR_NOT_ROUTER_PORT}

(*
 * A Demand Dial Router attempted to connect over a port that was reserved for Remote Access Clients only.%0
 *)

  ERROR_CLIENT_INTERFACE_ALREADY_EXISTS = (ROUTEBASE+15);
  {$EXTERNALSYM ERROR_CLIENT_INTERFACE_ALREADY_EXISTS}

(*
 * The client interface with this name already exists and is currently connected.%0
 *)

  ERROR_INTERFACE_DISABLED = (ROUTEBASE+16);
  {$EXTERNALSYM ERROR_INTERFACE_DISABLED}

(*
 * The interface is in a disabled state.%0
 *)

  ERROR_AUTH_PROTOCOL_REJECTED = (ROUTEBASE+17);
  {$EXTERNALSYM ERROR_AUTH_PROTOCOL_REJECTED}

(*
 * The authentication protocol was rejected by the remote peer.%0
 *)

  ERROR_NO_AUTH_PROTOCOL_AVAILABLE = (ROUTEBASE+18);
  {$EXTERNALSYM ERROR_NO_AUTH_PROTOCOL_AVAILABLE}

(*
 * There are no authentication protocols available for use.%0
 *)

  ERROR_PEER_REFUSED_AUTH = (ROUTEBASE+19);
  {$EXTERNALSYM ERROR_PEER_REFUSED_AUTH}

(*
 * The remote computer refused to be authenticated using the configured authentication protocol. The line has been disconnected.%0
 *)

  ERROR_REMOTE_NO_DIALIN_PERMISSION = (ROUTEBASE+20);
  {$EXTERNALSYM ERROR_REMOTE_NO_DIALIN_PERMISSION}

(*
 * The remote account does not have Remote Access permission.%0
 *)

  ERROR_REMOTE_PASSWD_EXPIRED = (ROUTEBASE+21);
  {$EXTERNALSYM ERROR_REMOTE_PASSWD_EXPIRED}

(*
 * The remote account has expired.%0
 *)

  ERROR_REMOTE_ACCT_DISABLED = (ROUTEBASE+22);
  {$EXTERNALSYM ERROR_REMOTE_ACCT_DISABLED}

(*
 * The remote account is disabled.%0
 *)

  ERROR_REMOTE_RESTRICTED_LOGON_HOURS = (ROUTEBASE+23);
  {$EXTERNALSYM ERROR_REMOTE_RESTRICTED_LOGON_HOURS}

(*
 * The remote account is not permitted to logon at this time of day.%0
 *)

  ERROR_REMOTE_AUTHENTICATION_FAILURE = (ROUTEBASE+24);
  {$EXTERNALSYM ERROR_REMOTE_AUTHENTICATION_FAILURE}

(*
 * Access was denied to the remote peer  because username and/or password is invalid on the domain.%0
 *)

  ERROR_INTERFACE_HAS_NO_DEVICES = (ROUTEBASE+25);
  {$EXTERNALSYM ERROR_INTERFACE_HAS_NO_DEVICES}

(*
 * There are no routing enabled ports available for use by this demand dial interface.%0
 *)

  ERROR_IDLE_DISCONNECTED = (ROUTEBASE+26);
  {$EXTERNALSYM ERROR_IDLE_DISCONNECTED}

(*
 * The port has been disconnected due to inactivity.%0
 *)

  ERROR_INTERFACE_UNREACHABLE = (ROUTEBASE+27);
  {$EXTERNALSYM ERROR_INTERFACE_UNREACHABLE}

(*
 * The interface is not reachable at this time.%0
 *)

  ERROR_SERVICE_IS_PAUSED = (ROUTEBASE+28);
  {$EXTERNALSYM ERROR_SERVICE_IS_PAUSED}

(*
 * The Demand Dial service is in a paused state.%0
 *)

  ERROR_INTERFACE_DISCONNECTED = (ROUTEBASE+29);
  {$EXTERNALSYM ERROR_INTERFACE_DISCONNECTED}

(*
 * The interface has been disconnected by the administrator.%0
 *)

  ERROR_AUTH_SERVER_TIMEOUT = (ROUTEBASE+30);
  {$EXTERNALSYM ERROR_AUTH_SERVER_TIMEOUT}

(*
 * The authentication server did not respond to authentication requests in a timely fashion.%0
 *)

  ERROR_PORT_LIMIT_REACHED = (ROUTEBASE+31);
  {$EXTERNALSYM ERROR_PORT_LIMIT_REACHED}

(*
 * The maximum number of ports allowed for use in the multilinked connection has been reached.%0
 *)

  ERROR_PPP_SESSION_TIMEOUT = (ROUTEBASE+32);
  {$EXTERNALSYM ERROR_PPP_SESSION_TIMEOUT}

(*
 * The connection time limit for the user has been reached.%0
 *)

  ERROR_MAX_LAN_INTERFACE_LIMIT = (ROUTEBASE+33);
  {$EXTERNALSYM ERROR_MAX_LAN_INTERFACE_LIMIT}

(*
 * The maximum limit on the number of LAN interfaces supported has been reached.%0
 *)

  ERROR_MAX_WAN_INTERFACE_LIMIT = (ROUTEBASE+34);
  {$EXTERNALSYM ERROR_MAX_WAN_INTERFACE_LIMIT}

(*
 * The maximum limit on the number of Demand Dial interfaces supported has been reached.%0
 *)

  ERROR_MAX_CLIENT_INTERFACE_LIMIT = (ROUTEBASE+35);
  {$EXTERNALSYM ERROR_MAX_CLIENT_INTERFACE_LIMIT}

(*
 * The maximum limit on the number of Remote Access clients supported has been reached.%0
 *)

  ERROR_BAP_DISCONNECTED = (ROUTEBASE+36);
  {$EXTERNALSYM ERROR_BAP_DISCONNECTED}

(*
 * The port has been disconnected due to the BAP policy.%0
 *)

  ERROR_USER_LIMIT = (ROUTEBASE+37);
  {$EXTERNALSYM ERROR_USER_LIMIT}

(*
 * Because another connection of your type is in use, the incoming connection cannot accept your connection request.%0
 *)

  ERROR_NO_RADIUS_SERVERS = (ROUTEBASE+38);
  {$EXTERNALSYM ERROR_NO_RADIUS_SERVERS}

(*
 * No RADIUS servers were located on the network.%0
 *)

  ERROR_INVALID_RADIUS_RESPONSE = (ROUTEBASE+39);
  {$EXTERNALSYM ERROR_INVALID_RADIUS_RESPONSE}

(*
 * An invalid response was received from the RADIUS authentication server.
 * Make sure that the case sensitive secret pasword for the RADIUS server is set correctly.%0
 *)

  ERROR_DIALIN_HOURS_RESTRICTION = (ROUTEBASE+40);
  {$EXTERNALSYM ERROR_DIALIN_HOURS_RESTRICTION}

(*
 * You do not have permission to connect at this time.%0
 *)

  ERROR_ALLOWED_PORT_TYPE_RESTRICTION = (ROUTEBASE+41);
  {$EXTERNALSYM ERROR_ALLOWED_PORT_TYPE_RESTRICTION}

(*
 * You do not have permission to connect using the current device type.%0
 *)

  ERROR_AUTH_PROTOCOL_RESTRICTION = (ROUTEBASE+42);
  {$EXTERNALSYM ERROR_AUTH_PROTOCOL_RESTRICTION}

(*
 * You do not have permission to connect using the selected authentication protocol.%0
 *)

  ERROR_BAP_REQUIRED = (ROUTEBASE+43);
  {$EXTERNALSYM ERROR_BAP_REQUIRED}

(*
 * BAP is required for this user.%0
 *)

  ERROR_DIALOUT_HOURS_RESTRICTION = (ROUTEBASE+44);
  {$EXTERNALSYM ERROR_DIALOUT_HOURS_RESTRICTION}

(*
 * The interface is not allowed to connect at this time.%0
 *)

  ERROR_ROUTER_CONFIG_INCOMPATIBLE = (ROUTEBASE+45);
  {$EXTERNALSYM ERROR_ROUTER_CONFIG_INCOMPATIBLE}

(*
 * The saved router configuration is incompatible with the current router.%0
 *)

  WARNING_NO_MD5_MIGRATION = (ROUTEBASE+46);
  {$EXTERNALSYM WARNING_NO_MD5_MIGRATION}

(*
 * RemoteAccess has detected older format user accounts that will not be
 * migrated automatically.  To migrate these manually, run XXXX.
 *)

  ERROR_PROTOCOL_ALREADY_INSTALLED          = (ROUTEBASE+48);
  {$EXTERNALSYM ERROR_PROTOCOL_ALREADY_INSTALLED}

(*
 * The transport is already installed with the router.%0
 *)

  ERROR_INVALID_SIGNATURE_LENGTH            = (ROUTEBASE+49);
  {$EXTERNALSYM ERROR_INVALID_SIGNATURE_LENGTH}

(*
 * Received invalid signature length in packet from RADIUS server.%0
 *)

  ERROR_INVALID_SIGNATURE                   = (ROUTEBASE+50);
  {$EXTERNALSYM ERROR_INVALID_SIGNATURE}

(*
 * Received invalid signature in packet from RADIUS server.%0
 *)

  ERROR_NO_SIGNATURE                        = (ROUTEBASE+51);
  {$EXTERNALSYM ERROR_NO_SIGNATURE}

(*
 * Did not receive signature along with EAPMessage from RADIUS server.%0
 *)

  ERROR_INVALID_PACKET_LENGTH_OR_ID         = (ROUTEBASE+52);
  {$EXTERNALSYM ERROR_INVALID_PACKET_LENGTH_OR_ID}

(*
 * Received packet with invalid length or Id from RADIUS server.%0
 *)

  ERROR_INVALID_ATTRIBUTE_LENGTH            = (ROUTEBASE+53);
  {$EXTERNALSYM ERROR_INVALID_ATTRIBUTE_LENGTH}

(*
 * Received packet with attribute with invalid length from RADIUS server.%0
 *)

  ERROR_INVALID_PACKET                      = (ROUTEBASE+54);
  {$EXTERNALSYM ERROR_INVALID_PACKET}

(*
 * Received invalid packet from RADIUS server.%0
 *)

  ERROR_AUTHENTICATOR_MISMATCH              = (ROUTEBASE+55);
  {$EXTERNALSYM ERROR_AUTHENTICATOR_MISMATCH}

(*
 * Authenticator does not match in packet from RADIUS server.%0
 *)

  ROUTEBASEEND                              = (ROUTEBASE+56);
  {$EXTERNALSYM ROUTEBASEEND}

implementation

end.
