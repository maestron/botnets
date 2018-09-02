/*	shellbot - a high performance IRC bot for Win32
	Copyright (C) 2005 Shellz

	This program is free software; you can redistribute it and/or
	modify it under the terms of the GNU General Public License
	as published by the Free Software Foundation; either version 2
	of the License, or (at your option) any later version.

	This program is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
	GNU General Public License for more details.

	You should have received a copy of the GNU General Public License
	along with this program; if not, write to the Free Software
	Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA. */

#include "vInclude.h"
#include "vPOEb.h"

//!
//! KeepAlive (TM) system
//! 
void *CKeepAlive::Run() {
	vPOEb->vIRC.vReply = false;
	vPOEb->vIRC.bInitiated = false;
	while(1) {
		if (vPOEb->vIRC.IRCRunning && vPOEb->vIRC.bInitiated) {
			if (!vPOEb->vIRC.SendData("PING EB3984CD\r\n",vPOEb->vCmd.serverAlias.c_str()))
				continue;
#ifdef DEBUG_MODE
			vPOEb->DebugPrint("debug",con::fg_gray,"Sent PING...");
#endif // DEBUGMODE	
			Sleep(10000);
#ifdef DEBUG_MODE
			vPOEb->DebugPrint("debug",con::fg_gray,"10 seconds passed...");
#endif // DEBUGMODE	
			if (!vPOEb->vIRC.vReply && vPOEb->vIRC.IRCRunning) {
#ifdef DEBUG_MODE
				vPOEb->DebugPrint("debug",con::fg_gray,"No PONG as of yet..."); 
#endif // DEBUGMODE
				vPOEb->vIRC.Disconnect("Ping Timeout");
			}
			vPOEb->vIRC.vReply = false; 			
			Sleep(60000); 
#ifdef DEBUG_MODE
			vPOEb->DebugPrint("debug",con::fg_gray,"240 seconds passed...");
#endif // DEBUGMODE
		} 
		Sleep(3000); 
	}
	return NULL; 
}
